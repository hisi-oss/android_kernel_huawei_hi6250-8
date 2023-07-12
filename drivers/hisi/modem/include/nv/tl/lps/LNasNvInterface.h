

#ifndef __LNASNVINTERFACE_H__
#define __LNASNVINTERFACE_H__

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include  "AppNasComm.h"


/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  #pragma pack(*)    
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 Macro
*****************************************************************************/


/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/

/*Added by lifuxin for DATA RETRY PHASEII 2016-05-23 start*/
#define LNAS_NV_DATA_RETRY_EMM_FAIL_CAUSE_EVENT_CNT     (9)
#define LNAS_NV_DATA_RETRY_EMM_FAIL_CAUSE_NUM           (6)

/*Added by lifuxin for DATA RETRY PHASEII 2016-05-23 end*/

#define LNAS_NV_MAX_APN_CONTEXT_NUM               6
#define LNAS_NV_MAX_APN_LEN                       99

#define LNAS_NV_ATTACH_REJ_NOT_REL_MAX_CAUSE_NUM  10
#define LNAS_NV_TAU_REJ_NOT_REL_MAX_CAUSE_NUM     10
#define LNAS_NV_ACDC_APP_MAX_NUM                  4
#define LNAS_NV_ACDC_OSID_LEN                (16)
#define LNAS_NV_ACDC_MAX_APPID_LEN           (128)

#define LNAS_NV_MT_DETACH_OPT_OTHER_CAUSE_CNT (32)
/************************stNasFunFlag02 Begin***************************/

/*****************************************************************************
  5 STRUCT
*****************************************************************************/
/*****************************************************************************
    :RRC_PLMN_ID_STRU
  :
ASN.1 :
  :
    MCC, Mobile country code (aucPlmnId[0], aucPlmnId[1] bits 1 to 4)
    MNC, Mobile network code (aucPlmnId[2], aucPlmnId[1] bits 5 to 8).

    The coding of this field is the responsibility of each administration but BCD
    coding shall be used. The MNC shall consist of 2 or 3 digits. For PCS 1900 for NA,
    Federal regulation mandates that a 3-digit MNC shall be used. However a network
    operator may decide to use only two digits in the MNC over the radio interface.
    In this case, bits 5 to 8 of octet 4 shall be coded as "1111". Mobile equipment
    shall accept MNC coded in such a way.

    ---------------------------------------------------------------------------
                 ||(BIT8)|(BIT7)|(BIT6)|(BIT5)|(BIT4)|(BIT3)|(BIT2)|(BIT1)
    ---------------------------------------------------------------------------
    aucPlmnId[0] ||    MCC digit 2            |           MCC digit 1
    ---------------------------------------------------------------------------
    aucPlmnId[1] ||    MNC digit 3            |           MCC digit 3
    ---------------------------------------------------------------------------
    aucPlmnId[2] ||    MNC digit 2            |           MNC digit 1
    ---------------------------------------------------------------------------

    AT
    at+cops=1,2,"mcc digit 3, mcc digit 2, mcc digit 1, mnc digit 3, mnc digit 2, mnc digit 1",2 :

    e.g.
    at+cops=1,2,"789456",2 :
    --------------------------------------------------------------------------------
    (mcc digit 3)|(mcc digit 2)|(mcc digit 1)|(mnc digit 3)|(mnc digit 2)|(mnc digit 1)
    --------------------------------------------------------------------------------
       7         |     8       |      9      |     4       |      5      |     6
    --------------------------------------------------------------------------------

    aucPlmnId[3]:
    ---------------------------------------------------------------------------
                 ||(BIT8)|(BIT7)|(BIT6)|(BIT5)|(BIT4)|(BIT3)|(BIT2)|(BIT1)
    ---------------------------------------------------------------------------
    aucPlmnId[0] ||    MCC digit 2 = 8        |           MCC digit 1 = 9
    ---------------------------------------------------------------------------
    aucPlmnId[1] ||    MNC digit 3 = 4        |           MCC digit 3 = 7
    ---------------------------------------------------------------------------
    aucPlmnId[2] ||    MNC digit 2 = 6        |           MNC digit 1 = 5
    ---------------------------------------------------------------------------
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucPlmnId[3];
    VOS_UINT8                           ucReserved;
}LRRC_LNAS_PLMN_ID_STRU;


typedef struct
{
    VOS_UINT32                          bitOpUeNetCap   :1;
    VOS_UINT32                          bitRsv          :31;

    NAS_MM_UE_NET_CAP_STRU              stUeNetCap;
}LNAS_LMM_NV_UE_NET_CAP_STRU;



typedef struct
{
    VOS_UINT32                          bitOpImsi     :1;
    VOS_UINT32                          bitOpRsv      :31;

    VOS_UINT8                           aucImsi[NAS_MM_MAX_UEID_BUF_SIZE];
    VOS_UINT8                           aucReserved1[2];
}LNAS_LMM_NV_IMSI_STRU;

/* LEQUIP_NV */
typedef struct
{
    VOS_UINT32                          bitOpImei     :1;
    VOS_UINT32                          bitOpRsv      :31;

    VOS_UINT8                           aucImei[NAS_MM_MAX_UEID_BUF_SIZE];
    VOS_UINT8                           aucReserved1[2];
}LNAS_LMM_NV_IMEI_STRU;

typedef struct
{
    VOS_UINT32                          bitOpGuti     :1; /* 1: VALID; 0: INVALID*/
    VOS_UINT32                          bitOpTai      :1;
    VOS_UINT32                          bitOpUpState  :1;
    VOS_UINT32                          bitOpRsv      :29;

    NAS_MM_GUTI_STRU                    stGuti;
    NAS_MM_TA_STRU                      stLastRegTai;
    NAS_MM_UPDATE_STATE_ENUM_UINT32     enUpdateState;
}LNAS_LMM_NV_EPS_LOC_STRU;


typedef struct
{
    VOS_UINT32                          bitOpMsClassMark :1; /* 1: VALID; 0: INVALID*/
    VOS_UINT32                          bitOpRsv      :31;
    NAS_MM_MS_CLASSMARK_STRU            stMsClassMark;
}LNAS_LMM_NV_MS_CLASSMARK_STRU;


typedef struct
{
    VOS_UINT32                          bitOpAccClassMark :1; /* 1: VALID; 0: INVALID*/
    VOS_UINT32                          bitOpRsv      :31;
    VOS_UINT16                          usAccClassMark;
    VOS_UINT8                           aucReserved1[2];
}LNAS_LMM_NV_ACC_CLASSMARK_STRU;


typedef struct
{
    VOS_UINT32                          bitOpEpsSec   :1;       /* 1: VALID; 0: INVALID*/
    VOS_UINT32                          bitOpRsv      :31;

    VOS_UINT8                           ucKSIsgsn;
    VOS_UINT8                           ucKSIasme;
    VOS_UINT8                           ucSecuAlg;
    VOS_UINT8                           ucRsv;
    VOS_UINT8                           aucKasme[NAS_MM_AUTH_KEY_ASME_LEN];
    VOS_UINT32                          ulUlNasCount;
    VOS_UINT32                          ulDlNasCount;
}LNAS_LMM_NV_EPS_SEC_CONTEXT_STRU;
typedef struct
{
    VOS_UINT32                          bitOpUeCenter       :1;       /* 1: VALID; 0: INVALID*/
    VOS_UINT32                          bitOpRsv            :31;

    LNAS_LMM_UE_CENTER_ENUM_UINT32      enUeCenter;
}LNAS_LMM_NV_UE_CENTER_STRU;


typedef struct
{
    VOS_UINT32                          bitOpVoicDomain     :1;       /* 1: VALID; 0: INVALID*/
    VOS_UINT32                          bitOpRsv            :31;
    NAS_LMM_VOICE_DOMAIN_ENUM_UINT32    enVoicDomain;
}LNAS_LMM_NV_VOICE_DOMAIN_STRU;

