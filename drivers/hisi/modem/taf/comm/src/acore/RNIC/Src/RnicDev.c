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
#include "RnicEntity.h"
#include "RnicDebug.h"
#include "RnicCtx.h"
#include "RnicDev.h"
#include <linux/version.h>
#include <net/sock.h>

/*****************************************************************************
    .C
*****************************************************************************/

#define THIS_FILE_ID PS_FILE_ID_RNIC_DEV_C

/******************************************************************************
   2 
******************************************************************************/

/******************************************************************************
   3 
******************************************************************************/

/******************************************************************************
   4 
*****************************************************************************/
/*  */
    static const struct net_device_ops rnic_ops = {
           .ndo_stop                = RNIC_StopNetCard,
           .ndo_open                = RNIC_OpenNetCard,
           .ndo_start_xmit          = RNIC_StartXmit,
           .ndo_set_mac_address     = RNIC_SetMacAddress,
           .ndo_change_mtu          = RNIC_ChangeMtu,
           .ndo_tx_timeout          = RNIC_ProcTxTimeout,
           .ndo_do_ioctl            = RNIC_Ioctrl,
           .ndo_get_stats           = RNIC_GetNetCardStats,
    };

#define RNIC_DEV_NAME_PREFIX            "rmnet"
const RNIC_NETCARD_ELEMENT_TAB_STRU           g_astRnicManageTbl[RNIC_NET_ID_MAX_NUM] =
{
    {
      "0",
      {{0x58, 0x02, 0x03, 0x04, 0x05, 0x06}, {0x00, 0x11, 0x09, 0x64, 0x01, 0x01}, 0x0008, {0, 0}},
      {{0x58, 0x02, 0x03, 0x04, 0x05, 0x06}, {0x00, 0x11, 0x09, 0x64, 0x01, 0x01}, 0xDD86, {0, 0}},
      MODEM_ID_0, RNIC_RMNET_ID_0, {0, 0, 0, 0, 0}},

    { "1",
      {{0x58, 0x02, 0x03, 0x04, 0x05, 0x07}, {0x00, 0x11, 0x09, 0x64, 0x01, 0x02}, 0x0008, {0, 0}},
      {{0x58, 0x02, 0x03, 0x04, 0x05, 0x07}, {0x00, 0x11, 0x09, 0x64, 0x01, 0x02}, 0xDD86, {0, 0}},
      MODEM_ID_0, RNIC_RMNET_ID_1, {0, 0, 0, 0, 0}},

    { "2",
      {{0x58, 0x02, 0x03, 0x04, 0x05, 0x08}, {0x00, 0x11, 0x09, 0x64, 0x01, 0x03}, 0x0008, {0, 0}},
      {{0x58, 0x02, 0x03, 0x04, 0x05, 0x08}, {0x00, 0x11, 0x09, 0x64, 0x01, 0x03}, 0xDD86, {0, 0}},
      MODEM_ID_0, RNIC_RMNET_ID_2, {0, 0, 0, 0, 0}},

    { "3",
      {{0x58, 0x02, 0x03, 0x04, 0x05, 0x09}, {0x00, 0x11, 0x09, 0x64, 0x01, 0x04}, 0x0008, {0, 0}},
      {{0x58, 0x02, 0x03, 0x04, 0x05, 0x09}, {0x00, 0x11, 0x09, 0x64, 0x01, 0x04}, 0xDD86, {0, 0}},
      MODEM_ID_1, RNIC_RMNET_ID_3, {0, 0, 0, 0, 0}},

    { "4",
      {{0x58, 0x02, 0x03, 0x04, 0x05, 0x0a}, {0x00, 0x11, 0x09, 0x64, 0x01, 0x05}, 0x0008, {0, 0}},
      {{0x58, 0x02, 0x03, 0x04, 0x05, 0x0a}, {0x00, 0x11, 0x09, 0x64, 0x01, 0x05}, 0xDD86, {0, 0}},
      MODEM_ID_1, RNIC_RMNET_ID_4, {0, 0, 0, 0, 0}},



    { "_ims00",
      {{0x58, 0x02, 0x03, 0x04, 0x05, 0x0d}, {0x00, 0x11, 0x09, 0x64, 0x01, 0x08}, 0x0008, {0, 0}},
      {{0x58, 0x02, 0x03, 0x04, 0x05, 0x0d}, {0x00, 0x11, 0x09, 0x64, 0x01, 0x08}, 0xDD86, {0, 0}},
      MODEM_ID_0, RNIC_RMNET_ID_IMS00, {0, 0, 0, 0, 0}},

    { "_r_ims00",
      {{0x58, 0x02, 0x03, 0x04, 0x05, 0x0e}, {0x00, 0x11, 0x09, 0x64, 0x01, 0x09}, 0x0008, {0, 0}},
      {{0x58, 0x02, 0x03, 0x04, 0x05, 0x0e}, {0x00, 0x11, 0x09, 0x64, 0x01, 0x09}, 0xDD86, {0, 0}},
      MODEM_ID_0, RNIC_RMNET_ID_R_IMS00, {0, 0, 0, 0, 0}},

    { "_ims10",
      {{0x58, 0x02, 0x03, 0x04, 0x05, 0x0f}, {0x00, 0x11, 0x09, 0x64, 0x01, 0x0a}, 0x0008, {0, 0}},
      {{0x58, 0x02, 0x03, 0x04, 0x05, 0x0f}, {0x00, 0x11, 0x09, 0x64, 0x01, 0x0a}, 0xDD86, {0, 0}},
      MODEM_ID_1, RNIC_RMNET_ID_IMS10, {0, 0, 0, 0, 0}},

    { "_r_ims10",
      {{0x58, 0x02, 0x03, 0x04, 0x05, 0x10}, {0x00, 0x11, 0x09, 0x64, 0x01, 0x0b}, 0x0008, {0, 0}},
      {{0x58, 0x02, 0x03, 0x04, 0x05, 0x10}, {0x00, 0x11, 0x09, 0x64, 0x01, 0x0b}, 0xDD86, {0, 0}},
      MODEM_ID_1, RNIC_RMNET_ID_R_IMS10, {0, 0, 0, 0, 0}},
    { "_tun00",
      {{0x58, 0x02, 0x03, 0x04, 0x05, 0x11}, {0x00, 0x11, 0x09, 0x64, 0x01, 0x0c}, 0x0008, {0, 0}},
      {{0x58, 0x02, 0x03, 0x04, 0x05, 0x11}, {0x00, 0x11, 0x09, 0x64, 0x01, 0x0c}, 0xDD86, {0, 0}},
      MODEM_ID_BUTT, RNIC_RMNET_ID_TUN00, {0, 0, 0, 0, 0}},

    { "_tun01",
      {{0x58, 0x02, 0x03, 0x04, 0x05, 0x12}, {0x00, 0x11, 0x09, 0x64, 0x01, 0x0d}, 0x0008, {0, 0}},
      {{0x58, 0x02, 0x03, 0x04, 0x05, 0x12}, {0x00, 0x11, 0x09, 0x64, 0x01, 0x0d}, 0xDD86, {0, 0}},
      MODEM_ID_BUTT, RNIC_RMNET_ID_TUN01, {0, 0, 0, 0, 0}},

    { "_tun02",
      {{0x58, 0x02, 0x03, 0x04, 0x05, 0x13}, {0x00, 0x11, 0x09, 0x64, 0x01, 0x0e}, 0x0008, {0, 0}},
      {{0x58, 0x02, 0x03, 0x04, 0x05, 0x13}, {0x00, 0x11, 0x09, 0x64, 0x01, 0x0e}, 0xDD86, {0, 0}},
      MODEM_ID_BUTT, RNIC_RMNET_ID_TUN02, {0, 0, 0, 0, 0}},

    { "_tun03",
      {{0x58, 0x02, 0x03, 0x04, 0x05, 0x14}, {0x00, 0x11, 0x09, 0x64, 0x01, 0x0f}, 0x0008, {0, 0}},
      {{0x58, 0x02, 0x03, 0x04, 0x05, 0x14}, {0x00, 0x11, 0x09, 0x64, 0x01, 0x0f}, 0xDD86, {0, 0}},
      MODEM_ID_BUTT, RNIC_RMNET_ID_TUN03, {0, 0, 0, 0, 0}},

    { "_tun04",
      {{0x58, 0x02, 0x03, 0x04, 0x05, 0x15}, {0x00, 0x11, 0x09, 0x64, 0x01, 0x10}, 0x0008, {0, 0}},
      {{0x58, 0x02, 0x03, 0x04, 0x05, 0x15}, {0x00, 0x11, 0x09, 0x64, 0x01, 0x10}, 0xDD86, {0, 0}},
      MODEM_ID_BUTT, RNIC_RMNET_ID_TUN04, {0, 0, 0, 0, 0}},

    { "_tun10",
      {{0x58, 0x02, 0x03, 0x04, 0x05, 0x16}, {0x00, 0x11, 0x09, 0x64, 0x01, 0x11}, 0x0008, {0, 0}},
      {{0x58, 0x02, 0x03, 0x04, 0x05, 0x16}, {0x00, 0x11, 0x09, 0x64, 0x01, 0x11}, 0xDD86, {0, 0}},
      MODEM_ID_BUTT, RNIC_RMNET_ID_TUN10, {0, 0, 0, 0, 0}},

    { "_tun11",
      {{0x58, 0x02, 0x03, 0x04, 0x05, 0x17}, {0x00, 0x11, 0x09, 0x64, 0x01, 0x12}, 0x0008, {0, 0}},
      {{0x58, 0x02, 0x03, 0x04, 0x05, 0x17}, {0x00, 0x11, 0x09, 0x64, 0x01, 0x12}, 0xDD86, {0, 0}},
      MODEM_ID_BUTT, RNIC_RMNET_ID_TUN11, {0, 0, 0, 0, 0}},

    { "_tun12",
      {{0x58, 0x02, 0x03, 0x04, 0x05, 0x18}, {0x00, 0x11, 0x09, 0x64, 0x01, 0x13}, 0x0008, {0, 0}},
      {{0x58, 0x02, 0x03, 0x04, 0x05, 0x18}, {0x00, 0x11, 0x09, 0x64, 0x01, 0x13}, 0xDD86, {0, 0}},
      MODEM_ID_BUTT, RNIC_RMNET_ID_TUN12, {0, 0, 0, 0, 0}},

    { "_tun13",
      {{0x58, 0x02, 0x03, 0x04, 0x05, 0x19}, {0x00, 0x11, 0x09, 0x64, 0x01, 0x14}, 0x0008, {0, 0}},
      {{0x58, 0x02, 0x03, 0x04, 0x05, 0x19}, {0x00, 0x11, 0x09, 0x64, 0x01, 0x14}, 0xDD86, {0, 0}},
      MODEM_ID_BUTT, RNIC_RMNET_ID_TUN13, {0, 0, 0, 0, 0}},

    { "_tun14",
      {{0x58, 0x02, 0x03, 0x04, 0x05, 0x1a}, {0x00, 0x11, 0x09, 0x64, 0x01, 0x15}, 0x0008, {0, 0}},
      {{0x58, 0x02, 0x03, 0x04, 0x05, 0x1a}, {0x00, 0x11, 0x09, 0x64, 0x01, 0x15}, 0xDD86, {0, 0}},
      MODEM_ID_BUTT, RNIC_RMNET_ID_TUN14, {0, 0, 0, 0, 0}},


    {
      "_emc0",
      {{0x58, 0x02, 0x03, 0x04, 0x05, 0x1b}, {0x00, 0x11, 0x09, 0x64, 0x01, 0x16}, 0x0008, {0, 0}},
      {{0x58, 0x02, 0x03, 0x04, 0x05, 0x1b}, {0x00, 0x11, 0x09, 0x64, 0x01, 0x16}, 0xDD86, {0, 0}},
      MODEM_ID_0, RNIC_RMNET_ID_EMC0, {0, 0, 0, 0, 0}},


};


