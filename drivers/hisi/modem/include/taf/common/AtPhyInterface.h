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

#ifndef __ATPHYINTERFACE_H__
#define __ATPHYINTERFACE_H__

/*****************************************************************************
  1 
*****************************************************************************/

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "vos.h"

#pragma pack(4)

/*****************************************************************************
  2 
*****************************************************************************/

#define W_AFC_INIT_VALUE                (0x959)           /* W_AFC */

#define WDSP_CTRL_TX_OFF                 2       /*DSPRF*/
#define WDSP_CTRL_TX_ON                  3       /*DSPRF*/

#define WDSP_CTRL_TX_ONE_TONE            8       /*  */
#define WDSP_CTRL_TX_TWO_TONE            9       /*  */

#define GDSP_CTRL_TX_OFF                0xAAAA   /*DSPRF*/
#define GDSP_CTRL_TX_ON                 0x5555   /*DSPRF*/

#define WDSP_MAX_TX_AGC                 2047
#define GDSP_MAX_TX_VPA                 1023

#define BBP_PA_HIGH_MODE                1       /*PA*/
#define BBP_PA_MID_MODE                 2       /*PA*/
#define BBP_PA_LOW_MODE                 3       /*PA*/
#define BBP_PA_AUTO_MODE                0       /*PA*/

#define DSP_CTRL_RX_OFF                2       /*CPU*/
#define DSP_CTRL_RX_ANT1_ON            3       /*CPU,1*/
#define DSP_CTRL_RX_ALL_ANT_ON         7       /*CPU,12 */

#define DSP_LNA_HIGH_GAIN_MODE          (0x2)     /* DSPLNA */
#define DSP_LNA_LOW_GAIN_MODE           (0x1)     /* DSPLNA */
#define DSP_LNA_NO_CTRL_GAIN_MODE       (0x0)     /* WBBPLNA, */

#define AT_GDSP_AGC_GAIN1_75DB          (0)      /*GDSP AGC,0*/
#define AT_GDSP_AGC_GAIN2_63DB          (1)      /*GDSP AGC,1*/
#define AT_GDSP_AGC_GAIN3_43DB          (2)      /*GDSP AGC,2*/
#define AT_GDSP_AGC_GAIN4_23DB          (3)      /*GDSP AGC,3*/


#define AT_GDSP_RX_MODE_BURST           (0)      /**/
#define AT_GDSP_RX_MODE_CONTINOUS_BURST (1)      /**/
#define AT_GDSP_RX_MODE_STOP            (2)      /**/


#define AT_GDSP_RX_SLOW_AGC_MODE        (0)      /*Slow AGC*/
#define AT_GDSP_RX_FAST_AGC_MODE        (1)      /*fast AGC*/

#define AT_DSP_RF_AGC_STATE_ERROR       (-1)     /*-1 */

#define AT_DSP_RSSI_MEASURE_NUM         (1)      /*RSSI*/
#define AT_DSP_RSSI_MEASURE_INTERVAL    (0)      /*RSSIms */
#define AT_DSP_RSSI_VALUE_UINT          (0.125)  /*RSSI0.125dBm*/
#define AT_DSP_RSSI_VALUE_MUL_THOUSAND  (125)    /*RSSI,0.125dBm*1000*/

/*tyg*/
#define AT_DPS_NOISERSSI_MAX_NUM        (32)

#define AT_RX_PRI_ON                    (0)      /**/
#define AT_RX_DIV_ON                    (1)      /**/
#define AT_RXON_OPEN                    (0)      /*RXON=1*/
#define AT_TXON_OPEN                    (1)      /*TXON=1*/

#define AT_BIT0                            0x00000001L
#define AT_BIT1                            0x00000002L
#define AT_BIT2                            0x00000004L
#define AT_BIT3                            0x00000008L
#define AT_BIT4                            0x00000010L
#define AT_BIT5                            0x00000020L
#define AT_BIT6                            0x00000040L
#define AT_BIT7                            0x00000080L
#define AT_BIT8                            0x00000100L
#define AT_BIT9                            0x00000200L
#define AT_BIT10                           0x00000400L
#define AT_BIT11                           0x00000800L
#define AT_BIT12                           0x00001000L
#define AT_BIT13                           0x00002000L
#define AT_BIT14                           0x00004000L
#define AT_BIT15                           0x00008000L

