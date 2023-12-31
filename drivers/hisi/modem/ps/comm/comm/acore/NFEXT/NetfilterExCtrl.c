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
   1 
******************************************************************************/
#include "v_typdef.h"
#include "PsTypeDef.h"
#include "IpsMntn.h"
#include "TtfOamInterface.h"
#include "TTFComm.h"
#include "NetfilterEx.h"
#include "TTFUtil.h"

#ifdef STATIC
#undef STATIC
#endif

#define STATIC

/*****************************************************************************
    .C
*****************************************************************************/

#define THIS_FILE_ID PS_FILE_ID_ACPU_NFEX_CTRL_C


/*****************************************************************************
  2 
*****************************************************************************/

/*****************************************************************************
  3 
*****************************************************************************/
NF_EXT_ENTITY_STRU                  g_stExEntity            = {0};
VOS_UINT32                          g_ulNFExtTaskId         = 0;
VOS_UINT32                          g_ulNFExtInitFlag       = 0;

#if(NF_EXT_DBG == DBG_ON)
NF_EXT_STATS_STRU                   g_stNfExtStats = {{0}};
#endif

NF_EXT_FLOW_CTRL_ENTITY             g_stExFlowCtrlEntity;
NF_EXT_NV_STRU                      g_stNfExtNv;
NF_EXT_HOOK_MASK_NV_STRU            g_stExHookMask;

/*****************************************************************************
  4 
*****************************************************************************/
/* netfilter */
NF_EXT_MASK_OPS_STRU g_stNfExtMaskOps[NF_EXT_HOOK_ON_MASK_IDX_ENUM_BUTT];


STATIC VOS_UINT32 NFExt_ReadNvCfg(VOS_VOID);
STATIC VOS_VOID NFExt_SetDefaultNvCfg(VOS_VOID);
STATIC VOS_VOID NFExt_EntityInit(VOS_VOID);
STATIC VOS_VOID NFExt_MaskOpsInit(VOS_VOID);
STATIC VOS_INT NFExt_Init(VOS_VOID);
STATIC VOS_VOID NFExt_SndDataNotify(VOS_VOID);

STATIC VOS_INT NFExt_RingBufferGet( OM_RING_ID rngId, VOS_CHAR *buffer, VOS_INT maxbytes );
STATIC VOS_VOID NFExt_RcvNfExtInfoCfgReq(VOS_VOID *pMsg);
STATIC VOS_VOID NFExt_EventProc(VOS_UINT32 ulEvent);
STATIC VOS_UINT32 NFExt_SaveBrDev(VOS_VOID);
STATIC VOS_INT NFExt_RingBufferPut( OM_RING_ID rngId, VOS_CHAR *buffer, VOS_INT nbytes );
STATIC VOS_VOID NFExt_FlowCtrlInit(VOS_VOID);

STATIC VOS_INT  NFExt_ReRegHooks(VOS_UINT32 ulMask);

/******************************************************************************
   5 
******************************************************************************/
/*****************************************************************************
     : NFExt_UnregHooks
   : 
   : VOS_UINT32 ulMask    
   : 
     : 
   :
   :

       :
  1.       : 20111122
           : caikai
       : Created
*****************************************************************************/
VOS_VOID  NFExt_UnregHooks(VOS_UINT32 ulMask)
{
    VOS_UINT i;

    for ( i = 0; i < ARRAY_SIZE(g_stNfExtMaskOps); i++ )
    {
        if ( g_stNfExtMaskOps[i].ulHookMask == (ulMask & g_stNfExtMaskOps[i].ulHookMask) )
        {
            /**/
            nf_unregister_hook(&(g_stNfExtMaskOps[i].stNfExtOps));

            /*  */
            g_stExEntity.ulCurHookOnMask &= ~g_stNfExtMaskOps[i].ulHookMask;
        }
    }

}

/*****************************************************************************
     : NFExt_RegHooks
   : 
   : VOS_UINT32 ulMask        
   : 
     : VOS_INT
   :
   :

       :
  1.       : 20111122
           : caikai
       : Created
*****************************************************************************/
VOS_INT  NFExt_RegHooks(VOS_UINT32 ulMask)
{
    VOS_INT iRet;
    VOS_UINT i;

    for ( i = 0; i < ARRAY_SIZE(g_stNfExtMaskOps); i++ )
    {
        if ( g_stNfExtMaskOps[i].ulHookMask != (ulMask & g_stNfExtMaskOps[i].ulHookMask) )
        {
            continue;
        }

        /**/
        iRet = nf_register_hook(&(g_stNfExtMaskOps[i].stNfExtOps));
        if ( 0 != iRet )
        {
            TTF_LOG(ACPU_PID_NFEXT, DIAG_MODE_COMM, PS_PRINT_WARNING,"register_hook error!!\n");

            /**/
            NFExt_UnregHooks(g_stExEntity.ulCurHookOnMask);
            return iRet;
        }

        g_stExEntity.ulCurHookOnMask |= g_stNfExtMaskOps[i].ulHookMask;
    }

    return 0;
}

/*****************************************************************************
     : NFExt_ReRegHooks
   : 
   : VOS_UINT32 ulMask    
   : 
     : VOS_INT
   :
   :

       :
  1.       : 20111122
           : caikai
       : Created
*****************************************************************************/
STATIC VOS_INT  NFExt_ReRegHooks(VOS_UINT32 ulMask)
{
    VOS_INT iRet;

    /**/
    if ( 0 != g_stExEntity.ulCurHookOnMask )
    {
        NFExt_UnregHooks(g_stExEntity.ulCurHookOnMask);
    }

    iRet = NFExt_RegHooks(ulMask);

    return iRet;
}

/*****************************************************************************
     : NFExt_ConfigEffective
   : 
   : NF_EXT_TRACE_CONFIG_REQ_STRU *pRcvMsg
   : 
     : PS_BOOL_ENUM_UINT8
   :
   :

       :
  1.       : 20111122
           : caikai
       : Created
*****************************************************************************/
PS_BOOL_ENUM_UINT8 NFExt_ConfigEffective(IPS_MNTN_TRACE_CONFIG_REQ_STRU *pRcvMsg)
{
    VOS_INT             iRet;
    VOS_UINT32          ulMask = 0;

    /* hook */
    ulMask |= NF_EXT_DEF_FLOW_CTRL_HOOK_ON_MASK;

    if ( (pRcvMsg->stBridgeArpTraceCfg.ulChoice > IPS_MNTN_TRACE_NULL_CHOSEN)
        && (pRcvMsg->stBridgeArpTraceCfg.ulChoice <= IPS_MNTN_TRACE_WHOLE_DATA_LEN_CHOSEN) )
    {
        ulMask |= NF_EXT_DEF_BR_ARP_HOOK_ON_MASK;
    }

    if ( (pRcvMsg->stPreRoutingTraceCfg.ulChoice > IPS_MNTN_TRACE_NULL_CHOSEN)
        && (pRcvMsg->stPreRoutingTraceCfg.ulChoice <= IPS_MNTN_TRACE_WHOLE_DATA_LEN_CHOSEN))
    {
        ulMask |= NF_EXT_DEF_PRE_ROUTING_HOOK_ON_MASK;
    }

    if ( (pRcvMsg->stPostRoutingTraceCfg.ulChoice > IPS_MNTN_TRACE_NULL_CHOSEN)
        && (pRcvMsg->stPostRoutingTraceCfg.ulChoice <= IPS_MNTN_TRACE_WHOLE_DATA_LEN_CHOSEN))
    {
        ulMask |= NF_EXT_DEF_POST_ROUTING_HOOK_ON_MASK;
    }

    if ( (pRcvMsg->stLocalTraceCfg.ulChoice > IPS_MNTN_TRACE_NULL_CHOSEN)
        && (pRcvMsg->stLocalTraceCfg.ulChoice <= IPS_MNTN_TRACE_WHOLE_DATA_LEN_CHOSEN))
    {
        ulMask |= NF_EXT_DEF_LOCAL_HOOK_ON_MASK;
    }

    iRet = NFExt_ReRegHooks(ulMask);

    if (iRet < 0)
    {
        TTF_LOG(ACPU_PID_NFEXT, DIAG_MODE_COMM, PS_PRINT_WARNING,"NFExt_ConfigEffective: NFExt_ReRegHooks failed!\n");
        return PS_FALSE;
    }

    return PS_TRUE;
}

