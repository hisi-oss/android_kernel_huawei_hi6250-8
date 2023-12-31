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


#ifndef __DRV_NV_DEF_H__
#define __DRV_NV_DEF_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "mdrv_nv_comm_def.h"

#define LDO_GPIO_MAX        2
#define RSE_MIPI_SW_REG_NUM 8
#define RSE_MODEM_NUM       2
#define PASTAR_NUM   2

/*******************************************************************/

/*****************************************************************************
     : nv_protocol_base_type
   : nv_protocol_base_type ID= en_NV_Item_Modem_Log_Path 148
 			MBB modem logmodem log
*****************************************************************************/
/*NV ID = 50018*/
#pragma pack(push)
#pragma pack(1)
	typedef struct
	{
		s32 	   nvStatus;
		s8		   nv_version_info[30];
	}NV_SW_VER_STRU;
#pragma pack(pop)
/*END NV ID = 50018*/

typedef struct
{
   char  ucModemLogPath[32];
   char  modemLogRsv[4];
}NV_MODEM_LOG_PATH;



/*NV ID = 0xd109*/
/*10*/
typedef struct
{
	s32 buck2_switch;    /*[0, 1]*/
}NV_PASTAR_BUCK2_SWITCH_STRU;
/*end NV ID = 0xd109*/

/*NV ID  = 0xd10b*/

typedef struct ST_PWC_SWITCH_STRU_S {

	/*NVBIT*/
 	u32 deepsleep  :1; /*bit0*/
    u32 lightsleep :1; /*bit1*/
    u32 dfs        :1; /*bit2*/
    u32 hifi       :1; /*bit3*/
    u32 drxAbb     :1; /*bit4*/
    u32 drxZspCore :1; /*bit5*/
    u32 drxZspPll  :1; /*bit6*/
    u32 drxWLBbpPll  :1; /*bit7*/
    u32 drxGBbpPll   :1; /*bit8*/
    u32 drxRf      :1; /*bit9*/
    u32 drxPa      :1; /*bit10*/
    u32 drxGuBbpPd   :1; /*bit11*/
    u32 drxDspPd     :1; /*bit12*/
    u32 drxLBbpPd    :1; /*bit13*/
    u32 drxPmuEco    :1; /*bit14*/
    u32 drxPeriPd    :1; /*bit15*/
    u32 l2cache_mntn  :1; /*bit16*/
    u32 bugChk     :1; /*bit17*/
    u32 pmuSwitch     :1; /*bit18*/
    u32 drxLdsp      :1;  /*bit 19*/
    u32 matserTDSpd  :1; /*bit20*/
    u32 tdsClk    :1;  /*bit21*/
    u32 slaveTDSpd   :1; /*bit22*/
    u32 slow	     :1;/*bit23*/
    u32 ccpu_hotplug_suspend      :1;/*bit24 cpususpend*/
    u32 ccpu_hotplug_crg      :1;/*bit25 l1cacheremove smpcpu*/
    u32 ccpu_tickless          :1;/*bit26 ccpu tickless*/
    u32 reserved    :5; /*bit27-31*/

	/*NVDEBUG*/
	u32 drx_pa_pd        :1; /*bit0 PA*/
    u32 drx_rfic_pd      :1; /*bit1 RFIC*/
    u32 drx_rfclk_pd     :1; /*bit2 RFIC CLK*/
    u32 drx_fem_pd       :1; /*bit3 FEM*/
    u32 drx_cbbe16_pd    :1; /*bit4 CBBE16*/
    u32 drx_bbe16_pd     :1; /*bit5 BBE16*/
    u32 drx_abb_pd       :1; /*bit6 ABB*/
    u32 drx_bbp_init     :1; /*bit7 BBP*/
    u32 drx_bbppwr_pd    :1; /*bit8 BBP*/
    u32 drx_bbpclk_pd    :1; /*bit9 BBP*/
    u32 drx_bbp_pll      :1; /*bit10 BBP_PLL*/
    u32 drx_cbbe16_pll   :1; /*bit11 CBBE16_PLL*/
    u32 drx_bbe16_pll    :1; /*bit12 BBE16_PLL*/
    u32 drx_bbp_reserved :1; /*bit13 bbp*/
    u32 drx_abb_gpll     :1; /*bit14 ABB_GPLL*/
    u32 drx_abb_scpll    :1; /*bit15 ABB_SCPLL*/
    u32 drx_abb_reserved1:1;
    u32 drx_abb_reserved2:1;
    u32 reserved2        :14; /*bit18-31 */
}ST_PWC_SWITCH_STRU;

typedef struct ST_PWC_PM_DEBUG_CFG_STRU_S {
    u32 sr_time_ctrl :1;    /*bit0*/
	u32 bugon_reset_modem:1;/*bit1*/
	u32 print_to_ddr:1;/*bit2*/
    u32 reserved     :29;/*bit3-31*/
    /*NVPM */
    u32 dpm_suspend_time_threshold ;/*dpm suspend*/
    u32 dpm_resume_time_threshold  ;/*dpm resume*/
    u32 pm_suspend_time_threshold  ;/*pm suspend*/
    u32 pm_resume_time_threshold   ;/*pm resume*/
}ST_PWC_PM_DEBUG_CFG_STRU;

/*NV ID = 0xd10c*/
typedef struct ST_PWC_DFS_STRU_S {
    u32 CcpuUpLimit;
	u32 CcpuDownLimit;
	u32 CcpuUpNum;
	u32 CcpuDownNum;
	u32 AcpuUpLimit;
	u32 AcpuDownLimit;
	u32 AcpuUpNum;
	u32 AcpuDownNum;
	u32 DFSTimerLen;
	u32 DFSHifiLoad;
 	u32 Strategy;/*bit0:1->200ms,bit0:0->4s;bit1:1/0/DDR*/
 	u32 DFSDdrUpLimit;
 	u32 DFSDdrDownLimit;
 	u32 DFSDdrprofile;
 	u32 reserved;
}ST_PWC_DFS_STRU;

/*NV ID = 0xd153*/
typedef struct ST_PWC_IDLEFREQ_STRU_S {
    u32 ccpu_idlefreq_en;
    u32 slow_idlefreq_en;
    u32 bbpphy_idlefreq_en;
}ST_PWC_IDLEFREQ_STRU;

/*NV ID = 0xd157 DVShpm*/
typedef struct {
	u32 dvs_en;
	u32 hpm_delay;
}ST_DVS_CONFIG_STRU;
/*NV ID = 0xd10f beginPMU*/
typedef struct
{
    u8  VoltId;         /*id*/
    u8  VoltOcpIsOff;   /**/
    u8  VoltOcpIsRst;   /**/
    u8  VoltOtpIsOff;   /*PMU*/
} PMU_VOLT_PRO_STRU;
typedef struct
{
    u8    ulOcpIsOn;        /*:0:1:--0*/
    u8    ulOcpIsOff;       /*:0:1:--1*/
    u8    ulOtpCurIsOff;    /*():0:1:--1*/
    u8    ulOtpIsRst;       /*():0:1:--0*/

    u8    ulOtpIsOff;       /*PMU150PMU():0:PMU1:PMUPMU--1*/
    u8    ulUvpIsRst;       /*0:*/
    u16   reserved2;

    u16   ulOtpLimit;       /*:105:105115:115125:125 135:135 (HI6559135)125--125 */
    u16   ulUvpLimit;       /*mv:3000:3v; 2700:2.7v(2850:2.85v.HI65592.85,HI65512.7) 3v--3000*/

    PMU_VOLT_PRO_STRU VoltProConfig[50];/**/
} PMU_EXC_PRO_NV_STRU;

