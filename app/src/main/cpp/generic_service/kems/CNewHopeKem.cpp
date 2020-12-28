/*
 * CNewHopeKem.cpp
 *
 *  Created on: 25 Feb 2020
 *      Author: yiwen
 */

#include "../../generic_service/kems/CNewHopeKem.h"

#include <libpqch/libpqch.h>

#include "../../generic_service/debug_config.h"

CNewHopeKem::CNewHopeKem(string &pubkey, string &privkey) :
		CKem("NEWHOPE-KEM", NEWHOPE_CRYPTO_ALGNAME, pubkey, privkey)
{

	// TODO Auto-generated constructor stub

}

CNewHopeKem::~CNewHopeKem()
{

	// TODO Auto-generated destructor stub
}

int CNewHopeKem::KeyGen()
{
	//NEWHOPE_crypto_kem_keypair(PubKey, PrivKey);

	return 0;
}

int CNewHopeKem::Encaps()
{
	unsigned char *ct, *ss;

	ct = new unsigned char[NEWHOPE_CRYPTO_CIPHERTEXTBYTES];
	ss = new unsigned char[NEWHOPE_CRYPTO_BYTES];

	::NewHope_crypto_kem_enc(ct, ss, (unsigned char *)PubKey.data());

#ifdef KEP_DEBUG_NEWHOPE_KEM_ENC_CT_SS
	cout<<"NEWHOPE CipherText Encaps:"<<endl;
	BIO_dump_fp(stdout, ct, NEWHOPE_CRYPTO_CIPHERTEXTBYTES);
	cout<<"NEWHOPE SharedStr:"<<endl;
	BIO_dump_fp(stdout, ss, NEWHOPE_CRYPTO_BYTES);
#endif

	string ctstr((char*)ct, NEWHOPE_CRYPTO_CIPHERTEXTBYTES);
	string ssstr((char*)ss, NEWHOPE_CRYPTO_BYTES);

	CipherText = ctstr;
	SharedStr = ssstr;

	delete[] ct;
	delete[] ss;

	return 0;
}
int CNewHopeKem::Decaps()
{
	unsigned char *ct, *ss;

	ss = new unsigned char[NEWHOPE_CRYPTO_BYTES];

	::NewHope_crypto_kem_dec(ss, (unsigned char*)CipherText.data(), (unsigned char *)PrivKey.data());

#ifdef KEP_DEBUG_NEWHOPE_KEM_DEC_CT_SS
	cout<<"NEWHOPE CipherText Decaps:"<<endl;
	BIO_dump_fp(stdout, CipherText.data(), NEWHOPE_CRYPTO_CIPHERTEXTBYTES);
	cout<<"NEWHOPE SharedStr:"<<endl;
	BIO_dump_fp(stdout, ss, NEWHOPE_CRYPTO_BYTES);
#endif

	string ssstr((char*)ss, NEWHOPE_CRYPTO_BYTES);

	SharedStr = ssstr;

	delete[] ss;

	return 0;
}
