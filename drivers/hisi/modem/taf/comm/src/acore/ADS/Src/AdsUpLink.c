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
#include "AdsUpLink.h"
#include "AcpuReset.h"
#include "NasNvInterface.h"
#include "TafNvInterface.h"
#include "AdsFilter.h"
#include "AdsDebug.h"
#include "AdsMntn.h"



/*****************************************************************************
    .C
*****************************************************************************/
#define    THIS_FILE_ID                 PS_FILE_ID_ADS_UPLINK_C


/*****************************************************************************
  2 
*****************************************************************************/

/*****************************************************************************
  3 
*****************************************************************************/

/*****************************************************************************
     : ADS_UL_CCpuResetCallback
   : CADS UL
   : enParam   -- 0 
             iUserData -- 
   : 
     : VOS_INT
   :
   :

      :
 1.       : 20130410
          : f00179208
      : 
*****************************************************************************/
VOS_INT ADS_UL_CCpuResetCallback(
    DRV_RESET_CB_MOMENT_E               enParam,
    VOS_INT                             iUserData
)
{
    ADS_CCPU_RESET_IND_STRU                 *pstMsg = VOS_NULL_PTR;

    /* 0 */
    if (MDRV_RESET_CB_BEFORE == enParam)
    {
        ADS_TRACE_HIGH("before reset: enter.\n");

        ADS_SetUlResetFlag(VOS_TRUE);

        /*  */
        pstMsg = (ADS_CCPU_RESET_IND_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(ACPU_PID_ADS_UL,
                                                                        sizeof(ADS_CCPU_RESET_IND_STRU));
        if (VOS_NULL_PTR == pstMsg)
        {
            ADS_TRACE_HIGH("before reset: alloc msg failed.\n");
            return VOS_ERROR;
        }

        /*  */
        pstMsg->ulReceiverPid               = ACPU_PID_ADS_UL;
        pstMsg->enMsgId                     = ID_ADS_CCPU_RESET_START_IND;

        /*  */
        if (VOS_OK != PS_SEND_MSG(ACPU_PID_ADS_UL, pstMsg))
        {
            ADS_TRACE_HIGH("before reset: send msg failed.\n");
            return VOS_ERROR;
        }

        /*  */
        if (VOS_OK != VOS_SmP(ADS_GetULResetSem(), ADS_RESET_TIMEOUT_LEN))
        {
            ADS_TRACE_HIGH("before reset: VOS_SmP failed.\n");
            ADS_DBG_UL_RESET_LOCK_FAIL_NUM(1);
            return VOS_ERROR;
        }

        ADS_TRACE_HIGH("before reset: succ.\n");
        return VOS_OK;
    }
    /*  */
    else if (MDRV_RESET_CB_AFTER == enParam)
    {
        ADS_TRACE_HIGH("after reset enter.\n");

        ADS_SetUlResetFlag(VOS_FALSE);

        ADS_TRACE_HIGH("after reset: succ.\n");
        ADS_DBG_UL_RESET_SUCC_NUM(1);
        return VOS_OK;
    }
    else
    {
        return VOS_ERROR;
    }
}

/*****************************************************************************
     : ADS_UL_StartDsFlowStats
   : 
   : ucInstance - 
             ucRabId    - RABID [5,15]
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 2013822
           : A00165503
       : 
*****************************************************************************/
VOS_VOID ADS_UL_StartDsFlowStats(
    VOS_UINT8                           ucInstance,
    VOS_UINT8                           ucRabId
)
{
    /* ,  */
    if (VOS_OK == ADS_UL_IsQueueExistent(ucInstance, ucRabId))
    {
        ADS_StartTimer(TI_ADS_DSFLOW_STATS, TI_ADS_DSFLOW_STATS_LEN);
    }

    return;
}

/*****************************************************************************
     : ADS_UL_StopDsFlowStats
   : 
   : ucInstance - 
             ucRabId    - RABID [5,15]
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 2013822
           : A00165503
       : 
*****************************************************************************/
VOS_VOID ADS_UL_StopDsFlowStats(
    VOS_UINT8                           ucInstance,
    VOS_UINT8                           ucRabId
)
{
    /*  */
    if (VOS_FALSE == ADS_UL_IsAnyQueueExist())
    {
        ADS_StopTimer(ACPU_PID_ADS_UL, TI_ADS_DSFLOW_STATS, ADS_TIMER_STOP_CAUSE_USER);
        ADS_InitStatsInfoCtx();
    }

    return;
}

/*****************************************************************************
     : ADS_UL_SendPacket
   : ADS
             
   : pstImmZc  --- IMM
             ucExRabId --- RABID [5, 15]
   : 
     : VOS_OK/VOS_ERR
   :
   :

       :
  1.       : 2011127
           : /l60609
       : 

  2.       : 2016617
           : A00165503
       : DTS2016061504494: 0

*****************************************************************************/
VOS_UINT32 ADS_UL_SendPacket(
    IMM_ZC_STRU                        *pstImmZc,
    VOS_UINT8                           ucExRabId
)
{
    VOS_UINT8                           ucInstance;
    VOS_UINT8                           ucRabId;

    /*  */
    if (VOS_NULL_PTR == pstImmZc)
    {
        ADS_WARNING_LOG(ACPU_PID_ADS_UL, "ADS_UL_SendPacket: pstImmZc is null!");
        return VOS_ERR;
    }

    if (0 == IMM_ZcGetUsedLen(pstImmZc))
    {
        ADS_WARNING_LOG(ACPU_PID_ADS_UL, "ADS_UL_SendPacket: len is 0!");
        return VOS_ERR;
    }

    /*  */
    ADS_DBG_UL_RMNET_RX_PKT_NUM(1);

    /*  */
    ADS_RECV_UL_PERIOD_PKT_NUM(pstImmZc->len);

    /* MODEMID */
    ucInstance = ADS_GET_MODEMID_FROM_EXRABID(ucExRabId);
    if (ucInstance >= ADS_INSTANCE_MAX_NUM)
    {
        ADS_DBG_UL_RMNET_MODEMID_ERR_NUM(1);
        return VOS_ERR;
    }

    /* RABID */
    ucRabId = ADS_GET_RABID_FROM_EXRABID(ucExRabId);
    if (!ADS_IS_RABID_VALID(ucRabId))
    {
        ADS_DBG_UL_RMNET_RABID_NUM(1);
        return VOS_ERR;
    }

    /* pstDataucRabId */
    if (VOS_OK != ADS_UL_InsertQueue(ucInstance, pstImmZc, ucRabId))
    {
        ADS_DBG_UL_RMNET_ENQUE_FAIL_NUM(1);
        return VOS_ERR;
    }

    ADS_DBG_UL_RMNET_ENQUE_SUCC_NUM(1);
    return VOS_OK;
}

/*****************************************************************************
     : ADS_UL_SendPacketEx
   : , ADS, 
             , ADS_DL_RegFilterDataCallback
             , ADS_DL_RegFilterDataCallback,
             
   : pstImmZc  --- IMM
             enIpType  --- IP
             ucExRabId --- RABID [5, 15]
   : 
     : VOS_OK/VOS_ERR
   :
   :
       :
  1.       : 201363
           : L47619
       : V3R3 Share-PDP

  2.       : 2016617
           : A00165503
       : DTS2016061504494: 0

*****************************************************************************/
VOS_UINT32 ADS_UL_SendPacketEx(
    IMM_ZC_STRU                        *pstImmZc,
    ADS_PKT_TYPE_ENUM_UINT8             enIpType,
    VOS_UINT8                           ucExRabId
)
{
    ADS_DL_RAB_INFO_STRU               *pstDlRabInfo;
    VOS_UINT8                           ucInstance;
    VOS_UINT8                           ucRabId;

    /*  */
    if (VOS_NULL_PTR == pstImmZc)
    {
        ADS_WARNING_LOG(ACPU_PID_ADS_UL, "ADS_UL_SendPacketEx: pstImmZc is null!");
        return VOS_ERR;
    }

    if (0 == IMM_ZcGetUsedLen(pstImmZc))
    {
        ADS_WARNING_LOG(ACPU_PID_ADS_UL, "ADS_UL_SendPacketEx: len is 0!");
        return VOS_ERR;
    }

    /*  */
    ADS_DBG_UL_RMNET_RX_PKT_NUM(1);

    /*  */
    ADS_RECV_UL_PERIOD_PKT_NUM(pstImmZc->len);

    /* MODEMID */
    ucInstance = ADS_GET_MODEMID_FROM_EXRABID(ucExRabId);
    if (ucInstance >= ADS_INSTANCE_MAX_NUM)
    {
        ADS_DBG_UL_RMNET_MODEMID_ERR_NUM(1);
        return VOS_ERR;
    }

    /* RABID */
    ucRabId = ADS_GET_RABID_FROM_EXRABID(ucExRabId);
    if (!ADS_IS_RABID_VALID(ucRabId))
    {
        ADS_DBG_UL_RMNET_RABID_NUM(1);
        return VOS_ERR;
    }

    /*  */
    pstDlRabInfo = ADS_DL_GET_RAB_INFO_PTR(ucInstance, ucRabId);
    if (VOS_NULL_PTR != pstDlRabInfo->pRcvDlFilterDataFunc)
    {
        /*  */
        ADS_FILTER_ProcUlPacket(pstImmZc, enIpType);
    }

    /* pstDataucRabId */
    if (VOS_OK != ADS_UL_InsertQueue(ucInstance, pstImmZc, ucRabId))
    {
        ADS_DBG_UL_RMNET_ENQUE_FAIL_NUM(1);
        return VOS_ERR;
    }

    ADS_DBG_UL_RMNET_ENQUE_SUCC_NUM(1);
    return VOS_OK;
}

/*****************************************************************************
     : ADS_UL_GetInstanceNextQueueNode
   : 
   : VOS_UINT8                           ucInstanceIndex,
   : VOS_UINT8                          *pucRabId
     : IMM_ZC_STRU                        *pstNode
   :
   :

       :
  1.       : 20111220
           : /l60609
       : 
  2.       : 20120221
           : f00179208
       : V7R1C50
  3.       : 20121124
           : l60609
       : DSDA Phase II:
*****************************************************************************/
IMM_ZC_STRU* ADS_UL_GetInstanceNextQueueNode(
    VOS_UINT8                           ucInstanceIndex,
    VOS_UINT8                          *pucRabId,
    VOS_UINT8                          *puc1XorHrpdUlIpfFlag
)
{
    VOS_UINT32                          i;
    VOS_UINT8                          *pucCurIndex;
    ADS_UL_CTX_STRU                    *pstAdsUlCtx;
    IMM_ZC_STRU                        *pstNode;

    pstAdsUlCtx = ADS_GetUlCtx(ucInstanceIndex);

    pucCurIndex = &pstAdsUlCtx->ucAdsUlCurIndex;

    pstNode     = VOS_NULL_PTR;

    /*  */
    for (i = 0; i < ADS_RAB_NUM_MAX; i++)
    {
        /* 
            */
        if (VOS_NULL_PTR == ADS_UL_GET_QUEUE_LINK_INFO(ucInstanceIndex, *pucCurIndex))
        {
            i += ADS_RAB_NUM_MAX - (*pucCurIndex + 1U);

            *pucCurIndex = 0;

            continue;
        }

        /*  */
        if (0 == ADS_UL_GET_QUEUE_LINK_INFO(ucInstanceIndex, *pucCurIndex)->qlen)
        {
            /*  */
            ADS_UL_CLR_RECORD_NUM_IN_WEIGHTED(ucInstanceIndex, *pucCurIndex);

            *pucCurIndex = (*pucCurIndex + 1) % ADS_RAB_NUM_MAX;

            continue;
        }

        /*  */
        /*  */
        if (ADS_UL_GET_RECORD_NUM_IN_WEIGHTED(ucInstanceIndex, *pucCurIndex) < ADS_UL_GET_QUEUE_PRI_WEIGHTED_NUM(ucInstanceIndex, *pucCurIndex))
        {
            /*  */
            pstNode = IMM_ZcDequeueHead(ADS_UL_GET_QUEUE_LINK_INFO(ucInstanceIndex, *pucCurIndex));

            /* RabId */
            *pucRabId = ADS_UL_GET_PRIO_QUEUE_INDEX(ucInstanceIndex, *pucCurIndex);

            /* 1XHRPD */
            *puc1XorHrpdUlIpfFlag = ADS_UL_GET_1X_OR_HRPD_UL_IPF_FLAG(ucInstanceIndex, *pucCurIndex);

            /*  1*/
            ADS_UL_SET_RECORD_NUM_IN_WEIGHTED(ucInstanceIndex, *pucCurIndex, 1);

            /*  */
            if (ADS_UL_GET_RECORD_NUM_IN_WEIGHTED(ucInstanceIndex, *pucCurIndex) == ADS_UL_GET_QUEUE_PRI_WEIGHTED_NUM(ucInstanceIndex, *pucCurIndex))
            {
                /*  */
                ADS_UL_CLR_RECORD_NUM_IN_WEIGHTED(ucInstanceIndex, *pucCurIndex);

                *pucCurIndex = (*pucCurIndex + 1) % ADS_RAB_NUM_MAX;
            }

            break;
        }
    }


    return pstNode;
}

/*****************************************************************************
     : ADS_UL_GetNextQueueNode
   : DSDA Phase II:
   : VOS_UINT8 *pucRabId
   : 
     : IMM_ZC_STRU*
   :
   :

       :
  1.       : 20121124
           : l60609
       : 

*****************************************************************************/
IMM_ZC_STRU* ADS_UL_GetNextQueueNode(
    VOS_UINT8                          *pucRabId,
    VOS_UINT8                          *pucInstanceIndex,
    VOS_UINT8                          *puc1XorHrpdUlIpfFlag
)
{
    ADS_CTX_STRU                       *pstAdsCtx = VOS_NULL_PTR;
    IMM_ZC_STRU                        *pstNode = VOS_NULL_PTR;
    VOS_UINT8                           i;
    VOS_UINT8                           ucCurInstanceIndex;

    pstAdsCtx = ADS_GetAllCtx();

    ucCurInstanceIndex = pstAdsCtx->ucAdsCurInstanceIndex;

    for (i = 0; i < ADS_INSTANCE_MAX_NUM; i++)
    {
        ucCurInstanceIndex = ucCurInstanceIndex % ADS_INSTANCE_MAX_NUM;

        pstNode = ADS_UL_GetInstanceNextQueueNode(ucCurInstanceIndex, pucRabId, puc1XorHrpdUlIpfFlag);

        if (VOS_NULL_PTR != pstNode)
        {
            break;
        }

        ucCurInstanceIndex++;
    }

    /* BDmodem id */
    *pucInstanceIndex = ucCurInstanceIndex;

    /*  */
    pstAdsCtx->ucAdsCurInstanceIndex = (ucCurInstanceIndex + 1) % ADS_INSTANCE_MAX_NUM;

    return pstNode;
}

/*****************************************************************************
     : ADS_UL_SaveIpfSrcMem
   : IPF BD
   : const ADS_IPF_BD_BUFF_STRU         *pstIpfUlBdBuff
             VOS_UINT32                          ulSaveNum
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20151006
           : A00165503
       : 

*****************************************************************************/
VOS_VOID ADS_UL_SaveIpfSrcMem(
    const ADS_IPF_BD_BUFF_STRU         *pstIpfUlBdBuff,
    VOS_UINT32                          ulSaveNum
)
{
    VOS_UINT32                          ulCnt;

    if (ulSaveNum > IPF_ULBD_DESC_SIZE)
    {
        return;
    }

    for (ulCnt = 0; ulCnt < ulSaveNum; ulCnt++)
    {
        IMM_ZcQueueTail(ADS_UL_IPF_SRCMEM_FREE_QUE(), pstIpfUlBdBuff[ulCnt].pstPkt);
        ADS_DBG_UL_BDQ_SAVE_SRC_MEM_NUM(1);
    }

    return;
}

/*****************************************************************************
     : ADS_UL_FreeIpfSrcMem
   : 
   : VOS_VOID
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 2012830
           : l60609
       : 

*****************************************************************************/
VOS_VOID ADS_UL_FreeIpfSrcMem(VOS_VOID)
{
    IMM_ZC_STRU                        *pstImmZc = VOS_NULL_PTR;
    VOS_UINT32                          ulIdleBD;
    VOS_UINT32                          ulBusyBD;
    VOS_UINT32                          ulCanFree;
    VOS_UINT32                          ulQueCnt;
    VOS_UINT32                          ulCnt;

    /* que is empty */
    ulQueCnt = IMM_ZcQueueLen(ADS_UL_IPF_SRCMEM_FREE_QUE());
    if (0 == ulQueCnt)
    {
        return;
    }

    /* get busy bd num */
    ulIdleBD = mdrv_ipf_get_uldesc_num();
    ulBusyBD = IPF_ULBD_DESC_SIZE - ulIdleBD;
    if (ulQueCnt >= ulBusyBD)
    {
        ulCanFree = ulQueCnt - ulBusyBD;
    }
    else
    {
        ADS_ERROR_LOG3(ACPU_PID_ADS_UL, "ADS_UL_FreeIpfUlSrcMem: Buff Num Less IPF Busy BD Num. ulQueCnt, ulBusyBD, ulIdleBD", ulQueCnt, ulBusyBD, ulIdleBD);
        ADS_DBG_UL_BDQ_FREE_SRC_MEM_ERR(1);
        return;
    }

    /* free src mem */
    for (ulCnt = 0; ulCnt < ulCanFree; ulCnt++)
    {
        pstImmZc = IMM_ZcDequeueHead(ADS_UL_IPF_SRCMEM_FREE_QUE());
        if (VOS_NULL_PTR == pstImmZc)
        {
            break;
        }

        /* CACHE,  */
        ADS_IPF_UL_MEM_UNMAP(pstImmZc, IMM_ZcGetUsedLen(pstImmZc));
        IMM_ZcFreeAny(pstImmZc);
        ADS_DBG_UL_BDQ_FREE_SRC_MEM_NUM(1);
    }

    return;
}

/*****************************************************************************
     : ADS_UL_ClearIpfSrcMem
   : IPF Src Mem
   : VOS_VOID
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 2012831
           : l60609
       : 

*****************************************************************************/
VOS_VOID ADS_UL_ClearIpfSrcMem(VOS_VOID)
{
    IMM_ZC_STRU                      *pstImmZc = VOS_NULL_PTR;
    VOS_UINT32                        ulQueCnt;
    VOS_UINT32                        ulCnt;
    VOS_UINT32                        ulIpfUlBdNum;
    VOS_UINT8                         i;

    ulQueCnt = IMM_ZcQueueLen(ADS_UL_IPF_SRCMEM_FREE_QUE());
    if (0 == ulQueCnt)
    {
        return;
    }

    /* PDPBD */
    for (i = 0; i < ADS_INSTANCE_MAX_NUM; i++)
    {
        if (VOS_FALSE == ADS_UL_CheckAllQueueEmpty(i))
        {
            return;
        }
    }

    ulIpfUlBdNum = mdrv_ipf_get_uldesc_num();
    /* BD63 */
    if (IPF_ULBD_DESC_SIZE != ulIpfUlBdNum)
    {
        return;
    }

    /*free src mem*/
    for (ulCnt = 0; ulCnt < ulQueCnt; ulCnt++)
    {
        pstImmZc = IMM_ZcDequeueHead(ADS_UL_IPF_SRCMEM_FREE_QUE());
        if (VOS_NULL_PTR == pstImmZc)
        {
            break;
        }

        /* CACHE,  */
        ADS_IPF_UL_MEM_UNMAP(pstImmZc, pstImmZc->len);
        IMM_ZcFreeAny(pstImmZc);
        ADS_DBG_UL_BDQ_FREE_SRC_MEM_NUM(1);
    }

    return;
}

/*****************************************************************************
     : ADS_UL_GetBdFcHead
   : IPF
   : VOS_UINT8                           ucInstanceIndex
             VOS_UINT8                           uc1XorHrpdUlIpfFlag
   : 
     : VOS_UINT8
   :
   :

       :
  1.       : 20151219
           : Y00213812
       : 

*****************************************************************************/
VOS_UINT8 ADS_UL_GetBdFcHead(
    VOS_UINT8                           ucInstanceIndex,
    VOS_UINT8                           uc1XorHrpdUlIpfFlag
)
{
    VOS_UINT8                           ucIpfFlterCh;
    if (VOS_TRUE == uc1XorHrpdUlIpfFlag)
    {
        ucIpfFlterCh = ADS_UL_IPF_1XHRPD;
    }
    else
    {
        ucIpfFlterCh = ucInstanceIndex;
    }

    return ucIpfFlterCh;
}

/*****************************************************************************
     : ADS_UL_CalcBuffTime
   : 
   : ulBeginSlice --- 
             ulEndSlice   --- 
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 20151006
           : A00165503
       : 
  2.       : 20160826
           : l00373346
       : 

*****************************************************************************/
VOS_UINT32 ADS_UL_CalcBuffTime(VOS_UINT32 ulBeginSlice, VOS_UINT32 ulEndSlice)
{
    if (ulEndSlice > ulBeginSlice)
    {
        return (ulEndSlice - ulBeginSlice);
    }
    else
    {
        return (VOS_NULL_DWORD - ulBeginSlice + ulEndSlice + 1);
    }
}

/*****************************************************************************
     : ADS_UL_ConfigBD
   : ADSBDIPF
   : VOS_UINT32 ulBdNum
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 2011127
           : /l60609
       : 

  2.       : 2015922
           : A00165503
       : DTS2015081008249: ADS, 

*****************************************************************************/
VOS_VOID ADS_UL_ConfigBD(VOS_UINT32 ulBdNum)
{
    IPF_CONFIG_ULPARAM_S               *pstUlCfgParam = VOS_NULL_PTR;
    ADS_IPF_BD_BUFF_STRU               *pstUlBdBuff   = VOS_NULL_PTR;
    IMM_ZC_STRU                        *pstImmZc      = VOS_NULL_PTR;
    VOS_UINT32                          ulBeginSlice;
    VOS_UINT32                          ulEndSlice;
    VOS_UINT32                          ulTmp;
    VOS_UINT32                          ulCnt;
    VOS_INT32                           lRslt;
    VOS_UINT8                           ucInstance;
    VOS_UINT8                           ucRabId;
    VOS_UINT8                           uc1XorHrpdUlIpfFlag;

    ulEndSlice = VOS_GetSlice();

    for (ulCnt = 0; ulCnt < ulBdNum; ulCnt++)
    {
        pstImmZc = ADS_UL_GetNextQueueNode(&ucRabId, &ucInstance, &uc1XorHrpdUlIpfFlag);
        if (VOS_NULL_PTR == pstImmZc)
        {
            break;
        }

        pstUlBdBuff = ADS_UL_GET_BD_BUFF_PTR(ulCnt);
        pstUlBdBuff->pstPkt = pstImmZc;

        ulBeginSlice  = ADS_UL_GET_SLICE_FROM_IMM(pstImmZc);
        pstUlCfgParam = ADS_UL_GET_BD_CFG_PARA_PTR(ulCnt);
        /* Attribute: modem00modem11 */
#if (LINUX_VERSION_CODE < KERNEL_VERSION(4, 9, 0))
        pstUlCfgParam->u32Data = (VOS_UINT32)virt_to_phys((VOS_VOID *)pstImmZc->data);
        pstUlCfgParam->u16Attribute = (VOS_UINT16)ADS_UL_BUILD_BD_ATTRIBUTE(VOS_FALSE, IPF_MODE_FILTERANDTRANS, ADS_UL_GetBdFcHead(ucInstance, uc1XorHrpdUlIpfFlag));
        pstUlCfgParam->u16Len       = (VOS_UINT16)pstImmZc->len;
#endif
        pstUlCfgParam->u16UsrField1 = (VOS_UINT16)ADS_UL_BUILD_BD_USER_FIELD_1(ucInstance, ucRabId);
        pstUlCfgParam->u32UsrField3 = (VOS_UINT32)ADS_UL_CalcBuffTime(ulBeginSlice, ulEndSlice);
        pstUlCfgParam->u32UsrField2 = 0;
        if( VOS_NULL_PTR != pstImmZc->sk )
        {
             pstUlCfgParam->u32UsrField2 |= pstImmZc->sk->acc_state;
        }
        /* Attribute: modem00modem11 */
        ADS_MNTN_RecULIpPktInfo(pstImmZc,
                                pstUlCfgParam->u16UsrField1,
                                pstUlCfgParam->u32UsrField2,
                                pstUlCfgParam->u32UsrField3
                               );

        /* CAHCE */
        ADS_IPF_UL_MEM_MAP(pstImmZc, pstImmZc->len);

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 9, 0))
        pstUlCfgParam->u32Data      = (VOS_UINT32)ADS_IPF_GetMemDma(pstImmZc);
        pstUlCfgParam->u16Attribute = (VOS_UINT16)ADS_UL_BUILD_BD_ATTRIBUTE(VOS_FALSE, IPF_MODE_FILTERANDTRANS, ADS_UL_GetBdFcHead(ucInstance, uc1XorHrpdUlIpfFlag));
        pstUlCfgParam->u16Len       = (VOS_UINT16)pstImmZc->len;
#endif
    }

    /* 0 */
    if (0 == ulCnt)
    {
        return;
    }

    /* BD */
    pstUlCfgParam = ADS_UL_GET_BD_CFG_PARA_PTR(ulCnt - 1);
    ADS_UL_SET_BD_ATTR_INT_FLAG(pstUlCfgParam->u16Attribute);
    /* IPFBD */
    lRslt = mdrv_ipf_config_ulbd(ulCnt, ADS_UL_GET_BD_CFG_PARA_PTR(0));
    if (IPF_SUCCESS != lRslt)
    {
        /* IPF,  */
        ulTmp = ulCnt;
        for (ulCnt = 0; ulCnt < ulTmp; ulCnt++)
        {
            pstUlBdBuff = ADS_UL_GET_BD_BUFF_PTR(ulCnt);
            IMM_ZcFreeAny(pstUlBdBuff->pstPkt);
            ADS_DBG_UL_BDQ_CFG_BD_FAIL_NUM(1);
        }

        ADS_DBG_UL_BDQ_CFG_IPF_FAIL_NUM(1);
        return;
    }

    /* BD */
    ADS_UL_SaveIpfSrcMem(ADS_UL_GET_BD_BUFF_PTR(0), ulCnt);
    ADS_DBG_UL_BDQ_CFG_BD_SUCC_NUM(ulCnt);
    ADS_DBG_UL_BDQ_CFG_IPF_SUCC_NUM(1);

    ADS_MNTN_ReportULPktInfo();

    ADS_UL_EnableRxWakeLockTimeout(ADS_UL_RX_WAKE_LOCK_TMR_LEN);
    return;
}

