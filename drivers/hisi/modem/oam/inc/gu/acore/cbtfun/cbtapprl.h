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

/******************************************************************************

                   (C), 2015-2025, 

 ******************************************************************************
       : Cbtapprl.h
       : 
         : x00263027
     : 201532
     :
     : Cbtapprl.h 
     :
     :
  1.       : 201532
           : x00263027
       : 

******************************************************************************/

#ifndef __CBT_APPRL_H__
#define __CBT_APPRL_H__

/*****************************************************************************
  1 
*****************************************************************************/
#include "cbtrl.h"


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif





extern VOS_UINT32                       g_ulCbtAcpuDbgFlag;


/*****************************************************************************
  2 
*****************************************************************************/
#define CBT_MSG_FIRST_BYTE                  (0x07)
#define BIT_LEFTMOVE_N(num)                 (0x01 <<( num))
#define CBT_ACPU_VCOM_CB                    BIT_LEFTMOVE_N(0)
#define CBT_ACPU_DISPATCH_MSG               BIT_LEFTMOVE_N(1)
#define CBT_ACPU_USB_CB                     BIT_LEFTMOVE_N(2)
/* datatype  */
#define CBT_RL_DATATYPE_LEN                 (0x1)
#define CBT_HDLC_FCS_LEN                    (2)           /* HDLCFCS(: Byte) */
#define CBT_HDLC_BUF_MAX_LEN                (CBT_MSG_SEGMENT_LEN + CBT_RL_DATATYPE_LEN + CBT_HDLC_FCS_LEN)

/*CBT_READ_NV_IND_STRUsizeof(ulErrorCode) + sizeof(ulNvId) + sizeof(ulCount)*/
#define CBT_READ_NV_HEAD_SIZE               (12)
#define CBT_WRITE_NV_HEAD_SIZE              (8)
/*NVID+NVID*/
#define CBT_NV_ITEM_SIZE                    (4)
#define CBT_IND_RESULT_SIZE                 (4)
#define CBT_EST_IND_CHIP_ID_SIZE            (4)
#define CBT_EST_IND_RSV_LEN                 (252)


#define CBT_END_FRAME                       (1)
/*#define SEG_MAX_LEN                         (4*1024)*/
/*#define MAXSEGMENT                          (16)*/
/**/
#define CBT_TOTAL_MSG_MAX_LEN               (20*1024)/*(SEG_MAX_LEN + (SEG_MAX_LEN-CBT_MSG_HEADER_LENGTH)*(MAXSEGMENT-1))*/

#define OM_CBT_SEND_DATA_REQ                (0x030d)



#define CBT_ACPU_DEBUG_TRACE(pucData, ulDataLen, ulSwitch) \
    if(VOS_FALSE != (g_ulCbtAcpuDbgFlag&ulSwitch)) \
    { \
        VOS_UINT32 ulOmDbgIndex; \
        (VOS_VOID)vos_printf("\n%s, Data Len: = %d\n", __FUNCTION__, ulDataLen); \
        for (ulOmDbgIndex = 0 ; ulOmDbgIndex < ulDataLen; ulOmDbgIndex++) \
        { \
            (VOS_VOID)vos_printf("%02x ", *((VOS_UINT8*)pucData + ulOmDbgIndex)); \
        } \
        (VOS_VOID)vos_printf("\r\n"); \
    } \


/*OM<->APP : Restablish link*/
#define APP_OM_ESTABLISH_REQ                      0x80b1
#define OM_APP_ESTABLISH_CNF                      0x80b2

/*OM<->APP : Release link*/
#define APP_OM_RELEASE_REQ                        0x80b3
#define OM_APP_RELEASE_CNF                        0x80b4

#define APP_OM_READ_NV_REQ                        0x8021

#define OM_APP_READ_NV_IND                        0x8022

#define APP_OM_WRITE_NV_REQ                       0x8023
#define OM_APP_WRITE_NV_CNF                       0x8024

#define APP_OM_NV_BACKUP_REQ                      0x8025
#define OM_APP_NV_BACKUP_CNF                      0x8026


/*****************************************************************************
  6 STRUCT
*****************************************************************************/

typedef struct
{
    VOS_UINT32 ulResult;                            /**/
    VOS_UINT32 ulChipId;
    VOS_UINT8  ausReserve[CBT_EST_IND_RSV_LEN];
}CBT_ESTABLISH_IND_STRU;

