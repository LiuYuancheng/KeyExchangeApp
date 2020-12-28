/*
 * CBikeKem.cpp
 *
 *  Created on: 20 Feb 2020
 *      Author: yiwen
 */

#include "../../generic_service/kems/CSaberKem.h"

#include <libpqch/libpqch.h>

#include <string>

#include "../../generic_service/kems/CKem.h"

using namespace std;

CSaberKem::CSaberKem(string &pubkey, string &privkey) :
		CKem("SABER-KEM", SABER_CRYPTO_ALGNAME, pubkey, privkey)
{

	// TODO Auto-generated constructor stub

}

CSaberKem::~CSaberKem()
{

	// TODO Auto-generated destructor stub
}

int CSaberKem::KeyGen()
{
	unsigned char *p, *q;

	p = new unsigned char(SABER_CRYPTO_PUBLICKEYBYTES);
	q = new unsigned char(SABER_CRYPTO_SECRETKEYBYTES);

	::SABER_crypto_kem_keypair(p, q);

	string pk((char*) p, SABER_CRYPTO_PUBLICKEYBYTES), sk((char*) q,
	SABER_CRYPTO_SECRETKEYBYTES);

	delete p, q;

	PubKey = pk;
	PrivKey = sk;

	return 0;
}

int CSaberKem::Encaps()
{
	unsigned char *ct, *ss;

	ct = new unsigned char[SABER_CRYPTO_CIPHERTEXTBYTES];
	ss = new unsigned char[SABER_CRYPTO_BYTES];


	::SABER_crypto_kem_enc(ct, ss, (unsigned char*) PubKey.data());

//	cout << "SABER CipherText Encaps:" << endl;
//	BIO_dump_fp(stdout, ct, SABER_CRYPTO_CIPHERTEXTBYTES);
//	cout << "SABER SharedStr:" << endl;
//	BIO_dump_fp(stdout, ss, SABER_CRYPTO_BYTES);

	string ctstr((char*) ct, SABER_CRYPTO_CIPHERTEXTBYTES);
	string ssstr((char*) ss, SABER_CRYPTO_BYTES);

	CipherText = ctstr;
	SharedStr = ssstr;

	delete[] ct;
	delete[] ss;

	return 0;
}

int CSaberKem::Decaps()
{
	unsigned char *ss;

	ss = new unsigned char[SABER_CRYPTO_BYTES];

	SABER_crypto_kem_dec(ss, (unsigned char*) CipherText.data(),
			(unsigned char*) PrivKey.data());

//	cout << "SABER CipherText Decaps:" << endl;
//	BIO_dump_fp(stdout, (unsigned char*) CipherText.data(),
//			SABER_CRYPTO_CIPHERTEXTBYTES);
//	cout << "SABER SharedStr:" << endl;
//	BIO_dump_fp(stdout, ss, SABER_CRYPTO_BYTES);

	string ssstr((char*) ss, SABER_CRYPTO_BYTES);

	delete[] ss;

	SharedStr = ssstr;

	return 0;
}

