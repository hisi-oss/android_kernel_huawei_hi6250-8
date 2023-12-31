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
**************************************************************************** */
#include "OmCommonPpm.h"
#include "OmHsicPpm.h"
#include "cpm.h"
#include "TafOamInterface.h"


#define    THIS_FILE_ID        PS_FILE_ID_OM_HSIC_PPM_C

/* ****************************************************************************
  2 
**************************************************************************** */
/* HSICOM */
OM_HSIC_PORT_STATUS_ENUM_UINT32         g_ulOmHsicConnectStatus = OM_HSIC_PORT_STATUS_OFF;

/*OM HSIC */
VOS_SEM                                 g_ulOmAcpuHsicSem;

/*****************************************************************************
  3 
*****************************************************************************/


/*****************************************************************************
  4 
*****************************************************************************/

/*****************************************************************************
     :
   :
   :
   :
     :
   :
   :

       :
  1.       : 2014531
           : XXXXXXXX
       : V8R1 OM_Optimize

*****************************************************************************/


/*****************************************************************************
     : PPM_GetHsicPortStatus
   : OMHSIC
   : 
   : 
     : 
       :
  1.       : 2014531
           : h59254
       : V8R1 OM_Optimize
*****************************************************************************/
OM_HSIC_PORT_STATUS_ENUM_UINT32 PPM_GetHsicPortStatus(VOS_VOID)
{
    /* OMHSIC */
    return g_ulOmHsicConnectStatus;
}

/*****************************************************************************
     : PPM_HsicIndWriteDataCB
   : Hsic 
   : pucData:   
             ulDataLen: 
   : 
     : 
   :
   :
   :
   1.      : 201222
           : zhuli
       : Creat Function
*****************************************************************************/
VOS_VOID PPM_HsicIndWriteDataCB(VOS_UINT8* pucVirData, VOS_UINT8* pucPhyData, VOS_INT lLen)
{
    /*OM*/
    PPM_PortWriteAsyCB(OM_HSIC_IND_PORT_HANDLE, pucVirData, lLen);

    return;
}


/*****************************************************************************
     : PPM_HsicCfgReadDataCB
   : ACPUHSIC CFGICCOM
   : 
   : 
     : VOS_ERR/VOS_OK
   :
  1.       : 2014531
           : h59254
       : V8R1 OM_Optimize
*****************************************************************************/
VOS_INT32 PPM_HsicCfgReadDataCB(VOS_VOID)
{
    if (OM_HSIC_PORT_STATUS_OFF == PPM_GetHsicPortStatus())
    {
        return VOS_OK;
    }

    return PPM_ReadPortData(CPM_HSIC_CFG_PORT, g_astOMPortUDIHandle[OM_HSIC_CFG_PORT_HANDLE], OM_HSIC_CFG_PORT_HANDLE);
}

/*****************************************************************************
     : PPM_HsicCfgWriteDataCB
   : Hsic CFG
   : pucData:   
             ulDataLen: 
   : 
     : 
   :
  1.       : 2014531
           : h59254
       : V8R1 OM_Optimize
*****************************************************************************/
VOS_VOID PPM_HsicCfgWriteDataCB(VOS_UINT8* pucVirData, VOS_UINT8* pucPhyData, VOS_INT lLen)
{
    /*OM*/
    PPM_PortWriteAsyCB(OM_HSIC_CFG_PORT_HANDLE, pucVirData, lLen);

    return;
}

/*****************************************************************************
     : PPM_HsicCfgPortOpen
   : OMHsic CFG
   : 
   : 
     : 
   :
  1.       : 2014531
           : h59254
       : V8R1 OM_Optimize
*****************************************************************************/
VOS_VOID PPM_HsicCfgPortOpen(VOS_VOID)
{

    PPM_ReadPortDataInit(CPM_HSIC_CFG_PORT,
                           OM_HSIC_CFG_PORT_HANDLE,
                           PPM_HsicCfgReadDataCB,
                           PPM_HsicCfgWriteDataCB,
                           VOS_NULL_PTR);

    return;
}

