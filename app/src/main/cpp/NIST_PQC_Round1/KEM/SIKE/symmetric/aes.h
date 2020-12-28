/********************************************************************************************
* Header defining the APIs for AES in ECB mode
*********************************************************************************************/

#ifndef SIKE__AES_H
#define SIKE__AES_H

#include <stdint.h>

void SIKE_AES_ECB_encrypt(const uint8_t* input, const uint8_t* key, uint8_t* output);

#endif
