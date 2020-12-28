/*
  This file is for Niederreiter decryption
*/

#include <stdio.h>
#include "decrypt.h"

#include "params.h"
#include "benes.h"
#include "util.h"
#include "synd.h"
#include "root.h"
#include "gf.h"
#include "bm.h"

/* Niederreiter decryption with the Berlekamp decoder */
/* intput: sk, secret key */
/*         c, ciphertext */
/* output: e, error vector */
/* return: 0 for success; 1 for failure */
int decrypt(unsigned char *e, const unsigned char *sk, const unsigned char *c)
{
	int i, w = 0; 
	uint16_t check;	

	unsigned char r[ CM_SYS_N/8 ];

	gf g[ CM_SYS_T+1 ];
	gf L[ CM_SYS_N ];

	gf s[ CM_SYS_T*2 ];
	gf s_cmp[ CM_SYS_T*2 ];
	gf locator[ CM_SYS_T+1 ];
	gf images[ CM_SYS_N ];

	gf t;

	//

	for (i = 0; i < CM_SYND_BYTES; i++)       r[i] = c[i];
	r[i-1] &= (1 << ((CM_GFBITS * CM_SYS_T) % 8)) - 1;
	for (i = CM_SYND_BYTES; i < CM_SYS_N/8; i++) r[i] = 0;

	for (i = 0; i < CM_SYS_T; i++) { g[i] = load2(sk); g[i] &= CM_GFMASK; sk += 2; } g[ CM_SYS_T ] = 1;

	support_gen(L, sk);

	synd(s, g, L, r);

	bm(locator, s);

	root(images, locator, L);

	//
	
	for (i = 0; i < CM_SYS_N/8; i++) 
		e[i] = 0;

	for (i = 0; i < CM_SYS_N; i++)
	{
		t = gf_iszero(images[i]) & 1;

		e[ i/8 ] |= t << (i%8);
		w += t;

	}

#ifdef KAT
  {
    int k;
    printf("decrypt e: positions");
    for (k = 0;k < CM_SYS_N;++k)
      if (e[k/8] & (1 << (k&7)))
        printf(" %d",k);
    printf("\n");
  }
#endif
	
	synd(s_cmp, g, L, e);

	//

	check = w;
	check ^= CM_SYS_T;

	for (i = 0; i < CM_SYS_T*2; i++)
		check |= s[i] ^ s_cmp[i]; 

	check -= 1;
	check >>= 15;

	return check ^ 1;
}

