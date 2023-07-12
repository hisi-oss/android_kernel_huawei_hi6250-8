/******************************************************************************

  Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : NasNvInterface.h
  Description     : NasNvInterface.h header file
  History         :

******************************************************************************/

#ifndef __NASNVINTERFACE_H__
#define __NASNVINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

#include "PsTypeDef.h"

/*****************************************************************************
  2 Macro
*****************************************************************************/
#define NAS_MMC_NV_ITEM_ACTIVE          (1)                                     /* NV */
#define NAS_MMC_NV_ITEM_DEACTIVE        (0)                                     /* NV */

/* GPRS GEA  */
#define NAS_MMC_GPRS_GEA1_SUPPORT       (0x01)                                  /* GPRS GEA1 */
#define NAS_MMC_GPRS_GEA1_VALUE         (0x80)                                  /* GEA1 */
#define NAS_MMC_GPRS_GEA2_VALUE         (0x40)                                  /* GEA2 */
#define NAS_MMC_GPRS_GEA3_VALUE         (0x20)                                  /* GEA3 */
#define NAS_MMC_GPRS_GEA4_VALUE         (0x10)                                  /* GEA4 */
#define NAS_MMC_GPRS_GEA5_VALUE         (0x08)                                  /* GEA5 */
#define NAS_MMC_GPRS_GEA6_VALUE         (0x04)                                  /* GEA6 */
#define NAS_MMC_GPRS_GEA7_VALUE         (0x02)                                  /* GEA7 */

#define NAS_MMC_GPRS_GEA2_SUPPORT       (0x02)                                  /* GPRS GEA2 */
#define NAS_MMC_GPRS_GEA3_SUPPORT       (0x04)                                  /* GPRS GEA3 */
#define NAS_MMC_GPRS_GEA4_SUPPORT       (0x08)                                  /* GPRS GEA4 */
#define NAS_MMC_GPRS_GEA5_SUPPORT       (0x10)                                  /* GPRS GEA5 */
#define NAS_MMC_GPRS_GEA6_SUPPORT       (0x20)                                  /* GPRS GEA6 */
#define NAS_MMC_GPRS_GEA7_SUPPORT       (0x40)                                  /* GPRS GEA7 */
#define NAS_MMC_NVIM_MAX_EPLMN_NUM      (16)                                    /* en_NV_Item_EquivalentPlmn NVplmn */
#define NAS_MMC_NVIM_MAX_MCC_SIZE       (3)                                     /* plmnMcc */
#define NAS_MMC_NVIM_MAX_MNC_SIZE       (3)                                     /* plmnMnc */
#define NAS_MMC_LOW_BYTE_MASK           (0x0f)

#define NAS_MMC_A5_1_SUPPORT            (0x0001)                                  /* A5-1 */
#define NAS_MMC_A5_2_SUPPORT            (0x0002)                                  /* A5-2 */
#define NAS_MMC_A5_3_SUPPORT            (0x0004)                                  /* A5-3 */
#define NAS_MMC_A5_4_SUPPORT            (0x0008)                                  /* A5-4 */
#define NAS_MMC_A5_5_SUPPORT            (0x0010)                                  /* A5-5 */
#define NAS_MMC_A5_6_SUPPORT            (0x0020)                                  /* A5-6 */
#define NAS_MMC_A5_7_SUPPORT            (0x0040)                                  /* A5-7 */

#define NAS_MMC_NVIM_MAX_USER_CFG_IMSI_PLMN_NUM                  (6)                 /* USIM/SIM */
#define NAS_MMC_NVIM_MAX_USER_CFG_EHPLMN_NUM                     (6)                 /* EHplmn */
#define NAS_MMC_MAX_BLACK_LOCK_PLMN_WITH_RAT_NUM            (8)                 /* PLMN ID */
#define NAS_MMC_NVIM_MAX_USER_CFG_EXT_EHPLMN_NUM              (8)                /* NVEHplmn*/
#define NAS_MMC_NVIM_MAX_USER_CFG_FORB_PLMN_GROUP_NUM         (8)                /* forb plmn */

#define NAS_MMC_NVIM_MAX_USER_OPLMN_VERSION_LEN               (8)               /* OPLMN */
#define NAS_MMC_NVIM_MAX_USER_OPLMN_IMSI_NUM                  (6)               /* OPLMNUSIM/SIM */
#define NAS_MMC_NVIM_MAX_USER_CFG_OPLMN_NUM                   (256)             /* OPLMN */
#define NAS_MMC_NVIM_OPLMN_WITH_RAT_UNIT_LEN                  (5)               /* OPLMN6F615 */
#define NAS_MMC_NVIM_MAX_USER_CFG_OPLMN_DATA_LEN              (500)             /* OPLMN,500*/
#define NAS_MMC_NVIM_MAX_USER_CFG_OPLMN_DATA_EXTEND_LEN       (1280)            /* OPLMN*/


/* Modified by c00318887 for DPlmnHPLMN, 2015-5-18, begin */
/* :128256; ,67*/
#define NAS_MMC_NVIM_MAX_CFG_DPLMN_DATA_LEN             (7*256)            /* DPLMN */
#define NAS_MMC_NVIM_MAX_CFG_NPLMN_DATA_LEN             (7*256)            /* NPLMN */
/* Modified by c00318887 for DPlmnHPLMN, 2015-5-18, end */

#define NAS_MMC_NVIM_MAX_CFG_DPLMN_DATA_EXTEND_LEN       (6*128)            /* DPLMN*/
#define NAS_MMC_NVIM_MAX_CFG_NPLMN_DATA_EXTEND_LEN       (6*128)            /* NPLMN*/
#define NAS_MMC_NVIM_MAX_CFG_HPLMN_NUM                   (3*8)
#define NAS_MCC_NVIM_VERSION_LEN                         (9)                /* xx.xx.xxx */

#define NAS_MMC_NVIM_MAX_CFG_DPLMN_NUM                   (256)            /* DPLMN */
#define NAS_MMC_NVIM_MAX_CFG_NPLMN_NUM                   (256)            /* NPLMN */
/* Added by s00217060 for PhaseI, 2016-8-9, begin */
/* ,71-3simplmn id
   4-5(0x8000w0x4000lte0x0080gsm)6-7LACTAC
   WG6-7LAC;LTE6-7TAC */
#define NAS_MMC_EVERY_BORDER_INFO_LEN                    (7)              /* en_NV_Item_Ap_Preset_Border_Info nv */
#define NAS_MMC_NVIM_MAX_CFG_BORDER_DATA_LEN             (7*256)          /* AP7256 */
/* Added by s00217060 for PhaseI, 2016-8-9, end */
#define NAS_NVIM_MAX_OPER_SHORT_NAME_LEN                36
#define NAS_NVIM_MAX_OPER_LONG_NAME_LEN                 40

#define NAS_NVIM_ITEM_MAX_IMSI_LEN          (9)                     /* IMSI */
#define NAS_MML_NVIM_PS_LOCI_SIM_FILE_LEN                    (14)                    /* USIMPSLOCI */
#define NAS_NVIM_PS_LOCI_SIM_FILE_LEN                    (14)                    /* USIMPSLOCI */

#define NAS_UTRANCTRL_MAX_NVIM_CFG_TD_MCC_LIST_NUM          (6)                 /*  */
#define NAS_UTRANCTRL_MAX_NVIM_CFG_IMSI_PLMN_LIST_NUM       (6)                 /* USIM/IMSI */

#define NAS_MML_NVIM_MAX_DISABLED_RAT_PLMN_NUM              (8)                 /* PLMN ID */

#define NAS_MML_NVIM_MAX_SKIP_BAND_TYPE_SEARCH_MCC_NUM      (8)

#define NAS_MML_MAX_EXTENDED_FORB_PLMN_NUM                  (32)

#define NAS_MML_NVIM_FRAT_MAX_IMSI_NUM                       (6)                 /* FRATIMSI */
#define NAS_MML_NVIM_FRAT_MAX_PLMN_ID_NUM                    (40)                /* FRATPLMN */

#define NAS_SIM_FORMAT_PLMN_LEN                     (3)                     /* SimPlmn */

#define NAS_MML_NVIM_MAX_BLACK_LOCK_PLMN_NUM                 (16)                    /* PLMN ID */

#define NAS_MML_NVIM_MAX_WHITE_LOCK_PLMN_NUM                 (16)                    /* PLMN ID */

#define NAS_MML_BG_SEARCH_REGARDLESS_MCC_NUMBER         (10)                     /* BG */
#define NAS_MML_SINGLE_DOMAIN_FAIL_ACTION_MAX_LIST      (5)                     /*  */

#define NV_ITEM_NET_CAPABILITY_MAX_SIZE                     (10)

#define NAS_MMC_NVIM_SUPPORTED_3GPP_RELEASE_SIZE            (2)                 /*  */

#define NAS_MMC_NVIM_MAX_IMSI_LEN                           (9)                     /* IMSI */

#define NVIM_MAX_EPLMN_NUM                                  (16)
#define NVIM_MAX_MCC_SIZE                                   (3)
#define NVIM_MAX_MNC_SIZE                                   (3)

#define NVIM_MAX_FDD_FREQ_BANDS_NUM                         (12)

/* Add by z60575 for multi_ssid, 2012-9-5 end */
/*+CGMI - */

#define NAS_NVIM_MAX_IMSI_FORBIDDEN_LIST_NUM         (16)
#define NAS_NVIM_MAX_RAT_FORBIDDEN_LIST_NUM          (8)    /*  */
#define NAS_NVIM_MAX_SUPPORTED_FORBIDDEN_RAT_NUM     (2)

#define NAS_NVIM_FORBIDDEN_RAT_NUM_0                 (0)
#define NAS_NVIM_FORBIDDEN_RAT_NUM_1                 (1)
#define NAS_NVIM_FORBIDDEN_RAT_NUM_2                 (2)


#define NAS_NVIM_MAX_REJECT_NO_RETRY_CAUSE_NUM              (8)

#define NAS_NVIM_MAX_LAU_REJ_TRIG_PLMN_SEARCH_CAUSE_NUM     (12)

/* NVID(PS_NV_ID_ENUM, SYS_NV_ID_ENUM, RF_NV_ID_ENUM) */
typedef VOS_UINT16  NV_ID_ENUM_U16;
#define NV_ITEM_IMEI_SIZE                      16
#define NV_ITEM_MMA_OPERATORNAME_SIZE          84

#define NV_ITEM_OPER_NAME_LONG          (40)
#define NV_ITEM_OPER_NAME_SHORT         (36)
#define NV_ITEM_PLMN_ID_LEN             (8)

#define NV_ITEM_AT_PARA_SIZE                   100
#define NV_ITEM_HPLMN_FIRST_SEARCH_SIZE        1  /* HPLMN */
#define NVIM_ITEM_MAX_IMSI_LEN          (9)                     /* IMSI */

#define CNAS_NVIM_MAX_1X_MRU_SYS_NUM                            (12)

#define NAS_MMC_NVIM_MAX_CAUSE_NUM      (10)     /* NV */

#define CNAS_NVIM_PRL_SIZE                                      (4096) /* PRL NV size: 4K byte */

#define CNAS_NVIM_CBT_PRL_SIZE                                  (48) /* PRL NV size: 45 bytes */

#define CNAS_NVIM_MAX_1X_BANDCLASS_NUM                          (32)

#define CNAS_NVIM_MAX_1X_HOME_SID_NID_NUM                       (20)
#define CNAS_NVIM_MAX_OOC_SCHEDULE_PHASE_NUM                    (8)

#define CNAS_NVIM_MAX_1X_OOC_SCHEDULE_PHASE_NUM                    (8)

#define CNAS_NVIM_MAX_HRPD_MRU_SYS_NUM                           (12)
#define CNAS_NVIM_HRPD_SUBNET_LEN                                (16)

#define CNAS_NVIM_MAX_STORAGE_BLOB_LEN                      ( 255 )

#define NAS_NVIM_BYTES_IN_SUBNET                            (16)
#define NAS_NVIM_MAX_RAT_NUM                                (7)                 /* 1XHRPD */

#define NAS_MSCC_NVIM_MLPL_SIZE                                      (1024) /* PRL NV size: 1K byte */
#define NAS_MSCC_NVIM_MSPL_SIZE                                      (1024) /* PRL NV size: 1K byte */

#define NAS_NV_TRI_MODE_CHAN_PARA_PROFILE_NUM      ( 8 )                       /*   */

#define CNAS_NVIM_ICCID_OCTET_LEN                            (10)
#define CNAS_NVIM_MEID_OCTET_NUM                             (7)
#define CNAS_NVIM_UATI_OCTET_LENGTH                          (16)

#define CNAS_NVIM_MAX_WHITE_LOCK_SYS_NUM                     (20)

#define CNAS_NVIM_MAX_HRPD_CUSTOMIZE_FREQ_NUM                (10)

#define CNAS_NVIM_MAX_CDMA_1X_CUSTOM_PREF_CHANNELS_NUM              (10)
#define CNAS_NVIM_MAX_CDMA_1X_CUSTOMIZE_PREF_CHANNELS_NUM           (20)

/* Added by c00318887 for file refresh, 2015-4-28, begin */
/* PLMN refresh :   */
#define NV_ITEM_HIGH_PRIO_PLMN_REFRESH_TRIGGER_BG_SEARCH_DEFAULT_DELAY_LEN    (5)
/* Added by c00318887 for file refresh, 2015-4-28, end */

#define NAS_NVIM_MAX_PLMN_CSG_ID_NUM             (35)
#define NAS_NVIM_MAX_CSG_REJ_CAUSE_NUM           (10)

#define NAS_NVIM_LTE_OOS_2G_PREF_PLMN_SEL_MAX_IMSI_LIST_NUM      (16)    /* SIM (LTE OOS2G3G) */

#define NAS_MML_NVIM_MAX_REG_FAIL_CAUSE_NUM        (16)        /*LA*/
#define CNAS_NVIM_MAX_AUTHDATA_USERNAME_LEN                      (253)   /* HRPD ppp AN
                                                                            C.S0023-D section 3.4.53
                                                                            C.S0016-D,section 3.5.8.13,
                                                                            255-2(NAI
                                                                            ) */

#define CNAS_NVIM_1X_MAX_MRU_SYS_NUM                   (12)

#define CNAS_NVIM_1X_AVOID_MAX_PHASE_NUM               (8)
#define CNAS_NVIM_1X_AVOID_REASON_MAX                  (20)

#define CNAS_NVIM_MAX_HRPD_OOC_SCHEDULE_PHASE_NUM                    (8)

#define CNAS_NVIM_HRPD_AVOID_MAX_PHASE_NUM               (8)
#define CNAS_NVIM_HRPD_AVOID_REASON_MAX                  (16)

#define CNAS_NVIM_HOME_MCC_MAX_NUM                      (5)

#define NAS_NVIM_MAX_BSR_PHASE_NUM                      (2)

#define NAS_MMC_NVIM_MAX_EXTENDED_FORB_PLMN_NUM         (32)
#define NAS_NVIM_MAX_LIMIT_PDP_ACT_PLMN_NUM             (8)
#define NAS_NVIM_MAX_LIMIT_PDP_ACT_CAUSE_NUM            (8)

#define NAS_MAX_TMSI_LEN                                (4)                     /* TMSI */
#define NAS_SIM_MAX_LAI_LEN                             (6)                     /* SIMLAI */
#define NAS_MMC_NVIM_MAX_CUSTOM_SUPPLEMENT_OPLMN_NUM    (16)

#define CNAS_NVIM_MAX_CDMA_HRPD_CUSTOMIZE_PREF_CHANNELS_NUM           (20)

#define NAS_NVIM_MODE_SELECTION_RETRY_TIMER_PHASE_NUM_MAX             (10)

#define NAS_NVIM_MODE_SELECTION_PUNISH_TIMER_PHASE_NUM_MAX            (10)

#define NAS_NVIM_MODE_SELECTION_RETRY_SYS_ACQ_PHASE_NUM_MAX           (4)

#define NAS_NVIM_CUSTOMIZE_MAX_CL_ACQ_SCENE_NUM                       (40)

#define NAS_NVIM_CHINA_BOUNDARY_NETWORK_NUM_MAX             (30)

#define NAS_NVIM_CHINA_HOME_NETWORK_NUM_MAX                 (5)

#define NAS_NVIM_1X_MT_EST_CNF_REEST_CAUSE_MAX_NUM          (10)
#define NAS_NVIM_1X_MT_TERMINATE_IND_REEST_CAUSE_MAX_NUM    (9)
/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/
/*****************************************************************************
    : NAS_MMC_NVIM_SINGLE_DOMAIN_REG_FAIL_ACTION_ENUM
  : MMC

1.       : 2012611
         : w00166186
     : AT&T&DCM

2.       : 2014819
         : w00167002
     : DTS2014081905808:PS14HOME PLMN
               ACTION:HOME
               

*****************************************************************************/
enum NAS_MMC_NVIM_SINGLE_DOMAIN_REG_FAIL_ACTION_ENUM
{
    NAS_MMC_NVIM_SINGLE_DOMAIN_REG_FAIL_ACTION_PLMN_SELECTION                    = 0,            /*  */
    NAS_MMC_NVIM_SINGLE_DOMAIN_REG_FAIL_ACTION_NORMAL_CAMP_ON                    = 1,            /*  */
    NAS_MMC_NVIM_SINGLE_DOMAIN_REG_FAIL_ACTION_OPTIONAL_PLMN_SELECTION           = 2,            /*  */
    NAS_MMC_NVIM_SINGLE_DOMAIN_REG_FAIL_ACTION_LIMITED_CAMP_ON                   = 3,            /*  */

    NAS_MMC_NVIM_SINGLE_DOMAIN_ROAMING_REG_FAIL_ACTION_PLMN_SELECTION            = 4,            /* HOME */

    NAS_MMC_NVIM_SINGLE_DOMAIN_REG_FAIL_ACTION_BUTT
};
typedef VOS_UINT8 NAS_MMC_NVIM_SINGLE_DOMAIN_REG_FAIL_ACTION_ENUM_UINT8;

/*****************************************************************************
    : NAS_MMC_NVIM_REG_FAIL_CAUSE_ENUM
  : 

1.       : 2012611
         : w00166186
     : AT&T&DCM

*****************************************************************************/
enum NAS_MMC_NVIM_REG_FAIL_CAUSE_ENUM
{
    NAS_MMC_NVIM_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN = 14,
    NAS_MMC_NVIM_REG_FAIL_CAUSE_TIMER_TIMEOUT               = 301,                                 /*  */
    NAS_MMC_NVIM_REG_FAIL_CAUSE_BUTT
};
typedef VOS_UINT16 NAS_MMC_NVIM_REG_FAIL_CAUSE_ENUM_UINT16;

/*****************************************************************************
    : NAS_MMC_NVIM_REG_DOMAIN_ENUM_UINT8
  : 

1.       : 2012611
         : w00166186
     : AT&T&DCM

*****************************************************************************/
enum NAS_MMC_NVIM_REG_DOMAIN_ENUM
{
    NAS_MMC_NVIM_REG_DOMAIN_CS = 1,
    NAS_MMC_NVIM_REG_DOMAIN_PS = 2,                                 /*  */
    NAS_MMC_NVIM_REG_DOMAIN_BUTT
};
typedef VOS_UINT8 NAS_MMC_NVIM_REG_DOMAIN_ENUM_UINT8;

/* Added by w00176964 for UC2NV, 2013-3-11, begin */
/*****************************************************************************
     : NAS_MMC_UCS2_ENUM
   : UCS2 
   :
 1.        : 20130311
           : w00176964
       : 
*****************************************************************************/

enum NAS_MMC_UCS2_ENUM
{
    NAS_MMC_UCS2_HAS_PREFER                                = 0,
    NAS_MMC_UCS2_NO_PREFER                                 = 1,

    NAS_MMC_UCS2_BUTT
};

typedef VOS_UINT16 NAS_MMC_UCS2_ENUM_UINT16;
/* Added by w00176964 for UC2NV, 2013-3-11, end */

/*****************************************************************************
     : NV_MS_MODE_ENUM_UINT8
   :  NV
  1.       : 2011818
           : z00161729
       : 
  2.       : 2012423
           : w00166186
       : DTS2012033104746,ANY
*****************************************************************************/
enum NV_MS_MODE_ENUM
{
    NV_MS_MODE_CS_ONLY,                                                 /* CS */
    NV_MS_MODE_PS_ONLY,                                                 /* PS */
    NV_MS_MODE_CS_PS,                                                   /* CSPS */

    NV_MS_MODE_ANY,                                                     /* ANY,CS */

    NV_MS_MODE_BUTT
};
typedef VOS_UINT8 NV_MS_MODE_ENUM_UINT8;

/*****************************************************************************
     : NAS_NV_LTE_CS_SERVICE_CFG_ENUM_UINT8
   : Lcs
 1.       : 20160216
          : w00167002
      : 
*****************************************************************************/
enum NAS_NV_LTE_CS_SERVICE_CFG_ENUM
{
    NAS_NV_LTE_SUPPORT_CSFB_AND_SMS_OVER_SGS = 1,           /* cs fallbacksms over sgs*/
    NAS_NV_LTE_SUPPORT_SMS_OVER_SGS_ONLY,                   /* sms over sgs only*/
    NAS_NV_LTE_SUPPORT_1XCSFB,                              /* 1XCSFB */
    NAS_NV_LTE_SUPPORT_BUTT
};
typedef VOS_UINT8 NAS_NV_LTE_CS_SERVICE_CFG_ENUM_UINT8;


/*****************************************************************************
     : NAS_NVIM_CHANGE_REG_REJ_CAUSE_TYPE_ENUM
   : 
  1.       : 20131119
           : l00208543
       : 
*****************************************************************************/
enum NAS_NVIM_CHANGE_REG_REJ_CAUSE_TYPE_ENUM
{
    NAS_NVIM_CHANGE_REG_REJ_CAUSE_TYPE_INACTIVE     = 0,        /*  */
    NAS_NVIM_CHANGE_REG_REJ_CAUSE_TYPE_CS_PS,                   /* CS+PS */
    NAS_NVIM_CHANGE_REG_REJ_CAUSE_TYPE_CS_ONLY,                 /* CS */
    NAS_NVIM_CHANGE_REG_REJ_CAUSE_TYPE_PS_ONLY,                 /* PS */
    NAS_NVIM_CHANGE_REG_REJ_CAUSE_TYPE_BUTT
};
typedef VOS_UINT8 NAS_NVIM_CHANGE_REG_REJ_CAUSE_TYPE_ENUM_UINT8;

/*****************************************************************************
     : NAS_NVIM_CHAN_REPEAT_SCAN_ENUM_UINT8
   : 
 1.       : 20150108
          : h00313353
      : 
*****************************************************************************/
enum NAS_NVIM_CHAN_REPEAT_SCAN
{
    NAS_NVIM_CHAN_SCAN_NORMAL,
    NAS_NVIM_CHAN_REPEAT_SCAN_REACQ_0_1_2_3_4S,
    NAS_NVIM_CHAN_REPEAT_SCAN_PING_5,
    NAS_NVIM_CHAN_REPEAT_SCAN_2_7,

    NAS_NVIM_CHAN_REPEAT_SCAN_BUTT
};
typedef VOS_UINT8 NAS_NVIM_CHAN_REPEAT_SCAN_ENUM_UINT8;

/*****************************************************************************
     : NAS_NVIM_EPDSZID_SUPPORT_TYPE_ENUM_UINT8
   : EPDSZID
 1.       : 20150110
          : g00261581
      : 
*****************************************************************************/
enum NAS_NVIM_EPDSZID_SUPPORT_TYPE_ENUM
{
    NAS_NVIM_EPDSZID_SUPPORT_TYPE_PDSZID,
    NAS_NVIM_EPDSZID_SUPPORT_TYPE_PDSZID_SID,
    NAS_NVIM_EPDSZID_SUPPORT_TYPE_PDSZID_SID_NID,

    NAS_NVIM_EPDSZID_SUPPORT_TYPE_BUTT
};
typedef VOS_UINT8 NAS_NVIM_EPDSZID_SUPPORT_TYPE_ENUM_UINT8;


enum NAS_NVIM_LC_RAT_COMBINED_ENUM
{
    NAS_NVIM_LC_RAT_COMBINED_GUL,
    NAS_NVIM_LC_RAT_COMBINED_CL,

    NAS_NVIM_LC_RAT_COMBINED_BUTT
};
typedef VOS_UINT8 NAS_NVIM_LC_RAT_COMBINED_ENUM_UINT8;

/*****************************************************************************
     : CNAS_NVIM_1X_NEG_PREF_SYS_CMP_CTRL_ENUM_UINT8
   : neg perf
 1.       : 201569
          : c00299063
      : 
*****************************************************************************/
enum CNAS_NVIM_1X_NEG_PREF_SYS_CMP_TYPE_ENUM
{
    CNAS_NVIM_1X_NEG_PREF_SYS_CMP_BAND_CHAN_AMBIGUOUS_MATCH,                /* Band Channel  */
    CNAS_NVIM_1X_NEG_PREF_SYS_CMP_BAND_CHAN_ACCURATE_MATCH,                 /* Band Channel */
    CNAS_NVIM_1X_NEG_PREF_SYS_CMP_BUTT
};
typedef VOS_UINT8 CNAS_NVIM_1X_NEG_PREF_SYS_CMP_TYPE_ENUM_UINT8;

/*****************************************************************************
     : NAS_NVIM_CL_SYS_ACQ_DSDS_STRATEGY_SCENE_ENUM
   : CLdsds
 1.       : 20160202
          : w00176964
      : DTS2016013006596
 2.       : 20160615
          : w00176964
      : DTS2016060709509
*****************************************************************************/
enum NAS_NVIM_CL_SYS_ACQ_DSDS_STRATEGY_SCENE_ENUM
{
    NAS_NVIM_CL_SYS_ACQ_DSDS_STRATEGY_SCENE_SWITCH_ON                 = 0,        /*  */

    NAS_NVIM_CL_SYS_ACQ_DSDS_STRATEGY_SCENE_SWITCH_ON_AND_SYSCFG_SET  = 0x1,      /* syscfg */

    NAS_NVIM_CL_SYS_ACQ_DSDS_STRATEGY_SCENE_ANY                       = 0xFE,     /* CL */

    NAS_NVIM_CL_SYS_ACQ_DSDS_STRATEGY_SCENE_ENUM_BUTT
};
typedef VOS_UINT8 NAS_NVIM_CL_SYS_ACQ_DSDS_STRATEGY_SCENE_ENUM_UINT8;


/*****************************************************************************
     : NAS_MSCC_NVIM_SYS_ACQ_SCENE_ENUM
   : 
 1.       : 20160922
          : m00312079
      : 
*****************************************************************************/
enum NAS_MSCC_NVIM_SYS_ACQ_SCENE_ENUM
{
    NAS_MSCC_NVIM_SYS_ACQ_SCENE_SWITCH_ON                                        = 0,       /*  */

    NAS_MSCC_NVIM_SYS_ACQ_SCENE_HRPD_LOST,                                                  /* hrpd  */

    NAS_MSCC_NVIM_SYS_ACQ_SCENE_HRPD_LOST_NO_RF,                                            /* hrpd no rf */

    NAS_MSCC_NVIM_SYS_ACQ_SCENE_SLEEP_TIMER_EXPIRED,                                        /* sleep  */

    NAS_MSCC_NVIM_SYS_ACQ_SCENE_SYS_CFG_SET,                                                /* system configure */

    NAS_MSCC_NVIM_SYS_ACQ_SCENE_LTE_RF_AVAILABLE,                                           /* LTE RF */

    NAS_MSCC_NVIM_SYS_ACQ_SCENE_HRPD_RF_AVAILABLE,                                          /* HRPD RF */

    NAS_MSCC_NVIM_SYS_ACQ_SCENE_MO_TRIGGER,                                                 /*  */

    NAS_MSCC_NVIM_SYS_ACQ_SCENE_AVAILABLE_TIMER_EXPIRED_1XSRVEXIST_HISTORY,                 /* 1xavailable */
    NAS_MSCC_NVIM_SYS_ACQ_SCENE_AVAILABLE_TIMER_EXPIRED_1XSRVEXIST_PREFBAND,                /* 1xavailablepref band */
    NAS_MSCC_NVIM_SYS_ACQ_SCENE_AVAILABLE_TIMER_EXPIRED_1XSRVEXIST_FULLBAND,                /* 1xavailablefull band */

    NAS_MSCC_NVIM_SYS_ACQ_BSR,                                                              /*  */

    NAS_MSCC_NVIM_SYS_ACQ_SCENE_BUTT
};
typedef VOS_UINT32 NAS_MSCC_NVIM_SYS_ACQ_SCENE_ENUM_UINT32;
/*****************************************************************************
  5 STRUCT
*****************************************************************************/
/*****************************************************************************
*                                                                            *
*                                                            *
*                                                                            *
******************************************************************************/
/*****************************************************************************
     : NAS_MMC_NVIM_MANUAL_SEARCH_HPLMN_FLG_STRU
   : NV SrchHplmnFlg_ManualMode

 1.       : 2013517
          : l00167671
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usManualSearchHplmnFlg; /*Range:[0,1]*/
}NAS_MMC_NVIM_MANUAL_SEARCH_HPLMN_FLG_STRU;
/*****************************************************************************
     : NAS_MMC_NVIM_AUTO_SEARCH_HPLMN_FLG_STRU
   : NV SrchHplmnFlg_ManualMode

 1.       : 2013517
          : l00167671
      : 
*****************************************************************************/

typedef struct
{
    VOS_UINT16                          usAutoSearchHplmnFlg; /*Range:[0,3]*/
}NAS_MMC_NVIM_AUTO_SEARCH_HPLMN_FLG_STRU;

/*****************************************************************************
     : NAS_NVIM_ADD_EHPLMN_WHEN_SRCH_HPLMN_CFG_STRU
   : NV en_NV_Item_Add_EHPLMN_WHEN_SRCH_HPLMN_CFG 

  1.       : 2015930
           : c00318887
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucActiveFlag;       /* ucActiveFlag VOS_TRUE:VOS_FALSE: */
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
    VOS_UINT8                           ucReserve3;
}NAS_NVIM_ADD_EHPLMN_WHEN_SRCH_HPLMN_CFG_STRU;

/*****************************************************************************
     : NAS_MMC_NVIM_AUTO_SEARCH_HPLMN_FLG_STRU
   : NV SrchHplmnFlg_AutoMode

 1.       : 2013517
          : l00167671
      : 
 2.       : 201532
          : w00316404
      : reserve
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usEHPlmnSupportFlg; /*Range:[0,1]*/
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}NAS_MMC_NVIM_EHPLMN_SUPPORT_FLG_STRU;

