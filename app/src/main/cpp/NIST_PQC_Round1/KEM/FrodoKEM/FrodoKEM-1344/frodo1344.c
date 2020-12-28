/********************************************************************************************
* FrodoKEM: Learning with Errors Key Encapsulation
*
* Abstract: functions for FrodoKEM-1344
*           Instantiates "frodo_macrify.c" with the necessary matrix arithmetic functions
*********************************************************************************************/

#include "api.h"
#include "frodo_macrify.h"


// Parameters for "FrodoKEM-1344"
#define PARAMS_N 1344
#define PARAMS_NBAR 8
#define PARAMS_LOGQ 16
#define PARAMS_Q (1 << PARAMS_LOGQ)
#define PARAMS_EXTRACTED_BITS 4
#define PARAMS_STRIPE_STEP 8
#define PARAMS_PARALLEL 4
#define BYTES_SEED_A 16
#define BYTES_MU (PARAMS_EXTRACTED_BITS*PARAMS_NBAR*PARAMS_NBAR)/8
#define BYTES_PKHASH FRODOKEM_CRYPTO_BYTES

// Selecting SHAKE XOF function for the KEM and noise sampling
#define shake     shake256

// CDF table
uint16_t CDF_TABLE[7] = {9142, 23462, 30338, 32361, 32725, 32765, 32767};
uint16_t CDF_TABLE_LEN = 7;

#include "kem.c"
#include "noise.c"
#include "frodo_macrify_reference.c"
