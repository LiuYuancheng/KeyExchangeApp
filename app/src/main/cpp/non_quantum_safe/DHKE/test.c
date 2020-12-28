#include <stdio.h>
#include <memory.h>
#include <openssl/bio.h>

#include "dh_ke.h"
#include "../../lib/format_helper.h"
#include "../../lib/timing_helper.h"

#define TEST_REPEATS	5

static int test_repeats = TEST_REPEATS;

unsigned long long int CPUHZ;

int main(int argc, char * argv[])
{
	unsigned char p[DH_PRIME_BITS/8],g[DH_PRIME_BITS/8];
	int p_bytes, g_bytes;
	unsigned long long int c1, c2, c = 0;

	if(argc > 1) test_repeats = atoi(argv[1]);

	CPUHZ = cpuhz();
	printf("DH setup testing ...\n");
	printf("=====================================================\n");
	printf("                   CPU cycles                Latency \n");
	printf("----------------------------------------------------\n");
	for(int n = 0; n < test_repeats; n ++)
	{
		c1 = currentcycles();
		if(DH_setup(p, &p_bytes, g, &g_bytes) != 0) return -1;
		c2 = currentcycles();
		c += c2 - c1;
		printf("%5d:%20s CC%20s ms\n",n + 1, format(c2-c1), format((c2-c1)/(double)CPUHZ*1000,2));
	}

	c = c/test_repeats;
	printf("-----------------------------------------------------\n");
	printf("%5s:%20s CC%20s ms\n","mean", format(c), format(c/(double)CPUHZ * 1000, 2));
	printf("=====================================================\n");

//	BIO_dump_fp(stdout, p, p_bytes);
//	BIO_dump_fp(stdout, p, p_bytes);

	return 0;
}
