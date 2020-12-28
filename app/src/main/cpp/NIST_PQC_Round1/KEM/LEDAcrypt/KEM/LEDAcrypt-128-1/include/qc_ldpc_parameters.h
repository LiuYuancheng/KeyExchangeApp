/**
 *
 * <qc_ldpc_parameters.h>
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
#pragma once
// CATEGORY defined in the makefile

#define CATEGORY  1
#define LEDA_N0          2 
#define CPU_WORD_BITS   64


/*----------------------------------------------------------------------------*/
#if CATEGORY == 1
#define TRNG_BYTE_LENGTH (24)
#define    HASH_FUNCTION sha3_256
#define HASH_BYTE_LENGTH (32)
// LEDA_N0 defined in the makefile
#if LEDA_N0 == 2
#define    LEDA_P  (14939)  // modulus(x) = x^P-1
#define    LEDA_DV (11)  // odd number
#define    LEDA_M  (7)
#define    LEDA_M0 (4)
#define    LEDA_M1 (3)
#define    NUM_ERRORS_T   (136)

#elif LEDA_N0 == 3
#define    LEDA_P  (8269)  // modulus(x) = x^P-1
#define    LEDA_DV (9)  // odd number
#define    LEDA_M  (9)
#define    LEDA_M0 (4)
#define    LEDA_M1 (3)
#define    LEDA_M2 (2)
#define    NUM_ERRORS_T   (86)

#elif LEDA_N0 == 4
#define    LEDA_P  (7547)  // modulus(x) = x^P-1
#define    LEDA_DV (13)  // odd number
#define    LEDA_M  (7)
#define    LEDA_M0 (2)
#define    LEDA_M1 (2)
#define    LEDA_M2 (2)
#define    LEDA_M3 (1)
#define    NUM_ERRORS_T   (69)

#else
#error "Unsupported number of circulant blocks"
#endif
#endif // end CATEGORY == 1

/*----------------------------------------------------------------------------*/

// We employ the parameters for Category 3 also in the case where the required
// security level is Category 2, where Category 2 has the following parameters.
//   #define TRNG_BYTE_LENGTH (32)
//   #define    HASH_FUNCTION sha3_256
//   #define HASH_BYTE_LENGTH (32)

/*----------------------------------------------------------------------------*/

#if (CATEGORY == 2) || (CATEGORY == 3)
#define TRNG_BYTE_LENGTH (32)
#define    HASH_FUNCTION sha3_384
#define HASH_BYTE_LENGTH (48)
// LEDA_N0 defined in the makefile
#if LEDA_N0 == 2
#define    LEDA_P  (25693)  // modulus(x) = x^P-1
#define    LEDA_DV (13)  // odd number
#define    LEDA_M  (9)
#define    LEDA_M0 (5)
#define    LEDA_M1 (4)
#define    NUM_ERRORS_T   (199)

#elif LEDA_N0 == 3
#define    LEDA_P  (16067)  // modulus(x) = x^P-1
#define    LEDA_DV (11)  // odd number
#define    LEDA_M  (11)
#define    LEDA_M0 (4)
#define    LEDA_M1 (4)
#define    LEDA_M2 (3)
#define    NUM_ERRORS_T   (127)

#elif LEDA_N0 == 4
#define    LEDA_P  (14341)  // modulus(x) = x^P-1
#define    LEDA_DV (15)  // odd number
#define    LEDA_M  (9)
#define    LEDA_M0 (3)
#define    LEDA_M1 (2)
#define    LEDA_M2 (2)
#define    LEDA_M3 (2)
#define    NUM_ERRORS_T   (101)

#else
#error "Unsupported number of circulant blocks"
#endif
#endif

/*----------------------------------------------------------------------------*/

// We employ the parameters for Category 4 also in the case where the required
// security level is Category 5, where Category 4 has the following parameters.
// #if CATEGORY == 4
//   #define TRNG_BYTE_LENGTH (40)
//   #define    HASH_FUNCTION sha3_384
//   #define HASH_BYTE_LENGTH (48)
// #endif

/*----------------------------------------------------------------------------*/

#if (CATEGORY == 4) || (CATEGORY == 5)
#define TRNG_BYTE_LENGTH (40)
#define    HASH_FUNCTION  sha3_512
#define HASH_BYTE_LENGTH (64)
// LEDA_N0 defined in the makefile
#if LEDA_N0 == 2
#define    LEDA_P  (36877)  // modulus(x) = x^P-1
#define    LEDA_DV (11)  // odd number
#define    LEDA_M  (13)
#define    LEDA_M0 (7)
#define    LEDA_M1 (6)
#define    NUM_ERRORS_T   (267)

#elif LEDA_N0 == 3
#define    LEDA_P  (27437)  // modulus(x) = x^P-1
#define    LEDA_DV (15)  // odd number
#define    LEDA_M  (11)
#define    LEDA_M0 (4)
#define    LEDA_M1 (4)
#define    LEDA_M2 (3)
#define    NUM_ERRORS_T   (169)

#elif LEDA_N0 == 4
#define    LEDA_P  (22691)  // modulus(x) = x^P-1
#define    LEDA_DV (13)  // odd number
#define    LEDA_M  (13)
#define    LEDA_M0 (4)
#define    LEDA_M1 (3)
#define    LEDA_M2 (3)
#define    LEDA_M3 (3)
#define    NUM_ERRORS_T   (134)

#else
#error "Unsupported number of circulant blocks"
#endif
#endif
/*----------------------------------------------------------------------------*/

// Derived parameters, they are useful for QC-LDPC algorithms
#define HASH_BIT_LENGTH (HASH_BYTE_LENGTH << 3)
#define               LEDA_K ((LEDA_N0-1)*LEDA_P)
#define               LEDA_N (LEDA_N0*LEDA_P)
#define              LEDA_DC (LEDA_N0*LEDA_DV)

// Circulant weight structure of the Q matrix, specialized per value of LEDA_N0

#if LEDA_N0 == 2
#define    Q_BLOCK_WEIGHTS  {{LEDA_M0,LEDA_M1},{LEDA_M1,LEDA_M0}}
#elif LEDA_N0 == 3
#define    Q_BLOCK_WEIGHTS  {{LEDA_M0,LEDA_M1,LEDA_M2},{LEDA_M2,LEDA_M0,LEDA_M1},{LEDA_M1,LEDA_M2,LEDA_M0}}
#elif LEDA_N0 == 4
#define    Q_BLOCK_WEIGHTS  {{LEDA_M0,LEDA_M1,LEDA_M2,LEDA_M3},{LEDA_M3,LEDA_M0,LEDA_M1,LEDA_M2},{LEDA_M2,LEDA_M3,LEDA_M0,LEDA_M1},{LEDA_M1,LEDA_M2,LEDA_M3,LEDA_M0}}
#else
#error "Unsupported number of circulant blocks"
#endif

static const unsigned char qBlockWeights[LEDA_N0][LEDA_N0] = Q_BLOCK_WEIGHTS;

/*----------------------------------------------------------------------------*/
