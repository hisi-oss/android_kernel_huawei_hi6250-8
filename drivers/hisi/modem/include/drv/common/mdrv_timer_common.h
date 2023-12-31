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

#ifndef __MDRV_TIMER_COMMON_H__
#define __MDRV_TIMER_COMMON_H__

#ifdef __cplusplus
extern "C"
{
#endif

    typedef enum
    {
        TIMER_ONCE_COUNT = 0,        /*  */
        TIMER_PERIOD_COUNT,          /*  */
        TIMER_FREERUN_COUNT,         /*  */
        TIMER_COUNT_BUTT
    }DRV_TIMER_MODE_E;

    typedef enum
    {
        TIMER_UNIT_MS = 0,           /* 0ms */
        TIMER_UNIT_US,               /* 1us */
        TIMER_UNIT_NONE,             /* 21load  */
        TIMER_UNIT_BUTT
    }DRV_TIMER_UNIT_E;




	typedef enum
	{
		TIMER_CCPU_DSP_DRX_PROT_ID	,	/*v9r1     liujing*/
		ACORE_SOFTTIMER_ID			,	/*A core timer id                lixiaojie*/
		CCORE_SOFTTIMER_ID			,	/*C core timer id                lixiaojie*/
		ACORE_WDT_TIMER_ID			,	/*A CORE                           yangqiang*/
		CCORE_WDT_TIMER_ID			,	/*C CORE                           yangqiang*/
		TIME_STAMP_ID				,	/*P531A core C CORE M3,fastboot V7R2BBPlixiaojie*/
		USB_TIMER_ID				,	/*A CORE    V7R2 USB                lvhui*/
		CCORE_SOFTTIMER_NOWAKE_ID	,	/*C core timer                 lixiaojie*/
		ACORE_SOFTTIMER_NOWAKE_ID	,	/*A core timer                 lixiaojie*/
		TIMER_DSP_TIMER2_ID			,	/*DSP                                 liujing*/
		TIMER_MCPU_ID				,	/*M3                                lixiaojie*/
		TIMER_HIFI_TIMER2_ID		,	/*hifi                              fuying*/
		TIMER_UDELAY_TIMER_ID		,	/*cudelayfastboot              lixiaojie*/
		CCORE_SYSTEM_TIMER_ID		,	/*C Core                        luting*/
		ACORE_SYSTEM_TIMER_ID		,	/*A CORE                        luting*/
		ACORE_SOURCE_TIMER_ID		,	/*A CORE                         luting */
		TIMER_ACPU_CPUVIEW_ID		,	/*A CORE CPU VIEW                      duxiaopeng*/
		TIMER_CCPU_CPUVIEW_ID		,	/*C CORE CPU VIEW                     duxiaopeng*/
		TIMER_HIFI_TIMER1_ID		,	/*hifi                             fuying*/
		TIMER_ACPU_OSA_ID			,	/*A CORE                        cuijunqiang*/
		TIMER_CCPU_OSA_ID			,	/*C CORE                        cuijunqiang*/
		TIMER_CCPU_DRX1_STABLE_ID	,	/*C CORE tcxoxujingcui            */
		TIMER_DSP_TIMER1_ID			,	/*DSP                             liujing*/
		TIMER_CCPU_OM_TCXO_ID		,	/*vos timer, XUCHENG   */
		TIMER_CCPU_DRX_TIMER_ID		,	/*,cuijunqiang          */
		TIMER_ACPU_OM_TCXO_ID		,	/*vos timer, xucheng    */
		TIMER_DSP_SWITCH_DELAY_ID	,	/*VOLTE sleep dalay optimize for dsp ,cuijunqiang*/
		TIMER_CCPU_G1PHY_DRX_ID		,	/*V9R1V7R2K3V3:luoqingquan*/
		TIMER_CCPU_AUX_ID			,	/*v8 */
		TIMER_CCPU_MSP_ID			,	/*v8 */
		TIMER_CCPU_APP_ID			,	/*v8 */
		TIMER_ALL_SLICE_ID			,	/*v8 */
		TIMER_CCPU_DFS_ID 			,	/*v8 */
		TIMER_CCPU_DRX_STAMP_ID		,	/*v8 */
		TIMER_MCU_TIMER1_ID			,	/*v8 */
		TIMER_MCU_TIMER2_ID			,	/*v8 */
		TIMER_ACPU_FREE_RUN			,	/*v8 */
		TIMER_ACPU_IDLE_ID			,	/*v8 */
		TIMER_GUPHY_TIMER3_ID		,	/*GUPHY,linqingen,38*/
		TIMER_GUPHY_TIMER4_ID		,	/*GUPHY,linqingen,39*/
		TIMER_CCPU_MPERF_ID			,
		TIMER_CCPU_MPERF1_ID			,
		TIMER_ID_MAX
	} DRV_TIMER_ID;

    /*****************************************************************************
     *      : mdrv_timer_debug_register
     *    : timerOM
     *    : usrClkId:  ID
     *              routine:  
     *                 arg:   
     *      : void
     *    :
     *    :
     *
     *        :
     *      1.       : 201456
     *               : lixiaojie 00227190
     *            : 
     *
     ******************************************************************************/
    void mdrv_timer_debug_register(unsigned int timer_id, FUNCPTR_1 routinue, int arg);

    /*****************************************************************************
     *      : mdrv_timer_start
     *    : 
     *    : usrClkId:  ID,0~19
     *              routine:   
     *                  arg:   
     *           timerValue:   
     *                 mode:   .
     *             unitType:   0ms1us21load
     *
     *    : 
     *      : int
     *
     *        :
     *      1.       : 2012719
     *               :  00179452
     *           : 
     *
     ******************************************************************************/
    int mdrv_timer_start(unsigned int usrClkId, FUNCPTR_1 routine, int arg,
            unsigned int timerValue, DRV_TIMER_MODE_E mode,  DRV_TIMER_UNIT_E unitType);

    /*****************************************************************************
     *      : mdrv_timer_stop
     *    : 
     *    : usrClkId:ID,0~19
     *    : 
     *      : int
     *
     *        :
     *      1.       : 2012719
     *               :  00179452
     *           : 
     *
     ******************************************************************************/
    int mdrv_timer_stop(unsigned int usrClkId);

    /*****************************************************************************
     *      : mdrv_timer_get_rest_time
     *    : 
     *    : usrClkId:ID,0~19
     *              unitType
     *              pRestTime
     *    : 
     *      : int
     *
     *    :
     *      1.       : 2012719
     *               :  00179452
     *           : 
     *
     ******************************************************************************/
    int mdrv_timer_get_rest_time(unsigned int usrClkId, unsigned int unitType, unsigned int * pRestTime);

    /*****************************************************************************
     *    : BSP_BBPGetCurTime
     *    : BBPOAM 
     *    : void
     *    :
     *           pulLow32bitValue:    
     *           pulHigh32bitValue:    32bit
     *    : int
     ******************************************************************************/
    int mdrv_timer_get_accuracy_timestamp(unsigned int *pulHigh32bitValue, unsigned int *pulLow32bitValue);

    /************************************************************************
     *  FUNCTION
     *       mdrv_timer_get_normal_timestamp
     * DESCRIPTION
     *       GetSliceValue
     * INPUTS
     *       NONE
     * OUTPUTS
     *       NONE
             
     *************************************************************************/
    unsigned int mdrv_timer_get_normal_timestamp(void);
	/************************************************************************
     *  FUNCTION
     *       mdrv_timer_get_hrt_timestamp
     * DESCRIPTION
     *       GetHrtSliceValue
     * INPUTS
     *       NONE
     * OUTPUTS
     *       NONE
             0.5us
             ,(lixiaojie\gebaizhang\xiajun)
     *************************************************************************/
	unsigned int mdrv_timer_get_hrt_timestamp(void);

#ifdef __cplusplus
}
#endif
#endif
