/**
 * \file ffi_elt.h
 * \brief Interface for finite field elements
 */

#ifndef ROLLO_FFI_ELT_H
#define ROLLO_FFI_ELT_H

#include <NTL/GF2EX.h>
#include "rng.h"
#include "ffi.h"


void ROLLO_ffi_elt_set(ffi_elt& o, const ffi_elt& e);
void ROLLO_ffi_elt_set_zero(ffi_elt& o);
void ROLLO_ffi_elt_set_one(ffi_elt& o);
void ROLLO_ffi_elt_set_random_using_rng(ffi_elt& o);
void ROLLO_ffi_elt_set_random_using_seedexpander(ffi_elt& o, AES_XOF_struct* ctx);

int ROLLO_ffi_elt_is_zero(const ffi_elt& e);

void ROLLO_ffi_elt_inv(ffi_elt& o, const ffi_elt& e);
void ROLLO_ffi_elt_add(ffi_elt& o, const ffi_elt& e1, const ffi_elt& e2);
void ROLLO_ffi_elt_mul(ffi_elt& o, const ffi_elt& e1, const ffi_elt& e2);

void ROLLO_ffi_elt_to_string(unsigned char* str, const ffi_elt& e);
void ROLLO_ffi_elt_from_string(ffi_elt& e, const unsigned char* str);
void ROLLO_ffi_elt_print(const ffi_elt& e);


unsigned long ntl_random_word_using_rng();
unsigned long ntl_random_word_using_seedexpander(AES_XOF_struct* ctx);
unsigned long ntl_random_bits_ulong_using_rng(long l);
unsigned long ntl_random_bits_ulong_using_seedexpander(long l, AES_XOF_struct* ctx);
void ntl_random_using_rng(GF2X& x, long n);
void ntl_random_using_seedexpander(GF2X& x, long n, AES_XOF_struct* ctx);

#endif

