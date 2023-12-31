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
#include "AdsCtx.h"
#include "AdsLog.h"
#include "AdsFilter.h"
/* Modified by m00217266 for L-C, 2014-2-11, begin */
#include "AdsInterface.h"
/* Modified by m00217266 for L-C, 2014-2-11, end */
#include "NVIM_Interface.h"


/*****************************************************************************
    .C
*****************************************************************************/
#define    THIS_FILE_ID                 PS_FILE_ID_ADS_FILTER_C

/*****************************************************************************
  2 
*****************************************************************************/
/* ADS */
ADS_FILTER_CTX_STRU                     g_stAdsFilterCtx;

/* ADS: :
           
      0         IPv4 TCP
      1         IPv4 UDP
      2         IPv4 ECHO REQ
      3         IPv4
      4         IPv6
      5         IPv4 TCP
      6         IPv4 UDP
      7         IPv4 ECHO REPLY
      8         IPv4 ICMP
      9         IPv4 ()
      10        IPv4 ()
      11        IPv6 */
VOS_UINT32                              g_aulAdsFilterStats[ADS_FILTER_ORIG_PKT_BUTT]  = {0};

/* ADSICMPEcho ReplyICMP */
ADS_FILTER_DECODE_DL_ICMP_FUNC_STRU     g_astAdsFilterDecodeDlIcmpFuncTbl[] =
    {         /*ICMP Type*/                            /* pFunc */                               /* enOrigPktType */           /* aucReserved[4] */
        /*  0:Echo Reply              */   {ADS_FILTER_DecodeDlIPv4EchoReplyPacket,     ADS_FILTER_ORIG_PKT_DL_IPV4_ECHOREPLY,         {0,0,0,0}},
        /*  1:Reserve                 */   {VOS_NULL_PTR,                               ADS_FILTER_ORIG_PKT_BUTT             ,         {0,0,0,0}},
        /*  2:Reserve                 */   {VOS_NULL_PTR,                               ADS_FILTER_ORIG_PKT_BUTT             ,         {0,0,0,0}},
        /*  3:Destination Unreachable */   {ADS_FILTER_DecodeDlIPv4IcmpErrorPacket,     ADS_FILTER_ORIG_PKT_DL_IPV4_ICMPERROR,         {0,0,0,0}},
        /*  4:Source Quench           */   {ADS_FILTER_DecodeDlIPv4IcmpErrorPacket,     ADS_FILTER_ORIG_PKT_DL_IPV4_ICMPERROR,         {0,0,0,0}},
        /*  5:Redirect (change route) */   {ADS_FILTER_DecodeDlIPv4IcmpErrorPacket,     ADS_FILTER_ORIG_PKT_DL_IPV4_ICMPERROR,         {0,0,0,0}},
        /*  6:Reserve                 */   {VOS_NULL_PTR,                               ADS_FILTER_ORIG_PKT_BUTT             ,         {0,0,0,0}},
        /*  7:Reserve                 */   {VOS_NULL_PTR,                               ADS_FILTER_ORIG_PKT_BUTT             ,         {0,0,0,0}},
        /*  8:Echo Request            */   {VOS_NULL_PTR,                               ADS_FILTER_ORIG_PKT_BUTT             ,         {0,0,0,0}},
        /*  9:Reserve                 */   {VOS_NULL_PTR,                               ADS_FILTER_ORIG_PKT_BUTT             ,         {0,0,0,0}},
        /* 10:Reserve                 */   {VOS_NULL_PTR,                               ADS_FILTER_ORIG_PKT_BUTT             ,         {0,0,0,0}},
        /* 11:Time Exceeded           */   {ADS_FILTER_DecodeDlIPv4IcmpErrorPacket,     ADS_FILTER_ORIG_PKT_DL_IPV4_ICMPERROR,         {0,0,0,0}},
        /* 12:Parameter Problem       */   {ADS_FILTER_DecodeDlIPv4IcmpErrorPacket,     ADS_FILTER_ORIG_PKT_DL_IPV4_ICMPERROR,         {0,0,0,0}},
        /* 13:Timestamp Request       */   {VOS_NULL_PTR,                               ADS_FILTER_ORIG_PKT_BUTT             ,         {0,0,0,0}},
        /* 14:Timestamp Reply         */   {VOS_NULL_PTR,                               ADS_FILTER_ORIG_PKT_BUTT             ,         {0,0,0,0}},
        /* 15:Information Request     */   {VOS_NULL_PTR,                               ADS_FILTER_ORIG_PKT_BUTT             ,         {0,0,0,0}},
        /* 16:Information Reply       */   {VOS_NULL_PTR,                               ADS_FILTER_ORIG_PKT_BUTT             ,         {0,0,0,0}},
        /* 17:Address Mask Request    */   {VOS_NULL_PTR,                               ADS_FILTER_ORIG_PKT_BUTT             ,         {0,0,0,0}},
        /* 18:Address Mask Reply      */   {VOS_NULL_PTR,                               ADS_FILTER_ORIG_PKT_BUTT             ,         {0,0,0,0}}
    };


/*****************************************************************************
  3 
*****************************************************************************/
/*****************************************************************************
     : ADS_FILTER_ResetIPv6Addr
   : IPv6
   : 
   : 
     : 
   :
   :

       :
  1.       : 20130604
           : l00198894
       : V3R3 Share-PDP
*****************************************************************************/
VOS_VOID ADS_FILTER_ResetIPv6Addr(VOS_VOID)
{
    TAF_MEM_SET_S(ADS_FILTER_GET_IPV6_ADDR(), sizeof(ADS_IPV6_ADDR_UN), 0x00, sizeof(ADS_IPV6_ADDR_UN));

    return;
}

/*****************************************************************************
     : ADS_FILTER_InitListsHead
   : ADS
   : 
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20130604
           : l00198894
       : V3R3 Share-PDP
*****************************************************************************/
VOS_VOID ADS_FILTER_InitListsHead(VOS_VOID)
{
    VOS_UINT32                          ulLoop;
    HI_LIST_S                          *pstListHead = VOS_NULL_PTR;

    /*  */
    for (ulLoop = 0; ulLoop < ADS_FILTER_MAX_LIST_NUM; ulLoop++)
    {
        pstListHead = ADS_FILTER_GET_LIST(ulLoop);

        HI_INIT_LIST_HEAD(pstListHead);
    }
    return;
}