/*****************************************************************************
     : NAS_MMC_NVIM_STK_STEERING_OF_ROAMING_SUPPORT_FLG_STRU
   : en_NV_Item_Standard_STK_SteeringOfRoaming_Support_Flg

 1.       : 2013517
          : l00167671
      : 
 2.       : 201532
          : w00316404
      : reserve
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usStkSteeringOfRoamingSupportFlg; /*Range:[0,1]*/
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}NAS_MMC_NVIM_STK_STEERING_OF_ROAMING_SUPPORT_FLG_STRU;

/*****************************************************************************
     : NVIM_SCAN_CTRL_STRU
   : en_NV_Item_Scan_Ctrl_Para (9080)NV
  1.       : 20120611
           : l60609
       : 
  2.       : 201532
           : w00316404
       : reserve
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNvimActiveFlg;                        /* en_NV_Item_Scan_Ctrl_Para NVVOS_TRUE:VOS_FALSE: */
    VOS_UINT8                           ucReserved1;                            /*  */
    VOS_UINT8                           ucReserved2;                            /*  */
    VOS_UINT8                           ucReserved3;                            /*  */
}NVIM_SCAN_CTRL_STRU;

/*****************************************************************************
     : NAS_NVIM_PLMN_ID_STRU
   : PLMN

 1.       : 2013517
          : l00167671
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulMcc;                                  /* MCC,3 bytes */
    VOS_UINT32                          ulMnc;                                  /* MNC,2 or 3 bytes */
}NAS_NVIM_PLMN_ID_STRU;

/*****************************************************************************
     : NAS_NVIM_PLMN_ID_STRU
   : en_NV_Item_Network_Name_From_MM_Info

 1.       : 2013517
          : l00167671
      : 
*****************************************************************************/
typedef struct
{
    NAS_NVIM_PLMN_ID_STRU               stOperatorPlmnId;
    VOS_UINT8                           aucOperatorNameShort[NAS_NVIM_MAX_OPER_SHORT_NAME_LEN];/*  */
    VOS_UINT8                           aucOperatorNameLong[NAS_NVIM_MAX_OPER_LONG_NAME_LEN];  /*  */
}NAS_MMC_NVIM_OPERATOR_NAME_INFO_STRU;

/*****************************************************************************
     : NAS_NVIM_POWER_ON_READ_USIM_OPTIMIZE_INFO_STRU
   : en_NV_Item_Power_On_Read_Usim_Optimize_Cfg

 1.       : 2016813
          : w00167002
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNotReadFileEnableFlg;                  /*  */
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
}NAS_NVIM_POWER_ON_READ_USIM_OPTIMIZE_INFO_STRU;


/*****************************************************************************
     : NAS_MMC_NVIM_OPER_LOCK_BLACKPLMN_STRU
   : en_NV_Item_OPERLOCK_PLMN_INFO NV
  1.       : 2011725
           : z00161729
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulBlackPlmnLockNum;                     /* ,0 */
    NAS_NVIM_PLMN_ID_STRU               astBlackPlmnId[NAS_MML_NVIM_MAX_BLACK_LOCK_PLMN_NUM];
}NAS_MMC_NVIM_OPER_LOCK_BLACKPLMN_STRU;
/*****************************************************************************
     : NAS_MMC_AIS_ROAMING_CFG_STRU
   : en_NV_Item_AIS_ROAMING_Config NV
 1.       : 2012517
          : z40661
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEnableFlg;                            /*  */
    VOS_UINT8                           ucHighPrioRatType;                              /*  */
    VOS_UINT8                           aucReserve[2];
    NAS_NVIM_PLMN_ID_STRU               stHighPrioPlmnId;                       /* PLMN ID ,HPLMN,PLMNID*/
    NAS_NVIM_PLMN_ID_STRU               stSimHPlmnId;                           /* SIMHPLMN ID */
}NAS_MMC_NVIM_AIS_ROAMING_CFG_STRU;

/*****************************************************************************
     : NAS_MML_USER_AUTO_RESEL_CFG_STRU
   : en_NV_Item_User_Auto_Resel_Switch NV,UserResecl
 1.       : 2012515
          : l00130025
      : DTS2012012903053:Ts23.122 ch4.4.3.2.1 Auto user reselecton
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucAutoReselActiveFlg;                   /* LTE:VOS_TRUE LTE VOS_FALSE LTE */
    VOS_UINT8                           ucReserve;
}NAS_MMC_NVIM_USER_AUTO_RESEL_CFG_STRU;

/*****************************************************************************
     : NAS_MMC_NVIM_PRIO_HPLMNACT_CFG_STRU
   :  en_NV_Item_PRIO_HPLMNACT_CFG NV
 1.       : 201269
          : l00130025
      : DTS2012060400029:HPLMNActUSimHPLMNACTL
*****************************************************************************/
typedef struct
{
    VOS_UINT8                            ucStatus;        /* NV, 1: 0 */
	VOS_UINT8                            ucReserved;      /*  */
    VOS_UINT16                           usPrioHplmnAct;      /**/
}NAS_MMC_NVIM_PRIO_HPLMNACT_CFG_STRU;

/*****************************************************************************
     : NAS_MML_NVIM_AVAIL_TIMER_CFG_STRU
   : en_NV_Item_SEARCH_TIMER_INFO NV
  1.       : 2013522
           : l00167671
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulFirstSearchTimeLen;                   /* available timer */
    VOS_UINT32                          ulFirstSearchTimeCount;                 /* available timer */
    VOS_UINT32                          ulDeepSearchTimeLen;                    /* available timer */
    VOS_UINT32                          ulDeepSearchTimeCount;
}NAS_MMC_NVIM_AVAIL_TIMER_CFG_STRU;


/*****************************************************************************
     : NAS_MMC_NVIM_T3212_TIMER_CFG_STRU
   : en_NV_Item_SEARCH_TIMER_INFO NV
  1.       : 2015314
           : w00167002
       : 

    BIT0: LAUUT3212
    ulT3212StartSceanCtrlBitMask1 BIT0:             NAS_MM_T3212_START_SCENE_LAU_RRC_EST_CONN_FAIL
    BIT1: LAURELT3212
    ulT3212StartSceanCtrlBitMask1 BIT1:             NAS_MM_T3212_START_SCENE_LAU_RRC_EST_REL_BY_AS

*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulNvActiveFlg;                          /* NV */
    VOS_UINT32                          ulT3212StartSceneCtrlBitMask;           /* BIT0~BIT31,T3212NV */
    VOS_UINT32                          ulT3212Phase1TimeLen;                   /* t32121,s */
    VOS_UINT32                          ulT3212Phase1Count;                     /* t32121 */
    VOS_UINT32                          ulT3212Phase2TimeLen;                   /* t32122,s  */
    VOS_UINT32                          ulT3212Phase2Count;                     /* t32122 */
}NAS_MMC_NVIM_T3212_TIMER_CFG_STRU;

/*****************************************************************************
     : NAS_MMC_NVIM_OPER_LOCK_WHITEPLMN_STRU
   : en_NV_Item_OPERLOCK_PLMN_INFO_WHITE NV
  1.       : 2011725
           : z00161729
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulWhitePlmnLockNum;                     /* ,0 */
    NAS_NVIM_PLMN_ID_STRU               astWhitePlmnId[NAS_MML_NVIM_MAX_WHITE_LOCK_PLMN_NUM];
}NAS_MMC_NVIM_OPER_LOCK_WHITEPLMN_STRU;

/*****************************************************************************
     : NAS_MMC_NVIM_CPHS_SUPPORT_FLG_STRU
   : en_NV_Item_SUPPORT_CPHS_FLAG NV
  1.       : 2013522
           : l00167671
       : 
  2.       : 201532
           : w00316404
       : reserve
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usSupportFlg; /*Range:[0,1]*/
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}NAS_MMC_NVIM_CPHS_SUPPORT_FLG_STRU;

/* Added by l60609 for B060 Project, 2012-2-20, Begin   */
/*****************************************************************************
     : NAS_PREVENT_TEST_IMSI_REG_STRU
   : en_NV_Item_PREVENT_TEST_IMSI_REG
  1.       : 2012222
           : w00199382
       : 
  2.       : 201532
           : w00316404
       : reserve
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucStatus;                               /*01 */
    VOS_UINT8                           ucActFlg;
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}NAS_PREVENT_TEST_IMSI_REG_STRU;
/* Added by l60609 for B060 Project, 2012-2-20, End   */
/*****************************************************************************
*                                                                            *
*                                                            *
*                                                                            *
******************************************************************************/

/*****************************************************************************
     : NAS_PREVENT_TEST_IMSI_REG_STRU
   : en_NV_Item_PREVENT_TEST_IMSI_REG
  1.       : 2012222
           : w00199382
       : 
  2.       : 201532
           : w00316404
       : reserve
*****************************************************************************/
typedef struct
{
    VOS_UINT8   ucHplmnSearchPowerOn;
    VOS_UINT8   ucReserve1;
    VOS_UINT8   ucReserve2;
    VOS_UINT8   ucReserve3;
}NAS_MMC_NVIM_HPLMN_SEARCH_POWERON_STRU;


/*****************************************************************************
     : NAS_PREVENT_TEST_IMSI_REG_STRU
   : NAS_PREVENT_TEST_IMSI_REG_STRU
  1.       : 2013522
           : l00167671
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucTinType;                              /* TIN */
    VOS_UINT8                           aucReserve[2];
    VOS_UINT8                           aucImsi[NAS_NVIM_ITEM_MAX_IMSI_LEN];        /* IMSI */
}NAS_NVIM_TIN_INFO_STRU;

/*****************************************************************************
     : NAS_PREVENT_TEST_IMSI_REG_STRU
   : NAS_PREVENT_TEST_IMSI_REG_STRU
  1.       : 2013522
           : l00167671
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT32 ulAutoStart;
}NAS_MMA_NVIM_AUTO_START_STRU;


/*****************************************************************************
     : NAS_MMC_NVIM_SINGLE_DOMAIN_FAIL_CNT_STRU
   : en_NV_Item_SINGLE_DOMAIN_FAIL_SRCH_PLMN_CNT NV
  1.       : 201185
           : z00161729
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucSingleDomainFailPlmnSrchFlag;         /* DT */
    VOS_UINT8                           ucReserved;                             /* */
}NAS_MMC_NVIM_SINGLE_DOMAIN_FAIL_CNT_STRU;

/*****************************************************************************
     : NAS_PREVENT_TEST_IMSI_REG_STRU
   : NAS_PREVENT_TEST_IMSI_REG_STRU
  1.       : 2013522
           : l00167671
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucPsLocInfo[NAS_NVIM_PS_LOCI_SIM_FILE_LEN];
}NAS_NVIM_PS_LOCI_SIM_FILES_STRU;

/*****************************************************************************
     : NAS_NVIM_CS_LOCI_SIM_FILES_STRU
   : en_NV_Item_Cs_Loci  NV
  1.       : 2016410
           : j00174725
       : DTS2016040901340
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucTmsi[NAS_MAX_TMSI_LEN];
    VOS_UINT8                           aucLastLai[NAS_SIM_MAX_LAI_LEN];
    VOS_UINT8                           ucLauStaus;
    VOS_UINT8                           ucReserved;
}NAS_NVIM_CS_LOCI_SIM_FILES_STRU;

/*****************************************************************************
     : NAS_MML_NVIM_GPRS_GEA_ALG_CTRL_STRU
   : en_NV_Item_GEA_SUPPORT_CTRL NV
 1.       : 2011714
          : z00161729
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                          ucStatus;                                /* NV, 0: 1:  */
    VOS_UINT8                          ucGeaSupportCtrl;                        /* :GPRS GEA */
}NAS_MMC_NVIM_GPRS_GEA_ALG_CTRL_STRU;

/*****************************************************************************
     : NAS_NVIM_LTE_CS_SERVICE_CFG_STRU
   : en_NV_Item_Lte_Cs_Service_Config NVLTEcs
  1.       : 20111028
           : z00161729
       : 
  2.       : 20130924
           : s00217060
       : VoLTE_PhaseII
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNvimActiveFlg;    /* en_NV_Item_Lte_Cs_Service_Config NVVOS_TRUE:VOS_FALSE: */
    VOS_UINT8                           ucLteCsServiceCfg;  /* LTE cs*/
}NAS_NVIM_LTE_CS_SERVICE_CFG_STRU;

/*****************************************************************************
     : NAS_MMC_NVIM_HO_WAIT_SYSINFO_TIMER_CFG_STRU
   : NVIMCSFB HONV
 1.       : 2012214
          : z00161729
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNvimActiveFlg;
    VOS_UINT8                           ucWaitSysinfoTimeLen;
}NAS_MMC_NVIM_HO_WAIT_SYSINFO_TIMER_CFG_STRU;



/*****************************************************************************
     : NAS_MMC_NVIM_LTE_INTERNATIONAL_ROAM_CFG_STRU
   : en_NV_Item_Lte_Internation_Roam_Config NV
 1.       : 2012314
          : w00176964
      : 
 2.       : 2012425
          : w00176964
      : DTS2012042403564:NV
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucLteRoamAllowedFlg;
    VOS_UINT8                           aucReserve[1];
    VOS_UINT8                           aucRoamEnabledMccList[20];/*  */
}NAS_MMC_NVIM_LTE_INTERNATIONAL_ROAM_CFG_STRU;

/*****************************************************************************
     : NAS_MMC_NVIM_ROAM_RPLMN_SEARCH_CFG_STRU
   : en_NV_Item_Roam_Search_Rplmn_Config NV
 1.       : 2014224
          : t00173447
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucRoamRplmnflg;
    VOS_UINT8                           aucReserve[3];
    VOS_UINT32                         aucRoamEnabledMccList[5];/*  */
}NAS_MMC_NVIM_ROAM_SEARCH_RPLMN_CFG_STRU;

/* Modified by w00176964 for UC2NV, 2013-3-11, begin */
/*****************************************************************************
     : NAS_MMC_NVIM_CLOSE_SMS_CAPABILITY_CFG_STRU
   : en_NV_Item_Close_SMS_Capability_Config NV
 1.       : 2013311
          : w00176964
      : close sms capability NV
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucActFlg;
    VOS_UINT8                           aucReserved[3];
}NAS_NVIM_CLOSE_SMS_CAPABILITY_CFG_STRU;
/* Modified by w00176964 for UC2NV, 2013-3-11, end */

/*****************************************************************************
     : NAS_MMC_NVIM_WCDMA_PRIORITY_GSM_STRU
   : en_NV_Item_NVIM_WCDMA_PRIORITY_GSM_SUPPORT_FLG NV
  1.       : 20120303
           : S62952
       : 
  2.       : 20131213
           : z00161729
       : DTS2013121206933:syscfg9055 nv
  3.       : 201532
           : w00316404
       : reserve
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucWcdmaPriorityGsmFlg;                  /* H3GWG*/

    VOS_UINT8                           ucSortAvailalePlmnListRatPrioFlg;    /* syscfg1:; 0:*/
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}NAS_MMC_NVIM_WCDMA_PRIORITY_GSM_FLG_STRU;

/*****************************************************************************
     : NAS_MMC_NVIM_PS_ONLY_CS_SERVICE_SUPPORT_FLG_STRU
   : en_NV_Item_NVIM_PS_ONLY_CS_SERVICE_SUPPORT_FLG NV
  1.       : 20120303
           : S62952
       : 
  2.       : 201532
           : w00316404
       : reserve
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucPsOnlyCsServiceSupportFlg;            /* PS ONLYCS()*/
    VOS_UINT8                           ucReserved1;                            /* */
    VOS_UINT8                           ucReserved2;                            /* */
    VOS_UINT8                           ucReserved3;                            /* */
}NAS_NVIM_PS_ONLY_CS_SERVICE_SUPPORT_FLG_STRU;

/*****************************************************************************
     : NAS_CC_NVIM_CCBS_SUPPORT_FLG_STRU
   : en_NV_Item_NVIM_CCBS_SUPPORT_FLG NV
  1.       : 20120303
           : S62952
       : 
  2.       : 201532
           : w00316404
       : reserve
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCcbsSupportFlg;                       /* CCBS()*/
    VOS_UINT8                           ucReserved1;                            /* */
    VOS_UINT8                           ucReserved2;                            /* */
    VOS_UINT8                           ucReserved3;                            /* */
}NAS_NVIM_CCBS_SUPPORT_FLG_STRU;

/*****************************************************************************
     : NAS_MMC_NVIM_HPLMN_SEARCH_REGARDLESS_MCC_SUPPORT_STRU
   : en_NV_Item_HPLMN_SEARCH_REGARDLESS_MCC_SUPPORT NV
 1.       : 2012611
          : W00166186
      : AT&T&t&DCM
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNvimActiveFlg;
    VOS_UINT8                           ucCustomMccNum;
    VOS_UINT8                           aucReserve[2];
    VOS_UINT32                          aulCustommMccList[10];                   /*  */
}NAS_MMC_NVIM_HPLMN_SEARCH_REGARDLESS_MCC_SUPPORT_STRU;


/*****************************************************************************
     : NVIM_ACTING_HPLMN_SUPPORT_FLAG_STRU
   : en_NV_Item_ACTING_PLMN_SUPPORT_FLAG NV
  1.       : 20110611
           : W00166186
       : AT&T&DCM
  2.       : 201532
           : w00316404
       : reserve
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNvimActiveFlg;
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
}NVIM_ACTING_HPLMN_SUPPORT_FLAG_STRU;

/*****************************************************************************
     : NAS_MMC_NVIM_REG_FAIL_NETWORK_FAILURE_CUSTOM_FLG_STRU
   : en_NV_Item_CS_FAIL_NETWORK_FAILURE_PLMN_SEARCH_FLAG NV
  1.       : 20110611
           : W00166186
       : AT&T&DCM
  2.       : 201532
           : w00316404
       : reserve
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNvimActiveFlg;
    VOS_UINT8                           ucReserved1;                            /* */
    VOS_UINT8                           ucReserved2;                            /* */
    VOS_UINT8                           ucReserved3;                            /* */
}NAS_MMC_NVIM_REG_FAIL_NETWORK_FAILURE_CUSTOM_FLG_STRU;



/*****************************************************************************
     : NAS_MMC_NVIM_SINGLE_DOMAIN_FAIL_ACTION_LIST_STRU
   : 
 1.       : 2012611
          : W00166186
      : AT&T&t&DCM
*****************************************************************************/
typedef struct
{
    NAS_MMC_NVIM_REG_FAIL_CAUSE_ENUM_UINT16                 enRegCause;
    NAS_MMC_NVIM_REG_DOMAIN_ENUM_UINT8                      enDomain;
    NAS_MMC_NVIM_SINGLE_DOMAIN_REG_FAIL_ACTION_ENUM_UINT8   enAction;
}NAS_MMC_NVIM_SINGLE_DOMAIN_REG_FAIL_ACTION_STRU;


/*****************************************************************************
     : NAS_MMC_NVIM_SINGLE_DOMAIN_FAIL_ACTION_LIST_STRU
   : en_NV_Item_SINGLE_DOMAIN_FAIL_ACTION_LIST
 1.       : 2012611
          : W00166186
      : AT&T&t&DCM
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucActiveFlag;
    VOS_UINT8                                               ucCount;
    VOS_UINT8                                               auReserv[2];
    NAS_MMC_NVIM_SINGLE_DOMAIN_REG_FAIL_ACTION_STRU         astSingleDomainFailActionList[NAS_MML_SINGLE_DOMAIN_FAIL_ACTION_MAX_LIST];
}NAS_MMC_NVIM_SINGLE_DOMAIN_FAIL_ACTION_LIST_STRU;

/*****************************************************************************
     : NAS_SIM_FORMAT_PLMN_ID
   : Sim PLMN ID
 1.       : 2011528
          : zhoujun 40661
      : 
*****************************************************************************/
typedef struct {
    VOS_UINT8                           aucSimPlmn[NAS_SIM_FORMAT_PLMN_LEN];
    VOS_UINT8                           aucReserve[1];
}NAS_SIM_FORMAT_PLMN_ID;

/*****************************************************************************
     : NAS_UTRANCTRL_NVIM_CURRENT_UTRAN_MODE_STRU
   : en_NV_Item_Utran_Mode NV
 1.       : 2012713
          : w00167002
      : V7R1C50_GUTL_PhaseI:
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucUtranMode;                            /* UTRAN */
    VOS_UINT8                           ucReserve;
}NAS_UTRANCTRL_NVIM_UTRAN_MODE_STRU;

/*****************************************************************************
     : NAS_UTRANCTRL_NVIM_UTRAN_MODE_AUTO_SWITCH_STRU
   : en_NV_Item_Utran_Mode_Auto_Switch NV
 1.       : 201287
          : w00167002
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucUtranSwitchMode;                      /* 0UTRANFDD 1UTRANTDD 2:AUTO SWITCH */
    VOS_UINT8                           ucTdMccListNum;                         /* TD */
    VOS_UINT8                           ucImsiPlmnListNum;                      /* IMS PLMNUTRANAUTO SWITCHIMSIPLMNW */
    VOS_UINT8                           aucReserve[1];

    VOS_UINT32                          aulTdMccList[NAS_UTRANCTRL_MAX_NVIM_CFG_TD_MCC_LIST_NUM];
    NAS_SIM_FORMAT_PLMN_ID              astImsiPlmnList[NAS_UTRANCTRL_MAX_NVIM_CFG_IMSI_PLMN_LIST_NUM];
}NAS_UTRANCTRL_NVIM_UTRAN_MODE_AUTO_SWITCH_STRU;




/*****************************************************************************
     : NAS_UTRANCTRL_NVIM_SMC_CTRL_FLAG_STRU
   : en_NV_Item_UTRAN_TDD_SMC_FLAG NV
 1.       : 2013725
          : w00167002
      : 3G TDDSMC:
                TDSMC
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucIsUtranTddCsSmcNeeded;                /* 3G TDDCS SMC:0-1- */
    VOS_UINT8                           ucIsUtranTddPsSmcNeeded;                /* 3G TDDPS SMC:0-1- */
    VOS_UINT8                           aucReserved[2];                         /*  */
}NAS_UTRANCTRL_NVIM_SMC_CTRL_FLAG_STRU;


/*****************************************************************************
     : NAS_MMC_NVIM_ACC_BAR_PLMN_SEARCH_FLG_STRU
   : NAS_MMC_NVIM_ACC_BAR_PLMN_SEARCH_FLG_STRUHPLMN/RPLMN
             PLMN en_NV_Item_ACC_BAR_PLMN_SEARCH_FLG
 1.       : 20131015
          : s00190137
*****************************************************************************/
typedef struct
{
    VOS_UINT8   ucAccBarPlmnSearchFlg;
    VOS_UINT8   aucReserve[3];
}NAS_MMC_NVIM_ACC_BAR_PLMN_SEARCH_FLG_STRU;


/*****************************************************************************
     : NAS_MMC_NVIM_USER_CFG_OPLMN_INFO_STRU
   : NAS_MMC_NVIM_USER_CFG_OPLMN_INFO_STRU NVIMOPLMN
 1.       : 20131015
          : s00190137
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucActiveFlg;                                          /*  */
    VOS_UINT8                           ucImsiCheckFlg;                                       /* IMSI0: 1: */
    VOS_UINT8                           aucVersion[NAS_MMC_NVIM_MAX_USER_OPLMN_VERSION_LEN];  /*  */
    VOS_UINT8                           ucImsiPlmnListNum;                                    /* IMSI */
    VOS_UINT8                           ucOplmnListNum;                                       /* Oplmn */
    NAS_SIM_FORMAT_PLMN_ID              astImsiPlmnList[NAS_MMC_NVIM_MAX_USER_OPLMN_IMSI_NUM];
    VOS_UINT8                           aucOPlmnList[NAS_MMC_NVIM_MAX_USER_CFG_OPLMN_DATA_LEN];/* OPLMNPDUEFOplmn */
}NAS_MMC_NVIM_USER_CFG_OPLMN_INFO_STRU;

/*****************************************************************************
     : NAS_MMC_NVIM_USER_CFG_OPLMN_EXTEND_STRU
   : NAS_MMC_NVIM_USER_CFG_OPLMN_EXTEND_STRU NVIMOPLMN
 1.       : 20131126
      : NVOPLMN256
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucActiveFlg;                                          /*  */
    VOS_UINT8                           ucImsiCheckFlg;                                       /* IMSI0: 1: */
    VOS_UINT8                           aucVersion[NAS_MMC_NVIM_MAX_USER_OPLMN_VERSION_LEN];  /*  */
    VOS_UINT16                          usOplmnListNum;                                       /* Oplmn */
    VOS_UINT8                           ucImsiPlmnListNum;                                    /* IMSI */
    VOS_UINT8                           aucReserve[3];
    NAS_SIM_FORMAT_PLMN_ID              astImsiPlmnList[NAS_MMC_NVIM_MAX_USER_OPLMN_IMSI_NUM];
    VOS_UINT8                           aucOPlmnList[NAS_MMC_NVIM_MAX_USER_CFG_OPLMN_DATA_EXTEND_LEN];/* OPLMNPDUEFOplmn */
}NAS_MMC_NVIM_USER_CFG_OPLMN_EXTEND_STRU;


/*****************************************************************************
     : NAS_MMC_NVIM_CFG_DPLMN_NPLMN_INFO_STRU
   : en_NV_Item_First_Preset_Dplmn_Nplmn_Cfg NVIM
            en_NV_Item_Second_Preset_Dplmn_Nplmn_Cfg
            en_NV_Item_Self_Learn_Dplmn_Nplmn_Cfg
            DPLMN NPLMN
 1.       : 2015528
          : c00318887
      : DPlmnHPLMN
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEnableFlg;                                                    /* NV */
    VOS_UINT8                           ucExtendedForbPlmnNum;                                          /* Forb Plmn */
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
    NAS_NVIM_PLMN_ID_STRU               astForbPlmnIdList[NAS_MMC_NVIM_MAX_EXTENDED_FORB_PLMN_NUM];     /* Forb Plmn */
}NAS_MMC_NVIM_EXTENDED_FORBIDDEN_PLMN_LIST_CFG_STRU;

/* Added by c00318887 for DPlmnHPLMN, 2015-5-28, begin */
/*****************************************************************************
     : NAS_MMC_NVIM_CFG_DPLMN_NPLMN_INFO_STRU
   : en_NV_Item_First_Preset_Dplmn_Nplmn_Cfg NVIM
            en_NV_Item_Second_Preset_Dplmn_Nplmn_Cfg
            en_NV_Item_Self_Learn_Dplmn_Nplmn_Cfg
            DPLMN NPLMN
 1.       : 2015528
          : c00318887
      : DPlmnHPLMN
*****************************************************************************/
typedef struct
{
    VOS_UINT16                         usDplmnListNum;                                       /* Dplmn */
    VOS_UINT16                         usNplmnListNum;                                       /* Nplmn */

    /* DPLMN,7dplmn1-3simplmn id
       4-5(0x8000w0x4000lte0x0080gsm)
       6:1(cs)2(ps)3(cs ps)
       7: 1(Dplmn), 0(DPLMN) */
    VOS_UINT8                          aucDPlmnList[NAS_MMC_NVIM_MAX_CFG_DPLMN_DATA_LEN];

    /* NPLMN,7nplmn1-3simplmn id
       4-5(0x8000w0x4000lte0x0080gsm)
       6:1(cs)2(ps)3(cs ps)
       7: 1(nplmn), 0(nplmn) */
    VOS_UINT8                          aucNPlmnList[NAS_MMC_NVIM_MAX_CFG_NPLMN_DATA_LEN];/* NPLMN*/
}NAS_MMC_NVIM_CFG_DPLMN_NPLMN_INFO_STRU;

/*****************************************************************************
     : NAS_MMC_NVIM_CFG_DPLMN_NPLMN_INFO_STRU
   : en_NV_Item_CMCC_Cfg_Dplmn_Nplmn NVIM
            en_NV_Item_UNICOM_Cfg_Dplmn_Nplmn
            en_NV_Item_CT_Cfg_Dplmn_Nplmn
            DPLMN NPLMN
 1.       : 2014714
          : c00188733
      : DPLMN NPLMN
 2.       : 2014113
          : z00161729
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT16                         usDplmnListNum;                                       /* Dplmn */
    VOS_UINT16                         usNplmnListNum;                                       /* Nplmn */

    /* DPLMN,6dplmn1-3simplmn id
       4-5(0x8000w0x4000lte0x0080gsm)6:1(cs)2(ps)3(cs ps)*/
    VOS_UINT8                          aucDPlmnList[NAS_MMC_NVIM_MAX_CFG_DPLMN_DATA_EXTEND_LEN];

    /* NPLMN,6nplmn1-3simplmn id
       4-5(0x8000w0x4000lte0x0080gsm)6:1(cs)2(ps)3(cs ps)*/
    VOS_UINT8                          aucNPlmnList[NAS_MMC_NVIM_MAX_CFG_NPLMN_DATA_EXTEND_LEN];/* NPLMN*/
}NAS_MMC_NVIM_CFG_DPLMN_NPLMN_INFO_OLD_STRU;
/* Added by c00318887 for DPlmnHPLMN, 2015-5-28, end */

/*****************************************************************************
     : NAS_MMC_NVIM_CFG_DPLMN_NPLMN_FLAG_STRU
   : en_NV_Item_Cfg_Dplmn_Nplmn_Flag NVIM
 1.       : 2014714
          : c00188733
      : DPLMN NPLMN
*****************************************************************************/
typedef struct
{
    VOS_UINT16                         usCfgDplmnNplmnFlag;
    VOS_UINT8                          ucCMCCHplmnNum;
    VOS_UINT8                          aucCMCCHplmnList[NAS_MMC_NVIM_MAX_CFG_HPLMN_NUM];
    VOS_UINT8                          ucUNICOMHplmnNum;
    VOS_UINT8                          aucUNICOMHplmnList[NAS_MMC_NVIM_MAX_CFG_HPLMN_NUM];
    VOS_UINT8                          ucCTHplmnNum;
    VOS_UINT8                          aucCTHplmnList[NAS_MMC_NVIM_MAX_CFG_HPLMN_NUM];
    VOS_UINT8                          aucReserve[3];
}NAS_MMC_NVIM_CFG_DPLMN_NPLMN_FLAG_STRU;

/* Added by l00426960 for Anycell, 2017-11-08, begin */
/*****************************************************************************
    : NV_NAS_HIGH_PRIO_PS_CFG_STRU
  : en_NV_Item_HIGH_PRIO_PS_CFG

1.       : 2017619
         : z00185430
     : 

*****************************************************************************/
typedef struct
{
    VOS_UINT8                   ucRestrainHighPrioRatHPlmnSrch;         /* Home1:0: Dallas */
    VOS_UINT8                   ucRestrainAnyCellSrch;                  /* AnyCell1:0: */
    VOS_UINT16                  usHighPrioRatHPlmnSrchTimerRetryLen;    /* HighPrioRatHPlmnSrch:  Dallas*/

    VOS_UINT8                   ucRsv1;                                /* 1 */
    VOS_UINT8                   ucRsv2;                                /* 2 */
    VOS_UINT8                   ucRsv3;                                /* 3 */
    VOS_UINT8                   ucRsv4;                                /* 4 */
}NV_NAS_HIGH_PRIO_PS_CFG_STRU;
/* Added by l00426960 for Anycell, 2017-11-08, end */

