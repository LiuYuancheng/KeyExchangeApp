#ifndef POLY_H
#define POLY_H

#include <stdint.h>
#include "params.h"

/*
 * Elements of R_q = Z_q[X]/(X^n + 1). Represents polynomial
 * coeffs[0] + X*coeffs[1] + X^2*xoeffs[2] + ... + X^{n-1}*coeffs[n-1]
 */
typedef struct{
  int16_t coeffs[KYBER_N];
} poly;

void KYBER_poly_compress(unsigned char *r, poly *a);
void KYBER_poly_decompress(poly *r, const unsigned char *a);

void KYBER_poly_tobytes(unsigned char *r, poly *a);
void KYBER_poly_frombytes(poly *r, const unsigned char *a);

void KYBER_poly_frommsg(poly *r, const unsigned char msg[KYBER_SYMBYTES]);
void KYBER_poly_tomsg(unsigned char msg[KYBER_SYMBYTES], poly *r);

void KYBER_poly_getnoise(poly *r,const unsigned char *seed, unsigned char nonce);

void KYBER_poly_ntt(poly *r);
void KYBER_poly_invntt(poly *r);
void KYBER_poly_basemul(poly *r, const poly *a, const poly *b);
void KYBER_poly_frommont(poly *r);

void KYBER_poly_reduce(poly *r);
void KYBER_poly_csubq(poly *r);

void KYBER_poly_add(poly *r, const poly *a, const poly *b);
void KYBER_poly_sub(poly *r, const poly *a, const poly *b);

#endif
