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


#ifndef __MSP_NV_DEF_H__
#define __MSP_NV_DEF_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "vos.h"




/* NV_ID_IMEI                           = 0, */
typedef struct
{
    VOS_UINT8  ucSerialNumber[16];
}NV_IMEI_STRU;

/* V_ID_MSP_SERIAL_NUMBER              = 6, */
typedef struct
{
    VOS_UINT8  SerialNumber[20];
}SERIALNUMBER_STRU;

/* NV_ID_MSP_WATCHDOG_FLAG              = 9, */
typedef struct
{
    VOS_UINT32                              WatchDogFlag;    /*[0,1]*/
}WATCHDOGFLAG_STRU;

/* NV_ID_MSP_KICKDOG_TIME               = 11, */
typedef struct
{
    VOS_UINT32                              KickDog_Time;
}KICKDOG_TIME_STRU;

/* NV_ID_MSP_SCHEDULE_WATCHDOG_TIME     = 12, */
typedef struct
{
    VOS_UINT32                              ScheduleWatchDog_Time;
}SCHEDULEWATCHDOG_TIME_STRU;

/* NV_ID_MSP_MAX_REG_CNT_IN_GSM_MODE    = 28, */
typedef struct
{
    VOS_UINT16  usMaxRegCntGMode;
}NV_MAX_REG_CNT_IN_GMODE_STRU;

/* NV_ID_MSP_MAX_REG_CNT_IN_GSM_MODE    = 28, */
typedef struct
{
    VOS_UINT16                              Max_Reg_Cnt_in_GSM_Mode;    /*[1,1024]*/
}MAX_REG_CNT_IN_GSM_MODE_STRU;

/* NV_ID_MSP_DFS_CONFIG                 = 29, */
/*  */

/* NV_ID_MSP_SW_VER_FLAG                = 36, */
typedef struct
{
    VOS_UINT32                              NV_SW_VER_Flag;    /*[0,1]*/
}NV_SW_VER_FLAG_STRU;

/* NV_ID_MSP_ERRLOG_ENABLE              = 37, */
typedef struct
{
    VOS_UINT16                              NV_ERRORLOG_ENABLEFLAG;    /*[0,1]*/
}NV_ERRORLOG_ENABLEFLAG_STRU;

/* NV_ID_MSP_ERRLOG_FLUSH               = 38, */
typedef struct
{
    VOS_UINT32                              NV_ERRORLOG_FLUSHBUFINTERVALUE;
}NV_ERRORLOG_FLUSHBUFINTERVALUE_STRU;
/* NV_ID_MSP_ERRLOG_RECOVER             = 39, */
typedef struct
{
    VOS_UINT32                              NV_ERRORLOG_RECORDPERIOD;    /*[0,103680]*/
}NV_ERRORLOG_RECORDPERIOD_STRU;

/* NV_ID_MSP_USIM_TEMP_PROTECT_NEW      = 40, */
typedef struct
{
    VOS_UINT8                                      TempOverCount;
    VOS_UINT8                                      TempResumeCount;
    VOS_UINT8                                      TempCloseCount;
    VOS_UINT8                                      TempPoweroffCount;
    VOS_UINT32                                     WaitTimer;
}MONITORPARACTRL_NEW_STRU;

typedef struct
{
    VOS_UINT32                                     ProtectEnable;
    VOS_INT32                                     lpoweroffThreshold;
    VOS_INT32                                     PmicCloseAdcThreshold;
    VOS_INT32                                     PmicAlarmAdcThreshold;
    VOS_INT32                                     PmicResumeAdcThreshold;
    VOS_INT32                                     SIMPowerOffThreshold;
    MONITORPARACTRL_NEW_STRU                     stMonitorParaCtrl_New;
}USIMTEMPPROTECT_NEW_STRU;
/* NV_ID_MSP_WIFI_IPADDRESS             = 44, */
/*  */

