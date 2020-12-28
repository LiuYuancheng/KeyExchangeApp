/** 
 * \file parsing.h
 * \brief Functions to parse secret key, public key and ciphertext of the RQC scheme
 */

#ifndef RQC_PARSING_H
#define RQC_PARSING_H

#include "ffi/ffi_vec.h"


void rqc_secret_key_to_string(unsigned char* sk, const unsigned char* seed, const unsigned char* pk);
void rqc_secret_key_from_string(RQC_ffi_vec& x, RQC_ffi_vec& y, unsigned char* pk, const unsigned char* sk);

void rqc_public_key_to_string(unsigned char* pk, const RQC_ffi_vec& s, const unsigned char* seed);
void rqc_public_key_from_string(RQC_ffi_vec& g, RQC_ffi_vec& h, RQC_ffi_vec& s, const unsigned char* pk);

void rqc_kem_ciphertext_to_string(unsigned char* ct, const RQC_ffi_vec& u, const RQC_ffi_vec& v, const unsigned char* d);
void rqc_kem_ciphertext_from_string(RQC_ffi_vec& u, RQC_ffi_vec& v, unsigned char* d, const unsigned char* ct);

#endif