/*****************************************************************************
     : PPM_HsicIndPortOpen
   : OMHsic IND
   : 
   : 
     : 
       :
  1.       : 2014531
           : h59254
       : V8R1 OM_Optimize
*****************************************************************************/
VOS_VOID PPM_HsicIndPortOpen(VOS_VOID)
{
    /* HSIC IND  */
    PPM_ReadPortDataInit(CPM_HSIC_IND_PORT,
                           OM_HSIC_IND_PORT_HANDLE,
                           VOS_NULL_PTR,
                           PPM_HsicIndWriteDataCB,
                           VOS_NULL_PTR);

    return;
}

/*****************************************************************************
     : PPM_HsicIndPortClose
   : Hsic INDUSB
   : 
   : 
     : 
   :
   :
   :
  1.       : 2014531
           : h59254
       : V8R1 OM_Optimize
*****************************************************************************/
VOS_VOID PPM_HsicIndPortClose(VOS_VOID)
{
    PPM_PortCloseProc(OM_HSIC_IND_PORT_HANDLE, CPM_HSIC_IND_PORT);

    return;
}

/*****************************************************************************
     : PPM_HsicCfgPortClose
   : Hsic INDUSB
   : 
   : 
     : 
   :
  1.       : 2014531
           : h59254
       : V8R1 OM_Optimize
*****************************************************************************/
VOS_VOID PPM_HsicCfgPortClose(VOS_VOID)
{
    PPM_PortCloseProc(OM_HSIC_CFG_PORT_HANDLE, CPM_HSIC_CFG_PORT);

    return;
}

/*****************************************************************************
     : GU_OamHsicIndSendData
   : Hsic INDPC
   : pucVirAddr:   
             pucPhyAddr:   
             ulDataLen: 
   : 
     : VOS_ERROR/VOS_OK
   :
  1.       : 2014531
           : h59254
       : V8R1 OM_Optimize
*****************************************************************************/
VOS_UINT32 PPM_HsicIndSendData(VOS_UINT8 *pucVirAddr, VOS_UINT8 *pucPhyAddr, VOS_UINT32 ulDataLen)
{
    return PPM_PortSend(OM_HSIC_IND_PORT_HANDLE, pucVirAddr, pucPhyAddr, ulDataLen);
}

/*****************************************************************************
     : PPM_HsicCfgSendData
   : Hsic CFGPC
   : pucVirAddr:   
             pucPhyAddr:   
             ulDataLen: 
   : 
     : VOS_ERROR/VOS_OK
   :
  1.       : 2014531
           : h59254
       : V8R1 OM_Optimize
*****************************************************************************/
VOS_UINT32 PPM_HsicCfgSendData(VOS_UINT8 *pucVirAddr, VOS_UINT8 *pucPhyAddr, VOS_UINT32 ulDataLen)
{
    return PPM_PortSend(OM_HSIC_CFG_PORT_HANDLE, pucVirAddr, pucPhyAddr, ulDataLen);
}

/*****************************************************************************
     : PPM_HsicIndStatusCB
   : ACPUHSIC INDOM
   : enPortState:   
   : 
     : 
   :
  1.       : 2014531
           : h59254
       : V8R1 OM_Optimize
*****************************************************************************/
VOS_VOID PPM_HsicIndStatusCB(ACM_EVT_E enPortState)
{
    PPM_PortStatus(OM_HSIC_IND_PORT_HANDLE, CPM_HSIC_IND_PORT, enPortState);

    return;
}