/*****************************************************************************
     : ADS_FILTER_InitCtx
   : ADS
   : 
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20130604
           : l00198894
       : V3R3 Share-PDP
  2.       : 201307222
           : j00177245
       : warning
*****************************************************************************/
VOS_VOID ADS_FILTER_InitCtx(VOS_VOID)
{
    TAF_NVIM_SHARE_PDP_INFO_STRU        stSharePdp;
    VOS_UINT32                          ulTimeLen;

    TAF_MEM_SET_S(&g_stAdsFilterCtx, sizeof(g_stAdsFilterCtx), 0x00, sizeof(g_stAdsFilterCtx));

    /*  */
    ADS_FILTER_InitListsHead();

    /*  */
    /* NV */
    TAF_MEM_SET_S(&stSharePdp, sizeof(stSharePdp), 0x00, sizeof(stSharePdp));
    if (NV_OK != NV_ReadEx(MODEM_ID_0,
                           en_NV_Item_SHARE_PDP_INFO,
                           &stSharePdp,
                           sizeof(stSharePdp)))
    {
        ADS_WARNING_LOG(ACPU_PID_ADS_DL, "ADS_FILTER_InitCtx: NV Read Failed!");
        stSharePdp.usAgingTimeLen = ADS_FILTER_DEFAULT_AGING_TIMELEN;
    }

    ulTimeLen   = ADS_FILTER_SECOND_TRANSFER_JIFFIES * stSharePdp.usAgingTimeLen;
    ADS_FILTER_SET_AGING_TIME_LEN(ulTimeLen);

    /* IPv6 */
    ADS_FILTER_ResetIPv6Addr();

    return;
}

/*****************************************************************************
     : ADS_FILTER_HeapAlloc
   : ADS
   : VOS_UINT32 ulSize  -- 
   : 
     : VOS_VOID*          -- 
   :
   :

       :
  1.       : 20130604
           : l00198894
       : V3R3 Share-PDP
*****************************************************************************/
VOS_VOID* ADS_FILTER_HeapAlloc(VOS_UINT32 ulSize)
{
    VOS_VOID                           *ret = VOS_NULL_PTR;

    if ((ulSize == 0) || (ulSize > 1024))
    {
        return VOS_NULL_PTR;
    }

    ret = (VOS_VOID *)kmalloc(ulSize, GFP_KERNEL);

    return ret;
}

/*****************************************************************************
     : ADS_FILTER_HeapFree
   : ADS
   : VOS_VOID *pAddr    -- 
   : 
     : 
   :
   :

       :
  1.       : 20130604
           : l00198894
       : V3R3 Share-PDP
*****************************************************************************/
VOS_VOID ADS_FILTER_HeapFree(VOS_VOID *pAddr)
{
    if (pAddr == NULL)
    {
        return;
    }

    kfree(pAddr);

    return;
}

/*****************************************************************************
     : ADS_FILTER_AddFilter
   : 
   : ADS_FILTER_IPV4_INFO_STRU *pstFilter   -- 
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20130604
           : l00198894
       : V3R3 Share-PDP
*****************************************************************************/
VOS_VOID ADS_FILTER_AddFilter(
    ADS_FILTER_IPV4_INFO_STRU          *pstFilter)
{
    ADS_FILTER_NODE_STRU               *pstNode         = VOS_NULL_PTR;
    HI_LIST_S                          *pstListHead     = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;

    /*  */
    pstNode = (ADS_FILTER_NODE_STRU *)ADS_FILTER_MALLOC(sizeof(ADS_FILTER_NODE_STRU));
    if (VOS_NULL_PTR == pstNode)
    {
        ADS_ERROR_LOG(ACPU_PID_ADS_UL, "ADS_FILTER_AddFilter: Malloc Failed!");
        return;
    }

    TAF_MEM_SET_S(pstNode, (VOS_SIZE_T)sizeof(ADS_FILTER_NODE_STRU), 0x00, (VOS_SIZE_T)sizeof(ADS_FILTER_NODE_STRU));
    pstNode->stFilter = *pstFilter;

    /*  */
    ucIndex = ADS_FILTER_GET_INDEX(pstFilter);

    /*  */
    pstListHead = ADS_FILTER_GET_LIST(ucIndex);

    /*  */
    msp_list_add_tail(&pstNode->stList, pstListHead);

    return;
}

/*****************************************************************************
     : ADS_FILTER_ResetLists
   : ADS
   : 
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20130604
           : l00198894
       : V3R3 Share-PDP
*****************************************************************************/
VOS_VOID ADS_FILTER_ResetLists(VOS_VOID)
{
    VOS_UINT32                          ulLoop;
    HI_LIST_S                          *pstMe       = VOS_NULL_PTR;
    HI_LIST_S                          *pstTmp      = VOS_NULL_PTR;
    HI_LIST_S                          *pstListHead = VOS_NULL_PTR;
    ADS_FILTER_NODE_STRU               *pstNode     = VOS_NULL_PTR;

    /*  */
    for (ulLoop = 0; ulLoop < ADS_FILTER_MAX_LIST_NUM; ulLoop++)
    {
        pstListHead = ADS_FILTER_GET_LIST(ulLoop);
        msp_list_for_each_safe(pstMe, pstTmp, pstListHead)
        {
            pstNode = msp_list_entry(pstMe, ADS_FILTER_NODE_STRU, stList);

            /*  */
            msp_list_del(&pstNode->stList);

            /*  */
            ADS_FILTER_FREE(pstNode);
        }
    }

    return;
}

/*****************************************************************************
     : ADS_FILTER_Reset
   : 
   : 
   : 
     : 
   :
   :

       :
  1.       : 20130604
           : l00198894
       : V3R3 Share-PDP
*****************************************************************************/
VOS_VOID ADS_FILTER_Reset(VOS_VOID)
{
    /* IPv6 */
    ADS_FILTER_ResetIPv6Addr();

    /*  */
    ADS_FILTER_ResetLists();

    return;
}

