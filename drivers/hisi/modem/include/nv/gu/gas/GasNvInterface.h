/******************************************************************************

  Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : GasNvInterface.h
  Description     : GasNvInterface.h header file
  History         :
  1.       : 2017117
           : s00184266
       : dts2017011204014, DESCRIPTION

******************************************************************************/

#ifndef __GASNVINTERFACE_H__
#define __GASNVINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(2)
#else
#pragma pack(push, 2)
#endif

#include "vos.h"

/*****************************************************************************
  2 Macro
*****************************************************************************/
#define NVIM_ULTRA_CLASSMARK_LEN                            (24)
#define NVIM_BAND_PWR_LEN                                   (8)
#define NVIM_CLASSMARK1_LEN                                 (2)
#define NVIM_CLASSMARK2_LEN                                 (4)
#define NVIM_CLASSMARK3_LEN                                 (16)
#define NVIM_CLASSMARK3_R8_LEN                              (36)
#define NVIM_GCF_ITEM_LEN                                   (80)
#define NVIM_GSM_BA_MAX_SIZE                                (33)
#define NVIM_EGPRS_RA_CAPABILITY_DATA_LEN                   (53)
#define NVIM_PREFER_GSM_PLMN_LIST_LEN                       (976)
#define NVIM_GSM_DEC_FAIL_ARFCN_LIST_LEN                    (120)
#define NVIM_EUTRA_MAX_SUPPORT_BANDS_NUM                    (64)
#define NVIM_TDS_MAX_SUPPORT_BANDS_NUM                      (8)
#define NVIM_EUTRA_CAPA_COMM_INFO_SIZE                      (260)
#define NVIM_CBS_MID_LIST_LEN                               (2004)
#define NVIM_CBS_MID_RANGE_LIST_LEN                         (2004)
/* Added by yangsicong for L2G REDIR C1 CUSTUME, 2015-1-26, begin */
#define NVIM_GAS_C1_CALC_OPT_PLMN_WHITE_LIST_CNT_MAX        (20)
/* Added by yangsicong for L2G REDIR C1 CUSTUME, 2015-1-26, end */

#define NVIM_GAS_GSM_BAND_CUSTOMIZE_LIST_MAX_CNT            (80)

#define NVIM_GSM_OPERATE_CUSTOMIZE_FREQ_PLMN_MAX_CNT        (10)
#define NVIM_GSM_OPERATE_CUSTOMIZE_FREQ_RANGE_MAX_CNT       (8)
#define NVIM_GSM_OPERATE_CUSTOMIZE_DESCRETE_FREQ_MAX_CNT    (16)

#if defined( __PS_WIN32_RECUR__ ) || defined (DMT)
#define MAX_CHR_ALARM_ID_NUM (20)
#endif

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/
enum NVIM_TDS_FREQ_BAND_LIST_ENUM
{
    ID_NVIM_TDS_FREQ_BAND_A         = 0x01,         /* : 9504~9596  10054~10121 */
    ID_NVIM_TDS_FREQ_BAND_B         = 0x02,         /* : 9254~9546  9654~9946 */
    ID_NVIM_TDS_FREQ_BAND_C         = 0x04,         /* : 9554~9646 */
    ID_NVIM_TDS_FREQ_BAND_D         = 0x08,         /* : 12854~13096 */
    ID_NVIM_TDS_FREQ_BAND_E         = 0x10,         /* : 11504~11996 */
    ID_NVIM_TDS_FREQ_BAND_F         = 0x20,         /* : 9404~9596 */
    ID_NVIM_TDS_FREQ_BAND_BUTT
};
typedef VOS_UINT8  NVIM_TDS_FREQ_BAND_LIST_ENUM_UINT8;

/*****************************************************************************
     : NVIM_BAND_IND
   : NVBAND
   :
  1.     : 2015914
         : s00184266
     : 

*****************************************************************************/
enum NVIM_BAND_IND_ENUM
{
    NVIM_BAND_IND_2                 = 0x2,          /* BAND2 */
    NVIM_BAND_IND_3                 = 0x3,          /* BAND3 */
    NVIM_BAND_IND_5                 = 0x5,          /* BAND5 */
    NVIM_BAND_IND_8                 = 0x8,          /* BAND8 */
    NVIM_BAND_IND_BUTT
};
typedef VOS_UINT8 NVIM_BAND_IND_ENUM_UINT8;


/*****************************************************************************
  5 STRUCT
*****************************************************************************/
/*****************************************************************************
*                                                                            *
*                                                            *
*                                                                            *
******************************************************************************/

/*****************************************************************************
     : NVIM_ULTRA_CLASSMARK_STRU
   : en_NV_Item_Ultra_Classmark 
 DESCRIPTION: 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucUltraClassmark[NVIM_ULTRA_CLASSMARK_LEN];
}NVIM_ULTRA_CLASSMARK_STRU;

/*****************************************************************************
     : NVIM_GAS_MULTIRATE_FLAG_STRU
   : en_NV_Item_Gas_MultiRateFlag 
 DESCRIPTION: 
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usMultiRateFlag;
    VOS_UINT8                           aucReserve[2];
}NVIM_GAS_MULTIRATE_FLAG_STRU;

/*****************************************************************************
     : NVIM_BAND_PWR_STRU
   : en_NV_Item_Band_Pwr 
 DESCRIPTION: MS
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucBandPwr[NVIM_BAND_PWR_LEN];          /* MS */
}NVIM_BAND_PWR_STRU;

/*****************************************************************************
     : NVIM_VGCS_FLAG_STRU
   : en_NV_Item_Vgcs_Flag 
 DESCRIPTION: MS
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usVgcsFlag;                             /* 0x0: 
                                                                                   0x1:  */
    VOS_UINT8                           aucReserve[2];
}NVIM_VGCS_FLAG_STRU;

/*****************************************************************************
     : NVIM_EGPRS_MULTI_SLOT_CLASS_STRU
   : en_NV_Item_Egprs_Multi_Slot_Class 
 DESCRIPTION:  MSEGPRS
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usEgprsMultiSlotClass;                  /* Range: [0,12]
                                                                                   0x0:MS0xC
                                                                                   0x1~0xC:MS */
    VOS_UINT8                           aucReserve[2];
}NVIM_EGPRS_MULTI_SLOT_CLASS_STRU;

/*****************************************************************************
     : NVIM_GSM_CLASSMARK1_STRU
   : en_NV_Item_Gsm_Classmark1 
 DESCRIPTION:  GSM Classmark1
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucGsmClassmark1[NVIM_CLASSMARK1_LEN];  /* CLASSMARK1  */
    VOS_UINT8                           aucReserve[2];
}NVIM_GSM_CLASSMARK1_STRU;

/*****************************************************************************
     : NVIM_GSM_CLASSMARK2_STRU
   : en_NV_Item_Gsm_Classmark2 
 DESCRIPTION:  GSM Classmark2
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucGsmClassmark2[NVIM_CLASSMARK2_LEN];  /* CLASSMARK2  */
}NVIM_GSM_CLASSMARK2_STRU;

/*****************************************************************************
     : NVIM_GSM_CLASSMARK3_STRU
   : en_NV_Item_Gsm_Classmark3 
 DESCRIPTION:  GSM Classmark3
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucGsmClassmark3[NVIM_CLASSMARK3_LEN];  /* CLASSMARK3  */
}NVIM_GSM_CLASSMARK3_STRU;

/*****************************************************************************
     : NVIM_GSM_IND_FREQ_STRU
   : en_NV_Item_Gsm_Ind_Freq 
 DESCRIPTION:  GSM
               
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usGsmIndFreq;                           /* 0x0000~0xFFFE
                                                                                   0xFFFF */
    VOS_UINT8                           aucReserve[2];
}NVIM_GSM_IND_FREQ_STRU;

/*****************************************************************************
     : NVIM_GCF_ITEM_STRU
   : en_NV_Item_GCF_Item 
 DESCRIPTION:  GCF
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucGcfItem[NVIM_GCF_ITEM_LEN];
}NVIM_GCF_ITEM_STRU;

/*****************************************************************************
     : NVIM_G2W_RSSI_RSCP_OFFSET_STRU
   : en_NV_Item_G2W_RSSI_RSCP_OFFSET 
 DESCRIPTION:  
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usG2WRssiRscpOffset;
    VOS_UINT8                           aucReserve[2];
}NVIM_G2W_RSSI_RSCP_OFFSET_STRU;

/*****************************************************************************
     : NVIM_GSM_BA_COUNT_STRU
   : en_NV_Item_GSM_Ba_Count 
 DESCRIPTION:  BAMSNV
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usGsmBaCount;                           /* 0x0000:BA0
                                                                                   0x0001~0x0021:GSM BA LISTBA */
    VOS_UINT8                           aucReserve[2];
}NVIM_GSM_BA_COUNT_STRU;

/*****************************************************************************
     : NVIM_GSM_BA_LIST_STRU
   : en_NV_Item_GSM_Ba_List 
 DESCRIPTION:  PLMN
               PLMNNV
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulMcc;                                  /*  */
    VOS_UINT32                          ulMnc;                                  /*  */
    VOS_UINT16                          usArfcn[NVIM_GSM_BA_MAX_SIZE];          /* ausArfcn[0]
                                                                                   ausArfcn[1]~ausArfcn[33] */
    VOS_UINT8                           aucReserve[2];
}NVIM_GSM_BA_LIST_STRU;

/*****************************************************************************
     : NVIM_EGPRS_FLAG_STRU
   : en_NV_Item_Egprs_Flag 
 DESCRIPTION:  MSEGPRSNVModem
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usEgprsFlag;                            /* 0x0000:EGPRS
                                                                                   0x0001:EGPRS */
    VOS_UINT8                           aucReserve[2];
}NVIM_EGPRS_FLAG_STRU;

/*****************************************************************************
     : NVIM_EGPRS_RA_CAPABILITY_STRU
   : en_NV_Item_EgprsRaCapability 
 DESCRIPTION:  EGPRSRA
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucLength;                               /*  */
    VOS_UINT8                           aucEgprsRaCapabilityData[NVIM_EGPRS_RA_CAPABILITY_DATA_LEN];    /*  */
    VOS_UINT8                           aucReserve[2];
}NVIM_EGPRS_RA_CAPABILITY_STRU;

/*****************************************************************************
     : NVIM_PREFER_GSM_PLMN_COUNT_STRU
   : en_NV_Item_Prefer_GSM_PLMN_Count 
 DESCRIPTION:  GSMPLMN
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usPreferGsmPlmnCount;                   /* PLMN */
    VOS_UINT8                           aucReserve[2];
}NVIM_PREFER_GSM_PLMN_COUNT_STRU;

/*****************************************************************************
     : NVIM_PREFER_GSM_PLMN_LIST_STRU
   : en_NV_Item_Prefer_GSM_PLMN_List 
 DESCRIPTION:  GSMMCCMNCPLMN
               15PLMNPLMN60
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          ausPreferGsmPlmnListData[NVIM_PREFER_GSM_PLMN_LIST_LEN];    /* GSM */
}NVIM_PREFER_GSM_PLMN_LIST_STRU;

/*****************************************************************************
     : NVIM_GSM_DEC_FAIL_ARFCN_COUNT_STRU
   : en_NV_Item_GSM_DEC_FAIL_ARFCN_Count 
 DESCRIPTION:  GSM
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usGsmDecFailArfcnCount;                 /*  */
    VOS_UINT8                           aucReserve[2];
}NVIM_GSM_DEC_FAIL_ARFCN_COUNT_STRU;

/*****************************************************************************
     : NVIM_GSM_DEC_FAIL_ARFCN_LIST_STRU
   : en_NV_Item_GSM_DEC_FAIL_ARFCN_List 
 DESCRIPTION:  GSM
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usGsmDecFailArfcnList[NVIM_GSM_DEC_FAIL_ARFCN_LIST_LEN];    /*  */
}NVIM_GSM_DEC_FAIL_ARFCN_LIST_STRU;

/*****************************************************************************
     : NVIM_PREFER_GSM_PLMN_SWITCH_STRU
   : en_NV_Item_Prefer_GSM_PLMN_Switch 
 DESCRIPTION:  GSM_PLMN_CountGSM_PLMN_ListNV
               NV
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usPreferGsmPlmnSwitch;                  /* 0x0000:0x0001 */
    VOS_UINT8                           aucReserve[2];
}NVIM_PREFER_GSM_PLMN_SWITCH_STRU;

/*****************************************************************************
     : NVIM_PREFER_GSM_PLMN_CUSTOMIZE_CFG_STRU
   : 
 DESCRIPTION: 
   :
  1.     : 201599
         : s00184266
     : 

*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucAgingEnable;                          /* NV */
    VOS_UINT8                           ucRsrv1;                                /*  */
    VOS_UINT8                           ucRsrv2;                                /*  */
    VOS_UINT8                           ucRsrv3;                                /*  */
    VOS_INT16                           sDecFailedRssiThreshold;                /* RSSI */
    VOS_UINT16                          usRsrv1;                                /*  */
    VOS_UINT16                          usRsrv2;                                /*  */
    VOS_UINT16                          usRsrv3;                                /*  */
    VOS_UINT32                          ulRsrv1;                                /*  */
    VOS_UINT32                          ulRsrv2;                                /*  */
}NVIM_PREFER_GSM_PLMN_CUSTOMIZE_CFG_STRU;

/*****************************************************************************
     : NVIM_GERAN_FEATURE_PACKAGE1_STRU
   : en_NV_Item_Geran_Feature_Package1 
 DESCRIPTION: MSGeran Feature Package1
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usGeranFeaturePackage1;                 /* Range: [0,1],0x0:,0x1: */
    VOS_UINT8                           aucReserve[2];
}NVIM_GERAN_FEATURE_PACKAGE1_STRU;

/*****************************************************************************
     : NVIM_GSM_A5_STRU
   : en_NV_Item_Gsm_A5 
 DESCRIPTION: A5A5/1A5/2A5/3A5/4
              Bitbit0bit1...bit7bit:
              bit0=0:A5/1bit0=1:A5/1
              bit1=0:A5/2bit1=1:A5/2
              bit2=0:A5/3bit2=1:A5/3
              bit3=0:A5/4bit3=1:A5/4
              bit
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usGsmA5;                                /* Range: [0,15]
                                                                                   0x0:A5;
                                                                                   0x1:A5/1;
                                                                                   0x2:A5/2;
                                                                                   0x3:A5/1A5/2 
                                                                                   0x4:A5/3;
                                                                                   0x5:A5/3A5/1;
                                                                                   0x6:A5/3A5/2;
                                                                                   0x7:A5/3A5/2A5/3 */
    VOS_UINT8                           aucReserve[2];
}NVIM_GSM_A5_STRU;

/*****************************************************************************
     : NVIM_LOW_COST_EDGE_FLAG_STRU
   : en_NV_Item_LowCostEdge_Flag 
 DESCRIPTION: MSlowCostEdgeMS8PSK
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usLowCostEdgeFlag;                      /* Range: [0,1],0x0:,0x1: */
    VOS_UINT8                           aucReserve[2];
}NVIM_LOW_COST_EDGE_FLAG_STRU;

/*****************************************************************************
     : NVIM_GPRS_ACTIVE_TIMER_LENGTH_STRU
   : en_NV_Item_GPRS_ActiveTimerLength 
 DESCRIPTION: GPRS Active Timer
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulGprsActiveTimerLength;                /* 0x0000:100ms;
                                                                                   0x0001:100ms;
                                                                                   0x0002:200ms; */
}NVIM_GPRS_ACTIVE_TIMER_LENGTH_STRU;

/*****************************************************************************
     : NVIM_GPRS_MULTI_SLOT_CLASS_STRU
   : en_Nv_Item_Gprs_Multi_Slot_Class 
 DESCRIPTION: MSGPRS
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usGprsMultiSlotClass;                   /* Range: [0,12]
                                                                                   0x0:MS0xC
                                                                                   0x1~0xC:MS */
    VOS_UINT8                           aucReserve[2];
}NVIM_GPRS_MULTI_SLOT_CLASS_STRU;

/*****************************************************************************
     : NVIM_GSM_PLMN_SEARCH_ARFCN_MAX_NUM_STRU
   : en_NV_Item_GSM_PLMN_SEARCH_ARFCN_MAX_NUM 
 DESCRIPTION: GSM0x003C
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usGsmPlmnSearchArfcmMaxNum;             /* Range: [0x1,0x8C], */
    VOS_UINT8                           aucReserve[2];
}NVIM_GSM_PLMN_SEARCH_ARFCN_MAX_NUM_STRU;

/*****************************************************************************
     : NVIM_GCBS_CONF_STRU
   : en_Nv_Item_GCBS_Conf 
 DESCRIPTION: GCBSECBCHGCBS DrxGCBS
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                      usECBCHSwitch;              /* ECBCH,0x0:,0x1: */
    VOS_UINT16                                      usDrxSwitch;                /* GCBS DRX,0x0:,0x1: */
    VOS_UINT32                                      ulGCBSActiveTimerLength;    /* GCBSms */
}NVIM_GCBS_CONF_STRU;

/*****************************************************************************
     : NVIM_REPEATED_ACCH_CAPABILITY_STRU
   : en_NV_Item_Repeated_Acch_Capability 
 DESCRIPTION: Repeated FACCH/SACCHR6
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                      usRepeatedAcchCapability;   /* 0x0:BSSrepeated FACCH;
                                                                                   0x1:BSSrepeated FACCH */
    VOS_UINT8                                       aucReserve[2];
}NVIM_REPEATED_ACCH_CAPABILITY_STRU;


/*****************************************************************************
     : NVIM_ES_IND_STRU
   : en_NV_Item_ES_IND 
 DESCRIPTION: Controlled Early Classmark Sending
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                      usEsInd;                    /* Range: [0,1],0x0:,0x1: */
    VOS_UINT8                                       aucReserve[2];
}NVIM_ES_IND_STRU;

/*****************************************************************************
     : NVIM_GPRS_EXTENDED_DYNAMIC_ALLOCATION_CAPABILITY_STRU
   : en_NV_Item_GPRS_Extended_Dynamic_Allocation_Capability 
 DESCRIPTION: GPRS
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                      usGprsExtDynAllocCap;       /* Range: [0,1],0x0:,0x1: */
    VOS_UINT8                                       aucReserve[2];
}NVIM_GPRS_EXTENDED_DYNAMIC_ALLOCATION_CAPABILITY_STRU;

/*****************************************************************************
     : NVIM_EGPRS_EXTENDED_DYNAMIC_ALLOCATION_CAPABILITY_STRU
   : en_NV_Item_EGPRS_Extended_Dynamic_Allocation_Capability 
 DESCRIPTION: EGPRS
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                      usEGprsExtDynAllocCap;      /* Range: [0,1],0x0:,0x1: */
    VOS_UINT8                                       aucReserve[2];
}NVIM_EGPRS_EXTENDED_DYNAMIC_ALLOCATION_CAPABILITY_STRU;

/*****************************************************************************
     : NVIM_REVISION_LEVEL_INDICATOR_STRU
   : en_NV_Item_Revision_Level_Indicator 
 DESCRIPTION: ME
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                      usRevLvlInd;                /* Range: [0,1],0x0:R99,0x1:RR */
    VOS_UINT8                                       aucReserve[2];
}NVIM_REVISION_LEVEL_INDICATOR_STRU;

/*****************************************************************************
     : NVIM_GAS_REVISION_LEVEL_CUSTOMIZE_STRU
   : en_NV_Item_GAS_Revision_Level_Customization 
 DESCRIPTION: classmark2revision level IE
*****************************************************************************/
typedef struct
{
    VOS_UINT8                            ucInterRatCustomizeFlag;       /* classmark2Revison level IE
                                                                           0:
                                                                           1:classmark2Revison levelR99
                                                                        */
    
    VOS_UINT8                            ucRsv1;                        /* 1 */
    
    VOS_UINT8                            ucRsv2;                        /* 2 */
    
    VOS_UINT8                            ucRsv3;                        /* 3 */

}NVIM_GAS_REVISION_LEVEL_CUSTOMIZE_STRU;