/*NV ID = 0xd10f end*/

/*ID=0xd110*/
typedef struct
{
    u32    u32CalcTime;        /* (10ms) */
    u32    u32PktNum;          /*  */
    u32    u32SwichFlag;       /* netif */
} NETIF_INIT_PARM_T;

/*ID=0xd111 begin */
typedef struct
{
    u32 dump_switch    : 2; /* 00: excdump, 01: usbdump, 1x: no dump */
    u32 ARMexc         : 1; /* 2 ARM*/
    u32 stackFlow      : 1; /* 3 */
    u32 taskSwitch     : 1; /* 4 */
    u32 intSwitch      : 1; /* 5 */
    u32 intLock        : 1; /* 6 */
    u32 appRegSave1    : 1; /* 7 1 */
    u32 appRegSave2    : 1; /* 8 2*/
    u32 appRegSave3    : 1; /* 9 3*/
    u32 commRegSave1   : 1; /* 10 1 */
    u32 commRegSave2   : 1; /* 11 2*/
    u32 commRegSave3   : 1; /* 12 3*/
    u32 sysErrReboot   : 1; /* 13 systemError*/
    u32 reset_log      : 1; /* 14 */
    u32 fetal_err      : 1; /* 15 */
	u32 log_ctrl       : 2; /* bsp_trsce */
    u32 reserved1      : 14;
} DUMP_CFG_STRU;

typedef struct
{
    union
    {
        u32         uintValue;
        DUMP_CFG_STRU   Bits;
    } dump_cfg;

    u32 appRegAddr1;	/* ACORE1*/
    u32 appRegSize1;	/* ACORE1*/
    u32 appRegAddr2;	/* ACORE2*/
    u32 appRegSize2;	/* ACORE2*/
    u32 appRegAddr3;	/* ACORE3*/
    u32 appRegSize3;	/* ACORE3*/

    u32 commRegAddr1;	/* CCORE1*/
    u32 commRegSize1;	/* CCORE1*/
    u32 commRegAddr2;	/* CCORE2*/
    u32 commRegSize2;	/* CCORE2*/
    u32 commRegAddr3;	/* CCORE3*/
    u32 commRegSize3;	/* CCORE3*/

    u32 traceOnstartFlag;           /* 0:Trace, 0:Trace */
    u32 traceCoreSet;               /* 0:ATrace, 1:CTrace, 2:Trace */
    u32 busErrFlagSet;             /* 0:, 0: */
} NV_DUMP_STRU;
/*ID=0xd111 end */

/*NV ID = 0xd114 begin,PMU*/
#define NUM_OF_PMU_NV  50
typedef struct
{
    u8  VoltId;     /*id*/
    u8  IsNeedSet;  /*:0:1:*/
    u8  IsOnSet;    /*:0:1:*/
    u8  IsOffSet;   /*:0:1:*/

    u8  IsVoltSet;  /*:0:1:*/
    u8  IsEcoSet;   /*ECO:0:1:*/
    u8  EcoMod;     /*eco:0:normal;2:force_eco;3:follow_eco*/
    u8  reserved3;  /**/

    u32 Voltage;    /**/
} PMU_INIT_CON_STRU;
typedef struct
{
    PMU_INIT_CON_STRU InitConfig[NUM_OF_PMU_NV];
} PMU_INIT_NV_STRU;
/*NV ID = 0xd114 end*/

/*NV ID = 0xd115 start*/

typedef struct {
    u32	index;           /*(1+2)*/
    u32	hwIdSub;        /**/
	char  name[32];           /**/
    char	namePlus[32];       /*PLUS*/
    char	hwVer[32];          /**/
    char	dloadId[32];        /**/
    char	productId[32];      /**/
}PRODUCT_INFO_NV_STRU;

/*NV ID =0xd115 end*/

/*NV ID =0xd116 start,mipi0_chn*/
typedef struct{
	u32 mipi_chn;
}MIPI0_CHN_STRU;
/*NV ID =0xd116 end,mipi0_chn*/

/*NV ID =0xd117 start,mipi1_chn*/
typedef struct{
	u32 mipi_chn;
}MIPI1_CHN_STRU;
/*NV ID =0xd117 end,mipi1_chn*/

/*NV ID =0xd12e start, rf power control, pastar config*/
typedef struct{
	u32 rfpower_m0;/*[0, 1,2]*//*modem0,0,value01pastar2LDO*/
	u32 rfpower_m1;/*[0, 1,2]*//*modem1,1,value01pastar2LDO*/
}NV_RFPOWER_UNIT_STRU;
/*NV ID =0xd12e start, pastar config*/

/* NV ID =0xd13A start, pa power control, pastar config */
typedef struct{
	u32 papower_m0;/*[0,1,2]*//*modem0,0,value01pastar2*/
	u32 papower_m1;/*[0,1,2]*//*modem1,1,value01pastar2*/
}NV_PAPOWER_UNIT_STRU;
/* NV ID =0xd13A start, pastar config */

typedef struct
{
    u32   nvSysTimeValue;   /*  */
}SYS_TIME;

typedef struct
{
    u32  ulIsEnable;				/**/
    u32    lCloseAdcThreshold;
    u32  ulTempOverCount;
}CHG_BATTERY_HIGH_TEMP_PROT_NV;

typedef struct
{
    u32  ulIsEnable;			/**/
    u32    lCloseAdcThreshold;
    u32  ulTempLowCount;
}CHG_BATTERY_LOW_TEMP_PROTE_NV;

/* nv,0 :  1: **/
typedef struct
{
    u32 ulFactoryMode;
}FACTORY_MODE_TYPE;

/*  */
typedef struct
{
    u32 ulTryTimes;
}BOOT_TRY_TIMES_STRU;

/*  */
typedef struct
{
    u32 ulPowKeyTime;
}POWER_KEY_TIME_STRU;

typedef struct
{
    u16 temperature;
    u16 voltage;
}CHG_TEMP_ADC_TYPE;

typedef struct
{
    CHG_TEMP_ADC_TYPE g_adc_batt_therm_map[31];
}NV_BATTERY_TEMP_ADC;


/*nv,1 :  0: */
typedef struct
{
    u32 ulHwVer;
}E5_HW_TEST_TYPE;

/*APTnv,1 :  0: */
typedef struct
{
    u32 ulIsSupportApt;
}NV_SUPPORT_APT_TYPE;

/*PMUnv*/
typedef struct
{
    u8 TemppmuLimit;  /*PMU:0:105;1:115;2:125;3:135*/
	u8 ulCurIsOff;  /*01*/
	u8 ulOcpIsRst;  /*: 0: 1:*/
	u8 PmuproIsOn;  /*PMU01*/
}PMU_PRO_NV;

typedef struct
{
    u32 u32SciGcfStubFlag;   /* 1: GCF0GCF */
}SCI_NV_GCF_STUB_FLAG;

/*NV*/
typedef struct
{
    u32 ulEnable;   /*01*/
}NV_SHORT_ONOFF_ENABLE_TYPE;