/*****************************************************************************
     : PPM_HsicIndStatusCB
   : ACPUHSIC CFGOM
   : enPortState:   
   : 
     : 
   :
  1.       : 2014531
           : h59254
       : V8R1 OM_Optimize
*****************************************************************************/
VOS_VOID PPM_HsicCfgStatusCB(ACM_EVT_E enPortState)
{
    PPM_PortStatus(OM_HSIC_CFG_PORT_HANDLE, CPM_HSIC_CFG_PORT, enPortState);

    return;
}

/*****************************************************************************
     : PPM_HsicPortInit
   : HSIC
   : 
   : 
     : 
   :
  1.       : 2014531
           : h59254
       : V8R1 OM_Optimize
*****************************************************************************/
VOS_VOID PPM_HsicPortInit(VOS_VOID)
{
    /* HSIC */
    if (BSP_MODULE_SUPPORT != mdrv_misc_support_check(BSP_MODULE_TYPE_HSIC))
    {
        return;
    }

    /* HSIC
        HSIC*/
    if (VOS_TRUE == DRV_GET_HSIC_ENUM_STATUS())
    {
        PPM_HsicIndPortOpen();
        PPM_HsicCfgPortOpen();
    }
    else
    {
        DRV_HSIC_REGUDI_ENABLECB((HSIC_UDI_ENABLE_CB_T)PPM_HsicIndPortOpen);
        DRV_HSIC_REGUDI_ENABLECB((HSIC_UDI_ENABLE_CB_T)PPM_HsicCfgPortOpen);
    }

    DRV_HSIC_REGUDI_DISABLECB((HSIC_UDI_DISABLE_CB_T)PPM_HsicIndPortClose);
    DRV_HSIC_REGUDI_DISABLECB((HSIC_UDI_DISABLE_CB_T)PPM_HsicCfgPortClose);

    CPM_PhySendReg(CPM_HSIC_IND_PORT,  PPM_HsicIndSendData);
    CPM_PhySendReg(CPM_HSIC_CFG_PORT,  PPM_HsicCfgSendData);

    return;
}

/*****************************************************************************
 Prototype       : PPM_HsicConnectProc
 Description     : OMHSIC
 Input           : None
 Output          : None
 Return Value    : VOS_UINT32

 History         : ---
    Date         : 2012-04-09
    Author       : h59254
    Modification : AP-Modem
 *****************************************************************************/
VOS_VOID PPM_HsicConnectProc(VOS_VOID)
{
    if (VOS_OK != VOS_SmP(g_ulOmAcpuHsicSem, 0))
    {
        return;
    }

    /* HSIC */
    if (BSP_MODULE_SUPPORT != mdrv_misc_support_check(BSP_MODULE_TYPE_HSIC))
    {
        (VOS_VOID)VOS_SmV(g_ulOmAcpuHsicSem);

        return;
    }

    /*  */
    if (OM_HSIC_PORT_STATUS_ON == g_ulOmHsicConnectStatus)
    {
        (VOS_VOID)VOS_SmV(g_ulOmAcpuHsicSem);

        return;
    }

    /*  */
    g_ulOmHsicConnectStatus = OM_HSIC_PORT_STATUS_ON;

    (VOS_VOID)VOS_SmV(g_ulOmAcpuHsicSem);

    return;
}

/*****************************************************************************
 Prototype       : PPM_HsicDisconnectProc
 Description     : OMHSIC
 Input           : None
 Output          : None
 Return Value    : VOS_UINT32

 History         : ---
    Date         : 2012-04-09
    Author       : h59254
    Modification : AP-Modem
 *****************************************************************************/
VOS_VOID PPM_HsicDisconnectProc(VOS_VOID)
{
    /* HSIC */
    if (BSP_MODULE_SUPPORT != mdrv_misc_support_check(BSP_MODULE_TYPE_HSIC))
    {
        return;
    }

    /*  */
    if (OM_HSIC_PORT_STATUS_OFF == g_ulOmHsicConnectStatus)
    {
        return;
    }

    /*  */
    g_ulOmHsicConnectStatus = OM_HSIC_PORT_STATUS_OFF;

    return;
}





