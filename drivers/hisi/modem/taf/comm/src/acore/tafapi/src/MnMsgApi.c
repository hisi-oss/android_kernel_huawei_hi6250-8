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

/*****************************************************************************
  1 
*****************************************************************************/
#include  "product_config.h"
#include  "vos.h"
#include  "MnErrorCode.h"
#include  "MnMsgApi.h"
#include  "ATCmdProc.h"



/*****************************************************************************
  2 
*****************************************************************************/
#define THIS_FILE_ID                PS_FILE_ID_MNMSG_API_C

/*****************************************************************************
  3 
*****************************************************************************/
/*API*/
typedef struct
{
    MN_MSG_MSGTYPE_ENUM_U16             enMsgType;
    VOS_UINT16                          usLen;
}MSG_MSGTYPE_LEN_STRU;

/*****************************************************************************
  4 
*****************************************************************************/
LOCAL MSG_MSGTYPE_LEN_STRU             f_astMsgTypeLen[] = {
    {MN_MSG_MSGTYPE_SEND_RPDATA_DIRECT ,sizeof(MN_MSG_SEND_PARM_STRU)},
    {MN_MSG_MSGTYPE_SEND_RPDATA_FROMMEM ,sizeof(MN_MSG_SEND_FROMMEM_PARM_STRU)},
    {MN_MSG_MSGTYPE_SEND_RPRPT ,sizeof(MN_MSG_SEND_ACK_PARM_STRU)},
    {MN_MSG_MSGTYPE_WRITE ,sizeof(MN_MSG_WRITE_PARM_STRU)},
    {MN_MSG_MSGTYPE_READ ,sizeof(MN_MSG_READ_PARM_STRU)},
    {MN_MSG_MSGTYPE_LIST ,sizeof(MN_MSG_LIST_PARM_STRU)},
    {MN_MSG_MSGTYPE_DELETE ,sizeof(MN_MSG_DELETE_PARAM_STRU)},
    {MN_MSG_MSGTYPE_DELETE_TEST, sizeof(MN_MSG_LIST_PARM_STRU)},
    {MN_MSG_MSGTYPE_WRITE_SRV_PARA ,sizeof(MN_MSG_WRITE_SRV_PARAM_STRU)},
    {MN_MSG_MSGTYPE_READ_SRV_PARA ,sizeof(MN_MSG_READ_COMM_PARAM_STRU)},
    {MN_MSG_MSGTYPE_DELETE_SRV_PARA ,sizeof(MN_MSG_DELETE_PARAM_STRU)},
    {MN_MSG_MSGTYPE_MODIFY_STATUS ,sizeof(MN_MSG_MODIFY_STATUS_PARM_STRU)},
    {MN_MSG_MSGTYPE_SET_RCVPATH ,sizeof(MN_MSG_SET_RCVMSG_PATH_PARM_STRU)},
    {MN_MSG_MSGTYPE_GET_RCVPATH ,sizeof(MN_MSG_GET_RCVMSG_PATH_PARM_STRU)},
    {MN_MSG_MSGTYPE_GET_STORAGESTATUS ,sizeof(MN_MSG_GET_STORAGE_STATUS_PARM_STRU)},
    {MN_MSG_MSGTYPE_READ_STARPT ,sizeof(MN_MSG_READ_COMM_PARAM_STRU)},
    {MN_MSG_MSGTYPE_DELETE_STARPT ,sizeof(MN_MSG_DELETE_PARAM_STRU)},
    {MN_MSG_MSGTYPE_GET_STARPT_FROMMOMSG ,sizeof(MN_MSG_STARPT_MOMSG_PARM_STRU)},
    {MN_MSG_MSGTYPE_GET_MOMSG_FROMSTARPT ,sizeof(MN_MSG_STARPT_MOMSG_PARM_STRU)},
    {MN_MSG_MSGTYPE_SET_MEMSTATUS ,sizeof(MN_MSG_SET_MEMSTATUS_PARM_STRU)},
    {MN_MSG_MSGTYPE_SET_RELAY_LINK_CTRL, sizeof(MN_MSG_SET_LINK_CTRL_STRU)},
    {MN_MSG_MSGTYPE_GET_RELAY_LINK_CTRL, 0},
    {MN_MSG_MSGTYPE_STUB, sizeof(MN_MSG_STUB_MSG_STRU)},
    {MN_MSG_MSGTYPE_GET_ALLCBMIDS ,0},
    {MN_MSG_MSGTYPE_ADD_CBMIDS ,    sizeof(TAF_CBA_CBMI_RANGE_LIST_STRU)},
    {MN_MSG_MSGTYPE_DELETE_CBMIDS , sizeof(TAF_CBA_CBMI_RANGE_LIST_STRU)},
    {MN_MSG_MSGTYPE_EMPTY_CBMIDS,0}
};

LOCAL MN_MSG_TS_DATA_INFO_STRU         f_stMsgDataInfo;

/*****************************************************************************
  5 
*****************************************************************************/
/*****************************************************************************
     : MSG_SendAppReq
   : 
   : enMsgType       - 
             clientId        - ClientID
             opId            - Operation ID, 
             pSendParm       - 
   : 
     : MN_ERR_NO_ERROR
             
   :
   :

       :
  1.       : 2008214
           : z40661
       : 
  2.       : 201245
           : l00171473
       : for V7R1C50 CSFB&PPAC&ETWS&ISR
  3.       : 20121211
           : l00167671
       : DTS2012121802573,TQE
  4.       : 20121224
           : l60609
       : DSDA Phase II

*****************************************************************************/
VOS_UINT32 MSG_SendAppReq(
    MN_MSG_MSGTYPE_ENUM_U16             enMsgType,
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const VOS_VOID                      *pSendParm
)
{
    MN_APP_REQ_MSG_STRU                *pstAppReq;
    VOS_UINT32                          ulLen;
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulSendLen;
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulMaxLoop;

    /*  */
    if ((enMsgType >= MN_MSG_MSGTYPE_MAX)
     || (enMsgType <= MN_APP_MSG_CLASS_MSG))
    {
        AT_WARN_LOG("MSG_SendAppReq:Invalid enMsgType. ");
        return MN_ERR_INVALIDPARM;
    }

    /*  */
    ulMaxLoop    = sizeof(f_astMsgTypeLen)/sizeof(MSG_MSGTYPE_LEN_STRU);
    for (ulLoop = 0; ulLoop < ulMaxLoop; ulLoop++)
    {
        if (enMsgType == f_astMsgTypeLen[ulLoop].enMsgType)
        {
            break;
        }
    }

    if (ulLoop == ulMaxLoop)
    {
        return MN_ERR_CLASS_SMS_INTERNAL;
    }

    ulLen = f_astMsgTypeLen[ulLoop].usLen;

    ulSendLen = (ulLen + sizeof(MN_APP_REQ_MSG_STRU)) - (sizeof(VOS_UINT8)*4);

    /*  */
    pstAppReq = (MN_APP_REQ_MSG_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_AT,ulSendLen);

    if (VOS_NULL_PTR == pstAppReq)
    {
        AT_WARN_LOG("MSG_SendAppReq:Alloc Msg Failed");
        return MN_ERR_NOMEM;
    }

    pstAppReq->ulSenderCpuId = VOS_LOCAL_CPUID;
    pstAppReq->ulSenderPid = WUEPS_PID_AT;
    pstAppReq->ulReceiverCpuId = VOS_LOCAL_CPUID;
    /* Modified by l60609 for DSDA Phase II, 2012-12-24, Begin */
    pstAppReq->ulReceiverPid = AT_GetDestPid(clientId, I0_WUEPS_PID_TAF);
    /* Modified by l60609 for DSDA Phase II, 2012-12-24, End */
    pstAppReq->usMsgName = enMsgType;
    pstAppReq->aucReserve1[0] = 0;
    pstAppReq->aucReserve1[1] = 0;
    pstAppReq->clientId = clientId;
    pstAppReq->opId = opId;
    pstAppReq->aucReserve2[0] = 0;

    if ((ulLen > 0) && (VOS_NULL_PTR != pSendParm))
    {
        TAF_MEM_CPY_S(pstAppReq->aucContent, ulLen, (VOS_UINT8*)pSendParm, ulLen);
    }
    ulRet = PS_SEND_MSG(WUEPS_PID_AT, pstAppReq);
    if (VOS_OK != ulRet)
    {
        AT_WARN_LOG("MSG_SendAppReq: PS_SEND_MSG fails");
        return MN_ERR_SEND_MSG_ERROR;
    }

    return MN_ERR_NO_ERROR;
}

