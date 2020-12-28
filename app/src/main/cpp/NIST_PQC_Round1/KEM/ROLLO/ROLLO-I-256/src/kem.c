/** 
 * \file kem.cpp
 * \brief Implementation of api.h
 */

#include "string.h"
#include "hash.h"
#include "rng.h"
#include "api.h"
#include "parameters.h"
#include "rsr_algorithm.h"
#include "parsing.h"
#include "ffi/ffi_field.h"
#include "ffi/ffi_vec.h"
#include "lake_types.h"


/** 
 * \fn int ROLLO_crypto_kem_keypair(unsigned char* pk, unsigned char* sk)
 * \brief Keygen of the LAKE scheme
 *
 * \param[out] pk String containing the public key
 * \param[out] sk String containing the secret key
 * \return 0 if keygen is sucessfull
 */
int ROLLO_crypto_kem_keypair(unsigned char* pk, unsigned char* sk) {
  #ifdef VERBOSE
    printf("\n\n\n### KEYGEN ###\n\n");
  #endif

  ROLLO_ffi_field_init();

  publicKey pk_tmp;
  secretKey sk_tmp;

  long invStatus = 1;
  ROLLO_ffi_vec invx;

  // Create seed expanders for public key and secret key
  unsigned char sk_seed[SEEDEXPANDER_SEED_BYTES];

  do {
    randombytes(sk_seed, SEEDEXPANDER_SEED_BYTES);

    lake_secret_key_from_string(sk_tmp, sk_seed);

    //Try to invert x
    invStatus = ROLLO_ffi_vec_inv(invx, sk_tmp.x);
    //If not invertible change the private key
  } while(invStatus == 1);

  //Computes h=x^-1.y the public key
  ROLLO_ffi_vec_mul(pk_tmp.h, invx, sk_tmp.y, ROLLO_PARAM_N);

  // Parse keys to string
  lake_public_key_to_string(pk, pk_tmp);
  lake_secret_key_to_string(sk, sk_seed);

  #ifdef VERBOSE
    printf("\n\nsk(seed): "); for(int i = 0 ; i < SEEDEXPANDER_SEED_BYTES ; ++i) printf("%02x", sk_seed[i]);
    printf("\n\nF: "); ROLLO_ffi_vec_print(sk_tmp.F, ROLLO_PARAM_D);
    printf("\n\nx: "); ROLLO_ffi_vec_print(sk_tmp.x, ROLLO_PARAM_N);
    printf("\n\ny: "); ROLLO_ffi_vec_print(sk_tmp.y, ROLLO_PARAM_N);

    printf("\n\nh = x^-1.y: "); ROLLO_ffi_vec_print(pk_tmp.h, ROLLO_PARAM_N);

    printf("\n\npk: "); for(int i = 0 ; i < PUBLIC_KEY_BYTES ; ++i) printf("%02x", pk[i]);
  #endif

  return 0;
}



/** 
 * \fn int ROLLO_crypto_kem_enc(unsigned char* ct, unsigned char* ss, const unsigned char* pk)
 * \brief Encapsulation of the LAKE scheme
 *
 * \param[out] ct String containing the ciphertext
 * \param[out] ss String containing the shared secret
 * \param[in] pk String containing the public key
 * \return 0 if encapsulation is sucessfull
 */
