/*
 * CBikeKem.cpp
 *
 *  Created on: 20 Feb 2020
 *      Author: yiwen
 */

#include "../../generic_service/kems/CLedaKem.h"

#include <libpqch/libpqch.h>

#include <string>

#include "../../generic_service/kems/CKem.h"

using namespace std;

CLedaKem::CLedaKem(string &pubkey, string &privkey) :
		CKem("LEDACRYPT-KEM", LEDACRYPT_CRYPTO_ALGNAME, pubkey, privkey)
{

	// TODO Auto-generated constructor stub

}

CLedaKem::~CLedaKem()
{

	// TODO Auto-generated destructor stub
}

int CLedaKem::KeyGen()
{
	unsigned char *p, *q;

	p = new unsigned char(LEDACRYPT_CRYPTO_PUBLICKEYBYTES);
	q = new unsigned char(LEDACRYPT_CRYPTO_SECRETKEYBYTES);

	::LEDAcrypt_crypto_kem_keypair(p, q);

	string pk((char*) p, LEDACRYPT_CRYPTO_PUBLICKEYBYTES), sk((char*) q,
	LEDACRYPT_CRYPTO_SECRETKEYBYTES);

	delete p, q;

	PubKey = pk;
	PrivKey = sk;

	return 0;
}

int CLedaKem::Encaps()
{
	unsigned char *ct, *ss;

	ct = new unsigned char[LEDACRYPT_CRYPTO_CIPHERTEXTBYTES];
	ss = new unsigned char[LEDACRYPT_CRYPTO_BYTES];

	::LEDAcrypt_crypto_kem_enc(ct, ss, (unsigned char*) PubKey.data());

//	cout << "LEDACRYPT CipherText Encaps:" << endl;
//	BIO_dump_fp(stdout, ct, LEDACRYPT_CRYPTO_CIPHERTEXTBYTES);
//	cout << "LEDACRYPT SharedStr:" << endl;
//	BIO_dump_fp(stdout, ss, LEDACRYPT_CRYPTO_BYTES);

	string ctstr((char*) ct, LEDACRYPT_CRYPTO_CIPHERTEXTBYTES);
	string ssstr((char*) ss, LEDACRYPT_CRYPTO_BYTES);

	CipherText = ctstr;
	SharedStr = ssstr;

	delete[] ct;
	delete[] ss;

	return 0;
}

int CLedaKem::Decaps()
{
	unsigned char *ss;

	ss = new unsigned char[LEDACRYPT_CRYPTO_BYTES];

	::LEDAcrypt_crypto_kem_dec(ss, (unsigned char*) CipherText.data(),
			(unsigned char*) PrivKey.data());

//	cout << "LEDACRYPT CipherText Decaps:" << endl;
//	BIO_dump_fp(stdout, (unsigned char*) CipherText.data(),
//	LEDACRYPT_CRYPTO_CIPHERTEXTBYTES);
//	cout << "LEDACRYPT SharedStr:" << endl;
//	BIO_dump_fp(stdout, ss, LEDACRYPT_CRYPTO_BYTES);

	string ssstr((char*) ss, LEDACRYPT_CRYPTO_BYTES);

	delete[] ss;

	SharedStr = ssstr;

	return 0;
}

