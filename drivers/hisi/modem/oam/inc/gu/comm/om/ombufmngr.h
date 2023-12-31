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

/******************************************************************************

                   (C), 2001-2012, 

 ******************************************************************************
       : ombufmngr.h
       : 
         : 
     : 20120731
     :
     : BM(Buffer Manager)
     :

        :
   1.       : 20120731
            : g47350
        : V900R001

******************************************************************************/

#ifndef __OMBUFMNGR_H__
#define __OMBUFMNGR_H__

/*****************************************************************************
  1 
*****************************************************************************/
#include "vos.h"


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
#define OM_RECORD_MAX_NUM  (100)


#define OM_ALLOC_RECORD(pData, lLen) \
    { \
        g_stOmBufRecord.astAllocItem[g_stOmBufRecord.ulAllocNum].pucData    = pData; \
        g_stOmBufRecord.astAllocItem[g_stOmBufRecord.ulAllocNum].lLen       = lLen; \
        g_stOmBufRecord.astAllocItem[g_stOmBufRecord.ulAllocNum].ulSlice    = VOS_GetSlice(); \
        \
        g_stOmBufRecord.ulAllocNum++; \
        /* */ \
        if (OM_RECORD_MAX_NUM == g_stOmBufRecord.ulAllocNum) \
        { \
            g_stOmBufRecord.ulAllocNum = 0; \
        } \
    } \

#define OM_RLS_RECORD(pData, lLen) \
    { \
        g_stOmBufRecord.astRlsItem[g_stOmBufRecord.ulRlsNum].pucData    = pData; \
        g_stOmBufRecord.astRlsItem[g_stOmBufRecord.ulRlsNum].lLen       = lLen; \
        g_stOmBufRecord.astRlsItem[g_stOmBufRecord.ulRlsNum].ulSlice    = VOS_GetSlice(); \
        \
        g_stOmBufRecord.ulRlsNum++; \
        /* */ \
        if (OM_RECORD_MAX_NUM == g_stOmBufRecord.ulRlsNum) \
        { \
            g_stOmBufRecord.ulRlsNum = 0; \
        } \
    } \

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
     : OM_BUF_CTRL_STRU
   : OM
*****************************************************************************/
typedef struct
{
    VOS_INT32                           lAlloc;         /*  */
    VOS_INT32                           lRelease;       /*  */
    VOS_INT32                           lPadding;       /*  */
    VOS_INT32                           lBufSize;       /*  */
    VOS_UINT8                          *pucBuf;         /*  */
    VOS_UINT8                          *pucRealBuf;     /*  */
}OM_BUF_CTRL_STRU;


typedef struct
{
    VOS_UINT8                          *pucData;
    VOS_INT32                           lLen;
    VOS_UINT32                          ulSlice;
}OM_DATA_ITEM_STRU;

typedef struct
{
    VOS_UINT32                          ulSocpBug;
    VOS_UINT32                          ulAllocNum;
    VOS_UINT32                          ulRlsNum;
    OM_DATA_ITEM_STRU                   astAllocItem[OM_RECORD_MAX_NUM];
    OM_DATA_ITEM_STRU                   astRlsItem[OM_RECORD_MAX_NUM];
}OM_BUF_RECORD_STRU;

/*****************************************************************************
  8 UNION
*****************************************************************************/
/*****************************************************************************
  9 OTHERS
*****************************************************************************/
extern OM_BUF_RECORD_STRU                      g_stOmBufRecord;

/*****************************************************************************
  10 
*****************************************************************************/

extern VOS_UINT32 OM_GetSlice(VOS_VOID);

/*****************************************************************************
     : OM_CreateTraceBuffer
   : OM
   : pstBufCtrl: 
             lBufSize:   

   : 

     : VOS_OK/VOS_ERR
*****************************************************************************/
VOS_UINT32 OM_CreateTraceBuffer(OM_BUF_CTRL_STRU *pstBufCtrl, VOS_INT32 lBufSize);

/*****************************************************************************
     : OM_AllocTraceMem
   : .
   : pstBufCtrl: 
             lLen:       

   : 

     : VOS_NULL_PTR 
             VOS_VOID*    
*****************************************************************************/
VOS_VOID* OM_AllocTraceMem(OM_BUF_CTRL_STRU *pstBufCtrl, VOS_INT32 lLen);

/*****************************************************************************
     : OM_ReleaseTraceMem
   : .
   : pstBufCtrl: 
             pucAddr:    
             lLen:      

   : 

     : VOS_OK/VOS_ERR
*****************************************************************************/
VOS_UINT32 OM_ReleaseTraceMem(OM_BUF_CTRL_STRU *pstBufCtrl,
                                        VOS_VOID *pAddr, VOS_INT32 lLen);

/*****************************************************************************
     : OM_TraceMemFreeBytes
   : .
   : pstBufCtrl: 

   : 

     : VOS_INT32 
*****************************************************************************/
VOS_INT32 OM_TraceMemNBytes(OM_BUF_CTRL_STRU *pstBufCtrl);

/*****************************************************************************
     : OM_AddrVirtToReal
   : .
   : pstBufCtrl: 
             pucVirtAddr:

   : 

     : VOS_NULL_PTR 
             VOS_VOID*    
*****************************************************************************/
VOS_VOID* OM_AddrVirtToReal(OM_BUF_CTRL_STRU *pstBufCtrl, VOS_UINT8 *pucVirtAddr);

/*****************************************************************************
     : OM_AddrRealToVirt
   : .
   : pstBufCtrl: 
             pucRealAddr:

   : 

     : VOS_NULL_PTR 
             VOS_VOID*    
*****************************************************************************/
VOS_VOID* OM_AddrRealToVirt(OM_BUF_CTRL_STRU *pstBufCtrl, VOS_UINT8 *pucRealAddr);

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif


#ifdef __cplusplus
#if __cplusplus
    }
#endif
#endif

#endif
