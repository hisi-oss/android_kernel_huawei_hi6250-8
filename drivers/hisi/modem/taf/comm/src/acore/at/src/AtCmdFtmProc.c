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
#include "AtCmdFtmProc.h"
#include "ATCmdProc.h"
#include "AtMtaInterface.h"

/* Added by z60575 for LOG35_TL, 2013-8-9 begin */
#include "msp_diag.h"
/* Added by z60575 for LOG35_TL, 2013-8-9 end */

#include "AtTestParaCmd.h"


/*****************************************************************************
    .C
*****************************************************************************/
#define    THIS_FILE_ID                 PS_FILE_ID_AT_CMD_FTM_PROC_C

/*****************************************************************************
  2 
*****************************************************************************/


/*****************************************************************************
  3 
*****************************************************************************/
/*****************************************************************************
     : At_SetLogPortPara
   : ^LOGPORT
   : VOS_UINT8 ucIndex
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 2013620
           : l60609
       : 
  2.       : 201389
           : z60575
       : LOG35_TLTL
*****************************************************************************/
VOS_UINT32 At_SetLogPortPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRslt;
    VOS_UINT32                          ulOmLogPort;

    /*  */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    /*  */
    if ((2 < gucAtParaIndex) || (0 == gucAtParaIndex))
    {
        return AT_ERROR;
    }

    if (AT_LOG_PORT_USB == gastAtParaList[0].ulParaValue)
    {
        ulOmLogPort = CPM_OM_PORT_TYPE_USB;
    }
    else
    {
        ulOmLogPort = CPM_OM_PORT_TYPE_VCOM;
    }

    /*  */
    if (1 == gucAtParaIndex)
    {
        gastAtParaList[1].ulParaValue = VOS_TRUE;
    }

    /* add print by cuijunqiang, for socp timer set, 2016.01.21 */
    vos_printf("[socp set timer] : at port %d, log port %d, param %d.\n",
        ucIndex, ulOmLogPort, gastAtParaList[1].ulParaValue);

    /* OM */
    ulRslt = PPM_LogPortSwitch(ulOmLogPort, gastAtParaList[1].ulParaValue);

    if (VOS_OK == ulRslt)
    {
        return AT_OK;
    }
    else
    {
        return AT_ERROR;
    }
}

/*****************************************************************************
     : At_QryLogPortPara
   : ^LOGPORT
   : VOS_UINT8 ucIndex
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 2013620
           : l60609
       : 
  2.       : 201389
           : z60575
       : LOG35_TLTL
*****************************************************************************/
VOS_UINT32 At_QryLogPortPara(VOS_UINT8 ucIndex)
{
    VOS_UINT16                          usLength;
    VOS_UINT32                          ulOmLogPort;
    VOS_UINT32                          ulAtLogPort;
    VOS_UINT32                          ulRslt;

    usLength                            = 0;
    ulOmLogPort                         = AT_LOG_PORT_USB;

    ulRslt = PPM_QueryLogPort(&ulOmLogPort);

    if (VOS_OK != ulRslt)
    {
        return AT_ERROR;
    }

    if (COMM_LOG_PORT_USB == ulOmLogPort)
    {
        ulAtLogPort = AT_LOG_PORT_USB;
    }
    else
    {
        ulAtLogPort = AT_LOG_PORT_VCOM;
    }

    usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR*)pgucAtSndCodeAddr,
                                       (VOS_CHAR*)pgucAtSndCodeAddr,
                                       "%s: ",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR*)pgucAtSndCodeAddr,
                                       (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                       "%d",
                                       ulAtLogPort);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}

/*****************************************************************************
     : At_SetDpdtTestFlagPara
   : ^DPDTTEST
             :^DPDTTEST=<RatMode>,<Flag>
   : ucIndex - 
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 20140404
           : g00261581
       : 

*****************************************************************************/
VOS_UINT32 At_SetDpdtTestFlagPara(VOS_UINT8 ucIndex)
{
    AT_MTA_SET_DPDTTEST_FLAG_REQ_STRU   stAtCmd;
    VOS_UINT32                          ulRst;

    /*  */
    if (2 != gucAtParaIndex)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ATMTA */
    TAF_MEM_SET_S(&stAtCmd, sizeof(stAtCmd), 0x00, sizeof(AT_MTA_SET_DPDTTEST_FLAG_REQ_STRU));
    stAtCmd.enRatMode = (AT_MTA_CMD_RATMODE_ENUM_UINT8)gastAtParaList[0].ulParaValue;
    stAtCmd.ucFlag    = (VOS_UINT8)gastAtParaList[1].ulParaValue;

    /* C */
    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   ID_AT_MTA_SET_DPDTTEST_FLAG_REQ,
                                   &stAtCmd,
                                   sizeof(AT_MTA_SET_DPDTTEST_FLAG_REQ_STRU),
                                   I0_UEPS_PID_MTA);

    if (AT_SUCCESS == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_DPDTTEST_SET;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}

/*****************************************************************************
     : At_SetDpdtPara
   : ^DPDT
             :^DPDT=<RatMode>,<DpdtValue>
   : ucIndex - 
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 20140404
           : g00261581
       : 

*****************************************************************************/
VOS_UINT32 At_SetDpdtPara(VOS_UINT8 ucIndex)
{
    AT_MTA_SET_DPDT_VALUE_REQ_STRU      stAtCmd;
    VOS_UINT32                          ulRst;

    /*  */
    if (2 != gucAtParaIndex)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ATMTA */
    TAF_MEM_SET_S(&stAtCmd, sizeof(stAtCmd), 0x00, sizeof(AT_MTA_SET_DPDT_VALUE_REQ_STRU));
    stAtCmd.enRatMode   = (AT_MTA_CMD_RATMODE_ENUM_UINT8)gastAtParaList[0].ulParaValue;
    stAtCmd.ulDpdtValue = gastAtParaList[1].ulParaValue;

    /* C */
    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   ID_AT_MTA_SET_DPDT_VALUE_REQ,
                                   &stAtCmd,
                                   sizeof(AT_MTA_SET_DPDT_VALUE_REQ_STRU),
                                   I0_UEPS_PID_MTA);

    if (AT_SUCCESS == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_DPDT_SET;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }

}

/*****************************************************************************
     : At_SetQryDpdtPara
   : ^DPDTQRY
             :^DPDTQRY=<RatMode>
   : ucIndex - 
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 20140404
           : g00261581
       : 

*****************************************************************************/
VOS_UINT32 At_SetQryDpdtPara(VOS_UINT8 ucIndex)
{
    AT_MTA_QRY_DPDT_VALUE_REQ_STRU      stAtCmd;
    VOS_UINT32                          ulRst;

    /*  */
    if (1 != gucAtParaIndex)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ATMTA */
    TAF_MEM_SET_S(&stAtCmd, sizeof(stAtCmd), 0x00, sizeof(AT_MTA_QRY_DPDT_VALUE_REQ_STRU));
    stAtCmd.enRatMode = (AT_MTA_CMD_RATMODE_ENUM_UINT8)gastAtParaList[0].ulParaValue;

    /* C */
    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   ID_AT_MTA_QRY_DPDT_VALUE_REQ,
                                   &stAtCmd,
                                   sizeof(AT_MTA_QRY_DPDT_VALUE_REQ_STRU),
                                   I0_UEPS_PID_MTA);

    if (AT_SUCCESS == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_DPDTQRY_SET;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}

