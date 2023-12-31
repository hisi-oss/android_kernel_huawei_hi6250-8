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

#ifndef _BSP_SOCP_H
#define _BSP_SOCP_H

#include "osl_common.h"
#include "mdrv_socp_common.h"
#include "bsp_trace.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**************************************************************************
  
**************************************************************************/
#define BSP_ERR_SOCP_BASE            BSP_DEF_ERR(BSP_MODU_SOCP, 0)
#define BSP_ERR_SOCP_NULL            (BSP_ERR_SOCP_BASE + 0x1)
#define BSP_ERR_SOCP_NOT_INIT        (BSP_ERR_SOCP_BASE + 0x2)
#define BSP_ERR_SOCP_MEM_ALLOC       (BSP_ERR_SOCP_BASE + 0x3)
#define BSP_ERR_SOCP_SEM_CREATE      (BSP_ERR_SOCP_BASE + 0x4)
#define BSP_ERR_SOCP_TSK_CREATE      (BSP_ERR_SOCP_BASE + 0x5)
#define BSP_ERR_SOCP_INVALID_CHAN    (BSP_ERR_SOCP_BASE + 0x6)
#define BSP_ERR_SOCP_INVALID_PARA    (BSP_ERR_SOCP_BASE + 0x7)
#define BSP_ERR_SOCP_NO_CHAN         (BSP_ERR_SOCP_BASE + 0x8)
#define BSP_ERR_SOCP_SET_FAIL        (BSP_ERR_SOCP_BASE + 0x9)
#define BSP_ERR_SOCP_TIMEOUT         (BSP_ERR_SOCP_BASE + 0xa)
#define BSP_ERR_SOCP_NOT_8BYTESALIGN (BSP_ERR_SOCP_BASE + 0xb)
#define BSP_ERR_SOCP_CHAN_RUNNING    (BSP_ERR_SOCP_BASE + 0xc)
#define BSP_ERR_SOCP_CHAN_MODE       (BSP_ERR_SOCP_BASE + 0xd)
#define BSP_ERR_SOCP_DEST_CHAN       (BSP_ERR_SOCP_BASE + 0xe)
#define BSP_ERR_SOCP_DECSRC_SET      (BSP_ERR_SOCP_BASE + 0xf)

typedef u32 (*socp_compress_isr)     (void);
typedef u32 (*socp_compress_event_cb)(socp_event_cb EventCB);
typedef u32 (*socp_compress_read_cb) (socp_read_cb ReadCB);
typedef u32 (*socp_compress_enable)  (void);
typedef u32 (*socp_compress_disable) (void);
typedef u32 (*socp_compress_set)     (u32 chanid, SOCP_CODER_DEST_CHAN_S* attr);
typedef u32 (*socp_compress_getbuffer) (SOCP_BUFFER_RW_STRU *pRingBuffer);
typedef u32 (*socp_compress_readdone)(u32 u32Size);
typedef u32 (*socp_compress_clear)   (void);

typedef struct socp_compress_ops
{
    socp_compress_isr       isr;
    socp_compress_event_cb  register_Eventcb;
    socp_compress_read_cb   register_Readcb;
    socp_compress_enable    enable;
    socp_compress_disable   disable;
    socp_compress_set       set;
    socp_compress_getbuffer getbuffer;
    socp_compress_readdone  readdone;
    socp_compress_clear     clear;
}socp_compress_ops_stru;

#if (FEATURE_SOCP_DECODE_INT_TIMEOUT == FEATURE_ON)
/*201422214:23:11 l00258701 v711begin*/
typedef enum timeout_module
{
    DECODE_TIMEOUT_INT_TIMEOUT = 0,
    DECODE_TIMEOUT_DEC_INT_TIMEOUT = 1,
    DECODE_TIMEOUT_BUTTON = 2,

} DECODE_TIMEOUT_MODULE;

/*201422214:23:11 l00258701 v711end*/
#endif

typedef struct
{
    SOCP_VOTE_TYPE_ENUM_U32 type;
}socp_vote_req_stru;

typedef struct
{
    u32 vote_rst;   /* 1:1: */
}socp_vote_cnf_stru;

struct socp_enc_dst_log_cfg
{
    void*           pVirBuffer;      /* SOCPBUFFER324648 */
    unsigned long   ulPhyBufferAddr; /* SOCPBUFFER */
    unsigned int    BufferSize;      /* SOCPBUFFER */
    unsigned int    overTime;        /* NVE */
    unsigned int    logOnFlag;       /* buffer(SOCP_DST_CHAN_CFG_TYPE_ENUM) */
    unsigned int    ulCurTimeout;    /* SOCP */
    unsigned int    flushFlag;
	unsigned int    memLogCfg;
	unsigned int    currentMode;
    
};

/*****************************************************************************
*     : socp_init
*
*   : 
*
*   : 
*
*   : 
*
*     : 
*****************************************************************************/
s32 socp_init(void);

/*****************************************************************************
     : bsp_socp_coder_set_src_chan
   : SOCP
   : pSrcAttr:
             pSrcChanID:ID
   : 
     : SOCP_OK:
             SOCP_ERROR:
*****************************************************************************/
s32 bsp_socp_coder_set_src_chan(SOCP_CODER_SRC_ENUM_U32 enSrcChanID, SOCP_CODER_SRC_CHAN_S *pSrcAttr);

/*****************************************************************************
     : bsp_socp_coder_set_dest_chan_attr
   : 
   : u32DestChanID:SOCPID
             pDestAttr:SOCP
   : 
     : SOCP_OK:
             SOCP_ERROR:
*****************************************************************************/
s32 bsp_socp_coder_set_dest_chan_attr(u32 u32DestChanID, SOCP_CODER_DEST_CHAN_S *pDestAttr);

/*****************************************************************************
         : bsp_socp_decoder_set_dest_chan
   :SOCP
                
                
   : pAttr:
                         pDestChanID:ID
   : 
         : SOCP_OK:
                             SOCP_ERROR:
*****************************************************************************/
s32 bsp_socp_decoder_set_dest_chan(SOCP_DECODER_DST_ENUM_U32 enDestChanID, SOCP_DECODER_DEST_CHAN_STRU *pAttr);

/*****************************************************************************
         : bsp_socp_decoder_set_src_chan_attr
   :
   : u32SrcChanID:ID
                         pInputAttr:
   : 
         : SOCP_OK:
                             SOCP_ERROR:
*****************************************************************************/
s32 bsp_socp_decoder_set_src_chan_attr ( u32 u32SrcChanID,SOCP_DECODER_SRC_CHAN_STRU *pInputAttr);

/*****************************************************************************
         : bsp_socp_decoder_get_err_cnt
   :
   : u32ChanID:ID
                         pErrCnt:
   : 
         : SOCP_OK:
                             SOCP_ERROR:
*****************************************************************************/
s32 bsp_socp_decoder_get_err_cnt (u32 u32ChanID, SOCP_DECODER_ERROR_CNT_STRU *pErrCnt);

/*****************************************************************************
     : bsp_socp_free_channel
   : ID
   : u32ChanID:ID
   : 
     : SOCP_OK:
             SOCP_ERROR:
*****************************************************************************/
s32 bsp_socp_free_channel(u32 u32ChanID);

/*****************************************************************************
*     : socp_clean_encsrc_chan
*
*   : V9 SOCP
*
*   : enSrcChanID       
*
*   : 
*
*     : BSP_OK
*****************************************************************************/
u32 bsp_socp_clean_encsrc_chan(SOCP_CODER_SRC_ENUM_U32 enSrcChanID);

/*****************************************************************************
     : bsp_socp_register_event_cb
   : 
   : u32ChanID:ID
             EventCB:socp_event_cb
   : 
     : SOCP_OK:
             SOCP_ERROR:
*****************************************************************************/
s32 bsp_socp_register_event_cb(u32 u32ChanID, socp_event_cb EventCB);

/*****************************************************************************
     : bsp_socp_start
   : 
   : u32SrcChanID:ID
   : 
     : SOCP_OK:
             SOCP_ERROR:
*****************************************************************************/
s32 bsp_socp_start(u32 u32SrcChanID);

/*****************************************************************************
     : bsp_socp_stop
   : 
   : u32SrcChanID:ID
   : 
     : SOCP_OK:
             SOCP_ERROR:
*****************************************************************************/
s32 bsp_socp_stop(u32 u32SrcChanID);

/*****************************************************************************
         : bsp_socp_set_timeout
   :
   : u32Timeout:

   : 
         : SOCP_OK:
                             SOCP_ERROR:
*****************************************************************************/
s32 bsp_socp_set_timeout (SOCP_TIMEOUT_EN_ENUM_UIN32 eTmOutEn, u32 u32Timeout);

/*****************************************************************************
      : bsp_socp_set_dec_pkt_lgth
   :
   : pPktlgth:

   : 
         : SOCP_OK:
                    :
*****************************************************************************/
s32 bsp_socp_set_dec_pkt_lgth(SOCP_DEC_PKTLGTH_STRU *pPktlgth);

/*****************************************************************************
      : bsp_socp_set_debug
   :debug
   : u32ChanID:ID
                  u32DebugEn: debug
   : 
         : SOCP_OK:
                     :
*****************************************************************************/
s32 bsp_socp_set_debug(u32 u32DestChanID, u32 u32DebugEn);

/*****************************************************************************
         : bsp_socp_get_write_buff
   :buffer
   : u32SrcChanID:ID
                  pBuff:           :buffer

   : 
         : SOCP_OK:buffer
                             SOCP_ERROR:buffer
*****************************************************************************/
s32 bsp_socp_get_write_buff( u32 u32SrcChanID, SOCP_BUFFER_RW_STRU *pBuff);

/*****************************************************************************
         : bsp_socp_write_done
   :
   : u32SrcChanID:ID
                  u32WrtSize:   
   : 
         : SOCP_OK:
                             SOCP_ERROR:
*****************************************************************************/
s32 bsp_socp_write_done(u32 u32SrcChanID, u32 u32WrtSize);

/*****************************************************************************
         : bsp_socp_register_rd_cb
   :RD
   : u32SrcChanID:ID
                  RdCB:  
   : 
         : SOCP_OK:RD
                             SOCP_ERROR:RD
*****************************************************************************/
s32 bsp_socp_register_rd_cb(u32 u32SrcChanID, socp_rd_cb RdCB);

/*****************************************************************************
         : bsp_socp_get_rd_buffer
   :RD buffer
   : u32SrcChanID:ID
                  pBuff:  RD buffer
   : 
         : SOCP_OK:RD
                             SOCP_ERROR:RD
*****************************************************************************/
s32 bsp_socp_get_rd_buffer( u32 u32SrcChanID,SOCP_BUFFER_RW_STRU *pBuff);

/*****************************************************************************
         : bsp_socp_read_rd_done
   :SOCPRD buffer
   : u32SrcChanID:ID
                  u32RDSize:  RD buffer
   : 
         : SOCP_OK:RDbuffer
                             SOCP_ERROR:RDbuffer
*****************************************************************************/
s32 bsp_socp_read_rd_done(u32 u32SrcChanID, u32 u32RDSize);

/*****************************************************************************
         : bsp_socp_register_read_cb
   :
   : u32DestChanID:ID
                  ReadCB: 
   : 
         : SOCP_OK:
                             SOCP_ERROR:
*****************************************************************************/
s32 bsp_socp_register_read_cb( u32 u32DestChanID, socp_read_cb ReadCB);

/*****************************************************************************
         : bsp_socp_register_read_cb
   :
   : u32DestChanID:ID
                  ReadCB: buffer
   : 
         : SOCP_OK:
                             SOCP_ERROR:
*****************************************************************************/
s32 bsp_socp_get_read_buff(u32 u32DestChanID,SOCP_BUFFER_RW_STRU *pBuffer);

/*****************************************************************************
         : bsp_socp_read_data_done
   :SOCP
   : u32DestChanID:ID
                  u32ReadSize: 
   : 
         : SOCP_OK:
                             SOCP_ERROR:
*****************************************************************************/
s32 bsp_socp_read_data_done(u32 u32DestChanID,u32 u32ReadSize);

/*****************************************************************************
         : bsp_socp_set_bbp_enable
   :BBP
   : bEnable:ID
   : 
         : SOCP_OK:
                   :
*****************************************************************************/
s32 bsp_socp_set_bbp_enable(int bEnable);