/* Added by f62575 for AT Project2011-10-03,  Begin*/
/*****************************************************************************
     : MN_MSG_ReqStub
   : C
   : MN_CLIENT_ID_T                 clientId ClientID
             MN_OPERATION_ID_T              opId     Operation ID, 
             const MN_MSG_STUB_MSG_STRU     *pstStubParam 
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 2011103
           : f62575
       : 

*****************************************************************************/
VOS_UINT32 MN_MSG_ReqStub(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_STUB_MSG_STRU         *pstStubParam
)
{
    VOS_UINT32                          ulRet;

    /**/
    if (VOS_NULL_PTR == pstStubParam)
    {
        AT_WARN_LOG("MN_MSG_ReqStub: pstSetParam is Null ");
        return MN_ERR_NULLPTR;
    }

    ulRet = MSG_SendAppReq(MN_MSG_MSGTYPE_STUB,
                           clientId,
                           opId,
                           (VOS_VOID *)pstStubParam);

    return ulRet;
}
/* Added by f62575 for AT Project2011-10-03,  End*/

/*****************************************************************************
     : MN_MSG_SetLinkCtrl
   : 
   : clientId          - ClientID
             opId              - Operation ID, 
             pstSetParam     - 
   : 
     : MN_ERR_NO_ERROR
             
   :
   :

       :
  1.       : 2008721
           : f62575
       : 
*****************************************************************************/
VOS_UINT32   MN_MSG_SetLinkCtrl(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_SET_LINK_CTRL_STRU     *pstSetParam
)
{
    VOS_UINT32                          ulRet;

    /**/
    if (VOS_NULL_PTR == pstSetParam)
    {
        AT_WARN_LOG("MN_MSG_SetLinkCtrl:pstSetParam is Null ");
        return MN_ERR_NULLPTR;
    }

    if (pstSetParam->enRelayLinkCtrl >= MN_MSG_LINK_CTRL_BUTT)
    {
        AT_WARN_LOG("MN_MSG_SetLinkCtrl:Invalid value");
        return MN_ERR_INVALIDPARM;
    }

    ulRet = MSG_SendAppReq(MN_MSG_MSGTYPE_SET_RELAY_LINK_CTRL,
                           clientId,
                           opId,
                           (VOS_VOID *)pstSetParam);

    return ulRet;

}

/*****************************************************************************
     : MN_MSG_GetLinkCtrl
   : 
   : clientId          - ClientID
             opId              - Operation ID, 
   : 
     : MN_ERR_NO_ERROR
             
   :
   :

       :
  1.       : 2008721
           : f62575
       : 
*****************************************************************************/
VOS_UINT32   MN_MSG_GetLinkCtrl(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId
)
{
    VOS_UINT32                          ulRet;

    ulRet = MSG_SendAppReq(MN_MSG_MSGTYPE_GET_RELAY_LINK_CTRL,
                           clientId,
                           opId,
                           VOS_NULL_PTR);

    return ulRet;
}

/*****************************************************************************
     : MN_MSG_Send
   : 
   : clientId          - ClientID
             opId              - Operation ID, 
             pstSendDirectParm - 
   : 
     : MN_ERR_NO_ERROR
             
   :
   :

       :
  1.       : 2007927
           : z40661
       : 
  2.       : 20110301
           : A00165503
       : : DTS2011021202242/DTS2011021400322
                 PS_ONLYCS
*****************************************************************************/
VOS_UINT32   MN_MSG_Send(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_SEND_PARM_STRU         *pstSendParm
)
{
    VOS_UINT32                          ulRet;

    /**/
    if (VOS_NULL_PTR == pstSendParm)
    {
        AT_WARN_LOG("MN_MSG_Send:pstSendDirectParm is Null ");
        return MN_ERR_NULLPTR;
    }

    if (MN_MSG_SEND_DOMAIN_CS_PREFERRED < pstSendParm->enDomain)
    {
        AT_WARN_LOG("MN_MSG_Send:Invalid enDomain");
        return MN_ERR_CLASS_SMS_NOAVAILDOMAIN;
    }

    if (MN_MSG_MEM_STORE_NV < pstSendParm->enMemStore)
    {
        AT_WARN_LOG("MN_MSG_Send:Invalid enMemStore");
        return MN_ERR_INVALIDPARM;
    }

    /*SCADDR,24011,BCD2,11*/
    if (pstSendParm->stMsgInfo.stScAddr.ucBcdLen > 0)
    {
        if ((pstSendParm->stMsgInfo.stScAddr.ucBcdLen < MN_MSG_MIN_BCD_NUM_LEN)
         || (pstSendParm->stMsgInfo.stScAddr.ucBcdLen > MN_MSG_MAX_BCD_NUM_LEN))
        {
            AT_WARN_LOG("MN_MSG_Send:Invalid SC Address");
            return MN_ERR_CLASS_SMS_INVALID_SCADDR;
        }
    }

    /*TPDU,*/
    if ((MN_MSG_TPDU_COMMAND != pstSendParm->stMsgInfo.stTsRawData.enTpduType)
     && (MN_MSG_TPDU_SUBMIT != pstSendParm->stMsgInfo.stTsRawData.enTpduType))
    {
        AT_WARN_LOG("MN_MSG_Send:Invalid Tpdu Type");
        return MN_ERR_CLASS_SMS_INVALID_TPDUTYPE;
    }

    TAF_MEM_SET_S(&f_stMsgDataInfo, sizeof(f_stMsgDataInfo), 0x00, sizeof(f_stMsgDataInfo));
    ulRet = MN_MSG_Decode(&pstSendParm->stMsgInfo.stTsRawData,&f_stMsgDataInfo);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        AT_WARN_LOG("MN_MSG_Send:Invalid Tpdu");
        return MN_ERR_CLASS_SMS_INVALID_TPDU;
    }

    if (MN_MSG_TPDU_SUBMIT == pstSendParm->stMsgInfo.stTsRawData.enTpduType)
    {
        if (MN_MSG_TPDU_SUBMIT != f_stMsgDataInfo.enTpduType)
        {
            AT_WARN_LOG("MN_MSG_Send:Conflict TPDU type");
            return MN_ERR_CLASS_SMS_INVALID_TPDUTYPE;
        }

        if (0 == f_stMsgDataInfo.u.stSubmit.stDestAddr.ulLen)
        {
            AT_WARN_LOG("MN_MSG_Send:No DA");
            return MN_ERR_CLASS_SMS_INVALID_DESTADDR;
        }
    }
    else
    {
        if (MN_MSG_TPDU_COMMAND != f_stMsgDataInfo.enTpduType)
        {
            AT_WARN_LOG("MN_MSG_Send:Conflict TPDU type");
            return MN_ERR_CLASS_SMS_INVALID_TPDUTYPE;
        }
    }

    ulRet = MSG_SendAppReq(MN_MSG_MSGTYPE_SEND_RPDATA_DIRECT,
                           clientId,
                           opId,
                           (VOS_VOID *)pstSendParm);

    return ulRet;
}