/*R10 modify begin for leili*/
typedef struct
{
    VOS_UINT32                          bitOpReleaseName    :1;       /* 1: VALID; 0: INVALID*/
    VOS_UINT32                          bitOpRsv            :31;

    VOS_UINT32                          ulReleaseName;

}LNAS_LMM_NV_NAS_RELEASE_STRU;
/*R10 modify end for leili*/

typedef struct
{
    VOS_UINT32                          bitOpLocalIpCap     :1;       /* 1: VALID; 0: INVALID*/
    VOS_UINT32                          bitOpRsv            :31;

    VOS_UINT32                          ulLocalIpCap;

}LNAS_LMM_NV_NAS_LOCALIP_CAP_STRU;


/*self-adaption NW cause modify begin for leili*/
typedef LNAS_LMM_CONFIG_NWCAUSE_STRU        LNAS_LMM_NV_CONFIG_NWCAUSE_STRU;

/*self-adaption NW cause modify end for leili*/


/*****************************************************************************
    :LNAS_ESM_NV_BACKOFF_CONFIG_PARA_STRU
    :DAMNV
*****************************************************************************/
typedef struct
{
    VOS_UINT32                           bitOpBackOffAlg   :1; /* Back-off     */
    VOS_UINT32                           bitOpBackOffFx    :1; /* NVFx     */
    VOS_UINT32                           bitOpShareEntityFlag :1;  /* 0 1  */
    VOS_UINT32                           bitOpRsv          :29;

    NAS_BACKOFF_RAT_SUPPORT_ENUM_UINT32  enBackOffRatSupport;  /* LTEGU  */
    NAS_CONFIG_BACKOFF_FX_PARA_STRU      stBackOffFx;          /* Fx               */
    NAS_CONFIG_PDP_PERM_CAUSE_STRU       stPdpPermCause;       /*    */
    NAS_CONFIG_PDP_TEMP_CAUSE_STRU       stPdpTempCause;       /*    */
}NAS_BACKOFF_NV_BACKOFF_CONFIG_PARA_STRU;

/*****************************************************************************
    :LNAS_LMM_NV_LTE_NO_ACCOUNT_CONFIG_STRU
    :LTENV
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucLteNoSubscribeVplmnSwitch;    /*4G, VPLMN1:  0: */
    VOS_UINT8                           ucLteNoSubscribeHplmnSwitch;    /*4GHPLMN, 1:  0: */
    VOS_UINT8                           ucDiscardExtendedEmmCauseFlag;  /*attach rejtau rej
                                                                          0:,1:*/
    VOS_UINT8                           ucRsv2;                         /**/
    VOS_UINT32                          ulPublishmentTimerVplmnLen;     /*VPLMN*/
    VOS_UINT32                          ulPublishmentTimerHplmnLen;     /*HPLMN*/
}LNAS_LMM_NV_LTE_NO_SUBSCRIBE_CONFIG_STRU;

/*****************************************************************************
    :LNAS_LMM_NV_ATTACHTAU_REJ1719_NOT_REL_STRU
    :DOCOMOATTACH/TAU17/19
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucSwitch;    /*,1: , 0: */
    VOS_UINT8                           ucAttachCauseNum;
    VOS_UINT8                           aucAttachCause[LNAS_NV_ATTACH_REJ_NOT_REL_MAX_CAUSE_NUM];
    VOS_UINT8                           ucTauCauseNum;
    VOS_UINT8                           aucTauCause[LNAS_NV_TAU_REJ_NOT_REL_MAX_CAUSE_NUM];
    VOS_UINT8                           ucRsv;
}LNAS_LMM_NV_ATTACHTAU_REJ_NOT_REL_STRU;

/*****************************************************************************
    :LNAS_LMM_NV_LOAD_BALANCE_TAU_CONTROL_CONFIG_STRU
    :load balanceUETAU
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucSwitch;                   /*,1: ,TAU 0: */
    VOS_UINT8                           aucRsv[3];
    VOS_UINT32                          ulThrotCtlTimeLen;          /*: */
}LNAS_LMM_NV_LOAD_BALANCE_TAU_CONTROL_CONFIG_STRU;

/*****************************************************************************
    :LNAS_LMM_NV_COMM_CONFIG_PARA_STRU
    :LNASLMMNVLMMNV
             NV
*****************************************************************************/
typedef struct
{
    VOS_UINT8                            ucMaxRej19AtmptCnt; /*  0: 5 ; */
    VOS_UINT8                            ucRsv0[3];           /*  */
    LNAS_LMM_NV_LTE_NO_SUBSCRIBE_CONFIG_STRU    stLteNoSubscribeConfig; /* 4GNV*/
    VOS_UINT32                           ulRsv1[13];          /*  */
    NAS_TMO_IMSI_HPLMN_LIST              stTmoImsiHplmnList;  /* TMOIMSI PLMN */
    VOS_UINT8                            ucRsv2[28];          /*  */
}LNAS_LMM_NV_COMM_CONFIG_PARA_STRU;


typedef struct
{
    VOS_UINT32                          bitOpAttachBearerReest   :1;   /* 1: VALID; 0: INVALID*/
    VOS_UINT32                          bitOpRsv                 :31;
    VOS_UINT32                          ulReestTimeLen;
}LNAS_ESM_NV_ATTACH_BEARER_REEST_STRU;
/*****************************************************************************
     : LNAS_FUN_FLAG_NV_BIT_STRU_1
   :
 ASN.1 :
   : 
*****************************************************************************/
typedef struct
{
    VOS_UINT32  bitOpKeyInfoFlag                       :1;/* Lnas,:1 */
    VOS_UINT32  bitOpKeyEventFlag                      :1;/* Lnas,:1 */
    VOS_UINT32  bitOpApiFlag                           :1;/* LnasAPI,:1 */
    VOS_UINT32  bitOpSuccRatioFlag                     :1;/* Lnas,:1 */
    VOS_UINT32  bitOpDelayFlag                         :1;/* Lnas,:1 */
    VOS_UINT32  bitOpEsrRej39OptimizeFlag              :1;/* Lnas Esr Rej #39,:0 */
    VOS_UINT32  bitOpNasAustraliaFlag                  :1;/* Lnas ,:0 */
    VOS_UINT32  bitOpImsiAttachWithInvalidTinFlag      :1;/* Lnas DSDS2.0 */
    VOS_UINT32  bitOpDsdsOptimizeFlag                  :1;/* Lnas SRLTE */
    VOS_UINT32  bitOpNasSrlteFlag                      :1;/* srlte */
    VOS_UINT32  bitOpNasT3402DefaultFlag               :1;/* T3402 */
    VOS_UINT32  bitOpThrotAlgSwitchFlag                :1;/* Lnas DATA RETRY,:0 */
    VOS_UINT32  bitOpUiccResetClearFlag                :1;/* uicc resetGUTI,LVR TAIEU2 */
    VOS_UINT32  bitOpDataRetryCtrlFlag                 :1;/* Lnas data retry */
    VOS_UINT32  bitOpTauRej17OneMoreAttachOptimFlag    :1;/* LNAS TAU#17:0 */
    VOS_UINT32  bitOpIncreaseFreqFlag                  :1;/* LNAS EMM(ATTACH):0*/
    VOS_UINT32  bitOpCsfbFrChr                         :1;/* LNAS CSFB FR DEALY CHR:0 */
    VOS_UINT32  bitOpServiceCounterFlag                :1;/* Lnas Service Counter,:0 */
    VOS_UINT32  bitOpAttachWithImsiFlag                 :1;/* Lnas Attach with IMSI,:0 */
    VOS_UINT32  bitOpAcdcFlag                           :1;/* ACDC,:0 */
    VOS_UINT32  bitOpAttachCause19WithoutEmmTimerFlag   :1;/*APNT3411/T3402:0*/
    VOS_UINT32  bitFlag22                   :1;
    VOS_UINT32  bitFlag23                   :1;
    VOS_UINT32  bitFlag24                   :1;
    VOS_UINT32  bitFlag25                   :1;
    VOS_UINT32  bitFlag26                   :1;
    VOS_UINT32  bitFlag27                   :1;
    VOS_UINT32  bitFlag28                   :1;
    VOS_UINT32  bitFlag29                   :1;
    VOS_UINT32  bitFlag30                   :1;
    VOS_UINT32  bitFlag31                   :1;
    VOS_UINT32  bitFlag32                   :1;
}LNAS_FUN_FLAG_NV_BIT_STRU_1;