/*****************************************************************************
     : NFExt_Get1stInetIpv4Addr
   : Ipv4
   : struct net_device *pstDev IP
   : 
     : 
   :
   :

       :
  1.       : 20120111
           : t00148005
       : Created
*****************************************************************************/
VOS_UINT32  NFExt_Get1stInetIpv4Addr(struct net_device *pstDev)
{
    struct in_device   *pinDev;

    /* LinuxLinux */
    if (NULL == pstDev)
    {
        return 0;
    }

    if (NULL == pstDev->ip_ptr)
    {
        return 0;
    }

    pinDev = (struct in_device*)(pstDev->ip_ptr);

    if (NULL == pinDev->ifa_list)
    {
        return 0;
    }

    return (VOS_UINT32)htonl((VOS_ULONG)pinDev->ifa_list->ifa_address);
}

/*****************************************************************************
     : NFExt_ReadNvCfg
   : NV
   :
   : 
     : VOS_OK, VOS_ERR
   :
   :

       :
  1.       : 2012827
           : c00191211
       : 
*****************************************************************************/
STATIC VOS_UINT32 NFExt_ReadNvCfg(VOS_VOID)
{
    VOS_UINT32                     ulRet;

    /*  */
    ulRet = NV_Read (en_NV_Item_NETFILTER_HOOK_MASK, &g_stNfExtNv , sizeof(NF_EXT_NV_STRU));
    if (NV_OK != ulRet)
    {
        PS_PRINTF("NFExt_ReadNvCfg Fail, Read NV FAIL, Error Code \n");
        return VOS_ERR;
    }

    /* NVg_stExHookMask*/
    g_stExHookMask.ulBrArpHookValue         = g_stNfExtNv.ulNetfilterPara1;
    g_stExHookMask.ulInHookValue            = g_stNfExtNv.ulNetfilterPara2;
    g_stExHookMask.ulOutHookValue           = g_stNfExtNv.ulNetfilterPara3;
    g_stExHookMask.ulFlowCtrlHookValue      = g_stNfExtNv.ulNetfilterPara4;
    g_stExHookMask.ulLocalHookValue         = g_stNfExtNv.ulNetfilterPara5;

    return VOS_OK;
}

/*****************************************************************************
     : NFExt_SetDefaultNvCfg
   : NV
   :
   : 
     :
   :
   :

       :
  1.       : 2012827
           : c00191211
       : 
*****************************************************************************/
STATIC VOS_VOID NFExt_SetDefaultNvCfg(VOS_VOID)
{
    g_stExHookMask.ulBrArpHookValue     = (  NF_EXT_GET_MASK_FROM_INDEX(NF_EXT_ARP_LOCAL_IN_ON_MASK_IDX)
                                           | NF_EXT_GET_MASK_FROM_INDEX(NF_EXT_ARP_LOCAL_OUT_ON_MASK_IDX) );

    g_stExHookMask.ulInHookValue        = (  NF_EXT_GET_MASK_FROM_INDEX(NF_EXT_IP4_PRE_ROUTING_HOOK_ON_MASK_IDX)
                                           | NF_EXT_GET_MASK_FROM_INDEX(NF_EXT_IP6_PRE_ROUTING_HOOK_ON_MASK_IDX) );

    g_stExHookMask.ulOutHookValue       = (  NF_EXT_GET_MASK_FROM_INDEX(NF_EXT_IP4_POST_ROUTING_HOOK_ON_MASK_IDX)
                                           | NF_EXT_GET_MASK_FROM_INDEX(NF_EXT_IP6_POST_ROUTING_HOOK_ON_MASK_IDX) );

    g_stExHookMask.ulFlowCtrlHookValue  = 0;

    g_stExHookMask.ulLocalHookValue     = (  NF_EXT_GET_MASK_FROM_INDEX(NF_EXT_IP4_LOCAL_IN_HOOK_ON_MASK_IDX)
                                           | NF_EXT_GET_MASK_FROM_INDEX(NF_EXT_IP4_LOCAL_OUT_HOOK_ON_MASK_IDX)
                                           | NF_EXT_GET_MASK_FROM_INDEX(NF_EXT_IP6_LOCAL_IN_HOOK_ON_MASK_IDX)
                                           | NF_EXT_GET_MASK_FROM_INDEX(NF_EXT_IP6_LOCAL_OUT_HOOK_ON_MASK_IDX));

    return;
}

/*****************************************************************************
     : NFExt_EntityInit
   : NFExt
   : void
   : 
     : void
   :
   :

       :
  1.       : 20111122
           : caikai
       : Created
*****************************************************************************/
STATIC VOS_VOID NFExt_EntityInit(VOS_VOID)
{
    g_stExEntity.ulCurHookOnMask    = 0;
    g_stExEntity.ulIsBlkflag        = NF_EXT_FLAG_BLOCKED;
    g_stExEntity.ulIsDeviceOpen     = 0;
    g_stExEntity.ulOmIp             = 0;
}

/*****************************************************************************
     : NFExt_MaskOpsInit
   : NFExtMaskOps
   : void
   : 
     : void
   :
   :

       :
  1.       : 201727
           : d00314740
       : Created
*****************************************************************************/
STATIC VOS_VOID NFExt_MaskOpsInit(VOS_VOID)
{
    NF_EXT_MASK_OPS_STRU               *pstMaskOps  = &(g_stNfExtMaskOps[0]);

    PSACORE_MEM_SET(pstMaskOps,
        NF_EXT_HOOK_ON_MASK_IDX_ENUM_BUTT * sizeof(NF_EXT_MASK_OPS_STRU),
        0x00,
        NF_EXT_HOOK_ON_MASK_IDX_ENUM_BUTT * sizeof(NF_EXT_MASK_OPS_STRU));

    pstMaskOps[NF_EXT_BR_PRE_ROUTING_HOOK_ON_MASK_IDX].ulHookMask
        = NF_EXT_GET_MASK_FROM_INDEX(NF_EXT_BR_PRE_ROUTING_HOOK_ON_MASK_IDX);
    pstMaskOps[NF_EXT_BR_PRE_ROUTING_HOOK_ON_MASK_IDX].stNfExtOps.hook      = (nf_hookfn*)NFExt_BrPreRoutingHook;
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 1, 0))
    pstMaskOps[NF_EXT_BR_PRE_ROUTING_HOOK_ON_MASK_IDX].stNfExtOps.priv      = NULL,
#endif
    pstMaskOps[NF_EXT_BR_PRE_ROUTING_HOOK_ON_MASK_IDX].stNfExtOps.pf        = NFPROTO_BRIDGE;
    pstMaskOps[NF_EXT_BR_PRE_ROUTING_HOOK_ON_MASK_IDX].stNfExtOps.hooknum   = NF_BR_PRE_ROUTING;
    pstMaskOps[NF_EXT_BR_PRE_ROUTING_HOOK_ON_MASK_IDX].stNfExtOps.priority  = NF_EXT_BR_PRI_FILTER_OTHER;   /* hook */

    pstMaskOps[NF_EXT_BR_POST_ROUTING_HOOK_ON_MASK_IDX].ulHookMask
        = NF_EXT_GET_MASK_FROM_INDEX(NF_EXT_BR_POST_ROUTING_HOOK_ON_MASK_IDX);
    pstMaskOps[NF_EXT_BR_POST_ROUTING_HOOK_ON_MASK_IDX].stNfExtOps.hook     = (nf_hookfn*)NFExt_BrPostRoutingHook;
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 1, 0))
    pstMaskOps[NF_EXT_BR_POST_ROUTING_HOOK_ON_MASK_IDX].stNfExtOps.priv     = NULL,
#endif
    pstMaskOps[NF_EXT_BR_POST_ROUTING_HOOK_ON_MASK_IDX].stNfExtOps.pf       = NFPROTO_BRIDGE;
    pstMaskOps[NF_EXT_BR_POST_ROUTING_HOOK_ON_MASK_IDX].stNfExtOps.hooknum  = NF_BR_POST_ROUTING;
    pstMaskOps[NF_EXT_BR_POST_ROUTING_HOOK_ON_MASK_IDX].stNfExtOps.priority = NF_EXT_BR_PRI_FILTER_OTHER;

    pstMaskOps[NF_EXT_BR_FORWARD_HOOK_ON_MASK_IDX].ulHookMask
        = NF_EXT_GET_MASK_FROM_INDEX(NF_EXT_BR_FORWARD_HOOK_ON_MASK_IDX);
    pstMaskOps[NF_EXT_BR_FORWARD_HOOK_ON_MASK_IDX].stNfExtOps.hook      = (nf_hookfn*)NFExt_BrForwardHook;
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 1, 0))
    pstMaskOps[NF_EXT_BR_FORWARD_HOOK_ON_MASK_IDX].stNfExtOps.priv      = NULL,
