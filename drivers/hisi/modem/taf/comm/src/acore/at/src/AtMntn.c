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
#include "AtMntn.h"
#include "AtInputProc.h"
#include "AtCtx.h"
#include "AtDataProc.h"



/*****************************************************************************
    .C
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_AT_MNTN_C

/*****************************************************************************
  2 
*****************************************************************************/


/*****************************************************************************
  3 
*****************************************************************************/


/*****************************************************************************
  4 
*****************************************************************************/
AT_DEBUG_INFO_STRU                      g_stAtDebugInfo = {VOS_FALSE};

AT_MNTN_STATS_STRU                      g_stAtStatsInfo;

AT_MNTN_MSG_RECORD_INFO_STRU            g_stAtMsgRecordInfo;

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
  8 UNION
*****************************************************************************/


/*****************************************************************************
  9 OTHERS
*****************************************************************************/

/*****************************************************************************
  10 
*****************************************************************************/
/*****************************************************************************
    : AT_InitMntnCtx
  : AT
  : 
  : 
    : 
  :
  :

      :
 1.       : 20140913
          : g00261581
      : 
*****************************************************************************/
VOS_VOID AT_InitMntnCtx(VOS_VOID)
{
    TAF_MEM_SET_S(&g_stAtMsgRecordInfo, sizeof(g_stAtMsgRecordInfo), 0x00, sizeof(g_stAtMsgRecordInfo));
}

/*****************************************************************************
    : AT_SetPcuiCtrlConcurrentFlag
  : PCUIPCUI2CTRL
  : VOS_UINT8    ucFlag
  : 
    : 
  :
  :

      :
 1.       : 2013418
          : z00220246
      : 
*****************************************************************************/
VOS_VOID AT_SetPcuiCtrlConcurrentFlag(VOS_UINT8 ucFlag)
{
    g_stAtDebugInfo.ucPcuiCtrlConcurrentFlg = ucFlag;
}

/*****************************************************************************
    : AT_GetPcuiCtrlConcurrentFlag
  : PCUICTRL
  : 
  : 
    : VOS_UINT8
  :
  :

      :
 1.       : 2013418
          : z00220246
      : 
*****************************************************************************/
VOS_UINT8 AT_GetPcuiCtrlConcurrentFlag(VOS_VOID)
{
    return g_stAtDebugInfo.ucPcuiCtrlConcurrentFlg;
}

/*****************************************************************************
     : AT_SetPcuiPsCallFlag
   : PCUInidsdup
   : VOS_UINT8         ucFlag
             VOS_UINT8         ucIndex
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 2013427
           : l60609
       : 
*****************************************************************************/
VOS_VOID AT_SetPcuiPsCallFlag(
    VOS_UINT8                           ucFlag,
    VOS_UINT8                           ucIndex
)
{
    g_stAtDebugInfo.ucPcuiPsCallFlg     = ucFlag;
    g_stAtDebugInfo.ucPcuiUserId        = AT_CLIENT_TAB_APP_INDEX;
}

/*****************************************************************************
     : AT_GetPcuiPsCallFlag
   : PCUInidsdup
   : 
   : 
     : VOS_UINT8
   :
   :

       :
  1.       : 2013427
           : l60609
       : 
*****************************************************************************/
VOS_UINT8 AT_GetPcuiPsCallFlag(VOS_VOID)
{
    return g_stAtDebugInfo.ucPcuiPsCallFlg;
}

/*****************************************************************************
     : AT_GetPcuiUsertId
   : PCUINDISDUP
   : VOS_VOID
   : 
     : VOS_UINT8
   :
   :

       :
  1.       : 201357
           : l60609
       : 
*****************************************************************************/
VOS_UINT8 AT_GetPcuiUsertId(VOS_VOID)
{
    return g_stAtDebugInfo.ucPcuiUserId;
}

/*****************************************************************************
     : AT_SetCtrlPsCallFlag
   : Ctrlnidsdup
   : VOS_UINT8            ucFlag
             VOS_UINT8            ucIndex
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 201378
           : l60609
       : 
*****************************************************************************/
VOS_VOID AT_SetCtrlPsCallFlag(
    VOS_UINT8                           ucFlag,
    VOS_UINT8                           ucIndex
)
{
    g_stAtDebugInfo.ucCtrlPsCallFlg     = ucFlag;
    g_stAtDebugInfo.ucCtrlUserId        = AT_CLIENT_TAB_APP5_INDEX;
}

/*****************************************************************************
     : AT_GetCtrlPsCallFlag
   : CTRLnidsdup
   : 
   : 
     : VOS_UINT8
   :
   :

       :
  1.       : 201378
           : l60609
       : 
*****************************************************************************/
VOS_UINT8 AT_GetCtrlPsCallFlag(VOS_VOID)
{
    return g_stAtDebugInfo.ucCtrlPsCallFlg;
}

/*****************************************************************************
     : AT_GetCtrlUserId
   : CTRLNDISDUP
   : VOS_VOID
   : 
     : VOS_UINT8
   :
   :

       :
  1.       : 201378
           : l60609
       : 
*****************************************************************************/
VOS_UINT8 AT_GetCtrlUserId(VOS_VOID)
{
    return g_stAtDebugInfo.ucCtrlUserId;
}

/*****************************************************************************
     : AT_SetPcui2PsCallFlag
   : PCUI2^NDISDUP
   : VOS_UINT8        ucFlag
             VOS_UINT8        ucIndex
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 2015527
           : l00198894
       : 

*****************************************************************************/
VOS_VOID AT_SetPcui2PsCallFlag(
    VOS_UINT8                           ucFlag,
    VOS_UINT8                           ucIndex
)
{
    g_stAtDebugInfo.ucPcui2PsCallFlg    = ucFlag;
    g_stAtDebugInfo.ucPcui2UserId       = AT_CLIENT_TAB_APP20_INDEX;

}

