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
#include "AtCtx.h"
#include "AtDataProc.h"
#include "AtMntn.h"


/*****************************************************************************
    .C
*****************************************************************************/
#define    THIS_FILE_ID                 PS_FILE_ID_AT_CTX_C

/*****************************************************************************
  2 
*****************************************************************************/
/***************************AT Begin******************************/
/* ATPID  */
AT_MODEM_PID_TAB_STRU                   g_astAtModemPidTab[] =
{
    {I0_WUEPS_PID_USIM,         I1_WUEPS_PID_USIM,          I2_WUEPS_PID_USIM,      0},
    {I0_MAPS_STK_PID,           I1_MAPS_STK_PID,            I2_MAPS_STK_PID,        0},
    {I0_MAPS_PIH_PID,           I1_MAPS_PIH_PID,            I2_MAPS_PIH_PID,        0},
    {I0_MAPS_PB_PID,            I1_MAPS_PB_PID,             I2_MAPS_PB_PID,         0},
    {I0_UEPS_PID_GRM,           I1_UEPS_PID_GRM,            I2_UEPS_PID_GRM,        0},
    {I0_UEPS_PID_DL,            I1_UEPS_PID_DL,             I2_UEPS_PID_DL,         0},
    {I0_UEPS_PID_LL,            I1_UEPS_PID_LL,             I2_UEPS_PID_LL,         0},
    {I0_UEPS_PID_SN,            I1_UEPS_PID_SN,             I2_UEPS_PID_SN,         0},
    {I0_UEPS_PID_GAS,           I1_UEPS_PID_GAS,            I2_UEPS_PID_GAS,        0},
    {I0_WUEPS_PID_MM,           I1_WUEPS_PID_MM,            I2_WUEPS_PID_MM,        0},
    {I0_WUEPS_PID_MMC,          I1_WUEPS_PID_MMC,           I2_WUEPS_PID_MMC,       0},
    {I0_WUEPS_PID_GMM,          I1_WUEPS_PID_GMM,           I2_WUEPS_PID_GMM,       0},
    {I0_WUEPS_PID_MMA,          I1_WUEPS_PID_MMA,           I2_WUEPS_PID_MMA,       0},
    {I0_WUEPS_PID_CC,           I1_WUEPS_PID_CC,            I2_WUEPS_PID_CC,        0},
    {I0_WUEPS_PID_SS,           I1_WUEPS_PID_SS,            I2_WUEPS_PID_SS,        0},
    {I0_WUEPS_PID_TC,           I1_WUEPS_PID_TC,            I2_WUEPS_PID_TC,        0},
    {I0_WUEPS_PID_SMS,          I1_WUEPS_PID_SMS,           I2_WUEPS_PID_SMS,       0},
    {I0_WUEPS_PID_RABM,         I1_WUEPS_PID_RABM,          I2_WUEPS_PID_RABM,      0},
    {I0_WUEPS_PID_SM,           I1_WUEPS_PID_SM,            I2_WUEPS_PID_SM,        0},
    {I0_WUEPS_PID_ADMIN,        I1_WUEPS_PID_ADMIN,         I2_WUEPS_PID_ADMIN,     0},
    {I0_WUEPS_PID_TAF,          I1_WUEPS_PID_TAF,           I2_WUEPS_PID_TAF,       0},
    {I0_WUEPS_PID_VC,           I1_WUEPS_PID_VC,            I2_WUEPS_PID_VC,        0},
    {I0_WUEPS_PID_DRV_AGENT,    I1_WUEPS_PID_DRV_AGENT,     I2_WUEPS_PID_DRV_AGENT, 0},
    {I0_UEPS_PID_MTA,           I1_UEPS_PID_MTA,            I2_UEPS_PID_MTA,        0},
    {I0_DSP_PID_GPHY,           I1_DSP_PID_GPHY,            I2_DSP_PID_GPHY,        0},
    {I0_DSP_PID_SLEEP,          I1_DSP_PID_SLEEP,           I2_DSP_PID_SLEEP,       0},
    {I0_DSP_PID_APM,            I1_DSP_PID_APM,             I2_DSP_PID_APM,         0},
    {I0_WUEPS_PID_SLEEP,        I1_WUEPS_PID_SLEEP,         I2_WUEPS_PID_SLEEP,     0},
    {I0_WUEPS_PID_WRR,          I1_WUEPS_PID_WRR,           0,                      0},
    {I0_WUEPS_PID_WCOM,         I1_WUEPS_PID_WCOM,          0,                      0},
    {I0_DSP_PID_WPHY,           I1_DSP_PID_WPHY,            0,                      0},
};

VOS_UINT32                              g_ulCtzuFlag = 0;

/* AT */
AT_COMM_CTX_STRU                        g_stAtCommCtx;

/* ATModem */
AT_MODEM_CTX_STRU                       g_astAtModemCtx[MODEM_ID_BUTT];

/* ATClient */
AT_CLIENT_CTX_STRU                      g_astAtClientCtx[AT_MAX_CLIENT_NUM];

/* AT */
AT_RESET_CTX_STRU                       g_stAtResetCtx;

/***************************AT End******************************/

/**********************************************************************/
/* (DIAG/SHELL) */
AT_E5_RIGHT_FLAG_ENUM_U32               g_enATE5RightFlag;

/*  g_stATDislogPwd  DIAGNV; 
    g_stATDislogPwd ,  DIAG ;
   NV  */
VOS_INT8                                g_acATOpwordPwd[AT_OPWORD_PWD_LEN+1];

/* Modified by s62952 for BalongV300R002 Build 2012-02-28, begin */
/* AT */
AT_RIGHT_OPEN_FLAG_STRU                 g_stAtRightOpenFlg;
/* Modified by s62952 for BalongV300R002 Build 2012-02-28, begin */

/* Modified by s62952 for BalongV300R002 Build 2012-02-28, begin */
/* SD */
VOS_INT8                                g_acATE5DissdPwd[AT_DISSD_PWD_LEN+1];
/* Modified by s62952 for BalongV300R002 Build 2012-02-28, end */

/* Modified by s62952 for BalongV300R002 Build 2012-02-28, begin */
/**/
VOS_UINT8                               gaucAtCmdNotSupportStr[AT_NOTSUPPORT_STR_LEN+4];
/* Modified by s62952 for BalongV300R002 Build 2012-02-28, end */

AT_ABORT_CMD_CTX_STRU                   gstAtAbortCmdCtx;   /*  */

/* */
PPP_DIAL_ERR_CODE_ENUM                  gucPppDialErrCodeRpt;

AT_DIAL_CONNECT_DISPLAY_RATE_STRU       g_stDialConnectDisplayRate;

/* UE:  */
AT_DOWNLINK_RATE_CATEGORY_STRU          g_stAtDlRateCategory;

VOS_UINT8                               ucAtS3          = 13;                   /* <CR> */
VOS_UINT8                               ucAtS4          = 10;                   /* <LF> */
VOS_UINT8                               ucAtS5          = 8;                    /* <DEL> */
VOS_UINT8                               ucAtS6          = 2;                    /* Number of seconds to wait before blind dialling:default value = 2 */
VOS_UINT8                               ucAtS7          = 50;                   /* Number of seconds in which connection must be established or call will be disconnected,
                                                                                   default value = 50(refer to Q)*/

/* Modified by s62952 for BalongV300R002 Build 2012-02-28, begin */
AT_CMEE_TYPE                            gucAtCmeeType;                          /* E5 */
/* Modified by s62952 for BalongV300R002 Build 2012-02-28, end */

TAF_UINT32                              g_ulSTKFunctionFlag = TAF_FALSE;

/*********************************CC Begin*************************************/
/* Deleted by s00217060 for ATC, 2013-4-10, begin */
/* Deleted by s00217060 for ATC, 2013-4-10, end */
/*********************************CC End*************************************/

/*********************************SMS Begin*************************************/
MN_MSG_CLASS0_TAILOR_U8                 g_enClass0Tailor         = MN_MSG_CLASS0_DEF;
/*********************************SMS End*************************************/

/*********************************NET Begin*************************************/
VOS_UINT16                              g_usReportCregActParaFlg = VOS_FALSE;
CREG_CGREG_CI_RPT_BYTE_ENUM             gucCiRptByte = CREG_CGREG_CI_RPT_TWO_BYTE;

/*********************************NET End*************************************/
NVIM_RSRP_CFG_STRU                      g_stRsrpCfg;
NVIM_RSCP_CFG_STRU                      g_stRscpCfg;
NVIM_ECIO_CFG_STRU                      g_stEcioCfg;

AT_ACCESS_STRATUM_RELEASE_STRU          g_stReleaseInfo;

AT_SS_CUSTOMIZE_PARA_STRU               g_stAtSsCustomizePara;

AT_TRACE_MSGID_TAB_STRU                 g_stAtTraceMsgIdTab[AT_CLIENT_ID_BUTT];

/*lint -e648 -e598 -e845 */
AT_CLIENT_CFG_MAP_TAB_STRU              g_astAtClientCfgMapTbl[] =
{
    AT_CLIENT_CFG_ELEMENT(PCUI),
    AT_CLIENT_CFG_ELEMENT(CTRL),
    AT_CLIENT_CFG_ELEMENT(PCUI2),
    AT_CLIENT_CFG_ELEMENT(MODEM),
    AT_CLIENT_CFG_ELEMENT(NDIS),
    AT_CLIENT_CFG_ELEMENT(UART),
    AT_CLIENT_CFG_ELEMENT(SOCK),
    AT_CLIENT_CFG_ELEMENT(APPSOCK),
    AT_CLIENT_CFG_ELEMENT(APP),
    AT_CLIENT_CFG_ELEMENT(APP1),
    AT_CLIENT_CFG_ELEMENT(APP2),
    AT_CLIENT_CFG_ELEMENT(APP3),
    AT_CLIENT_CFG_ELEMENT(APP4),
    AT_CLIENT_CFG_ELEMENT(APP5),
    AT_CLIENT_CFG_ELEMENT(APP6),
    AT_CLIENT_CFG_ELEMENT(APP7),
    AT_CLIENT_CFG_ELEMENT(APP8),
    AT_CLIENT_CFG_ELEMENT(APP9),
    AT_CLIENT_CFG_ELEMENT(APP10),
    AT_CLIENT_CFG_ELEMENT(APP11),
    AT_CLIENT_CFG_ELEMENT(APP12),
    AT_CLIENT_CFG_ELEMENT(APP13),
    AT_CLIENT_CFG_ELEMENT(APP14),
    AT_CLIENT_CFG_ELEMENT(APP15),
    AT_CLIENT_CFG_ELEMENT(APP16),
    AT_CLIENT_CFG_ELEMENT(APP17),
    AT_CLIENT_CFG_ELEMENT(APP18),
    AT_CLIENT_CFG_ELEMENT(APP19),
    AT_CLIENT_CFG_ELEMENT(APP20),
    AT_CLIENT_CFG_ELEMENT(APP21),
    AT_CLIENT_CFG_ELEMENT(APP22),
    AT_CLIENT_CFG_ELEMENT(APP23),
    AT_CLIENT_CFG_ELEMENT(APP24),
    AT_CLIENT_CFG_ELEMENT(APP25),
    AT_CLIENT_CFG_ELEMENT(APP26),

    AT_CLIENT_CFG_ELEMENT(APP27),
    AT_CLIENT_CFG_ELEMENT(APP28),
    AT_CLIENT_CFG_ELEMENT(APP29),
    AT_CLIENT_CFG_ELEMENT(APP30),
    AT_CLIENT_CFG_ELEMENT(APP31),
    AT_CLIENT_CFG_ELEMENT(APP32),
    AT_CLIENT_CFG_ELEMENT(APP33),
    AT_CLIENT_CFG_ELEMENT(APP34),
    AT_CLIENT_CFG_ELEMENT(APP35),
    AT_CLIENT_CFG_ELEMENT(APP36),
    AT_CLIENT_CFG_ELEMENT(APP37),
    AT_CLIENT_CFG_ELEMENT(APP38),
    AT_CLIENT_CFG_ELEMENT(APP39),
    AT_CLIENT_CFG_ELEMENT(APP40),
    AT_CLIENT_CFG_ELEMENT(APP41),

    AT_CLIENT_CFG_ELEMENT(APP42),
    AT_CLIENT_CFG_ELEMENT(APP43),
    AT_CLIENT_CFG_ELEMENT(APP44),
    AT_CLIENT_CFG_ELEMENT(APP45),
    AT_CLIENT_CFG_ELEMENT(APP46),
    AT_CLIENT_CFG_ELEMENT(APP47),
    AT_CLIENT_CFG_ELEMENT(APP48),
    AT_CLIENT_CFG_ELEMENT(APP49),
    AT_CLIENT_CFG_ELEMENT(APP50),
    AT_CLIENT_CFG_ELEMENT(APP51),
    AT_CLIENT_CFG_ELEMENT(APP52)

};
/*lint +e648 +e598 +e845 */

