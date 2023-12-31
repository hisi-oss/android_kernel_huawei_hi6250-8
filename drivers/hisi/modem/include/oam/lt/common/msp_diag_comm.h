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


#ifndef __MSP_DIAG_COMM_H__
#define __MSP_DIAG_COMM_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include "vos.h"
#include "mdrv.h"

/**************************************************************************
  
**************************************************************************/

/*PSMODID DIAG_AIR_MSG_LOG_IDDIAG_ID*/
#define DIAG_ID(module_id, log_type)   (VOS_UINT32)(module_id | (log_type << 12))

#define DIAG_AIR_MSG_LOG_ID(module_id, is_up_link)  DIAG_ID(module_id, is_up_link) /*module_idPID*/

#define DIAG_GEN_LOG_MODULE(modemid, modetype, level)  \
               (((VOS_UINT32)(modemid & 0xff) << 24)  \
              | ((VOS_UINT32)(modetype & 0xf) << 16)  \
              | ((VOS_UINT32)(level    & 0xf ) << 12))

#define DIAG_GEN_MODULE(modemid, modetype)  \
               (((VOS_UINT32)(modemid & 0xff) << 24)  \
              | ((VOS_UINT32)(modetype & 0xf) << 16))


#define DIAG_GEN_MODULE_EX(modemid, modetype, groupid)  \
                   (((VOS_UINT32)(modemid & 0xff) << 24)  \
                  | ((VOS_UINT32)(modetype & 0xf) << 16) \
                  | ((VOS_UINT32)(groupid  & 0xf)  << 8))

#define DIAG_GEN_LOG_ID(filenum, linenum)   \
                ((((VOS_UINT32)(filenum & 0XFFFF)) << 16)   \
                | ((VOS_UINT32)(linenum & 0XFFFF)))

/*is_up_link*/
#define OS_MSG_UL                (0x01)/* */
#define OS_MSG_DL                (0x02)/* */


#define DIAG_SIDE_UE             (0x1)  /* UENET-->UE*/
#define DIAG_SIDE_NET            (0x2)  /* NETUE-->NET*/

/* */
#define DIAG_LOG_TYPE_INFO            0x00000008UL
#define DIAG_LOG_TYPE_AUDIT_FAILURE   0x00000004UL
#define DIAG_LOG_TYPE_AUDIT_SUCCESS   0x00000002UL
#define DIAG_LOG_TYPE_ERROR           0x00000001UL
#define DIAG_LOG_TYPE_WARNING         0x00000010UL

/*diag_message_id.h,*/
#define ID_MSG_DIAG_HSO_DISCONN_IND                 (0x00010004)
#define ID_MSG_DIAG_CHR_REQ                         (0x00010010)

/*diag AGENTPSHSO*/
#define ID_MSG_DIAG_CMD_REPLAY_TO_PS    			(0x00010100)

/*  DIAG_MESSAGE_TYPE_U32  */

/* 2000 - 2fffPS */

/* TTFTTFTTFCPU */
#define     DIAG_TTF_TRACECFG_REQ                   (0x00002201)    /* TTF */
#define     DIAG_TTF_DISCONN_REQ                    (0x00002203)    /* TTF */


/* 3000 - 3fffPHY */
#define     DIAG_GUPHY_RELEASE_REQ                  (0x00003201)    /* API */


/* c000 - cfffHIFI */
#define     DIAG_HIFI_RELEASE_REQ                   (0x0000c001)


/* HIFIID */
#define     ID_HIFI_DIAG_CONNECT_CNF                (0x492A)
#define     ID_HIFI_DIAG_DISCONNECT_CNF             (0x492B)


/*****************************************************************************
  4 Enum
*****************************************************************************/

/* ================================================== */

/* DIAG_SERVICE_HEAD_STRU:ssid4b */
enum DIAG_SSID_TYPE
{
    DIAG_SSID_APP_CPU   = 0x1,
    DIAG_SSID_MODEM_CPU,
    DIAG_SSID_LTE_DSP,
    DIAG_SSID_LTE_BBP,
    DIAG_SSID_GU_DSP,
    DIAG_SSID_HIFI,
    DIAG_SSID_TDS_DSP,
    DIAG_SSID_TDS_BBP,
    DIAG_SSID_MCU,
    DIAG_SSID_GPU,
    DIAG_SSID_GU_BBP,
    DIAG_SSID_IOM3,
    DIAG_SSID_ISP,
    DIAG_SSID_X_DSP,
    DIAG_SSID_BUTT
};
typedef VOS_UINT32 DIAG_SSID_TYPE_U32;


