/* =====================================================================
 * Project:      PULP DSP Library
 * Title:        plp_dot_prod_q16v_xpulpv2.c
 * Description:  16-bit fixed point vectorized dot product for XPULPV2
 *
 * $Date:        26. May 2019
 * $Revision:    V0
 *
 * Target Processor: PULP cores
 * ===================================================================== */
/*
 * Copyright (C) 2019 ETH Zurich and University of Bologna. All rights reserved.
 *
 * Author: Xiaying Wang, ETH Zurich
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "plp_math.h"


/**
  @ingroup BasicDotProd
 */


/**
  @addtogroup BasicDotProdKernels
  @{
 */

/**
  @brief Vectorized dot product of 16-bit fixed point vectors kernel for XPULPV2 extension.
  @param[in]  pSrcA      points to the first input vector [16 bit]
  @param[in]  pSrcB      points to the second input vector [16 bit]
  @param[in]  blockSize  number of samples in each vector
  @param[in]  deciPoint  decimal point for right shift
  @param[out] pRes     output result returned here [32 bit]
  @return        none

  @par Exploiting SIMD instructions
  The 16 bit values are packed two by two into 32 bit vectors and then the two dot products are performed simultaneously on 32 bit vectors, with 32 bit accumulator.
 */

void plp_dot_prod_q16v_xpulpv2(
                               const int16_t * __restrict__ pSrcA,
                               const int16_t * __restrict__ pSrcB,
                               uint32_t blockSize,
                               uint32_t deciPoint,
                               int32_t * __restrict__ pRes){

  uint32_t blkCnt, tmpBS, remBS;                   /* Loop counter, temporal BlockSize */
  int32_t sum = 0;
  //  int32_t sum1 = 0, sum2 = 0;                          /* Temporary return variable */

#if defined(PLP_MATH_LOOPUNROLL)

        tmpBS = (blockSize>>2);

        for (blkCnt=0; blkCnt<tmpBS; blkCnt++){

          v2s a0 = *((v2s*)((void*)(pSrcA+4*blkCnt)));
          v2s b0 = *((v2s*)((void*)(pSrcB+4*blkCnt)));
          v2s a1 = *((v2s*)((void*)(pSrcA+4*blkCnt+2)));
          v2s b1 = *((v2s*)((void*)(pSrcB+4*blkCnt+2)));
          //sum = __SUMDOTP2(a0, b0, sum);
          //sum = sum >> deciPoint;
          //sum = __SUMDOTP2(a1, b1, sum);
          //sum = sum >> deciPoint;
          int32_t x0 = __DOTP2(a0, b0);
          int32_t x1 = __DOTP2(a1, b1);
          sum += __ADDROUNDNORM_REG(x0, x1, deciPoint);

          //sum = __MAC(sum, (*pSrcA++), (*pSrcB++));
          //sum = __MAC(sum, (*pSrcA++), (*pSrcB++));
        }

        remBS = (blockSize%4U);

        for (blkCnt=0; blkCnt<remBS; blkCnt++){
          int16_t a = *(pSrcA+4*tmpBS+blkCnt);
          int16_t b = *(pSrcB+4*tmpBS+blkCnt);
          //sum += a*b;
          //sum = sum >> deciPoint;
          sum += __ROUNDNORM_REG(a * b, deciPoint);
          //sum = __MAC(sum, (*pSrcA++), (*pSrcB++));
        }

#else // PLP_MATH_LOOPUNROLL

        for (blkCnt=0; blkCnt<blockSize; blkCnt++){
          //sum = __MAC(sum, (*pSrcA++), (*pSrcB++));
          sum += __ROUNDNORM_REG((*pSrcA++) * (*pSrcB++), deciPoint);
        }

#endif // PLP_MATH_LOOPUNROLL

        * pRes = sum; //sum1 + sum2;

}

/**
   @} end of BasicDotProdKernels group
*/

