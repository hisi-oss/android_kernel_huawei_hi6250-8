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
#ifndef __GEN_MSG_H__
#define __GEN_MSG_H__

#include "ApsL4aInterface.h"
#include "at_common.h"
#include "vos.h"
#include "mdrv.h"
#include "AppRrcInterface.h"
#include "AppEsmInterface.h"
#include "AppMmInterface.h"

#include "AppRrcLteCommonInterface.h"
#include  "AppL2Interface.h"

#define MSP_UPGRADE_DLOAD_VER_LEN             (30)
#define MSP_UPGRADE_DLOAD_SOFTWARE_LEN        (30)
#define MSP_UPGRADE_DLOAD_ISO_LEN             (100)
#define MSP_UPGRADE_DLOAD_PRODUCTID_LEN       (30)

#define L4A_MAX_IPV6_PREFIX_NUM                (6)                             /* IPv6 */


/*****************************************************************************

 MSP 

*****************************************************************************/

#if(VOS_OS_VER == VOS_WIN32)
#pragma warning(disable:4200) /* disable nonstandard extension used : zero-sized array in struct/union.*/
#pragma warning(disable:4214) /* allows bitfield structure members to be of any integral type.*/
#endif

/*****************************************************************************

 MUX
 (0x00010000,0x00010050]
*****************************************************************************/
#define ID_MSG_DIAG_CMD_REQ          (0x00010001)
#define ID_MSG_DIAG_CMD_CNF          (0x00010002)


/*****************************************************************************

 AT
 [0x00010051,0x00010100)
*****************************************************************************/



/*****************************************************************************

 DIAG 
 [0x00010101,0x00010120)
*****************************************************************************/
#define ID_MSG_DIAG_DRA_DSP_REQ         (0x00010101)
#define ID_MSG_DIAG_DRA_DSP_CNF         (0x00010102) /* HAL_DRA --> DIAG*/
#define ID_MSG_DIAG_TIMER_DSPTIMOUT_IND (0x00010103)

#define ID_MSG_DIAG_SIMMTRANS_REQ       (0x00010107)
#define ID_MSG_DIAG_SIMMTRANS_CNF       (0x00010108)
#define ID_MSG_DIAG_SIMMTRANS_IND       (0x00010109)
#define ID_MSG_DIAG_AT_HSOADDR_IND      (0x0001010A) /* DIAGAT*/
#define ID_MSG_DIAG_AT_HSO_AT_REQ       (0x0001010B) /* DIAG-->AT*/
#define ID_MSG_AT_DIAG_HSO_AT_CNF       (0x0001010C) /* AT  -->DIAG*/
#define ID_MSG_AT_DIAG_HSO_AT_IND       (0x0001010D) /* AT  -->DIAG*/
#define ID_MSG_A_DIAG_HSO_CONN_IND      (0x0001010E) /* A DIAG  --> M DIAG*/


/*****************************************************************************

 POM
 [0x00010121,0x00010140)
*****************************************************************************/
#define ID_MSG_SYM_SYSMODE_IND          (0x00010121)
#define ID_MSG_SYM_SET_TMODE_REQ        (0x00010122)
#define ID_MSG_SYM_SET_TMODE_CNF        (0x00010123)
#define ID_MSG_SYM_RD_TMODE_REQ         (0x00010124)
#define ID_MSG_SYM_RD_TMODE_CNF         (0x00010125)
#define ID_MSG_SUM_SOFTUPDATE_IND       (0x00010128)
#define ID_MSG_SUM_SOFTBACK_REQ         (0x00010129)
#define ID_MSG_SUM_SOFTBACK_CNF         (0x0001012A)
#define ID_MSG_SYM_GET_FTP_FILE_IND     (0x0001012B)
#define ID_MSG_SYM_SET_HPM_REQ          (0x0001012C)
#define ID_MSG_SYM_SET_HPM_CNF          (0x0001012D)
#define ID_MSG_SYM_RD_HPM_REQ          (0x0001012E)
#define ID_MSG_SYM_RD_HPM_CNF          (0x0001012F)
#define ID_MSG_SYM_ATF_REQ              (0x00010130)
#define ID_MSG_SYM_ATF_CNF              (0x00010131)
#define ID_MSG_SYM_QUERY_CARDLOCK_REQ   (0x00010132)
#define ID_MSG_SYM_QUERY_CARDLOCK_CNF   (0x00010133)

/*****************************************************************************

 FTM
 [0x00010140,0x00010201)
*****************************************************************************/
#define ID_MSG_FTM_SET_TXON_REQ             (0x00010140)
#define ID_MSG_FTM_SET_TXON_CNF             (0x00010141)
#define ID_MSG_FTM_RD_TXON_REQ              (0x00010142)
#define ID_MSG_FTM_RD_TXON_CNF              (0x00010143)
#define ID_MSG_FTM_SET_FCHAN_REQ            (0x00010144)
#define ID_MSG_FTM_SET_FCHAN_CNF            (0x00010145)
#define ID_MSG_FTM_RD_FCHAN_REQ             (0x00010146)
#define ID_MSG_FTM_RD_FCHAN_CNF             (0x00010147)
#define ID_MSG_FTM_SET_RXON_REQ             (0x0001014e)
#define ID_MSG_FTM_SET_RXON_CNF             (0x0001014f)
#define ID_MSG_FTM_RD_RXON_REQ              (0x00010150)
#define ID_MSG_FTM_RD_RXON_CNF              (0x00010151)
#define ID_MSG_FTM_SET_FWAVE_REQ            (0x00010152)
#define ID_MSG_FTM_SET_FWAVE_CNF            (0x00010153)
#define ID_MSG_FTM_RD_FWAVE_REQ             (0x00010154)
#define ID_MSG_FTM_RD_FWAVE_CNF             (0x00010155)
#define ID_MSG_FTM_SET_AAGC_REQ             (0x00010156)
#define ID_MSG_FTM_SET_AAGC_CNF             (0x00010157)
#define ID_MSG_FTM_RD_AAGC_REQ              (0x00010158)
#define ID_MSG_FTM_RD_AAGC_CNF              (0x00010159)
#define ID_MSG_FTM_FRSSI_REQ                (0x0001015a)
#define ID_MSG_FTM_FRSSI_CNF                (0x0001015b)
#define ID_MSG_FTM_OPENCHAN_REQ             (0x0001015c)
#define ID_MSG_FTM_OPENCHAN_CNF             (0x0001015d)

#define ID_MSG_FTM_TIME_OUT                 (0x0001015e)

#define ID_MSG_FTM_PHY_POWER_REQ            (0x0001015f)
#define ID_MSG_FTM_PHY_POWER_CNF            (0x00010160)

#define ID_MSG_FTM_RD_FAGC_REQ              (0x00010163)
#define ID_MSG_FTM_RD_FAGC_CNF              (0x00010164)


/*start*/
#define ID_MSG_FTM_SET_SRXPOW_REQ             (0x000101d3)
#define ID_MSG_FTM_SET_SRXPOW_CNF             (0x000101d4)
#define ID_MSG_FTM_RD_SRXPOW_REQ              (0x000101d5)
#define ID_MSG_FTM_RD_SRXPOW_CNF              (0x000101d6)

#define ID_MSG_FTM_SET_SRXBLER_REQ             (0x000101db)
#define ID_MSG_FTM_SET_SRXBLER_CNF             (0x000101dc)

/*end*/

/* FTM lkf58113 @ 20111010*/
#define ID_MSG_FTM_RD_DLOADVER_REQ              (0x000101eb)
#define ID_MSG_FTM_RD_DLOADVER_CNF              (0x000101ec)

#define ID_MSG_FTM_RD_DLOADINFO_REQ             (0x000101ed)
#define ID_MSG_FTM_RD_DLOADINFO_CNF             (0x000101ee)

#define ID_MSG_FTM_RD_AUTHORITYVER_REQ          (0x000101ef)
#define ID_MSG_FTM_RD_AUTHORITYVER_CNF          (0x000101f0)

#define ID_MSG_FTM_RD_AUTHORITYID_REQ           (0x000101f1)
#define ID_MSG_FTM_RD_AUTHORITYID_CNF           (0x000101f2)

#define ID_MSG_FTM_SET_NVBACKUP_REQ             (0x000101f5)
#define ID_MSG_FTM_SET_NVBACKUP_CNF             (0x000101f6)

#define ID_MSG_FTM_SET_NVRESTORE_REQ            (0x000101f7)
#define ID_MSG_FTM_SET_NVRESTORE_CNF            (0x000101f8)

#define ID_MSG_FTM_SET_GODLOAD_REQ              (0x000101f9)
#define ID_MSG_FTM_SET_GODLOAD_CNF              (0x000101fa)

#define ID_MSG_FTM_SET_RESET_REQ                (0x000101fb)
#define ID_MSG_FTM_SET_RESET_CNF                (0x000101fc)

#define ID_MSG_FTM_SET_NVRSTSTTS_REQ            (0x000101fd)
#define ID_MSG_FTM_SET_NVRSTSTTS_CNF            (0x000101fe)

#define ID_MSG_FTM_SET_SDLOAD_REQ               (0x000101ff)
#define ID_MSG_FTM_SET_SDLOAD_CNF               (0x00010200)

#define ID_MSG_L1A_CT_IND                       (0x00010450)

/**/
#define ID_MSG_FTM_SET_TSELRF_REQ               (0x00010950)
#define ID_MSG_FTM_SET_TSELRF_CNF               (0x00010951)
/**/
#define ID_MSG_FTM_SET_TBAT_REQ                (0x0001095c)
#define ID_MSG_FTM_SET_TBAT_CNF                (0x0001095d)

#define ID_MSG_FTM_RD_TBAT_REQ                 (0x0001095e)
#define ID_MSG_FTM_RD_TBAT_CNF                 (0x0001095f)
#define ID_MSG_FTM_TMODE_TO_SLAVE              (0x00010964)
#define ID_MSG_FTM_TMODE_TO_SLAVE_CNF          (0x00010965)

#define ID_MSG_FTM_FCHAN_TO_DSP_MASTER         (0x00010966)
#define ID_MSG_FTM_FCHAN_TO_DSP_SLAVE          (0x00010968)
#define ID_MSG_FTM_POLLTEMPR_REQ               (0x00010969)

/*notice: lte msg id range from 0x00011000 to 0x00011FFF*/

#define ID_MSG_TDS_SET_TSELRF_REQ       (0x0001097B)
#define ID_MSG_TDS_SET_TSELRF_CNF       (0x0001097C)
#define ID_MSG_TDS_RD_TSELRF_REQ        (0x0001097D)
#define ID_MSG_TDS_RD_TSELRF_CNF        (0x0001097E)
#define ID_MSG_TDS_SET_FCHAN_REQ        (0x0001097F)
#define ID_MSG_TDS_SET_FCHAN_CNF     	(0x00010980)
#define ID_MSG_TDS_RD_FCHAN_REQ         (0x00010981)
#define ID_MSG_TDS_RD_FCHAN_CNF         (0x00010982)
#define ID_MSG_TDS_SET_FWAVE_REQ        (0x00010983)
#define ID_MSG_TDS_SET_FWAVE_CNF        (0x00010984)

#define ID_MSG_TDS_SET_FTXON_REQ        (0x00010985)
#define ID_MSG_TDS_SET_FTXON_CNF        (0x00010986)
#define ID_MSG_TDS_RD_FTXON_REQ         (0x00010987)
#define ID_MSG_TDS_RD_FTXON_CNF         (0x00010988)
#define ID_MSG_TDS_SET_FRXON_REQ        (0x00010989)
#define ID_MSG_TDS_SET_FRXON_CNF        (0x0001098A)
#define ID_MSG_TDS_RD_FRXON_REQ         (0x0001098B)
#define ID_MSG_TDS_RD_FRXON_CNF         (0x0001098C)
#define ID_MSG_TDS_RD_FRSSI_REQ         (0x0001098D)
#define ID_MSG_TDS_RD_FRSSI_CNF         (0x0001098E)

#define ID_MSG_TDS_REQ         			(0x00010991)
#define ID_MSG_TDS_CNF         			(0x00010992)



