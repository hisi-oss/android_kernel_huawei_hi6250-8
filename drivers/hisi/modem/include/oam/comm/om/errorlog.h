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

#ifndef __ERRORLOG_H__
#define __ERRORLOG_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "v_typdef.h"
//#include "OmCodecInterface.h"
#include "NasNvInterface.h"
#include "TafNvInterface.h"

#pragma pack(4)

/*****************************************************************************
   
******************************************************************************/
#define MNTN_ERRLOG_DIR                     "/mnvm3:0/Errlog"
#define MNTN_ERRLOG0_PATH                   "/mnvm3:0/Errlog/Errorlog0.bin"  /*log0*/
#define MNTN_ERRLOG1_PATH                   "/mnvm3:0/Errlog/Errorlog1.bin"  /*log1*/
#define MNTN_ERRLOG_UNITARY_DIR             "/modem_log/Errlog"
#define MNTN_ERRLOG0_UNITARY_PATH           "/modem_log/Errlog/Errorlog0.bin"  /*log0*/
#define MNTN_ERRLOG1_UNITARY_PATH           "/modem_log/Errlog/Errorlog1.bin"  /*log1*/


#define MNTN_ERRLOG_IMEI_SIZE               (16)
#define MNTN_ERRLOG_HARDVERSION_SIZE        (32)
#define MNTN_ERRLOG_SOFTVERSION_SIZE        (32)
#define IMSI_RECORD_LEN						(9)

#define MNTN_ERRLOG_MAXSIZE                 (0x10000)

/* PC2 */
#define NAS_MNTN_PC_ACTIVE_EXPIRE_TIMES     (2)

/* PDP */
#define NAS_MNTN_SM_REJ_CAUSE_INVALID       (0xff)
#define MNTN_RAC_INVALID_ID                 (0xffff)
#define NAS_MNTN_IMSI_LENGTH_IN_USIM        (9)
#define NAS_MNTN_CS_ATTEMPT_MAX             (4)
#define NAS_MNTN_PS_ATTEMPT_MAX             (5)
#define NAS_MNTN_MAX_ASCII_ADDRESS_NUM      (20)
#define NAS_MNTN_MAX_HIGH_PLMN_NUM          (16)                                    /* PLMN RRC_MAX_HIGH_PLMN_NUM*/
#define NAS_MNTN_LOW_PLMN_NUM               (16)                                    /* PLMN RRC_MAX_LOW_PLMN_NUM*/
/* ERROR LOG55 */
/* 5INDEX0 */
#define NAS_MNTN_AVAILABLE_PLMN_SRCH_TIMER_LENGTH_ZERO      (0)

/* 55 */
#define NAS_MNTN_AVAILABLE_PLMN_SRCH_TIMER_COUNTER_TIMES    (5)

/* ERROR LOG */
#define NAS_MNTN_ERRORLOG_SERVICE_UNAVAILABLE_EVENT_MAX     (10)

/* ERROR LOG */
#define NAS_MNTN_ERRORLOG_PLMN_UNAVAILABLE_EVENT_MAX        (30)

/* ERROR LOGPDP */
#define NAS_MNTN_ERRORLOG_ACTIVATE_FAIL_EVENT_MAX           (15)

/* ERROR LOG */
#define NAS_MNTN_ERRORLOG_SMS_MO_FAILURE_MAX                (5)

/*30*/
#define GAS_MNTN_WEAK_SIGNAL_LIST_MAX_NUM                       (30)

/* ERROR LOGME */
#define NAS_MNTN_ERRORLOG_ME_FILE_ERROR_MAX                 (1)

#define NAS_MNTN_MAX_LOG_EVENT_STATE_NUM                    (100)              /*  */

/*******************************************************************************
   
*****************************************************************************/
/*****************************************************************************
     : MNTN_WRITEFLASH_EVENT_ENUM
   : ulMsgName
*****************************************************************************/
enum MNTN_WRITEFLASH_EVENT_ENUM
{
    /*  */                              /*ID*/              /*  */
    MNTN_VERSION_INFO_EVENT                     = 0x00000000,           /* _H2ASN_MsgChoice MNTN_VERSION_INFO_EVENT_STRU */
    MNTN_NAS_ERRORLOG_ACTIVATE_FAIL_EVENT       = 0x00000001,           /* _H2ASN_MsgChoice NAS_MNTN_ACTIVE_FAIL_EVENT_STRU */
    MNTN_NAS_ERRORLOG_PLMN_UNAVAILABLE_EVENT    = 0x00000002,           /* _H2ASN_MsgChoice NAS_MNTN_PLMN_UNAVAILABLE_EVENT_STRU */
    MNTN_NAS_ERRORLOG_SERVICE_UNAVAILABLE_EVENT = 0x00000003,           /* _H2ASN_MsgChoice NAS_MNTN_SERVICE_UNAVAILABLE_EVENT_STRU */
    MNTN_NAS_ERRORLOG_SMS_MO_FAILURE            = 0x00000004,           /* _H2ASN_MsgChoice NAS_MNTN_SMS_MO_FAIL_EVENT_STRU */
    MNTN_NAS_ERRORLOG_CS_CHANNEL_OPEN_FAILURE   = 0x00000005,           /* _H2ASN_MsgChoice NAS_MNTN_CS_CHANNEL_OPEN_FAILURE_EVENT_STRU */
    MNTN_NAS_ERRORLOG_CS_MED_TIMEOUT            = 0x00000006,           /* _H2ASN_MsgChoice NAS_MNTN_CS_MED_TIMEOUT_EVENT_STRU */
    MNTN_NAS_ERRORLOG_SMS_ME_ERROR              = 0x00000007,           /* _H2ASN_MsgChoice NAS_MNTN_SMS_ME_ERROR_EVENT_STRU */

