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

#ifndef _SOCP_BALONG_H
#define _SOCP_BALONG_H

#ifdef __cplusplus
extern "C"
{
#endif

/**************************************************************************
  
**************************************************************************/
#include "bsp_memmap.h"
#include "soc_interrupts.h"
#include "product_config.h"
#include "hi_socp.h"
#include "bsp_socp.h"
#include "bsp_trace.h"
#include <linux/dma-mapping.h>
#include <linux/semaphore.h>
#include <linux/workqueue.h>
#include <linux/kernel.h>
#include <asm/io.h>
#include <linux/device.h>
#include <linux/module.h>
#include <linux/err.h>
#include <linux/io.h>
#include <linux/platform_device.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/regulator/consumer.h>
#if defined(__OS_RTOSCK__)
#include "securec.h"
#endif

/**************************************************************************
  
**************************************************************************/
//#define SOCP_VIRT_PHY(virt)          virt_to_phys((void*)virt)
//#define SOCP_PHY_VIRT(phy)           phys_to_virt((unsigned long)phy)
#define SOCP_VIRT_PHY(virt)          (virt)
#define SOCP_PHY_VIRT(phy)           (phy)

typedef int (*socp_task_entry)(void * data);

/**************************************************************************
  ,
**************************************************************************/
#define SOCP_REG_GBLRST             (HI_SOCP_GLOBAL_SRST_CTRL_OFFSET)
#define SOCP_REG_ENCRST             (HI_SOCP_ENC_SRST_CTRL_OFFSET)
#define SOCP_REG_DECRST             (HI_SOCP_DEC_SRST_CTRL_OFFSET)
#define SOCP_REG_ENCSTAT            (HI_SOCP_ENC_CH_STATUS_OFFSET)
#define SOCP_REG_DECSTAT            (HI_SOCP_DEC_CH_STATUS_OFFSET)
#define SOCP_REG_CLKCTRL            (HI_SOCP_CLK_CTRL_OFFSET)
#define SOCP_REG_PRICFG             (HI_SOCP_PRIOR_CFG_OFFSET)
#if (FEATURE_SOCP_DECODE_INT_TIMEOUT == FEATURE_ON)
#define SOCP_REG_DEC_INT_TIMEOUT    (HI_SOCP_DEC_INT_TIMEOUT_OFFSET)
#endif
#define SOCP_REG_INTTIMEOUT         (HI_SOCP_INT_TIMEOUT_OFFSET)
#define SOCP_REG_BUFTIMEOUT         (HI_SOCP_BUFFER_TIMEOUT_OFFSET)
#define SOCP_REG_DEC_PKTLEN         (HI_SOCP_DEC_PKT_LEN_CFG_OFFSET)
#define SOCP_REG_GBL_INTSTAT        (HI_SOCP_GLOBAL_INT_STATUS_OFFSET)

/*  */
#define SOCP_REG_ENC_MASK0          (HI_SOCP_ENC_CORE0_MASK0_OFFSET)
#define SOCP_REG_ENC_RAWINT0        (HI_SOCP_ENC_CORE0_RAWINT0_OFFSET)
#define SOCP_REG_ENC_INTSTAT0       (HI_SOCP_ENC_CORE0_INT0_OFFSET)
#define SOCP_REG_APP_MASK1          (HI_SOCP_ENC_CORE0_MASK1_OFFSET)
#define SOCP_REG_MODEM_MASK1        (HI_SOCP_ENC_CORE1_MASK1_OFFSET)
#define SOCP_REG_ENC_RAWINT1        (HI_SOCP_ENC_RAWINT1_OFFSET)
#define SOCP_REG_APP_INTSTAT1       (HI_SOCP_ENC_CORE0_INT1_OFFSET)
#define SOCP_REG_MODEM_INTSTAT1     (HI_SOCP_ENC_CORE1_INT1_OFFSET)
#define SOCP_REG_ENC_MASK2          (HI_SOCP_ENC_CORE0_MASK2_OFFSET)
#define SOCP_REG_ENC_RAWINT2        (HI_SOCP_ENC_CORE0_RAWINT2_OFFSET)
#define SOCP_REG_ENC_INTSTAT2       (HI_SOCP_ENC_CORE0_INT2_OFFSET)
#define SOCP_REG_APP_MASK3          (HI_SOCP_ENC_CORE0_MASK3_OFFSET)
#define SOCP_REG_MODEM_MASK3        (HI_SOCP_ENC_CORE1_MASK3_OFFSET)
#define SOCP_REG_ENC_RAWINT3        (HI_SOCP_ENC_RAWINT3_OFFSET)
#define SOCP_REG_APP_INTSTAT3       (HI_SOCP_ENC_CORE0_INT3_OFFSET)
#define SOCP_REG_MODEM_INTSTAT3     (HI_SOCP_ENC_CORE1_INT3_OFFSET)
#define SOCP_REG_ENC_CORE1_MASK0    (HI_SOCP_ENC_CORE1_MASK0_OFFSET)
#define SOCP_REG_ENC_CORE1_INT0     (HI_SOCP_ENC_CORE1_INT0_OFFSET)
#define SOCP_REG_ENC_CORE1_MASK2    (HI_SOCP_ENC_CORE1_MASK2_OFFSET)
#define SOCP_REG_ENC_CORE1_INT2     (HI_SOCP_ENC_CORE1_INT2_OFFSET)

/* */
#define SOCP_REG_DEC_CORE0MASK0     (HI_SOCP_DEC_CORE0_MASK0_OFFSET)
#define SOCP_REG_DEC_CORE1MASK0     (HI_SOCP_DEC_CORE1_MASK0_OFFSET)
#define SOCP_REG_DEC_RAWINT0        (HI_SOCP_DEC_RAWINT0_OFFSET)
#define SOCP_REG_DEC_CORE0ISTAT0    (HI_SOCP_DEC_CORE0_INT0_OFFSET)
#define SOCP_REG_DEC_CORE1ISTAT0    (HI_SOCP_DEC_CORE1_INT0_OFFSET)
#define SOCP_REG_DEC_MASK1          (HI_SOCP_DEC_CORE0_MASK1_OFFSET)
#define SOCP_REG_DEC_RAWINT1        (HI_SOCP_DEC_CORE0_RAWINT1_OFFSET)
#define SOCP_REG_DEC_INTSTAT1       (HI_SOCP_DEC_CORE0_INT1_OFFSET)
#define SOCP_REG_DEC_CORE0MASK2     (HI_SOCP_DEC_CORE0_MASK2_OFFSET)
#define SOCP_REG_DEC_CORE1MASK2     (HI_SOCP_DEC_CORE1NOTE_MASK2_OFFSET)
#define SOCP_REG_DEC_RAWINT2        (HI_SOCP_DEC_RAWINT2_OFFSET)
#define SOCP_REG_DEC_CORE0ISTAT2    (HI_SOCP_DEC_CORE0NOTE_NT2_OFFSET)
#define SOCP_REG_DEC_CORE1ISTAT2    (HI_SOCP_DEC_CORE1NOTE_INT2_OFFSET)
#define SOCP_REG_DEC_CORE1_MASK1    (HI_SOCP_DEC_CORE1_MASK1_OFFSET)
#define SOCP_REG_DEC_CORE1_INT1     (HI_SOCP_DEC_CORE1_INT1_OFFSET)

/*buffer*/

/* buffer*/
#define SOCP_REG_ENCSRC_BUFWPTR(m)  (HI_SOCP_ENC_SRC_BUFM_WPTR_0_OFFSET + m*0x40)
#define SOCP_REG_ENCSRC_BUFRPTR(m)  (HI_SOCP_ENC_SRC_BUFM_RPTR_0_OFFSET + m*0x40)
#define SOCP_REG_ENCSRC_BUFCFG0(m)  (HI_SOCP_ENC_SRC_BUFM_CFG0_0_OFFSET + m*0x40)
#define SOCP_REG_ENCSRC_BUFCFG1(m)  (HI_SOCP_ENC_SRC_BUFM_CFG1_0_OFFSET + m*0x40)
#define SOCP_REG_ENCSRC_RDQWPTR(m)  (HI_SOCP_ENC_SRC_RDQ_WPTR_0_OFFSET + m*0x40)
#define SOCP_REG_ENCSRC_RDQRPTR(m)  (HI_SOCP_ENC_SRC_RDQ_RPTR_0_OFFSET + m*0x40)
#define SOCP_REG_ENCSRC_RDQCFG(m)   (HI_SOCP_ENC_SRC_RDQ_CFG_0_OFFSET + m*0x40)
#ifdef FEATURE_SOCP_ADDR_64BITS
#define SOCP_REG_ENCSRC_BUFADDR_L(m)  (HI_SOCP_ENC_SRC_BUFM_ADDR_L_0_OFFSET + m*0x40)
#define SOCP_REG_ENCSRC_BUFADDR_H(m)  (HI_SOCP_ENC_SRC_BUFM_ADDR_H_0_OFFSET + m*0x40)
#define SOCP_REG_ENCSRC_RDQADDR_L(m)  (HI_SOCP_ENC_SRC_RDQ_BADDR_L_0_OFFSET + m*0x40)
#define SOCP_REG_ENCSRC_RDQADDR_H(m)  (HI_SOCP_ENC_SRC_RDQ_BADDR_H_0_OFFSET + m*0x40)
#else
#define SOCP_REG_ENCSRC_BUFADDR(m)  (HI_SOCP_ENC_SRC_BUFM_ADDR_0_OFFSET + m*0x40)
#define SOCP_REG_ENCSRC_RDQADDR(m)  (HI_SOCP_ENC_SRC_RDQ_BADDR_0_OFFSET + m*0x40)
#endif
/* buffer*/
#define SOCP_REG_ENCDEST_BUFWPTR(n) (HI_SOCP_ENC_DEST_BUFN_WPTR_0_OFFSET + (n)*0x20)
#define SOCP_REG_ENCDEST_BUFRPTR(n) (HI_SOCP_ENC_DEST_BUFN_RPTR_0_OFFSET + (n)*0x20)
#define SOCP_REG_ENCDEST_BUFCFG(n)  (HI_SOCP_ENC_DEST_BUFN_CFG_0_OFFSET + n*0x20)
#define SOCP_REG_ENCDEST_BUFTHRH(n) (HI_SOCP_ENC_DEST_BUFN_THRH_0_OFFSET + n*0x20)
#define SOCP_REG_ENCDEST_BUFTHRESHOLD(n) (HI_SOCP_ENC_INT_THRESHOLD_0_OFFSET + n*0x20)

#define SOCP_REG_ENCDEST_SBCFG(n)        (HI_SOCP_ENC_DEST_SB_CFG_OFFSET + n*0x20)

/* !   Boston CS(v2.04)*/
#define SOCP_REG_ENCDEST_BUFSIDEBAND(n)  (HI_SOCP_ENC_DEST_BUFN_SIDBAND_OFFSET + n*0x20)
////////////////////////////////////////////////////////////////////////////////////////////
#ifdef FEATURE_SOCP_ADDR_64BITS
#define SOCP_REG_ENCDEST_BUFADDR_L(n) (HI_SOCP_ENC_DEST_BUFN_ADDR_L_0_OFFSET + (n)*0x20)
#define SOCP_REG_ENCDEST_BUFADDR_H(n) (HI_SOCP_ENC_DEST_BUFN_ADDR_H_0_OFFSET + (n)*0x20)
#else
#define SOCP_REG_ENCDEST_BUFADDR(n) (HI_SOCP_ENC_DEST_BUFN_ADDR_0_OFFSET + (n)*0x20)
#endif

/*buffer*/
/* buffer*/
#define SOCP_REG_DECSRC_BUFWPTR(x)  (HI_SOCP_DEC_SRC_BUFX_WPTR_0_OFFSET + x*0x40)
#define SOCP_REG_DECSRC_BUFRPTR(x)  (HI_SOCP_DEC_SRC_BUFX_RPTR_0_OFFSET + x*0x40)
#define SOCP_REG_DECSRC_BUFCFG0(x)  (HI_SOCP_DEC_SRC_BUFX_CFG0_0_OFFSET + x*0x40)
#define SOCP_REG_DEC_BUFSTAT0(x)    (HI_SOCP_DEC_BUFX_STATUS0_0_OFFSET + x*0x40)
#define SOCP_REG_DEC_BUFSTAT1(x)    (HI_SOCP_DEC_BUFX_STATUS1_0_OFFSET + x*0x40)
/* !   Boston CS(v2.04)*/
#define SOCP_REG_DECSRC_BUFSIDEBAND(x) (HI_SOCP_DEC_SRC_BUFX_SIDEBAND_OFFSET + x*0x40)
#define SOCP_REG_DECDEST_BUFSIDEBAND(y)  (HI_SOCP_DEC_DEST_BUFY_SIDEBAND_OFFSET + y*0x10)
////////////////////////////////////////////////////////////////////////////////////////////
#ifdef FEATURE_SOCP_ADDR_64BITS
#define SOCP_REG_DECSRC_BUFADDR_L(x)  (HI_SOCP_DEC_SRC_BUFX_ADDR_L_0_OFFSET + x*0x40)
#define SOCP_REG_DECSRC_BUFADDR_H(x)  (HI_SOCP_DEC_SRC_BUFX_ADDR_H_0_OFFSET + x*0x40)
#else
#define SOCP_REG_DECSRC_BUFADDR(x)  (HI_SOCP_DEC_SRC_BUFX_ADDR_0_OFFSET + x*0x40)
#endif
/* buffer*/
#ifdef FEATURE_SOCP_ADDR_64BITS
#define SOCP_REG_DECDEST_BUFWPTR(y) (HI_SOCP_DEC_DEST_BUFY_WPTR_0_OFFSET + y*0x20)
#define SOCP_REG_DECDEST_BUFRPTR(y) (HI_SOCP_DEC_DEST_BUFY_RPTR_0_OFFSET + y*0x20)
#define SOCP_REG_DECDEST_BUFADDR_L(y) (HI_SOCP_DEC_DEST_BUFY_ADDR_L_0_OFFSET + y*0x20)
#define SOCP_REG_DECDEST_BUFADDR_H(y) (HI_SOCP_DEC_DEST_BUFY_ADDR_H_0_OFFSET + y*0x20)
#define SOCP_REG_DECDEST_BUFCFG(y)  (HI_SOCP_DEC_DEST_BUFY_CFG0_0_OFFSET + y*0x20)
#else
#define SOCP_REG_DECDEST_BUFWPTR(y) (HI_SOCP_DEC_DEST_BUFY_WPTR_0_OFFSET + y*0x10)
#define SOCP_REG_DECDEST_BUFRPTR(y) (HI_SOCP_DEC_DEST_BUFY_RPTR_0_OFFSET + y*0x10)
#define SOCP_REG_DECDEST_BUFADDR(y) (HI_SOCP_DEC_DEST_BUFY_ADDR_0_OFFSET + y*0x10)
#define SOCP_REG_DECDEST_BUFCFG(y)  (HI_SOCP_DEC_DEST_BUFY_CFG0_0_OFFSET + y*0x10)
#endif

/*DEBUG*/
#define SOCP_REG_ENCCD_DBG0         (HI_SOCP_ENC_CD_DBG0_OFFSET)
#define SOCP_REG_ENCCD_DBG1         (HI_SOCP_ENC_CD_DBG1_OFFSET)
#define SOCP_REG_ENCIBUF_DBG0       (HI_SOCP_ENC_IBUF_DBG0_OFFSET)
#define SOCP_REG_ENCIBUF_DBG1       (HI_SOCP_ENC_IBUF_DBG1_OFFSET)
#define SOCP_REG_ENCIBUF_DBG2       (HI_SOCP_ENC_IBUF_DBG2_OFFSET)
#define SOCP_REG_ENCIBUF_DBG3       (HI_SOCP_ENC_IBUF_DBG3_OFFSET)
#define SOCP_REG_ENCOBUF_DBG0       (HI_SOCP_ENC_OBUF_DBG0_OFFSET)
#define SOCP_REG_ENCOBUF_DBG1       (HI_SOCP_ENC_OBUF_DBG1_OFFSET)
#define SOCP_REG_ENCOBUF_DBG2       (HI_SOCP_ENC_OBUF_DBG2_OFFSET)
#define SOCP_REG_ENCOBUF_DBG3       (HI_SOCP_ENC_OBUF_DBG3_OFFSET)
#define SOCP_REG_DECIBUF_DBG0       (HI_SOCP_DEC_IBUF_DBG0_OFFSET)
#define SOCP_REG_DECIBUF_DBG1       (HI_SOCP_DEC_IBUF_DBG1_OFFSET)
#define SOCP_REG_DECIBUF_DBG2       (HI_SOCP_DEC_IBUF_DBG2_OFFSET)
#define SOCP_REG_DECIBUF_DBG3       (HI_SOCP_DEC_IBUF_DBG3_OFFSET)
#define SOCP_REG_DECOBUF_DBG0       (HI_SOCP_DEC_OBUF_DBG0_OFFSET)
#define SOCP_REG_DECOBUF_DBG1       (HI_SOCP_DEC_OBUF_DBG1_OFFSET)
#define SOCP_REG_DECOBUF_DBG2       (HI_SOCP_DEC_OBUF_DBG2_OFFSET)
#define SOCP_REG_DECOBUF_DBG3       (HI_SOCP_DEC_OBUF_DBG3_OFFSET)

/**/
#define SOCP_REG_SOCP_VERSION       (HI_SOCP_SOCP_VERSION_OFFSET)
#define SOCP_201_VERSION            (0x201)
#define SOCP_204_VERSION             (0x204)
#define SOCP_3_4MS_VERSION          (0x203)     /* 203SOCP3.4ms */
#define SOCP_CLK_RATIO(n)           (n*5/39)    /*  */

/* BBP  */
#define BBP_REG_LOG_ADDR(m)         (0x0200 + 0x10*m)
#define BBP_REG_LOG_WPTR(m)         (0x0204 + 0x10*m)
#define BBP_REG_LOG_RPTR(m)         (0x0208 + 0x10*m)
#define BBP_REG_LOG_CFG(m)          (0x020C + 0x10*m)
#define BBP_REG_DS_ADDR             (0x0280)
#define BBP_REG_DS_WPTR             (0x0284)
#define BBP_REG_DS_RPTR             (0x0288)
#define BBP_REG_DS_CFG              (0x028C)
#define BBP_REG_PTR_ADDR            (0x0290)
#define BBP_REG_CH_EN               (0x0294)
#define BBP_REG_PKT_CNT             (0x0298)
#define BBP_REG_CH_STAT             (0x029C)
#define BBP_REG_LOG_EN              (0x02B8)

/**************************************************************************
  
**************************************************************************/
#define SOCP_TOTAL_ENCSRC_CHN         (0x20)

#define BBP_MAX_CHN                   (0x09)
#define BBP_MAX_LOG_CHN               (0x08)
#define DSP_MAX_CHN                   (0x02)
#define SOCP_FIXED_MAX_CHAN           (BBP_MAX_CHN+DSP_MAX_CHN)
#define SOCP_MAX_ENCSRC_CHN           (0x20)    /*  */
#define SOCP_MAX_ENCDST_CHN           (0x07)
#define SOCP_MAX_DECSRC_CHN           (0x04)
#define SOCP_MAX_DECDST_CHN           (0x10)
#define SOCP_CCORE_ENCSRC_CHN_BASE    (4)
#define SOCP_CCORE_ENCSRC_CHN_NUM     (5)

/* LTE DSP/BBP */
#define SOCP_DSPLOG_CHN               (0x0e)         // 14
#define SOCP_BBPLOG_CHN               (SOCP_DSPLOG_CHN + 2)  // 168
#define SOCP_BBPDS_CHN                (SOCP_BBPLOG_CHN + 8)  // 24
#define SOCP_FIXCHN_BASE              (SOCP_DSPLOG_CHN)
#define SOCP_FIXCHN_END               (SOCP_BBPDS_CHN)

/*  */
#define BBP_REG_ARM_BASEADDR          HI_BBP_DMA_BASE_ADDR_VIRT
#define TENSILICA_CORE0_DRAM_ADDR     (0x49f80000)      /* DSP */
#define SOCP_REG_BASEADDR             (g_strSocpStat.baseAddr)

/*SOCP BBP*/
#define PBXA9_DRAM_BBPDS_VIRT         (IO_ADDRESS(DDR_SOCP_ADDR))      /*  */
#define PBXA9_DRAM_BBPDS_PHYS         (DDR_SOCP_ADDR)      /*  */
#define PBXA9_DRAM_BBPDS_SIZE         (DDR_SOCP_SIZE)           /*  */

#define INT_LVL_SOCP                  INT_LVL_SOCP0

/**/
#define SOCP_BBPDS_CHN_ADDR           (PBXA9_DRAM_BBPDS_PHYS)
#define SOCP_BBPDS_CHN_SIZE           (PBXA9_DRAM_BBPDS_SIZE)


#define SOCP_BBPLOG_CHN_SIZE          (0x2000)
// modify by yangzhi 20130624
#define SOCP_BBPLOG0_CHN_SIZE         (0x2000*8)
#define SOCP_FIXEDID_BASE             (SOCP_DSPLOG_CHN - SOCP_FIXCHN_BASE)

#define SOCP_DSPLOG_DST_BUFID         ((s32) 1)
#define SOCP_BBPLOG_DST_BUFID         ((s32) 1)
#define SOCP_BBPDS_DST_BUFID          ((s32) 1)


/* log2.0 2014-03-19 Begin:*/
/* SOCP10ms */
#define SOCP_LOG_FLUSH_MAX_OVER_TIME    10
/* log2.0 2014-03-19 End:*/
/**************************************************************************
  
**************************************************************************/

/*  */
typedef struct tagSOCP_RING_BUF_S
{
    unsigned long          Start;
    unsigned long          End;
    u32             		u32Write;
    u32             		u32Read;
    u32             		u32Length;
    u32             		u32IdleSize;
}SOCP_RING_BUF_S;

typedef struct tagSOCP_ENCSRC_CHAN_S
{
    u32                     u32ChanID;
    u32                     u32ChanEn;
    u32                     u32DestChanID;
    u32                     u32BypassEn;
    u32                     u32AllocStat;  /* */
    u32                     u32LastRdSize;
    u32                     u32RdThreshold;
    SOCP_ENCSRC_CHNMODE_ENUM_UIN32   eChnMode;      /*  */
    SOCP_CHAN_PRIORITY_ENUM_UIN32    ePriority;
    SOCP_DATA_TYPE_ENUM_UIN32        eDataType;
    SOCP_DATA_TYPE_EN_ENUM_UIN32     eDataTypeEn;
    SOCP_ENC_DEBUG_EN_ENUM_UIN32     eDebugEn;
    SOCP_RING_BUF_S         sEncSrcBuf;
    SOCP_RING_BUF_S         sRdBuf;
    socp_event_cb           event_cb;
    socp_rd_cb              rd_cb;
}SOCP_ENCSRC_CHAN_S;


typedef struct tagSOCP_ENCSRC_FIXCHAN_S
{
    u32                     u32ChanID;
    u32                     u32ChanEn;
    u32                     u32DestChanID;
    SOCP_ENCSRC_CHNMODE_ENUM_UIN32   eChnMode;      /*  */
    SOCP_CHAN_PRIORITY_ENUM_UIN32    ePriority;
    SOCP_DATA_TYPE_ENUM_UIN32        eDataType;
    SOCP_DATA_TYPE_EN_ENUM_UIN32     eDataTypeEn;
    SOCP_ENC_DEBUG_EN_ENUM_UIN32     eDebugEn;
    SOCP_RING_BUF_S         sEncSrcBuf;
    SOCP_RING_BUF_S         sRdBuf;
    socp_event_cb           event_cb;
    socp_rd_cb              rd_cb;
}SOCP_ENCSRC_FIXCHAN_S;



typedef struct socp_compress
{
    int bcompress;
    socp_compress_ops_stru  ops;
}socp_compress_stru;

typedef struct tagSOCP_ENCDST_CHAN_S
{
    u32                     u32ChanID;
    u32                     u32SetStat;    /* */
    u32                     u32Thrh;       /* */
    socp_compress_stru      struCompress;
    SOCP_RING_BUF_S         sEncDstBuf;
    SOCP_EVENT_ENUM_UIN32            eChnEvent;
    socp_event_cb           event_cb;
    socp_read_cb            read_cb;
    u32                     bufThreshold;
}SOCP_ENCDST_CHAN_S;

typedef struct tagSOCP_DECSRC_CHAN_S
{
    u32                     u32ChanID;
    u32                     u32ChanEn;
    u32                     u32SetStat;    /* */
    u32                     u32RdThreshold;
    SOCP_DATA_TYPE_EN_ENUM_UIN32     eDataTypeEn;
    SOCP_DECSRC_CHNMODE_ENUM_UIN32   eChnMode;      /*  */
    SOCP_RING_BUF_S         sDecSrcBuf;
    SOCP_RING_BUF_S         sDecRdBuf;
    socp_event_cb           event_cb;
    socp_rd_cb              rd_cb;
}SOCP_DECSRC_CHAN_S;

typedef struct tagSOCP_DECDST_CHAN_S
{
    u32                     u32ChanID;
    u32                     u32AllocStat;
    SOCP_DATA_TYPE_ENUM_UIN32        eDataType;
    SOCP_RING_BUF_S         sDecDstBuf;
    socp_event_cb           event_cb;
    socp_read_cb            read_cb;
}SOCP_DECDST_CHAN_S;


/*  */
typedef struct tagSOCP_GBL_STATE
{
    s32                     bInitFlag;
    unsigned long           baseAddr;
    unsigned long           armBaseAddr;
    unsigned long           tensiAddr;
    unsigned long           bbpDsAddr;
    struct semaphore        u32EncSrcSemID;
    struct semaphore        u32EncDstSemID;
    struct semaphore        u32DecSrcSemID;
    struct semaphore        u32DecDstSemID;
    unsigned long           u32EncSrcTskID;
    unsigned long           u32EncDstTskID;
    unsigned long           u32DecSrcTskID;
    unsigned long           u32DecDstTskID;
    u32                     u32IntEncSrcHeader;
    u32                     u32IntEncSrcRD;
    u32                     u32IntEncDstTfr;
    u32                     u32IntEncDstOvf;
    u32                     u32IntEncDstThresholdOvf;
    u32                     u32IntDecSrcErr;
    u32                     u32IntDecDstTfr;
    u32                     u32IntDecDstOvf;
    socp_compress_isr       compress_isr;
    SOCP_ENCSRC_CHAN_S      sEncSrcChan[SOCP_MAX_ENCSRC_CHN];
    SOCP_ENCDST_CHAN_S      sEncDstChan[SOCP_MAX_ENCDST_CHN];
    SOCP_DECSRC_CHAN_S      sDecSrcChan[SOCP_MAX_DECSRC_CHN];
    SOCP_DECDST_CHAN_S      sDecDstChan[SOCP_MAX_DECDST_CHN];
}SOCP_GBL_STATE;

/**/
enum SOCP_ENC_DST_OUTPUT_COMPRESS_ENUM
{
    SOCP_NO_COMPRESS       = 0,
    SOCP_COMPRESS,
};
typedef unsigned int SOCP_ENC_DST_COMPRESS_UINT32;

typedef struct tagSOCP_DEBUG_GBL_S
{
    u32  u32SocpAllocEncSrcCnt;        /* SOCP*/
    u32  u32SocpAllocEncSrcSucCnt;     /* SOCP*/
    u32  u32SocpSetEncDstCnt;          /* SOCP*/
    u32  u32SocpSetEncDstSucCnt;       /* SOCP*/
    u32  u32SocpSetDecSrcCnt;          /* SOCP*/
    u32  u32SocpSetDeSrcSucCnt;        /* SOCP*/
    u32  u32SocpAllocDecDstCnt;        /* SOCP*/
    u32  u32SocpAllocDecDstSucCnt;     /* SOCP*/
    u32 u32SocpAppEtrIntCnt;           /* APP*/
    u32 u32SocpAppSucIntCnt;           /* APP*/
} SOCP_DEBUG_GBL_S;

typedef struct tagSOCP_DEBUG_ENCSRC_S
{
    u32 u32SocpFreeEncSrcCnt[SOCP_MAX_ENCSRC_CHN];         /* SOCP*/
    u32 u32SocpSoftResetEncSrcCnt[SOCP_MAX_ENCSRC_CHN];    /* SOCP*/
    u32 u32SocpStartEncSrcCnt[SOCP_MAX_ENCSRC_CHN];        /* SOCP*/
    u32 u32SocpStopEncSrcCnt[SOCP_MAX_ENCSRC_CHN];         /* SOCP*/
    u32 u32SocpRegEventEncSrcCnt[SOCP_MAX_ENCSRC_CHN];     /* SOCP*/
    u32 u32SocpGetWBufEncSrcEtrCnt[SOCP_MAX_ENCSRC_CHN];      /* SOCPbuffer*/
    u32 u32SocpGetWBufEncSrcSucCnt[SOCP_MAX_ENCSRC_CHN];      /* SOCPbuffer*/
    u32 u32socp_write_doneEncSrcEtrCnt[SOCP_MAX_ENCSRC_CHN];    /* SOCPbuffer*/
    u32 u32socp_write_doneEncSrcSucCnt[SOCP_MAX_ENCSRC_CHN];    /* SOCPbuffer*/
    u32 u32socp_write_doneEncSrcFailCnt[SOCP_MAX_ENCSRC_CHN];    /* SOCPbuffer*/
    u32 u32SocpRegRdCBEncSrcCnt[SOCP_MAX_ENCSRC_CHN];          /* SOCPRDbuffer*/
    u32 u32SocpGetRdBufEncSrcEtrCnt[SOCP_MAX_ENCSRC_CHN];     /* SOCPRdbuffer*/
    u32 u32SocpGetRdBufEncSrcSucCnt[SOCP_MAX_ENCSRC_CHN];     /* SOCPRdbuffer*/
    u32 u32SocpReadRdDoneEncSrcEtrCnt[SOCP_MAX_ENCSRC_CHN];   /* SOCPRdbuffer*/
    u32 u32SocpReadRdDoneEncSrcSucCnt[SOCP_MAX_ENCSRC_CHN];   /* SOCPRdbuffer*/
    u32 u32SocpReadRdDoneEncSrcFailCnt[SOCP_MAX_ENCSRC_CHN];   /* SOCPRdbuffer*/
    u32 u32SocpEncSrcTskHeadCbCnt[SOCP_MAX_ENCSRC_CHN];      /* */
    u32 u32SocpEncSrcTskHeadCbOriCnt[SOCP_MAX_ENCSRC_CHN];   /* */
    u32 u32SocpEncSrcTskRdCbCnt[SOCP_MAX_ENCSRC_CHN];        /* Rd */
    u32 u32SocpEncSrcTskRdCbOriCnt[SOCP_MAX_ENCSRC_CHN];     /* Rd */
    u32 u32SocpEncSrcIsrHeadIntCnt[SOCP_MAX_ENCSRC_CHN];      /* ISR*/
    u32 u32SocpEncSrcIsrRdIntCnt[SOCP_MAX_ENCSRC_CHN];        /* ISRRd */
} SOCP_DEBUG_ENCSRC_S;

typedef struct tagSOCP_DEBUG_ENCDST_S
{
    u32 u32SocpRegEventEncDstCnt[SOCP_MAX_ENCDST_CHN];     /* SOCP*/
    u32 u32SocpRegReadCBEncDstCnt[SOCP_MAX_ENCDST_CHN];    /* SOCP*/
    u32 u32SocpGetReadBufEncDstEtrCnt[SOCP_MAX_ENCDST_CHN];   /* SOCP*/
    u32 u32SocpGetReadBufEncDstSucCnt[SOCP_MAX_ENCDST_CHN];   /* SOCP*/
    u32 u32socp_read_doneEncDstEtrCnt[SOCP_MAX_ENCDST_CHN];     /* SOCPbuffer*/
    u32 u32socp_read_doneEncDstSucCnt[SOCP_MAX_ENCDST_CHN];     /* SOCPbuffer*/
    u32 u32socp_read_doneEncDstFailCnt[SOCP_MAX_ENCDST_CHN];     /* SOCPbuffer*/
    u32 u32socp_read_doneZeroEncDstCnt[SOCP_MAX_ENCDST_CHN];     /* SOCPbuffer size 0 */
    u32 u32socp_read_doneValidEncDstCnt[SOCP_MAX_ENCDST_CHN];    /* SOCPbuffer size 0 */
    u32 u32SocpEncDstTskTrfCbCnt[SOCP_MAX_ENCDST_CHN];        /* */
    u32 u32SocpEncDstTskTrfCbOriCnt[SOCP_MAX_ENCDST_CHN];        /* */
    u32 u32SocpEncDstTskOvfCbCnt[SOCP_MAX_ENCDST_CHN];        /* buf */
    u32 u32SocpEncDstTskOvfCbOriCnt[SOCP_MAX_ENCDST_CHN];     /* buf */
    u32 u32SocpEncDstIsrTrfIntCnt[SOCP_MAX_ENCDST_CHN];        /* ISR*/
    u32 u32SocpEncDstIsrOvfIntCnt[SOCP_MAX_ENCDST_CHN];        /* ISRbuf */
    u32 u32SocpEncDstTskThresholdOvfCbCnt[SOCP_MAX_ENCDST_CHN];        /* buf*/
    u32 u32SocpEncDstTskThresholdOvfCbOriCnt[SOCP_MAX_ENCDST_CHN];     /* buf*/
    u32 u32SocpEncDstIsrThresholdOvfIntCnt[SOCP_MAX_ENCDST_CHN];       /* ISRbuf*/
    /* log2.0 2014-03-19 Begin:*/
	BSP_U32 u32SocpEncDstSoftOverTimeOriCnt[SOCP_MAX_ENCDST_CHN];  /* SOCP */
    BSP_U32 u32SocpEncDstSoftOverTimeCnt[SOCP_MAX_ENCDST_CHN];     /* SOCP */
	/* log2.0 2014-03-19 End:*/
} SOCP_DEBUG_ENCDST_S;

typedef struct tagSOCP_DEBUG_DECSRC_S
{
    u32 u32SocpSoftResetDecSrcCnt[SOCP_MAX_DECSRC_CHN];    /* SOCP*/
    u32 u32SocpStartDecSrcCnt[SOCP_MAX_DECSRC_CHN];        /* SOCP*/
    u32 u32SocpStopDecSrcCnt[SOCP_MAX_DECSRC_CHN];         /* SOCP*/
    u32 u32SocpRegEventDecSrcCnt[SOCP_MAX_DECSRC_CHN];     /* SOCP*/
    u32 u32SocpGetWBufDecSrcEtrCnt[SOCP_MAX_DECSRC_CHN];      /* SOCPbuffer*/
    u32 u32SocpGetWBufDecSrcSucCnt[SOCP_MAX_DECSRC_CHN];      /* SOCPbuffer*/
    u32 u32socp_write_doneDecSrcEtrCnt[SOCP_MAX_DECSRC_CHN];    /* SOCPbuffer*/
    u32 u32socp_write_doneDecSrcSucCnt[SOCP_MAX_DECSRC_CHN];    /* SOCPbuffer*/
    u32 u32socp_write_doneDecSrcFailCnt[SOCP_MAX_DECSRC_CHN];    /* SOCPbuffer*/
    u32 u32SocpRegRdCBDecSrcCnt[SOCP_MAX_DECSRC_CHN];      /* SOCPRDbuffer*/
    u32 u32SocpGetRdBufDecSrcEtrCnt[SOCP_MAX_DECSRC_CHN];     /* SOCPRdbuffer*/
    u32 u32SocpGetRdBufDecSrcSucCnt[SOCP_MAX_DECSRC_CHN];     /* SOCPRdbuffer*/
    u32 u32SocpReadRdDoneDecSrcEtrCnt[SOCP_MAX_DECSRC_CHN];   /* SOCPRdbuffer*/
    u32 u32SocpReadRdDoneDecSrcSucCnt[SOCP_MAX_DECSRC_CHN];   /* SOCPRdbuffer*/
    u32 u32SocpReadRdDoneDecSrcFailCnt[SOCP_MAX_DECSRC_CHN];   /* SOCPRdbuffer*/
    u32 u32SocpDecSrcIsrErrIntCnt[SOCP_MAX_DECSRC_CHN];        /* ISR*/
    u32 u32SocpDecSrcTskErrCbCnt[SOCP_MAX_DECSRC_CHN];        /* */
    u32 u32SocpDecSrcTskErrCbOriCnt[SOCP_MAX_DECSRC_CHN];     /* */
} SOCP_DEBUG_DECSRC_S;

typedef struct tagSOCP_DEBUG_DECDST_S
{
    u32 u32SocpFreeDecDstCnt[SOCP_MAX_DECDST_CHN];         /* SOCP*/
    u32 u32SocpRegEventDecDstCnt[SOCP_MAX_DECDST_CHN];     /* SOCP*/
    u32 u32SocpRegReadCBDecDstCnt[SOCP_MAX_DECDST_CHN];    /* SOCP*/
    u32 u32SocpGetReadBufDecDstEtrCnt[SOCP_MAX_DECDST_CHN];   /* SOCP*/
    u32 u32SocpGetReadBufDecDstSucCnt[SOCP_MAX_DECDST_CHN];   /* SOCP*/
    u32 u32socp_read_doneDecDstEtrCnt[SOCP_MAX_DECDST_CHN];     /* SOCPbuffer*/
    u32 u32socp_read_doneDecDstSucCnt[SOCP_MAX_DECDST_CHN];     /* SOCPbuffer*/
    u32 u32socp_read_doneDecDstFailCnt[SOCP_MAX_DECDST_CHN];     /* SOCPbuffer*/
    u32 u32socp_read_doneZeroDecDstCnt[SOCP_MAX_DECDST_CHN];   /* SOCPbuffer size 0 */
    u32 u32socp_read_doneValidDecDstCnt[SOCP_MAX_DECDST_CHN];   /* SOCPbuffer size 0 */
    u32 u32SocpDecDstIsrTrfIntCnt[SOCP_MAX_DECDST_CHN];        /* ISR*/
    u32 u32SocpDecDstTskTrfCbCnt[SOCP_MAX_DECDST_CHN];         /* */
    u32 u32SocpDecDstTskTrfCbOriCnt[SOCP_MAX_DECDST_CHN];      /* */
    u32 u32SocpDecDstIsrOvfIntCnt[SOCP_MAX_DECDST_CHN];        /* ISRbuf */
    u32 u32SocpDecDstTskOvfCbCnt[SOCP_MAX_DECDST_CHN];         /* buf */
    u32 u32SocpDecDstTskOvfCbOriCnt[SOCP_MAX_DECDST_CHN];      /* buf */
} SOCP_DEBUG_DECDST_S;

/* */
typedef struct tagSOCP_DEBUG_INFO_S
{
    SOCP_DEBUG_GBL_S    sSocpDebugGBl;
    SOCP_DEBUG_ENCSRC_S sSocpDebugEncSrc;
    SOCP_DEBUG_ENCDST_S sSocpDebugEncDst;
    SOCP_DEBUG_DECSRC_S sSocpDebugDecSrc;
    SOCP_DEBUG_DECDST_S sSocpDebugDecDst;
}SOCP_DEBUG_INFO_S;

typedef struct
{
    SOCP_VOTE_TYPE_ENUM_U32 vote_type;
    BSP_U32                 vote_time;
}SOCP_VOTE_INFO_STRU;

typedef struct
{
    BSP_U32 en_flag;
}SOCP_ON_DEMAND_STRU;

typedef struct
{
    struct device * dev;
    struct regulator_bulk_data socp_vcc;
}SOCP_VCC_STRU;

typedef enum{
    SOCP_DST_CHAN_CFG_ADDR = 0,
    SOCP_DST_CHAN_CFG_SIZE,
    SOCP_DST_CHAN_CFG_TIME,
    SOCP_DST_CHAN_CFG_RSV,
    SOCP_DST_CHAN_CFG_BUTT
}SOCP_DST_CHAN_CFG_ENUM;

typedef struct
{
    struct device * dev;
    struct clk    * socp_clk;
    u32             ulCnt;
}SOCP_CLK_STRU;

/**************************************************************************
  
**************************************************************************/

/*
* Bit masks for registers: ENCSTAT,DECSTAT, channel state
*/
#define SOCP_CHN_BUSY                   ( (s32) 1)   /**/
#define SOCP_CHN_IDLE                   ( (s32) 0)   /**/

/*
* 
*/
#define SOCP_CHN_ALLOCATED              ((s32) 1)    /**/
#define SOCP_CHN_UNALLOCATED            ((s32) 0)    /**/

/*
* 
*/
#define SOCP_CHN_ENABLE                 ( (s32) 1)   /**/
#define SOCP_CHN_DISABLE                ( (s32) 0)   /**/

/*
* 
*/
#define SOCP_CHN_SET                    ( (s32) 1)     /**/
#define SOCP_CHN_UNSET                  ( (s32) 0)     /**/
/*
* 
*/
#define SOCP_ENCSRC_BYPASS_ENABLE       ( (s32) 1)     /**/
#define SOCP_ENCSRC_BYPASS_DISABLE      ( (s32) 0)     /**/


/*
* 
*/
#define SOCP_DECSRC_DEBUG_ENBALE        ( (s32) 1)     /*DEBUG */
#define SOCP_DECSRC_DEBUG_DISBALE       ( (s32) 0)     /*DEBUG */

#define SOCP_CORE0_DEC_OUTOVFINT_MASK   ( (s32)(1))          /* core0 BUFFER */
#define SOCP_DEC_INERRINT_MASK          ( (s32)(1<<1))       /*  */
#define SOCP_CORE0_DEC_TFRINT_MASK      ( (s32)(1<<2))       /* core0  */
#define SOCP_CORE1_DEC_TFRINT_MASK      ( (s32)(1<<3))       /* core1  */
#define SOCP_CORE1_DEC_OUTOVFINT_MASK   ( (s32)(1<<4))       /* core1 BUFFER*/
#define SOCP_CORE0_ENC_MODESWT_MASK     ( (s32)(1<<6))       /* core0 buffer */
#define SOCP_CORE1_ENC_MODESWT_MASK     ( (s32)(1<<7))       /* core1 buffer */
#define SOCP_MODEM_ENC_RDINT_MASK       ( (s32)(1<<10))      /* RDBUFFER */
#define SOCP_APP_ENC_RDINT_MASK         ( (s32)(1<<11))      /* APPCPURd */
#define SOCP_APP_ENC_OUTOVFINT_MASK     ( (s32)(1<<12))      /* RDBUFFER */
#define SOCP_MODEM_ENC_FLAGINT_MASK     ( (s32)(1<<13))      /* MODEMCPU */
#define SOCP_APP_ENC_FLAGINT_MASK       ( (s32)(1<<14))      /* APP  CPU */
#define SOCP_APP_ENC_TFRINT_MASK        ( (s32)(1<<15))      /*  */
#define SOCP_DEC_SRCINT_NUM             (6)                  /* MODEMCPU */


#define SOCP_TRANS_TIMEOUT_DEFAULT      (0x17)     //dec:23
#define SOCP_OVERFLOW_TIMEOUT_DEFAULT   (0x5969)   //dec:22889

#define SOCP_DEC_PKTLGTH_MAX            (0x04)     //dec:4096, KB
#define SOCP_DEC_PKTLGTH_MIN            (0x06)     //dec:6, 
#define SOCP_TIMEOUT_MAX                (0xffff)
#define SOCP_DEC_MAXPKT_MAX             (0x1000)
#define SOCP_DEC_MINPKT_MAX             (0x1f)
#define SOCP_ENC_SRC_BUFLGTH_MAX        (0x7ffffff)
#define SOCP_ENC_SRC_RDLGTH_MAX         (0xffff)
#define SOCP_ENC_DST_BUFLGTH_MAX        (0x1fffff)
#define SOCP_ENC_DST_TH_MAX             (0x7ff)
#define SOCP_DEC_SRC_BUFLGTH_MAX        (0xffff)
#define SOCP_DEC_SRC_RDLGTH_MAX         (0xffff)
#define SOCP_DEC_DST_BUFLGTH_MAX        (0xffff)
#define SOCP_DEC_DST_TH_MAX             (0xff)

// buffer16-22
#define SOCP_ENC_DST_BUFF_THRESHOLD_OVF_MASK    (0x007f0000)
#define SOCP_ENC_DST_BUFF_OVF_MASK              (0x0000007f)
// 
#define SOCP_ENC_DST_BUFF_THRESHOLD_OVF_BEGIN   (16)

#define SOCP_RESET_TIME                 (1000)
#define SOCP_GBLRESET_TIME              (100)

extern SOCP_GBL_STATE g_strSocpStat;

/*  */
//cppcheck-suppress *
#define SOCP_CHECK_INIT() \
    do{\
        if (!g_strSocpStat.bInitFlag)\
        {\
            socp_printf("the module has not been initialized!\n");\
            return BSP_ERR_SOCP_NOT_INIT;\
        }\
    }while(0)

/*  */
//cppcheck-suppress *
#define SOCP_CHECK_PARA(para) \
    do{\
        if (0 == para)\
        {\
            socp_printf("the parameter is NULL!\n");\
            return BSP_ERR_SOCP_NULL;\
        }\
    }while(0)
//cppcheck-suppress *
#define SOCP_CHECK_BUF_ADDR(start, end) \
    do{\
        if (start >= end)\
        {\
            socp_printf("the buff is valid!\n");\
            socp_printf("start: %p\n", (char*)start);\
            socp_printf("end: %p\n", (char*)end);\
            return BSP_ERR_SOCP_INVALID_PARA;\
        }\
    }while(0)

//cppcheck-suppress *
#define SOCP_CHECK_CHAN_TYPE(para, type) \
    do{\
        if (type != para)\
        {\
            socp_printf("the Chan's Type is Valid!\n");\
            return BSP_ERR_SOCP_INVALID_CHAN;\
        }\
    }while(0)
    
//cppcheck-suppress *
#define SOCP_CHECK_CHAN_ID(para, id) \
    do{\
        if (para >= id)\
        {\
            socp_printf("the Chan Id is Valid!\n");\
            return BSP_ERR_SOCP_INVALID_CHAN;\
        }\
    }while(0)

//cppcheck-suppress *
#define SOCP_CHECK_ENCSRC_CHAN_ID(id) \
    do {\
        if ((id >= SOCP_CCORE_ENCSRC_CHN_BASE) && (id < (SOCP_CCORE_ENCSRC_CHN_BASE + SOCP_CCORE_ENCSRC_CHN_NUM)))\
        {\
            socp_printf("the Chan Id is Valid!\n"); \
            return BSP_ERR_SOCP_INVALID_CHAN; \
        } \
    } while (0)

/* 8 */
//cppcheck-suppress *
#define SOCP_CHECK_8BYTESALIGN(para) \
    do{\
        if (0 != (para%8))\
        {\
            socp_printf("the parameter is not 8 bytes aligned!\n");\
            return BSP_ERR_SOCP_NOT_8BYTESALIGN;\
        }\
    }while(0)

//cppcheck-suppress *
#define SOCP_CHECK_ENCSRC_CHNMODE(para) \
    do{\
        if (para >= SOCP_ENCSRC_CHNMODE_BUTT)\
        {\
            socp_printf("encoder src channele mode is %d, which is valid!\n", para);\
            return BSP_ERR_SOCP_INVALID_PARA;\
        }\
    }while(0)

//cppcheck-suppress *
#define SOCP_CHECK_DECSRC_CHNMODE(para) \
    do{\
        if (para >= SOCP_DECSRC_CHNMODE_BUTT)\
        {\
            socp_printf("decoder dst channele mode is %d, which is valid!\n", para);\
            return BSP_ERR_SOCP_INVALID_PARA;\
        }\
    }while(0)

//cppcheck-suppress *
#define SOCP_CHECK_CHAN_PRIORITY(para) \
    do{\
        if (para >= SOCP_CHAN_PRIORITY_BUTT)\
        {\
            socp_printf("encoder src channele priority is %d, which is valid!\n", para);\
            return BSP_ERR_SOCP_INVALID_PARA;\
        }\
    }while(0)

//cppcheck-suppress *
#define SOCP_CHECK_DATA_TYPE(para) \
    do{\
        if (para >= SOCP_DATA_TYPE_BUTT)\
        {\
            socp_printf("channel data type is %d, which is valid!\n", para);\
            return BSP_ERR_SOCP_INVALID_PARA;\
        }\
    }while(0)

//cppcheck-suppress *
#define SOCP_CHECK_ENCSRC_ALLOC(id) \
    do{\
        if(SOCP_CHN_ALLOCATED != g_strSocpStat.sEncSrcChan[id].u32AllocStat)\
        {\
            socp_printf("encoder src[%d] not allocated!\n", id);\
            return BSP_ERR_SOCP_INVALID_CHAN;\
        }\
    }while(0)

//cppcheck-suppress *
#define SOCP_CHECK_ENCDST_SET(id) \
    do{\
        if(SOCP_CHN_SET!= g_strSocpStat.sEncDstChan[id].u32SetStat)\
        {\
            socp_printf("encoder dst[%d] set failed!\n", id);\
            return BSP_ERR_SOCP_INVALID_CHAN;\
        }\
    }while(0)

//cppcheck-suppress *
#define SOCP_CHECK_DECSRC_SET(id) \
    do{\
        if(SOCP_CHN_SET!= g_strSocpStat.sDecSrcChan[id].u32SetStat)\
        {\
            socp_printf("decoder[%d] src set failed!\n", id);\
            return BSP_ERR_SOCP_INVALID_CHAN;\
        }\
    }while(0)

//cppcheck-suppress *
#define SOCP_CHECK_DECDST_ALLOC(id) \
    do{\
        if(SOCP_CHN_ALLOCATED!= g_strSocpStat.sDecDstChan[id].u32AllocStat)\
        {\
            socp_printf("decoder dst[%d] alloc failed!\n", id);\
            return BSP_ERR_SOCP_INVALID_CHAN;\
        }\
    }while(0)

//cppcheck-suppress *
#define SOCP_CHECK_DATA_TYPE_EN(param) \
    do {\
        if (param >= SOCP_DATA_TYPE_EN_BUTT)\
        {\
            socp_printf("the data type en is valid, para is %d!\n", param); \
            return BSP_ERR_SOCP_INVALID_PARA; \
        } \
    } while (0)

//cppcheck-suppress *
#define SOCP_CHECK_ENC_DEBUG_EN(param) \
    do {\
        if (param >= SOCP_ENC_DEBUG_EN_BUTT)\
        {\
            socp_printf("the enc src debug en is valid, para is %d!\n", param); \
            return BSP_ERR_SOCP_INVALID_PARA; \
        } \
    } while (0)


/**************************************************************************
  
**************************************************************************/
s32 socp_soft_free_encdst_chan(u32 u32EncDstChanId);
s32 socp_soft_free_decsrc_chan(u32 u32DecSrcChanId);
s32 socp_reset_dec_chan(u32 u32ChanID);
s32 socp_get_index(u32 u32Size,u32 *index);
s32 socp_can_sleep(void);
void bsp_socp_encdst_set_cycle(u32 chanid, u32 cycle);
/* log2.0 2014-03-19 Begin:*/
u32 socp_is_encdst_chan_empty(void);
/* log2.0 2014-03-19 End:*/



void socp_help(void);

#define BSP_REG_SETBITS(base, reg, pos, bits, val) (BSP_REG(base, reg) = (BSP_REG(base, reg) & (~((((u32)1 << (bits)) - 1) << (pos)))) \
                                                                         | ((u32)((val) & (((u32)1 << (bits)) - 1)) << (pos)))
