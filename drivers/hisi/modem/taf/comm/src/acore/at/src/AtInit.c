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
#include "AtInit.h"

/* PSPS */
#include "AtDataProc.h"
#include "AcpuReset.h"
#include "msp_nvim.h"
#include "msp_nv_id.h"
#include "msp_nv_def.h"
#include "LPsNvInterface.h"
#include "at_lte_common.h"
#include "GasNvInterface.h"
#include "NasNvInterface.h"
#include "TafNvInterface.h"
#include "product_config.h"
#include "mdrv.h"
#include "msp_diag_comm.h"
#include "GuNasLogFilter.h"
#include "PsLogFilterInterface.h"





/*****************************************************************************
    .C
*****************************************************************************/
#define    THIS_FILE_ID                 PS_FILE_ID_AT_INIT_C


/*****************************************************************************
  2 
*****************************************************************************/


/*****************************************************************************
  3 
*****************************************************************************/

/*****************************************************************************
     : AT_ReadPlatformNV
   : NV
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20121227
           : z00220246
       : DSDA Phase II:

*****************************************************************************/
VOS_VOID AT_ReadPlatformNV(VOS_VOID)
{
    MODEM_ID_ENUM_UINT16                enModemID;
    PLATAFORM_RAT_CAPABILITY_STRU       stPlatFormRat;
    VOS_UINT8                           ucRatIndex;
    AT_MODEM_SPT_RAT_STRU              *pstAtSptRatList = VOS_NULL_PTR;

    TAF_MEM_SET_S(&stPlatFormRat, sizeof(stPlatFormRat), 0x00, sizeof(PLATAFORM_RAT_CAPABILITY_STRU));

    for (enModemID = 0; enModemID < MODEM_ID_BUTT; enModemID++)
    {
        pstAtSptRatList = AT_GetSptRatFromModemId(enModemID);

        /* NV */
        if(NV_OK == NV_ReadEx(enModemID, en_NV_Item_Platform_RAT_CAP, &stPlatFormRat,
                              sizeof(PLATAFORM_RAT_CAPABILITY_STRU)))
        {
            pstAtSptRatList->ucPlatformSptGsm        = VOS_FALSE;
            pstAtSptRatList->ucPlatformSptWcdma      = VOS_FALSE;
            pstAtSptRatList->ucPlatformSptLte        = VOS_FALSE;
            pstAtSptRatList->ucPlatformSptUtralTDD   = VOS_FALSE;

            for (ucRatIndex = 0; ucRatIndex < stPlatFormRat.usRatNum; ucRatIndex++)
            {
                /* LTE */
                if (PLATFORM_RAT_LTE == stPlatFormRat.aenRatList[ucRatIndex])
                {
                    pstAtSptRatList->ucPlatformSptLte = VOS_TRUE;
                }
                /* WCDMA */
                if (PLATFORM_RAT_WCDMA == stPlatFormRat.aenRatList[ucRatIndex])
                {
                    pstAtSptRatList->ucPlatformSptWcdma = VOS_TRUE;
                }

                /* TDS*/
                if (PLATFORM_RAT_TDS == stPlatFormRat.aenRatList[ucRatIndex])
                {
                    pstAtSptRatList->ucPlatformSptUtralTDD = VOS_TRUE;
                }
                /* GSM */
                if (PLATFORM_RAT_GSM == stPlatFormRat.aenRatList[ucRatIndex])
                {
                    pstAtSptRatList->ucPlatformSptGsm = VOS_TRUE;
                }
            }
        }
    }

    return;
}

/*****************************************************************************
     : AT_ReadClientConfigNV
   : en_NV_Item_AT_CLIENT_CFGmodem
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20121228
           : l00227485
       : DSDA PhaseII: 
  2.       : 20140423
           : f00179208
       : DTS2014042304605
*****************************************************************************/
VOS_VOID AT_ReadClientConfigNV(VOS_VOID)
{
    TAF_AT_NVIM_AT_CLIENT_CFG_STRU      stAtClientCfg;
    AT_CLINET_CONFIG_DESC_STRU         *pstCfgDesc;
    AT_CLIENT_CONFIGURATION_STRU       *pstClientCfg;
    AT_CLIENT_CFG_MAP_TAB_STRU         *pstCfgMapTbl;
    VOS_UINT8                           i;

    TAF_MEM_SET_S(&stAtClientCfg, sizeof(stAtClientCfg), 0x00, sizeof(TAF_AT_NVIM_AT_CLIENT_CFG_STRU));

    /* NVen_NV_Item_AT_CLIENT_CONFIG
       aucAtClientConfig[Index]
       Index = 0 -- AT_CLIENT_TAB_PCUI_INDEX
       Index = 1 -- AT_CLIENT_TAB_CTRL_INDEX
       ......
       index
       aucAtClientConfig[Index]
       BIT0-BIT1clientModemId:00:modem0 01:modem1
       BIT2client:0: 1:
    */
    if (VOS_OK != NV_ReadEx(MODEM_ID_0,
                            en_NV_Item_AT_CLIENT_CFG,
                            &stAtClientCfg,
                            sizeof(TAF_AT_NVIM_AT_CLIENT_CFG_STRU)))
    {
        return;
    }

    pstCfgDesc = (AT_CLINET_CONFIG_DESC_STRU *)&(stAtClientCfg.aucAtClientConfig[0]);

    for (i = 0; i < AT_GET_CLIENT_CFG_TAB_LEN(); i++)
    {
        pstCfgMapTbl = AT_GetClientCfgMapTbl(i);
        pstClientCfg = AT_GetClientConfig(pstCfgMapTbl->enClientId);

        pstClientCfg->enModemId   = pstCfgDesc[pstCfgMapTbl->enNvIndex].ucModemId;
        pstClientCfg->ucReportFlg = pstCfgDesc[pstCfgMapTbl->enNvIndex].ucReportFlg;
    }

    return;
}

/*****************************************************************************
     : AT_GetCpmsMtMem
   : CPMS<MT>
   : 
   : MODEM_ID_ENUM_UINT16                enModemId
             MN_MSG_MEM_STORE_ENUM_U8           *penSmMemStore  CPMS<MT>
     : VOS_VOID
   :
   :

       :
  1.       : 20130306
           : f00179208
       : 
  2.       : 20130520
           : m00217266
       : nv
*****************************************************************************/
VOS_VOID AT_GetCpmsMtMem(
    MODEM_ID_ENUM_UINT16                enModemId,
    MN_MSG_MEM_STORE_ENUM_U8           *penSmMemStore
)
{
    VOS_UINT32                          ulRet;
    TAF_NVIM_SMS_SERVICE_PARA_STRU      stSmsServicePara;
    /* NV
       VOS_TRUE        NV
       VOS_FALSE       NVSM */
    VOS_BOOL                            bSmMemEnable;
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;

    TAF_MEM_SET_S(&stSmsServicePara, sizeof(stSmsServicePara), 0x00, sizeof(TAF_NVIM_SMS_SERVICE_PARA_STRU));

    *penSmMemStore = MN_MSG_MEM_STORE_SIM;

    ulRet = NV_ReadEx(enModemId, en_NV_Item_SMS_SERVICE_Para, &stSmsServicePara, MN_MSG_SRV_PARAM_LEN);
    if (NV_OK != ulRet)
    {
        AT_ERR_LOG("AT_GetCpmsMtMem: Read Service Parm From Nvim Failed");
        return;
    }

    bSmMemEnable                  = (stSmsServicePara.aucSmsServicePara)[MN_MSG_SRV_SM_MEM_ENABLE_OFFSET];

    pstSmsCtx                     = AT_GetModemSmsCtxAddrFromModemId(enModemId);

    if (MN_MSG_ME_STORAGE_ENABLE == pstSmsCtx->enMsgMeStorageStatus)
    {
        if (VOS_TRUE == bSmMemEnable)
        {
            *penSmMemStore = (stSmsServicePara.aucSmsServicePara)[MN_MSG_SRV_RCV_SM_MEM_STORE_OFFSET];
        }
    }

    return;
}

/*****************************************************************************
     : AT_SendDomainNvimToProto
   : NVIM
   :
   : 
     : 
   :
   :

       :
  1.       : 20130306
           : f00179208
       : 

*****************************************************************************/
AT_CGSMS_SEND_DOMAIN_ENUM_U8 AT_SendDomainNvimToProto(
    VOS_UINT32                           ulNvimSendDomain
)
{
    AT_CGSMS_SEND_DOMAIN_ENUM_U8        enProtoSendDomain;

    if (AT_NV_SMS_DOMAIN_PS_PREFERRED == ulNvimSendDomain)
    {
        enProtoSendDomain = MN_MSG_SEND_DOMAIN_PS_PREFERRED;
    }
    else if ((AT_NV_SMS_DOMAIN_PS_ONLY == ulNvimSendDomain))
    {
        enProtoSendDomain = MN_MSG_SEND_DOMAIN_PS;
    }
    else if (AT_NV_SMS_DOMAIN_CS_ONLY == ulNvimSendDomain)
    {
        enProtoSendDomain = MN_MSG_SEND_DOMAIN_CS;
    }
    else
    {
        enProtoSendDomain = MN_MSG_SEND_DOMAIN_CS_PREFERRED;
    }

    return enProtoSendDomain;
}

/*****************************************************************************
     : AT_ReadSmsSendDomainNV
   : SMSNV
   : VOS_VOID
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20130306
           : f00179208
       : 
  2.       : 20130520
           : m00217266
       : nv
*****************************************************************************/
VOS_VOID AT_ReadSmsSendDomainNV(VOS_VOID)
{
    VOS_UINT32                          ulRet;
    AT_NVIM_SEND_DOMAIN_STRU            stSendDomain;
    MODEM_ID_ENUM_UINT16                enModemId;
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;
    VOS_UINT32                          ulLength;

    for (enModemId = 0; enModemId < MODEM_ID_BUTT; enModemId++)
    {
        pstSmsCtx = AT_GetModemSmsCtxAddrFromModemId(enModemId);

        /* ,NVIM, */
        TAF_MEM_SET_S(&stSendDomain, sizeof(stSendDomain), 0x00, sizeof(stSendDomain));
        ulLength = 0;
        (VOS_VOID)NV_GetLength(en_NV_Item_SMS_SEND_DOMAIN, &ulLength);
        ulRet = NV_ReadEx(enModemId, en_NV_Item_SMS_SEND_DOMAIN, &stSendDomain, ulLength);
        if ( (NV_OK == ulRet)
          && (VOS_TRUE == stSendDomain.ucActFlg))
        {
            /* NVIM
               NVIM, */
            pstSmsCtx->stCgsmsSendDomain.ucActFlg     = VOS_TRUE;
            pstSmsCtx->stCgsmsSendDomain.enSendDomain = AT_SendDomainNvimToProto((VOS_UINT32)stSendDomain.ucSendDomain);
        }
    }
    return;
}

/*****************************************************************************
     : AT_ReadSmsMeStorageInfoNV
   : ME
   : VOS_VOID
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20130306
           : f00179208
       : 

*****************************************************************************/
VOS_VOID AT_ReadSmsMeStorageInfoNV(VOS_VOID)
{
    VOS_UINT32                          ulRet;
    MN_MSG_ME_STORAGE_PARM_STRU         stMeStorageParm;
    MODEM_ID_ENUM_UINT16                enModemId;
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;

    for (enModemId = 0; enModemId < MODEM_ID_BUTT; enModemId++)
    {
        pstSmsCtx = AT_GetModemSmsCtxAddrFromModemId(enModemId);

        stMeStorageParm.enMeStorageStatus   = MN_MSG_ME_STORAGE_DISABLE;
        stMeStorageParm.usMeStorageNum      = 0;

        /* ME */
        ulRet = NV_ReadEx(enModemId, en_NV_Item_Sms_Me_Storage_Info, &stMeStorageParm, sizeof(stMeStorageParm));
        if (NV_OK == ulRet)
        {
            pstSmsCtx->enMsgMeStorageStatus = stMeStorageParm.enMeStorageStatus;
        }

        /* */
        AT_GetCpmsMtMem(enModemId, &(pstSmsCtx->stCpmsInfo.stRcvPath.enSmMemStore));
        pstSmsCtx->stCpmsInfo.stRcvPath.enStaRptMemStore = pstSmsCtx->stCpmsInfo.stRcvPath.enSmMemStore;
    }

    return;
}

