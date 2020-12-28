/** 
 * \file rqc.c
 * \brief Implementation of rqc.h
 */

#include "ffi/ffi_field.h"
#include "ffi/ffi_vec.h"
#include "gabidulin.h"
#include "parameters.h"
#include "parsing.h"
#include "rqc.h"


/** 
 * \fn void rqc_pke_keygen(unsigned char* pk, unsigned char* sk)
 * \brief Keygen of the RQC_PKE IND-CPA scheme
 *
 * The public key is composed of the syndrom <b>s</b> as well as the <b>seed</b> used to generate vectors <b>g</b> and <b>h</b>.
 *
 * The secret key is composed of the seed used to generate vectors <b>x</b> and <b>y</b>.
 * As a technicality, the public key is appended to the secret key in order to respect the NIST API.
 *
 * \param[out] pk String containing the public key
 * \param[out] sk String containing the secret key
 */
void rqc_pke_keygen(unsigned char* pk, unsigned char* sk) {

  // Create seed expanders for public key and secret key
  unsigned char sk_seed[SEEDEXPANDER_SEED_BYTES];
  randombytes(sk_seed, SEEDEXPANDER_SEED_BYTES);
  AES_XOF_struct* sk_seedexpander = (AES_XOF_struct*) malloc(sizeof(AES_XOF_struct));
  seedexpander_init(sk_seedexpander, sk_seed, sk_seed + 32, SEEDEXPANDER_MAX_LENGTH);

  unsigned char pk_seed[SEEDEXPANDER_SEED_BYTES];
  randombytes(pk_seed, SEEDEXPANDER_SEED_BYTES);
  AES_XOF_struct* pk_seedexpander = (AES_XOF_struct*) malloc(sizeof(AES_XOF_struct));
  seedexpander_init(pk_seedexpander, pk_seed, pk_seed + 32, SEEDEXPANDER_MAX_LENGTH);

  RQC_ffi_field_init();

  // Compute secret key
  RQC_ffi_vec x, y, support_w;
  RQC_ffi_vec_set_random_full_rank_with_one(support_w, RQC_PARAM_W, sk_seedexpander);
  RQC_ffi_vec_set_random_from_support(x, RQC_PARAM_N, support_w, RQC_PARAM_W, sk_seedexpander);
  RQC_ffi_vec_set_random_from_support(y, RQC_PARAM_N, support_w, RQC_PARAM_W, sk_seedexpander);

  // Compute public key
  RQC_ffi_vec g, h, s;
  RQC_ffi_vec_set_random_full_rank(g, RQC_PARAM_N, pk_seedexpander);
  RQC_ffi_vec_set_random(h, RQC_PARAM_N, pk_seedexpander); 
  
  RQC_ffi_vec_mul(s, h, y, RQC_PARAM_N);
  RQC_ffi_vec_add(s, s, x, RQC_PARAM_N);

  // Parse keys to string
  rqc_public_key_to_string(pk, s, pk_seed);
  rqc_secret_key_to_string(sk, sk_seed, pk);

  #ifdef VERBOSE
    printf("\n\nsk_seed: "); for(int i = 0 ; i < SEEDEXPANDER_SEED_BYTES ; ++i) printf("%02x", sk_seed[i]);
    printf("\n\nsupport_w: "); RQC_ffi_vec_print(support_w, RQC_PARAM_W);
    printf("\nx: "); RQC_ffi_vec_print(x, RQC_PARAM_N);
    printf("\ny: "); RQC_ffi_vec_print(y, RQC_PARAM_N);

    printf("\npk_seed: "); for(int i = 0 ; i < SEEDEXPANDER_SEED_BYTES ; ++i) printf("%02x", pk_seed[i]);
    printf("\n\ng: "); RQC_ffi_vec_print(g, RQC_PARAM_N);
    printf("\nh: "); RQC_ffi_vec_print(h, RQC_PARAM_N);
    printf("\ns: "); RQC_ffi_vec_print(s, RQC_PARAM_N);

    printf("\nsk: "); for(int i = 0 ; i < SECRET_KEY_BYTES ; ++i) printf("%02x", sk[i]);
    printf("\n\npk: "); for(int i = 0 ; i < PUBLIC_KEY_BYTES ; ++i) printf("%02x", pk[i]);
  #endif

  free(pk_seedexpander);
  free(sk_seedexpander);
}



/** 
 * \fn void rqc_pke_encrypt(RQC_ffi_vec& u, RQC_ffi_vec& v, const RQC_ffi_vec& m, unsigned char* theta, const unsigned char* pk)
 * \brief Encryption of the RQC_PKE IND-CPA scheme
 *
 * The ciphertext is composed of the vectors <b>u</b> and <b>v</b>.
 *
 * \param[out] u Vector u (first part of the ciphertext)
 * \param[out] v Vector v (second part of the ciphertext)
 * \param[in] m Vector representing the message to encrypt
 * \param[in] theta Seed used to derive randomness required for encryption
 * \param[in] pk String containing the public key
 */
