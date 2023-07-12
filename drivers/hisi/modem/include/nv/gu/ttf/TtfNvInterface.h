/******************************************************************************

  Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : TtfNvInterface.h
  Description     : TtfNvInterface.h header file
  History         :
  1.       : 2017117
           : s00184266
       : dts2017011702266, DESCRIPTION

******************************************************************************/

#ifndef __TTFNVINTERFACE_H__
#define __TTFNVINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include "vos.h"

/*****************************************************************************
  2 Macro
*****************************************************************************/

#define TTF_MEM_MAX_POOL_NUM                (5)
#define TTF_MEM_MAX_CLUSTER_NUM             (8)

#define FC_UL_RATE_MAX_LEV                  (11)
#define TTF_MEM_POOL_NV_NUM                 (TTF_MEM_MAX_POOL_NUM + 1)
#define FC_ACPU_DRV_ASSEM_NV_LEV            (4)

#define BASTET_HPRTODCH_SUPPORT             (0x01)
#define BASTET_CHNL_LPM_SUPPORT             (0x02)
#define BASTET_ASPEN_SUPPORT                (0x04)

#define NV_PLATFORM_MAX_RAT_NUM             (7)               /*  */

#define NV_PLATFORM_MAX_MODEM_NUM           (8)

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/

enum FC_MEM_THRESHOLD_LEV_ENUM
{
    FC_MEM_THRESHOLD_LEV_1              = 0,
    FC_MEM_THRESHOLD_LEV_2,
    FC_MEM_THRESHOLD_LEV_3,
    FC_MEM_THRESHOLD_LEV_4,
    FC_MEM_THRESHOLD_LEV_5,
    FC_MEM_THRESHOLD_LEV_6,
    FC_MEM_THRESHOLD_LEV_7,
    FC_MEM_THRESHOLD_LEV_8,
    FC_MEM_THRESHOLD_LEV_BUTT           = 8
};
typedef VOS_UINT32  FC_MEM_THRESHOLD_LEV_ENUM_UINT32;

enum FC_ACPU_DRV_ASSEM_LEV_ENUM
{
    FC_ACPU_DRV_ASSEM_LEV_1             = 0,
    FC_ACPU_DRV_ASSEM_LEV_2,
    FC_ACPU_DRV_ASSEM_LEV_3,
    FC_ACPU_DRV_ASSEM_LEV_4,
    FC_ACPU_DRV_ASSEM_LEV_5             = 4,
    FC_ACPU_DRV_ASSEM_LEV_BUTT          = 5
};
typedef VOS_UINT32  FC_ACPU_DRV_ASSEM_LEV_ENUM_UINT32;

enum RATIO_RESET_TYPE_ENUM
{
    TTF_NODE_RESET_TYPE                 = 0,
    PS_QNODE_RESET_TYPE                 = 1,
    RATIO_RESET_TYPE_BUTT               = 2
};
typedef VOS_UINT32  RATIO_RESET_TYPE_ENUM_UINT32;

/*****************************************************************************
     : TTF_BOOL_ENUM
   :
 ASN.1 :
   : TTF
*****************************************************************************/
enum TTF_BOOL_ENUM
{
    TTF_FALSE                            = 0,
    TTF_TRUE                             = 1,

    TTF_BOOL_BUTT
};
typedef VOS_UINT8   TTF_BOOL_ENUM_UINT8;

/*****************************************************************************
  5 STRUCT
*****************************************************************************/
/*****************************************************************************
*                                                                            *
*                                                            *
*                                                                            *
******************************************************************************/

/*****************************************************************************
     : TTF_MEM_POOL_CFG_NV_STRU
 DESCRIPTION: 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                      ucClusterCnt;                                /* Range:[0,8] */
    VOS_UINT8                      aucReserved[1];
    VOS_UINT16                     ausBlkSize[TTF_MEM_MAX_CLUSTER_NUM];         /* (byte) */
    VOS_UINT16                     ausBlkCnt[TTF_MEM_MAX_CLUSTER_NUM];          /*  */
}TTF_MEM_POOL_CFG_NV_STRU;

/*****************************************************************************
     : TTF_MEM_SOLUTION_CFG_NV_STRU
 DESCRIPTION: 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucPoolCnt;                              /* Range:[0,6] */
    VOS_UINT8                           ucPoolMask;                             /* bit1-  0- */
    TTF_MEM_POOL_CFG_NV_STRU            astTtfMemPoolCfgInfo[TTF_MEM_POOL_NV_NUM];  /*  */
    VOS_UINT8                           aucReserve[2];
}TTF_MEM_SOLUTION_CFG_NV_STRU;

