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
#include "vos.h"
#include "PsCommonDef.h"
#include "AtMnInterface.h"
#include "MnCallApi.h"
#include  "product_config.h"
#include "MnErrorCode.h"
#include "AtParse.h"
#include "ATCmdProc.h"

#include "TafAppCall.h"


#define    THIS_FILE_ID        PS_FILE_ID_MNCALL_API_C

/*****************************************************************************
   2 
*****************************************************************************/

/*****************************************************************************
     : MN_CALL_SendAppRequest
   : APPCCA
   : enReq    - 
              clientId - Client ID
              opId     - 
              callId   - ID
              punParam - 
   : 
     :
   :
   :

       :
  1.       : 2007920
           :  49431
       : 
  2.       : 20111107
           : f00179208
       : AT Project, ATWUEPS_PID_VCWUEPS_PID_AT
  3.       : 2012927
           : A00165503
       : STK&DCM: CS
  4.       : 20121222
           : l00227485
       : DSDA phaseII

*****************************************************************************/
VOS_UINT32  MN_CALL_SendAppRequest(
    MN_CALL_APP_REQ_ENUM_UINT32         enReq,
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_ID_T                        callId,
    const MN_CALL_APP_REQ_PARM_UNION   *punParam
)
{
    MN_CALL_APP_REQ_MSG_STRU *pstMsg =
        (MN_CALL_APP_REQ_MSG_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_AT,
                                              sizeof(MN_CALL_APP_REQ_MSG_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        AT_ERR_LOG("MN_CALL_SendAppRequest: Failed to alloc VOS message.");
        return VOS_ERR;
    }

    TAF_MEM_SET_S((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,
               (VOS_SIZE_T)(sizeof(MN_CALL_APP_REQ_MSG_STRU) - VOS_MSG_HEAD_LENGTH),
                0x00,
               (VOS_SIZE_T)(sizeof(MN_CALL_APP_REQ_MSG_STRU) - VOS_MSG_HEAD_LENGTH));

    /* VOS */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = WUEPS_PID_AT;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = AT_GetDestPid(clientId, I0_WUEPS_PID_TAF);

    /*  */
    pstMsg->enReq = enReq;
    pstMsg->clientId = clientId;
    pstMsg->opId = opId;
    pstMsg->callId = callId;

    if (TAF_NULL_PTR != punParam)
    {
        TAF_MEM_CPY_S(&pstMsg->unParm, sizeof(pstMsg->unParm), punParam, sizeof(pstMsg->unParm));
    }

    /* VOS */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_AT, pstMsg))
    {
        AT_ERR_LOG1("MN_CALL_SendAppRequest: Send Message Fail. reqtype:", (VOS_INT32)enReq);
        return VOS_ERR;
    }

    return VOS_OK;
}


/*****************************************************************************
     : MN_CALL_Orig
   : 
   : clientId   - Client ID
             opId       - 
             pstOrigParam - 
   : pCallId    - ID, 
     :
   :
   :

       :
  1.       : 2007920
           :  49431
       : 
  2.       : 20111006
           : f00179208
       : AT, CALLIdC
  3.       : 2012925
           : A00165503
       : STK&DCM: CS
*****************************************************************************/
VOS_UINT32  MN_CALL_Orig(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_ID_T                       *pCallId,
    const MN_CALL_ORIG_PARAM_STRU      *pstOrigParam
)
{
    VOS_UINT32                          ulResult;
    MN_CALL_ID_T                        callId;
    MN_CALL_APP_REQ_PARM_UNION          stAppReq;

    /* CallIdcallId0
       CallIdMN CALL */
    callId = 0;

    TAF_MEM_SET_S(&stAppReq, (VOS_UINT32)sizeof(stAppReq), 0x00, (VOS_UINT32)sizeof(stAppReq));
    TAF_MEM_CPY_S(&(stAppReq.stOrig), (VOS_UINT32)sizeof(stAppReq.stOrig), pstOrigParam, (VOS_UINT32)sizeof(MN_CALL_ORIG_PARAM_STRU));

    /*  */
    ulResult = MN_CALL_SendAppRequest(MN_CALL_APP_ORIG_REQ, clientId,
                                      opId, callId,
                                      &stAppReq);

    *pCallId = callId;

    return ulResult;

}


/*****************************************************************************
     : MN_CALL_End
   : 
   : clientId   - Client ID
             opId       - 
             callId     - ID
             pstEndParam  - , , NULL
   : 
     :
   :
   :

       :
  1.       : 2007920
           :  49431
       : 
  2.       : 20120918
           : y00213812
       : STK&DCM CS

*****************************************************************************/
VOS_UINT32  MN_CALL_End(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_ID_T                        callId,
    const MN_CALL_END_PARAM_STRU       *pstEndParam
)
{
    MN_CALL_APP_REQ_PARM_UNION          stAppReq;
    VOS_UINT32                          ulResult;

    TAF_MEM_SET_S(&stAppReq, (VOS_UINT32)sizeof(stAppReq), 0x00, (VOS_UINT32)sizeof(stAppReq));

    if ( TAF_NULL_PTR == pstEndParam)
    {
        /* MN_CALL_END_REQ_PARAM_STRU, 255 */
        stAppReq.stEnd.enEndCause = MN_CALL_INTERWORKING_UNSPECIFIED;
    }
    else
    {
        stAppReq.stEnd.enEndCause = pstEndParam->enEndCause;
    }

    /*  */
    ulResult = MN_CALL_SendAppRequest(MN_CALL_APP_END_REQ, clientId,
                                      opId, callId,
                                      &stAppReq);

    return ulResult;
}

/* Added by f62575 for AT Project, 2011-10-04,  Begin */
/*****************************************************************************
     : MN_CALL_QryCdur
   : 
   : MN_CLIENT_ID_T                      clientId  Client ID
             MN_OPERATION_ID_T                   opId      
             MN_CALL_ID_T                        callId    ID
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 2011106
           : f62575
       : 

*****************************************************************************/
VOS_UINT32  MN_CALL_QryCdur(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_ID_T                        callId
)
{
    VOS_UINT32                          ulResult;

    /*  */
    ulResult = MN_CALL_SendAppRequest(MN_CALL_APP_GET_CDUR_REQ, clientId,
                                      opId, callId,
                                      VOS_NULL_PTR);

    return ulResult;
}
/* Added by f62575 for AT Project, 2011-10-04,  End */

/*****************************************************************************
     : TAF_CALL_SendDtmf
   : APPTAFDTMF
   : enMsgType      - DTMF
             clientId       - Client ID
             opId           - 
             pstDtmfParam   - DTMF
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 20130711
           : l00198894
       : V9R1 STK
*****************************************************************************/
VOS_UINT32  TAF_CALL_SendDtmf(
    AT_MN_MSGTYPE_ENUM_UINT16           enMsgType,
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const TAF_CALL_DTMF_PARAM_STRU     *pstDtmfParam
)
{
    VOS_UINT32                          ulResult;
    MN_CALL_APP_REQ_PARM_UNION          stAppPara;

    /*  */
    TAF_MEM_SET_S(&stAppPara, sizeof(stAppPara), 0x00, sizeof(stAppPara));
    TAF_MEM_CPY_S(&stAppPara.stDtmf, sizeof(stAppPara.stDtmf), pstDtmfParam, sizeof(TAF_CALL_DTMF_PARAM_STRU));

    /*  */
    ulResult = MN_CALL_SendAppRequest(enMsgType, clientId, opId,
                                      pstDtmfParam->CallId,
                                      &stAppPara);

    return ulResult;
}

/*****************************************************************************
     : MN_CALL_Sups
   : 
   : clientId   - Client ID
             opId       - 
             pstCallSupsParam   - 
   : 
     :
   :
   :

       :
  1.       : 2007920
           :  49431
       : 
  2.       : 2012925
           : A00165503
       : STK&DCM: CS
  3.       : 20130930
           : s00217060
       : VoLTE_PhaseIICallId
*****************************************************************************/
VOS_UINT32  MN_CALL_Sups(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_CALL_SUPS_PARAM_STRU       *pstCallSupsParam
)
{
    VOS_UINT32                          ulResult;
    MN_CALL_APP_REQ_PARM_UNION          stAppPara;

    TAF_MEM_SET_S(&stAppPara, (VOS_UINT32)sizeof(stAppPara), 0x00, (VOS_UINT32)sizeof(stAppPara));
    TAF_MEM_CPY_S(&stAppPara.stCallMgmtCmd, (VOS_UINT32)sizeof(stAppPara.stCallMgmtCmd), pstCallSupsParam, (VOS_UINT32)sizeof(MN_CALL_SUPS_PARAM_STRU));

    /*  */
    /* Modified by s00217060 for VoLTE_PhaseII  , 2013-09-30, begin */
    /* CallId */
    ulResult = MN_CALL_SendAppRequest(MN_CALL_APP_SUPS_CMD_REQ, clientId,
                                      opId, pstCallSupsParam->callId,
                                      &stAppPara);
    /* Modified by s00217060 for VoLTE_PhaseII  , 2013-09-30, end */

    return ulResult;
}


/*****************************************************************************
     : MN_CALL_GetInfoList
   : IDLE
   : pNumOfCalls - 
   : pNumOfCalls - (IDLE)
              pstCallInfos  - 
     :
   :
   :

       :
  1.       : 2007920
           :  49431
       : 

  2.       : 201031
           : zhoujun /z40661
       : 
  3.       : 20111015
           : f00179208
       : ATCCALL Info
  4.       : 2012925
           : A00165503
       : STK&DCM: CS
*****************************************************************************/
VOS_UINT32  MN_CALL_GetCallInfos(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_ID_T                        callId
)
{
    VOS_UINT32                          ulResult;

    /*  */
    ulResult = MN_CALL_SendAppRequest(MN_CALL_APP_GET_INFO_REQ, clientId,
                                      opId, callId,
                                      VOS_NULL_PTR);

    return ulResult;
}

/*****************************************************************************
     : MN_CALL_SetAlsLineNo
   : NV
   : enAlsLine : 
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 2010122
           : z40661
       : 
  2.       : 20111024
           : c00173809
       : ATMN_CALL_UpdateAlsLineInfo

  3.       : 20111024
           : o00132663
       : AT CC APIMN_CALL_UpdateAlsLineInfo
                 
  4.       : 2012925
           : A00165503
       : STK&DCM: CS
*****************************************************************************/
VOS_UINT32 MN_CALL_SetAlsLineNo(
    TAF_UINT8                           ucIndex,
    MN_CALL_ALS_LINE_NO_ENUM_U8         enAlsLine
)
{
    VOS_UINT32                          ulRst;
    MN_CALL_APP_REQ_PARM_UNION          stAppReq;

    stAppReq.stSetAls.enAlsLine = enAlsLine;

    /*1.TAF_MSG_ALS_LINE_NO_SETMN_CALL_ALS_PARAM_STRU
        TAFALS*/
    ulRst = MN_CALL_SendAppRequest(MN_CALL_APP_SET_ALS_REQ,
                                   gastAtClientTab[ucIndex].usClientId,
                                   At_GetOpId(),
                                   0,
                                   &stAppReq);
    return ulRst;
}

/*****************************************************************************
     : MN_CALL_CheckUus1ParmValid
   : UUS1
   : enSetType      :UUS1
             pstUus1Info    :UUS1
   : 
     : VOS_UINT32     :
   :
   :

       :
  1.       : 2010727
           : zhoujun /40661
       : 

*****************************************************************************/
VOS_UINT32 MN_CALL_CheckUus1ParmValid(
    MN_CALL_SET_UUS1_TYPE_ENUM_U32      enSetType,
    MN_CALL_UUS1_INFO_STRU              *pstUus1Info
)
{
    if ( VOS_NULL_PTR == pstUus1Info )
    {
        return MN_ERR_INVALIDPARM;
    }

    /*  , */
    if ( ( enSetType >= MN_CALL_SET_UUS1_BUTT )
      || ( pstUus1Info->enMsgType > MN_CALL_UUS1_MSG_RELEASE_COMPLETE ))
    {
        return MN_ERR_INVALIDPARM;
    }


    /* UUIEUUIE,PD,
       ,UUS1,  */
    if ( ( MN_CALL_SET_UUS1_ACT == enSetType)
      && ( MN_CALL_UUS_IEI != pstUus1Info->aucUuie[MN_CALL_IEI_POS]))
    {
        return MN_ERR_INVALIDPARM;
    }

    return MN_ERR_NO_ERROR;
}

/*****************************************************************************
     : TAF_XCALL_SendFlashReq
   : APPTAFFlash
   : clientId       - Client ID
             opId           - 
             pstFlashPara   - Flash
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 2014118
           : L00256032
       : 1X SS Project
*****************************************************************************/
VOS_UINT32  TAF_XCALL_SendFlashReq(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    TAF_CALL_FLASH_PARA_STRU           *pstFlashPara
)
{
    TAF_CALL_APP_SEND_FLASH_REQ_STRU *pstMsg =
        (TAF_CALL_APP_SEND_FLASH_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_AT,
                                              sizeof(TAF_CALL_APP_SEND_FLASH_REQ_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        AT_ERR_LOG("TAF_XCALL_SendFlashReq: Failed to alloc VOS message.");
        return VOS_ERR;
    }

    TAF_MEM_SET_S((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,
               (VOS_SIZE_T)(sizeof(TAF_CALL_APP_SEND_FLASH_REQ_STRU) - VOS_MSG_HEAD_LENGTH),
                0x00,
               (VOS_SIZE_T)(sizeof(TAF_CALL_APP_SEND_FLASH_REQ_STRU) - VOS_MSG_HEAD_LENGTH));

    /* VOS */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = WUEPS_PID_AT;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = AT_GetDestPid(clientId, I0_WUEPS_PID_TAF);

    /*  */
    pstMsg->usMsgId    = TAF_CALL_APP_SEND_FLASH_REQ;
    pstMsg->usClientId = clientId;
    pstMsg->ucOpId     = opId;
    TAF_MEM_CPY_S(&(pstMsg->stFlashPara), sizeof(pstMsg->stFlashPara), pstFlashPara, sizeof(TAF_CALL_FLASH_PARA_STRU));

    /* VOS */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_AT, pstMsg))
    {
        AT_ERR_LOG("TAF_XCALL_SendFlashReq: Send TAF_CALL_APP_SEND_FLASH_REQ Message Fail");
        return VOS_ERR;
    }

    return VOS_OK;
}

/* Added by f279542 for CDMA 1X Iteration 4, 2014-11-10, begin */
/*****************************************************************************
     : TAF_XCALL_SendBurstDtmf
   : APPTAFFlash
   : clientId              - Client ID
             opId                  - 
             pstSndBurstDTMFPara   - Send Burst Dtmf
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 20141110
           : f279542
       : 
*****************************************************************************/
VOS_UINT32  TAF_XCALL_SendBurstDtmf(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    TAF_CALL_BURST_DTMF_PARA_STRU      *pstSndBurstDTMFPara
)
{
    TAF_CALL_BURST_DTMF_REQ_MSG_STRU *pstMsg =
        (TAF_CALL_BURST_DTMF_REQ_MSG_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_AT,
                                              sizeof(TAF_CALL_BURST_DTMF_REQ_MSG_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        AT_ERR_LOG("TAF_XCALL_SendBurstDtmf: Failed to alloc VOS message.");
        return VOS_ERR;
    }

    TAF_MEM_SET_S((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,
               (VOS_SIZE_T)(sizeof(TAF_CALL_BURST_DTMF_REQ_MSG_STRU) - VOS_MSG_HEAD_LENGTH),
                0x00,
               (VOS_SIZE_T)(sizeof(TAF_CALL_BURST_DTMF_REQ_MSG_STRU) - VOS_MSG_HEAD_LENGTH));

    /* VOS */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = WUEPS_PID_AT;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = AT_GetDestPid(clientId, I0_WUEPS_PID_TAF);

    /*  */
    pstMsg->usMsgId    = TAF_CALL_APP_SEND_BURST_DTMF_REQ;
    pstMsg->usClientId = clientId;
    pstMsg->ucOpId     = opId;
    TAF_MEM_CPY_S(&(pstMsg->stBurstDTMFPara), sizeof(pstMsg->stBurstDTMFPara), pstSndBurstDTMFPara, sizeof(TAF_CALL_BURST_DTMF_PARA_STRU));

    /* VOS */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_AT, pstMsg))
    {
        AT_ERR_LOG("TAF_XCALL_SendBurstDtmf: Send TAF_CALL_APP_SEND_BURST_DTMF_REQ Message Fail");
        return VOS_ERR;
    }

    return VOS_OK;
}
/* Added by f279542 for CDMA 1X Iteration 4, 2014-11-10, end */

/*****************************************************************************
     : TAF_XCALL_SendCustomDialReq
   : APPTAFFlash
   : clientId       - Client ID
             opId           - 
             pstFlashPara   - Flash
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 201548
           : w00242748
       : 
*****************************************************************************/
VOS_UINT32  TAF_XCALL_SendCustomDialReq(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    TAF_CALL_CUSTOM_DIAL_PARA_STRU     *pstCustomDialPara
)
{
    TAF_CALL_APP_SEND_CUSTOM_DIAL_REQ_STRU *pstMsg =
        (TAF_CALL_APP_SEND_CUSTOM_DIAL_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_AT,
                                              sizeof(TAF_CALL_APP_SEND_CUSTOM_DIAL_REQ_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        AT_ERR_LOG("TAF_XCALL_SendCustomDialReq: Failed to alloc VOS message.");
        return VOS_FALSE;
    }

    TAF_MEM_SET_S((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,
               (VOS_SIZE_T)(sizeof(TAF_CALL_APP_SEND_CUSTOM_DIAL_REQ_STRU) - VOS_MSG_HEAD_LENGTH),
                0x00,
               (VOS_SIZE_T)(sizeof(TAF_CALL_APP_SEND_CUSTOM_DIAL_REQ_STRU) - VOS_MSG_HEAD_LENGTH));

    /* VOS */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = WUEPS_PID_AT;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = AT_GetDestPid(clientId, I0_WUEPS_PID_TAF);

    /*  */
    pstMsg->usMsgId    = TAF_CALL_APP_SEND_CUSTOM_DIAL_REQ;
    pstMsg->usClientId = clientId;
    pstMsg->ucOpId     = opId;
    TAF_MEM_CPY_S(&(pstMsg->stCustomDialPara), sizeof(pstMsg->stCustomDialPara), pstCustomDialPara, sizeof(pstMsg->stCustomDialPara));

    /* VOS */
    (VOS_VOID)PS_SEND_MSG(WUEPS_PID_AT, pstMsg);

    return VOS_TRUE;
}



VOS_UINT32  TAF_XCALL_SendContinuousDtmf(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    TAF_CALL_CONT_DTMF_PARA_STRU       *pstSndContDTMFPara
)
{
    TAF_CALL_CONT_DTMF_REQ_MSG_STRU *pstMsg = VOS_NULL_PTR;
    pstMsg = (TAF_CALL_CONT_DTMF_REQ_MSG_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_AT,
                                              sizeof(TAF_CALL_CONT_DTMF_REQ_MSG_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        AT_ERR_LOG("TAF_XCALL_SendContinuousDtmf: Failed to alloc VOS message.");
        return VOS_ERR;
    }

    TAF_MEM_SET_S((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,
               (VOS_SIZE_T)(sizeof(TAF_CALL_CONT_DTMF_REQ_MSG_STRU) - VOS_MSG_HEAD_LENGTH),
                0x00,
               (VOS_SIZE_T)(sizeof(TAF_CALL_CONT_DTMF_REQ_MSG_STRU) - VOS_MSG_HEAD_LENGTH));

    /* fill in VOS_MSG_HEAD */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = WUEPS_PID_AT;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = AT_GetDestPid(clientId, I0_WUEPS_PID_TAF);

    /* fill in message content */
    pstMsg->usMsgId    = TAF_CALL_APP_SEND_CONT_DTMF_REQ;
    pstMsg->usClientId = clientId;
    pstMsg->ucOpId     = opId;
    TAF_MEM_CPY_S(&(pstMsg->stContDTMFPara), sizeof(pstMsg->stContDTMFPara), pstSndContDTMFPara, sizeof(TAF_CALL_CONT_DTMF_PARA_STRU));

    /* Send VOS message */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_AT, pstMsg))
    {
        AT_ERR_LOG("TAF_XCALL_SendContinuousDtmf: Send TAF_CALL_APP_SEND_CONT_DTMF_REQ Message Fail");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
     : TAF_XCALL_SendCclpr
   : APPTAFClpr
   : clientId              - Client ID
             opId                  - 
             ucCallId               - id
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 2015820
           : f279542
       : 
*****************************************************************************/
VOS_UINT32  TAF_XCALL_SendCclpr(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    VOS_UINT8                           ucCallId
)
{
    TAF_CALL_SND_CCLPR_REQ_MSG_STRU *pstMsg =
        (TAF_CALL_SND_CCLPR_REQ_MSG_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_AT,
                                              sizeof(TAF_CALL_SND_CCLPR_REQ_MSG_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        AT_ERR_LOG("TAF_XCALL_SendCclpr: Failed to alloc VOS message.");
        return VOS_ERR;
    }

    TAF_MEM_SET_S((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,
               (VOS_SIZE_T)(sizeof(TAF_CALL_SND_CCLPR_REQ_MSG_STRU) - VOS_MSG_HEAD_LENGTH),
                0x00,
               (VOS_SIZE_T)(sizeof(TAF_CALL_SND_CCLPR_REQ_MSG_STRU) - VOS_MSG_HEAD_LENGTH));

    /* VOS */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = WUEPS_PID_AT;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = AT_GetDestPid(clientId, I0_WUEPS_PID_TAF);

    /*  */
    pstMsg->usMsgId    = TAF_CALL_APP_SEND_CCLPR_REQ;
    pstMsg->usClientId = clientId;
    pstMsg->ucOpId     = opId;
    pstMsg->ucCallId   = ucCallId;

    /* VOSTAF_CALL_APP_SEND_CCLPR_REQ */
    (VOS_VOID)PS_SEND_MSG(WUEPS_PID_AT, pstMsg);

    return VOS_OK;
}

/*****************************************************************************
     : TAF_XCALL_SndEncryptCall
   : xcallAT
   : VOS_UINT32                                              ulModuleId,
             MN_CLIENT_ID_T                                          usClientId,
             MN_OPERATION_ID_T                                       opId,
             TAF_CALL_APP_ENCRYPT_VOICE_TYPE_ENUM_UINT32             enEccVoiceType, 
             MN_CALL_CALLED_NUM_STRU                                *pstDialNumber   
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 20151022
           : y00322978
       : 

*****************************************************************************/
VOS_UINT32 TAF_XCALL_SendEncryptCall(
    VOS_UINT32                                              ulModuleId,
    MN_CLIENT_ID_T                                          usClientId,
    MN_OPERATION_ID_T                                       opId,
    VOS_UINT32                                              ulEccVoiceType,
    TAF_ECC_CALL_BCD_NUM_STRU                              *pstDialNumber
)
{

    TAF_CALL_APP_ENCRYPT_VOICE_REQ_STRU                    *pstEncryptVoiceReq;
    VOS_UINT32                                              ulReceiverPid;
    VOS_UINT32                                              ulSenderPid;

    ulReceiverPid      = AT_GetDestPid(usClientId, WUEPS_PID_TAF);
    ulSenderPid        = AT_GetDestPid(usClientId, WUEPS_PID_TAF);

    pstEncryptVoiceReq = (TAF_CALL_APP_ENCRYPT_VOICE_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(ulSenderPid,
                                          sizeof(TAF_CALL_APP_ENCRYPT_VOICE_REQ_STRU));
    if (VOS_NULL_PTR == pstEncryptVoiceReq)
    {
        AT_ERR_LOG("TAF_XCALL_SndEncryptCall: Failed to alloc VOS message.");
        return VOS_ERR;
    }

    TAF_MEM_SET_S((VOS_INT8*)pstEncryptVoiceReq + VOS_MSG_HEAD_LENGTH,
               (VOS_SIZE_T)(sizeof(TAF_CALL_APP_ENCRYPT_VOICE_REQ_STRU) - VOS_MSG_HEAD_LENGTH),
                0x00,
               (VOS_SIZE_T)(sizeof(TAF_CALL_APP_ENCRYPT_VOICE_REQ_STRU) - VOS_MSG_HEAD_LENGTH));

    /* VOS */
    pstEncryptVoiceReq->ulSenderCpuId                       = VOS_LOCAL_CPUID;
    pstEncryptVoiceReq->ulSenderPid                         = ulSenderPid;
    pstEncryptVoiceReq->ulReceiverCpuId                     = VOS_LOCAL_CPUID;
    pstEncryptVoiceReq->ulReceiverPid                       = ulReceiverPid;
    pstEncryptVoiceReq->ulLength                            = sizeof(TAF_CALL_APP_ENCRYPT_VOICE_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    /*  */
    pstEncryptVoiceReq->enMsgName                           = ID_TAF_CALL_APP_ENCRYPT_VOICE_REQ;
    pstEncryptVoiceReq->stCtrl.usClientId                   = usClientId;
    pstEncryptVoiceReq->stCtrl.ucOpId                       = opId;
    pstEncryptVoiceReq->stCtrl.ulModuleId                   = ulModuleId;
    pstEncryptVoiceReq->enEccVoiceType                      = ulEccVoiceType;
    TAF_MEM_CPY_S(&pstEncryptVoiceReq->stDialNumber, (VOS_UINT32)sizeof(pstEncryptVoiceReq->stDialNumber), pstDialNumber, (VOS_UINT32)sizeof(TAF_ECC_CALL_BCD_NUM_STRU));

    /* VOSID_TAF_CALL_APP_ENCRYPT_VOICE_REQ */
	/*lint -e830 -e516 */
    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstEncryptVoiceReq);

    return VOS_OK;
}

/*****************************************************************************
     : TAF_XCALL_SndEccCtrl
   : 
   : VOS_UINT32                                              ulModuleId,
             MN_CLIENT_ID_T                                          usClientId,
             MN_OPERATION_ID_T                                       opId,
             TAF_CALL_REMOTE_CTRL_APP_TYPE_ENUM_UINT32               ulRemoteCtrlEvtType,
             TAF_CALL_REMOTE_CTRL_APP_RESULT_ENUM_UINT32             ulResult            
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 20151022
           : y00322978
       : 

*****************************************************************************/
VOS_UINT32 TAF_XCALL_SendEccCtrl(
    VOS_UINT32                                              ulModuleId,
    MN_CLIENT_ID_T                                          usClientId,
    MN_OPERATION_ID_T                                       opId,
    VOS_UINT32                                              ulRemoteCtrlEvtType,
    VOS_UINT32                                              ulResult

)
{
    TAF_CALL_APP_REMOTE_CTRL_ANSWER_REQ_STRU               *pstEccRemoteCtrlAnsReq;
    VOS_UINT32                                              ulReceiverPid;
    VOS_UINT32                                              ulSenderPid;

    ulReceiverPid          = AT_GetDestPid(usClientId, WUEPS_PID_TAF);
    ulSenderPid            = AT_GetDestPid(usClientId, WUEPS_PID_TAF);

    pstEccRemoteCtrlAnsReq = (TAF_CALL_APP_REMOTE_CTRL_ANSWER_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(ulSenderPid,
                                          sizeof(TAF_CALL_APP_REMOTE_CTRL_ANSWER_REQ_STRU));
    if (VOS_NULL_PTR == pstEccRemoteCtrlAnsReq)
    {
        AT_ERR_LOG("TAF_XCALL_SndEccCtrl: Failed to alloc VOS message.");
        return VOS_ERR;
    }

    TAF_MEM_SET_S((VOS_INT8*)pstEccRemoteCtrlAnsReq + VOS_MSG_HEAD_LENGTH,
               (VOS_SIZE_T)(sizeof(TAF_CALL_APP_REMOTE_CTRL_ANSWER_REQ_STRU) - VOS_MSG_HEAD_LENGTH),
                0x00,
               (VOS_SIZE_T)(sizeof(TAF_CALL_APP_REMOTE_CTRL_ANSWER_REQ_STRU) - VOS_MSG_HEAD_LENGTH));

    /* VOS */
    pstEccRemoteCtrlAnsReq->ulSenderCpuId                   = VOS_LOCAL_CPUID;
    pstEccRemoteCtrlAnsReq->ulSenderPid                     = ulSenderPid;
    pstEccRemoteCtrlAnsReq->ulReceiverCpuId                 = VOS_LOCAL_CPUID;
    pstEccRemoteCtrlAnsReq->ulReceiverPid                   = ulReceiverPid;
    pstEccRemoteCtrlAnsReq->ulLength                        = sizeof(TAF_CALL_APP_REMOTE_CTRL_ANSWER_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    /*  */
    pstEccRemoteCtrlAnsReq->enMsgName                       = ID_TAF_CALL_APP_REMOTE_CTRL_ANSWER_REQ;
    pstEccRemoteCtrlAnsReq->stCtrl.usClientId               = usClientId;
    pstEccRemoteCtrlAnsReq->stCtrl.ucOpId                   = opId;
    pstEccRemoteCtrlAnsReq->stCtrl.ulModuleId               = ulModuleId;
    pstEccRemoteCtrlAnsReq->enRemoteCtrlEvtType             = ulRemoteCtrlEvtType;
    pstEccRemoteCtrlAnsReq->enResult                        = ulResult;

    /* VOSID_TAF_CALL_APP_REMOTE_CTRL_ANSWER_REQ */
    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstEccRemoteCtrlAnsReq);

    return VOS_OK;
}

/*****************************************************************************
     : TAF_XCALL_SetEccCap
   : modem
   : VOS_UINT32                                              ulModuleId,
             MN_CLIENT_ID_T                                          usClientId,
             MN_OPERATION_ID_T                                       opId,
             TAF_CALL_APP_ECC_SRV_CAP_ENUM_UINT32                    ulEccSrvCap,   ()
             TAF_CALL_APP_ECC_SRV_STATUS_ENUM_UINT32                 ulEccSrvStatus ()
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 20151022
           : y00322978
       : 

*****************************************************************************/
VOS_UINT32 TAF_XCALL_SetEccCap(
    VOS_UINT32                                              ulModuleId,
    MN_CLIENT_ID_T                                          usClientId,
    MN_OPERATION_ID_T                                       opId,
    VOS_UINT32                                              ulEccSrvCap,
    VOS_UINT32                                              ulEccSrvStatus
)
{
    TAF_CALL_APP_ECC_SRV_CAP_CFG_REQ_STRU                  *pstEccSrvCapReq;
    VOS_UINT32                                              ulReceiverPid;
    VOS_UINT32                                              ulSenderPid;

    ulReceiverPid   = AT_GetDestPid(usClientId, WUEPS_PID_TAF);
    ulSenderPid     = AT_GetDestPid(usClientId, WUEPS_PID_TAF);

    pstEccSrvCapReq = (TAF_CALL_APP_ECC_SRV_CAP_CFG_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(ulSenderPid,
                                          sizeof(TAF_CALL_APP_ECC_SRV_CAP_CFG_REQ_STRU));
    if (VOS_NULL_PTR == pstEccSrvCapReq)
    {
        AT_ERR_LOG("TAF_XCALL_SetEccCap: Failed to alloc VOS message.");
        return VOS_ERR;
    }

    TAF_MEM_SET_S((VOS_INT8*)pstEccSrvCapReq + VOS_MSG_HEAD_LENGTH,
               (VOS_SIZE_T)(sizeof(TAF_CALL_APP_ECC_SRV_CAP_CFG_REQ_STRU) - VOS_MSG_HEAD_LENGTH),
                0x00,
               (VOS_SIZE_T)(sizeof(TAF_CALL_APP_ECC_SRV_CAP_CFG_REQ_STRU) - VOS_MSG_HEAD_LENGTH));

    /* VOS */
    pstEccSrvCapReq->ulSenderCpuId                          = VOS_LOCAL_CPUID;
    pstEccSrvCapReq->ulSenderPid                            = ulSenderPid;
    pstEccSrvCapReq->ulReceiverCpuId                        = VOS_LOCAL_CPUID;
    pstEccSrvCapReq->ulReceiverPid                          = ulReceiverPid;
    pstEccSrvCapReq->ulLength                               = sizeof(TAF_CALL_APP_ECC_SRV_CAP_CFG_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    /*  */
    pstEccSrvCapReq->enMsgName                              = ID_TAF_CALL_APP_ECC_SRV_CAP_CFG_REQ;
    pstEccSrvCapReq->stCtrl.usClientId                      = usClientId;
    pstEccSrvCapReq->stCtrl.ucOpId                          = opId;
    pstEccSrvCapReq->stCtrl.ulModuleId                      = ulModuleId;
    pstEccSrvCapReq->enEccSrvCap                            = ulEccSrvCap;
    pstEccSrvCapReq->enEccSrvStatus                         = ulEccSrvStatus;

    /* VOSID_TAF_CALL_APP_ECC_SRV_CAP_CFG_REQ */
    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstEccSrvCapReq);

    return VOS_OK;
}
/*****************************************************************************
     : TAF_XCALL_QryEncryptCallCap
   : modem 
   : VOS_UINT32                                              ulModuleId,
             MN_CLIENT_ID_T                                          usClientId,
             MN_OPERATION_ID_T                                       opId
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 20151023
           : y00322978
       : 

*****************************************************************************/
VOS_UINT32 TAF_XCALL_QryEncryptCallCap(
    VOS_UINT32                                              ulModuleId,
    MN_CLIENT_ID_T                                          usClientId,
    MN_OPERATION_ID_T                                       opId
)
{
    TAF_CALL_APP_ECC_SRV_CAP_QRY_REQ_STRU                  *pstQryEccCapReq;
    VOS_UINT32                                              ulReceiverPid;
    VOS_UINT32                                              ulSenderPid;

    ulReceiverPid   = AT_GetDestPid(usClientId, WUEPS_PID_TAF);
    ulSenderPid     = AT_GetDestPid(usClientId, WUEPS_PID_TAF);

    pstQryEccCapReq = (TAF_CALL_APP_ECC_SRV_CAP_QRY_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(ulSenderPid,
                                          sizeof(TAF_CALL_APP_ECC_SRV_CAP_QRY_REQ_STRU));
    if (VOS_NULL_PTR == pstQryEccCapReq)
    {
        AT_ERR_LOG("TAF_XCALL_QryEncryptCallCap: Failed to alloc VOS message.");
        return VOS_ERR;
    }

    TAF_MEM_SET_S((VOS_INT8*)pstQryEccCapReq + VOS_MSG_HEAD_LENGTH,
               (VOS_SIZE_T)(sizeof(TAF_CALL_APP_ECC_SRV_CAP_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH),
                0x00,
               (VOS_SIZE_T)(sizeof(TAF_CALL_APP_ECC_SRV_CAP_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH));

    /* VOS */
    pstQryEccCapReq->ulSenderCpuId                        = VOS_LOCAL_CPUID;
    pstQryEccCapReq->ulSenderPid                          = ulSenderPid;
    pstQryEccCapReq->ulReceiverCpuId                      = VOS_LOCAL_CPUID;
    pstQryEccCapReq->ulReceiverPid                        = ulReceiverPid;
    pstQryEccCapReq->ulLength                             = sizeof(TAF_CALL_APP_ECC_SRV_CAP_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH;


    /*  */
    pstQryEccCapReq->enMsgName                            = ID_TAF_CALL_APP_ECC_SRV_CAP_QRY_REQ;
    pstQryEccCapReq->stCtrl.usClientId                    = usClientId;
    pstQryEccCapReq->stCtrl.ucOpId                        = opId;
    pstQryEccCapReq->stCtrl.ulModuleId                    = ulModuleId;

    /* VOSID_TAF_CALL_APP_ECC_SRV_CAP_QRY_REQ */
    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstQryEccCapReq);

    return VOS_OK;
}



/*****************************************************************************
     : TAF_XCALL_SetPrivacyModePreferred
   : Privacy mode
   : VOS_UINT32                                              ulModuleId,
             MN_CLIENT_ID_T                                          usClientId,
             MN_OPERATION_ID_T                                       opId,
             VOS_UINT32                                              ulPrivacyMode

   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 20151222
           : y00245242
       : 

*****************************************************************************/
VOS_UINT32 TAF_XCALL_SetPrivacyModePreferred(
    VOS_UINT32                                              ulModuleId,
    MN_CLIENT_ID_T                                          usClientId,
    MN_OPERATION_ID_T                                       opId,
    VOS_UINT32                                              ulPrivacyMode
)
{
    TAF_CALL_APP_PRIVACY_MODE_SET_REQ_STRU                 *pstPrivacyModeReq = VOS_NULL_PTR;
    VOS_UINT32                                              ulReceiverPid;
    VOS_UINT32                                              ulSenderPid;

    ulReceiverPid        = AT_GetDestPid(usClientId, WUEPS_PID_TAF);
    ulSenderPid          = AT_GetDestPid(usClientId, WUEPS_PID_TAF);


    pstPrivacyModeReq = (TAF_CALL_APP_PRIVACY_MODE_SET_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(ulSenderPid,
                                                                                               sizeof(TAF_CALL_APP_PRIVACY_MODE_SET_REQ_STRU));
    if (VOS_NULL_PTR == pstPrivacyModeReq)
    {
        AT_ERR_LOG("TAF_XCALL_SetPrivacyModePreferred: Failed to alloc VOS message.");
        return VOS_ERR;
    }

    TAF_MEM_SET_S((VOS_INT8*)pstPrivacyModeReq + VOS_MSG_HEAD_LENGTH,
               (VOS_SIZE_T)(sizeof(TAF_CALL_APP_PRIVACY_MODE_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH),
                0x00,
               (VOS_SIZE_T)(sizeof(TAF_CALL_APP_PRIVACY_MODE_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH));


    /* VOS */
    pstPrivacyModeReq->ulSenderCpuId                        = VOS_LOCAL_CPUID;
    pstPrivacyModeReq->ulSenderPid                          = ulSenderPid;
    pstPrivacyModeReq->ulReceiverCpuId                      = VOS_LOCAL_CPUID;
    pstPrivacyModeReq->ulReceiverPid                        = ulReceiverPid;
    pstPrivacyModeReq->ulLength                             = sizeof(TAF_CALL_APP_PRIVACY_MODE_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    /*  */
    pstPrivacyModeReq->enMsgName                            = ID_TAF_CALL_APP_PRIVACY_MODE_SET_REQ;
    pstPrivacyModeReq->stCtrl.usClientId                    = usClientId;
    pstPrivacyModeReq->stCtrl.ucOpId                        = opId;
    pstPrivacyModeReq->stCtrl.ulModuleId                    = ulModuleId;

    pstPrivacyModeReq->enPrivacyMode                        = (TAF_CALL_PRIVACY_MODE_ENUM_UINT8)ulPrivacyMode;

    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstPrivacyModeReq);

    return VOS_OK;
}

/*****************************************************************************
     : TAF_XCALL_QryPrivacyModePreferred
   : Privacy mode
   : VOS_UINT32                                              ulModuleId,
             MN_CLIENT_ID_T                                          usClientId,
             MN_OPERATION_ID_T                                       opId

   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 20151222
           : y00245242
       : 

*****************************************************************************/
VOS_UINT32 TAF_XCALL_QryPrivacyModePreferred(
    VOS_UINT32                                              ulModuleId,
    MN_CLIENT_ID_T                                          usClientId,
    MN_OPERATION_ID_T                                       opId
)
{
    TAF_CALL_APP_PRIVACY_MODE_QRY_REQ_STRU                 *pstPrivacyModeReq = VOS_NULL_PTR;
    VOS_UINT32                                              ulReceiverPid;
    VOS_UINT32                                              ulSenderPid;

    ulReceiverPid        = AT_GetDestPid(usClientId, WUEPS_PID_TAF);
    ulSenderPid          = AT_GetDestPid(usClientId, WUEPS_PID_TAF);


    pstPrivacyModeReq = (TAF_CALL_APP_PRIVACY_MODE_QRY_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(ulSenderPid,
                                                                                               sizeof(TAF_CALL_APP_PRIVACY_MODE_QRY_REQ_STRU));
    if (VOS_NULL_PTR == pstPrivacyModeReq)
    {
        AT_ERR_LOG("TAF_XCALL_QryPrivacyModePreferred: Failed to alloc VOS message.");
        return VOS_ERR;
    }

    TAF_MEM_SET_S((VOS_INT8*)pstPrivacyModeReq + VOS_MSG_HEAD_LENGTH,
               (VOS_SIZE_T)(sizeof(TAF_CALL_APP_PRIVACY_MODE_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH),
                0x00,
               (VOS_SIZE_T)(sizeof(TAF_CALL_APP_PRIVACY_MODE_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH));


    /* VOS */
    pstPrivacyModeReq->ulSenderCpuId                        = VOS_LOCAL_CPUID;
    pstPrivacyModeReq->ulSenderPid                          = ulSenderPid;
    pstPrivacyModeReq->ulReceiverCpuId                      = VOS_LOCAL_CPUID;
    pstPrivacyModeReq->ulReceiverPid                        = ulReceiverPid;
    pstPrivacyModeReq->ulLength                             = sizeof(TAF_CALL_APP_PRIVACY_MODE_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    /*  */
    pstPrivacyModeReq->enMsgName                            = ID_TAF_CALL_APP_PRIVACY_MODE_QRY_REQ;
    pstPrivacyModeReq->stCtrl.usClientId                    = usClientId;
    pstPrivacyModeReq->stCtrl.ucOpId                        = opId;
    pstPrivacyModeReq->stCtrl.ulModuleId                    = ulModuleId;

    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstPrivacyModeReq);

    return VOS_OK;
}

/*****************************************************************************
     : TAF_CALL_QryCnap
   : ^CNAP
   : VOS_UINT32                              ulModuleId
             MN_CLIENT_ID_T                          usClientId
             MN_OPERATION_ID_T                       opId
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 20161116
           : c00380008
       : 

*****************************************************************************/
VOS_UINT32 TAF_CALL_QryCnap(
    VOS_UINT32                              ulModuleId,
    MN_CLIENT_ID_T                          usClientId,
    MN_OPERATION_ID_T                       opId
)
{
    TAF_CALL_APP_CNAP_QRY_REQ_STRU         *pstCnapQryReq;
    VOS_UINT32                              ulReceiverPid;
    VOS_UINT32                              ulSenderPid;

    ulReceiverPid     = AT_GetDestPid(usClientId, WUEPS_PID_TAF);
    ulSenderPid       = AT_GetDestPid(usClientId, WUEPS_PID_TAF);

    pstCnapQryReq = (TAF_CALL_APP_CNAP_QRY_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(ulSenderPid,
                                sizeof(TAF_CALL_APP_CNAP_QRY_REQ_STRU));

    if (VOS_NULL_PTR == pstCnapQryReq)
    {
        AT_ERR_LOG("TAF_CALL_QryCnapPara: Failed to alloc VOS message.");
        return VOS_ERR;
    }

    TAF_MEM_SET_S((VOS_INT8 *)pstCnapQryReq + VOS_MSG_HEAD_LENGTH,
                  (VOS_SIZE_T)(sizeof(TAF_CALL_APP_CNAP_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH),
                  0x00,
                  (VOS_SIZE_T)(sizeof(TAF_CALL_APP_CNAP_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH));

    /* VOS */
    pstCnapQryReq->ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstCnapQryReq->ulSenderPid      = ulSenderPid;
    pstCnapQryReq->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstCnapQryReq->ulReceiverPid    = ulReceiverPid;
    pstCnapQryReq->ulLength         = sizeof(TAF_CALL_APP_CNAP_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    /*  */
    pstCnapQryReq->enMsgName            = ID_TAF_CALL_APP_CNAP_QRY_REQ;
    pstCnapQryReq->stCtrl.usClientId    = usClientId;
    pstCnapQryReq->stCtrl.ucOpId        = opId;
    pstCnapQryReq->stCtrl.ulModuleId    = ulModuleId;

    /* VOSID_TAF_CALL_APP_CNAP_QRY_REQ */
    (VOS_VOID)PS_SEND_MSG(ulSenderPid, pstCnapQryReq);

    return VOS_OK;
}

