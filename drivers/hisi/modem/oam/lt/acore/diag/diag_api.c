
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
  1 Include HeadFile
*****************************************************************************/
#include  "vos.h"
#include  "diag_common.h"
#include  "SCMProc.h"
#include  "diag_api.h"
#include  "diag_cfg.h"
#include  "msp_diag.h"
#include  "msp_errno.h"
#include  "diag_debug.h"
#include  "mdrv.h"
#include  "soc_socp_adapter.h"
#include  "LNvCommon.h"
#include  "LPsNvInterface.h"


#define    THIS_FILE_ID        MSP_FILE_ID_DIAG_API_C
/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/

extern VOS_UINT8 g_EventModuleCfg[DIAG_CFG_PID_NUM];

VOS_UINT32 diag_CheckMsgPara(DIAG_AIR_MSG_LOG_STRU* pstRptMessage);
VOS_UINT32 diag_GetLayerMsgCfg(VOS_UINT32 ulCatId, VOS_UINT32 ulMsgId);
VOS_UINT32 diag_GetLayerSrcCfg(VOS_UINT32 ulModuleId);
VOS_UINT32 diag_GetLayerDstCfg(VOS_UINT32 ulModuleId);
VOS_UINT32 diag_GetLayerCfg(VOS_UINT32 ulSrcModuleId, VOS_UINT32 ulDstModuleId, VOS_UINT32 ulMsgId);
VOS_UINT32 diag_GetPrintCfg(VOS_UINT32 ulModuleId, VOS_UINT32 ulLevel);

VOS_UINT32 g_ulTransId = 0;

DIAG_LOG_PKT_NUM_ACC_STRU g_DiagLogPktNum ={0};
DIAG_TraceFilterFunc g_pFilterFunc = VOS_NULL;
DIAG_TraceMatchFunc  g_pMatchFunc  = VOS_NULL;


/*****************************************************************************
  3 Function
*****************************************************************************/

/*****************************************************************************
 Function Name   : DIAG_GetConnState
 Description     : 
 Return          : 1:connect; 0:disconnect

 History         :
    1.c00326366      2015-6-24  Draft Enact
*****************************************************************************/
VOS_UINT32 DIAG_GetConnState(VOS_VOID)
{
    return (VOS_UINT32)((DIAG_IS_CONN_ON)?1:0);
}


/*****************************************************************************
 Function Name   : diag_GetMsgCfg
 Description     : 
 Input           :VOS_UINT32 ulCatId
                VOS_UINT32 ulMsgId
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.w00182550      2012-12-5  Draft Enact

*****************************************************************************/
VOS_UINT32 diag_GetLayerMsgCfg(VOS_UINT32 ulCatId, VOS_UINT32 ulMsgId)
{
    DIAG_CFG_LOG_CAT_MSG_CFG_STRU *pstItemCfg =NULL;
    VOS_UINT32 i;

    for(i = 0 ; i < g_stMsgCfg.ulCfgCnt; i++)
    {
       pstItemCfg = (g_stMsgCfg.astMsgCfgList + i);

       if(ulMsgId == pstItemCfg->ulId )
       {
           if(DIAG_CFG_SWT_CLOSE == pstItemCfg->ulSwt)
           {
              return ERR_MSP_CFG_LOG_NOT_ALLOW;
           }
           else if(DIAG_CFG_SWT_OPEN == pstItemCfg->ulSwt)
           {
              return ERR_MSP_SUCCESS;
           }
           else
           {
              return ERR_MSP_DIAG_MSG_CFG_NOT_SET;
           }
       }
    }

    return ERR_MSP_DIAG_MSG_CFG_NOT_SET;
}


VOS_UINT32 diag_GetLayerSrcCfg(VOS_UINT32 ulModuleId)
{
    VOS_UINT32 ulOffset = 0;

    if(DOPRA_PID_TIMER == ulModuleId)
    {
        return ERR_MSP_SUCCESS;
    }

    if(DIAG_CFG_LAYER_MODULE_IS_ACORE(ulModuleId))
    {
        ulOffset = DIAG_CFG_LAYER_MODULE_ACORE_OFFSET(ulModuleId);

        if(DIAG_CFG_SWT_OPEN == g_ALayerSrcModuleCfg[ulOffset])
        {
            return ERR_MSP_SUCCESS;
        }
    }
    else if(DIAG_CFG_LAYER_MODULE_IS_CCORE(ulModuleId))
    {
        ulOffset = DIAG_CFG_LAYER_MODULE_CCORE_OFFSET(ulModuleId);

        if(DIAG_CFG_SWT_OPEN == g_CLayerSrcModuleCfg[ulOffset])
        {
            return ERR_MSP_SUCCESS;
        }
    }

    return ERR_MSP_CFG_LOG_NOT_ALLOW;
}

VOS_UINT32 diag_GetLayerDstCfg(VOS_UINT32 ulModuleId)
{
    VOS_UINT32 ulOffset = 0;

    if(DIAG_CFG_LAYER_MODULE_IS_ACORE(ulModuleId))
    {
        ulOffset = DIAG_CFG_LAYER_MODULE_ACORE_OFFSET(ulModuleId);

        if(DIAG_CFG_SWT_OPEN == g_ALayerDstModuleCfg[ulOffset])
        {
            return  ERR_MSP_SUCCESS;
        }
    }
    else if(DIAG_CFG_LAYER_MODULE_IS_CCORE(ulModuleId))
    {
        ulOffset = DIAG_CFG_LAYER_MODULE_CCORE_OFFSET(ulModuleId);

        if(DIAG_CFG_SWT_OPEN == g_CLayerDstModuleCfg[ulOffset])
        {
            return  ERR_MSP_SUCCESS;
        }
    }

    return ERR_MSP_CFG_LOG_NOT_ALLOW;
}

/*****************************************************************************
 Function Name   : diag_GetLayerCfg
 Description     : 
 Input           :VOS_UINT32 ulSrcModuleId
                VOS_UINT32 ulDstModuleId
                VOS_UINT32 ulMsgId
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.w00182550      2012-12-5  Draft Enact

*****************************************************************************/
VOS_UINT32 diag_GetLayerCfg(VOS_UINT32 ulSrcModuleId, VOS_UINT32 ulDstModuleId, VOS_UINT32 ulMsgId)
{
    VOS_UINT32 ret = ERR_MSP_CFG_LOG_NOT_ALLOW;
    VOS_UINT32 ret2 = ERR_MSP_CFG_LOG_NOT_ALLOW;
    VOS_UINT32 ulMsgCfg;

    /*IDID*/
    ulMsgCfg = diag_GetLayerMsgCfg(DIAG_CMD_LOG_CATETORY_LAYER_ID, ulMsgId);
    if(ERR_MSP_DIAG_MSG_CFG_NOT_SET == ulMsgCfg )
    {
        ret = diag_GetLayerSrcCfg(ulSrcModuleId);
        ret2 = diag_GetLayerDstCfg(ulDstModuleId);
        if((ERR_MSP_SUCCESS != ret) && (ERR_MSP_SUCCESS != ret2))
        {
            return ERR_MSP_CFG_LOG_NOT_ALLOW;
        }
        else
        {
            return ERR_MSP_SUCCESS;
        }
    }
    else if(ERR_MSP_SUCCESS == ulMsgCfg )
    {
        return ERR_MSP_SUCCESS;
    }
    else
    {
        return ERR_MSP_CFG_LOG_NOT_ALLOW;
    }
}

