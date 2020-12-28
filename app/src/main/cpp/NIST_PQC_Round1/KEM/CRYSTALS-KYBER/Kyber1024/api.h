#ifndef KYBER_API_H
#define KYBER_API_H

#include "params.h"

#define KYBER_CRYPTO_SECRETKEYBYTES  KYBER_SECRETKEYBYTES
#define KYBER_CRYPTO_PUBLICKEYBYTES  KYBER_PUBLICKEYBYTES
#define KYBER_CRYPTO_CIPHERTEXTBYTES KYBER_CIPHERTEXTBYTES
#define KYBER_CRYPTO_BYTES           KYBER_SSBYTES

#if   (KYBER_K == 2)
#define KYBER_CRYPTO_ALGNAME "Kyber512"
#elif (KYBER_K == 3)
#define KYBER_CRYPTO_ALGNAME "Kyber768"
#elif (KYBER_K == 4)
#define KYBER_CRYPTO_ALGNAME "Kyber1024"
#else
#error "KYBER_K must be in {2,3,4}"
#endif

int KYBER_crypto_kem_keypair(unsigned char *pk, unsigned char *sk);

int KYBER_crypto_kem_enc(unsigned char *ct, unsigned char *ss, const unsigned char *pk);

int KYBER_crypto_kem_dec(unsigned char *ss, const unsigned char *ct, const unsigned char *sk);


#endif
