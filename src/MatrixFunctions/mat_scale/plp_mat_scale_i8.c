/* =====================================================================
 * Project:      PULP DSP Library
 * Title:        plp_mat_scale_i8.c
 * Description:  16-bit integer matrix scale glue code
 *
 * $Date:        6. July 2020
 * $Revision:    V0
 *
 * Target Processor: PULP cores
 * ===================================================================== */
/*
 * Copyright (C) 2020 ETH Zurich and Ubiversity of Bologna. All rights reserved.
 *
 * Author: Tibor Schneider, ETH Zurich
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
  @ingroup groupMatrix
 */

/**
  @addtogroup MatScale
  @{
 */

/**
  @brief Glue code for matrix scale of 16-bit integer matrices.
  @param[in]  pSrc        Points to the input matrix
  @param[in]  M           Height of both matrices
  @param[in]  N           Width of both matrices
  @param[in]  scaleFactor Factor to mulitply all elements before shifting
  @param[in]  shift       Amount to shift each element
  @param[out] pDst        Points to the output matrix
  @return     none
 */

void plp_mat_scale_i8(const int8_t * __restrict__ pSrc,
                      uint32_t M,
                      uint32_t N,
                      int8_t scaleFactor,
                      int32_t shift,
                      int8_t * __restrict__ pDst){

    if (rt_cluster_id() == ARCHI_FC_CID){
        plp_mat_scale_i8s_rv32im(pSrc, M, N, scaleFactor, shift, pDst);
    }
    else{
        plp_mat_scale_i8v_xpulpv2(pSrc, M, N, scaleFactor, shift, pDst);
    }

}

/**
  @} end of MatScale group
 */


