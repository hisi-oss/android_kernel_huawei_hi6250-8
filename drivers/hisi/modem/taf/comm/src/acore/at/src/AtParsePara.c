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



#define    THIS_FILE_ID        PS_FILE_ID_AT_PARSEPARA_C


/*  */
AT_SUB_STATE_STRU AT_PARA_NONE_STATE_TAB[]=
{
    /* AT_PARA_NONE_STATEatCheckLeftBracketAT_PARA_LEFT_BRACKET_STATE */
    {    At_CheckLeftBracket    ,    AT_PARA_LEFT_BRACKET_STATE    },

    /*  */
    {    NULL    ,    AT_BUTT_STATE    },
};

/*  */
AT_SUB_STATE_STRU AT_PARA_LEFT_BRACKET_STATE_TAB[]=
{
    /* AT_PARA_LEFT_BRACKET_STATEatCheckZeroAT_PARA_ZERO_STATE */
    {At_CheckChar0,   AT_PARA_ZERO_STATE},

    /* AT_PARA_LEFT_BRACKET_STATEatCheckDigitAT_PARA_NUM_STATE */
    {At_CheckDigit,  AT_PARA_NUM_STATE},

    /* AT_PARA_LEFT_BRACKET_STATEat_NoQuotLetterAT_PARA_NO_QUOT_LETTER_STATE */
    {atNoQuotLetter, AT_PARA_NO_QUOT_LETTER_STATE},

    /* AT_PARA_LEFT_BRACKET_STATEatCheckLetterAT_PARA_LETTER_STATE */
    {At_CheckLetter, AT_PARA_LETTER_STATE},

    /* AT_PARA_LEFT_BRACKET_STATEatCheckQuotAT_PARA_LEFT_QUOT_STATE */
    {At_CheckQuot,   AT_PARA_LEFT_QUOT_STATE},

    /*  */
    {NULL,           AT_BUTT_STATE},
};

/*  */
AT_SUB_STATE_STRU AT_PARA_NUM_STATE_TAB[]=
{
    /* AT_PARA_NUM_STATEatCheckDigitAT_PARA_NUM_STATE */
    {   At_CheckDigit   ,   AT_PARA_NUM_STATE    },

    /* AT_PARA_NUM_STATEatCheckColonAT_PARA_NUM_COLON_STATE */
    {   atCheckComma ,   AT_PARA_NUM_COLON_STATE  },

    /* AT_PARA_NUM_STATEatCheckRightBracketAT_PARA_RIGHT_BRACKET_STATE */
    {   At_CheckRightBracket  , AT_PARA_RIGHT_BRACKET_STATE   },

    /* AT_PARA_NUM_STATEatCheckCharSubAT_PARA_SUB_STATE */
    {   At_CheckCharSub   ,   AT_PARA_SUB_STATE    },

    /*  */
    {    NULL    ,    AT_BUTT_STATE    },
};

/*  */
AT_SUB_STATE_STRU AT_PARA_SUB_STATE_TAB[]=
{
    /* AT_PARA_SUB_STATEatCheckZeroAT_PARA_ZERO_SUB_STATE */
    {At_CheckChar0,  AT_PARA_ZERO_SUB_STATE},

    /* AT_PARA_SUB_STATEatCheckDigitAT_PARA_NUM_SUB_STATE */
    {At_CheckDigit, AT_PARA_NUM_SUB_STATE},

    /*  */
    {NULL,          AT_BUTT_STATE},
};

/*  */
AT_SUB_STATE_STRU AT_PARA_NUM_SUB_STATE_TAB[]=
{
    /* AT_PARA_NUM_SUB_STATEatCheckDigitAT_PARA_NUM_SUB_STATE */
    {   At_CheckDigit   ,   AT_PARA_NUM_SUB_STATE    },

    /* AT_PARA_NUM_SUB_STATEatCheckColonAT_PARA_NUM_SUB_COLON_STATE */
    {   atCheckComma ,   AT_PARA_NUM_SUB_COLON_STATE  },

    /* AT_PARA_NUM_SUB_STATEatCheckRightBracketAT_PARA_RIGHT_BRACKET_STATE */
    {   At_CheckRightBracket  ,   AT_PARA_RIGHT_BRACKET_STATE   },

    /*  */
    {    NULL    ,    AT_BUTT_STATE    },
};