/*****************************************************************************
     : FC_CFG_CPU_STRU
 DESCRIPTION: FC_CFG_CPU,CPU
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulCpuOverLoadVal;                       /*Range:[0,100]*//* CPU */
    VOS_UINT32                          ulCpuUnderLoadVal;                      /*Range:[0,100]*//* CPU */
    VOS_UINT32                          ulSmoothTimerLen;                       /*Range:[2,1000]*//* CPU:CPU */
    VOS_UINT32                          ulStopAttemptTimerLen;                  /* CPUR: 0 */
    VOS_UINT32                          ulUmUlRateThreshold;                    /* CPU */
    VOS_UINT32                          ulUmDlRateThreshold;                    /* CPU */
    VOS_UINT32                          ulRmRateThreshold;                      /* E5 WIFI/USB CPUbps */
} FC_CFG_CPU_STRU;

/*****************************************************************************
     : FC_CFG_MEM_THRESHOLD_STRU
 DESCRIPTION: FC_CFG_MEM_THRESHOLD,MEM
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulSetThreshold;                         /*   */
    VOS_UINT32                          ulStopThreshold;                        /*   */
} FC_CFG_MEM_THRESHOLD_STRU;

/*****************************************************************************
     : FC_CFG_MEM_THRESHOLD_CST_STRU
 DESCRIPTION: FC_CFG_MEM_THRESHOLD_CST,MEM
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulSetThreshold;                         /*Range:[0,4096]*//*   */
    VOS_UINT32                          ulStopThreshold;                        /*Range:[0,4096]*//*   */
} FC_CFG_MEM_THRESHOLD_CST_STRU;


/*****************************************************************************
     : FC_CFG_UM_UL_RATE_STRU
 DESCRIPTION: FC_CFG_UM_UL_RATE,
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucRateCnt;                              /*Range:[0,11]*//* 11FC_PRI_99 */
    VOS_UINT8                           aucRsv[1];
    VOS_UINT16                          ausRate[FC_UL_RATE_MAX_LEV];            /* [0,65535]bps */
} FC_CFG_UM_UL_RATE_STRU;

/*****************************************************************************
     : FC_CFG_NV_STRU
 DESCRIPTION: FC_CFG_NVNV
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulFcEnbaleMask;                         /*  */
    FC_CFG_CPU_STRU                     stFcCfgCpuA;                            /* ACPU */
    VOS_UINT32                          ulFcCfgMemThresholdCnt;                 /* Range:[0,8]*/
    FC_CFG_MEM_THRESHOLD_STRU           stFcCfgMem[FC_MEM_THRESHOLD_LEV_BUTT];  /* A */
    FC_CFG_MEM_THRESHOLD_CST_STRU       stFcCfgCst;                             /* CSD */
    FC_CFG_MEM_THRESHOLD_STRU           stFcCfgGprsMemSize;                     /* G */
    FC_CFG_MEM_THRESHOLD_STRU           stFcCfgGprsMemCnt;                      /* G */
    FC_CFG_CPU_STRU                     stFcCfgCpuC;                            /* CCPU */
    FC_CFG_UM_UL_RATE_STRU              stFcCfgUmUlRateForCpu;                  /* CCPU */
    FC_CFG_UM_UL_RATE_STRU              stFcCfgUmUlRateForTmp;                  /* C */
    FC_CFG_MEM_THRESHOLD_STRU           stFcCfgCdmaMemSize;                     /* X */
    FC_CFG_MEM_THRESHOLD_STRU           stFcCfgCdmaMemCnt;                      /* X */
} FC_CFG_NV_STRU;

/*****************************************************************************
     : CPULOAD_CFG_STRU
 DESCRIPTION: CPULOAD_CFGNV,ACPU
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulMonitorTimerLen;
} CPULOAD_CFG_STRU;

/*****************************************************************************
     : FC_CPU_DRV_ASSEM_PARA_STRU
 DESCRIPTION: CPU LOAD
*****************************************************************************/
typedef struct
{
    VOS_UINT8                          ucHostOutTimeout;    /* PC */
    VOS_UINT8                          ucEthTxMinNum;       /* UE */
    VOS_UINT8                          ucEthTxTimeout;      /* UE */
    VOS_UINT8                          ucEthRxMinNum;       /* UE */
    VOS_UINT8                          ucEthRxTimeout;      /* UE */
    VOS_UINT8                          ucCdsGuDlThres;      /*  */
    VOS_UINT8                          aucRsv[2];
}FC_DRV_ASSEM_PARA_STRU;

