/*
  This file is for Benes network related functions
*/

#ifndef CM_BENES_H
#define CM_BENES_H

#include "gf.h"

void apply_benes(unsigned char *, const unsigned char *, int);
void support_gen(gf *, const unsigned char *);

#endif

