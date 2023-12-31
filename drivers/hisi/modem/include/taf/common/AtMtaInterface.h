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

#ifndef __ATMTAINTERFACE_H__
#define __ATMTAINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  1 
*****************************************************************************/
#include "PsTypeDef.h"
#include "AtMnInterface.h"
/* Modified by s00217060 for VoLTE_PhaseI  , 2013-07-27, begin */
#include "NasNvInterface.h"
/* Modified by s00217060 for VoLTE_PhaseI  , 2013-07-27, end */
#include "TafNvInterface.h"
#include "MtaCommInterface.h"

/*****************************************************************************
  2 
*****************************************************************************/
#define MTA_CPOS_XML_MAX_LEN            (1024)              /* MTAATXML */
#define MTA_CPOSR_XML_MAX_LEN           (1024)              /* MTAATXML1024 */
#define MTA_SIMLOCK_PASSWORD_LEN        (16)                /*  */

#define MTA_CLIENTID_BROADCAST          (0xFFFF)
#define MTA_INVALID_TAB_INDEX           (0x00)


#define AT_MTA_WRR_AUTOTEST_MAX_PARA_NUM          (10) /* autotest */
#define MTA_AT_WRR_AUTOTEST_MAX_RSULT_NUM         (20) /* autotest */
#define MTA_AT_WRR_ONE_MEANRPT_MAX_CELL_NUM       (8)  /*  */
#define MTA_AT_WRR_MAX_MEANRPT_NUM                (10) /*  */

#define MTA_AT_WRR_MAX_NCELL_NUM                  (8)

/* Added by s00217060 for ATC, 2013-3-25, begin */
#define AT_MTA_RPT_CFG_MAX_SIZE                   (8)
/* Added by s00217060 for ATC, 2013-3-25, end */

#define AT_MTA_HANDLEDECT_MIN_TYPE                (0)
#define AT_MTA_HANDLEDECT_MAX_TYPE                (4)

#if (FEATURE_ON == FEATURE_SC_SEC_UPDATE)
#define AT_RSA_CIPHERTEXT_LEN           (256)
#else
#define AT_RSA_CIPHERTEXT_LEN           (128)
#endif

#define  AT_MTA_INTEREST_FREQ_MAX_NUM         (0x05)
#define  AT_MTA_MBMS_AVL_SERVICE_MAX_NUM      (0x10)
#define  AT_MTA_ISMCOEX_BANDWIDTH_NUM         (0x06)

#define AT_MTA_MEID_DATA_LEN                         (7)

#define MTA_AT_EFRUIMID_OCTET_LEN_EIGHT                   (8)
#define MTA_AT_EFRUIMID_OCTET_LEN_FIVE                    (5)

#define MTA_AT_UIMID_OCTET_LEN                            (4)

#define AT_MTA_GPS_XO_COEF_NUM                       (4)

#if (FEATURE_ON == FEATURE_PROBE_FREQLOCK)
#define MTA_FREQLOCK_MAX_MODE                     (4)
#endif

#define MTC_MTA_MAX_BESTFREQ_GROUPNUM        (8)

#define MTA_RCM_MAX_DIE_ID_LEN              (32)

#define MTA_PMU_MAX_DIE_SN_LEN              (20)

#define AT_MAX_RS_INFO_NUM                  (32)    /* LRRCRS */
#define AT_RS_INFO_MULTI                    (100)   /* LRRCRSRPRSRQ100MTA */

/*****************************************************************************
  3 
*****************************************************************************/
/*****************************************************************************
     : AT_MTA_MSG_TYPE_ENUM
   : ATMTA
1.      : 20120628
        : y00213812
    : V7R1C50 A_GPS
2.       : 20121121
         : z00161729
    : cerssinmr
3.       : 20121226
         : m00217266
     :  WASID
4.      : 20130313
        : z00214637
    : BodySAR
5.       : 2013325
         : s00217060
     : CID
*****************************************************************************/
enum AT_MTA_MSG_TYPE_ENUM
{
    /*  */                      /* ID */        /* , ASN */
    /* ATMTA */
    ID_AT_MTA_CPOS_SET_REQ              = 0x0000,           /* _H2ASN_MsgChoice AT_MTA_CPOS_REQ_STRU        */
    ID_AT_MTA_CGPSCLOCK_SET_REQ         = 0x0001,           /* _H2ASN_MsgChoice AT_MTA_CGPSCLOCK_REQ_STRU   */
    ID_AT_MTA_SIMLOCKUNLOCK_SET_REQ     = 0x0003,           /* _H2ASN_MsgChoice AT_MTA_SIMLOCKUNLOCK_REQ_STRU */

    ID_AT_MTA_QRY_NMR_REQ               = 0x0004,           /* _H2ASN_MsgChoice AT_MTA_QRY_NMR_REQ_STRU */

    ID_AT_MTA_RESEL_OFFSET_CFG_SET_NTF  = 0x0005,           /* _H2ASN_MsgChoice AT_MTA_RESEL_OFFSET_CFG_SET_NTF_STRU */
    ID_AT_MTA_WRR_AUTOTEST_QRY_REQ      = 0x0006,           /* _H2ASN_MsgChoice AT_MTA_WRR_AUTOTEST_QRY_PARA_STRU */
    ID_AT_MTA_WRR_CELLINFO_QRY_REQ      = 0x0007,           /* _H2ASN_MsgChoice AT_MTA_RESERVE_STRU */
    ID_AT_MTA_WRR_MEANRPT_QRY_REQ       = 0x0008,           /* _H2ASN_MsgChoice AT_MTA_RESERVE_STRU */
    ID_AT_MTA_WRR_FREQLOCK_SET_REQ      = 0x0009,           /* _H2ASN_MsgChoice MTA_AT_WRR_FREQLOCK_CTRL_STRU     */
    ID_AT_MTA_WRR_RRC_VERSION_SET_REQ   = 0x000A,           /* _H2ASN_MsgChoice AT_MTA_RESERVE_STRU*/
    ID_AT_MTA_WRR_CELLSRH_SET_REQ       = 0x000B,           /* _H2ASN_MsgChoice AT_MTA_RESERVE_STRU*/
    ID_AT_MTA_WRR_FREQLOCK_QRY_REQ      = 0x000C,           /* _H2ASN_MsgChoice AT_MTA_RESERVE_STRU */
    ID_AT_MTA_WRR_RRC_VERSION_QRY_REQ   = 0x000D,           /* _H2ASN_MsgChoice AT_MTA_RESERVE_STRU */
    ID_AT_MTA_WRR_CELLSRH_QRY_REQ       = 0x000E,           /* _H2ASN_MsgChoice AT_MTA_RESERVE_STRU */

    ID_AT_MTA_BODY_SAR_SET_REQ          = 0x000F,           /* _H2ASN_MsgChoice AT_MTA_BODY_SAR_SET_REQ_STRU */
    /* Added by s00217060 for ATC, 2013-3-25, begin */
    ID_AT_MTA_CURC_SET_NOTIFY           = 0x0010,           /* _H2ASN_MsgChoice AT_MTA_CURC_SET_NOTIFY_STRU */
    ID_AT_MTA_CURC_QRY_REQ              = 0x0011,           /* _H2ASN_MsgChoice AT_MTA_CURC_QRY_REQ_STRU */
    ID_AT_MTA_UNSOLICITED_RPT_SET_REQ   = 0x0012,           /* _H2ASN_MsgChoice AT_MTA_UNSOLICITED_RPT_SET_REQ_STRU */
    ID_AT_MTA_UNSOLICITED_RPT_QRY_REQ   = 0x0013,           /* _H2ASN_MsgChoice AT_MTA_UNSOLICITED_RPT_QRY_REQ_STRU */
    /* Added by s00217060 for ATC, 2013-3-25, end */

    ID_AT_MTA_IMEI_VERIFY_QRY_REQ       = 0x0014,           /* _H2ASN_MsgChoice AT_MTA_RESERVE_STRU */
    ID_AT_MTA_CGSN_QRY_REQ              = 0x0015,           /* _H2ASN_MsgChoice AT_MTA_RESERVE_STRU */
    ID_AT_MTA_NCELL_MONITOR_SET_REQ     = 0x0016,           /* _H2ASN_MsgChoice AT_MTA_NCELL_MONITOR_SET_REQ_STRU */
    ID_AT_MTA_NCELL_MONITOR_QRY_REQ     = 0x0017,           /* _H2ASN_MsgChoice AT_MTA_RESERVE_STRU */

    ID_AT_MTA_REFCLKFREQ_SET_REQ        = 0x0018,           /* _H2ASN_MsgChoice AT_MTA_REFCLKFREQ_SET_REQ_STRU */
    ID_AT_MTA_REFCLKFREQ_QRY_REQ        = 0x0019,           /* _H2ASN_MsgChoice AT_MTA_RESERVE_STRU */

    ID_AT_MTA_HANDLEDECT_SET_REQ        = 0x001A,           /* _H2ASN_MsgChoice AT_MTA_RESERVE_STRU */
    ID_AT_MTA_HANDLEDECT_QRY_REQ        = 0x001B,           /* _H2ASN_MsgChoice AT_MTA_RESERVE_STRU */

    /* Added by l00198894 for +ECID, 2013-12-09, begin */
    ID_AT_MTA_ECID_SET_REQ              = 0x001C,           /* _H2ASN_MsgChoice AT_MTA_ECID_SET_REQ_STRU */
    /* Added by l00198894 for +ECID, 2013-12-09, end */

    ID_AT_MTA_MIPICLK_QRY_REQ           = 0x001D,           /* _H2ASN_MsgChoice AT_MTA_RESERVE_STRU */

    ID_AT_MTA_SET_DPDTTEST_FLAG_REQ     = 0x001E,           /* _H2ASN_MsgChoice AT_MTA_SET_DPDTTEST_FLAG_REQ_STRU */
    ID_AT_MTA_SET_DPDT_VALUE_REQ        = 0x001F,           /* _H2ASN_MsgChoice AT_MTA_SET_DPDT_VALUE_REQ_STRU */
    ID_AT_MTA_QRY_DPDT_VALUE_REQ        = 0x0020,           /* _H2ASN_MsgChoice AT_MTA_QRY_DPDT_VALUE_REQ_STRU */

    ID_AT_MTA_RRC_PROTECT_PS_REQ        = 0x0021,
    ID_AT_MTA_PHY_INIT_REQ              = 0x0022,

    ID_AT_MTA_SET_JAM_DETECT_REQ        = 0x0023,           /* _H2ASN_MsgChoice AT_MTA_SET_JAM_DETECT_REQ_STRU */

    ID_AT_MTA_SET_FREQ_LOCK_REQ         = 0x0024,           /* _H2ASN_MsgChoice AT_MTA_SET_FREQ_LOCK_REQ_STRU */

    ID_AT_MTA_SET_GSM_FREQLOCK_REQ      = 0x0025,          /* _H2ASN_MsgChoice AT_MTA_SET_GSM_FREQLOCK_REQ_STRU */
    ID_AT_MTA_SET_FEMCTRL_REQ           = 0x0026,

    ID_AT_MTA_NVWRSECCTRL_SET_REQ       = 0x0027,

    ID_AT_MTA_MBMS_SERVICE_OPTION_SET_REQ   = 0x0028,      /* _H2ASN_MsgChoice AT_MTA_MBMS_SERVICE_OPTION_SET_REQ_STRU */
    ID_AT_MTA_MBMS_PREFERENCE_SET_REQ       = 0x0029,      /* _H2ASN_MsgChoice AT_MTA_MBMS_PREFERENCE_SET_REQ_STRU */
    ID_AT_MTA_SIB16_NETWORK_TIME_QRY_REQ    = 0x002A,      /* _H2ASN_MsgChoice AT_MTA_RESERVE_STRU */
    ID_AT_MTA_BSSI_SIGNAL_LEVEL_QRY_REQ     = 0x002B,      /* _H2ASN_MsgChoice AT_MTA_RESERVE_STRU */
    ID_AT_MTA_NETWORK_INFO_QRY_REQ          = 0x002C,      /* _H2ASN_MsgChoice AT_MTA_RESERVE_STRU */
    ID_AT_MTA_EMBMS_STATUS_QRY_REQ          = 0x002D,      /* _H2ASN_MsgChoice AT_MTA_RESERVE_STRU */
    ID_AT_MTA_MBMS_UNSOLICITED_CFG_SET_REQ  = 0x002E,      /* _H2ASN_MsgChoice AT_MTA_MBMS_UNSOLICITED_CFG_SET_REQ_STRU */
    ID_AT_MTA_LTE_LOW_POWER_SET_REQ         = 0x002F,      /* _H2ASN_MsgChoice AT_MTA_LOW_POWER_CONSUMPTION_SET_REQ_STRU */
    ID_AT_MTA_INTEREST_LIST_SET_REQ         = 0x0030,      /* _H2ASN_MsgChoice AT_MTA_MBMS_INTERESTLIST_SET_REQ_STRU */
    ID_AT_MTA_MBMS_SERVICE_STATE_SET_REQ    = 0x0031,      /* _H2ASN_MsgChoice AT_MTA_MBMS_SERVICE_STATE_SET_REQ_STRU */
    ID_AT_MTA_MBMS_AVL_SERVICE_LIST_QRY_REQ = 0x0032,      /* _H2ASN_MsgChoice AT_MTA_RESERVE_STRU */
    ID_AT_MTA_LTE_WIFI_COEX_SET_REQ         = 0x0033,      /* _H2ASN_MsgChoice AT_MTA_LTE_WIFI_COEX_SET_REQ_STRU */
    ID_AT_MTA_LTE_WIFI_COEX_QRY_REQ         = 0x0034,      /* _H2ASN_MsgChoice AT_MTA_RESERVE_STRU */

    ID_AT_MTA_SET_FR_REQ                = 0x0035,

    ID_AT_MTA_MEID_SET_REQ              = 0x0036,     /* _H2ASN_MsgChoice AT_MTA_MEID_SET_REQ_STRU */
    ID_AT_MTA_MEID_QRY_REQ              = 0x0037,

#if (FEATURE_ON == FEATURE_PROBE_FREQLOCK)
    ID_AT_MTA_SET_M2M_FREQLOCK_REQ      = 0x0038,           /* _H2ASN_MsgChoice AT_MTA_SET_M2M_FREQLOCK_REQ_STRU */
    ID_AT_MTA_QRY_M2M_FREQLOCK_REQ      = 0x0039,           /* _H2ASN_MsgChoice AT_MTA_RESERVE_STRU */
#endif

    ID_AT_MTA_TRANSMODE_QRY_REQ         = 0x0044,

    ID_AT_MTA_UE_CENTER_SET_REQ         = 0x0045,     /* _H2ASN_MsgChoice AT_MTA_SET_UE_CENTER_REQ_STRU */
    ID_AT_MTA_UE_CENTER_QRY_REQ         = 0x0046,

    ID_AT_MTA_SET_NETMON_SCELL_REQ      = 0x0047,
    ID_AT_MTA_SET_NETMON_NCELL_REQ      = 0x0048,

    ID_AT_MTA_RFICSSIRD_QRY_REQ         = 0x0049,

    ID_AT_MTA_ANQUERY_QRY_REQ           = 0x004A,
    ID_AT_MTA_CSNR_QRY_REQ              = 0x004B,
    ID_AT_MTA_CSQLVL_QRY_REQ            = 0x004C,

    ID_AT_MTA_EVDO_SYS_EVENT_SET_REQ    = 0x004d,     /* _H2ASN_MsgChoice AT_MTA_EVDO_SYS_EVENT_SET_REQ_STRU */
    ID_AT_MTA_EVDO_SIG_MASK_SET_REQ     = 0x004e,     /* _H2ASN_MsgChoice AT_MTA_EVDO_SIG_MASK_SET_REQ_STRU */

    ID_AT_MTA_XCPOSR_SET_REQ            = 0x004F,                               /* _H2ASN_MsgChoice AT_MTA_SET_XCPOSR_REQ_STRU */
    ID_AT_MTA_XCPOSR_QRY_REQ            = 0x0050,                               /* _H2ASN_MsgChoice AT_MTA_RESERVE_STRU */
    ID_AT_MTA_XCPOSRRPT_SET_REQ         = 0x0051,                               /* _H2ASN_MsgChoice AT_MTA_SET_XCPOSRRPT_REQ_STRU */
    ID_AT_MTA_XCPOSRRPT_QRY_REQ         = 0x0052,                               /* _H2ASN_MsgChoice AT_MTA_RESERVE_STRU */
    ID_AT_MTA_CLEAR_HISTORY_FREQ_REQ    = 0x0053,       /* _H2ASN_MsgChoice AT_MTA_CLEAR_HISTORY_FREQ_REQ_STRU */

    ID_AT_MTA_SET_SENSOR_REQ            = 0x0054,                               /* _H2ASN_MsgChoice AT_MTA_SET_SENSOR_REQ_STRU*/
    ID_AT_MTA_SET_SCREEN_REQ            = 0x0055,                               /* _H2ASN_MsgChoice AT_MTA_SET_SCREEN_REQ_STRU*/
    ID_AT_MTA_FRAT_IGNITION_QRY_REQ     = 0x0056,                               /* _H2ASN_MsgChoice MTA_AT_FRAT_IGNITION_QRY_CNF_STRU */
    ID_AT_MTA_FRAT_IGNITION_SET_REQ     = 0x0057,                               /* _H2ASN_MsgChoice MTA_AT_FRAT_IGNITION_SET_CNF_STRU */

    ID_AT_MTA_MODEM_TIME_SET_REQ        = 0x0058,

    ID_AT_MTA_RX_TEST_MODE_SET_REQ      = 0x0059,

    ID_AT_MTA_SLAVE_SET_REQ             = 0x005A,

    ID_AT_MTA_BESTFREQ_SET_REQ          = 0x005B,           /* AT_MTA_BESTFREQ_SET_REQ_STRU */
    ID_AT_MTA_BESTFREQ_QRY_REQ          = 0x005C,

    ID_AT_MTA_RFIC_DIE_ID_QRY_REQ       = 0x005D,

    /* Added by c00380008 for Wifi & VoLTE, 2016-8-22, begin */
    ID_AT_MTA_CRRCONN_SET_REQ           = 0x005E,
    ID_AT_MTA_CRRCONN_QRY_REQ           = 0x005F,
    ID_AT_MTA_VTRLQUALRPT_SET_REQ       = 0x0060,
    /* Added by c00380008 for Wifi & VoLTE, 2016-8-22, end */

    ID_AT_MTA_PMU_DIE_SN_QRY_REQ        = 0x0061,

    ID_AT_MTA_MODEM_CAP_UPDATE_REQ      = 0x0062,

    ID_AT_MTA_TAS_CFG_REQ               = 0x0063,
    ID_AT_MTA_TAS_QRY_REQ               = 0x0064,

    ID_AT_MTA_MIPI_WREX_REQ              = 0x0065,
    ID_AT_MTA_MIPI_RDEX_REQ              = 0x0066,

    ID_AT_MTA_RS_INFO_QRY_REQ           = 0x0067,

    ID_AT_MTA_PHY_COM_CFG_SET_REQ       = 0x0068,

