//
//  api.h
//
//  Created by Bassham, Lawrence E (Fed) on 9/6/17.
//  Copyright © 2017 Bassham, Lawrence E (Fed). All rights reserved.
//


//   This is a sample 'api.h' for use 'sign.c'

#ifndef SABER_api_h
#define SABER_api_h

// Available algorithms for different security levels
//#define LightSaber 1
//#define Saber 2
#define FireSaber 3

// Change the algorithm name 
//#define SABER_TYPE LightSaber
//#define SABER_TYPE Saber
#define SABER_TYPE FireSaber

//  Set these three values apropriately for your algorithm
#if SABER_TYPE == LightSaber
	#define SABER_CRYPTO_ALGNAME "LightSaber"
	#define SABER_CRYPTO_SECRETKEYBYTES 1568
	#define SABER_CRYPTO_PUBLICKEYBYTES (2*320+32)
	#define SABER_CRYPTO_BYTES 32
	#define SABER_CRYPTO_CIPHERTEXTBYTES 736
	#define Saber_type 1
#elif SABER_TYPE == Saber
	#define SABER_CRYPTO_ALGNAME "Saber"
	#define SABER_CRYPTO_SECRETKEYBYTES 2304
	#define SABER_CRYPTO_PUBLICKEYBYTES (3*320+32)
	#define SABER_CRYPTO_BYTES 32
	#define SABER_CRYPTO_CIPHERTEXTBYTES 1088
	#define Saber_type 2
#elif SABER_TYPE == FireSaber
	#define SABER_CRYPTO_ALGNAME "FireSaber"
	#define SABER_CRYPTO_SECRETKEYBYTES 3040
	#define SABER_CRYPTO_PUBLICKEYBYTES (4*320+32)
	#define SABER_CRYPTO_BYTES 32
	#define SABER_CRYPTO_CIPHERTEXTBYTES 1472
	#define Saber_type 3
#endif


int SABER_crypto_kem_keypair(unsigned char *pk, unsigned char *sk);
int SABER_crypto_kem_enc(unsigned char *ct, unsigned char *ss, const unsigned char *pk);
int SABER_crypto_kem_dec(unsigned char *ss, const unsigned char *ct, const unsigned char *sk);

#endif /* api_h */
