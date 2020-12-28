/*
 * CBikeKem.cpp
 *
 *  Created on: 20 Feb 2020
 *      Author: yiwen
 */

#include "../../generic_service/kems/CCmKem.h"

#include  <libpqch/libpqch.h>

#include <string>

#include "../../generic_service/kems/CKem.h"

using namespace std;

CCmKem::CCmKem(string &pubkey, string &privkey) :
		CKem("CM-KEM", CM_CRYPTO_ALGNAME, pubkey, privkey)
{

	// TODO Auto-generated constructor stub

}

CCmKem::~CCmKem()
{

	// TODO Auto-generated destructor stub
}

int CCmKem::KeyGen()
{
	unsigned char *p, *q;

	p = new unsigned char(CM_CRYPTO_PUBLICKEYBYTES);
	q = new unsigned char(CM_CRYPTO_SECRETKEYBYTES);

	::CM_crypto_kem_keypair(p, q);

	string pk((char*) p, CM_CRYPTO_PUBLICKEYBYTES), sk((char*) q,
	CM_CRYPTO_SECRETKEYBYTES);

	delete p, q;

	PubKey = pk;
	PrivKey = sk;

	return 0;
}

int CCmKem::Encaps()
{
	unsigned char *ct, *ss;

	ct = new unsigned char[CM_CRYPTO_CIPHERTEXTBYTES];
	ss = new unsigned char[CM_CRYPTO_BYTES];

	::CM_crypto_kem_enc(ct, ss, (unsigned char*) PubKey.data());

//	cout << "CM CipherText Encaps:" << endl;
//	BIO_dump_fp(stdout, ct, CM_CRYPTO_CIPHERTEXTBYTES);
//	cout << "CM SharedStr:" << endl;
//	BIO_dump_fp(stdout, ss, CM_CRYPTO_BYTES);

	string ctstr((char*) ct, CM_CRYPTO_CIPHERTEXTBYTES);
	string ssstr((char*) ss, CM_CRYPTO_BYTES);

	CipherText = ctstr;
	SharedStr = ssstr;

	delete[] ct;
	delete[] ss;

	return 0;
}

int CCmKem::Decaps()
{
	unsigned char *ss;

	ss = new unsigned char[CM_CRYPTO_BYTES];

	CM_crypto_kem_dec(ss, (unsigned char*) CipherText.data(),
			(unsigned char*) PrivKey.data());

//	cout << "CM CipherText Decaps:" << endl;
//	BIO_dump_fp(stdout, (unsigned char*) CipherText.data(),
//	CM_CRYPTO_CIPHERTEXTBYTES);
//	cout << "CM SharedStr:" << endl;
//	BIO_dump_fp(stdout, ss, CM_CRYPTO_BYTES);

	string ssstr((char*) ss, CM_CRYPTO_BYTES);

	delete[] ss;

	SharedStr = ssstr;

	return 0;
}