#define ID_MSG_FTM_SET_LTCOMMCMD_REQ        (0x000109BD)
#define ID_MSG_FTM_SET_LTCOMMCMD_CNF        (0x000109BE)
#define ID_MSG_FTM_RD_LTCOMMCMD_REQ         (0x000109BF)
#define ID_MSG_FTM_RD_LTCOMMCMD_CNF         (0x000109C0)

#define ID_MSG_FTM_RD_FPLLSTATUS_REQ        (0x000109c1)
#define ID_MSG_FTM_RD_FPLLSTATUS_CNF        (0x000109c2)

#define ID_MSG_L4A_MODE_IND             (0x00011001)
#define ID_MSG_L4A_READ_CEREG_CNF       (0x00011002)
#define ID_MSG_L4A_CGANS_IND            (0x00011003)

#define ID_MSG_DIAG_PSTRANS_REQ         (0x00011004)
#define ID_MSG_DIAG_PSTRANS_CNF         (0x00011005)
#define ID_MSG_DIAG_PSTRANS_IND         (0x00011006)

#define ID_MSG_L4A_CSQ_INFO_REQ         (0x00011007)
#define ID_MSG_L4A_CSQ_INFO_CNF         (0x00011008)
#define ID_MSG_L4A_RSSI_IND             (0x00011009)

#define ID_MSG_L4A_ANLEVEL_IND          (0x0001100A)
#define ID_MSG_L4A_ANQUERY_INFO_REQ	    (0x0001100B)
#define ID_MSG_L4A_ANQUERY_INFO_CNF     (0x0001100C)

#define ID_MSG_L4A_LWCLASHQRY_REQ       (0x0001100D)
#define ID_MSG_L4A_LWCLASHQRY_CNF       (0x0001100E)
#define ID_MSG_L4A_LWCLASH_IND          (0x0001100F)

#define ID_MSG_L4A_CERSSI_REQ           (0x00011010)
#define ID_MSG_L4A_CERSSI_CNF           (0x00011011)
#define ID_MSG_L4A_CERSSI_IND           (0x00011012)

#define ID_MSG_L4A_CELL_ID_REQ          (0x00011015)
#define ID_MSG_L4A_CELL_ID_CNF          (0x00011016)

#define ID_MSG_L4A_LTE_TO_IDLE_REQ      (0x00011017)
#define ID_MSG_L4A_LTE_TO_IDLE_CNF      (0x00011018)

#define ID_MSG_L4A_LW_THRESHOLD_REQ     (0x00011019)
#define ID_MSG_L4A_LW_THRESHOLD_CNF     (0x0001101A)

#define ID_MSG_L4A_FAST_DORM_REQ        (0x0001101B)
#define ID_MSG_L4A_FAST_DORM_CNF        (0x0001101C)

#define ID_MSG_L4A_CELL_INFO_REQ        (0x00011020)
#define ID_MSG_L4A_CELL_INFO_CNF        (0x00011021)
#define ID_MSG_L4A_CELL_INFO_IND        (0x00011022)

#define ID_MSG_L4A_LTE_CS_REQ           (0x00011023)
#define ID_MSG_L4A_LTE_CS_CNF           (0x00011024)

#define ID_MSG_L4A_IND_CFG_REQ		    (0x00011025)

#define ID_MSG_L4A_CERSSI_INQ_REQ       (0x00011026)
#define ID_MSG_L4A_CERSSI_INQ_CNF       (0x00011027)

/*begin_added by c64416 for lte wifi 20131013*/
#define ID_MSG_L4A_ISMCOEXSET_REQ       (0x00011028)
#define ID_MSG_L4A_ISMCOEXSET_CNF       (0x00011029)
/*end_added by c64416 for lte wifi 20131013*/

#define ID_MSG_L4A_RADVER_SET_REQ       (0x00011030)
#define ID_MSG_L4A_RADVER_SET_CNF       (0x00011031)

#define ID_MSG_L4A_LCACELLQRY_REQ       (0x00011032)
#define ID_MSG_L4A_LCACELLQRY_CNF       (0x00011033)
#define ID_MSG_L4A_LCACELL_IND          (0x00011034)



#define ID_MSG_TDS_DIAG_REQ         	(0x00020001)
#define ID_MSG_TDS_DIAG_CNF         	(0x00020002)

/*****************************************************************************

 L1AID [0x00010450,0x00010500)
*****************************************************************************/

#define RSSI_POW_MAX_NUM        (30)
#define CT_F_FREQ_LIST_MAX_NUM     32

/*****************************************************************************

 MSP 

*****************************************************************************/

/*****************************************************************************

 MUX
 (0x00010000,0x00010050]
*****************************************************************************/



/*****************************************************************************

 MSM

*****************************************************************************/

typedef struct
{
	VOS_UINT16 usIndex;
	VOS_UINT8 ucContent[8];
}WIWEP_SUPPORT_STRU;

typedef struct
{
	VOS_UINT32 ulBandValue;
	VOS_UINT8 pucBandStr[4];
}CLIP_SUPPORT_BANDS_STRU;

/******************************************************************************/
/* lkf58113 @20111011*/
/*DLOADVER*/
typedef struct
{
    VOS_UINT32 ulReserved;
} FTM_RD_DLOADVER_REQ_STRU;

typedef struct
{
    VOS_UINT32 ulErrCode;
    /*VOS_UINT32 ulLength; */
    VOS_CHAR cVer[MSP_UPGRADE_DLOAD_VER_LEN+1];
    VOS_CHAR padding;

} FTM_RD_DLOADVER_CNF_STRU;

/*DLOADINFO*/
typedef struct
{
    VOS_UINT32 ulReserved; /* */
} FTM_RD_DLOADINFO_REQ_STRU;

/*DLOADINFO*/
typedef struct
{
    VOS_UINT32 ulReserved; /* */
} FTM_RD_SDLOAD_REQ_STRU;

typedef struct
{
    VOS_UINT32 ulErrCode;
    VOS_UINT32 ulRetValue;
} FTM_SET_SDLOAD_CNF_STRU;


typedef struct
{
    VOS_UINT32   ulErrCode;
    /*VOS_UINT32 ulLength; */
    VOS_CHAR  szSendSW[MSP_UPGRADE_DLOAD_SOFTWARE_LEN +1];
    VOS_CHAR padding;
    VOS_CHAR  szSendISO[MSP_UPGRADE_DLOAD_ISO_LEN+1];
    VOS_CHAR padding1[3];
    VOS_CHAR  szSendProductID[MSP_UPGRADE_DLOAD_PRODUCTID_LEN+1];
    VOS_CHAR padding2;
    VOS_CHAR  szSendDloadType[4];


} FTM_RD_DLOADINFO_CNF_STRU;

/*AUTHORITYVER*/
typedef struct
{
    VOS_UINT32 ulReserved; /* */
} FTM_RD_AUTHORITYVER_REQ_STRU;

typedef struct
{
    VOS_UINT32 ulErrCode;
    /*VOS_UINT32 ulLength; */
    VOS_CHAR szAuthorityVer[MSP_UPGRADE_DLOAD_VER_LEN +1];
    VOS_CHAR padding;

} FTM_RD_AUTHORITYVER_CNF_STRU;

/*AUTHORITYID*/
typedef struct
{
    VOS_UINT32 ulReserved; /* */
} FTM_RD_AUTHORITYID_REQ_STRU;

typedef struct
{
    VOS_UINT32 ulErrCode;
    /*VOS_UINT32 ulLength;*/
    VOS_CHAR szAuthorityID[MSP_UPGRADE_DLOAD_VER_LEN +1];
    VOS_CHAR padding0;
    VOS_CHAR szAuthorityType[2];
    VOS_CHAR padding[2];

} FTM_RD_AUTHORITYID_CNF_STRU;

/*BOOTROMVER*/
typedef struct
{
    VOS_UINT32 ulReserved; /* */
} FTM_RD_BOOTROMVER_REQ_STRU;

typedef struct
{
    VOS_UINT32 ulErrCode;
    /*VOS_UINT32 ulLength; */
    VOS_CHAR szSendStr[MSP_UPGRADE_DLOAD_VER_LEN +1];
    VOS_CHAR padding;

} FTM_RD_BOOTROMVER_CNF_STRU;

/*NVBACKUP*/
typedef struct
{
    VOS_UINT32 ulReserved; /* */
} FTM_SET_NVBACKUP_REQ_STRU;

typedef struct
{
    VOS_UINT32 ulErrCode;
    VOS_UINT32 ulRetValue;

} FTM_SET_NVBACKUP_CNF_STRU;

/*NVRESTORE*/
typedef struct
{
    VOS_UINT32 ulReserved; /* */
} FTM_SET_NVRESTORE_REQ_STRU;

typedef struct
{
    VOS_UINT32 ulErrCode;
    VOS_UINT32 ulRetValue;

} FTM_SET_NVRESTORE_CNF_STRU;

/*GODLOAD*/
typedef struct
{
    VOS_UINT32 ulNvBackupFlag;
} FTM_SET_GODLOAD_REQ_STRU;

typedef struct
{
    VOS_UINT32 ulErrCode;

} FTM_SET_GODLOAD_CNF_STRU;

/*RESET*/
typedef struct
{
    VOS_UINT32 ulReserved; /* */
} FTM_SET_RESET_REQ_STRU;

typedef struct
{
    VOS_UINT32 ulErrCode;

} FTM_SET_RESET_CNF_STRU;

/*NVRSTSTTS*/
typedef struct
{
    VOS_UINT32 ulReserved; /* */
} FTM_SET_NVRSTSTTS_REQ_STRU;

typedef struct
{
    VOS_UINT32 ulErrCode;
    VOS_CHAR szNVRst[4];

} FTM_SET_NVRSTSTTS_CNF_STRU;


/*****************************************************************************
  : MUX DIAG  TO DO ...
 ID   : ID_MSG_SYM_SYSMODE_IND
 REQ  : NA
 CNF  : NA
 IND  : SYM_SYSMODE_IND_STRU
  :
*****************************************************************************/
typedef enum _POM_SYSMODE_ENUM
{
    EN_POM_SYSMODE_NORMAL = 0,
    EN_POM_SYSMODE_FTM,
    EN_POM_SYSMODE_ETM,
    EN_POM_SYSMODE_UNKNOWN
} SYM_SYSMODE_ENUM;

typedef struct
{
    SYM_SYSMODE_ENUM   enSysMode;
} SYM_SYSMODE_IND_STRU;

/*****************************************************************************
  : TMODE ^TMODESYM
        SYMDSP
 ID   : ID_MSG_SYM_SET_TMODE_REQ,ID_MSG_SYM_SET_TMODE_CNF
        ID_MSG_SYM_RD_TMODE_REQ,ID_MSG_SYM_RD_TMODE_CNF
 REQ  : SYM_SET_TMODE_REQ_STRU,SYM_RD_TMODE_REQ_STRU
 CNF  : SYM_SET_TMODE_CNF_STRU,SYM_RD_TMODE_CNF_STRU
 IND  : NA
  :
*****************************************************************************/
enum
{
    EN_SYM_TMODE_SIGNAL = 0,
    EN_SYM_TMODE_NONESIGNAL,
    EN_SYM_TMODE_LOAD,
    EN_SYM_TMODE_RESET,
    EN_SYM_TMODE_SHUTDOWN,
    EN_SYM_TMODE_SIGNAL_NOCARD  = 11,

    EN_SYM_TMODE_OFFLINE        = 12,
    EN_SYM_TMODE_F_NONESIGNAL   = 13,   /*TMODE=613*/

    EN_SYM_TMODE_SYN_NONESIGNAL = 14,   /*LTE */
    EN_SYM_TMODE_SET_SLAVE       = 15,
    EN_SYM_TMODE_GU_BT              = 16,
    EN_SYM_TMODE_TDS_FAST_CT        = 17,
    EN_SYM_TMODE_TDS_BT             = 18,
    EN_SYM_TMODE_COMM_CT            = 19,
    EN_SYM_TMODE_UNKNOWN = 0xffffffff
} ;
typedef VOS_UINT32 SYM_TMODE_ENUM;


