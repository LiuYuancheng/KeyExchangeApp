#ifndef KYBER_VERIFY_H
#define KYBER_VERIFY_H

#include <stdio.h>

int kyber_verify(const unsigned char *a, const unsigned char *b, size_t len);

void kyber_cmov(unsigned char *r, const unsigned char *x, size_t len, unsigned char b);

#endif