/*****************************************************************************
     : NAS_MMC_NVIM_DPLMN_NPLMN_CFG_STRU
   : en_NV_Item_Cfg_Dplmn_Nplmn_Flag NVIM
 1.       : 20151020
          : s00217060
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEHplmnNum;
    VOS_UINT8                           aucEHplmnList[NAS_MMC_NVIM_MAX_CFG_HPLMN_NUM];
    VOS_UINT8                           aucVersionId[NAS_MCC_NVIM_VERSION_LEN];
    VOS_UINT8                           aucReserved[2];
}NAS_MMC_NVIM_DPLMN_NPLMN_CFG_STRU;

/* Added by s00217060 for PhaseI, 2016-8-9, begin */
/*****************************************************************************
     : NAS_NVIM_BORDER_INFO_STRU
   : en_NV_Item_Ap_Preset_Border_Info NVIM
  1.       : 201689
           : s00217060
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucVersionId[NAS_MCC_NVIM_VERSION_LEN];
    VOS_UINT8                           ucReserved;                                                 /*  */
    VOS_UINT16                          usBorderNum;                                                /*  */
    /* ,71-3simplmn id
       4-5(0x8000w0x4000lte0x0080gsm)6-7LACTAC
       WG6-7LAC;LTE6-7TAC */
    VOS_UINT8                           aucBorderList[NAS_MMC_NVIM_MAX_CFG_BORDER_DATA_LEN];        /*  */
}NAS_NVIM_BORDER_INFO_STRU;
/* Added by s00217060 for PhaseI, 2016-8-9, end */


/*****************************************************************************
     : NAS_MML_USER_CFG_EHPLMN_INFO_STRU
   : en_NV_Item_User_Cfg_Ehplmn NVIMEhplmn List
 1.       : 201289
          : w00167002
      : V7R1C50_GUTL_PhaseII:CMCCEHPLMN
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucImsiPlmnListNum;                      /* IMSI */
    VOS_UINT8                           ucEhplmnListNum;                        /* EHplmn */
    VOS_UINT8                           aucReserve[2];
    NAS_SIM_FORMAT_PLMN_ID              astImsiPlmnList[NAS_MMC_NVIM_MAX_USER_CFG_IMSI_PLMN_NUM];
    NAS_SIM_FORMAT_PLMN_ID              astEhPlmnList[NAS_MMC_NVIM_MAX_USER_CFG_EHPLMN_NUM];
}NAS_MMC_NVIM_USER_CFG_EHPLMN_INFO_STRU;

/*****************************************************************************
     : NAS_MMC_NVIM_USER_CFG_EXT_EHPLMN_INFO_STRU
   : en_NV_Item_User_Cfg_Ehplmn NVIMEhplmn List
 1.       : 20141219
          : wx270776
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                ulNvimEhplmnNum;
    NAS_MMC_NVIM_USER_CFG_EHPLMN_INFO_STRU    astNvimEhplmnInfo[NAS_MMC_NVIM_MAX_USER_CFG_EXT_EHPLMN_NUM];
}NAS_MMC_NVIM_USER_CFG_EXT_EHPLMN_INFO_STRU;


/*****************************************************************************
     : NAS_MMC_NVIM_FORB_PLMN_INFO_STRU
   : en_NV_Item_User_Cfg_Forb_Plmn_Info NVIMFPLMN
  1.       : 201641
           : s00217060
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucImsiPlmnListNum;                      /* IMSI */
    VOS_UINT8                           ucForbPlmnListNum;                      /* Forb Plmn */
    VOS_UINT8                           aucReserve[2];
    NAS_SIM_FORMAT_PLMN_ID              astImsiPlmnList[NAS_MMC_NVIM_MAX_USER_CFG_IMSI_PLMN_NUM];
    NAS_SIM_FORMAT_PLMN_ID              astForbPlmnList[NAS_MMC_MAX_BLACK_LOCK_PLMN_WITH_RAT_NUM];
}NAS_MMC_NVIM_FORB_PLMN_INFO_STRU;


/*****************************************************************************
     : NAS_MMC_NVIM_USER_CFG_FORB_PLMN_INFO_STRU
   : en_NV_Item_User_Cfg_Forb_Plmn_Info NVIMForb PLMN
  1.       : 2016331
           : s00217060
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulGroupNum;
    NAS_MMC_NVIM_FORB_PLMN_INFO_STRU    astForbPlmnInfo[NAS_MMC_NVIM_MAX_USER_CFG_FORB_PLMN_GROUP_NUM];
}NAS_MMC_NVIM_USER_CFG_FORB_PLMN_INFO_STRU;

/*****************************************************************************
     : NAS_MMC_NVIM_CAUSE18_ENABLE_LTE_SUPPORT_FLG_STRU
   : en_NV_Item_Cause18_Enable_Lte_Support_Flg NV
  1.       : 201648
           : h00275845
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                          ucCause18EnableLteSupportFlg; /*Cause18 Enable Lte*/
    VOS_UINT8                          aucReserved0;
    VOS_UINT8                          aucReserved1;
    VOS_UINT8                          aucReserved2;
}NAS_MMC_NVIM_CAUSE18_ENABLE_LTE_SUPPORT_FLG_STRU;

/*****************************************************************************
     : NAS_MMC_NVIM_PLMN_WITH_RAT_STRU
   : NAS MML PLMN
 1.       : 201289
          : w00176964
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulMcc;                                  /* MCC,3 bytes */
    VOS_UINT32                          ulMnc;                                  /* MNC,2 or 3 bytes */
    VOS_UINT8                           enRat;
    VOS_UINT8                           aucReserve[3];
}NAS_MMC_NVIM_PLMN_WITH_RAT_STRU;


/*****************************************************************************
     : NAS_MMC_NVIM_DISABLED_RAT_PLMN_INFO_STRU
   : en_NV_Item_DISABLED_RAT_PLMN_INFO NV
  1.       : 2012815
           : w00176964
       : 
  2.       : 2015418
           : w00167002
       : DTS2015032709270:NV8
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulDisabledRatPlmnNum;                   /* PLMN,0 */

    NAS_MMC_NVIM_PLMN_WITH_RAT_STRU     astDisabledRatPlmnId[NAS_MML_NVIM_MAX_DISABLED_RAT_PLMN_NUM];/* PLMNRAT */

}NAS_MMC_NVIM_DISABLED_RAT_PLMN_INFO_STRU;

/*****************************************************************************
     : NAS_MMC_NVIM_RAT_FORBIDDEN_LIST_SWITCH_FLAG_ENUM
   :
 1.    : 20131101
       : l00208543
   : 
*****************************************************************************/
enum NAS_MMC_NVIM_RAT_FORBIDDEN_LIST_SWITCH_FLAG_ENUM
{
    NAS_MMC_NVIM_RAT_FORBIDDEN_LIST_SWITCH_INACTIVE                   = 0,           /*  */
    NAS_MMC_NVIM_RAT_FORBIDDEN_LIST_SWITCH_BLACK                      = 1,           /*  */
    NAS_MMC_NVIM_RAT_FORBIDDEN_LIST_SWITCH_WHITE                      = 2,           /*  */
    NAS_MMC_NVIM_RAT_FORBIDDEN_LIST_SWITCH_BUTT
};
typedef VOS_UINT8 NAS_MMC_NVIM_RAT_FORBIDDEN_LIST_SWITCH_FLAG_ENUM_UINT8;

/*****************************************************************************
     : NAS_MMC_NVIM_PLATFORM_SUPPORT_RAT_ENUM
   :
 1.    : 20131101
       : l00208543
   : 
*****************************************************************************/
enum NAS_MMC_NVIM_PLATFORM_SUPPORT_RAT_ENUM
{
    NAS_MMC_NVIM_PLATFORM_SUPPORT_RAT_GERAN                   = 0,           /* GERAN */
    NAS_MMC_NVIM_PLATFORM_SUPPORT_RAT_UTRAN                   = 1,           /* UTRANWCDMA/TDS-CDMA */
    NAS_MMC_NVIM_PLATFORM_SUPPORT_RAT_EUTRAN                  = 2,           /* E-UTRAN */
    NAS_MMC_NVIM_PLATFORM_SUPPORT_RAT_BUTT
};
typedef VOS_UINT8 NAS_MMC_NVIM_PLATFORM_SUPPORT_RAT_ENUM_UINT8;


enum NAS_MSCC_NVIM_SYS_PRI_CLASS_ENUM
{
    NAS_MSCC_NVIM_SYS_PRI_CLASS_HOME             = 0,    /* home or ehome plmn */
    NAS_MSCC_NVIM_SYS_PRI_CLASS_PREF             = 1,    /* UPLMN or OPLMN */
    NAS_MSCC_NVIM_SYS_PRI_CLASS_ANY              = 2,    /* Acceptable PLMN */
    NAS_MSCC_NVIM_SYS_PRI_CLASS_BUTT
};
typedef VOS_UINT8 NAS_MSCC_NVIM_SYS_PRI_CLASS_ENUM_UINT8;

/*****************************************************************************
     : NAS_MMC_NVIM_RAT_FORBIDDEN_LIST_STRU
   : en_NV_Item_Rat_Forbidden_List_Accord_Imsi_Config NV
  1.       : 20131101
           : l00208543
       : 

    ucSwitchFlag        0
                                  1: astImsiPlmnList RAT
                                  2astImsiPlmnList RAT
    ucImsiPlmnListNum   SIM16
    ucForbidRatListNum  RAT 8NVLTELTE+UTRAN
                                                       NV
    astImsiPlmnList     SIM16
    aucForbidRatList    RAT 2NVLTELTE+UTRAN
                                                   NV
                        0: GSM
                        1: UTRAN
                        2: E-UTRAN
                        
*****************************************************************************/
typedef struct
{
    NAS_MMC_NVIM_RAT_FORBIDDEN_LIST_SWITCH_FLAG_ENUM_UINT8  enSwitchFlag;                                         /*  */
    VOS_UINT8                                               ucImsiListNum;                                        /*SIM(/)  */
    VOS_UINT8                                               ucForbidRatNum;                                       /*RAT  */
    VOS_UINT8                                               aucReserve[1];
    NAS_SIM_FORMAT_PLMN_ID                                  astImsiList[NAS_NVIM_MAX_IMSI_FORBIDDEN_LIST_NUM];        /* SIM (/) */
    NAS_MMC_NVIM_PLATFORM_SUPPORT_RAT_ENUM_UINT8            aenForbidRatList[NAS_NVIM_MAX_RAT_FORBIDDEN_LIST_NUM];    /*  */
}NAS_MMC_NVIM_RAT_FORBIDDEN_LIST_STRU;

/*****************************************************************************
     : NAS_MMC_NVIM_CSFB_EMG_CALL_LAI_CHG_LAU_FIRST_CFG_STRU
   : NVIMcsfb gulaimmlau
 1.       : 2012814
          : z00161729
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCsfbEmgCallLaiChgLauFirstFlg;
    VOS_UINT8                           aucRserved[1];
}NAS_MMC_NVIM_CSFB_EMG_CALL_LAI_CHG_LAU_FIRST_CFG_STRU;
/*****************************************************************************
     : NAS_MMC_NVIM_PLMN_EXACTLY_COMPARE_FLAG_STRU
   : en_NV_Item_PLMN_EXACTLY_COMPARE_FLG NV
  1.       : 20120816
           : t00212959
       : DCM,
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucPlmnExactlyCompareFlag;
    VOS_UINT8                           aucRsv[3];                         /* */
}NAS_MMC_NVIM_PLMN_EXACTLY_COMPARE_FLAG_STRU;

/*****************************************************************************
     : NAS_MMC_NVIM_HPLMN_REGISTER_CTRL_FLAG_STRU
   : en_NV_Item_Hplmn_Register_Ctrl_Flg NV
 1.       : 20121129
          : w00176964
      : HPLMN
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucHplmnRegisterCtrlFlg;                 /* HPLMN */
    VOS_UINT8                           aucRsv[3];                              /*  */
}NAS_MMC_NVIM_HPLMN_REGISTER_CTRL_FLAG_STRU;
/*****************************************************************************
    : NAS_NVIM_CELL_SIGN_REPORT_CFG_STRU
  : 
1.      : 20121121
        : z00161729
    : ^cerssi
2.       : 201532
         : w00316404
     : reserve
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucSignThreshold;    /* ,RSSI
                                                                                  0 */
    VOS_UINT8                                               ucMinRptTimerInterval;     /*    */
    VOS_UINT8                                               ucRserved1;
    VOS_UINT8                                               ucRserved2;
} NAS_NVIM_CELL_SIGN_REPORT_CFG_STRU;

/*****************************************************************************
     : NAS_MMC_NVIM_H3G_CTRL_FLAG_STRU
   : en_NV_Item_H3g_Ctrl_Flg NV
 1.       : 2013410
          : w00176964
      : H3G
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucH3gCtrlFlg;                           /* H3G */
    VOS_UINT8                           aucRsv[3];                              /*  */
}NAS_MMC_NVIM_H3G_CTRL_FLAG_STRU;

/*****************************************************************************
     : NAS_MMC_NVIM_UCS2_CUSTOMIZATION_STRU
   : NAS_MMC_NVIM_UCS2_CUSTOMIZATION_STRU
  1.       : 2013522
           : l00167671
       : 
  2.       : 201532
           : w00316404
       : reserve
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usUcs2Customization;
    VOS_UINT8                           ucRserved1;
    VOS_UINT8                           ucRserved2;
}NAS_MMC_NVIM_UCS2_CUSTOMIZATION_STRU;

/*****************************************************************************
     : SMS_TIMER_LENGTH_STRU
   : 

1.        : 20121228
          : l00167671
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usTc1mLength;
    VOS_UINT16                          usTr1mLength;
    VOS_UINT16                          usTr2mLength;
    VOS_UINT16                          usTramLength;
}SMS_NVIM_TIMER_LENGTH_STRU;


/*****************************************************************************
     : NVIM_PRIVATE_CMD_STATUS_RPT_STRU
   : 
 1.       : 2013510
          : s00217060
      : ATCNV
 2.       : 201532
          : w00316404
      : reserve
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucStatus;                               /* NV, 0: 1:  */
    VOS_UINT8                           ucStatusRptGeneralControl;        /*  0:1: */
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}NVIM_PRIVATE_CMD_STATUS_RPT_STRU;

/*****************************************************************************
     : NAS_MMC_NVIM_SPECIAL_ROAM_STRU
   : en_NV_Item_Special_Roam_Flag NV
  1.       : 2011720
           : z00161729
       : 
  2.       : 201532
           : w00316404
       : reserve
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucStatus;                               /* NV, 0: 1:   */
    VOS_UINT8                           ucSpecialRoamFlg;                         /* VplmnHplmn,Hplmn,1:0: */
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}NAS_MMC_NVIM_SPECIAL_ROAM_STRU;

/*****************************************************************************
     : NAS_MMC_NVIM_ENHANCED_HPLMN_SRCH_FLG_STRU
   : NAS_MMC_NVIM_ENHANCED_HPLMN_SRCH_FLG_STRU
  1.       : 2013522
           : l00167671
       : 
  2.       : 201532
           : w00316404
       : reserve
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usEnhancedHplmnSrchFlg;
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}NAS_MMC_NVIM_ENHANCED_HPLMN_SRCH_FLG_STRU;

/*****************************************************************************
     : NAS_CC_NVIM_TIMER_LEN_STRU
   : NAS_CC_NVIM_TIMER_LEN_STRUen_NV_Item_CC_TimerLen
  1.       : 2013830
           : l00208543
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8   ucT305Len;
    VOS_UINT8   ucT308Len;
    VOS_UINT8   aucReserve[2];
}NAS_CC_NVIM_TIMER_LEN_STRU;

/*****************************************************************************
     : NAS_CC_NVIM_T303_LEN_CFG_STRU
   : NAS_CC_NVIM_T303_LEN_CFG_STRUen_NV_Item_CC_T303_Len_Cfg
  1.       : 2015320
           : wx270776
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucT303ActiveFlag;                       /* T3030:1:*/
    VOS_UINT8                           ucT303Len;                              /* T303 */
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}NAS_CC_NVIM_T303_LEN_CFG_STRU;

/*****************************************************************************
     : NAS_NVIM_LAU_REJ_TRIG_PLMN_SEARCH_CFG_STRU
   : 
  1.       : 2015821
           : s00217060
       : 

*****************************************************************************/
typedef struct
{
    VOS_UINT8   ucCmSrvExistTrigPlmnSearch;                                                     /*  */
    VOS_UINT8   ucCmSrvTrigPlmnSearchCauseNum;                                                  /*  */
    VOS_UINT8   ucReserve1;
    VOS_UINT8   ucReserve2;
    VOS_UINT8   aucCmSrvTrigPlmnSearchCause[NAS_NVIM_MAX_LAU_REJ_TRIG_PLMN_SEARCH_CAUSE_NUM];   /*  */
    VOS_UINT8   aucReserve[NAS_NVIM_MAX_LAU_REJ_TRIG_PLMN_SEARCH_CAUSE_NUM];                    /*  */
}NAS_NVIM_LAU_REJ_TRIG_PLMN_SEARCH_CFG_STRU;

/*****************************************************************************
     : NAS_NVIM_LAU_REJ_NORETRY_WHEN_CM_SRV_EXIST_CFG_STRU
   : 
  1.       : 2015821
           : s00217060
       : 

*****************************************************************************/
typedef struct
{
    VOS_UINT8   ucLauRejCauseNum;
    VOS_UINT8   ucLauRejTimes;
    VOS_UINT8   ucReserve1;
    VOS_UINT8   ucReserve2;
    VOS_UINT8   aucLauRejCause[NAS_NVIM_MAX_REJECT_NO_RETRY_CAUSE_NUM];
}NAS_NVIM_LAU_REJ_NORETRY_WHEN_CM_SRV_EXIST_CFG_STRU;

/*****************************************************************************
     : NAS_NVIM_CHANGE_REG_REJECT_CAUSE_FLG_STRU
   : NAS_NVIM_CHANGE_REG_REJECT_CAUSE_FLG_STRUen_NV_Item_ChangeRejectCause_Flg
  1.       : 20131009
           : l00208543
       : 
  2.       : 20131119
           : l00208543
       : 
*****************************************************************************/
typedef struct
{
    NAS_NVIM_CHANGE_REG_REJ_CAUSE_TYPE_ENUM_UINT8           enChangeRegRejCauCfg;
    VOS_UINT8   ucPreferredRegRejCau_HPLMN_EHPLMN;             /* HPLMN/EHPLMN */
    VOS_UINT8   ucPreferredRegRejCau_NOT_HPLMN_EHPLMN;         /* HPLMN/EHPLMN */
    VOS_UINT8   aucReserve[1];
}NAS_NVIM_CHANGE_REG_REJECT_CAUSE_FLG_STRU;

/*****************************************************************************
     : NAS_NVIM_ROAMINGREJECT_NORETYR_CFG_STRU
   : NAS_NVIM_ROAMINGREJECT_NORETYR_CFG_STRUen_NV_Item_ROAMING_REJECT_NORETRY_CFG
  1.       : 2014429
           : l00208543
       : 

*****************************************************************************/
typedef struct
{
    VOS_UINT8   ucNoRetryRejectCauseNum;
    VOS_UINT8   aucNoRetryRejectCause[NAS_NVIM_MAX_REJECT_NO_RETRY_CAUSE_NUM];
    VOS_UINT8   aucReserve[3];
}NAS_NVIM_ROAMINGREJECT_NORETYR_CFG_STRU;

/*****************************************************************************
     : NAS_MMC_NVIM_IGNORE_AUTH_REJ_CFG_STRU
   : en_NV_Item_Remove_Auth_Rej_CFG NV


 1.       : 2014218
          : l00215384
      : 
*****************************************************************************/
typedef struct
{
   VOS_UINT8                           ucIgnoreAuthRejFlg;
   VOS_UINT8                           ucMaxAuthRejNo;
   VOS_UINT8                           aucReserved[2];
}NAS_MMC_NVIM_IGNORE_AUTH_REJ_CFG_STRU;

/*****************************************************************************
     : NAS_NV_GWMAC_ADDR_STRU
   : NV_GWMAC_ADDR(39026)
  1.       : 2013522
           : l00167671
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8 ucStatus;
    VOS_UINT8 ucReserved1;
    VOS_UINT8 aucE5GwMacAddr[18];
}NAS_NV_GWMAC_ADDR_STRU;

/*****************************************************************************
     : NAS_NVIM_E5_ROAMING_WHITE_LIST_SUPPORT_FLG_STRU
   : E5_RoamingWhiteList_Support_Flg(39330)
  1.       : 2013522
           : l00167671
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8 aucE5_RoamingWhiteList_Support_Flg[2];
}NAS_NVIM_E5_ROAMING_WHITE_LIST_SUPPORT_FLG_STRU;

/*****************************************************************************
     : NAS_NVIM_NDIS_DIALUP_ADDRESS_STRU
   : NDIS_DIALUP_ADDRESS(39330)
  1.       : 2013522
           : l00167671
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT32 ulNDIS_DIALUP_ADDRESS;
}NAS_NVIM_NDIS_DIALUP_ADDRESS_STRU;

/*****************************************************************************
     : NAS_NVIM_NV_BREATH_LED_STR_STRU
   : NV_BREATH_LED_STR(9051)
  1.       : 2013522
           : l00167671
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8 ucBreOnTime; /*Range:[0,7]*/
    VOS_UINT8 ucBreOffTime; /*Range:[0,7]*/
    VOS_UINT8 ucBreRiseTime; /*Range:[0,5]*/
    VOS_UINT8 ucBreFallTime; /*Range:[0,5]*/
}NAS_NVIM_NV_BREATH_LED_STR_STRU;

/*****************************************************************************
     : NAS_NVIM_MANUAL_MODE_REG_HPLMN_CFG_STRU
   : en_NV_Item_Manual_Mode_Reg_Hplmn_CfgNV
   : 
     : typedef
   :
   :

       :
  1.       : 2018129
           : n00355355
       : 

*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucIsManualModeRegHplmnFlg;              /* HPLMNHPLMN */
    VOS_UINT8                           ucReserved1;                            /*  */
    VOS_UINT8                           ucReserved2;                            /*  */
    VOS_UINT8                           ucReserved3;                            /*  */
}NAS_NVIM_MANUAL_MODE_REG_HPLMN_CFG_STRU;

/*****************************************************************************
     : NAS_NVIM_NV_WIFI_Key_STRU
   : NV_WIFI_Key(50012)()
  1.       : 2013522
           : l00167671
       : 
*****************************************************************************/
typedef struct
{
VOS_UINT8  aucwlAuthMode[16];
VOS_UINT8  aucBasicEncryptionModes[5];
VOS_UINT8  aucWPAEncryptionModes[5];
VOS_UINT8  aucwlKeys1[27];
VOS_UINT8  aucwlKeys2[27];
VOS_UINT8  aucwlKeys3[27];
VOS_UINT8  aucwlKeys4[27];
VOS_UINT32 ulwlKeyIndex;
VOS_UINT8  aucwlWpaPsk[65];
VOS_UINT8  ucwlWpsEnbl;
VOS_UINT8  ucwlWpsCfg;
VOS_UINT8  ucReserved;
}NAS_NVIM_NV_WIFI_KEY_STRU;

/*****************************************************************************
     : NAS_NVIM_NV_PRI_VERSION_STRU
   : NV_PRI_VERSION(50023)
  1.       : 2013522
           : l00167671
       : 
*****************************************************************************/
typedef struct
{
VOS_UINT8 aucPRIVersion[32];
VOS_UINT8 aucReserve[32];
}NAS_NVIM_NV_PRI_VERSION_STRU;

/*****************************************************************************
    : NAS_NVIM_SYSTEM_APP_CONFIG_STRU
  : en_NV_Item_System_APP_Config(121)
1.       : 2013522
         : m00217266
     : 
2.       : 201532
         : w00316404
     : reserve
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usSysAppConfigType;
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}NAS_NVIM_SYSTEM_APP_CONFIG_STRU;

/*****************************************************************************
    : NAS_MMC_NVIM_NETWORK_CAPABILITY_STRU
  : en_NV_Item_NetworkCapability(8197)
1.       : 2013522
         : m00217266
     : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucNetworkCapability[NV_ITEM_NET_CAPABILITY_MAX_SIZE];
}NAS_MMC_NVIM_NETWORK_CAPABILITY_STRU;

/*****************************************************************************
    : NAS_NVIM_AUTOATTACH_STRU
  : en_NV_Item_Autoattach(8202)
1.       : 2013522
         : m00217266
     : 
2.       : 201532
         : w00316404
     : reserve
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usAutoattachFlag;
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}NAS_NVIM_AUTOATTACH_STRU;

/*****************************************************************************
    : NAS_NVIM_SELPLMN_MODE_STRU
  : en_NV_Item_SelPlmn_Mode(8214)
1.       : 2013522
         : m00217266
     : 
2.       : 201532
         : w00316404
     : reserve
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usSelPlmnMode;
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}NAS_NVIM_SELPLMN_MODE_STRU;

/*****************************************************************************
    : NAS_MMA_NVIM_ACCESS_MODE_STRU
  : en_NV_Item_MMA_AccessMode(8232)
1.       : 2013522
         : m00217266
     : 
2.       : 201532
         : w00316404
     : reserve
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucAccessMode[2];
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}NAS_MMA_NVIM_ACCESS_MODE_STRU;

/*****************************************************************************
    : NAS_NVIM_MS_CLASS_STRU
  : en_NV_Item_MMA_MsClass(8233)
1.       : 2013522
         : m00217266
     : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucMsClass;
    VOS_UINT8                           ucReserved;
}NAS_NVIM_MS_CLASS_STRU;

/*****************************************************************************
    : NAS_MMA_NVIM_RF_Auto_Test_Flag_STRU
  : en_NV_Item_RF_Auto_Test_Flag(8262)
1.       : 2013522
         : m00217266
     : 
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usRfAutoTestFlg;
}NAS_MMA_NVIM_RF_AUTO_TEST_FLAG_STRU;

/*****************************************************************************
    : NAS_NVIM_HPLMN_FIRST_TIMER_STRU
  : en_NV_Item_HPlmnFirstTimer(8276)
1.       : 2013522
         : m00217266
     : 
2.       : 201532
         : w00316404
     : reserve
*****************************************************************************/
typedef struct
{
    VOS_UINT8   ucHplmnTimerLen;
    VOS_UINT8   ucReserved1;
    VOS_UINT8   ucReserved2;
    VOS_UINT8   ucReserved3;
}NAS_NVIM_HPLMN_FIRST_TIMER_STRU;

/*****************************************************************************
    : NAS_MMC_NVIM_SUPPORT_3GPP_RELEASE_STRU
  : en_NV_Item_NAS_Supported_3GPP_Release(8288)
1.       : 2013522
         : m00217266
     : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8   aucSupported3GppRelease[NAS_MMC_NVIM_SUPPORTED_3GPP_RELEASE_SIZE];
}NAS_MMC_NVIM_SUPPORT_3GPP_RELEASE_STRU;

/*****************************************************************************
    : NAS_MMC_NVIM_LAST_IMSI_STRU
  : en_NV_Item_Last_Imsi(8325)
1.       : 2013522
         : m00217266
     : 
2.       : 201532
         : w00316404
     : reserve
*****************************************************************************/
typedef struct
{
    VOS_UINT8   ucValid;
    VOS_UINT8   aucImsi[NAS_MMC_NVIM_MAX_IMSI_LEN];
    VOS_UINT8   ucReserved1;
    VOS_UINT8   ucReserved2;
}NAS_MMC_NVIM_LAST_IMSI_STRU;

/*****************************************************************************
    : NAS_MMA_NVIM_ROAMING_BROKER_STRU
  : en_NV_Item_Roaming_Broker(8328)
1.       : 2013522
         : m00217266
     : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8   aucRoamingBroker[2];
}NAS_MMA_NVIM_ROAMING_BROKER_STRU;

/*****************************************************************************
    : NAS_MMC_NVIM_USE_SINGLE_RPLMN_STRU
  : en_NV_Item_Use_Single_Rplmn_When_Area_Lost(8343)
1.       : 2013522
         : m00217266
     : 
2.       : 201532
         : w00316404
     : reserve
*****************************************************************************/
typedef struct
{
    VOS_UINT16  usUseSingleRplmnFlag;
    VOS_UINT8   ucReserved1;
    VOS_UINT8   ucReserved2;
}NAS_MMC_NVIM_USE_SINGLE_RPLMN_STRU;

/* en_NV_Item_EquivalentPlmn 8215 */
/*****************************************************************************
    : NVIM_PLMN_VALUE_STRU
  : en_NV_Item_EquivalentPlmn(8215)#
1.       : 2013522
         : m00217266
     : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8    ucMcc[NVIM_MAX_MCC_SIZE];
    VOS_UINT8    ucMnc[NVIM_MAX_MNC_SIZE];
}NVIM_PLMN_VALUE_STRU;

/*****************************************************************************
    : NVIM_EQUIVALENT_PLMN_LIST_STRU
  : en_NV_Item_EquivalentPlmn(8215)#
1.       : 2013522
         : m00217266
     : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8             ucCount;
    NVIM_PLMN_VALUE_STRU  struPlmnList[NVIM_MAX_EPLMN_NUM];
    VOS_UINT8             aucReserve[3];   /*NV4*/
}NVIM_EQUIVALENT_PLMN_LIST_STRU;

