/******************************************************************************

  Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : LPSCommon.h
  Description     : LPSCommon.h header file
  History         :
      1.XiaoJun 58160       2008-11-5   Draft Enact
      2.xiaoJun 58160       2009-05-19  BJ9D00823 enum PS_MSG_ID_SECTION_ENUM
                   IDPS_AIR_MSG_ID_BASE
      3.xiaojun 58160       2009-05-19  BJ9D00828  AppMmInterface.h
                               OmCommon.h
                               
      4.xiaojun 58160       2009-06-05  BJ9D01038  L2 OM, OM
                               
	  5.wangyue 00151278    2011-07-15 DTS2011062801783: KDF
******************************************************************************/

#ifndef __LPSCOMMON_H__
#define __LPSCOMMON_H__

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include  "vos.h"

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

/* Msg ID4:
-----------------------------------------------------------------
                                        
-----------------------------------------------------------------
| BYTE1  |  BYTE2    |   BYTE3    |    BYTE4   |
-----------------------------------------------------------------
BYTE1 :
                UE_MSG_TYPE

BYTE2 :
                 UE_FUNC_MODULE_ID_ENUM  UE_APP_MODULE_ID_ENUM


BYTE3 :
                BYTE2

BYTE4  :0~255
*/


/* ID:   enMsgType UE_MSG_TYPE;
   enSrcModuleId  enDestModuleIdUE_FUNC_MODULE_ID_ENUM  UE_APP_MODULE_ID_ENUM;*/
#define  DEF_MSG(enMsgType, enSrcModuleId, enDestModuleId, ucNum) \
            (((0xff&enMsgType)<<24)|((0xff&enSrcModuleId)<<16)|((0xff& enDestModuleId)<<8)|ucNum)

/* 32BITulMsgId*/
#define GET_MSG_TYPE(ulMsgId)           (((ulMsgId) & 0xff000000 ) >> 24)

/* 32BITulMsgIdID*/
#define GET_SRC_MODULE_ID(ulMsgId)      (((ulMsgId) & 0x00ff0000 ) >> 16)

/* 32BITulMsgIdID*/
#define GET_DST_MODULE_ID(ulMsgId)      (((ulMsgId) & 0x0000ff00 ) >> 8)

/* 32BITulMsgId8*/
#define GET_MSG_INDEX(ulMsgId)          ((ulMsgId) & 0x000000ff )



/* APP */
#define APP_OM_HEADER_LEN               12

/*ID*/
#define MSG_ID_LENGTH                   4


/*APP*/
#define APP_MSG_HEADER                  VOS_UINT16   usOriginalId;\
                                        VOS_UINT16   usTerminalId;\
                                        VOS_UINT32   ulTimeStamp; \
                                        VOS_UINT32   ulSN;

#define PS_MSG_ID_BASE                  0x0500
#define PS_MSG_ID_END                   0x2000

/* RRCID0x8D00-0x8DFF */
#define PS_DT_MSG_ID_BASE                  0x8D00

/* Modem errlog report, relation event lps-om message base address begin */
#define PS_ERR_LOG_MSG_ID_BASE             0x8E00
/* Modem errlog report, relation event lps-om message base address end */

/* boston add begin */

#if defined(INSTANCE_1)
#define LPS_MODEM_ID                MODEM_ID_1
#else
#define LPS_MODEM_ID                MODEM_ID_0
#endif

#if (FEATURE_ON == FEATURE_MODEM1_SUPPORT_LTE)
#define LPS_MAX_MODEM_NUM                2
#else
#define LPS_MAX_MODEM_NUM                1
#endif
/* boston add end */

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

#define UE_INVALID_MODULE_ID            0xff  /*ID*/



/*****************************************************************************
  4 Enum
*****************************************************************************/
/*****************************************************************************
     : LTE_SECU_KEY_INDEX_ENUM
   :
*****************************************************************************/
enum LTE_SECU_KEY_INDEX_ENUM
{
    /* LTEmodem0 */
    I0_LTE_SECU_NAS_INTEGRITY_KEY_INDEX                           = 0,
    I0_LTE_SECU_NAS_CIPHER_KEY_INDEX                              = 1,
    I0_LTE_SECU_PDCP_UP_CIPHER_KEY_INDEX                          = 2,
    I0_LTE_SECU_RRC_INTEGRITY_KEY_INDEX                           = 3,
    I0_LTE_SECU_RRC_CIPHER_KEY_INDEX                              = 4,
    I0_LTE_SECU_LASTEST_PDCP_UP_CIPHER_KEY_INDEX                  = 5,
    I0_LTE_SECU_LRRC_KDF_OUTPUT_INDEX                             = 6,
    I0_LTE_SECU_LMM_KDF_OUTPUT_INDEX                              = 7,

    /* LTEmodem1 */
    I1_LTE_SECU_NAS_INTEGRITY_KEY_INDEX                           = 8,
    I1_LTE_SECU_NAS_CIPHER_KEY_INDEX                              = 9,
    I1_LTE_SECU_PDCP_UP_CIPHER_KEY_INDEX                          = 10,
    I1_LTE_SECU_RRC_INTEGRITY_KEY_INDEX                           = 11,
    I1_LTE_SECU_RRC_CIPHER_KEY_INDEX                              = 12,
    I1_LTE_SECU_LASTEST_PDCP_UP_CIPHER_KEY_INDEX                  = 13,
    I1_LTE_SECU_LRRC_KDF_OUTPUT_INDEX                             = 14,
    I1_LTE_SECU_LMM_KDF_OUTPUT_INDEX                              = 15,

