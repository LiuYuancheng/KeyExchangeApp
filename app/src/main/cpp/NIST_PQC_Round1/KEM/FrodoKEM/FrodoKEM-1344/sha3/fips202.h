#ifndef FIPS202_H
#define FIPS202_H

#include <stdint.h>


#define SHAKE128_RATE 168
#define SHAKE256_RATE 136

void frodokem1344_shake128_absorb(uint64_t *s, const unsigned char *input, unsigned int inputByteLen);
void frodokem1344_shake128_squeezeblocks(unsigned char *output, unsigned long long nblocks, uint64_t *s);
void frodokem1344_shake128(unsigned char *output, unsigned long long outlen, const unsigned char *input,  unsigned long long inlen);

void frodokem1344_shake256_absorb(uint64_t *s, const unsigned char *input, unsigned int inputByteLen);
void frodokem1344_shake256_squeezeblocks(unsigned char *output, unsigned long long nblocks, uint64_t *s);
void frodokem1344_shake256(unsigned char *output, unsigned long long outlen, const unsigned char *input,  unsigned long long inlen);


#endif
