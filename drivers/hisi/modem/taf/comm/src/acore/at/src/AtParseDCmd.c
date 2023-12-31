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

#include "at_common.h"


/* AT */
AT_SUB_STATE_STRU AT_D_CMD_NONE_STATE_TAB[]=
{
    /* ATCMD_NONE_STATEatCheckCharDAT_D_CMD_NAME_STATE */
    {    At_CheckCharD    ,    AT_D_CMD_NAME_STATE    },

    /*  */
    {    NULL    ,    AT_BUTT_STATE    },
};

/* AT D */
AT_SUB_STATE_STRU AT_D_CMD_NAME_STATE_TAB[]=
{
    /* AT_D_CMD_NAME_STATEAt_CheckCharRightArrowAT_D_CMD_RIGHT_ARROW_STATE */
    {    At_CheckCharRightArrow    ,    AT_D_CMD_RIGHT_ARROW_STATE    },

    /* AT_D_CMD_NAME_STATEatCheckDailStringAT_D_CMD_DIALSTRING_STATE */
    {    At_CheckDialNum    ,    AT_D_CMD_DIALSTRING_STATE    },

    /*  */
    {    NULL    ,    AT_BUTT_STATE    },
};

/* AT D */
AT_SUB_STATE_STRU AT_D_CMD_DIALSTRING_STATE_TAB[]=
{
    /* AT_D_CMD_DIALSTRING_STATEatCheckDailStringAT_D_CMD_DIALSTRING_STATE */
    {    At_CheckDialNum    ,    AT_D_CMD_DIALSTRING_STATE    },

    /* AT_D_CMD_DIALSTRING_STATEAt_CheckCharIAT_D_CMD_CHAR_I_STATE */
    {    At_CheckCharI    ,    AT_D_CMD_CHAR_I_STATE    },

    /* AT_D_CMD_DIALSTRING_STATEAt_CheckCharGAT_D_CMD_CHAR_G_STATE */
    {    At_CheckCharG    ,    AT_D_CMD_CHAR_G_STATE    },

    /* AT_D_CMD_DIALSTRING_STATEAt_CheckSemicolonAT_D_CMD_SEMICOLON_STATE */
    {    At_CheckSemicolon    ,    AT_D_CMD_SEMICOLON_STATE    },

    /*  */
    {    NULL    ,    AT_BUTT_STATE    },
};

/* AT DI */
AT_SUB_STATE_STRU AT_D_CMD_CHAR_I_STATE_TAB[]=
{
    /* AT_D_CMD_CHAR_I_STATEAt_CheckCharGAT_D_CMD_CHAR_G_STATE */
    {    At_CheckCharG    ,    AT_D_CMD_CHAR_G_STATE    },

    /* AT_D_CMD_CHAR_I_STATEAt_CheckSemicolonAT_D_CMD_SEMICOLON_STATE */
    {    At_CheckSemicolon    ,    AT_D_CMD_SEMICOLON_STATE    },

    /*  */
    {    NULL    ,    AT_BUTT_STATE    },
};

/* AT DG */
AT_SUB_STATE_STRU AT_D_CMD_CHAR_G_STATE_TAB[]=
{
    /* AT_D_CMD_CHAR_G_STATEAt_CheckSemicolonAT_D_CMD_SEMICOLON_STATE */
    {    At_CheckSemicolon    ,    AT_D_CMD_SEMICOLON_STATE    },

    /*  */
    {    NULL    ,    AT_BUTT_STATE    },
};

/* AT D */
AT_SUB_STATE_STRU AT_D_CMD_RIGHT_ARROW_STATE_TAB[]=
{
    /* AT_D_CMD_RIGHT_ARROW_STATEatCheck_quotAT_D_CMD_LEFT_QUOT_STATE */
    {    At_CheckQuot    ,    AT_D_CMD_LEFT_QUOT_STATE    },

    /* AT_D_CMD_RIGHT_ARROW_STATEatCheck_numAT_D_CMD_DIGIT_STATE */
    {    At_CheckDigit    ,    AT_D_CMD_DIGIT_STATE    },

    /* AT_D_CMD_RIGHT_ARROW_STATEAt_CheckUpLetterAT_D_CMD_CHAR_STATE */
    {    At_CheckUpLetter    ,    AT_D_CMD_CHAR_STATE    },

    /*  */
    {    NULL    ,    AT_BUTT_STATE    },
};