/*****************************************************************************
     : MN_MSG_SendFromMem
   : USIMNVIM
   : clientId           - ClientID
             opId               - Operation ID, 
             enDomain           - 
             pstSendFromMemParm - 
   : 
     : MN_ERR_NO_ERROR
             
   :
   :

       :
  1.       : 2007927
           : z40661
       : 
*****************************************************************************/
VOS_UINT32   MN_MSG_SendFromMem(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_SEND_FROMMEM_PARM_STRU *pstSendFromMemParm
)
{
    VOS_UINT32                          ulRet;

    /**/
    if (VOS_NULL_PTR == pstSendFromMemParm)
    {
        AT_WARN_LOG("MN_MSG_SendFromMem:pstSendFromMemParm is Null");
        return MN_ERR_NULLPTR;
    }

    if (MN_MSG_SEND_DOMAIN_CS_PREFERRED < pstSendFromMemParm->enDomain)
    {
        AT_WARN_LOG("MN_MSG_SendFromMem:Invalid enDomain");
        return MN_ERR_INVALIDPARM;
    }

    if ((MN_MSG_MEM_STORE_SIM != pstSendFromMemParm->enMemStore)
     && (MN_MSG_MEM_STORE_NV != pstSendFromMemParm->enMemStore))
    {
        AT_WARN_LOG("MN_MSG_SendFromMem:Invalid enMemStore");
        return MN_ERR_INVALIDPARM;
    }

    if ((pstSendFromMemParm->stDestAddr.ucBcdLen > 0)
     && ((pstSendFromMemParm->stDestAddr.ucBcdLen < MN_MSG_MIN_BCD_NUM_LEN)
      || (pstSendFromMemParm->stDestAddr.ucBcdLen > MN_MSG_MAX_BCD_NUM_LEN)))
    {
        AT_WARN_LOG("MN_MSG_SendFromMem:Invalid Dest Address");
        return MN_ERR_CLASS_SMS_INVALID_DESTADDR;
    }

    ulRet = MSG_SendAppReq(MN_MSG_MSGTYPE_SEND_RPDATA_FROMMEM,
                           clientId,
                           opId,
                           (VOS_VOID *)pstSendFromMemParm);

    return ulRet;
}

/*****************************************************************************
     : MN_MSG_SendAck
   : ,,RP-ACKRP-ERROR
   : clientId           - ClientID
             opId               - Operation ID, 
             pstAckParm         - 
   : 
     : MN_ERR_NO_ERROR
             
   :
   :

       :
  1.       : 2007927
           : z40661
       : 
*****************************************************************************/
VOS_UINT32   MN_MSG_SendAck(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_SEND_ACK_PARM_STRU     *pstAckParm
)
{
    VOS_UINT32                          ulRet;

    /**/
    if (VOS_NULL_PTR == pstAckParm)
    {
        AT_WARN_LOG("MN_MSG_SendAck:pstAckParm is Null");
        return MN_ERR_NULLPTR;
    }
    /*Deliver Ack Deliver Err*/
    if ((MN_MSG_TPDU_DELIVER_RPT_ACK != pstAckParm->stTsRawData.enTpduType)
     && (MN_MSG_TPDU_DELIVER_RPT_ERR != pstAckParm->stTsRawData.enTpduType))
    {
        AT_WARN_LOG("MN_MSG_SendAck:Invalid Tpdu Type");
        return MN_ERR_CLASS_SMS_INVALID_TPDUTYPE;
    }
    /*TPDU,*/
    TAF_MEM_SET_S(&f_stMsgDataInfo, sizeof(f_stMsgDataInfo), 0x00, sizeof(f_stMsgDataInfo));
    ulRet = MN_MSG_Decode(&pstAckParm->stTsRawData,&f_stMsgDataInfo);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        AT_WARN_LOG("MN_MSG_SendAck:Invalid Tpdu");
        return MN_ERR_CLASS_SMS_INVALID_TPDU;
    }

    ulRet = MSG_SendAppReq(MN_MSG_MSGTYPE_SEND_RPRPT,
                           clientId,
                           opId,
                           (VOS_VOID *)pstAckParm);

    return ulRet;
}

