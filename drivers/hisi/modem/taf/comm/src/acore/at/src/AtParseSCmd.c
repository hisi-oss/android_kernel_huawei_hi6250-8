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



/* AT S */
AT_SUB_STATE_STRU AT_S_CMD_NONE_STATE_TAB[]=
{
    /* ATCMD_NONE_STATEatCheckCharSAT_S_CMD_NAME_STATE */
    {    At_CheckCharS    ,    AT_S_CMD_NAME_STATE    },

    /*  */
    {    NULL    ,    AT_BUTT_STATE    },
};

/* AT S */
AT_SUB_STATE_STRU AT_S_CMD_NAME_STATE_TAB[]=
{
    /* AT_S_CMD_NAME_STATEatCheck_numAT_S_CMD_NAME_STATE */
    {    At_CheckDigit    ,    AT_S_CMD_NAME_STATE    },

    /* AT_S_CMD_NAME_STATEatCheck_equAT_S_CMD_SET_STATE */
    {    At_CheckEqu    ,    AT_S_CMD_SET_STATE    },

    /* AT_S_CMD_NAME_STATEatCheck_reqAT_S_CMD_READ_STATE */
    {    At_CheckReq    ,    AT_S_CMD_READ_STATE    },

    /*  */
    {    NULL    ,    AT_BUTT_STATE    },
};


/* AT S */
AT_SUB_STATE_STRU AT_S_CMD_SET_STATE_TAB[]=
{
    /* AT_S_CMD_SET_STATEatCheck_numAT_S_CMD_PARA_STATE */
    {    At_CheckDigit    ,    AT_S_CMD_PARA_STATE    },

    /* AT_S_CMD_SET_STATEatCheck_reqAT_S_CMD_TEST_STATE */
    {    At_CheckReq    ,    AT_S_CMD_TEST_STATE    },

    /*  */
    {    NULL    ,    AT_BUTT_STATE    },
};

/* AT S */
AT_SUB_STATE_STRU AT_S_CMD_PARA_STATE_TAB[]=
{
    /* AT_S_CMD_PARA_STATEatCheck_numAT_S_CMD_PARA_STATE */
    {    At_CheckDigit    ,    AT_S_CMD_PARA_STATE    },

    /*  */
    {    NULL    ,    AT_BUTT_STATE    },
};


/* AT S */
AT_MAIN_STATE_STRU AT_S_CMD_MAIN_STATE_TAB[] =
{
    /* AT_NONE_STATEAT_S_CMD_NONE_STATE_TAB */
    {    AT_NONE_STATE    ,    AT_S_CMD_NONE_STATE_TAB    },

    /* ATCMD_B_CMD_STATEAT_S_CMD_NAME_STATE_TAB */
    {    AT_S_CMD_NAME_STATE    ,    AT_S_CMD_NAME_STATE_TAB    },

    /* AT_S_CMD_SET_STATEAT_S_CMD_SET_STATE_TAB */
    {    AT_S_CMD_SET_STATE    ,    AT_S_CMD_SET_STATE_TAB    },

    /* AT_S_CMD_PARA_STATEAT_S_CMD_PARA_STATE_TAB */
    {    AT_S_CMD_PARA_STATE    ,    AT_S_CMD_PARA_STATE_TAB    },

    /*  */
    {    AT_BUTT_STATE    ,    NULL    },
};

/******************************************************************************
 : atParseSCmd
 : AT,,,,

 :
   pData [in] 
   usLen [in] 

   :
    AT_SUCCESS: 
    AT_ERROR: 

 : TODO: ...
 : TODO: ...
     : /00064416 [2009-08-11]
******************************************************************************/

