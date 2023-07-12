/******************************************************************************

  Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : TafNvInterface.h
  Description     : TafNvInterface.h header file
  History         :

******************************************************************************/

#ifndef __TAFNVINTERFACE_H__
#define __TAFNVINTERFACE_H__

#include "vos.h"
#include "product_config.h"

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

/*****************************************************************************
  2 Macro
*****************************************************************************/

#define AT_NVIM_SETZ_LEN                (16)
#define AT_NOTSUPPORT_STR_LEN           (16)

/*  */
#define ADS_UL_QUEUE_SCHEDULER_PRI_MAX  (9)

/*WIFI  NV*/
#define AT_WIFI_BASIC_NV_LEN            (116)
#define AT_WIFI_SEC_NV_LEN              (205)

/*WIFI SSID KEY*/
#define AT_WIFI_SSID_LEN_MAX            (33)
#define AT_WIFI_KEY_LEN_MAX             (27)

/* Add by z60575 for multi_ssid, 2012-9-5 begin */
/*  */
#define AT_WIFI_WLAUTHMODE_LEN          (16)

/*  */
#define AT_WIFI_ENCRYPTIONMODES_LEN     (5)

/* WPA */
#define AT_WIFI_WLWPAPSK_LEN            (65)

/* 4SSID */
#define AT_WIFI_MAX_SSID_NUM            (4)

#define AT_WIFI_KEY_NUM                 (AT_WIFI_MAX_SSID_NUM)

#define TAF_CBA_NVIM_MAX_ETWS_DUP_DETECT_SPEC_MCC_NUM            (5)                 /* MCC */
#define TAF_CBA_NV_MAX_USER_SPEC_ETWS_MSGID_RANGE_NUM            (2)

/* 9130IPv6 */
#define TAF_NV_IPV6_FALLBACK_EXT_CAUSE_MAX_NUM      (20)

#define AT_AP_NVIM_XML_RPT_SRV_URL_LEN              (127)
/* Added by l60609 for XML, 2011-08-11 Begin */
#define AT_AP_XML_RPT_SRV_URL_LEN                   (127)
#define AT_AP_XML_RPT_SRV_URL_STR_LEN               (AT_AP_XML_RPT_SRV_URL_LEN + 1)
#define AT_AP_XML_RPT_INFO_TYPE_LEN                 (127)

/*WEB UI */
#define AT_WEBUI_PWD_MAX                            (16)
#define AT_WEBUI_PWD_MAX_SET                        (0)
#define AT_WEBUI_PWD_VERIFY                         (1)

#define AT_AP_NVIM_XML_RPT_INFO_TYPE_LEN            (127)
#define AT_AP_NVIM_XML_RPT_INFO_TYPE_STR_LEN        (AT_AP_NVIM_XML_RPT_INFO_TYPE_LEN + 1)
/* PRODUCT NAME*/
#define AT_PRODUCT_NAME_MAX_NUM                     (29)
#define AT_PRODUCT_NAME_LENGHT                      (AT_PRODUCT_NAME_MAX_NUM + 1)

#define TAF_NVIM_DFS_MAX_PROFILE_NUM                (8)

#define TAF_NVIM_DIFF_DFS_NUM                       (8)

#define TAF_NVIM_MAX_APN_LEN                        (99)
#define TAF_NVIM_MAX_APN_STR_LEN                    (TAF_NVIM_MAX_APN_LEN + 1)

#define AT_MAX_ABORT_CMD_STR_LEN                    (16)
#define AT_MAX_ABORT_RSP_STR_LEN                    (16)

#define AT_NVIM_BODYSARGSM_MAX_PARA_GROUP_NUM       (8)

#define AT_NVIM_RIGHT_PWD_LEN                       (16)

#define TAF_PH_NVIM_MAX_GUL_RAT_NUM                 (3)                 /*AT^syscfgexacqorder */

#define TAF_NVIM_ITEM_IMEI_SIZE                     (16)

#define AT_DISSD_PWD_LEN                            (16)

#define AT_OPWORD_PWD_LEN                           (16)

#define AT_FACINFO_INFO1_LENGTH                     (128)
#define AT_FACINFO_INFO2_LENGTH                     (128)
#define AT_FACINFO_STRING_LENGTH        \
((AT_FACINFO_INFO1_LENGTH + 1) + (AT_FACINFO_INFO2_LENGTH + 1))

#define AT_FACINFO_INFO1_STR_LENGTH                 (AT_FACINFO_INFO1_LENGTH + 1)
#define AT_FACINFO_INFO2_STR_LENGTH                 (AT_FACINFO_INFO2_LENGTH + 1)

#define AT_MDATE_STRING_LENGTH                      (20)

#define MMA_FORB_BAND_NV_MAX_SIZE                   (10)     /* FobBandNV */

#define MMA_OPERTOR_NAME_MAX_SIZE                   (256)

#define TAF_PH_WCDMA_CLASSMAEK1_LEN                         (2)
#define TAF_PH_WCDMA_CLASSMAEK2_LEN                         (4)
#define TAF_PH_WCDMA_CLASSMAEK3_LEN                         (16)

#define TAF_MAX_MFR_ID_LEN                                  (31)
#define TAF_MAX_MFR_ID_STR_LEN                              (TAF_MAX_MFR_ID_LEN + 1)

#define NAS_MMA_NVIM_OPERATOR_NAME_LEN                      (360)

#define TAF_NVIM_ME_PERSONALISATION_PWD_LEN_MAX             (8)

#define TAF_NVIM_MAX_IMSI_LEN                               (15)
#define TAF_NVIM_MAX_IMSI_STR_LEN                           (TAF_NVIM_MAX_IMSI_LEN + 1)

#define TAF_NVIM_MSG_ACTIVE_MESSAGE_MAX_URL_LEN             (160)

/*^AUTHDATA*/
#define TAF_NVIM_MAX_NDIS_USERNAME_LEN_OF_AUTHDATA          (128)                            /* USERNAME 127 */
#define TAF_NVIM_MAX_NDIS_PASSWORD_LEN_OF_AUTHDATA          (128)                            /* PASSWORD 127 */

/*^AUTHDATA<PLMN>*/
#define TAF_NVIM_MAX_NDIS_PLMN_LEN                          (7)

#define TAF_NVIM_PDP_PARA_LEN                               (1952)

#define TAF_PH_PRODUCT_NAME_LEN                             (15)
#define TAF_PH_PRODUCT_NAME_STR_LEN                         (TAF_PH_PRODUCT_NAME_LEN + 1)

/* NV */
#define MN_MSG_SRV_PARAM_LEN                                (8)                 /* NV */
#define MN_MSG_SRV_RCV_SM_ACT_OFFSET                        (0)                 /* NV */
#define MN_MSG_SRV_RCV_SM_MEM_STORE_OFFSET                  (1)                 /* NV */
#define MN_MSG_SRV_RCV_STARPT_ACT_OFFSET                    (2)                 /* c */
#define MN_MSG_SRV_RCV_STARPT_MEM_STORE_OFFSET              (3)                 /* NV */
#define MN_MSG_SRV_CBM_MEM_STORE_OFFSET                     (4)                 /* NV */
#define MN_MSG_SRV_APP_MEM_STATUS_OFFSET                    (5)                 /* APPNV0: 1: */
#define MN_MSG_SRV_SM_MEM_ENABLE_OFFSET                     (6)                 /* NVNV0: 1: */
#define MN_MSG_SRV_MO_DOMAIN_PROTOCOL_OFFSET                (7)                 /* 0: 1: */

#define MN_MSG_MAX_EF_LEN                                   (255)
#define MN_MSG_EFSMSS_PARA_LEN                              (256)
#define MN_MSG_EFSMSP_PARA_LEN                              (256)

#define TAF_PH_SIMLOCK_PLMN_STR_LEN                         (8)                 /* Plmn  */
#define TAF_MAX_SIM_LOCK_RANGE_NUM                          (20)

/* WINSNV */
#define WINS_CONFIG_DISABLE                                 (0)                 /* WINS */
#define WINS_CONFIG_ENABLE                                  (1)                 /* WINS */

#define TAF_CBA_NVIM_MAX_CBMID_RANGE_NUM                    (100)               /* IDCBMIR */
#define TAF_CBA_NVIM_MAX_LABEL_NUM                          (16)                /* BYTE */

#define TAF_SVN_DATA_LENGTH                                 (2)                 /* SVN */

/*  UMTScodec3, */
#define MN_CALL_MAX_UMTS_CODEC_TYPE_NUM                     (7)

#define MN_CALL_NVIM_BC_MAX_SPH_VER_NUM                     (6)
#define MN_CALL_NVIM_MAX_CUSTOM_ECC_NUM                     (20)                /*  */

#define MN_CALL_NVIM_MAX_BCD_NUM_LEN                        (20)

#define TAF_AT_NVIM_CLIENT_CONFIG_LEN                       (64)

#define TAF_AT_NVIM_CLIENT_CFG_LEN                          (96)

#define TAF_NVIM_CBA_MAX_LABEL_NUM                          (16)

#define MTA_BODY_SAR_WBAND_MAX_NUM                          (5)
#define MTA_BODY_SAR_GBAND_MAX_NUM                          (4)

#define MTC_RF_LCD_MIPICLK_MAX_NUM                          (8)                 /* MIPICLK */
#define MTC_RF_LCD_MIPICLK_FREQ_MAX_NUM                     (8)                 /* MIPICLK */

#define TAF_NV_BLACK_LIST_MAX_NUM                           (51)


#define TAF_NVIM_MAX_OPER_NAME_SERVICE_PRIO_NUM              (4)
#define TAF_NVIM_STORED_OPER_NAME_NUM                        (3)

#define TAF_NVIM_IMS2CS_CALL_REDIAL_CAUSE_MAX_NUM     (128)       /* IMS --> CS 128 */
#define TAF_NVIM_IMSA2CS_CALL_REDIAL_CAUSE_MAX_NUM    (64)        /* IMSA --> CS 128 */


#define TAF_NVIM_CALL_REDIAL_CAUSE_MAX_NUM            (32)
#define TAF_NVIM_SS_RETRY_CAUSE_MAX_NUM               (32)
#define TAF_NVIM_SMS_RETRY_CAUSE_MAX_NUM              (32)
#define TAF_NVIM_SMS_NO_RETRY_RP_CAUSE_MAX_NUM        (32)

#define TAF_NVIM_CALL_RETRY_DISC_CAUSE_MAX_NUM               (64)

#define TAF_NVIM_CALL_TRIG_RESEL_DISC_CAUSE_MAX_NUM      (64)

#define TAF_NVIM_KMC_MSG_MAX_KMC_PUB_KEY_LEN          (48)

#define TAF_NVIM_CTCC_OOS_TIMER_MAX_PHASE              (10)

#define TAF_SIM_FORMAT_PLMN_LEN                        (3)                      /* SimPlmn */
#define TAF_NVIM_OTA_SECURITY_MSG_IMSI_PLMN_MAX_NUM    (6)

#define TAF_NVIM_MAX_1X_NW_NORMAL_REL_REDIAL_PHASE_NUM (4)

#define TAF_NVIM_ICC_ID_MAX                             (11)
#define TAF_NVIM_RPM_RSV_PARA_NUM                       (26)

#define TAF_NVIM_MAX_USER_SYS_CFG_RAT_NUM               (5)

#define MTC_INTRUSION_DEVICE_GROUP_MAX_NUM              (8)
#define MTC_INTRUSION_DEVICE_FREQ_CASE_MAX_NUM          (4)
#define MTC_INTRUSION_DEVICE_FREQ_LIST_MAX_NUM          (12)

#define MTC_MODEM_SCELL_MAX_WEIGHT                      (100)               /* Modem */
#define MTC_MODEM_NCELL_MAX_WEIGHT                      (10)                /* Modem */
#define MTC_INTRUSION_FREQ_MAX_WEIGHT                   (10)                /*  */

#define TAF_NVIM_MAX_CTCC_USIM_PLMN_NUM                 (10)

#define TAF_NVIM_MAX_CTCC_CSIM_PLMN_NUM                 (10)

#define MN_MSG_MIN_SRV_PARM_LEN                         (28)                  /*EFSMSP*/

#define TAF_NVIM_CHINA_HOME_NETWORK_NUM_MAX                 (5)

typedef VOS_UINT8  MN_CALL_STATE_ENUM_UINT8;

typedef VOS_UINT32  MMA_QUICK_START_STA_UINT32;

#define TAF_NV_SSA_IMS2CS_REDIAL_CAUSE_MAX_NUM                  (172)

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/
/* ME Storage Function On or Off*/
enum MN_MSG_ME_STORAGE_STATUS_ENUM
{
    MN_MSG_ME_STORAGE_DISABLE           = 0x00,
    MN_MSG_ME_STORAGE_ENABLE            = 0x01,
    MN_MSG_ME_STORAGE_BUTT
};
typedef VOS_UINT8 MN_MSG_ME_STORAGE_STATUS_ENUM_UINT8;

enum AT_UART_LINK_TYPE_ENUM
{
    AT_UART_LINK_TYPE_OM        = 1,          /* OM */
    AT_UART_LINK_TYPE_AT        = 2,          /* AT */
    AT_UART_LINK_TYPE_BUTT
};
typedef VOS_UINT16 AT_UART_LINK_TYPE_ENUM_UINT16;

enum MMA_CUSTOM_CARDLOCK_OPERATOR_ENUM
{
    MMA_CUSTOM_CARDLOCK_NO_AVAILABLE   = 0,                                     /* 0SIMLOCK */
    MMA_CUSTOM_CARDLOCK_EGYPT_VDF,                                              /* 1VDF37SIMLOCK */
    MMA_CUSTOM_CARDLOCK_NORWAY_NETCOM,                                          /* 2NetcommSIMLOCK */
    MMA_CUSTOM_CARDLOCK_MEXICO_TELCEL,                                          /* 3TELCEL334020 */
    MMA_CUSTOM_CARDLOCK_DOMINICA_TELCEL,                                        /* 4TELCEL370023387042502 */
    MMA_CUSTOM_CARDLOCK_BUTT
};


/*****************************************************************************
     : MTA_WCDMA_BAND_ENUM
   : WCDMA
 1.       : 20130227
          : l00198894
      : 
*****************************************************************************/
enum MTA_WCDMA_BAND_ENUM
{
    MTA_WCDMA_I_2100                    = 0x0001,
    MTA_WCDMA_II_1900,
    MTA_WCDMA_III_1800,
    MTA_WCDMA_IV_1700,
    MTA_WCDMA_V_850,
    MTA_WCDMA_VI_800,
    MTA_WCDMA_VII_2600,
    MTA_WCDMA_VIII_900,
    MTA_WCDMA_IX_J1700,
    /* 
    MTA_WCDMA_X,
    */
    MTA_WCDMA_XI_1500                   = 0x000B,
    /* 
    MTA_WCDMA_XII,
    MTA_WCDMA_XIII,
    MTA_WCDMA_XIV,
    MTA_WCDMA_XV,
    MTA_WCDMA_XVI,
    MTA_WCDMA_XVII,
    MTA_WCDMA_XVIII,
    */
    MTA_WCDMA_XIX_850                   = 0x0013,

    MTA_WCDMA_BAND_BUTT
};
typedef VOS_UINT16 MTA_WCDMA_BAND_ENUM_UINT16;

/* Added by s00246516 for L-C, 2014-01-23, Begin */
/*****************************************************************************
     : TAF_NVIM_LC_WORK_CFG_ENUM
   : L-C
 1.       : 20140123
          : s00246516
      : 
*****************************************************************************/
enum TAF_NVIM_LC_WORK_CFG_ENUM
{
    TAF_NVIM_LC_INDEPENT_WORK = 0,
    TAF_NVIM_LC_INTER_WORK    = 1,
    TAF_NVIM_LC_WORK_CFG_BUTT
};
typedef VOS_UINT8 TAF_NVIM_LC_WORK_CFG_ENUM_UINT8;

/*****************************************************************************
     : TAF_NVIM_LC_RAT_COMBINED_ENUM
   : L-C
 1.       : 20140123
          : s00246516
      : 
*****************************************************************************/
enum TAF_NVIM_LC_RAT_COMBINED_ENUM
{
    TAF_NVIM_LC_RAT_COMBINED_GUL  = 0x55,
    TAF_NVIM_LC_RAT_COMBINED_CL   = 0xAA,
    TAF_NVIM_LC_RAT_COMBINED_BUTT
};
typedef VOS_UINT8 TAF_NVIM_LC_RAT_COMBINED_ENUM_UINT8;
/* Added by s00246516 for L-C, 2014-01-23, End */

/*****************************************************************************
     : MTC_PS_TRANSFER_ENUM
   : PS 
 1.       : 20140117
          : l00198894
      : V9R1C53 C+L 
*****************************************************************************/
enum MTC_PS_TRANSFER_ENUM
{
    MTC_PS_TRANSFER_NONE                = 0x00,                                 /* PS */
    MTC_PS_TRANSFER_LOST_AREA           = 0x01,                                 /*  */
    MTC_PS_TRANSFER_OFF_AREA            = 0x02,                                 /*  */

    MTC_PS_TRANSFER_SOLUTION_BUTT
};
typedef VOS_UINT8 MTC_PS_TRANSFER_ENUM_UINT8;


enum TAF_NV_CLIENT_CFG_ENUM
{
    TAF_NV_CLIENT_CFG_PCUI              = 0,
    TAF_NV_CLIENT_CFG_CTRL              = 1,
    TAF_NV_CLIENT_CFG_MODEM             = 2,
    TAF_NV_CLIENT_CFG_NDIS              = 3,
    TAF_NV_CLIENT_CFG_UART              = 4,
    TAF_NV_CLIENT_CFG_SOCK              = 5,
    TAF_NV_CLIENT_CFG_APPSOCK           = 6,
    TAF_NV_CLIENT_CFG_HSIC1             = 7,
    TAF_NV_CLIENT_CFG_HSIC2             = 8,
    TAF_NV_CLIENT_CFG_HSIC3             = 9,
    TAF_NV_CLIENT_CFG_HSIC4             = 10,
    TAF_NV_CLIENT_CFG_MUX1              = 11,
    TAF_NV_CLIENT_CFG_MUX2              = 12,
    TAF_NV_CLIENT_CFG_MUX3              = 13,
    TAF_NV_CLIENT_CFG_MUX4              = 14,
    TAF_NV_CLIENT_CFG_MUX5              = 15,
    TAF_NV_CLIENT_CFG_MUX6              = 16,
    TAF_NV_CLIENT_CFG_MUX7              = 17,
    TAF_NV_CLIENT_CFG_MUX8              = 18,
    TAF_NV_CLIENT_CFG_APP               = 19,
    TAF_NV_CLIENT_CFG_APP1              = 20,
    TAF_NV_CLIENT_CFG_APP2              = 21,
    TAF_NV_CLIENT_CFG_APP3              = 22,
    TAF_NV_CLIENT_CFG_APP4              = 23,
    TAF_NV_CLIENT_CFG_APP5              = 24,
    TAF_NV_CLIENT_CFG_APP6              = 25,
    TAF_NV_CLIENT_CFG_APP7              = 26,
    TAF_NV_CLIENT_CFG_APP8              = 27,
    TAF_NV_CLIENT_CFG_APP9              = 28,
    TAF_NV_CLIENT_CFG_APP10             = 29,
    TAF_NV_CLIENT_CFG_APP11             = 30,
    TAF_NV_CLIENT_CFG_APP12             = 31,
    TAF_NV_CLIENT_CFG_APP13             = 32,
    TAF_NV_CLIENT_CFG_APP14             = 33,
    TAF_NV_CLIENT_CFG_APP15             = 34,
    TAF_NV_CLIENT_CFG_APP16             = 35,
    TAF_NV_CLIENT_CFG_APP17             = 36,
    TAF_NV_CLIENT_CFG_APP18             = 37,
    TAF_NV_CLIENT_CFG_APP19             = 38,
    TAF_NV_CLIENT_CFG_APP20             = 39,
    TAF_NV_CLIENT_CFG_APP21             = 40,
    TAF_NV_CLIENT_CFG_APP22             = 41,
    TAF_NV_CLIENT_CFG_APP23             = 42,
    TAF_NV_CLIENT_CFG_APP24             = 43,
    TAF_NV_CLIENT_CFG_APP25             = 44,
    TAF_NV_CLIENT_CFG_APP26             = 45,
    TAF_NV_CLIENT_CFG_HSIC_MODEM        = 46,
    TAF_NV_CLIENT_CFG_HSUART            = 47,
    TAF_NV_CLIENT_CFG_PCUI2             = 48,

    TAF_NV_CLIENT_CFG_APP27             = 49,
    TAF_NV_CLIENT_CFG_APP28             = 50,
    TAF_NV_CLIENT_CFG_APP29             = 51,
    TAF_NV_CLIENT_CFG_APP30             = 52,
    TAF_NV_CLIENT_CFG_APP31             = 53,
    TAF_NV_CLIENT_CFG_APP32             = 54,
    TAF_NV_CLIENT_CFG_APP33             = 55,
    TAF_NV_CLIENT_CFG_APP34             = 56,
    TAF_NV_CLIENT_CFG_APP35             = 57,
    TAF_NV_CLIENT_CFG_APP36             = 58,
    TAF_NV_CLIENT_CFG_APP37             = 59,
    TAF_NV_CLIENT_CFG_APP38             = 60,
    TAF_NV_CLIENT_CFG_APP39             = 61,
    TAF_NV_CLIENT_CFG_APP40             = 62,
    TAF_NV_CLIENT_CFG_APP41             = 63,
    TAF_NV_CLIENT_CFG_APP42             = 64,
    TAF_NV_CLIENT_CFG_APP43             = 65,
    TAF_NV_CLIENT_CFG_APP44             = 66,
    TAF_NV_CLIENT_CFG_APP45             = 67,
    TAF_NV_CLIENT_CFG_APP46             = 68,
    TAF_NV_CLIENT_CFG_APP47             = 69,
    TAF_NV_CLIENT_CFG_APP48             = 70,
    TAF_NV_CLIENT_CFG_APP49             = 71,
    TAF_NV_CLIENT_CFG_APP50             = 72,
    TAF_NV_CLIENT_CFG_APP51             = 73,
    TAF_NV_CLIENT_CFG_APP52             = 74,
    TAF_NV_CLIENT_CFG_MAX               = TAF_AT_NVIM_CLIENT_CFG_LEN
};
typedef VOS_UINT16 TAF_NV_CLIENT_CFG_ENUM_UINT16;
/*****************************************************************************
     : TAF_FLASH_DIRECTORY_TYPE_ENUM
   : FLASH
 1.       : 20140304
          : f62575
      : DTS2013091009786 FLASH
*****************************************************************************/
enum TAF_FLASH_DIRECTORY_TYPE_ENUM
{

