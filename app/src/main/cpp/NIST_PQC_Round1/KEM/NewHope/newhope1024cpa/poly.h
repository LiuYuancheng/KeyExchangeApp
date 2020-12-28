#ifndef NEWHOPE_POLY_H
#define NEWHOPE_POLY_H

#include <stdint.h>
#include "params.h"

/* 
 * Elements of R_q = Z_q[X]/(X^n + 1). Represents polynomial
 * coeffs[0] + X*coeffs[1] + X^2*xoeffs[2] + ... + X^{n-1}*coeffs[n-1] 
 */
typedef struct {
  uint16_t coeffs[NEWHOPE_N];
} poly __attribute__ ((aligned (32)));

void newhope1024cpa_poly_uniform(poly *a, const unsigned char *seed);
void newhope1024cpa_poly_sample(poly *r, const unsigned char *seed, unsigned char nonce);
void newhope1024cpa_poly_add(poly *r, const poly *a, const poly *b);

void newhope1024cpa_poly_ntt(poly *r);
void newhope1024cpa_poly_invntt(poly *r);
void poly_mul_pointwise(poly *r, const poly *a, const poly *b);

void newhope1024cpa_poly_frombytes(poly *r, const unsigned char *a);
void poly_tobytes(unsigned char *r, const poly *p);
void newhope1024cpa_poly_compress(unsigned char *r, const poly *p);
void newhope1024cpa_poly_decompress(poly *r, const unsigned char *a);

void newhope1024cpa_poly_frommsg(poly *r, const unsigned char *msg);
void poly_tomsg(unsigned char *msg, const poly *x);
void newhope1024cpa_poly_sub(poly *r, const poly *a, const poly *b);

#endif
