/******************************************************************************

    Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : PsNvInterface.h
  Description     : PsNvInterface.h header file
  History           :
     1.Name+ID      yyyy-mm-dd  Draft Enact
     2.guojiyu 00149868   2010-02-1  BJ9D02655:NV,NV
     3.linyu   00161178   2010-02-23 BJ9D02764:
.....4.Wang Yangcai 49178 2010-03-04 BJ9D02803:
     5.Wang Yue  00151278 2010-03-09 BJ9D02817:3db
     6.Zhu Hua  00161499 2010-03-12 BJ9D02761:NV
     7.wangxingtong 00132391  2010-5-07 BJ9D02900:
     8.wangyue 00151278   2010-05-13 BJ9D02926:DRX
     9.lishangfeng 55206   2010-06-25 DTS2010062301125 :NV
     10.zhangwei 00103912 2010-07-23 DTS2010072301127: NV
     11.wangyue 00151278  2010-7-22 DTS2010072101159:DSP DRX
     12.Wang Yangcai 49178  2010-08-18 DTS2010081700724:NVRTT
     13.lihong 00150010   2010-09-01 DTS2010083103486: NVPCO
     14.wangyue 00151278 2010-09-02 DTS2010083101214:DT
     15.wangxingtong 00132391   2010-09-27 DTS2010092601206:Band64
     16.guojiyu 00149868        2010-11-08 DTS2010110302568:RRCestablishment cause24.301 Table D.1.1
     17.Wang Yangcai 49178      2010-12-15 DTS2010121403984:AFC
     18.wangxingtong 00132391   2011-1-8   DTS2010102100541:ModemUE
     19.lihong 00150010         2011-1-17  DTS2011011701778:DHCP SERVERDHCP SERVER
     20.Wang Yangcai 49178      2011-02-15 DTS2011013100231:
     21.Wang Yangcai 49178      2011-03-08 DTS2011030105833:APCDSPNV
	 22.wangyue 00151278        2011-07-15 DTS2011062801783: KDF
	 23.lihong 00150010         2011-08-18 DTS2011081804004: combined attach
	 24.lishangfeng  55206 2011-09-11 DTS2011091100356:Band
	 25.wangyue 151278       2011-11-26 DTS2011112400987: 
	 26.liujiyan 285345      2014-08-25  ADRX
	 27 shujunwei 00204251   2014-6-28 DTS2014050604888 B28 
******************************************************************************/

#ifndef __LPSNVINTERFACE_H__
#define __LPSNVINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include  "vos.h"
#include  "PsTypeDef.h"
#include  "LNvCommon.h"
#include  "RrcNvInterface.h"
#include  "LNasNvInterface.h"
#include  "msp_nvim.h"
#if (VOS_OS_VER != VOS_WIN32)
#include  "msp.h"
#endif
#pragma pack(4)

/*****************************************************************************
  2 macro
*****************************************************************************/
/* NV */
/*
ERR_MSP_NO_INITILIZATION   3              
ERR_MSP_NO_INITILIZATION   502            
ERR_MSP_NV_NOT_SUPPORT_ID  520            ID
ERR_MSP_NV_ERROR_READ      521            flash
ERR_MSP_NV_ITEM_IS_EMPTY   1100           
*/
#if (VOS_OS_VER != VOS_WIN32)
#define LPs_NvimItem_Read( ulId, pItemData, usItemDataLen ) \
        NVM_Read( ulId, (VOS_VOID *)pItemData, usItemDataLen)

/*
ERR_MSP_NO_INITILIZATION             3              
ERR_MSP_NO_INITILIZATION             502            
ERR_MSP_NV_NOT_SUPPORT_ID            520            IDID
ERR_MSP_NV_NOT_SUPPORT_LENTH         522            
ERR_MSP_NV_ERROR_WRITE               524            flash
ERR_MSP_NV_FLASH_FULL                1103           flash
ERR_MSP_NVIM_NOT_SUPPORT_WRITE       2007           
*/
#define LPs_NvimItem_Write( ulId, pItemData, usItemDataLen)\
       NVM_Write( ulId, (VOS_VOID *)pItemData, usItemDataLen)

#define LPs_NvimItem_ReadEx(ulModmeId, ulId, pItemData, usItemDataLen ) \
        NV_ReadEx(ulModmeId, ulId, (VOS_VOID *)pItemData, usItemDataLen)
#define LPs_NvimItem_WriteEx(ulModmeId, ulId, pItemData, usItemDataLen)\
       NV_WriteEx(ulModmeId, ulId, (VOS_VOID *)pItemData, usItemDataLen)
#else
#define LPs_NvimItem_Read( ulId, pItemData, usItemDataLen ) \
        NVM_Read_Stub( ulId, (VOS_VOID *)pItemData, usItemDataLen)

#define LPs_NvimItem_Write( ulId, pItemData, usItemDataLen)\
       NVM_Write_Stub( ulId, (VOS_VOID *)pItemData, usItemDataLen)

#define LPs_NvimItem_ReadEx(ulModmeId, ulId, pItemData, usItemDataLen ) \
        NVM_Read_Stub(ulId, (VOS_VOID *)pItemData, usItemDataLen)
#define LPs_NvimItem_WriteEx(ulModmeId, ulId, pItemData, usItemDataLen)\
       NVM_Write_Stub(ulId, (VOS_VOID *)pItemData, usItemDataLen)
#endif

#define LPs_FactNvim_Write(ulId, pItemData, usDataLen)\
        NVIM_WriteFactoryForce(ulId, (VOS_VOID *)pItemData, usDataLen)

/* GCF, */
#define LPS_NV_GET_TAU_CIPHERED_BIT         ( 0x00000001 )
#define LPS_NV_LOCK_BAND_FREQ_CELL_IN_TEST_MODE_FUNC_BIT     (0x00000001)

#define LPS_NV_DL_CTRL_PDU_NOTIFY_BIT          (0x00000002)

/*added by lishangfeng 20130320 begin*/
#define LPS_NV_SEARCHING_OPTIMIZE_FUN_BIT    (0x00000004)
/*added by lishangfeng 20130320 end*/

#define LPS_NV_GET_MSG4_OLDCR_BIT           ( 0x00000002 )

/* GCF24.301 Table D.1.1 */
#define LPS_NV_GET_EST_CAUSE_BIT             ( 0x00000004 )

/* , */
#define LPS_NV_GET_SUPPORT_SMC_TEST_MODE_BIT  ( 0x00000008 )

/* GCFCDRX */
#define LPS_NV_GET_CDRX_L2_TIMER_BIT         ( 0x00000010 )

/* PS, */
#define LPS_NV_GET_SUPPORT_BAND64_BIT       ( 0x00000001 )

/* PS,SDFQos  */
/* SDFQos01 */
#define LPS_NV_GET_DEL_SDF_WITH_QOS_BIT       ( 0x00000002 )

/* ue, 0 ,  4 */
#define LPS_NV_GET_CONN_RCV_PAGING_TO_RELASE_BIT       ( 0x00000004 )

/* delete by s00139335 for DTS2016041910228,, 2016-4-19*/

/* PS,KDF */
#define LPS_NV_GET_HARD_KDF_BIT         ( 0x00000010 )
#define LPS_NV_GET_HARD_KDF_HYBRI_BIT   ( 0x00000020 )
#define LPS_NV_GET_ULDRB_DISCARD_BIT    ( 0x00000040 )

/*  0x000000800 */
#define PS_NV_TIME_DELAY_SWITCH_BIT     ( 0x00000080 )

/*  0x000001000 */
#define PS_NV_TIME_DELAY_HOOK_SWITCH_BIT     ( 0x00000100 )

/* MBMS */
#define LPS_NV_GET_MBMS_SUPPORT_BIT         ( 0x00000200 )

/* Bandwidth */
#define LPS_NV_GET_BANDWIDTH_SUPPORT_BIT         ( 0x00000400 )

/* modify by lishangfeng freq all begin */
#define LPS_NV_GET_FREQ_IN_ALL_BANDWITH_SUPPORT_BIT ( 0x00000800 )
/* modify by lishangfeng freq all end */
/*  */
#define LPS_NV_GET_REST_STUB_SUPPORT_BIT         ( 0x00001000 )

/* sunjitan DCM GULTA */
#define LPS_NV_GET_GU2L_HO_IGNORE_FORBID_TA_BIT     ( 0x00002000 )

/* gaojishan-ETWS-Begin */
#define LPS_NV_ETWS_SUPPORT_BIT         ( 0x00004000 )
#define LPS_NV_CMAS_SUPPORT_BIT         ( 0x00008000 )
/* gaojishan-ETWS-End */
/* gaojishan-SYSCFG-SAVENV-Begin */
#define LPS_NV_GET_JP_UBand1_Record_SUPPORT_BIT         ( 0x00010000 )
/* gaojishan-SYSCFG-SAVENV-End */

/* LUTRA-FDD */
#define LPS_NV_GET_L_REEST_CELL_SRCH_UTRA_FDD_BIT         ( 0x00020000 )

/* LGSM */
#define LPS_NV_GET_L_REEST_CELL_SRCH_GSM_BIT         ( 0x00040000 )

/* ,bar */
#define LPS_NV_GET_CELL_SRCH_CELL_BAR_BIT         ( 0x00080000 )

/* gaojishan-nccpermit */
#define LPS_NV_NCC_PERMIT_BIT         ( 0x00100000 )

/* bgs begin */
/* L */
#define LPS_NV_GET_L_BGS_SUPPORT_BIT                 ( 0x00200000 )
/* bgs end */

/*y00151394,tcp*/
#define LPS_NV_TCP_OPT_BIT            ( 0x00800000 )


/* gaojishan-reest-measGap*/
#define LPS_NV_GET_REEST_MEAS_GAP_SETUP_BIT            ( 0x00400000 )

/* gaojishan-SoftBank-:true,set Band41 range */
#define LPS_NV_SOFT_BANK_FLAG_BIT            ( 0x01000000 )

/* gaojishan-nccpermit-2 */
#define LPS_NV_NO_IDLE_NCC_PERMIT_BIT        ( 0x02000000 )

/* gaojishan-dcom-resel-cfg */
#define LPS_NV_JP_DCOM_USE_R8_BIT        ( 0x04000000 )

/* gaojishan-dcom-resel-cfg */
#define LPS_NV_JP_DCOM_CON_TO_IDLE_BIT        ( 0x08000000 )

/* gaojishan-dcom-resel-cfg */
#define LPS_NV_JP_DCOM_REL_OFFSET_BIT        ( 0x10000000 )
#define LPS_NV_JP_DCOM_REL_OFFSET_DEBUG_BIT  ( 0x20000000 )
/* gaojishan-fast-dorm-cfg */
#define LPS_NV_JP_DCOM_FAST_DORM_BIT  ( 0x40000000 )

/* add by lishangfeng for RRM 5.2.1 test begin */
#define LPS_NV_RRM_LTE_521_BIT  ( 0x80000000 )
/* add by lishangfeng for RRM 5.2.1 test end */

/* gaojishan-CMAS-Begin */
#define LPS_NV_CMAS_REPT_BEFORE_CAMP_SUCC_BIT    (0x00000008 )
/* gaojishan-CMAS-End */

/* v7r2 ca begin */
/* CA10 */
#define LPS_NV_CA_SUPPORT_BIT  ( 0x00000001 )
/* v7r2 ca end */

/* add for LTE NetScan begin */
/* stPsFunFlag021 */
/* NetScan10 */
#define LPS_NV_NETSCAN_SUPPORT_BIT    (0x00000002)
/* add for LTE NetScan end */

/* add for MFBI begin */
#define LPS_NV_LRRC_MFBI_CAMPON_WIDER_BAND_FLAG_BIT    (0x00000004)
/* add for MFBI end */

#define LPS_NV_LRRC_SUPPORT_EIA0_BIT (0x00000010)

/* lwurc  */
#define LPS_NV_LWURC_BAND_LIMIT_FLG_BIT            (0x00000020)

/* LLMM GU  */
#define LPS_NV_GET_L_BGS_L_SUPPORT_BIT            (0x00000040)

/* modify by lishangfeng 20131212 begin */
#define LPS_NV_SND_ETWS_IMIDIEATELY_BIT           (0x00000080)                  /* 0x800x00 */
/* modify by lishangfeng 20131212 end */

#define LPS_NV_L2_TLEVENT_REPORT_BIT           (0x00000100)                  /* TL L2*/
#define LPS_NV_RRC_LIST_SEARCH_TWICE_BIT           (0x00000400)                  /* LTE LIST*/
#define LPS_NV_RRC_BACKTOLTE_REDRECTFAIL_BIT        (0x00000800)

/* PS,NAS */
#define LPS_NV_GET_NAS_PLAIN_REJ_MSG_FLAG_BIT  (0x00001000)

#define LPS_NV_L2_CACELLINFO_REPORT_BIT          (0x00002000)                  /*CA SCELL*/

/* PS,CSFBBUGNV */
#define LPS_NV_GET_NAS_CSFB_TAU_TYPE2_FLAG_BIT  (0x00004000)

#define LPS_NV_GET_INTRA_HO_IGNORE_FORBID_TA_BIT    (0x00008000)                /* TA */

#define LPS_NV_GET_HO_RETRAN_ESR_MSG_FLAG_BIT     (0x00010000)                  /* ESR,TAU,ESR */
#define LPS_NV_GET_CSFB_OPTIMIZE_FLAG_BIT           (0x00020000)                /*csfbrelease*/

#define LPS_NV_LRRC_CHR_FEATURE_ON_FLAG_BIT    (0x00040000)

#define LPS_NV_LRRC_DYNAMIC_UE_CAP                (0x00080000)

/* UECA,CA,UERECFG_CMP; psfunflag02 bitflag21; 0:CMP; 1:CMP */
#define LPS_NV_LRRC_REPLY_RECFG_CMP_FLAG          (0x00100000)

#define LPS_NV_LRRC_CMAS_TEMPORARY_PROJECT_FLAG          (0x00200000)

/*add by l00220658  ADRX SSC NV stPsFunFlag03 0 1*/
#define LPS_NV_GET_SSC_SUPPORT_BIT                (0x00000001)
#define LPS_NV_GET_ADRX_SUPPORT_BIT               (0x00000002)
/* niuxiufan rrc release modify begin */
#define LPS_NV_GET_NOT_TRY_FAKE_CELL_FLAG_BIT     (0x00000004)
/* niuxiufan rrc release modify end */
#define LPS_NV_GET_DEL_MOBILE_SUPPORT_BIT         (0x00000008)

#define LPS_NV_GET_PTMSI_TAU_ACTIVE_FLAG_SUPPORT_BIT (0x00000020)

#define LPS_NV_GET_SBM_MFBI_CONN_MEAS_FLAG_SUPPORT_BIT (0x00000040)

#define LPS_NV_GET_FAKE_MDT_LOCINFO_FLAG_BIT    (0x00000080)

#define LPS_NV_GET_CMAS_RCV_CMP_FLAG_BIT    (0x00000100)

#define LPS_NV_GU2L_NO_BAR_BIT    (0x00000200)

/* Begin: add by m00352332 DCM,HO_CNF,T304 */
/* stPsFunFlag03 bitFlag12_11 */
#define LPS_NV_DCM_HO_FAIL_WAIT_T304_REEST_BIT    (0x00000800)
/* End: add by m00352332 DCM,HO_CNF,T304 */


/*TDS DSP */
#define ADDR_SELF_ADJUST_PARA       (0x1300F840)

/*DTS2016050400657 z00275692 for  NV*/
#define LPS_NV_GET_PDCP_CNTCHK_BIT    (0x00000010)


/*niuxiufan preamble modify begin */
#define LPS_NV_MAC_HIGHSPEED_CELL_RA_OPTIMIZE_BIT   (0x00000020)
#define LPS_NV_MAC_RA_PBL_LESS2_OPTIMIZE_BIT   (0x00000040)
/*niuxiufan preamble modify end */


/* GCF */
#define  LPS_NV_GET_GCF_FLAG(ucIndex, ulFlag) \
         (g_aulGcfFlg[ucIndex]&(ulFlag))

/* PS */
#define  LPS_NV_GET_PS_FUN_FLAG(ucIndex, ulFlag) \
         (g_aulPsFunFlg[ucIndex]&(ulFlag))

#define  LPS_NV_SUPPORT_BAND64                1     /* Band64 */
#define  LPS_NV_NOT_SUPPORT_BAND64            0     /* Band64 */
#define LPS_NV_CONN_RCV_PAGING_RELASE  0          /*  */
#define LPS_NV_CONN_RCV_PAGING_NO_RELASE  LPS_NV_GET_CONN_RCV_PAGING_TO_RELASE_BIT   /*  */

#define LPS_NV_GET_HARD_KDF_OFF        0                        /* KDF */
#define LPS_NV_GET_HARD_KDF_ON         LPS_NV_GET_HARD_KDF_BIT  /* KDF */


#define LPS_NV_GET_HARD_KDF_HYBRI_OFF        0                              /* KDF */
#define LPS_NV_GET_HARD_KDF_HYBRI_ON         LPS_NV_GET_HARD_KDF_HYBRI_BIT  /* KDF */


/* PS */
#define LPS_FUNC_SW_ON                       (1)
#define LPS_FUNC_SW_OFF                      (0)

/**/
#define MAX_GLOBAL_PRANT_NUM   5

/* TPS  */
#define  TPS_NV_GET_FLAG(uVlaue, ulFlag) \
         (uVlaue&(ulFlag))
#define TPS_NV_OP_HL1_SCHEDULE_IND_FLITER_BIT            ( 0x00000001 )
#define TPS_NV_OP_T_RRC_trafficMeasPeriod_FLITER_BIT            ( 0x00000002 )
#define TPS_NV_Print_FLITER_BIT            ( 0x00000004 )
/*CELLUPDATE MODEFIED BEGIN*/
#define TPS_NV_OP_Cellupdate_stub_BIT            ( 0x00000001 )
/*CELLUPDATE MODEFIED END*/
#define TPS_NV_OP_ADRX_GET_BIT            ( 0x00000100 )
/*DTS2015031800795 ADRX */
#define TPS_NV_OP_FORCE_ADRX_GET_BIT      ( 0x00001000 )

/* Cell-Reselection optimazation in CELL-FACH when Srx/SNR are lower than the thresholds*/
#define TPS_NV_CELL_RESEL_FOR_CELLFACH_GET_BIT      ( 0x00002000 )

/* RRC Connection Request failure with V300>N300 */
#define TPS_NV_RRCCONNECTIONREQ_FAILUREOPT_BIT      ( 0x00200000 )


/*bitFlag10*/
#define  TPS_NV_OP_DMO_Message_BIT           ( 0x00000200)

#define TPS_NV_SMC_STUB_BIT                 ( 0x00000400 )

#define TPS_NV_CS_TL_MEAS_EVA_CLOSE_BIT                 ( 0x00000800 )