/*****************************************************************************
     : AT_RcvMtaSetDpdtTestFlagCnf
   : ATMTASet Dpdt Flag
   : pstMsg -- 
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 20140409
           : g00261581
       : 
*****************************************************************************/
VOS_UINT32 AT_RcvMtaSetDpdtTestFlagCnf(VOS_VOID *pMsg)
{
    /*  */
    AT_MTA_MSG_STRU                    *pstMtaMsg         = VOS_NULL_PTR;
    MTA_AT_SET_DPDTTEST_FLAG_CNF_STRU  *pstSetDpdtFlagCnf = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    /*  */
    ucIndex   = 0;
    pstMtaMsg = (AT_MTA_MSG_STRU *)pMsg;
    pstSetDpdtFlagCnf = (MTA_AT_SET_DPDTTEST_FLAG_CNF_STRU *)pstMtaMsg->aucContent;

    /* ClientIducIndex */
    if (AT_FAILURE == At_ClientIdToUserId(pstMtaMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaSetDpdtTestFlagCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaSetDpdtTestFlagCnf: WARNING:AT_BROADCAST_INDEX!");
        return VOS_ERR;
    }

    /* AT_CMD_DPDTTEST_SET */
    if (AT_CMD_DPDTTEST_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaSetDpdtTestFlagCnf: WARNING:Not AT_CMD_DPDTTEST_SET!");
        return VOS_ERR;
    }

    /* AT */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /*  */
    if (MTA_AT_RESULT_NO_ERROR == pstSetDpdtFlagCnf->enResult)
    {
        ulResult    = AT_OK;
    }
    else
    {
        ulResult    = AT_ERROR;
    }

    gstAtSendData.usBufLen = 0;

    /* At_FormatResultData */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
     : AT_RcvMtaSetDpdtValueCnf
   : ATMTASet Dpdt Value
   : pstMsg -- 
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 20140409
           : g00261581
       : 
*****************************************************************************/
VOS_UINT32 AT_RcvMtaSetDpdtValueCnf(VOS_VOID *pMsg)
{
    /*  */
    AT_MTA_MSG_STRU                    *pstMtaMsg          = VOS_NULL_PTR;
    MTA_AT_SET_DPDT_VALUE_CNF_STRU     *pstSetDpdtValueCnf = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    /*  */
    ucIndex            = 0;
    pstMtaMsg          = (AT_MTA_MSG_STRU *)pMsg;
    pstSetDpdtValueCnf = (MTA_AT_SET_DPDT_VALUE_CNF_STRU *)pstMtaMsg->aucContent;

    /* ClientIducIndex */
    if (AT_FAILURE == At_ClientIdToUserId(pstMtaMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaSetDpdtValueCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaSetDpdtValueCnf: WARNING:AT_BROADCAST_INDEX!");
        return VOS_ERR;
    }

    /* AT_CMD_DPDT_SET */
    if (AT_CMD_DPDT_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaSetDpdtValueCnf: WARNING:Not AT_CMD_DPDT_SET!");
        return VOS_ERR;
    }

    /* AT */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /*  */
    if (MTA_AT_RESULT_NO_ERROR == pstSetDpdtValueCnf->enResult)
    {
        ulResult    = AT_OK;
    }
    else
    {
        ulResult    = AT_ERROR;
    }

    gstAtSendData.usBufLen = 0;

    /* At_FormatResultData */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
     : AT_RcvMtaQryDpdtValueCnf
   : ATMTAQry Dpdt Value
   : pstMsg -- 
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 20140409
           : g00261581
       : 
*****************************************************************************/
VOS_UINT32 AT_RcvMtaQryDpdtValueCnf(VOS_VOID *pMsg)
{
    /*  */
    AT_MTA_MSG_STRU                    *pstMtaMsg          = VOS_NULL_PTR;
    MTA_AT_QRY_DPDT_VALUE_CNF_STRU     *pstQryDpdtValueCnf = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    /*  */
    ucIndex            = 0;
    pstMtaMsg          = (AT_MTA_MSG_STRU *)pMsg;
    pstQryDpdtValueCnf = (MTA_AT_QRY_DPDT_VALUE_CNF_STRU *)pstMtaMsg->aucContent;

    /* ClientIducIndex */
    if (AT_FAILURE == At_ClientIdToUserId(pstMtaMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaQryDpdtValueCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaQryDpdtValueCnf: WARNING:AT_BROADCAST_INDEX!");
        return VOS_ERR;
    }

    /* AT_CMD_DPDTQRY_SET */
    if (AT_CMD_DPDTQRY_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaQryDpdtValueCnf: WARNING:Not AT_CMD_DPDTQRY_SET!");
        return VOS_ERR;
    }

    /* AT */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /*  */
    if (MTA_AT_RESULT_NO_ERROR == pstQryDpdtValueCnf->enResult)
    {
        ulResult = AT_OK;
        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                            (TAF_CHAR *)pgucAtSndCodeAddr,
                                            (TAF_CHAR *)pgucAtSndCodeAddr,
                                            "^DPDTQRY: %d",
                                            pstQryDpdtValueCnf->ulDpdtValue);
    }
    else
    {
        ulResult = AT_ERROR;
        gstAtSendData.usBufLen = 0;
    }

    /* At_FormatResultData */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
     : At_SetJamDetectPara
   : ^JDETEX
             :^JDETEX=<mode>[,<METHOD>,<NPT>,<UCN>]
   : ucIndex - 
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 20140505
           : g00261581
       : 

*****************************************************************************/
VOS_UINT32 At_SetJamDetectPara(VOS_UINT8 ucIndex)
{
    AT_MTA_SET_JAM_DETECT_REQ_STRU      stAtCmd;
    NV_NAS_JAM_DETECT_CFG_STRU          stNvJamCfg;
    VOS_UINT32                          ulRst;

    /*  */
    if ((gucAtParaIndex < 1) || (gucAtParaIndex > 4))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ATMTA */
    TAF_MEM_SET_S(&stAtCmd, sizeof(stAtCmd), 0x00, sizeof(AT_MTA_SET_JAM_DETECT_REQ_STRU));

    stAtCmd.ucFlag         = (VOS_UINT8)gastAtParaList[0].ulParaValue;
    stAtCmd.ucMethod       = AT_JAM_DETECT_DEFAULT_METHOD;

    if (0 == gastAtParaList[2].usParaLen)
    {
        stAtCmd.ucThreshold    = AT_JAM_DETECT_DEFAULT_THRESHOLD;
    }
    else
    {
        stAtCmd.ucThreshold    = (VOS_UINT8)gastAtParaList[2].ulParaValue;
    }

    if (0 == gastAtParaList[3].usParaLen)
    {
        stAtCmd.ucFreqNum      = AT_JAM_DETECT_DEFAULT_FREQ_NUM;
    }
    else
    {
        stAtCmd.ucFreqNum      = (VOS_UINT8)gastAtParaList[3].ulParaValue;
    }

    if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_JAM_DETECT_CFG, &stNvJamCfg, sizeof(stNvJamCfg)))
    {
        AT_WARN_LOG("At_SetJamDetectPara():en_NV_Item_JAM_DETECT_CFG NV Read Fail!");
        return AT_ERROR;
    }

    /* NV */
    stNvJamCfg.ucMode      = stAtCmd.ucFlag;
    stNvJamCfg.ucMethod    = stAtCmd.ucMethod;
    stNvJamCfg.ucThreshold = stAtCmd.ucThreshold;
    stNvJamCfg.ucFreqNum   = stAtCmd.ucFreqNum;

    if (NV_OK != NV_WriteEx(MODEM_ID_0, en_NV_Item_JAM_DETECT_CFG, &stNvJamCfg, sizeof(stNvJamCfg)))
    {
        AT_WARN_LOG("At_SetJamDetectPara():en_NV_Item_JAM_DETECT_CFG NV Write Fail!");
        return AT_ERROR;
    }

    /* C */
    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   ID_AT_MTA_SET_JAM_DETECT_REQ,
                                   &stAtCmd,
                                   sizeof(AT_MTA_SET_JAM_DETECT_REQ_STRU),
                                   I0_UEPS_PID_MTA);

    if (TAF_SUCCESS == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_JDETEX_SET;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}

/*****************************************************************************
     : At_QryJamDetectPara
   : ^JDETEXJam Detect
   : ucIndex - 
   : 
     : 
   :
   :

       :
  1.       : 201459
           : g00261581
       : 
*****************************************************************************/
VOS_UINT32 At_QryJamDetectPara(VOS_UINT8 ucIndex)
{
    NV_NAS_JAM_DETECT_CFG_STRU          stNvJamDetect;

    TAF_MEM_SET_S(&stNvJamDetect, sizeof(stNvJamDetect), 0x00, sizeof(stNvJamDetect));

    /* NVJam Detect */
    if (NV_OK != NV_ReadEx(MODEM_ID_0,
                           en_NV_Item_JAM_DETECT_CFG,
                           &stNvJamDetect,
                           sizeof(NV_NAS_JAM_DETECT_CFG_STRU)))
    {
        AT_WARN_LOG("At_QryJamDetectPara: NV_ReadEx en_NV_Item_JAM_DETECT_CFG fail!");
        return AT_ERROR;
    }

    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    "%s: %d,%d,%d,%d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    stNvJamDetect.ucMode,
                                                    stNvJamDetect.ucMethod,
                                                    stNvJamDetect.ucThreshold,
                                                    stNvJamDetect.ucFreqNum);

    return AT_OK;
}

/*****************************************************************************
     : AT_RcvMtaSetJamDetectCnf
   : ATMTAJam Detect
   : pstMsg -- 
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 201456
           : g00261581
       : 
*****************************************************************************/
VOS_UINT32 AT_RcvMtaSetJamDetectCnf(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                        *pstRcvMsg;
    MTA_AT_SET_JAM_DETECT_CNF_STRU         *pstSetCnf;
    VOS_UINT32                              ulResult;
    VOS_UINT8                               ucIndex;

    /*  */
    pstRcvMsg    = (AT_MTA_MSG_STRU *)pMsg;
    pstSetCnf    = (MTA_AT_SET_JAM_DETECT_CNF_STRU *)pstRcvMsg->aucContent;
    ulResult     = AT_OK;
    ucIndex      = 0;

    /* clientidindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaSetJamDetectCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaSetJamDetectCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* AT */
    if (AT_CMD_JDETEX_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaSetJamDetectCnf : Current Option is not AT_CMD_JDETEX_SET.");
        return VOS_ERR;
    }

    /* AT */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /*  */
    gstAtSendData.usBufLen = 0;

    if (MTA_AT_RESULT_NO_ERROR != pstSetCnf->enResult)
    {
        ulResult = AT_ERROR;
    }

    /*  */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
     : AT_RcvMtaJamDetectInd
   : ATMTAJam Ind
   : pstMsg -- 
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 201456
           : g00261581
       : 
*****************************************************************************/
VOS_UINT32 AT_RcvMtaJamDetectInd(
    VOS_VOID                           *pMsg
)
{
    VOS_UINT8                           ucIndex;
    AT_MTA_MSG_STRU                    *pstMtaMsg;
    MTA_AT_JAM_DETECT_IND_STRU         *pstJamDetectInd;

    /*  */
    ucIndex             = 0;
    pstMtaMsg           = (AT_MTA_MSG_STRU*)pMsg;
    pstJamDetectInd     = (MTA_AT_JAM_DETECT_IND_STRU*)pstMtaMsg->aucContent;

    /* ClientIducIndex */
    if (AT_FAILURE == At_ClientIdToUserId(pstMtaMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaJamDetectInd: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    gstAtSendData.usBufLen = 0;

    /*  */
    if (MTA_AT_JAM_RESULT_JAM_DISCOVERED == pstJamDetectInd->enJamResult)
    {
        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        "%s^JDET: JAMMED%s",
                                                        gaucAtCrLf,
                                                        gaucAtCrLf);

        At_SendResultData(ucIndex, pgucAtSndCodeAddr, gstAtSendData.usBufLen);
    }

    if (MTA_AT_JAM_RESULT_JAM_DISAPPEARED == pstJamDetectInd->enJamResult)
    {
        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        "%s^JDET: DETECTING%s",
                                                        gaucAtCrLf,
                                                        gaucAtCrLf);

        At_SendResultData(ucIndex, pgucAtSndCodeAddr, gstAtSendData.usBufLen);
    }
    return VOS_OK;
}

/*****************************************************************************
     : AT_SetRatFreqLock
   : ^FREQLOCK
             :^FREQLOCK=<enable>[,<freq>[,<ratMode>[,<band>]]]
   : ucIndex - 
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 20140611
           : g00261581
       : 

*****************************************************************************/
VOS_UINT32 AT_SetRatFreqLock(VOS_UINT8 ucIndex)
{
    AT_MTA_SET_FREQ_LOCK_REQ_STRU       stAtCmd;
    VOS_UINT32                          ulRst;

    /*  */
    if ((gucAtParaIndex < 1) || (gucAtParaIndex > 4))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    TAF_MEM_SET_S(&stAtCmd, sizeof(stAtCmd), 0x00, sizeof(AT_MTA_SET_FREQ_LOCK_REQ_STRU));
    stAtCmd.ucEnableFlg = (VOS_UINT8)gastAtParaList[0].ulParaValue;

    /* Nv, AT_OK */
    if (VOS_FALSE == stAtCmd.ucEnableFlg)
    {
        if (NV_OK != NV_WriteEx(MODEM_ID_0, en_NV_Item_FREQ_LOCK_CFG, &stAtCmd, sizeof(stAtCmd)))
        {
            AT_ERR_LOG("AT_SetRatFreqLock(): en_NV_Item_FREQ_LOCK_CFG NV Write Fail!");
            return AT_ERROR;
        }

        return AT_OK;
    }

    stAtCmd.usLockedFreq = (VOS_UINT16)gastAtParaList[1].ulParaValue;

    /*  */
    if (0 == gastAtParaList[2].usParaLen)
    {
        stAtCmd.enRatMode = AT_MTA_FREQLOCK_RATMODE_WCDMA;
    }
    else
    {
        stAtCmd.enRatMode = (AT_MTA_FREQLOCK_RATMODE_ENUM_UINT8)gastAtParaList[2].ulParaValue;
    }

    /* BAND */
    if (0 == gastAtParaList[3].usParaLen)
    {
        if (AT_MTA_FREQLOCK_RATMODE_GSM == stAtCmd.enRatMode)
        {
            return AT_ERROR;
        }
        stAtCmd.enBand = AT_MTA_GSM_BAND_BUTT;
    }
    else
    {
        stAtCmd.enBand = (AT_MTA_GSM_BAND_ENUM_UINT16)gastAtParaList[3].ulParaValue;
    }

    /* C */
    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   ID_AT_MTA_SET_FREQ_LOCK_REQ,
                                   &stAtCmd,
                                   sizeof(AT_MTA_SET_FREQ_LOCK_REQ_STRU),
                                   I0_UEPS_PID_MTA);

    if (TAF_SUCCESS == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_RATFREQLOCK_SET;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}

/*****************************************************************************
     : AT_RcvMtaSetRatFreqLockCnf
   : ATMTA
   : pstMsg -- 
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 2014612
           : g00261581
       : 
*****************************************************************************/
VOS_UINT32 AT_RcvMtaSetRatFreqLockCnf(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pstRcvMsg;
    MTA_AT_SET_FREQ_LOCK_CNF_STRU      *pstSetCnf;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    /*  */
    pstRcvMsg    = (AT_MTA_MSG_STRU *)pMsg;
    pstSetCnf    = (MTA_AT_SET_FREQ_LOCK_CNF_STRU *)pstRcvMsg->aucContent;
    ucIndex      = 0;
    ulResult     = AT_ERROR;

    /* clientidindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaSetRatFreqLockCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaSetRatFreqLockCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* AT */
    if (AT_CMD_RATFREQLOCK_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaSetRatFreqLockCnf : Current Option is not AT_CMD_RATFREQLOCK_SET.");
        return VOS_ERR;
    }

    /* AT */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /*  */
    gstAtSendData.usBufLen = 0;

    if (MTA_AT_RESULT_NO_ERROR == pstSetCnf->enResult)
    {
        ulResult = AT_OK;
    }

    At_FormatResultData(ucIndex, ulResult);
    return VOS_OK;
}

/*****************************************************************************
     : AT_QryRatFreqLock
   : ^FREQLOCK
   : ucIndex - 
   : 
     : 
   :
   :

       :
  1.       : 2014612
           : g00261581
       : 
*****************************************************************************/
VOS_UINT32 AT_QryRatFreqLock(VOS_UINT8 ucIndex)
{
    TAF_NVIM_FREQ_LOCK_CFG_STRU         stNvFreqLockCfg;

    TAF_MEM_SET_S(&stNvFreqLockCfg, sizeof(stNvFreqLockCfg), 0x00, sizeof(stNvFreqLockCfg));

    /* NVFreq Lock */
    if (NV_OK != NV_ReadEx(MODEM_ID_0,
                           en_NV_Item_FREQ_LOCK_CFG,
                           &stNvFreqLockCfg,
                           sizeof(TAF_NVIM_FREQ_LOCK_CFG_STRU)))
    {
        AT_WARN_LOG("At_QryRatFreqLock: NV_ReadEx en_NV_Item_FREQ_LOCK_CFG fail!");
        return AT_ERROR;
    }

    /* :0 */
    if (VOS_FALSE == stNvFreqLockCfg.ucEnableFlg)
    {
        /*  */
        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        "%s: %d",
                                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                        stNvFreqLockCfg.ucEnableFlg);

        return AT_OK;
    }

    /* GBAND */
    if (TAF_NVIM_RAT_MODE_GSM == stNvFreqLockCfg.enRatMode)
    {
        /*  */
        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        "%s: %d,%d,\"0%d\",\"0%d\"",
                                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                        stNvFreqLockCfg.ucEnableFlg,
                                                        stNvFreqLockCfg.usLockedFreq,
                                                        stNvFreqLockCfg.enRatMode,
                                                        stNvFreqLockCfg.enBand);
    }
    else
    {
        /*  */
        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        "%s: %d,%d,\"0%d\"",
                                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                        stNvFreqLockCfg.ucEnableFlg,
                                                        stNvFreqLockCfg.usLockedFreq,
                                                        stNvFreqLockCfg.enRatMode);
    }

    return AT_OK;
}