/* DIAG_SERVICE_HEAD_STRU:sessionid8b */
#define MSP_SERVICE_SESSION_ID        (0x1) /* ServiceClient,1*/

/* DIAG_SERVICE_HEAD_STRU:mt2b */
enum DIAG_MSGTYPE_TYPE
{
    DIAG_MT_RSV   = 0x0,
    DIAG_MT_REQ   = 0x1,
    DIAG_MT_CNF   = 0x2,
    DIAG_MT_IND   = 0x3
};
typedef VOS_UINT32 DIAG_DIRECTION_TYPE_U32;

/* ======================================================================== */


/* ================================================== */

/* MSP_DIAG_STID_STRU:pri4b */
enum DIAG_MESSAGE_TYPE
{
    DIAG_MSG_TYPE_RSV   = 0x0,
    DIAG_MSG_TYPE_MSP   = 0x1,
    DIAG_MSG_TYPE_PS    = 0x2,
    DIAG_MSG_TYPE_PHY   = 0x3,
    DIAG_MSG_TYPE_BBP   = 0x4,
    DIAG_MSG_TYPE_HSO   = 0x5,
    DIAG_MSG_TYPE_BSP   = 0x9,
    DIAG_MSG_TYPE_ISP   = 0xa,
    DIAG_MSG_TYPE_AUDIO = 0xc,
    DIAG_MSG_TYPE_APP   = 0xe,
    DIAG_MSG_TYPE_BUTT
};
typedef VOS_UINT32 DIAG_MESSAGE_TYPE_U32;

/* MSP_DIAG_STID_STRU:mode4b */
enum DIAG_MODE_TYPE
{
    DIAG_MODE_LTE  = 0x0,
    DIAG_MODE_TDS  = 0x1,
    DIAG_MODE_GSM  = 0x2,
    DIAG_MODE_UMTS = 0x3,
    DIAG_MODE_1X   = 0x4,
    DIAG_MODE_HRPD = 0x5,
    DIAG_MODE_COMM = 0xf
};
typedef VOS_UINT32 DIAG_MODE_TYPE_U32;

/* MSP_DIAG_STID_STRU:pri4b */
enum DIAG_MSG_SUB_TYPE_TYPE
{
    DIAG_MSG_CMD        = 0x0,
    DIAG_MSG_PS_AIR     = 0x1,
    DIAG_MSG_PS_LAYER   = 0x2,
    DIAG_MSG_PS_PRINT   = 0x3,
    DIAG_MSG_PS_EVENT   = 0x4,
    DIAG_MSG_PS_USER    = 0x5,
    DIAG_MSG_PS_VOLTE   = 0x6,
    DIAG_MSG_PS_STRUCT  = 0x7,
    DIAG_MSG_PS_DOT     = 0x8,
    DIAG_MSG_DSP_PRINT  = 0x9,
    DIAG_MSG_RAE_CNF    = 0xa,
    DIAG_MSG_RAE_IND    = 0xb,
    DIAG_MSG_STAT       = 0x1f
};
typedef VOS_UINT32 DIAG_MSG_SUB_TYPE_U32;


enum DIAG_MODEM_ID
{
    DIAG_MODEM_0 = 0x0,
    DIAG_MODEM_1 = 0x1,
    DIAG_MODEM_2 = 0x2
};
typedef unsigned int DIAG_MODEM_ID_U32;


/* DIAG_SERVICE_HEAD_STRU:sid8b */
enum DIAG_SID_TYPE
{
    MSP_SID_DEFAULT   = 0x0,
    MSP_SID_AT_SERVICE,
    MSP_SID_DIAG_SERVICE,
    MSP_SID_DATA_SERVICE,
    MSP_SID_NV_SERVICE,
    MSP_SID_USIM_SERVICE,
    MSP_SID_DM_SERVICE,
    MSP_SID_CBT_SERVICE,
    MSP_SID_BUTT
};

typedef unsigned int MSP_SID_TYPE_U32;

