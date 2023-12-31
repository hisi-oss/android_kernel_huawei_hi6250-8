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
#include "mdrv.h"
#include "PppInterface.h"
#include "TafDrvAgent.h"
#include "Taf_Tafm_Remote.h"
#include "TtfMemAtInterface.h"
#include "ATCmdProc.h"
#include "AtCheckFunc.h"
#include "AtParseCmd.h"
#include "AtPhyInterface.h"
#include "AtDataProc.h"
#include "AtCmdMsgProc.h"
#include "AtCheckFunc.h"
#include "AtSndMsg.h"
#include "AtRnicInterface.h"
#include "AtCheckFunc.h"
#include "AtInputProc.h"
#include "AtEventReport.h"
#include "AtDeviceCmd.h"


/* Added by l00167671 for NV , 2013-05-17, begin */
#include "NasNvInterface.h"
#include "TafNvInterface.h"
/* Added by l00167671 for NV , 2013-05-17, end*/

#include "AtTafAgentInterface.h"
#include "AppVcApi.h"
#include "TafOamInterface.h"

#include "msp_nvim.h"
#include "msp_nv_def.h"
#include "msp_nv_id.h"
#include "at_common.h"
/* ADD by c64416 for V9R1/V7R1 AT, 2013/09/18 begin */
#include "at_lte_common.h"
/* ADD by c64416 for V9R1/V7R1 AT, 2013/09/18 end */

#include "CssAtInterface.h"

#include "AtMsgPrint.h"

#include "PsCommonDef.h"
#include "PsLib.h"
#include "product_config.h"
#include "TafAppCall.h"



/*****************************************************************************
    .C
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_AT_QUERYPARACMD_C


/*****************************************************************************
   2 
*****************************************************************************/

/**/
extern TAF_UINT32                       gulErrType;

extern VOS_UINT32                       g_ulWifiFreq;
extern VOS_UINT32                       g_ulWifiMode;
extern VOS_UINT32                       g_ulWifiRate;
extern VOS_UINT32                       g_lWifiPower;
/* Added by L00171473 for DTS2012020106679,AT WT 2012-01-17  Begin */
extern VOS_UINT32                       g_ulUcastWifiRxPkts;
extern VOS_UINT32                       g_ulMcastWifiRxPkts;
/* Added by L00171473 for DTS2012020106679,AT WT 2012-01-17  End */


/*****************************************************************************
   3 
*****************************************************************************/

/* Modified by z00161729 for DCM, 2012-8-30, begin */
/* Modified by z00161729 for DCM, 2012-8-30, end */
/*****************************************************************************
   4 
*****************************************************************************/
/*****************************************************************************
     : AT_QryGTimerPara
   : GPRS
   : TAF_UINT8 ucIndex 
   : 
     : VOS_UINT32 ATC
             AT_OK                  
             AT_DEVICE_OTHER_ERROR  NV
   :
   :

       :
  1.       : 201082
           : /f62575
       : 
  2.       : 20121213
           : L00171473
       : DTS2012121802573, TQE
*****************************************************************************/
VOS_UINT32 AT_QryGTimerPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulGTimerLength;


    ulGTimerLength = 0;

    /* NVen_NV_Item_GPRS_ActiveTimerLengthGPRS */
    ulRet = NV_ReadEx(MODEM_ID_0, en_NV_Item_GPRS_ActiveTimerLength,
                    &ulGTimerLength,
                    sizeof(ulGTimerLength));
    if (NV_OK != ulRet)
    {
        AT_WARN_LOG("AT_QryGTimerPara: Fail to read en_NV_Item_GPRS_ActiveTimerLength");
        return AT_DEVICE_OTHER_ERROR;
    }

    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      "%s:%d",
                                      g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                      ulGTimerLength);

    return AT_OK;
}

/*****************************************************************************
     : AT_QryRsimPara
   : SIM/USIM
             < state >   
             0   
             1   SIM/USIM/UIM
             2   SIM/USIM/UIM
   : VOS_UINT8 ucIndex 
   : 
     : VOS_UINT32 ATC
             AT_OK      
             AT_ERROR   MT
   :
   :

       :
  1.       : 201082
           : /f62575
       : 
  2.       : 20111012
           : /w00181244
       : SIM
  3.       : 20120406
           : f62575
       : DTS2012040600347SIM2
  4.       : 20121224
           : l60609
       : DSDA Phase II
  5.       : 201335
           : l60609
       : DSDA PHASE III
*****************************************************************************/
VOS_UINT32 AT_QryRsimPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                           ucCardStatus;
    VOS_UINT32                           ucCardType;
    /* Modified by l60609 for DSDA Phase II, 2012-12-24, Begin */
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT32                          ulGetModemIdRslt;
    /* Modified by l60609 for DSDA Phase III, 2013-3-5, Begin */
    AT_USIM_INFO_CTX_STRU              *pstUsimInfoCtx = VOS_NULL_PTR;

    enModemId = MODEM_ID_0;

    ulGetModemIdRslt = AT_GetModemIdFromClient(ucIndex, &enModemId);

    if (VOS_OK != ulGetModemIdRslt)
    {
        AT_ERR_LOG("At_SetCardModePara:Get Modem Id fail!");
        return AT_ERROR;
    }

    pstUsimInfoCtx = AT_GetUsimInfoCtxFromModemId(enModemId);
    /* Modified by l60609 for DSDA Phase II, 2012-12-24, End */

    /*  SIM  */
    ucCardType   =  pstUsimInfoCtx->enCardType;
    ucCardStatus =  pstUsimInfoCtx->enCardStatus;
    /* Modified by l60609 for DSDA Phase III, 2013-3-5, End */

    AT_NORM_LOG1("AT_QryRsimPara: ucCardStatus is ", (VOS_INT32)ucCardStatus);
    AT_NORM_LOG1("AT_QryRsimPara: ucCardType is ",   (VOS_INT32)ucCardType);

    if (USIMM_CARDAPP_SERVIC_BUTT == ucCardStatus)
    {
        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          "%s:%d",
                                          g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                          AT_RSIM_STATUS_USIMM_CARD_BUSY);
        return AT_OK;
    }

    /* USIMM_CARD_ROM_SIM */
    if ((USIMM_CARD_MEDIUM_ROM == pstUsimInfoCtx->enCardMediumType)
     || (USIMM_CARDAPP_SERVIC_ABSENT == ucCardStatus))
    {
        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          "%s:%d",
                                          g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                          AT_RSIM_STATUS_USIMM_CARD_ABSENT);
    }
    else
    {
        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          "%s:%d",
                                          g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                          AT_RSIM_STATUS_USIMM_CARD_AVAILABLE);
    }

    return AT_OK;
}

/*****************************************************************************
     : AT_QryBatVolPara
   : 

   : VOS_UINT8 ucIndex
   : 
     : OK
   :
   :

       :
  1.       : 20110531
           : w00166186
       : 

  2.       : 20111015
           : /w00181244
       :, API I0_WUEPS_PID_DRV_AGENTAPI
  3.       : 20120303
           : s62952
       : BalongV300R002 Build  :FEATURE_E5,
*****************************************************************************/
VOS_UINT32 AT_QryBatVolPara(VOS_UINT8 ucIndex)
{

    /* */
    if (TAF_SUCCESS == AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                             gastAtClientTab[ucIndex].opId,
                                             DRV_AGENT_TBATVOLT_QRY_REQ,
                                             VOS_NULL_PTR,
                                             0,
                                             I0_WUEPS_PID_DRV_AGENT))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_TBATVOLT_QRY;           /* */
        return AT_WAIT_ASYNC_RETURN;                                            /*  */
    }
    else
    {
        return AT_ERROR;
    }
}

/* Added by f62575 for AT Project, 2011/10/20, begin */
/*****************************************************************************
     : AT_DeciDigit2Ascii
   : ASCII
   : VOS_UINT8  aucDeciDigit[]
             VOS_UINT32 ulLength      
   : VOS_UINT8  aucAscii[]    ASCII
     : VOS_UINT32 : VOS_OKVOS_ERR
   :
   :

       :
  1.       : 201082
           : /f62575
       : 

*****************************************************************************/
VOS_UINT32 AT_DeciDigit2Ascii(
    VOS_UINT8                           aucDeciDigit[],
    VOS_UINT32                          ulLength,
    VOS_UINT8                           aucAscii[]
)
{
    VOS_UINT32                          ulLoop;

    for (ulLoop = 0; ulLoop < ulLength; ulLoop++)
    {
        if (aucDeciDigit[ulLoop] > 9)
        {
            return VOS_ERR;
        }

        aucAscii[ulLoop] = aucDeciDigit[ulLoop] + '0';
    }

    return VOS_OK;
}
/* Added by f62575 for AT Project, 2011/10/20, end */

/*****************************************************************************
     : AT_ConvertImsiDigit2String
   : IMSI
   : VOS_UINT8                           aucImsi[NAS_MAX_IMSI_LENGTH]
             VOS_UINT8                          *pucImsiString
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20151027
           : n00355355
       : 

*****************************************************************************/
VOS_VOID AT_ConvertImsiDigit2String(
    VOS_UINT8                          *pucImsi,
    VOS_UINT8                          *pucImsiString
)
{
    VOS_UINT8                           ucImsiLen;
    VOS_UINT32                          ulTempNum;
    VOS_UINT8                           aucImsiNum[NAS_IMSI_STR_LEN];
    VOS_UINT32                          i;

    AT_NORM_LOG("AT_ConvertImsiDigit2String enter.");

    TAF_MEM_SET_S(aucImsiNum, sizeof(aucImsiNum), 0x00, NAS_IMSI_STR_LEN);
    ulTempNum       = 0;
    ucImsiLen       = pucImsi[0];

    aucImsiNum[ulTempNum++] = (pucImsi[1] & 0xf0) >> 4;

    for (i = 2; i <= ucImsiLen; i++)
    {
        aucImsiNum[ulTempNum++] = pucImsi[i] & 0x0f;
        aucImsiNum[ulTempNum++] = (pucImsi[i] & 0xf0) >> 4;
    }

    /* 'f'IMSI */
    i = 0;

    while (i < ulTempNum)
    {
        if (0x0f != aucImsiNum[i])
        {
            pucImsiString[i] = aucImsiNum[i] + '0';
            i++;
        }
        else
        {
            break;
        }
    }

    pucImsiString[i] = '\0';

    AT_INFO_LOG(pucImsiString);

    return;
}

/* Added by f62575 for SMALL IMAGE, 2012-1-3, begin */
/*****************************************************************************
     : AT_GetPhynumMac
   : PHYNUMMAC
   : 
   : VOS_UINT8 aucMac[]  PHYNUMMAC
     : VOS_UINT32          
   :
   :

       :
  1.       : 2012112
           : f62575
       : 
  2.       : 20121213
           : L00171473
       : DTS2012121802573, TQE
*****************************************************************************/
VOS_UINT32 AT_GetPhynumMac(VOS_UINT8 aucMac[])
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulRet;
    VOS_UINT8                           aucE5GwMacAddr[AT_MAC_ADDR_LEN + 1]; /* MAC*/
    VOS_UINT32                          ulE5GwMacAddrOffset;
    VOS_UINT32                          ulMacOffset;


    TAF_MEM_SET_S(aucE5GwMacAddr, sizeof(aucE5GwMacAddr), 0x00, sizeof(aucE5GwMacAddr));

    /* MAC */
    ulRet = NV_ReadEx(MODEM_ID_0, en_NV_Item_WIFI_MAC_ADDR, aucE5GwMacAddr, AT_MAC_ADDR_LEN);
    if (NV_OK != ulRet)
    {
        AT_WARN_LOG("AT_GetPhynumMac: Fail to read en_Nv_Item_Imei_Svn.");
        return AT_ERROR;
    }

    /* MAC: 7A:FE:E2:21:11:E4=>7AFEE22111E4 */
    ulMacOffset         = 0;
    ulE5GwMacAddrOffset = 0;
    for (ulLoop = 0; ulLoop < (1 + AT_PHYNUM_MAC_COLON_NUM); ulLoop++)
    {
        TAF_MEM_CPY_S(&aucMac[ulMacOffset],
                   AT_PHYNUM_MAC_LEN + 1 - ulMacOffset,
                   &aucE5GwMacAddr[ulE5GwMacAddrOffset],
                   AT_WIFIGLOBAL_MAC_LEN_BETWEEN_COLONS);
        ulMacOffset         += AT_WIFIGLOBAL_MAC_LEN_BETWEEN_COLONS;
        ulE5GwMacAddrOffset += AT_WIFIGLOBAL_MAC_LEN_BETWEEN_COLONS + VOS_StrLen(":");
    }

    aucMac[AT_PHYNUM_MAC_LEN] = '\0';

    return AT_OK;
}
/* Added by f62575 for SMALL IMAGE, 2012-1-3, end */

/*****************************************************************************
     : AT_QryPhyNumPara
   : 
   : VOS_UINT8 ucIndex 
   : 
     : VOS_UINT32 ATC
             AT_OK      
             AT_ERROR   NV
   :
   :

       :
  1.       : 201082
           : /f62575
       : 

  2.       : 2011103
           : /w00181244
       : AT_GetImeiValue

  3.       : 201213
           : f62575
       : SMALL IMAGE: MAC

  4.       : 2012419
           : A00165503
       : DTS2012041104111: WIFI, WIFI
                 MAC
  5.       : 2012810
           : L00171473
       : DTS2012082204471, TQE
  6.       : 201334
           : L60609
       : DSDA PHASE III
*****************************************************************************/
VOS_UINT32 AT_QryPhyNumPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRet;
    VOS_UINT16                          usLength;
    VOS_UINT8                           aucAsciiImei[TAF_PH_IMEI_LEN + 1];
    TAF_SVN_DATA_STRU                   stSvn;
    VOS_UINT8                           aucAsciiSvn[TAF_SVN_DATA_LENGTH + 1];
    /* Added by f62575 for SMALL IMAGE, 2012-1-3, begin */
    VOS_UINT8                           aucMac[AT_PHYNUM_MAC_LEN + 1]; /* MAC*/
    /* Added by f62575 for SMALL IMAGE, 2012-1-3, end */
    /* Modified by l60609 for DSDA Phase III, 2013-3-4, Begin */
    MODEM_ID_ENUM_UINT16                enModemId;

    enModemId = MODEM_ID_0;
    /* Modified by l60609 for DSDA Phase III, 2013-3-4, End */


    TAF_MEM_SET_S(&stSvn, sizeof(stSvn), 0x00, sizeof(stSvn));


    /* Modified by l60609 for DSDA Phase III, 2013-3-4, Begin */
    ulRet = AT_GetModemIdFromClient(ucIndex, &enModemId);

    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_QryPhyNumPara: Get modem id fail.");
        return AT_ERROR;
    }

    /* NVIMEI */
    ulRet = AT_GetImeiValue(enModemId, aucAsciiImei);

    if (VOS_OK != ulRet)
    {
        AT_WARN_LOG("AT_QryPhyNumPara: Fail to read en_NV_Item_IMEI.");
        return AT_ERROR;
    }

    /* NVSVN */
    ulRet = NV_ReadEx(enModemId, en_NV_Item_Imei_Svn, &stSvn, sizeof(stSvn));
    /* Modified by l60609 for DSDA Phase III, 2013-3-4, End */
    if (NV_OK != ulRet)
    {
        AT_WARN_LOG("AT_QryPhyNumPara: Fail to read en_Nv_Item_Imei_Svn.");
        return AT_ERROR;
    }
    else
    {
        if (NV_ITEM_ACTIVE != stSvn.ucActiveFlag)
        {
            /* nv'0' */
            TAF_MEM_SET_S(aucAsciiSvn, sizeof(aucAsciiSvn), '0', TAF_SVN_DATA_LENGTH);
        }
        else
        {
            AT_DeciDigit2Ascii(stSvn.aucSvn, TAF_SVN_DATA_LENGTH, aucAsciiSvn);
        }

        aucAsciiSvn[TAF_SVN_DATA_LENGTH] = '\0';
    }

    /* Added by f62575 for SMALL IMAGE, 2012-1-3, begin */
    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      "%s:IMEI,%s%s",
                                      g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                      aucAsciiImei, gaucAtCrLf);

    if (BSP_MODULE_SUPPORT == mdrv_misc_support_check(BSP_MODULE_TYPE_WIFI) )
    {
        ulRet = AT_GetPhynumMac(aucMac);
        if (AT_OK != ulRet)
        {
            AT_WARN_LOG("AT_QryPhyNumPara: Fail to read en_NV_Item_IMEI.");
            return AT_ERROR;
        }

        /* MAC */
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%s:MACWLAN,%s%s",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                           aucMac,
                                           gaucAtCrLf);
    }

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s:SVN,%s",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                       aucAsciiSvn);

    /* Added by f62575 for SMALL IMAGE, 2012-1-3, end   */

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}

/*****************************************************************************
     : AT_WriteActiveMessage
   : NVIM
   : MODEM_ID_ENUM_UINT16                enModemId
             MN_MSG_ACTIVE_MESSAGE_STRU         *pstOrgActiveMessageInfo NVIM
             MN_MSG_ACTIVE_MESSAGE_STRU         *pstActiveMessageInfo   
   : 
     : MN_ERR_NO_ERROR 
   :
   :

       :
  1.       : 20111022
           : f62575
       :  CMN_MSG_WriteActiveMessageA

*****************************************************************************/
VOS_UINT32 AT_WriteActiveMessage(
    MODEM_ID_ENUM_UINT16                enModemId,
    MN_MSG_ACTIVE_MESSAGE_STRU         *pstOrgActiveMessageInfo,
    MN_MSG_ACTIVE_MESSAGE_STRU         *pstActiveMessageInfo
)
{
    VOS_UINT32                          ulRet;
    VOS_INT32                           lRet;
    VOS_UINT8                          *pucActiveMessageInfo;
    VOS_UINT8                          *pucEvaluate;

    /*1.NVIMNVIM*/
    if (pstOrgActiveMessageInfo->enActiveStatus == pstActiveMessageInfo->enActiveStatus)
    {
        if (pstOrgActiveMessageInfo->stUrl.ulLen == pstActiveMessageInfo->stUrl.ulLen)
        {
            if (pstOrgActiveMessageInfo->enMsgCoding == pstActiveMessageInfo->enMsgCoding)
            {
                lRet = VOS_MemCmp(pstOrgActiveMessageInfo->stUrl.aucUrl,
                                  pstActiveMessageInfo->stUrl.aucUrl,
                                  pstActiveMessageInfo->stUrl.ulLen);
                if (0 == lRet)
                {
                    return MN_ERR_NO_ERROR;
                }
            }
        }
    }

    /*2.NVIM*/
    /*2.1 NVIM*/
    pucActiveMessageInfo = (VOS_UINT8 *)PS_MEM_ALLOC(WUEPS_PID_AT,
                                                     MN_MSG_ACTIVE_MESSAGE_PARA_LEN);
    if (VOS_NULL_PTR == pucActiveMessageInfo)
    {
        return MN_ERR_NOMEM;
    }

    /*2.2 NVIM*/
    pucEvaluate  = pucActiveMessageInfo;
    *pucEvaluate = pstActiveMessageInfo->enActiveStatus;
    pucEvaluate++;

    *pucEvaluate = pstActiveMessageInfo->enMsgCoding;
    pucEvaluate++;

    *pucEvaluate = (VOS_UINT8)(pstActiveMessageInfo->stUrl.ulLen & 0xff);
    pucEvaluate++;
    *pucEvaluate = (VOS_UINT8)((pstActiveMessageInfo->stUrl.ulLen >> 8) & 0xff);
    pucEvaluate++;
    *pucEvaluate = (VOS_UINT8)((pstActiveMessageInfo->stUrl.ulLen >> 16) & 0xff);
    pucEvaluate++;
    *pucEvaluate = (VOS_UINT8)((pstActiveMessageInfo->stUrl.ulLen >> 24) & 0xff);
    pucEvaluate++;

    TAF_MEM_CPY_S(pucEvaluate,
               MN_MSG_ACTIVE_MESSAGE_PARA_LEN - 6,
               pstActiveMessageInfo->stUrl.aucUrl,
               (VOS_UINT16)pstActiveMessageInfo->stUrl.ulLen);

    /*2.3 NVIM*/
    /* Modified by l60609 for DSDA Phase III, 2013-3-4, Begin */
    ulRet = NV_WriteEx(enModemId,
                       en_NV_Item_SMS_ActiveMessage_Para,
                       pucActiveMessageInfo,
                       MN_MSG_ACTIVE_MESSAGE_PARA_LEN);
    /* Modified by l60609 for DSDA Phase III, 2013-3-4, End */
    if (NV_OK != ulRet)
    {
        ulRet = MN_ERR_CLASS_SMS_NVIM;
    }
    else
    {
        ulRet = MN_ERR_NO_ERROR;
    }

    PS_MEM_FREE(WUEPS_PID_AT, pucActiveMessageInfo);
    return ulRet;
}

/*****************************************************************************
     : AT_QryRstriggerPara
   : URL
   : TAF_UINT8                           ucIndex    
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 2010315
           : f62575
       : 

  2.       : 201334
           : l60609
       : DSDA PHASE III
*****************************************************************************/
TAF_UINT32 AT_QryRstriggerPara(
    TAF_UINT8                           ucIndex
)
{
    TAF_UINT32                          ulRet;
    TAF_UINT16                          usLength;
    MN_MSG_ACTIVE_MESSAGE_STRU          stActiveMessageInfo;
    /* Modified by l60609 for DSDA Phase III, 2013-3-4, Begin */
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT32                          ulRslt;

    usLength  = 0;
    enModemId = MODEM_ID_0;

    ulRslt = AT_GetModemIdFromClient(ucIndex, &enModemId);

    if (VOS_OK != ulRslt)
    {
        AT_ERR_LOG("AT_SetRstriggerPara: Get modem id fail.");
        return AT_ERROR;
    }
    /* Modified by l60609 for DSDA Phase III, 2013-3-4, End */

    /*NVIM*/
    /* Modified by l60609 for DSDA Phase III, 2013-3-4, Begin */
    ulRet = AT_ReadActiveMessage(enModemId, &stActiveMessageInfo);
    /* Modified by l60609 for DSDA Phase III, 2013-3-4, End */
    if (MN_ERR_NO_ERROR != ulRet)
    {
        AT_LOG1("AT_QryRstriggerPara: fail to get NVIM information, cause is %d",
                ulRet);
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%s: 255,\"\"",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    }
    else
    {
        if (MN_MSG_ACTIVE_MESSAGE_STATUS_ACTIVE != stActiveMessageInfo.enActiveStatus)
        {
            stActiveMessageInfo.enActiveStatus = MN_MSG_ACTIVE_MESSAGE_STATUS_DEACTIVE;
        }

        /*: URL*/
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%s: ",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                            (TAF_CHAR *)pgucAtSndCodeAddr,
                                            (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                            "%d,\"",
                                            stActiveMessageInfo.enActiveStatus);

        usLength += (TAF_UINT16)At_PrintReportData(AT_CMD_MAX_LEN,
                                                   (TAF_INT8 *)pgucAtSndCodeAddr,
                                                   stActiveMessageInfo.enMsgCoding,
                                                   (pgucAtSndCodeAddr + usLength),
                                                   stActiveMessageInfo.stUrl.aucUrl,
                                                   (TAF_UINT16)stActiveMessageInfo.stUrl.ulLen);

        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "\"");
    }

    gstAtSendData.usBufLen = usLength;
    return AT_OK;
}

/*****************************************************************************
 Prototype      : At_QryClipPara
 Description    :
 Input          : ucIndex --- 
 Output         :
 Return Value   : AT_XXX  --- ATC
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
  2.        : 20070111
            : d49431
        : A32D08327
*****************************************************************************/
TAF_UINT32 At_QryClipPara(TAF_UINT8 ucIndex)
{
    TAF_SS_INTERROGATESS_REQ_STRU para;

    /*  */
    TAF_MEM_SET_S(&para, sizeof(para), 0x00, sizeof(para));

    /* SsCode */
    para.SsCode = TAF_CLIP_SS_CODE;

    if(AT_SUCCESS == TAF_InterrogateSSReq(gastAtClientTab[ucIndex].usClientId, 0,&para))
    {
        /*  */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CLIP_READ;
        return AT_WAIT_ASYNC_RETURN;    /*  */
    }
    else
    {
        return AT_ERROR;
    }
}
/*****************************************************************************
 Prototype      : At_QryClirPara
 Description    :
 Input          : ucIndex --- 
 Output         :
 Return Value   : AT_XXX  --- ATC
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2006-11-27
    Author      : ---
    Modification: Created function A32D07303
  2.        : 20070111
            : d49431
        : A32D08327
  3.        : 20070530
            : d49431
        : A32D11328
*****************************************************************************/
TAF_UINT32 At_QryClirPara(TAF_UINT8 ucIndex)
{
    TAF_SS_INTERROGATESS_REQ_STRU para;

    /*  */
    TAF_MEM_SET_S(&para, sizeof(para), 0x00, sizeof(para));

    /* SsCode */
    para.SsCode = TAF_CLIR_SS_CODE;

    if (TAF_InterrogateSSReq(gastAtClientTab[ucIndex].usClientId,
        0, &para) == TAF_SUCCESS)
    {
        /*  */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CLIR_READ;
        return AT_WAIT_ASYNC_RETURN;    /*  */
    }
    else
    {
        return AT_ERROR;
    }
}

/*****************************************************************************
     : At_QryColpPara
   : AT+COLP
   : TAF_UINT8 ucIndex
   : 
     : TAF_UINT32
   :
   :

       :
  1.       : 20111027
           : o00132663
       : 

*****************************************************************************/
TAF_UINT32 At_QryColpPara(TAF_UINT8 ucIndex)
{
    TAF_SS_INTERROGATESS_REQ_STRU para;

    /*  */
    TAF_MEM_SET_S(&para, sizeof(para), 0x00, sizeof(para));

    /* SsCode */
    para.SsCode = TAF_COLP_SS_CODE;

    para.OP_BsService = 0;

    if(AT_SUCCESS == TAF_InterrogateSSReq(gastAtClientTab[ucIndex].usClientId, 0,&para))
    {
        /*  */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_COLP_READ;
        return AT_WAIT_ASYNC_RETURN;    /*  */
    }
    else
    {
        return AT_ERROR;
    }
}
/*****************************************************************************
 Prototype      : At_QryS0Para
 Description    :
 Input          : ucIndex --- 
 Output         :
 Return Value   : AT_XXX  --- ATC
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
  2.Date        : 2009-03-25
    Author      : S62952
    Modification: AT2D10248
  3.       : 2013221
           : l60609
       : DSDA PHASE III
*****************************************************************************/
TAF_UINT32 At_QryS0Para(TAF_UINT8 ucIndex)
{
    /* Modified by l60609 for DSDA Phase III, 2013-2-21, Begin */
    AT_MODEM_CC_CTX_STRU               *pstCcCtx = VOS_NULL_PTR;

    pstCcCtx = AT_GetModemCcCtxAddrFromClientId(ucIndex);

    gstAtSendData.usBufLen  = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR*)pgucAtSndCodeAddr,
                                                    "%d",
                                                    pstCcCtx->stS0TimeInfo.ucS0TimerLen);
    /* Modified by l60609 for DSDA Phase III, 2013-2-21, End */
    return AT_OK;
}
/*****************************************************************************
 Prototype      : At_QryS3Para
 Description    :
 Input          : ucIndex --- 
 Output         :
 Return Value   : AT_XXX  --- ATC
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_QryS3Para(TAF_UINT8 ucIndex)
{
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR*)pgucAtSndCodeAddr,"%03d",ucAtS3);
    return AT_OK;
}
/*****************************************************************************
 Prototype      : At_QryS4Para
 Description    :
 Input          : ucIndex --- 
 Output         :
 Return Value   : AT_XXX  --- ATC
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_QryS4Para(TAF_UINT8 ucIndex)
{
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR*)pgucAtSndCodeAddr,"%03d",ucAtS4);
    return AT_OK;
}
/*****************************************************************************
 Prototype      : At_QryS5Para
 Description    :
 Input          : ucIndex --- 
 Output         :
 Return Value   : AT_XXX  --- ATC
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_QryS5Para(TAF_UINT8 ucIndex)
{
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR*)pgucAtSndCodeAddr,"%03d",ucAtS5);
    return AT_OK;
}
/*****************************************************************************
 Prototype      : At_QryS6Para
 Description    :
 Input          : ucIndex --- 
 Output         :
 Return Value   : AT_XXX  --- ATC
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2009-05-27
    Author      : L47619
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_QryS6Para(TAF_UINT8 ucIndex)
{
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR*)pgucAtSndCodeAddr,"%03d",ucAtS6);
    return AT_OK;
}
/*****************************************************************************
 Prototype      : At_QryS7Para
 Description    :
 Input          : ucIndex --- 
 Output         :
 Return Value   : AT_XXX  --- ATC
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2009-05-27
    Author      : L47619
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_QryS7Para(TAF_UINT8 ucIndex)
{
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR*)pgucAtSndCodeAddr,"%03d",ucAtS7);
    return AT_OK;
}
/*****************************************************************************
 Prototype      : At_QryCusdPara
 Description    :
 Input          : ucIndex --- 
 Output         :
 Return Value   : AT_XXX  --- ATC
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
  2.       : 2013221
           : l60609
       : DSDA PHASE III
  3.       : 201343
           : s00217060
       : ATC
*****************************************************************************/
TAF_UINT32 At_QryCusdPara(TAF_UINT8 ucIndex)
{
    /* Modified by s00217060 for ATC, 2013-4-1, begin */
    AT_MTA_UNSOLICITED_RPT_QRY_REQ_STRU     stAtCmd;
    VOS_UINT32                              ulResult;

    TAF_MEM_SET_S(&stAtCmd, sizeof(stAtCmd), 0x00, sizeof(AT_MTA_UNSOLICITED_RPT_QRY_REQ_STRU));
    stAtCmd.enReqType       = AT_MTA_QRY_CUSD_RPT_TYPE;

    /* MTA+cusd */
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   ID_AT_MTA_UNSOLICITED_RPT_QRY_REQ,
                                   &stAtCmd,
                                   sizeof(AT_MTA_UNSOLICITED_RPT_QRY_REQ_STRU),
                                   I0_UEPS_PID_MTA);

    if (TAF_SUCCESS != ulResult)
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_UNSOLICITED_RPT_READ;

    return AT_WAIT_ASYNC_RETURN;
    /* Modified by s00217060 for ATC, 2013-4-1, end */
}
/*****************************************************************************
 Prototype      : At_QryCcwaPara
 Description    :
 Input          : ucIndex --- 
 Output         :
 Return Value   : AT_XXX  --- ATC
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
  2.       : 2013221
           : l60609
       : DSDA PHASE III
*****************************************************************************/
TAF_UINT32 At_QryCcwaPara(TAF_UINT8 ucIndex)
{
    /* Modified by l60609 for DSDA Phase III, 2013-2-21, Begin */
    AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;

    pstSsCtx = AT_GetModemSsCtxAddrFromClientId(ucIndex);

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR*)pgucAtSndCodeAddr,"%s: %d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    pstSsCtx->ucCcwaType);
    /* Modified by l60609 for DSDA Phase III, 2013-2-21, End */
    return AT_OK;
}
/*****************************************************************************
 Prototype      : At_QryCpinPara
 Description    :
 Input          : ucIndex --- 
 Output         :
 Return Value   : AT_XXX  --- ATC
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
  1.Date        : 2009-08-25
    Author      : h44270
    Modification: AT2D14070
*****************************************************************************/
TAF_UINT32 At_QryCpinPara(TAF_UINT8 ucIndex)
{
    TAF_PH_PIN_DATA_STRU stPinData;

    TAF_MEM_SET_S(&stPinData, sizeof(stPinData), 0x00, sizeof(stPinData));

    stPinData.CmdType = TAF_PIN_QUERY;

    stPinData.PinType = TAF_SIM_NON;


    if(AT_SUCCESS == Taf_PhonePinHandle(gastAtClientTab[ucIndex].usClientId, 0,&stPinData))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CPIN_READ;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}


/*****************************************************************************
 Prototype      : At_QryIccidPara
 Description    : ^ICCID
 Input          : ucIndex --- 
 Output         :
 Return Value   : AT_WAIT_ASYNC_RETURN
                  AT_ERROR
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2009-08-27
    Author      : L47619
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_QryIccidPara(TAF_UINT8 ucIndex)
{
    /*  */
    if(AT_SUCCESS == Taf_ParaQuery(gastAtClientTab[ucIndex].usClientId,0,TAF_PH_ICC_ID,TAF_NULL_PTR))
    {
        /*  */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_ICCID_READ;
        return AT_WAIT_ASYNC_RETURN;    /*  */
    }
    else
    {
        return AT_ERROR;
    }
}

/*******************************************************************************
*Function   : At_QryCardTypePara
*Description: OK
*Input      :
*Output     :
*Return     : TAF_UINT32
*Others     :
*History    :
  1.Date        : 2014-06-04
    Author      : w00180399
    Modification: Created function
********************************************************************************/
TAF_UINT32 At_QryCardTypePara(TAF_UINT8 ucIndex)
{
    VOS_UINT32 ulResult;

    ulResult = SI_PIH_CardTypeQuery(gastAtClientTab[ucIndex].usClientId,
                                      gastAtClientTab[ucIndex].opId);

    if (TAF_SUCCESS != ulResult)
    {
        AT_WARN_LOG("SI_PIH_CardTypeQuery: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CARDTYPE_QUERY;

    return AT_WAIT_ASYNC_RETURN;
}

/*******************************************************************************
*Function   : At_ QryPNNPara
*Description: OK
*Input      :
*Output     :
*Return     : TAF_UINT32
*Others     :
*History    :
  1.Date        : 2008-03-04
    Author      : h59254
    Modification: Created function
  2.       : 20120625
           : f00179208
       : :DTS2012062202129, AT^PNN?OK
********************************************************************************/
TAF_UINT32 At_QryPNNPara (TAF_UINT8 ucIndex)
{

    return AT_OK;
}

/*****************************************************************************
     : At_QryCPNNPara
   : ^CPNN
   : TAF_UINT8 ucIndex
   : 
     : TAF_UINT32
   :
   :

       :
  1.Date        : 2009-09-09
    Author      : l00130025
    Modification: Created function

  2.       : 2011114
           : /l60609
       : AT Project:TAF_IsNormalSrvStatusC
*****************************************************************************/
TAF_UINT32 At_QryCPNNPara (TAF_UINT8 ucIndex)
{
    /*Modified by l60609 for At Project, 2011-11-3, Begin */
    VOS_UINT32                          ulRst;

    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   DRV_AGENT_CPNN_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_WUEPS_PID_DRV_AGENT);

    if (TAF_SUCCESS == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CPNN_READ;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
    /*Modified by l60609 for At Project, 2011-11-3, Begin */
}

/*******************************************************************************
*Function   : At_QryOPLPara
*Description: OK.
*Input      :
*Output     :
*Return     : TAF_UINT32
*Others     :
*History    :
  1.Date        : 2008-03-06
    Author      : h59254
    Modification: Created function
  2.       : 20121224
           : l00198894
       : DTS2012121702841: ^OPLAT
********************************************************************************/
TAF_UINT32 At_QryOPLPara (TAF_UINT8 ucIndex)
{

    return AT_OK;

}

/*****************************************************************************
 Prototype      : At_QryCpinStatus
 Description    :
 Input          : ucIndex --- 
 Output         :
 Return Value   : AT_XXX  --- ATC
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2007-09-29
    Author      : ---
    Modification: Created function by z100318
*****************************************************************************/
TAF_UINT32 At_QryCpinStatus(TAF_UINT8 ucIndex)
{
    TAF_PH_PIN_DATA_STRU stPinData;

    TAF_MEM_SET_S(&stPinData, sizeof(stPinData), 0x00, sizeof(stPinData));

    stPinData.CmdType = TAF_PIN_RemainTime;
    stPinData.PinType = TAF_SIM_NON;

    if(AT_SUCCESS == Taf_PhonePinHandle(gastAtClientTab[ucIndex].usClientId, 0,&stPinData))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CPIN_READ;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}
/*****************************************************************************
 Prototype      : At_QryCardlockPara
 Description    :
 Input          : ucIndex --- 
 Output         :
 Return Value   : AT_XXX  --- ATC
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2007-03-15
    Author      : luojian
    Modification: Created function by z100318
*****************************************************************************/
TAF_UINT32 At_QryCardlockPara(TAF_UINT8 ucIndex)
{
    TAF_ME_PERSONALISATION_DATA_STRU    stMePersonalisationData;

    TAF_MEM_SET_S(&stMePersonalisationData, sizeof(stMePersonalisationData), 0x00, sizeof(TAF_ME_PERSONALISATION_DATA_STRU));

    /*  */
    stMePersonalisationData.CmdType     = TAF_ME_PERSONALISATION_QUERY;
    /*  */
    stMePersonalisationData.MePersonalType = TAF_OPERATOR_PERSONALISATION;
    /*  */
    if(AT_SUCCESS == Taf_MePersonalisationHandle(gastAtClientTab[ucIndex].usClientId, 0,&stMePersonalisationData))
    {
        /*  */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CARD_LOCK_READ;
        return AT_WAIT_ASYNC_RETURN;    /*  */
    }
    else
    {
        return AT_ERROR;
    }
}

/*****************************************************************************
 Prototype      : At_QryCpin2Para
 Description    :
 Input          : ucIndex --- 
 Output         :
 Return Value   : AT_XXX  --- ATC
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
  2.        : 20120407
            : L47619
        : AP-Modem
*****************************************************************************/
TAF_UINT32 At_QryCpin2Para(TAF_UINT8 ucIndex)
{
    TAF_PH_PIN_DATA_STRU stPinData;

    TAF_MEM_SET_S(&stPinData, sizeof(stPinData), 0x00, sizeof(stPinData));

    /* Modified by L47619 for AP-Modem Personalisation Project, 2012/04/21, begin */
    stPinData.CmdType = TAF_PIN2_QUERY;
    /* Modified by L47619 for AP-Modem Personalisation Project, 2012/04/21, end */

    stPinData.PinType = TAF_SIM_NON;

    if(AT_SUCCESS == Taf_PhonePinHandle(gastAtClientTab[ucIndex].usClientId, 0,&stPinData))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CPIN2_READ;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}
/*****************************************************************************
 Prototype      : At_QryCpbsPara
 Description    :
 Input          : ucIndex --- 
 Output         :
 Return Value   : AT_XXX  --- ATC
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
2.       : 20070930
           : Z100318
       : :A32D12973

*****************************************************************************/
TAF_UINT32 At_QryCpbsPara(TAF_UINT8 ucIndex)
{
    gulPBPrintTag = VOS_TRUE;

    if(AT_SUCCESS == SI_PB_Query(gastAtClientTab[ucIndex].usClientId,0))
    {
        /*  */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CPBS_READ;
        return AT_WAIT_ASYNC_RETURN;    /*  */
    }
    else
    {
        return AT_ERROR;
    }

}
/*****************************************************************************
 Prototype      : At_QryCfunPara
 Description    :
 Input          : ucIndex --- 
 Output         :
 Return Value   : AT_XXX  --- ATC
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
 2.       : 20121213
          : L00171473
      : DTS2012121802573, TQE
 3.       : 20150323
          : y00322978
      :Phone Mode 
*****************************************************************************/
TAF_UINT32 At_QryCfunPara(TAF_UINT8 ucIndex)
{
    if(VOS_TRUE == TAF_MMA_QryPhoneModeReq(WUEPS_PID_AT, gastAtClientTab[ucIndex].usClientId, 0))
    {
        /*  */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CFUN_READ;
        return AT_WAIT_ASYNC_RETURN;    /*  */
    }
    else
    {
        return AT_ERROR;
    }
}

/*****************************************************************************
 Prototype      : At_QryCpamPara
 Description    :
 Input          : ucIndex --- 
 Output         :
 Return Value   : AT_XXX  --- ATC
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function

  2.       : 2015327
           : g00261581
       : 
*****************************************************************************/
TAF_UINT32 At_QryCpamPara(TAF_UINT8 ucIndex)
{
    if(VOS_TRUE == TAF_MMA_QryAccessModeReq(WUEPS_PID_AT, gastAtClientTab[ucIndex].usClientId, 0))
    {
        /*  */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CPAM_READ;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}
/*****************************************************************************
 Prototype      : At_QryStsfPara
 Description    :
 Input          : ucIndex --- 
 Output         :
 Return Value   : AT_XXX  --- ATC
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
  2.       : 2013517
           : l00167671
       : NV, NV
*****************************************************************************/
TAF_UINT32 At_QryStsfPara(TAF_UINT8 ucIndex)
{
    USIMM_STK_CFG_STRU                  ProfileContent={0};
    TAF_UINT32                          Result ;
    TAF_UINT16                          NVLen = sizeof(USIMM_STK_CFG_STRU);
    TAF_UINT16                          Length = 0;
    MODEM_ID_ENUM_UINT16                usModemId;

    Result = NV_ReadEx(MODEM_ID_0, en_NV_Item_TerminalProfile_Set, &ProfileContent, NVLen);

    if(NV_OK != Result)
    {
        return AT_ERROR;
    }

    if (VOS_OK != AT_GetModemIdFromClient(ucIndex, &usModemId))
    {
        return AT_ERROR;
    }

    Length += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                (TAF_CHAR *)pgucAtSndCodeAddr,
                                                (TAF_CHAR*)pgucAtSndCodeAddr+Length,
                                                "^STSF:%d,",
                                                ProfileContent.ucFuncEnable);

    if (TAF_MMA_USIMM_CARD_USIM == AT_GetUsimInfoCtxFromModemId(usModemId)->enCardType)
    {
        Length += (TAF_UINT16)At_HexAlpha2AsciiString(AT_CMD_MAX_LEN,
                                                    (TAF_INT8 *)pgucAtSndCodeAddr,
                                                    (TAF_UINT8 *)pgucAtSndCodeAddr+Length,
                                                    ProfileContent.stUsimProfile.aucProfile,
                                                    ProfileContent.stUsimProfile.ucProfileLen);
    }
    else
    {
        Length += (TAF_UINT16)At_HexAlpha2AsciiString(AT_CMD_MAX_LEN,
                                                    (TAF_INT8 *)pgucAtSndCodeAddr,
                                                    (TAF_UINT8 *)pgucAtSndCodeAddr+Length,
                                                    ProfileContent.stSimProfile.aucProfile,
                                                    ProfileContent.stSimProfile.ucProfileLen);

    }

    Length += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR*)pgucAtSndCodeAddr+Length,
                                                    ",%d",
                                                    ProfileContent.ucTimer);

    gstAtSendData.usBufLen = Length;

    return AT_OK;
}

/*****************************************************************************
 Prototype      : At_QryStgiPara
 Description    :
 Input          : ucIndex --- 
 Output         :
 Return Value   : AT_XXX  --- ATC
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_QryStgiPara(TAF_UINT8 ucIndex)
{
    if(TAF_FALSE == g_ulSTKFunctionFlag)
    {
        return AT_ERROR;
    }

    if(AT_SUCCESS == SI_STK_QuerySTKCommand(gastAtClientTab[ucIndex].usClientId,USAT_CMDQRYSTGI))
    {
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}

/*****************************************************************************
     : At_QryImsichgPara
   : ^imsichg
   : TAF_UINT8 ucIndex
   : 
     : TAF_UINT32
   :
   :

       :
  1.Date        : 2010-02-11
    Author      : ---
    Modification: Created function
  2.       : 2011113
           : /l60609
       : STKAPIC

*****************************************************************************/
TAF_UINT32 At_QryImsichgPara(TAF_UINT8 ucIndex)
{
    /*Modified by l60609 for At Project, 2011-11-3, Begin */
    VOS_UINT32                          ulRst;

    if (VOS_FALSE == SI_STKIsDualImsiSupport())
    {
        return AT_CMD_NOT_SUPPORT;
    }

    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   DRV_AGENT_IMSICHG_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_WUEPS_PID_DRV_AGENT);

    if (TAF_SUCCESS == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_IMSICHG_READ;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
    /*Modified by l60609 for At Project, 2011-11-3, Begin */
}

/*****************************************************************************
 Prototype      : At_QryCgclassPara
 Description    :
 Input          : ucIndex --- 
 Output         :
 Return Value   : AT_XXX  --- ATC
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
  2.       : 20120303
           : s62952
       : BalongV300R002 Build:NAS_FEATURE_AT_COMMAND_CGCLASS
*****************************************************************************/
TAF_UINT32 At_QryCgclassPara(TAF_UINT8 ucIndex)
{
    /* Modified by s62952 for BalongV300R002 Build 2012-02-28, begin */
    VOS_UINT16                          usLength = 0;

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,"%s: ",g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,"\"A\"");

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
    /* Modified by s62952 for BalongV300R002 Build 2012-02-28, end */
}
/*****************************************************************************
 Prototype      : At_QryCopsPara
 Description    :
 Input          : ucIndex --- 
 Output         :
 Return Value   : AT_XXX  --- ATC
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function

  2.       : 2016122
           : h00313353
       : DTS2016012202418
*****************************************************************************/
TAF_UINT32 At_QryCopsPara(TAF_UINT8 ucIndex)
{
    /* CLAT+COPS */

    if(VOS_TRUE == TAF_MMA_QryCopsInfoReq(WUEPS_PID_AT, gastAtClientTab[ucIndex].usClientId, 0))
    {
        /*  */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_COPS_READ;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}

/*****************************************************************************
     : At_QryHplmnPara
   : ^HPLMN
   : TAF_UINT8 ucIndex
   : 
     : TAF_UINT32
   :
   :

       :
  1.       : 2015108
           : n00355355
       : 

*****************************************************************************/
VOS_UINT32 At_QryHplmnPara(VOS_UINT8 ucIndex)
{
    if(VOS_TRUE == TAF_MMA_QryApHplmnInfoReq(WUEPS_PID_AT, gastAtClientTab[ucIndex].usClientId, 0))
    {
        /*  */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_EHPLMN_LIST_QRY;
        return AT_WAIT_ASYNC_RETURN;
    }

    return AT_ERROR;
}

/*****************************************************************************
     : AT_QryDplmnListPara
   : ^DPLMNLIST
   : TAF_UINT8 ucIndex
   : 
     : TAF_UINT32
   :
   :

       :
  1.       : 2015108
           : n00355355
       : 

*****************************************************************************/
VOS_UINT32 AT_QryDplmnListPara(VOS_UINT8 ucIndex)
{
    if ( VOS_TRUE == TAF_MMA_QryDplmnListReq(WUEPS_PID_AT,
                                             gastAtClientTab[ucIndex].usClientId,
                                             0))
    {
        /*  */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_DPLMNLIST_QRY;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }

}


/* Added by s00217060 for PhaseI, 2016-8-22, begin */
/*****************************************************************************
     : AT_QryBorderInfoPara
   : AT^BORDERINFO?^BORDERINFO:<version>
   : VOS_UINT8 ucIndex
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 2016822
           : s00217060
       : 

*****************************************************************************/
VOS_UINT32 AT_QryBorderInfoPara(VOS_UINT8 ucIndex)
{
    if ( VOS_TRUE == TAF_MMA_QryBorderInfoReq(WUEPS_PID_AT,
                                             gastAtClientTab[ucIndex].usClientId,
                                             0))
    {
        /*  */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_BORDERINFO_QRY;
        return AT_WAIT_ASYNC_RETURN;
    }

    return AT_ERROR;
}
/* Added by s00217060 for PhaseI, 2016-8-22, end */
/*****************************************************************************
     : At_QryCampCsgIdInfo
   : csg id
   : ucIndex - 
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 20151116
           : z00161729
       : LTE CSG
  2.       : 20151124
           : s00193151
       : 
*****************************************************************************/
VOS_UINT32 At_QryCampCsgIdInfo(VOS_UINT8 ucIndex)
{
    if(VOS_TRUE == TAF_MMA_QryCampCsgIdInfoReq(WUEPS_PID_AT, gastAtClientTab[ucIndex].usClientId, 0))
    {
        /*  */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CSG_ID_INFO_QRY;
        return AT_WAIT_ASYNC_RETURN;
    }

    return AT_ERROR;

}


/*****************************************************************************
     : At_QryCgcattPara
   : CGCATT
   : 
   : 
     : ATC
   :
   :

       :
  1.       : 2005419
           : ---
       : 
  2.       : 2011930
           : C00173809
       : AT
  3.       : 20111024
           : c00173809
       : ATMMA API Taf_GetCurrentAttachStatus
  4.       : 201549
           : h00313353
       : SysCfg 
*****************************************************************************/
VOS_UINT32 At_QryCgcattPara(VOS_UINT8 ucIndex)
{


    /* ATMMAMMACSPS */
    if (VOS_TRUE == TAF_MMA_AttachStatusQryReq(WUEPS_PID_AT,
                                               gastAtClientTab[ucIndex].usClientId,
                                               gastAtClientTab[ucIndex].opId,
                                               TAF_MMA_SERVICE_DOMAIN_CS_PS))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_MMA_GET_CURRENT_ATTACH_STATUS;
        return AT_WAIT_ASYNC_RETURN;
    }
    return AT_ERROR;
    /* Added by c00173809 for AT Project2011-9-29 */
}
/*****************************************************************************
     : At_QryCgattPara
   : +CGATT
   : 
   : 
     : ATC
   :
   :

       :
  1.       : 2005419
           : ---
       : 
  2.       : 2011930
           : C00173809
       : AT
  3.       : 201549
           : h00313353
       : SysCfg 
*****************************************************************************/
VOS_UINT32 At_QryCgattPara(VOS_UINT8 ucIndex)
{


    /* ATMMAMMACSPS */
    if (VOS_TRUE == TAF_MMA_AttachStatusQryReq(WUEPS_PID_AT,
                                               gastAtClientTab[ucIndex].usClientId,
                                               gastAtClientTab[ucIndex].opId,
                                               TAF_MMA_SERVICE_DOMAIN_PS))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_MMA_GET_CURRENT_ATTACH_STATUS;
        return AT_WAIT_ASYNC_RETURN;
    }
    return AT_ERROR;
    /* Added by c00173809 for AT Project2011-9-29 */
}

/*****************************************************************************
 Prototype      : AT_QryCgdnsPara
 Description    :
 Input          : ucIndex --- 
 Output         :
 Return Value   : AT_XXX  --- ATC
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function

  2.       : 20111023
           : A00165503
       : PDP DNS

*****************************************************************************/
TAF_UINT32 AT_QryCgdnsPara(TAF_UINT8 ucIndex)
{
    /*  */
    if ( VOS_OK != TAF_PS_GetPdpDnsInfo(WUEPS_PID_AT,
                                        AT_PS_BuildExClientId(gastAtClientTab[ucIndex].usClientId),
                                        0) )
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGDNS_READ;

    return AT_WAIT_ASYNC_RETURN;
}

/*****************************************************************************
 Prototype      : AT_QryCgautoPara
 Description    :
 Input          : ucIndex --- 
 Output         :
 Return Value   : AT_XXX  --- ATC
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function

  2.       : 20111023
           : A00165503
       : 

*****************************************************************************/
TAF_UINT32 AT_QryCgautoPara(TAF_UINT8 ucIndex)
{
    /*  */
    if ( VOS_OK != TAF_PS_GetAnsModeInfo(WUEPS_PID_AT,
                                         AT_PS_BuildExClientId(gastAtClientTab[ucIndex].usClientId),
                                         0) )
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGAUTO_READ;

    return AT_WAIT_ASYNC_RETURN;
}

/*****************************************************************************
 Prototype      : AT_QryCgtftPara
 Description    :
 Input          : ucIndex --- 
 Output         :
 Return Value   : AT_XXX  --- ATC
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function

  2.       : 20111023
           : A00165503
       : TFT

*****************************************************************************/
TAF_UINT32 AT_QryCgtftPara(TAF_UINT8 ucIndex)
{
    /*  */
    if ( VOS_OK != TAF_PS_GetTftInfo(WUEPS_PID_AT,
                                     AT_PS_BuildExClientId(gastAtClientTab[ucIndex].usClientId),
                                     0) )
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGTFT_READ;

    return AT_WAIT_ASYNC_RETURN;
}

/*****************************************************************************
 Prototype      : AT_QryCgactPara
 Description    :
 Input          : ucIndex --- 
 Output         :
 Return Value   : AT_XXX  --- ATC
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function

  2.       : 20111023
           : A00165503
       : PDP

*****************************************************************************/
TAF_UINT32 AT_QryCgactPara(TAF_UINT8 ucIndex)
{
    /*  */
    if ( VOS_OK != TAF_PS_GetPdpContextState(WUEPS_PID_AT,
                                             AT_PS_BuildExClientId(gastAtClientTab[ucIndex].usClientId),
                                             0) )
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGACT_READ;

    return AT_WAIT_ASYNC_RETURN;
}

/*****************************************************************************
 Prototype      : AT_QryCgdcontPara
 Description    :
 Input          : ucIndex --- 
 Output         :
 Return Value   : AT_XXX  --- ATC
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function

  2.       : 20111023
           : A00165503
       : PDP

*****************************************************************************/
VOS_UINT32 AT_QryCgdcontPara(VOS_UINT8 ucIndex)
{
    /*  */
    if ( VOS_OK != TAF_PS_GetPrimPdpContextInfo(WUEPS_PID_AT,
                                                AT_PS_BuildExClientId(gastAtClientTab[ucIndex].usClientId),
                                                0) )
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGDCONT_READ;

    return AT_WAIT_ASYNC_RETURN;
}

/*****************************************************************************
 Prototype      : AT_QryCgeqreqPara
 Description    :
 Input          : ucIndex --- 
 Output         :
 Return Value   : AT_XXX  --- ATC
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function

  2.       : 20111023
           : A00165503
       : UMTS QOS

*****************************************************************************/
VOS_UINT32 AT_QryCgeqreqPara(VOS_UINT8 ucIndex)
{
    /*  */
    if ( VOS_OK != TAF_PS_GetUmtsQosInfo(WUEPS_PID_AT,
                                         AT_PS_BuildExClientId(gastAtClientTab[ucIndex].usClientId),
                                         0) )
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGEQREQ_READ;

    return AT_WAIT_ASYNC_RETURN;
}

/*****************************************************************************
 Prototype      : At_QryCgeqminPara
 Description    :
 Input          : ucIndex --- 
 Output         :
 Return Value   : AT_XXX  --- ATC
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function

  2.       : 20111023
           : A00165503
       : UMTS MIN QOS

*****************************************************************************/
VOS_UINT32 At_QryCgeqminPara(VOS_UINT8 ucIndex)
{
    /*  */
    if ( VOS_OK != TAF_PS_GetUmtsQosMinInfo(WUEPS_PID_AT,
                                            AT_PS_BuildExClientId(gastAtClientTab[ucIndex].usClientId),
                                            0) )
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGEQMIN_READ;

    return AT_WAIT_ASYNC_RETURN;
}
/*****************************************************************************
 Prototype      : AT_QryCgdscontPara
 Description    :
 Input          : ucIndex --- 
 Output         :
 Return Value   : AT_XXX  --- ATC
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function

  2.       : 20111023
           : A00165503
       : Secondary PDP

*****************************************************************************/
VOS_UINT32 AT_QryCgdscontPara(VOS_UINT8 ucIndex)
{
    /*  */
    if ( VOS_OK != TAF_PS_GetSecPdpContextInfo(WUEPS_PID_AT,
                                               AT_PS_BuildExClientId(gastAtClientTab[ucIndex].usClientId),
                                               0) )
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGDSCONT_READ;

    return AT_WAIT_ASYNC_RETURN;
}

/*****************************************************************************
 Prototype      : At_QryCrcPara
 Description    :
 Input          : ucIndex --- 
 Output         :
 Return Value   : AT_XXX  --- ATC
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function

  2.       : 20111024
           : o00132663
       : AT
  3.       : 2013225
           : l60609
       : DSDA PHASE III
*****************************************************************************/
TAF_UINT32 At_QryCrcPara(TAF_UINT8 ucIndex)
{
    /* Modified by l60609 for DSDA Phase III, 2013-2-25, Begin */
    AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;

    pstSsCtx = AT_GetModemSsCtxAddrFromClientId(ucIndex);

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR*)pgucAtSndCodeAddr,
                                                    "%s: %d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    pstSsCtx->ucCrcType);
    /* Modified by l60609 for DSDA Phase III, 2013-2-25, End */
    return AT_OK;
}

/*****************************************************************************
 Prototype      : At_QryCbstPara
 Description    :
 Input          : ucIndex --- 
 Output         :
 Return Value   : AT_XXX  --- ATC
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function

  2.       : 20111024
           : o00132663
       : AT
  3.       : 2013221
           : l60609
       : DSDA PHASE III
*****************************************************************************/
TAF_UINT32 At_QryCbstPara(TAF_UINT8 ucIndex)
{
    /* Modified by l60609 for DSDA Phase III, 2013-2-21, Begin */
    AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;

    pstSsCtx = AT_GetModemSsCtxAddrFromClientId(ucIndex);

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s: %d,%d,%d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    pstSsCtx->stCbstDataCfg.enSpeed,
                                                    pstSsCtx->stCbstDataCfg.enName,
                                                    pstSsCtx->stCbstDataCfg.enConnElem);
    /* Modified by l60609 for DSDA Phase III, 2013-2-21, End */

    return AT_OK;

}
/*****************************************************************************
 Prototype      : At_QryCmodPara
 Description    :
 Input          : ucIndex --- 
 Output         :
 Return Value   : AT_XXX  --- ATC
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function

  2.       : 20111024
           : o00132663
       : AT
  3.       : 2013221
           : l60609
       : DSDA PHASE III
*****************************************************************************/
TAF_UINT32 At_QryCmodPara(TAF_UINT8 ucIndex)
{
    /* Modified by l60609 for DSDA Phase III, 2013-2-21, Begin */
    AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;

    pstSsCtx = AT_GetModemSsCtxAddrFromClientId(ucIndex);

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR*)pgucAtSndCodeAddr,
                                                    "%s: %d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    pstSsCtx->enCModType);
    /* Modified by l60609 for DSDA Phase III, 2013-2-21, End */
    return AT_OK;
}

/*****************************************************************************
 Prototype      : At_QryCstaPara
 Description    :
 Input          : ucIndex --- 
 Output         :
 Return Value   : AT_XXX  --- ATC
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function

  2.       : 20111024
           : o00132663
       : AT
*****************************************************************************/
TAF_UINT32 At_QryCstaPara(TAF_UINT8 ucIndex)
{

    gstAtSendData.usBufLen  = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR*)pgucAtSndCodeAddr,"%s: %d",g_stParseContext[ucIndex].pstCmdElement->pszCmdName,g_enAtCstaNumType);

    return AT_OK;
}

/*****************************************************************************
 Prototype      : At_QryCcugPara
 Description    :
 Input          : ucIndex --- 
 Output         :
 Return Value   : AT_XXX  --- ATC
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function

  2.       : 20111024
           : o00132663
       : AT
  3.       : 2013221
           : l60609
       : DSDA PHASE III
*****************************************************************************/
TAF_UINT32 At_QryCcugPara(TAF_UINT8 ucIndex)
{
    TAF_UINT16                          usLength = 0;
    TAF_UINT16                          usIndex;
    TAF_UINT16                          usInfo;
    /* Modified by l60609 for DSDA Phase III, 2013-2-21, Begin */
    AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;

    pstSsCtx = AT_GetModemSsCtxAddrFromClientId(ucIndex);

    usIndex = (TAF_UINT16)pstSsCtx->stCcugCfg.ulIndex;

    usInfo = (TAF_UINT16)((pstSsCtx->stCcugCfg.bSuppressPrefer << 1) | pstSsCtx->stCcugCfg.bSuppressOA);

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,"%s: %d",g_stParseContext[ucIndex].pstCmdElement->pszCmdName,pstSsCtx->stCcugCfg.bEnable);
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,",%d",usIndex);
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,",%d",usInfo);

    /* Modified by l60609 for DSDA Phase III, 2013-2-21, End */

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}

/*****************************************************************************
 Prototype      : At_QryCssnPara
 Description    :
 Input          : ucIndex --- 
 Output         :
 Return Value   : AT_XXX  --- ATC
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function

  2.       : 20111024
           : o00132663
       : AT
  3.       : 2013225
           : l60609
       : DSDA PHASE III
  4.       : 201341
           : s00217060
       : ATC
*****************************************************************************/
TAF_UINT32 At_QryCssnPara(TAF_UINT8 ucIndex)
{
    /* Modified by s00217060 for ATC, 2013-4-1, begin */
    AT_MTA_UNSOLICITED_RPT_QRY_REQ_STRU     stAtCmd;
    VOS_UINT32                              ulResult;

    TAF_MEM_SET_S(&stAtCmd, sizeof(stAtCmd), 0x00, sizeof(AT_MTA_UNSOLICITED_RPT_QRY_REQ_STRU));
    stAtCmd.enReqType       = AT_MTA_QRY_CSSN_RPT_TYPE;

    /* MTA^cssn */
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   ID_AT_MTA_UNSOLICITED_RPT_QRY_REQ,
                                   &stAtCmd,
                                   sizeof(AT_MTA_UNSOLICITED_RPT_QRY_REQ_STRU),
                                   I0_UEPS_PID_MTA);

    if (TAF_SUCCESS != ulResult)
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_UNSOLICITED_RPT_READ;

    return AT_WAIT_ASYNC_RETURN;
    /* Modified by s00217060 for ATC, 2013-4-1, end */
}

/*****************************************************************************
 Prototype      : At_QryCnmiPara
 Description    :
 Input          : ucIndex --- 
 Output         :
 Return Value   : AT_XXX  --- ATC
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
  2.     : 20080418
         : f62575
     : CM

  3.       : 20111024
           : o00132663
       : AT
  3.       : 2013222
           : l60609
       : DSDA PHASE III
*****************************************************************************/
TAF_UINT32 At_QryCnmiPara(TAF_UINT8 ucIndex)
{
    TAF_UINT16                          usLength            = 0;
    /* Modified by l60609 for DSDA Phase III, 2013-2-22, Begin */
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;

    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(ucIndex);

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,"%s: %d",g_stParseContext[ucIndex].pstCmdElement->pszCmdName,pstSmsCtx->stCnmiType.CnmiModeType);
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR*)pgucAtSndCodeAddr + usLength,",%d",pstSmsCtx->stCnmiType.CnmiMtType);
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR*)pgucAtSndCodeAddr + usLength,",%d",pstSmsCtx->stCnmiType.CnmiBmType);
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR*)pgucAtSndCodeAddr + usLength,",%d",pstSmsCtx->stCnmiType.CnmiDsType);
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR*)pgucAtSndCodeAddr + usLength,",%d",pstSmsCtx->stCnmiType.CnmiBfrType);
    /* Modified by l60609 for DSDA Phase III, 2013-2-22, End */

    gstAtSendData.usBufLen = usLength;
    return AT_OK;
}

/*****************************************************************************
 Prototype      : At_QryCmgfPara
 Description    :
 Input          : ucIndex --- 
 Output         :
 Return Value   : AT_XXX  --- ATC
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
  2.     : 20080418
         : f62575
     : CM

  3.       : 20111024
           : o00132663
       : AT
  4.       : 2013225
           : l60609
       : DSDA PHASE III
*****************************************************************************/
TAF_UINT32 At_QryCmgfPara(TAF_UINT8 ucIndex)
{
    /* Modified by l60609 for DSDA Phase III, 2013-2-25, Begin */
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;

    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(ucIndex);

    gstAtSendData.usBufLen = 0;
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)(pgucAtSndCodeAddr + gstAtSendData.usBufLen),
                                                    "%s: %d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    pstSmsCtx->enCmgfMsgFormat);
    /* Modified by l60609 for DSDA Phase III, 2013-2-25, End */

    return AT_OK;
}

/* Modified by f62575 for AT Project2011-10-03,  Begin */
/*****************************************************************************
     : At_QryCscaPara
   : AT
   : VOS_UINT8 ucIndex  
   : 
     : VOS_UINT32 ATC
   :
   :

       :
  1.       : 2011103
           : f62575
       : 
  2.       : 2011103
           : f62575
       : AT Project 
                 MSG
*****************************************************************************/
VOS_UINT32 At_QryCscaPara(VOS_UINT8 ucIndex)
{
    /* Modified by f62575 for AT Project2011-10-03,  Begin*/
    VOS_UINT32                          ulRet;
    MN_MSG_READ_COMM_PARAM_STRU         stReadParam;

    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;
    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(ucIndex);

    /*   :
    ATSIMEFSMSP */

    stReadParam.ulIndex = (VOS_UINT32)pstSmsCtx->stCscaCsmpInfo.ucDefaultSmspIndex;

    stReadParam.enMemStore  = MN_MSG_MEM_STORE_SIM;
    TAF_MEM_SET_S(stReadParam.aucReserve1, sizeof(stReadParam.aucReserve1), 0x00, sizeof(stReadParam.aucReserve1));

    /* C */
    gastAtClientTab[ucIndex].opId = At_GetOpId();
    ulRet = MN_MSG_ReadSrvParam(gastAtClientTab[ucIndex].usClientId,
                                gastAtClientTab[ucIndex].opId,
                                &stReadParam);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        return AT_ERROR;
    }

    /* AT */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CSCA_READ;
    return AT_WAIT_ASYNC_RETURN;
    /* Modified by f62575 for AT Project2011-10-03,  End*/
}
/* Modified by f62575 for AT Project2011-10-03,  End */

/*****************************************************************************
 Prototype      : At_QryCsmsPara
 Description    :
 Input          : ucIndex --- 
 Output         :
 Return Value   : AT_XXX  --- ATC
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
  2.     : 20080418
         : f62575
     : CM
  3.       : 2013220
           : l60609
       : DSDA PHASE III
*****************************************************************************/
TAF_UINT32 At_QryCsmsPara(TAF_UINT8 ucIndex)
{
    /* Modified by l60609 for DSDA Phase III, 2013-2-20, Begin */
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;

    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(ucIndex);

    gstAtSendData.usBufLen = 0;
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)(pgucAtSndCodeAddr + gstAtSendData.usBufLen),
                                                    "%s: %d,",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    pstSmsCtx->enCsmsMsgVersion);
    /* Modified by l60609 for DSDA Phase III, 2013-2-20, End */
    At_PrintCsmsInfo(ucIndex);
    return AT_OK;
}

/*****************************************************************************
 Prototype      : At_QryCsmpPara
 Description    :
 Input          : ucIndex --- 
 Output         :
 Return Value   : AT_XXX  --- ATC
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
  2.     : 20080418
         : f62575
     : CM

  3.       : 201054
           : zhoujun /z40661
       : FOAT2D15352
  4.       : 2013222
           : L60609
       : DSDA PHASE III
  5.       : 20140304
           : f62575
       : DTS2014030801193, +CSMP
*****************************************************************************/
TAF_UINT32 At_QryCsmpPara(TAF_UINT8 ucIndex)
{
    TAF_UINT16                          usLength            = 0;
    /* Modified by l60609 for DSDA Phase III, 2013-2-22, Begin */
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;
    MN_MSG_VALID_PERIOD_ENUM_U8         enValidPeriod;                          /*TP Validity Period Format*/

    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(ucIndex);

    if (TAF_TRUE == pstSmsCtx->stCscaCsmpInfo.bFoUsed)
    {
        /* <fo> */
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%s: %d,",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                           pstSmsCtx->stCscaCsmpInfo.ucFo);

        AT_GET_MSG_TP_VPF(enValidPeriod, pstSmsCtx->stCscaCsmpInfo.ucFo);

        /* <vp> */
        if (enValidPeriod == pstSmsCtx->stCscaCsmpInfo.stVp.enValidPeriod)
        {
            usLength += At_MsgPrintVp(&(pstSmsCtx->stCscaCsmpInfo.stVp), (pgucAtSndCodeAddr + usLength));
        }

    }
    else
    {
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (TAF_CHAR *)pgucAtSndCodeAddr,
                                          (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                          "%s: ,",
                                          g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    }

    /* <pid>  <dcs> */
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (TAF_CHAR *)pgucAtSndCodeAddr,
                                       (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                       ",%d,%d",
                                       pstSmsCtx->stCscaCsmpInfo.stParmInUsim.ucPid,
                                       pstSmsCtx->stCscaCsmpInfo.stParmInUsim.ucDcs);
    /* Modified by l60609 for DSDA Phase III, 2013-2-22, End */
    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}
/*****************************************************************************
 Prototype      : At_QryCpmsPara
 Description    :
 Input          : ucIndex --- 
 Output         :
 Return Value   : AT_XXX  --- ATC
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
  2.Date        : 2007-11-09
    Author      : z40661
    Modification: A32D13393
  3.     : 20080418
         : f62575
     : CM
  4.       : 20101126
           : /f62575
       :  DTS2010112605152SMSCPMS
                 0+CMS ERROR: 500
  5.       : 2011112
           : /f62575
       : DTAS2011011200351 ORANGEPIN
  6.       : 2013222
           : l60609
       : DSDA PHASE III
*****************************************************************************/
TAF_UINT32 At_QryCpmsPara(TAF_UINT8 ucIndex)
{
    /* Modified by l60609 for DSDA Phase III, 2013-2-22, Begin */
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;

    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(ucIndex);

    if (AT_OK != At_GetSmsStorage(ucIndex,
                                  pstSmsCtx->stCpmsInfo.enMemReadorDelete,
                                  pstSmsCtx->stCpmsInfo.enMemSendorWrite,
                                  pstSmsCtx->stCpmsInfo.stRcvPath.enSmMemStore))
    {
        return AT_ERROR;
    }
    /* Modified by l60609 for DSDA Phase III, 2013-2-22, End */

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CPMS_READ;
    return AT_WAIT_ASYNC_RETURN;    /*  */
}

/*****************************************************************************
 Prototype      : At_QryCgsmsPara
 Description    :
 Input          : ucIndex --- 
 Output         :
 Return Value   : AT_XXX  --- ATC
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
  2.     : 20080418
         : f62575
     : CM
  3.       : 2013222
           : l60609
       : DSDA PHASE III
*****************************************************************************/
TAF_UINT32 At_QryCgsmsPara(TAF_UINT8 ucIndex)
{
    /* Modified by l60609 for DSDA Phase III, 2013-2-22, Begin */
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;

    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(ucIndex);

    gstAtSendData.usBufLen = 0;
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)(pgucAtSndCodeAddr + gstAtSendData.usBufLen),
                                                    "%s: %d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    pstSmsCtx->stCgsmsSendDomain.enSendDomain);
    /* Modified by l60609 for DSDA Phase III, 2013-2-22, End */

    return AT_OK;
}


/*****************************************************************************
 Prototype      : At_QryCmgdPara
 Description    : +CMGD=?
 Input          : ucIndex --- 
 Output         :
 Return Value   : AT_XXX  --- ATC
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2008-06-19
    Author      : ---
    Modification: Created function

  2.       : 20111024
           : o00132663
       : AT
  3.       : 2013220
           : L60609
       : DSDA PHASE III
*****************************************************************************/
TAF_UINT32 At_QryCmgdPara(TAF_UINT8 ucIndex)
{
    MN_MSG_LIST_PARM_STRU               stListPara;
    /* Added by l60609 for DSDA Phase III, 2013-2-20, Begin */
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;

    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(ucIndex);
    /* Added by l60609 for DSDA Phase III, 2013-2-20, End */

    TAF_MEM_SET_S(&stListPara, sizeof(MN_MSG_LIST_PARM_STRU), 0x00, sizeof(MN_MSG_LIST_PARM_STRU));

    stListPara.bChangeFlag = VOS_FALSE;
    /* Modified by l60609 for DSDA Phase III, 2013-2-20, Begin */
    stListPara.enMemStore  = pstSmsCtx->stCpmsInfo.enMemReadorDelete;
    /* Modified by l60609 for DSDA Phase III, 2013-2-20, End */
    stListPara.enStatus    = MN_MSG_STATUS_NONE;

    gastAtClientTab[ucIndex].opId = At_GetOpId();
    if (MN_ERR_NO_ERROR == MN_MSG_Delete_Test(gastAtClientTab[ucIndex].usClientId,
                                         gastAtClientTab[ucIndex].opId,
                                         &stListPara))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CMGD_TEST;
        g_stParseContext[ucIndex].ucClientStatus = AT_FW_CLIENT_STATUS_PEND;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}

/*****************************************************************************
     : At_QryCmmsPara
   : CMMS
   : TAF_UINT8 ucIndex
   : 
     : AT_XXX  --- ATC
   :
   :

       :
  1.       : 2008721
           : Fu Yingjun id:62575
       : 
*****************************************************************************/
TAF_UINT32 At_QryCmmsPara(
    TAF_UINT8                           ucIndex
)
{
    TAF_UINT32                          ulRet;

    gastAtClientTab[ucIndex].opId = At_GetOpId();
    ulRet = MN_MSG_GetLinkCtrl(gastAtClientTab[ucIndex].usClientId,
                               gastAtClientTab[ucIndex].opId);
    if (MN_ERR_NO_ERROR == ulRet)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CMMS_READ;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}


/*****************************************************************************
     : At_QryCscbPara
   : CSCB
   : VOS_UINT8       ucIndex
   : 
     : VOS_UINT32:
   :

       :
  1.       : 2010515
           : zhoujun /z40661
       : 
*****************************************************************************/
VOS_UINT32 At_QryCscbPara(
    VOS_UINT8                           ucIndex
)
{
    TAF_UINT32                          ulRet;

    gastAtClientTab[ucIndex].opId = At_GetOpId();

    ulRet = MN_MSG_GetAllCbMids(gastAtClientTab[ucIndex].usClientId,
                             gastAtClientTab[ucIndex].opId);
    if (MN_ERR_NO_ERROR == ulRet)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CSCB_READ;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}

/*****************************************************************************
 Prototype      : At_QryCgregPara
 Description    :
 Input          : ucIndex --- 
 Output         :
 Return Value   : AT_XXX  --- ATC
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function

  2.       : 2015327
           : g00261581
       : ID
*****************************************************************************/
TAF_UINT32 At_QryCgregPara(TAF_UINT8 ucIndex)
{
    if (VOS_TRUE == TAF_MMA_QryRegStateReq(WUEPS_PID_AT, gastAtClientTab[ucIndex].usClientId, 0, TAF_MMA_QRY_REG_STATUS_TYPE_PS))
    {
        /*  */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGREG_READ;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}

/*****************************************************************************
     : At_QryCeregPara
   : CEREG
   : ucIndex - 
   : 
     : AT_XXX  --- ATC
       :
  1.       : 2011125
           : z00161729
       : 

  2.       : 2015327
           : g00261581
       : ID
*****************************************************************************/
VOS_UINT32 At_QryCeregPara(VOS_UINT8 ucIndex)
{
    if (VOS_TRUE == TAF_MMA_QryRegStateReq(WUEPS_PID_AT, gastAtClientTab[ucIndex].usClientId, 0, TAF_MMA_QRY_REG_STATUS_TYPE_EPS))
    {
        /*  */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CEREG_READ;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}

/*****************************************************************************
 Prototype      : At_QryCregPara
 Description    :
 Input          : ucIndex --- 
 Output         :
 Return Value   : AT_XXX  --- ATC
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function

  2.       : 2015327
           : g00261581
       : ID
*****************************************************************************/
TAF_UINT32 At_QryCregPara(TAF_UINT8 ucIndex)
{
    if (VOS_TRUE == TAF_MMA_QryRegStateReq(WUEPS_PID_AT, gastAtClientTab[ucIndex].usClientId, 0, TAF_MMA_QRY_REG_STATUS_TYPE_CS))
    {
        /*  */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CREG_READ;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}
/*****************************************************************************
 Prototype      : At_QryCnmiPara
 Description    :
 Input          : ucIndex --- 
 Output         :
 Return Value   : AT_XXX  --- ATC
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
  2.       : 2013222
           : l60609
       : DSDA PHASE III
*****************************************************************************/
TAF_UINT32 At_QryCsdhPara(TAF_UINT8 ucIndex)
{
    /* Modified by l60609 for DSDA Phase III, 2013-2-22, Begin */
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;

    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(ucIndex);

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR*)pgucAtSndCodeAddr,
                                                    "%s: %d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    pstSmsCtx->ucCsdhType);
    /* Modified by l60609 for DSDA Phase III, 2013-2-22, End */

    return AT_OK;
}
/*****************************************************************************
 Prototype      : At_QryCscsPara
 Description    :
 Input          : ucIndex --- 
 Output         :
 Return Value   : AT_XXX  --- ATC
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function

  2.       : 20111024
           : o00132663
       : AT
*****************************************************************************/
TAF_UINT32 At_QryCscsPara(TAF_UINT8 ucIndex)
{
    if(AT_CSCS_IRA_CODE == gucAtCscsType)
    {
        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR*)pgucAtSndCodeAddr,"%s: \"IRA\"",g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    }
    else if (AT_CSCS_UCS2_CODE == gucAtCscsType)
    {
        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR*)pgucAtSndCodeAddr,"%s: \"UCS2\"",g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    }
    else
    {
        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR*)pgucAtSndCodeAddr,"%s: \"GSM\"",g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    }
    return AT_OK;
}

/*****************************************************************************
 Prototype      : At_QryCmeePara
 Description    :
 Input          : ucIndex --- 
 Output         :
 Return Value   : AT_XXX  --- ATC
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function

  2.       : 20111024
           : o00132663
       : AT
*****************************************************************************/
TAF_UINT32 At_QryCmeePara(TAF_UINT8 ucIndex)
{
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR*)pgucAtSndCodeAddr,"%s: %d",g_stParseContext[ucIndex].pstCmdElement->pszCmdName,gucAtCmeeType);
    return AT_OK;
}

/*****************************************************************************
 Prototype      : At_QryParaCmd
 Description    : 
 Input          : ucIndex --- 
 Output         :
 Return Value   : AT_XXX  --- ATC
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function

  2.       : 20111024
           : o00132663
       : AT
*****************************************************************************/
TAF_UINT32 At_QryParaCmd(TAF_UINT8 ucIndex)
{
    AT_RRETURN_CODE_ENUM_UINT32         ulResult = AT_FAILURE;

    if(TAF_NULL_PTR != g_stParseContext[ucIndex].pstCmdElement->pfnQryProc)
    {
        ulResult = (AT_RRETURN_CODE_ENUM_UINT32)g_stParseContext[ucIndex].pstCmdElement->pfnQryProc(ucIndex);

        if(AT_WAIT_ASYNC_RETURN == ulResult)
        {
            /*  */
            if(AT_SUCCESS != At_StartTimer(g_stParseContext[ucIndex].pstCmdElement->ulQryTimeOut,ucIndex))
            {
                AT_ERR_LOG("At_QryParaCmd:ERROR:Start Timer");
                return AT_ERROR;
            }

            g_stParseContext[ucIndex].ucClientStatus = AT_FW_CLIENT_STATUS_PEND;
        }
        return ulResult;
    }
    else
    {
        return AT_ERROR;
    }
}

/* BEGIN: Added by liuyang id:48197, 2006/8/2   PN:A32D02883*/

/*****************************************************************************
     : At_QryFPlmnPara
   : PLMN
   : TAF_UINT8 ucIndex
   : 
     : TAF_UINT32
   :
   :

       :
  17.       : 20080103
            : l00107747
        : A32D13994
*****************************************************************************/
TAF_UINT32 At_QryFPlmnPara(TAF_UINT8 ucIndex)
{
    if (VOS_TRUE == TAF_MMA_QryFPlmnInfo(WUEPS_PID_AT,
                                         gastAtClientTab[ucIndex].usClientId,0))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CFPLMN_READ;           /* */
        return AT_WAIT_ASYNC_RETURN;                                         /*  */
    }
    else
    {
        return AT_ERROR;                    /*  */

    }
}

/*****************************************************************************
     : At_QryMaxFreelockSizePara
   : 
   : VOS_UINT8 ucIndex
   : 
     : ,:byte
   :
   :

       :
  1.       : 2011316
           : z00161729
       : 
*****************************************************************************/
VOS_UINT32 At_QryMaxFreelockSizePara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRet;

    /* C MFREELOCKSIZE */
    ulRet = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   DRV_AGENT_MFREELOCKSIZE_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_WUEPS_PID_DRV_AGENT);
    if (TAF_SUCCESS != ulRet)
    {
        AT_WARN_LOG("At_QryMaxFreelockSizePara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* AT */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_MFREELOCKSIZE_READ;
    return AT_WAIT_ASYNC_RETURN;

/* Modified  by f62575 for AT Project, 2011-10-17, end */

}

/*****************************************************************************
     : At_QryCpuLoadPara
   : CPU
   : VOS_UINT8 ucIndex
   : 
     : CPU
   :
   :

       :
  1.       : 2011513
           : z00161729
       : DTS2011051601515
  2.       : 20111115
           : /f62575
       : CPULOAD&MFREELOCKSIZEC
*****************************************************************************/
VOS_UINT32 At_QryCpuLoadPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRet;

    /* C CPULOAD */
    ulRet = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   DRV_AGENT_CPULOAD_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_WUEPS_PID_DRV_AGENT);
    if (TAF_SUCCESS != ulRet)
    {
        AT_WARN_LOG("At_QryCpuLoadPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* AT */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CPULOAD_READ;
    return AT_WAIT_ASYNC_RETURN;

/* Modified  by f62575 for AT Project, 2011-10-17, end */

}

/*****************************************************************************
     : At_QryLcStartTimePara
   : 
   : VOS_UINT8 ucIndex
   : 
     : 
   :
   :

       :
  1.       : 2011316
           : z00161729
       : 
*****************************************************************************/
VOS_UINT32 At_QryLcStartTimePara(VOS_UINT8 ucIndex)
{
    /* Modified by s62952 for BalongV300R002 Build 2012-02-28, begin */
    VOS_UINT8                          *pucSystemAppConfig;

    pucSystemAppConfig                  = AT_GetSystemAppConfigAddr();



    if (SYSTEM_APP_WEBUI != *pucSystemAppConfig)
    {
        return AT_ERROR;
    }
    /* Modified by s62952 for BalongV300R002 Build 2012-02-28, end */

    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR*)pgucAtSndCodeAddr,
                                                    "%s:%d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    g_ulLcStartTime);
    return AT_OK;

}

/*****************************************************************************
     : At_QryDialModePara
   : (AT^DIALMODE)
   : TAF_UINT8 ucIndex
   : 
     : TAF_UINT32
   :
   :

       :
  01.       : 20081201
            : L47619
        : AT:AT^DIALMODE
  02.       : 20100629
            : o00132663
        : DTS2010062901078,
  03.       : 20120130
            : c00184452
        : DTS2012012903007,V7R1
  4.       : 20121213
           : L00171473
       : DTS2012121802573, TQE
*****************************************************************************/
TAF_UINT32 At_QryDialModePara(TAF_UINT8 ucIndex)
{
    VOS_UINT8   ucDialmode;
    VOS_UINT8   ucCdcSpec;
    VOS_UINT32  ulRst;

    /*  */
    /* ucRst:       VOS_OK/VOS_ERR */
    /* ucDialmode:  0 - Modem; 1 - NDIS; 2 - ModemNDIS */
    /* ucCdcSpec:   0 - Modem/NDISCDC; 1 - ModemCDC;
                    2 - NDISCDC;         3 - Modem/NDISCDC */


    ucDialmode = 0;
    ucCdcSpec  = 0;

    ulRst = (VOS_UINT32)DRV_GET_DIAG_MODE_VALUE(&ucDialmode, &ucCdcSpec);

    if (VOS_OK != ulRst)
    {
        AT_ERR_LOG("At_QryDialModePara:ERROR:DRV_GET_DIAG_MODE_VALUE Return Err!");
        return AT_ERROR;
    }

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR*)pgucAtSndCodeAddr,
                                                    "%s:%d,%d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    ucDialmode, ucCdcSpec);
    return AT_OK;
}


/*****************************************************************************
     : At_QryPortSelPara
   : PORTSEL 
   : TAF_UINT8 ucIndex
   : 
     : TAF_UINT32
   :
   :

       :
  1.       : 20081126
           : ouyang fei 00132663
       : AT2D06578 AT^PORTSELAT^HVERAT+CLAC 

*****************************************************************************/
TAF_UINT32 At_QryPortSelPara(TAF_UINT8 ucIndex)
{
    gstAtSendData.usBufLen =
        (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                               (TAF_CHAR*)pgucAtSndCodeAddr,
                               (TAF_CHAR*)pgucAtSndCodeAddr,
                               "%s: %d",
                               g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                               gucAtPortSel);
    return AT_OK;
}

/*****************************************************************************
     : At_QryCurcPara
   : 
   : TAF_UINT8 ucIndex
   : 
     : TAF_UINT32
   :
   :

       :
  1.       : 20090709
           : ouyang fei 00132663
       : AT2D12839 ^CURC

  2.       : 20111024
           : o00132663
       : AT

  3.       : 20120918
           : l00198894
       : STKDCM

  4.       : 2013220
           : l60609
       : DSDA Phase III
  5.       : 201341
           : s00217060
       : ATC
*****************************************************************************/
TAF_UINT32 At_QryCurcPara(TAF_UINT8 ucIndex)
{
    /* Modified by s00217060 for ATC, 2013-4-1, begin */
    VOS_UINT32                          ulResult;

    /* AT MTA CURC */
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                      gastAtClientTab[ucIndex].opId,
                                      ID_AT_MTA_CURC_QRY_REQ,
                                      VOS_NULL_PTR,
                                      0,
                                      I0_UEPS_PID_MTA);

    if (TAF_SUCCESS != ulResult)
    {
        AT_WARN_LOG("At_QryCurcPara: send Msg fail.");
        return AT_ERROR;
    }

    /*  */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CURC_READ;

    return AT_WAIT_ASYNC_RETURN;
    /* Modified by s00217060 for ATC, 2013-4-1, end */

}

/*****************************************************************************
     : At_QryTimePara
   : 
   : TAF_UINT8 ucIndex
   : 
     : TAF_UINT32
   :
   :

       :
  1.       : 20100323
           : ouyang fei 00132663
       : NAS R7 ^TIME

  2.       : 20111024
           : o00132663
       : AT
  3.       : 2013222
           : l60609
       : DSDA PHASE III
  4.       : 201343
           : s00217060
       : ATC
*****************************************************************************/
TAF_UINT32 At_QryTimePara(TAF_UINT8 ucIndex)
{
    /* Modified by s00217060 for ATC, 2013-4-1, begin */
    AT_MTA_UNSOLICITED_RPT_QRY_REQ_STRU     stAtCmd;
    VOS_UINT32                              ulResult;

    TAF_MEM_SET_S(&stAtCmd, sizeof(stAtCmd), 0x00, sizeof(AT_MTA_UNSOLICITED_RPT_QRY_REQ_STRU));
    stAtCmd.enReqType       = AT_MTA_QRY_TIME_RPT_TYPE;

    /* MTA^time */
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   ID_AT_MTA_UNSOLICITED_RPT_QRY_REQ,
                                   &stAtCmd,
                                   sizeof(AT_MTA_UNSOLICITED_RPT_QRY_REQ_STRU),
                                   I0_UEPS_PID_MTA);

    if (TAF_SUCCESS != ulResult)
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_UNSOLICITED_RPT_READ;

    return AT_WAIT_ASYNC_RETURN;
    /* Modified by s00217060 for ATC, 2013-4-1, end */
}

/*****************************************************************************
     : At_QryCtzrPara
   : 
   : TAF_UINT8 ucIndex
   : 
     : TAF_UINT32
   :
   :

       :
  1.       : 20100323
           : ouyang fei 00132663
       : NAS R7 ^TIME

  2.       : 20111024
           : o00132663
       : AT
  3.       : 2013222
           : l60609
       : DSDA PHASE III
  4.       : 201343
           : s00217060
       : ATC
 *****************************************************************************/
TAF_UINT32 At_QryCtzrPara(TAF_UINT8 ucIndex)
{
    /* Modified by s00217060 for ATC, 2013-4-1, begin */
    AT_MTA_UNSOLICITED_RPT_QRY_REQ_STRU     stAtCmd;
    VOS_UINT32                              ulResult;

    TAF_MEM_SET_S(&stAtCmd, sizeof(stAtCmd), 0x00, sizeof(AT_MTA_UNSOLICITED_RPT_QRY_REQ_STRU));
    stAtCmd.enReqType       = AT_MTA_QRY_CTZR_RPT_TYPE;

    /* MTA^ctzr */
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   ID_AT_MTA_UNSOLICITED_RPT_QRY_REQ,
                                   &stAtCmd,
                                   sizeof(AT_MTA_UNSOLICITED_RPT_QRY_REQ_STRU),
                                   I0_UEPS_PID_MTA);

    if (TAF_SUCCESS != ulResult)
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_UNSOLICITED_RPT_READ;

    return AT_WAIT_ASYNC_RETURN;
    /* Modified by s00217060 for ATC, 2013-4-1, begin */
}



/*****************************************************************************
     : At_QryQuickStart
   : 
   : TAF_UINT8 ucIndex
   : 
     : TAF_UINT32
   :
   :

       :
  1.       : 2007109
           : luojian id:107747
       : 

  2.       : 2015327
           : y00322978
       : CQST
*****************************************************************************/
VOS_UINT32 At_QryQuickStart(TAF_UINT8 ucIndex)
{
    if(VOS_TRUE == TAF_MMA_QryQuickStartReq(WUEPS_PID_AT,
                                            gastAtClientTab[ucIndex].usClientId,
                                            0))
    {
        /* */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CQST_READ;
        /*  */
        return AT_WAIT_ASYNC_RETURN;
    }

    else
    {
        /*  */
        return AT_ERROR;
    }
}
/*****************************************************************************
     : At_QryAutoAttach
   : 
   : TAF_UINT8 ucIndex
   : 
     : TAF_UINT32
   :
   :

       :
  1.       : 20080219
           : x00115505
       : 

  2.       : 2015328
           : g00261581
       : 

*****************************************************************************/
VOS_UINT32 At_QryAutoAttach(TAF_UINT8 ucIndex)
{
    if(VOS_TRUE == TAF_MMA_QryAutoAttachInfoReq(WUEPS_PID_AT, gastAtClientTab[ucIndex].usClientId, 0))
    {
        /*  */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CAATT_READ;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}

/*****************************************************************************
     : AT_QrySysCfgExPara
   : syscfgex
   : ucIndex - 
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 2011629
           : z00161729
       : 
  2.       : 20121213
           : L00171473
       : DTS2012121802573, TQE

  3.       : 2015326
           : y00322978
       : syscfgex 
    Taf_SysCfgHandle  ->  TAF_MMA_QrySyscfgReq
*****************************************************************************/
VOS_UINT32 AT_QrySysCfgExPara(VOS_UINT8 ucIndex)
{
    if (VOS_TRUE == TAF_MMA_QrySyscfgReq(WUEPS_PID_AT,
                                         gastAtClientTab[ucIndex].usClientId,
                                         0))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_SYSCFGEX_READ;             /* */
        return AT_WAIT_ASYNC_RETURN;                                            /*  */
    }
    else
    {
        return AT_ERROR;
    }

}



/*****************************************************************************
     : At_QrySysCfgPara
   :
   : TAF_UINT8 ucIndex
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 2008421
           : luojian id:107747
       : 
  2.       : 20121213
           : L00171473
       : DTS2012121802573, TQE

  3.       : 2014213
           : w00167002
       : L-C:SYSCFG

  4.       : 2015326
           : y00322978
       : syscfg 
    Taf_SysCfgHandle  ->  TAF_MMA_QrySyscfgReq
*****************************************************************************/
TAF_UINT32 At_QrySysCfgPara(TAF_UINT8 ucIndex)
{

    if (VOS_TRUE == TAF_MMA_QrySyscfgReq(WUEPS_PID_AT,
                                         gastAtClientTab[ucIndex].usClientId,
                                         0))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_SYSCFG_READ;             /* */
        return AT_WAIT_ASYNC_RETURN;                                            /*  */
    }
    else
    {
        return AT_ERROR;
    }
}


/* Add by w00199382 for V7, 2012-04-07, Begin   */
/*****************************************************************************
     : At_QryCemode
   :ue
   : TAF_UINT8 ucIndex
   : 
     : TAF_UINT32
   :
   :

       :
  1.       : 2012423
           :  w00182550
       : 

*****************************************************************************/
TAF_UINT32 At_QryCemode(TAF_UINT8 ucIndex)
{
    if (AT_SUCCESS == TAF_PS_GetCemodeInfo(WUEPS_PID_AT,
                                           AT_PS_BuildExClientId(gastAtClientTab[ucIndex].usClientId),
                                           0))
    {

        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CEMODE_READ;             /* */
        return AT_WAIT_ASYNC_RETURN;                                            /*  */
    }
    else
    {
        (VOS_VOID)vos_printf(" At_QryCemode TAF_PS_GetCemodeInfo fail\n");
        return AT_ERROR;
    }
}

/*****************************************************************************
     : At_QryLtecsInfo
   :LTE 
                          CS
   : TAF_UINT8 ucIndex
   : 
     : TAF_UINT32
   :
   :

       :
  1.       : 2012423
           : w00199382
       : 

*****************************************************************************/
TAF_UINT32 At_QryLtecsInfo(TAF_UINT8 ucIndex)
{

    if(AT_SUCCESS == TAF_PS_GetLteCsInfo(WUEPS_PID_AT,
                                         AT_PS_BuildExClientId(gastAtClientTab[ucIndex].usClientId),
                                         0))
    {
        /*  */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_LTECS_READ;

        /*  */
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}
/* Add by w00199382 for V7, 2012-04-07, End   */
/*****************************************************************************
 Prototype      : At_QryClvlPara
 Description    : +CLVL?
 Input          : ucIndex --- 
 Output         :
 Return Value   : AT_XXX  --- ATC
 Calls          :
 Called By      :

 History        :
  1.Date        : 2007-07-11
    Author      : d49431
    Modification: Created function

  2.     : 2010-10-21
         : z00161729
     : :DTS2010101802261,,

  3.       : 20111024
           : o00132663
       : AT
  4.       : 20111006
           : f00179208
       : AT, TAF_UINT8VOS_UINT8
  5.       : 20120303
           : s62952
       : BalongV300R002 Build:NAS_FEATURE_CS_VC
  6.       : 2012510
           : l60609
       : DTS2011102400120:AT+CLVLNV
*****************************************************************************/
VOS_UINT32 At_QryClvlPara(VOS_UINT8 ucIndex)
{
    if (VOS_OK == APP_VC_GetVoiceVolume(gastAtClientTab[ucIndex].usClientId, 0))
    {
        /*  */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CLVL_READ;
        return AT_WAIT_ASYNC_RETURN;    /*  */
    }
    else
    {
        return AT_ERROR;
    }
}

/*****************************************************************************
     : At_QryVMSETPara
   : 
   : TAF_UINT8 ucIndex
   : 
     : TAF_UINT32
   :
   :

       :
  1.       : 20070711
           : d49431
       : 

  2.       : 20111005
           : f00179208
       : ATAPI
  3.       : 20111006
           : f00179208
       : AT, TAF_UINT8VOS_UINT8
  5.       : 20120303
           : s62952
       : BalongV300R002 Build:NAS_FEATURE_CS_VC
*****************************************************************************/
VOS_UINT32 At_QryVMSETPara(VOS_UINT8 ucIndex)
{
    /*  */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /*0 1 2 3 4 5 PC */
    if (VOS_OK == APP_VC_GetVoiceMode(gastAtClientTab[ucIndex].usClientId, 0))
    {
        /*  */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_VMSET_READ;
        return AT_WAIT_ASYNC_RETURN;    /*  */
    }
    else
    {
        return AT_ERROR;
    }

}

/*****************************************************************************
 Prototype      : At_QryRRCVersion
 Description    : UE  (0: R4,1:R5,2:R6)
 Input          : ucIndex --- 
 Output         :
 Return Value   : AT_XXX  --- ATC
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2008-04-07
    Author      : C29528
    Modification: Created function

  2.       : 20111024
           : o00132663
       : AT
  3.       : 20121226
           : m00217266
       : DSDA C(MTA)
*****************************************************************************/
TAF_UINT32 At_QryRRCVersion(TAF_UINT8 ucIndex)
{
    VOS_UINT32                          ulRst;


    /* ID_AT_MTA_WRR_RRC_VERSION_QRY_REQAT */
    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   ID_AT_MTA_WRR_RRC_VERSION_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_UEPS_PID_MTA);

    if (TAF_SUCCESS == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_RRC_VERSION_QUERY;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}

/*****************************************************************************
 Prototype      : At_QryCSNR
 Description    : 
 Input          : ucIndex --- 
 Output         :
 Return Value   : AT_XXX  --- ATC
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2008-04-15
    Author      : C29528
    Modification: Created function

  2.       : 20111018
           : o00132663
       : ATAPI

  3.       : 2015328
           : y00322978
       : CSNR
    Taf_ParaQuery -> TAF_MMA_QryCsnrReq

  4.       : 20151225
           : n00355355
       : ChicagoWCDMAATMTA
*****************************************************************************/
TAF_UINT32 At_QryCSNR(TAF_UINT8 ucIndex)
{
    VOS_UINT32                          ulRst;

    /*  ID_AT_MTA_WRR_ANQUERY_QRY_REQ  MTA  */
    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   ID_AT_MTA_CSNR_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_UEPS_PID_MTA);

    if (AT_SUCCESS == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CSNR_QUERY;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }

}


/*****************************************************************************
 Prototype      : At_QryFreqLock
 Description    : 
 Input          : ucIndex --- 
 Output         :
 Return Value   : AT_XXX  --- ATC
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2008-04-15
    Author      : C29528
    Modification: Created function

  2.       : 2009-03-24
           : l00130025
       : :AT2D00246/AT2D10314/AT2D00315, ^freqlock

  3.       : 20111018
           : o00132663
       : ATAPI
  4.       : 20121226
           : m00217266
       : DSDA C(MTA)
*****************************************************************************/
TAF_UINT32 At_QryFreqLock(TAF_UINT8 ucIndex)
{
    VOS_UINT32                          ulRst;


    /* ID_AT_MTA_WRR_FREQLOCK_QRY_REQAT */
    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   ID_AT_MTA_WRR_FREQLOCK_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_UEPS_PID_MTA);

    if (TAF_SUCCESS == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_FREQLOCK_QUERY;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }

}


/*****************************************************************************
 Prototype      : At_QryU2DiagPara
 Description    : AT^U2DIAG?   USB
 Input          : ucIndex --- 
 Output         :
 Return Value   :
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2009-06-27
    Author      : L47619
    Modification: Created function

  2.       : 20111024
           : o00132663
       : AT
  3.       : 20120510
           : f62575
       : DTS2012050704264NV31U2DIAG
  4.       : 2012810
           : L00171473
       : DTS2012082204471, TQE
*****************************************************************************/
TAF_UINT32 At_QryU2DiagPara(TAF_UINT8 ucIndex)
{
    AT_USB_ENUM_STATUS_STRU             stUsbEnumStatus;
    AT_PID_ENABLE_TYPE_STRU             stPidEnableType;


    stPidEnableType.ulPidEnabled = VOS_FALSE;

    TAF_MEM_SET_S(&stUsbEnumStatus, sizeof(stUsbEnumStatus), 0x00, sizeof(stUsbEnumStatus));


    /* PIDNV */
    if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_PID_Enable_Type,
                        &stPidEnableType,
                        sizeof(AT_PID_ENABLE_TYPE_STRU)))
    {
        return AT_ERROR;
    }

    /* NVPIDERROR */
    if (VOS_FALSE != stPidEnableType.ulPidEnabled)
    {
        return AT_ERROR;
    }

    if(NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_USB_Enum_Status,
                         &stUsbEnumStatus,
                         sizeof(AT_USB_ENUM_STATUS_STRU)))
    {
        return AT_ERROR;
    }

    if (0 == stUsbEnumStatus.ulStatus)
    {
        /* en_NV_Item_USB_Enum_StatusAPIUSB */
        stUsbEnumStatus.ulValue = DRV_GET_U2DIAG_DEFVALUE();
    }

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s: %d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    stUsbEnumStatus.ulValue);
    return AT_OK;
}

/*****************************************************************************
     : At_QryPort
   : AT^SETPORT?
   : VOS_UINT8 ucIndex
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 2010429
           : l60609
       : 

  2.       : 20111024
           : o00132663
       : AT
  3.       : 2012023
           : f62575
       : B050 
                 DIAGDIAG
                 NVen_NV_Item_PID_Enable_Type
  4.       : 2012810
           : L00171473
       : DTS2012082204471, TQE
*****************************************************************************/
VOS_UINT32 At_QryPort(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          i;
    VOS_UINT32                          j;
    VOS_UINT16                          usLength;
    VOS_UINT8                           ucCount;
    VOS_UINT32                          ulResult;
    DRV_DYNAMIC_PID_TYPE_STRU           stDynamicPidType;
    /* Modified by f62575 for B050 Project, 2012-2-3, Begin   */
    AT_PID_ENABLE_TYPE_STRU             stPidEnableType;
    /* Modified by f62575 for B050 Project, 2012-2-3, end   */

    usLength = 0;
    ucCount  = 0;


    stPidEnableType.ulPidEnabled = VOS_FALSE;


    TAF_MEM_SET_S(&stDynamicPidType, sizeof(stDynamicPidType), 0x00, sizeof(DRV_DYNAMIC_PID_TYPE_STRU));

    /* Modified by f62575 for B050 Project, 2012-2-3, Begin   */
    /* PIDNV */
    if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_PID_Enable_Type,
                        &stPidEnableType,
                        sizeof(AT_PID_ENABLE_TYPE_STRU)))
    {
        AT_ERR_LOG("At_QryPort:Read NV fail!");
        return AT_ERROR;
    }

    /* NVPIDERROR */
    if (VOS_TRUE != stPidEnableType.ulPidEnabled)
    {
        AT_WARN_LOG("At_QryPort:The PID is not enabled!");
        return AT_ERROR;
    }
    /* Modified by f62575 for B050 Project, 2012-2-3, end   */

    /*  */
    ulResult = DRV_SET_PORT_QUIRY(&stDynamicPidType);
    if (AT_SUCCESS != ulResult)
    {
        AT_ERR_LOG("At_QryPort:Qry the pot type fail!");
        return AT_ERROR;
    }

    /* ^SETPORT: */
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                    (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                    "%s:",
                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    /* OLD PORT */
    for (i = 0; i< AT_SETPORT_PARA_MAX_LEN; i++)
    {
        for (j = 0; j < AT_SETPORT_DEV_MAP_LEN; j++)
        {
            if (stDynamicPidType.aucFirstPortStyle[i] == g_astSetPortParaMap[j].ucDrvPara)
            {
                /* 1: */
                if (ucCount > 0)
                {
                    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                    ",");
                }

                /*  */
                usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                (VOS_CHAR *)pgucAtSndCodeAddr,
                                                (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                "%s",
                                                g_astSetPortParaMap[j].aucAtSetPara);

                ucCount++;
                break;
            }
        }
    }

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                    (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                    ";");

    ucCount = 0;

    /* CUR PORT */
    for (i = 0; i< AT_SETPORT_PARA_MAX_LEN; i++)
    {
        for (j = 0; j < AT_SETPORT_DEV_LEN; j++)
        {
            if (stDynamicPidType.aucRewindPortStyle[i] == g_astSetPortParaMap[j].ucDrvPara)
            {
                /* 1: */
                if (ucCount > 0)
                {
                    /*  */
                    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                    ",");
                }

                /*  */
                usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                (VOS_CHAR *)pgucAtSndCodeAddr,
                                                (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                "%s",
                                                g_astSetPortParaMap[j].aucAtSetPara);

                ucCount++;

                break;
            }
        }
    }

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}

/*****************************************************************************
     : At_QryPcscInfo
   : AT^PCSCINFO? (PCSC)
   : TAF_UINT8 ucIndex
   : 
     : TAF_UINT32
   :
   :

       :
  1.       : 20100319
           : L60609
       : 

  2.       : 20111024
           : o00132663
       : AT

  3.       : 2012320
           : l60609
       : B070 Project:NV

*****************************************************************************/
TAF_UINT32 At_QryPcscInfo(TAF_UINT8 ucIndex)
{
    VOS_UINT32                          ulPortState;

    /*PCSC , 0 ; 1 */
    if (VOS_TRUE == AT_ExistSpecificPort(AT_DEV_PCSC))
    {
        ulPortState = VOS_TRUE;
    }
    else
    {
        ulPortState = VOS_FALSE;
    }

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR*)pgucAtSndCodeAddr,
                                                    "%s:%d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    ulPortState);
    return AT_OK;
}

/*****************************************************************************
     : At_QryCellSearch
   : AT^CELLSRCH? ()
   : TAF_UINT8 ucIndex
   : 
     : TAF_UINT32
   :
   :

       :
  1.       : 20100603
           : s46746
       : 
  2.       : 20111014
           : c00173809
       : AT WASAPI
  3.       : 20121226
           : m00217266
       : DSDA C(MTA)
*****************************************************************************/
VOS_UINT32 At_QryCellSearch(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRst;

    /*  ID_AT_MTA_WRR_CELLSRH_QRY_REQ  DRV AGENT  */
    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   ID_AT_MTA_WRR_CELLSRH_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_UEPS_PID_MTA);

    if(AT_SUCCESS == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_WAS_MNTN_QRY_CELLSRH;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}


/*****************************************************************************
 Prototype      : At_QryGetportmodePara
 Description    :
 Input          : ucIndex --- 
 Output         :
 Return Value   : AT_XXX  --- ATC
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2009-07-13
    Author      : S62952
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_QryGetportmodePara (TAF_UINT8 ucIndex)
{
     /*ERROR*/
     return AT_ERROR;
}

/*****************************************************************************
     : At_QryCvoicePara
   : 
   : TAF_UINT8 ucIndex
   : 
     : TAF_UINT32
   :
   :

       :
  1.       : 20090713
           : S62952
       : 

  2.       : 20111006
           : f00179208
       : ATAPI
  3.       : 20120303
           : s62952
       : BalongV300R002 Build:NAS_FEATURE_CS_VC
*****************************************************************************/
VOS_UINT32 At_QryCvoicePara (VOS_UINT8 ucIndex)
{
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /*0 1 2 3 4  */
    if (VOS_OK == APP_VC_GetVoiceMode(gastAtClientTab[ucIndex].usClientId, 0))
    {
        /*  */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CVOICE_READ;
        return AT_WAIT_ASYNC_RETURN;    /*  */
    }
    else
    {
        return AT_ERROR;
    }

}


/*****************************************************************************
     : At_QryDdsetexPara
   : 
   : TAF_UINT8 ucIndex
   : 
     : TAF_UINT32
   :
   :

       :
  1.       : 20090713
           : S62952
       : 

  2.       : 20111006
           : f00179208
       : ATAPI
  3.       : 20120303
           : s62952
       : BalongV300R002 Build:NAS_FEATURE_CS_VC

*****************************************************************************/
VOS_UINT32 At_QryDdsetexPara(VOS_UINT8 ucIndex)
{
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if (VOS_OK == APP_VC_GetVoicePort(gastAtClientTab[ucIndex].usClientId, 0))
    {
        /*  */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_DDSETEX_READ;
        return AT_WAIT_ASYNC_RETURN;    /*  */
    }
    else
    {
        return AT_ERROR;
    }
}

/*****************************************************************************
 Prototype      : At_QryCmsrPara
 Description    : ^CMSR?
 Input          : ucIndex --- 
 Output         :
 Return Value   : AT_XXX  --- ATC
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2009-07-13
    Author      : S62952
    Modification: Created function
  2.       : 2013220
           : l60609
       : DSDA PHASE III
*****************************************************************************/
TAF_UINT32 At_QryCmsrPara(TAF_UINT8 ucIndex)
{
    /* Modified by l60609 for DSDA Phase III, 2013-2-20, Begin */
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;

    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(ucIndex);

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR*)pgucAtSndCodeAddr,
                                                    "%s: %d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    pstSmsCtx->ucParaCmsr);
    /* Modified by l60609 for DSDA Phase III, 2013-2-20, End */
    return AT_OK;
}


/*****************************************************************************
     : At_QryUssdModePara
   : (AT^USSDMODE)ussd
   : TAF_UINT8 ucIndex
   : 
     : TAF_UINT32
   :
   :

       :
  1.       : 20090623
           : S62952
       : AT:AT^USSDMODE
  2.       : 2013225
           : l60609
       : DSDA PHASE III
*****************************************************************************/
TAF_UINT32 At_QryUssdModePara(TAF_UINT8 ucIndex)
{
    /* Modified by l60609 for DSDA Phase III, 2013-2-25, Begin */
    AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;

    pstSsCtx = AT_GetModemSsCtxAddrFromClientId(ucIndex);

    /* 0USSDUSSD1USSDUSSD)*/
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR*)pgucAtSndCodeAddr,
                                                    "%s: %d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    pstSsCtx->usUssdTransMode);
    /* Modified by l60609 for DSDA Phase III, 2013-2-25, End */

    return AT_OK;
}

/*****************************************************************************
     : At_QryAdcTempPara
   : (AT^ADCTEMP)
   : TAF_UINT8 ucIndex
   : 
     : TAF_UINT32
   :
   :

       :
  01.       : 20090813
            : m00128685
        : AT:AT^ADCTEMP
   2.       : 2012810
            : L00171473
        : DTS2012082204471, TQE
*****************************************************************************/
TAF_UINT32 At_QryAdcTempPara(TAF_UINT8 ucIndex)
{
    SPY_TEMP_PROTECT_NV_STRU stTempProtectNv;


    TAF_MEM_SET_S(&stTempProtectNv, sizeof(stTempProtectNv), 0x00, sizeof(stTempProtectNv));


    /*NV*/
    if(NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_USIM_TEMP_PROTECT_NEW,
                        (VOS_VOID*)&stTempProtectNv,
                        sizeof(SPY_TEMP_PROTECT_NV_STRU)))
    {
        AT_ERR_LOG("Spy_SetTempPara: NV_ReadEx en_NV_Item_USIM_TEMP_PROTECT Fail!");

        return AT_ERROR;
    }

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                (TAF_CHAR *)pgucAtSndCodeAddr,
                                                (TAF_CHAR*)pgucAtSndCodeAddr,
                                                "^ADCTEMP: %d,%d,%d,%d",
                                                stTempProtectNv.ulIsEnable,
                                                stTempProtectNv.lCloseAdcThreshold,
                                                stTempProtectNv.lAlarmAdcThreshold,
                                                stTempProtectNv.lResumeAdcThreshold);

    return AT_OK;
}

/*****************************************************************************
     : At_QryCommDebugPara
   : OAMAT
   : TAF_UINT8 ucIndex
   : 
     : TAF_UINT32
   :
   :

       :
  01.       : 20090813
            : m00128685
        : AT:AT^COMM
  2.       : 20121213
           : L00171473
       : DTS2012121802573, TQE
  3.       : 20130517
           : m00217266
       : nv
*****************************************************************************/
TAF_UINT32 At_QryCommDebugPara(TAF_UINT8 ucIndex)
{
    TAF_AT_NVIM_COMMDEGBUG_CFG_STRU     stDebugFlag;


    stDebugFlag.ulCommDebugFlag = 0;

    if(NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_COMMDEGBUG_CFG,
                        (VOS_VOID*)&(stDebugFlag.ulCommDebugFlag),
                        sizeof(TAF_AT_NVIM_COMMDEGBUG_CFG_STRU)))
    {
        AT_ERR_LOG("At_QryOamDebugPara: NV_ReadEx en_NV_Item_USIM_TEMP_PROTECT Fail!");

        return AT_ERROR;
    }

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                (TAF_CHAR *)pgucAtSndCodeAddr,
                                                (TAF_CHAR *)pgucAtSndCodeAddr,
                                                "^COMM: 0x%X", stDebugFlag.ulCommDebugFlag);

    return AT_OK;
}

/*****************************************************************************
 Prototype      : At_QryDwinsPara
 Description    : ^DWINS?   WINS
 Input          : ucIndex --- 
 Output         :
 Return Value   :
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2009-07-11
    Author      : L47619
    Modification: Created function
  2.       : 2012810
           : L00171473
       : DTS2012082204471, TQE
  2.       : 2013517
           : l00167671
       : NV, NV
*****************************************************************************/
TAF_UINT32 At_QryDwinsPara(TAF_UINT8 ucIndex)
{
    WINS_CONFIG_STRU    stWins;
    VOS_UINT32          ulLength;

    ulLength = 0;


    TAF_MEM_SET_S(&stWins, sizeof(stWins), 0x00, sizeof(stWins));

    (VOS_VOID)NV_GetLength(en_NV_Item_WINS_Config, &ulLength);
    if(NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_WINS_Config, &stWins, ulLength))
    {
        return AT_ERROR;
    }

    if (0 == stWins.ucStatus)
    {
        /* en_NV_Item_WINSWINS */
        stWins.ucWins = WINS_CONFIG_ENABLE;
    }

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s: %d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    stWins.ucWins);
    return AT_OK;
}

/*****************************************************************************
 Prototype      : At_QryYjcxPara
 Description    : ^Yjcx?   WINS
 Input          : ucIndex --- 
 Output         :
 Return Value   :
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2009-08-07
    Author      : S62952
    Modification: Created function

  2.       : 20111024
           : o00132663
       : ATDRV APIDRV_GET_GPIO_INFO
*****************************************************************************/
TAF_UINT32 At_QryYjcxPara(TAF_UINT8 ucIndex)
{
    VOS_UINT32                          ulRst;


    /* DRV_AGENT_YJCX_QRY_REQAT */
    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   DRV_AGENT_YJCX_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_WUEPS_PID_DRV_AGENT);

    if (VOS_OK == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_YJCX_QUERY;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }

}

/*****************************************************************************
 Prototype      : At_QryCplsPara
 Description    : AT+CPLS?   CPLS
 Input          : ucIndex --- 
 Output         :
 Return Value   :
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2009-08-19
    Author      : z40661
    Modification: Created function
  2.       : 2013222
           : l60609
       : DSDA PHASE III
*****************************************************************************/
VOS_UINT32 At_QryCplsPara(VOS_UINT8 ucIndex)
{
    /* Modified by l60609 for DSDA Phase III, 2013-2-22, Begin */
    AT_MODEM_NET_CTX_STRU              *pstNetCtx = VOS_NULL_PTR;

    pstNetCtx = AT_GetModemNetCtxAddrFromClientId(ucIndex);

    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR*)pgucAtSndCodeAddr,
                                                    "%s: %d",g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    pstNetCtx->enPrefPlmnType);
    /* Modified by l60609 for DSDA Phase III, 2013-2-22, End */

    return AT_OK;

}

/*****************************************************************************
 Prototype      : At_QryCpolPara
 Description    : AT+CPOL?   CPOL
 Input          : ucIndex --- 
 Output         :
 Return Value   :
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2009-08-19
    Author      : z40661
    Modification: Created function
  2.       : 2013222
           : l60609
       : DSDA PHASE III
  3.       : 20140115
           : f62575
       : DTS2014011301359+CPOL37UPLMN
  4.       : 201523
           : y00307564
       : Iteration 8
  5.       : 2015312
           : z00161729
       : AT&T EONS
*****************************************************************************/
TAF_UINT32 At_QryCpolPara(TAF_UINT8 ucIndex)
{
    VOS_UINT32                          ulRet;
    AT_MODEM_NET_CTX_STRU              *pstNetCtx = VOS_NULL_PTR;
    TAF_MMA_CPOL_INFO_QUERY_REQ_STRU    stCpolInfo;

    /*  */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    /*
    ATMMA:
    37
    037
    */
    pstNetCtx = AT_GetModemNetCtxAddrFromClientId(ucIndex);

    TAF_MEM_SET_S(&stCpolInfo, sizeof(stCpolInfo), 0x00, sizeof(stCpolInfo));

    stCpolInfo.enPrefPLMNType   = pstNetCtx->enPrefPlmnType;
    stCpolInfo.ulFromIndex      = 0;

    stCpolInfo.ulPlmnNum        = TAF_MMA_MAX_PLMN_NAME_LIST_NUM;

    /* MMA */
    ulRet = TAF_MMA_QueryCpolReq(WUEPS_PID_AT,
                                 gastAtClientTab[ucIndex].usClientId,
                                 0,
                                 &stCpolInfo);
    if (VOS_TRUE != ulRet)
    {
        return AT_ERROR;
    }


    /* AT */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CPOL_READ;

    return AT_WAIT_ASYNC_RETURN;

}

/*****************************************************************************
 Prototype      : AT_QryAuthdataPara
 Description    : ^AUTHDATA?
 Input          : ucIndex --- 
 Output         :
 Return Value   :
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2009-08-27
    Author      : L47619
    Modification: Created function

  2.       : 20111020
           : A00165503
       : AT Project: AUTHDATA

*****************************************************************************/
TAF_UINT32 AT_QryAuthdataPara(TAF_UINT8 ucIndex)
{
    if ( VOS_OK != TAF_PS_GetAuthDataInfo(WUEPS_PID_AT,
                                          AT_PS_BuildExClientId(gastAtClientTab[ucIndex].usClientId),
                                          0) )
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_AUTHDATA_READ;

    return AT_WAIT_ASYNC_RETURN;
}



/*****************************************************************************
     : AT_QryIpv6CapPara
   : IPv6
             <CR><LF>^ IPV6CAP: <value> <CR><LF>
             <CR><LF>OK<CR><LF>
             value:0~0xFF,
             0x01:IPV4 ONLY
             0x02:IPV6 ONLY
             0x04 IPV4V6 support enabled over one IPV4V6 context
             (fallbacking on 2 single address PDP contexts if necessary)
             0x08 IPV4V6 support enabled over 2 single address PDP
   : VOS_UINT8 ucIndex
   : 
     : VOS_ERRVOS_OK
   :
   :

       :
  1.       : 201161
           : x00180552
       : 

*****************************************************************************/
VOS_UINT32 AT_QryIpv6CapPara(VOS_UINT8 ucIndex)
{
    VOS_UINT8                           ucIpv6Capability;

    switch (AT_GetIpv6Capability())
    {
        case AT_IPV6_CAPABILITY_IPV4_ONLY:
            ucIpv6Capability = AT_IPV6_CAPABILITY_IPV4_ONLY;
            break;

        case AT_IPV6_CAPABILITY_IPV6_ONLY:
            ucIpv6Capability = AT_IPV6_CAPABILITY_IPV6_ONLY;
            break;

        case AT_IPV6_CAPABILITY_IPV4V6_OVER_ONE_PDP:
            ucIpv6Capability = AT_IPV6_CAPABILITY_IPV4_ONLY
                               + AT_IPV6_CAPABILITY_IPV6_ONLY
                               + AT_IPV6_CAPABILITY_IPV4V6_OVER_ONE_PDP;
            break;

        case AT_IPV6_CAPABILITY_IPV4V6_OVER_TWO_PDP:
            ucIpv6Capability = AT_IPV6_CAPABILITY_IPV4_ONLY
                               + AT_IPV6_CAPABILITY_IPV6_ONLY
                               + AT_IPV6_CAPABILITY_IPV4V6_OVER_TWO_PDP;
            break;

        default:
            ucIpv6Capability = AT_IPV6_CAPABILITY_IPV4_ONLY;
            break;
    }

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s: %d",
                                                     g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                     ucIpv6Capability);
    return AT_OK;
}

/*****************************************************************************
 Prototype      : At_QryCrpnPara
 Description    : ^CRPN?
 Input          : ucIndex --- 
 Output         :
 Return Value   :
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2009-09-01
    Author      : L47619
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_QryCrpnPara(TAF_UINT8 ucIndex)
{
    return AT_OK;
}

/*****************************************************************************
     : AT_QryAlsPara
   : ALS
   : ucIndex --- 
   : 
     : AT_XXX  --- ATC
   :
   :

       :
  1.       : 2010122
           : z40661
       : 

*****************************************************************************/
VOS_UINT32 AT_QryAlsPara( TAF_UINT8 ucIndex )
{
    VOS_UINT32                          ulRst;
    MN_CALL_APP_REQ_ENUM_UINT32         usMsg;

    usMsg                           = MN_CALL_APP_QRY_ALS_REQ;
    gastAtClientTab[ucIndex].opId   = At_GetOpId();

    /*TAF_CS_ALS_LINE_NO_QRYTAFTAF*/
    ulRst = MN_CALL_SendAppRequest(usMsg,
                                   gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   0,
                                   VOS_NULL_PTR);
    if(AT_SUCCESS == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_APP_QRY_ALS_REQ;
        return AT_WAIT_ASYNC_RETURN;
    }
    return AT_ERROR;
}

/*****************************************************************************
     : At_CovertMsInternalRxDivParaToUserSet
   : 
   : VOS_UINT16 usCurBandSwitch
             VOS_UINT32 *pulUserDivBandsLow
             VOS_UINT32 *pulUserDivBandsHigh
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 2010221
           : l65478
       : 

*****************************************************************************/
VOS_VOID At_CovertMsInternalRxDivParaToUserSet(
                    VOS_UINT16 usCurBandSwitch,
                    VOS_UINT32 *pulUserDivBandsLow,
                    VOS_UINT32 *pulUserDivBandsHigh
                    )
{
    *pulUserDivBandsLow      = 0;
    *pulUserDivBandsHigh     = 0;

    /*:
        0x80000            GSM850
        0x300              GSM900
        0x80               DCS1800
        0x200000           PCS1900
        0x400000           WCDMA2100
        0x800000           WCDMA1900
        0x1000000          WCDMA1800
        0x2000000          WCDMA_AWS
        0x4000000          WCDMA850
        0x2000000000000    WCDMA900
        0x4000000000000    WCDMA1700
      MS:
        2100M/ bit1  1900M/bit2  1800M/bit3  1700M/bit4  1600M/bit5
        1500M/bit6   900M/bit7   850M/bit8   800M/bit9   450M/bit10
      MS
    */
    if (0 != (usCurBandSwitch & AT_MS_SUPPORT_RX_DIV_900))
    {
        *pulUserDivBandsHigh |= TAF_PH_BAND_WCDMA_VIII_900;
    }
    if (0 != (usCurBandSwitch & AT_MS_SUPPORT_RX_DIV_IX_1700))
    {
        *pulUserDivBandsHigh |= TAF_PH_BAND_WCDMA_IX_1700;
    }
    if (0 != (usCurBandSwitch & AT_MS_SUPPORT_RX_DIV_2100))
    {
        *pulUserDivBandsLow |= TAF_PH_BAND_WCDMA_I_IMT_2100;
    }
    if (0 != (usCurBandSwitch & AT_MS_SUPPORT_RX_DIV_1900))
    {
        *pulUserDivBandsLow |= TAF_PH_BAND_WCDMA_II_PCS_1900;
    }
    if (0 != (usCurBandSwitch & AT_MS_SUPPORT_RX_DIV_1800))
    {
        *pulUserDivBandsLow |= TAF_PH_BAND_WCDMA_III_1800;
    }
    if (0 != (usCurBandSwitch & AT_MS_SUPPORT_RX_DIV_850))
    {
        *pulUserDivBandsLow |= TAF_PH_BAND_WCDMA_V_850;
    }

    return;
}

/*****************************************************************************
     : At_QryFrssiPara
   : RSSI
   : ucIndex - 
   : 
     : ATC
   :
   :

       :
  1.       : 2010720
           : z00161729
       : 
  2.       : 2011104
           : w00181244
       :  LTE 
  3.       : 20121221
           : l00227485
       : DSDA PhaseII
*****************************************************************************/
VOS_UINT32 At_QryFrssiPara(
    VOS_UINT8                           ucIndex
)
{
    AT_HPA_RF_RX_RSSI_REQ_STRU          *pstMsg;
    VOS_UINT32                          ulLength;

    /*  LTE  */
    if ((AT_RAT_MODE_FDD_LTE == g_stAtDevCmdCtrl.ucDeviceRatMode)
      ||(AT_RAT_MODE_TDD_LTE == g_stAtDevCmdCtrl.ucDeviceRatMode))
    {
        return atQryFRSSIPara(ucIndex);
    }

    if(AT_RAT_MODE_TDSCDMA == g_stAtDevCmdCtrl.ucDeviceRatMode)
    {
        return atQryFRSSIPara(ucIndex);
    }


    /**/
    if (AT_TMODE_FTM != g_stAtDevCmdCtrl.ucCurrentTMode)
    {
        return AT_DEVICE_MODE_ERROR;
    }

    /**/
    if (VOS_FALSE == g_stAtDevCmdCtrl.bDspLoadFlag)
    {
        return AT_CHANNEL_NOT_SET;
    }

    /**/
    if (AT_DSP_RF_SWITCH_OFF == g_stAtDevCmdCtrl.ucRxOnOff)
    {
        return AT_FRSSI_RX_NOT_OPEN;
    }

    /* GDSP LOAD
    GDSP  */
    if ((AT_TXON_OPEN == g_stAtDevCmdCtrl.ucRxonOrTxon)
     && ((AT_RAT_MODE_GSM == g_stAtDevCmdCtrl.ucDeviceRatMode)
      || (AT_RAT_MODE_EDGE == g_stAtDevCmdCtrl.ucDeviceRatMode)))
    {
        return AT_FRSSI_OTHER_ERR;
    }

    /* AT_HPA_RF_RX_RSSI_REQ_STRU */
    ulLength = sizeof(AT_HPA_RF_RX_RSSI_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg   = (AT_HPA_RF_RX_RSSI_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_AT, ulLength);

    if (VOS_NULL_PTR == pstMsg)
    {
        AT_WARN_LOG("At_QryFrssiPara: alloc msg fail!");
        return AT_FRSSI_OTHER_ERR;
    }

    /* Modified by L00171473 for DTS2012010901510 DSP PID, 2012-01-07, begin */
    if ((AT_RAT_MODE_GSM == g_stAtDevCmdCtrl.ucDeviceRatMode)
     || (AT_RAT_MODE_EDGE == g_stAtDevCmdCtrl.ucDeviceRatMode))
    {
        pstMsg->ulReceiverPid = AT_GetDestPid(ucIndex, I0_DSP_PID_GPHY);
        pstMsg->usMsgID       = ID_AT_GHPA_RF_RX_RSSI_REQ;
    }
    else
    {
        pstMsg->ulReceiverPid = AT_GetDestPid(ucIndex, I0_DSP_PID_WPHY);
        pstMsg->usMsgID       = ID_AT_HPA_RF_RX_RSSI_REQ;
    }
    /* Modified by L00171473 for DTS2012010901510 DSP PID, 2012-01-07, end */

    pstMsg->usMeasNum  = AT_DSP_RSSI_MEASURE_NUM;
    pstMsg->usInterval = AT_DSP_RSSI_MEASURE_INTERVAL;
    pstMsg->usRsv      = 0;

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_AT, pstMsg))
    {
        AT_WARN_LOG("At_QryFrssiPara: Send msg fail!");
        return AT_FRSSI_OTHER_ERR;
    }

    /*  */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_QUERY_RSSI;
    g_stAtDevCmdCtrl.ucIndex               = ucIndex;

    return AT_WAIT_ASYNC_RETURN;    /*  */

}

/*****************************************************************************
     : At_QryRxDiv
   : 
   : TAF_UINT8 ucIndex
   : 
     : TAF_UINT32
   :
   :

       :
  1.       : 20100221
           : l65478
       : 
  2.       : 20110125
           : lijun 00171473
       : DTS2011012204713,NV,C30_Main
  3.       : 2011105
           : c00173809
       : AT

*****************************************************************************/
VOS_UINT32 At_QryRxDiv(TAF_UINT8 ucIndex)
{
    VOS_UINT32                          ulRst;

    /* DRV_AGENT_HARDWARE_QRYDRV AGENT */
    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   DRV_AGENT_RXDIV_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_WUEPS_PID_DRV_AGENT);

    if (TAF_SUCCESS == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_DRV_AGENT_RXDIV_QRY_REQ;
        return AT_WAIT_ASYNC_RETURN;
    }

    return AT_ERROR;

}

/*****************************************************************************
     : At_QryCuus1Para
   : UUS1
   : ucIndex  :AT
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 2010728
           : zhoujun /40661
       : 
  2.       : 2011108
           : c00173809
       : AT ,API
*****************************************************************************/
VOS_UINT32 At_QryCuus1Para(
    VOS_UINT8                           ucIndex
)
{
    VOS_UINT32                          ulRst;
    MN_CALL_APP_REQ_ENUM_UINT32         ucMsg;

    ucMsg = MN_CALL_APP_QRY_UUSINFO_REQ;

    ulRst = MN_CALL_SendAppRequest(ucMsg,
                                   gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   0,
                                   VOS_NULL_PTR);
    if (MN_ERR_NO_ERROR == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_APP_SET_UUSINFO_REQ;
        return AT_WAIT_ASYNC_RETURN;
    }
    return AT_ERROR;
}

/*****************************************************************************
     : At_QryApHplmn
   : MMAMCCMNC
   : VOS_UINT8  ucIndex
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 201094
           : w00167002
       : 

  2.       : 20111015
           : o00132663
       : ATAPI
*****************************************************************************/
VOS_UINT32 At_QryApHplmn( VOS_UINT8  ucIndex )
{
    if(VOS_TRUE == TAF_MMA_QryApHplmnInfoReq(WUEPS_PID_AT, gastAtClientTab[ucIndex].usClientId, 0))
    {
        /*  */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_HOMEPLMN_READ;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}
/*****************************************************************************
     : AT_QryAnQuery
   : rscp, ecio, rssi,,ID
   : VOS_UINT8 ucIndex
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 201094
           : w00167002
       : 

  2.       : 20101110
           : lijun 00171473
       : 34; 

  3.       : 20101214
           : lijun 00171473
       : DTS2010121101304, 

  4.       : 2011105
           : o00132663
       : ATCAPI

  5.       : 20151222
           : n00355355
       : ChicagoWCDMAATMTA
*****************************************************************************/
VOS_UINT32 AT_QryAnQuery( VOS_UINT8 ucIndex )
{
    VOS_UINT32                          ulRst;

    /*  ID_AT_MTA_WRR_ANQUERY_QRY_REQ  MTA  */
    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   ID_AT_MTA_ANQUERY_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_UEPS_PID_MTA);

    if (AT_SUCCESS == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_ANQUERY_READ;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}

/*****************************************************************************
     : AT_CalculateAntennaLevel
   : rscp, Ecio, rssi: g_ucMNPHAntennaLevel
   : VOS_INT32  lRssi,
             VOS_INT16  lRscp,
             VOS_INT16  lEcio
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 201094
           : w00167002
       : 
  2.       : 20101110
           : lijun 00171473
       : 34
*****************************************************************************/
AT_CMD_ANTENNA_LEVEL_ENUM_UINT8 AT_CalculateAntennaLevel(
    VOS_INT16                           sRscp,
    VOS_INT16                           sEcio
)
{
/* Add by w00199382 for V7, 2012-04-07, Begin   */
    VOS_UINT16                          usRscp;
    VOS_UINT16                          usEcio;
    AT_CMD_ANTENNA_LEVEL_ENUM_UINT8     enRlstAntennaLevel;

/* RSCP and ECIO different Thresholds variables */
   VOS_INT32                            alRscpThreshold[AT_ANTEN_LEV_MAX_NUM] = {125, 108, 102, 96} ;
   VOS_INT32                            alEcioThreshold[AT_ANTEN_LEV_MAX_NUM] = {30, 16, 13, 10};


    VOS_UINT8                          *pucSystemAppConfig;
    pucSystemAppConfig                  = AT_GetSystemAppConfigAddr();

    if ( SYSTEM_APP_WEBUI == *pucSystemAppConfig)
    {
        /*  */
        usRscp                    = (VOS_UINT16)-sRscp;
        usEcio                    = (VOS_UINT16)-sEcio;

        /* 3 level of Signal */
        if ( (usEcio <= g_stEcioCfg.ssValue[3])
          && (usRscp <= g_stRscpCfg.ssValue[3]))
        {
            enRlstAntennaLevel = AT_CMD_ANTENNA_LEVEL_4;
        }
        /* 2 level of Signal */
        else if (((usEcio <= g_stEcioCfg.ssValue[2]) && (usEcio > g_stEcioCfg.ssValue[3])
               && (usRscp <= g_stRscpCfg.ssValue[2]))
              || ((usRscp <= g_stRscpCfg.ssValue[2]) && (usRscp > g_stRscpCfg.ssValue[3])
               && (usEcio < g_stEcioCfg.ssValue[2])))
        {
            enRlstAntennaLevel  = AT_CMD_ANTENNA_LEVEL_3;
        }
        /* 1 level of Signal */
        else if (((usEcio <= g_stEcioCfg.ssValue[1]) && (usEcio > g_stEcioCfg.ssValue[2])
               && (usRscp <= g_stRscpCfg.ssValue[1]))
              || ((usRscp <= g_stRscpCfg.ssValue[1]) && (usRscp > g_stRscpCfg.ssValue[2])
               && (usEcio < g_stEcioCfg.ssValue[1])))
        {
            enRlstAntennaLevel  = AT_CMD_ANTENNA_LEVEL_2;
        }
        else
        {
            enRlstAntennaLevel  = AT_CMD_ANTENNA_LEVEL_1;
        }
        return enRlstAntennaLevel;
    }

    enRlstAntennaLevel        = 0;

    /*  */
    usRscp                    = (VOS_UINT16)-sRscp;
    usEcio                    = (VOS_UINT16)-sEcio;

    /* 3 level of Signal */
    if ( (usEcio <= alEcioThreshold[3])
      && (usRscp <= alRscpThreshold[3]))
    {
        enRlstAntennaLevel = AT_CMD_ANTENNA_LEVEL_4;
    }
    /* 2 level of Signal */
    else if (((usEcio <= alEcioThreshold[2]) && (usEcio > alEcioThreshold[3])
           && (usRscp <= alRscpThreshold[2]))
          || ((usRscp <= alRscpThreshold[2]) && (usRscp > alRscpThreshold[3])
           && (usEcio < alEcioThreshold[2])))
    {
        enRlstAntennaLevel  = AT_CMD_ANTENNA_LEVEL_3;
    }
    /* 1 level of Signal */
    else if (((usEcio <= alEcioThreshold[1]) && (usEcio > alEcioThreshold[2])
           && (usRscp <= alRscpThreshold[1]))
          || ((usRscp <= alRscpThreshold[1]) && (usRscp > alRscpThreshold[2])
           && (usEcio < alEcioThreshold[1])))
    {
        enRlstAntennaLevel  = AT_CMD_ANTENNA_LEVEL_2;
    }
    else
    {
        enRlstAntennaLevel  = AT_CMD_ANTENNA_LEVEL_1;
    }

    return enRlstAntennaLevel;

/* Add by w00199382 for V7, 2012-04-07, End   */
}
/*****************************************************************************
     : AT_GetSmoothAntennaLevel
   : 
   : VOS_UINT8                           ucIndex,
             AT_CMD_ANTENNA_LEVEL_ENUM_UINT8     enLevel
   : 
     :
   :
   :

       :
  1.       : 20101110
           : lijun 00171473
       : 
  2.       : 2013222
           : l60609
       : DSDA PHASE III
*****************************************************************************/
VOS_VOID AT_GetSmoothAntennaLevel(
    VOS_UINT8                           ucIndex,
    AT_CMD_ANTENNA_LEVEL_ENUM_UINT8     enLevel
)
{
    VOS_UINT8                               i;
    /* Modified by l60609 for DSDA Phase III, 2013-2-22, Begin */
    AT_MODEM_NET_CTX_STRU              *pstNetCtx = VOS_NULL_PTR;

    pstNetCtx = AT_GetModemNetCtxAddrFromClientId(ucIndex);

    /*    */
    if ( AT_CMD_ANTENNA_LEVEL_0 == enLevel )
    {
        pstNetCtx->enCalculateAntennaLevel = enLevel;

        TAF_MEM_SET_S( pstNetCtx->aenAntennaLevel, sizeof(pstNetCtx->aenAntennaLevel), 0x00, sizeof(pstNetCtx->aenAntennaLevel) );
        return;
    }

    /*     */
    if ( AT_CMD_ANTENNA_LEVEL_0 == pstNetCtx->enCalculateAntennaLevel )
    {
        pstNetCtx->enCalculateAntennaLevel = enLevel;

        TAF_MEM_SET_S( pstNetCtx->aenAntennaLevel, sizeof(pstNetCtx->aenAntennaLevel), 0x00, sizeof(pstNetCtx->aenAntennaLevel) );
        pstNetCtx->aenAntennaLevel[AT_ANTENNA_LEVEL_MAX_NUM-1] = enLevel;
        return;
    }

    /* , (1) */
    if ( enLevel > (pstNetCtx->aenAntennaLevel[AT_ANTENNA_LEVEL_MAX_NUM-1] + 1) )
    {
        pstNetCtx->enCalculateAntennaLevel = enLevel;

        TAF_MEM_SET_S( pstNetCtx->aenAntennaLevel, sizeof(pstNetCtx->aenAntennaLevel), 0x00, sizeof(pstNetCtx->aenAntennaLevel) );
        pstNetCtx->aenAntennaLevel[AT_ANTENNA_LEVEL_MAX_NUM-1] = enLevel;
        return;
    }
    else if (( enLevel + 1) < pstNetCtx->aenAntennaLevel[AT_ANTENNA_LEVEL_MAX_NUM-1] )
    {
        pstNetCtx->enCalculateAntennaLevel = enLevel;

        TAF_MEM_SET_S( pstNetCtx->aenAntennaLevel, sizeof(pstNetCtx->aenAntennaLevel), 0x00, sizeof(pstNetCtx->aenAntennaLevel) );
        pstNetCtx->aenAntennaLevel[AT_ANTENNA_LEVEL_MAX_NUM-1] = enLevel;
        return;
    }
    else
    {
      /* Do nothing... */
    }


    /* 3 */
    for ( i=0; i<AT_ANTENNA_LEVEL_MAX_NUM-1; i++ )
    {
         pstNetCtx->aenAntennaLevel[i] = pstNetCtx->aenAntennaLevel[i+1];
    }
    pstNetCtx->aenAntennaLevel[i] = enLevel;


    /*  */
    for ( i=0; i<AT_ANTENNA_LEVEL_MAX_NUM; i++ )
    {
        if ( pstNetCtx->enCalculateAntennaLevel == pstNetCtx->aenAntennaLevel[i] )
        {
            return;
        }
    }

    /*  AT_ANTENNA_LEVEL_MAX_NUM  */
    pstNetCtx->enCalculateAntennaLevel = enLevel;
    /* Modified by l60609 for DSDA Phase III, 2013-2-22, End */
}


/*****************************************************************************
     : AT_CalculateLTESignalValue
   : LTEsRsrp,sRsrq,sLevel
                atSetAnlevelCnfSameProc
   : TAF_INT16   	sRssi,
             TAF_UINT8    *sLevel,
             TAF_INT16    *sRsrp,
             TAF_INT16    *sRsrq
   : TAF_UINT8    *sLevel,
             TAF_INT16    *sRsrp,
             TAF_INT16    *sRsrq
     : 
   :
   :

       :
  1.       : 20141129
           : l00305157
       : Service_State_Optimize_PhaseI
*****************************************************************************/
TAF_VOID AT_CalculateLTESignalValue(
                                              VOS_INT16    *psRssi,
                                              VOS_UINT8    *pusLevel,
                                              VOS_INT16    *psRsrp,
                                              VOS_INT16    *psRsrq

)
{
        VOS_UINT8                           enCurAntennaLevel;
        VOS_INT16                           sRsrp;
        VOS_INT16                           sRsrq;

        /*  atSetAnlevelCnfSameProc*/
        /* : RscpEcioRscpEcio-145-32rssi99
        0 */
        if ( (TAF_PH_RSSIUNKNOW == *psRsrp)
          || (TAF_PH_RSSIUNKNOW == *psRssi) )
        {
            /* 0,  */
            enCurAntennaLevel       = AT_CMD_ANTENNA_LEVEL_0;
        }
        else
        {
            /*  */
            sRsrp            = (-(*psRsrp));

            /* AT_CalculateAntennaLevelD25 */
            enCurAntennaLevel = AT_CalculateLTEAntennaLevel((VOS_INT16)(sRsrp));
        }

        /*  */
        *pusLevel = AT_GetSmoothLTEAntennaLevel(enCurAntennaLevel);



        if(AT_RSSI_UNKNOWN == *psRssi)
        {
            *psRssi = AT_RSSI_UNKNOWN;
        }
        else if(*psRssi >= AT_RSSI_HIGH)
        {
            *psRssi = AT_CSQ_RSSI_HIGH;
        }
        else if(*psRssi <= AT_RSSI_LOW)
        {
            *psRssi = AT_CSQ_RSSI_LOW;
        }
        else
        {
            *psRssi = ( VOS_INT16)((*psRssi - AT_RSSI_LOW) / 2);
        }

        sRsrp = (*psRsrp == 99)?99:(-(*psRsrp));
        sRsrq = (*psRsrq == 99)?99:(-(*psRsrq));

        *psRsrp = sRsrp;
        *psRsrq = sRsrq;

        return;

}



/*****************************************************************************
     : At_QryGlastErrPara
   : 
   : TAF_UINT8 ucIndex
   : 
     : TAF_UINT32
   :
   :

       :
  1.       : 2010521
           : s62952
       : 

*****************************************************************************/
TAF_UINT32 At_QryGlastErrPara( TAF_UINT8 ucIndex )
{
    TAF_UINT16                 usLength;

    /* */
    usLength =  (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,
                                       (TAF_CHAR*)pgucAtSndCodeAddr, "%s:",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,
                                       (TAF_CHAR *)pgucAtSndCodeAddr + usLength, "%d",
                                       gulErrType);
    gstAtSendData.usBufLen = usLength;

    return AT_OK;

}

/*****************************************************************************
     : At_QryTModePara
   : TMode
   : TAF_UINT8 ucIndex
   : 
     : TAF_UINT32
   :
   :

       :
  1.       : 2010629
           : l00130025
       : 
  2.       : 20111013
           : w00181244
       : LTE
  3.       : 201393
           : z60575,l00169177
       : DTS2013082901597, V7R2
*****************************************************************************/
TAF_UINT32  At_QryTModePara(TAF_UINT8 ucIndex )
{
    TAF_UINT16                 usLength;

    /* TMODE */
    usLength =  (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,
                                       (TAF_CHAR*)pgucAtSndCodeAddr, "%s:",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,
                                       (TAF_CHAR *)pgucAtSndCodeAddr + usLength, "%d",
                                       1);
    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}

/*****************************************************************************
     : At_QryFpaPara
   : PA
   : ucIndex - 
   : 
     : PA
   :
   :

       :
  1.       : 2010719
           : z00161729
       : 

*****************************************************************************/
VOS_UINT32  At_QryFpaPara(VOS_UINT8 ucIndex)
{
    VOS_UINT16                          usLength;

    /**/
    if (AT_TMODE_FTM != g_stAtDevCmdCtrl.ucCurrentTMode)
    {
        return AT_DEVICE_MODE_ERROR;
    }

    /* PA */
    usLength =  (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR*)pgucAtSndCodeAddr, "%s:%d",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                       g_stAtDevCmdCtrl.ucPaLevel);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;

}

/*****************************************************************************
     : At_QryFlnaPara
   : LNA,:^FLNA:<level>
   : ucIndex - 
   : 
     : LNA
   :
   :

       :
  1.       : 2010719
           : z00161729
       : 
  2.       : 2011104
           : w00181244
       : LTE
*****************************************************************************/
VOS_UINT32  At_QryFlnaPara(VOS_UINT8 ucIndex)
{
    VOS_UINT16                          usLength;

    /*  LTE  */
    if ((AT_RAT_MODE_FDD_LTE == g_stAtDevCmdCtrl.ucDeviceRatMode)
      ||(AT_RAT_MODE_TDD_LTE == g_stAtDevCmdCtrl.ucDeviceRatMode))
    {
        return atQryFLNAPara(ucIndex);
    }

    /**/
    if (AT_TMODE_FTM != g_stAtDevCmdCtrl.ucCurrentTMode)
    {
        return AT_DEVICE_MODE_ERROR;
    }

    /* PA */
    usLength =  (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR*)pgucAtSndCodeAddr, "%s:%d",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                       g_stAtDevCmdCtrl.ucLnaLevel);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;

}

/*****************************************************************************
     : At_QryFChanPara
   : 
   : TAF_UINT8 ucIndex
   : 
     : TAF_UINT32
   :
   :

       :
  1.       : 2010629
           : l00130025
       : 
  2.       : 20111013
           : w00181244
       : LTE
*****************************************************************************/
TAF_UINT32  At_QryFChanPara(TAF_UINT8 ucIndex )
{
    TAF_UINT16                 usLength;

    if ((AT_RAT_MODE_FDD_LTE == g_stAtDevCmdCtrl.ucDeviceRatMode)
      ||(AT_RAT_MODE_TDD_LTE == g_stAtDevCmdCtrl.ucDeviceRatMode))
    {
        return atQryFCHANPara(ucIndex);
    }

    if (AT_TMODE_FTM != g_stAtDevCmdCtrl.ucCurrentTMode)
    {
        return AT_DEVICE_MODE_ERROR;
    }

    /* FCHAN */
    usLength =  (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,
                                       (TAF_CHAR*)pgucAtSndCodeAddr, "%s:",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,
                                  (TAF_CHAR *)pgucAtSndCodeAddr + usLength, "%d,%d,%d,%d",
                                   g_stAtDevCmdCtrl.ucDeviceRatMode,
                                   g_stAtDevCmdCtrl.ucDeviceAtBand,
                                   g_stAtDevCmdCtrl.stDspBandArfcn.usUlArfcn,
                                   g_stAtDevCmdCtrl.stDspBandArfcn.usDlArfcn);
    gstAtSendData.usBufLen = usLength;

    return AT_OK;

}

/*****************************************************************************
     : At_QryFRxonPara
   : ,:^FRXON:<switch>
   : ucIndex - 
   : 
     : 
   :
   :

       :
  1.       : 2010719
           : z00161729
       : 
  2.       : 2011104
           : w00181244
       : LTE
*****************************************************************************/
VOS_UINT32  At_QryFRxonPara(VOS_UINT8 ucIndex)
{
    VOS_UINT16                          usLength;

    /* LTE  */
    if ((AT_RAT_MODE_FDD_LTE == g_stAtDevCmdCtrl.ucDeviceRatMode)
      ||(AT_RAT_MODE_TDD_LTE == g_stAtDevCmdCtrl.ucDeviceRatMode))
    {
        return atQryFRXONPara(ucIndex);
    }

    /**/
    if (AT_TMODE_FTM != g_stAtDevCmdCtrl.ucCurrentTMode)
    {
        return AT_DEVICE_MODE_ERROR;
    }

    /*  */
    usLength =  (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR*)pgucAtSndCodeAddr, "%s:%d",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                       g_stAtDevCmdCtrl.ucRxOnOff);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;

}

/*****************************************************************************
     : At_QryFTxonPara
   : FTxOn
   : TAF_UINT8 ucIndex
   : 
     : TAF_UINT32
   :
   :

       :
  1.       : 2010629
           : l00130025
       : 

  2.       : 20111015
           : /w00181244
       : LTE
*****************************************************************************/
TAF_UINT32  At_QryFTxonPara(TAF_UINT8 ucIndex )
{
    TAF_UINT16                 usLength;

    /* LTE  */
    if ((AT_RAT_MODE_FDD_LTE == g_stAtDevCmdCtrl.ucDeviceRatMode)
      ||(AT_RAT_MODE_TDD_LTE == g_stAtDevCmdCtrl.ucDeviceRatMode))
    {
        return atQryFTXONPara(ucIndex);
    }

    if (AT_TMODE_FTM != g_stAtDevCmdCtrl.ucCurrentTMode)
    {
        return AT_DEVICE_MODE_ERROR;
    }
    /* DAC */
    usLength =  (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,
                                       (TAF_CHAR*)pgucAtSndCodeAddr, "%s:",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,
                                  (TAF_CHAR *)pgucAtSndCodeAddr + usLength, "%d",
                                   g_stAtDevCmdCtrl.ucTxOnOff);
    gstAtSendData.usBufLen = usLength;

    return AT_OK;

}
/*****************************************************************************
     : AT_QryFDac
   : DACWDSP AGC,GTxVpa
   : TAF_UINT8 ucIndex
   : 
     : TAF_UINT32
   :
   :

       :
  1.       : 2010629
           : l00130025
       : 

*****************************************************************************/
TAF_UINT32  AT_QryFDac(TAF_UINT8 ucIndex )
{
    TAF_UINT16                 usLength;

    if (AT_TMODE_FTM != g_stAtDevCmdCtrl.ucCurrentTMode)
    {
        return AT_DEVICE_MODE_ERROR;
    }

    /* DAC */
    usLength =  (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,
                                       (TAF_CHAR*)pgucAtSndCodeAddr, "%s:",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,
                                  (TAF_CHAR *)pgucAtSndCodeAddr + usLength, "%d",
                                   g_stAtDevCmdCtrl.usFDAC);
    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}

/*****************************************************************************
     : AT_QryPlatForm
   : 
             1: huwawei
             submode:
             V2 C6 -->26
             V3 C01 -->31
   : TAF_UINT8 ucIndex
   : 
     : TAF_UINT32
   :
   :

       :
  1.       : 2010628
           : w00167002
       : 
  2.       : 20120206
           : f62575
       : < sub_platform _info >V3R22632V3R1R
  3.       : 20120419
           : f62575
       : < sub_platform _info >V3 NVNV
  4.       : 20121213
           : L00171473
       : DTS2012121802573, TQE
  5.       : 2013517
           : l00167671
       : NV, NV
*****************************************************************************/

TAF_UINT32  At_QryPlatForm(TAF_UINT8 ucIndex )
{
    /* Modify by f62575 for V7, 2012-04-07, Begin   */
    VOS_UINT32                          ulRet;
    NAS_NVIM_PLATFORM_STRU              stPlatform;



    stPlatform.usPlatform = 0;

    ulRet = NV_ReadEx(MODEM_ID_0, en_NV_Item_SubPlatFormInfo, &stPlatform.usPlatform, sizeof(stPlatform.usPlatform));
    if (NV_OK != ulRet)
    {
        return AT_ERROR;
    }
    /* Modify by f62575 for V7, 2012-04-07, End   */

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR*)pgucAtSndCodeAddr,
                                                    "%s: %d,%d",g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    1,
                                                    stPlatform.usPlatform);

    return AT_OK;

}
/*****************************************************************************
     : At_QryDataLock
   : 
   : VOS_UINT8 ucIndex
   : 
     : AT_OK
   :
   :

       :
  1.       : 2010724
           : l00130025
       : 

*****************************************************************************/
VOS_UINT32  At_QryDataLock(VOS_UINT8 ucIndex )
{
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR*)pgucAtSndCodeAddr,
                                                    "%s:%d", g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    g_bAtDataLocked);

    return AT_OK;

}
/*****************************************************************************
     : At_QrySD
   : SD
   : ucIndex --AT
   : 
     : AT_OK
   :
   :

       :
  1.       : 2010726
           : l00130025
       : 
  2.       : 20120213
           : f62575
       : SD
*****************************************************************************/
VOS_UINT32  At_QrySD(VOS_UINT8 ucIndex )
{

    VOS_UINT32                          ulCurrentOprtStaus;

    ulCurrentOprtStaus = mdrv_sd_get_opptstatus();

    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR*)pgucAtSndCodeAddr,
                                                    "%s:%d", g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    ulCurrentOprtStaus);
    return AT_OK;
}
/*****************************************************************************
     : At_DelCtlAndBlankCharWithEndPadding
   : ,'\0',
             1.0x20,<CR><LF>0D,0A
             2.
   : pData -- AT
   : pusCmdLen -- 
     : : AT_FAILURE
             : AT_SUCCESS
   :
   :

       :
  1.       : 2010811
           : l00130025
       : 

*****************************************************************************/
VOS_UINT32  At_DelCtlAndBlankCharWithEndPadding(
    VOS_UINT8                               *pucData,
    VOS_UINT16                              *pusCmdLen
)
{

    VOS_UINT16                              usOrigLen;

    usOrigLen = *pusCmdLen;

    /*  */
    if(AT_FAILURE == At_ScanCtlChar(pucData, pusCmdLen))
    {
        return AT_FAILURE;
    }

    /*  */
    if(AT_FAILURE == At_ScanBlankChar(pucData, pusCmdLen))
    {
        return AT_FAILURE;
    }

    TAF_MEM_SET_S(pucData + (*pusCmdLen), (VOS_SIZE_T)(usOrigLen - (*pusCmdLen)), 0x00, (VOS_SIZE_T)(usOrigLen - (*pusCmdLen)));

    return AT_SUCCESS;

}
/*****************************************************************************
     : AT_QryVersion
   : 
   : VOS_UINT8 ucIndex
   : 
     : AT_OK
   :
   :

       :
  1.       : 2010724
           : l00130025
       : 

  2.       : 20110222
           : A00165503
       : : DTS2011022205350

  3.       : 20111015
           : /w00181244
       : DRV_AGENT_VERSION_QRY_REQI0_WUEPS_PID_DRV_AGENT
                 ,AT_CMD_VERSION_QRY
*****************************************************************************/
VOS_UINT32  At_QryVersion(VOS_UINT8 ucIndex )
{
    if(TAF_SUCCESS == AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                            gastAtClientTab[ucIndex].opId,
                                            DRV_AGENT_VERSION_QRY_REQ,
                                            VOS_NULL_PTR,
                                            0,
                                            I0_WUEPS_PID_DRV_AGENT))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_VERSION_QRY;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}

/*****************************************************************************
     : AT_QryBsn
   : 
   : TAF_UINT8 ucIndex
   : 
     : TAF_UINT32
   :
   :

       :
  1.       : 2010628
           : w00167002
       : 
  2.       : 201334
           : l60609
       : DSDA PHASE III
*****************************************************************************/

VOS_UINT32  At_QryBsn(VOS_UINT8 ucIndex )
{
    /* 16, */
    VOS_UINT8                            aucBsnSerialNum[17];
    VOS_UINT16                           usLength;
    /* Modified by l60609 for DSDA Phase III, 2013-3-4, Begin */
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT32                          ulRet;

    enModemId = MODEM_ID_0;
    /* Modified by l60609 for DSDA Phase III, 2013-3-4, End */

    /*  */
    if(AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    usLength = sizeof(aucBsnSerialNum);

    /* Modified by l60609 for DSDA Phase III, 2013-3-4, Begin */
    ulRet = AT_GetModemIdFromClient(ucIndex, &enModemId);

    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("At_SetSDomainPara: Get modem id fail.");
        return AT_ERROR;
    }

    if (NV_OK != NV_ReadEx(enModemId, en_NV_Item_ManufactureInfo, aucBsnSerialNum, usLength))
    /* Modified by l60609 for DSDA Phase III, 2013-3-4, End */
    {
        AT_WARN_LOG("At_QryBsn:WARNING:NVIM Read en_NV_Item_Serial_Num falied!");
        return AT_ERROR;
    }
    else
    {
        aucBsnSerialNum[16]=0;/*'\0'*/
        usLength = 0;
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,"%s:",g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,"%s",aucBsnSerialNum);
    }
    gstAtSendData.usBufLen = usLength;
    return AT_OK;

}
/*****************************************************************************
     : At_QryCsVer
   : 
   : VOS_UINT8 ucIndex
   : 
     : AT_OK
   :
   :

       :
  1.       : 201089
           : w00167002
       : 
  2.       : 20120419
           : f62575
       : 
  3.       : 20121213
           : L00171473
       : DTS2012121802573, TQE
  4.       : 2013517
           : l00167671
       : NV, NV
*****************************************************************************/
VOS_UINT32  At_QryCsVer(VOS_UINT8 ucIndex )
{
    /* Modify by f62575 for V7, 2012-04-07, Begin   */
    VOS_UINT32                          ulRet;
    TAF_NVIM_CS_VER_STRU                stCsver;


    stCsver.usCsver = 0;

    ulRet = NV_ReadEx(MODEM_ID_0, en_NV_Item_Csver, &stCsver, sizeof(VOS_UINT16));
    if (NV_OK != ulRet)
    {
        return AT_ERROR;
    }
    /* Modify by f62575 for V7, 2012-04-07, End   */

   gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                                   "%s:%d",
                                                   g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                   stCsver.usCsver);

    return AT_OK;
}
/*****************************************************************************
     : At_QryQosPara
   : PDPQoSTraffic Class
   : VOS_UINT8 ucIndex
   : 
     : VOS_UINT32:
             NVAT_OK
             AT_DEVICE_OTHER_ERROR
   :
   :

       :
  1.       : 2010810
           : w00167002
       : 
  2.       : 2012-03-19
           : w00199382
       :  DTS2012031306141 QOSsubscribed
  3.       : 2012810
           : L00171473
       : DTS2012082204471, TQE
  4.       : 201334
           : l60609
       : DSDA PHASE III
*****************************************************************************/
VOS_UINT32  At_QryQosPara(VOS_UINT8 ucIndex )
{
    AT_TRAFFIC_CLASS_CUSTOMIZE_STRU     stATTrafficClass;
    VOS_UINT16                          usReadLength;
    VOS_UINT16                          usLength;
    /* Modified by l60609 for DSDA Phase III, 2013-3-4, Begin */
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT32                          ulRet;

    enModemId = MODEM_ID_0;
    /* Modified by l60609 for DSDA Phase III, 2013-3-4, End */


    stATTrafficClass.ucStatus       = NV_ITEM_DEACTIVE;
    stATTrafficClass.ucTrafficClass = AT_QOS_TRAFFIC_CLASS_SUBSCRIBE;


    /**/
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_DEVICE_OTHER_ERROR;
    }

    /*NVstATTrafficClass*/
    usReadLength = sizeof(stATTrafficClass);

    /* Modified by l60609 for DSDA Phase III, 2013-3-4, Begin */
    ulRet = AT_GetModemIdFromClient(ucIndex, &enModemId);

    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("At_QryQosPara: Get modem id fail.");
        return AT_ERROR;
    }

    if (NV_OK != NV_ReadEx(enModemId, en_NV_Item_TRAFFIC_CLASS_Type, &stATTrafficClass, usReadLength))
    {
        AT_WARN_LOG("At_QryQosPara:WARNING:NVIM Read en_NV_Item_TRAFFIC_CLASS_Type failed!");
        return AT_DEVICE_OTHER_ERROR;
    }
    /* Modified by l60609 for DSDA Phase III, 2013-3-4, End */

    /*NV,:AT_QOS_TRAFFIC_CLASS_INTERACTIVE*/
    if (NV_ITEM_DEACTIVE == stATTrafficClass.ucStatus)
    {
        usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR *)pgucAtSndCodeAddr, "%s:%d",
                                          g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                          AT_QOS_TRAFFIC_CLASS_SUBSCRIBE);


    }
    else
    {
        usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr,
                                         (VOS_CHAR *)pgucAtSndCodeAddr, "%s:%d",
                                         g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                         stATTrafficClass.ucTrafficClass);
    }
    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}
/*****************************************************************************
     : At_QrySDomainPara
   : 
   : VOS_UINT8 ucIndex
   : 
     : VOS_UINT32:
             NVAT_OK
             AT_DEVICE_OTHER_ERROR
   :
   :

       :
  1.       : 2010810
           : w00167002
       : 
  2.       : 20121213
           : L00171473
       : DTS2012121802573, TQE
  3.       : 201334
           : l60609
       : DSDA PHASE III
  4.       : 20130520
           : m00217266
       : nv
*****************************************************************************/
VOS_UINT32   At_QrySDomainPara(VOS_UINT8 ucIndex)
{
    NAS_NVIM_MS_CLASS_STRU              stMsClass;
    VOS_UINT16                          usLength;
    /* Modified by l60609 for DSDA Phase III, 2013-3-4, Begin */
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulLength;

    enModemId = MODEM_ID_0;
    ulLength  = 0;

    /* Modified by l60609 for DSDA Phase III, 2013-3-4, End */

    TAF_MEM_SET_S(&stMsClass, sizeof(stMsClass), 0x00, sizeof(NAS_NVIM_MS_CLASS_STRU));
    stMsClass.ucMsClass = TAF_PH_MS_CLASS_A;

    /**/
    if(AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_DEVICE_OTHER_ERROR;
    }

    /*NV*/
    usLength = sizeof(TAF_PH_MS_CLASS_TYPE);

    /* Modified by l60609 for DSDA Phase III, 2013-3-4, Begin */
    ulRet = AT_GetModemIdFromClient(ucIndex, &enModemId);

    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("At_QrySDomainPara: Get modem id fail.");
        return AT_ERROR;
    }
    (VOS_VOID)NV_GetLength(en_NV_Item_MMA_MsClass, &ulLength);
    if (NV_OK != NV_ReadEx(enModemId, en_NV_Item_MMA_MsClass, &stMsClass, ulLength))
    {
        AT_WARN_LOG("At_QrySDomainPara:WARNING:NVIM Read en_NV_Item_MMA_MsClass failed!");
        return AT_DEVICE_OTHER_ERROR;
    }
    /* Modified by l60609 for DSDA Phase III, 2013-3-4, End */

    /*NVMsClass*/
    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr,
                                      (VOS_CHAR *)pgucAtSndCodeAddr, "%s:%d",
                                      g_stParseContext[ucIndex].pstCmdElement->pszCmdName, stMsClass.ucMsClass);
    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}
/*****************************************************************************
     : At_QryGPIOPL
   : GPIO
   : VOS_UINT8 ucIndex-- 
   : 
     : AT_OK
   :
   :

       :
  1.       : 2010726
           : l00130025
       : 

  2.       : 20111015
           : w00181244
       : AT_FillAndSndAppReqMsgCI0_WUEPS_PID_DRV_AGENT
*****************************************************************************/
VOS_UINT32   At_QryGPIOPL(VOS_UINT8 ucIndex)
{
    if (TAF_SUCCESS == AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                              gastAtClientTab[ucIndex].opId,
                                              DRV_AGENT_GPIOPL_QRY_REQ,
                                              VOS_NULL_PTR,
                                              0,
                                              I0_WUEPS_PID_DRV_AGENT))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_GPIOPL_QRY;             /* */
        return AT_WAIT_ASYNC_RETURN;                                            /*  */
    }
    else
    {
        return AT_ERROR;
    }
}

/*****************************************************************************
     : AT_QryMDatePara
   : 
   : VOS_UINT8 ucIndex 
   : 
     : VOS_UINT32 ATC
             AT_OK      
             AT_ERROR   MT
   :
   :

       :
  1.       : 2010719
           : /f62575
       : 
  2.       : 20130517
           : m00217266
       : nv
*****************************************************************************/
VOS_UINT32 AT_QryMDatePara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRet;
    VOS_UINT16                          usLength;
    TAF_AT_NVIM_MANUFACTURE_DATE_STRU   stManufactrueDate;

    ulRet = NV_ReadEx(MODEM_ID_0, en_NV_Item_AT_MANUFACTURE_DATE,
                    &stManufactrueDate,
                    AT_MDATE_STRING_LENGTH);
    if (NV_OK != ulRet)
    {
        AT_WARN_LOG("AT_QryMDatePara: fail to read NVIM . ");
        return AT_ERROR;
    }

    /*: */
    usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       "%s:",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    stManufactrueDate.aucMDate[AT_MDATE_STRING_LENGTH - 1] = '\0';
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s",
                                       stManufactrueDate.aucMDate);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}

/*****************************************************************************
     : AT_QryFacInfoPara
   : 
   : VOS_UINT8 ucIndex 
   : 
     : VOS_UINT32 ATC
             AT_OK      
             AT_ERROR   MT
   :
   :

       :
  1.       : 2010719
           : /f62575
       : 

*****************************************************************************/
VOS_UINT32 AT_QryFacInfoPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRet;
    VOS_UINT8                           *pucFacInfo = TAF_NULL_PTR;
    VOS_UINT16                          usLength;

    /* NV */
    pucFacInfo = (VOS_UINT8 *)PS_MEM_ALLOC(WUEPS_PID_AT, AT_FACINFO_STRING_LENGTH);
    if (VOS_NULL_PTR == pucFacInfo)
    {
        AT_WARN_LOG("AT_QryFacInfoPara: fail to alloc memory.");
        return AT_ERROR;
    }

    ulRet = NV_ReadEx(MODEM_ID_0, en_NV_Item_AT_FACTORY_INFO,
                    pucFacInfo,
                    AT_FACINFO_STRING_LENGTH);
    if (NV_OK != ulRet)
    {
        AT_WARN_LOG("AT_QryFacInfoPara: fail to read en_NV_Item_AT_FACTORY_INFO . ");
        PS_MEM_FREE(WUEPS_PID_AT, pucFacInfo);
        return AT_ERROR;
    }

    /* NVINFO*/
    *(pucFacInfo + (AT_FACINFO_STRING_LENGTH - 1))     = '\0';
    *(pucFacInfo + AT_FACINFO_INFO1_LENGTH)            = '\0';

    /* :  */
    usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       "%s:0,%s",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                       pucFacInfo);

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s",
                                       gaucAtCrLf);

    /* :  */
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s:1,%s",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                       ((pucFacInfo + AT_FACINFO_INFO1_LENGTH) + 1));

    gstAtSendData.usBufLen = usLength;

    PS_MEM_FREE(WUEPS_PID_AT, pucFacInfo);
    return AT_OK;
}

/*****************************************************************************
     : At_ReadDpaCatFromNV
   : nvdpa,
   : VOS_UINT8 *pucDpaRate
   : 
     : OK
   :
   :

       :
  1.       : 2010817
           : w00167002
       : 
  2.       : 20110614
           : f00179208
      : DTS2011061304049,V3R1C03B010ATWasUeAccessCapa
                AT^DPACAT=<VALUE>AT^DPACAT?WasUeAccessCapa
  3.       : 201177
           : l60609
       : :DTS2011060304931,AT
  4.       : 2012518
           : z60575
       : DTS2012051806821NV
  5.       : 2012810
           : L00171473
       : DTS2012082204471, TQE
*****************************************************************************/
VOS_UINT32  At_ReadDpaCatFromNV(VOS_UINT8 *pucDpaRate)
{
    AT_NVIM_UE_CAPA_STRU                stUECapa;
    AT_DPACAT_PARA_STRU                 astDhpaCategory[AT_DPACAT_CATEGORY_TYPE_BUTT] = {
                {PS_TRUE,   AT_HSDSCH_PHY_CATEGORY_6,  PS_FALSE, 0, PS_FALSE},                                                           /* 3.6M  */
                {PS_TRUE,   AT_HSDSCH_PHY_CATEGORY_8,  PS_FALSE, 0, PS_FALSE},                                                           /* 7.2M  */
                {PS_TRUE,   AT_HSDSCH_PHY_CATEGORY_11, PS_FALSE, 0, PS_FALSE},                                                           /* 1.8M  */
                {PS_TRUE,   AT_HSDSCH_PHY_CATEGORY_10, PS_FALSE, 0, PS_FALSE},                                                          /*  14.4M */
                {PS_TRUE,   AT_HSDSCH_PHY_CATEGORY_10, PS_TRUE,  AT_HSDSCH_PHY_CATEGORY_14, PS_FALSE}};           /*  21M */
    VOS_UINT8                           ucLoop;


    TAF_MEM_SET_S(&stUECapa, sizeof(stUECapa), 0x00, sizeof(stUECapa));


    /* */
    if ( VOS_NULL_PTR == pucDpaRate )
    {
        AT_WARN_LOG("At_ReadDpaCatFromNV: null PTR.");
        return VOS_ERR;
    }

    if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_WAS_RadioAccess_Capa_New, &stUECapa,
                        sizeof(AT_NVIM_UE_CAPA_STRU)))
    {
        AT_WARN_LOG("At_ReadDpaCatFromNV():en_NV_Item_WAS_RadioAccess_Capa NV Read Fail!");
        return VOS_ERR;
    }

    for (ucLoop = 0; ucLoop < AT_DPACAT_CATEGORY_TYPE_BUTT; ucLoop++)
    {
        if ((stUECapa.enHSDSCHSupport        == astDhpaCategory[ucLoop].enHSDSCHSupport)
         && (stUECapa.ucHSDSCHPhyCategory    == astDhpaCategory[ucLoop].ucHSDSCHPhyCategory)
         && (stUECapa.enMacEhsSupport        == astDhpaCategory[ucLoop].enMacEhsSupport)
         && (stUECapa.ucHSDSCHPhyCategoryExt == astDhpaCategory[ucLoop].ucHSDSCHPhyCategoryExt)
         && (stUECapa.enMultiCellSupport     == astDhpaCategory[ucLoop].enMultiCellSupport))
        {
            *pucDpaRate = ucLoop;
            return VOS_OK;
        }
    }

    return VOS_ERR;
}

/*****************************************************************************
     : At_QueryDpaCat
   : HSDPA < rate >

   : ucIndex - 
   : 
     : OK
   :
   :

       :
  1.       : 2010723
           : w00167002
       : 
  2.       : 201241
           : l60609
       : DTS2012032702034:ERROR
*****************************************************************************/

VOS_UINT32   At_QryDpaCat(VOS_UINT8 ucIndex)
{
    VOS_UINT8                           ucDpaRate;
    VOS_UINT32                          ulWasResult;
    VOS_UINT16                          usLength;

    /*  */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    /* NV: At_ReadDpaCatFromNV, */
    ulWasResult = At_ReadDpaCatFromNV(&ucDpaRate);
    if (VOS_OK == ulWasResult)
    {
        usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (TAF_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR *)pgucAtSndCodeAddr, "%s:",
                                          g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength, "%d",
                                           (VOS_UINT32)ucDpaRate);
        gstAtSendData.usBufLen = usLength;
        return  AT_OK;
    }
    else
    {
        AT_WARN_LOG("At_QryDpaCat:WARNING:WAS_MNTN_QueryDpaCat failed!");
        return AT_ERROR;
    }
}
/*****************************************************************************
     : AT_ReadRrcVerFromNV
   : NVRrcVer
   : VOS_UINT8 *pucRrcVer
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 2010817
           : w00167002
       : 

  2.       : 2012421
           : l60609
       : DTS2012032304901:NV9008
  3.       : 2012810
           : L00171473
       : DTS2012082204471, TQE
*****************************************************************************/
VOS_UINT32 AT_ReadRrcVerFromNV(VOS_UINT8 *pucRrcVer)
{
    AT_NVIM_UE_CAPA_STRU                stUECapa;


    TAF_MEM_SET_S(&stUECapa, sizeof(stUECapa), 0x00, sizeof(stUECapa));


    /*  */
    if (VOS_NULL_PTR == pucRrcVer)
    {
        AT_WARN_LOG("AT_ReadRrcVerFromNV: null PTR.");
        return VOS_ERR;
    }

    if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_WAS_RadioAccess_Capa_New,
                         &stUECapa,
                         sizeof(AT_NVIM_UE_CAPA_STRU)))
    {
        AT_WARN_LOG("AT_ReadRrcVerFromNV: NV_ReadEx en_NV_Item_WAS_RadioAccess_Capa_New fail!");
        return VOS_ERR;
    }

    /* NV */
    if (VOS_FALSE == stUECapa.ulHspaStatus)
    {
        *pucRrcVer = AT_RRC_VERSION_DPA_AND_UPA;
        return VOS_OK;
    }

    /* NV */
    /* HSPA+ */
    if ((stUECapa.enAsRelIndicator >= AT_PTL_VER_ENUM_R7)
     && (VOS_TRUE == stUECapa.enEDCHSupport)
     && (VOS_TRUE == stUECapa.enHSDSCHSupport))
    {
        *pucRrcVer = AT_RRC_VERSION_HSPA_PLUNS;
    }
    /* DPA/UPA */
    else if((VOS_TRUE == stUECapa.enEDCHSupport)
         && (VOS_TRUE == stUECapa.enHSDSCHSupport))
    {
        *pucRrcVer = AT_RRC_VERSION_DPA_AND_UPA;
    }
    /* DPA */
    else if(VOS_TRUE == stUECapa.enHSDSCHSupport)
    {
        *pucRrcVer = AT_RRC_VERSION_DPA;
    }
    /* WCDMA */
    else
    {
        *pucRrcVer = AT_RRC_VERSION_WCDMA;
    }


    return VOS_OK;
}

/*****************************************************************************
     : AT_QueryHspaSpt
   : RRC

   : ucIndex - 
   : 
     : OK
   :
   :

       :
  1.       : 2010723
           : w00167002
       : 

*****************************************************************************/

VOS_UINT32   AT_QryHspaSpt(VOS_UINT8 ucIndex)
{
    VOS_UINT8                           ucRRCVer;
    VOS_UINT32                          ulWasResult;
    VOS_UINT16                          usLength;

    /*  */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_DPAUPA_ERROR;
    }

    ulWasResult = AT_ReadRrcVerFromNV(&ucRRCVer);

    if (VOS_OK == ulWasResult)
    {
        usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (TAF_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR *)pgucAtSndCodeAddr, "%s:",
                                          g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength, "%d",
                                           (VOS_UINT32)ucRRCVer);
        gstAtSendData.usBufLen = usLength;
        return  AT_OK;
    }
    else
    {
        AT_WARN_LOG("AT_QryHspaSpt:WARNING:WAS_MNTN_QueryHspaSpt failed!");
        return AT_DPAUPA_ERROR;
    }
}

/*****************************************************************************
     : At_QryCallSrvPara
   : ,:^CALLSRV:< service >
   : ucIndex - 
   : 
     : AT_OK                 - 
             AT_DEVICE_OTHER_ERROR - 
   :
   :

       :
  1.       : 201083
           : z00161729
       : 
  2.       : 2012810
           : L00171473
       : DTS2012082204471, TQE
  3.       : 2013517
           : l00167671
       : NV, NV
*****************************************************************************/
VOS_UINT32 At_QryCallSrvPara(VOS_UINT8 ucIndex)
{
    NAS_NVIM_CUSTOMIZE_SERVICE_STRU              stCustSrv;
    VOS_UINT16                          usLength;


    stCustSrv.ulStatus           = NV_ITEM_DEACTIVE;
    stCustSrv.ulCustomizeService = 0;


    if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_CustomizeService, &stCustSrv, sizeof(stCustSrv)))
    {
        AT_WARN_LOG("At_QryCallSrvPara():en_NV_Item_CustomizeService NV Read Fail!");
        return AT_DEVICE_OTHER_ERROR;
    }

    /* NVFALSE */
    if (NV_ITEM_DEACTIVE == stCustSrv.ulStatus)
    {
        usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR*)pgucAtSndCodeAddr, "%s:%d",
                                          g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                          VOS_FALSE);
    }
    else
    {
        usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR*)pgucAtSndCodeAddr, "%s:%d",
                                          g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                          stCustSrv.ulCustomizeService);
    }

    gstAtSendData.usBufLen = usLength;

    return AT_OK;

}

/*****************************************************************************
     : At_ReadGprsActiveTimerLenNV
   : en_NV_Item_GPRS_ActiveTimerLength NV
   : 
   : pulGprsActiveTimerLen - GPRS Active Timer,
             pusValueInfo          - 0:;
                                                 1:;
                                                 2:;
     : VOS_OK  - 
             VOS_ERR - 
   :
   :

       :
  1.       : 201083
           : z00161729
       : 

*****************************************************************************/
VOS_UINT32 At_ReadGprsActiveTimerLenNV(
    VOS_UINT32                          *pulGprsActiveTimerLen,
    VOS_UINT16                          *pusValueInfo
)
{
    if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_GPRS_ActiveTimerLength,
                          pulGprsActiveTimerLen, sizeof(VOS_UINT32)))
    {
        AT_WARN_LOG("At_ReadGprsActiveTimerLenNV():en_NV_Item_GPRS_ActiveTimerLength NV Read Fail!");
        return VOS_ERR;
    }

    if (AT_CUSTOMIZE_ITEM_DEFAULT_VAL_CHANGED == *pusValueInfo)
    {
        return VOS_OK;
    }

    /*NV*/
    if (*pulGprsActiveTimerLen != AT_GPRS_ACT_TIMER_LEN_DEFAULT_VAL)
    {
        *pusValueInfo = AT_CUSTOMIZE_ITEM_DEFAULT_VAL_CHANGED;
    }

    return VOS_OK;

}

/*****************************************************************************
     : At_QryCsdfltPara
   : ,:
             <CR><LF>^CSDFLT: < value_info > <CR><LF>\
             <CR><LF>^CSDFLT: <item>,<value><CR><LF>\
             [....]\
             <CR><LF>OK<CR><LF>
   : ucIndex - 
   : 
     : AT_OK    - 
             AT_DEVICE_OTHER_ERROR - 
   :
   :

       :
  1.       : 201083
           : z00161729
       : 
  2.       : 201183
           : z00161729
       : en_NV_Item_MMA_AccessMode NVen_NV_Item_RAT_PRIO_LIST
  3.       : 20111024
           : w00181244
       : At_ReadCustomizeSimLockNV
  4.       : 20120304
           : f62575
       : SIMLOCKC
*****************************************************************************/
VOS_UINT32 At_QryCsdfltPara(VOS_UINT8 ucIndex)
{

    /* Added by f62575 for B050 Project, 2012-2-3, Begin   */
    /* CSIMLOCK  */
    if(TAF_SUCCESS != Taf_ParaQuery(gastAtClientTab[ucIndex].usClientId,
                                    0,
                                    TAF_PH_SIMLOCK_VALUE_PARA,
                                    TAF_NULL_PTR))
    {
        return AT_ERROR;
    }

    /* AT */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CSDFLT_READ;

    return AT_WAIT_ASYNC_RETURN;
    /* Added by f62575 for B050 Project, 2012-2-3, end   */
}

/*****************************************************************************
     : AT_JudgeU8ArrayZero
   : UINT80
   : VOS_UINT8                           aucValue   UINT8
             VOS_UINT32                          ulLength   UINT8
   : 
     : VOS_UINT32     VOS_OK  UINT80
                            VOS_ERR UINT80
   :
   :

       :
  1.       : 2012728
           : f62575
       : 
*****************************************************************************/
VOS_UINT32 AT_JudgeU8ArrayZero(
    VOS_UINT8                           aucValue[],
    VOS_UINT32                          ulLength
)
{
    VOS_UINT32                          ulLoop;

    for (ulLoop = 0; ulLoop < ulLength; ulLoop++)
    {
        if (0 != aucValue[ulLoop])
        {
            return VOS_ERR;
        }
    }

    return VOS_OK;
}

/* Modify by z60575 for multi_ssid, 2012-9-5 begin */
/*****************************************************************************
     : AT_GetWifiNvValue
   : WIFINV
   : 
   : VOS_UINT16 *pusCsdValue    WIFINV
     : VOS_UINT32     VOS_OK  UINT80
                            VOS_ERR UINT80
   :
   :

       :
  1.       : 2012728
           : f62575
       : 
  2.       : 2012917
           : z60575
       : MULTI_SSID
*****************************************************************************/
VOS_UINT32 AT_GetWifiNvValue(VOS_UINT16 *pusCsdValue)
{
    TAF_AT_MULTI_WIFI_SEC_STRU                              stWifiKey;
    TAF_AT_MULTI_WIFI_SSID_STRU                             stWifiSsid;
    VOS_UINT32                                              ulRet;
    VOS_UINT32                                              ulLoop;

    /* WIFIWIFINV */
    if (BSP_MODULE_UNSUPPORT == mdrv_misc_support_check(BSP_MODULE_TYPE_WIFI))
    {
        *pusCsdValue = AT_CUSTOMIZE_ITEM_DEFAULT_VAL_UNCHANGE;
        return VOS_OK;
    }

    TAF_MEM_SET_S(&stWifiKey, sizeof(stWifiKey), 0x00, sizeof(stWifiKey));
    TAF_MEM_SET_S(&stWifiSsid, sizeof(stWifiSsid), 0x00, sizeof(stWifiSsid));

    /* en_NV_Item_WIFI_KEY0:
       aucWifiWpapsk aucWifiWepKey1 aucWifiWepKey2 aucWifiWepKey3 aucWifiWepKey4 */
    if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_MULTI_WIFI_KEY, &stWifiKey, sizeof(TAF_AT_MULTI_WIFI_SEC_STRU)))
    {
        AT_WARN_LOG("AT_GetWifiNvValue:READ NV ERROR");
        return VOS_ERR;
    }

    /* en_NV_Item_WIFI_STATUS_SSID0:
        aucWifiSsid
    */
    if (VOS_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_MULTI_WIFI_STATUS_SSID, &stWifiSsid, sizeof(TAF_AT_MULTI_WIFI_SSID_STRU)))
    {
        AT_WARN_LOG("AT_GetWifiNvValue:READ NV ERROR");
        return VOS_ERR;
    }

    for (ulLoop = 0; ulLoop < AT_WIFI_MAX_SSID_NUM; ulLoop++)
    {
        ulRet = AT_JudgeU8ArrayZero(stWifiKey.aucWifiWpapsk[ulLoop], sizeof(stWifiKey.aucWifiWpapsk[ulLoop]));
        if (VOS_OK != ulRet)
        {
            *pusCsdValue = AT_CUSTOMIZE_ITEM_DEFAULT_VAL_CHANGED;
            return VOS_OK;
        }

        ulRet = AT_JudgeU8ArrayZero(stWifiKey.aucWifiWepKey1[ulLoop], sizeof(stWifiKey.aucWifiWepKey1[ulLoop]));
        if (VOS_OK != ulRet)
        {
            *pusCsdValue = AT_CUSTOMIZE_ITEM_DEFAULT_VAL_CHANGED;
            return VOS_OK;
        }

        ulRet = AT_JudgeU8ArrayZero(stWifiKey.aucWifiWepKey2[ulLoop], sizeof(stWifiKey.aucWifiWepKey2[ulLoop]));
        if (VOS_OK != ulRet)
        {
            *pusCsdValue = AT_CUSTOMIZE_ITEM_DEFAULT_VAL_CHANGED;
            return VOS_OK;
        }

        ulRet = AT_JudgeU8ArrayZero(stWifiKey.aucWifiWepKey3[ulLoop], sizeof(stWifiKey.aucWifiWepKey3[ulLoop]));
        if (VOS_OK != ulRet)
        {
            *pusCsdValue = AT_CUSTOMIZE_ITEM_DEFAULT_VAL_CHANGED;
            return VOS_OK;
        }

        ulRet = AT_JudgeU8ArrayZero(stWifiKey.aucWifiWepKey4[ulLoop], sizeof(stWifiKey.aucWifiWepKey4[ulLoop]));
        if (VOS_OK != ulRet)
        {
            *pusCsdValue = AT_CUSTOMIZE_ITEM_DEFAULT_VAL_CHANGED;
            return VOS_OK;
        }

        ulRet = AT_JudgeU8ArrayZero(stWifiSsid.aucWifiSsid[ulLoop], sizeof(stWifiSsid.aucWifiSsid[ulLoop]));
        if (VOS_OK != ulRet)
        {
            *pusCsdValue = AT_CUSTOMIZE_ITEM_DEFAULT_VAL_CHANGED;
            return VOS_OK;
        }
    }

    *pusCsdValue = AT_CUSTOMIZE_ITEM_DEFAULT_VAL_UNCHANGE;
    return VOS_OK;

}
/* Modify by z60575 for multi_ssid, 2012-9-5 end */

/*****************************************************************************
     : AT_GetCsdValue
   : 
   : VOS_BOOL                            bSimlockEnableFlg
             VOS_UINT16                         *pusCsdValue
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 2012410
           : l60609
       : 
  2.       : 2012518
           : z60575
       : :DTS2012051806821, NVen_NV_Item_WAS_RadioAccess_Capa_New
  3.       : 2012720
           : f62575
       : :DTS2012071402176, 50009,8271,8317,8233,9007,21
                 NV6267,6268,626950012,52000

*****************************************************************************/
VOS_UINT32 AT_GetCsdValue(
    VOS_BOOL                            bSimlockEnableFlg,
    VOS_UINT16                         *pusCsdValue)
{
    /* Modified by f62575 for B050 Project, 2012-2-3, Begin   */
    VOS_UINT32                          ulRet;
    /* Modified by f62575 for B050 Project, 2012-2-3, End     */

    /*SIM LOCK StatusDISABLE */
    /*SIM Lock Status*/
    if (VOS_FALSE != bSimlockEnableFlg)
    {
        *pusCsdValue = AT_CUSTOMIZE_ITEM_DEFAULT_VAL_CHANGED;
        return VOS_OK;
    }

    /* WIFINV */
    ulRet = AT_GetWifiNvValue(pusCsdValue);

    return ulRet;
}

/* Added by f62575 for B050 Project, 2012-2-3, Begin   */
/*****************************************************************************
     : AT_OutputCsdfltDefault
   : ,:
             <CR><LF>^CSDFLT: < value_info > <CR><LF>\
             <CR><LF>^CSDFLT: <item>,<value><CR><LF>\
             [....]\
             <CR><LF>OK<CR><LF>
   : VOS_UINT8                           ucIndex           - 
             VOS_BOOL                            bSimlockEnableFlg - SIMLOCK
   : 
     : AT_OK    - 
             AT_DEVICE_OTHER_ERROR - 
   :
   :

       :
  1.       : 20120204
           : f62575
       : B050 SIMLOCK: SIMLOCK
                 
*****************************************************************************/
VOS_UINT32 AT_OutputCsdfltDefault(
    VOS_UINT8                           ucIndex,
    VOS_BOOL                            bSimlockEnableFlg
)
{
    VOS_UINT16                          usLength;
    VOS_UINT32                          ulCsdfltFlg;
    VOS_UINT16                          usCsdfltValue;
    VOS_UINT32                          ulRslt;

    ulCsdfltFlg = VOS_TRUE;

    ulRslt = AT_GetCsdValue(bSimlockEnableFlg, &usCsdfltValue);

    if (VOS_OK != ulRslt)
    {
        return AT_ERROR;
    }

    /* 0:;
                       1: */
    if (AT_CUSTOMIZE_ITEM_DEFAULT_VAL_UNCHANGE == usCsdfltValue)
    {
        ulCsdfltFlg = VOS_FALSE;
    }

    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pgucAtSndCodeAddr,
                                      (VOS_CHAR*)pgucAtSndCodeAddr, "%s:%d",
                                      g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                      ulCsdfltFlg);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;

}
/* Added by f62575 for B050 Project, 2012-2-3, End   */

/*****************************************************************************
     : At_SimlockPlmnNumToAscii
   : SimlockPlmnAscii:
             {0x23,0x00,0x1F} --> "23001"
   : pucPlmnRange     - Plmn
             ucPlmnRangeLen   - PlmnImsiStr
   : pcAsciiStr  - ASCII('\0')
     :
   :
   :

       :
  1.       : 2010818
           : l00130025
       : 

*****************************************************************************/
VOS_UINT32  At_SimlockPlmnNumToAscii(
    const VOS_UINT8                     *pucPlmnRange,
    VOS_UINT8                           ucPlmnRangeLen,
    VOS_UINT8                            *pucAsciiStr
)
{
    VOS_UINT8                           ucLoop;
    VOS_UINT8                           ucLen;
    VOS_UINT8                           ucBcdCode;

    if ((VOS_NULL_PTR == pucPlmnRange)
     || (VOS_NULL_PTR == pucAsciiStr))
    {
        AT_WARN_LOG("At_SimlockPlmnNumToAscii: Parameter of the function is null.");
        return AT_FAILURE;
    }

    /*0XFF*/
    while (ucPlmnRangeLen > 1)
    {
        if (0xFF == pucPlmnRange[ucPlmnRangeLen - 1])
        {
            ucPlmnRangeLen--;
        }
        else
        {
            break;
        }
    }

    /*pucPlmnRange1111
    */
    if ((pucPlmnRange[ucPlmnRangeLen - 1] & 0x0F) == 0x0F)
    {
        ucLen = (VOS_UINT8)((ucPlmnRangeLen * 2) - 1);
    }
    else
    {
        ucLen = (VOS_UINT8)(ucPlmnRangeLen * 2);
    }

    /**/
    for (ucLoop = 0; ucLoop < ucLen; ucLoop++)
    {
        /*0*/
        if (0 == (ucLoop % 2))
        {
            /*4*/
            ucBcdCode = ((pucPlmnRange[(ucLoop / 2)] >> 4) & 0x0F);
        }
        else
        {
            /*4*/
            ucBcdCode = (pucPlmnRange[(ucLoop / 2)] & 0x0F);
        }

        /*Ascii*/
        if (ucBcdCode <= 9)
        {
            pucAsciiStr[ucLoop] = (ucBcdCode + '0');
        }
        else
        {
            return AT_FAILURE;
        }
    }

    pucAsciiStr[ucLoop] = '\0';      /*0*/

    return AT_SUCCESS;
}

/*****************************************************************************
     : At_QrySimLockPlmnInfo
   : SimlockPlmn
   : VOS_UINT8 ucIndex 
   : 
     : AT_OK --- 
             AT_ERROR --- 
   :
   :

       :
  1.       : 2010810
           : l00130025
       : 
  2.       : 2012810
           : L00171473
       : DTS2012082204471, TQE
*****************************************************************************/
VOS_UINT32 At_QrySimLockPlmnInfo(VOS_UINT8 ucIndex)
{
    TAF_CUSTOM_SIM_LOCK_PLMN_INFO_STRU  stSimLockPlmnInfo;
    VOS_UINT32                          i;
    VOS_UINT16                          usLength;
    VOS_UINT8                           ucMncLen;
    VOS_UINT32                          ulPlmnIdx;
    VOS_UINT32                          ulRsltChkPlmnBegin;
    VOS_UINT32                          ulRsltChkPlmnEnd;
    VOS_UINT32                          ulTotalPlmnNum;
    VOS_BOOL                            abPlmnValidFlg[TAF_MAX_SIM_LOCK_RANGE_NUM] = {VOS_FALSE};
    VOS_UINT8                           aucAsciiNumBegin[(TAF_PH_SIMLOCK_PLMN_STR_LEN * 2) + 1];
    VOS_UINT8                           aucAsciiNumEnd[(TAF_PH_SIMLOCK_PLMN_STR_LEN * 2) + 1];


    TAF_MEM_SET_S(&stSimLockPlmnInfo, sizeof(stSimLockPlmnInfo), 0x00, sizeof(stSimLockPlmnInfo));


    if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_CustomizeSimLockPlmnInfo,
                       &stSimLockPlmnInfo,
                       sizeof(stSimLockPlmnInfo)))
    {
        return AT_ERROR;
    }

    ulTotalPlmnNum = 0;

    if (NV_ITEM_DEACTIVE == stSimLockPlmnInfo.ulStatus)
    {
        /* Plmn0 */
        usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr, "%s:%d",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName,ulTotalPlmnNum);

        gstAtSendData.usBufLen = usLength;
        return AT_OK;
    }

    /*  Plmn */
    for ( i = 0; i < TAF_MAX_SIM_LOCK_RANGE_NUM; i++ )
    {
        ucMncLen = stSimLockPlmnInfo.astSimLockPlmnRange[i].ucMncNum;

        ulRsltChkPlmnBegin = At_SimlockPlmnNumToAscii(stSimLockPlmnInfo.astSimLockPlmnRange[i].aucRangeBegin,
                                    TAF_PH_SIMLOCK_PLMN_STR_LEN,aucAsciiNumBegin);

        ulRsltChkPlmnEnd = At_SimlockPlmnNumToAscii(stSimLockPlmnInfo.astSimLockPlmnRange[i].aucRangeBegin,
                                    TAF_PH_SIMLOCK_PLMN_STR_LEN,aucAsciiNumEnd);

        if ((AT_SUCCESS == ulRsltChkPlmnBegin)
         && (AT_SUCCESS == ulRsltChkPlmnEnd)
         && ((ucMncLen <= 3) && (ucMncLen >= 2)))
        {
            abPlmnValidFlg[i] = VOS_TRUE;
            ++ ulTotalPlmnNum;
        }
    }

    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr, "%s:%d",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName,ulTotalPlmnNum);


    if (0 == ulTotalPlmnNum)
    {
        gstAtSendData.usBufLen = usLength;
        return AT_OK;
    }
    else
    {
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr,
                                    (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                    "%s", gaucAtCrLf);
    }


    ulPlmnIdx = 0;
    for ( i = 0; i < TAF_MAX_SIM_LOCK_RANGE_NUM; i++ )
    {
        if (VOS_FALSE == abPlmnValidFlg[i])
        {
            continue;
        }

        ++ ulPlmnIdx;

        At_SimlockPlmnNumToAscii(stSimLockPlmnInfo.astSimLockPlmnRange[i].aucRangeBegin,
                                    TAF_PH_SIMLOCK_PLMN_STR_LEN,aucAsciiNumBegin);

        At_SimlockPlmnNumToAscii(stSimLockPlmnInfo.astSimLockPlmnRange[i].aucRangeEnd,
                                    TAF_PH_SIMLOCK_PLMN_STR_LEN,aucAsciiNumEnd);

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr,
                                    (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                    "%s:%d,%d,%s,%s",
                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                    ulPlmnIdx,
                                    stSimLockPlmnInfo.astSimLockPlmnRange[i].ucMncNum,
                                    aucAsciiNumBegin,
                                    aucAsciiNumEnd);

        if (ulPlmnIdx < ulTotalPlmnNum)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr,
                                            (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                            "%s", gaucAtCrLf);
        }
    }

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}
/*****************************************************************************
     : At_QryMaxLockTimes
   : Simlock
   : VOS_UINT8 ucIndex
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 2010814
           : l00130025
       : 
  2.       : 2012810
           : L00171473
       : DTS2012082204471, TQE
*****************************************************************************/
VOS_UINT32 At_QryMaxLockTimes(VOS_UINT8 ucIndex)
{
    TAF_CUSTOM_SIM_LOCK_MAX_TIMES_STRU          stSimLockMaxTimes;
    VOS_UINT32                                  ulResult;
    VOS_UINT16                                  usLength;


    stSimLockMaxTimes.ulStatus       = NV_ITEM_DEACTIVE;
    stSimLockMaxTimes.ulLockMaxTimes = 0;


    ulResult = NV_ReadEx(MODEM_ID_0, en_NV_Item_CustomizeSimLockMaxTimes,
                       &stSimLockMaxTimes,
                       sizeof(stSimLockMaxTimes));
    if (NV_OK != ulResult)
    {
        AT_WARN_LOG("At_QryMaxLockTimes():en_NV_Item_CustomizeSimLockMaxTimes NV_ReadEx Fail!");
        return AT_DEVICE_OTHER_ERROR;
    }


    /* NV 10 */
    if (NV_ITEM_DEACTIVE == stSimLockMaxTimes.ulStatus)
    {
        usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR*)pgucAtSndCodeAddr, "%s:%d",
                                          g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                          TAF_PH_CARDLOCK_DEFAULT_MAXTIME);
    }
    else
    {
        usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR*)pgucAtSndCodeAddr, "%s:%d",
                                          g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                          stSimLockMaxTimes.ulLockMaxTimes);
    }

    gstAtSendData.usBufLen = usLength;

    return AT_OK;

}

/*****************************************************************************
     : At_QryAppWronReg
   : 
   : VOS_UINT8 ucIndex
   : 
     : VOS_UINT32:
   :
   :

       :
  1.       : 201098
           : zhoujun /40661
       : 

  2.       : 20111015
           : o00132663
       : ATAPI

  3.       : 20150327
           : K00902809
       : Added seperate function TAF_MMA_QryAppwronregReq to send message to mma
*****************************************************************************/
VOS_UINT32  At_QryAppWronReg( VOS_UINT8 ucIndex )
{
    /* MMA */

    /* Modified by k902809 for Iteration 11, 2015-3-27, begin */
    if(VOS_TRUE == TAF_MMA_QryApPwrOnAndRegTimeReq(WUEPS_PID_AT,
                                                   gastAtClientTab[ucIndex].usClientId,
                                                   0))
    /* Modified by k902809 for Iteration 11, Iteration 11 2015-3-27, end */
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_REGISTER_TIME_READ;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}

/*****************************************************************************
 Prototype      : At_QryNdisdupPara
 Description    : ^NDISDUP?
 Input          : ucIndex --- 
 Output         :
 Return Value   :
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2009-08-27
    Author      : L47619
    Modification: Created function
  2.Date        : 2011-01-14
    Author      : c00173809
    Modification: DTS2011042202062,VDF
  3.       : 20110428
           : o00132663
       : DTS2011042800390,AT^NDISDUPERROR
  4.       : 20111212
           : L00171473
       : : DTS2011110807367, PCUINDIS(
                 PCUINDIS)
  5.       : 20120327
           : f00179208
       : :DTS2012032107203, AT^NDISDUP?OK
*****************************************************************************/
VOS_UINT32 At_QryNdisdupPara(
    VOS_UINT8                           ucIndex
)
{
    /* PDP TYPE OK */
    return AT_OK;
}

/*****************************************************************************
     : At_QryNdisConnPara
   : NDIS
   : TAF_UINT8 ucIndex
   : 
     : vos_OK
   :
   :

       :
  1.       : 2010521
           : s62952
       : 
  2.       : 201152
           : w00199382
       : DTS2012042803139

*****************************************************************************/
VOS_UINT32 At_QryNdisConnPara(
    VOS_UINT8                           ucIndex
)
{
    /* Modified by s62952 for BalongV300R002 Build 2012-02-28, begin */
    /*--------------------------------------------------------------
       , , ,
       PS, 
    --------------------------------------------------------------*/
    AT_NDISCONN_PARA_STRU              *pstNdisConnDialInfo;
    VOS_UINT16                          usLength;

    /* NDISCONN */
    usLength            = 0;
    pstNdisConnDialInfo = AT_GetNdisConnParaAddr();

    /* ^NDISCONN:  */
    usLength =  (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR*)pgucAtSndCodeAddr, "%s:", "^NDISCONN");

    /*<pdpid>*/
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength, "%d", pstNdisConnDialInfo->ucCID);


    /*APN*/
    if ( (AT_PDP_STATE_IDLE == g_stAtNdisDhcpPara.enIpv4State)
      && (AT_PDP_STATE_IDLE == g_stAtNdisDhcpPara.enIpv6State)
      && (AT_PDP_STATE_IDLE == g_stAtNdisDhcpPara.enIpv4v6State) )
    {
        /*<connect>*/
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength, ",%d", 0);
    }
    else
    {
        /*<connect>*/
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength, ",%d", pstNdisConnDialInfo->ulConnectState);

        /*<APN>*/
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength, ",\"%s\"", pstNdisConnDialInfo->aucAPN);

        /*<username>*/
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength, ",\"%s\"", pstNdisConnDialInfo->aucUsername);

        /*<passwd>*/
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength, ",\"%s\"", pstNdisConnDialInfo->aucPassword);

        /*<auth>*/
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength, ",%d", pstNdisConnDialInfo->usAuthType);
    }
    gstAtSendData.usBufLen = usLength;
    /* Modified by s62952 for BalongV300R002 Build 2012-02-28, end */



    return AT_OK;
}

/* Modified by s62952 for BalongV300R002 Build 2012-02-28, begin */
/*****************************************************************************
     : AT_NdisGetConnStatus
   : NDIS
   : enPdpState                 - PDP
   : 
     : AT_PDP_STATUS_ACT          - NDIS
             AT_PDP_STATUS_DEACT        - NDIS
   :
   :

       :
  1.       : 20111015
           : A00165503
       : 

*****************************************************************************/
AT_PDP_STATUS_ENUM_UINT32 AT_NdisGetConnStatus(
    AT_PDP_STATE_ENUM_U8                enPdpState
)
{
    AT_PDP_STATUS_ENUM_UINT32           enConnStatus;

    enConnStatus                        = AT_PDP_STATUS_DEACT;

    if ( (AT_PDP_STATE_ACTED    == enPdpState)
      || (AT_PDP_STATE_DEACTING == enPdpState) )
    {
        enConnStatus = AT_PDP_STATUS_ACT;
    }

    return enConnStatus;
}

/*****************************************************************************
     : AT_ReportNdisStatInfo
   : GUNDIS
   : VOS_UINT8 ucIndex
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 20111021
           : A00165503
       : 

*****************************************************************************/
VOS_UINT32 AT_ReportNdisStatInfo(VOS_UINT8 ucIndex)
{
    VOS_UINT16                          usLength;
    AT_PDP_STATUS_ENUM_UINT32           enIpv4Status;

    /*  */
    usLength        = 0;
    enIpv4Status    = AT_PDP_STATUS_DEACT;

    /*  */
    if (AT_PDP_STATE_ACTED == AT_NdisGetState(TAF_PDP_IPV4))
    {
        enIpv4Status = AT_PDP_STATUS_ACT;
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
                                       enIpv4Status);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}

/*****************************************************************************
     : AT_QryNdisStatPara
   : PDP TYPE
   : ucIndex --- 
   : 
     : 
             

   :
   :

       :
  1.       : 201153
           : s62952
       : 
  2.       : 20111217
           : C00173809
       : PS,NDIS
*****************************************************************************/
VOS_UINT32 AT_QryNdisStatPara(
    VOS_UINT8                           ucIndex
)
{
    AT_PDP_STATUS_ENUM_UINT32           enIpv4Status;
    AT_PDP_STATUS_ENUM_UINT32           enIpv6Status;
    AT_PDP_STATUS_ENUM_UINT32           enIpv4v6Status;
    VOS_UINT16                          usLength;
    VOS_UINT8                           aucAtStrIpv4[] = "IPV4";
    VOS_UINT8                           aucAtStrIpv6[] = "IPV6";

    usLength                            = 0;
    enIpv4Status                        = AT_PDP_STATUS_DEACT;
    enIpv6Status                        = AT_PDP_STATUS_DEACT;
    enIpv4v6Status                      = AT_PDP_STATUS_DEACT;

    switch (AT_GetIpv6Capability())
    {
        case AT_IPV6_CAPABILITY_IPV4_ONLY:
            enIpv4Status = AT_NdisGetConnStatus(AT_NdisGetState(TAF_PDP_IPV4));

            usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR*)pgucAtSndCodeAddr,
                                               (VOS_CHAR*)pgucAtSndCodeAddr,
                                               "%s: ",
                                               g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR*)pgucAtSndCodeAddr,
                                               (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                               "%d,,,\"%s\"",
                                               enIpv4Status,
                                               aucAtStrIpv4);
            break;

        case AT_IPV6_CAPABILITY_IPV6_ONLY:
            enIpv6Status    = AT_NdisGetConnStatus(AT_NdisGetState(TAF_PDP_IPV6));

            usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR*)pgucAtSndCodeAddr,
                                               (VOS_CHAR*)pgucAtSndCodeAddr,
                                               "%s: ",
                                               g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR*)pgucAtSndCodeAddr,
                                               (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                               "%d,,,\"%s\"",
                                               enIpv6Status,
                                               aucAtStrIpv6);
            break;

        case AT_IPV6_CAPABILITY_IPV4V6_OVER_ONE_PDP:
            enIpv4v6Status  = AT_NdisGetConnStatus(AT_NdisGetState(TAF_PDP_IPV4V6));
            if ( AT_PDP_STATUS_ACT != enIpv4v6Status )
            {
                enIpv4Status = AT_NdisGetConnStatus(AT_NdisGetState(TAF_PDP_IPV4));
                enIpv6Status = AT_NdisGetConnStatus(AT_NdisGetState(TAF_PDP_IPV6));
            }
            else
            {
                enIpv4Status = enIpv4v6Status;
                enIpv6Status = enIpv4v6Status;
            }

            usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR*)pgucAtSndCodeAddr,
                                               (VOS_CHAR*)pgucAtSndCodeAddr,
                                               "%s: ",
                                               g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR*)pgucAtSndCodeAddr,
                                               (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                               "%d,,,\"%s\"",
                                               enIpv4Status,
                                               aucAtStrIpv4);
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR*)pgucAtSndCodeAddr,
                                               (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                               ",%d,,,\"%s\"",
                                               enIpv6Status,
                                               aucAtStrIpv6);
            break;

        case AT_IPV6_CAPABILITY_IPV4V6_OVER_TWO_PDP:
            enIpv4Status = AT_NdisGetConnStatus(AT_NdisGetState(TAF_PDP_IPV4));
            enIpv6Status = AT_NdisGetConnStatus(AT_NdisGetState(TAF_PDP_IPV6));

            usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR*)pgucAtSndCodeAddr,
                                               (VOS_CHAR*)pgucAtSndCodeAddr,
                                               "%s: ",
                                               g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR*)pgucAtSndCodeAddr,
                                               (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                               "%d,,,\"%s\"",
                                               enIpv4Status,
                                               aucAtStrIpv4);
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR*)pgucAtSndCodeAddr,
                                               (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                               ",%d,,,\"%s\"",
                                               enIpv6Status,
                                               aucAtStrIpv6);
            break;

        default:
            break;
    }
    gstAtSendData.usBufLen = usLength;

    return AT_OK;

}

/*****************************************************************************
     : At_QryNdisAddPara
   : NDIS
   : TAF_UINT8 ucIndex
   : 
     : TAF_UINT32
   :
   :

       :
  1.       : 2010521
           : s62952
       : 

*****************************************************************************/
TAF_UINT32 At_QryNdisAddPara(VOS_UINT8 ucIndex)
{
    return AT_CMD_NOT_SUPPORT;
}
/* Modified by s62952 for BalongV300R002 Build 2012-02-28, end */

/*****************************************************************************
     : At_QryDnsPrim
   : NDISDNS
   : VOS_UINT8 ucIndex
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 20101027
           : /00166186
       : 

  2.       : 20110818
           : A00165503
       : : DTS2011081400480, ^DNSP^DNSSHiLink

  3.       : 20111020
           : s62952
       : AT Project: RNIC
  4.       : 20111212
           : L00171473
       : : DTS2011110807367, PCUINDIS(
                 PCUINDIS)
  5.       : 20120320
           : f00179208
       : : DTS2012031400837, CMDipconfig /all
                 DNS
*****************************************************************************/
VOS_UINT32 At_QryDnsPrim(
    VOS_UINT8                           ucIndex
)
{
    TAF_UINT16                          usLength;
    VOS_UINT32                          ulPdpStateFlag;
    /* Modified by s62952 for BalongV300R002 Build 2012-02-28, begin */
    AT_PDP_STATE_ENUM_U8                enState;
    /* Modified by s62952 for BalongV300R002 Build 2012-02-28, end */

    AT_DIAL_PARAM_STRU                 *pstAppDialPara;

    pstAppDialPara                      = AT_APP_GetDailParaAddr();

    ulPdpStateFlag                      = VOS_FALSE;
    usLength                            = 0;

    if (AT_APP_USER == gastAtClientTab[ucIndex].UserType)
    {
        ulPdpStateFlag = AT_AppCheckIpv4PdpState(AT_PDP_STATE_ACTED);
        if (VOS_TRUE != ulPdpStateFlag)
        {
            AT_WARN_LOG("At_QryDnsPrim:WARNING: PDP is not ativated!");
            return AT_CME_NO_CONNECTION_TO_PHONE;
        }

        if (VOS_FALSE == pstAppDialPara->ulPrimIPv4DNSValidFlag)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                   (VOS_CHAR*)pgucAtSndCodeAddr,
                                   (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                   "%s: %s",
                                   g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                   "0.0.0.0");
        }
        else
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR*)pgucAtSndCodeAddr,
                                               (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                               "%s: %s",
                                               g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                               pstAppDialPara->aucPrimIPv4DNSAddr);
        }

        gstAtSendData.usBufLen = usLength;

        return AT_OK;
    }

    enState = AT_NdisGetState(TAF_PDP_IPV4);
    if(AT_PDP_STATE_ACTED == enState)
    {
       ulPdpStateFlag = VOS_TRUE;
    }

    if (VOS_FALSE == ulPdpStateFlag)
    {
        AT_WARN_LOG("At_QryDnsPrim AT_NdisGetState:");
        return AT_CME_NO_CONNECTION_TO_PHONE;
    }

    if (VOS_FALSE == gstAtNdisAddParam.ulPrimIPv4DNSValidFlag)
    {
        usLength    += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR*)pgucAtSndCodeAddr,
                                               "%s",
                                               "^DNSP: 0.0.0.0");
    }
    else
    {
        usLength    += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR*)pgucAtSndCodeAddr,
                                               "%s: %s",
                                               "^DNSP",
                                               gstAtNdisAddParam.aucPrimIPv4DNSAddr);
    }

    gstAtSendData.usBufLen = usLength;

    return AT_OK;

}

/*****************************************************************************
     : At_QryDnsSnd
   : NDISDNS
   : VOS_UINT8 ucIndex
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 20101027
           : /00166186
       : 

  2.       : 20110818
           : A00165503
       : : DTS2011081400480, ^DNSP^DNSSHiLink

  3.       : 20111020
           : s62952
       : AT Project: RNIC
  4.       : 20111212
           : L00171473
       : : DTS2011110807367, PCUINDIS(
                 PCUINDIS)
  5.       : 20120320
           : f00179208
       : : DTS2012031400837, CMDipconfig /all
                 DNS
*****************************************************************************/
VOS_UINT32 At_QryDnsSnd(
    VOS_UINT8                           ucIndex
)
{
    TAF_UINT16                          usLength;
    VOS_UINT32                          ulPdpStateFlag;
    AT_PDP_STATE_ENUM_U8                enState;
    AT_DIAL_PARAM_STRU                 *pstAppDialPara;

    pstAppDialPara                      = AT_APP_GetDailParaAddr();

    ulPdpStateFlag                      = VOS_FALSE;
    usLength                            = 0;

    if (AT_APP_USER == gastAtClientTab[ucIndex].UserType)
    {
        ulPdpStateFlag = AT_AppCheckIpv4PdpState(AT_PDP_STATE_ACTED);
        if (VOS_TRUE != ulPdpStateFlag)
        {
            AT_WARN_LOG("At_QryDnsPrim:WARNING: PDP is not ativated!");
            return AT_CME_NO_CONNECTION_TO_PHONE;
        }

        if (VOS_FALSE == pstAppDialPara->ulSndIPv4DNSValidFlag)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR*)pgucAtSndCodeAddr,
                                               (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                               "%s: %s",
                                               g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                               "0.0.0.0");
        }
        else
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR*)pgucAtSndCodeAddr,
                                               (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                               "%s: %s",
                                               g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                               pstAppDialPara->aucSndIPv4DNSAddr);

        }

        gstAtSendData.usBufLen = usLength;

        return AT_OK;
    }

    enState = AT_NdisGetState(TAF_PDP_IPV4);
    if(AT_PDP_STATE_ACTED == enState)
    {
       ulPdpStateFlag = VOS_TRUE;
    }

    if (VOS_FALSE == ulPdpStateFlag)
    {
        AT_WARN_LOG("At_QryDnsPrim AT_NdisGetState:");
        return AT_CME_NO_CONNECTION_TO_PHONE;
    }

    if (VOS_FALSE == gstAtNdisAddParam.ulSndIPv4DNSValidFlag)
    {
        usLength    += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR*)pgucAtSndCodeAddr,
                                               "%s",
                                               "^DNSS: 0.0.0.0");
    }
    else
    {
        usLength    += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR*)pgucAtSndCodeAddr,
                                               "%s: %s",
                                               "^DNSS:",
                                               gstAtNdisAddParam.aucSndIPv4DNSAddr);
    }

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}

/*****************************************************************************
     : At_QryApDialModePara
   : 
   : TAF_UINT8 ucIndex
   : 
     :
   :
   :

       :
 1.       : 201099
          : s62952
      : 
 2.       : 20111208
          : f00179208
      : PS Project: RNIC

*****************************************************************************/
VOS_UINT32  At_QryApDialModePara(
    VOS_UINT8                           ucIndex
)
{
    AT_RNIC_DIAL_MODE_REQ_STRU         *pstMsg;

    /* ID_RNIC_AT_DIAL_MODE_REQ */
    pstMsg = (AT_RNIC_DIAL_MODE_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                            WUEPS_PID_AT,
                            sizeof(AT_RNIC_DIAL_MODE_REQ_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        AT_WARN_LOG("At_QryApDialModePara: alloc msg fail!");
        return VOS_ERR;
    }

    /*  */
    TAF_MEM_SET_S((VOS_CHAR *)pstMsg + VOS_MSG_HEAD_LENGTH,
               (VOS_SIZE_T)(sizeof(AT_RNIC_DIAL_MODE_REQ_STRU) - VOS_MSG_HEAD_LENGTH),
               0x00,
               (VOS_SIZE_T)(sizeof(AT_RNIC_DIAL_MODE_REQ_STRU) - VOS_MSG_HEAD_LENGTH));

    /*  */
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = ACPU_PID_RNIC;
    pstMsg->enMsgId         = ID_AT_RNIC_DIAL_MODE_REQ;
    pstMsg->clientId        = gastAtClientTab[ucIndex].usClientId;

    /* ID_RNIC_AT_DIAL_MODE_REQRNIC */
    if (VOS_OK == PS_SEND_MSG(WUEPS_PID_AT, pstMsg))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_APDIALMODE_READ;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        AT_WARN_LOG("At_QryApDialModePara: Send msg failed!");
        return AT_ERROR;
    }
}

/*****************************************************************************
     : AT_QryAppdmverPara
   : PDM
   : VOS_UINT8 ucIndex
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 201098
           : lijun 00171473
       : 
  2.       : 2011104
           : f62575
       : AT Project
                 PDMDRV_MEM_VERCTRL(memVersionCtrl)C
                 C
*****************************************************************************/
VOS_UINT32  AT_QryAppdmverPara ( VOS_UINT8 ucIndex )
{
    /* Modified  by f62575 for AT Project, 2011-10-17, begin */
    VOS_UINT32                          ulRet;

    /* C PDM */
    ulRet = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   DRV_AGENT_APPDMVER_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_WUEPS_PID_DRV_AGENT);
    if (TAF_SUCCESS != ulRet)
    {
        AT_WARN_LOG("AT_QryAppdmverPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* AT */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_APPDMVER_READ;
    return AT_WAIT_ASYNC_RETURN;

    /* Modified  by f62575 for AT Project, 2011-10-17, end */
}

/*****************************************************************************
     : AT_QryDislogPara
   : DISLOG
   : VOS_UINT8 ucIndex
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 2010910
           : lijun 00171473
       : 
  2.       : 20101026
           : lijun 00171473
       :  DTS2010102501711 
  3.       : 20120207
           : f62575
       : B050 PIDNV
                 ^DISLOGNVen_NV_Item_AT_DISLOG_PWD
                 en_NV_Item_Huawei_Dynamic_PID_Type


*****************************************************************************/
VOS_UINT32  AT_QryDislogPara ( VOS_UINT8 ucIndex )
{
    AT_DIAG_OPEN_FLAG_ENUM_U32          enDiagPortState;

    /* Add by w00199382 for V7, 2012-04-07, Begin   */
    VOS_UINT32                          ulRetDiag;
    VOS_UINT32                          ulRet3GDiag;
    VOS_UINT32                          ulRetGps;

    ulRet3GDiag   = AT_ExistSpecificPort(AT_DEV_DIAG);
    ulRetDiag     = AT_ExistSpecificPort(AT_DEV_4G_DIAG);
    ulRetGps      = AT_ExistSpecificPort(AT_DEV_4G_GPS);

    if ((VOS_TRUE == ulRet3GDiag)
      &&(VOS_TRUE == ulRetDiag)
      &&(VOS_TRUE == ulRetGps))
    {
        enDiagPortState = AT_DIAG_OPEN_FLAG_OPEN;
    }
    else
    {
        enDiagPortState = AT_DIAG_OPEN_FLAG_CLOSE;
    }
    /* Add by w00199382 for V7, 2012-04-07, End   */

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR*)pgucAtSndCodeAddr,
                                                    "%s:%d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    enDiagPortState);
    return AT_OK;

}

/*****************************************************************************
     : AT_QryShellPara
   : AT^SHELL?
   : VOS_UINT8 ucIndex
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 2010913
           : lijun 00171473
       : 
  2.       : 20101026
           : lijun 00171473
       :  DTS2010102501778 
  3.       : 2012221
           : l60609
       : B060 Prj:SHELLAT^SHELL?NV33
                 g_enATShellOpenFlag
  4.       : 2012810
           : L00171473
       : DTS2012082204471, TQE
*****************************************************************************/
VOS_UINT32 AT_QryShellPara (VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulShellStatus;


    ulShellStatus = AT_SHELL_CLOSE;


    if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_AT_SHELL_OPEN_FLAG, &ulShellStatus,
                          sizeof(ulShellStatus)))
    {
        AT_WARN_LOG("AT_QryShellPara:WARNING:NV_ReadEx SHELL_OPEN_FLAG faild!");

        return AT_ERROR;
    }

    /* shell0,1,2 */
    if (AT_SHELL_OPEN < ulShellStatus)
    {
        return AT_ERROR;
    }

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR*)pgucAtSndCodeAddr,
                                                    "%s:%d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    ulShellStatus);
    return AT_OK;

}

/* Added by f62575 for SMALL IMAGE, 2012-1-3, Begin   */
/*****************************************************************************
     : AT_QryWifiGlobalMacPara
   : MAC
   : ucIndex - 
   : 
     : AT_OK    - 
             AT_ERROR - 
   :
   :

       :
  1.       : 201099
           : z00161729
       : 
  2.       : 2010119
           : s62952
       :  :DTS2010110403564,MACE5mac
  3.       : 20111115
           : /f62575
       : E5
*****************************************************************************/
VOS_UINT32 AT_QryWifiGlobalMacPara(VOS_UINT8 ucIndex)
/* Added by f62575 for SMALL IMAGE, 2012-1-3, End   */
{
    VOS_UINT16                          usLength;
    VOS_UINT32                          ulResult;
    /* Added by /f62575 for E5, 2011/11/15, begin */
    VOS_UINT8                           aucE5GwMacAddr[AT_MAC_ADDR_LEN+1]; /* MAC*/

    /* MAC*/
    ulResult = NV_ReadEx(MODEM_ID_0, en_NV_Item_WIFI_MAC_ADDR, aucE5GwMacAddr, AT_MAC_ADDR_LEN);
    aucE5GwMacAddr[AT_MAC_ADDR_LEN] = '\0';
    /* Added by /f62575 for AT Project, 2011/11/15, end */

    if ( NV_OK != ulResult )
    {
        AT_WARN_LOG("AT_QryApMacPara:read en_NV_Item_GWMAC_ADDR failed or no need to updatee");
        return AT_ERROR;
    }

    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      (VOS_CHAR*)pgucAtSndCodeAddr, "%s:%s",
                                      g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                      aucE5GwMacAddr);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;

}

/* Added by f62575 for AT Project, 2011-10-04,  Begin */

/*****************************************************************************
     : AT_QryDloadInfoPara
   : 
             
             <CR><LF>swver:<software version><CR><LF>
             <CR><LF>isover:<iso version><CR><LF>
             <CR><LF>product name:<product name><CR><LF>
             <CR><LF>dload type: <dload type><CR><LF>
             <CR><LF>OK<CR><LF>
   : VOS_UINT8 ucIndex
   : 
     : VOS_ERRVOS_OK
   :
   :

       :
  1.       : 2011219
           : s62952
       : 
  2.       : 2011219
           : w00166186
       : WEBUI
  3.       : 201188
           : /f62575
       : DTS2011080805707 
  4.       : 2011817
           : /f62575
       : DTS2011081700388 dload type10
  5.       : 2011106
           : f62575
       : AT Project
                 
                 DRV_GET_DLOAD_INFO(getDloadInfo)C
                 C
*****************************************************************************/
VOS_UINT32 AT_QryDloadInfoPara( VOS_UINT8 ucIndex )
{
    /* Modified  by f62575 for AT Project, 2011-10-17, begin */
    VOS_UINT32                          ulRet;

    /* C */
    ulRet = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   DRV_AGENT_DLOADINFO_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_WUEPS_PID_DRV_AGENT);
    if (TAF_SUCCESS != ulRet)
    {
        AT_WARN_LOG("AT_QryDloadInfoPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* AT */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_DLOADINFO_READ;
    return AT_WAIT_ASYNC_RETURN;
    /* Modified  by f62575 for AT Project, 2011-10-17, end */
}

/*****************************************************************************
     : AT_QryAuthorityVerPara
   : 
             <CR><LF><Authority Version><CR><LF>
             <CR><LF>OK<CR><LF>
   : VOS_UINT8 ucIndex
   : 
     : VOS_ERRVOS_OK
   :
   :

       :
  1.       : 2011219
           : s62952
       : 

  2.       : 2011106
           : f62575
       : AT Project
                 DRV_GET_AUTHORITY_VERSION(getAuthorityVersion)C
                 C
*****************************************************************************/
VOS_UINT32 AT_QryAuthorityVerPara( VOS_UINT8 ucIndex )
{
    /* Modified  by f62575 for AT Project, 2011-10-17, begin */
    VOS_UINT32                          ulRet;

    /* C */
    ulRet = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   DRV_AGENT_AUTHORITYVER_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_WUEPS_PID_DRV_AGENT);
    if (TAF_SUCCESS != ulRet)
    {
        AT_WARN_LOG("AT_QryAuthorityVerPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* AT */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_AUTHORITYVER_READ;
    return AT_WAIT_ASYNC_RETURN;
    /* Modified  by f62575 for AT Project, 2011-10-17, end */
}

/*****************************************************************************
     : AT_QryAuthorityIdPara
   : 
             <CR><LF><Authority ID>, <Authority Type><CR><LF>
             <CR><LF>OK<CR><LF>
   : VOS_UINT8 ucIndex
   : 
     : VOS_ERRVOS_OK
   :
   :

       :
  1.       : 2011219
           : s62952
       : 

  2.       : 2011106
           : f62575
       : AT Project
                 DRV_GET_AUTHORITY_ID(getAuthorityId)C
                 C
*****************************************************************************/
VOS_UINT32 AT_QryAuthorityIdPara( VOS_UINT8 ucIndex )
{
    /* Modified  by f62575 for AT Project, 2011-10-17, begin */
    VOS_UINT32                          ulRet;

    /* C */
    ulRet = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   DRV_AGENT_AUTHORITYID_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_WUEPS_PID_DRV_AGENT);
    if (TAF_SUCCESS != ulRet)
    {
        AT_WARN_LOG("AT_QryAuthorityIdPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* AT */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_AUTHORITYID_READ;
    return AT_WAIT_ASYNC_RETURN;
    /* Modified  by f62575 for AT Project, 2011-10-17, end */
}

/*****************************************************************************
     : AT_QryFlashInfoPara
   : FLASH
             <CR><LF>~~~~~~FLASH INFO~~~~~~:<CR><LF>
             <CR><LF>MMC BLOCK COUNT:<blockcount>,
                     PAGE SIZE:<pagesize>,
                     PAGE COUNT PER BLOCK:<blocksize><CR><LF>
             <CR><LF>OK<CR><LF>
   : VOS_UINT8 ucIndex
   : 
     : VOS_ERRVOS_OK
   :
   :

       :
  1.       : 2011219
           : s62952
       : 
  2.       : 20111017
           : /f62575
       : AT PROJECT
                 FLASHDRV_GET_DLOAD_FLASHINFO(getDloadFlashInfo)C
                 C
*****************************************************************************/
VOS_UINT32 AT_QryFlashInfoPara( VOS_UINT8 ucIndex )
{
    /* Modified  by f62575 for AT Project, 2011-10-17, begin */
    VOS_UINT32                          ulRet;

    /* CFLASH */
    ulRet = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   DRV_AGENT_FLASHINFO_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_WUEPS_PID_DRV_AGENT);
    if (TAF_SUCCESS != ulRet)
    {
        AT_WARN_LOG("AT_QryFlashInfoPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* AT */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_FLASHINFO_READ;
    return AT_WAIT_ASYNC_RETURN;
    /* Modified  by f62575 for AT Project, 2011-10-17, end */

}

/*****************************************************************************
     : AT_QryAuthverPara
   : SIMLOCK MANAGER
             <CR><LF>^ AUTHVER: <value> <CR><LF>
             <CR><LF>OK<CR><LF>
             value:
             11.0
             22.0
             

   : VOS_UINT8 ucIndex
   : 
     : VOS_ERRVOS_OK
   :
   :

       :
  1.       : 2011423
           : x00180552
       : 

  2.       : 20120129
           : l00171473
       : DTS2012013000257 SIMLOCK2.0
*****************************************************************************/
VOS_UINT32 AT_QryAuthverPara(VOS_UINT8 ucIndex)
{
    /* Modified  by f62575 for AT Project, 2011-10-17, begin */
    VOS_UINT32                          ulRet;

    /* CSIMLOCK MANAGER */
    ulRet = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   DRV_AGENT_AUTHVER_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_WUEPS_PID_DRV_AGENT);
    if (TAF_SUCCESS != ulRet)
    {
        AT_WARN_LOG("AT_QryAuthverPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* AT */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_AUTHVER_READ;
    return AT_WAIT_ASYNC_RETURN;
    /* Modified  by f62575 for AT Project, 2011-10-17, end */

}

/*****************************************************************************
     : AT_QryWiFiEnablePara
   : Wifi

   : VOS_UINT8 ucIndex 
   : 
     : OK
   :
   :

       :
  1.       : 20110531
           : w00166186
       : 

*****************************************************************************/
VOS_UINT32 AT_QryWiFiEnablePara(VOS_UINT8 ucIndex)
{
    /* WiFi */
    VOS_UINT32                          ulWifiStatus;

    /* Modified by s62952 for BalongV300R002 Build 2012-02-28, begin */
    if (BSP_MODULE_UNSUPPORT == mdrv_misc_support_check(BSP_MODULE_TYPE_WIFI) )
    {
        return AT_ERROR;
    }
    /* Modified by s62952 for BalongV300R002 Build 2012-02-28, begin */

    ulWifiStatus = (VOS_UINT32)WIFI_GET_STATUS();

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%d",
                                                     g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                     ulWifiStatus);
    return AT_OK;
}
/*****************************************************************************
     : AT_QryWiFiModePara
   : Wifi

   : VOS_UINT8 ucIndex
   : 
     : OK
   :
   :

       :
  1.       : 20110531
           : w00166186
       : 
*****************************************************************************/
VOS_UINT32 AT_QryWiFiModePara(VOS_UINT8 ucIndex)
{
    /* Modified by s62952 for BalongV300R002 Build 2012-02-28, begin */
    if (BSP_MODULE_UNSUPPORT == mdrv_misc_support_check(BSP_MODULE_TYPE_WIFI) )
    {
        return AT_ERROR;
    }
    /* Modified by s62952 for BalongV300R002 Build 2012-02-28, begin */

    /* WIFIB/G/N */
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%d",
                                                     g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                     g_ulWifiMode);
    return AT_OK;
}
/*****************************************************************************
     : AT_QryWiFiBandPara
   : Wifi

   : VOS_UINT8 ucIndex 
   : 
     : OK
   :
   :

       :
  1.       : 20110531
           : w00166186
       : 

*****************************************************************************/
VOS_UINT32 AT_QryWiFiBandPara(VOS_UINT8 ucIndex)
{
    /* Modified by s62952 for BalongV300R002 Build 2012-02-28, begin */
    if (BSP_MODULE_UNSUPPORT == mdrv_misc_support_check(BSP_MODULE_TYPE_WIFI) )
    {
        return AT_ERROR;
    }
    /* Modified by s62952 for BalongV300R002 Build 2012-02-28, begin */

    /* 20M */
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%d",
                                                     g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                     AT_WIFI_BAND_20M);
    return AT_OK;
}
/*****************************************************************************
     : AT_QryWiFiFreqPara
   : Wifi

   : VOS_UINT8 ucIndex 
   : 
     : OK
   :
   :

       :
  1.       : 20110531
           : w00166186
       : 

*****************************************************************************/
VOS_UINT32 AT_QryWiFiFreqPara(VOS_UINT8 ucIndex)
{
    /* Modified by s62952 for BalongV300R002 Build 2012-02-28, begin */
    if (BSP_MODULE_UNSUPPORT == mdrv_misc_support_check(BSP_MODULE_TYPE_WIFI) )
    {
        return AT_ERROR;
    }
    /* Modified by s62952 for BalongV300R002 Build 2012-02-28, begin */


    /*  */
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%d",
                                                     g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                     g_ulWifiFreq);
    return AT_OK;
}
/*****************************************************************************
     : AT_QryWiFiRatePara
   : Wifi

   : VOS_UINT8 ucIndex 
   : 
     : OK
   :
   :

       :
  1.       : 20110531
           : w00166186
       : 

*****************************************************************************/
VOS_UINT32 AT_QryWiFiRatePara(VOS_UINT8 ucIndex)
{
    /* Modified by s62952 for BalongV300R002 Build 2012-02-28, begin */
    if (BSP_MODULE_UNSUPPORT == mdrv_misc_support_check(BSP_MODULE_TYPE_WIFI) )
    {
        return AT_ERROR;
    }
    /* Modified by s62952 for BalongV300R002 Build 2012-02-28, begin */

    /*  */
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%d",
                                                     g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                     g_ulWifiRate);
    return AT_OK;
}
/*****************************************************************************
     : AT_QryWiFiPowerPara
   : Wifi

   : VOS_UINT8 ucIndex 
   : 
     : OK
   :
   :

       :
  1.       : 20110531
           : w00166186
       : 

*****************************************************************************/
VOS_UINT32 AT_QryWiFiPowerPara(VOS_UINT8 ucIndex)
{
    /* Modified by s62952 for BalongV300R002 Build 2012-02-28, begin */
    if (BSP_MODULE_UNSUPPORT == mdrv_misc_support_check(BSP_MODULE_TYPE_WIFI) )
    {
        return AT_ERROR;
    }
    /* Modified by s62952 for BalongV300R002 Build 2012-02-28, begin */



    /*  */
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    g_lWifiPower);
    return AT_OK;
}
/*****************************************************************************
     : AT_QryWiFiTxStatusPara
   : Wifi

   : VOS_UINT8 ucIndex
   : 
     : OK
   :
   :

       :
  1.       : 20110531
           : w00166186
       : 

*****************************************************************************/
VOS_UINT32 AT_QryWiFiTxPara(VOS_UINT8 ucIndex)
{
    VOS_UINT8   ucWifiTxStatus;

    /* Modified by s62952 for BalongV300R002 Build 2012-02-28, begin */
    if (BSP_MODULE_UNSUPPORT == mdrv_misc_support_check(BSP_MODULE_TYPE_WIFI) )
    {
        return AT_ERROR;
    }
    /* Modified by s62952 for BalongV300R002 Build 2012-02-28, begin */

    /* WiFi */
    if (AT_WIFI_TX_MODE == WIFI_GET_TCMD_MODE())
    {
        ucWifiTxStatus = AT_WIFI_TX_ON;
    }
    else
    {
        ucWifiTxStatus = AT_WIFI_TX_OFF;
    }

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    ucWifiTxStatus );
    return AT_OK;
}
/*****************************************************************************
     : AT_QryWiFiRxStatusPara
   : Wifi

   : VOS_UINT8 ucIndex
   : 
     : OK
   :
   :

       :
  1.       : 20110531
           : w00166186
       : 

*****************************************************************************/
VOS_UINT32 AT_QryWiFiRxPara(VOS_UINT8 ucIndex)
{
    VOS_UINT8                           ucWifiRxStatus;

    /* Modified by s62952 for BalongV300R002 Build 2012-02-28, begin */
    if (BSP_MODULE_UNSUPPORT == mdrv_misc_support_check(BSP_MODULE_TYPE_WIFI) )
    {
        return AT_ERROR;
    }
    /* Modified by s62952 for BalongV300R002 Build 2012-02-28, begin */


    /* WiFi */
    if (AT_WIFI_RX_MODE == WIFI_GET_TCMD_MODE())
    {
        ucWifiRxStatus = AT_WIFI_TX_ON;
    }
    else
    {
        ucWifiRxStatus = AT_WIFI_TX_OFF;
    }

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    ucWifiRxStatus );
    return AT_OK;
}
/*****************************************************************************
     : AT_QryWiFiPacketPara
   : Wifi

   : VOS_UINT8 ucIndex
   : 
     : OK
   :
   :

       :
  1.       : 20110531
           : w00166186
       : 
  2.       : 20120117
           : l00171473
       : for V3R2 DTS2012020106679,AT WT
*****************************************************************************/
VOS_UINT32 AT_QryWiFiPacketPara(VOS_UINT8 ucIndex)
{
    VOS_UINT                                ulUcastWifiRxPkts;
    VOS_UINT                                ulMcastWifiRxPkts;
    VOS_UINT32                              ulWifiRxPkts;

    /* Modified by s62952 for BalongV300R002 Build 2012-02-28, begin */
    if (BSP_MODULE_UNSUPPORT == mdrv_misc_support_check(BSP_MODULE_TYPE_WIFI) )
    {
        return AT_ERROR;
    }
    /* Modified by s62952 for BalongV300R002 Build 2012-02-28, begin */


    /* Modified by L00171473 for DTS2012020106679,AT WT 2012-01-17  Begin */
    /*  */
    if (AT_WIFI_RX_MODE != WIFI_GET_TCMD_MODE())
    {
        AT_WARN_LOG("AT_QryWiFiPacketPara: Not Rx Mode.");
        return AT_ERROR;
    }

    /*  */
    WIFI_GET_RX_PACKET_REPORT(&ulUcastWifiRxPkts,  &ulMcastWifiRxPkts);
    ulWifiRxPkts = (ulUcastWifiRxPkts - g_ulUcastWifiRxPkts);

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%d,%d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    ulWifiRxPkts,
                                                    0);

    /* Modified by L00171473 for DTS2012020106679,AT WT 2012-01-17  End */

    return AT_OK;
}

/* Modify by z60575 for multi_ssid, 2012-9-5 begin */
/*****************************************************************************
     : AT_QryWiFiSsidPara
   : WIFISSID

   : VOS_UINT8 ucIndex
   : 
     : OK
   :
   :

       :
  1.       : 20110531
           : w00166186
       : 
  2.       : 2012917
           : z60575
       : MULTI_SSID
  3.       : 2013517
           : l00167671
       : NV, NV
*****************************************************************************/
VOS_UINT32 AT_QryWiFiSsidPara(VOS_UINT8 ucIndex)
{
    TAF_AT_MULTI_WIFI_SSID_STRU                             stWifiSsid;
    VOS_UINT16                                              usLen;
    VOS_UINT8                                               ucSsidNum;
    VOS_UINT32                                              ulLoop;
    VOS_UINT8                                               aucSsidLen[AT_WIFI_MAX_SSID_NUM];

    /* Modified by s62952 for BalongV300R002 Build 2012-02-28, begin */
    if (BSP_MODULE_UNSUPPORT == mdrv_misc_support_check(BSP_MODULE_TYPE_WIFI) )
    {
        return AT_ERROR;
    }
    /* Modified by s62952 for BalongV300R002 Build 2012-02-28, begin */

    TAF_MEM_SET_S(&stWifiSsid, sizeof(stWifiSsid), 0x00 ,sizeof(stWifiSsid));

    /*WIFI SSIDNV*/
    if (VOS_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_MULTI_WIFI_STATUS_SSID,&stWifiSsid, sizeof(TAF_AT_MULTI_WIFI_SSID_STRU)))
    {
        AT_WARN_LOG("AT_SetWiFiSsidPara:READ NV ERROR");
        return AT_ERROR;
    }

    ucSsidNum = 0;
    TAF_MEM_SET_S(aucSsidLen, sizeof(aucSsidLen), 0x00, sizeof(aucSsidLen));

    for (ulLoop = 0; ulLoop < AT_WIFI_MAX_SSID_NUM; ulLoop++)
    {
        aucSsidLen[ulLoop] = (VOS_UINT8)VOS_StrLen((VOS_CHAR*)stWifiSsid.aucWifiSsid[ulLoop]);

        if (0 != aucSsidLen[ulLoop])
        {
            ucSsidNum++ ;
        }
    }

    usLen = 0;
    usLen += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                    (TAF_CHAR *)pgucAtSndCodeAddr + usLen,
                                    "%s:%d%s",
                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                    ucSsidNum,
                                    gaucAtCrLf);

    for (ulLoop = 0; ulLoop < AT_WIFI_MAX_SSID_NUM; ulLoop++)
    {
        if (0 != aucSsidLen[ulLoop])
        {
            usLen += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                            (TAF_CHAR *)pgucAtSndCodeAddr,
                                            (TAF_CHAR *)pgucAtSndCodeAddr + usLen,
                                            "%s:%d,%s%s",
                                            g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                            ulLoop,
                                            stWifiSsid.aucWifiSsid[ulLoop],
                                            gaucAtCrLf);
        }
    }

    gstAtSendData.usBufLen = usLen;

    return AT_OK;
}

/*****************************************************************************
     : AT_QryWiFiSsidPara
   : WIFISSID

   : VOS_UINT8 ucIndex
   : 
     : OK
   :
   :

       :
  1.       : 20110531
           : w00166186
       : 
  2.       : 20120117
           : l00171473
       : for V3R2 DTS2012020106679,AT WT
  3.       : 2012917
           : z60575
       : MULTI_SSID
  4.       : 2013517
           : l00167671
       : NV, NV
*****************************************************************************/
VOS_UINT32 AT_QryWiFiLogPara(VOS_UINT8 ucIndex)
{
    TAF_AT_MULTI_WIFI_SSID_STRU                             stWifiSsid;
    TAF_AT_MULTI_WIFI_SEC_STRU                              stWifiSec;
    VOS_UINT16                                              usLen;

    /* Modified by s62952 for BalongV300R002 Build 2012-02-28, begin */
    if (BSP_MODULE_UNSUPPORT == mdrv_misc_support_check(BSP_MODULE_TYPE_WIFI) )
    {
        return AT_ERROR;
    }
    /* Modified by s62952 for BalongV300R002 Build 2012-02-28, begin */

    TAF_MEM_SET_S(&stWifiSec, sizeof(stWifiSec), 0x00, sizeof(stWifiSec));
    TAF_MEM_SET_S(&stWifiSsid, sizeof(stWifiSsid), 0x00, sizeof(stWifiSsid));

    /* Modified by L00171473 for DTS2012020106679,AT WT 2012-01-17  Begin */
    /* WIFI SSIDNV */
    if (VOS_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_MULTI_WIFI_STATUS_SSID,&stWifiSsid, sizeof(TAF_AT_MULTI_WIFI_SSID_STRU)))
    {
        AT_WARN_LOG("AT_QryWiFiLogPara:READ NV FAIL");
        return AT_ERROR;
    }

    usLen = 0;

    usLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                   (TAF_CHAR *)pgucAtSndCodeAddr,
                                   (TAF_CHAR *)pgucAtSndCodeAddr + usLen,
                                   "%s:0,%s%s",
                                   g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                   stWifiSsid.aucWifiSsid[0],
                                   gaucAtCrLf);
    /* Modified by L00171473 for DTS2012020106679,AT WT 2012-01-17  End */

    /* WIFI keyNV */
    if (VOS_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_MULTI_WIFI_KEY, &stWifiSec,sizeof(TAF_AT_MULTI_WIFI_SEC_STRU)))
    {
        AT_WARN_LOG("AT_QryWiFiLogPara:READ NV FAIL");
        return AT_ERROR;
    }

    /* KEY1NVKEY1 */
    if (0 != VOS_StrLen((VOS_CHAR*)stWifiSec.aucWifiWepKey1[0]))
    {
        usLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                        (TAF_CHAR *)pgucAtSndCodeAddr,
                                        (TAF_CHAR *)pgucAtSndCodeAddr + usLen,
                                        "%s:1,%s%s",
                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                        stWifiSec.aucWifiWepKey1[0],
                                        gaucAtCrLf);
    }

    /* KEY2NVKEY2 */
    if (0 != VOS_StrLen((VOS_CHAR*)stWifiSec.aucWifiWepKey2[0]))
    {
        usLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                        (TAF_CHAR *)pgucAtSndCodeAddr,
                                        (TAF_CHAR *)pgucAtSndCodeAddr + usLen,
                                        "%s:2,%s%s",
                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                        stWifiSec.aucWifiWepKey2[0],
                                        gaucAtCrLf);
    }
    /* KEY3NVKEY3 */
    if (0 != VOS_StrLen((VOS_CHAR*)stWifiSec.aucWifiWepKey3[0]))
    {
        usLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                        (TAF_CHAR *)pgucAtSndCodeAddr,
                                        (TAF_CHAR *)pgucAtSndCodeAddr + usLen,
                                        "%s:3,%s%s",
                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                        stWifiSec.aucWifiWepKey3[0],
                                        gaucAtCrLf);
    }
    /* KEY4NVKEY3 */
    if (0 != VOS_StrLen((VOS_CHAR*)stWifiSec.aucWifiWepKey4[0]))
    {
        usLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                        (TAF_CHAR *)pgucAtSndCodeAddr,
                                        (TAF_CHAR *)pgucAtSndCodeAddr + usLen,
                                        "%s:4,%s%s",
                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                        stWifiSec.aucWifiWepKey4[0],
                                        gaucAtCrLf);
    }

    gstAtSendData.usBufLen = usLen;

    return AT_OK;
}
/*****************************************************************************
     : AT_QryWiFiKeyPara
   : Wifi

   : VOS_UINT8 ucIndex
   : 
     : OK
   :
   :

       :
  1.       : 20110531
           : w00166186
       : 

  2.       : 20120313
           : w00199382
       : DTS2012030804030,wifikey aucWifiWpapsk
  3.       : 2012917
           : z60575
       : MULTI_SSID
*****************************************************************************/
VOS_UINT32 AT_QryWiFiKeyPara(VOS_UINT8 ucIndex)
{
    TAF_AT_MULTI_WIFI_SEC_STRU                              stWifiSec;
    VOS_UINT8                                               ucWifiKeyNum;
    VOS_UINT16                                              usLen;
    VOS_UINT8                                               aucWpapskLen[AT_WIFI_MAX_SSID_NUM];
    VOS_UINT32                                              ulLoop;

    /* Modified by s62952 for BalongV300R002 Build 2012-02-28, begin */
    if (BSP_MODULE_UNSUPPORT == mdrv_misc_support_check(BSP_MODULE_TYPE_WIFI) )
    {
        return AT_ERROR;
    }
    /* Modified by s62952 for BalongV300R002 Build 2012-02-28, begin */

    TAF_MEM_SET_S(&stWifiSec, sizeof(stWifiSec), 0x00, sizeof(stWifiSec));

    /* WIFI keyNV */
    if (VOS_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_MULTI_WIFI_KEY, &stWifiSec,sizeof(TAF_AT_MULTI_WIFI_SEC_STRU)))
    {
        AT_WARN_LOG("AT_QryWiFiSsidPara:READ NV FAIL");
        return AT_ERROR;
    }


    ucWifiKeyNum = 0;
    TAF_MEM_SET_S(aucWpapskLen, sizeof(aucWpapskLen), 0x00, sizeof(aucWpapskLen));

    for (ulLoop = 0; ulLoop < AT_WIFI_MAX_SSID_NUM; ulLoop++)
    {

        /* KEY1NVKEY1 */
        aucWpapskLen[ulLoop] = (VOS_UINT8)VOS_StrLen((VOS_CHAR*)stWifiSec.aucWifiWpapsk[ulLoop]);

        if (0 != aucWpapskLen[ulLoop])
        {
            ucWifiKeyNum++ ;
        }
    }

    /* 0 */
    if (VOS_TRUE == g_bAtDataLocked)
    {
        ucWifiKeyNum = 0;
        TAF_MEM_SET_S(aucWpapskLen, sizeof(aucWpapskLen), 0x00, sizeof(aucWpapskLen));
    }

    usLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                   (TAF_CHAR *)pgucAtSndCodeAddr,
                                   (TAF_CHAR *)pgucAtSndCodeAddr,
                                   "%s:%d%s",
                                   g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                   ucWifiKeyNum,
                                   gaucAtCrLf);

    for (ulLoop = 0; ulLoop < AT_WIFI_MAX_SSID_NUM; ulLoop++)
    {
        if (0 != aucWpapskLen[ulLoop])
        {
            usLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                            (TAF_CHAR *)pgucAtSndCodeAddr,
                                            (TAF_CHAR *)pgucAtSndCodeAddr + usLen,
                                            "%s:%d,%s%s",
                                            g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                            ulLoop,
                                            stWifiSec.aucWifiWpapsk[ulLoop],
                                            gaucAtCrLf);
        }
    }

    gstAtSendData.usBufLen = usLen;


    return AT_OK;
}
/* Modify by z60575 for multi_ssid, 2012-9-5 end */

/*****************************************************************************
     : AT_QryWifiPaRangePara
   : WIFI
   : VOS_UINT8 ucIndex  
   : 
     : AT_OK --- 
             AT_ERROR --- 
   :
   :

       :
  1.       : 20120202
           : l00198894
       : 

*****************************************************************************/
VOS_UINT32 AT_QryWifiPaRangePara (VOS_UINT8 ucIndex)
{
    AT_WIFI_MODE_ENUM_UINT8             ucCurWifiMode;

    /* Modified by s62952 for BalongV300R002 Build 2012-02-28, begin */
    if (BSP_MODULE_UNSUPPORT == mdrv_misc_support_check(BSP_MODULE_TYPE_WIFI) )
    {
        return AT_ERROR;
    }
    /* Modified by s62952 for BalongV300R002 Build 2012-02-28, begin */


    /* WIFI */
    ucCurWifiMode   = (VOS_UINT8)WIFI_GET_PA_CUR_MODE();

    if (AT_WIFI_MODE_ONLY_PA == ucCurWifiMode)
    {
        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        "%s:%s",
                                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                        "h");
    }
    else if (AT_WIFI_MODE_ONLY_NOPA == ucCurWifiMode)
    {
        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        "%s:%s",
                                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                        "l");
    }
    else
    {
        return AT_ERROR;
    }

    return AT_OK;
}

 /*****************************************************************************
     : AT_QryProdTypePara
   : 

   : VOS_UINT8 ucIndex
   : 
     : OK
   :
   :

       :
  1.       : 20110531
           : w00166186
       : 

  2.       : 20111017
           : w00181244
       :  DRV_PRODUCT_TYPE_GET C 
*****************************************************************************/
VOS_UINT32 AT_QryProdTypePara(VOS_UINT8 ucIndex)
{
    if (TAF_SUCCESS == AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                              gastAtClientTab[ucIndex].opId,
                                              DRV_AGENT_PRODTYPE_QRY_REQ,
                                              VOS_NULL_PTR,
                                              0,
                                              I0_WUEPS_PID_DRV_AGENT))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_PRODTYPE_QRY;             /* */
        return AT_WAIT_ASYNC_RETURN;                                            /*  */
    }
    else
    {
        return AT_ERROR;
    }
}
/*****************************************************************************
     : AT_QryTmmiPara
   : mmi

   : VOS_UINT8 ucIndex
   : 
     : OK
   :
   :

       :
  1.       : 20110531
           : w00166186
       : 
  2.       : 2012220
           : l60609
       : NV
*****************************************************************************/
VOS_UINT32 AT_QryTmmiPara(VOS_UINT8 ucIndex)
{
    VOS_UINT8                           aucFacInfo[AT_FACTORY_INFO_LEN];
    VOS_UINT8                           ucMmiFlag;
    VOS_UINT32                          ulResult;

    ulResult = NV_ReadEx(MODEM_ID_0, en_NV_Item_Factory_Info,
                       aucFacInfo,
                       AT_FACTORY_INFO_LEN);

    if (NV_OK != ulResult)
    {
        return AT_ERROR;
    }

    if (VOS_OK == VOS_MemCmp(&aucFacInfo[AT_MMI_TEST_FLAG_OFFSET],
                             AT_MMI_TEST_FLAG_SUCC,
                             AT_MMI_TEST_FLAG_LEN))
    {
        ucMmiFlag = VOS_TRUE;
    }
    else
    {
        ucMmiFlag = VOS_FALSE;
    }

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                            (TAF_CHAR *)pgucAtSndCodeAddr,
                                            (TAF_CHAR *)pgucAtSndCodeAddr,
                                            "%s:%d",
                                            g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                            ucMmiFlag);

    return AT_OK;
}

/*****************************************************************************
     : AT_QryChrgInfoPara
   : 

   : VOS_UINT8 ucIndex
   : 
     : OK
   :
   :

       :
  1.       : 20110531
           : w00166186
       : 

*****************************************************************************/
VOS_UINT32 AT_QryChrgInfoPara(VOS_UINT8 ucIndex)
{

    VOS_INT32                           lChargeState;

    /* Modified by s62952 for BalongV300R002 Build 2012-02-28, begin */
    if (BSP_MODULE_UNSUPPORT == mdrv_misc_support_check(BSP_MODULE_TYPE_CHARGE) )
    {
        return AT_ERROR;
    }
    /* Modified by s62952 for BalongV300R002 Build 2012-02-28, begin */

    /*  */
    lChargeState = mdrv_misc_get_charging_status();

    /*  */
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)(pgucAtSndCodeAddr),
                                                    "%s:%d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    lChargeState);

    return AT_OK;

}
/*****************************************************************************
     : AT_QryChrgEnablePara
   : 

   : VOS_UINT8 ucIndex
   : 
     : OK
   :
   :

       :
  1.       : 20110531
           : w00166186
       : 

*****************************************************************************/
VOS_UINT32 AT_QryChrgEnablePara(VOS_UINT8 ucIndex)
{
    /*DTS2012041102190 : h00135900 start in 2011-04-11 AT*/
    VOS_INT32                             ucChargeEnable;

    /* Modified by s62952 for BalongV300R002 Build 2012-02-28, begin */
    if (BSP_MODULE_UNSUPPORT == mdrv_misc_support_check(BSP_MODULE_TYPE_CHARGE) )
    {
        return AT_ERROR;
    }
    /* Modified by s62952 for BalongV300R002 Build 2012-02-28, begin */

    /*  */

    ucChargeEnable = mdrv_misc_get_charge_state();
    /*  */
    /* TRUE/FLASE */
    if((ucChargeEnable == TRUE)||( ucChargeEnable == FALSE))
    {
        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                       (TAF_CHAR *)pgucAtSndCodeAddr,
                                                       (TAF_CHAR *)pgucAtSndCodeAddr,
                                                       "%s:%d",
                                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                       ucChargeEnable);

        return AT_OK;
    }
    else
    {
        return AT_ERROR;
    }
    /*DTS2012041102190 : h00135900 end in 2011-04-11 AT*/
}

/*****************************************************************************
     : AT_GetWcdmaBandStr
   : WCDMAband

   : VOS_UINT8                           *pucGsmBandstr,
             AT_UE_BAND_CAPA_ST                  *pstBandCapa
   : VOS_UINT32
     : usLen
   :
   :

       :
  1.       : 20110615
           : w00166186
       : 
2.        : 2012510
          : f62575
      : DTS2012051007817 SFEATUREWCDMA BAND11
3.        : 20121112
          : t00212959
      : DTS2012103101740,MMABandUINT32,AT
*****************************************************************************/
VOS_UINT32 AT_GetWcdmaBandStr(
    VOS_UINT8                          *pucGsmBandstr,
    AT_UE_BAND_CAPA_ST                 *pstBandCapa
)
{
    VOS_UINT32                          ulLen;
    ulLen = 0;

    if (1 == pstBandCapa->unWRFSptBand.BitBand.BandWCDMA_I_2100)
    {
        ulLen += (TAF_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pucGsmBandstr,
                                      (TAF_CHAR *)pucGsmBandstr + ulLen,
                                      "BC1,");
    }

    if (1 == pstBandCapa->unWRFSptBand.BitBand.BandWCDMA_II_1900)
    {
        ulLen += (TAF_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pucGsmBandstr,
                                      (TAF_CHAR *)pucGsmBandstr + ulLen,
                                      "BC2,");
    }


    if (1 == pstBandCapa->unWRFSptBand.BitBand.BandWCDMA_III_1800)
    {
        ulLen += (TAF_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pucGsmBandstr,
                                      (TAF_CHAR *)pucGsmBandstr + ulLen,
                                      "BC3,");
    }

    if (1 == pstBandCapa->unWRFSptBand.BitBand.BandWCDMA_IV_1700)
    {
        ulLen += (TAF_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pucGsmBandstr,
                                      (TAF_CHAR *)pucGsmBandstr + ulLen,
                                      "BC4,");
    }

    if (1 == pstBandCapa->unWRFSptBand.BitBand.BandWCDMA_V_850)
    {
        ulLen += (TAF_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pucGsmBandstr,
                                      (TAF_CHAR *)pucGsmBandstr + ulLen,
                                      "BC5,");
    }

    if (1 == pstBandCapa->unWRFSptBand.BitBand.BandWCDMA_VI_800)
    {
        ulLen += (TAF_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pucGsmBandstr,
                                      (TAF_CHAR *)pucGsmBandstr + ulLen,
                                      "BC6,");
    }


    if (1 == pstBandCapa->unWRFSptBand.BitBand.BandWCDMA_VII_2600)
    {
        ulLen += (TAF_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pucGsmBandstr,
                                      (TAF_CHAR *)pucGsmBandstr + ulLen,
                                      "BC7,");
    }

    if (1 == pstBandCapa->unWRFSptBand.BitBand.BandWCDMA_VIII_900)
    {
        ulLen += (TAF_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pucGsmBandstr,
                                      (TAF_CHAR *)pucGsmBandstr + ulLen,
                                      "BC8,");
    }

    if (1 == pstBandCapa->unWRFSptBand.BitBand.BandWCDMA_IX_J1700)
    {
        ulLen += (TAF_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pucGsmBandstr,
                                      (TAF_CHAR *)pucGsmBandstr + ulLen,
                                      "BC9,");
    }

    if (1 == pstBandCapa->unWRFSptBand.BitBand.BandWCDMA_XI_1500)
    {
        ulLen += (TAF_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pucGsmBandstr,
                                      (TAF_CHAR *)pucGsmBandstr + ulLen,
                                      "BC11,");
    }
    if (1 == pstBandCapa->unWRFSptBand.BitBand.BandWCDMA_XIX_850)
    {
        ulLen += (VOS_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pucGsmBandstr,
                                      (VOS_CHAR *)pucGsmBandstr + ulLen,
                                      "BC19,");
    }

    if (ulLen != 0)
    {
        pucGsmBandstr[ulLen - 1] = '\0';
    }

    return ulLen;
 }

/*****************************************************************************
     : AT_GetWcdmaDivBandStr
   : WCDMAband

   :
   : VOS_UINT8   *pucGsmBandstr WCDMAband
     : VOS_UINT32   WCDMAband
   :
   :

       :
  1.       : 20120515
           : f62575
       : DTS2012051400682UMTS
 2.        : 20121112
           : t00212959
       : DTS2012103101740,MMABandUINT32,AT
*****************************************************************************/
VOS_UINT32 AT_GetWcdmaDivBandStr(
    VOS_UINT8                          *pucGsmBandstr
)
{
    VOS_UINT32                                  ulLen;
    VOS_UINT32                                  ulBand;

    AT_WCDMA_PREF_BAND_STRU      *pstBitBand;

    /* UMTS
        V3R2en_NV_Item_W_RF_DIV_BANDV3R1en_NV_Item_ANTENNA_CONFIG */
    if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_W_RF_DIV_BAND, &ulBand, sizeof(ulBand)))
    {
        AT_WARN_LOG("AT_GetWcdmaDivBandStr: Read NVIM Smss Error");
        return 0;
    }

    ulLen = 0;
    pstBitBand = (AT_WCDMA_PREF_BAND_STRU *)&ulBand;

    /* BAND 
        Band123*/

    if (1 == pstBitBand->BandWCDMA_I_2100)
    {
        ulLen += (VOS_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pucGsmBandstr,
                                      (VOS_CHAR *)pucGsmBandstr + ulLen,
                                      "U1,");
    }

    if (1 == pstBitBand->BandWCDMA_II_1900)
    {
        ulLen += (VOS_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pucGsmBandstr,
                                      (VOS_CHAR *)pucGsmBandstr + ulLen,
                                      "U2,");
    }


    if (1 == pstBitBand->BandWCDMA_III_1800)
    {
        ulLen += (VOS_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pucGsmBandstr,
                                      (VOS_CHAR *)pucGsmBandstr + ulLen,
                                      "U3,");
    }

    if (1 == pstBitBand->BandWCDMA_IV_1700)
    {
        ulLen += (VOS_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pucGsmBandstr,
                                      (VOS_CHAR *)pucGsmBandstr + ulLen,
                                      "U4,");
    }

    if (1 == pstBitBand->BandWCDMA_V_850)
    {
        ulLen += (VOS_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pucGsmBandstr,
                                      (VOS_CHAR *)pucGsmBandstr + ulLen,
                                      "U5,");
    }

    if (1 == pstBitBand->BandWCDMA_VI_800)
    {
        ulLen += (VOS_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pucGsmBandstr,
                                      (VOS_CHAR *)pucGsmBandstr + ulLen,
                                      "U6,");
    }


    if (1 == pstBitBand->BandWCDMA_VII_2600)
    {
        ulLen += (VOS_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pucGsmBandstr,
                                      (VOS_CHAR *)pucGsmBandstr + ulLen,
                                      "U7,");
    }

    if (1 == pstBitBand->BandWCDMA_VIII_900)
    {
        ulLen += (VOS_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pucGsmBandstr,
                                      (VOS_CHAR *)pucGsmBandstr + ulLen,
                                      "U8,");
    }

    if (1 == pstBitBand->BandWCDMA_IX_J1700)
    {
        ulLen += (VOS_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pucGsmBandstr,
                                      (VOS_CHAR *)pucGsmBandstr + ulLen,
                                      "U9,");
    }

    if (1 == pstBitBand->BandWCDMA_XI_1500)
    {
        ulLen += (VOS_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pucGsmBandstr,
                                      (VOS_CHAR *)pucGsmBandstr + ulLen,
                                      "U11,");
    }

    if (1 == pstBitBand->BandWCDMA_XIX_850)
    {
        ulLen += (VOS_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pucGsmBandstr,
                                      (VOS_CHAR *)pucGsmBandstr + ulLen,
                                      "U19,");
    }

    if (ulLen != 0)
    {
        pucGsmBandstr[ulLen - 1] = '\0';
    }

    return ulLen;
 }

/*****************************************************************************
     : AT_GetGsmBandStr
   :  GSM band

   : VOS_UINT8                          *pucGsmBandstr ,
             AT_UE_BAND_CAPA_ST                 *pstBandCapa

   : 
     : usLen
   :
   :

       :
  1.       : 20110615
           : w00166186
       : 
  2.       : 20121112
           : t00212959
       : DTS2012103101740,MMABandUINT32,AT
*****************************************************************************/
VOS_UINT32 AT_GetGsmBandStr(
    VOS_UINT8                          *pucGsmBandstr ,
    AT_UE_BAND_CAPA_ST                 *pstBandCapa
)
{
    VOS_UINT32                          ulLen;

    ulLen = 0;

    if (1 == pstBandCapa->unGRFSptBand.BitBand.BandGsm450)
    {
        ulLen += (TAF_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pucGsmBandstr,
                                      (TAF_CHAR *)pucGsmBandstr + ulLen,
                                      "450,");
    }

    if (1 == pstBandCapa->unGRFSptBand.BitBand.BandGsm480)
    {
        ulLen += (TAF_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pucGsmBandstr,
                                      (TAF_CHAR *)pucGsmBandstr + ulLen,
                                      "480,");
    }


    if (1 == pstBandCapa->unGRFSptBand.BitBand.BandGsm850)
    {
        ulLen += (TAF_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pucGsmBandstr,
                                      (TAF_CHAR *)pucGsmBandstr + ulLen,
                                      "850,");
    }


    if (1 == pstBandCapa->unGRFSptBand.BitBand.BandGsmP900)
    {
        ulLen += (TAF_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pucGsmBandstr,
                                      (TAF_CHAR *)pucGsmBandstr + ulLen,
                                      "P900,");
    }
    if (1 == pstBandCapa->unGRFSptBand.BitBand.BandGsmR900)
    {
        ulLen += (TAF_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pucGsmBandstr,
                                      (TAF_CHAR *)pucGsmBandstr + ulLen,
                                      "R900,");
    }
    if (1 == pstBandCapa->unGRFSptBand.BitBand.BandGsmE900)
    {
        ulLen += (TAF_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pucGsmBandstr,
                                      (TAF_CHAR *)pucGsmBandstr + ulLen,
                                      "E900,");
    }
    if (1 == pstBandCapa->unGRFSptBand.BitBand.BandGsm1800)
    {
        ulLen += (TAF_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pucGsmBandstr,
                                      (TAF_CHAR *)pucGsmBandstr + ulLen,
                                      "1800,");
    }
    if (1 == pstBandCapa->unGRFSptBand.BitBand.BandGsm1900)
    {
        ulLen += (TAF_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pucGsmBandstr,
                                      (TAF_CHAR *)pucGsmBandstr + ulLen,
                                      "1900,");
    }
    if (1 == pstBandCapa->unGRFSptBand.BitBand.BandGsm700)
    {
        ulLen += (TAF_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pucGsmBandstr,
                                      (TAF_CHAR *)pucGsmBandstr + ulLen,
                                      "700,");
    }

    if (ulLen != 0)
    {
        pucGsmBandstr[ulLen - 1] = '\0';
    }

    return ulLen;
}
 /*****************************************************************************
     : AT_QryFeaturePara
   : 

   : VOS_UINT8 ucIndex
   : 
     : OK
   :
   :

       :
  1.       : 20110531
           : w00166186
       : 

  2.       : 20111017
           : /w00181244
       : ,APICAPI
*****************************************************************************/
VOS_UINT32 AT_QryFeaturePara(VOS_UINT8 ucIndex)
{
    if (TAF_SUCCESS == AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                             gastAtClientTab[ucIndex].opId,
                                             DRV_AGENT_SFEATURE_QRY_REQ,
                                             VOS_NULL_PTR,
                                             0,
                                             I0_WUEPS_PID_DRV_AGENT))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_SFEATURE_QRY;           /* */
        return AT_WAIT_ASYNC_RETURN;                                            /*  */
    }
    else
    {
        return AT_ERROR;
    }
}

/*****************************************************************************
     : AT_QryProdNamePara
   : 
   : VOS_UINT8 ucIndex
   : 
     : OK
   :
   :

       :
  1.       : 20110705
           : l60609
       : 
  2.       : 20110808
           : l60609
       : DTS2011080502346 NV5004830
  3.       : 2013517
           : l00167671
       : NV, NV
*****************************************************************************/
VOS_UINT32 AT_QryProdNamePara(VOS_UINT8 ucIndex)
{
    TAF_AT_PRODUCT_ID_STRU              stProductId;
    VOS_UINT32                          ulRet;

    TAF_MEM_SET_S(&stProductId, sizeof(stProductId), 0x00,sizeof(TAF_AT_PRODUCT_ID_STRU));

    /* NV50048 */
    /* NVen_NV_Item_PRODUCT_ID */
    ulRet = NV_ReadEx(MODEM_ID_0, en_NV_Item_PRODUCT_ID,
                    &stProductId,
                    sizeof(stProductId.ulNvStatus) + sizeof(stProductId.aucProductId));

    if (NV_OK != ulRet)
    {
        AT_WARN_LOG("AT_QryProdNamePara: Fail to read en_NV_Item_PRODUCT_ID");
        return AT_ERROR;
    }

    /*NV*/
    if (VOS_TRUE != stProductId.ulNvStatus)
    {
        return AT_ERROR;
    }

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%s",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    stProductId.aucProductId);

    return AT_OK;
}

/*****************************************************************************
     : AT_QryEqverPara
   : AT
   : VOS_UINT8 ucIndex
   : 
     : OK
   :
   :

       :
  1.       : 20110705
           : l60609
       : 
  2.       : 20120419
           : f62575
       : 
  3.       : 20121213
           : L00171473
       : DTS2012121802573, TQE
  4.       : 2013517
           : l00167671
       : NV, NV
*****************************************************************************/
VOS_UINT32 AT_QryEqverPara(VOS_UINT8 ucIndex)
{
    /*<version> AT0~9
    AT
    114 AT
    balong115*/
    /* Modify by f62575 for V7, 2012-04-07, Begin   */
    VOS_UINT32                          ulRet;
    TAF_AT_EQ_VER_STRU                  stEqver;

    stEqver.usEqver = 0;

    ulRet = NV_ReadEx(MODEM_ID_0, en_NV_Item_Eqver, &stEqver.usEqver, sizeof(stEqver.usEqver));
    if (NV_OK != ulRet)
    {
        return AT_ERROR;
    }
    /* Modify by f62575 for V7, 2012-04-07, End   */

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%d",
                                                     g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                     stEqver.usEqver);

    return AT_OK;
}


/* Added by l60609 for XML, 2011-08-11 Begin */
/*****************************************************************************
     : AT_QryApRptSrvUrlPara
   : XML ReportingURL
   : VOS_UINT8 ucIndex
   : 
     : OK
   :
   :

       :
  1.       : 20110811
           : l60609
       : 
  2.       : 2013517
           : l00167671
       : NV, NV
  3.       : 2014530
           : j00174725
       : TQE
*****************************************************************************/
VOS_UINT32 AT_QryApRptSrvUrlPara(VOS_UINT8 ucIndex)
{
    VOS_UINT8                           aucApRptSrvUrl[AT_AP_NVIM_XML_RPT_SRV_URL_LEN + 1];
    VOS_UINT32                          ulRet;
    TAF_AT_NVIM_AP_RPT_SRV_URL_STRU     stApRptSrvUrl;

    TAF_MEM_SET_S(aucApRptSrvUrl, sizeof(aucApRptSrvUrl), 0x00, (VOS_SIZE_T)(AT_AP_NVIM_XML_RPT_SRV_URL_LEN + 1));

    TAF_MEM_SET_S(&stApRptSrvUrl, sizeof(stApRptSrvUrl), 0x00, sizeof(stApRptSrvUrl));

    /* NV:en_NV_Item_AP_RPT_SRV_URL*/
    ulRet = NV_ReadEx(MODEM_ID_0, en_NV_Item_AP_RPT_SRV_URL,
                    &stApRptSrvUrl,
                    AT_AP_NVIM_XML_RPT_SRV_URL_LEN);

    if (NV_OK != ulRet)
    {
        AT_ERR_LOG("AT_QryApRptSrvUrlPara:Read NV fail");
        return AT_ERROR;
    }
    TAF_MEM_CPY_S(aucApRptSrvUrl, sizeof(aucApRptSrvUrl), stApRptSrvUrl.aucApRptSrvUrl, AT_AP_NVIM_XML_RPT_SRV_URL_LEN);
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:\"%s\"",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    aucApRptSrvUrl);

    return AT_OK;
}

/*****************************************************************************
     : AT_QryApXmlInfoTypePara
   : XML Reporting
   : VOS_UINT8 ucIndex
   : 
     : OK
   :
   :

       :
  1.       : 20110811
           : l60609
       : 
  2.       : 2013517
           : l00167671
       : NV, NV
  3.       : 2014530
           : j00174725
       : TQE
*****************************************************************************/
VOS_UINT32 AT_QryApXmlInfoTypePara(VOS_UINT8 ucIndex)
{
    VOS_UINT8                           aucApXmlInfoType[AT_AP_XML_RPT_INFO_TYPE_LEN + 1];
    VOS_UINT32                          ulRet;
    TAF_AT_NVIM_AP_XML_INFO_TYPE_STRU   stApXmlInfoType;

    TAF_MEM_SET_S(aucApXmlInfoType, sizeof(aucApXmlInfoType), 0x00, (VOS_SIZE_T)(AT_AP_XML_RPT_INFO_TYPE_LEN + 1));

    TAF_MEM_SET_S(&stApXmlInfoType, sizeof(stApXmlInfoType), 0x00, sizeof(stApXmlInfoType));

    /* NV:en_NV_Item_AP_XML_INFO_TYPE*/
    ulRet = NV_ReadEx(MODEM_ID_0, en_NV_Item_AP_XML_INFO_TYPE,
                    &stApXmlInfoType,
                    AT_AP_NVIM_XML_RPT_INFO_TYPE_LEN);

    if (NV_OK != ulRet)
    {
        AT_ERR_LOG("AT_QryApXmlInfoTypePara:Read NV fail");
        return AT_ERROR;
    }

    TAF_MEM_CPY_S(aucApXmlInfoType, sizeof(aucApXmlInfoType), stApXmlInfoType.aucApXmlInfoType, AT_AP_NVIM_XML_RPT_INFO_TYPE_LEN);

    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%s",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    aucApXmlInfoType);

    return AT_OK;
}

/*****************************************************************************
     : AT_QryApXmlRptFlagPara
   : XML Reporting
   : VOS_UINT8 ucIndex
   : 
     : OK
   :
   :

       :
  1.       : 20110811
           : l60609
       : 
  2.       : 20121213
           : L00171473
       : DTS2012121802573, TQE
  3.       : 2013517
           : l00167671
       : NV, NV
*****************************************************************************/
VOS_UINT32 AT_QryApXmlRptFlagPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRet;
    TAF_AT_NVIM_AP_XML_RPT_FLG_STRU     stApXmlRptFlg;
    VOS_UINT32                          ulLength;

    ulLength                   = 0;

    (VOS_VOID)NV_GetLength(en_NV_Item_AP_XML_RPT_FLAG, &ulLength);

    stApXmlRptFlg.ucApXmlRptFlg = VOS_FALSE;

    /* NV:en_NV_Item_AP_XML_RPT_FLAG*/
    ulRet = NV_ReadEx(MODEM_ID_0, en_NV_Item_AP_XML_RPT_FLAG,
                        &stApXmlRptFlg,
                        ulLength);

    if (NV_OK != ulRet)
    {
        AT_ERR_LOG("AT_QryApXmlRptFlagPara:Read NV fail");
        return AT_ERROR;
    }

    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    stApXmlRptFlg.ucApXmlRptFlg);

    return AT_OK;
}

/* Added by l60609 for XML, 2011-08-11 End */

/* Added by h44270 for V7R1 phase III, 2011-10-18, begin */
/*****************************************************************************
     : At_QryFastDormPara
   : FAST DORMANCY
   : ucIndex - 
   : 
     :
   :
   :

       :
  1.       : 20101019
           : h44270
       : 
*****************************************************************************/
VOS_UINT32 AT_QryFastDormPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRslt;

    /* MN_FillAndSndAppReqMsg()RABM */
    ulRslt = AT_SndQryFastDorm(gastAtClientTab[ucIndex].usClientId,gastAtClientTab[ucIndex].opId);
    if (AT_SUCCESS == ulRslt)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_FASTDORM_READ;
        return AT_WAIT_ASYNC_RETURN;
    }

    return AT_ERROR;
}
/* Added by h44270 for V7R1 phase III, 2011-10-18, end */

/*****************************************************************************
     : AT_QryAcpuMemInfoPara
   : ACPU
   : ucIndex - 
   : 
     :
   :
   :

       :
  1.       : 20120201
           : S62952
       : 
*****************************************************************************/
VOS_UINT32 AT_QryAcpuMemInfoPara(TAF_UINT8 ucIndex)
{
    (VOS_VOID)vos_printf("AT_QryAcpuMemInfoPara:at cmd\r\n");

    /**/
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_DEVICE_OTHER_ERROR;
    }

    /* Deleted by wx270776 for OM, 2015-7-9, begin */

    /* Deleted by wx270776 for OM, 2015-7-9, end */

    return AT_OK;

}


/*****************************************************************************
     : AT_QryCcpuMemInfoPara
   : CCPU
   : ucIndex - 
   : 
     :
   :
   :

       :
  1.       : 20120201
           : S62952
       : 

  2.       : 20121222
           : l60609
       : DSDA Phase II
*****************************************************************************/
VOS_UINT32 AT_QryCcpuMemInfoPara(TAF_UINT8 ucIndex)
{
    /* Modified by l60609 for DSDA Phase II, 2012-12-22, Begin */
    VOS_UINT32                          ulRet;

    (VOS_VOID)vos_printf("AT_QryCcpuMemInfoPara:at cmd\r\n");

    /**/
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_DEVICE_OTHER_ERROR;
    }

    /* CCCPU */
    ulRet = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   DRV_AGENT_QRY_CCPU_MEM_INFO_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_WUEPS_PID_DRV_AGENT);

    if (TAF_SUCCESS == ulRet)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CCPUMEMINFO_QRY;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        AT_WARN_LOG("AT_QryCcpuMemInfoPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* Modified by l60609 for DSDA Phase II, 2012-12-22, End */
}

/*****************************************************************************
     : AT_QryCipherPara
   : PS
             <CR><LF>^CIPHERQRY:<CIPHER><CR><LF>
             <CR><LF>OK<CR><LF>
             CIPHER:
   : VOS_UINT8 ucIndex
   : 
     : AT_ERRORAT_OK
   :
   :

       :
  1.       : 20120202
           : l00198894
       : 

*****************************************************************************/
VOS_UINT32 AT_QryCipherPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulResult;

    /* MMACipher */
    ulResult = TAF_MMA_QryCipherReq(WUEPS_PID_AT,
                                    gastAtClientTab[ucIndex].usClientId,
                                    0);

    /*  */
    if (VOS_TRUE == ulResult)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CIPERQRY_READ;

        /*  */
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}

/*****************************************************************************
     : AT_QryLocinfoPara
   : UE
             <CR><LF>^LOCINFO:<PLMN>,<LAC>,<RAC>,<CI><CR><LF>
             <CR><LF>OK<CR><LF>
             CIPHER:
   : VOS_UINT8 ucIndex
   : 
     : AT_ERRORAT_OK
   :
   :

       :
  1.       : 2011826
           : q00180979
       : 

*****************************************************************************/
VOS_UINT32 AT_QryLocinfoPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulResult;

    /* MMAUE */
    ulResult = TAF_MMA_QryLocInfoReq(WUEPS_PID_AT,
                                     gastAtClientTab[ucIndex].usClientId,
                                     0);

    /*  */
    if (VOS_TRUE == ulResult)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_LOCINFO_READ;

        /*  */
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }

}

/* Added by l60609 for B070 Project, 2012/03/09, begin */
/*****************************************************************************
     : AT_QryNvResumePara
   : AT^QRYNVRESUME?
             <CR><LF>^QRYNVRESUME:<status>
             <CR><LF>OK<CR><LF>
             MS
             <CR><LF>ERROR<CR><LF>
   : VOS_UINT8 ucIndex
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 201239
           : l60609
       : 
  2.       : 2012810
           : L00171473
       : DTS2012082204471, TQE
*****************************************************************************/
VOS_UINT32 AT_QryNvResumePara(VOS_UINT8 ucIndex)
{
    VOS_UINT16                          usNvResumeFlag;


    usNvResumeFlag = AT_NV_RESUME_SUCC;


    /* en_NV_Resume_Flag */
    if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Resume_Flag, &usNvResumeFlag, sizeof(VOS_UINT16)))
    {
        AT_WARN_LOG("AT_QryNvResumePara:READ NV FAIL");
        return AT_ERROR;
    }

    /* 01 */
    if ((AT_NV_RESUME_SUCC != usNvResumeFlag)
     && (AT_NV_RESUME_FAIL != usNvResumeFlag))
    {
        AT_WARN_LOG("AT_QryNvResumePara:PARA IS INVALID");
        return AT_ERROR;
    }

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%d",
                                                     g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                     usNvResumeFlag);
    return AT_OK;
}
/* Added by l60609 for B070 Project, 2012/03/09, end */

/*****************************************************************************
     : AT_QryNvBackupStatusPara
   : (AT^NVBACKUPSTAT)NV
   : ucIndex - 
   : 
     :
   :
   :

       :
  1.       : 20120218
           : l00198894
       : 
*****************************************************************************/
VOS_UINT32 AT_QryNvBackupStatusPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRet;

    /* CNV */
    ulRet = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   DRV_AGENT_NVBACKUPSTAT_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_WUEPS_PID_DRV_AGENT);
    if (TAF_SUCCESS != ulRet)
    {
        AT_WARN_LOG("AT_QryNvBackupStatusPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* AT */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_NVBACKUPSTAT_READ;

    return AT_WAIT_ASYNC_RETURN;
}

/*****************************************************************************
     : AT_QryNandBadBlockPara
   : (AT^NANDBBC)NAND FLASH
   : ucIndex - 
   : 
     :
   :
   :

       :
  1.       : 20120218
           : l00198894
       : 
*****************************************************************************/
VOS_UINT32 AT_QryNandBadBlockPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRet;

    /* CNAND FLASH */
    ulRet = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   DRV_AGENT_NANDBBC_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_WUEPS_PID_DRV_AGENT);
    if (TAF_SUCCESS != ulRet)
    {
        AT_WARN_LOG("AT_QryNandBadBlockPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* AT */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_NANDBBC_READ;

    return AT_WAIT_ASYNC_RETURN;
}

/*****************************************************************************
     : AT_QryNandDevInfoPara
   : (AT^NANDVER)NAND FLASHIDID
   : ucIndex - 
   : 
     :
   :
   :

       :
  1.       : 20120218
           : l00198894
       : 
*****************************************************************************/
VOS_UINT32 AT_QryNandDevInfoPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRet;

    /* CNAND FLASH */
    ulRet = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   DRV_AGENT_NANDVER_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_WUEPS_PID_DRV_AGENT);
    if (TAF_SUCCESS != ulRet)
    {
        AT_WARN_LOG("AT_QryNandDevInfoPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* AT */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_NANDVER_READ;

    return AT_WAIT_ASYNC_RETURN;
}

/*****************************************************************************
     : AT_QryChipTempPara
   : (AT^CHIPTEMP)PASIM
   : ucIndex - 
   : 
     :
   :
   :

       :
  1.       : 20120218
           : l00198894
       : 
*****************************************************************************/
VOS_UINT32 AT_QryChipTempPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRet;

    /* CPASIM */
    ulRet = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   DRV_AGENT_CHIPTEMP_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_WUEPS_PID_DRV_AGENT);
    if (TAF_SUCCESS != ulRet)
    {
        AT_WARN_LOG("AT_QryChipTempPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* AT */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CHIPTEMP_READ;

    return AT_WAIT_ASYNC_RETURN;
}

/*****************************************************************************
     : AT_QryApRptPortSelectPara
   : (AT^APRPTPORTSEL)HSIC AT
   : ucIndex - 
   : 
     :
   :
   :

       :
  1.       : 20120218
           : l00198894
       : 
  2.       : 2012813
           : l60609
       : MUX:MUX
  3.       : 20140426
           : f00179208
       : DTS2014042304605
  4.       : 20170220
           : lwx331495
       : VCOM capacity

*****************************************************************************/
VOS_UINT32 AT_QryApRptPortSelectPara(VOS_UINT8 ucIndex)
{
    AT_PORT_RPT_CFG_STRU                stRptCfg;
    AT_CLIENT_CONFIGURATION_STRU       *pstClientCfg;
    AT_CLIENT_CFG_MAP_TAB_STRU         *pstCfgMapTbl;
    VOS_UINT8                           i;

    TAF_MEM_SET_S(&stRptCfg, sizeof(stRptCfg), 0x00, sizeof(stRptCfg));

    /*  */
    /* Modified by L60609 for MUX2012-08-13,  Begin */
    if (VOS_FALSE == AT_IsApPort(ucIndex))
    /* Modified by L60609 for MUX2012-08-13,  End */
    {
        return AT_ERROR;
    }

    for (i = 0; i < AT_GET_CLIENT_CFG_TAB_LEN(); i++)
    {
        pstCfgMapTbl = AT_GetClientCfgMapTbl(i);
        pstClientCfg = AT_GetClientConfig(pstCfgMapTbl->enClientId);

        if (VOS_TRUE == pstClientCfg->ucReportFlg)
        {
            stRptCfg.aulRptCfgBit32[0] |= pstCfgMapTbl->ulRptCfgBit32[0];
            stRptCfg.aulRptCfgBit32[1] |= pstCfgMapTbl->ulRptCfgBit32[1];
            stRptCfg.aulRptCfgBit32[2] |= pstCfgMapTbl->ulRptCfgBit32[2];
        }
    }

    /*  */
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    "%s: %08X, %08X, %08X",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    stRptCfg.aulRptCfgBit32[0],
                                                    stRptCfg.aulRptCfgBit32[1],
                                                    stRptCfg.aulRptCfgBit32[2]);


    return AT_OK;
}

/*****************************************************************************
     : At_QryUsbSwitchPara
   : +USBSWITCH
   : VOS_UINT8 ucIndex
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 2012-02-23
           : H59254
       : AP-MODEM IPC
  2.       : 2012813
           : l60609
       : MUX:MUX
  3.       : 20121213
           : L00171473
       : DTS2012121802573, TQE
*****************************************************************************/
VOS_UINT32 At_QryUsbSwitchPara (VOS_UINT8 ucIndex)
{
    VOS_UINT8                           ucUsbStatus;
    VOS_UINT32                          ulResult;


    ucUsbStatus = USB_SWITCH_OFF;

    /*  */
    /* Modified by L60609 for MUX2012-08-13,  Begin */
    if (VOS_FALSE == AT_IsApPort(ucIndex))
    /* Modified by L60609 for MUX2012-08-13,  End */
    {
        return AT_ERROR;
    }

    if (VOS_OK != DRV_USB_PHY_SWITCH_GET(&ucUsbStatus))
    {
        return AT_ERROR;
    }

    ulResult = (ucUsbStatus == USB_SWITCH_ON)?AT_USB_SWITCH_SET_VBUS_VALID:\
                                              AT_USB_SWITCH_SET_VBUS_INVALID;

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                            (TAF_CHAR *)pgucAtSndCodeAddr,
                                            (TAF_CHAR *)pgucAtSndCodeAddr,
                                            "+USBSWITCH: %X", ulResult);

    return AT_OK;
}

/*****************************************************************************
     : AT_QryAntState
   : 
   : ucIndex - 
   : 
     :
   :
   :

       :
  1.       : 20120220
           : w00184875
       : 
  2.       : 20121213
           : L00171473
       : DTS2012121802573, TQE
  3.       : 2013530
           : z60575
      : DTS2013060307614, DSDA_SAR
  4.       : 201382
           : z60575
      : DTS2013073103769, C
*****************************************************************************/
VOS_UINT32 AT_QryAntState(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRet;
    VOS_UINT16                          usAntState;

    /*  */
    if(AT_CMD_OPT_SET_CMD_NO_PARA != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }


    usAntState = 0;

    ulRet = TAF_AGENT_GetAntState(ucIndex, &usAntState);
    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_QryAntState: TAF_AGENT_GetAntState fail");

        return AT_ERROR;
    }

    /* 01 */
    if (0 == (usAntState & AT_CMD_MAX_ANT_BIT_MASK))
    {
        AT_NORM_LOG("AT_QryAntState: usAntState Set to 0");
        usAntState = 0;
    }
    else
    {
        AT_NORM_LOG("AT_QryAntState: usAntState Set to 1");
        usAntState = 1;
    }

    /* AT */
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    usAntState);
    return AT_OK;
}

/*****************************************************************************
     : AT_QrySARReduction
   : 
   : ucIndex - 
   : 
     :
   :
   :

       :
  1.       : 20120220
           : w00184875
       : 
  2.       : 20121213
           : L00171473
       : DTS2012121802573, TQE
  3.       : 2013530
           : z60575
       : DTS2013060307614DSDA_SAR
  4.       : 201382
           : z60575
       : DTS2013073103769C
  5.       : 20161121
           : l00198894
       : DTS2016111703335Chicago SAR
*****************************************************************************/
VOS_UINT32 AT_QrySARReduction(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRet;
    VOS_UINT16                          usUETestMode;
    AT_MODEM_MT_INFO_CTX_STRU          *pstMtInfoCtx = VOS_NULL_PTR;
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT16                          usAntState;

    usUETestMode = VOS_FALSE;

    /* NV */
    ulRet = NV_ReadEx(MODEM_ID_0,
                      en_NV_Item_RF_SAR_BACKOFF_TESTMODE,
                      &usUETestMode,
                      sizeof(usUETestMode));

    if (NV_OK != ulRet)
    {
        AT_ERR_LOG("AT_QrySARReduction:Read NV fail");
        return AT_ERROR;
    }


    enModemId  = MODEM_ID_0;

    ulRet   = AT_GetModemIdFromClient(ucIndex, &enModemId);

    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_QrySARReduction:Get modem id fail");
        return AT_ERROR;
    }

    pstMtInfoCtx = AT_GetModemMtInfoCtxAddrFromModemId(enModemId);

    usAntState   = 0;
    ulRet        = TAF_AGENT_GetAntState(ucIndex, &usAntState);
    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_QrySARReduction:Get modem id fail");
        return AT_ERROR;
    }

    if ((AT_ANT_CONDUCTION_MODE == usAntState) && (VOS_TRUE != usUETestMode))
    {
        AT_ERR_LOG("AT_QrySARReduction: ant state wrong");
        return AT_ERROR;
    }

    /* AT */
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%u",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    pstMtInfoCtx->ulSarReduction);

    return AT_OK;
}

/* Add by c00172979 for V7, 2012-04-07, Begin   */
/*****************************************************************************
     : AT_QryRsrpCfgPara
   : rsrp
   : VOS_UINT8 ucIndex
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 2012423
           : w00199382
       : V7R1 Bugfix

*****************************************************************************/
VOS_UINT32  AT_QryRsrpCfgPara ( VOS_UINT8 ucIndex )
{
    NVIM_RSRP_CFG_STRU stRsrpCfg;
    VOS_UINT32 i =0;

    TAF_MEM_SET_S(&stRsrpCfg, sizeof(stRsrpCfg), 0x00, sizeof(stRsrpCfg));

    if (g_enATE5RightFlag == AT_E5_RIGHT_FLAG_YES)
    {
        if (NV_OK != NVM_Read(EN_NV_ID_RSRP_CFG, &stRsrpCfg,sizeof(stRsrpCfg)))
        {
            (VOS_VOID)vos_printf("read RSRP_CFG NV fail!\n");
            return AT_ERROR;
        }

        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (TAF_CHAR *)pgucAtSndCodeAddr,
                                                        (TAF_CHAR *)pgucAtSndCodeAddr,
                                                        "%s:",
                                                         g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

        for (i = 0 ;i < 3; i++)
        {
            gstAtSendData.usBufLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (TAF_CHAR *)pgucAtSndCodeAddr,
                                                        (TAF_CHAR *)pgucAtSndCodeAddr + gstAtSendData.usBufLen,
                                                        "(%d)%d,",
                                                         i+1,
                                                         stRsrpCfg.ssValue[i]);
        }

        gstAtSendData.usBufLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr + gstAtSendData.usBufLen,
                                                    "(4)%d",
                                                     stRsrpCfg.ssValue[3]);
    }
    else
    {
        return AT_ERROR;
    }


    return AT_OK;
}
/*****************************************************************************
     : AT_QryRscpCfgPara
   : rscp
   : VOS_UINT8 ucIndex
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 2012423
           : w00199382
       : V7R1 Bugfix

*****************************************************************************/
VOS_UINT32  AT_QryRscpCfgPara ( VOS_UINT8 ucIndex )
{
    NVIM_RSCP_CFG_STRU stRscpCfg;
    VOS_UINT32 i =0;

    TAF_MEM_SET_S(&stRscpCfg, sizeof(stRscpCfg), 0x00, sizeof(stRscpCfg));

    if (g_enATE5RightFlag == AT_E5_RIGHT_FLAG_YES)
    {
        if (NV_OK != NVM_Read(EN_NV_ID_RSCP_CFG, &stRscpCfg,
                          sizeof(stRscpCfg)))
        {
            return AT_ERROR;
        }


        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                                (TAF_CHAR *)pgucAtSndCodeAddr,
                                                                (TAF_CHAR *)pgucAtSndCodeAddr,
                                                                "%s:",
                                                                 g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
        for (i = 0; i < 3; i++)
        {
            gstAtSendData.usBufLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (TAF_CHAR *)pgucAtSndCodeAddr,
                                                        (TAF_CHAR *)pgucAtSndCodeAddr+ gstAtSendData.usBufLen,
                                                        "(%d)%d,",
                                                         i+1,
                                                         stRscpCfg.ssValue[i]);
        }

        gstAtSendData.usBufLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr+ gstAtSendData.usBufLen,
                                                    "(4)%d",
                                                     stRscpCfg.ssValue[3]);
    }
    else
    {
        return AT_ERROR;
    }


    return AT_OK;
}
/*****************************************************************************
     : AT_QryEcioCfgPara
   : ecio
   : VOS_UINT8 ucIndex
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 2012423
           : w00199382
       : V7R1 Bugfix

*****************************************************************************/
VOS_UINT32  AT_QryEcioCfgPara ( VOS_UINT8 ucIndex )
{
    NVIM_ECIO_CFG_STRU stEcioCfg;
    VOS_UINT32 i =0;

    TAF_MEM_SET_S(&stEcioCfg, sizeof(stEcioCfg), 0x00, sizeof(stEcioCfg));

    if (g_enATE5RightFlag == AT_E5_RIGHT_FLAG_YES)
    {
        if (NV_OK != NVM_Read(EN_NV_ID_ECIO_CFG, &stEcioCfg,
                          sizeof(stEcioCfg)))
        {
            (VOS_VOID)vos_printf("read ECIO_CFG NV fail!\n");
            return AT_ERROR;
        }

        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                                  (TAF_CHAR *)pgucAtSndCodeAddr,
                                                                  (TAF_CHAR *)pgucAtSndCodeAddr,
                                                                  "%s:",
                                                                   g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
        for (i = 0 ;i < 3; i++)
        {
            gstAtSendData.usBufLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (TAF_CHAR *)pgucAtSndCodeAddr,
                                                        (TAF_CHAR *)pgucAtSndCodeAddr+ gstAtSendData.usBufLen,
                                                        "(%d)%d,",
                                                         i+1,
                                                         stEcioCfg.ssValue[i]);
        }

        gstAtSendData.usBufLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr+ gstAtSendData.usBufLen,
                                                    "(4)%d",
                                                     stEcioCfg.ssValue[3]);
    }
    else
    {
        return AT_ERROR; /* ERROR */
    }

    return AT_OK;
}

/* AT_QryCellRoamPara */

/*****************************************************************************
     : AT_QryPdprofmodPara
   : pdprofmod
   : VOS_UINT8 ucIndex
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 2012423
           : w00199382
       : V7R1 Bugfix

*****************************************************************************/
VOS_UINT32 AT_QryPdprofmodPara(VOS_UINT8 ucIndex)
{
    return AT_OK;
}
/*****************************************************************************
     : At_QrySfm
   : sfm
   : VOS_UINT8 ucIndex
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 2012423
           : w00199382
       : V7R1 Bugfix
  2.       : 20121213
           : L00171473
       : DTS2012121802573, TQE
*****************************************************************************/
VOS_UINT32 At_QrySfm(VOS_UINT8 ucIndex)
{
    VOS_UINT32  ulCustomVersion;


    ulCustomVersion = 0;

    if ( VOS_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_SW_VERSION_FLAG, &ulCustomVersion, sizeof(ulCustomVersion)) )
    {
        return AT_ERROR;
    }
    else
    {

        /* ATNV */
        if (0 == ulCustomVersion)
        {

            /* 1  */
            ulCustomVersion = 1;

        }
        else
        {

            /* 0  */
            ulCustomVersion = 0;
        }

        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,
            (TAF_CHAR *)pgucAtSndCodeAddr,"^SFM: %d", ulCustomVersion);

        return AT_OK;
    }
}

/* Modify by c00172979 for V7, 2012-04-07, End   */

/*****************************************************************************
     : AT_QryPhoneSimlockInfoPara
   : ^PHONESIMLOCKINFO
   : VOS_UINT8 ucIndex
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 20120409
           : l00198894
       : AP-Modem
  2.       : 2012813
           : l60609
       : MUX:MUX
*****************************************************************************/
VOS_UINT32 AT_QryPhoneSimlockInfoPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulResult;

    /*  */
    /* Modified by L60609 for MUX2012-08-13,  Begin */
    if (VOS_FALSE == AT_IsApPort(ucIndex))
    /* Modified by L60609 for MUX2012-08-13,  End */
    {
        return AT_ERROR;
    }

    printk(KERN_ERR "\n AT_QryPhoneSimlockInfoPara enter \n");

    /* C,  */
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                      gastAtClientTab[ucIndex].opId,
                                      DRV_AGENT_PHONESIMLOCKINFO_QRY_REQ,
                                      VOS_NULL_PTR,
                                      0,
                                      I0_WUEPS_PID_DRV_AGENT);

    if (TAF_SUCCESS != ulResult)
    {
        AT_WARN_LOG("AT_QryPhoneSimlockInfoPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* AT */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_PHONESIMLOCKINFO_READ;
    return AT_WAIT_ASYNC_RETURN;
}

/*****************************************************************************
     : AT_QrySimlockDataReadPara
   : ^SIMLOCKDATAREAD
   : VOS_UINT8 ucIndex
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 20120409
           : l00198894
       : AP-Modem
  2.       : 2012813
           : l60609
       : MUX:MUX
*****************************************************************************/
VOS_UINT32 AT_QrySimlockDataReadPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulResult;

    /*  */
    /* Modified by L60609 for MUX2012-08-13,  Begin */
    if (VOS_FALSE == AT_IsApPort(ucIndex))
    /* Modified by L60609 for MUX2012-08-13,  End */
    {
        return AT_ERROR;
    }

    printk(KERN_ERR "\n AT_QrySimlockDataReadPara enter \n");

    /* C,  */
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                      gastAtClientTab[ucIndex].opId,
                                      DRV_AGENT_SIMLOCKDATAREAD_QRY_REQ,
                                      VOS_NULL_PTR,
                                      0,
                                      I0_WUEPS_PID_DRV_AGENT);

    if (TAF_SUCCESS != ulResult)
    {
        AT_WARN_LOG("AT_QrySimlockDataReadPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* AT */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_SIMLOCKDATAREAD_READ;
    return AT_WAIT_ASYNC_RETURN;
}

/*****************************************************************************
     : AT_QryPhonePhynumPara
   : ^PHONEPHYNUM
   : VOS_UINT8 ucIndex
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 20120409
           : l00198894
       : AP-Modem
  2.       : 2012813
           : l60609
       : MUX:MUX
*****************************************************************************/
VOS_UINT32 AT_QryPhonePhynumPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulResult;

    /*  */
    /* Modified by L60609 for MUX2012-08-13,  Begin */
    if (VOS_FALSE == AT_IsApPort(ucIndex))
    /* Modified by L60609 for MUX2012-08-13,  End */
    {
        return AT_ERROR;
    }

    /* C,  */
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                      gastAtClientTab[ucIndex].opId,
                                      DRV_AGENT_PHONEPHYNUM_QRY_REQ,
                                      VOS_NULL_PTR,
                                      0,
                                      I0_WUEPS_PID_DRV_AGENT);

    if (TAF_SUCCESS != ulResult)
    {
        AT_WARN_LOG("AT_QryPhonePhynumPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* AT */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_PHONEPHYNUM_READ;
    return AT_WAIT_ASYNC_RETURN;
}


/*****************************************************************************
     : AT_QryPortCtrlTmpPara
   : ^PORTCTRLTMP
   : VOS_UINT8 ucIndex
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 20120410
           : y00213812
       : AP-Modem
  2.       : 2012813
           : l60609
       : MUX:MUX
*****************************************************************************/
VOS_UINT32 AT_QryPortCtrlTmpPara(VOS_UINT8 ucIndex)
{
    OM_HSIC_PORT_STATUS_ENUM_UINT32     enOmHsicPortStatus;

    /*  */
    /* Modified by L60609 for MUX2012-08-13,  Begin */
    if (VOS_FALSE == AT_IsApPort(ucIndex))
    /* Modified by L60609 for MUX2012-08-13,  End */
    {
        return AT_ERROR;
    }

    /* AOMOM_GetHsicPortStatus()AP */
    enOmHsicPortStatus = PPM_GetHsicPortStatus();

    if ( (OM_HSIC_PORT_STATUS_ON != enOmHsicPortStatus)
       && (OM_HSIC_PORT_STATUS_OFF != enOmHsicPortStatus) )
    {
        return AT_ERROR;
    }


    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s: %d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    enOmHsicPortStatus);

    return AT_OK;
}

/*****************************************************************************
     : AT_QryPortAttribSetPara
   : ^PORTATTRIBSET
   : VOS_UINT8 ucIndex
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 20120410
           : y00213812
       : AP-Modem
  2.       : 2012813
           : l60609
       : MUX;MUX
*****************************************************************************/
VOS_UINT32 AT_QryPortAttribSetPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulResult;

    /*  */
    /* Modified by L60609 for MUX2012-08-13,  Begin */
    if (VOS_FALSE == AT_IsApPort(ucIndex))
    /* Modified by L60609 for MUX2012-08-13,  End */
    {
        return AT_ERROR;
    }

    /* C */
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                      gastAtClientTab[ucIndex].opId,
                                      DRV_AGENT_PORTATTRIBSET_QRY_REQ,
                                      VOS_NULL_PTR,
                                      0,
                                      I0_WUEPS_PID_DRV_AGENT);

    if (TAF_SUCCESS != ulResult)
    {
        AT_WARN_LOG("AT_QryPortAttribSetPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* AT */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_PORTATTRIBSET_READ;
    return AT_WAIT_ASYNC_RETURN;
}



/*****************************************************************************
     : AT_QryCposrPara
   : +CPOSR
   : VOS_UINT8 ucIndex
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 20120627
           : y00213812
       : V7R1C50 A-GPS
  2.       : 2012813
           : l60609
       : MUX:MUX
  3.       : 2013220
           : l60609
       : DSDA PHASE III
*****************************************************************************/
VOS_UINT32 AT_QryCposrPara(VOS_UINT8 ucIndex)
{
    /* Modified by l60609 for DSDA Phase III, 2013-2-20, Begin */
    AT_MODEM_AGPS_CTX_STRU             *pstAgpsCtx = VOS_NULL_PTR;

    pstAgpsCtx = AT_GetModemAgpsCtxAddrFromClientId(ucIndex);

    /* +CPOSR */
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR*)pgucAtSndCodeAddr,
                                                    (VOS_CHAR*)pgucAtSndCodeAddr,
                                                    "%s: %d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    pstAgpsCtx->enCposrReport);
    /* Modified by l60609 for DSDA Phase III, 2013-2-20, End */

    return AT_OK;
}

/*****************************************************************************
     : AT_QryXcposrPara
   : ^XCPOSR
   : VOS_UINT8 ucIndex
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 20120627
           : y00213812
       : V7R1C50 A-GPS
  2.       : 2012813
           : l60609
       : MUX:MUX
  3.       : 2013220
           : l60609
       : DSDA PHASE III
  4.       : 20160308
           : h00360002
       : C
*****************************************************************************/
VOS_UINT32 AT_QryXcposrPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                              ulResult;

    /*  */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    /* MTA+xcposr */
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                      0,
                                      ID_AT_MTA_XCPOSR_QRY_REQ,
                                      VOS_NULL_PTR,
                                      0,
                                      I0_UEPS_PID_MTA);

    if (TAF_SUCCESS != ulResult)
    {
        AT_WARN_LOG("AT_QryXcposrPara: send Msg fail.");
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_XCPOSR_QRY;

    return AT_WAIT_ASYNC_RETURN;
}

/*****************************************************************************
     : AT_QryXcposrRptPara
   : ^XCPOSRRPT
   : VOS_UINT8 ucIndex
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 20160309
           : h00360002
       : 
*****************************************************************************/
VOS_UINT32 AT_QryXcposrRptPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                              ulResult;

    /*  */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    /* MTA */
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                      0,
                                      ID_AT_MTA_XCPOSRRPT_QRY_REQ,
                                      VOS_NULL_PTR,
                                      0,
                                      I0_UEPS_PID_MTA);

    if (TAF_SUCCESS != ulResult)
    {
        AT_WARN_LOG("AT_QryXcposrRptPara: send Msg fail.");
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_XCPOSRRPT_QRY;

    return AT_WAIT_ASYNC_RETURN;

}

/*****************************************************************************
     : AT_QryCPsErrPara
   : ^CPSERR: <cause> PS
   : ucIndex --- 
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 2012822
           : A00165503
       : 
  2.       : 2013220
           : l60609
       : DSDA PHASE III
*****************************************************************************/
VOS_UINT32 AT_QryCPsErrPara(VOS_UINT8 ucIndex)
{
    VOS_UINT16                          usLength;

    /* Modified by l60609 for DSDA Phase III, 2013-2-20, Begin */
    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      "%s: %d",
                                      g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                      AT_PS_GetPsCallErrCause(ucIndex));
    /* Modified by l60609 for DSDA Phase III, 2013-2-20, End */

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}

/*****************************************************************************
     : AT_QryCmutPara
   : +CMUT? 
   : ucIndex --- 
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 2012912
           : A00165503
       : 

*****************************************************************************/
VOS_UINT32 AT_QryCmutPara(VOS_UINT8 ucIndex)
{
    if (VOS_OK != APP_VC_GetMuteStatus(gastAtClientTab[ucIndex].usClientId, 0))
    {
        return AT_ERROR;
    }

    /*  */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CMUT_READ;

    /*  */
    return AT_WAIT_ASYNC_RETURN;
}

/*****************************************************************************
     : AT_QryCCsErrPara
   : ^CCSERR
   : VOS_UINT8 ucIndex
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 20120918
           : y00213812
       : STK&DCM 

  2.       : 201335
           : l60609
       : DSDA PHASE III
*****************************************************************************/
VOS_UINT32 AT_QryCCsErrPara(VOS_UINT8 ucIndex)
{
    VOS_UINT16                          usLength;

    /* Modified by l60609 for DSDA Phase III, 2013-3-5, Begin */
    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      "%s: %d",
                                      g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                      AT_GetCsCallErrCause(ucIndex));
    /* Modified by l60609 for DSDA Phase III, 2013-3-5, End */

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}


/*****************************************************************************
     : At_QryCerssiPara
   : ^cerssi
   : ucIndex - 
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 20121121
           : z00161729
       : 
  2.       : 201319
           : t00212959
       : DTS2013010809978,
  3.       : 201324
           : t00212959
       : DTS2013020600770:at^cerssi?
  4.       : 2013222
           : l60609
       : DSDA PHASE III
  5.       : 201307222
           : j00177245
       : warning
  6.       : 20141128
           : w00281933
       : Phase I
  7.       : 2015324
           : g00261581
       : Cerssi
*****************************************************************************/
VOS_UINT32 At_QryCerssiPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulResult;

    ulResult = TAF_MMA_QryCerssiReq(WUEPS_PID_AT, gastAtClientTab[ucIndex].usClientId, gastAtClientTab[ucIndex].opId);

    /*  */
    if (VOS_TRUE == ulResult)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CERSSI_READ;

        /*  */
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}


/*****************************************************************************
     : At_QryCecellidPara
   : ^cecellid,4g
   : ucIndex - 
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 20121121
           : z00161729
       : 

*****************************************************************************/
VOS_UINT32 At_QryCecellidPara(VOS_UINT8 ucIndex)
{
    /* L  */
    return At_QryCellIdPara(ucIndex);
}


/*****************************************************************************
     : At_QryCbgPara
   : ^cbg,
   : ucIndex - 
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 20121228
           : /00214637
       : AT^CBG=? 
*****************************************************************************/
VOS_UINT32 AT_QryCbgPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulResult;

    /* AT VC  */
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                      gastAtClientTab[ucIndex].opId,
                                      APP_VC_MSG_FOREGROUND_QRY,
                                      VOS_NULL_PTR,
                                      0,
                                      I0_WUEPS_PID_VC);

    if (TAF_SUCCESS != ulResult)
    {
        AT_WARN_LOG("AT_QryCbgPara: send Msg fail.");
        return AT_ERROR;
    }

    /*  */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CBG_READ;

    return AT_WAIT_ASYNC_RETURN;
}

/* Added by w00176964 for V7R1C50_DCM, 2012-12-12, begin */
/*****************************************************************************
     : AT_QryAcInfoPara
   : UE
             <CR><LF>^ACINFO:<srv_domain>,<cell_ac>,<reg_restrict>,<paging_restrict><<CR><LF>
             CIPHER:
   : VOS_UINT8 ucIndex
   : 
     : AT_ERRORAT_OK
   :
   :

       :
  1.       : 20121212
           : W00176964
       : 
  2.       : 20150323
           : K00902809
       : Added the seperate function TAF_MMA_QryAcInfoReq to send message to MMA
                 and deleted TAF_MMA_AC_INFO_QUERY_REQ_STRU.
*****************************************************************************/
VOS_UINT32 AT_QryAcInfoPara(VOS_UINT8 ucIndex)
{
    /* Modified by k902809 for Iteration 11, 2015-3-23, begin */
    VOS_UINT32                          ulResult;

    /* MMAUE */
    ulResult = TAF_MMA_QryAcInfoReq(WUEPS_PID_AT,
                                    gastAtClientTab[ucIndex].usClientId,
                                    0);
    /*  */
    if (VOS_TRUE == ulResult)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_ACINFO_READ;

        /*  */
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
    /* Modified by k902809 for Iteration 11, Iteration 11 2015-3-23, end */
}

/* Added by w00176964 for V7R1C50_DCM, 2012-12-12, end */

/*****************************************************************************
     : AT_QryCLteRoamAllowPara
   : ^CLTEROAMALLOW,LTE
   : ucIndex - 
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 20121219
           : l00171473
       : DTS2012121803877, ATLTE
  2.       : 2013517
           : l00167671
       : NV, NV

  3.       : 2013109
           : z00234330
       : DTS201300600336,2,22
*****************************************************************************/
VOS_UINT32 AT_QryCLteRoamAllowPara(VOS_UINT8 ucIndex)
{
    VOS_UINT8                                       ucLteRoamAllow;
    NAS_MMC_NVIM_LTE_INTERNATIONAL_ROAM_CFG_STRU    stNvimLteRoamAllowedFlg;
    VOS_UINT32                                      ulLength;

    ulLength = 0;


    /*  */
    ucLteRoamAllow          = VOS_FALSE;
    stNvimLteRoamAllowedFlg.ucLteRoamAllowedFlg = VOS_FALSE;

    (VOS_VOID)NV_GetLength(en_NV_Item_Lte_Internation_Roam_Config, &ulLength);

    /* NV, NV NAS_MMC_NVIM_LTE_INTERNATIONAL_ROAM_CFG_STRU, 1 */
    if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_Lte_Internation_Roam_Config,
                         &stNvimLteRoamAllowedFlg,
                         ulLength))
    {
        AT_WARN_LOG("AT_QryCLteRoamAllowPara(): en_NV_Item_Lte_Internation_Roam_Config NV_ReadEx Error");
        return AT_ERROR;
    }


    /* , NVVOS_FALSE,  */
    if (VOS_FALSE == stNvimLteRoamAllowedFlg.ucLteRoamAllowedFlg)
    {
        ucLteRoamAllow = VOS_FALSE;
    }
    else
    {
        ucLteRoamAllow = VOS_TRUE;
    }

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%d",
                                                     g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                     ucLteRoamAllow);
    return AT_OK;
}


/*****************************************************************************
     : At_QryMmPlmnInfoPara
   : MM INFOPLMN
   : VOS_UINT8 ucIndex
   : 
     : AT_ERRORAT_OK
   :
   :

       :
  1.       : 20130109
           : l65478
       : 
  2.       : 20150330
           : K00902809
       : Added new function TAF_MMA_QryMMPlmnInfoReq to send message to MMA.
*****************************************************************************/
VOS_UINT32 At_QryMmPlmnInfoPara(VOS_UINT8 ucIndex)
{
    /* Modified by k902809 for Iteration 11, 2015-3-30, begin */
    if(VOS_TRUE == TAF_MMA_QryMMPlmnInfoReq(WUEPS_PID_AT,
                                            gastAtClientTab[ucIndex].usClientId,
                                            0))
    /* Modified by k902809 for Iteration 11, Iteration 11 2015-3-30, end */
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_MMPLMNINFO_QRY;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}

/*****************************************************************************
     : At_QryEonsUcs2Para
   : EONSUCS2PLMN
   : VOS_UINT8   ucIndex
   : 
     : AT_ERROR             -- 
             AT_OK                -- 
   :
   :

       :
  1.       : 20150312
           : c00318887
       : 
*****************************************************************************/
VOS_UINT32 At_QryEonsUcs2Para(VOS_UINT8 ucIndex)
{
    if(VOS_TRUE == TAF_MMA_QryEonsUcs2Req(
                    WUEPS_PID_AT,
                    gastAtClientTab[ucIndex].usClientId,
                    0))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_EONSUCS2_QRY;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}

/*****************************************************************************
     : At_QryPlmnPara
   : PLMNmcc mnc
   : VOS_UINT8 ucIndex
   : 
     : AT_ERRORAT_WAIT_ASYNC_RETURN
   :
   :

       :
  1.       : 20130123
           : Y00213812
       : 
  2.       : 20150330
           : K00902809
       : Added new function TAF_MMA_QryPlmnReq to send message to MMA.
*****************************************************************************/
VOS_UINT32 At_QryPlmnPara(VOS_UINT8 ucIndex)
{
    /* Modified by k902809 for Iteration 11, 2015-3-30, begin */
    if(VOS_TRUE == TAF_MMA_QryPlmnReq(WUEPS_PID_AT,
                                      gastAtClientTab[ucIndex].usClientId,
                                      0))
    /* Modified by k902809 for Iteration 11, Iteration 11 2015-3-30, end */
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_PLMN_QRY;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }

}

/*****************************************************************************
     : At_QryXlemaPara
   : ^XLEMA
   : VOS_UINT8 ucIndex
   : 
     : AT_ERRORAT_WAIT_ASYNC_RETURN
   :
   :

       :
  1.       : 20130123
           : Y00213812
       : 
*****************************************************************************/
VOS_UINT32 At_QryXlemaPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRst;

    /*  */
    ulRst = MN_CALL_SendAppRequest(MN_CALL_APP_XLEMA_REQ,
                                   gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   0,
                                   TAF_NULL_PTR);

    if (MN_ERR_NO_ERROR != ulRst)
    {
        AT_WARN_LOG("At_QryXlemaPara: MN_CALL_SendAppRequest fail.");
        return AT_ERROR;
    }

    /* OK */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_XLEMA_QRY;
    return AT_WAIT_ASYNC_RETURN;

}

/*****************************************************************************
     : AT_QryBodySarOnPara
   : ^BODYSARON,BODYSAR
   : ucIndex - 
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 20130311
           : z00214637
       : ^BODYSARON

*****************************************************************************/
VOS_UINT32 AT_QryBodySarOnPara(VOS_UINT8 ucIndex)
{
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    "%s: %d",
                                                     g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                     g_enAtBodySarState);
    return AT_OK;
}

/*****************************************************************************
     : AT_FillBodySarWcdmaQryPara
   : Body SAR^BODYSARWCDMA
   : pstBodySarPara         -- Body SAR
   : pstBodySarWcdmaPara    -- ^BODYSARWCDMA
     : VOS_OK     -- 
             VOS_ERR    -- 
   :
   :

       :
  1.       : 20130311
           : l00198894
       : Body SAR

*****************************************************************************/
VOS_UINT32 AT_FillBodySarWcdmaQryPara(
    MTA_BODY_SAR_PARA_STRU             *pstBodySarPara,
    AT_BODYSARWCDMA_SET_PARA_STRU      *pstBodySarWcdmaPara)
{
    VOS_UINT8                           ucLoop1;
    VOS_UINT8                           ucLoop2;
    AT_NV_WG_RF_MAIN_BAND_STRU          stWGBand;
    VOS_UINT32                          ulTmpBand;

    TAF_MEM_SET_S(&stWGBand, sizeof(stWGBand), 0x00, sizeof(stWGBand));
    ulTmpBand       = 0;

    /* WCDMA Band */
    if (NV_OK != NV_ReadEx(MODEM_ID_0,
                            en_NV_Item_WG_RF_MAIN_BAND,
                            &stWGBand,
                            sizeof(stWGBand)))
    {
        AT_ERR_LOG("AT_FillBodySarWcdmaQryPara: Read NV fail!");
        return VOS_ERR;
    }

    for (ucLoop1 = 0; ucLoop1 < pstBodySarPara->usWBandNum; ucLoop1++)
    {
        for (ucLoop2 = 0; ucLoop2 < pstBodySarWcdmaPara->ucParaNum; ucLoop2++)
        {
            if (pstBodySarPara->astWBandPara[ucLoop1].sPower == pstBodySarWcdmaPara->asPower[ucLoop2])
            {
                break;
            }
        }

        if (ucLoop2 == pstBodySarWcdmaPara->ucParaNum)
        {
            pstBodySarWcdmaPara->ucParaNum++;
            pstBodySarWcdmaPara->asPower[ucLoop2] =pstBodySarPara->astWBandPara[ucLoop1].sPower;
        }

        pstBodySarWcdmaPara->aulBand[ucLoop2]   |= 0x00000001U << (pstBodySarPara->astWBandPara[ucLoop1].enBand - 1);
        ulTmpBand                               |= pstBodySarWcdmaPara->aulBand[ucLoop2];
    }

    /*  */
    ulTmpBand = stWGBand.unWcdmaBand.ulBand & (~ulTmpBand);
    if (0 != ulTmpBand)
    {
        pstBodySarWcdmaPara->aulBand[pstBodySarWcdmaPara->ucParaNum] = ulTmpBand;
        pstBodySarWcdmaPara->asPower[pstBodySarWcdmaPara->ucParaNum] = AT_WCDMA_BAND_DEFAULT_POWER;
        pstBodySarWcdmaPara->ucParaNum++;
    }

    return VOS_OK;
}

/*****************************************************************************
     : AT_QryBodySarWcdmaPara
   : AT^BODYSARWCDMA
   : VOS_UINT8 ucIndex  
   : 
     : VOS_UINT32         AT
   :
   :

       :
  1.       : 20130311
           : l00198894
       : Body SAR

*****************************************************************************/
VOS_UINT32 AT_QryBodySarWcdmaPara(VOS_UINT8 ucIndex)
{
    MTA_BODY_SAR_PARA_STRU              stBodySarPara;
    AT_BODYSARWCDMA_SET_PARA_STRU       stBodySarWcdmaPara;
    VOS_UINT8                           ucLoop;
    VOS_UINT16                          usLength;

    TAF_MEM_SET_S(&stBodySarPara, sizeof(stBodySarPara), 0x00, sizeof(stBodySarPara));
    TAF_MEM_SET_S(&stBodySarWcdmaPara, sizeof(stBodySarWcdmaPara), 0x00, sizeof(stBodySarWcdmaPara));
    usLength        = 0;

    /* NVBody SAR */
    if (NV_OK != NV_ReadEx(MODEM_ID_0,
                            en_NV_Item_BODY_SAR_PARA,
                            &stBodySarPara,
                            sizeof(stBodySarPara)))
    {
        AT_ERR_LOG("AT_QryBodySarWcdmaPara: Read NV fail!");
        return AT_ERROR;
    }

    /* Body SAR^BODYSARWCDMA */
    if (VOS_OK != AT_FillBodySarWcdmaQryPara(&stBodySarPara, &stBodySarWcdmaPara))
    {
        AT_ERR_LOG("AT_QryBodySarWcdmaPara: AT_FillBodySarWcdmaQryPara fail!");
        return AT_ERROR;
    }

    /*  */
    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      "%s: ",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    /* WCDMABody SAR */
    if (1 == stBodySarWcdmaPara.ucParaNum)
    {
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "(%d,%08X)",
                                           stBodySarWcdmaPara.asPower[0],
                                           AT_RF_BAND_ANY);

        gstAtSendData.usBufLen = usLength;

        return AT_OK;
    }

    for (ucLoop = 0; ucLoop < stBodySarWcdmaPara.ucParaNum; ucLoop++)
    {
        if (0 != ucLoop)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                               ",");
        }

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "(%d,%08X)",
                                           stBodySarWcdmaPara.asPower[ucLoop],
                                           stBodySarWcdmaPara.aulBand[ucLoop]);
    }

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}

/*****************************************************************************
     : AT_FillBodySarGsmDefaultPower
   : Body SARGSM
   : 
   : pstBodySarPara     -- Body SAR
     : VOS_OK     -- 
             VOS_ERR    -- 
   :
   :

       :
  1.       : 20130311
           : l00198894
       : Body SAR

*****************************************************************************/
VOS_UINT32 AT_FillBodySarGsmDefaultPower(
    MTA_BODY_SAR_PARA_STRU             *pstBodySarPara)
{
    VOS_UINT32                          ulGBandCapa;
    VOS_UINT32                          ulTmpBand;

    ulGBandCapa     = 0;
    ulTmpBand       = 0;

    /* GSM Band */
    if (VOS_OK != AT_GetGsmBandCapa(&ulGBandCapa))
    {
        AT_ERR_LOG("AT_FillBodySarGsmDefaultPower: AT_GetGsmBandCapa fail!");
        return VOS_ERR;
    }

    ulTmpBand = ulGBandCapa & (~pstBodySarPara->ulGBandMask);

    if (0 != (AT_BODY_SAR_GBAND_GPRS_850_MASK & ulTmpBand))
    {
        pstBodySarPara->ulGBandMask |= AT_BODY_SAR_GBAND_GPRS_850_MASK;
        pstBodySarPara->astGBandPara[AT_GSM_850].sGPRSPower = AT_GSM_GPRS_850_DEFAULT_POWER;
    }

    if (0 != (AT_BODY_SAR_GBAND_EDGE_850_MASK & ulTmpBand))
    {
        pstBodySarPara->ulGBandMask |= AT_BODY_SAR_GBAND_EDGE_850_MASK;
        pstBodySarPara->astGBandPara[AT_GSM_850].sEDGEPower = AT_GSM_EDGE_850_DEFAULT_POWER;
    }

    if (0 != (AT_BODY_SAR_GBAND_GPRS_900_MASK & ulTmpBand))
    {
        pstBodySarPara->ulGBandMask |= AT_BODY_SAR_GBAND_GPRS_900_MASK;
        pstBodySarPara->astGBandPara[AT_GSM_900].sGPRSPower = AT_GSM_GPRS_900_DEFAULT_POWER;
    }

    if (0 != (AT_BODY_SAR_GBAND_EDGE_900_MASK & ulTmpBand))
    {
        pstBodySarPara->ulGBandMask |= AT_BODY_SAR_GBAND_EDGE_900_MASK;
        pstBodySarPara->astGBandPara[AT_GSM_900].sEDGEPower = AT_GSM_EDGE_900_DEFAULT_POWER;
    }

    if (0 != (AT_BODY_SAR_GBAND_GPRS_1800_MASK & ulTmpBand))
    {
        pstBodySarPara->ulGBandMask |= AT_BODY_SAR_GBAND_GPRS_1800_MASK;
        pstBodySarPara->astGBandPara[AT_GSM_1800].sGPRSPower = AT_GSM_GPRS_1800_DEFAULT_POWER;
    }

    if (0 != (AT_BODY_SAR_GBAND_EDGE_1800_MASK & ulTmpBand))
    {
        pstBodySarPara->ulGBandMask |= AT_BODY_SAR_GBAND_EDGE_1800_MASK;
        pstBodySarPara->astGBandPara[AT_GSM_1800].sEDGEPower = AT_GSM_EDGE_1800_DEFAULT_POWER;
    }

    if (0 != (AT_BODY_SAR_GBAND_GPRS_1900_MASK & ulTmpBand))
    {
        pstBodySarPara->ulGBandMask |= AT_BODY_SAR_GBAND_GPRS_1900_MASK;
        pstBodySarPara->astGBandPara[AT_GSM_1900].sGPRSPower = AT_GSM_GPRS_1900_DEFAULT_POWER;
    }

    if (0 != (AT_BODY_SAR_GBAND_EDGE_1900_MASK & ulTmpBand))
    {
        pstBodySarPara->ulGBandMask |= AT_BODY_SAR_GBAND_EDGE_1900_MASK;
        pstBodySarPara->astGBandPara[AT_GSM_1900].sEDGEPower = AT_GSM_EDGE_1900_DEFAULT_POWER;
    }

    return VOS_OK;
}

/*****************************************************************************
     : AT_FillBodySarGsmByModulationMode
   : Body SAR^BODYSARGSM
   : pstBodySarPara     -- Body SAR
             ucModulationOffset -- GSM
   : pstBodySarGsmPara  -- ^BODYSARGSM
     : 
   :
   :

       :
  1.       : 20130311
           : l00198894
       : Body SAR

*****************************************************************************/
VOS_VOID AT_FillBodySarGsmByModulationMode(
    MTA_BODY_SAR_PARA_STRU             *pstBodySarPara,
    VOS_UINT8                           ucModulationOffset,
    AT_BODYSARGSM_SET_PARA_STRU        *pstBodySarGsmPara)
{
    VOS_UINT8                           ucLoop1;
    VOS_UINT8                           ucLoop2;

    for (ucLoop1 = AT_GSM_850; ucLoop1 < AT_GSM_BAND_BUTT; ucLoop1++)
    {
        for (ucLoop2 = 0; ucLoop2 < pstBodySarGsmPara->ucParaNum; ucLoop2++)
        {
            if (AT_GSM_GPRS_BAND_OFFSET == ucModulationOffset)
            {
                if (pstBodySarPara->astGBandPara[ucLoop1].sGPRSPower == pstBodySarGsmPara->asPower[ucLoop2])
                {
                    break;
                }
            }
            else
            {
                if (pstBodySarPara->astGBandPara[ucLoop1].sEDGEPower == pstBodySarGsmPara->asPower[ucLoop2])
                {
                    break;
                }
            }
        }

        if (ucLoop2 == pstBodySarGsmPara->ucParaNum)
        {
            pstBodySarGsmPara->ucParaNum++;
            if (AT_GSM_GPRS_BAND_OFFSET == ucModulationOffset)
            {
                pstBodySarGsmPara->asPower[ucLoop2] = pstBodySarPara->astGBandPara[ucLoop1].sGPRSPower;
            }
            else
            {
                pstBodySarGsmPara->asPower[ucLoop2] = pstBodySarPara->astGBandPara[ucLoop1].sEDGEPower;
            }
        }
        pstBodySarGsmPara->aulBand[ucLoop2]   |= 0x00000001U << (ucLoop1 + ucModulationOffset);
    }

    return;
}

/*****************************************************************************
     : AT_QryBodySarGsmPara
   : AT^BODYSARGSM
   : VOS_UINT8 ucIndex  
   : 
     : VOS_UINT32         AT
   :
   :

       :
  1.       : 20130311
           : l00198894
       : Body SAR

*****************************************************************************/
VOS_UINT32 AT_QryBodySarGsmPara(VOS_UINT8 ucIndex)
{
    MTA_BODY_SAR_PARA_STRU              stBodySarPara;
    AT_BODYSARGSM_SET_PARA_STRU         stBodySarGsmPara;
    VOS_UINT8                           ucLoop;
    VOS_UINT16                          usLength;

    TAF_MEM_SET_S(&stBodySarPara, sizeof(stBodySarPara), 0x00, sizeof(stBodySarPara));
    TAF_MEM_SET_S(&stBodySarGsmPara, sizeof(stBodySarGsmPara), 0x00, sizeof(stBodySarGsmPara));
    usLength        = 0;

    /* NVBody SAR */
    if (NV_OK != NV_ReadEx(MODEM_ID_0,
                            en_NV_Item_BODY_SAR_PARA,
                            &stBodySarPara,
                            sizeof(stBodySarPara)))
    {
        AT_ERR_LOG("AT_QryBodySarGsmPara: Read NV fail!");
        return AT_ERROR;
    }

    /* GSMBody SAR */
    if (VOS_OK != AT_FillBodySarGsmDefaultPower(&stBodySarPara))
    {
        AT_ERR_LOG("AT_QryBodySarGsmPara: AT_FillBodySarGsmDefaultPower fail!");
        return AT_ERROR;
    }

    /* Body SAR^BODYSARGSM */
    /* GPRS */
    AT_FillBodySarGsmByModulationMode(&stBodySarPara, AT_GSM_GPRS_BAND_OFFSET, &stBodySarGsmPara);

    /* EDGE */
    AT_FillBodySarGsmByModulationMode(&stBodySarPara, AT_GSM_EDGE_BAND_OFFSET, &stBodySarGsmPara);

    /*  */
    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      "%s: ",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    /* GSMBody SAR */
    if (1 == stBodySarGsmPara.ucParaNum)
    {
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "(%d,%08X)",
                                           stBodySarGsmPara.asPower[0],
                                           AT_RF_BAND_ANY);

        gstAtSendData.usBufLen = usLength;

        return AT_OK;
    }

    for (ucLoop = 0; ucLoop < stBodySarGsmPara.ucParaNum; ucLoop++)
    {
        if (0 != ucLoop)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                               ",");
        }

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "(%d,%08X)",
                                           stBodySarGsmPara.asPower[ucLoop],
                                           stBodySarGsmPara.aulBand[ucLoop]);
    }

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}


/*****************************************************************************
     : At_QryIMEIVerifyPara
   : IMEI
   : VOS_UINT8 ucIndex
   : 
     : AT_ERRORAT_WAIT_ASYNC_RETURN
   :
   :

       :
  1.       : 20130523
           : Y00213812
       : 
*****************************************************************************/
VOS_UINT32 At_QryIMEIVerifyPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRst;

    /*  ID_AT_MTA_IMEI_VERIFY_QRY_REQ  MTA  */
    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   ID_AT_MTA_IMEI_VERIFY_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_UEPS_PID_MTA);

    if(AT_SUCCESS == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_IMEI_VERIFY_READ;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }

}

/*****************************************************************************
     : AT_QryNCellMonitorPara
   : TD/LTE
   : TAF_UINT8 ucIndex
   : 
     : TAF_UINT32
   :
   :

       :
  4.       : 201364
           : s00217060
       : 
*****************************************************************************/
VOS_UINT32 AT_QryNCellMonitorPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulResult;

    /* MTA^NCELLMONITOR */
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   ID_AT_MTA_NCELL_MONITOR_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_UEPS_PID_MTA);

    if (TAF_SUCCESS != ulResult)
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_NCELL_MONITOR_READ;

    return AT_WAIT_ASYNC_RETURN;
}

/*****************************************************************************
     : AT_QryUserSrvStatePara
   : 
   : TAF_UINT8 ucIndex
   : 
     : TAF_UINT32
   :
   :

       :
  1.       : 2013611
           : s00217060
       : 

  2.       : 20150327
           : K00902809
       : Added seperate function TAF_MMA_QryUserSrvStateReq to send message to mma
*****************************************************************************/
VOS_UINT32 AT_QryUserSrvStatePara(VOS_UINT8 ucIndex)
{
    /* Modified by k902809 for Iteration 11, 2015-3-27, begin */
    if(VOS_TRUE == TAF_MMA_QryUserSrvStateReq(WUEPS_PID_AT,
                                              gastAtClientTab[ucIndex].usClientId,
                                              0))
    /* Modified by k902809 for Iteration 11, Iteration 11 2015-3-27, end */
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_USER_SRV_STATE_READ;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}


/*****************************************************************************
     : AT_QryRefclkfreqPara
   : GPSAT^REFCLKFREQ
   : ucIndex    -- AT
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20130722
           : l00198894
       : V9R1 AGPS
*****************************************************************************/
VOS_UINT32 AT_QryRefclkfreqPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulResult;

    /*  */
    if (VOS_FALSE == AT_IsApPort(ucIndex))
    {
        return AT_ERROR;
    }

    /* C, GPS */
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                      gastAtClientTab[ucIndex].opId,
                                      ID_AT_MTA_REFCLKFREQ_QRY_REQ,
                                      VOS_NULL_PTR,
                                      0,
                                      I0_UEPS_PID_MTA);

    if (TAF_SUCCESS != ulResult)
    {
        AT_WARN_LOG("At_QryRefclkfreqPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* AT */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_REFCLKFREQ_READ;

    return AT_WAIT_ASYNC_RETURN;
}

/*****************************************************************************
     : At_QryHandleDect
   : cp
   : VOS_UINT8 ucIndex
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 201388
           : M00217266
       : AP Sensor:

*****************************************************************************/
VOS_UINT32 At_QryHandleDect(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRst;
    VOS_UINT8                          *pucSystemAppConfig;

    /* NV */
    pucSystemAppConfig = AT_GetSystemAppConfigAddr();

    /* ANDROID */
    if ( SYSTEM_APP_ANDROID != *pucSystemAppConfig)
    {
        return AT_CMD_NOT_SUPPORT;
    }

    /*  */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    /*  ID_AT_MTA_HANDLEDECT_QRY_REQ MTA */
    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   At_GetOpId(),
                                   ID_AT_MTA_HANDLEDECT_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_UEPS_PID_MTA);

    if (AT_SUCCESS == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_HANDLEDECT_QRY;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }

}

/*****************************************************************************
     : AT_QryLogNvePara
   : ^LOGNVE
   : ucIndex - 
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 20130117
           : H59254
       : 
  2.       : 20131008
           : j00174725
       : TQE
  3.       : 201542
           : w00316404
       : clean coverity
*****************************************************************************/
VOS_UINT32 AT_QryLogNvePara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulResult;
    VOS_UINT16                          usLength;
    VOS_UINT32                          ulEnable;
    VOS_UINT32                          ulTimeout;
    VOS_UINT32                          ulBufferSize;
    SOCP_ENC_DST_BUF_LOG_CFG_STRU       stLogCfg = {0};

    ulEnable                            = 0;
    ulTimeout                           = 0;
    ulBufferSize                        = 0;


    ulResult = mdrv_socp_get_sd_logcfg(&stLogCfg);

    if (VOS_OK != ulResult)
    {
        return AT_ERROR;
    }

    ulEnable = stLogCfg.logOnFlag;
    ulTimeout= stLogCfg.ulCurTimeout;
    ulBufferSize = stLogCfg.BufferSize;

    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      "%s: %d,%d,%d",
                                      g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                      ulEnable,
                                      ulTimeout,
                                      ulBufferSize);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}

/*****************************************************************************
     : AT_QryCiregPara
   : +CIREG?
   : VOS_UINT8 ucIndex
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 20130918
           : Y00213812
       : 

*****************************************************************************/
VOS_UINT32 AT_QryCiregPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRst;
    MODEM_ID_ENUM_UINT16                enModemId;

    enModemId = MODEM_ID_0;

    /* client idModem Id */
    ulRst = AT_GetModemIdFromClient(gastAtClientTab[ucIndex].usClientId, &enModemId);

    if (VOS_ERR == ulRst)
    {
        AT_WARN_LOG("AT_QryCiregPara: AT_GetModemIdFromClient fail.");
        return AT_ERROR;
    }

    if ((MODEM_ID_1 == enModemId) || (MODEM_ID_2 == enModemId))
    {
        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           "%s: %d,0",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                           AT_IMSA_IMS_REG_STATE_DISABLE_REPORT);

        return AT_OK;
    }

    /*  */
    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   ID_AT_IMSA_CIREG_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_PS_PID_IMSA);

    if (TAF_SUCCESS != ulRst)
    {
        AT_WARN_LOG("AT_QryCiregPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /*  */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CIREG_QRY;
    return AT_WAIT_ASYNC_RETURN;

}

/*****************************************************************************
     : AT_QryCirepPara
   : +CIREP?
   : VOS_UINT8 ucIndex
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 20130918
           : Y00213812
       : 

*****************************************************************************/
VOS_UINT32 AT_QryCirepPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRst;

    /*  */
    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   ID_AT_IMSA_CIREP_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_PS_PID_IMSA);

    if (TAF_SUCCESS != ulRst)
    {
        AT_WARN_LOG("AT_QryCirepPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /*  */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CIREP_QRY;
    return AT_WAIT_ASYNC_RETURN;

}

/*****************************************************************************
     : AT_QryImsRegDomainPara
   : ^IMSREGDOMAIN?
   : VOS_UINT8 ucIndex
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 20151023
           : h00360002
       : 

*****************************************************************************/
VOS_UINT32 AT_QryImsRegDomainPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32 ulResult;

    /*  */
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                      gastAtClientTab[ucIndex].opId,
                                      ID_AT_IMSA_IMS_REG_DOMAIN_QRY_REQ,
                                      VOS_NULL_PTR,
                                      0,
                                      I0_PS_PID_IMSA);

    if (TAF_SUCCESS != ulResult)
    {
        AT_WARN_LOG("AT_QryImsRegDomainPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_IMSREGDOMAIN_QRY;

    return AT_WAIT_ASYNC_RETURN;
}

/*****************************************************************************
     : AT_QryImsDomainCfgPara
   : ^IMSDOMAINCFG?
   : VOS_UINT8 ucIndex
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 20151026
           : h00360002
       : 

*****************************************************************************/
VOS_UINT32 AT_QryImsDomainCfgPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32 ulResult;

    /*  */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    /* AT MMA  */
    ulResult = TAF_MMA_QryImsDomainCfgReq(WUEPS_PID_AT,
                                          gastAtClientTab[ucIndex].usClientId,
                                          0);

    if (VOS_TRUE == ulResult)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_IMSDOMAINCFG_QRY;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }

}

/*****************************************************************************
     : AT_QryImsEmcRdpPara
   : ^IMSEMCRDP?
   : ucIndex - 
   : 
     : AT_XXX  - ATC
   :
   :

       :
  1.       : 2017323
           : A00165503
       : 

*****************************************************************************/
VOS_UINT32 AT_QryImsEmcRdpPara(VOS_UINT8 ucIndex)
{
    AT_IMS_EMC_RDP_STRU                *pstImsEmcRdp = VOS_NULL_PTR;
    VOS_CHAR                            acIpv4AddrStr[TAF_MAX_IPV4_ADDR_STR_LEN];
    VOS_UINT8                           aucIpv6AddrStr[TAF_MAX_IPV6_ADDR_COLON_STR_LEN];
    VOS_UINT16                          usLength = 0;

    TAF_MEM_SET_S(acIpv4AddrStr, sizeof(acIpv4AddrStr), 0x00, sizeof(acIpv4AddrStr));
    TAF_MEM_SET_S(aucIpv6AddrStr, sizeof(aucIpv6AddrStr), 0x00, sizeof(aucIpv6AddrStr));

    /* IMS EMC RDP */
    pstImsEmcRdp = AT_GetImsEmcRdpByClientId(ucIndex);
    if (VOS_NULL_PTR == pstImsEmcRdp)
    {
        AT_WARN_LOG("AT_QryImsEmcRdpPara: ImsEmcRdp not found.");
        return AT_ERROR;
    }

    /* IMS EMC PDN */
    if ( (VOS_TRUE != pstImsEmcRdp->bitOpIPv4PdnInfo)
      && (VOS_TRUE != pstImsEmcRdp->bitOpIPv6PdnInfo) )
    {
        return AT_ERROR;
    }

    if (VOS_TRUE == pstImsEmcRdp->bitOpIPv4PdnInfo)
    {
        /* ^IMSEMCRDP: */
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR*)pgucAtSndCodeAddr,
                                           (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                           "%s:",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
        /* IP Type */
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%s",
                                           "\"IPV4\"");
        /* IP Addr */
        AT_Ipv4AddrItoa(acIpv4AddrStr, pstImsEmcRdp->stIPv4PdnInfo.aucIpAddr);
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           ",\"%s\"",
                                           acIpv4AddrStr);

        /* Primary DNS */
        AT_Ipv4AddrItoa(acIpv4AddrStr, pstImsEmcRdp->stIPv4PdnInfo.aucDnsPrimAddr);
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           ",\"%s\"",
                                           acIpv4AddrStr);

        /* Secondary DNS */
        AT_Ipv4AddrItoa(acIpv4AddrStr, pstImsEmcRdp->stIPv4PdnInfo.aucDnsSecAddr);
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           ",\"%s\"",
                                           acIpv4AddrStr);

        /* MTU */
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           ",%d",
                                           pstImsEmcRdp->stIPv4PdnInfo.usMtu);
    }

    if ( (VOS_TRUE == pstImsEmcRdp->bitOpIPv4PdnInfo)
      && (VOS_TRUE == pstImsEmcRdp->bitOpIPv6PdnInfo) )
    {
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%s",
                                           gaucAtCrLf);
    }

    if (VOS_TRUE == pstImsEmcRdp->bitOpIPv6PdnInfo)
    {
        /* ^IMSEMCRDP: */
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR*)pgucAtSndCodeAddr,
                                           (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                           "%s:",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

        /* IP Type */
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%s",
                                           "\"IPV6\"");

        /* IP Addr */
        AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                          pstImsEmcRdp->stIPv6PdnInfo.aucIpAddr,
                                          TAF_IPV6_STR_RFC2373_TOKENS);

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           ",\"%s\"",
                                           aucIpv6AddrStr);

        /* Primary DNS */
        AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                          pstImsEmcRdp->stIPv6PdnInfo.aucDnsPrimAddr,
                                          TAF_IPV6_STR_RFC2373_TOKENS);

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           ",\"%s\"",
                                           aucIpv6AddrStr);

        /* Secondary DNS */
        AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                          pstImsEmcRdp->stIPv6PdnInfo.aucDnsSecAddr,
                                          TAF_IPV6_STR_RFC2373_TOKENS);

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           ",\"%s\"",
                                           aucIpv6AddrStr);

        /* MTU */
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           ",%d",
                                           pstImsEmcRdp->stIPv6PdnInfo.usMtu);
    }

    gstAtSendData.usBufLen = usLength;
    return AT_OK;
}

/*****************************************************************************
     : AT_QryClccPara
   : ^CLCC?
   : VOS_UINT8 ucIndex
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 20130918
           : Y00213812
       : 

*****************************************************************************/
VOS_UINT32 AT_QryClccPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRet;

    /* C */
    ulRet = MN_CALL_GetCallInfos(gastAtClientTab[ucIndex].usClientId,
                                 gastAtClientTab[ucIndex].opId,
                                 0);
    if (VOS_OK != ulRet)
    {
        AT_WARN_LOG("AT_QryClccPara: MN_CALL_GetCallInfos fail.");
        return AT_ERROR;
    }

    /* AT */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CLCC_QRY;

    return AT_WAIT_ASYNC_RETURN;
}

/*****************************************************************************
     : AT_QryClccEconfInfo
   : 
   : ucIndex
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 20141128
           : j00174725
       : 
*****************************************************************************/
VOS_UINT32 AT_QryClccEconfInfo(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRet;

    /* C */
    ulRet = MN_CALL_SendAppRequest(TAF_CALL_APP_GET_ECONF_CALLED_INFO_REQ,
                                   gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   0,
                                   VOS_NULL_PTR);
    if (VOS_OK != ulRet)
    {
        AT_WARN_LOG("AT_QryClccEconfInfo: MN_CALL_SendAppRequest fail.");

        return AT_ERROR;
    }

    /* AT */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CLCCECONF_QRY;

    return AT_WAIT_ASYNC_RETURN;
}

/*****************************************************************************
     : AT_QryEconfErrPara
   : 
   : ucIndex
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 20141128
           : f00179208
       : 
*****************************************************************************/
VOS_UINT32 AT_QryEconfErrPara(VOS_UINT8 ucIndex)
{
    VOS_UINT16                          i;
    VOS_UINT16                          usLength;
    AT_MODEM_CC_CTX_STRU               *pstCcCtx     = VOS_NULL_PTR;
    AT_ECONF_INFO_STRU                 *pstEconfInfo = VOS_NULL_PTR;
    VOS_UINT8                           aucAsciiNum[MN_CALL_MAX_CALLED_ASCII_NUM_LEN + 1];
    VOS_UINT8                           ucNumOfCalls;
    VOS_UINT8                           ucErrNum;

    ucErrNum     = 0;
    usLength     = 0;
    pstCcCtx     = AT_GetModemCcCtxAddrFromClientId(ucIndex);
    pstEconfInfo = &(pstCcCtx->stEconfInfo);
    ucNumOfCalls = pstEconfInfo->ucNumOfCalls;
    TAF_MEM_SET_S(aucAsciiNum, sizeof(aucAsciiNum), 0x00, sizeof(aucAsciiNum));

    for (i = 0; ((i < ucNumOfCalls) && (i < TAF_CALL_MAX_ECONF_CALLED_NUM)); i++)
    {
        /*  */
        if ((0 != pstEconfInfo->astCallInfo[i].stCallNumber.ucNumLen)
         && (TAF_CS_CAUSE_SUCCESS != pstEconfInfo->astCallInfo[i].enCause))
        {
            /* <CR><LF> */
            if (0 != ucErrNum)
            {
                usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                   "%s",
                                                   gaucAtCrLf);
            }

            AT_BcdNumberToAscii(pstEconfInfo->astCallInfo[i].stCallNumber.aucBcdNum,
                                pstEconfInfo->astCallInfo[i].stCallNumber.ucNumLen,
                                (VOS_CHAR *)aucAsciiNum);

            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%s: \"%s\",%d,%d",
                                               g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                               aucAsciiNum,
                                               (pstEconfInfo->astCallInfo[i].stCallNumber.enNumType | AT_NUMBER_TYPE_EXT),
                                               pstEconfInfo->astCallInfo[i].enCause);

            ucErrNum++;
        }
    }

    gstAtSendData.usBufLen = usLength;

    return AT_OK;

}

/*****************************************************************************
     : AT_QryLteImsSwitchPara
   : IMS 
              :^LTEIMSSWITCH?
   : 
   : 
     : VOS_UINT32
   :
   :

       :
  1.     : 2015-02-02
         : zwx247453
     : 

*****************************************************************************/
VOS_UINT32 AT_QryLteImsSwitchPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRst;

    /*  */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    /* AT MMA  */
    ulRst = TAF_MMA_QryImsSwitchReq(WUEPS_PID_AT,
                                    gastAtClientTab[ucIndex].usClientId,
                                    0);
    if (VOS_TRUE == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_LTE_IMS_SWITCH_QRY;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}

/*****************************************************************************
     : AT_QryCevdpPara
   : 
               :+CEVDP?
   : 
   : 
     : VOS_UINT32
   :
   :

       :
  1.     : 2015-02-02
         : zwx247453
     : 

*****************************************************************************/
VOS_UINT32 AT_QryCevdpPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRst;

    /*  */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    /* AT MMA  */
    ulRst = TAF_MMA_QryVoiceDomainReq(WUEPS_PID_AT,
                                      gastAtClientTab[ucIndex].usClientId,
                                      0);
    if (VOS_TRUE == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_VOICE_DOMAIN_QRY;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}

/*****************************************************************************
     : AT_QryRoamImsServicePara
   : ^ROAMIMSSERVICE,
   : ucIndex - 
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 20160115
           : w00316404
       :
*****************************************************************************/
VOS_UINT32 AT_QryRoamImsServicePara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulResult;

    if(AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    /*  */
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                      gastAtClientTab[ucIndex].opId,
                                      ID_AT_IMSA_ROAMING_IMS_QRY_REQ,
                                      VOS_NULL_PTR,
                                      0,
                                      I0_PS_PID_IMSA);

    if (TAF_SUCCESS != ulResult)
    {
        AT_WARN_LOG("AT_QryRoamImsServicePara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /*  */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_ROAM_IMS_QRY;

    return AT_WAIT_ASYNC_RETURN;
}


/*****************************************************************************
     : AT_QryUserCfgOPlmnPara
   : ^EOPLMN
   : ucIndex - 
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 20131015
           : s00190137
       : 
  2.       : 20150330
           : K00902809
       : Added new function   TAF_MMA_SetEOPlmnReq to send message to MMA
*****************************************************************************/
VOS_UINT32 AT_QryUserCfgOPlmnPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRst;

    /*  ID_AT_MTA_HANDLEDECT_QRY_REQ MTA */
    /* Modified by k902809 for Iteration 11, 2015-3-30, begin */
    ulRst = TAF_MMA_QryEOPlmnReq(WUEPS_PID_AT,
                                 gastAtClientTab[ucIndex].usClientId,
                                 0);
    if (VOS_TRUE == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_EOPLMN_QRY;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
    /* Modified by k902809 for Iteration 11, Iteration 11 2015-3-30, end */
}


/*****************************************************************************
     : At_SetAntSwitchPara
   : ^ANTSWITCH
             :^ANTSWITCH?

   : ucIndex - 
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 20131111
           : y00258578
       : 

*****************************************************************************/
VOS_UINT32 AT_QryAntSwitchPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRst;

    /*  */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   At_GetOpId(),
                                   DRV_AGENT_ANTSWITCH_QRY_REQ,
                                   VOS_NULL,
                                   0,
                                   I0_WUEPS_PID_DRV_AGENT);

    if (TAF_SUCCESS == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_ANTSWITCH_QRY;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}


/*****************************************************************************
     : AT_QryModemStatusPara
   : ^MODEMSTATUS 
             <CR><LF>OK<CR><LF>
   : 
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 20131220
           : d00212987
       : V9R1 L_plus_C
*****************************************************************************/
VOS_UINT32 AT_QryModemStatusPara(VOS_UINT8 ucIndex)
{
    return AT_OK;
}

/*****************************************************************************
     : AT_QryRATCombinePara
   : ^RATCOMBINEPRIO 
             <CR><LF>OK<CR><LF>
   : 
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 20131220
           : z00100318
       : V9R1 L_plus_C phaseII

  2.       : 2014214
           : j00174725
       : TQE
*****************************************************************************/
VOS_UINT32 AT_QryRATCombinePara(VOS_UINT8 ucIndex)
{
    TAF_NV_LC_CTRL_PARA_STRU            stNVData;
    VOS_UINT16                          usLength;
    VOS_UINT8                           usRatMode;
    MODEM_ID_ENUM_UINT16                enModemId;

    TAF_MEM_SET_S(&stNVData, sizeof(stNVData), 0x00, sizeof(stNVData));

    if (VOS_OK != AT_GetModemIdFromClient(ucIndex, &enModemId))
    {
        AT_ERR_LOG("AT_QryRATCombinePara: Get modem id fail.");

        return AT_ERROR;
    }

    if (NV_OK != NV_ReadEx(enModemId, en_NV_Item_LC_Ctrl_PARA, &stNVData, sizeof(TAF_NV_LC_CTRL_PARA_STRU)))
    {
        AT_ERR_LOG("AT_QryRATCombinePara: Get en_NV_Item_LC_Ctrl_PARA id fail.");

        return AT_ERROR;
    }

    if (VOS_TRUE != stNVData.ucLCEnableFlg)
    {
        return AT_CME_OPERATION_NOT_ALLOWED;
    }

    if (TAF_NVIM_LC_RAT_COMBINED_CL == stNVData.enRatCombined)
    {
        usRatMode = 0;
    }
    else if (TAF_NVIM_LC_RAT_COMBINED_GUL == stNVData.enRatCombined)
    {
        usRatMode = 1;
    }
    else
    {
        return AT_ERROR;
    }

    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      "%s: %d",
                                      g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                      usRatMode);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}


/*****************************************************************************
     : AT_QryMipiClkValue
   : ^MIPICLKMIPICLK
   : ucIndex - 
   : 
     : 
   :
   :

       :
  1.       : 20140304
           : j00174725
       : RF&LCD INTRUSION
*****************************************************************************/
VOS_UINT32 AT_QryMipiClkValue(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulResult;

    /* AT MTA  */
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                      gastAtClientTab[ucIndex].opId,
                                      ID_AT_MTA_MIPICLK_QRY_REQ,
                                      VOS_NULL_PTR,
                                      0,
                                      I0_UEPS_PID_MTA);

    if (TAF_SUCCESS != ulResult)
    {
        AT_WARN_LOG("AT_QryMipiClkValue: send Msg fail.");
        return AT_ERROR;
    }

    /*  */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_MIPI_CLK_QRY;

    return AT_WAIT_ASYNC_RETURN;

}

/*****************************************************************************
     : AT_QryBestFreqPara
   : ^BESTFREQBESTFREQ
   : ucIndex - 
   : 
     : 
   :
   :

       :
  1.       : 20160727
           : q00380176
       : dynamic_fm_intrusion_ctrl
*****************************************************************************/
VOS_UINT32 AT_QryBestFreqPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulRslt;
    MODEM_ID_ENUM_UINT16                enModemId;

    enModemId = MODEM_ID_BUTT;
    ulRslt    = AT_GetModemIdFromClient(gastAtClientTab[ucIndex].usClientId, &enModemId);

    /* ModemIDModem0 */
    if ((enModemId != MODEM_ID_0)
     || (ulRslt != VOS_OK))
    {
        AT_WARN_LOG("AT_QryBestFreqPara: Not  Modem0 or fail to get current ModemID!");
        return AT_ERROR;
    }

    /* AT MTA */
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                      gastAtClientTab[ucIndex].opId,
                                      ID_AT_MTA_BESTFREQ_QRY_REQ,
                                      VOS_NULL_PTR,
                                      0,
                                      I0_UEPS_PID_MTA);

    if (TAF_SUCCESS != ulResult)
    {
        AT_WARN_LOG("AT_QryBestFreqPara: send Msg fail.");
        return AT_ERROR;
    }

    /*  */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_BESTFREQ_QRY;

    return AT_WAIT_ASYNC_RETURN;
}

VOS_VOID Show_Time(MODEM_ID_ENUM_UINT16 enModemId)
{
    AT_MODEM_NET_CTX_STRU              *pstNetCtx = VOS_NULL_PTR;

    pstNetCtx = AT_GetModemNetCtxAddrFromModemId(enModemId);

    (VOS_VOID)vos_printf("\r\nTime:\r\n");
    (VOS_VOID)vos_printf("ucIeFlg: %d\r\n",pstNetCtx->stTimeInfo.ucIeFlg);
    (VOS_VOID)vos_printf("cLocalTimeZone: %d\r\n",pstNetCtx->stTimeInfo.cLocalTimeZone);
    (VOS_VOID)vos_printf("ucDST: %d\r\n",pstNetCtx->stTimeInfo.ucDST);
    (VOS_VOID)vos_printf("ucLSAID: %d\r\n",pstNetCtx->stTimeInfo.ucLSAID);
    (VOS_VOID)vos_printf("cTimeZone: %d\r\n",pstNetCtx->stTimeInfo.stUniversalTimeandLocalTimeZone.cTimeZone);
    (VOS_VOID)vos_printf("ucYear: %d\r\n",pstNetCtx->stTimeInfo.stUniversalTimeandLocalTimeZone.ucYear);
    (VOS_VOID)vos_printf("ucMonth: %d\r\n",pstNetCtx->stTimeInfo.stUniversalTimeandLocalTimeZone.ucMonth);
    (VOS_VOID)vos_printf("ucDay: %d\r\n",pstNetCtx->stTimeInfo.stUniversalTimeandLocalTimeZone.ucDay);
    (VOS_VOID)vos_printf("ucHour: %d\r\n",pstNetCtx->stTimeInfo.stUniversalTimeandLocalTimeZone.ucHour);
    (VOS_VOID)vos_printf("ucMinute: %d\r\n",pstNetCtx->stTimeInfo.stUniversalTimeandLocalTimeZone.ucMinute);
    (VOS_VOID)vos_printf("ucSecond: %d\r\n",pstNetCtx->stTimeInfo.stUniversalTimeandLocalTimeZone.ucSecond);

    return;
}
/*****************************************************************************
     : AT_QryCclkPara
   : 
   : 
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 20141118
           : j00174725
       : 
*****************************************************************************/
VOS_UINT32 AT_QryCclkPara(VOS_UINT8 ucIndex)
{
    AT_MODEM_NET_CTX_STRU              *pstNetCtx = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_INT8                            cTimeZone;

    enModemId = MODEM_ID_0;
    cTimeZone = AT_INVALID_TZ_VALUE;

    ulRslt = AT_GetModemIdFromClient(ucIndex, &enModemId);

    if (VOS_OK != ulRslt)
    {
        AT_ERR_LOG("AT_QryCclkPara: Get modem id fail.");
        return AT_ERROR;
    }

    pstNetCtx = AT_GetModemNetCtxAddrFromModemId(enModemId);

    /*: +cclk: "yy/mm/dd,hh:mm:ss(+/-)zz" */
    if (NAS_MM_INFO_IE_UTLTZ == (pstNetCtx->stTimeInfo.ucIeFlg & NAS_MM_INFO_IE_UTLTZ))
    {
        /*  */
        cTimeZone   = pstNetCtx->stTimeInfo.stUniversalTimeandLocalTimeZone.cTimeZone;

        /*  Local time zone, Local time zone */
        if (NAS_MM_INFO_IE_LTZ == (pstNetCtx->stTimeInfo.ucIeFlg & NAS_MM_INFO_IE_LTZ))
        {
            cTimeZone   = pstNetCtx->stTimeInfo.cLocalTimeZone;
        }

        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                            "%s: \"%02d/%02d/%02d,%02d:%02d:%2d",
                                            g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                            pstNetCtx->stTimeInfo.stUniversalTimeandLocalTimeZone.ucYear,
                                            pstNetCtx->stTimeInfo.stUniversalTimeandLocalTimeZone.ucMonth,
                                            pstNetCtx->stTimeInfo.stUniversalTimeandLocalTimeZone.ucDay,
                                            pstNetCtx->stTimeInfo.stUniversalTimeandLocalTimeZone.ucHour,
                                            pstNetCtx->stTimeInfo.stUniversalTimeandLocalTimeZone.ucMinute,
                                            pstNetCtx->stTimeInfo.stUniversalTimeandLocalTimeZone.ucSecond);

        if (cTimeZone >= 0)
        {
            gstAtSendData.usBufLen += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                (VOS_CHAR *)pgucAtSndCodeAddr,
                (VOS_CHAR *)pgucAtSndCodeAddr + gstAtSendData.usBufLen,
                "+%02d\"",
                cTimeZone);

        }
        else
        {
            gstAtSendData.usBufLen += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                (VOS_CHAR *)pgucAtSndCodeAddr,
                (VOS_CHAR *)pgucAtSndCodeAddr + gstAtSendData.usBufLen,
                "-%02d\"",
                -cTimeZone);

        }

        return AT_OK;
    }

    return AT_CME_NO_NETWORK_SERVICE;
}

/*****************************************************************************
     : AT_QryCLocInfo
   : ^CLocinfoCDMA
   : ucIndex - 
   : 
     : 
   :
   :

       :
  1.       : 20141119
           : g00261581
       : AT
  2.       : 201519
           : K00902809
       : Added TAF_MMA_SetEOPlmnReq function to send request to MMA.
*****************************************************************************/
VOS_UINT32 AT_QryCLocInfo(VOS_UINT8 ucIndex)
{

    VOS_UINT32                          ulRet;

    /*  */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    /* Modified by k902809 for Iteration 11, 2015-3-25, begin */
    /* MMA */
    ulRet = TAF_MMA_QryCLocInfoReq(WUEPS_PID_AT,
                                   gastAtClientTab[ucIndex].usClientId,
                                   0);
    if (VOS_TRUE != ulRet)
    {
        return AT_ERROR;
    }
    /* Modified by k902809 for Iteration 11, Iteration 11 2015-3-25, end */

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CLOCINFO_QRY;

    return AT_WAIT_ASYNC_RETURN;

}


/*****************************************************************************
     : AT_QryEmcCallBack
   : emc callback
   : ucIndex - 
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 2015714
           : y00322978
       : 

*****************************************************************************/
VOS_UINT32 AT_QryEmcCallBack( VOS_UINT8 ucIndex  )
{
    VOS_UINT32                          ulRet;

    /*  */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    ulRet = TAF_MMA_QryCurrEmcCallBackMode(WUEPS_PID_AT,
                                           gastAtClientTab[ucIndex].usClientId,
                                           0);
    if (VOS_TRUE != ulRet)
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_EMCCBM_QRY;

    return AT_WAIT_ASYNC_RETURN;
}


/*****************************************************************************
     : AT_QryEncryptCallCap
   : 
   : VOS_UINT8 ulIndex
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 20151023
           : y00322978
       : 

*****************************************************************************/
VOS_UINT32 AT_QryEncryptCallCap( VOS_UINT8 ucIndex )
{
    VOS_UINT32                          ulRet;

    /*  */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    ulRet = TAF_XCALL_QryEncryptCallCap ( WUEPS_PID_AT,
                                          gastAtClientTab[ucIndex].usClientId,
                                          0);
    if (VOS_OK != ulRet)
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_ECCAP_QRY;

    return AT_WAIT_ASYNC_RETURN;
}
/*****************************************************************************
     : AT_QryPrivacyModePreferred
   : privay mode
   : VOS_UINT8 ucIndex
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 20151222
           : y00245242
       : 

*****************************************************************************/
VOS_UINT32 AT_QryPrivacyModePreferred(VOS_UINT8 ucIndex)
{
    /*  */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }


    if (VOS_OK == TAF_XCALL_QryPrivacyModePreferred(WUEPS_PID_AT,
                                                    gastAtClientTab[ucIndex].usClientId,
                                                    0))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CPMP_QRY;

        return AT_WAIT_ASYNC_RETURN;
    }

    return AT_ERROR;
}

/*****************************************************************************
     : AT_QryCFreqLockInfo
   : ^QryCFREQLOCK
   : ucIndex - 
   : 
     : 
   :
   :

       :
  1.       : 20141229
           : y00307564
       : AT
*****************************************************************************/
VOS_UINT32 AT_QryCFreqLockInfo(VOS_UINT8 ucIndex)
{

    /*  */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    if (VOS_TRUE ==  TAF_MMA_ProcCFreqLockQryReq(WUEPS_PID_AT,
                                                 gastAtClientTab[ucIndex].usClientId,
                                                 0))
    {
        /*  */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CFREQLOCK_QRY;
        return AT_WAIT_ASYNC_RETURN;    /*  */
    }
    else
    {
        return AT_ERROR;
    }

}
/*****************************************************************************
     : AT_QryCdmaCsqPara
   : AT^CDMACSQAT
   : VOS_UINT8                           ucIndex
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 20141225
           : m00312079
       : 

*****************************************************************************/
VOS_UINT32 AT_QryCdmaCsqPara(VOS_UINT8 ucIndex)
{

    /*  */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    if (VOS_TRUE == TAF_MMA_ProcCdmaCsqQryReq(WUEPS_PID_AT,
                                               gastAtClientTab[ucIndex].usClientId,
                                               0))
    {
        /*  */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CDMACSQ_QRY;
        return AT_WAIT_ASYNC_RETURN;    /*  */
    }
    else
    {
        return AT_ERROR;
    }

}

/*****************************************************************************
     : At_QryCbgPara
   : ^TTYMODE,
   : ucIndex - 
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 20150207
           : w00316404
       :
*****************************************************************************/
VOS_UINT32 AT_QryTTYModePara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulResult;

    if(AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    /* AT VC  */
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                      gastAtClientTab[ucIndex].opId,
                                      APP_VC_MSG_QRY_TTYMODE_REQ,
                                      VOS_NULL_PTR,
                                      0,
                                      I0_WUEPS_PID_VC);

    if (TAF_SUCCESS != ulResult)
    {
        AT_WARN_LOG("AT_QryTTYModePara: send Msg fail.");
        return AT_ERROR;
    }

    /*  */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_TTYMODE_READ;

    return AT_WAIT_ASYNC_RETURN;
}


/*****************************************************************************
     : AT_QryCtaPara
   : AT+CTAAT
   : VOS_UINT8                           ucIndex
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 2015420
           : c00299063
       : 
*****************************************************************************/
VOS_UINT32 AT_QryCtaPara(VOS_UINT8 ucIndex)
{

    /*  */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    /*  */
    if (VOS_OK != TAF_PS_GetCtaInfo(WUEPS_PID_AT,
                                    AT_PS_BuildExClientId(gastAtClientTab[ucIndex].usClientId),
                                    0))
    {
        return AT_ERROR;
    }

    /*  */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CTA_QRY;

    /*  */
    return AT_WAIT_ASYNC_RETURN;


}


/*****************************************************************************
     : At_QryRatRfSwitch
   : RF Profile Id
   : 
   : 
     : VOS_UINT32
   :
   :

       :
  1.     : 2015-01-04
         : z00301431
     : 

*****************************************************************************/
VOS_UINT32 At_QryRatRfSwitch(VOS_UINT8 ucIndex)
{
    NAS_NV_TRI_MODE_ENABLE_STRU  stTriModeEnableStru;
    NAS_NV_TRI_MODE_FEM_PROFILE_ID_STRU  stTriModeFemProfileIdStru;

    TAF_MEM_SET_S(&stTriModeEnableStru, sizeof(stTriModeEnableStru), 0x00, sizeof(stTriModeEnableStru));
    TAF_MEM_SET_S(&stTriModeFemProfileIdStru, sizeof(stTriModeFemProfileIdStru), 0x00, sizeof(stTriModeFemProfileIdStru));

    if(AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }


    /* NV */
    if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_TRI_MODE_ENABLE, &stTriModeEnableStru, sizeof(stTriModeEnableStru)))
    {
        AT_WARN_LOG("At_QryRatRfSwitch:read en_NV_Item_TRI_MODE_ENABLE failed");
        return AT_ERROR;
    }

    if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_TRI_MODE_FEM_PROFILE_ID, &stTriModeFemProfileIdStru, sizeof(stTriModeFemProfileIdStru)))
    {
        AT_WARN_LOG("At_QryRatRfSwitch:read en_NV_Item_TRI_MODE_FEM_PROFILE_ID failed");
        return AT_ERROR;
    }

    /* */
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                            "%s: %d,%u",
                                            g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                            stTriModeEnableStru.usEnable,
                                            stTriModeFemProfileIdStru.ulProfileId);
    return AT_OK;
}

/*****************************************************************************
     : AT_Qry1xChanPara
   : AT^1XCHANAT
   : VOS_UINT8                           ucIndex
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 20150516
           : z00316370
       : 

*****************************************************************************/
VOS_UINT32 AT_Qry1xChanPara(VOS_UINT8 ucIndex)
{

    /*  */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    if (VOS_TRUE ==  TAF_MMA_Proc1xChanQryReq(WUEPS_PID_AT,
                                              gastAtClientTab[ucIndex].usClientId,
                                              0))
    {
        /*  */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_1XCHAN_QRY;
        return AT_WAIT_ASYNC_RETURN;    /*  */
    }
    else
    {
        return AT_ERROR;
    }
}

/*****************************************************************************
     : AT_QryProRevInUse
   : AT^CVERAT
   : VOS_UINT8                           ucIndex
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 20150516
           : z00316370
       : 

*****************************************************************************/
VOS_UINT32 AT_QryProRevInUse(VOS_UINT8 ucIndex)
{

    /*  */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    if (VOS_TRUE ==  TAF_MMA_ProcProRevInUseQryReq(WUEPS_PID_AT,
                                                   gastAtClientTab[ucIndex].usClientId,
                                                   0))
    {
        /*  */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CVER_QRY;
        return AT_WAIT_ASYNC_RETURN;    /*  */
    }
    else
    {
        return AT_ERROR;
    }
}

/*****************************************************************************
     : AT_QryState
   : AT^GETSTAT
   : VOS_UINT8                           ucIndex
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 20150516
           : z00316370
       : 

*****************************************************************************/
VOS_UINT32 AT_QryCasState(VOS_UINT8 ucIndex)
{

    /*  */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    if (VOS_TRUE ==  TAF_MMA_ProcStateQryReq(WUEPS_PID_AT,
                                             gastAtClientTab[ucIndex].usClientId,
                                             0))
    {
        /*  */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_GETSTA_QRY;
        return AT_WAIT_ASYNC_RETURN;    /*  */
    }
    else
    {
        return AT_ERROR;
    }
}

/*****************************************************************************
     : AT_QryProGetEsn
   : AT^GETESNAT
   : VOS_UINT8                           ucIndex
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 20150516
           : z00316370
       : 

*****************************************************************************/
VOS_UINT32 AT_QryProGetEsn(VOS_UINT8 ucIndex)
{
    NV_ESN_MEID_STRU                    stEsnMeId;
    VOS_INT32                           slIndex;
    VOS_UINT32                          ulEsn;

    ulEsn = 0;
    TAF_MEM_SET_S(&stEsnMeId, sizeof(stEsnMeId), 0x00, sizeof(NV_ESN_MEID_STRU));

    /*  */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    /* en_NV_Item_ESN_MEID */
    if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_ESN_MEID, &stEsnMeId, sizeof(NV_ESN_MEID_STRU)))
    {
        AT_WARN_LOG("AT_QryProGetEsn:Read Nvim Failed");
        return AT_ERROR;
    }

    /* 0 ??? */
    if ((ESN_ME_ENABLE_FLAG   == stEsnMeId.enEsnMeIDFlag)
     || (ESN_MEID_ENABLE_BOTH == stEsnMeId.enEsnMeIDFlag))
    {
        /* Read from high to low */
        for (slIndex = PS_MIN(stEsnMeId.aucEsn[0], sizeof(stEsnMeId.aucEsn) - 1); slIndex > 0; slIndex--)
        {
            /* Update the current value */
            ulEsn <<= sizeof(stEsnMeId.aucEsn[0]) * 8;

            /* Add lower bits */
            ulEsn |= stEsnMeId.aucEsn[slIndex];
        }

        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        "%s: %d",
                                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                        ulEsn);

    }
    else
    {
        AT_WARN_LOG("AT_QryProGetEsn: ESN is disabled");
    }

    return AT_OK;
}

/*****************************************************************************
     : AT_QryProGetMeid
   : AT^GETMEIDAT
   : VOS_UINT8                           ucIndex
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 20150516
           : z00316370
       : 

*****************************************************************************/
VOS_UINT32 AT_QryProGetMeid(VOS_UINT8 ucIndex)
{
    NV_ESN_MEID_STRU                    stEsnMeId;
    VOS_UINT8                           aucMeId[2*AT_MEID_OCTET_NUM + 1];

    TAF_MEM_SET_S(&stEsnMeId, sizeof(stEsnMeId), 0x00, sizeof(NV_ESN_MEID_STRU));

    /*  */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    /* en_NV_Item_ESN_MEID */
    if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_ESN_MEID, &stEsnMeId, sizeof(NV_ESN_MEID_STRU)))
    {
        AT_WARN_LOG("AT_QryProGetMeid:Read Nvim Failed");
        return AT_ERROR;
    }

    /* 0 ??? */
    if ((MEID_ME_ENABLE_FLAG  == stEsnMeId.enEsnMeIDFlag)
     || (ESN_MEID_ENABLE_BOTH == stEsnMeId.enEsnMeIDFlag))
    {
        AT_Hex2Ascii_Revers(&(stEsnMeId.aucMeID[1]), AT_MEID_OCTET_NUM, aucMeId);
        aucMeId[2*AT_MEID_OCTET_NUM] = '\0';

        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        "%s: %s%s",
                                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                        aucMeId,
                                                        gaucAtCrLf);

    }
    else
    {
        AT_WARN_LOG("AT_QryProGetMeid: MEID is disabled");
    }

    return AT_OK;
}

/*****************************************************************************
     : AT_QryHighVer
   : AT^CHIGHVERAT
   : VOS_UINT8                           ucIndex
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 20150516
           : z00316370
       : 

*****************************************************************************/
VOS_UINT32 AT_QryHighVer(VOS_UINT8 ucIndex)
{

    /*  */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    if (VOS_TRUE ==  TAF_MMA_ProcCHVerQryReq(WUEPS_PID_AT,
                                             gastAtClientTab[ucIndex].usClientId,
                                             0))
    {
        /*  */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CHIGHVER_QRY;
        return AT_WAIT_ASYNC_RETURN;    /*  */
    }
    else
    {
        return AT_ERROR;
    }
}
/*****************************************************************************
     : AT_QryCgmtuPara
   : MTU
   : VOS_UINT8 ucIndex
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 2015529
           : g00261581
       : 

*****************************************************************************/
VOS_UINT32 AT_QryCgmtuPara(VOS_UINT8 ucIndex)
{

    /*  */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    /*  */
    if (VOS_OK != TAF_PS_GetCgmtuInfo(WUEPS_PID_AT,
                                      AT_PS_BuildExClientId(gastAtClientTab[ucIndex].usClientId),
                                      0))
    {
        return AT_ERROR;
    }

    /*  */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGMTU_READ;

    /*  */
    return AT_WAIT_ASYNC_RETURN;

}

/*****************************************************************************
     : At_QryTransMode
   : ^TRANSMODE
   : ucIndex - 
   : 
     : AT_XXX
   :
   :

       :
  1.       : 20150730
           : lwx277467
       : 
*****************************************************************************/
VOS_UINT32 AT_QryTransModePara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulResult;

    /*  */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    /* */
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                      gastAtClientTab[ucIndex].opId,
                                      ID_AT_MTA_TRANSMODE_QRY_REQ,
                                      VOS_NULL_PTR,
                                      0,
                                      I0_UEPS_PID_MTA);

    if (TAF_SUCCESS != ulResult)
    {
        AT_WARN_LOG("AT_QryTransModePara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /*  */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_TRANSMODE_READ;

    return AT_WAIT_ASYNC_RETURN;
}


/*****************************************************************************
     : AT_QryCdmaDormTimerVal
   : Dormant tiemr val
   : VOS_UINT8     ucIndex
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 20150814
           : y00314741
       : 

*****************************************************************************/
VOS_UINT32 AT_QryCdmaDormTimerVal(VOS_UINT8 ucIndex)
{

    /*  */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    /*  */
    if (VOS_OK != TAF_PS_ProcCdmaDormTimerQryReq(WUEPS_PID_AT,
                                                 AT_PS_BuildExClientId(gastAtClientTab[ucIndex].usClientId),
                                                 0))
    {
        return AT_ERROR;
    }

    /*  */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_DORMTIMER_QRY;

    /*  */
    return AT_WAIT_ASYNC_RETURN;

}


/*****************************************************************************
     : AT_QryMccFreqPara
   : 
   : ucIndex
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 20151009
           : l00289540
       : 

*****************************************************************************/
VOS_UINT32 AT_QryMccFreqPara(
    VOS_UINT8                           ucIndex
)
{
    AT_CSS_MCC_VERSION_INFO_REQ_STRU   *pstMsg = VOS_NULL_PTR;

    /*  */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        AT_ERR_LOG("AT_QryMccFreqPara: Invalid Cmd Type");

        return AT_ERROR;
    }

    /* Allocating memory for message */
    pstMsg = (AT_CSS_MCC_VERSION_INFO_REQ_STRU *)AT_ALLOC_MSG_WITH_HDR(sizeof(AT_CSS_MCC_VERSION_INFO_REQ_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        AT_ERR_LOG("AT_QryMccFreqPara: Mem Alloc failed");

        return AT_ERROR;
    }

    TAF_MEM_SET_S( ((VOS_UINT8 *)pstMsg + VOS_MSG_HEAD_LENGTH),
                (VOS_SIZE_T)(sizeof(AT_CSS_MCC_VERSION_INFO_REQ_STRU) - VOS_MSG_HEAD_LENGTH),
                0x00,
                (VOS_SIZE_T)(sizeof(AT_CSS_MCC_VERSION_INFO_REQ_STRU) - VOS_MSG_HEAD_LENGTH) );

    /*  */
    AT_CFG_MSG_HDR(pstMsg, PS_PID_CSS, ID_AT_CSS_MCC_VERSION_INFO_REQ);

    pstMsg->usClientId          = gastAtClientTab[ucIndex].usClientId;

    AT_SEND_MSG(pstMsg);

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_MCCFREQ_QRY;

    return AT_WAIT_ASYNC_RETURN;
}

/*****************************************************************************
     : At_QryUECenterPara
   : +CEUS?
   : ucIndex - 
   : 
     : AT_XXX
   :
   :

       :
  1.       : 20150730
           : lwx277467
       : 
*****************************************************************************/
VOS_UINT32 AT_QryUECenterPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulResult;

    /*  */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    /* */
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                      gastAtClientTab[ucIndex].opId,
                                      ID_AT_MTA_UE_CENTER_QRY_REQ,
                                      VOS_NULL_PTR,
                                      0,
                                      I0_UEPS_PID_MTA);

    if (TAF_SUCCESS != ulResult)
    {
        AT_WARN_LOG("At_QryUEModePara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /*  */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_UE_CENTER_QRY;

    return AT_WAIT_ASYNC_RETURN;
}


/*****************************************************************************
     : AT_QryHdrCsqPara
   : AT^HDRCSQ?AT
   : VOS_UINT8                           ucIndex
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 20151022
           : C00299064
       : 

*****************************************************************************/
VOS_UINT32 AT_QryHdrCsqPara(VOS_UINT8 ucIndex)
{

    /*  */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    if (VOS_TRUE == TAF_MMA_ProcHdrCsqQryReq(WUEPS_PID_AT,
                                               gastAtClientTab[ucIndex].usClientId,
                                               0))
    {
        /*  */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_HDR_CSQ_QRY;
        return AT_WAIT_ASYNC_RETURN;    /*  */
    }

    return AT_ERROR;


}


/*****************************************************************************
     : AT_QryCurrSidNid
   : sid nid
   : ucIndex - 
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 20151023
           : f00279542
       : 

*****************************************************************************/
VOS_UINT32 AT_QryCurrSidNid(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRet;

    /*  */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    ulRet = TAF_MMA_QryCurrSidNid(WUEPS_PID_AT,
                                  gastAtClientTab[ucIndex].usClientId,
                                  0);
    if (VOS_TRUE != ulRet)
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CSNID_QRY;

    return AT_WAIT_ASYNC_RETURN;
}

/*****************************************************************************
     : AT_QryCtRoamInfo
   : SID/MCC
   : VOS_UINT8 ucIndex
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 2016120
           : w00242748
       : 

*****************************************************************************/
VOS_UINT32 AT_QryCtRoamInfo(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRet;

    /*  */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    ulRet = TAF_MMA_QryCtRoamInfo(WUEPS_PID_AT,
                                  gastAtClientTab[ucIndex].usClientId,
                                  0);
    if (VOS_TRUE != ulRet)
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CTROAMINFO_QRY;

    return AT_WAIT_ASYNC_RETURN;
}
/*****************************************************************************
     : AT_QryPRLID
   : PRLID ,MLPL version id, MSPL version id
   : VOS_UINT8 ucIndex
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 2016324
           : l00359089
       : 

*****************************************************************************/
VOS_UINT32 AT_QryPRLID(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRet;

    /*  */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    ulRet = TAF_MMA_QryPrlIdInfo(WUEPS_PID_AT,
                                 gastAtClientTab[ucIndex].usClientId,
                                 0);
    if (VOS_TRUE != ulRet)
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_PRLID_QRY;

    return AT_WAIT_ASYNC_RETURN;
}



/*****************************************************************************
     : AT_QryAfcClkInfo
   : 
   : ucIndex - 
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 20151224
           : c00299064
       : 

*****************************************************************************/
VOS_UINT32 AT_QryAfcClkInfo(VOS_UINT8 ucIndex)
{

    VOS_UINT32                          ulRet;

    /*  */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    ulRet = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   ID_AT_MTA_QRY_AFC_CLK_FREQ_XOCOEF_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_UEPS_PID_MTA);
    if (TAF_SUCCESS != ulRet)
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_AFCCLKINFO_QRY;

    return AT_WAIT_ASYNC_RETURN;
}


/*****************************************************************************
     : AT_QryFratIgnitionInfo
   : FRAT IGNITION 
   : VOS_UINT8 ucIndex
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 2016420
           : c00318887
       : 

*****************************************************************************/
VOS_UINT32 AT_QryFratIgnitionInfo(VOS_UINT8 ucIndex)
{

    VOS_UINT32                          ulRet;

    /*  */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    ulRet = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   ID_AT_MTA_FRAT_IGNITION_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_UEPS_PID_MTA);
    if (TAF_SUCCESS != ulRet)
    {
        AT_WARN_LOG("AT_QryFratIgnitionInfo: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_FRATIGNITION_QRY;

    return AT_WAIT_ASYNC_RETURN;
}

/*****************************************************************************
     : AT_QryPacspPara
   : ENS
   : VOS_UINT8 ucIndex
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 2016109
           : n00269697
       : 

*****************************************************************************/
VOS_UINT32 AT_QryPacspPara(VOS_UINT8 ucIndex)
{
    /*  */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if (VOS_TRUE != TAF_MMA_QryPacspReq(WUEPS_PID_AT, gastAtClientTab[ucIndex].usClientId, 0))
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_PACSP_QRY;

    /*  */
    return AT_WAIT_ASYNC_RETURN;
}


/*****************************************************************************
     : AT_QryNoCardMode
   : AT^CNOCARDMODEAT
   : VOS_UINT8                           ucIndex
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 20160503
           : z00316370
       : 

*****************************************************************************/
VOS_UINT32 AT_QryNoCardMode(VOS_UINT8 ucIndex)
{
    CNAS_NVIM_NO_CARD_MODE_CFG_STRU     stNoCardModeCfg = {0};

    TAF_MEM_SET_S(&stNoCardModeCfg, sizeof(stNoCardModeCfg), 0x00, sizeof(stNoCardModeCfg));

    /*  */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    /* en_NV_Item_NO_CARD_MODE_CFG */
    if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_NO_CARD_MODE_CFG, &stNoCardModeCfg, sizeof(stNoCardModeCfg)))
    {
        AT_WARN_LOG("AT_QryNoCardMode:Read Nvim Failed");
        return AT_ERROR;
    }

    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                     "%s: %d",
                                                     g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                     stNoCardModeCfg.ulEnableFlag);

    return AT_OK;
}

/*****************************************************************************
     : AT_QryRatCombinedMode
   :  AT^RATCOMBINEDMODE?
   : VOS_UINT8 ucIndex
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 2016718
           : l00359089
       : 

*****************************************************************************/
VOS_UINT32 AT_QryRatCombinedMode(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRet;

    /*  */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    ulRet = TAF_MMA_QryRatCombinedMode(WUEPS_PID_AT,
                                       gastAtClientTab[ucIndex].usClientId,
                                       0);
    if (VOS_TRUE != ulRet)
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_RATCOMBINEDMODE_QRY;

    return AT_WAIT_ASYNC_RETURN;
}


/*****************************************************************************
     : AT_QryFclassPara
   : +FCLASS?
   : ucIndex --- 
   : 
     : AT_XXX  --- ATC
   :
   :

       :
  1.       : 2016711
           : l00373346
       : 

*****************************************************************************/
VOS_UINT32 AT_QryFclassPara(VOS_UINT8 ucIndex)
{
    AT_WARN_LOG("AT_QryFclassPara: Not support this command!");
    (VOS_VOID)ucIndex;
    return AT_ERROR;
}

/*****************************************************************************
     : AT_QryGciPara
   : +GCI?
   : ucIndex --- 
   : 
     : AT_XXX  --- ATC
   :
   :

       :
  1.       : 2016711
           : l00373346
       : 

*****************************************************************************/
VOS_UINT32 AT_QryGciPara(VOS_UINT8 ucIndex)
{
    AT_WARN_LOG("AT_QryGciPara: Not support this command!");
    (VOS_VOID)ucIndex;
    return AT_ERROR;
}

/*****************************************************************************
     : AT_QryRsrp
   : 
   : ucIndex - 
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 20170117
           : wx270776
       : 

*****************************************************************************/
VOS_UINT32 AT_QryRsrp(VOS_UINT8 ucIndex)
{

    VOS_UINT32                          ulRet;
    AT_MTA_RS_INFO_QRY_REQ_STRU         stRsInfoQryReq;

    stRsInfoQryReq.enRsInfoType = AT_MTA_RSRP_TYPE;

    /*  */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    ulRet = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   ID_AT_MTA_RS_INFO_QRY_REQ,
                                   &stRsInfoQryReq,
                                   (VOS_UINT32)sizeof(AT_MTA_RS_INFO_QRY_REQ_STRU),
                                   I0_UEPS_PID_MTA);
    if (TAF_SUCCESS != ulRet)
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_RSRP_QRY;

    return AT_WAIT_ASYNC_RETURN;
}

/*****************************************************************************
     : AT_QryRsrq
   : 
   : ucIndex - 
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 20170117
           : wx270776
       : 

*****************************************************************************/
VOS_UINT32 AT_QryRsrq(VOS_UINT8 ucIndex)
{

    VOS_UINT32                          ulRet;
    AT_MTA_RS_INFO_QRY_REQ_STRU         stRsInfoQryReq;

    stRsInfoQryReq.enRsInfoType = AT_MTA_RSRQ_TYPE;

    /*  */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    ulRet = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   ID_AT_MTA_RS_INFO_QRY_REQ,
                                   &stRsInfoQryReq,
                                   (VOS_UINT32)sizeof(AT_MTA_RS_INFO_QRY_REQ_STRU),
                                   I0_UEPS_PID_MTA);
    if (TAF_SUCCESS != ulRet)
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_RSRQ_QRY;

    return AT_WAIT_ASYNC_RETURN;
}