/*****************************************************************************
     : FC_CPU_DRV_ASSEM_PARA_STRU
 DESCRIPTION: CPU LOAD
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulCpuLoad;                              /* CPU,Range:[0,100] */
    FC_DRV_ASSEM_PARA_STRU              stDrvAssemPara;
}FC_CPU_DRV_ASSEM_PARA_STRU;

/*****************************************************************************
     : FC_CPU_DRV_ASSEM_PARA_NV_STRU
 DESCRIPTION: FC_CPU_DRV_ASSEMNVCPU LOAD
*****************************************************************************/
typedef struct
{
    VOS_UINT8                              ucEnableMask;                        /* 0x0:0x1: */
    VOS_UINT8                              ucSmoothCntUpLev;                    /*  */
    VOS_UINT8                              ucSmoothCntDownLev;                  /*  */
    VOS_UINT8                              ucRsv;
    FC_CPU_DRV_ASSEM_PARA_STRU             stCpuDrvAssemPara[FC_ACPU_DRV_ASSEM_NV_LEV]; /* CPU */
}FC_CPU_DRV_ASSEM_PARA_NV_STRU;

/*****************************************************************************
     : WTTF_MACDL_WATERMARK_LEVEL_STRU
 DESCRIPTION: WTTF_MACDL_BBMST_WATER_LEVELNV,BBP
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulWaterLevelOne;                        /* 1 */
    VOS_UINT32                          ulWaterLevelTwo;                        /* 2 */
    VOS_UINT32                          ulWaterLevelThree;                      /* 3 */
    VOS_UINT32                          ulWaterLevelFour;                       /* 4, */
} WTTF_MACDL_WATERMARK_LEVEL_STRU;

/*****************************************************************************
     : WTTF_MACDL_BBPMST_TB_HEAD_STRU
 DESCRIPTION: WTTF_MACDL_BBMST_TB_HEADNV,BBP
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulTBHeadNum;                /* TB */
    VOS_UINT32                          ulTBHeadReserved;           /* TBTB3V9R1 30V3R3 15  */
} WTTF_MACDL_BBPMST_TB_HEAD_STRU;

/*****************************************************************************
     : WTTF_SRB_NOT_SEND_THRESHOLD_STRU
 DESCRIPTION: WTTF_SRB_NOT_SEND_THRESHOLD_STRUNV
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulWttfSrbNotSendThreshold;                /* SRBbuffer */
} WTTF_SRB_NOT_SEND_THRESHOLD_STRU;


/*****************************************************************************
     : NF_EXT_NV_STRU
 DESCRIPTION: NETFILTER_HOOK_MASKNV,NV5:
             ulNvValue1~ulNvValue5, 0-FFFFFFFF,
             1
*****************************************************************************/
typedef struct
{
    VOS_UINT32          ulNetfilterPara1;                                       /* 1 */
    VOS_UINT32          ulNetfilterPara2;                                       /* 2 */
    VOS_UINT32          ulNetfilterPara3;                                       /* 3 */
    VOS_UINT32          ulNetfilterPara4;                                       /* 4 */
    VOS_UINT32          ulNetfilterPara5;                                       /* 5 */
}NF_EXT_NV_STRU;

/*****************************************************************************
     : EXT_TEBS_FLAG_NV_STRU
 DESCRIPTION: NV_Ext_Tebs_FlagNV,BOBOBOSG
*****************************************************************************/
typedef struct
{
    VOS_UINT32          ulExtTebsFlag;                                          /* .0x0:,0x1: */
}EXT_TEBS_FLAG_NV_STRU;

/*****************************************************************************
     : TCP_ACK_DELETE_FLG_NV_STRU
 DESCRIPTION: NV_TCP_ACK_Delete_FlgNVSDUTCP ACKIP
*****************************************************************************/
typedef struct
{
    VOS_UINT32          ulTcpAckDeleteFlg;                                      /* .0x0:,0x1: */
}TCP_ACK_DELETE_FLG_NV_STRU;

/*****************************************************************************
     : HUAWEI_IRAN_OPEN_PAGE_I_NV_STRU
 DESCRIPTION: HUAWEI_IRAN_OPEN_PAGE_I_NV,XID
*****************************************************************************/
typedef struct
{
    VOS_UINT16          usHuaweiIranOpenPageI;                                  /* Range:[0,1]
                                                                                   0: UEXID
                                                                                   1: LLC ADMXIDLLC ABMXID */
    VOS_UINT8           aucReserve[2];
}HUAWEI_IRAN_OPEN_PAGE_I_NV_STRU;

