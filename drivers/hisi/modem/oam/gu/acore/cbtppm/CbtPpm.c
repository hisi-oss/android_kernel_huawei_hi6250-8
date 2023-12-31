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

                   (C), 2001-2011, 

 ******************************************************************************
       : CbtPpm.c
       : 
         :
     :
     :
     : CBT
     :
     :
  1.       : 2014531
           : L00256032
       : V8R1 OM_Optimize

***************************************************************************** */

/*****************************************************************************
  1 
**************************************************************************** */
#include "AtAppVcomInterface.h"
#include "CbtPpm.h"
#include "CbtCpm.h"
#include "pamappom.h"
#include "omprivate.h"
#include "cbtapprl.h"
#include "PamOamSpecTaskDef.h"


#define    THIS_FILE_ID        PS_FILE_ID_CBT_PPM_C

/* ****************************************************************************
  2 
**************************************************************************** */
VOS_SEM                            g_ulCbtUsbPseudoSyncSemId;   /*  */

CBT_ACPU_VCOM_DEBUG_INFO           g_stCbtVComAcpuDebugInfo;

/* ACPUCBTUDI */
UDI_HANDLE                         g_ulCbtPortUDIHandle    = VOS_ERROR;

/*****************************************************************************
  3 
*****************************************************************************/
extern  CBTCPM_RCV_FUNC                 g_pCbtRcvFunc;
extern  CBTCPM_SEND_FUNC                g_pCbtSndFunc;

extern VOS_UINT32 CBTSCM_SoftDecodeDataRcv(VOS_UINT8 *pucBuffer, VOS_UINT32 ulLen);

/*****************************************************************************
  4 
*****************************************************************************/

/*****************************************************************************
     : CBTPPM_OamCbtPortDataSnd
   : CBT
   : pucVirAddr:   
             pucPhyAddr:   
             ulDataLen:    
   : 
     : VOS_ERR/VOS_OK
   :
   1.      : 2014526
           : h59254
       : Creat Function
*****************************************************************************/
VOS_UINT32 CBTPPM_OamCbtPortDataSnd(VOS_UINT8 *pucVirAddr, VOS_UINT8 *pucPhyAddr, VOS_UINT32 ulDataLen)
{
    CBTCPM_SEND_FUNC                    pFunc;

    pFunc = CBTCPM_GetSndFunc();

    if (VOS_NULL_PTR == pFunc)
    {
        return VOS_ERR;
    }

    return pFunc(pucVirAddr, pucPhyAddr, ulDataLen);
}