/*****************************************************************************
     : MN_MSG_Write
   : USIMNVIM
   : clientId       - ClientID
             opId           - Operation ID, 
             pstWriteParm   - 
   : 
     : MN_ERR_NO_ERROR
             
   :
   :

       :
  1.       : 2007927
           : z40661
       : 
*****************************************************************************/
VOS_UINT32   MN_MSG_Write(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_WRITE_PARM_STRU        *pstWriteParm
)
{
    VOS_UINT32                          ulRet;

    /**/
    if (VOS_NULL_PTR == pstWriteParm)
    {
        AT_WARN_LOG("MN_MSG_Write:pstWriteParm is Null");
        return MN_ERR_NULLPTR;
    }

    if ((MN_MSG_WRITE_MODE_INSERT != pstWriteParm->enWriteMode)
     && (MN_MSG_WRITE_MODE_REPLACE != pstWriteParm->enWriteMode))
    {
        AT_WARN_LOG("MN_MSG_Write:Invalid enWriteMode");
        return MN_ERR_INVALIDPARM;
    }

    if ((MN_MSG_MEM_STORE_SIM != pstWriteParm->enMemStore)
     && (MN_MSG_MEM_STORE_NV != pstWriteParm->enMemStore))
    {
        AT_WARN_LOG("MN_MSG_Write:Invalid enMemStore");
        return MN_ERR_INVALIDPARM;
    }

    if (pstWriteParm->enStatus >= MN_MSG_STATUS_NONE)
    {
        AT_WARN_LOG("MN_MSG_Write:Invalid enStatus");
        return MN_ERR_INVALIDPARM;
    }

    /*SC ADDR,SC ADDR*/
    if (pstWriteParm->stMsgInfo.stScAddr.ucBcdLen > 0)
    {
        if ((pstWriteParm->stMsgInfo.stScAddr.ucBcdLen < MN_MSG_MIN_BCD_NUM_LEN)
         || (pstWriteParm->stMsgInfo.stScAddr.ucBcdLen > MN_MSG_MAX_BCD_NUM_LEN))
        {
            AT_WARN_LOG("MN_MSG_Send:Invalid SC Address");
            return MN_ERR_CLASS_SMS_INVALID_SCADDR;
        }
    }

    /*TPDU,*/
    TAF_MEM_SET_S(&f_stMsgDataInfo, sizeof(f_stMsgDataInfo), 0x00, sizeof(f_stMsgDataInfo));
    ulRet = MN_MSG_Decode(&pstWriteParm->stMsgInfo.stTsRawData,&f_stMsgDataInfo);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        AT_WARN_LOG("MN_MSG_Write:Invalid Tpdu");
        return MN_ERR_CLASS_SMS_INVALID_TPDU;
    }

    ulRet = MSG_SendAppReq(MN_MSG_MSGTYPE_WRITE,
                           clientId,
                           opId,
                           (VOS_VOID *)pstWriteParm);

    return ulRet;
}

/*****************************************************************************
     : MN_MSG_Read
   : USIMNVIM
   : clientId       - ClientID
             opId           - Operation ID, 
             pstReadParm    - 
   : 
     : MN_ERR_NO_ERROR
             
   :
   :

       :
  1.       : 2007927
           : z40661
       : 
*****************************************************************************/
VOS_UINT32   MN_MSG_Read(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_READ_PARM_STRU         *pstReadParm
)
{
    VOS_UINT32                          ulRet;

    if (VOS_NULL_PTR == pstReadParm)
    {
        AT_WARN_LOG("MN_MSG_Read:pstReadParm is Null");
        return MN_ERR_NULLPTR;
    }

    if ((MN_MSG_MEM_STORE_SIM != pstReadParm->enMemStore)
     && (MN_MSG_MEM_STORE_NV != pstReadParm->enMemStore))
    {
        AT_WARN_LOG("MN_MSG_Read:Invalid enMemStore");
        return MN_ERR_INVALIDPARM;
    }

    ulRet = MSG_SendAppReq(MN_MSG_MSGTYPE_READ,
                           clientId,
                           opId,
                           (VOS_VOID *)pstReadParm);

    return ulRet;
}


/*****************************************************************************
     : MN_MSG_List
   : USIMNVIM
   : clientId       - ClientID
             opId           - Operation ID, 
             pstListParm    - 
   : 
     : MN_ERR_NO_ERROR
             
   :
   :

       :
  1.       : 2007927
           : z40661
       : 
*****************************************************************************/
VOS_UINT32   MN_MSG_List(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_LIST_PARM_STRU         *pstListParm
)
{
    VOS_UINT32                          ulRet;

    if (VOS_NULL_PTR == pstListParm)
    {
        AT_WARN_LOG("MN_MSG_List:pstListParm is Null");
        return MN_ERR_NULLPTR;
    }

    if ((MN_MSG_MEM_STORE_SIM != pstListParm->enMemStore)
     && (MN_MSG_MEM_STORE_NV != pstListParm->enMemStore))
    {
        AT_WARN_LOG("MN_MSG_List:Invalid enMemStore");
        return MN_ERR_INVALIDPARM;
    }

    if (MN_MSG_STATUS_NONE < pstListParm->enStatus)
    {
        AT_WARN_LOG("MN_MSG_List:Invalid enStatus");
        return MN_ERR_INVALIDPARM;
    }

    ulRet = MSG_SendAppReq(MN_MSG_MSGTYPE_LIST,
                           clientId,
                           opId,
                           (VOS_VOID *)pstListParm);

    return ulRet;
}

/*****************************************************************************
     : MN_MSG_Delete
   : USIMNVIM
   : clientId       - ClientID
             opId           - Operation ID, 
             pstDeleteParm  - ,
   : 
     : MN_ERR_NO_ERROR
             
   :
   :

       :
  1.       : 2007927
           : z40661
       : 
*****************************************************************************/
VOS_UINT32   MN_MSG_Delete(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_DELETE_PARAM_STRU      *pstDeleteParam
)
{
    VOS_UINT32                          ulRet;

    if (VOS_NULL_PTR == pstDeleteParam)
    {
        AT_WARN_LOG("MN_MSG_Delete:pstDelete is Null");
        return MN_ERR_NULLPTR;
    }

    if ((MN_MSG_MEM_STORE_SIM != pstDeleteParam->enMemStore)
     && (MN_MSG_MEM_STORE_NV != pstDeleteParam->enMemStore))
    {
        AT_WARN_LOG("MN_MSG_Delete:Invalid enMemStore");
        return MN_ERR_INVALIDPARM;
    }

    if (MN_MSG_DELETE_ALL < pstDeleteParam->enDeleteType)
    {
        AT_WARN_LOG("MN_MSG_Delete:Invalid enDeleteType");
        return MN_ERR_INVALIDPARM;
    }

    ulRet = MSG_SendAppReq(MN_MSG_MSGTYPE_DELETE,
                           clientId,
                           opId,
                           (VOS_VOID *)pstDeleteParam);

    return ulRet;
}

/*****************************************************************************
     : MN_MSG_Delete_Test
   : USIMNVIM
   : clientId       - ClientID
             opId           - Operation ID, 
             enMemStore     - 
   : 
     : MN_ERR_NO_ERROR
             
   :
   :

       :
  1.       : 2007927
           : z40661
       : 
*****************************************************************************/
VOS_UINT32   MN_MSG_Delete_Test(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_LIST_PARM_STRU         *pstListPara
)
{
    VOS_UINT32                          ulRet;

    if ((MN_MSG_MEM_STORE_SIM != pstListPara->enMemStore)
     && (MN_MSG_MEM_STORE_NV != pstListPara->enMemStore))
    {
        AT_WARN_LOG("MN_MSG_Delete:Invalid enMemStore");
        return MN_ERR_INVALIDPARM;
    }

    if (pstListPara->enStatus >= MN_MSG_STATUS_MAX)
    {
        AT_WARN_LOG("MN_MSG_Delete:Invalid enStatus");
        return MN_ERR_INVALIDPARM;
    }

    ulRet = MSG_SendAppReq(MN_MSG_MSGTYPE_DELETE_TEST,
                           clientId,
                           opId,
                           (VOS_VOID *)pstListPara);

    return ulRet;
}

