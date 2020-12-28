#include <string.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/bio.h>
#include <openssl/sha.h>
#include "rng.h"
#include "../rsa_kem.h"

#include <stdio.h>


int main()
{
    size_t pri_len, max_pri_len = 0;           // Length of private key
    size_t pub_len, max_pub_len = 0;           // Length of public key
    char *pri_key;            // Private key
    char *pub_key;            // Public key


    for(int n = 0; n < 1000; n ++)
    {
	    RSA *keypair = RSA_generate_key(RSA_PARAM_N_BITS, RSA_PUB_EXP, NULL, NULL);
	    
	    // To get the C-string PEM form:
	    BIO *pri = BIO_new(BIO_s_mem());
	    BIO *pub = BIO_new(BIO_s_mem());
	    
	    PEM_write_bio_RSAPrivateKey(pri, keypair, NULL, NULL, 0, NULL, NULL);
	    PEM_write_bio_RSAPublicKey(pub, keypair);
	    
	    pri_len = BIO_pending(pri);
	    pub_len = BIO_pending(pub);

	    printf("%d: %d, %d\n",n, pri_len, pub_len);
	    if(pri_len > max_pri_len) max_pri_len = pri_len;
	    if(pub_len > max_pub_len) max_pub_len = pub_len;
    }	    
    printf("max: %d, %d\n", max_pri_len, max_pub_len);
    
    return 0;

}
