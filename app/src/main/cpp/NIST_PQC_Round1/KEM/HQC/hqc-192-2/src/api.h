/**
 * \file api.h
 * \brief NIST KEM API used by the HQC_KEM IND-CCA2 scheme
 */

#ifndef HQC_API_H
#define HQC_API_H

#define HQC_CRYPTO_ALGNAME                      "HQC_192_2"

#define HQC_CRYPTO_SECRETKEYBYTES               5924
#define HQC_CRYPTO_PUBLICKEYBYTES               5884
#define HQC_CRYPTO_BYTES                        64
#define HQC_CRYPTO_CIPHERTEXTBYTES              11749

// As a technicality, the public key is appended to the secret key in order to respect the NIST API. 
// Without this constraint, HQC_CRYPTO_SECRETKEYBYTES would be defined as 32

int HQC_crypto_kem_keypair(unsigned char* pk, unsigned char* sk);
int HQC_crypto_kem_enc(unsigned char* ct, unsigned char* ss, const unsigned char* pk);
int HQC_crypto_kem_dec(unsigned char* ss, const unsigned char* ct, const unsigned char* sk);
  
#endif
