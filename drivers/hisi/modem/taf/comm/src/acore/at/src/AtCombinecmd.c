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

#include "ATCmdProc.h"

#include "hi_list.h"

#include "at_common.h"
#include "AtCmdCallProc.h"

#include "AtCombinecmd.h"


#define    THIS_FILE_ID        PS_FILE_ID_AT_COMBINEDCMD_C

VOS_UINT32 At_GetSecondAddr(VOS_UINT8 *pData,VOS_UINT16 usLen, VOS_UINT8** ppDataOut)
{
    VOS_UINT8* pucFirAddr = NULL;
    VOS_UINT8* pucSecAddr = NULL;
    VOS_UINT32 ulBasicCmdLen = 0;
    VOS_UINT8* pcTmp = NULL;

    /* \0 */
    pcTmp = (VOS_UINT8*)AT_MALLOC(usLen+1);
    if(NULL == pcTmp)
    {
        return ERR_MSP_FAILURE;
    }

    TAF_MEM_CPY_S(pcTmp, usLen+1, pData, usLen);
    pcTmp[usLen] = '\0';

    pucFirAddr = At_GetFirstBasicCmdAddr(pcTmp, &ulBasicCmdLen);
    if(NULL == pucFirAddr)
    {
        AT_FREE(pcTmp);
        return ERR_MSP_FAILURE;
    }

    pucSecAddr = At_GetFirstBasicCmdAddr((pucFirAddr + ulBasicCmdLen), &ulBasicCmdLen);

    if(NULL == pucSecAddr)
    {
        *ppDataOut = pData + usLen;
    }
    else
    {
        *ppDataOut = pData + (pucSecAddr - pcTmp);
    }

    AT_FREE(pcTmp);
    return ERR_MSP_SUCCESS;
}


/******************************************************************************
 : At_GetFirstCmdLen
 : 

 :
   pData [in] 
   usLen [in] 

     : /00064416 [2011-06-21]
******************************************************************************/
VOS_UINT32 At_GetFirstCmdLen( VOS_UINT8 *pData, VOS_UINT16 usLen)
{
    VOS_UINT8* pucBegin  = pData;
    VOS_UINT8* pucEnd    = pData;
    VOS_UINT16 usLenFir  = 0;

    if(ERR_MSP_SUCCESS == At_GetSecondAddr(pucBegin, usLen, &pucEnd))
    {
        usLenFir = (VOS_UINT16)(pucEnd - pucBegin);
    }
    else
    {
        /*  */
        usLenFir = usLen;
    }

    return usLenFir;
}


/******************************************************************************
 : At_ResetCombinCmdInfo
 : AT

     : /64416 [2011-08-25]

  2.       : 20111225
           : /00130025
       : DTS2011120703681

  3.       : 2016516
           : A00165503
       : DTS2016050901596: , 
                 
******************************************************************************/
VOS_VOID At_ResetCombinCmdInfo(HI_LIST_S* pstCombList)
{
    AT_FW_COMBINE_CMD_INFO_STRU        *pstCombineCmdInfo = VOS_NULL_PTR;
    AT_FW_COMBINE_CMD_NODE_STRU        *pstNode = VOS_NULL_PTR;
    HI_LIST_S                          *pstTmp = VOS_NULL_PTR;
    HI_LIST_S                          *me = VOS_NULL_PTR;

    if ((VOS_NULL_PTR == pstCombList) || (VOS_NULL_PTR == pstCombList->next))
    {
        return ;
    }

    /*  */
    msp_list_for_each_safe(me, pstTmp, pstCombList)
    {
        if (me == NULL)
        {
            pstCombineCmdInfo = msp_list_entry(pstCombList, AT_FW_COMBINE_CMD_INFO_STRU, stCombineCmdList);
            pstCombineCmdInfo->usTotalNum = 0;
            pstCombineCmdInfo->usProcNum  = 0;
            /*lint -e717*/
            HI_INIT_LIST_HEAD(pstCombList);
            /*lint +e717*/
            return;
        }

        pstNode = msp_list_entry(me, AT_FW_COMBINE_CMD_NODE_STRU, stCombCmdList);
        /*lint -e774*/
        if (VOS_NULL_PTR == pstNode)
        {
            pstCombineCmdInfo = msp_list_entry(pstCombList, AT_FW_COMBINE_CMD_INFO_STRU, stCombineCmdList);
            pstCombineCmdInfo->usTotalNum = 0;
            pstCombineCmdInfo->usProcNum  = 0;
            /*lint -e717*/
            HI_INIT_LIST_HEAD(pstCombList);
            /*lint +e717*/
            return;
        }
        /*lint +e774*/

        msp_list_del(&(pstNode->stCombCmdList));
        AT_FREE(pstNode->pstCombCmd);
        AT_FREE(pstNode);
    }

    pstCombineCmdInfo = msp_list_entry(pstCombList, AT_FW_COMBINE_CMD_INFO_STRU, stCombineCmdList);
    pstCombineCmdInfo->usTotalNum = 0;
    pstCombineCmdInfo->usProcNum  = 0;

    return ;
}


