/** 
 * \file lake_types.h
 * \brief File defining publicKey, secretKey and cipherText types for LAKE
 */

#ifndef LAKE_TYPES_H
#define LAKE_TYPES_H

#include "ffi/ffi_vec.h"

typedef struct secretKey {
	ROLLO_ffi_vec F;
	ROLLO_ffi_vec x;
	ROLLO_ffi_vec y;
} secretKey;

typedef struct publicKey {
	ROLLO_ffi_vec h;
} publicKey;

typedef struct ciphertext{
	ROLLO_ffi_vec syndrom;
} ciphertext;

#endif