#define TPS_NV_OP_NEWKEY_GET_BIT            ( 0x00000008 )
#define TPS_NV_CELL_SEARCH_OPT_BIT                 ( 0x00010000 )
#define TPS_NV_CELL_SEARCH_PRO_BIT                 ( 0x00020000 )
#define TPS_NV_L2T_REDIR_OPT_BIT                 ( 0x00004000 )
#define TPS_NV_CSS_BAND_SCAN_OPT_BIT              ( 0x00040000 )

#define TPS_NV_OP_TCP_ACK_DIS_GET_BIT       ( 0x00000010 )


/*DETECT CELL MODIFIY BEGIN*/
#define TPS_NV_OP_DETECT_CELL_GET_BIT       (0x00000020)
/*DETECT CELL MODIFIY END*/

#define TPS_NV_OP_MEASCONTROL_GET_BIT       (0x00000040)

#define TPS_NV_OP_RlcUmDataInd_GET_BIT       (0x00000080)


/*DTS2013022506993  BEGIN*/
#define TPS_NV_OP_Debug_Info_BIT            ( 0x00000002 )

#define TPS_NV_OP_Debug_State_BIT            ( 0x00000004 )
/*DTS2013022506993  END*/


#define TPS_NV_GCF_CS_LOOP_BIT            ( 0x00000001 )

#define TPS_NV_GCF_DRXEXTRA_CONTROL_BIT            ( 0x00000002 )

/*FRbegin*/
#define TPS_NV_OP_GSM_FR_BIT           ( 0x00000004 )
/*FRend*/
/*TG begin*/
#define TPS_NV_GCF_SIRAT_BIT           ( 0x00000008 )
#define TPS_NV_GCF_QRXLEVMIN_BIT        (0x00000010)
#define TPS_NV_GCF_S_UNSATISFIED_BIT    (0x00000020)
#define TPS_NV_T2G_IRAT_REPORT_BIT      (0x00000040)
/*TG end*/

#define TPS_NV_GCF_RRM_STUB_BIT         (0x00000080)

/* TL FR */
#define TPS_NV_FR_FEATURE_BIT           (0x00080000)
/* PSFR */
#define TPS_NV_PS_SIG_CONN_EXIST_FR_BIT (0x00100000)

#define TPS_NV_TG_3A_ESTIMATE_OPTIMIZATION_BIT (0x00800000)
/*IDLDBGNV*/
#define TPS_NV_DBG_IDL_MEAS_INFO_BIT           (0x01000000 )
/*DBGNV*/
#define TPS_NV_DBG_CONN_MEAS_INFO_BIT           (0x02000000 )

/* Ac All Barred Optimize Begin */
#define TPS_NV_AC_ALL_BARRED_OPTIMIZE_BIT      (0x04000000 )
/* Ac All Barred Optimize End */

/* LTE PS Transfer begin */
#define LRRC_MTC_THRESHOLD_MIN_VALUE      (0)
#define LRRC_MTC_THRESHOLD_MAX_VALUE      (31 * 2 * 8)
/* LTE PS Transfer end */
/* niuxiufan taiwan modify begin */
#define LRRC_IRAT_REDIR_NOT_BANDSCAN_BIT (0x00000008)
/* niuxiufan taiwan modify end */

/* Paging,UE Paging l00285345 begin*/
#define LRRC_IDLE_DISCARD_PAGING_BIT     (0x00000001)
/* Paging,UE Paging l00285345 end*/

/* high rat */
#define LRRC_NV_HIGHRAT_SEARCH_BIT     (0x00000004)
/* high rat */

#define TPS_NV_OP_OCCUPY_GET_BIT            ( 0x00000001 )
#define TPS_NV_OP_SIGNAL_REL_GET_BIT        ( 0x00000002 )

/* Paging,UE Paging l00285345 begin*/
#define TPS_NV_OP_DISCARD_PAGING_GET_BIT    ( 0x00000004 )
/* Paging,UE Paging l00285345 end*/

/* cgi-infoMeasObjcellForWhichToReportCGI  x00349962 begin */
#define LRRC_NV_ENDELCELLFORCGIFlG_BIT    ( 0x00040000 )
/* cgi-infoMeasObjcellForWhichToReportCGI  x00349962 end */

#define LRRC_MAX_NUM_IDC_SUBFRAME_PATTERNLIST           8
#define LRRC_MAX_NUM_SUBFRAME_CONFIG0_R11               9
#define LRRC_MAX_NUM_SUBFRAME_CONFIG6_R11               8

#define LRRC_ACCFAIL_MAX_BAR_STEP                       5


#define LRRC_SINGLE_CAND_PLMN_MAX_BAND                  8
#define LRRC_SINGLE_CAND_PLMN_MAX_FRQNUM               16
#define LRRC_CAND_PLMNFREQ_MAX_PLMNNUM                 20
#define LRRC_LATEST_MAX_CAND_FREQ_NUM                  12

/*PLMN*/
#define LRRC_MAX_PLMN_CANDARFCN_NUM                    48

#define LUP_MEM_MAX_POOL_NUM                (5)
#define LUP_MEM_MAX_CLUSTER_NUM             (8)

#define LRRC_IMSA_THRES_WLAN_LOW_P             (-105)
#define LRRC_IMSA_THRES_WLAN_LOW_Q             (-20)
#define LRRC_IMSA_THRES_WLAN_HIGH_P            (-80)
#define LRRC_IMSA_THRES_WLAN_HIGH_Q            (-5)
#define LRRC_IMSA_TIME_STEERING_WLAN           (3000)
#define LRRC_IMSA_THRES_WLAN_DELTA_P           (5)
#define LRRC_IMSA_THRES_WLAN_INTERVAL_RPT_TIME           (10000)
#define LRRC_CSG_HISTORY_CAMPED_CELL_NUM               50
#define LRRC_CSG_NEIGH_MACRO_CELL_NUM                  8
#define LRRC_CSG_HISTORY_CAMPED_CELL_PART_NUM          25

#define LRRC_SINGLE_DL_BAND_GROUP_NUM       (8)
#define LRRC_SINGLE_DL_BAND_CTRL_BIT             (0x00000001)

#define LRRC_RESTRICTED_BAND_ARRAY_NUM      (8)
#define LRRC_MAX_NUM_IDC_UL_CA_PARALIST      8

/* PLMNbegin */
#define LRRC_TEST_PLMN_MAX_NUM               (32)
/* PLMNend */

#define LRRC_FORBIDDEN_BAND_PLMN_MAX_NUM           (16)
#define LRRC_SINGLE_PLMN_FORBIDDEN_BAND_MAX_NUM    (8)

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/
/**/
enum RRC_NV_SWITCH_ENUM
{
    RRC_SWITCH_OFF = 0,
    RRC_SWITCH_ON  = 1
};

typedef VOS_UINT32   RRC_NV_SWITCH_ENUM_UINT32;

/* sib*/
enum RRC_NV_TIMER_CHOICE_ENUM
{
    RRC_TIMER_CHOICE_DEFAULT = 0,           /*  */
    RRC_TIMER_CHOICE_DT  = 1,               /*  */
    RRC_TIMER_CHOICE_BUTT
};
typedef VOS_UINT32   RRC_NV_TIMER_CHOICE_ENUM_UINT32;

enum RRC_PHY_LTE_RF_HW_ENUM
{
    RRC_PHY_LTE_RF_HW_BAND7_38_40         = 0,  /* Band7/38/40*/
    RRC_PHY_LTE_RF_HW_BAND20,                   /* Band20*/
    RRC_PHY_LTE_RF_HW_USB_STICK_VB,             /* USB STICKvb */
    RRC_PHY_LTE_RF_HW_SOFTBANK_BAND64,          /* Band64 */
    RRC_PHY_LTE_RF_HW_USB_STICK_VC,             /* USB STICKvC */
    RRC_PHY_LTE_RF_HW_USB_STICK_VD,             /* USB STICKvD */
    RRC_PHY_LTE_RF_HW_USB_STICK_VE,             /* USB STICKvE */
    RRC_PHY_LTE_RF_HW_USB_STICK_VF,             /* USB STICKvF */
    RRC_PHY_LTE_RF_HW_USB_STICK_VG,             /* USB STICKvG */
    RRC_PHY_LTE_RF_HW_USB_STICK_VH,             /* USB STICKvH */
    RRC_PHY_LTE_RF_HW_BUTT
};
typedef VOS_UINT8 RRC_PHY_LTE_RF_HW_ENUM_UINT8;
/*NV*/
/* gaojishan-PLMN_EXACTLY_COMPARE_FLG */
#ifdef PS_ITT_PC_TEST2
#define en_NV_Item_PLMN_EXACTLY_COMPARE_FLG   (9106)
#endif

/*****************************************************************************
     : LPS_NV_FLOW_CONTROL
   :
 ASN.1 :
   : 
*****************************************************************************/
typedef struct
{
    /*  */
    VOS_UINT32                          ulFlowCtrlFlag;
    /*ulFcInitFlag 0-RRC1-NV*/
    VOS_UINT32                          ulFcInitFlag;
    VOS_UINT32                          ulFcPdcpTarget;
    VOS_UINT32                          ulTargetIPMax;
    VOS_UINT32                          ulSendSduMax;
    VOS_UINT32                          ulDlSduMax;
    VOS_UINT32                          ulULIpMax;
    VOS_UINT32                          ulMeasGap;
    VOS_UINT32                          ulSduGap;
}LPS_NV_FLOW_CONTROL;

/*****************************************************************************
     : LPS_NV_GLOBAL_PRINT
   :
 ASN.1 :
   : 
*****************************************************************************/
typedef struct
{
    /*  0:1: 2: 3 4 5 */
    VOS_UINT32                          ulGlobalPrintFlag;
    VOS_UINT32                          aulPara[MAX_GLOBAL_PRANT_NUM];
}LPS_NV_GLOBAL_PRINT_STRU;

/*****************************************************************************
     : LPS_NV_MEAS_THRESHOLD_STRU
   :
 ASN.1 :
   :
*****************************************************************************/
typedef struct
{
    VOS_UINT8 ucSynsSwitch;     /* */
    VOS_UINT8 ucRsrpLowCount;   /* PHYsRsrpHoldThreshold */
    VOS_INT16 sRsrpHoldThreshold;  /* PHY ucRsrpLowCount++*/
}LPS_NV_MEAS_THRESHOLD_STRU;


/* 2655 begin */
 /*****************************************************************************
     : LPS_NV_LONG_BIT_STRU
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
}LPS_NV_LONG_BIT_STRU;
/*****************************************************************************
     : LPS_NV_TL_L2_PARA_STRU
   :
 ASN.1 :
   : L2
*****************************************************************************/
typedef struct
{
    /* RLC  NV45*/
    VOS_UINT32                          ulRlcUlSduLimit;

    LPS_NV_LONG_BIT_STRU                stL2Flag;

    /************************stL2FlagBIT***************************
     bitFlag01: L2 MAC PDU g_ulIfForwardToPc, 
     bitFlag02: L2 MAC PDU g_ulCapPusch, 
     bitFlag03: L2 MAC PDU g_ulCapPdsch, 
     bitFlag04: L2 MAC PDU g_ulCapPdcp, 
     bitFlag05: L2 MAC PDU g_ulTcpDebugFlg, 
     bitFlag06: L2 MAC PDU g_ulTcpDlFlg, 
     bitFlag07: L2 MAC PDU g_g_ulTcpUlFlg, 
     bitFlag08: L2 MAC PDU g_ulTcpCtrlPduFlg, 
     bitFlag09: RLC POLLING g_ulPollingCfgSwitch,
     bitFlag10:
     bitFlag11:
     bitFlag12:
     bitFlag13:
     bitFlag14:
     bitFlag15:
     bitFlag16:
     bitFlag17:
     bitFlag18:
     bitFlag19:
     bitFlag20:
     bitFlag21:
     bitFlag22:
     bitFlag23:
     bitFlag24:
     bitFlag25:
     bitFlag26:
     bitFlag27:
     bitFlag28:
     bitFlag29:
     bitFlag30:
     bitFlag31:
     bitFlag32:
    ****************************************************************************/

    LPS_NV_LONG_BIT_STRU                stL2Flag1;

    /*********************************
    Rev[0]IPV6NVIPV6UE1
    Rev[1]ROHC
    Rev[2]pollingPdu,32
    Rev[3]pollingByte25000
    **********************************/
    VOS_UINT32                          ulRev[32];
}LPS_NV_TL_L2_PARA_STRU;
/*****************************************************************************
     : LPS_NV_TL_L2_CHR_PARA_STRU
   :
 ASN.1 :
   : L2 CHR
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulRptPeriod;
    VOS_UINT32                          ulReestRptPeriod;
    VOS_UINT32                          ulReestRptThres;
    VOS_UINT32                          ulPdcpUlLossRptPeriod;
    VOS_UINT32                          ulPdcpUlLossRptThres;
    VOS_UINT32                          ulPdcpUlBuffTimeRptThres;
    VOS_UINT32                          ulPdcpDlLossRptPeriod;
    VOS_UINT32                          ulPdcpDlLossRptThres;
    VOS_UINT32                          ulMacDlTbCheckErrRptPeriod;
    VOS_UINT32                          ulMacDlTbCheckErrRptThres;
    VOS_UINT32                          ulPdcpSigPasRptPeriod;
    VOS_UINT32                          ulImsVoiceStopRptPeriod;
    VOS_UINT32                          ulImsVoiceStopRptThres;
    VOS_UINT32                          aulResv[24];
}LPS_NV_TL_L2_CHR_PARA_STRU;

/*****************************************************************************
     : LPS_SWITCH_PARA_STRU
   :
 ASN.1 :
   : 
*****************************************************************************/
typedef struct
{
    /* TA TimerSRSPUCCH 0:1: */
    VOS_UINT32                          ulCloseTaTimer;

    /* SR 0:  1: */
    VOS_UINT32                          ulSrTrigFlag;

    /* SR 0:1: */
    VOS_UINT32                          ulCloseSrRandFlag;

    /*01*/
    /*VOS_UINT32                          ulSyncCtrlFlag;*/

    /*01*/
    VOS_UINT32                          ulConnMeasFlg;

    /*IND: 1*/
    VOS_UINT32                          ulMeasReportMaxNum;

    /*0: 1: */
    VOS_UINT32                          ulIfForwardToPc;

    /**/
    VOS_UINT32                          ulSmcControl;

    /*eNBTDD*/
    /*VOS_UINT32                          ulMsg4OnlyPadding;*/

    /*BAR*/
    VOS_UINT32                          ulCloseBarCell;

    /*DRX 0:  1:*/
    VOS_UINT32                          ulDrxControlFlag;

   /* 0:  1:.*/
    VOS_UINT32                          ulFieldTestSwitch;

    /* PCO01 */
    VOS_UINT32                          ulPcoFlag;

    /**/
    LPS_NV_FLOW_CONTROL                  stPsNvFlowCtl;

    /************************stPsGcfFlag01BIT***************************
     bitFlag01:GCFTAU1
               0: 1:
     bitFlag02:GCFmsg41
               0: ; 1:
     bitFlag03:GCF24.301 Table D.1.11
               0: ; 1:
     bitFlag04:GCF1
               0: ; 1:
    ****************************************************************************/
    LPS_NV_LONG_BIT_STRU                 stPsGcfFlag01;

    /************************stPsGcfFlag02BIT***************************
     stPsGcfFlag01BIT:
     bitFlag01:
     bitFlag02:
    ****************************************************************************/
    LPS_NV_LONG_BIT_STRU                 stPsGcfFlag02;

    /************************stPsFunFlag01BIT***************************
     bitFlag01: Band64:0; 0:;1:
     bitFlag02: SDFQos,:0; 0:;1:
     bitFlag03: ue,:0; 0:;1:
     bitFlag04: ,:0; 0:;1:
     bitFlag05:
     bitFlag06:
     bitFlag07: DRBPDCP,01
     bitFlag08: Print:0; 0:;1:;RRM
     bitFlag09: :0; 0:;1:;
     bitFlag10: MBMS:0; 0:;1:;
     bitFlag11: SBMband.:0; 0:;1:;
     bitFlag12: :1; 0:;1:;
     bitFlag13: ,:1; 0:;1:;
     bitFlag14: DCM GULNASTA;:0; 0:;1:;
     bitFlag15: ETWS;:1; 0:;1:;
     bitFlag16: CMAS;:1; 0:;1:;
     bitFlag17:
     bitFlag18: LUTRAN;:1; 0:;1:;
     bitFlag19: LGSM;:1; 0:;1:;
     bitFlag20: ,RSRPbar;:0; 0:;1:;
     bitFlag21: NCC:0; 01
     bitFlag22: ,:0;1:0:
     bitFlag23: GAP:1; 1:0:
     bitFlag24:
     bitFlag25:
     bitFlag26: IDLENCC:0; 01
     bitFlag27: V7R1DCOM:0; 0:;1:;
     bitFlag28: V7R1DCOM:0; 0:;1:;
     bitFlag29: V7R1DCOM:0; 0:;1:;
     bitFlag30: V7R1DCOM:0; 0:;1:;
     bitFlag31: V7R1DCOM:0; 0:;1:;
     bitFlag32: RRM:0; 1:0:
    ****************************************************************************/
    LPS_NV_LONG_BIT_STRU                 stPsFunFlag01;

    /************************stPsFunFlag02BIT***************************
     bitFlag01: CA::0; 0:;1::;
     bitFlag02:
     bitFlag03:
     bitFlag04: CMAS:0;0: ; 1:
     bitFlag05:
     bitFlag06:
     bitFlag07: L.GU.:0; 0:;1:;
     bitFlag08: ETWS; 1:0:
     bitFlag09: TL L2-:0;0:;1:
     bitFlag10: LTE L2 -:0;0:;1:
     bitFlag11: LIST20:;1:
     bitFlag12: ; 0:;1:
     bitFlag13: NAS: 0; 0:  1: 
     bitFlag14: LTE CA-:0;0:;1:
     bitFlag15: BUGCSFBFRLpagingLTAUtype20.0:  1:
     bitFlag16: LTENASTA,:0; 0:; 1:
     bitFlag17: ESR,TAU,ESR,:0; 0: 1:
     bitFlag18: csfbrelease:0;0:;1:
     bitFlag19: LRRCCHR,:1; 0:;1:
     bitFlag20: UE,0:;1:;chicago,
     bitFlag21: UECA,CA,UERECFG_CMP;:0;  0:CMP; 1:CMP
     bitFlag22: CMAS; :0;  0:; 1:;
     bitFlag23:
     bitFlag24:
     bitFlag25:
     bitFlag26:
     bitFlag27:
     bitFlag28:
     bitFlag29:
     bitFlag30:
     bitFlag31:
     bitFlag32:
    ****************************************************************************/
    LPS_NV_LONG_BIT_STRU                 stPsFunFlag02;

    /************************stPsFunFlag03BIT***************************
     bitFlag01:  SCC; :0; 0:;1:;wanjiang w00178404
     bitFlag02:  ADRX;:0; 0:;1:;wanjiang w00178404
     bitFlag03:
     bitFlag04:
     bitFlag05:
     bitFlag06:  L,TAUACTIVE FLAG;:0; 0:; 1:
     bitFlag07:  MFBIband;0;0:;1:
     bitFlag08:  MDT/RLFMDTGCF0.0: 1:
     bitFlag09:  CMAS00:1:
     bitFlag10:  GU2LCCOLL10ms
     bitFlag11:
     bitFlag12:
     bitFlag13:
     bitFlag14:
     bitFlag15:
     bitFlag16:
     bitFlag17:
     bitFlag18:
     bitFlag19:
     bitFlag20:
     bitFlag21:
     bitFlag22:
     bitFlag23:
     bitFlag24:
     bitFlag25:
     bitFlag26:
     bitFlag27:
     bitFlag28:
     bitFlag29:
     bitFlag30:
     bitFlag31:
     bitFlag32:
    ****************************************************************************/
    LPS_NV_LONG_BIT_STRU                 stPsFunFlag03;

   /************************stPsFunFlag04BIT***************************
     bitFlag01: LTE ,IDLEUE Paging0.
                0:  1:
     bitFlag02:
     bitFlag03:
     bitFlag04:
     bitFlag05:
     bitFlag06: L2 MAC1,
     bitFlag07: L2 MACPreamble2,1
     bitFlag08:
     bitFlag09:
     bitFlag10:
     bitFlag11:
     bitFlag12:
     bitFlag13:
     bitFlag14:
     bitFlag15:
     bitFlag16:
     bitFlag17:
     bitFlag18:
     bitFlag19:
     bitFlag20:
     bitFlag21:
     bitFlag22:
     bitFlag23:
     bitFlag24:
     bitFlag25:
     bitFlag26:
     bitFlag27:
     bitFlag28:
     bitFlag29:
     bitFlag30:
     bitFlag31:
     bitFlag32:
    ****************************************************************************/
    LPS_NV_LONG_BIT_STRU                 stPsFunFlag04;

    LPS_NV_GLOBAL_PRINT_STRU             stPsNvGlobalPrint;
}LPS_SWITCH_PARA_STRU;

