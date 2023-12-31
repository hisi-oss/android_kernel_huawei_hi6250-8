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
#include "RnicDebug.h"
#include "RnicCtx.h"


/*****************************************************************************
  2 
*****************************************************************************/


/******************************************************************************
   3 
******************************************************************************/


/******************************************************************************
   4 
******************************************************************************/

RNIC_MNTN_STATS_STRU                    g_stRnicMntnStats = {0};
RNIC_STATS_INFO_STRU                    g_astRnicStats[RNIC_NET_ID_MAX_NUM];
RNIC_RMNET_CONFIG_CHECK_INFO_STRU       g_stRnicRmnetConfigCheckInfo;
VOS_UINT32                              g_ulRnicPrintUlDataFlg = VOS_FALSE;
VOS_UINT32                              g_ulRnicPrintDlDataFlg = VOS_FALSE;


/******************************************************************************
   5 
******************************************************************************/

VOS_VOID RNIC_SetPrintUlDataFlg(VOS_UINT32 ulFlg)
{
    g_ulRnicPrintUlDataFlg = ulFlg;
}

/*****************************************************************************
     : RNIC_ShowRnicPdpStats
   : RNIC pdp
   : ucRmNetId : ID
   : 
     :

   :
   :

   :
    1.       : 20121123
             : f00179208
         : 
*****************************************************************************/
VOS_VOID RNIC_ShowRnicPdpStats(VOS_UINT8 ucRmNetId)
{
    RNIC_PDP_CTX_STRU                  *pstPdpCtx;

    if (ucRmNetId >= RNIC_NET_ID_MAX_NUM)
    {
        PS_PRINTF("RNIC_ShowRnicPdpStats: NetId overtop, ucRmNetId = %d\n", ucRmNetId);
        return;
    }

    pstPdpCtx                           = RNIC_GetPdpCtxAddr(ucRmNetId);

    PS_PRINTF("RNIC %d IPV4 PDP STATUS                     %d\n",   ucRmNetId, pstPdpCtx->stIpv4PdpInfo.enRegStatus);
    PS_PRINTF("RNIC %d IPV4 PDP RABID                      %d\n",   ucRmNetId, pstPdpCtx->stIpv4PdpInfo.ucRabId);
    PS_PRINTF("RNIC %d IPV4 PDP PDNID                      %d\n",   ucRmNetId, pstPdpCtx->stIpv4PdpInfo.ucPdnId);
    PS_PRINTF("RNIC %d IPV4 PDP IPV4ADDR                   %d\n\n", ucRmNetId, pstPdpCtx->stIpv4PdpInfo.ulIpv4Addr);

    PS_PRINTF("RNIC %d IPV6 PDP STATUS                     %d\n",   ucRmNetId, pstPdpCtx->stIpv6PdpInfo.enRegStatus);
    PS_PRINTF("RNIC %d IPV6 PDP RABID                      %d\n",   ucRmNetId, pstPdpCtx->stIpv6PdpInfo.ucRabId);
    PS_PRINTF("RNIC %d IPV6 PDP PDNID                      %d\n",   ucRmNetId, pstPdpCtx->stIpv6PdpInfo.ucPdnId);
    PS_PRINTF("RNIC %d IPV6 PDP IPV6ADDR                   %s\n\n", ucRmNetId, pstPdpCtx->stIpv6PdpInfo.aucIpv6Addr);

    PS_PRINTF("RNIC %d IPV4V6 PDP STATUS                   %d\n", ucRmNetId, pstPdpCtx->stIpv4v6PdpInfo.enRegStatus);
    PS_PRINTF("RNIC %d IPV4V6 PDP RABID                    %d\n", ucRmNetId, pstPdpCtx->stIpv4v6PdpInfo.ucRabId);
    PS_PRINTF("RNIC %d IPV4V6 PDP PDNID                    %d\n", ucRmNetId, pstPdpCtx->stIpv4v6PdpInfo.ucPdnId);
    PS_PRINTF("RNIC %d IPV4V6 PDP IPV4ADDR                 %d\n", ucRmNetId, pstPdpCtx->stIpv4v6PdpInfo.ulIpv4Addr);
    PS_PRINTF("RNIC %d IPV4V6 PDP IPV6ADDR                 %s\n", ucRmNetId, pstPdpCtx->stIpv4v6PdpInfo.aucIpv6Addr);
}

