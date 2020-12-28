/**
 * \file ffi_field.cpp
 * \brief Implementation of ffi_field.h using the NTL library
 */

#include "ffi.h"
#include "ffi_field.h"

int init = 0;
RQC_ffi_vec RQC_ideal_modulo;


/**
 * \fn void ffi_field_init()
 * \brief This function initializes a finite field
 */
void RQC_ffi_field_init() {
//	if(!init) {
		init = 1;

    // Polynomial used for field computation
		GF2X P = BuildSparseIrred_GF2X(RQC_FIELD_M);
		GF2E::init(P);
    GF2X::HexOutput = 1;

    // Polynomial used for vector multiplication
    unsigned int values[RQC_MODULO_NUMBER] = RQC_MODULO_VALUES;
    for(int i = 0 ; i < RQC_MODULO_NUMBER ; ++i) {
      SetCoeff(RQC_ideal_modulo, values[i], 1);
    }
//	}
}



/**
 * \fn int RQC_ffi_field_get_degree()
 * \brief This function returns the degree m of the finite field GF(2^m)
 *
 * \return Degree of the finite field
 */
int RQC_ffi_field_get_degree() {
  return RQC_FIELD_M;
}