#endif
    pstMaskOps[NF_EXT_BR_FORWARD_HOOK_ON_MASK_IDX].stNfExtOps.pf        = NFPROTO_BRIDGE;
    pstMaskOps[NF_EXT_BR_FORWARD_HOOK_ON_MASK_IDX].stNfExtOps.hooknum   = NF_BR_FORWARD;
    pstMaskOps[NF_EXT_BR_FORWARD_HOOK_ON_MASK_IDX].stNfExtOps.priority  = NF_EXT_BR_PRI_FILTER_OTHER;

    pstMaskOps[NF_EXT_BR_LOCAL_IN_HOOK_ON_MASK_IDX].ulHookMask
        = NF_EXT_GET_MASK_FROM_INDEX(NF_EXT_BR_LOCAL_IN_HOOK_ON_MASK_IDX);
    pstMaskOps[NF_EXT_BR_LOCAL_IN_HOOK_ON_MASK_IDX].stNfExtOps.hook     = (nf_hookfn*)NFExt_BrLocalInHook;
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 1, 0))
    pstMaskOps[NF_EXT_BR_LOCAL_IN_HOOK_ON_MASK_IDX].stNfExtOps.priv     = NULL,
#endif
    pstMaskOps[NF_EXT_BR_LOCAL_IN_HOOK_ON_MASK_IDX].stNfExtOps.pf       = NFPROTO_BRIDGE;
    pstMaskOps[NF_EXT_BR_LOCAL_IN_HOOK_ON_MASK_IDX].stNfExtOps.hooknum  = NF_BR_LOCAL_IN;
    pstMaskOps[NF_EXT_BR_LOCAL_IN_HOOK_ON_MASK_IDX].stNfExtOps.priority = NF_EXT_BR_PRI_FILTER_OTHER;

    pstMaskOps[NF_EXT_BR_LOCAL_OUT_HOOK_ON_MASK_IDX].ulHookMask
        = NF_EXT_GET_MASK_FROM_INDEX(NF_EXT_BR_LOCAL_OUT_HOOK_ON_MASK_IDX);
    pstMaskOps[NF_EXT_BR_LOCAL_OUT_HOOK_ON_MASK_IDX].stNfExtOps.hook        = (nf_hookfn*)NFExt_BrLocalOutHook;
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 1, 0))
    pstMaskOps[NF_EXT_BR_LOCAL_OUT_HOOK_ON_MASK_IDX].stNfExtOps.priv        = NULL,
#endif
    pstMaskOps[NF_EXT_BR_LOCAL_OUT_HOOK_ON_MASK_IDX].stNfExtOps.pf          = NFPROTO_BRIDGE;
    pstMaskOps[NF_EXT_BR_LOCAL_OUT_HOOK_ON_MASK_IDX].stNfExtOps.hooknum     = NF_BR_LOCAL_OUT;
    pstMaskOps[NF_EXT_BR_LOCAL_OUT_HOOK_ON_MASK_IDX].stNfExtOps.priority    = NF_EXT_BR_PRI_FILTER_OTHER;

    pstMaskOps[NF_EXT_ARP_LOCAL_IN_ON_MASK_IDX].ulHookMask
        = NF_EXT_GET_MASK_FROM_INDEX(NF_EXT_ARP_LOCAL_IN_ON_MASK_IDX);
    pstMaskOps[NF_EXT_ARP_LOCAL_IN_ON_MASK_IDX].stNfExtOps.hook     = (nf_hookfn*)NFExt_ArpInHook;
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 1, 0))
    pstMaskOps[NF_EXT_ARP_LOCAL_IN_ON_MASK_IDX].stNfExtOps.priv     = NULL,
#endif
    pstMaskOps[NF_EXT_ARP_LOCAL_IN_ON_MASK_IDX].stNfExtOps.pf       = NFPROTO_ARP;
    pstMaskOps[NF_EXT_ARP_LOCAL_IN_ON_MASK_IDX].stNfExtOps.hooknum  = NF_ARP_IN;
    pstMaskOps[NF_EXT_ARP_LOCAL_IN_ON_MASK_IDX].stNfExtOps.priority = NF_EXT_IP_PRI_CONNTRACK;      /* ARP hook */

    pstMaskOps[NF_EXT_ARP_LOCAL_OUT_ON_MASK_IDX].ulHookMask
        = NF_EXT_GET_MASK_FROM_INDEX(NF_EXT_ARP_LOCAL_OUT_ON_MASK_IDX);
    pstMaskOps[NF_EXT_ARP_LOCAL_OUT_ON_MASK_IDX].stNfExtOps.hook        = (nf_hookfn*)NFExt_ArpOutHook;
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 1, 0))
    pstMaskOps[NF_EXT_ARP_LOCAL_OUT_ON_MASK_IDX].stNfExtOps.priv        = NULL,
#endif
    pstMaskOps[NF_EXT_ARP_LOCAL_OUT_ON_MASK_IDX].stNfExtOps.pf          = NFPROTO_ARP;
    pstMaskOps[NF_EXT_ARP_LOCAL_OUT_ON_MASK_IDX].stNfExtOps.hooknum     = NF_ARP_OUT;
    pstMaskOps[NF_EXT_ARP_LOCAL_OUT_ON_MASK_IDX].stNfExtOps.priority    = NF_EXT_IP_PRI_CONNTRACK;

    pstMaskOps[NF_EXT_IP4_PRE_ROUTING_HOOK_ON_MASK_IDX].ulHookMask
        = NF_EXT_GET_MASK_FROM_INDEX(NF_EXT_IP4_PRE_ROUTING_HOOK_ON_MASK_IDX);
    pstMaskOps[NF_EXT_IP4_PRE_ROUTING_HOOK_ON_MASK_IDX].stNfExtOps.hook     = (nf_hookfn*)NFExt_Ip4PreRoutingHook;
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 1, 0))
    pstMaskOps[NF_EXT_IP4_PRE_ROUTING_HOOK_ON_MASK_IDX].stNfExtOps.priv     = NULL,
#endif
    pstMaskOps[NF_EXT_IP4_PRE_ROUTING_HOOK_ON_MASK_IDX].stNfExtOps.pf       = NFPROTO_IPV4;
    pstMaskOps[NF_EXT_IP4_PRE_ROUTING_HOOK_ON_MASK_IDX].stNfExtOps.hooknum  = NF_INET_PRE_ROUTING;
    pstMaskOps[NF_EXT_IP4_PRE_ROUTING_HOOK_ON_MASK_IDX].stNfExtOps.priority = NF_EXT_IP_PRI_MANGLE;         /* DNAT hook */

    pstMaskOps[NF_EXT_IP4_POST_ROUTING_HOOK_ON_MASK_IDX].ulHookMask
        = NF_EXT_GET_MASK_FROM_INDEX(NF_EXT_IP4_POST_ROUTING_HOOK_ON_MASK_IDX);
    pstMaskOps[NF_EXT_IP4_POST_ROUTING_HOOK_ON_MASK_IDX].stNfExtOps.hook        = (nf_hookfn*)NFExt_Ip4PostRoutingHook;
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 1, 0))
    pstMaskOps[NF_EXT_IP4_POST_ROUTING_HOOK_ON_MASK_IDX].stNfExtOps.priv        = NULL,
