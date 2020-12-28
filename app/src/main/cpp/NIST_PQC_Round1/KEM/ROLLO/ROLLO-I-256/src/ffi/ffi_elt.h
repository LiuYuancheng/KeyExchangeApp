/**
 * \file ROLLO_ffi_elt.h
 * \brief Interface for finite field elements
 */

#ifndef ROLLO_FFI_ELT_H
#define ROLLO_FFI_ELT_H

#include <NTL/GF2EX.h>
#include "rng.h"
#include "ffi.h"


void ROLLO_ffi_elt_set(ROLLO_ffi_elt& o, const ROLLO_ffi_elt& e);
void ROLLO_ffi_elt_set_zero(ROLLO_ffi_elt& o);
void ROLLO_ffi_elt_set_one(ROLLO_ffi_elt& o);
void ROLLO_ffi_elt_set_random_using_rng(ROLLO_ffi_elt& o);
void ROLLO_ffi_elt_set_random_using_seedexpander(ROLLO_ffi_elt& o, AES_XOF_struct* ctx);

int ROLLO_ffi_elt_is_zero(const ROLLO_ffi_elt& e);

void ROLLO_ffi_elt_inv(ROLLO_ffi_elt& o, const ROLLO_ffi_elt& e);
void ROLLO_ffi_elt_add(ROLLO_ffi_elt& o, const ROLLO_ffi_elt& e1, const ROLLO_ffi_elt& e2);
void ROLLO_ffi_elt_mul(ROLLO_ffi_elt& o, const ROLLO_ffi_elt& e1, const ROLLO_ffi_elt& e2);

void ROLLO_ffi_elt_to_string(unsigned char* str, const ROLLO_ffi_elt& e);
void ROLLO_ffi_elt_from_string(ROLLO_ffi_elt& e, const unsigned char* str);
void ROLLO_ffi_elt_print(const ROLLO_ffi_elt& e);


unsigned long ntl_random_word_using_rng();
unsigned long ntl_random_word_using_seedexpander(AES_XOF_struct* ctx);
unsigned long ntl_random_bits_ulong_using_rng(long l);
unsigned long ntl_random_bits_ulong_using_seedexpander(long l, AES_XOF_struct* ctx);
void ntl_random_using_rng(GF2X& x, long n);
void ntl_random_using_seedexpander(GF2X& x, long n, AES_XOF_struct* ctx);

#endif