/*****************************************************************************
     : GCF_TYPE_CONTENT_NV_STRU
 DESCRIPTION: GCFTypeContentNV
*****************************************************************************/
typedef struct
{
    VOS_UINT32          ulGcfTypeContent;                                       /* .0x0:,0x1: */
}GCF_TYPE_CONTENT_NV_STRU;

/*****************************************************************************
     : W_RF8960_BER_TEST_NV_STRU
 DESCRIPTION: W_RF8960_BER_TestNV,Aglient8960FR BER
*****************************************************************************/
typedef struct
{
    VOS_UINT32          ulRlc8960RFBerTestFlag;                                 /* .0x0:,0x1: */
}W_RF8960_BER_TEST_NV_STRU;

/*****************************************************************************
     : LAPDM_RAND_BIT_NV_STRU
 DESCRIPTION: LAPDM_RAND_BITNV,lapdmBIT
*****************************************************************************/
typedef struct
{
    VOS_UINT16          usLapdmRandBit;                                         /* .0x0:,0x1: */
    VOS_UINT8           aucReserve[2];
}LAPDM_RAND_BIT_NV_STRU;

/*****************************************************************************
     : CBS_W_DRX_SWITCH_NV_STRU
 DESCRIPTION: CBS_W_DRX_SwitchNV,WCBSDRX
*****************************************************************************/
typedef struct
{
    VOS_UINT32          ulCbsWDrxSwitch;                                        /* .0x0:,0x1: */
}CBS_W_DRX_SWITCH_NV_STRU;

/*****************************************************************************
     : CBS_W_WAIT_NEW_CBS_MSG_TIMER_NV_STRU
 DESCRIPTION: CBS_W_WaitNewCBSMsgTimerNVWCBS
*****************************************************************************/
typedef struct
{
    VOS_UINT32          ulCbsWWaitNewCbsMsgTimer;                               /* WCBSms */
}CBS_W_WAIT_NEW_CBS_MSG_TIMER_NV_STRU;

/*****************************************************************************
     : CBS_W_WAIT_SHED_MSG_TIMER_NV_STRU
 DESCRIPTION: CBS_W_WaitShedMsgTimerNV
*****************************************************************************/
typedef struct
{
    VOS_UINT32          ulCbsWWaitShedMsgTimer;
}CBS_W_WAIT_SHED_MSG_TIMER_NV_STRU;

/*****************************************************************************
     : FC_QOS_STRU
 DESCRIPTION: FC_QOS_STRU ,NV
*****************************************************************************/

typedef struct
{
    VOS_UINT32          ulULKBitRate;
    VOS_UINT32          ulDLKBitRate;
}FC_QOS_STRU;

/*****************************************************************************
     : CPU_FLOW_CTRL_CONFIG_NV_STRU
 DESCRIPTION: CPU_FLOW_CTRL_CONFIG_STRUNV
*****************************************************************************/
typedef struct
{
    VOS_UINT32          ulFuncMask;
    VOS_UINT32          ulCpuOverLoadVal;
    VOS_UINT32          ulCpuUnderLoadVal;
    FC_QOS_STRU         astQos1[2];
    FC_QOS_STRU         astQos2[2];
    FC_QOS_STRU         stUmtsEhsUlLimitForDlHighRate;
    FC_QOS_STRU         stUmtsHslULimitForDlHighRate;
    FC_QOS_STRU         stUlLimitForDlLowRate;
    VOS_UINT32          ulRItfDlkBitRate;
    VOS_UINT32          ulRItfRate;
    VOS_UINT32          ulWaitQosTimeLen;
    VOS_UINT32          ulSmoothTimerLen;
    VOS_UINT32          ulRItfSetTimerLen;
    VOS_UINT32          ulCpuFlowCtrlEnable;
    VOS_UINT32          aulRsv[2];
}CPU_FLOW_CTRL_CONFIG_NV_STRU;

/*****************************************************************************
     : R_ITF_FLOW_CTRL_CONFIG_STRU
 DESCRIPTION: R_ITF_FLOW_CTRL_CONFIG_STRUNV,R
*****************************************************************************/
typedef struct
{
    VOS_UINT32              ulRateDismatchUsbEnable;                            /* USBR.0x0:,0x1: */
    VOS_UINT32              ulRateDismatchWifiEnable;                           /* WIFIR.0x0:,0x1: */
} R_ITF_FLOW_CTRL_CONFIG_STRU;

/*****************************************************************************
     : TFC_POWER_FUN_ENABLE_NV_STRU
 DESCRIPTION: TFC_POWER_FUN_ENABLENV,TFC
*****************************************************************************/
typedef struct
{
    VOS_UINT32          ulTfcPowerFunEnable;                                    /* TFC.0x0:,0x1: */
}TFC_POWER_FUN_ENABLE_NV_STRU;

/*****************************************************************************
    : PPP_CONFIG_MRU_TYPE_NV_STRU
DESCRIPTION: PPP_CONFIG_MRU_TypeNV,MTUPPP LCP
*****************************************************************************/
typedef struct
{
    VOS_UINT16                           usPppConfigType;   /* MRU,Range:[296,1500]*/
    VOS_UINT8                            aucReserve[2];
}PPP_CONFIG_MRU_TYPE_NV_STRU;

/*****************************************************************************
     : FC_CDS_DL_CONFIG_STRU
   :
 ASN.1 :
 DESCRIPTION: CDS
*****************************************************************************/
typedef struct
{
    VOS_UINT32          ulDiscardThres;         /* CDS */
    VOS_UINT32          ulDiscardRate;          /*  */
} FC_CDS_DL_CONFIG_STRU;

/*****************************************************************************
     : QOS_FC_CONFIG_STRU
   :
 ASN.1 :
 DESCRIPTION: QOS
*****************************************************************************/
typedef struct
{
    VOS_UINT32          ulPktCntLimit;              /* QoS */
    VOS_UINT32          ulTimerLen;                 /* QoS */
    VOS_UINT32          ulRandomDiscardRate;        /*  */
    VOS_UINT32          ulDiscardRate;              /*  */
    VOS_UINT32          ulWarningThres;             /*  */
    VOS_UINT32          ulDiscardThres;             /*  */
    VOS_UINT32          ulRandomDiscardThres;       /*  */
    VOS_UINT32          ulRestoreThres;             /*  */
} QOS_FC_CONFIG_STRU;

/*****************************************************************************
     : FLOWCTRL_CDS_CONFIG_STRU
   :
 ASN.1 :
 DESCRIPTION: CCDS
*****************************************************************************/
typedef struct
{
    VOS_UINT32              ulFcEnableMask;         /*  */
                                                    /* bit0 QoS */
                                                    /* bit1  */
                                                    /* bit2 CDS */
                                                    /* bit3  */
    QOS_FC_CONFIG_STRU      stQosFcConfig;          /* QOS */
    FC_CDS_DL_CONFIG_STRU   stFcCdsDlConfig;        /* CDS */
}FLOWCTRL_CDS_CONFIG_STRU;

/*****************************************************************************
    : BMC_CBS_MSG_READ_NV_STRU
DESCRIPTION: BMC_CBS_MSG_READ_NV_STRUNV.Reading AdvisedReading optional CBS
*****************************************************************************/
typedef struct
{
    VOS_UINT8               ucDisableReadAdvised;       /*Range:[0,1]*//*advisedDRX PS_FALSEPS_TRUE*/
    VOS_UINT8               ucDisableReadOptional;      /*Range:[0,1]*//*optionalDRXPS_FALSEPS_TRUE*/
    VOS_UINT8               ucDisableRepetitionMsg;     /*Range:[0,1]*//*Repetition msgDRXPS_FALSEPS_TRUE*/
    VOS_UINT8               ucDisableOldMsg;            /*Range:[0,1]*//*old msgDRXPS_FALSEPS_TRUE*/
}BMC_CBS_MSG_READ_NV_STRU;


/*****************************************************************************
    : NV_MODEM_RF_SHARE_CFG_STRU
DESCRIPTION: NV_MODEM_RF_SHARE_CFGNV
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usSupportFlag;      /* Range:[0,2]DSDS,DSDS1.0,DSDS2.0 */
    VOS_UINT16                          usGSMRFID;          /* GSMRFID */
    VOS_UINT16                          usWCDMARFID;        /* WCDMARFID */
    VOS_UINT16                          usTDSRFID;          /* TD-SCDMARFID */
    VOS_UINT16                          usLTERFID;          /* LTERFID */
    VOS_UINT16                          usCDMARFID;         /* CMDARFID */
    VOS_UINT16                          usEVDORFID;         /* CDMA EVDORFID */
    VOS_UINT16                          usReserved;
} NV_MODEM_RF_SHARE_CFG_STRU;


