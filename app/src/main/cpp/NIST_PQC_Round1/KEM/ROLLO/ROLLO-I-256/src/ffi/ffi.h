/** 
 * \file ffi.h
 * \brief Constants to define the finite field used
 */
#ifndef ROLLO_FFI_H
#define ROLLO_FFI_H

#include <NTL/GF2E.h>
#include <NTL/GF2EX.h>
#include "../parameters.h"

using namespace NTL;

typedef GF2E  ROLLO_ffi_elt;
typedef GF2EX ROLLO_ffi_vec;

#define ROLLO_FIELD_Q 2 
#define ROLLO_FIELD_M ROLLO_PARAM_M
#define ROLLO_FIELD_ELT_BYTES ROLLO_GF2MBYTES

extern ROLLO_ffi_vec ROLLO_ideal_modulo;
#define ROLLO_MODULO_NUMBER ROLLO_NMODCOEFFS
#define ROLLO_MODULO_VALUES ROLLO_MODCOEFFS

#endif