    /* MTAAT */
    ID_MTA_AT_CPOS_SET_CNF              = 0x1000,           /* _H2ASN_MsgChoice MTA_AT_CPOS_CNF_STRU        */
    ID_MTA_AT_CGPSCLOCK_SET_CNF         = 0x1001,           /* _H2ASN_MsgChoice MTA_AT_CGPSCLOCK_CNF_STRU   */
    ID_MTA_AT_CPOSR_IND                 = 0x1002,           /* _H2ASN_MsgChoice MTA_AT_CPOSR_IND_STRU       */
    ID_MTA_AT_XCPOSRRPT_IND             = 0x1003,           /* _H2ASN_MsgChoice MTA_AT_XCPOSRRPT_IND_STRU   */
    ID_MTA_AT_APSEC_SET_CNF             = 0x1004,           /* _H2ASN_MsgChoice MTA_AT_APSEC_CNF_STRU       */
    ID_MTA_AT_SIMLOCKUNLOCK_SET_CNF     = 0x1005,           /* _H2ASN_MsgChoice MTA_AT_SIMLOCKUNLOCK_CNF_STRU */

    ID_MTA_AT_QRY_NMR_CNF               = 0x1006,           /* _H2ASN_MsgChoice MTA_AT_QRY_NMR_CNF_STRU */

    ID_MTA_AT_WRR_AUTOTEST_QRY_CNF      = 0x1007,           /* _H2ASN_MsgChoice MTA_AT_WRR_AUTOTEST_QRY_CNF_STRU       */
    ID_MTA_AT_WRR_CELLINFO_QRY_CNF      = 0x1008,           /* _H2ASN_MsgChoice MTA_AT_WRR_CELLINFO_QRY_CNF_STRU       */
    ID_MTA_AT_WRR_MEANRPT_QRY_CNF       = 0x1009,           /* _H2ASN_MsgChoice MTA_AT_WRR_MEANRPT_QRY_CNF_STRU        */
    ID_MTA_AT_WRR_FREQLOCK_SET_CNF      = 0x100A,           /* _H2ASN_MsgChoice MTA_AT_WRR_FREQLOCK_SET_CNF_STRU       */
    ID_MTA_AT_WRR_RRC_VERSION_SET_CNF   = 0x100B,           /* _H2ASN_MsgChoice MTA_AT_WRR_RRC_VERSION_SET_CNF_STRU    */
    ID_MTA_AT_WRR_CELLSRH_SET_CNF       = 0x100C,           /* _H2ASN_MsgChoice MTA_AT_WRR_CELLSRH_SET_CNF_STRU        */
    ID_MTA_AT_WRR_FREQLOCK_QRY_CNF      = 0x100D,           /* _H2ASN_MsgChoice MTA_AT_WRR_FREQLOCK_QRY_CNF_STRU       */
    ID_MTA_AT_WRR_RRC_VERSION_QRY_CNF   = 0x100E,           /* _H2ASN_MsgChoice MTA_AT_WRR_RRC_VERSION_QRY_CNF_STRU    */
    ID_MTA_AT_WRR_CELLSRH_QRY_CNF       = 0x100F,           /* _H2ASN_MsgChoice MTA_AT_WRR_CELLSRH_QRY_CNF_STRU        */

    ID_MTA_AT_BODY_SAR_SET_CNF          = 0x1010,           /* _H2ASN_MsgChoice MTA_AT_RESULT_CNF_STRU */

    /* Added by s00217060 for ATC, 2013-3-25, begin */
    ID_MTA_AT_CURC_QRY_CNF              = 0x1011,           /* _H2ASN_MsgChoice MTA_AT_CURC_QRY_CNF_STRU */
    ID_MTA_AT_UNSOLICITED_RPT_SET_CNF   = 0x1012,           /* _H2ASN_MsgChoice MTA_AT_UNSOLICITED_RPT_SET_CNF_STRU */
    ID_MTA_AT_UNSOLICITED_RPT_QRY_CNF   = 0x1013,           /* _H2ASN_MsgChoice MTA_AT_UNSOLICITED_RPT_QRY_CNF_STRU */
    /* Added by s00217060 for ATC, 2013-3-25, end */

    ID_MTA_AT_IMEI_VERIFY_QRY_CNF       = 0x1014,            /* _H2ASN_MsgChoice AT_MTA_RESERVE_STRU */
    ID_MTA_AT_CGSN_QRY_CNF              = 0x1015,            /* _H2ASN_MsgChoice MTA_AT_CGSN_QRY_CNF_STRU */
    ID_MTA_AT_NCELL_MONITOR_SET_CNF     = 0x1016,           /* _H2ASN_MsgChoice MTA_AT_RESULT_CNF_STRU        */
    ID_MTA_AT_NCELL_MONITOR_QRY_CNF     = 0x1017,           /* _H2ASN_MsgChoice MTA_AT_NCELL_MONITOR_QRY_CNF_STRU        */
    ID_MTA_AT_NCELL_MONITOR_IND         = 0x1018,           /* _H2ASN_MsgChoice MTA_AT_NCELL_MONITOR_IND_STRU        */

    ID_MTA_AT_REFCLKFREQ_SET_CNF        = 0x1019,           /* _H2ASN_MsgChoice MTA_AT_RESULT_CNF_STRU */
    ID_MTA_AT_REFCLKFREQ_QRY_CNF        = 0x101A,           /* _H2ASN_MsgChoice MTA_AT_REFCLKFREQ_QRY_CNF_STRU */
    ID_MTA_AT_REFCLKFREQ_IND            = 0x101B,           /* _H2ASN_MsgChoice MTA_AT_REFCLKFREQ_IND_STRU */

    ID_MTA_AT_HANDLEDECT_SET_CNF        = 0x101C,           /* _H2ASN_MsgChoice MTA_AT_HANDLEDECT_SET_CNF_STRU */
    ID_MTA_AT_HANDLEDECT_QRY_CNF        = 0x101D,           /* _H2ASN_MsgChoice MTA_AT_HANDLEDECT_QRY_CNF_STRU */

    ID_MTA_AT_PS_TRANSFER_IND           = 0x101E,           /* _H2ASN_MsgChoice MTA_AT_PS_TRANSFER_IND_STRU */

    /* Added by l00198894 for +ECID, 2013-12-09, begin */
    ID_MTA_AT_ECID_SET_CNF              = 0x101F,           /* _H2ASN_MsgChoice MTA_AT_ECID_SET_CNF_STRU */
    /* Added by l00198894 for +ECID, 2013-12-09, end */

    ID_MTA_AT_MIPICLK_QRY_CNF           = 0x1020,           /* _H2ASN_MsgChoice MTA_AT_RF_LCD_MIPICLK_CNF_STRU */
    ID_MTA_AT_MIPICLK_INFO_IND          = 0x1021,           /* _H2ASN_MsgChoice MTA_AT_RF_LCD_MIPICLK_IND_STRU */

    ID_MTA_AT_SET_DPDTTEST_FLAG_CNF     = 0x1022,           /* _H2ASN_MsgChoice MTA_AT_SET_DPDTTEST_FLAG_CNF_STRU */
    ID_MTA_AT_SET_DPDT_VALUE_CNF        = 0x1023,           /* _H2ASN_MsgChoice MTA_AT_SET_DPDT_VALUE_CNF_STRU */
    ID_MTA_AT_QRY_DPDT_VALUE_CNF        = 0x1024,           /* _H2ASN_MsgChoice MTA_AT_QRY_DPDT_VALUE_CNF_STRU */

    ID_MTA_AT_RRC_PROTECT_PS_CNF        = 0x1025,
    ID_MTA_AT_PHY_INIT_CNF              = 0x1026,

    ID_MTA_AT_SET_JAM_DETECT_CNF        = 0x1027,           /* _H2ASN_MsgChoice MTA_AT_SET_JAM_DETECT_CNF_STRU */
    ID_MTA_AT_JAM_DETECT_IND            = 0x1028,           /* _H2ASN_MsgChoice MTA_AT_JAM_DETECT_IND_STRU */

    ID_MTA_AT_SET_FREQ_LOCK_CNF         = 0x1029,           /* _H2ASN_MsgChoice MTA_AT_SET_FREQ_LOCK_CNF_STRU */

    ID_MTA_AT_SET_GSM_FREQLOCK_CNF      = 0x102A,           /* _H2ASN_MsgChoice MTA_AT_SET_GSM_FREQLOCK_CNF_STRU */

    ID_AT_MTA_SET_FEMCTRL_CNF           = 0x102B,

    ID_MTA_AT_XPASS_INFO_IND            = 0x102C,

    ID_MTA_AT_NVWRSECCTRL_SET_CNF       = 0x102D,

    ID_MTA_AT_MBMS_SERVICE_OPTION_SET_CNF   = 0x102E,       /* _H2ASN_MsgChoice MTA_AT_RESULT_CNF_STRU */
    ID_MTA_AT_MBMS_PREFERENCE_SET_CNF       = 0x102F,       /* _H2ASN_MsgChoice MTA_AT_RESULT_CNF_STRU */
    ID_MTA_AT_SIB16_NETWORK_TIME_QRY_CNF    = 0x1030,       /* _H2ASN_MsgChoice MTA_AT_MBMS_SIB16_NETWORK_TIME_QRY_CNF_STRU */
    ID_MTA_AT_BSSI_SIGNAL_LEVEL_QRY_CNF     = 0x1031,       /* _H2ASN_MsgChoice MTA_AT_MBMS_BSSI_SIGNAL_LEVEL_QRY_CNF_STRU */
    ID_MTA_AT_NETWORK_INFO_QRY_CNF          = 0x1032,       /* _H2ASN_MsgChoice MTA_AT_MBMS_NETWORK_INFO_QRY_CNF_STRU */
    ID_MTA_AT_EMBMS_STATUS_QRY_CNF          = 0x1033,       /* _H2ASN_MsgChoice MTA_AT_EMBMS_STATUS_QRY_CNF_STRU */
    ID_MTA_AT_MBMS_UNSOLICITED_CFG_SET_CNF  = 0x1034,       /* _H2ASN_MsgChoice MTA_AT_RESULT_CNF_STRU */
    ID_MTA_AT_MBMS_SERVICE_EVENT_IND        = 0x1035,       /* _H2ASN_MsgChoice MTA_AT_MBMS_SERVICE_EVENT_IND_STRU */
    ID_MTA_AT_LTE_LOW_POWER_SET_CNF         = 0x1036,       /* _H2ASN_MsgChoice MTA_AT_RESULT_CNF_STRU */
    ID_MTA_AT_INTEREST_LIST_SET_CNF         = 0x1037,       /* _H2ASN_MsgChoice MTA_AT_RESULT_CNF_STRU */
    ID_MTA_AT_MBMS_SERVICE_STATE_SET_CNF    = 0x1038,       /* _H2ASN_MsgChoice MTA_AT_RESULT_CNF_STRU */
    ID_MTA_AT_MBMS_AVL_SERVICE_LIST_QRY_CNF = 0x1039,       /* _H2ASN_MsgChoice MTA_AT_MBMS_AVL_SERVICE_LIST_QRY_CNF_STRU */
    ID_MTA_AT_LTE_WIFI_COEX_SET_CNF         = 0x103A,       /* _H2ASN_MsgChoice MTA_AT_RESULT_CNF_STRU */
    ID_MTA_AT_LTE_WIFI_COEX_QRY_CNF         = 0x103B,       /* _H2ASN_MsgChoice MTA_AT_LTE_WIFI_COEX_QRY_CNF_STRU */

    ID_MTA_AT_SET_FR_CNF                = 0x103C,

    ID_MTA_AT_MEID_SET_CNF              = 0x103d,     /* _H2ASN_MsgChoice MTA_AT_RESULT_CNF_STRU */

    ID_MTA_AT_RFICSSIRD_QRY_CNF         = 0x103e,

    ID_MTA_AT_MEID_QRY_CNF              = 0x103f,     /* _H2ASN_MsgChoice MTA_AT_MEID_QRY_CNF_STRU */

#if (FEATURE_ON == FEATURE_PROBE_FREQLOCK)
    ID_MTA_AT_SET_M2M_FREQLOCK_CNF      = 0x1040,           /* _H2ASN_MsgChoice AT_MTA_SET_M2M_FREQLOCK_CNF_STRU */
    ID_MTA_AT_QRY_M2M_FREQLOCK_CNF      = 0x1041,           /* _H2ASN_MsgChoice MTA_AT_QRY_FREQLOCK_CNF_STRU */
#endif

    ID_MTA_AT_TRANSMODE_QRY_CNF         = 0x1052,

    ID_MTA_AT_UE_CENTER_SET_CNF         = 0x1053,
    ID_MTA_AT_UE_CENTER_QRY_CNF         = 0x1054,     /* _H2ASN_MsgChoice MTA_AT_QRY_UE_CENTER_CNF_STRU */

    ID_MTA_AT_SET_NETMON_SCELL_CNF      = 0x1055,     /* _H2ASN_MsgChoice MTA_AT_NETMON_CELL_INFO_STRU */
    ID_MTA_AT_SET_NETMON_NCELL_CNF      = 0x1056,     /* _H2ASN_MsgChoice MTA_AT_NETMON_CELL_INFO_STRU */

    ID_AT_MTA_QRY_AFC_CLK_FREQ_XOCOEF_REQ = 0x1057, /* _H2ASN_MsgChoice AT_MTA_QRY_AFC_CLK_FREQ_XOCOEF_REQ_STRU */
    ID_MTA_AT_QRY_AFC_CLK_FREQ_XOCOEF_CNF = 0x1058, /* _H2ASN_MsgChoice MTA_AT_QRY_AFC_CLK_FREQ_XOCOEF_CNF_STRU */
    ID_MTA_AT_ANQUERY_QRY_CNF           = 0x1059,       /* _H2ASN_MsgChoice MTA_AT_ANTENNA_INFO_QRY_CNF_STRU */
    ID_MTA_AT_CSNR_QRY_CNF              = 0x105A,       /* _H2ASN_MsgChoice MTA_AT_CSNR_QRY_CNF_STRU */
    ID_MTA_AT_CSQLVL_QRY_CNF            = 0x105B,       /* _H2ASN_MsgChoice MTA_AT_CSQLVL_QRY_CNF_STRU */

    ID_MTA_AT_EVDO_SYS_EVENT_CNF        = 0x105c,     /* _H2ASN_MsgChoice MTA_AT_RESULT_CNF_STRU */
    ID_MTA_AT_EVDO_SIG_MASK_CNF         = 0x105d,     /* _H2ASN_MsgChoice MTA_AT_RESULT_CNF_STRU */
    ID_MTA_AT_EVDO_REVA_RLINK_INFO_IND  = 0x105e,
    ID_MTA_AT_EVDO_SIG_EXEVENT_IND      = 0x105f,

    ID_MTA_AT_XCPOSR_SET_CNF            = 0x1060,                               /* _H2ASN_MsgChoice MTA_AT_RESULT_CNF_STRU */
    ID_MTA_AT_XCPOSR_QRY_CNF            = 0x1061,                               /* _H2ASN_MsgChoice MTA_AT_QRY_XCPOSR_CNF_STRU */
    ID_MTA_AT_XCPOSRRPT_SET_CNF         = 0x1062,                               /* _H2ASN_MsgChoice MTA_AT_RESULT_CNF_STRU */
    ID_MTA_AT_XCPOSRRPT_QRY_CNF         = 0x1063,                               /* _H2ASN_MsgChoice MTA_AT_QRY_XCPOSRRPT_CNF_STRU */
    ID_MTA_AT_CLEAR_HISTORY_FREQ_CNF    = 0x1064,   /* _H2ASN_MsgChoice MTA_AT_RESULT_CNF_STRU */

    ID_MTA_AT_SET_SENSOR_CNF           = 0x1065,     /* _H2ASN_MsgChoice MTA_AT_SET_SENSOR_CNF_STRU */
    ID_MTA_AT_SET_SCREEN_CNF           = 0x1066,     /* _H2ASN_MsgChoice MTA_AT_SET_SCREEN_CNF_STRU */
    ID_MTA_AT_FRAT_IGNITION_QRY_CNF     = 0x1067,                               /* _H2ASN_MsgChoice MTA_AT_FRAT_IGNITION_QRY_CNF_STRU */
    ID_MTA_AT_FRAT_IGNITION_SET_CNF     = 0x1068,                               /* _H2ASN_MsgChoice MTA_AT_FRAT_IGNITION_SET_CNF_STRU */

    ID_MTA_AT_SET_MODEM_TIME_CNF              = 0x1069,

    ID_MTA_AT_RX_TEST_MODE_SET_CNF      = 0x106A,

    ID_MTA_AT_AFC_CLK_UNLOCK_CAUSE_IND  = 0x106B,

    ID_MTA_AT_SIB16_TIME_UPDATE_IND     = 0x106C,

    ID_MTA_AT_SLAVE_SET_CNF             = 0x106D,

    ID_MTA_AT_BESTFREQ_SET_CNF          = 0x106E,
    ID_MTA_AT_BEST_FREQ_INFO_IND        = 0x106F,                             /* _H2ASN_MsgChoice MTA_AT_BEST_FREQ_CASE_STRU */
    ID_MTA_AT_BESTFREQ_QRY_CNF          = 0x1070,

    ID_MTA_AT_RFIC_DIE_ID_QRY_CNF       = 0x1071,

    /* Added by c00380008 for Wifi & VoLTE, 2016-8-30, begin */
    ID_MTA_AT_CRRCONN_SET_CNF           = 0x1072,
    ID_MTA_AT_CRRCONN_QRY_CNF           = 0x1073,
    ID_MTA_AT_CRRCONN_STATUS_IND        = 0x1074,
    ID_MTA_AT_VTRLQUALRPT_SET_CNF       = 0x1075,
    ID_MTA_AT_RL_QUALITY_INFO_IND       = 0x1076,
    ID_MTA_AT_VIDEO_DIAG_INFO_RPT       = 0x1077,
    /* Added by c00380008 for Wifi & VoLTE, 2016-8-30, end */

    ID_MTA_AT_PMU_DIE_SN_QRY_CNF        = 0x1078,

    ID_MTA_AT_MODEM_CAP_UPDATE_CNF      = 0x1079,

    ID_MTA_AT_LTE_CATEGORY_INFO_IND     = 0x107A,                               /* _H2ASN_MsgChoice MTA_AT_LTE_CATEGORY_INFO_IND_STRU */

    ID_MTA_AT_TAS_TEST_CFG_CNF          = 0x1080,
    ID_MTA_AT_TAS_TEST_QRY_CNF          = 0x1081,

    ID_MTA_AT_ACCESS_STRATUM_REL_IND    = 0x1082,

    ID_MTA_AT_MIPI_WREX_CNF             = 0x1083,
    ID_MTA_AT_MIPI_RDEX_CNF             = 0x1084,

    ID_MTA_AT_RS_INFO_QRY_CNF           = 0x1085,

    ID_MTA_AT_PHY_COM_CFG_SET_CNF       = 0x1086,

    /*  */
    ID_AT_MTA_MSG_TYPE_BUTT

};
typedef VOS_UINT32 AT_MTA_MSG_TYPE_ENUM_UINT32;