/*en_NV_Item_Support_Freqbands 8229*/
/*
NVIM_UE_SUPPORT_FREQ_BAND_STRU:
usWcdmaBandusGsmBandBitbit1I,bit2II,
,1,.:
-------------------------------------------------------------------------------
        bit8       bit7      bit6     bit5    bit4     bit3      bit2     bit1
-------------------------------------------------------------------------------
WCDMA   900(VIII)  2600(VII) 800(VI)  850(V)  1700(IV) 1800(III) 1900(II) 2100(I) oct1
        spare      spare     spare    spare   spare    spare     spare   J1700(IX)oct2
-------------------------------------------------------------------------------
GSM 1900(VIII) 1800(VII) E900(VI) R900(V) P900(IV) 850(III)  480(II)  450(I)  oct3
        spare      spare     spare    spare   spare    spare     spare    700(IX) oct4
-------------------------------------------------------------------------------
aucUeSupportWcdmaBandaucUeSupportGsmBandUE,
,0xff.

:
oct1-oct40x03,0x00,0x7B,0x00
   WWCDMA-I-2100, WCDMA-II-1900
                         G850(III),P900(IV),R900(V),E900(VI),1800(VII)
oct5-oct16:2,5,1,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff
   UEWI,II,V,:II,V,I.
oct17-oct28:4,5,8,7,6,3,0xff,0xff,0xff,0xff,0xff,0xff
   UEGIII,IV,V,VI,VII,VIII,:IV,V,VIII,VII,VI,III.
*/
/*****************************************************************************
    : NAS_NVIM_UE_SUPPORT_FREQ_BAND_STRU
  : en_NV_Item_Support_Freqbands(8229)#
1.       : 2013522
         : m00217266
     : 
2.       : 201481
         : b00269685
     : NV
*****************************************************************************/
typedef struct
{
    VOS_UINT32                  ulWcdmaBand;
    VOS_UINT32                  ulGsmBand;
    VOS_UINT8                   aucReserved1[12];
    VOS_UINT8                   aucReserved2[12];
    VOS_UINT8                   aucReserved[24];        /* nv */
}NVIM_UE_SUPPORT_FREQ_BAND_STRU;

/*en_NV_Item_Roam_Capa 8266*/
/*****************************************************************************
     : NAS_NVIM_ROAM_CFG_INFO_STRU
   : en_NV_Item_Roam_Capa(8266) NV#
  1.       : 2011818
           : z00161729
       : 
  2.       : 201532
           : w00316404
       : reserve
*****************************************************************************/
typedef struct
{
    VOS_UINT8                               ucRoamFeatureFlg;                   /*,VOS_FALSE:,VOS_TRUE:*/
    VOS_UINT8                               ucRoamCapability;                   /**/
    VOS_UINT8                               ucReserve1;
    VOS_UINT8                               ucReserve2;
}NAS_NVIM_ROAM_CFG_INFO_STRU;

/*en_NV_Item_CustomizeService 8271*/
/*****************************************************************************
    : NAS_NVIM_CUSTOMIZE_SERVICE_STRU
  : en_NV_Item_CustomizeService(8271)#
            
1.       : 2013522
         : m00217266
     : 
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulStatus;           /*01 */
    VOS_UINT32                          ulCustomizeService; /*1byte4byte3byte*/
}NAS_NVIM_CUSTOMIZE_SERVICE_STRU;

/*en_NV_Item_RPlmnWithRat 8275*/
/*****************************************************************************
     : NAS_MM_NVIM_RPLMN_WITH_RAT_STRU
   : en_NV_Item_RPlmnWithRat(8275) NV
1.       : 2013522
         : m00217266
     : 
*****************************************************************************/
typedef struct
{
    NAS_NVIM_PLMN_ID_STRU               stGRplmn;                               /* G RPLMN */
    NAS_NVIM_PLMN_ID_STRU               stWRplmn;                               /* W RPLMN*/
    VOS_UINT8                           ucLastRplmnRat;                         /* 0:GSM;1:WCDMA;0xFF: */
    VOS_UINT8                           ucLastRplmnRatEnableFlg;                /* 0:NV ; 1:NV */
    VOS_UINT8                           aucReserved[2];                          /*  */
}NAS_NVIM_RPLMN_WITH_RAT_STRU;

/*****************************************************************************
     : NAS_MMC_NVIM_SEARCH_HPLMN_TIMER_STRU
   : en_NV_Item_SearchHplmnTtimerValue NV
  1.       : 2011725
           : z00161729
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                            ucStatus;                              /* 0:NV ; 1:NV  */
    VOS_UINT8                            ucReserve;                             /*  */
    VOS_UINT16                           usSrchHplmnTimerValue;                 /* VPLMNHPLMN,: */

}NAS_MMC_NVIM_SEARCH_HPLMN_TIMER_STRU;

/* Added by c00318887 for file refresh, 2015-4-28, begin */
/*****************************************************************************
     : NAS_MML_HIGH_PRIO_PLMN_REFRESH_TRIGGER_BG_SEARCH_CFG_STRU
   : en_NV_Item_HIGH_PRIO_PLMN_REFRESH_TRIGGER_BG_SEARCH_CFG NV
 1.       : 2015428
          : c00318887
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucTriggerBGSearchFlag;  /* 0: mmcPLMNBG SEARCH; 1:mmcPLMNBG SEARCH */
    VOS_UINT8                           ucReserved;
    VOS_UINT16                          usSearchDelayLen;             /* BG SEARCH Delay , :   */
}NAS_MMC_NVIM_HIGH_PRIO_PLMN_REFRESH_TRIGGER_BG_SEARCH_STRU;

/* Added by c00318887 for file refresh, 2015-4-28, end */


/*en_NV_Item_EFust_Service_Cfg 8285*/
/*****************************************************************************
     : NAS_MMC_NVIM_EFUST_SERVICE_CFG_STRU
   : en_NV_Item_EFust_Service_Cfg(8285) NV
  1.       : 2011725
           : z00161729
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucStatus;                               /* NV01 */
    VOS_UINT8                           ucForbidReg2GNetWork;                   /* 0EFust GSMEFust 2738GSM
                                                                                   UESIMEFust 2738GSM
                                                                                   EFUST0GSMGSM
                                                                                   SIMEFust 2738USIM1EFust GSM */
    VOS_UINT8                           ucForbidSndMsg;                         /* 0EFustEFust 1012SMS
                                                                                   1EFustNVUESIMEFUST1012
                                                                                   ,0SMS*/
    VOS_UINT8                           ucReserved[13];
}NAS_MMC_NVIM_EFUST_SERVICE_CFG_STRU;

/*en_NV_Item_UE_MSCR_VERSION 8289*/
/*****************************************************************************
     : NAS_MMC_NVIM_MSCR_VERSION_STRU
   : en_NV_Item_UE_MSCR_VERSION(8289) NV
 1.       : 2011714
          : z00161729
      : 
2.       : 201532
         : w00316404
     : reserve
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucStatus;                               /* NV, 0: 1:  */
    VOS_UINT8                           ucUeMscrVersion;                        /* SGSN */
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}NAS_MMC_NVIM_MSCR_VERSION_STRU;

/*en_NV_Item_UE_SGSNR_VERSION 8290*/
/*****************************************************************************
     : NAS_MMC_NVIM_SGSNR_VERSION_STRU
   : en_NV_Item_UE_SGSNR_VERSION(8290) NV
 1.       : 2011714
          : z00161729
      : 
 2.       : 201532
          : w00316404
      : reserve
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucStatus;                               /* NV, 0: 1:  */
    VOS_UINT8                           ucUeSgsnrVersion;                       /* SGSN */
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}NAS_MMC_NVIM_SGSNR_VERSION_STRU;

/*en_NV_Item_SteeringofRoaming_SUPPORT_CTRL 8292*/
/*****************************************************************************
     : NAS_MMC_NVIM_CS_REJ_SEARCH_SUPPORT_STRU
   : en_NV_Item_SteeringofRoaming_SUPPORT_CTRL(8292) NV
  1.       : 2011725
           : z00161729
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucStatus;                               /* NV, 0: 1:  */
    VOS_UINT8                           ucCsRejSearchSupportFlg;                /* vodafone,CS,VOS_FALSE:,VOS_TRUE: */
}NAS_MMC_NVIM_CS_REJ_SEARCH_SUPPORT_STRU;

/*en_NV_Item_Max_Forb_Roam_La 8320*/
/*****************************************************************************
     : NAS_MMC_NVIM_MAX_FORB_ROAM_LA_STRU
   : en_NV_Item_Max_Forb_Roam_La(8320) NV
  1.       : 2011725
           : z00161729
       : 
2.       : 201532
         : w00316404
     : reserve
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucMaxForbRoamLaFlg;                     /* NVLA: VOS_TRUE:valid;VOS_FALSE:INVALID */
    VOS_UINT8                           ucMaxForbRoamLaNum;                     /* NVLA */
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}NAS_MMC_NVIM_MAX_FORB_ROAM_LA_STRU;

/*en_NV_Item_Default_Max_Hplmn_Srch_Peri 8321*/
/*****************************************************************************
     : NAS_MMC_NVIM_DEFAULT_MAX_HPLMN_PERIOD_STRU
   : en_NV_Item_Default_Hplmn_Srch_Peri(8321) NV
  1.       : 2011720
           : z00161729
       : 
  2.       : 201532
           : w00316404
       : reserve
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucDefaultMaxHplmnPeriFlg;               /* HPLMN,VOS_TRUE:valid;VOS_FALSE:INVALID */
    VOS_UINT8                           ucDefaultMaxHplmnTim;                   /* HPLMN */
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}NAS_MMC_NVIM_DEFAULT_MAX_HPLMN_PERIOD_STRU;

/*en_NV_Item_USSD_Apha_To_Ascii 8327*/
/*USSD*/
/*****************************************************************************
     : NAS_SSA_NVIM_ALPHA_to_ASCII_STRU
   : en_NV_Item_USSD_Apha_To_Ascii(8327) NV
  1.       : 2011720
           : z00161729
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                       ucStatus;            /*01 */
    VOS_UINT8                       ucAlphaTransMode;    /* */
}NAS_SSA_NVIM_ALPHA_to_ASCII_STRU;

/*en_NV_Item_Register_Fail_Cnt 8338*/
/*****************************************************************************
     : NAS_MMC_NVIM_REG_FAIL_CNT_STRU
   : en_NV_Item_Register_Fail_Cnt(8338) NV
  1.       : 2011725
           : z00161729
       : 
  2.       : 201532
           : w00316404
       : reserve
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNvActiveFlag;                         /* NV */
    VOS_UINT8                           ucRegFailCnt;                           /* NV2 */
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}NAS_MMC_NVIM_REG_FAIL_CNT_STRU;

/*en_NV_Item_CREG_CGREG_CI_Four_Byte_Rpt 8345*/
/* VDF: CREG/CGREG<CI>4NV */
/*****************************************************************************
    : NAS_NV_CREG_CGREG_CI_FOUR_BYTE_RPT_STRU
  : en_NV_Item_CREG_CGREG_CI_Four_Byte_Rpt(8345)#
1.       : 2013522
         : m00217266
     : 
2.       : 201532
         : w00316404
     : reserve
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucStatus;                        /* 1: NV0 */
    VOS_UINT8                           ucCiBytesRpt;                    /* <CI>02, 14 */
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}NAS_NV_CREG_CGREG_CI_FOUR_BYTE_RPT_STRU;

/*****************************************************************************
     : NAS_MMC_NVIM_DAIL_REJECT_CFG_STRU
   : en_NV_Item__Dell_Reject_Config NV11,12,13,15,other cause,,NV
 1.       : 201236
          : w00176964
      : 
 2.       : 201532
          : w00316404
      : reserve
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEnableFlg;                            /*  VOS-TRUE: VOS_FALSE: */
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
    VOS_UINT8                           ucReserve3;
}NAS_MMC_NVIM_DAIL_REJECT_CFG_STRU;

/* en_NV_Item_NDIS_DHCP_DEF_LEASE_TIME 8344 */
typedef struct
{
    VOS_UINT32                          ulDhcpLeaseHour;    /*Range:[0x1,0x2250]*/
}NDIS_NV_DHCP_LEASE_HOUR_STRU;

typedef struct
{
    VOS_UINT32                          ulIpv6Mtu;          /*Range:[1280,65535]*/
}NDIS_NV_IPV6_MTU_STRU;

/*****************************************************************************
    : NAS_NVIM_CCALLSTATE_RPT_STATUS_STRU
  : en_NV_Item_CCallState_Rpt_Status nvid 9116()
1.       : 2013522
         : m00217266
     : 
2.       : 201532
         : w00316404
     : reserve
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucStatus;
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
}NAS_NVIM_CCALLSTATE_RPT_STATUS_STRU;

/*****************************************************************************
     : NVIM_PLMN_EXACTLY_COMPARE_FLAG_STRU
   : PLMN
   :
 1.        : 2012087
           : l00128652
       : 
*****************************************************************************/
typedef struct
{
   VOS_UINT8                            ucPlmnExactlyCompareFlag;               /* PLMN */
   VOS_UINT8                            aucRsv[3];                              /*  */
}NVIM_PLMN_EXACTLY_COMPARE_FLAG_STRU;

/*****************************************************************************
    : PLATFORM_RAT_TYPE_ENUM
  : 

  1.       : 20121225
           : z00220246
       : 
*******************************************************************************/
enum PLATFORM_RAT_TYPE_ENUM
{
    PLATFORM_RAT_GSM,                                                       /*GSM */
    PLATFORM_RAT_WCDMA,                                                     /* WCDMA */
    PLATFORM_RAT_LTE,                                                       /* LTE */
    PLATFORM_RAT_TDS,                                                       /* TDS */
    PLATFORM_RAT_1X,                                                        /* CDMA-1X */
    PLATFORM_RAT_HRPD,                                                      /* CDMA-EV_DO */

    PLATFORM_RAT_BUTT
};
typedef VOS_UINT16 PLATFORM_RAT_TYPE_ENUM_UINT16;

#define PLATFORM_MAX_RAT_NUM            (7)                                    /*  */

/*****************************************************************************
    : PLATAFORM_RAT_CAPABILITY_STRU
  : 

  1.       : 20121225
           : z00220246
       : 
*******************************************************************************/
typedef struct
{
    VOS_UINT16                           usRatNum;                              /* */
    PLATFORM_RAT_TYPE_ENUM_UINT16        aenRatList[PLATFORM_MAX_RAT_NUM];  /*  */
}PLATAFORM_RAT_CAPABILITY_STRU;

/*en_NV_Item_Rplmn 8216*/
/*****************************************************************************
     : NAS_NVIM_RPLMN_INFO_STRU
   : en_NV_Item_Rplmn(8216) NV()
1.       : 2013522
         : m00217266
     : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucRplmnInfo[56];
}NAS_NVIM_RPLMN_INFO_STRU;

/*****************************************************************************
     : SVLTE_SUPPORT_FLAG_STRU
   : en_NV_Item_SVLTE_FLAG NV
 1.       : 2013620
          : z00161729
      : SVLTE:0-1-
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucSvlteSupportFlag;                     /* SVLTE:0-1- */
    VOS_UINT8                           aucReserved[3];                         /*  */
}SVLTE_SUPPORT_FLAG_STRU;


/*****************************************************************************
     : NAS_MMC_NVIM_ENABLE_LTE_TIMER_LEN_STRU
   : en_NV_Item_Enable_Lte_Timer_Len NV
 1.       : 201363
          : z00161729
      : enable lte
 2.       : 2015424
          : z00161729
      : 24301 R11 CR
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNvimActiveFlag;                       /* 0: nv1:nv */
    VOS_UINT8                           ucCsPsMode1EnableLteTimerLen;           /* 1)cs ps mode1 Leps onlycs#16/#17/#22disable lteenable lte
                                                                                   2)cs ps mode1 Lcs epsother cause disable lteenable lte,: nv054 */
    VOS_UINT8                           ucCsfbEmgCallEnableLteTimerLen;         /* Lcsfbgugudisable lteenable lte: nv05 */

    /* #16#17#18Additional Update Result IE
    SMS OnlyCSFB Not Preferreddisable lteR11
    PLMNRAT0xFF
    : */
    VOS_UINT8                           ucLteVoiceNotAvailPlmnForbiddenPeriod;
}NAS_MMC_NVIM_ENABLE_LTE_TIMER_LEN_STRU;


/* Added by c00318887 for DCM DisableLteSMC, 2017-2-22, begin */
/*****************************************************************************
     : NAS_MMC_NVIM_DCM_CUSTOMER_ENABLE_LTE_TIMER_LEN_STRU
   : en_NV_Item_Dcm_Custom_Disable_Lte_Cfg NV

  1.       : 2017222
           : c00318887
       : DCM_CUSTOMER enable lte
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucActiveFlag;                           /* 0: nv1:nv */
    VOS_UINT8                           ucEnableLteTimerLen;                    /* EnableLte timer len, : nv0 */
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
}NAS_MMC_NVIM_DCM_CUSTOM_DISABLE_LTE_CFG_STRU;

/*****************************************************************************
     : NAS_MMC_NVIM_DCM_CUSTOMER_ENABLE_LTE_TIMER_LEN_STRU
   : en_NV_Item_Smc_Fail_Csfb_Mt_Force_Auth_Cfg NV

  1.       : 2017222
           : c00318887
       : SMC
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCsfbMtForceAuthFlag;                  /* 0: nv1:nv */
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
}NAS_MMC_NVIM_SMC_FAIL_CSFB_MT_FORCE_AUTH_CFG_STRU;

/* Added by c00318887 for DCM DisableLteSMC, 2017-2-22, end */

/* Added by c00318887 for T3402 , 2015-6-17, begin */
/*****************************************************************************
     : NAS_MMC_NVIM_DISABLE_LTE_START_T3402_ENABLE_LTE_CFG_STRU
   : en_NV_Item_DISABLE_LTE_START_T3402_ENABLE_LTE_CFG NV
             ucT3402Flag Disable LTE LTE :
             ucT3402Flag 0Disable LTE LTE NV_Item_Enable_Lte_Timer_Len  0x24049220
              ucT3402Flag  1LMM_MMC_T3402_LEN_NOTIFY
            1) EPS ONLY,CS18,CS16,17,22,other cause,EPS5
            2) EPS #19, 
            3) EPS #301, 
            4) EPS #other cause, 
            5) EPS #401, 
 1.       : 2015428
          : c00318887
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucT3402Flag;                           /* 0: LMM_MMC_T3402_LEN_NOTIFY; 1:LMM_MMC_T3402_LEN_NOTIFY */
    VOS_UINT8                           ucHighPrioRatTimerNotEnableLteFlag;    /* 1:RAT HPLMN TIMER ENABLE lte0: RAT HPLMN TIMER ENABLE lte */
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
}NAS_MMC_NVIM_DISABLE_LTE_START_T3402_ENABLE_LTE_CFG_STRU;

/* Added by c00318887 for T3402 , 2015-6-17, end */


/*****************************************************************************
     : NAS_MMC_NVIM_REJ_MAX_TIMES_DISABLE_LTE_CFG_STRU
   : lte attach and tau R12disable lte

  1.       : 2016824
           : c00318887
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucRejMaxTimesDisableLte;          /* 0: r12disable lte; 1: r12disable lte */
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
}NAS_MMC_NVIM_REJ_MAX_TIMES_DISABLE_LTE_CFG_STRU;


/*****************************************************************************
     : NAS_NVIM_SRVCC_SN_MODULO_CFG_STRU
   : SRVCCGSNR994

  1.       : 201691
           : n00269697
       : 
*****************************************************************************/
typedef struct
{
    /* 24007 11.2.3.2.3.1.1
       after successful completion of SRVCC handover (see 3GPP TS 23.216 [27]),
       the mobile station shall perform modulo 4 arithmetic operations on V(SD).
       The mobile station shall keep using modulo 4 until the release of the RR
       connection established at SRVCC handover.

       During SRVCC handover the MSCR bit is not provided to the mobile station,
       and therefore the mobile station assumes to access to a Release 99 or
       later core network.
    */
    VOS_UINT8                           ucSrvccSnModuloCfg;                     /* 0: SNSRVCCg_stMmNsd.ucNsdMod; 1: SNR994 */
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
}NAS_NVIM_SRVCC_SN_MODULO_CFG_STRU;

/*****************************************************************************
    : NAS_MMC_NVIM_ISR_CFG_STRU
  : ISR
1.      : 20130523
        : z00234330
    : ISRNVIM
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucIsrSupport;       /* ISR ???? */
    VOS_UINT8                                               ucReserve1;
} NAS_NVIM_ISR_CFG_STRU;


/*****************************************************************************
    : NAS_NVIM_EMC_BAR_TRIGGER_PLMN_SEARCH_STRU
  : bar

  1.       : 2017110
           : c00318887
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucEmcBarTriggerPlmnSearch;       /* VOS_FALSE: ;  VOS_TRUE:  */
    VOS_UINT8                                               ucReserve1;
    VOS_UINT8                                               ucReserve2;
    VOS_UINT8                                               ucReserve3;
} NAS_NVIM_EMC_BAR_TRIGGER_PLMN_SEARCH_STRU;


/*****************************************************************************
     : CSFB_MT_FOLLOW_ON_SUPPORT_FLAG_STRU
   : en_NV_Item_CSFB_MT_RAU_FOLLOW_ON_FLAG NV
 1.       : 2013725
          : w00242748
      : Csfb mtRAUfollow on:0-1-
 2.       : 2014610
          : w00242748
      : Csfb moRAUfollow on:0-1-
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucIsRauNeedFollowOnCsfbMtFlg;           /* Csfb mtRAUfollow on:0-1- */
    VOS_UINT8                           ucIsRauNeedFollowOnCsfbMoFlg;           /* Csfb moRAUfollow on:0-1- */
    VOS_UINT8                           aucReserved[2];                         /*  */
}NAS_MMC_CSFB_RAU_FOLLOW_ON_FLAG_STRU;

/*****************************************************************************
     : NV_DSDA_PLMN_SEARCH_ENHANCED_CFG_STRU
   : en_NV_Item_DSDA_PLMN_SEARCH_ENHANCED_CFG NV
  : Modem
  1)  ModemPLMN,FDDGUTL+GGFDDTDD
  2)  Modem1GSMLTDS, Modem0GSMT/LTDS/LTE
 1.       : 20131118
          : z00161729
      : 
 2.       : 2014126
          : z00161729
      : DTS2014012305088NCELLModem1NCELL
*****************************************************************************/
typedef struct
{
   VOS_UINT16                           usSolutionMask;/*ModemBitbitn=0nbitn=1n
                                                         bit0bit1 
                                                         BIT0ModemModemPLMNFDD
                                                         BIT1Modem1GSMLTDS, Modem0GSMT/LTDS/LTE
                                                               Modem1NCELLucSolution2NcellSearchTimer
                                                         BIT2~BIT15:*/
   VOS_UINT8                            ucSolution2NcellQuickSearchTimer;       /**/

   VOS_UINT8                            ucSolution2NcellQuickSearchTimer2;      /* */
   VOS_UINT8                            aucAdditonCfg[4];
}NV_DSDA_PLMN_SEARCH_ENHANCED_CFG_STRU;


/*****************************************************************************
    : NV_NAS_GMM_REL_CONN_AFTER_PDP_DEACT_STRU
  : en_NV_Item_NAS_GMM_REL_CONN_AFTER_PDP_DEACT(9140)
1.       : 20140113
         : l65478
     : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8   ucRelFlg;
    VOS_UINT8   ucReserve;
}NV_NAS_GMM_REL_CONN_AFTER_PDP_DEACT_STRU;

/*****************************************************************************
    : NAS_NVIM_WG_RF_MAIN_BAND_STRU
  : en_NV_Item_WG_RF_MAIN_BAND
  1.       : 20140210
           : f62575
       : DTS2014012600456: en_NV_Item_WG_RF_MAIN_BAND
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulWband;                                /* WCDMA */
    VOS_UINT32                          ulWbandExt;                             /* WCDMA */
    VOS_UINT32                          ulGband;                                /* GSM */
}NAS_NVIM_WG_RF_MAIN_BAND_STRU;


/*****************************************************************************
     : NAS_MMC_IMS_VOICE_MOBILE_MANAGEMENT
   : en_NV_Item_IMS_VOICE_MOBILE_MANAGEMENT NV
 1.       : 20131216
          : f00261443
      : ISRLGULAIRAI
                LAURAU
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucImsVoiceInterSysLauEnable;           /* ISRLGULAILAU */
    VOS_UINT8                           ucImsVoiceMMEnable;         /* IMS NV */
    VOS_UINT8                           aucReserved[2];             /*  */
}NAS_MMC_IMS_VOICE_MOBILE_MANAGEMENT;

/*****************************************************************************
    : NAS_MMC_LTE_DISABLED_USE_LTE_INFO_FLAG_STRU
  : en_NV_Item_LTE_DISABLED_USE_LTE_INFO_FLAG
  1.       : 20140225
           : z00161729
       : DTS2014022206794:GCF 9.2.1.2.1b/9.2.3.2.3/9.2.1.2.1disable lterauL

*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucLDisabledRauUseLInfoFlag;             /* l disabledraulgutivos_true:vos_false:*/
    VOS_UINT8                           ucReserved[3];
}NAS_MMC_LTE_DISABLED_USE_LTE_INFO_FLAG_STRU;


/*****************************************************************************
    : NAS_MML_CS_ONLY_DATA_SERVICE_SUPPORT_FLG_STRU
  : en_NV_Item_CS_ONLY_DATA_SERVICE_SUPPORT_FLG
  1.       : 20140213
           : f62575
       : DTS2014012902032:
                 NVen_NV_Item_CS_ONLY_DATA_SERVICE_SUPPORT_FLG
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucActiveFlg;                            /*  */
    VOS_UINT8                           ucCsOnlyDataServiceSupportFlg;          /* PS */
}NAS_MML_CS_ONLY_DATA_SERVICE_SUPPORT_FLG_STRU;
/*****************************************************************************
     : NAS_MMC_NVIM_HIGH_PRIO_RAT_HPLMN_TIMER_INFO_STRU
   : en_NV_Item_HIGH_PRIO_RAT_HPLMN_TIMER_INFO NV
 1.       : 2014219
          : w00176964
      : 
 2.       : 20141025
          : b00269685
      : NV
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucActiveFLg;                             /*  */                       /* TD */
    VOS_UINT8                           aucRsv[3];
    VOS_UINT32                          ulFirstSearchTimeLen;                   /* high prio rat timer : */
    VOS_UINT32                          ulFirstSearchTimeCount;                 /* high prio rat timer */
    VOS_UINT32                          ulNonFirstSearchTimeLen;                /* high prio rat timer : */
    VOS_UINT32                          ulRetrySearchTimeLen;                   /* high prio rat  :*/
}NAS_MMC_NVIM_HIGH_PRIO_RAT_HPLMN_TIMER_INFO_STRU;

/*****************************************************************************
     : NAS_MMC_NVIM_HIGH_PRIO_RAT_HPLMN_TIMER_CFG_STRU
   : en_NV_Item_HIGH_PRIO_RAT_HPLMN_TIMER_CFG NV
 1.       : 20141025
          : b00269685
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucActiveFLg;                            /*  */
    VOS_UINT8                           ucTdThreshold;                          /* TD */
    VOS_UINT8                           aucRsv[2];
    VOS_UINT32                          ulFirstSearchTimeLen;                   /* high prio rat timer : */
    VOS_UINT32                          ulFirstSearchTimeCount;                 /* high prio rat timer */
    VOS_UINT32                          ulNonFirstSearchTimeLen;                /* high prio rat timer : */
    VOS_UINT32                          ulRetrySearchTimeLen;                   /* high prio rat  :*/
}NAS_MMC_NVIM_HIGH_PRIO_RAT_HPLMN_TIMER_CFG_STRU;


/*****************************************************************************
     : NAS_MMC_NVIM_ULTRA_FLASH_CSFB_SUPPORT_FLG_STRU
   : en_NV_Item_Ultra_Flash_Csfb_Support_Flg NV
 1.       : 2014530
          : s00217060
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucUltraFlashCsfbSupportFLg;                 /* ultra flash csfb */
    VOS_UINT8                           aucRsv[3];
}NAS_MMC_NVIM_ULTRA_FLASH_CSFB_SUPPORT_FLG_STRU;

/*****************************************************************************
     : NAS_MMC_NVIM_3GPP2_Uplmn_Not_Pref_STRU
   : en_NV_Item_3GPP2_Uplmn_Not_Pref_Flg NV
 1.       : 2014613
          : B00269685
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           uc3GPP2UplmnNotPrefFlg;                    /* 3GPP2 pref plmn */
    VOS_UINT8                           aucRsv[3];
}NAS_MMC_NVIM_3GPP2_UPLMN_NOT_PREF_STRU;

/*****************************************************************************
     : NAS_MMC_NVIM_SYSCFG_TRIGGER_PLMN_SEARCH_CFG_STRU
   : en_NV_Item_Syscfg_Trigger_Plmn_Search_Cfg NV
 1.       : 2014714
          : w00242748
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucHighPrioRatPlmnSrchFlg;                  /*  */
    VOS_UINT8                           aucReserved1[3];
}NAS_MMC_NVIM_SYSCFG_TRIGGER_PLMN_SEARCH_CFG_STRU;

/*****************************************************************************
     : NAS_MMC_NVIM_DSDS_END_SESSION_DELAY_STRU
   : en_NV_Item_Dsds_Delay_Time NV
 1.       : 2014717
          : B00269685
      : 

 2.       : 201655
          : n00355355
      : DR DSDS2.0CSFB
  3.       : 2017126
           : s00217060
       : DSDSNV
*****************************************************************************/
typedef struct
{
    VOS_UINT32                           ulCsRegEndSessionDelayTime;              /* Lau: */
    VOS_UINT32                           ulPsRegEndSessionDelayTime;              /* Rau: */
    VOS_UINT32                           ulCsfbCallEndSessionDelayTime;               /* CSFB: */
    VOS_UINT32                           ulReserve2;
} NAS_MMC_NVIM_DSDS_END_SESSION_DELAY_STRU;

/* Added by s00217060 for DSDS, 2017-1-26, begin */
/*****************************************************************************
     : NAS_MMC_NVIM_DSDS_DELAY_TIME_STRU
   : en_NV_Item_Dsds_Delay_Time NV
  1.       : 2017126
           : s00217060
       : DSDS
*****************************************************************************/

typedef struct
{
    VOS_UINT32                           ulCsRegEndSessionDelayTime;            /* Lau: */
    VOS_UINT32                           ulPsRegEndSessionDelayTime;            /* Rau: */
    VOS_UINT32                           ulCsfbCallEndSessionDelayTime;         /* CSFB: */
    VOS_UINT32                           ulCsCallEndSessionDelayTime;           /* CS CALL: */
    VOS_UINT32                           ulCsSmsEndSessionDelayTime;            /* CS SMS: */
    VOS_UINT32                           ulCsSsEndSessionDelayTime;             /* CS SS: */
    VOS_UINT32                           ulCsRegEnableRfOccupyDelayTime;        /* LAU: */
    VOS_UINT32                           ulReserve1;
    VOS_UINT32                           ulReserve2;
    VOS_UINT32                           ulReserve3;
    VOS_UINT32                           ulReserve4;
} NAS_MMC_NVIM_DSDS_DELAY_TIME_STRU;
/* Added by s00217060 for DSDS, 2017-1-26, end */