/*****************************************************************************
 Function Name   : diag_GetPrintCfg
 Description     : 
 Input           :VOS_UINT32 ulModuleId
                VOS_UINT32 ulLevel
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.w00182550      2012-12-6  Draft Enact

*****************************************************************************/
VOS_UINT32 diag_GetPrintCfg(VOS_UINT32 ulModuleId, VOS_UINT32 ulLevel)
{
    VOS_UINT32 ulLevelFilter = 0;
    VOS_UINT32 ulTmp = 0;

    if((PS_LOG_LEVEL_OFF == ulLevel)||(ulLevel >= PS_LOG_LEVEL_BUTT))
    {
        diag_LNR(EN_DIAG_LNR_LOG_LOST, ulLevel, 0xAAAAAAAA);/* [false alarm]:alarm */
        return ERR_MSP_CFG_LOG_NOT_ALLOW;
    }

    /* LEVELMSPHSOLEVEL */
    /*
        TOOL        <->     MSP     <->     PS
        0x40000000  <->     0x40    <->     1 (ERROR);
        0x20000000  <->     0x20    <->     2 (WARNING);
        0x10000000  <->     0x10    <->     3 (NORMAL);
        0x08000000  <->     0x08    <->     4 (INFO)
    */

    ulLevelFilter = ((VOS_UINT32)1<<(7-ulLevel));

    ulTmp = (ulLevelFilter << 16) | g_PrintTotalCfg;

    /* */
    if(DIAG_CFG_PRINT_TOTAL_MODULE_SWT_NOT_USE != g_PrintTotalCfg)
    {
        if(ulLevelFilter & g_PrintTotalCfg)
        {
            return ERR_MSP_SUCCESS;
        }
        else
        {
            diag_LNR(EN_DIAG_LNR_LOG_LOST, ulTmp, ulModuleId);
            return ERR_MSP_CFG_LOG_NOT_ALLOW;
        }
    }
    else
    {
        /**/
        if(DIAG_CFG_MODULE_IS_INVALID((VOS_INT32)ulModuleId))
        {
            diag_LNR(EN_DIAG_LNR_LOG_LOST, ulModuleId, 0xBBBBBBBB);/* [false alarm]:alarm */
            return  ERR_MSP_CFG_LOG_NOT_ALLOW;
        }

        ulTmp = (ulLevelFilter << 16) | g_PrintModuleCfg[ulModuleId - VOS_PID_DOPRAEND];

        if(ulLevelFilter & g_PrintModuleCfg[ulModuleId - VOS_PID_DOPRAEND])
        {
            return ERR_MSP_SUCCESS;
        }
        else
        {
            diag_LNR(EN_DIAG_LNR_LOG_LOST, ulTmp, ulModuleId);
            return ERR_MSP_CFG_LOG_NOT_ALLOW;
        }
    }
}


#define LTE_DIAG_PRINTF_LEN             (256+sizeof(VOS_UINT32)+sizeof(VOS_UINT32))




/******************************************************************************
: DIAG_LogIdReport
: 
:
            ulModuleId[in]  : ( 31-24:modemid,23-16:modeid,15-12:level )
            ulPid[in]       : PID
            ulLogId[in]     : DIAG_LOG_ID
            amount[in]      : ulModuleId/ulLevel/ulLogId/amout
            ...             : 
:
            1. 
            2. amount
            3. int
            4. 6
******************************************************************************/
VOS_INT32 DIAG_LogIdReport(VOS_UINT32 ulModuleId, VOS_UINT32 ulPid,
                        VOS_UINT32 ulLogId, VOS_UINT32 amount, ...)
{
    VOS_UINT32 ret = ERR_MSP_SUCCESS;
    VOS_UINT32 ulDataLength =0;
    VOS_CHAR ucDiagPrintData[LTE_DIAG_PRINTF_LEN]={0};
    VOS_INT32 val, i, lTmpLen, lSpareLen, lOccupyLen;
    va_list vl;
    VOS_UINT32 paranum;

    DIAG_MSG_REPORT_HEAD_STRU stDiagHead;

    /* */
    DIAG_DEBUG_SDM_FUN(EN_SDM_DIAG_DOT, ulLogId, 0, 0);

    if(!DIAG_IS_POLOG_ON)
    {
        /*DIAGHSO*/
        if(!DIAG_IS_CONN_ON)
        {
            DIAG_DEBUG_SDM_FUN(EN_SDM_DIAG_DOT_ERR, ERR_MSP_NO_INITILIZATION, ulLogId, 1);
            return ERR_MSP_NO_INITILIZATION;
        }

        ret = diag_GetPrintCfg(ulPid, DIAG_GET_PRINTF_LEVEL(ulModuleId));
        if(ERR_MSP_SUCCESS != ret)
        {
            DIAG_DEBUG_SDM_FUN(EN_SDM_DIAG_DOT_ERR, ERR_MSP_UNAVAILABLE, ulLogId, 2);
            return ERR_MSP_UNAVAILABLE;
        }
    }
    *((VOS_UINT32*)ucDiagPrintData) = ulPid;
    *(VOS_UINT32*)(ucDiagPrintData + sizeof(VOS_UINT32)) = DIAG_GET_PRINTF_LEVEL(ulModuleId);

    lOccupyLen = 8;

    lSpareLen  = (VOS_INT32)LTE_DIAG_PRINTF_LEN - lOccupyLen;

    lTmpLen    = VOS_nsprintf_s(ucDiagPrintData + lOccupyLen, (VOS_UINT32)lSpareLen, (VOS_UINT32)lSpareLen-1, "%d, ", ulLogId);
  
    if(!(0 <= lTmpLen)) 
    {
        vos_printf("LTE_LOG_ASSERT %d.\n", __LINE__); 
        return -1; 
    }
    lOccupyLen += lTmpLen;   
    if(!(LTE_DIAG_PRINTF_LEN >= (VOS_UINT32)lOccupyLen)) 
    {
        vos_printf("LTE_LOG_ASSERT %d.\n", __LINE__); 
        return -1; 
    }
    lSpareLen  = (VOS_INT32)LTE_DIAG_PRINTF_LEN - lOccupyLen;

    lTmpLen    = VOS_nsprintf_s(ucDiagPrintData + lOccupyLen, (VOS_UINT32)lSpareLen, (VOS_UINT32)lSpareLen-1, "%u, ", VOS_GetTick());
   
    if(!(0 <= lTmpLen)) 
    {
        vos_printf("LTE_LOG_ASSERT %d.\n", __LINE__); 
        return -1; 
    }
    lOccupyLen += lTmpLen;
    if(!(LTE_DIAG_PRINTF_LEN >= (VOS_UINT32)lOccupyLen)) 
    {
        vos_printf("LTE_LOG_ASSERT %d.\n", __LINE__); 
        return -1; 
    }
    lSpareLen  = (VOS_INT32)LTE_DIAG_PRINTF_LEN - lOccupyLen;

    (VOS_VOID)VOS_MemSet_s(&vl, (VOS_UINT32)sizeof(va_list), 0, (VOS_UINT32)sizeof(va_list));

    va_start(vl, amount);
    paranum = (amount > LTE_DIAG_PRINTF_PARAM_MAX_NUM) ? LTE_DIAG_PRINTF_PARAM_MAX_NUM : amount;

    for(i = 0; i < (VOS_INT32)paranum; i++)
    {
        val = va_arg(vl, int);
        /* coverity[overrun-local] */
        lTmpLen = VOS_nsprintf_s(ucDiagPrintData + lOccupyLen, (VOS_UINT32)lSpareLen, (VOS_UINT32)lSpareLen-1, "%d, ", val);
        if(0 > lTmpLen)
        {
            DIAG_DEBUG_SDM_FUN(EN_SDM_DIAG_DOT_ERR, ERR_MSP_TOO_SMALL_BUFFER, (VOS_UINT32)lSpareLen, 3);
            va_end(vl);
            return -1;
        }

        lOccupyLen += lTmpLen;
        /* coverity[cond_at_most] */
        if(LTE_DIAG_PRINTF_LEN < (VOS_UINT32)lOccupyLen)
        {
            DIAG_DEBUG_SDM_FUN(EN_SDM_DIAG_DOT_ERR, ERR_MSP_TOO_SMALL_BUFFER, (VOS_UINT32)lOccupyLen, 4);
            va_end(vl);
            return -1;
        }
        lSpareLen  = (VOS_INT32)LTE_DIAG_PRINTF_LEN - lOccupyLen;
    }
    va_end(vl);

    ulDataLength = (VOS_UINT32)lOccupyLen;

    stDiagHead.u.stID.pri4b     = DIAG_MSG_TYPE_PS;
    stDiagHead.u.stID.mode4b    = DIAG_GET_MODE_ID(ulModuleId);
    stDiagHead.u.stID.sec5b     = DIAG_MSG_PS_DOT;
    stDiagHead.u.stID.cmdid19b  = 0;
    stDiagHead.ulSsid           = DIAG_SSID_CPU;
    stDiagHead.ulModemId        = DIAG_GET_MODEM_ID(ulModuleId);
    stDiagHead.ulDirection      = DIAG_MT_IND;
    stDiagHead.ulMsgTransId     = g_ulTransId++;
    stDiagHead.ulChanId         = SCM_CODER_SRC_LOM_IND;

    stDiagHead.ulHeaderSize     = 0;
    stDiagHead.pHeaderData      = VOS_NULL;

    stDiagHead.ulDataSize       = ulDataLength;
    stDiagHead.pData            = ucDiagPrintData;

    ret = diag_ServicePackData(&stDiagHead);

    if(ret)
    {
        DIAG_DEBUG_SDM_FUN(EN_SDM_DIAG_DOT_ERR, ret, 0, 5);
    }
    else
    {
        DIAG_DEBUG_SDM_FUN(EN_SDM_DIAG_DOT_OK, 0, 0, 0);
    }

    return (VOS_INT32)ret;
}


