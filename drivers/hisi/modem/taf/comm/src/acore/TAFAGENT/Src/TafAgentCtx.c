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
#include  "TafAgentCtx.h"
#include  "TafAgentLog.h"




/*****************************************************************************
    .C
*****************************************************************************/

#define    THIS_FILE_ID                 PS_FILE_ID_TAF_AGENT_CTX_C

/*****************************************************************************
  2 
*****************************************************************************/

TAFAGENT_CTX_STRU                       g_stTafAgentCtx = {0};
TAF_AGENT_STATS_INFO_STRU               g_stTafAgentStats = {0};

/*****************************************************************************
  3 
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

  2.       : 201274
           : A00165503
       : DTS2012042102488: TAF AGENT, API
                 

  3.       : 2012717
           : A00165503
       : DTS2012071607302: TAFAPI, ,
                 API
*****************************************************************************/
VOS_UINT32 Taf_Agent_InitCtx(VOS_VOID)
{
    g_stTafAgentCtx.pucTafAcpuCnfMsg = VOS_NULL_PTR;

    /*  */
    if (VOS_OK != VOS_SmMCreate("SYNC", VOS_SEMA4_FIFO, &g_stTafAgentCtx.hTafAcpuSyncSem))
    {
        TAFAGENT_ERROR_LOG(ACPU_PID_TAFAGENT, "Create aps acpu sycn sem failed!");
        TAF_AGENT_DBG_CREATE_MUTEX_SEM_FAIL_NUM(1);
        g_stTafAgentCtx.ulInitFlg = VOS_FALSE;
        return VOS_ERR;
    }
    else
    {
        TAF_AGENT_DBG_SAVE_MUTEX_SEM_ID(g_stTafAgentCtx.hTafAcpuSyncSem);
    }

    /*  */
    if (VOS_OK != VOS_SmBCreate( "CNF", 0, VOS_SEMA4_FIFO, &g_stTafAgentCtx.hTafAcpuCnfSem))
    {
        TAFAGENT_ERROR_LOG(ACPU_PID_TAFAGENT, "Create aps acpu cnf sem failed!");
        TAF_AGENT_DBG_CREATE_BINARY_SEM_FAIL_NUM(1);
        g_stTafAgentCtx.ulInitFlg = VOS_FALSE;
        return VOS_ERR;
    }
    else
    {
        TAF_AGENT_DBG_SAVE_BINARY_SEM_ID(g_stTafAgentCtx.hTafAcpuCnfSem);
    }

    g_stTafAgentCtx.ulInitFlg = VOS_TRUE;

    TAF_AGENT_SET_ACPU_CNF_SEM_LOCK_FLG(VOS_FALSE);

    TAF_AGENT_ClearMsg();

    return VOS_OK;
}

/*****************************************************************************
     : TAF_AGETN_GetTafAcpuSyncSem
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
VOS_SEM TAF_AGENT_GetTafAcpuSyncSem(VOS_VOID)
{
    return g_stTafAgentCtx.hTafAcpuSyncSem;
}

/*****************************************************************************
     : TAF_AGENT_GetTafAcpuCnfSem
   : Cnf
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
VOS_SEM TAF_AGENT_GetTafAcpuCnfSem(VOS_VOID)
{
    return g_stTafAgentCtx.hTafAcpuCnfSem;
}

/*****************************************************************************
     : TAF_AGETN_GetTafAcpuCnfMsg
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
VOS_UINT8* TAF_AGENT_GetTafAcpuCnfMsg(VOS_VOID)
{
    return g_stTafAgentCtx.pucTafAcpuCnfMsg;
}

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
VOS_VOID TAF_AGENT_SetTafAcpuCnfMsg(VOS_UINT8* pMsg)
{
    g_stTafAgentCtx.pucTafAcpuCnfMsg = pMsg;
}

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
VOS_VOID TAF_AGENT_ClearMsg(VOS_VOID)
{
    TAF_MEM_SET_S(g_stTafAgentCtx.aucMsg, sizeof(g_stTafAgentCtx.aucMsg), 0x00, sizeof(g_stTafAgentCtx.aucMsg));
}

/*****************************************************************************
     : TAF_AGENT_SaveMsg
   : 
   :
   : VOS_UINT8*
     : VOS_VOID
   :
   :

       :
  1.       : 2011127
           : c00173809
       : 
*****************************************************************************/
VOS_UINT8* TAF_AGENT_SaveMsg(
    VOS_UINT8                          *pucMsg,
    VOS_UINT32                          ulLen
)
{
    if ((TAFAGENT_APS_MAX_MSG_LEN - VOS_MSG_HEAD_LENGTH) >= ulLen)
    {
        /*  */
        TAF_MEM_CPY_S(g_stTafAgentCtx.aucMsg, sizeof(g_stTafAgentCtx.aucMsg), pucMsg, ulLen + VOS_MSG_HEAD_LENGTH);

        return &(g_stTafAgentCtx.aucMsg[0]);
    }
    else
    {
        (VOS_VOID)vos_printf("TAF_AGENT_SaveMsg-->msg len too big\n");
        return VOS_NULL_PTR;
    }
}

/*****************************************************************************
     : TAF_AGENT_ShowStats
   : TAF AGENT, API
   : VOS_VOID
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 201274
           : A00165503
       : 

  2.       : 2012717
           : A00165503
       : DTS2012071607302: TAFAPI, ,
                 API
*****************************************************************************/
VOS_VOID TAF_AGENT_ShowStats(VOS_VOID)
{
    (VOS_VOID)vos_printf("********************TAF AGENT*******************\n");
    (VOS_VOID)vos_printf("                              %d\n", g_stTafAgentCtx.ulInitFlg);
    (VOS_VOID)vos_printf("                            %x\n", g_stTafAgentCtx.hTafAcpuSyncSem);
    (VOS_VOID)vos_printf("                            %x\n", g_stTafAgentCtx.hTafAcpuCnfSem);
    (VOS_VOID)vos_printf("                            %p\n", g_stTafAgentStats.ulMutexSemId);
    (VOS_VOID)vos_printf("                          %p\n", g_stTafAgentStats.ulBinarySemId);
    (VOS_VOID)vos_printf("                      %d\n", g_stTafAgentStats.ulCreateMutexSemFailNum);
    (VOS_VOID)vos_printf("                    %d\n", g_stTafAgentStats.ulCreateBinarySemFailNum);
    (VOS_VOID)vos_printf("                        %d\n", g_stTafAgentStats.ulLockMutexSemFailNum);
    (VOS_VOID)vos_printf("                      %d\n", g_stTafAgentStats.ulLockBinarySemFailNum);
    (VOS_VOID)vos_printf("                %x\n", g_stTafAgentStats.ulLastMutexSemErrRslt);
    (VOS_VOID)vos_printf("              %x\n", g_stTafAgentStats.ulLastBinarySemErrRslt);
    (VOS_VOID)vos_printf("                            %d\n", g_stTafAgentStats.ulSyncMsgIsNullNum);
    (VOS_VOID)vos_printf("                          %d\n", g_stTafAgentStats.ulSyncMsgNotMatchNum);

    (VOS_VOID)vos_printf("\r\n");

}