#define BSP_REG_GETBITS(base, reg, pos, bits) ((BSP_REG(base, reg) >> (pos)) & (((u32)1 << (bits)) - 1))

#define SOCP_REG_WRITE(reg, data) (writel(data, (volatile void *)(g_strSocpStat.baseAddr + reg)))
#define SOCP_REG_READ(reg, result) (result = readl((const volatile void *)(g_strSocpStat.baseAddr + reg)))

#define SOCP_REG_SETBITS(reg, pos, bits, val) BSP_REG_SETBITS(g_strSocpStat.baseAddr, reg, pos, bits, val)
#define SOCP_REG_GETBITS(reg, pos, bits) BSP_REG_GETBITS(g_strSocpStat.baseAddr, reg, pos, bits)

#define BBP_REG_WRITE(reg, data) (writel(data, (volatile void *)(g_strSocpStat.armBaseAddr + reg)))
#define BBP_REG_READ(reg, result) (result = readl((const volatile void *)(g_strSocpStat.armBaseAddr + reg)))

#define BBP_REG_SETBITS(reg, pos, bits, val) BSP_REG_SETBITS(g_strSocpStat.armBaseAddr, reg, pos, bits, val)
#define BBP_REG_GETBITS(reg, pos, bits) BSP_REG_GETBITS(g_strSocpStat.armBaseAddr, reg, pos, bits)
/**************************************************************************/

// #define SOCP_FLUSH_CACHE(ptr, size) __dma_single_cpu_to_dev(ptr, size, 1)
// #define SOCP_INVALID_CACHE(ptr, size) __dma_single_dev_to_cpu(ptr, size, 2)

#define SOCP_FLUSH_CACHE(ptr, size)  (0)
#define SOCP_INVALID_CACHE(ptr, size) (0)



#if defined(__KERNEL__)

#define Socp_Memcpy(dst,src,len)       (void)memcpy(dst,src,len)
#define Socp_Memset(src,count,len)     (void)memset(src,count,len)

#elif defined(__OS_VXWORKS__)

#define Socp_Memcpy(dst,src,len)       (void)memcpy(dst,src,len)
#define Socp_Memset(src,count,len)     (void)memset(src,count,len)

#elif defined(__OS_RTOSCK__)

//#define Socp_Memcpy(dst,src,len)        (void)memcpy_s(dst,len,src,len)
//#define Socp_Memset(src,count,len)     (void)memset_s(src, len,count,len)

#endif
#define socp_printf(fmt,...)     bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_SOCP,fmt,##__VA_ARGS__)

#define BIT_N(n)                (0x01 << (n))
#define SOCP_DEBUG_READ_DONE    BIT_N(0)
#define SOCP_DEBUG_READ_CB      BIT_N(1)

#define SOCP_DEBUG_TRACE(ulSwitch, ARG1, ARG2, ARG3, ARG4) \
do{\
    if(FALSE != (g_ulSocpDebugTraceCfg&ulSwitch)) \
    { \
        socp_printf("[%s] %d, 0x%x, 0x%x, 0x%x, 0x%x\n", __FUNCTION__, __LINE__, ARG1, ARG2, ARG3, ARG4); \
    }\
}while(0)


#ifdef __cplusplus
}
#endif

#endif