    /* modem0 DC support */
    I0_LTE_SECU_SCG_PDCP_UP_CIPHER_KEY_INDEX                      = 16,
    I0_LTE_SECU_SCG_LASTEST_PDCP_UP_CIPHER_KEY_INDEX              = 17,
    I0_LTE_SECU_SCG_LRRC_KDF_OUTPUT_INDEX                         = 18,

    /* modem1 DC support */
    I1_LTE_SECU_SCG_PDCP_UP_CIPHER_KEY_INDEX                      = 19,
    I1_LTE_SECU_SCG_LASTEST_PDCP_UP_CIPHER_KEY_INDEX              = 20,
    I1_LTE_SECU_SCG_LRRC_KDF_OUTPUT_INDEX                         = 21,

    LTE_SECU_KEY_BUTT

};
typedef VOS_UINT32 LTE_SECU_KEY_INDEX_ENUM_UINT32;

/*****************************************************************************
     : LPS_SECU_KEY_INDEX_ENUM
   :
*****************************************************************************/
enum LPS_SECU_KEY_INDEX_ENUM
{
#if defined(INSTANCE_1)
    /* LTEmodem1 */
    LTE_SECU_NAS_INTEGRITY_KEY_INDEX                        = I1_LTE_SECU_NAS_INTEGRITY_KEY_INDEX,
    LTE_SECU_NAS_CIPHER_KEY_INDEX                           = I1_LTE_SECU_NAS_CIPHER_KEY_INDEX,
    LTE_SECU_PDCP_UP_CIPHER_KEY_INDEX                       = I1_LTE_SECU_PDCP_UP_CIPHER_KEY_INDEX,
    LTE_SECU_RRC_INTEGRITY_KEY_INDEX                        = I1_LTE_SECU_RRC_INTEGRITY_KEY_INDEX,
    LTE_SECU_RRC_CIPHER_KEY_INDEX                           = I1_LTE_SECU_RRC_CIPHER_KEY_INDEX,
    LTE_SECU_LASTEST_PDCP_UP_CIPHER_KEY_INDEX               = I1_LTE_SECU_LASTEST_PDCP_UP_CIPHER_KEY_INDEX,
    LTE_SECU_LRRC_KDF_OUTPUT_INDEX                          = I1_LTE_SECU_LRRC_KDF_OUTPUT_INDEX,
    LTE_SECU_LMM_KDF_OUTPUT_INDEX                           = I1_LTE_SECU_LMM_KDF_OUTPUT_INDEX,
    /* DC support */
    LTE_SECU_SCG_PDCP_UP_CIPHER_KEY_INDEX                   = I1_LTE_SECU_SCG_PDCP_UP_CIPHER_KEY_INDEX,
    LTE_SECU_SCG_LASTEST_PDCP_UP_CIPHER_KEY_INDEX           = I1_LTE_SECU_SCG_LASTEST_PDCP_UP_CIPHER_KEY_INDEX,
    LTE_SECU_SCG_LRRC_KDF_OUTPUT_INDEX                      = I1_LTE_SECU_SCG_LRRC_KDF_OUTPUT_INDEX,
#else
    /* LTEmodem0 */
    LTE_SECU_NAS_INTEGRITY_KEY_INDEX                        = I0_LTE_SECU_NAS_INTEGRITY_KEY_INDEX,
    LTE_SECU_NAS_CIPHER_KEY_INDEX                           = I0_LTE_SECU_NAS_CIPHER_KEY_INDEX,
    LTE_SECU_PDCP_UP_CIPHER_KEY_INDEX                       = I0_LTE_SECU_PDCP_UP_CIPHER_KEY_INDEX,
    LTE_SECU_RRC_INTEGRITY_KEY_INDEX                        = I0_LTE_SECU_RRC_INTEGRITY_KEY_INDEX,
    LTE_SECU_RRC_CIPHER_KEY_INDEX                           = I0_LTE_SECU_RRC_CIPHER_KEY_INDEX,
    LTE_SECU_LASTEST_PDCP_UP_CIPHER_KEY_INDEX               = I0_LTE_SECU_LASTEST_PDCP_UP_CIPHER_KEY_INDEX,
    LTE_SECU_LRRC_KDF_OUTPUT_INDEX                          = I0_LTE_SECU_LRRC_KDF_OUTPUT_INDEX,
    LTE_SECU_LMM_KDF_OUTPUT_INDEX                           = I0_LTE_SECU_LMM_KDF_OUTPUT_INDEX,
    /* DC support */
    LTE_SECU_SCG_PDCP_UP_CIPHER_KEY_INDEX                   = I0_LTE_SECU_SCG_PDCP_UP_CIPHER_KEY_INDEX,
    LTE_SECU_SCG_LASTEST_PDCP_UP_CIPHER_KEY_INDEX           = I0_LTE_SECU_SCG_LASTEST_PDCP_UP_CIPHER_KEY_INDEX,
    LTE_SECU_SCG_LRRC_KDF_OUTPUT_INDEX                      = I0_LTE_SECU_SCG_LRRC_KDF_OUTPUT_INDEX,
#endif
    LTE_SECU_KEY_INDEX_BUTT
};
typedef VOS_UINT32 LPS_SECU_KEY_INDEX_ENUM_UINT32;