int ROLLO_crypto_kem_enc(unsigned char* ct, unsigned char* ss, const unsigned char* pk) {
  #ifdef VERBOSE
    printf("\n\n\n\n### ENCAPS ###");
  #endif

  ROLLO_ffi_field_init();

  publicKey pk_tmp;

  lake_public_key_from_string(pk_tmp, pk);

  //Random error vectors
  ROLLO_ffi_vec E;
  ROLLO_ffi_vec_set_random_full_rank_using_rng(E, ROLLO_PARAM_R);

  //Polynomials
  ROLLO_ffi_vec polyE1, polyE2, polyM;
  ROLLO_ffi_vec_set_random_from_support_using_rng(polyE1, ROLLO_PARAM_N, E, ROLLO_PARAM_R);
  ROLLO_ffi_vec_set_random_from_support_using_rng(polyE2, ROLLO_PARAM_N, E, ROLLO_PARAM_R);

  //Compute ciphertext
  ciphertext c_tmp;

  //Left part : we multiply with the generator matrix by the message and then add right part of the error
  ROLLO_ffi_vec_mul(c_tmp.syndrom, polyE2, pk_tmp.h, ROLLO_PARAM_N);
  ROLLO_ffi_vec_add(c_tmp.syndrom, c_tmp.syndrom, polyE1, ROLLO_PARAM_N);

  lake_ciphertext_to_string(ct, c_tmp.syndrom);

  ROLLO_ffi_vec_echelonize(E, ROLLO_PARAM_R);

  // Compute shared secret
  
  unsigned char support[ROLLO_FFI_VEC_R_BYTES];
  ROLLO_ffi_vec_to_string(support, E, ROLLO_PARAM_R);
  sha512(ss, support, ROLLO_FFI_VEC_R_BYTES);

  #ifdef VERBOSE
    printf("\n\nh: "); ROLLO_ffi_vec_print(pk_tmp.h, ROLLO_PARAM_N);
    printf("\n\nE: "); ROLLO_ffi_vec_print(E, ROLLO_PARAM_R);
    printf("\n\nE1: "); ROLLO_ffi_vec_print(polyE1, ROLLO_PARAM_N);
    printf("\n\nE2: "); ROLLO_ffi_vec_print(polyE2, ROLLO_PARAM_N);
    printf("\n\nc(syndrom): "); ROLLO_ffi_vec_print(c_tmp.syndrom, ROLLO_PARAM_N);
    printf("\n\nct: "); for(int i = 0 ; i < CIPHERTEXT_BYTES ; ++i) printf("%02x", ct[i]);
    printf("\n\nss: "); for(int i = 0 ; i < ROLLO_SHARED_SECRET_BYTES ; ++i) printf("%02x", ss[i]);
  #endif

  return 0;
}



/** 
 * \fn int ROLLO_crypto_kem_dec(unsigned char* ss, const unsigned char* ct, const unsigned char* sk)
 * \brief Decapsulation of the LAKE scheme
 *
 * \param[out] ss String containing the shared secret
 * \param[in] ct String containing the ciphertext
 * \param[in] sk String containing the secret key
 * \return 0 if decapsulation is successfull
 */
int ROLLO_crypto_kem_dec(unsigned char* ss, const unsigned char* ct, const unsigned char* sk) {
  #ifdef VERBOSE
    printf("\n\n\n\n### DECAPS ###\n");
  #endif

  ROLLO_ffi_field_init();

  ciphertext c;
  secretKey sk_tmp;

  //Retrieve ciphertext and secret key
  lake_ciphertext_from_string(ct, c.syndrom);
  lake_secret_key_from_string(sk_tmp, sk);

  //Syndrom computation
  ROLLO_ffi_vec xc;
  ROLLO_ffi_vec_mul(xc, sk_tmp.x, c.syndrom, ROLLO_PARAM_N);
  #ifdef VERBOSE
    printf("\n\nxc: "); ROLLO_ffi_vec_print(xc, ROLLO_PARAM_N);
  #endif

  // Retrieve support_r by cyclic-support error decoding
  ROLLO_ffi_vec E;
  unsigned int E_dim;
  rank_support_recover(E, E_dim, ROLLO_PARAM_R, sk_tmp.F, ROLLO_PARAM_D, xc, ROLLO_PARAM_N);

  // Compute shared secret
  if(E_dim != 0) {
    unsigned char support[ROLLO_FFI_VEC_R_BYTES];
    ROLLO_ffi_vec_to_string(support, E, ROLLO_PARAM_R);
    sha512(ss, support, ROLLO_FFI_VEC_R_BYTES);
  } else {
    //memset(ss, 0, sizeof(ROLLO_SHARED_SECRET_BYTES));
    memset(ss, 0, sizeof(ROLLO_CRYPTO_BYTES));
  }

  #ifdef VERBOSE
    printf("\n\nE: "); ROLLO_ffi_vec_print(E, E_dim);
    printf("\n\nss: "); for(int i = 0 ; i < ROLLO_SHARED_SECRET_BYTES ; ++i) printf("%02x", ss[i]);
  #endif

  if(E_dim != ROLLO_PARAM_R) return 1;

  return 0;
}