/*****************************************************************************
     : CNAS_NVIM_1X_SYSTEM_STRU
   : 1x system
 1.       : 2014818
          : w00176964
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usSid;
    VOS_UINT16                                              usNid;
    VOS_UINT16                                              usBandClass;
    VOS_UINT16                                              usChannel;
}CNAS_NVIM_1X_SYSTEM_STRU;

/*****************************************************************************
     : CNAS_XSD_NVIM_1X_MRU_LIST_STRU
   : en_NV_Item_1X_MRU_LIST NV
 1.       : 2014818
          : w00176964
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucSysNum;
    VOS_UINT8                           aucReserve[3];
    CNAS_NVIM_1X_SYSTEM_STRU            astSystem[CNAS_NVIM_MAX_1X_MRU_SYS_NUM];
}CNAS_NVIM_1X_MRU_LIST_STRU;


/*****************************************************************************
     : CNAS_NVIM_1X_TEST_CONFIG_STRU
   : en_NV_Item_1X_TEST_CONFIG NV
 1.       : 2015511
          : c00299063
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucReadNvPrlDirectly;
    VOS_UINT8                           ucReadDefaultPrl;        /* Default Prl */
    VOS_UINT8                           ucIsMod1xAvailTimerLen;
    VOS_UINT8                           ucNvPrlCombinedFlag;     /* NV PRL */
    VOS_UINT8                           aucReserve[12];

}CNAS_NVIM_TEST_CONFIG_STRU;

/*****************************************************************************
     : CNAS_NVIM_1X_CALLBACK_CFG_STRU
   : en_Nv_Item_CNAS_XSD_CALLBACK_CFG NV
 1.       : 201572
          : h00313353
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulCallBackEnableFlg;
    VOS_UINT32                          ulCallBackModeTimerLen;
} CNAS_NVIM_1X_CALLBACK_CFG_STRU;

/*****************************************************************************
     : NAS_MSCC_NVIM_CTCC_ROAM_EMC_CALL_CFG_STRU
   : en_NV_Item_CTCC_ROAM_EMC_CALL_CFG NV
 1.       : 201675
          : c00299063
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucIsAllowCallInForeign;
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
}NAS_MSCC_NVIM_CTCC_ROAM_EMC_CALL_CFG_STRU;

/*****************************************************************************
     : CNAS_NVIM_1X_ADD_AVOID_FREQ_CFG_STRU
   : en_NV_Item_1X_ADD_AVOID_CHAN_CFG NV
 1.       : 201565
          : c00299063
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucIsNegSysAdd;
    VOS_UINT8                           aucReserve[15];
}CNAS_NVIM_1X_ADD_AVOID_LIST_CFG_STRU;

/*****************************************************************************
     : CNAS_NVIM_1X_NEG_PREF_SYS_CMP_CTRL_STRU
   : en_NV_Item_1X_NEG_PREF_SYS_CMP_CTRL NV
 1.       : 201565
          : c00299063
      : 
*****************************************************************************/
typedef struct
{
    CNAS_NVIM_1X_NEG_PREF_SYS_CMP_TYPE_ENUM_UINT8           enNegPrefSysCmpType;
    VOS_UINT8                                               aucReserve[15];
}CNAS_NVIM_1X_NEG_PREF_SYS_CMP_CTRL_STRU;

/*****************************************************************************
     : CNAS_NVIM_1X_CALL_NVIM_CFG_STRU
   : en_NV_Item_1X_CALL_NVIM_CFG_CTRL NV
 1.       : 2015615
          : c00299063
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucIsL3ErrReOrigCount;
    VOS_UINT8                                               ucPrivacyMode;      /* privacy mode flag: 0 - disable 1 - enable */

    VOS_UINT8                                               aucReserve[14];
}CNAS_NVIM_1X_CALL_NVIM_CFG_STRU;


/*****************************************************************************
     : CNAS_NVIM_1X_SUPPORT_BANDCLASS_MASK_STRU
   :
 ASN.1 :
   :   3601
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulSupportBandclassMask;               /* bit0x000000010 */
}CNAS_NVIM_1X_SUPPORT_BANDCLASS_MASK_STRU;

/*****************************************************************************
     : CNAS_NVIM_HRPD_SUPPORT_BANDCLASS_MASK_STRU
   :
 ASN.1 :
   :   3601
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulSupportBandclassMask;               /* bit0x000000010 */
}CNAS_NVIM_HRPD_SUPPORT_BANDCLASS_MASK_STRU;

/*****************************************************************************
     : CNAS_NVIM_HRPD_AVOID_PHASE_STRU
   : avoid
  1.       : 20160302
           : x00306642
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          ausAvoidTimerLen[CNAS_NVIM_HRPD_AVOID_MAX_PHASE_NUM];
}CNAS_NVIM_HRPD_AVOID_PHASE_STRU;

/*****************************************************************************
     : CNAS_NVIM_HRPD_AVOID_SCHEDULE_INFO_STRU
   : avoid
  1.       : 20160302
           : x00306642
       : 
*****************************************************************************/
typedef struct
{
    CNAS_NVIM_HRPD_AVOID_PHASE_STRU     astAvoidPhaseNum[CNAS_NVIM_HRPD_AVOID_REASON_MAX];
}CNAS_NVIM_HRPD_AVOID_SCHEDULE_INFO_STRU;

/*****************************************************************************
    :NAS_MMC_NVIM_ADAPTION_CAUSE_STRU
    :
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCnCause;     /*  */
    VOS_UINT8                           ucHplmnCause;  /* HPLMN */
    VOS_UINT8                           ucVplmnCause;  /* VPLMN */
    VOS_UINT8                           aucReserved[1];
}NAS_MMC_NVIM_ADAPTION_CAUSE_STRU;

/*****************************************************************************
    :NAS_MMC_NVIM_CHANGE_NW_CAUSE_CFG_STRU
    :en_NV_Item_ChangeNWCause_CFG NV
*****************************************************************************/
typedef struct
{
    /* CS(LU) */
    VOS_UINT8                           ucCsRegCauseNum;
    VOS_UINT8                           aucReserved1[3];
    NAS_MMC_NVIM_ADAPTION_CAUSE_STRU    astCsRegAdaptCause[NAS_MMC_NVIM_MAX_CAUSE_NUM];

    /* PS(ATTACH/RAU) */
    VOS_UINT8                           ucPsRegCauseNum;
    VOS_UINT8                           aucReserved2[3];
    NAS_MMC_NVIM_ADAPTION_CAUSE_STRU    astPsRegAdaptCause[NAS_MMC_NVIM_MAX_CAUSE_NUM];

    /* GPRS Detach  */
    VOS_UINT8                           ucDetachCauseNum;
    VOS_UINT8                           aucReserved3[3];
    NAS_MMC_NVIM_ADAPTION_CAUSE_STRU    astDetachAdaptCause[NAS_MMC_NVIM_MAX_CAUSE_NUM];

    /* GMM service request */
    VOS_UINT8                           ucPsSerRejCauseNum;
    VOS_UINT8                           aucReserved4[3];
    NAS_MMC_NVIM_ADAPTION_CAUSE_STRU    astPsSerRejAdaptCause[NAS_MMC_NVIM_MAX_CAUSE_NUM];

    /* MM ABORT */
    VOS_UINT8                           ucMmAbortCauseNum;
    VOS_UINT8                           aucReserved5[3];
    NAS_MMC_NVIM_ADAPTION_CAUSE_STRU    astMmAbortAdaptCause[NAS_MMC_NVIM_MAX_CAUSE_NUM];

    /* CM Service */
    VOS_UINT8                           ucCmSerRejCauseNum;
    VOS_UINT8                           aucReserved6[3];
    NAS_MMC_NVIM_ADAPTION_CAUSE_STRU    astCmSerRejAdaptCause[NAS_MMC_NVIM_MAX_CAUSE_NUM];

    VOS_UINT8                           ucHplmnPsRejCauseChangTo17MaxNum; /* HPLMN PS/EPS#17 */
    VOS_UINT8                           ucHplmnCsRejCauseChangTo17MaxNum; /* HPLMN CS#17 */
    VOS_UINT8                           ucVplmnPsRejCauseChangTo17MaxNum; /* VPLMN PS/EPS#17 */
    VOS_UINT8                           ucVplmnCsRejCauseChangTo17MaxNum; /* VPLMN CS#17 */
}NAS_MMC_NVIM_CHANGE_NW_CAUSE_CFG_STRU;

/*****************************************************************************
     : NAS_MMC_NVIM_REL_PS_SIGNAL_CON_CFG_STRU
   : en_NV_Item_REL_PS_SIGNAL_CON_CFG NV
 1.       : 20141104
        : h00285180
    : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucRelPsSignalConFlg;/*  */

    VOS_UINT8                           ucPdpExistNotStartT3340Flag; /* rauattachfollow onattach acceptrau acceptfollow onpdpT3340,0:T3340; 1: */
    VOS_UINT8                           aucReserved[2];

    VOS_UINT32                          ulT3340Len;         /* GMM T3340,: */
}NAS_MMC_NVIM_REL_PS_SIGNAL_CON_CFG_STRU;

/*****************************************************************************
     : NAS_RABM_NVIM_WCDMA_VOICE_PREFER_STRU
   : en_NV_Item_WCDMA_VOICE_PREFER_CFG
  1.       : 20141226
           : s00273135
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8   ucEnableFlag;/* */
    VOS_UINT8   aucReserve[3];
    VOS_UINT32  ulMcc;    /*MCC*/
    VOS_UINT32  ulMnc;    /*MNC*/
}NAS_RABM_NVIM_WCDMA_VOICE_PREFER_STRU;
/*****************************************************************************
     : NAS_NV_TRI_MODE_ENABLE_STRU
   : en_NV_Item_TRI_MODE_ENABLE NV
 1.       : 20150104
        : z00306637
    : 
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usEnable;                          /*  */
    VOS_UINT16                              usReserved;
}NAS_NV_TRI_MODE_ENABLE_STRU;

/*****************************************************************************
     : NAS_NV_TRI_MODE_FEM_PROFILE_ID_STRU
   : en_NV_Item_TRI_MODE_FEM_PROFILE_ID NV
 1.       : 20150104
        : z00306637
    : 
*****************************************************************************/
typedef struct
{
    VOS_UINT32                              ulProfileId;                        /* ABBTCXORFRF
                                                                                   AT00-7 */
    VOS_UINT32                              ulReserved[3];                     /*  */
}NAS_NV_TRI_MODE_FEM_PROFILE_ID_STRU;



/*****************************************************************************
    : NAS_NV_MODE_BASIC_PARA_STRU
  :
NVID:

  1.       : 20141230
           : z00306637
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usABBSwitch;                       /* ABB PLL0:ABB CH0 1:ABB CH1 2:ABB CH0&CH1 */
    VOS_UINT16                              usRFSwitch;                        /* RFIC0:RFICMIPI0 1RFICMIPI1 2*/
    VOS_UINT16                              usTCXOSwitch;                      /* 0:TCXO0 1:TCXO1 */
    VOS_UINT16                              usReserved;                        /*  */
}NAS_NV_MODE_BASIC_PARA_STRU;

/*****************************************************************************
     : NV_TRI_MODE_CHAN_PARA_STRU
   :
 ASN.1 :
   :   ()
*****************************************************************************/
typedef struct
{
    NAS_NV_MODE_BASIC_PARA_STRU            stModeBasicPara[2];                  /* [0]:GSM
                                                                                   [1]:WCDMA
                                                                                    WCDMA*/
    VOS_UINT32                              ulRfSwitch;                         /*  */
    VOS_UINT32                              ulGsmRficSel;                       /* 0RF0,1RF1 */
    VOS_UINT32                              ulGpioCtrl;                         /* gpio */
    VOS_UINT32                              aulReserved[14];                    /*  */
}NAS_NV_TRI_MODE_CHAN_PARA_STRU;

/*****************************************************************************
     : NAS_NV_TRI_MODE_FEM_CHAN_PROFILE_STRU
   :
 ASN.1 :
   : 8
*****************************************************************************/
typedef struct
{
    NAS_NV_TRI_MODE_CHAN_PARA_STRU          stPara[NAS_NV_TRI_MODE_CHAN_PARA_PROFILE_NUM];  /* 8 */
}NAS_NV_TRI_MODE_FEM_CHAN_PROFILE_STRU;





/*****************************************************************************
     : NAS_MMC_NVIM_CSMO_SUPPORTED_CFG_STRU
   : en_NV_Item_CSMO_SUPPORTED_Cfg_Info NV
 1.       : 2015303
          : w00167002
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCsmoSupportedFlg;
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
}NAS_MMC_NVIM_CSMO_SUPPORTED_CFG_STRU;


/*****************************************************************************
     : NAS_MMC_NVIM_ROAM_DISPLAY_CFG_STRU
   : en_NV_Item_Roam_Display_Cfg NV
 1.       : 2015320
          : B00269685
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucHplmnInEplmnDisplayHomeFlg;
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
}NAS_MMC_NVIM_ROAM_DISPLAY_CFG_STRU;

/*****************************************************************************
     : NAS_MMC_MT_CSFB_PAGING_PROCEDURE_LEN_STRU
   : en_NV_Item_Mt_Csfb_Paging_Procedure_Len NV
 1.       : 201554
          : B00269685
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usMtCsfbPagingProcedureLen;
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
}NAS_MMC_NVIM_PROTECT_MT_CSFB_PAGING_PROCEDURE_LEN_STRU;

/*****************************************************************************
     : NAS_MMC_NVIM_ROAM_PLMN_SELECTION_SORT_CFG_STRU
   : en_NV_Item_Roam_Plmn_Selection_Sort_Cfg NV
 1.       : 2015602
          : W00167002
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucRoamPlmnSelectionSortFlg;
    VOS_UINT8                           ucSrchUOplmnPriorToDplmnFlg;
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
}NAS_MMC_NVIM_ROAM_PLMN_SELECTION_SORT_CFG_STRU;


/*****************************************************************************
     : NAS_MMC_NVIM_OOS_PLMN_SEARCH_PATTERN_CFG_STRU
   : 
  1.       : 20151010
           : h00281185
       : 

    NV :
    ucHistoryNum          PrefBand/FullBand
    ucPrefBandNum       PrefBand  FullBand
    ucFullBandNum       FullBand, , 

    
        
        Timerlen = 2sec
        ucHistoryNum            = 2
        ucPrefBandNum           = 2
        ucFullBandNum           = 1
         -> TotalLen            = 2*2*2 = 8
        
        Timerlen = 4sec
        ucHistoryNum            = 1
        ucPrefBandNum           = 2
        ucFullBandNum           = Null (1 or 100 , full band)
         -> TotalLen            = 1*2*4 = 8

        
        OOC:_H_P_H_F|__P__F__P__F__P__F__P__F ...

        :
        OOC:_H_H_P_H_H_P_H_H_F|__H__P__H__P__H__F
        TotalLen = (2+1)*(2+1)*2sec = 18sec (FullBand)

        
        CASE#1:
        ucHistoryNum            = 2
        ucPrefBandNum           = 2
        ucFullBandNum           = 0
        OOC:_H_H_P_H_H_P|
        TotalLen = (2+1)*2sec = 6 (PrefBand)

        CASE#2:
        ucHistoryNum            = 2
        ucPrefBandNum           = 0
        ucFullBandNum           = 0
        OOC:_H_H|
        TotalLen = Timerlen     = 2sec (PrefBand)

        CASE#3:
        ucFullBandNum           = 0
        ucPrefBandNum           = 0
        ucHistoryNum            = 0
        ucFullBandNum = 1
        OOC:_F|

*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usTotalTimerLen;                        /* ,:s */
    VOS_UINT16                          usSleepTimerLen;                        /* ,:s */
    VOS_UINT16                          usReserve1;
    VOS_UINT16                          usReserve2;
    VOS_UINT8                           ucHistoryNum;                           /*   PrefBand/FullBand */
    VOS_UINT8                           ucPrefBandNum;                          /* PrefBand  FullBand */
    VOS_UINT8                           ucFullBandNum;                          /* FullBand, ,  */
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
    VOS_UINT8                           ucReserve3;
    VOS_UINT8                           ucReserve4;
    VOS_UINT8                           ucReserve5;
}NAS_MMC_NVIM_OOS_PLMN_SEARCH_PATTERN_CFG_STRU;

/*****************************************************************************
     : NAS_MMC_NVIM_OOS_PLMN_SEARCH_STRATEGY_CFG_STRU
   : en_NV_Item_Oos_Plmn_Search_Strategy_Cfg NV
  1.       : 20151010
           : h00281185
       : 
*****************************************************************************/
typedef struct
{
    NAS_MMC_NVIM_OOS_PLMN_SEARCH_PATTERN_CFG_STRU           stPhaseOnePatternCfg;    /*  */
    NAS_MMC_NVIM_OOS_PLMN_SEARCH_PATTERN_CFG_STRU           stPhaseTwoPatternCfg;    /*  */
    NAS_MMC_NVIM_OOS_PLMN_SEARCH_PATTERN_CFG_STRU           stPhaseThreePatternCfg;  /*  */
    NAS_MMC_NVIM_OOS_PLMN_SEARCH_PATTERN_CFG_STRU           stPhaseFourPatternCfg;   /*  */
}NAS_MMC_NVIM_OOS_PLMN_SEARCH_STRATEGY_CFG_STRU;

/*****************************************************************************
     : NAS_MMC_NVIM_SKIP_BAND_TYPE_PLMN_SEARCH_CFG_STRU
   : en_NV_Item_Skip_Band_Type_Plmn_Search_Cfg NV

  1.       : 2016627
           : n00355355
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucIsSupportSkipBandTypeSearch;                              /* band */
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucMccNum;                                                   /* band */
    VOS_UINT32                          aulMccList[NAS_MML_NVIM_MAX_SKIP_BAND_TYPE_SEARCH_MCC_NUM]; /* band */
}NAS_MMC_NVIM_SKIP_BAND_TYPE_PLMN_SEARCH_CFG_STRU;

/*****************************************************************************
     : NAS_MMC_NVIM_NON_OOS_PLMN_SEARCH_FEATURE_SUPPORT_CFG_STRU
   : en_NV_Item_Non_Oos_Plmn_Search_Feature_Support_Cfg NV
  1.       : 2015525
           : s00217060
       : 
  2.       : 2017126
           : s00217060
       : 
*****************************************************************************/
typedef struct
{
    /* Modified by s00217060 for DSDS, 2017-1-26, begin */
    VOS_UINT8           ucPrefbandCfg;
    VOS_UINT8           ucSearchTypeAfterHistoryInAreaLostScene;
    VOS_UINT8           ucSearchTypeAfterGetGeoFail;
    VOS_UINT8           ucReserved1;

    VOS_UINT32          ulHistoryCfg;
    VOS_UINT32          ulReserved2;
    /* Modified by s00217060 for DSDS, 2017-1-26, end */
}NAS_MMC_NVIM_NON_OOS_PLMN_SEARCH_FEATURE_SUPPORT_CFG_STRU;


/* Added by s00217060 for , 2016-2-15, begin */
/*****************************************************************************
     : NAS_MMC_NVIM_OOS_BG_NETWORK_SEARCH_CUSTOM_STRU
   : en_NV_Item_OOS_BG_NETWORK_SEARCH_CUSTOM NV
  1.       : 2015525
           : s00217060
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulDelayNetworkSearchTimerLenAfterEmc;   /* :s0 */
    VOS_UINT8                           ucBgHistorySupportFlg;                  /* BGhistory */
    VOS_UINT8                           ucPrefBandListSupportFlg;               /* pref band */
    VOS_UINT8                           ucFullBandListSupportFlg;               /* full band */
    VOS_UINT8                           ucRsv1;
    VOS_UINT8                           ucRsv2;
    VOS_UINT8                           ucRsv3;
    VOS_UINT8                           ucRsv4;
    VOS_UINT8                           ucRsv5;
}NAS_MMC_NVIM_OOS_BG_NETWORK_SEARCH_CUSTOM_STRU;
/* Added by s00217060 for , 2016-2-15, end */

/*****************************************************************************
     : NAS_NVIM_EXTEND_T3240_LEN_CFG_STRU
   : en_NV_Item_EXTEND_T3240_LEN_CFG NV
  1.       : 2016413
           : z00359541
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucExtendT3240LenFlg;                    /* T3240 0: 1: */
    VOS_UINT8                           ucReserve;                              /*  */
    VOS_UINT16                          usCustomizedT3240Len;                   /* T324065535 */
}NAS_NVIM_EXTEND_T3240_LEN_CFG_STRU;

/*****************************************************************************
     : NAS_MMC_NVIM_GET_GEO_PRIO_RAT_LIST_STRU
   : 
  1.       : 2015525
           : s00217060
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucRatOrderNum;                          /*  */
    VOS_UINT8                           aucRatOrder[NAS_NVIM_MAX_RAT_NUM];      /*  */
}NAS_NVIM_GET_GEO_PRIO_RAT_LIST_STRU;

/*****************************************************************************
     : NAS_NVIM_GET_GEO_CFG_INFO_STRU
   : en_NV_Item_Get_Geo_Cfg_Info NVIM
 1.       : 20150522
          : f00179208
      : 
  2.       : 2017126
           : s00217060
       : 
*****************************************************************************/
typedef struct
{
    /* Modified by s00217060 for DSDS, 2017-1-26, begin */
    VOS_UINT8                                               ucGetGeoFlag;   /* GET GEO; GET GEO; GET GEO; 3OOCGET GEO
                                                                                        : 0x07, GET GEO */
    VOS_UINT8                                               ucGetGeoTimerlen;               /*  */
    VOS_UINT8                                               ucScanTypeOfFlightModeGetGeo;   /* GET GEOFFT*/
    VOS_UINT8                                               ucScanTypeOfOocGetGeo;          /* OOC GET GEOFFT*/
    /* Modified by s00217060 for DSDS, 2017-1-26, end */
    VOS_UINT32                                              ulGeoEffectiveTimeLen;          /*  */
    NAS_NVIM_GET_GEO_PRIO_RAT_LIST_STRU                     stGetGeoPrioRatList;            /*  */
}NAS_NVIM_GET_GEO_CFG_INFO_STRU;

/* added by y00176023 for DTS2015091602371 ANYCELLLTE, 2015-9-17, begin */
/*****************************************************************************
     : NAS_NVIM_LOW_PRIO_ANYCELL_SEARCH_LTE_FLG_STRU
   : en_NV_Item_Low_Prio_Anycell_Search_Lte_Cfg NV
  1.       : 2015109
           : w00167002
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucLowPrioAnycellSearchLteFlg;
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
}NAS_NVIM_LOW_PRIO_ANYCELL_SEARCH_LTE_FLG_STRU;
/* added by y00176023 for DTS2015091602371 ANYCELLLTE, 2015-9-17, end */

/*****************************************************************************
     : NAS_NVIM_REFRESH_RPLMN_WHEN_EPLMN_INVALID_CFG_STRU
   : en_NV_Item_REFRESH_RPLMN_WHEN_EPLMN_INVALID_CFG NV
  1.       : 2015109
           : w00167002
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucDeleteRplmnFlg;
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
}NAS_NVIM_REFRESH_RPLMN_WHEN_EPLMN_INVALID_CFG_STRU;

/*****************************************************************************
     : NAS_NVIM_NW_SEARCH_CHR_RECORD_CFG_STRU
   : en_NV_Item_Nw_Search_Chr_Record_Cfg NVIM
 1.       : 20150813
          : f00179208
      : CHR
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucActiveFlag;       /* NV */
    VOS_UINT8                                               ucReserved1;
    VOS_UINT8                                               ucReserved2;
    VOS_UINT8                                               ucReserved3;
    VOS_UINT32                                              ulRecordNum;        /*  */
}NAS_NVIM_NW_SEARCH_CHR_RECORD_CFG_STRU;

/*****************************************************************************
     : CNAS_NVIM_1X_EVDO_PRL_LIST_STRU
   : en_NV_Item_1X_EVDO_PRL_LIST NV
 1.       : 20141103
          : y00245242
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucPrlData[CNAS_NVIM_PRL_SIZE];
}CNAS_NVIM_1X_EVDO_PRL_LIST_STRU;

/*****************************************************************************
     : CNAS_NVIM_CBT_PRL_LIST_STRU
   : en_NV_Item_CBT_PRL_LIST NV
 1.       : 20141103
          : y00245242
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucPrlData[CNAS_NVIM_CBT_PRL_SIZE];
}CNAS_NVIM_CBT_PRL_LIST_STRU;

/*****************************************************************************
     : CNAS_NVIM_1X_HOME_SID_NID_STRU
   : HOME_SID_NID
 1.       : 20141231
          : h00313353
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usSid;
    VOS_UINT16                          usNid;
    VOS_UINT16                          usBand;
    VOS_UINT16                          usReserved;
}CNAS_NVIM_1X_HOME_SID_NID_STRU;

/*****************************************************************************
     : CNAS_NVIM_1X_HOME_SID_NID_LIST_STRU
   : HOME_SID_NID
 1.       : 20141231
          : h00313353
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucSysNum;
    VOS_UINT8                           aucReserve[3];
    CNAS_NVIM_1X_HOME_SID_NID_STRU      astHomeSidNid[CNAS_NVIM_MAX_1X_HOME_SID_NID_NUM];
}CNAS_NVIM_1X_HOME_SID_NID_LIST_STRU;

/*****************************************************************************
     : CNAS_NVIM_1X_SEARCH_INTERVAL_STRU
   : 
 1.       : 20141231
          : h00313353
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usTimes;
    VOS_UINT16                          usTimerLen;
}CNAS_NVIM_OOC_TIMER_INFO_STRU;

/*****************************************************************************
     : CNAS_NVIM_1X_SEARCH_INTERVAL_LIST_STRU
   : 
 1.       : 20141231
          : h00313353
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucMru0SearchTimerLen;
    VOS_UINT8                           ucPhaseNum;
    VOS_UINT8                           uc1xOocDoTchPhase1TimerLen;              /* Do TCH4 Ooc Timer  */
    VOS_UINT8                           uc1xOocDoTchPhase2TimerLen;              /* Do TCH4 Ooc Timer  */
    CNAS_NVIM_OOC_TIMER_INFO_STRU       astOocTimerInfo[CNAS_NVIM_MAX_OOC_SCHEDULE_PHASE_NUM];
}CNAS_NVIM_OOC_TIMER_SCHEDULE_INFO_STRU;
/*****************************************************************************
     : CNAS_NVIM_1X_SEARCH_INTERVAL_LIST_STRU
   : 
 1.       : 20150108
          : h00313353
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucInsertOrigChanFlg;        /*  */
    NAS_NVIM_CHAN_REPEAT_SCAN_ENUM_UINT8                    enChanRepeatScanStrategy;   /* */
    VOS_UINT8                                               aucReserved[2];
}CNAS_NVIM_OOC_REPEAT_SCAN_STRATEGY_INFO_STRU;

/*****************************************************************************
     : CNAS_NVIM_1X_EPDSZID_FEATURE_CFG_STRU
   : EPDSZID Feature Cfg
 1.       : 20150108
          : g00261581
      : 
*****************************************************************************/
typedef struct
{
    NAS_NVIM_EPDSZID_SUPPORT_TYPE_ENUM_UINT8                ucEpdszidType;  /* EPDSZID */
    VOS_UINT8                                               ucHatLen;       /* HATs */
    VOS_UINT8                                               ucHtLen;        /* HTs */
    VOS_UINT8                                               aucReserved[5];
}CNAS_NVIM_1X_EPDSZID_FEATURE_CFG_STRU;

/*****************************************************************************
     : CNAS_NVIM_HRPD_SYSTEM_STRU
   : NVHRDPBANDChannel
 1.       : 20141211
          : h00300778
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                          aucSubnet[CNAS_NVIM_HRPD_SUBNET_LEN];
    VOS_UINT16                         usBandClass;
    VOS_UINT16                         usChannel;
}CNAS_NVIM_HRPD_SYSTEM_STRU;

/*****************************************************************************
     : CNAS_NVIM_HRPD_MRU_LIST_STRU
   : en_NV_Item_HRPD_MRU_LIST NV
 1.       : 20141211
          : h00300778
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucSysNum;
    VOS_UINT8                           aucRsv[3];
    CNAS_NVIM_HRPD_SYSTEM_STRU          astSystem[CNAS_NVIM_MAX_HRPD_MRU_SYS_NUM];
}CNAS_NVIM_HRPD_MRU_LIST_STRU;

/*****************************************************************************
     : CNAS_NVIM_1X_LAST_SCI_STRU
   : en_NV_Item_1X_LAST_SCI NV
 1.       : 201524
          : g00256031
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulSicValue;
}CNAS_NVIM_1X_LAST_SCI_STRU;

/*****************************************************************************
     : NAS_NVIM_WAIT_IMS_VOICE_AVAIL_TIMER_LEN_STRU
   : en_NV_Item_WAIT_IMS_VOICE_AVAIL_Timer_Len NV
 1.       : 2015129
          : y00245242
      : IMS VOICE CAP
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNvimActiveFlag;                       /* 0: nv1:nv */
    VOS_UINT8                           ucWaitImsVoiceAvailTimerLen;            /* IMS VOICE,, */
    VOS_UINT8                           ucWaitImsWithWifiVoiceAvailTimerLen;    /* IMS WIFI,IMS VOICE,, */
    VOS_UINT8                           ucReserved;
}NAS_NVIM_WAIT_IMS_VOICE_AVAIL_TIMER_LEN_STRU;

typedef struct
{
    VOS_UINT32                          ulIsValid;
    VOS_UINT8                           ucLocType;
    VOS_UINT8                           ucLocLen;
    VOS_UINT16                          usSID;
    VOS_UINT16                          usNID;
    VOS_UINT8                           ucPacketZoneID;
    VOS_UINT8                           ucReserve;
}CNAS_NVIM_HRPD_LOC_INFO_STRU;


typedef struct
{
    VOS_UINT32                          ulIsValid;
    VOS_UINT16                          usStrgBLOBType;
    VOS_UINT8                           ucStrgBLOBLen;
    VOS_UINT8                           aucStorageBLOB[CNAS_NVIM_MAX_STORAGE_BLOB_LEN];
    VOS_UINT8                           aucReserve[2];
}CNAS_NVIM_HRPD_STORAGE_BLOB_STRU;

/*****************************************************************************
     : NAS_MMC_NVIM_LTE_REJ_CAUSE_14_CFG_STRU
   : en_NV_Item_LTE_REJ_CAUSE_14_CFG NV
 1.       : 201515
          : h00285180
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucLteRejCause14Flg;               /* LTE #140: 1: */
    VOS_UINT8                           aucReserved[1];
    VOS_UINT16                          usLteRejCause14EnableLteTimerLen; /* LTE #14gudisable lteenable lte: */
}NAS_MMC_NVIM_LTE_REJ_CAUSE_14_CFG_STRU;