#endif
    pstMaskOps[NF_EXT_IP4_POST_ROUTING_HOOK_ON_MASK_IDX].stNfExtOps.pf          = NFPROTO_IPV4;
    pstMaskOps[NF_EXT_IP4_POST_ROUTING_HOOK_ON_MASK_IDX].stNfExtOps.hooknum     = NF_INET_POST_ROUTING;
    pstMaskOps[NF_EXT_IP4_POST_ROUTING_HOOK_ON_MASK_IDX].stNfExtOps.priority    = NF_EXT_IP_PRI_SELINUX_LAST;   /* SNAT hook */

    pstMaskOps[NF_EXT_IP4_LOCAL_IN_HOOK_ON_MASK_IDX].ulHookMask
        = NF_EXT_GET_MASK_FROM_INDEX(NF_EXT_IP4_LOCAL_IN_HOOK_ON_MASK_IDX);
    pstMaskOps[NF_EXT_IP4_LOCAL_IN_HOOK_ON_MASK_IDX].stNfExtOps.hook        = (nf_hookfn*)NFExt_Ip4LocalInHook;
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 1, 0))
    pstMaskOps[NF_EXT_IP4_LOCAL_IN_HOOK_ON_MASK_IDX].stNfExtOps.priv        = NULL,
#endif
    pstMaskOps[NF_EXT_IP4_LOCAL_IN_HOOK_ON_MASK_IDX].stNfExtOps.pf          = NFPROTO_IPV4;
    pstMaskOps[NF_EXT_IP4_LOCAL_IN_HOOK_ON_MASK_IDX].stNfExtOps.hooknum     = NF_INET_LOCAL_IN;
    pstMaskOps[NF_EXT_IP4_LOCAL_IN_HOOK_ON_MASK_IDX].stNfExtOps.priority    = NF_EXT_IP_PRI_SELINUX_LAST;

    pstMaskOps[NF_EXT_IP4_LOCAL_OUT_HOOK_ON_MASK_IDX].ulHookMask
        = NF_EXT_GET_MASK_FROM_INDEX(NF_EXT_IP4_LOCAL_OUT_HOOK_ON_MASK_IDX);
    pstMaskOps[NF_EXT_IP4_LOCAL_OUT_HOOK_ON_MASK_IDX].stNfExtOps.hook       = (nf_hookfn*)NFExt_Ip4LocalOutHook;
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 1, 0))
    pstMaskOps[NF_EXT_IP4_LOCAL_OUT_HOOK_ON_MASK_IDX].stNfExtOps.priv       = NULL,
#endif
    pstMaskOps[NF_EXT_IP4_LOCAL_OUT_HOOK_ON_MASK_IDX].stNfExtOps.pf         = NFPROTO_IPV4;
    pstMaskOps[NF_EXT_IP4_LOCAL_OUT_HOOK_ON_MASK_IDX].stNfExtOps.hooknum    = NF_INET_LOCAL_OUT;
    pstMaskOps[NF_EXT_IP4_LOCAL_OUT_HOOK_ON_MASK_IDX].stNfExtOps.priority   = NF_EXT_IP_PRI_SELINUX_LAST;

    pstMaskOps[NF_EXT_IP4_FORWARD_HOOK_ON_MASK_IDX].ulHookMask
        = NF_EXT_GET_MASK_FROM_INDEX(NF_EXT_IP4_FORWARD_HOOK_ON_MASK_IDX);
    pstMaskOps[NF_EXT_IP4_FORWARD_HOOK_ON_MASK_IDX].stNfExtOps.hook     = (nf_hookfn*)NFExt_Ip4ForwardHook;
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 1, 0))
    pstMaskOps[NF_EXT_IP4_FORWARD_HOOK_ON_MASK_IDX].stNfExtOps.priv     = NULL,
#endif
    pstMaskOps[NF_EXT_IP4_FORWARD_HOOK_ON_MASK_IDX].stNfExtOps.pf       = NFPROTO_IPV4;
    pstMaskOps[NF_EXT_IP4_FORWARD_HOOK_ON_MASK_IDX].stNfExtOps.hooknum  = NF_INET_FORWARD;
    pstMaskOps[NF_EXT_IP4_FORWARD_HOOK_ON_MASK_IDX].stNfExtOps.priority = NF_EXT_IP_PRI_SELINUX_LAST;

    pstMaskOps[NF_EXT_IP6_PRE_ROUTING_HOOK_ON_MASK_IDX].ulHookMask
        = NF_EXT_GET_MASK_FROM_INDEX(NF_EXT_IP6_PRE_ROUTING_HOOK_ON_MASK_IDX);
    pstMaskOps[NF_EXT_IP6_PRE_ROUTING_HOOK_ON_MASK_IDX].stNfExtOps.hook     = (nf_hookfn*)NFExt_Ip6PreRoutingHook;
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 1, 0))
    pstMaskOps[NF_EXT_IP6_PRE_ROUTING_HOOK_ON_MASK_IDX].stNfExtOps.priv     = NULL,
#endif
    pstMaskOps[NF_EXT_IP6_PRE_ROUTING_HOOK_ON_MASK_IDX].stNfExtOps.pf       = NFPROTO_IPV6;
    pstMaskOps[NF_EXT_IP6_PRE_ROUTING_HOOK_ON_MASK_IDX].stNfExtOps.hooknum  = NF_INET_PRE_ROUTING;
    pstMaskOps[NF_EXT_IP6_PRE_ROUTING_HOOK_ON_MASK_IDX].stNfExtOps.priority = NF_EXT_IP_PRI_MANGLE;

    pstMaskOps[NF_EXT_IP6_POST_ROUTING_HOOK_ON_MASK_IDX].ulHookMask
        = NF_EXT_GET_MASK_FROM_INDEX(NF_EXT_IP6_POST_ROUTING_HOOK_ON_MASK_IDX);
    pstMaskOps[NF_EXT_IP6_POST_ROUTING_HOOK_ON_MASK_IDX].stNfExtOps.hook        = (nf_hookfn*)NFExt_Ip6PostRoutingHook;
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 1, 0))
    pstMaskOps[NF_EXT_IP6_POST_ROUTING_HOOK_ON_MASK_IDX].stNfExtOps.priv        = NULL,
#endif
    pstMaskOps[NF_EXT_IP6_POST_ROUTING_HOOK_ON_MASK_IDX].stNfExtOps.pf          = NFPROTO_IPV6;
    pstMaskOps[NF_EXT_IP6_POST_ROUTING_HOOK_ON_MASK_IDX].stNfExtOps.hooknum     = NF_INET_POST_ROUTING;
    pstMaskOps[NF_EXT_IP6_POST_ROUTING_HOOK_ON_MASK_IDX].stNfExtOps.priority    = NF_EXT_IP_PRI_SELINUX_LAST;

    pstMaskOps[NF_EXT_IP6_LOCAL_IN_HOOK_ON_MASK_IDX].ulHookMask
        = NF_EXT_GET_MASK_FROM_INDEX(NF_EXT_IP6_LOCAL_IN_HOOK_ON_MASK_IDX);
    pstMaskOps[NF_EXT_IP6_LOCAL_IN_HOOK_ON_MASK_IDX].stNfExtOps.hook        = (nf_hookfn*)NFExt_Ip6LocalInHook;
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 1, 0))
    pstMaskOps[NF_EXT_IP6_LOCAL_IN_HOOK_ON_MASK_IDX].stNfExtOps.priv        = NULL,
#endif
    pstMaskOps[NF_EXT_IP6_LOCAL_IN_HOOK_ON_MASK_IDX].stNfExtOps.pf          = NFPROTO_IPV6;
    pstMaskOps[NF_EXT_IP6_LOCAL_IN_HOOK_ON_MASK_IDX].stNfExtOps.hooknum     = NF_INET_LOCAL_IN;
    pstMaskOps[NF_EXT_IP6_LOCAL_IN_HOOK_ON_MASK_IDX].stNfExtOps.priority    = NF_EXT_IP_PRI_SELINUX_LAST;

    pstMaskOps[NF_EXT_IP6_LOCAL_OUT_HOOK_ON_MASK_IDX].ulHookMask
        = NF_EXT_GET_MASK_FROM_INDEX(NF_EXT_IP6_LOCAL_OUT_HOOK_ON_MASK_IDX);
    pstMaskOps[NF_EXT_IP6_LOCAL_OUT_HOOK_ON_MASK_IDX].stNfExtOps.hook       = (nf_hookfn*)NFExt_Ip6LocalOutHook;
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 1, 0))
    pstMaskOps[NF_EXT_IP6_LOCAL_OUT_HOOK_ON_MASK_IDX].stNfExtOps.priv       = NULL,