/*NV*/
typedef struct NV_SHORT_ONOFF_TYPE_S
{
    u32 ulPowerOffMaxTimes;   /**/
	u32 ulMaxTime;            /**/
	u32 ulVoltLevel1;         /**/
	u32 ulVoltLevel2;         /**/
	u32 ulRTCLevel1;          /*RTC*/
	u32 ulRTCLevel2;          /*RTC*/
	u32 ulRTCLevel3;          /*RTC*/
}NV_SHORT_ONOFF_TYPE;

/*NV*/
typedef struct
{
        u32 ulLEDEnable;   /*LED 01*/
        u32 ulReserved1;   /*  01*/
        u32 ulReserved2;   /*  01*/
}NV_POWER_SAVE_TYPE;

/**/
typedef struct
{
    u32 v_offset_a;         /*  */
    s32 v_offset_b;         /* */
    u32 c_offset_a;         /*  */
    s32 c_offset_b;         /*  */
}COUL_CALI_NV_TYPE;

/*HKADC NV_ID_DRV_TEMP_HKADC_CONFIG            = 0xd120 */

typedef struct
{
    u32 out_config;         /* bit0-bit1 0: 1: 2: */
                                /* bit2 1: 0: */
                                /* bit3: 0: 1: */
                                /* bit8: A */
                                /* bit9: C */
    u32 have_config;
    u16 out_period;         /* : */
    u16 convert_list_len;   /*  */
    u16 convert_list_id;    /* NVusTempDataLen */
    u16 reserved;
}TEMP_HKADC_CHAN_CONFIG;

typedef struct
{
    TEMP_HKADC_CHAN_CONFIG chan_config[16];

}TEMP_HKADC_CHAN_CONFIG_ARRAY;

typedef struct adc_convert_conf {
    u32 convert_period; //ms
    u32 convert_num;    //convert_numconvert_num0n(n>0)n
} adc_convert_conf;
typedef struct adc_convert_conf_array
{
    adc_convert_conf convert_conf[16];
} adc_convert_conf_array;
typedef struct convert_table
{
    s32 temperature;
    u16 code;
    u16 reserved;
} convert_table;
#define XO_TBL_SIZE 166
typedef struct xo_convert_table_array
{
    convert_table convert_table[XO_TBL_SIZE];
} xo_convert_table_array;
#define PA_TBL_SIZE 32
typedef struct pa_convert_table_array
{
    convert_table convert_table[PA_TBL_SIZE];
} pa_convert_table_array;
/*HKADC NV_ID_DRV_TEMP_TSENS_CONFIG            = 0xd121 */
typedef struct
{
    u16 enable;         /* bit0: bit1: 1  0 */
    u16 high_thres;     /*   */
    u16 high_count;     /*  */
    u16 reserved;
    /*u32 low_thres;*/  /*  */
    /*u32 low_count;*/  /*  */

}TEMP_TSENS_REGION_CONFIG;

typedef struct
{
    TEMP_TSENS_REGION_CONFIG region_config[3];

}TEMP_TSENS_REGION_CONFIG_ARRAY;



/*  NV_ID_DRV_TEMP_BATTERY_CONFIG          = 0xd122 */
typedef struct
{
    u16 enable;        /* bit0: bit1: 1  0 */
    u16 hkadc_id;      /* hkadcID */
    u16 high_thres;    /*  */
    u16 high_count;    /*  */
    s16 low_thres;     /*  */
    u16 low_count;     /*  */

    u32 reserved[2];   /**/
} DRV_SYS_TEMP_STRU;

/*  NV_ID_DRV_TEMP_CHAN_MAP          = 0xd126 */
typedef struct
{
    u8 chan_map[32];

}TEMP_HKADC_PHY_LOGIC_ARRAY;

/* USB Feature for usb id:50075 */
typedef struct
{
    u8 flags;
    u8 reserve1;
    u8 hibernation_support;/**/
    u8 pc_driver;
    u8 detect_mode;/*0=pmu detect; 1=no detect(for fpga&cpe); 2=car module vbus detect */
    u8 enable_u1u2_workaround;
    u8 usb_gpio_support:4;
    u8 usb_mode:4;
    u8 network_card;
} NV_USB_FEATURE;


typedef struct
{
    u32 sci_dsda_select;        /* 0: sim0, 1:sim1*/
} DRV_SCI_DSDA_SELECT;
/* SIM gcf test flage*/
typedef struct
{
    u32 sci_gcf_sub_flag;        /* 0: open, 1:close */
} DRV_SCI_GCF_STUB_FLAG;

/*E5*/
typedef struct
{
	u32 wait_usr_sele_uart : 1;//[bit 0-0]1: await user's command for a moment; 0: do not wait
	u32 a_core_uart_num    : 2;//[bit 1-2]the number of uart used by a core
	u32 c_core_uart_num    : 2;//[bit 3-4]the number of uart used by c core
	u32 m_core_uart_num    : 2;//[bit 5-6]the number of uart used by m core
	u32 a_shell            : 1;//[bit 7-7]0:ashell is not used; 1:ashell is used
	u32 c_shell            : 1;//[bit 8-8]0:cshell is not used; 1:cshell is used
	u32 uart_at            : 1;//[bit 9-9]uart at control
	u32 extendedbits       : 22;//[b00]1:open cshell_auart; 0:close
}DRV_UART_SHELL_FLAG;

/* product support module nv define */
typedef struct
{
	u32 sdcard 		: 1;//1: support; 0: not support
	u32 charge 		: 1;
	u32 wifi    	: 1;
	u32 oled    	: 1;
	u32 hifi        : 1;
	u32 onoff       : 1;
	u32 hsic        : 1;
	u32 localflash  : 1;
	u32 reserved    : 24;
} DRV_MODULE_SUPPORT_STRU;

/* TEST support module nv define */
typedef struct
{
	u32 lcd 		: 1;//1: support; 0: not support
	u32 emi 		: 1;
	u32 pwm     	: 1;
	u32 i2c    	    : 1;
	u32 leds        : 1;
	u32 reserved    : 27;
} DRV_MODULE_TEST_STRU;

typedef struct
{
	u8 normalwfi_flag;
	u8 deepsleep_flag;
	u8 buck3off_flag;
	u8 peridown_flag;
	u32 deepsleep_Tth;
	u32 TLbbp_Tth;
}DRV_NV_PM_TYPE;


/* NV_ID_DRV_DDR_AUTOREF    = 0Xd152, */


/*
rank_num
, 
  0,   rank_num-1
 <=0  >=(rank_num-1)  

ddr_autoref_t
8,<=[n] n
0,7;6
8

ddr_autoref_t2
 
 >ddr_autoref_t[n] n+1 <=ddr_autoref_t[n]
 >ddr_autoref_t2[n]nn+1

ddr_autoref_cfg
8 bit0 bit1
0 7 0
80

*/

/*
t(a,b]  ddr_autoref_t[a]<<=ddr_autoref_t[b]
0  t(-,0] -  cfg[0] 
1  t(0,1] -  cfg[1]
2  t(1,2] -  cfg[2]
3  t(2,3] -  cfg[3]
4  t(3,4] -  cfg[4]
5  t(4,5] -  cfg[5]
6  t(5,6] -  cfg[6]
7  t(6,7] -  cfg[7] 
*/