enum
{
    EN_SYM_TMODE_STA_DOING = 0,
    EN_SYM_TMODE_STA_OK,
    EN_SYM_TMODE_STA_ERR,
    EN_SYM_TMODE_STA_UNKNOWN = 0xffffffff
};
typedef VOS_UINT32 SYM_TMODE_STA_ENUM;

/* */
typedef struct
{
    VOS_UINT8 ucWCDMAIsSet;      /*1,IsSet; 0,notSet;*/
    VOS_UINT8 ucCDMAIsSet;
    VOS_UINT8 ucTDSCDMAIsSet;
    VOS_UINT8 ucGSMIsSet;
    VOS_UINT8 ucEDGEIsSet;
    VOS_UINT8 ucAWSIsSet;
    VOS_UINT8 ucFDDLTEIsSet;
    VOS_UINT8 ucTDDLTEIsSet;
    VOS_UINT8 ucWIFIIsSet;
    VOS_UINT8 ucRsv1;
    VOS_UINT8 ucRsv2;
    VOS_UINT8 ucRsv3;
}AT_TMODE_RAT_FLAG_STRU;

/*AT^PLATFORM?*/
typedef struct
{
    VOS_UINT16 usProvider;
    VOS_UINT16 usSubPlatForm;
}AT_PLATFORM_NV_STRU;

/* */
typedef struct
{
    /*  TODO: ... (/00149739/2010-05-07)*/
    SYM_TMODE_ENUM   enTmodeMode;
} SYM_SET_TMODE_REQ_STRU;

typedef struct
{
    /*  TODO: ... (/00149739/2010-05-07)*/
    SYM_TMODE_ENUM   enTmodeMode;      /* */
    SYM_TMODE_STA_ENUM  enSymTmodeSta; /* */

    /* ERR_SUCCESS(0):*/
    /* 1:*/
    /* 2:*/
    /* 3:*/
    /* 4:*/
    /* 5:*/
    VOS_UINT32 ulErrCode;                   /* ERR_SUCCESS:OTHER:*/
} SYM_SET_TMODE_CNF_STRU;

/* */
typedef struct
{
    VOS_UINT32 ulReserved; /* */
} SYM_RD_TMODE_REQ_STRU;

typedef struct
{
    VOS_UINT32 ulTmode;
	VOS_UINT32 ulCnfRet;
}AT_TMODE_RESULT_STRU;


typedef SYM_SET_TMODE_CNF_STRU SYM_RD_TMODE_CNF_STRU;

/*****************************************************************************
  : ^FAGC RSRP
 ID   : ID_MSG_FTM_RD_FAGC_REQ,ID_MSG_FTM_RD_FAGC_CNF
 REQ  : FTM_RD_FAGC_REQ_STRU
 CNF  : FTM_RD_FAGC_CNF_STRU
 IND  : NA
  :
*****************************************************************************/

/* */
typedef struct
{
    VOS_UINT32 ulReserved; /* */
} FTM_RD_FAGC_REQ_STRU;

typedef struct
{
    VOS_INT16 sRsrp; /* */
    VOS_UINT16 usRsd;

    /* ERR_MSP_SUCCESS */
    /* */
    /* */
    VOS_UINT32 ulErrCode;
} FTM_RD_FAGC_CNF_STRU;


 /* */
 typedef struct
{
  VOS_UINT16  min_value;
  VOS_UINT16  max_value;
}MSP_VBAT_CALIBART_TYPE;


/*****************************************************************************
  : ^F 
 ID   : ID_MSG_SYM_ATF_REQ,ID_MSG_SYM_ATF_CNF
 REQ  : SYM_ATF_REQ_STRU,
 CNF  : SYM_ATF_CNF_STRU
 IND  : NA
  :
*****************************************************************************/
typedef struct
{
    VOS_UINT32 ulFpara; /* */
} SYM_ATF_REQ_STRU;

typedef struct
{
    VOS_UINT32 ulErrCode;   /* ERR_SUCCESS:OTHER:*/
} SYM_ATF_CNF_STRU;


/*****************************************************************************

 FTM

*****************************************************************************/

/* 
 
 
 typedef enum _FTM_ERR_ENUM
 {
      0: 
     EN_FTM_UEMODE_ERR = 0,

      
     EN_FTM_UNSETCH_ERR,

      
     EN_FTM_RX_OPEN_ERR,

      
     EN_FTM_TX_OPEN_ERR,

      
     EN_FTM_TX_OPEN_ERR,

      
     EN_FTM_TXON_PA_OPEN,
     EN_FTM_TXON_UNKNOWN = 0xFFFFFFFF
 } FTM_ERR_ENUM;*/

/*****************************************************************************
  : ^FTXON 
 ID   : ID_MSG_FTM_SET_TXON_REQ,ID_MSG_FTM_SET_TXON_CNF
        ID_MSG_FTM_RD_TXON_REQ,ID_MSG_FTM_RD_TXON_CNF
 REQ  : FTM_SET_TXON_REQ_STRU,FTM_RD_TXON_REQ_STRU
 CNF  : FTM_SET_TXON_CNF_STRU,FTM_RD_TXON_CNF_STRU
 IND  : NA
  :
*****************************************************************************/

/* TXON*/
enum
{
    /* 0:*/
    EN_FTM_TXON_CLOSE = 0,

    /* 1:RF*/
    EN_FTM_TXON_UL_RFBBP_OPEN,

    /* 2:RFIC TransmitterPA */
    /* BBVCTCXO*/
    EN_FTM_TXON_RF_PA_OPEN,
    EN_FTM_TXON_UNKNOWN = 0xFFFFFFFF
};
typedef VOS_UINT32 FTM_TXON_SWT_ENUM;

typedef struct
{
    VOS_UINT32 ulReserved;
}FTM_RD_FPLLSTATUS_REQ_STRU;

typedef struct
{
    VOS_UINT16 tx_status;
    VOS_UINT16 rx_status;
    VOS_UINT32 ulErrCode;
}FTM_RD_FPLLSTATUS_CNF_STRU;



/* SET*/
typedef struct
{
    FTM_TXON_SWT_ENUM enSwtich;

} FTM_SET_TXON_REQ_STRU;

typedef struct
{
    /* ERR_SUCCESS(0):*/
    /* 1:*/
    /* 2:*/
    /* 3:*/
    /* 4:*/
    /* 5:*/
    VOS_UINT32 ulErrCode;
} FTM_SET_TXON_CNF_STRU;

/* READ*/
typedef struct
{
    VOS_UINT32 ulReserved; /* */
} FTM_RD_TXON_REQ_STRU;

typedef struct
{
    FTM_TXON_SWT_ENUM enSwtich;

    /* ERR_SUCCESS(0):*/
    /* 1:*/
    /* 2:*/
    /* 3:*/
    /* 4:*/
    /* 5:*/
    VOS_UINT32 ulErrCode;
} FTM_RD_TXON_CNF_STRU;

/*****************************************************************************
  : ^FCHAN 
 ID   : ID_MSG_FTM_SET_FCHAN_REQ,ID_MSG_FTM_SET_FCHAN_CNF
        ID_MSG_FTM_RD_FCHAN_REQ,ID_MSG_FTM_RD_FCHAN_CNF
 REQ  : FTM_SET_FCHAN_REQ_STRU,FTM_SET_FCHAN_CNF_STRU
 CNF  : FTM_RD_FCHAN_REQ_STRU,FTM_RD_FCHAN_CNF_STRU
 IND  : NA
  :
*****************************************************************************/

enum _FCHAN_MODE_ENUM
{
    EN_FCHAN_MODE_WCDMA = 0,
    EN_FCHAN_MODE_CDMA,
    EN_FCHAN_MODE_TD_SCDMA,
    EN_FCHAN_MODE_TD_GSM,
    EN_FCHAN_MODE_TD_EDGE,
    EN_FCHAN_MODE_TD_AWS,
    EN_FCHAN_MODE_FDD_LTE,
    EN_FCHAN_MODE_TDD_LTE,
    EN_FCHAN_MODE_TD_SELF_DIFINE,
    EN_FCHAN_MODE_UNKONWN = 0xFF
} ;
typedef VOS_UINT32 FCHAN_MODE_ENUM;

/* */
#define FTM_AT_FCHAN_BAND    (8)		/* 800M*/
#define FTM_AT_FCHAN_BAND_MAX (14)
#define FTM_DSP_FCHAN_BAND   (20)       /* 800M*/

/* SET*/
typedef struct
{
    FCHAN_MODE_ENUM enFchanMode;
    VOS_UINT16 usChannel;
    VOS_UINT8 ucBand;
    VOS_UINT8 ucPadding;
    VOS_UINT16 usListeningPathFlg;
    VOS_UINT16 usReserved;
} FTM_SET_FCHAN_REQ_STRU;

typedef struct
{
    /* ERR_SUCCESS(0):*/
    /* 1:*/
    /* 2:*/
    /* 3:*/
    /* 4:*/
    /* 5:*/
    FCHAN_MODE_ENUM enFchanMode;
    VOS_UINT32 ulErrCode;
} FTM_SET_FCHAN_CNF_STRU;

/* READ*/
typedef struct
{
    VOS_UINT32 ulReserved; /* */
} FTM_RD_FCHAN_REQ_STRU;

#define MSP_FTM_FREQ_VALID   (1)
#define MSP_FTM_FREQ_INVALID (0)

typedef struct
{
    FCHAN_MODE_ENUM enFchanMode;
    VOS_UINT8 ucBand;
    VOS_UINT8 ucPadding[3]; /* PADDING*/

    /* AT, */
    VOS_UINT16 usUlChannel;
    VOS_UINT16 usDlChannel;

    /* ERR_SUCCESS(0):*/
    /* 1:*/
    /* 2:*/
    /* 3:*/
    /* 4:*/
    /* 5:*/
    VOS_UINT32 ulErrCode;
} FTM_RD_FCHAN_CNF_STRU;

/*****************************************************************************
  : ^FVCTCXO VCTCXO
 ID   : ID_MSG_FTM_SET_FVCTCXO_REQ,ID_MSG_FTM_SET_FVCTCXO_CNF
        ID_MSG_FTM_RD_FVCTCXO_REQ,ID_MSG_FTM_RD_FVCTCXO_CNF
 REQ  : FTM_SET_FVCTCXO_REQ_STRU,FTM_RD_FVCTCXO_REQ_STRU
 CNF  : FTM_SET_FVCTCXO_CNF_STRU,FTM_RD_FVCTCXO_CNF_STRU
 IND  : NA
  :
*****************************************************************************/

#define FTM_CALPDDCS_EXECUTING (1) /* IP2 */
#define FTM_CALPDDCS_EXECUTED (0)  /* IP2 */

typedef struct
{
    VOS_UINT16 ulPdAutoFlg;  /*065535*/
    VOS_UINT16 usRsv;     /**/
} FTM_SET_F_FCALPDDCS_REQ_STRU;
typedef struct
{
    /*U32_T ulMsgID;	ID*/
    VOS_UINT16 usDacCfg;    		/*DAC*/
    VOS_UINT16 usVgaCfg;   	/*VGA*/
    VOS_UINT16 usStatus;	 /*VGA*/
    VOS_UINT16 usRsv;
    /*
    ERR_SUCCESS(0):
    526    ()
    527    
    545    
    566    
    501    
    */
    VOS_UINT32 ulErrCode;
} FTM_RD_F_FCALPDDCS_CNF_STRU;
//SET
typedef struct
{
    VOS_UINT32 ulPdEnbFlg;               /*PD*/
    VOS_UINT16 usDacCfg;
    VOS_UINT16 usVgaCfg;
}FTM_SET_F_FPDPOWS_REQ_STRU;
typedef struct
{
	VOS_UINT32 ulErrCode;
}FTM_SET_F_FPDPOWS_CNF_STRU;

typedef struct
{
    VOS_UINT16 ulErrCode;						/* */
    VOS_UINT16 usRsv;
    VOS_UINT16 ausPDDCValue[CT_F_FREQ_LIST_MAX_NUM][RSSI_POW_MAX_NUM];
}FTM_RD_FQPDDCRES_CNF_STRU;