/*****************************************************************************
     : MTA_AT_RESULT_ENUM
   : MTAAT
1.      : 20120628
        : y00213812
    : V7R1C50 A_GPS
*****************************************************************************/
enum MTA_AT_RESULT_ENUM
{
    /* AT */
    MTA_AT_RESULT_NO_ERROR                      = 0x000000,                     /*  */
    MTA_AT_RESULT_ERROR,                                                        /*  */
    MTA_AT_RESULT_INCORRECT_PARAMETERS,
    MTA_AT_RESULT_OPTION_TIMEOUT,

    /* AT */

    /*  */
    MTA_AT_RESULT_DEVICE_ERROR_BASE             = 0x100000,
    MTA_AT_RESULT_DEVICE_SEC_IDENTIFY_FAIL,                                     /*  */
    MTA_AT_RESULT_DEVICE_SEC_SIGNATURE_FAIL,                                    /*  */
    MTA_AT_RESULT_DEVICE_SEC_DK_INCORRECT,                                      /*  */
    MTA_AT_RESULT_DEVICE_SEC_UNLOCK_KEY_INCORRECT,                              /*  */
    MTA_AT_RESULT_DEVICE_SEC_PH_PHYNUM_LEN_ERROR,                               /*  */
    MTA_AT_RESULT_DEVICE_SEC_PH_PHYNUM_VALUE_ERROR,                             /*  */
    MTA_AT_RESULT_DEVICE_SEC_PH_PHYNUM_TYPE_ERROR,                              /*  */
    MTA_AT_RESULT_DEVICE_SEC_RSA_ENCRYPT_FAIL,                                  /* RSA */
    MTA_AT_RESULT_DEVICE_SEC_RSA_DECRYPT_FAIL,                                  /* RSA */
    MTA_AT_RESULT_DEVICE_SEC_GET_RAND_NUMBER_FAIL,                              /* (crypto_rand) */
    MTA_AT_RESULT_DEVICE_SEC_WRITE_HUK_FAIL,                                    /* HUK */
    MTA_AT_RESULT_DEVICE_SEC_FLASH_ERROR,                                       /* Flash */
    MTA_AT_RESULT_DEVICE_SEC_NV_ERROR,                                          /* NV */
    MTA_AT_RESULT_DEVICE_SEC_OTHER_ERROR,                                       /*  */


    /*  */
    MTA_AT_RESULT_PRICMD_ERROR_BASE             = 0x200000,

    MTA_AT_RESULT_BUTT
};
typedef VOS_UINT32 MTA_AT_RESULT_ENUM_UINT32;

/*****************************************************************************
     : MTA_AT_CGPSCLOCK_ENUM
   : RFGPS
 1.       : 20120625
          : h44270
      : Added for AGPS
*****************************************************************************/
enum MTA_AT_CGPSCLOCK_ENUM
{
    MTA_AT_CGPSCLOCK_STOP           = 0,
    MTA_AT_CGPSCLOCK_START,
    MTA_AT_CGPSCLOCK_BUTT
};
typedef VOS_UINT32 MTA_AT_CGPSCLOCK_ENUM_UINT32;


/*****************************************************************************
     : MTA_AT_CPOS_OPERATE_TYPE_ENUM
   : +CPOS XML
 1.       : 20120625
          : h44270
      : Added for AGPS
*****************************************************************************/
enum MTA_AT_CPOS_OPERATE_TYPE_ENUM
{
    MTA_AT_CPOS_SEND                = 0,
    MTA_AT_CPOS_CANCEL,
    MTA_AT_CPOS_BUTT
};
typedef VOS_UINT32 MTA_AT_CPOS_OPERATE_TYPE_ENUM_UINT32;

/*****************************************************************************
    : AT_MTA_PERS_CATEGORY_ENUM
  : Category

  1.       : 2012918
           : l00198894
       : STKDCM
*****************************************************************************/
enum AT_MTA_PERS_CATEGORY_ENUM
{
    AT_MTA_PERS_CATEGORY_NETWORK                    = 0x00,                     /* Category:  */
    AT_MTA_PERS_CATEGORY_NETWORK_SUBSET             = 0x01,                     /* Category:  */
    AT_MTA_PERS_CATEGORY_SERVICE_PROVIDER           = 0x02,                     /* Category: SP */
    AT_MTA_PERS_CATEGORY_CORPORATE                  = 0x03,                     /* Category:  */
    AT_MTA_PERS_CATEGORY_SIM_USIM                   = 0x04,                     /* Category: (U)SIM */

    AT_MTA_PERS_CATEGORY_BUTT
};
typedef VOS_UINT8 AT_MTA_PERS_CATEGORY_ENUM_UINT8;

/* Added by s00217060 for ATC, 2013-3-25, begin */
/*****************************************************************************
    : AT_MTA_RPT_GENERAL_CTRL_TYPE_ENUM
  : 

  1.       : 2013325
           : s00217060
       : 
*****************************************************************************/
enum AT_MTA_RPT_GENERAL_CTRL_TYPE_ENUM
{
    AT_MTA_RPT_GENERAL_CONTROL_NO_REPORT      = 0x00,                           /*  */
    AT_MTA_RPT_GENERAL_CONTROL_REPORT         = 0x01,                           /*  */
    AT_MTA_RPT_GENERAL_CONTROL_CUSTOM         = 0x02,                           /* BIT */

    AT_MTA_RPT_GENERAL_CONTROL_BUTT
};
typedef VOS_UINT8 AT_MTA_RPT_GENERAL_CTRL_TYPE_ENUM_UINT8;

/*****************************************************************************
    : AT_MTA_RPT_SET_TYPE_ENUM
  : 

  1.       : 2013325
           : s00217060
       : 
*****************************************************************************/
enum AT_MTA_RPT_SET_TYPE_ENUM
{
    AT_MTA_SET_MODE_RPT_TYPE            = 0,                                 /* Category:  */
    AT_MTA_SET_SRVST_RPT_TYPE,
    AT_MTA_SET_RSSI_RPT_TYPE,
    AT_MTA_SET_TIME_RPT_TYPE,
    AT_MTA_SET_CTZR_RPT_TYPE,
    AT_MTA_SET_DSFLOWRPT_RPT_TYPE,
    AT_MTA_SET_SIMST_RPT_TYPE,
    AT_MTA_SET_CREG_RPT_TYPE,
    AT_MTA_SET_CGREG_RPT_TYPE,
    AT_MTA_SET_CEREG_RPT_TYPE,
    AT_MTA_SET_CSID_RPT_TYPE,
    AT_MTA_SET_CLOCINFO_RPT_TYPE,
    AT_MTA_SET_RPT_TYPE_BUTT
};
typedef VOS_UINT32 AT_MTA_RPT_SET_TYPE_ENUM_UINT32;

/*****************************************************************************
    : AT_MTA_RPT_QRY_TYPE_ENUM
  : 

  1.       : 2013410
           : l00167671
       : 
*****************************************************************************/
enum AT_MTA_RPT_QRY_TYPE_ENUM
{
    AT_MTA_QRY_TIME_RPT_TYPE = 0,
    AT_MTA_QRY_CTZR_RPT_TYPE,
    AT_MTA_QRY_CSSN_RPT_TYPE,
    AT_MTA_QRY_CUSD_RPT_TYPE,
    AT_MTA_QRY_RPT_TYPE_BUTT
};
typedef VOS_UINT32 AT_MTA_RPT_QRY_TYPE_ENUM_UINT32;

/* Added by s00217060 for ATC, 2013-3-25, end */

/*****************************************************************************
     : AT_MTA_CMD_RPT_FLG_ENUM
   : AT

  1.       : 20130722
           : l00198894
       : V9R1 AGPS
*****************************************************************************/
enum AT_MTA_CMD_RPT_FLG_ENUM
{
    AT_MTA_CMD_RPT_FLG_OFF              = 0,                        /* AT */
    AT_MTA_CMD_RPT_FLG_ON,                                          /* AT */
    AT_MTA_CMD_RPT_FLG_BUTT
};
typedef VOS_UINT8 AT_MTA_CMD_RPT_FLG_ENUM_UINT8;
/*****************************************************************************
     : AT_MTA_CMD_CLEAR_FREQ_FLG_ENUM
   : 

  1.       : 201624
           : y00358807
       :
*****************************************************************************/
enum AT_MTA_CLEAR_FREQ_FLG_ENUM
{
    AT_MTA_CLEAR_FREQ_FLG_NOT_CSG_HISTORY_FREQ              = 0,                /* CSG */
    AT_MTA_CLEAR_FREQ_FLG_CSG_HISTORY_FREQ,                                     /* CSG */
    AT_MTA_CLEAR_FREQ_FLG_ALL_FREQ,                                         /*  */
    AT_MTA_CLEAR_FREQ_FLG_BUTT
};
typedef VOS_UINT8 AT_MTA_CLEAR_FREQ_FLG_ENUM_UINT8;


/*****************************************************************************
     : AT_MTA_CMD_RATMODE_ENUM
   : ATRatMode

  1.       : 2014048
           : g00261581
       : 
*****************************************************************************/
enum AT_MTA_CMD_RATMODE_ENUM
{
    AT_MTA_CMD_RATMODE_GSM              = 0,
    AT_MTA_CMD_RATMODE_WCDMA,
    AT_MTA_CMD_RATMODE_LTE,
    AT_MTA_CMD_RATMODE_TD,
    AT_MTA_CMD_RATMODE_CDMA,
    AT_MTA_CMD_RATMODE_BUTT
};
typedef VOS_UINT8 AT_MTA_CMD_RATMODE_ENUM_UINT8;

/*****************************************************************************
     : MTA_AT_JAM_RESULT_ENUM
   : JAM DETECT REPORT

  1.       : 2014055
           : g00261581
       : 
*****************************************************************************/
enum MTA_AT_JAM_RESULT_ENUM
{
    MTA_AT_JAM_RESULT_JAM_DISAPPEARED        = 0x00,                            /*  */
    MTA_AT_JAM_RESULT_JAM_DISCOVERED,                                           /*  */

    MTA_AT_JAM_RESULT_BUTT
};
typedef VOS_UINT32 MTA_AT_JAM_RESULT_ENUM_UINT32;

/*****************************************************************************
     : AT_MTA_FREQLOCK_RATMODE_ENUM
   : ATMTA

  1.       : 20140611
           : g00261581
       : 
*****************************************************************************/
enum AT_MTA_FREQLOCK_RATMODE_ENUM
{
    AT_MTA_FREQLOCK_RATMODE_GSM         = 0x01,
    AT_MTA_FREQLOCK_RATMODE_WCDMA,
    AT_MTA_FREQLOCK_RATMODE_LTE,
    AT_MTA_FREQLOCK_RATMODE_CDMA1X,
    AT_MTA_FREQLOCK_RATMODE_TD,
    AT_MTA_FREQLOCK_RATMODE_WIMAX,
    AT_MTA_FREQLOCK_RATMODE_EVDO,

    AT_MTA_FREQLOCK_RATMODE_BUTT
};
typedef VOS_UINT8 AT_MTA_FREQLOCK_RATMODE_ENUM_UINT8;

/*****************************************************************************
     : AT_MTA_GSM_BAND_ENUM
   : ATMTABAND

  1.       : 20140611
           : g00261581
       : 
*****************************************************************************/
enum AT_MTA_GSM_BAND_ENUM
{
    AT_MTA_GSM_BAND_850                 = 0x00,
    AT_MTA_GSM_BAND_900,
    AT_MTA_GSM_BAND_1800,
    AT_MTA_GSM_BAND_1900,

    AT_MTA_GSM_BAND_BUTT
};
typedef VOS_UINT16 AT_MTA_GSM_BAND_ENUM_UINT16;

/*****************************************************************************
     : AT_MTA_CFG_ENUM
   : /

  1.       : 2015522
           : w00316404
       : 
*****************************************************************************/
enum AT_MTA_CFG_ENUM
{
    AT_MTA_CFG_DISABLE                  = 0,
    AT_MTA_CFG_ENABLE                   = 1,
    AT_MTA_CFG_BUTT
};
typedef VOS_UINT8 AT_MTA_CFG_ENUM_UINT8;

/*****************************************************************************
     : AT_MTA_MBMS_SERVICE_STATE_SET_ENUM
   : MBMS Service

  1.       : 2015522
           : w00316404
       : 
*****************************************************************************/
enum AT_MTA_MBMS_SERVICE_STATE_SET_ENUM
{
    AT_MTA_MBMS_SERVICE_STATE_SET_ACTIVE       = 0,
    AT_MTA_MBMS_SERVICE_STATE_SET_DEACTIVE     = 1,
    AT_MTA_MBMS_SERVICE_STATE_SET_DEACTIVE_ALL = 2,
    AT_MTA_MBMS_SERVICE_STATE_SET_BUTT
};
typedef VOS_UINT8 AT_MTA_MBMS_SERVICE_STATE_SET_ENUM_UINT8;

/*****************************************************************************
     : AT_MTA_MBMS_CAST_MODE_ENUM
   : MBMS/

  1.       : 2015522
           : w00316404
       : 
*****************************************************************************/
enum AT_MTA_MBMS_CAST_MODE_ENUM
{
    AT_MTA_MBMS_CAST_MODE_UNICAST       = 0,
    AT_MTA_MBMS_CAST_MODE_MULTICAST     = 1,
    AT_MTA_MBMS_CAST_MODE_BUTT
};
typedef VOS_UINT8 AT_MTA_MBMS_CAST_MODE_ENUM_UINT8;

/*****************************************************************************
     : MTA_AT_EMBMS_FUNTIONALITY_STATUS_ENUM
   : EMBMS 

  1.       : 2015522
           : w00316404
       : 
*****************************************************************************/
enum MTA_AT_EMBMS_FUNTIONALITY_STATUS_ENUM
{
    MTA_AT_EMBMS_FUNTIONALITY_OFF       = 0,
    MTA_AT_EMBMS_FUNTIONALITY_ON        = 1,
    MTA_AT_EMBMS_FUNTIONALITY_STATUS_BUTT
};
typedef VOS_UINT8 MTA_AT_EMBMS_FUNTIONALITY_STATUS_ENUM_UINT8;

/*****************************************************************************
     : MTA_AT_MBMS_SERVICE_EVENT_ENUM
   : MBMS 

  1.       : 2015522
           : w00316404
       : 
*****************************************************************************/
enum MTA_AT_MBMS_SERVICE_EVENT_ENUM
{
    MTA_AT_MBMS_SERVICE_EVENT_SERVICE_CHANGE       = 0,
    MTA_AT_MBMS_SERVICE_EVENT_NO_SERVICE           = 1,
    MTA_AT_MBMS_SERVICE_EVENT_ONLY_UNICAST         = 2,
    MTA_AT_MBMS_SERVICE_EVENT_SERVICE_AVAILABLE    = 3,
    MTA_AT_MBMS_SERVICE_EVENT_BUTT
};
typedef VOS_UINT8 MTA_AT_MBMS_SERVICE_EVENT_ENUM_UINT8;

/*****************************************************************************
     : AT_MTA_COEX_BW_TYPE_ENUM
   : LTE&WIFI

  1.       : 2015522
           : w00316404
       : 
*****************************************************************************/
enum AT_MTA_COEX_BW_TYPE_ENUM
{
    AT_MTA_COEX_BAND_WIDTH_6RB          = 0,                                    /* 1.4M */
    AT_MTA_COEX_BAND_WIDTH_15RB         = 1,                                    /* 3M */
    AT_MTA_COEX_BAND_WIDTH_25RB         = 2,                                    /* 5M */
    AT_MTA_COEX_BAND_WIDTH_50RB         = 3,                                    /* 10M */
    AT_MTA_COEX_BAND_WIDTH_75RB         = 4,                                    /* 15M */
    AT_MTA_COEX_BAND_WIDTH_100RB        = 5,                                    /* 20M */
    AT_MTA_COEX_BAND_WIDTH_BUTT
};
typedef VOS_UINT16 AT_MTA_COEX_BW_TYPE_ENUM_UINT16;

/*****************************************************************************
     : AT_MTA_COEX_CFG_ENUM
   : LTE&WIFI

  1.       : 2015522
           : w00316404
       : 

*****************************************************************************/
enum AT_MTA_COEX_CFG_ENUM
{
    AT_MTA_COEX_CFG_DISABLE             = 0,
    AT_MTA_COEX_CFG_ENABLE              = 1,
    AT_MTA_COEX_CFG_BUTT
};
typedef VOS_UINT16 AT_MTA_COEX_CFG_ENUM_UINT16;

/*****************************************************************************
     : AT_MTA_LTE_LOW_POWER_ENUM
   : 

  1.       : 2015522
           : w00316404
       : 

*****************************************************************************/
enum AT_MTA_LTE_LOW_POWER_ENUM
{
    AT_MTA_LTE_LOW_POWER_NORMAL         = 0,
    AT_MTA_LTE_LOW_POWER_LOW            = 1,
    AT_MTA_LTE_LOW_POWER_BUTT
};
typedef VOS_UINT8 AT_MTA_LTE_LOW_POWER_ENUM_UINT8;

/*****************************************************************************
     : AT_MTA_MBMS_PRIORITY_ENUM
   : 

  1.       : 2015522
           : w00316404
       : 

*****************************************************************************/
enum AT_MTA_MBMS_PRIORITY_ENUM
{
    AT_MTA_MBMS_PRIORITY_UNICAST        = 0,
    AT_MTA_MBMS_PRIORITY_MBMS           = 1,
    AT_MTA_MBMS_PRIORITY_BUTT
};
typedef VOS_UINT8 AT_MTA_MBMS_PRIORITY_ENUM_UINT8;


enum AT_MTA_UE_CENTER_TYPE_ENUM
{
    AT_MTA_UE_CENTER_VOICE_CENTRIC                          = 0,
    AT_MTA_UE_CENTER_DATA_CENTRIC                           = 1,
    AT_MTA_UE_CENTER_BUTT
};
typedef VOS_UINT32 AT_MTA_UE_CENTER_TYPE_ENUM_UINT32;

/*****************************************************************************
     : AT_MTA_BODY_SAR_STATE_ENUM
   : Body SAR 
 1.       : 20151030
          : w00316404
      : (AC)
*****************************************************************************/
enum AT_MTA_BODY_SAR_STATE_ENUM
{
    AT_MTA_BODY_SAR_OFF                 = 0,                                    /* Body SAR */
    AT_MTA_BODY_SAR_ON,                                                         /* Body SAR */
    AT_MTA_BODY_SAR_STATE_BUTT
};
typedef VOS_UINT16 AT_MTA_BODY_SAR_STATE_ENUM_UINT16;

/*****************************************************************************
     : MTA_AT_REFCLOCK_STATUS_ENUM
   : GPS

 1.       : 20151030
          : w00316404
      : (AC)
*****************************************************************************/
enum MTA_AT_REFCLOCK_STATUS_ENUM
{
    MTA_AT_REFCLOCK_UNLOCKED            = 0,                                    /* GPS */
    MTA_AT_REFCLOCK_LOCKED,                                                     /* GPS */
    MTA_AT_REFCLOCK_STATUS_BUTT
};
typedef VOS_UINT16 MTA_AT_REFCLOCK_STATUS_ENUM_UINT16;

