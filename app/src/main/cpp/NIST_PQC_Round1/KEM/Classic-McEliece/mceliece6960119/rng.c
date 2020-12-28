/*
   rng.c
   Created by Bassham, Lawrence E (Fed) on 8/29/17.
   Copyright © 2017 Bassham, Lawrence E (Fed). All rights reserved.
*/

#include <string.h>
#include "rng.h"
#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>

AES256_CTR_DRBG_struct  CM_DRBG_ctx;

void    CM_AES256_ECB(unsigned char *key, unsigned char *ctr, unsigned char *buffer);

/*
 seedexpander_init()
 ctx            - stores the current state of an instance of the seed expander
 seed           - a 32 byte random value
 diversifier    - an 8 byte diversifier
 maxlen         - maximum number of bytes (less than 2**32) generated under this seed and diversifier
 */
int
CM_seedexpander_init(AES_XOF_struct *ctx,
                  unsigned char *seed,
                  unsigned char *diversifier,
                  unsigned long maxlen)
{
    if ( maxlen >= 0x100000000 )
        return RNG_BAD_MAXLEN;
    
    ctx->length_remaining = maxlen;
    
    memcpy(ctx->key, seed, 32);
    
    memcpy(ctx->ctr, diversifier, 8);
    ctx->ctr[11] = maxlen % 256;
    maxlen >>= 8;
    ctx->ctr[10] = maxlen % 256;
    maxlen >>= 8;
    ctx->ctr[9] = maxlen % 256;
    maxlen >>= 8;
    ctx->ctr[8] = maxlen % 256;
    memset(ctx->ctr+12, 0x00, 4);
    
    ctx->buffer_pos = 16;
    memset(ctx->buffer, 0x00, 16);
    
    return RNG_SUCCESS;
}

/*
 seedexpander()
    ctx  - stores the current state of an instance of the seed expander
    x    - returns the XOF data
    xlen - number of bytes to return
 */
int
CM_seedexpander(AES_XOF_struct *ctx, unsigned char *x, unsigned long xlen)
{
    unsigned long   offset;
    int i;
    
    if ( x == NULL )
        return RNG_BAD_OUTBUF;
    if ( xlen >= ctx->length_remaining )
        return RNG_BAD_REQ_LEN;
    
    ctx->length_remaining -= xlen;
    
    offset = 0;
    while ( xlen > 0 ) {
        if ( xlen <= (16-ctx->buffer_pos) ) { /* buffer has what we need */
            memcpy(x+offset, ctx->buffer+ctx->buffer_pos, xlen);
            ctx->buffer_pos += xlen;
            
            return RNG_SUCCESS;
        }
        
        /* take what's in the buffer */
        memcpy(x+offset, ctx->buffer+ctx->buffer_pos, 16-ctx->buffer_pos);
        xlen -= 16-ctx->buffer_pos;
        offset += 16-ctx->buffer_pos;
        
        CM_AES256_ECB(ctx->key, ctx->ctr, ctx->buffer);
        ctx->buffer_pos = 0;
        
        /* increment the counter */
        for (i=15; i>=12; i--) {
            if ( ctx->ctr[i] == 0xff )
                ctx->ctr[i] = 0x00;
            else {
                ctx->ctr[i]++;
                break;
            }
        }
        
    }
    
    return RNG_SUCCESS;
}


void CM_handleErrors(void)
{
    ERR_print_errors_fp(stderr);
    abort();
}

/*
   Use whatever AES implementation you have. This uses AES from openSSL library
      key - 256-bit AES key
      ctr - a 128-bit plaintext value
      buffer - a 128-bit ciphertext value
*/
void
CM_AES256_ECB(unsigned char *key, unsigned char *ctr, unsigned char *buffer)
{
    EVP_CIPHER_CTX *ctx;
    
    int len;
    
    /* Create and initialise the context */
    if(!(ctx = EVP_CIPHER_CTX_new())) CM_handleErrors();
    
    if(1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_ecb(), NULL, key, NULL))
        CM_handleErrors();
    
    if(1 != EVP_EncryptUpdate(ctx, buffer, &len, ctr, 16))
        CM_handleErrors();
    
    /* Clean up */
    EVP_CIPHER_CTX_free(ctx);
}

void
CM_randombytes_init(unsigned char *entropy_input,
                 unsigned char *personalization_string,
                 int security_strength)
{
    unsigned char   seed_material[48];
    int i;
    
    memcpy(seed_material, entropy_input, 48);
    if (personalization_string)
        for (i=0; i<48; i++)
            seed_material[i] ^= personalization_string[i];
    memset(CM_DRBG_ctx.Key, 0x00, 32);
    memset(CM_DRBG_ctx.V, 0x00, 16);
    CM_AES256_CTR_DRBG_Update(seed_material, CM_DRBG_ctx.Key, CM_DRBG_ctx.V);
    CM_DRBG_ctx.reseed_counter = 1;
}

int
CM_randombytes(unsigned char *x, unsigned long long xlen)
{
    unsigned char   block[16];
    int             i = 0;
    int j;
    
    while ( xlen > 0 ) {
        /* increment V */
        for (j=15; j>=0; j--) {
            if ( CM_DRBG_ctx.V[j] == 0xff )
                CM_DRBG_ctx.V[j] = 0x00;
            else {
                CM_DRBG_ctx.V[j]++;
                break;
            }
        }
        CM_AES256_ECB(CM_DRBG_ctx.Key, CM_DRBG_ctx.V, block);
        if ( xlen > 15 ) {
            memcpy(x+i, block, 16);
            i += 16;
            xlen -= 16;
        }
        else {
            memcpy(x+i, block, xlen);
            xlen = 0;
        }
    }
    CM_AES256_CTR_DRBG_Update(NULL, CM_DRBG_ctx.Key, CM_DRBG_ctx.V);
    CM_DRBG_ctx.reseed_counter++;
    
    return RNG_SUCCESS;
}

void
CM_AES256_CTR_DRBG_Update(unsigned char *provided_data,
                       unsigned char *Key,
                       unsigned char *V)
{
    unsigned char   temp[48];
    int i;
    int j;
    
    for (i=0; i<3; i++) {
        /* increment V */
        for (j=15; j>=0; j--) {
            if ( V[j] == 0xff )
                V[j] = 0x00;
            else {
                V[j]++;
                break;
            }
        }
        
        CM_AES256_ECB(Key, V, temp+16*i);
    }
    if ( provided_data != NULL )
        for (i=0; i<48; i++)
            temp[i] ^= provided_data[i];
    memcpy(Key, temp, 32);
    memcpy(V, temp+32, 16);
}