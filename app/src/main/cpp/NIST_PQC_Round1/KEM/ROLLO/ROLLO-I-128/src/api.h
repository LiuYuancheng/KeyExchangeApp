/**
 * \file api.h
 * \brief NIST KEM API used by the LAKE scheme
 */


#ifndef ROLLO_API_H
#define ROLLO_API_H


#define ROLLO_CRYPTO_ALGNAME "ROLLO-I-128"

#define ROLLO_CRYPTO_SECRETKEYBYTES 40
#define ROLLO_CRYPTO_PUBLICKEYBYTES 465
#define ROLLO_CRYPTO_BYTES 64
#define ROLLO_CRYPTO_CIPHERTEXTBYTES 465


int ROLLO_crypto_kem_keypair(unsigned char* pk, unsigned char* sk);
int ROLLO_crypto_kem_enc(unsigned char* ct, unsigned char* ss, const unsigned char* pk);
int ROLLO_crypto_kem_dec(unsigned char* ss, const unsigned char* ct, const unsigned char* sk);

#endif