/*****************************************************************************
     : AT_ReadSmsClass0TailorNV
   : CLASS0
   : VOS_VOID
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20130306
           : f00179208
       : 
  2.       : 20130520
           : m00217266
       : nv
*****************************************************************************/
VOS_VOID AT_ReadSmsClass0TailorNV(VOS_VOID)
{
    VOS_UINT32                          ulRet;
    MN_MSG_NVIM_CLASS0_TAILOR_STRU      stClass0Tailor;
    VOS_UINT32                          ulLength;

    ulLength                            = 0;
    stClass0Tailor.ucActFlg             = MN_MSG_NVIM_ITEM_INACTIVE;
    stClass0Tailor.enClass0Tailor       = MN_MSG_CLASS0_DEF;

    (VOS_VOID)NV_GetLength(en_NV_Item_SMS_CLASS0_TAILOR, &ulLength);
    /* CLASS0 */
    ulRet = NV_ReadEx(MODEM_ID_0, en_NV_Item_SMS_CLASS0_TAILOR, &stClass0Tailor, ulLength);
    if ( (NV_OK == ulRet)
      && (MN_MSG_NVIM_ITEM_ACTIVE == stClass0Tailor.ucActFlg))
    {
        g_enClass0Tailor = stClass0Tailor.enClass0Tailor;
    }
    else
    {
        g_enClass0Tailor = MN_MSG_CLASS0_DEF;
    }

    return;
}

/*****************************************************************************
     : AT_ReadSmsClosePathNV
   : close pathNV
   : VOS_VOID
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 2013717
           : z00234330
       : DTS2013052304352
  2.       : 20131008
           : j00174725
       : TQE
*****************************************************************************/
VOS_VOID AT_ReadSmsClosePathNV(VOS_VOID)
{
    TAF_NVIM_SMS_CLOSE_PATH_CFG_STRU    stClosePath;
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT32                          ulRet;

    TAF_MEM_SET_S(&stClosePath, sizeof(stClosePath), 0x00, sizeof(stClosePath));

    for (enModemId = 0; enModemId < MODEM_ID_BUTT; enModemId++)
    {
        pstSmsCtx = AT_GetModemSmsCtxAddrFromModemId(enModemId);

        /* ME */
        ulRet = NV_ReadEx(enModemId, en_NV_Item_SMS_Close_Path, &stClosePath, sizeof(stClosePath));
        if ( (NV_OK == ulRet)
           && (VOS_TRUE == stClosePath.ucNvimValid))
        {
            pstSmsCtx->ucLocalStoreFlg = stClosePath.ucSmsClosePathFlg;
        }
    }
}

/*****************************************************************************
     : AT_ReadMtCustomizeInfo
   : 
   : VOS_VOID
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20150114
           : x00182239
       : 
*****************************************************************************/
VOS_VOID AT_ReadMtCustomizeInfo(VOS_VOID)
{
    VOS_UINT32                          ulRet;
    MN_MSG_MT_CUSTOMIZE_INFO_STRU       stMtCustomize;
    MODEM_ID_ENUM_UINT16                enModemId;
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;

    TAF_MEM_SET_S(&stMtCustomize, (VOS_SIZE_T)sizeof(stMtCustomize), 0x00, (VOS_SIZE_T)sizeof(MN_MSG_MT_CUSTOMIZE_INFO_STRU));

    ulRet = NV_Read(en_NV_Item_SMS_MT_CUSTOMIZE_INFO,
                &stMtCustomize,
                sizeof(stMtCustomize));
    if (NV_OK != ulRet)
    {
        AT_INFO_LOG("AT_ReadMtCustomizeInfo: Fail to read ");
        return;
    }

    for (enModemId = 0; enModemId < MODEM_ID_BUTT; enModemId++)
    {
        pstSmsCtx = AT_GetModemSmsCtxAddrFromModemId(enModemId);

        if (MN_MSG_NVIM_ITEM_ACTIVE == stMtCustomize.ucActFlag)
        {
            pstSmsCtx->stSmMeFullCustomize.ucActFlg      = VOS_TRUE;
            pstSmsCtx->stSmMeFullCustomize.enMtCustomize = stMtCustomize.enMtCustomize;
        }
    }
    return;
}

/*****************************************************************************
     : AT_ReadPortBuffCfgNV
   : NV
   : VOS_VOID
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20131228
           : j00174725
       : HSUART PHASE III

  2.       : 2014214
           : j00174725
       : TQE
*****************************************************************************/
VOS_VOID AT_ReadPortBuffCfgNV(VOS_VOID)
{
    AT_COMM_CTX_STRU                   *pstCommCtx = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;
    TAF_NV_PORT_BUFF_CFG_STRU           stSmsBuffCfg;

    pstCommCtx = AT_GetCommCtxAddr();

    TAF_MEM_SET_S(&stSmsBuffCfg, sizeof(stSmsBuffCfg), 0x00, sizeof(stSmsBuffCfg));

    ulRet = NV_ReadEx(MODEM_ID_0, en_NV_Item_PORT_BUFF_CFG, &stSmsBuffCfg, sizeof(stSmsBuffCfg));

    if (NV_OK == ulRet)
    {
        if (stSmsBuffCfg.ucEnableFlg < AT_PORT_BUFF_BUTT)
        {
            pstCommCtx->stPortBuffCfg.enSmsBuffCfg = stSmsBuffCfg.ucEnableFlg;
        }
        else
        {
            pstCommCtx->stPortBuffCfg.enSmsBuffCfg = AT_PORT_BUFF_DISABLE;
        }
    }
    else
    {
        pstCommCtx->stPortBuffCfg.enSmsBuffCfg = AT_PORT_BUFF_DISABLE;
    }

    return;
}


/*****************************************************************************
     : AT_ReadSmsNV
   : SMSNV
   : VOS_VOID
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20130306
           : f00179208
       : 

*****************************************************************************/
VOS_VOID AT_ReadSmsNV(VOS_VOID)
{
    AT_ReadSmsSendDomainNV();

    AT_ReadSmsMeStorageInfoNV();

    AT_ReadSmsClass0TailorNV();

    AT_ReadSmsClosePathNV();


    AT_ReadMtCustomizeInfo();

    return;
}
/* Deleted by s00217060 for ATC, 2013-4-1, begin */
/* Deleted by s00217060 for ATC, 2013-4-1, end */

/*****************************************************************************
     : AT_ReadRoamCapaNV
   : NV
   : 
   : 
     : 
   :
   :

       :
  1.       : 20130306
           : f00179208
       : 
  2.       : 20130520
           : m00217266
       : nv
  3.       : 20131008
           : j00174725
       : TQE
*****************************************************************************/
VOS_VOID  AT_ReadRoamCapaNV(VOS_VOID)
{
    NAS_NVIM_ROAM_CFG_INFO_STRU         stRoamCfgInfo;
    MODEM_ID_ENUM_UINT16                enModemId;
    AT_MODEM_NET_CTX_STRU              *pstNetCtx = VOS_NULL_PTR;
    VOS_UINT32                          ulLength;

    ulLength = 0;
    TAF_MEM_SET_S(&stRoamCfgInfo, sizeof(stRoamCfgInfo), 0x00, sizeof(stRoamCfgInfo));

    for (enModemId = 0; enModemId < MODEM_ID_BUTT; enModemId++)
    {
        pstNetCtx = AT_GetModemNetCtxAddrFromModemId(enModemId);

        (VOS_VOID)NV_GetLength(en_NV_Item_Roam_Capa, &ulLength);
        if (NV_OK == NV_ReadEx(enModemId, en_NV_Item_Roam_Capa, &stRoamCfgInfo, ulLength))
        {
            if (stRoamCfgInfo.ucRoamFeatureFlg >1)
            {
                 pstNetCtx->ucRoamFeature = AT_ROAM_FEATURE_OFF;
            }
            else
            {
                pstNetCtx->ucRoamFeature = stRoamCfgInfo.ucRoamFeatureFlg;
            }
        }
        else
        {
            pstNetCtx->ucRoamFeature = AT_ROAM_FEATURE_OFF;
        }
    }
    return;
}

/*****************************************************************************
     : AT_ReadPrivacyFilterCfgNv
   : NvSMS
   : 
   : 
     : 
   :
   :

       :
  1.       : 20150917
           : h00313353
       : 
  2.       : 20160701
           : f00179208
       : :NV
*****************************************************************************/
VOS_VOID AT_ReadPrivacyFilterCfgNv(VOS_VOID)
{
    AT_MODEM_PRIVACY_FILTER_CTX_STRU   *pstFilterCtx = VOS_NULL_PTR;
    NAS_NV_PRIVACY_FILTER_CFG_STRU      stPrivacyFilterCfg;
    MODEM_ID_ENUM_UINT16                enModemId;

    /*  */
    TAF_MEM_SET_S(&stPrivacyFilterCfg, sizeof(stPrivacyFilterCfg), 0x00, sizeof(NAS_NV_PRIVACY_FILTER_CFG_STRU));

    for (enModemId = 0; enModemId < MODEM_ID_BUTT; enModemId++)
    {
        /* NV */
        if (NV_OK != NV_ReadEx(enModemId,
                               en_NV_Item_Privacy_Log_Filter_Cfg,
                               &stPrivacyFilterCfg,
                               sizeof(NAS_NV_PRIVACY_FILTER_CFG_STRU)))
        {
            stPrivacyFilterCfg.ucFilterEnableFlg = VOS_FALSE;
        }

        /* NV */
        if (VOS_TRUE == stPrivacyFilterCfg.ucFilterEnableFlg)
        {
            stPrivacyFilterCfg.ucFilterEnableFlg = VOS_TRUE;
        }

        pstFilterCtx = AT_GetModemPrivacyFilterCtxAddrFromModemId(enModemId);

        pstFilterCtx->ucFilterEnableFlg = stPrivacyFilterCfg.ucFilterEnableFlg;
    }

    return;
}

/*****************************************************************************
     : AT_ReadSystemAppConfigNV
   : NV
   : 
   : 
     : 
   :
   :

       :
  1.       : 20130306
           : f00179208
       : 
  2.       : 20130517
           : m00217266
       : nv
*****************************************************************************/
VOS_VOID  AT_ReadSystemAppConfigNV(VOS_VOID)
{
    VOS_UINT8                          *pucSystemAppConfig;
    NAS_NVIM_SYSTEM_APP_CONFIG_STRU     stSysAppConfig;
    VOS_UINT32                          ulLength;

    stSysAppConfig.usSysAppConfigType = SYSTEM_APP_BUTT;

    /* NV */
    pucSystemAppConfig                  = AT_GetSystemAppConfigAddr();
    ulLength                            = 0;

    (VOS_VOID)NV_GetLength(en_NV_Item_System_APP_Config, &ulLength);
    /* */
    if (VOS_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_System_APP_Config,&stSysAppConfig,ulLength))
    {
        *pucSystemAppConfig  = SYSTEM_APP_MP;
        return;
    }

    if ( SYSTEM_APP_ANDROID < stSysAppConfig.usSysAppConfigType)
    {
        *pucSystemAppConfig  = SYSTEM_APP_MP;
    }
    else
    {
        *pucSystemAppConfig  = (VOS_UINT8)stSysAppConfig.usSysAppConfigType;
    }

    return;

}