/* NV_ID_MSP_OM_PORT_TYPE               = 45, */
typedef struct
{
    VOS_UINT32                                     enPortType;
    VOS_UINT32                                     ulMaxFileSize;
}NV_OM_PORT_TYPE_STRU;

/* NV_ID_MSP_PRINTF_PORT_TYPE           = 46, */
typedef struct
{
    VOS_UINT32                                     enPortType;
    VOS_UINT32                                     ulMaxFileSize;
}NV_PRINTF_PORT_TYPE_STRU;

/* NV_ID_MSP_PSLOG_PORT_TYPE            = 47, */
typedef struct
{
    VOS_UINT32                                     enPortType;
    VOS_UINT32                                     ulMaxFileSize;
}NV_PSLOG_PORT_TYPE_STRU;

/* NV_ID_MSP_M2_ENABLE                  = 59, */
typedef struct
{
    VOS_UINT32                              M2_ENABLE;
}M2_ENABLE_STRU;

/* NV_ID_MSP_MANUFACTUREINFO            = 32768, */
typedef struct
{
    VOS_UINT8                               ManufactureInfo[128];
}MANUFACTUREINFO_STRU;

/* NV_ID_MSP_PPP_CONFIG_MRU_TYPE        = 32769, */
typedef struct
{
    VOS_UINT16                              PPP_CONFIG_MRU_Type;    /*[1,65535]*/
}PPP_CONFIG_MRU_TYPE_STRU;

/* NV_ID_MSP_WIFI_KEY                   = 50012, */
typedef struct
{
    VOS_UINT8                                      aucwlAuthMode[16];
    VOS_UINT8                                      aucBasicEncryptionModes[5];
    VOS_UINT8                                      aucWPAEncryptionModes[5];
    VOS_UINT8                                      aucwlKeys1[27];
    VOS_UINT8                                      aucwlKeys2[27];
    VOS_UINT8                                      aucwlKeys3[27];
    VOS_UINT8                                      aucwlKeys4[27];
    VOS_UINT32                                     ulwlKeyIndex;
    VOS_UINT8                                      aucwlWpaPsk[65];
    VOS_UINT8                                      ucwlWpsEnbl;
    VOS_UINT8                                      ucwlWpsCfg;
    VOS_UINT8                                      ucReserved;
}NV_WIFI_KEY_STRU;

/* NV_ID_MSP_MAC_ADDR                   = 50014, */
typedef struct
{
    VOS_UINT8                               NV_MACADDR[32];
}NV_MACADDR_STRU;

/* NV_ID_MSP_BATTERY_TEMP_CFG           = 50016, */
typedef struct
{
    VOS_UINT32                                     ulIsEnable;
    VOS_INT32                                     lCloseADCHold;
    VOS_UINT32                                     ulTempOverMax;
}NV_BATTERYTEMP_CFG_STRU;

/* NV_ID_MSP_MEAN_THROUGHPUT            = 50031, */
typedef struct
{
    VOS_UINT8                               MEAN_THROUGHPUT[2];
}MEAN_THROUGHPUT_STRU;

/* NV_ID_MSP_OAM_CONFIG                 = 120, */
/*  */

/* NV_ID_MSP_HIFI_LDF_CONFIG            = 123, */
typedef struct
{
    VOS_UINT32                                     ulDataAddr;
    VOS_UINT32                                     ulDataLen;
}HIFI_LDF_DUMP_DATA_INFO_STRU;

typedef struct
{
    VOS_UINT32                                     ulDataNum;
    HIFI_LDF_DUMP_DATA_INFO_STRU            stHIFI_LDF_DUMP_DATA_INFO_STRU[64];
}NV_HIFI_LDF_CONFIG_STRU;

/* NV_ID_MSP_PRIORITY_THREAD            = 127, */
typedef struct
{
    VOS_UINT16                                     ausNvMiddle[6];
    VOS_UINT16                                     ausRsv[2];
}NV_PRIORITY_THRESHOLD_STRU;

