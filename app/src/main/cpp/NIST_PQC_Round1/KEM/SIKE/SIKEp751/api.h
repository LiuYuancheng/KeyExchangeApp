//
//  api.h
//
//  Created by Bassham, Lawrence E (Fed) on 9/6/17.
//  Copyright © 2017 Bassham, Lawrence E (Fed). All rights reserved.
//


//   This is a sample 'api.h' for use 'sign.c'

#ifndef SIKE_api_h
#define SIKE_api_h

#define SIKE_CRYPTO_SECRETKEYBYTES     644    // MSG_BYTES + SECRETKEY_B_BYTES + CRYPTO_PUBLICKEYBYTES bytes
#define SIKE_CRYPTO_PUBLICKEYBYTES     564
#define SIKE_CRYPTO_BYTES               32
#define SIKE_CRYPTO_CIPHERTEXTBYTES    596    // CRYPTO_PUBLICKEYBYTES + MSG_BYTES bytes

// Algorithm name
#define SIKE_CRYPTO_ALGNAME "SIKEp751"

// SIKE's key generation
// It produces a private key sk and computes the public key pk.
// Outputs: secret key sk (CRYPTO_SECRETKEYBYTES = 644 bytes)
//          public key pk (CRYPTO_PUBLICKEYBYTES = 564 bytes)
int SIKE_crypto_kem_keypair(unsigned char *pk, unsigned char *sk);

// SIKE's encapsulation
// Input:   public key pk         (CRYPTO_PUBLICKEYBYTES = 564 bytes)
// Outputs: shared secret ss      (CRYPTO_BYTES = 32 bytes)
//          ciphertext message ct (CRYPTO_CIPHERTEXTBYTES = 596 bytes)
int SIKE_crypto_kem_enc(unsigned char *ct, unsigned char *ss, const unsigned char *pk);

// SIKE's decapsulation
// Input:   secret key sk         (CRYPTO_SECRETKEYBYTES = 644 bytes)
//          ciphertext message ct (CRYPTO_CIPHERTEXTBYTES = 596 bytes)
// Outputs: shared secret ss      (CRYPTO_BYTES = 32 bytes)
int SIKE_crypto_kem_dec(unsigned char *ss, const unsigned char *ct, const unsigned char *sk);

#endif /* api_h */
