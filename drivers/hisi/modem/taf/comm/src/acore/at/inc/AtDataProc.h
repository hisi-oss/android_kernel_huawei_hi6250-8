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


#ifndef __AT_DATA_PROC_H__
#define __AT_DATA_PROC_H__


/*****************************************************************************
  1 
*****************************************************************************/
#include "mdrv.h"

#include "AtCtx.h"
#include "AtInputProc.h"
#include "AtNdisInterface.h"
#include "AtRnicInterface.h"
/* Modified by m00217266 for L-C, 2014-2-11, begin */
#include "RnicConfigInterface.h"
#include "AdsInterface.h"
/* Modified by m00217266 for L-C, 2014-2-11, end */
#include "AtPppInterface.h"

#include "FcInterface.h"
#include "PppInterface.h"

#include "TafApsApi.h"

#include "AtCmdMsgProc.h"

#include "AtInternalMsg.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 
*****************************************************************************/

/*lint -e778 */
/*lint -e572 */
#ifndef VOS_NTOHL                   /* */
#if VOS_BYTE_ORDER==VOS_BIG_ENDIAN
#define VOS_NTOHL(x)    (x)
#define VOS_HTONL(x)    (x)
#define VOS_NTOHS(x)    (x)
#define VOS_HTONS(x)    (x)
#else
#define VOS_NTOHL(x)    ((((x) & 0x000000ffU) << 24) | \
             (((x) & 0x0000ff00U) <<  8) | \
             (((x) & 0x00ff0000U) >>  8) | \
             (((x) & 0xff000000U) >> 24))

#define VOS_HTONL(x)    ((((x) & 0x000000ffU) << 24) | \
             (((x) & 0x0000ff00U) <<  8) | \
             (((x) & 0x00ff0000U) >>  8) | \
             (((x) & 0xff000000U) >> 24))

#define VOS_NTOHS(x)    ((((x) & 0x00ff) << 8) | \
             (((x) & 0xff00) >> 8))

#define VOS_HTONS(x)    ((((x) & 0x00ff) << 8) | \
             (((x) & 0xff00) >> 8))
#endif  /* _BYTE_ORDER==_LITTLE_ENDIAN */
#endif
/*lint -e572 */
/*lint -e778 */

#define AT_PPP_CODE_REQ                 (1)
#define AT_PPP_CODE_ACK                 (2)
#define AT_PPP_DEF_ID                   (1)

#define AT_AP_PPP_CODE_CHALLENGE        (1)
#define AT_AP_PPP_CODE_RESPONSE         (2)

#define AT_AP_PPP_PRIMARY_DNS           (129)
#define AT_AP_PPP_PRIMARY_WINNS         (130)
#define AT_AP_PPP_SECONDARY_DNS         (131)
#define AT_AP_PPP_SECONDARY_WINNS       (132)

#define AT_AP_PPP_CHAP_CHALLENGE_LEN    (16)
#define AT_AP_PPP_CHAP_RESPONSE_LEN     (16)
#define AT_AP_MAX_IPV4_ADDR_LEN         (15)

#define AT_AP_AUTH_NO_PROTO             (0)
#define AT_AP_AUTH_PAP_PROTO            (1)
#define AT_AP_AUTH_CHAP_PROTO           (2)

#define AT_DEF_DISPLAY_SPEED            (81920000)                              /* 10 M*/

#define AT_MAX_IPV4_DNS_LEN             (16)
#define AT_MAX_IPV4_NBNS_LEN            (16)
#define AT_MAX_IPV6_DNS_LEN             (16)
#define AT_MAX_IPV6_NBNS_LEN            (16)

#define AT_MAX_IPV6_STR_DOT_NUM          (3)
#define AT_MAX_IPV4V6_STR_COLON_NUM      (6)
#define AT_MAX_IPV6_STR_COLON_NUM        (7)

#define AT_IPV6_STR_MAX_TOKENS                  (16)                            /* IPV6 */
#define AT_IPV4_STR_DELIMITER                   '.'                             /* RFCIPV4 */
#define AT_IPV6_STR_DELIMITER                   ':'                             /* RFC2373IPV6 */

#if (FEATURE_ON == FEATURE_IPV6)
#define AT_GetIpv6Capability()                  (AT_GetCommPsCtxAddr()->ucIpv6Capability)
#endif

/* Added by L47619 for V3R3 Share-PDP Project, 2013-6-6, begin */
#define AT_PS_GET_SHARE_PDP_FLG()               (AT_GetCommPsCtxAddr()->ucSharePdpFlag)
/* Added by L47619 for V3R3 Share-PDP Project, 2013-6-6, end */

#define AT_APP_GetPdpEntInfoAddr()              (&g_stAtAppPdpEntity)

#define AT_APP_GetDailParaAddr()                (&g_stAtAppDialPara)

#define AT_APP_GetFirstActPdpType()             (g_enAtAppFirstActPdpType)
#define AT_APP_SetFirstActPdpType(ucPdpType)    (g_enAtAppFirstActPdpType = (ucPdpType))

#define AT_APP_GetActPdpType()                  (g_enAtAppActPdpType)
#define AT_APP_SetActPdpType(ucPdpType)         (g_enAtAppActPdpType = (ucPdpType))

/* APPID */
#define AT_APP_GET_CLIENT_ID()          (gastAtClientTab[AT_CLIENT_TAB_APP_INDEX].usClientId)

/* APP */
#define AT_APP_GET_USR_PORT_INDEX()     (g_stAtAppPdpEntity.stUsrInfo.enPortIndex)

/* APPcid */
#define AT_APP_GET_USR_CID()            (g_stAtAppPdpEntity.stUsrInfo.ucUsrCid)


/* NDIS */
#define AT_APP_GET_CURR_CMD_OPT()       (gastAtClientTab[AT_APP_GET_USR_PORT_INDEX()].CmdCurrentOpt)

#define AT_APP_GetRaInfoAddr()                  (&g_stAtAppRaInfo)

/*----------------------------------------------------------------------
   ^NDISSTAT: <stat>[,<err_code>[,<wx_stat>[,<PDP_type]]]
   <err_code> value defined as follows:
   0      - Unknown error/Unspecified error
   others - (E)SM Cause
            SM Cause is defined in TS 24.008 section 10.5.6.6
            ESM Cause is defined in TS 24.301 section 9.9.4.4
*---------------------------------------------------------------------*/
#define AT_NDISSTAT_ERR_UNKNOWN                 (0)

/* NDISNDISCONNNDISDUP index */
#define AT_NDIS_CID_IDX                         (0)
#define AT_NDIS_CONN_IDX                        (1)
#define AT_NDIS_APN_IDX                         (2)
#define AT_NDIS_NAME_IDX                        (3)
#define AT_NDIS_PWD_IDX                         (4)
#define AT_NDIS_AUTH_IDX                        (5)

#define AT_NDIS_GetPdpEntInfoAddr()             (&g_stAtNdisDhcpPara)

/* NDISID */
#define AT_NDIS_GET_CLIENT_ID()         (gastAtClientTab[AT_CLIENT_TAB_NDIS_INDEX].usClientId)

/* NDIS */
#define AT_NDIS_GET_USR_PORT_INDEX()    (g_stAtNdisDhcpPara.stUsrInfo.enPortIndex)

/* NDIScid */
#define AT_NDIS_GET_USR_CID()           (g_stAtNdisDhcpPara.stUsrInfo.ucUsrCid)



/* NDIS */
#define AT_NDIS_GET_CURR_CMD_OPT()      (gastAtClientTab[AT_NDIS_GET_USR_PORT_INDEX()].CmdCurrentOpt)

#define AT_GetNdisConnParaAddr()                (&g_stAtNdisConnPara)

#define AT_APS_IP6_ADDR_PREFIX_BYTE_LEN  (8)

#define AT_MAC_LEN                       (6)
#define AT_IPV6_ADDR_PREFIX_BYTE_LEN     (8)
#define AT_IPV6_ADDR_PREFIX_BIT_LEN      (64)

#define AT_REG_FC                        (1)
#define AT_DEREG_FC                      (0)

/* QOS_TRAFFIC_CLASS */
#define AT_QOS_TRAFFIC_CLASS_SUBSCRIBE                (0)
#define AT_QOS_TRAFFIC_CLASS_CONVERSATIONAL           (1)
#define AT_QOS_TRAFFIC_CLASS_STREAMING                (2)
#define AT_QOS_TRAFFIC_CLASS_INTERACTIVE              (3)
#define AT_QOS_TRAFFIC_CLASS_BACKGROUND               (4)



#define AT_IPV6_STR_RFC2373_TOKENS                    (8)   /*  */



#define AT_IPPROTO_UDP                  (0x11)              /* IPUDP*/
#define AT_IP_VERSION                   (4)                 /* IPIP V4 */
#define AT_IP_DEF_TTL                   (0xFF)              /* IPIP TTL */
#define AT_IP_RAND_ID                   (61468)             /* IPID*/
#define AT_IP_HDR_LEN                   (20)                /* IP  */
#define AT_UDP_HDR_LEN                  (8)                 /* UDP  */

/* Added by l60609 for DSDA Phase II, 2012-12-18, Begin */
/* CID123 */
#define AT_PS_USER_CID_1                (1)
#define AT_PS_USER_CID_2                (2)
#define AT_PS_USER_CID_3                (3)
/* Added by l60609 for DSDA Phase II, 2012-12-18, End */

/* Added by l60609 for V9R1 IPv6&TAF/SM Project, 2013-4-24, begin */
/* PSCID */
#define AT_PS_CALL_INVALID_CID          (0xFF)
#define AT_PS_CALL_INVALID_CALLID       (0xFF)

/* IPV68 */
#define AT_PS_IS_IPV6_ADDR_IID_VALID(aucIpv6Addr)\
            !((aucIpv6Addr[8] == 0x00) && (aucIpv6Addr[9] == 0x00)\
             && (aucIpv6Addr[10] == 0x00) && (aucIpv6Addr[11] == 0x00)\
             && (aucIpv6Addr[12] == 0x00) && (aucIpv6Addr[13] == 0x00)\
             && (aucIpv6Addr[14] == 0x00) && (aucIpv6Addr[15] == 0x00))


#if (FEATURE_ON == FEATURE_IPV6)
/* IPv6 ID, 64bit */
#define AT_PS_IPV6_IID_LEN              (8)
#define AT_PS_IPV6_IID_OFFSET           (8)

#endif

#define AT_PS_INVALID_RMNET_ID   (0xFFFF)

#if (FEATURE_ON == FEATURE_IPV6)
#define AT_PS_IS_PDP_TYPE_SUPPORT(pdptype)  \
            ( (TAF_PDP_IPV4 == (pdptype))   \
             || (TAF_PDP_IPV6 == (pdptype)) \
             || (TAF_PDP_IPV4V6 == (pdptype)))
#else
#define AT_PS_IS_PDP_TYPE_SUPPORT(pdptype)  \
            (TAF_PDP_IPV4 == (pdptype))
#endif

#define AT_PS_IS_RABID_VALID(ucRabId)\
    (((ucRabId) >= AT_PS_MIN_RABID) && ((ucRabId) <= AT_PS_MAX_RABID))

#define AT_PS_GET_CURR_CMD_OPT(index)   (gastAtClientTab[index].CmdCurrentOpt)
#define AT_PS_GET_CURR_DATA_MODE(index) (gastAtClientTab[index].DataMode)
#define AT_PS_GET_PPPID(index)          (gastAtClientTab[index].usPppId)

#define AT_PS_GET_RPT_CONN_RSLT_FUNC_TBL_PTR()      (g_astAtRptConnectedResultTab)
#define AT_PS_GET_RPT_CONN_RSLT_FUNC_TBL_SIZE()     (AT_ARRAY_SIZE(g_astAtRptConnectedResultTab))

#define AT_PS_GET_RPT_END_RSLT_FUNC_TBL_PTR()       (g_astAtRptEndedResultTab)
#define AT_PS_GET_RPT_END_RSLT_FUNC_TBL_SIZE()      (AT_ARRAY_SIZE(g_astAtRptEndedResultTab))

#define AT_PS_GET_REG_FC_POINT_FUNC_TBL_PTR()       (g_astAtRegFCPointTab)
#define AT_PS_GET_REG_FC_POINT_FUNC_TBL_SIZE()      (AT_ARRAY_SIZE(g_astAtRegFCPointTab))

#define AT_PS_GET_DEREG_FC_POINT_FUNC_TBL_PTR()     (g_astAtDeRegFCPointTab)
#define AT_PS_GET_DEREG_FC_POINT_FUNC_TBL_SIZE()    (AT_ARRAY_SIZE(g_astAtDeRegFCPointTab))

#define AT_PS_GET_SND_PDP_ACT_IND_FUNC_TBL_PTR()    (g_astAtSndPdpActIndTab)
#define AT_PS_GET_SND_PDP_ACT_IND_FUNC_TBL_SIZE()   (AT_ARRAY_SIZE(g_astAtSndPdpActIndTab))

#define AT_PS_GET_SND_PDP_DEACT_IND_FUNC_TBL_PTR()  (g_astAtSndPdpDeActIndTab)
#define AT_PS_GET_SND_PDP_DEACT_IND_FUNC_TBL_SIZE() (AT_ARRAY_SIZE(g_astAtSndPdpDeActIndTab))

#define AT_PS_GET_CHDATA_RNIC_RMNET_ID_TBL_PTR()    (g_astAtChdataRnicRmNetIdTab)
#define AT_PS_GET_CHDATA_RNIC_RMNET_ID_TBL_SIZE()   (AT_ARRAY_SIZE(g_astAtChdataRnicRmNetIdTab))
/* Added by l60609 for V9R1 IPv6&TAF/SM Project, 2013-4-24, end */


#define AT_PS_DIAL_RAT_TYPE_NO_ASTRICT              (0)
#define AT_PS_DIAL_RAT_TYPE_1X_OR_HRPD              (24)
#define AT_PS_DIAL_RAT_TYPE_LTE_OR_EHRPD            (36)