#define DDR_AUTOREF_RANK_NUM 8
#define DDR_AUTOREF_ERR_CFG 0

typedef struct
{
    u32 enable_flag;
    u32 timeout;/* ms */
    u32 sleep_timeout;/* ms */
    u32 rank_num;       /*  */
    s32 ddr_autoref_t[DDR_AUTOREF_RANK_NUM];
    s32 ddr_autoref_t2[DDR_AUTOREF_RANK_NUM];
    u32 ddr_autoref_cfg[DDR_AUTOREF_RANK_NUM];
}DDR_AUTOREF_NV_STRU;


/* NV_ID_DRV_TSENS_TABLE = 0xd129*/
typedef struct
{
    s16 temp[256];

}DRV_TSENS_TEMP_TABLE;

typedef struct
{
    u32 clkdis1; /*crg clk dis1*/
    u32 clkdis2; /*crg clk dis2*/
    u32 clkdis3; /*crg clk dis3*/
    u32 clkdis4;  /*crg clk dis4*/
	u32 clkdis5;  /*crg clk dis5*/
    u32 mtcmosdis; /*MTCMOScrg mtcmosdis*/
}DRV_NV_PM_CLKINIT_STRU;

typedef struct
{
    u32 ucBBPCh0TcxoSel:1; 	    /* bit 0,CH0 19.2MTCXO0 TCXO0, 1: TCXO1;  0x90000148 */
    u32 ucBBPCh1TcxoSel:1;  	/* bit 1,CH1 19.2MTCXO0 TCXO0, 1: TCXO1;  0x90000148 */
    u32 ucABBCh0TcxoSel:1; 		/* bit 2,ABB Ch0 TCXO0 TCXO0, 1: TCXO1; ABB 0x94 */
    u32 ucABBCh1TcxoSel:1; 		/* bit 3,ABB Ch1 TCXO0 TCXO0, 1: TCXO1;  0x94 */
	u32 ucBbpPllTcxoSel:1; 		/* bit 4,BBP PLL TCXO0 TCXO0, 1: TCXO1;*/
	u32 ucG1bp104mTcxoSel:1; 	/* bit 5,G1BBP 104M ABB00, 1: 1;*/
	u32 ucG2bp104mTcxoSel:1; 	/* bit 6,G1BBP 104M ABB00, 1: 1;*/
	u32 reserve:25;             /* bit 7-31*/
}DRV_TCXO_SEL_PARA_STRU;

typedef struct
{
    u32 u32UsbDbg;   /* usb */
}DRV_USB_DBG_STRU;

typedef struct
{
	u32 wdt_enable;
	u32 wdt_timeout;
	u32 wdt_keepalive_ctime;
	u32 wdt_suspend_timerout;
	u32 wdt_reserve;
}DRV_WDT_INIT_PARA_STRU;

/* axi monitorID */
typedef struct
{
    u32 id_enable;      /*id*/
    u32 cnt_opt;        /*  */
    u32 cnt_type;       /* 01:10:11:: */
    u32 port;           /*  */
    u32 master_id;      /* masterid */
    u32 addr_enable;    /* */
    u32 start_addr;     /*  */
    u32 end_addr;       /*  */
} AMON_CNT_CONFIG_T;

/* axi monitorNV NV_ID_DRV_AMON = 0xd130 */
typedef struct
{
    u32         en_flag;            /* 00:01:SOC10:CPUFAST11:SOC,CPUFAST */
    AMON_CNT_CONFIG_T   config[8];      /* SOC8ID */
} DRV_AMON_CNT_CONFIG_STRU;


/* SOCPNV = 0xd132 */
typedef struct
{
    u32         en_flag;            /* 00:01: */
} DRV_SOCP_ON_DEMAND_STRU;

/* drx delay flag */
typedef struct
{
    u8         lpm3_flag;         /* 0x11 lpm3 */
    u8         lpm3_0;            /* 1delay,delay */
    u8         lpm3_1;
    u8         lpm3_2;
    u8         lpm3_3;
    u8         lpm3_4;
    u8         lpm3_5;
    u8         drv_flag;          /* 0x22 drv */
    u8         drv_0;             /* 1delay,delay */
    u8         drv_1;
    u8         drv_2;
    u8         drv_3;
    u8         drv_4;
    u8         drv_5;
    u8         msp_flag;          /* 0x33 msp */
    u8         msp_0;             /* 1delay,delay */
    u8         msp_1;
    u8         msp_2;
    u8         msp_3;
    u8         msp_4;
}DRV_DRX_DELAY_STRU;

/* CNV = 0xd134 */
typedef struct
{
    u32 is_feature_on:1;         /* bit0, C */
    u32 is_connected_ril:1;      /* bit1, RIL */
	u32 reserve:30;              /* bit 2-31*/
} DRV_CCORE_RESET_STRU;

/* NV ID = 0xd135 */
/* LDOBUCK */
typedef struct
{
	u32 ldo1_switch     :1;         /* 0bit10 */
	u32 ldo2_switch     :1;         /* 1bit10 */
	u32 buckpa_switch   :1;         /* 2bit10 */
	u32 buck1_switch    :1;         /* 3bit10 */
	u32 buck2_switch    :1;         /* 4bit10 */
	u32 reserved        :27;        /* 5~31bit0 */
}NV_PASTAR_SWITCH_STRU_BITS;

typedef struct
{
    union
    {
        u32 u32;
        NV_PASTAR_SWITCH_STRU_BITS bits;
    }cont;
}NV_PASTAR_SWITCH_STRU;
/* end NV ID = 0xd135 */


/* log2.0 2014-03-19 Begin:*/
typedef struct
{
    u32 ulSocpDelayWriteFlg;/* SOCP */
    u32 ulGuSocpLevel;      /* GU SOCPBUFFER */
    u32 ulLSocpLevel;       /* L SOCPBUFFER */
    u32 ulTimeOutValue;     /* SOCPBUFFER */
}DRV_NV_SOCP_LOG_CFG_STRU;
/* log2.0 2014-03-19 End*/
typedef struct
{
    u32  enUartEnableCfg;
	u32  enUartlogEnableCfg;
	u32  AwakeTmer;
	u32  DoSleepTimer;
}DRV_DUAL_MODEM_STR;

typedef struct
{
	u32 enUart5IrqCfg;
	u32 dmInitCfg;
	u32 ex1_param;
	u32 ex2_param;
	u32 ex3_param;
	u32 ex4_param;
}DRV_DM_UART5_STR;

/* GPIOLDO NV = 0xd137 */
typedef struct
{
    u32 gpio;      /* LDOGPIO */
    u32 used;      /* GPIO */
} DRV_DRV_LDO_GPIO_CFG;

typedef struct
{
    DRV_DRV_LDO_GPIO_CFG ldo_gpio[LDO_GPIO_MAX];/*0fem1rf*/
}DRV_DRV_LDO_GPIO_STRU;

/* RSE POWER GPIO NV = 0xd139 */
typedef struct
{
    u32 ulRsePowerOnIds;
    u32 ulFemCtrlInfo;
    u32 ulRfGpioBitMask;
    u32 ulRfGpioOutValue;
    u16 usFemMipiCmdAddr;
    u16 usFemMipiCmdData;
}RF_NV_RSE_CFG_STRU;