#endif
    pstMaskOps[NF_EXT_IP6_LOCAL_OUT_HOOK_ON_MASK_IDX].stNfExtOps.pf         = NFPROTO_IPV6;
    pstMaskOps[NF_EXT_IP6_LOCAL_OUT_HOOK_ON_MASK_IDX].stNfExtOps.hooknum    = NF_INET_LOCAL_OUT;
    pstMaskOps[NF_EXT_IP6_LOCAL_OUT_HOOK_ON_MASK_IDX].stNfExtOps.priority   = NF_EXT_IP_PRI_SELINUX_LAST;

    pstMaskOps[NF_EXT_IP6_FORWARD_HOOK_ON_MASK_IDX].ulHookMask
        = NF_EXT_GET_MASK_FROM_INDEX(NF_EXT_IP6_FORWARD_HOOK_ON_MASK_IDX);
    pstMaskOps[NF_EXT_IP6_FORWARD_HOOK_ON_MASK_IDX].stNfExtOps.hook     = (nf_hookfn*)NFExt_Ip6ForwardHook;
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 1, 0))
    pstMaskOps[NF_EXT_IP6_FORWARD_HOOK_ON_MASK_IDX].stNfExtOps.priv     = NULL,
#endif
    pstMaskOps[NF_EXT_IP6_FORWARD_HOOK_ON_MASK_IDX].stNfExtOps.pf       = NFPROTO_IPV6;
    pstMaskOps[NF_EXT_IP6_FORWARD_HOOK_ON_MASK_IDX].stNfExtOps.hooknum  = NF_INET_FORWARD;
    pstMaskOps[NF_EXT_IP6_FORWARD_HOOK_ON_MASK_IDX].stNfExtOps.priority = NF_EXT_IP_PRI_SELINUX_LAST;

    pstMaskOps[NF_EXT_BR_FORWARD_FLOW_CTRL_HOOK_ON_MASK_IDX].ulHookMask
        = NF_EXT_GET_MASK_FROM_INDEX(NF_EXT_BR_FORWARD_FLOW_CTRL_HOOK_ON_MASK_IDX);
    pstMaskOps[NF_EXT_BR_FORWARD_FLOW_CTRL_HOOK_ON_MASK_IDX].stNfExtOps.hook        = (nf_hookfn*)NFExt_BrForwardFlowCtrlHook;
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 1, 0))
    pstMaskOps[NF_EXT_BR_FORWARD_FLOW_CTRL_HOOK_ON_MASK_IDX].stNfExtOps.priv        = NULL,
#endif
    pstMaskOps[NF_EXT_BR_FORWARD_FLOW_CTRL_HOOK_ON_MASK_IDX].stNfExtOps.pf          = NFPROTO_BRIDGE;
    pstMaskOps[NF_EXT_BR_FORWARD_FLOW_CTRL_HOOK_ON_MASK_IDX].stNfExtOps.hooknum     = NF_BR_FORWARD;
    pstMaskOps[NF_EXT_BR_FORWARD_FLOW_CTRL_HOOK_ON_MASK_IDX].stNfExtOps.priority    = NF_EXT_BR_PRI_FILTER_BRIDGED;             /* ,0 */

}

/*****************************************************************************
     : NFExt_Init
   : 
   : 
   : 
     : 
   :
   :

       :
  1.       : 20111122
           : caikai
       : Created
*****************************************************************************/
STATIC VOS_INT NFExt_Init(VOS_VOID)
{
    VOS_UINT32  ulRet;

    ulRet = NFExt_ReadNvCfg();
    if (VOS_ERR == ulRet)
    {
        NFExt_SetDefaultNvCfg();
    }

    /* NFExt */
    NFExt_EntityInit();

    /* NFExtMaskOps */
    NFExt_MaskOpsInit();

    /*  */
    NFExt_FlowCtrlInit();

    return VOS_OK;
}

/*****************************************************************************
                        
*****************************************************************************/
/*****************************************************************************
     : NFExt_FlowCtrlInit
   : 
   : 
   : 
     : 
   :
   :

       :
  1.       : 20120111
           : t00148005
       : Created
*****************************************************************************/
STATIC VOS_VOID NFExt_FlowCtrlInit(VOS_VOID)
{
    if (NFExt_RegHooks(NF_EXT_DEF_FLOW_CTRL_HOOK_ON_MASK))
    {
        PS_PRINTF("NFExt_FlowCtrlInit NFExt_RegHooks fail");

        return;
    }

    g_stExFlowCtrlEntity.ulFlowCtrlMsk = 0;
    g_stExFlowCtrlEntity.pstBrDev      = NULL;

    PSACORE_MEM_SET(g_stExFlowCtrlEntity.aulTxBytesCnt, sizeof(g_stExFlowCtrlEntity.aulTxBytesCnt), 0, sizeof(g_stExFlowCtrlEntity.aulTxBytesCnt));
}

/*****************************************************************************
     : NFExt_BrSetFlowCtrl
   : 
   : 
   : 
     : 
   :
   :

       :
  1.       : 20120111
           : t00148005
       : Created
*****************************************************************************/
/*lint -e{550,438} */
VOS_VOID  NFExt_BrSetFlowCtrl(VOS_VOID)
{
    VOS_ULONG       ulFlags = 0UL;

    VOS_SpinLockIntLock(&g_stExEntity.stLockTxTask, ulFlags);
    g_stExFlowCtrlEntity.ulFlowCtrlMsk |= NF_EXT_BR_FORWARD_FLOW_CTRL_MASK;
    VOS_SpinUnlockIntUnlock(&g_stExEntity.stLockTxTask, ulFlags);

    IPS_MNTN_FlowCtrl(NF_EXT_BR_FORWARD_FLOW_CTRL_MASK, ID_IPS_TRACE_BR_FORWARD_FLOW_CTRL_START);
}

/*****************************************************************************
     : NFExt_BrStopFlowCtrl
   : 
   : 
   : 
     : 
   :
   :

       :
  1.       : 20120111
           : t00148005
       : Created
*****************************************************************************/
/*lint -e{550,438} */
VOS_VOID  NFExt_BrStopFlowCtrl(VOS_VOID)
{
    VOS_ULONG       ulFlags = 0UL;

    VOS_SpinLockIntLock(&g_stExEntity.stLockTxTask, ulFlags);
    g_stExFlowCtrlEntity.ulFlowCtrlMsk &= ~NF_EXT_BR_FORWARD_FLOW_CTRL_MASK;
    VOS_SpinUnlockIntUnlock(&g_stExEntity.stLockTxTask, ulFlags);

    IPS_MNTN_FlowCtrl(NF_EXT_BR_FORWARD_FLOW_CTRL_MASK, ID_IPS_TRACE_BR_FORWARD_FLOW_CTRL_STOP);
}

/*****************************************************************************
     : NFExt_GetBrBytesCnt
   : 
   : 
   : 
     : 
   :
   :

       :
  1.       : 20120111
           : t00148005
       : Created
*****************************************************************************/
VOS_UINT32 NFExt_GetBrBytesCnt(VOS_VOID)
{
    return 0;
}


/*****************************************************************************
     : NFExt_SaveBrDev
   : 
   : 
   : 
     : 
   :
   :

       :
  1.       : 20120111
           : t00148005
       : Created
*****************************************************************************/
STATIC VOS_UINT32 NFExt_SaveBrDev(VOS_VOID)
{
    struct net_device   *dev;
    dev = dev_get_by_name(&init_net, NF_EXT_BR_NAME);

    if (NULL == dev)
    {
        return VOS_ERR;
    }

    g_stExFlowCtrlEntity.pstBrDev   = dev;

    /* IPv4 */
    g_stExEntity.ulOmIp             = NFExt_Get1stInetIpv4Addr(dev);

    return VOS_OK;
}

