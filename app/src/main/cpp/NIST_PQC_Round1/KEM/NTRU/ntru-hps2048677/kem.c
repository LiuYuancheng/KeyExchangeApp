#include "rng.h"
#include "fips202.h"
#include "params.h"
#include "verify.h"
#include "owcpa.h"

// API FUNCTIONS 
int NTRU_crypto_kem_keypair(unsigned char *pk, unsigned char *sk)
{
  unsigned char seed[NTRU_SAMPLE_FG_BYTES];

  randombytes(seed, NTRU_SAMPLE_FG_BYTES);
  owcpa_keypair(pk, sk, seed);

  randombytes(sk+NTRU_OWCPA_SECRETKEYBYTES, NTRU_PRFKEYBYTES);

  return 0;
}

int NTRU_crypto_kem_enc(unsigned char *c, unsigned char *k, const unsigned char *pk)
{
  unsigned char rm[NTRU_OWCPA_MSGBYTES];
  unsigned char rm_seed[NTRU_SAMPLE_RM_BYTES];

  randombytes(rm_seed, NTRU_SAMPLE_RM_BYTES);
  owcpa_samplemsg(rm, rm_seed);

  sha3_256(k, rm, NTRU_OWCPA_MSGBYTES);

  owcpa_enc(c, rm, pk);

  return 0;
}

int NTRU_crypto_kem_dec(unsigned char *k, const unsigned char *c, const unsigned char *sk)
{
  int i, fail;
  unsigned char rm[NTRU_OWCPA_MSGBYTES];
  unsigned char buf[NTRU_PRFKEYBYTES+NTRU_CIPHERTEXTBYTES];
  unsigned char *cmp = buf+NTRU_PRFKEYBYTES;

  fail = owcpa_dec(rm, c, sk);
  /* If fail = 0 then c = Enc(h, rm), there is no need to re-encapsulate. */
  /* See comment in owcpa_dec for details.                                */

  sha3_256(k, rm, NTRU_OWCPA_MSGBYTES);

  /* shake(secret PRF key || input ciphertext) */
  for(i=0;i<NTRU_PRFKEYBYTES;i++)
    buf[i] = sk[i+NTRU_OWCPA_SECRETKEYBYTES];
  for(i=0;i<NTRU_CIPHERTEXTBYTES;i++)
    cmp[i] = c[i];
  sha3_256(rm, cmp, NTRU_PRFKEYBYTES+NTRU_CIPHERTEXTBYTES);

  cmov(k, rm, NTRU_SHAREDKEYBYTES, fail);

  return 0;
}
