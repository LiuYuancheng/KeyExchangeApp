/*
 * CBikeKem.cpp
 *
 *  Created on: 20 Feb 2020
 *      Author: yiwen
 */

#include "../../generic_service/kems/CNtruKem.h"

#include <libpqch/libpqch.h>

#include <string>

#include "../../generic_service/kems/CKem.h"

using namespace std;

CNtruKem::CNtruKem(string &pubkey, string &privkey) :
		CKem("NTRU-KEM", NTRU_CRYPTO_ALGNAME, pubkey, privkey)
{

	// TODO Auto-generated constructor stub

}

CNtruKem::~CNtruKem()
{

	// TODO Auto-generated destructor stub
}

int CNtruKem::KeyGen()
{
	unsigned char *p, *q;

	p = new unsigned char(NTRU_CRYPTO_PUBLICKEYBYTES);
	q = new unsigned char(NTRU_CRYPTO_SECRETKEYBYTES);

	::NTRU_crypto_kem_keypair(p, q);

	string pk((char*) p, NTRU_CRYPTO_PUBLICKEYBYTES), sk((char*) q,
	NTRU_CRYPTO_SECRETKEYBYTES);

	delete p, q;

	PubKey = pk;
	PrivKey = sk;

	return 0;
}

int CNtruKem::Encaps()
{
	unsigned char *ct, *ss;

	ct = new unsigned char[NTRU_CRYPTO_CIPHERTEXTBYTES];
	ss = new unsigned char[NTRU_CRYPTO_BYTES];

	::NTRU_crypto_kem_enc(ct, ss, (unsigned char*) PubKey.data());

//	cout << "NTRU CipherText Encaps:" << endl;
//	BIO_dump_fp(stdout, ct, NTRU_CRYPTO_CIPHERTEXTBYTES);
//	cout << "NTRU SharedStr:" << endl;
//	BIO_dump_fp(stdout, ss, NTRU_CRYPTO_BYTES);

	string ctstr((char*) ct, NTRU_CRYPTO_CIPHERTEXTBYTES);
	string ssstr((char*) ss, NTRU_CRYPTO_BYTES);

	CipherText = ctstr;
	SharedStr = ssstr;

	delete[] ct;
	delete[] ss;

	return 0;
}

int CNtruKem::Decaps()
{
	unsigned char *ss;

	ss = new unsigned char[NTRU_CRYPTO_BYTES];

	NTRU_crypto_kem_dec(ss, (unsigned char*) CipherText.data(),
			(unsigned char*) PrivKey.data());

//	cout << "NTRU CipherText Decaps:" << endl;
//	BIO_dump_fp(stdout, (unsigned char*) CipherText.data(),
//			NTRU_CRYPTO_CIPHERTEXTBYTES);
//	cout << "NTRU SharedStr:" << endl;
//	BIO_dump_fp(stdout, ss, NTRU_CRYPTO_BYTES);

	string ssstr((char*) ss, NTRU_CRYPTO_BYTES);

	delete[] ss;

	SharedStr = ssstr;

	return 0;
}