    MNTN_GAS_INIT_WEAK_SIGNAL_EVENT             = 0x00000201,           /* _H2ASN_MsgChoice GAS_MNTN_INIT_WEAK_SIGNAL_EVT_STRU */

    MNTN_GAS_PERIOD_WEAK_SIGNAL_LIST_EVENT      = 0x00000202,            /* _H2ASN_MsgChoice GAS_MNTN_PERIOD_WEAK_SIGNAL_LIST_EVT_STRU */

    MNTN_WAS_NO_SIGNAL_EVENT                    = 0x00000301,           /* _H2ASN_MsgChoice WAS_MNTN_NO_SIGNAL_EVENT_STRU*/
    MNTN_WAS_WEAK_SIGNAL_SAMPLE_EVENT           = 0x00000302,           /* _H2ASN_MsgChoice WAS_MNTN_WEAK_SIGNAL_SAMPLE_EVENT_STRU*/
    MNTN_OAM_NO_SIM_CARD_EVENT                  = 0x00000401,           /* _H2ASN_MsgChoice OAM_MNTN_NO_SIM_CARD_EVENT_STRU */
    MNTN_OAM_SIM_CARD_LOST_EVENT                = 0x00000402,           /* _H2ASN_MsgChoice OAM_MNTN_SIM_CARD_LOST_EVENT_STRU */
    MNTN_OAM_PCV_QUNUE_FULL_EVENT               = 0x00000403,           /* _H2ASN_MsgChoice OAM_MNTN_PCV_ERRLOG_EVENT_STRU */
    MNTN_OAM_PCV_DATA_EXCEPTION_EVENT           = 0x00000404,           /* _H2ASN_MsgChoice OAM_MNTN_PCV_ERRLOG_EVENT_STRU */
    MNTN_OAM_MNTN_NV_ERRLOG_EVENT               = 0x00000405,           /* _H2ASN_MsgChoice OAM_MNTN_NV_ERRLOG_EVENT_STRU */
    MNTN_OAM_MNTN_WD_COUNT_ERRLOG_EVENT         = 0x00000406,           /* _H2ASN_MsgChoice OAM_MNTN_WD_COUNT_ERRLOG_EVENT_STRU */
    MNTN_OAM_PORT_NUM_ERRLOG_EVENT              = 0x00000407,           /* _H2ASN_MsgChoice OAM_MNTN_PORT_ERRLOG_EVENT_STRU */
    MNTN_USB_ENUMERATE_STATUS_EVENT             = 0x00000501,           /* _H2ASN_MsgChoice USB_MNTN_ENUMERATE_STATUS_EVENT_STRU */
    MNTN_USB_INSTALL_SUCCESS_EVENT              = 0x00000502,           /* _H2ASN_MsgChoice USB_MNTN_INSTALL_SUCCESS_EVENT_STRU */
    MNTN_USB_RESET_ABNORMAL_EVENT               = 0x00000503,           /* _H2ASN_MsgChoice USB_MNTN_RESET_ABNORMAL_EVENT_STRU */
    MNTN_MED_VS_ERRLOG_EVENTS_DMA_MIC_RESET     = 0x00000601,           /* _H2ASN_MsgChoice MED_MNTN_CS_ERR_EVENT_STRU */
    MNTN_MED_VS_ERRLOG_EVENTS_DMA_SPK_RESET     = 0x00000602,           /* _H2ASN_MsgChoice MED_MNTN_CS_ERR_EVENT_STRU */
    MNTN_MED_VS_ERRLOG_EVENTS_W_DEC_INT_LOST    = 0x00000603,           /* _H2ASN_MsgChoice MED_MNTN_CS_ERR_EVENT_STRU */
    MNTN_MED_VS_ERRLOG_EVENTS_WBBP_DATA_NONE    = 0x00000604,           /* _H2ASN_MsgChoice MED_MNTN_CS_ERR_EVENT_STRU */
    MNTN_MED_VS_ERRLOG_EVENTS_WBBP_DATA_BAD     = 0x00000605,           /* _H2ASN_MsgChoice MED_MNTN_CS_ERR_EVENT_STRU */
    MNTN_MED_VS_ERRLOG_EVENTS_W_DECIPHER_LOST   = 0x00000606,           /* _H2ASN_MsgChoice MED_MNTN_CS_ERR_EVENT_STRU */
    MNTN_MED_VS_ERRLOG_EVENTS_GSM_BFI_FRAME     = 0x00000607,           /* _H2ASN_MsgChoice MED_MNTN_CS_ERR_EVENT_STRU */
    MNTN_MED_VS_ERRLOG_EVENTS_CODEC_SID_FRAME   = 0x00000608,           /* _H2ASN_MsgChoice MED_MNTN_CS_ERR_EVENT_STRU */
    MNTN_MED_VS_ERRLOG_EVENTS_PCV_INTERPOLATE   = 0x00000609,           /* _H2ASN_MsgChoice MED_MNTN_CS_ERR_EVENT_STRU */
    MNTN_MED_VS_ERRLOG_EVENTS_PCV_RINGBUF_FULL  = 0x0000060A,           /* _H2ASN_MsgChoice MED_MNTN_CS_ERR_EVENT_STRU */
    MNTN_DRV_HIGH_STACK_RECORD                  = 0x00000701,           /* _H2ASN_MsgChoice HIGH_STACK_TASK_STR */
    MNTN_DRV_SD_ERRLOG_RECORD                   = 0x00000702,           /* _H2ASN_MsgChoice SD_TRANSFER_ERROR_ST */
    MNTN_DRV_WIFI_ERRLOG_RECORD                 = 0x00000703,           /* _H2ASN_MsgChoice WIFI_TARGET_ASSERT_ERROR_ST */
    MNTN_DRV_PMU_WRNLOG_RECORD                  = 0x00000704,           /* _H2ASN_MsgChoice MNTN_DRV_PMU_ERROR_ST */
    MNTN_DRV_PMU_ERRLOG_RECORD                  = 0x00000705,           /* _H2ASN_MsgChoice MNTN_DRV_PMU_ERROR_ST */
    MNTN_DRV_SYSTEM_RESET_RECORD                = 0x00000706,           /* _H2ASN_MsgChoice DRV_MNTN_SYSTEM_RESET_STRU */

