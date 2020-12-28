#ifndef NTRU_API_H
#define NTRU_API_H

#include "params.h"

#define NTRU_CRYPTO_SECRETKEYBYTES NTRU_SECRETKEYBYTES
#define NTRU_CRYPTO_PUBLICKEYBYTES NTRU_PUBLICKEYBYTES
#define NTRU_CRYPTO_CIPHERTEXTBYTES NTRU_CIPHERTEXTBYTES
#define NTRU_CRYPTO_BYTES NTRU_SHAREDKEYBYTES

#define NTRU_CRYPTO_ALGNAME "NTRU-HRSS701"

int NTRU_crypto_kem_keypair(unsigned char *pk, unsigned char *sk);

int NTRU_crypto_kem_enc(unsigned char *ct, unsigned char *ss, const unsigned char *pk);

int NTRU_crypto_kem_dec(unsigned char *ss, const unsigned char *ct, const unsigned char *sk);


#endif