/*****************************************************************************
     : NAS_MMC_NVIM_T3396_RUNNING_DISABLE_LTE_CFG_STRU
   : en_NV_Item_T3396_Running_Disable_Lte_Cfg NV

  1.       : 20161115
           : n00355355
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucIsT3396RunningDisableLteFlg;            /* LMM->MMC ATTACH INDT3396disable lte0: 1: */
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
}NAS_MMC_NVIM_T3396_RUNNING_DISABLE_LTE_CFG_STRU;


typedef struct
{
    VOS_UINT32                          ulActiveFlag;
    VOS_UINT32                          ulExpireTimerLen;
    VOS_UINT16                          usMaxNoOfRetry;
    VOS_UINT8                           ucMaxConnFail;
    VOS_UINT8                           aucRsv[1];
}CNAS_EHSM_RETRY_CONN_EST_NVIM_INFO_STRU;


typedef struct
{
    VOS_UINT32                          ulActiveFlag;
    VOS_UINT32                          ulExpireTimerLen;
    VOS_UINT16                          usMaxNoOfRetry;
    VOS_UINT8                           aucRsv[2];
}CNAS_NVIM_EHRPD_PDN_SETUP_RETRY_STRU;

/*****************************************************************************
     : NAS_SMS_PS_CONCATENATE_ENUM
   : PS
  1.       : 20150518
           : j00174725
       : 
*****************************************************************************/
enum NAS_SMS_PS_CONCATENATE_ENUM
{
    NAS_SMS_PS_CONCATENATE_DISABLE      = 0,
    NAS_SMS_PS_CONCATENATE_ENABLE,

    NAS_SMS_PS_CONCATENATE_BUTT
};
typedef VOS_UINT8 NAS_SMS_PS_CONCATENATE_ENUM_UINT8;

/*****************************************************************************
   : NAS_NV_SMS_PS_CTRL_STRU
   : PS

  1.       : 20150518
           : j00174725
       : 
*****************************************************************************/
typedef struct
{
    NAS_SMS_PS_CONCATENATE_ENUM_UINT8   enSmsConcatenateFlag;
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
} NAS_NV_SMS_PS_CTRL_STRU;
/*****************************************************************************
   : NAS_NV_PRIVACY_FILTER_CFG_STRU
   : 

  1.       : 20150917
           : h00313353
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucFilterEnableFlg;
    VOS_UINT8                           aucReserved[3];
} NAS_NV_PRIVACY_FILTER_CFG_STRU;


/*****************************************************************************
 Name    : NAS_NVIM_AVAILABLE_TIMER_CFG_STRU
 Description  : Structure defintion for available timer config used in MSCC
 History     :
  1.Date     : 2015-04-14
    Author   : a00295761
    Modify   : create
  2.Date     : 2016-01-14
    Author   : W00176964
    Modify   : DTS2016011505496:MSPLBSR,NV
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCLOosTimerMaxExpiredTimes;    /* Available Timer */

    VOS_UINT8                           ucCLSysAcqWaitHsdCnfTimerLen;   /* MSCC CLHSD */

    VOS_UINT16                          usReserved1;/* MSPL,bsr */

    VOS_UINT32                          ulFirstSearchAvailTimerLen; /* Contains the Available timer length to be used , when the
                                                                    number of successive triggers is less than ulFirstSearchAvailTimerCount */

    VOS_UINT32                          ulFirstSearchAvailTimerCount; /* For the number successive triggers of avaiable timer less
                                                                      than or equal to ulFirstSearchAvailTimerCount , MSCC uses a timer
                                                                      length value of ulFirstSearchAvailTimerLen */

    VOS_UINT32                          ulDeepSearchAvailTimerLen;  /* For the number successive triggers of avaiable timer greater
                                                                    than ulFirstSearchAvailTimerCount , MSCC uses a timer
                                                                    length value of ulDeepSearchAvailTimerLen */

    VOS_UINT32                          ulScanTimerLen; /* Contains the scan timer length */
    VOS_UINT8                           ucBsrCtrlDoEnterIdleRstLen;     /* BSR 10DOCONNIDLEbsr
                                                                                bsridle  */
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
    VOS_UINT32                          ulSleepTimerLen; /* Contains the sleep timer length */
}NAS_NVIM_MSCC_SYS_ACQ_TIMER_CFG_STRU;



typedef struct
{
    VOS_UINT32                                              ulMcc;
    VOS_UINT32                                              ulMnc;
    VOS_UINT16                                              usSid;
    VOS_UINT16                                              usNid;

    NAS_MSCC_NVIM_SYS_PRI_CLASS_ENUM_UINT8                  en1xPrioClass;
    NAS_MSCC_NVIM_SYS_PRI_CLASS_ENUM_UINT8                  enAIPrioClass;
    VOS_UINT8                                               aucRsv[2];  /* remain four bytes in future */
}NAS_NVIM_1X_LOC_INFO_STRU;

/*****************************************************************************
     : NAS_NVIM_3GPP_LOC_INFO_STRU
   : 3gpp loc info

 1.       : 2015526
          : w00176964
      : 
 2.Date       : 2015-05-29
   Author     : w00176964
   Modify     : DTS2015052903319:add pri class
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                              ulMcc;                                  /* MCC,3 bytes */
    VOS_UINT32                                              ulMnc;                                  /* MNC,2 or 3 bytes */
    NAS_MSCC_NVIM_SYS_PRI_CLASS_ENUM_UINT8                  enPrioClass;
    VOS_UINT8                                               aucRsv[3];  /* remain four bytes in future */
}NAS_NVIM_3GPP_LOC_INFO_STRU;


typedef struct
{
    VOS_UINT8                           ucIsLocInfoUsedInSwitchOn;
    NAS_NVIM_LC_RAT_COMBINED_ENUM_UINT8 enSysAcqMode;
    VOS_UINT8                           ucIs1xLocInfoValid;
    VOS_UINT8                           ucIsLteLocInfoValid;
    NAS_NVIM_1X_LOC_INFO_STRU           st1xLocInfo;
    NAS_NVIM_3GPP_LOC_INFO_STRU         st3gppLocInfo;
}NAS_NVIM_MMSS_LAST_LOCATION_INFO_STRU;


typedef struct
{

    VOS_UINT8                                               ucReAcqLteOnHrpdSyncIndFlag; /* The NVIM Flag controls if
                                                                                                       MSCC must search  for LTE Service
                                                                                                       when HSD sends Sync Ind, if LTE
                                                                                                       is preferred */

    VOS_UINT8                                               ucIs1xLocInfoPrefThanLte;  /* The NVIM Flag controls if CDMA 1x
                                                                                                     Loc info is more preferred than LTe
                                                                                                     Loc Info */
    VOS_UINT8                                               aucReserved[2];
    NAS_NVIM_MSCC_SYS_ACQ_TIMER_CFG_STRU                    stMmssSysAcqTimerCfg;  /* Contains the Timer Configuration
                                                                                                for MMSS System Acquire */
}NAS_NVIM_MMSS_SYSTEM_ACQUIRE_CFG_STRU;



typedef struct
{
    VOS_UINT8                           ucMlplMsplActiveFlag;
    VOS_UINT8                           aucRsv[3];
    VOS_UINT16                          usMlplBufSize;
    VOS_UINT16                          usMsplBufSize;
    VOS_UINT8                           aucMlplBuf[NAS_MSCC_NVIM_MLPL_SIZE];
    VOS_UINT8                           aucMsplBuf[NAS_MSCC_NVIM_MSPL_SIZE];
}NAS_MSCC_NVIM_MLPL_MSPL_STRU;

/*****************************************************************************
     : CNAS_NVIM_1X_MOB_TERM_STRU
   : en_NV_Item_1X_MOB_TERM NV
 1.       : 201562
          : g00256031
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucMobTermForNid;
    VOS_UINT8                           ucMobTermForSid;
    VOS_UINT8                           ucMobTermHome;
    VOS_UINT8                           ucRsv;
}CNAS_NVIM_1X_MOB_TERM_STRU;


typedef struct
{
    VOS_UINT8                           ucActiveFlag;           /* NV item is active not not */
    VOS_UINT8                           ucRsv1;
    VOS_UINT16                          usActTimerLen;          /* Session activate timer length, unit is second */
    VOS_UINT8                           ucMaxActCountConnFail;  /* Max session activate count of reason conntion fail */
    VOS_UINT8                           ucMaxActCountOtherFail; /* Max session activate count of reason other fail */
    VOS_UINT8                           ucRsv2;
    VOS_UINT8                           ucRsv3;
}CNAS_HSM_NVIM_SESSION_RETRY_CFG_STRU;

/*****************************************************************************
 Name    : CNAS_HSM_NVIM_SESSION_CTRL_CFG_STRU
 Description  : Structure definition for en_NV_Item_CNAS_HRPD_Session_Ctrl_Cfg
 History     :
  1.Date     : 2015-09-23
    Author   : m00312079
    Modify   : create
  2.Date     : 2015-12-17
    Author   : m00312079
    Modify   : DTS2015121410637:NVAMP setupopenUATI reqUATI assign
  3.Date     : 2015-12-31
    Author   : m00312079
    Modify   : DTS2015123108077:NVopenUATI reqUATI assign
  4.Date     : 2016-01-16
    Author   : m00312079
    Modify   : DTS2015122603997:NVkeep aliveNV
  5.Date     : 2016-04-05
    Author   : m00312079
    Modify   : DTS2016032810749:UEehrpdNVehrpdNV(ehrpd)
  6.Date     : 2016-05-28
    Author   : m00312079
    Modify   : DTS2016050402784:UATI2000ms
  7.Date     : 2016-07-26
    Author   : m00312079
    Modify   : DTS2016071807950:session closeeHRPD
  8.Date     : 2016-08-13
    Author   : y00307564
    Modify   : DTS2016081509099:NV4GsessioneHRPD
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucStartUatiReqAfterSectorIdChgFlg;   /* RFCCF2.2.2.8NV
                                                                                          NV():sector IDUATI
                                                                                          NV:      C.S0024 7.3.7.1.6.1HO
                                                                                                       Conn Closesector IDUATI */

    VOS_UINT8                           ucWaitUatiAssignTimerLenInAmpSetup; /* :(s),5s.UE
                                                                                        UEUATI assign5s120s() */
    VOS_UINT8                           ucWaitUatiAssignTimerLenInAmpOpen; /* :(s),120s()5s120s*/

    VOS_UINT8                           ucUatiReqRetryTimesWhenUatiAssignTimerExpireInAmpOpen;/* NVopenUATI req
                                                                                                             UATI assign,4 */
    VOS_UINT8                           ucClearKATimerInConnOpenFlg;                          /* NVkeep alive
                                                                                                             NV(): keep alivekeep alive
                                                                                                                           keep alivekeep alive
                                                                                                             NV:       keep alive */
    VOS_UINT8                           ucRecoverEhrpdAvailFlg;                              /* NVUEehrpd,ehrpd
                                                                                                             NV:        ehrpdhrpd
                                                                                                             NV():  ehrpdhrpdrecover */

    VOS_UINT8                           ucRecoverEhrpdCapAfterSessionCloseFlg;              /* NVsession closeeHRPD
                                                                                                             NV:       session closeUEeHRPD(NV)
                                                                                                             NV():  session closeUEeHRPD*/
    VOS_UINT8                           ucCloseEhrpdCapAfterSyscfgNotSupportLteFlg;         /* NV4GsessioneHRPD
                                                                                                             NV:       4GUE eHRPD(NV)
                                                                                                             NV(): UEeHRPD,4GUEeHRPD*/

    VOS_UINT32                          ulUatiSigProtectTimeLen;                             /*  UATI(CTTFUati reqSNP_DATA_CNFUATI assignment)
                                                                                                             1200ms,ms */

    VOS_UINT8                           aucRsv1[20];
}CNAS_HSM_NVIM_SESSION_CTRL_CFG_STRU;


typedef struct
{
    VOS_UINT8                           ucIsKeepAliveInfoValid;    /* If TRUE, then the Keep alive paramters are valid */
    VOS_UINT8                           ucRsv1;                    /* for padding */
    VOS_UINT16                          usTsmpClose;               /* stores the TsmpClose value of the last session. Unit is minutes */
    VOS_UINT32                          ulTsmpCloseRemainTime;     /* Stores the time remaining for Tsmpclose minutes to
                                                                               expire. Unit is seconds */
    VOS_UINT32                          aulLastPowerOffSysTime[2]; /* Stores the CDMA system time at last Power Off.
                                                                              Unit is Milliseconds. */
}CNAS_HSM_NVIM_SESSION_KEEP_ALIVE_INFO_STRU;


typedef struct
{
    VOS_UINT8                           ucEhrpdSupportFlg;       /* EHRPD is support or not */
    VOS_UINT8                           ucRsv1;
    VOS_UINT8                           ucRsv2;
    VOS_UINT8                           ucRsv3;
}NAS_NVIM_EHRPD_SUPPORT_FLG_STRU;


/* Added by c00318887 for , 2015-8-26, begin */
/*****************************************************************************
     : NAS_NVIM_PLMN_SEARCH_PHASE_ONE_TOTAL_TIMER_CFG_STRU
   : en_NV_Item_Plmn_Search_Phase_One_Total_Timer_CFG NV
  1.       : 2015826
           : c00318887
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucActiveFlag;                           /* NV */
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
    VOS_UINT32                          ulTotalTimeLen;                         /* ,:s */
}NAS_NVIM_PLMN_SEARCH_PHASE_ONE_TOTAL_TIMER_CFG_STRU;

/* Added by c00318887 for , 2015-8-26, end */

/*****************************************************************************
     : NAS_MMC_NVIM_CUSTOMIZED_FORB_LA_CFG_STRU
   : en_NV_Item_CS_REG_FAIL_CAUSE_FORB_LA_TIME_CFG NV
  1.       : 2015923
           : z00359541
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usRegFailCauseNum;                      /* ,0 */
    VOS_UINT16                          usForbLaTimeLen;                        /* LA,:s */
    VOS_UINT16                          usPunishTimeLen;                        /*  */
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT16                          ausRegFailCauseList[NAS_MML_NVIM_MAX_REG_FAIL_CAUSE_NUM];
}NAS_MMC_NVIM_CUSTOMIZED_FORB_LA_CFG_STRU;

/*****************************************************************************
   : NAS_NVIM_CSG_AUTONOMOUS_SEARCH_CFG_STRU
   : CSG

  1.       : 2015921
           : z00161729
       : LTE CSG
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usCsgAutonomousSrchFirstSrchTimeLen;                   /* CSG */
    VOS_UINT8                           ucCsgAutonomousSrchFirstSrchTimeCount;                 /* CSG */
    VOS_UINT8                           ucReserved1;
    VOS_UINT16                          usCsgAutonomousSrchSecondSrchTimeLen;                  /* CSG */
    VOS_UINT8                           ucCsgAutonomousSrchSecondSrchTimeCount;                /* CSG */
    VOS_UINT8                           ucReserved2;
} NAS_NVIM_CSG_AUTONOMOUS_SEARCH_CFG_STRU;

/*****************************************************************************
     : NAS_NVIM_PLMN_WITH_CSG_ID_STRU
   : PLMNCSG ID

 1.       : 2015921
          : z00161729
      : LTE CSG
*****************************************************************************/
typedef struct
{
    NVIM_PLMN_VALUE_STRU                stPlmnId;
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT32                          ulCsgId;
}NAS_NVIM_PLMN_WITH_CSG_ID_STRU;


/*****************************************************************************
     : NAS_NVIM_ALLOWED_CSG_LIST_STRU
   : Allowed CSG Listnvallowed CSG List

 1.       : 2015921
          : z00161729
      : LTE CSG
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucPlmnWithCsgIdNum;
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
    NAS_NVIM_PLMN_WITH_CSG_ID_STRU      astPlmnWithCsgIdList[NAS_NVIM_MAX_PLMN_CSG_ID_NUM];
}NAS_NVIM_ALLOWED_CSG_LIST_STRU;
/*****************************************************************************
     : NAS_NVIM_UE_BASED_OPERATOR_CSG_LIST_STRU
   : Operater CSG Listnvoperater CSG List

 1.       : 2016323
          : y00358807
      : LTE CSG
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucPlmnWithCsgIdNum;
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
    NAS_NVIM_PLMN_WITH_CSG_ID_STRU      astPlmnWithCsgIdList[NAS_NVIM_MAX_PLMN_CSG_ID_NUM];
}NAS_NVIM_UE_BASED_OPERATOR_CSG_LIST_STRU;
/*****************************************************************************
    : NAS_NVIM_CSG_DUPLICATE_RPLMN_AND_EPLMN_LIST_STRU
  : CSGRPLMNEPLMN
1.       : 2015921
         : z00161729
     : LTE CSG
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNum;
    VOS_UINT8                           ucRat;                                  /* duplicate rplmn*/
    VOS_UINT8                           aucReserve[2];                          /*NV4*/
    NVIM_PLMN_VALUE_STRU                astRplmnAndEplmnList[NVIM_MAX_EPLMN_NUM];
}NAS_NVIM_CSG_DUPLICATED_RPLMN_AND_EPLMN_LIST_STRU;

/*****************************************************************************
    : NAS_NVIM_CSG_FORBIDDEN_PLMN_CFG_STRU
  : csg
1.       : 2015921
         : z00161729
     : LTE CSG
*****************************************************************************/
typedef struct
{
    /* CSG, */
    VOS_UINT16                          usCsgPlmnForbiddenPeriod;

    /* CSGcsg */
    VOS_UINT8                           ucCauseNum;
    VOS_UINT8                           ucReserved;
    VOS_UINT16                          ausCause[NAS_NVIM_MAX_CSG_REJ_CAUSE_NUM];
}NAS_NVIM_CSG_FORBIDDEN_PLMN_CFG_STRU;
/*****************************************************************************
   : NAS_NVIM_CSG_CTRL_CFG_STRU
   : CSGnv

  1.       : 2015921
           : z00161729
       : LTE CSG
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucBitOp1:1;
    VOS_UINT8                                               ucBitOp2:1;
    VOS_UINT8                                               ucBitOp3:1;
    VOS_UINT8                                               ucBitOp4:1;
    VOS_UINT8                                               ucBitOp5:1;
    VOS_UINT8                                               ucBitOp6:1;
    VOS_UINT8                                               ucBitOp7:1;
    VOS_UINT8                                               ucBitOp8:1;
    VOS_UINT8                                               ucReserved0;
    VOS_UINT8                                               ucIsSupportCsgFlag;             /* VOS_TRUE:UECSG; VOS_FALSE:UECSG */
    VOS_UINT8                                               ucCsgListOnlyReportOperatorCsgListFlag; /* VOS_TRUE:csgoperator csg list; VOS_FALSE:CSGCSG ID */
    NAS_NVIM_CSG_FORBIDDEN_PLMN_CFG_STRU                    stCsgForbiddenPlmnCfg;       /* CSG */
    NAS_NVIM_ALLOWED_CSG_LIST_STRU                          stAllowedCsgList;               /* Allowed CSG List */
    VOS_UINT32                                              ulCsgPeriodicSearchPeriod;      /* CSG, */
    NAS_NVIM_CSG_DUPLICATED_RPLMN_AND_EPLMN_LIST_STRU       stDuplicatedRplmnAndEplmnList;  /* CSGCSGCSGRPLMNEPLMN*/
    NAS_NVIM_CSG_AUTONOMOUS_SEARCH_CFG_STRU                 stCsgAutonomousSrchCfg;         /* CSG */
	NAS_NVIM_UE_BASED_OPERATOR_CSG_LIST_STRU                stUeBasedOperatorCsgList;       /* Based CSG List */
    VOS_UINT8                                               ucRplmnCellType;                /* duplicated RPLMN */
    VOS_UINT8                                               ucReserved1;
    VOS_UINT8                                               ucReserved2;
    VOS_UINT8                                               ucReserved3;
    VOS_UINT32                                              ulReserved1;
} NAS_NVIM_CSG_CTRL_CFG_STRU;

/*****************************************************************************
     : NAS_NVIM_KEEP_CS_FORB_INFO_WHEN_PS_REG_SUCC_STRU
   : PS

 1.       : 20151211
          : z00359541
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucKeepCsForbInfoFlg;
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
}NAS_NVIM_KEEP_CS_FORB_INFO_WHEN_PS_REG_SUCC_STRU;

/*****************************************************************************
     : NAS_NVIM_CLEAR_CKSN_STRU
   : CKSN
 1.       : 201515
          : z00359541
      : 
  2.       : 2016119
           : c00318887
       : nv
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNwIgnoreAuthFailFlg;                  /* CKSN */
    VOS_UINT8                           ucUsimGsmAuthActiveFlg;                            /* USIMGSM2G cs/ps 3GCS/ps CKSN */
    VOS_UINT8                           ucUsimDoneGsmCsAuthFlg;
    VOS_UINT8                           ucUsimDoneGsmPsAuthFlg;
}NAS_NVIM_CLEAR_CKSN_STRU;

/*****************************************************************************
     : NAS_NVIM_ATT_ENS_CTRL_STRU
   : en_NV_Item_ATT_Ctrl_Para(9081) NV

   :
 1.       : 20160215
          : w00167002
      : 

*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNetSelMenuFlg;                        /* VOS_TRUE:VOS_FALSE: */
    VOS_UINT8                           ucRatBalancingFlg;                      /* VOS_TRUE:VOS_FALSE: */
    VOS_UINT8                           aucReserved[2];                         /*  */
}NAS_NVIM_ATT_ENS_CTRL_STRU;


/*****************************************************************************
     : NAS_NVIM_ATT_FRAT_CFG_STRU
   : en_NV_Item_ATT_FRAT_CFG_Info NV

   :
 1.       : 20160419
          : w00167002
      : 

*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEnableFlg;                            /* FRAT */
    VOS_UINT8                           ucIgnitionState;                        /* FRATIgnition */
    VOS_UINT8                           ucImsiPlmnNum;
    VOS_UINT8                           ucFratPlmnNum;

    VOS_UINT32                          ulFratSlowTimerValue;                   /* FRATSlow Timer 180 */
    VOS_UINT32                          ulFratFastTimerValue;                   /* FRATFast Timer 3 */
    NAS_SIM_FORMAT_PLMN_ID              astImsiPlmnIdList[NAS_MML_NVIM_FRAT_MAX_IMSI_NUM];          /* FRATIMSIPLMN */
    NAS_SIM_FORMAT_PLMN_ID              astFratPlmnIdList[NAS_MML_NVIM_FRAT_MAX_PLMN_ID_NUM];       /* FRATPLMN20PLMN */
}NAS_NVIM_ATT_FRAT_CFG_STRU;

/*****************************************************************************
     : NAS_MMC_PAGING_RESPONSE_RETRY_CFG_STRU
   : en_NV_Item_PAGING_RESPONSE_RETRY_CFG NV

   :
 1.       : 201671
          : s00273135
      : 

*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucPagingResponseRetrySupportFlg;        /* 1: 0: */
    VOS_UINT8                           ucPagingResponseRetryPeriod;            /* ,*/
    VOS_UINT8                           ucPagingResoneseRetry2GInterval;        /* 2G, */
    VOS_UINT8                           ucPagingResoneseRetry3GInterval;        /* 3G, */

}NAS_MMC_PAGING_RESPONSE_RETRY_CFG_STRU;
/*****************************************************************************
     : NAS_NVIM_NONREGULAR_SERVICE_CUSTOM_STRU
   : en_NV_Item_Nonregular_Servic_Custom NV

   :
 1.       : 201669
          : n00269697
      : 

*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucTiNonregularCustom;
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
    VOS_UINT8                           ucReserve3;
    VOS_UINT8                           ucReserve4;
    VOS_UINT8                           ucReserve5;
    VOS_UINT8                           ucReserve6;
    VOS_UINT8                           ucReserve7;
}NAS_NVIM_NONREGULAR_SERVICE_CUSTOM_STRU;
/*****************************************************************************
     : NAS_NVIM_HOLD_RETRIEVE_REJ_OPTIMIZE_STRU
   : en_NV_Item_Hold_Retrieve_Rej_Optimize NV

   :
 1.       : 2016624
          : n00269697
      : 

*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucHoldRetrieveRejOptimize;
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
    VOS_UINT8                           ucReserve3;
}NAS_NVIM_HOLD_RETRIEVE_REJ_OPTIMIZE_STRU;

/*****************************************************************************
     : NAS_NVIM_CC_STATUS_ENQUIRY_CFG_STRU
   : CC Status Enquiry
 1.       : 20160721
          : f00179208
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEnableFlag;                           /* VOS_TRUE:,VOS_FALSE: */
    VOS_UINT8                           aucReserved1;
    VOS_UINT8                           aucReserved2;
    VOS_UINT8                           aucReserved3;
}NAS_NVIM_CC_STATUS_ENQUIRY_CFG_STRU;


enum CNAS_NVIM_HRPD_SESSION_STATUS_ENUM
{
    CNAS_NVIM_HRPD_SESSION_STATUS_CLOSE,
    CNAS_NVIM_HRPD_SESSION_STATUS_OPEN,
    CNAS_NVIM_HRPD_SESSION_STATUS_BUTT
};
typedef VOS_UINT8 CNAS_NVIM_HRPD_SESSION_STATUS_ENUM_UINT8;


enum CNAS_NVIM_HRPD_SESSION_TYPE_ENUM
{
    CNAS_NVIM_HRPD_SESSION_TYPE_HRPD,
    CNAS_NVIM_HRPD_SESSION_TYPE_EHRPD,
    CNAS_NVIM_HRPD_SESSION_TYPE_BUTT
};
typedef VOS_UINT8 CNAS_NVIM_HRPD_SESSION_TYPE_ENUM_UINT8;


enum CNAS_NVIM_HARDWARE_ID_TYPE_ENUM
{
    CNAS_NVIM_HARDWARE_ID_TYPE_MEID                    = 0x0000FFFF,
    CNAS_NVIM_HARDWARE_ID_TYPE_ESN                     = 0x00010000,
    CNAS_NVIM_HARDWARE_ID_TYPE_NULL                    = 0x00FFFFFF,
    CNAS_NVIM_HARDWARE_ID_TYPE_BUTT
};
typedef VOS_UINT32 CNAS_NVIM_HARDWARE_ID_TYPE_ENUM_UINT32;


enum CNAS_NVIM_HARDWARE_ID_SRC_TYPE_ENUM
{
    CNAS_NVIM_HARDWARE_ID_SRC_TYPE_NVIM,
    CNAS_NVIM_HARDWARE_ID_SRC_TYPE_RAND,
    CNAS_NVIM_HARDWARE_ID_SRC_TYPE_UIM,
    CNAS_NVIM_HARDWARE_ID_SRC_TYPE_BUTT
};
typedef VOS_UINT32 CNAS_NVIM_HARDWARE_ID_SRC_TYPE_ENUM_UINT32;

/*****************************************************************************
 Structure Name    : CNAS_NVIM_HRPD_UATI_INFO_STRU
 Description       : hrpd uati info structure
 History     :
  1.Date     : 2015-06-03
    Author   : m00312079
    Modify   : create
  2.Date     : 2015-06-18
    Author   : m00312079
    Modify   : DTS2015091604029:nvuati assigngmentsequence number
*****************************************************************************/

typedef struct
{
    VOS_UINT8                           aucCurUATI[CNAS_NVIM_UATI_OCTET_LENGTH];
    VOS_UINT8                           ucUATIColorCode;
    VOS_UINT8                           ucUATISubnetMask;
    VOS_UINT8                           ucUATIAssignMsgSeq;
    VOS_UINT8                           ucRsv2;
}CNAS_NVIM_HRPD_UATI_INFO_STRU;


typedef struct
{
    CNAS_NVIM_HARDWARE_ID_TYPE_ENUM_UINT32                  enHwidType;
    CNAS_NVIM_HARDWARE_ID_SRC_TYPE_ENUM_UINT32              enHwidSrcType;
    VOS_UINT32                                              ulEsn;                                /* 32-bit */
    VOS_UINT8                                               aucMeId[CNAS_NVIM_MEID_OCTET_NUM];    /* 56-bit */
    VOS_UINT8                                               ucRsv1;
}CNAS_NVIM_HARDWARE_ID_INFO_STRU;


typedef struct
{
    VOS_INT32                           lLongitude;
    VOS_INT32                           lLatitude;
}CNAS_NVIM_LOC_INFO_STRU;


typedef struct
{
    CNAS_NVIM_HRPD_SESSION_STATUS_ENUM_UINT8                enSessionStatus;
    CNAS_NVIM_HRPD_SESSION_TYPE_ENUM_UINT8                  enSessionType;
    VOS_UINT8                                               aucIccid[CNAS_NVIM_ICCID_OCTET_LEN];
    CNAS_NVIM_HRPD_UATI_INFO_STRU                           stUatiInfo;
    CNAS_NVIM_LOC_INFO_STRU                                 stLocInfo;
    CNAS_NVIM_HARDWARE_ID_INFO_STRU                         stHwid;
}CNAS_NVIM_HRPD_SESSION_INFO_STRU;


typedef struct
{
    PS_BOOL_ENUM_UINT8                  enSuppOnlyDo0;                          /* DO0 */
    PS_BOOL_ENUM_UINT8                  enSuppDoaWithMfpa;                      /* DOAMFPA */
    PS_BOOL_ENUM_UINT8                  enSuppDoaWithEmfpa;                     /* DOAMFPAEMPA */
    PS_BOOL_ENUM_UINT8                  enSuppDoaEhrpd;                         /* eHRPD */
}CNAS_NVIM_HRPD_UE_REV_INFO_STRU;

/*****************************************************************************
 Name    : CNAS_NVIM_HRPD_SESSION_INFO_EX_STRU
 Description  : Structure definition for en_Nv_Item_HRPD_Session_Info_Ex
 History     :
  1.Date     : 2015-09-18
    Author   : m00312079
    Modify   : create
  2.Date     : 2015-12-21
    Author   : m00312079
    Modify   : DTS2015120208895,sessionUE
  3.Date     : 2016-08-25
    Author   : y00307564
    Modify   : sessionseed
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulSessionSeed;
    CNAS_NVIM_HRPD_UE_REV_INFO_STRU     stUERevInfo;
    VOS_UINT8                           ucLteRegSuccFlg;
    VOS_UINT8                           aucReserve1[3];
    VOS_UINT32                          ulPseudorandomNumber;  /* sessionseed */
    VOS_UINT8                           aucReserve2[4];
}CNAS_NVIM_HRPD_SESSION_INFO_EX_STRU;

/*****************************************************************************
    : NAS_NVIM_TIME_INFO_REPORT_OPTIMIZE_CFG_STRU
  : en_NV_Item_Time_Info_Report_Cfg(2434) 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucRptOptType;                           /*  0:1:^TIME */
                                                                                /*  2:03:1 */
    VOS_UINT8                           ucInterval;                             /* RptOptType3min0-255 */
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
}NAS_NVIM_TIME_INFO_REPORT_OPTIMIZE_CFG_STRU;