/*****************************************************************************
     : NVIM_DOWNLINK_ADVANCED_RECEIVER_PERFORMANCE_STRU
   : en_NV_Item_Downlink_Advanced_Receiver_Performance 
 DESCRIPTION: 
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                      usDlAdvRcvPer;              /* Range: [0,1],0x0:,0x1: */
    VOS_UINT8                                       aucReserve[2];
}NVIM_DOWNLINK_ADVANCED_RECEIVER_PERFORMANCE_STRU;

/*****************************************************************************
     : NVIM_EXT_RLC_MAC_CTRL_MSG_SEGMENT_CAPABILITY_STRU
   : en_NV_Item_Ext_RLC_MAC_Ctrl_Msg_Segment_Capability 
 DESCRIPTION: MSRLC/MAC
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                      usExtRlcMacCtrlMsgSegCap;   /* Range: [0,1],0x0:,0x1: */
    VOS_UINT8                                       aucReserve[2];
}NVIM_EXT_RLC_MAC_CTRL_MSG_SEGMENT_CAPABILITY_STRU;

/*****************************************************************************
     : NVIM_PS_HANDOVER_CAPABILITY_STRU
   : en_NV_Item_PS_Handover_Capability 
 DESCRIPTION: MSPS
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                      usPsHandoverCapability;     /* Range: [0,1],0x0:,0x1: */
    VOS_UINT8                                       aucReserve[2];
}NVIM_PS_HANDOVER_CAPABILITY_STRU;

/*****************************************************************************
     : NVIM_GAS_WEAK_SIGNAL_THREHOLD_STRU
   : en_NV_Item_GAS_Errorlog_Energy_Threshold 
 DESCRIPTION: GSM ErrorLogRSSI 
*****************************************************************************/
typedef struct
{
    VOS_INT16                                       sWeakSignalThreshold;       /* GSM ErrorLogRSSIRange:[-120,20] */
    VOS_UINT8                                       aucReserve[2];
}NVIM_GAS_WEAK_SIGNAL_THREHOLD_STRU;

/*****************************************************************************
     : NVIM_GSM_MULTIRATE_CAP_STRU
   : en_NV_Item_GSM_Multirate_Capability 
 DESCRIPTION: UEGSM
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                       ucGsmMultirateCap;          /* GSM.0x0:,0x1:DUAL RATE,0x2:SDCCH */
    VOS_UINT8                                       aucRsv[3];
}NVIM_GSM_MULTIRATE_CAP_STRU;

/*****************************************************************************
     : NVIM_GSM_CLASSMARK3_R8_STRU
   : en_NV_Item_Gsm_Classmark3_R8 
 DESCRIPTION: GSM Classmark3
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                       aucGsmClassMark3Data[NVIM_CLASSMARK3_R8_LEN];   /* CLASSMARK3  */
}NVIM_GSM_CLASSMARK3_R8_STRU;

/*****************************************************************************
     : NVIM_EUTRA_MEAS_AND_REPORTING_SUPPORT_FLG_STRU
   : en_NV_Item_EUTRA_MEAS_AND_REPORTING_SUPPORT_FLG 
 DESCRIPTION: MSEUTRAN
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                      usLteMeasSupportedFlg;      /* Range: [0,1],0x0:,0x1: */
    VOS_UINT8                                       aucReserve[2];
}NVIM_EUTRA_MEAS_AND_REPORTING_SUPPORT_FLG_STRU;

/*****************************************************************************
     : NVIM_PRI_BASED_RESEL_SUPPORT_FLG_STRU
   : en_NV_Item_PRI_BASED_RESEL_SUPPORT_FLG 
 DESCRIPTION: MS
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                      usPriBasedReselSupportFlg;  /* Range: [0,1],0x0:,0x1: */
    VOS_UINT8                                       aucReserve[2];
}NVIM_PRI_BASED_RESEL_SUPPORT_FLG_STRU;

/*****************************************************************************
     : NVIM_GERAN_TO_EUTRA_SUPPORT_IN_TRANSFER_MODE_STRU
   : en_NV_Item_GERAN_TO_EUTRA_SUPPORT_IN_TRANSFER_MODE 
 DESCRIPTION: MSLTE
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                      usLteSupportInTransferMode; /* Range: [0,3]
                                                                                   0x0:GSME-UTRAN;
                                                                                   0x1:GSME-UTRAN,GSMEUTRANCCN/CCOEUTRAN
                                                                                   0x2:GSME-UTRAN,GSMEUTRANCCN/CCOEUTRAN
                                                                                   0x3:12PS HANDOVEREUTRAN, */
    VOS_UINT8                                       aucReserve[2];
}NVIM_GERAN_TO_EUTRA_SUPPORT_IN_TRANSFER_MODE_STRU;

/*****************************************************************************
     : NVIM_UE_EUTRA_FREQ_BAND_INFO_STRU
   :  LTE 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucBandNo;
    VOS_UINT8                           ucDuplexModeFlg;
    VOS_UINT8                           aucReserve[2];
}NVIM_UE_EUTRA_FREQ_BAND_INFO_STRU;

/*****************************************************************************
     : NVIM_UE_EUTRA_SUPPORT_FREQ_BAND_LIST_STRU
   : en_NV_Item_EUTRA_CAPA_COMM_INFO 
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usBandCnt;
    VOS_UINT8                               aucReserved1[2];
    NVIM_UE_EUTRA_FREQ_BAND_INFO_STRU       astCandBands[NVIM_EUTRA_MAX_SUPPORT_BANDS_NUM];
}NVIM_UE_EUTRA_SUPPORT_FREQ_BAND_LIST_STRU;

/*****************************************************************************
     : NVIM_GAS_HIGH_MULTISLOT_CLASS_STRU
   : en_NV_Item_GAS_High_Multislot_Class 
 DESCRIPTION: MSMulti class33
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usHighMultislotClassFlg;            /* Range: [0,1],0x0:,0x1: */
    VOS_UINT16                              usHighMultislotClass;               /* NV */
}NVIM_GAS_HIGH_MULTISLOT_CLASS_STRU;

/*****************************************************************************
     : NVIM_GPRS_NON_DRX_TIMER_LENGTH_STRU
   : en_NV_Item_GPRS_Non_Drx_Timer_Length 
 DESCRIPTION: NON-DRXRAUAttach
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usNonDrxTimerLen;                   /* Range: [0,7]
                                                                                   0:NON-DRX0
                                                                                   1:NON-DRX1
                                                                                   2:NON-DRX2
                                                                                   3:NON-DRX4
                                                                                   4:NON-DRX8
                                                                                   5:NON-DRX16
                                                                                   6:NON-DRX32
                                                                                   7:NON-DRX64
                                                                                   */
    VOS_UINT8                               aucReserve[2];
}NVIM_GPRS_NON_DRX_TIMER_LENGTH_STRU;

/*****************************************************************************
     : NVIM_UE_TDS_SUPPORT_FREQ_BAND_LIST_STRU
   : en_NV_Item_UTRAN_TDD_FREQ_BAND 
 DESCRIPTION: TDS
*****************************************************************************/
typedef struct
{
    VOS_UINT8                               ucBandCnt;                          /* TDS,3(A/E/F),Range: [0,6] */
    VOS_UINT8                               aucReserved[3];
    VOS_UINT8                               aucBandNo[NVIM_TDS_MAX_SUPPORT_BANDS_NUM];  /* aucBandNo[x]TDS */
}NVIM_UE_TDS_SUPPORT_FREQ_BAND_LIST_STRU;

/*****************************************************************************
     : NVIM_QSEARCH_CUSTOMIZATION_STRU
   : en_NV_Item_QSearch_Customization 
 DESCRIPTION: QSearch
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usQSearchCustomMode;                /* 0x0:3GPP,0x1: */
    VOS_UINT8                               aucReserve[2];
}NVIM_QSEARCH_CUSTOMIZATION_STRU;

/*****************************************************************************
     : NVIM_GSM_POOR_RXQUAL_THRESHOLD_STRU
   : en_NV_Item_Gsm_Poor_RxQual_ThresHold 
 DESCRIPTION: 
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usRrPoorRxQualThresHold;
    VOS_UINT8                               aucReserve[2];
}NVIM_GSM_POOR_RXQUAL_THRESHOLD_STRU;

/*****************************************************************************
     : NVIM_CSFB_CUSTOMIZATION_STRU
   : en_NV_Item_Csfb_Customization 
 DESCRIPTION: L2G CSFB
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usCsfbCustomization;                /* 0x0:,0x1: */
    VOS_UINT8                               aucReserve[2];
}NVIM_CSFB_CUSTOMIZATION_STRU;

/*****************************************************************************
     : NVIM_CBS_MID_LIST_STRU
   : en_NV_Item_CBS_MID_List 
 DESCRIPTION: 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                               aucCbsMidList[NVIM_CBS_MID_LIST_LEN];
}NVIM_CBS_MID_LIST_STRU;

/*****************************************************************************
     : NVIM_CBS_MID_RANGE_LIST_STRU
   : en_NV_Item_CBS_MID_Range_List 
 DESCRIPTION: 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                               aucCbsMidRangeList[NVIM_CBS_MID_RANGE_LIST_LEN];
}NVIM_CBS_MID_RANGE_LIST_STRU;

/*****************************************************************************
     : NVIM_GSM_AUTO_FR_LTE_MEAS_CONFIG_STRU
   : GSMLTELTE
 DESCRIPTION: GSMLTELTE
   :
 1.        : 20130805
           : y00142674
       : , GSMLTE
*****************************************************************************/
typedef struct
{
   VOS_UINT8                            ucFrLteMeasFlag;                        /* GSMLTELTE0: , 1: 1 */
   VOS_UINT8                            ucMaxSavedMeasTimes;                    /* 8:[0,8] */

   VOS_UINT8                            ucFrInvalidMeasFlag;                    /* GSMLTE0: , 1: 1 */
   VOS_UINT8                            ucMaxInvalidMeasTimes;                  /* 8:[0,8] */
}NVIM_GSM_AUTO_FR_LTE_MEAS_CONFIG_STRU;