void rqc_pke_encrypt(RQC_ffi_vec& u, RQC_ffi_vec& v, const RQC_ffi_vec& m, unsigned char* theta, const unsigned char* pk) {

  // Create seed_expander from theta
  AES_XOF_struct* seedexpander = (AES_XOF_struct*) malloc(sizeof(AES_XOF_struct));
  seedexpander_init(seedexpander, theta, theta + 32, SEEDEXPANDER_MAX_LENGTH);

  RQC_ffi_field_init();

  // Retrieve g, h and s from public key
  RQC_ffi_vec g, h, s;
  rqc_public_key_from_string(g, h, s, pk);

  // Generate r1, r2 and e
  RQC_ffi_vec r1, r2, e, support_r;
  RQC_ffi_vec_set_random_full_rank(support_r, RQC_PARAM_W_R, seedexpander);
  RQC_ffi_vec_set_random_from_support(r1, RQC_PARAM_N, support_r, RQC_PARAM_W_R, seedexpander);
  RQC_ffi_vec_set_random_from_support(r2, RQC_PARAM_N, support_r, RQC_PARAM_W_R, seedexpander);
  RQC_ffi_vec_set_random_from_support(e, RQC_PARAM_N, support_r, RQC_PARAM_W_R, seedexpander);

  // Compute u = r1 + h.r2
  RQC_ffi_vec_mul(u, h, r2, RQC_PARAM_N);
  RQC_ffi_vec_add(u, u, r1, RQC_PARAM_N);

  // Compute v = m.G by encoding the message
  gabidulin_code code = gabidulin_code_init(g, RQC_PARAM_K, RQC_PARAM_N);
  gabidulin_code_encode(v, code, m);

  // Compute v = m.G + s.r2 + e
  RQC_ffi_vec tmp;
  RQC_ffi_vec_mul(tmp, s, r2, RQC_PARAM_N);
  RQC_ffi_vec_add(tmp, tmp, e, RQC_PARAM_N);
  RQC_ffi_vec_add(v, v, tmp, RQC_PARAM_N);

  #ifdef VERBOSE
    printf("\n\nh: "); RQC_ffi_vec_print(h, RQC_PARAM_N);
    printf("\ns: "); RQC_ffi_vec_print(s, RQC_PARAM_N);
    printf("\nsupport_r: "); RQC_ffi_vec_print(support_r, RQC_PARAM_W_R);
    printf("\nr1: "); RQC_ffi_vec_print(r1, RQC_PARAM_N);
    printf("\nr2: "); RQC_ffi_vec_print(r2, RQC_PARAM_N);
    printf("\ne: "); RQC_ffi_vec_print(e, RQC_PARAM_N);

    printf("\nu: "); RQC_ffi_vec_print(u, RQC_PARAM_N);
    printf("\nv: "); RQC_ffi_vec_print(v, RQC_PARAM_N);
  #endif

  free(seedexpander);
}



/** 
 * \fn void rqc_pke_decrypt(RQC_ffi_vec& m, const RQC_ffi_vec& u, const RQC_ffi_vec& v, const unsigned char* sk)
 * \brief Decryption of the RQC_PKE IND-CPA scheme
 *
 * \param[out] m Vector representing the decrypted message
 * \param[in] u Vector u (first part of the ciphertext)
 * \param[in] v Vector v (second part of the ciphertext)
 * \param[in] sk String containing the secret key
 */
void rqc_pke_decrypt(RQC_ffi_vec& m, const RQC_ffi_vec& u, const RQC_ffi_vec& v, const unsigned char* sk) {

  RQC_ffi_field_init();

  // Retrieve x, y, g, h and s from secret key
  unsigned char pk[PUBLIC_KEY_BYTES];
  RQC_ffi_vec x, y;
  RQC_ffi_vec g, h, s; 

  rqc_secret_key_from_string(x, y, pk, sk);
  rqc_public_key_from_string(g, h, s, pk);

  // Compute v - u.y
  RQC_ffi_vec tmp;
  RQC_ffi_vec_mul(tmp, u, y, RQC_PARAM_N);
  RQC_ffi_vec_add(tmp, v, tmp, RQC_PARAM_N);

  #ifdef VERBOSE
    printf("\n\nu: "); RQC_ffi_vec_print(u, RQC_PARAM_N);
    printf("\nv: "); RQC_ffi_vec_print(v, RQC_PARAM_N);
    printf("\ny: "); RQC_ffi_vec_print(y, RQC_PARAM_N);
    printf("\nv - u.y: "); RQC_ffi_vec_print(tmp, RQC_PARAM_N);
  #endif

  // Compute m by decoding v - u.y
  gabidulin_code code = gabidulin_code_init(g, RQC_PARAM_K, RQC_PARAM_N);
  gabidulin_code_decode(m, code, tmp);
}