typedef struct
{
    VOS_UINT8                           ucAccessAuthAvailFlag;
    VOS_UINT8                           ucAccessAuthUserNameLen;
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           aucAccessAuthUserName[CNAS_NVIM_MAX_AUTHDATA_USERNAME_LEN];
}CNAS_NVIM_HRPD_ACCESS_AUTH_INFO_STRU;

/*****************************************************************************
     : NAS_NVIM_EMC_UNDER_NET_PIN_CFG_STRU
   : en_NV_Item_Emc_Under_Net_Pin_Cfg(2433)  VDF
 1.       : 20170113
          : z00359541
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucUseImsiFlg;                           /* VDFIMSI */
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
}NAS_NVIM_EMC_UNDER_NET_PIN_CFG_STRU;

/*****************************************************************************
     : NAS_NVIM_PS_REG_FAIL_MAX_TIMES_TRIG_LAU_ONCE_CFG_STRU
   : AttachRAULAU
 1.       : 20150813
          : l00289540
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                 ucPsRegFailMaxTimesTrigLauOnceFlg;
    VOS_UINT8                 ucReserved1;
    VOS_UINT8                 ucReserved2;
    VOS_UINT8                 ucReserved3;
}NAS_NVIM_PS_REG_FAIL_MAX_TIMES_TRIG_LAU_ONCE_CFG_STRU;

/*****************************************************************************
     : NAS_NVIM_KEEP_SRCH_HPLMN_EVEN_REJ_BY_CAUSE_13_CFG_STRU
   : HPLMN#13HPLMN WITH RAT
 1.       : 20150813
          : l00289540
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                 ucKeepSrchHplmnEvenRejByCause13Flg;
    VOS_UINT8                 ucReserved1;
    VOS_UINT8                 ucReserved2;
    VOS_UINT8                 ucReserved3;
}NAS_NVIM_KEEP_SRCH_HPLMN_EVEN_REJ_BY_CAUSE_13_CFG_STRU;

/*****************************************************************************
     : NAS_NVIM_EPS_REJ_BY_CAUSE_14_IN_VPLMN_ALLOW_PS_REG_CFG_STRU
   : VPLMN LTE#142/3G PS
 1.       : 20150813
          : l00289540
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                 ucEpsRejByCause14InVplmnAllowPsRegFlg;
    VOS_UINT8                 ucReserved1;
    VOS_UINT8                 ucReserved2;
    VOS_UINT8                 ucReserved3;
}NAS_NVIM_EPS_REJ_BY_CAUSE_14_IN_VPLMN_ALLOW_PS_REG_CFG_STRU;

/*****************************************************************************
     : NAS_MMC_NVIM_CARRY_EPLMN_SWITCH_FLAG_ENUM
   : RPLMNEPLMN
 1.    : 2015813
       : l00289540
   : 
*****************************************************************************/
enum NAS_MMC_NVIM_CARRY_EPLMN_SWITCH_FLAG_ENUM
{
    NAS_MMC_NVIM_CARRY_EPLMN_SWITCH_OFF                     = 0,           /*  */
    NAS_MMC_NVIM_CARRY_EPLMN_SWITCH_ON_FOR_ROAM             = 1,           /*  */
    NAS_MMC_NVIM_CARRY_EPLMN_SWITCH_ON_FOR_ALL              = 2,           /*  */
    NAS_MMC_NVIM_CARRY_EPLMN_SWITCH_BUTT
};
typedef VOS_UINT8 NAS_MMC_NVIM_CARRY_EPLMN_SWITCH_FLAG_ENUM_UINT8;

/*****************************************************************************
     : NAS_NVIM_CARRY_EPLMN_WHEN_SRCH_RPLMN_CFG_STRU
   : RPLMNEPLMNNV
 1.       : 20150813
          : l00289540
      : 
*****************************************************************************/
typedef struct
{
    NAS_MMC_NVIM_CARRY_EPLMN_SWITCH_FLAG_ENUM_UINT8         enSwitchFlag;
    VOS_UINT8                                               ucCarryEplmnSceneSwitchOn;
    VOS_UINT8                                               ucCarryEplmnSceneAreaLost;
    VOS_UINT8                                               ucCarryEplmnSceneAvailableTimerExpired;
    VOS_UINT8                                               ucCarryEplmnSceneSysCfgSet;
    VOS_UINT8                                               ucCarryEplmnSceneDisableLte;
    VOS_UINT8                                               ucCarryEplmnSceneEnableLte;
    VOS_UINT8                                               ucCarryEplmnSceneCSFBServiceRej;
    VOS_UINT8                                               ucReserved1;
    VOS_UINT8                                               ucReserved2;
    VOS_UINT8                                               ucReserved3;
    VOS_UINT8                                               ucReserved4;
}NAS_NVIM_CARRY_EPLMN_WHEN_SRCH_RPLMN_CFG_STRU;

/*****************************************************************************
     : NAS_NVIM_TELCEL_PDP_ACT_LIMIT_CFG_STRU
   : PDP
  1.       : 20161025
           : s00217060
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucActiveFlg;                                                /*  */
    VOS_UINT8                           ucRetryTimerLenOnLte;                                       /* LTEPDP retrys */
    VOS_UINT8                           ucRetryTimerLenOnGu;                                        /* GUPDP retrys */
    VOS_UINT8                           ucLimitTimerLenAfterMaxCnt;                                 /* PDPPDPmin */
    VOS_UINT8                           ucMaxRetryCnt;                                              /* retry */
    VOS_UINT8                           ucReserve;
    VOS_UINT8                           ucPlmnNum;
    VOS_UINT8                           ucCauseNum;
    NAS_SIM_FORMAT_PLMN_ID              astPlmnIdList[NAS_NVIM_MAX_LIMIT_PDP_ACT_PLMN_NUM];         /*  */
    VOS_UINT8                           aucCauseList[NAS_NVIM_MAX_LIMIT_PDP_ACT_CAUSE_NUM];         /*  */
}NAS_NVIM_TELCEL_PDP_ACT_LIMIT_CFG_STRU;
/* Added by z00359541 for PhaseI, 2016-8-19, begin */
/*****************************************************************************
     : NAS_NVIM_BORDER_PLMN_SEARCH_CFG_STRU
   : 
 1.       : 20160819
          : z00359541
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                 ucSwitchOnBorderPlmnSearchFlg;                 /*  VOS_TRUE: VOS_FALSE: */
    VOS_UINT8                 ucBorderBgSearchFlg;                              /*  VOS_TRUE: VOS_FALSE: */
    VOS_UINT8                 ucReserved1;
    VOS_UINT8                 ucReserved2;
}NAS_NVIM_BORDER_PLMN_SEARCH_CFG_STRU;
/* Added by z00359541 for PhaseI, 2016-8-19, end */

/*****************************************************************************
 Name    : CNAS_NVIM_HOME_SID_NID_DEPEND_ON_PRL_CFG_STRU
 Description  : Structure definition for en_NV_Item_HOME_SID_NID_PRI_CFG
                HOME SID/NIDVOS_TRUEhome SID/NID
                PRLVOS_FALSEhome SID/NID
                PRLNEGroaming
 History     :
  1.Date     : 2015-07-02
    Author   : w00242748
    Modify   : create
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucHomeSidNidDependOnPrlFlg;
    VOS_UINT8                           aucReserved[3];
}CNAS_NVIM_HOME_SID_NID_DEPEND_ON_PRL_CFG_STRU;

/*****************************************************************************
     : CNAS_NVIM_SYS_INFO_STRU
   : SIDMCCMCCSIDSID

 1.       : 201572
          : w00242748
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usStartSid;
    VOS_UINT16                          usEndSid;
    VOS_UINT32                          ulMcc;
}CNAS_NVIM_SYS_INFO_STRU;

/*****************************************************************************
     : CNAS_NVIM_OPER_LOCK_WHITE_SID_STRU
   : en_NV_Item_OPER_LOCK_WHITE_SID_INFO NV
  1.       : 201572
           : w00242748
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEnable;                          /*  */
    VOS_UINT8                           ucReserved;
    VOS_UINT16                          usWhiteSysNum;                     /* ,0 */
    CNAS_NVIM_SYS_INFO_STRU             astSysInfo[CNAS_NVIM_MAX_WHITE_LOCK_SYS_NUM];
}CNAS_NVIM_OPER_LOCK_SYS_WHITE_LIST_STRU;

/*****************************************************************************
     : CNAS_NVIM_FREQENCY_CHANNEL_STRU
   : 
  1.       : 201573
           : w00242748
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usChannel;
    VOS_UINT8                           aucReserved[2];
}CNAS_NVIM_FREQENCY_CHANNEL_STRU;

/*****************************************************************************
     : CNAS_NVIM_CTCC_CUSTOMIZE_FREQ_LIST_STRU
   : 
  1.       : 201573
           : w00242748
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEnableFlg;
    VOS_UINT8                           ucReserved;
    VOS_UINT16                          usFreqNum;
    CNAS_NVIM_FREQENCY_CHANNEL_STRU     astFreqList[CNAS_NVIM_MAX_HRPD_CUSTOMIZE_FREQ_NUM];
}CNAS_NVIM_CTCC_CUSTOMIZE_FREQ_LIST_STRU;

/*****************************************************************************
     : CNAS_NVIM_CDMA_STANDARD_CHANNELS_STRU
   : CDAM standard channels
  1.       : 2015714
           : y00245242
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usPrimaryA;
    VOS_UINT16                          usPrimaryB;
    VOS_UINT16                          usSecondaryA;
    VOS_UINT16                          usSecondaryB;
}CNAS_NVIM_CDMA_STANDARD_CHANNELS_STRU;


typedef struct
{
    VOS_UINT32                                              ulEnableFlag;
}CNAS_NVIM_NO_CARD_MODE_CFG_STRU;

/*****************************************************************************
     : CNAS_NVIM_EMC_REDIAL_SYS_ACQ_CFG_STRU
   : en_NV_Item_EMC_REDIAL_SYS_ACQ_CFG NV
  1.       : 20151026
           : c00299063
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               aucRedialTimes[CNAS_NVIM_1X_MAX_MRU_SYS_NUM];  /* mru list*/
}CNAS_NVIM_1X_EMC_REDIAL_SYS_ACQ_CFG_STRU;

/*****************************************************************************
     : CNAS_NVIM_1X_AVOID_PHASE_NUM
   : avoid
  1.       : 20151123
           : c00299063
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucAvoidTimerLen[CNAS_NVIM_1X_AVOID_MAX_PHASE_NUM];
}CNAS_NVIM_1X_AVOID_PHASE_NUM;

/*****************************************************************************
     : CNAS_NVIM_1X_AVOID_SCHEDULE_INFO_STRU
   : avoid
  1.       : 20151123
           : c00299063
       : 
*****************************************************************************/
typedef struct
{
    CNAS_NVIM_1X_AVOID_PHASE_NUM        astAvoidPhaseNum[CNAS_NVIM_1X_AVOID_REASON_MAX];
}CNAS_NVIM_1X_AVOID_SCHEDULE_INFO_STRU;

/*****************************************************************************
     : CNAS_NVIM_1X_POWER_OFF_CAMP_ON_CTRL_STRU
   : en_CNAS_NVIM_1X_POWER_OFF_CAMP_ON_CTRL_STRU NV
  1.       : 20151026
           : c00299063
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucPowerOffCampOnCtrlFlg;
    VOS_UINT8                                               aucReserved[3];
}CNAS_NVIM_1X_POWER_OFF_CAMP_ON_CTRL_STRU;

/*****************************************************************************
     : CNAS_NVIM_1X_PRL_ROAM_IND_STRATEGY_CFG_STRU
   : en_NV_Item_1X_PRL_ROAM_IND_STRATEGY_CFG NV
  1.       : 20160305
           : h00313353
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucIsConsiderRoamIndInPRLFlg;        /* PRLROAM IND */
    VOS_UINT8                                               ucReserved1;
    VOS_UINT8                                               ucReserved2;
    VOS_UINT8                                               ucReserved3;
} CNAS_NVIM_1X_PRL_ROAM_IND_STRATEGY_CFG_STRU;

/*****************************************************************************
     : CNAS_NVIM_1X_SYS_ACQ_NO_RF_PROTECT_TIMER_CFG_STRU
   : en_NV_Item_1X_SYS_ACQ_NO_RF_PROTECT_TIMER_CFG NV
  1.       : 2016225
           : Y00322978
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                              ul1xSysAcqNoRfProtectTimerLen;
    VOS_UINT32                                              ul1xRedirNoRfProtectTimerLen;
    VOS_UINT32                                              ulHrpdSysAcqNoRfProtectTimerLen;
    VOS_UINT8                                               aucReserved[4];
}CNAS_NVIM_1X_DO_SYS_ACQ_NO_RF_PROTECT_TIMER_CFG_STRU;

/*****************************************************************************
     : CNAS_NVIM_LTE_DO_CONN_INTERUPT_1X_SYS_ACQ_CFG_STRU
   : en_NV_Item_LTE_DO_CONN_INTERUPT_1X_SYS_ACQ_CFG NV
  1.       : 2016225
           : Y00322978
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucLteDoConnInterrupt1xSysAcqFlg;
    VOS_UINT8                                               ucReserved1;
    VOS_UINT8                                               ucReserved2;
    VOS_UINT8                                               ucReserved3;
}CNAS_NVIM_LTE_DO_CONN_INTERUPT_1X_SYS_ACQ_CFG_STRU;

/*****************************************************************************
     : CNAS_NVIM_LTE_OR_DO_CONN_1X_SYS_ACQ_SYNC_DELAY_INFO_STRU
   : en_NV_Item_1X_SYS_ACQ_DELAY_TIMER_CFG_WHEN_LTE_DO_CONN NV
  1.       : 2016328
           : Y00322978
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                              ul1xSysAcqDelayTimerLen;
    VOS_UINT8                                               uc1xSysAcqSyncDelayEnable;
    VOS_UINT8                                               auc1xSysAcqSyncDelayFreqNum[3];             //  sync
}CNAS_NVIM_LTE_OR_DO_CONN_1X_SYS_ACQ_SYNC_DELAY_INFO_STRU;

/*****************************************************************************
     : NAS_MMC_NVIM_LTE_OOS_2G_PREF_PLMN_SEL_CFG_STRUs
   : en_NV_Item_LTE_OOS_2G_PREF_PLMN_SEL_CFG NV
  1.       : 20150703
           : h00285180
       : 

    ucImsiPlmnListNum   SIM16
    astImsiPlmnList     SIM16;
*****************************************************************************/
typedef struct
{
    VOS_UINT8                          ucImsiListNum;                                                  /*SIM(LTE OOS2G3G)  */
    VOS_UINT8                          ucReserved1;
    VOS_UINT8                          ucReserved2;
    VOS_UINT8                          ucReserved3;
    NAS_SIM_FORMAT_PLMN_ID             astImsiList[NAS_NVIM_LTE_OOS_2G_PREF_PLMN_SEL_MAX_IMSI_LIST_NUM];/* SIM (LTE OOS2G3G) */
}NAS_MMC_NVIM_LTE_OOS_2G_PREF_PLMN_SEL_CFG_STRU;

/*****************************************************************************
     : CNAS_NVIM_CUSTOM_FREQUENCY_CHANNEL_STRU
   : 
  1.       : 201573
           : h00313353
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usChannel;
    VOS_UINT16                          usBandClass;
} CNAS_NVIM_CUSTOM_FREQUENCY_CHANNEL_STRU;

/*****************************************************************************
     : CNAS_NVIM_CDMA_1X_PREF_CHANNELS_STRU
   : 1X
  1.       : 201573
           : h00313353
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                               ucEnableFlg;
    VOS_UINT8                               ucReserved;
    VOS_UINT16                              usFreqNum;
    CNAS_NVIM_CUSTOM_FREQUENCY_CHANNEL_STRU astFreqList[CNAS_NVIM_MAX_CDMA_1X_CUSTOM_PREF_CHANNELS_NUM];
} CNAS_NVIM_CDMA_1X_CUSTOM_PREF_CHANNELS_STRU;

/*****************************************************************************
     : CNAS_NVIM_CDMA_1X_CUSTOMIZE_PREF_CHANNELS_STRU
   : 1X
  1.       : 201573
           : h00313353
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                               ucEnableFlg;
    VOS_UINT8                               ucReserved;
    VOS_UINT16                              usFreqNum;
    CNAS_NVIM_CUSTOM_FREQUENCY_CHANNEL_STRU astFreqList[CNAS_NVIM_MAX_CDMA_1X_CUSTOMIZE_PREF_CHANNELS_NUM];
} CNAS_NVIM_CDMA_1X_CUSTOMIZE_PREF_CHANNELS_STRU;

/*****************************************************************************
     : NAS_NVIM_DYNLOAD_CTRL_STRU
   : 
  1.       : 2015812
           : w00242748
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEnableDynloadTW;
    VOS_UINT8                           ucReseverd1;
    VOS_UINT8                           ucReseverd2;
    VOS_UINT8                           ucReseverd3;
}NAS_NVIM_DYNLOAD_CTRL_STRU;

/*****************************************************************************
     : NAS_NVIM_DYNLOAD_EXCEPTION_CTRL_STRU
   : 
  1.       : 20151112
           : w00242748
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucTWMaxAttemptCount;
    VOS_UINT8                           ucReseverd1;
    VOS_UINT8                           ucReseverd2;
    VOS_UINT8                           ucReseverd3;
}NAS_NVIM_DYNLOAD_EXCEPTION_CTRL_STRU;

/*****************************************************************************
     : CNAS_NVIM_1X_PAGING_RSP_SO_CFG_STRU
   : en_NV_Item_1X_PAGING_RSP_SO_CFG NV
 1.       : 20151102
          : L00301449
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNoDataSrvRspSo33;                     /* Paging rsp0 - Paging RspSO0 1 - Paging RspSO33 */
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
}CNAS_NVIM_1X_PAGING_RSP_SO_CFG_STRU;



/*****************************************************************************
     : NAS_NVIM_PROGRESS_INDICATOR_START_T310_INFO_STRU
   : en_NV_Item_PROGRESS_INDICATOR_START_T310_INFO NV
 1.       : 20151010
          : j00174725
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucIsStartT310AccordWith3GPP;            /* proceedingprogressprogress indicator#1#2#64
                                                                                   T310, 0 - ;  1 -   */
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
}NAS_NVIM_PROGRESS_INDICATOR_START_T310_INFO_STRU;

/*****************************************************************************
     : NAS_NVIM_CDATA_DISCING_PARA_INFO_STRU
   : en_NV_Item_CDATA_DISCING_PARA_CFG NV
 1.       : 20151111
          : g00261581
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucPppDeactTimerLen;                     /* (S), PPP */
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
}NAS_NVIM_CDATA_DISCING_PARA_INFO_STRU;
/*****************************************************************************
     : NAS_NVIM_PPP_AUTH_INFO_FROM_CARD_STRU
   : en_NV_Item_PPP_AUTH_INFO_FROM_CARD_FLAG NV
 1.       : 20151111
          : Y00322978
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulIsPppAuthGetFromCard;
}NAS_NVIM_PPP_AUTH_INFO_FROM_CARD_STRU;

/*****************************************************************************
     : NAS_NVIM_EHRPD_AUTO_ATTACH_CTRL_CFG_STRU
   : en_NV_Item_EHRPD_AUTO_ATTACH_CTRL_CFG NV
 1.       : 20151226
          : g00261581
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEnableFlag;                           /* VOS_TRUE:Auto attachVOS_FALSE:Auto attach */
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
}NAS_NVIM_EHRPD_AUTO_ATTACH_CTRL_CFG_STRU;

/*****************************************************************************
     : CNAS_NVIM_1X_CALL_ENCVOICE_ECC_SRV_CAP_INFO_STRU
   : ECC
             : ECCECC

       :
  1.       : 2015-11-11
           : l00359089
       : Iteration 19
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEccSrvCap;        /* ECC: TRUE -- ECCFALSE -- ECC */
    VOS_UINT8                           ucEccSrvStatus;     /* ECC: TRUE -- ECCFALSE -- ECC */
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
} CNAS_NVIM_1X_CALL_ENCVOICE_ECC_SRV_CAP_INFO_STRU;


/*****************************************************************************
     : NAS_NVIM_1X_SERVICE_CL_SYSTEM_ACQUIRE_PATTERN_CFG_STRU
   : 1XCL
       :
  1.       : 2015-12-10
           : w00176964
       : CL_MUTIMODE_OPTIMIZE
  2.       : 2016-6-4
           : w00176964
       : CL_MULTIMODE_OPTIMIZE_V2
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usTotalTimeLen;         /* , */
    VOS_UINT16                          usSleepTimeLen;         /* available, */
    VOS_UINT16                          usReserve1;
    VOS_UINT16                          usReserve2;
    VOS_UINT8                           ucLteHistorySrchNum;       /* LTE */
    VOS_UINT8                           ucLteFullBandSrchNum;      /* LTE */
    VOS_UINT8                           ucLtePrefBandSrchNum;      /* LTE pref band */
    VOS_UINT8                           ucReserve2;
    VOS_UINT8                           ucReserve3;
    VOS_UINT8                           ucReserve4;
    VOS_UINT8                           ucReserve5;
    VOS_UINT8                           ucReserve6;
} NAS_NVIM_1X_SERVICE_CL_SYSTEM_ACQUIRE_PATTERN_CFG_STRU;

/*****************************************************************************
     : NAS_NVIM_1X_SERVICE_CL_SYSTEM_ACQUIRE_CTRL_STRU
   : 1XCL
       :
  1.       : 2015-12-21
           : w00176964
       : CL_MUTIMODE_OPTIMIZE
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           uc1xBsrLteActiveFlg;                /* 1XBSR LTE--CCF */
    VOS_UINT8                           uc1xBsrLteTimerLen;                 /* 1XBSR LTE- */
    VOS_UINT8                           ucSrlte1xBsrLteEnableFlg;           /* SRLTE1xBSR LTE */
    VOS_UINT8                           ucReserve4;
    VOS_UINT8                           ucReserve5;
    VOS_UINT8                           ucReserve6;
    VOS_UINT8                           ucReserve7;
    VOS_UINT8                           ucReserve8;
} NAS_NVIM_1X_SERVICE_CL_SYSTEM_ACQUIRE_CTRL_STRU;


/*****************************************************************************
     : NAS_NVIM_1X_SERVICE_CL_SYSTEM_ACQUIRE_STRATEGY_CFG_STRU
   : 1XCLNV
       :
  1.       : 2015-12-10
           : w00176964
       : CL_MUTIMODE_OPTIMIZE
*****************************************************************************/
typedef struct
{
    NAS_NVIM_1X_SERVICE_CL_SYSTEM_ACQUIRE_CTRL_STRU         stCtrlInfo;
    NAS_NVIM_1X_SERVICE_CL_SYSTEM_ACQUIRE_PATTERN_CFG_STRU  stPhaseOnePatternCfg;   /*  */
    NAS_NVIM_1X_SERVICE_CL_SYSTEM_ACQUIRE_PATTERN_CFG_STRU  stPhaseTwoPatternCfg;   /*  */
    NAS_NVIM_1X_SERVICE_CL_SYSTEM_ACQUIRE_PATTERN_CFG_STRU  stPhaseThreePatternCfg; /* :, */
} NAS_NVIM_1X_SERVICE_CL_SYSTEM_ACQUIRE_STRATEGY_CFG_STRU;
/*****************************************************************************
     : NAS_NVIM_LTE_OOS_DELAY_ACTIVATE_1X_TIMER_INFO_STRU
   : lteVoLTE1x
       :
  1.       : 2015-12-21
           : y00322978
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucLteOos1xActDelayTimerLen;   /* VOLTE,lte oos1x,(s) */

    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
    VOS_UINT8                           ucReserve3;
    VOS_UINT8                           ucReserve4;
    VOS_UINT8                           ucReserve5;
    VOS_UINT8                           ucReserve6;
    VOS_UINT8                           ucReserve7;
} NAS_NVIM_LTE_OOS_DELAY_ACTIVATE_1X_TIMER_INFO_STRU;


/*****************************************************************************
     : NAS_NVIM_CL_VOLTE_CFG_INFO_STRU
   : CLIMS
       :
  1.       : 2016-10-13
           : g00261581
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucClImsSupportFlag;             /* CLIMS */

    VOS_UINT8                           ucClEnhanceVolteFlag;           /* cdma normal volte flag, effective only when ucClImsSupportFlag is true
                                                                                  0: normal volte , voltesrlteapLTEIMSSWITHC;
                                                                                  1: enhance volte,  voltesrlte  */

    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
    VOS_UINT32                          ulDisableLteTimerLen;           /*  : */
    VOS_UINT8                           ucPingPongCtrlTimerLen;           /*  : */
    VOS_UINT8                           ucMaxPingPongNum;                 /*  */
    VOS_UINT8                           ucReserve3;
    VOS_UINT8                           ucReserve4;
} NAS_NVIM_CL_VOLTE_CFG_INFO_STRU;

/*****************************************************************************
     : CNAS_NVIM_1X_SEARCH_INTERVAL_LIST_STRU
   : 
 1.       : 20160112
          : z00316370
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucMru0SearchTimerLen;
    VOS_UINT8                           ucPhaseNum;
    VOS_UINT8                           ucHrpdMru0TimerMaxExpiredTimes; /* HRPD MRU0 */
    VOS_UINT8                           ucReserved;
    CNAS_NVIM_OOC_TIMER_INFO_STRU       astOocTimerInfo[CNAS_NVIM_MAX_HRPD_OOC_SCHEDULE_PHASE_NUM];
}CNAS_NVIM_HRPD_OOC_TIMER_SCHEDULE_INFO_STRU;

/*****************************************************************************
     : NAS_NVIM_CL_SYSTEM_ACQUIRE_DSDS_STRATEGY_CFG_STRU
   : DSDS
       :
  1.       : 2016-2-2
           : w00176964
       : DTS2016013006596
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucReAcqLteWithNoRfEnable;           /* lte no rflte */
    NAS_NVIM_CL_SYS_ACQ_DSDS_STRATEGY_SCENE_ENUM_UINT8      enReAcqLteWithNoRfScene;            /* lte no rflte */
    VOS_UINT8                                               ucReAcqLteWithNoRfDelayTime;        /* lte no rflte- */
    VOS_UINT8                                               ucRsv1;
    VOS_UINT16                                              usRsv1;
    VOS_UINT16                                              usRsv2;
    VOS_UINT8                                               ucRsv2;
    VOS_UINT8                                               ucRsv3;
    VOS_UINT8                                               ucRsv4;
    VOS_UINT8                                               ucRsv5;
    VOS_UINT8                                               ucRsv6;
    VOS_UINT8                                               ucRsv7;
    VOS_UINT8                                               ucRsv8;
    VOS_UINT8                                               ucRsv9;
}NAS_NVIM_CL_SYSTEM_ACQUIRE_DSDS_STRATEGY_CFG_STRU;


/*****************************************************************************
     : CNAS_NVIM_1X_OOS_SYS_ACQ_STRATEGY_CTRL_STRU
   : 1X OOS
 1.       : 20151222
          : w00176964
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucPhaseNum;                 /*  */
    NAS_NVIM_CHAN_REPEAT_SCAN_ENUM_UINT8                    enChanRepeatScanStrategy;   /*  */
    VOS_UINT16                                              usReserved;
    VOS_UINT8                                               uc1xOocDoTchPhase1TimerLen; /* Do TCH4 Ooc Timer , */
    VOS_UINT8                                               uc1xOocDoTchPhase2TimerLen; /* Do TCH4 Ooc Timer , */
    VOS_UINT16                                              usRsv1;
    VOS_UINT8                                               uc1xMru0TimerMaxExpiredTimes;   /* MRU0MRU0 */
    VOS_UINT8                                               ucRsv2;
    VOS_UINT8                                               ucRsv3;
    VOS_UINT8                                               ucRsv4;
}CNAS_NVIM_1X_OOS_SYS_ACQ_STRATEGY_CTRL_STRU;

/*****************************************************************************
     : CNAS_NVIM_1X_OOS_SYS_ACQ_STRATEGY_PATTERN_STRU
   : 1X OOS
 1.       : 20151222
          : w00176964
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usTotalTimeLen;         /* 1x, */
    VOS_UINT16                          usSleepTimeLen;         /* 1x, */
    VOS_UINT8                           ucSrchNum;              /* 1x */
    VOS_UINT8                           ucRsv1;
    VOS_UINT8                           ucRsv2;
    VOS_UINT8                           ucRsv3;
    VOS_UINT16                          usMru0SearchTimerLen;       /* MRU0available,, */

    VOS_UINT16                          usModem0MinSleepTimerLen;     /* 1xSleepTimeLen,usSleepTimeLenucMinSleepTimerLen, */

    VOS_UINT8                           ucModem1MinSleepTimerLen; /* 1xSleepTimeLen,usSleepTimeLenucMinSleepTimerLen, */
    VOS_UINT8                           ucModem2MinSleepTimerLen;  /* 1xSleepTimeLen,usSleepTimeLenucMinSleepTimerLen, */
    VOS_UINT8                           ucRsv6;
    VOS_UINT8                           ucRsv7;
}CNAS_NVIM_1X_OOS_SYS_ACQ_STRATEGY_PATTERN_STRU;

/*****************************************************************************
     : CNAS_NVIM_1X_OOS_SYS_ACQ_STRATEGY_CFG_STRU
   : 1XOOSNV
 1.       : 20151222
          : w00176964
      : 
*****************************************************************************/
typedef struct
{
    CNAS_NVIM_1X_OOS_SYS_ACQ_STRATEGY_CTRL_STRU             stCtrlInfo;
    CNAS_NVIM_1X_OOS_SYS_ACQ_STRATEGY_PATTERN_STRU          astSysAcqPhaseInfo[CNAS_NVIM_MAX_1X_OOC_SCHEDULE_PHASE_NUM];
}CNAS_NVIM_1X_OOS_SYS_ACQ_STRATEGY_CFG_STRU;