/* NV_ID_MSP_USIM_SUPPORT_FEATURE       = 9090, */
typedef struct
{
    VOS_UINT32                              UsimSupportFeatureCfg;
}USIMSUPPORTFEATURECFG_STRU;

/* NV_ID_MSP_USIM_STATUS_NEED_FCP       = 9108, */
typedef struct
{
    VOS_UINT32                              USIM_Status_Need_Fcp;
}USIM_STATUS_NEED_FCP_STRU;

/* NV_ID_MSP_USIM_OPS_FILE_CONFIG       = 9126, */

/* NV_ID_MSP_SIM_OPS_FILE_CONFIG        = 9127, */

/* NV_ID_MSP_TEST_CARD_CONFIG           = 9129, */


typedef struct
{
   VOS_UINT32  FLMidPrioThred;        /*NV*/
}NV_ID_FLASH_LESS_MID_THRED_STRU;

typedef struct
{
    VOS_UINT32  AuthType;             /*AuthorityType*/
}NV_MSP_AUTH_TYPE_STRU;

typedef struct
{
    VOS_UINT32  AuthVer;             /*AuthorityVer*/
}NV_MSP_AUTH_VER_STRU;


typedef struct
{
    VOS_UINT32  UdpValue;             /*UDP product id*/
}NV_UDP_TYPE_STRU;


typedef struct
{
    VOS_UINT32 ulAgentFlag;     /*1 0 */
	VOS_UINT8 ulRandData[256];  /**/
}NV_AGENT_FLAG_STRU;

typedef struct
{
    VOS_INT16 ssLevel[4];
    VOS_INT16 ssValue[4];
}NV_RSRP_CFG_STRU;

typedef struct
{
    VOS_INT16 ssLevel[4];
    VOS_INT16 ssValue[4];
}NV_ECIO_CFG_STRU;

typedef struct
{
    VOS_INT16 ssLevel[4];
    VOS_INT16 ssValue[4];
}NV_RSCP_CFG_STRU;

typedef struct
{
   VOS_UINT32 FLMidPrioThred;
}NV_ITEM_FLASH_LESS_MID_THRED_STRU;

typedef struct
{
    VOS_UINT32 ulAgentFlag; /*1 0 */
	VOS_UINT8 ulRandData[260];  /**/
}NV_ITEM_AGENT_FLAG_STRU;

typedef struct
{
    VOS_UINT32 ulSocpDelayWriteFlg;/* SOCP */
    VOS_UINT32 ulGuSocpLevel;      /* GU SOCPBUFFER */
    VOS_UINT32 ulLSocpLevel;       /* L SOCPBUFFER */
    VOS_UINT32 ulTimeOutValue;     /* SOCPBUFFER */
}NV_ITEM_SOCP_LOG_CFG_STRU;
typedef struct
{
    VOS_UINT32 ulSocpDelayWriteFlg;/* SOCP */
    VOS_UINT32 ulGuSocpLevel;      /* GU SOCPBUFFER */
    VOS_UINT32 ulLSocpLevel;       /* L SOCPBUFFER */
    VOS_UINT32 ulTimeOutValue;     /* SOCPBUFFER */
}NV_SOCP_LOG_CFG_STRU;

typedef struct
{
    VOS_UINT32 ulTcxoRsmTime;     /* TCXO,us */
    /*U32MSP*/
    VOS_UINT32 ulPowerSwich:1;      /* bit 0 MSPDSP 0:  1:*/
    VOS_UINT32 ulVoteSwitch:1;      /* bit 1 MSPDSP 0:  1:*/

    VOS_UINT32 ulReserve:6;

    VOS_UINT32 ulMspPowerup:8;      /* MSPslice */
    VOS_UINT32 ulDspTcmResume:8;    /* DSPslice */
    VOS_UINT32 ulInterval:8;        /* slice */
}NV_TL_DRX_RESUME_TIME_STRU;
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif

