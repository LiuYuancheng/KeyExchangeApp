/*
 * CBikeKem.cpp
 *
 *  Created on: 20 Feb 2020
 *      Author: yiwen
 */

#include "../../generic_service/kems/CNtsKem.h"

#include <libpqch/libpqch.h>

#include <string>

#include "../../generic_service/kems/CKem.h"

using namespace std;

CNtsKem::CNtsKem(string &pubkey, string &privkey) :
		CKem("NTS-KEM", NTS_CRYPTO_ALGNAME, pubkey, privkey)
{

	// TODO Auto-generated constructor stub

}

CNtsKem::~CNtsKem()
{

	// TODO Auto-generated destructor stub
}

int CNtsKem::KeyGen()
{
	unsigned char *p, *q;

	p = new unsigned char(NTS_CRYPTO_PUBLICKEYBYTES);
	q = new unsigned char(NTS_CRYPTO_SECRETKEYBYTES);

	::NTS_crypto_kem_keypair(p, q);

	string pk((char*) p, NTS_CRYPTO_PUBLICKEYBYTES), sk((char*) q,
	NTS_CRYPTO_SECRETKEYBYTES);

	delete p, q;

	PubKey = pk;
	PrivKey = sk;

	return 0;
}

int CNtsKem::Encaps()
{
	unsigned char *ct, *ss;

	ct = new unsigned char[NTS_CRYPTO_CIPHERTEXTBYTES];
	ss = new unsigned char[NTS_CRYPTO_BYTES];

	::NTS_crypto_kem_enc(ct, ss, (unsigned char*) PubKey.data());

//	cout << "NTS CipherText Encaps:" << endl;
//	BIO_dump_fp(stdout, ct, NTS_CRYPTO_CIPHERTEXTBYTES);
//	cout << "NTS SharedStr:" << endl;
//	BIO_dump_fp(stdout, ss, NTS_CRYPTO_BYTES);

	string ctstr((char*) ct, NTS_CRYPTO_CIPHERTEXTBYTES);
	string ssstr((char*) ss, NTS_CRYPTO_BYTES);

	CipherText = ctstr;
	SharedStr = ssstr;

	delete[] ct;
	delete[] ss;

	return 0;
}

int CNtsKem::Decaps()
{
	unsigned char *ss;

	ss = new unsigned char[NTS_CRYPTO_BYTES];

	NTS_crypto_kem_dec(ss, (unsigned char*) CipherText.data(),
			(unsigned char*) PrivKey.data());

//	cout << "NTS CipherText Decaps:" << endl;
//	BIO_dump_fp(stdout, (unsigned char*) CipherText.data(),
//			NTS_CRYPTO_CIPHERTEXTBYTES);
//	cout << "NTS SharedStr:" << endl;
//	BIO_dump_fp(stdout, ss, NTS_CRYPTO_BYTES);

	string ssstr((char*) ss, NTS_CRYPTO_BYTES);

	delete[] ss;

	SharedStr = ssstr;

	return 0;
}

