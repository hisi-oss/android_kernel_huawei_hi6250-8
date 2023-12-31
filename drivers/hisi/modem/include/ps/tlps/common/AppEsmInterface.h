/******************************************************************************

  Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : AppEsmInterface.h
  Description     : AppEsmInterface.h header file
  History         :
      1.sunbing       2008-12-16   Draft Enact
      2.yangqianhui   2008-12-22   Modify
      3.sunbing       2009-01-06   Modify  BA8D00870
      4.yangqianhui   2009-02-05   Modify  BA8D00933
      5.yangqianhui   2009-03-06   Modify  BA8D01127

******************************************************************************/

#ifndef __APPESMINTERFACE_H__
#define __APPESMINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include "AppNasComm.h"

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 Macro
*****************************************************************************/

/*IP*/
#define APP_MAX_IPV4_ADDR_LEN                               4
#define APP_MAX_IPV6_ADDR_LEN                               16

#define APP_MAX_IPV6_PREFIX_LEN                             8

#define APP_ESM_MAX_IPV6_PREFIX_NUM     (6)
#define APP_ESM_IPV6_ADDR_LEN           (16)



#define APP_MAX_APN_LEN                                     99
#define APP_ESM_MAX_EPSB_NUM                                (11)                /**/
#define APP_ESM_MAX_ACCESS_NUM_LEN                          32
/* atAT^AUTHDATA127 */
#define APP_ESM_MAX_USER_NAME_LEN                           127
#define APP_ESM_MAX_PASSWORD_LEN                            127
/* PCO253127PCOGUAUTH99,GU99 */
#define APP_ESM_MAX_USER_NAME_ENCODE_LEN                    99
#define APP_ESM_MAX_PASSWORD_ENCODE_LEN                     99


#define APP_ESM_MAX_SDF_PF_NUM                              16


/*APP->SM Command3 APP->SM*/
#define APP_ESM_MSG_ID_HEADER                               PS_MSG_ID_APP_TO_ESM_BASE

/*SM->APP Command3 SM->APP*/
#define ESM_APP_MSG_ID_HEADER                               PS_MSG_ID_ESM_TO_APP_BASE

#define APP_ESM_PPP_CHAP_CHALLNGE_LEN       (16)
#define APP_ESM_PPP_CHAP_CHALLNGE_NAME_LEN  (16)
#define APP_ESM_PPP_CHAP_RESPONSE_LEN       (16)


#define APP_ESM_PPP_MAX_USERNAME_LEN    (99)
#define APP_ESM_PPP_MAX_PASSWORD_LEN    (99)

#define APP_ESM_TFT_MAX_PF_NUM                              16

/* niuxiufan DT begin */
#define APP_ESM_DT_REPORT_STATUS_OPEN                       1
#define APP_ESM_DT_REPORT_STATUS_CLOSE                      0
/* niuxiufan DT end */

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/
/*****************************************************************************
     : APP_ESM_MSG_TYPE_ENUM
   : APPSM
*****************************************************************************/
enum APP_ESM_MSG_TYPE_ENUM
{
    /**/
    ID_APP_ESM_SET_TFT_REQ              = 0x01+APP_ESM_MSG_ID_HEADER,/*_H2ASN_MsgChoice  APP_ESM_SET_TFT_REQ_STRU*/
    ID_APP_ESM_SET_TFT_CNF              = 0x02+ESM_APP_MSG_ID_HEADER,/*_H2ASN_MsgChoice  APP_ESM_SET_TFT_CNF_STRU*/

    ID_APP_ESM_SET_QOS_REQ              = 0x03+APP_ESM_MSG_ID_HEADER,/*_H2ASN_MsgChoice  APP_ESM_SET_QOS_REQ_STRU*/
    ID_APP_ESM_SET_QOS_CNF              = 0x04+ESM_APP_MSG_ID_HEADER,/*_H2ASN_MsgChoice  APP_ESM_SET_QOS_CNF_STRU*/

    ID_APP_ESM_SET_EPS_QOS_REQ          = 0x05+APP_ESM_MSG_ID_HEADER,/*_H2ASN_MsgChoice  APP_ESM_SET_EPS_QOS_REQ_STRU*/
    ID_APP_ESM_SET_EPS_QOS_CNF          = 0x06+ESM_APP_MSG_ID_HEADER,/*_H2ASN_MsgChoice  APP_ESM_SET_EPS_QOS_CNF_STRU*/

    ID_APP_ESM_SET_APN_REQ              = 0x07+APP_ESM_MSG_ID_HEADER,/*_H2ASN_MsgChoice  APP_ESM_SET_APN_REQ_STRU*/
    ID_APP_ESM_SET_APN_CNF              = 0x08+ESM_APP_MSG_ID_HEADER,/*_H2ASN_MsgChoice  APP_ESM_SET_APN_CNF_STRU*/

    ID_APP_ESM_SET_PCO_REQ              = 0x09+APP_ESM_MSG_ID_HEADER,/*_H2ASN_MsgChoice  APP_ESM_SET_PCO_REQ_STRU*/
    ID_APP_ESM_SET_PCO_CNF              = 0x0A+ESM_APP_MSG_ID_HEADER,/*_H2ASN_MsgChoice  APP_ESM_SET_PCO_CNF_STRU*/

    ID_APP_ESM_SET_PDN_TYPE_REQ         = 0x0B+APP_ESM_MSG_ID_HEADER,/*_H2ASN_MsgChoice  APP_ESM_SET_PDN_TYPE_REQ_STRU*/
    ID_APP_ESM_SET_PDN_TYPE_CNF         = 0x0C+ESM_APP_MSG_ID_HEADER,/*_H2ASN_MsgChoice  APP_ESM_SET_PDN_TYPE_CNF_STRU*/

    ID_APP_ESM_SET_BEARER_TYPE_REQ      = 0x0D+APP_ESM_MSG_ID_HEADER,/*_H2ASN_MsgChoice  APP_ESM_SET_BEARER_TYPE_REQ_STRU*/
    ID_APP_ESM_SET_BEARER_TYPE_CNF      = ESM_APP_MSG_ID_HEADER + 0x0E,/*_H2ASN_MsgChoice  APP_ESM_SET_BEARER_TYPE_CNF_STRU*/

    ID_APP_ESM_SET_PDP_MANAGER_TYPE_REQ = 0x0F+APP_ESM_MSG_ID_HEADER,/*_H2ASN_MsgChoice  APP_ESM_SET_PDP_MANAGER_TYPE_REQ_STRU*/
    ID_APP_ESM_SET_PDP_MANAGER_TYPE_CNF = 0x10+ESM_APP_MSG_ID_HEADER,/*_H2ASN_MsgChoice  APP_ESM_SET_PDP_MANAGER_TYPE_CNF_STRU*/

    ID_APP_ESM_SET_GW_AUTH_REQ          = 0x11+APP_ESM_MSG_ID_HEADER,/*_H2ASN_MsgChoice  APP_ESM_SET_GW_AUTH_REQ_STRU*/
    ID_APP_ESM_SET_GW_AUTH_CNF          = 0x11+ESM_APP_MSG_ID_HEADER,/*_H2ASN_MsgChoice  APP_ESM_SET_GW_AUTH_CNF_STRU*/
    /* niuxiufan modify begin */
    ID_APP_ESM_IPV6_INFO_NOTIFY         = 0x12+APP_ESM_MSG_ID_HEADER,/*_H2ASN_MsgChoice  APP_ESM_IPV6_INFO_NOTIFY_STRU*/

    ID_APP_ESM_PROCEDURE_ABORT_NOTIFY   = 0x13+APP_ESM_MSG_ID_HEADER,/*_H2ASN_MsgChoice  APP_ESM_PROCEDURE_ABORT_NOTIFY_STRU*/
    /* niuxiufan modify end */

    ID_APP_ESM_NDISCONN_REQ             = 0x14+APP_ESM_MSG_ID_HEADER,/*_H2ASN_MsgChoice  APP_ESM_NDISCONN_REQ_STRU*/
    ID_APP_ESM_NDISCONN_CNF             = 0x12+ESM_APP_MSG_ID_HEADER,/*_H2ASN_MsgChoice  APP_ESM_NDISCONN_CNF_STRU*/

    ID_APP_ESM_SET_CGDCONT_REQ          = 0x15+APP_ESM_MSG_ID_HEADER,/*_H2ASN_MsgChoice  APP_ESM_SET_CGDCONT_REQ_STRU*/
    ID_APP_ESM_SET_CGDCONT_CNF          = 0x13+ESM_APP_MSG_ID_HEADER,/*_H2ASN_MsgChoice  APP_ESM_SET_CGDCONT_CNF_STRU*/

    /**/
    ID_APP_ESM_INQ_TFT_REQ              = 0x31+APP_ESM_MSG_ID_HEADER,/*_H2ASN_MsgChoice  APP_ESM_INQ_TFT_REQ_STRU*/
    ID_APP_ESM_INQ_TFT_CNF              = 0x32+ESM_APP_MSG_ID_HEADER,/*_H2ASN_MsgChoice  APP_ESM_INQ_TFT_CNF_STRU*/

    ID_APP_ESM_INQ_QOS_REQ              = 0x33+APP_ESM_MSG_ID_HEADER,/*_H2ASN_MsgChoice  APP_ESM_INQ_QOS_REQ_STRU*/
    ID_APP_ESM_INQ_QOS_CNF              = 0x34+ESM_APP_MSG_ID_HEADER,/*_H2ASN_MsgChoice  APP_ESM_INQ_QOS_CNF_STRU*/

    ID_APP_ESM_INQ_EPS_QOS_REQ          = 0x35+APP_ESM_MSG_ID_HEADER,/*_H2ASN_MsgChoice  APP_ESM_INQ_EPS_QOS_REQ_STRU*/
    ID_APP_ESM_INQ_EPS_QOS_CNF          = 0x36+ESM_APP_MSG_ID_HEADER,/*_H2ASN_MsgChoice  APP_ESM_INQ_EPS_QOS_CNF_STRU*/

    ID_APP_ESM_INQ_APN_REQ              = 0x37+APP_ESM_MSG_ID_HEADER,/*_H2ASN_MsgChoice  APP_ESM_INQ_APN_REQ_STRU*/
    ID_APP_ESM_INQ_APN_CNF              = 0x38+ESM_APP_MSG_ID_HEADER,/*_H2ASN_MsgChoice  APP_ESM_INQ_APN_CNF_STRU*/

