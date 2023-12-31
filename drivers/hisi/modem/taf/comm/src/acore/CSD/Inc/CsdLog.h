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

#ifndef __CSDLOG_H__
#define __CSDLOG_H__

/*****************************************************************************
  1 
*****************************************************************************/
#include "vos.h"

#include "PsCommonDef.h"
/* Added by wx270776 for OM, 2015-6-27, begin */
#include "AtMntn.h"
/* Added by wx270776 for OM, 2015-6-27, end */


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 
*****************************************************************************/
/*================================================*/
/*  */
/*================================================*/
#define CSD_MEM_FAIL()\
        TAF_LOG(ACPU_PID_CSD, 0, PS_LOG_LEVEL_ERROR, "CSD Mem Operation Failed!");
#define CSD_MSG_FAIL()\
        TAF_LOG(ACPU_PID_CSD, 0, PS_LOG_LEVEL_ERROR, "CSD Msg Opration Failed!");
#define CSD_TIMER_FAIL()\
        TAF_LOG(ACPU_PID_CSD, 0, PS_LOG_LEVEL_ERROR, "CSD Timer Opration Failed!");

/*================================================*/
/*  */
/*================================================*/
#ifndef SUBMOD_NULL
#define    SUBMOD_NULL                                                  (0)
#endif

#define CSD_INFO_LOG(Mod, String)\
        TAF_LOG ( (Mod), SUBMOD_NULL,  PS_LOG_LEVEL_INFO, (String) )
#define CSD_INFO_LOG1(Mod, String,Para1)\
        TAF_LOG1 ( (Mod), SUBMOD_NULL, PS_LOG_LEVEL_INFO, (String), (VOS_INT32)(Para1) )
#define CSD_INFO_LOG2(Mod, String,Para1,Para2)\
        TAF_LOG2 ( (Mod), SUBMOD_NULL, PS_LOG_LEVEL_INFO, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2) )
#define CSD_INFO_LOG3(Mod, String,Para1,Para2,Para3)\
        TAF_LOG3 ( (Mod), SUBMOD_NULL, PS_LOG_LEVEL_INFO, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3) )
#define CSD_INFO_LOG4(Mod, String,Para1,Para2,Para3,Para4)\
        TAF_LOG4 ( (Mod), SUBMOD_NULL, PS_LOG_LEVEL_INFO, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3), (VOS_INT32)(Para4) )

#define CSD_NORMAL_LOG(Mod, String)\
        TAF_LOG ( (Mod), SUBMOD_NULL,  PS_LOG_LEVEL_NORMAL, (String) )
#define CSD_NORMAL_LOG1(Mod, String,Para1)\
        TAF_LOG1 ( (Mod), SUBMOD_NULL, PS_LOG_LEVEL_NORMAL, (String), (VOS_INT32)(Para1) )
#define CSD_NORMAL_LOG2(Mod, String,Para1,Para2)\
        TAF_LOG2 ( (Mod), SUBMOD_NULL, PS_LOG_LEVEL_NORMAL, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2) )
#define CSD_NORMAL_LOG3(Mod, String,Para1,Para2,Para3)\
        TAF_LOG3 ( (Mod), SUBMOD_NULL, PS_LOG_LEVEL_NORMAL, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3) )
#define CSD_NORMAL_LOG4(Mod, String,Para1,Para2,Para3,Para4)\
        TAF_LOG4 ( (Mod), SUBMOD_NULL, PS_LOG_LEVEL_NORMAL, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3), (VOS_INT32)(Para4) )

#define CSD_WARNING_LOG(Mod, String)\
        TAF_LOG ( (Mod), SUBMOD_NULL,  PS_LOG_LEVEL_WARNING, (String) )
#define CSD_WARNING_LOG1(Mod, String,Para1)\
        TAF_LOG1 ( (Mod), SUBMOD_NULL, PS_LOG_LEVEL_WARNING, (String), (VOS_INT32)(Para1) )
#define CSD_WARNING_LOG2(Mod, String,Para1,Para2)\
        TAF_LOG2 ( (Mod), SUBMOD_NULL, PS_LOG_LEVEL_WARNING, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2) )
#define CSD_WARNING_LOG3(Mod, String,Para1,Para2,Para3)\
        TAF_LOG3 ( (Mod), SUBMOD_NULL, PS_LOG_LEVEL_WARNING, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3) )
#define CSD_WARNING_LOG4(Mod, String,Para1,Para2,Para3,Para4)\
        TAF_LOG4 ( (Mod), SUBMOD_NULL, PS_LOG_LEVEL_WARNING, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3), (VOS_INT32)(Para4) )

#define CSD_ERROR_LOG(Mod, String)\
        TAF_LOG ( (Mod), SUBMOD_NULL,  PS_LOG_LEVEL_ERROR, (String) )
#define CSD_ERROR_LOG1(Mod, String,Para1)\
        TAF_LOG1 ( (Mod), SUBMOD_NULL, PS_LOG_LEVEL_ERROR, (String), (VOS_INT32)(Para1) )
#define CSD_ERROR_LOG2(Mod, String,Para1,Para2)\
        TAF_LOG2 ( (Mod), SUBMOD_NULL, PS_LOG_LEVEL_ERROR, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2) )
#define CSD_ERROR_LOG3(Mod, String,Para1,Para2,Para3)\
        TAF_LOG3 ( (Mod), SUBMOD_NULL, PS_LOG_LEVEL_ERROR, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3) )
#define CSD_ERROR_LOG4(Mod, String,Para1,Para2,Para3,Para4)\
        TAF_LOG4 ( (Mod), SUBMOD_NULL, PS_LOG_LEVEL_ERROR, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3), (VOS_INT32)(Para4) )

/*****************************************************************************
  3 
*****************************************************************************/


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

#endif /* end of CsdLog.h */
