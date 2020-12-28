/** 
 * \file parsing.c
 * \brief Implementation of parsing.h
 */

#include "ffi/ffi_vec.h"
#include "parameters.h"
#include "parsing.h"
#include <cstring>


/** 
 * \fn void rqc_secret_key_to_string(unsigned char* sk, const unsigned char* seed, const unsigned char* pk)
 * \brief This function parses a secret key into a string
 *
 * The secret key is composed of the seed used to generate vectors <b>x</b> and <b>y</b>.
 * As a technicality, the public key is appended to the secret key in order to respect the NIST API.
 *
 * \param[out] sk String containing the secret key
 * \param[in] seed Seed used to generate the vectors x and y
 * \param[in] pk String containing the public key
 */
void rqc_secret_key_to_string(unsigned char* sk, const unsigned char* seed, const unsigned char* pk) {
  memcpy(sk, seed, SEEDEXPANDER_SEED_BYTES);
  memcpy(sk + SEEDEXPANDER_SEED_BYTES, pk, PUBLIC_KEY_BYTES);
}



/** 
 * \fn void rqc_secret_key_from_string(RQC_ffi_vec& x, RQC_ffi_vec& y, unsigned char* pk, const unsigned char* sk)
 * \brief This function parses a secret key from a string
 *
 * The secret key is composed of the seed used to generate vectors <b>x</b> and <b>y</b>.
 * As a technicality, the public key is appended to the secret key in order to respect the NIST API.
 *
 * \param[out] x RQC_ffi_vec representation of vector x
 * \param[out] y RQC_ffi_vec representation of vector y
 * \param[out] pk String containing the public key
 * \param[in] sk String containing the secret key
 */
void rqc_secret_key_from_string(RQC_ffi_vec& x, RQC_ffi_vec& y, unsigned char* pk, const unsigned char* sk) {
  unsigned char sk_seed[SEEDEXPANDER_SEED_BYTES];
  memcpy(sk_seed, sk, SEEDEXPANDER_SEED_BYTES);

  AES_XOF_struct* sk_seedexpander = (AES_XOF_struct*) malloc(sizeof(AES_XOF_struct));
  seedexpander_init(sk_seedexpander, sk_seed, sk_seed + 32, SEEDEXPANDER_MAX_LENGTH);

  RQC_ffi_vec support_w;
  RQC_ffi_vec_set_random_full_rank_with_one(support_w, RQC_PARAM_W, sk_seedexpander);
  RQC_ffi_vec_set_random_from_support(x, RQC_PARAM_N, support_w, RQC_PARAM_W, sk_seedexpander);
  RQC_ffi_vec_set_random_from_support(y, RQC_PARAM_N, support_w, RQC_PARAM_W, sk_seedexpander);
  free(sk_seedexpander);

  memcpy(pk, sk + SEEDEXPANDER_SEED_BYTES, PUBLIC_KEY_BYTES);
}



/** 
 * \fn void rqc_public_key_to_string(unsigned char* pk, const RQC_ffi_vec& s, const unsigned char* seed)
 * \brief This function parses a public key into a string
 *
 * The public key is composed of the syndrom <b>s</b> as well as the seed used to generate vectors <b>g</b> and <b>h</b>.
 *
 * \param[out] pk String containing the public key
 * \param[in] s RQC_ffi_vec representation of vector s
 * \param[in] seed Seed used to generate the public key
 */
void rqc_public_key_to_string(unsigned char* pk, const RQC_ffi_vec& s, const unsigned char* seed) {
  RQC_ffi_vec_to_string_compact(pk, s, RQC_PARAM_N);
  memcpy(pk + RQC_VEC_N_BYTES, seed, SEEDEXPANDER_SEED_BYTES);
}



/** 
 * \fn void rqc_public_key_from_string(RQC_ffi_vec& g, RQC_ffi_vec& h, RQC_ffi_vec& s, const unsigned char* pk)
 * \brief This function parses a public key from a string
 *
 * The public key is composed of the syndrom <b>s</b> as well as the seed used to generate vectors <b>g</b> and <b>h</b>.
 *
 * \param[out] g RQC_ffi_vec representation of vector g
 * \param[out] h RQC_ffi_vec representation of vector h
 * \param[out] s RQC_ffi_vec representation of vector s
 * \param[in] pk String containing the public key
 */
void rqc_public_key_from_string(RQC_ffi_vec& g, RQC_ffi_vec& h, RQC_ffi_vec& s, const unsigned char* pk) {
  RQC_ffi_vec_from_string_compact(s, RQC_PARAM_N, pk);

  unsigned char pk_seed[SEEDEXPANDER_SEED_BYTES];
  memcpy(pk_seed, pk + RQC_VEC_N_BYTES, SEEDEXPANDER_SEED_BYTES);

  AES_XOF_struct* pk_seedexpander = (AES_XOF_struct*) malloc(sizeof(AES_XOF_struct));
  seedexpander_init(pk_seedexpander, pk_seed, pk_seed + 32, SEEDEXPANDER_MAX_LENGTH);

  RQC_ffi_vec_set_random_full_rank(g, RQC_PARAM_N, pk_seedexpander);
  RQC_ffi_vec_set_random(h, RQC_PARAM_N, pk_seedexpander); 

  free(pk_seedexpander);
}



/** 
 * \fn void rqc_kem_ciphertext_to_string(unsigned char* ct, const RQC_ffi_vec& u, const RQC_ffi_vec& v, const unsigned char* d) {
 * \brief This function parses a ciphertext into a string
 *
 * The ciphertext is composed of vectors <b>u</b>, <b>v</b> and the hash <b>d</b>.
 *
 * \param[out] ct String containing the ciphertext
 * \param[in] u RQC_ffi_vec representation of vector u
 * \param[in] v RQC_ffi_vec representation of vector v
 * \param[in] d String containing the hash d
 */
void rqc_kem_ciphertext_to_string(unsigned char* ct, const RQC_ffi_vec& u, const RQC_ffi_vec& v, const unsigned char* d) {
  RQC_ffi_vec_to_string_compact(ct, u, RQC_PARAM_N);
  RQC_ffi_vec_to_string_compact(ct + RQC_VEC_N_BYTES, v, RQC_PARAM_N);
  memcpy(ct + 2 * RQC_VEC_N_BYTES, d, SHA512_BYTES);
}



/** 
 * \fn void rqc_kem_ciphertext_from_string(RQC_ffi_vec& u, RQC_ffi_vec& v, unsigned char* d, const unsigned char* ct)
 * \brief This function parses a ciphertext from a string
 *
 * The ciphertext is composed of vectors <b>u</b>, <b>v</b> and the hash <b>d</b>.
 *
 * \param[out] u RQC_ffi_vec representation of vector u
 * \param[out] v RQC_ffi_vec representation of vector v
 * \param[out] d String containing the hash d
 * \param[in] ct String containing the ciphertext
 */
void rqc_kem_ciphertext_from_string(RQC_ffi_vec& u, RQC_ffi_vec& v, unsigned char* d, const unsigned char* ct) {
  RQC_ffi_vec_from_string_compact(u, RQC_PARAM_N, ct);
  RQC_ffi_vec_from_string_compact(v, RQC_PARAM_N, ct + RQC_VEC_N_BYTES);
  memcpy(d, ct + 2 * RQC_VEC_N_BYTES, SHA512_BYTES);
}

