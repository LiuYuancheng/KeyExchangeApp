#include <stdio.h>
#include <string.h>

#include "dh_ke.h"


int main()
{
	int p_bytes, g_bytes;
	unsigned char P[DH_P_BYTES], G[DH_G_BYTES];
	unsigned char pk1[DH_PUBLICKEYBYTES], sk1[DH_SECRETKEYBYTES], pk2[DH_PUBLICKEYBYTES], sk2[DH_SECRETKEYBYTES];
	unsigned char sd1[DH_BYTES], sd2[DH_BYTES];

	DH_setup(P, &p_bytes, G, &g_bytes);
	
	printf("%d\n",DH_keypair(pk1, sk1, P, G));
	printf("%d\n",DH_keypair(pk2, sk2, P, G));

	DH_compute(sd1, pk1, sk2, P, G);
	DH_compute(sd2, pk2, sk1, P, G);

	if(memcmp(sd1, sd2, DH_BYTES) == 0)
		printf("correctness test passed.\n");
	else
		printf("correctness test failed.\n");

	return 0;
}


