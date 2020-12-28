/**
 * \file ffi_field.h
 * \brief Interface for finite fields
 *
 * In the context of the RQC scheme, a finite field always describes an extension of a binary field namely a finite field of the form \f$ GF(2^m) \f$.
 *
 */

#ifndef RQC_FFI_FIELD_H
#define RQC_FFI_FIELD_H

void RQC_ffi_field_init();
int RQC_ffi_field_get_degree();

#endif