/*****************************************************************************
     : AT_SetGFreqLock
   : ^GFREQLOCK
             :^GFREQLOCK =<enable>[,<freq>,<band>]
   : ucIndex - 
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 20140805
           : j00174725
       : 
*****************************************************************************/
VOS_UINT32 AT_SetGFreqLock(VOS_UINT8 ucIndex)
{
    AT_MTA_SET_GSM_FREQLOCK_REQ_STRU    stGFreqLockInfo;
    VOS_UINT32                          ulRst;

    /*  */
    if ((gucAtParaIndex != 1) && (gucAtParaIndex != 3))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /*  */
    TAF_MEM_SET_S(&stGFreqLockInfo, sizeof(stGFreqLockInfo), 0x00, sizeof(AT_MTA_SET_GSM_FREQLOCK_REQ_STRU));

    /*  */
    /*  */
    if (0 == gastAtParaList[0].usParaLen)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    stGFreqLockInfo.enableFlag = (PS_BOOL_ENUM_UINT8)gastAtParaList[0].ulParaValue;

    /*  */
    if (PS_TRUE == stGFreqLockInfo.enableFlag)
    {
        if ( (0 == gastAtParaList[1].usParaLen)
          || (0 == gastAtParaList[2].usParaLen) )
        {
            return AT_CME_INCORRECT_PARAMETERS;
        }
        else
        {
            stGFreqLockInfo.usFreq = (VOS_UINT16)gastAtParaList[1].ulParaValue;
            stGFreqLockInfo.enBand = (AT_MTA_GSM_BAND_ENUM_UINT16)gastAtParaList[2].ulParaValue;
        }
    }

    /* C */
    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   ID_AT_MTA_SET_GSM_FREQLOCK_REQ,
                                   &stGFreqLockInfo,
                                   sizeof(AT_MTA_SET_GSM_FREQLOCK_REQ_STRU),
                                   I0_UEPS_PID_MTA);

    if (TAF_SUCCESS == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_GSM_FREQLOCK_SET;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}