#define IMS_PCSCF_ADDR_PORT_MAX                     (65535)


#define AT_BUILD_EXRABID(i,j)          (((i << 6) & 0xC0) | (j & 0x3F))

#define AT_GET_RABID_FROM_EXRABID(i)   (i & 0x3F)


/*****************************************************************************
  3 
*****************************************************************************/

enum AT_PDP_STATUS_ENUM
{
    AT_PDP_STATUS_DEACT                    = 0,
    AT_PDP_STATUS_ACT                      = 1,
    AT_PDP_STATUS_BUTT
};
typedef VOS_UINT32 AT_PDP_STATUS_ENUM_UINT32;

/*****************************************************************************
    : AT_PDP_TYPE_ENUM_ENUM
    :
 ASN.1  :
    : PDP
*****************************************************************************/
enum AT_PDP_TYPE_ENUM
{
    AT_PDP_IPV4                         = 1,
    AT_PDP_IPV6                         = 2,
    AT_PDP_IPV4V6                       = 3,
    AT_PDP_PPP                          = 4,
    AT_PDP_TYPE_BUTT
};
typedef VOS_UINT8 AT_PDP_TYPE_ENUM_ENUM_U8;

/*****************************************************************************
    : AT_IPV6_STR_TYPE_ENUM
    :
 ASN.1  :
    : IPV6 String
              HEXRFC2373':'
              DEXRFC'.'
*****************************************************************************/
enum AT_IPV6_STR_TYPE_ENUM
{
    AT_IPV6_STR_TYPE_HEX                = 0x01,
    AT_IPV6_STR_TYPE_DEC                = 0x02,

    AT_IPV6_STR_TYPE_BUTT               = 0xFF
};
typedef VOS_UINT8 AT_IPV6_STR_TYPE_ENUM_UINT8;

/*****************************************************************************
    : AT_IP_ADDR_TYPE_ENUM
    :
 ASN.1  :
    : SOURCELOCALIP ADDR
*****************************************************************************/
enum AT_IP_ADDR_TYPE_ENUM
{
    AT_IP_ADDR_TYPE_SOURCE              = 0x01,
    AT_IP_ADDR_TYPE_LOCAL               = 0x02,

    AT_IP_ADDR_TYPE_BUTT                = 0xFF
};
typedef VOS_UINT8 AT_IP_ADDR_TYPE_ENUM_UINT8;

/*****************************************************************************
    : AT_HILINK_MODE_ENUM
    :
 ASN.1  :
    : HiLink
*****************************************************************************/
enum AT_HILINK_MODE_ENUM
{
    AT_HILINK_NORMAL_MODE,
    AT_HILINK_GATEWAY_MODE,
    AT_HILINK_MODE_BUTT
};
typedef VOS_UINT8 AT_HILINK_MODE_ENUM_U8;

/* APP*/
/*****************************************************************************
    : AT_APP_CONN_STATE_ENUM
    :
 ASN.1  :
    : APP
*****************************************************************************/
enum AT_APP_CONN_STATE_ENUM
{
    AT_APP_DIALING,                     /*0: indicates is connecting*/
    AT_APP_DIALED,                      /*1: indicates connected*/
    AT_APP_UNDIALED,                    /*2: indicates disconnected*/
    AT_APP_BUTT
};
typedef VOS_UINT32 AT_APP_CONN_STATE_ENUM_U32;

/*****************************************************************************
 PPP:
 1.2GGSM/GPRS/EDGE,:
     GSM          - 9600
     GPRS         - 85600
     GPRS Class33 - 107800
     EDGE         - 236800
     EDGE Class33 - 296000
      -
 2.3gRRCHSDPAcategory:
     RRCR99   - 384000
     RRCR99 - HSDPAcategory
                   6  - 3600000
                   8  - 7200000
                   9  - 10200000
                   10 - 14400000
                   12 - 1800000
                   14 - 21600000
                   18 - 28800000
                   24 - 43200000
                   26 - 57600000
                   28 - 86400000
     category - 21600000
     category - 7200000
*****************************************************************************/
enum PPP_RATE_DISPLAY_ENUM
{
    PPP_RATE_DISPLAY_GSM = 0,
    PPP_RATE_DISPLAY_GPRS,
    PPP_RATE_DISPLAY_GPRS_CALSS33,
    PPP_RATE_DISPLAY_EDGE,
    PPP_RATE_DISPLAY_EDGE_CALSS33,

    PPP_RATE_DISPLAY_R99,
    PPP_RATE_DISPLAY_DPA_CATEGORY_6,
    PPP_RATE_DISPLAY_DPA_CATEGORY_8,
    PPP_RATE_DISPLAY_DPA_CATEGORY_9,
    PPP_RATE_DISPLAY_DPA_CATEGORY_10,
    PPP_RATE_DISPLAY_DPA_CATEGORY_12,
    PPP_RATE_DISPLAY_DPA_CATEGORY_14,
    PPP_RATE_DISPLAY_DPA_CATEGORY_18,
    PPP_RATE_DISPLAY_DPA_CATEGORY_24,
    PPP_RATE_DISPLAY_DPA_CATEGORY_26,
    PPP_RATE_DISPLAY_DPA_CATEGORY_28,

    PPP_RATE_DISPLAY_BUTT
};
typedef VOS_UINT32 PPP_RATE_DISPLAY_ENUM_UINT32;


/* Modified by l60609 for V9R1 IPv6&TAF/SM Project, 2013-4-26, begin */
/*****************************************************************************
     : AT_CH_DATA_CHANNEL_ENUM
   : AT^CHDATA<datachannelid>


  1.       : 20130507
           : y00213812
       : V9R1 IPv6&TAF/SM Project

*****************************************************************************/
enum AT_CH_DATA_CHANNEL_ENUM
{
    AT_CH_DATA_CHANNEL_ID_1             = 1,
    AT_CH_DATA_CHANNEL_ID_2,
    AT_CH_DATA_CHANNEL_ID_3,
    AT_CH_DATA_CHANNEL_ID_4,
    AT_CH_DATA_CHANNEL_ID_5,
    AT_CH_DATA_CHANNEL_ID_6,
    AT_CH_DATA_CHANNEL_ID_7,

    AT_CH_DATA_CHANNEL_BUTT
};
typedef VOS_UINT32 AT_CH_DATA_CHANNEL_ENUM_UINT32;

/* Modified by l60609 for V9R1 IPv6&TAF/SM Project, 2013-4-26, end */


/*****************************************************************************
  4 
*****************************************************************************/


/*****************************************************************************
  5 
*****************************************************************************/


/*****************************************************************************
  6 STRUCT
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulDLEnqueuedPkts;                       /**/
    VOS_UINT32                          ulDLDequeuedPkts;                       /**/
    VOS_UINT32                          ulDLDroppedPkts;                        /**/
    VOS_UINT32                          ulDLMaxBlkPkts;                         /**/
    VOS_UINT32                          ulDLMaxDequeueOnce;                     /**/
} AT_AP_DL_DATA_Q_STAT_ST;


/* DHCP*/
typedef struct
{
    VOS_UINT32                          ulIPAddr;                               /* IP */
    VOS_UINT32                          ulSubNetMask;                           /* IP*/
    VOS_UINT32                          ulGateWay;                              /* DHCP Server*/
    VOS_UINT32                          ulPrimDNS;                              /*  DNS*/
    VOS_UINT32                          ulSndDNS;                               /*  DNS*/
}AT_DHCP_CONFIG_STRU;


typedef struct
{
    VOS_UINT16                          usClientID;                             /* Client ID*/
    VOS_UINT8                           ucRabID;                                /* Rab ID*/
    VOS_UINT8                           ucCid;                                  /* CID*/
    AT_PDP_STATE_ENUM_U8                enState;                                /* State*/
    VOS_UINT8                           aucReserved[3];
    VOS_UINT32                          ulFlowCtrlState;                        /* Flow Ctrl State ; 1: flow ctrl ,0: no flow ctrl*/
    VOS_UINT32                          ulSpeed;                                /* Um Speed*/

    VOS_UINT32                          ulDLMaxRate;                            /* */
    VOS_UINT32                          ulULMaxRate;                            /* */
    VOS_UINT32                          ulDLCurrentRate;                        /* */
    VOS_UINT32                          ulULCurrentRate;                        /* */
    VOS_UINT32                          ulRateCalcPeriod;                       /* */
    AT_DHCP_CONFIG_STRU                 stDhcpCfg;
}AT_CTRL_ENTITY_STRU;

typedef struct AT_DHCP_PARA
{
    VOS_UINT16                          usClientID;                             /* Client ID*/
    VOS_UINT8                           ucRabID;                                /* Rab ID*/
    VOS_UINT8                           ucCid;                                  /* CID*/
    VOS_UINT32                          ulSpeed;                                /* Um Speed*/
    VOS_UINT32                          ulDLMaxRate;                            /* */
    VOS_UINT32                          ulULMaxRate;                            /* */
    AT_DHCP_CONFIG_STRU                 stDhcpCfg;
}AT_DHCP_PARA_STRU;

typedef struct
{
  VOS_UINT8                             ucCode;                                 /* Request code */
  VOS_UINT8                             ucId;                                   /* Identification */
  VOS_UINT16                            usLength;                               /* Length of packet */
}AT_PPP_FRAME_HEAD_STRU;

/* IP U32*/
typedef struct
{
    VOS_UINT32                          ulIpAddr;                               /*U32*/
}IN_ADDR_ST;


typedef struct
{
    VOS_UINT8                           ucType;
    VOS_UINT8                           ucCode;
    VOS_UINT16                          usCheckSum;
    VOS_UINT16                          usId;
    VOS_UINT16                          usSeq;
}ICMP_ECHO_HEAD_ST;

typedef struct
{
    VOS_UINT32                          ulIPAddr;                               /* IP */
    VOS_UINT32                          ulPrimDNS;                              /*  DNS*/
    VOS_UINT32                          ulSndDNS;                               /*  DNS*/
    VOS_UINT32                          ulPrimWINNS;                            /* WINNS*/
    VOS_UINT32                          ulSncWINNS;                             /* WINNS */
}AT_DHCP_SETUP_PARAM_ST;


/* DHCP */
typedef struct
{
    AT_DHCP_CONFIG_STRU                 stDHCPConfig;                           /* DHCP*/
    VOS_UINT32                          ulDHCPServerOn;                         /* DHCP*/
}AT_DHCP_ENTITY_ST;

/* PDP*/
typedef struct
{
    VOS_UINT32                          ulspeed;                                /* bps */
    AT_PDP_STATUS_ENUM_UINT32           enActiveSatus;                          /* 0 */
}AT_NDIS_PRO_STRU;

/*****************************************************************************
    : AT_PDP_SAVE_STATE_STRU
    :
 ASN.1  :
    : 
*****************************************************************************/
typedef struct
{

    AT_PDP_STATE_ENUM_U8                enIpv4State;
    AT_PDP_STATE_ENUM_U8                enIpv6State;
    AT_PDP_STATE_ENUM_U8                enIpv4v6State;

} AT_PDP_SAVE_STATE_INFO_STRU;





/*****************************************************************************
     : AT_NDIS_MSG_STRU
   :
 ASN.1 :
   :

  1.       : 20111224
           : o00132663
       : PSAT_NDIS_DHCPINFO_RPT_IND_STRU
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucClientId;
    VOS_UINT8                           ucSysMode;
    VOS_UINT16                          usMsgSize;
    VOS_UINT32                          ulMsgId;
    union
    {
        AT_NDIS_PDNINFO_CFG_CNF_STRU    stNdisPdnInfoCfgCnf;
        AT_NDIS_PDNINFO_REL_CNF_STRU    stNdisPdnInfoRelCnf;
        AT_NDIS_USBABNORMAL_IND_STRU    stNdisUsbabnormalInd;
    }unMsg;
} AT_NDIS_MSG_STRU;

/*****************************************************************************
     : AT_NDISCONN_PARA_STRU
   : NDISNDISCONN 
*****************************************************************************/
typedef struct
{
    VOS_UINT32  ulConnectState;                                                 /* , 0 1  */
    VOS_UINT8   ucCID;                                                          /* AT CID*/
    VOS_UINT8   aucAPN[TAF_MAX_APN_LEN+1];                                      /* ATAPN */
    VOS_UINT8   aucUsername[TAF_MAX_GW_AUTH_USERNAME_LEN+1];                    /* username*/
    VOS_UINT8   aucPassword[TAF_MAX_GW_AUTH_PASSWORD_LEN+1];                    /* password*/
    VOS_UINT8   ucReserved;
    VOS_UINT16  usAuthType;
} AT_NDISCONN_PARA_STRU;

/*****************************************************************************
     : AT_CLINTID_RABID_MAP_STRU
   :
 ASN.1 :
   :

  1.       : 2012218
           : L47619
       : AP-MODEM
  2.       : 20130415
           : f00179208
       : C
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulUsed;   /* FCIDVOS_TRUE:VOS_FALSE: */
    VOS_UINT32                          ulRabIdMask;
    MODEM_ID_ENUM_UINT16                enModemId;
    FC_PRI_ENUM_UINT8                   enFcPri;
    VOS_UINT8                           aucReserve[1];                          /*  */
} AT_FCID_MAP_STRU;

/*****************************************************************************
      : AT_IPHDR_STRU
    :
 ASN.1  :
    : IPv4 packet header 
  1.       : 2012612
           : S62952
       : 
*****************************************************************************/
typedef struct
{
#if (VOS_LITTLE_ENDIAN == VOS_BYTE_ORDER)                   /* */
    VOS_UINT8                           ucIpHdrLen  :4;     /* IP */
    VOS_UINT8                           ucIpVer     :4;     /* IP*/
#elif (VOS_BIG_ENDIAN == VOS_BYTE_ORDER)                    /* */
    VOS_UINT8                           ucIpVer     :4;     /* IP*/
    VOS_UINT8                           ucIpHdrLen  :4;     /* IP */
#else
#error  "Please fix Macro VOS_BYTE_ORDER"                   /* VOS_BYTE_ORDER*/
#endif
    VOS_UINT8                           ucServiceType;      /* IP TOS*/
    VOS_UINT16                          usTotalLen;         /* IP*/
    VOS_UINT16                          usIdentification;   /* IPID*/
    VOS_UINT16                          usOffset;           /* IP*/
    VOS_UINT8                           ucTTL;              /* IPTTL*/
    VOS_UINT8                           ucProtocol;         /* IP*/
    VOS_UINT16                          usCheckSum;         /* IP*/
    VOS_UINT32                          ulSrcAddr;          /* IP*/
    VOS_UINT32                          ulDstAddr;          /* IP*/
} AT_IPHDR_STRU;

/*****************************************************************************
      : AT_UDP_HDR_STRU
    :
 ASN.1  :
    : UDP header 
  1.       : 2012612
           : S62952
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usSrcPort;          /*  */
    VOS_UINT16                          usDstPort;          /*  */
    VOS_UINT16                          usLen;              /* UDP */
    VOS_UINT16                          usChecksum;         /* UDP */
} AT_UDP_HDR_STRU;

/*****************************************************************************
      : AT_UDP_PACKET_FORMAT_STRU
    :
 ASN.1  :
    : UDP packet 
  1.       : 2012612
           : S62952
       : 
*****************************************************************************/
typedef struct
{

    AT_IPHDR_STRU                       stIpHdr;            /* IP */
    AT_UDP_HDR_STRU                     stUdpHdr;           /* UDP */
    VOS_UINT32                          ulBody;
} AT_UDP_PACKET_FORMAT_STRU;

/* Added by l60609 for DSDA Phase II, 2012-12-18, Begin */
/*****************************************************************************
     : AT_PS_RMNET_ID_TAB
   : PSModemId,cid,FcId
   1.       : 20121218
            : L60609
        : 
*****************************************************************************/
typedef struct
{
    MODEM_ID_ENUM_UINT16                enModemId;
    FC_ID_ENUM_UINT8                    enFcId;
    VOS_UINT8                           ucUsrCid;
}AT_PS_RMNET_ID_TAB;
/* Added by l60609 for DSDA Phase II, 2012-12-18, End */

/*****************************************************************************
    : AT_PDP_ENTITY_STRU
    :
 ASN.1  :
    : PDP
*****************************************************************************/
typedef struct
{
    AT_PS_USER_INFO_STRU                stUsrInfo;
    VOS_UINT8                           ucIpv4Cid;
    VOS_UINT8                           ucIpv6Cid;
    VOS_UINT8                           ucIpv4v6Cid;
    AT_PDP_STATE_ENUM_U8                enIpv4State;
    AT_PDP_STATE_ENUM_U8                enIpv6State;
    AT_PDP_STATE_ENUM_U8                enIpv4v6State;
    VOS_UINT8                           aucRsv[2];

    AT_IPV4_DHCP_PARAM_STRU             stIpv4Dhcp;
    AT_IPV6_DHCP_PARAM_STRU             stIpv6Dhcp;

}AT_PDP_ENTITY_STRU;


/*****************************************************************************
     : AT_CHDATA_RNIC_RMNET_ID_STRU
   : AT^CHDATARNIC

  1.       : 2013426
           : L60609
       : V9R1 IPv6&TAF/SM
*****************************************************************************/
typedef struct
{
    AT_CH_DATA_CHANNEL_ENUM_UINT32      enChdataValue;
    RNIC_RMNET_ID_ENUM_UINT8            enRnicRmNetId;

    VOS_UINT8                           aucReserved[3];
}AT_CHDATA_RNIC_RMNET_ID_STRU;

/*****************************************************************************
     : AT_DISPLAY_RATE_STRU
   : 

  1.       : 2016928
           : l00373346
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucDlSpeed[AT_AP_SPEED_STRLEN + 1];
    VOS_UINT8                           ucUlSpeed[AT_AP_SPEED_STRLEN + 1];
    VOS_UINT8                           aucReserved[2];
}AT_DISPLAY_RATE_STRU;

/*****************************************************************************
  7 UNION
*****************************************************************************/


/*****************************************************************************
  8 OTHERS
*****************************************************************************/


/*****************************************************************************
  9 
*****************************************************************************/

/* */
extern VOS_UINT32                       g_ulLcStartTime;

extern AT_PDP_ENTITY_STRU               g_stAtNdisDhcpPara;

extern TAF_PDP_TYPE_ENUM_UINT8          g_enAtFirstNdisActPdpType;

extern AT_NDISCONN_PARA_STRU            g_stAtNdisConnPara;

extern TAF_PDP_TYPE_ENUM_UINT8          g_enAtNdisActPdpType;

extern AT_DIAL_PARAM_STRU               gstAtNdisAddParam;

extern AT_HILINK_MODE_ENUM_U8           g_enHiLinkMode;

extern AT_PDP_ENTITY_STRU               g_stAtAppPdpEntity;

extern AT_DIAL_PARAM_STRU               g_stAtAppDialPara;

extern AT_PDP_STATE_ENUM_U8             g_enAtAppSaveState;

extern AT_PDP_SAVE_STATE_INFO_STRU      g_stAtAppSaveStateInfo;

extern TAF_PDP_TYPE_ENUM_UINT8          g_enAtAppActPdpType;

extern TAF_PDP_TYPE_ENUM_UINT8          g_enAtAppFirstActPdpType;

extern AT_IPV6_RA_INFO_STRU             g_stAtAppRaInfo;

extern AT_FCID_MAP_STRU                 g_stFcIdMaptoFcPri[];

extern AT_PS_RMNET_ID_TAB               g_astPsRmNetIdTab[];

/* Modified by l60609 for V9R1 IPv6&TAF/SM Project, 2013-4-24, begin */
extern AT_PS_REPORT_CONN_RESULT_STRU    g_astAtRptConnectedResultTab[];

extern AT_PS_REPORT_END_RESULT_STRU     g_astAtRptEndedResultTab[];

extern AT_PS_REG_FC_POINT_STRU          g_astAtRegFCPointTab[];

/* Modified by l60609 for V9R1 IPv6&TAF/SM Project, 2013-4-24, end */

/*****************************************************************************
  10 
*****************************************************************************/
/*****************************************************************************
     : AT_GetDhcpPara
   : DHCP(DHCP)
   : pstConfig                  - DHCP()
   : 
     : VOS_VOID
   :
   :
*****************************************************************************/
VOS_VOID AT_GetDhcpPara(
    AT_DHCP_PARA_STRU                  *pstConfig,
    AT_IPV4_DHCP_PARAM_STRU            *pstIpv4Dhcp
);

/******************************************************************************
     : AT_GetDisplayRate
   : NAS
   : *pstSpeed     ----    
   : 
     : 
   :
   :
******************************************************************************/
VOS_UINT32 AT_GetDisplayRate(
    VOS_UINT16                          usClientId,
    AT_DISPLAY_RATE_STRU               *pstSpeed
);

/******************************************************************************
     : AT_CtrlConnIndProc
   : DHCP
   : pstEventTAF_PS_CALL_EVENT_INFO_STRU
   : 
     : 
   :
   :

       :
  1.       : 2010123
           : sunshaohua
       : 
******************************************************************************/
VOS_VOID AT_CtrlConnIndProc(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent,
    AT_USER_TYPE                        ucUserType
);

/******************************************************************************
 Function:      AT_CtrlGetPDPAuthType
 Description:    PCPDP
 Calls:
 Data Accessed:
 Data Updated:
 Input:
                 usTotalLen     PDP
 Output:
 Return:        0   no auth
                1   pap
                2   chap
******************************************************************************/
PPP_AUTH_TYPE_ENUM_UINT8 AT_CtrlGetPDPAuthType(
    VOS_UINT32                          Value,
    VOS_UINT16                          usTotalLen
);
/*****************************************************************************
     : AT_CtrlGetTapPdpAuthType
   : CLppp
   : 
   : 
     : TAF_PDP_AUTH_TYPE_ENUM_UINT8
   :
   :

       :
  1.       : 2015129
           : y00322978
       : 

*****************************************************************************/
TAF_PDP_AUTH_TYPE_ENUM_UINT8 AT_ClGetPdpAuthType(
    VOS_UINT32                          Value,
    VOS_UINT16                          usTotalLen
);

/******************************************************************************
 Function:       AT_CtrlFreePCOContext
 Description:    PCO
 Calls:
 Data Accessed:
 Data Updated:
 Input:
                 usTotalLen     PDP
 Output:
 Return:        0   no auth
                1   pap
                2   chap
******************************************************************************/
VOS_VOID AT_CtrlFreePCOContext(
    PPP_REQ_CONFIG_INFO_STRU            *pstPppReqCfgInfo
);


/******************************************************************************
 Function:       AT_CtrlMakePCOPapAuthInfo
 Description:    ATPCO
 Calls:
 Data Accessed:
 Data Updated:
 Input:         pstPppReqCfgInfo    PCO
                pucUserName         
                usUserNameLen       
                pucPassWord         
                usPassWordLen       
 Output:
 Return:        VOS_OK
                VOS_ERR
 Others:        pap
                1 byte    -- code
                1 byte    -- id
                2 byte    -- length (include "code", "id", "length")
                1 byte    -- username length
                x byte    -- username
                1 byte    -- password length
                x byte    -- password
                :TTF_NDIS_CtrlFreePCOContext
******************************************************************************/
VOS_UINT32 AT_CtrlMakePCOPapAuthInfo(
    PPP_REQ_CONFIG_INFO_STRU            *pstPppReqCfgInfo,
    VOS_UINT8                           *pucUserName,
    VOS_UINT16                          usUserNameLen,
    VOS_UINT8                           *pucPassWord,
    VOS_UINT16                          usPassWordLen
);


/******************************************************************************
 Function:       AT_CtrlMakePCOChapAuthInfo
 Description:    ATPCO
 Calls:
 Data Accessed:
 Data Updated:
 Input:         pstPppReqCfgInfo    PCO
                pucUserName         
                usUserNameLen       
                pucPassWord         
                usPassWordLen       
 Output:
 Return:
 Others:        chap challenge 
                1 byte    -- code
                1 byte    -- id
                2 byte    -- length (include "code", "id", "length")
                1 byte    -- challenge length   (16 bytes)
                x byte    -- challenge
                x byte    -- name               ("huawei.com" )
                chap response 
                1 byte    -- code
                1 byte    -- id
                2 byte    -- length (include "code", "id", "length")
                1 byte    -- response length    (16 bytes)
                x byte    -- response
                x byte    -- name               (from username)
******************************************************************************/
VOS_UINT32 AT_CtrlMakePCOChapAuthInfo(
    PPP_REQ_CONFIG_INFO_STRU            *pstPppReqCfgInfo,
    VOS_UINT8                           *pucUserName,
    VOS_UINT16                           usUserNameLen,
    VOS_UINT8                           *pucPassWord,
    VOS_UINT16                           usPassWordLen
);

/******************************************************************************
 : AT_Ipv4AddrAtoi
 : IPV4

 :
   pcString [in] IP,char * pcString="192.168.0.1"
   pucNumber [out] IP,char pucNumber[4]={192,168,0,1};

   :
    TODO: ...

 : TODO: ...
 : TODO: ...
     : /00064416 [2010-02-02]
******************************************************************************/
VOS_UINT32 AT_Ipv4AddrAtoi(VOS_CHAR *pcString, VOS_UINT8 *pucNumber);

/******************************************************************************
 : AT_Ipv4AddrItoa
 : IPV4

 :
   pcString [out] IP,char * pcString="192.168.0.1"
   pucNumber [in] IP,char pucNumber[4]={192,168,0,1};

   :
    TODO: ...

 : TODO: ...
 : TODO: ...
     : /00064416 [2010-02-02]
******************************************************************************/
VOS_UINT32 AT_Ipv4AddrItoa(VOS_CHAR *pcString, VOS_UINT8 *pucNumber);

/*****************************************************************************
     : AT_Ipv4Addr2Str
   : IPV4
   : pucNumber      - IPV4
   : pcString       - 
     : VOS_UINT32

*****************************************************************************/
VOS_UINT32 AT_Ipv4Addr2Str(
    VOS_CHAR                           *pcString,
    VOS_UINT8                          *pucNumber
);

VOS_UINT32 AT_Ipv6AddrAtoi(VOS_CHAR *pcString, VOS_UINT8 *pucNumber);

/*****************************************************************************
     : AT_Ipv6LenStrToAddrProc
   : IPSMIP(IPV6).
   : pucStr - IP
             pucColonCount - 
             pucDotCount   - 
   : pucIpAddr - SMIP
     : VOS_VOID
   :
   :
*****************************************************************************/
VOS_VOID AT_Ipv6LenStrToAddrProc(
    VOS_UINT8                          *pucStr,
    VOS_UINT8                          *pucIpAddr,
    VOS_UINT8                           ucColonCount,
    VOS_UINT8                           ucDotCount
);


/******************************************************************************
     : AT_Ipv6LenStrToAddrProcCompressed
   : IPV6.
   : pucStr       - IP
             ucColonCount - 
             ucDotCount   - 
             ucStrlen     - 
             ucIdxPos     - 
   : pucIpAddr - IP
     : VOS_VOID
   :
   :
******************************************************************************/
VOS_VOID  AT_Ipv6LenStrToAddrProcCompressed(
    VOS_UINT8                          *pucStr,
    VOS_UINT8                           ucColonCount,
    VOS_UINT8                           ucDotCount,
    VOS_UINT8                           ucStrlen,
    VOS_UINT8                           ucIdxPos
);


/*****************************************************************************
     : AT_Ipv6LenStrToAddrAccess
   : IPV6
   : pucStr        - IP
   : pucColonCount - 
             pucDotCount   - 
             pucStrlen     - IPV6
             pucIdxPos     - 
     : VOS_OK - 
             VOS_ERR - 
   :
   :
*****************************************************************************/
VOS_UINT32 AT_Ipv6LenStrToAddrAccess(
    VOS_UINT8                          *pucStr,
    VOS_UINT8                          *pucColonCount,
    VOS_UINT8                          *pucDotCount,
    VOS_UINT8                          *pucStrlen,
    VOS_UINT8                          *pucIdxPos
);


/******************************************************************************
     : AT_Ipv6LenStrToAddr
   : IPSMIP(IPV6).
   : pucStr - IP
   : pucIpAddr - SMIP
     : VOS_OK  - 
             VOS_ERR - 
   :
   :
******************************************************************************/
VOS_UINT32  AT_Ipv6LenStrToAddr(
    VOS_UINT8                          *pucStr,
    VOS_UINT8                          *pucIpAddr
);

VOS_VOID AT_PcscfIpv4Addr2Str(
    VOS_CHAR                           *pcString,
    VOS_UINT8                          *pucNumber
);

VOS_UINT32 AT_PcscfIpv6StrToAddr(
    VOS_UINT8                          *pucStr,
    VOS_UINT8                          *pucIpAddr,
    VOS_UINT8                           ucColonCount
);

VOS_UINT32  AT_PortAtoI(
    VOS_CHAR                         *pcString,
    VOS_UINT32                       *pulValue
);

VOS_UINT32 AT_CheckPcscfIpv6Addr(
    VOS_CHAR                           *pucIpv6Str,
    VOS_UINT32                         *pulPortExistFlg
);

VOS_UINT32  AT_ParsePortFromPcscfIpv6Addr(
    VOS_UINT8                          *pucStr,
    VOS_UINT8                          *pucIpv6Addr,
    VOS_UINT32                         *pulPortExistFlg,
    VOS_UINT32                         *pulPortNum
    
);

VOS_UINT32  AT_ParseAddrFromPcscfIpv6Addr(
    VOS_UINT8                          *pucStr,
    VOS_UINT8                          *pucIpAddr
);


VOS_UINT32  AT_Ipv6PcscfDataToAddr(
    VOS_UINT8                          *pucStr,
    VOS_UINT8                          *pucIpAddr,
    VOS_UINT32                         *pulPortExistFlg,
    VOS_UINT32                         *pulPortNum
    
);

/*****************************************************************************
     : AT_Ipv6AddrToStr
   : IPV6
   : aucIpAddr[]    - IPV6()
             enIpStrType    - IPV6
   : aucAddrStr[]   - IPV6()
     : VOS_OK         - 
             VOS_ERR        - 
   :
   :
*****************************************************************************/
VOS_UINT32 AT_Ipv6AddrToStr(
    VOS_UINT8                           aucAddrStr[],
    VOS_UINT8                           aucIpAddr[],
    AT_IPV6_STR_TYPE_ENUM_UINT8         enIpStrType
);

/*****************************************************************************
     : AT_Itoa
   : (1016), ASCII, 
   : usValue    - ASCII
             pcStr      - 
             usRadix    - 
   : 
     : VOS_CHAR*
   :
   :
*****************************************************************************/
VOS_CHAR* AT_Itoa(
    VOS_UINT16                          usValue,
    VOS_CHAR                           *pcStr,
    VOS_UINT16                          usRadix,
    VOS_UINT32                          ulLength
);
/******************************************************************************
     : AT_AtoI
   : 
   : pString 
   : 
     :  IP
   :
   :
******************************************************************************/
VOS_UINT64  AT_AtoI(
    VOS_UINT8                         *pString
);


/******************************************************************************
     : AT_AtoI
   : ()
   : pString 
   : 
     :  IP
   :
   :
******************************************************************************/
VOS_INT32  AT_AtoInt(
    VOS_UINT8                          *pString,
    VOS_INT32                          *pOut
);

/*****************************************************************************
     : AT_FindIpv6AddrZeroFieldsToBeCompressed
   : "::"IP
   : ausAddrValue[]     - IPV6
             ucTokensNum        - 
   : pucZeroFieldStart  - 0IP
             pucZeroFieldCount  - 0IP
     : VOS_OK             - 
             VOS_ERR            - 
   :
   :
*****************************************************************************/
VOS_UINT32 AT_FindIpv6AddrZeroFieldsToBeCompressed(
    VOS_UINT8                          *pucZeroFieldStart,
    VOS_UINT8                          *pucZeroFieldCount,
    VOS_UINT16                          ausAddrValue[],
    VOS_UINT8                           ucTokensNum
);


/*****************************************************************************
     : AT_ConvertIpv6AddrToCompressedStr
   : IPV6
   : aucIpAddr[]    - IPV6()
             ucTokensNum    - 
   : aucAddrStr[]   - IPV6()
     : VOS_OK         - 
             VOS_ERR        - 
   :
   :
*****************************************************************************/
VOS_UINT32 AT_ConvertIpv6AddrToCompressedStr(
    VOS_UINT8                           aucAddrStr[],
    VOS_UINT8                           aucIpAddr[],
    VOS_UINT8                           ucTokensNum
);

VOS_UINT32 AT_GetLanAddr32(
  VOS_UINT8                            *pucAddr
);
TAF_UINT32 AT_DHCPGetIPMask(
    TAF_UINT32                          ulIpAddrHL
);
VOS_UINT32 AT_DHCPGetGateWay(
    VOS_UINT32                          ulIpAddrHL,
    VOS_UINT32                          ulMaskHL
);

/*****************************************************************************
     : AT_CalcIpHdrCRC16
   : IPCRC
   : pucData    - IP
             usSize     - IP
   : 
     : ulCheckSum - CRC
   :
   :
*****************************************************************************/
VOS_UINT16 AT_CalcIpHdrCRC16(
    VOS_UINT8                          *pucData,
    VOS_UINT16                          usSize
);


/*****************************************************************************
     : AT_BuildUdpHdr
   : IPUDP(UDP)
   : pstUdpPkt  - UDP
             usLen      - UDP
             ulSrcAddr  - IP
             ulDstAddr  - IP
             usSrcPort  - 
             usDstPort  - 
   : 
     : VOS_OK     - 
             VOS_ERR    - 
   :
   :
*****************************************************************************/
VOS_UINT32 AT_BuildUdpHdr(
    AT_UDP_PACKET_FORMAT_STRU          *pstUdpPkt,
    VOS_UINT16                          usLen,
    VOS_UINT32                          ulSrcAddr,
    VOS_UINT32                          ulDstAddr,
    VOS_UINT16                          usSrcPort,
    VOS_UINT16                          usDstPort
);


/*****************************************************************************
     : AT_NidsGet3gppSmCauseByPsCause
   : PS3GPP(E)SM Cause, 3GPP
             0(Unknown error/Unspecified error)
   : enCause - PS
   : 
     : VOS_UINT16
   :
   :
*****************************************************************************/
VOS_UINT32 AT_Get3gppSmCauseByPsCause(
    TAF_PS_CAUSE_ENUM_UINT32            enCause
);


/*****************************************************************************
     : AT_SaveNdisConnDailPara
   : NDISCONNNDISCONN
   : AT_PARSE_PARA_TYPE_STRU            *pstParaList
   : 
     : VOS_VOID
   :
   :
*****************************************************************************/
VOS_VOID AT_SaveNdisConnDailPara(
    AT_PARSE_PARA_TYPE_STRU            *pstParaList
);


/*****************************************************************************
     : AT_SendNdisRelReq
   : PDN
   : TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
   : 
     : VOS_UINT32
   :
   :
*****************************************************************************/
VOS_UINT32 AT_SendNdisRelReq(
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
);

/*****************************************************************************
     : AT_RcvNdisPdnInfoCfgCnf
   : NDIS
   : AT_NDIS_PDNINFO_CFG_CNF_STRU       *pstNdisPdnInfoCfgCnf
   : 
     : VOS_UINT32
   :
   :
*****************************************************************************/
VOS_UINT32 AT_RcvNdisPdnInfoCfgCnf(
    AT_NDIS_PDNINFO_CFG_CNF_STRU       *pstNdisPdnInfoCfgCnf
);

/*****************************************************************************
     : AT_RcvNdisPdnInfoRelCnf
   : NDIS
   : AT_NDIS_PDNINFO_REL_CNF_STRU       *pstNdisPdnInfoRelCnf
   : 
     : VOS_UINT32
   :
   :
*****************************************************************************/
VOS_UINT32 AT_RcvNdisPdnInfoRelCnf(
    AT_NDIS_PDNINFO_REL_CNF_STRU       *pstNdisPdnInfoRelCnf
);



#if (FEATURE_ON == FEATURE_IPV6)
/*****************************************************************************
     : AT_NdisIpv6DhcpRest
   : IPV6
   : 
   : 
     :
   :
   :
*****************************************************************************/
VOS_VOID AT_NdisIpv6DhcpRest(VOS_VOID);


/*****************************************************************************
     : AT_NdisCtrlConnIpv6IndProc
   : IPV6
   : 
   : 
     :
   :
   :
*****************************************************************************/
VOS_VOID  AT_NdisCtrlConnIpv6IndProc(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU         *pstEvent
);

/*****************************************************************************
     : AT_NdisCheckIpv6PdpState
   : IPv6PDP
   : enPdpState - PDP
   : 
     : VOS_TRUE   - PDP
             VOS_FALSE  - PDP
   :
   :
*****************************************************************************/
VOS_UINT32 AT_NdisCheckIpv6PdpState(
    AT_PDP_STATE_ENUM_U8                enPdpState
);
#endif


/*****************************************************************************
     : AT_NdisStateChangeProc
   : NDISPC
   : ucPdpType --- PDP
             ulStat    --- NDIS:0-; 1-
   : 
     : VOS_VOID
   :
   :
*****************************************************************************/
VOS_VOID AT_NdisStateChangeProc(
    VOS_UINT8                           ucPdpType,
    VOS_UINT32                          ulStat,
    TAF_PS_CAUSE_ENUM_UINT32            enCause
);


/******************************************************************************
     : AT_NdisGetState
   : NDIS/
   : ucIndex --- 
   : 
     : AT_PDP_STATE_ENUM_U8  /

   :
   :
******************************************************************************/
AT_PDP_STATE_ENUM_U8 AT_NdisGetState(
    VOS_UINT8                           ucCid
);


/*****************************************************************************
     : AT_NdisCheckPdpIdleState
   : ideldeactingPDP
   : 
   : 
     :
   :
   :
*****************************************************************************/
VOS_UINT32 AT_NdisCheckPdpIdleState(VOS_VOID);

/*****************************************************************************
     : AT_NdisAddrProc
   : NDIS
   : pstConfig --- DHCP
             pstEvent  --- 
   : 
     :
   :
   :
*****************************************************************************/
VOS_VOID AT_NdisAddrProc(
    AT_DHCP_CONFIG_STRU                 *pstConfig,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU   *pstEvent
);


/*****************************************************************************
     : AT_NdisCheckIpv6PdpState
   : IPv4PDP
   : enPdpState - PDP
   : 
     : VOS_TRUE   - PDP
             VOS_FALSE  - PDP
   :
   :
*****************************************************************************/
VOS_UINT32 AT_NdisCheckIpv4PdpState(
    AT_PDP_STATE_ENUM_U8                enPdpState
);


/*****************************************************************************
     : AT_NdisGetDhcpPara
   : DHCP
   : 
   : VOS_VOID
     :
   :
   :
*****************************************************************************/
VOS_VOID AT_NdisGetDhcpPara(
    AT_DHCP_PARA_STRU                  *pstConfig
);


/*****************************************************************************
     : AT_NdisSetState
   : NDIS
   : ucPdpType --- PDP
             enState   --- PDP
   : 
     : VOS_VOID
   :
   :
*****************************************************************************/
VOS_VOID AT_NdisSetState(
    VOS_UINT8                              ucPdpType,
    AT_PDP_STATE_ENUM_U8                   enState
);

/*****************************************************************************
     : AT_NdisPsRspPdpActEvtRejProc
   : pdpNDIS
   : ucIndex --- 
             pEvent  --- 
   : 
     : 
   :
   :
*****************************************************************************/
VOS_VOID  AT_NdisPsRspPdpActEvtRejProc(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU  *pstEvent
);


/*****************************************************************************
     : AT_NdisPsRspPdpActEvtCnfProc
   : pdpNdis
   : ucIndex --- 
             pEvent  --- 
   : 
     : 
   :
   :
*****************************************************************************/
VOS_VOID  AT_NdisPsRspPdpActEvtCnfProc(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
);


/*****************************************************************************
     : AT_NdisPsRspPdpDeactEvtCnfProc
   : pdpNdis
   : ucIndex --- 
             pEvent  --- 
   : 
     : 
   :
   :
*****************************************************************************/
VOS_VOID  AT_NdisPsRspPdpDeactEvtCnfProc(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
);


/*****************************************************************************
     : AT_NdisPsRspPdpDeactivatedEvtProc
   : pdpNdis
   : ucIndex --- 
             pEvent  --- 
   : 
     : 
   :
   :
*****************************************************************************/
VOS_VOID  AT_NdisPsRspPdpDeactivatedEvtProc(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_DEACTIVATE_IND_STRU *pstEvent
);


/*****************************************************************************
     : AT_NDIS_ParseUsrInfo
   : NDIS
   : ucIndex     - (ClientId)
   : pstUserInfo - 
   : 
     : VOS_VOID
*****************************************************************************/
VOS_VOID AT_NDIS_ParseUsrInfo(
    VOS_UINT8                           ucIndex,
    AT_PS_USER_INFO_STRU               *pstUsrInfo
);

VOS_VOID AT_NDIS_ConnStatusChgProc(NCM_IOCTL_CONNECT_STUS_E enStatus);


#if (FEATURE_ON == FEATURE_IPV6)
/*****************************************************************************
     : AT_CalcIpv6LanAddrFromIpv6Prefix
   : IPV6IPV6
   : pucPrefix
             ulPrefixByteLen
             pucIpv6LanAddr
             ulIpv6LanAddrLen
   : 
     : VOS_UINT32
   :
   :
*****************************************************************************/
VOS_UINT32 AT_CalcIpv6LanAddrFromIpv6Prefix(
    VOS_UINT8                          *pucPrefix,
    VOS_UINT32                          ulPrefixByteLen,
    VOS_UINT8                          *pucIpv6LanAddr,
    VOS_UINT32                          ulIpv6LanAddrLen
);


/*****************************************************************************
     : AT_AppRcvIpv6LanAddr
   : NASHOSTHOSTIPv6NAS-
             IPv6
   : aucLanAddr       - Ipv6
             ulLanAddrByteLen - , BYTE
             ulPrefixBitLen   - , BIT
   : 
     : VOS_VOID
   :
   :
*****************************************************************************/
VOS_VOID AT_AppRcvIpv6LanAddr(
    VOS_UINT8                           aucLanAddr[],
    VOS_UINT32                          ulLanAddrByteLen,
    VOS_UINT32                          ulPrefixBitLen
);


/*****************************************************************************
     : AT_AppRcvIpV6Prefix
   : NASHOSTHOSTGGSNRANAS-
             IPv6
   : VOS_UINT8  aucPrefix   Ipv6
             VOS_UINT32 ulPrefixLen BIT
   : 
     : VOS_VOID
   :
   :
*****************************************************************************/
VOS_VOID AT_AppRcvIpv6Prefix(
    VOS_UINT8                           aucPrefix[],
    VOS_UINT32                          ulPrefixBitLen
);


/*****************************************************************************
     : AT_AppRcvPrefixIpV6PreferredLifetime
   : PreferredLifetime
   : ulPrefixPreferredLifetime - 
   : 
     : VOS_VOID
   :
   :
*****************************************************************************/
VOS_VOID AT_AppRcvPrefixIpv6PreferredLifetime(
    VOS_UINT32                          ulPrefixPreferredLifetime
);


/*****************************************************************************
     : AT_RcvPrefixIpV6ValidLifetime
   : ValidLifetime
   : ulValidLifetime - 
   : 
     : VOS_VOID
   :
   :
*****************************************************************************/
VOS_VOID AT_AppRcvPrefixIpv6ValidLifetime(
    VOS_UINT32                          ulValidLifetime
);


/*****************************************************************************
     : AT_RcvIpV6LinkMtu
   : HOSTMTU: MTUAPP
             RAHOSTNASMTU
   : ulMTU - MTU Size
   : 
     : VOS_VOID
   :
   :
*****************************************************************************/
VOS_VOID AT_AppRcvIpv6LinkMtu(
    VOS_UINT32                          ulMtu
);


/*****************************************************************************
     : AT_RcvEnableIpV6Prefix
   : IPV6
   : VOS_VOID
   : 
     : VOS_VOID
   :
   :
*****************************************************************************/
VOS_VOID AT_AppRcvEnableIpv6Prefix(VOS_VOID);


/*****************************************************************************
     : AT_AppProcIpv6RaInfo
   : Router Advertisement IP, 
   : pstRaInfoNotifyInd         - RA
   : 
     : VOS_VOID
   :
   :
*****************************************************************************/
VOS_VOID AT_AppProcIpv6RaInfo(TAF_PS_IPV6_INFO_IND_STRU *pstRaInfoNotifyInd);


/*****************************************************************************
     : AT_AppCtrlConnIpv6IndProc
   : IPv6
   : pstAppPdpEntity - PDP
             pstEvent        - 
   : 
     : VOS_VOID
   :
   :
*****************************************************************************/
VOS_VOID AT_AppCtrlConnIpv6IndProc(
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
);


/*****************************************************************************
     : AT_AppDhcpv6Reset
   : IPv6
   : VOS_VOID
   : 
     : VOS_VOID
   :
   :
*****************************************************************************/
VOS_VOID AT_AppDhcpv6Reset(VOS_VOID);
#endif


/*****************************************************************************
     : AT_AppDhcpReset
   : APPDHCP
   : VOS_VOID
   : 
     : VOS_VOID
   :
   :
*****************************************************************************/
VOS_VOID AT_AppDhcpReset(VOS_VOID);

/*****************************************************************************
     : AT_AppPdpAddrProc
   : IPv4
   : pstAppPdpEntity - PDP
             pstDhcpConfig   - DCHP
             pstEvent        - 
   : 
     : VOS_VOID
   :
   :
*****************************************************************************/
VOS_VOID AT_AppPdpAddrProc(
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity,
    AT_DHCP_CONFIG_STRU                *pstDhcpConfig,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
);

/*****************************************************************************
     : AT_AppCheckPdpIdleState
   : IDLEDEACTIVATINGPDP
   : VOS_VOID
   : 
     : VOS_TRUE  - PDP
             VOS_FALSE - PDP
   :
   :
*****************************************************************************/
VOS_UINT32 AT_AppCheckPdpIdleState(VOS_VOID);

/*****************************************************************************
     : AT_AppCheckIpv4PdpState
   : IPv4PDP
   : enPdpState - PDP
   : 
     : VOS_TRUE   - PDP
             VOS_FALSE  - PDP
   :
   :
*****************************************************************************/
VOS_UINT32 AT_AppCheckIpv4PdpState(
    AT_PDP_STATE_ENUM_U8                enPdpState
);


#if (FEATURE_ON == FEATURE_IPV6)
/*****************************************************************************
     : AT_AppCheckIpv6PdpState
   : IPv6PDP
   : enPdpState - PDP
   : 
     : VOS_TRUE   - PDP
             VOS_FALSE  - PDP
   :
   :
*****************************************************************************/
VOS_UINT32 AT_AppCheckIpv6PdpState(
    AT_PDP_STATE_ENUM_U8                enPdpState
);
#endif


/*****************************************************************************
     : AT_AppGetPdpState
   : APPPDP/
   : ucPdpType - PDP
   : 
     : AT_PDP_STATE_ENUM_U8
   :
   :
*****************************************************************************/
AT_PDP_STATE_ENUM_U8 AT_AppGetPdpState(
    VOS_UINT8                           ucPdpType
);


/*****************************************************************************
     : AT_AppSetPdpState
   : APPPDP
   : ucPdpType  - PDP
             enPdpState - PDP
   : 
     : VOS_VOID
   :
   :
*****************************************************************************/
VOS_VOID AT_AppSetPdpState(
    VOS_UINT8                           ucPdpType,
    AT_PDP_STATE_ENUM_U8                enPdpState
);


/*****************************************************************************
     : AT_AppSndCallConnectedResult
   : ^DCONN, APP
   : ucCid                      - CID
             enPdpType                  - (IPv4/IPv6)
   : 
     : VOS_VOID
   :
   :
*****************************************************************************/
VOS_VOID AT_AppSndCallConnectedResult(
    VOS_UINT8                           ucCid,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
);


/*****************************************************************************
     : AT_AppSndCallEndedResult
   : ^DCONN, APP
   : ucCid     - CID
             enCause   - 
             enPdpType - (IPv4/IPv6)
   : 
     : VOS_VOID
   :
   :
*****************************************************************************/
VOS_VOID AT_AppSndCallEndedResult(
    VOS_UINT8                           ucCid,
    TAF_PS_CAUSE_ENUM_UINT32            enCause,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
);


/*****************************************************************************
     : AT_AppPdpActOrig
   : PDP
   : usClientId - ID
             ucCid      - CID
             ucPdpType  - PDP
   : 
     : VOS_VOID
   :
   :
*****************************************************************************/
VOS_VOID AT_AppPdpActOrig(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCid,
    TAF_PDP_TYPE_ENUM_UINT8             ucPdpType
);


#if (FEATURE_ON == FEATURE_IPV6)
/*****************************************************************************
     : AT_AppActCnfBackProc
   : PDP
   : pstEvent   - 
   : 
     : VOS_VOID
   :
   :
*****************************************************************************/
VOS_VOID AT_AppActCnfBackProc(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU        *pstEvent
);
#endif


/*****************************************************************************
     : AT_AppIpv4ActCnfProc
   : IPV4PDP
   : pstAppPdpEntity - PDP
             pstEvent        - 
   : 
     : VOS_VOID
   :
   :
*****************************************************************************/
VOS_VOID AT_AppIpv4PdpActCnfProc(
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
);


#if (FEATURE_ON == FEATURE_IPV6)
/*****************************************************************************
     : AT_AppIpv6ActCnfProc
   : IPV6PDP
   : pstAppPdpEntity - PDP
             pstEvent        - 
   : 
     : VOS_VOID
   :
   :
*****************************************************************************/
VOS_VOID AT_AppIpv6PdpActCnfProc(
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
);


/*****************************************************************************
     : AT_AppIpv4v6ActCnfProc
   : IPv4v6PDP
   : pstAppPdpEntity - PDP
             pstEvent        - 
   : 
     : VOS_VOID
   :
   :
*****************************************************************************/
VOS_VOID AT_AppIpv4v6PdpActCnfProc(
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
);
#endif

/*****************************************************************************
     : AT_AppIpv4DeactCnfProc
   : IPv4PDP
   : pstAppPdpEntity - PDP
             pstEvent        - 
   : 
     : VOS_VOID
   :
   :
*****************************************************************************/
VOS_VOID AT_AppIpv4PdpDeactivatedProc(
    AT_PDP_ENTITY_STRU                  *pstAppPdpEntity,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
);


#if (FEATURE_ON == FEATURE_IPV6)
/*****************************************************************************
     : AT_AppIpv6DeactCnfProc
   : IPv4PDP
   : pstAppPdpEntity - PDP
             pstEvent        - 
   : 
     : VOS_VOID
   :
   :
*****************************************************************************/
VOS_VOID AT_AppIpv6PdpDeactivatedProc(
    AT_PDP_ENTITY_STRU                  *pstAppPdpEntity,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
);


/*****************************************************************************
     : AT_AppIpv4v6DeactCnfProc
   : IPv4v6PDP
   : pstAppPdpEntity - PDP
             pstEvent        - 
   : 
     : VOS_VOID
   :
   :
*****************************************************************************/
VOS_VOID AT_AppIpv4v6PdpDeactivatedProc(
    AT_PDP_ENTITY_STRU                  *pstAppPdpEntity,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
);
#endif


/*****************************************************************************
     : AT_AppIpv4v6PdpActRejProc
   : IPv4PDP
   : pstAppPdpEntity - PDP
             pstEvent        - 
   : 
     : VOS_VOID
   :
   :
*****************************************************************************/
VOS_VOID AT_AppIpv4PdpActRejProc(
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity,
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU  *pstEvent
);


#if (FEATURE_ON == FEATURE_IPV6)
/*****************************************************************************
     : AT_AppIpv6PdpActRejProc
   : IPv6PDP
   : pstAppPdpEntity - PDP
             pstEvent        - 
   : 
     : VOS_VOID
   :
   :
*****************************************************************************/
VOS_VOID AT_AppIpv6PdpActRejProc(
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity,
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU  *pstEvent
);


/*****************************************************************************
     : AT_AppIpv4v6PdpActRejProc
   : IPv4PDP
   : pstAppPdpEntity - PDP
             pstEvent        - 
   : 
     : VOS_VOID
   :
   :
*****************************************************************************/
VOS_VOID AT_AppIpv4v6PdpActRejProc(
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity,
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU  *pstEvent
);
#endif


/*****************************************************************************
     : AT_AppPsRspPdpActEvtCnfProc
   : PDPAPP
   : ucIndex  - 
             pstEvent - 
   : 
     : VOS_VOID
   :
   :
*****************************************************************************/
VOS_VOID AT_AppPsRspEvtPdpActCnfProc(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
);


/*****************************************************************************
     : AT_AppPsRspPdpActEvtRejProc
   : PDPAPP
   : ucIndex  - 
             pstEvent - 
   : 
     : VOS_VOID
   :
   :
*****************************************************************************/
VOS_VOID AT_AppPsRspEvtPdpActRejProc(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU  *pstEvent
);


/*****************************************************************************
     : AT_AppPsRspPdpDeactEvtCnfProc
   : PDPAPP
   : ucIndex  - 
             pstEvent - 
   : 
     : VOS_VOID
   :
   :
*****************************************************************************/
VOS_VOID AT_AppPsRspEvtPdpDeactCnfProc(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
);


/*****************************************************************************
     : AT_AppPsRspPdpDeactivatedEvtProc
   : PDP, APP
   : ucIndex  - 
             pstEvent - 
   : 
     : VOS_VOID
   :
   :
*****************************************************************************/
VOS_VOID AT_AppPsRspEvtPdpDeactivatedProc(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_DEACTIVATE_IND_STRU *pstEvent
);


/*****************************************************************************
     : AT_AppSetFlowCtrl
   : 
   : ulParam1   - 
             ulParam2   - 
   : 
     : VOS_OK     - 
             VOS_ERR    - 
   :
   :
*****************************************************************************/
VOS_UINT32 AT_AppSetFlowCtrl(
    VOS_UINT32                          ulParam1,
    VOS_UINT32                          ulParam2
);


/*****************************************************************************
     : AT_AppClearFlowCtrl
   : 
   : ulParam1   - 
             ulParam2   - 
   : 
     : VOS_OK     - 
             VOS_ERR    - 
   :
   :
*****************************************************************************/
VOS_UINT32 AT_AppClearFlowCtrl(
    VOS_UINT32                          ulParam1,
    VOS_UINT32                          ulParam2
);


/*****************************************************************************
     : AT_AppRegFCPoint
   : 
   : FC_ID_ENUM_UINT8                    enFcId
             TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
   : 
     : VOS_UINT32
   :
   :
*****************************************************************************/
VOS_UINT32 AT_AppRegFCPoint(
    FC_ID_ENUM_UINT8                    enFcId,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent,
    VOS_UINT8                           ucRmNetId
);


/*****************************************************************************
     : AT_AppDeRegFCPoint
   : 
   : FC_ID_ENUM_UINT8                      enFcId,
             TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU  *pstEvent
   : 
     : VOS_OK     - 
             VOS_ERR    - 
   :
   :
*****************************************************************************/
VOS_UINT32 AT_AppDeRegFCPoint(
    FC_ID_ENUM_UINT8                     enFcId,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
);


/*****************************************************************************
     : AT_APP_ParseUsrInfo
   : APP
   : ucIndex     - (ClientId)
   : pstUserInfo - 
   : 
     : VOS_VOID
*****************************************************************************/
VOS_VOID AT_APP_ParseUsrInfo(
    VOS_UINT8                           ucIndex,
    AT_PS_USER_INFO_STRU               *pstUsrInfo
);

/* Deleted by Y00213812 for VoLTE_PhaseI , 2013-07-08, begin */
/* Deleted by Y00213812 for VoLTE_PhaseI , 2013-07-08, end */

/*****************************************************************************
     : AT_ModemPsRspPdpActEvtRejProc
   : pdpAP MODEM
   : ucIndex --- 
             pEvent  --- 
   : 
     : 
   :
   :

       :
  1.       : 201155
           : S62952
       : 

*****************************************************************************/
VOS_VOID  AT_ModemPsRspPdpActEvtRejProc(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU  *pEvent
);


/*****************************************************************************
     : AT_ModemPsRspPdpActEvtCnfProc
   : pdpModem
   : ucIndex --- 
             pEvent  --- 
   : 
     : 
   :
   :

       :
  1.       : 201155
           : S62952
       : 

*****************************************************************************/
VOS_VOID  AT_ModemPsRspPdpActEvtCnfProc(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pEvent
);

/*****************************************************************************
     : AT_ModemPsRspPdpDeactEvtCnfProc
   : pdpModem
   : ucIndex --- 
             pEvent  --- 
   : 
     : 
   :
   :

       :
  1.       : 201155
           : S62952
       : 

*****************************************************************************/
VOS_VOID  AT_ModemPsRspPdpDeactEvtCnfProc(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pEvent
);

/*****************************************************************************
     : AT_MODEM_ProcCallEndedEvent
   : PS_CALL_END_CNF
   : ucIndex  - 
             pstEvent - ID_EVT_TAF_PS_CALL_END_CNF
   : 
     : VOS_VOID
*****************************************************************************/
VOS_VOID AT_MODEM_ProcCallEndCnfEvent(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_END_CNF_STRU           *pstEvent
);


/*****************************************************************************
     : AT_MODEM_HangupCall
   : PPP
   : ucIndex - 
   : 
     : AT_XXX  - ATC
*****************************************************************************/
VOS_UINT32 AT_MODEM_HangupCall(VOS_UINT8 ucIndex);


VOS_VOID  AT_AnswerPdpActInd(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
);

/*****************************************************************************
     : AT_ModemPsRspPdpDeactivatedEvtProc
   : pdpModem
   : ucIndex --- 
             pEvent  --- 
   : 
     : 
   :
   :

       :
  1.       : 201155
           : S62952
       : 

*****************************************************************************/
VOS_VOID  AT_ModemPsRspPdpDeactivatedEvtProc(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_DEACTIVATE_IND_STRU *pEvent
);





/*****************************************************************************
     : AT_GetLCStartTime
   : 
   : 
   : 
     :  
   :
   :
*****************************************************************************/
extern VOS_UINT32 AT_GetLCStartTime(VOS_VOID);

/*****************************************************************************
    : AT_SendRnicPdpDeactInd
  : APP
  : VOS_UINT8 ucRabId
  : 
    : 
            
  :
  :
*****************************************************************************/
extern VOS_UINT32 AT_SendRnicPdpDeactInd(
    VOS_UINT8                           ucRabId,
    VOS_UINT8                           ucRmNetId
);

/*****************************************************************************
     : AT_DeRegModemPsDataFCPoint
   : Modem
   : MN_CLIENT_ID_T                      usClientID,
             VOS_UINT8                           ucRabId
   : 
     : VOS_UINT32
   :
   :
*****************************************************************************/
extern VOS_UINT32 AT_DeRegModemPsDataFCPoint(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                           ucRabId
);

/*****************************************************************************
     : AT_RegModemPsDataFCPoint
   : Modem
   : TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU  *pstEvent
             FC_ID_ENUM_UINT8                      enFcId
   : 
     : VOS_UINT32
   :
   :
*****************************************************************************/
extern VOS_UINT32 AT_RegModemPsDataFCPoint(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent,
    FC_ID_ENUM_UINT8                    enFcId
);

#if( FEATURE_ON == FEATURE_CSD )
/*****************************************************************************
     : AT_RegModemVideoPhoneFCPoint
   : ModemCST
   : FC_ID_ENUM_UINT8                    enFcId
   : 
     : VOS_UINT32
   :
   :
*****************************************************************************/
VOS_UINT32 AT_RegModemVideoPhoneFCPoint(
    VOS_UINT8                           ucIndex,
    FC_ID_ENUM_UINT8                    enFcId
);

/*****************************************************************************
     : AT_DeRegModemVideoPhoneFCPoint
   : ModemCST
   :
   : 
     : VOS_UINT32
   :
   :
*****************************************************************************/
VOS_UINT32 AT_DeRegModemVideoPhoneFCPoint(VOS_UINT8 ucIndex);
#endif


/*****************************************************************************
     : AT_ProcNdisRegFCPoint
   : NDISPDP
   : TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent,
             TAF_PDP_TYPE_ENUM_UINT8             enPdpType
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20130708
           : Y00213812
       : VoLTE_PhaseI 

*****************************************************************************/
VOS_VOID  AT_ProcNdisRegFCPoint(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
);

/*****************************************************************************
     : AT_ProcNdisDeRegFCPoint
   : NDISPDP
   : TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent,
             TAF_PDP_TYPE_ENUM_UINT8             enPdpType
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20130708
           : Y00213812
       : VoLTE_PhaseI 

*****************************************************************************/
VOS_VOID  AT_ProcNdisDeRegFCPoint(
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
);

/*****************************************************************************
     : AT_RegNdisFCPoint
   : NDIS
   : TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
   : 
     : VOS_UINT32
   :
   :
*****************************************************************************/
extern VOS_UINT32 AT_RegNdisFCPoint(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent,
    FC_ID_ENUM_UINT8                    enFcId,
    MODEM_ID_ENUM_UINT16                enModemId
);

/*****************************************************************************
     : AT_DeRegNdisFCPoint
   : NDIS
   : VOS_UINT8                           ucRabId
   : 
     : VOS_UINT32
   :
   :
*****************************************************************************/
extern VOS_UINT32 AT_DeRegNdisFCPoint(
    VOS_UINT8                           ucRabId,
    MODEM_ID_ENUM_UINT16                enModemId
);

/*****************************************************************************
     : AT_NdisPdpActOrig
   : PDP
   :  VOS_UINT16                  usClientId
              VOS_UINT8                   ucCid
              TAF_PDP_TYPE_ENUM_UINT8     ucPdpType
   : 
     :
   :
   :
*****************************************************************************/
extern VOS_VOID AT_NdisPdpActOrig(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCid,
    TAF_PDP_TYPE_ENUM_UINT8             ucPdpType
);

#if (FEATURE_ON == FEATURE_IPV6)
/*****************************************************************************
     : AT_NdisActCnfBackProc
   : PDP
   : 
   : 
     :
   :
   :
*****************************************************************************/
extern VOS_VOID  AT_NdisActCnfBackProc(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU   *pstEvent
);

/*****************************************************************************
     : AT_SendNdisIPv6PdnInfoCfgReq
   : IPV6PDN
   : TAF_PS_IPV6_INFO_IND_STRU* pRaInfo
   : 
     : AT_APS_IPV6_RA_INFO_STRU* pIPv6RaInfo
   :
   :
*****************************************************************************/
extern VOS_UINT32 AT_SendNdisIPv6PdnInfoCfgReq(
           MODEM_ID_ENUM_UINT16                 enModemId,
           TAF_PS_IPV6_INFO_IND_STRU* pIPv6RaNotify);

/*****************************************************************************
     : AT_NdisIpv4ActCnfProc
   : IPV4PDP
   : pEvent  --- 
   : 
     :
   :
   :
*****************************************************************************/
extern VOS_VOID AT_NdisIpv4ActCnfProc(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU        *pstEvent
);

/*****************************************************************************
     : AT_NdisIpv6ActCnfProc
   : IPV6PDP
   : pEvent  --- 
   : 
     :
   :
   :
*****************************************************************************/
extern VOS_VOID AT_NdisIpv6ActCnfProc(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU        *pstEvent
);

/*****************************************************************************
     : AT_NdisIpv4v6ActCnfProc
   : IPV4v6PDP
   : pstEvent --- 
   : 
     :
   :
   :
*****************************************************************************/
extern VOS_VOID AT_NdisIpv4v6ActCnfProc(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU        *pstEvent
);
#endif


/*****************************************************************************
     : AT_GetFCPriFromQos
   : QosFC
   : TAF_UMTS_QOS_STRU                  *pstUmtsQos
   : 
     : FC_PRI_ENUM_UINT8
   :
   :
*****************************************************************************/
extern FC_PRI_ENUM_UINT8 AT_GetFCPriFromQos(
    TAF_UMTS_QOS_STRU                  *pstUmtsQos
);

/*****************************************************************************
     : AT_GetPsDialParamFromAtDialParam
   : 
   : TAF_PDP_PRIM_CONTEXT_EXT_STRU      *pstPdpPrimContextExt,
             AT_DIAL_PARAM_STRU                 *pstDialParam
   : 
     : VOS_VOID
   :
   :
*****************************************************************************/
extern VOS_VOID AT_GetPsDialParamFromAtDialParam(
    TAF_PS_DIAL_PARA_STRU              *pstPsDialParam,
    AT_DIAL_PARAM_STRU                 *pstDialParam
);

/*****************************************************************************
     : AT_GetPdpContextFromAtDialParam
   : pdp
   : TAF_PDP_PRIM_CONTEXT_EXT_STRU      *pstPdpPrimContextExt,
             AT_DIAL_PARAM_STRU                 *pstDialParam
   : 
     : VOS_VOID
   :
   :s
*****************************************************************************/
extern VOS_VOID AT_GetPdpContextFromAtDialParam(
    TAF_PDP_PRIM_CONTEXT_EXT_STRU      *pstPdpPrimContextExt,
    AT_DIAL_PARAM_STRU                 *pstDialParam
);

/*****************************************************************************
     : AT_GetFcPriFromMap
   : FC IDFC PRI
   : FC_ID_ENUM_UINT8                   enFcId,
             AT_FCID_MAP_STRU                  *pstFcIdMap
   : 
     : VOS_UINT32
   :
   :
*****************************************************************************/
extern VOS_UINT32 AT_GetFcPriFromMap(
    FC_ID_ENUM_UINT8                   enFcId,
    AT_FCID_MAP_STRU                  *pstFcIdMap
);


/*****************************************************************************
     : AT_NotifyFcWhenPdpModify
   : PDP MODIFY(UE)FC
   : pstEvt       TAF_PS_CALL_EVENT_INFO_STRU
             enFcId        ID
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 2012218
           : L47619
       : 
*****************************************************************************/
VOS_VOID AT_NotifyFcWhenPdpModify(
    TAF_PS_CALL_PDP_MODIFY_CNF_STRU    *pstEvent,
    FC_ID_ENUM_UINT8                    enFcId
);


#if (FEATURE_ON == FEATURE_IPV6)
/*****************************************************************************
     : AT_SaveIPv6Dns
   : IPV6DNSPDP
   : TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent,
             AT_PDP_ENTITY_STRU                 *pstPdpEntity
   : 
     : VOS_VOID
   :
   :
*****************************************************************************/
extern VOS_VOID  AT_SaveIPv6Dns(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent,
    AT_PDP_ENTITY_STRU                 *pstPdpEntity
);

/*****************************************************************************
     : AT_SaveIPv6Pcscf
   : IPV6PcscfPDP
   : TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU        *pstEvent,
             AT_PDP_ENTITY_STRU                 *pstPdpEntity
   : 
     : VOS_VOID
   :
   :
*****************************************************************************/
VOS_VOID  AT_SaveIPv6Pcscf(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent,
    AT_PDP_ENTITY_STRU                 *pstPdpEntity
);
#endif


/*****************************************************************************
     : AT_UsbEthHostAccumTuneCB
   : FC()HOSTNCM/ECM
   : pstFcDrvAssemPara - NCM/ECM, :
                                 1. HOST OUT
   : 
     : VOS_OK            - 
             VOS_ERR           - 
   :
   :
*****************************************************************************/
VOS_UINT32 AT_UsbEthHostAccumTuneCB(
    FC_DRV_ASSEM_PARA_STRU             *pstFcDrvAssemPara
);


/*****************************************************************************
     : AT_UsbEthDeviceAccumTuneCB
   : FC()DEVICENCM/ECM
   : pstFcDrvAssemPara - NCM/ECM, :
                                 1. TX
                                 2. TX
                                 3. RX
                                 4. RX
   : 
     : VOS_OK            - 
             VOS_ERR           - 
   :
   :
*****************************************************************************/
VOS_UINT32 AT_UsbEthDeviceAccumTuneCB(
    FC_DRV_ASSEM_PARA_STRU             *pstFcDrvAssemPara
);


/*****************************************************************************
     : AT_ChangeFCPoint
   : 
   : TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU   *pstEvent,
             FC_PRI_ENUM_UINT8                    enFCPri,
             FC_ID_ENUM_UINT8                     enFcId
   : 
     : VOS_UINT32
   :
   :
*****************************************************************************/
extern VOS_UINT32 AT_ChangeFCPoint(
    TAF_CTRL_STRU                       *pstCtrl,
    FC_PRI_ENUM_UINT8                    enFCPri,
    FC_ID_ENUM_UINT8                     enFcId
);

extern VOS_UINT32 AT_EnableHsicFlowCtl(
    VOS_UINT32                          ulUdiHdl,
    VOS_UINT32                          ulParam2
);
extern VOS_UINT32 AT_DisableHsicFlowCtl(
    VOS_UINT32                          ulUdiHdl,
    VOS_UINT32                          ulParam2
);
extern VOS_UINT32 AT_RegHsicFCPoint(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU        *pstEvent
);
extern VOS_UINT32 AT_DeRegHsicFCPoint(
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU        *pstEvent
);
extern VOS_VOID  AT_HsicPsRspEvtPdpActCnfProc(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU        *pstEvent
);
extern VOS_VOID  AT_HsicPsRspEvtPdpDeactCnfProc(
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU        *pstEvent
);
extern VOS_VOID  AT_HsicPsRspEvtPdpDeactivatedProc(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_DEACTIVATE_IND_STRU *pstEvent
);
/* Modified by l60609 for AP 2012-09-10 Begin */
extern VOS_VOID  AT_ProcAppPsRspEvtPdpActCnf(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
);
extern VOS_VOID  AT_ProcAppPsRspEvtPdpDeActCnf(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
);
/* Modified by l60609 for AP 2012-09-10 End */
extern VOS_VOID AT_ProcAppPsRspEvtPdpDeactivated(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_DEACTIVATE_IND_STRU *pstEvent
);
extern VOS_VOID AT_NotifyFcWhenAppPdpModify(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_MODIFY_CNF_STRU    *pstEvent
);

/*DTS2012041102190 : h00135900 start in 2011-04-11 AT*/
#if (FEATURE_ON == FEATURE_LTE)
/* ATFTM  */
extern VOS_UINT32 atSendFtmDataMsg(VOS_UINT32 TaskId, VOS_UINT32 MsgId, VOS_UINT32 ulClientId, VOS_VOID* pData, VOS_UINT32 uLen);
#endif
/*DTS2012041102190 : h00135900 end in 2011-04-11 AT*/

extern VOS_UINT32 AT_SendRnicCgactIpv4ActInd(
    VOS_UINT8                           ucRabId,
    VOS_UINT8                           ucRmNetId
);

/*****************************************************************************
     : AT_PS_AddIpAddrRabIdMap
   : IPRABID
   : usClientId - ID
             pstEvent   - PS
   : 
     : VOS_VOID
*****************************************************************************/
VOS_VOID AT_PS_AddIpAddrRabIdMap(
    VOS_UINT16                          usClientId,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
);


/*****************************************************************************
     : AT_PS_DeleteIpAddrRabIdMap
   : IPRABID
   : usClientId - ID
             pstEvent   - PS
   : 
     : VOS_VOID
*****************************************************************************/
VOS_VOID AT_PS_DeleteIpAddrRabIdMap(
    VOS_UINT16                          usClientId,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
);


/*****************************************************************************
     : AT_PS_GetIpAddrByRabId
   : RABIDIP
   : usClientId - ID
             ucRabId    - RABID [5,15]
   : 
     : ulIpAddr   - IP()
*****************************************************************************/
VOS_UINT32 AT_PS_GetIpAddrByRabId(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucRabId
);


extern VOS_UINT32 AT_PS_GetRmNetIdByCid(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCid,
    VOS_UINT8                          *pucRmNetId
);
/* Modified by l60609 for DSDA Phase III, 2013-2-25, Begin */
extern VOS_VOID AT_PS_SetPsCallErrCause(
    VOS_UINT16                          usClientId,
    TAF_PS_CAUSE_ENUM_UINT32            enPsErrCause
);
extern TAF_PS_CAUSE_ENUM_UINT32 AT_PS_GetPsCallErrCause(
    VOS_UINT16                          usClientId
);
/* Modified by l60609 for DSDA Phase III, 2013-2-25, End */

extern VOS_UINT32 AT_ResetFlowCtl(
    VOS_UINT32                          ulParam1,
    VOS_UINT32                          ulParam2
);
/* Added by l60609 for V9R1 IPv6&TAF/SM Project, 2013-4-24, begin */
VOS_UINT32 AT_PS_GetRnicRmNetIdFromChDataValue(
    VOS_UINT8                           ucIndex,
    AT_CH_DATA_CHANNEL_ENUM_UINT32      enDataChannelId,
    RNIC_RMNET_ID_ENUM_UINT8           *penRnicRmNetId
);

VOS_UINT32 AT_PS_GetChDataValueFromRnicRmNetId(
    RNIC_RMNET_ID_ENUM_UINT8            enRnicRmNetId,
    AT_CH_DATA_CHANNEL_ENUM_UINT32     *penDataChannelId
);

AT_PS_CALL_ENTITY_STRU* AT_PS_GetCallEntity(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId
);

VOS_UINT8 AT_PS_TransCidToCallId(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCid
);

VOS_UINT32 AT_PS_IsCallIdValid(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId
);

VOS_VOID AT_PS_ReportDCONN(
    VOS_UINT8                           ucCid,
    VOS_UINT8                           ucPortIndex,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
);

VOS_VOID AT_PS_ReportDEND(
    VOS_UINT8                           ucCid,
    VOS_UINT8                           ucPortIndex,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType,
    TAF_PS_CAUSE_ENUM_UINT32            enCause
);

VOS_VOID AT_PS_RegHsicFCPoint(
    VOS_UINT8                           ucCid,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
);

VOS_VOID AT_PS_DeRegHsicFCPoint(
    VOS_UINT8                           ucCid,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
);

VOS_VOID AT_PS_RegAppFCPoint(
    VOS_UINT8                           ucCid,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
);

VOS_VOID AT_PS_DeRegAppFCPoint(
    VOS_UINT8                           ucCid,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
);

VOS_VOID  AT_PS_SndDipcPdpActInd(
    VOS_UINT8                           ucCid,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
);

VOS_VOID  AT_PS_SndDipcPdpDeactInd(
    VOS_UINT8                           ucCid,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
);

VOS_VOID  AT_PS_SndRnicPdpActInd(
    VOS_UINT8                           ucCid,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
);

VOS_VOID AT_PS_SndRnicPdpDeactInd(
    VOS_UINT8                           ucCid,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
);

#if (FEATURE_ON == FEATURE_IPV6)
VOS_UINT32 AT_PS_IsIpv6CapabilityValid(VOS_UINT8 ucCapability);

VOS_UINT32 AT_CheckIpv6Capability(
    VOS_UINT8                           ucPdpType
);

VOS_UINT32 AT_PS_GenIpv6LanAddrWithRadomIID(
    VOS_UINT8                          *pucPrefix,
    VOS_UINT32                          ulPrefixByteLen,
    VOS_UINT8                          *pucIpv6LanAddr
);


VOS_VOID  AT_PS_SaveIPv6Dns(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
);

VOS_VOID  AT_PS_SaveIPv6Pcscf(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
);

VOS_VOID AT_PS_ProcConnectedIpv6Addr(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
);

VOS_VOID AT_PS_ProcIpv6RaInfo(TAF_PS_IPV6_INFO_IND_STRU *pstRaInfoNotifyInd);


VOS_UINT32 AT_PS_MatchIpv4v6ConnFailFallbackCause(
    TAF_PS_CAUSE_ENUM_UINT32            enCause
);


VOS_UINT32 AT_PS_SetupSingleStackConn(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
);


VOS_UINT32 AT_PS_HangupSingleStackConn(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
);


VOS_VOID AT_PS_ProcDualStackCallConn(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
);

VOS_VOID AT_PS_ProcIpv4ConnSuccFallback(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU   *pstEvent
);


VOS_VOID AT_PS_ProcIpv6ConnSuccFallback(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
);


VOS_UINT32 AT_PS_ProcIpv4ConnFailFallback(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU  *pstEvent
);


VOS_UINT32 AT_PS_ProcIpv4v6ConnFailFallback(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU  *pstEvent
);
#endif

VOS_VOID AT_PS_ProcIpv4CallConnected(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
);

VOS_VOID AT_PS_ProcIpv4CallReject(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU  *pstEvent
);

VOS_VOID AT_PS_ProcIpv4CallEnded(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
);

#if (FEATURE_ON == FEATURE_IPV6)

VOS_VOID AT_PS_ProcIpv6CallConnected(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
);


VOS_VOID AT_PS_ProcIpv4v6CallConnected(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
);


VOS_VOID AT_PS_ProcIpv6CallReject(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU  *pstEvent
);

VOS_VOID AT_PS_ProcIpv4v6CallReject(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU  *pstEvent
);

VOS_VOID AT_PS_ProcIpv6CallEnded(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
);

VOS_VOID AT_PS_ProcIpv4v6CallEnded(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
);

VOS_UINT8 AT_CalcIpv6PrefixLength(
    VOS_UINT8                           *pucLocalIpv6Mask
);

VOS_VOID AT_GetIpv6MaskByPrefixLength(
    VOS_UINT8                            ucLocalIpv6Prefix,
    VOS_UINT8                           *pucLocalIpv6Mask
);

#endif

VOS_VOID AT_PS_ProcCallConnectedEvent(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
);

VOS_VOID AT_PS_ProcCallRejectEvent(
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU   *pstEvent
);

VOS_VOID AT_PS_ProcCallEndedEvent(
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
);

VOS_VOID AT_PS_ProcCallOrigCnfEvent(TAF_PS_CALL_ORIG_CNF_STRU *pstCallOrigCnf);

VOS_VOID AT_PS_ProcCallEndCnfEvent(TAF_PS_CALL_END_CNF_STRU *pstCallEndCnf);

VOS_UINT32 AT_PS_ProcCallModifyEvent(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_MODIFY_CNF_STRU    *pstEvent
);

VOS_UINT32 AT_PS_AllocCallEntity(
    VOS_UINT16                          usClientId,
    VOS_UINT8                          *pucCallId
);

VOS_VOID AT_PS_FreeCallEntity(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId
);

VOS_UINT32 AT_PS_ValidateDialParam(VOS_UINT8 ucIndex);

VOS_VOID AT_PS_ParseUsrInfo(
    VOS_UINT8                           ucIndex,
    AT_PS_USER_INFO_STRU               *pstUserInfo
);

TAF_PDP_TYPE_ENUM_UINT8 AT_PS_GetCurrCallType(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId
);

VOS_UINT32 AT_PS_SetupCall(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId,
    AT_DIAL_PARAM_STRU                 *pstCallDialParam
);

VOS_UINT32 AT_PS_HangupCall(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_END_CAUSE_ENUM_UINT8    enCause
);

TAF_PS_CALL_END_CAUSE_ENUM_UINT8 AT_PS_TransCallEndCause(
    VOS_UINT8                           ucConnectType
);

VOS_UINT32 AT_PS_ProcDialUp(VOS_UINT8 ucIndex);

VOS_UINT32 AT_PS_ProcDialDown(VOS_UINT8 ucIndex);

VOS_UINT32 AT_PS_ProcDialCmd(VOS_UINT8 ucIndex);


extern VOS_UINT32 AT_CheckApnFormat(
    VOS_UINT8                          *pucApn,
    VOS_UINT16                          usApnLen
);


VOS_VOID AT_PS_AssignCallIdToCid(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCid,
    VOS_UINT8                           ucCallId
);

VOS_VOID AT_PS_FreeCallIdToCid(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCid
);

/* Added by l60609 for V9R1 IPv6&TAF/SM Project, 2013-4-24, end */

/*****************************************************************************
     : AT_PS_ProcDeactSharePdpState
   : PDPShare PDP
   : TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent,
             TAF_PDP_TYPE_ENUM_UINT8             enPdpType
   : 
     : VOS_VOID
*****************************************************************************/
VOS_VOID  AT_PS_ProcDeactSharePdpState(
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
);

/*****************************************************************************
     : AT_PS_ProcActSharePdpState
   : PDPShare PDP
   : TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent,
             TAF_PDP_TYPE_ENUM_UINT8             enPdpType
   : 
     : VOS_VOID
*****************************************************************************/
VOS_VOID  AT_PS_ProcActSharePdpState(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU   *pstEvent,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
);

#if (FEATURE_ON == FEATURE_IPV6)
/*****************************************************************************
     : AT_PS_ProcSharePdpIpv6RaInfo
   : Share-PDPRouter Advertisement IP, PDN
   : pstRaInfoNotifyInd         - RA
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 201366
           : L47619
       : V3R3 Share-PDP

*****************************************************************************/
VOS_VOID AT_PS_ProcSharePdpIpv6RaInfo(
    TAF_PS_IPV6_INFO_IND_STRU *pstRaInfoNotifyInd
);
#endif

/******************************************************************************
     : AT_PS_SaveRnicPdpDhcpPara
   : NDIS PDPDHCPAPP PDP
   : TAF_PDP_TYPE_ENUM_UINT8              ucPdpType,
              TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
   : 
     : 
   :
   :

       :
  1.       : 201365
           : z00214637
       : 
******************************************************************************/
VOS_VOID AT_PS_SaveRnicPdpDhcpPara(
    TAF_PDP_TYPE_ENUM_UINT8             ucPdpType,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
);

/******************************************************************************
     : AT_PS_ResetRnicPdpDhcpPara
   : NDIS PDPAppPdpEntity
   : ucPdpType - PDP
   : 
     : 
   :
   :

       :
  1.       : 201365
           : z00214637
       : 
******************************************************************************/
VOS_VOID AT_PS_ResetRnicPdpDhcpPara(
    TAF_PDP_TYPE_ENUM_UINT8             ucPdpType
);

/*****************************************************************************
     : AT_PS_SendRnicPdnInfoCfgInd
   : RNICPDN
   : TAF_PDP_TYPE_ENUM_UINT8             ucPdpType,
             VOS_UINT8                           ucRabId,
             AT_PDP_ENTITY_STRU                 *pstAppPdpEntity
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 201364
           : z00214637
       : V3R3 Share-PDP
*****************************************************************************/
VOS_UINT32 AT_PS_SendRnicPdnInfoCfgInd(
    TAF_PDP_TYPE_ENUM_UINT8             ucPdpType,
    VOS_UINT8                           ucRabId,
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity
);

/*****************************************************************************
     : AT_PS_SendRnicPdnInfoRelInd
   : RNICPDN
   : AT_PDP_ENTITY_STRU                 *pstAppPdpEntity
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 201364
           : z00214637
       : V3R3 Share-PDP
*****************************************************************************/
VOS_UINT32 AT_PS_SendRnicPdnInfoRelInd(
    VOS_UINT8                           ucRabId
);

/*****************************************************************************
     : AT_PS_GetRptConnResultFunc
   : 
   : ucUsrType - 
   : 
     : AT_PS_RPT_CONN_RSLT_FUNC
*****************************************************************************/
AT_PS_RPT_CONN_RSLT_FUNC AT_PS_GetRptConnResultFunc(AT_USER_TYPE ucUsrType);

/*****************************************************************************
     : AT_PS_GetRptEndResultFunc
   : 
   : ucUsrType - 
   : 
     : AT_PS_RPT_END_RSLT_FUNC
*****************************************************************************/
AT_PS_RPT_END_RSLT_FUNC AT_PS_GetRptEndResultFunc(AT_USER_TYPE ucUsrType);


VOS_UINT32 AT_PS_SetQosPara(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucUserCid,
    VOS_UINT8                           ucActCid
);

/* Modified by s00217060 for ATC, 2013-4-17, begin */
VOS_UINT32 Taf_GetDisplayRate(
    VOS_UINT16                          usClientId,
    AT_DISPLAY_RATE_STRU               *stSpeed
);
/* Modified by s00217060 for ATC, 2013-4-17, end */

/* Added by m00217266 for L-C, 2014-1-26, begin */
/* Added by m00217266 for L-C, 2014-1-26, end */

/*****************************************************************************
     : AT_ProcAppRegFCPoint
   : APPPDP
   : TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent,
   : 
     : VOS_VOID

*****************************************************************************/
VOS_VOID  AT_ProcAppRegFCPoint(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
);

/*****************************************************************************
     : AT_SendRnicIpv4ActInd
   : APPIPV4
   : VOS_UINT8 ucRmNetId
   : 
     : VOS_UINT32

*****************************************************************************/
VOS_UINT32 AT_SendRnicIpv4ActInd(VOS_UINT8 ucRmNetId);


#if (FEATURE_ON == FEATURE_IPV6)
/*****************************************************************************
    : AT_SendRnicIpv6ActInd
  : APPIPV6
  : VOS_UINT8 ucRmNetId
  : 
    : 
            
*****************************************************************************/
VOS_UINT32 AT_SendRnicIpv6ActInd(VOS_UINT8 ucRmNetId);

/*****************************************************************************
    : AT_SendRnicIpv4v6ActInd
  : APPIPV4V6
  : VOS_UINT8 ucRmNetId
  : 
    : VOS_UINT32

*****************************************************************************/
VOS_UINT32 AT_SendRnicIpv4v6ActInd(VOS_UINT8 ucRmNetId);

#endif

/*****************************************************************************
     : AT_NdisIPv4DeactiveCnfProc
   : IPV4pdpNdis
   : pEvent  --- 
   : 
     : 

*****************************************************************************/
VOS_VOID AT_NdisIPv4DeactiveCnfProc(
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
);

/*****************************************************************************
     : AT_DeActiveUsbNet
   : USB
   : VOS_VOID
   : 
     : VOS_UINT32

*****************************************************************************/
VOS_UINT32 AT_DeActiveUsbNet(VOS_VOID);

/*****************************************************************************
     : AT_PS_GetDataChanlCfg
   : 
   : VOS_UINT16                          usClientId
             VOS_UINT8                           ucCid
   : 
     : AT_PS_DATA_CHANL_CFG_STRU*

*****************************************************************************/
AT_PS_DATA_CHANL_CFG_STRU* AT_PS_GetDataChanlCfg(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCid
);

/*****************************************************************************
     : AT_PS_RegFCPoint
   : 
   : ucCallId   - ID
             pstEvent   - 
   : 
     : VOS_VOID
*****************************************************************************/
VOS_VOID AT_PS_RegFCPoint(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
);

/*****************************************************************************
     : AT_PS_GetCidByCallType
   : CID
   : usClientId - ID
             ucCallId  - 
             enPdpType - PDP
   : 
     : VOS_UINT8 - CID

*****************************************************************************/
VOS_UINT8 AT_PS_GetCidByCallType(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
);

/*****************************************************************************
     : AT_PS_SetCallStateByType
   : PDP
   : usClientId - ID
             ucCallId   - 
             enPdpType  - PDP(IPv4, IPv6 or IPv4v6)
             enPdpState - PDP
   : 
*****************************************************************************/
VOS_VOID AT_PS_SetCallStateByType(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType,
    AT_PDP_STATE_ENUM_U8                enPdpState
);

/*****************************************************************************
     : AT_PS_SndCallConnectedResult
   : 
   : ucCallId  - 
             enPdpType - PDP
   : 
     : VOS_VOID
*****************************************************************************/
VOS_VOID AT_PS_SndCallConnectedResult(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
);

/*****************************************************************************
     : AT_PS_SndCallEndedResult
   : ^DEND
   : ucCallId  - 
             enPdpType - PDP
             enCause   - 
   : 
     : VOS_VOID
*****************************************************************************/
VOS_VOID AT_PS_SndCallEndedResult(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType,
    TAF_PS_CAUSE_ENUM_UINT32            enCause
);

/*****************************************************************************
     : AT_PS_IsLinkGoingUp
   : /
   : usClientId - ID
             ucCallId  - 
   : 
     : VOS_TRUE  - /
             VOS_FALSE - 
*****************************************************************************/
VOS_UINT32 AT_PS_IsLinkGoingUp(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId
);

/*****************************************************************************
     : AT_PS_IsLinkGoingDown
   : 
   : usClientId - ID
             ucCallId   - 
   : 
     : VOS_TRUE
             VOS_FALSE
*****************************************************************************/
VOS_UINT32 AT_PS_IsLinkGoingDown(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId
);

/*****************************************************************************
     : AT_PS_IsLinkDown
   : 
   : usClientId - ID
             ucCallId   - 
   : 
     : VOS_TRUE  - 
             VOS_FALSE - 
   :
   :

       :
  1.       : 20121217
           : A00165503
       : 
*****************************************************************************/
VOS_UINT32 AT_PS_IsLinkDown(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId
);

/*****************************************************************************
     : AT_PS_GetFcIdFromRnicByRmNetId
   : RNICFCID
   : VOS_UINT32                          ulRmNetId
   : 
     : FC_ID_ENUM_UINT8
*****************************************************************************/
FC_ID_ENUM_UINT8 AT_PS_GetFcIdFromRnicByRmNetId(
    VOS_UINT32                          ulRmNetId
);

/*****************************************************************************
     : AT_PS_GetFcIdByUdiDeviceId
   : DIPCIDFCID
   : UDI_DEVICE_ID                       enDataChannelId
   : 
     : FC_ID_ENUM_UINT8
*****************************************************************************/
FC_ID_ENUM_UINT8 AT_PS_GetFcIdByUdiDeviceId(
    UDI_DEVICE_ID_E                     enDataChannelId
);

/*****************************************************************************
     : AT_PS_ProcConflictDialUpWithCurrCall
   : 
   : ucIndex  - (ClientId)
             ucCallId - 
   : 
     : VOS_OK   - 
             VOS_ERR  - 
*****************************************************************************/
VOS_UINT32 AT_PS_ProcConflictDialUpWithCurrCall(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                           ucCallId
);

/*****************************************************************************
     : AT_PS_ReportCurrCallConnState
   : 
   : usClientId - ID
             ucCallId   - 
   : 
     : VOS_VOID
*****************************************************************************/
VOS_VOID AT_PS_ReportCurrCallConnState(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId
);


/*****************************************************************************
     : AT_PS_ReportCurrCallEndState
   : 
   : usClientId - ID
             ucCallId   - 
   : 
     : VOS_VOID
*****************************************************************************/
VOS_VOID AT_PS_ReportCurrCallEndState(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId
);

/*****************************************************************************
     : AT_PS_IsIpv6Support
   : IPV6
   : VOS_VOID
   : 
     : VOS_UINT32

*****************************************************************************/
VOS_UINT32 AT_PS_IsIpv6Support(VOS_VOID);

/*****************************************************************************
     : AT_PS_GetCallStateByCid
   : CID
   : usClientId - ID
             ucCallId   - 
             ucCid      - CID
   : 
     : AT_PDP_STATE_ENUM_U8
   :
*****************************************************************************/
AT_PDP_STATE_ENUM_U8 AT_PS_GetCallStateByCid(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId,
    VOS_UINT8                           ucCid
);

/*****************************************************************************
     : AT_PS_SndRnicIpv4PdpActInd
   : RNICPDP, IPv4
   : VOS_UINT8                           ucCid
             TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
   : 
     : VOS_VOID

*****************************************************************************/
VOS_VOID AT_PS_SndRnicIpv4PdpActInd(
    VOS_UINT8                           ucCid,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU *pstEvent
);

/*****************************************************************************
     : AT_PS_SndRnicIpv6PdpActInd
   : RNICPDP, IPv6
   : VOS_UINT8                           ucCid
             TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
   : 
     : VOS_VOID

*****************************************************************************/
VOS_VOID AT_PS_SndRnicIpv6PdpActInd(
    VOS_UINT8                           ucCid,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
);

/*****************************************************************************
     : AT_PS_SndDipcPdpDeactBearerTypeInd
   : ATDIPCPDP
   : TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent,
             DIPC_BEARER_TYPE_ENUM_UINT8         enBearerType
   : 
     : 
*****************************************************************************/
VOS_VOID  AT_PS_SndDipcPdpDeactBearerTypeInd(
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent,
    DIPC_BEARER_TYPE_ENUM_UINT8         enBearerType
);

/*****************************************************************************
     : AT_PS_SndDipcPdpActBearerTypeInd
   : ATDIPCPDP
   : ucCid          ----  CID
             pstEvent       ----  PsCallEventInfo
             enBearerType   ----  BearerType
   : 
     : 

*****************************************************************************/
VOS_VOID  AT_PS_SndDipcPdpActBearerTypeInd(
    VOS_UINT8                           ucCid,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent,
    DIPC_BEARER_TYPE_ENUM_UINT8         enBearerType
);

/******************************************************************************
     : AT_LenStr2IpAddr
   : IPSMIP.V100R001
   : pucStr - IP
   : pucIpAddr - SMIP
     : TAF_SUCCESS - 
             TAF_FAILURE - 
******************************************************************************/
VOS_UINT32  AT_LenStr2IpAddr(
    VOS_UINT8                           *pucStr,
    VOS_UINT8                           *pucIpAddr
);

/******************************************************************************
     : AT_DHCPServerSetUp
   : ptrDHCPParamDHCP ServerptrDHCPConfig
                DHCP Server()
                DHCP Server
   : pstEventPDP
   : AT_DHCP_SETUP_PARAM_ST *ptrDHCPCfg       DHCP
             AT_DHCP_CONFIG_STRU    *ptrDHCPConfig    DHCP
     : VOS_OK      
             VOS_ERR     
******************************************************************************/
VOS_UINT32  AT_DHCPServerSetUp(
    AT_DHCP_SETUP_PARAM_ST              *ptrDHCPParam,
    AT_DHCP_CONFIG_STRU                 *ptrDHCPConfig
);

/*****************************************************************************
     : AT_PS_ReportAllCallEndState
   : 
   : ucIndex - (ClientId)
   : 
     : VOS_VOID

*****************************************************************************/
VOS_VOID AT_PS_ReportAllCallEndState(VOS_UINT8 ucIndex);

/*****************************************************************************
     : AT_PS_SetCid2CurrCall
   : CID
   : usClientId - ID
             ucCallId  - 
             enPdpType - PDP
             ucCid     - CID
   : 
     : VOS_VOID

*****************************************************************************/
VOS_VOID AT_PS_SetCid2CurrCall(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType,
    VOS_UINT8                           ucCid
);

/*****************************************************************************
     : AT_PS_PdpAddrProc
   : IPv4
   : ucCallId      - 
             pstDhcpConfig - DCHP
             pstEvent      - 
   : 
     : VOS_VOID

*****************************************************************************/
VOS_VOID AT_PS_PdpAddrProc(
    VOS_UINT8                           ucCallId,
    AT_DHCP_CONFIG_STRU                *pstDhcpConfig,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
);


/*****************************************************************************
     : AT_AppSndRnicPdpActInd
   : APPPDPRNIC
   : enPdpType      PDP
   : 
     : VOS_VOID

*****************************************************************************/
VOS_VOID AT_AppSndRnicPdpActInd(
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
);

/*****************************************************************************
     : AT_PS_BuildExClientId
   : ClientId(ModemId + ClientId)
   : usClientId                 - ClientId
   : 
     : VOS_UINT16                 - ClientId
*****************************************************************************/
VOS_UINT16 AT_PS_BuildExClientId(VOS_UINT16 usClientId);

/*****************************************************************************
     : AT_PS_BuildNdisExClientId
   : ClientId(ModemId + ClientId)
   : usPortIndex                - 
             usClientId                 - ClientId
   : 
     : VOS_UINT16                 - ClientId
*****************************************************************************/
VOS_UINT16 AT_PS_BuildNdisExClientId(
    VOS_UINT16                          usPortIndex,
    VOS_UINT16                          usClientId
);

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

VOS_UINT32 AT_PS_CheckDialRatType(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                           ucBitRatType
);
#endif

VOS_VOID AT_PS_ProcRabidChangedEvent(
    TAF_PS_CALL_PDP_RABID_CHANGE_IND_STRU  *pstEvent
);


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

#endif


