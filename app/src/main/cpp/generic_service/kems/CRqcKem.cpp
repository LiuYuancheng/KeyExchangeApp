/*
 * CRqcKem.cpp
 *
 *  Created on: 25 Feb 2020
 *      Author: yiwen
 */

#include "../../generic_service/kems/CRqcKem.h"

#include <libpqch/libpqch.h>
#include <string.h>

#include "../../generic_service/debug_config.h"

CRqcKem::CRqcKem(string &pubkey, string &privkey) :
		CKem("RQC-KEM", RQC_CRYPTO_ALGNAME, pubkey, privkey)
{

	// TODO Auto-generated constructor stub

}

CRqcKem::~CRqcKem()
{

	// TODO Auto-generated destructor stub
}

int CRqcKem::KeyGen()
{
	//RQC_crypto_kem_keypair(PubKey, PrivKey);

	return 0;
}

int CRqcKem::Encaps()
{
	unsigned char *ct, *ss, *pk;

	ct = new unsigned char[RQC_CRYPTO_CIPHERTEXTBYTES];
	ss = new unsigned char[RQC_CRYPTO_BYTES];
	pk = new unsigned char[RQC_CRYPTO_PUBLICKEYBYTES];

	cout<<"@@@@@@@@@@@@@@@@@ RQC keysize:" <<RQC_CRYPTO_PUBLICKEYBYTES<<":"<<PubKey.size()<<endl;

	memcpy(pk, PubKey.data(), PubKey.size());

	::RQC_crypto_kem_enc(ct, ss, pk);

#ifdef KEP_DEBUG_RQC_KEM_ENC_CT_SS
	cout<<"Rqc CipherText Encaps:"<<endl;
	BIO_dump_fp(stdout, ct, RQC_CRYPTO_CIPHERTEXTBYTES);
	cout<<"Rqc SharedStr:"<<endl;
	BIO_dump_fp(stdout, ss, RQC_CRYPTO_BYTES);
#endif

	string ctstr((char*)ct, RQC_CRYPTO_CIPHERTEXTBYTES);
	string ssstr((char*)ss, RQC_CRYPTO_BYTES);

	CipherText = ctstr;
	SharedStr = ssstr;

	delete[] ct;
	delete[] ss;
	delete[] pk;

	return 0;
}



int CRqcKem::Decaps()
{
	unsigned char *ct, *ss;

	ss = new unsigned char[RQC_CRYPTO_BYTES];
	ct = new unsigned char[RQC_CRYPTO_CIPHERTEXTBYTES];

	memcpy(ct, CipherText.data(), CipherText.size());

	::RQC_crypto_kem_dec(ss, ct, (unsigned char *)PrivKey.data());

#ifdef KEP_DEBUG_RQC_KEM_DEC_CT_SS
	cout<<"Rqc CipherText Decaps:"<<endl;
	BIO_dump_fp(stdout, CipherText.data(), RQC_CRYPTO_CIPHERTEXTBYTES);
	cout<<"Rqc SharedStr:"<<endl;
	BIO_dump_fp(stdout, ss, RQC_CRYPTO_BYTES);
#endif

	string ssstr((char*)ss, RQC_CRYPTO_BYTES);

	SharedStr = ssstr;

	delete[] ss;
	delete[] ct;

	return 0;
}