/* AT D */
AT_SUB_STATE_STRU AT_D_CMD_CHAR_STATE_TAB[]=
{
    /* AT_D_CMD_CHAR_STATEatCheckCharStrAT_D_CMD_CHAR_STATE */
    {    At_CheckUpLetter    ,    AT_D_CMD_CHAR_STATE    },

    /* AT_D_CMD_CHAR_STATEatCheck_quotAT_D_CMD_RIGHT_QUOT_STATE */
    {    At_CheckDigit    ,    AT_D_CMD_DIGIT_STATE    },

    /*  */
    {    NULL    ,    AT_BUTT_STATE    },
};

/* AT D */
AT_SUB_STATE_STRU AT_D_CMD_LEFT_QUOT_STATE_TAB[]=
{
    /* AT_D_CMD_LEFT_QUOT_STATEatCheckCharStrAT_D_CMD_LEFT_QUOT_STATE */
    {    At_CheckNoQuot    ,    AT_D_CMD_LEFT_QUOT_STATE    },

    /* AT_D_CMD_LEFT_QUOT_STATEatCheck_quotAT_D_CMD_RIGHT_QUOT_STATE */
    {    At_CheckQuot    ,    AT_D_CMD_RIGHT_QUOT_STATE    },

    /*  */
    {    NULL    ,    AT_BUTT_STATE    },
};

/* AT D */
AT_SUB_STATE_STRU AT_D_CMD_RIGHT_QUOT_STATE_TAB[]=
{
    /* AT_D_CMD_RIGHT_ARROW_STATEatCheck_numAT_D_CMD_DIGIT_STATE */
    {    At_CheckDigit    ,    AT_D_CMD_DIGIT_STATE    },

    /* AT_D_CMD_DIALSTRING_STATEAt_CheckCharIAT_D_CMD_CHAR_I_STATE */
    {    At_CheckCharI    ,    AT_D_CMD_CHAR_I_STATE    },

    /* AT_D_CMD_DIALSTRING_STATEAt_CheckCharGAT_D_CMD_CHAR_G_STATE */
    {    At_CheckCharG    ,    AT_D_CMD_CHAR_G_STATE    },

    /* AT_D_CMD_DIALSTRING_STATEAt_CheckSemicolonAT_D_CMD_SEMICOLON_STATE */
    {    At_CheckSemicolon    ,    AT_D_CMD_SEMICOLON_STATE    },

    /*  */
    {    NULL    ,    AT_BUTT_STATE    },
};



/* AT */
AT_MAIN_STATE_STRU AT_D_CMD_MAIN_STATE_TAB[] =
{
    /* AT_NONE_STATEAT_D_CMD_NONE_STATE_TAB */
    {    AT_NONE_STATE    ,    AT_D_CMD_NONE_STATE_TAB    },

    /* AT_D_CMD_NAME_STATEAT_D_CMD_NAME_STATE_TAB */
    {    AT_D_CMD_NAME_STATE    ,    AT_D_CMD_NAME_STATE_TAB    },

    /* AT_D_CMD_DIALSTRING_STATEAT_D_CMD_DIALSTRING_STATE_TAB */
    {    AT_D_CMD_DIALSTRING_STATE    ,    AT_D_CMD_DIALSTRING_STATE_TAB    },

    /* AT_D_CMD_CHAR_I_STATEAT_D_CMD_CHAR_I_STATE_TAB */
    {    AT_D_CMD_CHAR_I_STATE    ,    AT_D_CMD_CHAR_I_STATE_TAB    },

    /* AT_D_CMD_CHAR_G_STATEAT_D_CMD_CHAR_G_STATE_TAB */
    {    AT_D_CMD_CHAR_G_STATE    ,    AT_D_CMD_CHAR_G_STATE_TAB    },

    /* AT_D_CMD_CHAR_STATEAT_D_CMD_CHAR_STATE_TAB */
    {    AT_D_CMD_CHAR_STATE    ,    AT_D_CMD_CHAR_STATE_TAB    },

    /* AT_D_CMD_RIGHT_ARROW_STATEAT_D_CMD_RIGHT_ARROW_STATE_TAB */
    {    AT_D_CMD_RIGHT_ARROW_STATE    ,    AT_D_CMD_RIGHT_ARROW_STATE_TAB    },

    /* AT_D_CMD_LEFT_QUOT_STATEAT_D_CMD_LEFT_QUOT_STATE_TAB */
    {    AT_D_CMD_LEFT_QUOT_STATE    ,    AT_D_CMD_LEFT_QUOT_STATE_TAB    },

    /* AT_D_CMD_RIGHT_QUOT_STATEAT_D_CMD_RIGHT_QUOT_STATE_TAB */
    {    AT_D_CMD_RIGHT_QUOT_STATE    ,    AT_D_CMD_RIGHT_QUOT_STATE_TAB    },

    /* AT_D_CMD_DIGIT_STATEAT_D_CMD_DIGIT_STATE_TAB */
    {    AT_D_CMD_DIGIT_STATE    ,    AT_D_CMD_RIGHT_QUOT_STATE_TAB    },

    /*  */
    {    AT_BUTT_STATE    ,    NULL    },
};