/*****************************************************************************
    : NV_MODEM_RF_SHARE_CFG_EX_STRU
DESCRIPTION: NV_MODEM_RF_SHARE_CFG_EX_STRUNV,DSDSRFID
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulProfileTypeId;     /* en_NV_Item_TRI_MODE_FEM_PROFILE_IDulProfileId,
                                                                */
    NV_MODEM_RF_SHARE_CFG_STRU          astNvModemRfShareCfg[8];                /* ModemRF */
}NV_MODEM_RF_SHARE_CFG_EX_STRU;

/*****************************************************************************
    : PLATFORM_RAT_TYPE_ENUM
  1.       : 2015427
           : g00260269
       : 
DESCRIPTION: 
*******************************************************************************/
enum NV_PLATFORM_RAT_TYPE_ENUM
{
    NV_PLATFORM_RAT_GSM,                                                       /*GSM */
    NV_PLATFORM_RAT_WCDMA,                                                     /* WCDMA */
    NV_PLATFORM_RAT_LTE,                                                       /* LTE */
    NV_PLATFORM_RAT_TDS,                                                       /* TDS */
    NV_PLATFORM_RAT_1X,                                                        /* CDMA-1X */
    NV_PLATFORM_RAT_EVDO,                                                      /* CDMA-EV_DO */

    NV_PLATFORM_RAT_BUTT
};
typedef VOS_UINT16 NV_PLATFORM_RAT_TYPE_ENUM_UINT16;

/*****************************************************************************
    : NV_PLATAFORM_RAT_CAPABILITY_STRU
  1.       : 2015427
           : g00260269
       : 
DESCRIPTION: 
*******************************************************************************/
typedef struct
{
    VOS_UINT16                           usRatNum;                          /*  */
    NV_PLATFORM_RAT_TYPE_ENUM_UINT16     aenRatList[NV_PLATFORM_MAX_RAT_NUM];  /*  */
}NV_PLATAFORM_RAT_CAPABILITY_STRU;

/*****************************************************************************
    : BASTET_SUPPORT_FLG_STRU
  1.       : 20141122
           : z00128442
       : bastetnv
DESCRIPTION: BASTET_SUPPORT_FLG_STRU
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucActiveFlg;        /*  */
    VOS_UINT8                           ucHookFlg;          /* Bastet */
    VOS_UINT8                           aucSubFun[2];
}BASTET_SUPPORT_FLG_STRU;

/*****************************************************************************
    : NV_CTTF_BOOL_ENUM_UINT8
DESCRIPTION:

  1.       : 201599
           : c00309867
       : 
*******************************************************************************/
enum NV_CTTF_BOOL_ENUM
{
    NV_CTTF_BOOL_FALSE,                /*  */
    NV_CTTF_BOOL_TRUE,               /*  */
    NV_CTTF_BOOL_BUTT
};
typedef VOS_UINT8 NV_CTTF_BOOL_ENUM_UINT8;

/*****************************************************************************
    : NV_SUPPORT_PROBE_INIT_ADJ_CFG_STRU
  1.       : 201590
           : c00309867
       : nv
DESCRIPTION: NV_SUPPORT_PROBE_INIT_ADJ_CFG_STRU,Probe
*****************************************************************************/
typedef struct
{
    NV_CTTF_BOOL_ENUM_UINT8             enSupportFlg;                   /* NVcProbeInitialAdjustNV_CTTF_BOOL_FALSE:NV_CTTF_BOOL_TRUE */
    VOS_INT8                            cProbeInitialAdjust;            /* cProbeInitialAdjust */
    VOS_UINT8                           aucSubFun[2];
}NV_CTTF_PROBE_INIT_POWER_CTRL_STRU;


/*****************************************************************************
    : TTF_PPPC_NVIM_CONFIG_OPTIONS_STRU
  1.       : 20150829
           : w00316385
       : nv
DESCRIPTION: TTF_PPPC_NVIM_CONFIG_OPTIONS_STRU,PPP
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usMru;                  /* PPP */
    VOS_UINT8                           ucReserved;
    VOS_UINT8                           ucCaveEnable;           /* PPPCAVE01 */
    VOS_UINT32                          ulPppInactTimerLen;     /* MAX PPP Inactive Timers */
}TTF_PPPC_NVIM_CONFIG_OPTIONS_STRU;