typedef enum
{
    PS_LOG_LEVEL_OFF  = 0,
    PS_LOG_LEVEL_ERROR,
    PS_LOG_LEVEL_WARNING,
    PS_LOG_LEVEL_NORMAL,
    PS_LOG_LEVEL_INFO,
    PS_LOG_LEVEL_BUTT
}PS_LOG_LEVEL_EN;

/**************************************************************************
  5 
**************************************************************************/

/* ============================================================== */

/*  :: service */
typedef struct
{
    VOS_UINT32    sid8b       :8;
    VOS_UINT32    mdmid3b     :3;
    VOS_UINT32    rsv1b       :1;
    VOS_UINT32    ssid4b      :4;
    VOS_UINT32    sessionid8b :8;
    VOS_UINT32    mt2b        :2;
    VOS_UINT32    index4b     :4;
    VOS_UINT32    eof1b       :1;
    VOS_UINT32    ff1b        :1;

    VOS_UINT32    ulMsgTransId;
    VOS_UINT8     aucTimeStamp[8];
}DIAG_SERVICE_HEAD_STRU;


/*  :: DIAG */
typedef struct
{
    VOS_UINT32    cmdid19b:19;
    VOS_UINT32    sec5b   :5;
    VOS_UINT32    mode4b  :4;
    VOS_UINT32    pri4b   :4;
} MSP_DIAG_STID_STRU;

typedef struct
{
    union
    {
        VOS_UINT32          ulID;           /* ID */
        MSP_DIAG_STID_STRU  stID;
    };

    VOS_UINT32          ulDataSize;     /* ucData */
    VOS_UINT8           aucData[0];
}DIAG_MSG_INFO_STRU;

/*  :: REQ/CNF */
typedef struct
{
    VOS_UINT32 ulAuid;         /* AUID*/
    VOS_UINT32 ulSn;           /* HSO*/
    VOS_UINT8  ucData[0];      /* */
} MSP_DIAG_DATA_REQ_STRU;

typedef MSP_DIAG_DATA_REQ_STRU MSP_DIAG_DATA_CNF_STRU;


/*  : */
typedef struct
{
    DIAG_SERVICE_HEAD_STRU      stService;

    union
    {
        VOS_UINT32          ulCmdId;           /* ID */
        MSP_DIAG_STID_STRU  stID;
    };

    VOS_UINT32                  ulMsgLen;
#if (VOS_OS_VER == VOS_WIN32)
    VOS_UINT8                   aucData[4];
#else
    VOS_UINT8                   aucData[0];
#endif

}DIAG_FRAME_INFO_STRU;


/*  */
typedef struct
{
    DIAG_SSID_TYPE_U32          ulSSId;         /* CPU ID */
    DIAG_MESSAGE_TYPE_U32       ulMsgType;      /*  */
    DIAG_MODE_TYPE_U32          ulMode;         /*  */
    DIAG_MSG_SUB_TYPE_U32       ulSubType;      /* DIAG_MSG_SUB_TYPE_U32 */
    DIAG_DIRECTION_TYPE_U32     ulDirection;    /*  */
    VOS_UINT32                  ulModemid;
    VOS_UINT32                  ulMsgId;        /* 16 */
    VOS_UINT32                  ulTransId;      /* TransId */
} MSP_DIAG_CNF_INFO_STRU;

/* ======================================================================== */


typedef struct
{
    VOS_UINT32 ulId;
    VOS_UINT32 ulMessageID;  /* Specify the message id.*/
    VOS_UINT32 ulSideId;     /* */
    VOS_UINT32 ulDestMod;    /* */
    VOS_UINT32 ulDataSize;   /* the data size in bytes.*/
    VOS_VOID* pData;      /* Pointer to the data buffer.*/
} DIAG_AIR_MSG_LOG_STRU;

typedef DIAG_AIR_MSG_LOG_STRU DIAG_LAYER_MSG_STRU;

typedef struct
{
    VOS_UINT32 ulMessageID;    /* Specify the message id.*/
    VOS_UINT32 ulDataSize;     /* the data size in bytes.*/
    VOS_VOID* pData;        /* Pointer to the data buffer.*/
} DIAG_USERPLANE_MSG_STRU;

#if(FEATURE_SOCP_ON_DEMAND == FEATURE_ON)
/* MSP_PID_DIAG_APP_AGENT */
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32              ulMsgId;
    SOCP_VOTE_ID_ENUM_U32   ulVoteId;    /*  */
    SOCP_VOTE_TYPE_ENUM_U32 ulVoteType;  /*  */
}DIAG_MSG_SOCP_VOTE_REQ_STRU;