/*****************************************************************************
     : ADS_FILTER_Match
   : 
   : HI_LIST_S                 *pstListHead     -- 
             ADS_FILTER_IPV4_INFO_STRU *pstFilter       -- 
   : 
     : VOS_TRUE   -- 
             VOS_FALSE  -- 
   :
   :

       :
  1.       : 20130604
           : l00198894
       : V3R3 Share-PDP
*****************************************************************************/
VOS_UINT32 ADS_FILTER_IsInfoMatch(
    ADS_FILTER_IPV4_INFO_STRU          *pstFilter1,
    ADS_FILTER_IPV4_INFO_STRU          *pstFilter2)
{
    VOS_UINT32                          ulRet;

    ulRet = VOS_FALSE;

    /*  */
    if ( !ADS_FILTER_IS_IPHDR_MATCH(&pstFilter1->stIPHeader, &pstFilter2->stIPHeader) )
    {
        return ulRet;
    }

    /*  */
    switch(pstFilter1->enPktType)
    {
        case ADS_FILTER_PKT_TYPE_TCP:
            /* TCP */
            if (ADS_FILTER_IS_TCP_PKT_MATCH(&pstFilter1->unFilter.stTcpFilter,
                                            &pstFilter2->unFilter.stTcpFilter))
            {
                ulRet = VOS_TRUE;
            }
            break;
        case ADS_FILTER_PKT_TYPE_UDP:
            /* UDP */
            if (ADS_FILTER_IS_UDP_PKT_MATCH(&pstFilter1->unFilter.stUdpFilter,
                                            &pstFilter2->unFilter.stUdpFilter))
            {
                ulRet = VOS_TRUE;
            }
            break;
        case ADS_FILTER_PKT_TYPE_ICMP:
            /* ICMP */
            if (ADS_FILTER_IS_ICMP_PKT_MATCH(&pstFilter1->unFilter.stIcmpFilter,
                                             &pstFilter2->unFilter.stIcmpFilter))
            {
                ulRet = VOS_TRUE;
            }
            break;
        case ADS_FILTER_PKT_TYPE_FRAGMENT:
            /*  */
            if (ADS_FILTER_IS_FRAGMENT_MATCH(&pstFilter1->unFilter.stFragmentFilter,
                                             &pstFilter2->unFilter.stFragmentFilter))
            {
                ulRet = VOS_TRUE;
            }
            break;
        default:
            break;
    }

    return ulRet;
}

/*****************************************************************************
     : ADS_FILTER_Match
   : 
   : ADS_FILTER_IPV4_INFO_STRU *pstFilter       -- 
   : 
     : VOS_TRUE   -- 
             VOS_FALSE  -- 
   :
   :

       :
  1.       : 20130604
           : l00198894
       : V3R3 Share-PDP
*****************************************************************************/
VOS_UINT32 ADS_FILTER_Match(
    ADS_FILTER_IPV4_INFO_STRU          *pstFilter)
{
    ADS_FILTER_NODE_STRU               *pstNode     = VOS_NULL_PTR;
    HI_LIST_S                          *pstMe       = VOS_NULL_PTR;
    HI_LIST_S                          *pstListTmp  = VOS_NULL_PTR;
    HI_LIST_S                          *pstListHead = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    ulRet   = VOS_FALSE;

    /*  */
    ucIndex = ADS_FILTER_GET_INDEX(pstFilter);

    /*  */
    pstListHead = ADS_FILTER_GET_LIST(ucIndex);

    /*  */
    msp_list_for_each_safe(pstMe, pstListTmp, pstListHead)
    {
        pstNode = msp_list_entry(pstMe, ADS_FILTER_NODE_STRU, stList);

        /*  */
        if (ADS_FILTER_IS_AGED(pstNode->stFilter.ulTmrCnt))
        {
            /*  */
            msp_list_del(&pstNode->stList);

            /*  */
            ADS_FILTER_FREE(pstNode);

            continue;
        }

        /*  */
        if ( (pstFilter->enPktType != pstNode->stFilter.enPktType)
          || (VOS_TRUE == ulRet) )
        {
            /*  */
            continue;
        }

        /*  */
        ulRet = ADS_FILTER_IsInfoMatch(pstFilter, &pstNode->stFilter);

        /*  */
        if (VOS_TRUE == ulRet)
        {
            pstNode->stFilter.ulTmrCnt = ADS_GET_CURR_KERNEL_TIME();
        }
    }

    return ulRet;
}

/*****************************************************************************
     : ADS_FILTER_SaveIPAddrInfo
   : IP
   : ADS_FILTER_IP_ADDR_INFO_STRU       *pstFilterIpAddr    -- IP
   : 
     : 
   :
   :

       :
  1.       : 20130604
           : l00198894
       : V3R3 Share-PDP
*****************************************************************************/
VOS_VOID ADS_FILTER_SaveIPAddrInfo(
    ADS_FILTER_IP_ADDR_INFO_STRU       *pstFilterIpAddr)
{
    /* IPv6IPv6 */
    if (VOS_TRUE == pstFilterIpAddr->bitOpIpv6Addr)
    {
        TAF_MEM_CPY_S(ADS_FILTER_GET_IPV6_ADDR()->aucIpAddr,
                   ADS_IPV6_ADDR_LEN,
                   pstFilterIpAddr->aucIpv6Addr,
                   ADS_IPV6_ADDR_LEN);
    }

    return;
}

