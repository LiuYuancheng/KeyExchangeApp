#include <string.h>
#include "../rsa_kem.h"
#include "rng.h"
#include <ctime>

int main()
{
    unsigned char pk[RSA_CRYPTO_PUBLICKEYBYTES],sk[RSA_CRYPTO_SECRETKEYBYTES];
    unsigned char ss0[RSA_CRYPTO_BYTES], ss1[RSA_CRYPTO_BYTES],  ct[RSA_CRYPTO_CIPHERTEXTBYTES];

    char randbytes[20] = {0};

    srand((unsigned)time(NULL));
    sprintf(randbytes, "%d", rand());
    randombytes_init((unsigned char *)randbytes, (unsigned char *)"rsa", 256);




    RSA_crypto_kem_keypair(pk, sk);
    BIO_dump_fp(stdout, pk, RSA_CRYPTO_PUBLICKEYBYTES);
    BIO_dump_fp(stdout, sk, RSA_CRYPTO_SECRETKEYBYTES);
    RSA_crypto_kem_enc(ct, ss0, pk);
    RSA_crypto_kem_dec(ss1, ct, sk);

    for(int i = 0; i < 32; i ++)
    {
        printf("%02X ", ss0[i]);
    }
    printf("\n");
    for(int i = 0; i < 32; i ++)
    {
        printf("%02X ", ss1[i]);
    }
    printf("\n");
    if(memcmp(ss0, ss1, 32) == 0)
        printf("OK\n");

    return 0;

}

