/**
 * \file parameters.h
 * \brief Parameters of the HQC_KEM IND-CCA2 scheme
 */

#include "api.h"
#include "vector.h"

#ifndef HQC_PARAMETERS_H
#define HQC_PARAMETERS_H


/*
  #define HQC_PARAM_N                             Define the parameter n of the scheme  
  #define HQC_PARAM_N1                            Define the parameter n1 of the scheme (length of BCH code)  
  #define HQC_PARAM_N2                            Define the parameter n2 of the scheme (length of the repetition code)
  #define HQC_PARAM_N1N2                          Define the parameter n1 * n2 of the scheme (length of the tensor code)
  #define HQC_PARAM_T                             Define a threshold for decoding repetition code word (HQC_PARAM_T = (HQC_PARAM_N2 - 1) / 2)
  #define HQC_PARAM_OMEGA                         Define the parameter omega of the scheme
  #define HQC_PARAM_OMEGA_E                       Define the parameter omega_e of the scheme
  #define HQC_PARAM_OMEGA_R                       Define the parameter omega_r of the scheme
  #define HQC_PARAM_DELTA                         Define the parameter delta of the scheme (correcting capacity of the BCH code)
  #define HQC_PARAM_SECURITY                      Define the security level corresponding to the chosen parameters
  #define HQC_PARAM_DFR_EXP                       Define the decryption failure rate corresponding to the chosen parameters
  
  #define SECRET_KEY_BYTES                    Define the size of the secret key in bytes
  #define PUBLIC_KEY_BYTES                    Define the size of the public key in bytes
  #define SHARED_SECRET_BYTES                 Define the size of the shared secret in bytes 
  #define CIPHERTEXT_BYTES                    Define the size of the ciphertext in bytes
  
  #define HQC_PARAM_POLY                          Define p(x) = 1 + x^3 + x^10 the primitive polynomial of degree 10 in hexadecimal representation
                                              We define alpha as the root of p(x), i.e p(alpha) = 0. Then, alpha is a primitive element, 
                                              and the powers of alpha generate all the nonzero elements of GF(2^10)
                                              We use this polynomial to build the Galois Field GF(2^10) needed for the BCH code 
  #define HQC_PARAM_M                             Define a positive integer 
  #define HQC_PARAM_GF_MUL_ORDER                  Define the size of the multiplicative group of GF(2^m), i.e 2^m -1
  #define HQC_PARAM_G                             Define the size of the generator polynomial of BCH code
  #define HQC_PARAM_K                             Define the size of the information bits of the BCH code 

  #define UTILS_REJECTION_THRESHOLD           Define the rejection threshold used to generate given weight vectors (see vector_u32_fixed_weight function documentation)

  #define HQC_VEC_N_ARRAY_SIZE_BYTES              Define the size of the array used to store a HQC_PARAM_N sized vector in bytes
  #define HQC_VEC_N1_ARRAY_SIZE_BYTES             Define the size of the array used to store a HQC_PARAM_N1 sized vector in bytes  
  #define HQC_VEC_N1N2_ARRAY_SIZE_BYTES           Define the size of the array used to store a HQC_PARAM_N1N2 sized vector in bytes 
  #define HQC_VEC_K_ARRAY_SIZE_BYTES              Define the size of the array used to store a HQC_PARAM_K sized vector in bytes
   
  #define SHA512_BYTES                        Define the size of SHA512 output in bytes
  #define SEED_BYTES                          Define the size of the seed in bytes
  #define SEEDEXPANDER_MAX_LENGTH             Define the seed expander max length
*/

#define HQC_PARAM_N                             43669
#define HQC_PARAM_N1                            766
#define HQC_PARAM_N2                            57
#define HQC_PARAM_N1N2                          43662
#define HQC_PARAM_T                             28
#define HQC_PARAM_OMEGA                         101
#define HQC_PARAM_OMEGA_E                       117 
#define HQC_PARAM_OMEGA_R                       117
#define HQC_PARAM_DELTA                         57
#define HQC_PARAM_SECURITY                      192
#define HQC_PARAM_DFR_EXP                       128

#define SECRET_KEY_BYTES                    HQC_CRYPTO_SECRETKEYBYTES
#define PUBLIC_KEY_BYTES                    HQC_CRYPTO_PUBLICKEYBYTES
#define SHARED_SECRET_BYTES                 HQC_CRYPTO_BYTES
#define CIPHERTEXT_BYTES                    HQC_CRYPTO_CIPHERTEXTBYTES

#define HQC_PARAM_POLY                          0x409
#define HQC_PARAM_M                             10
#define HQC_PARAM_GF_MUL_ORDER                  1023
#define HQC_PARAM_G                             511
#define HQC_PARAM_K                             256

#define UTILS_REJECTION_THRESHOLD           16768896

#define HQC_VEC_N_SIZE_BYTES                    CEIL_DIVIDE(HQC_PARAM_N, 8)
#define HQC_VEC_N1_SIZE_BYTES                   CEIL_DIVIDE(HQC_PARAM_N1, 8)
#define HQC_VEC_N1N2_SIZE_BYTES                 CEIL_DIVIDE(HQC_PARAM_N1N2, 8)
#define HQC_VEC_K_SIZE_BYTES                    CEIL_DIVIDE(HQC_PARAM_K, 8)

#define SHA512_BYTES                        64
#define SEED_BYTES                          40
#define SEEDEXPANDER_MAX_LENGTH             4294967295
  
#endif