/*****************************************************************************
  : RXON 
 ID   : ID_MSG_FTM_SET_RXON_REQ,ID_MSG_FTM_SET_RXON_CNF
        ID_MSG_FTM_RD_RXON_REQ,ID_MSG_FTM_RD_RXON_CNF
 REQ  : FTM_SET_RXON_REQ_STRU,FTM_RD_RXON_REQ_STRU
 CNF  : FTM_SET_RXON_CNF_STRU,FTM_RD_RXON_CNF_STRU
 IND  : NA
  :
*****************************************************************************/

/* RXON */
enum
{
    EN_FTM_RXON_CLOSE   = 0,         /*      */
    EN_FTM_RXON_OPEN    = 1,         /*      */
    EN_FTM_RXON_UNKNOWN = 0xFFFFFFFF /*  */
};
typedef VOS_UINT32 FTM_RXON_SWT_ENUM;

/* SET*/
typedef struct
{
    /* 0: */
    /* 1: */
    VOS_UINT32 ulRxSwt;
} FTM_SET_RXON_REQ_STRU;

typedef struct
{
    /* ERR_SUCCESS(0):*/
    /* 1:*/
    /* 2:*/
    /* 3:*/
    VOS_UINT32 ulErrCode;
} FTM_SET_RXON_CNF_STRU;

/* READ*/
typedef struct
{
    VOS_UINT32 ulResved;
} FTM_RD_RXON_REQ_STRU;

typedef struct
{
    /* 0: */
    /* 1: */
    VOS_UINT32 ulRxSwt;

    /* ERR_SUCCESS(0):*/
    /* 1:*/
    /* 2:*/
    /* 3:*/
    VOS_UINT32 ulErrCode;
} FTM_RD_RXON_CNF_STRU;

/*****************************************************************************
  : ^RFANT RF
        RXRTTRSSI
 ID   : ID_MSG_FTM_SET_RXANT_REQ,ID_MSG_FTM_SET_RXANT_CNF
        ID_MSG_FTM_RD_RXANT_REQ,ID_MSG_FTM_RD_RXANT_CNF
 REQ  : FTM_SET_RXANT_REQ_STRU,FTM_RD_RXANT_REQ_STRU
 CNF  : FTM_SET_RXANT_CNF_STRU,FTM_RD_RXANT_CNF_STRU
 IND  : NA
  :
*****************************************************************************/

#define FTM_RXANT_TYPE_TX          (0)
#define FTM_RXANT_TYPE_RX          (1)
#define FTM_RXANT_TYPE_UNKNOWN     (0xff)

#define FTM_RXANT_CLOSE_DCHAN     (0)
#define FTM_RXANT_OPEN_CHAN1      (1)
#define FTM_RXANT_OPEN_CHAN2      (2)
#define FTM_RXANT_OPEN_DCHAN      (3)
#define FTM_RXANT_UNKNOWN         (0xff)

/* for AT^TSELRF  */
#define FTM_TSELRF_TD    (6)

#define FTM_TSELRF_WIFI           (7)
#define FTM_TSELRF_FDD_LTE_MAIN   (9)
#define FTM_TSELRF_FDD_LTE_SUB    (10)
#define FTM_TSELRF_FDD_LTE_MIMO   (11)
#define FTM_TSELRF_TDD_LTE_MAIN   (12)
#define FTM_TSELRF_TDD_LTE_SUB    (13)
#define FTM_TSELRF_TDD_LTE_MIMO   (14)

/* SET*/
typedef struct
{
    /* 0 */
    /* 1 */
    VOS_UINT8 ucChanelType;

    /* 0 */
    /* 1 1*/
    /* 2 2*/
    /* 3 */
    VOS_UINT8 ucChanelNo;
    VOS_UINT16 usReserved;
} FTM_SET_RXANT_REQ_STRU;

typedef struct
{
    /* ERR_SUCCESS(0):*/
    /* 1:*/
    /* 2:*/
    /* 3:2DD8001T2R*/
    /* 4:*/
    VOS_UINT32 ulErrCode;
} FTM_SET_RXANT_CNF_STRU;

/* READ*/
typedef struct
{
    VOS_UINT32 ulReserved;
} FTM_RD_RXANT_REQ_STRU;

typedef struct
{
    VOS_UINT8 ucChanelNo;
    VOS_UINT8 padding[3];

    /* ERR_SUCCESS(0):*/
    /* 1:*/
    /* 2:*/
    /* 3:2DD8001T2R*/
    /* 4:*/
    VOS_UINT32 ulErrCode;
} FTM_RD_RXANT_CNF_STRU;

/******************************************************************************/
/*AT^TSELRF*/
/******************************************************************************/
/* SET*/
typedef struct
{
    VOS_UINT8 ucPath;

    VOS_UINT8 ucGroup;

    VOS_UINT16 usReserved;
} FTM_SET_TSELRF_REQ_STRU;

typedef struct
{
    /* ERR_SUCCESS(0):*/
    /* 1:*/
    /* 2:*/
    /* 3:2DD8001T2R*/
    /* 4:*/
    VOS_UINT32 ulErrCode;
} FTM_SET_TSELRF_CNF_STRU;

/* READ*/
typedef struct
{
    VOS_UINT32 ulReserved;
} FTM_RD_TSELRF_REQ_STRU;

typedef struct
{
    VOS_UINT8 ucPath;
    VOS_UINT8 ucGroup;
    VOS_UINT16 usRsv;

    /* ERR_SUCCESS(0):*/
    /* 1:*/
    /* 2:*/
    /* 3:2DD8001T2R*/
    /* 4:*/
    VOS_UINT32 ulErrCode;
} FTM_RD_TSELRF_CNF_STRU;



/* SET*/
typedef struct
{
    /* 8-74*/
    VOS_UINT8 ucLevel;
    VOS_UINT8 padding[3];
} FTM_SET_FPA_REQ_STRU;

typedef struct
{
    /* ERR_SUCCESS(0):*/
    /* 1:*/
    /* 2:*/
    /* 3:AAGC*/
    /* 4:*/
    VOS_UINT32 ulErrCode;
} FTM_SET_FPA_CNF_STRU;


/* SET*/
typedef struct
{
    /* 8-74*/
    VOS_UINT16 usTxControlNum;
    VOS_UINT16 padding;
} FTM_SET_FDAC_REQ_STRU;

typedef struct
{
    /* ERR_SUCCESS(0):*/
    /* 1:*/
    /* 2:*/
    /* 3:AAGC*/
    /* 4:*/
    VOS_UINT32 ulErrCode;
} FTM_SET_FDAC_CNF_STRU;

/*****************************************************************************
  : ^FWAVE  0.01db
 ID   : ID_MSG_FTM_SET_FWAVE_REQ ID_MSG_FTM_SET_FWAVE_CNF
        ID_MSG_FTM_RD_FWAVE_REQ  ID_MSG_FTM_RD_FWAVE_CNF
 REQ  : FTM_SET_FWAVE_REQ_STRU,  FTM_RD_FWAVE_REQ_STRU
 CNF  : FTM_SET_FWAVE_CNF_STRU,  FTM_RD_FWAVE_CNF_STRU
 IND  : NA
  :
******************************************************************************/
enum _FWAVE_TYPE_ENUM
{
    EN_FWAVE_TYPE_CW    = 0, /*          */
    EN_FWAVE_TYPE_WCDMA,     /*  WCDMA */
    EN_FWAVE_TYPE_GSM,       /*  GSM   */
    EN_FWAVE_TYPE_EDGE,      /*  EDGE  */
    EN_FWAVE_TYPE_WIFI,      /*  WIFI  */
    EN_FWAVE_TYPE_LTE,       /*  LTE   */
    EN_FWAVE_TYPE_CDMA,      /*  CDMA  */
    EN_FWAVE_TYPE_TDS,       /*  TDS   */
    EN_FWAVE_TYPE_UNKONWN = 0xFFFF
} ;
typedef VOS_UINT32 FWAVE_TYPE_ENUM;


// SET
typedef struct
{
    VOS_UINT16 usType; /*  */
    VOS_UINT16 usPower;/*   */
}FTM_SET_FWAVE_REQ_STRU;

typedef struct
{
    VOS_UINT32 ulErrCode;
}FTM_SET_FWAVE_CNF_STRU;

// READ
typedef struct
{
    VOS_UINT32 ulReserved;
}FTM_RD_FWAVE_REQ_STRU;

typedef struct
{
    VOS_UINT16 usType; /*  */
    VOS_UINT16 usPower;/*   */
}FTM_RD_FWAVE_CNF_STRU;

/*****************************************************************************
  : ^FLNA RFICAAGCAGCdB
        RTTRFIC
 ID   : ID_MSG_FTM_SET_AAGC_REQ,ID_MSG_FTM_SET_AAGC_CNF
        ID_MSG_FTM_RD_AAGC_REQ,ID_MSG_FTM_RD_AAGC_CNF
 REQ  : FTM_SET_AAGC_REQ_STRU,FTM_RD_AAGC_REQ_STRU
 CNF  : FTM_SET_AAGC_CNF_STRU,FTM_RD_AAGC_CNF_STRU
 IND  : NA
  :
*****************************************************************************/

/* SET*/
typedef struct
{
    /* 8-74*/
    VOS_UINT8 ucAggcLvl;
    VOS_UINT8 padding[3];
} FTM_SET_AAGC_REQ_STRU;

typedef struct
{
    /* ERR_SUCCESS(0):*/
    /* 1:*/
    /* 2:*/
    /* 3:AAGC*/
    /* 4:*/
    VOS_UINT32 ulErrCode;
} FTM_SET_AAGC_CNF_STRU;

/* READ*/
typedef struct
{
    VOS_UINT32 ulReserved;
} FTM_RD_AAGC_REQ_STRU;


typedef struct
{
    /* 8-74*/
    VOS_UINT8 ucAggcLvl;
    VOS_UINT8 padding[3];

    /* ERR_SUCCESS(0):*/
    /* 1:*/
    /* 2:*/
    /* 3:AAGC*/
    /* 4:*/
    VOS_UINT32 ulErrCode;
} FTM_RD_AAGC_CNF_STRU;

/*****************************************************************************
AT^TBAT
*****************************************************************************/
typedef struct
{
    VOS_UINT8  ucType;
    VOS_UINT8  ucOpr;
    VOS_UINT16 usValueMin;
	VOS_UINT16 usValueMax;
	VOS_UINT16 usRsv;

}FTM_SET_TBAT_REQ_STRU;

typedef struct
{
    VOS_UINT32 ulErrCode;
}FTM_SET_TBAT_CNF_STRU;

typedef struct
{
    VOS_UINT8 ucType;
    VOS_UINT8 ucOpr;
    VOS_UINT16 usValue;
}FTM_RD_TBAT_REQ_STRU;

typedef struct
{
    VOS_UINT8 ucType;
    VOS_UINT8 ucRsv;
    VOS_UINT16 usValue;
	VOS_UINT32 ulErrCode;
}FTM_RD_TBAT_CNF_STRU;

typedef struct
{
    VOS_UINT16 usMin;
    VOS_UINT16 usMax;
}FTM_VBAT_CALIBART_TYPE;

/**********************************************************************************/

/*****************************************************************************
     : DRV_AGENT_CBC_GET_CNF_STRU
   : The message struct get cbc state reponse.

1.        : 20120301
          : HanJiuping 00122021
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8        ulbcs;
	VOS_UINT8        ulbcl;
	VOS_UINT16       usReserved;
	VOS_UINT32       enResult;
}DRV_GET_CBC_CNF_STRU;


/*****************************************************************************
  : ^FRSSI RFICAAGCAGCdB
        RTTRFIC
 ID   : ID_MSG_FTM_FRSSI_REQ,ID_MSG_FTM_FRSSI_CNF

 REQ  : FTM_FRSSI_REQ_STRU
 CNF  : FTM_FRSSI_CNF_STRU
 IND  : NA
  :
*****************************************************************************/
typedef struct
{
    /* */
    VOS_UINT32 ulReserved;
} FTM_FRSSI_REQ_STRU;

typedef struct
{
    /* , 1/8dBm, DSP, */
    VOS_INT32 lValue1;
    VOS_INT32 lValue2;
    VOS_INT32 lValue3;
    VOS_INT32 lValue4;

    /* ERR_SUCCESS(0):*/
    /* 1:*/
    /* 2:*/
    /* 3:*/
    /* 4:*/
    /* 5:*/
    VOS_UINT32 ulErrCode;
} FTM_FRSSI_CNF_STRU;