/*****************************************************************************
     : LNAS_FUN_FLAG_NV_BIT_STRU_2
   :
 ASN.1 :
   : 
*****************************************************************************/
typedef struct
{
    VOS_UINT32  bitFlag01                   :1;
    VOS_UINT32  bitFlag02                   :1;
    VOS_UINT32  bitFlag03                   :1;
    VOS_UINT32  bitFlag04                   :1;
    VOS_UINT32  bitFlag05                   :1;
    VOS_UINT32  bitFlag06                   :1;
    VOS_UINT32  bitFlag07                   :1;
    VOS_UINT32  bitFlag08                   :1;
    VOS_UINT32  bitFlag09                   :1;
    VOS_UINT32  bitFlag10                   :1;
    VOS_UINT32  bitFlag11                   :1;
    VOS_UINT32  bitFlag12                   :1;
    VOS_UINT32  bitFlag13                   :1;
    VOS_UINT32  bitFlag14                   :1;
    VOS_UINT32  bitFlag15                   :1;
    VOS_UINT32  bitFlag16                   :1;
    VOS_UINT32  bitFlag17                   :1;
    VOS_UINT32  bitFlag18                   :1;
    VOS_UINT32  bitFlag19                   :1;
    VOS_UINT32  bitFlag20                   :1;
    VOS_UINT32  bitFlag21                   :1;
    VOS_UINT32  bitFlag22                   :1;
    VOS_UINT32  bitFlag23                   :1;
    VOS_UINT32  bitFlag24                   :1;
    VOS_UINT32  bitFlag25                   :1;
    VOS_UINT32  bitFlag26                   :1;
    VOS_UINT32  bitFlag27                   :1;
    VOS_UINT32  bitFlag28                   :1;
    VOS_UINT32  bitFlag29                   :1;
    VOS_UINT32  bitFlag30                   :1;
    VOS_UINT32  bitFlag31                   :1;
    VOS_UINT32  bitFlag32                   :1;
}LNAS_FUN_FLAG_NV_BIT_STRU_2;

/*****************************************************************************
     : LNAS_FUN_FLAG_NV_BIT_STRU_3
   :
 ASN.1 :
   : 
*****************************************************************************/
typedef struct
{
    VOS_UINT32  bitFlag01                   :1;
    VOS_UINT32  bitFlag02                   :1;
    VOS_UINT32  bitFlag03                   :1;
    VOS_UINT32  bitFlag04                   :1;
    VOS_UINT32  bitFlag05                   :1;
    VOS_UINT32  bitFlag06                   :1;
    VOS_UINT32  bitFlag07                   :1;
    VOS_UINT32  bitFlag08                   :1;
    VOS_UINT32  bitFlag09                   :1;
    VOS_UINT32  bitFlag10                   :1;
    VOS_UINT32  bitFlag11                   :1;
    VOS_UINT32  bitFlag12                   :1;
    VOS_UINT32  bitFlag13                   :1;
    VOS_UINT32  bitFlag14                   :1;
    VOS_UINT32  bitFlag15                   :1;
    VOS_UINT32  bitFlag16                   :1;
    VOS_UINT32  bitFlag17                   :1;
    VOS_UINT32  bitFlag18                   :1;
    VOS_UINT32  bitFlag19                   :1;
    VOS_UINT32  bitFlag20                   :1;
    VOS_UINT32  bitFlag21                   :1;
    VOS_UINT32  bitFlag22                   :1;
    VOS_UINT32  bitFlag23                   :1;
    VOS_UINT32  bitFlag24                   :1;
    VOS_UINT32  bitFlag25                   :1;
    VOS_UINT32  bitFlag26                   :1;
    VOS_UINT32  bitFlag27                   :1;
    VOS_UINT32  bitFlag28                   :1;
    VOS_UINT32  bitFlag29                   :1;
    VOS_UINT32  bitFlag30                   :1;
    VOS_UINT32  bitFlag31                   :1;
    VOS_UINT32  bitFlag32                   :1;
}LNAS_FUN_FLAG_NV_BIT_STRU_3;

/*****************************************************************************
     : LNAS_FUN_FLAG_NV_BIT_STRU_4
   :
 ASN.1 :
   : 
*****************************************************************************/
typedef struct
{
    VOS_UINT32  bitFlag01                   :1;
    VOS_UINT32  bitFlag02                   :1;
    VOS_UINT32  bitFlag03                   :1;
    VOS_UINT32  bitFlag04                   :1;
    VOS_UINT32  bitFlag05                   :1;
    VOS_UINT32  bitFlag06                   :1;
    VOS_UINT32  bitFlag07                   :1;
    VOS_UINT32  bitFlag08                   :1;
    VOS_UINT32  bitFlag09                   :1;
    VOS_UINT32  bitFlag10                   :1;
    VOS_UINT32  bitFlag11                   :1;
    VOS_UINT32  bitFlag12                   :1;
    VOS_UINT32  bitFlag13                   :1;
    VOS_UINT32  bitFlag14                   :1;
    VOS_UINT32  bitFlag15                   :1;
    VOS_UINT32  bitFlag16                   :1;
    VOS_UINT32  bitFlag17                   :1;
    VOS_UINT32  bitFlag18                   :1;
    VOS_UINT32  bitFlag19                   :1;
    VOS_UINT32  bitFlag20                   :1;
    VOS_UINT32  bitFlag21                   :1;
    VOS_UINT32  bitFlag22                   :1;
    VOS_UINT32  bitFlag23                   :1;
    VOS_UINT32  bitFlag24                   :1;
    VOS_UINT32  bitFlag25                   :1;
    VOS_UINT32  bitFlag26                   :1;
    VOS_UINT32  bitFlag27                   :1;
    VOS_UINT32  bitFlag28                   :1;
    VOS_UINT32  bitFlag29                   :1;
    VOS_UINT32  bitFlag30                   :1;
    VOS_UINT32  bitFlag31                   :1;
    VOS_UINT32  bitFlag32                   :1;
}LNAS_FUN_FLAG_NV_BIT_STRU_4;

/*****************************************************************************
     : LNAS_FUN_FLAG_NV_BIT_STRU_5
   :
 ASN.1 :
   : 
*****************************************************************************/
typedef struct
{
    VOS_UINT32  bitFlag01                   :1;
    VOS_UINT32  bitFlag02                   :1;
    VOS_UINT32  bitFlag03                   :1;
    VOS_UINT32  bitFlag04                   :1;
    VOS_UINT32  bitFlag05                   :1;
    VOS_UINT32  bitFlag06                   :1;
    VOS_UINT32  bitFlag07                   :1;
    VOS_UINT32  bitFlag08                   :1;
    VOS_UINT32  bitFlag09                   :1;
    VOS_UINT32  bitFlag10                   :1;
    VOS_UINT32  bitFlag11                   :1;
    VOS_UINT32  bitFlag12                   :1;
    VOS_UINT32  bitFlag13                   :1;
    VOS_UINT32  bitFlag14                   :1;
    VOS_UINT32  bitFlag15                   :1;
    VOS_UINT32  bitFlag16                   :1;
    VOS_UINT32  bitFlag17                   :1;
    VOS_UINT32  bitFlag18                   :1;
    VOS_UINT32  bitFlag19                   :1;
    VOS_UINT32  bitFlag20                   :1;
    VOS_UINT32  bitFlag21                   :1;
    VOS_UINT32  bitFlag22                   :1;
    VOS_UINT32  bitFlag23                   :1;
    VOS_UINT32  bitFlag24                   :1;
    VOS_UINT32  bitFlag25                   :1;
    VOS_UINT32  bitFlag26                   :1;
    VOS_UINT32  bitFlag27                   :1;
    VOS_UINT32  bitFlag28                   :1;
    VOS_UINT32  bitFlag29                   :1;
    VOS_UINT32  bitFlag30                   :1;
    VOS_UINT32  bitFlag31                   :1;
    VOS_UINT32  bitFlag32                   :1;
}LNAS_FUN_FLAG_NV_BIT_STRU_5;