/*****************************************************************************
    : NV_HRPD_RF_ALLOC_SWITCH_MASK_STRU
  1.       : 2016314
           : t00359887
       : nv
DESCRIPTION: NV_HRPD_RF_ALLOC_SWITCH_MASK_STRU
            ulHrpdRfAllocSwitchMask bit10
            bit 0:signaling alloc rf
            bit 1:ppp in access auth alloc rf
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulHrpdRfAllocSwitchMask;    /* bit10, bit 0:signaling alloc rf, bit 1:ppp in access auth alloc rf */
}NV_HRPD_RF_ALLOC_SWITCH_MASK_STRU;


/*****************************************************************************
    : NV_TTF_NODE_RESET_CTRL_STRU
  1.       : 20160126
           : m00314743
       : nv
DESCRIPTION: NV_TTF_NODE_RESET_CTRL_STRU
*****************************************************************************/
typedef struct
{
    NV_CTTF_BOOL_ENUM_UINT8             enResetEnable;                  /* TTF_Node */
    VOS_UINT8                           ucFailPercent;             /*  */
    VOS_UINT16                          usTotalStat;               /*  */
}NV_RATIO_RESET_CTRL_STRU;

/*****************************************************************************
    : NV_NODE_RESET_CTRL_STRU
  1.       : 20160126
           : m00314743
       : nv
DESCRIPTION: NV_NODE_RESET_CTRL_STRU
*****************************************************************************/
typedef struct
{
    NV_RATIO_RESET_CTRL_STRU                  astNvResetCtrl[RATIO_RESET_TYPE_BUTT];
}NV_NODE_RESET_CTRL_STRU;

/*****************************************************************************
     : TTF_CICOM_IP_ENT_NVIM_STRU
 DESCRIPTION: TTF_CICOM_IP_ENT_NVIM_STRUNV,CIOCM
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCicomIPNumber;         /* CIOCM */
    VOS_UINT8                           aucRsv[3];

    VOS_UINT8                           aucModemIdToCicomIndex[NV_PLATFORM_MAX_MODEM_NUM];   /* Modem id,CIOCM Index0~ucCicomIPNumber-1 */
}TTF_CICOM_IP_ENT_NVIM_STRU;

/*****************************************************************************
     : NV_TTF_PPP_CONFIG_STRU
 DESCRIPTION: en_NV_Item_PPP_CONFIGNV
*****************************************************************************/
typedef struct
{
    TTF_BOOL_ENUM_UINT8                 enChapEnable;           /* Chap */
    TTF_BOOL_ENUM_UINT8                 enPapEnable;            /* Pap */
    VOS_UINT16                          usLcpEchoMaxLostCnt;    /* LcpEchoRequest */

    VOS_UINT16                          usQueneMaxCnt;          /*  */
    VOS_UINT8                           aucRsv[2];
}NV_TTF_PPP_CONFIG_STRU;

/*****************************************************************************
     : NV_TTF_SEQ_OUT_OF_ORDER_COMPATIBLE_STRU
 DESCRIPTION: en_NV_Item_TTF_SEQ_OUT_OF_ORDER_COMPATIBLENV
*****************************************************************************/
typedef struct
{
    TTF_BOOL_ENUM_UINT8                 enWcdmaEnable;                  /*Range:[0,1]*//* WCDMA */
    TTF_BOOL_ENUM_UINT8                 enLAPDmEnable;                  /*Range:[0,1]*//* LAPDm */
    VOS_UINT8                           ucWcdmaRlcAckOutOfSeqScope;     /*Range:[0,24]*//* WRLCACKLSN */
    VOS_UINT8                           ucWcdmaRlcErrStatusPduCnt;      /*Range:[0,4]*//* WRLCPDU */
}NV_TTF_SEQ_OUT_OF_ORDER_COMPATIBLE_STRU;

/*****************************************************************************
     : NV_WTTF_CSPS_RLC_PS_NOT_RPT_DATALINK_LOSS_STRU
 DESCRIPTION: en_NV_Item_WTTF_CSPS_RLC_PS_NOT_RPT_DATALINK_LOSSNVCS+PSPS RB
*****************************************************************************/
typedef struct
{
    TTF_BOOL_ENUM_UINT8                 enEnable;                       /*Range:[0,1]*//* CS+PSPS RB */
    VOS_UINT8                           ucRsv1;
    VOS_UINT8                           ucRsv2;
    VOS_UINT8                           ucRsv3;
}NV_WTTF_CSPS_RLC_PS_NOT_RPT_DATALINK_LOSS_STRU;