/* W_RF_CFG_REQ */
#define W_RF_MASK_AFC                   AT_BIT0
#define W_RF_MASK_TX_ARFCN              AT_BIT1
#define W_RF_MASK_TX_TXONOFF            AT_BIT2
#define W_RF_MASK_TX_PAMODE             AT_BIT3
#define W_RF_MASK_TX_AGC                AT_BIT4
#define W_RF_MASK_TX_POWER              AT_BIT5
#define W_RF_MASK_RX_RXONOFF            AT_BIT6
#define W_RF_MASK_RX_ARFCN              AT_BIT7
#define W_RF_MASK_RX_ANTSEL             AT_BIT8
#define W_RF_MASK_RX_LNAMODE            AT_BIT9
#define W_RF_MASK_RX_PGC                AT_BIT10
#define W_RF_MASK_TX_POWDET             AT_BIT11

/* G_RF_RX_CFG_REQ_STRUuhwMask */
#define G_RF_MASK_RX_ARFCN              AT_BIT0            /*  */
#define G_RF_MASK_RX_MODE               AT_BIT1            /*  */
#define G_RF_MASK_RX_AGCMODE            AT_BIT2            /*  */
#define G_RF_MASK_RX_AGCGAIN            AT_BIT3            /* AGC */

/* G_RF_TX_CFG_REQ_STRUuhwMask */
/* : 1)GMSKG_RF_MASK_TX_GSMK_PA_VOLT
           G_RF_MASK_TX_POWER,;
         2)8PSK:G_RF_MASK_TX_POWER
         3) */
#define G_RF_MASK_TX_AFC                AT_BIT0            /*  */
#define G_RF_MASK_TX_ARFCN              AT_BIT1            /*  */
#define G_RF_MASK_TX_TXEN               AT_BIT2            /*  */
#define G_RF_MASK_TX_TXMODE             AT_BIT3            /*  */
#define G_RF_MASK_TX_MOD_TYPE           AT_BIT4            /*  */
#define G_RF_MASK_TX_GSMK_PA_VOLT       AT_BIT5            /* GMSK PA */
#define G_RF_MASK_TX_POWER              AT_BIT6            /* ,GMSK8PSK */
#define G_RF_MASK_TX_8PSK_PA_VBIAS      AT_BIT7            /* 8PSKPA */
#define G_RF_MASK_TX_TXOLC              AT_BIT8            /* TXOLC */
#define G_RF_MASK_TX_DATA_PATTERN       AT_BIT9

/**/
#define G_MOD_TYPE_GMSK                 0       /* GMSK */
#define G_MOD_TYPE_8PSK                 1       /* 8PSK */

/* noise tool  */
#define PHY_NOISE_MAX_RESULT_NUMB       32

/* 0xff */
#define PHY_NOIST_TOOL_CLOSE_TX         0xff

/*****************************************************************************
  3 
*****************************************************************************/
/*  */
enum AT_ANT_MODE_ENUM
{
    ANT_ONE  = 1,/**/
    ANT_TWO  = 2,/**/
    ANT_BUTT
};
typedef VOS_UINT8 AT_ANT_MODE_UINT8;

/* WDSP */
enum AT_W_BAND_ENUM
{
    W_FREQ_BAND1 = 1,
    W_FREQ_BAND2,
    W_FREQ_BAND3,
    W_FREQ_BAND4,
    W_FREQ_BAND5,
    W_FREQ_BAND6,
    W_FREQ_BAND7,
    W_FREQ_BAND8,
    W_FREQ_BAND9,
    W_FREQ_BAND10,                                                              /*  BAND10  */
    W_FREQ_BAND11,
    W_FREQ_BAND_BUTT
};
typedef VOS_UINT16 AT_WDSP_BAND_ENUM_UINT16;

/* GDSP  */
enum AT_GDSP_BAND_ENUM
{
    G_FREQ_BAND_GSM850 = 0,
    G_FREQ_BAND_GSM900,
    G_FREQ_BAND_DCS1800,
    G_FREQ_BAND_PCS1900,
    G_FREQ_BAND_BUTT
};
typedef VOS_UINT16 AT_GDSP_BAND_ENUM_UINT16;

