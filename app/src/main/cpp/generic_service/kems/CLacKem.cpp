/*
 * CBikeKem.cpp
 *
 *  Created on: 20 Feb 2020
 *      Author: yiwen
 */

#include "../../generic_service/kems/CLacKem.h"

#include <libpqch/libpqch.h>

#include <string>

#include "../../generic_service/kems/CKem.h"

using namespace std;

CLacKem::CLacKem(string &pubkey, string &privkey) :
		CKem("LAC-KEM", LAC_CRYPTO_ALGNAME, pubkey, privkey)
{

	// TODO Auto-generated constructor stub

}

CLacKem::~CLacKem()
{

	// TODO Auto-generated destructor stub
}

int CLacKem::KeyGen()
{
	unsigned char *p, *q;

	p = new unsigned char(LAC_CRYPTO_PUBLICKEYBYTES);
	q = new unsigned char(LAC_CRYPTO_SECRETKEYBYTES);

	::LAC_crypto_kem_keypair(p, q);

	string pk((char*) p, LAC_CRYPTO_PUBLICKEYBYTES), sk((char*) q,
	LAC_CRYPTO_SECRETKEYBYTES);

	delete p, q;

	PubKey = pk;
	PrivKey = sk;

	return 0;
}

int CLacKem::Encaps()
{
	unsigned char *ct, *ss;

	ct = new unsigned char[LAC_CRYPTO_CIPHERTEXTBYTES];
	ss = new unsigned char[LAC_CRYPTO_BYTES];

	::LAC_crypto_kem_enc(ct, ss, (unsigned char*) PubKey.data());

//	cout << "LAC CipherText Encaps:" << endl;
//	BIO_dump_fp(stdout, ct, LAC_CRYPTO_CIPHERTEXTBYTES);
//	cout << "LAC SharedStr:" << endl;
//	BIO_dump_fp(stdout, ss, LAC_CRYPTO_BYTES);

	string ctstr((char*) ct, LAC_CRYPTO_CIPHERTEXTBYTES);
	string ssstr((char*) ss, LAC_CRYPTO_BYTES);

	CipherText = ctstr;
	SharedStr = ssstr;

	delete[] ct;
	delete[] ss;

	return 0;
}

int CLacKem::Decaps()
{
	unsigned char *ss;

	ss = new unsigned char[LAC_CRYPTO_BYTES];

	LAC_crypto_kem_dec(ss, (unsigned char*) CipherText.data(),
			(unsigned char*) PrivKey.data());

//	cout << "LAC CipherText Decaps:" << endl;
//	BIO_dump_fp(stdout, (unsigned char*) CipherText.data(),
//			LAC_CRYPTO_CIPHERTEXTBYTES);
//	cout << "LAC SharedStr:" << endl;
//	BIO_dump_fp(stdout, ss, LAC_CRYPTO_BYTES);

	string ssstr((char*) ss, LAC_CRYPTO_BYTES);

	delete[] ss;

	SharedStr = ssstr;

	return 0;
}