/*DTS2013010602867 Tps*/
/*****************************************************************************
     : TPS_SWITCH_PARA_STRU
   :
 ASN.1 :
   : 
*****************************************************************************/
typedef struct
{
    /************************stTpsLayFliterFlag01BIT********************
     bitFlag01:OP_HL1_SCHEDULE_IND0
               0: 1:
     bitFlag02:OP_T_RRC_trafficMeasPeriod0
               0: 1:
     bitFlag03:0
               0: 1:
     bitFlag04:
     bitFlag05:
     bitFlag06:
     bitFlag07:
     bitFlag08:
     bitFlag09:
     bitFlag10:
     bitFlag11:
     bitFlag12:
     bitFlag13:
     bitFlag14:
     bitFlag15:
     bitFlag16:
     bitFlag17:
     bitFlag18:
     bitFlag19:
     bitFlag20:
     bitFlag21:
     bitFlag22:
     bitFlag23:
     bitFlag24:
     bitFlag25:
     bitFlag26:
     bitFlag27:
     bitFlag28:
     bitFlag29:
     bitFlag30:
     bitFlag31:
     bitFlag32:

    ****************************************************************************/
    LPS_NV_LONG_BIT_STRU                 stTpsLayFliterFlag01;

    /************************stTpsLayFliterFlag01BIT********************
     bitFlag01:
     bitFlag02:
    ****************************************************************************/
    LPS_NV_LONG_BIT_STRU                 stTpsLayFliterFlag02;

    /************************stTPsGCFFlag01BIT**************************
     bitFlag01: GCFcs loop 
                0
                0:CsLoop  1:
                

     bitFlag02: TDS,TRRCS
                0
                0: 1:

     bitFlag03: FR
                1
                0: 1:

     bitFlag04: TGsOfIratsearch
                0
                0:  1:

     bitFlag05: TGQrxLev
                0
                0:  1:

     bitFlag06: TS0GSMS0
                0
                0:  1:

     bitFlag07: ,6dbtdst
                0
                0:  1:

     bitFlag08: RRMRRM
                0
                0: 1:

     bitFlag09:
     bitFlag10:
     bitFlag11:
     bitFlag12:
     bitFlag13:
     bitFlag14:
     bitFlag15:
     bitFlag16:
     bitFlag17:
     bitFlag18:
     bitFlag19:
     bitFlag20:
     bitFlag21:
     bitFlag22:
     bitFlag23:
     bitFlag24:
     bitFlag25:
     bitFlag26:
     bitFlag27:
     bitFlag28:
     bitFlag29:
     bitFlag30:
     bitFlag31:
     bitFlag32:
    ****************************************************************************/
    LPS_NV_LONG_BIT_STRU                 stTPsGCFFlag01;

    /************************stTPsGCFFlag02BIT**************************
     bitFlag01:
     bitFlag02:
    ****************************************************************************/
    LPS_NV_LONG_BIT_STRU                 stTPsGCFFlag02;

    /************************stTPsFunFlag01BIT**************************
     bitFlag01: CellUpdateT313PSCellUpdate,IDL
                1
                0: 1:

     bitFlag02: debug
                0.
                0: 1:

     bitFlag03: debugDebug
                0
                0: 1:

     bitFlag04: SMC
                0
                0: 1:

     bitFlag05: TCP ACK
                0
                0: 1:

     bitFlag06: DetectCell
                0
                0: 1:

     bitFlag07: MeasCtrl
                0
                0: 1:

     bitFlag08: CCCHUE
                1
                0: 1:

     bitFlag09:ADRX ,DRX
               0
               0: 1:

     bitFlag10:DMO message function
               0: 1:

     bitFlag11:SMCSMCGUNAS
               0
               0: 1:

     bitFlag12:CSTL
               1
               0: 1:

     bitFlag13:ADRX ,DRX
               0
               0: 1:
     bitFlag14:CS FACH
              0
              0: 1:
     bitFlag15:L2T
               0
               0: 1:
     bitFlag16:
     bitFlag17:MACMACTRRC
              0
              0: 1:
     bitFlag18:
               0
               0: 1:
     bitFlag19:CSSBANDSCAN
               0: 1:
     bitFlag20:FR
               1
               0: 1:
     bitFlag21:PSFR
               1
               0: 1:
     bitFlag22:RRC connection requestV300>N300,Bar
               1
               0: 1:
     bitFlag23:
     bitFlag24:TG 3A
               1
               0: 1:
     bitFlag25:IdlDEBUG
               1
               0: 1:
     bitFlag26:ConnDEBUG
               1
               0: 1:
     bitFlag27:AcBar
               1
               0: 1:
     bitFlag28:
     bitFlag29:
     bitFlag30:
     bitFlag31:
     bitFlag32:

    ****************************************************************************/
    LPS_NV_LONG_BIT_STRU                 stTPsFunFlag01;

    /************************stTPsFunFlag02BIT**************************
     bitFlag01: TDS DSDS DCH_CONFIG.0
                0:  1:
     bitFlag02: TDS DSDS 500msSignalRel0.
                0:  1:
     bitFlag03:TDS ,IDLEUE Paging0.
                0:  1:
    ****************************************************************************/
    LPS_NV_LONG_BIT_STRU                 stTPsFunFlag02;
}TPS_SWITCH_PARA_STRU;

/*DTS2013010602867 end Tps*/
/*****************************************************************************
     : TDS_CERSSI_REPORT_PARA_STRU
   :
 ASN.1 :
   : 
*****************************************************************************/
typedef struct
{
    VOS_UINT32                           ulThreshold;
    VOS_UINT32                           ulInterval;
    VOS_UINT8                            aucRsv[4];
}TDS_CERSSI_REPORT_PARA_STRU;
/*****************************************************************************
     : LPS_LTE_CONFIG_STRU
   :
 ASN.1 :
   : LTE
*****************************************************************************/
typedef struct
{
    /* LTE */
    VOS_UINT32                          ulPsCfgDspAntCnt;

    /*VOS_UINT32                          ulPsCfgDspRatMod;*/
    /*14036.101band,20*/
    VOS_UINT8                          ucEutraBand;

    VOS_UINT8                          aucRsv[3];

    /* 1 */
    VOS_UINT32                          ulCfgSubFrameAssign;

    /* 7 */
    VOS_UINT32                          ulSubFramePattern;
}LPS_LTE_CONFIG_STRU;

/*****************************************************************************
     : LRRC_NV_CAND_CELL_LIST_STRU
   :
 ASN.1 :
   : NV
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usFreqCount;                            /*  */
    VOS_UINT8                           aucReserved1[2];
    RRC_NV_CSEL_CAND_FREQ_STRU          ausCandFreqs[RRC_NV_EACH_BAND_FREQ_COUNT];/*  */
}LRRC_NV_CAND_CELL_LIST_STRU;

/*****************************************************************************
     : LRRC_NV_SUPPORT_BAND_LIST_STRU
   :
 ASN.1 :
   : UENV
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usBandCount;                            /*  */
    VOS_UINT8                           aucReserved1[2];
    RRC_NV_CSEL_FREQ_BAND_INFO_STRU     astCandBands[RRC_NV_EACH_BAND_BANDS_COUNT];
}LRRC_NV_SUPPORT_BAND_LIST_STRU;

/*****************************************************************************
     : RRC_NV_EACH_BAND_IND_INFO_STRU
   :
 ASN.1 :
   : Band
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucBandInd;                              /*  */
    PS_BOOL_ENUM_UINT8                  enFirstSearchFlg;                       /*  */
    VOS_UINT8                           aucReserved1[2];
    LRRC_NV_CAND_CELL_LIST_STRU         stCandCellInfo;                         /* Band */
    LRRC_NV_SUPPORT_BAND_LIST_STRU      stCandBandsInfo;                        /* Band */
}LRRC_NV_EACH_BAND_CAND_INFO_STRU;


/*****************************************************************************
     : LRRC_NV_CALIBRATION_BAND_LIST_STRU
   :
 ASN.1 :
   : UEband
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucReserved[2];
    VOS_UINT16                          usCnt;
    VOS_UINT8                           aucEutraBand[RRC_MAX_NUM_OF_BANDS];
}LRRC_NV_CALIBRATION_BAND_LIST_STRU;

/*****************************************************************************
     : LRRC_UE_CAP_MEAS_EUTRA_BAND_STRU
   :
 ASN.1 :
   : UE EUTRAMEAS->Band
*****************************************************************************/
typedef struct
{
    RRC_INTER_FREQ_EUTRA_BAND_INFO_STRU stInterFreqEutraBandInfo;
    RRC_INTER_RAT_BAND_INFO_STRU        stInterRatBandInfo;
}LRRC_UE_CAP_MEAS_EUTRA_BAND_STRU;

/*****************************************************************************
     : RRC_UE_EUTRA_CAP_STRU
   :
 ASN.1 :
   : UE EUTRA
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitFeatureGroupIndsPresent    : 1;
    VOS_UINT32                          bitUeCapV920IesPresent        : 1;
    VOS_UINT32                          bitSpare                      : 30;
    VOS_UINT8                           aucReserved[2];
    /* UE10Rel8,Rel9,.... */
    VOS_UINT8                           ucAsRelBitmap;
    RRC_UE_CATEGORY_ENUM_UINT8          enUeCatg;
    RRC_UE_CAP_PDCP_PARA_STRU           stPdcpPara;
    RRC_UE_CAP_PHY_PARA_STRU            stPhyPara;
    RRC_UE_CAP_RF_PARA_STRU             stRfPara;
    RRC_UE_CAP_MEAS_PARA_STRU           stMeasPara;
    RRC_UE_CAP_FEATURE_GROUP_IND_STRU   stFeatrueGroupInds;
    RRC_UE_CAP_INTER_RAT_PARA_STRU      stInterRatPara;
    RRC_UE_EUTRA_CAP_V920_IES_STRU      stUeCapV920Ies;
} LRRC_NV_UE_EUTRA_CAP_STRU;

/*****************************************************************************
     : LRRC_NV_RRC_CTRL_STRU
   :
 ASN.1 :
   : RRC
             3db,BAR,SIB
*****************************************************************************/
typedef struct
{
    RRC_NV_SWITCH_ENUM_UINT32            en3dbCtlFlg;           /*  0 */
    VOS_UINT32                           ulMaxSeachCntOfBarFrq;
    RRC_NV_TIMER_CHOICE_ENUM_UINT32      enSibTimerChoiceFlg;   /* 0 */
    VOS_UINT32                           ulReserved;            /* 1 */
}LRRC_NV_RRC_CTRL_STRU;

enum LRRC_NV_LOCK_MODE
{
    LRRC_NV_LOCK_MODE_RoadTest                    = 0,          /*,List*/
    LRRC_NV_LOCK_MODE_POS                         = 1,          /*POSList*/
    LRRC_NV_LOCK_MODE_BUTT
};
typedef VOS_UINT8   LRRC_NV_LOCK_MODE_UINT8;

/*****************************************************************************
     : LRRC_NV_LOCK_INFO_STRU
   :
 ASN.1 :
   :NV
*****************************************************************************/
typedef struct
{
    RRC_NV_LOCK_INFO_ENUM_UINT32         enLockInd;
    PS_BOOL_ENUM_UINT8                   ucActiveFlag;                   /*,PS_TRUE*/
    LRRC_NV_LOCK_MODE_UINT8              ucLockMode;                     /*,*/
    /*end: add by wangmiao00272217 ,PS_TRUE*/
    VOS_UINT8                            ucBandInd;                      /*  */
    VOS_UINT8                            ucForbidReselAndHO;             /*  */
    VOS_UINT16                           usCellId;                       /* ID */
    VOS_UINT16                           usFreqPoint;                    /*  */
    RRC_NV_CSEL_FREQ_BAND_INFO_STRU      stLockedBand;                   /* Band */
} LRRC_NV_LOCK_INFO_STRU;

/* modify by lishangfeng begin */

/*****************************************************************************
     : LRRC_NV_CSQ_RPT_INFO_STRU
   :
 ASN.1 :
   : 
*****************************************************************************/
typedef struct
{
    VOS_UINT32                       ulRssiReportLen;
    VOS_UINT32                       ulDetaRssi;    /*  */
    VOS_UINT16                       usMs;          /*  */
    VOS_UINT16                       usDetaSINR;    /*  (0,50)db*/
} LRRC_NV_CSQ_RPT_INFO_STRU;

/* modify by lishangfeng end */

/* wangrui 20120817 begin */
/*****************************************************************************
     : LRRC_NV_LWCLASH_RANGE_STRU
   :
 ASN.1 :
   : 
*****************************************************************************/
typedef struct
{
    VOS_UINT16                        usFreqBegin;        /* :100Khz*/
    VOS_UINT16                        usFreqEnd;          /* :100Khz*/
} LRRC_NV_LWCLASH_RANGE_INFO_STRU;
/*****************************************************************************
     : LRRC_NV_LWCLASH_RANGE_STRU
   :
 ASN.1 :
   : 
*****************************************************************************/
typedef struct
{
    VOS_UINT16                        ulnum;                /* :100Khz*/
    VOS_UINT8                         ucRev[2];
    LRRC_NV_LWCLASH_RANGE_INFO_STRU   stBandRng[RRC_NV_LWCLASH_RANGE_COUNT]; /* :100Khz*/
} LRRC_NV_LWCLASH_RANGE_STRU;

/* wangrui 20120817 end */
/*****************************************************************************
     : LRRC_NV_UE_RFRD_TYPE_STRU
   :
 ASN.1 :
   :NV
*****************************************************************************/
typedef struct
{
    RRC_NV_UE_RFRD_TYPE_ENUM_UINT8       enUeRfrdType;              /*  */
    VOS_UINT8                            aucReserved[3];

} LRRC_NV_UE_RFRD_TYPE_STRU;

/*****************************************************************************
     : LRRC_NV_RF_HW_STRU
   :
 ASN.1 :
   :9361RF
*****************************************************************************/
typedef struct
{
    RRC_PHY_LTE_RF_HW_ENUM_UINT8       enLteRfHw;
    VOS_UINT8                          aucRsv[3];
} LRRC_NV_RF_HW_STRU;

/*****************************************************************************
     : LTE_COMPENSATE_SWITCH_STRU
   :
 ASN.1 :
   : , NVDSP
*****************************************************************************/
typedef struct
{
    VOS_UINT16 usFreqCmpnstSwitch;      /*0 1:*/
    VOS_UINT16 usTempCmpnstSwitch;      /*0  1:*/
    VOS_UINT16 usTxPwrCmpnstSwitch;     /*0 1: */
    VOS_UINT16 usReserved;
}LTE_COMPENSATE_SWITCH_STRU;

/*****************************************************************************
     : LUPLINK_POWER_CONFIG_STRU
   :
 ASN.1 :
   : , NVDSP
*****************************************************************************/
typedef struct
{
    VOS_UINT16 usPuschPwrCtrlSwitch;
    VOS_UINT16 usPuschClosedLoopSwitch;
    VOS_UINT16 usPucchPwrCtrlSwitch;
    VOS_UINT16 usPucchClosedLoopSwitch;
    VOS_UINT16 usSrsPwrCtrlSwitch;
    VOS_UINT16 usPrachPwrCtrlSwitch;

    VOS_INT16  sPuschTxPower;
    VOS_INT16  sPucchTxPower;
    VOS_INT16  sSrsTxPower;
    VOS_INT16  sPrachTxPower;
}LUPLINK_POWER_CONFIG_STRU;

/* LTE PS Transfer begin */
/* MTC AREA LOST Begins */
#if(FEATURE_MULTI_MODEM == FEATURE_ON)
typedef struct
{
    PS_BOOL_ENUM_UINT8      enValidFlag;  /*  */
    VOS_UINT8               ucLrrcMTCLostThreshold; 	/* LTEPS,0~31 */
    VOS_UINT8               ucLrrcMTCAvailableDValue;    /* LTEPS,0~(31-ucLrrcMTCLostThresh) */
    VOS_UINT8               ucMTCLostTimerLen;    /* LTE->CDMAPS,:s */
    VOS_INT16               sRsv; /**/
    VOS_UINT16              usMTCAvailableTimerLen; /* CDMA->LTEPS,:s */
}LTE_MTC_AREA_LOST_THRESHOLD_STRU;
#endif
/* MTC AREA LOST End */
/* LTE PS Transfer end */


/* gaojishan-PLMN_EXACTLY_COMPARE_FLG */
#ifdef PS_ITT_PC_TEST2
typedef struct
{
    VOS_UINT8   ucPlmnExactlyCompareFlag;
    VOS_UINT8   aucRsv[3];
}NVIM_PLMN_EXACTLY_COMPARE_FLAG_STRU;
#endif
/* TCXo */


/*****************************************************************************
     : LTE_GATE_CLOCK_CONFIG_STRU
   :
 ASN.1 :
   :
*****************************************************************************/
typedef struct
{
    VOS_UINT16 usGateClockEnableFlag;       /* 0:invalid, 1:Valid,  0 */
    VOS_UINT16 usRsvd;
} LTE_GATE_CLOCK_CONFIG_STRU;

