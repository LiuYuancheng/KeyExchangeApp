/*
 * CBikeKem.cpp
 *
 *  Created on: 20 Feb 2020
 *      Author: yiwen
 */

#include "../../generic_service/kems/CRolloKem.h"

#include <libpqch/libpqch.h>

#include <string>

#include "../../generic_service/kems/CKem.h"

using namespace std;

CRolloKem::CRolloKem(string &pubkey, string &privkey) :
		CKem("ROLLO-KEM", ROLLO_CRYPTO_ALGNAME, pubkey, privkey)
{

	// TODO Auto-generated constructor stub

}

CRolloKem::~CRolloKem()
{

	// TODO Auto-generated destructor stub
}

int CRolloKem::KeyGen()
{
	unsigned char *p, *q;

	p = new unsigned char(ROLLO_CRYPTO_PUBLICKEYBYTES);
	q = new unsigned char(ROLLO_CRYPTO_SECRETKEYBYTES);

	::ROLLO_crypto_kem_keypair(p, q);

	string pk((char*) p, ROLLO_CRYPTO_PUBLICKEYBYTES), sk((char*) q,
	ROLLO_CRYPTO_SECRETKEYBYTES);

	delete p, q;

	PubKey = pk;
	PrivKey = sk;

	return 0;
}

int CRolloKem::Encaps()
{
	unsigned char *ct, *ss;

	ct = new unsigned char[ROLLO_CRYPTO_CIPHERTEXTBYTES];
	ss = new unsigned char[ROLLO_CRYPTO_BYTES];

	::ROLLO_crypto_kem_enc(ct, ss, (unsigned char*) PubKey.data());

//	cout << "ROLLO CipherText Encaps:" << endl;
//	BIO_dump_fp(stdout, ct, ROLLO_CRYPTO_CIPHERTEXTBYTES);
//	cout << "ROLLO SharedStr:" << endl;
//	BIO_dump_fp(stdout, ss, ROLLO_CRYPTO_BYTES);

	string ctstr((char*) ct, ROLLO_CRYPTO_CIPHERTEXTBYTES);
	string ssstr((char*) ss, ROLLO_CRYPTO_BYTES);

	CipherText = ctstr;
	SharedStr = ssstr;

	delete[] ct;
	delete[] ss;

	return 0;
}

int CRolloKem::Decaps()
{
	unsigned char *ss;

	ss = new unsigned char[ROLLO_CRYPTO_BYTES];

	ROLLO_crypto_kem_dec(ss, (unsigned char*) CipherText.data(),
			(unsigned char*) PrivKey.data());

//	cout << "ROLLO CipherText Decaps:" << endl;
//	BIO_dump_fp(stdout, (unsigned char*) CipherText.data(),
//			ROLLO_CRYPTO_CIPHERTEXTBYTES);
//	cout << "ROLLO SharedStr:" << endl;
//	BIO_dump_fp(stdout, ss, ROLLO_CRYPTO_BYTES);

	string ssstr((char*) ss, ROLLO_CRYPTO_BYTES);

	delete[] ss;

	SharedStr = ssstr;

	return 0;
}

