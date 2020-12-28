/*
 * CBikeKem.cpp
 *
 *  Created on: 20 Feb 2020
 *      Author: yiwen
 */

#include "../../generic_service/kems/CThreeBearsKem.h"

#include <libpqch/libpqch.h>

#include <string>

#include "../../generic_service/kems/CKem.h"

using namespace std;

CThreeBearsKem::CThreeBearsKem(string &pubkey, string &privkey) :
		CKem("THREEBEARS-KEM", THREEBEARS_CRYPTO_ALGNAME, pubkey, privkey)
{

	// TODO Auto-generated constructor stub

}

CThreeBearsKem::~CThreeBearsKem()
{

	// TODO Auto-generated destructor stub
}

int CThreeBearsKem::KeyGen()
{
	unsigned char *p, *q;

	p = new unsigned char(THREEBEARS_CRYPTO_PUBLICKEYBYTES);
	q = new unsigned char(THREEBEARS_CRYPTO_SECRETKEYBYTES);

	ThreeBears_crypto_kem_keypair(p, q);

	string pk((char*) p, THREEBEARS_CRYPTO_PUBLICKEYBYTES), sk((char*) q,
	THREEBEARS_CRYPTO_SECRETKEYBYTES);

	delete p, q;

	PubKey = pk;
	PrivKey = sk;

	return 0;
}

int CThreeBearsKem::Encaps()
{
	unsigned char *ct, *ss;

	ct = new unsigned char[THREEBEARS_CRYPTO_CIPHERTEXTBYTES];
	ss = new unsigned char[THREEBEARS_CRYPTO_BYTES];

	ThreeBears_crypto_kem_enc(ct, ss, (unsigned char*) PubKey.data());

//	cout << "THREEBEARS CipherText Encaps:" << endl;
//	BIO_dump_fp(stdout, ct, THREEBEARS_CRYPTO_CIPHERTEXTBYTES);
//	cout << "THREEBEARS SharedStr:" << endl;
//	BIO_dump_fp(stdout, ss, THREEBEARS_CRYPTO_BYTES);

	string ctstr((char*) ct, THREEBEARS_CRYPTO_CIPHERTEXTBYTES);
	string ssstr((char*) ss, THREEBEARS_CRYPTO_BYTES);

	CipherText = ctstr;
	SharedStr = ssstr;

	delete[] ct;
	delete[] ss;

	return 0;
}

int CThreeBearsKem::Decaps()
{
	unsigned char *ss;

	ss = new unsigned char[THREEBEARS_CRYPTO_BYTES];

	ThreeBears_crypto_kem_dec(ss, (unsigned char*) CipherText.data(),
			(unsigned char*) PrivKey.data());

//	cout << "THREEBEARS CipherText Decaps:" << endl;
//	BIO_dump_fp(stdout, (unsigned char*) CipherText.data(),
//			THREEBEARS_CRYPTO_CIPHERTEXTBYTES);
//	cout << "THREEBEARS SharedStr:" << endl;
//	BIO_dump_fp(stdout, ss, THREEBEARS_CRYPTO_BYTES);

	string ssstr((char*) ss, THREEBEARS_CRYPTO_BYTES);

	delete[] ss;

	SharedStr = ssstr;

	return 0;
}