    /* V3R3E5STICK */
    TAF_FLASH_DIRECTORY_TYPE_V3R3E5_V3R3STICK               = 0x00,

    /* V7R2V3R3M2M */
    TAF_FLASH_DIRECTORY_TYPE_V7R2_V3R3M2M                   = 0x01,

    /* V9R1 */
    TAF_FLASH_DIRECTORY_TYPE_V9R1PHONE                      = 0x02,

    /* FLASHK3V3V8R1 */
    TAF_FLASH_DIRECTORY_TYPE_K3V3V8R1                       = 0x03,

    TAF_FLASH_DIRECTORY_TYPE_BUTT
};
typedef VOS_UINT8 TAF_FLASH_DIRECTORY_TYPE_ENUM_UINT16;

/*****************************************************************************
     : TAF_NVIM_RAT_MODE_ENUM
   : 
 1.       : 20140603
          : g00261581
      : V711 Cell Lock
*****************************************************************************/
enum TAF_NVIM_RAT_MODE_ENUM
{
    TAF_NVIM_RAT_MODE_GSM               = 0x01,
    TAF_NVIM_RAT_MODE_WCDMA,
    TAF_NVIM_RAT_MODE_LTE,
    TAF_NVIM_RAT_MODE_CDMA1X,
    TAF_NVIM_RAT_MODE_TDSCDMA,
    TAF_NVIM_RAT_MODE_WIMAX,
    TAF_NVIM_RAT_MODE_EVDO,

    TAF_NVIM_RAT_MODE_BUTT
};
typedef VOS_UINT8 TAF_NVIM_RAT_MODE_ENUM_UINT8;

/*****************************************************************************
     : TAF_NVIM_GSM_BAND_ENUM
   : GSM
 1.       : 20140604
          : g00261581
      : 
*****************************************************************************/
enum TAF_NVIM_GSM_BAND_ENUM
{
    TAF_NVIM_GSM_BAND_850               = 0,
    TAF_NVIM_GSM_BAND_900,
    TAF_NVIM_GSM_BAND_1800,
    TAF_NVIM_GSM_BAND_1900,

    TAF_NVIM_GSM_BAND_BUTT
};
typedef VOS_UINT16 TAF_NVIM_GSM_BAND_ENUM_UINT16;

/*****************************************************************************
     : TAF_NV_ACTIVE_MODEM_MODE_ENUM
   : DSDSModem
 1.       : 20140921
          : l00198894
      : DSDS/
*****************************************************************************/
enum TAF_NV_ACTIVE_MODEM_MODE_ENUM
{
    TAF_NV_ACTIVE_SINGLE_MODEM              = 0x00,
    TAF_NV_ACTIVE_MULTI_MODEM               = 0x01,

    TAF_NV_ACTIVE_MODEM_MODE_BUTT
};
typedef VOS_UINT8 TAF_NV_ACTIVE_MODEM_MODE_ENUM_UINT8;

/*****************************************************************************
     : CNAS_XSMS_DATA_REQ_SEND_CHAN_ENUM
   : 
*****************************************************************************/
enum TAF_XSMS_DATA_REQ_SEND_CHAN_ENUM
{
    TAF_XSMS_DATA_REQ_SEND_CHAN_TRAFFIC_CHAN   = 0x0,
    TAF_XSMS_DATA_REQ_SEND_CHAN_ACCESS_CHAN    = 0x1,
    TAF_XSMS_DATA_REQ_SEND_CHAN_BOTH           = 0x2,
    TAF_XSMS_DATA_REQ_SEND_CHAN_BUTT
};

typedef VOS_UINT8 TAF_XSMS_DATA_REQ_SEND_CHAN_ENUM_UINT8;

/** ****************************************************************************
 * Name        : TAF_MMA_CFREQ_LOCK_MODE_TYPE_ENUM
 *
 * Description :
 *******************************************************************************/
enum TAF_MMA_CFREQ_LOCK_MODE_TYPE_ENUM
{
    TAF_MMA_CFREQ_LOCK_MODE_OFF         = 0x00,     /*  */
    TAF_MMA_CFREQ_LOCK_MODE_ON          = 0x01,     /*  */
    TAF_MMA_CFREQ_LOCK_MODE_BUTT        = 0x02
};
typedef VOS_UINT8 TAF_MMA_CFREQ_LOCK_MODE_TYPE_ENUM_UINT8;

/*****************************************************************************
     : TAF_VC_TTYMODE_ENUM
   : TTY
  1.       : 20150207
           : w00316404
       : 
*****************************************************************************/
enum TAF_VC_TTYMODE_ENUM
{
    TAF_VC_TTY_OFF                      = 0,
    TAF_VC_TTY_FULL                     = 1,
    TAF_VC_TTY_VCO                      = 2,
    TAF_VC_TTY_HCO                      = 3,
    TAF_VC_TTYMODE_BUTT
};
typedef VOS_UINT8 TAF_VC_TTYMODE_ENUM_UINT8;

/*****************************************************************************
     : TAF_CALL_CCWA_CTRL_MODE_ENUM
   : 
 1.       : 2015824
          : n00269697
      : 
*****************************************************************************/
enum TAF_CALL_CCWA_CTRL_MODE_ENUM
{
    TAF_CALL_CCWA_CTRL_BY_NW          = 0,
    TAF_CALL_CCWA_CTRL_BY_UE            = 1,

    TAF_CALL_CCWA_CTRL_MODE_BUTT
};
typedef VOS_UINT8   TAF_CALL_CCWA_CTRL_MODE_ENUM_U8;

/*****************************************************************************
     : TAF_CALL_CCWAI_MODE_ENUM
   : 

 1.       : 20160216
          : n00269697
      : DTS2016021506132ccwaicallcallims
*****************************************************************************/
enum TAF_CALL_CCWAI_MODE_ENUM
{
    TAF_CALL_CCWAI_MODE_DISABLE               = 0,
    TAF_CALL_CCWAI_MODE_ENABLE                = 1,

    TAF_CALL_CCWAI_MODE_BUTT
};
typedef  VOS_UINT8  TAF_CALL_CCWAI_MODE_ENUM_UINT8;

/*****************************************************************************
     : TAF_XSMS_TL_ACK_NEED_LEVEL_ENUM
   : TL_ACK
  1.       : 20160119
           : c00299064
       : 
*****************************************************************************/
enum TAF_XSMS_TL_ACK_NEED_LEVEL_ENUM
{
    TAF_XSMS_TL_ACK_NEED_LEVEL_ALWAYS_NEEDED                    = 0,
    TAF_XSMS_TL_ACK_NEED_LEVEL_NOT_NEEDED_WHEN_RCV_SMS          = 1,  /* TL_ACK */
    TAF_XSMS_TL_ACK_NEED_LEVEL_ALWAYS_NOT_NEEDED                = 2,  /* TL_ACK */

    TAF_XSMS_TL_ACK_NEED_LEVEL_BUTT
};
typedef VOS_UINT8 TAF_XSMS_TL_ACK_NEED_LEVEL_ENUM_UINT8;


/*****************************************************************************
     : TAF_NV_GPS_CHIP_TYPE_ENUM
   : GPS
  1.       : 201679
           : wx270776
       : 
*****************************************************************************/
enum TAF_NV_GPS_CHIP_TYPE_ENUM
{
    TAF_NV_GPS_CHIP_BROADCOM          = 0,
    TAF_NV_GPS_CHIP_HISI1102          = 1,

    TAF_NV_GPS_CHIP_BUTT
};
typedef VOS_UINT8 TAF_NV_GPS_CHIP_TYPE_ENUM_UINT8;
/*****************************************************************************
     : TAF_SPM_NVIM_MULTIMODE_EMC_CS_PRFER_TYPE_ENUM_UINT8
   : CS: 3GPP23GPP
  1.       : 20160719
           : y00245242
       : 
*****************************************************************************/
enum TAF_SPM_NVIM_MULTIMODE_EMC_CS_PRFER_TYPE_ENUM
{
    TAF_SPM_NVIM_MULTIMODE_EMC_CS_NOT_PREFER                = 0,
    TAF_SPM_NVIM_MULTIMODE_EMC_CS_3GPP_PRFER                = 1,
    TAF_SPM_NVIM_MULTIMODE_EMC_CS_3GPP2_PRFER               = 2,

    TAF_SPM_NVIM_MULTIMODE_EMC_CS_PRFER_BUTT
};
typedef VOS_UINT8 TAF_SPM_NVIM_MULTIMODE_EMC_CS_PRFER_TYPE_ENUM_UINT8;

/*****************************************************************************
     : TAF_LSMS_RESEND_FLAG_ENUM
   : 
  1.       : 20160718
           : z00316370
       : 
*****************************************************************************/
enum TAF_LSMS_RESEND_FLAG_ENUM
{
    TAF_LSMS_RESEND_FLAG_DISABLE          = 0,  /*  */
    TAF_LSMS_RESEND_FLAG_ENABLE           = 1,  /*  */

    TAF_LSMS_RESEND_FLAG_BUTT
};
typedef VOS_UINT8 TAF_LSMS_RESEND_FLAG_ENUM_UINT8;

/*****************************************************************************
     : TAF_IMS2CS_REDIAL_AFTER_ALERTING_DOMAIN_ENUM
   : IMSCS
  1.       : 20171125
           : j00174725
       : 
*****************************************************************************/
enum TAF_IMS2CS_REDIAL_AFTER_ALERTING_DOMAIN_ENUM
{
    TAF_IMS2CS_REDIAL_AFTER_ALERTING_NONE                   = 0,                /*  */
    TAF_IMS2CS_REDIAL_AFTER_ALERTING_WIFI                   = 1,                /* VOWIFI */
    TAF_IMS2CS_REDIAL_AFTER_ALERTING_LTE                    = 2,                /* IMS */
    TAF_IMS2CS_REDIAL_AFTER_ALERTING_WIFI_LTE               = 3,                /* IMS & WIFI */

    TAF_IMSCALL_2_CS_REDIAL_AFTER_ALERTING_BUTT
};
typedef VOS_UINT8 TAF_IMS2CS_REDIAL_AFTER_ALERTING_DOMAIN_ENUM_UINT8;

/*****************************************************************************
  5 STRUCT
*****************************************************************************/
/*****************************************************************************
     : TAF_AT_TZ_STRU
   : en_NV_Item_ATSETZ_RET_VALUE NV
  1.       : 2011725
           : z00161729
       : 
*****************************************************************************/
typedef struct
{
    VOS_INT8    acTz[AT_NVIM_SETZ_LEN];
}TAF_AT_TZ_STRU;

/*****************************************************************************
     : AT_NOT_SUPPORT_CMD_ERROR_TEXT_STRU
   : en_NV_Item_NOT_SUPPORT_RET_VALUE NV
  1.       : 2013522
           : l00167671
       : 
*****************************************************************************/
typedef struct
{
    VOS_INT8    acErrorText[AT_NOTSUPPORT_STR_LEN];
}TAF_AT_NOT_SUPPORT_CMD_ERROR_TEXT_STRU;

/*****************************************************************************
    : ADS_UL_QUEUE_SCHEDULER_PRI_NV_STRU
  : ADSNV

  1.       : 20120224
           : f00179208
       : 
*****************************************************************************/
typedef struct
{
    /* NV 0: 1: */
    VOS_UINT32                              ulStatus;

    /*  */
    VOS_UINT16                              ausPriWeightedNum[ADS_UL_QUEUE_SCHEDULER_PRI_MAX];
    VOS_UINT8                               aucRsv[2];
}ADS_UL_QUEUE_SCHEDULER_PRI_NV_STRU;

/*****************************************************************************
     : TAF_TAF_AT_MULTI_WIFI_SSID_STRU
   :
 ASN.1 :
   : en_NV_Item_MULTI_WIFI_STATUS_SSID NV
             wifi SSIDNVSSID
             PADDINGUINT8
             aucwlSsid[AT_WIFI_MAX_SSID_NUM][AT_WIFI_SSID_LEN_MAX];
             ulwlChannel;
             ulwlHide;
             aucwlCountry[NV_WLCOUNTRY_CODE_LEN];
             aucwlMode[NV_WLMODE_LEN];
             ulwlRate;
             ulwlTxPwrPcnt;
             ulwlMaxAssoc;
             ucwlEnbl;
             ulwlFrgThrshld;
             ulwlRtsThrshld;
             ulwlDtmIntvl;
             ulwlBcnIntvl;
             ulwlWme;
             ulwlPamode;
             ulwlIsolate;
             ulwlProtectionmode;
             ulwloffenable;
             ucwlofftime;
             aucwlExtends[12];
             ucReserve;

  1.       : 2012915
           : z60575
       : 
*****************************************************************************/

typedef struct
{

    VOS_UINT8    aucWifiSsid[AT_WIFI_MAX_SSID_NUM][AT_WIFI_SSID_LEN_MAX];
    VOS_UINT8    aucReserved[84];
}TAF_AT_MULTI_WIFI_SSID_STRU;

/*****************************************************************************
     : TAF_AT_MULTI_WIFI_SEC_STRU
   :
 ASN.1 :
   : en_NV_Item_MULTI_WIFI_KEY NV
             wifi 
             nv_wifisec_typeNV50012nv_wifisec_type
             aucwlAuthMode              
             aucBasicEncryptionModes    
             aucWPAEncryptionModes      WPA
             aucWifiWepKey1...aucWifiWepKey4               WIFI KEY
             ucWifiWepKeyIndex          WIFI KEY index,1wlKeys1
             aucWpaPsk                  WPA
             ucWpsEnable                wps
             ucWpsCfg                   registerenrollee,  0:();  1:

  1.       : 2012915
           : z60575
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8    aucWifiAuthmode[AT_WIFI_WLAUTHMODE_LEN];
    VOS_UINT8    aucWifiBasicencryptionmodes[AT_WIFI_ENCRYPTIONMODES_LEN];
    VOS_UINT8    aucWifiWpaencryptionmodes[AT_WIFI_ENCRYPTIONMODES_LEN];
    VOS_UINT8    aucWifiWepKey1[AT_WIFI_MAX_SSID_NUM][AT_WIFI_KEY_LEN_MAX];
    VOS_UINT8    aucWifiWepKey2[AT_WIFI_MAX_SSID_NUM][AT_WIFI_KEY_LEN_MAX];
    VOS_UINT8    aucWifiWepKey3[AT_WIFI_MAX_SSID_NUM][AT_WIFI_KEY_LEN_MAX];
    VOS_UINT8    aucWifiWepKey4[AT_WIFI_MAX_SSID_NUM][AT_WIFI_KEY_LEN_MAX];
    VOS_UINT8    ucWifiWepKeyIndex[AT_WIFI_MAX_SSID_NUM];
    VOS_UINT8    aucWifiWpapsk[AT_WIFI_MAX_SSID_NUM][AT_WIFI_WLWPAPSK_LEN];
    VOS_UINT8    ucWifiWpsenbl;
    VOS_UINT8    ucWifiWpscfg;
}TAF_AT_MULTI_WIFI_SEC_STRU;

/*****************************************************************************
     : TAF_AT_NVIM_AP_RPT_SRV_URL_STRU
   : TAF_AT_NVIM_AP_RPT_SRV_URL_STRU
  1.       : 2013522
           : l00167671
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8 aucApRptSrvUrl[AT_AP_XML_RPT_SRV_URL_STR_LEN];
}TAF_AT_NVIM_AP_RPT_SRV_URL_STRU;

/*****************************************************************************
     : TAF_AT_NVIM_WEB_ADMIN_PASSWORD_STRU
   : en_NV_Item_WEB_ADMIN_PASSWORD
  1.       : 2013522
           : l00167671
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8 aucWebPwd[AT_WEBUI_PWD_MAX];
}TAF_AT_NVIM_WEB_ADMIN_PASSWORD_STRU;

/*****************************************************************************
     : TAF_AT_NVIM_AP_XML_INFO_TYPE_STRU
   : TAF_AT_NVIM_AP_XML_INFO_TYPE_STRU
  1.       : 2013522
           : l00167671
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8 aucApXmlInfoType[AT_AP_NVIM_XML_RPT_INFO_TYPE_STR_LEN];
}TAF_AT_NVIM_AP_XML_INFO_TYPE_STRU;

/*****************************************************************************
     : MMA_CUSTOM_CARDLOCK_OPERATOR_STRU
   : MMA_CUSTOM_CARDLOCK_OPERATOR_STRU
  1.       : 2013522
           : l00167671
       : 
  2.       : 201532
           : w00316404
       : reserve
*****************************************************************************/
/*lint -e958 -e959 :l60609;:64bit*/
typedef struct
{
    VOS_UINT32                          ulNvStatus;
    VOS_UINT8                           aucProductId[AT_PRODUCT_NAME_LENGHT];   /* product id */
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}TAF_AT_PRODUCT_ID_STRU;
/*lint +e958 +e959 :l60609;:64bit*/

/* TIMNV */
/*****************************************************************************
     : NAS_NV_PPP_DIAL_ERR_CODE_STRU
   : en_NV_Item_PPP_DIAL_ERR_CODE(50061)
  1.       : 2013522
           : m00217266
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucStatus;                               /* 1: NV0 */
    VOS_UINT8                           ucErrCodeRpt;                           /*1: 0,  1*/
}NAS_NV_PPP_DIAL_ERR_CODE_STRU;

/*****************************************************************************
     : AT_NVIM_ABORT_CMD_PARA_STRU
   : AT, NV
             "AT", "ABORT". 

  1.       : 20120921
           : L00171473
       : for V7R1C50_At_Abort,  
  2.       : 201532
           : w00316404
       : reserve
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucAbortEnableFlg;                           /* AT */
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
    VOS_UINT8                           ucReserve3;
    VOS_UINT8                           aucAbortAtCmdStr[AT_MAX_ABORT_CMD_STR_LEN]; /* AT */
    VOS_UINT8                           aucAbortAtRspStr[AT_MAX_ABORT_RSP_STR_LEN]; /*  */
}AT_NVIM_ABORT_CMD_PARA_STRU;

/*****************************************************************************
    : AT_BODYSARGSM_SET_PARA_STRU
  : Body SAR
1.      : 20130312
        : l00198894
    : Body SAR
*****************************************************************************/
typedef struct
{
    VOS_UINT8                   ucParaNum;                                      /*  */
    VOS_UINT8                   ucRsv[3];                                       /*  */
    VOS_INT16                   asPower[AT_NVIM_BODYSARGSM_MAX_PARA_GROUP_NUM];      /* G */
    VOS_UINT32                  aulBand[AT_NVIM_BODYSARGSM_MAX_PARA_GROUP_NUM];      /* G */
}AT_BODYSARGSM_SET_PARA_STRU;

/*****************************************************************************
     : TAF_AT_NVIM_RIGHT_OPEN_FLAG_STRU
   : en_NV_Item_AT_RIGHT_PASSWORD NV
  1.       : 2013522
           : l00167671
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          enRightOpenFlg;
    VOS_INT8                            acPassword[AT_NVIM_RIGHT_PWD_LEN];
}TAF_AT_NVIM_RIGHT_OPEN_FLAG_STRU;

/*****************************************************************************
     : NAS_NV_GWMAC_ADDR_STRU
   : RABM_TOTAL_RX_BYTES(39126)
  1.       : 2013522
           : l00167671
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT32 ulDSTotalSendFluxLow;
    VOS_UINT32 ulDSTotalSendFluxHigh;
    VOS_UINT32 ulDSTotalReceiveFluxLow;
    VOS_UINT32 ulDSTotalReceiveFluxHigh;
    TAF_AT_NVIM_RIGHT_OPEN_FLAG_STRU stRightPwd;
}NAS_NV_RABM_TOTAL_RX_BYTES_STRU;

/*****************************************************************************
    : IMEI_STRU
  : en_NV_Item_IMEI(0)
1.       : 2013522
         : m00217266
     : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                          aucImei[TAF_NVIM_ITEM_IMEI_SIZE];
}IMEI_STRU;

/*****************************************************************************
    : TAF_AT_NVIM_DISSD_PWD_STRU
  : en_NV_Item_AT_DISSD_PWD(43)
1.       : 2013522
         : m00217266
     : 
*****************************************************************************/
typedef struct
{
    VOS_INT8                           acATE5DissdPwd[AT_DISSD_PWD_LEN];
}TAF_AT_NVIM_DISSD_PWD_STRU;

/*****************************************************************************
    : TAF_AT_NVIM_DISLOG_PWD_NEW_STRU
  : en_NV_Item_AT_DISLOG_PWD_NEW(48)
1.       : 2013522
         : m00217266
     : 
*****************************************************************************/
typedef struct
{
    VOS_INT8                           acATOpwordPwd[AT_OPWORD_PWD_LEN];
}TAF_AT_NVIM_DISLOG_PWD_NEW_STRU;

/*****************************************************************************
     : TAF_AT_EQ_VER_STRU
   : TAF_AT_EQ_VER_STRU
  1.       : 2013522
           : l00167671
       : 
  2.       : 201532
           : w00316404
       : reserve
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usEqver;
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}TAF_AT_EQ_VER_STRU;

/*****************************************************************************
     : TAF_NVIM_CS_VER_STRU
   : NAS_PREVENT_TEST_IMSI_REG_STRU
  1.       : 2013522
           : l00167671
       : 
  2.       : 201532
           : w00316404
       : reserve
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usCsver;
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}TAF_NVIM_CS_VER_STRU;

/*****************************************************************************
     : NAS_PREVENT_TEST_IMSI_REG_STRU
   : NAS_PREVENT_TEST_IMSI_REG_STRU
  1.       : 2013522
           : l00167671
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8   ucEnableFlag;
    VOS_UINT8   ucReserve;
}NAS_RABM_NVIM_FASTDORM_ENABLE_FLG_STRU;

/*****************************************************************************
    : AT_IPV6_CAPABILITY_STRU
    :
 ASN.1  :
    : IPV6NV
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucStatus;           /* NV, 1: 0 */
    VOS_UINT8                           ucIpv6Capablity;    /* IPV6 */
    VOS_UINT8                           aucReversed[2];     /*  */

} AT_NV_IPV6_CAPABILITY_STRU;

/*****************************************************************************
     : NAS_PREVENT_TEST_IMSI_REG_STRU
   : NAS_PREVENT_TEST_IMSI_REG_STRU
  1.       : 2013522
           : l00167671
       : 
  2.       : 201532
           : w00316404
       : reserve
*****************************************************************************/
typedef struct
{

    VOS_UINT8   ucGsmConnectRate;
    VOS_UINT8   ucGprsConnectRate;
    VOS_UINT8   ucEdgeConnectRate;
    VOS_UINT8   ucWcdmaConnectRate;
    VOS_UINT8   ucDpaConnectRate;
    VOS_UINT8   ucReserve1;
    VOS_UINT8   ucReserve2;
    VOS_UINT8   ucReserve3;
}AT_NVIM_DIAL_CONNECT_DISPLAY_RATE_STRU;