/*******************************************************************************
 : atParseDCmd
 : AT,,,,
            D[<dial_string>][I][G][;]
            D>mem<n>[I][G][;]
            D><n>[I][G][;]
            D><name>[I][G][;]

 :
   pData [in/out] 
   usLen [in] 

   :
    AT_SUCCESS: 
    AT_FAILURE: 

 : TODO: ...
 : TODO: ...
     : /00064416 [2009-08-11]
******************************************************************************/

static VOS_UINT32 atParseDCmd( VOS_UINT8 * pData, VOS_UINT16 usLen)
{
    AT_STATE_TYPE_ENUM curr_state = AT_NONE_STATE;  /*   */
    AT_STATE_TYPE_ENUM new_state = AT_NONE_STATE;   /*   */
    VOS_UINT8 *pucCurrPtr = pData;                  /*  */
    VOS_UINT8 *pucCopyPtr = pData;                  /*   */
    VOS_UINT16 usLength = 0;                        /*  */

    /* */
    while( (usLength++ < usLen) && (g_stATParseCmd.ucParaIndex < AT_MAX_PARA_NUMBER))                     /*  */
    {
        curr_state = new_state;                  /* */

        /* */
        new_state = atFindNextMainState(AT_D_CMD_MAIN_STATE_TAB,*pucCurrPtr,curr_state);

        switch(new_state)                        /* */
        {
        case AT_D_CMD_NAME_STATE:                /* AT D */
            g_stATParseCmd.ucCmdFmtType = AT_BASIC_CMD_TYPE;     /* */
            g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_CMD_NO_PARA;   /* */
            pucCopyPtr = pucCurrPtr;                 /* D*/
            break;

        case AT_D_CMD_RIGHT_ARROW_STATE:         /* AT D */
        case AT_D_CMD_DIALSTRING_STATE:          /* AT D */
            if(curr_state != new_state)          /* */
            {
                g_stATParseCmd.stCmdName.usCmdNameLen = (VOS_UINT16)(pucCurrPtr - pucCopyPtr);
                if(g_stATParseCmd.stCmdName.usCmdNameLen < sizeof(g_stATParseCmd.stCmdName.aucCmdName))
                {
                    atRangeCopy(g_stATParseCmd.stCmdName.aucCmdName,pucCopyPtr,pucCurrPtr);
                }
                else
                {
                    return AT_FAILURE;                  /*  */
                }
                pucCopyPtr = pucCurrPtr;             /* */
            }
            break;

        case AT_D_CMD_DIGIT_STATE:               /* AT D */
        case AT_D_CMD_LEFT_QUOT_STATE:           /* AT D */
        case AT_D_CMD_CHAR_STATE:
            if(curr_state != new_state)          /* */
            {
                /*  */
                if(ERR_MSP_SUCCESS != atfwParseSaveParam(pucCopyPtr, (VOS_UINT16)(pucCurrPtr - pucCopyPtr)))
                {
                    return AT_FAILURE;
                }

                pucCopyPtr = pucCurrPtr;                /* */
            }
            break;

        case AT_D_CMD_CHAR_I_STATE:              /* AT DI */
        case AT_D_CMD_CHAR_G_STATE:              /* AT DG */
        case AT_D_CMD_SEMICOLON_STATE:           /* AT D */
            /*  */
            if(ERR_MSP_SUCCESS != atfwParseSaveParam(pucCopyPtr, (VOS_UINT16)(pucCurrPtr - pucCopyPtr)))
            {
                return AT_FAILURE;
            }

            pucCopyPtr = pucCurrPtr;                /* */
            break;

        case AT_BUTT_STATE:                     /*  */
            return AT_FAILURE;                  /*  */

        default:
            break;
        }
        pucCurrPtr++;                             /* */
    }

    switch(new_state)                           /* */
    {
    case AT_D_CMD_SEMICOLON_STATE:              /* AT D */
        break;

    case AT_D_CMD_DIALSTRING_STATE:             /* AT D */
    case AT_D_CMD_DIGIT_STATE:                  /* AT D */
    case AT_D_CMD_RIGHT_QUOT_STATE:             /* AT D */
    case AT_D_CMD_CHAR_G_STATE:                 /* AT DG */
    case AT_D_CMD_CHAR_I_STATE:                 /* AT DI */
        /*  */
        if(ERR_MSP_SUCCESS != atfwParseSaveParam(pucCopyPtr, (VOS_UINT16)(pucCurrPtr - pucCopyPtr)))
        {
            return AT_FAILURE;
        }

        break;

    default:
        return AT_FAILURE;                      /* */
    }
    return AT_SUCCESS;                          /* */
}

/******************************************************************************
     : atCdataParseDCmd
   : #777
   : VOS_UINT8                          *pData
             VOS_UINT16                          usLen
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 20150827
           : y00314741
       : 

******************************************************************************/
VOS_VOID atCdataParseDCmd(
    VOS_UINT8                          *pData,
    VOS_UINT16                          usLen
)
{
    g_stATParseCmd.ucCmdFmtType = AT_BASIC_CMD_TYPE;            /* */
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_CMD_NO_PARA;   /* */

    /* D*/
    g_stATParseCmd.stCmdName.usCmdNameLen = 1;
    g_stATParseCmd.stCmdName.aucCmdName[0] = *pData;
}



/******************************************************************************
 : atScanDcmdModifier
 : D

 :
   pData [in/out] 
   pLen [in/out] 

   :
    TODO: ...

 : TODO: ...
 : TODO: ...
     : /00064416 [2009-08-11]
******************************************************************************/
static VOS_VOID atScanDcmdModifier( VOS_UINT8 *pData, VOS_UINT16 *pLen)
{
    VOS_UINT16 usChkLen  = 0;
    VOS_UINT16 usLen     = 0;
    VOS_UINT8  *pWrite   = pData;
    VOS_UINT8  *pRead    = pData;

    /*  */
    while ( usChkLen++ < *pLen )
    {
        /*',','T','P','!','W','@'*/
        if((',' != *pRead) && ('T' != *pRead) && ('P' != *pRead)
            && ('!' != *pRead) && ('W' != *pRead) && ('@' != *pRead))
        {
            *pWrite++ = *pRead;
            usLen++;
        }
        pRead++;
    }

    *pLen  =  usLen;
    return;
}

/******************************************************************************
 : atScanDmcmdModifier
 : Dm

 :
   pData [in/out] 
   pLen [in/out] 

   :
    TODO: ...

 : TODO: ...
 : TODO: ...
     : /00064416 [2009-08-11]

  2.       : 20131012
           : l00198894
       : DTS2013100901373:ATDPPP
******************************************************************************/
static VOS_VOID atScanDmcmdModifier( VOS_UINT8 *pData, VOS_UINT16 *pLen)
{
    VOS_UINT16 usLen     = 0;
    VOS_UINT8  *pWrite   = VOS_NULL_PTR;
    VOS_UINT8  *pRead    = VOS_NULL_PTR;
    VOS_UINT8  *pTmp     = VOS_NULL_PTR;
    VOS_UINT8  *pDataTmp = VOS_NULL_PTR;
    VOS_UINT8  aucStr[]  = "*99**PPP";
    VOS_UINT16 usStrLen  = 0;

    pDataTmp = (VOS_UINT8*)AT_MALLOC(*pLen + 1);
    if (VOS_NULL_PTR == pDataTmp)
    {
        vos_printf("atScanDmcmdModifier(): AT_MALLOC Failed!\n");
        return;
    }

    atRangeCopy(pDataTmp, pData, (pData + *pLen));

    /*  */
    pDataTmp[*pLen] = 0;

    pRead   = pDataTmp;
    pWrite  = pDataTmp;

    pTmp = (VOS_UINT8*)AT_STRSTR((VOS_CHAR *)pDataTmp,(VOS_CHAR *)aucStr);
    if(NULL != pTmp)
    {
        usStrLen = (VOS_UINT16)AT_STRLEN((VOS_CHAR *)aucStr);
        /*  */
        while ( pRead < pTmp )
        {
            /*',','T','P','!','W','@'*/
            if((',' != *pRead) && ('T' != *pRead) && ('P' != *pRead)
                && ('!' != *pRead) && ('W' != *pRead) && ('@' != *pRead))
            {
                *pWrite++ = *pRead;
                usLen++;
            }
            pRead++;
        }
        while( pRead < (pTmp+usStrLen) )
        {
            *pWrite++ = *pRead++;
            usLen++;
        }
        while( pRead < (pDataTmp+(*pLen)) )
        {
            /*',','T','P','!','W','@'*/
            if((',' != *pRead) && ('T' != *pRead) && ('P' != *pRead)
                && ('!' != *pRead) && ('W' != *pRead) && ('@' != *pRead))
            {
                *pWrite++ = *pRead;
                usLen++;
            }
            pRead++;
        }
    }
    else
    {
        /*  */
        while ( pRead < (pDataTmp+(*pLen)) )
        {
            /*',','T','P','!','W','@'*/
            if((',' != *pRead) && ('T' != *pRead) && ('P' != *pRead)
                && ('!' != *pRead) && ('W' != *pRead) && ('@' != *pRead))
            {
                *pWrite++ = *pRead;
                usLen++;
            }
            pRead++;
        }
    }

    atRangeCopy(pData, pDataTmp, (pDataTmp + *pLen));

    *pLen = usLen;

    AT_FREE(pDataTmp);
    return;
}

