
#define CIPHERSUITE_MAX_SIZE  18

typedef enum{
	IND_CPA,
	IND_CCA,
	IND_CCA2
} SECURITY_TYPE;

typedef enum{
	NIST_LEVEL_1,
	NIST_LEVEL_2,
	NIST_LEVEL_3,
	NIST_LEVEL_4,
	NIST_LEVEL_5,
	LESS_THAN_NIST_LEVEL_1,
	MORE_THAN_NIST_LEVEL_5
} SECURITY_STHRENGTH;


#define MAJOR_READABLE_NAME_MAX_SIZE	20
#define MINOR_READABLE_NAME_MAX_SIZE	300

class CKEM
{
	private:
		unsigned char MajorReadableName[MAJOR_READABLE_NAME_MAX_SIZE];
		unsigned char MinorReadableName[MINOR_READABLE_NAME_MAX_SIZE];
		unsigned char *pk, *sk, *ct, *ss;

	public:
		CKEM(unsigned char *MajorName);
		~CKEM();

		void GetMajorName(unsigned char *);
		void GetMinorName(unsigned char *);
		void GetPublicKey(unsigned char *);
		void GetPrivateKey(unsigned char *);
		void GetCiphertext(unsigned char *);
		void GetSharedKey(unsigned char *);


		void SetMajorName(unsigned char *);
		void SetMinorName(unsigned char *);
		void SetPublicKey(unsigned char *);
		void SetPrivateKey(unsigned char *);
		void SetCiphertext(unsigned char *);
		void SetSharedKey(unsigned char *);



};



class CKEMHybrid
{


};





typedef struct {
	int major_type;
	int minor_type;
	char major_readable_name[20];
	char minor_readable_name[40];
	SECURITY_STHRENGTH 		sec_level;
	SECURITY_TYPE			sec_type;
	
	unsigned char *pk;
	unsigned char *sk;
	unsigned char *ct;
	unsigned char *ss;

	size_t pk_len;
	size_t sk_len;
	size_t ct_len;
	size_t ss_len;

	int (*kem_keypair)(unsigned char *pk, unsigned char *sk);
	int (*kem_enc)(unsigned char *ct, unsigned char *ss, const unsigned char *pk);
	int (*kem_dec)(unsigned char *ss, const unsigned char *ct, const unsigned char *sk);

} PQC_KEM;

typedef struct {
	PQC_KEM pqc_kem[CIPHERSUITE_MAX_SIZE];
	int count;

        unsigned char *pk;
        unsigned char *sk;
        unsigned char *ct;
        unsigned char *ss;
        unsigned char *key;
	

        size_t pk_len;
        size_t sk_len;
        size_t ct_len;
        size_t ss_len;
        size_t key_len;
	
	int (*kem_keypair)(unsigned char *pk, unsigned char *sk);
	int (*kem_enc)(unsigned char *ct, unsigned char *ss, const unsigned char *pk);
	int (*kem_dec)(unsigned char *ss, const unsigned char *ct, const unsigned char *sk);
	
	int (* kdf)(uint8_t *key_in, size_t len, uint8_t *key_out, uint8_t * additional);

} PQCH_KEM;