/*****************************************************************************
     : AT_TRAFFIC_CLASS_CUSTOMIZE_STRU
   : PDPQoS Traffic Class
*****************************************************************************/

typedef struct
{
    VOS_UINT8                          ucStatus;                         /* 1: NV0 */
    VOS_UINT8                          ucTrafficClass;                   /* Traffic Class */
    VOS_UINT8                          ucReserve1;
    VOS_UINT8                          ucReserve2;
}AT_TRAFFIC_CLASS_CUSTOMIZE_STRU;

/*****************************************************************************
    : AT_SS_CUSTOMIZE_PARA_STRU
  : SS
            NVucStatus0: 1: 
            SS
            BIT 0 +CCWA0 1: 
            BIT 1 +CLCK0 1: 
1.      : 20130124
        : f62575
    : SS
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucStatus;                               /* NV,  */
    VOS_UINT8                           ucSsCmdCustomize;
    VOS_UINT8                           aucReserved1[2];
} AT_SS_CUSTOMIZE_PARA_STRU;

/*****************************************************************************
     : TAF_AT_NVIM_CIMI_PORT_CFG_STRU
   : TAF_AT_NVIM_CIMI_PORT_CFG_STRU
  1.       : 2013522
           : l00167671
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT32 ulCimiPortCfg;
}TAF_AT_NVIM_CIMI_PORT_CFG_STRU;

/*****************************************************************************
     : TAF_AT_NVIM_MUX_REPORT_CFG_STRU
   : TAF_AT_NVIM_MUX_REPORT_CFG_STRU
  1.       : 2013522
           : l00167671
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT32 ulMuxReportCfg;
}TAF_AT_NVIM_MUX_REPORT_CFG_STRU;

/*****************************************************************************
     : NAS_MN_NVIM_TOTAL_MSG_STRU
   : NAS_MN_NVIM_TOTAL_MSG_STRU
  1.       : 2013522
           : l00167671
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT32 ulTotalMsg;
}NAS_MN_NVIM_TOTAL_MSG_STRU;

/*****************************************************************************
     : TAF_AT_NVIM_AP_XML_RPT_FLG_STRU
   : TAF_AT_NVIM_AP_XML_RPT_FLG_STRU
  1.       : 2013522
           : l00167671
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8   ucApXmlRptFlg;
    VOS_UINT8   ucReserve[3];
}TAF_AT_NVIM_AP_XML_RPT_FLG_STRU;

/* Added by l60609 for XML, 2011-08-11 End */

/*****************************************************************************
     : AT_CLIENT_BASIC_INFO_STRU
   : AT

  1.       : 20121220
           : L60609
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usModemId;                              /* modem */
    VOS_UINT8                           ucReportFlg;                            /* VOS_TRUEVOS_FALSE */
    VOS_UINT8                           aucRsv[1];
}AT_NVIM_CLIENT_CONFIGURATION_STRU;

/*****************************************************************************
     : NAS_MMA_NVIM_FORBAND_STRU
   : NAS_MMA_NVIM_FORBAND_STRU
  1.       : 2013522
           : l00167671
       : 
  2.       : 201532
           : w00316404
       : reserve
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucForband[MMA_FORB_BAND_NV_MAX_SIZE];
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}NAS_MMA_NVIM_FORBAND_STRU;


/*****************************************************************************
     : NAS_MMA_NVIM_OPERATOR_NAME_STRU
   : NAS_MMA_NVIM_OPERATOR_NAME_STRU
  1.       : 2013522
           : l00167671
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8 aucRcvData[MMA_OPERTOR_NAME_MAX_SIZE];
}NAS_MMA_NVIM_OPERATOR_NAME_STRU;

/*****************************************************************************
    : NAS_NVIM_FOLLOWON_OPENSPEED_FLAG_STRU
  : en_NV_Item_FollowOn_OpenSpeed_Flag(6656)
1.       : 2013522
         : m00217266
     : 
*****************************************************************************/
typedef struct
{
    MMA_QUICK_START_STA_UINT32          ulQuickStartSta;
}NAS_NVIM_FOLLOWON_OPENSPEED_FLAG_STRU;

/*****************************************************************************
    : NAS_MMA_NVIM_CLASSMARK1_STRU
  : en_NV_Item_Classmark1(8194)
1.       : 2013522
         : m00217266
     : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucClassmark1[TAF_PH_WCDMA_CLASSMAEK1_LEN];
}NAS_MMA_NVIM_CLASSMARK1_STRU;

/*****************************************************************************
    : NAS_MMA_NVIM_CLASSMARK2_STRU
  : en_NV_Item_Classmark2(8195)
1.       : 2013522
         : m00217266
     : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8 aucClassmark2[TAF_PH_WCDMA_CLASSMAEK2_LEN];
}NAS_MMA_NVIM_CLASSMARK2_STRU;

/*****************************************************************************
    : NAS_MMA_NVIM_CLASSMARK3_STRU
  : en_NV_Item_Classmark3(8196)
1.       : 2013522
         : m00217266
     : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8 aucClassmark3[TAF_PH_WCDMA_CLASSMAEK3_LEN];
}NAS_MMA_NVIM_CLASSMARK3_STRU;

/*****************************************************************************
    : TAF_NVIM_SMS_SERVICE_PARA_STRU
  : en_NV_Item_SMS_SERVICE_Para(8237)
1.       : 2013522
         : m00217266
     : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8   aucSmsServicePara[MN_MSG_SRV_PARAM_LEN];
}TAF_NVIM_SMS_SERVICE_PARA_STRU;

/*****************************************************************************
    : TAF_MMA_NVIM_SMS_EFSMSS_PARA_STRU
  : en_NV_Item_SMS_EFSMSS_Para(8238)
1.       : 2013522
         : m00217266
     : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8   aucSmsEfsmssPara[MN_MSG_EFSMSS_PARA_LEN];
}TAF_MMA_NVIM_SMS_EFSMSS_PARA_STRU;

/*****************************************************************************
    : TAF_MMA_NVIM_SMS_EFSMSP_PARA_STRU
  : en_NV_Item_SMS_EFSMSP_Para(8239)
1.       : 2013522
         : m00217266
     : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8   aucSmsEfsmspPara[MN_MSG_EFSMSP_PARA_LEN];
}TAF_MMA_NVIM_SMS_EFSMSP_PARA_STRU;

/*****************************************************************************
    : MN_MSG_NVIM_EFSMSP_PRESETED_STRU
  : en_NV_Item_Smsp_Preseted(2422)
1.       : 20161103
         : q00380176
     : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8   ucActFlg;                                                       /* NV: 01 */
    VOS_UINT8   ucReserved1;
    VOS_UINT8   ucReserved2;
    VOS_UINT8   ucReserved3;
    VOS_UINT8   aucSmscAddr[MN_MSG_MIN_SRV_PARM_LEN];                           /* NV */
}MN_MSG_NVIM_EFSMSP_PRESETED_STRU;

/*****************************************************************************
    : NAS_MMA_SIM_PERSONAL_PWD_STRU
  : en_NV_Item_Sim_Personalisation_Pwd(8253)
1.       : 2013522
         : m00217266
     : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8  aucPwd[TAF_NVIM_ME_PERSONALISATION_PWD_LEN_MAX];
}TAF_MMA_SIM_PERSONAL_PWD_STRU;

/*****************************************************************************
    : NAS_MMA_SIM_PERSONAL_IMST_STRU
  : en_NV_Item_Sim_Personalisation_Imsi_Str(8254)
1.       : 2013522
         : m00217266
     : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8  aucImsiStr[TAF_NVIM_MAX_IMSI_STR_LEN];
}NAS_MMA_SIM_PERSONAL_IMST_STRU;

/*****************************************************************************
    : NAS_MMA_NVIM_DISPLAY_SPN_FLAG_STRU
  : en_NV_Item_Display_Spn_Flag(8296)
1.       : 2013522
         : m00217266
     : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucDisplaySpnFlag[2];
}NAS_MMA_NVIM_DISPLAY_SPN_FLAG_STRU;

/*****************************************************************************
    : TAF_AT_NVIM_RXDIV_CONFIG_STRU
  : en_NV_Item_RXDIV_CONFIG(8319)
1.       : 2013522
         : m00217266
     : 
2.       : 201532
         : w00316404
     : reserve
*****************************************************************************/
typedef struct
{
    VOS_UINT8   ucVaild;
    VOS_UINT8   ucReserved1;
    VOS_UINT8   ucReserved2;
    VOS_UINT8   ucReserved3;
}TAF_AT_NVIM_RXDIV_CONFIG_STRU;

/*****************************************************************************
    : TAF_AT_NVIM_SMS_ACTIVE_MESSAGE_STRU
  : en_NV_Item_SMS_ActiveMessage_Para(8322)
1.       : 2013522
         : m00217266
     : 
2.       : 201532
         : w00316404
     : reserve
*****************************************************************************/
/*lint -e958 -e959 :l60609;:64bit*/
typedef struct
{
    VOS_INT8    cStatus;
    VOS_UINT8   ucEncodeType;
    VOS_UINT8   ucReserved1;
    VOS_UINT8   ucReserved2;
    VOS_UINT32  ulLength;
    VOS_UINT8   ucData[TAF_NVIM_MSG_ACTIVE_MESSAGE_MAX_URL_LEN];
}TAF_AT_NVIM_SMS_ACTIVE_MESSAGE_STRU;
/*lint +e958 +e959 :l60609;:64bit*/

/*8301-8312*/
/*****************************************************************************
    : TAF_NVIM_NDIS_AUTHDATA_STRU
  : en_NV_Item_NDIS_Authdata_0(8301-8312)#
1.       : 2013522
         : m00217266
     : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucAuthType;
    VOS_UINT8                           aucPlmn[TAF_NVIM_MAX_NDIS_PLMN_LEN];
    VOS_UINT8                           aucPassword[TAF_NVIM_MAX_NDIS_PASSWORD_LEN_OF_AUTHDATA];
    VOS_UINT8                           aucUsername[TAF_NVIM_MAX_NDIS_USERNAME_LEN_OF_AUTHDATA];
}TAF_NVIM_NDIS_AUTHDATA_STRU;

/*****************************************************************************
    : TAF_NVIM_NDIS_AUTHDATA_TABLE_STRU
  : en_NV_Item_NDIS_Authdata_0(8301-8312)#
1.       : 2013522
         : m00217266
     : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucUsed;                                             /*01*/
    VOS_UINT8                           aucRsv[3];
    TAF_NVIM_NDIS_AUTHDATA_STRU         stAuthData;                                         /**/
}TAF_NVIM_NDIS_AUTHDATA_TABLE_STRU;

/*8451-8462 en_NV_Item_Taf_PdpPara_0*/
/*****************************************************************************
    : TAF_NVIM_PDP_PARA_STRU
  : en_NV_Item_Taf_PdpPara_0(8451-8462)#
1.       : 2013522
         : m00217266
     : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8          aucPdpPara[TAF_NVIM_PDP_PARA_LEN];
}TAF_NVIM_PDP_PARA_STRU;

/* en_NV_Item_ProductName 8205 */
/*****************************************************************************
    : TAF_PH_PRODUCT_NAME_STRU
  : en_NV_Item_ProductName(8205)#
1.       : 2013522
         : m00217266
     : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8          aucProductName[TAF_PH_PRODUCT_NAME_STR_LEN];
}TAF_PH_PRODUCT_NAME_STRU;

/*en_NV_Item_Imei_Svn 8337*/
/*****************************************************************************
    : TAF_SVN_DATA_STRU
  : en_NV_Item_Imei_Svn(8337)#
1.       : 2013522
         : m00217266
     : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucActiveFlag;
    VOS_UINT8                           aucSvn[TAF_SVN_DATA_LENGTH];
    VOS_UINT8                           aucReserve[1];
}TAF_SVN_DATA_STRU;

/*en_NV_Item_SMS_MO_RETRY_PERIOD 8293*/
/*****************************************************************************
    : MN_MSG_NVIM_RETRY_PERIOD_STRU
  : en_NV_Item_SMS_MO_RETRY_PERIOD(8293)#
1.       : 2013522
         : m00217266
     : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucActFlg;                                           /* NVIM */
    VOS_UINT8                           ucReserved[3];
    VOS_UINT32                          ulRetryPeriod;                                      /**/
}MN_MSG_NVIM_RETRY_PERIOD_STRU;

/*en_NV_Item_SMS_MO_RETRY_INTERVAL 8294*/
/*****************************************************************************
    : MN_MSG_NVIM_RETRY_INTERVAL_STRU
  : en_NV_Item_SMS_MO_RETRY_INTERVAL(8294)#
1.       : 2013522
         : m00217266
     : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucActFlg;                               /* NVIM */
    VOS_UINT8                           ucReserved[3];
    VOS_UINT32                          ulRetryInterval;                        /**/
}MN_MSG_NVIM_RETRY_INTERVAL_STRU;

/*****************************************************************************
    : MN_MSG_NVIM_CHECK_USIM_CSIM_SMS_STATUS_CFG_STRU
  : en_NV_Item_CHECK_USIM_CSIM_SMS_STATUS_CFG(2416)#
1.       : 20161013
         : q00380176
     : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucUsimActFlg;                           /* USIM SMS */
    VOS_UINT8                           ucCsimActFlg;                           /* CSIM SMS */
    VOS_UINT16                          usTimerLength;                          /* USIMCSIM, */
}MN_MSG_NVIM_CHECK_USIM_CSIM_SMS_STATUS_CFG_STRU;
/*****************************************************************************
    : TAF_MSG_NVIM_RETRY_CM_SRV_REJ_CFG_STRU
  : en_NV_Item_SMS_RETRY_CN_SRV_REJ_CAUSE_CFG
  1.       : 2015829
           : s00217060
       : 
*****************************************************************************/typedef struct
{
    VOS_UINT8                           ucSmsRetryCmSrvRejCauseNum;
    VOS_UINT8                           aucReserved[3];
    VOS_UINT8                           aucSmsRetryCmSrvRejCause[TAF_NVIM_SMS_RETRY_CAUSE_MAX_NUM];
}TAF_MSG_NVIM_RETRY_CM_SRV_REJ_CFG_STRU;

/*****************************************************************************
    : TAF_MSG_NVIM_NO_RETRY_RP_CAUSE_CFG_STRU
  : en_NV_Item_SMS_RETRY_RP_CAUSE_CFG
  1.       : 2016514
           : n00269697
       : RP CAUSE38
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucSmsNoRetryRpCauseNum;
    VOS_UINT8                           aucReserved1;
    VOS_UINT8                           aucReserved2;
    VOS_UINT8                           aucReserved3;
    VOS_UINT8                           aucSmsNoRetryRpCause[TAF_NVIM_SMS_NO_RETRY_RP_CAUSE_MAX_NUM];
}TAF_MSG_NVIM_NO_RETRY_RP_CAUSE_CFG_STRU;

/*en_NV_Item_SMS_SEND_DOMAIN 8295*/
/* NVIM */
/*****************************************************************************
    : AT_NVIM_SEND_DOMAIN_STRU
  : en_NV_Item_SMS_SEND_DOMAIN(8295)#
1.       : 2013522
         : m00217266
     : 
2.       : 201532
         : w00316404
     : reserve
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucActFlg;
    VOS_UINT8                           ucSendDomain;
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}AT_NVIM_SEND_DOMAIN_STRU;

/*en_NV_Item_WINS_Config 8297*/
/*****************************************************************************
    : WINS_CONFIG_STRU
  : en_NV_Item_WINS_Config(8297)#
1.       : 2013522
         : m00217266
     : 
2.       : 201532
         : w00316404
     : reserve
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucStatus;        /* 1: NV0 */
    VOS_UINT8                           ucWins;          /* WINS: 0Disable,  1Enable */
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}WINS_CONFIG_STRU;

/*en_NV_Item_CustomizeSimLockPlmnInfo 8267*/
/*****************************************************************************
    : TAF_CUSTOM_SIM_LOCK_PLMN_RANGE_STRU
  : en_NV_Item_CustomizeSimLockPlmnInfo(8267)#
            SIM LOCKPLMN
1.       : 2013522
         : m00217266
     : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucMncNum;
    VOS_UINT8                           aucRangeBegin[TAF_PH_SIMLOCK_PLMN_STR_LEN];
    VOS_UINT8                           aucRangeEnd[TAF_PH_SIMLOCK_PLMN_STR_LEN];
}TAF_CUSTOM_SIM_LOCK_PLMN_RANGE_STRU;

/*****************************************************************************
    : TAF_CUSTOM_SIM_LOCK_PLMN_INFO_STRU
  : en_NV_Item_CustomizeSimLockPlmnInfo(8267)#
1.       : 2013522
         : m00217266
     : 
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulStatus;/*01 */
    TAF_CUSTOM_SIM_LOCK_PLMN_RANGE_STRU astSimLockPlmnRange[TAF_MAX_SIM_LOCK_RANGE_NUM];
}TAF_CUSTOM_SIM_LOCK_PLMN_INFO_STRU;

/* en_NV_Item_CardlockStatus 8268 */
/*****************************************************************************
    : TAF_NVIM_CUSTOM_CARDLOCK_STATUS_STRU
  : en_NV_Item_CardlockStatus(8268)#
            SIM LOCK
1.       : 2013522
         : m00217266
     : 
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulStatus;            /*01 */
    VOS_UINT32                          ulCardlockStatus;    /**/
    VOS_UINT32                          ulRemainUnlockTimes; /**/
}TAF_NVIM_CUSTOM_CARDLOCK_STATUS_STRU;

/*en_NV_Item_CustomizeSimLockMaxTimes 8269*/
/*****************************************************************************
    : TAF_CUSTOM_SIM_LOCK_MAX_TIMES_STRU
  : en_NV_Item_CustomizeSimLockMaxTimes(8269)#
            SIM LOCK,10
1.       : 2013522
         : m00217266
     : 
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulStatus;            /*01 */
    VOS_UINT32                          ulLockMaxTimes;
}TAF_CUSTOM_SIM_LOCK_MAX_TIMES_STRU;

/*en_NV_Item_CCA_TelePara 8230*/
/*****************************************************************************
    : TAF_CCA_TELE_PARA_STRU
  : en_NV_Item_CCA_TelePara(8230)#
1.       : 2013522
         : m00217266
     : 
*****************************************************************************/
/*V1R1NV15*/
typedef struct
{
    VOS_UINT8               aucRsv[15];              /*NV4*/
    VOS_UINT8               ucS0TimerLen;
} TAF_CCA_TELE_PARA_STRU;

/*en_NV_Item_PS_TelePara 8231*/
/*****************************************************************************
    : TAF_APS_NVIM_PS_ANS_MODE_STRU
  : en_NV_Item_PS_TelePara(8231)#
1.       : 2013522
         : m00217266
     : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8         AnsMode;
    VOS_UINT8         AnsType;
    VOS_UINT16        ClientId;
}TAF_APS_NVIM_PS_ANS_MODE_STRU;

/*en_NV_Item_User_Set_Freqbands 8265*/
/*bandMSRACIEZ*/
/*
  80CM_BAND_PREF_GSM_DCS_1800              GSM DCS systems
  100CM_BAND_PREF_GSM_EGSM_900             Extended GSM 900
  200CM_BAND_PREF_GSM_PGSM_900             Primary GSM 900
  100000CM_BAND_PREF_GSM_RGSM_900          GSM Railway GSM 900
  200000CM_BAND_PREF_GSM_PCS_1900          GSM PCS
  400000CM_BAND_PREF_WCDMA_I_IMT_2000      WCDMA IMT 2000
  3FFFFFFFCM_BAND_PREF_ANY                 
  40000000CM_BAND_PREF_NO_CHANGE           
*/
/*****************************************************************************
    : TAF_MMA_NVIM_USER_SET_PREF_BAND64
  : en_NV_Item_User_Set_Freqbands(8265)#
1.       : 2013522
         : m00217266
     : 
*****************************************************************************/
typedef struct
{
    VOS_UINT32 ulBandLow; /*32*/
    VOS_UINT32 ulBandHigh;/*32*/
} TAF_MMA_NVIM_USER_SET_PREF_BAND64;

/*****************************************************************************
    : TAF_AT_NVIM_REPORT_REG_ACT_FLG_STRU
  : en_NV_Item_REPORT_REG_ACT_FLG(8340)
1.       : 2013522
         : m00217266
     : 
2.       : 201532
         : w00316404
     : reserve
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usReportRegActFlg;
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}TAF_AT_NVIM_REPORT_REG_ACT_FLG_STRU;

/*****************************************************************************
    : NAS_MMA_ME_PERSONAL_ACT_FLAG_STRU
  : en_NV_Item_Me_Personalisation_Active_Flag(8255)
1.       : 2013522
         : m00217266
     : 
2.       : 201532
         : w00316404
     : reserve
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usMePersonalActFlag;
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}NAS_MMA_ME_PERSONAL_ACT_FLAG_STRU;

/*****************************************************************************
    : TAF_CBA_CBS_SERVICE_PARM_STRU
  : en_NV_Item_CBS_Service_Para(8240)
1.       : 2013522
         : m00217266
     : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCbStatus;         /* CBS*/

    VOS_UINT8                           ucDupDetectCfg;     /*  */

    VOS_UINT8                           ucRptAppFullPageFlg; /* VOS_TRUE: 88; VOS_FALSE:  */

    VOS_UINT8                           ucRsv;              /* NV4 */
}TAF_CBA_NVIM_CBS_SERVICE_PARM_STRU;

/*****************************************************************************
    : TAF_AT_NVIM_COMMDEGBUG_CFG_STRU
  : en_NV_Item_COMMDEGBUG_CFG(27)
1.       : 2013522
         : m00217266
     : 
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulCommDebugFlag;
}TAF_AT_NVIM_COMMDEGBUG_CFG_STRU;

/*****************************************************************************
    : TAF_AT_NVIM_DEFAULT_LINK_OF_UART_STRU
  : en_NV_Item_DEFAULT_LINK_OF_UART(53)
1.       : 2013522
         : m00217266
     : 
2.       : 201532
         : w00316404
     : reserve
*****************************************************************************/
typedef struct
{
    AT_UART_LINK_TYPE_ENUM_UINT16       enUartLinkType;
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}TAF_AT_NVIM_DEFAULT_LINK_OF_UART_STRU;