/*****************************************************************************
     : AT_RcvMtaSetGFreqLockCnf
   : ATMTAG
   : pstMsg -- 
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 20140805
           : j00174725
       : 
*****************************************************************************/
VOS_UINT32 AT_RcvMtaSetGFreqLockCnf(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pstRcvMsg;
    MTA_AT_SET_GSM_FREQLOCK_CNF_STRU   *pstSetCnf;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    /*  */
    pstRcvMsg    = (AT_MTA_MSG_STRU *)pMsg;
    pstSetCnf    = (MTA_AT_SET_GSM_FREQLOCK_CNF_STRU *)pstRcvMsg->aucContent;
    ucIndex      = 0;
    ulResult     = AT_ERROR;

    /* clientidindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaSetGFreqLockCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaSetGFreqLockCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* AT */
    if (AT_CMD_GSM_FREQLOCK_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaSetGFreqLockCnf : Current Option is not AT_CMD_GSM_FREQLOCK_SET.");
        return VOS_ERR;
    }

    /* AT */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /*  */
    gstAtSendData.usBufLen = 0;

    if (MTA_AT_RESULT_NO_ERROR == pstSetCnf->enResult)
    {
        ulResult = AT_OK;
    }

    At_FormatResultData(ucIndex, ulResult);
    return VOS_OK;
}


/*****************************************************************************
     : AT_NetMonFmtPlmnId
   : PLMN ID 
   : ulMcc -- Mcc
             ulMnc -- Mnc
   : pstrPlmn  -- PLMN
             pusLength --PLMN
     : VOS_VOID
   :
   :

        :
  1.       : 20151019
           : wx270776
       : 
*****************************************************************************/
VOS_VOID AT_NetMonFmtPlmnId(
    VOS_UINT32                          ulMcc,
    VOS_UINT32                          ulMnc,
    VOS_CHAR                           *pstrPlmn,
    VOS_UINT16                         *pusLength
)
{
    VOS_UINT32                          ulMaxLength;
    VOS_UINT32                          ulLength;

    ulLength                          = 0;
    ulMaxLength                       = AT_NETMON_PLMN_STRING_MAX_LENGTH;

    /* MCC */
    ulLength += VOS_nsprintf_s( (VOS_CHAR *)pstrPlmn,
                              (VOS_UINT32)ulMaxLength,
                              (VOS_UINT32)ulMaxLength,
                              "%X%X%X",
                              (ulMcc & 0x0f),
                              (ulMcc & 0x0f00)>>8,
                              (ulMcc & 0x0f0000)>>16 );


    /* MNC */
    if (0x0f0000 == (ulMnc & 0x0f0000))
    {
        ulLength += VOS_nsprintf_s( (VOS_CHAR *)(pstrPlmn + ulLength),
                                  (VOS_UINT32)ulMaxLength - ulLength,
                                  (VOS_UINT32)ulMaxLength - ulLength,
                                  ",%X%X",
                                  (ulMnc & 0x0f),
                                  (ulMnc & 0x0f00)>>8 );
    }
    else
    {
        ulLength += VOS_nsprintf_s( (VOS_CHAR *)(pstrPlmn + ulLength),
                                  (VOS_UINT32)ulMaxLength - ulLength,
                                  (VOS_UINT32)ulMaxLength - ulLength,
                                  ",%X%X%X",
                                  (ulMnc & 0x0f),
                                  (ulMnc & 0xf00)>>8,
                                  (ulMnc & 0x0f0000)>>16 );
    }

    *pusLength = (VOS_UINT16)ulLength;

    return;
}

/*****************************************************************************
     : AT_NetMonFmtGsmSCellData
   : GSM  
   : pstSCellInfo -- 
   : pusLength  --  GSM  
     : VOS_VOID
   :
   :

        :
  1.       : 20151019
           : wx270776
       : 
*****************************************************************************/
VOS_VOID AT_NetMonFmtGsmSCellData(
    MTA_AT_NETMON_CELL_INFO_STRU       *pstSCellInfo,
    VOS_UINT16                         *pusLength
)
{
    VOS_UINT8                           pucPlmnstr[AT_NETMON_PLMN_STRING_MAX_LENGTH];
    VOS_UINT32                          ulMcc;
    VOS_UINT32                          ulMnc;
    VOS_UINT16                          ulPlmnStrLen;
    VOS_UINT16                          usLength;

    usLength                          = 0;
    ulPlmnStrLen                      = 0;
    TAF_MEM_SET_S(pucPlmnstr, sizeof(pucPlmnstr), 0x00, sizeof(pucPlmnstr));

    ulMcc = pstSCellInfo->unSCellInfo.stGsmSCellInfo.stSCellInfo.ulMcc;
    ulMnc = pstSCellInfo->unSCellInfo.stGsmSCellInfo.stSCellInfo.ulMnc;

    AT_NetMonFmtPlmnId(ulMcc, ulMnc, (VOS_CHAR *)pucPlmnstr, &ulPlmnStrLen);

    /* PLMN */
    usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                        (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                        "^MONSC: GSM,%s,%d,%d,%d,%X,%X",
                                        pucPlmnstr,
                                        pstSCellInfo->unSCellInfo.stGsmSCellInfo.stSCellInfo.enBand,
                                        pstSCellInfo->unSCellInfo.stGsmSCellInfo.stSCellInfo.usArfcn,
                                        pstSCellInfo->unSCellInfo.stGsmSCellInfo.stSCellInfo.ucBsic,
                                        pstSCellInfo->unSCellInfo.stGsmSCellInfo.stSCellInfo.ulCellID,
                                        pstSCellInfo->unSCellInfo.stGsmSCellInfo.stSCellInfo.usLac );

    /* RSSI */
    if (AT_NETMON_GSM_RSSI_INVALID_VALUE == pstSCellInfo->unSCellInfo.stGsmSCellInfo.stSCellInfo.sRssi)
    {
        usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                            (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                            "," );
    }
    else
    {
        usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                            (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                            ",%d",
                                            pstSCellInfo->unSCellInfo.stGsmSCellInfo.stSCellInfo.sRssi );
    }

    /*  */
    if (AT_NETMON_GSM_RX_QUALITY_INVALID_VALUE == pstSCellInfo->unSCellInfo.stGsmSCellInfo.stSCellInfo.ucRxQuality)
    {
        usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                            (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                            "," );
    }
    else
    {
        usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                            (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                            ",%d",
                                            pstSCellInfo->unSCellInfo.stGsmSCellInfo.stSCellInfo.ucRxQuality );
    }

    /*TA*/
    if (PS_IE_PRESENT == pstSCellInfo->unSCellInfo.stGsmSCellInfo.bitOpTa)
    {
        usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                            (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                            ",%d",
                                            pstSCellInfo->unSCellInfo.stGsmSCellInfo.usTa );
    }
    else
    {
        usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                            "," );
    }

    *pusLength = usLength;

    return;
}

