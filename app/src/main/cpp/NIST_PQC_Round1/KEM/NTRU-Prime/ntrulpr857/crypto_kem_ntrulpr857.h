#ifndef crypto_kem_ntrulpr857_H
#define crypto_kem_ntrulpr857_H

#define crypto_kem_ntrulpr857_ref_SECRETKEYBYTES 1463
#define crypto_kem_ntrulpr857_ref_PUBLICKEYBYTES 1184
#define crypto_kem_ntrulpr857_ref_CIPHERTEXTBYTES 1312
#define crypto_kem_ntrulpr857_ref_BYTES 32
 
#ifdef __cplusplus
extern "C" {
#endif
extern int crypto_kem_ntrulpr857_ref_keypair(unsigned char *,unsigned char *);
extern int crypto_kem_ntrulpr857_ref_enc(unsigned char *,unsigned char *,const unsigned char *);
extern int crypto_kem_ntrulpr857_ref_dec(unsigned char *,const unsigned char *,const unsigned char *);
#ifdef __cplusplus
}
#endif

#define crypto_kem_ntrulpr857_keypair crypto_kem_ntrulpr857_ref_keypair
#define crypto_kem_ntrulpr857_enc crypto_kem_ntrulpr857_ref_enc
#define crypto_kem_ntrulpr857_dec crypto_kem_ntrulpr857_ref_dec
#define crypto_kem_ntrulpr857_PUBLICKEYBYTES crypto_kem_ntrulpr857_ref_PUBLICKEYBYTES
#define crypto_kem_ntrulpr857_SECRETKEYBYTES crypto_kem_ntrulpr857_ref_SECRETKEYBYTES
#define crypto_kem_ntrulpr857_BYTES crypto_kem_ntrulpr857_ref_BYTES
#define crypto_kem_ntrulpr857_CIPHERTEXTBYTES crypto_kem_ntrulpr857_ref_CIPHERTEXTBYTES

#endif