/*****************************************************************************
     : AT_GetPcui2PsCallFlag
   : PCUI2^NDISDUP
   : VOS_VOID
   : 
     : VOS_UINT8
   :
   :

       :
  1.       : 2015527
           : l00198894
       : 

*****************************************************************************/
VOS_UINT8 AT_GetPcui2PsCallFlag(VOS_VOID)
{
    return g_stAtDebugInfo.ucPcui2PsCallFlg;
}

/*****************************************************************************
     : AT_GetPcui2UserId
   : PCUI2NDISDUP
   : VOS_VOID
   : 
     : VOS_UINT8
   :
   :

       :
  1.       : 2015527
           : l00198894
       : 

*****************************************************************************/
VOS_UINT8 AT_GetPcui2UserId(VOS_VOID)
{
    return g_stAtDebugInfo.ucPcui2UserId;
}


/*****************************************************************************
     : AT_SetUnCheckApPortFlg
   :  ApPort
   : VOS_UINT8                            ucFlag
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 201481
           : n00269697
       : 
*****************************************************************************/
VOS_VOID AT_SetUnCheckApPortFlg(
    VOS_UINT8                           ucFlag
)
{
    if ((0 == ucFlag) || (1 == ucFlag))
    {
        g_stAtDebugInfo.ucUnCheckApPortFlg = ucFlag;
    }
}

/*****************************************************************************
     : AT_GetUnCheckApPortFlg
   :  ApPort
   : 
   : 
     : g_stAtDebugInfo.ucUnCheckApPortFlg
   :
   :

       :
  1.       : 201481
           : n00269697
       : 
*****************************************************************************/
VOS_UINT8 AT_GetUnCheckApPortFlg(VOS_VOID)
{
    return g_stAtDebugInfo.ucUnCheckApPortFlg;
}

/*****************************************************************************
     : AT_MNTN_TraceEvent
   : 
   : pMsg - ()
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20131111
           : A00165503
       : 
*****************************************************************************/
VOS_VOID AT_MNTN_TraceEvent(VOS_VOID *pMsg)
{

    DIAG_TraceReport(pMsg);

    return;
}

/*****************************************************************************
     : AT_MNTN_TraceInputMsc
   : 
   : ucIndex   - 
             pstDceMsc - ()
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20131111
           : A00165503
       : 
*****************************************************************************/
VOS_VOID AT_MNTN_TraceInputMsc(
    VOS_UINT8                           ucIndex,
    AT_DCE_MSC_STRU                    *pstDceMsc
)
{
    AT_MNTN_MSC_STRU                    stMntnMsc;

    /*  */
    AT_MNTN_CFG_MSG_HDR(&stMntnMsc, ID_AT_MNTN_INPUT_MSC, (sizeof(AT_MNTN_MSC_STRU) - VOS_MSG_HEAD_LENGTH));

    /*  */
    stMntnMsc.ulPortId = ucIndex;
    TAF_MEM_CPY_S(&(stMntnMsc.stDceMscInfo), sizeof(stMntnMsc.stDceMscInfo), pstDceMsc, sizeof(AT_DCE_MSC_STRU));

    /*  */
    AT_MNTN_TraceEvent(&stMntnMsc);

    return;
}

/*****************************************************************************
     : AT_MNTN_TraceOutputMsc
   : 
   : ucIndex   - 
             pstDceMsc - ()
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20131111
           : A00165503
       : 
*****************************************************************************/
VOS_VOID AT_MNTN_TraceOutputMsc(
    VOS_UINT8                           ucIndex,
    AT_DCE_MSC_STRU                    *pstDceMsc
)
{
    AT_MNTN_MSC_STRU                    stMntnMsc;

    /*  */
    AT_MNTN_CFG_MSG_HDR(&stMntnMsc, ID_AT_MNTN_OUTPUT_MSC, (sizeof(AT_MNTN_MSC_STRU) - VOS_MSG_HEAD_LENGTH));

    /*  */
    stMntnMsc.ulPortId = ucIndex;
    TAF_MEM_CPY_S(&(stMntnMsc.stDceMscInfo), sizeof(stMntnMsc.stDceMscInfo), pstDceMsc, sizeof(AT_DCE_MSC_STRU));

    /*  */
    AT_MNTN_TraceEvent(&stMntnMsc);

    return;
}

/*****************************************************************************
     : AT_MNTN_TraceStartFlowCtrl
   : 
   : ucIndex    - 
             enFcDevive - 
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20131111
           : A00165503
       : 
*****************************************************************************/
VOS_VOID AT_MNTN_TraceStartFlowCtrl(
    VOS_UINT8                           ucIndex,
    AT_FC_DEVICE_TYPE_ENUM_UINT32       enFcDevive
)
{
    AT_MNTN_FLOW_CTRL_STRU              stMntnFlowCtrl;

    /*  */
    AT_MNTN_CFG_MSG_HDR(&stMntnFlowCtrl, ID_AT_MNTN_START_FLOW_CTRL, (sizeof(AT_MNTN_FLOW_CTRL_STRU) - VOS_MSG_HEAD_LENGTH));

    /*  */
    stMntnFlowCtrl.ulPortId = ucIndex;
    stMntnFlowCtrl.enDevice = enFcDevive;

    /*  */
    AT_MNTN_TraceEvent(&stMntnFlowCtrl);

    return;
}

/*****************************************************************************
     : AT_MNTN_TraceStopFlowCtrl
   : 
   : ucIndex    - 
             enFcDevive - 
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20131111
           : A00165503
       : 
*****************************************************************************/
VOS_VOID AT_MNTN_TraceStopFlowCtrl(
    VOS_UINT8                           ucIndex,
    AT_FC_DEVICE_TYPE_ENUM_UINT32       enFcDevive
)
{
    AT_MNTN_FLOW_CTRL_STRU              stMntnFlowCtrl;

    /*  */
    AT_MNTN_CFG_MSG_HDR(&stMntnFlowCtrl, ID_AT_MNTN_STOP_FLOW_CTRL, (sizeof(AT_MNTN_FLOW_CTRL_STRU) - VOS_MSG_HEAD_LENGTH));

    /*  */
    stMntnFlowCtrl.ulPortId = ucIndex;
    stMntnFlowCtrl.enDevice = enFcDevive;

    /*  */
    AT_MNTN_TraceEvent(&stMntnFlowCtrl);

    return;
}

