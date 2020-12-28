

#ifndef __NTRUPRIME_API_H__
#define __NTRUPRIME_API_H__
#define NTRUPRIME_CRYPTO_SECRETKEYBYTES 1125
#define NTRUPRIME_CRYPTO_PUBLICKEYBYTES 897
#define NTRUPRIME_CRYPTO_CIPHERTEXTBYTES 1025
#define NTRUPRIME_CRYPTO_BYTES 32
#define NTRUPRIME_CRYPTO_ALGNAME  "ntrulpr653"


int NTRUPrime_crypto_kem_keypair(unsigned char *pk,unsigned char *sk);

int NTRUPrime_crypto_kem_enc(unsigned char *c,unsigned char *k,const unsigned char *pk);

int NTRUPrime_crypto_kem_dec(unsigned char *k,const unsigned char *c,const unsigned char *sk);

#endif