/*****************************************************************************
     : NAS_NVIM_CDMA_ERR_LOG_ACTIVE_REPORT_CONTRL_STRU
   :  NV
 1.       : 2016224
          : j00354216
      : CDMA Iteration 20
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           uc1xOosReportEnable;
    VOS_UINT8                           uc1xMtServiceExceptionReportEnable;
    VOS_UINT8                           ucHrpdUatiFailReportEnable;
    VOS_UINT8                           ucHrpdSessionFailReportEnable;
    VOS_UINT8                           ucHrpdSessionExceptionDeactReportEnable;
    VOS_UINT8                           uctHrpdOrLteOosReportEnable;
    VOS_UINT8                           uctXregResltReportEnable;
    VOS_UINT8                           ucXsmsReportEnable;
    VOS_UINT8                           ucVolteIms1xSwitchReportEnable;
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
    VOS_UINT8                           ucReserve3;
    VOS_UINT8                           ucReserve4;
    VOS_UINT8                           ucReserve5;
    VOS_UINT8                           ucReserve6;

    VOS_UINT8                           ucReserve7;
    VOS_UINT8                           ucReserve8;
    VOS_UINT8                           ucReserve9;
    VOS_UINT8                           ucReserve10;
    VOS_UINT8                           ucReserve11;
    VOS_UINT8                           ucReserve12;
    VOS_UINT8                           ucReserve13;
    VOS_UINT8                           ucReserve14;
    VOS_UINT8                           ucReserve15;
}NAS_NVIM_CDMA_ERR_LOG_ACTIVE_REPORT_CONTRL_STRU;

/*****************************************************************************
     : CNAS_NVIM_HOME_MCC_INFO_STRU
   : MCC

       :
  1.       : 2016-2-26
           : g00256031
       : Create
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulMccNum;                               /* MCC */
    VOS_UINT32                          aulMcc[CNAS_NVIM_HOME_MCC_MAX_NUM];     /* MCC */
} CNAS_NVIM_HOME_MCC_INFO_STRU;
/*****************************************************************************
     : CNAS_NVIM_MRU0_SWITCH_ON_OOC_STRATEGY_CFG_STRU
   : MRU0OOCNV
 1.       : 20151222
          : w00176964
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEnable;
    VOS_UINT8                           ucReserved;
    VOS_UINT16                          usMru0Times;
}CNAS_NVIM_MRU0_SWITCH_ON_OOC_STRATEGY_CFG_STRU;

/*****************************************************************************
     : NAS_NVIM_SYS_ACQ_BSR_TIMER_INFO_STRU
   : SYS ACQ BSR
 1.       : 201638
          : w00242748
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucMaxHistorySrchTimes;
    VOS_UINT8                           ucMaxPrefBandSrchTimes;
    VOS_UINT8                           ucBsrTimerMaxExpiredTimes; /* BSR */
    VOS_UINT8                           ucReserve1;
    VOS_UINT16                          usBsrTimerLenWithNoMatchedMsplRec;  /* MSPLBSR */
    VOS_UINT16                          usBsrTimerLen;                      /* MSPLBSR */
}NAS_NVIM_SYS_ACQ_BSR_TIMER_INFO_STRU;

/*****************************************************************************
     : NAS_NVIM_SYS_ACQ_BSR_CTRL_STRU
   : SYS ACQ BSR
 1.       : 201638
          : w00242748
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucBsrTimerActivateFlag;
    VOS_UINT8                                               ucBsrPhaseNum;
    VOS_UINT8                                               ucHrpdConnBsrActiveFlg; /* HRPDBSRVOS_TRUE:;VOS_FALSE: */
    VOS_UINT8                                               ucEhrpdConnBsrActiveFlg;/* EHRPDBSRVOS_TRUE:;VOS_FALSE: */
    NAS_NVIM_SYS_ACQ_BSR_TIMER_INFO_STRU                    astBsrTimerInfo[NAS_NVIM_MAX_BSR_PHASE_NUM];
}NAS_NVIM_SYS_ACQ_BSR_CTRL_STRU;
/*****************************************************************************
     : NAS_MMC_NVIM_CUSTOM_SUPPLEMENT_OPLMN_INFO_STRU
   : OPLMN--en_NV_Item_Custom_Supplement_Oplmn_Info
 1.       : 2016413
          : w00176964
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucImsiPlmnListNum;              /* IMSI */
    VOS_UINT8                           ucOPlmnListNum;                 /* Oplmn */
    VOS_UINT8                           ucRsv1;
    VOS_UINT8                           ucRsv2;
    NAS_SIM_FORMAT_PLMN_ID              astImsiPlmnList[NAS_MMC_NVIM_MAX_USER_CFG_IMSI_PLMN_NUM];
    NAS_SIM_FORMAT_PLMN_ID              astOPlmnList[NAS_MMC_NVIM_MAX_CUSTOM_SUPPLEMENT_OPLMN_NUM];
}NAS_MMC_NVIM_CUSTOM_SUPPLEMENT_OPLMN_INFO_STRU;

/*****************************************************************************
     : AI_MODEM_NAS_PLMN_SRCH_CFG_STRU
   : AI_MODEM_NAS_PLMN_SRCH_CFG_STRU
  1.       : 20160413
           : w00167002
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucOosSrchSleepCnt;
    VOS_UINT8                           ucHighPrioSrchSleepCnt;
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
    VOS_UINT8                           ucReserve3;
    VOS_UINT8                           ucReserve4;
    VOS_UINT8                           ucReserve5;
    VOS_UINT8                           ucReserve6;
}AI_MODEM_NAS_PLMN_SRCH_CFG_STRU;

/*****************************************************************************
     : AI_MODEM_LTE_MEASURE_CFG_STRU
   : AI_MODEM_LTE_MEASURE_CFG_STRU
  1.       : 20160413
           : w00167002
       : 
*****************************************************************************/

typedef struct
{
    VOS_INT16                           sThresholdRsrq;                         /* RSRQAI MODERSRQ[-15, -1],1dB */
    VOS_INT16                           sThresholdRsrp;                         /* RSRPAI MODERSRP[-115 , -1],1dB */
    VOS_UINT16                          usStillTimeThres;
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}AI_MODEM_LTE_MEASURE_CFG_STRU;

/*****************************************************************************
     : AI_MODEM_GSM_MEASURE_CFG_STRU
   : AI_MODEM_GSM_MEASURE_CFG_STRU
  1.       : 20160413
           : w00167002
       : 
*****************************************************************************/

typedef struct
{
    VOS_INT16                           sThresholdRssi;                         /* GSMRSSI[-1150] */
    VOS_UINT16                          usMeasOptimizeTimerLen;                 /* GSM:s */
    VOS_UINT16                          usStillTimeThres;
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}AI_MODEM_GSM_MEASURE_CFG_STRU;

/*****************************************************************************
     : AI_MODEM_WCDMA_MEASURE_CFG_STRU
   : AI_MODEM_WCDMA_MEASURE_CFG_STRU
  1.       : 20160413
           : w00167002
       : 
*****************************************************************************/

typedef struct
{
    VOS_INT16                           sThresholdRscp;                         /* WCDMARSCP[-1200] */
    VOS_INT16                           sThresholdEcn0;                         /* WCDMAECN0[-24,0] */
    VOS_UINT16                          usStillTimeThres;
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}AI_MODEM_WCDMA_MEASURE_CFG_STRU;


/*****************************************************************************
     : AI_MODEM_TIME_CFG_STRU
   : AI_MODEM_TIME_CFG_STRU
  1.       : 20160413
           : w00167002
       : 
*****************************************************************************/

typedef struct
{
    VOS_UINT8                           ucTimeStart;
    VOS_UINT8                           ucTimeEnd;
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}AI_MODEM_TIME_CFG_STRU;


/*****************************************************************************
     : AI_MODEM_CFG_NVIM_STRU
   : en_NV_Item_AI_MODEM_CFG_INFO
  1.       : 20160413
           : w00167002
       : 
*****************************************************************************/

typedef struct
{
    VOS_UINT8                           ucActFlg;                               /*01 */
    VOS_UINT8                           ucApplyArea;                            /*,0 */
    VOS_UINT8                           ucSensorIccFlg;                         /*SensorHubicc,0ICC1ICC*/
    VOS_UINT8                           ucReserve2;

    AI_MODEM_TIME_CFG_STRU              stTimeCfg;
    AI_MODEM_NAS_PLMN_SRCH_CFG_STRU     stNasSrchCfg;
    AI_MODEM_LTE_MEASURE_CFG_STRU       stLteMeasureCfg;
    AI_MODEM_GSM_MEASURE_CFG_STRU       stGasMeasureCfg;
    AI_MODEM_WCDMA_MEASURE_CFG_STRU     stWcdmaMeasureCfg;


    VOS_UINT8                           ucReserve3;
    VOS_UINT8                           ucReserve4;

    VOS_UINT8                           ucReserve5;
    VOS_UINT8                           ucReserve6;
    VOS_UINT8                           ucReserve7;
    VOS_UINT8                           ucReserve8;

    VOS_UINT8                           ucReserve9;
    VOS_UINT8                           ucReserve10;
    VOS_UINT8                           ucReserve11;
    VOS_UINT8                           ucReserve12;

    VOS_UINT8                           ucReserve13;
    VOS_UINT8                           ucReserve14;
}AI_MODEM_CFG_NVIM_STRU;


/*****************************************************************************
     : OPEN_ICC_CFG_STRU
   : en_NV_Item_Open_Icc_Cfg
  1.       : 20160720
           : g00322017
       : 
*****************************************************************************/

typedef struct
{
    VOS_UINT8                           ucSensorIccFlg;            /* ICC01 */
    VOS_UINT8                           ucReserve1;          /*  */
    VOS_UINT8                           ucReserve2;          /*  */
    VOS_UINT8                           ucReserve3;          /*  */

}OPEN_ICC_CFG_STRU;

/*****************************************************************************
     : SAR_SENSOR_HUB_CFG_STRU
   : en_NV_Item_SAR_SENSOR_HUB_CFG_INFO
  1.       : 20160720
           : g00322017
       : 
*****************************************************************************/

typedef struct
{
    VOS_UINT8                           ucSarSensorFlg;            /* sar sensor hub01 */
    VOS_UINT8                           ucReserve1;          /*  */
    VOS_UINT8                           ucReserve2;          /*  */
    VOS_UINT8                           ucReserve3;          /*  */

}SAR_SENSOR_HUB_CFG_STRU;

/*****************************************************************************
     : CNAS_NVIM_CDMA_HRPD_CUSTOMIZE_PREF_CHANNELS_STRU
   : HRPD
  1.       : 20160421
           : z00316370
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                               ucEnableFlg;
    VOS_UINT8                               ucReserved;
    VOS_UINT16                              usFreqNum;
    CNAS_NVIM_FREQENCY_CHANNEL_STRU         astFreqList[CNAS_NVIM_MAX_CDMA_HRPD_CUSTOMIZE_PREF_CHANNELS_NUM];
} CNAS_NVIM_CDMA_HRPD_CUSTOMIZE_PREF_CHANNELS_STRU;

/*****************************************************************************
     : NAS_NVIM_READ_USIM_FILE_TIMER_CTRL_STRU
   : USIM

 1.       : 20160902
          : p00371183
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usImsiFileTimerLen;        /* IMSI  */
    VOS_UINT16                                              usIccidFileTimerLen;       /* ICCID */
    VOS_UINT16                                              usServiceFileTimerLen;     /*  */
    VOS_UINT16                                              usReserved1;
    VOS_UINT16                                              usReserved2;
    VOS_UINT16                                              usReserved3;
    VOS_UINT16                                              usReserved4;
    VOS_UINT16                                              usReserved5;
    VOS_UINT16                                              usReserved6;
    VOS_UINT16                                              usReserved7;
}NAS_NVIM_READ_USIM_FILE_TIMER_CTRL_STRU;


/*****************************************************************************
     : NAS_NVIM_MODE_SELECTION_RETRY_TIMER_INFO_STRU
   : RETRY TIMER INFO 
  1.       : 20160504
           : L00301449
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usTimes;
    VOS_UINT16                          usTimerLen;
    VOS_UINT8                           ucRsv1;
    VOS_UINT8                           ucRsv2;
    VOS_UINT8                           ucRsv3;
    VOS_UINT8                           ucRsv4;
    VOS_UINT8                           ucRsv5;
    VOS_UINT8                           ucRsv6;
    VOS_UINT8                           ucRsv7;
    VOS_UINT8                           ucRsv8;
}NAS_NVIM_MODE_SELECTION_RETRY_TIMER_INFO_STRU;

/*****************************************************************************
     : NAS_NVIM_MODE_SELECTION_RETRY_TIMER_CTRL_STRU
   : RETRY TIMER
  1.       : 20160504
           : L00301449
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucRetryPhaseNum;
    VOS_UINT8                                               aucRsved[3];
    NAS_NVIM_MODE_SELECTION_RETRY_TIMER_INFO_STRU           astRetryTimerInfo[NAS_NVIM_MODE_SELECTION_RETRY_TIMER_PHASE_NUM_MAX];
}NAS_NVIM_MODE_SELECTION_RETRY_TIMER_CTRL_STRU;

/*****************************************************************************
     : NAS_NVIM_NO_CARD_SYS_ACQ_CFG_STRU
   : 
  1.       : 20160504
           : L00301449
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucNoCardPowerSaveFlg;         /* PowerSave */
    VOS_UINT8                                               ucClAcqLteFlg;                /* CLLTE */
    VOS_UINT8                                               ucReserve1;
    VOS_UINT8                                               ucReserve2;
}NAS_NVIM_NO_CARD_SYS_ACQ_CFG_STRU;


/*****************************************************************************
     : NAS_NVIM_MODE_SELECTION_CFG_STRU
   : 
  1.       : 20160504
           : L00301449
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucActiveFlg;

    /* VOS_TRUE */
    VOS_UINT8                                               ucIsAllowFirstSrch;

    /* VOS_FALSE */
    VOS_UINT8                                               ucIsAllowLastSrch;

    /* CLGULGULVOS_TRUE*/
    VOS_UINT8                                               ucIsOnlyBoundarySwitchMode;

    /* Retry timer lenen_NV_Item_MODE_SELECTION_RETRY_SYS_ACQ_STRATEGYsleep timer */
    NAS_NVIM_MODE_SELECTION_RETRY_TIMER_CTRL_STRU           stRsv;

    /* IMSI */
    VOS_UINT8                                               ucIsNeedFastSwitchImsi;
    VOS_UINT8                                               ucRsv2;
    VOS_UINT8                                               ucRsv3;
    VOS_UINT8                                               ucRsv4;
}NAS_NVIM_MODE_SELECTION_CFG_STRU;


/*****************************************************************************
     : NAS_NVIM_MODE_SELECTION_PUNISH_TIMER_INFO_STRU
   : PUNISH TIMER INFO 
  1.       : 20160630
           : L00301449
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulCount;            /*  */
    VOS_UINT32                          ulTimerLen;         /*  */
}NAS_NVIM_MODE_SELECTION_PUNISH_TIMER_INFO_STRU;

/*****************************************************************************
     : NAS_NVIM_MODE_SELECTION_PUNISH_CTRL_INFO_STRU
   : 
  1.       : 20160630
           : L00301449
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucActiveFlg;
    VOS_UINT8                                               ucRsv1;
    VOS_UINT8                                               ucRsv2;
    VOS_UINT8                                               ucPunishPhaseNum;
    NAS_NVIM_MODE_SELECTION_PUNISH_TIMER_INFO_STRU          astPunishTimerInfo[NAS_NVIM_MODE_SELECTION_PUNISH_TIMER_PHASE_NUM_MAX];
}NAS_NVIM_MODE_SELECTION_PUNISH_CTRL_INFO_STRU;

/*****************************************************************************
     : NAS_NVIM_MODE_SELECTION_RETRY_SYS_ACQ_PHASE_STRU
   : RETRY TIMER
  1.       : 20160628
           : L00301449
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usSleepTimerLen;
    VOS_UINT16                          usRsved1;
    VOS_UINT8                           ucHistoryNum;                           /*   PrefBand/FullBand */
    VOS_UINT8                           ucPrefBandNum;                          /* PrefBand  FullBand */
    VOS_UINT8                           ucFullBandNum;                          /* FullBand, ,  */
    VOS_UINT8                           ucRsved1;                               /*  */
    VOS_UINT8                           ucRsved2;
    VOS_UINT8                           ucRsved3;
    VOS_UINT8                           ucRsved4;
    VOS_UINT8                           ucRsved5;
}NAS_NVIM_MODE_SELECTION_RETRY_SYS_ACQ_PHASE_STRU;

/*****************************************************************************
     : NAS_NVIM_MODE_SELECTION_RETRY_SYS_ACQ_STRATEGY_STRU
   : RETRY
  1.       : 20160630
           : L00301449
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucActiveFlg;
    VOS_UINT8                                               ucPhaseNum;
    VOS_UINT8                                               ucRsved1;
    VOS_UINT8                                               ucRsved2;
    NAS_NVIM_MODE_SELECTION_RETRY_SYS_ACQ_PHASE_STRU        astSysAcqPhase[NAS_NVIM_MODE_SELECTION_RETRY_SYS_ACQ_PHASE_NUM_MAX];
}NAS_NVIM_MODE_SELECTION_RETRY_SYS_ACQ_STRATEGY_STRU;

/*****************************************************************************
     : NAS_NVIM_CL_SYS_ACQ_TYPE_CTRL_CFG_STRU
   : CL
  1.       : 20160912
           : m00312079
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucHistoryCfgSwitch;                                               /* History0:History  1:History*/
    VOS_UINT8                           ucPrefBandCfgSwitch;                                              /* PrefBand0:PrefBand1:PrefBand*/
    VOS_UINT8                           ucRsv1;                                                           /* RFU */
    VOS_UINT8                           ucRsv2;                                                           /* RFU */
    VOS_UINT8                           aucHistoryActiveFlg[NAS_NVIM_CUSTOMIZE_MAX_CL_ACQ_SCENE_NUM];      /* ucHistoryCfgSwitch0
                                                                                                                        History:
                                                                                                                        0History;
                                                                                                                        1History
                                                                                                                        NAS_MSCC_NVIM_SYS_ACQ_SCENE_ENUM_UINT32 */
    VOS_UINT8                           aucPrefBandActiveFlg[NAS_NVIM_CUSTOMIZE_MAX_CL_ACQ_SCENE_NUM];    /* ucPrefBandCfgSwitch0
                                                                                                                          PrefBand:
                                                                                                                          0PrefBand;
                                                                                                                          1PrefBand
                                                                                                                          NAS_MSCC_NVIM_SYS_ACQ_SCENE_ENUM_UINT32 */
    VOS_UINT8                           ucRsv3;                                                           /* RFU */
    VOS_UINT8                           ucRsv4;                                                           /* RFU */
    VOS_UINT8                           ucRsv5;                                                           /* RFU */
    VOS_UINT8                           ucRsv6;                                                           /* RFU */
}NAS_NVIM_CL_SYS_ACQ_TYPE_CTRL_CFG_STRU;

/*****************************************************************************
     : NAS_MMC_NVIM_OOS_MODE_SWITCH_SRCH_CTRL_CFG_STRU
   : MMC OOC
  1.       : 20160509
           : y00245242
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usOosModeSwitchSrchTimerLen;     /* MMC OOS */
    VOS_UINT16                                              usPowerOnModeSwitchSrchTimerLen; /* MMC  */
    VOS_UINT8                                               ucOosModeSwitchSrchTimes;        /* MMC OOS */
    VOS_UINT8                                               ucPowerOnModeSwitchSrchTimes;    /* MMC  */
    VOS_UINT8                                               aucReserved[2];
}NAS_MMC_NVIM_OOS_MODE_SWITCH_SRCH_CTRL_CFG_STRU;

/*****************************************************************************
     : CNAS_XSD_NVIM_OOS_MODE_SWITCH_SRCH_CTRL_CFG_STRU
   : XSD OOC
  1.       : 20160509
           : y00245242
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usOosModeSwitchSrchTimerLen;     /* MMC OOS */
    VOS_UINT16                                              usPowerOnModeSwitchSrchTimerLen; /* MMC  */
    VOS_UINT8                                               ucOosModeSwitchSrchTimes;        /* MMC OOS */
    VOS_UINT8                                               ucPowerOnModeSwitchSrchTimes;    /* MMC  */
    VOS_UINT8                                               aucReserved[2];
}CNAS_XSD_NVIM_OOS_MODE_SWITCH_SRCH_CTRL_CFG_STRU;

/*****************************************************************************
     : CNAS_NVIM_1X_REG_CFG_INFO_STRU
   : 1X
  1.       : 20160730
           : g00256031
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucIsPowerupRegAdv;              /* ,VOS_TRUE,VOS_FALSE */
    VOS_UINT8                                               aucRsv[3];
}CNAS_NVIM_1X_REG_CFG_INFO_STRU;

/*****************************************************************************
     :  NAS_NVIM_SMS_FAIL_LINK_CTRL_CFG_STRU
   :  
  1.       : 20160727
           : j00174725
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                               ucEnableFlg;
    VOS_UINT8                               ucReserved1;
    VOS_UINT8                               ucReserved2;
    VOS_UINT8                               ucReserved3;
} NAS_NVIM_SMS_FAIL_LINK_CTRL_CFG_STRU;

/*****************************************************************************
     :  NAS_NVIM_HIGH_SPEED_MODE_RPT_CFG_STRU
   :  
  1.       : 20160829
           : m00217266
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                               ucEnableFlg;
    VOS_UINT8                               ucReserved1;
    VOS_UINT8                               ucReserved2;
    VOS_UINT8                               ucReserved3;
} NAS_NVIM_HIGH_SPEED_MODE_RPT_CFG_STRU;

/*****************************************************************************
     : NAS_NVIM_SID_AND_MCC_INFO_STRU
   : sidmcc
  1.       : 20161013
           : l00359089
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT16                         usSidRangeStart;                                      /*SID  */
    VOS_UINT16                         usSidRangeEnd;                                        /*SID  */
    VOS_UINT32                         ulMcc;                                                /*mobile country code */
}NAS_NVIM_SID_AND_MCC_INFO_STRU;

/*****************************************************************************
     : NAS_NVIM_CHINA_BOUNDARY_SID_AND_MCC_INFO_STRU
   : SID MCC
  1.       : 20161013
           : l00359089
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulNum;                                                /*  */
    NAS_NVIM_SID_AND_MCC_INFO_STRU      astSidMccInfo[NAS_NVIM_CHINA_BOUNDARY_NETWORK_NUM_MAX];
}NAS_NVIM_CHINA_BOUNDARY_SID_AND_MCC_INFO_STRU;


/*****************************************************************************
     : NAS_NVIM_CHINA_BOUNDARY_SID_AND_MCC_INFO_STRU
   : HOMESID MCC
  1.       : 20161013
           : l00359089
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucActiveFlg;
    VOS_UINT8                                               ucHomeNetworkNum;               /* home */
    VOS_UINT8                                               ucRsved1;
    VOS_UINT8                                               ucRsved2;
    NAS_NVIM_SID_AND_MCC_INFO_STRU                          astSidRangeMccInfo[NAS_NVIM_CHINA_HOME_NETWORK_NUM_MAX];
}NAS_NVIM_CHINA_HOME_SID_AND_MCC_INFO_STRU;

/*****************************************************************************
     : NAS_NVIM_1X_MT_NVIM_REEST_CFG_STRU
   : X
  1.       : 20170104
           : h00360002
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucReestEnableFlg;                                                               /*  */
    VOS_UINT8                                               ucProtectTimerLen;                                                              /*  */
    VOS_UINT8                                               ucIntervalTimerLen;                                                             /*  */
    VOS_UINT8                                               ucMtEstCnfReestCauseNum;                                                        /* est_cnf */
    VOS_UINT8                                               aucMtEstCnfReestCause[NAS_NVIM_1X_MT_EST_CNF_REEST_CAUSE_MAX_NUM];              /* est_cnf */
    VOS_UINT8                                               ucMtTerminateIndReestCauseNum;                                                  /* terminate_ind */
    VOS_UINT8                                               aucMtTerminateIndReestCause[NAS_NVIM_1X_MT_TERMINATE_IND_REEST_CAUSE_MAX_NUM];  /* terminate_ind */
}NAS_NVIM_1X_MT_NVIM_REEST_CFG_STRU;

/*****************************************************************************
     :  NAS_NVIM_POWER_ON_QUICK_DISPLAY_NORMAL_SERVICE_OPTIMIZE_INFO_STRU
   :  
  1.       : 20160929
           : xwx377961
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                               ucQuickDisplayEnableFlg;
    VOS_UINT8                               ucReserved1;
    VOS_UINT8                               ucReserved2;
    VOS_UINT8                               ucReserved3;
} NAS_NVIM_POWER_ON_QUICK_DISPLAY_NORMAL_SERVICE_OPTIMIZE_INFO_STRU;

/*****************************************************************************
     : NAS_NVIM_TMSI_OR_P_TMSI_REALLOC_PLMN_VALID_CFG_STRU
   : TMSIP_TMSIPLMN0

 1.       : 20160103
          : b00368361
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucZeroPlmnInvalidFlag;                         /* TMSIP_TMSIPLMN0 */
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
}NAS_NVIM_TMSI_OR_P_TMSI_REALLOC_PLMN_VALID_CFG_STRU;

/*****************************************************************************
     :  NAS_NVIM_LOG_PRINT_CFG_STRU
   :  en_NV_Item_Nas_Log_Print_Max_Cnt_Cfg NAS LOG PRINT
  1.       : 20161209
           : wx270776
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucLogPrintMaxCnt;                       /* LOG */
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
    VOS_UINT8                           ucReserve3;
    VOS_UINT8                           ucReserve4;
    VOS_UINT8                           ucReserve5;
    VOS_UINT8                           ucReserve6;
    VOS_UINT8                           ucReserve7;
} NAS_NVIM_LOG_PRINT_CFG_STRU;

/*****************************************************************************
     : NVIM_GSM_A5_STRU
   : en_NV_Item_Gsm_A5 
 DESCRIOTION: A5A5/1A5/2A5/3A5/4
              Bitbit0bit1...bit7bit:
              bit0=0:A5/1bit0=1:A5/1
              bit1=0:A5/2bit1=1:A5/2
              bit2=0:A5/3bit2=1:A5/3
              bit3=0:A5/4bit3=1:A5/4
              bit

 1.       : 20170220
          : n00269697
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usGsmA5;
    VOS_UINT8                           aucReserve[2];
}NAS_NVIM_GSM_A5_STRU;
/*****************************************************************************
     : NAS_NVIM_OOS_CHR_POWER_SAVE_CFG_STRU
   : en_NV_Item_Oos_Chr_Cfg NV
 1.        : 20170214
           : l00324781
       : 

*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucPowerSaveEnableFlag;             /* 0:NV ; 1:NV  */
    VOS_UINT8                           ucScreenOnEnableFlag;              /* 0:;1: */
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT32                          ulGutlOosRptTimerInterval;         /* GUTL */
    VOS_UINT32                          ulGutlOosCsUserSenseTimerInterval; /* CS */
    VOS_UINT32                          ulGutlOosPsUserSenseTimerInterval; /* PS */
    VOS_UINT32                          ul1xOosRptTimerInterval;           /* CL1x:*/
    VOS_UINT32                          ulDoLteOosRptTimerInterval;        /* CLDO_LTE:*/
    VOS_UINT32                          ul1xRegFailRptTimerInterval;       /* CL1xCHR,: */
    VOS_UINT32                          ulReserved4;                       /*  */
}NAS_NVIM_OOS_CHR_POWER_SAVE_CFG_STRU;

/* Added by z00385378 for T310, 2017-1-9, begin */
/*****************************************************************************
     :  NAS_CC_NVIM_T310_CFG_STRU
   :  T310
  1.       : 20170103
           : z00385378
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                               ucNvActiveFlg;                             /* NV */
    VOS_UINT8                               ucT310CHREnableFlg;                        /* 310CHR */
    VOS_UINT8                               ucT310Len;
    VOS_UINT8                               ucReserved1;
} NAS_CC_NVIM_T310_CFG_STRU;
/* Added by z00385378 for T310, 2017-1-9, end */

/*****************************************************************************
     : NAS_NVIM_EMC_CATE_SUPPORT_ECALL_CFG_STRU
   : en_NV_Item_Emc_Cate_Support_ECALL_CFG NV
 1.        : 20170218
           : j00174725
       : 

*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEmcCateSupportEcallFlag;
    VOS_UINT8                           ucBit8Is1OtherBitOKFlag;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
}NAS_NVIM_EMC_CATE_SUPPORT_ECALL_CFG_STRU;

/*****************************************************************************
     :  NAS_NVIM_MO_COLLISION_STRU
   :  NV
  1.       : 20170224
           : z00385378
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                               ucNvActiveFlg;                             /* NV */
    VOS_UINT8                               ucProtectTimerLen;                         /*  */
    VOS_UINT8                               ucReserved1;
    VOS_UINT8                               ucReserved2;
} NAS_NVIM_MO_COLLISION_STRU;

/*****************************************************************************
     : NAS_NVIM_SRVCC_NO_CALL_NUM_T3240_CFG_STRU
   : SRVCCGIMSAT3240
  1.       : 20170328
           : n00269697
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucSrvccNoCallNumT3240Flag;              /* 0T3240
                                                                                   1T3240ulSrvccNoCallNumT3240Len ms */
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
    VOS_UINT32                          ulSrvccNoCallNumT3240Len;               /* T3240ms1000 ms */
}NAS_NVIM_SRVCC_NO_CALL_NUM_T3240_CFG_STRU;

/*****************************************************************************
     : NAS_NVIM_CLASSMARK_SUPPCODEC_CAPRPT_CTRL_STRU
   : GUclassmark23supported codecsNV

  1.       : 20171103
           : n00269697
       : 

*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucClamk2RptFlag;                        /* GURAU ATTACHclassmark 2 */
    VOS_UINT8                           ucClamk3RptFlag;                        /* GURAU ATTACHclassmark 3 */
    VOS_UINT8                           ucSuppCodecRptFlag;                     /* GURAU ATTACHsupported codecs */
    VOS_UINT8                           ucReserved;                             /*  */
}NAS_NVIM_CLASSMARK_SUPPCODEC_CAPRPT_CTRL_STRU;

/*****************************************************************************
     : NAS_NV_CELL_CHG_TRIGGER_LAU_IN_IU_MODE_CTRL_STRU
   : SSREL IND NV
  1.       : 2018310
           : n00269697
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucSsConnStateRcvRelIndSetCauseFlg;      /* SSREL IND:
                                                                                   0--
                                                                                   1-- */
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;

}NAS_NVIM_SS_CONN_STATE_RCV_REL_IND_SET_CAUSE_STRU;


/*****************************************************************************
     : NAS_NVIM_MT_MM_S12_RCV_SYSINFO_CFG_STRU
   : en_NV_Item_MT_MM_S12_RCV_SYSINFO_CFG NV
 1.        : 20170218
           : j00174725
       : 

*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucMtS12DiscardSysInfoFlg;                  /* pagingest req */
    VOS_UINT8                           ucChrEnableFlg;                            /* CHR */
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
}NAS_NVIM_MT_MM_S12_RCV_SYSINFO_CFG_STRU;




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
