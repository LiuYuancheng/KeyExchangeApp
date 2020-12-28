/*
 * CBikeKem.cpp
 *
 *  Created on: 20 Feb 2020
 *      Author: yiwen
 */

#include "../../generic_service/kems/CSikeKem.h"

#include <libpqch/libpqch.h>

#include <string>

#include "../../generic_service/kems/CKem.h"

using namespace std;

CSikeKem::CSikeKem(string &pubkey, string &privkey) :
		CKem("SIKE-KEM", SIKE_CRYPTO_ALGNAME, pubkey, privkey)
{

	// TODO Auto-generated constructor stub

}

CSikeKem::~CSikeKem()
{

	// TODO Auto-generated destructor stub
}

int CSikeKem::KeyGen()
{
	unsigned char *p, *q;

	p = new unsigned char(SIKE_CRYPTO_PUBLICKEYBYTES);
	q = new unsigned char(SIKE_CRYPTO_SECRETKEYBYTES);

	::SIKE_crypto_kem_keypair(p, q);

	string pk((char*) p, SIKE_CRYPTO_PUBLICKEYBYTES), sk((char*) q,
	SIKE_CRYPTO_SECRETKEYBYTES);

	delete p, q;

	PubKey = pk;
	PrivKey = sk;

	return 0;
}

int CSikeKem::Encaps()
{
	unsigned char *ct, *ss;

	ct = new unsigned char[SIKE_CRYPTO_CIPHERTEXTBYTES];
	ss = new unsigned char[SIKE_CRYPTO_BYTES];

	::SIKE_crypto_kem_enc(ct, ss, (unsigned char*) PubKey.data());

//	cout << "SIKE CipherText Encaps:" << endl;
//	BIO_dump_fp(stdout, ct, SIKE_CRYPTO_CIPHERTEXTBYTES);
//	cout << "SIKE SharedStr:" << endl;
//	BIO_dump_fp(stdout, ss, SIKE_CRYPTO_BYTES);

	string ctstr((char*) ct, SIKE_CRYPTO_CIPHERTEXTBYTES);
	string ssstr((char*) ss, SIKE_CRYPTO_BYTES);

	CipherText = ctstr;
	SharedStr = ssstr;

	delete[] ct;
	delete[] ss;

	return 0;
}

int CSikeKem::Decaps()
{
	unsigned char *ss;

	ss = new unsigned char[SIKE_CRYPTO_BYTES];

	SIKE_crypto_kem_dec(ss, (unsigned char*) CipherText.data(),
			(unsigned char*) PrivKey.data());

//	cout << "SIKE CipherText Decaps:" << endl;
//	BIO_dump_fp(stdout, (unsigned char*) CipherText.data(),
//			SIKE_CRYPTO_CIPHERTEXTBYTES);
//	cout << "SIKE SharedStr:" << endl;
//	BIO_dump_fp(stdout, ss, SIKE_CRYPTO_BYTES);

	string ssstr((char*) ss, SIKE_CRYPTO_BYTES);

	delete[] ss;

	SharedStr = ssstr;

	return 0;
}

