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

#ifndef __MDRV_IPC_ENUM_H__
#define __MDRV_IPC_ENUM_H__
#ifdef __cplusplus
extern "C"
{
#endif

/* */
typedef enum tagIPC_INT_CORE_E
{
    IPC_CORE_APPARM = 0x0,
    IPC_CORE_COMARM,
    IPC_CORE_ACORE = 0x0,   /*P531,V7R2*/
    IPC_CORE_CCORE,
    IPC_CORE_MCORE,
    IPC_CORE_LDSP,
    IPC_CORE_HiFi,
    IPC_CORE_BBE,           /* xdsp core id */
    IPC_CORE_NXDSP,
    IPC_CORE0_A15,
    IPC_CORE1_A15,
    /* !!!!  */
    IPC_CORE_BUTTOM
}IPC_INT_CORE_E;

/*********************************************************
*  IPC:
*  IPC_<>_INT_SRC_<>_</>
*  :ACPUCCPUMCUHIFIBBE16
*    :ACPUCCPUMCUHIFIBBE16
*  / :
*********************************************************/
typedef enum tagIPC_INT_LEV_E
{
    IPC_CCPU_INT_SRC_HIFI_MSG              = 0, /* HIFI */
    IPC_CCPU_INT_SRC_MCU_MSG               = 1, /* MCU */
    IPC_INT_DSP_HALT                       = 2, /* DSPARM*/
    IPC_INT_DSP_RESUME                     = 3, /* DSPARM*/
                                                /* 4, ,IPC_INT_DICC_USRDATA*/
                                                /* 5, ,IPC_INT_DICC_USRDATA*/
    /* TDSIPC,begin */
    IPC_INT_WAKE_SLAVE                     = 6, /* BBE16CCPU,GSM */
    IPC_CCPU_INT_SRC_DSP_DVS,                  /* BBE16CCPUBBPdsp */
    IPC_INT_DSP_PS_PUB_MBX                 ,/* DSP->ARM,IPC */
    IPC_INT_DSP_PS_MAC_MBX                 ,/* DSP->ARM,IPC */
    IPC_INT_DSP_MBX_RSD                    ,/* DSP->ARM,IPC */
    IPC_CCPU_INT_SRC_DSP_MNTN              ,/* BBE16mailbox */
    /* TDSIPC,end */
    IPC_CCPU_INT_SDR_CCPU_BBP_MASTER_ERROR ,   /* BBE16C */
    IPC_CCPU_INT_SRC_LDSP_OM_MBX,               /* DSP->ARM,  */
    IPC_CCPU_INT_TLMODEM1_WAKE_SLAVE,           /* BBE16CCPU,GUTX */
    IPC_CCPU_INT_TLMODEM1_MAC_MBX,              /* BBE16CCPU,  */
    IPC_CCPU_INT_SRC_ACPU_RESET            ,   /* A/CC(C), v8r2 */
    IPC_CCPU_SRC_ACPU_DUMP                 ,   /* v7r2 ACPU CCPU IPC */
    IPC_CCPU_INT_SRC_ICC_PRIVATE           ,   /* v7r2 ICCicc,ACPUCCPUIPC       */
    IPC_CCPU_INT_SRC_MCPU                  ,   /* ICC, MCUCCPU  IPC */
    IPC_CCPU_INT_SRC_MCPU_WDT              ,   /* tracewdt */
    IPC_CCPU_INT_SRC_XDSP_1X_HALT          ,   /* 1X Halt */
    IPC_CCPU_INT_SRC_XDSP_HRPD_HALT        ,   /* HRPD Halt */
    IPC_CCPU_INT_SRC_XDSP_1X_RESUME        ,   /* 1X Resume */
    IPC_CCPU_INT_SRC_XDSP_HRPD_RESUME      ,   /* HRPD Resume */
    IPC_CCPU_INT_SRC_XDSP_MNTN             ,   /* XDSP */
    IPC_CCPU_INT_SRC_XDSP_PS_MBX           ,   /* PSX */
    IPC_CCPU_INT_SRC_XDSP_DVS              ,   /* CBBE16CCPUdsp */
    
    IPC_CCPU_INT_SRC_ACPU_IPC_EXTEND = 30, /* acpuccpu,IPC */
    /*  austin mcu  icc ,  */
    IPC_CCPU_INT_SRC_ACPU_ICC              = 31, /* acpuccpu*/

    /*  ICC,  */
    IPC_CCPU_INT_SRC_SECOS_ICC_IFC         = 32, /* IPC0ICC */
    IPC_CCPU_INT_SRC_SECOS_ICC_VSIM        = 33, /* IPC1ICC */

    IPC_INNER_INT_TEST        = 70, 

    /* MCU IPCbit */
    IPC_MCU_INT_SRC_ACPU_MSG             = 0,    /* ACPU */
    IPC_MCU_INT_SRC_CCPU_MSG                ,    /* CCPU */
    IPC_MCU_INT_SRC_HIFI_MSG                ,    /* HIFI */
    IPC_MCU_INT_SRC_CCPU_IPF                ,    /* IPF */
    IPC_MCU_INT_SRC_ACPU_PD                 ,    /* acpu power down */
    IPC_MCU_INT_SRC_HIFI_PD                 ,    /* hifi power down */
    IPC_MCU_INT_SRC_HIFI_DDR_VOTE           ,    /* HIFI DDR */
    IPC_MCU_INT_SRC_ACPU_I2S_REMOTE_SLOW    ,
    IPC_MCU_INT_SRC_ACPU_I2S_REMOTE_SLEEP   ,
    IPC_MCU_INT_SRC_ACPU_I2S_REMOTE_INVALID ,
    /* ACPUCCPUIPCM3 */
    IPC_MCU_INT_SRC_ACPU_DRX                ,
    IPC_MCU_INT_SRC_CCPU_DRX                ,   /* CCPUACPUIPCM3 */
    IPC_MCU_INT_SRC_ICC_PRIVATE             ,   /* m3 iccipc */
    IPC_MCU_INT_SRC_DUMP                    ,   /* m3 dumpACOREMCUIPC*/
    IPC_MCU_INT_SRC_HIFI_PU                 ,   /* POWERUP,  HIFIMCUIPC */
    IPC_MCU_INT_SRC_HIFI_DDR_DFS_QOS        , /* HIFIDDR */
    IPC_MCU_INT_SRC_TEST                    ,   /* for test a\c interact with m3 */
    IPC_MCPU_INT_SRC_ACPU_USB_PME_EN        ,  /* acoreM3USB */
    /* 3austinAP */
    IPC_MCU_INT_SRC_ICC                 = 29,   /* m3 iccipc */
    IPC_MCU_INT_SRC_CCPU_PD             = 30,    /* ccpu power down */
    IPC_MCU_INT_SRC_CCPU_START          = 31,   /* MCUCCPU */

    /* ACPU IPCbit */
    IPC_ACPU_INT_SRC_CCPU_MSG             = 0,   /* CCPU */
    IPC_ACPU_INT_SRC_HIFI_MSG             = 1,   /* HIFI */
    IPC_ACPU_INT_SRC_MCU_MSG              = 2,   /* ACPU */
    IPC_ACPU_INT_SRC_CCPU_NVIM            = 3,   /* NVIMCA*/
    IPC_INT_DICC_USRDATA                  = 4,   /* CCPU*/
    IPC_INT_DICC_RELDATA                  = 5,   /* CCPU*/
    IPC_ACPU_INT_SRC_CCPU_ICC             ,
    IPC_ACPU_INT_SRC_ICC_PRIVATE          ,   /* v7r2 icc CCPUACPUIPC */
    IPC_ACPU_SRC_CCPU_DUMP                ,   /* v7r2 CCPU ACPU IPC */
    IPC_ACPU_INT_SRC_MCPU                 ,   /* ICC, MCUACPU IPC */
    IPC_ACPU_INT_SRC_MCPU_WDT             ,  /* tracewdt */
    IPC_ACPU_INT_MCU_SRC_DUMP             ,  /* dump?MCUACPUIPC */
    IPC_ACPU_INT_SRC_CCPU_RESET_IDLE      ,  /* A/CC(master in idle) */
    IPC_ACPU_INT_SRC_CCPU_RESET_SUCC      ,  /* A/CC(ccore reset ok) */
    IPC_ACPU_INT_SRC_CCPU_LOG             ,  /* CCPUACPULOG */
    IPC_ACPU_INT_SRC_MCU_FOR_TEST         ,  /* test, m core to acore */
    IPC_ACPU_INT_SRC_CCPU_TEST_ENABLE     ,  /* IPCIPC */
    IPC_ACPU_INT_SRC_MCPU_USB_PME         ,  /* M3acoreUSB */
    IPC_ACPU_INT_SRC_HIFI_PC_VOICE_RX_DATA,  /* hifi->acore pc voice */
    IPC_ACPU_INT_SRC_CCPU_PM_OM           ,  /* CCPUACPUPMOM,,  */
    IPC_ACPU_INT_SRC_CCPU_IPC_EXTEND =20,
    IPC_ACPU_INT_SRC_END,

    /* HIFI IPCbit */
    IPC_HIFI_INT_SRC_ACPU_MSG = 0 ,  /* ACPU */
    IPC_HIFI_INT_SRC_CCPU_MSG     ,  /* CCPU */
    IPC_HIFI_INT_SRC_BBE_MSG      ,  /* TDDSP */
    IPC_HIFI_INT_SRC_MCU_MSG      ,
    IPC_HIFI_INT_SRC_END          ,

    /* BBE16 IPCbit */
    IPC_INT_MSP_DSP_OM_MBX = 0 ,   /* ARM->DSP */
    IPC_INT_PS_DSP_PUB_MBX     ,   /* ARM->DSP */
    IPC_INT_PS_DSP_MAC_MBX     ,   /* ARM->DSP */
    IPC_INT_HIFI_DSP_MBX       ,   /* HIFI->DSP */
    IPC_BBE16_INT_SRC_HIFI_MSG ,   /* HIFIBBE16IPC */
    IPC_BBE16_INT_SRC_END  ,


    /* XDSP IPCbit */
    IPC_XDSP_INT_SRC_CCPU_1X_WAKE =  IPC_BBE16_INT_SRC_END ,   /* 1X Wake */
    IPC_XDSP_INT_SRC_CCPU_HRPD_WAKE   ,   /* HRPD Wake */
    IPC_XDSP_INT_SRC_CCPU_OM_MBX      ,   /* C->XDSP */
    IPC_XDSP_INT_SRC_CCPU_PUB_MBX     ,   /* C->XDSP */
    IPC_XDSP_INT_SRC_END ,   


    /*  */
    IPC_INT_BUTTOM             = 96,
}IPC_INT_LEV_E;

typedef enum tagIPC_SEM_ID_E
{
    IPC_SEM_MEM          ,
    IPC_SEM_DICC         ,
    IPC_SEM_SYNC         , 
    IPC_SEM_SYSCTRL      ,
    IPC_SEM_BBP          ,  /*BBE16BBE16*/
    IPC_SEM_LBBP1        ,  /*bbpccore  tlphy  */
    IPC_SEM_NVIM         ,
    IPC_SEM_1X_MODE      ,  /* 1XGSDR */
    IPC_SEM_DPDT_CTRL_ANT,  /* mdrv_ipc_spin_trylock */
    IPC_SEM_BBPMASTER_0  ,
    IPC_SEM_BBPMASTER_1  ,
    IPC_SEM_BBPMASTER_2  ,
    IPC_SEM_BBPMASTER_3  ,
    IPC_SEM_BBPMASTER_5  ,
    IPC_SEM_BBPMASTER_6  ,
    IPC_SEM_BBPMASTER_7  ,
    IPC_SEM_NV           ,
    IPC_SEM_GPIO         ,
    IPC_SEM_PMU          ,
    IPC_SEM_IPF_PWCTRL   ,
    IPC_SEM_NV_CRC       ,
    IPC_SEM_PM_OM_LOG    ,
    IPC_SEM_MDRV_LOCK    ,
    IPC_SEM_CDMA_DRX     , /* CXDSP */
    IPC_SEM_GU_SLEEP     ,
    IPC_SEM2_IPC_TEST    , /*IPC*/
    IPC_SEM_DFS_FIX      = 31, /*M3 DFSHIFIAPB,HI6950*/

    IPC_SEM_INNER_TEST = 70,
    IPC_SEM_BUTTOM       = 96
} IPC_SEM_ID_E;
 
#ifdef __cplusplus
}
#endif

#endif
