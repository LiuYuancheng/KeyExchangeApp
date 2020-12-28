#ifndef THREEBEARS_api_h
#define THREEBEARS_api_h

#define THREEBEARS_CRYPTO_SECRETKEYBYTES 40
#define THREEBEARS_CRYPTO_PUBLICKEYBYTES 1194
#define THREEBEARS_CRYPTO_BYTES 32
#define THREEBEARS_CRYPTO_CIPHERTEXTBYTES 1307
#define THREEBEARS_CRYPTO_ALGNAME "MamaBear"

int ThreeBears_crypto_kem_keypair(
    unsigned char *pk,
    unsigned char *sk
);

int ThreeBears_crypto_kem_enc(
    unsigned char *ct,
    unsigned char *ss,
    const unsigned char *pk
);

int ThreeBears_crypto_kem_dec(
    unsigned char *ss,
    const unsigned char *ct,
    const unsigned char *sk
);

#endif /* api_h */

