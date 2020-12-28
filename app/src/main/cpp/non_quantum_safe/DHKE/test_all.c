#include <openssl/dh.h>
#include <memory.h>
#include "../../lib/timing_helper.h"
#include "../../lib/format_helper.h"
#include "dh_ke.h"

#define TEST_REPEATS		25

int main() {
    DH *d1,*d2;
    BIO *b;
    BIGNUM *p, *g, *pk1, *pk2;


    int ret,size,i,len1,len2;
    unsigned char sharekey1[DH_PRIME_BITS/8],sharekey2[DH_PRIME_BITS/8];

    unsigned long long c1, c2, c3, c4, c_setup = 0, c_keygen_A = 0, c_keygen_B = 0, c_comp_A = 0, c_comp_B = 0;
    
    for(int n = 0; n < TEST_REPEATS; n ++)
    {
        d1 = DH_new();
        d2 = DH_new();
    	p    = BN_new();
    	g    = BN_new();
    	pk1 = BN_new();
    	pk2 = BN_new();

	printf("%3d", n + 1);

	c1 = currentcycles();
    	ret = DH_generate_parameters_ex(d1,DH_PRIME_BITS,DH_GENERATOR_2,NULL);   
        c2 = currentcycles();

        printf("%20s", format(c2 - c1));
        c_setup += c2 - c1;
        if(ret!=1) 
	{               //prime_len，g大于1，常见2和5
           printf("DH_generate_parameters_ex err!\n");
           return -1;
	}
    

    /* 检查密钥参数 */
   /* ret = DH_check(d1,&i);
    if(ret != 1) {
        printf("DH_check err!\n");
    if(&DH_CHECK_P_NOT_PRIME)
        printf("p value is not prime\n");
    if(i&DH_CHECK_P_NOT_SAFE_PRIME)
        printf("p value is not a safe prime\n");
    if (i&DH_UNABLE_TO_CHECK_GENERATOR)
        printf("unable to check the generator value\n");
    if (i&DH_NOT_SUITABLE_GENERATOR)
        printf("the g value is not a generator\n");
    }
    printf("DH parameters appear to be ok.\n");
    */
    /* 密钥大小 */
   // size=DH_size(d1);
   // printf("DH key1 size : %d\n",size);
    /* 生成公私钥 */
    c1 = currentcycles();
    ret=DH_generate_key(d1);
    c2 = currentcycles();
    c_keygen_A += c2 - c1;
    printf("%20s", format(c2-c1));
    if(ret!=1) {
        printf("DH_generate_key err!\n");
        return -1;
    }
    /* p和g为公开的密钥参数，因此可以拷贝 */
    DH_get0_pqg(d1, (const BIGNUM **) &p, NULL, (const BIGNUM **)&g);
    DH_set0_pqg(d2, p, NULL, g);

    /* 生成公私钥,用于测试生成共享密钥 */
    c1	= currentcycles();
    ret = DH_generate_key(d2);
    c2  = currentcycles();
    c_keygen_B += c2 - c1;
    printf("%20s", format(c2-c1));
    if(ret!=1) {
        printf("DH_generate_key err!\n");
        return -1;
    }
    /* 检查公钥 */
    /*
    ret=DH_check_pub_key(d1,d1->pub_key,&i);
    if(ret!=1) {
        if (i&DH_CHECK_PUBKEY_TOO_SMALL)
            printf("pub key too small \n");
        if (i&DH_CHECK_PUBKEY_TOO_LARGE)
            printf("pub key too large \n");
    }
    */

    DH_get0_key(d1, (const BIGNUM **)&pk1, NULL);
    DH_get0_key(d2, (const BIGNUM **)&pk2, NULL);

    /* 计算共享密钥 */
    c1 = currentcycles();
    len1 = DH_compute_key(sharekey1,pk2,d1);
    c2 = currentcycles();
    c_comp_A += c2 - c1;
    printf("%20s", format(c2-c1));
    c1 = currentcycles();
    len2 = DH_compute_key(sharekey2,pk1,d2);
    c2 = currentcycles();
    c_comp_B += c2 - c1;
    printf("%20s\n", format(c2-c1));
    if(len1 != len2) {
        printf("生成共享密钥失败1\n");
        return -1;
    }
    if(memcmp(sharekey1,sharekey2,len1)!=0) {
        printf("生成共享密钥失败2\n");
        return -1;
    }
    //printf("生成共享密钥成功\n");
    
    BN_free(p);
    BN_free(g);
    BN_free(pk1);
    BN_free(pk2);
    }
    c_setup 	= c_setup/TEST_REPEATS;
    c_keygen_A 	= c_keygen_A/TEST_REPEATS;
    c_comp_A 	= c_comp_A/TEST_REPEATS;
    c_keygen_B 	= c_keygen_B/TEST_REPEATS;
    c_comp_B 	= c_comp_B/TEST_REPEATS;

    printf("   %20s%20s%20s%20s%20s\n", format(c_setup), format(c_keygen_A), format(c_comp_A), format(c_keygen_B), format(c_comp_B));
    



    return 0;
}