const VOS_UINT8                         g_ucAtClientCfgMapTabLen = AT_ARRAY_SIZE(g_astAtClientCfgMapTbl);




/*****************************************************************************
  3 
*****************************************************************************/
/*****************************************************************************
     : AT_InitUsimStatus
   : USIM
   : MODEM_ID_ENUM_UINT16 enModemId
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 2013226
           : l60609
       : 
  2.       : 201343
           : s00217060
       : ATC

*****************************************************************************/
VOS_VOID AT_InitUsimStatus(MODEM_ID_ENUM_UINT16 enModemId)
{
    AT_USIM_INFO_CTX_STRU              *pstUsimInfoCtx = VOS_NULL_PTR;

    pstUsimInfoCtx = AT_GetUsimInfoCtxFromModemId(enModemId);

    pstUsimInfoCtx->enCardStatus = USIMM_CARDAPP_SERVIC_BUTT;
    pstUsimInfoCtx->enCardType   = TAF_MMA_USIMM_CARD_TYPE_BUTT;

    pstUsimInfoCtx->ucIMSILen    = 0;
    TAF_MEM_SET_S(pstUsimInfoCtx->aucIMSI, sizeof(pstUsimInfoCtx->aucIMSI), 0x00, sizeof(pstUsimInfoCtx->aucIMSI));

    /* Deleted by s00217060 for ATC, 2013-4-3, begin */
    /* Deleted by s00217060 for ATC, 2013-4-3, end */

    return;
}

/*****************************************************************************
     : AT_InitPlatformRatList
   : 
   : MODEM_ID_ENUM_UINT16 enModemId
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 2013226
           : l60609
       : 

*****************************************************************************/
VOS_VOID AT_InitPlatformRatList(MODEM_ID_ENUM_UINT16 enModemId)
{
    AT_MODEM_SPT_RAT_STRU              *pstSptRat   = VOS_NULL_PTR;
    VOS_UINT8                          *pucIsCLMode = VOS_NULL_PTR;

    pstSptRat = AT_GetSptRatFromModemId(enModemId);

    /* GSM */
    pstSptRat->ucPlatformSptGsm        = VOS_TRUE;
    pstSptRat->ucPlatformSptWcdma      = VOS_FALSE;
    pstSptRat->ucPlatformSptLte        = VOS_FALSE;
    pstSptRat->ucPlatformSptUtralTDD   = VOS_FALSE;

    pucIsCLMode  = AT_GetModemCLModeCtxAddrFromModemId(enModemId);
    *pucIsCLMode = VOS_FALSE;

    return;

}

/*****************************************************************************
     : AT_InitCommPsCtx
   : PS
   : VOS_VOID
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 2013426
           : l60609
       : 

  2.       : 201367
           : z00214637
       : V3R3 Share-PDP

  3.       : 2015330
           : A00165503
       : SPE Project: SPE
*****************************************************************************/
VOS_VOID AT_InitCommPsCtx(VOS_VOID)
{
    AT_COMM_PS_CTX_STRU                *pstPsCtx = VOS_NULL_PTR;

    TAF_MEM_SET_S(&g_stAtNdisDhcpPara, sizeof(g_stAtNdisDhcpPara), 0x00, sizeof(g_stAtNdisDhcpPara));
    TAF_MEM_SET_S(&g_stAtAppPdpEntity, sizeof(g_stAtAppPdpEntity), 0x00, sizeof(g_stAtAppPdpEntity));

    pstPsCtx = AT_GetCommPsCtxAddr();

    pstPsCtx->ucIpv6Capability = AT_IPV6_CAPABILITY_IPV4_ONLY;

    pstPsCtx->stIpv6BackProcExtCauseTbl.ulCauseNum = 0;

    pstPsCtx->ulIpv6AddrTestModeCfg = 0;

    pstPsCtx->ucSharePdpFlag = VOS_FALSE;

    pstPsCtx->lSpePort       = AT_INVALID_SPE_PORT;
    pstPsCtx->ulIpfPortFlg   = VOS_FALSE;

    return;
}

/*****************************************************************************
     : AT_InitCommPbCtx
   : 
   : VOS_VOID
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 2015312
           : A00165503
       : 
*****************************************************************************/
VOS_VOID AT_InitCommPbCtx(VOS_VOID)
{
    AT_COMM_PB_CTX_STRU                *pstCommPbCntxt = VOS_NULL_PTR;

    pstCommPbCntxt = AT_GetCommPbCtxAddr();

    pstCommPbCntxt->usCurrIdx       = 0;
    pstCommPbCntxt->usLastIdx       = 0;
    pstCommPbCntxt->ulSingleReadFlg = VOS_FALSE;
    return;
}

/*****************************************************************************
     : AT_GetCmdProcCtxAddr
   : 
   : VOS_VOID
   : 
     : AT_CMD_PROC_CTX_STRU*
   :
   :

       :
  1.       : 2016510
           : z00301431
       : 
*****************************************************************************/
AT_CMD_PROC_CTX_STRU* AT_GetCmdProcCtxAddr(VOS_VOID)
{
    return &(g_stAtCommCtx.stCmdProcCtx);
}

/*****************************************************************************
     : AT_GetAuthPubkeyExCmdCtxAddr
   : 
   : VOS_VOID
   : 
     : AT_AUTH_PUBKEYEX_CMD_PROC_CTX*
   :
   :

       :
  1.       : 2016510
           : z00301431
       : 
*****************************************************************************/
AT_AUTH_PUBKEYEX_CMD_PROC_CTX* AT_GetAuthPubkeyExCmdCtxAddr(VOS_VOID)
{
    return &(AT_GetCmdProcCtxAddr()->stAuthPubkeyExCmdCtx);
}


/*****************************************************************************
     : AT_GetCmdVmsetCtxAddr
   : vmset
   : VOS_VOID
   : 
     : AT_VMSET_CMD_CTX_STRU*
   :
   :

       :
  1.       : 2016616
           : h00360002
       : 
*****************************************************************************/
AT_VMSET_CMD_CTX_STRU* AT_GetCmdVmsetCtxAddr(VOS_VOID)
{
    return &(AT_GetCmdProcCtxAddr()->stVmSetCmdCtx);
}

/*****************************************************************************
     : AT_InitVmSetCtx
   : VmSetCtx
   : VOS_VOID
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 2016618
           : h00360002
       : 
*****************************************************************************/
VOS_VOID AT_InitVmSetCtx(VOS_VOID)
{
    AT_VMSET_CMD_CTX_STRU              *pstVmSetCmdCtx        = VOS_NULL_PTR;

    pstVmSetCmdCtx = AT_GetCmdVmsetCtxAddr();

    pstVmSetCmdCtx->ulReportedModemNum  = 0;
    pstVmSetCmdCtx->ulResult            = AT_OK;

    return;
}


/*****************************************************************************
     : AT_InitCmdProcCtx
   : 
   : VOS_VOID
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 2016510
           : z00301431
       : 
*****************************************************************************/
VOS_VOID AT_InitCmdProcCtx(VOS_VOID)
{
    AT_AUTH_PUBKEYEX_CMD_PROC_CTX      *pstAuthPubkeyExCmdCtx = VOS_NULL_PTR;

    pstAuthPubkeyExCmdCtx = AT_GetAuthPubkeyExCmdCtxAddr();

    pstAuthPubkeyExCmdCtx->ucClientId               = 0;
    pstAuthPubkeyExCmdCtx->ucCurIdx                 = 0;
    pstAuthPubkeyExCmdCtx->ucTotalNum               = 0;
    pstAuthPubkeyExCmdCtx->usParaLen                = 0;
    pstAuthPubkeyExCmdCtx->ucSettingFlag            = VOS_FALSE;
    pstAuthPubkeyExCmdCtx->pucData                  = VOS_NULL_PTR;
    pstAuthPubkeyExCmdCtx->hAuthPubkeyProtectTimer  = VOS_NULL_PTR;


    AT_InitVmSetCtx();

    return;
}

/*****************************************************************************
     : AT_InitMsgNumCtrlCtx
   : at
   : VOS_VOID
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20160927
           : m00217266
       : 
*****************************************************************************/
VOS_VOID AT_InitMsgNumCtrlCtx(VOS_VOID)
{
    AT_CMD_MSG_NUM_CTRL_STRU           *pstMsgNumCtrlCtx = VOS_NULL_PTR;

    pstMsgNumCtrlCtx = AT_GetMsgNumCtrlCtxAddr();

    /*  */
    VOS_SpinLockInit(&(pstMsgNumCtrlCtx->stSpinLock));

    pstMsgNumCtrlCtx->ulMsgCount = 0;

    return;
}

/*****************************************************************************
     : AT_ClearAuthPubkeyCtx
   : 
   : VOS_VOID
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 2016510
           : z00301431
       : 
*****************************************************************************/
VOS_VOID AT_ClearAuthPubkeyCtx(VOS_VOID)
{
    AT_AUTH_PUBKEYEX_CMD_PROC_CTX      *pstAuthPubkeyExCmdCtx = VOS_NULL_PTR;

    pstAuthPubkeyExCmdCtx = AT_GetAuthPubkeyExCmdCtxAddr();

    pstAuthPubkeyExCmdCtx->ucClientId               = 0;
    pstAuthPubkeyExCmdCtx->ucCurIdx                 = 0;
    pstAuthPubkeyExCmdCtx->ucTotalNum               = 0;
    pstAuthPubkeyExCmdCtx->usParaLen                = 0;
    pstAuthPubkeyExCmdCtx->ucSettingFlag            = VOS_FALSE;

    if (VOS_NULL_PTR != pstAuthPubkeyExCmdCtx->pucData)
    {
        PS_MEM_FREE(WUEPS_PID_AT, pstAuthPubkeyExCmdCtx->pucData);
        pstAuthPubkeyExCmdCtx->pucData = VOS_NULL_PTR;
    }

    return;
}


/*****************************************************************************
     : AT_InitModemCcCtx
   : 
   : MODEM_ID_ENUM_UINT16 enModemId
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 2013220
           : l60609
       : 
  2.       : 20130411
           : l00198894
       : C50
  3.       : 20130711
           : l00198894
       : V9R1 STK
*****************************************************************************/
VOS_VOID AT_InitModemCcCtx(MODEM_ID_ENUM_UINT16 enModemId)
{
    AT_MODEM_CC_CTX_STRU               *pstCcCtx = VOS_NULL_PTR;
    VOS_UINT8                           i;

    pstCcCtx = AT_GetModemCcCtxAddrFromModemId(enModemId);

    pstCcCtx->ulCurIsExistCallFlag = VOS_FALSE;
    pstCcCtx->enCsErrCause         = TAF_CS_CAUSE_SUCCESS;

    /*  */
    TAF_MEM_SET_S(&(pstCcCtx->stS0TimeInfo), sizeof(pstCcCtx->stS0TimeInfo), 0x00, sizeof(pstCcCtx->stS0TimeInfo));

    TAF_MEM_SET_S(&(pstCcCtx->stEconfInfo), sizeof(pstCcCtx->stEconfInfo), 0x00, sizeof(pstCcCtx->stEconfInfo));

    for (i = 0; i < TAF_CALL_MAX_ECONF_CALLED_NUM; i++)
    {
        pstCcCtx->stEconfInfo.astCallInfo[i].enCallState = TAF_CALL_ECONF_STATE_BUTT;
        pstCcCtx->stEconfInfo.astCallInfo[i].enCause     = TAF_CS_CAUSE_SUCCESS;
    }

    /* Deleted by l00198894 for V9R1 STK, 2013/07/11 */

    return;
}