    MNTN_SPY_QOS_LIMIT_EVENT                    = 0x00000801,           /* _H2ASN_MsgChoice OAM_MNTN_SPY_ERROR_EVENT_STRU */
    MNTN_SPY_SOFTOFF_EVENT                      = 0x00000802,           /* _H2ASN_MsgChoice OAM_MNTN_SPY_ERROR_EVENT_STRU */
    MNTN_SPY_PWOER_DOWN_EVENT                   = 0x00000803,           /* _H2ASN_MsgChoice OAM_MNTN_SPY_ERROR_EVENT_STRU */
    MNTN_OAM_SOCP_ERROR_EVENT                   = 0x00000A01,
    MNTN_OAM_ICC_ERROR_EVENT                    = 0x00000B01,
    MNTN_ERRLOG_BUTT                            = 0xFFFFFFFF
};
typedef VOS_INT32 MNTN_WRITEFLASH_EVENT_ENUM_UINT32;

typedef struct
{
    VOS_UINT32                                              ulInfoLen;          /* _H2ASN_Skip */ /*,:*/
    VOS_UINT32                                              ulErrNo;            /* _H2ASN_Skip */
    VOS_UINT32                                              ulBoardtime;
    VOS_UINT32                                              ulSliceTime;
}MNTN_HEAD_INFO_STRU;

typedef struct
{
    MNTN_HEAD_INFO_STRU    stRecordHead;
    VOS_UINT32             ulStatusReg;
}MNTN_DRV_PMU_ERROR_ST;

/*****************************************************************************
     : MNTN_ME_OPERATION_ENUM
   : ME
*****************************************************************************/
enum MNTN_ME_OPERATION_ENUM
{
    MNTN_ME_OPERATION_READ,
    MNTN_ME_OPERATION_WRITE,
    MNTN_ME_OPERATION_BUTT
};
typedef VOS_INT32 MNTN_ME_OPERATION_ENUM_UINT32;


/*****************************************************************************
     : NAS_MNTN_ACTIVE_FAIL_TYPE_ENUM
   : PDPPS
             ,BACKOFF
*****************************************************************************/
enum NAS_MNTN_ACTIVE_FAIL_TYPE_ENUM
{
    NAS_MNTN_ACTIVE_FAIL_TYPE_PS_SERVICE_UNAVAILABLE = 0,
    NAS_MNTN_ACTIVE_FAIL_TYPE_ACTIVE_TIMEOUT,
    NAS_MNTN_ACTIVE_FAIL_TYPE_ACTIVE_REJECT,
    NAS_MNTN_ACTIVE_FAIL_TYPE_BACKOFF_ALG_NOT_ALLOWED,
    NAS_MNTN_ACTIVE_FAIL_TYPE_BUTT
};
typedef VOS_UINT32 NAS_MNTN_ACTIVE_FAIL_TYPE_ENUM_UINT32;

/*****************************************************************************
     : NAS_MNTN_SYS_SUBMODE_ENUM
   :
 ASN.1 :
   : 
*****************************************************************************/
enum NAS_MNTN_SYS_SUBMODE_ENUM
{
    NAS_MNTN_SYS_SUBMODE_NULL                  = 0,                /*  */
    NAS_MNTN_SYS_SUBMODE_GSM                   = 1,                /* GSM */
    NAS_MNTN_SYS_SUBMODE_GPRS                  = 2,                /* GPRS */
    NAS_MNTN_SYS_SUBMODE_EDGE                  = 3,                /* EDGE */
    NAS_MNTN_SYS_SUBMODE_WCDMA                 = 4,                /* WCDMA */
    NAS_MNTN_SYS_SUBMODE_HSDPA                 = 5,                /* HSDPA */
    NAS_MNTN_SYS_SUBMODE_HSUPA                 = 6,                /* HSUPA */
    NAS_MNTN_SYS_SUBMODE_HSDPA_HSUPA           = 7,                /* HSDPA+HSUPA */
    NAS_MNTN_SYS_SUBMODE_BUTT
};
typedef VOS_UINT8  NAS_MNTN_SYS_SUBMODE_ENUM_UINT8;

/*****************************************************************************
     : NAS_MNTN_SEND_DOMAIN_STATUS_ENUM
   :
 ASN.1 :
   : 
*****************************************************************************/
enum NAS_MNTN_SEND_DOMAIN_STATUS_ENUM
{
    NAS_MNTN_SEND_DOMAIN_STATUS_UNAVAILABLE,
    NAS_MNTN_SEND_DOMAIN_STATUS_AVAILABLE
};
typedef VOS_UINT32 NAS_MNTN_SEND_DOMAIN_STATUS_ENUM_UINT32;

/*****************************************************************************
     : OSA_MNTN_WD_COUNT_ENUM
   :
 ASN.1 :
   :
*****************************************************************************/
enum OSA_MNTN_WD_COUNT_ENUM
{
    OSA_MNTN_WD_COUNT_TIMER         = 0,
    OSA_MNTN_WD_COUNT_RTC_TIMER,
    OSA_MNTN_WD_COUNT_MESSAGE,
    OSA_MNTN_WD_COUNT_PS_MEMORY,
    OSA_MNTN_WD_COUNT_APP_MEMORY,
    OSA_MNTN_WD_COUNT_BUTT
};
typedef VOS_UINT32 OSA_MNTN_WD_COUNT_ENUM_UINT32;
/*****************************************************************************
   STRUCT
*****************************************************************************/