/*****************************************************************************
     : RNIC_ShowUlProcStats
   : RNIC
   : ucRmNetId : ID
   : 
     :

   :
   :

   :
    1.       : 20120112
             : S62952
         : 
    2.       : 20121123
             : f00179208
         : DSDA Phase I: RNIC
*****************************************************************************/
VOS_VOID RNIC_ShowULProcStats(VOS_UINT8 ucRmNetId)
{
    PS_PRINTF("NET TX RMNETID ERR NUM                                 %d\n", g_stRnicMntnStats.ulNetTxRmNetIdErrNum);
    PS_PRINTF("SPE TX PORTID ERR NUM                                  %d\n", g_stRnicMntnStats.ulSpeTxPortIdErrNum);

    if (ucRmNetId >= RNIC_NET_ID_MAX_NUM)
    {
        PS_PRINTF("RNIC_ShowUlProcStats: NetId overtop, ucRmNetId = %d\n", ucRmNetId);
        return;
    }

    /*  */
    PS_PRINTF("RNIC %d                                        %d\n", ucRmNetId, g_stRnicCtx.astSpecCtx[ucRmNetId].enFlowCtrlStatus);
    PS_PRINTF("RNIC %dIPV4                          %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlRecvIpv4PktNum);
    PS_PRINTF("RNIC %dIPV6                          %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlRecvIpv6PktNum);
    PS_PRINTF("IPV4V6RNIC %dIPV4IPV6      %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlRecvIpv4v6PktNum);
    PS_PRINTF("RNIC %d                      %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlRecvUndiaPktNum);
    PS_PRINTF("RNIC %dADS                         %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlSendPktNum);
    PS_PRINTF("RNIC %dADS                     %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlSendPktFailNum);
    PS_PRINTF("RNIC %dIPV4              %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlIpv4BrdcstPktNum);
    PS_PRINTF("RNIC %dIMM_ZC                      %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlImmzcFailPktNum);
    PS_PRINTF("RNIC %dMAC                         %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlRmvMacHdrFailPktNum);
    PS_PRINTF("RNIC %d            %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlNetCardDiscardNum);
    PS_PRINTF("RNIC %dID                  %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlNetIdDiscardNum);
    PS_PRINTF("RNIC %dModem ID                %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlModemIdDiscardNum);
    PS_PRINTF("RNIC %d                        %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlFlowCtrlDiscardNum);
    PS_PRINTF("RNIC %dipv4ipv6                %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlRecvErrPktNum);
    PS_PRINTF("RNIC %dAPP                             %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlSendAppDialUpSucc);
    PS_PRINTF("RNIC %dAPP                             %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlSendAppDialUpFail);
    PS_PRINTF("RNIC %dAPP                             %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlSendAppDialDownSucc);
    PS_PRINTF("RNIC %dAPP                             %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlSendAppDialDownFail);

    if (RNIC_RMNET_ID_0 == ucRmNetId)
    {
        PS_PRINTF("                                           %d\n", g_stRnicCtx.stDialMode.enDialMode);
        PS_PRINTF("                               %d\n", g_stRnicCtx.stDialMode.enEventReportFlag);
        PS_PRINTF("                                   %d\n", g_stRnicCtx.stDialMode.ulIdleTime);
    }

    PS_PRINTF("RNIC %d RAB IDRNIC                %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlRabIdErr);
    PS_PRINTF("RNIC %d PDN IDRNIC                %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlPdnIdErr);

    PS_PRINTF("\r\n");

    return;
}

/*****************************************************************************
     : RNIC_ShowDLProcStats
   : RNIC
   : ucRmNetId : ID
   : 
     :

   :
   :

   :
    1.       : 20120112
             : S62952
         : 
    2.       : 20121123
             : f00179208
         : DSDA Phase I: RNIC
*****************************************************************************/
VOS_VOID RNIC_ShowDLProcStats(VOS_UINT8 ucRmNetId)
{
    if (ucRmNetId >= RNIC_NET_ID_MAX_NUM)
    {
        PS_PRINTF("RNIC_ShowDLProcStats: NetId overtop, ucRmNetId = %d\n", ucRmNetId);
        return;
    }

    /*  */
    PS_PRINTF("RNIC %dIPV4                      %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulDlRecvIpv4PktNum);
    PS_PRINTF("RNIC %dIPV6                      %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulDlRecvIpv6PktNum);
    PS_PRINTF("RNIC %dGRO               %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulDlGroIfRecvPktNum);
    PS_PRINTF("RNIC %d                          %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulDlSendPktNum);
    PS_PRINTF("RNIC %d                      %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulDlSendPktFailNum);
    PS_PRINTF("RNIC %dMTU                 %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulDlRecvBigPktNum);
    PS_PRINTF("RNIC %d                    %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulDlDiscardPktNum);
    PS_PRINTF("RNIC %dMAC                       %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulDlAddMacHdFailNum);
    PS_PRINTF("RNIC %d        %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulDlNetCardDiscardNum);
    PS_PRINTF("RNIC %dID              %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulDlNetIdDiscardNum);
    PS_PRINTF("RNIC %dipv4ipv6            %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulDlRecvErrPktNum);
    PS_PRINTF("\r\n");

    return;
}

/*****************************************************************************
     : RNIC_ShowResetStats
   : RNIC
   : 
   : 
     :

   :
   :

   :
    1.       : 20130415
             : f00179208
         : 
*****************************************************************************/
VOS_VOID RNIC_ShowResetStats(VOS_VOID)
{
    PS_PRINTF("                              %d\n", g_astRnicStats[0].ulSemInitFlg);
    PS_PRINTF("                          %p\n", g_stRnicCtx.hResetSem);
    PS_PRINTF("                          %p\n", g_astRnicStats[0].hBinarySemId);
    PS_PRINTF("                    %d\n", g_astRnicStats[0].ulCreateBinarySemFailNum);
    PS_PRINTF("                      %d\n", g_astRnicStats[0].ulLockBinarySemFailNum);
    PS_PRINTF("              %x\n", g_astRnicStats[0].ulLastBinarySemErrRslt);
    PS_PRINTF("                              %d\n", g_astRnicStats[0].ulResetSucessNum);
}

/* Added by m00217266 for L-C, 2014-2-19, begin */
/*****************************************************************************
     : RNIC_Rmnet_Config_Check_Info
   : 
   : VOID
   : 
     : VOID
   :
   :

       :
  1.       : 2014219
           : m00217266
       : 

*****************************************************************************/
VOS_VOID RNIC_ShowRmnetConfigCheckInfo(VOS_VOID)
{
    PS_PRINTF("Totla req                           %d\n", g_stRnicRmnetConfigCheckInfo.ucTotlaCnt);
    PS_PRINTF("Modem type err                      %d\n", g_stRnicRmnetConfigCheckInfo.ucModemTypeErrCnt);
    PS_PRINTF("Rmnet id err                        %d\n", g_stRnicRmnetConfigCheckInfo.ucRmNetIdErrCnt);
    PS_PRINTF("Modem ID err                        %d\n", g_stRnicRmnetConfigCheckInfo.ucModemIdErrCnt);
    PS_PRINTF("Pdn ID err                          %d\n", g_stRnicRmnetConfigCheckInfo.ucPdnIdErrCnt);
    PS_PRINTF("Rab ID err                          %d\n", g_stRnicRmnetConfigCheckInfo.ucRabIdErrCnt);
    PS_PRINTF("Rmnet status err                    %d\n", g_stRnicRmnetConfigCheckInfo.ucRmnetStatusErrCnt);
    PS_PRINTF("IP type err                         %d\n", g_stRnicRmnetConfigCheckInfo.ucIpTypeErrCnt);
    PS_PRINTF("Send err                            %d\n", g_stRnicRmnetConfigCheckInfo.ucSendErrCnt);
    PS_PRINTF("Success                             %d\n", g_stRnicRmnetConfigCheckInfo.ucSuccCnt);
}
/* Added by m00217266 for L-C, 2014-2-19, end */

/*****************************************************************************
     : RNIC_Help
   : RNIC
   :
   : 
     :

   :
   :

   :
    1.       : 20120112
             : S62952
         : 
    2.       : 20121123
             : f00179208
         : DSDA Phase I: RNIC
*****************************************************************************/
VOS_VOID RNIC_Help(VOS_VOID)
{

    PS_PRINTF("********************RNIC************************\n");
    PS_PRINTF("RNIC_ShowULProcStats  ucRmNetId                 RNIC\n");
    PS_PRINTF("RNIC_ShowDLProcStats  ucRmNetId                 RNIC\n");
    PS_PRINTF("RNIC_ShowRnicPdpStats ucRmNetId                 RNICPDP\n");
    PS_PRINTF("RNIC_ShowResetStats                             RNIC\n");

    return;
}

/*****************************************************************************
     : RNIC_ShowDataFromIpStack
   : IP
   : pstSkb   :SKBUF
   : 
     : 
   :
   :

       :
 1.       : 20130425
          : 
      : 
*****************************************************************************/
VOS_VOID RNIC_ShowDataFromIpStack(
    struct sk_buff                     *pstSkb
)
{
    VOS_UINT32                          i;

    PS_PRINTF("RNIC_ShowDataFromIpStack: data len is %d. \r\n", pstSkb->len);

    PS_PRINTF("RNIC_ShowDataFromIpStack: data content is: \r\n");

    for (i = 0; i < pstSkb->len; i++)
    {
        if (pstSkb->data[i] > 0xf)
        {
            PS_PRINTF("%x", pstSkb->data[i]);
        }
        else
        {
            PS_PRINTF("0%x", pstSkb->data[i]);
        }
    }

    PS_PRINTF("\r\n");

    return;
}




