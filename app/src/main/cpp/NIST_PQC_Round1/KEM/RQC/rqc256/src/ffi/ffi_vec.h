/**
 * \file RQC_ffi_vec.h
 * \brief Interface for vectors over finite field elements
 */

#ifndef RQC_FFI_VEC_H
#define RQC_FFI_VEC_H

#include "ffi.h"
#include "rng.h"

RQC_ffi_elt RQC_ffi_vec_get_coeff(const RQC_ffi_vec& v, unsigned int position);
void RQC_ffi_vec_set_coeff(RQC_ffi_vec& o, const RQC_ffi_elt& e, unsigned int position);
void RQC_ffi_vec_set_length(RQC_ffi_vec& o, unsigned int size);

void RQC_ffi_vec_set(RQC_ffi_vec& o, const RQC_ffi_vec& v, unsigned int size);
void RQC_ffi_vec_set_zero(RQC_ffi_vec& o, unsigned int size);
void RQC_ffi_vec_set_random(RQC_ffi_vec& o, unsigned int size, AES_XOF_struct* ctx);
void RQC_ffi_vec_set_random2(RQC_ffi_vec& o, unsigned int size);
void RQC_ffi_vec_set_random_full_rank(RQC_ffi_vec& o, unsigned int size, AES_XOF_struct* ctx);
void RQC_ffi_vec_set_random_full_rank_with_one(RQC_ffi_vec& o, unsigned int size, AES_XOF_struct* ctx);
void RQC_ffi_vec_set_random_from_support(RQC_ffi_vec& o, unsigned int size, const RQC_ffi_vec& support, unsigned int rank, AES_XOF_struct* ctx);

int RQC_ffi_vec_is_equal_to(const RQC_ffi_vec& v1, const RQC_ffi_vec& v2, unsigned int position);

void RQC_ffi_vec_add(RQC_ffi_vec &o, const RQC_ffi_vec& v1, const RQC_ffi_vec& v2, unsigned int size);
void RQC_ffi_vec_mul(RQC_ffi_vec &o, const RQC_ffi_vec& v1, const RQC_ffi_vec& v2, unsigned int size);

void RQC_ffi_vec_to_string(unsigned char* str, const RQC_ffi_vec& v, unsigned int size);
void RQC_ffi_vec_to_string_compact(unsigned char* str, const RQC_ffi_vec& v, unsigned int size);
void RQC_ffi_vec_from_string(RQC_ffi_vec &o, unsigned int size, const unsigned char *str);
void RQC_ffi_vec_from_string_compact(RQC_ffi_vec &o, unsigned int size, const unsigned char *str);

void RQC_ffi_vec_print(const RQC_ffi_vec& v, unsigned int size);

#endif