/*****************************************************************************
     : MN_MSG_ReadStaRpt
   : USIMNVIM
   : clientId            - ClientID
             opId                - Operation ID, 
             pstReadParm         - ,
   : 
     : MN_ERR_NO_ERROR
             
   :
   :

       :
  1.       : 2007927
           : z40661
       : 
  2.       : 20120303
           : s62952
       : BalongV300R002 Build:
  3.       : 2014530
           : j00174725
       : TQE
*****************************************************************************/
VOS_UINT32   MN_MSG_ReadStaRpt(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_READ_COMM_PARAM_STRU   *pstReadParam
)
{
    VOS_UINT32                          ulRet;

    if (VOS_NULL_PTR == pstReadParam)
    {
        AT_WARN_LOG("MN_MSG_ReadStaRpt:pstReadParam is Null");
        return MN_ERR_NULLPTR;
    }

    /* Modified by s62952 for BalongV300R002 Build 2012-02-28, begin */
    if ((MN_MSG_MEM_STORE_SIM != pstReadParam->enMemStore)
     && (MN_MSG_MEM_STORE_NV != pstReadParam->enMemStore))
    {
        AT_WARN_LOG("MN_MSG_ReadStaRpt:Invalid enMemStore1");
        return MN_ERR_INVALIDPARM;
    }

    if (MN_MSG_MEM_STORE_SIM != pstReadParam->enMemStore)
    {
        AT_WARN_LOG("MN_MSG_ReadStaRpt:Invalid enMemStore2");
        return MN_ERR_INVALIDPARM;
    }
    /* Modified by s62952 for BalongV300R002 Build 2012-02-28, end */

    ulRet = MSG_SendAppReq(MN_MSG_MSGTYPE_READ_STARPT,
                           clientId,
                           opId,
                           (VOS_VOID *)pstReadParam);

    return ulRet;
}

/*****************************************************************************
     : MN_MSG_DeleteStaRpt
   : USIMNVIM
   : clientId       - ClientID
             opId           - Operation ID, 
             pstDelete      - ,,
   : 
     : MN_ERR_NO_ERROR
             
   :
   :

       :
  1.       : 2007927
           : z40661
       : 
 2.       : 20120303
           : s62952
       : BalongV300R002 Build:API
*****************************************************************************/
VOS_UINT32   MN_MSG_DeleteStaRpt(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_DELETE_PARAM_STRU       *pstDeleteParam
)
{
    VOS_UINT32                          ulRet;

    if (VOS_NULL_PTR == pstDeleteParam)
    {
        AT_WARN_LOG("MN_MSG_DeleteStaRpt:pstDeleteParam is Null");
        return MN_ERR_NULLPTR;
    }

    /* Modified by s62952 for BalongV300R002 Build 2012-02-28, begin */
    if ((MN_MSG_MEM_STORE_SIM != pstDeleteParam->enMemStore)
     && (MN_MSG_MEM_STORE_NV != pstDeleteParam->enMemStore))
    {
        AT_WARN_LOG("MN_MSG_DeleteStaRpt:Invalid enMemStore");
        return MN_ERR_INVALIDPARM;
    }

    if (MN_MSG_MEM_STORE_SIM != pstDeleteParam->enMemStore)
    {
        AT_WARN_LOG("MN_MSG_DeleteStaRpt:Invalid enMemStore");
        return MN_ERR_INVALIDPARM;
    }
    /* Modified by s62952 for BalongV300R002 Build 2012-02-28, end */

    if ((MN_MSG_DELETE_SINGLE != pstDeleteParam->enDeleteType)
     && (MN_MSG_DELETE_ALL != pstDeleteParam->enDeleteType))
    {
        AT_WARN_LOG("MN_MSG_DeleteStaRpt:Invalid enDeleteType");
        return MN_ERR_INVALIDPARM;
    }

    ulRet = MSG_SendAppReq(MN_MSG_MSGTYPE_DELETE_STARPT,
                           clientId,
                           opId,
                           (VOS_VOID *)pstDeleteParam);

    return ulRet;
}


/*****************************************************************************
     : MN_MSG_WriteSrvParam
   : ,
   : clientId       - ClientID
             opId           - Operation ID, 
             pstSrvParam     - ,
   : 
     : MN_ERR_NO_ERROR
             
   :
   :

       :
  1.       : 2007927
           : z40661
       : 
*****************************************************************************/
VOS_UINT32   MN_MSG_WriteSrvParam(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_WRITE_SRV_PARAM_STRU   *pstSrvParam
)
{
    VOS_UINT32                          ulRet;

    if (VOS_NULL_PTR == pstSrvParam)
    {
        AT_WARN_LOG("MN_MSG_WriteSrvParam:pstSetSrvParm is Null");
        return MN_ERR_NULLPTR;
    }

    if ((MN_MSG_WRITE_MODE_INSERT != pstSrvParam->enWriteMode)
     && (MN_MSG_WRITE_MODE_REPLACE != pstSrvParam->enWriteMode))
    {
        AT_WARN_LOG("MN_MSG_WriteSrvParam:Invalid enWriteMode");
        return MN_ERR_INVALIDPARM;
    }

    if ((MN_MSG_MEM_STORE_SIM != pstSrvParam->enMemStore)
     && (MN_MSG_MEM_STORE_NV != pstSrvParam->enMemStore))
    {
        AT_WARN_LOG("MN_MSG_WriteSrvParam:Invalid enMemStore");
        return MN_ERR_INVALIDPARM;
    }

    if ((MN_MSG_MEM_STORE_NV == pstSrvParam->enMemStore)
     && (0 != pstSrvParam->ulIndex))
    {
        AT_WARN_LOG("MN_MSG_WriteSrvParam:Only one record supported in NV.");
        return MN_ERR_INVALIDPARM;
    }

    /*,*/
    if (MN_MSG_SRV_PARM_TOTALABSENT == (pstSrvParam->stSrvParm.ucParmInd & MN_MSG_SRV_PARM_TOTALABSENT))
    {
        AT_WARN_LOG("MN_MSG_WriteSrvParam:Invalid Parm,No Valid Data");
        return MN_ERR_INVALIDPARM;
    }

    /*SC AddrDest Addr*/
    if (MN_MSG_SRV_PARM_PRESENT ==
        ((pstSrvParam->stSrvParm.ucParmInd & MN_MSG_SRV_PARM_MASK_SC_ADDR) >> 1))
    {
       if (pstSrvParam->stSrvParm.stScAddr.ucBcdLen > MN_MSG_MAX_BCD_NUM_LEN)
       {
           AT_WARN_LOG("MN_MSG_WriteSrvParam:Invalid SC Address");
           return MN_ERR_CLASS_SMS_INVALID_SCADDR;
       }
    }

    if (MN_MSG_SRV_PARM_PRESENT ==
        (pstSrvParam->stSrvParm.ucParmInd & MN_MSG_SRV_PARM_MASK_DEST_ADDR))
    {
        if (pstSrvParam->stSrvParm.stDestAddr.ucBcdLen > MN_MSG_MAX_BCD_NUM_LEN)
        {
            AT_WARN_LOG("MN_MSG_WriteSrvParam:Invalid Dest Address");
            return MN_ERR_CLASS_SMS_INVALID_DESTADDR;
        }
    }

    ulRet = MSG_SendAppReq(MN_MSG_MSGTYPE_WRITE_SRV_PARA,
                           clientId,
                           opId,
                           (VOS_VOID *)pstSrvParam);

    return ulRet;
}

