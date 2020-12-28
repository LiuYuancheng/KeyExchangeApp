#ifndef KYBER_FIPS202_H
#define KYBER_FIPS202_H

#include <stdint.h>

#define SHAKE128_RATE 168
#define SHAKE256_RATE 136
#define SHA3_256_RATE 136
#define SHA3_512_RATE  72

void KYBER_shake128_absorb(uint64_t *s, const unsigned char *input, unsigned int inputByteLen);
void KYBER_shake128_squeezeblocks(unsigned char *output, unsigned long long nblocks, uint64_t *s);

void KYBER_shake256(unsigned char *output, unsigned long long outlen, const unsigned char *input,  unsigned long long inlen);

void KYBER_sha3_256(unsigned char *output, const unsigned char *input,  unsigned long long inlen);
void KYBER_sha3_512(unsigned char *output, const unsigned char *input,  unsigned long long inlen);

#endif