/*****************************************************************************
    : NAS_NVIM_AUTOATTACH_STRU
  : en_NV_Item_FMRID(8203)
1.       : 2013522
         : m00217266
     : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8 aucMfrId[TAF_MAX_MFR_ID_STR_LEN];
}TAF_PH_FMR_ID_STRU;

/*****************************************************************************
    : NAS_MMA_OPERATOR_NAME_STRU
  : en_NV_Item_MMA_OperatorName(8206)
1.       : 2013522
         : m00217266
     : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8 aucOperatorName[NAS_MMA_NVIM_OPERATOR_NAME_LEN];
}NAS_MMA_OPERATOR_NAME_STRU;

/*****************************************************************************
    : TAF_AT_NVIM_FACTORY_INFO_STRU
  : en_NV_Item_AT_FACTORY_INFO(115)
1.       : 2013522
         : m00217266
     : 
2.       : 201532
         : w00316404
     : reserve
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucFactInfo1[AT_FACINFO_INFO1_STR_LENGTH];
    VOS_UINT8                           aucFactInfo2[AT_FACINFO_INFO2_STR_LENGTH];
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}TAF_AT_NVIM_FACTORY_INFO_STRU;

/*****************************************************************************
    : TAF_AT_NVIM_MANUFACTURE_DATE_STRU
  : en_NV_Item_AT_MANUFACTURE_DATE(116)
1.       : 2013522
         : m00217266
     : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucMDate[AT_MDATE_STRING_LENGTH];
}TAF_AT_NVIM_MANUFACTURE_DATE_STRU;

/*****************************************************************************
     : APP_VC_NVIM_PC_VOICE_SUPPORT_FLAG_STRU
   : en_NV_Item_PCVOICE_Support_Flg

 1.       : 2013517
          : l00167671
      : 
 2.       : 201532
          : w00316404
      : reserve
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usPcVoiceSupportFlag; /*Range:[0,1]*/
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}APP_VC_NVIM_PC_VOICE_SUPPORT_FLAG_STRU;



/*****************************************************************************
     : MN_MSG_ME_STORAGE_PARM_STRU
   : en_NV_Item_Sms_Me_Storage_Info NV
  1.       : 2013522
           : l00167671
       : 
*****************************************************************************/
typedef struct
{
    MN_MSG_ME_STORAGE_STATUS_ENUM_UINT8 enMeStorageStatus;                      /* ME*/
    VOS_UINT8                           aucReserve[1];                          /* NV4 */
    VOS_UINT16                          usMeStorageNum;                         /* ME */
}MN_MSG_ME_STORAGE_PARM_STRU;
/*****************************************************************************
     : TAF_APS_DSFLOW_NV_STRU
   : NV
1.       : 20111214
         :  00132663
     : 
*****************************************************************************/
typedef struct
{
    VOS_UINT32      ulDSLastLinkTime;                       /*DS*/
    VOS_UINT32      ulDSTotalSendFluxLow;                   /*DS*/
    VOS_UINT32      ulDSTotalSendFluxHigh;                  /*DS*/
    VOS_UINT32      ulDSTotalLinkTime;                      /*DS*/
    VOS_UINT32      ulDSTotalReceiveFluxLow;                /*DS*/
    VOS_UINT32      ulDSTotalReceiveFluxHigh;               /*DS*/

} TAF_APS_DSFLOW_NV_STRU;

/*****************************************************************************
     : NAS_PREVENT_TEST_IMSI_REG_STRU
   : en_NV_Item_PREVENT_TEST_IMSI_REG
  1.       : 2012222
           : w00199382
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucActFlg;/* MN_MSG_NVIM_ITEM_ACTIVE */
    VOS_UINT8                           aucReserved[3];
}MN_MSG_DISCARD_DELIVER_MSG_STRU;
/*****************************************************************************
     : NAS_PREVENT_TEST_IMSI_REG_STRU
   : en_NV_Item_PREVENT_TEST_IMSI_REG
  1.       : 2012222
           : w00199382
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucActFlg;/* MN_MSG_NVIM_ITEM_ACTIVE */
    VOS_UINT8                           aucReserved[3];
}MN_MSG_REPLACE_DELIVER_MSG_STRU;

/* Added by z40661 for AMR-WB , 2012-02-09 , end */
/*****************************************************************************
     : TAF_APS_DSFLOW_STATS_CTRL_NV_STRU
   : NV
1.       : 20111221
         :  00132663
     : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8       ucDsFlowStatsRptCtrl;                   /*  */
    VOS_UINT8       ucDsFlowStatsSave2NvCtrl;               /* NV */
    VOS_UINT8       ucDsFlowSavePeriod;                     /* NV */
    VOS_UINT8       aucReserve[1];                          /* */
} TAF_APS_DSFLOW_STATS_CTRL_NV_STRU;

/*****************************************************************************
     : TAF_PH_RAT_STRU
   : AT^syscfgexacqorder
 1.     : 2011069
        : l00130025
    : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucRatOrderNum;                          /* syscfgexacqoder */
    VOS_UINT8                           aenRatOrder[TAF_PH_NVIM_MAX_GUL_RAT_NUM];    /* at^syscfgexacqoder */
}TAF_PH_NVIM_RAT_ORDER_STRU;

/*****************************************************************************
     : NAS_PREVENT_TEST_IMSI_REG_STRU
   : NAS_PREVENT_TEST_IMSI_REG_STRU
  1.       : 2013522
           : l00167671
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucActFlg;
    VOS_UINT8                           aucReserved[3];
}MN_MSG_NVIM_MO_SMS_CTRL_STRU;


/*****************************************************************************
     : TAF_APS_NVIM_PDP_ACT_LIMIT_STRU
   : AT&T PDPNV
 1.       : 2012614
          : m00217266
      : 
 2.       : 201532
          : w00316404
      : reserve
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNvimActiveFlg;                        /* en_NV_Item_PDP_Actving_Limit NVVOS_TRUE:VOS_FALSE: */
    VOS_UINT8                           ucReserved1;                            /*  */
    VOS_UINT8                           ucReserved2;                            /*  */
    VOS_UINT8                           ucReserved3;                            /*  */
}TAF_APS_NVIM_PDP_ACT_LIMIT_STRU;
/*****************************************************************************
     : MN_CALL_NVIM_CUSTOM_ECC_NUM_STRU
   : NV
 1.       : 20120611
          : W00166186
      : AT&T&DCM

****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCategory;                             /*  */
    VOS_UINT8                           ucValidSimPresent;                      /* 10 */
    VOS_UINT8                           ucAbnormalServiceFlg;                   /* 0:1: */
    VOS_UINT8                           ucEccNumLen;
    VOS_UINT8                           aucEccNum[MN_CALL_NVIM_MAX_BCD_NUM_LEN];
    VOS_UINT32                          ulMcc;                                  /* MCC,3 bytes */
} MN_CALL_NVIM_CUSTOM_ECC_NUM_STRU;


/*****************************************************************************
     : MN_CALL_NVIM_CUSTOM_ECC_NUM_LIST_STRU
   : en_NV_Item_CUSTOM_ECC_NUM_LIST
 1.       : 20120611
          : W00166186
      : AT&T&DCM

****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEccNumCount;
    VOS_UINT8                           aucReserve[3];
    MN_CALL_NVIM_CUSTOM_ECC_NUM_STRU    astCustomEccNumList[MN_CALL_NVIM_MAX_CUSTOM_ECC_NUM];
} MN_CALL_NVIM_CUSTOM_ECC_NUM_LIST_STRU;

/*****************************************************************************
     : TAF_NVIM_BUFFER_SERVICE_REQ_PROTECT_TIMER_CFG_STRU
   : NV en_NV_Item_BUFFER_SERVICE_REQ_PROTECT_TIMER_CFG 

  1.       : 2015930
           : c00318887
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucBufferCcProtectTimerLen;              /* 0: 0: CC  */
    VOS_UINT8                           ucBufferSmsProtectTimerLen;             /* 0: 0: SMS  */
    VOS_UINT8                           ucBufferSsProtectTimerLen;              /* 0: 0: SS  */
    VOS_UINT8                           ucReserve1;
}TAF_NVIM_BUFFER_SERVICE_REQ_PROTECT_TIMER_CFG_STRU;



/*****************************************************************************
     : MN_CALL_NVIM_SIM_CALL_CONTROL_FLG_STRU
   : en_NV_Item_NVIM_SIM_CALL_CONTROL_SUPPORT_FLG NV
  1.       : 20120303
           : S62952
       : 
  2.       : 201532
           : w00316404
       : reserve
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucSimCallCtrlSupportFlg;                /* SIMCall Control*/
    VOS_UINT8                           ucReserved1;                            /* */
    VOS_UINT8                           ucReserved2;                            /* */
    VOS_UINT8                           ucReserved3;                            /* */
}MN_CALL_NVIM_SIM_CALL_CONTROL_FLG_STRU;
/*****************************************************************************
     : MN_CALL_NVIM_CALL_DEFLECTION_SUPPORT_FLG_STRU
   : en_NV_Item_NVIM_CALL_DEFLECTION_SUPPORT_FLG NV
  1.       : 20120303
           : S62952
       : 
  2.       : 201532
           : w00316404
       : reserve
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCallDeflectionSupportFlg;             /* */
    VOS_UINT8                           ucReserved1;                            /* */
    VOS_UINT8                           ucReserved2;                            /* */
    VOS_UINT8                           ucReserved3;                            /* */
}MN_CALL_NVIM_CALL_DEFLECTION_SUPPORT_FLG_STRU;
/*****************************************************************************
     : MN_CALL_NVIM_ALS_SUPPORT_FLG_STRU
   : en_NV_Item_NVIM_ALS_SUPPORT_FLG NV
  1.       : 20120303
           : S62952
       : 
  2.       : 201532
           : w00316404
       : reserve
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucAlsSupportFlg;                        /* */
    VOS_UINT8                           ucReserved1;                            /* */
    VOS_UINT8                           ucReserved2;                            /* */
    VOS_UINT8                           ucReserved3;                            /* */
}MN_CALL_NVIM_ALS_SUPPORT_FLG_STRU;
/*****************************************************************************
     : MN_MSG_GET_CSMP_PARA_FROM_USIM_SUPPORT_FLG_STRU
   : en_NV_Item_NVIM_GET_CSMP_PARA_FROM_USIM_SUPPORT_FLG NV
  1.       : 20120303
           : S62952
       : 
  2.       : 201499
           : z00161729
       : DTS2014091200106:4G0x6f42indicationbit1
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucGetCsmpParaFromUsimSupportFlg;        /*(U)SIMCSMP*/

    VOS_UINT8                           ucGetScAddrIgnoreScIndication; /* 0x6f42sc indication
                                                                       VOS_FALSE:sc indication
                                                                       VOS_TRUE: sc indication */
}MN_MSG_GET_CSMP_PARA_FROM_USIM_SUPPORT_FLG_STRU;
/*****************************************************************************
     : MN_MSG_SMS_PP_DOWNLOAD_SUPPORT_FLG_STRU
   : en_NV_Item_NVIM_SMS_PP_DOWNLOAD_SUPPORT_FLG NV
  1.       : 20120303
           : S62952
       : 
  2.       : 201532
           : w00316404
       : reserve
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucSmsPpDownlodSupportFlg;               /*PP-DOWNLOAD*/
    VOS_UINT8                           ucReserved1;                            /* */
    VOS_UINT8                           ucReserved2;                            /* */
    VOS_UINT8                           ucReserved3;                            /* */
}MN_MSG_SMS_PP_DOWNLOAD_SUPPORT_FLG_STRU;
/*****************************************************************************
     : MN_MSG_SMS_NVIM_SMSREXIST_SUPPORT_FLG_STRU
   : en_NV_Item_NVIM_SMS_NVIM_SMSREXIST_SUPPORT_FLG NV
  1.       : 20120303
           : S62952
       : 
  2.       : 201532
           : w00316404
       : reserve
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucSmsNvSmsRexitSupportFlg;              /*PS ONLYCS() */
    VOS_UINT8                           ucReserved1;                            /* */
    VOS_UINT8                           ucReserved2;                            /* */
    VOS_UINT8                           ucReserved3;                            /* */
}MN_MSG_SMS_NVIM_SMSREXIST_SUPPORT_FLG_STRU;

/*****************************************************************************
     : MN_MSG_SMS_STATUS_IN_EFSMS_SUPPORT_FLG_STRU
   : en_NV_Item_NVIM_SMS_STATUS_REPORT_IN_EFSMS_SUPPORT_FLG NV
  1.       : 20120303
           : S62952
       : 
  2.       : 201532
           : w00316404
       : reserve
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucSmsStatusInEfsmsSupportFlg;           /* NVIM*/
    VOS_UINT8                           ucReserved1;                            /* */
    VOS_UINT8                           ucReserved2;                            /* */
    VOS_UINT8                           ucReserved3;                            /* */
}MN_MSG_SMS_STATUS_IN_EFSMS_SUPPORT_FLG_STRU;


/* Added by z40661 for AMR-WB , 2012-02-09 , begin */

/*****************************************************************************
     : MN_CALL_NIMV_ITEM_CODEC_TYPE_STRU
   : NVIMGSMcodec
 1.       : 2012209
          : zhoujun 40661
      : 
*****************************************************************************/

typedef struct
{
    VOS_UINT8                           ucCodecTypeNum;
    VOS_UINT8                           aucCodecType[MN_CALL_NVIM_BC_MAX_SPH_VER_NUM];
    VOS_UINT8                           ucReserve;
}MN_CALL_NIMV_ITEM_CODEC_TYPE_STRU;

/* Added by z40661 for AMR-WB , 2012-02-09 , end */

	/* Added by f62575 for C50_IPC Project, 2012/02/23, begin */
/*****************************************************************************
     : TAF_FDN_CONFIG_STRU
   : FDN
             enMeStatus         MEFDN
1.       : 20120223
         : f62575
     : 
*****************************************************************************/
typedef struct
{
    VOS_UINT32       ulMeStatus;
}TAF_FDN_NVIM_CONFIG_STRU;
/* Added by f62575 for C50_IPC Project, 2012/02/23, end   */

/*****************************************************************************
    : TAF_CALL_NVIM_CALL_NOT_SUPPORTED_CAUSE_STRU
  : CALLRELEASE COMPLETE
            ucVoiceCallNotSupportedCause   VOICE CALLRELEASE COMPLETE
            ucVideoCallNotSupportedCause   VIDEO CALLRELEASE COMPLETE
1.       : 20131209
           : f62575
       : DTS2013120411878VOICE/VIDEO CALLRELEASE COMPLETE

*****************************************************S************************/
typedef struct
{
    VOS_UINT8                           ucVoiceCallNotSupportedCause;
    VOS_UINT8                           ucVideoCallNotSupportedCause;
    VOS_UINT8                           aucReserved1[2];
}TAF_CALL_NVIM_CALL_NOT_SUPPORTED_CAUSE_STRU;

/*****************************************************************************
     : TAF_MMA_NVIM_REPORT_PLMN_SUPPORT_FLG_STRU
   : en_NV_Item_REPORT_PLMN_SUPPORT_FLAG NV
             PLMN

   :
 1.       : 20120611
          : W00166186
      : 
*****************************************************************************/

typedef struct
{
    VOS_UINT8                           ucNvimActiveFlg;                        /* en_NV_Item_Network_Selection_Menu_Ctrl_Para NVVOS_TRUE:VOS_FALSE: */
    VOS_UINT8                           ucReserved;                             /*  */
}TAF_MMA_NVIM_REPORT_PLMN_SUPPORT_FLG_STRU;

	/*****************************************************************************
     : TAF_MMA_NOT_DISPLAY_LOCAL_NETWORKNAME_NVIM_STRU
   : en_NV_Item_NotDisplayLocalNetworkName NV
 1.       : 2012111
          : w00167002
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNotDisplayLocalNetworkNameFlg;
    VOS_UINT8                           ucReserved;
}TAF_MMA_NOT_DISPLAY_LOCAL_NETWORKNAME_NVIM_STRU;

/*****************************************************************************
     : MN_MSG_MT_CUSTOMIZE_INFO_STRU
   : NVen_NV_Item_SMS_MT_CUSTOMIZE_INFO
             ucActFlag      
             enMtCustomize  
  1.       : 20121110
           : f62575
       : DCM&DEVICE
  2.       : 20171012
           : h00360002
       : downloadstk
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucActFlag;
    VOS_UINT8                           enMtCustomize;
    VOS_UINT8                           aucMtCustomize[2];                      /* MT. [0]: download mtstk */
}MN_MSG_MT_CUSTOMIZE_INFO_STRU;


/*****************************************************************************
     : TAF_SIM_FORMAT_PLMN_ID
   : Sim PLMN ID

 1.       : 201646
          : c00318887
      : DAM & SmartCard

*****************************************************************************/
typedef struct {
    VOS_UINT8                           aucSimPlmn[TAF_SIM_FORMAT_PLMN_LEN];
    VOS_UINT8                           aucReserve[1];
}TAF_SIM_FORMAT_PLMN_ID;

/*****************************************************************************
     : TAF_MN_OTA_MSG_PLMN_LIST_STRU
   : DAM & SmartCardNV

  1.       : 201646
           : c00318887
       : DAM & SmartCard
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulPlmnNum;
    TAF_SIM_FORMAT_PLMN_ID              astSimPlmnId[TAF_NVIM_OTA_SECURITY_MSG_IMSI_PLMN_MAX_NUM];
} TAF_MN_OTA_SECURITY_SMS_IMSI_PLMN_LIST;

/*****************************************************************************
     : TAF_MN_NVIM_OTA_SECURITY_SMS_CFG_STRU
   : DAM & SmartCardNVen_NV_Item_MN_OTA_MSG_SECURITY_REQUIREMENT_CFG
             ucOtaMsgSequrityRequirementActFlg      OTA
  1.       : 20160329
           : wx270776
       : DAM & SmartCard

*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucOtaSmsActiveFlg;
    VOS_UINT8                                               ucReserve1;
    VOS_UINT8                                               ucReserve2;
    VOS_UINT8                                               ucReserve3;
    TAF_MN_OTA_SECURITY_SMS_IMSI_PLMN_LIST                  stImsiPlmnList;  /* IMSIMCC-MNC  */
}TAF_MN_NVIM_OTA_SECURITY_SMS_CFG_STRU;

/*****************************************************************************
     : TAF_NVIM_GPS_CUST_CFG_STRU
   : NVen_NV_Item_Gps_Cust_CFG
             enGpsChipType      GPS
  1.       : 201677
           : wx270776
       : NV

*****************************************************************************/
typedef struct
{
    TAF_NV_GPS_CHIP_TYPE_ENUM_UINT8     enGpsChipType;
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
    VOS_UINT8                           ucReserve3;
}TAF_NVIM_GPS_CUST_CFG_STRU;

/*****************************************************************************
     : MN_CALL_UMTS_CODEC_TYPE_STRU
   : MN_CALL_UMTS_CODEC_TYPE_STRU
  1.       : 2013522
           : l00167671
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8  ucCnt;
    VOS_UINT8  aucUmtsCodec[MN_CALL_MAX_UMTS_CODEC_TYPE_NUM];
} MN_CALL_UMTS_CODEC_TYPE_STRU;
/*****************************************************************************
     : MMA_CUSTOM_CARDLOCK_PERM_STRU
   : MMA_CUSTOM_CARDLOCK_PERM_STRU
  1.       : 2013522
           : l00167671
       : 
  2.       : 201532
           : w00316404
       : reserve
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucStatus;/*01 */
    VOS_UINT8                           ucCardLockPerm;
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}MMA_CUSTOM_CARDLOCK_PERM_STRU;

/*****************************************************************************
     : TAF_CBA_NVIM_ETWS_MSGID_RANGE_STRU
   : ETWSMSG ID
 1.       : 2012308
          : l00171473
      :  for V7R1C50 CSFB&PPAC&ETWS&ISR
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usMsgIdFrom;                            /*Cell broadcast message id value range from  */
    VOS_UINT16                          usMsgIdTo;                              /*Cell broadcast message id value range to    */
}TAF_CBA_NVIM_ETWS_MSGID_RANGE_STRU;
/*****************************************************************************
     : TAF_CBA_NVIM_ETWS_DUP_DETC_CFG_STRU
   : NVIMETWS
 1.       : 2012308
          : l00171473
      :  for V7R1C50 CSFB&PPAC&ETWS&ISR
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucEnhDupDetcFlg;    /* DoCoMoETWS, VOS_TRUE:,VOS_FALSE:.
                                                                                        1. ,CBS, PLMN
                                                                                        2. ,CBS, PLMNMCC
                                                                                        3. ETWSCBS */
    VOS_UINT8                                               ucRsv;

    VOS_UINT16                                              usNormalTimeLen;   /* :,  */

    VOS_UINT16                                              usSpecMccTimeLen;  /* :, //CBSMCCMcc */
    VOS_UINT16                                              usOtherMccTimeLen; /* :, //CBSMCCMcc */
    VOS_UINT32                                              aulSpecMcc[TAF_CBA_NVIM_MAX_ETWS_DUP_DETECT_SPEC_MCC_NUM];  /* MCC */
}TAF_CBA_NVIM_ETWS_DUP_DETC_CFG_STRU;

/*****************************************************************************
     : MN_CALL_NVIM_REPORT_ECC_NUM_SUPPORT_FLG_STRU
   : en_NV_Item_NVIM_ECC_NUM_REPORT_FLG NV
  1.       : 20120303
           : S62952
       : 
  2.       : 201532
           : w00316404
       : reserve
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucReportEccNumFlg;                      /* 1:APP, 0:APP*/
    VOS_UINT8                           ucReserved1;                            /* */
    VOS_UINT8                           ucReserved2;                            /* */
    VOS_UINT8                           ucReserved3;                            /* */
}MN_CALL_NVIM_REPORT_ECC_NUM_SUPPORT_FLG_STRU;


/*****************************************************************************
     : MMA_CUSTOM_CARDLOCK_OPERATOR_STRU
   : MMA_CUSTOM_CARDLOCK_OPERATOR_STRU
  1.       : 2013522
           : l00167671
       : 
  2.       : 201532
           : w00316404
       : reserve
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucStatus;/*01 */
    MN_CALL_STATE_ENUM_UINT8            enCardLockOperator;
    VOS_UINT8                           ucReserved1;                            /* */
    VOS_UINT8                           ucReserved2;                            /* */
}MMA_CUSTOM_CARDLOCK_OPERATOR_STRU;

/*****************************************************************************
     : MN_CALL_NV_ITEM_VIDEO_CALL_STRU
   : MN_CALL_NV_ITEM_VIDEO_CALL_STRU
  1.       : 2013522
           : l00167671
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucStatus;                               /* 1: NV0 */
    VOS_UINT8                           ucVpCfgState;                           /* NV */
}MN_CALL_NV_ITEM_VIDEO_CALL_STRU;
/* Added by f62575 for AT Project, 2011-10-27, begin */

