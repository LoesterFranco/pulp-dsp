/* =====================================================================
 * Project:      PULP DSP Library
 * Title:        plp_bitreversal_xpulpv2.c
 * Description:  Bitreversal functions
 *
 * $Date:        3. July 2020
 * $Revision:    V0
 *
 * Target Processor: PULP cores
 * ===================================================================== */
/*
 * Copyright (C) 2020 ETH Zurich and University of Bologna. All rights reserved.
 *
 * Author: Michael Rogenmoser, ETH Zurich
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
 * @ingroup groupTransforms
 */

/**
 * @addtogroup fft
 * @{
 */


/**
  @brief         In-place 16 bit reversal function.
  @param[in,out] pSrc        points to in-place buffer of unknown 16-bit data type
  @param[in]     bitRevLen   bit reversal table length
  @param[in]     pBitRevTab  points to bit reversal table
  @return        none
*/

void plp_bitreversal_16v_xpulpv2(
        uint16_t *pSrc,
  const uint16_t bitRevLen,
  const uint16_t *pBitRevTab)
{
  uint16_t a, b, i, tmp;

  v2s c;

  for (i = 0; i < bitRevLen; )
  {
     // a = pBitRevTab[i    ] >> 2;
     // b = pBitRevTab[i + 1] >> 2;

     c = __SRA2(*(v2s *) & pBitRevTab[i], ((v2s){2,2}));

     //real
     // tmp = pSrc[a];
     // pSrc[a] = pSrc[b];
     // pSrc[b] = tmp;

     tmp = pSrc[c[0]];
     pSrc[c[0]] = pSrc[c[1]];
     pSrc[c[1]] = tmp;

     //complex
     // tmp = pSrc[a+1];
     // pSrc[a+1] = pSrc[b+1];
     // pSrc[b+1] = tmp;

     tmp = pSrc[c[0]+1];
     pSrc[c[0]+1] = pSrc[c[1]+1];
     pSrc[c[1]+1] = tmp;

    i += 2;
  }
}


/**
 * @} end of FFT group
 */