/******************************************************************************
     : At_ResetCombinParseInfo
   : AT
   : VOS_UINT8 ucIndex
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20111014
           : c64416
       : 

  2.       : 20111225
           : /00130025
       : DTS2011120703681

******************************************************************************/
VOS_VOID At_ResetCombinParseInfo(VOS_UINT8 ucIndex)
{
    HI_LIST_S* pstCombList = NULL;
    AT_PARSE_CONTEXT_STRU* pClientContext = NULL;

    if (ucIndex >= AT_MAX_CLIENT_NUM)
    {
        return;
    }

    pClientContext = &(g_stParseContext[ucIndex]);

    pstCombList = &pClientContext->stCombineCmdInfo.stCombineCmdList;

    if(NULL == pstCombList->next)
    {
        /*lint -e717*/
        HI_INIT_LIST_HEAD(&(pClientContext->stCombineCmdInfo.stCombineCmdList));
        /*lint -e717*/
    }

    At_ResetCombinCmdInfo(pstCombList);

    /*buffer*/
    /* MSP_MEMSET(gstAtCombineSendData,  0, sizeof(AT_SEND_DATA_BUFFER_STRU) * AT_MAX_CLIENT_NUM); */
    gstAtCombineSendData[ucIndex].usBufLen = 0;

    return ;
}


/*  */
VOS_VOID At_PrintCombinCmd(VOS_VOID)
{
    VOS_UINT32 i = 0, j = 0;
    HI_LIST_S* me = NULL;
    HI_LIST_S* pstCombList = NULL;
    AT_PARSE_CONTEXT_STRU* pClientContext = NULL;
    AT_FW_COMBINE_CMD_STRU* pstCombCmd = NULL;
    AT_FW_COMBINE_CMD_NODE_STRU* pstCombCmdNode = NULL;

    for(j = 0; j < AT_MAX_CLIENT_NUM; j++)
    {
        pClientContext = &(g_stParseContext[j]);

        pstCombList = &pClientContext->stCombineCmdInfo.stCombineCmdList;

        /* clientClientId */
        msp_list_for_each(me, pstCombList)
        {
            pstCombCmdNode = msp_list_entry(me, AT_FW_COMBINE_CMD_NODE_STRU, stCombCmdList);
            pstCombCmd = pstCombCmdNode->pstCombCmd;

            if(NULL == pstCombCmd)
            {
                continue;
            }

            (VOS_VOID)vos_printf("-%d-:", pstCombCmd->ulLen);

            for(i = 0; i < pstCombCmd->ulLen; i++)
            {
                (VOS_VOID)vos_printf("%c", pstCombCmd->ucData[i]);
            }

            (VOS_VOID)vos_printf("\n");
        }
    }

    return ;
}