/*****************************************************************************
     : PS_MSG_ID_SECTION_ENUM
   : ID:
             1(RRC/NAS/L2)
             
             (0);
             2
             3PCID
             
*****************************************************************************/
enum PS_MSG_ID_SECTION_ENUM
{
    /* NASRRC */
    PS_MSG_ID_NAS_TO_RRC_BASE   = PS_MSG_ID_BASE,                       /*NASRRCID*/

    PS_MSG_ID_RRC_TO_NAS_BASE   = PS_MSG_ID_NAS_TO_RRC_BASE + 0x80,     /*RRCNASID*/

    /* L2RRC */
    PS_MSG_ID_RRC_TO_MAC_BASE   = PS_MSG_ID_RRC_TO_NAS_BASE + 0x80,     /*RRCMACID*/
    PS_MSG_ID_MAC_TO_RRC_BASE   = PS_MSG_ID_RRC_TO_MAC_BASE + 0x80,     /*MACRRCID*/

    PS_MSG_ID_RRC_TO_RLC_BASE   = PS_MSG_ID_MAC_TO_RRC_BASE + 0x80,
    PS_MSG_ID_RLC_TO_RRC_BASE   = PS_MSG_ID_RRC_TO_RLC_BASE + 0x80,

    PS_MSG_ID_RRC_TO_PDCP_BASE  = PS_MSG_ID_RLC_TO_RRC_BASE + 0x80,
    PS_MSG_ID_PDCP_TO_RRC_BASE  = PS_MSG_ID_RRC_TO_PDCP_BASE + 0x80,

    /*RRCPHY */
    PS_MSG_ID_ERRC_TO_PHY_BASE  = PS_MSG_ID_PDCP_TO_RRC_BASE + 0x40,
    PS_MSG_ID_PHY_TO_ERRC_BASE  = PS_MSG_ID_ERRC_TO_PHY_BASE + 0x40,

    PS_MSG_ID_ERMM_TO_PHY_BASE  = PS_MSG_ID_PHY_TO_ERRC_BASE + 0x40,
    PS_MSG_ID_PHY_TO_ERMM_BASE  = PS_MSG_ID_ERMM_TO_PHY_BASE + 0x40,

    /*L2PHY */
    PS_MSG_ID_UL_MAC_TO_PHY_BASE = PS_MSG_ID_PHY_TO_ERMM_BASE + 0x40,
    PS_MSG_ID_PHY_TO_UL_MAC_BASE = PS_MSG_ID_UL_MAC_TO_PHY_BASE + 0x40,

    PS_MSG_ID_DL_MAC_TO_PHY_BASE = PS_MSG_ID_PHY_TO_UL_MAC_BASE + 0x40,
    PS_MSG_ID_PHY_TO_DL_MAC_BASE = PS_MSG_ID_DL_MAC_TO_PHY_BASE + 0x40,

    /*NASAPP */
    PS_MSG_ID_EMM_TO_APP_BASE   = PS_MSG_ID_PHY_TO_DL_MAC_BASE + 0x80,
    PS_MSG_ID_APP_TO_EMM_BASE   = PS_MSG_ID_EMM_TO_APP_BASE + 0x80,

    PS_MSG_ID_ESM_TO_APP_BASE   = PS_MSG_ID_APP_TO_EMM_BASE+ 0x80,
    PS_MSG_ID_APP_TO_ESM_BASE   = PS_MSG_ID_ESM_TO_APP_BASE+ 0x80,

    /*RRCAPP */
    PS_MSG_ID_RRC_TO_APP_BASE   = PS_MSG_ID_APP_TO_ESM_BASE + 0x80,
    PS_MSG_ID_APP_TO_RRC_BASE   = PS_MSG_ID_RRC_TO_APP_BASE + 0x80,

    /*L2APP */
    PS_MSG_ID_L2_TO_APP_BASE    = PS_MSG_ID_APP_TO_RRC_BASE + 0x80,
    PS_MSG_ID_APP_TO_L2_BASE    = PS_MSG_ID_L2_TO_APP_BASE + 0x10,

    /*L2 MACAPP */
    PS_MSG_ID_MAC_TO_APP_BASE    = PS_MSG_ID_APP_TO_L2_BASE + 0x10,
    PS_MSG_ID_APP_TO_MAC_BASE    = PS_MSG_ID_MAC_TO_APP_BASE + 0x30,

    /*L2 RLCAPP */
    PS_MSG_ID_RLC_TO_APP_BASE    = PS_MSG_ID_APP_TO_MAC_BASE + 0x30,
    PS_MSG_ID_APP_TO_RLC_BASE    = PS_MSG_ID_RLC_TO_APP_BASE + 0x20,