/*****************************************************************************
     : MN_MSG_NVIM_CLASS0_TAILOR_STRU
   : MN_MSG_NVIM_CLASS0_TAILOR_STRU
  1.       : 2013522
           : l00167671
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucActFlg;                               /* NVIM */
    VOS_UINT8                           enClass0Tailor;
}MN_MSG_NVIM_CLASS0_TAILOR_STRU;
/* Added by f62575 for AT Project, 2011-10-27, end */
/* : 2GSpare_bit3 */
typedef struct
{
    VOS_UINT8                           ucStatus;       /* 1: NV0 */
    VOS_UINT8                           ucDisable2GBit3;
    VOS_UINT8                           ucReserved1;                            /* */
    VOS_UINT8                           ucReserved2;                            /* */
}APS_2G_DISABLE_BIT3_CUSTOMIZE_STRU;

/*****************************************************************************
     : MN_CALL_NV_ITEM_MULTISIM_CALLCON_STRU
   : MN_CALL_NV_ITEM_MULTISIM_CALLCON_STRU
  1.       : 2013522
           : l00167671
       : 
  2.       : 201532
           : w00316404
       : reserve
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usMultiSimCallConf;                             /*o1*/
    VOS_UINT8                           ucReserved1;                            /* */
    VOS_UINT8                           ucReserved2;                            /* */
}MN_CALL_NV_ITEM_MULTISIM_CALLCON_STRU;


/*****************************************************************************
     : TAF_USSD_NVIM_TRANS_MODE_STRU
   : TAF_USSD_NVIM_TRANS_MODE_STRU
  1.       : 2013522
           : l00167671
       : 
  2.       : 201532
           : w00316404
       : reserve
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucStatus;        /* 1: NV0 */
    VOS_UINT8                           ucUssdTransMode;
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}TAF_USSD_NVIM_TRANS_MODE_STRU;

/*****************************************************************************
     : TAF_CALL_REDIAL_CM_SRV_REJ_CFG_STRU
   : 
 1.        : 2015829
           : n00355355
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCallRedialCmSrvRejCauseNum;                                   /*  */
    VOS_UINT8                           aucReserved[3];
    VOS_UINT8                           aucCallRedialCmSrvRejCause[TAF_NVIM_CALL_REDIAL_CAUSE_MAX_NUM]; /*  */
}TAF_CALL_REDIAL_CM_SRV_REJ_CFG_STRU;

/*****************************************************************************
     : TAF_CALL_REDIAL_DISC_CFG_STRU
   : DISCONNECT
 1.        : 20160308
           : l00356716
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCallRedialForDiscSupportFlg;                            /* disconnect VOS_TRUE:VOS_FALSE:*/
    VOS_UINT8                           ucCallRedialDiscCauseNum;                                   /*  */
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           aucCallRedialDiscCause[TAF_NVIM_CALL_RETRY_DISC_CAUSE_MAX_NUM]; /*  */
}TAF_CALL_REDIAL_DISC_CFG_STRU;

/*****************************************************************************
     : TAF_CALL_TRIG_RESEL_DISCONNECT_CAUSE_CFG_STRU
   : DISCONNECTAS
 1.        : 2016421
           : k00364749
       : 
*****************************************************************************/

typedef struct
{
    VOS_UINT8                           ucCallTrigReselForDiscSupportFlg;                            /* disconnectVOS_TRUE:VOS_FALSE:*/
    VOS_UINT8                           ucCallTrigReselDiscCauseNum;                                 /*  */
    VOS_UINT8                           ucDisconnectNum;                                             /* AS, */
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           aucCallTrigReselDiscCause[TAF_NVIM_CALL_TRIG_RESEL_DISC_CAUSE_MAX_NUM]; /*  */
}TAF_CALL_TRIG_RESEL_DISC_CAUSE_CFG_STRU;

/*****************************************************************************
     : MN_CALL_REDIAL_CFG_STRU
   : 
 1.       : 20121029
          : z00161729
      : 
 2.       : 20140428
          : y00245242
      : eCall feature
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCallRedialSupportFlg;     /* VOS_TRUE:VOS_FALSE:*/
    VOS_UINT8                           aucReserved1[3];
    VOS_UINT32                          ulCallRedialPeriod;         /*  */
    VOS_UINT32                          ulCallRedialInterval;       /*  */
}MN_CALL_REDIAL_CFG_STRU;

/* Added by y00245242 for V3R3C60_eCall, 2014-4-15, begin */
/*****************************************************************************
     : TAF_CALL_NVIM_ECALL_CFG_STRU
   : eCall, eCallT9
 1.       : 20140415
          : y00245242
      : eCall feature
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEcallT9Len;                /* T91~12 */
    VOS_UINT8                           ucEcallRedialSupportFlg;   /* eCallVOS_TRUE:VOS_FALSE:*/
    VOS_UINT8                           aucReserved1[2];
    VOS_UINT16                          usEcallRedialPeriod;         /* eCalleCall */
    VOS_UINT16                          usEcallRedialInterval;       /* eCalleCall */
}TAF_CALL_NVIM_ECALL_CFG_STRU;
/* Added by y00245242 for V3R3C60_eCall, 2014-4-15, end */


/*****************************************************************************
     : APP_VC_NV_CLVL_VOLUME_STRU
   : en_NV_Item_Clvl_Volume

  1.       : 20120508
           : l60609
       : en_NV_Item_Clvl_Volume
*****************************************************************************/
typedef struct
{
    VOS_INT16                           sHandSetVolValue;
    VOS_INT16                           sHandsFreeVolValue;
    VOS_INT16                           sCarFreeVolValue;
    VOS_INT16                           sEarphoneVolValue;
    VOS_INT16                           sBlueToothVolValue;
    VOS_INT16                           sPcVoiceVolValue;
    VOS_INT16                           sHeadPhoneVolValue;
    VOS_INT16                           sSuperFreeVolValue;
    VOS_INT16                           sSmartTalkVolValue;
    VOS_INT16                           sPreVolume;
    VOS_UINT16                          usCurrDevMode;
    VOS_UINT16                          usPreDevMode;
    VOS_UINT16                          usSetVoiceFlg;                          /*DEVVolflagmodem*/
    VOS_INT16                           sRsv[3];
} APP_VC_NV_CLVL_VOLUME_STRU;

/* : APN */
typedef struct
{
    VOS_UINT8   ucStatus;       /* 1: NV0 */
    VOS_UINT8   aucApn[TAF_NVIM_MAX_APN_STR_LEN];       /* APN'\0' */
    VOS_UINT8   aucRsv[3];
}APS_APN_CUSTOMIZE_STRU;

/*****************************************************************************
     : TAF_CBA_NVIM_ETWS_CFG_STRU
   : NVIMETWS
 1.       : 2012308
          : l00171473
      :  for V7R1C50 CSFB&PPAC&ETWS&ISR
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucEtwsEnableFlg;    /* ETWS, VOS_TRUE:, VOS_FALSE: */
    VOS_UINT8                                               ucRsv;
    VOS_UINT16                                              usTempEnableCbsTimeLen; /* :, CBS,CBS */

    TAF_CBA_NVIM_ETWS_DUP_DETC_CFG_STRU                     stDupDetcCfg;       /* TAF_CBA_NV_MAX_USER_SPEC_ETWS_MSGID_RANGE_NUM Duplication Detection Time  */
    TAF_CBA_NVIM_ETWS_MSGID_RANGE_STRU                      astSpecEtwsMsgIdList[TAF_CBA_NV_MAX_USER_SPEC_ETWS_MSGID_RANGE_NUM];   /* ETWSID */
}TAF_CBA_NVIM_ETWS_CFG_STRU;

/*****************************************************************************
     : MN_CALL_ALS_LINE_INFO_STRU
   : en_NV_Item_ALS_LINE_Config(8450) NVIM
 1.       : 2012308
          : l00171473
      :  for V7R1C50 CSFB&PPAC&ETWS&ISR
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           enAlsLine;
    VOS_UINT8                           aucMmaImsi[9];
}MN_CALL_ALS_LINE_INFO_STRU;

/*****************************************************************************
    : TAF_AT_NVIM_AT_CLIENT_CONFIG_STRU
  : en_NV_Item_AT_CLIENT_CONFIG 9202
1.       : 2013522
         : m00217266
     : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                          aucAtClientConfig[TAF_AT_NVIM_CLIENT_CONFIG_LEN];
}TAF_AT_NVIM_AT_CLIENT_CONFIG_STRU;

/*****************************************************************************
    : TAF_AT_NVIM_AT_CLIENT_CFG_STRU
  : en_NV_Item_AT_CLIENT_CONFIG 2437
1.       : 20170220
         : lwx331495
     : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                          aucAtClientConfig[TAF_AT_NVIM_CLIENT_CFG_LEN+32];     /*nv32*/
}TAF_AT_NVIM_AT_CLIENT_CFG_STRU;

/*******************************************************************************
     : TAF_TEMP_PROTECT_CONFIG_STRU
   : NV(9212)
 1.       : 20130417
          : z00214637
      : 
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucECallNotifySupport;                   /* NV */
    VOS_UINT8                           ucSpyStatusIndSupport;                  /* NV */
    VOS_UINT8                           aucReserved[2];                          /*  */
}TAF_TEMP_PROTECT_CONFIG_STRU;

/*****************************************************************************
     : NVIM_ATT_ENS_CTRL_STRU
   : en_NV_Item_ATT_Ctrl_Para(9081) NV

   :
 1.       : 20120612
          : l60609
      : 

*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNetSelMenuFlg;                        /* VOS_TRUE:VOS_FALSE: */
    VOS_UINT8                           ucRatBalancingFlg;                      /* VOS_TRUE:VOS_FALSE: */
    VOS_UINT8                           aucReserved[2];                         /*  */
}NVIM_ATT_ENS_CTRL_STRU;

/*****************************************************************************
    : TAF_NVIM_USER_SET_LTEBANDS_STRU
  : en_NV_Item_USER_SET_LTEBANDS 9017
1.       : 2013522
         : m00217266
     : 
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          aulUserSetLtebands[2];
}TAF_NVIM_USER_SET_LTEBANDS_STRU;

/*****************************************************************************
    : TAF_NVIM_RABM_TOTAL_RX_BYTES_STRU
  : en_NV_Item_RABM_TOTAL_RX_BYTES 8491()
1.       : 2013522
         : m00217266
     : 
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulDSTotalSendFluxLow;
    VOS_UINT32                          ulDSTotalSendFluxHigh;
    VOS_UINT32                          ulDSTotalReceiveFluxLow;
    VOS_UINT32                          ulDSTotalReceiveFluxHig;
}TAF_NVIM_RABM_TOTAL_RX_BYTES_STRU;

/*****************************************************************************
    : TAF_NVIM_E5_ROAM_WHITE_LIST_SUPPORT_FLG_STRU
  : en_NV_Item_E5_RoamingWhiteList_Support_Flg 8504()
1.       : 2013522
         : m00217266
     : 
2.       : 201532
         : w00316404
     : reserve
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucRoamWhiteListFlag[2];
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}TAF_NVIM_E5_ROAM_WHITE_LIST_SUPPORT_FLG_STRU;

/*****************************************************************************
    : TAF_NVIM_NDIS_DIALUP_ADDRESS_STRU
  : en_NV_Item_NDIS_DIALUP_ADDRESS 9010()
1.       : 2013522
         : m00217266
     : 
*****************************************************************************/
typedef struct
{
    VOS_UINT32                         ulNdisDialUpAdd;
}TAF_NVIM_NDIS_DIALUP_ADDRESS_STRU;

/*nv 9130, ipv6nv*/
/*****************************************************************************
   : TAF_NV_IPV6_FALLBACK_EXT_CAUSE_STRU
 : IPv4v6(SM Cause)

  1.       : 20121210
           : Y00213812
       : C50 IPv6 
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulActiveFlag;
    VOS_UINT8                           aucSmCause[TAF_NV_IPV6_FALLBACK_EXT_CAUSE_MAX_NUM];

} TAF_NV_IPV6_FALLBACK_EXT_CAUSE_STRU;

/*****************************************************************************
    : TAF_NDIS_NV_IPV6_ROUTER_MTU_STRU
  : en_NV_Item_IPV6_ROUTER_MTU 8513(nv,)
1.       : 2013522
         : m00217266
     : 
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulIpv6RouterMtu;
}TAF_NDIS_NV_IPV6_ROUTER_MTU_STRU;

/*****************************************************************************
    : TAF_AT_NV_DISLOG_PWD_STRU
  : en_NV_Item_AT_DISLOG_PWD 32()
1.       : 2013522
         : m00217266
     : 
*****************************************************************************/
typedef struct
{
    VOS_INT32                           lValue;
    VOS_INT8                            acPassword[16];
}TAF_AT_NV_DISLOG_PWD_STRU;

/*****************************************************************************
    : TAF_AT_NV_E5_RIGHT_FLAG_STRU
  : en_NV_Item_AT_E5_RIGHT_FLAG 34()
1.       : 2013522
         : m00217266
     : 
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulE5RightFlag;
}TAF_AT_NV_E5_RIGHT_FLAG_STRU;

/*****************************************************************************
    : TAF_AT_NV_DISSD_FLAG_STRU
  : en_NV_Item_AT_DISSD_FLAG 42()
1.       : 2013522
         : m00217266
     : 
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulDissdFlag;
}TAF_AT_NV_DISSD_FLAG_STRU;

/*****************************************************************************
    : TAF_AT_NV_OM_PORT_NUM_STRU
  : en_NV_Item_OM_Port_Num 2049()
1.       : 2013522
         : m00217266
     : 
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulOmPortNum;
}TAF_AT_NV_OM_PORT_NUM_STRU;

/*****************************************************************************
    : TAF_AT_NV_RA_CAPABILITY_STRU
  : en_NV_Item_RaCapability 8198()
1.       : 2013522
         : m00217266
     : 
2.       : 201532
         : w00316404
     : reserve
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucLength;
    VOS_UINT8                           aucData[53];
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}TAF_AT_NV_RA_CAPABILITY_STRU;

/*****************************************************************************
    : TAF_AT_NV_UMTS_AUTH_STRU
  : en_NV_Item_UMTS_Auth 8199()
1.       : 2013522
         : m00217266
     : 
2.       : 201532
         : w00316404
     : reserve
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucUmtsAuth[2];
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}TAF_AT_NV_UMTS_AUTH_STRU;

/*****************************************************************************
    : TAF_AT_NV_GMM_INFO_STRU
  : en_NV_Item_GmmInfo 8200()
1.       : 2013522
         : m00217266
     : 
2.       : 201532
         : w00316404
     : reserve
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucGmmInfo[2];
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}TAF_AT_NV_GMM_INFO_STRU;

/*****************************************************************************
    : TAF_AT_NV_MM_INFO_STRU
  : en_NV_Item_MMInfo 8201()
1.       : 2013522
         : m00217266
     : 
2.       : 201532
         : w00316404
     : reserve
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucMmInfo[2];
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}TAF_AT_NV_MM_INFO_STRU;

/*****************************************************************************
    : TAF_AT_NV_SMS_TEXT_STRU
  : en_NV_Item_SMS_TEXT_Para 8236()
1.       : 2013522
         : m00217266
     : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucSmsText[16];
}TAF_AT_NV_SMS_TEXT_STRU;

/*****************************************************************************
    : TAF_AT_NV_CUSTOM_GPRS_RECENT_ACT_TIMER_STRU
  : en_NV_Item_CustomizeGprsRecentActivityTimer 8270()
1.       : 2013522
         : m00217266
     : 
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulStatus;
    VOS_UINT32                          ulGprsRecentActTime;
}TAF_AT_NV_CUSTOM_GPRS_RECENT_ACT_TIMER_STRU;

/*****************************************************************************
    : TAF_AT_NV_PS_DELAY_FLAG_STRU
  : en_NV_Item_Ps_Delay_Flag 8272()
1.       : 2013522
         : m00217266
     : 
2.       : 201532
         : w00316404
     : reserve
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usPsDelayFlag;
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}TAF_AT_NV_PS_DELAY_FLAG_STRU;

/*****************************************************************************
    : TAF_AT_NV_EHPLMN_SUPPORT_FLAG_STRU
  : en_NV_Item_EHPlmn_Support_Flag 8300()
1.       : 2013522
         : m00217266
     : 
2.       : 201532
         : w00316404
     : reserve
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucEhplmnSupportFlag[2];
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}TAF_AT_NV_EHPLMN_SUPPORT_FLAG_STRU;

/*****************************************************************************
    : TAF_AT_NV_BG_FS_FBS_RATIO_STRU
  : en_NV_Item_BG_FS_FBS_Ratio 8315()
1.       : 2013522
         : m00217266
     : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                          aucBgFsFbsRatio[4];
}TAF_AT_NV_BG_FS_FBS_RATIO_STRU;

/*****************************************************************************
    : TAF_AT_NV_EPLMN_USE_RAT_FLAG_STRU
  : en_NV_Item_Eplmn_Use_Rat_Flag 8342()
1.       : 2013522
         : m00217266
     : 
2.       : 201532
         : w00316404
     : reserve
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usEplmnUseRatFlag;
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}TAF_AT_NV_EPLMN_USE_RAT_FLAG_STRU;
/*****************************************************************************
     : TAF_CBA_CBMI_RANGE_STRU
   : 
 1.       : 20120317
          : z40661
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucLabel[TAF_NVIM_CBA_MAX_LABEL_NUM]; /* id */
    VOS_UINT16                                              usMsgIdFrom;                    /* ID  */
    VOS_UINT16                                              usMsgIdTo;                      /* ID */
    VOS_UINT32                                              ulRcvMode;                      /* CBMI RANGE ,  ACCEPT */
}TAF_CBA_NVIM_CBMI_RANGE_STRU;
/*****************************************************************************
     : TAF_CBA_NVIM_CBMI_RANGE_LIST_STRU
   : ID
 1.       : 20120328
          : w00176964
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulCbmirNum;                             /* ID */
    TAF_CBA_NVIM_CBMI_RANGE_STRU        astCbmiRangeInfo[TAF_CBA_NVIM_MAX_CBMID_RANGE_NUM]; /*  */
}TAF_CBA_NVIM_CBMI_RANGE_LIST_STRU;


/*****************************************************************************
     : NAS_PREVENT_TEST_IMSI_REG_STRU
   : NAS_PREVENT_TEST_IMSI_REG_STRU
  1.       : 2013522
           : l00167671
       : 
  2.       : 201532
           : w00316404
       : reserve
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usPlatform;
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}NAS_NVIM_PLATFORM_STRU;

/*****************************************************************************
     : TAF_AT_NVIM_MUX_SUPPORT_FLG_STRU
   : TAF_AT_NVIM_MUX_SUPPORT_FLG_STRU
  1.       : 2013522
           : l00167671
       : 
  2.       : 201532
           : w00316404
       : reserve
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucMuxSupportFlg;
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
}TAF_AT_NVIM_MUX_SUPPORT_FLG_STRU;

/*USSD*/
typedef struct
{
    VOS_UINT8                           ucStatus;            /*01 */
    VOS_UINT8                           ucAlphaTransMode;    /* */
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
}SSA_NV_ITEM_ALPHA_to_ASCII_STRU;

/*****************************************************************************
    : TAF_CBA_CBS_SERVICE_PARM_STRU
  : NVCBS
1.       : 2012323
         : t00212959
     :  for V7R1C50 CSFB&PPAC&ETWS&ISR
2.       : 20121204
         : l00171473
     : for DTS2012120600056, NV
3.       : 20121210
         : l00171473
     : for DTS2012120609682,CBS88
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCbStatus;         /* CBS*/

    VOS_UINT8                           ucDupDetectCfg;     /*  */


    VOS_UINT8                           ucRptAppFullPageFlg; /* VOS_TRUE: 88; VOS_FALSE:  */

    VOS_UINT8                           ucRsv;              /* NV4 */
}TAF_CBA_CBS_SERVICE_PARM_STRU;

/*******************************************************************************
     : MTA_BODY_SAR_W_PARA_STRU
   : Body SAR W 
 1.       : 20130227
          : l00198894
      : 
*******************************************************************************/
typedef struct
{
    MTA_WCDMA_BAND_ENUM_UINT16          enBand;                     /* WCDMA */
    VOS_INT16                           sPower;                     /*  */
}MTA_BODY_SAR_W_PARA_STRU;

/*******************************************************************************
     : MTA_BODY_SAR_G_PARA_STRU
   : Body SAR G 
 1.       : 20130227
          : l00198894
      : 
*******************************************************************************/
typedef struct
{
    VOS_INT16                           sGPRSPower;                 /* GPRS */
    VOS_INT16                           sEDGEPower;                 /* EDGE */
}MTA_BODY_SAR_G_PARA_STRU;

/*******************************************************************************
     : MTA_BODY_SAR_PARA_STRU
   : Body SAR
 1.       : 20130227
          : l00198894
      : 
*******************************************************************************/
typedef struct
{
    VOS_UINT32                          ulGBandMask;                                /* GSM BandMask */
    VOS_UINT16                          usWBandNum;                                 /* WCDMABand */
    VOS_UINT16                          ausReserved1[1];                            /*  */
    MTA_BODY_SAR_G_PARA_STRU            astGBandPara[MTA_BODY_SAR_GBAND_MAX_NUM];   /* GSM */
    MTA_BODY_SAR_W_PARA_STRU            astWBandPara[MTA_BODY_SAR_WBAND_MAX_NUM];   /* WCDMA */
}MTA_BODY_SAR_PARA_STRU;

typedef struct
{
    VOS_UINT32  ulNvStatus;
    VOS_UINT8   aucFirstPortStyle[17];   /*  */
    VOS_UINT8   aucRewindPortStyle[17];  /*  */
    VOS_UINT8   aucReserved[22];         /*  */
}AT_DYNAMIC_PID_TYPE_STRU;

/* Added by L47619 for V3R3 Share-PDP Project, 2013-6-3, begin */
/*****************************************************************************
     : TAF_NVIM_SHARE_PDP_INFO_STRU
   : Share-PDPNV
 1.       : 20130603
          : L47619
      : V3R3 Share-PDP
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEnableFlag;       /* Share PDP, 0 - ;  1 -  */
    VOS_UINT8                           ucReserved;         /*  */
    VOS_UINT16                          usAgingTimeLen;     /*  */

} TAF_NVIM_SHARE_PDP_INFO_STRU;

/*****************************************************************************
     : TAF_NVIM_DEACT_SIM_WHEN_POWEROFF_STRU
   : AT+CFUN=0(U)SIMNV
 1.       : 20130603
          : L47619
      : V3R3 Share-PDP
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEnableFlag;  /* AT+CFUN=0(U)SIM, 0 - , 1 - */
    VOS_UINT8                           aucReserved[3];
} TAF_NVIM_DEACT_SIM_WHEN_POWEROFF_STRU;
/* Added by L47619 for V3R3 Share-PDP Project, 2013-6-3, end */

