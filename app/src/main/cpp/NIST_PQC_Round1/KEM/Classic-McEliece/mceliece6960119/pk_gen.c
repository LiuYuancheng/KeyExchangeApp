/*
  This file is for public-key generation
*/

#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "controlbits.h"
#include "pk_gen.h"
#include "params.h"
#include "benes.h"
#include "root.h"
#include "util.h"

/* input: secret key sk */
/* output: public key pk */
int pk_gen(unsigned char * pk, unsigned char * sk, uint32_t * perm)
{
	unsigned char *pk_ptr = pk;

	int i, j, k;
	int row, c, tail;

	uint64_t buf[ 1 << CM_GFBITS ];

	unsigned char mat[ CM_GFBITS * CM_SYS_T ][ CM_SYS_N/8 ];
	unsigned char mask;
	unsigned char b;

	gf g[ CM_SYS_T+1 ]; // Goppa polynomial
	gf L[ CM_SYS_N ]; // support
	gf inv[ CM_SYS_N ];

	//

	g[ CM_SYS_T ] = 1;

	for (i = 0; i < CM_SYS_T; i++) { g[i] = load2(sk); g[i] &= CM_GFMASK; sk += 2; }

	for (i = 0; i < (1 << CM_GFBITS); i++)
	{
		buf[i] = perm[i];
		buf[i] <<= 31;
		buf[i] |= i;
	}

	sort_63b(1 << CM_GFBITS, buf);

	for (i = 0; i < (1 << CM_GFBITS); i++) perm[i] = buf[i] & CM_GFMASK;
	for (i = 0; i < CM_SYS_N;         i++) L[i] = bitrev(perm[i]);

	// filling the matrix

	root(inv, g, L);
		
	for (i = 0; i < CM_SYS_N; i++)
		inv[i] = gf_inv(inv[i]);

	for (i = 0; i < CM_PK_NROWS; i++)
	for (j = 0; j < CM_SYS_N/8; j++)
		mat[i][j] = 0;

	for (i = 0; i < CM_SYS_T; i++)
	{
		for (j = 0; j < CM_SYS_N; j+=8)
		for (k = 0; k < CM_GFBITS;  k++)
		{
			b  = (inv[j+7] >> k) & 1; b <<= 1;
			b |= (inv[j+6] >> k) & 1; b <<= 1;
			b |= (inv[j+5] >> k) & 1; b <<= 1;
			b |= (inv[j+4] >> k) & 1; b <<= 1;
			b |= (inv[j+3] >> k) & 1; b <<= 1;
			b |= (inv[j+2] >> k) & 1; b <<= 1;
			b |= (inv[j+1] >> k) & 1; b <<= 1;
			b |= (inv[j+0] >> k) & 1;

			mat[ i*CM_GFBITS + k ][ j/8 ] = b;
		}

		for (j = 0; j < CM_SYS_N; j++)
			inv[j] = gf_mul(inv[j], L[j]);

	}

	// gaussian elimination

	for (i = 0; i < (CM_GFBITS * CM_SYS_T + 7) / 8; i++)
	for (j = 0; j < 8; j++)
	{
		row = i*8 + j;			

		if (row >= CM_GFBITS * CM_SYS_T)
			break;

		for (k = row + 1; k < CM_GFBITS * CM_SYS_T; k++)
		{
			mask = mat[ row ][ i ] ^ mat[ k ][ i ];
			mask >>= j;
			mask &= 1;
			mask = -mask;

			for (c = 0; c < CM_SYS_N/8; c++)
				mat[ row ][ c ] ^= mat[ k ][ c ] & mask;
		}

		if ( ((mat[ row ][ i ] >> j) & 1) == 0 ) // return if not systematic
		{
			return -1;
		}

		for (k = 0; k < CM_GFBITS * CM_SYS_T; k++)
		{
			if (k != row)
			{
				mask = mat[ k ][ i ] >> j;
				mask &= 1;
				mask = -mask;

				for (c = 0; c < CM_SYS_N/8; c++)
					mat[ k ][ c ] ^= mat[ row ][ c ] & mask;
			}
		}
	}

	tail = (CM_GFBITS * CM_SYS_T) % 8;

	for (i = 0; i < CM_GFBITS * CM_SYS_T; i++)
	{
		for (j = (CM_GFBITS * CM_SYS_T - 1)/8; j < CM_SYS_N/8 - 1; j++)
			*pk_ptr++ = (mat[i][j] >> tail) | (mat[i][j+1] << (8-tail));

		*pk_ptr++ = (mat[i][j] >> tail);
	}

	return 0;
}