/*****************************************************************************
     : AT_NetMonFmtUtranFddSCellData
   : WCDMA  
   : pstSCellInfo -- 
   : pusLength  --  WCDMA  
     : VOS_VOID
   :
   :

        :
  1.       : 20151019
           : wx270776
       : 
*****************************************************************************/
VOS_VOID AT_NetMonFmtUtranFddSCellData(
    MTA_AT_NETMON_CELL_INFO_STRU       *pstSCellInfo,
    VOS_UINT16                         *pusLength
)
{
    VOS_UINT8                           pucPlmnstr[AT_NETMON_PLMN_STRING_MAX_LENGTH];
    VOS_UINT32                          ulMcc;
    VOS_UINT32                          ulMnc;
    VOS_UINT16                          ulPlmnStrLen;
    VOS_UINT16                          usLength;

    usLength                          = 0;
    ulPlmnStrLen                      = 0;
    TAF_MEM_SET_S(pucPlmnstr, sizeof(pucPlmnstr), 0x00, sizeof(pucPlmnstr));

    ulMcc = pstSCellInfo->unSCellInfo.stUtranSCellInfo.ulMcc;
    ulMnc = pstSCellInfo->unSCellInfo.stUtranSCellInfo.ulMnc;

    AT_NetMonFmtPlmnId(ulMcc, ulMnc, (VOS_CHAR *)pucPlmnstr, &ulPlmnStrLen);

    /* PLMN */
    usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                        (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                        "^MONSC: WCDMA,%s",
                                        pucPlmnstr );

    /**/
    usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                        (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                        ",%d",
                                        pstSCellInfo->unSCellInfo.stUtranSCellInfo.usArfcn );

    /* PSC */
    if ((AT_NETMON_UTRAN_FDD_RSCP_INVALID_VALUE == pstSCellInfo->unSCellInfo.stUtranSCellInfo.u.stCellMeasResultsFDD.sRSCP)
        && (AT_NETMON_UTRAN_FDD_ECN0_INVALID_VALUE == pstSCellInfo->unSCellInfo.stUtranSCellInfo.u.stCellMeasResultsFDD.sECN0))
    {
        usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                            (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                            "," );
    }
    else
    {
        usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                            (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                            ",%d",
                                            pstSCellInfo->unSCellInfo.stUtranSCellInfo.u.stCellMeasResultsFDD.usPSC );
    }

    /*Cell ID*/
    if (PS_IE_PRESENT == pstSCellInfo->unSCellInfo.stUtranSCellInfo.bitOpCellID)
    {
        usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                            (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                            ",%X",
                                            pstSCellInfo->unSCellInfo.stUtranSCellInfo.ulCellID );
    }
    else
    {
        usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                            (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                            "," );
    }

    /*LAC*/
    if (PS_IE_PRESENT == pstSCellInfo->unSCellInfo.stUtranSCellInfo.bitOpLAC)
    {
        usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                            (VOS_CHAR *)pgucAtSndCodeAddr+usLength,
                                            ",%X",
                                            pstSCellInfo->unSCellInfo.stUtranSCellInfo.usLAC );
    }
    else
    {
        usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                            (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                            "," );
    }

    /* RSCP */
    if (AT_NETMON_UTRAN_FDD_RSCP_INVALID_VALUE == pstSCellInfo->unSCellInfo.stUtranSCellInfo.u.stCellMeasResultsFDD.sRSCP)
    {
        usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                            (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                            "," );
    }
    else
    {
        usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                            (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                            ",%d",
                                            pstSCellInfo->unSCellInfo.stUtranSCellInfo.u.stCellMeasResultsFDD.sRSCP );
    }

    /* RSSI */
    if (AT_NETMON_UTRAN_FDD_RSSI_INVALID_VALUE == pstSCellInfo->unSCellInfo.stUtranSCellInfo.u.stCellMeasResultsFDD.sRSSI)
    {
        usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                            (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                            "," );
    }
    else
    {
        usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                            (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                            ",%d",
                                            pstSCellInfo->unSCellInfo.stUtranSCellInfo.u.stCellMeasResultsFDD.sRSSI );
    }

    /* ECN0 */
    if (AT_NETMON_UTRAN_FDD_ECN0_INVALID_VALUE == pstSCellInfo->unSCellInfo.stUtranSCellInfo.u.stCellMeasResultsFDD.sECN0)
    {
        usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                            (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                            "," );
    }
    else
    {
        usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                            (VOS_CHAR *)pgucAtSndCodeAddr+usLength,
                                            ",%d",
                                            pstSCellInfo->unSCellInfo.stUtranSCellInfo.u.stCellMeasResultsFDD.sECN0 );
    }

    /*DRX*/
    if (PS_IE_PRESENT == pstSCellInfo->unSCellInfo.stUtranSCellInfo.u.stCellMeasResultsFDD.bitOpDRX)
    {
        usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                            (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                            ",%d",
                                            pstSCellInfo->unSCellInfo.stUtranSCellInfo.u.stCellMeasResultsFDD.ulDrx );
    }
    else
    {
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                            (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                            "," );
    }

    /*URA Id*/
    if (PS_IE_PRESENT == pstSCellInfo->unSCellInfo.stUtranSCellInfo.u.stCellMeasResultsFDD.bitOpURA)
    {
        usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                            (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                            ",%d",
                                            pstSCellInfo->unSCellInfo.stUtranSCellInfo.u.stCellMeasResultsFDD.usURA );
    }
    else
    {
        usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                            (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                            "," );
    }

    *pusLength = usLength;

    return;
}

/*****************************************************************************
     : AT_NetMonFmtGsmNCellData
   : GSM  
   : pstNCellInfo -- 
             usInLen      -- 
   : pusOutLen    --  GSM  
     : VOS_VOID
   :
   :

        :
  1.       : 20151019
           : wx270776
       : 
*****************************************************************************/
VOS_VOID AT_NetMonFmtGsmNCellData(
    MTA_AT_NETMON_CELL_INFO_STRU       *pstNCellInfo,
    VOS_UINT16                          usInLen,
    VOS_UINT16                         *pusOutLen
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT16                          usLength;

    usLength                          = usInLen;

    if (pstNCellInfo->stNCellInfo.ucGsmNCellCnt > NETMON_MAX_GSM_NCELL_NUM)
    {
        pstNCellInfo->stNCellInfo.ucGsmNCellCnt = NETMON_MAX_GSM_NCELL_NUM;
    }

    /* GSM */
    for (ulLoop = 0; ulLoop < pstNCellInfo->stNCellInfo.ucGsmNCellCnt; ulLoop++)
    {
        /*  */
        if (0 != usLength)
        {
            usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                                (VOS_CHAR *)pgucAtSndCodeAddr,
                                                (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                "%s",
                                                gaucAtCrLf );
        }

        usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                            (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                            "^MONNC: GSM,%d,%d",
                                            pstNCellInfo->stNCellInfo.astGsmNCellInfo[ulLoop].enBand,
                                            pstNCellInfo->stNCellInfo.astGsmNCellInfo[ulLoop].usAfrcn );

        /*Bsic*/
        if (PS_IE_PRESENT == pstNCellInfo->stNCellInfo.astGsmNCellInfo[ulLoop].bitOpBsic)
        {
            usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                                (VOS_CHAR *)pgucAtSndCodeAddr,
                                                (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                ",%d",
                                                pstNCellInfo->stNCellInfo.astGsmNCellInfo[ulLoop].ucBsic );
        }
        else
        {
            usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                                (VOS_CHAR *)pgucAtSndCodeAddr,
                                                (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                "," );
        }

        /*Cell ID*/
        if (PS_IE_PRESENT == pstNCellInfo->stNCellInfo.astGsmNCellInfo[ulLoop].bitOpCellID)
        {
            usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                ",%X",
                                                pstNCellInfo->stNCellInfo.astGsmNCellInfo[ulLoop].ulCellID );
        }
        else
        {
            usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                                (VOS_CHAR *)pgucAtSndCodeAddr,
                                                (VOS_CHAR *)pgucAtSndCodeAddr+usLength,
                                                "," );
        }

         /*LAC*/
        if (PS_IE_PRESENT == pstNCellInfo->stNCellInfo.astGsmNCellInfo[ulLoop].bitOpLAC)
        {
            usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               ",%X",
                                               pstNCellInfo->stNCellInfo.astGsmNCellInfo[ulLoop].usLAC );
        }
        else
        {
            usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "," );
        }

        /*RSSI*/
        usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                            (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                            ",%d",
                                            pstNCellInfo->stNCellInfo.astGsmNCellInfo[ulLoop].sRSSI );
    }

    *pusOutLen = usLength;

    return;
}
/*****************************************************************************
     : AT_NetMonFmtUtranFddNCellData
   : WCDMA  
   : pstNCellInfo -- 
             usInLen      -- 
   : pusOutLen    --  WCDMA 
     : VOS_VOID
   :
   :

        :
  1.       : 20151019
           : wx270776
       : 
*****************************************************************************/
VOS_VOID AT_NetMonFmtUtranFddNCellData(
    MTA_AT_NETMON_CELL_INFO_STRU       *pstNCellInfo,
    VOS_UINT16                          usInLen,
    VOS_UINT16                         *pusOutLen
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT16                          usLength;

    usLength                          = usInLen;

    if (pstNCellInfo->stNCellInfo.ucUtranNCellCnt > NETMON_MAX_UTRAN_NCELL_NUM)
    {
        pstNCellInfo->stNCellInfo.ucUtranNCellCnt = NETMON_MAX_UTRAN_NCELL_NUM;
    }

    /*WCDMA */
    for (ulLoop = 0; ulLoop < pstNCellInfo->stNCellInfo.ucUtranNCellCnt; ulLoop++)
    {
        /*  */
        if (0 != usLength)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                (VOS_CHAR *)pgucAtSndCodeAddr,
                                                (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                "%s",
                                                gaucAtCrLf);
        }

        usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                            (VOS_CHAR *)pgucAtSndCodeAddr+usLength,
                                            "^MONNC: WCDMA,%d,%d,%d,%d",
                                            pstNCellInfo->stNCellInfo.u.astFddNCellInfo[ulLoop].usArfcn,
                                            pstNCellInfo->stNCellInfo.u.astFddNCellInfo[ulLoop].usPSC,
                                            pstNCellInfo->stNCellInfo.u.astFddNCellInfo[ulLoop].sRSCP,
                                            pstNCellInfo->stNCellInfo.u.astFddNCellInfo[ulLoop].sECN0 );
    }

    *pusOutLen = usLength;

    return;
}

