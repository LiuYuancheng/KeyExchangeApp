/*
 * CKeyPairSouce.h
 *
 *  Created on: 21 Feb 2020
 *      Author: yiwen
 */

#ifndef CPP_CKEMKEYPAIRSOUCE_H_
#define CPP_CKEMKEYPAIRSOUCE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mbedtls/base64.h>
#include "hybrid_kem.h"

class CKEMKeyPairSouce
{
	char KeyDir[100];
	char Id[20];
public:
	CKEMKeyPairSouce();
	virtual ~CKEMKeyPairSouce();

	static int RSAKeyPair(unsigned char *pk, unsigned char *sk)
	{
		FILE *fp;
		size_t len, olen;
		char sk_fn[256] =
		{ 0 }, pk_dir[256] =
		{ 0 };
		unsigned char *base64, *key;

		fp = fopen(sk_fn, "r");
		if (fp == 0)
			return -2;
		fseek(fp, 0, SEEK_END);
		len = ftell(fp);

		base64 = (unsigned char*) malloc(len * 2);
		if (base64 == NULL)
		{
			fclose(fp);
			return -2;
		}
		rewind(fp);
		fread(base64, 1, len, fp);
		fclose(fp);

		if (mbedtls_base64_decode(base64 + len, len, &olen, base64, len))
			return -3;

		if (olen == RSA_CRYPTO_PUBLICKEYBYTES)
		{
			memcpy(pk, base64 + len, RSA_CRYPTO_PUBLICKEYBYTES);
		}
		free(base64);
		return 0;
	}
};

#endif /* CPP_CKEMKEYPAIRSOUCE_H_ */