/******************************************************************************
   5 
******************************************************************************/
/*****************************************************************************
     : RNIC_StopNetCard
   : RNIC
   : pstNetDev:
   : 
     : VOS_INT:RNIC_OK, RNIC_ERROR
   :
   :

       :
 1.       : 20111206
          : 
      : 
*****************************************************************************/
VOS_INT RNIC_StopNetCard(
    struct net_device                  *pstNetDev
)
{
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv = VOS_NULL_PTR;

    /*  */
    pstPriv = (RNIC_NETCARD_DEV_INFO_STRU *)netdev_priv(pstNetDev);


    /* netif_stop_queue() */
    netif_stop_queue(pstNetDev);

    /*  */
    pstPriv->enStatus = RNIC_NETCARD_STATUS_CLOSED;

    return 0;
}

/*****************************************************************************
     : RNIC_OpenNetCard
   : RNIC
   : pstNetDev:
   : 
     : VOS_INT:RNIC_OK, RNIC_ERR, RNIC_BUSY
   :
   :

       :
 1.       : 20111206
          : 
      : 
*****************************************************************************/
VOS_INT RNIC_OpenNetCard(
    struct net_device                  *pstNetDev
)
{
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv = VOS_NULL_PTR;

    /*  */
    pstPriv = (RNIC_NETCARD_DEV_INFO_STRU *)netdev_priv(pstNetDev);


    /*  */
    netif_start_queue(pstNetDev);

    /*  */
    pstPriv->enStatus = RNIC_NETCARD_STATUS_OPENED;

    return 0;
}