/*  */
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32              ulMsgId;
    SOCP_VOTE_ID_ENUM_U32   ulVoteId;    /*  */
    SOCP_VOTE_TYPE_ENUM_U32 ulVoteType;  /*  */
    VOS_UINT32              ulVoteRst;   /* 0-, 0xFFFFFFFF- */
}DIAG_MSG_SOCP_VOTE_WAKE_CNF_STRU;
#endif


/* servicebuffer */
typedef struct
{
    DIAG_SERVICE_HEAD_STRU      *pHeadService;
    DIAG_MSG_INFO_STRU          *pHeadMessage;
    VOS_VOID                    *pData;
    VOS_UINT32                  ulSize;         /*  */
    VOS_UINT32                  ulLength;       /*  */
}DIAG_SERVICE_REPORT_STRU;



/*****************************************************************************
 : TTF(TTF)
MSGID:DIAG_TTF_LAYERCFG_REQ
REQ : DIAG_TTF_TRACECFG_REQ_STRU()
*****************************************************************************/

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                  ulMsgId;

    VOS_UINT8                   aucSrcPid[VOS_PID_BUTT-VOS_PID_DOPRAEND];
    VOS_UINT8                   aucDstPid[VOS_PID_BUTT-VOS_PID_DOPRAEND];
}DIAG_TTF_TRACECFG_REQ_STRU;


/*****************************************************************************
    : OM_AT_MSG_ENUM
  : ATOM

  1.       : 201244
           : h59254
       : V7R1C51 
*****************************************************************************/
enum OM_AT_MSG_ENUM
{
    AT_OM_PORT_SWITCH           = 0,    /* OMUSBHSIC */
    AT_OM_HSIC_PORT_CONNECT,            /* OMOMHSIC */
    AT_OM_HSIC_PORT_DISCONNECT,         /* OMOMHSIC */
    AT_OM_MSG_BUTT
};
typedef VOS_UINT32 OM_AT_MSG_ENUM_UINT32;

/*****************************************************************************
    : OM_PORT_SWITCH_MODE_ENUM
  : USB SWITCH

  1.       : 201244
           : h59254
       : V7R1C51 
*****************************************************************************/
enum OM_PORT_SWITCH_MODE_ENUM
{
    OM_PORT_SWITCH_MODEM2AP     = USB_SWITCH_OFF,
    OM_PORT_SWITCH_AP2MODEM     = USB_SWITCH_ON,
    OM_PORT_SWITCH_BUTT
};
typedef VOS_UINT32 OM_PORT_SWITCH_MODE_ENUM_UINT32;

/*****************************************************************************
    : OM_PORT_SWITCH_MSG_STRU
  : AP+MODEMAP-Modem USB

  1.       : 2012410
           : h59254
       : 
*****************************************************************************/
typedef struct
{
   VOS_MSG_HEADER
   OM_AT_MSG_ENUM_UINT32            ulMsgName;      /**/
   OM_PORT_SWITCH_MODE_ENUM_UINT32  ulSwitchMode;   /*APModemModemAP*/
}OM_PORT_SWITCH_MSG_STRU;

/*****************************************************************************
    : OM_HSIC_CONNECT_MSG_STRU
  : AP+MODEMATOMHSIC

  1.       : 2012410
           : h59254
       : 
*****************************************************************************/
typedef struct
{
   VOS_MSG_HEADER
   OM_AT_MSG_ENUM_UINT32            ulMsgName;      /**/
}OM_HSIC_CONNECT_MSG_STRU;

/**************************************************************************
  
**************************************************************************/


/* ======================================================== */

typedef struct
{
    VOS_UINT32        ulModule;		/* DIAG_GEN_MODULE*/
    VOS_UINT32        ulPid;
    VOS_UINT32        ulEventId;		/* ID */
    VOS_UINT32        ulLength;
    VOS_VOID          *pData;
}DIAG_EVENT_IND_STRU;

typedef struct
{
    VOS_UINT32        ulModule;       /* DIAG_GEN_MODULE*/
    VOS_UINT32        ulPid;
    VOS_UINT32        ulMsgId;
    VOS_UINT32        ulDirection;
    VOS_UINT32        ulLength;
    VOS_VOID          *pData;
}DIAG_AIR_IND_STRU;

