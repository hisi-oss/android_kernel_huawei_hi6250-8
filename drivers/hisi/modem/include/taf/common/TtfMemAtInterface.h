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

#ifndef __TTFMEMATINTERFACE_H__
#define __TTFMEMATINTERFACE_H__


/*****************************************************************************
  1 
*****************************************************************************/
#include "v_typdef.h"



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 
*****************************************************************************/


/*****************************************************************************
  3 
*****************************************************************************/


/*****************************************************************************
    : TTF_AT_MSG_ID_ENUM_UINT32
  : ATTTF

  1.       : 20111222
           :
       : AT->TTF CCPU MEM

*****************************************************************************/
enum TTF_AT_MSG_ID_ENUM
{
    /* AT->TTF CCPU MEM */
    ID_TTF_AT_QRY_CCPU_MEM_INFO_IND,                                             /* _H2ASN_MsgChoice TAFAGENT_APS_FIND_CID_FOR_DIAL_CNF_STRU */

    ID_TTF_AT_MSG_ID_ENUM_BUTT
};
typedef VOS_UINT32  TTF_AT_MSG_ID_ENUM_UINT32;

/*****************************************************************************
  4 
*****************************************************************************/


/*****************************************************************************
  5 
*****************************************************************************/


/*****************************************************************************
  6 
*****************************************************************************/


/*****************************************************************************
  7 STRUCT
*****************************************************************************/

/*****************************************************************************
     : TTF_MEM_RB_CCPU_MEM_INFO_IND_STRU
   : TTF_MEM_RB_CCPU_MEM_INFO_IND_STRU,
 1.       : 20111219
          : C00173809
      : 
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    TTF_AT_MSG_ID_ENUM_UINT32     enMsgId;

} TTF_MEM_RB_CCPU_MEM_INFO_IND_STRU;

/*****************************************************************************
  8 UNION
*****************************************************************************/


/*****************************************************************************
  9 OTHERS
*****************************************************************************/


/*****************************************************************************
  10 
*****************************************************************************/
/*****************************************************************************
     : TTF_NodeMemCheckNodeLeak
   : TTF
   : 
   : 
     : 0
   :
   :

       :
  1.       : 20160912
           : c00199705
       : 

*****************************************************************************/
extern VOS_UINT32 TTF_NodeMemCheckNodeLeak(VOS_VOID);

/*****************************************************************************
     : RRM_NodeMemCheckNodeLeak
   : RRM
   : 
   : 
     : 0
   :
   :

       :
  1.       : 20160912
           : c00199705
       : 

*****************************************************************************/
extern VOS_UINT32 RRM_NodeMemCheckNodeLeak(VOS_VOID);

/*****************************************************************************
     : TTF_MemCcpuCheckPoolLeak
   : C
   : VOS_VOID
   : 
     : 0
   :
   :

       :
  1.       : 2012112
           : s00164817
       : 

*****************************************************************************/
extern VOS_UINT32 TTF_MemCcpuCheckPoolLeak(VOS_VOID);


#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of TTFMemInterface.h */


