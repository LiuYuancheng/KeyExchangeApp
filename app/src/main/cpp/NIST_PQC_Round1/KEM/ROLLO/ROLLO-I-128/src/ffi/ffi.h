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

typedef GF2E  ffi_elt;
typedef GF2EX ffi_vec;

#define FIELD_Q 2 
#define ROLLO_FIELD_M ROLLO_PARAM_M
#define FIELD_ELT_BYTES GF2MBYTES

extern ffi_vec ROLLO_ideal_modulo;
#define MODULO_NUMBER ROLLO_NMODCOEFFS
#define MODULO_VALUES ROLLO_MODCOEFFS

#endif