/*****************************************************************************
     : AT_MNTN_TraceRegFcPoint
   : 
   : ucIndex   - 
             enFcPoint - 
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20131111
           : A00165503
       : 
*****************************************************************************/
VOS_VOID AT_MNTN_TraceRegFcPoint(
    VOS_UINT8                           ucIndex,
    AT_FC_POINT_TYPE_ENUM_UINT32        enFcPoint
)
{
    AT_MNTN_FC_POINT_STRU               stMntnFcPoint;

    /*  */
    AT_MNTN_CFG_MSG_HDR(&stMntnFcPoint, ID_AT_MNTN_REG_FC_POINT, (sizeof(AT_MNTN_FC_POINT_STRU) - VOS_MSG_HEAD_LENGTH));

    /*  */
    stMntnFcPoint.ulPortId = ucIndex;
    stMntnFcPoint.enPoint  = enFcPoint;

    /*  */
    AT_MNTN_TraceEvent(&stMntnFcPoint);

    return;
}

/*****************************************************************************
     : AT_MNTN_TraceDeregFcPoint
   : 
   : ucIndex   - 
             enFcPoint - 
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20131111
           : A00165503
       : 
*****************************************************************************/
VOS_VOID AT_MNTN_TraceDeregFcPoint(
    VOS_UINT8                           ucIndex,
    AT_FC_POINT_TYPE_ENUM_UINT32        enFcPoint
)
{
    AT_MNTN_FC_POINT_STRU               stMntnFcPoint;

    /*  */
    AT_MNTN_CFG_MSG_HDR(&stMntnFcPoint, ID_AT_MNTN_DEREG_FC_POINT, (sizeof(AT_MNTN_FC_POINT_STRU) - VOS_MSG_HEAD_LENGTH));

    /*  */
    stMntnFcPoint.ulPortId = ucIndex;
    stMntnFcPoint.enPoint  = enFcPoint;

    /*  */
    AT_MNTN_TraceEvent(&stMntnFcPoint);

    return;
}

/*****************************************************************************
     : AT_MNTN_TraceCmdResult
   : AT
   : ucIndex   - 
             pucData   - 
             usDataLen - 
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20131106
           : j00174725
       : 
*****************************************************************************/
VOS_VOID AT_MNTN_TraceCmdResult(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                          *pucData,
    VOS_UINT16                          usDataLen
)
{
    AT_MSG_STRU                        *pstMsg;
    AT_INTER_MSG_ID_ENUM_UINT32         enEventId;
    VOS_UINT32                          ulLength;
    MODEM_ID_ENUM_UINT16                enModemId;

    AT_GetAtMsgStruMsgLength(usDataLen, &ulLength);

    /*  */
    pstMsg = (AT_MSG_STRU *)PS_MEM_ALLOC(WUEPS_PID_AT, (ulLength + VOS_MSG_HEAD_LENGTH));
    if (VOS_NULL_PTR == pstMsg)
    {
        AT_ERR_LOG("AT_MNTN_TraceCmdResult:ERROR:Alloc Mem Fail.");
        return;
    }

    /*  */
    enEventId       = AT_GetResultMsgID(ucIndex);
    AT_MNTN_CFG_MSG_HDR(pstMsg, enEventId, ulLength);

    /*  */
    pstMsg->ucType  = 0x1;
    pstMsg->ucIndex = ucIndex;
    pstMsg->usLen   = usDataLen;

    enModemId = MODEM_ID_0;
    if (VOS_OK != AT_GetModemIdFromClient(ucIndex, &enModemId))
    {
        enModemId = MODEM_ID_0;
    }

    pstMsg->enModemId       = (VOS_UINT8)enModemId;
    pstMsg->enVersionId     = 0xAA;
    pstMsg->aucReserved     = 0;
    AT_GetUserTypeFromIndex(ucIndex, &pstMsg->ucUserType);

    TAF_MEM_CPY_S((TAF_VOID*)pstMsg->aucValue, usDataLen, pucData, usDataLen);

    /*  */
    AT_MNTN_TraceEvent(pstMsg);

    /*  */
    PS_MEM_FREE(WUEPS_PID_AT, pstMsg);

    return;
}

/*****************************************************************************
     : AT_MNTN_TraceCmdBuffer
   : 
   : ucIndex   - 
             pucData   - 
             usDataLen - 
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 2010324
           : s46746
       : 
*****************************************************************************/
VOS_VOID AT_MNTN_TraceCmdBuffer(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                          *pucData,
    VOS_UINT16                          usDataLen
)
{
    AT_MSG_STRU                        *pstMsg;
    AT_INTER_MSG_ID_ENUM_UINT32         enEventId;
    VOS_UINT32                          ulLength;
    MODEM_ID_ENUM_UINT16                enModemId;

    AT_GetAtMsgStruMsgLength(usDataLen, &ulLength);

    /*  */
    pstMsg = (AT_MSG_STRU *)PS_MEM_ALLOC(WUEPS_PID_AT, (ulLength + VOS_MSG_HEAD_LENGTH));
    if (VOS_NULL_PTR == pstMsg)
    {
        AT_ERR_LOG("AT_MNTN_TraceCmdBuffer:ERROR:Alloc Mem Fail.");
        return;
    }

    /*  */
    enEventId       = AT_GetResultMsgID(ucIndex);
    AT_MNTN_CFG_MSG_HDR(pstMsg, enEventId, ulLength);

    /*  */
    pstMsg->ucType          = 0x2;
    pstMsg->ucIndex         = ucIndex;
    pstMsg->usLen           = usDataLen;

    enModemId               = MODEM_ID_0;
    if (VOS_OK != AT_GetModemIdFromClient(ucIndex, &enModemId))
    {
        enModemId = MODEM_ID_0;
    }

    pstMsg->enModemId       = (VOS_UINT8)enModemId;
    pstMsg->enVersionId     = 0xAA;
    pstMsg->aucReserved     = 0;

    AT_GetUserTypeFromIndex(ucIndex, &pstMsg->ucUserType);

    TAF_MEM_CPY_S((TAF_VOID*)pstMsg->aucValue, usDataLen, pucData, usDataLen);

    /*  */
    AT_MNTN_TraceEvent(pstMsg);

    /*  */
    PS_FREE_MSG(WUEPS_PID_AT, pstMsg);

    return;
}

