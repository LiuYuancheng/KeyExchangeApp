/** 
 * \file ffi.h
 * \brief Constants defining the finite field used
 */

#ifndef RQC_FFI_H
#define RQC_FFI_H

#include <NTL/GF2E.h>
#include <NTL/GF2EX.h>
#include <NTL/GF2X.h>
#include <NTL/GF2XFactoring.h>
#include <NTL/mat_GF2.h>
#include <NTL/vec_vec_GF2.h>
#include <gmp.h>

using namespace NTL;

typedef GF2E  ffi_elt;
typedef GF2EX ffi_vec;

#define RQC_FIELD_Q 2 
#define RQC_FIELD_M 97
#define RQC_FIELD_ELT_BYTES 13

extern ffi_vec ideal_modulo;
#define RQC_MODULO_NUMBER 5
#define RQC_MODULO_VALUES {0, 1, 2, 5, 67}

#endif