typedef struct
{
    VOS_UINT32 ulCount;             /*NV*/
    VOS_UINT16 ausNvItemId[2];      /*NVIDulCount*/
}CBT_READ_NV_REQ_STRU;

typedef struct
{
    VOS_UINT32 ulErrorCode;        /**/
    VOS_UINT32 ulErrNvId;          /*NVID*/
    VOS_UINT32 ulCount;            /*NV*/
    VOS_UINT16 ausNVItemData[2];   /*NVIDNVIDNVID*/
}CBT_READ_NV_IND_STRU;

typedef struct
{
    CBT_MSG_HEAD_STRU           stMsgHead;
    VOS_UINT16                  usMsgId;      /* ID */
    CBT_COMPONENT_MODE_STRU     stCompMode;
    VOS_UINT32                  ulMsgLength;

    VOS_UINT32                  ulErrorCode;        /**/
    VOS_UINT32                  ulErrNvId;          /*NVID*/
    VOS_UINT32                  ulCount;            /*NV*/
}CBT_READ_NV_CNF_STRU;

typedef struct
{
    VOS_UINT32 ulCount;             /*NV*/
    VOS_UINT16 ausNvItemData[2];    /*NVIDNVIDNVID*/
}CBT_WRITE_NV_REQ_STRU;

typedef struct
{
    CBT_MSG_HEAD_STRU           stMsgHead;
    VOS_UINT16                  usMsgId;      /* ID */
    CBT_COMPONENT_MODE_STRU     stCompMode;
    VOS_UINT32                  ulMsgLength;

    VOS_UINT32                  ulErrorCode;        /**/
    VOS_UINT32                  ulErrNvId;          /*NVID*/
}CBT_WRITE_NV_CNF_STRU;

/*****************************************************************************
    : OMRL_CBT_HDLC_ENCODE_MEM_CTRL
  : OMRL CBTHDLC(uncache)
*****************************************************************************/
typedef struct
{
    VOS_UINT8                          *pucBuf;         /*  */
    VOS_UINT8                          *pucRealBuf;     /*  */
    VOS_UINT32                          ulBufSize;      /*  */
    VOS_UINT32                          ulRsv;          /* Reserve */
}CBT_HDLC_ENCODE_MEM_CTRL;

/*****************************************************************************
    : OM_ACPU_ICC_SEND_FAIL_STRU
  : ACPU ICC
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulICCOmSendErrNum;      /**/
    VOS_UINT32                          ulICCOmSendErrLen;      /**/
    VOS_UINT32                          ulICCOmSendErrSlice;    /**/
}CBT_ACPU_ICC_SEND_FAIL_STRU;

/*****************************************************************************
    : OM_ACPU_ICC_SEND_SUC_STRU
  : ACPU ICC
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulICCOmSendMsgNum;      /**/
    VOS_UINT32                          ulICCOmSendLen;         /**/
    VOS_UINT32                          ulICCOmSendSlice;       /**/
}CBT_ACPU_ICC_SEND_SUC_STRU;

/*****************************************************************************
    : OM_MAINTENANCE_INFO_STRU
  : OM
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulDataLen; /*  */
    VOS_UINT32                          ulNum;     /*  */
}CBT_MAINTENANCE_INFO_STRU;

/*****************************************************************************
    : OM_ACPU_PC_UE_RELEASE_INFO_STRU
  : OM
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulRlsAp2Modem;     /* APModem */
    VOS_UINT32                          ulRlsModem2Ap;     /* ModemAP */
    VOS_UINT32                          ulRlsDrvSuspend;   /* DRV */
    VOS_UINT32                          ulRlsPortClose;    /*  */
    VOS_UINT32                          ulRlsPortSwitch;   /*  */
    VOS_UINT32                          ulSlice;           /*  */
}CBT_ACPU_PC_UE_RELEASE_INFO_STRU;