typedef int * TIMER_HANDLE;

/*******************************************************************************
     : MNTN_VERSION_INFO_EVENT_STRU
   :
 ASN.1 :
   : 
*******************************************************************************/
typedef struct
{
    MNTN_HEAD_INFO_STRU                 stRecordHead;
    IMEI_STRU                           stIMEI;
    VOS_CHAR                            acHardVersion[MNTN_ERRLOG_HARDVERSION_SIZE];
    VOS_CHAR                            acSoftVersion[MNTN_ERRLOG_SOFTVERSION_SIZE];
}MNTN_VERSION_INFO_EVENT_STRU;

/*******************************************************************************
     : USB_MNTN_INSTALL_SUCCESS_EVENT_STRU
   :
 ASN.1 :
   : 
*******************************************************************************/
typedef struct
{
    MNTN_HEAD_INFO_STRU              stRecordHead;
    VOS_UINT32                       ulRewindCommand;
    VOS_UINT32                       ulU2diag;
}USB_MNTN_INSTALL_SUCCESS_EVENT_STRU;

/*******************************************************************************
     : USB_MNTN_ENUMERATE_STATUS_EVENT_STRU
   :
 ASN.1 :
   : 
*******************************************************************************/
typedef struct
{
    MNTN_HEAD_INFO_STRU             stRecordHead;
    VOS_UINT32                      ulU2diag;
    VOS_UINT8                       ucFlag;      /*differentiate rewind and timeout*/
    VOS_UINT8                       ucUsbSpeed;
    VOS_UINT8                       ucUsbStatus;
    VOS_UINT8                       ucReserved;
}USB_MNTN_ENUMERATE_STATUS_EVENT_STRU;

/*******************************************************************************
     : USB_MNTN_RESET_ABNORMAL_EVENT_STRU
   :
 ASN.1 :
   : usb
*******************************************************************************/
typedef struct
{
    MNTN_HEAD_INFO_STRU             stRecordHead;
    VOS_UINT32                      ulU2diag;
    VOS_UINT8                       ucUsbStatus;
    VOS_UINT8                       ucUsbSpeed;
    VOS_UINT8                       ucSCSITimeoutFlag;
    VOS_UINT8                       ucSCSICommand;
    VOS_UINT8                       ucLastIntrIndex;
    VOS_UINT8                       aucReserve[3];
    VOS_UINT32                      ulLedStatus;
}USB_MNTN_RESET_ABNORMAL_EVENT_STRU;

/*******************************************************************************
     : DRV_MNTN_SYSTEM_RESET_STR
   :
 ASN.1 :
   : 
*******************************************************************************/
typedef struct
{
    MNTN_HEAD_INFO_STRU                    stRecordHead;
    VOS_UINT32                             ulRebootReason ;
    VOS_UINT32                             ulModeId;
    VOS_UINT32                             ulArg1;
    VOS_UINT32                             ulArg2;
    VOS_UINT8                              Imsi[IMSI_RECORD_LEN];
    VOS_UINT8                              ImsiStatus;
    VOS_UINT8                              reserv[2];
}DRV_MNTN_SYSTEM_RESET_STRU;

/*****************************************************************************
     : NAS_MNTN_SMS_ME_ERROR_EVENT_STRU
   :
 ASN.1 :
   :ME
             
*******************************************************************************/
typedef struct
{
    MNTN_HEAD_INFO_STRU                 stHeader;
    MNTN_ME_OPERATION_ENUM_UINT32       enOperation;
    VOS_UINT32                          ulErrorNo;
} NAS_MNTN_SMS_ME_ERROR_EVENT_STRU;

/*******************************************************************************
     : NAS_MNTN_PDP_ACTIVE_FAIL_STRU
   :
 ASN.1 :
   : :
              PS
             
             GMMPS
*******************************************************************************/
typedef struct
{
    NAS_MNTN_ACTIVE_FAIL_TYPE_ENUM_UINT32                   enFailType;
    VOS_UINT8                                               ucSmCause;
    /* 3380 */
    VOS_UINT8                                               ucRegisterFlg;
    VOS_UINT8                                               aucReserved1[2];
}NAS_MNTN_PDP_ACTIVE_FAIL_STRU;

/*******************************************************************************
     : MNTN_PLMN_ID_STRU
   :
 ASN.1 :
   : PLMN
*******************************************************************************/
typedef struct
{
    VOS_UINT32                        ulMcc;
    VOS_UINT32                        ulMnc;
}MNTN_PLMN_ID_STRU;/* MMC_PLMN_ID_STRU */

/*******************************************************************************
     : MNTN_RAI_INFO_STRU
   :
 ASN.1 :
   : 
*******************************************************************************/
typedef struct
{
    MNTN_PLMN_ID_STRU                   stPlmn;
    VOS_UINT16                          usLac;
    VOS_UINT16                          usRac;
}MNTN_RAI_INFO_STRU;

/*******************************************************************************
     : NAS_MNTN_USIM_INFO_STRU
   :
 ASN.1 :
   : NAS(U)SIM:
             (SIMUSIM)PIN
             (U)SIMIMSI
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCardStatus;                           /* :  */
    VOS_UINT8                           ucCardType;                             /* : SIMUSIMUIMCSIM */
    VOS_UINT8                           ucCardMediumType;                       /* Medium:  */
    VOS_UINT8                           ucPinStatus;                            /* PIN: READY*/
    VOS_UINT8                           aucImsi[NAS_MNTN_IMSI_LENGTH_IN_USIM];  /* IMSI */
    VOS_UINT8                           aucReserved[3];
    MNTN_PLMN_ID_STRU                   stRplmn;
}NAS_MNTN_USIM_INFO_STRU;