    ID_APP_ESM_INQ_PCO_REQ              = 0x39+APP_ESM_MSG_ID_HEADER,/*_H2ASN_MsgChoice  APP_ESM_INQ_PCO_REQ_STRU*/
    ID_APP_ESM_INQ_PCO_CNF              = 0x3A+ESM_APP_MSG_ID_HEADER,/*_H2ASN_MsgChoice  APP_ESM_INQ_PCO_CNF_STRU*/

    ID_APP_ESM_INQ_PDN_TYPE_REQ         = 0x3B+APP_ESM_MSG_ID_HEADER,/*_H2ASN_MsgChoice  APP_ESM_INQ_PDN_TYPE_REQ_STRU*/
    ID_APP_ESM_INQ_PDN_TYPE_CNF         = 0x3C+ESM_APP_MSG_ID_HEADER,/*_H2ASN_MsgChoice  APP_ESM_INQ_PDN_TYPE_CNF_STRU*/

    ID_APP_ESM_INQ_BEARER_TYPE_REQ      = 0x3D+APP_ESM_MSG_ID_HEADER,/*_H2ASN_MsgChoice  APP_ESM_INQ_BEARER_TYPE_REQ_STRU*/
    ID_APP_ESM_INQ_BEARER_TYPE_CNF      = ESM_APP_MSG_ID_HEADER + 0x3E,/*_H2ASN_MsgChoice  APP_ESM_INQ_BEARER_TYPE_CNF_STRU*/

    ID_APP_ESM_INQ_PDP_MANAGER_TYPE_REQ= 0x3F+APP_ESM_MSG_ID_HEADER,/*_H2ASN_MsgChoice  APP_ESM_INQ_PDP_MANAGER_TYPE_REQ_STRU*/
    ID_APP_ESM_INQ_PDP_MANAGER_TYPE_CNF= 0x40+ESM_APP_MSG_ID_HEADER,/*_H2ASN_MsgChoice  APP_ESM_INQ_PDP_MANAGER_TYPE_CNF_STRU*/

    ID_APP_ESM_INQ_BEAER_QOS_REQ        =  0x41 + APP_ESM_MSG_ID_HEADER,/*_H2ASN_MsgChoice  APP_ESM_INQ_BEAER_QOS_REQ_STRU*/
    ID_APP_ESM_INQ_BEAER_QOS_CNF        =  0x42 + ESM_APP_MSG_ID_HEADER,/*_H2ASN_MsgChoice  APP_ESM_INQ_BEAER_QOS_CNF_STRU*/
    ID_APP_ESM_INQ_BEAER_QOS_IND        =  0x43 + ESM_APP_MSG_ID_HEADER,/*_H2ASN_MsgChoice  APP_ESM_INQ_BEAER_QOS_IND_STRU*/

    ID_APP_ESM_INQ_DYNAMIC_PDP_CONT_REQ = 0x44+APP_ESM_MSG_ID_HEADER,/*_H2ASN_MsgChoice  APP_ESM_INQ_DYNAMIC_PDP_CONT_REQ_STRU*/
    ID_APP_ESM_INQ_DYNAMIC_PDP_CONT_CNF = 0x45+ESM_APP_MSG_ID_HEADER,/*_H2ASN_MsgChoice  APP_ESM_INQ_DYNAMIC_PDP_CONT_CNF_STRU*/

    ID_APP_ESM_INQ_DYNAMIC_EPS_QOS_REQ  = 0x46+APP_ESM_MSG_ID_HEADER,/*_H2ASN_MsgChoice  APP_ESM_INQ_DYNAMIC_EPS_QOS_REQ_STRU*/
    ID_APP_ESM_INQ_DYNAMIC_EPS_QOS_CNF  = 0x47+ESM_APP_MSG_ID_HEADER,/*_H2ASN_MsgChoice  APP_ESM_INQ_DYNAMIC_EPS_QOS_CNF_STRU*/

    ID_APP_ESM_INQ_DYNAMIC_TFT_REQ      = 0x48+APP_ESM_MSG_ID_HEADER,/*_H2ASN_MsgChoice  APP_ESM_INQ_DYNAMIC_TFT_REQ_STRU*/
    ID_APP_ESM_INQ_DYNAMIC_TFT_CNF      = 0x49+ESM_APP_MSG_ID_HEADER,/*_H2ASN_MsgChoice  APP_ESM_INQ_DYNAMIC_TFT_CNF_STRU*/

    ID_APP_ESM_INQ_GW_AUTH_REQ          = 0x4A+APP_ESM_MSG_ID_HEADER,/*_H2ASN_MsgChoice  APP_ESM_INQ_GW_AUTH_REQ_STRU*/
    ID_APP_ESM_INQ_GW_AUTH_CNF          = 0x4A+ESM_APP_MSG_ID_HEADER,/*_H2ASN_MsgChoice  APP_ESM_INQ_GW_AUTH_CNF_STRU*/

    /* niuxiufan DT begin */
    ID_APP_ESM_DT_INQ_PDP_INFO_REQ      = 0x4B+APP_ESM_MSG_ID_HEADER,/*_H2ASN_MsgChoice  APP_ESM_INQ_PDP_INFO_REQ_STRU*/
    ID_APP_ESM_DT_INQ_PDP_INFO_CNF      = 0x4B+ESM_APP_MSG_ID_HEADER,/*_H2ASN_MsgChoice  APP_ESM_INQ_PDP_INFO_CNF_STRU*/
    ID_APP_ESM_DT_INQ_PDP_INFO_IND      = 0x4C+ESM_APP_MSG_ID_HEADER,/*_H2ASN_MsgChoice  APP_ESM_INQ_PDP_INFO_IND_STRU*/
    /* niuxiufan DT end */

    /**/
    ID_APP_ESM_PDP_SETUP_REQ         = 0x61+APP_ESM_MSG_ID_HEADER,/*_H2ASN_MsgChoice  APP_ESM_PDP_SETUP_REQ_STRU*/
    ID_APP_ESM_PDP_SETUP_CNF         = 0x62+ESM_APP_MSG_ID_HEADER,/*_H2ASN_MsgChoice  APP_ESM_PDP_SETUP_CNF_STRU*/
    ID_APP_ESM_PDP_SETUP_IND         = 0x63+ESM_APP_MSG_ID_HEADER,/*_H2ASN_MsgChoice  APP_ESM_PDP_SETUP_IND_STRU*/

    ID_APP_ESM_PDP_MODIFY_REQ        = 0x64+APP_ESM_MSG_ID_HEADER,/*_H2ASN_MsgChoice  APP_ESM_PDP_MODIFY_REQ_STRU*/
    ID_APP_ESM_PDP_MODIFY_CNF        = 0x65+ESM_APP_MSG_ID_HEADER,/*_H2ASN_MsgChoice  APP_ESM_PDP_MODIFY_CNF_STRU*/
    ID_APP_ESM_PDP_MODIFY_IND        = 0x66+ESM_APP_MSG_ID_HEADER,/*_H2ASN_MsgChoice  APP_ESM_PDP_MODIFY_IND_STRU*/

    ID_APP_ESM_PDP_RELEASE_REQ       = 0x67+APP_ESM_MSG_ID_HEADER,/*_H2ASN_MsgChoice  APP_ESM_PDP_RELEASE_REQ_STRU*/
    ID_APP_ESM_PDP_RELEASE_CNF       = 0x68+ESM_APP_MSG_ID_HEADER,/*_H2ASN_MsgChoice  APP_ESM_PDP_RELEASE_CNF_STRU*/
    ID_APP_ESM_PDP_RELEASE_IND       = 0x69+ESM_APP_MSG_ID_HEADER,/*_H2ASN_MsgChoice  APP_ESM_PDP_RELEASE_IND_STRU*/

    ID_APP_ESM_PDP_MANAGER_IND       = 0x6A+ESM_APP_MSG_ID_HEADER,/*_H2ASN_MsgChoice  APP_ESM_PDP_MANAGER_IND_STRU*/
    ID_APP_ESM_PDP_MANAGER_RSP       = 0x6B+APP_ESM_MSG_ID_HEADER,/*_H2ASN_MsgChoice  APP_ESM_PDP_MANAGER_RSP_STRU*/

    ID_APP_ESM_MSG_TYPE_BUTT
};
typedef VOS_UINT32 APP_ESM_MSG_TYPE_ENUM_UINT32;


/*****************************************************************************
     : APP_ESM_PARA_SET_ENUM
   : 
*****************************************************************************/
enum APP_ESM_PARA_SET_ENUM
{
    APP_ESM_PARA_SETTING                = 0x00,
    APP_ESM_PARA_DELETE                 = 0x01,
    APP_ESM_PARA_BUTT
};
typedef VOS_UINT32 APP_ESM_PARA_SET_ENUM_UINT32;

/*****************************************************************************
     : APP_ESM_PARA_SET_RESULT_ENUM
   : 
*****************************************************************************/
enum APP_ESM_PARA_SET_RESULT_ENUM
{
    APP_ESM_PARA_SET_SUCCESS            = 0x00,
    APP_ESM_PARA_SET_FAIL               = 0x01,
    APP_ESM_PARA_SET_BUTT
};
typedef VOS_UINT32 APP_ESM_PARA_SET_RESULT_ENUM_UINT32;

/*****************************************************************************
     : APP_ESM_BEARER_STATE_ENUM
   : 
*****************************************************************************/
enum APP_ESM_BEARER_STATE_ENUM
{
    APP_ESM_BEARER_STATE_INACTIVE       = 0x00,
    APP_ESM_BEARER_STATE_ACTIVATED      = 0x01,
    APP_ESM_BEARER_STATE_BUTT
};
typedef VOS_UINT32 APP_ESM_BEARER_STATE_ENUM_UINT32;

/*****************************************************************************
     : APP_ESM_CAUSE_ENUM_UINT32
   : SM
*****************************************************************************/

typedef VOS_UINT32 APP_ESM_CAUSE_ENUM_UINT32;

/*****************************************************************************
     : APP_ESM_BEARER_TYPE_ENUM
   : 
*****************************************************************************/
enum APP_ESM_BEARER_TYPE_ENUM
{
    APP_ESM_BEARER_TYPE_DEFAULT         = 0x00,
    APP_ESM_BEARER_TYPE_DEDICATED       = 0x01,
    APP_ESM_BEARER_TYPE_EMERGENCY       = 0x02,
    APP_ESM_BEARER_TYPE_BUTT
};
typedef VOS_UINT32 APP_ESM_BEARER_TYPE_ENUM_UINT32;

