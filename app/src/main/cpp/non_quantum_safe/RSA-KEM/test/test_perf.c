#include <string.h>
#include "../rsa_kem.h"
#include "rng.h"
#include <ctime>
#include "format_helper.h"
#include "timing_helper.h"

#define TEST_REPEATS	5



int main()
{
    unsigned char pk[RSA_CRYPTO_PUBLICKEYBYTES],sk[RSA_CRYPTO_SECRETKEYBYTES];
    unsigned char ss0[RSA_CRYPTO_BYTES], ss1[RSA_CRYPTO_BYTES],  ct[RSA_CRYPTO_CIPHERTEXTBYTES];
    unsigned long long  cycleA = 0, cycleB = 0, cycleC=0, cycle0, cycle1, cycle2, cycle3;

    char randbytes[20] = {0};

    srand((unsigned)time(NULL));
    sprintf(randbytes, "%d", rand());
    randombytes_init((unsigned char *)randbytes, (unsigned char *)"rsa", 256);

    unsigned long long CPUHZ = cpuhz();

    printf("------------------------------------------------------------------------------------------------------------------------------\n");
    printf("|%6s  %21s Key Generation\t%18s Key Encapsulation\t%18s Key Decapsulation |\n", "NO", RSA_CRYPTO_ALGNAME,RSA_CRYPTO_ALGNAME,RSA_CRYPTO_ALGNAME);
    printf("------------------------------------------------------------------------------------------------------------------------------\n");
    for(int n = 0; n < TEST_REPEATS; n ++)
    {
	    cycle0 = currentcycles();
	    RSA_crypto_kem_keypair(pk, sk);
	    cycle1 = currentcycles();
	    RSA_crypto_kem_enc(ct, ss0, pk);
	    cycle2 = currentcycles();
	    RSA_crypto_kem_dec(ss1, ct, sk);
	    cycle3 = currentcycles();
	    printf("|%6d  %12s CC/OP  %10s ms/OP\t%12s CC/OP  %10s ms/OP\t%12s CC/OP  %10s ms/OP |\n",n+1, format(cycle1-cycle0), format((cycle1-cycle0)/(double)CPUHZ * 1000, 2), format(cycle2-cycle1), format((cycle2-cycle1)/(double)CPUHZ * 1000, 2), format(cycle3-cycle2), format((cycle3-cycle2)/(double)CPUHZ * 1000, 2));
	    cycleA += cycle1 - cycle0;
	    cycleB += cycle2 - cycle1;
	    cycleC += cycle3 - cycle2;
    }
    cycleA = cycleA/TEST_REPEATS;
    cycleB = cycleB/TEST_REPEATS;
    cycleC = cycleC/TEST_REPEATS;
    printf("------------------------------------------------------------------------------------------------------------------------------\n");
    printf("|%6s  %12s CC/OP  %10s ms/OP\t%12s CC/OP  %10s ms/OP\t%12s CC/OP  %10s ms/OP |\n", "Speed", format(cycleA), format(cycleA/(double)CPUHZ * 1000, 2), format(cycleB), format(cycleB/(double)CPUHZ * 1000, 2), format(cycleC), format(cycleC/(double)CPUHZ * 1000, 2));
    printf("------------------------------------------------------------------------------------------------------------------------------\n");

    return 0;

}