/*******************************************************************************
     : NAS_MNTN_POSITION_INFO_STRU
   :
 ASN.1 :
   : 
             IDCSPS
             
*******************************************************************************/
typedef struct
{
    MNTN_RAI_INFO_STRU                      stRai;                                  /* LAC: g_MmcGlobalCtrl.CurLai.ulLac */
    VOS_UINT32                              ulCellId;                               /* CELL ID: gstMmcCellInfo.aulCellId[0]*/
    NAS_MNTN_SYS_SUBMODE_ENUM_UINT8         enSysSubMode;                           /* RRMM_SYS_INFO_IND_STRU */
    VOS_UINT8                               ucRat;
    VOS_UINT8                               ucNetworkMode;                          /* NETWORK MODE: g_MmcGlobalCtrl.ucNwMode */
    VOS_UINT8                               ucSensorState;                          /* Sensor */
}NAS_MNTN_POSITION_INFO_STRU;

/*******************************************************************************
     : NAS_MNTN_CS_UNAVAILABLE_INFO_STRU
   :
 ASN.1 :
   : CS
             
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucTimes;
    VOS_UINT8                           aucReserved[3];
    VOS_UINT32                          aulCause[NAS_MNTN_CS_ATTEMPT_MAX];                                             /*                              */
    VOS_BOOL                            bRecordRequired;
}NAS_MNTN_CS_UNAVAILABLE_INFO_STRU;

/*******************************************************************************
     : NAS_MNTN_PS_UNAVAILABLE_INFO_STRU
   :
 ASN.1 :
   : PS
             
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucTimes;
    VOS_UINT8                           aucReserved[3];
    VOS_UINT32                          aulCause[NAS_MNTN_PS_ATTEMPT_MAX];                                             /*                              */
    VOS_BOOL                            bRecordRequired;
}NAS_MNTN_PS_UNAVAILABLE_INFO_STRU;

/*******************************************************************************
     : NAS_MNTN_SERVICE_INFO_STRU
   :
 ASN.1 :
   : 
             CSPS
*******************************************************************************/
typedef struct
{
    NAS_MNTN_CS_UNAVAILABLE_INFO_STRU   stCsUnavailable;
    NAS_MNTN_PS_UNAVAILABLE_INFO_STRU   stPsUnavailable;
}NAS_MNTN_SERVICE_INFO_STRU;

/*******************************************************************************
     : NAS_MNTN_MO_SERVICE_INFO_STRU
   :
 ASN.1 :
   : UST
             (U)SIMSMSS,SMS,SMSR,SMSP
             MO-SMS Control by USIM
*******************************************************************************/
typedef struct
{
    VOS_BOOL                            bEfSmssFlag;                            /*EFSMSS*/
    VOS_BOOL                            bEfSmsFlag;                             /*SMS Storage */
    VOS_BOOL                            bEfSmsrFlag;                            /*SMSR Storage */
    VOS_BOOL                            bEfSmspFlag;                            /*SMSP */
    VOS_BOOL                            bMoSmsCtrlFlag;                         /*MO-SMS Control by USIM*/
}NAS_MNTN_MO_SERVICE_INFO_STRU;

/*******************************************************************************
     : NAS_MNTN_USIM_STATUS_INFO_STRU
   :
 ASN.1 :
   : 
             (U)SIMTAF
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucUsimStatus;                           /*SIM*/
    VOS_UINT8                           ucPowerState;                           /**/
    VOS_UINT8                           aucReserved[2];
} NAS_MNTN_USIM_STATUS_INFO_STRU;/*MN_MSG_USIM_STATUS_INFO_STRU*/

/*******************************************************************************
     : NAS_MNTN_ASCII_ADDR_STRU
   :
 ASN.1 :
   : 
             ASCII
*******************************************************************************/
/*Content of Sms BCD Address*/
typedef struct
{
    VOS_UINT8                           ucNumType;                              /*type of number*/
    VOS_UINT8                           ucNumPlan;                              /*Numbering plan identification*/
    VOS_UINT8                           aucReserve1[2];
    VOS_UINT32                          ulLen;                                  /*Length of AsicNum*/
    VOS_UINT8                           aucAsciiNum[NAS_MNTN_MAX_ASCII_ADDRESS_NUM + 1];   /*array  of ASCII Num*/
    VOS_UINT8                           aucReserve2[3];
} NAS_MNTN_ASCII_ADDR_STRU;/*MN_MSG_ASCII_ADDR_STRU*/

/*******************************************************************************
     : NAS_MNTN_SMS_MO_INFO_STRU
   :
 ASN.1 :
   : 
             UST
             RP-ERRORRP-Cause
1.       : 2013626
         : f62575
     : V9R1 STK ucRpCause-> ulMoFailCause
*******************************************************************************/
typedef struct
{
    NAS_MNTN_MO_SERVICE_INFO_STRU       stUstInfo;
    NAS_MNTN_USIM_STATUS_INFO_STRU      stMsgStatus;
    NAS_MNTN_ASCII_ADDR_STRU            stScAddr;                               /*destination addr of sms*/
    NAS_MNTN_ASCII_ADDR_STRU            stDestAddr;                             /*destination addr of sms*/
    VOS_UINT32                          ulMoFailCause;
}NAS_MNTN_SMS_MO_INFO_STRU;