/*  */
AT_SUB_STATE_STRU AT_PARA_NUM_SUB_COLON_STATE_TAB[]=
{
    /* AT_PARA_NUM_SUB_COLON_STATEatCheckZeroAT_PARA_ZERO_STATE */
    {At_CheckChar0,  AT_PARA_ZERO_STATE},

    /* AT_PARA_NUM_SUB_COLON_STATEatCheckDigitAT_PARA_NUM_STATE */
    {At_CheckDigit, AT_PARA_NUM_STATE},

    /*  */
    {NULL,          AT_BUTT_STATE},
};

/*  */
AT_SUB_STATE_STRU AT_PARA_RIGHT_BRACKET_STATE_TAB[]=
{
    /* AT_PARA_RIGHT_BRACKET_STATEatCheckColonAT_PARA_COLON_STATE */
    {   atCheckComma ,   AT_PARA_COLON_STATE  },

    /*  */
    {    NULL    ,    AT_BUTT_STATE    },
};

/*  */
AT_SUB_STATE_STRU AT_PARA_COLON_STATE_TAB[]=
{
    /* AT_PARA_COLON_STATEatCheckLeftBracketAT_PARA_LEFT_BRACKET_STATE */
    {   At_CheckLeftBracket  ,   AT_PARA_LEFT_BRACKET_STATE   },

    /*  */
    {    NULL    ,    AT_BUTT_STATE    },
};

/*  */
AT_SUB_STATE_STRU AT_PARA_LEFT_QUOT_STATE_TAB[]=
{
    /* AT_PARA_LEFT_QUOT_STATEatCheckNoQuotAT_PARA_LEFT_QUOT_STATE */
    {   At_CheckNoQuot   ,   AT_PARA_LEFT_QUOT_STATE },

    /* AT_PARA_LEFT_QUOT_STATEatCheckQuotAT_PARA_RIGHT_QUOT_STATE */
    {   At_CheckQuot ,    AT_PARA_RIGHT_QUOT_STATE },

    /*  */
    {    NULL    ,    AT_BUTT_STATE    },
};

/*  */
AT_SUB_STATE_STRU AT_PARA_RIGHT_QUOT_STATE_TAB[]=
{
    /* AT_PARA_RIGHT_QUOT_STATEatCheckRightBracketAT_PARA_RIGHT_BRACKET_STATE */
    {   At_CheckRightBracket  ,   AT_PARA_RIGHT_BRACKET_STATE   },

    /* AT_PARA_RIGHT_QUOT_STATEatCheckColonAT_PARA_QUOT_COLON_STATE */
    {   atCheckComma ,   AT_PARA_QUOT_COLON_STATE },

    /*  */
    {    NULL    ,    AT_BUTT_STATE    },
};

/*  */
AT_SUB_STATE_STRU AT_PARA_LETTER_STATE_TAB[]=
{
    /* AT_PARA_LETTER_STATEatCheckLetterAT_PARA_LETTER_STATE */
    {   At_CheckLetter    ,   AT_PARA_LETTER_STATE },

    /* AT_PARA_LETTER_STATEatCheckRightBracketAT_PARA_RIGHT_BRACKET_STATE */
    {   At_CheckRightBracket  ,   AT_PARA_RIGHT_BRACKET_STATE   },

    /* AT_PARA_LETTER_STATEatCheckCharSubAT_PARA_LETTER_STATE */
    {   At_CheckCharSub   ,   AT_PARA_LETTER_STATE },

    /* AT_PARA_LETTER_STATEatCheckColonAT_PARA_LETTER_STATE */
    {   atCheckColon     ,   AT_PARA_LETTER_STATE },

    /* AT_PARA_LETTER_STATEatCheckblankAT_PARA_LETTER_STATE */
    {   atCheckblank     ,   AT_PARA_LETTER_STATE },

    /*  */
    {    NULL    ,    AT_BUTT_STATE    },
};

