#ifndef NEWHOPE_API_H
#define NEWHOPE_API_H

#include "params.h"

#define NEWHOPE_CRYPTO_SECRETKEYBYTES  NEWHOPE_CPAKEM_SECRETKEYBYTES
#define NEWHOPE_CRYPTO_PUBLICKEYBYTES  NEWHOPE_CPAKEM_PUBLICKEYBYTES
#define NEWHOPE_CRYPTO_CIPHERTEXTBYTES NEWHOPE_CPAKEM_CIPHERTEXTBYTES
#define NEWHOPE_CRYPTO_BYTES           NEWHOPE_SYMBYTES

#if   (NEWHOPE_N == 512)
#define NEWHOPE_CRYPTO_ALGNAME "NewHope-512-CPA"
#elif (NEWHOPE_N == 1024)
#define NEWHOPE_CRYPTO_ALGNAME "NewHope-1024-CPA"
#else
#error "NEWHOPE_N must be either 512 or 1024"
#endif

int NewHope_crypto_kem_keypair(unsigned char *pk, unsigned char *sk);

int NewHope_crypto_kem_enc(unsigned char *ct, unsigned char *ss, const unsigned char *pk);

int NewHope_crypto_kem_dec(unsigned char *ss, const unsigned char *ct, const unsigned char *sk);

#endif
