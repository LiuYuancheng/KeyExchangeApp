#include "format_helper.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define CF_SIZE         10

static char commas_format[CF_SIZE][20];
static int  CF_counter = 0;

char * format(unsigned long long int val)
{
   int CF_counter_pri;

   if(val < 1000)
   {
        sprintf(commas_format[CF_counter], "%d", val);
   }
   else if(val >= 1000 && val < 1000000)
   {
        sprintf(commas_format[CF_counter], "%d,%03d", val/1000, val%1000);
   }
   else if(val >= 1000000 && val < 1000000000)
   {
        sprintf(commas_format[CF_counter], "%d,%03d,%03d", val/1000000, (val%1000000)/1000, val%1000);
   }
   else
   {
        sprintf(commas_format[CF_counter], "%d,%03d,%03d,%03d", val/1000000000, (val%1000000000)/1000000, (val%1000000)/1000, val%1000);
   }
   CF_counter_pri = CF_counter;
   CF_counter = (CF_counter + 1) % CF_SIZE;

   return commas_format[CF_counter_pri];
}

char * format(double val, int nfractional)
{
   unsigned long long int vali, valf;
   char format_s[10];
   int CF_counter_pri = CF_counter;;

   vali = (unsigned long long int)val;
   valf = (val - vali) * pow(10, nfractional);
   format(vali);
   strcat(commas_format[CF_counter_pri], ".");
   sprintf(format_s, "%%0%dd", nfractional);
   sprintf(commas_format[CF_counter_pri] + strlen(commas_format[CF_counter_pri]), format_s, valf);

   return commas_format[CF_counter_pri];
}

