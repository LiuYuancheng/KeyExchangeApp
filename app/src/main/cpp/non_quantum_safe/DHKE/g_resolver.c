#include <openssl/bio.h>
#include <mbedtls/base64.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "dh_ke.h"

int main(int argc, char * argv[])
{
	int ret = 0;
	size_t len = 0, olen;
	unsigned char *k, *base64;
	FILE * fp = fopen(argv[1],"r");
	
	if(fp == NULL)
	{
		ret = -1;
		goto err;
	}
	fseek(fp, 0, SEEK_END);
	len = ftell(fp);
        base64 = (unsigned char *)malloc(len*2 + 10);
	if(base64 == NULL)
	{
		ret = -3;
		goto err;
	}
	rewind(fp);
        fread(base64, 1, len, fp);
        fclose(fp);

	if(mbedtls_base64_decode(base64 + len, len, &olen, base64, len))
	{
		ret = -4;
		goto err;
	}

        if(olen != DH_G_BYTES)
        {
		ret = -5;
		goto err;
	}
	k = base64 + len;

	BIO_dump_fp(stdout, k, DH_G_BYTES);
	printf("\n");




err:
	free(base64);
	fclose(fp);
	
	return 0;
}