/*****************************************************************************
     : RNIC_StartXmit
   : RNIC
   : pstSkb   :SKBUF
             pstNetDev:
   : 
     : netdev_tx_t:NETDEV_TX_OK
   :
   :

       :
 1.       : 20111206
          : 
      : 
 2.       : 2012531
          : A00165503
      : DTS2012053004651: PS, A, 
                192.168.1.1 ping
 3.       : 2012620
          : A00165503
      : DTS2012061904440: 
 4.       : 2012830
          : l60609
      : AP
 5.       : 20121123
          : f00179208
      : DSDA Phase I: RNIC
*****************************************************************************/
netdev_tx_t RNIC_StartXmit(
    struct sk_buff                     *pstSkb,
    struct net_device                  *pstNetDev
)
{
    RNIC_SPEC_CTX_STRU                 *pstNetCntxt = VOS_NULL_PTR;
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv     = VOS_NULL_PTR;

    pstPriv     = (RNIC_NETCARD_DEV_INFO_STRU *)netdev_priv(pstNetDev);

    pstNetCntxt = RNIC_GetNetCntxtByRmNetId(pstPriv->enRmNetId);
    if (VOS_NULL_PTR == pstNetCntxt)
    {
        IMM_ZcFreeAny(pstSkb);
        RNIC_DBG_NET_TX_RMNETID_ERR_NUM(1);
        return NETDEV_TX_OK;
    }
    
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 9, 0))
    /* The value is a bit-shift of 1 second,
     * so 4 is ~64ms of queued data. Only affects local TCP
     * sockets.
     */
    sk_pacing_shift_update(pstSkb->sk, 4);