/*****************************************************************************
     : ADS_UL_ProcLinkData
   : IPF
   : VOS_VOID
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 2011127
           : /l60609
       : 

  2.       : 2012330
           : l60609
       : DTS2012031206512BD

  3.       : 2012412
           : A00165503
       : DTS2012020708222: ADS

  4.       : 2012427
           : l60609
       : DTS2012041802250: ADS10ms

  5.       : 2012831
           : l60609
       : APBD

*****************************************************************************/
VOS_VOID ADS_UL_ProcLinkData(VOS_VOID)
{
    VOS_UINT32                          ulAllUlQueueDataNum;
    VOS_UINT32                          ulIpfUlBdNum;
    VOS_UINT32                          ulSndBdNum;

    /*  */
    for (;;)
    {
        /*  */
        if (VOS_TRUE == ADS_GetUlResetFlag())
        {
            printk(KERN_ERR "\n ADS_UL_ProcLinkData in ccore reset \n");
            return;
        }


        /* BD */
        ulIpfUlBdNum = mdrv_ipf_get_uldesc_num();
        if (0 == ulIpfUlBdNum)
        {
            ADS_DBG_UL_BDQ_CFG_IPF_HAVE_NO_BD_NUM(1);

            /*  */
            ADS_UL_SET_SENDING_FLAG(VOS_FALSE);

            /*  */
            ADS_StartTimer(TI_ADS_UL_SEND, ADS_UL_GET_PROTECT_TIMER_LEN());
            break;
        }


        /*  */
        ADS_UL_SET_SENDING_FLAG(VOS_TRUE);

        /*  */
        ulAllUlQueueDataNum = ADS_UL_GetAllQueueDataNum();

        /* BD */
        ulSndBdNum = PS_MIN(ulIpfUlBdNum, ulAllUlQueueDataNum);

        /*  */
        ADS_UL_FreeIpfSrcMem();

        /* BDIPF */
        ADS_UL_ConfigBD(ulSndBdNum);

        /*  */
        ulAllUlQueueDataNum = ADS_UL_GetAllQueueDataNum();

        /*  */
        if (0 == ulAllUlQueueDataNum)
        {
            /*  */
            ADS_UL_SET_SENDING_FLAG(VOS_FALSE);
            break;
        }
        /*  */
        else if (ulAllUlQueueDataNum <= ADS_UL_SEND_DATA_NUM_THREDHOLD)
        {
            ADS_StartTimer(TI_ADS_UL_SEND, ADS_UL_GET_PROTECT_TIMER_LEN());

            /*  */
            ADS_UL_SET_SENDING_FLAG(VOS_FALSE);
            break;
        }
        else
        {
            continue;
        }
    }

    return;
}

