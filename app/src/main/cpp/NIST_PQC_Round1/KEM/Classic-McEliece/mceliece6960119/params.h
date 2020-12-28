#ifndef CM_PARAMS_H
#define CM_PARAMS_H

#define CM_GFBITS 13
#define CM_SYS_N 6960
#define CM_SYS_T 119

#define CM_COND_BYTES ((1 << (CM_GFBITS-4))*(2*CM_GFBITS - 1))
#define CM_IRR_BYTES (CM_SYS_T * 2)

#define CM_PK_NROWS (CM_SYS_T*CM_GFBITS) 
#define CM_PK_NCOLS (CM_SYS_N - CM_PK_NROWS)
#define CM_PK_ROW_BYTES ((CM_PK_NCOLS + 7)/8)

#define CM_SK_BYTES (CM_SYS_N/8 + CM_IRR_BYTES + CM_COND_BYTES)
#define CM_SYND_BYTES ((CM_PK_NROWS + 7)/8)

#define CM_GFMASK ((1 << CM_GFBITS) - 1)

#endif

