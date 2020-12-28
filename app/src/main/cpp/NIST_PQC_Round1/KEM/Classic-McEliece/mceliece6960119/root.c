/*
  This file is for evaluating a polynomial at one or more field elements
*/

#include "params.h"
#include "gf.h"

#include <stdio.h>

/* input: polynomial f and field element a */
/* return f(a) */
gf eval(gf *f, gf a)
{
	int i;
	gf r;
	
	r = f[ CM_SYS_T ];

	for (i = CM_SYS_T-1; i >= 0; i--)
	{
		r = gf_mul(r, a);
		r = gf_add(r, f[i]);
	}

	return r;
}

/* input: polynomial f and list of field elements L */
/* output: out = [ f(a) for a in L ] */
void root(gf *out, gf *f, gf *L)
{
	int i; 

	for (i = 0; i < CM_SYS_N; i++)
		out[i] = eval(f, L[i]);
}