/*****************************************************************************
     : CBTPPM_OamUsbCbtSendData
   : USB(APP)PC
   : pucVirAddr:   
             pucPhyAddr:   
             ulDataLen:    
   : 
     : VOS_ERR/VOS_OK
   :
   :
   :
   1.      : 2011108
           : g47350
       : Creat Function
*****************************************************************************/
VOS_UINT32 CBTPPM_OamUsbCbtSendData(VOS_UINT8 *pucVirAddr, VOS_UINT8 *pucPhyAddr, VOS_UINT32 ulDataLen)
{
    VOS_INT32                           lRet;
    ACM_WR_ASYNC_INFO                   stVcom;
    /*VOS_UINT32                          ulInSlice;
    VOS_UINT32                          ulOutSlice;
    VOS_UINT32                          ulWriteSlice;*/

    if ((VOS_NULL_PTR == pucVirAddr) || (VOS_NULL_PTR == pucPhyAddr))
    {
        /*  */
        LogPrint("\r\n CBTPPM_OamUsbCbtSendData: Vir or Phy Addr is Null \n");

        return CBTCPM_SEND_PARA_ERR;
    }

    stVcom.pVirAddr = (VOS_CHAR*)pucVirAddr;
    stVcom.pPhyAddr = (VOS_CHAR*)pucPhyAddr;
    stVcom.u32Size  = ulDataLen;
    stVcom.pDrvPriv = VOS_NULL_PTR;

    /*g_stAcpuDebugInfo.astPortInfo[OM_USB_CBT_PORT_HANDLE].ulUSBWriteNum1++;

    ulInSlice = OM_GetSlice();*/

    lRet = mdrv_udi_ioctl(g_ulCbtPortUDIHandle, ACM_IOCTL_WRITE_ASYNC, &stVcom);

    /*g_stAcpuDebugInfo.astPortInfo[OM_USB_CBT_PORT_HANDLE].ulUSBWriteNum2++;

    ulOutSlice = OM_GetSlice();

    if(ulInSlice > ulOutSlice)
    {
        ulWriteSlice = ulInSlice - ulOutSlice;
    }
    else
    {
        ulWriteSlice = ulOutSlice - ulInSlice;
    }*/

    /*if(ulWriteSlice > g_stAcpuDebugInfo.astPortInfo[OM_USB_CBT_PORT_HANDLE].ulUSBWriteMaxTime)
    {
        g_stAcpuDebugInfo.astPortInfo[OM_USB_CBT_PORT_HANDLE].ulUSBWriteMaxTime = ulWriteSlice;
    }*/


    if (MDRV_OK == lRet)     /**/
    {
        if (VOS_OK != VOS_SmP(g_ulCbtUsbPseudoSyncSemId, 0))
        {
            LogPrint1("\r\n CBTPPM_OamUsbCbtSendData: mdrv_udi_ioctl Send Data return Error %d\n", lRet);
            return VOS_ERR;
        }

        return VOS_OK;
    }
    else if (MDRV_OK > lRet)    /**/
    {
        /*UDI*/
        LogPrint1("\r\n CBTPPM_OamUsbCbtSendData: mdrv_udi_ioctl Send Data return Error %d\n", lRet);


        /*        g_stAcpuDebugInfo.astPortInfo[OM_USB_CBT_PORT_HANDLE].ulUSBWriteErrNum++;
        g_stAcpuDebugInfo.astPortInfo[OM_USB_CBT_PORT_HANDLE].ulUSBWriteErrLen    += ulDataLen;
        g_stAcpuDebugInfo.astPortInfo[OM_USB_CBT_PORT_HANDLE].ulUSBWriteErrValue  = (VOS_UINT32)lRet;
        g_stAcpuDebugInfo.astPortInfo[OM_USB_CBT_PORT_HANDLE].ulUSBWriteErrTime   = OM_GetSlice();*/

        return VOS_ERR; /*NULL*/
    }
    else    /**/
    {
        /*UDI*/
        LogPrint1("\r\n CBTPPM_OamUsbCbtSendData: mdrv_udi_ioctl Send Data return Error %d\n", lRet);

        VOS_ProtectionReboot(OAM_USB_SEND_ERROR, (VOS_INT)THIS_FILE_ID, (VOS_INT)__LINE__,
                             (VOS_CHAR *)&lRet, sizeof(VOS_INT32));

        return VOS_ERR;
    }

}

/*****************************************************************************
     : CBTPPM_OamUsbCbtPortClose
   : USB
   : 
   : 
     : 
   :
   1.      : 2014524
           : h59254
       : Creat Function
*****************************************************************************/
VOS_VOID CBTPPM_OamUsbCbtPortClose(VOS_VOID)
{
    if (VOS_ERROR == g_ulCbtPortUDIHandle)
    {
        return;
    }

    (VOS_VOID)mdrv_udi_close(g_ulCbtPortUDIHandle);

    g_ulCbtPortUDIHandle = VOS_ERROR;

    /* CBTUSBVCOMUARTUSB */
    if (VOS_NULL_PTR == CBTCPM_GetRcvFunc())
    {
        return;
    }

    (VOS_VOID)PPM_DisconnectGUPort(OM_LOGIC_CHANNEL_CBT);

    return;
}

/*****************************************************************************
     : CBTPPM_OamUsbCbtWriteDataCB
   : USBCBT
   : pucData:   
             ulDataLen: 
   : 
     : 
   :
   1.      : 2014524
           : h59254
       : V8R1 OM_Optimize
*****************************************************************************/
VOS_VOID CBTPPM_OamUsbCbtWriteDataCB(VOS_UINT8* pucVirData, VOS_UINT8* pucPhyData, VOS_INT lLen)
{
    if (lLen < 0)
    {
        LogPrint("\r\n CBTPPM_OamUsbCbtWriteDataCB: lLen < 0. \n");
    }

    /*  */
    (VOS_VOID)VOS_SmV(g_ulCbtUsbPseudoSyncSemId);

    return;
}

/*****************************************************************************
     : CBTPPM_OamUsbCbtStatusCB
   : ACPUUSB
   : enPortState:   
   : 
     : 
   :
   1.      : 2014524
           : h59254
       : Creat Function
*****************************************************************************/
VOS_VOID CBTPPM_OamUsbCbtStatusCB(ACM_EVT_E enPortState)
{
    /* CBTUSBVCOMUARTUSB */
    if (VOS_NULL_PTR == CBTCPM_GetRcvFunc())
    {
        return;
    }

    /* CBTGU */
    (VOS_VOID)PPM_DisconnectGUPort(OM_LOGIC_CHANNEL_CBT);

    return;
}