/*****************************************************************************
     : NVIM_GSM_C1_CUSTOMIZE_CFG_STRU
   : C1
 DESCRIPTION: C1
   :
 1.        : 20140117
           : w00146666
       : , C1
*****************************************************************************/
typedef struct
{
   VOS_UINT8                            ucC1CustomizeSwitchFlag;          /* C10: , 1: 0 */
   VOS_UINT8                            ucRxlevAccessMin;                 /* C18:[0,63] */
   VOS_UINT8                            ucC1ValueThreshold;               /* C1 */
   VOS_UINT8                            aucRsv[1];
}NVIM_GSM_C1_CUSTOMIZE_CFG_STRU;

/*****************************************************************************
     : NVIM_GSM_NFREQ_THRESHOLD_STRU
   : en_NV_Item_Gsm_NFreq_Threshold 
 DESCRIPTION: 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                            ucFirstNFreqThreshold;                 /*  */
    VOS_UINT8                            aucRsv[3];
}NVIM_GSM_NFREQ_THRESHOLD_STRU;

/*****************************************************************************
     : NVIM_GAS_W_NON_NCELL_MEAS_CTRL_STRU
   : en_NV_Item_Gas_W_Non_NCell_Meas_Ctrl 
 DESCRIPTION: NVGSMWCDMA
*****************************************************************************/
typedef struct
{
    VOS_UINT8                            ucIdleNonNCellMeasEnable;              /* 0: , 1:  */
    VOS_UINT8                            ucTransferNonNCellMeasEnable;          /* 0: , 1:  */
    VOS_INT16                            sRscpThreshold;                        /*  RSCP Range:[-119,0) */
    VOS_INT16                            sEcn0Threshold;                        /*  ECN0 Range:[-20,0) */
    VOS_INT16                            sRssiThreshold;                        /*  RSSI Range:[-101,0) */
}NVIM_GAS_W_NON_NCELL_MEAS_CTRL_STRU;
/* Added by l67237 for Gas Dsds Feature, 2014-3-4, begin */
/*****************************************************************************
     : NV_GSM_RF_UNAVAILABLE_CFG_STRU
   : en_NV_Item_GSM_RF_UNAVAILABLE_CFG 
 DESCRIPTION: 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucStartSearchFlag;                      /* :,1:; 0: */
    VOS_UINT8                           ucSearchTimerLen;                       /* :s */
    VOS_UINT8                           ucEnableScellSbFbFlag;                  /* 1:0: */
    VOS_UINT8                           ucRsv;
}NV_GSM_RF_UNAVAILABLE_CFG_STRU;
/* Added by l67237 for Gas Dsds Feature, 2014-3-4, end */

/*****************************************************************************
     : NVIM_GSM_CELL_INFO_RPT_CFG_STRU
   : en_NV_Item_Gsm_Cell_Info_Rpt_Cfg 
 DESCRIPTION: GASMTC
*****************************************************************************/
typedef struct
{
    VOS_UINT8                            ucCellInfoRptFlg;                      /* : 0:; 1: */
    VOS_UINT8                            aucRsv[1];                             /*  */
    VOS_UINT16                           usRptInterval;                         /* , : ms */
}NVIM_GSM_CELL_INFO_RPT_CFG_STRU;

/*****************************************************************************
     : NVIM_GAS_INDIVIDUAL_CUSTOMIZE_CFG_STRU
   : en_NV_Item_Gas_Individual_Customize_Cfg 
 DESCRIPTION: 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucAccFailNoPunishCfg;                   /* ,NV3036 */
    VOS_INT8                            cFreqRxlevThreshold;                    /* ,
                                                                                     */

    VOS_UINT8                           ucAutoFrNonChanRelCase;                 /*  Channel Release  FR:
                                                                                   bit0: 1:  FR;
                                                                                         0: FR
                                                                                   bit1: 1: FR;
                                                                                         0: FR
                                                                                   bit2: 1: ;
                                                                                         0:  */

    VOS_UINT8                           ucScellPrioFastEnableFlg;               /* SI2Q0:,1: */

    VOS_UINT8                           aucRsv[36];
}NVIM_GAS_INDIVIDUAL_CUSTOMIZE_CFG_STRU;

/*****************************************************************************
     : NVIM_GSM_MNTN_CONFIG_STRU
   : GSMNV
 DESCRIPTION: GSMNV
   :
 1.        : 20140703
           : w00146666
       : 
 2.        : 20151026
           : w00146666
       : CHR NV 
 3.        : 20160414
           : w00146666
       : GSM PA CHRNV(, )   
 4.        : 20170110
           : w00402148
       : GSM RACHR  
*****************************************************************************/
typedef struct
{
   VOS_UINT16                           usCsHoTimeAlarmThreshold;              /* CSGAS */

   VOS_UINT16                           usRptPseudBtsMinTimeInterval;          /* CHR:30 */   

   VOS_INT16                            sRptRaFailRssiThreshold;               /* GAS, -85dBm */

   VOS_UINT16                           usRptRaNoRspMinTimeInterval;           /* CHR:30 */   
   
   VOS_INT16                            sRaNoRspRssiThreshold;                 /* GAS,-85dBm */
   
   VOS_UINT8                            usRaNoRspAlarmTimesThreshold;          /* GAS10 */   

   VOS_UINT8                            ucRptAbnormalAirMsgMinTimeInterval;    /* CHR:30 */      

   VOS_UINT32                           ulRptRaFailMinTimeInterval;            /* :30 */

   VOS_UINT32                           ulRsv7;                                /* 7KWKC */
}NVIM_GAS_MNTN_CONFIG_STRU;

/*****************************************************************************
     : NVIM_GAS_MNTN_CHR_DIRECT_RPT_CONFIG_STRU
   : GAS CHRNV
   :
 1.        : 20161108
           : y00383718
       : 
*****************************************************************************/
typedef struct
{
   VOS_UINT8                            ucNotSuppBssPagingCoorFlag;             /*  */
   
   VOS_UINT8                            ucNotSuppBssPagingCoorMaxNum;           /*  */

   VOS_UINT8                            ucRsrcCheckExcpFlag;                    /*  */

   VOS_UINT8                            ucRsrcCheckExcpMaxNum;                  /*  */

   VOS_UINT8                            ucCustomC1CellFlag;                     /* C1 */

   VOS_UINT8                            ucCustomC1CellMaxNum;                   /* C1 */

   VOS_UINT8                            ucRsv5;                                 /* KWKC */

   VOS_UINT8                            ucRsv6;                                 /* KWKC */

   VOS_UINT16                           usRsv1;                                 /* KWKC */   

   VOS_UINT16                           usRsv2;                                 /* KWKC */

   VOS_UINT16                           usRsv3;                                 /* KWKC */
   
   VOS_UINT16                           usRsv4;                                 /* KWKC */

   VOS_UINT32                           ulNotSuppBssPagingCoorInterval;         /*  30min, : 10ms */  

   VOS_UINT32                           ulRsrcCheckExcpInterval;                /*  60min, : min */

   VOS_UINT32                           ulCustomC1CellInterval;                 /* C1 30min, : min */

   VOS_UINT32                           ulRsv4;                                 /* KWKC */
}NVIM_GAS_MNTN_CHR_DIRECT_RPT_CONFIG_STRU;


/*****************************************************************************
     : NVIM_GAS_UTRAN_TDD_DEFAULT_Q_RXLMIN
   : en_NV_Item_GAS_UTRAN_TDD_DEFAULT_Q_RXLMIN NV 
              UTRAN ,  UTRAN TDD Q_RXLMIN. 
             .  Ranking  -90dB, 
 DESCRIPTION: en_NV_Item_GAS_UTRAN_TDD_DEFAULT_Q_RXLMIN NV 
               UTRAN ,  UTRAN TDD Q_RXLMIN. 
              .  Ranking  -90dB, 
   :
 1.        : 20141220
           : p00166345
       : 
*****************************************************************************/
typedef struct
{
   VOS_UINT8                            ucTdsDefaultQRxlMin;            /* TDS , : -1dB */

   VOS_UINT8                            aucRsv[3];                      /*  */
}NVIM_GAS_UTRAN_TDD_DEFAULT_Q_RXLMIN;

/* Added by yangsicong for L2G REDIR C1 CUSTUME, 2015-1-26, begin */
typedef struct
{
    VOS_UINT32                          ulMcc;
    VOS_UINT32                          ulMnc;
}NVIM_GAS_PLMN_ID_STRU;

/*****************************************************************************
     : NVIM_GAS_C1_CALC_OPT_PLMN_WHITE_LIST_STRU
   : C1(L CSFB G)
 DESCRIPTION: C1(L CSFB G)
   : 
 1.        : 20150206
           : y00265681
       : 
*****************************************************************************/
typedef struct
{
   VOS_UINT16                           usPlmnCnt;                          /* PLMN */
   VOS_UINT16                           usRxlevAccessMin;                   /* , 8:[0,63]
                                                                               0,  NV9248  ucRxlevAccessMin  */

   NVIM_GAS_PLMN_ID_STRU                astPlmn[NVIM_GAS_C1_CALC_OPT_PLMN_WHITE_LIST_CNT_MAX];       /* PLMN ID20 */
}NVIM_GAS_C1_CALC_OPT_PLMN_WHITE_LIST_STRU;
/* Added by yangsicong for L2G REDIR C1 CUSTUME, 2015-1-26, end */

/*****************************************************************************
     : NVIM_GSM_RAPID_HO_CUSTOMIZE_CFG_STRU
   : en_NV_Item_GSM_RAPID_HO_CUSTOMIZE_CFG ,GSM
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucSwitchFlag;                   /*  */
    VOS_UINT8                           ucBadQualityThreshold;          /* ..:  */
    VOS_UINT16                          usAlpha;                        /* Alpha. : 0.001 */
    VOS_UINT8                           ucBadQualityCntThreshold;       /*  */
    VOS_UINT8                           ucNCellRptAddValue;             /*  */
    VOS_UINT8                           aucRsv[2];                      /*  */
}NVIM_GSM_RAPID_HO_CUSTOMIZE_CFG_STRU;

/*****************************************************************************
     : NVIM_GSM_BAND_CUSTOMIZE_STRU
   : GSM 
   : 
 1.        : 2015-04-23
           : p00166345
       : 
*****************************************************************************/
typedef struct
{
    NVIM_GAS_PLMN_ID_STRU               stPlmn;                                 /* PLMN */
    VOS_UINT32                          ulBand;                                 /*  */
}NVIM_GSM_BAND_CUSTOMIZE_STRU;