#endif

    /* MODEM */
    RNIC_ProcessTxDataByModemType(pstNetCntxt, pstSkb);

    return NETDEV_TX_OK;
}

/*****************************************************************************
     : RNIC_SetMacAddress
   : RNICMAC
   : pstNetDev:
             pMacAddr :MAC
   : 
     : VOS_INT:RNIC_OK, RNIC_ADDR_INVALID
   :
   :

      :
 1.       : 20111206
          : 
      : 
*****************************************************************************/
VOS_INT RNIC_SetMacAddress(
    struct net_device                  *pstNetDev,
    VOS_VOID                           *pMacAddr
)
{
    struct sockaddr                    *pstAddr;
    VOS_INT                             lValid;

    /*  */
    pstAddr = (struct sockaddr *)pMacAddr;

    /* MAC */
    lValid = is_valid_ether_addr((VOS_UINT8 *)pstAddr->sa_data);
    if (VOS_FALSE == lValid)
    {
        RNIC_DEV_ERR_PRINTK("RNIC_SetMacAddress: Ether addr is invalid!");
        return -EINVAL;
    }

    /* MAC */
    memcpy(pstNetDev->dev_addr, pstAddr->sa_data, pstNetDev->addr_len);

    return 0;
}

/*****************************************************************************
     : RNIC_ChangeMtu
   : RNICMTU
   : pstNetDev:
             lNewMtu  :MTU
   : 
     : VOS_INT:RNIC_OK, RNIC_ERROR, RNIC_OUT_RANGE
   :
   :

      :
 1.       : 20111206
          : 
      : 

  2.       : 20161227
           : A00165503
       : DTS2016121600573: VOWIFI
*****************************************************************************/
VOS_INT RNIC_ChangeMtu(
    struct net_device                  *pstNetDev,
    VOS_INT                             lNewMtu
)
{
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv = VOS_NULL_PTR;

    pstPriv = (RNIC_NETCARD_DEV_INFO_STRU *)netdev_priv(pstNetDev);

    if (RNIC_RMNET_R_IS_VALID(pstPriv->enRmNetId))
    {
        if (lNewMtu > RNIC_R_IMS_MAX_PACKET)
        {
            RNIC_DEV_ERR_PRINTK("RNIC_ChangeMtu: R IMS Mtu out of range!");
            return -EINVAL;
        }
    }
    else
    {
        if (lNewMtu > RNIC_MAX_PACKET)
        {
            RNIC_DEV_ERR_PRINTK("RNIC_ChangeMtu: Mtu out of range!");
            return -EINVAL;
        }
    }

    /* mtu */
    pstNetDev->mtu = (VOS_UINT)lNewMtu;

    return 0;
}

