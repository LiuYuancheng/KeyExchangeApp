#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dh_ke.h"

#include "mbedtls/base64.h"

int main(int argc, char * argv[])
{
	int i;
	int pbytes, gbytes;
	size_t p_bytes, g_bytes, p_bytes_2, g_bytes_2;
	FILE * f_p, * f_g;
	unsigned char *p, *g, *p2, *g2, *p_base64, *g_base64;
/*
	srand((unsigned)time(NULL));
        sprintf(randbytes, "%d", rand());
        randombytes_init((unsigned char *)randbytes, (unsigned char *)"kep", 256);
*/

	p = (unsigned char *)malloc(DH_P_BYTES);
	g = (unsigned char *)malloc(DH_G_BYTES);
	p2 = (unsigned char *)malloc(DH_P_BYTES);
	g2 = (unsigned char *)malloc(DH_G_BYTES);

	p_base64 = (unsigned char *)malloc(2 * DH_P_BYTES);
	g_base64 = (unsigned char *)malloc(2 * DH_G_BYTES);
	
	DH_setup(p, &pbytes, g, &gbytes);
	
	mbedtls_base64_encode(p_base64, 2 * DH_P_BYTES, &p_bytes, p, DH_P_BYTES);
	mbedtls_base64_encode(g_base64, 2 * DH_G_BYTES + 10, &g_bytes, g, DH_G_BYTES);

	mbedtls_base64_decode(p2, 2 * DH_P_BYTES, &p_bytes_2, p_base64, p_bytes);
	mbedtls_base64_decode(g2, 2 * DH_G_BYTES, &g_bytes_2, g_base64, g_bytes);
		
	if(p_bytes_2 == DH_P_BYTES && memcmp(p, p2, DH_P_BYTES) == 0)
		printf("p encoding correct\n");
	if(g_bytes_2 == DH_G_BYTES && memcmp(g, g2, DH_G_BYTES) == 0)
		printf("g encoding correct\n");


//	printf("Public Key:\n%s\n", pk_base64);
//	printf("Private Key:\n%s\n", sk_base64);



	f_p = fopen(argv[1], "w");
	fwrite(p_base64, p_bytes, 1, f_p);
	printf("Param P (%s) generated.\n", argv[1]);
	//fwrite(pk, pk_len, 1, f_pk);
	f_g = fopen(argv[2], "w");
	fwrite(g_base64, g_bytes, 1, f_g);
	printf("Param G (%s) generated.\n", argv[2]);
	//
	//fwrite(sk, sk_len, 1, f_sk);
	fclose(f_p);
	fclose(f_g);


	free(p);
	free(g);
	free(p2);
	free(g2);
	free(p_base64);
	free(g_base64);
	return 0;

}