/*NV*/
/*NVID = 0xd13b01*/
typedef struct
{
	u32 is_enable;/*Range:[0,1]*/
}DRV_ANT_SW_UNPD_ENFLAG;

typedef struct
{
	u32 gpio_num;	/*GPIO    */
	u32 is_used;	/*Range:[0,1]*//**/
	u32 value;		/* */
}DRV_ANT_GPIO_CFG;

/*nvID = 0xd13c*/
/*+modem8zhaojun*/
/*01122modem*/
typedef struct
{
	DRV_ANT_GPIO_CFG 	antn_switch[8];
}DRV_ANT_SW_UNPD_CFG;

typedef struct
{
	DRV_ANT_SW_UNPD_CFG all_switch[3];
}NV_DRV_ANT_SW_UNPD_CFG;
/*End NV*/

/**/
typedef struct
{
	u32 en_flag;
}NV_DRV_FEM_SHARE_POWER;

/*rse mipi */
typedef struct
{
	u32 en_flag;
}DRV_ANT_SW_MIPI_ENFLAG;

typedef struct
{
    u32 is_invalid;/*mipi*/
    u8  mipi_chn;  /*mipi*/
    u8  slave_id;  /*slave id*/
    u8  reg_offset;/**/
    u8  value;     /**/
}DRV_ANT_SW_MIPI;

typedef struct
{
    DRV_ANT_SW_MIPI modem_switch[RSE_MIPI_SW_REG_NUM];     /*modemmipi8*/
}DRV_ANT_SW_MIPI_CONFIG;

typedef struct
{
    DRV_ANT_SW_MIPI_CONFIG all_switch[RSE_MODEM_NUM];/*0modem01modem1*/
}DRV_DRV_ANT_SW_MIPI_CONFIG;

/*end rse mipi */
typedef struct
{
	u32 DialupEnableCFG;
	u32 DialupACShellCFG;
}DRV_DIALUP_HSUART_STRU;


/*
*nvid = 0xd13d
*for mmc support or not
*/
typedef struct
{
	u32 support;
}DRV_MMC_SUPPORT_STRU;

/* PA/RFEM_MODEM_CONSUMER_ID */
/* CONSUMERid
typedef enum EM_MODEM_CONSUMER_ID_E
{
    MODEM_PA0,
    MODEM_RFIC0_ANALOG0,
    MODEM_RFIC0_ANALOG1,
    MODEM_FEM0,
    MODEM_PA_VBIAS0,
    MODEM_PA1,
    MODEM_RFIC1_ANALOG0,
    MODEM_RFIC1_ANALOG1,
    MODEM_FEM1,
    MODEM_PA_VBIAS1,
    MODEM_CONSUMER_ID_BUTT
}EM_MODEM_CONSUMER_ID;
*/
typedef struct
{
	u32 pa0 				: 1;	//1: ; 0: 
	u32 rfic0_analog0 		: 1;
	u32 rfic0_analog1    	: 1;
	u32 fem0    			: 1;
	u32 pa_vbias0       	: 1;
	u32 pa1 				: 1;
	u32 rfic1_analog0 		: 1;
	u32 rfic1_analog1    	: 1;
	u32 fem1    			: 1;
	u32 pa_vbias1       	: 1;
    u32 gpa                 : 1;
	u32 reserved    : 21;
}PARF_SWITCH_BITS;

typedef struct
{
    union
    {
        u32 u32;
        PARF_SWITCH_BITS bits;
    }cont;
} NV_DRV_PARF_SWITCH_STRU;

/* NVID=0xd144 begin */
typedef struct
{
    u32 mdm_dump     :1;     /* modem_dump.bin */
    u32 mdm_sram     :1;     /* modem_sram.bin */
    u32 mdm_share    :1;     /* modem_share.bin */
    u32 mdm_ddr      :1;     /* modem_ddr.bin */
    u32 lphy_tcm     :1;     /* lphy_tcm.bin */
    u32 lpm3_tcm     :1;     /* lpm3_tcm.bin */
    u32 ap_etb       :1;     /* ap_etb.bin */
    u32 mdm_etb      :1;     /* modem_etb.bin */
    u32 reset_log    :1;     /*reset.log*/
    u32 cphy_tcm     :1;     /* cphy_tcm.bin */
    u32 mdm_secshare :1;     /* secshare.bin */
    u32 mdm_dts      :1;     /* modem_dts.bin */
    u32 reserved2   :20;
}DUMP_FILE_BITS;

typedef struct
{
    union
    {
        u32         file_value;
        DUMP_FILE_BITS  file_bits;
    } file_list;
    u32             file_cnt; /*  */
}DUMP_FILE_CFG_STRU;

/*nvID = 0xd140*/
typedef struct
{
    u32 mipi_chn[2];/*pastarmipi*/
}NV_PASTAR_MIPI_CHN_STRU;

/* pm om NV = 0xd145 */
typedef struct
{
	u32 mem_ctrl:1;       /* bit:memory */
    u32 reserved:31;      /* bit: */
	u8  log_threshold[4]; /* acore/ccore/mcore,  */
    u8  mod_sw[8];        /* log */
}DRV_PM_OM_CFG_STRU;
/* NVID=0xd13d end */

/* DSP PLL Ctrl = 0xd146 */
typedef struct
{
    u32 app_a9_en   :1;
    u32 mdm_a9_en   :1;
    u32 reserved    :30;
}NV_DSP_PLL_CTRL_STRU;

typedef struct
{
    u32 tuner_mipi_mask         :4; /* TUNER_MIPI_MASK */
    u32 mipi_primary_bank0_en   :1; /* MIPIModem0bank0 */
    u32 mipi_primary_bank1_en   :1; /* MIPIModem0bank1 */
    u32 mipi_primary_bank2_en   :1; /* MIPIModem0bank2 */
    u32 mipi_primary_bank3_en   :1; /* MIPIModem0bank3 */
    u32 mipi_secondary_bank0_en :1; /* MIPIModem0bank0 */
    u32 mipi_secondary_bank1_en :1; /* MIPIModem0bank1 */
    u32 mipi_secondary_bank2_en :1; /* MIPIModem0bank2 */
    u32 mipi_secondary_bank3_en :1; /* MIPIModem0bank3 */
    u32 mipi_modem1_bank0_en    :1; /* MIPIModem1 bank0 */
    u32 mipi_modem1_bank1_en    :1; /* MIPIModem1 bank1 */
    u32 mipi_modem1_bank2_en    :1; /* MIPIModem1 bank2 */
    u32 mipi_modem1_bank3_en    :1; /* MIPIModem1 bank3 */
    u32 gpio_primary_en         :1; /* GPIOModem0 */
    u32 gpio_secondary_en       :1; /* GPIOModem0 */
    u32 gpio_modem1_en          :1; /* GPIOModem1 */
    u32 reserved3               :13;
} mipi_ctrl_reg;
typedef struct
{
    u32 tuner_en;               /* TUNER_EN */
    u32 tuner_req_en;           /* TUNER_REG_EN */
    mipi_ctrl_reg reg;
}NV_CROSS_MIPI_CTRL;

typedef struct
{
    u32 mipi_buffer[12][96];    /* MIPIbuffer */
    u32 gpio_buffer[3][8];      /* GPIObuffer */
}NV_CROSS_MIPI_MEM;