int PQCH_KEM_config(PQCH_KEM *pqch_kem, int (*kdf)(uint8_t,size_t,uint8_t,uint8_t))
{
	int i = 0;
#ifdef PQCH_RSA_KEM
	pqch_kem->pqc_kem[i].kem_keypair = RSA_crypto_kem_keypair;
	pqch_kem->pqc_kem[i].kem_enc = RSA_crypto_kem_enc;
	pqch_kem->pqc_kem[i].kem_dec = RSA_crypto_kem_dec;
	strcpy(pqch_kem->pqc_kem[i].major_readable_name, "RSA-KEM");
	strcpy(pqch_kem->pqc_kem[i].minor_readable_name, RSA_CRYPTO_ALGNAME);
	i ++;
#endif
#ifdef PQCH_BIKE_KEM
	pqch_kem->pqc_kem[i].kem_keypair = BIKE_crypto_kem_keypair;
	pqch_kem->pqc_kem[i].kem_enc = BIKE_crypto_kem_enc;
	pqch_kem->pqc_kem[i].kem_dec = BIKE_crypto_kem_dec;
	strcpy(pqch_kem->pqc_kem[i].major_readable_name, "BIKE-KEM");
	strcpy(pqch_kem->pqc_kem[i].minor_readable_name, BIKE_CRYPTO_ALGNAME);
	i ++;
#endif
#ifdef PQCH_FRODO_KEM
	pqch_kem->pqc_kem[i].kem_keypair = FRODOKEM_crypto_kem_keypair;
	pqch_kem->pqc_kem[i].kem_enc = RRODOKEM_crypto_kem_enc;
	pqch_kem->pqc_kem[i].kem_dec = FRODOKEM_crypto_kem_dec;
	strcpy(pqch_kem->pqc_kem[i].major_readable_name, "FRODO-KEM");
	strcpy(pqch_kem->pqc_kem[i].minor_readable_name, FRODOKEM_CRYPTO_ALGNAME);
	i ++;
#endif
#ifdef PQCH_NTRU_KEM
	pqch_kem->pqc_kem[i].kem_keypair = NTRU_crypto_kem_keypair;
	pqch_kem->pqc_kem[i].kem_enc = NTRU_crypto_kem_enc;
	pqch_kem->pqc_kem[i].kem_dec = NTRU_crypto_kem_dec;
	strcpy(pqch_kem->pqc_kem[i].major_readable_name, "NTRU-KEM");
	strcpy(pqch_kem->pqc_kem[i].minor_readable_name, NTRU_CRYPTO_ALGNAME);
	i ++;
#endif
#ifdef PQCH_NTRUPRIME_KEM
	pqch_kem->pqc_kem[i].kem_keypair = NTRUPRIME_crypto_kem_keypair;
	pqch_kem->pqc_kem[i].kem_enc = NTRUPRIME_crypto_kem_enc;
	pqch_kem->pqc_kem[i].kem_dec = NTRUPRIME_crypto_kem_dec;
	strcpy(pqch_kem->pqc_kem[i].major_readable_name, "NTRUPRIME-KEM");
	strcpy(pqch_kem->pqc_kem[i].minor_readable_name, NTRUPRIME_CRYPTO_ALGNAME);
	i ++;
#endif
#ifdef PQCH_KYBER_KEM
	pqch_kem->pqc_kem[i].kem_keypair = KYBER_crypto_kem_keypair;
	pqch_kem->pqc_kem[i].kem_enc = KYBER_crypto_kem_enc;
	pqch_kem->pqc_kem[i].kem_dec = KYBER_crypto_kem_dec;
	strcpy(pqch_kem->pqc_kem[i].major_readable_name, "KYBER-KEM");
	strcpy(pqch_kem->pqc_kem[i].minor_readable_name, KYBER_CRYPTO_ALGNAME);
	i ++;
#endif
#ifdef PQCH_SABER_KEM
	pqch_kem->pqc_kem[i].kem_keypair = SABER_crypto_kem_keypair;
	pqch_kem->pqc_kem[i].kem_enc = SABER_crypto_kem_enc;
	pqch_kem->pqc_kem[i].kem_dec = SABER_crypto_kem_dec;
	strcpy(pqch_kem->pqc_kem[i].major_readable_name, "SABER-KEM");
	strcpy(pqch_kem->pqc_kem[i].minor_readable_name, SABER_CRYPTO_ALGNAME);
	i ++;
#endif
#ifdef PQCH_NEWHOPE_KEM
	pqch_kem->pqc_kem[i].kem_keypair = NEWHOPE_crypto_kem_keypair;
	pqch_kem->pqc_kem[i].kem_enc = NEWHOPE_crypto_kem_enc;
	pqch_kem->pqc_kem[i].kem_dec = NEWHOPE_crypto_kem_dec;
	strcpy(pqch_kem->pqc_kem[i].major_readable_name, "NEWHOPE-KEM");
	strcpy(pqch_kem->pqc_kem[i].minor_readable_name, NEWHOPE_CRYPTO_ALGNAME);
	i ++;
#endif
#ifdef PQCH_HQC_KEM
	pqch_kem->pqc_kem[i].kem_keypair = HQC_crypto_kem_keypair;
	pqch_kem->pqc_kem[i].kem_enc = HQC_crypto_kem_enc;
	pqch_kem->pqc_kem[i].kem_dec = HQC_crypto_kem_dec;
	strcpy(pqch_kem->pqc_kem[i].major_readable_name, "HQC-KEM");
	strcpy(pqch_kem->pqc_kem[i].minor_readable_name, HQC_CRYPTO_ALGNAME);
	i ++;
#endif
#ifdef PQCH_RQC_KEM
	pqch_kem->pqc_kem[i].kem_keypair = RQC_crypto_kem_keypair;
	pqch_kem->pqc_kem[i].kem_enc = RQC_crypto_kem_enc;
	pqch_kem->pqc_kem[i].kem_dec = RQC_crypto_kem_dec;
	strcpy(pqch_kem->pqc_kem[i].major_readable_name, "RQC-KEM");
	strcpy(pqch_kem->pqc_kem[i].minor_readable_name, RQC_CRYPTO_ALGNAME);
	i ++;
#endif
#ifdef PQCH_ROLLO_KEM
	pqch_kem->pqc_kem[i].kem_keypair = ROLLO_crypto_kem_keypair;
	pqch_kem->pqc_kem[i].kem_enc = ROLLO_crypto_kem_enc;
	pqch_kem->pqc_kem[i].kem_dec = ROLLO_crypto_kem_dec;
	strcpy(pqch_kem->pqc_kem[i].major_readable_name, "ROLLO-KEM");
	strcpy(pqch_kem->pqc_kem[i].minor_readable_name, ROLLO_CRYPTO_ALGNAME);
	i ++;
#endif
#ifdef PQCH_LAC_KEM
	pqch_kem->pqc_kem[i].kem_keypair = LAC_crypto_kem_keypair;
	pqch_kem->pqc_kem[i].kem_enc = LAC_crypto_kem_enc;
	pqch_kem->pqc_kem[i].kem_dec = LAC_crypto_kem_dec;
	strcpy(pqch_kem->pqc_kem[i].major_readable_name, "LAC-KEM");
	strcpy(pqch_kem->pqc_kem[i].minor_readable_name, LAC_CRYPTO_ALGNAME);
	i ++;
#endif
#ifdef PQCH_ROUND5_KEM
	pqch_kem->pqc_kem[i].kem_keypair = ROUND5_crypto_kem_keypair;
	pqch_kem->pqc_kem[i].kem_enc = ROUND5_crypto_kem_enc;
	pqch_kem->pqc_kem[i].kem_dec = ROUND5_crypto_kem_dec;
	strcpy(pqch_kem->pqc_kem[i].major_readable_name, "ROUND5-KEM");
	strcpy(pqch_kem->pqc_kem[i].minor_readable_name, ROUND5_CRYPTO_ALGNAME);
	i ++;
#endif
#ifdef PQCH_LEDACRYPT_KEM
	pqch_kem->pqc_kem[i].kem_keypair = LEDACRYPT_crypto_kem_keypair;
	pqch_kem->pqc_kem[i].kem_enc = LEDACRYPT_crypto_kem_enc;
	pqch_kem->pqc_kem[i].kem_dec = LEDACRYPT_crypto_kem_dec;
	strcpy(pqch_kem->pqc_kem[i].major_readable_name, "LEDACRYPT-KEM");
	strcpy(pqch_kem->pqc_kem[i].minor_readable_name, LEDACRYPT_CRYPTO_ALGNAME);
	i ++;
#endif
#ifdef PQCH_NTS_KEM
	pqch_kem->pqc_kem[i].kem_keypair = NTS_crypto_kem_keypair;
	pqch_kem->pqc_kem[i].kem_enc = NTS_crypto_kem_enc;
	pqch_kem->pqc_kem[i].kem_dec = NTS_crypto_kem_dec;
	strcpy(pqch_kem->pqc_kem[i].major_readable_name, "NTS-KEM");
	strcpy(pqch_kem->pqc_kem[i].minor_readable_name, NTS_CRYPTO_ALGNAME);
	i ++;
#endif
#ifdef PQCH_THREEBEARS_KEM
	pqch_kem->pqc_kem[i].kem_keypair = THREEBEARS_crypto_kem_keypair;
	pqch_kem->pqc_kem[i].kem_enc = THREEBEARS_crypto_kem_enc;
	pqch_kem->pqc_kem[i].kem_dec = THREEBEARS_crypto_kem_dec;
	strcpy(pqch_kem->pqc_kem[i].major_readable_name, "THREEBEARS-KEM");
	strcpy(pqch_kem->pqc_kem[i].minor_readable_name, THREEBEARS_CRYPTO_ALGNAME);
	i ++;
#endif
#ifdef PQCH_CM_KEM
	pqch_kem->pqc_kem[i].kem_keypair = CM_crypto_kem_keypair;
	pqch_kem->pqc_kem[i].kem_enc = CM_crypto_kem_enc;
	pqch_kem->pqc_kem[i].kem_dec = CM_crypto_kem_dec;
	strcpy(pqch_kem->pqc_kem[i].major_readable_name, "CM-KEM");
	strcpy(pqch_kem->pqc_kem[i].minor_readable_name, CM_CRYPTO_ALGNAME);
	i ++;
#endif
#ifdef PQCH_SIKE_KEM
	pqch_kem->pqc_kem[i].kem_keypair = SIKE_crypto_kem_keypair;
	pqch_kem->pqc_kem[i].kem_enc = SIKE_crypto_kem_enc;
	pqch_kem->pqc_kem[i].kem_dec = SIKE_crypto_kem_dec;
	strcpy(pqch_kem->pqc_kem[i].major_readable_name, "SIKE-KEM");
	strcpy(pqch_kem->pqc_kem[i].minor_readable_name, SIKE_CRYPTO_ALGNAME);
	i ++;
#endif
	pqch_kem->count = i;
	pqch_kem->kdf = kdf;

	return 0;
}



			