/*****************************************************************************
     : ADS_FILTER_DecodeUlPacket
   : ADSTCP\UDP\ICMP
   : IMM_ZC_STRU                *pstData       -- 
   : ADS_FILTER_IPV4_INFO_STRU  *pstIPv4Filter -- 
     : VOS_OK     -- 
             VOS_ERR    -- 
   :
   :

       :
  1.       : 20130604
           : l00198894
       : V3R3 Share-PDP
*****************************************************************************/
VOS_UINT32 ADS_FILTER_DecodeUlPacket(
    IMM_ZC_STRU                        *pstData,
    ADS_FILTER_IPV4_INFO_STRU          *pstIPv4Filter)
{
    ADS_IPV4_HDR_STRU                  *pstIPv4Hdr      = VOS_NULL_PTR;
    ADS_UDP_HDR_STRU                   *pstUdpHdr       = VOS_NULL_PTR;
    ADS_TCP_HDR_STRU                   *pstTcpHdr       = VOS_NULL_PTR;
    ADS_ICMP_HDR_STRU                  *pstIcmpHdr      = VOS_NULL_PTR;

    /* IP */
    pstIPv4Hdr  = (ADS_IPV4_HDR_STRU *)IMM_ZcGetDataPtr(pstData);

    /* (: Offset0):
                         MF      Offset
                 0         0
               1         0
             1         0
               0         0 */
    if (0 != (pstIPv4Hdr->usFlags_fo & VOS_HTONS(ADS_IP_OFFSET)))
    {
        /*  */
        ADS_FILTER_DBG_STATISTIC(ADS_FILTER_ORIG_PKT_UL_IPV4_NOT_FIRST_FRAGMENT, 1);
        return VOS_ERR;
    }


    /*  */
    pstIPv4Filter->ulTmrCnt                 = ADS_GET_CURR_KERNEL_TIME();

    pstIPv4Filter->stIPHeader.ulSrcAddr     = pstIPv4Hdr->unSrcAddr.ulIpAddr;
    pstIPv4Filter->stIPHeader.ulDstAddr     = pstIPv4Hdr->unDstAddr.ulIpAddr;
    pstIPv4Filter->stIPHeader.ucProtocol    = pstIPv4Hdr->ucProtocol;

    /* TCP\UDP\ICMP:TCPUDPTCP/UDP */
    switch (pstIPv4Hdr->ucProtocol)
    {
        case ADS_IPPROTO_ICMP:
            pstIcmpHdr = (ADS_ICMP_HDR_STRU *)((VOS_UINT8 *)pstIPv4Hdr + ADS_FILTER_IPV4_HDR_LEN);

            /* PING ECHO REQICMPICMP */
            if (ADS_ICMP_ECHOREQUEST != pstIcmpHdr->ucType)
            {
                /* ICMP */
                ADS_FILTER_DBG_STATISTIC(ADS_FILTER_ORIG_PKT_UL_IPV4_NOT_SUPPORT, 1);
                return VOS_ERR;
            }

            pstIPv4Filter->enPktType = ADS_FILTER_PKT_TYPE_ICMP;
            pstIPv4Filter->unFilter.stIcmpFilter.usIdentifier = pstIcmpHdr->unIcmp.stIcmpEcho.usIdentifier;
            pstIPv4Filter->unFilter.stIcmpFilter.usSeqNum     = pstIcmpHdr->unIcmp.stIcmpEcho.usSeqNum;

            /*  */
            ADS_FILTER_DBG_STATISTIC(ADS_FILTER_ORIG_PKT_UL_IPV4_ECHOREQ, 1);
            return VOS_OK;

        case ADS_IPPROTO_TCP:
            pstIPv4Filter->enPktType = ADS_FILTER_PKT_TYPE_TCP;
            pstTcpHdr = (ADS_TCP_HDR_STRU *)((VOS_UINT8 *)pstIPv4Hdr + ADS_FILTER_IPV4_HDR_LEN);
            pstIPv4Filter->unFilter.stTcpFilter.usSrcPort = pstTcpHdr->usSrcPort;
            pstIPv4Filter->unFilter.stTcpFilter.usDstPort = pstTcpHdr->usDstPort;

            /*  */
            ADS_FILTER_DBG_STATISTIC(ADS_FILTER_ORIG_PKT_UL_IPV4_TCP, 1);
            return VOS_OK;

        case ADS_IPPROTO_UDP:
            pstIPv4Filter->enPktType = ADS_FILTER_PKT_TYPE_UDP;
            pstUdpHdr = (ADS_UDP_HDR_STRU *)((VOS_UINT8 *)pstIPv4Hdr + ADS_FILTER_IPV4_HDR_LEN);
            pstIPv4Filter->unFilter.stUdpFilter.usSrcPort = pstUdpHdr->usSrcPort;
            pstIPv4Filter->unFilter.stUdpFilter.usDstPort = pstUdpHdr->usDstPort;

            /*  */
            ADS_FILTER_DBG_STATISTIC(ADS_FILTER_ORIG_PKT_UL_IPV4_UDP, 1);
            return VOS_OK;

        default:
            /* IPv4 */
            /*  */
            ADS_FILTER_DBG_STATISTIC(ADS_FILTER_ORIG_PKT_UL_IPV4_NOT_SUPPORT, 1);
            break;
    }

    return VOS_ERR;
}

/*****************************************************************************
     : ADS_FILTER_ProcUlPacket
   : ADS
   : IMM_ZC_STRU               *pstData     -- 
             ADS_PKT_TYPE_ENUM_UINT8    enIpType    -- IP
   : 
     : 
   :
   :

       :
  1.       : 20130604
           : l00198894
       : V3R3 Share-PDP
*****************************************************************************/
VOS_VOID ADS_FILTER_ProcUlPacket(
    IMM_ZC_STRU                        *pstData,
    ADS_PKT_TYPE_ENUM_UINT8             enIpType)
{
    ADS_FILTER_IPV4_INFO_STRU           stIPv4Filter;
    VOS_UINT32                          ulDecodeRet;
    VOS_UINT32                          ulRet;

    /*  */
    TAF_MEM_SET_S(&stIPv4Filter, sizeof(stIPv4Filter), 0x00 ,sizeof(stIPv4Filter));

    /* IPv4IPv6 */
    if (ADS_PKT_TYPE_IPV4 != enIpType)
    {
        ADS_FILTER_DBG_STATISTIC(ADS_FILTER_ORIG_PKT_UL_IPV6_PKT, 1);
        return;
    }

    /*  */
    ulDecodeRet = ADS_FILTER_DecodeUlPacket(pstData, &stIPv4Filter);
    if (VOS_OK != ulDecodeRet)
    {
        /*  */
        return;
    }

    /*  */
    ulRet       = ADS_FILTER_Match(&stIPv4Filter);
    if (VOS_TRUE != ulRet)
    {
        /* IP */
        ADS_FILTER_AddFilter(&stIPv4Filter);
    }

    return;
}

/*****************************************************************************
     : ADS_FILTER_DecodeDlIPv4NotFirstFragPacket
   : ()
   : ADS_IPV4_HDR_STRU                        *pstIPv4Hdr     -- 
   : ADS_FILTER_IPV4_INFO_STRU                *pstIPv4Filter  -- 
     : VOS_VOID
   :
   :

       :
  1.       : 20130614
           : L47619
       : V3R3 Share-PDP
*****************************************************************************/
VOS_VOID ADS_FILTER_DecodeDlIPv4NotFirstFragPacket(
    ADS_IPV4_HDR_STRU                  *pstIPv4Hdr,
    ADS_FILTER_IPV4_INFO_STRU          *pstIPv4Filter)
{
    TAF_MEM_SET_S(pstIPv4Filter, sizeof(ADS_FILTER_IPV4_INFO_STRU), 0x00, sizeof(ADS_FILTER_IPV4_INFO_STRU));

    /*  */
    pstIPv4Filter->enPktType = ADS_FILTER_PKT_TYPE_FRAGMENT;
    pstIPv4Filter->ulTmrCnt  = ADS_GET_CURR_KERNEL_TIME();
    pstIPv4Filter->stIPHeader.ulSrcAddr  = pstIPv4Hdr->unDstAddr.ulIpAddr;
    pstIPv4Filter->stIPHeader.ulDstAddr  = pstIPv4Hdr->unSrcAddr.ulIpAddr;
    pstIPv4Filter->stIPHeader.ucProtocol = pstIPv4Hdr->ucProtocol;
    pstIPv4Filter->unFilter.stFragmentFilter.usIdentification = pstIPv4Hdr->usIdentification;

    return;
}

