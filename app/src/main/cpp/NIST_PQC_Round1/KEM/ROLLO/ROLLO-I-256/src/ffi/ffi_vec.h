/**
 * \file ROLLO_ffi_vec.h
 * \brief Interface for vectors over finite field elements
 */

#ifndef ROLLO_FFI_VEC_H
#define ROLLO_FFI_VEC_H

#include "rng.h"
#include "ffi.h"

void ROLLO_ffi_vec_set(ROLLO_ffi_vec& o, const ROLLO_ffi_vec& v, unsigned int size);
void ROLLO_ffi_vec_set_zero(ROLLO_ffi_vec& o, unsigned int size);
void ROLLO_ffi_vec_set_random_using_seedexpander(ROLLO_ffi_vec& o, unsigned int size, AES_XOF_struct* ctx);
void ROLLO_ffi_vec_set_random_full_rank_using_seedexpander(ROLLO_ffi_vec& o, unsigned int size, AES_XOF_struct* ctx);
void ROLLO_ffi_vec_set_random_full_rank_with_one_using_seedexpander(ROLLO_ffi_vec& o, unsigned int size, AES_XOF_struct* ctx);
void ROLLO_ffi_vec_set_random_from_support_using_seedexpander(ROLLO_ffi_vec& o, unsigned int size, const ROLLO_ffi_vec& support, unsigned int rank, AES_XOF_struct* ctx);
void ROLLO_ffi_vec_set_random_full_rank_using_rng(ROLLO_ffi_vec& o, unsigned int size);
void ROLLO_ffi_vec_set_random_full_rank_with_one_using_rng(ROLLO_ffi_vec& o, unsigned int size);
void ROLLO_ffi_vec_set_random_from_support_using_rng(ROLLO_ffi_vec& o, unsigned int size, const ROLLO_ffi_vec& support, unsigned int rank);
void ROLLO_ffi_vec_set_coeff(ROLLO_ffi_vec &v, const ROLLO_ffi_elt& e, unsigned int position);
void ROLLO_ffi_vec_get_coeff(ROLLO_ffi_elt& o, const ROLLO_ffi_vec& v, unsigned int position);
int ROLLO_ffi_vec_cmp(const ROLLO_ffi_vec &v1, const ROLLO_ffi_vec &v2);

unsigned int ROLLO_ffi_vec_gauss(ROLLO_ffi_vec &o, unsigned int size);
unsigned int ROLLO_ffi_vec_get_rank(ROLLO_ffi_vec v, unsigned int size);
void ROLLO_ffi_vec_echelonize(ROLLO_ffi_vec &o, unsigned int size);

void ROLLO_ffi_vec_add(ROLLO_ffi_vec &o, const ROLLO_ffi_vec& v1, const ROLLO_ffi_vec& v2, unsigned int size);
void ROLLO_ffi_vec_mul(ROLLO_ffi_vec &o, const ROLLO_ffi_vec& v1, const ROLLO_ffi_vec& v2, unsigned int size);
void ROLLO_ffi_vec_scalar_mul(ROLLO_ffi_vec& o, const ROLLO_ffi_vec& v, const ROLLO_ffi_elt& e, unsigned int size);
void ROLLO_ffi_vec_tensor_mul(ROLLO_ffi_vec& o, const ROLLO_ffi_vec& v1, unsigned int size1, const ROLLO_ffi_vec& v2, unsigned int size2);

void ROLLO_ffi_vec_directsum(ROLLO_ffi_vec& o, const ROLLO_ffi_vec& v1, unsigned int size1, const ROLLO_ffi_vec& v2, unsigned int size2);
void ROLLO_ffi_vec_intersection(ROLLO_ffi_vec& o, unsigned int& size, const ROLLO_ffi_vec& v1, unsigned int size1, const ROLLO_ffi_vec& v2, unsigned int size2);

void ROLLO_ffi_vec_to_string(unsigned char* str, const ROLLO_ffi_vec& v, unsigned int size);
void ROLLO_ffi_vec_from_string(ROLLO_ffi_vec &v, unsigned int size, const unsigned char *str);
void ROLLO_ffi_vec_print(const ROLLO_ffi_vec& v, unsigned int size);

long ROLLO_ffi_vec_inv(ROLLO_ffi_vec &inv, ROLLO_ffi_vec A);

#endif