typedef struct
{
    VOS_UINT32        ulModule;       /* DIAG_GEN_MODULE*/
    VOS_UINT32        ulPid;
    VOS_UINT32        ulMsgId;
    VOS_UINT32        ulLength;
    VOS_VOID          *pData;
}DIAG_USER_IND_STRU;


typedef struct
{
    VOS_UINT32        ulId;
    VOS_UINT32        ulMessageID;
    VOS_UINT32        ulSideId;
    VOS_UINT32        ulDestMod;
    VOS_UINT32        ulDataSize;
    VOS_VOID          *pData;
} DIAG_VOLTE_LOG_STRU;

typedef struct
{
    VOS_UINT32        ulModule;
    VOS_UINT32        ulPid;
    VOS_UINT32        ulMsgId;
    VOS_UINT32        ulReserve;
    VOS_UINT32        ulLength;
    VOS_VOID          *pData;
} DIAG_TRANS_IND_STRU;

/* OSA: 0-,; -, */
typedef VOS_UINT32 (*DIAG_TraceFilterFunc)(const VOS_VOID *pMsg);


/*****************************************************************************
 Function Name   : DIAG_TraceFilterFuncReg
 Description     : ()
 Input           : 
 Output          : None
 Return          : : 0--

 History         :
    1.c64416      2012-11-20  Draft Enact

*****************************************************************************/
VOS_UINT32 DIAG_TraceFilterFuncReg(DIAG_TraceFilterFunc pFun);

/* OSA */
typedef VOS_VOID* (*DIAG_TraceMatchFunc)(VOS_VOID *pMsg);

/*****************************************************************************
 Function Name   : DIAG_TraceMatchFuncReg
 Description     : ()
 Input           : 
 Output          : None
 Return          : : 0--

 History         :
    1.c64416      2012-11-20  Draft Enact

*****************************************************************************/
VOS_UINT32 DIAG_TraceMatchFuncReg(DIAG_TraceMatchFunc pFun);


/*****************************************************************************
     : DIAG_TransReport
   : (DIAG_ReportCommand)
   : DIAG_TRANS_IND_STRU->ulModule( 31-24:modemid,23-16:modeid,15-12:level,11-0:pid )
             DIAG_TRANS_IND_STRU->ulMsgId(ID)
             DIAG_TRANS_IND_STRU->ulLength()
             DIAG_TRANS_IND_STRU->pData()
*****************************************************************************/
VOS_UINT32 DIAG_TransReport(DIAG_TRANS_IND_STRU *pstData);

/*****************************************************************************
     : DIAG_TransReport_Ex
   : (DIAG_TransReport11-8bits )
   : DIAG_TRANS_IND_STRU->ulModule( 31-24:modemid,23-16:modeid,15-12:level,11-8:groupid )
   : DIAG_TRANS_IND_STRU->ulPid(PID)
             DIAG_TRANS_IND_STRU->ulMsgId(ID)
             DIAG_TRANS_IND_STRU->ulLength()
             DIAG_TRANS_IND_STRU->pData()
*****************************************************************************/
VOS_UINT32 DIAG_TransReport_Ex(DIAG_TRANS_IND_STRU *pstData);

/*****************************************************************************
     : DIAG_LogReport
   : 
   : ulModuleId( 31-24:modemid,23-16:modeid,15-12:level )
             ulPid( PID )
             pcFileName()
             ulLineNum()
             pszFmt()
   : 1K
             1K
                                           log1K
*****************************************************************************/
VOS_UINT32 DIAG_LogReport(VOS_UINT32 ulModuleId, VOS_UINT32 ulPid, VOS_CHAR *cFileName, VOS_UINT32 ulLineNum, VOS_CHAR* pszFmt, ...);


#define LTE_DIAG_PRINTF_PARAM_MAX_NUM       (6)
/******************************************************************************
: DIAG_LogIdReport
: 
:
            ulModuleId[in]  : ( 31-24:modemid,23-16:modeid,15-12:level )
            ulPid[in]       : PID
            ulLogId[in]     : DIAG_LOG_ID
            amount[in]      : ulModuleId/ulLevel/ulLogId/amout
            ...             : 
:
            1. 
            2. amount
            3. int
            4. 6
******************************************************************************/
VOS_INT32 DIAG_LogIdReport(VOS_UINT32 ulModuleId, VOS_UINT32 ulPid,
                        VOS_UINT32 ulLogId, VOS_UINT32 amount, ...);