/*****************************************************************************
     : NVIM_GAS_GSM_BAND_CUSTOMIZE_CFG_STRU
   : en_NV_Item_GAS_GSM_BAND_CUSTOMIZE_CFG NV 
 DESCRIPTION: PLMNGSM BANDBAND
   : 
 1.        : 2015-04-23
           : p00166345
       : 
*****************************************************************************/
typedef struct
{
   VOS_UINT16                           usItemCnt;                  /* Range:[0-80] */
   VOS_UINT16                           usRestoreEnableMask;        /* ,
                                                                       bit0:L2G0x0:,0x1: 
                                                                       bit1:GOOS, 0x0:,0x1: */
   VOS_UINT32                           ulCustomizeBandEnableMask;  /*  Band 
                                                                       bit0:L2G0x0:,0x1: 
                                                                       bit1:GOOS, 0x0:,0x1: */
   NVIM_GSM_BAND_CUSTOMIZE_STRU         astCustomizeBand[NVIM_GAS_GSM_BAND_CUSTOMIZE_LIST_MAX_CNT];     /* PLMN */
}NVIM_GAS_GSM_BAND_CUSTOMIZE_CFG_STRU;

/* Added by y00142674 for , 2015-04-30, begin */
/*****************************************************************************
     : NVIM_GSM_SEARCH_CUSTOMIZE_CFG_STRU
   : en_NV_Item_GSM_SEARCH_CUSTOMIZE_CFG GSM
 DESCRIPTION: GSM
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucRsv1;                                 /*  */
    VOS_UINT8                           ucRsv2;                                 /* GOos */

    VOS_UINT8                           ucGeoHighUseStoreFlag;                  /*  */
    VOS_UINT8                           ucGeoHighRemoveStoreFlag;               /*  */
    VOS_UINT8                           ucGeoNormalUseStoreFlag;                /*  */

    VOS_UINT8                           ucRmvDecFailSamePlmnFlag;               /* PLMN */

    VOS_UINT8                           ucUpdateRssiBySi;                       /*  */

    VOS_UINT8                           ucHistorySrchOperatorCustomizeCellCnt;  /* HISTORY */

}NVIM_GSM_SEARCH_CUSTOMIZE_CFG_STRU;
/* Added by y00142674 for , 2015-04-30, end */

/*****************************************************************************
     : NVIM_GAS_GSM_CELL_HISTORY_BCCH_SI_CFG_STRU
   : en_NV_Item_GAS_GSM_CELL_HISTORY_BCCH_SI_CFG NV 
 DESCRIPTION: GSMBCCH
   : 
 1.        : 2015-05-06
           : p00166345
       : 
 2.        : 2015-07-15
           : y00142674
       : 

*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEnableFlg;                    /* ,0x0:,0x1: */
    VOS_UINT8                           ucRefreshTimeLen;               /* .
                                                                           :. 0 */

    VOS_UINT16                          usValidTimeLen;                 /* , : */
    VOS_UINT32                          ulUsableMask;                   /*  */
    VOS_UINT8                           ucNcellEnableFlg;               /*  */
    VOS_UINT8                           ucNcellValidTimeLen;            /* , : */
    VOS_UINT8                           ucRsv3;                         /*  */
    VOS_UINT8                           ucRsv4;                         /*  */
}NVIM_GAS_GSM_CELL_HISTORY_BCCH_SI_CFG_STRU;

/*****************************************************************************
     : NVIM_GAS_H_PRIO_CONDITION_FLAG_STRU
   : H_PRIO 
 DESCRIPTION: GH_Prio
   : 
 1.        : 20150517
           : w00146666
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                            ucHPrioCustomizeFlag;   /* H_PRIO, 0H_PRIO
                                                                    1H_PRIO */
    
    VOS_UINT8                            ucRsv1;                 /* 1 */
    
    VOS_UINT8                            ucRsv2;                 /* 2 */
    
    VOS_UINT8                            ucRsv3;                 /* 3 */
}NVIM_GAS_INTER_RAT_RESEL_H_PRIO_CUSTOMIZE_STRU;

/*****************************************************************************
     : NVIM_GAS_FAST_AREA_LOST_CFG_STRU
   : en_NV_Item_GAS_FAST_AREA_LOST_CFG NV
              RR  NAS 
 DESCRIPTION:  RR  NAS 
   : 
 1.        : 20150515
           : p00166345
       : 
*****************************************************************************/
typedef struct
{
   VOS_UINT8                            ucRrRaFailEnableFlg;        /* ,0:;1: */

   VOS_UINT8                            ucRsv1;                     /*  */
   VOS_UINT8                            ucRsv2;                     /*  */
   VOS_UINT8                            ucRsv3;                     /*  */
}NVIM_GAS_FAST_AREA_LOST_CFG_STRU;

/*****************************************************************************
     : NVIM_GAS_AUTO_FR_CFG_STRU
   : en_NV_Item_GAS_AUTO_FR_CFG NV
              FR.
 DESCRIPTION:  FR.
   : 
 1.        : 2015-06-09
           : p00166345
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                            ucAutoFrInvalidMask;   /* bit 0 , 1  */
                                                                /* bit0: CSFB , NAS */
                                                                /* bit1: CSFB , NAS */
                                                                /* bit2~bit8:  */

    VOS_UINT8                            ucAutoFrNonCsfbFlg;       /* CSFB,  */
    VOS_UINT8                            ucRsv2;                /*  */
    VOS_UINT8                            ucRsv3;                /*  */
}NVIM_GAS_AUTO_FR_CFG_STRU;

/*****************************************************************************
     : NVIM_GAS_INTER_RAT_RESEL_CFG_STRU
   : en_NV_Item_GAS_INTER_RAT_RESEL_CFG NV
 DESCRIPTION: .
   : 
 1.        : 2015-07-07
           : p00166345
       : 
 2.       : 2017113
          : s00184266
      : dts2017011012871, NV
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucPrioReselDisableMask; /* . bit 1.0 */
                                                                /* : 0 NV 9003 */
                                                                /* bit0: LTE , 3G */
                                                                /* bit1: LTE  Disable, 3G */
                                                                /* bit2~bit8:  */

    VOS_UINT8                           ucWaitAllNCellDecodedByThreshGsmLow;    /*  */
    VOS_UINT8                           ucRsv2;                 /*  */
    VOS_UINT8                           ucRsv3;                 /*  */
    VOS_UINT16                          usRsv4;                 /*  */
    VOS_UINT16                          usRsv5;                 /*  */
}NVIM_GAS_INTER_RAT_RESEL_CFG_STRU;

/* Added by p00166345 for DTS2015052601104(), 2015-08-02, begin */
/*****************************************************************************
 Structure      : NVIM_GAS_PSEUD_BTS_IDENT_CUSTOMIZE_CFG_STRU
 Description    : NV
 DESCRIPTION: 
 Message origin :
  :
  1.        : 20150729
            : yangsicong
        : 
*****************************************************************************/
typedef struct
{
    VOS_UINT16      usEnableBitmap;             /*  0=1= */
                                                    /* bit0: X2G REDIR; */
                                                    /* bit1: X2G reselect; */
                                                    /* bit2: X2G CCO; */
                                                    /* bit3: GSM  SPEC/GOOS; */
                                                    /* bit4: GSM HISTORY/GSM FAST; */
                                                    /* bit5~bit15:  */
    VOS_UINT16      ucReserve1;                 /*  */
    VOS_UINT16      usFeatureSetEnableBitmap;   /* BITMAP: bit (n)=1n; */
    VOS_UINT16      usReserve2;                 /*  */
    VOS_UINT16      usPseudBTSFeatureSet0;      /* 0,bit,bit1:
                                                    bit0 RX_ACCESS_MIN=0; 
                                                    bit1  CCCH-CONF='001',BS-AG-BLKS-RES=2; 
                                                    bit2  GPRS; 
                                                    bit3 CRO 60;
                                                    bit4 MCC460;
                                                    bit5~bit15 */
    VOS_UINT16      usPseudBTSFeatureSet1;      /* */
    VOS_UINT16      usPseudBTSFeatureSet2;      /* */
    VOS_UINT16      usPseudBTSFeatureSet3;      /* */
    VOS_UINT16      usPseudBTSFeatureSet4;      /* */
    VOS_UINT16      usPseudBTSFeatureSet5;      /* */
    VOS_UINT16      usPseudBTSFeatureSet6;      /* */
    VOS_UINT16      usPseudBTSFeatureSet7;      /* */
} NVIM_GAS_PSEUD_BTS_IDENT_CUSTOMIZE_CFG_STRU;
/* Added by p00166345 for DTS2015052601104(), 2015-08-02, end */

/*****************************************************************************
     : NVIM_GAS_NETWORK_SEARCH_CUSTOMIZE_CFG_STRU
   : NV
 DESCRIPTION: GSM
   :
  1.     : 2015914
         : s00184266
     : 
  2.       : 2016629
           : s00184266
       : pref band saved cell, 

*****************************************************************************/
typedef struct
{
    VOS_UINT32              ulHistoryFreqEnableBitmap;                          /* bit */
    VOS_UINT32              ulOperateFreqEnableBitmap;                          /* bit */
    VOS_UINT32              ulFullListEnableBitmap;                             /* bit */
    VOS_UINT32              ulHistoryFilterSrchedFreqEnableBitmap;              /*  bit */
    VOS_UINT32              ulOperateFilterSrchedFreqEnableBitmap;              /*  bit */
    VOS_UINT32              ulFullListFilterSrchedFreqEnableBitmap;             /*  bit */
    VOS_UINT32              ulIgnoreLowPrioJudgeEnableBitmap;                   /* bit */
    VOS_UINT32              ulCloudFreqEnableBitmap;                            /* bit */
    VOS_UINT32              ulHistoryFreqBandSrchEnableBitmap;                  /*  */
    VOS_UINT32              ulPresetFreqBandSrchEnableBitmap;                   /*  */
    VOS_UINT32              ulCloudBandEnableBitmap;                            /* bit */
    VOS_UINT32              ulCloudFreqFilterSrchedFreqEnableBitmap;            /*  bit */
    VOS_UINT32              ulRescueCellByPresetBandEnableBitmap;               /* bit */
    VOS_UINT32              ulCssShareFreqSrchEnableBitmap;                     /* CSSModembit */
    VOS_UINT32              ulReserved3;                                        /*  */
    VOS_UINT32              ulReserved4;                                        /*  */
    VOS_UINT32              ulReserved5;                                        /*  */
}NVIM_GSM_NETWORK_SEARCH_CUSTOMIZE_CFG_STRU;

