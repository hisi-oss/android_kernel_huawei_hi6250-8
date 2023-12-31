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

/*****************************************************************************
  1 
*****************************************************************************/
#ifndef _TAFAGENT_CTX_H_
#define _TAFAGENT_CTX_H_


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
#define TAFAGENT_APS_MAX_MSG_LEN       (512)

#define TAF_AGENT_SET_ACPU_CNF_SEM_LOCK_FLG(locked)         (g_stTafAgentCtx.ulAcpuCnfSemLockedFlg = (locked))
#define TAF_AGENT_GET_ACPU_CNF_SEM_LOCK_FLG()               (g_stTafAgentCtx.ulAcpuCnfSemLockedFlg)

#define TAF_AGENT_DBG_SAVE_MUTEX_SEM_ID(sem_id)             (g_stTafAgentStats.ulMutexSemId = (sem_id))
#define TAF_AGENT_DBG_SAVE_BINARY_SEM_ID(sem_id)            (g_stTafAgentStats.ulBinarySemId = (sem_id))
#define TAF_AGENT_DBG_CREATE_MUTEX_SEM_FAIL_NUM(n)          (g_stTafAgentStats.ulCreateMutexSemFailNum += (n))
#define TAF_AGENT_DBG_CREATE_BINARY_SEM_FAIL_NUM(n)         (g_stTafAgentStats.ulCreateBinarySemFailNum += (n))
#define TAF_AGENT_DBG_LOCK_MUTEX_SEM_FAIL_NUM(n)            (g_stTafAgentStats.ulLockMutexSemFailNum += (n))
#define TAF_AGENT_DBG_LOCK_BINARY_SEM_FAIL_NUM(n)           (g_stTafAgentStats.ulLockBinarySemFailNum += (n))
#define TAF_AGENT_DBG_SAVE_LAST_MUTEX_SEM_ERR_RSLT(rslt)    (g_stTafAgentStats.ulLastMutexSemErrRslt = (rslt))
#define TAF_AGENT_DBG_SAVE_LAST_BIN_SEM_ERR_RSLT(rslt)      (g_stTafAgentStats.ulLastBinarySemErrRslt = (rslt))
#define TAF_AGENT_DBG_SYNC_MSG_IS_NULL_NUM(n)               (g_stTafAgentStats.ulSyncMsgIsNullNum += (n))
#define TAF_AGENT_DBG_SYNC_MSG_NOT_MATCH_NUM(n)             (g_stTafAgentStats.ulSyncMsgNotMatchNum += (n))


/*****************************************************************************
  3 
*****************************************************************************/


/*****************************************************************************
  2 
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
    : TAFAGENT_CTX_STRU
  : TAFAGENT
  1.       : 20120102
           : C00173809
       : 

  2.       : 2012717
           : A00165503
       : DTS2012071607302: TAFAPI, ,
                 API
*****************************************************************************/
typedef struct
{
    /* PSAPI,(0xFFFFFFFF) */
    VOS_SEM                             hTafAcpuSyncSem;

    /*  */
    VOS_SEM                             hTafAcpuCnfSem;

    /* , VOS_TRUE: ; VOS_FALSE:  */
    VOS_UINT32                          ulInitFlg;

    /*  */
    VOS_UINT32                          ulAcpuCnfSemLockedFlg;

    /* PSAPI */
    VOS_UINT8                          *pucTafAcpuCnfMsg;

    VOS_UINT8                           aucMsg[TAFAGENT_APS_MAX_MSG_LEN];
}TAFAGENT_CTX_STRU;

/*****************************************************************************
     : TAF_AGENT_STATS_INFO_STRU
   :
 ASN.1 :
   : TAFAGENT
  1.       : 201273
           : A00165503
       : 

  2.       : 2012717
           : A00165503
       : DTS2012071607302: TAFAPI, ,
                 API
*****************************************************************************/
typedef struct
{
    VOS_SEM                             ulMutexSemId;               /* ID */
    VOS_SEM                             ulBinarySemId;              /* ID */
    VOS_UINT32                          ulCreateMutexSemFailNum;    /*  */
    VOS_UINT32                          ulCreateBinarySemFailNum;   /*  */
    VOS_UINT32                          ulLockMutexSemFailNum;      /*  */
    VOS_UINT32                          ulLockBinarySemFailNum;     /*  */
    VOS_UINT32                          ulLastMutexSemErrRslt;      /*  */
    VOS_UINT32                          ulLastBinarySemErrRslt;     /*  */
    VOS_UINT32                          ulSyncMsgIsNullNum;         /*  */
    VOS_UINT32                          ulSyncMsgNotMatchNum;       /*  */

} TAF_AGENT_STATS_INFO_STRU;


/*****************************************************************************
  8 UNION
*****************************************************************************/


/*****************************************************************************
  9 OTHERS
*****************************************************************************/

extern TAF_AGENT_STATS_INFO_STRU        g_stTafAgentStats;

extern TAFAGENT_CTX_STRU                g_stTafAgentCtx;


/*****************************************************************************
  10 
*****************************************************************************/
/*****************************************************************************
     : Taf_Agent_InitCtx
   : Taf Agent
   : VOS_VOID
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 2011127
           : c00173809
       : 
*****************************************************************************/
extern VOS_UINT32 Taf_Agent_InitCtx(VOS_VOID);

/*****************************************************************************
     : TAF_AGENT_GetTafAcpuSyncSem
   : SYNC
   : VOS_VOID
   : 
     : VOS_SEM
   :
   :

       :
  1.       : 2011127
           : c00173809
       : 
*****************************************************************************/
extern VOS_SEM TAF_AGENT_GetTafAcpuSyncSem(VOS_VOID);

/*****************************************************************************
     : TAF_AGENT_GetTafAcpuCnfSem
   : Cnf
   : VOS_VOID
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 2011127
           : c00173809
       : 
*****************************************************************************/
extern VOS_SEM TAF_AGENT_GetTafAcpuCnfSem(VOS_VOID);

/*****************************************************************************
     : TAF_AGENT_GetTafAcpuCnfMsg
   : 
   : VOS_VOID
   : 
     : MsgBlock*
   :
   :

       :
  1.       : 2011127
           : c00173809
       : 
*****************************************************************************/
extern VOS_UINT8* TAF_AGENT_GetTafAcpuCnfMsg(VOS_VOID);

/*****************************************************************************
     : TAF_AGENT_SetTafAcpuCnfMsg
   : 
   : MsgBlock* pMsg
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 2011127
           : c00173809
       : 
*****************************************************************************/
extern VOS_VOID TAF_AGENT_SetTafAcpuCnfMsg(VOS_UINT8* pMsg);

/*****************************************************************************
     : TAF_AGENT_ClearMsg
   : 
   :
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 2011127
           : c00173809
       : 
*****************************************************************************/
extern VOS_VOID TAF_AGENT_ClearMsg(VOS_VOID);

/*****************************************************************************
     : TAF_AGENT_SaveMsg
   : 
   :
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 2011127
           : c00173809
       : 
*****************************************************************************/
extern VOS_UINT8* TAF_AGENT_SaveMsg(
    VOS_UINT8                          *pucMsg,
    VOS_UINT32                          ulLen
);

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

#endif

