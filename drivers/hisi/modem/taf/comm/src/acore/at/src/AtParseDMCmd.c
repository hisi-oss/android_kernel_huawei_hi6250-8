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

#include "AtCheckFunc.h"

#include "msp_errno.h"



/* AT */
AT_SUB_STATE_STRU AT_DM_CMD_NONE_STATE_TAB[]=
{
    /* ATCMD_NONE_STATEatCheckCharDAT_DM_CMD_NAME_STATE */
    {    At_CheckCharD    ,    AT_DM_CMD_NAME_STATE    },

    /*  */
    {    NULL    ,    AT_BUTT_STATE    },
};

/* AT DM */
AT_SUB_STATE_STRU AT_DM_CMD_NAME_STATE_TAB[]=
{
    /* AT_DM_CMD_NAME_STATEAt_CheckCharStarAT_DM_CMD_STAR_STATE */
    {    At_CheckCharStar    ,    AT_DM_CMD_STAR_STATE    },

    /* AT_D_CMD_NAME_STATEAt_CheckCharWellAT_DM_CMD_WELL_STATE */
    {    At_CheckCharWell    ,    AT_DM_CMD_WELL_STATE    },

    /*  */
    {    NULL    ,    AT_BUTT_STATE    },
};

/* AT DM */
AT_SUB_STATE_STRU AT_DM_CMD_CHAR_STATE_TAB[]=
{
    /* AT_DM_CMD_NAME_STATEAt_CheckCharStarAT_DM_CMD_STAR_STATE */
    {    At_CheckCharStar    ,    AT_DM_CMD_STAR_STATE    },

    /* AT_DM_CMD_NAME_STATEAt_CheckCharStarAT_DM_CMD_WELL_STATE */
    {    At_CheckCharWell    ,    AT_DM_CMD_WELL_STATE    },

    /* AT_DM_CMD_NAME_STATEAt_CheckCharStarAT_DM_CMD_NUM_STATE */
    {    At_CheckDmChar    ,    AT_DM_CMD_NUM_STATE    },

    /*  */
    {    NULL    ,    AT_BUTT_STATE    },
};

/* AT */
AT_MAIN_STATE_STRU AT_DM_CMD_MAIN_STATE_TAB[] =
{
    /* AT_NONE_STATEAT_DM_CMD_NONE_STATE_TAB */
    {    AT_NONE_STATE    ,    AT_DM_CMD_NONE_STATE_TAB    },

    /* AT_DM_CMD_NAME_STATEAT_DM_CMD_NAME_STATE_TAB */
    {    AT_DM_CMD_NAME_STATE    ,    AT_DM_CMD_NAME_STATE_TAB    },

    /* AT_DM_CMD_NUM_STATEAT_DM_CMD_CHAR_STATE_TAB */
    {    AT_DM_CMD_NUM_STATE    ,    AT_DM_CMD_CHAR_STATE_TAB    },

    /* AT_DM_CMD_STAR_STATEAT_DM_CMD_CHAR_STATE_TAB */
    {    AT_DM_CMD_STAR_STATE    ,    AT_DM_CMD_CHAR_STATE_TAB    },

    /* AT_DM_CMD_WELL_STATEAT_DM_CMD_CHAR_STATE_TAB */
    {    AT_DM_CMD_WELL_STATE    ,    AT_DM_CMD_CHAR_STATE_TAB    },

    /*  */
    {    AT_BUTT_STATE    ,    NULL    },
};

/******************************************************************************
 : atParseDMCmd
 : AT,,,,
              D*<GPRS_SC>[*[<called_address>][*[<L2P>][*[<cid>]]]]#
              D*<GPRS_SC_IP>[*<cid>[,<cid>]]#
              D**61*+1812555673*11*25#  ---  ,MMI
 :
   pData [in] 
   usLen [in] 

   :
    AT_SUCCESS: 
    AT_FAILURE: 

 : TODO: ...
 : TODO: ...
     : /00064416 [2009-08-11]
******************************************************************************/

VOS_UINT32 atParseDMCmd( VOS_UINT8 * pData, VOS_UINT16 usLen)
{
    AT_STATE_TYPE_ENUM curr_state = AT_NONE_STATE;  /*   */
    AT_STATE_TYPE_ENUM new_state = AT_NONE_STATE;   /*   */
    VOS_UINT8 *pucCurrPtr = pData;                  /*  */
    VOS_UINT8 *pucCopyPtr = pData;                  /*   */
    VOS_UINT16 usLength = 0;                        /*  */

    /* */
    while ( (usLength++ < usLen) && (g_stATParseCmd.ucParaIndex < AT_MAX_PARA_NUMBER))       /*  */
    {
        curr_state = new_state;                  /* */

        /* */
        new_state = atFindNextMainState(AT_DM_CMD_MAIN_STATE_TAB,*pucCurrPtr,curr_state);

        switch (new_state)                        /* */
        {
        case AT_DM_CMD_NAME_STATE:                /* AT DM */
            g_stATParseCmd.ucCmdFmtType = AT_BASIC_CMD_TYPE;     /* */
            g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_CMD_NO_PARA;   /* */
            pucCopyPtr = pucCurrPtr;                 /* DM*/
            break;

        /* gucAtParaIndex */
        case AT_DM_CMD_NUM_STATE:                /* AT DM */
            if (curr_state != new_state)          /* */
            {
                /*  */
                if (ERR_MSP_SUCCESS != atfwParseSaveParam(pucCopyPtr, (VOS_UINT16)(pucCurrPtr - pucCopyPtr)))
                {
                    return AT_FAILURE;
                }

                pucCopyPtr = pucCurrPtr;                /* */
            }
            break;

        case AT_DM_CMD_WELL_STATE:                /* AT DM# */
        case AT_DM_CMD_STAR_STATE:                /* AT DM* */
            if (AT_DM_CMD_NAME_STATE == curr_state)
            {
                g_stATParseCmd.stCmdName.usCmdNameLen = (VOS_UINT16)(pucCurrPtr - pucCopyPtr);
                if (g_stATParseCmd.stCmdName.usCmdNameLen < sizeof(g_stATParseCmd.stCmdName.aucCmdName))
                {
                    atRangeCopy(g_stATParseCmd.stCmdName.aucCmdName,pucCopyPtr,pucCurrPtr);
                }
                else
                {
                    return AT_FAILURE;                  /*  */
                }
                pucCopyPtr = pucCurrPtr;             /* */
            }
            else
            {
                /*  */
                if(ERR_MSP_SUCCESS != atfwParseSaveParam(pucCopyPtr, (VOS_UINT16)(pucCurrPtr - pucCopyPtr)))
                {
                    return AT_FAILURE;
                }

                pucCopyPtr = pucCurrPtr;                /* */
            }
            break;

        default:
            return AT_FAILURE;                  /*  */
        }

        pucCurrPtr++;                             /* */
    }

    switch (new_state)                           /* */
    {
    case AT_DM_CMD_WELL_STATE:                   /* AT DM# */
        break;

    default:
        return AT_FAILURE;                      /* */
    }
    
    return AT_SUCCESS;                          /* */
}