    /*L2 PDCPAPP */
    PS_MSG_ID_PDCP_TO_APP_BASE    = PS_MSG_ID_APP_TO_RLC_BASE + 0x20,
    PS_MSG_ID_APP_TO_PDCP_BASE    = PS_MSG_ID_PDCP_TO_APP_BASE + 0x20,


    /*NAS */
    PS_MSG_ID_EMM_TO_ESM_BASE   = PS_MSG_ID_APP_TO_PDCP_BASE + 0x20,
    PS_MSG_ID_ESM_TO_EMM_BASE   = PS_MSG_ID_EMM_TO_ESM_BASE + 0x20,

    PS_MSG_ID_ESM_TO_RABM_BASE  = PS_MSG_ID_ESM_TO_EMM_BASE + 0x20,
    PS_MSG_ID_RABM_TO_ESM_BASE  = PS_MSG_ID_ESM_TO_RABM_BASE + 0x20,

    PS_MSG_ID_RABM_TO_EMM_BASE  = PS_MSG_ID_RABM_TO_ESM_BASE + 0x20,
    PS_MSG_ID_EMM_TO_RABM_BASE  = PS_MSG_ID_RABM_TO_EMM_BASE + 0x20,

    PS_MSG_ID_AIR_BASE           = PS_MSG_ID_EMM_TO_RABM_BASE + 0x20,

    /*NASPDCP*/
    PS_MSG_ID_LTC_TO_LPDCP_BASE    = PS_MSG_ID_AIR_BASE + 0xA0,
    PS_MSG_ID_LPDCP_TO_LTC_BASE    = PS_MSG_ID_LTC_TO_LPDCP_BASE + 0x08,

    /* TCEMM */
    PS_MSG_ID_TC_TO_EMM_BASE    = PS_MSG_ID_LPDCP_TO_LTC_BASE + 0x08,
    PS_MSG_ID_EMM_TO_TC_BASE    = PS_MSG_ID_TC_TO_EMM_BASE + 0x08,

    /* TCRABM */
    PS_MSG_ID_TC_TO_RABM_BASE    = PS_MSG_ID_EMM_TO_TC_BASE + 0x08,
    PS_MSG_ID_RABM_TO_TC_BASE    = PS_MSG_ID_TC_TO_RABM_BASE + 0x08,

    /* NASIP */
    PS_MSG_ID_NAS_TO_IP_BASE     = PS_MSG_ID_RABM_TO_TC_BASE + 0x08,
    PS_MSG_ID_IP_TO_NAS_BASE     = PS_MSG_ID_NAS_TO_IP_BASE + 0x10,

    /* MMCLMM */
    PS_MSG_ID_LMM_TO_MMC_BASE    = PS_MSG_ID_IP_TO_NAS_BASE + 0x10,
    PS_MSG_ID_MMC_TO_LMM_BASE    = PS_MSG_ID_LMM_TO_MMC_BASE + 0x80,

    /* ESMSM */
    PS_MSG_ID_SM_TO_ESM_BASE     = PS_MSG_ID_MMC_TO_LMM_BASE + 0x80,
    PS_MSG_ID_ESM_TO_SM_BASE     = PS_MSG_ID_SM_TO_ESM_BASE + 0x10,

    /* LMMGMM */
    PS_MSG_ID_LMM_TO_GMM_BASE    = PS_MSG_ID_ESM_TO_SM_BASE + 0x10,
    PS_MSG_ID_GMM_TO_LMM_BASE    = PS_MSG_ID_LMM_TO_GMM_BASE + 0x20,

    /* LRRCWRRC */
    PS_MSG_ID_LRRC_TO_WRRC_BASE  = PS_MSG_ID_GMM_TO_LMM_BASE + 0x40,
    PS_MSG_ID_WRRC_TO_LRRC_BASE  = PS_MSG_ID_LRRC_TO_WRRC_BASE + 0x40,

    /* LRRCGRR */
    PS_MSG_ID_LRRC_TO_GRR_BASE   = PS_MSG_ID_WRRC_TO_LRRC_BASE + 0x40,
    PS_MSG_ID_GRR_TO_LRRC_BASE   = PS_MSG_ID_LRRC_TO_GRR_BASE + 0x40,
    /* PSLHPA */
    PS_MSG_ID_LHPA_TO_RRC_BASE     = PS_MSG_ID_GRR_TO_LRRC_BASE + 0x05,

    /* PS OMAPP*/
    PS_MSG_ID_PS_TO_APP_BASE    = PS_MSG_ID_LHPA_TO_RRC_BASE + 0x20,  /*0x1315*/
    PS_MSG_ID_APP_TO_PS_BASE    = PS_MSG_ID_PS_TO_APP_BASE + 0x20,    /*0x1335*/

    /* TDS begin */
    PS_MSG_ID_TDS_PS_BASE    = PS_MSG_ID_APP_TO_PS_BASE + 0x20,
    PS_MSG_ID_TDS_AIR_BASE   = PS_MSG_ID_TDS_PS_BASE + 0x500,
    PS_MSG_ID_TRRC_TO_GRR_BASE = PS_MSG_ID_TDS_AIR_BASE + 0x20,
    PS_MSG_ID_GRR_TO_TRRC_BASE = PS_MSG_ID_TRRC_TO_GRR_BASE + 0x20,