/*****************************************************************************
     : NVIM_GSM_OPERATE_CUSTOMIZE_FREQ_RANGE_STRU
   : GSM
 DESCRIPTION: GSM
   :
  1.     : 2015828
         : s00184266
     : 

*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usFreqBegin;                            /*  */
    VOS_UINT16                          usFreqEnd;                              /*  */
    NVIM_BAND_IND_ENUM_UINT8            enBand;                                 /* BAND */
    VOS_UINT8                           ucRsv1;                                 /*  */
    VOS_UINT8                           ucRsv2;                                 /*  */
    VOS_UINT8                           ucRsv3;                                 /*  */
}NVIM_GSM_OPERATE_CUSTOMIZE_FREQ_RANGE_STRU;

/*****************************************************************************
     : NVIM_GSM_OPERATE_CUSTOMIZE_DISCRETE_STRU
   : GSMGSM
 DESCRIPTION: GSMGSM
   :
  1.     : 201591
         : s00184266
     : 

*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usFreq;                                 /*  */
    NVIM_BAND_IND_ENUM_UINT8            enBand;                                 /* BAND */
    VOS_UINT8                           ucRsv1;                                 /*  */
}NVIM_GSM_OPERATE_CUSTOMIZE_DISCRETE_STRU;

/*****************************************************************************
     : NVIM_GSM_OPERATOR_CUSTOMIZE_PLMN_ITEM_STRU
   : GSMPLMNBAND
 DESCRIPTION: GSMPLMNBAND
   :
  1.     : 2015828
         : s00184266
     : 

*****************************************************************************/
typedef struct
{
    NVIM_GAS_PLMN_ID_STRU                       stPlmn;                         /* PLMN */
    VOS_UINT8                                   ucRangeCnt;                     /* :NVIM_GSM_OPERATE_CUSTOMIZE_FREQ_RANGE_MAX_CNT */
    VOS_UINT8                                   ucDiscreteCnt;                  /* :NVIM_GSM_OPERATE_CUSTOMIZE_DESCRETE_FREQ_MAX_CNT */
    VOS_UINT8                                   ucRsv1;                         /*  */
    VOS_UINT8                                   ucRsv2;                         /*  */
    NVIM_GSM_OPERATE_CUSTOMIZE_FREQ_RANGE_STRU  astGsmOperateCustomFreqRange[NVIM_GSM_OPERATE_CUSTOMIZE_FREQ_RANGE_MAX_CNT];
                                                                                /*  */
    NVIM_GSM_OPERATE_CUSTOMIZE_DISCRETE_STRU    astGsmOperateCustomDiscrete[NVIM_GSM_OPERATE_CUSTOMIZE_DESCRETE_FREQ_MAX_CNT];
                                                                                /*  */
    VOS_UINT8                                   ucRsv3;                         /*  */
    VOS_UINT8                                   ucRsv4;                         /*  */
    VOS_UINT16                                  usRsv1;                         /*  */
    VOS_UINT32                                  ulRsv1;                         /*  */
}NVIM_GSM_OPERATOR_CUSTOMIZE_PLMN_ITEM_STRU;

/*****************************************************************************
     : NVIM_GSM_OPERATOR_CUSTOMIZE_FREQ_CFG_STRU
   : GSMNV
 DESCRIPTION: GSM
   :
  1.     : 2015828
         : s00184266
     : 

*****************************************************************************/
typedef struct
{
    VOS_UINT8                                   ucPlmnCnt;                      /* PLMN:NVIM_GSM_OPERATE_CUSTOMIZE_FREQ_PLMN_MAX_CNT */
    VOS_UINT8                                   ucRsv1;                         /*  */
    VOS_UINT8                                   ucRsv2;                         /*  */
    VOS_UINT8                                   ucRsv3;                         /*  */
    NVIM_GSM_OPERATOR_CUSTOMIZE_PLMN_ITEM_STRU  astGsmOperatorCustomPlmnItem[NVIM_GSM_OPERATE_CUSTOMIZE_FREQ_PLMN_MAX_CNT];   
                                                                                /* PLMN */
}NVIM_GSM_OPERATOR_CUSTOMIZE_FREQ_CFG_STRU;

/*****************************************************************************
     : NVIM_GSM_PARALLEL_SEARCH_CUSTOMIZE_CFG_STRU
   : en_NV_Item_GSM_PARALLEL_SEARCH_CUSTOMIZE_CFG GSM
 DESCRIPTION: GSM
   :
  1.       : 2016620
           : s00184266
       : ucAnyCellSrchBaFlag
 
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulWaitFirstUsableMask;          /*  */
    VOS_UINT16                          usWaitFirstTimerLen;            /* :ms */

    VOS_INT16                           sSameLaiThreshold;              /* LAIRSSI */
    VOS_UINT32                          ulSameLaiUsableMask;            /* LAI */
    VOS_UINT16                          usSameLaiTimerLen;              /* LAI:ms */
    VOS_UINT8                           ucStoreSameLaiFlag;             /* LAI */
    VOS_UINT8                           ucFullSameLaiFlag;              /* LAI */

    VOS_UINT32                          ulWithSiUsableMask;             /*  */
    VOS_UINT8                           ucStoreWithSiFlag;              /*  */
    VOS_UINT8                           ucFullWithSiFlag;               /*  */
    VOS_INT16                           sWithSiThreshold;               /* RSSI */

    VOS_UINT8                           ucRmvUtranImpactFlg;            /* Utran */
    VOS_UINT8                           ucRmvPseudoNCell;               /*  */
    VOS_UINT8                           ucAutoAnycellCamp;              /* SUITABLEANYCELL */
    VOS_UINT8                           ucMaxArfcnNum;                  /*  */

    VOS_UINT8                           ucFirstTcIgnoreSi2Q;            /* TCSI2Quater */
    VOS_UINT8                           ucRmvNoNeedCellFlg;             /*  */
    VOS_UINT8                           ucRmvCellBetterThreshold;       /*  */
    VOS_UINT8                           ucAnyCellSrchBaFlag;            /* Any CellBA */

    VOS_UINT16                          usRsv1;                         /*  */
    VOS_UINT16                          usRsv2;                         /*  */
    VOS_UINT16                          usRsv3;                         /*  */
    VOS_UINT16                          usRsv4;                         /*  */

    VOS_INT16                           sRmvCellLastRxlevThreshold;     /*  */
    VOS_INT16                           sRsv2;                          /*  */
    VOS_INT16                           sRsv3;                          /*  */
    VOS_INT16                           sRsv4;                          /*  */

    VOS_UINT32                          ulRsv1;                         /*  */
    VOS_UINT32                          ulRsv2;                         /*  */
    VOS_UINT32                          ulRsv3;                         /*  */
    VOS_UINT32                          ulRsv4;                         /*  */

}NVIM_GSM_PARALLEL_SEARCH_CUSTOMIZE_CFG_STRU;

/*****************************************************************************
     : NVIM_GSM_ENABLE_HISTORY_ARFCN_WITH_SPEC_ARFCN_LST_STRU
   : en_NV_Item_GSM_ENABLE_HISTORY_ARFCN_WITH_SPEC_ARFCN_LST NV
 DESCRIPTION: L2G ,
   :
  1.     : 2015-10-16
         : p00166345
     : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCsfbEnableFlg;                        /* L2GCSFB,0x0:,0x1: */
    VOS_UINT8                           ucRedirEnableFlg;                       /* L2GCSFB,0x0:,0x1: */
    VOS_INT8                            cSpecArfcnPreferThreshold;              /*  */
    VOS_UINT8                           ucHistoryArfcnRssiReduceValue;          /* RSSIucHistoryArfcnRssiReduceValue */
    VOS_UINT8                           ucRsv1;
    VOS_UINT8                           ucRsv2;
    VOS_UINT8                           ucRsv3;
    VOS_UINT8                           ucRsv4;
}NVIM_GSM_ENABLE_HISTORY_ARFCN_WITH_SPEC_ARFCN_LST_STRU;

/*****************************************************************************
     : NVIM_GAS_RR_CONNECT_FAIL_PUNISH_CFG_STRU
   : RR
 DESCRIPTION: RR
   :
  1.     : 20151021
         : w00146666
     : 
  2.     : 2015124
         : w00146666
     : for DTS2015112600361, 
  3.     : 20160510
         : w00146666
     : for DTS2016050901311, 
*****************************************************************************/
typedef struct
{
    /* ===============NV===================== */
    VOS_UINT8           ucCsAccFailPunishSwitchFlag;        /* CS0: , 1: 1 */

    VOS_UINT8           ucPsAccFailPunishSwitchFlag;        /* PS0: , 1: 0 */

    VOS_UINT8           ucRrConnFailOptimizeSwtichFlag;     /* 
                                                               0: , 1: 1
                                                               NV
                                                               1.
                                                               FORBIND
                                                               BAR

                                                               2.
                                                               N200(NV)
                                                               N200(NV), BAR

                                                               3.
                                                               
                                                               N200                                                               

                                                               NVFORBINDN200
                                                               FORBIND3
                                                               */

    /* ===============NV===================== */
    VOS_UINT8           ucStartPunishRaFailTimesThreshold;     /* GSM,  */

    VOS_UINT8           ucRssiOffset;                         /* Bar */


    /* ===============N200NV============================== */
    VOS_UINT8           ucN200FailPunishSwitchFlag;             /* N2000: , 1: 1 */

    VOS_UINT8           ucStartReselN200FailTimesThreshold;     /* GSMN200,  */

    VOS_UINT8           ucStartPunishN200FailTimesThreshold;    /* GSMN200,  */
    
    VOS_INT16           sN200FailRssiThreshold;                 /* GSMN200RSSI:dBm  */

    /* ===============NV============================== */
    VOS_UINT16          usInitialForbidTimeLen;                /* : */

    VOS_UINT16          usMaxForbidTimeLen;                    /* : */

    VOS_INT16           sRssiHighThresh;                      /* :dBm,  */

    VOS_UINT32          ulForbidCellMaxReServeTimeLen;        /* Forbid: */

    VOS_UINT32          ulRssiThresholdSet;                    /* :dBm
                                                                  ,-85dBm-85dBm-85dBm;
                                                                  ,-95dBm, -85dBm-95dBm, -85dBm-95dBm;*/

    VOS_UINT32          ulRssiOffsetSet;                       /* 
                                                                  ,20;
                                                                  ,8;
                                                                  ,16;
                                                                  */
    VOS_UINT32          ulRsv6;                              /*  */
    VOS_UINT32          ulRsv7;                              /*  */

}NVIM_GAS_RR_CONNECT_FAIL_PUNISH_CFG_STRU;