/* MSCC module */

/*******************************************************************************
     : TAF_NV_SCI_CFG_STRU
   :
  1.       : 201374
           : s00190137
       : 

  2.       : 2015616
           : l00198894
       : TSTS
*******************************************************************************/
typedef struct
{
    VOS_UINT32                          bitCardNum      : 3;
    VOS_UINT32                          bitReserved0    : 5;
    VOS_UINT32                          bitCard0        : 3;
    VOS_UINT32                          bitCard1        : 3;
    VOS_UINT32                          bitCard2        : 3;
    VOS_UINT32                          bitReserved1    : 15;
} TAF_NV_SCI_CFG_STRU;

/*******************************************************************************
     : TAF_NVIM_SMS_CLOSE_PATH_CFG_STRU
   :
  1.       : 2013717
           : z00234330
       : 
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNvimValid;
    VOS_UINT8                           ucSmsClosePathFlg;
} TAF_NVIM_SMS_CLOSE_PATH_CFG_STRU;


/* Added by j00174725 for V9R1 , 2013/08/12, begin */
/*******************************************************************************
     : MTC_NV_RF_INTRUSION_CFG_STRU
   : MTCNV
  1.       : 20130813
           : /j00174725
       : 
*******************************************************************************/
typedef struct
{
    /*  :01:
    bit0B39/B3
    bit1Notch Bypass
    bit2: NarrowBand Dcs (V9 not support)
    bit3: B39/B3 2(G)
    bit4: RES 1RSE0RSE
    */
    VOS_UINT8                          ucSolutionMask;
    VOS_UINT8                          aucAdditonCfg[3];
} MTC_NV_RF_INTRUSION_CFG_STRU;
/* Added by j00174725 for V9R1 , 2013/08/12, end */

/* Added by f62575 for VSIM FEATURE, 2013-8-29, begin */
/**************************************************************
     : TAF_NVIM_VSIM_CFG_STRU
   : ME
             ucVsimCtrlFlg   NAS:
             1: VSIMMODEM
                  OTA
                  CS
             0: 
             aucReserved1 1BYTENV16BIT
  1.       : 2013829
           : f62575
       : VSIM FEATURE
  2.       : 201532
           : w00316404
       : reserve
**************************************************************/
typedef struct
{
    VOS_UINT8                           ucVsimCtrlFlg;
    VOS_UINT8                           aucReserved1;
    VOS_UINT8                           aucReserved2;
    VOS_UINT8                           aucReserved3;
} TAF_NVIM_VSIM_CFG_STRU;

/* Added by f62575 for VSIM FEATURE, 2013-8-29, end */
/*****************************************************************************
     : TAF_SSA_NVIM_RETRY_CFG_STRU
   : ss
 1.       : 2013910
          : z00161729
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucIsSsRetrySupportFlg;                  /* ssVOS_TRUE:VOS_FALSE:*/
    VOS_UINT8                           aucReserved1[3];
    VOS_UINT32                          ulSsRetryPeriod;                        /* ssss,30s */
    VOS_UINT32                          ulSsRetryInterval;                      /* ssss5s */
}TAF_SSA_NVIM_RETRY_CFG_STRU;

/*****************************************************************************
     : TAF_SSA_NVIM_RETRY_CFG_STRU
   : ss
 1.       : 2015824
          : n00355355
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucSsRetryCmSrvRejCauseNum;                                      /* ss*/
    VOS_UINT8                           aucReserved1[3];
    VOS_UINT8                           aucSsRetryCmSrvRejCause[TAF_NVIM_SS_RETRY_CAUSE_MAX_NUM];       /* ss */
}TAF_SSA_NVIM_RETRY_CM_SRV_REJ_CFG_STRU;


/*****************************************************************************
     : TAF_NVIM_SS_WAIT_USER_RSP_LEN_STRU
   : SS
 1.       : 20160718
          : f00179208
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usWaitUserRspLen;                       /*  */
    VOS_UINT8                           aucReserved1;
    VOS_UINT8                           aucReserved2;
}TAF_NVIM_SS_WAIT_USER_RSP_LEN_STRU;

/*****************************************************************************
     : TAF_NV_UART_RI_CFG_STRU
   : UART RI

  1.       : 20130918
           : A00165503
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulSmsRiOnInterval;      /* RI(ms) */
    VOS_UINT32                          ulSmsRiOffInterval;     /* RI(ms) */

    VOS_UINT32                          ulVoiceRiOnInterval;    /* RI(ms) */
    VOS_UINT32                          ulVoiceRiOffInterval;   /* RI(ms) */
    VOS_UINT8                           ucVoiceRiCycleTimes;    /* RI     */
    VOS_UINT8                           aucReserved[3];

} TAF_NV_UART_RI_STRU;

/*****************************************************************************
     : TAF_NV_UART_FRAME_STRU
   : UART 

  1.       : 20130918
           : j00174725
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucFormat;               /* UART  */
    VOS_UINT8                           ucParity;               /* UART */
    VOS_UINT8                           aucReserved[2];

} TAF_NV_UART_FRAME_STRU;

/*****************************************************************************
     : TAF_NV_UART_CFG_STRU
   : UART 

  1.       : 20130918
           : j00174725
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulBaudRate;             /* UART */
    TAF_NV_UART_FRAME_STRU              stFrame;                /* UART */
    TAF_NV_UART_RI_STRU                 stRiConfig;             /* UART Ring */

} TAF_NV_UART_CFG_STRU;

/*****************************************************************************
     : TAF_NV_DFS_RATE_BAND_STRU
   : DDR

  1.       : 20131213
           : f00179208
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulDlRate;
    VOS_UINT32                          ulUlRate;
    VOS_UINT32                          ulDdrBand;
} TAF_NV_DFS_RATE_BAND_STRU;

/*****************************************************************************
     : TAF_NV_DFS_DSFLOW_RATE_CONFIG_STRU
   : APSDDR

  1.       : 20131213
           : f00179208
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulProfileNum;
    TAF_NV_DFS_RATE_BAND_STRU           astProfile[TAF_NVIM_DFS_MAX_PROFILE_NUM];
} TAF_NV_DFS_DSFLOW_RATE_CONFIG_STRU;
/*****************************************************************************
     : TAF_NV_DIFF_RAT_DFS_DSFLOW_RATE_CONFIG_STRU
   : APSDDR

  1.       : 20140526
           : m00217266
       : 
*****************************************************************************/
typedef struct
{
    TAF_NV_DFS_DSFLOW_RATE_CONFIG_STRU          astDfsConfig[TAF_NVIM_DIFF_DFS_NUM];
} TAF_NV_MULTI_DFS_DSFLOW_RATE_CONFIG_STRU;

/*****************************************************************************
     : TAF_NV_VOICE_TEST_FLAG_STRU
   :

  1.       : 20131223
           : m00217266
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulFlagValue;
    VOS_UINT32                          ulReserved;
} TAF_NV_VOICE_TEST_FLAG_STRU;

/* Added by s00217060 for VoLTE_PhaseII  , 2013-11-04, begin */
/*******************************************************************************
     : TAF_NVIM_SMS_DOMAIN_STRU
   :
  1.       : 20131105
           : s00217060
       : 
*******************************************************************************/
typedef struct
{
    VOS_UINT8                          ucSmsDomain;
    VOS_UINT8                          aucReserved[3];
} TAF_NVIM_SMS_DOMAIN_STRU;

/* Added by s00217060 for VoLTE_PhaseII  , 2013-11-04, end */

/*****************************************************************************
     : TAF_NV_PORT_BUFF_CFG_STRU
   : 

  1.       : 20131228
           : j00174725
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEnableFlg;
    VOS_UINT8                           aucReserved[3];
} TAF_NV_PORT_BUFF_CFG_STRU;


/* Added by s00246516 for L-C, 2014-01-23, Begin */
/*****************************************************************************
     : TAF_NV_LC_CTRL_PARA_STRU
   : 
   : L+CSIM

       :
  1.       : 20140123
           : s00246516
       : L-CNV
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                     ucLCEnableFlg;
    TAF_NVIM_LC_RAT_COMBINED_ENUM_UINT8           enRatCombined;
    TAF_NVIM_LC_WORK_CFG_ENUM_UINT8               enLCWorkCfg;
    VOS_UINT8                                     aucReserved[1];
}TAF_NV_LC_CTRL_PARA_STRU;
/* Added by s00246516 for L-C, 2014-01-23, End */

/*****************************************************************************
     : TAF_NV_SWITCH_IMS_TO_CS_REDIAL_CAUSE_CONFIG_STRU
   :
 1.       : 2015813
          : l00289540
      : User_Exp_Improve 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                 ucImsRedialCauseNum;                                                  /* IMS call */
    VOS_UINT8                 ucImsaRedialCauseNum;                                                 /* IMSA call */
    VOS_UINT8                 aucReserve[2];
    VOS_UINT16                ausImsRedialCause[TAF_NVIM_IMS2CS_CALL_REDIAL_CAUSE_MAX_NUM];
    VOS_UINT16                ausImsaRedialCause[TAF_NVIM_IMSA2CS_CALL_REDIAL_CAUSE_MAX_NUM];
}TAF_NV_SWITCH_IMS_TO_CS_REDIAL_CAUSE_CONFIG_STRU;

/*****************************************************************************
     : TAF_NV_SWITCH_IMS_TO_CS_REDIAL_CONFIG_STRU
   :
 1.       : 2015813
          : l00289540
      : User_Exp_Improve 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucCallRedial;                           /* callflag */
    VOS_UINT8                                               ucSmsRedial;                            /* SMS flag */
    VOS_UINT8                                               ucSsRedial;                             /* SS  flag */
    /* NV */
    TAF_IMS2CS_REDIAL_AFTER_ALERTING_DOMAIN_ENUM_UINT8      aenImsRedialAfterAlertingDomain[1];     /* IMSalerting */
    TAF_NV_SWITCH_IMS_TO_CS_REDIAL_CAUSE_CONFIG_STRU        stCallRedialCauseCfg;
}TAF_NV_SWITCH_IMS_TO_CS_REDIAL_CONFIG_STRU;

/*****************************************************************************
     : TAF_NV_SWITCH_WIFI_TO_CS_REDIAL_CONFIG_STRU
   : en_NV_Item_REDIAL_WIFI_TO_CS_DOMAIN_CFG(2482)
 1.       : 20171010
          : gwx483917
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucLteWifiCauseDifferFlag; /* VOLTEVOWIFI */
    VOS_UINT8                                               aucReserve[3];
    TAF_NV_SWITCH_IMS_TO_CS_REDIAL_CAUSE_CONFIG_STRU        stCallRedialCauseCfg;
}TAF_NV_SWITCH_WIFI_TO_CS_REDIAL_CONFIG_STRU;

/*****************************************************************************
     : TAF_NV_SWITCH_CS_TO_IMS_REDIAL_CONFIG_STRU
   :
 1.       : 20131224
          : y00245242
      : IMSCS
 2.       : 2015813
          : l00289540
      : User_Exp_Improve 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                              ucCallRedial;
    VOS_UINT8                                              ucSmsRedial;
    VOS_UINT8                                              ucSsRedial;
    VOS_UINT8                                              aucReserve[1];
}TAF_NV_SWITCH_CS_TO_IMS_REDIAL_CONFIG_STRU;

/*****************************************************************************
     : TAF_NV_SWITCH_DOMAIN_REDIAL_CONFIG_STRU
   :
 1.       : 20131224
          : y00245242
      : IMSCS
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCallRedial;
    VOS_UINT8                           ucSmsRedial;
    VOS_UINT8                           ucSsRedial;
    VOS_UINT8                           aucReserve[1];
}TAF_NV_SWITCH_DOMAIN_REDIAL_CONFIG_STRU;

/*****************************************************************************
     : TAF_NV_IMS_ROAMING_SUPPORT_STRU
   :
 1.       : 20131224
          : y00245242
      : IMS
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucImsRoamingFlg;
    VOS_UINT8                           aucReserve[3];
}TAF_NV_IMS_ROAMING_SUPPORT_STRU;

/*****************************************************************************
     : TAF_NV_IMS_USSD_SUPPORT_STRU
   :
 3.       : 20140401
          : y00245242
      : DTS2014040203732NVUSSDUSSDNV
                CS
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucUssdOnImsSupportFlag;
    VOS_UINT8                           aucReserve[3];
}TAF_NV_IMS_USSD_SUPPORT_STRU;

/*******************************************************************************
     : MTC_NV_PS_TRANSFER_CFG_STRU
   : MTCPSNV
  1.       : 20140117
           : l00198894
       : V9R1C53 C+L 
*******************************************************************************/
typedef struct
{
    MTC_PS_TRANSFER_ENUM_UINT8         enSolutionCfg;
    VOS_UINT8                          aucAdditonCfg[3];
} MTC_NV_PS_TRANSFER_CFG_STRU;

/*****************************************************************************
     : TAF_NV_PRODUCT_TYPE_FOR_LOG_DIRECTORY
   : FLASH NV
 1.       : 20140304
          : f62575
      : DTS2013091009786 FLASH
*****************************************************************************/
typedef struct
{
    TAF_FLASH_DIRECTORY_TYPE_ENUM_UINT16                     enFlashDirectoryType;
    VOS_UINT8                                                aucReserved1[2];
}TAF_NV_FLASH_DIRECTORY_TYPE_STRU;

/*******************************************************************************
     : MTC_RF_LCD_TIMER_INTERVAL_STRU
   : MIPICLK
  1.       : 20140304
           : j00174725
       : RF&LCD INTRUSION
*******************************************************************************/
typedef struct
{
    VOS_UINT32                          ulTimerInterval;                        /* , */
}MTC_RF_LCD_TIMER_INTERVAL_STRU;

/*******************************************************************************
     : MTC_NVIM_RF_LCD_MIPICLK_FREQ_STRU
   : MIPICLK
  1.       : 20140304
           : j00174725
       : RF&LCD INTRUSION
*******************************************************************************/
typedef struct
{
    VOS_UINT32                          ulMipiClk;                              /* MipiClk */
    VOS_UINT32                          aulFreq[MTC_RF_LCD_MIPICLK_FREQ_MAX_NUM];/* ulMipiClk */
}MTC_NVIM_RF_LCD_MIPICLK_FREQ_STRU;

/*******************************************************************************
     : MTC_NVIM_RF_LCD_CFG_STRU
   : MTCRF&LCDNV
  1.       : 20140304
           : j00174725
       : RF&LCD INTRUSION
*******************************************************************************/
typedef struct
{
    VOS_UINT16                          usEnableBitMap;                         /* bit0 */
    VOS_UINT16                          usFreqWidth;                            /*  100KHZ */
    MTC_NVIM_RF_LCD_MIPICLK_FREQ_STRU   astRfMipiClkFreqList[MTC_RF_LCD_MIPICLK_MAX_NUM]; /* 100KHZ */
} MTC_NVIM_RF_LCD_CFG_STRU;

/*****************************************************************************
     : ADS_UL_WATER_MARK_LEVEL_NV_STRU
   : ADS UL
   1.       : 20140603
            : f00179208
        : 
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulWaterLevel1;                          /* 1 */
    VOS_UINT32                          ulWaterLevel2;                          /* 2 */
    VOS_UINT32                          ulWaterLevel3;                          /* 3 */
    VOS_UINT32                          ulWaterLevel4;                          /* 4, */
} ADS_UL_WATER_MARK_LEVEL_STRU;

/*****************************************************************************
     : ADS_UL_WATER_MARK_LEVEL_NV_STRU
   : ADS UL
   1.       : 20140603
            : f00179208
        : 
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulThreshold1;                           /* 1 */
    VOS_UINT32                          ulThreshold2;                           /* 2 */
    VOS_UINT32                          ulThreshold3;                           /* 3 */
    VOS_UINT32                          ulThreshold4;                           /* 4 */
} ADS_UL_THRESHOLD_LEVEL_STRU;

/*****************************************************************************
     : ADS_UL_WATER_MARK_LEVEL_NV_STRU
   : ADS UL
   1.       : 20140603
            : f00179208
        : 
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulActiveFlag;                           /* : 0,1 */
    VOS_UINT32                          ulProtectTmrExpCnt;                     /*  */
    ADS_UL_WATER_MARK_LEVEL_STRU        stWaterMarkLevel;
    ADS_UL_THRESHOLD_LEVEL_STRU         stThresholdLevel;
    VOS_UINT32                          aulReserved[6];
} ADS_NV_DYNAMIC_THRESHOLD_STRU;

/*****************************************************************************
     : TAF_CALL_NVIM_ATA_REPORT_OK_ASYNC_CFG_STRU
   : en_NV_Item_Ata_Report_Ok_Async_Cfg NV
   :
 1.       : 20140623
          : z00161729
      : 

*****************************************************************************/
typedef struct
{
    /* VOS_TRUE:ataokconnectokconnect ack
       VOS_FALSE:,ataconnectconnect ackok */
    VOS_UINT8                           ucAtaReportOkAsyncFlag;
    VOS_UINT8                           aucReserved1[3];
}TAF_CALL_NVIM_ATA_REPORT_OK_ASYNC_CFG_STRU;



/*****************************************************************************
    : NV_NAS_JAM_DETECT_CFG_STRU
  : en_NV_Item_JAM_DETECT_CFG

1.       : 2014425
         : y00142674
     : 

*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucMode;                                 /* JAM0:, 1: */
    VOS_UINT8                           ucMethod;                               /* JAM1:12:2,2 */
    VOS_UINT8                           ucFreqNum;                              /* :[0,255] */
    VOS_UINT8                           ucThreshold;                            /* :[0,70] */
    VOS_UINT8                           ucJamDetectingTmrLen;                   /* (s) */
    VOS_UINT8                           ucJamDetectedTmrLen;                    /* (s) */
    VOS_UINT8                           ucFastReportFlag;                       /*  */
    VOS_UINT8                           aucRsv[1];
}NV_NAS_JAM_DETECT_CFG_STRU;
/*****************************************************************************
    : NV_NAS_WCDMA_JAM_DETECT_CFG_STRU
  : en_NV_Item_WCDMA_JAM_DETECT_CFG

1.       : 2015217
         : y00142674
     : 

*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucMode;                                 /* JAM0:, 1: */
    VOS_UINT8                           ucMethod;                               /* JAM1:12:2,2 */
    VOS_UINT8                           ucJamBandWidth;                         /* 30M */
    VOS_UINT8                           ucFastReportFlag;                       /*  */
    VOS_UINT8                           ucRssiSrhThreshold;                     /* RSSI:[0,70]70 */
    VOS_UINT8                           ucRssiSrhFreqPercent;                   /* RSSI(BAND):[0,100] */
    VOS_UINT16                          usPschSrhThreshold;                     /* PSCH:[0,65535] */
    VOS_UINT8                           ucPschSrhFreqPercent;                   /* PSCH(BAND):[0,100] */
    VOS_UINT8                           ucJamDetectingTmrLen;                   /* (s) */
    VOS_UINT8                           ucJamDetectedTmrLen;                    /* (s) */
    VOS_UINT8                           aucRsv[1];
}NV_NAS_WCDMA_JAM_DETECT_CFG_STRU;
/*******************************************************************************
     : TAF_NV_VCOM_DEBUG_CFG_STRU
   : VCOM DEBUGNV
  1.       : 20140603
           : n00269697
       : VCOM DEBUG
*******************************************************************************/
typedef struct
{
    VOS_UINT32                          ulDebugLevel;                           /* VCOM DEBUG:ERR,NORMAL,INFO,DEBUG */
    VOS_UINT32                          ulAppVcomPortIdMask;                    /* VCOMID */
    VOS_UINT32                          ulReserved[4];                          /*  */
} TAF_NV_PORT_DEBUG_CFG_STRU;

/*******************************************************************************
     : TAF_NVIM_FREQ_LOCK_CFG_STRU
   : NV
  1.       : 20140603
           : g00261581
       : V711 Cell Lock
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEnableFlg;                            /* 1:0: */
    TAF_NVIM_RAT_MODE_ENUM_UINT8        enRatMode;
    VOS_UINT16                          usLockedFreq;
    TAF_NVIM_GSM_BAND_ENUM_UINT16       enBand;
    VOS_UINT8                           aucReserved[2];
} TAF_NVIM_FREQ_LOCK_CFG_STRU;

/*****************************************************************************
     : TAF_NV_DSDS_ACTIVE_MODEM_MODE_STRU
   : DSDSModem
 1.       : 20140921
          : l00198894
      : DSDS/
*****************************************************************************/
typedef struct
{
    TAF_NV_ACTIVE_MODEM_MODE_ENUM_UINT8 enActiveModem;
    VOS_UINT8                           aucReserve[3];
}TAF_NV_DSDS_ACTIVE_MODEM_MODE_STRU;

/*******************************************************************************
     : TAF_NVIM_ECID_TL2GSM_CFG_STRU
   : AT+ECIDTDSCDMALTEGSM
  1.       : 20141111
           : l00198894
       : 
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEnableFlg;                            /* 1:0: */
    VOS_UINT8                           ucReserved;
    VOS_UINT16                          usMcc;                                  /* : 0x0460() */
} TAF_NVIM_ECID_TL2GSM_CFG_STRU;

/*****************************************************************************
     : TAF_NVIM_ENHANCED_OPER_NAME_SERVICE_CFG_STRU
   : en_NV_Item_ENHANCED_OPERATOR_NAME_SRV_CFG NV
 1.       : 201529
        : z00161729
    : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucOperNameServicePrioNum;

    /* 1PNNcosp^eonsucs2PNN;
       2CPHS,cops^eonsucs2CPHS;
       3MM INFO,cops^eonsucs2mm/gmm/emm information;
       4SPN,cops^eonsucs2SPN*/
    VOS_UINT8                           aucOperNameSerivcePrio[TAF_NVIM_MAX_OPER_NAME_SERVICE_PRIO_NUM];
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
    VOS_UINT8                           ucPlmnCompareSupportWildCardFlag; /* plmn */
    VOS_UINT8                           ucWildCard;                       /* ,a-f,0-9 */
    VOS_UINT8                           ucReserved4;
    VOS_UINT8                           ucReserved5;                      /* ^usimstub^refreshstub*/
}TAF_NVIM_ENHANCED_OPER_NAME_SERVICE_CFG_STRU;

/*****************************************************************************
     : TAF_NVIM_REFRESH_ALL_FILE_RESTART_CFG_STRU
   : en_NV_Item_REFRESH_ALL_FILE_RESTART_CFG NV
 1.       : 201529
        : z00161729
    : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucRefreshAllFileRestartFlag;  /* 0: mmapihrefreshmodem; 1:mmapihrefreshmodem*/
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
}TAF_NVIM_REFRESH_ALL_FILE_RESTART_CFG_STRU;


