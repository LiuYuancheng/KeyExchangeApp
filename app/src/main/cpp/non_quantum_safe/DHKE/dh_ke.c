#include <openssl/dh.h>
#include <openssl/bn.h>
#include <openssl/sha.h>
#include "dh_ke.h"

int DH_setup(unsigned char *p, int *p_bytes, unsigned char *g, int *g_bytes)
{
	int ret = 0;
	DH *dh;
	BIGNUM *bp, *bg;

	dh = DH_new();
	bp = BN_new();
	bg = BN_new();

	if (1 != DH_generate_parameters_ex(dh, DH_PRIME_BITS, DH_GENERATOR_2, NULL))
	{
		ret = -1;
		goto exit;
	}
	DH_get0_pqg(dh, (const BIGNUM**) &bp, NULL, (const BIGNUM**) &bg);

	*p_bytes = BN_num_bytes((const BIGNUM* )bp);
	*g_bytes = BN_num_bytes((const BIGNUM* )bg);
//	printf("%d, %d\n", *p_bytes, *g_bytes);
	BN_bn2bin(bp, p);
	BN_bn2bin(bg, g);

	exit: BN_free(bp);
	BN_free(bg);

	return ret;
}

int DH_keypair(unsigned char *pk, unsigned char *sk, unsigned char *p,
		unsigned char *g)
{
	int ret = 0;
	DH *dh;
	BIGNUM *bn_p, *bn_g, *bn_pk, *bn_sk;

	dh = DH_new();
	bn_p = BN_new();
	bn_g = BN_new();
	bn_pk = BN_new();
	bn_sk = BN_new();

	BN_bin2bn(p, DH_P_BYTES, bn_p);
	BN_bin2bn(g, DH_G_BYTES, bn_g);
	DH_set0_pqg(dh, bn_p, NULL, bn_g);

	ret = DH_generate_key(dh);
	if (ret != 1)
	{
		ret = -1;
		goto exit;
	}
	ret = 0;

	DH_get0_key(dh, (const BIGNUM**) &bn_pk, (const BIGNUM**) &bn_sk);
	BN_bn2bin(bn_pk, pk);
	BN_bn2bin(bn_sk, sk);

	exit:
//	DH_free(dh);
	BN_free(bn_p);
	BN_free(bn_g);
	BN_free(bn_pk);
	BN_free(bn_sk);

	return ret;

}

int DH_compute(unsigned char *sd, unsigned char *pk, unsigned char *sk,
		unsigned char *p, unsigned char *g)
{
	int ret = 0;
	DH *dh;
	BIGNUM *bn_pk, *bn_sk, *bn_p, *bn_g;

	dh = DH_new();
	bn_pk = BN_new();
	bn_sk = BN_new();
	bn_p = BN_new();
	bn_g = BN_new();

	BN_bin2bn(p, DH_P_BYTES, bn_p);
	BN_bin2bn(g, DH_G_BYTES, bn_g);
	DH_set0_pqg(dh, bn_p, NULL, bn_g);

	BN_bin2bn(pk, DH_PUBLICKEYBYTES, bn_pk);
	BN_bin2bn(sk, DH_SECRETKEYBYTES, bn_sk);
	DH_set0_key(dh, NULL, bn_sk);
	ret = DH_compute_key(sd, bn_pk, dh);

	exit:
//	DH_free(dh);
	BN_free(bn_p);
	BN_free(bn_g);
	BN_free(bn_pk);
	BN_free(bn_sk);

	return ret;

}

int DH_compute_and_derive(unsigned char *sd, unsigned char *pk,
		unsigned char *sk, unsigned char *p, unsigned char *g)
{
	int ret = 0;
	unsigned char sd0[DH_P_BYTES];

	ret = DH_compute(sd0, pk, sk, p, g);
	if (ret == -1)
		return -1;

	SHA256(sd0, DH_P_BYTES, sd);

	return 0;
}

