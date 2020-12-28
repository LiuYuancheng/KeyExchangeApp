/**
 *
 * <bf_decoding.c>
 *
 * @version 2.0 (March 2019)
 *
 * Reference ISO-C11 Implementation of the LEDAcrypt KEM cipher using GCC built-ins.
 *
 * In alphabetical order:
 *
 * @author Marco Baldi <m.baldi@univpm.it>
 * @author Alessandro Barenghi <alessandro.barenghi@polimi.it>
 * @author Franco Chiaraluce <f.chiaraluce@univpm.it>
 * @author Gerardo Pelosi <gerardo.pelosi@polimi.it>
 * @author Paolo Santini <p.santini@pm.univpm.it>
 *
 * This code is hereby placed in the public domain.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHORS ''AS IS'' AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHORS OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 **/
#include "../include/bf_decoding.h"
#include "../include/gf2x_arith_mod_xPplusOne.h"
#include <string.h>
#include <assert.h>

#define ROTBYTE(a)   ( (a << 8) | (a >> (DIGIT_SIZE_b - 8)) )
#define ROTUPC(a)   ( (a >> 8) | (a << (DIGIT_SIZE_b - 8)) )

int bf_decoding(DIGIT out[], // LEDA_N0 polynomials
                const POSITION_T HtrPosOnes[LEDA_N0][LEDA_DV],
                const POSITION_T QtrPosOnes[LEDA_N0][LEDA_M],
                DIGIT privateSyndrome[]  //  1 polynomial
               )
{
#if LEDA_P < 64
#error The circulant block size should exceed 64
#endif

   uint8_t unsatParityChecks[LEDA_N0*LEDA_P];
   POSITION_T currQBlkPos[LEDA_M],currQBitPos[LEDA_M];
   DIGIT currSyndrome[NUM_DIGITS_GF2X_ELEMENT];
   int check;
   int iteration = 0;
    unsigned int synd_corrt_vec[][2]= {SYNDROME_TRESH_LOOKUP_TABLE};
   do {
      gf2x_copy(currSyndrome, privateSyndrome);
      memset(unsatParityChecks,0x00,LEDA_N0*LEDA_P*sizeof(uint8_t));
         for (int i = 0; i < LEDA_N0; i++) {
           for (int valueIdx = 0; valueIdx < LEDA_P; valueIdx++) {
              for(int HtrOneIdx = 0; HtrOneIdx < LEDA_DV; HtrOneIdx++) {
                  POSITION_T tmp = (HtrPosOnes[i][HtrOneIdx]+valueIdx) >= LEDA_P ? (HtrPosOnes[i][HtrOneIdx]+valueIdx) -LEDA_P : (HtrPosOnes[i][HtrOneIdx]+valueIdx);
                 if (gf2x_get_coeff(currSyndrome, tmp))
                    unsatParityChecks[i*LEDA_P+valueIdx]++;
              }
           }
         }

      // computation of syndrome weight and threshold determination
      int syndrome_wt = population_count(currSyndrome);
      int min_idx=0;
      int max_idx;
      max_idx = sizeof(synd_corrt_vec)/(2*sizeof(unsigned int)) - 1;
      int thresh_table_idx = (min_idx + max_idx)/2;
      while(min_idx< max_idx) {
         if (synd_corrt_vec[thresh_table_idx][0] <= syndrome_wt) {
            min_idx = thresh_table_idx +1;
         } else {
            max_idx = thresh_table_idx -1;
         }
         thresh_table_idx = (min_idx +max_idx)/2;
      }
      int corrt_syndrome_based=synd_corrt_vec[thresh_table_idx][1];

      //Computation of correlation  with a full Q matrix
      for (int i = 0; i < LEDA_N0; i++) {
         for (int j = 0; j < LEDA_P; j++) {
            int currQoneIdx = 0; // position in the column of QtrPosOnes[][...]
            int endQblockIdx = 0;
            int correlation =0;

            for (int blockIdx = 0; blockIdx < LEDA_N0; blockIdx++) {
               endQblockIdx += qBlockWeights[blockIdx][i];
               int currblockoffset = blockIdx*LEDA_P;
               for (; currQoneIdx < endQblockIdx; currQoneIdx++) {
                  int tmp = QtrPosOnes[i][currQoneIdx]+j;
                  tmp = tmp >= LEDA_P ? tmp - LEDA_P : tmp;
                  currQBitPos[currQoneIdx] = tmp;
                  currQBlkPos[currQoneIdx] = blockIdx;
                  correlation += unsatParityChecks[tmp + currblockoffset];
               }
            }
            /* Correlation based flipping */
            if (correlation > corrt_syndrome_based) {
               gf2x_toggle_coeff(out+NUM_DIGITS_GF2X_ELEMENT*i, j);
               for (int v = 0; v < LEDA_M; v++) {
                  unsigned syndromePosToFlip;
                  for (int HtrOneIdx = 0; HtrOneIdx < LEDA_DV; HtrOneIdx++) {
                     syndromePosToFlip = (HtrPosOnes[currQBlkPos[v]][HtrOneIdx] + currQBitPos[v] );
                     syndromePosToFlip = syndromePosToFlip >= LEDA_P ? syndromePosToFlip - LEDA_P : syndromePosToFlip;
                     gf2x_toggle_coeff(privateSyndrome, syndromePosToFlip);
                  }
               } // end for v
            } // end if
         } // end for j
      } // end for i

      iteration = iteration + 1;
      check = 0;
      while (check < NUM_DIGITS_GF2X_ELEMENT && privateSyndrome[check++] == 0);

   } while (iteration < ITERATIONS_MAX && check < NUM_DIGITS_GF2X_ELEMENT);

   return (check == NUM_DIGITS_GF2X_ELEMENT);
}  // end QdecodeSyndromeThresh_bitFlip_sparse
