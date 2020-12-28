/** 
 * \file parameters.h
 * \brief Parameters of the ROLLO scheme
 */

#ifndef ROLLO_PARAMETER_H
#define ROLLO_PARAMETER_H

#include "api.h"

#define ROLLO_PARAM_M 113 /**< Parameter m of the scheme (finite field GF(2^m)) */
#define ROLLO_PARAM_N 67 /**< Parameter n of the scheme (code length) */
#define ROLLO_PARAM_D 8 /**< Parameter d of the scheme (weight of vectors) */
#define ROLLO_PARAM_R 7 /**< Parameter r of the scheme (weight of vectors) */
#define ROLLO_PARAM_DFR 42 /**< Decryption Failure Rate (2^-30) */
#define ROLLO_PARAM_SECURITY 256 /**< Expected security level */

#define ROLLO_NMODCOEFFS 5 //Number of "1" coefficients in the polynomial defining the ideal
#define ROLLO_MODCOEFFS {0, 1, 2, 5, 67} //List of "1" coefficients in the polynomial defining the ideal
/*
#define PUBLIC_KEY_BYTES ROLLO_CRYPTO_PUBLICKEYBYTES
#define SECRET_KEY_BYTES ROLLO_CRYPTO_SECRETKEYBYTES
#define CIPHERTEXT_BYTES ROLLO_CRYPTO_CIPHERTEXTBYTES
#define ROLLO_SHARED_SECRET_BYTES ROLLO_CRYPTO_BYTES
*/
#define ROLLO_GF2MBYTES 15 //Number of bytes to store an element of GF2^m
#define ROLLO_FFI_VEC_R_BYTES 99 //Number of bytes to store R elements of GF2^m
#define ROLLO_FFI_VEC_N_BYTES 947 //Number of bytes to store N elements of GF2^m
#define SHA512_BYTES 64 /**< Size of SHA512 output */

#define SEEDEXPANDER_SEED_BYTES 40 /**< Seed size of the NIST seed expander */
#define SEEDEXPANDER_MAX_LENGTH 4294967295 /**< Max length of the NIST seed expander */

#endif