VOS_UINT32 atParseSCmd( VOS_UINT8 * pData, VOS_UINT16 usLen)
{
    AT_STATE_TYPE_ENUM curr_state = AT_NONE_STATE;  /*   */
    AT_STATE_TYPE_ENUM new_state = AT_NONE_STATE;   /*   */
    VOS_UINT8 *pucCurrPtr = pData;                  /*  */
    VOS_UINT8 *pucCopyPtr = pData;                  /*   */
    VOS_UINT16 usLength = 0;                        /*  */

    /*  */
    while( (usLength++ < usLen) && (g_stATParseCmd.ucParaIndex < AT_MAX_PARA_NUMBER))                      /*  */
    {
        curr_state = new_state;                     /*  */

        /*  */
        new_state = atFindNextMainState(AT_S_CMD_MAIN_STATE_TAB,*pucCurrPtr,curr_state);

        switch (new_state)                        /*  */
        {
        case AT_S_CMD_NAME_STATE:                /*  S*/
            if (curr_state != new_state)          /*  */
            {
                g_stATParseCmd.ucCmdFmtType = AT_BASIC_CMD_TYPE;         /*  */
                g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_CMD_NO_PARA;   /*  */
                pucCopyPtr = pucCurrPtr;             /*  S*/
            }
            break;

        case AT_S_CMD_SET_STATE:                 /* AT S */

            /*  */
            g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;  /* */

            g_stATParseCmd.stCmdName.usCmdNameLen = (VOS_UINT16)(pucCurrPtr - pucCopyPtr);
            if (g_stATParseCmd.stCmdName.usCmdNameLen < sizeof(g_stATParseCmd.stCmdName.aucCmdName))
            {
                atRangeCopy(g_stATParseCmd.stCmdName.aucCmdName,pucCopyPtr,pucCurrPtr);
            }
            else
            {
                return AT_ERROR;                  /*  */
            }
            break;

        case AT_S_CMD_PARA_STATE:               /* AT S */
            if (curr_state != new_state)         /* */
            {
                pucCopyPtr = pucCurrPtr;            /*  S*/
            }
            break;

        case AT_S_CMD_READ_STATE:                  /* AT S */

            /*  */
            g_stATParseCmd.stCmdName.usCmdNameLen = (VOS_UINT16)(pucCurrPtr - pucCopyPtr);
            if (g_stATParseCmd.stCmdName.usCmdNameLen < sizeof(g_stATParseCmd.stCmdName.aucCmdName))
            {
                atRangeCopy(g_stATParseCmd.stCmdName.aucCmdName,pucCopyPtr,pucCurrPtr);
            }
            else
            {
                return AT_ERROR;                  /*  */
            }

            g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_READ_CMD;  /* */

            break;

        case AT_S_CMD_TEST_STATE:                  /* AT S */
            g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_TEST_CMD;  /* */
            break;

        default:
            return AT_ERROR;                  /*  */
        }
        pucCurrPtr++;                             /*  */
    }

    switch(new_state)                           /*  */
    {
    case AT_S_CMD_PARA_STATE:                   /* AT S */

        /*  */
        if (ERR_MSP_SUCCESS != atfwParseSaveParam(pucCopyPtr, (VOS_UINT16)(pucCurrPtr - pucCopyPtr)))
        {
            return AT_ERROR;
        }

        break;

    case AT_S_CMD_NAME_STATE:                   /* AT S*/
        /*  */
        g_stATParseCmd.stCmdName.usCmdNameLen = (VOS_UINT16)(pucCurrPtr - pucCopyPtr);
        if (g_stATParseCmd.stCmdName.usCmdNameLen < sizeof(g_stATParseCmd.stCmdName.aucCmdName))
        {
            atRangeCopy(g_stATParseCmd.stCmdName.aucCmdName,pucCopyPtr,pucCurrPtr);
        }
        else
        {
            return AT_ERROR;                  /*  */
        }
        break;

    case AT_S_CMD_SET_STATE:                         /*  */
    case AT_S_CMD_READ_STATE:                         /*  */
    case AT_S_CMD_TEST_STATE:                         /*  */
        break;

    default:
        return AT_ERROR;                  /*  */
    }
    return AT_SUCCESS;                          /*  */
}