/*****************************************************************************
     : AT_InitModemSsCtx
   : SS
   : MODEM_ID_ENUM_UINT16 enModemId
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 2013220
           : l60609
       : 
  2.       : 201343
           : s00217060
       : ATC

*****************************************************************************/
VOS_VOID AT_InitModemSsCtx(MODEM_ID_ENUM_UINT16 enModemId)
{
    AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;

    pstSsCtx = AT_GetModemSsCtxAddrFromModemId(enModemId);

    /* Deleted by s00217060 for ATC, 2013-4-3, end */
    /* Deleted by s00217060 for ATC, 2013-4-3, end */
    pstSsCtx->usUssdTransMode      = AT_USSD_TRAN_MODE;
    /* Deleted by s00217060 for ATC, 2013-4-3, end */
    /* Deleted by s00217060 for ATC, 2013-4-3, end */
    pstSsCtx->enCModType           = MN_CALL_MODE_SINGLE;
    pstSsCtx->ucSalsType           = AT_SALS_DISABLE_TYPE;
    pstSsCtx->ucClipType           = AT_CLIP_DISABLE_TYPE;
    pstSsCtx->ucClirType           = AT_CLIR_AS_SUBSCRIPT;
    pstSsCtx->ucColpType           = AT_COLP_DISABLE_TYPE;
    pstSsCtx->ucCrcType            = AT_CRC_DISABLE_TYPE;
    pstSsCtx->ucCcwaType           = AT_CCWA_DISABLE_TYPE;

    /* Deleted by s00217060 for ATC, 2013-4-3, end */
    /* Deleted by s00217060 for ATC, 2013-4-3, end */

    pstSsCtx->stCbstDataCfg.enSpeed    = MN_CALL_CSD_SPD_64K_MULTI;
    pstSsCtx->stCbstDataCfg.enName     = MN_CALL_CSD_NAME_SYNC_UDI;
    pstSsCtx->stCbstDataCfg.enConnElem = MN_CALL_CSD_CE_T;

    TAF_MEM_SET_S(&(pstSsCtx->stCcugCfg), sizeof(pstSsCtx->stCcugCfg), 0x00, sizeof(pstSsCtx->stCcugCfg));

    return;
}

/*****************************************************************************
     : AT_InitModemSmsCtx
   : 
   : MODEM_ID_ENUM_UINT16 enModemId
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 2013220
           : l60609
       : 
  2.       : 20140304
           : f62575
       : DTS2014030801193, +CSMP

*****************************************************************************/
VOS_VOID AT_InitModemSmsCtx(MODEM_ID_ENUM_UINT16 enModemId)
{
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;

    pstSmsCtx = AT_GetModemSmsCtxAddrFromModemId(enModemId);

    pstSmsCtx->enCmgfMsgFormat      = AT_CMGF_MSG_FORMAT_PDU;
    pstSmsCtx->ucCsdhType           = AT_CSDH_NOT_SHOW_TYPE;
    pstSmsCtx->ucParaCmsr           = VOS_FALSE;
    pstSmsCtx->ucSmsAutoReply       = VOS_FALSE;
    pstSmsCtx->enCsmsMsgVersion     = MN_MSG_CSMS_MSG_VERSION_PHASE2_PLUS;

    /* ME */
    pstSmsCtx->enMsgMeStorageStatus = MN_MSG_ME_STORAGE_DISABLE;
    /* modified by l65478 for 2013-05-23 begin */
    pstSmsCtx->ucLocalStoreFlg      = VOS_TRUE;
    /* modified by l65478 for 2013-05-23 end */

    pstSmsCtx->stCnmiType.CnmiModeType    = AT_CNMI_MODE_BUFFER_TYPE;
    pstSmsCtx->stCnmiType.CnmiMtType      = AT_CNMI_MT_NO_SEND_TYPE;
    pstSmsCtx->stCnmiType.CnmiBmType      = AT_CNMI_BM_NO_SEND_TYPE;
    pstSmsCtx->stCnmiType.CnmiDsType      = AT_CNMI_DS_NO_SEND_TYPE;
    pstSmsCtx->stCnmiType.CnmiBfrType     = AT_CNMI_BFR_SEND_TYPE;
    pstSmsCtx->stCnmiType.CnmiTmpModeType = AT_CNMI_MODE_BUFFER_TYPE;
    pstSmsCtx->stCnmiType.CnmiTmpMtType   = AT_CNMI_MT_NO_SEND_TYPE;
    pstSmsCtx->stCnmiType.CnmiTmpBmType   = AT_CNMI_BM_NO_SEND_TYPE;
    pstSmsCtx->stCnmiType.CnmiTmpDsType   = AT_CNMI_DS_NO_SEND_TYPE;
    pstSmsCtx->stCnmiType.CnmiTmpBfrType  = AT_CNMI_BFR_SEND_TYPE;

    /*  */
    pstSmsCtx->stCgsmsSendDomain.ucActFlg     = VOS_FALSE;
    pstSmsCtx->stCgsmsSendDomain.enSendDomain = MN_MSG_SEND_DOMAIN_CS_PREFERRED;

    /* */
    pstSmsCtx->stSmMeFullCustomize.ucActFlg      = VOS_FALSE;
    pstSmsCtx->stSmMeFullCustomize.enMtCustomize = MN_MSG_MT_CUSTOMIZE_NONE;

    /*  */
    /*
    27005 3 Text Mode 3.1 Parameter Definitions
    Message Data Parameters
    <fo> depending on the command or result code: first octet of 3GPP TS 23.040
    [3] SMS-DELIVER, SMS-SUBMIT (default 17), SMS-STATUS-REPORT, or SMS-COMMAND
    (default 2) in integer format
    <vp> depending on SMS-SUBMIT <fo> setting: 3GPP TS 23.040 [3] TP-Validity-
    Period either in integer format (default 167), in time-string format (refer
    <dt>), or if EVPF is supported, in enhanced format (hexadecimal coded string
    with double quotes)
    */
    TAF_MEM_SET_S(&(pstSmsCtx->stCscaCsmpInfo), sizeof(pstSmsCtx->stCscaCsmpInfo), 0x00, sizeof(pstSmsCtx->stCscaCsmpInfo));
    pstSmsCtx->stCscaCsmpInfo.stParmInUsim.ucParmInd = 0xff;
    pstSmsCtx->stCscaCsmpInfo.stVp.enValidPeriod     =
    MN_MSG_VALID_PERIOD_RELATIVE;
    pstSmsCtx->stCscaCsmpInfo.stVp.u.ucOtherTime     = AT_CSMP_SUBMIT_VP_DEFAULT_VALUE;

    pstSmsCtx->stCscaCsmpInfo.ucDefaultSmspIndex     = AT_CSCA_CSMP_STORAGE_INDEX;

    /*  */
    pstSmsCtx->stCpmsInfo.stRcvPath.enStaRptMemStore = MN_MSG_MEM_STORE_SIM;
    pstSmsCtx->stCpmsInfo.stRcvPath.enSmMemStore     = MN_MSG_MEM_STORE_SIM;
    pstSmsCtx->stCpmsInfo.enMemReadorDelete          = MN_MSG_MEM_STORE_SIM;
    pstSmsCtx->stCpmsInfo.enMemSendorWrite           = MN_MSG_MEM_STORE_SIM;

    /*  */
    pstSmsCtx->stCpmsInfo.stRcvPath.enRcvSmAct       = MN_MSG_RCVMSG_ACT_STORE;
    pstSmsCtx->stCpmsInfo.stRcvPath.enRcvStaRptAct   = MN_MSG_RCVMSG_ACT_STORE;
    pstSmsCtx->stCpmsInfo.stRcvPath.enSmsServVersion = MN_MSG_CSMS_MSG_VERSION_PHASE2_PLUS;

    /* PDU */
    TAF_MEM_SET_S(&(pstSmsCtx->stSmtBuffer), sizeof(pstSmsCtx->stSmtBuffer), 0x00, sizeof(pstSmsCtx->stSmtBuffer));

    /*  */
    TAF_MEM_SET_S(pstSmsCtx->astSmsMtBuffer,
               sizeof(pstSmsCtx->astSmsMtBuffer),
               0x00,
               (sizeof(AT_SMS_MT_BUFFER_STRU) * AT_SMSMT_BUFFER_MAX));

    /* PDU */
    TAF_MEM_SET_S(&(pstSmsCtx->stCbsDcssInfo), sizeof(pstSmsCtx->stCbsDcssInfo), 0x00, sizeof(pstSmsCtx->stCbsDcssInfo));
    TAF_MEM_SET_S(&(pstSmsCtx->stCbmBuffer), sizeof(pstSmsCtx->stCbmBuffer), 0x00, sizeof(pstSmsCtx->stCbmBuffer));

    return;
}

/*****************************************************************************
     : AT_InitModemNetCtx
   : 
   : MODEM_ID_ENUM_UINT16 enModemId
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 2013221
           : l60609
       : 

*****************************************************************************/
VOS_VOID AT_InitModemNetCtx(MODEM_ID_ENUM_UINT16 enModemId)
{
    AT_MODEM_NET_CTX_STRU              *pstNetCtx = VOS_NULL_PTR;

    pstNetCtx = AT_GetModemNetCtxAddrFromModemId(enModemId);

    /* Deleted by s00217060 for ATC, 2013-4-1, begin */
    /* Deleted by s00217060 for ATC, 2013-4-1, end */
    pstNetCtx->ucCerssiReportType      = AT_CERSSI_REPORT_TYPE_5DB_CHANGE_REPORT;
    pstNetCtx->ucCregType              = AT_CREG_RESULT_CODE_NOT_REPORT_TYPE;
    pstNetCtx->ucCgregType             = AT_CGREG_RESULT_CODE_NOT_REPORT_TYPE;

    pstNetCtx->ucCopsFormatType         = AT_COPS_LONG_ALPH_TYPE;
    pstNetCtx->enPrefPlmnType           = MN_PH_PREF_PLMN_UPLMN;
    pstNetCtx->ucCpolFormatType         = AT_COPS_NUMERIC_TYPE;
    pstNetCtx->ucRoamFeature            = AT_ROAM_FEATURE_OFF;
    pstNetCtx->ucSpnType                = 0;
    pstNetCtx->ucCerssiMinTimerInterval = 0;
    pstNetCtx->enCalculateAntennaLevel  = AT_CMD_ANTENNA_LEVEL_0;
    TAF_MEM_SET_S(pstNetCtx->aenAntennaLevel, sizeof(pstNetCtx->aenAntennaLevel), 0x00, sizeof(pstNetCtx->aenAntennaLevel));
    TAF_MEM_SET_S(&(pstNetCtx->stTimeInfo), sizeof(pstNetCtx->stTimeInfo), 0x00, sizeof(pstNetCtx->stTimeInfo));

    pstNetCtx->ucCeregType           = AT_CEREG_RESULT_CODE_NOT_REPORT_TYPE;

    return;
}

/*****************************************************************************
     : AT_InitModemAgpsCtx
   : AGPS
   : MODEM_ID_ENUM_UINT16 enModemId
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 2013221
           : l60609
       : 

  2.       : 201599
           : l00198894
       : LCS

*****************************************************************************/
VOS_VOID AT_InitModemAgpsCtx(MODEM_ID_ENUM_UINT16 enModemId)
{
    AT_MODEM_AGPS_CTX_STRU             *pstAgpsCtx = VOS_NULL_PTR;

    pstAgpsCtx = AT_GetModemAgpsCtxAddrFromModemId(enModemId);

    TAF_MEM_SET_S(&(pstAgpsCtx->stXml), sizeof(pstAgpsCtx->stXml), 0x00, sizeof(pstAgpsCtx->stXml));

    pstAgpsCtx->enCposrReport   = AT_CPOSR_DISABLE;
    pstAgpsCtx->enXcposrReport  = AT_XCPOSR_DISABLE;
    pstAgpsCtx->enCmolreType    = AT_CMOLRE_NUMERIC;

    return;
}