/*****************************************************************************
    : NV_NODE_RESET_CTRL_STRU
  1.       : 20160220
           : m00314743
       : nv
DESCRIPTION: NV_NODE_RESET_CTRL_STRUTPE
*****************************************************************************/
typedef struct
{
    NV_CTTF_BOOL_ENUM_UINT8             enTpeEnable;             /* TPE */
    VOS_UINT8                           ucCorrectPercent;        /* : */
    VOS_UINT8                           aucReserved[2];
}NV_TTF_TPE_CTRL_STRU;

/*****************************************************************************
     : NV_TTF_CORE_BIND_CONFIG_STRU
 DESCRIPTION: NV_TTF_CORE_BIND_CONFIG_STRUNV
             core0 0bit1core1 1bit1
             core2 2bit1core3 3bit1
             mask
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucLlcFidCoreMask;          /* Llc */
    VOS_UINT8                           ucGrmFidCoreMask;          /* Grm */
    VOS_UINT8                           ucMacRlcUlFidCoreMask;     /* MacRlcUl */
    VOS_UINT8                           ucMacRlcDlFidCoreMask;     /* MacRlcDl */
}NV_TTF_CORE_BIND_CONFIG_STRU;

/*****************************************************************************
     : NV_CTTF_FID_CORE_BIND_CONFIG_STRU
 DESCRIPTION: NV_CTTF_FID_CORE_BIND_CONFIG_STRUNV, CoreMaskbit
             bit0Core0bit1Core1
             bit2Core2bit3Core3
             CoreMask0
             
             :
             uc1XFwdFidCoreMask1MSPS_FID_CTTF_1X_FWD0
             uc1XFwdFidCoreMask2MSPS_FID_CTTF_1X_FWD1
             uc1XFwdFidCoreMask4MSPS_FID_CTTF_1X_FWD2
             uc1XFwdFidCoreMask8MSPS_FID_CTTF_1X_FWD3
             uc1XFwdFidCoreMask3MSPS_FID_CTTF_1X_FWD01
             uc1XFwdFidCoreMask11MSPS_FID_CTTF_1X_FWD013
             uc1XFwdFidCoreMask15MSPS_FID_CTTF_1X_FWD0123
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           uc1XFwdFidCoreMask;       /* MSPS_FID_CTTF_1X_FWD */
    VOS_UINT8                           uc1XRevFidCoreMask;       /* MSPS_FID_CTTF_1X_REV */
    VOS_UINT8                           ucHrpdFwdFidCoreMask;     /* CTTF_FID_HRPD_FWD */
    VOS_UINT8                           ucHrpdRevFidCoreMask;     /* CTTF_FID_HRPD_REV */
}NV_CTTF_FID_CORE_BIND_CONFIG_STRU;


/*****************************************************************************
     : NV_ACTIVE_MODEM_MODE_ENUM
   : DSDSModem
 1.       : 20170216
          : l00383652
      : DSDS/
*****************************************************************************/
enum NV_ACTIVE_MODEM_MODE_ENUM
{
    NV_ACTIVE_SINGLE_MODEM              = 0x00,
    NV_ACTIVE_MULTI_MODEM               = 0x01,
    NV_ACTIVE_MODEM_MODE_BUTT
};
typedef VOS_UINT8 NV_ACTIVE_MODEM_MODE_ENUM_UINT8;

/*****************************************************************************
     : NV_DSDS_ACTIVE_MODEM_MODE_STRU
   : DSDSModem
 1.       : 20170216
          : l00383652
      : DSDS/
*****************************************************************************/
typedef struct
{
    NV_ACTIVE_MODEM_MODE_ENUM_UINT8     enActiveModem;
    VOS_UINT8                           aucReserve[3];
}NV_DSDS_ACTIVE_MODEM_MODE_STRU;

/*****************************************************************************
    : NV_TTF_RLC_FLOW_CONTROL_STRU
DESCRIPTION: en_NV_Item_RLC_Flow_Control,UDP WRLCUDP 
 1.       : 20180331
          : c00368566
*****************************************************************************/
typedef struct
{
    TTF_BOOL_ENUM_UINT8         enEnable;               /* ,01 */
    VOS_UINT8                   ucFreq;                 /* :10ms */
    VOS_UINT16                  usFlowCtrlThreshold;    /* :10ms */ 
}NV_TTF_RLC_FLOW_CONTROL_STRU;

/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/


/*****************************************************************************
  9 OTHERS
*****************************************************************************/
















#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of TtfNvInterface.h */