/*****************************************************************************
     : RNIC_Tx_Timeout
   : RNIC,,
             
   : pstNetDev:
   : 
     : VOS_VOID
   :
   :

       :
 1.       : 20111206
          : 
      : 
*****************************************************************************/
VOS_VOID RNIC_ProcTxTimeout(
    struct net_device                  *pstNetDev
)
{
    return;
}

/*****************************************************************************
     : RNIC_Ioctrl
   : RNICioctrl,ioctrl,
   : pstNetDev:
             pstIfr   :
             lCmd     :
   : 
     :   RNIC_NOTSUPP
   :
   :

       :
 1.       : 20111206
          : 
      : 
*****************************************************************************/
VOS_INT RNIC_Ioctrl(
    struct net_device                  *pstNetDev,
    struct ifreq                       *pstIfr,
    VOS_INT                             lCmd
)
{
    return -EOPNOTSUPP;
}

/*****************************************************************************
     : RNIC_GetNetCardStats
   : RNIC
   : pstNetDev:
   : 
     : net_device_stats
   :
   :

      :
 1.       : 20111206
          : 
      : 
*****************************************************************************/
struct net_device_stats *RNIC_GetNetCardStats(
    struct net_device                  *pstNetDev
)

{
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv = VOS_NULL_PTR;

    /*  */
    pstPriv = (RNIC_NETCARD_DEV_INFO_STRU *)netdev_priv(pstNetDev);

    /*  */
    return &pstPriv->stStats;
}