    /* LRRCTRRC */
    PS_MSG_ID_LRRC_TO_TRRC_BASE  = PS_MSG_ID_GRR_TO_TRRC_BASE + 0x100,
    PS_MSG_ID_TRRC_TO_LRRC_BASE  = PS_MSG_ID_LRRC_TO_TRRC_BASE + 0x40,
    /* TDS end */

    PS_MSG_ID_SMS_TO_LMM_BASE   = PS_MSG_ID_TRRC_TO_LRRC_BASE  + 0xa0,
    PS_MSG_ID_LMM_TO_SMS_BASE   = PS_MSG_ID_SMS_TO_LMM_BASE  + 0x20,

    /*CDSERABM*/
    PS_MSG_ID_CDS_TO_ERABM_BASE = PS_MSG_ID_LMM_TO_SMS_BASE  + 0x20,
    PS_MSG_ID_ERABM_TO_CDS_BASE = PS_MSG_ID_CDS_TO_ERABM_BASE+ 0x20,

    /*CDSETC*/
    PS_MSG_ID_CDS_TO_ETC_BASE   = PS_MSG_ID_ERABM_TO_CDS_BASE + 0x20,
    PS_MSG_ID_ETC_TO_CDS_BASE   = PS_MSG_ID_CDS_TO_ETC_BASE   + 0x20,

    /*CDSNDClient*/
    PS_MSG_ID_CDS_TO_NDCLIENT_BASE = PS_MSG_ID_ETC_TO_CDS_BASE + 0x20,
    PS_MSG_ID_NDCLIENT_TO_CDS_BASE = PS_MSG_ID_CDS_TO_NDCLIENT_BASE + 0x20,

    PS_MSG_ID_APS_TO_ND_BASE = PS_MSG_ID_NDCLIENT_TO_CDS_BASE + 0x20,
    PS_MSG_ID_ND_TO_APS_BASE = PS_MSG_ID_APS_TO_ND_BASE + 0x20,     /* 0x1B95 */

    PS_MSG_ID_MM_TO_LMM_BASE    = PS_MSG_ID_ND_TO_APS_BASE + 0x20,
    PS_MSG_ID_LMM_TO_MM_BASE    = PS_MSG_ID_MM_TO_LMM_BASE  + 0x20,

     /* LRRCTRRC */
    PS_MSG_ID_APP_TO_TRRC_BASE  = PS_MSG_ID_LMM_TO_MM_BASE + 0x20,
    PS_MSG_ID_TRRC_TO_APP_BASE  = PS_MSG_ID_APP_TO_TRRC_BASE + 0x20,

    /* LRRCTRRC */
    PS_MSG_ID_APP_TO_TDSL2_BASE  = PS_MSG_ID_TRRC_TO_APP_BASE + 0x20,
    PS_MSG_ID_TDSL2_TO_APP_BASE  = PS_MSG_ID_APP_TO_TDSL2_BASE + 0x20,
    /**/

    PS_MSG_ID_EMM_TO_EMM_OM_BASE  = PS_MSG_ID_TDSL2_TO_APP_BASE + 0x20,
    PS_MSG_ID_ESM_TO_ESM_OM_BASE  = PS_MSG_ID_EMM_TO_EMM_OM_BASE + 0x60,
    PS_MSG_ID_ERABM_TO_ERABM_OM_BASE= PS_MSG_ID_ESM_TO_ESM_OM_BASE + 0x20,

    /*DTS2013022506993  BEGIN*/
    TRRC_DEBUG_MSG_BASE = PS_MSG_ID_ERABM_TO_ERABM_OM_BASE+0x20 ,   /*0x1d15*/
    /*DTS2013022506993  END*/

    PS_MSG_ID_LNAS_TO_OM_BASE       = TRRC_DEBUG_MSG_BASE + 0x20,

    PS_MSG_ID_OM_TO_EMM_BASE       = PS_MSG_ID_LNAS_TO_OM_BASE + 0x20,
    PS_MSG_ID_EMM_TO_OM_BASE       = PS_MSG_ID_OM_TO_EMM_BASE + 0x20,

    PS_MSG_ID_OM_TO_ESM_BASE       = PS_MSG_ID_EMM_TO_OM_BASE + 0x20,
    PS_MSG_ID_ESM_TO_OM_BASE       = PS_MSG_ID_OM_TO_ESM_BASE + 0x20,

    PS_MSG_ID_IMSA_TO_IMSA_OM_BASE  = PS_MSG_ID_ESM_TO_OM_BASE + 0x20,

    PS_MSG_ID_DSDS_DEBUG_BASE  = PS_MSG_ID_IMSA_TO_IMSA_OM_BASE + 0x80,/*0x1e55*/

    PS_MSG_ID_IMSA_TO_ERRC_BASE = PS_MSG_ID_DSDS_DEBUG_BASE + 0x20,
    PS_MSG_ID_LPHY_TO_CSS_BASE  = PS_MSG_ID_IMSA_TO_ERRC_BASE + 0x20, /* 0x1e95 */
    /* KPI */
    PS_MSG_ID_TL_KPI_BASE       = PS_MSG_ID_LPHY_TO_CSS_BASE + 0x20,
    PS_MSG_ID_TL_PTL_BASE       = PS_MSG_ID_TL_KPI_BASE + 0x100,

    PS_MSG_ID_TL_DBG_BASE       = PS_MSG_ID_TL_PTL_BASE + 0x200,
    PS_MSG_ID_TL_DT_BASE        = PS_MSG_ID_TL_DBG_BASE + 0x200,

    /*CDSDhcp*/
    PS_MSG_ID_DHCP_TO_CDS_BASE = PS_MSG_ID_TL_DT_BASE + 0x100,
    PS_MSG_ID_CDS_TO_DHCP_BASE = PS_MSG_ID_DHCP_TO_CDS_BASE + 0x20,
    /* ... ... */

    /* LPPLRRC */
    PS_MSG_ID_LPP_TO_LRRC_BASE = PS_MSG_ID_CDS_TO_DHCP_BASE + 0x20,
    PS_MSG_ID_LRRC_TO_LPP_BASE = PS_MSG_ID_LPP_TO_LRRC_BASE + 0X20,

    /* EMMIMSABASE */
    PS_MSG_ID_EMM_TO_IMSA_BASE = PS_MSG_ID_LRRC_TO_LPP_BASE + 0x20,
    PS_MSG_ID_ERRC_TO_IMSA_BASE = PS_MSG_ID_EMM_TO_IMSA_BASE + 0x20,

    /*L2IMSA*/
    PS_MSG_ID_L2_TO_IMSA_BASE = PS_MSG_ID_ERRC_TO_IMSA_BASE + 0x20,
    
    /* zhangdongfeng, 00353461 , add it for cellular prefer project, begin in 2016-09-28 */
    /* IMSACAS */
    PS_MSG_ID_IMSA_TO_CAS_BASE   = PS_MSG_ID_L2_TO_IMSA_BASE + 0x20, /* 0x2525 */
    PS_MSG_ID_CAS_TO_IMSA_BASE   = PS_MSG_ID_IMSA_TO_CAS_BASE + 0x20,

    /* IMSAWRR */
    PS_MSG_ID_IMSA_TO_WRR_BASE   = PS_MSG_ID_CAS_TO_IMSA_BASE + 0x20,
    PS_MSG_ID_WRR_TO_IMSA_BASE   = PS_MSG_ID_IMSA_TO_WRR_BASE + 0x20,

    /* IMSAGRR */
    PS_MSG_ID_IMSA_TO_GRR_BASE   = PS_MSG_ID_WRR_TO_IMSA_BASE + 0x20,
    PS_MSG_ID_GRR_TO_IMSA_BASE   = PS_MSG_ID_IMSA_TO_GRR_BASE + 0x20,
    /* zhangdongfeng, 00353461 , add it for cellular prefer project, end in 2016-09-28 */
    

    /* RRCID0x8D00-0x8DFF */
    PS_MSG_ID_RRC_TO_DT_BASE  = PS_DT_MSG_ID_BASE,

    /* Modem errlog report, relation event lps-om message base address begin */
    PS_MSG_ID_LPSOM_PS_BASE   = PS_ERR_LOG_MSG_ID_BASE,

};
/*****************************************************************************
     : TL_KPI_MSG_ID_SECTION_ENUM
   : KPI
 1.       : 201563
          : leixiantiao 00258641
      : 
*****************************************************************************/
enum TL_KPI_MSG_ID_SECTION_ENUM
{
    TL_KPI_MSG_ID_LTE_NAS_BASE = PS_MSG_ID_TL_KPI_BASE,
    TL_KPI_MSG_ID_LTE_RRC_BASE = TL_KPI_MSG_ID_LTE_NAS_BASE + 0x40,
    TL_KPI_MSG_ID_TDS_RRC_BASE = TL_KPI_MSG_ID_LTE_RRC_BASE + 0x40,
    TL_KPI_MSG_ID_LTE_L2_BASE  = TL_KPI_MSG_ID_TDS_RRC_BASE + 0x40,
    TL_KPI_MSG_ID_TDS_L2_BASE  = TL_KPI_MSG_ID_LTE_L2_BASE  + 0x20,
    TL_KPI_MSG_ID_BUTT
};

/*****************************************************************************
     : TL_DBG_MSG_ID_SECTION_ENUM
   : DEBUG
 1.       : 2015828
          : leixiantiao 00258641
      : 
*****************************************************************************/
enum TL_DBG_MSG_ID_SECTION_ENUM
{
    TL_DBG_MSG_ID_LTE_NAS_BASE = PS_MSG_ID_TL_DBG_BASE,
    TL_DBG_MSG_ID_LTE_RRC_BASE = TL_DBG_MSG_ID_LTE_NAS_BASE + 0x40,
    TL_DBG_MSG_ID_TDS_RRC_BASE = TL_DBG_MSG_ID_LTE_RRC_BASE + 0x40,
    TL_DBG_MSG_ID_LTE_L2_BASE  = TL_DBG_MSG_ID_TDS_RRC_BASE + 0x40,
    TL_DBG_MSG_ID_TDS_L2_BASE  = TL_DBG_MSG_ID_LTE_L2_BASE  + 0x20,
    TL_DBG_MSG_ID_BUTT
};

/*****************************************************************************
     : TL_PTL_MSG_ID_SECTION_ENUM
   : PTL
 1.       : 2015720
          : y00151394
      : 
*****************************************************************************/
enum TL_PTL_MSG_ID_SECTION_ENUM
{
    TL_PTL_MSG_ID_LTE_NAS_BASE = PS_MSG_ID_TL_PTL_BASE,
    TL_PTL_MSG_ID_LTE_RRC_BASE = TL_PTL_MSG_ID_LTE_NAS_BASE + 0x80,
    TL_PTL_MSG_ID_TDS_RRC_BASE = TL_PTL_MSG_ID_LTE_RRC_BASE + 0x80,
    TL_PTL_MSG_ID_LTE_L2_BASE  = TL_PTL_MSG_ID_TDS_RRC_BASE + 0x80,
    TL_PTL_MSG_ID_TDS_L2_BASE  = TL_PTL_MSG_ID_LTE_L2_BASE  + 0x40,
    TL_PTL_MSG_ID_BUTT
};

/*****************************************************************************
     : TL_DT_MSG_ID_SECTION_ENUM
   : DT
 1.       : 2015720
          : y00151394
      : 
*****************************************************************************/
enum TL_DT_MSG_ID_SECTION_ENUM
{
    TL_DT_MSG_ID_LTE_NAS_BASE = PS_MSG_ID_TL_DT_BASE,
    TL_DT_MSG_ID_LTE_RRC_BASE = TL_DT_MSG_ID_LTE_NAS_BASE + 0x40,
    TL_DT_MSG_ID_TDS_RRC_BASE = TL_DT_MSG_ID_LTE_RRC_BASE + 0x40,
    TL_DT_MSG_ID_LTE_L2_BASE  = TL_DT_MSG_ID_TDS_RRC_BASE + 0x40,
    TL_DT_MSG_ID_TDS_L2_BASE  = TL_DT_MSG_ID_LTE_L2_BASE  + 0x20,
    TL_DT_MSG_ID_BUTT
};


/*****************************************************************************
     : UE_MSG_TYPE_ENUM
   : 32bitmessage id
*****************************************************************************/
enum UE_MSG_TYPE_ENUM
{
    ENUM_STRATUM_MSG            = 0 ,       /*  */
    ENUM_RESERVED_MSG               ,       /*  */
    ENUM_AIR_MSG                    ,       /*  */
    ENUM_GENERAL_CMD_MSG            ,       /*  */
    ENUM_REAL_TIME_MSG              ,       /*  */
    ENUM_KEY_EVENT_MSG              ,       /*  */
    ENUM_TRANSPARENT_MSG            ,       /*  */
    ENUM_MSG_BUTT

};
typedef VOS_UINT8 UE_MSG_TYPE_ENUM_UINT8;

/*****************************************************************************
     : UE_FUNC_MODULE_ID_ENUM
   : UEID, PSID [0xF200 -- 0xF800)
*****************************************************************************/
enum UE_FUNC_MODULE_ID_ENUM
{
    UE_MODULE_PS_ID             = 0x00,     /*UEPS*/

    /*UE_MODULE_NAS_ID = 0x10,
 */
    UE_MODULE_ESM_ID            = PS_PID_ESM,
    UE_MODULE_MM_ID             = PS_PID_MM,
    UE_MODULE_RABM_ID           = PS_PID_RABM,

    /*UE_MODULE_RRC_ID = 0x40,
 */
    UE_MODULE_ERRC_ID           = PS_PID_ERRC,
    UE_MODULE_ERMM_ID           = PS_PID_ERMM,
    UE_MODULE_HPA_M_ID          = PS_PID_HPA,  /* RTTHPA */

    /*UE_MODULE_L2_ID             = 0x70,    L2 */
    /*UE_MODULE_L2_PDCP_ID      = 0x71,    PDCP */
    /*UE_MODULE_L2_RLC_ID       = 0x72     RLC */
    /*UE_MODULE_L2_MAC_ID       = 0x73     MAC */

    UE_MODULE_L2_COM_ID         = PS_PID_PDCP_UL,
    UE_MODULE_L2_PDCP_UL_ID     = PS_PID_PDCP_UL,
    UE_MODULE_L2_PDCP_DL_ID     = PS_PID_PDCP_DL,
    UE_MODULE_L2_RLC_UL_ID      = PS_PID_RLC_UL,
    UE_MODULE_L2_RLC_DL_ID      = PS_PID_RLC_DL,
    UE_MODULE_L2_MAC_UL_ID      = PS_PID_MAC_UL,
    UE_MODULE_L2_MAC_DL_ID      = PS_PID_MAC_DL,
    /*UE_MODULE_HPA_S_ID          = 0x7c,   HPA */
    /*UE_MODULE_HPA_UL_ID         = 0x7d,   RTTHPA */
    /*UE_MODULE_HPA_DL_ID         = 0x7e,   RTTHPA */

