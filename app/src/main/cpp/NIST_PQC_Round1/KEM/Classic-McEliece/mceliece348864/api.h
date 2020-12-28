#ifndef __CM_H__
#define __CM_H__
#define CM_CRYPTO_PUBLICKEYBYTES 261120
#define CM_CRYPTO_SECRETKEYBYTES 6452
#define CM_CRYPTO_CIPHERTEXTBYTES 128
#define CM_CRYPTO_BYTES 32

#define CM_CRYPTO_ALGNAME  "mceliece348864"


int CM_crypto_kem_keypair(unsigned char *,unsigned char *);
int CM_crypto_kem_enc(unsigned char *,unsigned char *,const unsigned char *);
int CM_crypto_kem_dec(unsigned char *,const unsigned char *,const unsigned char *);

#endif