/******************************************************************************
 : At_StoreSubCombCmd
 : 

     : /64416 [2011-08-25]
******************************************************************************/
static VOS_UINT32 At_StoreSubCombCmd(HI_LIST_S* pstCombList, VOS_UINT8 *pDataIn, VOS_UINT16 usLenIn)
{
    AT_FW_COMBINE_CMD_STRU* pstCombCmd = NULL;
    AT_FW_COMBINE_CMD_NODE_STRU* pstCombCmdNode = NULL;
    AT_FW_COMBINE_CMD_INFO_STRU* pstCombineCmdInfo = NULL;

    /*  */

    pstCombineCmdInfo = msp_list_entry(pstCombList, AT_FW_COMBINE_CMD_INFO_STRU, stCombineCmdList);
    if(pstCombineCmdInfo->usTotalNum >= AT_MAX_NUM_COMBINE_CMD)
    {
        (VOS_VOID)vos_printf("usTotalNum %d\n", pstCombineCmdInfo->usTotalNum);
        return ERR_MSP_FAILURE;
    }

    pstCombCmdNode = (AT_FW_COMBINE_CMD_NODE_STRU*)AT_MALLOC(sizeof(AT_FW_COMBINE_CMD_NODE_STRU));
    if(NULL == pstCombCmdNode)
    {
        return ERR_MSP_MALLOC_FAILUE;
    }

    pstCombCmd = (AT_FW_COMBINE_CMD_STRU*)AT_MALLOC(sizeof(AT_FW_COMBINE_CMD_STRU) + usLenIn + AT_FW_LEN_AT);
    if(NULL == pstCombCmd)
    {
        AT_FREE(pstCombCmdNode);

        return ERR_MSP_MALLOC_FAILUE;
    }
    TAF_MEM_SET_S(pstCombCmd,
        (VOS_SIZE_T)sizeof(AT_FW_COMBINE_CMD_STRU) + usLenIn + AT_FW_LEN_AT,
        0x00,
        (VOS_SIZE_T)sizeof(AT_FW_COMBINE_CMD_STRU) + usLenIn + AT_FW_LEN_AT);
    pstCombCmdNode->pstCombCmd = pstCombCmd;
    pstCombCmd->ulLen = usLenIn + AT_FW_LEN_AT;
    TAF_MEM_CPY_S(pstCombCmd->ucData, usLenIn + AT_FW_LEN_AT, "AT", AT_FW_LEN_AT);
    TAF_MEM_CPY_S(&(pstCombCmd->ucData[AT_FW_LEN_AT]), usLenIn, pDataIn, usLenIn);

    msp_list_add_tail(&pstCombCmdNode->stCombCmdList, pstCombList);

    pstCombineCmdInfo->usTotalNum++;

    return ERR_MSP_SUCCESS;
}


/*  */
static VOS_UINT32 At_BasicCombineCmdParse(HI_LIST_S* pstCombList, VOS_UINT8 *pDataIn, VOS_UINT16 usLenIn)
{
    VOS_UINT32 ulRet = ERR_MSP_FAILURE;
    VOS_UINT16 usLenFir = 0, usChkLen = 0;
    VOS_UINT8* pData = pDataIn;

    while(usChkLen < usLenIn)
    {
        usLenFir = (VOS_UINT16)At_GetFirstCmdLen(pData, (usLenIn - usChkLen));

        ulRet = At_StoreSubCombCmd(pstCombList, pData, usLenFir);
        if(ERR_MSP_SUCCESS != ulRet)
        {
            At_ResetCombinCmdInfo(pstCombList);
            return ulRet;
        }

        usChkLen = usChkLen + usLenFir;
        pData = pDataIn + usChkLen;
    }

    return ERR_MSP_SUCCESS;
}


/*  */
VOS_UINT32 At_BasicExCombineCmdParse(HI_LIST_S* pstCombList, VOS_UINT8 *pDataIn, VOS_UINT16 usLenIn, VOS_UINT16 usFirIndex)
{
    VOS_UINT32 ulRet = ERR_MSP_FAILURE;
    VOS_UINT8* pData = pDataIn;

    /* pstCombListpDataIn */

    if(usFirIndex >= usLenIn)
    {
        return ERR_MSP_FAILURE;
    }

    /* 0"+^$" */
    if(0 != usFirIndex)
    {
        ulRet = At_BasicCombineCmdParse(pstCombList, pData, usFirIndex);
        if(ERR_MSP_SUCCESS != ulRet)
        {
            At_ResetCombinCmdInfo(pstCombList);
            return ulRet;
        }
    }

    ulRet = At_StoreSubCombCmd(pstCombList, (pData+usFirIndex), (usLenIn-usFirIndex));
    if(ERR_MSP_SUCCESS != ulRet)
    {
        At_ResetCombinCmdInfo(pstCombList);
    }

    return ulRet;
}


/******************************************************************************
 : At_UpStringCmdName
 : ()

     : /64416 [2011-11-14]
******************************************************************************/
static VOS_VOID At_UpStringCmdName(VOS_UINT8 *pData, VOS_UINT16 usLen)
{
    TAF_UINT8  *pTmp  = pData;                 /* current Char */
    TAF_UINT16 ChkLen = 0;

    if(0 == usLen)
    {
        return ;
    }

    while((ChkLen++ < usLen) && ('=' != (*pTmp)))
    {
        if ( (*pTmp >= 'a') && (*pTmp <= 'z'))
        {
            *pTmp = *pTmp - 0x20;
        }
        pTmp++;
    }

    return ;
}