/*****************************************************************************
     : ADS_FILTER_DecodeDlIPv4EchoReplyPacket
   : ECHO REPLY
   : ADS_IPV4_HDR_STRU                        *pstIPv4Hdr     -- 
   : ADS_FILTER_IPV4_INFO_STRU                *pstIPv4Filter  -- 
     : VOS_OK     -- 
             VOS_ERR    -- 
   :
   :

       :
  1.       : 20130614
           : L47619
       : V3R3 Share-PDP
*****************************************************************************/
VOS_UINT32 ADS_FILTER_DecodeDlIPv4EchoReplyPacket(
    ADS_IPV4_HDR_STRU                  *pstIPv4Hdr,
    ADS_FILTER_IPV4_INFO_STRU          *pstIPv4Filter)
{
    ADS_ICMP_HDR_STRU                  *pstIcmpHdr      = VOS_NULL_PTR;

    /* ICMP */
    pstIcmpHdr = (ADS_ICMP_HDR_STRU *)((VOS_UINT8 *)pstIPv4Hdr + ADS_FILTER_IPV4_HDR_LEN);

    pstIPv4Filter->enPktType = ADS_FILTER_PKT_TYPE_ICMP;
    pstIPv4Filter->ulTmrCnt  = ADS_GET_CURR_KERNEL_TIME();
    pstIPv4Filter->stIPHeader.ulSrcAddr  = pstIPv4Hdr->unDstAddr.ulIpAddr;
    pstIPv4Filter->stIPHeader.ulDstAddr  = pstIPv4Hdr->unSrcAddr.ulIpAddr;
    pstIPv4Filter->stIPHeader.ucProtocol = pstIPv4Hdr->ucProtocol;
    pstIPv4Filter->unFilter.stIcmpFilter.usIdentifier = pstIcmpHdr->unIcmp.stIcmpEcho.usIdentifier;
    pstIPv4Filter->unFilter.stIcmpFilter.usSeqNum = pstIcmpHdr->unIcmp.stIcmpEcho.usSeqNum;

    return VOS_OK;
}