/*****************************************************************************
     : MN_MSG_ReadSrvParam
   : ,
   : clientId       - ClientID
             opId           - Operation ID, 
             pstReadParm    - ,
   : 
     : MN_ERR_NO_ERROR
             
   :
   :

       :
  1.       : 2007927
           : z40661
       : 
*****************************************************************************/
VOS_UINT32   MN_MSG_ReadSrvParam(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_READ_COMM_PARAM_STRU  *pstReadParam
)
{
    VOS_UINT32                          ulRet;

    if (VOS_NULL_PTR == pstReadParam)
    {
        AT_WARN_LOG("MN_MSG_ReadSrvParam:pstReadParam is Null");
        return MN_ERR_NULLPTR;
    }

    if ((MN_MSG_MEM_STORE_SIM != pstReadParam->enMemStore)
     && (MN_MSG_MEM_STORE_NV != pstReadParam->enMemStore))
    {
        AT_WARN_LOG("MN_MSG_ReadSrvParam:Invalid enMemStore");
        return MN_ERR_INVALIDPARM;
    }

    if ((MN_MSG_MEM_STORE_NV == pstReadParam->enMemStore)
     && (0 != pstReadParam->ulIndex))
    {
        AT_WARN_LOG("MN_MSG_ReadSrvParam: Only one record supported in NV.");
        return MN_ERR_INVALIDPARM;
    }

    ulRet = MSG_SendAppReq(MN_MSG_MSGTYPE_READ_SRV_PARA,
                           clientId,
                           opId,
                           (VOS_VOID *)pstReadParam);

    return ulRet;
}


/*****************************************************************************
     : MN_MSG_DeleteSrvParam
   : ,
   : clientId        - ClientID
             opId            - Operation ID, 
             pstDeleteParm   - ,,
   : 
     : MN_ERR_NO_ERROR
             
   :
   :

       :
  1.       : 2007927
           : z40661
       : 
*****************************************************************************/
VOS_UINT32   MN_MSG_DeleteSrvParam(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_DELETE_PARAM_STRU     *pstDeleteParam
)
{
    VOS_UINT32                          ulRet;

    if (VOS_NULL_PTR == pstDeleteParam)
    {
        AT_WARN_LOG("MN_MSG_DeleteSrvParam:pstDeleteParam is Null");
        return MN_ERR_NULLPTR;
    }

    if ((MN_MSG_MEM_STORE_SIM != pstDeleteParam->enMemStore)
     && (MN_MSG_MEM_STORE_NV != pstDeleteParam->enMemStore))
    {
        AT_WARN_LOG("MN_MSG_DeleteSrvParam:Invalid enMemStore");
        return MN_ERR_INVALIDPARM;
    }

    if ((MN_MSG_DELETE_SINGLE != pstDeleteParam->enDeleteType)
     && (MN_MSG_DELETE_ALL != pstDeleteParam->enDeleteType))
    {
        AT_WARN_LOG("MN_MSG_DeleteSrvParam:Invalid enDeleteType");
        return MN_ERR_INVALIDPARM;
    }

    if (MN_MSG_MEM_STORE_NV == pstDeleteParam->enMemStore)
    {
        if ((MN_MSG_DELETE_SINGLE != pstDeleteParam->enDeleteType)
         && (0 != pstDeleteParam->ulIndex))
        {
            AT_WARN_LOG("MN_MSG_WriteSrvParam:Only one record supported in NV.");
            return MN_ERR_INVALIDPARM;
        }
    }

    ulRet = MSG_SendAppReq(MN_MSG_MSGTYPE_DELETE_SRV_PARA,
                           clientId,
                           opId,
                           (VOS_VOID *)pstDeleteParam);

    return ulRet;
}

/*****************************************************************************
     : MN_MSG_ModifyStatus
   : 
                                     SUMBITCOMMAND
   : clientId            - ClientID
             opId                - Operation ID, 
             pstModifyParm       - 
   : 
     : MN_ERR_NO_ERROR
             
   :
   :

       :
  1.       : 2007927
           : z40661
       : 
*****************************************************************************/
VOS_UINT32   MN_MSG_ModifyStatus(
    MN_CLIENT_ID_T                       clientId,
    MN_OPERATION_ID_T                    opId,
    const MN_MSG_MODIFY_STATUS_PARM_STRU *pstModifyParm
)
{
    VOS_UINT32                          ulRet;

    if (VOS_NULL_PTR == pstModifyParm)
    {
        AT_WARN_LOG("MN_MSG_ModifyStatus:pstModifyParm is Null");
        return MN_ERR_NULLPTR;
    }

    if ((MN_MSG_MEM_STORE_SIM != pstModifyParm->enMemStore)
     && (MN_MSG_MEM_STORE_NV != pstModifyParm->enMemStore))
    {
        AT_WARN_LOG("MN_MSG_ModifyStatus:Invalid enMemStore");
        return MN_ERR_INVALIDPARM;
    }

    if (MN_MSG_STATUS_MO_SENT < pstModifyParm->enStatus)
    {
        AT_WARN_LOG("MN_MSG_ModifyStatus:Invalid enStatus");
        return MN_ERR_INVALIDPARM;
    }

    ulRet = MSG_SendAppReq(MN_MSG_MSGTYPE_MODIFY_STATUS,
                           clientId,
                           opId,
                           (VOS_VOID *)pstModifyParm);

    return ulRet;
}


