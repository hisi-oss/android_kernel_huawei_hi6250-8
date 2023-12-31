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

#ifndef __CSDDEBUG_H__
#define __CSDDEBUG_H__

/*****************************************************************************
  1 
*****************************************************************************/
#include  "vos.h"
/* Added by l60609 for AP 2012-08-30 Begin */
#include "product_config.h"
/* Added by l60609 for AP 2012-08-30 End */

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 
*****************************************************************************/
#if( FEATURE_ON == FEATURE_CSD )

/*****************************************************************************
  3 
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
     : CSD_UL_STATUS_INFO_STRU
   :
 ASN.1 :
   : CSD
  1.       : 2012120
           : w00199382
       : 
*****************************************************************************/
typedef struct
{
    /*CSD*/
    VOS_UINT32                          ulULRecvPktNum;                         /*CSD*/
    VOS_UINT32                          ulULSaveBuffPktNum;                     /*CSD*/
    VOS_UINT32                          ulULEnQueFail;                          /*CSD*/
    VOS_UINT32                          ulULSendPktNum;                         /*CSD*/
    VOS_UINT32                          ulULQueNullNum;                         /*CSD*/
    VOS_UINT32                          ulULZcToImmFailNum;                     /*CSDsk_bufferIMM*/
    VOS_UINT32                          ulULInsertDiccFailNum;                  /*CSDDICC*/

    /*CSD*/
    VOS_UINT32                          ulDLRecvPktNum;                         /*CSD*/
    VOS_UINT32                          ulDLSendPktNum;                         /*CSD*/
    VOS_UINT32                          ulDLSendFailNum;                        /*CSD*/

}CSD_UL_STATUS_INFO_STRU;

/*****************************************************************************
  8 
*****************************************************************************/
extern CSD_UL_STATUS_INFO_STRU          g_stCsdStatusInfo;

/*****************************************************************************
  10 
*****************************************************************************/

/*CSD*/
#define CSD_DBG_UL_RECV_PKT_NUM(n)      (g_stCsdStatusInfo.ulULRecvPktNum       += (n))
#define CSD_DBG_UL_SAVE_BUFF_PKT_NUM(n) (g_stCsdStatusInfo.ulULSaveBuffPktNum   += (n))
#define CSD_DBG_UL_ENQUE_FAIL_NUM(n)    (g_stCsdStatusInfo.ulULEnQueFail        += (n))
#define CSD_DBG_UL_SEND_PKT_NUM(n)      (g_stCsdStatusInfo.ulULSendPktNum       += (n))
#define CSD_DBG_UL_QUENULL_NUM(n)       (g_stCsdStatusInfo.ulULQueNullNum       += (n))
#define CSD_DBG_UL_ZCTOIMM_FAIL_NUM(n)  (g_stCsdStatusInfo.ulULZcToImmFailNum   += (n))
#define CSD_DBG_UL_INSERT_FAIL_NUM(n)   (g_stCsdStatusInfo.ulULInsertDiccFailNum += (n))

/*CSD*/
#define CSD_DBG_DL_RECV_PKT_NUM(n)      (g_stCsdStatusInfo.ulDLRecvPktNum       += (n))
#define CSD_DBG_DL_SEND_PKT_NUM(n)      (g_stCsdStatusInfo.ulDLSendPktNum       += (n))
#define CSD_DBG_DL_SEND_FAIL_NUM(n)     (g_stCsdStatusInfo.ulDLSendFailNum      += (n))



#endif

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

#endif /* end of CsdDebug.h */
