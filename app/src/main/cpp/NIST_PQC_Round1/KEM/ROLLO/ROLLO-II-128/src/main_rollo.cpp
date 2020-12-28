
#include <stdio.h>
#include "api.h"
#include "parameters.h"

int main() {

  printf("\n");
  printf("******************************\n");
  printf("%s\n", CRYPTO_ALGNAME);
  printf("******************************\n");

  printf("\n");
  printf("M: %d  |  ", PARAM_M);
  printf("N: %d  |  ", PARAM_N);
  printf("D: %d  |  ", PARAM_D);
  printf("R: %d  |  ", PARAM_R);
  printf("DFR: 2^-%d  |  ", PARAM_DFR);
  printf("Sec: %d bits", PARAM_SECURITY);
  printf("\n");


  unsigned char pk[PUBLIC_KEY_BYTES];
  unsigned char sk[SECRET_KEY_BYTES];
  unsigned char ct[CIPHERTEXT_BYTES];
  unsigned char ss1[SHARED_SECRET_BYTES];
  unsigned char ss2[SHARED_SECRET_BYTES];


  crypto_kem_keypair(pk, sk);
  crypto_kem_enc(ct, ss1, pk);
  crypto_kem_dec(ss2, ct, sk);


  printf("\n\nsecret1: ");
  for(int i = 0 ; i < SHARED_SECRET_BYTES ; ++i) printf("%02x", ss1[i]);

  printf("\nsecret2: ");
  for(int i = 0 ; i < SHARED_SECRET_BYTES ; ++i) printf("%02x", ss2[i]);
  printf("\n\n");

}

