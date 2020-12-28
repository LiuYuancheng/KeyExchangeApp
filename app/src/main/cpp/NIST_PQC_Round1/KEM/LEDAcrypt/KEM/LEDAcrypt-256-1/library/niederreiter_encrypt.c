/**
 *
 * <niederreiter_encrypt.c>
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

#include "../include/niederreiter_encrypt.h"
#include "../include/qc_ldpc_parameters.h"
#include "../include/gf2x_arith_mod_xPplusOne.h"

#include <string.h> // memset(...)

void encrypt_niederreiter(DIGIT syndrome[],                // 1  polynomial
                          const publicKeyNiederreiter_t *const pk,
                          const DIGIT err[])               // LEDA_N0  polynomials
{
   int i;
   DIGIT saux[NUM_DIGITS_GF2X_ELEMENT];

   memset(syndrome, 0x00, NUM_DIGITS_GF2X_ELEMENT*DIGIT_SIZE_B);

   for (i = 0; i < LEDA_N0-1; i++) {
      gf2x_mod_mul(saux,
                   pk->Mtr+i*NUM_DIGITS_GF2X_ELEMENT,
                   err+i*NUM_DIGITS_GF2X_ELEMENT
                  );
      gf2x_mod_add(syndrome, syndrome, saux);
   }  // end for
   gf2x_mod_add(syndrome, syndrome, err+(LEDA_N0-1)*NUM_DIGITS_GF2X_ELEMENT);
} // end encrypt_niederreiter

/*----------------------------------------------------------------------------*/