/*******************************************************************************
     : NAS_MNTN_LOW_PLMN_INFO_STRU
   :
 ASN.1 :
   : PLMN
             PLMNRSCP
*******************************************************************************/
typedef struct
{
    MNTN_PLMN_ID_STRU                   stPlmnId;                               /* PLMN ID    */
    VOS_INT32                           lRscp;                                  /* RSCP */
}NAS_MNTN_LOW_PLMN_INFO_STRU;/*RRC_LOW_PLMN_INFO_STRU*/

/*******************************************************************************
     : NAS_MNTN_PLMN_AVAILABLE_STRU
   :
 ASN.1 :
   : PLMN
             PLMNPLMNPLMNPLMN
*******************************************************************************/
typedef struct
{
    VOS_UINT32                          ulHighPlmnNum;                          /* PLMN */
    MNTN_PLMN_ID_STRU                   astHighPlmnList[NAS_MNTN_MAX_HIGH_PLMN_NUM];   /* PLMN   */
    VOS_UINT32                          ulLowPlmnNum;                           /* PLMN */
    NAS_MNTN_LOW_PLMN_INFO_STRU         astLowPlmnList[NAS_MNTN_LOW_PLMN_NUM];     /* PLMN   */
}NAS_MNTN_PLMN_AVAILABLE_STRU;/*RRC_PLMN_ID_LIST_STRU*/

/*******************************************************************************
     : NAS_MNTN_SERVICE_UNAVAILABLE_EVENT_STRU
   :
 ASN.1 :
   : UE
             NASSIM
*******************************************************************************/
typedef struct
{
    MNTN_HEAD_INFO_STRU                 stHeader;
    NAS_MNTN_USIM_INFO_STRU             stUsimInfo;
    NAS_MNTN_POSITION_INFO_STRU         stPositionInfo;
    VOS_UINT32                          ulBand;
    /* PLMNASN */
    VOS_UINT8                           aucPlmnAttempt[4];
}NAS_MNTN_PLMN_UNAVAILABLE_EVENT_STRU;

/*******************************************************************************
     : NAS_MNTN_SERVICE_UNAVAILABLE_EVENT_STRU
   :
 ASN.1 :
   : UE
             NASSIMUE
*******************************************************************************/
typedef struct
{
    MNTN_HEAD_INFO_STRU                 stHeader;
    NAS_MNTN_USIM_INFO_STRU             stUsimInfo;
    NAS_MNTN_POSITION_INFO_STRU         stPositionInfo;
    NAS_MNTN_SERVICE_INFO_STRU          stServiceInfo;
}NAS_MNTN_SERVICE_UNAVAILABLE_EVENT_STRU;

/*******************************************************************************
     : NAS_MNTN_SMS_MO_FAIL_EVENT_STRU
   :
 ASN.1 :
   : 
             NAS(U)SIM
             CSPS
*******************************************************************************/
typedef struct
{
    MNTN_HEAD_INFO_STRU                 stHeader;
    NAS_MNTN_USIM_INFO_STRU             stUsimInfo;
    NAS_MNTN_POSITION_INFO_STRU         stPositionInfo;
    NAS_MNTN_SMS_MO_INFO_STRU           stMoFail;
    NAS_MNTN_SEND_DOMAIN_STATUS_ENUM_UINT32                 enCsStatus;
    NAS_MNTN_SEND_DOMAIN_STATUS_ENUM_UINT32                 enPsStatus;
}NAS_MNTN_SMS_MO_FAIL_EVENT_STRU;

/*******************************************************************************
     : NAS_MNTN_ACTIVE_FAIL_EVENT_STRU
   :
 ASN.1 :
   : 
             NASSIMPDPPS
*******************************************************************************/
typedef struct
{
    MNTN_HEAD_INFO_STRU                 stHeader;
    NAS_MNTN_USIM_INFO_STRU             stUsimInfo;
    NAS_MNTN_POSITION_INFO_STRU         stPositionInfo;
    NAS_MNTN_PDP_ACTIVE_FAIL_STRU       stPsActiveFail;
}NAS_MNTN_ACTIVE_FAIL_EVENT_STRU;

/*******************************************************************************
     : NAS_MNTN_MSG_INFO_STRU
   :
 ASN.1 :
   : ERROR LOGMO
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucMoFailureCounter;
    VOS_UINT8                           ucMeFileErrorCounter;
    VOS_UINT8                           aucReserved1[2];
}NAS_MNTN_MSG_INFO_STRU;

/*******************************************************************************
     : NAS_MNTN_SM_INFO_STRU
   :
 ASN.1 :
   : SMERROR LOGPDP
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucPdpActiveFailureCounter;
    VOS_UINT8                           aucReserved1[3];
}NAS_MNTN_SM_INFO_STRU;

typedef struct
{
    NAS_MNTN_CS_UNAVAILABLE_INFO_STRU   stCsUnavailableInfo;
    NAS_MNTN_PS_UNAVAILABLE_INFO_STRU   stPsUnavailableInfo;
    NAS_MNTN_PLMN_AVAILABLE_STRU        stPlmnAvailableList;
    VOS_UINT8                           ucServiceUnavailableCounter;
    VOS_UINT8                           ucPlmnUnavailableCounter;
    VOS_UINT8                           aucReserved1[2];
}NAS_MNTN_MM_INFO_STRU;

/*******************************************************************************
     : NAS_MNTN_CS_CHANNEL_OPEN_FAILURE_EVENT_STRU
   :
 ASN.1 :
   : CSERROR LOG
*******************************************************************************/
typedef struct
{
    MNTN_HEAD_INFO_STRU                 stHeader;
    NAS_MNTN_USIM_INFO_STRU             stUsimInfo;                             /* NASSIM */
    VOS_UINT16                          usPort;                                 /*  */
    VOS_UINT8                           aucReserved1[2];                        /*  */
    VOS_UINT32                          ulOmOperResult;                         /* OM */
}NAS_MNTN_CS_CHANNEL_OPEN_FAILURE_EVENT_STRU;