/*****************************************************************************
     : At_SetNetMonSCellPara
   : ^MONSC
   : ucIndex - 
   : 
     : 
   :
   :

       :
  1.       : 20151019
           : wx270776
       : 
*****************************************************************************/
VOS_UINT32 At_SetNetMonSCellPara(
    VOS_UINT8                           ucIndex
)
{
    VOS_UINT32                          ulRst;

    if (AT_CMD_OPT_SET_CMD_NO_PARA != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    ulRst = AT_FillAndSndAppReqMsg( gastAtClientTab[ucIndex].usClientId,
                                    gastAtClientTab[ucIndex].opId,
                                    ID_AT_MTA_SET_NETMON_SCELL_REQ,
                                    VOS_NULL_PTR,
                                    0,
                                    I0_UEPS_PID_MTA );

    if (TAF_SUCCESS == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_MONSC_SET;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}
/*****************************************************************************
     : At_SetNetMonNCellPara
   : ^MONNC
   : ucIndex - 
   : 
     : 
   :
   :

       :
  1.       : 20151019
           : wx270776
       : 
*****************************************************************************/
VOS_UINT32 At_SetNetMonNCellPara(
    VOS_UINT8                           ucIndex
)
{
    VOS_UINT32                          ulRst;

    if (AT_CMD_OPT_SET_CMD_NO_PARA != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    ulRst = AT_FillAndSndAppReqMsg( gastAtClientTab[ucIndex].usClientId,
                                    gastAtClientTab[ucIndex].opId,
                                    ID_AT_MTA_SET_NETMON_NCELL_REQ,
                                    VOS_NULL_PTR,
                                    0,
                                    I0_UEPS_PID_MTA );

    if (TAF_SUCCESS == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_MONNC_SET;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }

}
/*****************************************************************************
     : AT_RcvMtaSetNetMonSCellCnf
   : ATMTAMONSC
   : pstMsg -- 
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 20151019
           : wx270776
       : 
*****************************************************************************/
VOS_UINT32 AT_RcvMtaSetNetMonSCellCnf(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pstRcvMsg = VOS_NULL_PTR;
    MTA_AT_NETMON_CELL_INFO_STRU       *pstSetCnf = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;
    VOS_UINT16                          usLength;

    /*  */
    pstRcvMsg                         = (AT_MTA_MSG_STRU *)pMsg;
    pstSetCnf                         = (MTA_AT_NETMON_CELL_INFO_STRU *)pstRcvMsg->aucContent;

    usLength                          = 0;
    ucIndex                           = 0;

    /* clientidindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaSetMonitServingCellCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaSetMonitServingCellCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* AT */
    if (AT_CMD_MONSC_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaSetMonitServingCellCnf : Current Option is not AT_CMD_JDETEX_SET.");
        return VOS_ERR;
    }

    /* AT */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    if ( (MTA_AT_RESULT_ERROR   == pstSetCnf->enResult)
      || (MTA_NETMON_SCELL_TYPE != pstSetCnf->enCellType) )
    {
        gstAtSendData.usBufLen = usLength;
        At_FormatResultData(ucIndex, AT_ERROR);

        return VOS_OK;
    }

    switch(pstSetCnf->enRatType)
    {
        case MTA_AT_NETMON_CELL_INFO_GSM:
        {
            AT_NetMonFmtGsmSCellData(pstSetCnf, &usLength);
            break;
        }
        case MTA_AT_NETMON_CELL_INFO_UTRAN_FDD:
        {
            AT_NetMonFmtUtranFddSCellData(pstSetCnf, &usLength);
            break;
        }
        case MTA_AT_NETMON_CELL_INFO_UTRAN_TDD:
        {
            AT_NetMonFmtUtranTddSCellData(pstSetCnf, &usLength);
            break;
        }
        case MTA_AT_NETMON_CELL_INFO_LTE:
        {
            AT_NetMonFmtEutranSCellData(pstSetCnf, &usLength);
            break;
        }
        default:
            usLength += (TAF_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "^MONSC: NONE" );
            break;
    }


    /*  */
    gstAtSendData.usBufLen = usLength;
    At_FormatResultData(ucIndex, AT_OK);

    return VOS_OK;
}

/*****************************************************************************
     : AT_RcvMtaSetNetMonNCellCnf
   : ATMTAMONNC
   : pstMsg -- 
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 20151019
           : wx270776
       : 
*****************************************************************************/
VOS_UINT32 AT_RcvMtaSetNetMonNCellCnf(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pstRcvMsg = VOS_NULL_PTR;
    MTA_AT_NETMON_CELL_INFO_STRU       *pstSetCnf = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;
    VOS_UINT16                          usLength;
    VOS_UINT16                          usLengthTemp;

    /*  */
    pstRcvMsg                         = (AT_MTA_MSG_STRU *)pMsg;
    pstSetCnf                         = (MTA_AT_NETMON_CELL_INFO_STRU *)pstRcvMsg->aucContent;

    ucIndex                           = 0;
    usLength                          = 0;

    /* clientidindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaSetMonitNeighCellCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaSetMonitNeighCellCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* AT */
    if (AT_CMD_MONNC_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaSetMonitNeighCellCnf : Current Option is not AT_CMD_JDETEX_SET.");
        return VOS_ERR;
    }

    /* AT */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    if ( (MTA_AT_RESULT_ERROR   == pstSetCnf->enResult)
      || (MTA_NETMON_NCELL_TYPE != pstSetCnf->enCellType) )
    {
        gstAtSendData.usBufLen = usLength;
        At_FormatResultData(ucIndex, AT_ERROR);

        return VOS_OK;
    }

    usLengthTemp   = 0;
    usLength       = 0;

    /* GSM */
    AT_NetMonFmtGsmNCellData(pstSetCnf, usLengthTemp, &usLength);

    /* UTRAN */
    usLengthTemp = usLength;

    if (MTA_NETMON_UTRAN_FDD_TYPE == pstSetCnf->stNCellInfo.enCellMeasTypeChoice)
    {
        AT_NetMonFmtUtranFddNCellData(pstSetCnf, usLengthTemp, &usLength);
    }
    else if (MTA_NETMON_UTRAN_TDD_TYPE == pstSetCnf->stNCellInfo.enCellMeasTypeChoice)
    {
        AT_NetMonFmtUtranTddNCellData(pstSetCnf, usLengthTemp, &usLength);
    }
    else
    {
        /**/
        ;
    }

    /* LTE */
    usLengthTemp = usLength;

    AT_NetMonFmtEutranNCellData(pstSetCnf, usLengthTemp, &usLength);

    /* NONE */
    if ( 0 == ( pstSetCnf->stNCellInfo.ucGsmNCellCnt +
                pstSetCnf->stNCellInfo.ucUtranNCellCnt + pstSetCnf->stNCellInfo.ucLteNCellCnt ) )
    {
        usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                            (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                            "^MONNC: NONE" );
    }

    /*  */
    gstAtSendData.usBufLen = usLength;
    At_FormatResultData(ucIndex, AT_OK);

    return VOS_OK;
}

/*****************************************************************************
     : AT_NetMonFmtUtranTddSCellData
   : TD-SCDMA  
   : pstSCellInfo -- 
   : pusLength  --  TD-SCDMA  
     : VOS_VOID
   :
   :

        :
  1.       : 20151019
           : wx270776
       : 
*****************************************************************************/
VOS_VOID AT_NetMonFmtUtranTddSCellData(
    MTA_AT_NETMON_CELL_INFO_STRU       *pstSCellInfo,
    VOS_UINT16                         *pusLength
)
{
    VOS_UINT8                           pucPlmnstr[AT_NETMON_PLMN_STRING_MAX_LENGTH];
    VOS_UINT32                          ulMcc;
    VOS_UINT32                          ulMnc;
    VOS_UINT16                          ulPlmnStrLen;
    VOS_UINT16                          usLength;

    usLength                          = 0;
    ulPlmnStrLen                      = 0;
    TAF_MEM_SET_S(pucPlmnstr, sizeof(pucPlmnstr), 0x00, sizeof(pucPlmnstr));

    ulMcc = pstSCellInfo->unSCellInfo.stUtranSCellInfo.ulMcc;
    ulMnc = pstSCellInfo->unSCellInfo.stUtranSCellInfo.ulMnc;

    AT_NetMonFmtPlmnId(ulMcc, ulMnc, (VOS_CHAR *)pucPlmnstr, &ulPlmnStrLen);

    /* PLMN */
    usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                        (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                        "^MONSC: TD_SCDMA,%s",
                                        pucPlmnstr );

    usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                        (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                        ",%d,%d,%d,%X,%X,%d,%d,%d",
                                        pstSCellInfo->unSCellInfo.stUtranSCellInfo.usArfcn,
                                        pstSCellInfo->unSCellInfo.stUtranSCellInfo.u.stCellMeasResultsTDD.usSyncID,
                                        pstSCellInfo->unSCellInfo.stUtranSCellInfo.u.stCellMeasResultsTDD.usSC,
                                        pstSCellInfo->unSCellInfo.stUtranSCellInfo.ulCellID,
                                        pstSCellInfo->unSCellInfo.stUtranSCellInfo.usLAC,
                                        pstSCellInfo->unSCellInfo.stUtranSCellInfo.u.stCellMeasResultsTDD.sRSCP,
                                        pstSCellInfo->unSCellInfo.stUtranSCellInfo.u.stCellMeasResultsTDD.ulDrx,
                                        pstSCellInfo->unSCellInfo.stUtranSCellInfo.u.stCellMeasResultsTDD.usRac );

    *pusLength = usLength;

    return;
}
/*****************************************************************************
     : AT_NetMonFmtUtranFddNCellData
   : TD-SCDMA  
   : pstNCellInfo -- 
             usInLen      -- 
   : pusOutLen    --  TD-SCDMA 
     : VOS_VOID
   :
   :

        :
  1.       : 20151019
           : wx270776
       : 
*****************************************************************************/
VOS_VOID AT_NetMonFmtUtranTddNCellData(
    MTA_AT_NETMON_CELL_INFO_STRU       *pstNCellInfo,
    VOS_UINT16                          usInLen,
    VOS_UINT16                         *pusOutLen
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT16                          usLength;

    usLength                          = usInLen;

    if (pstNCellInfo->stNCellInfo.ucUtranNCellCnt > NETMON_MAX_UTRAN_NCELL_NUM)
    {
        pstNCellInfo->stNCellInfo.ucUtranNCellCnt = NETMON_MAX_UTRAN_NCELL_NUM;
    }

    /*WCDMA */
    for (ulLoop = 0; ulLoop < pstNCellInfo->stNCellInfo.ucUtranNCellCnt; ulLoop++)
    {
        /*  */
        if (0 != usLength)
        {
            usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                                 (VOS_CHAR *)pgucAtSndCodeAddr,
                                                 (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                 "%s",
                                                 gaucAtCrLf );
        }

        usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                            (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                            "^MONNC: TD_SCDMA,%d,%d,%d,%d",
                                            pstNCellInfo->stNCellInfo.u.astTddNCellInfo[ulLoop].usArfcn,
                                            pstNCellInfo->stNCellInfo.u.astTddNCellInfo[ulLoop].usSyncID,
                                            pstNCellInfo->stNCellInfo.u.astTddNCellInfo[ulLoop].usSC,
                                            pstNCellInfo->stNCellInfo.u.astTddNCellInfo[ulLoop].sRSCP );
    }

    *pusOutLen = usLength;

    return;
}

/*****************************************************************************
     : AT_NetMonFmtEutranSCellData
   : LTE  
   : pstSCellInfo -- 
   : pusLength  --  LTE  
     : VOS_VOID
   :
   :

        :
  1.       : 20151019
           : wx270776
       : 
*****************************************************************************/
VOS_VOID AT_NetMonFmtEutranSCellData(
    MTA_AT_NETMON_CELL_INFO_STRU       *pstSCellInfo,
    VOS_UINT16                         *pusLength
)
{
    VOS_UINT8                           pucPlmnstr[AT_NETMON_PLMN_STRING_MAX_LENGTH];
    VOS_UINT32                          ulMcc;
    VOS_UINT32                          ulMnc;
    VOS_UINT16                          ulPlmnStrLen;
    VOS_UINT16                          usLength;

    usLength                          = 0;
    ulPlmnStrLen                      = 0;
    TAF_MEM_SET_S(pucPlmnstr, sizeof(pucPlmnstr), 0x00, sizeof(pucPlmnstr));

    ulMcc = pstSCellInfo->unSCellInfo.stLteSCellInfo.ulMcc;
    ulMnc = pstSCellInfo->unSCellInfo.stLteSCellInfo.ulMnc;

    AT_NetMonFmtPlmnId(ulMcc, ulMnc, (VOS_CHAR *)pucPlmnstr, &ulPlmnStrLen);

    /* PLMN */
    usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                        (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                        "^MONSC: LTE,%s",
                                        pucPlmnstr );

    usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                        (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                        ",%d,%X,%X,%X,%d,%d,%d",
                                        pstSCellInfo->unSCellInfo.stLteSCellInfo.usArfcn,
                                        pstSCellInfo->unSCellInfo.stLteSCellInfo.ulCellID,
                                        pstSCellInfo->unSCellInfo.stLteSCellInfo.ulPID,
                                        pstSCellInfo->unSCellInfo.stLteSCellInfo.usTAC,
                                        pstSCellInfo->unSCellInfo.stLteSCellInfo.sRSRP,
                                        pstSCellInfo->unSCellInfo.stLteSCellInfo.sRSRQ,
                                        pstSCellInfo->unSCellInfo.stLteSCellInfo.sRSSI );
    *pusLength = usLength;

    return;
}

/*****************************************************************************
     : AT_NetMonFmtEutranNCellData
   : LTE  
   : pstNCellInfo -- 
             usInLen   -- 
   : pusOutLen  --  LTE 
     : VOS_VOID
   :
   :

        :
  1.       : 20151019
           : wx270776
       : 
*****************************************************************************/
VOS_VOID AT_NetMonFmtEutranNCellData(
    MTA_AT_NETMON_CELL_INFO_STRU       *pstNCellInfo,
    VOS_UINT16                          usInLen,
    VOS_UINT16                         *pusOutLen
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT16                          usLength;

    usLength                          = usInLen;

    if (pstNCellInfo->stNCellInfo.ucLteNCellCnt > NETMON_MAX_LTE_NCELL_NUM)
    {
        pstNCellInfo->stNCellInfo.ucLteNCellCnt = NETMON_MAX_LTE_NCELL_NUM;
    }

     /* LTE */
    for (ulLoop = 0; ulLoop < pstNCellInfo->stNCellInfo.ucLteNCellCnt; ulLoop++)
    {
        /*  */
        if (0 != usLength)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                (VOS_CHAR *)pgucAtSndCodeAddr,
                                                (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                "%s",
                                                gaucAtCrLf);
        }

        usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                            (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                            "^MONNC: LTE,%d,%X,%d,%d,%d",
                                            pstNCellInfo->stNCellInfo.astLteNCellInfo[ulLoop].usArfcn,
                                            pstNCellInfo->stNCellInfo.astLteNCellInfo[ulLoop].ulPID,
                                            pstNCellInfo->stNCellInfo.astLteNCellInfo[ulLoop].sRSRP,
                                            pstNCellInfo->stNCellInfo.astLteNCellInfo[ulLoop].sRSRQ,
                                            pstNCellInfo->stNCellInfo.astLteNCellInfo[ulLoop].sRSSI );
    }

    *pusOutLen = usLength;

    return;
}

/*****************************************************************************
     : AT_FmtLocalTime
   : LOCAL TIME
   : MTA_AT_SIB16_TIME_UPDATE_STRU      *pstSib16TimeUpdate - 
             VOS_UINT16                          usInLen            - 
   : VOS_UINT16                         *pusOutLen          - 
     : 
   :
   :

       :
  1.       : 2016525
           : wx270776
       : 

*****************************************************************************/
VOS_VOID AT_FmtTimeStru(
    MTA_AT_TIME_STRU                   *pstTimeStru,
    VOS_UINT16                         *pusOutLen,
    VOS_UINT16                          usInLen
)
{
    VOS_UINT16                          usLength;

    usLength = usInLen;

    /* YY */
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%d%d/",
                                       pstTimeStru->usYear / 10,
                                       pstTimeStru->usYear % 10);
    /* MM */
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%d%d/",
                                       pstTimeStru->ucMonth / 10,
                                       pstTimeStru->ucMonth % 10);
    /* dd */
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%d%d,",
                                       pstTimeStru->ucDay / 10,
                                       pstTimeStru->ucDay % 10);

    /* hh */
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%d%d:",
                                       pstTimeStru->ucHour / 10,
                                       pstTimeStru->ucHour % 10);

    /* mm */
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%d%d:",
                                       pstTimeStru->ucMinute / 10,
                                       pstTimeStru->ucMinute % 10);

    /* ss */
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%d%d, ",
                                       pstTimeStru->ucSecond / 10,
                                       pstTimeStru->ucSecond % 10);

   *pusOutLen = usLength;

    return;
}