/*****************************************************************************
  : SYMFTM

 ID   : ID_MSG_FTM_OPENCHAN_REQ,ID_MSG_FTM_OPENCHAN_CNF

 REQ  : FTM_OPENCHAN_REQ_STRU
 CNF  : FTM_OPENCHAN_CNF_STRU
 IND  : NA
  :
******************************************************************************/
/* */

/* EN_SYM_TMODE_NONESIGNAL */
/* EN_SYM_TMODE_F_NONESIGNAL */

typedef struct
{
    /* */
    /* EN_SYM_TMODE_NONESIGNAL*/
    /* EN_SYM_TMODE_F_NONESIGNAL*/
    VOS_UINT8 ucTmodeType;

    VOS_UINT8 padding[3];
} FTM_OPENCHAN_REQ_STRU;

typedef struct
{
    /* ERR_SUCCESS(0):*/
    /* 1:*/
    /* 2:*/
    /* 3:*/
    /* 4:*/
    /* 5:*/
    VOS_UINT32 ulErrCode;
} FTM_OPENCHAN_CNF_STRU;


/*****************************************************************************
  : SYMFTM

 ID   : ID_MSG_FTM_PHY_POWER_REQ,ID_MSG_FTM_PHY_POWER_CNF

 REQ  : FTM_PHY_POWER_REQ_STRU
 CNF  : FTM_PHY_POWER_CNF_STRU
 IND  : NA
  :
*****************************************************************************/
typedef struct
{
    /* */
    VOS_UINT32 ulReserved;
} FTM_PHY_POWER_REQ_STRU;

typedef struct
{
    VOS_UINT32 ulErrCode;
} FTM_PHY_POWER_CNF_STRU;


/*****************************************************************************

 FTM

******************************************************************************/


/*****************************************************************************
  : ^BANDSW Band
 ID   : ID_MSG_FTM_SET_BANDSW_REQ,ID_MSG_FTM_SET_BANDSW_CNF
        ID_MSG_FTM_RD_BANDSW_REQ,ID_MSG_FTM_RD_BANDSW_CNF
 REQ  : FTM_SET_BANDSW_REQ_STRU,FTM_RD_BANDSW_REQ_STRU
 CNF  : FTM_SET_BANDSW_CNF_STRU,FTM_RD_BANDSW_CNF_STRU
 IND  : NA
  :
****************************************************************************/

#define FTM_MAX_BAND_NUM 141
#define FTM_MAX_TDS_BAND_NUM 6

#define CT_F_TXPOW_SET_MAX_NUM             30

#define CT_F_PA_SET_MAX_NUM   (30)

#define CT_F_AAGC_SET_MAX_NUM    (30)

#define TXWAVE_TYPE_CW    (0)
#define TXWAVE_TYPE_LTE   (1)

#define START_TRIGGER_TYPE_TX   (0)
#define START_TRIGGER_TYPE_RX   (1)
#define START_TRIGGER_TYPE_TXRX (2)
#define START_TRIGGER_TYPE_MAXTX (3)

typedef struct
{
    VOS_UINT32 ulRsv;     /* */
} FTM_RD_LTESCINFO_REQ_STRU;

/*start*/
/*^SSYNC SET*/
typedef struct
{
    VOS_UINT32 ulStatus;
	VOS_UINT32 ulErrCode;
}FTM_RD_SSYNC_CNF_STRU;

typedef struct
{
    VOS_UINT32 ulBandwide;
	VOS_UINT32 ulErrCode;
}FTM_RD_STXBW_CNF_STRU;

typedef struct
{
    VOS_UINT32 ulStxChannel;
	VOS_UINT32 ulErrCode;
}FTM_RD_STXCHAN_CNF_STRU;

typedef struct
{
	VOS_UINT16 usSubFrameAssign;
	VOS_UINT16 usSubFramePattern;
	VOS_UINT32 ulErrCode;
}FTM_RD_SSUBFRAME_CNF_STRU;


/*^SPARA SET*/
typedef struct
{
    VOS_UINT16 usType;
	VOS_UINT16 usValue;
} FTM_SET_SPARA_REQ_STRU;

typedef struct
{
    VOS_UINT16 usType;
	VOS_UINT16 usValue;
	VOS_UINT32 ulErrCode;

}FTM_RD_SPARA_CNF_STRU;

typedef struct
{
    VOS_UINT32 ulTypeNum;
    FTM_RD_SPARA_CNF_STRU stSpara[32];
    VOS_UINT32 ulErrCode;
}FTM_RD_SPARA_CNF_TOTAL_STRU;

typedef struct
{
    VOS_UINT16 usSegNum;
	VOS_UINT16 usReserved;
	VOS_UINT32 ulErrCode;
}FTM_RD_SSEGNUM_CNF_STRU;

typedef struct
{
    VOS_UINT16 usmodulution_num;
	VOS_UINT16 usRsv;
	VOS_UINT16 usmodulation_list[256];
	VOS_UINT32 ulErrCode;
}FTM_RD_STXMODUS_CNF_STRU;

typedef struct
{
    VOS_UINT16 usrb_num;
	VOS_UINT16 usRsv;
	VOS_UINT16 usrb_list[256];
	VOS_UINT32 ulErrCode;
}FTM_RD_STXRBNUMS_CNF_STRU;

typedef struct
{
    VOS_UINT16 usrbpos_num;
    VOS_UINT16 usRsv;
	VOS_UINT16 usrbpos_list[256];
	VOS_UINT32 ulErrCode;
}FTM_RD_STXRBPOSS_CNF_STRU;

typedef struct
{
    VOS_UINT16 uspower_num;
	VOS_UINT16 usRsv;
	VOS_INT16 uspower_list[256];
	VOS_UINT32 ulErrCode;
}FTM_RD_STXPOWS_CNF_STRU;

typedef struct
{
    VOS_UINT16 ustype_num;
	VOS_UINT16 usRsv;
	VOS_UINT16 ustype_list[256];
	VOS_UINT32 ulErrCode;
}FTM_RD_STXCHANTYPES_CNF_STRU;

typedef struct
{
    VOS_UINT16 ussegment_len;
	VOS_UINT16 usReserved;
	VOS_UINT32 ulErrCode;
}FTM_RD_SSEGLEN_CNF_STRU;

typedef struct
{
    VOS_UINT16 usSwitch;/* 01*/
    VOS_INT16 sPower; /*-40~23*/
    VOS_UINT16 usMod;/* 0-2 ,0:QPSK,1:16QAM,2:64QAM*/
	VOS_UINT16 usRBNum; /* RB1-100*/
    VOS_UINT16 usRBPos;/*RB0-99*/
	VOS_UINT16 usReserved;
	VOS_UINT32 ulErrCode;
}FTM_RD_SRXSET_CNF_STRU;

/*^SRXPOW SET*/
typedef struct
{
    VOS_UINT16 usSwitch;
	VOS_INT16 usulPower;
	VOS_UINT16 usModuType;
	VOS_UINT16 usRbNum;
	VOS_UINT16 usRbPos;
	VOS_UINT16 usRsv;
} FTM_SET_SRXPOW_REQ_STRU;

typedef struct
{
    VOS_UINT32 ulErrCode;
}FTM_SET_SRXPOW_CNF_STRU;

/*^STXCHANTYPES RD*/
typedef struct
{
    VOS_UINT32 ulReserved;
} FTM_RD_SRXPOW_REQ_STRU;

typedef struct
{
    VOS_UINT16 usSwitch;
	VOS_INT16 usulPower;
	VOS_UINT32 ulErrCode;
}FTM_RD_SRXPOW_CNF_STRU;

typedef struct
{
    VOS_UINT16 ussubFrameNum;
	VOS_UINT16 usReserved;
	VOS_UINT32 ulErrCode;
}FTM_RD_SRXSUBFRA_CNF_STRU;

/*SRXBLER*/
/*^SRXBLER SET*/
typedef struct
{
    VOS_UINT16 usbler;
	VOS_UINT16 usReserved;
} FTM_SET_SRXBLER_REQ_STRU;

typedef struct
{
    VOS_UINT32 ulErrCode;
}FTM_SET_SRXBLER_CNF_STRU;

typedef struct
{
    VOS_UINT16 usbler[2];
	VOS_INT16 usSnr[2];
	VOS_UINT32 ulErrCode;
}FTM_RD_SRXBLER_CNF_STRU;

//TDS BER RD
typedef struct
{
    VOS_UINT32 ulbersum;
	VOS_UINT32 ulberErr;
	VOS_UINT32 ulErrCode;
}FTM_RD_STRXBER_CNF_STRU;

typedef struct
{
    VOS_UINT16 usType;
	VOS_UINT16 usStatus;
	VOS_UINT32 ulErrCode;
}FTM_RD_SSTART_CNF_STRU;


typedef struct
{
       VOS_UINT32				MsgId;
	VOS_UINT32				ulRserved;
}MSP_PS_AT_MODE_REQ_STRU;


typedef struct
{
       VOS_UINT32			   MsgId;
	VOS_UINT16                    cellID;
	VOS_UINT16                     freq;
}MSP_PS_SET_SFN_SYNC_REQ_STRU;

typedef struct
{
	VOS_UINT32		    ulMsgName;
	VOS_UINT32              ulresult;
}PS_MSP_SFN_SYNC_CNF;

typedef struct
{
       VOS_UINT32			   MsgId;
	VOS_UINT16             ulType;
	VOS_UINT16             ulRsv;
}MSP_PS_SSTOP_REQ_STRU;

typedef struct
{
    VOS_UINT32            MsgId;
	VOS_UINT32		      ulTransType;
    VOS_UINT16            ulTpcStep;
    VOS_UINT16            ulRsv;
}MSP_PS_DPCH_REQ_STRU;

typedef struct
{

	VOS_UINT32		    ulMsgName;
	VOS_UINT32		    ulStatus;
}PS_MSP_DPCH_CNF;

/*end*/


/*****************************************************************************

 DIAG

*****************************************************************************/

/*****************************************************************************
  : DIAGPSSIMM
 ID   : ID_MSG_DIAG_PSTRANS_REQ,ID_MSG_DIAG_PSTRANS_CNF,ID_MSG_DIAG_PSTRANS_IND
 REQ  : DIAG_PSTRANS_REQ_STRU
 CNF  : DIAG_PSTRANS_CNF_STRU
 IND  : DIAG_PSTRANS_IND_STRU
  :
*****************************************************************************/

typedef struct
{
    VOS_UINT32 ulCmdID;     /* */
    VOS_UINT32 ulParamSize; /* */
    VOS_UINT8  ucParam[0];  /* ,*/
} DIAG_PSTRANS_REQ_STRU;


/* DIAG<-L4A,SIMM  CNF/IND */
typedef struct
{
    VOS_UINT32 ulCmdID;      /* (CNF)  ID(IND ID)*/
    VOS_UINT32 ulParamSize;  /* */
    VOS_UINT8  ucParam[0];   /*  MSP*/
} DIAG_PSTRANS_CNF_STRU, DIAG_PSTRANS_IND_STRU;


/*****************************************************************************
  : DIAGPSSIMM
 ID   : ID_MSG_DIAG_SIMMTRANS_REQ,ID_MSG_DIAG_SIMMTRANS_CNF,ID_MSG_DIAG_SIMMTRANS_IND
 REQ  : DIAG_SIMMTRANS_REQ_STRU
 CNF  : DIAG_SIMMTRANS_CNF_STRU
 IND  : DIAG_SIMMTRANS_IND_STRU
  :
*****************************************************************************/
typedef DIAG_PSTRANS_REQ_STRU DIAG_SIMMTRANS_REQ_STRU;
typedef DIAG_PSTRANS_CNF_STRU DIAG_SIMMTRANS_CNF_STRU;
typedef DIAG_PSTRANS_IND_STRU DIAG_SIMMTRANS_IND_STRU;


/*****************************************************************************

 L1A [0x00010450,0x00010500)
******************************************************************************/

/*****************************************************************************
  : L1AFTMRTT
 ID   : ID_MSG_L1A_CT_IND
 REQ  : NA
 CNF  : NA
 IND  : SIMM_STATUS_IND_STRU
  :
*****************************************************************************/
typedef struct
{
    VOS_UINT32 ulDspId;  /* */
    VOS_UINT8 aucPadding[0];
}L1A_CT_IND_STRU;


#define  AT_CALIB_PARAM_APCOFF           6
#define  AT_CALIB_PARAM_APCOFF_MAX       8
#define  AT_CALIB_PARAM_APC              160
#define  AT_CALIB_PARAM_APCFREQ          96
#define  AT_CALIB_PARAM_AGC              32
#define  AT_CALIB_PARAM_AGCFREQ          32
#define  FTM_TDS_TX_LEVEL_NUM_MAX        3	 /*TDS TX*/
#define  FTM_TDS_RX_LEVEL_NUM_MAX		 16	 /*TDS RX*/
#define  FTM_TDS_TX_CAL_POWERNUM_MAX	 80	 /*TDS TX*/
#define  FTM_TDS_TX_CAL_FREQNUM_MAX		 16	 /*TDS TX*/
#define  FTM_TDS_RX_CAL_FREQNUM_MAX		 16	 /*TDS RX*/
#define  MAX_SCALIB_DATA_LEN             320

/*****************************************************************************
     : AT_TDS_OPT_TYPE_ENUM
   : 
*****************************************************************************/
typedef enum
{
	AT_CALIB_OP_TYPE_CACHE,    /* "CACHE",  */
	AT_CALIB_OP_TYPE_USE,      /* "USE",  DHI DSP  */
	AT_CALIB_OP_TYPE_SAVE,     /* "SAVE", NANDFLASH  */
	AT_CALIB_OP_TYPE_GET,      /* "GET",   */
	AT_CALIB_OP_TYPE_READ,     /* "READ", NANDFLASH NANDFLASH) */
	AT_CALIB_OP_TYPE_INI,      /* "INI",   */
	AT_CALIB_OP_TYPE_BEGIN,    /* "BEGIN", */
    AT_CALIB_OP_TYPE_END,      /* "END",   */
    AT_CALIB_OP_TYPE_SET,      /* "SET",  DSP */
	AT_CALIB_OP_TYPE_BUTT
}AT_TDS_OPT_TYPE_ENUM;
typedef VOS_UINT32 AT_TDS_OPT_TYPE_ENUM_U32;

/*****************************************************************************
     : AT_TDS_DATA_TYPE_ENUM
   : 
*****************************************************************************/
typedef enum
{
	AT_CALIB_BAND_TYPE_A = 1,       /* "BAND A",*/
    AT_CALIB_BAND_TYPE_E = 5,       /* "BAND E",*/
    AT_CALIB_BAND_TYPE_F = 6,       /* "BAND F",*/
	AT_CALIB_BAND_TYPE_BUTT
}AT_TDS_BAND_TYPE_ENUM;
typedef VOS_UINT32 AT_TDS_BAND_TYPE_ENUM_U32;

/*****************************************************************************
     : AT_TDS_DATA_TYPE_ENUM
   : 
*****************************************************************************/
typedef enum
{
	AT_CALIB_DATA_TYPE_APCOFFSETFLAG,   /* "APCOFFSETFLAG",*/
    AT_CALIB_DATA_TYPE_APCOFFSET,       /* "APCOFFSET",*/
    AT_CALIB_DATA_TYPE_APC,             /* "APC",*/
    AT_CALIB_DATA_TYPE_APCFREQ,         /* "APCFREQ",*/
    AT_CALIB_DATA_TYPE_AGC,             /* "AGC",*/
    AT_CALIB_DATA_TYPE_AGCFREQ,         /* "AGCFREQ",*/
	AT_CALIB_DATA_TYPE_BUTT
}AT_TDS_DATA_TYPE_ENUM;
typedef VOS_UINT32 AT_TDS_DATA_TYPE_ENUM_U32;

/*****************************************************************************
     : AT_SCALIB_SYSTEM_SETTING_STRU
   : 
*****************************************************************************/
typedef struct
{
    VOS_UINT16   flag1;  /**/
    VOS_UINT16   flag2;  /**/
}FTM_SCALIB_APCOFFSET_SETTING_STRU;

/*****************************************************************************
     : AT_SCALIB_SYSTEM_SETTING_STRU
   : 
*****************************************************************************/
typedef struct
{
    /* reserved for CQUPT begin*/
	VOS_UINT32	boardId;
	VOS_UINT16	serial[12];    /* SN*/
	VOS_UINT16  imei[5];      /* IMEI.*/
	VOS_UINT16  imeiSv[5];    /* IMEISV.*/
	VOS_UINT16  armFile[10];
	VOS_UINT16  zsp1File[10];
	VOS_UINT16  zsp2File[10];
	VOS_UINT16  tdRfTabFlag1;    /*1*/
	VOS_UINT16  reserved;
	VOS_UINT16  tdApcTab[80];    /**/
	VOS_UINT16  tdAgcTab[6];     /**/
	VOS_UINT16  tdApcOffset[6];
	VOS_UINT16  tdApcOffsetFlag;
	VOS_UINT16  tdAfcOffset;     /*AFC*/
	VOS_UINT32  tdDcOffset;      /**/
	VOS_UINT16  afcAgcDcFlag;
	VOS_UINT16  reserved1[3];
    VOS_UINT16  tdRfTabFlag2;     /*2*/
	VOS_UINT16  reserved2[3];
    /* reserved for CQUPT end*/
    /* added at 2012-6-11 begin*/
    VOS_UINT16  ApcOffFlag;
    VOS_UINT16  reserved3;
    VOS_UINT16  tdsTxPaPowerBand_A[FTM_TDS_TX_LEVEL_NUM_MAX];
    VOS_UINT16  reserved4;
    VOS_UINT16  tdsTxPaPowerBand_E[FTM_TDS_TX_LEVEL_NUM_MAX];
    VOS_UINT16  reserved5;
    VOS_UINT16  tdsTxPaPowerBand_F[FTM_TDS_TX_LEVEL_NUM_MAX];
    VOS_UINT16  reserved6;
    VOS_UINT16  tdsTxApcCompBand_A[FTM_TDS_TX_CAL_POWERNUM_MAX];
    VOS_UINT16  tdsTxApcCompBand_E[FTM_TDS_TX_CAL_POWERNUM_MAX];
    VOS_UINT16  tdsTxApcCompBand_F[FTM_TDS_TX_CAL_POWERNUM_MAX];
    VOS_UINT16  tdsTxApcFreqCompBand_A[FTM_TDS_TX_LEVEL_NUM_MAX][FTM_TDS_TX_CAL_FREQNUM_MAX];
    VOS_UINT16  tdsTxApcFreqCompBand_E[FTM_TDS_TX_LEVEL_NUM_MAX][FTM_TDS_TX_CAL_FREQNUM_MAX];
    VOS_UINT16  tdsTxApcFreqCompBand_F[FTM_TDS_TX_LEVEL_NUM_MAX][FTM_TDS_TX_CAL_FREQNUM_MAX];
    VOS_UINT16  tdsRxAgcCompBand_A[FTM_TDS_RX_LEVEL_NUM_MAX];
    VOS_UINT16  tdsRxAgcCompBand_E[FTM_TDS_RX_LEVEL_NUM_MAX];
    VOS_UINT16  tdsRxAgcCompBand_F[FTM_TDS_RX_LEVEL_NUM_MAX];
    VOS_UINT16  tdsRxAgcFreqCompBand_A[FTM_TDS_RX_CAL_FREQNUM_MAX];
    VOS_UINT16  tdsRxAgcFreqCompBand_E[FTM_TDS_RX_CAL_FREQNUM_MAX];
    VOS_UINT16  tdsRxAgcFreqCompBand_F[FTM_TDS_RX_CAL_FREQNUM_MAX];
    /* added at 2012-6-11 end*/
}FTM_SCALIB_SYSTEM_SETTING_STRU;

/* MAXPOWER NV*/
typedef struct
{
    VOS_INT16 asTxMaxPower[FTM_TDS_TX_LEVEL_NUM_MAX];
    VOS_INT16 asReserve;
}TDS_NV_PA_POWER_STRU;



typedef struct
{
    VOS_UINT16       ucPath;         /*  */
    VOS_UINT16       ucGroup;        /* path */
}TDS_SET_TSELRF_REQ_STRU;

typedef struct
{
    VOS_UINT16       usMode;         /*  */
    VOS_UINT16       usBand;         /* band */
    VOS_UINT16       usFreq;         /*  */
    VOS_UINT16       usRsv;
}TDS_SET_FCHAN_REQ_STRU;

typedef struct
{
    VOS_UINT16       usType;         /* ,0: */
    VOS_UINT16       usAmp;          /*  */
}TDS_SET_FWAVE_REQ_STRU;


typedef struct
{
    VOS_UINT16       usSwtich;       /* ,0:close;1:open */
    VOS_UINT16       usRsv;
}TDS_SET_FTXON_REQ_STRU;


typedef struct
{
    VOS_UINT16       usSwtich;       /* ,0:close;1:open */
    VOS_UINT16       usRsv;
}TDS_SET_FRXON_REQ_STRU;

typedef struct
{
    VOS_UINT32      ulRsv;
}TDS_SET_FRSSI_REQ_STRU;

typedef struct
{
    VOS_UINT32      ulErrCode;
}TDS_SET_CNF_STRU;



typedef struct
{
    VOS_INT32       lValue;         /* RSSI */
    VOS_UINT32      ulErrCode;      /*  */
}TDS_SET_FRSSI_CNF_STRU;


/*adde by yangzhi for*/
/******************************************************************************
:   TDSRF^TSELRF
ID:     ID_MSG_TDS_FRSSI_REQ,ID_MSG_TDS_FRSSI_CNF
:   ID_MSG_TDS_RD_TSELRF_REQ,ID_MSG_TDS_RD_TSELRF_CNF
******************************************************************************/
typedef struct
{
    VOS_UINT16       usChanelNo;    /* DSP  */
    VOS_UINT16       usRsv;
    VOS_UINT32       ulErrCode;      /*  */
}TDS_RD_TSELRF_CNF_STRU;


/******************************************************************************
:   TDS^FCHAN
ID:     ID_MSG_TDS_RD_FCHAN_REQ,ID_MSG_TDS_RD_FCHAN_CNF
:
******************************************************************************/
typedef struct
{
    FCHAN_MODE_ENUM enFchanMode;
    VOS_UINT16       usBand;
    VOS_UINT16       usUlFReqValid; /* DSP  */
    VOS_UINT16       usDlFreqValid; /* DSP  */
    VOS_UINT16       usUlChannel;
    VOS_UINT16       usDlChannel;
    VOS_UINT16       usRsv;
    VOS_UINT32       ulErrCode;      /*  */
}TDS_RD_FCHAN_CNF_STRU;

/******************************************************************************
:   TDS^FTXON
ID:     ID_MSG_TDS_RD_FTXON_REQ,ID_MSG_TDS_RD_FTXON_CNF
:
******************************************************************************/
typedef struct
{
    FTM_TXON_SWT_ENUM enSwtich;
    VOS_UINT32 ulErrCode;
}TDS_RD_FTXON_CNF_STRU;

/******************************************************************************
:   TDS^FRXON
ID:     ID_MSG_TDS_RD_FRXON_REQ,ID_MSG_TDS_RD_FRXON_CNF
:
******************************************************************************/
typedef struct
{
    VOS_UINT32 ulRxSwt;
    VOS_UINT32 ulErrCode;
}TDS_RD_FRXON_CNF_STRU;
#define FTM_STATUS_EXECUTING (0) /* IP2 */
#define FTM_STATUS_EXECUTED (1)  /* IP2 */

/* IP2 */
#define FTM_CALIIP2_MAX_CHAN_NUM (4)

/* DCOCAGC */
#define FTM_CALIDCOCS_AGC_NUM (16)

/* GainState */
#define FTM_GAINSTATE_MAX_NUM (60)
#define FTM_GAINSTATE_MAX_NUM_HI6362 (16*2*3) /* k3v5 */

/* DBB */
#define FTM_DBBATT_MAX_NUM FTM_GAINSTATE_MAX_NUM

/* BB */
#define FTM_BBATT_MAX_NUM FTM_GAINSTATE_MAX_NUM

/* AT^FCALIIPS */
typedef struct
{
    VOS_UINT32 ulRsv;
}FTM_RD_NOPRARA_REQ_STRU;

typedef struct
{
    VOS_UINT16 usChanNum;
    VOS_UINT16 usChan[FTM_CALIIP2_MAX_CHAN_NUM];
}FTM_SET_FCALIIP2S_REQ_STRU;

typedef struct
{
    VOS_UINT32 ulErrCode;
    VOS_UINT16 usStatus;
    VOS_UINT16 usChanNum;
    VOS_UINT16 usChan[FTM_CALIIP2_MAX_CHAN_NUM];
    VOS_UINT16 usMain_I_DivOff[FTM_CALIIP2_MAX_CHAN_NUM];
    VOS_UINT16 usMain_Q_DivOff[FTM_CALIIP2_MAX_CHAN_NUM];
    VOS_UINT16 usMain_I_DivOn[FTM_CALIIP2_MAX_CHAN_NUM];
    VOS_UINT16 usMain_Q_DivOn[FTM_CALIIP2_MAX_CHAN_NUM];
    VOS_UINT16 usDiv_I[FTM_CALIIP2_MAX_CHAN_NUM];
    VOS_UINT16 usDiv_Q[FTM_CALIIP2_MAX_CHAN_NUM];
}FTM_RD_FCALIIP2S_CNF_STRU;

/* AT^FCALIDCOCS */
typedef struct
{
	VOS_UINT16 usChannel;
	VOS_UINT16 usRsv;
}FTM_SET_FCALIDCOCS_REQ_STRU;

typedef struct
{
    VOS_UINT32 ulErrCode;
    VOS_UINT16 usStatus;
    VOS_UINT16 usChannel;
    VOS_UINT16 usNOBLK_ANT1_I[FTM_CALIDCOCS_AGC_NUM];
    VOS_UINT16 usNOBLK_ANT1_Q[FTM_CALIDCOCS_AGC_NUM];
	VOS_UINT16 usBLK_ANT1_I[FTM_CALIDCOCS_AGC_NUM];
    VOS_UINT16 usBLK_ANT1_Q[FTM_CALIDCOCS_AGC_NUM];
	VOS_UINT16 usNOBLK_ANT2_I[FTM_CALIDCOCS_AGC_NUM];
    VOS_UINT16 usNOBLK_ANT2_Q[FTM_CALIDCOCS_AGC_NUM];
	VOS_UINT16 usBLK_ANT2_I[FTM_CALIDCOCS_AGC_NUM];
    VOS_UINT16 usBLK_ANT2_Q[FTM_CALIDCOCS_AGC_NUM];
}FTM_RD_FCALIDCOCS_CNF_STRU;


/* AT^FCALIIP2SMRF */
#define FTM_CT_MAX_RFIC_PATH_NUM 2
#define FTM_CT_MAX_RX_ANT_NUM 2

typedef struct
{
    VOS_UINT16 usChanNum;
    VOS_UINT16 usBand;
    VOS_UINT16 usRfid;
    VOS_UINT16 usChan[FTM_CALIIP2_MAX_CHAN_NUM];
}FTM_SET_FCALIIP2SMRF_REQ_STRU;

typedef struct
{
    VOS_UINT16 usValidFlg;
    VOS_UINT16 usRsv;
	VOS_UINT16 usMain_I_DivOff[FTM_CALIIP2_MAX_CHAN_NUM];
	VOS_UINT16 usMain_Q_DivOff[FTM_CALIIP2_MAX_CHAN_NUM];
	VOS_UINT16 usMain_I_DivOn[FTM_CALIIP2_MAX_CHAN_NUM];
	VOS_UINT16 usMain_Q_DivOn[FTM_CALIIP2_MAX_CHAN_NUM];
	VOS_UINT16 usDiv_I[FTM_CALIIP2_MAX_CHAN_NUM];
	VOS_UINT16 usDiv_Q[FTM_CALIIP2_MAX_CHAN_NUM];
}FTM_FCALIIP2SMRF_CAL_ITEM;

typedef struct
{
    VOS_UINT32     ulErrCode;
    VOS_UINT16     usStatus;
    VOS_UINT16     usChanNum;
    VOS_UINT16     usChan[FTM_CALIIP2_MAX_CHAN_NUM];
    FTM_FCALIIP2SMRF_CAL_ITEM astIp2CalRst[FTM_CT_MAX_RFIC_PATH_NUM];
}FTM_RD_FCALIIP2SMRF_CNF_STRU;

/* AT^FCALIDCOCSMRF */
typedef struct
{
    VOS_UINT16 usChannel;	/*  */
    VOS_UINT16 usBand;      /* band   */
    VOS_UINT16 usRfid;      /*  */
    VOS_UINT16 usRsv;
}FTM_SET_FCALIDCOCSMRF_REQ_STRU;

typedef struct
{
     VOS_UINT16 usAntCompDCI[FTM_CALIDCOCS_AGC_NUM];
     VOS_UINT16 usAntCompDCQ[FTM_CALIDCOCS_AGC_NUM];
}FTM_FCALIDCOCSMRF_ANT_ITEM_STRU;

typedef struct
{
    VOS_UINT16 usValidFlg;
    VOS_UINT16 usValidAntNum;
    FTM_FCALIDCOCSMRF_ANT_ITEM_STRU   astAntCal[FTM_CT_MAX_RX_ANT_NUM];
}FTM_FCALIDCOCSMRF_DCCOMP_ITEM_STRU;

typedef struct
{
    VOS_UINT32 ulErrCode;
    VOS_UINT16 usStatus;
    VOS_UINT16 usChannel;
    FTM_FCALIDCOCSMRF_DCCOMP_ITEM_STRU  astDcocCalRst[FTM_CT_MAX_RFIC_PATH_NUM];
}FTM_RD_FCALIDCOCSMRF_CNF_STRU;


/* AT^FGAINSTATES */
typedef struct
{
    VOS_UINT16 usGainStateNum;
    VOS_UINT16 usRsv;
    VOS_UINT16 usGainState[FTM_GAINSTATE_MAX_NUM_HI6362];
}FTM_SET_FGAINSTATES_REQ_STRU;

/* AT^FDBBATTS */
typedef struct
{
    VOS_UINT16 usDbbCodeNum;
    VOS_UINT16 usDbbCode;
}FTM_SET_FDBBATTS_REQ_STRU;

/* AT^FBBATTS */
typedef struct
{
	VOS_UINT16 usBbAttNum;
	VOS_UINT16 usRsv;
	VOS_UINT16 usBbAtt[FTM_BBATT_MAX_NUM];
}FTM_SET_FBBATTS_REQ_STRU;

/* AT^FCALITXIQS */
typedef struct
{
    VOS_UINT16 usChannel;
    VOS_UINT16 usBand;
    VOS_UINT16 usRfid;
    VOS_UINT16 usRsv2;
}FTM_SET_FCALITXIQS_REQ_STRU;

typedef struct
{
	VOS_UINT32 ulErrCode;
	VOS_UINT16 usStatus;
	VOS_UINT16 usAmplitude;
	VOS_UINT16 usPhase;
	VOS_UINT16 usDCI;
	VOS_UINT16 usDCQ;
	VOS_UINT16 usReserved;
}FTM_RD_FCALITXIQS_CNF_STRU;

#define FTM_MAX_COMM_CMD_LEN 1152
typedef enum
{
    EN_LTCOMMCMD_DEST_LDSP_CT = 0,
    EN_LTCOMMCMD_DEST_LDSP_BT = 1,
    EN_LTCOMMCMD_DEST_TDSP_CT = 2,
    EN_LTCOMMCMD_DEST_TDSP_BT = 3,
}FTM_LTCOMMCMD_DEST;

typedef struct
{
    FTM_LTCOMMCMD_DEST ulCmdDest;
    VOS_UINT32 ulDataLen;
    VOS_CHAR   cData[0];
}FTM_SET_LTCOMMCMD_REQ_STRU;

typedef struct
{
    VOS_UINT32 ulErrCode;
    VOS_UINT32 ulDataLen;
    VOS_CHAR   cData[0];
}FTM_SET_LTCOMMCMD_CNF_STRU;

typedef struct
{
    VOS_UINT32 ulErrCode;
    VOS_UINT32 ulDataLen;
    VOS_CHAR   cData[1152]; /* LMspLPhyInterface.hMAX_COMM_CMD_LEN */
}FTM_RD_LTCOMMCMD_CNF_STRU;

typedef struct
{
    VOS_UINT32 ulMsgId;                  /*  */
    VOS_UINT32 ulDataLen;                /*  */
    VOS_UINT8   cData[0];   /*      */
}FTM_PHY_COMM_CMD_SET_REQ_STRU;

typedef struct
{
    VOS_UINT32 ulMsgId;                  /*  */
    VOS_UINT32 ulDataLen;                /*  */
    VOS_UINT8   cData[0];   /*      */
}PHY_FTM_COMM_CMD_SET_CNF_STRU;

typedef PHY_FTM_COMM_CMD_SET_CNF_STRU PHY_FTM_COMM_CMD_IND_STRU;



typedef struct
{
	VOS_MSG_HEADER																/* _H2ASN_Skip */
	APS_L4A_MSG_ID_ENUM_UINT32			enMsgId;								/* _H2ASN_Skip */

	APS_L4A_APPCTRL_STRU				stCtrl;
} L4A_COMM_REQ_STRU;
typedef L4A_COMM_REQ_STRU L4A_READ_LWCLASH_REQ_STRU;

typedef struct
{
	VOS_UINT16		 usUlFreq;			/*:100Khz*/
	VOS_UINT16		 usDlFreq;			/* :100Khz*/
	VOS_UINT16		 usUlBandwidth; 	/* */
	VOS_UINT16		 usDlBandwidth; 	/* */
	VOS_UINT8		 enCamped;			/* */
	VOS_UINT8		 enState;			/* */
	VOS_UINT8		 usBand;			/* */
	VOS_UINT8		 aucResv[1];
} L4A_LWCLASH_INFO_STRU;

typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32          				enMsgId;                                /* _H2ASN_Skip */

    VOS_UINT16                          usClientId;                             /* ID */
    VOS_UINT8                           ucOpId;
    VOS_UINT8		 					aucResv[1];
    VOS_UINT32                          ulErrorCode;

    L4A_LWCLASH_INFO_STRU               stLwclashInfo;
    VOS_UINT32                          ulScellNum;
    RRC_APP_SCELL_INFO_STRU             stScellInfo[LRRC_APP_LWCLASH_MAX_SCELL_NUM];
} L4A_READ_LWCLASH_CNF_STRU;

typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32          				enMsgId;                                /* _H2ASN_Skip */

    VOS_UINT16                          usClientId;                             /* ID */
    VOS_UINT8                           ucOpId;                                 /* ID */
    VOS_UINT8                           aucResv[1];                                  /* CID      */
    L4A_LWCLASH_INFO_STRU stLwclashInfo;
    VOS_UINT32                          ulScellNum;
    RRC_APP_SCELL_INFO_STRU             stScellInfo[LRRC_APP_LWCLASH_MAX_SCELL_NUM];
} L4A_READ_LWCLASH_IND_STRU;

typedef L4A_COMM_REQ_STRU L4A_READ_LCACELL_REQ_STRU;

typedef struct
{
    VOS_UINT8       ucUlConfigured;     /*CA0:1:*/
    VOS_UINT8       ucDlConfigured;     /*CA0:1:*/
    VOS_UINT8       ucActived;          /*SCell0:1:*/
    VOS_UINT8       ucRsv;
}L4A_CACELL_INFO_STRU;

typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    APS_L4A_MSG_ID_ENUM_UINT32          enMsgId;                                /* _H2ASN_Skip */

    VOS_UINT16                          usClientId;                             /* ID */
    VOS_UINT8                           ucOpId;
    VOS_UINT8		 					aucResv[1];
    VOS_UINT32                          ulErrorCode;

	L4A_CACELL_INFO_STRU                stLcacellInfo[CA_MAX_CELL_NUM];
} L4A_READ_LCACELL_CNF_STRU;

typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    APS_L4A_MSG_ID_ENUM_UINT32          enMsgId;                                /* _H2ASN_Skip */

    VOS_UINT16                          usClientId;                             /* ID */
    VOS_UINT8                           ucOpId;                                 /* ID */
    VOS_UINT8		 					aucResv[1];                             /* CID      */
	L4A_CACELL_INFO_STRU                stLcacellInfo[CA_MAX_CELL_NUM];
} L4A_READ_LCACELL_IND_STRU;



/*begin_added by c64416 for lte wifi 20131013*/
/******************************************************************************
:   ^ISMCOEX
ID:
:
******************************************************************************/
#define     L4A_ISMCOEX_BANDWIDTH_NUM       6

typedef struct
{
    VOS_UINT32              ulFlag;
    VOS_UINT32              ulTXBegin;
    VOS_UINT32              ulTXEnd;
    VOS_INT32               lTXPower;
    VOS_UINT32              ulRXBegin;
    VOS_UINT32              ulRXEnd;
} ISMCOEX_INFO_STRU;

typedef struct
{
	VOS_MSG_HEADER
	APS_L4A_MSG_ID_ENUM_UINT32			enMsgId;

	APS_L4A_APPCTRL_STRU				stCtrl;

    ISMCOEX_INFO_STRU                   astCoex[L4A_ISMCOEX_BANDWIDTH_NUM];
} L4A_ISMCOEX_REQ_STRU;

typedef struct
{
    VOS_MSG_HEADER
    APS_L4A_MSG_ID_ENUM_UINT32          enMsgId;

    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpId;
    VOS_UINT8		 					aucResv[1];
    VOS_UINT32                          ulErrorCode;
} L4A_ISMCOEX_CNF_STRU;

/*end_added by c64416 for lte wifi 20131013*/

typedef L4A_COMM_REQ_STRU L4A_READ_LTECS_REQ_STRU;

typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    APS_L4A_MSG_ID_ENUM_UINT32          enMsgId;                                /* _H2ASN_Skip */

    VOS_UINT16                          usClientId;                             /* ID   */
    VOS_UINT8                           ucOpId;                                 /* ID   */
    VOS_UINT8                           aucReserved[1];
    VOS_UINT32                          ulErrorCode;                            /*      */

	APP_MM_LTE_CS_INFO_STRU				stLtecsInfo;
} L4A_READ_LTECS_CNF_STRU;

typedef struct
{
	VOS_MSG_HEADER																/* _H2ASN_Skip */
	APS_L4A_MSG_ID_ENUM_UINT32			enMsgId;								/* _H2ASN_Skip */

	APS_L4A_APPCTRL_STRU				stCtrl;
    VOS_UINT8 n;
    VOS_UINT8 ucReserved[3];
}L4A_READ_CNMR_REQ_STRU;

typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    APS_L4A_MSG_ID_ENUM_UINT32          enMsgId;                                /* _H2ASN_Skip */

    VOS_UINT16                          usClientId;                             /* ID   */
    VOS_UINT8                           ucOpId;                                 /* ID   */
    VOS_UINT8                           aucReserved[1];
    VOS_UINT32                          ulErrorCode;                            /*      */
    RRC_APP_LTE_CELL_INFO_STRU          stLteCelInfo;
}L4A_READ_CNMR_CNF_STRU;

typedef struct
{
	VOS_MSG_HEADER																/* _H2ASN_Skip */
	APS_L4A_MSG_ID_ENUM_UINT32			enMsgId;								/* _H2ASN_Skip */

	APS_L4A_APPCTRL_STRU				stCtrl;
    VOS_UINT8 							ucnDb;
    VOS_UINT8 							ucMinRptTimerInterval;
    VOS_UINT8 							ucReserved[2];
} L4A_CSQ_INFO_REQ_STRU;

typedef struct
{
	VOS_MSG_HEADER																/* _H2ASN_Skip */
	APS_L4A_MSG_ID_ENUM_UINT32			enMsgId;								/* _H2ASN_Skip */

	VOS_UINT16							usClientId; 							/* ID   */
	VOS_UINT8							ucOpId; 								/* ID   */
	VOS_UINT8							aucReserved[1];
	VOS_UINT32							ulErrorCode;							/* 	  */

	VOS_INT16 	sRssi;				/* Rssi*/
	VOS_INT16 	sRsd; 	   			/* */
	VOS_INT16 	sRsrp;			  	/* (-141,-44), 99 */
	VOS_INT16 	sRsrq;			  	/* (-40, -6) , 99 */
	VOS_INT32  	lSINR;			   	/* SINR	RS_SNR */
    APP_RRC_CQI_INFO_STRU               stCQI;              /* CQI */
}L4A_CSQ_INFO_CNF_STRU;

typedef L4A_CSQ_INFO_CNF_STRU L4A_CSQ_INFO_IND_STRU;

typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    APS_L4A_MSG_ID_ENUM_UINT32          enMsgId;                                /* _H2ASN_Skip */

    VOS_UINT16                          usClientId;                             /* ID   */
    VOS_UINT8                           ucOpId;                                 /* ID   */
    VOS_UINT8                           aucReserved[1];
    VOS_UINT32                          ulErrorCode;                            /*      */

    VOS_INT16   sRssi;              /* Rssi*/
    VOS_INT16   sLevel;             /* */
    VOS_INT16   sRsrp;              /* (-141,-44), 99 */
    VOS_INT16   sRsrq;              /* (-40, -6) , 99 */
}AT_ANLEVEL_INFO_CNF_STRU;


#define L4A_CURC_RPT_CFG_MAX_SIZE        (8)
typedef struct
{
    VOS_UINT32  mode_bit_valid	:1 ;/*save mode set command-- 1:valid 0:invalid*/
	VOS_UINT32  mode_bit	:1 ;    /*save mode set command-- 1:open 0:close*/
	VOS_UINT32  lwurc_bit_valid	:1 ;/*save lwclash set command- 1:valid 0:invalid*/
	VOS_UINT32  lwurc_bit	:1 ;    /*save lwclash set command- 1:open 0:close*/
	VOS_UINT32  cerssi_bit_valid:1 ;/*save cerssi set command-- 1:valid 0:invalid*/
	VOS_UINT32  cerssi_bit	:1 ;    /*save cerssi set command-- 1:open 0:close*/
	VOS_UINT32  rssi_bit_valid:1;   /*save rssi set command--     1:valid 0:invalid*/
	VOS_UINT32  rssi_bit	:1 ;    /*save rssi set command--     1:open 0:close*/
	VOS_UINT32  anlevel_bit_valid:1;/*save anlevel set command--1:valid 0:invalid*/
	VOS_UINT32  anlevel_bit	:1 ;    /*save anlevel set command--1:open 0:close*/
    VOS_UINT32  lcacell_bit_valid:1;/*save lcacell set command--1:valid 0:invalid*/
	VOS_UINT32  lcacell_bit	:1 ;    /*save lcacell set command--1:open 0:close*/
	VOS_UINT32  curc_bit_valid	:1 ;/*save cruc=2                      --1:valid 0;invalid */
	VOS_UINT32  reserved    :21;
	VOS_UINT8   aucCurcCfgReq[L4A_CURC_RPT_CFG_MAX_SIZE];/*save curc=2*/
} L4A_IND_CFG_STRU;

typedef struct
{
	VOS_MSG_HEADER																/* _H2ASN_Skip */
	APS_L4A_MSG_ID_ENUM_UINT32			enMsgId;								/* _H2ASN_Skip */

	APS_L4A_APPCTRL_STRU				stCtrl;
    VOS_UINT32                          ulCellFlag;
} L4A_READ_CELL_INFO_REQ_STRU;

typedef struct
{
	VOS_MSG_HEADER																/* _H2ASN_Skip */
	APS_L4A_MSG_ID_ENUM_UINT32			enMsgId;								/* _H2ASN_Skip */

	VOS_UINT16							usClientId; 							/* ID   */
	VOS_UINT8							ucOpId; 								/* ID   */
	VOS_UINT8							aucReserved[1];
	VOS_UINT32							ulErrorCode;							/* 	  */
    LRRC_APP_NCELL_LIST_INFO_STRU 		stNcellListInfo;
} L4A_READ_CELL_INFO_CNF_STRU;

typedef L4A_COMM_REQ_STRU L4A_READ_CELL_ID_REQ_STRU;

typedef struct
{
	VOS_MSG_HEADER																/* _H2ASN_Skip */
	APS_L4A_MSG_ID_ENUM_UINT32			enMsgId;								/* _H2ASN_Skip */

	VOS_UINT16							usClientId; 							/* ID   */
	VOS_UINT8							ucOpId; 								/* ID   */
	VOS_UINT8							aucReserved[1];
	VOS_UINT32							ulErrorCode;							/* 	  */
    VOS_UINT16                          usMncNum;           /*?? MNC ??*/
    VOS_UINT16                          usMCC;
    VOS_UINT16                          usMNC;
    VOS_UINT16                          usRev;
    VOS_UINT32                          ulCi;               /* 0xFFFF???, */
    VOS_UINT16                          usPci;              /* 0xFFFF???,??:(0,503) */
    VOS_UINT16                          usTAC;             /* TAC */
}L4A_READ_CELL_ID_CNF_STRU;

typedef struct
{
    VOS_UINT16 Mcc;  /* Mobile Country Code , 0x460*/
    VOS_UINT16 Mnc;  /* Mobile Network Code ,MNC,0x0f*/
}L4A_PLMN_ID_STRU;

typedef L4A_COMM_REQ_STRU L4A_SET_LTE_TO_IDLE_REQ_STRU;

typedef struct
{
	VOS_MSG_HEADER																/* _H2ASN_Skip */
	APS_L4A_MSG_ID_ENUM_UINT32			enMsgId;								/* _H2ASN_Skip */

	APS_L4A_APPCTRL_STRU				stCtrl;
    VOS_UINT32             ulFlag;
}L4A_LW_THREASHOLD_CFG_REQ_STRU;

typedef struct
{
	VOS_MSG_HEADER																/* _H2ASN_Skip */
	APS_L4A_MSG_ID_ENUM_UINT32			enMsgId;								/* _H2ASN_Skip */

	APS_L4A_APPCTRL_STRU				stCtrl;
    VOS_INT32     ulFlag;
    VOS_INT32     ulTimerLen;
}L4A_SET_FAST_DORM_REQ_STRU;

typedef struct
{
	VOS_MSG_HEADER																/* _H2ASN_Skip */
	APS_L4A_MSG_ID_ENUM_UINT32			enMsgId;								/* _H2ASN_Skip */

	APS_L4A_APPCTRL_STRU				stCtrl;
    L4A_IND_CFG_STRU stIndCfg;
} L4A_IND_CFG_REQ_STRU;

typedef struct
{
	VOS_MSG_HEADER																/* _H2ASN_Skip */
	APS_L4A_MSG_ID_ENUM_UINT32			enMsgId;								/* _H2ASN_Skip */

	VOS_UINT16							usClientId; 							/* ID   */
	VOS_UINT8							ucOpId; 								/* ID   */
	VOS_UINT8							aucReserved[1];
	VOS_UINT32							ulErrorCode;							/* 	  */
} L4A_AT_CNF_HEADER_STRU;


typedef struct
{
	VOS_MSG_HEADER																/* _H2ASN_Skip */
	APS_L4A_MSG_ID_ENUM_UINT32			enMsgId;								/* _H2ASN_Skip */

	APS_L4A_APPCTRL_STRU				stCtrl;
    VOS_UINT32                          ulMod;
    VOS_UINT32                          ulVer;
} L4A_SET_RADVER_REQ_STRU;

typedef struct
{
	VOS_MSG_HEADER																/* _H2ASN_Skip */
	APS_L4A_MSG_ID_ENUM_UINT32			enMsgId;								/* _H2ASN_Skip */

	VOS_UINT16							usClientId; 							/* ID   */
	VOS_UINT8							ucOpId; 								/* ID   */
	VOS_UINT8							aucReserved;
	VOS_UINT32							ulErrorCode;							/* 	  */
} L4A_SET_RADVER_CNF_STRU;


#endif /* __GEN_MSG_H__ */