/* AT HPA 0:success, 1:fail */
enum AT_HPA_CFG_RLST_ENUM
{
    AT_HPA_RSLT_SUCC = 0,
    AT_HPA_RSLT_FAIL,
    AT_HPA_RSLT_BUTT
};
typedef VOS_UINT16 AT_HPA_CFG_RLST_ENUM_UINT16;

/*****************************************************************************
  4 
*****************************************************************************/


/*****************************************************************************
  5 
*****************************************************************************/


/*****************************************************************************
  6 
*****************************************************************************/
/*#define ID_HPA_AT_TRANS_MSG_ID          0x8001            ID */

        /* WID*/
#define ID_AT_HPA_RF_CFG_REQ            0x2621
#define ID_HPA_AT_RF_CFG_CNF            0x62E0

#define ID_AT_HPA_RF_RX_RSSI_REQ        0x2622
#define ID_HPA_AT_RF_RX_RSSI_IND        0x62E1

        /* W PLLID*/
#define ID_AT_WPHY_RF_PLL_STATUS_REQ    0x2623
#define ID_AT_WPHY_RF_PLL_STATUS_CNF    0x62E2

        /* GID*/
#define ID_AT_GHPA_RF_RX_CFG_REQ        0x2415          /*RX*/
#define ID_AT_GHPA_RF_TX_CFG_REQ        0x2418          /*TX*/
#define ID_GHPA_AT_RF_MSG_CNF           0x4212          /*  */

#define ID_AT_GHPA_RF_RX_RSSI_REQ       0x2416          /*RX*/
#define ID_GHPA_AT_RF_RX_RSSI_IND       0x4210          /*RX*/

        /* G PLLID*/
#define ID_AT_GPHY_RF_PLL_STATUS_REQ    0x2419
#define ID_AT_GPHY_RF_PLL_STATUS_CNF    0x4219

        /* PDID*/
#define ID_AT_PHY_POWER_DET_REQ        0x2624
#define ID_AT_PHY_POWER_DET_CNF        0x62e3

/* Added by tyg for noise tool, 2014-12-23, begin */
/* noise tool wphy */
#define ID_AT_HPA_RF_NOISE_CFG_REQ      0x2625
#define ID_HPA_AT_RF_NOISE_RSSI_IND     0x62e4
/**/
/* NOISE TOOL ID */
#define ID_AT_GHPA_RF_NOISE_CFG_REQ     0x241A
#define ID_GHPA_AT_RF_NOISE_RSSI_IND    0x421A

#define ID_AT_HPA_MIPI_WR_REQ           0x2490
#define ID_HPA_AT_MIPI_WR_CNF           0x4290
#define ID_AT_HPA_MIPI_RD_REQ           0x2491
#define ID_HPA_AT_MIPI_RD_CNF           0x4291

#define ID_AT_HPA_SSI_WR_REQ            0x2492
#define ID_HPA_AT_SSI_WR_CNF            0x4292
#define ID_AT_HPA_SSI_RD_REQ            0x2493
#define ID_HPA_AT_SSI_RD_CNF            0x4293

#define ID_AT_HPA_PDM_CTRL_REQ          0x2494
#define ID_HPA_AT_PDM_CTRL_CNF          0x4294

        /* CDMAID*/
#define ID_AT_CHPA_RF_CFG_REQ            0x6300
#define ID_CHPA_AT_RF_CFG_CNF            0x6301

#define ID_AT_CHPA_RF_RX_RSSI_REQ        0x6302
#define ID_CHPA_AT_RF_RX_RSSI_IND        0x6303

/*****************************************************************************
     : C_RF_CFG_PARA_STRU
   : RF
 1.       : 20111116
          : f62575
      : 
*****************************************************************************/
typedef struct
{
    /* Tx Cfg */
    VOS_UINT16                          usMask;                                 /*  */
    VOS_UINT16                          usTxAFCInit;                            /* AFC */
    VOS_UINT16                          usTxBand;                               /* 1,2,3...,band,BandId */
    VOS_UINT16                          usTxFreqNum;                            /* Arfcn */
    VOS_UINT16                          usTxEnable;                             /* TX */
    VOS_UINT16                          usTxPAMode;                             /* PA */
    VOS_INT16                           sTxPower;                               /* 0.1dBm */

    /* Rx Cfg */
    VOS_UINT16                          usRxEnable;                             /* RX */
    VOS_UINT16                          usRxBand;                               /* 1,2,3...,band*/
    VOS_UINT16                          usRxFreqNum;                            /* Arfcn*/
    VOS_UINT16                          usRxAntSel;                             /* Ant1/Ant2*/
    VOS_UINT16                          usRsv;             /*  */

}C_RF_CFG_PARA_STRU;