/*****************************************************************************
     : diag_GetFileNameFromPath
   : 
   : char* pcFileName
  1. cuijunqiang
*****************************************************************************/
VOS_CHAR * diag_GetFileNameFromPath(VOS_CHAR* pcFileName)
{
    VOS_CHAR    *pcPathPos1;
    VOS_CHAR    *pcPathPos2;
    VOS_CHAR    *pcPathPos;

    /* '\' */
    pcPathPos1 = (VOS_CHAR*)strrchr(pcFileName, '\\');
    if(VOS_NULL_PTR == pcPathPos1)
    {
        pcPathPos1 = pcFileName;
    }

    /* '/' */
    pcPathPos2 = (VOS_CHAR*)strrchr(pcFileName, '/');
    if(VOS_NULL_PTR == pcPathPos2)
    {
        pcPathPos2 = pcFileName;
    }

    pcPathPos = (pcPathPos1 > pcPathPos2) ? pcPathPos1 : pcPathPos2;

    /* '\''/' */
    if (pcFileName != pcPathPos)
    {
        pcPathPos++;
    }

    return pcPathPos;
}


/*****************************************************************************
     : DIAG_LogReport
   : 
   : ulModuleId( 31-24:modemid,23-16:modeid,15-12:level )
             pcFileName()
             ulLineNum()
             pszFmt()
   : 1K
             1K
                                           log1K
*****************************************************************************/
VOS_UINT32 DIAG_LogReport(VOS_UINT32 ulModuleId, VOS_UINT32 ulPid, VOS_CHAR *cFileName, VOS_UINT32 ulLineNum, VOS_CHAR* pszFmt, ...)
{
    VOS_UINT32 ret = ERR_MSP_SUCCESS;
    DIAG_CMD_LOG_PRINT_RAW_TXT_IND_STRU stRptInfo;
    VOS_CHAR   *cOffsetName;
    VOS_UINT32 ulDataLength =0;
    VOS_UINT32 ulModule = 0;
    VOS_UINT32 ulLevel = 0;
    va_list    arg;
    VOS_INT32  ulParamLen =0;
    VOS_ULONG  ulLockLevel;

    DIAG_MSG_REPORT_HEAD_STRU stDiagHead;

    /**/
    ulModule = ulPid;

    /**/
    ulLevel = DIAG_GET_PRINTF_LEVEL(ulModuleId);

    if(!DIAG_IS_POLOG_ON)
    {
        /*DIAGHSO*/
        if(!DIAG_IS_CONN_ON)
        {
            DIAG_DEBUG_SDM_FUN(EN_DIAG_CBT_API_PRINTFV_ERR, ERR_MSP_NO_INITILIZATION, ulModuleId, 1);
            return ERR_MSP_NO_INITILIZATION;
        }
        
        ret = diag_GetPrintCfg(ulModule, ulLevel);
        if(ERR_MSP_SUCCESS != ret)
        {
            DIAG_DEBUG_SDM_FUN(EN_DIAG_CBT_API_PRINTFV_ERR, ERR_MSP_UNAVAILABLE, ulModuleId, 2);
            return ERR_MSP_UNAVAILABLE;
        }
    }

    if(VOS_NULL == cFileName)
    {
        cFileName= " ";
    }

    /*  */
    cOffsetName = diag_GetFileNameFromPath(cFileName);

    /*HSO:pszFileName[ulLineNum]dataHSO[]*/
    /* coverity[negative_return_fn] */
    ulParamLen = VOS_nsprintf_s(stRptInfo.szText, DIAG_PRINTF_MAX_LEN, DIAG_PRINTF_MAX_LEN-1,"%s[%d]", cOffsetName, ulLineNum);

    if(ulParamLen > DIAG_PRINTF_MAX_LEN)
    {
        /*  */
        mdrv_om_system_error((VOS_INT)DIAG_ERROR_MODID_OVERFLOW, __LINE__, ulParamLen, 0, 0);
        return ERR_MSP_FAILURE;
    }

    (VOS_VOID)VOS_MemSet_s(&arg, (VOS_UINT32)sizeof(va_list), 0, (VOS_UINT32)sizeof(va_list));

    va_start(arg, pszFmt);
    
    /* coverity[negative_returns] */
    ulParamLen += VOS_nvsprintf_s((stRptInfo.szText + ulParamLen), (VOS_UINT32)(DIAG_PRINTF_MAX_LEN - ulParamLen),\
                 (VOS_UINT32)((DIAG_PRINTF_MAX_LEN - ulParamLen) -1), (const VOS_CHAR *)pszFmt, arg);
    if(ulParamLen > DIAG_PRINTF_MAX_LEN)
    {
        /*  */
        mdrv_om_system_error((VOS_INT)DIAG_ERROR_MODID_OVERFLOW, __LINE__, ulParamLen, 0, 0);
    }
    va_end(arg);

    stRptInfo.szText[DIAG_PRINTF_MAX_LEN-1] = '\0';
    ulDataLength = VOS_StrNLen(stRptInfo.szText, DIAG_PRINTF_MAX_LEN)+1;

    /*DIAG*/
    stRptInfo.ulModule = ulModule;
    VOS_SpinLockIntLock(&g_DiagLogPktNum.ulPrintLock, ulLockLevel);
    stRptInfo.ulNo = (g_DiagLogPktNum.ulPrintNum)++;
    VOS_SpinUnlockIntUnlock(&g_DiagLogPktNum.ulPrintLock, ulLockLevel);

    /* 1:error, 2:warning, 3:normal, 4:info */
    /* (0|ERROR|WARNING|NORMAL|INFO|0|0|0) */
    stRptInfo.ulLevel  = (0x80000000) >> ulLevel;

    /*  */
    ulDataLength += (sizeof(DIAG_CMD_LOG_PRINT_RAW_TXT_IND_STRU) - (DIAG_PRINTF_MAX_LEN+1));

    (VOS_VOID)VOS_MemSet_s(&stDiagHead, (VOS_UINT32)sizeof(DIAG_MSG_REPORT_HEAD_STRU), 0, sizeof(DIAG_MSG_REPORT_HEAD_STRU));

    stDiagHead.u.stID.pri4b     = DIAG_MSG_TYPE_PS;
    stDiagHead.u.stID.mode4b    = DIAG_GET_MODE_ID(ulModuleId);
    stDiagHead.u.stID.sec5b     = DIAG_MSG_PS_PRINT;
    stDiagHead.u.stID.cmdid19b  = 0;
    stDiagHead.ulSsid           = DIAG_SSID_CPU;
    stDiagHead.ulModemId        = DIAG_GET_MODEM_ID(ulModuleId);
    stDiagHead.ulDirection      = DIAG_MT_IND;
    stDiagHead.ulMsgTransId     = g_ulTransId++;
    stDiagHead.ulChanId         = SCM_CODER_SRC_LOM_IND;

    stDiagHead.ulHeaderSize     = 0;
    stDiagHead.pHeaderData      = VOS_NULL;

    stDiagHead.ulDataSize       = ulDataLength;
    stDiagHead.pData            = &stRptInfo;

    ret = diag_ServicePackData(&stDiagHead);

    if(ret)
    {
        DIAG_DEBUG_SDM_FUN(EN_DIAG_CBT_API_PRINTFV_ERR, ret, 0, 3);
    }
    else
    {
        DIAG_DEBUG_SDM_FUN(EN_DIAG_CBT_API_PRINTFV_OK, 0, 0, 4);
    }

    return ret;
}