/*****************************************************************************
     : FC_LTE_CPU_CONFIG_STRU
   :
 ASN.1 :
   : LTE CPU
*****************************************************************************/
typedef struct
{
    VOS_UINT16          usFirstDelay;           /*  */
    VOS_UINT16          usUlDownRate;           /*  */
    VOS_UINT16          usUlUpRate;             /*  */
    VOS_UINT16          usUlMinThr;             /*  kbps */
    VOS_UINT16          usHqDownRate;           /* HARQ */
    VOS_UINT16          usHqUpRate;             /* HARQ */
    VOS_UINT16          usHqMaxDiscardRate;     /* HARQ */
    VOS_UINT16          usDowngradeThres;       /* CPU */
    VOS_UINT16          usUpgradeThres;         /* CPU */
	VOS_UINT16          usResv;
} FC_LTE_CPU_CONFIG_STRU;

/*****************************************************************************
     : FC_LTE_TEMPERATURE_CONFIG_STRU
   :
 ASN.1 :
   : LTE 
*****************************************************************************/
#define FC_UL_THROUGHPUT_THRES_CNT_NV          (12)
typedef struct
{
    VOS_UINT8           ucInitialPos;           /* 0~11, 4 */
    VOS_UINT8           ucZeroSupport;          /* 0,00 */
    VOS_UINT8           ucResv[2];              /*  */
    VOS_UINT32          ulTemperSteps[FC_UL_THROUGHPUT_THRES_CNT_NV];      /* kbps[50000, 40000, 30000, 25000, 20000, 15000, 10000, 5000, 2000, 0, 0, 0] */
    VOS_UINT32          ulMinBsrThr;            /* BSRkbps120 */
} FC_LTE_TEMPERATURE_CONFIG_STRU;

/*****************************************************************************
     : FLOWCTRL_LTE_CONFIG_STRU
   :
 ASN.1 :
   : LTE
*****************************************************************************/
typedef struct
{
    FC_LTE_TEMPERATURE_CONFIG_STRU stFcTemperatureConfig;
    FC_LTE_CPU_CONFIG_STRU  stFcCpuConfig;
} FLOWCTRL_LTE_CONFIG_STRU;


/* gaojishan-SYSCFG-SAVENV-Begin */
#define NV_ITEM_EUTRA_MAX_SUPPORT_BANDS_NUM         (64)
#define NV_MAX_FDD_FREQ_BANDS_NUM                 (32)

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
typedef struct
{
    VOS_UINT32                  ulWcdmaBand;
    VOS_UINT16                  usGsmBand;
    VOS_UINT8                   aucReserve[2];
    VOS_UINT8                   aucUeSupportWcdmaBand[NV_MAX_FDD_FREQ_BANDS_NUM];
    VOS_UINT8                   aucUeSupportGsmBand[NV_MAX_FDD_FREQ_BANDS_NUM];
}NV_UE_SUPPORT_FREQ_BAND_STRU;

/*****************************************************************************
     : NV_UE_EUTRA_FREQ_BAND_INFO_STRU
   :
 ASN.1 :
   : LTE
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucBandNo;                               /* band(1-64) */
    VOS_UINT8                           ucDuplexModeFlg;                        /* 100 */
    VOS_UINT8                           aucReserve[2];
}NV_UE_EUTRA_FREQ_BAND_INFO_STRU;
/*******************************************************************************
     : NV_UE_EUTRA_SUPPORT_FREQ_BAND_LIST_STRU
   :
 ASN.1 :
   : LTE,LTE,WAS GASFDD,TDD,LTE

LTEBAND
1  0     C 599
2  600   -  1199
3  1200  C 1949
4  1950  C 2399
5  2400  C 2649
6  2650  C 2749
7  2750  C 3449
83 450   C 3799
93 800   C 4149
10 4150  C 4749
11 4750  C 4949
12 5010  -  5179
13 5180  C 5279
14 5280  C 5379
...
17 5730  C 5849
18 5850  C 5999
19 6000  C 6149
20 6150  C 6449
21 6450  C 6599
...
33 36000 C 36199
34 36200 C 36349
35 36350 C 36949
36 36950 C 37549
37 37550 C 37749
38 37750 C 38249
39 38250 -  38649
40 38650 -  39649
64 25450 -  25749
*******************************************************************************/
typedef struct
{
    VOS_UINT16                              usBandCnt;                          /* LTE band  4 */
    VOS_UINT8                               aucReserved1[2];                    /*  */

    /* LTEband64 72038 40a
        stCandBands[0].ucBandNo  =  7
        astCandBands[1].ucBandNo = 20
        astCandBands[2].ucBandNo = 38
        astCandBands[3].ucBandNo = 40  */
    NV_UE_EUTRA_FREQ_BAND_INFO_STRU       astCandBands[NV_ITEM_EUTRA_MAX_SUPPORT_BANDS_NUM];
}NV_UE_EUTRA_SUPPORT_FREQ_BAND_LIST_STRU;

/*****************************************************************************
     : NV_GUL_SUPPORT_FREQ_BAND_STRU
   :
 ASN.1 :
   : SYSCFGGULband
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                       ucValidFlag;
    VOS_UINT8                                       aucReserved1[3];
    NV_UE_SUPPORT_FREQ_BAND_STRU                  stGuCfgBand;
    NV_UE_EUTRA_SUPPORT_FREQ_BAND_LIST_STRU       stLteCfgBand;
}NV_GUL_SUPPORT_FREQ_BAND_STRU;
/* gaojishan-SYSCFG-SAVENV-End */
/* gaojishan-nv-bands-cfg-begin */
#define NV_ITEM_EUTRA_MAX_BANDXX_CAND_BANDS_NUM    (12)
#define NV_ITEM_EUTRA_MAX_CUSTOM_BAND_WIDTH_NUM    (6)
#define NV_LTE_NV_MAX_SUPPORT_BAND                 (47)
#define NV_BAND_IND_64                             (64)
enum RRC_NV_D2DA_BANDXX_FUNC_FLAG_ENUM
{
    RRC_BANDXX_FUNC_INVALIED = 0,
    RRC_BANDXX_FUNC_JAPAN_CUSTOMER,
    RRC_BANDXX_FUNC_CUSTOMIZE_BAND_RANG
};
typedef VOS_UINT16 RRC_NV_D2DA_BANDXX_FUNC_FLAG_ENUM_UINT16;

/*****************************************************************************
     : LRRC_NV_CUSTOM_BAND_INFO_STRU
   :
 ASN.1 :
   : band
*****************************************************************************/
typedef struct
{
    VOS_UINT8                         ucBandWidth;/* 0-5:1.4m3m5m10m15m20m */
    VOS_UINT8                         aucReserved1[3];
    RRC_NV_CSEL_FREQ_BAND_INFO_STRU   stCandBands;
}LRRC_NV_CUSTOM_BAND_INFO_STRU;

/*****************************************************************************
     : LRRC_NV_BANDXX_CAND_INFO_STRU
   :
 ASN.1 :
   : band
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                       ucBandInds;
    VOS_UINT8                                       ucCustomBandInfoNum;
    VOS_UINT8                                       aucReserved1[2];
    LRRC_NV_CUSTOM_BAND_INFO_STRU                   astCustomBandInfoList[NV_ITEM_EUTRA_MAX_CUSTOM_BAND_WIDTH_NUM];
}LRRC_NV_BANDXX_CAND_INFO_STRU;

/*****************************************************************************
     : NV_ID_BANDXX_CAND_INFO_GROUP_STRU
   :
 ASN.1 :
   : band
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                       ucValidFlag;
    VOS_UINT8                                       ucCandBandNum;
    VOS_UINT8                                       aucReserved1[2];
    LRRC_NV_BANDXX_CAND_INFO_STRU                   astCandBandInfoList[NV_ITEM_EUTRA_MAX_BANDXX_CAND_BANDS_NUM];
}NV_ID_BANDXX_CAND_INFO_GROUP_STRU;
/* gaojishan-nv-bands-cfg-end */

typedef struct
{
    VOS_UINT8                                       ucRcvSibRsrqFlg; /* qsib */
    VOS_UINT8                                       aucReserved1;
    VOS_UINT8                                       aucReserved2;
    VOS_UINT8                                       aucReserved3;
    VOS_UINT16                                      usGetGeoMinRsrpThreshold;
    VOS_UINT16                                      usMinRsrqRcvSibThreshold; /* Q*/
    VOS_UINT16                                      usHighRsrpByRsrqRcvSib; /* QP */
    VOS_UINT16                                      usLowRsrpByRsrqRcvSib;  /* QP */

}LRRC_NV_CSEL_GET_SIB_THRESHOLD_STRU;
typedef struct
{
    PS_BOOL_ENUM_UINT8    ucOffSetEnableFlg; /* offset NV*/
    PS_BOOL_ENUM_UINT8    enR8BasedCellReselFlg;  /* R8*/
    VOS_UINT8              aucReservel[2];         /* */
    VOS_UINT16             usWRscpThresh;        /* WRSCPoffset*/
    VOS_UINT16             usWEcnoThresh;        /* WECNOoffset*/
    VOS_UINT16             usEutranCellRsrpOffset;  /* EUTRANRSRP OFFSET*/
    VOS_UINT16             usEutranCellRsrqOffset;  /* EUTRANRSRQ OFFSET*/
    VOS_UINT16             usLteServRsrpOffSet;
    VOS_UINT16             usLteServRsrqOffSet;
    VOS_UINT16             usUtranRscpOffSet;
    VOS_UINT16             usUtranEcnoOffSet;
}NV_ID_APP_LRRC_RESEL_OFFSET_CFG_STRU;

/* gaojishan-fast-dorm-cfg-3 */
#define LRRC_NV_CTRL_PARA_U8_MAX_LEN                   (16)
#define LRRC_NV_CTRL_PARA_U16_MAX_LEN                  (8)
#define LRRC_NV_CTRL_PARA_U32_MAX_LEN                  (8)

/* gaojishan-fast-dorm-cfg-3 */
#define LRRC_CTRL_PARA_FAST_DORM_DELAY_BIT             (16)
#define LRRC_GET_CTRL_PARA_U8_INDEX( usIndex )         ( (usIndex))
#define LRRC_GET_CTRL_PARA_U16_INDEX( usIndex )        ( (usIndex)-LRRC_NV_CTRL_PARA_U8_MAX_LEN)
#define LRRC_GET_CTRL_PARA_U32_INDEX( usIndex )        ( (usIndex)-LRRC_NV_CTRL_PARA_U8_MAX_LEN - LRRC_NV_CTRL_PARA_U16_MAX_LEN )
#define LRRC_CTRL_PARA_IS_BIT_PRESENT( ulBitMap, ulBit )         ( (ulBitMap)&( 1<< (ulBit) ) )

typedef struct
{
    VOS_UINT32          bitValidMap ; /*BitMap(high--->low) U32,U16,U8,U8 */
    VOS_UINT8           astucCtrlPara[LRRC_NV_CTRL_PARA_U8_MAX_LEN];
    VOS_UINT16          astusCtrlPara[LRRC_NV_CTRL_PARA_U16_MAX_LEN];
    VOS_UINT32          astulCtrlPara[LRRC_NV_CTRL_PARA_U32_MAX_LEN];
}NV_ID_CTRL_PARA_STRU;

/* CMCC-BEGIN */
/*****************************************************************************
     : LTE_IRAT_REDIR_SWITCH_STRU
   :
 ASN.1 :
   : CMCC G2L4sG2L2s
             W2L2s
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                   ucG2LRedirFlag;                 /* G2L4s */
    VOS_UINT8                                   ucG2LAutoRedirFlag;             /* G2L2s */
    VOS_UINT8                                   ucW2LAutoRedirFlag;             /* W2L2s */
    VOS_UINT8                                   aucReservd1[5];
    VOS_UINT16                                  usG2LRedirTimeLen;              /* G2L4sms */
    VOS_UINT16                                  usG2LAutoRedirTimeLen;          /* G2L2sms */
    VOS_UINT16                                  usW2LAutoRedirTimeLen;          /* W2L2sms */
    VOS_UINT8                                   aucReservd2[6];
}LTE_IRAT_REDIR_SWITCH_STRU;
/* CMCC-END */
/*****************************************************************************
     : FC_LTE_TEMPERATURE_LIMIT_CONFIG_STRU
   :
 ASN.1 :
   : LTE 
*****************************************************************************/
#define FC_UL_THROUGHPUT_MIN_COUNT_NV          (0x03)
typedef struct
{
    VOS_UINT32          ulZeroSupported;
    VOS_UINT32          ulMinThroughput[FC_UL_THROUGHPUT_MIN_COUNT_NV];
} FC_LTE_TEMPERATURE_LIMIT_CONFIG_STRU;

/*****************************************************************************
     : LTE_APT_TOTAL_SWITCH
   :
 ASN.1 :
   : LTE NV
*****************************************************************************/
typedef struct
{
    VOS_UINT32          ulLteAptTotalSwitch;
    VOS_UINT32          ulRsv;
}LTE_APT_COMMONCTRL_STRU;

#define     LTE_MTC_ABAN_BAND_NUM_MAX   (8)
#define     LTE_MTC_ABAN_PLMN_NUM_MAX   (8)
#define     LTE_MTC_SPAC_BAND_NUM_MAX   (8)

typedef struct
{
    VOS_UINT32                          ulMcc;              /* MCC,3 bytes      */
    VOS_UINT32                          ulMnc;              /* MNC,2 or 3 bytes */
} LRRC_PLMN_ID_STRU;

/*  band NV */
typedef struct
{
    LRRC_PLMN_ID_STRU                 stPlmnID;
    VOS_UINT32                       ulBandNum;                                    /* Band */
    VOS_UINT8                        ucBand[LTE_MTC_ABAN_BAND_NUM_MAX];            /* Band */
} LTE_MTC_PLMN_ABAN_BAND_LIST;

/*Delete FDD Band */
typedef struct
{
    VOS_UINT8                     ucSwitchFlag;                                   /* ,0 close; 1 open */
    VOS_UINT8                     ucReserved;
    VOS_UINT16                    usMcc;                                          /*  460  */
}LTE_CUSTOM_MCC_INFO_STRU;

extern  LTE_CUSTOM_MCC_INFO_STRU g_stLRrcDelFddBand;
/*Delete FDD Band */

typedef struct
{
    VOS_UINT32                        ulPlmnNum;
    LTE_MTC_PLMN_ABAN_BAND_LIST       astAbandPlmnList[LTE_MTC_ABAN_PLMN_NUM_MAX]; /* PlmnBandList */
} LTE_MTC_ABANDON_EUTRA_BAND_SCAN_STRU;


/* band  */
typedef struct
{
     VOS_UINT8                      ucBand;                                        /* Band */
     VOS_UINT8                      aucRsv[3];                                     /**/
     VOS_UINT16                     usFreqBegin;
     VOS_UINT16                     usFreqEnd;
}LTE_MTC_SPAC_BAND_CONFIG_LIST;

typedef struct
{
     VOS_UINT32                     ulBandNum;
     VOS_UINT32                     ulSpacBandSwitch;                               /* 0 close; 1 open*/
     LTE_MTC_SPAC_BAND_CONFIG_LIST  astSpacBandList[LTE_MTC_SPAC_BAND_NUM_MAX];     /* Band */
} LTE_MTC_SPAC_BAND_SCAN_CONFIG_STRU;
extern LTE_MTC_ABANDON_EUTRA_BAND_SCAN_STRU g_stAbandEutraBandInfo;
extern LTE_MTC_SPAC_BAND_SCAN_CONFIG_STRU   g_stSpacBandInfo;

/* MTC NOTCH add begin  */
/*****************************************************************************
     : LTE_MTC_NOTCH_FEATURE_STRU
   :
 ASN.1 :
   : aucRcve[0]S
*****************************************************************************/
typedef struct
{
     VOS_UINT16                     usSwitchFlag;                                   /*  */
     VOS_UINT8                      aucRcve[2];                                     /*  */
} LTE_MTC_NOTCH_FEATURE_STRU;

/* MTC NOTCH add end  */
/*****************************************************************************
     : LTE_RRC_THRESHOLD_STRU
   :
 ASN.1 :
        ulCdrxPeriod:Balong
        lGeranBasiclag: Balong
        lGeranBasiStartThres:Balong
        ulCdrxFilterSwitch:Balong
        ulAbandinFristItraMeasFlg:0:1:Balong:0.
        ulTdsT315Len:  T315Balong0 5.
        ulHrpdIdleMeasIndInterTime:hrpdInd.Balong:200.
        ulHrpdConnMeasIndInterTime:hrpdInd.Balong:200.
        ultimerLrrcWaitCdmaCnfLen:hrpdIND,.Balong:30000.
        ulTReselectUtran: 3G.:Balong0 60.
        ulTReselectGsm: 2G.:Balong0 50.
   : LTE RRC 
*****************************************************************************/
/* begin:Abandon Frist Itra Meas Result */
typedef struct
{
    VOS_UINT32          ulCdrxPeriod;
    VOS_INT32           lGeranBasiclag;
    VOS_INT32           lGeranBasiStartThres;
    VOS_UINT32          ulCdrxFilterSwitch;
    VOS_UINT32          ulAbandinFristItraMeasFlg;
    VOS_UINT32          ulTdsT315Len;
    VOS_UINT32          ulHrpdIdleMeasIndInterTime;
    VOS_UINT32          ulHrpdConnMeasIndInterTime;
    VOS_UINT32          ultimerLrrcWaitCdmaCnfLen;
    VOS_UINT32          ulTReselectUtran;
    VOS_UINT32          ulTReselectGsm;
    /* mod for FreqSearchEnhance begin */
    VOS_UINT32          ulFreqSearchEnhanceFlag;
    VOS_UINT32          ulFreqSearchEnhanceSrchCnt;
    VOS_UINT32          ulFreqSearchEnhanceSrchThres;
    /* mod for FreqSearchEnhance end */
    VOS_UINT32          ulTReselectCdma;
    /*DTS2015030702005,add by l00195322,GURATLLTEIND-1/8 dB*/
    VOS_UINT32          ulBgsL2GuSearchIndThreshFlag;
    VOS_INT32           lBgsL2GuSearchIndThresh;
    /*DTS2015030702005,add by l00195322,GURATLLTEIND-1/8 dB*/
    VOS_UINT32          ulCampFailRetryNum;
    VOS_INT32           lDelfaultqQualMin;/*SIB1qQualMin*/
    /* mod for Balong CL begin */
    VOS_UINT32          ulWaitCasReselCnfLen;    /* CL LTECDMACNF */
    VOS_UINT32          ulWaitCasRedirectCnfLen;    /* CL LTECDMACNF */
    /* mod for Balong CL end */
    VOS_UINT32          ulAcBarStudyTimeLen;           /*acbars*/
    VOS_UINT32          ulAcBarNormalBarTimeLen;           /*BARacbars*/
    VOS_UINT32          ulAcNotBarNumforMoSignal;      /*ulAcBarStudyTimeLenulAcNotBarNumforMoSignalBar*/
    VOS_UINT32          ulAcNotBarNumforMoData;        /*ulAcBarStudyTimeLenulAcNotBarNumforMoDataBar*/
    VOS_UINT32          ulAcNotBarNumforMoCsfb;        /*ulAcBarStudyTimeLenulAcNotBarNumforMoCsfbBar*/
    /* Begin: 20150801 */
    VOS_UINT32          ulFrRecvSibRsrpFlag;   /* GU FR LTErsrp */
    VOS_UINT32          ulFrRecvSibRsrqFlag;   /* GU FR LTErsrp*/
    VOS_UINT32          ulFrRecvSibRsrq;       /* GU FR LTErsrp,12 - 40, */
    VOS_UINT32          ulFrRecvSibRsrp;       /* GU FR LTErsrp,100 - 140, */
    VOS_UINT32          ulStopIratRedirTimerFlg;  /*FRFlg */
    /* End: 20150801 */
    VOS_INT32           lRsrqMinforResel;

}LTE_RRC_THRESHOLD_STRU;
extern VOS_UINT32   g_ulAbandinFristItraMeasFlg;
/* end:Abandon Frist Itra Meas Result */