/*******************************************************************************
     : NAS_MNTN_CS_CHANNEL_OPEN_FAILURE_EVENT_STRU
   :
 ASN.1 :
   : VCMEDERROR LOG
*******************************************************************************/
typedef struct
{
    MNTN_HEAD_INFO_STRU                 stHeader;
    NAS_MNTN_USIM_INFO_STRU             stUsimInfo;                             /* NASSIM */
    VOS_UINT32                          ulTimerId;                              /*  */
} NAS_MNTN_CS_MED_TIMEOUT_EVENT_STRU;

#define MNTN_WAS_WEAK_SIGNAL_SAMPLE_NUMBER    (30)  /*Error LOG30*/

/*****************************************************************************
   : WAS_MNTN_FREQ_INFO_STRU
   : 
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usUlUarfcn;   /*  Integer(0 .. 16383),0xFFFF */
    VOS_UINT16                          usDlUarfcn;   /* ,0xFFFF                     */
} WAS_MNTN_FREQ_INFO_STRU;

/*****************************************************************************
   : WAS_MNTN_NO_SIGNAL_EVENT_STRU
   : 
*****************************************************************************/
typedef struct
{
    MNTN_HEAD_INFO_STRU                  stHeader;
    MNTN_RAI_INFO_STRU                   stRai;
    WAS_MNTN_FREQ_INFO_STRU              stFreqInfo;
    VOS_UINT16                           usPSC;       /*  Integer(0..511) */
    VOS_INT16                            sRscp;
    VOS_INT16                            sECN0;
    VOS_UINT8                            aucReserve1[2];     /*  */
}WAS_MNTN_NO_SIGNAL_EVENT_STRU;

/*****************************************************************************
   : WAS_MNTN_WEAK_SIGNAL_SAMPLE_EVENT_STRU
   : WAS
*****************************************************************************/
typedef struct
{
    MNTN_RAI_INFO_STRU                   stRai;       /* */
    WAS_MNTN_FREQ_INFO_STRU              stFreqInfo;  /*  */
    VOS_UINT16                           usPSC;       /*  Integer(0..511) */
    VOS_INT16                            sRscp;
    VOS_INT16                            sECN0;
    VOS_UINT16                           usErrlogIndex;/*30  */
}WAS_MNTN_WEAK_SIGNAL_CELL_INFO_STRU;

/*****************************************************************************
   : WAS_MNTN_WEAK_SIGNAL_SAMPLE_EVENT_STRU
   : WAS,30
*****************************************************************************/
typedef struct
{
    MNTN_HEAD_INFO_STRU                  stHeader;
    VOS_UINT16                           usWeakSignalNum;    /* 30 */
    VOS_UINT8                            aucReserve2[2];     /*  */
    WAS_MNTN_WEAK_SIGNAL_CELL_INFO_STRU  astWeakSignalCellInfo[MNTN_WAS_WEAK_SIGNAL_SAMPLE_NUMBER];/**/
}WAS_MNTN_WEAK_SIGNAL_SAMPLE_EVENT_STRU;
/*****************************************************************************
   : GAS_MNTN_INIT_WEAK_SIGNAL_EVT_STRU
   : GAS
*****************************************************************************/
typedef struct
{
    MNTN_HEAD_INFO_STRU                 stHeader;
    MNTN_RAI_INFO_STRU                  stRai;
    VOS_UINT16                          usArfcn;
    VOS_INT16                           sRxlev;
}GAS_MNTN_INIT_WEAK_SIGNAL_EVT_STRU;

/*****************************************************************************
   : GAS_MNTN_WEAK_SIGNAL_INFO_STRU
   : GAS
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucWeakSignalIndex;      /*30*/
    VOS_UINT8                           aucReserve1[3];
    MNTN_RAI_INFO_STRU                  stRai;                  /*:PLMNLACRAC*/
    VOS_UINT16                          usArfcn;                /**/
    VOS_INT16                           sRxlev;                 /*dBm*/
}GAS_MNTN_WEAK_SIGNAL_INFO_STRU;

/*****************************************************************************
   : GAS_MNTN_PERIOD_WEAK_SIGNAL_LIST_EVT_STRU
   : G
*****************************************************************************/
typedef struct
{
    MNTN_HEAD_INFO_STRU                  stHeader;
    VOS_UINT8                            ucWeakSignalNum;                                       /**/
    VOS_UINT8                            aucReserve1[3];
    GAS_MNTN_WEAK_SIGNAL_INFO_STRU       astWeakSignalInfo[GAS_MNTN_WEAK_SIGNAL_LIST_MAX_NUM];  /*30*/
} GAS_MNTN_PERIOD_WEAK_SIGNAL_LIST_EVT_STRU;

/*******************************************************************************
     : OAM_MNTN_NO_SIM_CARD_EVENT_STRU
   :
 ASN.1 :
   : SIM
             
*******************************************************************************/
typedef struct
{
    MNTN_HEAD_INFO_STRU                 stHeader;
}OAM_MNTN_NO_SIM_CARD_EVENT_STRU;

/*******************************************************************************
     : OAM_MNTN_SIM_CARD_LOST_EVENT_STRU
   :
 ASN.1 :
   : SIM
             
*******************************************************************************/
typedef struct
{
    MNTN_HEAD_INFO_STRU                 stHeader;
}OAM_MNTN_SIM_CARD_LOST_EVENT_STRU;