/*****************************************************************************
     : APP_ESM_BEARER_MODIFY_ENUM
   : 
*****************************************************************************/
enum APP_ESM_BEARER_MODIFY_ENUM
{
    APP_ESM_BEARER_MODIFY_TFT           = 0x00,
    APP_ESM_BEARER_MODIFY_QOS           = 0x01,
    APP_ESM_BEARER_MODIFY_TFT_QOS       = 0x02,
    APP_ESM_BEARER_MODIFY_BUTT
};
typedef VOS_UINT32 APP_ESM_BEARER_MODIFY_ENUM_UINT32;

/*****************************************************************************
     : APP_ESM_BEARER_ACT_TYPE_ENUM
   : 
*****************************************************************************/
enum APP_ESM_BEARER_ACT_TYPE_ENUM
{
    APP_ESM_BEARER_ACT_TYPE_ACTIVE      = 0x00,
    APP_ESM_BEARER_ACT_TYPE_MODIFY      = 0x01,
    APP_ESM_BEARER_ACT_TYPE_BUTT
};
typedef VOS_UINT32 APP_ESM_BEARER_ACT_TYPE_ENUM_UINT32;

/*****************************************************************************
     : APP_ESM_BEARER_ACT_RESULT_ENUM
   : 
*****************************************************************************/
enum APP_ESM_BEARER_ACT_RESULT_ENUM
{
    APP_ESM_BEARER_ACT_ACCEPT           = 0x00,
    APP_ESM_BEARER_ACT_REJ              = 0x01,
    APP_ESM_BEARER_ACT_BUTT
};
typedef VOS_UINT32 APP_ESM_BEARER_ACT_RESULT_ENUM_UINT32;

/*****************************************************************************
     : APP_ESM_ANSWER_MODE_ENUM
   : 
*****************************************************************************/
enum APP_ESM_ANSWER_MODE_ENUM
{
    APP_ESM_ANSWER_MODE_AUTO            = 0x00,
    APP_ESM_ANSWER_MODE_MANI            = 0x01,
    APP_ESM_ANSWER_MODE_BUTT
};
typedef VOS_UINT32 APP_ESM_ANSWER_MODE_ENUM_UINT32;

/*****************************************************************************
     : APP_ESM_ANSWER_RESULT_ENUM
   : 
*****************************************************************************/
enum APP_ESM_ANSWER_RESULT_ENUM
{
    APP_ESM_ANSWER_ACCEPT               = 0x00,
    APP_ESM_ANSWER_REJ                  = 0x01,
    APP_ESM_ANSWER_RESULT_BUTT
};
typedef VOS_UINT32 APP_ESM_ANSWER_RESULT_ENUM_UINT32;

/*****************************************************************************
     : APP_ESM_PDN_TYPE_ENUM
   : PDN
*****************************************************************************/
enum APP_ESM_PDN_TYPE_ENUM
{
    APP_ESM_PDN_TYPE_IPV4               = 0x01,             /*24301 9.9.4.10*/
    APP_ESM_PDN_TYPE_IPV6               = 0x02,
    APP_ESM_PDN_TYPE_IPV4_IPV6          = 0x03,
    APP_ESM_PDN_TYPE_BUTT
};
typedef VOS_UINT32 APP_ESM_PDN_TYPE_ENUM_UINT32;

/*Modify by sunbing 49683 for CL multimode 2014-01-09 begin*/
/*****************************************************************************
     : APP_ESM_PDN_REQUEST_TYPE_ENUM
   : PDN 24008 10.5.6.17
*****************************************************************************/
enum APP_ESM_PDN_REQUEST_TYPE_ENUM
{
    APP_ESM_PDN_REQUEST_TYPE_INITIAL    = 0x01,             /*PDN*/
    APP_ESM_PDN_REQUEST_TYPE_HANDOVER   = 0x02,             /*non-3GPPPDN*/
    APP_ESM_PDN_REQUEST_TYPE_BUTT
};
typedef VOS_UINT32 APP_ESM_PDN_REQUEST_TYPE_ENUM_UINT32;
/*Modify by sunbing 49683 for CL multimode 2014-01-09 end*/


/*****************************************************************************
     : APP_ESM_CID_TYPE_ENUM
   : CID
*****************************************************************************/
enum APP_ESM_CID_TYPE_ENUM
{
    APP_ESM_CID_TYPE_DEFAULT             = 0x00,
    APP_ESM_CID_TYPE_DEDICATED           = 0x01,
    APP_ESM_CID_TYPE_EMERGENCY           = 0x02,
    APP_ESM_CID_TYPE_BUTT
};
typedef VOS_UINT32   APP_ESM_CID_TYPE_ENUM_UINT32;

enum APP_ESM_TRANSFER_DIRECTION_ENUM
{
    APP_ESM_TRANSFER_DIRECTION_PRE_REL7_TFT_FILTER          = 0x00,
    APP_ESM_TRANSFER_DIRECTION_DOWNLINK                     = 0x01,
    APP_ESM_TRANSFER_DIRECTION_UPLINK                       = 0x02,
    APP_ESM_TRANSFER_DIRECTION_UPLINK_DOWNLINK              = 0x03,
    APP_ESM_TRANSFER_DIRECTION_BUTT
};
typedef VOS_UINT8 APP_ESM_TRANSFER_DIRECTION_ENUM_UINT8;

enum APP_ESM_BEARER_OPERATE_TYPE_ENUM
{
    APP_ESM_BEARER_OPERATE_TYPE_DEF_ACT      = 0x00,
    APP_ESM_BEARER_OPERATE_TYPE_DEDI_ACT     = 0x01,
    APP_ESM_BEARER_OPERATE_TYPE_MODIFY       = 0x02,
    APP_ESM_BEARER_OPERATE_TYPE_BUTT
};
typedef VOS_UINT32 APP_ESM_BEARER_OPERATE_TYPE_ENUM_UINT32;

enum APP_ESM_IPV4_ADDR_ALLOC_TYPE_ENUM
{
   APP_ESM_IPV4_ADDR_ALLOC_TYPE_NAS_SIGNALING   = 0x00,
   APP_ESM_IPV4_ADDR_ALLOC_TYPE_DHCP            = 0x01,

   APP_ESM_IPV4_ADDR_ALLOC_TYPE_BUTT
};
typedef VOS_UINT32 APP_ESM_IPV4_ADDR_ALLOC_TYPE_ENUM_UINT32;

enum APP_ESM_PDP_SETUP_TYPE_ENUM
{
    APP_ESM_PDP_SETUP_TYPE_NORMAL       = 0x00,
    APP_ESM_PDP_SETUP_TYPE_PPP          = 0x01,

    APP_ESM_PDP_SETUP_TYPE_BUTT         = 0xFF
};

typedef VOS_UINT32 APP_ESM_PDP_SETUP_TYPE_ENUM_UINT32;
/* EABAPP */
enum APP_ESM_BEARER_PRIO_ENUM
{
    APP_ESM_BEARER_PRIO_NORMAL          = 0x00,
    APP_ESM_BEARER_PRIO_LOW             = 0x01,

    APP_ESM_BEARER_PRIO_BUTT
};

typedef VOS_UINT32 APP_ESM_BEARER_PRIO_ENUM_UINT32;


/*****************************************************************************
 : APP_ESM_AUTH_TYPE_ENUM
 : Authentication Type
*****************************************************************************/
enum APP_ESM_AUTH_TYPE_ENUM
{
    APP_ESM_AUTH_TYPE_NONE              = 0x00,
    APP_ESM_AUTH_TYPE_PAP               = 0x01,
    APP_ESM_AUTH_TYPE_CHAP              = 0x02,

    APP_ESM_AUTH_TYPE_BUTT              = 0xFF
};

typedef VOS_UINT8 APP_ESM_AUTH_TYPE_ENUM_UINT8;

enum APP_ESM_BEARER_MANAGE_TYPE_ENUM
{
    APP_ESM_BEARER_MANAGE_TYPE_ACCEPT = 0,                  /**/
    APP_ESM_BEARER_MANAGE_TYPE_REJ,                         /**/

    APP_ESM_BEARER_MANANGE_TYPE_BUTT
};
typedef VOS_UINT8  APP_ESM_BEARER_MANAGE_TYPE_ENUM_UINT8;

enum APP_ESM_BEARER_MANAGE_MODE_ENUM
{
    APP_ESM_BEARER_MANAGE_MODE_AUTO = 0,                    /**/
    APP_ESM_BEARER_MANAGE_MODE_MANUAL,                      /**/

    APP_ESM_BEARER_MANAGE_MODE_BUTT
};
typedef VOS_UINT8  APP_ESM_BEARER_MANAGE_MODE_ENUM_UINT8;

/*niuxiufan DT begin */

/*****************************************************************************
     : NAS_ESM_DT_BEARER_TYPE_ENUM
   : 
*****************************************************************************/

enum NAS_ESM_DT_BEARER_TYPE_ENUM
{
    NAS_ESM_DT_BEARER_TYPE_DEFAULT = 0,                /**/
    NAS_ESM_DT_BEARER_TYPE_DEDICATED,                  /**/
    NAS_ESM_DT_BEARER_TYPE_EMERGENCY,                  /**/

    NAS_ESM_DT_BEARER_TYPE_BUTT
};/**/
typedef VOS_UINT8  NAS_ESM_DT_BEARER_TYPE_ENUM_UINT8;
/*niuxiufan DT end */

enum APP_ESM_PCSCF_DISCOVERY_ENUM
{
    APP_ESM_PCSCF_DISCOVERY_NOT_INFLUENCED  = 0x00,
    APP_ESM_PCSCF_DISCOVERY_THROUGH_NAS_SIG = 0x01,
    APP_ESM_PCSCF_DISCOVERY_THROUGH_DHCP    = 0x02,

    APP_ESM_PCSCF_DISCOVERY_BUTT
};
typedef VOS_UINT32 APP_ESM_PCSCF_DISCOVERY_ENUM_UINT32;

enum APP_ESM_IMS_CN_SIG_FLAG_ENUM
{
    APP_ESM_PDP_NOT_FOR_IMS_CN_SIG_ONLY     = 0x00,
    APP_ESM_PDP_FOR_IMS_CN_SIG_ONLY         = 0x01,

    APP_ESM_IMS_CN_SIG_FLAG_BUTT
};
typedef VOS_UINT32 APP_ESM_IMS_CN_SIG_FLAG_ENUM_UINT32;

enum APP_ESM_PDP_EMC_IND_ENUM
{
    APP_ESM_PDP_NOT_FOR_EMC             = 0x00,
    APP_ESM_PDP_FOR_EMC                 = 0x01,

    APP_ESM_PDP_EMC_IND_BUTT
};
typedef VOS_UINT32 APP_ESM_PDP_EMC_IND_ENUM_UINT32;