/******************************************************************************
 : At_SemicolonCmdParse
 : ;

     : /64416 [2011-08-25]

  2.       : 20131012
           : l00198894
       : DTS2013100901373:ATDPPP

******************************************************************************/
VOS_UINT32 At_SemicolonCmdParse(HI_LIST_S* pstCombList, VOS_UINT8 *pDataIn, VOS_UINT16 usLenIn)
{
    VOS_UINT32 ulRet = ERR_MSP_FAILURE;
    VOS_UINT16 usNumQuota = 0;
    VOS_UINT16 usNumSymbol = 0;
    VOS_UINT16 usFirIndex = 0;
    VOS_UINT16 i = 0;

    if((NULL == pstCombList) || (NULL == pDataIn))
    {
        return ERR_MSP_FAILURE;
    }

    if(AT_SUCCESS != At_CheckCharD(*pDataIn))
    {
        At_UpStringCmdName(pDataIn, usLenIn);
    }
    else
    {
        At_UpStringCmdName(pDataIn, 1);
    }

    /* ';'D */
    if(usLenIn > 2)
    {
        if(AT_SUCCESS == At_CheckCharD(*pDataIn))
        {
            if(AT_SUCCESS == At_CheckSemicolon(*(pDataIn+usLenIn-1)))
            {
                ulRet = At_StoreSubCombCmd(pstCombList, pDataIn, usLenIn);
                if(ERR_MSP_SUCCESS != ulRet)
                {
                    At_ResetCombinCmdInfo(pstCombList);
                }

                return ulRet;
            }
        }
    }

    /* ATD+117 */
    if(usLenIn > 2)
    {
        if((AT_SUCCESS == At_CheckCharD(*pDataIn)) && ('+' == pDataIn[1]))
        {
            ulRet = At_StoreSubCombCmd(pstCombList, pDataIn, usLenIn);
            if(ERR_MSP_SUCCESS != ulRet)
            {
                At_ResetCombinCmdInfo(pstCombList);
            }

            return ulRet;
        }
    }

    /*  */
    while(i < usLenIn)
    {
        if ('"' == pDataIn[i])
        {
            usNumQuota++;
        }
        else if ((('+' == pDataIn[i]) || ('^' == pDataIn[i]) || ('$' == pDataIn[i]))
             && (0 == (usNumQuota % 2)))
        {
            usNumSymbol++;
            if (1 == usNumSymbol)
            {
                usFirIndex = i; /* "+^$" */
            }
        }
        else
        {
        }

        i++;
    }

    /* 0AT */
    if(0 == usNumSymbol)
    {
        ulRet = At_BasicCombineCmdParse(pstCombList, pDataIn, usLenIn);
    }
    /* 1  */
    else if(1 == usNumSymbol)
    {
        ulRet = At_BasicExCombineCmdParse(pstCombList, pDataIn, usLenIn, usFirIndex);
    }
    /* ('+''^''$') */
    else
    {
        ulRet = ERR_MSP_FAILURE;
    }

    return ulRet;
}


/******************************************************************************
 : At_CombineCmdPreProc
 : ,

     : /64416 [2011-08-25]
******************************************************************************/
PRIVATE VOS_UINT32 At_CombineCmdPreProc(HI_LIST_S* pstCombList, VOS_UINT8 *pDataIn, VOS_UINT16 usLenIn)
{
    VOS_UINT16 i = 0;
    VOS_UINT32 ulRet = ERR_MSP_FAILURE;
    VOS_UINT16 usNumQuota = 0;
    VOS_UINT8* pData = pDataIn;
    VOS_UINT8* pDataHead = pDataIn;

    if((NULL == pstCombList) || (NULL == pDataIn))
    {
        return ERR_MSP_FAILURE;
    }

    while( i++ < usLenIn )
    {
        /*  */
        if((*pData == ';') && (0 == (usNumQuota%2)))
        {
            ulRet = At_SemicolonCmdParse(pstCombList, pDataHead, (VOS_UINT16)(pData- pDataHead + 1));
            if(ERR_MSP_SUCCESS != ulRet)
            {
                return ulRet;
            }

            pDataHead = (pData + 1);
        }
        else if(*pData == '"')
        {
            usNumQuota++;
        }
        else
        {
        }

        pData++;
    }

    /*  */
    if(pDataHead != (pDataIn + usLenIn))
    {
        ulRet = At_SemicolonCmdParse(pstCombList, pDataHead, (VOS_UINT16)(pData- pDataHead));
        if(ERR_MSP_SUCCESS != ulRet)
        {
            return ulRet;
        }
    }

    return ERR_MSP_SUCCESS;
}