/*  */
AT_SUB_STATE_STRU AT_PARA_NUM_COLON_STATE_TAB[]=
{
    /* AT_PARA_NUM_COLON_STATEatCheckZeroAT_PARA_ZERO_STATE */
    {At_CheckChar0,  AT_PARA_ZERO_STATE},

    /* AT_PARA_NUM_COLON_STATEatCheckDigitAT_PARA_NUM_STATE */
    {At_CheckDigit, AT_PARA_NUM_STATE},

    /*  */
    {NULL,          AT_BUTT_STATE},
};

/*  */
AT_SUB_STATE_STRU AT_PARA_QUOT_COLON_STATE_TAB[]=
{
    /* AT_PARA_QUOT_COLON_STATEatCheckQuotAT_PARA_LEFT_QUOT_STATE */
    {   At_CheckQuot  ,   AT_PARA_LEFT_QUOT_STATE },

    /*  */
    {    NULL    ,    AT_BUTT_STATE    },
};


/*  BEGIN */

/* 0 */
AT_SUB_STATE_STRU AT_PARA_ZERO_STATE_TAB[]=
{
    /* AT_PARA_ZERO_STATEat_CheckHexAT_PARA_HEX_STATE */
    {atCheckHex,          AT_PARA_HEX_STATE},

    /* AT_PARA_ZERO_STATEatCheckDigitAT_PARA_NUM_STATE */
    {At_CheckDigit,        AT_PARA_NUM_STATE},

    /* AT_PARA_ZERO_STATEatCheckColonAT_PARA_NUM_COLON_STATE */
    {atCheckComma,        AT_PARA_NUM_COLON_STATE},

    /* AT_PARA_ZERO_STATEatCheckRightBracketAT_PARA_RIGHT_BRACKET_STATE */
    {At_CheckRightBracket, AT_PARA_RIGHT_BRACKET_STATE},

    /* AT_PARA_ZERO_STATEatCheckCharSubAT_PARA_SUB_STATE */
    {At_CheckCharSub,      AT_PARA_SUB_STATE},

    /*  */
    {NULL,                 AT_BUTT_STATE},
};

/*  */
AT_SUB_STATE_STRU AT_PARA_HEX_STATE_TAB[]=
{
    /* AT_PARA_HEX_STATEat_CheckHexAT_PARA_HEX_NUM_STATE */
    {atCheckHexNum, AT_PARA_HEX_NUM_STATE},

    /*  */
    {NULL,           AT_BUTT_STATE},
};

/*  */
AT_SUB_STATE_STRU AT_PARA_HEX_NUM_STATE_TAB[]=
{
    /* AT_PARA_ZERO_STATEat_CheckHexAT_PARA_HEX_STATE */
    {atCheckHexNum,       AT_PARA_HEX_NUM_STATE},

    /* AT_PARA_ZERO_STATEatCheckColonAT_PARA_NUM_COLON_STATE */
    {atCheckComma,        AT_PARA_NUM_COLON_STATE},

    /* AT_PARA_ZERO_STATEatCheckRightBracketAT_PARA_RIGHT_BRACKET_STATE */
    {At_CheckRightBracket, AT_PARA_RIGHT_BRACKET_STATE},

    /* AT_PARA_ZERO_STATEatCheckCharSubAT_PARA_SUB_STATE */
    {At_CheckCharSub,      AT_PARA_SUB_STATE},

    /*  */
    {NULL,                 AT_BUTT_STATE},
};

/* 0 */
AT_SUB_STATE_STRU AT_PARA_ZERO_SUB_STATE_TAB[]=
{
    /* AT_PARA_ZERO_SUB_STATEat_CheckHexAT_PARA_HEX_SUB_STATE */
    {atCheckHex,          AT_PARA_HEX_SUB_STATE},

    /* AT_PARA_NUM_SUB_STATEatCheckDigitAT_PARA_NUM_SUB_STATE */
    {At_CheckDigit,        AT_PARA_NUM_SUB_STATE    },

    /* AT_PARA_NUM_SUB_STATEatCheckColonAT_PARA_NUM_SUB_COLON_STATE */
    {atCheckComma,        AT_PARA_NUM_SUB_COLON_STATE  },

    /* AT_PARA_NUM_SUB_STATEatCheckRightBracketAT_PARA_RIGHT_BRACKET_STATE */
    {At_CheckRightBracket, AT_PARA_RIGHT_BRACKET_STATE   },

    /*  */
    {NULL,                 AT_BUTT_STATE    },
};