/*****************************************************************************
     : APP_ESM_PDP_RELEASE_CAUSE_ENUM
   : PDP
*****************************************************************************/
enum APP_ESM_PDP_RELEASE_CAUSE_ENUM
{
    APP_ESM_PDP_RELEASE_CAUSE_NORMAL                  = 0,
    APP_ESM_PDP_RELEASE_CAUSE_IPV6_ADDR_ALLOC_FAIL    = 1,
    APP_ESM_PDP_RELEASE_CAUSE_IPV6_ADDR_TIME_OUT      = 2,
    APP_ESM_PDP_RELEASE_CAUSE_PCSCF_ADDR_ALLOC_FAIL   = 3,
    APP_ESM_PDP_RELEASE_CAUSE_REATTACH                = 4,
    APP_ESM_PDP_RELEASE_CAUSE_BUTT
};
typedef VOS_UINT8 APP_ESM_PDP_RELEASE_CAUSE_ENUM_UINT8;

/*****************************************************************************
     : APP_ESM_ATTACH_APN_TYPE_ENUM_UINT8
   : APN 
*****************************************************************************/
enum APP_ESM_ATTACH_APN_TYPE_ENUM
{
    APP_ESM_ATTACH_APN_TYPE_INVALID = 0x00,
    APP_ESM_ATTACH_APN_TYPE_CLASS1  = 0x01,
    APP_ESM_ATTACH_APN_TYPE_CLASS2  = 0x02,
    APP_ESM_ATTACH_APN_TYPE_CLASS3  = 0x03,
    APP_ESM_ATTACH_APN_TYPE_CLASS4  = 0x04,

    APP_ESM_ATTACH_APN_TYPE_BUTT
};
typedef VOS_UINT8 APP_ESM_ATTACH_APN_TYPE_ENUM_UINT8;



/*****************************************************************************
  5 STRUCT
*****************************************************************************/
/*****************************************************************************
*                                                                            *
*                                                            *
*                                                                            *
******************************************************************************/

/*****************************************************************************
     : APP_ESM_ATTACH_APN_INFO_STRU
   : APN
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulCid;  /*CID [0,11]*/
    APP_ESM_ATTACH_APN_TYPE_ENUM_UINT8  enApnType;    /*apn class*/
    VOS_UINT8                           ucDisableFlag;/*apn disable flag*/
    VOS_UINT8                           aucReserved[2];
    VOS_UINT32                          ulInactivityTimerValue;/*Inactivity Timer Value in second*/
}APP_ESM_ATTACH_APN_INFO_STRU;


/*****************************************************************************
     : APP_ESM_PARA_SET_CNF_STRU
   : 
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;             /**/
    VOS_UINT32                          ulCid;              /*:0~31   */
    VOS_UINT32                          ulSetRslt;          /*:0:,1:   */
}APP_ESM_PARA_SET_CNF_STRU;

/*****************************************************************************
     : APP_ESM_TFT_INFO_STRU
   : TFT  
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpRmtIpv4AddrAndMask        : 1;
    VOS_UINT32                          bitOpRmtIpv6AddrAndMask        : 1;
    VOS_UINT32                          bitOpProtocolId                : 1;
    VOS_UINT32                          bitOpSingleLocalPort           : 1;
    VOS_UINT32                          bitOpLocalPortRange            : 1;
    VOS_UINT32                          bitOpSingleRemotePort          : 1;
    VOS_UINT32                          bitOpRemotePortRange           : 1;
    VOS_UINT32                          bitOpSecuParaIndex             : 1;
    VOS_UINT32                          bitOpTypeOfService             : 1;
    VOS_UINT32                          bitOpFlowLabelType             : 1;
    VOS_UINT32                          bitOpLocalIpv4AddrAndMask      : 1;
    VOS_UINT32                          bitOpLocalIpv6AddrAndMask      : 1;
    VOS_UINT32                          bitOpSpare                     : 20;

    VOS_UINT8                           ucPacketFilterId;
    VOS_UINT8                           ucNwPacketFilterId;
    APP_ESM_TRANSFER_DIRECTION_ENUM_UINT8 enDirection;
    VOS_UINT8                           ucPrecedence;             /*packet filter evaluation precedence*/


    VOS_UINT32                          ulSecuParaIndex;          /*SPI*/
    VOS_UINT16                          usSingleLcPort;
    VOS_UINT16                          usLcPortHighLimit;
    VOS_UINT16                          usLcPortLowLimit;
    VOS_UINT16                          usSingleRmtPort;
    VOS_UINT16                          usRmtPortHighLimit;
    VOS_UINT16                          usRmtPortLowLimit;
    VOS_UINT8                           ucProtocolId;             /**/
    VOS_UINT8                           ucTypeOfService;          /*TOS*/

    VOS_UINT8                           ucTypeOfServiceMask;      /*TOS Mask*/
    VOS_UINT8                           aucReserved[1];

    VOS_UINT8                           aucRmtIpv4Address[APP_MAX_IPV4_ADDR_LEN];
                                                                  /*ucSourceIpAddress[0]IP
                                                                  ucSourceIpAddress[3]*/
    VOS_UINT8                           aucRmtIpv4Mask[APP_MAX_IPV4_ADDR_LEN];
                                                                  /*ucSourceIpMask[0]IP ,
                                                                  ucSourceIpMask[3]*/
    VOS_UINT8                           aucRmtIpv6Address[APP_MAX_IPV6_ADDR_LEN];
                                                                  /*ucRmtIpv6Address[0]IPv6
                                                                    ucRmtIpv6Address[7]IPv6*/
    VOS_UINT8                           aucRmtIpv6Mask[APP_MAX_IPV6_ADDR_LEN];
                                                                  /*ucRmtIpv6Mask[0]
                                                                    ucRmtIpv6Mask[7]*/

    VOS_UINT32                          ulFlowLabelType;          /*FlowLabelType*/
    VOS_UINT8                           aucLocalIpv4Addr[APP_MAX_IPV4_ADDR_LEN];
    VOS_UINT8                           aucLocalIpv4Mask[APP_MAX_IPV4_ADDR_LEN];
    VOS_UINT8                           aucLocalIpv6Addr[APP_MAX_IPV6_ADDR_LEN];
    VOS_UINT8                           ucLocalIpv6Prefix;
    VOS_UINT8                           aucReserved2[3];
}APP_ESM_TFT_INFO_STRU;
/*****************************************************************************
     : APP_ESM_SET_TFT_REQ_STRU
   : TFT  
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;             /**/
    VOS_UINT32                          ulCid;              /*:0~31       */
    APP_ESM_PARA_SET_ENUM_UINT32        enSetType;          /*:0:,1:*/
    APP_ESM_TFT_INFO_STRU               stAppTftInfo;       /*TFT*/
} APP_ESM_SET_TFT_REQ_STRU;

typedef  APP_ESM_PARA_SET_CNF_STRU APP_ESM_SET_TFT_CNF_STRU;

/*****************************************************************************
     : APP_ESM_QOS_INFO_STRU
   : QOS  
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucDelayClass;
    VOS_UINT8                           ucReliabClass;
    VOS_UINT8                           ucPeakThrough;
    VOS_UINT8                           ucPrecedenceClass;
    VOS_UINT8                           ucMeanThrough;
    VOS_UINT8                           ucTrafficClass;
    VOS_UINT8                           ucDeliverOrder;
    VOS_UINT8                           ucDeliverOfErrSdu;
    VOS_UINT8                           ucMaximSduSize;
    VOS_UINT8                           ucMaxBitRateForUp;
    VOS_UINT8                           ucMaxBitRateForDown;
    VOS_UINT8                           ucResidualBer;
    VOS_UINT8                           ucSduErrRatio;
    VOS_UINT8                           ucTransDelay;
    VOS_UINT8                           ucTraffHandlPrior;
    VOS_UINT8                           ucGuarantBitRateForUp;
    VOS_UINT8                           ucGuarantBitRateForDown;
    VOS_UINT8                           ucSrcStatisticsDescriptor;
    VOS_UINT8                           ucSignallingIndication;
    VOS_UINT8                           ucMaxBitRateForDownExt;
    VOS_UINT8                           ucGuarantBitRateForDownExt;
    VOS_UINT8                           ucMaxBitRateForUpExt;
    VOS_UINT8                           ucGuarantBitRateForUpExt;
    VOS_UINT8                           ucMaxBitRateForDownExt_2;
    VOS_UINT8                           ucGuarantBitRateForDownExt_2;
    VOS_UINT8                           ucMaxBitRateForUpExt_2;
    VOS_UINT8                           ucGuarantBitRateForUpExt_2;

    VOS_UINT8                           ucReserved[1];
}APP_ESM_QOS_INFO_STRU;


/*****************************************************************************
     : APP_ESM_SET_QOS_REQ_STRU
   : QOS  
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    VOS_UINT32                          ulCid;              /*:0~31       */
    APP_ESM_PARA_SET_ENUM_UINT32        enSetType;          /*:0:,1:*/
    APP_ESM_QOS_INFO_STRU               stAppQoSInfo;       /*APP_ESM_QOS_INFO_STRU*/
}APP_ESM_SET_QOS_REQ_STRU;

typedef  APP_ESM_PARA_SET_CNF_STRU APP_ESM_SET_QOS_CNF_STRU;

/*****************************************************************************
     : APP_ESM_EPS_QOS_INFO_STRU
   : EPS_QOS  
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucQCI;
    VOS_UINT8                           aucRsv[3];
    VOS_UINT32                          ulULMaxRate;    /* kbps */
    VOS_UINT32                          ulDLMaxRate;    /* kbps */
    VOS_UINT32                          ulULGMaxRate;   /* kbps */
    VOS_UINT32                          ulDLGMaxRate;   /* kbps */
}APP_ESM_EPS_QOS_INFO_STRU;

typedef struct
{
    VOS_UINT32                           ulEpsbId;
    APP_ESM_EPS_QOS_INFO_STRU            stQos;
} APP_EPS_QOS_STRU;
/*****************************************************************************
     : APP_ESM_SET_EPS_QOS_REQ_STRU
   : SDF QOS  
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    VOS_UINT32                          ulCid;

    APP_ESM_PARA_SET_ENUM_UINT32        enSetType;          /*0:SET;1:DEL*/
    APP_ESM_EPS_QOS_INFO_STRU           stSdfQosInfo;

}APP_ESM_SET_EPS_QOS_REQ_STRU;


typedef  APP_ESM_PARA_SET_CNF_STRU APP_ESM_SET_EPS_QOS_CNF_STRU;