#if(NF_EXT_DBG == DBG_ON)
/*****************************************************************************
     : NFExt_StatsShow
   : Netfilter ex debug
   : 
   : 
     : 
   :
   :

       :
  1.       : 20120211
           : t00148005
       : Created
*****************************************************************************/
STATIC VOS_VOID NFExt_StatsShow(VOS_VOID)
{
    vos_printf("forward %ld \n", g_stNfExtStats.aulStats[NF_EXT_STATS_BR_FC_DROP]);
    vos_printf("forward hook %ld \n", g_stNfExtStats.aulStats[NF_EXT_STATS_BR_FC_ENTER]);
    vos_printf("buf %ld \n", g_stNfExtStats.aulStats[NF_EXT_STATS_BUF_FULL_DROP]);
    vos_printf("buf %ld \n", g_stNfExtStats.aulStats[NF_EXT_STATS_PUT_BUF_FAIL]);
    vos_printf("buf %ld \n", g_stNfExtStats.aulStats[NF_EXT_STATS_GET_BUF_FAIL]);
    vos_printf(" %ld \n", g_stNfExtStats.aulStats[NF_EXT_STATS_ALLOC_MEM_FAIL]);

    vos_printf(" %ld \n", ((VOS_UINT32)OM_RingBufferNBytes(g_stExEntity.pRingBufferId) / sizeof(NF_EXT_DATA_RING_BUF_STRU)));
    vos_printf("Hook Mask %ld \n", g_stExEntity.ulCurHookOnMask);
    vos_printf("Mask %ld \n", g_stExFlowCtrlEntity.ulFlowCtrlMsk);
    vos_printf("OM WIFIIP %x \n", g_stExEntity.ulOmIp);
    vos_printf(" %x \n", g_stExFlowCtrlEntity.aulTxBytesCnt[NF_EXT_TX_BYTES_CNT_BR]);
}

/*****************************************************************************
     : NFExt_ResetPri
   : netfilter ex hook,Debug
   : 
   : 
     : 
   :
   :

       :
  1.       : 20120211
           : t00148005
       : Created
*****************************************************************************/
STATIC VOS_VOID NFExt_ResetPri(VOS_UINT32 ulHookNode, VOS_INT32 iPri)
{
    VOS_UINT32  ulCurHookMask = 0;

    if (ulHookNode > (ARRAY_SIZE(g_stNfExtMaskOps) - 1))
    {
        return;
    }

    ulCurHookMask = g_stExEntity.ulCurHookOnMask;
    g_stNfExtMaskOps[ulHookNode].stNfExtOps.priority = iPri;

    NFExt_ReRegHooks(ulCurHookMask);

    vos_printf("Current ulHookNode %d pri = %d\n", ulHookNode, iPri);
}
#endif


/******************************************************************************
 Prototype       : NFExt_SndDataNotify
 Description     : NFEXT_DATA_PROC_NOTIFY
 Input           :
 Output          : NONE
 Return Value    : PS_SUCC   --- 
                   PS_FAIL   --- 
 History         :
   1.Date        : 2008-07-16
     Author      : l47619
     Modification: PPP
******************************************************************************/
STATIC VOS_VOID NFExt_SndDataNotify(VOS_VOID)
{
    (VOS_VOID)VOS_EventWrite(g_ulNFExtTaskId, NFEXT_DATA_PROC_NOTIFY);

    return;
} /* NFExt_SndDataNotify */

/*****************************************************************************
     : NFExt_RingBufferPut
   : ring buffer
   : OM_RING_ID rngId:      buff
             VOS_CHAR *buffer:      buff
             VOS_INT nbytes:        buff
   : 
     : VOS_INT
   :
   :

       :
  1.       : 20111122
           : t00148005
       : Created
*****************************************************************************/
/*lint -e{550,438} */
STATIC VOS_INT NFExt_RingBufferPut( OM_RING_ID rngId, VOS_CHAR *buffer, VOS_INT nbytes )
{
    VOS_ULONG   ulFlags = 0UL;
    VOS_INT     iRst;

    iRst = 0;

    VOS_SpinLockIntLock(&g_stExEntity.stLockTxTask, ulFlags);
    if ((VOS_UINT32)OM_RingBufferFreeBytes(g_stExEntity.pRingBufferId) >= sizeof(NF_EXT_DATA_RING_BUF_STRU) )
    {
        iRst = OM_RingBufferPut(rngId, buffer, nbytes);
    }
    VOS_SpinUnlockIntUnlock(&g_stExEntity.stLockTxTask, ulFlags);

    return iRst;
}

/*****************************************************************************
     : NFExt_RingBufferGet
   : ring buffer
   : OM_RING_ID rngId:      buff
             VOS_CHAR *buffer:      buff
             VOS_INT nbytes:        buff
   : 
     : VOS_INT
   :
   :

       :
  1.       : 20111122
           : t00148005
       : Created
*****************************************************************************/
/*lint -e{550,438} */
STATIC VOS_INT NFExt_RingBufferGet( OM_RING_ID rngId, VOS_CHAR *buffer, VOS_INT maxbytes )
{
    VOS_ULONG   ulFlags = 0UL;
    VOS_INT     iRst;

    iRst = 0;

    VOS_SpinLockIntLock(&g_stExEntity.stLockTxTask, ulFlags);
    if (!OM_RingBufferIsEmpty(rngId))
    {
        iRst = OM_RingBufferGet(rngId, buffer, maxbytes );
    }
    VOS_SpinUnlockIntUnlock(&g_stExEntity.stLockTxTask, ulFlags);

    return iRst;
}

/*****************************************************************************
     : NFExt_FlushRingBuffer
   : RingBuffer
   : OM_RING_ID rngId OM ringbuffer id
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20111122
           : t00148005
       : Created
*****************************************************************************/
/*lint -e{550,438} */
VOS_VOID NFExt_FlushRingBuffer(OM_RING_ID rngId)
{
    NF_EXT_DATA_RING_BUF_STRU   stData;
    VOS_ULONG                   ulFlags = 0UL;
    VOS_INT                     iRst = 0;

    /*  */
    PSACORE_MEM_SET(&stData, sizeof(stData), 0x0, sizeof(stData));

    while (!OM_RingBufferIsEmpty(rngId))
    {
        iRst = NFExt_RingBufferGet(rngId, (VOS_CHAR*)(&stData), sizeof(NF_EXT_DATA_RING_BUF_STRU));
        if (iRst == sizeof(NF_EXT_DATA_RING_BUF_STRU))
        {
            NF_EXT_MEM_FREE(ACPU_PID_NFEXT, stData.pData);
        }
        else
        {
            TTF_LOG1(ACPU_PID_NFEXT, 0, PS_PRINT_WARNING,
                    "NFExt_FlushRingBuffer : ERROR : Get data error from ring buffer!", iRst);

            break;
        }
    }

    VOS_SpinLockIntLock(&g_stExEntity.stLockTxTask, ulFlags);
    OM_RingBufferFlush(rngId);
    VOS_SpinUnlockIntUnlock(&g_stExEntity.stLockTxTask, ulFlags);
}


/*****************************************************************************
     : NFExt_AddDataToRingBuf
   : OAMRingBuf
   : NF_EXT_DATA_RING_BUF_STRU *pstData ringbuffer
   : 
     : VOS_UINT32 
   :
   :

       :
  1.       : 20111122
           : t00148005
       : Created
  2.       :  20151031
           :  g00178567
       :  
*****************************************************************************/
VOS_UINT32 NFExt_AddDataToRingBuf(NF_EXT_DATA_RING_BUF_STRU *pstData)
{
    VOS_UINT32                  ulRst           = VOS_OK;
    VOS_UINT32                  ulNeedWakeUp    = VOS_FALSE;
    VOS_INT                     iRst;
    NF_EXT_DATA_RING_BUF_STRU   stData;

    if ( VOS_NULL_PTR == g_stExEntity.pRingBufferId )
    {
        TTF_LOG(ACPU_PID_NFEXT, DIAG_MODE_COMM, PS_PRINT_WARNING,"NFExt_AddDataToRingBuf: Warning : g_stExEntity.pRingBufferId is null!\n");
        return VOS_ERR;
    }

    /*  */
    if (OM_RingBufferIsEmpty(g_stExEntity.pRingBufferId))
    {
        ulNeedWakeUp = VOS_TRUE;
    }

    iRst = NFExt_RingBufferPut(g_stExEntity.pRingBufferId, (VOS_CHAR *)pstData, (VOS_INT)(sizeof(NF_EXT_DATA_RING_BUF_STRU)));
    if (sizeof(NF_EXT_DATA_RING_BUF_STRU) == iRst)
    {
        if (VOS_TRUE == ulNeedWakeUp)
        {
            NFExt_SndDataNotify();
        }

        ulRst = VOS_OK;
    }
    else if (0 == iRst)
    {
        NF_EXT_STATS_INC(1, NF_EXT_STATS_BUF_FULL_DROP);

        /*  */
        NFExt_SndDataNotify();

        ulRst = VOS_ERR;
    }
    else
    {
        TTF_LOG2(ACPU_PID_NFEXT, DIAG_MODE_COMM, PS_PRINT_WARNING,
                "RingBufferPut Fail found ulRst = %u, sizeof=%u \r\n", iRst, sizeof(NF_EXT_DATA_RING_BUF_STRU));

        (VOS_VOID)NFExt_RingBufferGet(g_stExEntity.pRingBufferId, (VOS_CHAR *)(&stData), iRst);

        NF_EXT_STATS_INC(1, NF_EXT_STATS_PUT_BUF_FAIL);

        ulRst = VOS_ERR;
    }

    return ulRst;
}