/*****************************************************************************
     : MTA_AT_GPHY_XPASS_MODE_ENUM
   : G XPASS

 1.       : 20151030
          : w00316404
      : (AC)
*****************************************************************************/
enum MTA_AT_GPHY_XPASS_MODE_ENUM
{
    MTA_AT_GPHY_XPASS_MODE_DISABLE      = 0,                                    /* XPASS */
    MTA_AT_GPHY_XPASS_MODE_ENABLE,                                              /* XPASS */
    MTA_AT_GPHY_XPASS_MODE_BUTT
};
typedef VOS_UINT16 MTA_AT_GPHY_XPASS_MODE_ENUM_UINT16;

/*****************************************************************************
     : MTA_AT_WPHY_HIGHWAY_MODE_ENUM
   : W

 1.       : 20151030
          : w00316404
      : (AC)
*****************************************************************************/
enum MTA_AT_WPHY_HIGHWAY_MODE_ENUM
{
    MTA_AT_WPHY_HIGHWAY_MODE_DISABLE    = 0,                                    /* W */
    MTA_AT_WPHY_HIGHWAY_MODE_ENABLE,                                            /* W */
    MTA_AT_WPHY_HIGHWAY_MODE_BUTT
};
typedef VOS_UINT16 MTA_AT_WPHY_HIGHWAY_MODE_ENUM_UINT16;

/*****************************************************************************
     : MTA_AT_NETMON_GSM_STATE_ENUM
   : network monitor GSMf

  1.       : 20151019
           : zwx247453
       : 
*****************************************************************************/
enum MTA_AT_NETMON_GSM_STATE_ENUM
{
   MTA_AT_NETMON_GSM_STATE_INIT   = 0,
   MTA_AT_NETMON_GSM_STATTE_WAIT_CELL_INFO  = 1,
   MTA_AT_NETMON_GSM_STATTE_WAIT_TA  = 2,
   MTA_AT_NETMON_GSM_STATTE_BUTT
};

typedef VOS_UINT32 MTA_AT_NETMON_GSM_STATE_ENUM_UINT32;

/*****************************************************************************
     : MTA_AT_NETMON_CELL_INFO_RESULT_ENUM
   : network monitor 

  1.       : 20151019
           : zwx247453
       : 
*****************************************************************************/

enum MTA_AT_NETMON_CELL_INFO_RAT_ENUM
{
    MTA_AT_NETMON_CELL_INFO_GSM         = 0,
    MTA_AT_NETMON_CELL_INFO_UTRAN_FDD   = 1,
    MTA_AT_NETMON_CELL_INFO_UTRAN_TDD   = 2,
    MTA_AT_NETMON_CELL_INFO_LTE         = 3,
    MTA_AT_NETMON_CELL_INFO_RAT_BUTT
};
typedef VOS_UINT32 MTA_AT_NETMON_CELL_INFO_RAT_ENUM_UINT32;


/*****************************************************************************
     : MTA_TAF_CTZR_TYPE
   : CTZR

  1.       : 20151117
           : h00360002
       : 
*****************************************************************************/

enum MTA_TAF_CTZR_TYPE
{
    MTA_TAF_CTZR_OFF            = 0x00,            /* CTZR */
    MTA_TAF_CTZR_CTZV           = 0x01,            /* CTZR:CTZV */
    MTA_TAF_CTZR_CTZE           = 0x02,            /* CTZR:CTZE */
    MTA_TAF_CTZR_BUTT
};
typedef VOS_UINT32 MTA_TAF_CTZR_TYPE_ENUM_UINT32;

/*****************************************************************************
    : AT_MTA_TYPE_ENUM
  : 

  1.       : 20151225
           : C00299064
       : 
*****************************************************************************/
enum AT_MTA_AFC_CLK_STATUS_ENUM
{
    AT_MTA_AFC_CLK_UNLOCKED           = 0,                                     /* AFC UNLOCKED */
    AT_MTA_AFC_CLK_LOCKED,                                                     /* AFC LOCKED */

    AT_MTA_AFC_CLK_STATUS_BUTT
};
typedef VOS_UINT32 AT_MTA_AFC_CLK_STATUS_ENUM_UINT32;

/*****************************************************************************
    : AT_MTA_XCPOSR_CFG_ENUM
  : AT^XCPOSRGPS

  1.       : 20160308
           : h00360002
       : 
*****************************************************************************/
enum AT_MTA_XCPOSR_CFG_ENUM
{
    AT_MTA_XCPOSR_CFG_DISABLE        = 0,                                       /*  */
    AT_MTA_XCPOSR_CFG_ENABLE,                                                   /*  */
    AT_MTA_XCPOSR_CFG_BUTT
};
typedef VOS_UINT8 AT_MTA_XCPOSR_CFG_ENUM_UNIT8;

/*****************************************************************************
    : AT_MTA_FRAT_IGNITION_ENUM
  : AT^fratIgnition ignition state


  1.       : 2016426
           : c00318887
       : 
*****************************************************************************/
enum AT_MTA_FRAT_IGNITION_ENUM
{
    AT_MTA_FRAT_IGNITION_STATT_OFF        = 0,                                  /*  */
    AT_MTA_FRAT_IGNITION_STATT_ON,                                                   /*  */
    AT_MTA_FRAT_IGNITION_STATT_BUTT
};
typedef VOS_UINT8 AT_MTA_FRAT_IGNITION_ENUM_UNIT8;


/*****************************************************************************
    : MTA_AT_AFC_CLK_UNLOCK_CAUSE_ENUM
  : AFC

  1.       : 20160705
           : wx270776
       : 
*****************************************************************************/
enum MTA_AT_AFC_CLK_UNLOCK_CAUSE_ENUM
{
    MTA_AT_AFC_CLK_UNLOCK_CAUSE_SLEEP,

    MTA_AT_AFC_CLK_UNLOCK_CAUSE_BUTT
};
typedef VOS_UINT16  MTA_AT_AFC_CLK_UNLOCK_CAUSE_ENUM_UINT16;

/*****************************************************************************
    : MTA_AT_MODEM_ID_ENUM
  : MTAAT Modem ID

  1.       : 20160707
           : wx270776
       : 
*****************************************************************************/
enum MTA_AT_MODEM_ID_ENUM
{
    MTA_AT_MODEM_ID_0  = 0,
    MTA_AT_MODEM_ID_1,
    MTA_AT_MODEM_ID_2,

    MTA_AT_MODEM_ID_BUTT
};
typedef VOS_UINT8 MTA_AT_MODEM_ID_ENUM_UINT8;

/*****************************************************************************
    : MTA_AT_RAT_MODE_ENUM
  : MTAAT Rat Mode

  1.       : 20160707
           : wx270776
       : 
*****************************************************************************/
enum MTA_AT_RAT_MODE_ENUM
{
    MTA_AT_RAT_MODE_GSM       = 0,
    MTA_AT_RAT_MODE_WCDMA,
    MTA_AT_RAT_MODE_LTE,
    MTA_AT_RAT_MODE_TDSCDMA,
    MTA_AT_RAT_MODE_CDMA_1X,
    MTA_AT_RAT_MODE_HRPD,

    MTA_AT_RAT_MODE_BUTT
};
typedef VOS_UINT8 MTA_AT_RAT_MODE_ENUM_UINT8;

/*****************************************************************************
     : MTA_AT_DAY_LIGHT_SAVING_IND_ENUM
   : 

  1.       : 2016525
           : wx270776
       : 
*****************************************************************************/
enum MTA_AT_DAY_LIGHT_SAVING_IND_ENUM
{
    MTA_AT_NO_ADJUST                  = 0,
    MTA_AT_ONE_HOUR                   = 1,
    MTA_AT_TWO_HOUR                   = 2,
    MTA_AT_HOUR_BUTT
};
typedef VOS_UINT8   MTA_AT_DAY_LIGHT_SAVING_IND_ENUM_UINT8;

/*****************************************************************************
    : MTA_AT_TIME_TYPE_ENUM
  : 

  1.       : 2016525
           : wx270776
       : 
*****************************************************************************/
enum MTA_AT_TIME_TYPE_ENUM
{
    MTA_AT_LOCAL_TIME                 = 1,
    MTA_AT_GPS_TIME                   = 2,
    MTA_AT_LOCAL_GPS_TIME             = 3,
    MTA_AT_TIME_BUTT
};
typedef VOS_UINT8   MTA_AT_TIME_TYPE_ENUM_UINT8;

/*****************************************************************************
    : AT_MTA_MODEM_CAP_UPDATE_TYPE_ENUM
  : ATMTAModem

  1.       : 201688
           : h00313353
       : New
*****************************************************************************/
enum AT_MTA_MODEM_CAP_UPDATE_TYPE_ENUM
{
    AT_MTA_MODEM_CAP_UPDATE_TYPE_CDMA_MODEM_SWITCH   = 0x00U,       /* AT^CDMAMODEMSWITCH */
    AT_MTA_MODEM_CAP_UPDATE_TYPE_ACTIVE_MODEM        = 0x01U,       /* AT^ACTIVEMODEM */

    AT_MTA_MODEM_CAP_UPDATE_TYPE_BUTT
};
typedef VOS_UINT8 AT_MTA_MODEM_CAP_UPDATE_TYPE_ENUM_UINT8;

/*****************************************************************************
     : AT_MTA_RS_INFO_TYPE_ENUM
   : MTAAT

  1.       : 20170118
           : wx270776
       : 
*****************************************************************************/
enum AT_MTA_RS_INFO_TYPE_ENUM
{
    AT_MTA_RSRP_TYPE                     = 0,
    AT_MTA_RSRQ_TYPE                     = 1,
    AT_MTA_RS_INFO_TYPE_BUTT
};
typedef VOS_UINT32 AT_MTA_RS_INFO_TYPE_ENUM_UINT32;

/*****************************************************************************
  4 
*****************************************************************************/
/*****************************************************************************
  5 
*******************************s**********************************************/
/*****************************************************************************
  6 
*****************************************************************************/
/*****************************************************************************
  7 STRUCT
*****************************************************************************/

/*****************************************************************************
    : AT_MTA_MSG_STRU
  : ATMTA
1.      : 20120628
        : y00213812
    : V7R1C50 A_GPS
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;                                /*  */
    AT_APPCTRL_STRU                     stAppCtrl;
    VOS_UINT8                           aucContent[4];                          /*  */
} AT_MTA_MSG_STRU;

/*****************************************************************************
    : MTA_AT_CPOS_REQ_MSG_STRU
  : AT+CPOS
1.      : 20120628
        : y00213812
    : V7R1C50 A_GPS
*****************************************************************************/
typedef struct
{
    MTA_AT_CPOS_OPERATE_TYPE_ENUM_UINT32    enCposOpType;
    VOS_UINT32                              ulXmlLength;
    VOS_CHAR                                acXmlText[MTA_CPOS_XML_MAX_LEN];
} AT_MTA_CPOS_REQ_STRU;

/*****************************************************************************
    : MTA_AT_CPOS_CNF_STRU
  : AT+CPOS
1.      : 20120628
        : y00213812
    : V7R1C50 A_GPS
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;                               /*  */
} MTA_AT_CPOS_CNF_STRU;

/*****************************************************************************
    : MTA_AT_CPOSR_IND_STRU
  : +CPOSR
1.      : 20120628
        : y00213812
    : V7R1C50 A_GPS
*****************************************************************************/
typedef struct
{
    /* ATMTAXML1024 */
    VOS_CHAR                            acXmlText[MTA_CPOSR_XML_MAX_LEN + 1];
    VOS_UINT8                           aucRsv[3];
} MTA_AT_CPOSR_IND_STRU;

/*****************************************************************************
    : MTA_AT_XCPOSRRPT_IND_STRU
  : ^XCPOSRRPT
1.      : 20120628
        : y00213812
    : V7R1C50 A_GPS
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulClearFlg;
} MTA_AT_XCPOSRRPT_IND_STRU;

/*****************************************************************************
    : AT_MTA_CGPSCLOCK_REQ_STRU
  : AT^CGPSCLOCK
1.      : 20120628
        : y00213812
    : V7R1C50 A_GPS
*****************************************************************************/
typedef struct
{
    MTA_AT_CGPSCLOCK_ENUM_UINT32        enGpsClockState;                        /* RFGPS */
} AT_MTA_CGPSCLOCK_REQ_STRU;

/*****************************************************************************
    : MTA_AT_CGPSCLOCK_CNF_STRU
  : AT^CGPSCLOCK
1.      : 20120628
        : y00213812
    : V7R1C50 A_GPS
2.      : 201679
        : wx270776
    : CGPS CLOCK OPT
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;                               /*  */

    MTA_AT_MODEM_ID_ENUM_UINT8          enModemId;
    MTA_AT_RAT_MODE_ENUM_UINT8          enRatMode;

    VOS_UINT8                           aucReserved[2];
} MTA_AT_CGPSCLOCK_CNF_STRU;

/*****************************************************************************
    : AT_MTA_SIMLOCKUNLOCK_REQ_STRU
  : AT^SIMLOCKUNLOCK
1.      : 20120918
        : l00198894
    : STKDCM
*****************************************************************************/
typedef struct
{
    AT_MTA_PERS_CATEGORY_ENUM_UINT8     enCategory;
    VOS_UINT8                           aucReserved[3];
    VOS_UINT8                           aucPassword[MTA_SIMLOCK_PASSWORD_LEN];
} AT_MTA_SIMLOCKUNLOCK_REQ_STRU;

/*****************************************************************************
    : MTA_AT_SIMLOCKUNLOCK_CNF_STRU
  : AT^SIMLOCKUNLOCK
1.      : 20120918
        : l00198894
    : STKDCM
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;                               /*  */
} MTA_AT_SIMLOCKUNLOCK_CNF_STRU;


/*****************************************************************************
     : AT_MTA_QRY_NMR_REQ_STRU
   : ATNMR

  1.       : 20121123
           : z00161729
       : NMR

*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucRatType;
    VOS_UINT8                           aucReserve[3];                          /*  */
}AT_MTA_QRY_NMR_REQ_STRU;

/*****************************************************************************
     : MTA_AT_QRY_NMR_CNF_STRU
   : mtaatnmr

  1.       : 20121123
           : z00161729
       : NMR

*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32         enResult;
    VOS_UINT8                         ucTotalIndex;
    VOS_UINT8                         ucCurrIndex;
    VOS_UINT16                        usNMRLen;                                 /* NMR */
    VOS_UINT8                         aucNMRData[4];                            /* NMR */
}MTA_AT_QRY_NMR_CNF_STRU;



/*****************************************************************************
     : AT_MTA_RESEL_OFFSET_CFG_SET_REQ_STRU
   : ATMTAWLTHRESHOLDCFG
  1.       : 20121210
           : t00212959
       : WLTHRESHOLDCFG

*****************************************************************************/
typedef struct
{
    VOS_UINT8                                   ucOffsetFlg;                    /* 0:1:*/
    VOS_UINT8                                   aucReserve[3];                  /*  */
}AT_MTA_RESEL_OFFSET_CFG_SET_NTF_STRU;

/*****************************************************************************
     : AT_MTA_WRR_AUTOTEST_QRY_PARA_STRU
   : AS

  1.       : 20121229
           : m00217266
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCmd;
    VOS_UINT8                           ucParaNum;
    VOS_UINT16                          usReserve;
    VOS_UINT32                          aulPara[AT_MTA_WRR_AUTOTEST_MAX_PARA_NUM];
}AT_MTA_WRR_AUTOTEST_QRY_PARA_STRU;

/*****************************************************************************
     : MTA_AT_WRR_AUTOTEST_QRY_RSLT_STRU
   : WAS

  1.       : 20121229
           : m00217266
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulRsltNum;
    VOS_UINT32                          aulRslt[MTA_AT_WRR_AUTOTEST_MAX_RSULT_NUM];
}MTA_AT_WRR_AUTOTEST_QRY_RSLT_STRU;

/*****************************************************************************
     : MTA_AT_WRR_AUTOTEST_QRY_CNF_STRU
   : WAS

  1.       : 20121229
           : m00217266
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulResult;
    MTA_AT_WRR_AUTOTEST_QRY_RSLT_STRU   stWrrAutoTestRslt;
} MTA_AT_WRR_AUTOTEST_QRY_CNF_STRU;

/*****************************************************************************
     : MTA_AT_WRR_CELLINFO_STRU
   : 

  1.       : 20121229
           : m00217266
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT16                      usCellFreq;
    VOS_UINT16                      usPrimaryScramCode;
    VOS_INT16                       sCpichRscp;
    VOS_INT16                       sCpichEcN0;

}MTA_AT_WRR_CELLINFO_STRU;

/*****************************************************************************
     : MTA_AT_WRR_CELLINFO_RSLT_STRU
   : WRRMTA

  1.       : 20121229
           : m00217266
       : 
*****************************************************************************/
typedef struct
{
     VOS_UINT32                     ulCellNum;
     MTA_AT_WRR_CELLINFO_STRU       astWCellInfo[MTA_AT_WRR_MAX_NCELL_NUM];         /*W 8*/

} MTA_AT_WRR_CELLINFO_RSLT_STRU;
/*****************************************************************************
     : MTA_AT_WRR_CELLINFO_QRY_CNF_STRU
   : WRRMTA

  1.       : 20121229
           : m00217266
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulResult;
    MTA_AT_WRR_CELLINFO_RSLT_STRU       stWrrCellInfo;
} MTA_AT_WRR_CELLINFO_QRY_CNF_STRU;

/*****************************************************************************
     : MTA_AT_WRR_MEANRPT_STRU
   : +

  1.       : 20121229
           : m00217266
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT16                      usEventId;                                  /**/
    VOS_UINT16                      usCellNum;
    VOS_UINT16                      ausPrimaryScramCode[MTA_AT_WRR_ONE_MEANRPT_MAX_CELL_NUM];
}MTA_AT_WRR_MEANRPT_STRU;

/*****************************************************************************
     : MTA_AT_WRR_MEANRPT_RSLT_STRU
   : AT^MEANRPT,
             10+

  1.       : 20121229
           : m00217266
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT32                      ulRptNum;
    MTA_AT_WRR_MEANRPT_STRU         astMeanRptInfo[MTA_AT_WRR_MAX_MEANRPT_NUM];
}MTA_AT_WRR_MEANRPT_RSLT_STRU;

/*****************************************************************************
     : MTA_AT_WRR_MEANRPT_QRY_CNF_STRU
   : WRRMTA^MEANRPT

  1.       : 20121229
           : m00217266
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulResult;
    MTA_AT_WRR_MEANRPT_RSLT_STRU        stMeanRptRslt;
} MTA_AT_WRR_MEANRPT_QRY_CNF_STRU;

/*****************************************************************************
     : MTA_AT_WRR_CSNR_QRY_CNF_STRU
   : WRRMTACSNRMTARscp EcNoRssi CellId
            AT

  1.       : 20151224
           : n00355355
       : 
*****************************************************************************/
typedef struct
{
    VOS_INT16                           sCpichRscp;
    VOS_INT16                           sCpichEcNo;
}MTA_AT_ANTENNA_QRY_CNF_STRU;