/*  */
AT_SUB_STATE_STRU AT_PARA_HEX_SUB_STATE_TAB[]=
{
    /* AT_PARA_HEX_SUB_STATEat_CheckHexAT_PARA_HEX_NUM_SUB_STATE */
    {atCheckHexNum, AT_PARA_HEX_NUM_SUB_STATE},

    /*  */
    {NULL,           AT_BUTT_STATE},
};

/*  */
AT_SUB_STATE_STRU AT_PARA_HEX_NUM_SUB_STATE_TAB[]=
{
    /* AT_PARA_HEX_NUM_SUB_STATEat_CheckHexNumAT_PARA_HEX_NUM_SUB_STATE */
    {atCheckHexNum,       AT_PARA_HEX_NUM_SUB_STATE},

    /* AT_PARA_NUM_SUB_STATEatCheckColonAT_PARA_NUM_SUB_COLON_STATE */
    {atCheckComma,        AT_PARA_NUM_SUB_COLON_STATE  },

    /* AT_PARA_NUM_SUB_STATEatCheckRightBracketAT_PARA_RIGHT_BRACKET_STATE */
    {At_CheckRightBracket, AT_PARA_RIGHT_BRACKET_STATE   },

    /*  */
    {NULL,                 AT_BUTT_STATE    },
};

/*  END */

/*  BEGIN */

/*  */
AT_SUB_STATE_STRU AT_PARA_NO_QUOT_LETTER_STATE_TAB[]=
{
    /* AT_PARA_NO_QUOT_LETTER_STATEatCheckLetterAT_PARA_NO_QUOT_LETTER_STATE */
    {At_CheckLetter,       AT_PARA_NO_QUOT_LETTER_STATE },

    /* AT_PARA_NO_QUOT_LETTER_STATEatCheckRightBracketAT_PARA_RIGHT_BRACKET_STATE */
    {At_CheckRightBracket, AT_PARA_RIGHT_BRACKET_STATE   },

    /*  */
    {NULL,                 AT_BUTT_STATE    },
};

/*  END */

/*  */
AT_MAIN_STATE_STRU AT_MAIN_PARA_STATE_TAB[] =
{
    /* AT_NONE_STATEAT_PARA_NONE_STATE_TAB */
    {   AT_NONE_STATE   ,   AT_PARA_NONE_STATE_TAB  },

    /* AT_PARA_LEFT_BRACKET_STATEAT_PARA_LEFT_BRACKET_STATE_TAB */
    {   AT_PARA_LEFT_BRACKET_STATE  , AT_PARA_LEFT_BRACKET_STATE_TAB    },

    /* AT_PARA_RIGHT_BRACKET_STATEAT_PARA_RIGHT_BRACKET_STATE_TAB */
    {   AT_PARA_RIGHT_BRACKET_STATE  , AT_PARA_RIGHT_BRACKET_STATE_TAB    },

    /* AT_PARA_LETTER_STATEAT_PARA_LETTER_STATE_TAB */
    {   AT_PARA_LETTER_STATE    ,   AT_PARA_LETTER_STATE_TAB    },

    /* AT_PARA_NUM_STATEAT_PARA_NUM_STATE_TAB */
    {   AT_PARA_NUM_STATE    ,   AT_PARA_NUM_STATE_TAB  },

    /* AT_PARA_NUM_COLON_STATEAT_PARA_NUM_COLON_STATE_TAB */
    {   AT_PARA_NUM_COLON_STATE ,    AT_PARA_NUM_COLON_STATE_TAB  },

    /* AT_PARA_SUB_STATEAT_PARA_SUB_STATE_TAB */
    {   AT_PARA_SUB_STATE    ,   AT_PARA_SUB_STATE_TAB  },

    /* AT_PARA_NUM_SUB_STATEAT_PARA_NUM_SUB_STATE_TAB */
    {   AT_PARA_NUM_SUB_STATE   ,  AT_PARA_NUM_SUB_STATE_TAB  },

    /* AT_PARA_NUM_SUB_COLON_STATEAT_PARA_NUM_SUB_COLON_STATE_TAB */
    {   AT_PARA_NUM_SUB_COLON_STATE  ,   AT_PARA_NUM_SUB_COLON_STATE_TAB  },

    /* AT_PARA_COLON_STATEAT_PARA_COLON_STATE_TAB */
    {   AT_PARA_COLON_STATE ,    AT_PARA_COLON_STATE_TAB  },

    /* AT_PARA_LEFT_QUOT_STATEAT_PARA_LEFT_QUOT_STATE_TAB */
    {   AT_PARA_LEFT_QUOT_STATE ,   AT_PARA_LEFT_QUOT_STATE_TAB    },

    /* AT_PARA_RIGHT_QUOT_STATEAT_PARA_RIGHT_QUOT_STATE_TAB */
    {   AT_PARA_RIGHT_QUOT_STATE    ,   AT_PARA_RIGHT_QUOT_STATE_TAB    },

    /* AT_PARA_QUOT_COLON_STATEAT_PARA_QUOT_COLON_STATE_TAB */
    {   AT_PARA_QUOT_COLON_STATE    ,   AT_PARA_QUOT_COLON_STATE_TAB    },

    /* AT_PARA_ZERO_STATEAT_PARA_ZERO_STATE_TAB */
    {AT_PARA_ZERO_STATE,           AT_PARA_ZERO_STATE_TAB},

    /* AT_PARA_ZERO_SUB_STATEAT_PARA_ZERO_SUB_STATE_TAB */
    {AT_PARA_ZERO_SUB_STATE,       AT_PARA_ZERO_SUB_STATE_TAB},

    /* AT_PARA_HEX_STATEAT_PARA_HEX_STATE_TAB */
    {AT_PARA_HEX_STATE,            AT_PARA_HEX_STATE_TAB},

    /* AT_PARA_HEX_NUM_STATEAT_PARA_HEX_NUM_STATE_TAB */
    {AT_PARA_HEX_NUM_STATE,        AT_PARA_HEX_NUM_STATE_TAB},

    /* AT_PARA_HEX_SUB_STATEAT_PARA_HEX_SUB_STATE_TAB */
    {AT_PARA_HEX_SUB_STATE,        AT_PARA_HEX_SUB_STATE_TAB},

    /* AT_PARA_HEX_NUM_SUB_STATEAT_PARA_HEX_NUM_SUB_STATE_TAB */
    {AT_PARA_HEX_NUM_SUB_STATE,    AT_PARA_HEX_NUM_SUB_STATE_TAB},

    /* AT_PARA_NO_QUOT_LETTER_STATEAT_PARA_NO_QUOT_LETTER_STATE_TAB */
    {AT_PARA_NO_QUOT_LETTER_STATE, AT_PARA_NO_QUOT_LETTER_STATE_TAB},

    /*  */
    {   AT_BUTT_STATE   ,   NULL  },
};

pAtChkFuncType      pgAtCheckFunc   = NULL;

/******************************************************************************
 : atCmparePara
 : 

 :
  This function has no arguments.

   :
    AT_SUCCESS: 
    AT_FAILURE: 

 : TODO: ...
 : TODO: ...
     : /00064416 [2009-08-11]
******************************************************************************/

VOS_UINT32 atCmparePara(VOS_VOID)
{
    /**/
    if(NULL != pgAtCheckFunc)
    {
        /**/
        if(0 < gastAtParaList[g_stATParseCmd.ucParaCheckIndex].usParaLen)
        {
            /**/
            if(AT_SUCCESS != pgAtCheckFunc(&gastAtParaList[g_stATParseCmd.ucParaCheckIndex]))
            {
                return AT_FAILURE;           /*  */
            }
        }

        /*1*/
        g_stATParseCmd.ucParaCheckIndex++;

        /*,*/
        if(0 != g_stATParseCmd.ucParaNumRangeIndex)
        {
            g_stATParseCmd.ucParaNumRangeIndex = 0;
            TAF_MEM_SET_S(g_stATParseCmd.astParaNumRange,sizeof(g_stATParseCmd.astParaNumRange), 0x00, sizeof(g_stATParseCmd.astParaNumRange));
        }

        if(0 != g_stATParseCmd.ucParaStrRangeIndex)
        {
            g_stATParseCmd.ucParaStrRangeIndex = 0;
            TAF_MEM_SET_S(g_stATParseCmd.auStrRange, sizeof(g_stATParseCmd.auStrRange), 0x00, sizeof(g_stATParseCmd.auStrRange));
        }

        pgAtCheckFunc = NULL;

        return AT_SUCCESS;                   /*  */
    }
    else
    {
        return AT_FAILURE;                   /*  */
    }
}

/******************************************************************************
 : atParsePara
 : ,,

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

VOS_UINT32 atParsePara( VOS_UINT8 * pData, VOS_UINT16 usLen)
{
    VOS_UINT16 usLength = 0;                        /*  */
    VOS_UINT8 *pucCurrPtr = pData;                  /*  */
    VOS_UINT8 *pucCopyPtr = pData;                  /*   */
    AT_STATE_TYPE_ENUM curr_state = AT_NONE_STATE;  /*   */
    AT_STATE_TYPE_ENUM new_state = AT_NONE_STATE;   /*   */

    /* */
    while( (usLength++ < usLen) && (g_stATParseCmd.ucParaNumRangeIndex < AT_MAX_PARA_NUMBER) && (g_stATParseCmd.ucParaStrRangeIndex < AT_MAX_PARA_NUMBER))        /*  */
    {
        curr_state = new_state;                 /*  */

        /*  */
        new_state = atFindNextMainState(AT_MAIN_PARA_STATE_TAB,*pucCurrPtr,curr_state);

        switch(new_state)                       /* */
        {
        case AT_PARA_NUM_STATE:                 /* */
        case AT_PARA_LETTER_STATE:              /* */
        case AT_PARA_LEFT_QUOT_STATE:           /* */
        case AT_PARA_NUM_SUB_STATE:             /* */
        case AT_PARA_ZERO_STATE:                /* 0 */
        case AT_PARA_ZERO_SUB_STATE:            /* 0 */
        case AT_PARA_NO_QUOT_LETTER_STATE:      /*  */
            if(curr_state != new_state)         /* */
            {
                pucCopyPtr = pucCurrPtr;            /*  */
            }
            break;

        case AT_PARA_HEX_STATE:                 /*  */
            /* continue */
        case AT_PARA_HEX_NUM_STATE:             /*  */
            /* continue */
        case AT_PARA_HEX_SUB_STATE:             /*  */
            /* continue */
        case AT_PARA_HEX_NUM_SUB_STATE:         /*  */
            break;

        case AT_PARA_QUOT_COLON_STATE:          /*  */

            /*  */
            /* 1*/

            if ((VOS_UINT32)(pucCurrPtr - pucCopyPtr) < sizeof(g_stATParseCmd.auStrRange[g_stATParseCmd.ucParaStrRangeIndex]))
            {
                atRangeCopy(g_stATParseCmd.auStrRange[g_stATParseCmd.ucParaStrRangeIndex++],pucCopyPtr,pucCurrPtr);
            }
            else
            {
                return AT_FAILURE;                  /*  */
            }
            break;

        case AT_PARA_NUM_SUB_COLON_STATE:

            /*  */
            /* 1*/
            g_stATParseCmd.astParaNumRange[g_stATParseCmd.ucParaNumRangeIndex++].ulBig = atRangeToU32(pucCopyPtr,pucCurrPtr);

            break;

        case AT_PARA_NUM_COLON_STATE:

            /*  */
            g_stATParseCmd.astParaNumRange[g_stATParseCmd.ucParaNumRangeIndex].ulSmall = atRangeToU32(pucCopyPtr,pucCurrPtr);

            /* */
            g_stATParseCmd.astParaNumRange[g_stATParseCmd.ucParaNumRangeIndex].ulBig = g_stATParseCmd.astParaNumRange[g_stATParseCmd.ucParaNumRangeIndex].ulSmall;

            /* 1*/
            g_stATParseCmd.ucParaNumRangeIndex++;

            break;

        case AT_PARA_SUB_STATE:

            /*  */
            g_stATParseCmd.astParaNumRange[g_stATParseCmd.ucParaNumRangeIndex].ulSmall = atRangeToU32(pucCopyPtr,pucCurrPtr);

            break;

        case AT_PARA_RIGHT_BRACKET_STATE:             /*  */
            switch (curr_state)
            {
            case AT_PARA_NUM_SUB_STATE:          /*  */
                /* continue */
            case AT_PARA_ZERO_SUB_STATE:
                /* continue */
            case AT_PARA_HEX_NUM_SUB_STATE:

                /*  */
                /* 1*/
                g_stATParseCmd.astParaNumRange[g_stATParseCmd.ucParaNumRangeIndex++].ulBig = atRangeToU32(pucCopyPtr,pucCurrPtr);

                pgAtCheckFunc = atCheckNumPara;    /*  */

                break;

            case AT_PARA_NUM_STATE:
                /* continue */
            case AT_PARA_ZERO_STATE:
                /* continue */
            case AT_PARA_HEX_NUM_STATE:

                /*  */
                g_stATParseCmd.astParaNumRange[g_stATParseCmd.ucParaNumRangeIndex].ulSmall = atRangeToU32(pucCopyPtr,pucCurrPtr);

                /* */
                g_stATParseCmd.astParaNumRange[g_stATParseCmd.ucParaNumRangeIndex].ulBig = g_stATParseCmd.astParaNumRange[g_stATParseCmd.ucParaNumRangeIndex].ulSmall;

                /* 1*/
                g_stATParseCmd.ucParaNumRangeIndex++;

                pgAtCheckFunc = atCheckNumPara;    /*  */

                break;

            case AT_PARA_LETTER_STATE:

                /*  */
                if ((VOS_UINT32)(pucCurrPtr - pucCopyPtr) < sizeof(g_stATParseCmd.auStrRange[g_stATParseCmd.ucParaStrRangeIndex]))
                {
                    atRangeCopy(g_stATParseCmd.auStrRange[g_stATParseCmd.ucParaStrRangeIndex],pucCopyPtr,pucCurrPtr);
                }
                else
                {
                    return AT_FAILURE;                  /*  */
                }

                /*  */
                pgAtCheckFunc = At_CheckStringPara;

                break;

            case AT_PARA_NO_QUOT_LETTER_STATE:      /*  */

                /*  */
                if ((VOS_UINT32)(pucCurrPtr - pucCopyPtr) < sizeof(g_stATParseCmd.auStrRange[g_stATParseCmd.ucParaStrRangeIndex]))
                {
                    atRangeCopy(g_stATParseCmd.auStrRange[g_stATParseCmd.ucParaStrRangeIndex],pucCopyPtr,pucCurrPtr);
                }
                else
                {
                    return AT_FAILURE;                  /*  */
                }

                /*  */
                pgAtCheckFunc = atCheckNoQuotStringPara;

                break;

            default:    /* AT_PARA_RIGHT_QUOT_STATE */

                /*  */
                if ((VOS_UINT32)(pucCurrPtr - pucCopyPtr) < sizeof(g_stATParseCmd.auStrRange[g_stATParseCmd.ucParaStrRangeIndex]))
                {
                    atRangeCopy(g_stATParseCmd.auStrRange[g_stATParseCmd.ucParaStrRangeIndex++],pucCopyPtr,pucCurrPtr);
                }
                else
                {
                    return AT_FAILURE;                  /*  */
                }

                /*  */
                pgAtCheckFunc = atCheckCharPara;

                break;
            }

            if(AT_FAILURE == atCmparePara())       /*  */
            {
                return AT_FAILURE;                   /*  */
            }
            break;

        case AT_BUTT_STATE:                     /*  */
            return AT_FAILURE;                  /*  */

        default:
            break;
        }
        pucCurrPtr++;                               /*  */
    }

    if(AT_NONE_STATE == new_state)                  /*  */
    {
        return AT_FAILURE;                          /*  */
    }

    return AT_SUCCESS;                          /*  */
}