    UE_MODULE_PS_OM             = PS_PID_OM,  /* PSOM */

    UE_MODULE_TC_ID             = PS_PID_TC,  /* TC */
    UE_MODULE_IP_ID             = PS_PID_IP,   /* IP */
    UE_MODULE_MMC_ID            = 0xF210,
    UE_MODULE_GMM_ID            = 0xF211,
    UE_MODULE_WAS_ID            = 0xF212,
    UE_MODULE_GAS_ID            = 0xF213,

    UE_MODULE_NDIS_UL           = 0xF214,
    UE_MODULE_NDIS_DL           = 0xF215,
    UE_MODULE_NDIS_COM          = 0xF216,

    UE_MODULE_IMSA_ID           = 0xF217,
    UE_MODULE_LPP_ID           = 0xF218,
    UE_MODULE_LCS_ID           = 0xF219,
    UE_MODULE_BACKOFF_ID       = 0xF21a
};
typedef VOS_UINT32 UE_FUNC_MODULE_ID_ENUM_UINT32;

/*****************************************************************************
     : UE_APP_MODULE_ID_ENUM
   : OMID
*****************************************************************************/
enum UE_APP_MODULE_ID_ENUM
{

    UE_APP_SUBSYS_ID            = 0xc0, /*PC  */

    UE_MODULE_OM_AGENT_ID       = 0xc1,  /* PCOM */
    UE_MODULE_OM_ID             = 0xc2,  /* OM */
    UE_MODULE_OM_SLAVE_ID       = 0xc3,  /* OM */
    UE_MODULE_OM_BBU_RFOM_ID    = 0xc4,  /* BBURFOM*/
    UE_MODULE_OM_MUX_ID         = 0xc5,  /* BBUMUX*/
    UE_MODULE_OM_RRU_RFOM_ID    = 0xc6,  /* RRURFOM */
    UE_MODULE_OM_RFDT_ID        = 0xc7,  /* RRURFDT*/

    UE_MODULE_OMT_ID            = 0xd1,  /* PCOMT */
    UE_MODULE_PROBE_ID          = 0xd2,  /* PC */
    UE_MODULE_BD_ID             = 0xd3   /* PC */


};
typedef VOS_UINT8 UE_APP_MODULE_ID_ENUM_UINT8;

/*****************************************************************************
     : LOG_SUBMOD_ID_ENUM
   : NAS
*****************************************************************************/
typedef enum
{
    LOG_SUBMOD_ID_NAS_MM_PUBM,
    LOG_SUBMOD_ID_NAS_MM_MMC,
    LOG_SUBMOD_ID_NAS_MM_EMM_ATTACH,
    LOG_SUBMOD_ID_NAS_MM_EMM_DETACH,
    LOG_SUBMOD_ID_NAS_MM_EMM_TAU,
    LOG_SUBMOD_ID_NAS_MM_EMM_SERVICE,
    LOG_SUBMOD_ID_NAS_MM_EMM_GUTI,
    LOG_SUBMOD_ID_NAS_MM_EMM_IDEN,
    LOG_SUBMOD_ID_NAS_MM_EMM_MRRC,
    LOG_SUBMOD_ID_NAS_MM_EMM_PLMN,
    LOG_SUBMOD_ID_NAS_MM_EMM_PUBU,
    LOG_SUBMOD_ID_NAS_MM_EMM_SECU,
    LOG_SUBMOD_ID_NAS_MM_BUTT
}LOG_SUBMOD_ID_ENUM;


typedef  VOS_UINT8  LOG_SUBMOD_ID_ENUM_UINT8;

/*****************************************************************************
 : LRRC_COMM_ACCESS_STRATUM_REL_ENUM
 :
 ASN.1:
 : NASMTA
           UE
*****************************************************************************/
enum LRRC_COMM_ACCESS_STRATUM_REL_ENUM
{
    LRRC_COMM_ACCESS_STRATUM_REL8                  = 0,
    LRRC_COMM_ACCESS_STRATUM_REL9                  = 1,
    LRRC_COMM_ACCESS_STRATUM_REL10                 = 2,
    LRRC_COMM_ACCESS_STRATUM_REL11                 = 3,
    LRRC_COMM_ACCESS_STRATUM_REL12                 = 4,
    LRRC_COMM_ACCESS_STRATUM_REL13                 = 5,
    LRRC_COMM_ACCESS_STRATUM_REL_SPARE2            = 6,
    LRRC_COMM_ACCESS_STRATUM_REL_SPARE1            = 7
};
typedef VOS_UINT8 LRRC_COMM_ACCESS_STRATUM_REL_ENUM_UINT8;

/*****************************************************************************
  5 STRUCT
*****************************************************************************/
/*****************************************************************************
     : LPS_32K_TIMESTAMP
   : 32KTIMESTAMP
*****************************************************************************/
typedef struct
{
    VOS_UINT32   ul32KTStampHighBit;
    VOS_UINT32   ul32KTStampLowBit;
}LPS_32K_TIMESTAMP;

typedef VOS_UINT64 LPS_32K_TSTAMP_UINT64;
typedef VOS_UINT64 LPS_MS_TSTAMP_UINT64;


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

#endif /* end of LPSCommon.h */