/*****************************************************************************
     : APP_ESM_APN_INFO_STRU
   : APN  
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucApnLen;
    VOS_UINT8                           aucApnName[APP_MAX_APN_LEN];
}APP_ESM_APN_INFO_STRU;

/*****************************************************************************
     : APP_ESM_SET_APN_REQ_STRU
   : APN  
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    VOS_UINT32                          ulCid;

    APP_ESM_PARA_SET_ENUM_UINT32        enSetType;          /*0:SET;1:DEL*/
    APP_ESM_APN_INFO_STRU               stApnInfo;
}APP_ESM_SET_APN_REQ_STRU;

typedef  APP_ESM_PARA_SET_CNF_STRU APP_ESM_SET_APN_CNF_STRU;


/*****************************************************************************
     : APP_ESM_APN_AMBR_INFO_STRU
   : APN AMBR 
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpDLApnAmbrExt                 : 1;
    VOS_UINT32                          bitOpULApnAmbrExt                 : 1;
    VOS_UINT32                          bitOpDLApnAmbrExt2                : 1;
    VOS_UINT32                          bitOpULApnAmbrExt2                : 1;
    VOS_UINT32                          bitOpSpare                        : 28;

    VOS_UINT8                           ucDLApnAmbr;
    VOS_UINT8                           ucULApnAmbr;
    VOS_UINT8                           ucDLApnAmbrExt;
    VOS_UINT8                           ucULApnAmbrExt;
    VOS_UINT8                           ucDLApnAmbrExt2;
    VOS_UINT8                           ucULApnAmbrExt2;
    VOS_UINT8                           aucRsv[2];

}APP_ESM_APN_AMBR_INFO_STRU;

/*****************************************************************************
     : APP_ESM_PCO_INFO_STRU
   : PCO  
*****************************************************************************/
typedef struct
{

    VOS_UINT32                          bitOpAPL                          : 1;
    VOS_UINT32                          bitOpCPOL                         : 1;
    VOS_UINT32                          bitOpPCSCFAddReq                  : 1;
    VOS_UINT32                          bitOpIMCNFlag                     : 1;
    VOS_UINT32                          bitOpDNSAddrReq                   : 1;
    VOS_UINT32                          bitOpMSBearCtrlID                 : 1;
    VOS_UINT32                          bitOpPrefBearCtrlMode             : 1;

    VOS_UINT32                          bitOpSpare                        : 25;

    VOS_UINT8                           ucConfigProtocol;
    VOS_UINT8                           ucBearMode;       /*container identifierPreferred Bearer Control Mode*/
    VOS_UINT8                           ucReserved[2];
    VOS_UINT16                          usAPLCid;          /*Additional parameters listcontainer identifier*/
    VOS_UINT16                          usCPOLPid;         /*Configuration protocol options listprotocol identifier*/
    VOS_UINT8                           aucPPPPacket[248];
}APP_ESM_PCO_INFO_STRU;



/*****************************************************************************
     : APP_ESM_SET_PCO_REQ_STRU
   : PCO 
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;             /**/
    VOS_UINT32                          ulCid;              /*:0~31       */

    APP_ESM_PARA_SET_ENUM_UINT32        enSetType;          /*:0:,1:*/
    APP_ESM_PCO_INFO_STRU               stAppPcoInfo;       /*PCO*/
} APP_ESM_SET_PCO_REQ_STRU;

typedef  APP_ESM_PARA_SET_CNF_STRU APP_ESM_SET_PCO_CNF_STRU;

/*****************************************************************************
     : APP_ESM_SET_PDN_TYPE_REQ_STRU
   : PDN_TYPE 
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    VOS_UINT32                          ulCid;

    VOS_UINT32                          bitOpIpv4AddrAllocType    :1;
    VOS_UINT32                          bitOpSpare              :31;

    APP_ESM_PARA_SET_ENUM_UINT32        enSetType;          /*0:SET;1:DEL*/
    APP_ESM_PDN_TYPE_ENUM_UINT32        enPdnType;      /*1:IPV4,2:IPV6,3:BOTH*/
    APP_ESM_IPV4_ADDR_ALLOC_TYPE_ENUM_UINT32 enIpv4AddrAllocType;
}APP_ESM_SET_PDN_TYPE_REQ_STRU;
typedef  APP_ESM_PARA_SET_CNF_STRU APP_ESM_SET_PDN_TYPE_CNF_STRU;

/*****************************************************************************
     : APP_ESM_SET_BEARER_TYPE_REQ_STRU
   : BEARER_TYPE  
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    VOS_UINT32                          ulCid;

    VOS_UINT32                          bitOpLinkdCid       :1;
    VOS_UINT32                          bitOpSpare          :31;

    APP_ESM_PARA_SET_ENUM_UINT32        enSetType;
    APP_ESM_CID_TYPE_ENUM_UINT32        enBearCidType;

    VOS_UINT32                          ulLinkdCid;

}APP_ESM_SET_BEARER_TYPE_REQ_STRU;

typedef  APP_ESM_PARA_SET_CNF_STRU APP_ESM_SET_BEARER_TYPE_CNF_STRU;


/*****************************************************************************
     : APP_ESM_SET_PDP_MANAGER_TYPE_REQ_STRU
   : APP
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;

    APP_ESM_PARA_SET_ENUM_UINT32        enSetType;
    APP_ESM_ANSWER_MODE_ENUM_UINT32     enAnsMode;          /*APP:0:,1:*/
    APP_ESM_ANSWER_RESULT_ENUM_UINT32   enAnsType;          /*APP:0:,1:,*/

} APP_ESM_SET_PDP_MANAGER_TYPE_REQ_STRU;

typedef struct
{
    VOS_MSG_HEADER                              /*_H2ASN_Skip*/
    VOS_UINT32              ulMsgId;            /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32              ulOpId;
    VOS_UINT32              ulSetRslt;
} APP_ESM_SET_PDP_MANAGER_TYPE_CNF_STRU;

/*****************************************************************************
     : APP_ESM_SET_GW_AUTH_REQ_STRU
   : 
*****************************************************************************/
typedef struct
{
    APP_ESM_AUTH_TYPE_ENUM_UINT8        enGwAuthType;
    VOS_UINT8                           ucAccNumLen;
    VOS_UINT8                           aucRsv1[2];
    VOS_UINT8                           auAccessNum[APP_ESM_MAX_ACCESS_NUM_LEN];/**/
    VOS_UINT8                           ucUserNameLen;
    VOS_UINT8                           aucRsv2[2];
    VOS_UINT8                           aucUserName[APP_ESM_MAX_USER_NAME_LEN];
    VOS_UINT8                           ucPwdLen;
    VOS_UINT8                           aucRsv3[2];
    VOS_UINT8                           aucPwd[APP_ESM_MAX_PASSWORD_LEN];
}APP_ESM_GW_AUTH_INFO_STRU;

/*****************************************************************************
     : APP_ESM_SDF_PARA_STRU
   : APPESM SDF
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpPdnType         : 1;
    VOS_UINT32                          bitOpApn             : 1;
    VOS_UINT32                          bitOpSdfQos          : 1;
    VOS_UINT32                          bitOpLinkdCId        : 1;
    VOS_UINT32                          bitIpv4AddrAllocType : 1;
    VOS_UINT32                          bitOpGwAuthInfo      : 1;
    VOS_UINT32                          bitOpPcscfDiscovery  : 1;
    VOS_UINT32                          bitOpImsCnSignalFlag : 1;
    VOS_UINT32                          bitOpSpare           : 24;

    APP_ESM_PDN_TYPE_ENUM_UINT32        enPdnType;
    APP_ESM_IPV4_ADDR_ALLOC_TYPE_ENUM_UINT32 enIpv4AddrAllocType;
    APP_ESM_BEARER_TYPE_ENUM_UINT32      enBearerCntxtType;  /* SM */

    VOS_UINT32                          ulCId;              /* ID */
    VOS_UINT32                          ulLinkdCId;         /*CID*/

    VOS_UINT32                          ulPfNum;
    APP_ESM_EPS_QOS_INFO_STRU           stSdfQosInfo;
    APP_ESM_APN_INFO_STRU               stApnInfo;
    APP_ESM_GW_AUTH_INFO_STRU           stGwAuthInfo;
    APP_ESM_TFT_INFO_STRU               astCntxtTftInfo[APP_ESM_MAX_SDF_PF_NUM];
    APP_ESM_PCSCF_DISCOVERY_ENUM_UINT32 enPcscfDiscovery;
    APP_ESM_IMS_CN_SIG_FLAG_ENUM_UINT32 enImsCnSignalFlag;
}APP_ESM_SDF_PARA_STRU;


typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    VOS_UINT32                          ulCid;

    APP_ESM_PARA_SET_ENUM_UINT32        enSetType;
    APP_ESM_GW_AUTH_INFO_STRU           stGwAuthInfo;
}APP_ESM_SET_GW_AUTH_REQ_STRU;

typedef  APP_ESM_PARA_SET_CNF_STRU APP_ESM_SET_GW_AUTH_CNF_STRU;


/*****************************************************************************
*                                                                            *
*                                                            *
*                                                                            *
******************************************************************************/

/*****************************************************************************
     : APP_ESM_INQ_PARA_REQ_STRU
   : 
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    VOS_UINT32                          ulCid;
}APP_ESM_INQ_PARA_REQ_STRU;

typedef APP_ESM_INQ_PARA_REQ_STRU APP_ESM_INQ_TFT_REQ_STRU;

/*****************************************************************************
     : APP_ESM_INQ_TFT_CNF_STRU
   : :TFT
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                  ulOpId;
    VOS_UINT32                  ulCid;
    VOS_UINT32                  ulRslt;
    VOS_UINT32                  ulPfNum;           /*PF*/
    APP_ESM_TFT_INFO_STRU       astPfInfo[APP_ESM_TFT_MAX_PF_NUM];
}APP_ESM_INQ_TFT_CNF_STRU;

typedef APP_ESM_INQ_PARA_REQ_STRU APP_ESM_INQ_QOS_REQ_STRU;

/*****************************************************************************
     : APP_ESM_INQ_QOS_CNF_STRU
   : :QOS
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    VOS_UINT32                          ulCid;
    VOS_UINT32                          ulRslt;
    APP_ESM_QOS_INFO_STRU               stAppQoSInfo;       /*APP_ESM_QOS_INFO_STRU*/
}APP_ESM_INQ_QOS_CNF_STRU;


typedef APP_ESM_INQ_PARA_REQ_STRU APP_ESM_INQ_PCO_REQ_STRU;

/*****************************************************************************
     : APP_ESM_INQ_PCO_CNF_STRU
   : :PCO
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    VOS_UINT32                          ulCid;
    VOS_UINT32                          ulRslt;
    APP_ESM_PCO_INFO_STRU               stAppPcoInfo;       /*PCO*/
} APP_ESM_INQ_PCO_CNF_STRU;


typedef APP_ESM_INQ_PARA_REQ_STRU APP_ESM_INQ_BEARER_TYPE_REQ_STRU;

/*****************************************************************************
     : APP_ESM_INQ_BEARER_TYPE_CNF_STRU
   : :BEARER_TYPE
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    VOS_UINT32                          ulCid;
    VOS_UINT32                          bitOpLinkdCid       :1;
    VOS_UINT32                          bitOpSpare          :31;

    VOS_UINT32                          ulRslt;
    APP_ESM_CID_TYPE_ENUM_UINT32        enBearCidType;
    VOS_UINT32                          ulLinkdCid;         /*CID*/

} APP_ESM_INQ_BEARER_TYPE_CNF_STRU;


typedef APP_ESM_INQ_PARA_REQ_STRU APP_ESM_INQ_PDN_TYPE_REQ_STRU;

/*****************************************************************************
     : APP_ESM_INQ_PDN_TYPE_CNF_STRU
   : :PDN_TYPE
*****************************************************************************/

typedef struct
{
    VOS_MSG_HEADER                                                  /*_H2ASN_Skip*/
    VOS_UINT32                                  ulMsgId;            /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                                  ulOpId;
    VOS_UINT32                                  ulCid;

    VOS_UINT32                                  bitOpIpv4AddrAllocType    :1;
    VOS_UINT32                                  bitOpSpare                :31;

    VOS_UINT32                                  ulRslt;
    APP_ESM_PDN_TYPE_ENUM_UINT32                enPdnType;          /*1:IPV4,2:IPV6,3:BOTH*/
    APP_ESM_IPV4_ADDR_ALLOC_TYPE_ENUM_UINT32    enIpv4AddrAllocType;
} APP_ESM_INQ_PDN_TYPE_CNF_STRU;

typedef APP_ESM_INQ_PARA_REQ_STRU APP_ESM_INQ_APN_REQ_STRU;

/*****************************************************************************
     : APP_ESM_INQ_APN_TYPE_CNF_STRU
   : :APN
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    VOS_UINT32                          ulCid;

    VOS_UINT32                          ulRslt;
    APP_ESM_APN_INFO_STRU               stApnInfo;
} APP_ESM_INQ_APN_CNF_STRU;

typedef APP_ESM_INQ_PARA_REQ_STRU APP_ESM_INQ_EPS_QOS_REQ_STRU;

/*****************************************************************************
     : APP_ESM_INQ_EPS_QOS_CNF_STRU
   : :SDF QOS
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    VOS_UINT32                          ulCid;
    VOS_UINT32                          ulRslt;

    APP_ESM_EPS_QOS_INFO_STRU           stSdfQosInfo;
} APP_ESM_INQ_EPS_QOS_CNF_STRU;

/*****************************************************************************
     : APP_ESM_INQ_PDP_MANAGER_TYPE_REQ_STRU
   : :BEARER_MANAGER_TYPE
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32               ulMsgId;                       /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32               ulOpId;
} APP_ESM_INQ_PDP_MANAGER_TYPE_REQ_STRU;

/*****************************************************************************
     : APP_ESM_INQ_PDP_MANAGER_TYPE_CNF_STRU
   : :BEARER_MANAGER_TYPE
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;

    VOS_UINT32                          ulRslt;
    APP_ESM_ANSWER_MODE_ENUM_UINT32     enAnsMode;          /*APP:0:,1:*/
    APP_ESM_ANSWER_RESULT_ENUM_UINT32   enAnsType;          /*APP:0:,1:,*/
} APP_ESM_INQ_PDP_MANAGER_TYPE_CNF_STRU;

/*****************************************************************************
     : APP_ESM_INQ_BEAER_QOS_REQ_STRU
   : :BEARER_QOS
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                  /*_H2ASN_Skip*/
    VOS_UINT32 ulMsgId;    /*_H2ASN_Skip*/

    APP_MSG_HEADER
    VOS_UINT32                             ulEpsbId;
} APP_ESM_INQ_BEAER_QOS_REQ_STRU;

/*****************************************************************************
     : APP_ESM_INQ_BEAER_QOS_CNF_STRU
   : :BEARER_QOS
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                  /*_H2ASN_Skip*/
    VOS_UINT32 ulMsgId;    /*_H2ASN_Skip*/

    APP_MSG_HEADER
    VOS_UINT32                             ulEpsbIdNum;
    APP_EPS_QOS_STRU                       astQosInfo[APP_ESM_MAX_EPSB_NUM];
    APP_ESM_ANSWER_RESULT_ENUM_UINT32      enAnsType;
}APP_ESM_INQ_BEAER_QOS_CNF_STRU;

typedef struct
{
    VOS_MSG_HEADER                                  /*_H2ASN_Skip*/
    VOS_UINT32 ulMsgId;    /*_H2ASN_Skip*/

    APP_MSG_HEADER
    VOS_UINT32                             ulEpsbId;
    APP_ESM_EPS_QOS_INFO_STRU              stQosInfo;
}APP_ESM_INQ_BEAER_QOS_IND_STRU;

typedef APP_ESM_INQ_PARA_REQ_STRU APP_ESM_INQ_DYNAMIC_PDP_CONT_REQ_STRU;

/*****************************************************************************
     : APP_ESM_IP_ADDR_STRU
   : IP
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucIpType;
    VOS_UINT8                           ucReserved[3];
    VOS_UINT8                           aucIpV4Addr[APP_MAX_IPV4_ADDR_LEN];
    VOS_UINT8                           aucIpV6Addr[APP_MAX_IPV6_ADDR_LEN];
}APP_ESM_IP_ADDR_STRU;

/*****************************************************************************
     : APP_ESM_INQ_DYNAMIC_PDP_CONT_CNF_STRU
   : :PDP
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    VOS_UINT32                          ulCid;

    VOS_UINT32                          bitOpPdnAddr         :1;
    VOS_UINT32                          bitOpApn             :1;
    VOS_UINT32                          bitOpLinkCid         :1;
    VOS_UINT32                          bitOpDnsPrim         :1;
    VOS_UINT32                          bitOpDnsSec          :1;
    VOS_UINT32                          bitOpPCscfPrim       :1;
    VOS_UINT32                          bitOpPCscfSec        :1;
    VOS_UINT32                          bitOpGateWayAddrInfo :1;
    VOS_UINT32                          bitOpImsCnSignalFlag :1;
    VOS_UINT32                          bitOpIpv4Mtu         : 1;
    VOS_UINT32                          bitOpSpare           :22;

    VOS_UINT32                          ulRslt;
    VOS_UINT32                          ulEpsbId;
    APP_ESM_IP_ADDR_STRU                stPDNAddrInfo;
    APP_ESM_IP_ADDR_STRU                stSubnetMask;
    APP_ESM_IP_ADDR_STRU                stGateWayAddrInfo;
    APP_ESM_IP_ADDR_STRU                stDnsPrimAddrInfo;  /*DNS */
    APP_ESM_IP_ADDR_STRU                stDnsSecAddrInfo;   /*DNS */
    APP_ESM_IP_ADDR_STRU                stPCscfPrimAddrInfo;/*P-CSCF */
    APP_ESM_IP_ADDR_STRU                stPCscfSecAddrInfo; /* P-CSCF */
    APP_ESM_APN_INFO_STRU               stApnInfo;
    VOS_UINT32                          ulLinkCid;
    APP_ESM_IMS_CN_SIG_FLAG_ENUM_UINT32 enImsCnSignalFlag;
    VOS_UINT16                          usIpv4Mtu;
    VOS_UINT8                           aucReserved[2];
} APP_ESM_INQ_DYNAMIC_PDP_CONT_CNF_STRU;

typedef APP_ESM_INQ_PARA_REQ_STRU APP_ESM_INQ_DYNAMIC_EPS_QOS_REQ_STRU;

/*****************************************************************************
     : APP_ESM_INQ_DYNAMIC_EPS_QOS_CNF_STRU
   : :EPS QoS
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                           /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;             /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    VOS_UINT32                          ulCid;

    VOS_UINT32                          ulRslt;
    APP_ESM_EPS_QOS_INFO_STRU           stSdfQosInfo;
} APP_ESM_INQ_DYNAMIC_EPS_QOS_CNF_STRU;

typedef APP_ESM_INQ_PARA_REQ_STRU APP_ESM_INQ_DYNAMIC_TFT_REQ_STRU;

/*****************************************************************************
     : APP_ESM_INQ_DYNAMIC_TFT_CNF_STRU
   : :TFT
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                           /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;             /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    VOS_UINT32                          ulCid;

    VOS_UINT32                          ulRslt;
    VOS_UINT32                          ulPfNum;             /*PF*/
    APP_ESM_TFT_INFO_STRU               astPfInfo[APP_ESM_TFT_MAX_PF_NUM];
} APP_ESM_INQ_DYNAMIC_TFT_CNF_STRU;


typedef APP_ESM_INQ_PARA_REQ_STRU APP_ESM_INQ_GW_AUTH_REQ_STRU;

/*****************************************************************************
     : APP_ESM_INQ_GW_AUTH_CNF_STRU
   : :
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                           /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;             /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    VOS_UINT32                          ulCid;
    VOS_UINT32                          ulRslt;
    APP_ESM_GW_AUTH_INFO_STRU           stGwAuthInfo;
} APP_ESM_INQ_GW_AUTH_CNF_STRU;

/*****************************************************************************
*                                                                            *
*                                                          *
*                                                                            *
******************************************************************************/
/*****************************************************************************
 : APP_ESM_CHAP_PARAM_STRU
 : The struct contains the parameter of CHAP.
           ulChallengeLen     - Length of username
           aucChallenge       - Array of challenge
           ulChallengeNameLen - Length of challenge name
           aucChallengeName   - Array of challenge name
           ulResponseLen      - Length of response
           aucResponse        - Array of response
           ulResponseNameLen  - Length of response name (username)
           aucResponseName    - Array of response name (username)
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulChallengeLen;
    VOS_UINT8                           aucChallenge[APP_ESM_PPP_CHAP_CHALLNGE_LEN];
    VOS_UINT32                          ulChallengeNameLen;
    VOS_UINT8                           aucChallengeName[APP_ESM_PPP_CHAP_CHALLNGE_NAME_LEN];
    VOS_UINT32                          ulResponseLen;
    VOS_UINT8                           aucResponse[APP_ESM_PPP_CHAP_RESPONSE_LEN];
    VOS_UINT8                           ucResponseNameLen;
    VOS_UINT8                           aucResponseName[APP_ESM_PPP_MAX_USERNAME_LEN];

} APP_ESM_CHAP_PARAM_STRU;

/*****************************************************************************
 : APP_ESM_PAP_PARAM_STRU
 : The struct contains the parameter of PAP.
           ucUsernameLen - Length of username
           aucUsername   - Array of username
           ucPasswordLen - Length of password
           aucPassword   - Array of password
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucUsernameLen;
    VOS_UINT8                           aucUsername[APP_ESM_PPP_MAX_USERNAME_LEN];
    VOS_UINT8                           ucPasswordLen;
    VOS_UINT8                           aucPassword[APP_ESM_PPP_MAX_PASSWORD_LEN];

} APP_ESM_PAP_PARAM_STRU;

/*****************************************************************************
 : APP_ESM_AUTH_INFO_STRU
 : The struct contains the authentication information.
           enAuthType  - Auth Type (NONE/PAP/CHAP)
           stChapParam - Parameters of CHAP
           stPapParam  - Parameters of PAP
*****************************************************************************/
typedef struct
{
    APP_ESM_AUTH_TYPE_ENUM_UINT8        enAuthType;
    VOS_UINT8                           ucAuthId;
    VOS_UINT8                           aucRsv[2];
    union
    {
        APP_ESM_CHAP_PARAM_STRU         stChapParam;
        APP_ESM_PAP_PARAM_STRU          stPapParam;
    } unAuthParam;

} APP_ESM_AUTH_INFO_STRU;