/*=================NEW CROSS MIPI=====================*/
typedef struct
{
    u32 tuner_mipi_mask         :4; /* TUNER_MIPI_MASK */
    u32 gpio_mask               :17; /* GPIOmask */
    u32 reserved3               :11;
} tuner_ctrl_reg;
typedef struct
{
    u32 tuner_en;               /* TUNER_EN */
    u32 tuner_req_en;           /* TUNER_REG_EN */
    u32 gpio_cross_en;          /* GPIO*/
    u32 tas_ind_en;             /* TAS IND */
    u32 mipi_tuner0_len;        /* MIPI Modem0buffer*/
    u32 mipi_tuner1_len;        /* MIPI Modem0buffer*/
    u32 mipi_tuner2_len;        /* MIPI Modem1buffer*/
    u32 gpio_tuner_len;         /* GPIObuffer*/
    tuner_ctrl_reg reg;
}NV_CROSS_MIPI_GPIO_CTRL;

typedef struct
{
    u32 mipi_buffer[1024];     /* MIPIModem0buffer */
}NV_MIPI_TUNER0_MEM;

typedef struct
{
    u32 mipi_buffer[1024];     /* MIPIModem0buffer */
}NV_MIPI_TUNER1_MEM;

typedef struct
{
    u32 mipi_buffer[1536];     /* MIPIModem1buffer */
}NV_MIPI_TUNER2_MEM;

typedef struct
{
    u32 gpio_buffer[192];      /* GPIObuffer */
}NV_GPIO_TUNER_MEM;

/*=================end NEW CROSS MIPI======================*/

/* watchpoint = 0xd148 begin */
typedef struct
{
    u32 enable;     /* 01  */
    u32 type;       /* : 123 */
    u32 start_addr; /*  */
    u32 end_addr;   /*  */
}WATCHPOINT_CFG;

typedef struct
{
    WATCHPOINT_CFG  ap_cfg[4];  /* A4watchpoint */
    WATCHPOINT_CFG  cp_cfg[4];  /* A4watchpoint */
}DRV_WATCHPOINT_CFG_STRU;
/* watchpoint = 0xd148 end */

typedef struct
{
	u32 enable;        /*, 0, ;  1, */
	u32 reset_enable;  /*, 0, ; 1, */
}DRV_PDLOCK_CFG_STRU;
/* pdlock = 0xd14a */

typedef struct
{
    u32 enable;        /*, 0, ;  1, */
	u32 reset_enable;  /*, 0, ; 1, */
}DRV_DLOCK_CFG_STRU;
/* dlock = 0xd155 */

typedef struct
{
    u32 enable;        /*noc err probe, 0, ;  1, */
    u32 reset_enable;  /*, 0, ; 1, */
}DRV_NOC_CFG_STRU;
/* noc = 0xd169 */

typedef struct
{
    u32 ulResumeMode;       /*NV,1:,2:*/
}NV_SELF_CTRL_STRU;

/* 0xD14C */
#define ABB_INIT_NV_NUM     (200)

typedef struct
{
    u16 addr;
    u8  value;
    u8  reserved;
}NV_ABB_INIT_STRU;

typedef struct
{
    NV_ABB_INIT_STRU cfg[ABB_INIT_NV_NUM];
}NV_ABB_INIT_CFG;

/* 0xD14d */
typedef struct
{
    u32 product         :2;
    u32 reset           :1;
    u32 save_bakup      :1;
    u32 save_image      :1;
    u32 save_ddr        :1;
    u32 resume_bakup    :1;  /*Range:[0,1]*/
    u32 resume_img      :1;  /*Range:[0,1]*/
    u32 reserved        :24;
}NV_DEBUG_CFG_STRU;

/* 0xD14d */
typedef struct
{
	u8  pll_mon_moudle;  /* pll:0,A9PLL; 1,DSPPLL; 2,USBPLL; 3,PERIPLL; 4,TCX0, */
	u8  pll_mon_mode;    /* pll: 0x00, ; 0x01, ; 0x10, ; 0x11 */
	u16 pll_mon_cnt_min; /* clk_monitor */
	u16 pll_mon_cnt_max; /* clk_monitor */
	u8  pll_stop_timeout;/* 125ms */
	u8  reserved;
}DRV_NV_CLK_MONITOR_CFG_STRU;
/* 0xD14F, for tsensor */
typedef struct
{
    s32 high_temp;
    s32 low_temp;
}DRV_TSENSOR_TEMP_THRESHOLD;

/* DSPDVS = 0xd150*/
typedef struct
{
    u32 enable;         /*, 0, ;  1, */
}DRV_DSPDVFS_CFG_STRU;

/* 0xD154 */
typedef struct
{
	u32 fbnet:1;
	u32 avb:1;
	u32 reserved:30;
	u16 rx0_len;
	u16 tx0_len;
	u16 tx1_len;
	u16 tx2_len;
	u32 backup;
}DRV_GMAC_FEATURE;

/*0xd168 begin*/
typedef struct
{
	u32 pmu_enable_cfg;		/*pmu nv*/
	u32 protocol_sel;		/*pmu ssi spmi*/
	u32 reserved;
}DRV_PMU_CFG_STRU;

typedef struct
{
    u32 ap_enable:1;        /*AP coresight enable flag*/
    u32 cp_enable:1;        /*CP coresight enable flag*/
    u32 ap_store :1;        /*AP coresight store flag*/
    u32 cp_store :1;        /*CP coresight store flag*/
    u32 reserved :28;
}DRV_CORESIGHT_CFG_STRU;
/*0xd168 end */

/******************************************************************************************

                 nv,18000nv

*******************************************************************************************/

/*****************************************************************************
        : FEMIO_PIN_CFG_STRU
   : bitnv
*****************************************************************************/
typedef struct
{
	u32 pin_00    : 1; /*1 is select, 0 is not select*/
	u32 pin_01    : 1; /*1 is select, 0 is not select*/
	u32 pin_02    : 1; /*1 is select, 0 is not select*/
	u32 pin_03    : 1; /*1 is select, 0 is not select*/
	u32 pin_04    : 1; /*1 is select, 0 is not select*/
	u32 pin_05	  : 1; /*1 is select, 0 is not select*/
	u32 pin_06 	  : 1; /*1 is select, 0 is not select*/
	u32 pin_07    : 1; /*1 is select, 0 is not select*/
	u32 pin_08    : 1; /*1 is select, 0 is not select*/
	u32 pin_09    : 1; /*1 is select, 0 is not select*/
	u32 pin_10    : 1; /*1 is select, 0 is not select*/
	u32 pin_11    : 1; /*1 is select, 0 is not select*/
	u32 pin_12    : 1; /*1 is select, 0 is not select*/
	u32 pin_13    : 1; /*1 is select, 0 is not select*/
	u32 pin_14    : 1; /*1 is select, 0 is not select*/
	u32 pin_15	  : 1; /*1 is select, 0 is not select*/
	u32 pin_16 	  : 1; /*1 is select, 0 is not select*/
	u32 pin_17    : 1; /*1 is select, 0 is not select*/
	u32 pin_18    : 1; /*1 is select, 0 is not select*/
	u32 pin_19    : 1; /*1 is select, 0 is not select*/
	u32 pin_20    : 1; /*1 is select, 0 is not select*/
	u32 pin_21    : 1; /*1 is select, 0 is not select*/
	u32 pin_22    : 1; /*1 is select, 0 is not select*/
	u32 pin_23    : 1; /*1 is select, 0 is not select*/
	u32 pin_24    : 1; /*1 is select, 0 is not select*/
	u32 pin_25	  : 1; /*1 is select, 0 is not select*/
	u32 pin_26 	  : 1; /*1 is select, 0 is not select*/
	u32 pin_27    : 1; /*1 is select, 0 is not select*/
	u32 pin_28    : 1; /*1 is select, 0 is not select*/
	u32 pin_29    : 1; /*1 is select, 0 is not select*/
	u32 pin_30    : 1; /*1 is select, 0 is not select*/
	u32 pin_31    : 1; /*1 is select, 0 is not select*/
}FEMIO_PIN_CFG_STRU;