/*****************************************************************************
     : LNAS_FUN_FLAG_NV_BIT_STRU_6
   :
 ASN.1 :
   : 
*****************************************************************************/
typedef struct
{
    VOS_UINT32  bitFlag01                   :1;
    VOS_UINT32  bitFlag02                   :1;
    VOS_UINT32  bitFlag03                   :1;
    VOS_UINT32  bitFlag04                   :1;
    VOS_UINT32  bitFlag05                   :1;
    VOS_UINT32  bitFlag06                   :1;
    VOS_UINT32  bitFlag07                   :1;
    VOS_UINT32  bitFlag08                   :1;
    VOS_UINT32  bitFlag09                   :1;
    VOS_UINT32  bitFlag10                   :1;
    VOS_UINT32  bitFlag11                   :1;
    VOS_UINT32  bitFlag12                   :1;
    VOS_UINT32  bitFlag13                   :1;
    VOS_UINT32  bitFlag14                   :1;
    VOS_UINT32  bitFlag15                   :1;
    VOS_UINT32  bitFlag16                   :1;
    VOS_UINT32  bitFlag17                   :1;
    VOS_UINT32  bitFlag18                   :1;
    VOS_UINT32  bitFlag19                   :1;
    VOS_UINT32  bitFlag20                   :1;
    VOS_UINT32  bitFlag21                   :1;
    VOS_UINT32  bitFlag22                   :1;
    VOS_UINT32  bitFlag23                   :1;
    VOS_UINT32  bitFlag24                   :1;
    VOS_UINT32  bitFlag25                   :1;
    VOS_UINT32  bitFlag26                   :1;
    VOS_UINT32  bitFlag27                   :1;
    VOS_UINT32  bitFlag28                   :1;
    VOS_UINT32  bitFlag29                   :1;
    VOS_UINT32  bitFlag30                   :1;
    VOS_UINT32  bitFlag31                   :1;
    VOS_UINT32  bitFlag32                   :1;
}LNAS_FUN_FLAG_NV_BIT_STRU_6;

/*****************************************************************************
     : LNAS_FUN_FLAG_NV_BIT_STRU_7
   :
 ASN.1 :
   : 
*****************************************************************************/
typedef struct
{
    VOS_UINT32  bitFlag01                   :1;
    VOS_UINT32  bitFlag02                   :1;
    VOS_UINT32  bitFlag03                   :1;
    VOS_UINT32  bitFlag04                   :1;
    VOS_UINT32  bitFlag05                   :1;
    VOS_UINT32  bitFlag06                   :1;
    VOS_UINT32  bitFlag07                   :1;
    VOS_UINT32  bitFlag08                   :1;
    VOS_UINT32  bitFlag09                   :1;
    VOS_UINT32  bitFlag10                   :1;
    VOS_UINT32  bitFlag11                   :1;
    VOS_UINT32  bitFlag12                   :1;
    VOS_UINT32  bitFlag13                   :1;
    VOS_UINT32  bitFlag14                   :1;
    VOS_UINT32  bitFlag15                   :1;
    VOS_UINT32  bitFlag16                   :1;
    VOS_UINT32  bitFlag17                   :1;
    VOS_UINT32  bitFlag18                   :1;
    VOS_UINT32  bitFlag19                   :1;
    VOS_UINT32  bitFlag20                   :1;
    VOS_UINT32  bitFlag21                   :1;
    VOS_UINT32  bitFlag22                   :1;
    VOS_UINT32  bitFlag23                   :1;
    VOS_UINT32  bitFlag24                   :1;
    VOS_UINT32  bitFlag25                   :1;
    VOS_UINT32  bitFlag26                   :1;
    VOS_UINT32  bitFlag27                   :1;
    VOS_UINT32  bitFlag28                   :1;
    VOS_UINT32  bitFlag29                   :1;
    VOS_UINT32  bitFlag30                   :1;
    VOS_UINT32  bitFlag31                   :1;
    VOS_UINT32  bitFlag32                   :1;
}LNAS_FUN_FLAG_NV_BIT_STRU_7;

/*****************************************************************************
     : LNAS_FUN_FLAG_NV_BIT_STRU_8
   :
 ASN.1 :
   : 
*****************************************************************************/
typedef struct
{
    VOS_UINT32  bitFlag01                   :1;
    VOS_UINT32  bitFlag02                   :1;
    VOS_UINT32  bitFlag03                   :1;
    VOS_UINT32  bitFlag04                   :1;
    VOS_UINT32  bitFlag05                   :1;
    VOS_UINT32  bitFlag06                   :1;
    VOS_UINT32  bitFlag07                   :1;
    VOS_UINT32  bitFlag08                   :1;
    VOS_UINT32  bitFlag09                   :1;
    VOS_UINT32  bitFlag10                   :1;
    VOS_UINT32  bitFlag11                   :1;
    VOS_UINT32  bitFlag12                   :1;
    VOS_UINT32  bitFlag13                   :1;
    VOS_UINT32  bitFlag14                   :1;
    VOS_UINT32  bitFlag15                   :1;
    VOS_UINT32  bitFlag16                   :1;
    VOS_UINT32  bitFlag17                   :1;
    VOS_UINT32  bitFlag18                   :1;
    VOS_UINT32  bitFlag19                   :1;
    VOS_UINT32  bitFlag20                   :1;
    VOS_UINT32  bitFlag21                   :1;
    VOS_UINT32  bitFlag22                   :1;
    VOS_UINT32  bitFlag23                   :1;
    VOS_UINT32  bitFlag24                   :1;
    VOS_UINT32  bitFlag25                   :1;
    VOS_UINT32  bitFlag26                   :1;
    VOS_UINT32  bitFlag27                   :1;
    VOS_UINT32  bitFlag28                   :1;
    VOS_UINT32  bitFlag29                   :1;
    VOS_UINT32  bitFlag30                   :1;
    VOS_UINT32  bitFlag31                   :1;
    VOS_UINT32  bitFlag32                   :1;
}LNAS_FUN_FLAG_NV_BIT_STRU_8;

/*****************************************************************************
    :LNAS_LMM_NV_GRADUAL_FORBIDDEN_PARA_STRU
    :LNASForbiddenNV
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucGradualForbFlag;           /* , 0: ; 1:  */
    VOS_UINT8                           ucRsv1;
    VOS_UINT8                           ucRsv2;
    VOS_UINT8                           ucRsv3;
    VOS_UINT16                          usGradualForbTimerFirstLen;  /* #15, ,  */
    VOS_UINT16                          usGradualForbTimerSecondLen; /* #15, ,  */
    VOS_UINT32                          ulGradualForbAgingTimerLen;  /* ,  */
    VOS_UINT16                          usRsv1;
    VOS_UINT16                          usRsv2;
    VOS_UINT16                          usRsv3;
    VOS_UINT16                          usRsv4;
    VOS_UINT32                          ulRsv1;
    VOS_UINT32                          ulRsv2;
    VOS_UINT32                          ulRsv3;
    VOS_UINT32                          ulRsv4;
}LNAS_LMM_NV_GRADUAL_FORBIDDEN_PARA_STRU;