/*****************************************************************************
     : NVIM_GSM_PING_PONG_HO_CUSTOMIZE_CFG_STRU
   : en_NV_Item_GSM_PING_PONG_HO_CUSTOMIZE_CFG ,GSM 
 DESCRIPTION: GSM 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucSwitchFlag;                   /*  */
    VOS_UINT8                           ucHoTimeThreshold;              /* , 30s */
    VOS_UINT8                           ucBadCellTimeScale;             /* , : 0.1,  20 */
    VOS_UINT8                           ucGoodQualityThreshold;         /* .. : , 5 */
    VOS_UINT8                           ucGoodQualityCntThreshold;      /* ,  3 */
    VOS_UINT8                           ucNCellRptReduceValue;          /* ,,  dB, 20 */
    VOS_UINT8                           ucWatchHoTimes;                 /* ,  4 */
    VOS_UINT8                           aucRsv1;                        /*  */
    VOS_UINT16                          ausRsv1;
    VOS_UINT16                          ausRsv2;
    VOS_UINT8                           aucRsv3;
    VOS_UINT8                           aucRsv4;
    VOS_UINT8                           aucRsv5;
    VOS_UINT8                           aucRsv6;
}NVIM_GSM_PING_PONG_HO_CUSTOMIZE_CFG_STRU;

/*****************************************************************************
     : NVIM_GSM_LTE_MEASURE_CFG_STRU
   : GSMLTENV
 DESCRIPTION: GSMLTENV
   :
  1.     : 2015127
         : s00184266
     : dts2015100803984,

*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucDistLteAcsTypeEnable;         /* LTE */
    VOS_UINT8                           aucRsv1;                        /*  */
    VOS_UINT8                           aucRsv2;
    VOS_UINT8                           aucRsv3;
    VOS_UINT16                          ausRsv1;
    VOS_UINT16                          ausRsv2;
}NVIM_GSM_LTE_MEASURE_CFG_STRU;

/*****************************************************************************
     : NVIM_GSM_SEC_RXQUAL_SUB_ALPHA_FILTERING_CFG_STRU
   : en_NV_Item_GSM_SEC_RXQUAL_SUB_ALPHA_FILTERING_CFG ,GSM SUBALPHA, 
 DESCRIPTION: GSM SUBALPHA, 
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usSecRrPoorRxQualSubThresHold;  /* , :, 0~1000, : 80, 8% */
    VOS_UINT16                          usSecRxQualSubAlpha;            /* Alpha, :, 0~1000, : 250, Alpha0.25 */
    VOS_UINT16                          usSecConSubBerCntThresHold;     /* usSecConSubBerCntThresHold, Poor, : 2,  */
    VOS_UINT8                           ucRsv1;                         /*  */
    VOS_UINT8                           ucRsv2;
    VOS_UINT16                          usRsv1;
    VOS_UINT16                          usRsv2;
}NVIM_GSM_SEC_RXQUAL_SUB_ALPHA_FILTERING_CFG_STRU;

#if defined( __PS_WIN32_RECUR__ ) || defined (DMT)
/*****************************************************************************
     : NVIM_GAS_CHR_PC_CFG_STRU
   : 
   :
  1.     : 20151228
         : w00146666
     : 
*****************************************************************************/
typedef struct  
{
    VOS_UINT32  ulPermitedChrAlarmIdCount;

    VOS_UINT16  aucAlarmIds[MAX_CHR_ALARM_ID_NUM];
    
}NVIM_GAS_CHR_PC_CFG_STRU;
#endif

/*****************************************************************************
     : NVIM_Item_GAS_SAME_LAI_PREFER_CFG_STRU
   : en_NV_Item_GAS_SAME_LAI_PREFER_CFG ,  LAI 
             .
 DESCRIPTION:  LAI .
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucMtSwitchFlag;                 /*  */
    VOS_UINT8                           ucMoSwitchFlag;                 /*  */

    VOS_INT8                            cFirstLevelAddValue;           /*  LAI  */
    VOS_INT8                            cFirstLevelThreshold;          /*  */

    VOS_INT8                            cSecLevelAddValue;             /*  LAI  */
    VOS_INT8                            cSecLevelThreshold;            /*  */
    VOS_UINT16                          usValidTimeLen;                 /* , : */
    VOS_UINT8                           aucRsv1;                        /*  */
    VOS_UINT8                           aucRsv2;                        /*  */
    VOS_UINT8                           aucRsv3;                        /*  */
    VOS_UINT8                           aucRsv4;                        /*  */
}NVIM_Item_GAS_SAME_LAI_PREFER_CFG_STRU;

/*****************************************************************************
     : NVIM_GSM_HO_CUSTOMIZE_CFG_STRU
   : en_NV_Item_GSM_HO_CUSTOMIZE_CFG ,GSM 
 DESCRIPTION: GSM 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucChanModeRptIndication;        /* , MM  GAS_RR_CHAN_IND  */
    VOS_UINT8                           aucRsv1;
    VOS_UINT16                          ausRsv1;
    VOS_UINT8                           aucRsv2;
    VOS_UINT8                           aucRsv3;
    VOS_UINT8                           aucRsv4;
    VOS_UINT8                           aucRsv5;
}NVIM_GSM_HO_CUSTOMIZE_CFG_STRU;

/*****************************************************************************
     : NVIM_GSM_PMR_CFG_STRU
   : en_NV_Item_GSM_PMR_CFG ,GSM PMR
 DESCRIPTION: GSM PMR
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNcReportPeriodIMin;           /*  PMR  */
    VOS_UINT8                           aucRsv1;
    VOS_UINT16                          ausRsv1;
    VOS_UINT8                           aucRsv2;
    VOS_UINT8                           aucRsv3;
    VOS_UINT8                           aucRsv4;
    VOS_UINT8                           aucRsv5;
}NVIM_GSM_PMR_CFG_STRU;

/*****************************************************************************
     : NVIM_GSM_GCBS_MESSAGE_CUSTOMIZE_CFG_STRU
   : en_NV_Item_GCbs_Message_Customize_CFG , GCBS Message
 DESCRIPTION: GCBS Message
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucIsFixedPageDataLengthFlag;    /* ,88PageTAF.VOS_TRUE,88;VOS_FALSE,(BLOCKx22);VOS_TRUE */
    VOS_UINT8                           ucIsOptionalMessageReadFlag;    /* ,Optional reading CB Message.VOS_TRUE,;VOS_FALSE,;VOS_TRUE */
    VOS_UINT8                           ucIsAdvisedMessageReadFlag;     /* ,Reading advised CB Message.VOS_TRUE,;VOS_FALSE,;VOS_TRUE */
    VOS_UINT8                           ucRsv1;                         /*  */
    VOS_UINT8                           ucRsv2;
    VOS_UINT8                           ucRsv3;
    VOS_UINT16                          usRsv1;
    VOS_UINT16                          usRsv2;
    VOS_UINT16                          usRsv3;
}NVIM_GSM_GCBS_MESSAGE_CUSTOMIZE_CFG_STRU;

/*****************************************************************************
     : NVIM_GAS_GSM_ACTIVE_CELL_RESELECT_CFG_STRU
   : en_NV_Item_GAS_GSM_CELL_RESELECT_CFG , GAS G2G
 DESCRIPTION: GAS G2G
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucC2ReselPartialReadFlg;        /* 
                                                                           1: ;
                                                                           0:  */
    VOS_UINT8                           ucRsv1;
    VOS_UINT16                          usHistorySi3ValidTimeLen;       /* SI3. : s */
    VOS_UINT8                           ucRsv2;
    VOS_UINT8                           ucRsv3;
    VOS_UINT8                           ucRsv4;
    VOS_UINT8                           ucRsv5;

    VOS_UINT8                           ucC2ReselPunishSwitchFlg;       /* 
                                                                           1: ;
                                                                           0:  */
    VOS_UINT8                           ucRsv6;
    VOS_INT16                           sScellRssiThreshold;            /* : dBm */
    VOS_UINT16                          usScellPchBerThreshold;         /* PCHAlpha: % */
    VOS_UINT16                          usScellPchBerAlpha;             /* PCHAlphaAlpha: % */
    VOS_UINT16                          usForbiddenCellPunishTimeLen;   /* Forbidden : s */
    VOS_UINT16                          usForbiddenCellPunishStep;      /* : dBm */
    VOS_UINT8                           ucScellRaSuccStep;              /* RA */
    VOS_UINT8                           ucScellRaFailStep;              /* RA */
    VOS_UINT8                           ucRsv9;
    VOS_UINT8                           ucRsv10;  
    VOS_UINT16                          usRsv1;
    VOS_UINT16                          usRsv2;
}NVIM_GAS_GSM_ACTIVE_CELL_RESELECT_CFG_STRU;

