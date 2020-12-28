/**
 * \file RQC_ffi_elt.h
 * \brief Interface for finite field elements
 */

#ifndef FFI_ELT_H
#define FFI_ELT_H

#include "ffi.h"
#include "rng.h"

RQC_ffi_elt RQC_ffi_elt_get_zero();
RQC_ffi_elt RQC_ffi_elt_get_one();

void RQC_ffi_elt_set(RQC_ffi_elt& o, const RQC_ffi_elt& e);
void RQC_ffi_elt_set_zero(RQC_ffi_elt& o);
void RQC_ffi_elt_set_random(RQC_ffi_elt& o, AES_XOF_struct* ctx);
void RQC_ffi_elt_set_random2(RQC_ffi_elt& o);

int RQC_ffi_elt_is_zero(const RQC_ffi_elt& e);

void RQC_ffi_elt_inv(RQC_ffi_elt& o, const RQC_ffi_elt& e);
void RQC_ffi_elt_sqr(RQC_ffi_elt& o, const RQC_ffi_elt& e);
void RQC_ffi_elt_nth_root(RQC_ffi_elt& o, const RQC_ffi_elt& e, int n);
void RQC_ffi_elt_add(RQC_ffi_elt& o, const RQC_ffi_elt& e1, const RQC_ffi_elt& e2);
void RQC_ffi_elt_mul(RQC_ffi_elt& o, const RQC_ffi_elt& e1, const RQC_ffi_elt& e2);

void RQC_ffi_elt_from_string(RQC_ffi_elt& o, const unsigned char* str);
void RQC_ffi_elt_to_string(unsigned char* str, const RQC_ffi_elt& e);

void RQC_ffi_elt_print(const RQC_ffi_elt& e);

#endif