/*****************************************************************************
     : MTA_AT_WRR_FREQLOCK_CTRL_STRU
   : WAS

  1.       : 20121229
           : m00217266
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucFreqLockEnable;
    VOS_UINT8                           aucReserved[1];
    VOS_UINT16                          usLockedFreq;
} MTA_AT_WRR_FREQLOCK_CTRL_STRU;

/*****************************************************************************
     : MTA_AT_WRR_FREQLOCK_SET_CNF_STRU
   : MTAAT

  1.       : 20121229
           : m00217266
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulResult;
} MTA_AT_WRR_FREQLOCK_SET_CNF_STRU;

/*****************************************************************************
     : MTA_AT_WRR_FREQLOCK_QRY_CNF_STRU
   : MTAAT

  1.       : 20121229
           : m00217266
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulResult;
    MTA_AT_WRR_FREQLOCK_CTRL_STRU       stFreqLockInfo;
} MTA_AT_WRR_FREQLOCK_QRY_CNF_STRU;

/*****************************************************************************
     : MTA_AT_WRR_RRC_VERSION_SET_CNF_STRU
   : WRRMTAversion

  1.       : 20121229
           : m00217266
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulResult;
} MTA_AT_WRR_RRC_VERSION_SET_CNF_STRU;

/*****************************************************************************
     : MTA_AT_WRR_RRC_VERSION_QRY_CNF_STRU
   : WRRMTAversion

  1.       : 20121229
           : m00217266
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucRrcVersion;
    VOS_UINT8                           aucReserved[3];
} MTA_AT_WRR_RRC_VERSION_QRY_CNF_STRU;

/*****************************************************************************
     : MTA_AT_WRR_CELLSRH_SET_CNF_STRU
   : WRRMTAcellsrh

  1.       : 20121229
           : m00217266
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulResult;
} MTA_AT_WRR_CELLSRH_SET_CNF_STRU;

/*****************************************************************************
     : MTA_AT_WRR_CELLSRH_QRY_CNF_STRU
   : WRRMTAcellsrh

  1.       : 20121229
           : m00217266
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucCellSearchType;
    VOS_UINT8                           aucReserve[3];
} MTA_AT_WRR_CELLSRH_QRY_CNF_STRU;

/*****************************************************************************
    : AT_MMA_ANQUERY_2G_3G_PARA_STRU
  : AT^ANQUERY2G/3G
  1.       : 2016112
           : n00355355
       : 
*******************************************************************************/
typedef struct
{
    VOS_INT16                           sCpichRscp;
    VOS_INT16                           sCpichEcNo;
    VOS_UINT32                          ulCellId;
    VOS_UINT8                           ucRssi;                                 /* Rssi, GU*/
    VOS_UINT8                           aucReserve[3];

}AT_MTA_ANQUERY_2G_3G_PARA_STRU;

/*****************************************************************************
    : AT_MMA_ANQUERY_4G_PARA_STRU
  : AT^ANQUERYLTE

  1.       : 2016112
           : n00355355
       : 
*******************************************************************************/
typedef struct
{
    VOS_INT16                           sRsrp;                                  /* (-141,-44), 99 */
    VOS_INT16                           sRsrq;                                  /* (-40, -6) , 99 */
    VOS_INT16                           sRssi;                                  /* Rssi, LTE*/
    VOS_UINT8                           aucReserve[2];
}AT_MTA_ANQUERY_4G_PARA_STRU;

/*****************************************************************************
    : AT_MMA_ANQUERY_PARA_STRU
  : AT^ANQUERY
  1.       : 2016112
           : n00355355
       : 
*******************************************************************************/
typedef struct
{
    VOS_UINT8                               enServiceSysMode;                       /* */
    VOS_UINT8                               aucReserve[3];
    union
    {
        AT_MTA_ANQUERY_2G_3G_PARA_STRU      st2G3GCellSignInfo;                     /* Rssi, GU*/
        AT_MTA_ANQUERY_4G_PARA_STRU         st4GCellSignInfo;                       /* Rssi, LTE*/
    }u;
}AT_MTA_ANQUERY_PARA_STRU;

/*****************************************************************************
    : MMA_AT_ANTENNA_INFO_QRY_CNF_STRU
  : Antenna Info qry cnf stru

  1.       : 20151223
           : n00355355
       : 
******************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;      /*  */
    AT_MTA_ANQUERY_PARA_STRU            stAntennaInfo;
}MTA_AT_ANTENNA_INFO_QRY_CNF_STRU;

/*****************************************************************************
    : AT_MMA_CSNR_PARA_STRU
  : AT+CSNR

  1.       : 2016112
           : n00355355
       : 
*******************************************************************************/
typedef struct
{
    VOS_INT16                           sCpichRscp;
    VOS_INT16                           sCpichEcNo;
}AT_MTA_CSNR_PARA_STRU;

/*****************************************************************************
    : MMA_AT_ANTENNA_INFO_QRY_CNF_STRU
  : Csnr Info qry cnf stru

  1.       : 20151223
           : n00355355
       : 
******************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;      /*  */
    AT_MTA_CSNR_PARA_STRU              stCsnrPara;
}MTA_AT_CSNR_QRY_CNF_STRU;

/*****************************************************************************
     : AT_MMA_CSQLVL_PARA_STRU
   : CSQLVL
             RSCP RSCP 
*******************************************************************************/
typedef struct
{
    VOS_UINT16                          usRscp;                                 /* RSCP  */
    VOS_UINT16                          usLevel;                                /* RSCP  */
}AT_MTA_CSQLVL_PARA_STRU;

/*****************************************************************************
     : AT_MMA_CSQLVLEXT_PARA_STRU
   :
 ASN.1 :
   : CSQLVLEX
             CSQLVLEXBER99

  1.       : 2016112
           : n00355355
       : 
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           enRssilv;                         /* CSQLVLEX */
    VOS_UINT8                           enBer;                            /* BER99*/
}AT_MTA_CSQLVLEXT_PARA_STRU;

/*****************************************************************************
    : MMA_AT_ANTENNA_INFO_QRY_CNF_STRU
  : CSQLVL Info qry cnf stru

  1.       : 20151223
           : n00355355
       : 
******************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;      /*  */
    AT_MTA_CSQLVL_PARA_STRU             stCsqLvlPara;
    AT_MTA_CSQLVLEXT_PARA_STRU          stCsqLvlExtPara;
    VOS_UINT8                           aucReserved[2];
}MTA_AT_CSQLVL_QRY_CNF_STRU;

/*****************************************************************************
    : MTA_AT_FRAT_IGNITION_QRY_CNF_STRU
  : fratIgnition qry cnf content

  1.       : 2016421
           : c00318887
       : FRAT IGNITION project 
******************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;                               /*  */
    AT_MTA_FRAT_IGNITION_ENUM_UNIT8     enFratIgnitionState;                    /* IgnitionState */
    VOS_UINT8                           aucReserved[3];
}MTA_AT_FRAT_IGNITION_QRY_CNF_STRU;

/*****************************************************************************
     : AT_MTA_FRAT_IGNITION_SET_REQ_STRU
   : fratIgnition set req content

   1.       : 2016421
            : c00318887
        : FRAT IGNITION project 

*****************************************************************************/
typedef struct
{
    AT_MTA_FRAT_IGNITION_ENUM_UNIT8     enFratIgnitionState;                    /* IgnitionState */
    VOS_UINT8                           aucReserved[3];
} AT_MTA_FRAT_IGNITION_SET_REQ_STRU;

/*****************************************************************************
     : AT_MTA_FRAT_IGNITION_SET_REQ_STRU
   : fratIgnition set cnf content

   1.       : 2016421
            : c00318887
        : FRAT IGNITION project 

*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;                               /* */
} MTA_AT_FRAT_IGNITION_SET_CNF_STRU;


/*****************************************************************************
     : AT_MTA_BODY_SAR_SET_REQ_STRU
   : ATMTABODYSAR
  1.       : 20130311
           : z00214637
       : ^BODYSARON
*****************************************************************************/
typedef struct
{
    AT_MTA_BODY_SAR_STATE_ENUM_UINT16   enState;       /* Body SAR */
    VOS_UINT16                          usRsv;         /*  */
    MTA_BODY_SAR_PARA_STRU              stBodySARPara; /* Body SAR */
}AT_MTA_BODY_SAR_SET_REQ_STRU;

/*******************************************************************************
     : MTA_AT_RESULT_CNF_STRU
   : AT
 1.       : 20130311
          : z00214637
      : 
*******************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;      /*  */
}MTA_AT_RESULT_CNF_STRU;

/*******************************************************************************
     : AT_MTA_RESERVE_STRU
   : ATMTA
 1.       : 20130311
          : z00214637
      : 
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           aucReserved[4]; /*  */
}AT_MTA_RESERVE_STRU;

/* Added by s00217060 for ATC, 2013-3-25, begin */
/*****************************************************************************
     : AT_MTA_CSSN_RPT_FLG_STRU
   : CSSNCSSICSSU

  1.       : 2013325
           : s00217060
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCssiRptFlg;                           /* +CSSI 0:;1: */
    VOS_UINT8                           ucCssuRptFlg;                           /* +CSSU 0:;1: */
} AT_MTA_CSSN_RPT_FLG_STRU;

/*****************************************************************************
     : AT_MTA_CURC_SET_NOTIFY_STRU
   : ATMTACURC

  1.       : 2013325
           : s00217060
       : 
*****************************************************************************/
typedef struct
{
    AT_MTA_RPT_GENERAL_CTRL_TYPE_ENUM_UINT8     enCurcRptType;                  /* 0:1:2:RptCfgbit */
    VOS_UINT8                                   aucReserve[3];                  /*  */
    VOS_UINT8                                   aucRptCfg[AT_MTA_RPT_CFG_MAX_SIZE];                   /* 64bit */
} AT_MTA_CURC_SET_NOTIFY_STRU;

/*****************************************************************************
     : AT_MTA_CURC_QRY_REQ_STRU
   : ATMTACURC

  1.       : 2013325
           : s00217060
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucReserve[4];
} AT_MTA_CURC_QRY_REQ_STRU;

/*****************************************************************************
     : AT_MTA_UNSOLICITED_RPT_SET_REQ_STRU
   : ATMTA

  1.       : 2013325
           : s00217060
       : 
*****************************************************************************/
typedef struct
{
    AT_MTA_RPT_SET_TYPE_ENUM_UINT32     enReqType;                              /*  */

    union
    {
        VOS_UINT8                       ucModeRptFlg;                           /* mode 0:1: */
        VOS_UINT8                       ucSrvstRptFlg;                          /* service status */
        VOS_UINT8                       ucRssiRptFlg;                           /* rssi */
        VOS_UINT8                       ucTimeRptFlg;                           /* time */
        VOS_UINT8                       ucCtzrRptFlg;                           /* ctzr */
        VOS_UINT8                       ucDsFlowRptFlg;                         /*  */
        VOS_UINT8                       ucSimstRptFlg;                          /* sim */
        VOS_UINT8                       ucCregRptFlg;                           /* cs */
        VOS_UINT8                       ucCgregRptFlg;                          /* ps */
        VOS_UINT8                       ucCeregRptFlg;                          /* L */
        VOS_UINT8                       ucCsidRptFlg;                           /* CSID */
        VOS_UINT8                       ucClocinfoRptFlg;                       /* CLOCINFO */
    }u;

    VOS_UINT8                           aucReserve[3];

 } AT_MTA_UNSOLICITED_RPT_SET_REQ_STRU;

/*****************************************************************************
     : AT_MTA_UNSOLICITED_RPT_QRY_REQ_STRU
   : ATMTA

  1.       : 2013325
           : s00217060
       : 
*****************************************************************************/
typedef struct
{
    AT_MTA_RPT_QRY_TYPE_ENUM_UINT32     enReqType;
} AT_MTA_UNSOLICITED_RPT_QRY_REQ_STRU;

/*****************************************************************************
     : AT_MTA_NCELL_MONITOR_SET_REQ_STRU
   : ATMTANCELLMONITOR

  1.       : 2013325
           : s00217060
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucSwitch;
    VOS_UINT8                           aucReserve[3];
} AT_MTA_NCELL_MONITOR_SET_REQ_STRU;

/*****************************************************************************
     : AT_MTA_CLEAR_HISTORY_FREQ_REQ_STRU
   : ATMTACHISFREQ

  1.       : 201624
           : y00358807
       : 
*****************************************************************************/
typedef struct
{
    AT_MTA_CLEAR_FREQ_FLG_ENUM_UINT8    enMode;
    VOS_UINT8                           aucReserved[3];
} AT_MTA_CLEAR_HISTORY_FREQ_REQ_STRU;


/*****************************************************************************
     : MTA_AT_CURC_QRY_CNF_STRU
   : MTAATCURC

  1.       : 2013325
           : s00217060
       : 
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32                   enResult;
    AT_MTA_RPT_GENERAL_CTRL_TYPE_ENUM_UINT8     enCurcRptType;                          /* 0:1:2:ReportCfgbit */
    VOS_UINT8                                   aucReserve[3];
    VOS_UINT8                                   aucRptCfg[AT_MTA_RPT_CFG_MAX_SIZE];  /*  */
} MTA_AT_CURC_QRY_CNF_STRU;

/*****************************************************************************
     : MTA_AT_UNSOLICITED_RPT_SET_CNF_STRU
   : MTAAT

  1.       : 2013325
           : s00217060
       : 
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
} MTA_AT_UNSOLICITED_RPT_SET_CNF_STRU;

/*****************************************************************************
     : MTA_AT_UNSOLICITED_RPT_QRY_CNF_STRU
   : MTAAT

  1.       : 2013325
           : s00217060
       : 
  2.       : 20151119
           : h00360002
       : ctzrctze
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
    AT_MTA_RPT_QRY_TYPE_ENUM_UINT32     enReqType;

    union
    {
        VOS_UINT8                       ucTimeRptFlg;                           /* time */
        MTA_TAF_CTZR_TYPE_ENUM_UINT32   ucCtzrRptFlg;                           /* ctzr */
        AT_MTA_CSSN_RPT_FLG_STRU        stCssnRptFlg;                           /* cssn */
        VOS_UINT8                       ucCusdRptFlg;                           /* cusd */
    }u;

} MTA_AT_UNSOLICITED_RPT_QRY_CNF_STRU;

/* Added by s00217060 for ATC, 2013-3-25, end */


/*******************************************************************************
     : MTA_AT_CGSN_QRY_CNF_STRU
   : ID_MTA_AT_CGSN_QRY_CNF
 1.       : 20130525
          : Y00213812
      : 
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           aucImei[NV_ITEM_IMEI_SIZE]; /* IMEI */
}MTA_AT_CGSN_QRY_CNF_STRU;
/*****************************************************************************
     : MTA_AT_NCELL_MONITOR_QRY_CNF_STRU
   : MTAAT

  1.       : 2013531
           : s00217060
       : 
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
    VOS_UINT8                           ucSwitch;
    VOS_UINT8                           ucNcellState;
    VOS_UINT8                           aucReserved[2];
} MTA_AT_NCELL_MONITOR_QRY_CNF_STRU;

/*****************************************************************************
     : MTA_AT_NCELL_MONITOR_IND_STRU
   : MTAAT

  1.       : 2013531
           : s00217060
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNcellState;
    VOS_UINT8                           aucReserved[3];
} MTA_AT_NCELL_MONITOR_IND_STRU;


/*****************************************************************************
    : AT_MTA_REFCLKFREQ_SET_REQ_STRU
  : AT^REFCLKFREQ

1.       : 20130722
         : l00198894
     : V9R1 AGPS
*****************************************************************************/
typedef struct
{
    AT_MTA_CMD_RPT_FLG_ENUM_UINT8       enRptFlg;                               /*  */
    VOS_UINT8                           aucReserved1[3];                        /*  */
} AT_MTA_REFCLKFREQ_SET_REQ_STRU;

/*****************************************************************************
    : MTA_AT_REFCLKFREQ_QRY_CNF_STRU
  : AT^REFCLKFREQ

1.       : 20130722
         : l00198894
     : V9R1 AGPS
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
    VOS_UINT32                          ulFreq;                                 /* GPSHz */
    VOS_UINT32                          ulPrecision;                            /* GPSppb */
    MTA_AT_REFCLOCK_STATUS_ENUM_UINT16  enStatus;                               /*  */
    VOS_UINT8                           aucReserved1[2];                        /*  */
} MTA_AT_REFCLKFREQ_QRY_CNF_STRU;


/*****************************************************************************
     : AT_MTA_RFICSSIRD_REQ_STRU
   :
 1.       : 20151029
          : x00316382
      : Added for tool
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usChannelNo;                            /*  */
    VOS_UINT16                          usRficReg;
}AT_MTA_RFICSSIRD_REQ_STRU;

/*****************************************************************************
    : MTA_AT_RFICSSIRD_CNF_STRU
  : AT^SSIRD

1.       : 20151029
         : x00316382
     : Rfic SSI Rd
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulRegValue;                             /*  */
} MTA_AT_RFICSSIRD_CNF_STRU;

/*****************************************************************************
    : MTA_AT_REFCLKFREQ_IND_STRU
  : GPS

1.       : 20130722
         : l00198894
     : V9R1 AGPS
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulFreq;                                 /* GPSHz */
    VOS_UINT32                          ulPrecision;                            /* GPSppb */
    MTA_AT_REFCLOCK_STATUS_ENUM_UINT16  enStatus;                               /*  */
    VOS_UINT8                           aucReserved1[2];                        /*  */
} MTA_AT_REFCLKFREQ_IND_STRU;


/*****************************************************************************
    : MTA_AT_HANDLEDECT_SET_CNF_STRU
  : cnf

1.       : 20130808
         : m00217266
     : AP Sensor
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;                               /*  */
} MTA_AT_HANDLEDECT_SET_CNF_STRU;

/*****************************************************************************
    : MTA_AT_HANDLEDECT_QRY_CNF_STRU
  : cnf

1.       : 20130808
         : m00217266
     : AP Sensor
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usHandle;                               /*  */
    VOS_UINT16                          aucReserved1[1];
    MTA_AT_RESULT_ENUM_UINT32           enResult;                               /*  */
} MTA_AT_HANDLEDECT_QRY_CNF_STRU;

/*****************************************************************************
     : MTA_AT_PS_TRANSFER_IND_STRU
   : PS

  1.       : 20131021
           : l00198894
       : V9R1C50 SVLTE
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCause;                                /* PS */
    VOS_UINT8                           aucReserved1[3];                        /*  */
} MTA_AT_PS_TRANSFER_IND_STRU;

/*****************************************************************************
     : MTA_AT_RF_LCD_MIPICLK_IND_STRU
   : MIPICLK

  1.       : 20140304
           : j00174725
       : RF&LCD INTRUSION
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usMipiClk;                              /* MIPICLK */
    VOS_UINT8                           aucReserved1[2];                        /*  */
} MTA_AT_RF_LCD_MIPICLK_IND_STRU;