/*****************************************************************************
     : AT_MNTN_TraceContextData
   : ATSDT
   : VOS_VOID
   : 
     : VOS_VOID
   :
   :
       :
  1.       : 20100212
           :  62575
       : 
  2.       : 2010716
           : /f62575
       : DTS2010071402189ATCLIENT ID
  3.       : 20130307
           : f00179208
       : DSDA PHASE III
*****************************************************************************/
VOS_VOID AT_MNTN_TraceContextData(VOS_VOID)
{
    NAS_AT_SDT_AT_PART_ST                  *pstSndMsgCB     = VOS_NULL_PTR;
    NAS_AT_OUTSIDE_RUNNING_CONTEXT_PART_ST *pstOutsideCtx   = VOS_NULL_PTR;
    AT_MODEM_SMS_CTX_STRU                  *pstSmsCtx       = VOS_NULL_PTR;
    MODEM_ID_ENUM_UINT16                    enModemId;

    pstSndMsgCB = (NAS_AT_SDT_AT_PART_ST *)PS_ALLOC_MSG(WUEPS_PID_AT,
                                            sizeof(NAS_AT_SDT_AT_PART_ST));

    if (VOS_NULL_PTR == pstSndMsgCB)
    {
        AT_ERR_LOG("AT_MNTN_TraceContextData:ERROR: Alloc Memory Fail.");
        return;
    }

    pstSndMsgCB->ulReceiverPid      = WUEPS_PID_AT;
    pstSndMsgCB->ulSenderPid        = WUEPS_PID_AT;
    pstSndMsgCB->ulSenderCpuId      = VOS_LOCAL_CPUID;
    pstSndMsgCB->ulReceiverCpuId    = VOS_LOCAL_CPUID;
    pstSndMsgCB->ulLength           = sizeof(NAS_AT_OUTSIDE_RUNNING_CONTEXT_PART_ST) + 4;
    pstSndMsgCB->ucType             = AT_PC_REPLAY_MSG;
    pstSndMsgCB->enMsgID            = ID_AT_MNTN_PC_REPLAY_MSG;
    pstSndMsgCB->aucReserved[0]     = 0;
    pstSndMsgCB->aucReserved[1]     = 0;
    pstSndMsgCB->aucReserved[2]     = 0;


    for (enModemId = 0; enModemId < MODEM_ID_BUTT; enModemId++)
    {
        pstSmsCtx                           = AT_GetModemSmsCtxAddrFromModemId(enModemId);
        pstOutsideCtx                       = &pstSndMsgCB->astOutsideCtx[enModemId];

        pstOutsideCtx->gucAtCscsType        = gucAtCscsType;
        pstOutsideCtx->gucAtCsdhType        = pstSmsCtx->ucCsdhType;
        pstOutsideCtx->g_OpId               = g_OpId;
        pstOutsideCtx->g_enAtCsmsMsgVersion = pstSmsCtx->enCsmsMsgVersion;
        pstOutsideCtx->g_enAtCmgfMsgFormat  = pstSmsCtx->enCmgfMsgFormat;

        TAF_MEM_CPY_S(&pstOutsideCtx->gstAtCnmiType,
                   sizeof(pstOutsideCtx->gstAtCnmiType),
                   &(pstSmsCtx->stCnmiType),
                   sizeof(pstSmsCtx->stCnmiType));

        TAF_MEM_CPY_S(&pstOutsideCtx->g_stAtCgsmsSendDomain,
                   sizeof(pstOutsideCtx->g_stAtCgsmsSendDomain),
                   &(pstSmsCtx->stCgsmsSendDomain),
                   sizeof(pstSmsCtx->stCgsmsSendDomain));

        TAF_MEM_CPY_S(&pstOutsideCtx->g_stAtCscaCsmpInfo,
                   sizeof(pstOutsideCtx->g_stAtCscaCsmpInfo),
                   &(pstSmsCtx->stCscaCsmpInfo),
                   sizeof(pstSmsCtx->stCscaCsmpInfo));

        TAF_MEM_CPY_S(&pstOutsideCtx->g_stAtCpmsInfo,
                   sizeof(pstOutsideCtx->g_stAtCpmsInfo),
                   &(pstSmsCtx->stCpmsInfo),
                   sizeof(pstSmsCtx->stCpmsInfo));

    }

    AT_MNTN_TraceEvent(pstSndMsgCB);

    PS_FREE_MSG(WUEPS_PID_AT, pstSndMsgCB);

    return;
}

/*****************************************************************************
     : AT_MNTN_TraceClientData
   : AT
   : VOS_VOID
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 2010717
           : /f62575
       : 
*****************************************************************************/
VOS_VOID AT_MNTN_TraceClientData(VOS_VOID)
{
    NAS_AT_SDT_AT_CLIENT_TABLE_STRU         *pstSndMsgCB;
    TAF_UINT8                               ucLoop;

    pstSndMsgCB = (NAS_AT_SDT_AT_CLIENT_TABLE_STRU *)PS_ALLOC_MSG(WUEPS_PID_AT,
                                            sizeof(NAS_AT_SDT_AT_CLIENT_TABLE_STRU));

    if ( VOS_NULL_PTR == pstSndMsgCB )
    {
        AT_ERR_LOG("AT_MNTN_TraceClientData:ERROR: Alloc Memory Fail.");
        return;
    }

    pstSndMsgCB->ulReceiverPid      = WUEPS_PID_AT;
    pstSndMsgCB->ulSenderPid        = WUEPS_PID_AT;
    pstSndMsgCB->ulSenderCpuId      = VOS_LOCAL_CPUID;
    pstSndMsgCB->ulReceiverCpuId    = VOS_LOCAL_CPUID;
    pstSndMsgCB->ulLength           = sizeof(NAS_AT_SDT_AT_CLIENT_TABLE_STRU) - 20;
    pstSndMsgCB->enMsgID            = ID_AT_MNTN_PC_REPLAY_CLIENT_TAB;
    pstSndMsgCB->ucType             = AT_PC_REPLAY_MSG_CLIENT_TAB;
    pstSndMsgCB->aucReserved[0]     = 0;
    pstSndMsgCB->aucReserved[1]     = 0;
    pstSndMsgCB->aucReserved[2]     = 0;

    for (ucLoop = 0; ucLoop < AT_MAX_CLIENT_NUM; ucLoop++)
    {
        pstSndMsgCB->gastAtClientTab[ucLoop].usClientId   = gastAtClientTab[ucLoop].usClientId;
        pstSndMsgCB->gastAtClientTab[ucLoop].opId         = gastAtClientTab[ucLoop].opId;
        pstSndMsgCB->gastAtClientTab[ucLoop].ucUsed       = gastAtClientTab[ucLoop].ucUsed;
        pstSndMsgCB->gastAtClientTab[ucLoop].UserType     = gastAtClientTab[ucLoop].UserType;
        pstSndMsgCB->gastAtClientTab[ucLoop].Mode         = gastAtClientTab[ucLoop].Mode;
        pstSndMsgCB->gastAtClientTab[ucLoop].IndMode      = gastAtClientTab[ucLoop].IndMode;
    }

    AT_MNTN_TraceEvent(pstSndMsgCB);

    PS_FREE_MSG(WUEPS_PID_AT, pstSndMsgCB);

    return;
}

/*****************************************************************************
     : AT_MNTN_TraceRPTPORT
   : AT
   : VOS_VOID
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 201481
           : n00269697
       : 
*****************************************************************************/
VOS_VOID AT_MNTN_TraceRPTPORT(VOS_VOID)
{
    AT_MNTN_RPTPORT_STRU                   *pstSndMsgCB;
    VOS_UINT8                               ucLoop;

    pstSndMsgCB = (AT_MNTN_RPTPORT_STRU *)PS_ALLOC_MSG(WUEPS_PID_AT,
                                            sizeof(AT_MNTN_RPTPORT_STRU));

    if ( VOS_NULL_PTR == pstSndMsgCB )
    {
        AT_ERR_LOG("AT_MNTN_TraceRPTPORT:ERROR: Alloc Memory Fail.");
        return;
    }

    pstSndMsgCB->ulReceiverPid      = WUEPS_PID_AT;
    pstSndMsgCB->ulSenderPid        = WUEPS_PID_AT;
    pstSndMsgCB->ulSenderCpuId      = VOS_LOCAL_CPUID;
    pstSndMsgCB->ulReceiverCpuId    = VOS_LOCAL_CPUID;
    pstSndMsgCB->ulLength           = sizeof(AT_MNTN_RPTPORT_STRU) - 20;
    pstSndMsgCB->enMsgId            = ID_AT_MNTN_RPT_PORT;

    for (ucLoop = 0; ucLoop < AT_MAX_CLIENT_NUM; ucLoop++)
    {
        pstSndMsgCB->astAtRptPort[ucLoop].enAtClientTabIndex = (AT_CLIENT_TAB_INDEX_UINT8)ucLoop;
        pstSndMsgCB->astAtRptPort[ucLoop].enModemId          = g_astAtClientCtx[ucLoop].stClientConfiguration.enModemId;
        pstSndMsgCB->astAtRptPort[ucLoop].ucReportFlg        = g_astAtClientCtx[ucLoop].stClientConfiguration.ucReportFlg;
    }

    AT_MNTN_TraceEvent(pstSndMsgCB);

    PS_FREE_MSG(WUEPS_PID_AT, pstSndMsgCB);

    return;
}

/*****************************************************************************
     : AT_InitHsUartStats
   : UART
   : VOS_VOID
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20130921
           : j00174725
       : 
*****************************************************************************/
VOS_VOID AT_InitHsUartStats(VOS_VOID)
{
    TAF_MEM_SET_S(&g_stAtStatsInfo.stHsUartStats, sizeof(g_stAtStatsInfo.stHsUartStats), 0x00, sizeof(AT_MNTN_HSUART_STATS_STRU));
    return;
}

/*****************************************************************************
     : AT_MODEM_Help
   : UART
   : VOS_VOID
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20131111
           : A00165503
       : 
*****************************************************************************/
VOS_VOID AT_InitModemStats(VOS_VOID)
{
    TAF_MEM_SET_S(&g_stAtStatsInfo.stModemStats, sizeof(g_stAtStatsInfo.stModemStats), 0x00, sizeof(AT_MNTN_MODEM_STATS_STRU));
    return;
}

/*****************************************************************************
     : AT_RecordAtMsgInfo
   : At_MsgProc
   : VOS_UINT32                          ulSendPid,
             VOS_UINT32                          ulMsgName,
             VOS_UINT32                          ulSliceStart,
             VOS_UINT32                          ulSliceEnd
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20140904
           : g00261581
       : 
*****************************************************************************/
VOS_VOID AT_RecordAtMsgInfo(
    VOS_UINT32                          ulSendPid,
    VOS_UINT32                          ulMsgName,
    VOS_UINT32                          ulSliceStart,
    VOS_UINT32                          ulSliceEnd
)
{
    VOS_UINT32                          ulIndex;

    if (g_stAtMsgRecordInfo.ulCurrentIndex >= AT_MNTN_MSG_RECORD_MAX_NUM)
    {
        g_stAtMsgRecordInfo.ulCurrentIndex = 0;
    }

    ulIndex = g_stAtMsgRecordInfo.ulCurrentIndex;

    g_stAtMsgRecordInfo.astAtMntnMsgRecord[ulIndex].ulSendPid    = ulSendPid;
    g_stAtMsgRecordInfo.astAtMntnMsgRecord[ulIndex].ulMsgName    = ulMsgName;
    g_stAtMsgRecordInfo.astAtMntnMsgRecord[ulIndex].ulSliceStart = ulSliceStart;
    g_stAtMsgRecordInfo.astAtMntnMsgRecord[ulIndex].ulSliceEnd   = ulSliceEnd;

    g_stAtMsgRecordInfo.ulCurrentIndex++;

    return;
}


/*****************************************************************************
     : AT_ShowModemDataStats
   : MODEM
   : VOS_VOID
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20111018
           : sunshaohua
       : 
*****************************************************************************/
VOS_VOID AT_ShowModemDataStats(VOS_VOID)
{
    (VOS_VOID)vos_printf("====================================\r\n");
    (VOS_VOID)vos_printf("MODEM UL DATA STATS                 \r\n");
    (VOS_VOID)vos_printf("====================================\r\n");
    (VOS_VOID)vos_printf("UL Read CB NUM:             %d\r\n", g_stAtStatsInfo.stModemStats.ulUlDataReadCBNum);
    (VOS_VOID)vos_printf("UL RD SUCC NUM:             %d\r\n", g_stAtStatsInfo.stModemStats.ulUlGetRDSuccNum);
    (VOS_VOID)vos_printf("UL RD Fail NUM:             %d\r\n", g_stAtStatsInfo.stModemStats.ulUlGetRDFailNum);
    (VOS_VOID)vos_printf("UL Invalid RD NUM:          %d\r\n", g_stAtStatsInfo.stModemStats.ulUlInvalidRDNum);
    (VOS_VOID)vos_printf("UL Retrun BUFF SUCC NUM:    %d\r\n", g_stAtStatsInfo.stModemStats.ulUlReturnBuffSuccNum);
    (VOS_VOID)vos_printf("UL Retrun BUFF FAIL NUM:    %d\r\n", g_stAtStatsInfo.stModemStats.ulUlReturnBuffFailNum);
    (VOS_VOID)vos_printf("====================================\r\n");
    (VOS_VOID)vos_printf("MODEM DL DATA STATS                 \r\n");
    (VOS_VOID)vos_printf("====================================\r\n");
    (VOS_VOID)vos_printf("DL Write Async SUCC NUM:    %d\r\n", g_stAtStatsInfo.stModemStats.ulDlWriteAsyncSuccNum);
    (VOS_VOID)vos_printf("DL Write Async FAIL NUM:    %d\r\n", g_stAtStatsInfo.stModemStats.ulDlWriteAsyncFailNum);
    (VOS_VOID)vos_printf("DL Free BUFF NUM:           %d\r\n", g_stAtStatsInfo.stModemStats.ulDlFreeBuffNum);


    return;
}

/*****************************************************************************
     : AT_ShowPsEntityInfo
   : PS
   : ucCallId - 
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20121231
           : A00165503
       : 
*****************************************************************************/
VOS_VOID AT_ShowPsEntityInfo(VOS_UINT8 ucCallId)
{
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT8                           aucIpv6AddrStr[TAF_MAX_IPV6_ADDR_COLON_STR_LEN];
    VOS_UINT8                           aucIpv6PrimDnsStr[TAF_MAX_IPV6_ADDR_COLON_STR_LEN];
    VOS_UINT8                           aucIpv6SecDnsStr[TAF_MAX_IPV6_ADDR_COLON_STR_LEN];

    for (enModemId = 0; enModemId < MODEM_ID_BUTT; enModemId++)
    {
        (VOS_VOID)vos_printf("################MODEM ID is %d################\n", enModemId);
        pstCallEntity = &(AT_GetModemPsCtxAddrFromModemId(enModemId)->astCallEntity[ucCallId]);

        (VOS_VOID)vos_printf("********************PS***********************\n");
        (VOS_VOID)vos_printf("Active Flag                             %d\n", pstCallEntity->ulUsedFlg);
        (VOS_VOID)vos_printf("Current Call Type                       %d\n", pstCallEntity->enCurrPdpType);
        (VOS_VOID)vos_printf("*********************************************\n");
        (VOS_VOID)vos_printf("User Actual Index                       %d\n", pstCallEntity->stUserInfo.enPortIndex);
        (VOS_VOID)vos_printf("User Expect Index                       %d\n", pstCallEntity->stUserInfo.enUserIndex);
        (VOS_VOID)vos_printf("User Type                               %d\n", pstCallEntity->stUserInfo.ucUsrType);
        (VOS_VOID)vos_printf("User CID                                %d\n", pstCallEntity->stUserInfo.ucUsrCid);
        (VOS_VOID)vos_printf("********************IPv4*************************\n");
        (VOS_VOID)vos_printf("IPv4 Bearer CID                         %d\n", pstCallEntity->ucIpv4Cid);
        (VOS_VOID)vos_printf("IPv4 Bearer State                       %d\n", pstCallEntity->enIpv4State);
        (VOS_VOID)vos_printf("IPv4 Bearer ID (RAB ID)                 %d\n", pstCallEntity->stIpv4DhcpInfo.ucRabId);
        (VOS_VOID)vos_printf("IPv4 Bearer Address                     0x%x\n", pstCallEntity->stIpv4DhcpInfo.ulIpv4Addr);
        (VOS_VOID)vos_printf("IPv4 Bearer Primary DNS                 0x%x\n", pstCallEntity->stIpv4DhcpInfo.ulIpv4PrimDNS);
        (VOS_VOID)vos_printf("IPv4 Bearer Secondary DNS               0x%x\n", pstCallEntity->stIpv4DhcpInfo.ulIpv4SecDNS);
        (VOS_VOID)vos_printf("IPv4 Bearer Gate Way                    0x%x\n", pstCallEntity->stIpv4DhcpInfo.ulIpv4GateWay);
        (VOS_VOID)vos_printf("IPv4 Bearer NET Mask                    0x%x\n", pstCallEntity->stIpv4DhcpInfo.ulIpv4NetMask);
        (VOS_VOID)vos_printf("***********************************************************\n");

        TAF_MEM_SET_S(aucIpv6AddrStr, sizeof(aucIpv6AddrStr), 0x00, sizeof(aucIpv6AddrStr));
        TAF_MEM_SET_S(aucIpv6PrimDnsStr, sizeof(aucIpv6PrimDnsStr), 0x00, sizeof(aucIpv6PrimDnsStr));
        TAF_MEM_SET_S(aucIpv6SecDnsStr, sizeof(aucIpv6SecDnsStr), 0x00, sizeof(aucIpv6SecDnsStr));

        AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                          pstCallEntity->stIpv6DhcpInfo.aucIpv6Addr,
                                          TAF_IPV6_STR_RFC2373_TOKENS);

        AT_ConvertIpv6AddrToCompressedStr(aucIpv6PrimDnsStr,
                                          pstCallEntity->stIpv6DhcpInfo.aucIpv6PrimDNS,
                                          TAF_IPV6_STR_RFC2373_TOKENS);

        AT_ConvertIpv6AddrToCompressedStr(aucIpv6SecDnsStr,
                                          pstCallEntity->stIpv6DhcpInfo.aucIpv6SecDNS,
                                          TAF_IPV6_STR_RFC2373_TOKENS);

        (VOS_VOID)vos_printf("********************IPv6*************************\n");
        (VOS_VOID)vos_printf("IPv6 Bearer CID                         %d\n", pstCallEntity->ucIpv6Cid);
        (VOS_VOID)vos_printf("IPv6 Bearer State                       %d\n", pstCallEntity->enIpv6State);
        (VOS_VOID)vos_printf("***********************************************************\n");
        (VOS_VOID)vos_printf("IPv6 Bearer ID (RAB ID)                 %d\n", pstCallEntity->stIpv6DhcpInfo.ucRabId);
        (VOS_VOID)vos_printf("IPv6 Bearer Global Address              %s\n", aucIpv6AddrStr);
        (VOS_VOID)vos_printf("IPv6 Bearer Primary DNS                 %s\n", aucIpv6PrimDnsStr);
        (VOS_VOID)vos_printf("IPv6 Bearer Secondary DNS               %s\n", aucIpv6SecDnsStr);
        (VOS_VOID)vos_printf("***********************************************************\n");
    }

    return;
}