/*****************************************************************************
     : DIAG_TransReport_Ex
   : (DIAG_TransReportDIAG_MESSAGE_TYPE)
   : DIAG_TRANS_IND_STRU->ulModule( 31-24:modemid,23-16:modeid,15-12:level,11-8:groupid )
             DIAG_TRANS_IND_STRU->ulMsgId(ID)
             DIAG_TRANS_IND_STRU->ulLength()
             DIAG_TRANS_IND_STRU->pData()

*****************************************************************************/
VOS_UINT32 DIAG_TransReport_Ex(DIAG_TRANS_IND_STRU *pstData)
{
    VOS_UINT32 ret = ERR_MSP_SUCCESS;
    DIAG_CMD_TRANS_IND_STRU stTransInfo = {0};
    DIAG_MSG_REPORT_HEAD_STRU stDiagHead;
    VOS_ULONG  ulLockLevel;

    /*DIAGHSO*/
    if((!DIAG_IS_CONN_ON) && (!DIAG_IS_POLOG_ON))
    {
        DIAG_DEBUG_SDM_FUN(EN_DIAG_CBT_API_TRANS_ERR, ERR_MSP_NO_INITILIZATION, 0, 1);
        return ERR_MSP_NO_INITILIZATION;
    }
    
    /**/
    if((VOS_NULL_PTR == pstData) || (NULL == pstData->pData) || (0 == pstData->ulLength))
    {
        DIAG_DEBUG_SDM_FUN(EN_DIAG_CBT_API_TRANS_ERR, ERR_MSP_NO_INITILIZATION, 0, 2);
        return ERR_MSP_INVALID_PARAMETER;
    }

    diag_LNR(EN_DIAG_LNR_TRANS_IND, pstData->ulMsgId, VOS_GetSlice());

    stTransInfo.ulModule = pstData->ulPid;
    stTransInfo.ulMsgId  = pstData->ulMsgId;
    
    VOS_SpinLockIntLock(&g_DiagLogPktNum.ulTransLock, ulLockLevel);
    stTransInfo.ulNo     = (g_DiagLogPktNum.ulTransNum)++;
    VOS_SpinUnlockIntUnlock(&g_DiagLogPktNum.ulTransLock, ulLockLevel);

    (VOS_VOID)VOS_MemSet_s(&stDiagHead, (VOS_UINT32)sizeof(DIAG_MSG_REPORT_HEAD_STRU), 0, sizeof(DIAG_MSG_REPORT_HEAD_STRU));

    stDiagHead.u.stID.pri4b     = DIAG_GET_GROUP_ID(pstData->ulModule);
    stDiagHead.u.stID.mode4b    = DIAG_GET_MODE_ID(pstData->ulModule);
    stDiagHead.u.stID.sec5b     = DIAG_MSG_PS_STRUCT;
    stDiagHead.u.stID.cmdid19b  = (pstData->ulMsgId)&0x7ffff;
    stDiagHead.ulSsid           = DIAG_SSID_CPU;
    stDiagHead.ulModemId        = DIAG_GET_MODEM_ID(pstData->ulModule);
    stDiagHead.ulDirection      = DIAG_MT_IND;
    stDiagHead.ulMsgTransId     = g_ulTransId++;
    stDiagHead.ulChanId         = SCM_CODER_SRC_LOM_IND;

    stDiagHead.ulHeaderSize     = sizeof(stTransInfo);
    stDiagHead.pHeaderData      = &stTransInfo;

    stDiagHead.ulDataSize       = pstData->ulLength;
    stDiagHead.pData            = pstData->pData;

    ret = diag_ServicePackData(&stDiagHead);

    if(ret)
    {
        DIAG_DEBUG_SDM_FUN(EN_DIAG_CBT_API_TRANS_ERR, ret, 0, 4);
    }
    else
    {
        DIAG_DEBUG_SDM_FUN(EN_DIAG_CBT_API_TRANS_OK, pstData->ulMsgId, VOS_GetSlice(), 5);
    }

    return ret;
}