/*****************************************************************************
     : ADS_UL_ProcPdpStatusInd
   : PDP
   : MsgBlock *pMsg
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 201417
           : l60609
       : 

*****************************************************************************/
VOS_UINT32 ADS_UL_ProcPdpStatusInd(
    ADS_PDP_STATUS_IND_STRU            *pstStatusInd
)
{
    VOS_UINT8                           ucInstanceIndex;
    ADS_CDS_IPF_PKT_TYPE_ENUM_UINT8     enPktType;
    ADS_QCI_TYPE_ENUM_UINT8             enPrio;

    enPktType                           = ADS_CDS_IPF_PKT_TYPE_IP;

    ucInstanceIndex                     = (VOS_UINT8)pstStatusInd->enModemId;

    enPrio                              = pstStatusInd->enQciType;

    /* RabId */
    if (!ADS_IS_RABID_VALID(pstStatusInd->ucRabId))
    {
        ADS_WARNING_LOG1(ACPU_PID_ADS_UL, "ADS_UL_ProcPdpStatusInd: ucRabId is ", pstStatusInd->ucRabId);
        return VOS_ERR;
    }

    /* PDPQCIPDP */
    if (VOS_FALSE == g_stAdsCtx.astAdsSpecCtx[ucInstanceIndex].stAdsUlCtx.stQueuePriNv.ulStatus)
    {
        enPrio = ADS_QCI_TYPE_QCI9_NONGBR;
    }

    if (ADS_PDP_PPP == pstStatusInd->enPdpType)
    {
        enPktType = ADS_CDS_IPF_PKT_TYPE_PPP;
    }

    /* PDP */
    switch(pstStatusInd->enPdpStatus)
    {
        /* PDP */
        case ADS_PDP_STATUS_ACT:

            /*  */
            ADS_UL_CreateQueue(ucInstanceIndex, pstStatusInd->ucRabId, enPrio, enPktType, pstStatusInd->uc1XorHrpdUlIpfFlag);

            /*  */
            ADS_UL_StartDsFlowStats(ucInstanceIndex, pstStatusInd->ucRabId);

            break;

        /* PDP */
        case ADS_PDP_STATUS_MODIFY:

            /*  */
            ADS_UL_UpdateQueueInPdpModified(ucInstanceIndex, enPrio, pstStatusInd->ucRabId);

            break;

        /* PDP */
        case ADS_PDP_STATUS_DEACT:

            /*  */
            ADS_UL_DestroyQueue(ucInstanceIndex, pstStatusInd->ucRabId);

            /* PDP */
            ADS_UL_ClearIpfSrcMem();

            /*  */
            ADS_UL_StopDsFlowStats(ucInstanceIndex, pstStatusInd->ucRabId);

            break;

        default:
            break;
    }

    return VOS_OK;
}

