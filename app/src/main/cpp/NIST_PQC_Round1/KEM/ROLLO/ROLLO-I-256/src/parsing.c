/** 
 * \file parsing.cpp
 * \brief Implementation of parsing.h
 */

#include "string.h"
#include "parameters.h"
#include "parsing.h"
#include "ffi/ffi_vec.h"


/**
 * @fn         void lake_secret_key_to_string(unsigned char* sk, const unsigned char* seed)
 *
 * @brief      This function parses a secret key into a string
 *
 *             The secret key is composed of the seed used to generate the secret key
 *
 * @param[out] sk    String containing the secret key
 * @param[in]  seed  Seed used to generate the secret key
 */
void lake_secret_key_to_string(unsigned char* sk, const unsigned char* seed) {
  memcpy(sk, seed, SEEDEXPANDER_SEED_BYTES);
}



/**
 * @fn         void lake_secret_key_from_string(ROLLO_ffi_vec& x, ROLLO_ffi_vec& y, ROLLO_ffi_vec& support_w, const unsigned char* sk)
 *
 * @brief      This function parses a secret key from a string
 *
 *             The secret key is composed of the seed used to generate vectors
 *             <b>x</b> and <b>y</b>.
 *
 * @param[in]  sk        The secret key
 * @param[in]  skString  The sk string
 */
void lake_secret_key_from_string(secretKey &sk, const unsigned char* skString) {
  unsigned char sk_seed[SEEDEXPANDER_SEED_BYTES];
  memcpy(sk_seed, skString, SEEDEXPANDER_SEED_BYTES);
  AES_XOF_struct* sk_seedexpander = (AES_XOF_struct*) malloc(sizeof(AES_XOF_struct));
  seedexpander_init(sk_seedexpander, sk_seed, sk_seed + 32, SEEDEXPANDER_MAX_LENGTH);

  //Computes the support of the parity check matrix
  ROLLO_ffi_vec_set_random_full_rank_using_seedexpander(sk.F, ROLLO_PARAM_D, sk_seedexpander);
  //Computes two polynomials A and B defining the two cyclic parts of the parity check matrix
  //These are parts of the secret key. See the parsing part of the supporting documentation for more details

  ROLLO_ffi_vec_set_random_from_support_using_seedexpander(sk.x, ROLLO_PARAM_N, sk.F, ROLLO_PARAM_D, sk_seedexpander);
  ROLLO_ffi_vec_set_random_from_support_using_seedexpander(sk.y, ROLLO_PARAM_N, sk.F, ROLLO_PARAM_D, sk_seedexpander);

  free(sk_seedexpander);
}



/**
 * @fn         void lake_public_key_to_string(unsigned char* pk, const ROLLO_ffi_vec& s, const unsigned char* seed)
 *
 * @brief      This function parses a public key into a string
 *
 * @param      pkString  The pk string
 * @param[out] pk        The public key
 */
void lake_public_key_to_string(unsigned char* pkString, publicKey pk) {
  ROLLO_ffi_vec_to_string(pkString, pk.h, ROLLO_PARAM_N);
}



/**
 * @fn         void lake_public_key_from_string(ROLLO_ffi_vec& h, ROLLO_ffi_vec& s, const unsigned char* pk)
 *
 * @brief      This function parses a public key from a string
 *
 * @param[in]  pk        The public key
 * @param[in]  pkString  The pk string
 */
void lake_public_key_from_string(publicKey &pk, const unsigned char *pkString) {
  ROLLO_ffi_vec_from_string(pk.h, ROLLO_PARAM_N, pkString);
}



/**
 * @fn         void lake_ciphertext_to_string(unsigned char* ct, const ROLLO_ffi_vec& sr, const ROLLO_ffi_vec& se) {
 *
 * @brief      This function parses a ciphertext into a string
 *
 * @param[out] ct    String containing the ciphertext
 * @param[in]  c     The ciphertext
 */
void lake_ciphertext_to_string(unsigned char* ct, const ROLLO_ffi_vec& c) {
  ROLLO_ffi_vec_to_string(ct, c, ROLLO_PARAM_N);
}



/**
 * @fn         void lake_ciphertext_from_string(ROLLO_ffi_vec& sr, ROLLO_ffi_vec& se, const unsigned char* ct)
 *
 * @brief      This function parses a ciphertext from a string
 *
 *             The ciphertext is composed of vectors <b>sr</b> and <b>se</b>.
 *
 * @param[in]  ct    String containing the ciphertext
 * @param      c     The ciphertext
 */
void lake_ciphertext_from_string(const unsigned char* ct, ROLLO_ffi_vec &c) {
  ROLLO_ffi_vec_from_string(c, ROLLO_PARAM_N, ct);
}