/*****************************************************************************
         : bsp_socp_set_bbp_ds_mode
   :BBP DS
   : eDsMode:DS
   : 
         : SOCP_OK:
                   :
*****************************************************************************/
s32 bsp_socp_set_bbp_ds_mode(SOCP_BBP_DS_MODE_ENUM_UIN32 eDsMode);

/*****************************************************************************
*     : bsp_socp_get_state
*
*   : SOCP
*
*     : SOCP_IDLE    
*             SOCP_BUSY    
*****************************************************************************/
SOCP_STATE_ENUM_UINT32 bsp_socp_get_state(void);

s32 socp_init(void);

/*****************************************************************************
*     : bsp_socp_vote
*   : SOCPSOCPA
*   : id --- IDtype --- 
*   : 
*     : BSP_S32 0 --- 0xFFFFFFFF --- 
*****************************************************************************/
BSP_S32 bsp_socp_vote(SOCP_VOTE_ID_ENUM_U32 id, SOCP_VOTE_TYPE_ENUM_U32 type);

/*****************************************************************************
*     : bsp_socp_vote_to_mcore
*   : SOCPCLDSPSOCP
*   : type --- 
*   : 
*     : BSP_S32 0 --- 0xFFFFFFFF --- 
*****************************************************************************/
BSP_S32 bsp_socp_vote_to_mcore(SOCP_VOTE_TYPE_ENUM_U32 type);

/*****************************************************************************
*     : bsp_socp_get_log_cfg
*   : log
*   :
*   :
*     :
*****************************************************************************/
struct socp_enc_dst_log_cfg * bsp_socp_get_log_cfg(void);
/*****************************************************************************
*     : bsp_socp_get_sd_logcfg
*   : 
*   :
*   :
*     :
*****************************************************************************/
u32 bsp_socp_get_sd_logcfg(SOCP_ENC_DST_BUF_LOG_CFG_STRU* cfg);
/*****************************************************************************
*     : socp_set_clk_autodiv_enable
*   : clkclk_disable_unpreparebypass0
*   : 
*   : 
*     : 
*       :
              clk_prepare_enable  clk_disable_unprepare 
              clk
               clk_prepare_enable  clk_disable_unprepare 
*****************************************************************************/
void bsp_socp_set_clk_autodiv_enable(void);

/*****************************************************************************
*     : socp_set_clk_autodiv_disable
*   : clkclk_prepare_enablebypass1
*   : 
*   : 
*     : 
*       :
              clk_prepare_enable  clk_disable_unprepare 
              clk
               clk_prepare_enable  clk_disable_unprepare 
*****************************************************************************/
void bsp_socp_set_clk_autodiv_disable(void);


#if (FEATURE_SOCP_DECODE_INT_TIMEOUT == FEATURE_ON)
/*****************************************************************************
*     : bsp_socp_set_decode_timeout_register
*   :
*   : 
*   : 
*     :
*****************************************************************************/
s32 bsp_socp_set_decode_timeout_register(DECODE_TIMEOUT_MODULE module);
#endif
/*****************************************************************************
*     : bsp_socp_set_enc_dst_threshold
*   :
*   :
*   :
*     :
*****************************************************************************/
void bsp_socp_set_enc_dst_threshold(bool mode,u32 u32DestChanID);

/*****************************************************************************
*     : bsp_socp_set_ind_mode
*
*   : 
*
*   : 
*
*   : 
*
*     : BSP_S32 BSP_OK: BSP_ERROR:
*****************************************************************************/
s32 bsp_socp_set_ind_mode(SOCP_IND_MODE_ENUM eMode);


/*****************************************************************************
     : mdrv_socp_modify_write_read_ptr
   : 
   : ulSrcChanId:ID
             
   : 
     : 
*****************************************************************************/
void bsp_socp_modify_write_read_ptr(u32 ulSrcChanId);


#ifdef CONFIG_DEFLATE
s32 bsp_socp_compress_enable(u32 u32DestChanID);

s32 bsp_socp_compress_disable(u32 u32DestChanID);

s32 bsp_socp_register_compress(socp_compress_ops_stru *ops);
#endif
#ifdef __cplusplus
}
#endif

#endif /* end of _BSP_SOCP_H*/