/*****************************************************************************
     : AT_ShowPsFcIdState
   : AT
   : 
   : 
     :

   :
   :

   :
    1.       : 20130415
             : f00179208
         : 
*****************************************************************************/
VOS_VOID AT_ShowPsFcIdState(VOS_UINT32 ulFcid)
{
    if (ulFcid >= FC_ID_BUTT)
    {
        (VOS_VOID)vos_printf("AT_ShowFcStatsInfo: Fcid overtop, ulFcid = %d\n", ulFcid);
        return;
    }

    (VOS_VOID)vos_printf("FCID                  %d\n", g_stFcIdMaptoFcPri[ulFcid].ulUsed);
    (VOS_VOID)vos_printf("FCID                  %d\n", g_stFcIdMaptoFcPri[ulFcid].enFcPri);
    (VOS_VOID)vos_printf("FCIDRABID               %d\n", g_stFcIdMaptoFcPri[ulFcid].ulRabIdMask);
    (VOS_VOID)vos_printf("FCIDModemId                 %d\n", g_stFcIdMaptoFcPri[ulFcid].enModemId);
    (VOS_VOID)vos_printf("\r\n");

    return;
}

/*****************************************************************************
     : AT_ShowResetStats
   : AT
   : 
   : 
     :

   :
   :

   :
    1.       : 20130415
             : f00179208
         : 
*****************************************************************************/
VOS_VOID AT_ShowResetStatsInfo(VOS_VOID)
{
    (VOS_VOID)vos_printf("                              %d\n", g_stAtStatsInfo.stCCpuResetStatsInfo.ulSemInitFlg);
    (VOS_VOID)vos_printf("                          %p\n", AT_GetResetSem());
    (VOS_VOID)vos_printf("                          %p\n", g_stAtStatsInfo.stCCpuResetStatsInfo.hBinarySemId);
    (VOS_VOID)vos_printf("                    %d\n", g_stAtStatsInfo.stCCpuResetStatsInfo.ulCreateBinarySemFailNum);
    (VOS_VOID)vos_printf("                      %d\n", g_stAtStatsInfo.stCCpuResetStatsInfo.ulLockBinarySemFailNum);
    (VOS_VOID)vos_printf("              %x\n", g_stAtStatsInfo.stCCpuResetStatsInfo.ulLastBinarySemErrRslt);
    (VOS_VOID)vos_printf("C                             %d\n", g_stAtStatsInfo.stCCpuResetStatsInfo.ulResetBeforeNum);
    (VOS_VOID)vos_printf("C                             %d\n", g_stAtStatsInfo.stCCpuResetStatsInfo.ulResetAfterNum);
    (VOS_VOID)vos_printf("HIFI                          %d\n", g_stAtStatsInfo.stCCpuResetStatsInfo.ulHifiResetNum);
    (VOS_VOID)vos_printf("AT                                  %d\n", AT_GetResetFlag());
    (VOS_VOID)vos_printf("\r\n");

    return;
}

