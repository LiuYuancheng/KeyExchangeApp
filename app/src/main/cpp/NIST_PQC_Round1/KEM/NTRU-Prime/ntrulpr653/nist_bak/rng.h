/*
   rng.h
   Created by Bassham, Lawrence E (Fed) on 8/29/17.
   Copyright © 2017 Bassham, Lawrence E (Fed). All rights reserved.
*/

#ifndef NTRUPRIME_rng_h
#define NTRUPRIME_rng_h

#include <stdio.h>

#define RNG_SUCCESS      0
#define RNG_BAD_MAXLEN  -1
#define RNG_BAD_OUTBUF  -2
#define RNG_BAD_REQ_LEN -3

typedef struct {
    unsigned char   buffer[16];
    int             buffer_pos;
    unsigned long   length_remaining;
    unsigned char   key[32];
    unsigned char   ctr[16];
} NTRUPrime_AES_XOF_struct;

typedef struct {
    unsigned char   Key[32];
    unsigned char   V[16];
    int             reseed_counter;
} NTRUPrime_AES256_CTR_DRBG_struct;


void
NTRUPrime_AES256_CTR_DRBG_Update(unsigned char *provided_data,
                       unsigned char *Key,
                       unsigned char *V);

int
NTRUPrime_seedexpander_init(NTRUPrime_AES_XOF_struct *ctx,
                  unsigned char *seed,
                  unsigned char *diversifier,
                  unsigned long maxlen);

int
NTRUPrime_seedexpander(NTRUPrime_AES_XOF_struct *ctx, unsigned char *x, unsigned long xlen);

void
NTRUPrime_randombytes_init(unsigned char *entropy_input,
                 unsigned char *personalization_string,
                 int security_strength);

int
NTRUPrime_randombytes(unsigned char *x, unsigned long long xlen);

#endif /* rng_h */