/*lint -save -e845 -specific(-e845)*/
/*****************************************************************************
     : AT_FormatRsrp
   : RSRP
   : MTA_AT_RS_INFO_QRY_CNF_STRU        *pstRsInfoQryCnf - MTAATLTE
   : 
     : 
   :
   :

       :
  1.       : 20170118
           : wx270776
       : 

*****************************************************************************/
VOS_VOID AT_FormatRsrp(
    MTA_AT_RS_INFO_QRY_CNF_STRU        *pstRsInfoQryCnf
)
{
    VOS_UINT32                          i;
    VOS_UINT16                          usLength;

    usLength = 0;

    /* AT+RSRP? */
    gstAtSendData.usBufLen = 0;

    /* +RSRP: */
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "+RSRP:");

    /*  */
    if ( (MTA_AT_RESULT_NO_ERROR != pstRsInfoQryCnf->enResult)
      || (0 == pstRsInfoQryCnf->stRsInfoRslt.ulRsInfoNum) )
    {
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "NONE");
        
        gstAtSendData.usBufLen = usLength;
        return;
    }

    for (i = 0; i < pstRsInfoQryCnf->stRsInfoRslt.ulRsInfoNum; i++)
    {
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%d",
                                           pstRsInfoQryCnf->stRsInfoRslt.u.astRsrpInfo[i].ulCellId);

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           ",%d",
                                           pstRsInfoQryCnf->stRsInfoRslt.u.astRsrpInfo[i].ulEarfcn);

        if (pstRsInfoQryCnf->stRsInfoRslt.u.astRsrpInfo[i].lRsrp >= 0)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           ",%d.%02d",
                                           pstRsInfoQryCnf->stRsInfoRslt.u.astRsrpInfo[i].lRsrp / AT_RS_INFO_MULTI,
                                           pstRsInfoQryCnf->stRsInfoRslt.u.astRsrpInfo[i].lRsrp % AT_RS_INFO_MULTI);
        }
        else
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           ",-%d.%02d",
                                           (-pstRsInfoQryCnf->stRsInfoRslt.u.astRsrpInfo[i].lRsrp) / AT_RS_INFO_MULTI,
                                           (-pstRsInfoQryCnf->stRsInfoRslt.u.astRsrpInfo[i].lRsrp) % AT_RS_INFO_MULTI);
        }
        

        if (i == pstRsInfoQryCnf->stRsInfoRslt.ulRsInfoNum - 1)
        {
            break;
        }

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           ",");
    }
    
    gstAtSendData.usBufLen = usLength;
    return;
}