/*****************************************************************************
     : TAF_NVIM_REFRESH_USIM_DELAY_RESTART_CFG_STRU
   : TAF_NVIM_REFRESH_USIM_DELAY_RESTART_CFG_STRU NV

  1.       : 2016331
           : c00318887
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNormalCallDelayRestartFlg;            /* refresh: 0: modem; 1:modem */
    VOS_UINT8                           ucSmsDelayRestartFlg;                   /* refreshsms: 0: modem; 1:modem */
    VOS_UINT8                           ucSsDelayRestartFlg;                    /* refreshss: 0: modem; 1:modem */
    VOS_UINT8                           ucNoServiceDelayRestartFlg;             /* refresh: 0: modem; 1:modem */
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
    VOS_UINT8                           ucReserved4;
    VOS_UINT8                           ucReserved5;
}TAF_NVIM_REFRESH_USIM_DELAY_RESTART_CFG_STRU;


/*****************************************************************************
   : TAF_NV_PDN_TEARDOWN_POLICY_STRU
   : PDN

  1.       : 2014111
           : A00165503
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucAllowDefPdnTeardownFlg;
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;

} TAF_NV_PDN_TEARDOWN_POLICY_STRU;

typedef struct
{
    TAF_XSMS_DATA_REQ_SEND_CHAN_ENUM_UINT8                  enXsmsChannelOption;    /*  */
    VOS_UINT8                                               ucResendMax;            /* 5 */
    VOS_UINT8                                               ucResendInterval;       /* 1 */
    VOS_UINT8                                               ucReconnectInterval;    /* 5 */
}TAF_NVIM_1X_XSMS_CFG_STRU;

/*****************************************************************************
    : TAF_NVIM_1X_MT_SMS_TCH_RELEASE_CFG
  : UEUE

  1.       : 20161206
           : y00314741
       : 
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucIsCfgEnableFlg;                /* TRUEFALSE */
    VOS_UINT8                           ucTimerLength;                   /*   */
    VOS_UINT8                           aucReserved[2];
}TAF_NVIM_1X_MT_SMS_TCH_RELEASE_CFG;

/*****************************************************************************
    : TAF_NVIM_CFREQ_LOCK_CFG_STRU
  : 1X/EVDO

  1.       : 20141229
           : y00307564
       : 
*******************************************************************************/
typedef struct
{
    TAF_MMA_CFREQ_LOCK_MODE_TYPE_ENUM_UINT8                 enFreqLockMode;
    VOS_UINT8                                               aucReserve[3];
    VOS_UINT16                                              usSid;
    VOS_UINT16                                              usNid;
    VOS_UINT16                                              usCdmaBandClass;
    VOS_UINT16                                              usCdmaFreq;
    VOS_UINT16                                              usCdmaPn;
    VOS_UINT16                                              usEvdoBandClass;
    VOS_UINT16                                              usEvdoFreq;
    VOS_UINT16                                              usEvdoPn;
}TAF_NVIM_CFREQ_LOCK_CFG_STRU;

/*****************************************************************************
   : TAF_NV_TTY_CFG_STRU
   : TTY MODE

  1.       : 20150207
           : w00316404
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucTTYMode;/*TTY0-3default:0*/
    VOS_UINT8                           ucReserved0;
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;

} TAF_NV_TTY_CFG_STRU;

/*******************************************************************************
     : TAF_NV_RAT_FREQUENTLY_SWITCH_CHR_RPT_CFG_STRU
   : gutlCHRNV
  1.       : 20150310
           : n00269697
       : CHR optimize
*******************************************************************************/
typedef struct
{
    VOS_UINT32                          ulStatisticTime;                        /*  */
    VOS_UINT32                          ulSwitchNum;                            /* gutl */
} TAF_NV_RAT_FREQUENTLY_SWITCH_CHR_RPT_CFG_STRU;

/*******************************************************************************
     : TAF_CALL_NVIM_CCWA_CTRL_MODE_STRU
   : NV
  1.       : 20150824
           : n00269697
       : ims_call_wait
*******************************************************************************/
typedef struct
{
    /* NV ulCcwaCtrlMode03gpp
       ulCcwaCtrlMode1UEVOLTE
      VoLTEAPCCWAIMSVoLTECCWAUE
       VOLTEVOLTECCWAI
    */
    TAF_CALL_CCWA_CTRL_MODE_ENUM_U8     enCcwaCtrlMode;
    TAF_CALL_CCWAI_MODE_ENUM_UINT8      enCcwaiMode;
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
} TAF_CALL_NVIM_CCWA_CTRL_MODE_STRU;

/*******************************************************************************
     : TAF_EMC_CS_TO_IMS_REDIAL_CFG_STRU
   : CSIMSNV
  1.       : 20160330
           : n00269697
       : VOLTE_EMC
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEmcCs2ImsRedialSupportFlg;
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
} TAF_EMC_CS_TO_IMS_REDIAL_CFG_STRU;


/*****************************************************************************
     : TAF_NVIM_CCPU_RESET_RECORD_STRU
   : en_NV_Item_Ccpu_Reset_Record NV
 1.       : 2015525
          : n00269697
      : ROAM_PLMN_SELECTION_OPTIMIZE_2.0 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCcpuResetFlag;                        /* 0:C ;
                                                                                   1:C*/
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
}TAF_NVIM_CCPU_RESET_RECORD_STRU;


/*****************************************************************************
    : TAF_NVIM_1X_DATA_SO_CFG
  : NVSO

  1.       : 2015812
           : c00299063
       : 
*******************************************************************************/
typedef struct
{
    VOS_UINT16                          usSo;
    VOS_UINT8                           aucReserved[2];
}TAF_NVIM_1X_DATA_SO_CFG;



/*****************************************************************************
    : TAF_NVIM_DATA_GENERIC_CONFIG_STRU
  : NV

  1.       : 2015422
           : c00299063
       : 
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucPktCdataInactivityTmrLen;     /* CDMA,  */
    VOS_UINT8                           ucSwitchOnWaitCLTmerLen;        /* CL */
    VOS_UINT8                           uc1xBackOffToDoTmrLen;          /* 1Xinactive timer
                                                                           1X backof to DO.0  */
    VOS_UINT8                           ucLessPktCdataInactivityTmrLen; /* CDMA, , 1s */
}TAF_NVIM_CDATA_GENERIC_CONFIG_STRU;


/*****************************************************************************
   : TAF_NV_ADS_WAKE_LOCK_CFG_STRU
   : ADS WALE LOCK

  1.       : 20150923
           : A00165503
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulEnable;           /*  */
    VOS_UINT32                          ulTxWakeTimeout;    /*  */
    VOS_UINT32                          ulRxWakeTimeout;    /*  */
    VOS_UINT32                          ulReserved;

} TAF_NV_ADS_WAKE_LOCK_CFG_STRU;

/*****************************************************************************
     : TAF_NV_ADS_IPF_MODE_CFG_STRU
   : IPFADS

 1.       : 2016113
          : l00373346
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucIpfMode;                              /* IPFADS, 0: ()1 */
    VOS_UINT8                           ucReserved0;
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
} TAF_NV_ADS_IPF_MODE_CFG_STRU;

/*****************************************************************************
     : TAF_NV_RNIC_NET_IF_CFG_STRU
   : RNICLinux

 1.       : 20170310
          : l00373346
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNetInterfaceMode;                     /* RNICLinux, 0: Net_rx()1NAPI */
    VOS_UINT8                           ucNapiPollWeight;                       /* RNICNAPIpoll */
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
} TAF_NV_RNIC_NET_IF_CFG_STRU;

/*****************************************************************************
   : TAF_NV_ADS_MEM_CFG_STRU
   : 

  1.       : 20151006
           : A00165503
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usBlkNum;
    VOS_UINT16                          usReserved0;
    VOS_UINT16                          usReserved1;
    VOS_UINT16                          usReserved2;

} TAF_NV_ADS_MEM_CFG_STRU;

/*****************************************************************************
   : TAF_NV_ADS_MEM_POOL_CFG_STRU
   : 

  1.       : 20151006
           : A00165503
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulEnable;
    TAF_NV_ADS_MEM_CFG_STRU             astMemCfg[2];

} TAF_NV_ADS_MEM_POOL_CFG_STRU;


/*****************************************************************************
     : TAF_XCALL_NVIM_1X_EMC_CALL_REDIAL_PERIOD_STRU
   : en_Nv_Item_EMC_REDIAL_PERIOD NV
 1.       : 2015615
          : c00299063
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                              ulEmcCallRedialPeriod;  /*  */
} TAF_XCALL_NVIM_1X_EMC_CALL_REDIAL_PERIOD_STRU;

/*****************************************************************************
    : TAF_NVIM_1X_VOICE_SO_CFG
  : NV so

  1.       : 2015819
           : c00299063
       : 
*******************************************************************************/
typedef struct
{
    VOS_UINT16                          usSo;
    VOS_UINT8                           aucReserved[2];
}TAF_NVIM_1X_VOICE_SO_CFG;



/*****************************************************************************
   : TAF_NV_NVWR_SEC_CTRL_STRU
   : NVWR

  1.       : 20150404
           : l00198894
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucSecType;
    VOS_UINT8                           ucBlackListNum;
    VOS_UINT16                          ausBlackList[TAF_NV_BLACK_LIST_MAX_NUM];
} TAF_NV_NVWR_SEC_CTRL_STRU;

/*****************************************************************************
     : TAF_NVIM_CCPU_RESET_RECORD_STRU
   : en_NV_Item_Ipv6_Address_Test_Mode_Cfg NV
 1.       : 2015729
          : n00269697
      : DTS2015072804293 
*****************************************************************************/
typedef struct
{
    VOS_UINT32                           ulIpv6AddrTestModeCfg;                 /* 0x55aa55aa */
}TAF_NVIM_IPV6_ADDR_TEST_MODE_CFG_STRU;

/*****************************************************************************
     : TAF_MMA_NVIM_DELAY_REPORT_SERVICE_STATUS_STRU
   : en_NV_Item_DELAY_REPORT_SERVICE_STATUS_CFG NV
 1.        : 20150211
           : l00305157
       : Service_State_Optimize_PhaseII 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEnable;                               /* 0:NV ; 1:NV  */
    VOS_UINT8                           aucReserved[3];
    VOS_UINT32                          ulRptSrvStaDelayTimerValue;             /*,: */
}TAF_MMA_NVIM_DELAY_REPORT_SERVICE_STATUS_STRU;

/*****************************************************************************
     : TAF_MMA_NVIM_DELAY_RPT_CLNOSERVICE_STRU
   : TAF_MMA_NVIM_DELAY_RPT_CLNOSERVICE_STRU
  1.       : 20160106
           : h00313353
       : CL
*****************************************************************************/
typedef struct
{
    VOS_UINT8   ucCLDelayTimerLen;                                              /* DO+LTE: 0: */
    VOS_UINT8   ucDoDelayTimerLen;                                              /* DO: 0: */
    VOS_UINT8   ucReserved1;
    VOS_UINT8   ucReserved2;
}TAF_MMA_NVIM_DELAY_RPT_CLNOSERVICE_STRU;

/*****************************************************************************
     : TAF_XCALL_NVIM_START_AND_STOP_CONT_DTMF_INTERVAL_STRU
   : en_NV_Item_START_AND_STOP_CONT_DTMF_INTERVAL NV
 1.       : 2015818
          : l00324781
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulStartAndStopContDtmfIntervalLen;  /* :ms  */
}TAF_XCALL_NVIM_START_AND_STOP_CONT_DTMF_INTERVAL_STRU;

/*****************************************************************************
     : TAF_XCALL_NVIM_CTCC_ROAM_EMC_CALL_CFG_STRU
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
}TAF_XCALL_NVIM_CTCC_ROAM_EMC_CALL_CFG_STRU;


/*****************************************************************************
   : TAF_NV_PRINT_MODEM_LOG_TYPE_STRU
   : modem log

  1.       : 20151017
           : w00316404
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucPrintModemLogType;                    /* 0:modem log1:modem logdefault:0 */
    VOS_UINT8                           ucReserved0;
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
} TAF_NV_PRINT_MODEM_LOG_TYPE_STRU;

/*****************************************************************************
     : TAF_MMA_NVIM_CL_DELAY_REPORT_SERVICE_STATUS_STRU
   : CL NV
 1.       : 2015818
          : l00324781
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCLDelayRptEnable;
    VOS_UINT8                           aucReserved1[3];
    VOS_UINT32                          ulCLRptSrvStaDelayTimerLen;
    VOS_UINT8                           aucReserved2[12];
}TAF_MMA_NVIM_CL_DELAY_REPORT_SERVICE_STATUS_STRU;


/*****************************************************************************
     : CNAS_MMA_NVIM_CDMA_SUPPORT_BANDCLASS_MASK_STRU
   :
 ASN.1 :
   : CDMA  3601
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulSupportBandclassMask;               /* bit0x000000010 */
}CNAS_MMA_NVIM_CDMA_SUPPORT_BANDCLASS_MASK_STRU;


/*****************************************************************************
     : TAF_NVIM_NONNORMAL_REG_STATUS_MERGE_CFG_STRU
   : en_NV_Item_NONNORMAL_REG_STATUS_MERGE_CFG NV
 1.       : 20151028
          : z00359541
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucMergeFlg;                             /*  */
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
}TAF_NVIM_NONNORMAL_REG_STATUS_MERGE_CFG_STRU;

/*****************************************************************************
     : TAF_NVIM_ENCVOICE_ECC_SRV_CAP_INFO_STRU
   : ECC
             : ECCECC

       :
  1.       : 20151023
           : h00313353
       : Iteration 19
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEccSrvCap;        /* ECC: TRUE -- ECCFALSE -- ECC */
    VOS_UINT8                           ucEccSrvStatus;     /* ECC: TRUE -- ECCFALSE -- ECC */
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
} TAF_NVIM_ENCVOICE_ECC_SRV_CAP_INFO_STRU;

/*****************************************************************************
     : TAF_NVIM_ENCVOICE_ECC_PUB_KEY_INFO_STRU
   : ECCK0

       :
  1.       : 20151023
           : h00313353
       : Iteration 19
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucVerNum;
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
    VOS_UINT8                           aucPubKey[TAF_NVIM_KMC_MSG_MAX_KMC_PUB_KEY_LEN];
} TAF_NVIM_ENCVOICE_ECC_PUB_KEY_INFO_STRU;

/*****************************************************************************
     : TAF_NVIM_ENCVOICE_SECINFO_ERASE_SYSTIME_INFO_STRU
   : 

   :
  1.       : 20151023
           : h00313353
       : Iteration 19
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usYear;     /* Year [1980..2100) */
    VOS_UINT16                          usMonth;    /* Month of year [1..12] */
    VOS_UINT16                          usDay;      /* Day of month [1..31] */
    VOS_UINT16                          usHour;     /* Hour of day [0..23] */
    VOS_UINT16                          usMinute;   /* Minute of hour [0..59] */
    VOS_UINT16                          usSecond;   /* Second of minute [0..59] */
} TAF_NVIM_ENCVOICE_SECINFO_ERASE_SYSTIME_INFO_STRU;

/*****************************************************************************
     : TAF_NVIM_ENCVOICE_PASSWD_RESET_SYSTIME_INFO_STRU
   : 

   :
  1.       : 20151023
           : h00313353
       : Iteration 19
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usYear;     /* Year [1980..2100) */
    VOS_UINT16                          usMonth;    /* Month of year [1..12] */
    VOS_UINT16                          usDay;      /* Day of month [1..31] */
    VOS_UINT16                          usHour;     /* Hour of day [0..23] */
    VOS_UINT16                          usMinute;   /* Minute of hour [0..59] */
    VOS_UINT16                          usSecond;   /* Second of minute [0..59] */
} TAF_NVIM_ENCVOICE_PASSWD_RESET_SYSTIME_INFO_STRU;

/*****************************************************************************
     : TAF_NVIM_ENCVOICE_TIMER_CFG_INFO_STRU
   : 

       :
  1.       : 20151023
           : h00313353
       : Iteration 19
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucDelayEncVoiceReqTimerLen;
    VOS_UINT8                           ucReserved1;
    VOS_UINT16                          usRemoteCtrlAnswerTimerLen;
} TAF_NVIM_ENCVOICE_TIMER_CFG_INFO_STRU;

/*****************************************************************************
     : TAF_NVIM_1X_CALLBACK_CFG_STRU
   : en_Nv_Item_CNAS_XSD_CALLBACK_CFG NV
 1.       : 201619
          : w00242748
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulCallBackEnableFlg;
    VOS_UINT32                          ulCallBackModeTimerLen;
} TAF_NVIM_1X_CALLBACK_CFG_STRU;

/*****************************************************************************
     : TAF_NVIM_NDIS_FILTER_ENABLE_FLAG_CFG_STRU
   : en_NV_Item_NDIS_FILTER_FLAG_CFG NV
 1.       : 20151226
          : g00261581
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEnableFlag;                           /* VOS_TRUE:FilterVOS_FALSE: */
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
}TAF_NVIM_NDIS_FILTER_ENABLE_FLAG_CFG_STRU;

/*****************************************************************************
     : TAF_NVIM_1X_NW_NORMAL_REL_REDIAL_STRATEGY_STRU
   : TAF_NVIM_1X_NW_NORMAL_REL_REDIAL_STRATEGY_STRU NV
 1.       : 20160425
          : g00261581
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucRedialInterTimerLen;   /* 1 */
    VOS_UINT8                           ucRedialNum;             /* 1 */
    VOS_UINT8                           ucRsv1;
    VOS_UINT8                           ucRsv2;
} TAF_NVIM_1X_NW_NORMAL_REL_REDIAL_STRATEGY_STRU;

/*****************************************************************************
     : TAF_NVIM_1X_NW_NORMAL_REL_REDIAL_STRATEGY_CFG_STRU
   :  NV
 1.       : 20160425
          : g00261581
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucPhaseNum;    /* : 44s10s15s20s */
    VOS_UINT8                                               ucReserved1;
    VOS_UINT8                                               ucReserved2;
    VOS_UINT8                                               ucReserved3;
    TAF_NVIM_1X_NW_NORMAL_REL_REDIAL_STRATEGY_STRU          astRedialInfo[TAF_NVIM_MAX_1X_NW_NORMAL_REL_REDIAL_PHASE_NUM];
} TAF_NVIM_1X_NW_NORMAL_REL_REDIAL_STRATEGY_CFG_STRU;

/*****************************************************************************
     : TAF_NVIM_DO_BACK_TO_LTE_CFG_STRU
   :  NV
 1.       : 20160727
          : y00314741
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucHrpdEnable;                    /* SRLTE: HRPD */
    VOS_UINT8                           ucEhrpdEnable;                   /* SRLTE: EHRPD */
    VOS_UINT8                           ucDoBackToLteTmrLen;             /* DOinactive timer
                                                                                   55 */
    VOS_UINT8                           ucMinPktCdataInactivityTmrLen;   /* CDMA, , 1s */

} TAF_NVIM_DO_BACK_TO_LTE_CFG_STRU;

/*****************************************************************************
     : TAF_XSMS_MO_TL_ACK_TIME_OUT_CFG_STRU
   :  NV
 1.       : 20160119
          : C00299064
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucIsCfgEnable;  /* VOS_TRUE:  VOS_FALSE: */
    TAF_XSMS_TL_ACK_NEED_LEVEL_ENUM_UINT8                   enTlAckNeedLevel;
    VOS_UINT8                                               ucMaxFlacQryTime; /*   : 2*/
    VOS_UINT8                                               ucFlacQryInterVal;/*  :  6 600ms */
}TAF_XSMS_MO_TL_ACK_TIME_OUT_CFG_STRU;

/*****************************************************************************
     : TAF_XSMS_KMC_DEF_ADDRESS_STRU
   :  NV
 1.       : 20151014
          : C00299064
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usNumOfDigits;
    VOS_UINT8                           aucDigits[38]; /* DTMF */
}TAF_XSMS_KMC_DEF_ADDRESS_STRU;

/*****************************************************************************
     : TAF_NVIM_CTCC_OOS_TIMER_CFG_STRU
   :  OOS
 1.       : 2016215
          : w00242748
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usTimes;
    VOS_UINT16                          usTimerLen;
}TAF_NVIM_CTCC_OOS_TIMER_CFG_STRU;

/*****************************************************************************
     : TAF_NVIM_CTCC_OOS_CONFIG_STRU
   :  NV
 1.       : 2016215
          : w00242748
      : 
*****************************************************************************/
typedef struct
{
    TAF_NVIM_CTCC_OOS_TIMER_CFG_STRU    astClOosTimerCfg[TAF_NVIM_CTCC_OOS_TIMER_MAX_PHASE];
    TAF_NVIM_CTCC_OOS_TIMER_CFG_STRU    astGulOosTimerCfg[TAF_NVIM_CTCC_OOS_TIMER_MAX_PHASE];
}TAF_NVIM_CTCC_OOS_CONFIG_STRU;

/*****************************************************************************
     : TAF_NVIM_GET_DNS_THTOUGH_DHCP_CFG_STRU
   :  DHCPDNS
 1.       : 2016229
          : y00213812
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNeedGetDnsByDhcp;                     /* 100 */

    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;

}TAF_NVIM_GET_DNS_THTOUGH_DHCP_CFG_STRU;


/*****************************************************************************
     : TAF_NVIM_LTE_LOST_EVENT_STRU
   : en_NV_Item_Lte_Lost_Chr_Cfg NV
 1.        : 20160324
           : g00322017
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEnable;                       /* 0:NV ; 1:NV  */
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
    VOS_UINT32                          ulGutlTriggerLteLostTimerValue; /* GUTL4G */
    VOS_UINT32                          ulClTriggerLteLostTimerValue;   /* CL4G */
    VOS_UINT32                          ulRptLteLostTimerValue;         /* 4G,:4G */
    VOS_UINT32                          ulReserved1;
    VOS_UINT32                          ulReserved2;
    VOS_UINT32                          ulReserved3;
}TAF_NVIM_LTE_LOST_EVENT_STRU;


/*****************************************************************************
     : TAF_NVIM_XCPOSRRPT_CFG_STRU
   : NV
 1.       : 20160309
          : h00360002
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucXcposrRptNvCfg;                       /* GPS */
    VOS_UINT8                           ucCposrDefault;
    VOS_UINT8                           ucXcposrDefault;
    VOS_UINT8                           ucXcposrRptDefault;
}TAF_NVIM_XCPOSRRPT_CFG_STRU;
/*****************************************************************************
     : TAF_NVIM_1X_CS_CALL_REDIR_CMPL_DELAY_TIMER_INFO_STRU
   : NVen_NV_Item_1X_CS_CALL_WAIT_REDIR_CMPL_DELAY_TIMER_INFO
 1.       : 20160528
          : y00322978
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           uc1xCsCallWaitRedirCmplTimerLen;         /* :  */
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
}TAF_NVIM_1X_CS_CALL_REDIR_CMPL_DELAY_TIMER_INFO_STRU;

