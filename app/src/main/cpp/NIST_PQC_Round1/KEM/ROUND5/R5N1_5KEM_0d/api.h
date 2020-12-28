/*
 * Copyright (c) 2019, Koninklijke Philips N.V.
 */

/**
 * @file
 * Declaration of the NIST API functions and setting of the NIST API
 * algorithm parameters: `ROUND5_CRYPTO_SECRETKEYBYTES`, `ROUND5_CRYPTO_PUBLICKEYBYTES`,
 * `ROUND5_CRYPTO_BYTES`, and `ROUND5_CRYPTO_CIPHERBYTES`.
 */

#ifndef ROUND5_API_H_
#define ROUND5_API_H_

#define ROUND5_CRYPTO_SECRETKEYBYTES 32
#define ROUND5_CRYPTO_PUBLICKEYBYTES 14264
#define ROUND5_CRYPTO_BYTES 32
#define ROUND5_CRYPTO_CIPHERTEXTBYTES 14288
#define ROUND5_CRYPTO_ALGNAME "R5N1_5KEM_0d"

#ifdef __cplusplus
extern "C" {
#endif

    /**
     * Generates a CPA KEM key pair.
     *
     * @param[out] pk public key
     * @param[out] sk secret key
     * @return __0__ in case of success
     */
    int ROUND5_crypto_kem_keypair(unsigned char *pk, unsigned char *sk);

    /**
     * CPA KEM encapsulate.
     *
     * @param[out] ct    key encapsulation message (ciphertext)
     * @param[out] k     shared secret
     * @param[in]  pk    public key with which the message is encapsulated
     * @return __0__ in case of success
     */
    int ROUND5_crypto_kem_enc(unsigned char *ct, unsigned char *k, const unsigned char *pk);

    /**
     * CPA KEM de-capsulate.
     *
     * @param[out] k     shared secret
     * @param[in]  ct    key encapsulation message (ciphertext)
     * @param[in]  sk    secret key with which the message is to be de-capsulated
     * @return __0__ in case of success
     */
    int ROUND5_crypto_kem_dec(unsigned char *k, const unsigned char *ct, const unsigned char *sk);

#ifdef __cplusplus
}
#endif

#endif /* _API_H_ */
