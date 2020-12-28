/**
 *
 * <H_Q_matrices_generation.c>
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

#include "../include/H_Q_matrices_generation.h"
#include "../include/gf2x_arith_mod_xPplusOne.h"
#include "../include/api.h"
/*----------------------------------------------------------------------------*/

void generateHPosOnes_HtrPosOnes(POSITION_T HPosOnes[LEDA_N0][LEDA_DV],
                        POSITION_T HtrPosOnes[LEDA_N0][LEDA_DV],
                        AES_XOF_struct *keys_expander
                       )
{
   for (int i = 0; i < LEDA_N0; i++) {
      /* Generate a random block of Htr */
      rand_circulant_sparse_block(&HtrPosOnes[i][0],
                                  LEDA_DV,
                                  keys_expander);
   }
   for (int i = 0; i < LEDA_N0; i++) {
      /* Obtain directly the sparse representation of the block of H */
      for (int k = 0; k < LEDA_DV; k++) {
         HPosOnes[i][k] = (LEDA_P - HtrPosOnes[i][k])  % LEDA_P; /* transposes indexes */
      }// end for k
   }
} // end generateHtr_HtrPosOnes

/*----------------------------------------------------------------------------*/

void  generateQsparse(POSITION_T pos_ones[LEDA_N0][LEDA_M],
                      AES_XOF_struct *keys_expander)
{
   for (int i = 0; i < LEDA_N0; i++) {
      int placed_ones = 0;
      for (int j = 0; j < LEDA_N0; j++) {
         rand_circulant_sparse_block(&pos_ones[i][placed_ones],
                                     qBlockWeights[i][j],
                                     keys_expander);
         placed_ones += qBlockWeights[i][j];
      } // end for j
   } // end for i
} // end generateQsparse

/*----------------------------------------------------------------------------*/