/*****************************************************************************
     : MTA_AT_RF_LCD_MIPICLK_CNF_STRU
   : MIPICLK

  1.       : 20140304
           : j00174725
       : RF&LCD INTRUSION
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usMipiClk;                              /* MIPICLK */
    VOS_UINT16                          usResult;
} MTA_AT_RF_LCD_MIPICLK_CNF_STRU;

/* Added by l00198894 for +ECID, 2013-12-09, begin */
/*******************************************************************************
     : AT_MTA_ECID_SET_REQ_STRU
   : ATMTA+ECID

  1.       : 20131210
           : l00198894
       : 
*******************************************************************************/
typedef struct
{
    VOS_UINT32                          ulVersion;                              /*  */
}AT_MTA_ECID_SET_REQ_STRU;

/*******************************************************************************
     : MTA_AT_ECID_SET_CNF_STRU
   : ATMTA+ECID

  1.       : 20131210
           : l00198894
       : 
*******************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
    VOS_UINT8                           aucCellInfoStr[4];                      /*  */
}MTA_AT_ECID_SET_CNF_STRU;
/* Added by l00198894 for +ECID, 2013-12-09, end */

/*****************************************************************************
     : AT_MTA_RRC_PROTECT_PS_REQ_STRU
   : ATPSPROTECTMODE

  1.       : 2014325
           : y00176023
       : PSPROTECTMODE

*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                  enPsProtectFlg;
    VOS_UINT8                           aucReserve[3];                          /*  */
}AT_MTA_RRC_PROTECT_PS_REQ_STRU;

/*****************************************************************************
     : MTA_AT_RRC_PROTECT_PS_CNF_STRU
   : ATPSPROTECTMODE

  1.       : 2014325
           : y00176023
       : PSPROTECTMODE

*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;                          /* AT */
}MTA_AT_RRC_PROTECT_PS_CNF_STRU;

/*****************************************************************************
     : MTA_AT_PHY_INIT_CNF_STRU
   : ATPHYINIT

  1.       : 2014325
           : y00176023
       : PHYINIT

*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucReserve[4];                          /*  */
}AT_MTA_PHY_INIT_REQ_STRU;

/*****************************************************************************
     : MTA_AT_PHY_INIT_CNF_STRU
   : AT

  1.       : 2014326
           : y00176023
       : PHYINIT
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;                          /* AT */
}MTA_AT_PHY_INIT_CNF_STRU;


/*****************************************************************************
     : AT_MTA_SET_DPDTTEST_FLAG_REQ_STRU
   : ATMTADPDT TEST FLAG

  1.       : 2014404
           : g00261581
       : 
*****************************************************************************/
typedef struct
{
    AT_MTA_CMD_RATMODE_ENUM_UINT8       enRatMode;
    VOS_UINT8                           ucFlag;
    VOS_UINT8                           aucReserved[2];
} AT_MTA_SET_DPDTTEST_FLAG_REQ_STRU;

/*****************************************************************************
     : AT_MTA_SET_DPDT_VALUE_REQ_STRU
   : ATMTADPDT

  1.       : 2014404
           : g00261581
       : 
*****************************************************************************/
typedef struct
{
    AT_MTA_CMD_RATMODE_ENUM_UINT8       enRatMode;
    VOS_UINT8                           aucReserved[3];
    VOS_UINT32                          ulDpdtValue;
} AT_MTA_SET_DPDT_VALUE_REQ_STRU;

/*****************************************************************************
     : AT_MTA_QRY_DPDT_VALUE_PARA_STRU
   : ATMTADPDT VAlUE

  1.       : 2014404
           : g00261581
       : 
*****************************************************************************/
typedef struct
{
    AT_MTA_CMD_RATMODE_ENUM_UINT8       enRatMode;
    VOS_UINT8                           aucReserved[3];
} AT_MTA_QRY_DPDT_VALUE_REQ_STRU;

/*****************************************************************************
     : MTA_AT_SET_DPDTTEST_FLAG_CNF_STRU
   : MTAATDPDTTEST Flag

  1.       : 2014404
           : g00261581
       : 
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
} MTA_AT_SET_DPDTTEST_FLAG_CNF_STRU;

/*****************************************************************************
     : MTA_AT_SET_DPDT_VALUE_CNF_STRU
   : MTAATDPDT Value

  1.       : 2014404
           : g00261581
       : 
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
} MTA_AT_SET_DPDT_VALUE_CNF_STRU;

/*****************************************************************************
     : MTA_AT_QRY_DPDT_VALUE_CNF_STRU
   : MTAATDPDT VAlUE

  1.       : 2014404
           : g00261581
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulDpdtValue;
    MTA_AT_RESULT_ENUM_UINT32           enResult;
} MTA_AT_QRY_DPDT_VALUE_CNF_STRU;

/*****************************************************************************
     : AT_MTA_SET_JAM_DETECT_REQ_STRU
   : ATMTAJamming Dectection Report

  1.       : 2014504
           : g00261581
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucFlag;
    VOS_UINT8                           ucMethod;
    VOS_UINT8                           ucThreshold;
    VOS_UINT8                           ucFreqNum;
} AT_MTA_SET_JAM_DETECT_REQ_STRU;

/*****************************************************************************
     : MTA_AT_SET_JAM_DETECT_CNF_STRU
   : MTAATJamming Dectection ReportCnf

  1.       : 2014504
           : g00261581
       : 
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
} MTA_AT_SET_JAM_DETECT_CNF_STRU;

/*****************************************************************************
     : MTA_AT_JAM_DETECT_IND_STRU
   : MTAATJamming Dectection ReportInd

  1.       : 2014504
           : g00261581
       : 
*****************************************************************************/
typedef struct
{
    MTA_AT_JAM_RESULT_ENUM_UINT32       enJamResult;
} MTA_AT_JAM_DETECT_IND_STRU;

/*****************************************************************************
     : AT_MTA_SET_FREQ_LOCK_REQ_STRU
   : ATMTA

  1.       : 2014611
           : g00261581
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEnableFlg;                            /* 1:0: */
    AT_MTA_FREQLOCK_RATMODE_ENUM_UINT8  enRatMode;
    VOS_UINT16                          usLockedFreq;
    AT_MTA_GSM_BAND_ENUM_UINT16         enBand;
    VOS_UINT8                           aucReserved[2];
} AT_MTA_SET_FREQ_LOCK_REQ_STRU;

/*****************************************************************************
     : MTA_AT_SET_FREQ_LOCK_CNF_STRU
   : MTAAT

  1.       : 2014611
           : g00261581
       : 
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
} MTA_AT_SET_FREQ_LOCK_CNF_STRU;

/*****************************************************************************
     : AT_MTA_SET_GSM_FREQLOCK_REQ_STRU
   : ATMTAG

  1.       : 20140805
           : j00174725
       : 
*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                  enableFlag;                             /* PS_TRUE:PS_FALSE: */
    VOS_UINT8                           aucReserved[3];                         /*  */
    VOS_UINT16                          usFreq;                                 /*  */
    AT_MTA_GSM_BAND_ENUM_UINT16         enBand;                                 /* GSM */
} AT_MTA_SET_GSM_FREQLOCK_REQ_STRU;

/*****************************************************************************
     : MTA_AT_SET_GSM_FREQLOCK_CNF_STRU
   : MTAATG

  1.       : 20140805
           : j00174725
       : 
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
} MTA_AT_SET_GSM_FREQLOCK_CNF_STRU;

#if (FEATURE_ON == FEATURE_PROBE_FREQLOCK)
/*****************************************************************************
     : AT_FREQLOCK_W_TYPE_ENUM
   : FREQLOCKW
1.      : 20141021
        : z00214637
    : 
*****************************************************************************/
enum AT_FREQLOCK_W_TYPE_ENUM
{
    AT_MTA_WCDMA_FREQLOCK_CMD_FREQ_ONLY         = 8,                            /* CWAS */
    AT_MTA_WCDMA_FREQLOCK_CMD_COMBINED          = 9,                            /* CWAS+ */
    AT_MTA_WCDMA_FREQLOCK_CMD_BUTT
};
typedef VOS_UINT8 AT_MTA_WCDMA_FREQLOCK_CMD_ENUM_UINT8;

/*****************************************************************************
     : AT_MTA_M2M_FREQLOCK_TYPE_ENUM
   : FREQLOCKW
1.      : 20141021
        : z00214637
    : 
*****************************************************************************/
enum AT_MTA_M2M_FREQLOCK_TYPE_ENUM
{
    AT_MTA_M2M_FREQLOCK_TYPE_ENUM_FREQ_ONLY     = 1,                            /* ONLY */
    AT_MTA_M2M_FREQLOCK_TYPE_ENUM_FREQ_COMBINED = 2,                            /* +//ID */
    AT_MTA_M2M_FREQLOCK_TYPE_ENUM_BUTT
};
typedef VOS_UINT8 AT_MTA_M2M_FREQLOCK_TYPE_ENUM_UINT8;

/*****************************************************************************
     : AT_MTA_M2M_GSM_FREQLOCK_PARA_STRU
   : ATMTAG

  1.       : 20141215
           : z00214637
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                  usFreq;                         /*  */
    AT_MTA_GSM_BAND_ENUM_UINT16                 enBand;                         /* GSM */
    VOS_UINT32                                  ulReserve;                      /* 8- */
} AT_MTA_M2M_GSM_FREQLOCK_PARA_STRU;

/*****************************************************************************
     : AT_MTA_M2M_WCDMA_FREQLOCK_PARA_STRU
   : ATMTAW

1.      : 20141021
        : z00214637
    : 
*****************************************************************************/
typedef struct
{
    AT_MTA_M2M_FREQLOCK_TYPE_ENUM_UINT8         ucFreqType;                     /*  */
    VOS_UINT8                                   aucReserved[3];                 /*  */
    VOS_UINT16                                  usFreq;                         /*  */
    VOS_UINT16                                  usPsc;                          /* WCDMA */
}AT_MTA_M2M_WCDMA_FREQLOCK_PARA_STRU;

/*****************************************************************************
     : AT_MTA_M2M_TDSCDMA_FREQLOCK_PARA_STRU
   : ATMTATD

1.      : 20141021
        : z00214637
    : 
*****************************************************************************/
typedef struct
{
    AT_MTA_M2M_FREQLOCK_TYPE_ENUM_UINT8         ucFreqType;                     /*  */
    VOS_UINT8                                   aucReserved[3];                 /*  */
    VOS_UINT16                                  usFreq;                         /*  */
    VOS_UINT16                                  usSc;                           /* TD-SCDMA */
}AT_MTA_M2M_TDSCDMA_FREQLOCK_PARA_STRU;

/*****************************************************************************
     : AT_MTA_M2M_LTE_FREQLOCK_PARA_STRU
   : ATMTAW

1.      : 20141021
        : z00214637
    : 
*****************************************************************************/
typedef struct
{
    AT_MTA_M2M_FREQLOCK_TYPE_ENUM_UINT8         ucFreqType;                     /*  */
    VOS_UINT8                                   aucReserved[3];                 /*  */
    VOS_UINT16                                  usFreq;                         /*  */
    VOS_UINT16                                  usPci;                          /* LTEID */
}AT_MTA_M2M_LTE_FREQLOCK_PARA_STRU;

/*****************************************************************************
     : AT_FREQLOCK_FLAG_TYPE_ENUM
   : FREQLOCKFLAG(/)
1.      : 20141021
        : z00214637
    : 
*****************************************************************************/
enum AT_FREQLOCK_FLAG_TYPE_ENUM
{
    AT_MTA_M2M_FREQLOCK_MODE_GSM            = 1,                                /* GSM */
    AT_MTA_M2M_FREQLOCK_MODE_WCDMA          = 2,                                /* WCDMA */
    AT_MTA_M2M_FREQLOCK_MODE_TDSCDMA        = 3,                                /* TD-SCDMA */
    AT_MTA_M2M_FREQLOCK_MODE_LTE            = 4,                                /* LTE */
    AT_MTA_M2M_FREQLOCK_MODE_BUTT
};
typedef VOS_UINT8 AT_MTA_M2M_FREQLOCK_MODE_ENUM_UINT8;

/*****************************************************************************
     : AT_MTA_M2M_FREQLOCK_FLAG_ENUM_UINT8
   : FREQLOCKFLAG(/)
1.      : 20141021
        : z00214637
    : 
*****************************************************************************/
enum AT_MTA_M2M_FREQLOCK_FLAG_TYPE_ENUM
{
    AT_MTA_M2M_FREQLOCK_FLAG_TYPE_OFF       = 0,                                /*  */
    AT_MTA_M2M_FREQLOCK_FLAG_TYPE_ON        = 1,                                /*  */
    AT_MTA_M2M_FREQLOCK_FLAG_TYPE_BUTT
};
typedef VOS_UINT8 AT_MTA_M2M_FREQLOCK_FLAG_ENUM_UINT8;

/*****************************************************************************
     : AT_MTA_SET_M2M_FREQLOCK_REQ_STRU
   : ATMTA

  1.       : 20141020
           : z00214637
       : 
*****************************************************************************/
typedef struct
{
    AT_MTA_M2M_FREQLOCK_FLAG_ENUM_UINT8         enableFlag;                                 /*  */
    AT_MTA_M2M_FREQLOCK_MODE_ENUM_UINT8         ucMode;                                     /*  */
    VOS_UINT8                                   aucReserved[6];                             /*  */
    AT_MTA_M2M_GSM_FREQLOCK_PARA_STRU           stGFreqPara;                                /* G */
    AT_MTA_M2M_WCDMA_FREQLOCK_PARA_STRU         stWFreqPara;                                /* W */
    AT_MTA_M2M_TDSCDMA_FREQLOCK_PARA_STRU       stTDFreqPara;                               /* TD */
    AT_MTA_M2M_LTE_FREQLOCK_PARA_STRU           stLFreqPara;                                /* L */
} AT_MTA_SET_M2M_FREQLOCK_REQ_STRU;

/*****************************************************************************
     : MTA_AT_SET_M2M_FREQLOCK_CNF_STRU
   : MTAAT

  1.       : 20141020
           : z00214637
       : 
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           ulResult;
} MTA_AT_SET_M2M_FREQLOCK_CNF_STRU;

/*****************************************************************************
     : MTA_AT_FREQLOCK_QRY_CNF_STRU
   : MTAATFREQLOCK

  1.       : 20141020
           : z00214637
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                   ucFreqState[MTA_FREQLOCK_MAX_MODE];     /* GUTL */
    AT_MTA_M2M_GSM_FREQLOCK_PARA_STRU           stGFreqLockInfo;                        /* GSM */
    AT_MTA_M2M_WCDMA_FREQLOCK_PARA_STRU         stWFreqLockInfo;                        /* WCDMA */
    AT_MTA_M2M_TDSCDMA_FREQLOCK_PARA_STRU       stTFreqLockInfo;                        /* TD-SCDMA */
    AT_MTA_M2M_LTE_FREQLOCK_PARA_STRU           stLFreqLockInfo;                        /* LTE */
} MTA_AT_QRY_M2M_FREQLOCK_CNF_STRU;
#endif


/*****************************************************************************
     : MTA_AT_XPASS_INFO_IND_STRU
   : MTAXPASS

  1.       : 20141225
           : m00217266
       : 
*****************************************************************************/
typedef struct
{
    MTA_AT_GPHY_XPASS_MODE_ENUM_UINT16            enGphyXpassMode;
    VOS_UINT16                                    usResev1;
    MTA_AT_WPHY_HIGHWAY_MODE_ENUM_UINT16          enWphyXpassMode;
    VOS_UINT16                                    usResev2;
} MTA_AT_XPASS_INFO_IND_STRU;
/*****************************************************************************
     : AT_MTA_SET_FEMCTRL_REQ_STRU
   : ATMTAgpiomipi

  1.       : 20141211
           : m00217266
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT32      ulCtrlType;
    VOS_UINT32      ulPara1;
    VOS_UINT32      ulPara2;
    VOS_UINT32      ulPara3;
} AT_MTA_SET_FEMCTRL_REQ_STRU;

/*****************************************************************************
     : MTA_AT_SET_FEMCTRL_CNF_STRU
   : MTAATgpiomipi

  1.       : 20141211
           : m00217266
       : 
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
} MTA_AT_SET_FEMCTRL_CNF_STRU;

/*****************************************************************************
     : AT_MTA_NVWRSECCTRL_SET_REQ_STRU
   : ATMTANVWR

  1.       : 20150404
           : l00198894
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucSecType;                              /*  */
    VOS_UINT8                           ucSecStrFlg;                            /*  */
    VOS_UINT8                           aucReserved[2];
    VOS_UINT8                           aucSecString[AT_RSA_CIPHERTEXT_LEN];    /*  */
} AT_MTA_NVWRSECCTRL_SET_REQ_STRU;

/*******************************************************************************
     : AT_MTA_SET_FR_REQ_STRU
   : ATMTAFR
 1.       : 20150601
          : wx270776
      : FR
*******************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                          enActFrFlag;                    /* FR0:  1: */
    VOS_UINT8                                   aucRsv[3];                      /*  */
}AT_MTA_SET_FR_REQ_STRU;

/*******************************************************************************
     : MTA_AT_SET_FR_CNF_STRU
   : MTAATFR
 1.       : 20150601
          : wx270776
      : FR
*******************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32                   enRslt;                         /* FR */
}MTA_AT_SET_FR_CNF_STRU;

/*******************************************************************************
     : MTA_AT_TIME_STRU
   : 
 1.       : 20160525
          : wx270776
      : SIB16
*******************************************************************************/
typedef struct
{
    VOS_UINT16                                    usYear;
    VOS_UINT8                                     ucMonth;
    VOS_UINT8                                     ucDay;
    VOS_UINT8                                     ucHour;
    VOS_UINT8                                     ucMinute;
    VOS_UINT8                                     ucSecond;
    VOS_UINT8                                     ucRsv;
}MTA_AT_TIME_STRU;

/*******************************************************************************
     : MTA_AT_SIB16_TIME_UPDATE_STRU
   : LRRCMTA
 1.       : 20160525
          : wx270776
      : SIB16
*******************************************************************************/
typedef struct
{
    MTA_AT_TIME_TYPE_ENUM_UINT8                   enTimeType;
    MTA_AT_DAY_LIGHT_SAVING_IND_ENUM_UINT8        enDayLightSavingInd;
    VOS_UINT8                                     aucRsv[2];
    MTA_AT_TIME_STRU                              stLocalTime;
    MTA_AT_TIME_STRU                              stGpsTime;
}MTA_AT_SIB16_TIME_UPDATE_STRU;

/*****************************************************************************
     : MTA_AT_ACCESS_STRATUM_REL_ENUM
   : AT

 1.       : 20161117
          : wx270776
      : 
*****************************************************************************/
enum MTA_AT_ACCESS_STRATUM_REL_ENUM
{
    MTA_AT_ACCESS_STRATUM_REL8                  = 0,
    MTA_AT_ACCESS_STRATUM_REL9                  = 1,
    MTA_AT_ACCESS_STRATUM_REL10                 = 2,
    MTA_AT_ACCESS_STRATUM_REL11                 = 3,
    MTA_AT_ACCESS_STRATUM_REL12                 = 4,
    MTA_AT_ACCESS_STRATUM_REL13                 = 5,
    MTA_AT_ACCESS_STRATUM_REL_SPARE2            = 6,
    MTA_AT_ACCESS_STRATUM_REL_SPARE1            = 7
};
typedef VOS_UINT8 MTA_AT_ACCESS_STRATUM_REL_ENUM_UINT8;