/*****************************************************************************
     : NVIM_GAS_GSM_PASSIVE_RESELECT_OPTIMIZE_CFG_STRU
   : en_NV_Item_GAS_GSM_PASSIVE_RESELECT_OPTIMIZE_CFG T3166/T3168
 DESCRIPTION: T3166/T3168
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucImmAssRejOptSwitchFlg;            /*  */
    VOS_UINT8                           ucImmAssRejCntThreshold;            /*  */
    VOS_UINT8                           ucImmAssRejWaitIndThreshold;        /* : s */

    VOS_UINT8                           ucCcAbnormalRelCnt;                 /* , 0xFF  */

    VOS_UINT8                           ucT3166T3168ExpiredOptSwitchFlg;    /*  */
    VOS_UINT8                           ucT3166T3168ExpiredCntThreshold;    /* T3166/T3168 */
    VOS_UINT16                          usT3166T3168ExpiredPunishTimeLen;   /* T3166/T3168: ms */

    VOS_UINT8                           ucRsv1;                             /*  */
    VOS_UINT8                           ucRsv2;
    VOS_UINT8                           ucRsv3;
    VOS_UINT8                           ucRsv4;
    VOS_UINT8                           ucRsv5;
    VOS_UINT8                           ucRsv6;
    VOS_UINT8                           ucRsv7;
    VOS_UINT8                           ucRsv8;

    VOS_UINT16                          usRsv1;
    VOS_UINT16                          usRsv2;
}NVIM_GAS_GSM_PASSIVE_RESELECT_OPTIMIZE_CFG_STRU;

/*****************************************************************************
     : NVIM_GAS_GSM_SACCH_BA_INHERIT_OPTIMIZE_CFG_STRU
   : en_NV_Item_GAS_GSM_SACCH_BA_INHERIT_OPTIMIZE_CFG , SACCH Ba 
 DESCRIPTION: SACCH Ba 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucInheritBcchFlg;
    VOS_UINT8                           ucInheritLastCellFlg;

    VOS_UINT8                           ucSi5terNotExistJugeTimes;

    VOS_UINT8                           ucRsv1;                             /*  */
    VOS_UINT8                           ucRsv2;
    VOS_UINT8                           ucRsv3;
    VOS_UINT8                           ucRsv4;
    VOS_UINT8                           ucRsv5;
}NVIM_GAS_GSM_SACCH_BA_INHERIT_OPTIMIZE_CFG_STRU;

/*****************************************************************************
     : NVIM_GAS_GSM_PAGE_RCV_CFG_STRU
   : en_NV_Item_GAS_GSM_PAGE_RCV_CFG , 
 DESCRIPTION: 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucRcvPchInPsFlg;            /* . 0:; 1: */
    VOS_UINT8                           ucRcvPchInPsSpecialFlg;     /* . 0:; 1:
                                                                       bit0: I. 
                                                                       bit1:  BSS . 
                                                                       bit2: RAU . 
                                                                       bit3: Attach . 
                                                                       bit4: PDP .  */

    VOS_UINT8                           ucRsv1;                             /*  */
    VOS_UINT8                           ucRsv2;
    VOS_UINT8                           ucRsv3;
    VOS_UINT8                           ucRsv4;
    VOS_UINT8                           ucRsv5;
    VOS_UINT8                           ucRsv6;
}NVIM_GAS_GSM_PAGE_RCV_CFG_STRU;

/*****************************************************************************
     : NVIM_GAS_NET_SRCH_RMV_INTER_RAT_FREQ_CFG_STRU
   : en_NV_Item_GAS_Net_Srch_Rmv_Inter_Rat_Freq_Cfg ,  
 DESCRIPTION:  
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucPreferBandSrchRmvLteFreqSwitch;       /* PREFER BandLTEG0: , 1: 1 */

    VOS_UINT8                           ucPreferBandSrchRmvWcdmaFreqSwitch;     /* PREFER BandWCDMAG0: , 1: 1 */

    VOS_UINT8                           ucPreferBandSrchRmvCdmaFreqSwitch;      /* PREFER BandCDMAG0: , 1: 1 */

    VOS_UINT8                           ucRsv1;                                 /*  */

    VOS_UINT8                           ucRsv2;

    VOS_UINT8                           ucRsv3;

    VOS_UINT16                          usRsv1;

    VOS_UINT16                          usRsv2;

    VOS_UINT16                          usRsv3;

    VOS_UINT32                          ulRsv1;

    VOS_UINT32                          ulRsv2;
}NVIM_GAS_NET_SRCH_RMV_INTER_RAT_FREQ_CFG_STRU;

/*****************************************************************************
     : NVIM_GUAS_CELLULAR_PREFER_PARA_CFG_STRU
   : GUAS Cellular Prefer 
 DESCRIPTION: GUAS Cellular Prefer 
   :
  1.     : 2016922
         : s00184266
     : 

*****************************************************************************/
typedef struct
{
    VOS_INT16                   sHighThresh;            /* dbm */
    VOS_INT16                   sLowThresh;             /* dbm */
    VOS_UINT16                  usOffset;               /* dbm */
    VOS_UINT16                  usRsv;                  /*  */
    VOS_UINT32                  ulTEvaluation;          /* ms */
    VOS_UINT32                  ulRsv;                  /*  */
}NVIM_GUAS_CELLULAR_PREFER_REPORT_PARA_CFG_STRU;

/*****************************************************************************
     : NVIM_GUAS_CELLULAR_PREFER_SELECT_CFG_STRU
   : GUAS Cellular Prefer 
 DESCRIPTION: GUAS Cellular Prefer 
   :
  1.     : 2016922
         : s00184266
     : 

*****************************************************************************/
typedef struct
{
    NVIM_GUAS_CELLULAR_PREFER_REPORT_PARA_CFG_STRU     stGsmCellPreferCfg;      /* g */
    NVIM_GUAS_CELLULAR_PREFER_REPORT_PARA_CFG_STRU     stWcdmaCellPreferCfg;    /* w */
}NVIM_GUAS_CELLULAR_PREFER_PARA_CFG_STRU;

/*****************************************************************************
     : NVIM_GSM_IRAT_ACTIVE_RESEL_CUSTOM_CFG_STRU
   : GSMIRAT
 DESCRIPTION: GSMIRAT
   :
  1.     : 2017417
         : s00184266
     : 

*****************************************************************************/
typedef struct
{
    VOS_UINT8                       ucEnableFlag;                               /*  */
    VOS_UINT8                       ucReserved1;                                /*  */
    VOS_UINT8                       ucReserved2;                                /*  */
    VOS_UINT8                       ucReserved3;                                /*  */
    VOS_INT16                       sGsmRxlevThresh;                            /* GSM scell Rxlev Greatdb */
    VOS_INT16                       sUtranFddRscpThreshOnRanking;               /* GSM GreatRANKINGWCDMA RSCPdb */
    VOS_INT16                       sUtranFddEcNoThreshOnRanking;               /* GSM GreatRANKINGWCDMA EcNodb */
    VOS_INT16                       sUtranFddRscpThreshOnPrio;                  /* GSM GreatPrioWCDMA RSCPdb */
    VOS_INT16                       sUtranFddEcNoThreshOnPrio;                  /* GSM GreatPrioWCDMA EcNodb */
    VOS_UINT16                      usReserved1;                                /*  */
    VOS_UINT16                      usReserved2;                                /*  */
    VOS_UINT16                      usReserved3;                                /*  */
    VOS_UINT16                      usReserved4;                                /*  */
    VOS_UINT16                      usReserved5;                                /*  */
    VOS_UINT16                      usReserved6;                                /*  */
    VOS_UINT16                      usReserved7;                                /*  */
}NVIM_GSM_IRAT_ACTIVE_RESEL_CUSTOM_CFG_STRU;



/*****************************************************************************
     : NVIM_GAS_CSFB_FAIL_LAI_PENALTY_CFG_STRU
   : GAS CSFBLAI 
 DESCRIPTION: GAS CSFBLAI 
   :
  1.     : 20161221
         : h00390293
     : 

*****************************************************************************/
typedef struct
{
    VOS_UINT8                   ucCsfbMoPenaltyFlg;             /* CSFB MO,0: , 1: 0 */                        
    VOS_UINT8                   ucCsfbMtPenaltyFlg;             /* CSFB MT,0: , 1: 0 */
    VOS_UINT16                  usCsfbPenaltyTime;              /* ,:2160 */
    VOS_UINT8                   ucCsfbFailCountForPenalty;      /* CSFB:3 */     
    VOS_UINT8                   ucCsfbDifLaiFailCount;          /* CSFBLAICSFBLAI:3 */      
    VOS_INT16                   sCsfbSameLaiThreshold;          /* CSFBLAIRSSI-90dbm */
    VOS_UINT16                  usCsfbSameLaiTimerLen;          /* CSFBLAI:ms5000ms */    
    VOS_UINT16                  usRsv1;                         /*  */
    VOS_UINT16                  usRsv2;                         /*  */
    VOS_UINT16                  usRsv3;                         /*  */
}NVIM_GAS_CSFB_FAIL_LAI_PENALTY_CFG_STRU;

/* Added by L00349911 for 3G, 2017-2-24, begin */
/*****************************************************************************
     : NVIM_GAS_NETWORK_NOT_ALLOC_UTRAN_PRIORITY_CFG_STRU
   : GSM3GUE 
 DESCRIPTION: GSM3GUE 
   :
  1.     : 20170224
         : L00349911
     : 

*****************************************************************************/
typedef struct
{
    VOS_UINT8                   ucAllocUtranPriFlg;             /* . 0:; 1: */    
    VOS_UINT8                   ucDefaultThreshUtran;           /* NV DEFAULT_THRESH_UTRAN  */   
    VOS_UINT8                   ucDefaultUtranQRxlMin;          /* NV DEFAULT_UTRAN_QRXLEVMIN  */   
    VOS_UINT8                   ucSetUtranPriMinValueFlg;       /* 3G10: 1; 1: 1 */
    VOS_UINT8                   ucRsv1;                         /*  */
    VOS_UINT8                   ucRsv2;                         /*  */
    VOS_UINT16                  usRsv3;                         /*  */
    VOS_UINT16                  usRsv4;                         /*  */
    VOS_UINT16                  usRsv5;                         /*  */
    VOS_UINT32                  ulRsv6;                         /*  */
}NVIM_GAS_NETWORK_NOT_ALLOC_UTRAN_PRIORITY_CFG_STRU;
/* Added by L00349911 for 3G, 2017-2-24, end */

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










#if (VOS_OS_VER != VOS_WIN32)
#pragma pack()
#else
#pragma pack(pop)
#endif





#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of NasNvInterface.h */
