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
#ifndef _BSP_IPC_H_
#define _BSP_IPC_H_
#ifdef __ASSEMBLY__
#include <bsp_memmap.h>

/* c->m send ipc_int  addr & bit  */
//#define  PM_C2M_IPC_ADDR       (HI_IPCM_REGBASE_ADDR+IPC_CPU_RAW_INT_M3)
//#define  PM_C2M_IPC_BIT        (0x1<<17)
/* a->m send ipc_int  addr & bit  */
/*#define  PM_A2M_IPC_ADDR       (HI_IPCM_REGBASE_ADDR+IPC_CPU_RAW_INT_M3)*/
//#define  PM_A2M_IPC_BIT        (0x1<<16)

#else

#include <product_config.h>
#include <osl_spinlock.h>
#include <osl_common.h>
#include <mdrv_ipc.h>
#include <mdrv_ipc_enum.h>
#ifdef __cplusplus
extern "C" {
#endif
typedef void  (*voidfuncptr)(u32);
#define IPC_ERR_MODEM_RESETING 1
#define MODEM_RESET_HWLOCK_ID 10
#define  IPC_CPU_RAW_INT_M3   0x420

struct ipc_entry
{
 	voidfuncptr routine;
	u32	arg;
} ;

#define INTSRC_NUM                     32
#define SEMSRC_NUM                      32
extern spinlock_t ipcm_lock[IPC_SEM_BUTTOM];

#ifdef CONFIG_MODULE_IPC
/*****************************************************************************
*        : bsp_ipc_init
*
*   : IPC
*
*   : 
*   : 
*
*        : 
*
*   : 201319   lixiaojie     
                          
*****************************************************************************/
int bsp_ipc_init(void);
/*****************************************************************************
*        : bsp_ipc_sem_create
*
*   : 
*
*   :   u32 u32SignalNum 

*   : 
*
*        : OK&ERROR
*
*   : 201319 lixiaojie 
*****************************************************************************/
s32 bsp_ipc_sem_create(u32 u32SignalNum);
/*****************************************************************************
*         : bsp_ipc_sem_delete
*
*   : 
*
*   :   u32 u32SignalNum 

*   : 
*
*        : OK&ERROR
*
*   : 201319 lixiaojie 
*****************************************************************************/

s32 bsp_ipc_sem_delete(u32 u32SignalNum);
/*****************************************************************************
*        :bsp_ipc_int_enable
*
*   : 
*
*   :   u32 ulLvl 031  
*   : 
*
*        : OK&ERROR
*
*   : 201318    lixiaojie 
*****************************************************************************/

s32 bsp_ipc_int_enable(IPC_INT_LEV_E ulLvl);
/*****************************************************************************
 *         : ipc_int_disable
 *
 *   : 
 *
 *   : u32 ulLvl 031   
 *   : 
 *
 *         : OK&ERROR
 *
 *   :  201318 lixiaojie  
 *****************************************************************************/

s32 bsp_ipc_int_disable(IPC_INT_LEV_E ulLvl);
/*****************************************************************************
 *        : bsp_ipc_int_connect
 *
 *   : 
 *
 *   : u32 ulLvl 031 
                              routine 
 *                            u32 parameter      
 *   : 
 *
 *         : OK&ERROR
 *
 *   : 201319 lixiaojie
 *****************************************************************************/

s32 bsp_ipc_int_connect(IPC_INT_LEV_E ulLvl, voidfuncptr routine, u32 parameter);
/*****************************************************************************
 *        : bsp_ipc_int_disconnect
 *
 *   : 
 *
 *   : u32 ulLvl 031 
 *                           voidfuncptr routine 
 *                           u32 parameter      
 *   : 
 *
 *         : OK&ERROR
 *
 *   : 201319 lixiaojie 
 *****************************************************************************/   

s32 bsp_ipc_int_disconnect(IPC_INT_LEV_E ulLvl,voidfuncptr routine, u32 parameter);
/*****************************************************************************
*         : bsp_ipc_int_send
*
*   : 
*
*   : ipc_int_core enDstore core
                             u32 ulLvl 031  
*   : 
*
*         :  OK&ERROR
*
*   :  201319 lixiaojie 
*****************************************************************************/

s32 bsp_ipc_int_send(IPC_INT_CORE_E enDstCore, IPC_INT_LEV_E ulLvl);
/*****************************************************************************
 *        : bsp_ipc_sem_take
 *
 *   : 
 *
 *   : u32SignalNum ID
                                s32timeout  ,ticktick10ms
 *   : 
 *
 *         : OK&ERROR
 *
 *   : 201319 lixiaojie 
 *****************************************************************************/

s32 bsp_ipc_sem_take(u32 u32SignalNum,s32 s32timeout);
/*****************************************************************************
 *        : bsp_ipc_sem_give
 *
 *   : 
 *
 *   : u32SignalNum 
 					    s32timeout  10ms
 *   : 
 *
 *         :OK&&ERROR
 *
 *   : 201319 lixiaojie 
 *****************************************************************************/

s32 bsp_ipc_sem_give(u32 u32SignalNum);
/*****************************************************************************
*        : bsp_ipc_spin_lock
*
*   : ,
			bsp_ipc_spin_lock_irqsave
*
*   : u32SignalNum 
*   : 
*
*         :ERROR&OK
*
*   :  201318 lixiaojie 
*****************************************************************************/

s32 bsp_ipc_spin_lock (u32 u32SignalNum);

/*****************************************************************************
*        : bsp_ipc_spin_trylock
*
*   : ,
*
*   : u32SignalNum 
*   : 
*
*         :ERROR&OK
*
*   :  20141111 huangxianke 
*****************************************************************************/
s32 bsp_ipc_spin_trylock (u32 u32SignalNum);

/*****************************************************************************
*         : bsp_ipc_spin_unlock
*
*   : bsp_ipc_spin_lock
			bsp_ipc_spin_unlock_irqrestore
*
*   : u32SignalNum  
*   : 
*
*         : OK&ERROR
*
*   :  201319 lixiaojie
*****************************************************************************/
s32 bsp_ipc_spin_unlock (u32 u32SignalNum);

/*****************************************************************************
*     : bsp_ipc_spin_lock_timeout_irqsave
*
*   : 
*
*   : u32SignalNum:
              TimeoutMs:
			  flags:
					: bsp_ipc_spin_unlock_irqrestore
						  bsp_ipc_spin_unlock_irqrestore
						  spin_lock_irqsave
*   : 
*
*     : MDRV_ERROR&MDRV_OK
*
*   : 2016226 nieluhua 
*****************************************************************************/
s32 bsp_ipc_spin_lock_timeout_irqsave(unsigned int u32SignalNum, unsigned int TimeoutMs, unsigned long *flags);

/*****************************************************************************
*        : bsp_ipc_spin_lock_irqsave
*
*   : 
*
*   : u32SignalNum 
						flags:bsp_ipc_spin_unlock_irqrestore
						
						spin_lock_irqsave
*   : 
*
*         :ERROR&OK
*
*   :  201358 lixiaojie 
*****************************************************************************/

#define bsp_ipc_spin_lock_irqsave(u32SignalNum,flags)  \
	do{spin_lock_irqsave(&ipcm_lock[u32SignalNum], flags);(void)bsp_ipc_spin_lock(u32SignalNum);}while(0)
/*****************************************************************************
*        : bsp_ipc_spin_unlock_irqrestore
*
*   :
*
*   : u32SignalNum 
					flags:bsp_ipc_spin_lock_irqsave
						
						spin_unlock_irqrestore
*   : 
*
*         :ERROR&OK
*
*   :  201358 lixiaojie 
*****************************************************************************/

#define bsp_ipc_spin_unlock_irqrestore(u32SignalNum,flags) \
	do{(void)bsp_ipc_spin_unlock(u32SignalNum);spin_unlock_irqrestore(&ipcm_lock[u32SignalNum], flags);}while(0)
#else
static inline s32 bsp_ipc_init(void) {return 0;}
static inline s32 bsp_ipc_sem_create(u32 u32SignalNum) {return 0;}
static inline s32 bsp_ipc_sem_delete(u32 u32SignalNum) {return 0;}
static inline s32 bsp_ipc_int_enable(IPC_INT_LEV_E ulLvl) {return 0;}
static inline s32 bsp_ipc_int_disable(IPC_INT_LEV_E ulLvl) {return 0;}
static inline s32 bsp_ipc_int_connect(IPC_INT_LEV_E ulLvl, voidfuncptr routine, u32 parameter) {return 0;}
static inline s32 bsp_ipc_int_disconnect(IPC_INT_LEV_E ulLvl,voidfuncptr routine, u32 parameter) {return 0;}
static inline s32 bsp_ipc_int_send(IPC_INT_CORE_E enDstCore, IPC_INT_LEV_E ulLvl) {return 0;}
static inline s32 bsp_ipc_sem_take(u32 u32SignalNum,s32 s32timeout) {return 0;}
static inline s32 bsp_ipc_sem_give(u32 u32SignalNum) {return 0;}
static inline s32 bsp_ipc_spin_lock (u32 u32SignalNum) {return 0;}
static inline s32 bsp_ipc_spin_trylock(u32 u32SignalNum) {return 0;}
static inline s32 bsp_ipc_spin_unlock (u32 u32SignalNum) {return 0;}
static inline s32 bsp_ipc_spin_lock_timeout_irqsave(unsigned int u32SignalNum, unsigned int TimeoutMs, unsigned long *flags) {return 0;}
#define bsp_ipc_spin_lock_irqsave(u32SignalNum,flags)  \
       do{flags = flags;}while(0)
#define bsp_ipc_spin_unlock_irqrestore(u32SignalNum,flags) \
       do{flags = flags;}while(0)

static inline void bsp_ipc_suspend(void){return ;}

static inline void bsp_ipc_resume(void){return ;}
#endif

typedef s32 (*read_cb_func)(u32 channel_id , u32 len, void* context);
#ifdef CONFIG_IPC_MSG
/*****************************************************************************
*     : bsp_ipc_msg_register
*
*   : IPC
*
*   : 
*
*   : 
*
*     :
*
*   : 2016610   n00261894
*****************************************************************************/
int bsp_ipc_msg_register(read_cb_func read_cb, void *read_context);

/*****************************************************************************
*     : bsp_ipc_msg_read
*
*   : IPC
*
*   : buf
*
*   : 
*
*     :
*
*   : 2016610   n00261894
*****************************************************************************/
int bsp_ipc_msg_read(u8 *buf, u32 buf_len);

/*****************************************************************************
*     : bsp_ipc_msg_write
*
*   : IPC255
*
*   : buf
*
*   : 
*
*     :
*
*   : 2016610   n00261894
*****************************************************************************/
int bsp_ipc_msg_write(u8 *buf, u32 buf_len);

#else
#ifndef UNUSED
#define UNUSED(a) (a=a)
#endif
static inline int __attribute__ ((unused))bsp_ipc_msg_register(read_cb_func read_cb, void *read_context)
{
	UNUSED(read_cb);
	UNUSED(read_context);
	return -1;
}
static inline int __attribute__ ((unused))bsp_ipc_msg_read(u8 *buf, u32 buf_len)
{
	UNUSED(buf);
	UNUSED(buf_len);
	return -1;
}
static inline int __attribute__ ((unused))bsp_ipc_msg_write(u8 *buf, u32 buf_len)
{
	UNUSED(buf);
	UNUSED(buf_len);
	return -1;
}
#endif

/*****************************************************************************
*        : bsp_int_send_info
*
*   :
*
*   : 
*   : 
*
*         :
*
*   :  2013510 lixiaojie 
*****************************************************************************/

void bsp_int_send_info(void);
#ifdef __CMSIS_RTOS
/*****************************************************************************
*   	: bsp_ipc_suspend
*
* 	:IPC
*
* 	: 
* 	: 
*
*   		:
*
* 	:  2013614 lixiaojie 
*****************************************************************************/
void bsp_ipc_suspend(void);
/*****************************************************************************
*   	: bsp_ipc_resume
*
* 	:IPC
*
* 	: 
* 	: 
*
*   		:0: success
						 -1:fail
*
* 	:  2013614 lixiaojie 
*****************************************************************************/
void bsp_ipc_resume(void);
#endif

#ifdef __cplusplus
}
#endif

#endif /*#ifdef __ASSEMBLY__*/

#endif /* end #define _BSP_IPC_H_*/