/*****************************************************************************
     : DIAG_TransReport
   : (DIAG_ReportCommand)
   : DIAG_TRANS_IND_STRU->ulModule( 31-24:modemid,23-16:modeid )
             DIAG_TRANS_IND_STRU->ulMsgId(ID)
             DIAG_TRANS_IND_STRU->ulLength()
             DIAG_TRANS_IND_STRU->pData()

 History   :
    1.w00182550      2012-11-20  Draft Enact
    2.c64416         2014-11-18  

*****************************************************************************/
VOS_UINT32 DIAG_TransReport(DIAG_TRANS_IND_STRU *pstData)
{
    /*DIAGHSO*/
    if((!DIAG_IS_CONN_ON) && (!DIAG_IS_POLOG_ON))
    {
        DIAG_DEBUG_SDM_FUN(EN_DIAG_CBT_API_TRANS_ERR, ERR_MSP_NO_INITILIZATION, 0, 1);
        return ERR_MSP_NO_INITILIZATION;
    }
    
    /**/
    if((VOS_NULL_PTR == pstData) || (NULL == pstData->pData) || (0 == pstData->ulLength))
    {
        DIAG_DEBUG_SDM_FUN(EN_DIAG_CBT_API_TRANS_ERR, ERR_MSP_NO_INITILIZATION, 0, 2);
        return ERR_MSP_INVALID_PARAMETER;
    }

    pstData->ulModule = DIAG_GEN_MODULE_EX( DIAG_GET_MODEM_ID(pstData->ulModule), \
                                            DIAG_GET_MODE_ID(pstData->ulModule),  \
                                            DIAG_MSG_TYPE_PS);

    return DIAG_TransReport_Ex(pstData);
}


/*****************************************************************************
     : DIAG_EventReport
   : PS(DIAG_ReportEventLog)
   : DIAG_EVENT_IND_STRU->ulModule( 31-24:modemid,23-16:modeid,15-12:level,11-0:pid )
             DIAG_EVENT_IND_STRU->ulEventId(event ID)
             DIAG_EVENT_IND_STRU->ulLength(event)
             DIAG_EVENT_IND_STRU->pData(event)

 History         :
    1.w00182550      2012-11-20  Draft Enact
    2.c64416         2014-11-18  

*****************************************************************************/
VOS_UINT32 DIAG_EventReport(DIAG_EVENT_IND_STRU *pstEvent)
{
    VOS_UINT32 ret = ERR_MSP_SUCCESS;
    DIAG_CMD_LOG_EVENT_IND_STRU stEventIndInfo;
    DIAG_MSG_REPORT_HEAD_STRU stDiagHead;
    VOS_ULONG  ulLockLevel;

    if(VOS_NULL_PTR == pstEvent)
    {
        DIAG_DEBUG_SDM_FUN(EN_DIAG_CBT_API_EVENT_ERR, ERR_MSP_INVALID_PARAMETER, 0, 2);
        return ERR_MSP_INVALID_PARAMETER;
    }
    
    if(!DIAG_IS_POLOG_ON)
    {
        /**/
        if(!DIAG_IS_EVENT_ON)
        {
            DIAG_DEBUG_SDM_FUN(EN_DIAG_CBT_API_EVENT_ERR, ERR_MSP_NO_INITILIZATION, 0, 1);
            return ERR_MSP_NO_INITILIZATION;
        }
        
        /* GUevent */
        if(0 == g_EventModuleCfg[pstEvent->ulPid - VOS_PID_DOPRAEND])
        {
            DIAG_DEBUG_SDM_FUN(EN_DIAG_CBT_API_EVENT_ERR, ERR_MSP_INVALID_PARAMETER, 0, 3);
            return ERR_MSP_INVALID_PARAMETER;
        }
    }

    /*DIAG*/
    VOS_SpinLockIntLock(&g_DiagLogPktNum.ulEventLock, ulLockLevel);
    stEventIndInfo.ulNo     = (g_DiagLogPktNum.ulEventNum)++;
    VOS_SpinUnlockIntUnlock(&g_DiagLogPktNum.ulEventLock, ulLockLevel);
    
    stEventIndInfo.ulId     = pstEvent->ulEventId;
    stEventIndInfo.ulModule = pstEvent->ulPid;

    (VOS_VOID)VOS_MemSet_s(&stDiagHead, (VOS_UINT32)sizeof(DIAG_MSG_REPORT_HEAD_STRU), 0, sizeof(DIAG_MSG_REPORT_HEAD_STRU));

    stDiagHead.u.stID.pri4b     = DIAG_MSG_TYPE_PS;
    stDiagHead.u.stID.mode4b    = DIAG_GET_MODE_ID(pstEvent->ulModule);
    stDiagHead.u.stID.sec5b     = DIAG_MSG_PS_EVENT;
    stDiagHead.u.stID.cmdid19b  = 0;
    stDiagHead.ulSsid           = DIAG_SSID_CPU;
    stDiagHead.ulModemId        = DIAG_GET_MODEM_ID(pstEvent->ulModule);
    stDiagHead.ulDirection      = DIAG_MT_IND;
    stDiagHead.ulMsgTransId     = g_ulTransId++;
    stDiagHead.ulChanId         = SCM_CODER_SRC_LOM_IND;

    stDiagHead.ulHeaderSize     = sizeof(stEventIndInfo);
    stDiagHead.pHeaderData      = &stEventIndInfo;

    stDiagHead.ulDataSize       = pstEvent->ulLength;
    stDiagHead.pData            = pstEvent->pData;

    ret = diag_ServicePackData(&stDiagHead);
    if(ret)
    {
        DIAG_DEBUG_SDM_FUN(EN_DIAG_CBT_API_EVENT_ERR, ret, 0, 4);
    }
    else
    {
        DIAG_DEBUG_SDM_FUN(EN_DIAG_CBT_API_EVENT_OK, 0, 0, 5);
    }
    return ret;
}


