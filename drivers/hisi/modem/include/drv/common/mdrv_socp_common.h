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

#ifndef __MDRV_SOCP_COMMON_H__
#define __MDRV_SOCP_COMMON_H__
#ifdef __cplusplus
extern "C"
{
#endif

#include <product_config.h>

/**************************************************************************
  
**************************************************************************/
#define SOCP_CODER_SRC_CHAN                 0x00
#define SOCP_CODER_DEST_CHAN                0x01
#define SOCP_DECODER_SRC_CHAN               0x02
#define SOCP_DECODER_DEST_CHAN              0x03


#define SOCP_CHAN_DEF(chan_type, chan_id)   ((chan_type<<16)|chan_id)
#define SOCP_REAL_CHAN_ID(unique_chan_id)   (unique_chan_id & 0xFFFF)
#define SOCP_REAL_CHAN_TYPE(unique_chan_id) (unique_chan_id>>16)

/* ID */
/* soc_socp_adapter.h enum SOCP_CODER_SRC_ENUM */
typedef unsigned int SOCP_CODER_SRC_ENUM_U32;

/*ID*/
enum SOCP_DECODER_SRC_ENUM
{
    SOCP_DECODER_SRC_LOM        = SOCP_CHAN_DEF(SOCP_DECODER_SRC_CHAN,0),   /* LTE OM */
    SOCP_DECODER_SRC_HDLC_AT    = SOCP_CHAN_DEF(SOCP_DECODER_SRC_CHAN,1),   /* HDLCAT */
    SOCP_DECODER_SRC_GUOM       = SOCP_CHAN_DEF(SOCP_DECODER_SRC_CHAN,2),   /* GU OM */
    SOCP_DECODER_SRC_RFU        = SOCP_CHAN_DEF(SOCP_DECODER_SRC_CHAN,3),   /*  */
    SOCP_DECODER_SRC_BUTT
};
typedef unsigned int SOCP_DECODER_SRC_ENUM_U32;

/*ID*/
enum SOCP_CODER_DST_ENUM
    {
    SOCP_CODER_DST_OM_CNF        = SOCP_CHAN_DEF(SOCP_CODER_DEST_CHAN,0), /* LTE OM */
    SOCP_CODER_DST_OM_IND        = SOCP_CHAN_DEF(SOCP_CODER_DEST_CHAN,1), /* LTE OM */
    SOCP_CODER_DST_HDLC_AT       = SOCP_CHAN_DEF(SOCP_CODER_DEST_CHAN,2), /* AT */
    SOCP_CODER_DST_RFU0          = SOCP_CHAN_DEF(SOCP_CODER_DEST_CHAN,3), /* GU OM */
    SOCP_CODER_DST_RFU1          = SOCP_CHAN_DEF(SOCP_CODER_DEST_CHAN,4), /*  */
    SOCP_CODER_DST_RFU2          = SOCP_CHAN_DEF(SOCP_CODER_DEST_CHAN,5), /*  */
    SOCP_CODER_DST_RFU3          = SOCP_CHAN_DEF(SOCP_CODER_DEST_CHAN,6), /*  */
    SOCP_CODER_DST_BUTT
};
typedef unsigned int SOCP_CODER_DST_ENUM_U32;

/*ID*/
enum SOCP_DECODER_DST_ENUM
    {
    SOCP_DECODER_DST_LOM        = SOCP_CHAN_DEF(SOCP_DECODER_DEST_CHAN,0),  /* LTE OM */
    SOCP_DECODER_DST_HDLC_AT    = SOCP_CHAN_DEF(SOCP_DECODER_DEST_CHAN,1),  /* HDLCAT */
    SOCP_DECODER_DST_GUOM       = SOCP_CHAN_DEF(SOCP_DECODER_DEST_CHAN,2),  /* GU OM */
    SOCP_DECODER_DST_RFU        = SOCP_CHAN_DEF(SOCP_DECODER_DEST_CHAN,3),  /*  */
    SOCP_DECODER_CBT            = SOCP_CHAN_DEF(SOCP_DECODER_DEST_CHAN,16), /* GU CBT */
    SOCP_DECODER_DST_BUTT
};
typedef unsigned int SOCP_DECODER_DST_ENUM_U32;

#define SOCP_CODER_SRC_CHAN_BASE            0x00000000
#define SOCP_CODER_DEST_CHAN_BASE           0x00010000
#define SOCP_DECODER_SRC_CHAN_BASE          0x00020000
#define SOCP_DECODER_DEST_CHAN_BASE         0x00030000

/**************************************************************************
  
**************************************************************************/
/* SCMV9 begin */
enum SOCP_BD_TYPE_ENUM
{
    SOCP_BD_DATA            = 0,    /* SOCP BD */
    SOCP_BD_LIST            = 1,    /* SOCP BD */
    SOCP_BD_BUTT
};
typedef unsigned short SOCP_BD_TYPE_ENUM_UINT16;

enum SOCP_HDLC_FLAG_ENUM
    {
    SOCP_HDLC_ENABLE         = 0,    /* HDLC */
    SOCP_HDLC_DISABLE        = 1,    /* HDLC */
    SOCP_HDLC_FLAG_BUTT
};

enum SOCP_STATE_ENUM
    {
    SOCP_IDLE               = 0,    /* SOCP */
    SOCP_BUSY,                      /* SOCP */
    SOCP_UNKNOWN_BUTT              /*   */
};
typedef unsigned int SOCP_STATE_ENUM_UINT32;

/* */
enum SCM_DATA_TYPE_ENUM
    {
    SCM_DATA_TYPE_TL            = 0,            /* LTE OAM */
    SCM_DATA_TYPE_GU,                           /* GU OAM */
    SCM_DATA_TYPE_BUTT
};
typedef unsigned  char SOCP_DATA_TYPE_ENUM_UIN8;

/*SOCPBD*/
typedef struct
{
#ifdef FEATURE_SOCP_ADDR_64BITS
    unsigned long                      ulDataAddr;     /*  */
    unsigned short                     usMsgLen;       /*  */
    unsigned short                     enDataType;     /*  */
    unsigned int                       reservd;
#else
    unsigned int                      ulDataAddr;       /*  */
    unsigned short                    usMsgLen;         /*  */
    unsigned short                    enDataType;       /*  */
#endif
}SOCP_BD_DATA_STRU;

/*SOCPRD*/
typedef struct
{
#ifdef FEATURE_SOCP_ADDR_64BITS
    unsigned long                      ulDataAddr;      /*  */
    unsigned short                     usMsgLen;        /**/
    unsigned short                     enDataType;      /**/
    unsigned int                       reservd;
#else
    unsigned int                       ulDataAddr;      /*  */
    unsigned short                     usMsgLen;        /**/
    unsigned short                     enDataType;      /**/
#endif
}SOCP_RD_DATA_STRU;
/* SCMV9 end */

enum tagSOCP_EVENT_E
{
        SOCP_EVENT_PKT_HEADER_ERROR         = 0x1,    /* "HISI" */
        SOCP_EVENT_OUTBUFFER_OVERFLOW       = 0x2,    /* buffer */
        SOCP_EVENT_RDBUFFER_OVERFLOW        = 0x4,    /* RDbuffer */
        SOCP_EVENT_DECODER_UNDERFLOW        = 0x8,    /* buffer */
        SOCP_EVENT_PKT_LENGTH_ERROR         = 0x10,   /*  */
        SOCP_EVENT_CRC_ERROR                = 0x20,   /* CRC */
        SOCP_EVENT_DATA_TYPE_ERROR          = 0x40,   /* */
        SOCP_EVENT_HDLC_HEADER_ERROR        = 0x80,   /* HDLC */
        SOCP_EVENT_OUTBUFFER_THRESHOLD_OVERFLOW = 0x100, /* buffer */
        SOCP_EVENT_BUTT
};
typedef unsigned int SOCP_EVENT_ENUM_UIN32;

/*  */
enum tagSOCP_ENCSRC_CHNMODE_E
{
    SOCP_ENCSRC_CHNMODE_CTSPACKET       = 0,    /*  */
    SOCP_ENCSRC_CHNMODE_FIXPACKET,              /*  */
    SOCP_ENCSRC_CHNMODE_LIST,                   /*  */
    SOCP_ENCSRC_CHNMODE_BUTT
};
typedef unsigned int SOCP_ENCSRC_CHNMODE_ENUM_UIN32;

/*  */
enum tagSOCP_DECSRC_CHNMODE_E
{
    SOCP_DECSRC_CHNMODE_BYTES        = 0,       /*  */
    SOCP_DECSRC_CHNMODE_LIST,                   /*  */
    SOCP_DECSRC_CHNMODE_BUTT
};
typedef unsigned int SOCP_DECSRC_CHNMODE_ENUM_UIN32;

/* SOCP_TIMEOUT_DECODE_TRF */
/* 201422215:34:11 l00258701 modify add */
enum tagSOCP_TIMEOUT_EN_E
{
    SOCP_TIMEOUT_BUFOVF_DISABLE        = 0,       /* buffer */
    SOCP_TIMEOUT_BUFOVF_ENABLE,                   /* buffer */
    SOCP_TIMEOUT_TRF,                             /*  */
    SOCP_TIMEOUT_DECODE_TRF,                      /*  */
    SOCP_TIMEOUT_BUTT
};
typedef unsigned int SOCP_TIMEOUT_EN_ENUM_UIN32;

/* */
enum tagSOCP_CHAN_PRIORITY_E
{
    SOCP_CHAN_PRIORITY_0     = 0,               /* */
    SOCP_CHAN_PRIORITY_1,                       /* */
    SOCP_CHAN_PRIORITY_2,                       /* */
    SOCP_CHAN_PRIORITY_3,                       /* */
    SOCP_CHAN_PRIORITY_BUTT
};
typedef unsigned int SOCP_CHAN_PRIORITY_ENUM_UIN32;

/* */
enum tagSOCP_DATA_TYPE_E
{
    SOCP_DATA_TYPE_0            = 0,            /* LTE OAM */
    SOCP_DATA_TYPE_1,                           /* GU OAM */
    SOCP_DATA_TYPE_2,                           /*  */
    SOCP_DATA_TYPE_3,                           /*  */
    SOCP_DATA_TYPE_BUTT
};
typedef unsigned int SOCP_DATA_TYPE_ENUM_UIN32;


/* BBP  */
enum tagSOCP_BBP_DS_MODE_E
{
    SOCP_BBP_DS_MODE_DROP           = 0,        /*  */
    SOCP_BBP_DS_MODE_OVERRIDE,                  /*  */
    SOCP_BBP_DS_MODE_BUTT
};
typedef unsigned int SOCP_BBP_DS_MODE_ENUM_UIN32;

/* data type  */
enum tagSOCP_DATA_TYPE_EN_E
{
    SOCP_DATA_TYPE_EN           = 0,        /* data type  */
    SOCP_DATA_TYPE_DIS,                     /* data type  */
    SOCP_DATA_TYPE_EN_BUTT
};
typedef unsigned int SOCP_DATA_TYPE_EN_ENUM_UIN32;

/* debug  */
enum tagSOCP_ENC_DEBUG_EN_E
{
    SOCP_ENC_DEBUG_DIS          = 0,       /* debug  */
    SOCP_ENC_DEBUG_EN,                     /* debug  */
    SOCP_ENC_DEBUG_EN_BUTT
};
typedef unsigned int SOCP_ENC_DEBUG_EN_ENUM_UIN32;

typedef enum
{
    SOCP_DST_CHAN_NOT_CFG = 0,
    SOCP_DST_CHAN_DELAY,        /* buffer */
    SOCP_DST_CHAN_DTS           /* DTSbuffer */
} SOCP_DST_CHAN_CFG_TYPE_ENUM;

/*  */
typedef struct tagSOCP_DEC_PKTLGTH_S
{
    unsigned int             u32PktMax;         /**/
    unsigned int             u32PktMin;         /**/
}SOCP_DEC_PKTLGTH_STRU;


/* buffer*/
typedef struct
{
    unsigned  char                 *pucInputStart;      /* */
    unsigned  char                 *pucInputEnd;        /* */
    unsigned  char                 *pucRDStart;         /* RD buffer*/
    unsigned  char                 *pucRDEnd;           /* RD buffer*/
    unsigned int                 u32RDThreshold;     /* RD buffer*/
    unsigned int                 ulRsv;              /* reserve */
}SOCP_SRC_SETBUF_STRU;

/* buffer*/
typedef struct
{
    unsigned  char                 *pucOutputStart;     /* */
    unsigned  char                 *pucOutputEnd;       /* */
    unsigned int                 u32Threshold;       /*  */
    unsigned int                 ulRsv;              /* reserve */
}SOCP_DST_SETBUF_STRU;

/* */
typedef struct tagSOCP_CODER_SRC_CHAN_S
{
    unsigned int                         u32DestChanID;      /* ID*/
    unsigned int                         u32BypassEn;        /* bypass*/
    SOCP_DATA_TYPE_ENUM_UIN32        eDataType;          /* */
    SOCP_DATA_TYPE_EN_ENUM_UIN32     eDataTypeEn;        /* */
    SOCP_ENC_DEBUG_EN_ENUM_UIN32     eDebugEn;           /* */
    SOCP_ENCSRC_CHNMODE_ENUM_UIN32   eMode;              /* */
    SOCP_CHAN_PRIORITY_ENUM_UIN32    ePriority;          /* */
    SOCP_SRC_SETBUF_STRU            sCoderSetSrcBuf;
}SOCP_CODER_SRC_CHAN_S;

/* */
typedef struct tagSOCP_CODER_DEST_CHAN_S
{
    unsigned int                 u32EncDstThrh;     /* */
    SOCP_DST_SETBUF_STRU       sCoderSetDstBuf;
}SOCP_CODER_DEST_CHAN_S;

/* */
typedef struct tagSOCP_DECODER_SRC_CHAN_S
{
    SOCP_DATA_TYPE_EN_ENUM_UIN32     eDataTypeEn;        /* */
    SOCP_DECSRC_CHNMODE_ENUM_UIN32   eMode;              /* */
    SOCP_SRC_SETBUF_STRU       sDecoderSetSrcBuf;
}SOCP_DECODER_SRC_CHAN_STRU;

/* */
typedef struct tagSOCP_DECODER_DEST_CHAN_S
{
    unsigned int                 u32SrcChanID;       /* ID*/
    SOCP_DATA_TYPE_ENUM_UIN32        eDataType;          /* */
    SOCP_DST_SETBUF_STRU       sDecoderDstSetBuf;
}SOCP_DECODER_DEST_CHAN_STRU;

/* buffer*/
typedef struct tagSOCP_BUFFER_RW_S
{
    char    *pBuffer;                        /* buffer*/
    char    *pRbBuffer;                      /* buffer*/
    unsigned int     u32Size;                        /* buffer*/
    unsigned int     u32RbSize;                      /* buffer*/
}SOCP_BUFFER_RW_STRU;

/* */
typedef struct tagSOCP_DECODER_ERROR_CNT_S
{
    unsigned int     u32PktlengthCnt;                /* */
    unsigned int     u32CrcCnt;                      /* CRC*/
    unsigned int     u32DataTypeCnt;                 /* */
    unsigned int     u32HdlcHeaderCnt;               /* 0x7E*/
}SOCP_DECODER_ERROR_CNT_STRU;

/*  */
typedef struct tagSOCP_ENCSRC_RSVCHN_SCOPE_S
{
    unsigned int                 u32RsvIDMin;        /*ID*/
    unsigned int                 u32RsvIDMax;        /*ID*/
}SOCP_ENCSRC_RSVCHN_SCOPE_STRU;

/* SOCP */
enum SOCP_VOTE_ID_ENUM
{
    SOCP_VOTE_GU_DSP,       /* GU DSP */
    SOCP_VOTE_DIAG_APP,     /* DIAG APP,DRV APP */
    SOCP_VOTE_DIAG_COMM,    /* DIAG COMM,LDSPDRV COMM */
    SOCP_VOTE_TL_DSP,       /* TL DSP*/
    SOCP_VOTE_SOCP_REG,     /* SOCP*/
    SOCP_VOTE_ID_BUTT
};
typedef unsigned int SOCP_VOTE_ID_ENUM_U32;

/* SOCP */
enum SOCP_VOTE_TYPE_ENUM
{
    SOCP_VOTE_FOR_SLEEP,    /*  */
    SOCP_VOTE_FOR_WAKE,     /*  */
    SOCP_VOTE_TYPE_BUTT
};
typedef unsigned int SOCP_VOTE_TYPE_ENUM_U32;

typedef int (*socp_event_cb)(unsigned int u32ChanID, SOCP_EVENT_ENUM_UIN32 u32Event, unsigned int u32Param);
typedef int (*socp_read_cb)(unsigned int u32ChanID);
typedef int (*socp_rd_cb)(unsigned int u32ChanID);

/* log2.0 2014-03-19 Begin:*/
typedef struct SOCP_ENC_DST_BUF_LOG_CFG
{
    void*           pVirBuffer;      /* SOCPBUFFER324648 */
    unsigned long   ulPhyBufferAddr; /* SOCPBUFFER */
    unsigned int    BufferSize;      /* SOCPBUFFER */
    unsigned int    overTime;        /* NVE */
    unsigned int    logOnFlag;       /* buffer(SOCP_DST_CHAN_CFG_TYPE_ENUM) */
    unsigned int    ulCurTimeout;    /* SOCP */
} SOCP_ENC_DST_BUF_LOG_CFG_STRU;
/* log2.0 2014-03-19 End*/

#define INNER_LOG_DATA_MAX                   0x40

typedef struct
{
    unsigned int                  ulSlice;
    unsigned int                  ulFileNO;
    signed int                   lLineNO;
    unsigned int                  ulP1;
    unsigned int                  ulP2;
}INNER_LOG_RECORD_STRU;

typedef struct
{
    unsigned int                  ulCnt;
    INNER_LOG_RECORD_STRU       astLogData[INNER_LOG_DATA_MAX];
}INNER_LOG_DATA_STRU;

typedef  enum
{
   SOCP_IND_MODE_DIRECT,
   SOCP_IND_MODE_DELAY,
   SOCP_IND_MODE_CYCLE
}SOCP_IND_MODE_ENUM;
/**************************************************************************
  
**************************************************************************/
/*****************************************************************************
*   : 
*
*   : 
*
*     : 
*****************************************************************************/
int DRV_SOCP_INIT(void);

/*****************************************************************************
    : mdrv_socp_corder_set_src_chan
  : SOCP
  : pSrcAttr:
     pSrcChanID:ID
*    : 
*      : SOCP_OK:     
*              SOCP_ERROR:  
*****************************************************************************/
int mdrv_socp_corder_set_src_chan(SOCP_CODER_SRC_ENUM_U32 enSrcChanID, SOCP_CODER_SRC_CHAN_S *pSrcAttr);

/*****************************************************************************
*      : mdrv_socp_coder_set_dest_chan_attr
*    : 
*    : u32DestChanID:   SOCPID
*                  pDestAttr:   SOCP
*    : 
*      : SOCP_OK:      
*              SOCP_ERROR:   
******************************************************************************/
int mdrv_socp_coder_set_dest_chan_attr(unsigned int u32DestChanID, SOCP_CODER_DEST_CHAN_S *pDestAttr);

/*****************************************************************************
*      : mdrv_socp_decoder_set_dest_chan
*    : SOCP
*              
*              
  : pAttr:
     pDestChanID:ID
  : 
    : SOCP_OK:
     SOCP_ERROR:
*****************************************************************************/
int DRV_SOCP_DECODER_SET_DEST_CHAN(SOCP_DECODER_DST_ENUM_U32 enDestChanID, SOCP_DECODER_DEST_CHAN_STRU *pAttr);

/*****************************************************************************
    : DRV_SOCP_DECODER_SET_SRC_CHAN_ATTR
  : 
  : u32SrcChanID:ID
     pInputAttr:
  : 
    : SOCP_OK:
     SOCP_ERROR:
*****************************************************************************/
int DRV_SOCP_DECODER_SET_SRC_CHAN_ATTR ( unsigned int u32SrcChanID,SOCP_DECODER_SRC_CHAN_STRU *pInputAttr);

/*****************************************************************************
    : DRV_SOCP_DECODER_GET_ERR_CNT
  :
  : u32ChanID:ID
                 pErrCnt:
  : 
        : SOCP_OK:
                     SOCP_ERROR:
*****************************************************************************/
int DRV_SOCP_DECODER_GET_ERR_CNT (unsigned int u32ChanID, SOCP_DECODER_ERROR_CNT_STRU *pErrCnt);

/*****************************************************************************
    : DRV_SOCP_FREE_CHANNEL
  : ID
  : u32ChanID:ID
  : 
    : SOCP_OK:
     SOCP_ERROR:
*****************************************************************************/
int DRV_SOCP_FREE_CHANNEL(unsigned int u32ChanID);

/*****************************************************************************
*     : DRV_SOCP_CLEAN_ENCSRC_CHAN
*
*   : V9 SOCP
*
*   : enSrcChanID       
*
*   : 
*
*     : BSP_OK
*****************************************************************************/
unsigned int DRV_SOCP_CLEAN_ENCSRC_CHAN(SOCP_CODER_SRC_ENUM_U32 enSrcChanID);
#define SOCP_CleanEncSrcChan(enSrcChanID)  DRV_SOCP_CLEAN_ENCSRC_CHAN(enSrcChanID)

/*****************************************************************************
    : DRV_SOCP_REGISTER_EVENT_CB
  : 
  : u32ChanID:ID
     EventCB:socp_event_cb
  : 
    : SOCP_OK:
     SOCP_ERROR:
*****************************************************************************/
int DRV_SOCP_REGISTER_EVENT_CB(unsigned int u32ChanID, socp_event_cb EventCB);

/*****************************************************************************
    : mdrv_socp_start
  : 
  : u32SrcChanID:ID
  : 
    : SOCP_OK:
      SOCP_ERROR:
*****************************************************************************/
int mdrv_socp_start(unsigned int u32SrcChanID);

/*****************************************************************************
    : mdrv_socp_stop
  : 
  : u32SrcChanID:ID
  : 
    : SOCP_OK:
     SOCP_ERROR:
*****************************************************************************/
int mdrv_socp_stop(unsigned int u32SrcChanID);
static inline void SOCP_Stop1SrcChan(unsigned int u32SrcChanID)
{
    (void)mdrv_socp_stop(u32SrcChanID);
}

/*****************************************************************************
    : DRV_SOCP_SET_TIMEOUT
  : 
  : u32Timeout:

  : 
    : SOCP_OK:
     SOCP_ERROR:
*****************************************************************************/
int DRV_SOCP_SET_TIMEOUT (SOCP_TIMEOUT_EN_ENUM_UIN32 eTmOutEn, unsigned int u32Timeout);

/*****************************************************************************
    : DRV_SOCP_SET_DEC_PKT_LGTH
  : 
  : pPktlgth:

  : 
    : SOCP_OK:
     :
*****************************************************************************/
int DRV_SOCP_SET_DEC_PKT_LGTH(SOCP_DEC_PKTLGTH_STRU *pPktlgth);

/*****************************************************************************
    : DRV_SOCP_SET_DEBUG
  : debug
  : u32ChanID:ID
     u32DebugEn: debug
  : 
    : SOCP_OK:
     :
*****************************************************************************/
int DRV_SOCP_SET_DEBUG(unsigned int u32DestChanID, unsigned int u32DebugEn);

/*****************************************************************************
    : DRV_SOCP_CHAN_SOFT_RESET
  : 
  : u32ChanID:ID
  : 
    : SOCP_OK:
     :
*****************************************************************************/
int DRV_SOCP_CHAN_SOFT_RESET(unsigned int u32ChanID);

/*****************************************************************************
    : mdrv_socp_get_write_buff
  : buffer
  : u32SrcChanID:ID
     pBuff:           :buffer

  : 
    : SOCP_OK:buffer
     SOCP_ERROR:buffer
*****************************************************************************/
int mdrv_socp_get_write_buff( unsigned int u32SrcChanID, SOCP_BUFFER_RW_STRU *pBuff);

/*****************************************************************************
    : mdrv_socp_write_done
  : 
  : u32SrcChanID:ID
     u32WrtSize:   
  : 
    : SOCP_OK:
       SOCP_ERROR:
*****************************************************************************/
int mdrv_socp_write_done(unsigned int u32SrcChanID, unsigned int u32WrtSize);

/*****************************************************************************
    : mdrv_socp_register_rd_cb
  : RD
  : u32SrcChanID:ID
     RdCB:  
  : 
    : SOCP_OK:RD
     SOCP_ERROR:RD
*****************************************************************************/
int DRV_SOCP_REGISTER_RD_CB(unsigned int u32SrcChanID, socp_rd_cb RdCB);

/*****************************************************************************
    : mdrv_socp_get_rd_buffer
  : RD buffer
  : u32SrcChanID:ID
     pBuff:  RD buffer
  : 
    : SOCP_OK:RD
     SOCP_ERROR:RD
*****************************************************************************/
int mdrv_socp_get_rd_buffer( unsigned int u32SrcChanID,SOCP_BUFFER_RW_STRU *pBuff);


/*****************************************************************************
    : bsp_socp_read_rd_done
  : SOCPRD buffer
  : u32SrcChanID:ID
      u32RDSize:  RD buffer
  : 
    : SOCP_OK:RDbuffer
      SOCP_ERROR:RDbuffer
*****************************************************************************/
int mdrv_socp_read_rd_done(unsigned int u32SrcChanID, unsigned int u32RDSize);

/*****************************************************************************
    : bsp_socp_register_read_cb
  : 
  : u32DestChanID:ID
     ReadCB: 
  : 
    : SOCP_OK:
     SOCP_ERROR:
*****************************************************************************/
int DRV_SOCP_REGISTER_READ_CB( unsigned int u32DestChanID, socp_read_cb ReadCB);
#define BSP_SOCP_RegisterReadCB(u32DestChanID,ReadCB)  \
    DRV_SOCP_REGISTER_READ_CB(u32DestChanID,ReadCB)

/*****************************************************************************
    : DRV_SOCP_GET_READ_BUFF
  : 
  : u32DestChanID:ID
     ReadCB: buffer
  : 
    : SOCP_OK:
     SOCP_ERROR:
*****************************************************************************/
int DRV_SOCP_GET_READ_BUFF(unsigned int u32DestChanID,SOCP_BUFFER_RW_STRU *pBuffer);
#define BSP_SOCP_GetReadBuff(u32SrcChanID,pBuff)  \
        DRV_SOCP_GET_READ_BUFF(u32SrcChanID,pBuff)

/*****************************************************************************
    : DRV_SOCP_READ_DATA_DONE
  : SOCP
  : u32DestChanID:ID
     u32ReadSize: 
  : 
    : SOCP_OK:
     SOCP_ERROR:
*****************************************************************************/
int DRV_SOCP_READ_DATA_DONE(unsigned int u32DestChanID,unsigned int u32ReadSize);
#define BSP_SOCP_ReadDataDone(u32DestChanID,u32ReadSize) \
        DRV_SOCP_READ_DATA_DONE(u32DestChanID,u32ReadSize)

/*****************************************************************************
    : DRV_SOCP_SET_BBP_ENABLE
  : BBP
  : bEnable:ID
  : 
        : SOCP_OK:
           :
*****************************************************************************/
int DRV_SOCP_SET_BBP_ENABLE(int bEnable);

/*****************************************************************************
    : DRV_SOCP_SET_BBP_DS_MODE
  : BBP DS
  : eDsMode:DS
  : 
        : SOCP_OK:
           :
*****************************************************************************/
int DRV_SOCP_SET_BBP_DS_MODE(SOCP_BBP_DS_MODE_ENUM_UIN32 eDsMode);

/*****************************************************************************
*     : DRV_SOCP_DSPCHN_START
*   : enable DSP channel
*   :
*   : 
*     :
*****************************************************************************/
void  DRV_SOCP_DSPCHN_START(void);


/*****************************************************************************
*     : DRV_SOCP_DSPCHN_STOP
*   : disable DSP channel
*   :
*   : 
*     :
*****************************************************************************/
void  DRV_SOCP_DSPCHN_STOP(void);

/*****************************************************************************
*     : DRV_SOCP_GET_STATE
*
*   : SOCP
*
*     : SOCP_IDLE    
*             SOCP_BUSY    
*****************************************************************************/
SOCP_STATE_ENUM_UINT32  DRV_SOCP_GET_STATE(void);

/*****************************************************************************
*     : DRV_BBPDMA_DRX_BAK_REG
*   : BBPDMA
*   :
*   : 
*     :
*****************************************************************************/
int  DRV_BBPDMA_DRX_BAK_REG(void);

/*****************************************************************************
*     : DRV_BBPDMA_DRX_RESTORE_REG
*   : BBPDMA
*   :
*   : 
*     :
*****************************************************************************/
int  DRV_BBPDMA_DRX_RESTORE_REG(void);

/*****************************************************************************
*     : mdrv_socp_get_sd_logcfg
*   : LOG2.0 SOCP
*   : 
*   : 
*     : SOCP_ENC_DST_BUF_LOG_CFG_STRU
*****************************************************************************/
unsigned int mdrv_socp_get_sd_logcfg(SOCP_ENC_DST_BUF_LOG_CFG_STRU* cfg);
/*****************************************************************************
*     : mdrv_socp_set_ind_mode
*
*   : 
*
*   : 
*
*   : 
*
*     : BSP_S32 BSP_OK: BSP_ERROR:
*****************************************************************************/
int mdrv_socp_set_ind_mode(SOCP_IND_MODE_ENUM eMode);

unsigned int  DRV_SOCP_INIT_LTE_DSP(unsigned int ulChanId,unsigned int ulPhyAddr,unsigned int ulSize);

unsigned int  DRV_SOCP_INIT_LTE_BBP_LOG(unsigned int ulChanId,unsigned int ulPhyAddr,unsigned int ulSize);

unsigned int  DRV_SOCP_INIT_LTE_BBP_DS(unsigned int ulChanId,unsigned int ulPhyAddr,unsigned int ulSize);

void DRV_SOCP_ENABLE_LTE_BBP_DSP(unsigned int ulChanId);

void BSP_SOCP_RefreshSDLogCfg(unsigned int ulTimerLen);

/*****************************************************************************
*     : mdrv_socp_set_autodiv_enalbe
*
*   : SOCP
*
*   : 
*
*   : 
*
*     : 
*****************************************************************************/
void mdrv_socp_enalbe_dfs(void);

/*****************************************************************************
*     : mdrv_socp_set_autodiv_disalbe
*
*   : SOCP
*
*   : 
*
*   : 
*
*     : 
*****************************************************************************/
void mdrv_socp_disalbe_dfs(void);

/*****************************************************************************
*     : DRV_SOCP_VOTE
*   : SOCPSOCPA
*   : id --- IDtype --- 
*   : 
*     : int 0 --- 0xFFFFFFFF --- 
*****************************************************************************/
int DRV_SOCP_VOTE(SOCP_VOTE_ID_ENUM_U32 id, SOCP_VOTE_TYPE_ENUM_U32 type);

/*****************************************************************************
*     : DRV_SOCP_VOTE_TO_MCORE
*   : SOCPCLDSPSOCP
*   : type --- 
*   : 
*     : int 0 --- 0xFFFFFFFF --- 
*****************************************************************************/
int DRV_SOCP_VOTE_TO_MCORE(SOCP_VOTE_TYPE_ENUM_U32 type);



#ifdef __cplusplus
}
#endif
#endif //__MDRV_SOCP_COMMON_H__