/*****************************************************************************
     : AT_InitModemPsCtx
   : PSmodem
   : VOS_VOID
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 2013426
           : l60609
       : 

  2.       : 20131111
           : A00165503
       : DTS2013110900839: IPRABID

  3.       : 2017323
           : A00165503
       : EMC
*****************************************************************************/
VOS_VOID AT_InitModemPsCtx(
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    AT_MODEM_PS_CTX_STRU               *pstPsCtx = VOS_NULL_PTR;
    VOS_UINT32                          ulCnt;

    pstPsCtx = AT_GetModemPsCtxAddrFromModemId(enModemId);

    /* CID */
    for (ulCnt = 0; ulCnt <= TAF_MAX_CID; ulCnt++)
    {
        pstPsCtx->aucCidToIndexTbl[ulCnt] = AT_PS_CALL_INVALID_CALLID;
    }

    /*  */
    for (ulCnt = 0; ulCnt < AT_PS_MAX_CALL_NUM; ulCnt++)
    {
        pstPsCtx->astCallEntity[ulCnt].ulUsedFlg   = VOS_FALSE;

        TAF_MEM_SET_S(&pstPsCtx->astCallEntity[ulCnt].stUsrDialParam,
                   sizeof(pstPsCtx->astCallEntity[ulCnt].stUsrDialParam), 0x00, sizeof(AT_DIAL_PARAM_STRU));

        pstPsCtx->astCallEntity[ulCnt].ucIpv4Cid   = AT_PS_CALL_INVALID_CID;
        pstPsCtx->astCallEntity[ulCnt].enIpv4State = AT_PDP_STATE_IDLE;

        TAF_MEM_SET_S(&pstPsCtx->astCallEntity[ulCnt].stIpv4DhcpInfo,
                   sizeof(pstPsCtx->astCallEntity[ulCnt].stIpv4DhcpInfo), 0x00, sizeof(AT_IPV4_DHCP_PARAM_STRU));

        pstPsCtx->astCallEntity[ulCnt].ucIpv6Cid   = AT_PS_CALL_INVALID_CID;
        pstPsCtx->astCallEntity[ulCnt].enIpv6State = AT_PDP_STATE_IDLE;

        TAF_MEM_SET_S(&pstPsCtx->astCallEntity[ulCnt].stIpv6RaInfo,
                   sizeof(pstPsCtx->astCallEntity[ulCnt].stIpv6RaInfo), 0x00, sizeof(AT_IPV6_RA_INFO_STRU));
        TAF_MEM_SET_S(&pstPsCtx->astCallEntity[ulCnt].stIpv6DhcpInfo,
                   sizeof(pstPsCtx->astCallEntity[ulCnt].stIpv6DhcpInfo), 0x00, sizeof(AT_IPV6_DHCP_PARAM_STRU));
    }

    /* CHDATA CFG */
    for (ulCnt = 0; ulCnt <= TAF_MAX_CID; ulCnt++)
    {
        pstPsCtx->astChannelCfg[ulCnt].ulUsed        = VOS_FALSE;
        pstPsCtx->astChannelCfg[ulCnt].ulRmNetId     = AT_PS_INVALID_RMNET_ID;
        pstPsCtx->astChannelCfg[ulCnt].ulRmNetActFlg = VOS_FALSE;
    }

    /*  */
    pstPsCtx->enPsErrCause = TAF_PS_CAUSE_SUCCESS;

    /* IPRABID */
    TAF_MEM_SET_S(pstPsCtx->aulIpAddrRabIdMap, sizeof(pstPsCtx->aulIpAddrRabIdMap), 0x00, (sizeof(VOS_UINT32) * AT_PS_RABID_MAX_NUM));

    TAF_MEM_SET_S(&(pstPsCtx->stImsEmcRdp), sizeof(AT_IMS_EMC_RDP_STRU), 0x00, sizeof(AT_IMS_EMC_RDP_STRU));

    return;
}

/*****************************************************************************
     : AT_InitModemPrivacyFilterCtx
   : 
   : MODEM_ID_ENUM_UINT16 enModemId
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20160702
           : f00179208
       : 
*****************************************************************************/
VOS_VOID AT_InitModemPrivacyFilterCtx(
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    AT_MODEM_PRIVACY_FILTER_CTX_STRU   *pstFilterCtx = VOS_NULL_PTR;

    pstFilterCtx = AT_GetModemPrivacyFilterCtxAddrFromModemId(enModemId);

    TAF_MEM_SET_S(pstFilterCtx,
                  (VOS_UINT32)sizeof(AT_MODEM_PRIVACY_FILTER_CTX_STRU),
                  0,
                  (VOS_UINT32)sizeof(AT_MODEM_PRIVACY_FILTER_CTX_STRU));

    pstFilterCtx->ucFilterEnableFlg = VOS_FALSE;

    return;
}

/*****************************************************************************
     : AT_InitModemCdmaModemSwitchCtx
   : CDMAMODEMSWITCH
   : MODEM_ID_ENUM_UINT16 enModemId
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20161027
           : h00313353
       : 
*****************************************************************************/
VOS_VOID AT_InitModemCdmaModemSwitchCtx(
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    AT_MODEM_CDMAMODEMSWITCH_CTX_STRU  *pstCdmaModemSwitchCtx;

    pstCdmaModemSwitchCtx = AT_GetModemCdmaModemSwitchCtxAddrFromModemId(enModemId);

    TAF_MEM_SET_S(pstCdmaModemSwitchCtx,
                  (VOS_UINT32)sizeof(AT_MODEM_CDMAMODEMSWITCH_CTX_STRU),
                  0x00,
                  (VOS_UINT32)sizeof(AT_MODEM_CDMAMODEMSWITCH_CTX_STRU));

    pstCdmaModemSwitchCtx->ucEnableFlg = VOS_FALSE;

    return;
}

/*****************************************************************************
     : AT_InitModemImsCtx
   : IMS
   : MODEM_ID_ENUM_UINT16 enModemId
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 2016718
           : w00316404
       : 

*****************************************************************************/
VOS_VOID AT_InitModemImsCtx(MODEM_ID_ENUM_UINT16 enModemId)
{
    AT_MODEM_IMS_CONTEXT_STRU           *pstImsCtx = VOS_NULL_PTR;

    pstImsCtx = AT_GetModemImsCtxAddrFromModemId(enModemId);

    TAF_MEM_SET_S(pstImsCtx, sizeof(AT_MODEM_IMS_CONTEXT_STRU), 0x00, sizeof(AT_MODEM_IMS_CONTEXT_STRU));

    pstImsCtx->stBatteryInfo.enCurrBatteryInfo = AT_IMSA_BATTERY_STATUS_BUTT;
    pstImsCtx->stBatteryInfo.enTempBatteryInfo = AT_IMSA_BATTERY_STATUS_BUTT;

    return;
}

/*****************************************************************************
     : AT_InitClientConfiguration
   : ATClient
   : VOS_VOID
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20121213
           : l60609
       : DSDA Phase II: 

*****************************************************************************/
VOS_VOID AT_InitClientConfiguration(VOS_VOID)
{
    VOS_UINT8                           i;
    AT_CLIENT_CTX_STRU                 *pstClientCtx = VOS_NULL_PTR;

    for (i = 0; i < AT_CLIENT_BUTT; i++)
    {
        pstClientCtx = AT_GetClientCtxAddr(i);

        pstClientCtx->stClientConfiguration.ucReportFlg = VOS_TRUE;
        pstClientCtx->stClientConfiguration.enModemId   = MODEM_ID_0;
    }

    return;
}

/*****************************************************************************
     : AT_InitResetCtx
   : RNIC
   : 
   : 
     : VOS_VOID
   :
   :

      :
 1.       : 20130415
          : f00179208
      : 
 2.       : 201307222
          : j00177245
      : warning
*****************************************************************************/
VOS_VOID AT_InitResetCtx(VOS_VOID)
{
    AT_RESET_CTX_STRU                   *pstResetCtx = VOS_NULL_PTR;

    TAF_MEM_SET_S(&g_stAtStatsInfo, (VOS_UINT32)sizeof(g_stAtStatsInfo), 0x00, (VOS_UINT32)sizeof(g_stAtStatsInfo));

    pstResetCtx = AT_GetResetCtxAddr();

    pstResetCtx->hResetSem     = VOS_NULL_PTR;
    pstResetCtx->ulResetingFlag = VOS_FALSE;

    /*  */
    if (VOS_OK != VOS_SmBCreate( "AT", 0, VOS_SEMA4_FIFO, &pstResetCtx->hResetSem))
    {
        (VOS_VOID)vos_printf("Create AT acpu cnf sem failed!\r\n");
        AT_DBG_SET_SEM_INIT_FLAG(VOS_FALSE);
        AT_DBG_CREATE_BINARY_SEM_FAIL_NUM(1);

        return;
    }
    else
    {
        AT_DBG_SAVE_BINARY_SEM_ID(pstResetCtx->hResetSem);
    }

    AT_DBG_SET_SEM_INIT_FLAG(VOS_TRUE);

    return;
}

/*****************************************************************************
     : AT_InitReleaseInfo
   : 
   : 
   : 
     : VOS_VOID
   :
   :

      :
 1.       : 20161123
          : wx270776
      : 
*****************************************************************************/
VOS_VOID AT_InitReleaseInfo(VOS_VOID)
{
    TAF_MEM_SET_S(&g_stReleaseInfo, (VOS_UINT32)sizeof(g_stReleaseInfo), 0x00, (VOS_UINT32)sizeof(g_stReleaseInfo));

    g_stReleaseInfo.enAccessStratumRel = AT_ACCESS_STRATUM_REL9;

    return;
}

/*****************************************************************************
     : AT_InitCommCtx
   : 
   : VOS_VOID
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 2013220
           : l60609
       : 

  2.       : 201352
           : l60609
       : IPv6&TAF/SM Project

  3.       : 20130922
           : j00174725
       : UART-MODEM: UART

  4.       : 2015312
           : A00165503
       : DTS2015032409785: 
*****************************************************************************/
VOS_VOID AT_InitCommCtx(VOS_VOID)
{
    AT_COMM_CTX_STRU                   *pstCommCtx = VOS_NULL_PTR;

    pstCommCtx = AT_GetCommCtxAddr();

    /* MP */
    pstCommCtx->ucSystemAppConfigAddr = SYSTEM_APP_MP;

    /* MUX */
    TAF_MEM_SET_S(&(pstCommCtx->stMuxCtx), (VOS_UINT32)sizeof(pstCommCtx->stMuxCtx), 0x00, (VOS_UINT32)sizeof(AT_MUX_CTX_STRU));

    /* Modified by l60609 for V9R1 IPv6&TAF/SM Project, 2013-5-2, begin */
    /* PS */
    AT_InitCommPsCtx();
    /* Modified by l60609 for V9R1 IPv6&TAF/SM Project, 2013-5-2, end */

    AT_InitCommPbCtx();

    AT_InitCmdProcCtx();

    AT_InitReleaseInfo();

    return;
}

/*****************************************************************************
     : AT_InitClientCtx
   : 
   : VOS_VOID
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20121224
           : l60609
       : 

*****************************************************************************/
VOS_VOID AT_InitClientCtx(VOS_VOID)
{
    AT_InitClientConfiguration();
}

/*****************************************************************************
     : AT_InitModemCtx
   : Modem
   : MODEM_ID_ENUM_UINT16 enModemId
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20121224
           : l60609
       : 
  2.       : 20121227
           : z00220246
       : 
  3.       : 201335
           : l60609
       : DSDA PHASE III
  4.       : 201352
           : l60609
       : IPv6&TAF/SM Project
*****************************************************************************/
VOS_VOID AT_InitModemCtx(MODEM_ID_ENUM_UINT16 enModemId)
{
    AT_InitUsimStatus(enModemId);

    AT_InitPlatformRatList(enModemId);

    AT_InitModemCcCtx(enModemId);

    AT_InitModemSsCtx(enModemId);

    AT_InitModemSmsCtx(enModemId);

    AT_InitModemNetCtx(enModemId);

    AT_InitModemAgpsCtx(enModemId);

    /* Modified by l60609 for V9R1 IPv6&TAF/SM Project, 2013-5-2, begin */
    AT_InitModemPsCtx(enModemId);
    /* Modified by l60609 for V9R1 IPv6&TAF/SM Project, 2013-5-2, end */

    AT_InitModemImsCtx(enModemId);

    AT_InitModemPrivacyFilterCtx(enModemId);

    AT_InitModemCdmaModemSwitchCtx(enModemId);

    return;
}

