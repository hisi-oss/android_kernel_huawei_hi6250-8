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



#ifndef __CTTF_ERR_LOG_CFG_H__
#define __CTTF_ERR_LOG_CFG_H__

/*****************************************************************************
  1 
*****************************************************************************/
#include "vos.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 
*****************************************************************************/


/*****************************************************************************
  3 
*****************************************************************************/
/*******************************************************************************
 * Name        : CTTF_ERR_LOG_ALM_ID_ENUM_UINT8
 * Description : 1x&Hrpd Err Log alarm id
*******************************************************************************/
enum CTTF_ERR_LOG_ALM_ID_ENUM
{
    CTTF_ERR_LOG_ALM_ID_1X              = 0x01,
    CTTF_ERR_LOG_ALM_ID_HRPD            = 0x02,

    CTTF_ERR_LOG_ALM_ID_BUTT
};
typedef  VOS_UINT8 CTTF_ERR_LOG_ALM_ID_ENUM_UINT8;

/*******************************************************************************
 * Name        : PPP_ERR_LOG_ALM_ID_ENUM_UINT8
 * Description : PPPAlarmId
*******************************************************************************/
enum PPP_ERR_LOG_ALM_ID_ENUM
{
    PPP_ERR_LOG_ALM_ID_RESOURCE_INFO    = 0x01,

    PPP_ERR_LOG_ALM_ID_BUTT
};
typedef VOS_UINT8 PPP_ERR_LOG_ALM_ID_ENUM_UINT8;

/*******************************************************************************
 Name    : RRM_ERR_LOG_ALM_ID_ENUM_UINT8
 Description  : RRMAlarmId
*******************************************************************************/
enum RRM_ERR_LOG_ALM_ID_ENUM
{
    RRM_ERR_LOG_ALM_ID_RESOURCE_INFO           = 0x01,
    RRM_ERR_LOG_ALM_ID_CDMA_RPT_RESOURCE_INFO  = 0x02,
    RRM_ERR_LOG_ALM_ID_HIGH_PRI_TASK_INFO      = 0x03,
    RRM_ERR_LOG_ALM_ID_CDMA_HIGH_PRI_TASK_INFO = 0x04,

    RRM_ERR_LOG_ALM_ID_BUTT
};
typedef VOS_UINT8 RRM_ERR_LOG_ALM_ID_ENUM_UINT8;

/*****************************************************************************
  4 
*****************************************************************************/


/*****************************************************************************
  5 
*****************************************************************************/


/*****************************************************************************
  6 
*****************************************************************************/


/*****************************************************************************
  7 STRUCT
*****************************************************************************/


/*****************************************************************************
  8 UNION
*****************************************************************************/


/*****************************************************************************
  9 OTHERS
*****************************************************************************/


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

#endif /* end of cttferrlogcfg.h */