/*****************************************************************************
     : LNAS_SWITCH_PARA_STRU
   :
 ASN.1 :
   : LNAS(BIT,)
*****************************************************************************/
typedef struct
{
    /*bitLNAS*/
    LNAS_FUN_FLAG_NV_BIT_STRU_1                 stNasFunFlag01;
    LNAS_FUN_FLAG_NV_BIT_STRU_2                 stNasFunFlag02;
    LNAS_FUN_FLAG_NV_BIT_STRU_3                 stNasFunFlag03;
    LNAS_FUN_FLAG_NV_BIT_STRU_4                 stNasFunFlag04;
    LNAS_FUN_FLAG_NV_BIT_STRU_5                 stNasFunFlag05;
    LNAS_FUN_FLAG_NV_BIT_STRU_6                 stNasFunFlag06;
    LNAS_FUN_FLAG_NV_BIT_STRU_7                 stNasFunFlag07;
    LNAS_FUN_FLAG_NV_BIT_STRU_8                 stNasFunFlag08;

    LNAS_LMM_NV_GRADUAL_FORBIDDEN_PARA_STRU stGradualForbPara;

    /* Bit,  */
    VOS_UINT8                               ucTauRej17MaxTimes;    /* TAU1710attach1-5 */
    VOS_UINT8                               uc3402TempForbiddenTAFlag;
    /* 0:   */
    /* 1: HPLMN */
    /* 2: VPLMN */
    /* 3:   */
    VOS_UINT8                               ucRsv3;
    VOS_UINT8                               ucRsv4;
    VOS_UINT8                               ucRsv5;
    VOS_UINT8                               ucRsv6;
    VOS_UINT8                               ucRsv7;
    VOS_UINT8                               ucRsv8;
    VOS_UINT8                               ucRsv9;
    VOS_UINT8                               ucRsv10;
    VOS_UINT8                               ucRsv11;
    VOS_UINT8                               ucRsv12;
    VOS_UINT8                               ucRsv13;
    VOS_UINT8                               ucRsv14;
    VOS_UINT8                               ucRsv15;
    VOS_UINT8                               ucRsv16;
    VOS_UINT8                               ucRsv17;
    VOS_UINT8                               ucRsv18;
    VOS_UINT8                               ucRsv19;
    VOS_UINT8                               ucRsv20;
    VOS_UINT8                               ucRsv21;
    VOS_UINT8                               ucRsv22;
    VOS_UINT8                               ucRsv23;
    VOS_UINT8                               ucRsv24;
    VOS_UINT8                               ucRsv25;
    VOS_UINT8                               ucRsv26;
    VOS_UINT8                               ucRsv27;
    VOS_UINT8                               ucRsv28;
    VOS_UINT8                               ucRsv29;
    VOS_UINT8                               ucRsv30;
    VOS_UINT8                               ucRsv31;
    VOS_UINT8                               ucRsv32;
    VOS_UINT8                               ucRsv33;
    VOS_UINT8                               ucRsv34;
    VOS_UINT8                               ucRsv35;
    VOS_UINT8                               ucRsv36;
    VOS_UINT8                               ucRsv37;
    VOS_UINT8                               ucRsv38;
    VOS_UINT8                               ucRsv39;
    VOS_UINT8                               ucRsv40;
    VOS_UINT8                               ucRsv41;
    VOS_UINT8                               ucRsv42;
    VOS_UINT8                               ucRsv43;
    VOS_UINT8                               ucRsv44;
    VOS_UINT8                               ucRsv45;
    VOS_UINT8                               ucRsv46;
    VOS_UINT8                               ucRsv47;
    VOS_UINT8                               ucRsv48;
    VOS_UINT8                               ucRsv49;
    VOS_UINT8                               ucRsv50;
    VOS_UINT8                               ucRsv51;
    VOS_UINT8                               ucRsv52;
    VOS_UINT8                               ucRsv53;
    VOS_UINT8                               ucRsv54;
    VOS_UINT8                               ucRsv55;
    VOS_UINT8                               ucRsv56;
    VOS_UINT8                               ucRsv57;
    VOS_UINT8                               ucRsv58;
    VOS_UINT8                               ucRsv59;
    VOS_UINT8                               ucRsv60;
    VOS_UINT8                               ucRsv61;
    VOS_UINT8                               ucRsv62;
    VOS_UINT8                               ucRsv63;
    VOS_UINT8                               ucRsv64;
    VOS_UINT16                              usTempForbTimerLen; /**/
    VOS_UINT16                              usRsv2;
    VOS_UINT16                              usRsv3;
    VOS_UINT16                              usRsv4;
    VOS_UINT16                              usRsv5;
    VOS_UINT16                              usRsv6;
    VOS_UINT16                              usRsv7;
    VOS_UINT16                              usRsv8;
    VOS_UINT16                              usRsv9;
    VOS_UINT16                              usRsv10;
    VOS_UINT16                              usRsv11;
    VOS_UINT16                              usRsv12;
    VOS_UINT16                              usRsv13;
    VOS_UINT16                              usRsv14;
    VOS_UINT16                              usRsv15;
    VOS_UINT16                              usRsv16;
    VOS_UINT16                              usRsv17;
    VOS_UINT16                              usRsv18;
    VOS_UINT16                              usRsv19;
    VOS_UINT16                              usRsv20;
    VOS_UINT16                              usRsv21;
    VOS_UINT16                              usRsv22;
    VOS_UINT16                              usRsv23;
    VOS_UINT16                              usRsv24;
    VOS_UINT16                              usRsv25;
    VOS_UINT16                              usRsv26;
    VOS_UINT16                              usRsv27;
    VOS_UINT16                              usRsv28;
    VOS_UINT16                              usRsv29;
    VOS_UINT16                              usRsv30;
    VOS_UINT16                              usRsv31;
    VOS_UINT16                              usRsv32;
    VOS_UINT16                              usRsv33;
    VOS_UINT16                              usRsv34;
    VOS_UINT16                              usRsv35;
    VOS_UINT16                              usRsv36;
    VOS_UINT16                              usRsv37;
    VOS_UINT16                              usRsv38;
    VOS_UINT16                              usRsv39;
    VOS_UINT16                              usRsv40;
    VOS_UINT16                              usRsv41;
    VOS_UINT16                              usRsv42;
    VOS_UINT16                              usRsv43;
    VOS_UINT16                              usRsv44;
    VOS_UINT16                              usRsv45;
    VOS_UINT16                              usRsv46;
    VOS_UINT16                              usRsv47;
    VOS_UINT16                              usRsv48;
    VOS_UINT16                              usRsv49;
    VOS_UINT16                              usRsv50;
    VOS_UINT16                              usRsv51;
    VOS_UINT16                              usRsv52;
    VOS_UINT16                              usRsv53;
    VOS_UINT16                              usRsv54;
    VOS_UINT16                              usRsv55;
    VOS_UINT16                              usRsv56;
    VOS_UINT16                              usRsv57;
    VOS_UINT16                              usRsv58;
    VOS_UINT16                              usRsv59;
    VOS_UINT16                              usRsv60;
    VOS_UINT16                              usRsv61;
    VOS_UINT16                              usRsv62;
    VOS_UINT16                              usRsv63;
    VOS_UINT16                              usRsv64;

    VOS_UINT32                              ulCcpuIncreaseFreqValue; /*Ccpu,KHZ*/
    VOS_UINT32                              ulDdrIncreaseFreqValue;  /*Ddr,KHZ*/

    VOS_UINT32                              ulRsv3;
    VOS_UINT32                              ulRsv4;
    VOS_UINT32                              ulRsv5;
    VOS_UINT32                              ulRsv6;
    VOS_UINT32                              ulRsv7;
    VOS_UINT32                              ulRsv8;
    VOS_UINT32                              ulRsv9;
    VOS_UINT32                              ulRsv10;
    VOS_UINT32                              ulRsv11;
    VOS_UINT32                              ulRsv12;
    VOS_UINT32                              ulRsv13;
    VOS_UINT32                              ulRsv14;
    VOS_UINT32                              ulRsv15;
    VOS_UINT32                              ulRsv16;
    VOS_UINT32                              ulRsv17;
    VOS_UINT32                              ulRsv18;
    VOS_UINT32                              ulRsv19;
    VOS_UINT32                              ulRsv20;
    VOS_UINT32                              ulRsv21;
    VOS_UINT32                              ulRsv22;
    VOS_UINT32                              ulRsv23;
    VOS_UINT32                              ulRsv24;
    VOS_UINT32                              ulRsv25;
    VOS_UINT32                              ulRsv26;
    VOS_UINT32                              ulRsv27;
    VOS_UINT32                              ulRsv28;
    VOS_UINT32                              ulRsv29;
    VOS_UINT32                              ulRsv30;
    VOS_UINT32                              ulRsv31;
    VOS_UINT32                              ulRsv32;
}LNAS_NV_SWITCH_PARA_STRU;
typedef struct
{
    VOS_UINT32                          bitOpPeriodicRptTimes:1;                /*  */
    VOS_UINT32                          bitOp2:1;
    VOS_UINT32                          bitOp3:1;
    VOS_UINT32                          bitOp4:1;
    VOS_UINT32                          bitOp5:1;
    VOS_UINT32                          bitOp6:1;
    VOS_UINT32                          bitOp7:1;
    VOS_UINT32                          bitOp8:1;
    VOS_UINT32                          bitOp9:1;
    VOS_UINT32                          bitOp10:1;
    VOS_UINT32                          bitOp11:1;
    VOS_UINT32                          bitOp12:1;
    VOS_UINT32                          bitOp13:1;
    VOS_UINT32                          bitOp14:1;
    VOS_UINT32                          bitOp15:1;
    VOS_UINT32                          bitOp16:1;
    VOS_UINT32                          bitOp17:1;
    VOS_UINT32                          bitOp18:1;
    VOS_UINT32                          bitOp19:1;
    VOS_UINT32                          bitOp20:1;
    VOS_UINT32                          bitOp21:1;
    VOS_UINT32                          bitOp22:1;
    VOS_UINT32                          bitOp23:1;
    VOS_UINT32                          bitOp24:1;
    VOS_UINT32                          bitOp25:1;
    VOS_UINT32                          bitOp26:1;
    VOS_UINT32                          bitOp27:1;
    VOS_UINT32                          bitOp28:1;
    VOS_UINT32                          bitOp29:1;
    VOS_UINT32                          bitOp30:1;
    VOS_UINT32                          bitOp31:1;
    VOS_UINT32                          bitOp32:1;
}LNAS_LCS_NV_FEATURE_BIT_STRU;