/*****************************************************************************
     : MN_MSG_SetRcvMsgPath
   : ,
   : clientId            - ClientID
             opId                - Operation ID, 
             pstRcvPathParm      - 
   : 
     : MN_ERR_NO_ERROR
             
   :
   :

       :
  1.       : 2007927
           : z40661
       : 
*****************************************************************************/
VOS_UINT32 MN_MSG_SetRcvMsgPath(
    MN_CLIENT_ID_T                         clientId,
    MN_OPERATION_ID_T                      opId,
    const MN_MSG_SET_RCVMSG_PATH_PARM_STRU *pstSetRcvPathParm
)
{
    VOS_UINT32                          ulRet;

    if (VOS_NULL_PTR == pstSetRcvPathParm)
    {
        AT_WARN_LOG("MN_MSG_SetRcvMsgPath:pstSetRcvPathParm is Null");
        return MN_ERR_NULLPTR;
    }

    if  ((MN_MSG_RCVMSG_ACT_TRANSFER_AND_ACK < pstSetRcvPathParm->enRcvSmAct)
      || (MN_MSG_RCVMSG_ACT_TRANSFER_AND_ACK < pstSetRcvPathParm->enRcvStaRptAct))
    {
        AT_WARN_LOG("MN_MSG_SetRcvMsgPath:Invalid enRcvSmAct");
        return MN_ERR_INVALIDPARM;
    }

    if ((MN_MSG_MEM_STORE_NV < pstSetRcvPathParm->enSmMemStore)
     || (MN_MSG_MEM_STORE_NV < pstSetRcvPathParm->enStaRptMemStore))
    {
        AT_WARN_LOG("MN_MSG_SetRcvMsgPath:Invalid enSmMemStore");
        return MN_ERR_INVALIDPARM;
    }

    if (MN_MSG_RCVMSG_ACT_STORE == pstSetRcvPathParm->enRcvSmAct)
    {
        if ((MN_MSG_MEM_STORE_NV  != pstSetRcvPathParm->enSmMemStore)
         && (MN_MSG_MEM_STORE_SIM != pstSetRcvPathParm->enSmMemStore))
        {
            AT_WARN_LOG("MN_MSG_SetRcvMsgPath:Invalid Parm");
            return MN_ERR_INVALIDPARM;
        }
    }

    if (MN_MSG_RCVMSG_ACT_STORE == pstSetRcvPathParm->enRcvStaRptAct)
    {
        if ((MN_MSG_MEM_STORE_NV  != pstSetRcvPathParm->enStaRptMemStore)
         && (MN_MSG_MEM_STORE_SIM != pstSetRcvPathParm->enStaRptMemStore))
        {
            AT_WARN_LOG("MN_MSG_SetRcvMsgPath:Invalid Parm");
            return MN_ERR_INVALIDPARM;
        }
    }

    ulRet = MSG_SendAppReq(MN_MSG_MSGTYPE_SET_RCVPATH,
                           clientId,
                           opId,
                           (VOS_VOID *)pstSetRcvPathParm);

    return ulRet;

}

/*****************************************************************************
     : MN_MSG_GetRcvMsgPath
   : ,
   : clientId            - ClientID
             opId                - Operation ID, 
             pstGetRcvPathParm   - 
   : 
     : MN_ERR_NO_ERROR
             
   :
   :

       :
  1.       : 2007927
           : z40661
       : 
*****************************************************************************/
VOS_UINT32   MN_MSG_GetRcvMsgPath(
    MN_CLIENT_ID_T                         clientId,
    MN_OPERATION_ID_T                      opId,
    const MN_MSG_GET_RCVMSG_PATH_PARM_STRU *pstGetRcvPathParm
)
{
    VOS_UINT32                          ulRet;

    if (VOS_NULL_PTR == pstGetRcvPathParm)
    {
        AT_WARN_LOG("MN_MSG_GetRcvMsgPath:pstGetRcvPathParm is Null");
        return MN_ERR_NULLPTR;
    }

    ulRet = MSG_SendAppReq(MN_MSG_MSGTYPE_GET_RCVPATH,
                           clientId,
                           opId,
                           (VOS_VOID *)pstGetRcvPathParm);

    return ulRet;
}

/*****************************************************************************
     : MN_MSG_GetStorageStatus
   : 
   : clientId            - ClientID
             opId                - Operation ID, 
             pstMemParm          - 
   : 
     : MN_ERR_NO_ERROR
             
   :
   :

       :
  1.       : 2007927
           : z40661
       : 
*****************************************************************************/
VOS_UINT32  MN_MSG_GetStorageStatus(
    MN_CLIENT_ID_T                            clientId,
    MN_OPERATION_ID_T                         opId,
    const MN_MSG_GET_STORAGE_STATUS_PARM_STRU *pstStorageParm
)
{
    VOS_UINT32                          ulRet;

    if (VOS_NULL_PTR == pstStorageParm)
    {
        AT_WARN_LOG("MN_MSG_GetStorageStatus:pstMemParm is Null");
        return MN_ERR_NULLPTR;
    }

    if ((MN_MSG_MEM_STORE_SIM != pstStorageParm->enMem1Store)
     && (MN_MSG_MEM_STORE_NV != pstStorageParm->enMem1Store)
     && (MN_MSG_MEM_STORE_NONE != pstStorageParm->enMem1Store))
    {
        AT_WARN_LOG("MN_MSG_GetStorageStatus:Invalid enMemStore:mem1");
        return MN_ERR_INVALIDPARM;
    }

    if (pstStorageParm->enMem1Store == pstStorageParm->enMem2Store)
    {
        AT_WARN_LOG("MN_MSG_GetStorageStatus:Invalid enMemStore:mem1 == mem2");
        return MN_ERR_INVALIDPARM;
    }

    ulRet = MSG_SendAppReq(MN_MSG_MSGTYPE_GET_STORAGESTATUS,
                           clientId,
                           opId,
                           (VOS_VOID *)pstStorageParm);

    return ulRet;
}

/*****************************************************************************
     : MN_MSG_GetStatusRptIndex
   : MO
   : clientId       - ClientID
             opId           - Operation ID, 
             pstMoMsgParm   - MO,
   : 
     : MN_ERR_NO_ERROR
             
   :
   :

       :
  1.       : 2007927
           : z40661
       : 
*****************************************************************************/
VOS_UINT32   MN_MSG_GetStaRptIndex(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_STARPT_MOMSG_PARM_STRU *pstMoMsgParm
)
{
    VOS_UINT32                          ulRet;

    if (VOS_NULL_PTR == pstMoMsgParm)
    {
        AT_WARN_LOG("MN_MSG_GetStaRptFromMoMsg:pstMoMsgParm is Null");
        return MN_ERR_NULLPTR;
    }

    if ((MN_MSG_MEM_STORE_SIM != pstMoMsgParm->enMemStore)
     && (MN_MSG_MEM_STORE_NV != pstMoMsgParm->enMemStore))
    {
        AT_WARN_LOG("MN_MSG_GetStaRptFromMoMsg:Invalid enMemStore");
        return MN_ERR_INVALIDPARM;
    }

    ulRet = MSG_SendAppReq(MN_MSG_MSGTYPE_GET_STARPT_FROMMOMSG,
                           clientId,
                           opId,
                           (VOS_VOID *)pstMoMsgParm);

    return ulRet;

}