/*****************************************************************************
     : DIAG_AirMsgReport
   : PS(DIAG_ReportAirMessageLog)
   : DIAG_AIR_IND_STRU->ulModule( 31-24:modemid,23-16:modeid,15-12:level,11-0:pid )
             DIAG_AIR_IND_STRU->ulMsgId(ID)
             DIAG_AIR_IND_STRU->ulDirection()
             DIAG_AIR_IND_STRU->ulLength()
             DIAG_AIR_IND_STRU->pData()

 History         :
    1.w00182550      2012-11-20  Draft Enact
    2.c64416         2014-11-18  

*****************************************************************************/
VOS_UINT32 DIAG_AirMsgReport(DIAG_AIR_IND_STRU *pstAir)
{
    VOS_UINT32 ret = ERR_MSP_SUCCESS;
    DIAG_CMD_LOG_AIR_IND_STRU stRptInfo = {0};
    DIAG_MSG_REPORT_HEAD_STRU stDiagHead;
    VOS_ULONG  ulLockLevel;

    /*LT */
    if ((!DIAG_IS_LT_AIR_ON) && (!DIAG_IS_POLOG_ON))
    {
        DIAG_DEBUG_SDM_FUN(EN_DIAG_CBT_API_AIR_ERR, ERR_MSP_NO_INITILIZATION, 0, 1);
        return ERR_MSP_NO_INITILIZATION;
    }

    /**/
    if((VOS_NULL == pstAir) || (VOS_NULL == pstAir->pData) || (0 == pstAir->ulLength))
    {
        DIAG_DEBUG_SDM_FUN(EN_DIAG_CBT_API_AIR_ERR, ERR_MSP_INVALID_PARAMETER, 0, 2);
        return ERR_MSP_INVALID_PARAMETER;
    }

    stRptInfo.ulModule  = pstAir->ulPid;
    stRptInfo.ulId      = pstAir->ulMsgId;
    stRptInfo.ulSide    = pstAir->ulDirection;
    
    VOS_SpinLockIntLock(&g_DiagLogPktNum.ulAirLock, ulLockLevel);
    stRptInfo.ulNo      = (g_DiagLogPktNum.ulAirNum)++;
    VOS_SpinUnlockIntUnlock(&g_DiagLogPktNum.ulAirLock, ulLockLevel);

    (VOS_VOID)VOS_MemSet_s(&stDiagHead, (VOS_UINT32)sizeof(DIAG_MSG_REPORT_HEAD_STRU), 0, sizeof(DIAG_MSG_REPORT_HEAD_STRU));

    stDiagHead.u.stID.pri4b     = DIAG_MSG_TYPE_PS;
    stDiagHead.u.stID.mode4b    = DIAG_GET_MODE_ID(pstAir->ulModule);
    stDiagHead.u.stID.sec5b     = DIAG_MSG_PS_AIR;
    stDiagHead.u.stID.cmdid19b  = 0;
    stDiagHead.ulSsid           = DIAG_SSID_CPU;
    stDiagHead.ulModemId        = DIAG_GET_MODEM_ID(pstAir->ulModule);
    stDiagHead.ulDirection      = DIAG_MT_IND;
    stDiagHead.ulMsgTransId     = g_ulTransId++;
    stDiagHead.ulChanId         = SCM_CODER_SRC_LOM_IND;

    stDiagHead.ulHeaderSize     = sizeof(stRptInfo);
    stDiagHead.pHeaderData      = &stRptInfo;

    stDiagHead.ulDataSize       = pstAir->ulLength;
    stDiagHead.pData            = pstAir->pData;

    ret = diag_ServicePackData(&stDiagHead);

    if(ret)
    {
        DIAG_DEBUG_SDM_FUN(EN_DIAG_CBT_API_AIR_ERR, ret, 0, 3);
    }
    else
    {
        DIAG_DEBUG_SDM_FUN(EN_DIAG_CBT_API_AIR_OK, 0, 0, 4);
    }

    return ret;
}


/*****************************************************************************
 Function Name   : DIAG_ReportVoLTELog
 Description     : VoLTE
 Input           : DIAG_VoLTE_LOG_STRU* pRptMessage
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.fuxin      2013-12-30  create
    2.c64416         2014-11-18  
*****************************************************************************/
VOS_UINT32 DIAG_ReportVoLTELog(DIAG_VOLTE_LOG_STRU* pRptMessage)
{
    VOS_UINT32 ret         = ERR_MSP_SUCCESS;
    VOS_UINT32 ulModuleId;
    DIAG_CMD_LOG_VOLTE_IND_STRU stRptInfo = {0};
    DIAG_MSG_REPORT_HEAD_STRU stDiagHead;
    VOS_ULONG  ulLockLevel;

    /*DIAGHSO*/
    if((!DIAG_IS_CONN_ON) && (!DIAG_IS_POLOG_ON))
    {
        DIAG_DEBUG_SDM_FUN(EN_DIAG_CBT_API_VOLTE_ERR, ERR_MSP_NO_INITILIZATION, 0, 1);
        return ERR_MSP_NO_INITILIZATION;
    }

    /**/
    if((VOS_NULL == pRptMessage) || (VOS_NULL == pRptMessage->pData) || (0 == pRptMessage->ulDataSize))
    {
        DIAG_DEBUG_SDM_FUN(EN_DIAG_CBT_API_VOLTE_ERR, ERR_MSP_INVALID_PARAMETER, 0, 2);
        return ERR_MSP_INVALID_PARAMETER;
    }

    ulModuleId  = DIAG_GET_MODULE_ID(pRptMessage->ulId);
    ret = diag_GetLayerCfg(ulModuleId, ulModuleId, pRptMessage->ulMessageID);

    if(ERR_MSP_SUCCESS != ret)
    {
        DIAG_DEBUG_SDM_FUN(EN_DIAG_CBT_API_VOLTE_ERR, ERR_MSP_CFG_LOG_NOT_ALLOW, 0, 3);
        return ERR_MSP_CFG_LOG_NOT_ALLOW;
    }

    stRptInfo.ulModule  = DIAG_GET_MODULE_ID(pRptMessage->ulId);
    stRptInfo.ulId      = pRptMessage->ulMessageID;
    stRptInfo.ulSide    = pRptMessage->ulSideId;

    VOS_SpinLockIntLock(&g_DiagLogPktNum.ulVoLTELock, ulLockLevel);
    stRptInfo.ulNo      = (g_DiagLogPktNum.ulVoLTENum)++;
    VOS_SpinUnlockIntUnlock(&g_DiagLogPktNum.ulVoLTELock, ulLockLevel);

    (VOS_VOID)VOS_MemSet_s(&stDiagHead, (VOS_UINT32)sizeof(DIAG_MSG_REPORT_HEAD_STRU), 0, sizeof(DIAG_MSG_REPORT_HEAD_STRU));

    stDiagHead.u.stID.pri4b     = DIAG_MSG_TYPE_PS;
    stDiagHead.u.stID.mode4b    = DIAG_GET_MODE_ID(pRptMessage->ulId);
    stDiagHead.u.stID.sec5b     = DIAG_MSG_PS_VOLTE;
    stDiagHead.u.stID.cmdid19b  = 0;
    stDiagHead.ulSsid           = DIAG_SSID_CPU;
    stDiagHead.ulModemId        = DIAG_GET_MODEM_ID(pRptMessage->ulId);
    stDiagHead.ulDirection      = DIAG_MT_IND;
    stDiagHead.ulMsgTransId     = g_ulTransId++;
    stDiagHead.ulChanId         = SCM_CODER_SRC_LOM_IND;

    stDiagHead.ulHeaderSize     = sizeof(stRptInfo);
    stDiagHead.pHeaderData      = &stRptInfo;

    stDiagHead.ulDataSize       = pRptMessage->ulDataSize;
    stDiagHead.pData            = pRptMessage->pData;

    ret = diag_ServicePackData(&stDiagHead);

    if(ret)
    {
        DIAG_DEBUG_SDM_FUN(EN_DIAG_CBT_API_VOLTE_ERR, ret, 0, 3);
    }
    else
    {
        DIAG_DEBUG_SDM_FUN(EN_DIAG_CBT_API_VOLTE_OK, 0, 0, 5);
    }

    return ret;
}