/*****************************************************************************
     : AT_ReadAtDislogPwdNV
   : DISLOGNV
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20130306
           : f00179208
       : 
  2.       : 20130517
           : m00217266
       : nv
*****************************************************************************/
VOS_VOID AT_ReadAtDislogPwdNV(VOS_VOID)
{
    VOS_UINT8                          *pucSystemAppConfig;
    TAF_AT_NVIM_DISLOG_PWD_NEW_STRU     stDislogPwdNew;

    /* D25  , NV,  */
    g_enATE5RightFlag = AT_E5_RIGHT_FLAG_NO;
    TAF_MEM_SET_S(&stDislogPwdNew, sizeof(stDislogPwdNew), 0x00, sizeof(stDislogPwdNew));

    /* NV */
    pucSystemAppConfig = AT_GetSystemAppConfigAddr();

    /* NVDISLOG(OPWORD) */
    if (NV_OK == NV_ReadEx(MODEM_ID_0, en_NV_Item_AT_DISLOG_PWD_NEW,
                          &stDislogPwdNew,
                          AT_OPWORD_PWD_LEN))
    {
        TAF_MEM_CPY_S((VOS_INT8*)g_acATOpwordPwd,
                   AT_OPWORD_PWD_LEN + 1,
                   (VOS_INT8*)(&stDislogPwdNew),
                   AT_OPWORD_PWD_LEN);

        /*  */
        g_acATOpwordPwd[AT_OPWORD_PWD_LEN] = 0;

        /* AP-Modem */
        if ((0 == VOS_StrLen((VOS_CHAR *)g_acATOpwordPwd))
         && (SYSTEM_APP_ANDROID != *pucSystemAppConfig))
        {
            /* NV */
            g_enATE5RightFlag = AT_E5_RIGHT_FLAG_YES;
        }
    }
    else
    {
        AT_WARN_LOG("AT_ReadAtDislogPwdNV:read en_NV_Item_AT_DISLOG_PWD_NEW failed");
    }

    return;
}

/*****************************************************************************
     : AT_ReadAtRightPasswordNV
   : ATNV
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20130306
           : f00179208
       : 
  2.       : 2013517
           : l00167671
       : NV, NV
  3.       : 2014530
           : j00174725
       : TQE
*****************************************************************************/
VOS_VOID AT_ReadAtRightPasswordNV(VOS_VOID)
{
    TAF_AT_NVIM_RIGHT_OPEN_FLAG_STRU        stNvimRightOpenFlg;

    TAF_MEM_SET_S(&stNvimRightOpenFlg, sizeof(stNvimRightOpenFlg), 0x00, sizeof(stNvimRightOpenFlg));

    /* NVAT */
    if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_AT_RIGHT_PASSWORD,
                           &stNvimRightOpenFlg,
                           sizeof(stNvimRightOpenFlg)))
    {
        /* NV, */
        TAF_MEM_SET_S(&g_stAtRightOpenFlg, sizeof(g_stAtRightOpenFlg), 0x00, sizeof(g_stAtRightOpenFlg));
        AT_WARN_LOG("AT_ReadAtRightPasswordNV:read en_NV_Item_AT_RIGHT_PASSWORD failed");
    }

    TAF_MEM_CPY_S(&g_stAtRightOpenFlg, sizeof(AT_RIGHT_OPEN_FLAG_STRU), &stNvimRightOpenFlg, sizeof(AT_RIGHT_OPEN_FLAG_STRU));
    return;
}

/*****************************************************************************
     : AT_ReadAtDissdPwdNV
   : SDNV
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20130306
           : f00179208
       : 
  2.       : 20130517
           : m00217266
       : nv
*****************************************************************************/
VOS_VOID AT_ReadAtDissdPwdNV(VOS_VOID)
{
    TAF_AT_NVIM_DISSD_PWD_STRU          stDissdPwd;

    TAF_MEM_SET_S(&stDissdPwd, sizeof(stDissdPwd), 0x00, AT_DISSD_PWD_LEN);

    if (NV_OK == NV_ReadEx(MODEM_ID_0, en_NV_Item_AT_DISSD_PWD,
                           &stDissdPwd,
                           AT_DISSD_PWD_LEN))
    {
        TAF_MEM_CPY_S((VOS_INT8*)g_acATE5DissdPwd,
                   AT_DISSD_PWD_LEN + 1,
                   (VOS_INT8*)(&stDissdPwd),
                   AT_DISSD_PWD_LEN);
        /*  */
        g_acATE5DissdPwd[AT_DISSD_PWD_LEN] = 0;
    }
    else
    {
        AT_WARN_LOG("AT_ReadAtDissdPwdNV:read en_NV_Item_AT_DISSD_PWD failed");
    }

    return;
}

/*****************************************************************************
     : AT_ReadNotSupportRetValueNV
   : NV
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20130306
           : f00179208
       : 
  2.       : 2013517
           : l00167671
       : NV, NV
*****************************************************************************/
VOS_VOID AT_ReadNotSupportRetValueNV(VOS_VOID)
{
    VOS_UINT32                                  ulRetLen;
    VOS_CHAR                                    acRetVal[AT_NOTSUPPORT_STR_LEN+1];
    TAF_AT_NOT_SUPPORT_CMD_ERROR_TEXT_STRU      stErrorText;

    TAF_MEM_SET_S(&stErrorText,  sizeof(stErrorText), 0x00, AT_NOTSUPPORT_STR_LEN);

     /* NVE5LCARDDONGLE
        NV"ERROR","COMMAND NOT SUPPORT" */
    if (NV_OK == NV_ReadEx(MODEM_ID_0, en_NV_Item_NOT_SUPPORT_RET_VALUE, stErrorText.acErrorText,
                           AT_NOTSUPPORT_STR_LEN))
    {
         TAF_MEM_CPY_S(acRetVal,
                    sizeof(acRetVal),
                    stErrorText.acErrorText,
                    AT_NOTSUPPORT_STR_LEN);

         /*  */
         acRetVal[AT_NOTSUPPORT_STR_LEN] = 0;
         ulRetLen                        = VOS_StrLen(acRetVal);
         if (ulRetLen > 0)
         {
             VOS_StrCpy_s((VOS_CHAR *)gaucAtCmdNotSupportStr, AT_NOTSUPPORT_STR_LEN+4, acRetVal);
         }
     }
     else
     {
         AT_WARN_LOG("AT_ReadNotSupportRetValueNV:read en_NV_Item_NOT_SUPPORT_RET_VALUE failed");
     }

    return;
}

/*****************************************************************************
     : AT_ReadE5NV
   : E5NV
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20130306
           : f00179208
       : 
*****************************************************************************/
VOS_VOID AT_ReadE5NV(VOS_VOID)
{
    AT_ReadAtDislogPwdNV();

    AT_ReadAtRightPasswordNV();

    AT_ReadAtDissdPwdNV();

    AT_ReadNotSupportRetValueNV();

    return;
}

/*****************************************************************************
     : AT_IsAbortCmdCharValid
   : .
   : pucAbortCmdChar: 
             ulLen          : 
   : 
     : VOS_TRUE: 
             VOS_FALSE:
   :
   :

       :
  1.       : 2012922
           : lijun 00171473
       :  for V7R1C50_At_Abort

*****************************************************************************/
VOS_UINT32 AT_IsAbortCmdCharValid(
    VOS_UINT8                          *pucAbortCmdChar,
    VOS_UINT32                          ulLen
)
{
    VOS_UINT32                          i;

    /* AT, , 
       (<0x20ASCII,, S3, S5).
       NVABORT, ,
       NVABORT,  */

    /*  */
    if ( VOS_NULL_PTR == pucAbortCmdChar )
    {
        return VOS_FALSE;
    }

    /* 0 */
    if ( 0 == ulLen )
    {
        return VOS_FALSE;
    }

    /* (<0x20ASCII,, S3, S5) */
    for ( i = 0 ; i < ulLen; i++ )
    {
        if ( (pucAbortCmdChar[i] == ucAtS3)
          || (pucAbortCmdChar[i] == ucAtS5)
          || (pucAbortCmdChar[i] <= 0x20) )
        {
            return VOS_FALSE;
        }
    }

    return VOS_TRUE;
}

/*****************************************************************************
     : AT_ReadAbortCmdParaNV
   : ATNV, 
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 2012922
           : lijun 00171473
       :  for V7R1C50_At_Abort
  2.       : 20131022
           : w00242748
       : NETSCANNVANY

*****************************************************************************/
VOS_VOID AT_ReadAbortCmdParaNV(VOS_VOID)
{
    AT_ABORT_CMD_PARA_STRU             *pstAbortCmdPara   = VOS_NULL_PTR;
    VOS_UINT8                           aucDfltAbortCmd[] = "AT";
    VOS_UINT8                           aucDfltAbortRsp[] = "OK";            /* ,  */
    AT_NVIM_ABORT_CMD_PARA_STRU         stNvAbortCmdPara;
    VOS_UINT32                          ulIsAbortCmdValid;
    VOS_UINT32                          ulIsAbortRspValid;
    VOS_UINT32                          ulRlst;
    VOS_UINT8                           aucAnyCharAbortCmd[] = "ANY";
    VOS_UINT32                          ulLen;

    /*  TQE */
    TAF_MEM_SET_S(&stNvAbortCmdPara,  sizeof(stNvAbortCmdPara), 0x00, sizeof(stNvAbortCmdPara));

    /*  */
    pstAbortCmdPara = AT_GetAbortCmdPara();
    TAF_MEM_SET_S(pstAbortCmdPara, sizeof(AT_ABORT_CMD_PARA_STRU), 0x00, sizeof(AT_ABORT_CMD_PARA_STRU));

    /* NV */
    ulRlst = NV_ReadEx(MODEM_ID_0, en_NV_Item_AT_ABORT_CMD_PARA,
                       &stNvAbortCmdPara,
                       sizeof(AT_NVIM_ABORT_CMD_PARA_STRU));

    /* NV */
    if ( NV_OK != ulRlst )
    {
        /* TRUE */
        pstAbortCmdPara->ucAbortEnableFlg = VOS_TRUE;

        /*  */
        VOS_StrNCpy_s((VOS_CHAR *)(pstAbortCmdPara->aucAbortAtCmdStr),
                    sizeof(pstAbortCmdPara->aucAbortAtCmdStr),
                    (VOS_CHAR*)aucDfltAbortCmd,
                    AT_MAX_ABORT_CMD_STR_LEN);
        pstAbortCmdPara->aucAbortAtCmdStr[AT_MAX_ABORT_CMD_STR_LEN] = '\0';

        /*  */
        VOS_StrNCpy_s((VOS_CHAR *)(pstAbortCmdPara->aucAbortAtRspStr),
                    sizeof(pstAbortCmdPara->aucAbortAtRspStr),
                    (VOS_CHAR *)aucDfltAbortRsp,
                    AT_MAX_ABORT_RSP_STR_LEN);
        pstAbortCmdPara->aucAbortAtRspStr[AT_MAX_ABORT_RSP_STR_LEN] = '\0';

        AT_WARN_LOG("AT_ReadAbortCmdParaNV:read en_NV_Item_AT_ABORT_CMD_PARA failed");

        return;
    }

    /* ,  */
    pstAbortCmdPara->ucAbortEnableFlg = stNvAbortCmdPara.ucAbortEnableFlg;
    if ( VOS_TRUE != pstAbortCmdPara->ucAbortEnableFlg )
    {
        return;
    }

    /* NVAT_MAX_ABORT_CMD_STR_LEN
       AT_MAX_ABORT_CMD_STR_LEN+1
       AT_MAX_ABORT_CMD_STR_LEN */
    VOS_StrNCpy_s((VOS_CHAR *)(pstAbortCmdPara->aucAbortAtCmdStr),
                sizeof(pstAbortCmdPara->aucAbortAtCmdStr),
                (VOS_CHAR *)(stNvAbortCmdPara.aucAbortAtCmdStr),
                AT_MAX_ABORT_CMD_STR_LEN);
    pstAbortCmdPara->aucAbortAtCmdStr[AT_MAX_ABORT_CMD_STR_LEN] = '\0';

    /* NVAT_MAX_ABORT_CMD_STR_LEN
       AT_MAX_ABORT_RSP_STR_LEN+1
       AT_MAX_ABORT_RSP_STR_LEN */
    VOS_StrNCpy_s((VOS_CHAR *)(pstAbortCmdPara->aucAbortAtRspStr),
                sizeof(pstAbortCmdPara->aucAbortAtRspStr),
                (VOS_CHAR *)(stNvAbortCmdPara.aucAbortAtRspStr),
                AT_MAX_ABORT_RSP_STR_LEN);
    pstAbortCmdPara->aucAbortAtRspStr[AT_MAX_ABORT_RSP_STR_LEN] = '\0';


    /* NV */
    ulIsAbortCmdValid = AT_IsAbortCmdCharValid(pstAbortCmdPara->aucAbortAtCmdStr,
                                     VOS_StrLen((VOS_CHAR *)(pstAbortCmdPara->aucAbortAtCmdStr)));

    ulIsAbortRspValid = AT_IsAbortCmdCharValid(pstAbortCmdPara->aucAbortAtRspStr,
                                     VOS_StrLen((VOS_CHAR *)(pstAbortCmdPara->aucAbortAtRspStr)));

    /* NV(, S3, S5, x020),  */
    if ( VOS_TRUE != ulIsAbortCmdValid )
    {
        VOS_StrNCpy_s((VOS_CHAR *)(pstAbortCmdPara->aucAbortAtCmdStr),
                    sizeof(pstAbortCmdPara->aucAbortAtCmdStr),
                    (VOS_CHAR*)aucDfltAbortCmd,
                    AT_MAX_ABORT_CMD_STR_LEN);
        pstAbortCmdPara->aucAbortAtCmdStr[AT_MAX_ABORT_CMD_STR_LEN] = '\0';

    }

    if ( VOS_TRUE != ulIsAbortRspValid )
    {
        VOS_StrNCpy_s((VOS_CHAR *)(pstAbortCmdPara->aucAbortAtRspStr),
                    sizeof(pstAbortCmdPara->aucAbortAtRspStr),
                    (VOS_CHAR *)aucDfltAbortRsp,
                    AT_MAX_ABORT_RSP_STR_LEN);
        pstAbortCmdPara->aucAbortAtRspStr[AT_MAX_ABORT_RSP_STR_LEN] = '\0';
    }

    ulLen = VOS_StrLen((VOS_CHAR *)pstAbortCmdPara->aucAbortAtCmdStr);

    if (VOS_StrLen((VOS_CHAR *)aucAnyCharAbortCmd) != ulLen)
    {
        return;
    }

    if ( (0 == VOS_StrNiCmp((VOS_CHAR *)aucAnyCharAbortCmd, (VOS_CHAR *)pstAbortCmdPara->aucAbortAtCmdStr, ulLen)) )
    {
        /* PS_MEM_SET0 */
        pstAbortCmdPara->ucAnyAbortFlg = VOS_TRUE;
    }

    return;
}