/*****************************************************************************
     : DIAG_EventReport
   : PS(DIAG_ReportEventLog)
   : DIAG_EVENT_IND_STRU->ulModule( 31-24:modemid,23-16:modeid,15-12:level,11-0:pid )
             DIAG_EVENT_IND_STRU->ulEventId(event ID)
             DIAG_EVENT_IND_STRU->ulLength(event)
             DIAG_EVENT_IND_STRU->pData(event)
*****************************************************************************/
VOS_UINT32 DIAG_EventReport(DIAG_EVENT_IND_STRU *pstEvent);

/*****************************************************************************
     : DIAG_AirMsgReport
   : PS(DIAG_ReportAirMessageLog)
   : DIAG_AIR_IND_STRU->ulModule( 31-24:modemid,23-16:modeid,15-12:level,11-0:pid )
             DIAG_AIR_IND_STRU->ulMsgId(ID)
             DIAG_AIR_IND_STRU->ulDirection()
             DIAG_AIR_IND_STRU->ulLength()
             DIAG_AIR_IND_STRU->pData()
*****************************************************************************/
VOS_UINT32 DIAG_AirMsgReport(DIAG_AIR_IND_STRU *pstAir);


/*****************************************************************************
     : DIAG_TraceReport
   : PS(DIAG_ReportLayerMessageLog)
   : pMsg(VOS)

*****************************************************************************/
extern VOS_VOID DIAG_TraceReport(VOS_VOID *pMsg);

/*****************************************************************************
     : DIAG_UserPlaneReport
   : PS(DIAG_ReportUserPlaneMessageLog)
   : DIAG_USER_IND_STRU->ulModule( 31-24:modemid,23-16:modeid,15-12:level,11-0:pid )
             DIAG_USER_IND_STRU->ulMsgId(ID)
             DIAG_USER_IND_STRU->ulLength()
             DIAG_USER_IND_STRU->pData()
*****************************************************************************/
VOS_UINT32 DIAG_UserPlaneReport(DIAG_USER_IND_STRU *pstUser);

/*****************************************************************************
 Function Name   : DIAG_ReportVoLTELog
 Description     : IMSVOLTE
 Input           : DIAG_VoLTE_LOG_STRU* pRptMessage
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.fuxin      2013-12-30  create
*****************************************************************************/
VOS_UINT32 DIAG_ReportVoLTELog(DIAG_VOLTE_LOG_STRU* pRptMessage);

/*****************************************************************************
 Function Name   : DIAG_GetConnState
 Description     : 
 Return          : 1:connect; 0:disconnect

 History         :
    1.c00326366      2015-6-24  Draft Enact
*****************************************************************************/
VOS_UINT32 DIAG_GetConnState(VOS_VOID);


/*****************************************************************************
  
*****************************************************************************/
extern VOS_UINT32 DIAG_ErrorLog(VOS_CHAR * cFileName,VOS_UINT32 ulFileId, VOS_UINT32 ulLine,
                VOS_UINT32 ulErrNo, VOS_VOID * pBuf, VOS_UINT32 ulLen);

#define MNTN_RecordErrorLog(ulErrNo,pBuf,ulLen) \
    DIAG_ErrorLog(__FILE__,THIS_FILE_ID,__LINE__,ulErrNo,pBuf,ulLen)


/*****************************************************************************
     : Log_GetPrintLevel
   : IdId
 return    : PS_LOG_LEVEL_EN
 History         :
    1.c00326366      2015-6-24  Draft Enact
*****************************************************************************/
extern VOS_UINT32 Diag_GetLogLevel(VOS_UINT32 ulPid);


#if(VOS_OS_VER == VOS_LINUX)
/*****************************************************************************
 Function Name   : DIAG_LogShowToFile
 Description     : ATDIAGlog
 Input           : bIsSendMsg AAlog
 Return          : VOS_VOID

 History         :
    1.c00326366      2015-6-20  Draft Enact
*****************************************************************************/
extern VOS_VOID DIAG_LogShowToFile(VOS_BOOL bIsSendMsg);
#endif

#ifdef __cplusplus
}
#endif
#endif

