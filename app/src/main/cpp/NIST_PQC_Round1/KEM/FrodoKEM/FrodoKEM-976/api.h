/********************************************************************************************
* FrodoKEM: Learning with Errors Key Encapsulation
*
* Abstract: parameters and API for FrodoKEM-976
*********************************************************************************************/

#ifndef _API_Frodo976_H_
#define _API_Frodo976_H_


#define FRODOKEM_CRYPTO_SECRETKEYBYTES  31296     // sizeof(s) + FRODOKEM_CRYPTO_PUBLICKEYBYTES + 2*PARAMS_N*PARAMS_NBAR + BYTES_PKHASH
#define FRODOKEM_CRYPTO_PUBLICKEYBYTES  15632     // sizeof(seed_A) + (PARAMS_LOGQ*PARAMS_N*PARAMS_NBAR)/8
#define FRODOKEM_CRYPTO_BYTES              24
#define FRODOKEM_CRYPTO_CIPHERTEXTBYTES 15744     // (PARAMS_LOGQ*PARAMS_N*PARAMS_NBAR)/8 + (PARAMS_LOGQ*PARAMS_NBAR*PARAMS_NBAR)/8  

// Algorithm name
#define FRODOKEM_CRYPTO_ALGNAME "FrodoKEM-976"           


int FrodoKEM_crypto_kem_keypair(unsigned char *pk, unsigned char *sk);
int FrodoKEM_crypto_kem_enc(unsigned char *ct, unsigned char *ss, const unsigned char *pk);
int FrodoKEM_crypto_kem_dec(unsigned char *ss, const unsigned char *ct, const unsigned char *sk);


#endif