/*****************************************************************************
     : AT_FormatRsrq
   : RSRQ
   : MTA_AT_RS_INFO_QRY_CNF_STRU        *pstRsInfoQryCnf - MTAATLTE
   : 
     : 
   :
   :

       :
  1.       : 20170118
           : wx270776
       : 

*****************************************************************************/
VOS_VOID AT_FormatRsrq(
    MTA_AT_RS_INFO_QRY_CNF_STRU        *pstRsInfoQryCnf
)
{
    VOS_UINT32                          i;
    VOS_UINT16                          usLength;

    usLength = 0;

    /* AT+RSRQ? */
    gstAtSendData.usBufLen = 0;

    /* +RSRQ: */
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "+RSRQ:");

    /*  */
    if ( (MTA_AT_RESULT_NO_ERROR != pstRsInfoQryCnf->enResult)
      || (0 == pstRsInfoQryCnf->stRsInfoRslt.ulRsInfoNum) )
    {
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "NONE");
        
        gstAtSendData.usBufLen = usLength;
        return;
    }

    for (i = 0; i < pstRsInfoQryCnf->stRsInfoRslt.ulRsInfoNum; i++)
    {
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%d",
                                           pstRsInfoQryCnf->stRsInfoRslt.u.astRsrqInfo[i].ulCellId);

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           ",%d",
                                           pstRsInfoQryCnf->stRsInfoRslt.u.astRsrqInfo[i].ulEarfcn);

        if (pstRsInfoQryCnf->stRsInfoRslt.u.astRsrqInfo[i].lRsrq >= 0)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           ",%d.%02d",
                                           pstRsInfoQryCnf->stRsInfoRslt.u.astRsrqInfo[i].lRsrq / AT_RS_INFO_MULTI,
                                           pstRsInfoQryCnf->stRsInfoRslt.u.astRsrqInfo[i].lRsrq % AT_RS_INFO_MULTI);
        }
        else
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           ",-%d.%02d",
                                           (-pstRsInfoQryCnf->stRsInfoRslt.u.astRsrqInfo[i].lRsrq) / AT_RS_INFO_MULTI,
                                           (-pstRsInfoQryCnf->stRsInfoRslt.u.astRsrqInfo[i].lRsrq) % AT_RS_INFO_MULTI);
        }

        if (i == pstRsInfoQryCnf->stRsInfoRslt.ulRsInfoNum - 1)
        {
            break;
        }

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           ",");
    }
    
    gstAtSendData.usBufLen = usLength;
    return;
}
/*lint -restore*/

/*****************************************************************************
     : AT_FormatGasAtCmdRslt
   : GAS
   : GAS_AT_RSLT_STRU                   *pstAtCmdRslt - GAS
   : 
     : 
   :
   :

       :
  1.       : 2017715
           : wx270776
       : 

*****************************************************************************/
VOS_VOID AT_FormatGasAtCmdRslt(
    GAS_AT_RSLT_STRU                   *pstAtCmdRslt
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          j;
    VOS_UINT16                          usLength;

    j = 0;
    usLength = 0;
    
    for (i = 0; i< (pstAtCmdRslt->ulRsltNum/3); i++)
    {
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pgucAtSndCodeAddr+usLength,
                                           "%d:%d,",
                                           (i+1),
                                           pstAtCmdRslt->aulRslt[j++]);
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pgucAtSndCodeAddr+usLength,
                                           "0x%X,",
                                           pstAtCmdRslt->aulRslt[j++]&0xff);
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pgucAtSndCodeAddr+usLength,
                                           "%d\r\n",
                                           pstAtCmdRslt->aulRslt[j++]);
    }
    
    gstAtSendData.usBufLen = usLength;
}