/*****************************************************************************
 : APP_ESM_IPCP_INFO_STRU
 : The struct contains the IPCP information.
           aucPrimDns  - Primary DNS address
           aucSecDns   - Secondary DNS address
           aucPrimNbns - Primary NBNS address
           aucSecNbns  - Secondary NBNS address
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpIpAddr         :1;
    VOS_UINT32                          bitOpPrimDns        :1;
    VOS_UINT32                          bitOpSecDns         :1;
    VOS_UINT32                          bitOpPrimNbns       :1;
    VOS_UINT32                          bitOpSecNbns        :1;
    VOS_UINT32                          bitOpSpare          :27;

    VOS_UINT8                           aucIpAddr[APP_MAX_IPV4_ADDR_LEN];
    VOS_UINT8                           aucPrimDns[APP_MAX_IPV4_ADDR_LEN];
    VOS_UINT8                           aucSecDns[APP_MAX_IPV4_ADDR_LEN];
    VOS_UINT8                           aucPrimNbns[APP_MAX_IPV4_ADDR_LEN];
    VOS_UINT8                           aucSecNbns[APP_MAX_IPV4_ADDR_LEN];

} APP_ESM_IPCP_INFO_STRU;


/*****************************************************************************
 : APP_ESM_PPP_INFO_STRU
 : The struct contains the PPP information.
           stAuthInfo - Authentication information
           stIpcpInfo - IPCP information
*****************************************************************************/
typedef struct
{
    APP_ESM_AUTH_INFO_STRU              stAuthInfo;       /*PPP*/
    APP_ESM_IPCP_INFO_STRU              stIpcpInfo;       /*PPPIPCPESM */

} APP_ESM_PPP_INFO_STRU;
typedef struct
{
    VOS_UINT32                           ulEpsbId;
    NAS_ESM_DT_BEARER_TYPE_ENUM_UINT8    enBearerType; /**/
    VOS_UINT8                            ucRsv[3];
 	APP_ESM_APN_INFO_STRU                stApn;         /*APN */
    APP_ESM_IP_ADDR_STRU                 stIpAddr;      /*UE IP */
    APP_ESM_EPS_QOS_INFO_STRU            stSdfQosInfo;  /*QoS */
} NAS_OM_EPSB_INFO_STRU;

typedef struct
{
    VOS_UINT32                ulActEpsbNum;                /* */
    NAS_OM_EPSB_INFO_STRU     stEpsbInfo[APP_ESM_MAX_EPSB_NUM];
}NAS_OM_ACT_PDP_INFO_STRU;


typedef struct
{
    VOS_MSG_HEADER                                  /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;    /*_H2ASN_Skip*/

    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;

    DT_CMD_ENUM_UINT8                   enCmd;
    VOS_UINT8                           ucRsv[3];
    VOS_UINT32                          ulRptPeriod;
}APP_ESM_DT_INQ_CMD_REQ_STRU;

typedef   APP_ESM_DT_INQ_CMD_REQ_STRU APP_ESM_INQ_PDP_INFO_REQ_STRU;

/*V7R2-DT ,l00195322,2014/4/24, CNF IND,begin*/
typedef struct
{
    VOS_MSG_HEADER                                           /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;             /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    VOS_UINT32                          ulRslt;
} APP_ESM_INQ_PDP_INFO_CNF_STRU;
/*V7R2-DT ,l00195322,2014/4/24, CNF IND,end*/

typedef struct
{
    VOS_MSG_HEADER                                           /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;             /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;

    NAS_OM_ACT_PDP_INFO_STRU            stActPdpInfo;
} APP_ESM_INQ_PDP_INFO_IND_STRU;


/* niuxiufan DT end */

/*****************************************************************************
*                                                                            *
*                                                          *
*                                                                            *
******************************************************************************/


/*****************************************************************************
    : APP_ESM_PDP_SETUP_REQ_STRU
  : APP
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;             /**/

    APP_ESM_PDP_SETUP_TYPE_ENUM_UINT32  enSetupType;        /* PDPPPP */

    VOS_UINT32                          ulCid;              /*:0~31*/
    APP_ESM_PPP_INFO_STRU               stPppInfo;          /* PPP*/
    APP_ESM_BEARER_PRIO_ENUM_UINT32     enBearerPrio;       /* NAS signalling low priority */
}APP_ESM_PDP_SETUP_REQ_STRU;


/*****************************************************************************
     : APP_ESM_PDP_SETUP_CNF_STRU
   : 
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    VOS_UINT32                          ulCid;

    VOS_UINT32                          bitOpLinkCid         :1;
    VOS_UINT32                          bitOpBearerState     :1;
    VOS_UINT32                          bitOpBearerType      :1;
    VOS_UINT32                          bitOpPdnAddr         :1;
    VOS_UINT32                          bitOpRabId           :1;
    VOS_UINT32                          bitOpApn             :1;
    VOS_UINT32                          bitOpSdfQos          :1;
    VOS_UINT32                          bitOpDnsPrim         :1;
    VOS_UINT32                          bitOpDnsSec          :1;
    VOS_UINT32                          bitOpPCscfPrim       :1;
    VOS_UINT32                          bitOpPCscfSec        :1;
    VOS_UINT32                          bitOpGateWayAddrInfo :1;
    VOS_UINT32                          bitOpSpare           :20;

    VOS_UINT32                          ulRslt;       /*;:3.1*/
    VOS_UINT32                          ulLinkCid;
    APP_ESM_BEARER_STATE_ENUM_UINT32    enBearerState;      /*:0~1*/
    APP_ESM_BEARER_TYPE_ENUM_UINT32     enBearerType;       /**/
    APP_ESM_IP_ADDR_STRU                stPDNAddrInfo;
    APP_ESM_IP_ADDR_STRU                stSubnetMask;
    APP_ESM_IP_ADDR_STRU                stGateWayAddrInfo;  /**/
    APP_ESM_IP_ADDR_STRU                stDnsPrimAddrInfo;  /*DNS */
    APP_ESM_IP_ADDR_STRU                stDnsSecAddrInfo;   /*DNS */
    APP_ESM_IP_ADDR_STRU                stPCscfPrimAddrInfo;/*P-CSCF */
    APP_ESM_IP_ADDR_STRU                stPCscfSecAddrInfo; /* P-CSCF */
    VOS_UINT32                          ulRabId;            /*ulEpsBid*/
    APP_ESM_APN_INFO_STRU               stApnInfo;
    APP_ESM_EPS_QOS_INFO_STRU           stSdfQosInfo;

    VOS_UINT8                           ucExpiredCount;     /*  */
    VOS_UINT8                           aucReserved[3];
} APP_ESM_PDP_SETUP_CNF_STRU;


typedef APP_ESM_PDP_SETUP_CNF_STRU APP_ESM_PDP_SETUP_IND_STRU;

/*****************************************************************************
     : APP_ESM_PDP_MODIFY_REQ_STRU
   : APP
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;             /**/
    VOS_UINT32                          ulCid;              /*:0~31*/
    APP_ESM_BEARER_PRIO_ENUM_UINT32     enBearerPrio;       /* NAS signalling priority */

}APP_ESM_PDP_MODIFY_REQ_STRU;

typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    VOS_UINT32                          ulCid;
    APP_ESM_BEARER_MODIFY_ENUM_UINT32   enBearerModifyType;

    VOS_UINT32                          bitOpBearerState    :1;
    VOS_UINT32                          bitOpBearerType     :1;
    VOS_UINT32                          bitOpRabId          :1;
    VOS_UINT32                          bitOpSdfQos         :1;
    VOS_UINT32                          bitOpSpare          :28;

    VOS_UINT32                          ulRslt ;            /*;:3.1*/

    APP_ESM_BEARER_STATE_ENUM_UINT32    enBearerState;      /*:0~1*/
    APP_ESM_BEARER_TYPE_ENUM_UINT32     enBearerType;       /**/

    VOS_UINT32                          ulRabId;            /*ulEpsBid*/

    APP_ESM_EPS_QOS_INFO_STRU           stSdfQosInfo;
} APP_ESM_PDP_MODIFY_CNF_STRU;

typedef APP_ESM_PDP_MODIFY_CNF_STRU APP_ESM_PDP_MODIFY_IND_STRU;


/*****************************************************************************
     : APP_ESM_PDP_RELEASE_REQ_STRU
   : APP
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    VOS_UINT32                          ulCid;

    APP_ESM_PDP_RELEASE_CAUSE_ENUM_UINT8          enCause;       /*  */
    VOS_UINT8                                     ucDetachInd;   /* DETACHVOS_TRUEVOS_FALS */
    VOS_UINT8                                     ucRsv[2];      /*  */

}APP_ESM_PDP_RELEASE_REQ_STRU;

/*****************************************************************************
     : APP_ESM_PDP_RELEASE_CNF_STRU
   : 
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    VOS_UINT32                          ulCid;

    VOS_UINT32                          bitOpLinkCid        :1;
    VOS_UINT32                          bitOpPdnAddr        :1;
    VOS_UINT32                          bitOpSpare          :30;

    VOS_UINT32                          ulRslt;


    VOS_UINT32                          ulLinkCid;
    APP_ESM_IP_ADDR_STRU                stPDNAddrInfo;

    /* APPRELEASE IND(RELEASE CNF);    */
    VOS_UINT32                          ulEpsbId;

}APP_ESM_PDP_RELEASE_CNF_STRU;