/*****************************************************************************
     : ADS_FILTER_DecodeDlIPv4IcmpErrorPacket
   : ICMP
   : ADS_IPV4_HDR_STRU                        *pstIPv4Hdr     -- 
   : ADS_FILTER_IPV4_INFO_STRU                *pstIPv4Filter  -- 
     : VOS_OK     -- 
             VOS_ERR    -- 
   :
   :

       :
  1.       : 20130614
           : L47619
       : V3R3 Share-PDP
*****************************************************************************/
VOS_UINT32 ADS_FILTER_DecodeDlIPv4IcmpErrorPacket(
    ADS_IPV4_HDR_STRU                  *pstIPv4Hdr,
    ADS_FILTER_IPV4_INFO_STRU          *pstIPv4Filter)
{
    ADS_IPV4_HDR_STRU                  *pstIcmpIPv4Hdr  = VOS_NULL_PTR;
    ADS_TCP_HDR_STRU                   *pstTcpHdr       = VOS_NULL_PTR;
    ADS_UDP_HDR_STRU                   *pstUdpHdr       = VOS_NULL_PTR;

    /* ICMPIP */
    pstIcmpIPv4Hdr = (ADS_IPV4_HDR_STRU *)(((VOS_UINT8 *)pstIPv4Hdr + ADS_FILTER_IPV4_HDR_LEN + ADS_FILTER_ICMP_HDR_LEN));

    pstIPv4Filter->ulTmrCnt  = ADS_GET_CURR_KERNEL_TIME();
    pstIPv4Filter->stIPHeader.ulSrcAddr  = pstIcmpIPv4Hdr->unSrcAddr.ulIpAddr;
    pstIPv4Filter->stIPHeader.ulDstAddr  = pstIcmpIPv4Hdr->unDstAddr.ulIpAddr;
    pstIPv4Filter->stIPHeader.ucProtocol = pstIcmpIPv4Hdr->ucProtocol;

    if (ADS_IPPROTO_TCP == pstIcmpIPv4Hdr->ucProtocol)
    {
        pstIPv4Filter->enPktType = ADS_FILTER_PKT_TYPE_TCP;
        pstTcpHdr = (ADS_TCP_HDR_STRU *)((VOS_UINT8 *)pstIcmpIPv4Hdr + ADS_FILTER_IPV4_HDR_LEN);
        pstIPv4Filter->unFilter.stTcpFilter.usSrcPort = pstTcpHdr->usSrcPort;
        pstIPv4Filter->unFilter.stTcpFilter.usDstPort = pstTcpHdr->usDstPort;
    }
    else if (ADS_IPPROTO_UDP == pstIcmpIPv4Hdr->ucProtocol)
    {
        pstIPv4Filter->enPktType = ADS_FILTER_PKT_TYPE_UDP;
        pstUdpHdr = (ADS_UDP_HDR_STRU *)((VOS_UINT8 *)pstIcmpIPv4Hdr + ADS_FILTER_IPV4_HDR_LEN);
        pstIPv4Filter->unFilter.stUdpFilter.usSrcPort = pstUdpHdr->usSrcPort;
        pstIPv4Filter->unFilter.stUdpFilter.usDstPort = pstUdpHdr->usDstPort;
    }
    else
    {
        /* TCP/UDPHOST */
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
     : ADS_FILTER_DecodeDlIPv4TcpPacket
   : TCP
   : ADS_IPV4_HDR_STRU                        *pstIPv4Hdr     -- 
   : ADS_FILTER_IPV4_INFO_STRU                *pstIPv4Filter  -- 
     : VOS_VOID
   :
   :

       :
  1.       : 20130614
           : L47619
       : V3R3 Share-PDP
*****************************************************************************/
VOS_VOID ADS_FILTER_DecodeDlIPv4TcpPacket(
    ADS_IPV4_HDR_STRU                  *pstIPv4Hdr,
    ADS_FILTER_IPV4_INFO_STRU          *pstIPv4Filter)
{
    ADS_TCP_HDR_STRU                   *pstTcpHdr       = VOS_NULL_PTR;

    /* TCP */
    pstTcpHdr = (ADS_TCP_HDR_STRU *)((VOS_UINT8 *)pstIPv4Hdr + ADS_FILTER_IPV4_HDR_LEN);

    pstIPv4Filter->enPktType = ADS_FILTER_PKT_TYPE_TCP;
    pstIPv4Filter->ulTmrCnt  = ADS_GET_CURR_KERNEL_TIME();
    pstIPv4Filter->stIPHeader.ulSrcAddr  = pstIPv4Hdr->unDstAddr.ulIpAddr;
    pstIPv4Filter->stIPHeader.ulDstAddr  = pstIPv4Hdr->unSrcAddr.ulIpAddr;
    pstIPv4Filter->stIPHeader.ucProtocol = pstIPv4Hdr->ucProtocol;
    pstIPv4Filter->unFilter.stTcpFilter.usSrcPort = pstTcpHdr->usDstPort;
    pstIPv4Filter->unFilter.stTcpFilter.usDstPort = pstTcpHdr->usSrcPort;

    return;
}

/*****************************************************************************
     : ADS_FILTER_DecodeDlIPv4UdpPacket
   : UDP
   : ADS_IPV4_HDR_STRU                        *pstIPv4Hdr     -- 
   : ADS_FILTER_IPV4_INFO_STRU                *pstIPv4Filter  -- 
     : VOS_VOID
   :
   :

       :
  1.       : 20130614
           : L47619
       : V3R3 Share-PDP
*****************************************************************************/
VOS_VOID ADS_FILTER_DecodeDlIPv4UdpPacket(
    ADS_IPV4_HDR_STRU                  *pstIPv4Hdr,
    ADS_FILTER_IPV4_INFO_STRU          *pstIPv4Filter)
{
    ADS_UDP_HDR_STRU                   *pstUdpHdr       = VOS_NULL_PTR;

    /* UDP */
    pstUdpHdr = (ADS_UDP_HDR_STRU *)((VOS_UINT8 *)pstIPv4Hdr + ADS_FILTER_IPV4_HDR_LEN);

    pstIPv4Filter->enPktType = ADS_FILTER_PKT_TYPE_UDP;
    pstIPv4Filter->ulTmrCnt  = ADS_GET_CURR_KERNEL_TIME();
    pstIPv4Filter->stIPHeader.ulSrcAddr  = pstIPv4Hdr->unDstAddr.ulIpAddr;
    pstIPv4Filter->stIPHeader.ulDstAddr  = pstIPv4Hdr->unSrcAddr.ulIpAddr;
    pstIPv4Filter->stIPHeader.ucProtocol = pstIPv4Hdr->ucProtocol;
    pstIPv4Filter->unFilter.stUdpFilter.usSrcPort = pstUdpHdr->usDstPort;
    pstIPv4Filter->unFilter.stUdpFilter.usDstPort = pstUdpHdr->usSrcPort;

    return;
}

/*****************************************************************************
     : ADS_FILTER_DecodeDlIPv4FragPacket
   : 
   : ADS_IPV4_HDR_STRU                        *pstIPv4Hdr     -- 
   : ADS_FILTER_IPV4_INFO_STRU                *pstIPv4Filter  -- 
             ADS_FILTER_ORIG_PKT_ENUM_UINT32          *penOrigPktType -- 
     : VOS_OK     -- 
             VOS_ERR    -- 
   :
   :

       :
  1.       : 20130618
           : L47619
       : V3R3 Share-PDP
*****************************************************************************/
VOS_UINT32 ADS_FILTER_DecodeDlIPv4FragPacket(
    ADS_IPV4_HDR_STRU                  *pstIPv4Hdr,
    ADS_FILTER_IPV4_INFO_STRU          *pstIPv4Filter,
    ADS_FILTER_ORIG_PKT_ENUM_UINT32    *penOrigPktType)
{
    VOS_UINT32                          ulRet;

    /* (Offset0).
        :
                         MF      Offset
               1         0
             1         0
               0         0 */
    if (0 == (pstIPv4Hdr->usFlags_fo & VOS_HTONS(ADS_IP_OFFSET)))
    {
        /* (TCPUDP) */
        switch (pstIPv4Hdr->ucProtocol)
        {
            case ADS_IPPROTO_TCP:
                /*  */
                *penOrigPktType = ADS_FILTER_ORIG_PKT_DL_IPV4_FIRST_FRAGMENT;

                /* TCP */
                ADS_FILTER_DecodeDlIPv4TcpPacket(pstIPv4Hdr, pstIPv4Filter);

                ulRet = VOS_OK;
                break;

            case ADS_IPPROTO_UDP:
                /*  */
                *penOrigPktType = ADS_FILTER_ORIG_PKT_DL_IPV4_FIRST_FRAGMENT;

                /* UDP */
                ADS_FILTER_DecodeDlIPv4UdpPacket(pstIPv4Hdr, pstIPv4Filter);

                ulRet = VOS_OK;
                break;

            default:
                /* HOST */
                ulRet = VOS_ERR;
                break;
        }
    }
    else
    {
        /* "", */
        *penOrigPktType = ADS_FILTER_ORIG_PKT_DL_IPV4_NOT_FIRST_FRAGMENT;

        /*  */
        ADS_FILTER_DecodeDlIPv4NotFirstFragPacket(pstIPv4Hdr, pstIPv4Filter);

        ulRet = VOS_OK;
    }

    return ulRet;
}

/*****************************************************************************
     : ADS_FILTER_DecodeDlIPv4Packet
   : TCP\UDP\ICMP(ECHO REPLYICMP)\
             
             : 
   : ADS_IPV4_HDR_STRU                        *pstIPv4Hdr,    -- 
   : ADS_FILTER_IPV4_INFO_STRU                *pstIPv4Filter  -- 
             ADS_FILTER_ORIG_PKT_ENUM_UINT32          *penOrigPktType -- 
     : VOS_OK     -- 
             VOS_ERR    -- 
   :
   :

       :
  1.       : 20130613
           : L47619
       : V3R3 Share-PDP
*****************************************************************************/
VOS_UINT32 ADS_FILTER_DecodeDlIPv4Packet(
    ADS_IPV4_HDR_STRU                  *pstIPv4Hdr,
    ADS_FILTER_IPV4_INFO_STRU          *pstIPv4Filter,
    ADS_FILTER_ORIG_PKT_ENUM_UINT32    *penOrigPktType)
{
    ADS_ICMP_HDR_STRU                                      *pstIcmpHdr           = VOS_NULL_PTR;
    ADS_FILTER_DECODE_DL_ICMP_FUNC                          pDecodeDlIcmpFunc    = VOS_NULL_PTR;
    ADS_FILTER_DECODE_DL_ICMP_FUNC_STRU                    *pDecodeDlIcmpFuncTbl = VOS_NULL_PTR;
    VOS_UINT32                                              ulRet                = VOS_ERR;

    /* "".:
                         MF      Offset
                 0         0
               1         0
             1         0
               0         0 */
    if (0 != (pstIPv4Hdr->usFlags_fo & VOS_HTONS(ADS_IP_MF | ADS_IP_OFFSET)))
    {
        return ADS_FILTER_DecodeDlIPv4FragPacket(pstIPv4Hdr, pstIPv4Filter, penOrigPktType);
    }

    /* TCP\UDP\ICMP(ECHO REPLYICMP) */
    switch (pstIPv4Hdr->ucProtocol)
    {
        case ADS_IPPROTO_ICMP:
            pstIcmpHdr = (ADS_ICMP_HDR_STRU *)((VOS_UINT8 *)pstIPv4Hdr + ADS_FILTER_IPV4_HDR_LEN);

            if (pstIcmpHdr->ucType < ADS_FILTER_GET_DL_ICMP_FUNC_TBL_SIZE())
            {
                pDecodeDlIcmpFuncTbl = ADS_FILTER_GET_DL_ICMP_FUNC_TBL_ADDR(pstIcmpHdr->ucType);
                pDecodeDlIcmpFunc = pDecodeDlIcmpFuncTbl->pFunc;
                if (VOS_NULL_PTR != pDecodeDlIcmpFunc)
                {
                    /*  */
                    *penOrigPktType = pDecodeDlIcmpFuncTbl->enOrigPktType;

                    /* ICMP */
                    ulRet = pDecodeDlIcmpFunc(pstIPv4Hdr, pstIPv4Filter);
                }
            }
            break;

        case ADS_IPPROTO_TCP:
            /*  */
            *penOrigPktType = ADS_FILTER_ORIG_PKT_DL_IPV4_TCP;

            /* TCP */
            ADS_FILTER_DecodeDlIPv4TcpPacket(pstIPv4Hdr, pstIPv4Filter);

            ulRet = VOS_OK;
            break;

        case ADS_IPPROTO_UDP:
            /*  */
            *penOrigPktType = ADS_FILTER_ORIG_PKT_DL_IPV4_UDP;

            /* UDP */
            ADS_FILTER_DecodeDlIPv4UdpPacket(pstIPv4Hdr, pstIPv4Filter);

            ulRet = VOS_OK;
            break;

        default:
            break;
    }

    return ulRet;
}

/*****************************************************************************
     : ADS_FILTER_ProcDlIPv4Packet
   : ADSIPv4
   : IMM_ZC_STRU               *pstData     -- 
   : 
     : VOS_OK   -- 
             VOS_ERR  -- 
   :
   :

       :
  1.       : 20130604
           : l00198894
       : V3R3 Share-PDP
*****************************************************************************/
VOS_UINT32 ADS_FILTER_ProcDlIPv4Packet(
    IMM_ZC_STRU                        *pstData)
{
    ADS_IPV4_HDR_STRU                  *pstIPv4Hdr      = VOS_NULL_PTR;
    ADS_FILTER_IPV4_INFO_STRU           stIPv4Filter;
    VOS_UINT32                          ulDecodeRet;
    VOS_UINT32                          ulRet;
    ADS_FILTER_ORIG_PKT_ENUM_UINT32     enOrigPktType;

    /* IPV4 */
    pstIPv4Hdr  = (ADS_IPV4_HDR_STRU *)IMM_ZcGetDataPtr(pstData);

    /*  */
    TAF_MEM_SET_S(&stIPv4Filter, sizeof(stIPv4Filter), 0x00, sizeof(ADS_FILTER_IPV4_INFO_STRU));
    ulDecodeRet = ADS_FILTER_DecodeDlIPv4Packet(pstIPv4Hdr, &stIPv4Filter, &enOrigPktType);
    if (VOS_OK != ulDecodeRet)
    {
        /* HOST */
        return VOS_ERR;
    }

    /*  */
    ulRet       = ADS_FILTER_Match(&stIPv4Filter);
    if (VOS_TRUE == ulRet)
    {
        /* 
             */
        if (ADS_FILTER_ORIG_PKT_DL_IPV4_FIRST_FRAGMENT == enOrigPktType)
        {
            ADS_FILTER_DecodeDlIPv4NotFirstFragPacket(pstIPv4Hdr, &stIPv4Filter);

            /*  */
            ADS_FILTER_AddFilter(&stIPv4Filter);
        }

        ADS_FILTER_DBG_STATISTIC(enOrigPktType, 1);

        return VOS_OK;
    }

    return VOS_ERR;
}

/*****************************************************************************
     : ADS_FILTER_ProcDlIPv6Packet
   : ADSIPv6
   : IMM_ZC_STRU               *pstData     -- 
   : 
     : VOS_OK   -- 
             VOS_ERR  -- 
   :
   :

       :
  1.       : 20130614
           : L47619
       : V3R3 Share-PDP
*****************************************************************************/
VOS_UINT32 ADS_FILTER_ProcDlIPv6Packet(
    IMM_ZC_STRU                        *pstData)
{
    ADS_IPV6_HDR_STRU                  *pstIPv6Hdr      = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;

    /* IPV6 */
    pstIPv6Hdr = (ADS_IPV6_HDR_STRU *)IMM_ZcGetDataPtr(pstData);

    /* DEVICE */
    if (ADS_FILTER_IS_IPV6_ADDR_IDENTICAL(ADS_FILTER_GET_IPV6_ADDR(), &(pstIPv6Hdr->unDstAddr)))
    {
        ADS_FILTER_DBG_STATISTIC(ADS_FILTER_ORIG_PKT_DL_IPV6_PKT, 1);

        ulRet = VOS_OK;
    }
    else
    {
        ulRet = VOS_ERR;
    }

    return ulRet;
}

/*****************************************************************************
     : ADS_FILTER_ProcDlPacket
   : ADS
   : IMM_ZC_STRU               *pstData     -- 
             ADS_PKT_TYPE_ENUM_UINT8    enIpType    -- IP
   : 
     : VOS_OK     -- 
             VOS_ERR    -- 
   :
   :

       :
  1.       : 20130604
           : l00198894
       : V3R3 Share-PDP
*****************************************************************************/
VOS_UINT32 ADS_FILTER_ProcDlPacket(
    IMM_ZC_STRU                        *pstData,
    ADS_PKT_TYPE_ENUM_UINT8             enIpType)
{
    VOS_UINT32                          ulRet;

    /*  */
    ulRet   = VOS_ERR;

    /* IP */
    switch (enIpType)
    {
        case ADS_PKT_TYPE_IPV4:
            /* IPv4 */
            ulRet = ADS_FILTER_ProcDlIPv4Packet(pstData);
            break;

        case ADS_PKT_TYPE_IPV6:
            /* IPv6IP */
            ulRet = ADS_FILTER_ProcDlIPv6Packet(pstData);
            break;

        default:
            break;
    }

    return ulRet;
}


/*****************************************************************************
     : ADS_FILTER_ShowStatisticInfo
   : 
   : VOS_VOID
   : VOS_VOID
     : VOS_VOID
   :
   :

       :
  1.       : 2013614
           : L47619
       : V3R3 Share-PDP
*****************************************************************************/
VOS_VOID ADS_FILTER_ShowStatisticInfo(VOS_VOID)
{
    PS_PRINTF("\n********************ADS FILTER ************************\n");
    PS_PRINTF("IPv4TCP              %d\n", ADS_FILTER_DBG_GET_STATS_BY_INDEX(ADS_FILTER_ORIG_PKT_UL_IPV4_TCP));
    PS_PRINTF("IPv4UDP              %d\n", ADS_FILTER_DBG_GET_STATS_BY_INDEX(ADS_FILTER_ORIG_PKT_UL_IPV4_UDP));
    PS_PRINTF("IPv4Echo Req         %d\n", ADS_FILTER_DBG_GET_STATS_BY_INDEX(ADS_FILTER_ORIG_PKT_UL_IPV4_ECHOREQ));
    PS_PRINTF("IPv4()     %d\n", ADS_FILTER_DBG_GET_STATS_BY_INDEX(ADS_FILTER_ORIG_PKT_UL_IPV4_NOT_FIRST_FRAGMENT));
    PS_PRINTF("IPv4     %d\n", ADS_FILTER_DBG_GET_STATS_BY_INDEX(ADS_FILTER_ORIG_PKT_UL_IPV4_NOT_SUPPORT));
    PS_PRINTF("IPv6                 %d\n", ADS_FILTER_DBG_GET_STATS_BY_INDEX(ADS_FILTER_ORIG_PKT_UL_IPV6_PKT));

    PS_PRINTF("********************ADS FILTER ************************\n");
    PS_PRINTF("IPv4TCP          %d\n", ADS_FILTER_DBG_GET_STATS_BY_INDEX(ADS_FILTER_ORIG_PKT_DL_IPV4_TCP));
    PS_PRINTF("IPv4UDP          %d\n", ADS_FILTER_DBG_GET_STATS_BY_INDEX(ADS_FILTER_ORIG_PKT_DL_IPV4_UDP));
    PS_PRINTF("IPv4Echo Reply   %d\n", ADS_FILTER_DBG_GET_STATS_BY_INDEX(ADS_FILTER_ORIG_PKT_DL_IPV4_ECHOREPLY));
    PS_PRINTF("IPv4ICMP %d\n", ADS_FILTER_DBG_GET_STATS_BY_INDEX(ADS_FILTER_ORIG_PKT_DL_IPV4_ICMPERROR));
    PS_PRINTF("IPv4     %d\n", ADS_FILTER_DBG_GET_STATS_BY_INDEX(ADS_FILTER_ORIG_PKT_DL_IPV4_FIRST_FRAGMENT));
    PS_PRINTF("IPv4   %d\n", ADS_FILTER_DBG_GET_STATS_BY_INDEX(ADS_FILTER_ORIG_PKT_DL_IPV4_NOT_FIRST_FRAGMENT));
    PS_PRINTF("IPv6             %d\n", ADS_FILTER_DBG_GET_STATS_BY_INDEX(ADS_FILTER_ORIG_PKT_DL_IPV6_PKT));

    return;
}

/*****************************************************************************
     : ADS_FILTER_ResetStatisticInfo
   : 
   : VOS_VOID
   : VOS_VOID
     : VOS_VOID
   :
   :

       :
  1.       : 2013614
           : L47619
       : V3R3 Share-PDP
*****************************************************************************/
VOS_VOID ADS_FILTER_ResetStatisticInfo(VOS_VOID)
{
    TAF_MEM_SET_S(ADS_FILTER_DBG_GET_STATS_ARRAY_ADDR(), (VOS_SIZE_T)(sizeof(VOS_UINT32) * ADS_FILTER_ORIG_PKT_BUTT), 0x00, (VOS_SIZE_T)(sizeof(VOS_UINT32) * ADS_FILTER_ORIG_PKT_BUTT));
    return;
}


/*****************************************************************************
     : ADS_FILTER_ShowIPv6Addr
   : IPv6
   : 
   : 
     : 
   :
   :

       :
  1.       : 20130604
           : l00198894
       : V3R3 Share-PDP
*****************************************************************************/
VOS_VOID ADS_FILTER_ShowIPv6Addr(VOS_VOID)
{
    VOS_UINT8                          *pucIPv6Addr = VOS_NULL_PTR;
    VOS_UINT8                           ucLoop;

    pucIPv6Addr = ADS_FILTER_GET_IPV6_ADDR()->aucIpAddr;

    for (ucLoop = 0; ucLoop < ADS_IPV6_ADDR_LEN; ucLoop++)
    {
        if ( (0 != ucLoop) && (0 == ucLoop % 2) )
        {
            PS_PRINTF(":");
        }
        PS_PRINTF("%02x", pucIPv6Addr[ucLoop]);
    }

    PS_PRINTF("\n");

    return;
}