extern VOS_UINT8    g_ucTReselectUtran;
extern VOS_UINT8    g_ucTReselectGsm;
extern VOS_UINT8    g_ucTReselectCdma;
extern VOS_UINT16    g_usNoRptSecondCellThres;

#define         MAX_IRAT_TDS_UE_CAPABILITY_LENGHT           (100)
typedef struct
{
     VOS_UINT16                     usSwitchFlag;                                   /* : NVue*/
     VOS_UINT16                     usLength;                                       /* UE */
     VOS_UINT8                      aucCapInfo[MAX_IRAT_TDS_UE_CAPABILITY_LENGHT];                                /* UE */
} LTE_IRAT_TDS_UE_CAPABILITY_STRU;
/*BEGIN DTS2014041603793 c00203521 modify for B28*/


/*****************************************************************************
     : LRRC_NV_EXT_BAND_LIST_STRU
   :
 ASN.1 :
   : NV
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usBandInd;      /* BAND */
    VOS_UINT16                          usScellBandInd;      /* ScellBAND */

	/* Band */
    LRRC_NV_SUPPORT_BAND_LIST_STRU      astBandInfoWithBandWidth[6];/*RRC_BAND_WIDTH_BUTT*/
}LRRC_NV_EXT_BAND_LIST_STRU;

/*****************************************************************************
     : LTE_RRC_EXTBANDINFO_WITH_BANDWIDTH_STRU
   :
 ASN.1 :
   : UENV
*****************************************************************************/
typedef struct
{
    VOS_UINT8          ucActive;
    VOS_UINT8          ucScellEnable;
    VOS_UINT16         usBandCount;
    LRRC_NV_EXT_BAND_LIST_STRU          stCandBandsInfo[8]; /*8*/
}LTE_RRC_EXTBANDINFO_WITH_BANDWIDTH_STRU;

/*END DTS2014041603793 c00203521 modify for B28*/
/*****************************************************************************
     : LRRC_NV_DSDS_CONFIG_STRU
   :
 ASN.1 :
   : DSDSNV
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usRsv0;
    VOS_UINT16                          usDsdsPagingTimeLen;
    VOS_UINT16                          usDsdsShrtOccpRfRcverTimeLen;
    VOS_UINT16                          usRsv;
    VOS_UINT32                          ulFrRelDelaytimer;
    VOS_UINT32                          ulRsv1;
    VOS_UINT32                          ulRsv2;
    VOS_UINT32                          ulRsv3;
}LRRC_NV_DSDS_CONFIG_STRU;
/*****************************************************************************
     : LTE_RRC_DAM_PARA_STRU
   :
 ASN.1 :
   : LRRCDAM
*****************************************************************************/
typedef struct
{
    VOS_UINT32                           ulDamCRRCMaxCnt;           /* LRRC DAMCRRC.1-60,5 */
    VOS_UINT32                           ulDamCellBarTimerLenth;    /* LRRC DAMbar.1-60(),6 */
}LRRC_DAM_PARA_STRU;

/*****************************************************************************
    :PS_NV_DAM_CONFIG_PARA_STRU
    :DAMNV
*****************************************************************************/
typedef struct
{
    VOS_UINT32                           bitOpLrrcDamSwitch:1;
    VOS_UINT32                           bitOpRsv          :31;
    VOS_UINT32                           ulCService;         /* 1-605   */
    LRRC_DAM_PARA_STRU                   stLrrcDamPara;      /* LRRCDAM       */
    NAS_DAM_CONFIG_PLMN_PARA             stDamConfigPlmnPara;/* DAM         */

    /* enable lte01 */
    VOS_UINT8                            ucEnableLteTrigPlmnSearchFlag;

    /* DAM disbale LTEDAMLTETRUEFALSE */
    VOS_UINT8                            ucAddDamPlmnInDisablePlmnWithRatListFlag;

    VOS_UINT8                            ucDamFlag[2];       /* DAM10[0] */

}PS_NV_DAM_CONFIG_PARA_STRU;

/*****************************************************************************
    :LRRC_DRX_ASSIST_INFO_R11_STRU
    :IDCNV
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           enDrxOffsetR11Flg;                      /*PS_FALSE:PS_TRUE:*/
    VOS_UINT8                           enDrxCycleLenR11;
    VOS_UINT8                           ucDrxOffsetR11;                         /* optional */    /*(0..255)*/
    VOS_UINT8                           enDrxActTimeR11;
}LRRC_DRX_ASSIST_INFO_R11_STRU;

/*****************************************************************************
    :LRRC_IDC_SUBFRAME_PATTERN_R11_STRU
    :IDCNV
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucChoice;                               /*1:ucSubframePatternFddR11,2:Tdd SubframeCfg0R11,3:usSubframeCfg15R11,4:SubframeCfg6R11*/

#define SUBFRAME_PATTERN_FDD_CFG        1
#define SUBFRAME_PATTERN_TDD_CFG_0      2
#define SUBFRAME_PATTERN_TDD_CFG_1_5    3
#define SUBFRAME_PATTERN_TDD_CFG_6      4

    VOS_UINT8                           ucSubframePatternFddCfgR11;
    VOS_UINT8                           aucSubframeTddCfg0R11[LRRC_MAX_NUM_SUBFRAME_CONFIG0_R11];
    VOS_UINT8                           usRsv;
    VOS_UINT16                          usSubframeTddCfg15R11;
    VOS_UINT8                           ausRsv1[2];
    VOS_UINT8                           aucSubframeTddCfg6R11[LRRC_MAX_NUM_SUBFRAME_CONFIG6_R11];
}LRRC_IDC_SUBFRAME_PATTERN_R11_STRU;

/*****************************************************************************
    :LRRC_IDC_SUBFRAME_PATTERN_LIST_R11_STRU
    :IDCNV
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usCnt;    /*(0, 1..UU_MAX_NUM_IDC_SUBFRAME_PATTERNLIST_R11)*/
    VOS_UINT16                          usRsv;
    LRRC_IDC_SUBFRAME_PATTERN_R11_STRU  aItem[LRRC_MAX_NUM_IDC_SUBFRAME_PATTERNLIST];
}LRRC_IDC_SUBFRAME_PATTERN_LIST_R11_STRU;

/*****************************************************************************
    :LRRC_TDM_ASSIST_INFO_R11_STRU
    :IDCNV
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                 ucChoice;                         /*1:stDrxAssistInfoR11,2:stIdcSubframePatternListR11*/
    VOS_UINT8                                 aucReserved[3];

    LRRC_DRX_ASSIST_INFO_R11_STRU             stDrxAssistInfoR11;
    LRRC_IDC_SUBFRAME_PATTERN_LIST_R11_STRU   stIdcSubframePatternListR11;
}LRRC_TDM_ASSIST_INFO_R11_STRU;

/*****************************************************************************
    :PS_NV_IDC_CONFIG_PARA_STRU
    :IDCNV
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                bitTdmAssistInfoR11Present :1;
    VOS_UINT32                                bitSpare                   :31;

    VOS_UINT8                                 ucInterferenceDirR11;             /*0:EUTRA,1:OTHER,2:BOTH*/
    VOS_UINT8                                 ucRsv[3];
    LRRC_TDM_ASSIST_INFO_R11_STRU             stTdmAssistInfoR11;
}PS_NV_IDC_CONFIG_PARA_STRU;

/*****************************************************************************
     : LRRC_IDC_UL_CA_PARA_STRU
   : LTE&WIFI

  1.       : 2015522
           : l00277963
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT32    bitGpsR11Present                            : 1;
    VOS_UINT32    bitGlonassR11Present                        : 1;
    VOS_UINT32    bitBdsR11Present                            : 1;
    VOS_UINT32    bitGalileoR11Present                        : 1;
    VOS_UINT32    bitWlanR11Present                           : 1;
    VOS_UINT32    bitBluetoothR11Present                      : 1;
    VOS_UINT32    bitSpare                                    : 26;

    VOS_UINT16    usTxBegin;
    VOS_UINT16    usTxEnd;
    VOS_UINT16    usRxBegin;
    VOS_UINT16    usRxEnd;
} LRRC_IDC_UL_CA_PARA_STRU;

/*****************************************************************************
     : PS_NV_IDC_UL_CA_PARA_LIST_STRU
   : LTE&WIFI

  1.       : 2015522
           : l00277963
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usCnt;
    VOS_UINT16                          usRsv;
    LRRC_IDC_UL_CA_PARA_STRU            aItem[LRRC_MAX_NUM_IDC_UL_CA_PARALIST];
} PS_NV_IDC_UL_CA_PARA_LIST_STRU;


/*****************************************************************************
    :PS_NV_OTDOA_ADDITIONAL_NCELL_INFO_STRU
    :otdoaNV
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                bitAddOtdoaNeighbourCellInfoListFlag :1;
    VOS_UINT32                                bitUeRxTxTimeDiffMeasPresent         :1;
    VOS_UINT32                                bitSpare                             :30;

}PS_NV_OTDOA_ADDITIONAL_NCELL_INFO_STRU;

/*****************************************************************************
    :LRRC_ACCFAILBAR_CONFIG_STRU
    :barNV
*****************************************************************************/
typedef struct
{
    VOS_UINT16   usAccFailEnableFlg;       /**/
    VOS_UINT16   usOrigAccFailTimeLimit;   /*s*/
    VOS_UINT16   usOrigAccFailCntLimit;    /**/
    /*usOrigAccFailTimeLimitusOrigAccFailCntLimitBar*/

    VOS_UINT16   usRsv1;


    VOS_UINT16   usBarStepCnt;             /*BarLRRC_ACCFAIL_MAX_BAR_STEP*/
    VOS_UINT16   ausBarTimeLen[LRRC_ACCFAIL_MAX_BAR_STEP]; /*s*/

    VOS_UINT16   usQImproveRelBarTrhesh;   /*QBar*/
    VOS_UINT16   usPImproveRelBarTrhesh;   /*PBar*/
    VOS_UINT16   usTimeLenBetweenBarStep;  /*Bar0*/

    VOS_UINT16   usRsv2;
    VOS_UINT16   usRsv3;
    VOS_UINT16   usRsv4;
    VOS_UINT32   ulRsv;
}LRRC_NV_ACCFAILBAR_CONFIG_STRU;
/* Begin: 2015/5/6 sbm */
/*****************************************************************************
     : LRRC_SBM_CUSTOM_DUAL_IMSI_STRU_NEW
   : imsiMCC
*****************************************************************************/

typedef struct
{
    VOS_UINT8                           ucSbmCustomSrchFlg; /*  SBm  LTEIMSI*/
    VOS_UINT8                           aucReserve[3];          /*  */
    VOS_UINT32                          aulSbmSupBandInJapan[2];         /* band1bandUEband */
    VOS_UINT32                          aulEmSupBandInJapan[2];          /* EMband1bandUEband */
    VOS_UINT32                          aulOtherOperateSupBandInJapan[2];/* band1bandUEband */
    VOS_UINT32                          aulSupBandOutJapan[2];           /* band,1bandUEband */
} LRRC_SBM_CUSTOM_DUAL_IMSI_STRU_NEW;
/* End: 2015/5/6 sbm */

/*****************************************************************************
     : LRRC_NV_PLMN_CAND_FREQ_PRIOR_ENUM_UINT8
   :
 ASN.1 :
   : TDDFDD
*****************************************************************************/
typedef enum
{
    LRRC_CELL_SEARCH_PRIOR_NO_PRIOR   = 0,
    LRRC_CELL_SEARCH_PRIOR_TDD_PRIOR  = 1,
    LRRC_CELL_SEARCH_PRIOR_FDD_PRIOR  = 2,
} LRRC_NV_PLMN_CAND_FREQ_PRIOR_ENUM;
typedef VOS_UINT8   LRRC_NV_PLMN_CAND_FREQ_PRIOR_ENUM_UINT8;

/*****************************************************************************
     : LRRC_PLMN_CAND_INFO_TYPE_ENUM
   :
 ASN.1 :
   : 
*****************************************************************************/
typedef enum
{
    LRRC_PLMN_CAND_INFO_FIXTBL_TYPE        = 0,
    LRRC_PLMN_CAND_INFO_DYNTBL_TYPE        = 1,
    LRRC_PLMN_CAND_INFO_TYPE_BUTT          = 2,
} LRRC_PLMN_CAND_INFO_TYPE_ENUM;
typedef VOS_UINT8   LRRC_PLMN_CAND_INFO_TYPE_ENUM_UINT8;

/*****************************************************************************
     : LRRC_NV_EACH_PLMN_CAND_INFO_STRU
   :
 ASN.1 :
   : PLMN
*****************************************************************************/
typedef struct
{
    LRRC_LNAS_PLMN_ID_STRU  stNasFormatPlmn;
    VOS_UINT16              ausPlmnBand[LRRC_SINGLE_CAND_PLMN_MAX_BAND];
    VOS_UINT32              aulEarfcn[LRRC_SINGLE_CAND_PLMN_MAX_FRQNUM];

    VOS_UINT32              ucBitSwitch              :1;/* plmn0      01*/
    VOS_UINT32              ucBitW2LSrch             :3;/* LW2L1    0+1*/
    VOS_UINT32              ucBitRedirSrch           :3;/* 0        0+1*/
    VOS_UINT32              ucBitReestSrch           :3;/* 1        0+1*/
    VOS_UINT32              ucBitOosSrch             :3;/* 00+126*/
    VOS_UINT32              ucBitAsSrch              :3;/* AS0        0+1conn->idle*/
    VOS_UINT32              ucBitAddMFreq            :1;/* ,,0,1,0*/
    VOS_UINT32              ucBitRsv4                :1;
    VOS_UINT32              ucBitRsv5                :1;
    VOS_UINT32              ucBitRsv6                :1;
    VOS_UINT32              ucBitRsv7                :1;
    VOS_UINT32              ucBitRsv8                :1;
    VOS_UINT32              ucBitRsv9                :1;
    VOS_UINT32              ucBitRsv10               :1;
    VOS_UINT32              ucBitRsv11               :2;
    VOS_UINT32              usBitRsv0                :6;

    VOS_INT16               sThresh0;                    /**/
    VOS_INT16               sThresh1;                    /**/
}LRRC_NV_SINGLE_PLMN_CAND_INFO_STRU;

/*****************************************************************************
     : LRRC_NV_CAND_FREQ_INFO_WITHPLMN
   :
 ASN.1 :
   : PLMN
*****************************************************************************/
typedef struct
{
    LRRC_LNAS_PLMN_ID_STRU  stNasFormatPlmn;
    VOS_UINT16              usBand;
    VOS_UINT8               ucRsv0;
    VOS_UINT8               ucRsv1;
    VOS_UINT16              usRsv;
    VOS_UINT16              usRsv1;
    VOS_UINT32              ulEarfcn;
}LRRC_NV_CAND_FREQ_INFO_WITHPLMN_STRU;

/*****************************************************************************
     : LRRC_NV_FIX_MUTI_PLMNS_CAND_INFO_STRU
   :
 ASN.1 :
   : PLMNT
*****************************************************************************/
typedef struct
{
    VOS_UINT16              ulValidNum;
    VOS_UINT8               ucCandInfoForEplmn;      /*Eplmn*/
    VOS_UINT8               ucRsv1;
    VOS_UINT16              sRsv0;
    VOS_UINT16              sRsv1;

    VOS_UINT16              usRsv1;
    VOS_UINT16              usRsv2;

    VOS_UINT32              ucBitW2LSrch                  :3;/* LW2L1    0+1*/
    VOS_UINT32              ucBitRedirSrch                :3;/* 0        0+1*/
    VOS_UINT32              ucBitReestSrch                :3;/* 1        0+1*/
    VOS_UINT32              ucBitAsSrch                   :3;/* AS0        0+1conn->idle*/
    VOS_UINT32              ucBitOosSrch                  :3;/* 0 0+126*/
    VOS_UINT32              ucBitRsv5                     :1;
    VOS_UINT32              ucBitRsv6                     :1;
    VOS_UINT32              ucBitRsv7                     :1;
    VOS_UINT32              ucBitRsv8                     :1;
    VOS_UINT32              ucBitRsv9                     :2;
    VOS_UINT32              ucBitRsv10                    :3;
    VOS_UINT32              ucBitRsv11                    :4;
    VOS_UINT32              usBitRsv0                     :4;

    VOS_UINT32              ulRsv;

    LRRC_NV_SINGLE_PLMN_CAND_INFO_STRU  astPlmnCand[LRRC_CAND_PLMNFREQ_MAX_PLMNNUM];
}LRRC_NV_FIX_MUTI_PLMNS_CAND_INFO_STRU;

/*****************************************************************************
     : LRRC_NV_DYNAMIC_MUTI_PLMNS_CAND_INFO_STRU
   :
 ASN.1 :
   : PLMN
*****************************************************************************/
typedef struct
{
    VOS_UINT8               ucRsv0;
    VOS_UINT8               ucRsv1;
    VOS_UINT16              usRsv0;
    VOS_UINT16              sRsv0;
    VOS_UINT16              sRsv1;

    VOS_UINT16              usRsv1;
    VOS_UINT16              usRsv2;

    VOS_UINT32              ucBitRsv1                :1;  /* ,OOS band*/
    VOS_UINT32              ucBitRsv2                :1;  /* ,OOS*/
    VOS_UINT32              ucBitRsv3                :1;  /* */
    VOS_UINT32              ucBitRsv                 :1;  /* */
    VOS_UINT32              ucBitRsv4                :1;
    VOS_UINT32              ucBitRsv5                :1;
    VOS_UINT32              ucBitRsv6                :1;
    VOS_UINT32              ucBitRsv7                :1;
    VOS_UINT32              ucBitRsv8                :1;
    VOS_UINT32              ucBitRsv9                :1;
    VOS_UINT32              ucBitRsv10               :4;
    VOS_UINT32              ucBitRsv11               :4;
    VOS_UINT32              usBitRsv0                :10;

    VOS_UINT32              ulRsv;

    LRRC_NV_SINGLE_PLMN_CAND_INFO_STRU      astPlmnCand[LRRC_CAND_PLMNFREQ_MAX_PLMNNUM];
}LRRC_NV_DYNAMIC_MUTI_PLMNS_CAND_INFO_STRU;