typedef struct
{
    LNAS_LCS_NV_FEATURE_BIT_STRU        stLcsFeatureBit;

    VOS_UINT8                           ucMaxRetryTimes;                        /*  */
    VOS_UINT8                           ucRsv1;
    VOS_UINT8                           ucRsv2;
    VOS_UINT8                           ucRsv3;
    VOS_UINT8                           ucRsv4;
    VOS_UINT8                           ucRsv5;
    VOS_UINT8                           ucRsv6;
    VOS_UINT8                           ucRsv7;
    VOS_UINT8                           ucRsv8;
    VOS_UINT8                           ucRsv9;
    VOS_UINT8                           ucRsv10;
    VOS_UINT8                           ucRsv11;
    VOS_UINT8                           ucRsv12;
    VOS_UINT8                           ucRsv13;
    VOS_UINT8                           ucRsv14;
    VOS_UINT8                           ucRsv15;
    VOS_UINT8                           ucRsv16;
    VOS_UINT8                           ucRsv17;
    VOS_UINT8                           ucRsv18;
    VOS_UINT8                           ucRsv19;
    VOS_UINT8                           ucRsv20;
    VOS_UINT8                           ucRsv21;
    VOS_UINT8                           ucRsv22;
    VOS_UINT8                           ucRsv23;
    VOS_UINT16                          usRetryTimerLen;                        /* ,  */
    VOS_UINT16                          usPeriodicRptTimes;                     /* MO-LR, */
    VOS_UINT16                          usRsv2;
    VOS_UINT16                          usRsv3;
    VOS_UINT16                          usRsv4;
    VOS_UINT16                          usRsv5;
    VOS_UINT16                          usRsv6;
    VOS_UINT16                          usRsv7;
    VOS_UINT16                          usRsv8;
    VOS_UINT16                          usRsv9;
    VOS_UINT16                          usRsv10;
    VOS_UINT16                          usRsv11;
    VOS_UINT16                          usRsv12;
    VOS_UINT16                          usRsv13;
    VOS_UINT16                          usRsv14;
    VOS_UINT16                          usRsv15;
    VOS_UINT32                          ulRsv0;
    VOS_UINT32                          ulRsv1;
    VOS_UINT32                          ulRsv2;
    VOS_UINT32                          ulRsv3;
    VOS_UINT32                          ulRsv4;
    VOS_UINT32                          ulRsv5;
    VOS_UINT32                          ulRsv6;
    VOS_UINT32                          ulRsv7;
    VOS_UINT32                          ulRsv8;
    VOS_UINT32                          ulRsv9;
    VOS_UINT32                          ulRsv10;
    VOS_UINT32                          ulRsv11;
    VOS_UINT32                          ulRsv12;
    VOS_UINT32                          ulRsv13;
    VOS_UINT32                          ulRsv14;
    VOS_UINT32                          ulRsv15;
}LNAS_LCS_NV_COMMON_CONFIG_STRU;

/*****************************************************************************
    :LNAS_LMM_NV_T3402_INFO_STRU
    :LNAST3402NV
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucIsT3402DefaultValue;                  /* 340201 */
    VOS_UINT8                           ucRsv[3];                               /*  */
    VOS_UINT32                          ul3402Len;                              /* 3402: */
    NAS_MM_PLMN_LIST_STRU               stT3402EPlmnList;                       /* 3402EPLMNLIST */
}LNAS_LMM_NV_T3402_INFO_STRU;


/*****************************************************************************
    :LNAS_LMM_NV_T3402_CTRL_STRU
    :LNASDATA RETRYT3402PLMNNV
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucT3402PlmnCtrlSwitch;                  /* T3402PLMN01 */
    VOS_UINT8                           ucT3402RmLenStore;                      /* T340201 */
    VOS_UINT8                           ucRsv1;                                 /*  */
    VOS_UINT8                           ucT3402PlmnNum;                         /* astT3402PlmnList */
    NAS_PLMN_T3402_STRU                 astT3402PlmnList[NAS_MM_MAX_T3402_PLMN_NUM];
    VOS_UINT32                          ulT3402DefaultValue;                    /* 3402: */

}LNAS_LMM_NV_T3402_CTRL_STRU;

/*Added by lifuxin for DATA RETRY PHASEII 2016-05-23 start*/
typedef struct
{
    VOS_UINT32                                  ulRemainLogTime;    /*,*/
    VOS_UINT16                                  usEventCnt;         /**/
    VOS_UINT8                                   ucRsv1;
    VOS_UINT8                                   ucRsv2;
    NAS_EMM_PLMN_ID_STRU                        stPlmnId;           /*PLMN ID*/
    NAS_EMM_TAC_STRU                            stTac;              /*Tac*/
}LNAS_EMM_DATA_RETRY_FAIL_EVENT_STRU;