/*****************************************************************************
     : CBTPPM_OamUsbCbtPortOpen
   : USBCBT
   : 
   : 
     : 
   :
   1.      : 2014524
           : h59254
       : Creat Function
*****************************************************************************/
VOS_VOID CBTPPM_OamUsbCbtPortOpen(VOS_VOID)
{
    CBTPPM_OamCbtPortDataInit(OM_USB_CBT_PORT_HANDLE,
                              CBTPPM_OamUsbCbtReadDataCB,
                              CBTPPM_OamUsbCbtWriteDataCB,
                              CBTPPM_OamUsbCbtStatusCB);

    return;
}

/*****************************************************************************
     : CBTPPM_OamUsbCbtReadDataCB
   : ACPUUSBCBTICCOM
   : 
   : 
     : VOS_ERR/VOS_OK
   :
   1.      : 2014524
           : h59254
       : Creat Function
*****************************************************************************/
VOS_INT32 CBTPPM_OamUsbCbtReadDataCB(VOS_VOID)
{
    ACM_WR_ASYNC_INFO                   stInfo  = {0};
    CBTCPM_RCV_FUNC                     pFunc;

    if (VOS_ERROR == g_ulCbtPortUDIHandle)
    {
        LogPrint("\r\n CBTPPM_OamUsbCbtReadDataCB: Input HANDLE  is err. \n");

        return VOS_ERR;
    }

    PAM_MEM_SET_S(&stInfo, sizeof(stInfo), 0, sizeof(stInfo));

    /* USBIO CTRL */
    if (VOS_OK != mdrv_udi_ioctl(g_ulCbtPortUDIHandle, UDI_ACM_IOCTL_GET_READ_BUFFER_CB, &stInfo))
    {
        LogPrint("\r\n CBTPPM_OamUsbCbtReadDataCB:Call mdrv_udi_ioctl is Failed\n");

        return VOS_ERR;
    }

    /*lint -e40*/
    CBT_ACPU_DEBUG_TRACE((VOS_UINT8*)stInfo.pVirAddr, stInfo.u32Size, CBT_ACPU_USB_CB);
    /*lint +e40*/

    /*  */
    pFunc = CBTCPM_GetRcvFunc();

    if (VOS_NULL_PTR != pFunc)
    {
        if (VOS_OK != pFunc((VOS_UINT8 *)stInfo.pVirAddr, stInfo.u32Size))
        {
            /*  */
        }
    }

    if(VOS_OK != mdrv_udi_ioctl(g_ulCbtPortUDIHandle, UDI_ACM_IOCTL_RETUR_BUFFER_CB, &stInfo))
    {
        LogPrint("\r\n CBTPPM_OamUsbCbtReadDataCB:Call mdrv_udi_ioctl UDI_ACM_IOCTL_RETUR_BUFFER_CB is Failed\n");

        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
     : CBTPPM_OamCbtPortDataInit
   : CBT
   : enHandle: 
             pReadCB: 
             pWriteCB: 
             pStateCB: 
   : 
     : VOS_OK/VOS_ERR
   :
   1.      : 2014524
           : h59254
       : Creat Function
*****************************************************************************/
VOS_VOID CBTPPM_OamCbtPortDataInit(OM_PROT_HANDLE_ENUM_UINT32          enHandle,
                                        VOS_VOID                            *pReadCB,
                                        VOS_VOID                            *pWriteCB,
                                        VOS_VOID                            *pStateCB)
{
    UDI_OPEN_PARAM_S                    stUdiPara;
    ACM_READ_BUFF_INFO                  stReadBuffInfo;


    stUdiPara.devid            = UDI_ACM_OM_ID;

    stReadBuffInfo.u32BuffSize = OM_ICC_BUFFER_SIZE;
    stReadBuffInfo.u32BuffNum  = OM_DRV_MAX_IO_COUNT;

    /*g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBOpenNum++;
    g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBOpenSlice = OM_GetSlice();*/


    if (VOS_ERROR != g_ulCbtPortUDIHandle)
    {
        LogPrint("\r\n CBTPPM_OamCbtPortDataInit: The UDI Handle is not Null !");

        return;
    }

    /* CBTUSB */
    g_ulCbtPortUDIHandle = mdrv_udi_open(&stUdiPara);

    if (VOS_ERROR == g_ulCbtPortUDIHandle)
    {
        LogPrint("\r\n CBTPPM_OamCbtPortDataInit: Open UDI ACM failed!");

        return;
    }


    /*g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBOpenOkNum++;
    g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBOpenOkSlice = OM_GetSlice();*/

    /* CBTUSB */
    if (VOS_OK != mdrv_udi_ioctl(g_ulCbtPortUDIHandle, ACM_IOCTL_RELLOC_READ_BUFF, &stReadBuffInfo))
    {
        LogPrint("\r\n CBTPPM_OamCbtPortDataInit, mdrv_udi_ioctl ACM_IOCTL_RELLOC_READ_BUFF Failed\r\n");

        return;
    }

    /* OMUSB */
    if (VOS_OK != mdrv_udi_ioctl(g_ulCbtPortUDIHandle, UDI_ACM_IOCTL_SET_READ_CB, pReadCB))
    {
        LogPrint("\r\n CBTPPM_OamCbtPortDataInit, mdrv_udi_ioctl UDI_ACM_IOCTL_SET_READ_CB Failed\r\n");

        return;
    }

    if(VOS_OK != mdrv_udi_ioctl(g_ulCbtPortUDIHandle, ACM_IOCTL_SET_WRITE_CB, pWriteCB))
    {
        LogPrint("\r\n CBTPPM_OamCbtPortDataInit, mdrv_udi_ioctl ACM_IOCTL_SET_WRITE_CB Failed\r\n");

        return;
    }

    if(VOS_OK != mdrv_udi_ioctl(g_ulCbtPortUDIHandle, ACM_IOCTL_SET_EVT_CB, pStateCB))
    {
        LogPrint("\r\n CBTPPM_OamCbtPortDataInit, mdrv_udi_ioctl ACM_IOCTL_SET_EVT_CB Failed\r\n");

        return;
    }

    if (VOS_OK != mdrv_udi_ioctl(g_ulCbtPortUDIHandle, ACM_IOCTL_WRITE_DO_COPY, VOS_NULL_PTR))
    {
        LogPrint("\r\n CBTPPM_OamCbtPortDataInit, mdrv_udi_ioctl ACM_IOCTL_WRITE_DO_COPY Failed\r\n");

        return;
    }


    /*g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBOpenOk2Num++;
    g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBOpenOk2Slice = OM_GetSlice();*/

    return;
}

/*****************************************************************************
     : GU_OamUsbCbtPortInit
   : USB CBT
   : 
   : 
     : VOS_OK/VOS_ERR
   :
   1.      : 2014525
           : h59254
       : Creat Function
*****************************************************************************/
VOS_UINT32 CBTPPM_OamUsbCbtPortInit(VOS_VOID)
{
    /* CBTPCVOICE */
    CBTCPM_PortRcvReg(CBTSCM_SoftDecodeDataRcv);

    /*  */
    CBTCPM_PortSndReg(CBTPPM_OamUsbCbtSendData);

    /* USBCBT */
    if(VOS_OK != VOS_SmCCreate("UCBT", 0, VOS_SEMA4_FIFO, &g_ulCbtUsbPseudoSyncSemId))
    {
        LogPrint("\r\n CBTPPM_OamUsbCbtPortInit: create g_ulCbtUsbPseudoSyncSemId failedd\r\n");

        return VOS_ERR;
    }

    /* USBCBTUDI */
    g_ulCbtPortUDIHandle = VOS_ERROR;

    /* CBTCBTCPM */
    (VOS_VOID)mdrv_usb_reg_enablecb((USB_UDI_ENABLE_CB_T)CBTPPM_OamUsbCbtPortOpen);

    (VOS_VOID)mdrv_usb_reg_disablecb((USB_UDI_DISABLE_CB_T)CBTPPM_OamUsbCbtPortClose);

    return VOS_OK;
}

/*****************************************************************************
     : CBTPPM_OamVComCbtReadData
   : VCOMCBT
   :  ucDevIndex: 
              pData    : 
              ullength : 

   : 
     : VOS_ERR/VOS_OK
   :
   1.      : 2014526
           : h59254
       : Creat Function
*****************************************************************************/
VOS_INT CBTPPM_OamVComCbtReadData(VOS_UINT8 ucDevIndex, VOS_UINT8 *pData, VOS_UINT32 ullength)
{
    CBTCPM_RCV_FUNC                     pFunc;

    if (ucDevIndex != APP_VCOM_DEV_INDEX_LOG)
    {
        (VOS_VOID)vos_printf("\r\n CBTPPM_OamVComCbtReadData:PhyPort port is error: %d\n", ucDevIndex);

        return VOS_ERR;
    }

    g_stCbtVComAcpuDebugInfo.ulVCOMRcvNum++;
    g_stCbtVComAcpuDebugInfo.ulVCOMRcvLen += ullength;

    if ((VOS_NULL_PTR == pData) || (0 == ullength))
    {
        (VOS_VOID)vos_printf("\r\n CBTPPM_OamVComCbtReadData:Send data is NULL\n");

        return VOS_ERR;
    }

    /*lint -e40*/
    CBT_ACPU_DEBUG_TRACE((VOS_UINT8*)pData, ullength, CBT_ACPU_VCOM_CB);
    /*lint +e40*/

    pFunc = CBTCPM_GetRcvFunc();

    /*  */
    if (VOS_NULL_PTR == pFunc)
    {
        return VOS_ERR;
    }

    if (VOS_OK != pFunc((VOS_UINT8*)pData, ullength))
    {
        g_stCbtVComAcpuDebugInfo.ulVCOMRcvErrNum++;
        g_stCbtVComAcpuDebugInfo.ulVCOMRcvErrLen += ullength;

        (VOS_VOID)vos_printf("\r\n Info: CBTPPM_OamVComCbtReadData:Call CBT Data Rcv Func fail\n");

        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
     : CBTPPM_OamVComCbtSendData
   : VCOMCBT
   : pucVirAddr:   
             pucPhyAddr:   
             ulDataLen:    
   : 
     : CBTCPM_SEND_ERR/CBTCPM_SEND_OK
   :
   1.      : 2014526
           : h59254
       : Creat Function
*****************************************************************************/
VOS_UINT32 CBTPPM_OamVComCbtSendData(VOS_UINT8 *pucVirAddr, VOS_UINT8 *pucPhyAddr, VOS_UINT32 ulDataLen)
{
    g_stCbtVComAcpuDebugInfo.ulVCOMSendNum++;
    g_stCbtVComAcpuDebugInfo.ulVCOMSendLen += ulDataLen;

    if (VOS_OK != APP_VCOM_Send(APP_VCOM_DEV_INDEX_LOG, pucVirAddr, ulDataLen))
    {
        g_stCbtVComAcpuDebugInfo.ulVCOMSendErrNum++;
        g_stCbtVComAcpuDebugInfo.ulVCOMSendErrLen += ulDataLen;

        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
     : CBTPPM_OamVComCbtPortInit
   :  Vcom CBT
   : 
   : 
     : 
   :
   1.      : 2014524
           : h59254
       : Creat Function
*****************************************************************************/
VOS_VOID CBTPPM_OamVComCbtPortInit(VOS_VOID)
{
    /* CBTPCVOICE */
    CBTCPM_PortRcvReg(CBTSCM_SoftDecodeDataRcv);

    /* VCOM28CPM */
    (VOS_VOID)APP_VCOM_RegDataCallback(APP_VCOM_DEV_INDEX_LOG, CBTPPM_OamVComCbtReadData);

    CBTCPM_PortSndReg(CBTPPM_OamVComCbtSendData);

    return;
}

/*****************************************************************************
     : CBTPPM_OamCbtPortInit
   : CBT
   : enCbtPort:CBT
   : 
     : VOS_VOID
   :
  1.       : 2014525
           : h59254
       : V8R1 OM_Optimize
*****************************************************************************/
VOS_VOID CBTPPM_OamCbtPortInit(VOS_VOID)
{
    OM_CHANNLE_PORT_CFG_STRU            stPortCfg = {0};

    /*  */
    PAM_MEM_SET_S(&g_stCbtVComAcpuDebugInfo,
                   sizeof(g_stCbtVComAcpuDebugInfo),
                   0,
                   sizeof(g_stCbtVComAcpuDebugInfo));

    /* OM */
    if (NV_OK != NV_Read(en_NV_Item_Om_Port_Type, &stPortCfg, sizeof(OM_CHANNLE_PORT_CFG_STRU)))
    {
        stPortCfg.enCbtPortNum = CPM_CBT_PORT_VCOM;
    }

    if (CPM_CBT_PORT_USB == stPortCfg.enCbtPortNum)
    {
        /* USB CBT */
        (VOS_VOID)CBTPPM_OamUsbCbtPortInit();
    }
    else if (CPM_CBT_PORT_SOCKET == stPortCfg.enCbtPortNum)
    {
        CBTPPM_SocketPortInit();
    }
    /* VCOMCBT */
    else
    {
        /* Vcom CBT */
        CBTPPM_OamVComCbtPortInit();
    }

    return;
}


/*****************************************************************************
     : CBTPPM_SocketTaskInit
   : CBT
   : 
   : 
     : VOS_OK/VOS_ERR
   :
  1.       : 20151221
           : x51137
       :  Creat Function
*****************************************************************************/
VOS_UINT32 CBTPPM_SocketTaskInit(VOS_VOID)
{
    return VOS_OK;
}

VOS_VOID CBTPPM_SocketPortInit(VOS_VOID)
{
    return;
}