/*****************************************************************************
     : LRRC_NV_LATEST_CAND_FREQ_INFO_WITHPLMN_STRU
   :
 ASN.1 :
   : PLMN:
             1.
             2.
             3.
*****************************************************************************/
typedef struct
{
    VOS_UINT8               ucAddMeasFreq; /* ,,1,0,0*/
    VOS_UINT8               ucRsv1;
    VOS_UINT16              usRsv1;

    VOS_UINT16              sRsv0;
    VOS_UINT16              sRsv1;

    VOS_UINT32              ulRsv;

    LRRC_NV_SINGLE_PLMN_CAND_INFO_STRU    stLatestServPlmnCandFreq; /**/
    LRRC_NV_CAND_FREQ_INFO_WITHPLMN_STRU  astLastestCandFreq[LRRC_LATEST_MAX_CAND_FREQ_NUM];    /*PLMN*/
}LRRC_NV_LATEST_CAND_FREQ_INFO_WITHPLMN_STRU;

/*****************************************************************************
     : LRRC_NV_CELL_GLOBAL_ID_STRU
   :
 ASN.1 :
   : EUTRA CELL GLOBAL CELL ID
*****************************************************************************/
typedef struct
{
    LRRC_LNAS_PLMN_ID_STRU              stPlmnId;                    /* SIB1PLMNPLMN */
    VOS_UINT32                          ulCellIdentity;
} LRRC_NV_CELL_GLOBAL_ID_STRU;

/*Begin: add by CSG */
/*****************************************************************************
     : LRRC_NV_CSG_NEIGH_MACRO_CELL_INFO_STRU
   :
 ASN.1 :
   : CSGECGI
*****************************************************************************/
typedef struct
{
    LRRC_NV_CELL_GLOBAL_ID_STRU        astCellGlobalId[LRRC_CSG_NEIGH_MACRO_CELL_NUM];
}LRRC_NV_CSG_NEIGH_MACRO_CELL_INFO_STRU;

/*****************************************************************************
     : LRRC_NV_CSG_CAMPED_CELL_INFO_STRU
   :
 ASN.1 :
   : CSG
*****************************************************************************/
typedef struct
{
    VOS_UINT16                  usPhyCellId;
    VOS_UINT16                  usBandInd;
    VOS_UINT32                  ulFreqInfo;
    VOS_UINT32                  ulCsgId;

    LRRC_LNAS_PLMN_ID_STRU      stCampedPlmn;        /* PLMNCGIPLMNPLMN */
    LRRC_NV_CELL_GLOBAL_ID_STRU stCellGlobalId;      /* CGI */

    VOS_UINT32                  ulNeighMacroCellNum;    /* CSGCSG */
}LRRC_NV_CSG_CAMPED_CELL_INFO_STRU;

/*****************************************************************************
     : LRRC_NV_CSG_HISTORY_CAMPED_INFO_STRU
   :
 ASN.1 :
   : CSGUEPLMN
*****************************************************************************/
typedef struct
{
    VOS_UINT32                         ulCsgCampedCellNum;    /*  */
    /* UECSG */
    LRRC_NV_CSG_CAMPED_CELL_INFO_STRU  astCsgCampedCellInfo[LRRC_CSG_HISTORY_CAMPED_CELL_NUM];
}LRRC_NV_CSG_HISTORY_CAMPED_INFO_STRU;

/*****************************************************************************
     : LRRC_NV_CSG_NEIGH_MACRO_CELL_PRAT_INFO_STRU
   :
 ASN.1 :
   : LRRC_NV_CSG_NEIGH_MACRO_CELL_PRAT_INFO_STRU
*****************************************************************************/
typedef struct
{
    LRRC_NV_CSG_NEIGH_MACRO_CELL_INFO_STRU       astNeighborMacroCell[LRRC_CSG_HISTORY_CAMPED_CELL_PART_NUM];
}LRRC_NV_CSG_NEIGH_MACRO_CELL_PRAT_INFO_STRU;

/*****************************************************************************
     : LRRC_NV_CSG_HISTORY_INFO_STRU
   :
 ASN.1 :
   : CSG:CSG LTELTE
*****************************************************************************/
typedef struct
{
    /* CSG */
    LRRC_NV_CSG_HISTORY_CAMPED_INFO_STRU         stCampedCsgCell;
    /* CSG  */
    LRRC_NV_CSG_NEIGH_MACRO_CELL_INFO_STRU       astNeighborMacroCell[LRRC_CSG_HISTORY_CAMPED_CELL_NUM];
}LRRC_NV_CSG_HISTORY_INFO_STRU;
/*End: add by CSG */

/*****************************************************************************
     : RRC_CSEL_MOBILITY_PARAM_STRU
   :
 ASN.1 :
   : 
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usHighTReselectionSf;                   /*  */
    VOS_UINT16                          usMediumTReselectionSf;                 /*  */
    VOS_INT16                           sHighQHystSf;                           /* QHyst */
    VOS_INT16                           sMediumQHystSf;                         /* QHyst */
} RRC_CSEL_MOBILITY_PARAM_STRU;

/*****************************************************************************
     : LRRC_NV_CSG_ASF_PARAMETERS_STRU
   :
 ASN.1 :
   : CSG ASF
*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                  enEnableIdleAsf;                        /* LTE IDLE ASF */
    PS_BOOL_ENUM_UINT8                  enAvoidCsgPingPongResel;                /* CSG */
    VOS_UINT16                          usMeasBandWidth;                        /*  */

    PS_BOOL_ENUM_UINT8                  enPresenceAntennaPort1;                 /*  */
    VOS_UINT8                           ucNeighCellCfg;
    VOS_INT16                           sQOffset;                               /* QHyst */

    VOS_UINT16                          usTReselection;                         /*  ms */
    VOS_INT16                           sQRxLevMin;

    VOS_INT16                           sPMax;
    VOS_INT16                           sPCompensation;                         /*  P-Max  UE Max Tx power  PCompensation */

    RRC_CSEL_MOBILITY_PARAM_STRU        stMobilityParam;                        /*  */

    VOS_INT16                           sQqualMin;                              /* SRSRQ */
    /*  :
            1ASFusIdleAsfMaxDiffToBest
            usIdleAsf_MaxDifferToBest0
            2ASF
    */
    VOS_UINT16                          usIdleAsfMaxDiffToBest;

    VOS_INT16                           sRsrqQualityThre;                       /* ASFLTE RSRQ */
    VOS_UINT16                          usBaseLengthOfIdleAsfTimer;             /* IdleAsfTimer */

    VOS_UINT16                          usStepSizeOfIdleAsfTimer;               /* IdleAsfTimer */
    /* IdleAsfTimer(usBaseLengthOfIdleAsfTimer + usStepSizeOfIdleAsfTimer *  ucMaxStepOfIdleAsfTimer) */
    VOS_UINT8                           ucMaxStepOfIdleAsfTimer;                /* IdleAsfTimer */
    /* CSG(N * ) */
    VOS_UINT8                           ucNForCsgAddMeasureTimer;               /* CSGN */
    VOS_UINT16                          usConnAsfTimerLen;                  /* 5 */
    /* ,1,obj */
    PS_BOOL_ENUM_UINT8                  enEnableConnAsfInterMeas;
    /* AT&T
         In the case of a CSG Aware UICC:
            o ASF shall not be triggered if the EF-Operator CSG Lists is empty i.e. does not contain any CSG IDs
            o ASF shall not be triggered when the UE is registered on a PLMN that is not listed as a PLMN in the
                CSG Information TLV object of the EF-Operator CSG Lists
            o ASF shall only be triggered when the UE is registered on a PLMN that is listed as a PLMN in the
                CSG Information TLV object of the EF-Operator CSG Lists
         In the case of a CSG Not Aware UICC:
            o ASF shall not be triggered if the UE based allowed CSG List is empty i.e. does not contain any CSG IDs
            o ASF shall not be triggered when the UE is registered on a PLMN that is not a PLMN of a fingerprinted CSG ID
            o ASF shall only be triggered when the UE is registered on a PLMN that is a PLMN of a fingerprinted CSD ID
    */
    PS_BOOL_ENUM_UINT8                  enAttAsfPlmnLimit;                      /* AT&T ASF */
}LRRC_NV_CSG_ASF_PARAMETERS_STRU;


/*****************************************************************************
     : TLRRC_NV_CTRL_SUBFUNC_COMM_STRU
   :
 ASN.1 :
   : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8               ucSwitch;
    VOS_UINT8               ucRsv1;
    VOS_UINT16              usRsv0;
    VOS_UINT16              usRsv1;
    VOS_UINT16              usRsv2;
    VOS_UINT16              usRsv3;
    VOS_UINT16              usRsv4;
    VOS_UINT16              usRsv5;
    VOS_UINT16              usRsv6;
    VOS_UINT32              ulRsv0;
}TLRRC_NV_CTRL_SUBFUNC_COMM_STRU;

/*****************************************************************************
     : LRRC_NV_RESTRICTED_BAND_STRU
   :
 ASN.1 :
   : Band NV
*****************************************************************************/
typedef struct
{
    VOS_UINT32              aulBand[LRRC_RESTRICTED_BAND_ARRAY_NUM];
}LRRC_NV_RESTRICTED_BAND_STRU;

/*****************************************************************************
     : LRRC_NV_CELL_SELECT_RSSI_SORT_CTRL
   :
 ASN.1 :
   : NV
*****************************************************************************/
typedef struct
{
    VOS_UINT8               ucValidFlg;
    VOS_UINT8               ucEnable;
    VOS_INT16               sRssiHighPriThre;
    VOS_INT16               sRssiHighPriDiffThre;
    VOS_UINT16              usSortFreqMaxNum;
    VOS_UINT16              usRedirectSortNum;
    VOS_UINT16              usPssRatioThres;
    VOS_INT16               sHighPssRatioRssiThre;  /* PSS RATIORSSI, */
    VOS_UINT16              usHighPssRatioRssiDiffThres;
    VOS_INT32               sHighPssRatioLowRssiThre;
    VOS_UINT16              usNoNoisePssRatioThres; /* PssRatio */
    VOS_UINT16              usNoNoisePssRatioDiffThres;/* PssRatioRssiPssRatio */
    VOS_INT16               sFddSrchFristRssiThre;/*FDDrssi*/
    VOS_UINT16              sFddSrchFristPssRatioThre;/*FDDPssRatio*/
    VOS_UINT32              ulRsv0;
    VOS_UINT32              ulRsv1;
}LRRC_NV_CELL_SELECT_RSSI_SORT_CTRL;

/*****************************************************************************
     : LRRC_NV_CELL_SELECT_RSSI_SORT_CTRL
   :
 ASN.1 :
   : CSG
*****************************************************************************/
typedef struct
{
    VOS_UINT8               ucValidFlg;
    VOS_UINT8               ucRsv0;
    VOS_INT16               sRsv0;
    VOS_INT16               sRsv1;
    VOS_UINT16              usCsgListNeighNum;    /* CSG */
    VOS_UINT16              usCsgSpecNeighNum;    /* CSG */
    VOS_UINT16              usRsv0;
    VOS_UINT16              usRsv1;
    VOS_UINT16              usRsv2;
    VOS_UINT32              ulRsv3;
}LRRC_NV_CSG_FEATURE_CTRL;

/*****************************************************************************
     : LRRC_NV_INTER_OPT_FREQENTLY_CTRL
   :
 ASN.1 :
   : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8               ucTotalSwitch;                   /*  */
    VOS_UINT8               ucComplicatedIntOptSwich;        /*  */
    VOS_INT16               sRsrpHighQualityThre;            /* LTE RSRP */
    VOS_INT16               sRsrqHighQualityThre;            /* LTE RSRQ */
    VOS_INT16               sGutHighQualityThre;             /* G RSSI/WT RSCP */
    VOS_INT16               sEneryDiffThre;                 /* RSRP/RSSI/RSCP */
    VOS_INT16               sRsrqDiffThre;                  /* RSRQ */
    VOS_UINT16              usBarOptTimerLen;                /*  */
    VOS_UINT16              usEvalueTimerLen;                /*  */
    VOS_UINT16              usInvalidTimerLenTwoOpt;         /*  */
    VOS_UINT16              usTwoCellOptTimerLen;            /* usTwoCellOptTimerLen4 */
    VOS_UINT16              usIratTwoCellOptTimerLen;        /* usIratTwoCellOptTimerLen3 */
    VOS_UINT16              enReslParaAdjustToCtlRselFreq;   /*  */
    VOS_UINT16              enReslParaAdjustHighSpeed;       /*  */
    VOS_INT16               sIntraReselMinDiff;             /* 2db */
    VOS_UINT16              usReselTmrMin;                   /* ReselTmr,ms */
    VOS_UINT16              ulRsv0;
    VOS_UINT32              ulRsv1;
    VOS_UINT16              ulRsv2;
    VOS_UINT16              ulRsv3;
}LRRC_NV_INTER_OPT_FREQENTLY_CTRL;

/*begin,add for CSFB B1 REPORT, l001953221*/
/*****************************************************************************
     : TLRRC_NV_LOC_B1_SWITCH_AND_THRETH
   :
 ASN.1 :
   : CSFBB1
*****************************************************************************/
typedef struct
{
    VOS_UINT8               ucCsfbB1Switch;
    VOS_UINT8               ucRsv1;
    VOS_INT16               sB1UtraRscp;         /* B1UTRARSCP1dB*/
    VOS_INT16               sB1UtraEcn0;         /* B1UTRAEcn00.5dB*/
    VOS_INT16               sB1GeranRssi;        /* B1GERANRSSI1dB*/
    VOS_UINT16              usRsv0;
    VOS_UINT16              usRsv1;
    VOS_UINT16              usRsv2;
    VOS_UINT16              usRsv3;
    VOS_UINT32              ulRsv0;
}LRRC_NV_PRIVATE_B1_SWITCH_AND_THRETH_STRU;
/*end,add for CSFB B1 REPORT, l001953221*/

/*****************************************************************************
     : LRRC_NV_VOLTE_A2B2_SWITCH_AND_THRETH_STRU
   :
 ASN.1 :
   : VOLTEA2B2
*****************************************************************************/
typedef struct
{
    VOS_UINT8               ucVolteA2Switch;     /* VOLTEA2 */
    VOS_UINT8               ucVolteB2Switch;     /* VOLTEB2 */
    VOS_INT16               sA2RsrpThres;        /* A2 RSRP, 1dB*/
    VOS_INT16               sA2RsrqThres;        /* A2 RSRQ, 1dB*/
    VOS_INT16               sB2RsrpThres;        /* B2 RSRP, 1dB*/
    VOS_INT16               sB2RsrqThres;        /* B2 RSRQ, 1dB*/
    VOS_INT16               sB2UtraRscp;         /* B2UTRARSCP1dB*/
    VOS_INT16               sB2UtraEcn0;         /* B2UTRAEcn00.5dB*/
    VOS_INT16               sB2GeranRssi;        /* B2GERANRSSI1dB*/
    VOS_UINT32              ulRsv0;
}LRRC_NV_VOLTE_A2B2_SWITCH_AND_THRETH_STRU;

/*****************************************************************************
     : LRRC_NV_VOLTE_OR_CSFB_CTRL_STRU
   :
 ASN.1 :
   : VOLTECSFB
*****************************************************************************/
typedef struct
{
    VOS_UINT8               ucTotalFeatureSwitch;     /*  */
    VOS_UINT8               ucUSASwitch;              /* CSFB;ucTotalFeatureSwitch */
    VOS_INT16               sRsrpThres;               /* RSRP, 1dB*/
    VOS_INT16               sRsrqThres;               /* RSRQ, 1dB*/
    VOS_INT16               sUtraRscp;                /* UTRARSCP1dB*/
    VOS_INT16               sUtraEcn0;                /* UTRAEcn00.5dB*/
    VOS_INT16               sGeranRssi;               /* GERANRSSI1dB*/
    VOS_INT16               usRsv0;
    VOS_INT16               usRsv1;
    VOS_UINT32              ulRsv0;
}LRRC_NV_VOLTE_OR_CSFB_CTRL_STRU;

/*****************************************************************************
     : LRRC_NV_VOLTE_B2_PRA2_SWITCH_AND_THRETH_STRU
   :
 ASN.1 :
   : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8               ucVolteB2Pra2Switch;
    VOS_UINT8               ucRsv1;
    VOS_INT16               sB2UtraMinRscp;      /* B2UTRARSCP1dB*/
    VOS_INT16               sB2UtraMinEcn0;      /* B2UTRAEcn00.5dB*/
    VOS_INT16               sB2GeranMinRssi;     /* B2GERANRSSI1dB*/
    VOS_UINT16              usRsv1;
    VOS_UINT16              usRsv2;
    VOS_UINT16              usRsv3;
    VOS_UINT16              usRsv4;
    VOS_UINT32              ulRsv5;
}LRRC_NV_VOLTE_B2_PRA2_SWITCH_AND_THRETH_STRU;

/* Volte Evs,begin */
/*****************************************************************************
     : LRRC_NV_VOLTE_EVS_PARA_CTRL_STRU
   :
 ASN.1 :
   : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8               ucVolteEvsCtrlSwitch; /* EVSLRRC */
    VOS_UINT8               ucRsv1;
    VOS_INT16               sVolteEvsCtrlRsrp;      /* IMSEVSRSRP1dB*/
    VOS_INT16               sVolteEvsCtrlRsrq;      /* IMSEVSRSRP1dB*/
    VOS_UINT16              usRsv1;
    VOS_UINT16              usRsv2;
    VOS_UINT16              usRsv3;
    VOS_UINT16              usRsv4;
    VOS_UINT16              usRsv5;
    VOS_UINT32              ulRsv0;
}LRRC_NV_VOLTE_EVS_PARA_CTRL_STRU;
/* Volte Evs,end */


/*****************************************************************************
     : LRRC_NV_ID_M_FEATURE_CTRL_STRU
   :
 ASN.1 :
   : 
*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8      ucConnPagingSwitch; /* Verizon: paging */
    VOS_UINT8               ucDlSupervisonFailSwitch; /* Verizon: downlink supervision failure */
    VOS_UINT8               ucSib16TimeUpdateSwitch;  /* Verizon: SIB16 */
    VOS_UINT8               ucNoUsimCheckImsEmergSuppSwitch; /* IMS */
    VOS_UINT8               ucSwitch4;
    VOS_UINT8               ucSwitch5;
    VOS_UINT8               ucSwitch6;
    VOS_UINT8               ucSwitch7;

    VOS_INT16               sUSADeltaRsrp;          /* AT&T: RSRPINDDelta0 */
    VOS_UINT16              usPagingValidTime;      /* Verizon: paging5s,0-10s */
    VOS_UINT16              ucDlSupervisonFailTime; /* Verizon: downlink supervision failure5s0-10s */
    VOS_UINT16              usRsv3;
    VOS_UINT16              usRsv4;
    VOS_UINT16              usRsv5;
    VOS_UINT16              usRsv6;
    VOS_UINT16              usRsv7;
    VOS_UINT16              usRsv8;
    VOS_UINT16              usRsv9;
    VOS_UINT16              usRsv10;
    VOS_UINT16              usRsv11;
    VOS_UINT16              usRsv12;
    VOS_UINT16              usRsv13;
    VOS_UINT16              usRsv14;
    VOS_UINT16              usRsv15;

    VOS_UINT32              ulRsv0;
    VOS_UINT32              ulRsv1;
    LRRC_NV_RESTRICTED_BAND_STRU        stRestrictedBand;
    TLRRC_NV_CTRL_SUBFUNC_COMM_STRU     stRsv1;
    TLRRC_NV_CTRL_SUBFUNC_COMM_STRU     stRsv2;
    TLRRC_NV_CTRL_SUBFUNC_COMM_STRU     stRsv3;
    TLRRC_NV_CTRL_SUBFUNC_COMM_STRU     stRsv4;
    TLRRC_NV_CTRL_SUBFUNC_COMM_STRU     stRsv5;
    TLRRC_NV_CTRL_SUBFUNC_COMM_STRU     stRsv6;
}LRRC_NV_ID_M_FEATURE_CTRL_STRU;

/*****************************************************************************
     : LPS_NV_OM_VOLTE_FAULT_CTRL_CTRL
   :
 ASN.1 :
   : Volte
*****************************************************************************/
typedef struct
{
    VOS_UINT8               ucVtTotalSwitch;           /*  */
    VOS_UINT8               ucVtChrRtpSwitch;          /* CHR */
    VOS_UINT8               ucDelayAnTime;             /*  */
    VOS_UINT8               ucPreDelayAnTime;          /* s */
    VOS_UINT16              usConPktLostThrUnitTime;   /*  */
    VOS_UINT16              usAccuPktLostThrUnitTime;  /* */
    VOS_UINT16              usJitterThrUnitTime;       /* */
    VOS_UINT16              usL2TrigPktLostThr;        /* L2 */
    VOS_UINT16              usL2TrigJitterThr;         /* L2 */
    VOS_INT16               sLowRsrqThre;              /* Rsrq */
    VOS_INT16               sLowRsrpThre;              /* Rsrp */
    VOS_UINT16              usChrRptInterval;          /* CHR */
    VOS_UINT16              usGenStatRptInterval;      /* CHR */
    VOS_UINT16              usGenStatCallLen;          /*  */
    VOS_UINT16              usGenStatFaultNum;         /*   */
    VOS_UINT16              usRsv7;
    VOS_UINT32              ulRsv0;
}LPS_NV_OM_VOLTE_FAULT_CTRL_CTRL;

/*****************************************************************************
     : LPS_NV_OM_FEATURE_CTRL_STRU
   :
 ASN.1 :
   : OMCHR
*****************************************************************************/
typedef struct
{
    VOS_UINT8               ucTFreqCollection; /* TDSChr */
    VOS_UINT8               ucSwitch1;
    VOS_UINT8               ucSwitch2;
    VOS_UINT8               ucSwitch3;
    VOS_UINT8               ucSwitch4;
    VOS_UINT8               ucSwitch5;
    VOS_UINT8               ucSwitch6;
    VOS_UINT8               ucSwitch7;

    VOS_UINT16              usRsv0;
    VOS_UINT16              usRsv1;
    VOS_UINT16              usRsv2;
    VOS_UINT16              usRsv3;
    VOS_UINT16              usRsv4;
    VOS_UINT16              usRsv5;
    VOS_UINT16              usRsv6;
    VOS_UINT16              usRsv7;
    VOS_UINT16              usRsv8;
    VOS_UINT16              usRsv9;
    VOS_UINT16              usRsv10;
    VOS_UINT16              usRsv11;
    VOS_UINT16              usRsv12;
    VOS_UINT16              usRsv13;
    VOS_UINT16              usRsv14;
    VOS_UINT16              usRsv15;

    VOS_UINT32              ulRsv0;
    VOS_UINT32              ulRsv1;

    LPS_NV_OM_VOLTE_FAULT_CTRL_CTRL     stVolteFaultInd;
    TLRRC_NV_CTRL_SUBFUNC_COMM_STRU     stRsv1;
    TLRRC_NV_CTRL_SUBFUNC_COMM_STRU     stRsv2;
    TLRRC_NV_CTRL_SUBFUNC_COMM_STRU     stRsv3;
    TLRRC_NV_CTRL_SUBFUNC_COMM_STRU     stRsv4;
    TLRRC_NV_CTRL_SUBFUNC_COMM_STRU     stRsv5;
    TLRRC_NV_CTRL_SUBFUNC_COMM_STRU     stRsv6;
    TLRRC_NV_CTRL_SUBFUNC_COMM_STRU     stRsv7;
}LPS_NV_OM_FEATURE_CTRL_STRU;

/*****************************************************************************
     : LRRC_NV_CELL_SELECT_CTRL_STRU
   :
 ASN.1 :
   : NV
*****************************************************************************/
typedef struct
{
    VOS_UINT8               ucRemoveBarredSwitch;         /* barbar*/
    VOS_UINT8               ucRemoveDupFreqAndBandSwitch; /* */
    VOS_UINT8               ucSwitch2;
    VOS_UINT8               ucSwitch3;
    VOS_UINT8               ucSwitch4;
    VOS_UINT8               ucSwitch5;
    VOS_UINT8               ucSwitch6;
    VOS_UINT8               ucSwitch7;

    VOS_INT16               sBarredDeltaRsrp;             /* RSRPbarsDeltaRsrpDBbar*/
    VOS_INT16               sBarredDeltaRsrq;             /* RSRQbarsDeltaRsrqDBbar*/
    VOS_UINT16              usRsv2;
    VOS_UINT16              usRsv3;
    VOS_UINT16              usRsv4;
    VOS_UINT16              usRsv5;
    VOS_UINT16              usRsv6;
    VOS_UINT16              usRsv7;
    VOS_UINT16              usRsv8;
    VOS_UINT16              usRsv9;
    VOS_UINT16              usRsv10;
    VOS_UINT16              usRsv11;
    VOS_UINT16              usRsv12;
    VOS_UINT16              usRsv13;
    VOS_UINT16              usRsv14;
    VOS_UINT16              usRsv15;

    VOS_UINT32              ulRsv0;
    VOS_UINT32              ulRsv1;

    LRRC_NV_CELL_SELECT_RSSI_SORT_CTRL  stRssiSortCtl;
    TLRRC_NV_CTRL_SUBFUNC_COMM_STRU     stRsv1;
    TLRRC_NV_CTRL_SUBFUNC_COMM_STRU     stRsv2;
    TLRRC_NV_CTRL_SUBFUNC_COMM_STRU     stRsv3;
    TLRRC_NV_CTRL_SUBFUNC_COMM_STRU     stRsv4;
}LRRC_NV_CELL_SELECT_CTRL_STRU;

/*****************************************************************************
     : LRRC_NV_CSG_CTRL_PARA_STRU
   :
 ASN.1 :
   : CSG NVASF CSG
*****************************************************************************/
typedef struct
{
    LRRC_NV_CSG_FEATURE_CTRL            stCsgFeatureCtrl;
    LRRC_NV_CSG_ASF_PARAMETERS_STRU     stCsgASfParameters;
}LRRC_NV_CSG_CTRL_PARA_STRU;

/*********************************************************************
     : LRRC_NV_CMAS_ETWS_CTR_STRU
   :
 ASN.1 :
   : LRRC_NV_CMAS_ETWS_CTR_STRU
*********************************************************************/
typedef struct
{
    VOS_UINT8  ucEtwsSupportSwitch;  /* ETWS01 */
    VOS_UINT8  ucCmasSupportSwitch;  /* CMAS01 */
    VOS_UINT8  ucCmasReptCampSucessSwitch;     /* 0:CMAS1 */
    VOS_UINT8  ucSndEtwsImidiSwitch;     /* ETWS01 */
    VOS_UINT8  ucGetCmasRcvCmpFlg;     /*CMAS01 */
    VOS_UINT8  aucReserved[3];
}LRRC_NV_CMAS_ETWS_CTR_STRU;

/*********************************************************************
     : LRRC_NV_CA_OPTIMIZE_CTR_STRU
   :
 ASN.1 :
   : CA
*********************************************************************/
typedef struct
{
    VOS_UINT8  ucCaSupportSwitch;   /* CA01 */
    VOS_UINT8  ucRplyRecfgCmpFlag;  /* UECACPM0CMP;1CMP */
    VOS_UINT8  aucReserved[2];
}LRRC_NV_CA_OPTIMIZE_CTR_STRU;

/*********************************************************************
     : LRRC_NV_VOLTE_OPTIMIZE_CTR_STRU
   :
 ASN.1 :
   : VOLTE
*********************************************************************/
typedef struct
{
    VOS_UINT8               ucVolteDelayB2MeasRptWhenMO;   /* VolteB2bsrvcc */
    VOS_UINT8               ucVolteDelayB2MeasRptWhenMT;   /* VolteB2bsrvcc */
    VOS_UINT8               ucVolteNoTdsConnB2MeasSwitch;  /* VolteTds */
    VOS_UINT8               ucReserved;

    LRRC_NV_VOLTE_A2B2_SWITCH_AND_THRETH_STRU       stVolteA2B2;
    LRRC_NV_VOLTE_OR_CSFB_CTRL_STRU                 stVolteOrCsfbCtrl;
    LRRC_NV_VOLTE_B2_PRA2_SWITCH_AND_THRETH_STRU    stVolteB2Pra2Para;
}LRRC_NV_VOLTE_OPTIMIZE_CTR_STRU;

/*****************************************************************************
     : LRRC_NV_INTER_OPT_CTRL_STRU
   :
 ASN.1 :
   : NV
*****************************************************************************/
typedef struct
{
    VOS_UINT8               ucSCellReselRsrqSwitch;    /* LTERSRQ */
    /* add for Conn Meas Filter Optimize begin */
    VOS_UINT8               ucConnMeasFilterOptimizeSwitch;
    /* add for Conn Meas Filter Optimize begin */
    VOS_UINT8               ucCsfbT304ExpCcoRemain;    /* CSFBT304CCO */
    VOS_UINT8               ucVolteDelayB2MeasRptWhenMO;   /* VolteB2bsrvcc */
    VOS_UINT8               ucVolteDelayB2MeasRptWhenMT;   /* VolteB2bsrvcc */
    /* Do not start tds connected B2 meas when volte is running, Begin */
    VOS_UINT8               ucVolteNoTdsConnB2MeasSwitch;  /* VolteTds */
    /* Do not start tds connected B2 meas when volte is running, End */
    /* set LTE Default resel prioty when no resel priory in sib5,begin */
    VOS_UINT8               ucSetLteReselPriotySwitch;
    /* set LTE Default resel prioty when no resel priory in sib5,end */
    VOS_UINT8               ucSwitch3;

    VOS_INT16               sSCellReselRsrqTres;       /* LTERSRQ*/
    VOS_INT16               sReselDeltaRsrq;          /* LTERSRQusReselDeltaRsrqDBRSRP*/
    VOS_INT16               sReselRsrpTres;            /* LTEsReselDeltaRsrqRSRPsReselRsrpTres */
    VOS_UINT16              usBgsClSearchThresSwitch;     /* CLCL */
    VOS_INT16               sBgsClSearchThres;         /* CLCL */
    VOS_UINT16              usCellSelThresSwitch;         /*  */
    VOS_INT16               sCellSelQrxlevMin;         /* ucCellSelThresSwitchQrxlevMin,1dB */
    VOS_INT16               sCellSelqQualMin;         /* ucCellSelThresSwitchqQualMin,1dB */
    /* begin, mod for conn meas and A3 timer */
    VOS_UINT16              usConnMeasCtrlSwitch;         /* RSRQ */
    VOS_INT16               sConnMeasRsrq;                /* RSRQ: 1sMeasure 2A3RSRQ */
    VOS_UINT16              usEverntA3TrigerTime;         /* A3: ms  */
    /* end, mod for conn meas and A3 timer */
    VOS_UINT16              usNoRptSecondCellThres;
    VOS_INT16               sLowPriMeasSrvRsrqThres;   /* q1/8dB,DTS2016050408711 */

    VOS_UINT16              usRsv2;
    VOS_UINT16              usRsv3;
    VOS_UINT16              usRsv4;


    VOS_UINT32              ulRsv0;
    VOS_UINT32              ulRsv1;

    LRRC_NV_INTER_OPT_FREQENTLY_CTRL    stOptFreqentlyCtl;
    LRRC_NV_PRIVATE_B1_SWITCH_AND_THRETH_STRU    stPriB1;
    LRRC_NV_VOLTE_A2B2_SWITCH_AND_THRETH_STRU    stVolteA2B2;
    LRRC_NV_VOLTE_OR_CSFB_CTRL_STRU     stVolteOrCsfbCtrl;
    LRRC_NV_VOLTE_B2_PRA2_SWITCH_AND_THRETH_STRU     stVolteB2Pra2Para;
    /* Volte Evs,begin */
    LRRC_NV_VOLTE_EVS_PARA_CTRL_STRU     stVolteEvsParaCtrl;
    /* Volte Evs,end */
    TLRRC_NV_CTRL_SUBFUNC_COMM_STRU     stRsv1;
    TLRRC_NV_CTRL_SUBFUNC_COMM_STRU     stRsv2;
    //TLRRC_NV_CTRL_SUBFUNC_COMM_STRU     stRsv3;
}LRRC_NV_INTER_OPT_CTRL_STRU;

/*****************************************************************************
     : LUP_MEM_POOL_CFG_NV_STRU
   : LUP_MEM_POOL_CFG_NV
*****************************************************************************/
typedef struct
{
    VOS_UINT8                      ucClusterCnt;
    VOS_UINT8                      aucRsv[3];
    VOS_UINT16                     ausBlkSize[LUP_MEM_MAX_CLUSTER_NUM];         /*  */
    VOS_UINT16                     ausBlkCnt[LUP_MEM_MAX_CLUSTER_NUM];          /*  */
}LUP_MEM_POOL_CFG_NV_STRU;

/*****************************************************************************
     : TTF_MEM_SOLUTION_CFG_NV_STRU
   : TTF_MEM_SOLUTION_CFGNV
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucPoolCnt;
    VOS_UINT8                           aucReserve[3];
    LUP_MEM_POOL_CFG_NV_STRU            astLupMemPoolCfgInfo[LUP_MEM_MAX_POOL_NUM];
}LUP_MEM_CFG_NV_STRU;

/*****************************************************************************
     : LRRC_NV_VOWIFI_TREES_STRU
   : 1PlowpQlowqBAD
             2PhighpQhighqGOOD;
             3NORMAL;
 ASN.1 :
   : vowifi 
*****************************************************************************/
typedef struct
{
    VOS_INT16               sThresWlanLowP;
    VOS_INT16               sThresWlanLowQ;
    VOS_INT16               sThresWlanHighP;
    VOS_INT16               sThresWlanHighQ;
    VOS_UINT32              ulTSteeringWLAN;
    VOS_INT16               sThresWlanDeltaP;
    VOS_INT16               sStableIntervalRptLen; /**/
}LRRC_VOWIFI_THRES_STRU;

/*****************************************************************************
     : LRRC_NV_VOWIFI_TREES_STRU
   :
 ASN.1 :
   : vowifi idle
*****************************************************************************/
typedef struct
{
    LRRC_VOWIFI_THRES_STRU  stVowifiThresConn;
    LRRC_VOWIFI_THRES_STRU  stVowifiThresIdle;
}LRRC_NV_VOWIFI_THRES_STRU;

/*****************************************************************************
     : LRRC_NV_ONLY_DL_BAND_CTRL_STRU
   :
 ASN.1 :
   : Band 
*****************************************************************************/
typedef struct
{
    /* 32bandband = (-1)*32 +  */
    LPS_NV_LONG_BIT_STRU                stBandGroupFlag[LRRC_SINGLE_DL_BAND_GROUP_NUM];
}LRRC_NV_ONLY_DL_BAND_CTRL_STRU;


/*****************************************************************************
     : GUTL_COMM_RESEL_THRES_CFG_NV_STRU
   : GUTL_COMM_RESEL_THRES_CFGNV
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucFeatureSwitch;                        /* */
    VOS_UINT8                           ucHigPrioRselSwitch;                    /* L */
    VOS_INT16                           sRsrqThres;                             /* LRsrq1dB */
    VOS_INT16                           sDeltaRsrq;                             /* LRSRQ1dB */
    VOS_INT16                           sUtraRscp;                              /* utraL1dB */
    VOS_INT16                           sUtraEcn0;                              /* utraL1dB */
    VOS_INT16                           sGeranRssi;                             /* geranL1dB */
    VOS_INT16                           sRsrpThres;                             /* LRsrp1dB */
    VOS_UINT16                          usDeltaRsrp;                            /* LRsrp1dB */
    VOS_UINT16                          usReserve1;
    VOS_UINT16                          usReserve2;
    VOS_UINT16                          usReserve3;
    VOS_UINT16                          usReserve4;
}GUTL_COMM_RESEL_THRES_CFG_NV_STRU;

/*****************************************************************************
    : TL_CHR_BIG_DATA_NV_PARA_STRU
  :
ASN.1 :
  : CHR 
*****************************************************************************/
typedef struct
{
    VOS_INT16           sLteLowRsrpThres;              /* CHR LTE */
    VOS_INT16           sLteHigRsrpThres;              /* CHR LTE */
    VOS_INT8            cTdsLowRscpThres;              /* CHR TDS */
    VOS_INT8            cTdsHigRscpThres;              /* CHR TDS */
    VOS_UINT8           ucResv[2];
}TL_CHR_BIG_DATA_NV_PARA_STRU;

/*****************************************************************************
    : TL_CHR_BIG_DATA_NV_PARA_STRU
  :
ASN.1 :
  : EN_NV_ID_RRC_MMP_CONFIG LRRCmodem
*****************************************************************************/
typedef struct
{
    VOS_UINT32              bitMmpPagingShareEnable : 1;         /* modem paging */
    VOS_UINT32              bitMmpCandFreqShareEnable : 1;       /* modem  */
    VOS_UINT32              bitMmpBsicShareEnable : 1;           /* modem Bsic */
    VOS_UINT32              bitMmpSibShareEnable : 1;            /* modem  */
    VOS_UINT32              bitMmpMeasureShareEnbale : 1;        /* modem  */
    VOS_UINT32              bitMmpReselShareEnbale : 1;          /* modem  */
    VOS_UINT32              bitRsv1 : 1;
    VOS_UINT32              bitRsv2 : 1;
    VOS_UINT32              bitRsv3 : 1;
    VOS_UINT32              bitRsv4 : 1;
    VOS_UINT32              bitRsv5 : 1;
    VOS_UINT32              bitRsv6 : 1;
    VOS_UINT32              bitRsv7 : 1;
    VOS_UINT32              bitRsv8 : 1;
    VOS_UINT32              bitRsv9 : 1;
    VOS_UINT32              bitRsv10 : 1;
    VOS_UINT32              bitRsv11 : 1;
    VOS_UINT32              bitRsv12 : 1;
    VOS_UINT32              bitRsv13 : 1;
    VOS_UINT32              bitRsv14 : 1;
    VOS_UINT32              bitRsv15 : 1;
    VOS_UINT32              bitRsv16 : 1;
    VOS_UINT32              bitRsv17 : 1;
    VOS_UINT32              bitRsv18 : 1;
    VOS_UINT32              bitRsv19 : 1;
    VOS_UINT32              bitRsv20 : 1;
    VOS_UINT32              bitRsv21 : 1;
    VOS_UINT32              bitRsv22 : 1;
    VOS_UINT32              bitRsv23 : 1;
    VOS_UINT32              bitRsv24 : 1;
    VOS_UINT32              bitRsv25 : 1;
    VOS_UINT32              bitRsv26 : 1;

    /*  */
    VOS_INT16               sMmpLowRsrpThresh;                   /*  */
    VOS_INT16               sMmpHighRsrpThresh;                  /*  */
    VOS_INT16               sMmpRsrpOffset;                      /* offsetsMmpHighRsrpThresh */
    PS_BOOL_ENUM_UINT8      enCandFreqShareInChina;              /*  */
    VOS_UINT8               ucMmpMaxCandFreqNum;                 /* MMP11modem */
}RRC_MMP_CONFIG_STRU;

/*****************************************************************************
     : log

   : cPowerOnlogCcPowerOnlogA1
*****************************************************************************/
typedef struct
{
    /* Clog*/
    VOS_INT8                            cPowerOnlogC;

    /* APlog,0AlinuxSOCP50MNV:10 */
    VOS_INT8                            cPowerOnlogA;
    VOS_INT8                            cSpare1;
    VOS_INT8                            cSpare2;
}NV_POWER_ON_LOG_SWITCH_STRU;

/* PLMNbegin */
/*****************************************************************************
     : LRRC_NV_TEST_PLMN_SET_STRU

   : PLMNPLMN
*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                        enTestPlmnSetFlag;
    VOS_UINT8                                 ucPlmnNum;
    LRRC_LNAS_PLMN_ID_STRU                    stPlmnId[LRRC_TEST_PLMN_MAX_NUM];
}LRRC_NV_TEST_PLMN_SET_STRU;
/* PLMNend */

/*****************************************************************************
     : LRRC_NV_RA_FAIL_REPORT_STRU

   : LRRC  CHR
*****************************************************************************/
typedef struct
{
    RRC_NV_SWITCH_ENUM_UINT32                 enReportSwitch;           /*  */
    VOS_INT16                                 sRsrpThreshold;           /* RSRP,:  -100db */
    VOS_INT16                                 sRsrqThreshold;           /* RSRq,:  -13db */
    VOS_UINT32                                ulSilencePeriod;          /*  30min */
}LRRC_NV_RA_FAIL_REPORT_STRU;

/*****************************************************************************
     : LRRC_SINGLE_PLMN_FORBIDDEN_BAND_STRU
   :
 ASN.1 :
   : PLMNBand
*****************************************************************************/
typedef struct
{
    LRRC_LNAS_PLMN_ID_STRU  stNasFormatPlmn;
    VOS_UINT16              ausPlmnBand[LRRC_SINGLE_PLMN_FORBIDDEN_BAND_MAX_NUM];
}LRRC_SINGLE_PLMN_FORBIDDEN_BAND_STRU;

/*****************************************************************************
     : LRRC_NV_PLMN_FORBIDDEN_BAND_STRU
   :
 ASN.1 :
   : PLMNBand
*****************************************************************************/
typedef struct
{
    VOS_UINT32                            ulPlmnNum;
    LRRC_SINGLE_PLMN_FORBIDDEN_BAND_STRU  astPlmn[LRRC_FORBIDDEN_BAND_PLMN_MAX_NUM];
}LRRC_NV_PLMN_FORBIDDEN_BAND_STRU;
/*****************************************************************************
     : LRRC_NV_USER_PLANE_IMPROVE_CTRL_STRU
   :
 ASN.1 :
   : NV
 *****************************************************************************/
typedef struct
{
    VOS_UINT8               ucConnRelProtectSwtich;         /*  */
    VOS_UINT8               ucSRProtectSwtich;              /* SR */
    VOS_UINT8               ucReestRecfgProtectSwtich;      /*  */
    VOS_UINT8               ucUeCapProtectSwtich;           /* UE  */
    VOS_UINT8               ucPdcpDisPduProtectSwtich;      /* PDCP*/
    VOS_UINT8               ucPdcpPacketErrProtectSwtich;   /* PDCP */
    VOS_UINT8               ucUserPlaneImproveChrSwtich;    /* CHR */
    VOS_UINT8               ucSwitch7;
    VOS_UINT8               ucSwitch8;
    VOS_UINT8               ucSwitch9;
    VOS_UINT8               ucSwitch10;
    VOS_UINT8               ucSwitch11;
    VOS_UINT16              usDecreaA2swtich;
    VOS_INT16               sDecreaA2offset;
    VOS_UINT16              usRsv2;
    VOS_UINT16              usRsv3;
    VOS_UINT16              usRsv4;
    VOS_UINT16              usRsv5;
    VOS_UINT16              usRsv6;
    VOS_UINT16              usRsv7;
    VOS_UINT16              usRsv8;
    VOS_UINT16              usRsv9;
    VOS_UINT16              usRsv10;
    VOS_UINT16              usRsv11;
    VOS_UINT16              usRsv12;
    VOS_UINT16              usRsv13;
    VOS_UINT16              usRsv14;
    VOS_UINT16              usRsv15;

    VOS_UINT32              ulConnRelProtectTimerLen;    /* ms */
    VOS_UINT32              ulRaSussCountThre;           /*  */
    VOS_UINT32              ulRecfgProtectTimerLen;      /* ms */
    VOS_UINT32              ulCapRelDetectCountThre;     /* UE */
    VOS_UINT32              ulRsv4;
    VOS_UINT32              ulRsv5;
    VOS_UINT32              ulRsv6;
    VOS_UINT32              ulRsv7;

    TLRRC_NV_CTRL_SUBFUNC_COMM_STRU     stRsv0;
    TLRRC_NV_CTRL_SUBFUNC_COMM_STRU     stRsv1;
    TLRRC_NV_CTRL_SUBFUNC_COMM_STRU     stRsv2;
    TLRRC_NV_CTRL_SUBFUNC_COMM_STRU     stRsv3;
}LRRC_NV_USER_PLANE_IMPROVE_CTRL_STRU;

/*****************************************************************************
     : LRRC_NV_RF_MEAS_PARAM_V1020
   :
 ASN.1 : NV53795NV48633 
   : LRRC_NV_RF_MEAS_PARAM_V1020_STRU
*****************************************************************************/
typedef struct
{
    VOS_UINT32    bitRfMeasParamV1020Present                  : 1;
    VOS_UINT32    bitSpare                                    : 31;
    RRC_RF_MEAS_PARAM_V1020_STRU                stRfMeasParamV1020;
    RRC_RF_MEAS_PARAM_V1020_STRU                stRfMeasParamV1020Ext;
}LRRC_NV_RF_MEAS_PARAM_V1020_STRU;

/*****************************************************************************
     : LRRC_NV_UE_CAP_FEATURE_GROUP_IND_R10
   :
 ASN.1 : NV53795NV48634
   : LRRC_NV_UE_CAP_FEATURE_GROUP_IND_R10_STRU
*****************************************************************************/
typedef struct
{
    VOS_UINT32    bitFeatureGroupIndRel10R10Present           : 1;
    VOS_UINT32    bitSpare                                    : 31;
    RRC_UE_CAP_FEATURE_GROUP_IND_R10_STRU       stFeatureGroupIndRel10R10;
}LRRC_NV_UE_CAP_FEATURE_GROUP_IND_R10_STRU;

/*****************************************************************************
     : LRRC_NV_UE_CAP_FEATURE_GROUP_IND_R9
   :
 ASN.1 : NV53794NV48635 
   : LRRC_NV_UE_CAP_FEATURE_GROUP_IND_R9_STRU
*****************************************************************************/
typedef struct
{
    VOS_UINT32    bitFeatureGroupIndRel9AddR9Present          : 1;
    VOS_UINT32    bitFddFeatureGroupIndR9Present              : 1;
    VOS_UINT32    bitFddFeatureGroupIndRel9AddR9Present       : 1;
    VOS_UINT32    bitTddFeatureGroupIndR9Present              : 1;
    VOS_UINT32    bitTddFeatureGroupIndRel9AddR9Present       : 1;
    VOS_UINT32    bitSpare                                    : 27;

    RRC_UE_CAP_FEATURE_GROUP_IND_R9ADD_STRU       stFeatureGroupIndRel9AddR9;
    RRC_UE_CAP_FEATURE_GROUP_IND_STRU             stFddFeatureGroupIndR9;
    RRC_UE_CAP_FEATURE_GROUP_IND_R9ADD_STRU       stFddFeatureGroupIndRel9AddR9;
    RRC_UE_CAP_FEATURE_GROUP_IND_STRU             stTddFeatureGroupIndR9;
    RRC_UE_CAP_FEATURE_GROUP_IND_R9ADD_STRU       stTddFeatureGroupIndRel9AddR9;
}LRRC_NV_UE_CAP_FEATURE_GROUP_IND_R9_STRU;

/*****************************************************************************
     : LRRC_NV_UE_CAP_FEATURE_GROUP_IND
   :
 ASN.1 : NV53804NV48636 
   : LRRC_NV_UE_CAP_FEATURE_GROUP_IND_STRU
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitFeatureGroupIndsPresent    : 1;
    VOS_UINT32                          bitSpare                      : 31;

    RRC_UE_CAP_FEATURE_GROUP_IND_STRU   stFeatrueGroupInds;
}LRRC_NV_UE_CAP_FEATURE_GROUP_IND_STRU;

/*****************************************************************************
     : LRRC_NV_UE_CAP_PDCP_PARA
   :
 ASN.1 : NV53804NV48637 
   : LRRC_NV_UE_CAP_PDCP_PARA_STRU
*****************************************************************************/
typedef RRC_UE_CAP_PDCP_PARA_STRU  LRRC_NV_UE_CAP_PDCP_PARA_STRU;


/*****************************************************************************
     : LRRC_NV_VOLTE_END_EVAB1B2_CTR_INFO
   :
 ASN.1 :
   : VOLTEB1B2NV
*****************************************************************************/
typedef struct
{
    VOS_UINT32              ulVolteEndEvaB1B2CtrTimerLen;/* VOLTEB1B2 */
    VOS_UINT8               ucRsv1;
    VOS_UINT8               ucRsv2;
    VOS_UINT16              usRsv1;
    VOS_UINT16              usRsv2;
    VOS_UINT16              usRsv3;
}LRRC_NV_VOLTE_END_EVAB1B2_CTR_INFO_STRU;


/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
/*boston modify begin */
/*TA Timer0:TA Timer 1:TA Timer*/
extern VOS_UINT32  g_aulCloseTaTimer[LPS_MAX_MODEM_NUM];

/*SR0:SR 1:SR*/
extern VOS_UINT32  g_aulCloseSrRandFlag[LPS_MAX_MODEM_NUM];

/*SR0:SRBSR 1:SRBSR*/
extern VOS_UINT32  g_aulSrTrigFlag[LPS_MAX_MODEM_NUM];
/*boston modify end */

/*PC*/
extern VOS_UINT32  g_ulIfForwardToPc;

/* :0-1-*/
extern VOS_UINT32  g_ulSmcControl;

/* DCMGULTA */
extern VOS_UINT32  g_ulHoIgnoreForbidTaFlag;
/* TA 1: 0:  */
extern VOS_UINT32    g_ulIntraHoIgnoreForbidTaFlag;

/* 0:  1:.*/
/*boston modify begin */
extern VOS_UINT32 g_aulFieldTestSwitch[LPS_MAX_MODEM_NUM];
/*boston modify end */

/*eNBTDD*/

/*BAR*/
extern VOS_UINT32 g_ulCloseBarCell;

/* DRX Control Flag  0: Close 1: Open */
extern VOS_UINT32 g_ulDrxControlFlag;

/* 1 */
extern VOS_UINT32 g_ulCfgSubFrameAssign;

/* 7 */
extern VOS_UINT32 g_ulSubFramePattern;

/*  */
extern VOS_UINT32 g_ulPsCfgDspAntCnt;


/* PCO01 */
extern VOS_UINT32 g_ulPcoFlag;

/* SDFQos01 */
extern VOS_UINT32 g_ulDelSdfWithQosFlag;

/* delete by s00139335 for DTS2016041910228,, 2016-4-19*/

/* TAU01 */
extern VOS_UINT32 g_ulTauCipheredFlag;

/**/
extern VOS_UINT32  g_ulFlowCtrlFlag;

/*CPU*/
extern VOS_UINT32  g_ulFcPdcpTarget;

/**/
extern VOS_UINT32   g_ulTargetIPMax;
extern VOS_UINT32   g_ulSendSduMax;

/**/
extern VOS_UINT32  g_ulDlSduMax;
extern VOS_UINT32  g_ulULIpMax;

/*ms*/
extern VOS_UINT32  g_ulMeasGap;
extern VOS_UINT32  g_ulSduGap;
/**/
extern VOS_UINT32  g_ulFcInitFlag ;

/*Msg4 6CR1Msg4
60*/
/*boston modify begin */
extern VOS_UINT32  g_aulMsg4ForOldCrFlag[LPS_MAX_MODEM_NUM];
/*boston modify end */

/* GCF24.301 Table D.1.1 0x00000004,0 */
extern VOS_UINT32 g_ulGcfEstCauseFlag;

/* SMC0x00000008 */
extern VOS_UINT32  g_ulSmcFuncTestMode;

/* GCFCDRX,0
1GCF0
extern VOS_UINT32  g_ulGcfConnDrxStubFlag;*/

/* LNASVOS_TRUE:VOS_FALSE:*/
extern VOS_UINT8  g_ucTestCardFlag;

#endif
/*  */
extern VOS_UINT32  g_ulPsSupportBand64Flg;
extern VOS_UINT32  g_ulPsPagingConnRelFlg;
extern VOS_UINT32  g_ulPsUlDrbDiscardFlag;
extern VOS_UINT32  g_ulMbmsSupportSwitch;
extern VOS_UINT32  g_ulPsBandwidthSupportFlg;
/* modify by lishangfeng freq all begin */
extern VOS_UINT32  g_ulPsFreqInAllBandWidthFlg;

extern VOS_UINT32  g_ulHoFailFlag;
extern VOS_UINT16  g_usHoFailT304;
/* gaojishan-SYSCFG-SAVENV-Begin */
extern VOS_UINT32  gulJpSbmDualImsiSwitch;
extern VOS_UINT32  gulLteDelWcdmaBandInJapan;           /*NV*/
/* Begin: 2015/5/6 sbm */
extern VOS_UINT8       g_ucSbmCustomSrchFlg;
extern VOS_UINT32      g_ulSbmSupBandInJapan;         /* band1bandUEband */
extern VOS_UINT32      g_ulEmSupBandInJapan;          /* EMband1bandUEband */
extern VOS_UINT32      g_ulOtherOperateSupBandInJapan;/* band1bandUEband */
extern VOS_UINT32      g_ulSupBandOutJapan;
/* Begin: 2015/5/6 sbm */

/*Begin: for sbm delete wcdma band9  */
extern VOS_UINT8       gucJpUband1MncCnt;
extern VOS_UINT8       gaucJpUband1Mnc[3];
extern VOS_UINT8       gaucJpUband1Mcc[3];
extern VOS_UINT8       gaucJpUband2Mcc[3];
/*End: for sbm delete wcdma band9  */
/* gaojishan-SYSCFG-SAVENV-End */
extern VOS_UINT32  g_ulLReestIratCellSrchFlg;
/* gaojishan-nccpermit */
extern VOS_UINT32 g_ulNccPermitFlag;
extern VOS_UINT32  g_ulLBgsSupportFlg;
/* gaojishan-reest-measGap*/
extern VOS_UINT32  g_ulLBgsLSupportFlg;

extern VOS_UINT32 g_ulLTEReestMeasGapSetupFlag;
/* BEGIN DTS********** c00171433 2012-12-08 Add, ATLTEIDLE*/
extern VOS_UINT32 g_ulLTEConnToIdleFlag;
/* END DTS********** c00171433 2012-12-08 Add, ATLTEIDLE*/


/* gaojishan-PLMN_EXACTLY_COMPARE_FLG */
extern VOS_UINT32 g_ulPlmnExactCmpFlg;
/* gaojishan-SoftBank-:true,set Band41 range */
extern VOS_UINT32 gulSoftBankFlag ;
/* gaojishan-nccpermit-2 */
extern VOS_UINT32 g_ulNoIdleNccPermitFlag;

/* gaojishan-dcom-resel-cfg */
extern VOS_UINT32 g_ulLteJpDcomUseR8Flag;
extern VOS_UINT32 g_ulLteJpDccomRelOffSetFlag;
extern VOS_UINT32 g_ulLteUtranEvaFlag;
/* gaojishan-fast-dorm-cfg */
extern VOS_UINT32 g_ulLteJpFastdormFlag;
/* gaojishan-fast-dorm-cfg-3 */
extern VOS_UINT32 g_usLteJpFastdormDelayValue;

extern VOS_UINT32 g_ulDlCtrlPduNotifyFlag;

/* gaojishan-CMAS-Begin */
/* >0: cmas report after rrc auth(after camp in fact); 0:cmas report even when cell searching*/
extern VOS_UINT32                              gul_CmasRptBeforeAuthSwitch;
/* gaojishan-CMAS-End */

/*add by l00220658  ADRX SSC NV stPsFunFlag03 0 1*/
extern VOS_UINT32 g_ulSscSupportFlag;
extern VOS_UINT32 g_ulAdrxSupportFlag;
/* niuxiufan taiwan modify begin */
extern VOS_UINT32 g_ulRedirNotBandScanFlg;
/* niuxiufan taiwan modify end */

/* Paging,UE Paging l00285345 begin*/
extern PS_BOOL_ENUM_UINT8  g_enPsIdleDiscardPagingFlag;
/* Paging,UE Paging l00285345 end*/

/* ESR,TAU,ESR:REL */
extern VOS_UINT32  g_ulNasEmmHoRetransEsrFlag;
/* niuxiufan rrc release modify begin */
extern VOS_UINT32 g_ulNotTryFakeCellFlg;
/* niuxiufan rrc release modify end */

extern VOS_UINT32                      g_ulDynmicUeCapFlg;

/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/


/*****************************************************************************
  9 OTHERS
*****************************************************************************/










#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of PsNvInterface.h */

