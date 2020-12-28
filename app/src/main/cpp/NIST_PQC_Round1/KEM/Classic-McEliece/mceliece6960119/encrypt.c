/*
  This file is for Niederreiter encryption
*/

#include "encrypt.h"

#include "util.h"
#include "params.h"
#include "randombytes.h"

#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "gf.h"

static inline uint32_t same_mask(uint16_t x, uint16_t y)
{
	uint32_t mask;

	mask = x ^ y;
	mask -= 1;
	mask >>= 31;
	mask = -mask;

	return mask;
}

/* output: e, an error vector of weight t */
static void gen_e(unsigned char *e)
{
	int i, j, eq, count;

	uint16_t ind_[ CM_SYS_T*2 ];
	uint16_t ind[ CM_SYS_T*2 ];
	unsigned char mask;	
	unsigned char val[ CM_SYS_T ];	

	while (1)
	{
		CM_randombytes((unsigned char *) ind_, sizeof(ind_));

		for (i = 0; i < CM_SYS_T*2; i++)
			ind_[i] &= CM_GFMASK;

		// moving and counting indices in the correct range

		count = 0;
		for (i = 0; i < CM_SYS_T*2; i++)
			if (ind_[i] < CM_SYS_N)
				ind[ count++ ] = ind_[i];
		
		if (count < CM_SYS_T) continue;

		// check for repetition

		eq = 0;

		for (i = 1; i < CM_SYS_T; i++) for (j = 0; j < i; j++)
			if (ind[i] == ind[j]) 
				eq = 1;

		if (eq == 0)
			break;
	}

	for (j = 0; j < CM_SYS_T; j++)
		val[j] = 1 << (ind[j] & 7);

	for (i = 0; i < CM_SYS_N/8; i++) 
	{
		e[i] = 0;

		for (j = 0; j < CM_SYS_T; j++)
		{
			mask = same_mask(i, (ind[j] >> 3));

			e[i] |= val[j] & mask;
		}
	}
}

/* input: public key pk, error vector e */
/* output: syndrome s */
void syndrome(unsigned char *s, const unsigned char *pk, unsigned char *e)
{
	unsigned char b, row[CM_SYS_N/8];
	const unsigned char *pk_ptr = pk;

	int i, j, tail = CM_PK_NROWS % 8;

	for (i = 0; i < CM_SYND_BYTES; i++)
		s[i] = 0;

	for (i = 0; i < CM_PK_NROWS; i++)	
	{
		for (j = 0; j < CM_SYS_N/8; j++) 
			row[j] = 0;

		for (j = 0; j < CM_PK_ROW_BYTES; j++) 
			row[ CM_SYS_N/8 - CM_PK_ROW_BYTES + j ] = pk_ptr[j];

		for (j = CM_SYS_N/8-1; j >= CM_SYS_N/8 - CM_PK_ROW_BYTES; j--) 
			row[ j ] = (row[ j ] << tail) | (row[j-1] >> (8-tail));

		row[i/8] |= 1 << (i%8);
		
		b = 0;
		for (j = 0; j < CM_SYS_N/8; j++)
			b ^= row[j] & e[j];

		b ^= b >> 4;
		b ^= b >> 2;
		b ^= b >> 1;
		b &= 1;

		s[ i/8 ] |= (b << (i%8));

		pk_ptr += CM_PK_ROW_BYTES;
	}
}

void encrypt(unsigned char *s, const unsigned char *pk, unsigned char *e)
{
	gen_e(e);

#ifdef KAT
  {
    int k;
    printf("encrypt e: positions");
    for (k = 0;k < CM_SYS_N;++k)
      if (e[k/8] & (1 << (k&7)))
        printf(" %d",k);
    printf("\n");
  }
#endif

	syndrome(s, pk, e);
}

