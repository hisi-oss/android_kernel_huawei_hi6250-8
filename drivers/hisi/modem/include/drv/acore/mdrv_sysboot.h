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

#ifndef __MDRV_ACORE_SYSBOOT_H__
#define __MDRV_ACORE_SYSBOOT_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <mdrv_sysboot_commmon.h>

typedef enum DRV_SHUTDOWN_REASON_tag_s
{
	DRV_SHUTDOWN_POWER_KEY,             /*  Power           */
	DRV_SHUTDOWN_BATTERY_ERROR,         /*                    */
	DRV_SHUTDOWN_LOW_BATTERY,           /*                  */
	DRV_SHUTDOWN_TEMPERATURE_PROTECT,   /*                */
	DRV_SHUTDOWN_CHARGE_REMOVE,         /*  */
	DRV_SHUTDOWN_UPDATE,                /*          */
	DRV_SHUTDOWN_RESET,                 /*                  */
	DRV_SHUTDOWN_BUTT
}DRV_SHUTDOWN_REASON_E;

/*****************************************************************************
*     : mdrv_sysboot_shutdown
*
*   : Modem
*
*   :
*   :
*
*     :
*
*   :
*            1 PS/TAF
*            2 MBB
*              mdrv_sysboot_shutdown
*
*****************************************************************************/
void mdrv_sysboot_shutdown(void);

/*****************************************************************************
*     : mdrv_sysboot_restart
*
*   : Modem
*
*   :
*   :
*
*     :
*
*   :
*            1 phoneModemCMBB
*            2 ccoreacore
*            3 modemsystem_error
*
*****************************************************************************/
void mdrv_sysboot_restart(void);

/*****************************************************************************
*     : mdrv_set_modem_state
*
*   : ModemReadyOff
*
*   : unsigned int state  ModemMODEM_NOT_READY(0), MODEM_READY(1)
*   :
*
*     : 01
*
*   :1 tafModem
*            2 ModemModemModemMODEM_READY
*            Modem Off
*
*****************************************************************************/
int  mdrv_set_modem_state(unsigned int state);

/*****************************************************************************
*     : mdrv_sysboot_register_reset_notify
*
*   : resetmodem C reset
*
*   : const char *pname   9
*             pdrv_reset_cbfun pcbfun  
*             int userdata      
*             int priolevel  emum DRV_RESET_CALLCBFUN_PRIO
*   :
*
*     : 01
*
*   :
*
*****************************************************************************/
typedef int (*pdrv_reset_cbfun)(DRV_RESET_CB_MOMENT_E enparam, int userdata);
int mdrv_sysboot_register_reset_notify(const char *pname, pdrv_reset_cbfun pcbfun, int userdata, int priolevel);

/*****************************************************************************
     : hifireset_regcbfunc
   : HIFI
   : pname9
             pcbfun
             puserdata:
             priolevel: 0-49
   : 
     : 0:  
             -1
*****************************************************************************/
extern int hifireset_regcbfunc(const char *pname, pdrv_reset_cbfun pcbfun, int userdata, int priolevel);
#define DRV_HIFIRESET_REGCBFUNC(pname,pcbfun, userdata, priolevel)\
                hifireset_regcbfunc(pname,pcbfun, userdata, priolevel)

#ifdef __cplusplus
}
#endif
#endif