/*****************************************************************************
        : RFFE_PIN_ALL_CFG
   : 
*****************************************************************************/
#define  NV_BALONG_MODEM_NUM 3/*Balong modem*/

typedef struct{
    u32 mask;              /*,0bit*/
    u32 mux;               /*,10GPIO*/
    u32 level;             /* ,01*/
}RFFE_PIN_STRU;

typedef struct{
	u32           valid;/**/
	RFFE_PIN_STRU modem_pwron [NV_BALONG_MODEM_NUM]; /*modem*/
	RFFE_PIN_STRU modem_pwroff[NV_BALONG_MODEM_NUM]; /*modem*/
	RFFE_PIN_STRU allmodem_pwroff; /*modem*/
}RFFE_PIN_ALL_CFG;

/*****************************************************************************
        :  NV_FEM_GPIO_MIPI_CTRL_STRU
   :  io
 NV ID               : 18002
*****************************************************************************/

typedef enum{
	FEMIO_CTRL_TOP = 0,/**/
	GPIO_ONLY = 1,     /*GPIO*/
	MIPI_ONLY = 2,     /*MIPI*/
	GPIO_MIPI = 3,     /*GPIOMIPI*/
	FEMIO_CTRL_BUTT
}FEMIO_CTRL_MODE;

/**************************** MIPI NEW NV START *****************************/

typedef struct
{
    RF_NV_MIPIDEV_UNIT_STRU pa[8];
    RF_NV_MIPIDEV_UNIT_STRU rfswitch[8];
    RF_NV_MIPIDEV_UNIT_STRU tunner[8];
    RF_NV_MIPIDEV_UNIT_STRU usrid[16];
    RF_NV_MIPIDEV_UNIT_STRU reserved[16];
}RF_NV_MIPIDEV_INIT_COMM_STRU;

typedef struct
{
    RF_NV_MIPIDEV_UNIT_STRU mipidev_unit[16];
}RF_NV_MIPIDEV_MDM_PWRON_COMM_STRU;

typedef struct
{
    RF_NV_MIPIDEV_UNIT_STRU mipidev_unit[16];
}RF_NV_MIPIDEV_MDM_PWROFF_COMM_STRU;

typedef struct
{
    RF_NV_MIPIDEV_UNIT_STRU mipidev_unit[16];
}RF_NV_MIPIDEV_ALL_MDM_PWROFF_COMM_STRU;

#define CHANNEL_NUM 3

typedef struct
{
    RF_NV_MIPIDEV_INIT_COMM_STRU            init;
    RF_NV_MIPIDEV_MDM_PWRON_COMM_STRU       pwron [CHANNEL_NUM];/*todo:*/
    RF_NV_MIPIDEV_MDM_PWROFF_COMM_STRU      pwroff[CHANNEL_NUM];
    RF_NV_MIPIDEV_ALL_MDM_PWROFF_COMM_STRU  all_pwroff;

}RF_NV_MIPIDEV_ALL_CFG;

typedef struct
{
    RF_NV_MIPIDEV_04CMD profile[32];
}RF_MIPIDEV_COMM_STRU;

/***************************** MIPI NEW NV END ******************************/


/**************************** MIPI OLD NV START *****************************/

/*****************************************************************************
     	: RF_NV_MIPI_CMD_STRU
   	: MIPI 
*****************************************************************************/
typedef struct
{
    u16              SlaveAddr    :4;   /* Mipi Slave0-15 */
    u16              RegAddr      :9;   /*  OR  */
    u16              ByteCnt      :3;   /*Range:[0,4]*//* byte */
}RF_NV_MIPI_CMD_STRU;

/*****************************************************************************
     : RF_NV_MIPI_BYTE_DATA_STRU
   :
 ASN.1 :
   : MIPI 
*****************************************************************************/
typedef struct
{
    u16              ByteData     :8;   /*  */
    u16              MasterSel    :3;   /* Mipi Master */
    u16              Reserved     :5;   /*  */
}RF_NV_MIPI_BYTE_DATA_STRU;

/*****************************************************************************
     : RF_NV_MIPI_INIT_COMM_STRU
   :
   : mipi
*****************************************************************************/
typedef struct{
    u16                          CmdValidCnt;
    RF_NV_MIPI_CMD_STRU          MipiCmd[4];
    RF_NV_MIPI_BYTE_DATA_STRU    MipiData[5];
}RF_NV_MIPI_04CMD;

typedef struct{
    u16                          CmdValidCnt;
    RF_NV_MIPI_CMD_STRU          MipiCmd[8];
    RF_NV_MIPI_BYTE_DATA_STRU    MipiData[9];
}RF_NV_MIPI_08CMD;

typedef struct{
    u16                          CmdValidCnt;
    RF_NV_MIPI_CMD_STRU          MipiCmd[16];
    RF_NV_MIPI_BYTE_DATA_STRU    MipiData[17];
}RF_NV_MIPI_16CMD;

typedef struct
{
    RF_NV_MIPI_08CMD pa;
    RF_NV_MIPI_08CMD rfswitch;
    RF_NV_MIPI_08CMD tunner;
    RF_NV_MIPI_16CMD usrid;
    RF_NV_MIPI_16CMD reserved;
}RF_NV_MIPI_INIT_COMM_STRU;

/*****************************************************************************
      : RF_NV_MIPI_ALL_CFG
    : mipinv
 NVID       :
*****************************************************************************/
typedef RF_NV_MIPI_16CMD RF_NV_MIPI_MDM_PWROFF_COMM_STRU;

typedef RF_NV_MIPI_16CMD RF_NV_MIPI_ALL_MDM_PWROFF_COMM_STRU;

typedef RF_NV_MIPI_08CMD RF_NV_MIPI_MDM_PWRON_COMM_STRU;

typedef RF_NV_MIPI_08CMD RF_NV_MIPI_MDM_DPM_COMM_STRU;

typedef struct
{
    RF_NV_MIPI_INIT_COMM_STRU            init;
    RF_NV_MIPI_MDM_PWRON_COMM_STRU       pwron [CHANNEL_NUM];/*todo:*/
    RF_NV_MIPI_MDM_PWROFF_COMM_STRU      pwroff[CHANNEL_NUM];
    RF_NV_MIPI_ALL_MDM_PWROFF_COMM_STRU  all_pwroff;

}RF_NV_MIPI_ALL_CFG;

