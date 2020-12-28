/*
 * CBikeKem.cpp
 *
 *  Created on: 20 Feb 2020
 *      Author: yiwen
 */

#include "../../generic_service/kems/CKyberKem.h"

#include <libpqch/libpqch.h>

#include <string>

#include "../../generic_service/kems/CKem.h"

using namespace std;

CKyberKem::CKyberKem(string &pubkey, string &privkey) :
		CKem("KYBER-KEM", KYBER_CRYPTO_ALGNAME, pubkey, privkey)
{

	// TODO Auto-generated constructor stub

}

CKyberKem::~CKyberKem()
{

	// TODO Auto-generated destructor stub
}

int CKyberKem::KeyGen()
{
	unsigned char *p, *q;

	p = new unsigned char(KYBER_CRYPTO_PUBLICKEYBYTES);
	q = new unsigned char(KYBER_CRYPTO_SECRETKEYBYTES);

	::KYBER_crypto_kem_keypair(p, q);

	string pk((char*) p, KYBER_CRYPTO_PUBLICKEYBYTES), sk((char*) q,
	KYBER_CRYPTO_SECRETKEYBYTES);

	delete p, q;

	PubKey = pk;
	PrivKey = sk;

	return 0;
}

int CKyberKem::Encaps()
{
	unsigned char *ct, *ss;

	ct = new unsigned char[KYBER_CRYPTO_CIPHERTEXTBYTES];
	ss = new unsigned char[KYBER_CRYPTO_BYTES];


	::KYBER_crypto_kem_enc(ct, ss, (unsigned char*) PubKey.data());

//	cout << "KYBER CipherText Encaps:" << endl;
//	BIO_dump_fp(stdout, ct, KYBER_CRYPTO_CIPHERTEXTBYTES);
//	cout << "KYBER SharedStr:" << endl;
//	BIO_dump_fp(stdout, ss, KYBER_CRYPTO_BYTES);

	string ctstr((char*) ct, KYBER_CRYPTO_CIPHERTEXTBYTES);
	string ssstr((char*) ss, KYBER_CRYPTO_BYTES);

	CipherText = ctstr;
	SharedStr = ssstr;

	delete[] ct;
	delete[] ss;

	return 0;
}

int CKyberKem::Decaps()
{
	unsigned char *ss;

	ss = new unsigned char[KYBER_CRYPTO_BYTES];

	KYBER_crypto_kem_dec(ss, (unsigned char*) CipherText.data(),
			(unsigned char*) PrivKey.data());

//	cout << "KYBER CipherText Decaps:" << endl;
//	BIO_dump_fp(stdout, (unsigned char*) CipherText.data(),
//			KYBER_CRYPTO_CIPHERTEXTBYTES);
//	cout << "KYBER SharedStr:" << endl;
//	BIO_dump_fp(stdout, ss, KYBER_CRYPTO_BYTES);

	string ssstr((char*) ss, KYBER_CRYPTO_BYTES);

	delete[] ss;

	SharedStr = ssstr;

	return 0;
}