/*****************************************************************************
    : CBT_ACPU_PC_UE_FAIL_STRU
  : CBT
*****************************************************************************/
typedef struct
{
    CBT_MAINTENANCE_INFO_STRU           stLostData;         /*  */
    VOS_UINT32                          ulFrameDecapErr;    /*  */

    VOS_UINT16                          usPacketLenErr;     /* OM_USB_FRAME_LEN */
    VOS_UINT16                          usLenTooShortErr;   /*  */
    VOS_UINT16                          usSegLenErr;        /*  */
    VOS_UINT16                          usSegNumErr;        /*  */

    VOS_UINT16                          usDatatypeErr;      /* datatype */
    VOS_UINT16                          usMsgTooLongErr;    /* 8K */
    VOS_UINT16                          usCpuIdErr;         /* CPU id */
    VOS_UINT16                          usNoMemErr;         /*  */

    VOS_UINT16                          usDataHeadErr;      /*  */
    VOS_UINT16                          usMsgLenErr;        /*  */
    VOS_UINT16                          usMsgSnErr;         /*  */
    VOS_UINT16                          usTransIdErr;       /* TransId  */
    VOS_UINT16                          usPacketLostErr;    /*  */
    VOS_UINT16                          usTimeStampErr;     /*  */

    VOS_UINT16                          usLinkDataLenErr;   /*  */
    VOS_UINT16                          usLinkStatusErr;    /*  */
    VOS_UINT16                          usAllocMsg;         /*  */
    VOS_UINT16                          usRcv;

    CBT_ACPU_ICC_SEND_FAIL_STRU          stICCSendFailInfo;  /* ACPUICC */
}CBT_ACPU_PC_UE_FAIL_STRU;

/*****************************************************************************
    : CBT_ACPU_PC_UE_SUC_STRU
  : CBT
*****************************************************************************/
typedef struct
{
    CBT_MAINTENANCE_INFO_STRU            stTotalData;       /*  */
    CBT_MAINTENANCE_INFO_STRU            stHdlcDecapData;
    CBT_MAINTENANCE_INFO_STRU            stLinkData;        /*  */
    CBT_MAINTENANCE_INFO_STRU            stCcpuData;        /* CCPU */
    CBT_MAINTENANCE_INFO_STRU            stAcpuData;        /* ACPU */
    CBT_ACPU_ICC_SEND_SUC_STRU           stICCSendSUCInfo;  /* ACPUICC */
    CBT_MAINTENANCE_INFO_STRU            stRlsData;         /* Release */
    CBT_ACPU_PC_UE_RELEASE_INFO_STRU     stRlsInfo;         /* Release */
}CBT_ACPU_PC_UE_SUC_STRU;

/*****************************************************************************
    : CBTRL_MSG_COMBINE_INFO_STRU
  : CBTRL
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucTotalSegNum;      /*  */
    VOS_UINT8                           ucExpectedSegSn;    /*  */
    VOS_UINT16                          usRsv;

    VOS_UINT32                          ulTransId;
    VOS_UINT32                          ulTimeStampL;
    VOS_UINT16                          usTimeStampH;
    VOS_UINT16                          usRsv2;

    VOS_UINT32                          ulTotalMsgLen;      /*  */
    VOS_UINT32                          ulMoveLen;          /*  */
    MsgBlock *                          pstWholeMsg;        /**/
}CBT_MSG_COMBINE_INFO_STRU;

/*****************************************************************************
    : CBTRL_RCV_CHAN_CTRL_INFO_STRU
  : CBTRL
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulCbtSwitchOnOff;
    CBT_MSG_COMBINE_INFO_STRU           stMsgCombineInfo;

    CBT_ACPU_PC_UE_FAIL_STRU            stPcToUeErrRecord;
    CBT_ACPU_PC_UE_SUC_STRU             stPcToUeSucRecord;
}CBT_RCV_CHAN_CTRL_INFO_STRU;


/*****************************************************************************
  
*****************************************************************************/
VOS_UINT32 CBT_AcpuInit(VOS_VOID);
VOS_UINT32 CBT_AcpuSendData(CBT_UNIFORM_MSG_STRU * pstMsg, VOS_UINT16 usMsgLen);

VOS_VOID CBT_AcpuSendResultChannel(CBT_MODEM_SSID_STRU stModemSsid, CBT_COMPONENT_MODE_STRU stCompMOde,
                            VOS_UINT16 usReturnPrimId, VOS_UINT32 ulResult);
VOS_VOID CBT_AcpuSendContentChannel(CBT_MODEM_SSID_STRU stModemSsid, CBT_COMPONENT_MODE_STRU stCompMOde,
                             VOS_UINT16 usReturnPrimId, CBT_UNIFORM_MSG_STRU * pstCbtToPcMsg);



#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif
