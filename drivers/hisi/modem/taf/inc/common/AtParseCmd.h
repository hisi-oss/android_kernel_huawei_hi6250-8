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

#ifndef _ATPARSECMD_H_
#define _ATPARSECMD_H_


/*****************************************************************************
  1 
*****************************************************************************/
/*#include "ATCmdProc.h" */
#include "TafTypeDef.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)
/*****************************************************************************
  2 
*****************************************************************************/

#define AT_CHECK_BASE_HEX                       (16)
#define AT_CHECK_BASE_OCT                       (8)
#define AT_CHECK_BASE_DEC                       (10)

/*******************************************************************************
  3 
*******************************************************************************/
typedef enum
{
    AT_NONE_STATE,                      /*  */

    AT_B_CMD_NAME_STATE,            /* AT */
    AT_B_CMD_PARA_STATE,            /* AT */

    AT_D_CMD_NAME_STATE,                /* AT D */
    AT_D_CMD_DIGIT_STATE,               /* AT D */
    AT_D_CMD_CHAR_STATE,                /* AT D */
    AT_D_CMD_RIGHT_ARROW_STATE,         /* AT D */
    AT_D_CMD_DIALSTRING_STATE,          /* AT D */
    AT_D_CMD_SEMICOLON_STATE,           /* AT D */
    AT_D_CMD_CHAR_G_STATE,              /* AT DG */
    AT_D_CMD_CHAR_I_STATE,              /* AT DI */
    AT_D_CMD_LEFT_QUOT_STATE,           /* AT D */
    AT_D_CMD_RIGHT_QUOT_STATE,          /* AT D */

    AT_DM_CMD_NAME_STATE,
    AT_DM_CMD_STAR_STATE,              /* AT D* */
    AT_DM_CMD_WELL_STATE,               /* AT D# */
    AT_DM_CMD_NUM_STATE,               /* AT D# */

    AT_S_CMD_NAME_STATE,             /* AT S */
    AT_S_CMD_SET_STATE,              /* AT S */
    AT_S_CMD_READ_STATE,             /* AT S */
    AT_S_CMD_TEST_STATE,             /* AT S */
    AT_S_CMD_PARA_STATE,             /* AT S */

    AT_E_CMD_NAME_STATE,               /* AT */
    AT_E_CMD_SET_STATE,                /* AT */
    AT_E_CMD_TEST_STATE,               /* AT */
    AT_E_CMD_READ_STATE,               /* AT */
    AT_E_CMD_PARA_STATE,               /* AT */
    AT_E_CMD_COLON_STATE,              /* AT */
    AT_E_CMD_LEFT_QUOT_STATE,          /* AT */
    AT_E_CMD_RIGHT_QUOT_STATE,         /* AT */

    AT_PARA_LEFT_BRACKET_STATE,      /*  */
    AT_PARA_NUM_STATE,               /*  */
    AT_PARA_LETTER_STATE,            /*  */
    AT_PARA_NUM_COLON_STATE,         /*  */
    AT_PARA_NUM_SUB_STATE,           /*  */
    AT_PARA_NUM_SUB_COLON_STATE,     /*  */
    AT_PARA_QUOT_COLON_STATE,        /*  */
    AT_PARA_RIGHT_BRACKET_STATE,     /*  */
    AT_PARA_SUB_STATE,               /*  */
    AT_PARA_LEFT_QUOT_STATE,         /*  */
    AT_PARA_RIGHT_QUOT_STATE,        /*  */
    AT_PARA_COLON_STATE,             /*  */
    AT_PARA_ZERO_STATE,              /* 0 */
    AT_PARA_ZERO_SUB_STATE,          /* 0 */
    AT_PARA_HEX_STATE,               /* , 0x0X */
    AT_PARA_HEX_SUB_STATE,           /*  */
    AT_PARA_HEX_NUM_STATE,           /*  */
    AT_PARA_HEX_NUM_SUB_STATE,       /*  */
    AT_PARA_NO_QUOT_LETTER_STATE,    /*  */

    AT_W_CMD_F_STATE,            /* AT& */
    AT_W_CMD_NAME_STATE,            /* ATW */
    AT_W_CMD_PARA_STATE,            /* ATW */

    AT_BUTT_STATE                    /*  */
}AT_STATE_TYPE_ENUM;

/*****************************************************************************
  4 
*****************************************************************************/

/*****************************************************************************
  5 
*****************************************************************************/
/*HEADER */

/*****************************************************************************
  6 
*****************************************************************************/


/*****************************************************************************
  7 STRUCT
*****************************************************************************/
/* */
typedef TAF_UINT32 (*pATChkCharFuncType)(TAF_UINT8);

/* */
/*lint -e958 -e959 :l60609;:64bit*/
typedef struct
{
    pATChkCharFuncType  pFuncName;                      /*    ,next_state*/
    AT_STATE_TYPE_ENUM next_state;                    /*     */
}AT_SUB_STATE_STRU;
/*lint +e958 +e959 :l60609;:64bit*/

/* */
/*lint -e958 -e959 :l60609;:64bit*/
typedef struct
{
    AT_STATE_TYPE_ENUM curr_state;                    /**/
    AT_SUB_STATE_STRU  *pSubStateTab;             /**/
}AT_MAIN_STATE_STRU;
/*lint +e958 +e959 :l60609;:64bit*/

/*****************************************************************************
  8 UNION
*****************************************************************************/


/*****************************************************************************
  9 OTHERS
*****************************************************************************/

/*****************************************************************************
  10 
*****************************************************************************/

/*lint -esym(752,At_RangeCopy)*/
TAF_VOID At_RangeCopy(TAF_UINT8 *pucDst,TAF_UINT8 * pucBegain, TAF_UINT8 * pucEnd);

/*lint -esym(752,At_RangeToU32)*/
TAF_UINT32 At_RangeToU32(TAF_UINT8 * pucBegain, TAF_UINT8 * pucEnd);


/*  */
/*lint -esym(752,atRangeCopy)*/
VOS_VOID atRangeCopy(VOS_UINT8 *pucDst,VOS_UINT8 * pucBegain, VOS_UINT8 * pucEnd);

/*  */
/*lint -esym(752,atRangeToU32)*/
VOS_UINT32 atRangeToU32(VOS_UINT8 * pucBegain, VOS_UINT8 * pucEnd);

/*lint -esym(752,atFindNextSubState)*/
AT_STATE_TYPE_ENUM atFindNextSubState(AT_SUB_STATE_STRU *pSubStateTab,VOS_UINT8 ucInputChar);

/*lint -esym(752,atFindNextMainState)*/
AT_STATE_TYPE_ENUM atFindNextMainState(AT_MAIN_STATE_STRU *pMainStateTab,VOS_UINT8 ucInputChar,AT_STATE_TYPE_ENUM InputState);

/*lint -esym(752,atAuc2ul)*/
extern VOS_UINT32 atAuc2ul(VOS_UINT8 *nptr,VOS_UINT16 usLen,VOS_UINT32 *pRtn);

/*lint -esym(752,At_ul2Auc)*/
VOS_VOID At_ul2Auc(VOS_UINT32 ulValue,TAF_UINT16 usLen,VOS_UINT8 *pRtn);


#if ((TAF_OS_VER == TAF_WIN32) || (TAF_OS_VER == TAF_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of MapsTemplate.h*/