/*****************************************************************************
     : DIAG_TraceReport
   : PS(DIAG_ReportLayerMessageLog)
   : pMsg(VOS)

 History         :
    1.w00182550      2012-11-20  Draft Enact
    2.c64416         2014-11-18  

*****************************************************************************/
VOS_VOID DIAG_TraceReport(VOS_VOID *pMsg)
{
    VOS_UINT32 ret, ulSrcModule, ulDstModule, ulMsgId;
    DIAG_OSA_MSG_STRU *pDiagMsg = (DIAG_OSA_MSG_STRU *)pMsg;
    DIAG_OSA_MSG_STRU *pNewMsg  = NULL;
    DIAG_CMD_LOG_LAYER_IND_STRU stTrace;

    DIAG_MSG_REPORT_HEAD_STRU stDiagHead;
    VOS_ULONG    ulLockLevel;
    
    if(VOS_NULL == pDiagMsg)
    {
        DIAG_DEBUG_SDM_FUN(EN_DIAG_CBT_API_TRACE_ERR, ERR_MSP_INVALID_PARAMETER, 0, 1);
        return ;
    }
    
    ulSrcModule = pDiagMsg->ulSenderPid;
    ulDstModule = pDiagMsg->ulReceiverPid;
    ulMsgId     = pDiagMsg->ulMsgId;

    if(!DIAG_IS_POLOG_ON)
    {
        /*DIAGHSO*/
        if(!DIAG_IS_CONN_ON)
        {
            DIAG_DEBUG_SDM_FUN(EN_DIAG_CBT_API_TRACE_ERR, ERR_MSP_NO_INITILIZATION, 0, 1);
            return ;
        }
        
        /**/
        ret = diag_GetLayerCfg(ulSrcModule, ulDstModule, ulMsgId);
        if(ret)
        {
            DIAG_DEBUG_SDM_FUN(EN_DIAG_CBT_API_TRACE_ERR, ERR_MSP_CFG_LOG_NOT_ALLOW, 0, 1);
            return ;
        }
    }

    /* 0 */
    if(VOS_NULL != g_pFilterFunc)
    {
        if(g_pFilterFunc(pDiagMsg))
        {
            DIAG_DEBUG_SDM_FUN(EN_DIAG_CBT_API_TRACE_FILTER, ulSrcModule, ulDstModule, ulMsgId);
            return ;
        }
    }

    pNewMsg = pDiagMsg;

    /*  */
    /*  */
    if(VOS_NULL != g_pMatchFunc)
    {
        pNewMsg = g_pMatchFunc(pDiagMsg);
        if(VOS_NULL == pNewMsg)
        {
            DIAG_DEBUG_SDM_FUN(EN_DIAG_CBT_API_TRACE_MATCH, ulSrcModule, ulDstModule, ulMsgId);
            return ;
        }
    }

    stTrace.ulModule    = ulSrcModule;
    stTrace.ulDestMod   = ulDstModule;
    /*matchmsgmsgidmsgidmsgid,*/
    stTrace.ulId        = pNewMsg->ulMsgId;
    
    VOS_SpinLockIntLock(&g_DiagLogPktNum.ulLayerLock, ulLockLevel);
    stTrace.ulNo        = (g_DiagLogPktNum.ulLayerNum++);
    VOS_SpinUnlockIntUnlock(&g_DiagLogPktNum.ulLayerLock, ulLockLevel);

    (VOS_VOID)VOS_MemSet_s(&stDiagHead, (VOS_UINT32)sizeof(DIAG_MSG_REPORT_HEAD_STRU), 0, sizeof(DIAG_MSG_REPORT_HEAD_STRU));

    stDiagHead.u.stID.pri4b     = DIAG_MSG_TYPE_PS;
    stDiagHead.u.stID.mode4b    = DIAG_MODE_COMM;       /*  */
    stDiagHead.u.stID.sec5b     = DIAG_MSG_PS_LAYER;
    stDiagHead.u.stID.cmdid19b  = 0;
    stDiagHead.ulSsid           = DIAG_SSID_CPU;

    ret = (DIAG_CFG_MODULE_IS_INVALID(ulSrcModule))?ulDstModule:ulSrcModule;

    stDiagHead.ulModemId        = VOS_GetModemIDFromPid(ret);
    stDiagHead.ulDirection      = DIAG_MT_IND;
    stDiagHead.ulMsgTransId     = g_ulTransId++;
    stDiagHead.ulChanId         = SCM_CODER_SRC_LOM_IND;

    stDiagHead.ulHeaderSize     = sizeof(stTrace);
    stDiagHead.pHeaderData      = &stTrace;

    stDiagHead.ulDataSize       = sizeof(DIAG_OSA_MSG_STRU) - sizeof(pNewMsg->ulMsgId) + pNewMsg->ulLength;
    stDiagHead.pData            = pNewMsg;

    ret = diag_ServicePackData(&stDiagHead);

    if(ret)
    {
        DIAG_DEBUG_SDM_FUN(EN_DIAG_CBT_API_TRACE_ERR, ret, 0, 3);
    }
    else
    {
        DIAG_DEBUG_SDM_FUN(EN_DIAG_CBT_API_TRACE_OK, 0, 0, 5);
    }
    return ;
}


/*****************************************************************************
 Function Name   : DIAG_TraceFilterFuncReg
 Description     : ()
 Input           : 
 Output          : None
 Return          : : 0--

 History         :
    1.c64416      2012-11-20  Draft Enact

*****************************************************************************/
VOS_UINT32 DIAG_TraceFilterFuncReg(DIAG_TraceFilterFunc pFun)
{
    if(VOS_NULL == g_pFilterFunc)
    {
        g_pFilterFunc = pFun;
        return ERR_MSP_SUCCESS;
    }
    else
    {
        return ERR_MSP_FAILURE;
    }
}


/*****************************************************************************
 Function Name   : DIAG_TraceMatchFuncReg
 Description     : ()
                    TTF
 Input           : 
 Output          : None
 Return          : : 0--

 History         :
    1.c00326366      2015-06-16  Draft Enact

*****************************************************************************/
VOS_UINT32 DIAG_TraceMatchFuncReg(DIAG_TraceMatchFunc pFun)
{
    if(VOS_NULL == g_pMatchFunc)
    {
        g_pMatchFunc = pFun;
        return ERR_MSP_SUCCESS;
    }
    else
    {
        return ERR_MSP_FAILURE;
    }
}


/*****************************************************************************
     : DIAG_UserPlaneReport
   : PS(DIAG_ReportUserPlaneMessageLog)
   : DIAG_USER_IND_STRU->ulModule( 31-24:modemid,23-16:modeid,15-12:level,11-0:pid )
             DIAG_USER_IND_STRU->ulMsgId(ID)
             DIAG_USER_IND_STRU->ulLength()
             DIAG_USER_IND_STRU->pData()

 History         :
    1.w00182550      2012-11-20  Draft Enact
    2.c64416         2014-11-18  

*****************************************************************************/
VOS_UINT32 DIAG_UserPlaneReport(DIAG_USER_IND_STRU *pstUser)
{
    VOS_UINT32 ret = ERR_MSP_SUCCESS;
    DIAG_CMD_LOG_USERPLANE_IND_STRU stRptInfo = {0};
    DIAG_MSG_REPORT_HEAD_STRU stDiagHead;
    VOS_ULONG    ulLockLevel;

    /*DIAGHSO*/
    if((!DIAG_IS_CONN_ON) && (!DIAG_IS_POLOG_ON))
    {
        DIAG_DEBUG_SDM_FUN(EN_DIAG_CBT_API_USER_ERR, ERR_MSP_NO_INITILIZATION, 0, 1);
        return ERR_MSP_NO_INITILIZATION;
    }

    /**/
    if((NULL == pstUser)||((0 == pstUser->ulLength) && (NULL == pstUser->pData)))
    {
        DIAG_DEBUG_SDM_FUN(EN_DIAG_CBT_API_USER_ERR, ERR_MSP_INVALID_PARAMETER, 0, 2);
        return ERR_MSP_INVALID_PARAMETER;
    }

    VOS_SpinLockIntLock(&g_DiagLogPktNum.ulUserLock, ulLockLevel);
    stRptInfo.ulNo          = (g_DiagLogPktNum.ulUserNum)++;
    VOS_SpinUnlockIntUnlock(&g_DiagLogPktNum.ulUserLock, ulLockLevel);
    
    stRptInfo.ulId          = pstUser->ulMsgId;
    stRptInfo.ulModule      = pstUser->ulPid;

    (VOS_VOID)VOS_MemSet_s(&stDiagHead, (VOS_UINT32)sizeof(DIAG_MSG_REPORT_HEAD_STRU), 0, sizeof(DIAG_MSG_REPORT_HEAD_STRU));

    stDiagHead.u.stID.pri4b     = DIAG_MSG_TYPE_PS;
    stDiagHead.u.stID.mode4b    = DIAG_GET_MODE_ID(pstUser->ulModule);
    stDiagHead.u.stID.sec5b     = DIAG_MSG_PS_USER;
    stDiagHead.u.stID.cmdid19b  = 0;
    stDiagHead.ulSsid           = DIAG_SSID_CPU;
    stDiagHead.ulModemId        = DIAG_GET_MODEM_ID(pstUser->ulModule);
    stDiagHead.ulDirection      = DIAG_MT_IND;
    stDiagHead.ulMsgTransId     = g_ulTransId++;
    stDiagHead.ulChanId         = SCM_CODER_SRC_LOM_IND;

    stDiagHead.ulHeaderSize     = sizeof(DIAG_CMD_LOG_USERPLANE_IND_STRU);
    stDiagHead.pHeaderData      = &stRptInfo;

    stDiagHead.ulDataSize       = pstUser->ulLength;
    stDiagHead.pData            = pstUser->pData;

    ret = diag_ServicePackData(&stDiagHead);

    if(ret)
    {
        DIAG_DEBUG_SDM_FUN(EN_DIAG_CBT_API_USER_ERR, ret, 0, 3);
    }
    else
    {
        DIAG_DEBUG_SDM_FUN(EN_DIAG_CBT_API_USER_OK, 0, 0, 4);
    }

    return ret;
}