/*****************************************************************************
     : AT_ReadSysNV
   : NV
   : 
   : 
     : 
   :
   :

       :
  1.       : 20130306
           : f00179208
       : 
*****************************************************************************/
VOS_VOID AT_ReadSysNV(VOS_VOID)
{
    AT_ReadRoamCapaNV();

    AT_ReadSystemAppConfigNV();

    AT_ReadE5NV();

    AT_ReadAbortCmdParaNV();

    return;
}

/*****************************************************************************
     : AT_ReadCellSignReportCfgNV
   : NV
   : 
   : 
     : 
   :
   :

       :
  1.       : 20130306
           : f00179208
       : 
  2.       : 2013111
           : t00212959
       : cerssi
  3.       : 2013517
           : l00167671
       : NV, NV
*****************************************************************************/
VOS_VOID AT_ReadCellSignReportCfgNV( VOS_VOID )
{
    NAS_NVIM_CELL_SIGN_REPORT_CFG_STRU  stCellSignReportCfg;
    MODEM_ID_ENUM_UINT16                enModemId;
    AT_MODEM_NET_CTX_STRU              *pstNetCtx = VOS_NULL_PTR;
    VOS_UINT32                          ulLength;

    ulLength                            = 0;

    for (enModemId = 0; enModemId < MODEM_ID_BUTT; enModemId++)
    {
        pstNetCtx = AT_GetModemNetCtxAddrFromModemId(enModemId);

        TAF_MEM_SET_S(&stCellSignReportCfg, sizeof(stCellSignReportCfg), 0x00, sizeof(stCellSignReportCfg));

        (VOS_VOID)NV_GetLength(en_NV_Item_CELL_SIGN_REPORT_CFG, &ulLength);
        if(NV_OK != NV_ReadEx(enModemId,
                              en_NV_Item_CELL_SIGN_REPORT_CFG,
                              &stCellSignReportCfg,
                              ulLength))
        {
             AT_WARN_LOG("AT_ReadCellSignReportCfgNV:read en_NV_Item_CELL_SIGN_REPORT_CFG failed");
             return;
        }

        pstNetCtx->ucCerssiReportType = stCellSignReportCfg.ucSignThreshold;

        if (stCellSignReportCfg.ucSignThreshold >= AT_CERSSI_REPORT_TYPE_BUTT)
        {
            pstNetCtx->ucCerssiReportType  = AT_CERSSI_REPORT_TYPE_NOT_REPORT;
        }

        pstNetCtx->ucCerssiMinTimerInterval = stCellSignReportCfg.ucMinRptTimerInterval;

        if (stCellSignReportCfg.ucMinRptTimerInterval > AT_CERSSI_MAX_TIMER_INTERVAL)
        {
            pstNetCtx->ucCerssiMinTimerInterval = 0;
        }
        }

    return;
}