/*****************************************************************************
     : MTA_AT_ACCESS_STRATUM_REL_IND_STRU
   :

 1.       : 20161117
          : wx270776
      : 
*****************************************************************************/
typedef struct
{
    MTA_AT_ACCESS_STRATUM_REL_ENUM_UINT8        enAccessStratumRel; /* AT */
    VOS_UINT8                                   aucRsv[3];
} MTA_AT_ACCESS_STRATUM_REL_IND_STRU;

/*****************************************************************************
     : AT_MTA_MBMS_SERVICE_OPTION_SET_REQ_STRU
   : ATMTAMBMS

  1.       : 2015522
           : w00316404
       : 
*****************************************************************************/
typedef struct
{
    AT_MTA_CFG_ENUM_UINT8               enCfg;                                  /* 0:1: */
    VOS_UINT8                           aucReserved[3];                         /*  */
} AT_MTA_MBMS_SERVICE_OPTION_SET_REQ_STRU;


/*****************************************************************************
     : AT_MTA_PLMN_ID_STRU
   : PLMN ID

  1.       : 2015522
           : w00316404
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulMcc;                                  /* MCC, 3 bytes */
    VOS_UINT32                          ulMnc;                                  /* MNC, 2 or 3 bytes */
} AT_MTA_PLMN_ID_STRU;

/*****************************************************************************
     : AT_MTA_MBMS_TMGI_STRU
   : TMGI

  1.       : 2015522
           : w00316404
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulMbmsSerId;                            /* Service ID */
    AT_MTA_PLMN_ID_STRU                 stPlmnId;                               /* PLMN ID */
} AT_MTA_MBMS_TMGI_STRU;

/*****************************************************************************
     : AT_MTA_MBMS_SERVICE_STATE_SET_REQ_STRU
   : ATMTA MBMS

  1.       : 2015522
           : w00316404
       : 
*****************************************************************************/
typedef struct
{
    AT_MTA_MBMS_SERVICE_STATE_SET_ENUM_UINT8    enStateSet;                     /*  */
    VOS_UINT8                                   aucReserved[3];                 /*  */
    VOS_UINT32                                  ulAreaId;                       /* Area ID */
    AT_MTA_MBMS_TMGI_STRU                       stTMGI;                         /* TMGI */
} AT_MTA_MBMS_SERVICE_STATE_SET_REQ_STRU;

/*****************************************************************************
     : AT_MTA_MBMS_PREFERENCE_SET_REQ_STRU
   : ATMTAMBMS

  1.       : 2015522
           : w00316404
       : 
*****************************************************************************/
typedef struct
{
    AT_MTA_MBMS_CAST_MODE_ENUM_UINT8    enCastMode;                             /* 0:,1: */
    VOS_UINT8                           aucReserved[3];                         /*  */
} AT_MTA_MBMS_PREFERENCE_SET_REQ_STRU;

/*****************************************************************************
     : MTA_AT_MBMS_SIB16_NETWORK_TIME_QRY_CNF_STRU
   : MTAATSIB16

  1.       : 2015522
           : w00316404
       : 
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
    VOS_UINT32                          aulUTC[2];                              /* (0..549755813887) */
} MTA_AT_MBMS_SIB16_NETWORK_TIME_QRY_CNF_STRU;

/*****************************************************************************
     : MTA_AT_MBMS_BSSI_SIGNAL_LEVEL_QRY_CNF_STRU
   : MTAATBSSI

  1.       : 2015522
           : w00316404
       : 
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
    VOS_UINT8                           ucBSSILevel;                            /* BSSI,0xFF:BSSI */
    VOS_UINT8                           aucReserved[3];                         /*  */
} MTA_AT_MBMS_BSSI_SIGNAL_LEVEL_QRY_CNF_STRU;

/*****************************************************************************
     : MTA_AT_MBMS_NETWORK_INFO_QRY_CNF_STRU
   : MTAAT

  1.       : 2015522
           : w00316404
       : 
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
    VOS_UINT32                          ulCellId;                               /* ID */
} MTA_AT_MBMS_NETWORK_INFO_QRY_CNF_STRU;

/*****************************************************************************
     : MTA_AT_EMBMS_STATUS_QRY_CNF_STRU
   : MTAATEMBMS

  1.       : 2015522
           : w00316404
       : 
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32                   enResult;
    MTA_AT_EMBMS_FUNTIONALITY_STATUS_ENUM_UINT8 enStatus;                       /*  */
    VOS_UINT8                                   aucReserved[3];                 /*  */
} MTA_AT_EMBMS_STATUS_QRY_CNF_STRU;

/*****************************************************************************
     : AT_MTA_MBMS_UNSOLICITED_CFG_SET_REQ_STRU
   : ATMTAMBMS

  1.       : 2015522
           : w00316404
       : 
*****************************************************************************/
typedef struct
{
    AT_MTA_CFG_ENUM_UINT8                       enCfg;                          /* 0:,1: */
    VOS_UINT8                                   aucReserved[3];                 /*  */
} AT_MTA_MBMS_UNSOLICITED_CFG_SET_REQ_STRU;

/*****************************************************************************
     : MTA_AT_MBMS_SERVICE_EVENT_IND_STRU
   : MTAATMBMS

  1.       : 2015522
           : w00316404
       : 
*****************************************************************************/
typedef struct
{
    MTA_AT_MBMS_SERVICE_EVENT_ENUM_UINT8    enEvent;                            /*  */
    VOS_UINT8                               aucReserved[3];                     /*  */
} MTA_AT_MBMS_SERVICE_EVENT_IND_STRU;

/*****************************************************************************
     : AT_MTA_LOW_POWER_CONSUMPTION_SET_REQ_STRU
   : ATMTA

  1.       : 2015522
           : w00316404
       : 
*****************************************************************************/
typedef struct
{
    AT_MTA_LTE_LOW_POWER_ENUM_UINT8         enLteLowPowerFlg;                   /* 0: Normal;1: Low Power Consumption */
    VOS_UINT8                               aucReserved[3];                     /*  */
} AT_MTA_LOW_POWER_CONSUMPTION_SET_REQ_STRU;

/*****************************************************************************
     : AT_MTA_MBMS_INTERESTLIST_SET_REQ_STRU
   : ATMTAInterest

  1.       : 2015522
           : w00316404
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          aulFreqList[AT_MTA_INTEREST_FREQ_MAX_NUM];  /*  */
    AT_MTA_MBMS_PRIORITY_ENUM_UINT8     enMbmsPriority;                             /* VOS_FALSE: ;VOS_TRUE: MBMS */
    VOS_UINT8                           aucReserved[3];                             /*  */
} AT_MTA_MBMS_INTERESTLIST_SET_REQ_STRU;

/*****************************************************************************
     : MTA_AT_MBMS_AVL_SERVICE_STRU
   : MBMS

  1.       : 2015522
           : w00316404
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpSessionId  : 1;
    VOS_UINT32                          bitSpare        : 31;
    VOS_UINT32                          ulAreaId;                               /* Area ID */
    AT_MTA_MBMS_TMGI_STRU               stTMGI;                                 /* TMGI */
    VOS_UINT32                          ulSessionId;                            /* Session ID */
} MTA_AT_MBMS_AVL_SERVICE_STRU;

/*****************************************************************************
     : MTA_AT_MBMS_AVL_SERVICE_LIST_QRY_CNF_STRU
   : MTAAT

  1.       : 2015522
           : w00316404
       : 
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
    VOS_UINT32                          ulAvlServiceNum;                                    /* ,0: */
    MTA_AT_MBMS_AVL_SERVICE_STRU        astAvlServices[AT_MTA_MBMS_AVL_SERVICE_MAX_NUM];    /*  */
} MTA_AT_MBMS_AVL_SERVICE_LIST_QRY_CNF_STRU;

/*****************************************************************************
     : MTA_LRRC_COEX_PARA_STRU
   : LTE&WIFI

  1.       : 2015522
           : w00316404
       : 
*****************************************************************************/
typedef struct
{
    AT_MTA_COEX_BW_TYPE_ENUM_UINT16             enCoexBWType;
    AT_MTA_COEX_CFG_ENUM_UINT16                 enCfg;
    VOS_UINT16                                  usTxBegin;
    VOS_UINT16                                  usTxEnd;
    VOS_INT16                                   sTxPower;
    VOS_UINT16                                  usRxBegin;
    VOS_UINT16                                  usRxEnd;
    VOS_UINT8                                   aucReserved[2];                 /*  */
} AT_MTA_COEX_PARA_STRU;

/*****************************************************************************
     : AT_MTA_LTE_WIFI_COEX_SET_REQ_STRU
   : ATMTALTE&WIFI

  1.       : 2015522
           : w00316404
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usCoexParaNum;
    VOS_UINT16                          usCoexParaSize;
    AT_MTA_COEX_PARA_STRU               astCoexPara[AT_MTA_ISMCOEX_BANDWIDTH_NUM];
} AT_MTA_LTE_WIFI_COEX_SET_REQ_STRU;

/*****************************************************************************
     : MTA_AT_LTE_WIFI_COEX_QRY_CNF_STRU
   : MTAATLTE&WIFI

  1.       : 2015522
           : w00316404
       : 
*****************************************************************************/
typedef struct
{
    AT_MTA_COEX_PARA_STRU               astCoexPara[AT_MTA_ISMCOEX_BANDWIDTH_NUM];
} MTA_AT_LTE_WIFI_COEX_QRY_CNF_STRU;

/*****************************************************************************
     : AT_MTA_MEID_SET_REQ_STRU
   : AT^MEID

       :
  1.       : 20150723
           : z00316370
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucMeid[AT_MTA_MEID_DATA_LEN];
    VOS_UINT8                           aucRsv[1];
}AT_MTA_MEID_SET_REQ_STRU;

/*****************************************************************************
     : MTA_AT_MEID_QRY_CNF_STRU
   : AT^MEID

       :
  1.       : 20151218
           : z00316370
       : 
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;                               /* */
    VOS_UINT8                           aucEFRUIMID[MTA_AT_EFRUIMID_OCTET_LEN_EIGHT];
}MTA_AT_MEID_QRY_CNF_STRU;




/*****************************************************************************
     : MTA_AT_TRANSMODE_QRY_CNF_STRU
   : MTAAT

  1.       : 20150730
           : lwx277467
       : 
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;                               /* */
    VOS_UINT8                           ucTransMode;                            /* */
    VOS_UINT8                           aucReserved[3];                         /**/
} MTA_AT_TRANSMODE_QRY_CNF_STRU;

/*****************************************************************************
     : AT_MTA_SET_UE_CENTER_REQ_STRU
   : ATMTAUE Mode

  1.       : 20150907
           : lwx277467
       : 
*****************************************************************************/
typedef struct
{
    AT_MTA_UE_CENTER_TYPE_ENUM_UINT32   enUeCenter;                             /*UE*/
} AT_MTA_SET_UE_CENTER_REQ_STRU;

/*****************************************************************************
     : MTA_AT_SET_UE_CENTER_CNF_STRU
   : MTAATUE Mode

  1.       : 20150907
           : lwx277467
       : 
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;                               /* */
} MTA_AT_SET_UE_CENTER_CNF_STRU;

/*****************************************************************************
     : MTA_AT_QRY_UE_CENTER_CNF_STRU
   : MTAATUE

  1.       : 20150907
           : lwx277467
       : 
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;                               /* */
    AT_MTA_UE_CENTER_TYPE_ENUM_UINT32   enUeCenter;                             /*UE*/
} MTA_AT_QRY_UE_CENTER_CNF_STRU;


/*****************************************************************************
     : MTA_AT_NETMON_GSM_SCELL_INFO_STRU
   : MTAAT network monitor

  1.       : 20151019
           : zwx247453
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpTa     :1;
    VOS_UINT32                          bitOpSpare  :31;
    GRR_MTA_NETMON_SCELL_INFO_STRU      stSCellInfo;
    VOS_UINT16                          usTa;
    VOS_UINT8                           aucReserved[2];
}MTA_AT_NETMON_GSM_SCELL_INFO_STRU;

/*****************************************************************************
     : MTA_AT_NETMON_SCELLL_INFO_UN
   : MTA 

  1.       : 20151019
           : zwx247453
       : 
*****************************************************************************/
typedef union
{
    MTA_AT_NETMON_GSM_SCELL_INFO_STRU       stGsmSCellInfo;    /* GSM */
    RRC_MTA_NETMON_UTRAN_SCELL_INFO_STRU    stUtranSCellInfo;  /* WCDMA */
    MTA_NETMON_EUTRAN_SCELL_INFO_STRU       stLteSCellInfo;    /* LTE*/
}MTA_AT_NETMON_SCELL_INFO_UN;

/*****************************************************************************
     : MTA_AT_NETMON_GSM_SCELL_INFO_STRU
   : MTAAT network monitor

  1.       : 20151019
           : zwx247453
       : 
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32                   enResult;               /*  */
    MTA_NETMON_CELL_TYPE_ENUM_UINT32            enCellType;             /* 0:1: */
    RRC_MTA_NETMON_NCELL_INFO_STRU              stNCellInfo;            /**/
    MTA_AT_NETMON_CELL_INFO_RAT_ENUM_UINT32     enRatType;              /*  */
    MTA_AT_NETMON_SCELL_INFO_UN                 unSCellInfo;
} MTA_AT_NETMON_CELL_INFO_STRU;



/*****************************************************************************
     : AT_MTA_QRY_AFC_CLK_FREQ_XOCOEF_REQ_STRU
   :

  1.       : 20151225
           : C00299064
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulReserveValue;
} AT_MTA_QRY_AFC_CLK_FREQ_XOCOEF_REQ_STRU;

/*****************************************************************************
     : MTA_AT_QRY_AFC_CLK_FREQ_XOCOEF_CNF_STRU
   :

  1.       : 20151225
           : C00299064
       : 
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;

    AT_MTA_AFC_CLK_STATUS_ENUM_UINT32   enStatus;
    VOS_INT32                           lDeviation;                                 /*  */

    /*  */
    VOS_INT16                           sCoeffStartTemp;
    VOS_INT16                           sCoeffEndTemp;

    /*  */
    VOS_UINT32                          aulCoeffMantissa[AT_MTA_GPS_XO_COEF_NUM];  /* a0,a1,a2,a3 */
    VOS_UINT16                          ausCoeffExponent[AT_MTA_GPS_XO_COEF_NUM];  /* a0,a1,a2,a3 */

} MTA_AT_QRY_AFC_CLK_FREQ_XOCOEF_CNF_STRU;


/*****************************************************************************
     : AT_MTA_EVDO_SYS_EVENT_SET_REQ_STRU
   : AT^DOSYSEVENT

       :
  1.       : 20151230
           : z00316370
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulDoSysEvent;
}AT_MTA_EVDO_SYS_EVENT_SET_REQ_STRU;

/*****************************************************************************
     : AT_MTA_EVDO_SIG_MASK_SET_REQ_STRU
   : AT^DOSIGMASK

       :
  1.       : 20151230
           : z00316370
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulDoSigMask;
}AT_MTA_EVDO_SIG_MASK_SET_REQ_STRU;

/*****************************************************************************
     : MTA_AT_EVDO_REVA_RLINK_INFO_IND_STRU
   : MTAATEVDO REVA RLING

  1.       : 2014504
           : g00261581
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulParaLen;
    VOS_UINT8                           aucContent[4];
} MTA_AT_EVDO_REVA_RLINK_INFO_IND_STRU;

/*****************************************************************************
     : MTA_AT_EVDO_SIG_EXEVENT_IND_STRU
   : MTAATEVDO SIG EX EVENT

  1.       : 2014504
           : g00261581
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulParaLen;
    VOS_UINT8                           aucContent[4];
} MTA_AT_EVDO_SIG_EXEVENT_IND_STRU;

/*****************************************************************************
     : AT_MTA_SET_XCPOSR_REQ_STRU
   :

  1.       : 20160308
           : h00360002
       : 
*****************************************************************************/
typedef struct
{
    AT_MTA_XCPOSR_CFG_ENUM_UNIT8        enXcposrEnableCfg;                            /* GPS */
    VOS_UINT8                           aucReserved[3];
} AT_MTA_SET_XCPOSR_REQ_STRU;

/*****************************************************************************
     : MTA_AT_QRY_XCPOSR_CNF_STRU
   :

  1.       : 20160308
           : h00360002
       : 
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;                               /*  */
    AT_MTA_XCPOSR_CFG_ENUM_UNIT8        enXcposrEnableCfg;
    VOS_UINT8                           aucReserved[3];
} MTA_AT_QRY_XCPOSR_CNF_STRU;

/*****************************************************************************
     : AT_MTA_SET_XCPOSRRPT_REQ_STRU
   :

  1.       : 20160309
           : h00360002
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucXcposrRptFlg;                         /* +XCPOSRRPT */
    VOS_UINT8                           aucReserved[3];
} AT_MTA_SET_XCPOSRRPT_REQ_STRU;

/*****************************************************************************
     : MTA_AT_QRY_XCPOSR_CNF_STRU
   :

  1.       : 20160308
           : h00360002
       : 
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;                               /*  */
    VOS_UINT8                           ucXcposrRptFlg;
    VOS_UINT8                           aucReserved[3];
} MTA_AT_QRY_XCPOSRRPT_CNF_STRU;

/*******************************************************************************
     : AT_MTA_SET_SENSOR_REQ_STRU
   :

  1.       : 20160322
           : z00347560
       : 
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucSensorStat;                              /* Sensor Hub  */
    VOS_UINT8                           aucReserved[3];
}AT_MTA_SET_SENSOR_REQ_STRU;
/*****************************************************************************
     : MTA_AT_SET_SENSOR_CNF_STRU
   : MTAATSensor Hub

  1.       : 20160322
           : z00347560
       : 
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
} MTA_AT_SET_SENSOR_CNF_STRU;

/*******************************************************************************
     : AT_MTA_SET_SCREEN_REQ_STRU
   :

  1.       : 20160322
           : z00347560
       : 
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucScreenStat;                              /* Screen  */
    VOS_UINT8                           aucReserved[3];
}AT_MTA_SET_SCREEN_REQ_STRU;
/*****************************************************************************
     : MTA_AT_SET_SCREEN_CNF_STRU
   : MTAAT

  1.       : 20160322
           : z00347560
       : 
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
} MTA_AT_SET_SCREEN_CNF_STRU;

/*****************************************************************************
     : AT_MTA_SET_RXTESTMODE_STRU
   : ATMTA

  1.       : 20160707
           : l00373346
       : 
*****************************************************************************/
typedef struct
{
    AT_MTA_CFG_ENUM_UINT8               enCfg;                                  /* 0:,1: */
    VOS_UINT8                           aucReserved[3];                         /*  */
} AT_MTA_SET_RXTESTMODE_REQ_STRU;

/*******************************************************************************
     : MTA_AT_SET_RXTESTMODE_CNF_STRU
   : AT
 1.       : 20160707
          : l00373346
      : 
*******************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;                               /*  */
}MTA_AT_SET_RXTESTMODE_CNF_STRU;
/*******************************************************************************
     : MTA_AT_AFC_CLK_UNLOCK_IND_STRU
   : MTAATAFC

 1.       : 20160705
          : wx270776
      : 
*******************************************************************************/
typedef struct
{
    VOS_UINT16                          usCause;
    VOS_UINT16                          usReserved;        /*  */
}MTA_AT_AFC_CLK_UNLOCK_IND_STRU;

/*******************************************************************************
     : MTA_AT_DEVICE_FREQ_STRU
   : MTAAT

 1.       : 20160727
          : s00370485
      : 
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucGroupID;                             /*  */
    VOS_UINT8                           ucDeviceID;                            /*  */
    VOS_UINT8                           ucCaseID;                              /*  */
    VOS_UINT8                           ucMode;                                /*  */
} MTA_AT_DEVICE_FREQ_STRU;

/*******************************************************************************
     : MTA_AT_BEST_FREQ_CASE_IND_STRU
   : ID_MTA_AT_BEST_CASE_IND

 1.       : 20160727
          : s00370485
      : 
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucRptDeviceNum;                                    /*  */
    VOS_UINT8                           aucReserved[3];                                    /*  */
    MTA_AT_DEVICE_FREQ_STRU             astDeviceFreqList[MTC_MTA_MAX_BESTFREQ_GROUPNUM];   /* 8 */
} MTA_AT_BEST_FREQ_CASE_IND_STRU;

/*****************************************************************************
     : MTA_AT_BESTFREQ_QRY_CNF_STRU
   : BESTFRQ

  1.       : 20160727
           : q00380176
       : dynamic_fm_intrusion_ctrl 
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;                               /*  */
    VOS_UINT8                           ucActiveDeviceNum;
    VOS_UINT8                           aucReserved[3];
    MTA_AT_DEVICE_FREQ_STRU             astDeviceInfoList[MTC_MTA_MAX_BESTFREQ_GROUPNUM];
}MTA_AT_BESTFREQ_QRY_CNF_STRU;

/*****************************************************************************
     : AT_MTA_SLAVE_SET_REQ_STRU
   : ATMTASLAVE 

  1.       : 20150404
           : l00198894
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT32                           ucRatType;                              /*0-GSM 1-WCDMA*/
} AT_MTA_SLAVE_SET_REQ_STRU;
/*****************************************************************************
     : MTA_AT_RFIC_DIE_ID_REQ_CNF_STRU
   : MATATRFIC DIE ID

  1.       : 20160827
           : xwx377961
       : 
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
    VOS_UINT16                          usRfic0DieIdValid;                       /*1- 0-*/
    VOS_UINT16                          usRfic1DieIdValid;
    VOS_UINT16                          ausRfic0DieId[MTA_RCM_MAX_DIE_ID_LEN];
    VOS_UINT16                          ausRfic1DieId[MTA_RCM_MAX_DIE_ID_LEN];
} MTA_AT_RFIC_DIE_ID_REQ_CNF_STRU;

/*****************************************************************************
     : AT_MTA_PHY_COM_CFG_SET_REQ_STRU
   : ATMTAPHY

  1.       : 20170124
           : xwx377961
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usCmdType;                              /*  */
    VOS_UINT16                          usRatBitmap;                            /* ratbitmap */                           
    VOS_UINT32                          ulPara1;                                /* 1 */
    VOS_UINT32                          ulPara2;                                /* 2 */
    VOS_UINT32                          ulPara3;                                /* 3 */
} AT_MTA_PHY_COM_CFG_SET_REQ_STRU;

/*****************************************************************************
     : MTA_AT_PHY_COM_CFG_SET_CNF_STRU
   : MATATPHY

  1.       : 20170124
           : xwx377961
       : 
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
} MTA_AT_PHY_COM_CFG_SET_CNF_STRU;

/* Add by c00380008 for WIFI  2016-08-22, begin */
/*****************************************************************************
     : AT_MTA_CRRCONN_SET_REQ_STRU
   : ATMTACRRCONN 

  1.       : 20160822
           : c00380008
       : 
*****************************************************************************/
typedef struct
{
    AT_MTA_CFG_ENUM_UINT8               enEnable;                               /* 01 */
    VOS_UINT8                           aucReserved[3];                         /*  */
}AT_MTA_SET_CRRCONN_REQ_STRU;

/*******************************************************************************
     : MTA_AT_CRRCONN_STATUS_IND_STRU
   : ID_MTA_AT_CRRCONN_STATUS_IND

 1.       : 20160822
          : c00380008
      : 
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucStatus0;
    VOS_UINT8                           ucStatus1;
    VOS_UINT8                           ucStatus2;
    VOS_UINT8                           ucReserved;                             /*  */
}MTA_AT_CRRCONN_STATUS_IND_STRU;

/*****************************************************************************
     : MTA_AT_SET_CRRCONN_CNF_STRU
   : MTAAT

  1.       : 20160822
           : c00380008
       : 
*****************************************************************************/
typedef MTA_AT_RESULT_CNF_STRU MTA_AT_SET_CRRCONN_CNF_STRU;

/*****************************************************************************
     : MTA_AT_SET_CRRCONN_CNF_STRU
   : MTAAT

  1.       : 20160822
           : c00380008
       : 
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
    AT_MTA_CFG_ENUM_UINT8               enEnable;
    VOS_UINT8                           ucStatus0;
    VOS_UINT8                           ucStatus1;
    VOS_UINT8                           ucStatus2;
} MTA_AT_QRY_CRRCONN_CNF_STRU;

/*****************************************************************************
     : AT_MTA_SET_VTRLQUALRPT_REQ_STRU
   : ATMTAVTRLQUALRPT 

  1.       : 20160830
           : c00380008
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulEnable;                               /* 01 */
    VOS_UINT32                          ulThreshold;                            /* LPDCP */
}AT_MTA_SET_VTRLQUALRPT_REQ_STRU;

/*****************************************************************************
     : MTA_AT_RL_QUALITY_INFO_IND_STRU
   : LTE600ms,ulRlQualityRptFlg10bitVideoDiagPresent TRUE
NASLTERLQUALINFO

 1.       : 20160830
          : c00380008
      : 
*****************************************************************************/
typedef struct
{
    VOS_INT16                           sRsrp;                                  /*RSRP*/
    VOS_INT16                           sRsrq;                                  /*RSRQ*/
    VOS_INT16                           sRssi;                                  /*RSSI*/
    VOS_UINT16                          usBler;                                 /**/
} MTA_AT_RL_QUALITY_INFO_IND_STRU;

/*****************************************************************************
     : MTA_AT_VIDEO_DIAG_INFO_RPT_STRU
   : VoLTE,600ms.

 1.      : 20160830
         : c00380008
     : 
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulCurrBuffTime;                         /**/
    VOS_UINT32                          ulCurrBuffPktNum;                       /**/
    VOS_UINT32                          ulMacUlThrput;                          /*MAC,:bytes/s*/
    VOS_UINT32                          ulMaxBuffTime;                          /*ms*/
}MTA_AT_VIDEO_DIAG_INFO_RPT_STRU;

/*****************************************************************************
     : MTA_AT_SET_VTRLQUALRPT_CNF_STRU
   : MTAAT

  1.       : 20160830
           : c00380008
       : 
*****************************************************************************/
typedef MTA_AT_RESULT_CNF_STRU MTA_AT_SET_VTRLQUALRPT_CNF_STRU;
/* Add by c00380008 for WIFI  2016-08-22, end */

/*****************************************************************************
     : MTA_AT_RFIC_DIE_ID_REQ_CNF_STRU
   : MATATRFIC DIE ID

  1.       : 20160827
           : xwx377961
       : 
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
    VOS_UINT8                           aucDieSN[MTA_PMU_MAX_DIE_SN_LEN];
} MTA_AT_PMU_DIE_SN_REQ_CNF_STRU;

/*****************************************************************************
     : AT_MTA_MIPI_WREX_REQ_STRU
   : ATMTAMIPI

  1.       : 20170116
           : xwx377961
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulExtendFlag;
    VOS_UINT32                          ulMipiId;
    VOS_UINT32                          ulSlaveId;
    VOS_UINT32                          ulRegAddr;
    VOS_UINT32                          ulValue;
    VOS_UINT32                          ulByteCnt;
} AT_MTA_MIPI_WREX_REQ_STRU;

/*****************************************************************************
     : AT_MTA_MIPI_RDEX_REQ_STRU
   : ATMTAMIPI

  1.       : 20170116
           : xwx377961
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulExtendFlag;
    VOS_UINT32                          ulMipiId;
    VOS_UINT32                          ulSlaveId;
    VOS_UINT32                          ulRegAddr;
    VOS_UINT32                          ulByteCnt;
} AT_MTA_MIPI_RDEX_REQ_STRU;

/*****************************************************************************
     : MTA_AT_MIPI_WREX_REQ_STRU
   : MATATMIPI

  1.       : 20170116
           : xwx377961
       : 
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
} MTA_AT_MIPI_WREX_CNF_STRU;

/*****************************************************************************
     : MTA_AT_MIPI_RDEX_REQ_STRU
   : MATATMIPI

  1.       : 20170116
           : xwx377961
       : 
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
    VOS_UINT32                          ulValue;
} MTA_AT_MIPI_RDEX_CNF_STRU;

/*****************************************************************************
     : AT_MTA_MODEM_CAP_UPDATE_REQ_STRU
   : ATMTA MODEM

  1.       : 201688
           : h00313353
       : New
*****************************************************************************/
typedef struct
{
    AT_MTA_MODEM_CAP_UPDATE_TYPE_ENUM_UINT8                 enModemCapUpdateType;   /* MODEM */
    VOS_UINT8                                               aucReserved[3];
} AT_MTA_MODEM_CAP_UPDATE_REQ_STRU;

/*****************************************************************************
     : MTA_AT_MODEM_CAP_UPDATE_CNF_STRU
   : MTAAT MODEM

  1.       : 201688
           : h00313353
       : New
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32                               enRslt;                 /* MODEM */
} MTA_AT_MODEM_CAP_UPDATE_CNF_STRU;

/*******************************************************************************
     : MTA_AT_LTE_CATEGORY_INFO_IND_STRU
   : ID_MTA_AT_LTE_CATEGORY_INFO_IND

 1.       : 20161018
          : l00373346
      : 
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucDlCategery;                           /* category */
    VOS_UINT8                           ucUlCategery;                           /* category */
    VOS_UINT8                           aucReserved[2];                         /*  */
} MTA_AT_LTE_CATEGORY_INFO_IND_STRU;

/*****************************************************************************
  8 UNION
*****************************************************************************/
/*****************************************************************************
  9 OTHERS
*****************************************************************************/

/*****************************************************************************
  H2ASN
*****************************************************************************/
typedef struct
{
    AT_MTA_MSG_TYPE_ENUM_UINT32         ulMsgId;                                /*_H2ASN_MsgChoice_Export AT_MTA_MSG_TYPE_ENUM_UINT32*/
    AT_APPCTRL_STRU                     stAppCtrl;
    VOS_UINT8                           aucMsgBlock[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          AT_MTA_MSG_TYPE_ENUM_UINT32
    ****************************************************************************/
}AT_MTA_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    AT_MTA_MSG_DATA                     stMsgData;
}AtMtaInterface_MSG;

/*******************************************************************************
     : AT_MTA_MODEM_TIME_STRU
   :

  1.       : 20160530
           : LWX331495
       : 
*******************************************************************************/
typedef struct
{
    VOS_INT32                           lSec;
    VOS_INT32                           lMin;
    VOS_INT32                           lHour;
    VOS_INT32                           lDay;
    VOS_INT32                           lMonth;
    VOS_INT32                           lYear;
    VOS_INT32                           lZone;
}AT_MTA_MODEM_TIME_STRU;

/*****************************************************************************
     : MTA_AT_SET_TIME_CNF_STRU
   : MTAATMODEM TIME

  1.       : 20160531
           : LWX331495
       : 
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
} MTA_AT_SET_TIME_CNF_STRU;

/*****************************************************************************
     : AT_MTA_BESTFREQ_SET_REQ_STRU
   : ATMTA

  1.       : 20160726
           : p00371183
       : 
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucDeviceID;      /* ID, 01-255 */
    VOS_UINT8                           ucMode;          /* 01 */
    VOS_UINT8                           aucReserved[2];
}AT_MTA_BESTFREQ_SET_REQ_STRU;


/*****************************************************************************
     :MTA_AT_TAS_TEST_RATMODE_ENUM_UINT32
   :
 ASN.1 :
   :,
            DRVGULT;
            DrvInterface.hPWC_COMM_MODE_E

 1.       : 2016928
          : LWX331495
      : 
*****************************************************************************/
enum MTA_AT_RCM_TAS_TEST_RATMODE_ENUM
{
    MTA_AT_RATMODE_GSM                  = 0,
    MTA_AT_RATMODE_WCDMA                = 1,
    MTA_AT_RATMODE_LTE                  = 2,
    MTA_AT_RATMODE_TDS                  = 3,
    MTA_AT_RATMODE_1X                   = 4,
    MTA_AT_RATMODE_HRPD                 = 5,
    MTA_AT_RATMODE_BUTT
};
typedef VOS_UINT32 MTA_AT_TAS_TEST_RATMODE_ENUM_UINT32;

/*****************************************************************************
     : AT_MTA_TAS_TEST_CFG_NTE_STRU
   : ATMTATAS

  1.       : 20160928
           : LWX331495
       : 
*****************************************************************************/
typedef struct
{
    MTA_AT_TAS_TEST_RATMODE_ENUM_UINT32 enRatMode;                                      /* 1-WCDMA   2-TLE */
    VOS_UINT32                          ulPara0;
    VOS_UINT32                          ulPara1;
    VOS_UINT32                          ulPara2;
    VOS_UINT32                          ulPara3;
} AT_MTA_TAS_TEST_CFG_STRU;

/*****************************************************************************
     : AT_MTA_TAS_TEST_CFG_NTE_STRU
   : ATMTATAS

  1.       : 20160928
           : LWX331495
       : 
*****************************************************************************/
typedef struct
{
    VOS_RATMODE_ENUM_UINT32             enRatMode;                                      /* 1-WCDMA   2-TLE */
} AT_MTA_TAS_TEST_QRY_STRU;

/*****************************************************************************
     : MTA_AT_TAS_TEST_CNF_NTE_STRU
   : MTAATTAS

  1.       : 2016928
           : LWX331495
       : 
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
} MTA_AT_TAS_TEST_CFG_CNF_STRU;

/*****************************************************************************
    : MTA_AT_TX_STATEII_LEVEL_STRU
  : MAS_TX_STATEII

 1.       : 2016928
          : LWX331495
      : 
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwSrcAntTimeLength;                    /* ():ms */
    VOS_UINT16                          uhwDestAntTimeLength;                   /* :ms */
    VOS_INT16                           shwSrcAntTxPowerGain;                   /* ():0.1dB */
    VOS_INT16                           shwDestAntTxPowerGain;                  /* :0.1dB */
}MTA_AT_TX_STATEII_LEVEL_STRU;

/*****************************************************************************
     : MTA_AT_TX_STATEII_LEVEL_TABLE_STRU
   : MTAATTAS

  1.       : 2016928
           : LWX331495
       : 
*****************************************************************************/
#define MAX_STATEII_LEVEL_ITEM          4
typedef struct
{
    VOS_UINT16                          uhwLevelNum;
    VOS_UINT16                          uhwRsv;
    MTA_AT_TX_STATEII_LEVEL_STRU        astLevelItem[MAX_STATEII_LEVEL_ITEM];
}MTA_AT_TX_STATEII_LEVEL_TABLE_STRU;


/*****************************************************************************
     : MTA_AT_TAS_TEST_QRY_CNF_STRU
   : MTARCMAT

  1.       : 20161024
           : LWX331495
       : 
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32               enResult;
    MTA_AT_TAS_TEST_RATMODE_ENUM_UINT32     enRatMode;
    VOS_UINT32                              ulCurrLevel;                        /*  */
    MTA_AT_TX_STATEII_LEVEL_STRU            stLevelInfo;                        /*  */
    MTA_AT_TX_STATEII_LEVEL_TABLE_STRU      stUsedTable;                        /*  */
}MTA_AT_TAS_TEST_QRY_CNF_STRU;

/*****************************************************************************
     : AT_MTA_RS_INFO_QRY_REQ_STRU
   : ATMTA

  1.       : 2017117
           : wx270776
       : +RSRP/+RSRQ
*****************************************************************************/
typedef struct
{
    AT_MTA_RS_INFO_TYPE_ENUM_UINT32     enRsInfoType;                           /* 0:RSRP1:RSRQ */
}AT_MTA_RS_INFO_QRY_REQ_STRU;

/*****************************************************************************
     : MTA_AT_RSRP_INFO_STRU
   : MTAATLTE RSRP

  1.       : 2017117
           : wx270776
       : +RSRP
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulCellId;                               /* ID */
    VOS_UINT32                          ulEarfcn;                               /*  */
    VOS_INT32                           lRsrp;                                  /* LRRC100AT */
}MTA_AT_RSRP_INFO_STRU;

/*****************************************************************************
     : MTA_AT_RSRQ_INFO_STRU
   : LRRCMTALTE RSRQ

  1.       : 2017117
           : wx270776
       : +RSRQ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulCellId;                               /* ID */
    VOS_UINT32                          ulEarfcn;                               /*  */
    VOS_INT32                           lRsrq;                                  /* LRRC100AT */
}MTA_AT_RSRQ_INFO_STRU;

/*****************************************************************************
     : MTA_AT_RS_INFO_RSLT_STRU
   : MTAATLTE

  1.       : 2017117
           : wx270776
       : +RSRP/+RSRQ
*****************************************************************************/
typedef struct
{
    AT_MTA_RS_INFO_TYPE_ENUM_UINT32     enRsInfoType;                           /* 0:RSRP1:RSRQ */
    VOS_UINT32                          ulRsInfoNum;
    union
    {
        MTA_AT_RSRP_INFO_STRU           astRsrpInfo[AT_MAX_RS_INFO_NUM];        /* RSRP */
        MTA_AT_RSRQ_INFO_STRU           astRsrqInfo[AT_MAX_RS_INFO_NUM];        /* RSRQ */
    }u;
}MTA_AT_RS_INFO_RSLT_STRU;

/*****************************************************************************
     : MTA_AT_RS_INFO_QRY_CNF_STRU
   : MTAATLTE

  1.       : 2017117
           : wx270776
       : +RSRP/+RSRQ
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
    MTA_AT_RS_INFO_RSLT_STRU            stRsInfoRslt;
}MTA_AT_RS_INFO_QRY_CNF_STRU;

/*****************************************************************************
  10 
*****************************************************************************/


#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif

