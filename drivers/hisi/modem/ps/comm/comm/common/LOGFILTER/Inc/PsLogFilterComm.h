/*
 * Copyright (C) Huawei Technologies Co., Ltd. 2012-2015. All rights reserved.
 * foss@huawei.com
 *
 * If distributed as part of the Linux kernel, the following license terms
 * apply:
 *
 * * This program is free software; you can redistribute it and/or modify
 * * it under the terms of the GNU General Public License version 2 and
 * * only version 2 as published by the Free Software Foundation.
 * *
 * * This program is distributed in the hope that it will be useful,
 * * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * * GNU General Public License for more details.
 * *
 * * You should have received a copy of the GNU General Public License
 * * along with this program; if not, write to the Free Software
 * * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
 *
 * Otherwise, the following license terms apply:
 *
 * * Redistribution and use in source and binary forms, with or without
 * * modification, are permitted provided that the following conditions
 * * are met:
 * * 1) Redistributions of source code must retain the above copyright
 * *    notice, this list of conditions and the following disclaimer.
 * * 2) Redistributions in binary form must reproduce the above copyright
 * *    notice, this list of conditions and the following disclaimer in the
 * *    documentation and/or other materials provided with the distribution.
 * * 3) Neither the name of Huawei nor the names of its contributors may
 * *    be used to endorse or promote products derived from this software
 * *    without specific prior written permission.
 *
 * * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef __PSLOGFILTERCOMM_H__
#define __PSLOGFILTERCOM_H__


/******************************************************************************
  1 
******************************************************************************/
#include "vos.h"
#include "PsLogFilterInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)


/******************************************************************************
  2 
******************************************************************************/

/******************************************************************************
  3 
******************************************************************************/


/******************************************************************************
  4 
******************************************************************************/


/******************************************************************************
  5 
******************************************************************************/


/******************************************************************************
  6 
******************************************************************************/


/******************************************************************************
  7 STRUCT
******************************************************************************/

/******************************************************************************
  8 UNION
******************************************************************************/


/******************************************************************************
  9 OTHERS
*****************************************************************************/


/*****************************************************************************
     : PS_OM_LayerMsgMatchFuncCommReg
   : A CMsgMatch
   : MsgMatchFunc:
                PS_OM_LAYER_MSG_MATCH_PFUNC         pFunc,
             MsgMatchFunc+1:
                VOS_UINT32                         *pulRegCnt,
             MsgMatchFunc:
                PS_OM_LAYER_MSG_MATCH_PFUNC         apfuncMatchEntry[],
             MsgMatchFunc:
                VOS_UINT32                          ulMsgMatchItemMaxCnt
:
             1.
               
             2.:
               VOS_NULL
               
                 
                 
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 2016113
           : z00383822
       : 

*****************************************************************************/
VOS_UINT32 PS_OM_LayerMsgMatchFuncCommReg
(
    PS_OM_LAYER_MSG_MATCH_PFUNC         pFunc,
    VOS_UINT32                         *pulRegCnt,
    PS_OM_LAYER_MSG_MATCH_PFUNC        *apfuncMatchEntry,
    VOS_UINT32                          ulMsgMatchItemMaxCnt
);


/*****************************************************************************
     : PS_OM_LayerMsgCommMatch
   : A C
   : :
                VOS_VOID                           *pMsg,
             MsgMatchFunc:
                VOS_UINT32                          ulRegCnt,
             MsgMatchFunc:
                PS_OM_LAYER_MSG_MATCH_PFUNC         apfuncMatchEntry[],
             MsgMatchFunc:
                VOS_UINT32                          ulMsgMatchItemMaxCnt
   : 
     : VOS_VOID*
   :
   :

       :
  1.       : 20161114
           : z00383822
       : 

*****************************************************************************/
VOS_VOID* PS_OM_LayerMsgCommMatch
(
    VOS_VOID                           *pMsg,
    VOS_UINT32                          ulRegCnt,
    PS_OM_LAYER_MSG_MATCH_PFUNC        *apfuncMatchEntry,
    VOS_UINT32                          ulMsgMatchItemMaxCnt
);


/*****************************************************************************
     : PS_OM_LayerMsgFilterFuncReg
   : AC MsgMatch
   :MsgFilterFunc:
                PS_OM_LAYER_MSG_FILTER_PFUNC         pFunc,
            MsgFilterFunc:
                VOS_UINT32                          *pulRegCnt,
            MsgFilterFunc:
                PS_OM_LAYER_MSG_FILTER_PFUNC         apfuncFilterEntry[],
            MsgFilterFunc:
                VOS_UINT32                           ulMsgFilterItemMaxCnt
            :
             1.VOS_FALSE
               
             2.VOS_TRUE
               
   : 
     : VOS_UINT32
   :
   :
       :
  1.       : 2016113
           : z00383822
       : 

*****************************************************************************/
VOS_UINT32 PS_OM_LayerMsgFilterFuncCommReg
(
    PS_OM_LAYER_MSG_FILTER_PFUNC         pFunc,
    VOS_UINT32                          *pulRegCnt,
    PS_OM_LAYER_MSG_FILTER_PFUNC        *apfuncFilterEntry,
    VOS_UINT32                           ulMsgFilterItemMaxCnt
);


/*****************************************************************************
     : PS_OM_LayerMsgCommFilter
   : AC 
   : :
                const VOS_VOID                     *pMsg,
             MsgFilterFunc:
                VOS_UINT32                          ulRegCnt,
             MsgFilterFunc:
                PS_OM_LAYER_MSG_MATCH_PFUNC         apfuncFilterEntry[],
             MsgFilterFunc:
                VOS_UINT32                          ulCount
   : 
     : VOS_UINT32:
                VOS_TRUE:  
                VOS_FALSE: 
   :
   :
       :
  1.       : 2016113
           : z00383822
       : 
*****************************************************************************/
VOS_UINT32 PS_OM_LayerMsgCommFilter
(
    const VOS_VOID                     *pMsg,
    VOS_UINT32                          ulRegCnt,
    PS_OM_LAYER_MSG_FILTER_PFUNC       *apfuncFilterEntry,
    VOS_UINT32                          ulMsgFilterItemMaxCnt
);


#pragma pack()


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* PsLogFilterComm.h */