typedef struct
{
    u16                          CmdValidCnt;
    RF_NV_MIPI_CMD_STRU          MipiCmd[4];
    RF_NV_MIPI_BYTE_DATA_STRU    MipiData[5];
}FEMIO_MIPI_CTRL_STRU;

typedef struct
{
	FEMIO_CTRL_MODE       mode;     /**/
	RFFE_GPIO_VALUE_STRU  gpio_ctrl;/*GPIO   */
	FEMIO_MIPI_CTRL_STRU  mipi_ctrl;/*MIPI    */
}FEM_GPIO_MIPI_CTRL_STRU;

typedef struct
{
	FEM_GPIO_MIPI_CTRL_STRU cfg[FEM_IO_CFG_MAX];
}NV_FEM_GPIO_MIPI_CTRL_STRU;

typedef struct
{
    RF_NV_MIPI_04CMD profile[32];
}RF_MIPI_COMM_STRU;

/***************************** MIPI OLD NV END ******************************/


/*****************************************************************************
        :  RF_ANTEN_DETECT_GPIO_STRU
   :  nv
 NV ID               :
*****************************************************************************/
#define RF_ANTEN_NUM 2
#define ANT_DETECT_STUB_GPIO 0XFFFF

typedef struct
{
    u32 anten[RF_ANTEN_NUM];  /* ANTENGPIO */
	u32 div_anten;
} RF_ANTEN_DETECT_GPIO_STRU;

/*****************************************************************************
 		: RF_ANT_SHARE_STRU
 	: 
NV ID			:
*****************************************************************************/
#define RF_SWITCH_INOUT_GPIO_NUM     16
typedef struct
{
	u8 rf_pin    :7;
	u8 gpio_level:1;  /*Range:[0,1]*/
}RF_ANT_SHARE_GPIO_CFG;

typedef struct
{
    u32                     num;	/**/
    RF_ANT_SHARE_GPIO_CFG   gpio[16];   /*gpio*/
}RF_ANT_SHARE_CFG;

typedef struct
{
    RF_ANT_SHARE_CFG inside;
    RF_ANT_SHARE_CFG outside;
}RF_ANT_SHARE_STRU;

/*18000*/
typedef struct
{
    u16 gpio_and_or_en; /*Range:[0,1]*/
    u16 abb_tx_index;   /*Range:[0,1,2,3]*/
}RF_NV_GSM_GPIO_ABBTX_FUNC_SEL;
/*end 18000*/

/*18020*/
typedef struct
{
    u32 abb0_tx_reg;
    u32 abb1_tx_reg;
}RF_NV_ABB_TX_STRU;

typedef struct
{

    u32 gpio_and_or_cfg;
    u32 reserved;
    RF_NV_ABB_TX_STRU  abb_tx_cfg[4];
}RF_NV_GSM_GPIO_ABBTX_CFG;
/*end 18020*/

/*18022\18023*/
typedef struct
{
    u32 enable:1;
    u32 gpio_num:16; /*gpio */
    u32 function:1;  /*, 0gpio,1*/
    u32 level:1;     /*, 0,1*/
  u32 reserved:13; /**/
}RF_GPIO_CONFIG_STRU;

typedef struct
{
    RF_GPIO_CONFIG_STRU profile[32];
}RF_GPIO_COMM_STRU;

typedef enum
{
    OUTER_MODEM_SPDT_SUSPEND = 0,

    RF_GPIO_COMM_MAX
}RF_GPIO_COMM_ENUM;

typedef enum
{
    OUTER_MODEM_TUNER_SUSPEND = 0,
    OUTER_MODEM_TUNER_RESUME = 1,

    RF_MIPI_COMM_MAX
}RF_MIPI_COMM_ENUM;

/*end 18022\ 18023*/

typedef struct
{
    u32 mipi_clk[16];
}RF_MIPI_CLK_SELECT;
/**********************************END RF NV ***********************************/

/*****************************************************************************
     : NV_SECBOOT_ENABLE_FLAG
   : NV_SECBOOT_ENABLE_FLAG ID=50201
*****************************************************************************/
typedef struct
{
    u16 usNVSecBootEnableFlag; /*Range:[0,1]*/
}NV_SECBOOT_ENABLE_FLAG;

/*****************************************************************************
     : NV_FACTORY_INFO_I_STRU
   : NV_FACTORY_INFO_I ID=114
*****************************************************************************/
#define NV_FACTORY_INFO_I_SIZE    (78)
typedef struct
{
    u8 aucFactoryInfo[NV_FACTORY_INFO_I_SIZE];
}NV_FACTORY_INFO_I_STRU;

/*****************************************************************************
     : LED_CONTROL_NV_STRU
   : LED_CONTROL_NV ID=7
*****************************************************************************/
typedef struct
{
    u8   ucLedColor;      /*LED_COLOR*/
    u8   ucTimeLength;    /*100ms*/
}LED_CONTROL_NV_STRU;

/*****************************************************************************
     : LED_CONTROL_STRU
   : LED_CONTROL
*****************************************************************************/
typedef struct
{
    LED_CONTROL_NV_STRU   stLED[10];
}LED_CONTROL_STRU;

/*****************************************************************************
     : LED_CONTROL_STRU_ARRAY
   : 
*****************************************************************************/
typedef struct
{
    LED_CONTROL_STRU    stLED_Control[32];
}LED_CONTROL_STRU_ARRAY;

/*****************************************************************************
     : NV_AT_SHELL_OPEN_FLAG_STRU
   : NV_AT_SHELL_OPEN_FLAG
*****************************************************************************/
typedef struct
{
    u32    NV_AT_SHELL_OPEN_FLAG;
}NV_AT_SHELL_OPEN_FLAG_STRU;

/*****************************************************************************
     : NV_SCI_CFG_STRU
   : NV_SCI_CFG ID=128
*****************************************************************************/
typedef struct
{
    u32 value;
} NV_SCI_CFG_STRU;

/*****************************************************************************
     : nv_wifibs_type
   : nv_wifibs_type
*****************************************************************************/
#define NV_WLSSID_LEN             (33)
#define NV_WLCOUNTRY_CODE_LEN     (5)
#define NV_WLMODE_LEN             (5)
typedef struct
{
    u8   aucwlSsid[NV_WLSSID_LEN];
    u32  ulwlChannel;
    u32  ulwlHide;
    u8   aucwlCountry[NV_WLCOUNTRY_CODE_LEN];
    u8   aucwlMode[NV_WLMODE_LEN];
    u32  ulwlRate;
    u32  ulwlTxPwrPcnt;
    u32  ulwlMaxAssoc;
    u8   ucwlEnbl;
    u32  ulwlFrgThrshld;
    u32  ulwlRtsThrshld;
    u32  ulwlDtmIntvl;
    u32  ulwlBcnIntvl;
    u32  ulwlWme;
    u32  ulwlPamode;
    u32  ulwlIsolate;
    u32  ulwlProtectionmode;
    u32  ulwloffenable;
    u32  ulwlofftime;
    u8   aucwlExtends[12];
}nv_wifibs_type;

/*****************************************************************************
     : RESUME_FLAG_STRU
   : RESUME_FLAG
*****************************************************************************/
typedef struct
{
    u16   usResumeFlag; /*Range:[0, 1]*/
}RESUME_FLAG_STRU;



#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif

