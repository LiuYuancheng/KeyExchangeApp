#ifndef crypto_kem_sntrup653_H
#define crypto_kem_sntrup653_H

#define crypto_kem_sntrup653_ref_SECRETKEYBYTES 1518
#define crypto_kem_sntrup653_ref_PUBLICKEYBYTES 994
#define crypto_kem_sntrup653_ref_CIPHERTEXTBYTES 897
#define crypto_kem_sntrup653_ref_BYTES 32
 
#ifdef __cplusplus
extern "C" {
#endif
extern int crypto_kem_sntrup653_ref_keypair(unsigned char *,unsigned char *);
extern int crypto_kem_sntrup653_ref_enc(unsigned char *,unsigned char *,const unsigned char *);
extern int crypto_kem_sntrup653_ref_dec(unsigned char *,const unsigned char *,const unsigned char *);
#ifdef __cplusplus
}
#endif

#define crypto_kem_sntrup653_keypair crypto_kem_sntrup653_ref_keypair
#define crypto_kem_sntrup653_enc crypto_kem_sntrup653_ref_enc
#define crypto_kem_sntrup653_dec crypto_kem_sntrup653_ref_dec
#define crypto_kem_sntrup653_PUBLICKEYBYTES crypto_kem_sntrup653_ref_PUBLICKEYBYTES
#define crypto_kem_sntrup653_SECRETKEYBYTES crypto_kem_sntrup653_ref_SECRETKEYBYTES
#define crypto_kem_sntrup653_BYTES crypto_kem_sntrup653_ref_BYTES
#define crypto_kem_sntrup653_CIPHERTEXTBYTES crypto_kem_sntrup653_ref_CIPHERTEXTBYTES

#endif
