/**
 * \file ffi_field.cpp
 * \brief Implementation of ffi_field.h
 */

#include <NTL/GF2E.h>
#include <NTL/GF2X.h>
#include <NTL/GF2XFactoring.h>
#include "ffi.h"
#include "ffi_field.h"

using namespace NTL;

int ROLLO_init = 0;
ffi_vec ROLLO_ideal_modulo;

/** 
 * \fn void ffi_field_init()
 * \brief This function initializes a finite field
 */
void ROLLO_ffi_field_init() {
//	if(!ROLLO_init) {
//		ROLLO_init = 1;
		GF2X P = BuildSparseIrred_GF2X(ROLLO_FIELD_M);
  		GF2E::init(P);
		GF2X::HexOutput = 1;

	    int coeffs[ROLLO_NMODCOEFFS] = ROLLO_MODCOEFFS;
	    int i;
	    for(i=0 ; i<ROLLO_NMODCOEFFS ; i++) {
	      SetCoeff(ROLLO_ideal_modulo, coeffs[i], 1);
	    }
//	}
}