/*****************************************************************************
     : AT_ShowAllClientState
   : 
   : VOS_VOID
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20140115
           : j00174725
       : 
*****************************************************************************/
VOS_VOID AT_ShowAllClientState(VOS_VOID)
{
    VOS_UINT8                           i;
    VOS_CHAR                            acStateStr[][20] = {"READY", "PEND"};
    VOS_CHAR                            acModeStr[][20] = {"CMD", "DATA", "ONLINE_CMD"};

    (VOS_VOID)vos_printf("\r\n The All Client State: \r\n");

    for (i = 0; i < AT_MAX_CLIENT_NUM; i++)
    {
        (VOS_VOID)vos_printf("Client[%d] State: %s    Mode: %s\r\n", i,
            acStateStr[g_stParseContext[i].ucClientStatus], acModeStr[gastAtClientTab[i].Mode]);
    }

    return;
}

/*****************************************************************************
     : AT_SetClientState
   : 
   : ucIndex -- clientID
             ulState -- (Pend/Ready)
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20140115
           : j00174725
       : 
*****************************************************************************/
VOS_VOID AT_SetClientState(VOS_UINT8 ucIndex, VOS_UINT8 ucState)
{
    if ((ucIndex >= AT_MAX_CLIENT_NUM)||(ucState > AT_FW_CLIENT_STATUS_PEND))
    {
        return;
    }

    g_stParseContext[ucIndex].ucClientStatus = ucState;

    return;
}

/*****************************************************************************
     : AT_SetClientMode
   : 
   : ucIndex -- clientID
             ucMode -- 
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20140115
           : j00174725
       : 
*****************************************************************************/
VOS_VOID AT_SetClientMode(VOS_UINT8 ucIndex, VOS_UINT8 ucMode)
{
    if ((ucIndex >= AT_MAX_CLIENT_NUM)||(ucMode > AT_ONLINE_CMD_MODE))
    {
        return;
    }

    gastAtClientTab[ucIndex].Mode = ucMode;

    return;
}

/*****************************************************************************
     : AT_ShowUsedClient
   : 
   : ucIndex -- clientID
             ucMode -- 
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20140115
           : j00174725
       : 
*****************************************************************************/
VOS_VOID AT_ShowUsedClient(VOS_VOID)
{
    AT_PORT_BUFF_CFG_STRU              *pstPortCfg;
    VOS_UINT32                          ulIndex;
    VOS_UINT8                           i;
    VOS_CHAR                            acStateStr[][20] = {"READY", "PEND"};
    VOS_CHAR                            acModeStr[][20] = {"CMD", "DATA", "ONLINE_CMD"};

    pstPortCfg = AT_GetPortBuffCfgInfo();

    (VOS_VOID)vos_printf("\r\n The All Used Client State: \r\n");
    for (i = 0; i < pstPortCfg->ucNum; i++)
    {
        ulIndex = pstPortCfg->ulUsedClientID[i];
        (VOS_VOID)vos_printf("Client[%d] State: %s    Mode: %s\r\n", ulIndex,
            acStateStr[g_stParseContext[ulIndex].ucClientStatus], acModeStr[gastAtClientTab[ulIndex].Mode]);
    }

    return;
}


/*****************************************************************************
     : AT_ShowClientCtxInfo
   : Client
   : 
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20140425
           : f00179208
       : 
*****************************************************************************/
VOS_VOID AT_ShowClientCtxInfo(VOS_VOID)
{
    VOS_UINT8                           i;
    AT_CLIENT_CFG_MAP_TAB_STRU         *pstCfgMapTbl;
    AT_CLIENT_CONFIGURATION_STRU       *pstClientCfg;

    (VOS_VOID)vos_printf("\r\n The All Used Client Config: \r\n");
    for (i = 0; i < AT_GET_CLIENT_CFG_TAB_LEN(); i++)
    {
        pstCfgMapTbl = AT_GetClientCfgMapTbl(i);
        pstClientCfg = AT_GetClientConfig(pstCfgMapTbl->enClientId);
        (VOS_VOID)vos_printf("Client[%s] modem:%d, reportFlag:%d\r\n",
                   pstCfgMapTbl->aucPortName,
                   pstClientCfg->enModemId,
                   pstClientCfg->ucReportFlg);
    }
}

/*****************************************************************************
     : AT_Help
   : AT
   : VOS_VOID
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20131112
           : A00165503
       : 
*****************************************************************************/
VOS_VOID AT_Help(VOS_VOID)
{
    (VOS_VOID)vos_printf("********************************************************\n");
    (VOS_VOID)vos_printf("PS                                              \n");
    (VOS_VOID)vos_printf("********************************************************\n");
    (VOS_VOID)vos_printf("AT_ShowPsEntityInfo                     \n");
    (VOS_VOID)vos_printf("AT_ShowPsFcIdState(ulFcid)            \n");
    (VOS_VOID)vos_printf("********************************************************\n");
    (VOS_VOID)vos_printf("UART                                            \n");
    (VOS_VOID)vos_printf("********************************************************\n");
    (VOS_VOID)vos_printf("AT_ShowHsUartConfigInfo     HSUART        \n");
    (VOS_VOID)vos_printf("AT_ShowHsUartNvStats        HSUARTNV  \n");
    (VOS_VOID)vos_printf("AT_ShowHsUartIoctlStats     HSUARTIOCTL   \n");
    (VOS_VOID)vos_printf("AT_ShowHsUartDataStats      HSUART    \n");
    (VOS_VOID)vos_printf("AT_ShowHsUartFcState        HSUART    \n");
    (VOS_VOID)vos_printf("********************************************************\n");
    (VOS_VOID)vos_printf("MODEM                                           \n");
    (VOS_VOID)vos_printf("********************************************************\n");
    (VOS_VOID)vos_printf("AT_ShowModemDataStats       MODEM     \n");
    (VOS_VOID)vos_printf("********************************************************\n");
    (VOS_VOID)vos_printf("                                            \n");
    (VOS_VOID)vos_printf("********************************************************\n");
    (VOS_VOID)vos_printf("AT_ShowResetStatsInfo       AT          \n");
    (VOS_VOID)vos_printf("AT_ShowAllClientState                   \n");
    (VOS_VOID)vos_printf("AT_ShowClientCtxInfo        Client  \n");

    return;
}




