/*
 * CHqcKem.cpp
 *
 *  Created on: 25 Feb 2020
 *      Author: yiwen
 */

#include "../../generic_service/kems/CHqcKem.h"

#include <libpqch/libpqch.h>

CHqcKem::CHqcKem(string &pubkey, string &privkey) :
		CKem("HQC-KEM", HQC_CRYPTO_ALGNAME, pubkey, privkey)
{

	// TODO Auto-generated constructor stub

}

CHqcKem::~CHqcKem()
{

	// TODO Auto-generated destructor stub
}

int CHqcKem::KeyGen()
{
	//HQC_crypto_kem_keypair(PubKey, PrivKey);

	return 0;
}

int CHqcKem::Encaps()
{
	unsigned char *ct, *ss;

	ct = new unsigned char[HQC_CRYPTO_CIPHERTEXTBYTES];
	ss = new unsigned char[HQC_CRYPTO_BYTES];

	::HQC_crypto_kem_enc(ct, ss, (unsigned char *)PubKey.data());

#ifdef KEP_DEBUG_HQC_KEM_ENC_CT_SS
	cout<<"Hqc CipherText Encaps:"<<endl;
	BIO_dump_fp(stdout, ct, HQC_CRYPTO_CIPHERTEXTBYTES);
	cout<<"Hqc SharedStr:"<<endl;
	BIO_dump_fp(stdout, ss, HQC_CRYPTO_BYTES);
#endif

	string ctstr((char*)ct, HQC_CRYPTO_CIPHERTEXTBYTES);
	string ssstr((char*)ss, HQC_CRYPTO_BYTES);

	CipherText = ctstr;
	SharedStr = ssstr;

	delete[] ct;
	delete[] ss;

	return 0;
}
int CHqcKem::Decaps()
{
	unsigned char *ct, *ss;

	ss = new unsigned char[HQC_CRYPTO_BYTES];

	::HQC_crypto_kem_dec(ss, (unsigned char*)CipherText.data(), (unsigned char *)PrivKey.data());

#ifdef KEP_DEBUG_HQC_KEM_DEC_CT_SS
	cout<<"Hqc CipherText Decaps:"<<endl;
	BIO_dump_fp(stdout, CipherText.data(), HQC_CRYPTO_CIPHERTEXTBYTES);
	cout<<"Hqc SharedStr:"<<endl;
	BIO_dump_fp(stdout, ss, HQC_CRYPTO_BYTES);
#endif
	string ssstr((char*)ss, HQC_CRYPTO_BYTES);

	SharedStr = ssstr;

	delete[] ss;

	return 0;
}