/*****************************************************************************
     : RNIC_DeInitNetCard
   : RNIC
   : pNetDev:
   : 
     : VOS_VOID
   :
   :

       :
 1.       : 20111206
          : 
      : 
 2.       : 20121123
          : f00179208
      : DSDA Phase I: RNIC
*****************************************************************************/
VOS_VOID RNIC_DeinitNetCard(
    struct net_device                  *pstNetDev
)
{
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv     = VOS_NULL_PTR;
    RNIC_SPEC_CTX_STRU                 *pstNetCntxt = VOS_NULL_PTR;

    /*  */
    pstPriv     = (RNIC_NETCARD_DEV_INFO_STRU *)netdev_priv(pstNetDev);
    pstNetCntxt = RNIC_GET_SPEC_NET_CTX(pstPriv->enRmNetId);

    /*  */
    netif_carrier_off(pstNetDev);

    /*  */
    netif_stop_queue(pstNetDev);

    /*  */
    unregister_netdev(pstNetDev);

    /*  */
    free_netdev(pstNetDev);

    /*  */
    pstNetCntxt->pstPriv = VOS_NULL_PTR;

    return;
}

/*****************************************************************************
     : RNIC_InitNetCard
   : RNICRNIC
   : 
   : VOS_VOID
     : VOS_INT:RNIC_NOMEM, RNIC_STATE, RNIC_OK
   :
   :

      :
 1.       : 20111206
          : 
      : 
 2.       : 20121123
          : f00179208
      : DSDA Phase I: RNIC

  3.       : 20161227
           : A00165503
       : DTS2016121600573: VOWIFI
*****************************************************************************/
VOS_INT __init RNIC_InitNetCard(VOS_VOID)
{
    struct net_device                  *pstDev      = VOS_NULL_PTR;
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv     = VOS_NULL_PTR;
    RNIC_SPEC_CTX_STRU                 *pstNetCntxt = VOS_NULL_PTR;
    VOS_INT                             lRegRst;
    VOS_UINT8                           ucIndex;

    printk("RNIC_InitNetCard: entry, %u", VOS_GetSlice());

    for (ucIndex = 0 ; ucIndex < RNIC_NET_ID_MAX_NUM ; ucIndex++)
    {
        /*  */
        pstNetCntxt = RNIC_GET_SPEC_NET_CTX(ucIndex);
        pstNetCntxt->pstPriv = VOS_NULL_PTR;

        /* netdev */
        /* alloc_etherdevnet_device RNIC_NETCARD_DEV_INFO_STRU
           RNIC_NETCARD_DEV_INFO_STRUnet_device */
        pstDev = alloc_etherdev(sizeof(RNIC_NETCARD_DEV_INFO_STRU));
        if (VOS_NULL_PTR == pstDev)
        {
            RNIC_DEV_ERR_PRINTK("RNIC_InitNetCard: net ptr is Null!");
            continue;
        }

        /* MAC, */
        memcpy(pstDev->dev_addr, RNIC_GET_DST_MAC_ADDR(ucIndex), RNIC_MAC_ADDR_LEN);

        /* MTU */
        pstDev->mtu = RNIC_DEFAULT_MTU;

        snprintf(pstDev->name, sizeof(pstDev->name),
            "%s%s",
            RNIC_DEV_NAME_PREFIX, g_astRnicManageTbl[ucIndex].pucRnicNetCardName);

        /* net_device */
        pstDev->netdev_ops = &rnic_ops;

        /*  */
        pstPriv = (RNIC_NETCARD_DEV_INFO_STRU *)netdev_priv(pstDev);
        pstPriv->pstDev    = pstDev;
        pstPriv->enRmNetId = ucIndex;


        /*  */
        netif_carrier_off(pstDev);

        /*  */
        netif_stop_queue(pstDev);

        /* register_netdevNetcard */
        lRegRst = register_netdev(pstDev);
        if (VOS_OK != lRegRst)
        {
            /* RNIC */
            RNIC_DEV_ERR_PRINTK("RNIC_InitNetCard:Register netdev failed!");
            free_netdev(pstDev);
            continue;
        }

        /*  */
        pstNetCntxt->pstPriv = pstPriv;

        /*  */
        netif_carrier_on(pstDev);

        /*  */
        netif_start_queue(pstDev);
    }

    printk("RNIC_InitNetCard: eixt, %u", VOS_GetSlice());

    return 0;
}

module_init(RNIC_InitNetCard);