typedef struct
{
    VOS_UINT8                                   ucEmmcause;         /*ID*/
    VOS_UINT8                                   ucRsv1;
    VOS_UINT8                                   ucRsv2;
    VOS_UINT8                                   ucRsv3;
    VOS_UINT32                                  ulEmmFailEventCnt;  /**/
    LNAS_EMM_DATA_RETRY_FAIL_EVENT_STRU         astEmmFailEvent[LNAS_NV_DATA_RETRY_EMM_FAIL_CAUSE_EVENT_CNT];  /*list*/
}LNAS_EMM_DATA_RETRY_FAIL_EVENT_LIST_STRU;

typedef struct
{
    VOS_UINT32                                  aulMaxLogTime[LNAS_NV_DATA_RETRY_EMM_FAIL_CAUSE_NUM];       /**/
    VOS_UINT8                                   aucMaxEventCounter[LNAS_NV_DATA_RETRY_EMM_FAIL_CAUSE_NUM];  /*ulMaxLogTime*/
    VOS_UINT8                                   ucRsv1;
    VOS_UINT8                                   ucRsv2;
	LNAS_EMM_DATA_RETRY_FAIL_EVENT_LIST_STRU    astEventCause[LNAS_NV_DATA_RETRY_EMM_FAIL_CAUSE_NUM];
}LNAS_EMM_DATA_RETRY_NV_PARA_CONFIG_STRU;


typedef struct
{
    VOS_UINT8                           ucApnLen;
    VOS_UINT8                           aucApnName[LNAS_NV_MAX_APN_LEN];
}LNAS_APN_INFO_STRU;

/*****************************************************************************
    :LNAS_APN_PRIO_INFO_STRU
    :
*****************************************************************************/
typedef struct
{
    LNAS_APN_INFO_STRU                  stApnInfo;                              /* APN  */
    NAS_ESM_BEARER_PRIO_ENUM_UINT32     ulBearPrio;                             /* */
}LNAS_APN_PRIO_INFO_STRU;

typedef struct
{
    LNAS_APN_INFO_STRU                  stApnInfo;                          /* APN                */
    VOS_UINT32                          ulRemainTimerLen;                   /*APN*/
}LNAS_ESM_APN_THROT_REMAIN_TIME_INFO_STRU;

typedef struct
{
    VOS_UINT32                                  ulWaitTime;            /* PDNwaittimePDN,:s*/
    VOS_UINT32                                  ulPdnMaxConnTime;      /* PDN:s*/
    VOS_UINT32                                  ulPdnMaxConnCount;     /* PDN*/
    VOS_UINT8                                   ucApnTotalNum;         /* APN */
    VOS_UINT8                                   aucRsv[3];              /*  */

    /* PDN*/
    LNAS_ESM_APN_THROT_REMAIN_TIME_INFO_STRU    astApnThrotRemainTimeInfo[LNAS_NV_MAX_APN_CONTEXT_NUM];
}LNAS_ESM_DATA_RETRY_NV_PARA_CONFIG_STRU;

/*Added by lifuxin for DATA RETRY PHASEII 2016-05-23 end*/

/*****************************************************************************
    :LNAS_LMM_NV_MT_DETACH_TAU_CTRL_STRU
    :LNASDETACHDSDS
             DETACH,UENV.

             (1)ucPlmnNum = 1,PLMNF,PLMN;
             (2),PLMN
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucActiveFlag;                           /* , 1:0: */
    VOS_UINT8                           ucRsv0;                                 /*  */
    VOS_UINT8                           ucRsv1;                                 /*  */
    VOS_UINT8                           ucPlmnNum;                              /* PLMN  */
    NAS_MM_PLMN_ID_STRU                 astPlmnId[NAS_MT_DETACH_TAU_PLMN_MAX_NUM];/* PLMN */
}LNAS_LMM_NV_MT_DETACH_TAU_CTRL_STRU;

/*****************************************************************************
    :LNAS_LMM_NV_NETWORK_FEATURE_VOPS_OPTIMIZE_CTRL_STRU
    :NVzainATTACH_ACPeps_network_feature_support
             ,VOLTEIMS.
             eps network feature support,
             ;NV,IMS,VOPS
             .
             NV
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNetVopsOptimizeCtrl;                  /* , 1:0:.  */
    VOS_UINT8                           ucRsv0;                                 /*  */
    VOS_UINT8                           ucRsv1;                                 /*  */
    VOS_UINT8                           ucRsv2;                                 /*  */
}LNAS_LMM_NV_NETWORK_FEATURE_VOPS_OPTIMIZE_CTRL_STRU;

typedef struct
{
    LNAS_APN_PRIO_INFO_STRU             stApnAndPrioInfo;                       /* APN and Prio INFO */
    VOS_UINT32                          ulT3396RemainLenForNonCustom;           /*  */
    VOS_UINT8                           ucPlmnNum;                              /* PLMN */
    VOS_UINT8                           aucRsv[3];
    NAS_PLMN_T3396_STRU                 astT3396PlmnList[NAS_MM_MAX_T3396_PLMN_NUM];
}LNAS_ESM_T3396_APN_PLMN_INFO_STRU;
/*****************************************************************************
    :LNAS_ESM_NV_T3396_CTRL_CONFIG_STRU
    :LNASDATA RETRYT3396PLMN/APNNV
*****************************************************************************/

typedef struct
{
    VOS_UINT8                           ucT3396CtrlSwitch;                      /* T339601 */
    VOS_UINT8                           ucIsPlmnCustom;                         /* PLMN01 */
    VOS_UINT8                           ucApnTotalNum;                          /* APN */
    VOS_UINT8                           ucRsv;                                  /*  */

    LNAS_ESM_T3396_APN_PLMN_INFO_STRU    astT3396ApnPlmnInfo[LNAS_NV_MAX_APN_CONTEXT_NUM];

}LNAS_ESM_NV_T3396_CTRL_CONFIG_STRU;

/*****************************************************************************
    :LNAS_LMM_NV_EAB_CONFIG_STRU
    :LNASEABNV
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucUeCapacityLowPri;             /* UE 01 */
    VOS_UINT8                           ucUeCapacityEab;                /* UEEAB 01 */
    VOS_UINT8                           ucEabFlag;                      /* EAB01 */
    VOS_UINT8                           ucSigLowPriFlag;                /* NAS Signalling Priority 01 */
    VOS_UINT8                           ucOverrideSigLowPriFlag;        /* NAS Signalling Priority 01 */
    VOS_UINT8                           ucOverrideEabFlag;              /* EAB01 */
    VOS_UINT8                           ucRsv1;
    VOS_UINT8                           ucRsv2;
}LNAS_LMM_NV_EAB_CONFIG_STRU;


/*****************************************************************************
    :LNAS_EMM_NV_T3346_CTRL_CONFIG_STRU
    :LNAS T3346NV
*****************************************************************************/

typedef struct
{
    VOS_UINT8                           ucT3346CtrlSwitch;                      /* T334601 */
    VOS_UINT8                           ucNasSigPrio;                           /* NAS Signalling Priority 01 */
    VOS_UINT8                           ucRsv1;                                 /*  */
    VOS_UINT8                           ucRsv2;                                 /*  */

    VOS_UINT32                          ulT3346RemainLen;                       /*  */
    NAS_MM_PLMN_ID_STRU                 stPlmnId;                               /* PLMN */
    NAS_MM_PLMN_LIST_STRU               stEPlmnList;                            /* equivalent PLMN list */

}LNAS_EMM_NV_T3346_CTRL_CONFIG_STRU;

/*****************************************************************************
    :LNAS_ESM_NV_APN_SWITCH_CTRL_CONFIG_STRU
    :
*****************************************************************************/

