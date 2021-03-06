#ifndef NTRUPRIME_crypto_kem_H
#define NTRUPRIME_crypto_kem_H

#include "crypto_kem_sntrup857.h"

#define NTRUPrime_crypto_kem_keypair crypto_kem_sntrup857_keypair
#define NTRUPrime_crypto_kem_enc crypto_kem_sntrup857_enc
#define NTRUPrime_crypto_kem_dec crypto_kem_sntrup857_dec
#define NTRUPrime_crypto_kem_PUBLICKEYBYTES crypto_kem_sntrup857_PUBLICKEYBYTES
#define NTRUPrime_crypto_kem_SECRETKEYBYTES crypto_kem_sntrup857_SECRETKEYBYTES
#define NTRUPrime_crypto_kem_BYTES crypto_kem_sntrup857_BYTES
#define NTRUPrime_crypto_kem_CIPHERTEXTBYTES crypto_kem_sntrup857_CIPHERTEXTBYTES
#define NTRUPRIME_CRYPTO_ALGNAME "sntrup857"

#endif
