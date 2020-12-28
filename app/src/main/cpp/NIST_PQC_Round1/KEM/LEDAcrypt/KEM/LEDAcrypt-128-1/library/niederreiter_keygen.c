/**
 *
 * <niederreiter_keygen.c>
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
 * EVEN IF ALEDA_DVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 **/

#include "../include/niederreiter_keygen.h"

#include "../include/H_Q_matrices_generation.h"
#include "../include/gf2x_arith_mod_xPplusOne.h"
#include "rng.h"

#include <string.h>
/*----------------------------------------------------------------------------*/
/* Implementation that should never be optimized out by the compiler */
static inline void zeroize(unsigned char  *v, size_t n )
{
   volatile unsigned char *p = v;
   while( n-- ) *p++ = 0;
} // end zeroize

/*----------------------------------------------------------------------------*/

void key_gen_niederreiter(publicKeyNiederreiter_t   *const pk,
                          privateKeyNiederreiter_t *const sk,
                          AES_XOF_struct *keys_expander)
{
   // sequence of LEDA_N0 circ block matrices (p x p): Hi

   POSITION_T HPosOnes[LEDA_N0][LEDA_DV];
   POSITION_T HtrPosOnes[LEDA_N0][LEDA_DV];
   /* Sparse representation of the transposed circulant matrix H,
   with weight LEDA_DV. Each index contains the position of a '1' digit in the
   corresponding Htr block */

   /* Sparse representation of the matrix (Q).
   A matrix containing the positions of the ones in the circulant
   blocks of Q. Each row contains the position of the
   ones of all the blocks of a row of Q as exponent+
   P*block_position */
   POSITION_T QPosOnes[LEDA_N0][LEDA_M];

   /*Rejection-sample for a full L*/
   POSITION_T LPosOnes[LEDA_N0][LEDA_DV*LEDA_M];
   int is_L_full;
   do {
     generateHPosOnes_HtrPosOnes(HPosOnes,
                                 HtrPosOnes,
                                 keys_expander);

     generateQsparse(QPosOnes,
                     keys_expander);
     for (int i = 0; i < LEDA_N0; i++) {
        for (int j = 0; j< LEDA_DV*LEDA_M; j++) {
           LPosOnes[i][j]=INVALID_POS_VALUE;
        }
     }

     POSITION_T auxPosOnes[LEDA_DV*LEDA_M];
     unsigned char processedQOnes[LEDA_N0] = {0};
     for (int colQ = 0; colQ < LEDA_N0; colQ++) {
        for (int i = 0; i < LEDA_N0; i++) {
           gf2x_mod_mul_sparse(LEDA_DV*LEDA_M, auxPosOnes,
                               LEDA_DV, HPosOnes[i],
                               qBlockWeights[i][colQ], QPosOnes[i]+processedQOnes[i]);
           gf2x_mod_add_sparse(LEDA_DV*LEDA_M, LPosOnes[colQ],
                               LEDA_DV*LEDA_M, LPosOnes[colQ],
                               LEDA_DV*LEDA_M, auxPosOnes);
           processedQOnes[i] += qBlockWeights[i][colQ];
        }
     }
     is_L_full = 1;
     for (int i = 0; i < LEDA_N0; i++) {
        is_L_full = is_L_full && (LPosOnes[i][LEDA_DV*LEDA_M-1] != INVALID_POS_VALUE);
     }
   } while(!is_L_full);

   DIGIT Ln0dense[NUM_DIGITS_GF2X_ELEMENT] = {0x00};
   for(int j = 0; j < LEDA_DV*LEDA_M; j++) {
      if(LPosOnes[LEDA_N0-1][j] != INVALID_POS_VALUE)
         gf2x_set_coeff(Ln0dense,LPosOnes[LEDA_N0-1][j],1);
   }
   DIGIT Ln0Inv[NUM_DIGITS_GF2X_ELEMENT] = {0x00};
   gf2x_mod_inverse(Ln0Inv, Ln0dense);
   for (int i = 0; i < LEDA_N0-1; i++) {
      gf2x_mod_mul_dense_to_sparse(pk->Mtr+i*NUM_DIGITS_GF2X_ELEMENT,
                                   Ln0Inv,
                                   LPosOnes[i],
                                   LEDA_DV*LEDA_M);
   }

   for (int i = 0; i < LEDA_N0-1; i++) {
      gf2x_transpose_in_place(pk->Mtr+i*NUM_DIGITS_GF2X_ELEMENT);
   }
} // end key_gen_niederreiter

/*----------------------------------------------------------------------------*/

void publicKey_deletion_niederreiter(publicKeyNiederreiter_t   *const pk)
{

   zeroize((unsigned char *)pk,sizeof(publicKeyNiederreiter_t));
} // publicKey_deletion_niederreiter

/*----------------------------------------------------------------------------*/

void privateKey_deletion_niederreiter(privateKeyNiederreiter_t *const sk)
{
   zeroize((unsigned char *)sk, sizeof(privateKeyNiederreiter_t));
} // privateKey_deletion_niederreiter

/*----------------------------------------------------------------------------*/