typedef APP_ESM_PDP_RELEASE_CNF_STRU APP_ESM_PDP_RELEASE_IND_STRU;

/*****************************************************************************
     : APP_ESM_PDP_MANAGER_IND_STRU
   : APP
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                                  ulOpId;
    VOS_UINT32                                  ulCid;
    VOS_UINT32                                  bitOpLinkCid      : 1;
    VOS_UINT32                                  bitOpModifyTpye   : 1;
    VOS_UINT32                                  bitOpSpare        : 30;

    VOS_UINT32                                  ulLinkCid;
    APP_ESM_BEARER_OPERATE_TYPE_ENUM_UINT32     enOperateType;
    APP_ESM_BEARER_MODIFY_ENUM_UINT32           enBearerModifyType;

}APP_ESM_PDP_MANAGER_IND_STRU;

/*****************************************************************************
     : APP_ESM_PDP_MANAGER_RSP_STRU
   : APP
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                              ulOpId;
    VOS_UINT32                              ulCid;
    APP_ESM_BEARER_ACT_RESULT_ENUM_UINT32   ulSetupRslt;       /*:0:,1:*/


}APP_ESM_PDP_MANAGER_RSP_STRU;

/*****************************************************************************
     : APP_ESM_IPV6_PREFIX_STRU
   : APS-->ESM IPv6 Prefix
*****************************************************************************/

/* APS, IPV6*/
typedef struct
{
    VOS_UINT8                           ucPrefixLen;
    VOS_UINT8                           aucReserved[3];

    VOS_UINT8                           aucPrefix[APP_ESM_IPV6_ADDR_LEN];
}APP_ESM_IPV6_PREFIX_STRU;

/*****************************************************************************
     : APP_ESM_IPV6_INFO_NOTIFY_STRU
   : APS-->ESM IPv6 Notify
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                      /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;        /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    VOS_UINT8                           ucEpsbId;
    VOS_UINT8                           ucIpv6PrefixNum;
    VOS_UINT8                           aucReserved[2];
    APP_ESM_IPV6_PREFIX_STRU            astIpv6PrefixArray[APP_ESM_MAX_IPV6_PREFIX_NUM];
}APP_ESM_IPV6_INFO_NOTIFY_STRU;
/*niuxiufan modify begin */
/*****************************************************************************
     : APP_ESM_PROCEDURE_ABORT_NOTIFY_STRU
   : APS-->ESM 
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                      /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;        /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    VOS_UINT32                          ulCid;
}APP_ESM_PROCEDURE_ABORT_NOTIFY_STRU;
/*niuxiufan modify end */


/*****************************************************************************
     : APP_ESM_NDISCONN_REQ_STRU
   : APS-->ESM 
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                                  ulMsgId;    /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                                  ulOpId;
    VOS_UINT32                                  ulCid;

    VOS_UINT32                                  bitOpPdnType           :1;
    VOS_UINT32                                  bitOpApn               :1;
    VOS_UINT32                                  bitOpGwAuth            :1;
    VOS_UINT32                                  bitOpIpv4AddrAlloc     :1;                /* Ipv4AddrAlloc*/
    VOS_UINT32                                  bitOpPcscfDiscovery    :1;                /* P-CSCF discovery */
    VOS_UINT32                                  bitOpImCnSignalFlg     :1;                /* IM CN Signalling Flag */
    VOS_UINT32                                  bitOpSpare             :26;

    APP_ESM_APN_INFO_STRU                       stApnInfo;
    APP_ESM_PDN_TYPE_ENUM_UINT32                enPdnType;
    APP_ESM_GW_AUTH_INFO_STRU                   stGwAuthInfo;
    APP_ESM_PDN_REQUEST_TYPE_ENUM_UINT32        enPdnReqestType;
    APP_ESM_PDP_EMC_IND_ENUM_UINT32             enEmergencyInd;
    APP_ESM_IPV4_ADDR_ALLOC_TYPE_ENUM_UINT32    enIpv4AddrAlloc;
    APP_ESM_PCSCF_DISCOVERY_ENUM_UINT32         enPcscfDiscovery;
    APP_ESM_IMS_CN_SIG_FLAG_ENUM_UINT32         enImCnSignalFlg;
    APP_ESM_BEARER_PRIO_ENUM_UINT32               enBearerPrio;
} APP_ESM_NDISCONN_REQ_STRU;


/*****************************************************************************
     : APP_ESM_NDISCONN_CNF_STRU
   : APS-->ESM 
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                                  ulMsgId;            /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                                  ulOpId;
    VOS_UINT32                                  ulCid;

    VOS_UINT32                                  bitOpBearerState    :1;
    VOS_UINT32                                  bitOpBearerType     :1;
    VOS_UINT32                                  bitOpPdnAddr        :1;
    VOS_UINT32                                  bitOpRabId          :1;
    VOS_UINT32                                  bitOpApn            :1;
    VOS_UINT32                                  bitOpSdfQos         :1;
    VOS_UINT32                                  bitOpDnsPrim        :1;
    VOS_UINT32                                  bitOpDnsSec         :1;
    VOS_UINT32                                  bitOpPCscfPrim      :1;
    VOS_UINT32                                  bitOpPCscfSec       :1;
    VOS_UINT32                                  bitOpGateWayAddrInfo    :1;
    VOS_UINT32                                  bitOpSpare          :21;

    VOS_UINT32                                  ulRslt;       /*:3.1*/

    APP_ESM_BEARER_STATE_ENUM_UINT32            enBearerState;      /*:0~1*/
    APP_ESM_BEARER_TYPE_ENUM_UINT32             enBearerType;       /**/

    APP_ESM_IP_ADDR_STRU                        stPDNAddrInfo;
    APP_ESM_IP_ADDR_STRU                        stSubnetMask;
    APP_ESM_IP_ADDR_STRU                        stGateWayAddrInfo;
    APP_ESM_IP_ADDR_STRU                        stDnsPrimAddrInfo;   /*DNS*/
    APP_ESM_IP_ADDR_STRU                        stDnsSecAddrInfo;    /*DNS*/
    APP_ESM_IP_ADDR_STRU                        stPCscfPrimAddrInfo; /*P-CSCF*/
    APP_ESM_IP_ADDR_STRU                        stPCscfSecAddrInfo;  /*P-CSCF*/
    VOS_UINT32                                  ulRabId;            /*ulEpsbId*/
    APP_ESM_APN_INFO_STRU                       stApnInfo;
    APP_ESM_EPS_QOS_INFO_STRU                   stSdfQosInfo;

    VOS_UINT8                                   ucExpiredCount;     /*  */
    VOS_UINT8                                   aucReserved[3];
} APP_ESM_NDISCONN_CNF_STRU;
/*****************************************************************************
     : APP_ESM_SET_CGDCONT_REQ_STRU
   : CGDCONTAT
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                                  ulMsgId;    /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                                  ulOpId;
    VOS_UINT32                                  ulCid;

    VOS_UINT32                                  bitOpBearType          :1;
    VOS_UINT32                                  bitOpPdnType           :1;
    VOS_UINT32                                  bitOpApn               :1;

    VOS_UINT32                                  bitOpIpv4AddrAllocType :1;
    VOS_UINT32                                  bitOpPcscfDiscovery    :1;
    VOS_UINT32                                  bitOpImsCnSignalFlag   :1;
    VOS_UINT32                                  bitOpSpare             :26;


    APP_ESM_PARA_SET_ENUM_UINT32                enSetType;       /*0:SET;1:DEL*/
    APP_ESM_CID_TYPE_ENUM_UINT32                enBearCidType;
    APP_ESM_APN_INFO_STRU                       stApnInfo;
    APP_ESM_PDN_TYPE_ENUM_UINT32                enPdnType;
    APP_ESM_IPV4_ADDR_ALLOC_TYPE_ENUM_UINT32    enIpv4AddrAllocType;
    APP_ESM_PCSCF_DISCOVERY_ENUM_UINT32         enPcscfDiscovery;
    APP_ESM_IMS_CN_SIG_FLAG_ENUM_UINT32         enImsCnSignalFlag;
} APP_ESM_SET_CGDCONT_REQ_STRU;

/*****************************************************************************
     : APP_ESM_SET_CGDCONT_CNF_STRU
   : CGDCONTAT
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                                  ulMsgId;    /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                                  ulOpId;
    VOS_UINT32                                  ulCid;

    VOS_UINT32                                  ulRslt;

} APP_ESM_SET_CGDCONT_CNF_STRU;


/*****************************************************************************
     : APP_ESM_PDP_MANAGE_INFO_STRU
   : PDP
*****************************************************************************/
typedef struct
{
    APP_ESM_BEARER_MANAGE_MODE_ENUM_UINT8    enMode;         /*  */
    APP_ESM_BEARER_MANAGE_TYPE_ENUM_UINT8    enType;         /*  */
    VOS_UINT8                                aucReserve1[2]; /*  */
}APP_ESM_PDP_MANAGE_INFO_STRU;


typedef struct
{
    APP_ESM_MSG_TYPE_ENUM_UINT32        enMsgId;            /*_H2ASN_MsgChoice_Export APP_ESM_MSG_TYPE_ENUM_UINT32*/
    VOS_UINT8                           aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          APP_ESM_MSG_TYPE_ENUM_UINT32
    ****************************************************************************/
}APP_ESM_INTERFACE_MSG_DATA;
/*_H2ASN_Length UINT32*/


typedef struct
{
    VOS_MSG_HEADER
    APP_ESM_INTERFACE_MSG_DATA           stMsgData;
} AppEsmInterface_MSG;






/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
extern VOS_UINT32 APP_GetSdfPara
(
    VOS_UINT32                         *pulSdfNum,
    APP_ESM_SDF_PARA_STRU              *pstSdfPara
);
extern VOS_UINT32 APP_GetPdpManageInfo
(
    APP_ESM_PDP_MANAGE_INFO_STRU  *pstPdpManageInfo
);
extern VOS_UINT32 APP_GetCidImsSuppFlag
(
    VOS_UINT8                           ucCid,
    VOS_UINT8                          *pucImsSuppFlag
);

extern VOS_UINT32 APP_ESM_GetAttachApnInfo(
    APP_ESM_ATTACH_APN_TYPE_ENUM_UINT8  enApnType,
    APP_ESM_ATTACH_APN_INFO_STRU       *pstApnInfo
);


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

#endif /* end of AppEsmInterface.h */