/*****************************************************************************
     : ADS_UL_RcvAtPdpStatusInd
   : ID_APS_ADS_PDP_STATUS_IND
   : MsgBlock *pMsg
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 2011126
           : /l60609
       : 
  2.       : 20120220
           : f00179208
       : V7R1C50PDP
  3.       : 2012831
           : l60609
       : AP
  4.       : 20121124
           : l60609
       : DSDA Phase II:
  5.       : 20130522
           : f00179208
       : V3R3 PPP PROJECT

  6.       : 2013922
           : A00165503
       : DTS2013092200927: 
*****************************************************************************/
VOS_UINT32 ADS_UL_RcvTafPdpStatusInd(MsgBlock *pMsg)
{
    ADS_PDP_STATUS_IND_STRU            *pstPdpStatusInd;
    VOS_UINT32                          ulRslt;

    pstPdpStatusInd = (ADS_PDP_STATUS_IND_STRU *)pMsg;

    ulRslt = ADS_UL_ProcPdpStatusInd(pstPdpStatusInd);

    return ulRslt;
}

/*****************************************************************************
     : ADS_UL_RcvCdsIpPacketMsg
   : ID_CDS_ADS_IP_PACKET_IND
   : MsgBlock *pMsg
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 2011127
           : /l60609
       : 

  2.       : 2012831
           : l60609
       : APIMM

  3.       : 20121221
           : l60609
       : DSDA Phase II
*****************************************************************************/
VOS_UINT32 ADS_UL_RcvCdsIpPacketMsg(MsgBlock *pMsg)
{
    VOS_UINT32                          ulResult;
    ADS_NDIS_DATA_IND_STRU             *pstAdsNdisDataInd;
    IMM_ZC_STRU                        *pstZcData;
    CDS_ADS_DATA_IND_STRU              *pstDataInd;
    VOS_CHAR                           *pstZcPutData;

    pstDataInd = (CDS_ADS_DATA_IND_STRU *)pMsg;

    /*   */
    pstAdsNdisDataInd = (ADS_NDIS_DATA_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                             ACPU_PID_ADS_UL,
                                             sizeof(ADS_NDIS_DATA_IND_STRU));

    if (VOS_NULL_PTR == pstAdsNdisDataInd)
    {
        return VOS_ERR;
    }

    TAF_MEM_SET_S((VOS_INT8 *)pstAdsNdisDataInd + VOS_MSG_HEAD_LENGTH,
               (VOS_SIZE_T)(sizeof(ADS_NDIS_DATA_IND_STRU) - VOS_MSG_HEAD_LENGTH),
               0x00,
               (VOS_SIZE_T)(sizeof(ADS_NDIS_DATA_IND_STRU) - VOS_MSG_HEAD_LENGTH));

    /*  */
    pstAdsNdisDataInd->ulReceiverPid  = PS_PID_APP_NDIS;
    pstAdsNdisDataInd->enMsgId        = ID_ADS_NDIS_DATA_IND;
    pstAdsNdisDataInd->enModemId      = pstDataInd->enModemId;
    pstAdsNdisDataInd->ucRabId        = pstDataInd->ucRabId;
    pstAdsNdisDataInd->enIpPacketType = pstDataInd->enIpPacketType;

    pstZcData = (IMM_ZC_STRU *)IMM_ZcStaticAlloc((VOS_UINT32)pstDataInd->usLen);

    if (VOS_NULL_PTR == pstZcData)
    {
        PS_MEM_FREE(ACPU_PID_ADS_UL, pstAdsNdisDataInd);

        return VOS_ERR;
    }

    /**/
    pstZcPutData = (VOS_CHAR *)IMM_ZcPut(pstZcData, pstDataInd->usLen);

    TAF_MEM_CPY_S(pstZcPutData, pstDataInd->usLen, pstDataInd->aucData, pstDataInd->usLen);

    pstAdsNdisDataInd->pstSkBuff = pstZcData;

    /* VOS */
    ulResult = PS_SEND_MSG(ACPU_PID_ADS_UL, pstAdsNdisDataInd);

    if(VOS_OK != ulResult)
    {
        ADS_ERROR_LOG(ACPU_PID_ADS_UL, "ADS_UL_RcvCdsIpPacketMsg: Send Msg Fail!");

        IMM_ZcFreeAny(pstZcData);

        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
     : ADS_UL_RcvCcpuResetStartInd
   : ADS_ULADS_ULID_CCPU_RESET_START_ADS_UL_TO_ADS_UL_NOTIFY
   : pMsg:
   : 
     : VOS_UINT32:VOS_OK
   :
   :

      :
 1.       : 20130415
          : f00179208
      : 

 2.       : 20130618
          : l00198894
      : V3R3 Share-PDP

  3.       : 201591
           : A00165503
       : DTS2015082300106: , AC
*****************************************************************************/
VOS_UINT32 ADS_UL_RcvCcpuResetStartInd(
    MsgBlock                           *pstMsg
)
{
    VOS_UINT8                           ucInsIndex;
    VOS_UINT8                           ucRabIndex;
    VOS_UINT8                           ucTiIndex;
    ADS_CTX_STRU                       *pstAdsCtx = VOS_NULL_PTR;

    ADS_TRACE_HIGH("enter.\n");

    pstAdsCtx = ADS_GetAllCtx();

    /*  */
    for (ucInsIndex = 0; ucInsIndex < ADS_INSTANCE_MAX_NUM; ucInsIndex++)
    {
        for (ucRabIndex = 0; ucRabIndex < ADS_RAB_ID_MAX + 1; ucRabIndex++)
        {
            ADS_UL_DestroyQueue(ucInsIndex, ucRabIndex);
        }
    }

    /*  */
    ADS_UL_ClearIpfSrcMem();

    /*  */
    for (ucTiIndex = 0; ucTiIndex < ADS_MAX_TIMER_NUM; ucTiIndex++)
    {
        ADS_StopTimer(ACPU_PID_ADS_UL, ucTiIndex, ADS_TIMER_STOP_CAUSE_USER);
    }

    /*  */
    ADS_ResetUlCtx();

    /* IPF */
    ADS_ResetIpfCtx();

    /*  */
    pstAdsCtx->ucAdsCurInstanceIndex = ADS_INSTANCE_INDEX_0;

    /* ADS Filter */
    ADS_FILTER_Reset();

    /* API */
    VOS_SmV(ADS_GetULResetSem());

    ADS_TRACE_HIGH("leave.\n");
    return VOS_OK;
}

/*****************************************************************************
     : ADS_UL_RcvTiSendExpired
   : TI_ADS_UL_SEND
   : VOS_UINT32                          ulParam,
             VOS_UINT32                          ulTimerName
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20160125
           : w00316404
       : 

*****************************************************************************/
VOS_VOID ADS_UL_RcvTiSendExpired(
    VOS_UINT32                          ulParam,
    VOS_UINT32                          ulTimerName
)
{
    ADS_UL_SndEvent(ADS_UL_EVENT_DATA_PROC);
    ADS_DBG_UL_10MS_TMR_TRIG_EVENT(1);
    return;
}

/*****************************************************************************
     : ADS_UL_RcvTiDsFlowStatsExpired
   : ADS
   : ulTimerName
             ulParam
   : 
     : VOS_VOID
   :
   :

      :
 1.       : 2012110
          : l60609
      : 

  2.       : 2012412
           : A00165503
       : DTS2012020708222: ADS

  3.       : 20121124
           : l60609
       : DSDA Phase II:

  4.       : 2013922
           : A00165503
       : DTS2013092200927: 

  5.       : 2015521
           : l00198894
       : TSTS
*****************************************************************************/
VOS_VOID ADS_UL_RcvTiDsFlowStatsExpired(
    VOS_UINT32                          ulTimerName,
    VOS_UINT32                          ulParam
)
{
    VOS_UINT32                          ulTaBytes;
    VOS_UINT32                          ulRate;

    /* ,  */
    if (VOS_FALSE == ADS_UL_IsAnyQueueExist())
    {
        ADS_NORMAL_LOG(ACPU_PID_ADS_DL, "ADS_UL_RcvTiDsFlowStatsExpired: no queue is exist!");
        return;
    }

    /* 1 */
    ulTaBytes = ADS_GET_DL_PERIOD_PKT_NUM();

    /* 1,:byte/s */
    ulRate = ulTaBytes;
    ADS_SET_CURRENT_DL_RATE(ulRate);

    /* 1 */
    ulTaBytes = ADS_GET_UL_PERIOD_PKT_NUM();

    /* 1,:byte/s */
    ulRate = ulTaBytes;
    ADS_SET_CURRENT_UL_RATE(ulRate);

    /* Byte */
    ADS_CLEAR_UL_PERIOD_PKT_NUM();
    ADS_CLEAR_DL_PERIOD_PKT_NUM();

    /* */
    ADS_StartTimer(TI_ADS_DSFLOW_STATS, TI_ADS_DSFLOW_STATS_LEN);

    return ;
}

/*****************************************************************************
     : ADS_UL_RcvTiStatExpired
   : 
   : VOS_UINT32    ulParam,
             VOS_UINT32    ulTimerName
   : 
     : VOS_VOID
   :
   :

      :
 1.       : 20140603
          : f00179208
      : 
*****************************************************************************/
VOS_VOID ADS_UL_RcvTiDataStatExpired(
    VOS_UINT32                          ulTimerName,
    VOS_UINT32                          ulParam
)
{
    VOS_UINT32                          ulStatPktNum;

    ulStatPktNum = ADS_UL_GET_STAT_PKT_NUM();

    /*  */
    if (ulStatPktNum < ADS_UL_GET_WATER_LEVEL_ONE())
    {
        ADS_UL_SET_SEND_DATA_NUM_THREDHOLD(ADS_UL_DATA_THRESHOLD_ONE);
        ADS_DBG_UL_WM_LEVEL_1_HIT_NUM(1);
    }
    else if (ulStatPktNum <  ADS_UL_GET_WATER_LEVEL_TWO())
    {
        ADS_UL_SET_SEND_DATA_NUM_THREDHOLD(ADS_UL_DATA_THRESHOLD_TWO);
        ADS_DBG_UL_WM_LEVEL_2_HIT_NUM(1);
    }
    else if (ulStatPktNum <  ADS_UL_GET_WATER_LEVEL_THREE())
    {
        ADS_UL_SET_SEND_DATA_NUM_THREDHOLD(ADS_UL_DATA_THRESHOLD_THREE);
        ADS_DBG_UL_WM_LEVEL_3_HIT_NUM(1);
    }
    else
    {
        ADS_UL_SET_SEND_DATA_NUM_THREDHOLD(ADS_UL_DATA_THRESHOLD_FOUR);
        ADS_DBG_UL_WM_LEVEL_4_HIT_NUM(1);
    }

    /* 100ms */
    if (0 != ulStatPktNum)
    {
        /*  */
        ADS_StartTimer(TI_ADS_UL_DATA_STAT, ADS_UL_GET_STAT_TIMER_LEN());
    }

    /*  */
    ADS_UL_CLR_STAT_PKT_NUM();

    return;
}

/*****************************************************************************
     : ADS_UL_RcvTafMsg
   : AT
   : MsgBlock *pMsg
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 2011126
           : /l60609
       : 
  2.       : 20140214
           : m00217266
       : pdp status ind taf aps
*****************************************************************************/
VOS_UINT32 ADS_UL_RcvTafMsg(MsgBlock *pMsg)
{
    MSG_HEADER_STRU                    *pstMsg;

    pstMsg = (MSG_HEADER_STRU*)pMsg;


    switch(pstMsg->ulMsgName)
    {
        case ID_APS_ADS_PDP_STATUS_IND:
            ADS_UL_RcvTafPdpStatusInd(pMsg);
            break;

        default:
            break;
    }

    return VOS_OK;
}

/*****************************************************************************
     : ADS_UL_RcvCdsMsg
   : CDS
   : MsgBlock *pMsg
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 2011126
           : /l60609
       : 

  2.       : 2015616
           : l00198894
       : TSTS
*****************************************************************************/
VOS_UINT32 ADS_UL_RcvCdsMsg(MsgBlock *pMsg)
{
    MSG_HEADER_STRU                    *pstMsg;

    pstMsg = (MSG_HEADER_STRU*)pMsg;

    switch(pstMsg->ulMsgName)
    {
        case ID_CDS_ADS_IP_PACKET_IND:
            ADS_UL_RcvCdsIpPacketMsg(pMsg);
            break;

        default:
            break;
    }

    return VOS_OK;
}

/*****************************************************************************
     : ADS_UL_RcvTimerMsg
   : 
   : MsgBlock *pMsg
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 2011127
           : /l60609
       : 

  2.       : 2013922
           : A00165503
       : DTS2013092200927: 

  3.       : 20140603
           : f00179208
       : CCPU LOAD

  4.       : 2015521
           : l00198894
       : TSTS

  5.       : 2015922
           : A00165503
       : DTS2015081008249: ADS, 

*****************************************************************************/
VOS_UINT32 ADS_UL_RcvTimerMsg(MsgBlock *pMsg)
{
    REL_TIMER_MSG                      *pstTimerMsg;

    pstTimerMsg = (REL_TIMER_MSG *)pMsg;

    /*  */
    ADS_StopTimer(ACPU_PID_ADS_UL, pstTimerMsg->ulName, ADS_TIMER_STOP_CAUSE_TIMEOUT);

    switch (pstTimerMsg->ulName)
    {
        case TI_ADS_DSFLOW_STATS:
            ADS_UL_RcvTiDsFlowStatsExpired(pstTimerMsg->ulName, pstTimerMsg->ulPara);
            ADS_MNTN_ReportAllStatsInfo();
            break;

        case TI_ADS_UL_DATA_STAT:
            ADS_UL_RcvTiDataStatExpired(pstTimerMsg->ulName, pstTimerMsg->ulPara);
            break;

        default:
            break;
    }

    return VOS_OK;
}

/*****************************************************************************
     : ADS_UL_RcvAdsUlMsg
   : ADS UL
   : MsgBlock *pMsg
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 20130415
           : f00179208
       : 

*****************************************************************************/
VOS_UINT32 ADS_UL_RcvAdsUlMsg(MsgBlock *pMsg)
{
    MSG_HEADER_STRU                    *pstMsg;

    pstMsg = (MSG_HEADER_STRU*)pMsg;

    switch(pstMsg->ulMsgName)
    {
        case ID_ADS_CCPU_RESET_START_IND:
            ADS_UL_RcvCcpuResetStartInd(pMsg);
            break;

        case ID_ADS_CCPU_RESET_END_IND:
            /* do nothing */
            ADS_NORMAL_LOG(ACPU_PID_ADS_UL, "ADS_DL_RcvAdsDlMsg: rcv ID_CCPU_ADS_UL_RESET_END_IND");
            break;

        default:
            ADS_NORMAL_LOG1(ACPU_PID_ADS_UL, "ADS_UL_RcvAdsUlMsg: rcv error msg id %d\r\n", pstMsg->ulMsgName);
            break;
    }

    return VOS_OK;
}

/*****************************************************************************
     : ADS_UL_ProcMsg
   : ADS
   : MsgBlock* pMsg
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 2011126
           : /l60609
       : 
  2.       : 2012412
           : A00165503
       : DTS2012020708222: ADS
  3.       : 2013415
           : f00179208
       : C
  4.       : 20140214
           : m00217266
       : pdp status ind taf aps
  5.       : 2015521
           : l00198894
       : TSTS
*****************************************************************************/
VOS_VOID ADS_UL_ProcMsg(MsgBlock* pMsg)
{
    if (VOS_NULL_PTR == pMsg)
    {
        return;
    }

    /*  */
    switch ( pMsg->ulSenderPid )
    {
        /* Timer */
        case VOS_PID_TIMER:
            ADS_UL_RcvTimerMsg(pMsg);
            return;

        /* TAF */
        case I0_WUEPS_PID_TAF:
        case I1_WUEPS_PID_TAF:
        case I2_WUEPS_PID_TAF:
            ADS_UL_RcvTafMsg(pMsg);
            return;

        /* CDS */
        case UEPS_PID_CDS:
            ADS_UL_RcvCdsMsg(pMsg);
            return;

        /* ADS UL */
        case ACPU_PID_ADS_UL:
            ADS_UL_RcvAdsUlMsg(pMsg);
            return;

        default:
            return;
    }
}

