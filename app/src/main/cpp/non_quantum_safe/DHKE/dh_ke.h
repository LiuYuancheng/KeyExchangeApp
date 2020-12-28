
#ifndef __DH_KE_H__
#define __DH_KE_H__

//#define DH_PRIME_BITS   15360
#define DH_PRIME_BITS   3072
//#define DH_PRIME_BITS   				1024
#define DH_P_BYTES						(DH_PRIME_BITS/8)
#define DH_G_BYTES						1

#define DH_PUBLICKEYBYTES				DH_P_BYTES
#define DH_SECRETKEYBYTES				DH_P_BYTES
#define DH_BYTES						32



int DH_setup(unsigned char *p, int * p_bytes, unsigned char *g, int *g_bytes);

int DH_keypair(unsigned char *pk, unsigned char *sk, unsigned char *p, unsigned char *g);

int DH_compute(unsigned char *sd, unsigned char *pk, unsigned char *sk, unsigned char *p, unsigned char *g);

int DH_compute_and_derive(unsigned char *sd, unsigned char *pk, unsigned char *sk, unsigned char *p, unsigned char *g);

#endif
