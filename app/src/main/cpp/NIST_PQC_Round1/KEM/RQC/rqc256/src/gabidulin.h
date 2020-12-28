/**
 * \file gabidulin.h
 * \brief Fonctions to encode and decode messages using Gabidulin codes
 *
 * The decoding algorithm provided is based on q_polynomials reconstruction, see \cite gabidulin:welch and \cite gabidulin:generalized for details.
 *
 */

#ifndef GABIDULIN_H
#define GABIDULIN_H

#include "ffi/ffi_vec.h"


/**
  * \typedef gabidulin_code
  * \brief Structure of a gabidulin code
  */
typedef struct gabidulin_code {
  RQC_ffi_vec g; /**< Generator vector defining the code */
  unsigned int k; /**< Size of vectors representing messages */
  unsigned int n; /**< Size of vectors representing codewords */
} gabidulin_code;


gabidulin_code gabidulin_code_init(const RQC_ffi_vec& g, unsigned int k, unsigned int n);

void gabidulin_code_encode(RQC_ffi_vec& c, gabidulin_code gc, const RQC_ffi_vec& m);
void gabidulin_code_decode(RQC_ffi_vec& m, gabidulin_code gc, const RQC_ffi_vec& y);

#endif

