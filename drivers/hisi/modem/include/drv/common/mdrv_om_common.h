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

#ifndef _MDRV_OM_COMMON_H_
#define _MDRV_OM_COMMON_H_

#ifdef _cplusplus
extern "C"
{
#endif

/* field idididid */
/* APfieldOM_AP_FIELD_ENDCPfieldOM_CP_FIELD_END */
enum OM_FIELD_ID_ENUM
{
    OM_AP_FIELD_BEGIN   = (0x01200000),
    OM_AP_OSA           = (OM_AP_FIELD_BEGIN),
    OM_AP_DIAG          = (OM_AP_FIELD_BEGIN + 1),
    OM_AP_FIELD_END,

    OM_CP_FIELD_BEGIN   = (0x02200000),
    OM_CP_OSA           = (OM_CP_FIELD_BEGIN),
    OM_CP_MSP_SLEEP     = (OM_CP_FIELD_BEGIN + 1),
    OM_CP_TLPS          = (OM_CP_FIELD_BEGIN + 2),
    OM_CP_FTM_MNTN      = (OM_CP_FIELD_BEGIN + 3),  
    OM_CP_GUAS          = (OM_CP_FIELD_BEGIN + 4),
    OM_CP_DIAG          = (OM_CP_FIELD_BEGIN + 5),  
    OM_CP_GUNAS         = (OM_CP_FIELD_BEGIN + 6),
    OM_CP_CPROC         = (OM_CP_FIELD_BEGIN + 7),
    OM_CP_CAS           = (OM_CP_FIELD_BEGIN + 8),
    OM_CP_CNAS          = (OM_CP_FIELD_BEGIN + 9),
    OM_CP_MSCC          = (OM_CP_FIELD_BEGIN + 10),
    OM_CP_CTTF          = (OM_CP_FIELD_BEGIN + 11),
    OM_CP_USIMM0        = (OM_CP_FIELD_BEGIN + 12),
    OM_CP_USIMM1        = (OM_CP_FIELD_BEGIN + 13),
	OM_CP_TLPS1         = (OM_CP_FIELD_BEGIN + 14),
    OM_CP_FIELD_END,
};
enum
{
    DUMP_OUT_VOICE = 0,
    DUMP_IN_VOICE = 1,
    DUMP_VOICE_BUTT,
};
typedef int dump_handle;
typedef void (*dump_hook)(void);

/*****************************************************************************
 *     : mdrv_om_system_error
 *   : 
 *   : modId:   
 *             arg1:    1
 *             arg2:    2
 *             arg3:    3
 *                       bufdumpdump
 *                       dumpfield
 *             arg3Length:  argbufmax_len(v74kv81k)
 *                       max_lenmax_len
 *   : 
 *     : 
 *****************************************************************************/
void mdrv_om_system_error(int modId, int arg1, int arg2, char * arg3, int arg3Length);

/*****************************************************************************
 *     : mdrv_om_register_field
 *   : 
 *             system_errordumpfield
 *   : field_id :   bufferfield id
 *             field_name:  field
 *             virt_addr:   dump
 *             phy_addr:    
 *             length:      buffer
 *             version:     buffer
 *
 *   : NULL:  buf
 *
 *     : 
 *****************************************************************************/
unsigned char* mdrv_om_register_field(unsigned int field_id, char * field_name, void * virt_addr,
                            void * phy_addr, unsigned int length, unsigned short version);

/*****************************************************************************
 *     : mdrv_om_get_field_addr
 *   : field_iddump
 *
 *   : field_id: mdrv_om_register_fielddumpID
 *
 *   : 
 *
 *     : >0   field
 *             0    
 *
 *****************************************************************************/
unsigned char * mdrv_om_get_field_addr(unsigned int field_id);

/*****************************************************************************
 *     : mdrv_om_get_field_phy_addr
 *   : field_iddump
 *
 *   : field_id: mdrv_om_register_fielddumpID
 *
 *   : 
 *
 *     : >0   field
 *             0    
 *
 *****************************************************************************/
unsigned char * mdrv_om_get_field_phy_addr(unsigned int field_id);

/*****************************************************************************
 *     : mdrv_om_register_callback
 *   : DUMPdump
 * system_error
 *
 *   : name :   
 *             pFunc:   
 *
 *   : 
 *
 *        : >0  
 *        -1, DUMP_HANDLE_INVALID  
 *
 *****************************************************************************/
dump_handle mdrv_om_register_callback(char * name, dump_hook pFunc);

/*****************************************************************************
      : mdrv_om_unregister_callback
    : DUMP

    : handle :   mdrv_om_register_callback

    : 

         : 0  
  -1   

 *****************************************************************************/
 int mdrv_om_unregister_callback(dump_handle handle);


/*****************************************************************************
      : mdrv_om_set_hsoflag
    : DIAGHSO

    : flag :  1HSO0HSO

    : 

         : 

 *****************************************************************************/
void mdrv_om_set_hsoflag(unsigned int flag);

/*****************************************************************************
 *     : mdrv_om_set_sysview_swt
 *   : HSOsysview
 *
 *   : set_type :  
 *             set_swt: 10 
 *             period:  
 *   : 
 *
 *     :  0  
 *        -1   
 *****************************************************************************/
unsigned int mdrv_om_set_sysview_swt(unsigned int set_type,unsigned int set_swt,unsigned int period);

/*****************************************************************************
 *     : mdrv_om_get_alltaskinfo
 *   : ID
 *
 *   : p_task_stru:  
 *             param_len:  
 *
 *   : 
 *
 *        :  0    
 *                 -1   
 *
 *****************************************************************************/
unsigned int mdrv_om_get_alltaskinfo(void *p_task_stru,unsigned int param_len);

 /**************************************************************************
  *     : mdrv_om_get_rootfs
  *   : 
  *   : data
  *             len: data
  *   :
  *                 : 0:  
  *                        -1 
  ****************************************************************************/
int mdrv_om_get_rootfs(char *data, unsigned int len);

#ifdef _cplusplus
}
#endif
#endif


