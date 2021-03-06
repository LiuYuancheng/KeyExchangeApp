/**
 * \file api.h
 * \brief NIST KEM API used by the HQC_KEM IND-CCA2 scheme
 */

#ifndef HQC_API_H
#define HC_API_H

#define HQC_CRYPTO_ALGNAME                      "HQC_256_2"

#define HQC_CRYPTO_SECRETKEYBYTES               8543
#define HQC_CRYPTO_PUBLICKEYBYTES               8503
#define HQC_CRYPTO_BYTES                        64
#define HQC_CRYPTO_CIPHERTEXTBYTES              16985

// As a technicality, the public key is appended to the secret key in order to respect the NIST API. 
// Without this constraint, HQC_CRYPTO_SECRETKEYBYTES would be defined as 32

int HQC_crypto_kem_keypair(unsigned char* pk, unsigned char* sk);
int HQC_crypto_kem_enc(unsigned char* ct, unsigned char* ss, const unsigned char* pk);
int HQC_crypto_kem_dec(unsigned char* ss, const unsigned char* ct, const unsigned char* sk);
  
#endif