/*****************************************************************************
     : TAF_NVIM_ICC_ID_STRU
   :    ICC ID
 1.       : 20160408
          : w00316404
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucLen;
    VOS_UINT8                           aucIccId[TAF_NVIM_ICC_ID_MAX];
}TAF_NVIM_ICC_ID_STRU;

/*****************************************************************************
     : TAF_NVIM_RPM_CFG_STRU
   : RPM
 1.       : 20160408
          : w00316404
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucRpmCap;
    VOS_UINT8                           ucRpmEnableFlag;
    VOS_UINT8                           ucRpmVersion;
    VOS_UINT8                           ucReserved0;
    TAF_NVIM_ICC_ID_STRU                stUiccInfo;
    VOS_UINT8                           ucRpmParaN1;
    VOS_UINT8                           ucRpmParaT1;
    VOS_UINT8                           ucRpmParaF1;
    VOS_UINT8                           ucRpmParaF2;
    VOS_UINT8                           ucRpmParaF3;
    VOS_UINT8                           ucRpmParaF4;
    VOS_UINT8                           aucReserved1[TAF_NVIM_RPM_RSV_PARA_NUM];
}TAF_NVIM_RPM_CFG_STRU;

/*****************************************************************************
     : TAF_NVIM_RPM_TIMER_INFO_STRU
   : NV
 1.       : 20160510
          : h00360002
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucTimersStatus;                         /* RPMN1LR1LR2 */
    VOS_UINT8                           ucApResetCounter;
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT32                          ulN1TimerStartRtc;
    VOS_UINT32                          ulLR1TimerStartRtc;
    VOS_UINT32                          ulLR2TimerStartRtc;
    VOS_UINT32                          ulLR3TimerStartRtc;
}TAF_NVIM_RPM_TIMER_INFO_STRU;

/*****************************************************************************
     : TAF_NVIM_RPM_STUB_STRU
   : NV
 1.       : 20160525
          : l00198894
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           bitOpRpmEnabledFlagFile     :1;         /* RPM EnabledFlag */
    VOS_UINT8                           bitOpRpmParaFile            :1;         /* RPM Para */
    VOS_UINT8                           bitOpRpmOmcLrFile           :1;         /* RPM OmcLr */
    VOS_UINT8                           bitOpRpmOmcFile             :1;         /* RPM Omc */
    VOS_UINT8                           bitSpare                    :4;

    VOS_UINT8                           ucStubEnable;                           /* RPM */
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucImsiStubFlag;                         /* SIMIMSI */
    VOS_UINT32                          ulRpmMcc;                               /* RPMMCC */
    VOS_UINT32                          ulRpmMnc;                               /* RPMMNC */

    /* RPM Enabled Flag */
    VOS_UINT8                           ucRpmEnabledFlagFile;

    /* RPM Parameters */
    VOS_UINT8                           ucRpmParaFileN1;
    VOS_UINT8                           ucRpmParaFileT1;
    VOS_UINT8                           ucRpmParaFileF1;
    VOS_UINT8                           ucRpmParaFileF2;
    VOS_UINT8                           ucRpmParaFileF3;
    VOS_UINT8                           ucRpmParaFileF4;

    /* RPM Operational Management Counters Leak Rate */
    VOS_UINT8                           ucRpmOmcLrFileLr1;
    VOS_UINT8                           ucRpmOmcLrFileLr2;
    VOS_UINT8                           ucRpmOmcLrFileLr3;

    /* RPM Operational Management Counters */
    VOS_UINT8                           ucRpmOmcFileCbr1;
    VOS_UINT8                           ucRpmOmcFileCr1;
    VOS_UINT8                           ucRpmOmcFileCPdp1;
    VOS_UINT8                           ucRpmOmcFileCPdp2;
    VOS_UINT8                           ucRpmOmcFileCPdp3;
    VOS_UINT8                           ucRpmOmcFileCPdp4;

}TAF_NVIM_RPM_STUB_STRU;


/*****************************************************************************
     : TAF_NVIM_USER_REBOOT_SUPPORT_STRU
   : 
 1.       : 20160530
          : h00360002
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucUserRebootConfig;
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
}TAF_NVIM_USER_REBOOT_SUPPORT_STRU;

/*****************************************************************************
     : TAF_NVIM_CCTC_ROAM_CTRL_CFG_STRU
   : CCTCucEnableModemCtrl
             MODEMAP
 1.       : 20160429
          : y00245242
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucModemCtrlFlag;
    VOS_UINT8                           aucReserved[3];
}TAF_NVIM_CCTC_ROAM_CTRL_CFG_STRU;


/*****************************************************************************
     : TAF_NVIM_MULTIMODE_RAT_CFG_STRU
   : SYS CFG RAT

 1.       : 20160503
          : y00245242
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucRatOrderNum;                                      /* syscfgexacqoder */
    VOS_UINT8                           aenRatOrder[TAF_NVIM_MAX_USER_SYS_CFG_RAT_NUM];     /* syscfgexacqoder */
    VOS_UINT8                           aucReserved[2];
}TAF_NVIM_MULTIMODE_RAT_CFG_STRU;

/*****************************************************************************
     : TAF_NVIM_UNKONWN_DUAL_MODE_CARD_MODE_SWITCH_CFG_STRU
   : CDMA

 1.       : 2016-7-13
          : l00359089
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucAlloweModeSwitchFlg;
    VOS_UINT8                           aucReserved[3];
}TAF_NVIM_UNKONWN_DUAL_MODE_CARD_MODE_SWITCH_CFG_STRU;


/*****************************************************************************
     : TAF_NVIM_SPM_VOICE_DOMAIN_SEL_CFG_STRU
   : 
  1.       : 20160712
           : m00217266
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                              ulEmcRetryPeriod;           /*  */
    TAF_SPM_NVIM_MULTIMODE_EMC_CS_PRFER_TYPE_ENUM_UINT8     enMultiModeEmcCsPreferType; /* cs prefer3gpp3gpp2 cs */
    VOS_UINT8                                               ucCycleRetryFlag;           /*  */
    VOS_UINT8                                               ucLteLimitServiceSelIms;    /* SPMPSLTEIMS */
    VOS_UINT8                                               ucCycRetryIntervalPeriod;   /*  */
    VOS_UINT8                                               ucEnableFlg;                /* SPMUE */
    VOS_UINT8                                               ucSpmVoiceDomain;           /* SPM0:cs only 1:ps only 2:cs prefer 3:ps prefer */
    VOS_UINT8                                               ucSpmEmsDomain;             /* SPM0:cs forced 1:cs prefer 2:ps prefer */
    VOS_UINT8                                               ucEmcCellularSrvAcqTiLen;   /* vowificellular :s */
}TAF_NVIM_SPM_VOICE_DOMAIN_SEL_CFG_STRU;

/*****************************************************************************
     : TAF_NVIM_SPM_EMC_CUSTOM_CFG_STRU
   : en_NV_Item_Taf_Spm_Emc_Custom_Cfg
  1.       : 20180424
           : j00174725
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucInternationalRoamEmcNotSelIms;
    VOS_UINT8                           usReserved1;
    VOS_UINT8                           usReserved2;
    VOS_UINT8                           usReserved3;
    VOS_UINT8                           usReserved4;
    VOS_UINT8                           usReserved5;
    VOS_UINT8                           usReserved6;
    VOS_UINT8                           usReserved7;
}TAF_NVIM_SPM_EMC_CUSTOM_CFG_STRU;


/*****************************************************************************
     : TAF_NVIM_LTE_SMS_CFG_STRU
   : lte3gpp2

 1.       : 20160503
          : y00245242
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucLteSmsEnable;         /* LTE3GPP2 VOS_TURE:,VOS_FALSE: */
    TAF_LSMS_RESEND_FLAG_ENUM_UINT8                         enResendFlag;           /*  */
    VOS_UINT8                                               ucResendMax;            /* 1 */
    VOS_UINT8                                               ucResendInterval;       /* : 30 */
}TAF_NVIM_LTE_SMS_CFG_STRU;

/*****************************************************************************
     : MTC_NVIM_FREQ_WIDTH_STRU
   : 

 1.       : 20160726
          : w00351686
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usGsmFreqWidth;                         /* GSM  100KHZ */
    VOS_UINT16                          usWcdmaFreqWidth;                       /* WCDMA100KHZ */
    VOS_UINT16                          usTdsFreqWidth;                         /* TDS  100KHZ */
    VOS_UINT16                          usLteFreqWidth;                         /* LTE  100KHZ */
    VOS_UINT16                          usCdmaFreqWidth;                        /* CDMA 100KHZ */
    VOS_UINT16                          usReserved1;
} MTC_NVIM_FREQ_WIDTH_STRU;

/*****************************************************************************
     : MTC_NVIM_INTRUSION_FREQ_LIST_STRU
   : 

 1.       : 20160726
          : w00351686
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usIntrusionFreq;                        /* , 100KHZ */
    VOS_UINT8                           ucIntrusionFreqWidth;                   /* ,100KHZ */
    VOS_UINT8                           ucIntrusionFreqWeight;                  /* ,0^10 */
}MTC_NVIM_INTRUSION_FREQ_LIST_STRU;

/*****************************************************************************
     : MTC_NVIM_DEVICE_FREQ_CFG_STRU
   : CASE

 1.       : 20160726
          : w00351686
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucIntrusionFreqNum;                                           /*  */
    VOS_UINT8                           aucReserved[3];
    MTC_NVIM_INTRUSION_FREQ_LIST_STRU   astIntrusionFreqList[MTC_INTRUSION_DEVICE_FREQ_LIST_MAX_NUM]; /*  */
}MTC_NVIM_DEVICE_FREQ_CASE_STRU;

/*****************************************************************************
     : MTC_NVIM_DEVICE_FREQ_CFG_STRU
   : 

 1.       : 20160726
          : w00351686
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucActiveFreqCaseNum;                                       /*  */
    VOS_UINT8                           ucDeviceID;                                                /* ID */
    VOS_UINT8                           aucReserved[2];
    MTC_NVIM_DEVICE_FREQ_CASE_STRU      astDeviceFreqCase[MTC_INTRUSION_DEVICE_FREQ_CASE_MAX_NUM]; /*  */
}MTC_NVIM_DEVICE_FREQ_CFG_STRU;

/*****************************************************************************
     : MTC_NVIM_MODEM_FREQ_WEIGHT_STRU
   : Modem

 1.       : 20160726
          : w00351686
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucScellWeight;                           /* ,0^100 */
    VOS_UINT8                           ucNcellWeight;                           /* ,0~10 */
    VOS_UINT8                           aucReserved[6];
}MTC_NVIM_MODEM_FREQ_WEIGHT_STRU;

/*****************************************************************************
     : MTC_NVIM_DYNAMIC_FM_INTRUSION_CTRL_CFG_STRU
   : NV

 1.       : 20160726
          : w00351686
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucActiveDeviceNum;                                    /* 1~8,0 */
    VOS_UINT8                           aucReserved[3];
    MTC_NVIM_FREQ_WIDTH_STRU            stFreqWidth;                                          /* GUTLC */
    MTC_NVIM_DEVICE_FREQ_CFG_STRU       astDeviceFreqCfg[MTC_INTRUSION_DEVICE_GROUP_MAX_NUM]; /* 8 */
    MTC_NVIM_MODEM_FREQ_WEIGHT_STRU     stModemFreqWeightCfg;                                 /* Modem */
} MTC_NVIM_DYNAMIC_FM_INTRUSION_CTRL_CFG_STRU;

/*****************************************************************************
     : TAF_NV_PDP_REDIAL_FOR_NO_CAUSE_CFG_STRU
   : 

 1.       : 20160831
          : l00373346
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEnable;                               /* , 1: 0 */
    VOS_UINT8                           aucReversed[3];                         /*  */
} TAF_NV_PDP_REDIAL_FOR_NO_CAUSE_CFG_STRU;


/*****************************************************************************
     : TAF_NVIM_LGU_SUPPORT_CFG_STRU
   : LGU+
 1.       : 20160806
          : w00316404
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucLguSupportConfig;                     /* 1:LGU0:LGU0 */
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
    VOS_UINT8                           ucReserved4;
    VOS_UINT8                           ucReserved5;
    VOS_UINT8                           ucReserved6;
    VOS_UINT8                           ucReserved7;
    VOS_UINT8                           ucReserved8;
    VOS_UINT8                           ucReserved9;
    VOS_UINT8                           ucReserved10;
    VOS_UINT8                           ucReserved11;
}TAF_NVIM_LGU_SUPPORT_CFG_STRU;


/*****************************************************************************
     : TAF_MMA_NVIM_CTCC_DUAL_MODE_IMSI_PLMN_INFO_STRU
   : IMSI PLMN

 1.       : 20160909
          : y00245242
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucCsimPlmnNum;
    VOS_UINT8                                               ucUsimPlmnNum;
    VOS_UINT8                                               aucReserved[2];
    VOS_UINT32                                              aulCsimPlmn[TAF_NVIM_MAX_CTCC_CSIM_PLMN_NUM];
    VOS_UINT32                                              aulUsimPlmn[TAF_NVIM_MAX_CTCC_USIM_PLMN_NUM];
}TAF_MMA_NVIM_CTCC_DUAL_MODE_IMSI_PLMN_INFO_STRU;

/* Added by c00380008 for AGPSR12R13, 2016-10-14, begin */
/*****************************************************************************
     : TAF_MTA_NVIM_CPOS_PROTOCOL_VERSION_CFG_STRU
   : NVMTAGPS

 1.       : 20161014
          : c00380008
      : 
*****************************************************************************/
typedef struct
{
    /* 0: R12; 1: R13 */
    VOS_UINT32                          bitOpQosRespTime            : 2;
    VOS_UINT32                          bitOpLocInfoTypeRespTime    : 2;
    VOS_UINT32                          bitOpGnssTodS               : 2;
    VOS_UINT32                          bitOpReserved0              : 2;
    VOS_UINT32                          bitOpReserved1              : 2;
    VOS_UINT32                          bitOpReserved2              : 2;
    VOS_UINT32                          bitOpReserved3              : 2;
    VOS_UINT32                          bitOpReserved4              : 2;
    VOS_UINT32                          bitOpReserved5              : 2;
    VOS_UINT32                          bitOpReserved6              : 2;
    VOS_UINT32                          bitOpReserved7              : 2;
    VOS_UINT32                          bitOpReserved8              : 2;
    VOS_UINT32                          bitOpReserved9              : 2;
    VOS_UINT32                          bitOpReserved10             : 2;
    VOS_UINT32                          bitOpReserved11             : 2;
    VOS_UINT32                          bitOpReserved12             : 2;
    VOS_UINT32                          bitOpReserved13             : 2;
    VOS_UINT32                          bitOpReserved14             : 2;
    VOS_UINT32                          bitOpReserved15             : 2;
    VOS_UINT32                          bitOpReserved16             : 2;
    VOS_UINT32                          bitOpReserved17             : 2;
    VOS_UINT32                          bitOpReserved18             : 2;
    VOS_UINT32                          bitOpReserved19             : 2;
    VOS_UINT32                          bitOpReserved20             : 2;
    VOS_UINT32                          bitOpReserved21             : 2;
    VOS_UINT32                          bitOpReserved22             : 2;
    VOS_UINT32                          bitOpReserved23             : 2;
    VOS_UINT32                          bitOpReserved24             : 2;
    VOS_UINT32                          bitOpReserved25             : 2;
    VOS_UINT32                          bitOpReserved26             : 2;
    VOS_UINT32                          bitOpReserved27             : 2;
    VOS_UINT32                          bitOpReserved28             : 2;
}TAF_MTA_NVIM_CPOS_PROTOCOL_VERSION_CFG_STRU;
/* Added by c00380008 for AGPSR12R13, 2016-10-14, end */

/*****************************************************************************
     : TAF_NVIM_READ_BACKOFF_FILE_CFG_STRU
   : BACKOFF
 1.       : 20161018
          : w00316404
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucReadBackoffFileConfig;                /* 1:BACKOFF0:0NV2379 */
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
}TAF_NVIM_READ_BACKOFF_FILE_CFG_STRU;

/*****************************************************************************
     : TAF_NVIM_OOS_CHR_POWER_SAVA_CFG_STRU
   : en_NV_Item_Oos_Chr_Cfg NV
 1.        : 20161028
           : g00322017
       : 
 2.        : 20161128
           : m00312079
       : CL
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
    VOS_UINT32                          ulReserved3;                       /*  */
    VOS_UINT32                          ulReserved4;                       /*  */
}TAF_NVIM_OOS_CHR_POWER_SAVE_CFG_STRU;

/*****************************************************************************
     : TAF_NVIM_CDMAMODEMSWITCH_NOT_RESET_CFG_STRU
   : CDMAMODEMSWITCHNV

 1.       : 20161026
          : h00313353
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEnableFlg;                            /* CDMAMODEMSWITCHNV, 1: 0 */
    VOS_UINT8                           aucReversed[7];                         /*  */
} TAF_NVIM_CDMAMODEMSWITCH_NOT_RESET_CFG_STRU;

/*****************************************************************************
     : TAF_NVIM_SID_RANGE_AND_MCC_INFO_STRU
   :  SID  MMC
1.       : 20161126
         : l00359089
     : MCC
*****************************************************************************/
typedef struct
{
    VOS_UINT16                         usSidRangeStart;                                      /*SID  */
    VOS_UINT16                         usSidRangeEnd;                                        /*SID  */
    VOS_UINT32                         ulMcc;                                                /*mobile country code */
}TAF_NVIM_SID_RANGE_AND_MCC_INFO_STRU;

/*****************************************************************************
     : TAF_NVIM_CHINA_HOME_SID_RANGE_AND_MCC_INFO_STRU
   : SID MCC
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
    TAF_NVIM_SID_RANGE_AND_MCC_INFO_STRU                    astSidRangeMccInfo[TAF_NVIM_CHINA_HOME_NETWORK_NUM_MAX];
}TAF_NVIM_CHINA_HOME_SID_RANGE_AND_MCC_INFO_STRU;

/*****************************************************************************
     : TAF_NVIM_SPM_IMSCALL_TO_CSREDIAL_CUSTOM_CFG_STRU
   : IMSCS
  1.       : 20161212
           : m00217266
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucHangupImsCallInCsRedialCfg;          /* ims */

    VOS_UINT8                           ucRedialImsToCsHifiStartedSupportFlg;  /* HIFICS */
    VOS_UINT8                           ucImsEmcFirstTryFlgVolteOff;
    VOS_UINT8                           ucReserv1;
    VOS_UINT8                           ucReserv2;
    VOS_UINT8                           ucReserv3;

    VOS_UINT8                           ucReserv4;
    VOS_UINT8                           ucReserv5;
}TAF_NVIM_SPM_IMSCALL_TO_CSREDIAL_CUSTOM_CFG_STRU;

/*****************************************************************************
     : TAF_NVIM_MATCH_REGISTER_APN_CFG_STRU
   : APNLTEAPN
 1.       : 20161224
          : w00316404
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucMatchRegApnConfig;                    /* 1:APNLTEAPN0: */
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
}TAF_NVIM_MATCH_REGISTER_APN_CFG_STRU;
/*****************************************************************************
     : TAF_NVIM_LIMITED_SERVICE_STATUS_REPORT_CFG_STRU
   : en_NV_Item_Limited_Service_Status_Report_cfg
            CS,PS
  1.       : 20161229
           : f00367319
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucLimitedServiceReportFlg;                  /* NV */
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
}TAF_NVIM_LIMITED_SERVICE_STATUS_REPORT_CFG_STRU;

/*****************************************************************************
     : TAF_NVIM_DSDS_CTRL_CFG_STRU
   : DSDSNV
  1.       : 20170208
           : c00299063
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucModemCtrlFlg;                  /* DSDSModem */
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
}TAF_NVIM_DSDS_CTRL_CFG_STRU;


/*****************************************************************************
     : TAF_NVIM_ALERTING_SRVCC_OPEN_CODEC_CFG_STRU
   : Alerting SrvccCodec NV
  1.       : 20170328
           : n00269697
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucAlertingSrvccOpenCodecFlag;           /* Alerting SrvccCodec */
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
}TAF_NVIM_ALERTING_SRVCC_OPEN_CODEC_CFG_STRU;

/*****************************************************************************
   : TAF_NVIM_DEACT_EMC_PDN_POLICY_STRU
   : PDNGU

  1.       : 20170203
           : W00316404
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucAllowDeactEmcPdnFlg;
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
} TAF_NVIM_DEACT_EMC_PDN_POLICY_STRU;

/*****************************************************************************
     : nv_wifi_info
   : nv_wifi_info
*****************************************************************************/
typedef struct
{
    VOS_UINT32 ulOpSupport;
    VOS_UINT8  usbHighChannel;
    VOS_UINT8  usbLowChannel;
    VOS_UINT8  aucRsv1[2];
    VOS_UINT16 ausbPower[2];
    VOS_UINT8  usgHighsChannel;
    VOS_UINT8  usgLowChannel;
    VOS_UINT8  aucRsv2[2];
    VOS_UINT16 ausgPower[2];
    VOS_UINT8  usnHighsChannel;
    VOS_UINT8  usnLowChannel;
    VOS_UINT8  ausnRsv3[2];
    VOS_UINT16 ausnPower[2];
}nv_wifi_info;

/*****************************************************************************
     : USB_ENUM_STATUS_STRU
   : USB_ENUM_STATUS
*****************************************************************************/
typedef struct
{
    VOS_UINT32    status;
    VOS_UINT32    value;
    VOS_UINT32    reserve1;
    VOS_UINT32    reserve2;
}USB_ENUM_STATUS_STRU;

/*****************************************************************************
     : VBAT_CALIBART_TYPE
   : 
*****************************************************************************/
typedef struct
{
    VOS_UINT16 min_value;
    VOS_UINT16 max_value;
}VBAT_CALIBART_TYPE;

/*****************************************************************************
     : TAF_NV_SS_IMS2CS_REDIAL_CFG_STRU
   : TAF_NV_SS_IMS_TO_CS_REDIAL_CFG_STRU
  1.       : 2017630
           : f00317170
       : USSD Ims2Cs Redial
                 ucIms2CsRedialCauseNum: 
                 ausIms2CsRedialCause:   
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucIms2CsRedialCauseNum;
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
    VOS_UINT16                          ausIms2CsRedialCause[TAF_NV_SSA_IMS2CS_REDIAL_CAUSE_MAX_NUM];
}TAF_NV_SS_IMS2CS_REDIAL_CFG_STRU;

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of NasNvInterface.h */