/*****************************************************************************
     : AT_IsDCmdValidChar
   : D
   : VOS_UINT8                           ucPara 
   : 
     : VOS_UINT32 VOS_TRUE    D
                        VOS_FALSE   D
   :
   :

       :
  1.       : 20131216
           : f62575
       : DTS2013121606723 
*****************************************************************************/
VOS_UINT32 AT_IsDCmdValidChar(
    VOS_UINT8                           ucPara
)
{
    /* dialing digits: 0-9,*,#,A-D */
    if ((ucPara >= '0') && (ucPara <= '9'))
    {
        return VOS_TRUE;
    }

    if ((ucPara >= 'a') && (ucPara <= 'c'))
    {
        return VOS_TRUE;
    }

    if ((ucPara >= 'A') && (ucPara <= 'C'))
    {
        return VOS_TRUE;
    }

    if ((ucPara == '*') || (ucPara == '#'))
    {
        return VOS_TRUE;
    }

    /* GSM/UMTS modifier characters: > i g I G */
    if ('>' == ucPara)
    {
        return VOS_TRUE;
    }

    if ((ucPara == 'i') || (ucPara == 'I'))
    {
        return VOS_TRUE;
    }

    if ((ucPara == 'g') || (ucPara == 'G'))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
     : AT_ProcDCmdGIPara
   : DGI
   : VOS_UINT32                  *pulSrcStrLen 
             VOS_UINT8                   *pucSrcStr    
             VOS_UINT32                   ulInsertStrLen, 
             VOS_UINT8                   *pucInsertStr  
   : VOS_UINT32                  *pulSrcStrLen 
             VOS_UINT8                   *pucSrcStr    
     : 
   :
   :

       :
  1.       : 20131216
           : f62575
       : DTS2013121606723 
*****************************************************************************/
VOS_VOID AT_InsertDCmdGIPara(
    VOS_UINT32                  *pulSrcStrLen,
    VOS_UINT8                   *pucSrcStr,
    VOS_UINT32                   ulMaxMemLength,
    VOS_UINT32                   ulInsertStrLen,
    VOS_UINT8                   *pucInsertStr
)
{
    VOS_UINT32                          ulSrcStrLen;

    ulSrcStrLen = *pulSrcStrLen;

    if (';' == pucSrcStr[ulSrcStrLen - 1])
    {
        TAF_MEM_CPY_S(&(pucSrcStr[ulSrcStrLen - 1]), ulMaxMemLength - (ulSrcStrLen - 1), pucInsertStr, ulInsertStrLen);

        ulSrcStrLen += ulInsertStrLen;

        pucSrcStr[ulSrcStrLen - 1] = ';';
    }
    else
    {
        TAF_MEM_CPY_S(&(pucSrcStr[ulSrcStrLen]), ulMaxMemLength - ulSrcStrLen, pucInsertStr, ulInsertStrLen);

        ulSrcStrLen += ulInsertStrLen;
    }

    *pulSrcStrLen = ulSrcStrLen;

    return;
}

/*****************************************************************************
     : AT_ProcDCmdGIPara
   : DGI
   : VOS_UINT32                   ulSrcStrLen 
             VOS_UINT8                   *pucSrcStr   
   : VOS_UINT32                   ulSrcStrLen 
             VOS_UINT8                   *pucSrcStr   
     : 
   :
   :

       :
  1.       : 20131216
           : f62575
       : DTS2013121606723 
*****************************************************************************/
VOS_VOID AT_ProcDCmdGIPara(
    VOS_UINT32                         *pulSrcStrLen,
    VOS_UINT8                          *pucSrcStr
)
{
    VOS_UINT32                          ulLoop;
    VOS_BOOL                            bIExist;
    VOS_BOOL                            biExist;
    VOS_BOOL                            bGExist;
    VOS_BOOL                            bgExist;
    VOS_UINT8                           aucInsertStr[AT_CALL_D_GI_PARA_LEN];
    VOS_UINT32                          ulInsertStrLen;
    VOS_UINT32                          ulPos;
    VOS_UINT32                          ulDstStrLen;
    VOS_UINT8                          *pucDstPara = VOS_NULL_PTR;
    VOS_UINT32                          ulMaxMemLength;

    bIExist = VOS_FALSE;
    biExist = VOS_FALSE;
    bGExist = VOS_FALSE;
    bgExist = VOS_FALSE;

    ulDstStrLen = *pulSrcStrLen;
    ulMaxMemLength = *pulSrcStrLen;
    pucDstPara  = (VOS_UINT8 *)PS_MEM_ALLOC(WUEPS_PID_AT, ulDstStrLen);
    if (VOS_NULL_PTR == pucDstPara)
    {
        AT_WARN_LOG("AT_ProcDCmdGIPara : fail to alloc memory . ");
        return;
    }

    /*
    DGIIi
    GgIi
    */
    for (ulLoop = 0, ulPos   = 0; ulLoop < ulDstStrLen; ulLoop++)
    {
        if ('I' == pucSrcStr[ulLoop])
        {
            bIExist = VOS_TRUE;
            biExist = VOS_FALSE;
            continue;
        }

        if ('i' == pucSrcStr[ulLoop])
        {
            biExist = VOS_TRUE;
            bIExist = VOS_FALSE;
            continue;
        }

        if ('G' == pucSrcStr[ulLoop])
        {
            bGExist = VOS_TRUE;
            continue;
        }

        if ('g' == pucSrcStr[ulLoop])
        {
            bgExist = VOS_TRUE;
            continue;
        }

        *(pucDstPara + ulPos) = *(pucSrcStr + ulLoop);

        ulPos++;
    }

    ulDstStrLen         = ulPos;

    /*  */
    *pulSrcStrLen       = ulDstStrLen;
    TAF_MEM_MOVE_S(pucSrcStr, ulDstStrLen, pucDstPara, ulDstStrLen);

    PS_MEM_FREE(WUEPS_PID_AT, pucDstPara);

    /* GI */
    TAF_MEM_SET_S(aucInsertStr, sizeof(aucInsertStr), 0x00, sizeof(aucInsertStr));

    ulInsertStrLen = 0;
    if (VOS_TRUE == bIExist)
    {
        aucInsertStr[ulInsertStrLen] = 'I';
        ulInsertStrLen++;
    }
    else
    {
        if (VOS_TRUE == biExist)
        {
            aucInsertStr[ulInsertStrLen] = 'i';
            ulInsertStrLen++;
        }
    }

    if ((VOS_TRUE == bGExist)
     || (VOS_TRUE == bgExist))
    {
        aucInsertStr[ulInsertStrLen] = 'G';
        ulInsertStrLen++;
    }

    /* GI */
    AT_InsertDCmdGIPara(pulSrcStrLen, pucSrcStr, ulMaxMemLength, ulInsertStrLen, aucInsertStr);

    return;
}


/*****************************************************************************
     : At_FilterSpecCharacter
   : 
   : VOS_UINT8 ucIndex
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 20130510
           : l65478
       : 
*****************************************************************************/
VOS_VOID At_FilterDCmdSpecCharacter(
    VOS_UINT32                  *pulParaLen,
    VOS_UINT8                   *pucPara
)
{
    VOS_UINT16                  i;
    VOS_UINT16                  usBeginPos;
    VOS_UINT32                  ulRet;

    if (*pulParaLen <= 3)
    {
        return;
    }

    /* ATD */
    /* 'a''A' */
    if(AT_SUCCESS != At_CheckCharA(pucPara[0]))
    {
        return;
    }
    /* 't''T' */
    if(AT_SUCCESS != At_CheckCharT(pucPara[1]))
    {
        return;
    }
    /* 'D''d' */
    if (AT_SUCCESS != At_CheckCharD(pucPara[2]))
    {
        return ;
    }

    usBeginPos = 3;
    /* ISDNATDI<STRING>ATD<STRING>I */
    if ('I' == pucPara[usBeginPos])
    {
        *pulParaLen = *pulParaLen - 1;
        TAF_MEM_MOVE_S(&(pucPara[usBeginPos]), *pulParaLen - usBeginPos, &(pucPara[usBeginPos + 1]), *pulParaLen - usBeginPos);
    }

    /* '+', */
    if ('+' == pucPara[usBeginPos])
    {
        usBeginPos++;
    }

    /* ATD'\0', */
    for (i = usBeginPos; i < *pulParaLen; i++)
    {
        ulRet = AT_IsDCmdValidChar(pucPara[i]);
        if (VOS_TRUE == ulRet)
        {
            continue;
        }

        /* ';' */
        if (i == (*pulParaLen - 1))
        {
            if (pucPara[i] == ';')
            {
                continue;
            }
        }

        *pulParaLen = *pulParaLen - 1;
        TAF_MEM_MOVE_S(&(pucPara[i]), *pulParaLen - i, &(pucPara[i + 1]), *pulParaLen - i);
        i--;
    }

    AT_ProcDCmdGIPara(pulParaLen, pucPara);

    return;
}

/******************************************************************************
 : At_CombineCmdProc
 : 

 :
   ucClientId [in] client id

     : /64416 [2011-08-25]
******************************************************************************/
VOS_UINT32 At_CombineCmdProc(VOS_UINT8 ucClientId)
{
    VOS_UINT32 i = 0;
    HI_LIST_S* me = NULL;
    HI_LIST_S* pstListHead = NULL;
    VOS_UINT32 ulRet = ERR_MSP_FAILURE;
    AT_PARSE_CONTEXT_STRU* pClientContext = NULL;

    AT_FW_COMBINE_CMD_STRU*      pstCombCmd         = NULL;
    AT_FW_COMBINE_CMD_NODE_STRU* pstCombCmdNode     = NULL;
    AT_FW_COMBINE_CMD_INFO_STRU* pstCombineCmdInfo  = NULL;

    AT_RRETURN_CODE_ENUM_UINT32 ulResult = AT_FAILURE;

    /* ucClientIdpDataIn */

    pClientContext = &(g_stParseContext[ucClientId]);

    pstCombineCmdInfo = &pClientContext->stCombineCmdInfo;
    pstListHead = &pstCombineCmdInfo->stCombineCmdList;

    /*  */
    if((0 == pstCombineCmdInfo->usTotalNum) || (pstCombineCmdInfo->usTotalNum <= pstCombineCmdInfo->usProcNum))
    {
        return AT_ERROR;
    }

    /*  */
    msp_list_for_each(me, pstListHead)
    {
        if(i < pstCombineCmdInfo->usProcNum)
        {
            i++;
            continue;
        }

        pstCombCmdNode = msp_list_entry(me, AT_FW_COMBINE_CMD_NODE_STRU, stCombCmdList);
        pstCombCmd = pstCombCmdNode->pstCombCmd;
        break;
    }

    /*  */
    if((i != pstCombineCmdInfo->usProcNum) || (NULL == pstCombCmd))
    {
    /* HAL_DIAG_SDM_FUN(EN_SDM_AT_FW_PARSE_FAILURE, 4, 0, 0); */

        return AT_ERROR;
    }

    /* T-REC-V[1].250-200307-I_MSW-E.doc
    6.3.1	Dial
        Any characters appearing in the dial string that the DCE does not recognize
        as a valid part of the call addressing information or as a valid modifier
        shall be ignored. This permits characters such as parentheses and hyphens
        to be included that are typically used in formatting of telephone numbers.
       */

    At_FilterDCmdSpecCharacter(&(pstCombCmd->ulLen), pstCombCmd->ucData);

    /*  */
    ulResult = (AT_RRETURN_CODE_ENUM_UINT32)AT_ParseCmdType(pstCombCmd->ucData, (VOS_UINT16)pstCombCmd->ulLen);

    /*  */
    if(ERR_MSP_SUCCESS != ulResult)
    {
        if(ERR_MSP_SUCCESS == atMatchCmdName(ucClientId, g_stATParseCmd.ucCmdFmtType))
        {
            if(NULL != g_stParseContext[ucClientId].pstCmdElement)
            {
                return g_stParseContext[ucClientId].pstCmdElement->ulParamErrCode;
            }
        }

        return ulResult;
    }

    /*  */
    ulRet = CmdParseProc(ucClientId, pstCombCmd->ucData, (VOS_UINT16)pstCombCmd->ulLen);
    if((AT_OK != ulRet) && (AT_WAIT_ASYNC_RETURN != ulRet))
    {
        At_ResetCombinCmdInfo(pstListHead);
    }

    return ulRet;
}


/******************************************************************************
 : At_CombineCmdChkProc
 : 

 :
   ucClientId [in] client id
   VOS_UINT8 * pDataIn [in/out] 
   usLenIn [in] 

     : /00064416 [2011-04-01]
******************************************************************************/
VOS_UINT32 At_CombineCmdChkProc(VOS_UINT8 ucClientId,  VOS_UINT8 *pDataIn, VOS_UINT16 usLenIn)
{
    VOS_UINT16 usLen = usLenIn;
    VOS_UINT8* pData = pDataIn;
    VOS_UINT32 ulRet = ERR_MSP_FAILURE;

    AT_PARSE_CONTEXT_STRU* pClientContext = NULL;
    HI_LIST_S* pstListHead = NULL;

    /* ucClientIdpDataIn */

    pClientContext = &(g_stParseContext[ucClientId]);
    pstListHead = &pClientContext->stCombineCmdInfo.stCombineCmdList;

    /* AT */
    if(AT_SUCCESS != At_CheckCharA(pData[0]))
    {
        return AT_ERROR;
    }

    if(AT_SUCCESS != At_CheckCharT(pData[1]))
    {
        return AT_ERROR;
    }

    /* "AT" or "AT;" */
    if(AT_FW_LEN_AT == usLenIn)
    {
        return AT_OK;
    }

    /*  */
    if(3 == usLenIn)
    {
        if(AT_SUCCESS == At_CheckSemicolon(pData[2]))
        {
            return AT_OK;
        }
    }

    /* "AT" */
    pData = pData + AT_FW_LEN_AT;
    usLen = usLen - AT_FW_LEN_AT;

    /*  */
    ulRet = At_CombineCmdPreProc(pstListHead, pData, usLen);
    if(ERR_MSP_SUCCESS != ulRet)
    {
    /* HAL_DIAG_SDM_FUN(EN_SDM_AT_FW_PARSE_FAILURE, 3, 0, 0); */
        return AT_ERROR;
    }

    /* At_PrintCombinCmd(); */

    ulRet = At_CombineCmdProc(ucClientId);

    return ulRet;
}


/******************************************************************************
 : At_CombCmdProcAfterCmd
 : 

 :
   ucClientId [in] client id

     : /64416 [2011-08-25]
  3.       : 2012810
           : L00171473
       : DTS2012082204471, TQE
******************************************************************************/
VOS_VOID At_CombCmdProcAfterCmd(VOS_UINT8 ucClientId)
{
    AT_RRETURN_CODE_ENUM_UINT32         ulResult = AT_FAILURE;
    AT_PARSE_CONTEXT_STRU* pstClientCont = NULL;
    AT_FW_COMBINE_CMD_INFO_STRU* pstCombineCmdInfo = NULL;

    if(ucClientId >= AT_MAX_CLIENT_NUM)
    {
        return;
    }

    pstClientCont = &(g_stParseContext[ucClientId]);

    pstCombineCmdInfo = &pstClientCont->stCombineCmdInfo;

    /*  */
    if(pstCombineCmdInfo->usProcNum < pstCombineCmdInfo->usTotalNum)
    {
        ulResult = (AT_RRETURN_CODE_ENUM_UINT32)At_CombineCmdProc(ucClientId);  /* TODO: */
        if(AT_WAIT_ASYNC_RETURN != ulResult)
        {
            At_FormatResultData(ucClientId, ulResult);
        }
    }
    else
    {
        return;
    }
}


/******************************************************************************
     : At_CombCmdisFinal
   : ATAT_OK
   : VOS_UINT8 ucIndex
   : 
     :
             VOS_FALSE : AT_OK
             VOS_TRUE  : AT_OK
   :
   :

       :
  1.       : 20111011
           : c64416
       : 

******************************************************************************/
VOS_BOOL At_CombCmdisFinal(VOS_UINT8 ucIndex)
{
    AT_PARSE_CONTEXT_STRU* pstClientCont = NULL;
    AT_FW_COMBINE_CMD_INFO_STRU* pstCombineCmdInfo = NULL;

    pstClientCont = &(g_stParseContext[ucIndex]);

    pstCombineCmdInfo = &pstClientCont->stCombineCmdInfo;

    if(0 == pstCombineCmdInfo->usTotalNum)
    {
        return VOS_TRUE;
    }

    if(pstCombineCmdInfo->usProcNum < (pstCombineCmdInfo->usTotalNum - 1))
    {
        return VOS_FALSE;
    }
    else
    {
        return VOS_TRUE;
    }
}