/******************************************************************************
 : ScanQuateChar
 : (D)

 :
   pData [in/out] 
   usLen [in] 

     : /00064416 [2011-04-01]
******************************************************************************/
static VOS_UINT32 ScanQuateChar( VOS_UINT8 * pData, VOS_UINT16 * pusLen)
{
    VOS_UINT8 *pWrite = pData;
    VOS_UINT8 *pRead  = pData;
    VOS_UINT16 usChkLen = 0;
    VOS_UINT16 usLen    = 0;

    if(0 == *pusLen)
    {
        return AT_FAILURE;
    }

    while(usChkLen++ < *pusLen)
    {
        /*  */
        if('"' != *pRead)
        {
            *pWrite++ = *pRead;
            usLen++;
        }
        pRead++;
    }
    *pusLen = usLen;

    return AT_SUCCESS;
}


/******************************************************************************
 : ParseDCmdPreProc
 : D

 :
   pData [in/out] 
   usLen [in] 

     : /00064416 [2011-04-01]

  2.       : 20121116
           : f62575
      : DTS2012111409590: ATD38944425#123i50

  3.       : 20131012
           : l00198894
       : DTS2013100901373:ATDPPP

******************************************************************************/
VOS_UINT32 ParseDCmdPreProc( VOS_UINT8 * pData, VOS_UINT16 usLen)
{
    VOS_UINT16 usTmpLen = usLen;
    VOS_UINT8* pTmp = pData;
    VOS_UINT32 ulResult = AT_FAILURE;

    /* LINUX(ATDT"*99#") */
    ScanQuateChar(pTmp, &usTmpLen);

    {
        if(AT_SUCCESS == At_CheckCharWell(pTmp[usTmpLen - 1]))      /* # */
        {
            atScanDmcmdModifier(pTmp,&usTmpLen);                    /*  */

            /* gstATCmdName.usCmdNameLen
            */
            if(ERR_MSP_SUCCESS != atfwParseSaveParam(pTmp, usTmpLen))
            {
                return AT_CME_DIAL_STRING_TOO_LONG;
            }

            ulResult = atParseDMCmd(pTmp,usTmpLen);                /*  */
            if(ulResult == AT_FAILURE)
            {
                return AT_ERROR;
            }
        }
        /* #777,"#777" */
        else if (AT_CheckStrStartWith(pTmp, usTmpLen, (VOS_UINT8 *)"D#777", AT_CDATA_DIAL_777_LEN+1))
        {
            ulResult = AT_SaveCdataDialParam(pTmp, usTmpLen);

            if(ulResult == AT_FAILURE)
            {
                return AT_ERROR;
            }

            atCdataParseDCmd(pTmp,usTmpLen);
        }
        else
        {
            if(AT_FAILURE == atCheckRightArrowStr(pTmp,usTmpLen))
            {
                atScanDcmdModifier(pTmp,&usTmpLen);                        /*  */
            }

            /* gstATCmdName.usCmdNameLen
            */
            if(ERR_MSP_SUCCESS != atfwParseSaveParam(pTmp, usTmpLen))
            {
                return AT_CME_DIAL_STRING_TOO_LONG;
            }

            ulResult = atParseDCmd(pTmp,usTmpLen);                       /* D */

            if(ulResult == AT_FAILURE)
            {
                return AT_ERROR;
            }

        }
    }

    return ulResult;
}



