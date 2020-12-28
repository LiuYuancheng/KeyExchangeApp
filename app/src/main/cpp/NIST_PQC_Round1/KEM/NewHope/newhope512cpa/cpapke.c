#include <stdio.h>
#include "api.h"
#include "poly.h"
#include "lib/rng.h"
#include "fips202.h"

/*************************************************
* Name:        encode_pk
* 
* Description: Serialize the public key as concatenation of the
*              serialization of the polynomial pk and the public seed
*              used to generete the polynomial a.
*
* Arguments:   unsigned char *r:          pointer to the output serialized public key
*              const poly *pk:            pointer to the input public-key polynomial
*              const unsigned char *seed: pointer to the input public seed
**************************************************/
static void encode_pk(unsigned char *r, const poly *pk, const unsigned char *seed)
{
  int i;
  NewHope_poly_tobytes(r, pk);
  for(i=0;i<NEWHOPE_SYMBYTES;i++)
    r[NEWHOPE_POLYBYTES+i] = seed[i];
}

/*************************************************
* Name:        decode_pk
* 
* Description: De-serialize the public key; inverse of encode_pk
*
* Arguments:   poly *pk:               pointer to output public-key polynomial
*              unsigned char *seed:    pointer to output public seed
*              const unsigned char *r: pointer to input byte array
**************************************************/
static void decode_pk(poly *pk, unsigned char *seed, const unsigned char *r)
{
  int i;
  NewHope_poly_frombytes(pk, r);
  for(i=0;i<NEWHOPE_SYMBYTES;i++)
    seed[i] = r[NEWHOPE_POLYBYTES+i];
}

/*************************************************
* Name:        encode_c
* 
* Description: Serialize the ciphertext as concatenation of the
*              serialization of the polynomial b and serialization
*              of the compressed polynomial v
*
* Arguments:   - unsigned char *r: pointer to the output serialized ciphertext
*              - const poly *b:    pointer to the input polynomial b
*              - const poly *v:    pointer to the input polynomial v
**************************************************/
static void encode_c(unsigned char *r, const poly *b, const poly *v)
{
  NewHope_poly_tobytes(r,b);
  NewHope_poly_compress(r+NEWHOPE_POLYBYTES,v);
}

/*************************************************
* Name:        decode_c
* 
* Description: de-serialize the ciphertext; inverse of encode_c
*
* Arguments:   - poly *b:                pointer to output polynomial b
*              - poly *v:                pointer to output polynomial v
*              - const unsigned char *r: pointer to input byte array
**************************************************/
static void decode_c(poly *b, poly *v, const unsigned char *r)
{
  NewHope_poly_frombytes(b, r);
  NewHope_poly_decompress(v, r+NEWHOPE_POLYBYTES);
}

/*************************************************
* Name:        gen_a
* 
* Description: Deterministically generate public polynomial a from seed
*
* Arguments:   - poly *a:                   pointer to output polynomial a
*              - const unsigned char *seed: pointer to input seed
**************************************************/
static void gen_a(poly *a, const unsigned char *seed)
{
  NewHope_poly_uniform(a,seed);
}


/*************************************************
* Name:        cpapke_keypair
* 
* Description: Generates public and private key 
*              for the CPA public-key encryption scheme underlying
*              the NewHope KEMs
*
* Arguments:   - unsigned char *pk: pointer to output public key
*              - unsigned char *sk: pointer to output private key
**************************************************/
void cpapke_keypair(unsigned char *pk,
                    unsigned char *sk)
{
  poly ahat, ehat, ahat_shat, bhat, shat;
  unsigned char z[2*NEWHOPE_SYMBYTES];
  unsigned char *publicseed = z;
  unsigned char *noiseseed = z+NEWHOPE_SYMBYTES;

  randombytes(z, NEWHOPE_SYMBYTES);
  NewHope_shake256(z, 2*NEWHOPE_SYMBYTES, z, NEWHOPE_SYMBYTES);

  gen_a(&ahat, publicseed);

  NewHope_poly_sample(&shat, noiseseed, 0);
  NewHope_poly_ntt(&shat);

  NewHope_poly_sample(&ehat, noiseseed, 1);
  NewHope_poly_ntt(&ehat);

  NewHope_poly_mul_pointwise(&ahat_shat, &shat, &ahat);
  NewHope_poly_add(&bhat, &ehat, &ahat_shat);

  NewHope_poly_tobytes(sk, &shat);
  encode_pk(pk, &bhat, publicseed);
}

/*************************************************
* Name:        cpapke_enc
* 
* Description: Encryption function of
*              the CPA public-key encryption scheme underlying
*              the NewHope KEMs
*
* Arguments:   - unsigned char *c:          pointer to output ciphertext
*              - const unsigned char *m:    pointer to input message (of length NEWHOPE_SYMBYTES bytes)
*              - const unsigned char *pk:   pointer to input public key
*              - const unsigned char *coin: pointer to input random coins used as seed
*                                           to deterministically generate all randomness
**************************************************/
void cpapke_enc(unsigned char *c,
                const unsigned char *m,
                const unsigned char *pk,
                const unsigned char *coin)
{
  poly sprime, eprime, vprime, ahat, bhat, eprimeprime, uhat, v;
  unsigned char publicseed[NEWHOPE_SYMBYTES];

  NewHope_poly_frommsg(&v, m);

  decode_pk(&bhat, publicseed, pk);
  gen_a(&ahat, publicseed);

  NewHope_poly_sample(&sprime, coin, 0);
  NewHope_poly_sample(&eprime, coin, 1);
  NewHope_poly_sample(&eprimeprime, coin, 2);

  NewHope_poly_ntt(&sprime);
  NewHope_poly_ntt(&eprime);

  NewHope_poly_mul_pointwise(&uhat, &ahat, &sprime);
  NewHope_poly_add(&uhat, &uhat, &eprime);

  NewHope_poly_mul_pointwise(&vprime, &bhat, &sprime);
  NewHope_poly_invntt(&vprime);

  NewHope_poly_add(&vprime, &vprime, &eprimeprime);
  NewHope_poly_add(&vprime, &vprime, &v); // add message

  encode_c(c, &uhat, &vprime);
}


/*************************************************
* Name:        cpapke_dec
* 
* Description: Decryption function of
*              the CPA public-key encryption scheme underlying
*              the NewHope KEMs
*
* Arguments:   - unsigned char *m:        pointer to output decrypted message
*              - const unsigned char *c:  pointer to input ciphertext
*              - const unsigned char *sk: pointer to input secret key
**************************************************/
void cpapke_dec(unsigned char *m,
                const unsigned char *c,
                const unsigned char *sk)
{
  poly vprime, uhat, tmp, shat;

  NewHope_poly_frombytes(&shat, sk);

  decode_c(&uhat, &vprime, c);
  NewHope_poly_mul_pointwise(&tmp, &shat, &uhat);
  NewHope_poly_invntt(&tmp);

  NewHope_poly_sub(&tmp, &tmp, &vprime);

  NewHope_poly_tomsg(m, &tmp);
}