/*****************************************************************************
     : AT_ValidateWasCategory
   : UECategory
   : pstUeCapability - WASUENV
   : 
     : VOS_OK          - 
             VOS_ERR         - 
   :
   :

       :
  1.       : 2011914
           : A00165503
       : 

*****************************************************************************/
VOS_UINT32 AT_ValidateWasCategory(
    AT_NV_UE_CAPABILITY_STRU           *pstUeCapability
)
{
    if (VOS_TRUE != pstUeCapability->ucHSDSCHSupport)
    {
        return VOS_ERR;
    }

    if ( (pstUeCapability->ucHSDSCHPhyCategory < 1)
      || (pstUeCapability->ucHSDSCHPhyCategory > 12) )
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
     : AT_ValidateWasCategoryExt
   : UECategoryExt
   : pstUeCapability - WASUENV
   : 
     : VOS_OK          - 
             VOS_ERR         - 
   :
   :

       :
  1.       : 2011914
           : A00165503
       : 

*****************************************************************************/
VOS_UINT32 AT_ValidateWasCategoryExt(
    AT_NV_UE_CAPABILITY_STRU           *pstUeCapability
)
{
    if ( (VOS_TRUE != pstUeCapability->ucHSDSCHSupport)
      || (VOS_TRUE != pstUeCapability->ucMacEhsSupport) )
    {
        return VOS_ERR;
    }

    if ( (pstUeCapability->ucHSDSCHPhyCategoryExt < 13)
      || (pstUeCapability->ucHSDSCHPhyCategoryExt > 20) )
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
     : AT_ValidateWasCategoryExt2
   : UECategoryExt2
   : pstUeCapability - WASUENV
   : 
     : VOS_OK          - 
             VOS_ERR         - 
   :
   :

       :
  1.       : 2011914
           : A00165503
       : 

*****************************************************************************/
VOS_UINT32 AT_ValidateWasCategoryExt2(
    AT_NV_UE_CAPABILITY_STRU           *pstUeCapability
)
{
    if ( (VOS_TRUE != pstUeCapability->ucHSDSCHSupport)
      || (VOS_TRUE != pstUeCapability->ucMacEhsSupport)
      || (VOS_TRUE != pstUeCapability->ucMultiCellSupport) )
    {
        return VOS_ERR;
    }

    if ( (pstUeCapability->ucHSDSCHPhyCategoryExt2 < 21)
      || (pstUeCapability->ucHSDSCHPhyCategoryExt2 > 24) )
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
     : AT_ValidateWasCategoryExt3
   : UECategoryExt3
   : pstUeCapability - WASUENV
   : 
     : VOS_OK          - 
             VOS_ERR         - 
   :
   :

       :
  1.       : 2011914
           : A00165503
       : 

*****************************************************************************/
VOS_UINT32 AT_ValidateWasCategoryExt3(
    AT_NV_UE_CAPABILITY_STRU           *pstUeCapability
)
{
    if ( (VOS_TRUE != pstUeCapability->ucHSDSCHSupport)
      || (VOS_TRUE != pstUeCapability->ucMacEhsSupport)
      || (VOS_TRUE != pstUeCapability->ucMultiCellSupport)
      || (VOS_TRUE != pstUeCapability->ucDcMimoSupport) )
    {
        return VOS_ERR;
    }

    if ( (pstUeCapability->ucHSDSCHPhyCategoryExt3 < 25)
      || (pstUeCapability->ucHSDSCHPhyCategoryExt3 > 28) )
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
     : AT_GetWasDefaultCategory
   :
   : AT_NV_UE_CAPABILITY_STRU           *pstUeCapability
   : 
     : VOS_UINT8
   :
   :

       :
  1.       : 2011914
           : A00165503
       : 

*****************************************************************************/
VOS_UINT8 AT_GetWasDefaultCategory(
    AT_NV_UE_CAPABILITY_STRU           *pstUeCapability
)
{
    AT_RATE_WCDMA_CATEGORY_ENUM_UINT8   enRateCategory;

    switch (pstUeCapability->ucAsRelIndicator)
    {
        case PS_PTL_VER_R5:
        case PS_PTL_VER_R6:
            enRateCategory = AT_RATE_WCDMA_CATEGORY_10;
            break;

        case PS_PTL_VER_R7:
            enRateCategory = AT_RATE_WCDMA_CATEGORY_18;
            break;

        case PS_PTL_VER_R8:
            enRateCategory = AT_RATE_WCDMA_CATEGORY_28;
            break;

        default:
            enRateCategory = AT_RATE_WCDMA_CATEGORY_10;
            break;
    }

    return enRateCategory;
}

/*****************************************************************************
     : AT_CalcWasCategory
   : WASUENVWASCATEGORY
   : pstUeCapability - WASUENV
   : 
     : VOS_UINT8
   :
   :

       :
  1.       : 2011914
           : A00165503
       : 

*****************************************************************************/
VOS_UINT8 AT_CalcWasCategory(
    AT_NV_UE_CAPABILITY_STRU           *pstUeCapability
)
{
    AT_RATE_WCDMA_CATEGORY_ENUM_UINT8   enRateCategory;

    if (VOS_OK == AT_ValidateWasCategoryExt3(pstUeCapability))
    {
        return pstUeCapability->ucHSDSCHPhyCategoryExt3;
    }

    if (VOS_OK == AT_ValidateWasCategoryExt2(pstUeCapability))
    {
        return pstUeCapability->ucHSDSCHPhyCategoryExt2;
    }

    if (VOS_OK == AT_ValidateWasCategoryExt(pstUeCapability))
    {
        return pstUeCapability->ucHSDSCHPhyCategoryExt;
    }

    if (VOS_OK == AT_ValidateWasCategory(pstUeCapability))
    {
        return pstUeCapability->ucHSDSCHPhyCategory;
    }

    enRateCategory = AT_GetWasDefaultCategory(pstUeCapability);

    return enRateCategory;
}

/*****************************************************************************
     : AT_ReadWasCapabilityNV
   : WAS: CATEGORY
   : VOS_VOID
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20130306
           : f00179208
       : 
*****************************************************************************/
VOS_VOID AT_ReadWasCapabilityNV(VOS_VOID)
{
    AT_NV_UE_CAPABILITY_STRU            stNvUeCapability;
    VOS_UINT32                          ulResult;

    TAF_MEM_SET_S(&stNvUeCapability, sizeof(stNvUeCapability), 0x00, sizeof(stNvUeCapability));

    ulResult = NV_ReadEx(MODEM_ID_0, en_NV_Item_WAS_RadioAccess_Capa_New,
                         &stNvUeCapability,
                         sizeof(AT_NV_UE_CAPABILITY_STRU));
    if (VOS_OK != ulResult)
    {
        /* NV, R99 */
        g_stAtDlRateCategory.cWasRelIndicator = PS_PTL_VER_R99;
        g_stAtDlRateCategory.ucWasCategory    = AT_RATE_WCDMA_R99;
    }
    else
    {
        g_stAtDlRateCategory.cWasRelIndicator = (VOS_INT8)stNvUeCapability.ucAsRelIndicator;
        g_stAtDlRateCategory.ucWasCategory    = AT_CalcWasCategory(&stNvUeCapability);
    }
}

/*****************************************************************************
     : AT_CalcGasCategory
   : GASUENVGASCATEGORY
   : NVIM_GAS_HIGH_MULTISLOT_CLASS_STRU         *pstHighMultislotclass
             VOS_UINT16                                  usGprsMultiSlotClass
             VOS_UINT16                                  usEgprsMultiSlotClass
             VOS_UINT16                                  usEgprsFlag
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 2013315
           : l60609
       : 

*****************************************************************************/
VOS_VOID AT_CalcGasCategory(
    NVIM_GAS_HIGH_MULTISLOT_CLASS_STRU         *pstHighMultislotclass,
    VOS_UINT16                                  usGprsMultiSlotClass,
    VOS_UINT16                                  usEgprsMultiSlotClass,
    VOS_UINT16                                  usEgprsFlag
)
{
    /* VOS_FALSE */
    g_stAtDlRateCategory.ucGasMultislotClass33Flg = VOS_FALSE;

    if((VOS_TRUE == pstHighMultislotclass->usHighMultislotClassFlg)
     &&(AT_GAS_HIGH_MULTISLOT_CLASS_0 == pstHighMultislotclass->usHighMultislotClass))
    {
        if ((VOS_FALSE  == usEgprsFlag)
          &&(AT_GAS_GRR_MULTISLOT_CLASS_MAX == usGprsMultiSlotClass))
        {
            g_stAtDlRateCategory.ucGasMultislotClass33Flg = VOS_TRUE;
        }

        if((VOS_TRUE == usEgprsFlag)
         &&(AT_GAS_GRR_MULTISLOT_CLASS_MAX == usEgprsMultiSlotClass))
        {
            g_stAtDlRateCategory.ucGasMultislotClass33Flg = VOS_TRUE;
        }
    }

    return;
}

/*****************************************************************************
     : AT_ReadGasCapabilityNV
   : GAS: CATEGORY
   : VOS_VOID
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20130306
           : f00179208
       : 
*****************************************************************************/
VOS_VOID AT_ReadGasCapabilityNV(VOS_VOID)
{
    VOS_UINT32                                  ulResult;
    NVIM_GAS_HIGH_MULTISLOT_CLASS_STRU          stHighMultislotclass;
    VOS_UINT16                                  usGprsMultiSlotClass;
    VOS_UINT16                                  usEgprsMultiSlotClass;
    VOS_UINT16                                  usEgprsFlag;

    stHighMultislotclass.usHighMultislotClassFlg = VOS_FALSE;
    stHighMultislotclass.usHighMultislotClass    = AT_GAS_HIGH_MULTISLOT_CLASS_0;

    usGprsMultiSlotClass  = 0;
    usEgprsMultiSlotClass = 0;
    usEgprsFlag           = 0;

    ulResult = NV_ReadEx(MODEM_ID_0, en_NV_Item_Egprs_Flag, &usEgprsFlag, sizeof(VOS_UINT16));
    if ( NV_OK != ulResult )
    {
        usEgprsFlag = 0x01;
    }

    ulResult = NV_ReadEx(MODEM_ID_0, en_Nv_Item_Gprs_Multi_Slot_Class, &usGprsMultiSlotClass, sizeof(VOS_UINT16));

    /* 12 */
    if ( NV_OK != ulResult )
    {
        usGprsMultiSlotClass = AT_GAS_GRR_MULTISLOT_CLASS_MAX;
    }

    /* 1-12 */
    if (( 0 == usGprsMultiSlotClass )
      ||( AT_GAS_GRR_MULTISLOT_CLASS_MAX < usGprsMultiSlotClass ))
    {
        usGprsMultiSlotClass = AT_GAS_GRR_MULTISLOT_CLASS_MAX;
    }

    ulResult = NV_ReadEx(MODEM_ID_0, en_NV_Item_Egprs_Multi_Slot_Class, &usEgprsMultiSlotClass, sizeof(VOS_UINT16));
    if ( NV_OK != ulResult )
    {
        usEgprsMultiSlotClass = AT_GAS_GRR_MULTISLOT_CLASS_MAX;
    }

    /* 1-12 */
    if (( 0 == usEgprsMultiSlotClass )
      ||( AT_GAS_GRR_MULTISLOT_CLASS_MAX < usEgprsMultiSlotClass ))
    {
        usEgprsMultiSlotClass = AT_GAS_GRR_MULTISLOT_CLASS_MAX;
    }

    ulResult = NV_ReadEx(MODEM_ID_0, en_NV_Item_GAS_High_Multislot_Class,&stHighMultislotclass, sizeof(NVIM_GAS_HIGH_MULTISLOT_CLASS_STRU));

    /* High Multislot Class   */
    if ( NV_OK != ulResult )
    {
        return  ;
    }

    if((VOS_TRUE == stHighMultislotclass.usHighMultislotClassFlg)
     &&(AT_GAS_HIGH_MULTISLOT_CLASS_0 != stHighMultislotclass.usHighMultislotClass))
    {
        stHighMultislotclass.usHighMultislotClass = AT_GAS_HIGH_MULTISLOT_CLASS_0;
    }

    AT_CalcGasCategory(&stHighMultislotclass,
                       usGprsMultiSlotClass,
                       usEgprsMultiSlotClass,
                       usEgprsFlag);

    return;
}

/*****************************************************************************
     : AT_ReadPppDialErrCodeNV
   : NVPPP
   : 
   : 
     : 
   :
   :

       :
  1.       : 20130306
           : f00179208
       : 
  2.       : 2013517
           : l00167671
       : NV, NV
*****************************************************************************/
VOS_VOID AT_ReadPppDialErrCodeNV( VOS_VOID )
{
    NAS_NV_PPP_DIAL_ERR_CODE_STRU       stPppErrRpt;
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulLength;

    stPppErrRpt.ucStatus         = VOS_FALSE;
    stPppErrRpt.ucErrCodeRpt     = PPP_DIAL_ERR_CODE_BUTT;
    ulLength                     = 0;

    (VOS_VOID)NV_GetLength(en_NV_Item_PPP_DIAL_ERR_CODE, &ulLength);
    ulResult = NV_ReadEx(MODEM_ID_0, en_NV_Item_PPP_DIAL_ERR_CODE,
                         &stPppErrRpt,
                         ulLength);

    if ((ulResult == NV_OK)
     && (VOS_TRUE == stPppErrRpt.ucStatus)
     && (PPP_DIAL_ERR_CODE_ENABLE == stPppErrRpt.ucErrCodeRpt))

    {
        gucPppDialErrCodeRpt = PPP_DIAL_ERR_CODE_ENABLE;
    }
    else
    {
        gucPppDialErrCodeRpt = PPP_DIAL_ERR_CODE_DISABLE;
    }

    return;
}

/*****************************************************************************
     : AT_ReadReportRegActFlgNV
   : NVCREG/CGREGACT
   : 
   : 
     : 
   :
   :

       :
  1.       : 20130306
           : f00179208
       : 
  2.       : 20130520
           : m00217266
       : nv
*****************************************************************************/
VOS_VOID AT_ReadReportRegActFlgNV( VOS_VOID )
{
    VOS_UINT32                          ulResult;
    TAF_AT_NVIM_REPORT_REG_ACT_FLG_STRU stReportRegFlg;

    TAF_MEM_SET_S(&stReportRegFlg, sizeof(stReportRegFlg), 0x00, sizeof(TAF_AT_NVIM_REPORT_REG_ACT_FLG_STRU));

    ulResult = NV_ReadEx(MODEM_ID_0, en_NV_Item_REPORT_REG_ACT_FLG,
                         &(stReportRegFlg.usReportRegActFlg),
                         sizeof(stReportRegFlg.usReportRegActFlg));
    if (NV_OK != ulResult)
    {
        g_usReportCregActParaFlg = VOS_FALSE;
    }
    else
    {
        g_usReportCregActParaFlg = stReportRegFlg.usReportRegActFlg;
    }

    return;
}

/*****************************************************************************
     : AT_ReadCregAndCgregCiFourByteRptNV
   : NVCREG/CGREGCI4
   : 
   : 
     : 
   :
   :

       :
  1.       : 20130306
           : f00179208
       : 
  2.       : 2013517
           : l00167671
       : NV, NV
*****************************************************************************/
VOS_VOID AT_ReadCregAndCgregCiFourByteRptNV( VOS_VOID )
{
    NAS_NV_CREG_CGREG_CI_FOUR_BYTE_RPT_STRU     stCiFourByteRpt;
    VOS_UINT32                                  ulResult;
    VOS_UINT32                                  ulLength;

    stCiFourByteRpt.ucStatus     = VOS_FALSE;
    stCiFourByteRpt.ucCiBytesRpt = 0;
    ulLength                     = 0;

    (VOS_VOID)NV_GetLength(en_NV_Item_CREG_CGREG_CI_Four_Byte_Rpt, &ulLength);
    ulResult = NV_ReadEx(MODEM_ID_0, en_NV_Item_CREG_CGREG_CI_Four_Byte_Rpt,
                         &stCiFourByteRpt,
                         ulLength);
    if ((NV_OK == ulResult)
     && (VOS_TRUE == stCiFourByteRpt.ucStatus)
     && (CREG_CGREG_CI_RPT_FOUR_BYTE == stCiFourByteRpt.ucCiBytesRpt))
    {
        gucCiRptByte = CREG_CGREG_CI_RPT_FOUR_BYTE;
    }
    else
    {
        gucCiRptByte = CREG_CGREG_CI_RPT_TWO_BYTE;
    }

    return;
}

/*****************************************************************************
     : AT_ReadIpv6CapabilityNV
   : NVIPV6
   : 
   : 
     : 
   :
   :

       :
  1.       : 20130306
           : f00179208
       : 

*****************************************************************************/
VOS_VOID AT_ReadIpv6CapabilityNV( VOS_VOID )
{
    AT_NV_IPV6_CAPABILITY_STRU          stNvIpv6Capability;
    VOS_UINT32                          ulRslt;
    AT_COMM_PS_CTX_STRU                *pstCommPsCtx = VOS_NULL_PTR;
    VOS_UINT32                          ulIpv6CapabilityValid;

    TAF_MEM_SET_S(&stNvIpv6Capability, sizeof(stNvIpv6Capability), 0x00, sizeof(AT_NV_IPV6_CAPABILITY_STRU));

    pstCommPsCtx = AT_GetCommPsCtxAddr();

    ulRslt = NV_ReadEx(MODEM_ID_0,
                       en_NV_Item_IPV6_CAPABILITY,
                       &stNvIpv6Capability,
                       sizeof(AT_NV_IPV6_CAPABILITY_STRU));

    ulIpv6CapabilityValid = AT_PS_IsIpv6CapabilityValid(stNvIpv6Capability.ucIpv6Capablity);

    if ((NV_OK == ulRslt)
     && (VOS_TRUE == stNvIpv6Capability.ucStatus)
     && (VOS_TRUE == ulIpv6CapabilityValid))
    {
        pstCommPsCtx->ucIpv6Capability = stNvIpv6Capability.ucIpv6Capablity;
    }
    else
    {
        pstCommPsCtx->ucIpv6Capability = AT_IPV6_CAPABILITY_IPV4_ONLY;
    }

    return;
}

/* Added by l60609 for V9R1 IPv6&TAF/SM Project, 2013-4-24, begin */
/*****************************************************************************
     : AT_ReadIpv6BackProcExtCauseNV
   : NVIPv4v6
   : VOS_VOID
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20121217
           : A00165503
       : 
*****************************************************************************/
VOS_VOID AT_ReadIpv6BackProcExtCauseNV(VOS_VOID)
{
    AT_PS_IPV6_BACKPROC_EXT_CAUSE_STRU *pstPsBackProcExtCause = VOS_NULL_PTR;
    TAF_NV_IPV6_FALLBACK_EXT_CAUSE_STRU stNvBackProcExtCause;
    VOS_UINT32                          ulCauseNum;
    VOS_UINT32                          ulRslt;
    VOS_UINT32                          ulCnt;

    pstPsBackProcExtCause = &(AT_GetCommPsCtxAddr()->stIpv6BackProcExtCauseTbl);
    ulCauseNum            = 0;

    TAF_MEM_SET_S(&stNvBackProcExtCause, sizeof(stNvBackProcExtCause), 0x00, sizeof(TAF_NV_IPV6_FALLBACK_EXT_CAUSE_STRU));

    ulRslt = NV_ReadEx(MODEM_ID_0,
                       en_NV_Item_IPV6_BACKPROC_EXT_CAUSE,
                       &stNvBackProcExtCause,
                       sizeof(TAF_NV_IPV6_FALLBACK_EXT_CAUSE_STRU));

    if ( (NV_OK == ulRslt)
      && (VOS_TRUE == stNvBackProcExtCause.ulActiveFlag) )
    {
        for (ulCnt = 0 ; ulCnt < TAF_NV_IPV6_FALLBACK_EXT_CAUSE_MAX_NUM; ulCnt++)
        {
            /* (E)SM Cause */
            if (!TAF_PS_IS_SM_CAUSE_VALID(stNvBackProcExtCause.aucSmCause[ulCnt]))
            {
                continue;
            }
            else
            {
                pstPsBackProcExtCause->aenPsCause[ulCauseNum] = TAF_PS_CONVERT_SM_CAUSE_TO_PS_CAUSE(stNvBackProcExtCause.aucSmCause[ulCnt]);
                ulCauseNum++;
            }
        }
    }

    pstPsBackProcExtCause->ulCauseNum = ulCauseNum;

    return;
}

/*****************************************************************************
     : AT_ReadIpv6AddrTestModeCfgNV
   : IPV6NV
   : VOS_VOID
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 2015729
           : n00269697
       : 

*****************************************************************************/
VOS_VOID AT_ReadIpv6AddrTestModeCfgNV(VOS_VOID)
{
    TAF_NVIM_IPV6_ADDR_TEST_MODE_CFG_STRU                   stIpv6AddrTestModeCfg;
    AT_COMM_PS_CTX_STRU                                    *pstCommPsCtx = VOS_NULL_PTR;
    VOS_UINT32                                              ulRslt;

    TAF_MEM_SET_S(&stIpv6AddrTestModeCfg, sizeof(stIpv6AddrTestModeCfg), 0x00, sizeof(TAF_NVIM_IPV6_ADDR_TEST_MODE_CFG_STRU));

    pstCommPsCtx = AT_GetCommPsCtxAddr();

    ulRslt = NV_ReadEx(MODEM_ID_0,
                       en_NV_Item_Ipv6_Address_Test_Mode_Cfg,
                       &stIpv6AddrTestModeCfg,
                       sizeof(stIpv6AddrTestModeCfg));

    if ((NV_OK == ulRslt))
    {
        pstCommPsCtx->ulIpv6AddrTestModeCfg = stIpv6AddrTestModeCfg.ulIpv6AddrTestModeCfg;
    }
    else
    {
        pstCommPsCtx->ulIpv6AddrTestModeCfg = 0;
    }

    return;
}

/* Added by l60609 for V9R1 IPv6&TAF/SM Project, 2013-4-24, end */

/*****************************************************************************
     : AT_ReadSharePdpInfoNV
   : NVShare PDPFLAG
   : VOS_VOID
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 201367
           : z00214637
       : V3R3 Share-PDP
*****************************************************************************/
VOS_VOID AT_ReadSharePdpInfoNV(VOS_VOID)
{
    TAF_NVIM_SHARE_PDP_INFO_STRU        stSharePdpInfo;
    AT_COMM_PS_CTX_STRU                *pstCommPsCtx = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;

    TAF_MEM_SET_S(&stSharePdpInfo, sizeof(stSharePdpInfo), 0x00, sizeof(TAF_NVIM_SHARE_PDP_INFO_STRU));

    pstCommPsCtx = AT_GetCommPsCtxAddr();

    ulRslt = NV_ReadEx(MODEM_ID_0,
                       en_NV_Item_SHARE_PDP_INFO,
                       &stSharePdpInfo,
                       sizeof(stSharePdpInfo));

    if (NV_OK == ulRslt)
    {
        pstCommPsCtx->ucSharePdpFlag = stSharePdpInfo.ucEnableFlag;
    }
    else
    {
        pstCommPsCtx->ucSharePdpFlag = VOS_FALSE;
    }

    return;
}

/*****************************************************************************
     : AT_ReadDialConnectDisplayRateNV
   : NV
   : 
   : 
     : 
   :
   :

       :
  1.       : 20130306
           : f00179208
       : 
  2.       : 2013517
           : l00167671
       : NV, NV
  3.       : 20131008
           : j00174725
       : TQE
*****************************************************************************/
VOS_VOID AT_ReadDialConnectDisplayRateNV(VOS_VOID)
{
    VOS_UINT32                                              ulResult;
    AT_NVIM_DIAL_CONNECT_DISPLAY_RATE_STRU                  stDialConnectDisplayRate;

    TAF_MEM_SET_S(&stDialConnectDisplayRate, sizeof(stDialConnectDisplayRate), 0x00, sizeof(stDialConnectDisplayRate));


    ulResult = NV_ReadEx(MODEM_ID_0, en_NV_Item_DIAL_CONNECT_DISPLAY_RATE,
                         &stDialConnectDisplayRate,
                         sizeof(AT_NVIM_DIAL_CONNECT_DISPLAY_RATE_STRU));
    if (NV_OK != ulResult)
    {
        TAF_MEM_SET_S(&g_stDialConnectDisplayRate, sizeof(g_stDialConnectDisplayRate), 0x00, sizeof(g_stDialConnectDisplayRate));
		return;
    }

    g_stDialConnectDisplayRate.ucDpaConnectRate             = stDialConnectDisplayRate.ucDpaConnectRate;
    g_stDialConnectDisplayRate.ucEdgeConnectRate            = stDialConnectDisplayRate.ucEdgeConnectRate;
    g_stDialConnectDisplayRate.ucGprsConnectRate            = stDialConnectDisplayRate.ucGprsConnectRate;
    g_stDialConnectDisplayRate.ucGsmConnectRate             = stDialConnectDisplayRate.ucGsmConnectRate;
    g_stDialConnectDisplayRate.ucReserve1                   = stDialConnectDisplayRate.ucReserve1;
    g_stDialConnectDisplayRate.ucReserve2                   = stDialConnectDisplayRate.ucReserve2;
    g_stDialConnectDisplayRate.ucReserve3                   = stDialConnectDisplayRate.ucReserve3;
    g_stDialConnectDisplayRate.ucWcdmaConnectRate           = stDialConnectDisplayRate.ucWcdmaConnectRate;

    return;
}

/*****************************************************************************
     : AT_ReadPsNV
   : PSNV
   : 
   : 
     : 
   :
   :

       :
  1.       : 20130306
           : f00179208
       : 
       : DSDA PHASE III
  2.       : 201364
           : z00214637
       : V3R3 Share-PDP
*****************************************************************************/
VOS_VOID  AT_ReadPsNV(VOS_VOID)
{
    /* NV */
    AT_ReadPppDialErrCodeNV();

    /* CREG/CGREGACTNV */
    AT_ReadReportRegActFlgNV();

    /* CREG/CGREGCI4NV(Vodafone) */
    AT_ReadCregAndCgregCiFourByteRptNV();

    /* IPV6NV, IPV6IPV4V6_OVER_ONE_PDP */
    AT_ReadIpv6CapabilityNV();

    /* Added by l60609 for V9R1 IPv6&TAF/SM Project, 2013-4-24, begin */
    /* IPv6 */
    AT_ReadIpv6BackProcExtCauseNV();
    /* Added by l60609 for V9R1 IPv6&TAF/SM Project, 2013-4-24, end */

    AT_ReadIpv6AddrTestModeCfgNV();

    /* NV */
    AT_ReadDialConnectDisplayRateNV();

    /* WCDMANV, PS */
    AT_ReadWasCapabilityNV();

    /* GASCLASS33 NV */
    AT_ReadGasCapabilityNV();

    AT_ReadCellSignReportCfgNV();

    AT_ReadSharePdpInfoNV();

    /*  */
    AT_ReadRedialNoCauseFlagNV();

    return;
}

/*****************************************************************************
     : AT_ReadCsNV
   : csNV (ssCCNV)
   : 
   : 
     : 
   :
   :

       :
  1.       : 20130306
           : f00179208
       : 
  2.       : 20130124
           : f62575
       : DTS2013012408620, SSSS-STATUS
  3.       : 2013517
           : l00167671
       : NV, NV
*****************************************************************************/
VOS_VOID  AT_ReadCsNV(VOS_VOID)
{
    TAF_USSD_NVIM_TRANS_MODE_STRU       stUssdTranMode;
    TAF_CCA_TELE_PARA_STRU              stTimeInfo;
    MODEM_ID_ENUM_UINT16                enModemId;
    AT_MODEM_CC_CTX_STRU               *pstCcCtx = VOS_NULL_PTR;
    AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;
    VOS_UINT32                          ulLength;

    ulLength = 0;

    for (enModemId = 0; enModemId < MODEM_ID_BUTT; enModemId++)
    {
        pstCcCtx = AT_GetModemCcCtxAddrFromModemId(enModemId);
        pstSsCtx = AT_GetModemSsCtxAddrFromModemId(enModemId);

        TAF_MEM_SET_S(&stTimeInfo, sizeof(stTimeInfo), 0x00, sizeof(stTimeInfo));

        /* */
        if(NV_OK == NV_ReadEx(enModemId,
                              en_NV_Item_CCA_TelePara,
                              &stTimeInfo,
                              sizeof(TAF_CCA_TELE_PARA_STRU)))
        {
            pstCcCtx->stS0TimeInfo.ucS0TimerLen = stTimeInfo.ucS0TimerLen;
        }

        TAF_MEM_SET_S(&stUssdTranMode, sizeof(stUssdTranMode), 0x00, sizeof(stUssdTranMode));

        (VOS_VOID)NV_GetLength(en_NV_Item_CUST_USSD_MODE, &ulLength);
        /*USSD */
        if (NV_OK == NV_ReadEx(MODEM_ID_0,
                               en_NV_Item_CUST_USSD_MODE,
                               &stUssdTranMode,
                               ulLength))
        {
            if (VOS_TRUE == stUssdTranMode.ucStatus)
            {
                pstSsCtx->usUssdTransMode = stUssdTranMode.ucUssdTransMode;
            }
        }

    }

    AT_ReadSsNV();

    return;
}

/*****************************************************************************
     : AT_ReadLTENV
   : LTENV
   : 
   : 
     : 
   :
   :

       :
  1.       : 2012428
           : w00182550
       : 
  2.       : 201307222
           : j00177245
       : warning
*****************************************************************************/
VOS_VOID AT_ReadLTENV(VOS_VOID)
{
    VOS_UINT32 ulResult = NV_OK;

    TAF_MEM_SET_S(&g_stRsrpCfg, sizeof(g_stRsrpCfg), 0x00, sizeof(g_stRsrpCfg));
    TAF_MEM_SET_S(&g_stRscpCfg, sizeof(g_stRscpCfg), 0x00, sizeof(g_stRscpCfg));
    TAF_MEM_SET_S(&g_stEcioCfg, sizeof(g_stEcioCfg), 0x00, sizeof(g_stEcioCfg));

    /* NV */
    ulResult = NVM_Read(EN_NV_ID_RSRP_CFG, &g_stRsrpCfg, sizeof(NVIM_RSRP_CFG_STRU));

    if(NV_OK != ulResult)
    {
        (VOS_VOID)vos_printf("read RSRP NV fail!\n");
        return ;
    }

    /* NV */
    ulResult = NVM_Read(EN_NV_ID_RSCP_CFG, &g_stRscpCfg, sizeof(NVIM_RSCP_CFG_STRU));

    if(NV_OK != ulResult)
    {
        (VOS_VOID)vos_printf("read RSCP NV fail!\n");
        return ;
    }

    /* NV */
    ulResult = NVM_Read(EN_NV_ID_ECIO_CFG, &g_stEcioCfg, sizeof(NVIM_ECIO_CFG_STRU));

    if(NV_OK != ulResult)
    {
        (VOS_VOID)vos_printf("read ECIO NV fail!\n");
        return ;
    }

    return;
}


/*****************************************************************************
     : AT_ReadAgpsNv
   : AGPSNV
   : VOS_VOID
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 2016528
           : l00198894
       : 

*****************************************************************************/
VOS_VOID AT_ReadAgpsNv(VOS_VOID)
{
    AT_MODEM_AGPS_CTX_STRU             *pstAgpsCtx      = VOS_NULL_PTR;
    TAF_NVIM_XCPOSRRPT_CFG_STRU         stXcposrRptCfg;
    MODEM_ID_ENUM_UINT16                enModemId;

    TAF_MEM_SET_S(&stXcposrRptCfg, (VOS_SIZE_T)sizeof(stXcposrRptCfg), 0x00, (VOS_SIZE_T)sizeof(stXcposrRptCfg));

    /* NV */
    if (NV_OK == NV_Read(en_NV_Item_XCPOSRRPT_CFG, &stXcposrRptCfg, sizeof(stXcposrRptCfg)))
    {
        for (enModemId = MODEM_ID_0; enModemId < MODEM_ID_BUTT; enModemId++)
        {
            pstAgpsCtx = AT_GetModemAgpsCtxAddrFromModemId(enModemId);
            pstAgpsCtx->enCposrReport   = stXcposrRptCfg.ucCposrDefault;
            pstAgpsCtx->enXcposrReport  = stXcposrRptCfg.ucXcposrRptDefault;
        }
    }
    else
    {
        AT_ERR_LOG("AT_ReadAgpsNv: NV_Read Failed!");
    }

    return;
}

/*****************************************************************************
     : AT_ReadNV
   : ATNV
   : 
   : 
     :
   :
   :

       :
  1.       : 20130306
           : f00179208
       : 

  2.       : 20130921
           : j00174725
       : UART-MODEM: UARTNV

  3.       : 20151020
           : W00316404
       : R11 TFT 
*****************************************************************************/
VOS_VOID  AT_ReadNV(VOS_VOID)
{
    /* NV */
    AT_ReadPlatformNV();

    /* client NV */
    AT_ReadClientConfigNV();

    /* Deleted by s00217060 for ATC, 2013-4-3, begin */
    /* Deleted by s00217060 for ATC, 2013-4-3, end */

    /* NV */
    AT_ReadSysNV();

    /* PSNV */
    AT_ReadPsNV();

    /* csCCSSNV) */
    AT_ReadCsNV();

    /* SMSNV */
    AT_ReadSmsNV();

    /* LTE NV */
    AT_ReadLTENV();



    AT_ReadPortBuffCfgNV();

    AT_ReadPrivacyFilterCfgNv();

    AT_ReadAgpsNv();

    AT_ReadCdmaModemSwitchNotResetCfgNv();

    return;
}

/*****************************************************************************
     : AT_WriteCcpuResetRecordNvim
   : CNV(en_NV_Item_Ccpu_Reset_Record)
   : VOS_BOOL bCcpuResetFlag
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 2015525
           : n00269697
       : 

*****************************************************************************/
VOS_VOID AT_WriteCcpuResetRecordNvim(VOS_UINT8 ucCcpuResetFlag)
{
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulLength;
    TAF_NVIM_CCPU_RESET_RECORD_STRU     stCcpuResetRecord;

    ulLength = 0;

    TAF_MEM_SET_S(&stCcpuResetRecord, sizeof(stCcpuResetRecord), 0x00, sizeof(TAF_NVIM_CCPU_RESET_RECORD_STRU));

    (VOS_VOID)NV_GetLength(en_NV_Item_Ccpu_Reset_Record, &ulLength);
    if (ulLength > sizeof(TAF_NVIM_CCPU_RESET_RECORD_STRU))
    {
        return;
    }

    stCcpuResetRecord.ucCcpuResetFlag = ucCcpuResetFlag;

    ulResult = NV_WriteEx(MODEM_ID_0, en_NV_Item_Ccpu_Reset_Record, &stCcpuResetRecord, ulLength);

    if (NV_OK != ulResult)
    {
        AT_WARN_LOG("AT_WriteCcpuResetRecordNvim: en_NV_Item_Ccpu_Reset_Record NV Write Fail!");
    }

    return;
}

/*****************************************************************************
     : AT_ReadPhyNV
   : NV
   : VOS_VOID
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 201334
           : l60609
       : 

*****************************************************************************/
VOS_UINT32  AT_ReadPhyNV(VOS_VOID)
{
    VOS_BOOL                            bImeiIsNull;
    MODEM_ID_ENUM_UINT16                enModemId;

    for (enModemId = 0; enModemId < MODEM_ID_BUTT; enModemId++)
    {
        if (AT_OK != AT_PhyNumIsNull(enModemId, AT_PHYNUM_TYPE_IMEI, &bImeiIsNull))
        {
            return VOS_ERR;
        }

        if (VOS_TRUE != bImeiIsNull)
        {
            return VOS_ERR;
        }
    }

    return VOS_OK;
}

/*****************************************************************************
     : AT_InitDeviceCmd
   : 
   : VOS_VOID
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 2013321
           : l60609
       : 

*****************************************************************************/
VOS_VOID AT_InitDeviceCmd(VOS_VOID)
{
    if (VOS_OK != AT_ReadPhyNV())
    {
        return;
    }

    /* IMEIDATALOCK */
    g_bAtDataLocked = VOS_FALSE;

    return;
}

/*****************************************************************************
     : AT_InitStk
   : STKAT
   : VOS_VOID
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20130306
           : f00179208
       : 
*****************************************************************************/
VOS_VOID AT_InitStk(VOS_VOID)
{
    USIMM_STK_CFG_STRU                  stProfile;

    TAF_MEM_SET_S(&stProfile, sizeof(stProfile), 0x00, sizeof(stProfile));

    if(NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_TerminalProfile_Set, &stProfile, sizeof(USIMM_STK_CFG_STRU)))
    {
        AT_ERR_LOG("AT_StkInit: read en_NV_Item_TerminalProfile_Set fail.");

        g_ulSTKFunctionFlag = VOS_FALSE;
    }
    else
    {
        g_ulSTKFunctionFlag = stProfile.ucFuncEnable;
    }

    return;
}

/*****************************************************************************
     : AT_InitPara
   : AT
   : VOS_VOID
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20130306
           : f00179208
       : 

*****************************************************************************/
VOS_VOID AT_InitPara(VOS_VOID)
{
    VOS_UINT8                          *pucSystemAppConfig;
    VOS_UINT8                           ucAtCmdNotSupportStr1[]   = "ERROR";
    VOS_UINT8                           ucAtCmdNotSupportStr2[]   = "COMMAND NOT SUPPORT";
    MODEM_ID_ENUM_UINT16                enModemId;
    AT_MODEM_NET_CTX_STRU              *pstNetCtx = VOS_NULL_PTR;

    pucSystemAppConfig                  = AT_GetSystemAppConfigAddr();

    /*  */
    switch(*pucSystemAppConfig)
    {
        /* E5 */
        case SYSTEM_APP_WEBUI:

            pstNetCtx = AT_GetModemNetCtxAddrFromModemId(MODEM_ID_0);

            /*E5ERROR*/
            TAF_MEM_CPY_S((VOS_CHAR*)gaucAtCmdNotSupportStr,
                       AT_NOTSUPPORT_STR_LEN + 4,
                       (VOS_CHAR*)ucAtCmdNotSupportStr1,
                       sizeof(ucAtCmdNotSupportStr1));

            /* E5 */
            pstNetCtx->ucCopsFormatType = AT_COPS_NUMERIC_TYPE;

            /* E5 */
            gucAtCmeeType   = AT_CMEE_ERROR_CODE;

            break;

         /* STICK*/
        case SYSTEM_APP_MP:

            pstNetCtx = AT_GetModemNetCtxAddrFromModemId(MODEM_ID_0);

            /**/
            TAF_MEM_CPY_S((VOS_CHAR*)gaucAtCmdNotSupportStr,
                       AT_NOTSUPPORT_STR_LEN + 4,
                       (VOS_CHAR*)ucAtCmdNotSupportStr2,
                       sizeof(ucAtCmdNotSupportStr2));

            pstNetCtx->ucCopsFormatType = AT_COPS_LONG_ALPH_TYPE;

            /*  */
            gucAtCmeeType   = AT_CMEE_ERROR_CONTENT;


            break;

        /* PAD,stick*/
        case SYSTEM_APP_ANDROID:

            /**/
            TAF_MEM_CPY_S((VOS_CHAR*)gaucAtCmdNotSupportStr,
                       AT_NOTSUPPORT_STR_LEN + 4,
                       (VOS_CHAR*)ucAtCmdNotSupportStr2,
                       sizeof(ucAtCmdNotSupportStr2));

            for (enModemId = 0; enModemId < MODEM_ID_BUTT; enModemId++)
            {
                pstNetCtx = AT_GetModemNetCtxAddrFromModemId(enModemId);
                pstNetCtx->ucCopsFormatType = AT_COPS_LONG_ALPH_TYPE;
            }

            /*  */
            gucAtCmeeType   = AT_CMEE_ERROR_CODE;

            break;

        default:
            break;
    }

    return;
}

/*****************************************************************************
     : AT_UsbSwitchGwMode
   : 
   : VOS_VOID
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20130306
           : f00179208
       : 
  2.       : 2013114
           : A00165503
       : DTS2012042104301: PCUINDIS/APP
  3.       : 2013413
           : y00213812
       : DTS2012042104301ClientId
  4.       : 20130708
           : Y00213812
       : VoLTE_PhaseI PID
*****************************************************************************/
VOS_VOID AT_UsbSwitchGwMode(VOS_VOID)
{
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           aucCid[TAF_MAX_CID+1];

    pstAppPdpEntity                     = AT_APP_GetPdpEntInfoAddr();

    g_enHiLinkMode                      = AT_HILINK_GATEWAY_MODE;

    /* CID */
    TAF_MEM_SET_S(aucCid, sizeof(aucCid), 0x00, sizeof(aucCid));

    /* PDPIDLE, ; DEACTING,  */
    ulResult = AT_AppCheckPdpIdleState();
    if (VOS_TRUE == ulResult)
    {
        AT_NORM_LOG("AT_UsbSwitchGwMode: The state is already IDLE.");
        return;
    }

    if ( (AT_PDP_STATE_ACTING == pstAppPdpEntity->enIpv4v6State)
      || (AT_PDP_STATE_ACTED  == pstAppPdpEntity->enIpv4v6State) )
    {
        if (VOS_OK != TAF_PS_CallEnd(WUEPS_PID_AT,
                                     AT_PS_BuildExClientId(gastAtClientTab[AT_CLIENT_TAB_APP_INDEX].usClientId),
                                     0,
                                     g_stAtAppPdpEntity.ucIpv4v6Cid))
        {
            AT_WARN_LOG("AT_UsbSwitchGwMode(): Disconnect IPv4v6 fail");
        }

        AT_AppSetPdpState(TAF_PDP_IPV4V6, AT_PDP_STATE_DEACTING);
    }
    else
    {
        if ( (AT_PDP_STATE_ACTING == pstAppPdpEntity->enIpv4State)
          || (AT_PDP_STATE_ACTED  == pstAppPdpEntity->enIpv4State) )
        {
            if (VOS_OK != TAF_PS_CallEnd(WUEPS_PID_AT,
                                         AT_PS_BuildExClientId(gastAtClientTab[AT_CLIENT_TAB_APP_INDEX].usClientId),
                                         0,
                                         pstAppPdpEntity->ucIpv4Cid))
            {
                AT_WARN_LOG("AT_UsbSwitchGwMode():TAF_PS_CallEnd fail");
            }

            AT_AppSetPdpState(TAF_PDP_IPV4, AT_PDP_STATE_DEACTING);
        }

        if ( (AT_PDP_STATE_ACTING == pstAppPdpEntity->enIpv6State)
          || (AT_PDP_STATE_ACTED  == pstAppPdpEntity->enIpv6State) )
        {
            if (VOS_OK != TAF_PS_CallEnd(WUEPS_PID_AT,
                                         AT_PS_BuildExClientId(gastAtClientTab[AT_CLIENT_TAB_APP_INDEX].usClientId),
                                         0,
                                         pstAppPdpEntity->ucIpv6Cid))
            {
                AT_WARN_LOG("AT_UsbSwitchGwMode():TAF_PS_CallEnd fail");
            }

            AT_AppSetPdpState(TAF_PDP_IPV6, AT_PDP_STATE_DEACTING);
        }
    }

    return;
}

/*****************************************************************************
     : AT_UsbEnableCB
   : USB
   : VOS_VOID
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20131228
           : j00174725
       : 
*****************************************************************************/
VOS_VOID AT_UsbEnableCB(VOS_VOID)
{
    /* USB MODEM */
    AT_UsbModemInit();

    /* NCM,NCMDRV */
    AT_OpenUsbNdis();
}

/*****************************************************************************
     : AT_UsbDisableCB
   : USB
   : VOS_VOID
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20131228
           : j00174725
       : 

  2.       : 2015527
           : l00198894
       : TSTS
*****************************************************************************/
VOS_VOID AT_UsbDisableCB(VOS_VOID)
{
    (VOS_VOID)vos_printf("AT_UsbDisableCB\r\n");
    /* USB MODEM */
    AT_UsbModemClose();

    /* NCM,NCMDRV */
    AT_CloseUsbNdis();

    /* USBclient ID */
    AT_RmUsedClientIdFromTab(AT_CLIENT_ID_PCUI);
    AT_RmUsedClientIdFromTab(AT_CLIENT_ID_CTRL);
    AT_RmUsedClientIdFromTab(AT_CLIENT_ID_NDIS);
    AT_RmUsedClientIdFromTab(AT_CLIENT_ID_MODEM);
    AT_RmUsedClientIdFromTab(AT_CLIENT_ID_PCUI2);
}


/*****************************************************************************
     : AT_InitPort
   : AT
   : VOS_VOID
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 2013122
           : l60609
       : 

  2.       : 20130522
           : f00179208
       : V3R3 PPP PROJECT

  3.       : 2013921
           : j00174725
       : UART-MODEM: HSUART

  4.       : 2015527
           : l00198894
       : TSTS
*****************************************************************************/
VOS_VOID AT_InitPort(VOS_VOID)
{
    VOS_UINT8                           i;

    for (i = 0; i < AT_CLIENT_BUTT; i++)
    {
        g_alAtUdiHandle[i] = UDI_INVALID_HANDLE;
    }

    /* PC NAS GTR PCSDT USBCOM ATclient ID
       USB COM */
    /* USB PCUI */
    At_UsbPcuiEst(AT_USB_COM_PORT_NO);

    /* USB Control */
    At_UsbCtrEst(AT_CTR_PORT_NO);

    /* USB PCUI2 */
    At_UsbPcui2Est(AT_PCUI2_PORT_NO);

    /* UART */
    AT_UART_InitPort();


    /* NDIS MODEM */
    AT_UsbNdisEst();

    mdrv_usb_reg_enablecb((USB_UDI_ENABLE_CB_T)AT_UsbEnableCB);
    mdrv_usb_reg_disablecb((USB_UDI_ENABLE_CB_T)AT_UsbDisableCB);

    /* APP  */
    AT_AppComEst();

    /* DRV */
    if (VOS_ERROR == DRV_USB_NAS_SWITCH_GATEWAY_REGFUNC((USB_NET_DEV_SWITCH_GATEWAY)AT_UsbSwitchGwMode))
    {
        AT_ERR_LOG( "AT_InitPort: DRV_USB_NAS_SWITCH_GATEWAY_REGFUNC Failed!" );
    }

    AT_SockComEst(AT_SOCK_PORT_NO);

    AT_AppSockComEst(AT_APP_SOCK_PORT_NO);



    return;
}


/*****************************************************************************
     : At_PidInit
   : AT PID
   : enum VOS_INIT_PHASE_DEFINE enPhase
   : 
     : VOS_UINT32
             VOS_OK
             VOS_ERR
   :
   :

       :
  1.       : 20130306
           : f00179208
       : 

  2.       : 20131228
           : j00174725
       : HSUART PHASE III
*****************************************************************************/
VOS_UINT32  At_PidInit(enum VOS_INIT_PHASE_DEFINE enPhase)
{
    switch ( enPhase )
    {
        case VOS_IP_INITIAL:

            /* AT */
            AT_InitCtx();


            AT_InitPortBuffCfg();

            AT_InitTraceMsgTab();

            /*  */
            AT_InitResetCtx();

            /*NV*/
            AT_ReadNV();

            /*AT */
            At_ParseInit();

            /*AT*/
            At_RegisterBasicCmdTable();
            At_RegisterExCmdTable();
            At_RegisterExPrivateCmdTable();
            At_RegisterDeviceCmdTable();
            At_RegisterDeviceCmdTLTable();
            At_RegisterTLCmdTable();                  /* ADDED by c64416 for V9R1/V7R1 AT, 2013/09/18 */
            /*  */
            AT_InitDeviceCmd();

            /* STKAT */
            AT_InitStk();

            /* AT */
            AT_InitPara();

            /* AT */
            AT_InitMsgNumCtrlCtx();

            /*  */
            AT_InitPort();

            /* g_stFcIdMaptoFcPri */
            AT_InitFcMap();

            /* NCM/ECM */
            FC_ACORE_RegDrvAssemFunc((FC_ACORE_DRV_ASSEMBLE_PARA_FUNC)AT_UsbEthDeviceAccumTuneCB,
                                     (FC_ACORE_DRV_ASSEMBLE_PARA_FUNC)AT_UsbEthHostAccumTuneCB);


            /* C */
            mdrv_sysboot_register_reset_notify(NAS_AT_FUNC_PROC_NAME,
                                               AT_CCpuResetCallback,
                                               0,
                                               ACPU_RESET_PRIORITY_AT);

            /* HIFI */
            hifireset_regcbfunc(NAS_AT_FUNC_PROC_NAME,
                                    AT_HifiResetCallback,
                                    0,
                                    ACPU_RESET_PRIORITY_AT);

            AT_InitMntnCtx();

            /*  */
            PS_OM_LayerMsgFilterInit();
            PS_OM_LayerMsgFilterFuncReg(GUNAS_OM_LayerMsgFilter);
            break;

        default:
            break;
    }

    return VOS_OK;
}

/*****************************************************************************
     : AT_ReadSsNV
   : NVSS
   : VOS_VOID
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20130124
           : f62575
       : DTS2013012408620, SSSS-STATUS

*****************************************************************************/
VOS_VOID AT_ReadSsNV( VOS_VOID )
{
    TAF_MEM_SET_S(&g_stAtSsCustomizePara, sizeof(g_stAtSsCustomizePara), 0x00, sizeof(g_stAtSsCustomizePara));

    /* SSNV */
    if(NV_OK != NV_ReadEx(MODEM_ID_0,
                          en_NV_Item_SS_CUSTOMIZE_PARA,
                          &g_stAtSsCustomizePara,
                          sizeof(g_stAtSsCustomizePara)))
    {
        g_stAtSsCustomizePara.ucStatus = VOS_FALSE;
    }

    return;
}


/*****************************************************************************
     : AT_ReadDisableRedialNoCauseFlagNV
   : NV
   : 
   : 
     : 
   :
   :

       :
  1.       : 20160831
           : l00373346
       : 

*****************************************************************************/
VOS_VOID AT_ReadRedialNoCauseFlagNV(VOS_VOID)
{
    AT_COMM_PS_CTX_STRU                        *pstCommPsCtx = VOS_NULL_PTR;
    TAF_NV_PDP_REDIAL_FOR_NO_CAUSE_CFG_STRU     stNvRedialForNoCauseCfg;
    VOS_UINT32                                  ulRslt;

    TAF_MEM_SET_S(&stNvRedialForNoCauseCfg, (VOS_SIZE_T)sizeof(stNvRedialForNoCauseCfg),
                  0x00, (VOS_SIZE_T)sizeof(TAF_NV_PDP_REDIAL_FOR_NO_CAUSE_CFG_STRU));

    pstCommPsCtx = AT_GetCommPsCtxAddr();

    ulRslt = NV_ReadEx(MODEM_ID_0,
                       en_NV_Item_PDP_REDIAL_FOR_NO_CAUSE_CFG,
                       &stNvRedialForNoCauseCfg,
                       (VOS_SIZE_T)sizeof(TAF_NV_PDP_REDIAL_FOR_NO_CAUSE_CFG_STRU));

    if ((NV_OK == ulRslt)
     && (VOS_FALSE == stNvRedialForNoCauseCfg.ucEnable))
    {
        pstCommPsCtx->ucRedialForNoCauseFlag = stNvRedialForNoCauseCfg.ucEnable;
    }
    else
    {
        pstCommPsCtx->ucRedialForNoCauseFlag = VOS_TRUE;
    }

    return;
}

/*****************************************************************************
     : AT_ReadCdmaModemSwitchNotResetCfgNv
   : NvCdmaModemSwitch
   : 
   : 
     : 
   :
   :

       :
  1.       : 20161027
           : h00313353
       : 
*****************************************************************************/
VOS_VOID AT_ReadCdmaModemSwitchNotResetCfgNv(VOS_VOID)
{
    AT_MODEM_CDMAMODEMSWITCH_CTX_STRU                      *pstCdmaModemSwitchCtx = VOS_NULL_PTR;
    TAF_NVIM_CDMAMODEMSWITCH_NOT_RESET_CFG_STRU             stCdmaModemSwitchNvCfg;
    MODEM_ID_ENUM_UINT16                                    enModemId;

    /*  */
    TAF_MEM_SET_S(&stCdmaModemSwitchNvCfg, (VOS_UINT32)sizeof(TAF_NVIM_CDMAMODEMSWITCH_NOT_RESET_CFG_STRU), 0x00, (VOS_UINT32)sizeof(TAF_NVIM_CDMAMODEMSWITCH_NOT_RESET_CFG_STRU));

    /* NV */
    if (NV_OK != NV_ReadEx(MODEM_ID_0,
                           en_NV_Item_CDMAMODEMSWITCH_NOT_RESET_CFG,
                           &stCdmaModemSwitchNvCfg,
                           (VOS_UINT32)sizeof(TAF_NVIM_CDMAMODEMSWITCH_NOT_RESET_CFG_STRU)))
    {
        stCdmaModemSwitchNvCfg.ucEnableFlg = VOS_FALSE;
    }

    if (VOS_TRUE != stCdmaModemSwitchNvCfg.ucEnableFlg)
    {
        stCdmaModemSwitchNvCfg.ucEnableFlg = VOS_FALSE;
    }

    for (enModemId = 0; enModemId < MODEM_ID_BUTT; enModemId++)
    {
        pstCdmaModemSwitchCtx = AT_GetModemCdmaModemSwitchCtxAddrFromModemId(enModemId);

        pstCdmaModemSwitchCtx->ucEnableFlg = stCdmaModemSwitchNvCfg.ucEnableFlg;
    }

    return;
}