typedef struct
{
    VOS_UINT8                           ucApnSwitchForVZW;          /*APN SWTICH : 1 0 */
    VOS_UINT8                           ucApnSwitchForNonVZW;      /*APN SWTICH : 1 0 */
    VOS_UINT8                           ucRsv1;
    VOS_UINT8                           ucRsv2;

}LNAS_ESM_NV_APN_SWITCH_CTRL_CONFIG_STRU;
/*****************************************************************************
    :LNAS_ESM_NV_BACKOFF_CTRL_CONFIG_STRU
    :LNASback-offNV
*****************************************************************************/

typedef struct
{
    VOS_UINT8                           ucBackOffCtrlSwitch;                    /* back-off01 */
    VOS_UINT8                           aucRsv[3];                              /*  */

}LNAS_ESM_NV_BACKOFF_CTRL_CONFIG_STRU;

/*****************************************************************************
    :LNAS_EMM_NV_HO_TAU_DELAY_CTRL_CONFIG_STRU
    :
*****************************************************************************/

typedef struct
{
    VOS_UINT8                           ucSwitchFlag;              /*SWTICH : 1 0 ,*/
    VOS_UINT8                           aucRsv[3];

    VOS_UINT32                          ulHoTauDelayTimeLen;      /*HO TAU DELAY  ms */
}LNAS_EMM_NV_HO_TAU_DELAY_CTRL_CONFIG_STRU;

/*****************************************************************************
    :LNAS_ESM_NV_NDIS_CONN_DELAY_CTRL_CONFIG_STRU
    :
*****************************************************************************/

typedef struct
{
    VOS_UINT8                           ucSwitchFlag;              /* SWTICH : 1 0 ,*/
    VOS_UINT8                           aucRsv[3];

    VOS_UINT32                          ulNdisConnDelayTimeLen;      /*NDIS CONN DELAY  ms */
}LNAS_ESM_NV_NDIS_CONN_DELAY_CTRL_CONFIG_STRU;


/*****************************************************************************
     : LNAS_AUSTRALIA_FLAG_CONFIG_STRU
   :
 ASN.1 :
   : (BIT,)
*****************************************************************************/
typedef struct
{
    VOS_UINT32      ulAustraliaFlag;
    VOS_UINT32      ulRsv;
}LNAS_LMM_NV_AUSTRALIA_FLAG_CONFIG_STRU;
/*****************************************************************************
    :LNAS_ESM_NV_NDIS_CONN_DELAY_CTRL_CONFIG_STRU
    :
*****************************************************************************/

typedef struct
{
    VOS_UINT8                           ucIpv4MtuForImsApnFlag;             /* IMS APNipv4 mtu: 1 0 ,*/
    VOS_UINT8                           ucIpv4MtuForOtherApnFlag;           /*  APNipv4 mtu: 1 0 ,*/
    VOS_UINT8                           aucRsv[2];
}LNAS_ESM_NV_IPV4_MTU_CTRL_CONFIG_STRU;
/*****************************************************************************
    :LNAS_ESM_NV_NDIS_CONN_DELAY_CTRL_CONFIG_STRU
    :
*****************************************************************************/

typedef struct
{
    VOS_UINT8                           ucSwitchFlag;                       /* : 1 0*/
    VOS_UINT8                           aucRsv[3];
    VOS_UINT8                           ucUsimInvalidForGprsMaxValue;       /* GRPS */
    VOS_UINT8                           ucUsimInvalidForNonGprsMaxValue;    /* GRPS */
    VOS_UINT8                           ucPlmnSpecificAttemptMaxValue;      /* PLMN */
    VOS_UINT8                           ucPlmnSpecificPsAttemptMaxValue;    /* PLMN PS */
}LNAS_EMM_NV_PLAIN_NAS_REJ_MSG_CTRL_CONFIG_STRU;
/*****************************************************************************
    :LNAS_ESM_NV_NDIS_CONN_DELAY_CTRL_CONFIG_STRU
    :
*****************************************************************************/

typedef struct
{
    VOS_UINT8                           ucSwitchFlag;                       /* : 1 0*/
    VOS_UINT8                           ucMaxDetachAttemptCnt;              /* detach */
    VOS_UINT8                           aucRsv[2];

}LNAS_EMM_NV_DETACH_ATTEMPT_CNT_CTRL_CONFIG_STRU;



/*****************************************************************************
    :LNAS_ESM_NV_CHANGE_TO_IMSAPN_CONFIG_STRU
    :
*****************************************************************************/

typedef struct
{
    VOS_UINT8                           ucChangeToImsApnFlag;             /* ATTACHIMS APNVOS_TRUE:VOS_fALSE_*/
    VOS_UINT8                           ucRsv1;
    VOS_UINT8                           ucRsv2;
    VOS_UINT8                           ucRsv3;
}LNAS_ESM_NV_CHANGE_TO_IMSAPN_CONFIG_STRU;
/*****************************************************************************
    :LNAS_EMM_NV_STORE_MMC_DETACH_CTRL_CONFIG_STRU
    :
*****************************************************************************/

typedef struct
{
    VOS_UINT8                           ucSwitchFlag;                       /* : 1 0*/
    VOS_UINT8                           aucRsv[3];

}LNAS_EMM_NV_STORE_MMC_DETACH_CTRL_CONFIG_STRU;



/*****************************************************************************
    :LNAS_LMM_NV_ACDC_APP_STRU
    :LNASACDCAPP-ACDCcategory
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               aucOsId[LNAS_NV_ACDC_OSID_LEN];        /* OSID */
    VOS_UINT8                                               aucAppId[LNAS_NV_ACDC_MAX_APPID_LEN];      /* APPID */
    VOS_UINT8                                               ucAcdcCategory;     /* APPID */
    VOS_UINT8                                               ucRsv[3];           /*  */
}LNAS_LMM_NV_ACDC_APP_STRU;

/*****************************************************************************
    :NAS_EMM_MT_DETACH_OPTIMIZE_STRU
    :MT-DETACH
*****************************************************************************/
typedef struct
{
    /*
    MT-detach re-attach-not-required :
    23678111213141525 
    otherother
    */
    VOS_UINT8                           aucMtDetachOptForGivenCauseList[LNAS_NV_MT_DETACH_OPT_OTHER_CAUSE_CNT]; /*MT-DETACH*/
    VOS_UINT16                          usRsv1;
    VOS_UINT16                          usRsv2;
    VOS_UINT16                          usRsv3;
    VOS_UINT16                          usRsv4;
    VOS_UINT32                          ulRsv1;
    VOS_UINT32                          u1Rsv2;
    VOS_UINT32                          ulRsv3;
}LNAS_LMM_NV_MT_DETACH_WITH_OPTIMZIE_CONFIG_STRU;


/*****************************************************************************
    :LNAS_LMM_NV_ACDC_APP_LIST_STRU
    :LNASACDCAPP
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulAppNum;                               /* APP */
    LNAS_LMM_NV_ACDC_APP_STRU           astAcdcAppList[LNAS_NV_ACDC_APP_MAX_NUM]; /* APP */
}LNAS_EMM_NV_ACDC_CONFIG_STRU;

/*****************************************************************************
    : LNAS_LMM_NV_DSDS_OPTIMIZE_FLAG_CONFIG_STRU
  :
ASN.1 :
  : DSDS2.0
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucDsdsOptimizeFlag;                 /* : 1:0: */
    VOS_UINT8                           ucRsv1;
    VOS_UINT8                           ucRsv2;
    VOS_UINT8                           ucRsv3;
}LNAS_LMM_NV_DSDS_OPTIMIZE_FLAG_CONFIG_STRU;

/*****************************************************************************
    : LNAS_LMM_NV_SRLTE_FLAG_CONFIG_STRU
  :
ASN.1 :
  : SRLTE
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucSrlteFlag;                       /* : 1:0: */
    VOS_UINT8                           ucRsv1;
    VOS_UINT8                           ucRsv2;
    VOS_UINT8                           ucRsv3;
}LNAS_LMM_NV_SRLTE_FLAG_CONFIG_STRU;

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

#endif /* end of MmcEmmInterface.h */




