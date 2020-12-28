/** 
 * \file parameters.h
 * \brief Parameters of the RQC_KEM IND-CCA2 scheme
 */

#include "api.h"

#ifndef RQC_PARAMETER_H
#define RQC_PARAMETER_H


#define RQC_PARAM_Q 2 /**< Parameter q of the scheme (finite field GF(q^m)) */
#define RQC_PARAM_M 97 /**< Parameter m of the scheme (finite field GF(q^m)) */
#define RQC_PARAM_K 4 /**< Parameter k of the scheme (code dimension) */
#define RQC_PARAM_N 67 /**< Parameter n of the scheme (code length) */
#define RQC_PARAM_W 5 /**< Parameter omega of the scheme (weight of vectors) */
#define RQC_PARAM_W_R 6 /**< Parameter omega_r of the scheme (weight of vectors) */
#define RQC_PARAM_SECURITY 128 /**< Expected security level */
/*
#define SECRET_KEY_BYTES RQC_CRYPTO_SECRETKEYBYTES 
#define PUBLIC_KEY_BYTES RQC_CRYPTO_PUBLICKEYBYTES 
#define SHARED_SECRET_BYTES RQC_CRYPTO_BYTES 
#define CIPHERTEXT_BYTES RQC_CRYPTO_CIPHERTEXTBYTES
*/
#define RQC_VEC_K_BYTES 49 /**< Number of bytes required to store a vector of size k */
#define RQC_VEC_N_BYTES 813 /**< Number of bytes required to store a vector of size n */
#define RQC_FFI_ELT_BYTES 13 /**< Number of bytes required to store an element of GF(q^m) */
#define RQC_FFI_VEC_K_BYTES RQC_PARAM_K * RQC_FFI_ELT_BYTES /**< Number of bytes required to store a vector of size k using the NTL-based ffi_vec implementation */
#define RQC_FFI_VEC_N_BYTES RQC_PARAM_N * RQC_FFI_ELT_BYTES /**< Number of bytes required to store a vector of size n using the NTL-based ffi_vec implementation */

#define SHA512_BYTES 64 /**< Size of SHA512 output */

#define SEEDEXPANDER_SEED_BYTES 40 /**< Seed size of the NIST seed expander */
#define SEEDEXPANDER_MAX_LENGTH 4294967295 /**< Max length of the NIST seed expander */

#endif

