/**
 * \file api.h
 * \brief NIST KEM API used by the RQC_KEM IND-CCA2 scheme
 */


#ifndef RQC_API_H
#define RQC_API_H

#define RQC_CRYPTO_ALGNAME "RQC-128"

#define RQC_CRYPTO_SECRETKEYBYTES 893
#define RQC_CRYPTO_PUBLICKEYBYTES 853
#define RQC_CRYPTO_BYTES 64
#define RQC_CRYPTO_CIPHERTEXTBYTES 1690

// As a technicality, the public key is appended to the secret key in order to respect the NIST API. 
// Without this constraint, CRYPTO_SECRETKEYBYTES would be defined as 40


int RQC_crypto_kem_keypair(unsigned char* pk, unsigned char* sk);
int RQC_crypto_kem_enc(unsigned char* ct, unsigned char* ss, const unsigned char* pk);
int RQC_crypto_kem_dec(unsigned char* ss, const unsigned char* ct, const unsigned char* sk);

#endif