/*****************************************************************************
     : AT_InitCtx
   : AT
   : VOS_VOID
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20121213
           : l60609
       : DSDA Phase II: 
  2.       : 201334
           : l60609
       : DSDA PHASE III
*****************************************************************************/
VOS_VOID AT_InitCtx(VOS_VOID)
{
    MODEM_ID_ENUM_UINT16                enModemId;

    AT_InitCommCtx();

    for (enModemId = 0; enModemId < MODEM_ID_BUTT; enModemId++)
    {
        AT_InitModemCtx(enModemId);
    }

    AT_InitClientCtx();

    return;
}

/*****************************************************************************
     : AT_GetModemIDFromPid
   : PIDModemID
   : VOS_UINT32
   : 
     : MODEM_ID_ENUM_UINT16
   :
   :

       :
  1.       : 20150808
           : w00316404
       : 
*****************************************************************************/
MODEM_ID_ENUM_UINT16 AT_GetModemIDFromPid(VOS_UINT32 ulPid)
{
    VOS_UINT32                          ulModemPidTabLen;
    VOS_UINT32                          i;

    ulModemPidTabLen    = (sizeof(g_astAtModemPidTab)/sizeof(AT_MODEM_PID_TAB_STRU));

    for (i = 0; i < ulModemPidTabLen; i++)
    {

        if (ulPid == g_astAtModemPidTab[i].ulModem0Pid)
        {
            return MODEM_ID_0;
        }

        if (ulPid == g_astAtModemPidTab[i].ulModem1Pid)
        {
            return MODEM_ID_1;
        }


    }

    return MODEM_ID_BUTT;
}


/*****************************************************************************
     : AT_GetSystemAppConfigAddr
   : APPNV
   : 
   : 
     : 
   :
   :

      :
 1.       : 20111207
          : s62952
      : 
 2.       : 201335
          : l60609
      : DSDA PHASE III
*****************************************************************************/
VOS_UINT8* AT_GetSystemAppConfigAddr(VOS_VOID)
{
    AT_COMM_CTX_STRU                   *pstCommCtx = VOS_NULL_PTR;

    pstCommCtx = AT_GetCommCtxAddr();

    return &(pstCommCtx->ucSystemAppConfigAddr);
}

/*****************************************************************************
     : AT_GetResetCtxAddr
   : 
   : VOS_VOID
   : 
     : AT_RESET_CTX_STRU*
   :
   :

       :
  1.       : 20130420
           : l60609
       : 

*****************************************************************************/
AT_RESET_CTX_STRU* AT_GetResetCtxAddr(VOS_VOID)
{
    return &(g_stAtResetCtx);
}

/*****************************************************************************
     : AT_GetCommCtxAddr
   : 
   : VOS_VOID
   : 
     : AT_COMM_CTX_STRU*
   :
   :

       :
  1.       : 2013220
           : l60609
       : 

*****************************************************************************/
AT_COMM_CTX_STRU* AT_GetCommCtxAddr(VOS_VOID)
{
    return &(g_stAtCommCtx);
}

/*****************************************************************************
     : AT_GetCommPsCtxAddr
   : PS
   : VOS_VOID
   : 
     : AT_PS_COMM_CTX_STRU*
   :
   :

       :
  1.       : 2013425
           : l60609
       : 

*****************************************************************************/
AT_COMM_PS_CTX_STRU* AT_GetCommPsCtxAddr(VOS_VOID)
{
    return &(g_stAtCommCtx.stPsCtx);
}

/*****************************************************************************
     : AT_GetImsEmcRdpByClientId
   : ClientIdIMS EMC RDP
   : usClientId --- ClientId
   : 
     : AT_IMS_EMC_RDP_STRU*
   :
   :

       :
  1.       : 2017323
           : A00165503
       : 

*****************************************************************************/
AT_IMS_EMC_RDP_STRU* AT_GetImsEmcRdpByClientId(VOS_UINT16 usClientId)
{
    MODEM_ID_ENUM_UINT16                enModemId = MODEM_ID_0;

    if (VOS_OK != AT_GetModemIdFromClient(usClientId, &enModemId))
    {
        AT_ERR_LOG("AT_GetImsEmcRdpByClientId: ClientId is invalid.");
        return VOS_NULL_PTR;
    }

    return &(AT_GetModemPsCtxAddrFromModemId(enModemId)->stImsEmcRdp);
}

/*****************************************************************************
     : AT_GetCommPbCtxAddr
   : 
   : VOS_VOID
   : 
     : AT_COMM_PB_CTX_STRU*
   :
   :

       :
  1.       : 2015312
           : A00165503
       : 
*****************************************************************************/
AT_COMM_PB_CTX_STRU* AT_GetCommPbCtxAddr(VOS_VOID)
{
    return &(g_stAtCommCtx.stCommPbCtx);
}

/*****************************************************************************
     : AT_GetMsgNumCtrlCtxAddr
   : 
   : VOS_VOID
   : 
     : AT_CMD_MSG_NUM_CTRL_STRU*
   :
   :

       :
  1.       : 2016927
           : m00217266
       : 
*****************************************************************************/
AT_CMD_MSG_NUM_CTRL_STRU* AT_GetMsgNumCtrlCtxAddr(VOS_VOID)
{
    return &(g_stAtCommCtx.stMsgNumCtrlCtx);
}

/*****************************************************************************
     : AT_GetModemCtxAddr
   : Modem
   : MODEM_ID_ENUM_UINT16                enModemId
   : 
     : AT_MODEM_CTX_STRU*
   :
   :

       :
  1.       : 2013220
           : l60609
       : 

*****************************************************************************/
AT_MODEM_CTX_STRU* AT_GetModemCtxAddr(
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    return &(g_astAtModemCtx[enModemId]);
}

/*****************************************************************************
     : AT_GetUsimInfoCtxFromModemId
   : MODEM ID
   : MODEM_ID_ENUM_UINT16                enModemId
   : 
     : AT_USIM_INFO_CTX_STRU*
   :
   :

       :
  1.       : 201335
           : l60609
       : 

*****************************************************************************/
AT_USIM_INFO_CTX_STRU* AT_GetUsimInfoCtxFromModemId(
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    return &(g_astAtModemCtx[enModemId].stAtUsimInfoCtx);
}

/*****************************************************************************
     : AT_GetSptRatFromModemId
   : MODEM ID
   : MODEM_ID_ENUM_UINT16                enModemId
   : 
     : AT_MODEM_SPT_RAT_STRU*
   :
   :

       :
  1.       : 201335
           : l60609
       : 

*****************************************************************************/
AT_MODEM_SPT_RAT_STRU* AT_GetSptRatFromModemId(
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    return &(g_astAtModemCtx[enModemId].stPlatformCapList.stPlatformRatList);
}

/* Deleted by s00217060 for ATC, 2013-4-1, begin */

/* Deleted by s00217060 for ATC, 2013-4-1, end */

/*****************************************************************************
     : AT_GetModemCcCtxAddrFromModemId
   : MODEM ID
   : MODEM_ID_ENUM_UINT16                enModemId
   : 
     : AT_MODEM_CC_CTX_STRU*
   :
   :

       :
  1.       : 2013220
           : l60609
       : 

*****************************************************************************/
AT_MODEM_CC_CTX_STRU* AT_GetModemCcCtxAddrFromModemId(
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    return &(g_astAtModemCtx[enModemId].stCcCtx);
}

/*****************************************************************************
     : AT_GetModemCcCtxAddrFromClientId
   : ClientId
   : VOS_UINT16                          usClientId
   : 
     : AT_MODEM_CC_CTX_STRU*
   :
   :

       :
  1.       : 2013220
           : l60609
       : 

*****************************************************************************/
AT_MODEM_CC_CTX_STRU* AT_GetModemCcCtxAddrFromClientId(
    VOS_UINT16                          usClientId
)
{
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT32                          ulRslt;

    enModemId = MODEM_ID_0;

    ulRslt = AT_GetModemIdFromClient((VOS_UINT8)usClientId, &enModemId);

    if (VOS_OK != ulRslt)
    {
        AT_ERR_LOG("AT_GetModemCcCtxAddrFromClientId: Get modem id fail.");
    }

    return &(g_astAtModemCtx[enModemId].stCcCtx);
}

/*****************************************************************************
     : AT_GetModemSsCtxAddrFromModemId
   : MODEM IDSS
   : MODEM_ID_ENUM_UINT16                enModemId
   : 
     : AT_MODEM_SS_CTX_STRU*
   :
   :

       :
  1.       : 2013220
           : l60609
       : 

*****************************************************************************/
AT_MODEM_SS_CTX_STRU* AT_GetModemSsCtxAddrFromModemId(
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    return &(g_astAtModemCtx[enModemId].stSsCtx);
}

/*****************************************************************************
     : AT_GetModemSsCtxAddrFromClientId
   : ClientId
   : VOS_UINT16                          usClientId
   : 
     : AT_MODEM_SS_CTX_STRU*
   :
   :

       :
  1.       : 2013220
           : l60609
       : 

*****************************************************************************/
AT_MODEM_SS_CTX_STRU* AT_GetModemSsCtxAddrFromClientId(
    VOS_UINT16                          usClientId
)
{
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT32                          ulRslt;

    enModemId = MODEM_ID_0;

    ulRslt = AT_GetModemIdFromClient((VOS_UINT8)usClientId, &enModemId);

    if (VOS_OK != ulRslt)
    {
        AT_ERR_LOG("AT_GetModemSsCtxAddrFromClientId: Get modem id fail.");
    }

    return &(g_astAtModemCtx[enModemId].stSsCtx);
}
/*****************************************************************************
     : AT_GetModemSmsCtxAddrFromModemId
   : MODEM ID
   : MODEM_ID_ENUM_UINT16                enModemId
   : 
     : AT_MODEM_SMS_CTX_STRU*
   :
   :

       :
  1.       : 2013220
           : l60609
       : 

*****************************************************************************/
AT_MODEM_SMS_CTX_STRU* AT_GetModemSmsCtxAddrFromModemId(
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    return &(g_astAtModemCtx[enModemId].stSmsCtx);
}

/*****************************************************************************
     : AT_GetModemSmsCtxAddrFromClientId
   : ClientId
   : VOS_UINT16                          usClientId
   : 
     : AT_MODEM_SMS_CTX_STRU*
   :
   :

       :
  1.       : 2013222
           : l60609
       : 

*****************************************************************************/
AT_MODEM_SMS_CTX_STRU* AT_GetModemSmsCtxAddrFromClientId(
    VOS_UINT16                          usClientId
)
{
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT32                          ulRslt;

    enModemId = MODEM_ID_0;

    ulRslt = AT_GetModemIdFromClient((VOS_UINT8)usClientId, &enModemId);

    if (VOS_OK != ulRslt)
    {
        AT_ERR_LOG("AT_GetModemSmsCtxAddrFromClientId: Get modem id fail");
    }

    return &(g_astAtModemCtx[enModemId].stSmsCtx);
}


/*****************************************************************************
     : AT_GetModemNetCtxAddrFromModemId
   : MODEM ID
   : MODEM_ID_ENUM_UINT16                enModemId
   : 
     : AT_MODEM_NET_CTX_STRU*
   :
   :

       :
  1.       : 2013220
           : l60609
       : 

*****************************************************************************/
AT_MODEM_NET_CTX_STRU* AT_GetModemNetCtxAddrFromModemId(
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    return &(g_astAtModemCtx[enModemId].stNetCtx);
}

/*****************************************************************************
     : AT_GetModemNetCtxAddrFromClientId
   : ClientId
   : VOS_UINT16                          usClientId
   : 
     : AT_MODEM_NET_CTX_STRU*
   :
   :

       :
  1.       : 2013222
           : l60609
       : 

*****************************************************************************/
AT_MODEM_NET_CTX_STRU* AT_GetModemNetCtxAddrFromClientId(
    VOS_UINT16                          usClientId
)
{
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT32                          ulRslt;

    enModemId = MODEM_ID_0;

    ulRslt = AT_GetModemIdFromClient((VOS_UINT8)usClientId, &enModemId);

    if (VOS_OK != ulRslt)
    {
        AT_ERR_LOG("AT_GetModemNetCtxAddrFromClientId: Get modem id fail");
    }

    return &(g_astAtModemCtx[enModemId].stNetCtx);
}
/*****************************************************************************
     : AT_GetModemAgpsCtxAddrFromModemId
   : MODEM IDAGPS
   : MODEM_ID_ENUM_UINT16                enModemId
   : 
     : AT_MODEM_AGPS_CTX_STRU*
   :
   :

       :
  1.       : 2013221
           : l60609
       : 

*****************************************************************************/
AT_MODEM_AGPS_CTX_STRU* AT_GetModemAgpsCtxAddrFromModemId(
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    return &(g_astAtModemCtx[enModemId].stAgpsCtx);
}
/*****************************************************************************
     : AT_GetModemAgpsCtxAddrFromClientId
   : ClientIdAGPS
   : VOS_UINT16                          usClientId
   : 
     : AT_MODEM_AGPS_CTX_STRU*
   :
   :

       :
  1.       : 2013221
           : l60609
       : 

*****************************************************************************/
AT_MODEM_AGPS_CTX_STRU* AT_GetModemAgpsCtxAddrFromClientId(
    VOS_UINT16                          usClientId
)
{
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT32                          ulRslt;

    enModemId = MODEM_ID_0;

    ulRslt = AT_GetModemIdFromClient((VOS_UINT8)usClientId, &enModemId);

    if (VOS_OK != ulRslt)
    {
        AT_ERR_LOG("AT_GetModemAgpsCtxAddrFromClientId: Get modem id fail.");
    }

    return &(g_astAtModemCtx[enModemId].stAgpsCtx);
}

/*****************************************************************************
     : AT_GetModemPsCtxAddrFromModemId
   : MODEM IDPSMODEM
   : MODEM_ID_ENUM_UINT16                enModemId
   : 
     : AT_MODEM_PS_CTX_STRU*
   :
   :

       :
  1.       : 2013425
           : l60609
       : 

*****************************************************************************/
AT_MODEM_PS_CTX_STRU* AT_GetModemPsCtxAddrFromModemId(
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    return &(g_astAtModemCtx[enModemId].stPsCtx);
}

/*****************************************************************************
     : AT_GetModemPsCtxAddrFromClientId
   : CLIENT IDPSMODEM
   : MODEM_ID_ENUM_UINT16                enModemId
   : 
     : AT_MODEM_PS_CTX_STRU*
   :
   :

       :
  1.       : 2013425
           : l60609
       : 

*****************************************************************************/
AT_MODEM_PS_CTX_STRU* AT_GetModemPsCtxAddrFromClientId(
    VOS_UINT16                          usClientId
)
{
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT32                          ulRslt;

    enModemId = MODEM_ID_0;

    ulRslt = AT_GetModemIdFromClient((VOS_UINT8)usClientId, &enModemId);

    if (VOS_OK != ulRslt)
    {
        AT_ERR_LOG("AT_GetModemPsCtxAddrFromClientId: Get modem id fail.");
    }

    return &(g_astAtModemCtx[enModemId].stPsCtx);
}

/*****************************************************************************
     : AT_GetModemImsCtxAddrFromModemId
   : MODEM IDIMS
   : MODEM_ID_ENUM_UINT16                enModemId
   : 
     : AT_MODEM_IMS_CONTEXT_STRU*
   :
   :

       :
  1.       : 2016718
           : w00316404
       : 

*****************************************************************************/
AT_MODEM_IMS_CONTEXT_STRU* AT_GetModemImsCtxAddrFromModemId(
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    return &(g_astAtModemCtx[enModemId].stAtImsCtx);
}
/*****************************************************************************
     : AT_GetModemImsCtxAddrFromClientId
   : ClientIdIMS
   : VOS_UINT16                          usClientId
   : 
     : AT_MODEM_IMS_CONTEXT_STRU*
   :
   :

       :
  1.       : 2016718
           : w00316404
       : 

*****************************************************************************/
AT_MODEM_IMS_CONTEXT_STRU* AT_GetModemImsCtxAddrFromClientId(
    VOS_UINT16                          usClientId
)
{
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT32                          ulRslt;

    enModemId = MODEM_ID_0;

    ulRslt = AT_GetModemIdFromClient((VOS_UINT8)usClientId, &enModemId);

    if (VOS_OK != ulRslt)
    {
        AT_ERR_LOG("AT_GetModemImsCtxAddrFromClientId: Get modem id fail.");
    }

    return &(g_astAtModemCtx[enModemId].stAtImsCtx);
}

/*****************************************************************************
     : AT_GetClientCtxAddr
   : 
   : AT_CLIENT_ID_ENUM_UINT16            enClientId
   : 
     : AT_CLIENT_CTX_STRU*
   :
   :

       :
  1.       : 2013220
           : l60609
       : 

*****************************************************************************/
AT_CLIENT_CTX_STRU* AT_GetClientCtxAddr(
    AT_CLIENT_ID_ENUM_UINT16            enClientId
)
{
    return &(g_astAtClientCtx[enClientId]);
}

/*****************************************************************************
     : AT_GetModemIdFromClient
   : AT CLIENT INDEXMODEM ID
   : VOS_UINT16                          usClientId
             MODEM_ID_ENUM_UINT16               *pModemId
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 20121213
           : l60609
       : 

  2.       : 20130313
           : f00179208
       : DSDA PHASE III:

  3.       : 2015527
           : l00198894
       : TSTS
*****************************************************************************/
VOS_UINT32 AT_GetModemIdFromClient(
    VOS_UINT16                          usClientId,
    MODEM_ID_ENUM_UINT16               *pModemId
)
{
    AT_CLIENT_CTX_STRU                 *pstAtClientCtx = VOS_NULL_PTR;

    /* MODEM0client index */
    if ((AT_BROADCAST_CLIENT_INDEX_MODEM_0 == usClientId)
     || (AT_BROADCAST_CLIENT_ID_MODEM_0 == usClientId))
    {
        *pModemId = MODEM_ID_0;
    }
    /* MODEM1client index */
    else if ((AT_BROADCAST_CLIENT_INDEX_MODEM_1 == usClientId)
          || (AT_BROADCAST_CLIENT_ID_MODEM_1 == usClientId))
    {
        *pModemId = MODEM_ID_1;
    }
    /* MODEM2client index */
    else if ((AT_BROADCAST_CLIENT_INDEX_MODEM_2 == usClientId)
          || (AT_BROADCAST_CLIENT_ID_MODEM_2 == usClientId))
    {
        *pModemId = MODEM_ID_2;
    }
    /* client index */
    else
    {
        /* client index  */
        if (usClientId >= AT_CLIENT_BUTT)
        {
            return VOS_ERR;
        }

        pstAtClientCtx = AT_GetClientCtxAddr(usClientId);

        *pModemId = pstAtClientCtx->stClientConfiguration.enModemId;
    }

    /* NVMODEMIDMODEM1 */
    if (*pModemId >= MODEM_ID_BUTT)
    {
        AT_ERR_LOG("AT_GetModemIdFromClient: modem id is invalid");

        *pModemId = MODEM_ID_0;
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
     : AT_GetDestPid
   : PID
   : MN_CLIENT_ID_T                      usClientId
             VOS_UINT32                          ulRcvPid
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 20121217
           : l60609
       : 

  2.       : 2015527
           : l00198894
       : TSTS
*****************************************************************************/
VOS_UINT32 AT_GetDestPid(
    MN_CLIENT_ID_T                      usClientId,
    VOS_UINT32                          ulRcvPid
)
{
    VOS_UINT32                          ulRslt;
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT32                          i;

    enModemId = MODEM_ID_0;

    /* client idModem Id */
    ulRslt = AT_GetModemIdFromClient(usClientId, &enModemId);

    /* modem 1ulRcvPidpid */
    if ((VOS_OK == ulRslt)
     && (MODEM_ID_0 != enModemId))
    {
        for (i = 0; i < (sizeof(g_astAtModemPidTab)/sizeof(AT_MODEM_PID_TAB_STRU)); i++)
        {
            if (ulRcvPid != g_astAtModemPidTab[i].ulModem0Pid)
            {
                continue;
            }

            if (MODEM_ID_1 == enModemId)
            {
                return g_astAtModemPidTab[i].ulModem1Pid;
            }

            if (MODEM_ID_2 == enModemId)
            {
                return g_astAtModemPidTab[i].ulModem2Pid;
            }
        }

        /* PID */
        if (i >= (sizeof(g_astAtModemPidTab)/sizeof(AT_MODEM_PID_TAB_STRU)))
        {
            (VOS_VOID)vos_printf("AT_GetDestPid: usClientId is %d, ulRcvPid is %d no modem1 pid. \r\n", usClientId, ulRcvPid);
        }
    }

    return ulRcvPid;
}

/*****************************************************************************
     : AT_GetRealClientId
   : ModemCilentId
   : MN_CLIENT_ID_T                      usClientId
             VOS_UINT32                          ulPid
   : 
     : MN_CLIENT_ID_T
   :
   :

       :
  1.       : 201331
           : L60609
       : 

  2.       : 2015528
           : l00198894
       : TSTS
*****************************************************************************/
MN_CLIENT_ID_T AT_GetRealClientId(
    MN_CLIENT_ID_T                      usClientId,
    VOS_UINT32                          ulPid
)
{
    MODEM_ID_ENUM_UINT16                enModemId;

    /* PidModemId */
    enModemId = AT_GetModemIDFromPid(ulPid);

    /* ModemIdClientId */
    if (MODEM_ID_0 == enModemId)
    {
        return (usClientId & AT_BROADCAST_CLIENT_ID_MODEM_0);
    }

    if (MODEM_ID_1 == enModemId)
    {
        return (usClientId & AT_BROADCAST_CLIENT_ID_MODEM_1);
    }


    AT_ERR_LOG1("AT_GetRealClientId, enModemId err", enModemId);

    return usClientId;
}

/*****************************************************************************
     : AT_IsModemSupportLte
   : Modem
   : MODEM_ID_ENUM_UINT16                enModemId
             TAF_MMA_RAT_TYPE_ENUM_UINT8         enRat
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 20121227
           : z00220246
       : 
  2.       : 2015410
           : h00313353
       : SysCfg
*****************************************************************************/
VOS_UINT8 AT_IsModemSupportRat(
    MODEM_ID_ENUM_UINT16                enModemId,
    TAF_MMA_RAT_TYPE_ENUM_UINT8         enRat
)
{
    AT_MODEM_SPT_RAT_STRU              *pstSptRatList = VOS_NULL_PTR;

    pstSptRatList = AT_GetSptRatFromModemId(enModemId);
    if (TAF_MMA_RAT_LTE == enRat)
    {
        return pstSptRatList->ucPlatformSptLte;
    }
    if (TAF_MMA_RAT_WCDMA == enRat)
    {
        if ((VOS_TRUE == pstSptRatList->ucPlatformSptWcdma)
         || (VOS_TRUE == pstSptRatList->ucPlatformSptUtralTDD))
        {
            return VOS_TRUE;
        }
        else
        {
            return VOS_FALSE;
        }
    }
    if (TAF_MMA_RAT_GSM == enRat)
    {
        return pstSptRatList->ucPlatformSptGsm;
    }

    return VOS_FALSE;
}

/*****************************************************************************
     : AT_IsModemSupportUtralTDDRat
   : ModemUTRALTDD
   : MODEM_ID_ENUM_UINT16                enModemId
   : 
     : VOS_UINT8
   :
   :

       :
  1.       : 2013822
           : l60609
       : 

*****************************************************************************/
VOS_UINT8 AT_IsModemSupportUtralTDDRat(
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    AT_MODEM_SPT_RAT_STRU              *pstSptRatList = VOS_NULL_PTR;

    pstSptRatList = AT_GetSptRatFromModemId(enModemId);

    return pstSptRatList->ucPlatformSptUtralTDD;
}




/*****************************************************************************
     : AT_GetCsCallErrCause
   : CS
   : VOS_UINT16                          usClientId
   : 
     : TAF_CS_CAUSE_ENUM_UINT32
   :
   :

       :
  1.       : 2013221
           : l60609
       : 

*****************************************************************************/
TAF_CS_CAUSE_ENUM_UINT32 AT_GetCsCallErrCause(
    VOS_UINT16                          usClientId
)
{
    AT_MODEM_CC_CTX_STRU               *pstCcCtx = VOS_NULL_PTR;

    pstCcCtx = AT_GetModemCcCtxAddrFromClientId(usClientId);

    return pstCcCtx->enCsErrCause;
}


/*****************************************************************************
     : AT_UpdateCallErrInfo
   : 
   : VOS_UINT16                          usClientId
             TAF_CS_CAUSE_ENUM_UINT32            enCsErrCause,
             TAF_CALL_ERROR_INFO_TEXT_STRU      *pstErrInfoText
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20161125
           : q00380176
       : 

*****************************************************************************/
VOS_VOID AT_UpdateCallErrInfo(
    VOS_UINT16                          usClientId,
    TAF_CS_CAUSE_ENUM_UINT32            enCsErrCause,
    TAF_CALL_ERROR_INFO_TEXT_STRU      *pstErrInfoText
)
{
    AT_MODEM_CC_CTX_STRU               *pstCcCtx = VOS_NULL_PTR;

    pstCcCtx = AT_GetModemCcCtxAddrFromClientId(usClientId);

    pstCcCtx->enCsErrCause = enCsErrCause;

    TAF_MEM_SET_S(&(pstCcCtx->stErrInfoText),
                  (VOS_SIZE_T)sizeof(pstCcCtx->stErrInfoText),
                  0x00,
                  (VOS_SIZE_T)sizeof(pstCcCtx->stErrInfoText));

    if (VOS_NULL_PTR != pstErrInfoText)
    {
        if (0 < pstErrInfoText->ucTextLen)
        {
            pstCcCtx->stErrInfoText.ucTextLen = TAF_MIN(pstErrInfoText->ucTextLen, TAF_CALL_ERROR_INFO_TEXT_STRING_SZ);

            TAF_MEM_CPY_S(pstCcCtx->stErrInfoText.acErrInfoText,
                          (VOS_SIZE_T)sizeof(pstCcCtx->stErrInfoText.acErrInfoText),
                          pstErrInfoText->acErrInfoText,
                          pstCcCtx->stErrInfoText.ucTextLen);
        }
    }

    return;
}
 
/*****************************************************************************
     : AT_GetCallErrInfoText
   : 
   : VOS_UINT16                          usClientId
   : 
     : TAF_CALL_ERROR_INFO_TEXT_STRU * stErrInfoText
   :
   :

       :
  1.       : 20124
           : q00380176
       : 

*****************************************************************************/
TAF_CALL_ERROR_INFO_TEXT_STRU * AT_GetCallErrInfoText(
    VOS_UINT16                          usClientId
)
{
    return &(AT_GetModemCcCtxAddrFromClientId(usClientId)->stErrInfoText);
}

/*****************************************************************************
     : AT_GetAbortCmdPara
   : AT
   : 
     : AT
   :
   :

       :
  1.       : 2012922
           : lijun 00171473
       :  for V7R1C50_At_Abort

  2.       : 20131018
           : w00242748
       : 
*****************************************************************************/
AT_ABORT_CMD_PARA_STRU* AT_GetAbortCmdPara(VOS_VOID)
{
    return &(gstAtAbortCmdCtx.stAtAbortCmdPara);
}

/*****************************************************************************
     : AT_GetAbortRspStr
   : AT
   : 
     : AT, \0
   :
   :

       :
  1.       : 2012922
           : lijun 00171473
       :  for V7R1C50_At_Abort

  2.       : 20131018
           : w00242748
       : 
*****************************************************************************/
VOS_UINT8* AT_GetAbortRspStr(VOS_VOID)
{
    return (gstAtAbortCmdCtx.stAtAbortCmdPara.aucAbortAtRspStr);
}


/*****************************************************************************
     : AT_GetSsCustomizePara
   : SS 
   : AT_SS_CUSTOMIZE_TYPE_UINT8 enSsCustomizeType   
   : 
     : VOS_UINT32
                VOS_FALSE       
                VOS_TRUE        
   :
   :

       :
  1.       : 20130124
           : f62575
       : DTS2013012408620, SSSS-STATUS

*****************************************************************************/
VOS_UINT32 AT_GetSsCustomizePara(AT_SS_CUSTOMIZE_TYPE_UINT8 enSsCustomizeType)
{
    VOS_UINT8                           ucMask;

    if (VOS_TRUE != g_stAtSsCustomizePara.ucStatus)
    {
        return VOS_FALSE;
    }

    ucMask = (VOS_UINT8)((VOS_UINT32)AT_SS_CUSTOMIZE_SERVICE_MASK << enSsCustomizeType);
    if (0 != (g_stAtSsCustomizePara.ucSsCmdCustomize & ucMask))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;

}

/*****************************************************************************
     : AT_GetResetSem
   : AT
   : 
   : 
     : AT
   :
   :

      :
 1.       : 20130417
          : f00179208
      : 
*****************************************************************************/
VOS_SEM AT_GetResetSem(VOS_VOID)
{
    return g_stAtResetCtx.hResetSem;
}

/*****************************************************************************
     : AT_GetResetFlag
   : AT
   : 
   : 
     : AT
   :
   :

      :
 1.       : 20130417
          : f00179208
      : 
*****************************************************************************/
VOS_UINT32 AT_GetResetFlag(VOS_VOID)
{
    return g_stAtResetCtx.ulResetingFlag;
}

/*****************************************************************************
     : AT_SetResetFlag
   : AT
   : 
   : 
     : 
   :
   :

      :
 1.       : 20130417
          : f00179208
      : 
*****************************************************************************/
VOS_VOID AT_SetResetFlag(VOS_UINT32 ulFlag)
{
    g_stAtResetCtx.ulResetingFlag = ulFlag;
    return;
}


/*****************************************************************************
     : AT_GetModemPrivacyFilterCtxAddrFromModemId
   : MODEM ID
   : MODEM_ID_ENUM_UINT16                enModemId
   : 
     : AT_MODEM_PRIVACY_FILTER_CTX_STRU *
   :
   :

       :
  1.       : 20160701
           : f00179208
       : 
*****************************************************************************/
AT_MODEM_PRIVACY_FILTER_CTX_STRU* AT_GetModemPrivacyFilterCtxAddrFromModemId(
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    return &(g_astAtModemCtx[enModemId].stFilterCtx);
}

/*****************************************************************************
     : AT_GetModemCdmaModemSwitchCtxAddrFromModemId
   : MODEM ID
   : MODEM_ID_ENUM_UINT16                enModemId
   : 
     : AT_MODEM_CDMAMODEMSWITCH_CTX_STRU *
   :
   :

       :
  1.       : 20161027
           : h00313353
       : 
*****************************************************************************/
AT_MODEM_CDMAMODEMSWITCH_CTX_STRU* AT_GetModemCdmaModemSwitchCtxAddrFromModemId(
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    return &(g_astAtModemCtx[enModemId].stCdmaModemSwitchCtx);
}

/*****************************************************************************
     : AT_GetModemMtInfoCtxAddrFromModemId
   : MODEM IDAGPS
   : MODEM_ID_ENUM_UINT16                enModemId
   : 
     : AT_MODEM_MT_INFO_CTX_STRU*
   :
   :

       :
  1.       : 2013530
           : z60575
       : 

*****************************************************************************/
AT_MODEM_MT_INFO_CTX_STRU* AT_GetModemMtInfoCtxAddrFromModemId(
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    return &(g_astAtModemCtx[enModemId].stMtInfoCtx);
}

/*****************************************************************************
     : AT_InitTraceMsgTab
   : 
   : VOS_VOID
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20131107
           : j00174725
       : 
*****************************************************************************/
VOS_VOID AT_InitTraceMsgTab(VOS_VOID)
{
    TAF_MEM_SET_S(g_stAtTraceMsgIdTab, sizeof(g_stAtTraceMsgIdTab), 0xFF, sizeof(g_stAtTraceMsgIdTab));
}

/*****************************************************************************
     : AT_GetResultMsgID
   :  Result MSG ID
   : ucIndex   -- client ID 
   : 
     : AT_INTER_MSG_ID_ENUM_UINT32 -- result msg id
   :
   :

       :
  1.       : 20131107
           : j00174725
       : 

  2.       : 2015527
           : l00198894
       : TSTS
*****************************************************************************/
AT_INTER_MSG_ID_ENUM_UINT32 AT_GetResultMsgID(VOS_UINT8 ucIndex)
{
    AT_INTER_MSG_ID_ENUM_UINT32         enResultMsgID;

    if (AT_BROADCAST_CLIENT_INDEX_MODEM_0 == ucIndex)
    {
        enResultMsgID = ID_AT_MNTN_RESULT_BROADCAST_MODEM_0;
    }
    else if (AT_BROADCAST_CLIENT_INDEX_MODEM_1 == ucIndex)
    {
        enResultMsgID = ID_AT_MNTN_RESULT_BROADCAST_MODEM_1;
    }
    else if (AT_BROADCAST_CLIENT_INDEX_MODEM_2 == ucIndex)
    {
        enResultMsgID = ID_AT_MNTN_RESULT_BROADCAST_MODEM_2;
    }
    else
    {
        enResultMsgID = g_stAtTraceMsgIdTab[ucIndex].enResultMsgID;
    }

    return enResultMsgID;
}

/*****************************************************************************
     : AT_GetCmdMsgID
   :  CMD MSG ID
   : ucIndex   -- client ID 
   : 
     : AT_INTER_MSG_ID_ENUM_UINT32 --cmd msg ID
   :
   :

       :
  1.       : 20131107
           : j00174725
       : 
*****************************************************************************/
AT_INTER_MSG_ID_ENUM_UINT32 AT_GetCmdMsgID(VOS_UINT8 ucIndex)
{
    return g_stAtTraceMsgIdTab[ucIndex].enCmdMsgID;
}

/*****************************************************************************
     : AT_ConfigTraceMsg
   : 
   : ucIndex       - 
             enCmdMsgId    - 
             enResultMsgId - 
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20131107
           : j00174725
       : 
*****************************************************************************/
VOS_VOID AT_ConfigTraceMsg(
    VOS_UINT8                           ucIndex,
    AT_INTER_MSG_ID_ENUM_UINT32         enCmdMsgId,
    AT_INTER_MSG_ID_ENUM_UINT32         enResultMsgId
)
{
    g_stAtTraceMsgIdTab[ucIndex].enCmdMsgID = enCmdMsgId;
    g_stAtTraceMsgIdTab[ucIndex].enResultMsgID = enResultMsgId;

    return;
}

/*****************************************************************************
     : At_SetAtCmdAbortTickInfo
   : ATtick
   : ucIndex   : 
             ulTick    : tick
   : 
     : 
   :
   :

       :
  1.       : 20131018
           : w00242748
       : 

*****************************************************************************/
VOS_VOID At_SetAtCmdAbortTickInfo(
    VOS_UINT8                           ucIndex,
    VOS_UINT32                          ulTick
)
{
    gstAtAbortCmdCtx.stCmdAbortTick.ulAtSetTick[ucIndex]    = ulTick;

    return;
}

/*****************************************************************************
     : At_GetAtCmdAbortTickInfo
   : ATTick
   : 
   : 
     : AT_CMD_ABORT_TICK_INFO 
   :
   :

       :
  1.       : 20131018
           : w00242748
       : 

*****************************************************************************/
AT_CMD_ABORT_TICK_INFO* At_GetAtCmdAbortTickInfo(VOS_VOID)
{
    return &(gstAtAbortCmdCtx.stCmdAbortTick);
}

/*****************************************************************************
     : At_GetAtCmdAnyAbortFlg
   : 
   : 
   : 
     : 
   :
   :

       :
  1.       : 20131018
           : w00242748
       : 

*****************************************************************************/
VOS_UINT8 At_GetAtCmdAnyAbortFlg(VOS_VOID)
{
    return (gstAtAbortCmdCtx.stAtAbortCmdPara.ucAnyAbortFlg);
}

/*****************************************************************************
     : At_SetAtCmdAnyAbortFlg
   : 
   : ucFlg    : 
   : 
     : 
   :
   :

       :
  1.       : 20131018
           : w00242748
       : 

*****************************************************************************/
VOS_VOID At_SetAtCmdAnyAbortFlg(
    VOS_UINT8                           ucFlg
)
{
    gstAtAbortCmdCtx.stAtAbortCmdPara.ucAnyAbortFlg = ucFlg;

    return;
}

/*****************************************************************************
     : AT_GetUartCtxAddr
   : UART
   : VOS_VOID
   : 
     : AT_COMM_CTX_STRU*
   :
   :

       :
  1.       : 20130921
           : j00174725
       : 
*****************************************************************************/
AT_UART_CTX_STRU* AT_GetUartCtxAddr(VOS_VOID)
{
    return &(g_stAtCommCtx.stUartCtx);
}

/*****************************************************************************
     : AT_GetUartRiCfgInfo
   : UART
   : VOS_VOID
   : 
     : AT_UART_PHY_CFG_STRU*
   :
   :

       :
  1.       : 20130921
           : A00165503
       : 
*****************************************************************************/
AT_UART_PHY_CFG_STRU* AT_GetUartPhyCfgInfo(VOS_VOID)
{
    return &(AT_GetUartCtxAddr()->stPhyConfig);
}

/*****************************************************************************
     : AT_GetUartLineCtrlInfo
   : UART
   : VOS_VOID
   : 
     : AT_UART_LINE_CTRL_STRU*
   :
   :

       :
  1.       : 20130921
           : A00165503
       : 
*****************************************************************************/
AT_UART_LINE_CTRL_STRU* AT_GetUartLineCtrlInfo(VOS_VOID)
{
    return &(AT_GetUartCtxAddr()->stLineCtrl);
}

/*****************************************************************************
     : AT_GetUartFlowCtrlInfo
   : UART
   : VOS_VOID
   : 
     : AT_UART_FLOW_CTRL_STRU*
   :
   :

       :
  1.       : 20130921
           : A00165503
       : 
*****************************************************************************/
AT_UART_FLOW_CTRL_STRU* AT_GetUartFlowCtrlInfo(VOS_VOID)
{
    return &(AT_GetUartCtxAddr()->stFlowCtrl);
}

/*****************************************************************************
     : AT_GetUartRiCfgInfo
   : UARTRING
   : VOS_VOID
   : 
     : AT_UART_RI_CFG_STRU*
   :
   :

       :
  1.       : 20130921
           : A00165503
       : 
*****************************************************************************/
AT_UART_RI_CFG_STRU* AT_GetUartRiCfgInfo(VOS_VOID)
{
    return &(AT_GetUartCtxAddr()->stRiConfig);
}

/*****************************************************************************
     : AT_GetUartRiStateInfo
   : UARTRING
   : VOS_VOID
   : 
     : AT_UART_RI_STATE_INFO_STRU*
   :
   :

       :
  1.       : 20130921
           : A00165503
       : 
*****************************************************************************/
AT_UART_RI_STATE_INFO_STRU* AT_GetUartRiStateInfo(VOS_VOID)
{
    return &(AT_GetUartCtxAddr()->stRiStateInfo);
}

/*****************************************************************************
     : AT_GetPortBuffCfgInfo
   : 
   : VOS_VOID
   : 
     : AT_COMM_CTX_STRU*
   :
   :

       :
  1.       : 20130921
           : j00174725
       : 
*****************************************************************************/
AT_PORT_BUFF_CFG_STRU* AT_GetPortBuffCfgInfo(VOS_VOID)
{
    return &(AT_GetCommCtxAddr()->stPortBuffCfg);
}

/*****************************************************************************
     : AT_GetPortBuffCfg
   : NV
   : VOS_VOID
   : VOS_VOID
     : AT_SMS_BUFF_CFG_ENUM_UINT8
   :
   :

       :
  1.       : 20131228
           : j00174725
       : HSUART PHASE III
*****************************************************************************/
AT_PORT_BUFF_CFG_ENUM_UINT8  AT_GetPortBuffCfg(VOS_VOID)
{
    AT_COMM_CTX_STRU                   *pstCommCtx = VOS_NULL_PTR;

    pstCommCtx = AT_GetCommCtxAddr();

    return pstCommCtx->stPortBuffCfg.enSmsBuffCfg;
}

/*****************************************************************************
     : AT_InitPortBuffCfg
   : clientID
   : VOS_VOID
   : VOS_VOID
     : VOS_VOID
   :
   :

       :
  1.       : 20131228
           : j00174725
       : HSUART PHASE III
*****************************************************************************/
VOS_VOID AT_InitPortBuffCfg(VOS_VOID)
{
    AT_PORT_BUFF_CFG_STRU              *pstUsedClientIdTab = VOS_NULL_PTR;

    pstUsedClientIdTab = AT_GetPortBuffCfgInfo();

    TAF_MEM_SET_S(pstUsedClientIdTab, sizeof(AT_PORT_BUFF_CFG_STRU), 0xFF, sizeof(AT_PORT_BUFF_CFG_STRU));

    pstUsedClientIdTab->ucNum = 0;
}

/*****************************************************************************
     : AT_AddUsedClientId2Tab
   : clientID
   : usClientId
   : VOS_VOID
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
VOS_VOID AT_AddUsedClientId2Tab(VOS_UINT16 usClientId)
{
    AT_PORT_BUFF_CFG_STRU              *pstPortBuffCfg = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;

    if (usClientId >= AT_MAX_CLIENT_NUM)
    {
        return;
    }

    pstPortBuffCfg = AT_GetPortBuffCfgInfo();

    /*   */
    if ( (usClientId >= AT_MIN_APP_CLIENT_ID)
      && (usClientId <= AT_MAX_APP_CLIENT_ID))
    {
        return;
    }


    if (pstPortBuffCfg->ucNum >= AT_MAX_CLIENT_NUM)
    {
        pstPortBuffCfg->ucNum = AT_MAX_CLIENT_NUM -1;
    }

    /*  */
    for (ucIndex = 0; ucIndex < pstPortBuffCfg->ucNum; ucIndex++)
    {
        if (usClientId == pstPortBuffCfg->ulUsedClientID[ucIndex])
        {
            return;
        }
    }

    /*  */
    if (ucIndex == pstPortBuffCfg->ucNum)
    {
        pstPortBuffCfg->ulUsedClientID[ucIndex] = (VOS_UINT32)usClientId;
        pstPortBuffCfg->ucNum++;
    }
}

/*****************************************************************************
     : AT_RmUsedClientIdFromTab
   : ClientID
   : usClientId
   : VOS_VOID
     : VOS_VOID
   :
   :

       :
  1.       : 20131228
           : j00174725
       : HSUART PHASE III
*****************************************************************************/
VOS_VOID AT_RmUsedClientIdFromTab(VOS_UINT16 usClientId)
{
    AT_PORT_BUFF_CFG_STRU              *pstPortBuffCfg = VOS_NULL_PTR;
    VOS_UINT32                          ulIndex;

    pstPortBuffCfg = AT_GetPortBuffCfgInfo();

    if (pstPortBuffCfg->ucNum > AT_MAX_CLIENT_NUM)
    {
        pstPortBuffCfg->ucNum = AT_MAX_CLIENT_NUM;
    }

    /*  */
    for (ulIndex = 0; ulIndex < pstPortBuffCfg->ucNum; ulIndex++)
    {
        if (usClientId == pstPortBuffCfg->ulUsedClientID[ulIndex])
        {
            break;
        }
    }

    /*  */
    if (ulIndex == pstPortBuffCfg->ucNum)
    {
        return;
    }

    /* client */
    if (ulIndex == pstPortBuffCfg->ucNum - 1)
    {
        pstPortBuffCfg->ucNum--;
        pstPortBuffCfg->ulUsedClientID[ulIndex] = VOS_NULL_DWORD;

    }
    else
    {
        pstPortBuffCfg->ulUsedClientID[ulIndex] =
                    pstPortBuffCfg->ulUsedClientID[pstPortBuffCfg->ucNum - 1];
        pstPortBuffCfg->ulUsedClientID[pstPortBuffCfg->ucNum - 1] = VOS_NULL_DWORD;
        pstPortBuffCfg->ucNum--;
    }
}


/*****************************************************************************
     : AT_GetClientConfig
   : ClientConfig
   : VOS_VOID
   : 
     : AT_CLIENT_CONFIGURATION_STRU*
   :
   :

       :
  1.       : 2014425
           : f00179208
       : 

*****************************************************************************/
AT_CLIENT_CONFIGURATION_STRU* AT_GetClientConfig(
    AT_CLIENT_ID_ENUM_UINT16            enClientId
)
{
    return &(AT_GetClientCtxAddr(enClientId)->stClientConfiguration);
}

/*****************************************************************************
     : AT_GetClientCfgMapTbl
   : CLIENT CFG TAB
   : VOS_VOID
   : 
     : AT_CLIENT_CFG_MAP_TAB_STRU*
   :
   :

       :
  1.       : 2014425
           : f00179208
       : 

*****************************************************************************/
AT_CLIENT_CFG_MAP_TAB_STRU* AT_GetClientCfgMapTbl(VOS_UINT8 ucIndex)
{
    return &(g_astAtClientCfgMapTbl[ucIndex]);
}


/*****************************************************************************
     : AT_GetPrivacyFilterEnableFlg
   : NV
   : 
   : 
     : VOS_UINT8 : 
   :
   :

       :
  1.       : 20160701
           : f00179208
       : 
*****************************************************************************/
VOS_UINT8 AT_GetPrivacyFilterEnableFlg(VOS_VOID)
{
    return AT_GetModemPrivacyFilterCtxAddrFromModemId(MODEM_ID_0)->ucFilterEnableFlg;
}

/*****************************************************************************
     : AT_IsSupportReleaseRst
   : Rx
   : enReleaseType   
   : 
     : VOS_UINT8
   :
   :

      :
 1.       : 20151020
          : w00316404
      : 

 2.       : 20161118
          : wx270776
      : DTS2016110401052
*****************************************************************************/
VOS_UINT8 AT_IsSupportReleaseRst(
    AT_ACCESS_STRATUM_REL_ENUM_UINT8    enReleaseType
)
{
    if (enReleaseType <= g_stReleaseInfo.enAccessStratumRel)
    {
        return VOS_TRUE;
    }
    return VOS_FALSE;
}

/*****************************************************************************
     : AT_GetModemCLModeCtxAddrFromModemId
   : MODEM IDCL mode
   : MODEM_ID_ENUM_UINT16                enModemId
   : 
     : AT_MODEM_SMS_CTX_STRU*
   :
   :

       :
  1.       : 20151027
           : f00279542
       : 

*****************************************************************************/
VOS_UINT8* AT_GetModemCLModeCtxAddrFromModemId(
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    return &(g_astAtModemCtx[enModemId].stPlatformCapList.ucIsCLMode);
}

/*****************************************************************************
     : AT_GetCgpsCLockEnableFlgByModemId
   : MODEM IDAT^CGPSCLOCK
   : MODEM_ID_ENUM_UINT16       enModemId
   : 
     : VOS_UINT8
   :
   :

       :
  1.       : 2016711
           : wx270776
       : 

*****************************************************************************/
VOS_UINT8 AT_GetCgpsCLockEnableFlgByModemId(
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    return g_astAtModemCtx[enModemId].stAgpsCtx.ucAtCgpsClockEnableFlag;
}

/*****************************************************************************
     : AT_SetCgpsCLockEnableFlgByModemId
   : MODEM IDAT^CGPSCLOCK
   : MODEM_ID_ENUM_UINT16       enModemId
   : 
     : 
   :
   :

       :
  1.       : 2016711
           : wx270776
       : 

*****************************************************************************/
VOS_VOID AT_SetCgpsCLockEnableFlgByModemId(
    MODEM_ID_ENUM_UINT16                enModemId,
    VOS_UINT8                           ucEnableFLg
)
{
    g_astAtModemCtx[enModemId].stAgpsCtx.ucAtCgpsClockEnableFlag = ucEnableFLg;
}

