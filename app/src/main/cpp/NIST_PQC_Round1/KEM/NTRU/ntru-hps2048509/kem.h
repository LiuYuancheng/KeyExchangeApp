#ifndef NTRUKEM_H
#define NTRUKEM_H

int NTRU_crypto_kem_keypair(unsigned char *pk, unsigned char *sk);

int NTRU_crypto_kem_enc(unsigned char *c, unsigned char *k, const unsigned char *pk);

int NTRU_crypto_kem_dec(unsigned char *k, const unsigned char *c, const unsigned char *sk);

#endif
