/** 
 * \file rqc.h
 * \brief Functions of the RQC_PKE IND-CPA scheme
 */

#ifndef RQC_H
#define RQC_H

#include "ffi/ffi_vec.h"


void rqc_pke_keygen(unsigned char* pk, unsigned char* sk);
void rqc_pke_encrypt(RQC_ffi_vec& u, RQC_ffi_vec& v, const RQC_ffi_vec& m, unsigned char* theta, const unsigned char* pk);
void rqc_pke_decrypt(RQC_ffi_vec& m, const RQC_ffi_vec& u, const RQC_ffi_vec& v, const unsigned char* sk);

#endif