/*******************************************************************************
     : OAM_MNTN_PCV_ERRLOG_EVENT_STRU
   :
 ASN.1 :
   : PC voice 
*******************************************************************************/
typedef struct
{
    MNTN_HEAD_INFO_STRU                 stHeader;
}OAM_MNTN_PCV_ERRLOG_EVENT_STRU;

/*******************************************************************************
     : OAM_MNTN_NV_ERRLOG_EVENT_STRU
   :
 ASN.1 :
   : NV 
*******************************************************************************/
typedef struct
{
    MNTN_HEAD_INFO_STRU                 stHeader;
}OAM_MNTN_NV_ERRLOG_EVENT_STRU;

/*******************************************************************************
     : OAM_MNTN_PORT_ERRLOG_EVENT_STRU
   :
 ASN.1 :
   : OM
*******************************************************************************/
typedef struct
{
    MNTN_HEAD_INFO_STRU                 stHeader;
    VOS_UINT16                          usLineNum;
    VOS_UINT16                          usPortNum;
}OAM_MNTN_PORT_ERRLOG_EVENT_STRU;

/*******************************************************************************
     : HIGH_STACK_TASK_STR
   :
 ASN.1 :
   : DRV HIGH STACK EVENT
*******************************************************************************/
typedef struct
{
    MNTN_HEAD_INFO_STRU     stRecordHead;
    VOS_INT8                taskName[16] ;
    VOS_INT32               taskId;
    VOS_INT32               highStackSize;
    VOS_INT32               taskStackSize;
}HIGH_STACK_TASK_STR;

/*******************************************************************************
     : SD_TRANSFER_ERROR_ST
   :
 ASN.1 :
   : SD
*******************************************************************************/
typedef struct
{
   VOS_UINT32 Ebe_int;
   VOS_UINT32 Ccd_int;
   VOS_UINT32 Sbe_int;
   VOS_UINT32 Hle_int;
   VOS_UINT32 Frun_int;
   VOS_UINT32 Hto_int;
   VOS_UINT32 Drto_int;
   VOS_UINT32 Rto_int;
   VOS_UINT32 Dcrc_int;
   VOS_UINT32 Rcrc_int;
   VOS_UINT32 Rxdr_int;
   VOS_UINT32 Txdr_int;
   VOS_UINT32 Dto_int;
   VOS_UINT32 Cd_int;
   VOS_UINT32 Re_int;
}SD_ERROR_REG_BIT_ST;

typedef struct
{
    MNTN_HEAD_INFO_STRU                  stRecordHead;
    SD_ERROR_REG_BIT_ST                  stSdErrLogGetFromInt;
}SD_TRANSFER_ERROR_ST;

/*******************************************************************************
     : OAM_MNTN_WD_COUNT_ERRLOG_EVENT_STRU
   :
 ASN.1 :
   : 
*******************************************************************************/
typedef struct
{
    MNTN_HEAD_INFO_STRU                 stHeader;
    OSA_MNTN_WD_COUNT_ENUM_UINT32       enReason;
}OAM_MNTN_WD_COUNT_ERRLOG_EVENT_STRU;

/*******************************************************************************
     : OAM_MNTN_SOCP_ERROR_EVENT_STRU
   :
 ASN.1 :
   : SOCP
             
*******************************************************************************/
typedef struct
{
    MNTN_HEAD_INFO_STRU                 stHeader;
    VOS_UINT32                          ulChannelID;
    VOS_UINT32                          ulEvent;
    VOS_UINT32                          ulData;
}OAM_MNTN_SOCP_ERROR_EVENT_STRU;

/*******************************************************************************
     : OAM_MNTN_ICC_ERROR_EVENT_STRU
   :
 ASN.1 :
   : ICC
             
*******************************************************************************/
typedef struct
{
    MNTN_HEAD_INFO_STRU                 stHeader;
    VOS_UINT32                          ulChannelID;
    VOS_UINT32                          ulEvent;
    VOS_UINT32                          ulData;
}OAM_MNTN_ICC_ERROR_EVENT_STRU;

/*******************************************************************************
     : OAM_MNTN_SPY_ERROR_EVENT_STRU
   :
 ASN.1 :
   : 
             
*******************************************************************************/
typedef struct
{
    MNTN_HEAD_INFO_STRU                 stHeader;
}OAM_MNTN_SPY_ERROR_EVENT_STRU;


/*****************************************************************************
  H2ASN
*****************************************************************************/
typedef struct
{
    MNTN_WRITEFLASH_EVENT_ENUM_UINT32   enMsgID;    /*_H2ASN_MsgChoice_Export MNTN_WRITEFLASH_EVENT_ENUM_UINT32*/
                                                    /* NASASN.1MNTN_WRITEFLASH_EVENT_ENUM_UINT32 */

    VOS_UINT8                           aucMsgBlock[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          MNTN_WRITEFLASH_EVENT_ENUM_UINT32
    ****************************************************************************/
}ERR_LOG_MSG_DATA;
/*_H2ASN_Length UINT32*/

/* , ASNdll */
typedef struct
{
    VOS_UINT32                          ulInfoLen; /* _H2ASN_Skip */
    ERR_LOG_MSG_DATA                    stMsgData;
}ErrorLog_MSG;

/*****************************************************************************
  
*****************************************************************************/
extern VOS_UINT32 DIAG_ErrorLog(VOS_CHAR * cFileName,VOS_UINT32 ulFileId, VOS_UINT32 ulLine,
                VOS_UINT32 ulErrNo, VOS_VOID * pBuf, VOS_UINT32 ulLen);
#define MNTN_RecordErrorLog(ulErrNo,pBuf,ulLen) \
    DIAG_ErrorLog(__FILE__,THIS_FILE_ID,__LINE__,ulErrNo,pBuf,ulLen)

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif/* end of ErrorLog.h */

