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

#ifndef _ATCSDINTERFACE_H_
#define _ATCSDINTERFACE_H_

/*****************************************************************************
  1 
*****************************************************************************/
#include "vos.h"
#include "ImmInterface.h"
#include "product_config.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 
*****************************************************************************/
#if(FEATURE_ON == FEATURE_CSD)


/*****************************************************************************
  3 
*****************************************************************************/

/*****************************************************************************
   : AT_CSD_MSG_ID_ENUM
 : ATCSD

  1.       : 2011126
           : w00199382
       : 
*****************************************************************************/
enum AT_CSD_MSG_ID_ENUM
{
    ID_AT_CSD_CALL_STATE_IND            = 0X0001,                               /**/
    ID_AT_CSD_MSG_ID_ENUM_BUTT
};
typedef VOS_UINT32 AT_CSD_MSG_ID_ENUM_UINT32;

/*****************************************************************************
   : AT_CSD_CALL_STATE_TYPE_ENUM
 : 

  1.       : 2011126
           : w00199382
       : 
*****************************************************************************/
enum AT_CSD_CALL_TYPE_STATE
{
    AT_CSD_CALL_STATE_ON                = 0X0001,                               /**/
    AT_CSD_CALL_STATE_OFF                       ,                               /**/
    AT_CSD_CALL_STATE_BUTT
};
typedef VOS_UINT16 AT_CSD_CALL_TYPE_STATE_ENUM_UINT16;

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
    : AT_CSD_CALL_STATE_TYPE_IND_STRU
  : 

  1.       : 2011126
           : w00199382
       : 
  2.       : 20130528
           : f00179208
       : V3R3 PPP PROJECT
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /**/
    AT_CSD_MSG_ID_ENUM_UINT32           enMsgId;                                /*ID*/
    AT_CSD_CALL_TYPE_STATE_ENUM_UINT16  enCallState;                            /**/
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           aucReserved[1];
}AT_CSD_CALL_STATE_TYPE_IND_STRU;


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
     : CSD_UL_SendData
   : USB_MODEMAt_UsbModemDataInd
   : IMM_ZC_STRU *pstULData
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20111214
           : w00199382
       : 

*****************************************************************************/
extern VOS_VOID CSD_UL_SendData(IMM_ZC_STRU *pstULData);



#endif/*FEATURE_CSD*/

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

#endif /* end of CsdInterface.h */