/*****************************************************************************
     : MN_MSG_GetMoMsgIndex
   : MO
   : clientId       - ClientID
             opId           - Operation ID, 
             pstStaRptParm  - ,

   : 
     : MN_ERR_NO_ERROR
             
   :
   :

       :
  1.       : 2007927
           : z40661
       : 
  2.       : 20120303
           : s62952
       : BalongV300R002 Build
*****************************************************************************/
VOS_UINT32   MN_MSG_GetMoMsgIndex(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_STARPT_MOMSG_PARM_STRU *pstStaRptParm
)
{
    VOS_UINT32                          ulRet;

    if (VOS_NULL_PTR == pstStaRptParm)
    {
        AT_WARN_LOG("MN_MSG_GetMoMsgFromStaRpt:pstMemParm is Null");
        return MN_ERR_NULLPTR;
    }

    /* Modified by s62952 for BalongV300R002 Build 2012-02-28, begin */
    if ((MN_MSG_MEM_STORE_SIM != pstStaRptParm->enMemStore)
     && (MN_MSG_MEM_STORE_NV != pstStaRptParm->enMemStore))
    {
        AT_WARN_LOG("MN_MSG_GetMoMsgFromStaRpt:Invalid enMemStore1");
        return MN_ERR_INVALIDPARM;
    }

    if (MN_MSG_MEM_STORE_SIM != pstStaRptParm->enMemStore)
    {
        AT_WARN_LOG("MN_MSG_GetMoMsgFromStaRpt:Invalid enMemStore2");
        return MN_ERR_INVALIDPARM;
    }
    /* Modified by s62952 for BalongV300R002 Build 2012-02-28, end */

    ulRet = MSG_SendAppReq(MN_MSG_MSGTYPE_GET_MOMSG_FROMSTARPT,
                           clientId,
                           opId,
                           (VOS_VOID *)pstStaRptParm);

    return ulRet;
}

/*****************************************************************************
     : MN_MSG_SetMemStatus
   : APP,
   : clientId            - ClientID
             opId                - Operation ID, 
             pMemStatusParm      - APP
   : 
     : MN_ERR_NO_ERROR
             
   :
   :

       :
  1.       : 2007927
           : z40661
       : 
*****************************************************************************/
VOS_UINT32 MN_MSG_SetMemStatus(
    MN_CLIENT_ID_T                       clientId,
    MN_OPERATION_ID_T                    opId,
    const MN_MSG_SET_MEMSTATUS_PARM_STRU *pMemStatusParm
)
{
    VOS_UINT32                          ulRet;

    if (VOS_NULL_PTR == pMemStatusParm)
    {
        AT_WARN_LOG("MN_MSG_SetMemStatus:pMemStatusParm is Null");
        return MN_ERR_NULLPTR;
    }

    if ((MN_MSG_MEM_FULL_SET != pMemStatusParm->enMemFlag)
     && (MN_MSG_MEM_FULL_UNSET != pMemStatusParm->enMemFlag))
    {
        AT_WARN_LOG("MN_MSG_SetMemStatus:Invalid enMemFlag");
        return MN_ERR_INVALIDPARM;
    }

    ulRet = MSG_SendAppReq(MN_MSG_MSGTYPE_SET_MEMSTATUS,
                           clientId,
                           opId,
                           (VOS_VOID *)pMemStatusParm);

    return ulRet;
}


/*****************************************************************************
     : MN_MSG_GetAllCbMids
   : CBS
   : clientId           - ClientID
             opId               - Operation ID, 
   : 
     : MN_ERR_NO_ERROR
             
   :
   :

       :
  1.       : 2010510
           : zhoujun \z40661
       : 

*****************************************************************************/
VOS_UINT32 MN_MSG_GetAllCbMids(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId
)
{
    VOS_UINT32                          ulRet;

    ulRet = MSG_SendAppReq(MN_MSG_MSGTYPE_GET_ALLCBMIDS,
                           clientId,
                           opId,
                           VOS_NULL_PTR);

    return ulRet;
}

/*****************************************************************************
     : MN_MSG_AddCbMids
   : CBS
   : clientId           - ClientID
             opId               - Operation ID, 
             pstCbMids          - ID
   : 
     : MN_ERR_NO_ERROR
             
   :
   :

       :
  1.       : 201058
           : zhoujun /z40661
       : 
  2.       : 201245
           : l00171473
       : for V7R1C50 CSFB&PPAC&ETWS&ISR
*****************************************************************************/
VOS_UINT32 MN_MSG_AddCbMids(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const TAF_CBA_CBMI_RANGE_LIST_STRU *pstCbmirList
)
{
    VOS_UINT32                          ulRet;

    if (VOS_NULL_PTR == pstCbmirList)
    {
        AT_WARN_LOG("MN_MSG_DeleteCbMsg: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }

    ulRet = MSG_SendAppReq(MN_MSG_MSGTYPE_ADD_CBMIDS,
                           clientId,
                           opId,
                           (VOS_VOID *)pstCbmirList);

    return ulRet;
}

/*****************************************************************************
     : MN_MSG_DeleteCbMids
   : CBS
   : clientId           - ClientID
             opId               - Operation ID, 
             pstCbMids          - ID
   : 
     : MN_ERR_NO_ERROR
             
   :
   :

 1.       : 201058
          : zhoujun /z40661
      : 
  2.       : 201245
           : l00171473
       : for V7R1C50 CSFB&PPAC&ETWS&ISR
*****************************************************************************/
VOS_UINT32 MN_MSG_DelCbMids(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const TAF_CBA_CBMI_RANGE_LIST_STRU *pstCbmirList
)
{
    VOS_UINT32                          ulRet;

    if (VOS_NULL_PTR == pstCbmirList)
    {
        AT_WARN_LOG("MN_MSG_DeleteCbMsg: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }

    ulRet = MSG_SendAppReq(MN_MSG_MSGTYPE_DELETE_CBMIDS,
                           clientId,
                           opId,
                           (VOS_VOID *)pstCbmirList);

    return ulRet;
}

/*****************************************************************************
     : MN_MSG_EmptyCbMids
   : CBS ID
   : clientId           - ClientID
             opId               - Operation ID, 
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 201058
           : zhoujun /z40661
       : 

*****************************************************************************/
VOS_UINT32 MN_MSG_EmptyCbMids(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId
)
{
    VOS_UINT32                          ulRet;

    ulRet = MSG_SendAppReq(MN_MSG_MSGTYPE_EMPTY_CBMIDS,
                           clientId,
                           opId,
                           VOS_NULL_PTR);

    return ulRet;
}