/* AT_HPA  */
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          usMsgID;           /* Msg ID */
    VOS_UINT16                          usRsv;             /*  */
    C_RF_CFG_PARA_STRU                  stRfCfgPara;            /* RF */
}AT_CHPA_RF_CFG_REQ_STRU;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          usMsgID;           /* Msg ID */
    VOS_UINT16                          usRsv;             /*  */
    VOS_UINT16                          usMeasNum;             /* RSSI */
    VOS_UINT16                          usInterval;            /* RSSIms */
}AT_CHPA_RF_RX_RSSI_REQ_STRU;



/*****************************************************************************
  7 STRUCT
*****************************************************************************/
/* WRF */
/* RF */
/*****************************************************************************
     : W_RF_CFG_PARA_STRU
   : RF
 1.       : 20111116
          : f62575
      : 
 2.       : 20111116
          : f62575
      : 
                sRrcWidth, sDbbAtten, usRxCarrMode, usPaVbias
                sTxPower,
                sRxPGC
*****************************************************************************/
typedef struct
{
    /* TX RX */
    VOS_INT16                           sRrcWidth;                              /* ,,RRC,[-5,5]MHz */

    /* Tx Cfg */
    VOS_UINT16                          usMask;                                 /*  */
    VOS_UINT16                          usTxAFCInit;                            /* AFC */
    VOS_UINT16                          usTxBand;                               /* 1,2,3...,band,BandId */
    VOS_UINT16                          usTxFreqNum;                            /* Arfcn */
    VOS_UINT16                          usTxEnable;                             /* TX */
    VOS_UINT16                          usTxPAMode;                             /* PA */
    VOS_INT16                           sTxPower;                               /* 0.1dBm */
    VOS_INT16                           sDbbAtten;                              /* DBB usTxAGC??? */
    VOS_UINT16                          usRfAtten;                              /* RF */
    VOS_UINT16                          usTxAGC;                                /* AGC */
    VOS_UINT16                          usPaVbias;                              /* W PA Vbias  */

    /* Rx Cfg */
    VOS_UINT16                          usRxEnable;                             /* RX */
    VOS_UINT16                          usRxBand;                               /* 1,2,3...,band*/
    VOS_UINT16                          usRxFreqNum;                            /* Arfcn*/
    VOS_UINT16                          usRxAntSel;                             /* Ant1/Ant2*/
    VOS_UINT16                          usRxLNAGainMode;                        /* LNA */


    VOS_UINT16                          usRxCarrMode;                           /* 0:;1: */
}W_RF_CFG_PARA_STRU;


/* AT_HPA  */
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          usMsgID;           /* Msg ID */
    VOS_UINT16                          usRsv;             /*  */
    W_RF_CFG_PARA_STRU                  stRfCfgPara;            /* RF */
}AT_HPA_RF_CFG_REQ_STRU;

/* GRF */
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          usMsgID;           /* Msg ID */
    VOS_UINT16                          usRsv;             /*  */
    VOS_UINT16                          usMask;        /* Reference MASK_CAL_RF_G_RX_* section */
    VOS_UINT16                          usFreqNum;     /* (Band << 12) | Arfcn */
    VOS_UINT16                          usRxMode;      /* 0:burst; 1:;, */
    VOS_UINT16                          usAGCMode;     /* Fast AGC,Slow AGC */
    VOS_UINT16                          usAgcGain;     /* AGC,0-3*/
    VOS_UINT16                          usRsv2;
}AT_GHPA_RF_RX_CFG_REQ_STRU;

/*****************************************************************************
     : AT_GHPA_RF_CTRLMODE_TYPE_ENUM
   : 
             0GMSK,usTxVpa
             1,usTxPower
             28PSK PaVbias&DBB Atten&RF AttenusPAVbiasusRfAtten,sDbbAtten
1.       : 20111117
         : f62575
     : 
*****************************************************************************/
enum AT_GHPA_RF_CTRLMODE_TYPE_ENUM
{
    AT_GHPA_RF_CTRLMODE_TYPE_GMSK,
    AT_GHPA_RF_CTRLMODE_TYPE_TXPOWER,
    AT_GHPA_RF_CTRLMODE_TYPE_8PSK,
    AT_GHPA_RF_CTRLMODE_TYPE_BUTT
};
typedef VOS_UINT16 AT_GHPA_RF_CTRLMODE_TYPE_ENUM_UINT16;

/*****************************************************************************
     : AT_GHPA_RF_TX_CFG_REQ_STRU
   :
 1.       : 20111116
          : f62575
      : 
 2.       : 20111116
          : f62575
      : 
                enCtrlMode, uhwRfAtten
                usModType,
                usTxolc
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          usMsgID;                                /* Msg ID */
    VOS_UINT16                          usRsv;                                  /*  */
    VOS_UINT16                          usMask;                                 /* Reference MASK_CAL_RF_G_TX_* section*/
    VOS_UINT16                          usAFC;                                  /* AFC */
    VOS_UINT16                          usModType;                              /* :0GMSK;18PSK */
    VOS_UINT16                          usFreqNum;                              /* (Band << 12) | Arfcn */
    VOS_UINT16                          usTxEnable;                             /* :0x5555-;0xAAAA-;TSC 0; TxData:  */
    VOS_UINT16                          usTxMode;                               /* 0:burst; 1: */
    AT_GHPA_RF_CTRLMODE_TYPE_ENUM_UINT16  enCtrlMode;                             /* 
                                                                                    0GMSK,usTxVpa
                                                                                    1,usTxPower
                                                                                    28PSK PaVbias&DBB Atten&RF Atten
                                                                                    usPAVbiasusRfAtten,sDbbAtten*/
    VOS_UINT16                          usReserved;
    VOS_UINT32                          uhwRfAtten;
    VOS_UINT16                          usTxPower;                              /* ,0.1dBm,GSMEDGE */
    VOS_UINT16                          usTxVpa;                                /* GSM PA,: */
    VOS_INT16                           shwDbbAtten;
    VOS_UINT16                          usPAVbias;                              /* EDGE PA Vbais  */
}AT_GHPA_RF_TX_CFG_REQ_STRU;


/*Response Head Struct    W/G */
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          usTransPrimID;     /* 0x8001 */
    VOS_UINT16                          usRsv1;            /*  */
    VOS_UINT16                          usMsgID;           /* Msg ID */
    VOS_UINT16                          usRsv;             /*  */
}HPA_AT_HEADER_STRU;

typedef struct
{
    HPA_AT_HEADER_STRU                  stMsgHeader;
    VOS_UINT16                          usCfgMsgID;        /* ID */
    VOS_UINT16                          usErrFlg;          /* 0:success, 1:fail */
}HPA_AT_RF_CFG_CNF_STRU;


typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          usMsgID;           /* Msg ID */
    VOS_UINT16                          usRsv;             /*  */
    VOS_UINT16                          usMeasNum;             /* RSSI */
    VOS_UINT16                          usInterval;            /* RSSIms */
}AT_HPA_RF_RX_RSSI_REQ_STRU;

/* RSSI  G/W */
typedef struct
{
    HPA_AT_HEADER_STRU                  stMsgHeader;
    VOS_INT16                           sRSSI;            /* RSSI [-2048,+2047]0.125dBm*/
    VOS_INT16                           sAGCGain;         /* -1 */
}HPA_AT_RF_RX_RSSI_IND_STRU;

/*****************************************************************************
     : PHY_NOISE_RESULT_STRU
   : PHYAT
 1.       : 20141229
          : tianyige
      : Noise tool PHY
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usDLFreq;                               /*PHY*/
    VOS_INT16                           sDLPriRssi;                             /*PHYRSSI*/
    VOS_INT16                           sDLDivRssi;                             /*PHYRSSI*/
    VOS_UINT16                          usRsv;
}PHY_NOISE_RESULT_STRU;

/*****************************************************************************
     : HPA_NOISE_RSSI_IND_STRU
   : WPHYGPHYAT
 1.       : 20141229
          : tianyige
      : Noise tool PHY
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usDLRssiNum;                            /*PHYRSSI*/
    VOS_UINT16                          usMeaStatus;                            /*PHY012 */
    PHY_NOISE_RESULT_STRU               astDlRssiResult[AT_DPS_NOISERSSI_MAX_NUM];
}HPA_NOISE_RSSI_IND_STRU;


