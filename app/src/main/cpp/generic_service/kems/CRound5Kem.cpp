/*
 * CBikeKem.cpp
 *
 *  Created on: 20 Feb 2020
 *      Author: yiwen
 */

#include "../../generic_service/kems/CRound5Kem.h"

#include <libpqch/libpqch.h>

#include <string>

#include "../../generic_service/kems/CKem.h"

using namespace std;

CRound5Kem::CRound5Kem(string &pubkey, string &privkey) :
		CKem("ROUND5-KEM", ROUND5_CRYPTO_ALGNAME, pubkey, privkey)
{

	// TODO Auto-generated constructor stub

}

CRound5Kem::~CRound5Kem()
{

	// TODO Auto-generated destructor stub
}

int CRound5Kem::KeyGen()
{
	unsigned char *p, *q;

	p = new unsigned char(ROUND5_CRYPTO_PUBLICKEYBYTES);
	q = new unsigned char(ROUND5_CRYPTO_SECRETKEYBYTES);

	::ROUND5_crypto_kem_keypair(p, q);

	string pk((char*) p, ROUND5_CRYPTO_PUBLICKEYBYTES), sk((char*) q,
	ROUND5_CRYPTO_SECRETKEYBYTES);

	delete p, q;

	PubKey = pk;
	PrivKey = sk;

	return 0;
}

int CRound5Kem::Encaps()
{
	unsigned char *ct, *ss;

	ct = new unsigned char[ROUND5_CRYPTO_CIPHERTEXTBYTES];
	ss = new unsigned char[ROUND5_CRYPTO_BYTES];

	::ROUND5_crypto_kem_enc(ct, ss, (unsigned char*) PubKey.data());

//	cout << "ROUND5 CipherText Encaps:" << endl;
//	BIO_dump_fp(stdout, ct, ROUND5_CRYPTO_CIPHERTEXTBYTES);
//	cout << "ROUND5 SharedStr:" << endl;
//	BIO_dump_fp(stdout, ss, ROUND5_CRYPTO_BYTES);

	string ctstr((char*) ct, ROUND5_CRYPTO_CIPHERTEXTBYTES);
	string ssstr((char*) ss, ROUND5_CRYPTO_BYTES);

	CipherText = ctstr;
	SharedStr = ssstr;

	delete[] ct;
	delete[] ss;

	return 0;
}

int CRound5Kem::Decaps()
{
	unsigned char *ss;

	ss = new unsigned char[ROUND5_CRYPTO_BYTES];

	ROUND5_crypto_kem_dec(ss, (unsigned char*) CipherText.data(),
			(unsigned char*) PrivKey.data());

//	cout << "ROUND5 CipherText Decaps:" << endl;
//	BIO_dump_fp(stdout, (unsigned char*) CipherText.data(),
//			ROUND5_CRYPTO_CIPHERTEXTBYTES);
//	cout << "ROUND5 SharedStr:" << endl;
//	BIO_dump_fp(stdout, ss, ROUND5_CRYPTO_BYTES);

	string ssstr((char*) ss, ROUND5_CRYPTO_BYTES);

	delete[] ss;

	SharedStr = ssstr;

	return 0;
}