/*****************************************************************************
     : NFExt_RcvNfExtInfoCfgReq
   : OM
   : VOS_VOID *pMsg
   : 
     : 
   :
   :

       :
  1.       : 20111122
           : caikai
       : Created
*****************************************************************************/
STATIC VOS_VOID NFExt_RcvNfExtInfoCfgReq(VOS_VOID *pMsg)
{
    OM_IPS_MNTN_INFO_CONFIG_REQ_STRU    *pstNfExtCfgReq;
    IPS_OM_MNTN_INFO_CONFIG_CNF_STRU    stNfExtCfgCnf;
    IPS_MNTN_RESULT_TYPE_ENUM_UINT32    enResult;

    pstNfExtCfgReq  = (OM_IPS_MNTN_INFO_CONFIG_REQ_STRU *)pMsg ;

    enResult        = IPS_MNTN_RESULT_OK;

    /*================================*/
    /**/
    /*================================*/

    /* Fill DIAG trans msg header */
    stNfExtCfgCnf.stDiagHdr.ulSenderCpuId   = VOS_LOCAL_CPUID;
    stNfExtCfgCnf.stDiagHdr.ulSenderPid     = ACPU_PID_NFEXT;
    stNfExtCfgCnf.stDiagHdr.ulReceiverCpuId = VOS_LOCAL_CPUID;
    stNfExtCfgCnf.stDiagHdr.ulReceiverPid   = MSP_PID_DIAG_APP_AGENT;   /* DIAGDIAGHIDS*/
    stNfExtCfgCnf.stDiagHdr.ulLength        = sizeof(IPS_OM_MNTN_INFO_CONFIG_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    stNfExtCfgCnf.stDiagHdr.ulMsgId         = ID_IPS_OM_MNTN_INFO_CONFIG_CNF;

    /* DIAG*/
    stNfExtCfgCnf.stDiagHdr.usOriginalId  = pstNfExtCfgReq->stDiagHdr.usOriginalId;
    stNfExtCfgCnf.stDiagHdr.usTerminalId  = pstNfExtCfgReq->stDiagHdr.usTerminalId;
    stNfExtCfgCnf.stDiagHdr.ulTimeStamp   = pstNfExtCfgReq->stDiagHdr.ulTimeStamp;
    stNfExtCfgCnf.stDiagHdr.ulSN          = pstNfExtCfgReq->stDiagHdr.ulSN;

    /* OM */
    stNfExtCfgCnf.stIpsMntnCfgCnf.enCommand  = pstNfExtCfgReq->stIpsMntnCfgReq.enCommand;
    stNfExtCfgCnf.stIpsMntnCfgCnf.enRslt     = enResult;

    /* OM */
    IPS_MNTN_SndCfgCnf2Om( ID_IPS_OM_MNTN_INFO_CONFIG_CNF,
        sizeof(IPS_OM_MNTN_INFO_CONFIG_CNF_STRU), &stNfExtCfgCnf );

    return;

}

/*****************************************************************************
     : NFExt_RcvOmMsg
   : NFExtOM
   : VOS_VOID *pMsg
   : 
     : 
   :
   :

       :
  1.       : 20111122
           : caikai
       : Created
*****************************************************************************/
VOS_VOID NFExt_RcvOmMsg(VOS_VOID *pMsg)
{
    VOS_UINT16          usMsgId;

    usMsgId = (VOS_UINT16)(*((VOS_UINT32 *)((VOS_UINT8 *)(pMsg) + VOS_MSG_HEAD_LENGTH)));

    switch ( usMsgId )
    {
        case ID_OM_IPS_ADVANCED_TRACE_CONFIG_REQ:
            IPS_MNTN_TraceAdvancedCfgReq(pMsg);
            break;

        case ID_OM_IPS_MNTN_INFO_CONFIG_REQ:
            NFExt_RcvNfExtInfoCfgReq(pMsg);
            break;

        default:
            TTF_LOG1(ACPU_PID_NFEXT, DIAG_MODE_COMM, PS_PRINT_WARNING,
                "NFExt_RcvConfig:Receive Unkown Type Message !\n", usMsgId);
            break;
    }

    return;
}

/******************************************************************************
 Prototype       : NFExt_BindToCpu
 Description     : TaskCPU
 Input           :
 Output          : NONE
 Return Value    : PS_SUCC   --- 
                   PS_FAIL   --- 
 History         :
   1.Date        : 2016-06-16
     Author      :
     Modification:
******************************************************************************/
VOS_VOID NFExt_BindToCpu(VOS_VOID)
{
    VOS_LONG            ret;
    pid_t               target_pid;
    VOS_INT             cpu;

    /* Pid */
    target_pid = current->pid;

    /* affinity */
    ret = sched_getaffinity(target_pid, &(g_stExEntity.orig_mask));
    if (ret < 0)
    {
        PS_PRINTF("warning: unable to get cpu affinity\n");
        return;
    }

    PSACORE_MEM_SET(&(g_stExEntity.curr_mask), cpumask_size(), 0, cpumask_size());

    /* affinity */
    for_each_cpu(cpu, &(g_stExEntity.orig_mask))
    {
        /* CPU0 */
        if ((0 < cpu) && (cpumask_test_cpu(cpu, &(g_stExEntity.orig_mask))))
        {
            cpumask_set_cpu((unsigned int)cpu, &(g_stExEntity.curr_mask));
        }
    }

    if (0 == cpumask_weight(&(g_stExEntity.curr_mask)))
    {
        cpumask_set_cpu(0, &(g_stExEntity.curr_mask));
        return;
    }

    ret = sched_setaffinity(target_pid, &(g_stExEntity.curr_mask));
    if (ret < 0)
    {
        PS_PRINTF("warning: unable to set cpu affinity\n");
        return;
    }

    return;
}

/*****************************************************************************
     : NFExt_ProcDataNotify
   : NFExt
   : VOS_VOID *pMsg
   : 
     : 
   :
   :

       :
  1.       : 20111122
           : caikai
       : Created
*****************************************************************************/
VOS_VOID NFExt_ProcDataNotify(VOS_VOID)
{
    NF_EXT_DATA_RING_BUF_STRU   stData;
    VOS_INT                     iRst;
    DIAG_TRANS_IND_STRU        *pstDiagTransData;
    VOS_UINT32                  ulDealCntOnce;

    if (VOS_NULL_PTR == g_stExEntity.pRingBufferId)
    {
        TTF_LOG(ACPU_PID_NFEXT, 0, PS_PRINT_WARNING,
            "NFExt_ProcDataNotify : ERROR : pRingBufferId is NULL!" );
        return;
    }

    ulDealCntOnce = 0;

    while (!OM_RingBufferIsEmpty(g_stExEntity.pRingBufferId))
    {
        /* 200 */
        if (NF_ONCE_DEAL_MAX_CNT <= ulDealCntOnce)
        {
            NFExt_SndDataNotify();
            break;
        }

        iRst = NFExt_RingBufferGet(g_stExEntity.pRingBufferId, (VOS_CHAR *)&stData, sizeof(NF_EXT_DATA_RING_BUF_STRU));
        if (sizeof(NF_EXT_DATA_RING_BUF_STRU) == iRst)
        {
            pstDiagTransData = (DIAG_TRANS_IND_STRU *)(stData.pData);

            if ( VOS_OK != DIAG_TransReport(pstDiagTransData))
            {
                TTF_LOG(ACPU_PID_NFEXT, DIAG_MODE_COMM, PS_PRINT_ERROR, "NFExt_ProcDataNotify, ERROR, Call DIAG_TransReport fail!");
            }

            NF_EXT_MEM_FREE(ACPU_PID_NFEXT, stData.pData);
        }
        else if (0 == iRst)
        {
            TTF_LOG(ACPU_PID_NFEXT, 0, PS_PRINT_WARNING,
                "NFExt_ProcDataNotify : ERROR : Get null from ring buffer!");

            break;
        }
        else
        {
            TTF_LOG2(ACPU_PID_NFEXT, 0, PS_PRINT_WARNING,
                "NFExt_ProcDataNotify : ERROR : Get data error from ring buffer!", iRst, sizeof(NF_EXT_DATA_RING_BUF_STRU));

            NF_EXT_STATS_INC(1, NF_EXT_STATS_GET_BUF_FAIL);

            NFExt_FlushRingBuffer(g_stExEntity.pRingBufferId);

            break;
        }

        ulDealCntOnce++;
    }
}

/*****************************************************************************
     : NFExt_EventProc
   : NFExt
   : struct MsgCB * pMsg
   : 
     : 
   :
   :

       :
  1.       : 20111122
           : caikai
       : Created
*****************************************************************************/
STATIC VOS_VOID NFExt_EventProc(VOS_UINT32 ulEvent)
{
    if (ulEvent & NFEXT_DATA_PROC_NOTIFY)
    {
        NFExt_ProcDataNotify();
    }

    return;
}

/*****************************************************************************
     : NFExt_MsgProc
   : NFExt
   : struct MsgCB * pMsg
   : 
     : 
   :
   :

       :
  1.       : 20111122
           : caikai
       : Created
*****************************************************************************/
VOS_VOID NFExt_MsgProc( struct MsgCB * pMsg )
{
    if ( VOS_NULL_PTR == pMsg )
    {
        TTF_LOG(ACPU_PID_NFEXT, DIAG_MODE_COMM, PS_PRINT_WARNING,"NFExt_MsgProc: Message is NULL !" );
        return;
    }

    switch ( pMsg->ulSenderPid )
    {
        case MSP_PID_DIAG_APP_AGENT:      /* OM */
            NFExt_RcvOmMsg( (void *)pMsg );
            break;

        default:
            break;
    }

    return;
}

/*****************************************************************************
     : NFExt_FidTask
   : OAMSDT
   : void
   : 
     : void
   :
   :

       :
  1.       : 20111122
           : t00148005
       : Created
*****************************************************************************/
VOS_VOID NFExt_FidTask(VOS_VOID)
{
    MsgBlock                           *pMsg          = VOS_NULL_PTR;
    VOS_UINT32                          ulEvent       = 0;
    VOS_UINT32                          ulTaskID      = 0;
    VOS_UINT32                          ulRtn         = VOS_ERR;
    VOS_UINT32                          ulEventMask   = 0;
    VOS_UINT32                          ulExpectEvent = 0;

    ulTaskID = VOS_GetCurrentTaskID();
    if (PS_NULL_UINT32 == ulTaskID)
    {
        TTF_LOG(ACPU_PID_NFEXT, DIAG_MODE_COMM, PS_PRINT_WARNING, "NFExt_FidTask: TaskID is invalid.");
        return;
    }

    if (VOS_OK != VOS_CreateEvent(ulTaskID))
    {
        TTF_LOG(ACPU_PID_NFEXT, DIAG_MODE_COMM, PS_PRINT_WARNING, "NFExt_FidTask: create event fail.");
        return;
    }

    g_ulNFExtTaskId = ulTaskID;

    NFExt_BindToCpu();

    ulExpectEvent = NFEXT_DATA_PROC_NOTIFY | VOS_MSG_SYNC_EVENT;
    ulEventMask   = VOS_EVENT_ANY | VOS_EVENT_WAIT;

    for ( ; ; )
    {
        ulRtn = VOS_EventRead(ulExpectEvent, ulEventMask, 0, &ulEvent);
        if (VOS_OK != ulRtn)
        {
            TTF_LOG(ACPU_PID_NFEXT, DIAG_MODE_COMM, PS_PRINT_WARNING, "NFExt_FidTask: read event error.");

            continue;
        }

        /*  */
        if (VOS_MSG_SYNC_EVENT != ulEvent)
        {
            NFExt_EventProc(ulEvent);

            continue;
        }

        pMsg = (MsgBlock *)VOS_GetMsg(ulTaskID);
        if (VOS_NULL_PTR != pMsg)
        {
            if (ACPU_PID_NFEXT == pMsg->ulReceiverPid)
            {
                NFExt_MsgProc(pMsg);
            }

            (VOS_VOID)VOS_FreeMsg(ACPU_PID_NFEXT, pMsg);
        }
    }
}

/*****************************************************************************
     : NFExt_PidInit
   : NFExt_Pid
   : ip - 
   : 
     : VOS_OK, VOS_ERR
   :
   :

       :
  1.       : 20111122
           : caikai
       : Created
*****************************************************************************/
VOS_UINT32 NFExt_PidInit( enum VOS_INIT_PHASE_DEFINE ip )
{
    switch ( ip )
    {
        case VOS_IP_LOAD_CONFIG:
            /* RingBuffer */
            g_stExEntity.pRingBufferId = OM_RingBufferCreate(NF_EXT_RING_BUF_SIZE);
            if ( VOS_NULL_PTR == g_stExEntity.pRingBufferId )
            {
                PS_PRINTF("NFExt_PidInit : ERROR : Create ring buffer Failed!" );
                return VOS_ERR;
            }

            /*  */
            VOS_SpinLockInit(&(g_stExEntity.stLockTxTask));
            break;

        case VOS_IP_FARMALLOC:
        case VOS_IP_INITIAL:
        case VOS_IP_ENROLLMENT:
        case VOS_IP_LOAD_DATA:
        case VOS_IP_FETCH_DATA:
        case VOS_IP_STARTUP:
        case VOS_IP_RIVAL:
        case VOS_IP_KICKOFF:
        case VOS_IP_STANDBY:
        case VOS_IP_BROADCAST_STATE:
        case VOS_IP_RESTART:
            break;
        default:
            break;
    }

    return VOS_OK;
}


/*****************************************************************************
     : NFExt_FidInit
   : NFExt_Fid
   : ip - 
   : 
     : VOS_OK, VOS_ERR
   :
   :

       :
  1.       : 20111122
           : caikai
       : Created
*****************************************************************************/
VOS_UINT32 NFExt_FidInit ( enum VOS_INIT_PHASE_DEFINE ip )
{
    VOS_UINT32                          ulRslt;

    switch ( ip )
    {
        case   VOS_IP_LOAD_CONFIG:
            /*  */
            if ( 0 != NFExt_Init() )
            {
                PS_PRINTF("NFExt_FidInit NFExt_Init FAIL!\n");
                return VOS_ERR;
            }

            /* PID */
            ulRslt = VOS_RegisterPIDInfo(ACPU_PID_NFEXT,
                                (Init_Fun_Type)NFExt_PidInit,
                                (Msg_Fun_Type)NFExt_MsgProc);
            if( VOS_OK != ulRslt )
            {
                PS_PRINTF("NFExt_FidInit VOS_RegisterPIDInfo FAIL!\n");
                return VOS_ERR;
            }

            ulRslt = VOS_RegisterMsgTaskEntry(ACPU_FID_NFEXT, (VOS_VOIDFUNCPTR)NFExt_FidTask);
            if (VOS_OK != ulRslt)
            {
                PS_PRINTF("NFExt_FidInit VOS_RegisterMsgTaskEntry fail!\n");
                return VOS_ERR;
            }

            ulRslt = VOS_RegisterMsgTaskPrio(ACPU_FID_NFEXT, VOS_PRIORITY_M4);
            if( VOS_OK != ulRslt )
            {
                PS_PRINTF("NFExt_FidInit VOS_RegisterTaskPrio Failed!\n");
                return VOS_ERR;
            }

            break;

        case   VOS_IP_FARMALLOC:
        case   VOS_IP_INITIAL:
        case   VOS_IP_ENROLLMENT:
        case   VOS_IP_LOAD_DATA:
        case   VOS_IP_FETCH_DATA:
        case   VOS_IP_STARTUP:
        case   VOS_IP_RIVAL:
        case   VOS_IP_KICKOFF:
        case   VOS_IP_STANDBY:
        case   VOS_IP_BROADCAST_STATE:
        case   VOS_IP_RESTART:
        case   VOS_IP_BUTT:
            break;

        default:
            break;
    }

    return PS_SUCC;
}