/*****************************************************************************
     : PHY_AT_RF_NOISE_RSSI_IND_STRU
   : WPHYGPHYAT
 1.       : 20141229
          : tianyige
      : Noise tool PHY
*****************************************************************************/
typedef struct
{
    HPA_AT_HEADER_STRU                  stMsgHeader;                            /*  */
    HPA_NOISE_RSSI_IND_STRU             stRssiInd;                              /*  */
}PHY_AT_RF_NOISE_RSSI_IND_STRU;

/*****************************************************************************
     : AT_PHY_RF_PLL_STATUS_REQ_STRU
   : ATWPHYGPHYPLL
 1.       : 20131129
          : L00256032
      : Added for PLL status query
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          usMsgID;           /* Msg ID */
    VOS_UINT16                          usRsv1;            /*  */
    VOS_UINT16                          usDspBand;         /* DSP */
    VOS_UINT16                          usRsv2;            /*  */
}AT_PHY_RF_PLL_STATUS_REQ_STRU;

/*****************************************************************************
     : AT_PHY_RF_PLL_STATUS_REQ_STRU
   : WPHYGPHYATPLL
 1.       : 20131129
          : L00256032
      : Added for PLL status query
*****************************************************************************/
typedef struct
{
    HPA_AT_HEADER_STRU                  stMsgHeader;
    VOS_UINT16                          usTxStatus;        /* 0:PLL, 1:PLL */
    VOS_UINT16                          usRxStatus;        /* 0:PLL, 1:PLL */
}PHY_AT_RF_PLL_STATUS_CNF_STRU;


/*****************************************************************************
     : AT_PHY_POWER_DET_REQ_STRU
   : ATWPHY
 1.       : 20140506
          : c00242732
      : Added for Power_Detect query
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          usMsgID;           /* Msg ID */
    VOS_UINT16                          usRsv;             /*  */
}AT_PHY_POWER_DET_REQ_STRU;

/*****************************************************************************
     : PHY_AT_POWER_DET_CNF_STRU
   : WPHYAT
 1.       : 20140506
          : c00242732
      : Added for Power_Detect query
*****************************************************************************/
typedef struct
{
    HPA_AT_HEADER_STRU                  stMsgHeader;
    VOS_INT16                           sPowerDet;         /* 0.1dBm */
    VOS_UINT16                          usRsv;             /*  */
}PHY_AT_POWER_DET_CNF_STRU;


/*****************************************************************************
     : AT_HPA_RF_NOISE_CFG_REQ_STRU
   : ATGPHYnoise tool
 1.       : 20141219
          : tianyige
      : Added for noise tool
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          usMsgID;                                /* Msg ID */
    VOS_UINT16                          usMode;                                 /* UE  */
    VOS_UINT16                          usBand;                                 /* band */
    VOS_UINT16                          usDlStartFreq;                          /*  */
    VOS_UINT16                          usDlEndFreq;                            /*  */
    VOS_UINT16                          usFreqStep;                             /*  */
    VOS_INT16                           sTxPwr;                                 /*  */
    VOS_UINT16                          usRsv;                                  /*  */
}AT_HPA_RF_NOISE_CFG_REQ_STRU;

/*****************************************************************************
     : AT_HPA_MIPI_WR_REQ_STRU
   : MIPI 

 1.       : 2015910
           : l00227485
       : 
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          usMsgID;
    VOS_UINT16                          usSlaveAddr;
    VOS_UINT16                          usRegAddr;
    VOS_UINT16                          usRegData;
    VOS_UINT16                          usMipiChannel;
    VOS_UINT16                          usRsv;
}AT_HPA_MIPI_WR_REQ_STRU;

/*****************************************************************************
     : HPA_AT_MIPI_WR_CNF_STRU
   : ATAT AGENT MIPI 
1.       : 2015910
          :l00227485
      : 
*****************************************************************************/
typedef struct
{
    HPA_AT_HEADER_STRU                  stMsgHeader;
    VOS_UINT32                          usErrFlg;          /* 0:success, 1:fail */
}HPA_AT_MIPI_WR_CNF_STRU;