/* MBBerrorlogMBBphone */
VOS_UINT32 DIAG_ErrorLog(VOS_CHAR * cFileName,VOS_UINT32 ulFileId, VOS_UINT32 ulLine,
                VOS_UINT32 ulErrNo, VOS_VOID * pBuf, VOS_UINT32 ulLen)
{
    return 0;
}


/*****************************************************************************
 Function Name   : diag_SendMsg
 Description     : DIAG
 Input           :VOS_UINT32 ulSenderId
                VOS_UINT32 ulRecverId
                VOS_UINT32 ulMsgId
                VOS_VOID* pDta
                VOS_UINT32 dtaSize
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.w00182550      2012-11-20  Draft Enact

*****************************************************************************/
VOS_UINT32 diag_SendMsg(VOS_UINT32 ulSenderId, VOS_UINT32 ulRecverId, VOS_UINT32 ulMsgId, VOS_UINT8* pDta, VOS_UINT32 dtaSize)
{
    VOS_UINT32 ret = ERR_MSP_UNKNOWN;
    DIAG_DATA_MSG_STRU* pDataMsg = NULL;

    pDataMsg = (DIAG_DATA_MSG_STRU*)VOS_AllocMsg(ulSenderId,(sizeof(DIAG_DATA_MSG_STRU)+ dtaSize - VOS_MSG_HEAD_LENGTH));

    if (pDataMsg != NULL)
    {
        pDataMsg->ulReceiverPid = ulRecverId;
        pDataMsg->ulSenderPid   = ulSenderId;
        pDataMsg->ulLength      = sizeof(DIAG_DATA_MSG_STRU)+ dtaSize - 20;

        pDataMsg->ulMsgId    = ulMsgId;
        pDataMsg->ulLen      = dtaSize;
        if(0 != dtaSize)
        {
            VOS_MemCpy_s(pDataMsg->pContext,dtaSize,pDta,dtaSize);
        }

        ret = VOS_SendMsg(ulSenderId, pDataMsg);
        if (ret != VOS_OK)
        {
            diag_printf("diag_SendMsg ulSenderId=%d,ulRecverId=%d,ulMsgId=0x%x,pDta=%p,dtaSize=%d!\n",ulSenderId,ulRecverId,ulMsgId,pDta,dtaSize);
        }
        else
        {
            ret = ERR_MSP_SUCCESS;
        }
    }

    return ret;
}


VOS_UINT32 Diag_GetLogLevel(VOS_UINT32 ulPid)
{
    VOS_UINT8 level;

    /*IDCCPUPS*/
    if ((VOS_PID_DOPRAEND <= ulPid) && (VOS_PID_BUTT > ulPid))
    {
	if( g_PrintTotalCfg == DIAG_CFG_PRINT_TOTAL_MODULE_SWT_NOT_USE)
	{
		level = g_PrintModuleCfg[ulPid - VOS_PID_DOPRAEND];
	}
	else
	{
		level = (VOS_UINT8)g_PrintTotalCfg;
	}

        /* level(0|ERROR|WARNING|NORMAL|INFO|0|0|0) bit 6-3 ERROR-INFO */

        if(level & 0x08)
        {
            return PS_LOG_LEVEL_INFO;
        }
        else if(level & 0x10)
        {
            return PS_LOG_LEVEL_NORMAL;
        }
        else if(level & 0x20)
        {
            return PS_LOG_LEVEL_WARNING;
        }
        else if(level & 0x40)
        {
            return PS_LOG_LEVEL_ERROR;
        }
        else
        {
            return PS_LOG_LEVEL_OFF;
        }
    }

    return PS_LOG_LEVEL_OFF;
}



/*****************************************************************************
 Function Name   : diag_FailedCmdCnf
 Description     : MSP
 Input           : pData     
                   ulErrcode 
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.c64416      2016-02-15  Draft Enact

*****************************************************************************/
VOS_UINT32 diag_FailedCmdCnf(DIAG_FRAME_INFO_STRU *pData, VOS_UINT32 ulErrcode)
{
    DIAG_COMM_CNF_STRU stCnfCmd   = {0};
    MSP_DIAG_CNF_INFO_STRU stDiagInfo = {0};

    DIAG_MSG_COMMON_PROC(stDiagInfo, stCnfCmd, pData);

    stDiagInfo.ulMsgType = pData->stID.pri4b;

    stCnfCmd.ulRet = ulErrcode;

    return DIAG_MsgReport(&stDiagInfo, &stCnfCmd, sizeof(stCnfCmd));
}


/*****************************************************************************
 Function Name   : diag_IsPowerOnLogOpen
 Description     : log
 Input           : None
 Output          : None
 Return          : VOS_TRUE:yes ; VOS_FALSE:no

 History         :
    1.c64416      2016-07-18  Draft Enact

*****************************************************************************/
VOS_BOOL diag_IsPowerOnLogOpen(VOS_VOID)
{
    VOS_UINT32          ulRet;
    NV_POWER_ON_LOG_SWITCH_STRU stPowerOnLog = {0};
    
    /* OM */
    ulRet = NV_Read(EN_NV_ID_POWER_ON_LOG_SWITCH, &stPowerOnLog, sizeof(stPowerOnLog));
    if((ERR_MSP_SUCCESS == ulRet) && (stPowerOnLog.cPowerOnlogA) && (stPowerOnLog.cPowerOnlogC))
    {
        return VOS_TRUE;
    }
    return VOS_FALSE;
}




