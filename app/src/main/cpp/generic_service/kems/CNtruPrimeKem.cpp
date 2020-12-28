/*
 * CBikeKem.cpp
 *
 *  Created on: 20 Feb 2020
 *      Author: yiwen
 */

#include "../../generic_service/kems/CNtruPrimeKem.h"

#include <libpqch/libpqch.h>

#include <string>

#include "../../generic_service/kems/CKem.h"

using namespace std;

CNtruPrimeKem::CNtruPrimeKem(string &pubkey, string &privkey) :
		CKem("NTRUPRIME-KEM", NTRUPRIME_CRYPTO_ALGNAME, pubkey, privkey)
{

	// TODO Auto-generated constructor stub

}

CNtruPrimeKem::~CNtruPrimeKem()
{

	// TODO Auto-generated destructor stub
}

int CNtruPrimeKem::KeyGen()
{
	unsigned char *p, *q;

	p = new unsigned char(NTRUPRIME_CRYPTO_PUBLICKEYBYTES);
	q = new unsigned char(NTRUPRIME_CRYPTO_SECRETKEYBYTES);

	::NTRUPrime_crypto_kem_keypair(p, q);

	string pk((char*) p, NTRUPRIME_CRYPTO_PUBLICKEYBYTES), sk((char*) q,
	NTRUPRIME_CRYPTO_SECRETKEYBYTES);

	delete p, q;

	PubKey = pk;
	PrivKey = sk;

	return 0;
}

int CNtruPrimeKem::Encaps()
{
	unsigned char *ct, *ss;

	ct = new unsigned char[NTRUPRIME_CRYPTO_CIPHERTEXTBYTES];
	ss = new unsigned char[NTRUPRIME_CRYPTO_BYTES];

	::NTRUPrime_crypto_kem_enc(ct, ss, (unsigned char*) PubKey.data());

//	cout << "NTRUPRIME CipherText Encaps:" << endl;
//	BIO_dump_fp(stdout, ct, NTRUPRIME_CRYPTO_CIPHERTEXTBYTES);
//	cout << "NTRUPRIME SharedStr:" << endl;
//	BIO_dump_fp(stdout, ss, NTRUPRIME_CRYPTO_BYTES);

	string ctstr((char*) ct, NTRUPRIME_CRYPTO_CIPHERTEXTBYTES);
	string ssstr((char*) ss, NTRUPRIME_CRYPTO_BYTES);

	CipherText = ctstr;
	SharedStr = ssstr;

	delete[] ct;
	delete[] ss;

	return 0;
}

int CNtruPrimeKem::Decaps()
{
	unsigned char *ss;

	ss = new unsigned char[NTRUPRIME_CRYPTO_BYTES];

	NTRUPrime_crypto_kem_dec(ss, (unsigned char*) CipherText.data(),
			(unsigned char*) PrivKey.data());

//	cout << "NTRUPRIME CipherText Decaps:" << endl;
//	BIO_dump_fp(stdout, (unsigned char*) CipherText.data(),
//	NTRUPRIME_CRYPTO_CIPHERTEXTBYTES);
//	cout << "NTRUPRIME SharedStr:" << endl;
//	BIO_dump_fp(stdout, ss, NTRUPRIME_CRYPTO_BYTES);

	string ssstr((char*) ss, NTRUPRIME_CRYPTO_BYTES);

	delete[] ss;

	SharedStr = ssstr;

	return 0;
}