/*****************************************************************************
     : AT_HPA_MIPI_RD_REQ_STRU
   :MIPI 
 1.       : 2015910
           : l00227485
       : 
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          usMsgID;                                /* Msg ID */
    VOS_UINT16                          uhwSlaveAddr;                           /*  */
    VOS_UINT16                          uhwReg;                                 /*  */
    VOS_UINT16                          uhwChannel;                             /*  */
}AT_HPA_MIPI_RD_REQ_STRU;

/*****************************************************************************
     : HPA_AT_MIPI_RD_CNF_STRU
   : ATAT AGENT MIPI 
1.       : 2015910
          :l00227485
      : 
*****************************************************************************/
typedef struct
{
    HPA_AT_HEADER_STRU                  stMsgHeader;
    VOS_UINT32                          ulValue;
    VOS_UINT32                          ulResult;
}HPA_AT_MIPI_RD_CNF_STRU;

/*****************************************************************************
     : AT_HPA_SSI_WR_REQ_STRU
   : ATPHYSSI
 1.       : 20150919
          : x00316382
      : Added for ssi tool
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          usMsgID;
    VOS_UINT16                          usRficSsi;                              /* Mipi */
    VOS_UINT16                          usRegAddr;                              /*  */
    VOS_UINT16                          usData;                                 /*  */
}AT_HPA_SSI_WR_REQ_STRU;

/*****************************************************************************
     : HPA_AT_SSI_WR_CNF_STRU
   : ATAT AGENT MIPI 
1.       : 2015910
          :l00227485
      : 
*****************************************************************************/
typedef struct
{
    HPA_AT_HEADER_STRU                  stMsgHeader;
    VOS_UINT32                          usErrFlg;                               /* 0:success, 1:fail */
}HPA_AT_SSI_WR_CNF_STRU;

/*****************************************************************************
     : AT_HPA_SSI_RD_REQ_STRU
   :
 1.       : 20150919
          : x00316382
      : Added for tool
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          usMsgID;                                /* Msg ID */
    VOS_UINT16                          usChannelNo;                            /*  */
    VOS_UINT32                          uwRficReg;
}AT_HPA_SSI_RD_REQ_STRU;

/*****************************************************************************
     : HPA_AT_SSI_RD_CNF_STRU
   : ATAT AGENT MIPI 
1.       : 2015910
          :l00227485
      : 
*****************************************************************************/
typedef struct
{
    HPA_AT_HEADER_STRU                  stMsgHeader;
    VOS_UINT32                          ulValue;
    VOS_UINT32                          ulResult;
}HPA_AT_SSI_RD_CNF_STRU;

/* RSSI  G/W */
typedef struct
{
    HPA_AT_HEADER_STRU                  stMsgHeader;
    VOS_INT16                           sRSSI;            /* RSSI [-2048,+2047]0.125dBm*/
    VOS_INT16                           sAGCGain;         /* -1 */
}CHPA_AT_RF_RX_RSSI_IND_STRU;

typedef struct
{
    HPA_AT_HEADER_STRU                  stMsgHeader;
    VOS_UINT16                          usCfgMsgID;        /* ID */
    VOS_UINT16                          usErrFlg;          /* 0:success, 1:fail */
}CHPA_AT_RF_CFG_CNF_STRU;

/*****************************************************************************
     : AT_HPA_PDM_CTRL_REQ_STRU
   :
 1.       : 20151020
          : x00316382
      : Added for tool
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          usMsgID;                                /* Msg ID */
    VOS_UINT16                          usRsv;                                  /*  */
    VOS_UINT16                          usPdmRegValue;
    VOS_UINT16                          usPaVbias;
    VOS_UINT16                          usPaVbias2;
    VOS_UINT16                          usPaVbias3;
}AT_HPA_PDM_CTRL_REQ_STRU;

/*****************************************************************************
     : HPA_AT_PDM_CTRL_CNF_STRU
   : ATAT AGENT PDM 
1.       : 20151020
         : x00316382
     : 
*****************************************************************************/
typedef struct
{
    HPA_AT_HEADER_STRU                  stMsgHeader;
    VOS_UINT32                          ulResult;
}HPA_AT_PDM_CTRL_CNF_STRU;

/*****************************************************************************
  8 UNION
*****************************************************************************/


/*****************************************************************************
  9 OTHERS
*****************************************************************************/


/*****************************************************************************
  10 
*****************************************************************************/


#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of AtPhyInterface.h */
