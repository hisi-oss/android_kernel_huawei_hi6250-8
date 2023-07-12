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

/*****************************************************************************
   1 
*****************************************************************************/
#include "AtDataProc.h"
#include "ATCmdProc.h"
#include "AtCsdInterface.h"
#include "AtTafAgentInterface.h"



/*****************************************************************************
    .C
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_AT_DATAPROC_C

/*****************************************************************************
   2 
*****************************************************************************/

/* HiLink:  */
AT_HILINK_MODE_ENUM_U8                  g_enHiLinkMode       = AT_HILINK_NORMAL_MODE;

/* Modified by s62952 for BalongV300R002 Build 2012-02-28, begin */
/* PDP */
TAF_PDP_TYPE_ENUM_UINT8                g_enAtNdisActPdpType;

/* PDP */
TAF_PDP_TYPE_ENUM_UINT8                g_enAtFirstNdisActPdpType;

/* NDIS */
AT_DIAL_PARAM_STRU                      gstAtNdisAddParam   = {0};

/* NDIS PDP */
AT_PDP_ENTITY_STRU                      g_stAtNdisDhcpPara;

/* NDISCONN , NDISCONN  */
AT_NDISCONN_PARA_STRU                   g_stAtNdisConnPara;



/* PDP */
TAF_PDP_TYPE_ENUM_UINT8                g_enAtAppActPdpType;

/* PDP */
TAF_PDP_TYPE_ENUM_UINT8                g_enAtAppFirstActPdpType;

/*  */
AT_DIAL_PARAM_STRU                      g_stAtAppDialPara       = {0};

/* APP PDP */
AT_PDP_ENTITY_STRU                      g_stAtAppPdpEntity;

/* RA */
AT_IPV6_RA_INFO_STRU                    g_stAtAppRaInfo         = {0};

/* IP*/
VOS_UINT32                              g_ulIpAddr = 0;


/*****************************************************************************
    : g_stFcIdMaptoFcPri
  : FC IDFC Pri

1.        : 2012224
          : L47619
      : 
*****************************************************************************/
AT_FCID_MAP_STRU                        g_stFcIdMaptoFcPri[FC_ID_BUTT];

/* Added by l60609 for DSDA Phase II, 2012-12-18, Begin */
AT_PS_RMNET_ID_TAB                      g_astPsRmNetIdTab[] =
{
    {MODEM_ID_0, FC_ID_NIC_1, AT_PS_USER_CID_1},
    {MODEM_ID_0, FC_ID_NIC_2, AT_PS_USER_CID_2},
    {MODEM_ID_0, FC_ID_NIC_3, AT_PS_USER_CID_3},
    {MODEM_ID_1, FC_ID_NIC_4, AT_PS_USER_CID_1},
    {MODEM_ID_1, FC_ID_NIC_5, AT_PS_USER_CID_2}
};
/* Added by l60609 for DSDA Phase II, 2012-12-18, End */

/* Added by l60609 for V9R1 IPv6&TAF/SM Project, 2013-4-24, begin */
/* ^DCONN */
AT_PS_REPORT_CONN_RESULT_STRU           g_astAtRptConnectedResultTab[] =
{
    /* ID */                        /*  */
    {AT_HSIC1_USER,                     AT_PS_ReportDCONN},
    {AT_HSIC2_USER,                     AT_PS_ReportDCONN},
    {AT_HSIC3_USER,                     AT_PS_ReportDCONN},
    {AT_HSIC4_USER,                     AT_PS_ReportDCONN},
    {AT_APP_USER,                       AT_PS_ReportDCONN}
};

/* ^DEND */
AT_PS_REPORT_END_RESULT_STRU            g_astAtRptEndedResultTab[] =
{
    /* ID */                        /*  */
    {AT_HSIC1_USER,                     AT_PS_ReportDEND},
    {AT_HSIC2_USER,                     AT_PS_ReportDEND},
    {AT_HSIC3_USER,                     AT_PS_ReportDEND},
    {AT_HSIC4_USER,                     AT_PS_ReportDEND},
    {AT_APP_USER,                       AT_PS_ReportDEND}
};


/*  */
AT_PS_REG_FC_POINT_STRU                 g_astAtRegFCPointTab[] =
{
    /* ID */                        /*  */
    {AT_HSIC1_USER,                     AT_PS_RegHsicFCPoint},
    {AT_HSIC2_USER,                     AT_PS_RegHsicFCPoint},
    {AT_HSIC3_USER,                     AT_PS_RegHsicFCPoint},
    {AT_HSIC4_USER,                     AT_PS_RegHsicFCPoint},
    {AT_APP_USER,                       AT_PS_RegAppFCPoint}
};


/*  */
AT_PS_DEREG_FC_POINT_STRU               g_astAtDeRegFCPointTab[] =
{
    /* ID */                        /*  */
    {AT_HSIC1_USER,                     AT_PS_DeRegHsicFCPoint},
    {AT_HSIC2_USER,                     AT_PS_DeRegHsicFCPoint},
    {AT_HSIC3_USER,                     AT_PS_DeRegHsicFCPoint},
    {AT_HSIC4_USER,                     AT_PS_DeRegHsicFCPoint},
    {AT_APP_USER,                       AT_PS_DeRegAppFCPoint}
};

AT_PS_SND_PDP_ACT_IND_STRU              g_astAtSndPdpActIndTab[] =
{
    /* ID */                        /*  */
    {AT_HSIC1_USER,                     AT_PS_SndDipcPdpActInd},
    {AT_HSIC2_USER,                     AT_PS_SndDipcPdpActInd},
    {AT_HSIC3_USER,                     AT_PS_SndDipcPdpActInd},
    {AT_HSIC4_USER,                     AT_PS_SndDipcPdpActInd},
    {AT_APP_USER,                       AT_PS_SndRnicPdpActInd}
};

AT_PS_SND_PDP_DEACT_IND_STRU            g_astAtSndPdpDeActIndTab[] =
{
    /* ID */                        /*  */
    {AT_HSIC1_USER,                     AT_PS_SndDipcPdpDeactInd},
    {AT_HSIC2_USER,                     AT_PS_SndDipcPdpDeactInd},
    {AT_HSIC3_USER,                     AT_PS_SndDipcPdpDeactInd},
    {AT_HSIC4_USER,                     AT_PS_SndDipcPdpDeactInd},
    {AT_APP_USER,                       AT_PS_SndRnicPdpDeactInd}
};

AT_CHDATA_RNIC_RMNET_ID_STRU            g_astAtChdataRnicRmNetIdTab[] =
{
    {AT_CH_DATA_CHANNEL_ID_1, RNIC_RMNET_ID_0, {0, 0, 0}},
    {AT_CH_DATA_CHANNEL_ID_2, RNIC_RMNET_ID_1, {0, 0, 0}},
    {AT_CH_DATA_CHANNEL_ID_3, RNIC_RMNET_ID_2, {0, 0, 0}},
    {AT_CH_DATA_CHANNEL_ID_4, RNIC_RMNET_ID_3, {0, 0, 0}},
    {AT_CH_DATA_CHANNEL_ID_5, RNIC_RMNET_ID_4, {0, 0, 0}}
};

/* Added by l60609 for V9R1 IPv6&TAF/SM Project, 2013-4-24, end */
/*****************************************************************************
   3 
*****************************************************************************/

extern const TAF_CHAR                       *g_PppDialRateDisplay[];

extern const AT_DISPLAY_RATE_PAIR_STRU  g_ucLTERateDisplay[AT_UE_LTE_CATEGORY_NUM_MAX];

extern const VOS_CHAR                       *g_ucDialRateDisplayNv[];

/*****************************************************************************
   4 
*****************************************************************************/
/*****************************************************************************
     : AT_PS_SetPsCallErrCause
   : PS
   : VOS_UINT16                          usClientId
             TAF_PS_CAUSE_ENUM_UINT32            enPsErrCause
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 2013221
           : l60609
       : 

*****************************************************************************/
VOS_VOID AT_PS_SetPsCallErrCause(
    VOS_UINT16                          usClientId,
    TAF_PS_CAUSE_ENUM_UINT32            enPsErrCause
)
{
    AT_MODEM_PS_CTX_STRU               *pstPsModemCtx = VOS_NULL_PTR;

    pstPsModemCtx = AT_GetModemPsCtxAddrFromClientId(usClientId);

    pstPsModemCtx->enPsErrCause = enPsErrCause;

    return;
}

/*****************************************************************************
     : AT_PS_GetPsCallErrCause
   : PS
   : VOS_UINT16                          usClientId
   : 
     : TAF_PS_CAUSE_ENUM_UINT32
   :
   :

       :
  1.       : 2013221
           : l60609
       : 

*****************************************************************************/
TAF_PS_CAUSE_ENUM_UINT32 AT_PS_GetPsCallErrCause(
    VOS_UINT16                          usClientId
)
{
    AT_MODEM_PS_CTX_STRU               *pstPsModemCtx = VOS_NULL_PTR;

    pstPsModemCtx = AT_GetModemPsCtxAddrFromClientId(usClientId);

    return pstPsModemCtx->enPsErrCause;
}
/*****************************************************************************
     : AT_GetLanAddr32
   : --->UINT32(LITTLE_ENDIAN)
   : VOS_UINT8                            *pucAddr
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 2011325
           : A00165503
       : 

*****************************************************************************/
VOS_UINT32 AT_GetLanAddr32(
  VOS_UINT8                            *pucAddr
)
{
    VOS_UINT32                          ulAddr;

    ulAddr = *pucAddr++;
    ulAddr <<= 8;
    ulAddr |= *pucAddr++;
    ulAddr <<= 8;
    ulAddr |= *pucAddr++;
    ulAddr <<= 8;
    ulAddr |= *pucAddr;

    return ulAddr;
}


/******************************************************************************
 Function:       AT_DHCPGetIPMask
 Description:    IP
 Calls:
 Data Accessed:
 Data Updated:
 Input:         TAF_UINT32 ulIpAddrHL   IP   
 Output:
 Return:        TAF_UINT32 ulNetMask     
 Others:
                IPbit[0]
                IPbitbit[x]bit[0]
                 0--x
  1.Date        : 2009-08-03
    Author      : S62952
    Modification: Created function
******************************************************************************/
TAF_UINT32 AT_DHCPGetIPMask(
    TAF_UINT32                          ulIpAddrHL
)
{
    /* 11111111.11111111.11111111.11111110*/
    TAF_UINT32 ulMask    = 0xfffffffeU;
    TAF_UINT32 ulIpTemp  = ulIpAddrHL;
    TAF_UINT32 ul1stBit;

    ul1stBit = ulIpTemp & 0x00000001;

    while(0x0 != ulMask)
    {
        ulMask   = ulMask << 1;
        ulIpTemp = ulIpTemp >> 1;

        if (ul1stBit != (ulIpTemp & 0x00000001))
        {
            break;
        }
    }

    return ulMask;
}
/******************************************************************************
 Function:       AT_DHCPGetGateWay
 Description:    IP
 Calls:
 Data Accessed:
 Data Updated:
 Input:         VOS_UINT32 ulIpAddrHL   IP   
                VOS_UINT32 ulMaskHL      
 Output:
 Return:        VOS_UINT32 ulGateWay     
 Others:
                IP+IP?
   1.Date        : 2009-08-03
    Author      : S62952
    Modification: Created function
******************************************************************************/
VOS_UINT32 AT_DHCPGetGateWay(
    VOS_UINT32                          ulIpAddrHL,
    VOS_UINT32                          ulMaskHL
)
{
    VOS_UINT32 ulGateWay;

    ulGateWay = 0;

    ulGateWay = (ulIpAddrHL & ulMaskHL) + 1;

    while (ulGateWay == ulIpAddrHL)
    {
        ulGateWay ++;
    };

    return ulGateWay;
}

/******************************************************************************
 : AT_Ipv4AddrAtoi
 : IPV4

 :
   pcString [in] IP,char * pcString="192.168.0.1"
   pucNumber [out] IP,char pucNumber[4]={192,168,0,1};

   :
    TODO: ...

 : TODO: ...
 : TODO: ...
     : /00064416 [2010-02-02]

  2.       : 2013923
           : A00165503
       : UART-MODEM: 
******************************************************************************/
VOS_UINT32 AT_Ipv4AddrAtoi(
    VOS_CHAR                           *pcString,
    VOS_UINT8                          *pucNumber
)
{
    VOS_UINT32                          i = 0;
    VOS_UINT32                          ulStrLen = 0;
    VOS_UINT32                          ulNumLen = 0;
    VOS_UINT32                          ulDotNum = 0;
    VOS_UINT32                          ulValTmp = 0;
    VOS_UINT8                           aucAddr[4] = {0};


    if ( (VOS_NULL_PTR == pcString) || (VOS_NULL_PTR == pucNumber) )
    {
        return VOS_ERR;
    }

    ulStrLen = VOS_StrLen(pcString);

    if ( ulStrLen > VOS_StrLen("255.255.255.255") )
    {
        AT_NORM_LOG("AT_Ipv4AddrAtoi: PCSCF IPV4 address length out of range");
        return VOS_ERR;
    }

    for ( i = 0; i < ulStrLen; i++ )
    {
        if ( (pcString[i] >= '0') && (pcString[i] <= '9') )
        {
            ulValTmp = (ulValTmp * 10) + (pcString[i] - '0');

            ulNumLen++;
            continue;
        }
        else if ( pcString[i] == '.' )
        {
            if ( (0 == ulNumLen) || (ulNumLen > 3) )
            {
                AT_NORM_LOG("AT_Ipv4AddrAtoi: the number between dots is out of range");
                return VOS_ERR;
            }

            if ( ulValTmp > 255 )
            {
                AT_NORM_LOG("AT_Ipv4AddrAtoi: the number is larger than 255");
                return VOS_ERR;
            }

            aucAddr[ulDotNum] = (VOS_UINT8)ulValTmp;

            ulValTmp = 0;
            ulNumLen = 0;

            /* '.' */
            ulDotNum++;

            continue;
        }
        else
        {
            AT_NORM_LOG("AT_Ipv4AddrAtoi: character not number nor dot, return ERROR");
            /*  */
            return VOS_ERR;
        }
    }

    /* 3'.' */
    if ( 3 != ulDotNum )
    {
        AT_NORM_LOG("AT_Ipv4AddrAtoi: dot number is not 3");
        return VOS_ERR;
    }

    /*  */
    if (ulValTmp > 255)
    {
        AT_NORM_LOG("AT_Ipv4AddrAtoi: last number is larger than 255");
        return VOS_ERR;
    }

    aucAddr[ulDotNum] = (VOS_UINT8)ulValTmp;

    TAF_MEM_CPY_S(pucNumber, TAF_IPV4_ADDR_LEN, aucAddr, 4);

    return VOS_OK;
}

/******************************************************************************
 : At_IPaddritoa
 : IPV4

 :
   pcString [out] IP,char * pcString="192.168.0.1"
   pucNumber [in] IP,char pucNumber[4]={192,168,0,1};

   :
    TODO: ...

 : TODO: ...
 : TODO: ...
     : /00064416 [2010-02-02]
******************************************************************************/
VOS_UINT32 AT_Ipv4AddrItoa(
    VOS_CHAR                           *pcString,
    VOS_UINT8                          *pucNumber
)
{
    VOS_UINT32                          ret = VOS_OK;
    VOS_CHAR                            astringTmp[8] = {0};

    if ( (VOS_NULL_PTR == pcString) || (VOS_NULL_PTR == pucNumber) )
    {
        ret = VOS_ERR;
    }
    else
    {
        TAF_MEM_SET_S(pcString, TAF_MAX_IPV4_ADDR_STR_LEN, 0x00, TAF_MAX_IPV4_ADDR_STR_LEN);
        VOS_sprintf_s(astringTmp, (VOS_SIZE_T)sizeof(astringTmp), "%d", pucNumber[0]);
        strncat(pcString, astringTmp, sizeof(astringTmp));

        VOS_sprintf_s(astringTmp, (VOS_SIZE_T)sizeof(astringTmp), ".%d", pucNumber[1]);
        strncat(pcString, astringTmp, sizeof(astringTmp));

        VOS_sprintf_s(astringTmp, (VOS_SIZE_T)sizeof(astringTmp), ".%d", pucNumber[2]);
        strncat(pcString, astringTmp, sizeof(astringTmp));

        VOS_sprintf_s(astringTmp, (VOS_SIZE_T)sizeof(astringTmp), ".%d", pucNumber[3]);
        strncat(pcString, astringTmp, sizeof(astringTmp));
    }

    return ret;
}

/*****************************************************************************
     : AT_Ipv4Addr2Str
   : IPV4
   : pucNumber      - IPV4
   : pcString       - 
     : VOS_UINT32
   :
   :

       :
  1.       : 20130808
           : Y00213812
       : VoLTE_PhaseI 

*****************************************************************************/
VOS_UINT32 AT_Ipv4Addr2Str(
    VOS_CHAR                           *pcString,
    VOS_UINT8                          *pucNumber
)
{
    VOS_CHAR                            astringTmp[8] = {0};

    if ( (VOS_NULL_PTR == pcString) || (VOS_NULL_PTR == pucNumber) )
    {
        return VOS_ERR;
    }

    TAF_MEM_SET_S(pcString, TAF_MAX_IPV4_ADDR_STR_LEN, 0x00, TAF_MAX_IPV4_ADDR_STR_LEN);

    /*  */
    if ((0 == pucNumber[0])
      &&(0 == pucNumber[1])
      &&(0 == pucNumber[2])
      &&(0 == pucNumber[3]))
    {
        return VOS_OK;
    }

    VOS_sprintf_s(astringTmp, (VOS_SIZE_T)sizeof(astringTmp), "%d", pucNumber[0]);
    strncat(pcString, astringTmp, sizeof(astringTmp));

    VOS_sprintf_s(astringTmp, (VOS_SIZE_T)sizeof(astringTmp), ".%d", pucNumber[1]);
    strncat(pcString, astringTmp, sizeof(astringTmp));

    VOS_sprintf_s(astringTmp, (VOS_SIZE_T)sizeof(astringTmp), ".%d", pucNumber[2]);
    strncat(pcString, astringTmp, sizeof(astringTmp));

    VOS_sprintf_s(astringTmp, (VOS_SIZE_T)sizeof(astringTmp), ".%d", pucNumber[3]);
    strncat(pcString, astringTmp, sizeof(astringTmp));

    return VOS_OK;
}

/******************************************************************************
     : AT_Ipv6AddrAtoi
   : IPV6
   : pcString - IP,char * pcString="192.168.0.1.13.23.56.24.192.168.0.1.13.23.56.24"
   : pucNumber - IP,char pucNumber[16]={192,168,0,1,13,23,56,24,192,168,0,1,13,23,56,24};
     : TAF_SUCCESS - 
             TAF_FAILURE - 
   :
   :

       :
  1.       : 20120112
           : f00179208
       : 

  2.       : 2013923
           : A00165503
       : UART-MODEM: 
******************************************************************************/
VOS_UINT32 AT_Ipv6AddrAtoi(
    VOS_CHAR                           *pcString,
    VOS_UINT8                          *pucNumber
)
{
    VOS_UINT32                          i = 0;
    VOS_UINT32                          ulStrLen = 0;
    VOS_UINT32                          ulNumLen = 0;
    VOS_UINT32                          ulDotNum = 0;
    VOS_UINT32                          ulValTmp = 0;
    VOS_UINT8                           aucAddr[TAF_IPV6_ADDR_LEN] = {0};


    if ( (VOS_NULL_PTR == pcString) || (VOS_NULL_PTR == pucNumber) )
    {
        return VOS_ERR;
    }

    ulStrLen = VOS_StrLen(pcString);

    if ( ulStrLen > VOS_StrLen("255.255.255.255.255.255.255.255.255.255.255.255.255.255.255.255") )
    {
        return VOS_ERR;
    }

    for ( i = 0; i < ulStrLen; i++ )
    {
        if ( (pcString[i] >= '0') && (pcString[i] <= '9') )
        {
            ulValTmp = (ulValTmp * 10) + (pcString[i] - '0');

            ulNumLen++;
            continue;
        }
        else if ( pcString[i] == '.' )
        {
            if ( (0 == ulNumLen) || (ulNumLen > 3) )
            {
                return VOS_ERR;
            }

            if ( ulValTmp > 255 )
            {
                return VOS_ERR;
            }

            aucAddr[ulDotNum] = (VOS_UINT8)ulValTmp;

            ulValTmp = 0;
            ulNumLen = 0;

            /* '.' */
            ulDotNum++;

            continue;
        }
        else
        {
            /*  */
            return VOS_ERR;
        }
    }

    /* 3'.' */
    if ((TAF_IPV6_ADDR_LEN - 1) != ulDotNum )
    {
        return VOS_ERR;
    }

    /*  */
    if (ulValTmp > 255)
    {
        return VOS_ERR;
    }

    aucAddr[ulDotNum] = (VOS_UINT8)ulValTmp;

    TAF_MEM_CPY_S(pucNumber, TAF_IPV6_ADDR_LEN, aucAddr, TAF_IPV6_ADDR_LEN);

    return VOS_OK;
}

/******************************************************************************
     : AT_LenStr2IpAddr
   : IPSMIP.V100R001
   : pucStr - IP
   : pucIpAddr - SMIP
     : TAF_SUCCESS - 
             TAF_FAILURE - 
   :
   :

       :
  1.       : 2010123
           : sunshaohua
       : 
******************************************************************************/
VOS_UINT32  AT_LenStr2IpAddr(
    VOS_UINT8                           *pucStr,
    VOS_UINT8                           *pucIpAddr
)
{
    VOS_UINT8 i;
    VOS_UINT8 j;
    VOS_UINT8 ucValue;

    i                = 0;
    j                = 0;
    ucValue          = 0;

    if (0 == pucStr[0])
    {
       /*ADDR0*/
        pucIpAddr[0] = 0;
        pucIpAddr[1] = 0;
        pucIpAddr[2] = 0;
        pucIpAddr[3] = 0;
        return AT_SUCCESS;
    }

    if (pucStr[0] == '.')
    {
        /*1'.'IP*/
        return AT_FAILURE;
    }

    for (i = 0; (i <= AT_AP_MAX_IPV4_ADDR_LEN) && (0 != pucStr[i]) ; i++)
    {
        /*1*/
        if (((pucStr[i] < 0x30) || (pucStr[i] > 0x39)) && (pucStr[i] != '.'))
        {
            /*'0'-'9'*/
            return AT_FAILURE;
        }
        if (pucStr[i] != '.')
        {
            /**/
            if (((ucValue * 10) + (pucStr[i] - 0x30)) <= 255)
            {
                /*IP*/
                ucValue = (TAF_UINT8)((ucValue * 10) + (pucStr[i] - 0x30));
            }
            else
            {
                /*255*/
                return AT_FAILURE;
            }
        }
        else
        {   /*'.'*/
            /*'.'*/
            if (j <= 3)
            {
               /*IPV4*/
                pucIpAddr[j] = ucValue;
                ucValue      = 0;

                /**/
                j++;
            }
            else
            {
                /*4IP*/
                return AT_FAILURE;
            }
        }
    }

    if (j == 3)
    {
        pucIpAddr[j] = ucValue;
        return AT_SUCCESS;
    }
    else
    {
        return AT_FAILURE;
    }
}

/*****************************************************************************
     : AT_Ipv6LenStrToAddrProc
   : IPSMIP(IPV6).
   : pucStr - IP
             pucColonCount - 
             pucDotCount   - 
   : pucIpAddr - SMIP
     : VOS_VOID
   :
   :

       :
  1.       : 2011510
           : x00180552
       : 

*****************************************************************************/
VOS_VOID AT_Ipv6LenStrToAddrProc(
    VOS_UINT8                          *pucStr,
    VOS_UINT8                          *pucIpAddr,
    VOS_UINT8                           ucColonCount,
    VOS_UINT8                           ucDotCount
)
{
    VOS_UINT8                           i;
    VOS_UINT8                           j;
    VOS_UINT16                          usValue;            /*Ipv6*/
    VOS_UINT8                           ucValue;            /*Ipv4*/

    usValue                             = 0;
    ucValue                             = 0;
    j                                   = 0;

    for (i = 0; ((i < TAF_MAX_IPV6_ADDR_COLON_STR_LEN) && ('\0' != pucStr[i])); i++)
    {
        if ((':' != pucStr[i]) && ('.' != pucStr[i]))
        {
            usValue <<= 4;

            if ((pucStr[i] >= '0') &&(pucStr[i] <= '9'))
            {
                /*  */
                usValue += (pucStr[i] - '0');
                ucValue  = (VOS_UINT8)((ucValue * 10) + (pucStr[i] - 0x30));
            }
            else
            {
                /*  */
                 usValue += (pucStr[i] - 'A' + 10);
            }
        }
        else if (':' == pucStr[i])
        {
            /* IPV6 */
            pucIpAddr[j] = (VOS_UINT8)((usValue >> 8) & 0x00FF);
            j++;
            /* IPV6 */
            pucIpAddr[j] = (VOS_UINT8)(usValue & 0x00FF);
            j++;
            usValue      = 0;
        }
        else
        {
            /* IPV4 */
            pucIpAddr[j] = ucValue;
            j++;
            ucValue      = 0;
        }
    }

    /*  */
    if (AT_MAX_IPV6_STR_COLON_NUM == ucColonCount)
    {
        pucIpAddr[j] = (VOS_UINT8)((usValue >> 8) & 0x00FF);
        j++;
        pucIpAddr[j] = (VOS_UINT8)(usValue & 0x00FF);
        j++;
    }

    if (AT_MAX_IPV6_STR_DOT_NUM == ucDotCount)
    {
        pucIpAddr[j] = ucValue;
        /* j++; */
    }

    return;
}

/******************************************************************************
     : AT_Ipv6LenStrToAddrProcCompressed
   : IPV6.
   : pucStr       - IP
             ucColonCount - 
             ucDotCount   - 
             ucStrlen     - 
             ucIdxPos     - 
   : pucIpAddr - IP
     : VOS_VOID
   :
   :

       :
  1.       : 2011510
           : x00180552
       : 
******************************************************************************/
VOS_VOID  AT_Ipv6LenStrToAddrProcCompressed(
    VOS_UINT8                          *pucStr,
    VOS_UINT8                           ucColonCount,
    VOS_UINT8                           ucDotCount,
    VOS_UINT8                           ucStrlen,
    VOS_UINT8                           ucIdxPos
)
{
    VOS_UINT8                           i;

    /*  */
    for (i = ucStrlen; i >= ucIdxPos; i--)
    {
        if (AT_MAX_IPV6_STR_DOT_NUM != ucDotCount)
        {
            pucStr[i + AT_MAX_IPV6_STR_COLON_NUM - ucColonCount] =  pucStr[i];
        }
        else
        {
            pucStr[i + AT_MAX_IPV4V6_STR_COLON_NUM - ucColonCount] =  pucStr[i];
        }
    }

    /*  */
    if (AT_MAX_IPV6_STR_DOT_NUM != ucDotCount)
    {
        for (i = ucIdxPos; i < (ucIdxPos + AT_MAX_IPV6_STR_COLON_NUM - ucColonCount); i++)
        {
            pucStr[i + 1] =  ':';
        }
    }
    else
    {
        for (i = ucIdxPos; i < (ucIdxPos + AT_MAX_IPV4V6_STR_COLON_NUM - ucColonCount); i++)
        {
            pucStr[i + 1] =  ':';
        }
    }

    return;
}

/*****************************************************************************
     : AT_Ipv6LenStrToAddrAccess
   : IPV6
   : pucStr        - IP
   : pucColonCount - 
             pucDotCount   - 
             pucStrlen     - IPV6
             pucIdxPos     - 
     : VOS_OK - 
             VOS_ERR - 
   :
   :

       :
  1.       : 201169
           : x00180552
       : 

*****************************************************************************/
VOS_UINT32 AT_Ipv6LenStrToAddrAccess(
    VOS_UINT8                          *pucStr,
    VOS_UINT8                          *pucColonCount,
    VOS_UINT8                          *pucDotCount,
    VOS_UINT8                          *pucStrlen,
    VOS_UINT8                          *pucIdxPos
)
{
    VOS_UINT32                          i;

    for (i = 0; ((i < TAF_MAX_IPV6_ADDR_COLON_STR_LEN) && ('\0' != pucStr[i])); i++)
    {
        if ( (pucStr[i] < '0' || pucStr[i] > '9')
          && (pucStr[i] < 'A' || pucStr[i] > 'F')
          && ('.' != pucStr[i])
          && (':' != pucStr[i]) )
        {
            return VOS_ERR;
        }
        /*  */
        if ((i > 0)
         && (':' == pucStr[i - 1])
         && (':' == pucStr[i]))
        {
            *pucIdxPos = (VOS_UINT8)i;
        }

        /*  */
        if (':' == pucStr[i])
        {
            (*pucColonCount)++;
        }

        /**/
        if ('.' == pucStr[i])
        {
            (*pucDotCount)++;
        }
    }

    *pucStrlen = (VOS_UINT8)i;

    return VOS_OK;
}

/******************************************************************************
     : AT_Ipv6LenStrToAddr
   : IPSMIP(IPV6).
   : pucStr - IP
   : pucIpAddr - SMIP
     : VOS_OK  - 
             VOS_ERR - 
   :
   :

       :
  1.       : 2011509
           : x00180552
       : 
  2.       : 20151226
           : f00179208
       : Coverity
******************************************************************************/
VOS_UINT32  AT_Ipv6LenStrToAddr(
    VOS_UINT8                          *pucStr,
    VOS_UINT8                          *pucIpAddr
)
{
    VOS_UINT8                           ucColonCount;       /*  */
    VOS_UINT8                           ucDotCount;         /*  */
    VOS_UINT8                           ucStrlen;           /*  */
    VOS_UINT8                           ucIdxPos;           /*  */
    VOS_UINT8                           pucStrTmp[TAF_MAX_IPV6_ADDR_COLON_STR_LEN];

    TAF_MEM_SET_S(pucStrTmp, sizeof(pucStrTmp), 0x00, TAF_MAX_IPV6_ADDR_COLON_STR_LEN);

    TAF_MEM_CPY_S(pucStrTmp, sizeof(pucStrTmp), pucStr, TAF_MAX_IPV6_ADDR_COLON_STR_LEN);
    ucColonCount                        = 0;
    ucDotCount                          = 0;
    ucStrlen                            = 0;
    ucIdxPos                            = 0;

    /* IPV6 */
    if (VOS_OK != AT_Ipv6LenStrToAddrAccess(pucStrTmp, &ucColonCount,
                                           &ucDotCount, &ucStrlen, &ucIdxPos))
    {
        return VOS_ERR;
    }

    /*  */
    if (ucStrlen == 0)
    {
        return VOS_ERR;
    }

    /* 73 */
    if ( (ucColonCount > AT_MAX_IPV6_STR_COLON_NUM)
      || ((AT_MAX_IPV6_STR_DOT_NUM != ucDotCount) && (0 != ucDotCount)) )
    {
        return VOS_ERR;
    }

    if ( (AT_MAX_IPV6_STR_COLON_NUM == ucColonCount)
      || ( (AT_MAX_IPV4V6_STR_COLON_NUM == ucColonCount)
        && (AT_MAX_IPV6_STR_DOT_NUM == ucDotCount) ) )
    {
        /*  */
        AT_Ipv6LenStrToAddrProc(pucStrTmp, pucIpAddr, ucColonCount, ucDotCount);
    }
    else
    {
        /*  */
        AT_Ipv6LenStrToAddrProcCompressed(pucStrTmp, ucColonCount, ucDotCount, ucStrlen, ucIdxPos);
        if (ucDotCount != AT_MAX_IPV6_STR_DOT_NUM)
        {
            /* IPV4IPV6 */
            AT_Ipv6LenStrToAddrProc(pucStrTmp, pucIpAddr, AT_MAX_IPV6_STR_COLON_NUM, ucDotCount);
        }
        else
        {
            /* IPV4IPV6 */
            AT_Ipv6LenStrToAddrProc(pucStrTmp, pucIpAddr, AT_MAX_IPV4V6_STR_COLON_NUM, ucDotCount);
        }
    }

    return VOS_OK;
}

/*****************************************************************************
     : AT_PcscfIpv4Addr2Str
   : IPV4
   : pucNumber      - IPV4
   : pcString       - 
     : VOS_UINT32
   :
   :

       :
  1.       : 201672
           : z00359541
       : 
*****************************************************************************/
VOS_VOID AT_PcscfIpv4Addr2Str(
    VOS_CHAR                           *pcString,
    VOS_UINT8                          *pucNumber
)
{
    VOS_CHAR                            astringTmp[8] = {0};

    TAF_MEM_SET_S(pcString, TAF_MAX_IPV4_ADDR_STR_LEN, 0, TAF_MAX_IPV4_ADDR_STR_LEN);

    VOS_sprintf_s(astringTmp, (VOS_SIZE_T)sizeof(astringTmp), "%d", pucNumber[0]);
    strncat(pcString, astringTmp, sizeof(astringTmp));

    VOS_sprintf_s(astringTmp, (VOS_SIZE_T)sizeof(astringTmp), ".%d", pucNumber[1]);
    strncat(pcString, astringTmp, sizeof(astringTmp));

    VOS_sprintf_s(astringTmp, (VOS_SIZE_T)sizeof(astringTmp), ".%d", pucNumber[2]);
    strncat(pcString, astringTmp, sizeof(astringTmp));

    VOS_sprintf_s(astringTmp, (VOS_SIZE_T)sizeof(astringTmp), ".%d", pucNumber[3]);
    strncat(pcString, astringTmp, sizeof(astringTmp));
}

/*****************************************************************************
     : AT_PcscfIpv6StrToAddr
   : P-CSCF IPSMIP(IPV6).
   : pucStr - IP
             pucColonCount - 
             pucDotCount   - 
   : pucIpAddr - SMIP
     : VOS_VOID
   :
   :

       :
  1.       : 2016629
           : z00359541
       : 

*****************************************************************************/
VOS_UINT32 AT_PcscfIpv6StrToAddr(
    VOS_UINT8                          *pucStr,
    VOS_UINT8                          *pucIpAddr,
    VOS_UINT8                           ucColonCount
)
{
    VOS_UINT8                           i;
    VOS_UINT8                           j;
    VOS_UINT16                          usValue;            /*Ipv6*/
    VOS_UINT8                           ucValue;            /*Ipv4*/
    VOS_UINT32                          ulNumLen;

    usValue                             = 0;
    ucValue                             = 0;
    j                                   = 0;
    ulNumLen                            = 0;

    if ((VOS_NULL_PTR == pucStr)
     || (VOS_NULL_PTR == pucIpAddr))
    {
        AT_NORM_LOG("AT_PcscfIpv6StrToAddr: input ptr is NULL, return ERROR");
        return VOS_ERR;
    }

    for (i = 0; ((i < TAF_MAX_IPV6_ADDR_COLON_STR_LEN) && ('\0' != pucStr[i])); i++)
    {
        /*  */
        if (':' != pucStr[i])
        {
            usValue <<= 4;

            if ((pucStr[i] >= '0') &&(pucStr[i] <= '9'))
            {
                /*  */
                usValue += (pucStr[i] - '0');
                ucValue  = (VOS_UINT8)((ucValue * 10) + (pucStr[i] - 0x30));
            }
            else
            {
                /*  */
                 usValue += ((pucStr[i] - 'A') + 10);
            }

            ulNumLen++;
        }
        /*  */
        else
        {
            /* 4 */
            if (4 < ulNumLen)
            {
                AT_ERR_LOG("AT_PcscfIpv6StrToAddr: the number of char betwwen colons is more than 4, return ERROR");
                return VOS_ERR;
            }

            /* IPV6 */
            pucIpAddr[j] = (VOS_UINT8)((usValue >> 8) & 0x00FF);
            j++;
            /* IPV6 */
            pucIpAddr[j] = (VOS_UINT8)(usValue & 0x00FF);
            j++;
            usValue      = 0;
            ulNumLen     = 0;
        }
    }

    /*  */
    if (AT_MAX_IPV6_STR_COLON_NUM == ucColonCount)
    {
        pucIpAddr[j] = (VOS_UINT8)((usValue >> 8) & 0x00FF);
        j++;
        pucIpAddr[j] = (VOS_UINT8)(usValue & 0x00FF);
        j++;
    }

    return VOS_OK;
}

/*****************************************************************************
     : AT_PortAtoI
   : 
   : pString 
   : pValue  
     : VOS_ERR(), VOS_OK()
   :
   :

       :
  1.       : 20160618
           : z00359541
       : 
*****************************************************************************/
VOS_UINT32  AT_PortAtoI(
    VOS_CHAR                           *pcString,
    VOS_UINT32                         *pulValue
)
{
    VOS_CHAR                           *pucTmp;
    VOS_UINT32                          ulRet;

    if ((VOS_NULL_PTR == pcString)
     || (VOS_NULL_PTR == pulValue))
    {
        AT_ERR_LOG("AT_PortAtoI: pcString or pulValue is NULL, return ERROR");
        return VOS_ERR;
    }

    pucTmp  = pcString;
    ulRet   = 0;

    *pulValue = 0;

    for (pucTmp = pcString; *pucTmp != '\0'; pucTmp++)
    {
        /* , */
        if (('0' > *pucTmp) || ('9' < *pucTmp))
        {
            AT_ERR_LOG("AT_PortAtoI: Not all number type in pcString , return ERROR");
            return VOS_ERR;
        }

        ulRet = (ulRet * 10) + (*pucTmp - '0');

        if (IMS_PCSCF_ADDR_PORT_MAX < ulRet)
        {
            AT_ERR_LOG("AT_PortAtoI: Port number is larger than 65535, return ERROR");
            return VOS_ERR;
        }
    }

    if ((0 < ulRet)
     && (IMS_PCSCF_ADDR_PORT_MAX >= ulRet))
    {
        *pulValue = (VOS_UINT32)ulRet;

        return VOS_OK;
    }

    AT_ERR_LOG("AT_PortAtoI: return ERROR");
    return VOS_ERR;
}

/******************************************************************************
     : AT_CheckPcscfIpv6Addr
   : PCSCF IPV6
   : pucIpv6Addr - IP
   : pulPortExistFlg - 
     : VOS_OK  - 
             VOS_ERR - 
   :
   :

       :
  1.       : 2016620
           : z00359541
       : 
******************************************************************************/
VOS_UINT32 AT_CheckPcscfIpv6Addr(
    VOS_CHAR                           *pucIpv6Str,
    VOS_UINT32                         *pulPortExistFlg
)
{
    VOS_CHAR                           *pucIpv6Start = VOS_NULL_PTR;
    VOS_CHAR                           *pucIpv6End   = VOS_NULL_PTR;

    if ((VOS_NULL_PTR == pucIpv6Str)
     || (VOS_NULL_PTR == pulPortExistFlg))
    {
        AT_NORM_LOG("AT_CheckPcscfIpv6Addr: input ptr is NULL, return ERROR");
        return VOS_ERR;
    }

    pucIpv6End   = VOS_StrStr(pucIpv6Str, "]");
    pucIpv6Start = VOS_StrStr(pucIpv6Str, "[");

    if ((VOS_NULL_PTR == pucIpv6End)
     && (VOS_NULL_PTR == pucIpv6Start))
    {
        AT_NORM_LOG("AT_CheckPcscfIpv6Addr: NO [ ] symbol in IPV6 addr, port not exists");
        *pulPortExistFlg = VOS_FALSE;
        return VOS_OK;
    }

    if ((VOS_NULL_PTR != pucIpv6End)
     && (VOS_NULL_PTR != pucIpv6Start)
     && (pucIpv6End > pucIpv6Start))
    {
        if ((pucIpv6End - pucIpv6Start) > TAF_MAX_IPV6_ADDR_COLON_STR_LEN)
        {
            AT_ERR_LOG("AT_CheckPcscfIpv6Addr: length of IPV6 addr in [] is larger than 39, return ERROR");
            return VOS_ERR;
        }

        AT_NORM_LOG("AT_CheckPcscfIpv6Addr: Have both [ ] symbol in IPV6 addr");
        *pulPortExistFlg = VOS_TRUE;

        return VOS_OK;
    }

    AT_ERR_LOG("AT_CheckPcscfIpv6Addr: IPV6 addr format incorrect");
    return VOS_ERR;
}


/******************************************************************************
     : AT_ParsePortFromPcscfIpv6Addr
   : PCSCF IPV6.
   : pucStr - PCSCF IPV6
   : pucIpv6Addr - IP
             pulPortExistFlg - 
             pulPortNum - 
     : VOS_OK  - 
             VOS_ERR - 
   :
   :

       :
  1.       : 2016620
           : z00359541
       : 
******************************************************************************/
VOS_UINT32  AT_ParsePortFromPcscfIpv6Addr(
    VOS_UINT8                          *pucStr,
    VOS_UINT8                          *pucIpv6Addr,
    VOS_UINT32                         *pulPortExistFlg,
    VOS_UINT32                         *pulPortNum

)
{
    VOS_CHAR                           *pucIpv6Start = VOS_NULL_PTR;
    VOS_CHAR                           *pucIpv6End   = VOS_NULL_PTR;
    VOS_CHAR                           *pucIpv6Str   = VOS_NULL_PTR;
    VOS_CHAR                           *pcStrPort    = VOS_NULL_PTR;

    if ((VOS_NULL_PTR == pucStr)
     || (VOS_NULL_PTR == pucIpv6Addr)
     || (VOS_NULL_PTR == pulPortExistFlg)
     || (VOS_NULL_PTR == pulPortNum))
    {
        AT_ERR_LOG("AT_ParsePortFromPcscfIpv6Addr: input ptr is NULL, return ERROR");
        return VOS_ERR;
    }

    if (VOS_OK != AT_CheckPcscfIpv6Addr((VOS_CHAR*)pucStr, pulPortExistFlg))
    {
        AT_ERR_LOG("AT_ParsePortFromPcscfIpv6Addr: AT_CheckPcscfIpv6Addr FAIL, return ERROR");
        return VOS_ERR;
    }

    /* [ipv6]:portipv6 */
    pucIpv6Str   = (VOS_CHAR*)pucStr;
    pucIpv6End   = VOS_StrStr(pucIpv6Str, "]");
    pucIpv6Start = VOS_StrStr(pucIpv6Str, "[");

    if (VOS_TRUE == *pulPortExistFlg)
    {
        /* IPV6 */
        TAF_MEM_CPY_S(pucIpv6Addr, TAF_MAX_IPV6_ADDR_COLON_STR_LEN, pucIpv6Start + 1, (VOS_UINT32)((pucIpv6End - pucIpv6Start) - 1));

        /*  */
        pcStrPort = VOS_StrStr(pucIpv6End, ":");

        /* [ipv6]:portERROR*/
        if (VOS_NULL_PTR == pcStrPort)
        {
            *pulPortExistFlg = VOS_FALSE;
            AT_ERR_LOG("AT_ParsePortFromPcscfIpv6Addr: IPV6 Port colon missed, return ERROR ");
            return VOS_ERR;
        }

        /* "]"ERROR */
        if (pcStrPort != pucIpv6End + 1)
        {
            *pulPortExistFlg = VOS_FALSE;
            AT_ERR_LOG("AT_ParsePortFromPcscfIpv6Addr: IPV6 Port colon location incorrect, return ERROR ");
            return VOS_ERR;
        }

        /* [ipv6]:portERROR*/
        if (VOS_OK != AT_PortAtoI(pcStrPort+1, pulPortNum))
        {
            *pulPortExistFlg = VOS_FALSE;
            AT_ERR_LOG("AT_ParsePortFromPcscfIpv6Addr: IPV6 Port decode ERROR");
            return VOS_ERR;
        }

        *pulPortExistFlg = VOS_TRUE;
    }
    else
    {
        /* IPV6 */
        TAF_MEM_CPY_S(pucIpv6Addr, TAF_MAX_IPV6_ADDR_COLON_STR_LEN, pucStr, TAF_MAX_IPV6_ADDR_COLON_STR_LEN);
    }

    return VOS_OK;
}

/******************************************************************************
     : AT_ParsePortFromPcscfIpv6Addr
   : PCSCF IPV6.
   : pucStr - IP
   : pucIpAddr - SMIP
     : VOS_OK  - 
             VOS_ERR - 
   :
   :

       :
  1.       : 2016620
           : z00359541
       : 
******************************************************************************/
VOS_UINT32  AT_ParseAddrFromPcscfIpv6Addr(
    VOS_UINT8                          *pucStr,
    VOS_UINT8                          *pucIpAddr
)
{
    VOS_UINT8                           ucColonCount;       /*  */
    VOS_UINT8                           ucDotCount;         /*  */
    VOS_UINT8                           ucStrlen;           /*  */
    VOS_UINT8                           ucIdxPos;           /*  */
    VOS_UINT32                          ulResult;

    ucColonCount = 0;
    ucDotCount   = 0;
    ucStrlen     = 0;
    ucIdxPos     = 0xFF;

    if ((VOS_NULL_PTR == pucStr)
     || (VOS_NULL_PTR == pucIpAddr))
    {
        AT_NORM_LOG("AT_ParseAddrFromPcscfIpv6Addr: input ptr is NULL, return ERROR");
        return VOS_ERR;
    }

    /* IPV6 */
    if (VOS_OK != AT_Ipv6LenStrToAddrAccess(pucStr, &ucColonCount, &ucDotCount, &ucStrlen, &ucIdxPos))
    {
        AT_ERR_LOG("AT_ParseAddrFromPcscfIpv6Addr: AT_Ipv6LenStrToAddrAccess FAIL, return ERROR");
        return VOS_ERR;
    }

    /* IPV4IPV6 */
    if (0 != ucDotCount)
    {
        AT_ERR_LOG("AT_ParseAddrFromPcscfIpv6Addr: There have dot symbol in address format, return ERROR");
        return VOS_ERR;
    }

    /*  */
    if (0 == ucStrlen)
    {
        AT_ERR_LOG("AT_ParseAddrFromPcscfIpv6Addr: IP address length is 0, return ERROR");
        return VOS_ERR;
    }

    /* 7 */
    if (ucColonCount > AT_MAX_IPV6_STR_COLON_NUM)
    {
        AT_ERR_LOG("AT_ParseAddrFromPcscfIpv6Addr: IPV6 address Colon number is larger than 7, return ERROR");
        return VOS_ERR;
    }

    if (AT_MAX_IPV6_STR_COLON_NUM == ucColonCount)
    {
        /*  */
        ulResult = AT_PcscfIpv6StrToAddr(pucStr, pucIpAddr, ucColonCount);
    }
    else
    {
        if (0xFF != ucIdxPos)
        {
            /*  */
            AT_Ipv6LenStrToAddrProcCompressed(pucStr, ucColonCount, ucDotCount, ucStrlen, ucIdxPos);
            /* IPV6 */
            ulResult = AT_PcscfIpv6StrToAddr(pucStr, pucIpAddr, AT_MAX_IPV6_STR_COLON_NUM);
        }
        /* IPV6 */
        else
        {
            AT_ERR_LOG("AT_ParseAddrFromPcscfIpv6Addr: Can not find two consecutive colons in compressed IPV6 address , return ERROR");
            return VOS_ERR;
        }
    }

    return ulResult;
}

/******************************************************************************
     : AT_Ipv6PcscfDataToAddr
   : IPSMIP(IPV6)
             .
   : pucStr - IP
   : pucIpAddr - SMIP
             pulPortExistFlg - 
             pulPortNum - 
     : VOS_OK  - 
             VOS_ERR - 
   :
   :

       :
  1.       : 2016620
           : z00359541
       : 
******************************************************************************/
VOS_UINT32  AT_Ipv6PcscfDataToAddr(
    VOS_UINT8                          *pucStr,
    VOS_UINT8                          *pucIpAddr,
    VOS_UINT32                         *pulPortExistFlg,
    VOS_UINT32                         *pulPortNum

)
{
    VOS_UINT8                           pucStrTmp[TAF_MAX_IPV6_ADDR_COLON_STR_LEN];

    TAF_MEM_SET_S(pucStrTmp, TAF_MAX_IPV6_ADDR_COLON_STR_LEN, 0, TAF_MAX_IPV6_ADDR_COLON_STR_LEN);

    if ((VOS_NULL_PTR == pucStr)
     || (VOS_NULL_PTR == pucIpAddr)
     || (VOS_NULL_PTR == pulPortExistFlg)
     || (VOS_NULL_PTR == pulPortNum))
    {
        AT_NORM_LOG("AT_Ipv6PcscfDataToAddr: input ptr is NULL, return ERROR");
        return VOS_ERR;
    }

    if (VOS_OK != AT_ParsePortFromPcscfIpv6Addr(pucStr, pucStrTmp, pulPortExistFlg, pulPortNum))
    {
        AT_ERR_LOG("AT_Ipv6PcscfDataToAddr: AT_ParsePortFromPcscfIpv6Addr FAIL, return ERROR");
        return VOS_ERR;
    }

    /* IPV6 */
    VOS_StrToUpper((VOS_CHAR*)pucStrTmp);

    if (VOS_OK != AT_ParseAddrFromPcscfIpv6Addr(pucStrTmp, pucIpAddr))
    {
        AT_ERR_LOG("AT_Ipv6PcscfDataToAddr: AT_ParseAddrFromPcscfIpv6Addr FAIL, return ERROR");
        return VOS_ERR;
    }

    return VOS_OK;
}


/*****************************************************************************
     : AT_Ipv6AddrToStr
   : IPV6
   : aucIpAddr[]    - IPV6()
             enIpStrType    - IPV6
   : aucAddrStr[]   - IPV6()
     : VOS_OK         - 
             VOS_ERR        - 
   :
   :

       :
  1.       : 20120109
           : l00198894
       : 

*****************************************************************************/
VOS_UINT32 AT_Ipv6AddrToStr(
    VOS_UINT8                           aucAddrStr[],
    VOS_UINT8                           aucIpAddr[],
    AT_IPV6_STR_TYPE_ENUM_UINT8         enIpStrType
)
{
    VOS_UINT8                          *pucBuffer;
    VOS_UINT16                          ausAddrValue[AT_IPV6_STR_MAX_TOKENS];
    VOS_UINT16                          usAddrNum;
    VOS_UINT8                           ucDelimiter;
    VOS_UINT8                           ucTokensNum;
    VOS_UINT8                           ucRadix;
    VOS_UINT32                          i;

    pucBuffer                           = aucAddrStr;

    TAF_MEM_SET_S(ausAddrValue, sizeof(ausAddrValue), 0x00, sizeof(ausAddrValue));

    /* IP,  */
    switch (enIpStrType)
    {
        case AT_IPV6_STR_TYPE_HEX:
            ucDelimiter = AT_IPV6_STR_DELIMITER;
            ucTokensNum = 8;
            ucRadix     = 16;
            break;

        case AT_IPV6_STR_TYPE_DEC:
            ucDelimiter = AT_IPV4_STR_DELIMITER;
            ucTokensNum = 16;
            ucRadix     = 10;
            break;

        default:
            return VOS_ERR;
    }

    /* IP, IP */
    for (i = 0; i < ucTokensNum; i++)
    {
        usAddrNum = *aucIpAddr++;

        if (AT_IPV6_STR_TYPE_HEX == enIpStrType)
        {
            usAddrNum <<= 8;
            usAddrNum  |= *aucIpAddr++;
        }

        ausAddrValue[i] = usAddrNum;
    }

    /* IP, IP */
    for (i=0; i < ucTokensNum; i++)
    {
        pucBuffer    = (VOS_UINT8*)AT_Itoa(ausAddrValue[i],
                                               (VOS_CHAR*)pucBuffer,
                                               ucRadix,
                                               (TAF_MAX_IPV6_ADDR_DOT_STR_LEN - (VOS_UINT32)(aucAddrStr - pucBuffer)));
        *pucBuffer++ = ucDelimiter;
    }

    /* ,  */
    if (aucAddrStr != pucBuffer)
    {
        *(--pucBuffer) = '\0';
    }

    return VOS_OK;
}

/*****************************************************************************
     : AT_CalcIpv6PrefixLength
   : ATTFTLocal IPV6
   : VOS_UINT8                   *pucLocalIpv6Mask
   : 
     : VOS_UINT8
   :
   :

       :
  1.       : 20151021
           : w00316404
       : 

*****************************************************************************/
VOS_UINT8 AT_CalcIpv6PrefixLength(VOS_UINT8 *pucLocalIpv6Mask)
{
    VOS_UINT32                          i                   = 0;
    VOS_UINT8                           j                   = 0;
    VOS_UINT8                           ucMaskLength        = 0;

    if ( VOS_NULL_PTR == pucLocalIpv6Mask )
    {
        return ucMaskLength;
    }

    for(i = 0; i < AT_IPV6_STR_MAX_TOKENS; i++)
    {
        if (0xFF == *(pucLocalIpv6Mask + i))
        {
            ucMaskLength = ucMaskLength + 8;
        }
        else
        {
            for (j = 0; j < 8; j++)
            {
                if (0 != ((*(pucLocalIpv6Mask + i)) & ((VOS_UINT32)1 << (7 - j))))
                {
                    ucMaskLength ++;
                }
                else
                {
                    break;
                }
            }
            break;
        }
    }

    return ucMaskLength;
}

/*****************************************************************************
     : AT_GetIpv6MaskByPrefixLength
   : Local IPV6Local IPV6 Mask
   : VOS_UINT8                   *ucLocalIpv6Prefix
   : VOS_UINT8                   *pucLocalIpv6Mask
     : VOS_VOID
   :
   :

       :
  1.       : 20151021
           : w00316404
       : 

*****************************************************************************/
VOS_VOID AT_GetIpv6MaskByPrefixLength(VOS_UINT8 ucLocalIpv6Prefix, VOS_UINT8 *pucLocalIpv6Mask)
{
    VOS_UINT8                           ucNum                   = 0;
    VOS_UINT8                           i                       = 0;

    ucNum = ucLocalIpv6Prefix/8;

    if ( VOS_NULL_PTR == pucLocalIpv6Mask )
    {
        return;
    }

    for (i = 0; i < ucNum; i ++)
    {
        *(pucLocalIpv6Mask + i) = 0xFF;
    }

    ucNum = ucLocalIpv6Prefix % 8;

    if (0 != ucNum)
    {
        *(pucLocalIpv6Mask + i) = 0xFF & ((VOS_UINT32)0xFF << (8 - ucNum));

    }

    return;
}

/*****************************************************************************
     : AT_Itoa
   : (1016), ASCII, 
   : usValue    - ASCII
             pcStr      - 
             usRadix    - 
   : 
     : VOS_CHAR*
   :
   :

       :
  1.       : 201167
           : A00165503
       : 

*****************************************************************************/
VOS_CHAR* AT_Itoa(
    VOS_UINT16                          usValue,
    VOS_CHAR                           *pcStr,
    VOS_UINT16                          usRadix,
    VOS_UINT32                          ulLength
)
{
    if (usRadix == 16)
    {
        pcStr += VOS_sprintf_s(pcStr, ulLength, "%x", usValue);
    }
    else if(usRadix == 10)
    {
        pcStr += VOS_sprintf_s(pcStr, ulLength, "%d", usValue);
    }
    else
    {
    }
    return pcStr;
}

/*****************************************************************************
     : AT_FindIpv6AddrZeroFieldsToBeCompressed
   : "::"IP
   : ausAddrValue[]     - IPV6
             ucTokensNum        - 
   : pucZeroFieldStart  - 0IP
             pucZeroFieldCount  - 0IP
     : VOS_OK             - 
             VOS_ERR            - 
   :
   :

       :
  1.       : 201169
           : A00165503
       : 

*****************************************************************************/
VOS_UINT32 AT_FindIpv6AddrZeroFieldsToBeCompressed(
    VOS_UINT8                          *pucZeroFieldStart,
    VOS_UINT8                          *pucZeroFieldCount,
    VOS_UINT16                          ausAddrValue[],
    VOS_UINT8                           ucTokensNum
)
{
    VOS_UINT8                           ucStart;
    VOS_UINT8                           ucCount;
    VOS_UINT8                           i;

    ucStart                             = 0xFF;
    ucCount                             = 0;

    for (i = 0; i < ucTokensNum - 1; i++)
    {
        if ( (0x0000 == ausAddrValue[i])
          && (0x0000 == ausAddrValue[i + 1]) )
        {
            /* 0IP */
            if (0xFF == ucStart)
            {
                ucStart = i;
            }

            /* 0IP */
            ucCount++;
        }
        else
        {
            /* IP, IP */
            if (0xFF != ucStart)
            {
                if (ucCount > *pucZeroFieldCount)
                {
                    *pucZeroFieldStart = ucStart;
                    *pucZeroFieldCount = ucCount;
                }

                ucStart = 0xFF;
                ucCount = 0;
            }
        }
    }

    /* 0IP, IP,
       IP */
    if (0xFF != ucStart)
    {
        if (ucCount > *pucZeroFieldCount)
        {
            *pucZeroFieldStart = ucStart;
            *pucZeroFieldCount = ucCount;
        }
    }

    return VOS_OK;
}

/*****************************************************************************
     : AT_ConvertIpv6AddrToCompressedStr
   : IPV6
   : aucIpAddr[]    - IPV6()
             ucTokensNum    - 
   : aucAddrStr[]   - IPV6()
     : VOS_OK         - 
             VOS_ERR        - 
   :
   :

       :
  1.       : 201169
           : A00165503
       : 

*****************************************************************************/
VOS_UINT32 AT_ConvertIpv6AddrToCompressedStr(
    VOS_UINT8                           aucAddrStr[],
    VOS_UINT8                           aucIpAddr[],
    VOS_UINT8                           ucTokensNum
)
{
    VOS_UINT8                          *pucBuffer;
    VOS_UINT16                          ausAddrValue[8]; /*TAF_IPV6_STR_RFC2373_TOKENS]; */
    VOS_UINT16                          usAddrNum;
    VOS_UINT8                           ucDelimiter;
    VOS_UINT8                           ucRadix;
    VOS_UINT8                           ucZeroFieldStart;
    VOS_UINT8                           ucZeroFieldCount;
    VOS_UINT8                           i;

    TAF_MEM_SET_S(ausAddrValue, sizeof(ausAddrValue), 0x00, sizeof(ausAddrValue));

    pucBuffer                           = aucAddrStr;
    ucDelimiter                         = TAF_IPV6_STR_DELIMITER;
    ucRadix                             = 16;
    ucZeroFieldStart                    = 0xFF;
    ucZeroFieldCount                    = 0;

    /* IP, IP */
    for (i = 0; i < ucTokensNum; i++)
    {
        usAddrNum = *aucIpAddr++;

        usAddrNum <<= 8;
        usAddrNum  |= *aucIpAddr++;

        ausAddrValue[i] = usAddrNum;
    }

    /* "::"IP  */
    AT_FindIpv6AddrZeroFieldsToBeCompressed(&ucZeroFieldStart,
                                            &ucZeroFieldCount,
                                            ausAddrValue,
                                            ucTokensNum);

    /* IP, IP */
    for (i=0; i < ucTokensNum; i++)
    {
        if (ucZeroFieldStart == i)
        {
            *pucBuffer++ = ucDelimiter;

            i += ucZeroFieldCount;

            /* IP,  */
            if ((ucTokensNum - 1) == i)
            {
                *pucBuffer++ = ucDelimiter;
            }
        }
        else
        {
            /* IP,  */
            if (0 != i)
            {
                *pucBuffer++ = ucDelimiter;
            }
            pucBuffer    = (VOS_UINT8*)AT_Itoa(ausAddrValue[i],
                                               (VOS_CHAR*)pucBuffer,
                                               ucRadix,
                                               (TAF_MAX_IPV6_ADDR_COLON_STR_LEN - (VOS_UINT32)(aucAddrStr - pucBuffer)));
        }
    }

    /*  */
    if (aucAddrStr != pucBuffer)
    {
        *pucBuffer = '\0';
    }

    return VOS_OK;
}

/*****************************************************************************
     : AT_CalcIpHdrCRC16
   : IPCRC
   : pucData    - IP
             usSize     - IP
   : 
     : ulCheckSum - CRC
   :
   :

       :
  1.       : 2012612
           : A00165503
       : 

*****************************************************************************/
VOS_UINT16 AT_CalcIpHdrCRC16(
    VOS_UINT8                          *pucData,
    VOS_UINT16                          usSize
)
{
    VOS_UINT16                         *pusBuffer;
    VOS_UINT32                          ulCheckSum;

    pusBuffer    = (VOS_UINT16 *)pucData;
    ulCheckSum = 0;

    while (usSize > 1)
    {
        ulCheckSum += *pusBuffer++;
        usSize     -= sizeof(VOS_UINT16);
    }

    if (usSize)
    {
        ulCheckSum += *(VOS_UINT8 *)pusBuffer;
    }

    ulCheckSum  = (ulCheckSum >> 16) + (ulCheckSum & 0xffff);
    ulCheckSum += (ulCheckSum >> 16);

    return (VOS_UINT16)(~ulCheckSum);
}

/*****************************************************************************
     : AT_BuildUdpHdr
   : IPUDP(UDP)
   : pstUdpPkt  - UDP
             usLen      - UDP
             ulSrcAddr  - IP
             ulDstAddr  - IP
             usSrcPort  - 
             usDstPort  - 
   : 
     : VOS_OK     - 
             VOS_ERR    - 
   :
   :

       :
  1.       : 2012612
           : A00165503
       : 

*****************************************************************************/
VOS_UINT32 AT_BuildUdpHdr(
    AT_UDP_PACKET_FORMAT_STRU          *pstUdpPkt,
    VOS_UINT16                          usLen,
    VOS_UINT32                          ulSrcAddr,
    VOS_UINT32                          ulDstAddr,
    VOS_UINT16                          usSrcPort,
    VOS_UINT16                          usDstPort
)
{
    static VOS_UINT16                   usIdentification = 0;

    /*  */
    if (VOS_NULL_PTR == pstUdpPkt)
    {
        return VOS_ERR;
    }

    /* IP */
    pstUdpPkt->stIpHdr.ucIpVer          = AT_IP_VERSION;
    pstUdpPkt->stIpHdr.ucIpHdrLen       = 5;
    pstUdpPkt->stIpHdr.ucServiceType    = 0x00;
    pstUdpPkt->stIpHdr.usTotalLen       = VOS_HTONS(usLen + AT_IP_HDR_LEN + AT_UDP_HDR_LEN);
    pstUdpPkt->stIpHdr.usIdentification = VOS_HTONS(usIdentification);
    pstUdpPkt->stIpHdr.usOffset         = 0;
    pstUdpPkt->stIpHdr.ucTTL            = AT_IP_DEF_TTL;
    pstUdpPkt->stIpHdr.ucProtocol       = AT_IPPROTO_UDP;
    pstUdpPkt->stIpHdr.ulSrcAddr        = VOS_HTONL(ulSrcAddr);
    pstUdpPkt->stIpHdr.ulDstAddr        = VOS_HTONL(ulDstAddr);
    pstUdpPkt->stIpHdr.usCheckSum       = AT_CalcIpHdrCRC16((VOS_UINT8 *)&pstUdpPkt->stIpHdr, AT_IP_HDR_LEN);

    /* UDP */
    pstUdpPkt->stUdpHdr.usSrcPort       = VOS_HTONS(usSrcPort);
    pstUdpPkt->stUdpHdr.usDstPort       = VOS_HTONS(usDstPort);
    pstUdpPkt->stUdpHdr.usLen           = VOS_HTONS(usLen + AT_UDP_HDR_LEN);
    pstUdpPkt->stUdpHdr.usChecksum      = 0;

    usIdentification++;

    return VOS_OK;
}

/******************************************************************************
 Function:       AT_DHCPCheckCfg
 Description:    DHCPIP01
 Calls:
 Data Accessed:
 Data Updated:
 Input:         AT_AP_DHCP_SETUP_PARAM_ST *ptrDHCPCfg DHCP
 Output:
 Return:        VOS_OK      
                VOS_ERR     
 Others:        IP01
     1.Date        : 2009-08-03-
    Author      : S62952
    Modification: Created function
******************************************************************************/
VOS_UINT32 AT_DHCPCheckCfg(
    AT_DHCP_SETUP_PARAM_ST             *ptrDHCPCfg
)
{
    if ( (0 == ptrDHCPCfg->ulIPAddr)
      || (0 == (0xffffffffU - ptrDHCPCfg->ulIPAddr)) )
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/******************************************************************************
     : AT_DHCPServerSetUp
   : ptrDHCPParamDHCP ServerptrDHCPConfig
                DHCP Server()
                DHCP Server
   : pstEventPDP
   : AT_DHCP_SETUP_PARAM_ST *ptrDHCPCfg       DHCP
             AT_DHCP_CONFIG_STRU    *ptrDHCPConfig    DHCP
     : VOS_OK      
             VOS_ERR     
   :
   :

       :
  1.       : 2010123
           : sunshaohua
       : 
******************************************************************************/
VOS_UINT32  AT_DHCPServerSetUp(
    AT_DHCP_SETUP_PARAM_ST              *ptrDHCPParam,
    AT_DHCP_CONFIG_STRU                 *ptrDHCPConfig
)
{
    if (VOS_ERR == AT_DHCPCheckCfg(ptrDHCPParam))
    {
        AT_ERR_LOG("AT_DHCPServerSetUp, ERROR, DHCP Config IP Address is Error!" );
        return VOS_ERR;
    }

      /**/
    ptrDHCPConfig->ulIPAddr     = ptrDHCPParam->ulIPAddr;
    ptrDHCPConfig->ulSubNetMask =
      AT_DHCPGetIPMask(ptrDHCPParam->ulIPAddr);
    ptrDHCPConfig->ulGateWay    =
      AT_DHCPGetGateWay(ptrDHCPParam->ulIPAddr,ptrDHCPConfig->ulSubNetMask);
    ptrDHCPConfig->ulPrimDNS    = ptrDHCPParam->ulPrimDNS;
    ptrDHCPConfig->ulSndDNS     = ptrDHCPParam->ulSndDNS;

    return VOS_OK;
}

/*****************************************************************************
     : AT_GetDhcpPara
   : DHCP(DHCP)
   : pstConfig                  - DHCP()
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 2012220
           : A00165503
       : 

*****************************************************************************/
VOS_VOID AT_GetDhcpPara(
    AT_DHCP_PARA_STRU                  *pstConfig,
    AT_IPV4_DHCP_PARAM_STRU            *pstIpv4Dhcp
)
{
    /* DHCP */
    pstConfig->stDhcpCfg.ulIPAddr     = VOS_HTONL(pstIpv4Dhcp->ulIpv4Addr);
    pstConfig->stDhcpCfg.ulSubNetMask = VOS_HTONL(pstIpv4Dhcp->ulIpv4NetMask);
    pstConfig->stDhcpCfg.ulGateWay    = VOS_HTONL(pstIpv4Dhcp->ulIpv4GateWay);
    pstConfig->stDhcpCfg.ulPrimDNS    = VOS_HTONL(pstIpv4Dhcp->ulIpv4PrimDNS);
    pstConfig->stDhcpCfg.ulSndDNS     = VOS_HTONL(pstIpv4Dhcp->ulIpv4SecDNS);

    return;
}

/******************************************************************************
     : AT_AtoI
   : 
   : pString 
   : 
     :  IP
   :
   :

       :
  1.       : 2010123
           : sunshaohua
       : 
******************************************************************************/
VOS_UINT64  AT_AtoI(
    VOS_UINT8                         *pString
)
{
    VOS_UINT8   *pucTmp;
    VOS_UINT64   ullRet;

    pucTmp  = pString;
    ullRet  = 0;

    for (pucTmp = pString ; *pucTmp != '\0' ; pucTmp++)
    {
        /* ,*/
        if ((*pucTmp < '0') || (*pucTmp > '9'))
        {
            continue;
        }

        ullRet = (ullRet * 10) + (*pucTmp - '0');
    }

    return ullRet;
}

/******************************************************************************
     : AT_AtoInt
   : 
   : pString 
   : 
     :  IP
   :
   :

       :
  1.       : 2016616
           : lwx331495
       : 
******************************************************************************/
VOS_INT32  AT_AtoInt(
    VOS_UINT8                          *pString,
    VOS_INT32                          *pOut
)
{
    VOS_UINT8                          *pucTmp;
    VOS_INT32                           lFlag;     /* negative flag */

    pucTmp  = pString;
    lFlag   = 0;

    if ('-' == *pucTmp)
    {
        lFlag = VOS_TRUE;
        pucTmp ++;
    }

    for (; *pucTmp != '\0' ; pucTmp++)
    {
        /* ,  */
        if ((*pucTmp < '0') || (*pucTmp > '9'))
        {
            return VOS_ERR;
        }

        *pOut = (*pOut * 10) + (*pucTmp - '0');
    }

    if (VOS_TRUE == lFlag)
    {
        *pOut = (0 - (*pOut));
    }

    return VOS_OK;
}

/******************************************************************************
     : AT_GetDisplayRate
   : NAS
   : ulSpeed
   : 
     : 
   :
   :

       :
  1.       : 2010123
           : sunshaohua
       : 
  2.       : 201347
           : s00217060
       : ATCmmammc
  3.       : 2016929
           : l00373346
       : 
******************************************************************************/
VOS_UINT32 AT_GetDisplayRate(
    VOS_UINT16                          usClientId,
    AT_DISPLAY_RATE_STRU               *pstSpeed
)
{
      if (VOS_ERR == Taf_GetDisplayRate(usClientId, pstSpeed))
      {
          AT_ERR_LOG("AT_GetDisplayRate : ERROR : at get rate Error!");
          return VOS_ERR;
      }
      pstSpeed->ucDlSpeed[AT_AP_SPEED_STRLEN] = '\0';
      pstSpeed->ucUlSpeed[AT_AP_SPEED_STRLEN] = '\0';

      return VOS_OK;
}

/******************************************************************************
     : AT_CtrlConnIndProc
   : DHCP
   : pstEventTAF_PS_CALL_EVENT_INFO_STRU
   : 
     : 
   :
   :

       :
  1.       : 2010123
           : sunshaohua
       : 

  2.       : 2012612
           : S62952
       : DTS2012032802023: ^CSND
  3.       : 20130708
           : Y00213812
       : VoLTE_PhaseI EVENT

  4.       : 20131111
           : A00165503
       : DTS2013110900839: ^CSND
******************************************************************************/
VOS_VOID AT_CtrlConnIndProc(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent,
    AT_USER_TYPE                        ucUserType
)
{
    AT_DHCP_SETUP_PARAM_ST              stParam;
    AT_DHCP_CONFIG_STRU                 stConfig;

    TAF_MEM_SET_S(&stParam, sizeof(stParam), 0x00, sizeof(AT_DHCP_SETUP_PARAM_ST));
    TAF_MEM_SET_S(&stConfig, sizeof(stConfig), 0x00, sizeof(AT_DHCP_CONFIG_STRU));

    /* PSDNSDNS*/
    if (pstEvent->stDns.bitOpPrimDnsAddr)
    {
        stParam.ulPrimDNS = AT_GetLanAddr32(pstEvent->stDns.aucPrimDnsAddr);
    }

    if (pstEvent->stDns.bitOpSecDnsAddr)
    {
        stParam.ulSndDNS = AT_GetLanAddr32(pstEvent->stDns.aucSecDnsAddr);
    }

    /* IP*/
    stParam.ulIPAddr = AT_GetLanAddr32(pstEvent->stPdpAddr.aucIpv4Addr);

    if (VOS_ERR == AT_DHCPServerSetUp(&stParam, &stConfig))
    {
        AT_ERR_LOG("AT_CtrlConnIndProc : ERROR AT_DHCPServerSetUp Error!" );

        return;
    }
    else
    {
        /* Modified by s62952 for BalongV300R002 Build 2012-02-28, begin */
        if (AT_NDIS_USER == ucUserType)
        {
            AT_NdisAddrProc(&stConfig, pstEvent);
        }
        /* Modified by s62952 for BalongV300R002 Build 2012-02-28, end */

        if (AT_APP_USER == ucUserType)
        {
            AT_AppPdpAddrProc(&g_stAtAppPdpEntity, &stConfig, pstEvent);
        }

        /* AT_USBCOM_USER */
    }

    return;
}

/*****************************************************************************
     : Taf_GetDisplayRate
   :
   :
   :
     : TAF_SUCCESS  - 
             TAF_FAILURE  - 
   :
   :

       :
  1.       : 2009-05-16
           :s62952
       : Created
  2.       : 2011-06-06
           :w00166186
       : NV
  3.       : 2011720
           : /f62575
       : DTS2011063000712 
  4.       : 201348
           : s00217060
       : ATC
  5.       : 2015410
           : h00313353
       : Syscfg
  6.       : 20151226
           : f00179208
       : Coverity
  7.       : 20151117
           : zwx247453
       : dallas gps
  8.       : 2016929
           : l00373346
       : 
*****************************************************************************/
VOS_UINT32 Taf_GetDisplayRate(
    VOS_UINT16                          usClientId,
    AT_DISPLAY_RATE_STRU               *pstSpeed
)
{
    PPP_RATE_DISPLAY_ENUM_UINT32        enRateDisplay;
    AT_DISPLAY_RATE_STRU                stDialRateTmp;
    TAF_AGENT_SYS_MODE_STRU             stSysMode;
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulDlSpeedLen      = 0;
    VOS_UINT32                          ulUlSpeedLen      = 0;
    VOS_UINT32                          ulNvDialRateIndex;
    VOS_UINT8                           ucSubSysMode;
    VOS_UINT8                           ucDlCategoryIndex = 0;
    VOS_UINT8                           ucUlCategoryIndex = 0;

    /*  */
    TAF_MEM_SET_S(&stSysMode, sizeof(stSysMode), 0x00, sizeof(stSysMode));
    TAF_MEM_SET_S(&stDialRateTmp, sizeof(AT_DISPLAY_RATE_STRU), 0x00, sizeof(AT_DISPLAY_RATE_STRU));

    /* CucRatTypeucSysSubMode */
    ulRet = TAF_AGENT_GetSysMode(usClientId, &stSysMode);

    if (VOS_OK != ulRet)
    {
        stSysMode.enRatType     = TAF_PH_INFO_GSM_RAT;
        stSysMode.enSysSubMode  = TAF_SYS_SUBMODE_BUTT;
    }

    ucSubSysMode = stSysMode.enSysSubMode;
    switch(ucSubSysMode)
    {
        case TAF_SYS_SUBMODE_GSM:
            ulNvDialRateIndex =    g_stDialConnectDisplayRate.ucGprsConnectRate;
            break;

        case TAF_SYS_SUBMODE_GPRS:
            ulNvDialRateIndex =    g_stDialConnectDisplayRate.ucGprsConnectRate;

            break;

        case TAF_SYS_SUBMODE_EDGE:
            ulNvDialRateIndex =    g_stDialConnectDisplayRate.ucEdgeConnectRate;
            break;

        case TAF_SYS_SUBMODE_WCDMA:
            ulNvDialRateIndex =    g_stDialConnectDisplayRate.ucWcdmaConnectRate;
            break;

        case TAF_SYS_SUBMODE_HSDPA:
        case TAF_SYS_SUBMODE_HSDPA_HSUPA:
            ulNvDialRateIndex =    g_stDialConnectDisplayRate.ucDpaConnectRate;
            break;

        default:
            ulNvDialRateIndex = 0;
            break;
    }

    if ((0 == ulNvDialRateIndex) || (ulNvDialRateIndex > 6))
    {
        if ( (TAF_PH_INFO_WCDMA_RAT == stSysMode.enRatType)
          || (TAF_PH_INFO_TD_SCDMA_RAT == stSysMode.enRatType) )
        {
            enRateDisplay = AT_GetRateDisplayIndexForWcdma(&g_stAtDlRateCategory);

            ulDlSpeedLen = VOS_StrLen((TAF_CHAR *)g_PppDialRateDisplay[enRateDisplay]);
            ulUlSpeedLen = VOS_StrLen((TAF_CHAR *)g_PppDialRateDisplay[enRateDisplay]);
            TAF_MEM_CPY_S(stDialRateTmp.ucDlSpeed, (VOS_SIZE_T)sizeof(stDialRateTmp.ucDlSpeed), g_PppDialRateDisplay[enRateDisplay], ulDlSpeedLen);
            TAF_MEM_CPY_S(stDialRateTmp.ucUlSpeed, (VOS_SIZE_T)sizeof(stDialRateTmp.ucUlSpeed), g_PppDialRateDisplay[enRateDisplay], ulUlSpeedLen);
        }
        else if (TAF_PH_INFO_LTE_RAT == stSysMode.enRatType)
        {
            ucDlCategoryIndex = AT_GetLteUeDlCategoryIndex();
            ucUlCategoryIndex = AT_GetLteUeUlCategoryIndex();

            ulDlSpeedLen = VOS_StrLen((TAF_CHAR *)(g_ucLTERateDisplay[ucDlCategoryIndex].acStrDlSpeed));
            TAF_MEM_CPY_S(stDialRateTmp.ucDlSpeed, (VOS_SIZE_T)sizeof(stDialRateTmp.ucDlSpeed), g_ucLTERateDisplay[ucDlCategoryIndex].acStrDlSpeed, ulDlSpeedLen);
            ulUlSpeedLen = VOS_StrLen((TAF_CHAR *)(g_ucLTERateDisplay[ucUlCategoryIndex].acStrUlSpeed));
            TAF_MEM_CPY_S(stDialRateTmp.ucUlSpeed, (VOS_SIZE_T)sizeof(stDialRateTmp.ucUlSpeed), g_ucLTERateDisplay[ucUlCategoryIndex].acStrUlSpeed, ulUlSpeedLen);
        }
        else
        {
            enRateDisplay = AT_GetRateDisplayIndexForGsm(&stSysMode);

            ulDlSpeedLen = VOS_StrLen((TAF_CHAR *)g_PppDialRateDisplay[enRateDisplay]);
            ulUlSpeedLen = VOS_StrLen((TAF_CHAR *)g_PppDialRateDisplay[enRateDisplay]);
            TAF_MEM_CPY_S(stDialRateTmp.ucDlSpeed, (VOS_SIZE_T)sizeof(stDialRateTmp.ucDlSpeed), g_PppDialRateDisplay[enRateDisplay], ulDlSpeedLen);
            TAF_MEM_CPY_S(stDialRateTmp.ucUlSpeed, (VOS_SIZE_T)sizeof(stDialRateTmp.ucUlSpeed), g_PppDialRateDisplay[enRateDisplay], ulUlSpeedLen);
        }
    }
    /* Modified by s00217060 for ATC, 2013-4-2, end */
    else
    {
        ulDlSpeedLen = VOS_StrLen((TAF_CHAR *)g_ucDialRateDisplayNv[ulNvDialRateIndex - 1]);
        ulUlSpeedLen = VOS_StrLen((TAF_CHAR *)g_ucDialRateDisplayNv[ulNvDialRateIndex - 1]);
        TAF_MEM_CPY_S(stDialRateTmp.ucDlSpeed, (VOS_SIZE_T)sizeof(stDialRateTmp.ucDlSpeed), g_ucDialRateDisplayNv[ulNvDialRateIndex - 1], ulDlSpeedLen);
        TAF_MEM_CPY_S(stDialRateTmp.ucUlSpeed, (VOS_SIZE_T)sizeof(stDialRateTmp.ucUlSpeed), g_ucDialRateDisplayNv[ulNvDialRateIndex - 1], ulUlSpeedLen);
    }

    /*CONNECT*/
    TAF_MEM_CPY_S(pstSpeed->ucDlSpeed, AT_AP_SPEED_STRLEN + 1, stDialRateTmp.ucDlSpeed, (VOS_UINT16)ulDlSpeedLen);
    TAF_MEM_CPY_S(pstSpeed->ucUlSpeed, AT_AP_SPEED_STRLEN + 1, stDialRateTmp.ucUlSpeed, (VOS_UINT16)ulUlSpeedLen);
    pstSpeed->ucDlSpeed[ulDlSpeedLen] = '\0';
    pstSpeed->ucUlSpeed[ulUlSpeedLen] = '\0';

    return VOS_OK;
}

/*****************************************************************************
     : AT_GetPdpContextFromAtDialParam
   : pdp
   : TAF_PDP_PRIM_CONTEXT_EXT_STRU      *pstPdpPrimContextExt,
             AT_DIAL_PARAM_STRU                 *pstDialParam
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20111231
           : c00173809
       : PSpdp
*****************************************************************************/
VOS_VOID AT_GetPdpContextFromAtDialParam(
    TAF_PDP_PRIM_CONTEXT_EXT_STRU      *pstPdpPrimContextExt,
    AT_DIAL_PARAM_STRU                 *pstDialParam
)
{
    VOS_UINT32                          ulRet;

    TAF_MEM_SET_S((VOS_VOID *)pstPdpPrimContextExt, sizeof(TAF_PDP_PRIM_CONTEXT_EXT_STRU), 0x00, sizeof(TAF_PDP_PRIM_CONTEXT_EXT_STRU));

    pstPdpPrimContextExt->bitOpPdpType      = VOS_TRUE;
    pstPdpPrimContextExt->bitOpPdpDcomp     = VOS_FALSE;
    pstPdpPrimContextExt->bitOpPdpHcomp     = VOS_FALSE;
    pstPdpPrimContextExt->enPdpType         = pstDialParam->enPdpType;
    pstPdpPrimContextExt->ucCid             = pstDialParam->ucCid;

    /* APN */
    if (0 != pstDialParam->ucAPNLen)
    {
        pstPdpPrimContextExt->bitOpApn      = VOS_TRUE;
        TAF_MEM_CPY_S((VOS_CHAR*)pstPdpPrimContextExt->aucApn,
                   sizeof(pstPdpPrimContextExt->aucApn),
                   (VOS_CHAR*)pstDialParam->aucAPN,
                   pstDialParam->ucAPNLen);
    }

    /* IPATPDPAPSIPV6IP */
    if (VOS_TRUE == pstDialParam->ulIPv4ValidFlag )
    {
        ulRet = AT_LenStr2IpAddr(pstDialParam->aucIPv4Addr,pstPdpPrimContextExt->stPdpAddr.aucIpv4Addr);
        if (AT_SUCCESS == ulRet )
        {
            pstPdpPrimContextExt->bitOpPdpAddr        = VOS_TRUE;
            pstPdpPrimContextExt->stPdpAddr.enPdpType = TAF_PDP_IPV4;
        }
    }
}

/*****************************************************************************
     : AT_GetPsDialParamFromAtDialParam
   : 
   : TAF_PDP_PRIM_CONTEXT_EXT_STRU      *pstPdpPrimContextExt,
             AT_DIAL_PARAM_STRU                 *pstDialParam
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20111231
           : c00173809
       : PS

  2.       : 20121218
           : A00165503
       : C50 IPv6 
*****************************************************************************/
VOS_VOID AT_GetPsDialParamFromAtDialParam(
    TAF_PS_DIAL_PARA_STRU              *pstPsDialParam,
    AT_DIAL_PARAM_STRU                 *pstDialParam
)
{
    TAF_MEM_SET_S((VOS_VOID *)pstPsDialParam, sizeof(TAF_PS_DIAL_PARA_STRU), 0x00, sizeof(TAF_PS_DIAL_PARA_STRU));

    pstPsDialParam->enPdpType       = pstDialParam->enPdpType;
    pstPsDialParam->ucCid           = pstDialParam->ucCid;

    /* APN */
    if (0 != pstDialParam->ucAPNLen)
    {
        pstPsDialParam->bitOpApn        = VOS_TRUE;
        TAF_MEM_CPY_S((VOS_CHAR*)pstPsDialParam->aucApn,
                   sizeof(pstPsDialParam->aucApn),
                   (VOS_CHAR*)pstDialParam->aucAPN,
                   pstDialParam->ucAPNLen);
    }

    /*  */
    pstPsDialParam->bitOpAuthType   = VOS_TRUE;
    pstPsDialParam->enAuthType      = (PPP_AUTH_TYPE_ENUM_UINT8)pstDialParam->usAuthType;

    if (0 != pstDialParam->usPasswordLen)
    {
        pstPsDialParam->bitOpPassWord = VOS_TRUE;
        TAF_MEM_CPY_S((VOS_VOID *)pstPsDialParam->aucPassWord,
                   sizeof(pstPsDialParam->aucPassWord),
                   (VOS_VOID *)pstDialParam->aucPassword,
                   pstDialParam->usPasswordLen);
    }
    else
    {
        pstPsDialParam->bitOpPassWord = VOS_FALSE;
    }

    if (0 != pstDialParam->usUsernameLen)
    {
        pstPsDialParam->bitOpUserName = VOS_TRUE;
        TAF_MEM_CPY_S((VOS_VOID *)pstPsDialParam->aucUserName,
                   sizeof(pstPsDialParam->aucUserName),
                   (VOS_VOID *)pstDialParam->aucUsername,
                   pstDialParam->usUsernameLen);
    }
    else
    {
        pstPsDialParam->bitOpUserName = VOS_FALSE;
    }

    pstPsDialParam->ucBitRatType   = pstDialParam->ucBitRatType;

}


/*****************************************************************************
     : AT_GetFcPriFromMap
   : FC IDFC PRI
   : FC_ID_ENUM_UINT8                   enFcId,
             AT_FCID_MAP_STRU                  *pstFcIdMap
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 2012218
           : L47619
       : 
*****************************************************************************/
VOS_UINT32 AT_GetFcPriFromMap(
    FC_ID_ENUM_UINT8                   enFcId,
    AT_FCID_MAP_STRU                  *pstFcIdMap
)
{
    if (enFcId >= FC_ID_BUTT)
    {
        return VOS_ERR;
    }

    if ((FC_ID_MODEM == enFcId)
     || (FC_ID_NIC_1 == enFcId)
     || (FC_ID_NIC_2 == enFcId)
     || (FC_ID_NIC_3 == enFcId)
     || (FC_ID_NIC_4 == enFcId)
     || (FC_ID_NIC_5 == enFcId)
     || (FC_ID_NIC_6 == enFcId)
     || (FC_ID_NIC_7 == enFcId)
     || (FC_ID_DIPC_1 == enFcId)
     || (FC_ID_DIPC_2 == enFcId)
     || (FC_ID_DIPC_3 == enFcId))
    {
        pstFcIdMap->ulUsed  = g_stFcIdMaptoFcPri[enFcId].ulUsed;
        pstFcIdMap->enFcPri = g_stFcIdMaptoFcPri[enFcId].enFcPri;

        return VOS_OK;
    }

    return VOS_ERR;
}




/*****************************************************************************
     : AT_NotifyFcWhenPdpModify
   : PDP MODIFY(UE)FC
   : pstEvt       TAF_PS_CALL_EVENT_INFO_STRU
             enFcId        ID
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 2012218
           : L47619
       : 
  2.       : 20130708
           : Y00213812
       : VoLTE_PhaseI EVENT
*****************************************************************************/
VOS_VOID AT_NotifyFcWhenPdpModify(
    TAF_PS_CALL_PDP_MODIFY_CNF_STRU    *pstEvent,
    FC_ID_ENUM_UINT8                    enFcId
)
{
    FC_PRI_ENUM_UINT8                   enFCPriCurrent;
    AT_FCID_MAP_STRU                    stFCPriOrg;

    if (VOS_OK == AT_GetFcPriFromMap(enFcId, &stFCPriOrg))
    {
        if (TAF_USED == pstEvent->bitOpUmtsQos)
        {
            enFCPriCurrent = AT_GetFCPriFromQos(&pstEvent->stUmtsQos);
        }
        else
        {
            enFCPriCurrent = FC_PRI_FOR_PDN_NONGBR;
        }

        if ( (VOS_TRUE == stFCPriOrg.ulUsed)
           && (enFCPriCurrent > stFCPriOrg.enFcPri))
        {
            /* QOS*/
            AT_ChangeFCPoint(&pstEvent->stCtrl,enFCPriCurrent,enFcId);
        }
    }

    return;
}



/***************************************************************************
               NDIS
*****************************************************************************/
/* Modified by s62952 for BalongV300R002 Build 2012-02-28, begin */

/*****************************************************************************
     : AT_PutNetworkAddr32
   : UINT32(LITTLE_ENDIAN)--->
   : VOS_UINT8                            *pucAddr
             VOS_UINT32                            ulAddr
   : 
     : VOS_UINT8*
   :
   :

       :
  1.       : 2011325
           : A00165503
       : 

  2.       : 20111020
           : A00165503
       : AT Project: Porting

*****************************************************************************/
VOS_UINT8* AT_PutNetworkAddr32(
  VOS_UINT8                            *pucAddr,
  VOS_UINT32                            ulAddr
)
{
    *pucAddr = (ulAddr >> 24);
    pucAddr++;

    *pucAddr = ((ulAddr >> 16) & 0xFF);
    pucAddr++;

    *pucAddr = ((ulAddr >> 8) & 0xFF);
    pucAddr++;

    *pucAddr = (ulAddr & 0xFF);
    pucAddr++;

    return pucAddr;
}

/*****************************************************************************
     : AT_CovertArrayToU32
   : UINT32
   : VOS_UINT8                            *pucAddr
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 2011516
           : L00171473
       : for V7R1 porting,

  2.       : 20111020
           : A00165503
       : AT Project: Porting

*****************************************************************************/
VOS_UINT32 AT_CovertArrayToU32(
  VOS_UINT8                            *pucAddr
)
{
    VOS_UINT32                          ulAddr;

    pucAddr += 4;

    pucAddr--;
    ulAddr = *(pucAddr);

    ulAddr <<= 8;
    pucAddr--;
    ulAddr |= *(pucAddr);

    ulAddr <<= 8;
    pucAddr--;
    ulAddr |= *(pucAddr);

    ulAddr <<= 8;
    pucAddr--;
    ulAddr |= *(pucAddr);

    return ulAddr;
}

/*****************************************************************************
     : AT_NidsGet3gppSmCauseByPsCause
   : PS3GPP(E)SM Cause, 3GPP
             0(Unknown error/Unspecified error)
   : enCause - PS
   : 
     : VOS_UINT16
   :
   :

       :
  1.       : 2012825
           : A00165503
       : 
  2.       : 20121120
           : Y00213812
       : DTS2012111907501: PDP DeactiveTAF_PS_CAUSE_SUCCESS
                 36
  3.       : 20130708
           : Y00213812
       : VoLTE_PhaseI VOS_UINT32
*****************************************************************************/
VOS_UINT32 AT_Get3gppSmCauseByPsCause(
    TAF_PS_CAUSE_ENUM_UINT32            enCause
)
{
    VOS_UINT32                          ul3gppSmCause;

    if ( (enCause >= TAF_PS_CAUSE_SM_NW_SECTION_BEGIN)
      && (enCause <= TAF_PS_CAUSE_SM_NW_SECTION_END) )
    {
        ul3gppSmCause = enCause - TAF_PS_CAUSE_SM_NW_SECTION_BEGIN;
    }
    /* E5PDP DEACTIVE36 */
    else if (TAF_PS_CAUSE_SUCCESS == enCause)
    {
        ul3gppSmCause = TAF_PS_CAUSE_SM_NW_REGULAR_DEACTIVATION - TAF_PS_CAUSE_SM_NW_SECTION_BEGIN;
    }
    else
    {
        ul3gppSmCause = AT_NDISSTAT_ERR_UNKNOWN;
    }

    return ul3gppSmCause;
}

/*****************************************************************************
     : AT_SaveNdisConnDailPara
   : NDISCONNNDISCONN
   : AT_PARSE_PARA_TYPE_STRU            *pstParaList
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 2011513
           : L00171473
       : for V7R1 porting,

  2.       : 20111020
           : A00165503
       : AT Project: Porting

  3.       : 2012515
           : l60609
       : DTS2012050800626:authTypechappapchap
*****************************************************************************/
VOS_VOID AT_SaveNdisConnDailPara(
    AT_PARSE_PARA_TYPE_STRU            *pstParaList
)
{
    AT_NDISCONN_PARA_STRU               *pstNdisDailPara;
    VOS_UINT16                          usStrLen;

    pstNdisDailPara = AT_GetNdisConnParaAddr();

    TAF_MEM_SET_S(pstNdisDailPara, sizeof(AT_NDISCONN_PARA_STRU), 0x00, sizeof(AT_NDISCONN_PARA_STRU));

    pstNdisDailPara->ulConnectState = pstParaList[AT_NDIS_CONN_IDX].ulParaValue;
    pstNdisDailPara->ucCID = (VOS_UINT8)pstParaList[AT_NDIS_CID_IDX].ulParaValue;

    usStrLen = pstParaList[AT_NDIS_APN_IDX].usParaLen;
    if ( usStrLen > TAF_MAX_APN_LEN )
    {
        usStrLen = TAF_MAX_APN_LEN;
    }
    TAF_MEM_CPY_S((VOS_CHAR*)pstNdisDailPara->aucAPN,
               sizeof(pstNdisDailPara->aucAPN),
               (VOS_CHAR*)pstParaList[AT_NDIS_APN_IDX].aucPara, usStrLen);

    usStrLen = pstParaList[AT_NDIS_NAME_IDX].usParaLen;
    if ( usStrLen > TAF_MAX_GW_AUTH_USERNAME_LEN )
    {
        usStrLen = TAF_MAX_GW_AUTH_USERNAME_LEN;
    }
    TAF_MEM_CPY_S((VOS_CHAR*)pstNdisDailPara->aucUsername,
               sizeof(pstNdisDailPara->aucUsername),
               (VOS_CHAR*)pstParaList[AT_NDIS_NAME_IDX].aucPara, usStrLen);

    usStrLen = pstParaList[AT_NDIS_PWD_IDX].usParaLen;
    if ( usStrLen > TAF_MAX_GW_AUTH_PASSWORD_LEN )
    {
        usStrLen = TAF_MAX_GW_AUTH_PASSWORD_LEN;
    }
    TAF_MEM_CPY_S((VOS_CHAR*)pstNdisDailPara->aucPassword,
               sizeof(pstNdisDailPara->aucPassword),
               (VOS_CHAR*)pstParaList[AT_NDIS_PWD_IDX].aucPara, usStrLen);

    pstNdisDailPara->usAuthType = AT_CtrlGetPDPAuthType(pstParaList[AT_NDIS_AUTH_IDX].ulParaValue,
                                                        pstParaList[AT_NDIS_AUTH_IDX].usParaLen);
}

/*****************************************************************************
     : AT_SendNdisRelReq
   : PDN
   : TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU        *pstEvent
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 2011326
           : A00165503
       : 
  2.       : 20111020
           : A00165503
       : AT Project: Porting
  3.       : 20111222
           : /l60609
       : PS Project: ATNDIS
  4.       : 20130708
           : Y00213812
       : VoLTE_PhaseI EVENT
*****************************************************************************/
VOS_UINT32 AT_SendNdisRelReq(
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU        *pstEvent
)
{
    /* Modified by l60609 for PS Project, 2011-12-21, Begin */
    AT_NDIS_PDNINFO_REL_REQ_STRU        stNdisRelReq;
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT32                          ulRet;

    enModemId                           = MODEM_ID_0;

    ulRet = AT_GetModemIdFromClient((AT_CLIENT_TAB_INDEX_UINT8)(pstEvent->stCtrl.usClientId), &enModemId);

    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_SendNdisRelReq:Get Modem Id fail");
        return VOS_ERR;
    }

    /*  */
    /* Modified by l60609 for DSDA Phase II, 2012-12-27, Begin */
    stNdisRelReq.enModemId = enModemId;
    /* Modified by l60609 for DSDA Phase II, 2012-12-27, End */
    stNdisRelReq.ucRabId   = pstEvent->ucRabId;

    /* Modified by l60609 for PS Project, 2011-12-21, End */


    /*  */
    if (ERR_MSP_SUCCESS != AT_FwSendClientMsg(PS_PID_APP_NDIS,
                                            ID_AT_NDIS_PDNINFO_REL_REQ,
                                            sizeof(AT_NDIS_PDNINFO_REL_REQ_STRU),
                                            (VOS_UINT8*)&stNdisRelReq))
    {
        AT_ERR_LOG("GUAT_SendNdisRelReq: Send client msg fail.");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
     : AT_ActiveUsbNet
   : USB
   : VOS_UINT32                          ulRxbps,
             VOS_UINT32                          ulTxbps
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 20111229
           : C00173809
       : PS 
*****************************************************************************/
VOS_UINT32 AT_ActiveUsbNet(VOS_VOID)
{
    VOS_UINT32                          ulLinkstus;
    VOS_INT32                           lRtn;
    NCM_IOCTL_CONNECTION_SPEED_S        stNcmConnectSpeed;
    AT_DISPLAY_RATE_STRU                stSpeed;

    TAF_MEM_SET_S(&stSpeed, sizeof(stSpeed), 0x00, (VOS_SIZE_T)(sizeof(AT_DISPLAY_RATE_STRU)));

    /* Modified by s00217060 for ATC, 2013-4-3, begin */
    if (VOS_OK != AT_GetDisplayRate(AT_CLIENT_ID_NDIS, &stSpeed))
    /* Modified by s00217060 for ATC, 2013-4-3, end */
    {
        AT_ERR_LOG("AT_ActiveUsbNet : ERROR : AT_GetDisplayRate Error!");
    }
    /* U320xffffffff */
    stNcmConnectSpeed.u32DownBitRate   = (AT_AtoI(stSpeed.ucDlSpeed) >= 0xffffffff) ? 0xffffffff : (VOS_UINT32)AT_AtoI(stSpeed.ucDlSpeed);
    stNcmConnectSpeed.u32UpBitRate     = (AT_AtoI(stSpeed.ucUlSpeed) >= 0xffffffff) ? 0xffffffff : (VOS_UINT32)AT_AtoI(stSpeed.ucUlSpeed);

    lRtn        = mdrv_udi_ioctl(g_ulAtUdiNdisHdl, NCM_IOCTL_CONNECTION_SPEED_CHANGE_NOTIF, (VOS_VOID *)(&stNcmConnectSpeed));
    if (0 != lRtn)
    {
        AT_ERR_LOG("AT_ActiveUsbNet, Ctrl Speed Fail!" );
        return VOS_ERR;
    }

    ulLinkstus  = NCM_IOCTL_CONNECTION_LINKUP;
    lRtn        = mdrv_udi_ioctl (g_ulAtUdiNdisHdl, NCM_IOCTL_NETWORK_CONNECTION_NOTIF, &ulLinkstus);
    if (0 != lRtn)
    {
        AT_ERR_LOG("AT_ActiveUsbNet, Active usb net Fail!" );
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
     : AT_DeActiveUsbNet
   : USB
   : VOS_VOID
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 20111229
           : c00173809
       : PS 
*****************************************************************************/
VOS_UINT32 AT_DeActiveUsbNet(VOS_VOID)
{
    VOS_UINT32  ulLinkstus;
    VOS_INT32   lRtn;

    /*BSP*/
    ulLinkstus = NCM_IOCTL_CONNECTION_LINKDOWN;

    lRtn  = mdrv_udi_ioctl (g_ulAtUdiNdisHdl, NCM_IOCTL_NETWORK_CONNECTION_NOTIF, (VOS_VOID*)(&ulLinkstus));
    if(0 != lRtn)
    {
        AT_ERR_LOG("AT_ActiveUsbNet, Deactive usb net Fail!" );
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
     : AT_SendNdisIPv4PdnInfoCfgReq
   : NDISIPV4PDN
   : MN_CLIENT_ID_T                      usClientId
             AT_IPV4_DHCP_PARAM_STRU            *pstIPv4DhcpParam
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20111224
           : C00173809
       : PSIPV4 PDN

  2.       : 20130708
           : Y00213812
       : VoLTE_PhaseI CLIENTIDMODEM ID

  3.       : 2015418
           : A00165503
       : SPE Project: SPE
*****************************************************************************/
VOS_UINT32 AT_SendNdisIPv4PdnInfoCfgReq(
    AT_CLIENT_TAB_INDEX_UINT8           usClientId,
    AT_IPV4_DHCP_PARAM_STRU            *pstIPv4DhcpParam
)
{
    AT_COMM_PS_CTX_STRU                *pstPsCntxt = VOS_NULL_PTR;
    AT_NDIS_PDNINFO_CFG_REQ_STRU        stNdisCfgReq;
    AT_DISPLAY_RATE_STRU                stSpeed;

    VOS_UINT32                          ulRelt;

    pstPsCntxt = AT_GetCommPsCtxAddr();
    TAF_MEM_SET_S(&stSpeed, sizeof(stSpeed), 0x00, (VOS_SIZE_T)(sizeof(AT_DISPLAY_RATE_STRU)));

    /*  */
    TAF_MEM_SET_S(&stNdisCfgReq, sizeof(stNdisCfgReq), 0x00, sizeof(AT_NDIS_PDNINFO_CFG_REQ_STRU));
    stNdisCfgReq.enModemId              = MODEM_ID_0;

    ulRelt = AT_GetModemIdFromClient(usClientId, &stNdisCfgReq.enModemId);

    if (VOS_OK != ulRelt)
    {
        AT_ERR_LOG("AT_SendNdisIPv4PdnInfoCfgReq:Get Modem Id fail");
        return VOS_ERR;
    }

    stNdisCfgReq.bitOpIpv4PdnInfo       = VOS_TRUE;
    stNdisCfgReq.ulHandle               = g_ulAtUdiNdisHdl;

    /*  */
    if (0 != pstIPv4DhcpParam->ucRabId )
    {
        stNdisCfgReq.ucRabId = pstIPv4DhcpParam->ucRabId;
    }

    /* IPv4 */
    if (0 != pstIPv4DhcpParam->ulIpv4Addr)
    {
        stNdisCfgReq.stIpv4PdnInfo.bitOpPdnAddr     = VOS_TRUE;
        AT_PutNetworkAddr32(stNdisCfgReq.stIpv4PdnInfo.stPDNAddrInfo.aucIpV4Addr,
                            pstIPv4DhcpParam->ulIpv4Addr);
    }

    /*  */
    if (0 != pstIPv4DhcpParam->ulIpv4NetMask)
    {
        AT_PutNetworkAddr32(stNdisCfgReq.stIpv4PdnInfo.stSubnetMask.aucIpV4Addr,
                            pstIPv4DhcpParam->ulIpv4NetMask);
    }

    /*  */
    if (0 != pstIPv4DhcpParam->ulIpv4GateWay)
    {
        AT_PutNetworkAddr32(stNdisCfgReq.stIpv4PdnInfo.stGateWayAddrInfo.aucIpV4Addr,
                            pstIPv4DhcpParam->ulIpv4GateWay);
    }

    /* DNS */
    if (0 != pstIPv4DhcpParam->ulIpv4PrimDNS)
    {
        stNdisCfgReq.stIpv4PdnInfo.bitOpDnsPrim     = VOS_TRUE;
        AT_PutNetworkAddr32(stNdisCfgReq.stIpv4PdnInfo.stDnsPrimAddrInfo.aucIpV4Addr,
                            pstIPv4DhcpParam->ulIpv4PrimDNS);

    }

    /* DNS */
    if (0 != pstIPv4DhcpParam->ulIpv4SecDNS)
    {
        stNdisCfgReq.stIpv4PdnInfo.bitOpDnsSec      = VOS_TRUE;
        AT_PutNetworkAddr32(stNdisCfgReq.stIpv4PdnInfo.stDnsSecAddrInfo.aucIpV4Addr,
                          pstIPv4DhcpParam->ulIpv4SecDNS);

    }

    /* WINS */
    if (0 != pstIPv4DhcpParam->ulIpv4PrimWINNS)
    {
        stNdisCfgReq.stIpv4PdnInfo.bitOpWinsPrim    = VOS_TRUE;
        AT_PutNetworkAddr32(stNdisCfgReq.stIpv4PdnInfo.stWinsPrimAddrInfo.aucIpV4Addr,
                            pstIPv4DhcpParam->ulIpv4PrimWINNS);
    }

    /* WINS */
    if (0 != pstIPv4DhcpParam->ulIpv4SecWINNS)
    {
        stNdisCfgReq.stIpv4PdnInfo.bitOpWinsSec     = VOS_TRUE;
        AT_PutNetworkAddr32(stNdisCfgReq.stIpv4PdnInfo.stWinsSecAddrInfo.aucIpV4Addr,
                            pstIPv4DhcpParam->ulIpv4SecWINNS);
    }

    if (pstIPv4DhcpParam->stIpv4PcscfList.ucIpv4PcscfAddrNum > 0)
    {
        AT_PutNetworkAddr32(stNdisCfgReq.stIpv4PdnInfo.stPcscfPrimAddrInfo.aucIpV4Addr,
                            pstIPv4DhcpParam->stIpv4PcscfList.aulIpv4PcscfAddrList[0]);

        stNdisCfgReq.stIpv4PdnInfo.bitOpPcscfPrim = VOS_TRUE;
    }

    if (pstIPv4DhcpParam->stIpv4PcscfList.ucIpv4PcscfAddrNum > 1)
    {
        AT_PutNetworkAddr32(stNdisCfgReq.stIpv4PdnInfo.stPcscfSecAddrInfo.aucIpV4Addr,
                            pstIPv4DhcpParam->stIpv4PcscfList.aulIpv4PcscfAddrList[1]);

        stNdisCfgReq.stIpv4PdnInfo.bitOpPcscfSec    = VOS_TRUE;
    }

    /* */
    /* Modified by s00217060 for ATC, 2013-4-3, begin */
    if (VOS_OK != AT_GetDisplayRate(AT_CLIENT_ID_NDIS, &stSpeed))
    /* Modified by s00217060 for ATC, 2013-4-3, end */
    {
        AT_ERR_LOG("AT_SendNdisIPv4PdnInfoCfgReq : ERROR : AT_GetDisplayRate Error!");
    }
    /* U320xffffffff */
    stNdisCfgReq.ulMaxRxbps = (AT_AtoI(stSpeed.ucDlSpeed) >= 0xffffffff) ? 0xffffffff : (VOS_UINT32)AT_AtoI(stSpeed.ucDlSpeed);
    stNdisCfgReq.ulMaxTxbps = (AT_AtoI(stSpeed.ucUlSpeed) >= 0xffffffff) ? 0xffffffff : (VOS_UINT32)AT_AtoI(stSpeed.ucUlSpeed);

    stNdisCfgReq.lSpePort   = pstPsCntxt->lSpePort;
    stNdisCfgReq.ulIpfFlag  = pstPsCntxt->ulIpfPortFlg;

    /*  */
    if (ERR_MSP_SUCCESS != AT_FwSendClientMsg(PS_PID_APP_NDIS,
                                            ID_AT_NDIS_PDNINFO_CFG_REQ,
                                            (VOS_UINT16)sizeof(AT_NDIS_PDNINFO_CFG_REQ_STRU),
                                            (VOS_UINT8*)&stNdisCfgReq))
    {
        AT_ERR_LOG("AT_SendNdisIPv4PdnInfoCfgReq: Send client msg fail.");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
     : AT_RcvNdisPdnInfoCfgCnf
   : NDIS
   : AT_NDIS_PDNINFO_CFG_CNF_STRU       *pstNdisPdnInfoCfgCnf
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 2011325
           : A00165503
       : 

  2.       : 20111020
           : A00165503
       : AT Project: Porting

  3.       : 20111225
           : C00173809
       : PS

  4.       : 2012315
           : l60609
       : DTS2012030804093:^NDISDUP

  5.       : 2012728
           : A00165503
       : DTS2012072806289: ^NDISSTAT
*****************************************************************************/
VOS_UINT32 AT_RcvNdisPdnInfoCfgCnf(
    AT_NDIS_PDNINFO_CFG_CNF_STRU       *pstNdisPdnInfoCfgCnf
)
{
    if (AT_NDIS_PDNCFG_CNF_FAIL == pstNdisPdnInfoCfgCnf->enResult)
    {
        AT_ERR_LOG("AT_RcvNdisPdnInfoRelCnf: Failed.");
    }

    return VOS_OK;
}

/*****************************************************************************
     : AT_RcvNdisPdnInfoRelCnf
   : NDIS
   : AT_NDIS_PDNINFO_REL_CNF_STRU       *pstNdisPdnInfoRelCnf
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 2011325
           : A00165503
       : 

  2.       : 20111020
           : A00165503
       : AT Project: Porting

  3.       : 20111225
           : C00173809
       : PS

  4.       : 2012728
           : A00165503
       : DTS2012072806289: ^NDISSTAT
*****************************************************************************/
VOS_UINT32 AT_RcvNdisPdnInfoRelCnf(
    AT_NDIS_PDNINFO_REL_CNF_STRU       *pstNdisPdnInfoRelCnf
)
{
    if (AT_NDIS_SUCC != pstNdisPdnInfoRelCnf->enResult)
    {
        AT_ERR_LOG("AT_RcvNdisPdnInfoRelCnf: Failed.");
    }

    return VOS_OK;
}



/*****************************************************************************
     : AT_NdisConfigIpv6Dns
   : IPv6 DNS
   : VOS_VOID
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 2012728
           : A00165503
       : 
  2.       : 20121211
           : l00167671
       : DTS2012121802573, TQE

*****************************************************************************/
VOS_VOID AT_NdisConfigIpv6Dns(VOS_VOID)
{
    AT_PDP_ENTITY_STRU                 *pstNdisPdpEntity;
    NCM_IPV6DNS_S                       stIPv6Dns;
    VOS_INT32                           lRslt;

    pstNdisPdpEntity = AT_NDIS_GetPdpEntInfoAddr();

    stIPv6Dns.pu8Ipv6DnsInfo = (unsigned char*)PS_MEM_ALLOC(
                                    WUEPS_PID_AT,
                                    BSP_NCM_IPV6_DNS_LEN);

    if (VOS_NULL_PTR == stIPv6Dns.pu8Ipv6DnsInfo)
    {
        AT_ERR_LOG("AT_NdisConfigIpv6Dns:Invalid stIPv6Dns.pu8Ipv6DnsInfo");
        return;
    }

    TAF_MEM_SET_S(stIPv6Dns.pu8Ipv6DnsInfo, BSP_NCM_IPV6_DNS_LEN, 0x00, BSP_NCM_IPV6_DNS_LEN);

    /* DNS32(Primary DNS LEN + Secondary DNS LEN) */
    stIPv6Dns.u32Length = BSP_NCM_IPV6_DNS_LEN;

    /*DNSDRVDNSPC*/
    if (VOS_TRUE == pstNdisPdpEntity->stIpv6Dhcp.bitOpIpv6PriDns)
    {
        TAF_MEM_CPY_S(stIPv6Dns.pu8Ipv6DnsInfo,
                   BSP_NCM_IPV6_DNS_LEN,
                   pstNdisPdpEntity->stIpv6Dhcp.aucIpv6PrimDNS,
                   AT_MAX_IPV6_DNS_LEN);
    }

    if (VOS_TRUE == pstNdisPdpEntity->stIpv6Dhcp.bitOpIpv6SecDns)
    {
        TAF_MEM_CPY_S(stIPv6Dns.pu8Ipv6DnsInfo + AT_MAX_IPV6_DNS_LEN,
                   BSP_NCM_IPV6_DNS_LEN - AT_MAX_IPV6_DNS_LEN,
                   pstNdisPdpEntity->stIpv6Dhcp.aucIpv6SecDNS,
                   AT_MAX_IPV6_DNS_LEN);
    }

    /* DNS */
    lRslt = mdrv_udi_ioctl(g_ulAtUdiNdisHdl, NCM_IOCTL_SET_IPV6_DNS, &stIPv6Dns);
    if (0 != lRslt)
    {
        AT_ERR_LOG("AT_NdisConfigIpv6Dns, DRV_UDI_IOCTL Fail!" );
    }

    /*  */
    PS_MEM_FREE(WUEPS_PID_AT, stIPv6Dns.pu8Ipv6DnsInfo);

}

/*****************************************************************************
     : AT_NdisActCnfBackProc
   : PDP
   : 
   : 
     :
   :
   :

       :
  1.       : 2011612
           : S62952
       : 

  2.       : 20111225
           : c00173809
       : PS IPV6

  3.       : 2012822
           : A00165503
       : PS

  4.       : 20121221
           : l00227485
       : DSDA PhaseII

  5.       : 20130708
           : Y00213812
       : VoLTE_PhaseI #50 , APPIPv6
                 #51 , APPIPv4

  6.       : 2015717
           : Y00213812
       : CDMA
*****************************************************************************/
VOS_VOID  AT_NdisActCnfBackProc(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU        *pstEvent
)
{
    AT_COMM_PS_CTX_STRU                *pstCommPsCtx = VOS_NULL_PTR;
    VOS_UINT8                           ucCid;
    VOS_UINT32                          ulRet;

    pstCommPsCtx = AT_GetCommPsCtxAddr();

    /* 52PDP */
    if ( (VOS_FALSE == pstEvent->bitOpCause)
      || ( (VOS_TRUE == pstEvent->bitOpCause)
        && (TAF_PS_CAUSE_SM_NW_SINGLE_ADDR_BEARERS_ONLY_ALLOWED == pstEvent->enCause) ) )
    {
        if (TAF_PDP_IPV4 == pstEvent->stPdpAddr.enPdpType)
        {
            if((VOS_FALSE == pstEvent->bitOpCause)
            && (VOS_FALSE == pstCommPsCtx->ucRedialForNoCauseFlag))
            {
                AT_NdisStateChangeProc(TAF_PDP_IPV6, AT_PDP_STATUS_DEACT, TAF_PS_CAUSE_SM_NW_PDP_TYPE_IPV4_ONLY_ALLOWED);
            }
            else
            {
                if (AT_PDP_STATE_IDLE == AT_NdisGetState(TAF_PDP_IPV6))
                {
                    /* CID */
                    ulRet       = TAF_AGENT_FindCidForDial(pstEvent->stCtrl.usClientId, &ucCid);
                    if (VOS_OK == ulRet)
                    {
                        AT_NdisPdpActOrig(pstEvent->stCtrl.usClientId, ucCid, TAF_PDP_IPV6);
                    }
                }
            }
        }
        else if (TAF_PDP_IPV6 == pstEvent->stPdpAddr.enPdpType)
        {
            if((VOS_FALSE == pstEvent->bitOpCause)
            && (VOS_FALSE == pstCommPsCtx->ucRedialForNoCauseFlag))
            {
                AT_NdisStateChangeProc(TAF_PDP_IPV4, AT_PDP_STATUS_DEACT, TAF_PS_CAUSE_SM_NW_PDP_TYPE_IPV6_ONLY_ALLOWED);
            }
            else
            {
                if (AT_PDP_STATE_IDLE == AT_NdisGetState(TAF_PDP_IPV4))
                {
                    /* CID */
                    ulRet       = TAF_AGENT_FindCidForDial(pstEvent->stCtrl.usClientId, &ucCid);
                    if (VOS_OK == ulRet)
                    {
                        AT_NdisPdpActOrig(pstEvent->stCtrl.usClientId, ucCid, TAF_PDP_IPV4);
                    }
                }
            }
        }
        else
        {
            ;
        }

        return;
    }
    /* Modified by Y00213812 for VoLTE_PhaseI , 2013-07-08, begin */
    /* , APP */
    switch (pstEvent->enCause)
    {
        /* #50 (IPv4 ONLY), APPIPv6 */
        case TAF_PS_CAUSE_SM_NW_PDP_TYPE_IPV4_ONLY_ALLOWED:
        case TAF_PS_CAUSE_PDP_TYPE_IPV4_ONLY_ALLOWED:

            AT_NdisStateChangeProc(TAF_PDP_IPV6, AT_PDP_STATUS_DEACT, pstEvent->enCause);

            break;

        /* #51 (IPv6 ONLY), APPIPv4 */
        case TAF_PS_CAUSE_SM_NW_PDP_TYPE_IPV6_ONLY_ALLOWED:
        case TAF_PS_CAUSE_PDP_TYPE_IPV6_ONLY_ALLOWED:
            AT_NdisStateChangeProc(TAF_PDP_IPV4, AT_PDP_STATUS_DEACT, pstEvent->enCause);

            break;

        /* ,  */
        default:
            AT_NORM_LOG1("AT_NdisActCnfBackProc: Other <Cause>", pstEvent->enCause);
            break;
    }
    /* Modified by Y00213812 for VoLTE_PhaseI , 2013-07-08, end */

    return;
}

/*****************************************************************************
     : AT_NdisIpv6ActCnfProc
   : IPV6PDP
   : pEvent  --- 
   : 
     :
   :
   :

       :
  1.       : 2011612
           : S62952
       : 

  2.       : 20111217
           : C00173809
       : PSID_AT_NDIS_PDNINFO_CFG_REQNDISIPV6PDN

  3.       : 2012728
           : A00165503
       : DTS2012072806289: ^NDISSTAT

  4.       : 20130708
           : Y00213812
       : VoLTE_PhaseI EVENT
*****************************************************************************/
VOS_VOID AT_NdisIpv6ActCnfProc(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU        *pstEvent
)
{
    /*  */
    TAF_MEM_SET_S(&g_stAtNdisDhcpPara.stIpv6Dhcp,
               sizeof(g_stAtNdisDhcpPara.stIpv6Dhcp),
               0x00,
               sizeof(AT_IPV6_DHCP_PARAM_STRU));

    g_stAtNdisDhcpPara.ucIpv6Cid   = pstEvent->ucCid;

    /* IPV6 */
    AT_NdisCtrlConnIpv6IndProc(pstEvent);

    /* NDISPDP, */
    AT_ProcNdisRegFCPoint(pstEvent, TAF_PDP_IPV6);

    /* NDISPDP, SharePdp*/
    AT_PS_ProcActSharePdpState(pstEvent, TAF_PDP_IPV6);

    /* IPv6 DNS */
    AT_NdisConfigIpv6Dns();

    /* IPV4V6PDP */
    if (TAF_PDP_IPV4V6 == g_enAtFirstNdisActPdpType)
    {
        switch (g_enAtNdisActPdpType)
        {
            case TAF_PDP_IPV6:
                /* PDPPDPIPV4
                   IPV6PDP, IPV6IPV4PDP */
                break;

            /* PDP */
            case TAF_PDP_IPV4V6:
                /* PDPIDLE */
               AT_NdisSetState(g_enAtNdisActPdpType, AT_PDP_STATE_IDLE);

               AT_NdisActCnfBackProc(pstEvent);
               break;

            default:
               AT_WARN_LOG("AT_NdisIpv6ActCnfProc:g_enAtNdisActPdpType is error!");
               break;
        }
    }

    return;
}

/*****************************************************************************
     : AT_NdisIpv4v6ActCnfProc
   : IPV4v6PDP
   : pstEvent --- 
   : 
     :
   :
   :

       :
  1.       : 2011612
           : S62952
       : 

  2.       : 20111217
           : C00173809
       : PSPDPADS,NDIS

  3.       : 2012728
           : A00165503
       : DTS2012072806289: ^NDISSTAT
  4.       : 20130708
           : Y00213812
       : VoLTE_PhaseI EVENT
*****************************************************************************/
VOS_VOID AT_NdisIpv4v6ActCnfProc(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU        *pstEvent
)
{
    VOS_UINT8                           aucIpv6Dns[AT_MAX_IPV6_DNS_LEN * 2];

    /*  */
    TAF_MEM_SET_S(aucIpv6Dns, sizeof(aucIpv6Dns), 0x00, sizeof(aucIpv6Dns));

    TAF_MEM_SET_S(&g_stAtNdisDhcpPara.stIpv6Dhcp,
               sizeof(g_stAtNdisDhcpPara.stIpv6Dhcp),
               0x00,
               sizeof(AT_IPV6_DHCP_PARAM_STRU));

    g_stAtNdisDhcpPara.ucIpv4v6Cid   = pstEvent->ucCid;

    /* IPV4DHCP */
    AT_CtrlConnIndProc(pstEvent, AT_NDIS_USER);

    /* IPV6*/
    AT_NdisCtrlConnIpv6IndProc(pstEvent);

    /* NDISPDP, */
    AT_ProcNdisRegFCPoint(pstEvent, TAF_PDP_IPV4V6);

    /* IPV4PDNNDIS */
    AT_SendNdisIPv4PdnInfoCfgReq(AT_NDIS_GET_USR_PORT_INDEX(),
                                 &(g_stAtNdisDhcpPara.stIpv4Dhcp));


    /* NDISPDP, SharePdp*/
    AT_PS_ProcActSharePdpState(pstEvent, TAF_PDP_IPV4V6);

    /* NDIS PDP,ipv6PDNRA */

    /* IPv6 DNS */
    AT_NdisConfigIpv6Dns();

    return;
}

/*****************************************************************************
     : AT_SendNdisIPv6PdnInfoCfgReq
   : IPV6PDN
   : MODEM_ID_ENUM_UINT16                 enModemId,
             TAF_PS_IPV6_INFO_IND_STRU* pRaInfo
   : 
     : AT_APS_IPV6_RA_INFO_STRU* pIPv6RaInfo
   :
   :

       :
  1.       : 20111224
           : C00173809
       : PSIPV6 PDN

  2.       : 2015418
           : A00165503
       : SPE Project: SPE
*****************************************************************************/
VOS_UINT32 AT_SendNdisIPv6PdnInfoCfgReq(
    MODEM_ID_ENUM_UINT16                 enModemId,
    TAF_PS_IPV6_INFO_IND_STRU           *pIPv6RaNotify
)
{
    AT_COMM_PS_CTX_STRU                *pstPsCntxt = VOS_NULL_PTR;
    AT_NDIS_PDNINFO_CFG_REQ_STRU        stNdisCfgReq;
    AT_PDP_ENTITY_STRU                 *pstNdisPdpEntity;
    AT_DISPLAY_RATE_STRU                stSpeed;

    pstPsCntxt = AT_GetCommPsCtxAddr();
    TAF_MEM_SET_S(&stSpeed, sizeof(stSpeed), 0x00, (VOS_SIZE_T)(sizeof(AT_DISPLAY_RATE_STRU)));

    /*  */
    pstNdisPdpEntity = AT_NDIS_GetPdpEntInfoAddr();
    TAF_MEM_SET_S(&stNdisCfgReq, sizeof(stNdisCfgReq), 0x00, sizeof(AT_NDIS_PDNINFO_CFG_REQ_STRU));

    stNdisCfgReq.ulHandle               = g_ulAtUdiNdisHdl;
    stNdisCfgReq.bitOpIpv6PdnInfo       = VOS_TRUE;
    stNdisCfgReq.enModemId              = enModemId;
    stNdisCfgReq.ucRabId                = pIPv6RaNotify->ucRabId;

    /* DNS */
    stNdisCfgReq.stIpv6PdnInfo.stDnsSer.ucSerNum    = 0;
    if (VOS_TRUE == pstNdisPdpEntity->stIpv6Dhcp.bitOpIpv6PriDns)
    {
        TAF_MEM_CPY_S((VOS_VOID *)stNdisCfgReq.stIpv6PdnInfo.stDnsSer.aucPriServer,
                    sizeof(stNdisCfgReq.stIpv6PdnInfo.stDnsSer.aucPriServer),
                    pstNdisPdpEntity->stIpv6Dhcp.aucIpv6PrimDNS,
                    TAF_IPV6_ADDR_LEN);
        stNdisCfgReq.stIpv6PdnInfo.stDnsSer.ucSerNum += 1;
    }

    if (VOS_TRUE == pstNdisPdpEntity->stIpv6Dhcp.bitOpIpv6SecDns)
    {
        TAF_MEM_CPY_S((VOS_VOID *)stNdisCfgReq.stIpv6PdnInfo.stDnsSer.aucSecServer,
                    sizeof(stNdisCfgReq.stIpv6PdnInfo.stDnsSer.aucSecServer),
                    pstNdisPdpEntity->stIpv6Dhcp.aucIpv6SecDNS,
                    TAF_IPV6_ADDR_LEN);
        stNdisCfgReq.stIpv6PdnInfo.stDnsSer.ucSerNum += 1;
    }

    /* MTU */
    if (VOS_TRUE == pIPv6RaNotify->stIpv6RaInfo.bitOpMtu)
    {
        stNdisCfgReq.stIpv6PdnInfo.ulBitOpMtu   = VOS_TRUE;
        stNdisCfgReq.stIpv6PdnInfo.ulMtu        = pIPv6RaNotify->stIpv6RaInfo.ulMtu;
    }

    stNdisCfgReq.stIpv6PdnInfo.ulBitCurHopLimit = pIPv6RaNotify->stIpv6RaInfo.ulBitCurHopLimit;
    stNdisCfgReq.stIpv6PdnInfo.ulBitM           = pIPv6RaNotify->stIpv6RaInfo.ulBitM;
    stNdisCfgReq.stIpv6PdnInfo.ulBitO           = pIPv6RaNotify->stIpv6RaInfo.ulBitO;
    stNdisCfgReq.stIpv6PdnInfo.ulPrefixNum      = pIPv6RaNotify->stIpv6RaInfo.ulPrefixNum;
    TAF_MEM_CPY_S((VOS_VOID *)stNdisCfgReq.stIpv6PdnInfo.astPrefixList,
                sizeof(stNdisCfgReq.stIpv6PdnInfo.astPrefixList),
                (VOS_VOID *)pIPv6RaNotify->stIpv6RaInfo.astPrefixList,
                sizeof(TAF_PDP_IPV6_PREFIX_STRU)*TAF_MAX_PREFIX_NUM_IN_RA);

    /* INTERFACEIPV68INTERFACE */
    TAF_MEM_CPY_S((VOS_VOID*)stNdisCfgReq.stIpv6PdnInfo.aucInterfaceId,
                sizeof(stNdisCfgReq.stIpv6PdnInfo.aucInterfaceId),
               (VOS_VOID*)pstNdisPdpEntity->stIpv6Dhcp.aucIpv6Addr,
                sizeof(VOS_UINT8)*AT_NDIS_IPV6_IFID_LENGTH);

    /* PCSCF  */
    stNdisCfgReq.stIpv6PdnInfo.stPcscfSer.ucSerNum      = 0;
    if (pstNdisPdpEntity->stIpv6Dhcp.stIpv6PcscfList.ucIpv6PcscfAddrNum > 0)
    {
        stNdisCfgReq.stIpv6PdnInfo.stPcscfSer.ucSerNum++;

        TAF_MEM_CPY_S((VOS_VOID *)stNdisCfgReq.stIpv6PdnInfo.stPcscfSer.aucPriServer,
                      sizeof(stNdisCfgReq.stIpv6PdnInfo.stPcscfSer.aucPriServer),
                      pstNdisPdpEntity->stIpv6Dhcp.stIpv6PcscfList.astIpv6PcscfAddrList[0].aucPcscfAddr,
                      sizeof(pstNdisPdpEntity->stIpv6Dhcp.stIpv6PcscfList.astIpv6PcscfAddrList[0].aucPcscfAddr));
    }

    if (pstNdisPdpEntity->stIpv6Dhcp.stIpv6PcscfList.ucIpv6PcscfAddrNum > 1)
    {
        stNdisCfgReq.stIpv6PdnInfo.stPcscfSer.ucSerNum++;

        TAF_MEM_CPY_S((VOS_VOID *)stNdisCfgReq.stIpv6PdnInfo.stPcscfSer.aucSecServer,
                      sizeof(stNdisCfgReq.stIpv6PdnInfo.stPcscfSer.aucSecServer),
                      pstNdisPdpEntity->stIpv6Dhcp.stIpv6PcscfList.astIpv6PcscfAddrList[1].aucPcscfAddr,
                      sizeof(pstNdisPdpEntity->stIpv6Dhcp.stIpv6PcscfList.astIpv6PcscfAddrList[1].aucPcscfAddr));
    }

    /* */
    /* Modified by s00217060 for ATC, 2013-4-3, begin */
    if (VOS_OK != AT_GetDisplayRate(AT_CLIENT_ID_NDIS, &stSpeed))
    /* Modified by s00217060 for ATC, 2013-4-3, end */
    {
        AT_ERR_LOG("AT_SendNdisIPv6PdnInfoCfgReq : ERROR : AT_GetDisplayRate Error!");
    }
    /* U320xffffffff */
    stNdisCfgReq.ulMaxRxbps = (AT_AtoI(stSpeed.ucDlSpeed) >= 0xffffffff) ? 0xffffffff : (VOS_UINT32)AT_AtoI(stSpeed.ucDlSpeed);
    stNdisCfgReq.ulMaxTxbps = (AT_AtoI(stSpeed.ucUlSpeed) >= 0xffffffff) ? 0xffffffff : (VOS_UINT32)AT_AtoI(stSpeed.ucUlSpeed);

    stNdisCfgReq.lSpePort   = pstPsCntxt->lSpePort;
    stNdisCfgReq.ulIpfFlag  = pstPsCntxt->ulIpfPortFlg;

    /*  */
    if (ERR_MSP_SUCCESS != AT_FwSendClientMsg(PS_PID_APP_NDIS,
                                            ID_AT_NDIS_PDNINFO_CFG_REQ,
                                            (VOS_UINT16)sizeof(AT_NDIS_PDNINFO_CFG_REQ_STRU),
                                            (VOS_UINT8*)&stNdisCfgReq))
    {
        AT_ERR_LOG("AT_SendNdisIPv6PdnInfoCfgReq: Send client msg fail.");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
     : AT_NdisCtrlConnIpv6IndProc
   : IPV6
   : pstEvent ---
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 2011510
           : s62952
       : 
  2.       : 20120102
           : c00173809
       : PSIPV6PCSCF
  3.       : 20130708
           : Y00213812
       : VoLTE_PhaseI EVENT
*****************************************************************************/
VOS_VOID  AT_NdisCtrlConnIpv6IndProc(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU        *pstEvent
)
{
    g_stAtNdisDhcpPara.stIpv6Dhcp.ucRabId  = pstEvent->ucRabId;

    /* IPV6IP */
    TAF_MEM_CPY_S(g_stAtNdisDhcpPara.stIpv6Dhcp.aucIpv6Addr,
               sizeof(g_stAtNdisDhcpPara.stIpv6Dhcp.aucIpv6Addr),
               pstEvent->stPdpAddr.aucIpv6Addr,
               TAF_IPV6_ADDR_LEN);

    /* IPV6DNS */
    AT_SaveIPv6Dns(pstEvent, &g_stAtNdisDhcpPara);

    /* IPV6PCSCF */
    AT_SaveIPv6Pcscf(pstEvent, &g_stAtNdisDhcpPara);

    return;
}

/*****************************************************************************
     : AT_NdisIpv6DhcpRest
   : IPV6
   : 
   : 
     :
   :
   :

       :
  1.       : 201099
           : s62952
       : 

*****************************************************************************/
VOS_VOID AT_NdisIpv6DhcpRest(VOS_VOID)
{
    TAF_MEM_SET_S(&g_stAtNdisDhcpPara.stIpv6Dhcp,
               sizeof(g_stAtNdisDhcpPara.stIpv6Dhcp),
               0x00,
               sizeof(AT_IPV6_DHCP_PARAM_STRU));

    return;
}

/*****************************************************************************
     : AT_NdisCheckIpv6PdpState
   : IPv6PDP
   : enPdpState - PDP
   : 
     : VOS_TRUE   - PDP
             VOS_FALSE  - PDP
   :
   :

       :
  1.       : 2011721
           : A00165503
       : 

*****************************************************************************/
VOS_UINT32 AT_NdisCheckIpv6PdpState(
    AT_PDP_STATE_ENUM_U8                enPdpState
)
{
    if ( (enPdpState == g_stAtNdisDhcpPara.enIpv6State)
      || (enPdpState == g_stAtNdisDhcpPara.enIpv4v6State) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
     : AT_NdisCheckIpv6PdpState
   : IPv4PDP
   : enPdpState - PDP
   : 
     : VOS_TRUE   - PDP
             VOS_FALSE  - PDP
   :
   :

       :
  1.       : 2011721
           : A00165503
       : 

*****************************************************************************/
VOS_UINT32 AT_NdisCheckIpv4PdpState(
    AT_PDP_STATE_ENUM_U8                enPdpState
)
{
    if ( (enPdpState == g_stAtNdisDhcpPara.enIpv4State)
      || (enPdpState == g_stAtNdisDhcpPara.enIpv4v6State) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
     : AT_NdisCheckPdpState
   : NDIS
   : enPdpState - PDP
   : 
     : VOS_TRUE   - NDIS
             VOS_TRUE   - NDIS
   :
   :

       :
  1.       : 2011613
           : A00165503
       : 

*****************************************************************************/
VOS_UINT32 AT_NdisCheckPdpState(
    AT_PDP_STATE_ENUM_U8                enPdpState
)
{
    if ( (enPdpState == g_stAtNdisDhcpPara.enIpv4State)
      || (enPdpState == g_stAtNdisDhcpPara.enIpv6State)
      || (enPdpState == g_stAtNdisDhcpPara.enIpv4v6State) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
     : AT_NdisCheckPdpIdleState
   : ideldeactingPDP
   : 
   : 
     :
   :
   :

       :
  1.       : 2011618
           : S62952
       : 

*****************************************************************************/
VOS_UINT32 AT_NdisCheckPdpIdleState(VOS_VOID)
{
    /*PDPIDLE;DEACTINGOK*/
    if ( (AT_PDP_STATE_DEACTING == g_stAtNdisDhcpPara.enIpv4State)
      || (AT_PDP_STATE_DEACTING == g_stAtNdisDhcpPara.enIpv6State)
      || (AT_PDP_STATE_DEACTING == g_stAtNdisDhcpPara.enIpv4v6State)
      || ( (AT_PDP_STATE_IDLE == g_stAtNdisDhcpPara.enIpv4State)
        && (AT_PDP_STATE_IDLE == g_stAtNdisDhcpPara.enIpv6State)
        && (AT_PDP_STATE_IDLE == g_stAtNdisDhcpPara.enIpv4v6State) ) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
     : AT_NdisAddrProc
   : NDIS
   : pstConfig --- DHCP
             pstEvent  --- 
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 2011510
           : s62952
       : 
  2.       : 2011121
           : /f62575
       : DTS2011113002867, PC UINDISNV
  3.       : 201212
           : c00173809
       : psIPV4PCSCF
  4.       : 20120807
           : f00179208
       : :DTS2015031000157, p-cscf
*****************************************************************************/
VOS_VOID  AT_NdisAddrProc(
    AT_DHCP_CONFIG_STRU                 *pstConfig,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU         *pstEvent
)
{
    VOS_UINT32                          ulIpAddr;
    VOS_UINT8                           ucIndex;

    g_stAtNdisDhcpPara.stIpv4Dhcp.ucRabId                 = pstEvent->ucRabId;
    g_stAtNdisDhcpPara.stIpv4Dhcp.ulIpv4Addr              = pstConfig->ulIPAddr;
    g_stAtNdisDhcpPara.stIpv4Dhcp.ulIpv4GateWay           = pstConfig->ulGateWay;
    g_stAtNdisDhcpPara.stIpv4Dhcp.ulIpv4NetMask           = pstConfig->ulSubNetMask;


    /* DNSDNSDNS */
    if (VOS_TRUE == gstAtNdisAddParam.ulPrimIPv4DNSValidFlag)
    {
        if (VOS_ERR == AT_LenStr2IpAddr(gstAtNdisAddParam.aucPrimIPv4DNSAddr, (VOS_UINT8 *)&ulIpAddr))
        {
            ulIpAddr = 0;
        }

        if (0 != ulIpAddr)
        {
            g_stAtNdisDhcpPara.stIpv4Dhcp.ulIpv4PrimDNS       = VOS_NTOHL(ulIpAddr);
            g_stAtNdisDhcpPara.stIpv4Dhcp.bitOpIpv4PriDns     = VOS_TRUE;
        }
    }
    else
    {
        if ( 0 != pstConfig->ulPrimDNS )
        {
            g_stAtNdisDhcpPara.stIpv4Dhcp.bitOpIpv4PriDns = VOS_TRUE;
            g_stAtNdisDhcpPara.stIpv4Dhcp.ulIpv4PrimDNS   = pstConfig->ulPrimDNS;
        }
        else
        {
            g_stAtNdisDhcpPara.stIpv4Dhcp.bitOpIpv4PriDns = VOS_FALSE;
        }
    }

    /* DNSDNSDNS */
    if (VOS_TRUE == gstAtNdisAddParam.ulSndIPv4DNSValidFlag)
    {
        if (VOS_ERR == AT_LenStr2IpAddr(gstAtNdisAddParam.aucSndIPv4DNSAddr, (VOS_UINT8 *)&ulIpAddr))
        {
            ulIpAddr = 0;
        }

        if (0 != ulIpAddr)
        {
            g_stAtNdisDhcpPara.stIpv4Dhcp.ulIpv4SecDNS    = VOS_NTOHL(ulIpAddr);
            g_stAtNdisDhcpPara.stIpv4Dhcp.bitOpIpv4SecDns = VOS_TRUE;
        }
    }
    else
    {
        if ( 0 != pstConfig->ulSndDNS)
        {
            g_stAtNdisDhcpPara.stIpv4Dhcp.bitOpIpv4SecDns = VOS_TRUE;
            g_stAtNdisDhcpPara.stIpv4Dhcp.ulIpv4SecDNS    = pstConfig->ulSndDNS;
        }
        else
        {
            g_stAtNdisDhcpPara.stIpv4Dhcp.bitOpIpv4SecDns = VOS_FALSE;
        }
    }

    /* WINSWINSWINS */
    if (VOS_TRUE == gstAtNdisAddParam.ulPrimIPv4WINNSValidFlag)
    {
        if (VOS_ERR == AT_LenStr2IpAddr(gstAtNdisAddParam.aucPrimIPv4WINNSAddr, (VOS_UINT8 *)&ulIpAddr))
        {
            ulIpAddr = 0;
        }

        if (0 != ulIpAddr)
        {
            g_stAtNdisDhcpPara.stIpv4Dhcp.ulIpv4PrimWINNS     = VOS_NTOHL(ulIpAddr);
            g_stAtNdisDhcpPara.stIpv4Dhcp.bitOpIpv4PriWINNS   = VOS_TRUE;
        }
    }
    else
    {
        g_stAtNdisDhcpPara.stIpv4Dhcp.ulIpv4PrimWINNS     = 0;
        g_stAtNdisDhcpPara.stIpv4Dhcp.bitOpIpv4PriWINNS   = VOS_FALSE;
    }

    /* WINSWINSWINS */
    if (VOS_TRUE == gstAtNdisAddParam.ulSndIPv4WINNSValidFlag)
    {
        if (VOS_ERR == AT_LenStr2IpAddr(gstAtNdisAddParam.aucSndIPv4WINNSAddr, (VOS_UINT8 *)&ulIpAddr))
        {
            ulIpAddr = 0;
        }

        if (0 != ulIpAddr)
        {
            g_stAtNdisDhcpPara.stIpv4Dhcp.ulIpv4SecWINNS      = VOS_NTOHL(ulIpAddr);
            g_stAtNdisDhcpPara.stIpv4Dhcp.bitOpIpv4SecWINNS   = VOS_TRUE;
        }
    }
    else
    {
        g_stAtNdisDhcpPara.stIpv4Dhcp.ulIpv4SecWINNS      = 0;
        g_stAtNdisDhcpPara.stIpv4Dhcp.bitOpIpv4SecWINNS   = VOS_FALSE;
    }

    /* PCSCF */
    g_stAtNdisDhcpPara.stIpv4Dhcp.stIpv4PcscfList.ucIpv4PcscfAddrNum = AT_MIN(TAF_PCSCF_ADDR_MAX_NUM,
                                                                              pstEvent->stIpv4PcscfList.ucIpv4PcscfAddrNum);

    for (ucIndex = 0; ucIndex < g_stAtNdisDhcpPara.stIpv4Dhcp.stIpv4PcscfList.ucIpv4PcscfAddrNum; ucIndex++)
    {
        g_stAtNdisDhcpPara.stIpv4Dhcp.stIpv4PcscfList.aulIpv4PcscfAddrList[ucIndex] = AT_GetLanAddr32(pstEvent->stIpv4PcscfList.astIpv4PcscfAddrList[ucIndex].aucPcscfAddr);
    }

    return;
}

/*****************************************************************************
     : AT_NdisStateChangeProc
   : NDISPC
   : pEvent -- TAF_PS_CALL_EVENT_INFO_STRU
             ulStat----NDIS:0-; 1-
   : 
     : 
             
   :
   :

       :
  1.       : 201098
           : S62952
       : 

  2.       : 20100704
           : S62952
       : : DTS2011070103435, IPv4v6, ^NDISSTAT
                 , 

  3.       : 20110802
           : A00165503
       : : DTS2011080103770, DETACH, AT
                 ^NDISSTATMP

  4.       : 20111212
           : L00171473
       : : DTS2011110807367, PCUINDIS(
                 PCUINDIS)

  5.       : 20111217
           : C00173809
       : PSAPI

  6.       : 2012728
           : A00165503
       : DTS2012072806289: ^NDISSTAT

  7.       : 2012822
           : A00165503
       : PS

  8.       : 20121120
           : Y00213812
       : DTS2012111907501: PDP Deactive

  9.       : 2013114
           : A00165503
       : DTS2012042104301: PCUINDIS/APP
*****************************************************************************/
VOS_VOID AT_NdisStateChangeProc(
    VOS_UINT8                           ucPdpType,
    AT_PDP_STATUS_ENUM_UINT32           enStat,
    TAF_PS_CAUSE_ENUM_UINT32            enCause
)
{
    VOS_UINT16                          usLength;
    VOS_UINT8                           aucAtStrIpv4[] = "IPV4";
    VOS_UINT8                           aucAtStrIpv6[] = "IPV6";

    VOS_UINT32                          ul3gppSmCause;

    usLength = 0;

    if (AT_PDP_STATUS_DEACT == enStat)
    {
        ul3gppSmCause = AT_Get3gppSmCauseByPsCause(enCause);

        switch (ucPdpType)
        {
            case TAF_PDP_IPV4:
                usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                            "%s^NDISSTAT:%d,%d,,\"%s\"%s",
                                            gaucAtCrLf,
                                            enStat,
                                            ul3gppSmCause,
                                            aucAtStrIpv4,
                                            gaucAtCrLf);
                break;

            case TAF_PDP_IPV6:
                usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                            "%s^NDISSTAT:%d,%d,,\"%s\"%s",
                                            gaucAtCrLf,
                                            enStat,
                                            ul3gppSmCause,
                                            aucAtStrIpv6,
                                            gaucAtCrLf);
                break;

            case TAF_PDP_IPV4V6:

                usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                            "%s^NDISSTAT:%d,%d,,\"%s\"%s",
                                            gaucAtCrLf,
                                            enStat,
                                            ul3gppSmCause,
                                            aucAtStrIpv4,
                                            gaucAtCrLf);

                At_SendResultData(AT_NDIS_GET_USR_PORT_INDEX(), pgucAtSndCodeAddr, usLength);

                usLength  = 0;

                usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                            "%s^NDISSTAT:%d,%d,,\"%s\"%s",
                                            gaucAtCrLf,
                                            enStat,
                                            ul3gppSmCause,
                                            aucAtStrIpv6,
                                            gaucAtCrLf);
                break;

            default:
                AT_ERR_LOG("AT_NdisStateChangeProc:ERROR: Wrong PDP type!");
                return;
        }
    }
    else
    {
        switch (ucPdpType)
        {
            case TAF_PDP_IPV4:
                usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                            "%s^NDISSTAT:%d,,,\"%s\"%s",
                                            gaucAtCrLf,
                                            enStat,
                                            aucAtStrIpv4,
                                            gaucAtCrLf);
                break;

            case TAF_PDP_IPV6:
                usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                            "%s^NDISSTAT:%d,,,\"%s\"%s",
                                            gaucAtCrLf,
                                            enStat,
                                            aucAtStrIpv6,
                                            gaucAtCrLf);
                break;

            case TAF_PDP_IPV4V6:
                usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                            "%s^NDISSTAT:%d,,,\"%s\"%s",
                                            gaucAtCrLf,
                                            enStat,
                                            aucAtStrIpv4,
                                            gaucAtCrLf);

                At_SendResultData(AT_NDIS_GET_USR_PORT_INDEX(), pgucAtSndCodeAddr, usLength);

                usLength  = 0;

                usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                            "%s^NDISSTAT:%d,,,\"%s\"%s",
                                            gaucAtCrLf,
                                            enStat,
                                            aucAtStrIpv6,
                                            gaucAtCrLf);
                break;

            default:
                AT_ERR_LOG("AT_NdisStateChangeProc:ERROR: Wrong PDP type!");
                return;
        }
    }

    At_SendResultData(AT_NDIS_GET_USR_PORT_INDEX(), pgucAtSndCodeAddr, usLength);

    return;
}

/*****************************************************************************
     : AT_NdisGetState
   : NDIS/
   : ucPdpType --- PDP
   : 
     : AT_PDP_STATE_ENUM_U8  /
   :
   :

       :
  1.       : 201153
           : S62952
       : 

*****************************************************************************/
AT_PDP_STATE_ENUM_U8 AT_NdisGetState(
    VOS_UINT8                           ucPdpType
)
{
    if (TAF_PDP_IPV4 == ucPdpType )
    {
        return g_stAtNdisDhcpPara.enIpv4State;
    }
    else if (TAF_PDP_IPV6 == ucPdpType )
    {
        return g_stAtNdisDhcpPara.enIpv6State;
    }
    else
    {
        return g_stAtNdisDhcpPara.enIpv4v6State;
    }
}

/*****************************************************************************
     : AT_NdisSetState
   : NDIS
   : ucPdpType --- PDP
             enState   --- PDP
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 201153
           : S62952
       : 
  2.       : 20130708
           : Y00213812
       : VoLTE_PhaseI PDP IPv4v6
*****************************************************************************/
VOS_VOID AT_NdisSetState(
    VOS_UINT8                           ucPdpType,
    AT_PDP_STATE_ENUM_U8                enState
)
{
    if (TAF_PDP_IPV4 == ucPdpType)
    {
        g_stAtNdisDhcpPara.enIpv4State   = enState;
    }
/* Modified by s62952 for AT Project2011-10-17,  Begin*/
    else if (TAF_PDP_IPV6 == ucPdpType)
    {
        g_stAtNdisDhcpPara.enIpv6State   = enState;
    }
    /* Added by Y00213812 for VoLTE_PhaseI , 2013-07-08, begin */
    else if (TAF_PDP_IPV4V6 == ucPdpType)
    {
        g_stAtNdisDhcpPara.enIpv4v6State = enState;
    }
    else
    {}

    /* Added by Y00213812 for VoLTE_PhaseI , 2013-07-08, end */

/* Modified by s62952 for AT Project2011-10-17,  Begin*/

    return;
}

/*****************************************************************************
     : AT_NdisDhcpRest
   : DHCP
   : 
   : 
     :
   :
   :

       :
  1.       : 201099
           : s62952
       : 

*****************************************************************************/
VOS_VOID AT_NdisDhcpRest(VOS_VOID)
{
    TAF_MEM_SET_S(&g_stAtNdisDhcpPara.stIpv4Dhcp,
               sizeof(g_stAtNdisDhcpPara.stIpv4Dhcp),
               0x00,
               sizeof(AT_IPV4_DHCP_PARAM_STRU));

    return;
}

/*****************************************************************************
     : AT_E5GetDhcpPara
   : DHCP(DHCP)
   : 
   : 
     :
   :
   :

       :
  1.       : 2010910
           : s62952
       : 

*****************************************************************************/
VOS_VOID AT_NdisGetDhcpPara(
    AT_DHCP_PARA_STRU                  *pstConfig
)
{
    /* DHCP */
    pstConfig->stDhcpCfg.ulIPAddr     = VOS_HTONL(g_stAtNdisDhcpPara.stIpv4Dhcp.ulIpv4Addr);
    pstConfig->stDhcpCfg.ulSubNetMask = VOS_HTONL(g_stAtNdisDhcpPara.stIpv4Dhcp.ulIpv4NetMask);
    pstConfig->stDhcpCfg.ulGateWay    = VOS_HTONL(g_stAtNdisDhcpPara.stIpv4Dhcp.ulIpv4GateWay);
    pstConfig->stDhcpCfg.ulPrimDNS    = VOS_HTONL(g_stAtNdisDhcpPara.stIpv4Dhcp.ulIpv4PrimDNS);
    pstConfig->stDhcpCfg.ulSndDNS     = VOS_HTONL(g_stAtNdisDhcpPara.stIpv4Dhcp.ulIpv4SecDNS);
    return;
}

/*****************************************************************************
     : AT_ProcNdisDeRegFCPoint
   : NDISPDP
   : TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent,
             TAF_PDP_TYPE_ENUM_UINT8             enPdpType
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20130708
           : Y00213812
       : VoLTE_PhaseI 

*****************************************************************************/
VOS_VOID  AT_ProcNdisDeRegFCPoint(
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU  *pstEvent,
    TAF_PDP_TYPE_ENUM_UINT8               enPdpType
)
{
    VOS_UINT32                          ulRet;
    MODEM_ID_ENUM_UINT16                enModemId;

    enModemId                           = MODEM_ID_0;

    ulRet = AT_GetModemIdFromClient((AT_CLIENT_TAB_INDEX_UINT8)(pstEvent->stCtrl.usClientId), &enModemId);

    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_ProcNdisDeRegFCPoint:Get Modem Id fail");
        return;
    }

    /* NDIS */
    AT_DeRegNdisFCPoint(pstEvent->ucRabId, enModemId);

}

/*****************************************************************************
     : AT_ProcNdisRegFCPoint
   : NDISPDP,
   : TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent,
             TAF_PDP_TYPE_ENUM_UINT8             enPdpType
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20130708
           : Y00213812
       : VoLTE_PhaseI 

*****************************************************************************/
VOS_VOID  AT_ProcNdisRegFCPoint(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
)
{
    VOS_UINT32                          ulRet;
    AT_FCID_MAP_STRU                    stFCPriOrg;
    FC_PRI_ENUM_UINT8                   enFCPriCurrent;
    MODEM_ID_ENUM_UINT16                enModemId;

    enModemId                           = MODEM_ID_0;

    ulRet = AT_GetModemIdFromClient((AT_CLIENT_TAB_INDEX_UINT8)(pstEvent->stCtrl.usClientId), &enModemId);

    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_ProcNdisRegFCPoint:Get Modem Id fail");
        return;
    }

    ulRet = AT_GetFcPriFromMap(FC_ID_NIC_1 ,&stFCPriOrg);
    if (VOS_OK == ulRet)
    {
        /* FC ID.*/
        if (VOS_TRUE != stFCPriOrg.ulUsed)
        {
            /* NDIS */
            AT_RegNdisFCPoint(pstEvent, FC_ID_NIC_1, enModemId);
        }
        else
        {
            if (TAF_USED == pstEvent->bitOpUmtsQos)
            {
                enFCPriCurrent = AT_GetFCPriFromQos(&pstEvent->stUmtsQos);
            }
            else
            {
                enFCPriCurrent = FC_PRI_FOR_PDN_NONGBR;
            }

            /* FCFC*/
            if(enFCPriCurrent > stFCPriOrg.enFcPri)
            {
                AT_ChangeFCPoint(&pstEvent->stCtrl,enFCPriCurrent, FC_ID_NIC_1);
            }
        }
    }

}

/*****************************************************************************
     : AT_NdisIpv4ActCnfProc
   : IPV4PDP
   : pstEvent --- 
   : 
     :
   :
   :

       :
  1.       : 2011612
           : S62952
       : 
  2.       : 20111020
           : A00165503
       : AT Project: V3R2/V7R1IPv6, 
  3.       : 20111217
           : C00173809
       : PSNDIS,FEATURE_IPV6IPV6
  4.       : 20121221
           : l00227485
       : DSDA PhaseII
*****************************************************************************/
VOS_VOID  AT_NdisIpv4ActCnfProc(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU        *pstEvent
)
{
    VOS_UINT8                           ucCid;
    VOS_UINT32                          ulRet;

    g_stAtNdisDhcpPara.ucIpv4Cid = pstEvent->ucCid;

    /* IPV4DHCP */
    AT_CtrlConnIndProc(pstEvent, AT_NDIS_USER);

    /* NDISPDP, */
    AT_ProcNdisRegFCPoint(pstEvent, TAF_PDP_IPV4);

    /* IPV4PDNNDIS */
    AT_SendNdisIPv4PdnInfoCfgReq(AT_NDIS_GET_USR_PORT_INDEX(),
                                 &(g_stAtNdisDhcpPara.stIpv4Dhcp));

    /* NDISPDP, SharePdp */
    AT_PS_ProcActSharePdpState(pstEvent, TAF_PDP_IPV4);

    /* IPV4V6PDP */
    if (TAF_PDP_IPV4V6 == g_enAtFirstNdisActPdpType)
    {
        switch (g_enAtNdisActPdpType)
        {
            /* PDPPDPIPV4
               IPV6PDPTAF_PDP_IPV6IPV6PDP
               IPV4IPV6PDP */
            case TAF_PDP_IPV4:
                if (AT_PDP_STATE_IDLE == AT_NdisGetState(TAF_PDP_IPV6))
                {
                    /* CID */
                    ulRet       = TAF_AGENT_FindCidForDial(pstEvent->stCtrl.usClientId, &ucCid);
                    if (VOS_OK == ulRet )
                    {
                        AT_NdisPdpActOrig(pstEvent->stCtrl.usClientId, ucCid, TAF_PDP_IPV6);
                    }
                }
                break;

            /* PDP */
            case TAF_PDP_IPV4V6:
                /* PDPIDLE */
                AT_NdisSetState(g_enAtNdisActPdpType, AT_PDP_STATE_IDLE);

                AT_NdisActCnfBackProc(pstEvent);
                break;

            default:
                AT_WARN_LOG("AT_NdisIpv4ActCnfProc:g_enAtNdisActPdpType is error!");
                break;
        }
    }

    return;
}

/*****************************************************************************
     : AT_NdisPsRspPdpActEvtCnfProc
   : pdpNdis
   : ucIndex --- 
             pEvent  --- 
   : 
     : 
   :
   :

       :
  1.       : 201155
           : S62952
       : 

  2.       : 20111020
           : A00165503
       : AT Project: V3R2/V7R1IPv6, 

  3.       : 20111217
           : C00173809
       : PSNDIS

  4.       : 2012315
           : l60609
       : DTS2012030804093:^NDISDUP

  5.       : 2012728
           : A00165503
       : DTS2012072806289: ^NDISSTAT

  6.       : 20121120
           : Y00213812
       : DTS2012111907501: PDPTAF_PS_CAUSE_SUCCESS
*****************************************************************************/
VOS_VOID  AT_NdisPsRspPdpActEvtCnfProc(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
    /**/
    AT_ActiveUsbNet();

    /* PC */
    AT_NdisStateChangeProc(pstEvent->stPdpAddr.enPdpType, AT_PDP_STATE_ACTED, TAF_PS_CAUSE_SUCCESS);

    /* PDP act */
    AT_NdisSetState(pstEvent->stPdpAddr.enPdpType, AT_PDP_STATE_ACTED);

    /* PDP*/
    switch ( pstEvent->stPdpAddr.enPdpType )
    {
        case TAF_PDP_IPV4:
            AT_NdisIpv4ActCnfProc(pstEvent);
            break;

        case TAF_PDP_IPV6:
            AT_NdisIpv6ActCnfProc(pstEvent);
            break;

        case TAF_PDP_IPV4V6:
            AT_NdisIpv4v6ActCnfProc(pstEvent);
            break;

        default:
            AT_WARN_LOG("AT_NdisPsRspPdpActEvtCnfProc:pdp type invaild!");
            break;
    }

    return;
}

/*****************************************************************************
     : AT_NdisPdpActOrig
   : PDP
   :  VOS_UINT16                  usClientId
              VOS_UINT8                   ucCid
              TAF_PDP_TYPE_ENUM_UINT8     ucPdpType
   : 
     :
   :
   :

       :
  1.       : 2011611
           : S62952
       : 
  2.       : 20110708
           : A00165503
       : : DTS2011070600664, NDISCID, 
                 AT
  3.       : 20111231
           : c00173809
       : PSNDIS
*****************************************************************************/
VOS_VOID AT_NdisPdpActOrig(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCid,
    TAF_PDP_TYPE_ENUM_UINT8             ucPdpType
)
{
    TAF_PS_DIAL_PARA_STRU               stDialParaInfo;

    TAF_MEM_SET_S(&stDialParaInfo, sizeof(stDialParaInfo), 0x00, sizeof(TAF_PS_DIAL_PARA_STRU));

    /* QOS */
    if (VOS_OK != AT_PS_SetQosPara(usClientId, AT_NDIS_GET_USR_CID(), ucCid))
    {
        return;
    }

    AT_GetPsDialParamFromAtDialParam(&stDialParaInfo,&gstAtNdisAddParam);
    stDialParaInfo.ucCid        = ucCid;
    stDialParaInfo.enPdpType    = ucPdpType;

    /* PDP */
    if (VOS_OK == TAF_PS_CallOrig(WUEPS_PID_AT,
                                  AT_PS_BuildNdisExClientId(AT_NDIS_GET_USR_PORT_INDEX(), usClientId),
                                  0, &stDialParaInfo))
    {
        if (TAF_PDP_IPV4 == stDialParaInfo.enPdpType)
        {
            g_stAtNdisDhcpPara.ucIpv4Cid = ucCid;
        }
        else
        {
            g_stAtNdisDhcpPara.ucIpv6Cid = ucCid;
        }

        g_enAtNdisActPdpType = ucPdpType;

        AT_NdisSetState(ucPdpType, AT_PDP_STATE_ACTING);
    }

    return;
}


/*****************************************************************************
     : AT_NdisPsRspPdpActEvtRejProc
   : pdpNDIS
   : ucIndex --- 
             pEvent  --- 
   : 
     : 
   :
   :

       :
  1.       : 201155
           : S62952
       : 

  2.       : 20110705
           : A00165503
       : : DTS2011070402532, NDISIPv4(
                 ), IPv6IPv4v6, IPv4
                 

  3.       : 20111020
           : A00165503
       : AT Project: V3R2/V7R1IPv6, 

  4.       : 2012728
           : A00165503
       : DTS2012072806289: ^NDISSTAT

  5.       : 2012822
           : A00165503
       : PS

  6.       : 20121120
           : Y00213812
       : DTS2012111907501: PDP

  7.       : 2013508
           : Y00213812
       : V9R1 IPv6&TAF/SM Project
*****************************************************************************/
VOS_VOID  AT_NdisPsRspPdpActEvtRejProc(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU  *pstEvent
)
{
    AT_PDP_ENTITY_STRU                 *pstNdisPdpEntity;
    AT_PDP_STATE_ENUM_U8                enPreIpv4State;

    /*  */
    pstNdisPdpEntity = AT_NDIS_GetPdpEntInfoAddr();
    enPreIpv4State = pstNdisPdpEntity->enIpv4State;

    /* IPV4 ONLYIPV6 ONLYIPV4V6
       IPv4IPv6PDP */
    if (TAF_PDP_IPV4V6 == g_enAtFirstNdisActPdpType)
    {
        if (TAF_PDP_IPV4V6 == g_enAtNdisActPdpType)
        {
            /* IPv4IPv6PDP */
            if (TAF_PS_CAUSE_SM_NW_UNKNOWN_PDP_ADDR_OR_TYPE == pstEvent->enCause)
            {
                /* PDPtypeIDLE */
                AT_NdisSetState(g_enAtNdisActPdpType, AT_PDP_STATE_IDLE);

                AT_NdisPdpActOrig(pstEvent->stCtrl.usClientId, pstEvent->ucCid, TAF_PDP_IPV4);
            }
            else
            {
                /* PDPIDLE */
                AT_NdisSetState(g_enAtNdisActPdpType, AT_PDP_STATE_IDLE);

                /* PDP */
                AT_NdisStateChangeProc(g_enAtNdisActPdpType, AT_PDP_STATUS_DEACT, pstEvent->enCause);

                /* NDIS */
                TAF_MEM_SET_S(&gstAtNdisAddParam, sizeof(gstAtNdisAddParam), 0x00, sizeof(AT_DIAL_PARAM_STRU));
            }
        }
        else if ( TAF_PDP_IPV4 == g_enAtNdisActPdpType )
        {
            /* IPv4v6PDP, , 28, 
               IPv4/IPv6PDP, IPv4, IPv6,
               IPV4PDP, IPV6
               PDPPDP, IPv6PDP, 
               IPv4PDP */
            AT_NdisSetState(g_enAtNdisActPdpType, AT_PDP_STATE_IDLE);

            /* PDP */
            AT_NdisStateChangeProc(g_enAtNdisActPdpType, AT_PDP_STATUS_DEACT, pstEvent->enCause);

            if ( (AT_PDP_STATE_IDLE == AT_NdisGetState(TAF_PDP_IPV6))
              && (AT_PDP_STATE_ACTING == enPreIpv4State) )
            {
                /* IPv6, , IPv6PDP */
                AT_NdisPdpActOrig(pstEvent->stCtrl.usClientId, pstEvent->ucCid, TAF_PDP_IPV6);
            }
            else
            {
                /* NDIS */
                TAF_MEM_SET_S(&gstAtNdisAddParam, sizeof(gstAtNdisAddParam), 0x00, sizeof(AT_DIAL_PARAM_STRU));
            }
        }
        else
        {
            /* IPv6, IPv4, IPv4PDP
               , IPv4PDP, PDP */
             AT_NdisSetState(g_enAtNdisActPdpType, AT_PDP_STATE_IDLE);

             /* PDP */
            AT_NdisStateChangeProc(g_enAtNdisActPdpType, AT_PDP_STATUS_DEACT, pstEvent->enCause);

             /* NDIS */
             TAF_MEM_SET_S(&gstAtNdisAddParam, sizeof(gstAtNdisAddParam), 0x00, sizeof(AT_DIAL_PARAM_STRU));
        }
    }
    else
    {
        /* PDPIDLE */
        AT_NdisSetState(g_enAtNdisActPdpType, AT_PDP_STATE_IDLE);

        /* PDP */
        AT_NdisStateChangeProc(g_enAtNdisActPdpType, AT_PDP_STATUS_DEACT, pstEvent->enCause);

        /* NDIS */
        TAF_MEM_SET_S(&gstAtNdisAddParam, sizeof(gstAtNdisAddParam), 0x00, sizeof(AT_DIAL_PARAM_STRU));
    }

    return;
}

/*****************************************************************************
     : AT_NdisIPv4DeactiveCnfProc
   : IPV4pdpNdis
   : pEvent  --- 
   : 
     : 
   :
   :

       :
  1.       : 20111219
           : c00173809
       : /PS

  2.       : 201262
           : A00165503
       : DTS2012060105018: IPv4v6, PDP(-
                 #39), UE
  3.       : 20130708
           : Y00213812
       : VoLTE_PhaseI EVENT

*****************************************************************************/
VOS_VOID AT_NdisIPv4DeactiveCnfProc(
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
)
{
    AT_PDP_STATE_ENUM_U8                enState;

    AT_NdisSetState(TAF_PDP_IPV4, AT_PDP_STATE_IDLE);
    AT_NdisDhcpRest();

    /* NDISPDP */
    AT_ProcNdisDeRegFCPoint(pstEvent, TAF_PDP_IPV4);

    /* NDISPDP, SharePdp*/
    AT_PS_ProcDeactSharePdpState(pstEvent, TAF_PDP_IPV4);

    /* PDP */
    enState     = AT_NdisGetState(TAF_PDP_IPV6);
    if ( (AT_PDP_STATE_IDLE     != enState)
      && (AT_PDP_STATE_DEACTING != enState) )
    {
        if (AT_SUCCESS == TAF_PS_CallEnd(WUEPS_PID_AT,
                                         AT_PS_BuildNdisExClientId(AT_NDIS_GET_USR_PORT_INDEX(), pstEvent->stCtrl.usClientId),
                                         0,
                                         g_stAtNdisDhcpPara.ucIpv6Cid))
        {
            AT_NdisSetState(TAF_PDP_IPV6, AT_PDP_STATE_DEACTING);
        }
    }
}

/*****************************************************************************
     : AT_NdisIPv6DeactiveCnfProc
   : IPV6pdpNdis
   : pEvent  --- 
   : 
     : 
   :
   :

       :
  1.       : 20111219
           : c00173809
       : /PS

  2.       : 201262
           : A00165503
       : DTS2012060105018: IPv4v6, PDP(-
                 #39), UE
  3.       : 20130708
           : Y00213812
       : VoLTE_PhaseI EVENT

*****************************************************************************/
VOS_VOID AT_NdisIPv6DeactiveCnfProc(
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
)
{
    AT_PDP_STATE_ENUM_U8                enState;

    AT_NdisSetState(TAF_PDP_IPV6, AT_PDP_STATE_IDLE);

    AT_NdisIpv6DhcpRest();

    /* NDISPDP */
    AT_ProcNdisDeRegFCPoint(pstEvent, TAF_PDP_IPV6);

    /* NDISPDP, SharePdp*/
    AT_PS_ProcDeactSharePdpState(pstEvent, TAF_PDP_IPV6);

    /*PDP*/
    enState = AT_NdisGetState(TAF_PDP_IPV4);
    if ( (AT_PDP_STATE_IDLE     != enState)
      && (AT_PDP_STATE_DEACTING != enState) )
    {
        if (AT_SUCCESS == TAF_PS_CallEnd(WUEPS_PID_AT,
                                         AT_PS_BuildNdisExClientId(AT_NDIS_GET_USR_PORT_INDEX(), pstEvent->stCtrl.usClientId),
                                         0,
                                         g_stAtNdisDhcpPara.ucIpv4Cid))
        {
            AT_NdisSetState(TAF_PDP_IPV4,AT_PDP_STATE_DEACTING);
        }
    }
}

/*****************************************************************************
     : AT_NdisIPv4v6DeactiveCnfProc
   : IPV4V6pdpNdis
   : pEvent  --- 
   : 
     : 
   :
   :

       :
  1.       : 20111219
           : c00173809
       : /PS

  2.       : 201262
           : A00165503
       : DTS2012060105018: IPv4v6, PDP(-
                 #39), UE
  3.       : 20130708
           : Y00213812
       : VoLTE_PhaseI EVENT
*****************************************************************************/
VOS_VOID AT_NdisIPv4v6DeactiveCnfProc(
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
)
{
    AT_NdisDhcpRest();

    AT_NdisIpv6DhcpRest();

    /* NDISPDP */
    AT_ProcNdisDeRegFCPoint(pstEvent, TAF_PDP_IPV4V6);

    /* NDISPDP, SharePdp*/
    AT_PS_ProcDeactSharePdpState(pstEvent, TAF_PDP_IPV4V6);
}

/*****************************************************************************
     : AT_NdisPsRspPdpDeactEvtCnfProc
   : pdpNdis
   : ucIndex --- 
             pEvent  --- 
   : 
     : 
   :
   :

       :
  1.       : 201155
           : S62952
       : 
  2.       : 20110802
           : A00165503
       : : DTS2011080103770, DETACH, AT
                 ^NDISSTATMP
  3.       : 20111020
           : A00165503
       : AT Project: V3R2/V7R1IPv6, 
  4.       : 20111217
           : C00173809
       : PSNDISPDPADS
  5.       : 2012728
           : A00165503
       : DTS2012072806289: ^NDISSTAT
  6.       : 20121120
           : Y00213812
       : DTS2012111907501: PDP Deactive
  7.       : 20130708
           : Y00213812
       : VoLTE_PhaseI EVENT
*****************************************************************************/
VOS_VOID  AT_NdisPsRspPdpDeactEvtCnfProc(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
)
{
    /* PC */
    AT_NdisStateChangeProc(pstEvent->enPdpType, AT_PDP_STATUS_DEACT, pstEvent->enCause);

    /* TTFRAB */
    AT_SendNdisRelReq(pstEvent);

    /* NDISIDLE */
    AT_NdisSetState(pstEvent->enPdpType, AT_PDP_STATE_IDLE);

    if (TAF_PDP_IPV4 == pstEvent->enPdpType)
    {
        AT_NdisIPv4DeactiveCnfProc(pstEvent);
    }
    else if (TAF_PDP_IPV6 == pstEvent->enPdpType)
    {
        AT_NdisIPv6DeactiveCnfProc(pstEvent);
    }
    else if (TAF_PDP_IPV4V6 == pstEvent->enPdpType)
    {
        AT_NdisIPv4v6DeactiveCnfProc(pstEvent);
    }
    else
    {
        ;
    }

    /* NDIS */
    if ( (AT_PDP_STATE_IDLE == g_stAtNdisDhcpPara.enIpv4State)
      && (AT_PDP_STATE_IDLE == g_stAtNdisDhcpPara.enIpv6State)
      && (AT_PDP_STATE_IDLE == g_stAtNdisDhcpPara.enIpv4v6State) )
    {
        TAF_MEM_SET_S(&gstAtNdisAddParam, sizeof(gstAtNdisAddParam), 0x00, sizeof(AT_DIAL_PARAM_STRU));
    }

    /*  */
    AT_DeActiveUsbNet();

    return;
}

/*****************************************************************************
     : AT_NdisPsRspPdpDeactivatedEvtProc
   : pdpNdis
   : ucIndex --- 
             pEvent  --- 
   : 
     : 
   :
   :

       :
  1.       : 201155
           : S62952
       : 
  2.       : 20110802
           : A00165503
       : : DTS2011080103770, DETACH, AT
                 ^NDISSTATMP
  3.       : 20111020
           : A00165503
       : AT Project: V3R2/V7R1IPv6, 
  4.       : 20111222
           : c00173809
       : PSIPV6
  5.       : 2012728
           : A00165503
       : DTS2012072806289: ^NDISSTAT
  6.       : 20121120
           : Y00213812
       : DTS2012111907501: PDP Deactive
  7.       : 20130708
           : Y00213812
       : VoLTE_PhaseI EVENT
*****************************************************************************/
VOS_VOID  AT_NdisPsRspPdpDeactivatedEvtProc(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_DEACTIVATE_IND_STRU *pstEvent
)
{

    /* ^NDISSTATNDIS */
    AT_NdisStateChangeProc(pstEvent->enPdpType, AT_PDP_STATUS_DEACT, pstEvent->enCause);

    /* TTFRAB */
    AT_SendNdisRelReq(pstEvent);

    /* NDISIDLE */
    AT_NdisSetState(pstEvent->enPdpType, AT_PDP_STATE_IDLE);

    if (TAF_PDP_IPV4 == pstEvent->enPdpType)
    {
        AT_NdisIPv4DeactiveCnfProc(pstEvent);
    }
    else if (TAF_PDP_IPV6 == pstEvent->enPdpType)
    {
        AT_NdisIPv6DeactiveCnfProc(pstEvent);
    }
    else if (TAF_PDP_IPV4V6 == pstEvent->enPdpType)
    {
        AT_NdisIPv4v6DeactiveCnfProc(pstEvent);
    }
    else
    {
        ;
    }

    /* NDIS */
    if ( (AT_PDP_STATE_IDLE == g_stAtNdisDhcpPara.enIpv4State)
      && (AT_PDP_STATE_IDLE == g_stAtNdisDhcpPara.enIpv6State)
      && (AT_PDP_STATE_IDLE == g_stAtNdisDhcpPara.enIpv4v6State) )
    {
        TAF_MEM_SET_S(&gstAtNdisAddParam, sizeof(gstAtNdisAddParam), 0x00, sizeof(AT_DIAL_PARAM_STRU));
    }

    /*  */
    AT_DeActiveUsbNet();

    return;
}

/*****************************************************************************
     : AT_EnableNdisFlowCtl
   : NDIS
   : VOS_UINT32                          ulParam1,
             VOS_UINT32                          ulParam2
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 20111217
           : c00173809
       : 
*****************************************************************************/
VOS_UINT32 AT_EnableNdisFlowCtl(
    VOS_UINT32                          ulParam1,
    VOS_UINT32                          ulParam2
)
{
    /* udi_ioctl */
    VOS_UINT32  ulEnbflg = NCM_IOCTL_FLOW_CTRL_ENABLE;

    if (0 != mdrv_udi_ioctl (g_ulAtUdiNdisHdl, NCM_IOCTL_FLOW_CTRL_NOTIF, (VOS_VOID*)(&ulEnbflg)))
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
     : AT_DisableNdisFlowCtl
   : NDIS
   : VOS_UINT32                          ulParam1,
             VOS_UINT32                          ulParam2
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 20111217
           : c00173809
       : 
*****************************************************************************/
VOS_UINT32 AT_DisableNdisFlowCtl(
    VOS_UINT32                          ulParam1,
    VOS_UINT32                          ulParam2
)
{
    /* udi_ioctl */
    VOS_UINT32  ulEnbflg = NCM_IOCTL_FLOW_CTRL_DISABLE;

    if (0 != mdrv_udi_ioctl (g_ulAtUdiNdisHdl, NCM_IOCTL_FLOW_CTRL_NOTIF, (VOS_VOID*)(&ulEnbflg)))
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
     : AT_RegNdisFCPoint
   : NDIS
   : TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
             FC_ID_ENUM_UINT8                    enFcId
             MODEM_ID_ENUM_UINT16                enModemId
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 20111217
           : c00173809
       : 
  2.       : 2012224
           : L47619
       : V7R1C50 IPC:NDIS
  3.       : 20121217
           : l60609
       : DSDA Phase II
  4.       : 20130415
           : f00179208
       : C
  5.       : 20130708
           : Y00213812
       : VoLTE_PhaseI EVENT
*****************************************************************************/
VOS_UINT32 AT_RegNdisFCPoint(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent,
    FC_ID_ENUM_UINT8                    enFcId,
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    /* Modified by l60609 for DSDA Phase II, 2012-12-17, Begin */
    FC_REG_POINT_STRU                   stRegFcPoint;
    VOS_UINT32                          ulRet;
    FC_PRI_ENUM_UINT8                   enFCPri;

    TAF_MEM_SET_S(&stRegFcPoint, sizeof(stRegFcPoint), 0x00, sizeof(FC_REG_POINT_STRU));

    /* RABID */
    FC_ChannelMapCreate(enFcId, pstEvent->ucRabId, enModemId);

    stRegFcPoint.enFcId             = enFcId;

    /* RAB QoS, */
    /*  FC_PRI_3        
        FC_PRI_4        NONGBR
        FC_PRI_5        GBR */

    if (TAF_USED == pstEvent->bitOpUmtsQos)
    {
        enFCPri = AT_GetFCPriFromQos(&pstEvent->stUmtsQos);
    }
    else
    {
        enFCPri = FC_PRI_FOR_PDN_NONGBR;
    }
    stRegFcPoint.enFcPri            = enFCPri;
    stRegFcPoint.enPolicyId         = FC_POLICY_ID_MEM;
    stRegFcPoint.enModemId          = enModemId;
    stRegFcPoint.pClrFunc           = AT_DisableNdisFlowCtl;
    stRegFcPoint.pSetFunc           = AT_EnableNdisFlowCtl;
    stRegFcPoint.pRstFunc           = AT_ResetFlowCtl;
    stRegFcPoint.ulParam2           = enFcId;
    stRegFcPoint.ulParam1           = (VOS_UINT32)pstEvent->stCtrl.usClientId;

    /* ,MEM,CPU,CDSGPRS */
    ulRet = FC_RegPoint(&stRegFcPoint);
    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_RegNdisFCPoint: ERROR: reg mem point Failed.");
        return VOS_ERR;
    }

    stRegFcPoint.enPolicyId         = FC_POLICY_ID_CPU_A;
    ulRet = FC_RegPoint(&stRegFcPoint);
    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_RegNdisFCPoint: ERROR: reg a cpu point Failed.");
        return VOS_ERR;
    }

    stRegFcPoint.enPolicyId         = FC_POLICY_ID_CDS;
    ulRet = FC_RegPoint(&stRegFcPoint);
    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_RegNdisFCPoint: ERROR: reg cds point Failed.");
        return VOS_ERR;
    }

    stRegFcPoint.enPolicyId         = FC_POLICY_ID_GPRS;
    ulRet = FC_RegPoint(&stRegFcPoint);
    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_RegNdisFCPoint: ERROR: reg gprs point Failed.");
        return VOS_ERR;
    }

    /* Modified by l60609 for DSDA Phase II, 2012-12-17, End */

    /* FCIDFC Pri */
    g_stFcIdMaptoFcPri[FC_ID_NIC_1].ulUsed      = VOS_TRUE;
    g_stFcIdMaptoFcPri[FC_ID_NIC_1].enFcPri     = enFCPri;
    /* RABIDRABID */
    g_stFcIdMaptoFcPri[FC_ID_NIC_1].ulRabIdMask |= ((VOS_UINT32)1 << (pstEvent->ucRabId));
    g_stFcIdMaptoFcPri[FC_ID_NIC_1].enModemId   = enModemId;

    /*  */
    AT_MNTN_TraceRegFcPoint((VOS_UINT8)pstEvent->stCtrl.usClientId, AT_FC_POINT_TYPE_NDIS);

    return VOS_OK;
}

/*****************************************************************************
     : AT_DeRegNdisFCPoint
   : NDIS
   : VOS_UINT8                           ucRabId
             MODEM_ID_ENUM_UINT16                enModemId
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 20111217
           : c00173809
       : 
  2.       : 2012224
           : L47619
       : V7R1C50 IPC:NDIS
  3.       : 20130415
           : f00179208
       : C
*****************************************************************************/
VOS_UINT32 AT_DeRegNdisFCPoint(
    VOS_UINT8                           ucRabId,
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    FC_ID_ENUM_UINT8                    enFcId;
    VOS_UINT32                          ulRet;

    /* FC_DeRegPoint,FC_ChannelMapDelete */
    FC_ChannelMapDelete(ucRabId, enModemId);

    /* NDIS */
    enFcId = FC_ID_NIC_1;

    ulRet = FC_DeRegPoint(enFcId, enModemId);
    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_DeRegNdisFCPoint: ERROR: de reg point Failed.");
        return VOS_ERR;
    }

    /* FCIDFC Pri */
    g_stFcIdMaptoFcPri[FC_ID_NIC_1].ulUsed      = VOS_FALSE;
    g_stFcIdMaptoFcPri[FC_ID_NIC_1].enFcPri     = FC_PRI_BUTT;
    /* RABIDRABID */
    g_stFcIdMaptoFcPri[FC_ID_NIC_1].ulRabIdMask &= ~((VOS_UINT32)1 << ucRabId);
    g_stFcIdMaptoFcPri[FC_ID_NIC_1].enModemId   = MODEM_ID_BUTT;

    /*  */
    AT_MNTN_TraceDeregFcPoint(AT_CLIENT_TAB_NDIS_INDEX, AT_FC_POINT_TYPE_NDIS);

    return VOS_OK;
}

/*****************************************************************************
     : AT_UsbEthHostAccumTuneCB
   : FC()HOSTNCM/ECM
   : pstFcDrvAssemPara - NCM/ECM, :
                                 1. HOST OUT
   : 
     : VOS_OK            - 
             VOS_ERR           - 
   :
   :

       :
  1.       : 2012514
           : A00165503
       : 

*****************************************************************************/
VOS_UINT32 AT_UsbEthHostAccumTuneCB(
    FC_DRV_ASSEM_PARA_STRU             *pstFcDrvAssemPara
)
{
    VOS_UINT8                          *pucSystemAppConfig;
    VOS_UINT32                          ulHostOutTimeout;

    /* : MP/WEBUI/ANDROID */
    pucSystemAppConfig = AT_GetSystemAppConfigAddr();
    ulHostOutTimeout   = pstFcDrvAssemPara->ucHostOutTimeout;


    if (SYSTEM_APP_MP == *pucSystemAppConfig)
    {
        /* HOST */
        if (VOS_OK != mdrv_udi_ioctl(g_ulAtUdiNdisHdl,
                                    NCM_IOCTL_SET_ACCUMULATION_TIME,
                                    (VOS_VOID*)&ulHostOutTimeout))
        {
            AT_ERR_LOG("AT_UsbEthHostAccumTuneCB: Set host out timeout failed.");

            return VOS_ERR;
        }

    }
    else if (SYSTEM_APP_WEBUI == *pucSystemAppConfig)
    {
        /* Modified by zwx247453 for pc3650, 2015-8-24, begin */
        /*lint -e747*/
        if (VOS_OK != USB_ETH_DrvSetHostAssembleParam((unsigned long)ulHostOutTimeout) )
        {
            AT_ERR_LOG("AT_UsbEthHostAccumTuneCB: Set Assemble para failed.");

            return VOS_ERR;
        }
        /*lint +e747*/
        /* Modified by zwx247453 for pc3650, 2015-8-24, end */
    }
    else if (SYSTEM_APP_ANDROID == *pucSystemAppConfig)
    {
        AT_NORM_LOG("AT_UsbEthHostAccumTuneCB: APP config is ANDROID, do nothing.");
    }
    else
    {
        AT_ERR_LOG("AT_UsbEthHostAccumTuneCB: Wrong APP config.");

        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
     : AT_UsbEthDeviceAccumTuneCB
   : FC()DEVICENCM/ECM
   : pstFcDrvAssemPara - NCM/ECM, :
                                 1. TX
                                 2. TX
                                 3. RX
                                 4. RX
   : 
     : VOS_OK            - 
             VOS_ERR           - 
   :
   :

       :
  1.       : 2012514
           : A00165503
       : 

*****************************************************************************/
VOS_UINT32 AT_UsbEthDeviceAccumTuneCB(
    FC_DRV_ASSEM_PARA_STRU             *pstFcDrvAssemPara
)
{
    VOS_UINT8                          *pucSystemAppConfig;
    VOS_UINT32                          ulEthTxMinNum;
    VOS_UINT32                          ulEthTxTimeout;
    VOS_UINT32                          ulEthRxMinNum;
    VOS_UINT32                          ulEthRxTimeout;

    /* : MP/WEBUI/ANDROID */
    pucSystemAppConfig = AT_GetSystemAppConfigAddr();
    ulEthTxMinNum      = pstFcDrvAssemPara->ucEthTxMinNum;
    ulEthTxTimeout     = pstFcDrvAssemPara->ucEthTxTimeout;
    ulEthRxMinNum      = pstFcDrvAssemPara->ucEthRxMinNum;
    ulEthRxTimeout     = pstFcDrvAssemPara->ucEthRxTimeout;

    if (SYSTEM_APP_MP == *pucSystemAppConfig)
    {
        if (VOS_OK != mdrv_udi_ioctl(g_ulAtUdiNdisHdl,
                                    NCM_IOCTL_SET_TX_MIN_NUM,
                                    (VOS_VOID*)&ulEthTxMinNum))
        {
            AT_ERR_LOG("AT_UsbEthDeviceAccumTuneCB: Set ETH tx min num failed.");

            return VOS_ERR;
        }

        if (VOS_OK != mdrv_udi_ioctl(g_ulAtUdiNdisHdl,
                                    NCM_IOCTL_SET_TX_TIMEOUT,
                                    (VOS_VOID*)&ulEthTxTimeout))
        {
            AT_ERR_LOG("AT_UsbEthDeviceAccumTuneCB: Set ETH tx timeout failed.");

            return VOS_ERR;
        }

        if (VOS_OK != mdrv_udi_ioctl(g_ulAtUdiNdisHdl,
                                    NCM_IOCTL_SET_RX_MIN_NUM,
                                    (VOS_VOID*)&ulEthRxMinNum))
        {
            AT_ERR_LOG("AT_UsbEthDeviceAccumTuneCB: Set ETH rx min num failed.");

            return VOS_ERR;
        }

        if (VOS_OK != mdrv_udi_ioctl(g_ulAtUdiNdisHdl,
                                    NCM_IOCTL_SET_RX_TIMEOUT,
                                    (VOS_VOID*)&ulEthRxTimeout))
        {
            AT_ERR_LOG("AT_UsbEthDeviceAccumTuneCB: Set ETH rx timeout failed.");

            return VOS_ERR;
        }
    }
    else if (SYSTEM_APP_WEBUI == *pucSystemAppConfig)
    {
        /* Modified by zwx247453 for pc3650, 2015-8-24, begin */
        /*lint -e747*/
        if (VOS_OK != USB_ETH_DrvSetDeviceAssembleParam((unsigned long)ulEthTxMinNum,
                                                        (unsigned long)ulEthTxTimeout,
                                                        (unsigned long)ulEthRxMinNum,
                                                        (unsigned long)ulEthRxTimeout))
        {
            AT_ERR_LOG("AT_UsbEthDeviceAccumTuneCB: Set Assemble para failed.");

            return VOS_ERR;
        }
        /*lint +e747*/
        /* Modified by zwx247453 for pc3650, 2015-8-24, end */
    }
    else if (SYSTEM_APP_ANDROID == *pucSystemAppConfig)
    {
        AT_NORM_LOG("AT_UsbEthDeviceAccumTuneCB: APP config is ANDROID, do nothing.");
    }
    else
    {
        AT_ERR_LOG("AT_UsbEthDeviceAccumTuneCB: Wrong APP config.");

        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
     : AT_NDIS_ParseUsrInfo
   : NIDS
   : ucIndex     - (ClientId)
   : pstUserInfo - 
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20130114
           : A00165503
       : 
*****************************************************************************/
VOS_VOID AT_NDIS_ParseUsrInfo(
    VOS_UINT8                           ucIndex,
    AT_PS_USER_INFO_STRU               *pstUsrInfo
)
{
    AT_CLIENT_TAB_INDEX_UINT8           enUsrIndex;

    if (VOS_TRUE == AT_CheckNdisUser(ucIndex))
    {
        enUsrIndex = ucIndex;
    }
    else
    {
        enUsrIndex = AT_CLIENT_TAB_NDIS_INDEX;
    }

    pstUsrInfo->enPortIndex = ucIndex;
    pstUsrInfo->enUserIndex = enUsrIndex;
    pstUsrInfo->ucUsrType   = (AT_USER_TYPE)gastAtClientTab[enUsrIndex].UserType;
    pstUsrInfo->ucUsrCid    = (VOS_UINT8)gastAtParaList[0].ulParaValue;

    return;
}

/*****************************************************************************
     : AT_NDIS_ConnStatusChgProc
   : NDIS
   : enStatus --- 
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 201595
           : A00165503
       : 
*****************************************************************************/
VOS_VOID AT_NDIS_ConnStatusChgProc(NCM_IOCTL_CONNECT_STUS_E enStatus)
{
    if (NCM_IOCTL_STUS_BREAK == enStatus)
    {
        /* PDPIDLEOK; DEACTINGOK */
        if (VOS_TRUE == AT_NdisCheckPdpIdleState())
        {
            return;
        }

        if ( (AT_PDP_STATE_ACTING == g_stAtNdisDhcpPara.enIpv4v6State)
          || (AT_PDP_STATE_ACTED  == g_stAtNdisDhcpPara.enIpv4v6State) )
        {
            if (VOS_OK == TAF_PS_CallEnd(WUEPS_PID_AT,
                                         AT_PS_BuildNdisExClientId(AT_NDIS_GET_USR_PORT_INDEX(), AT_NDIS_GET_CLIENT_ID()),
                                         0,
                                         g_stAtNdisDhcpPara.ucIpv4v6Cid) )
            {
                AT_NdisSetState(TAF_PDP_IPV4V6, AT_PDP_STATE_DEACTING);
            }
        }
        else
        {
            if ( (AT_PDP_STATE_ACTING == g_stAtNdisDhcpPara.enIpv4State)
              || (AT_PDP_STATE_ACTED  == g_stAtNdisDhcpPara.enIpv4State) )
            {
                if (VOS_OK == TAF_PS_CallEnd(WUEPS_PID_AT,
                                             AT_PS_BuildNdisExClientId(AT_NDIS_GET_USR_PORT_INDEX(), AT_NDIS_GET_CLIENT_ID()),
                                             0,
                                             g_stAtNdisDhcpPara.ucIpv4Cid))
                {
                    AT_NdisSetState(TAF_PDP_IPV4, AT_PDP_STATE_DEACTING);
                }
            }

            if ( (AT_PDP_STATE_ACTING == g_stAtNdisDhcpPara.enIpv6State)
              || (AT_PDP_STATE_ACTED  == g_stAtNdisDhcpPara.enIpv6State) )
            {
                if (VOS_OK == TAF_PS_CallEnd(WUEPS_PID_AT,
                                             AT_PS_BuildNdisExClientId(AT_NDIS_GET_USR_PORT_INDEX(), AT_NDIS_GET_CLIENT_ID()),
                                             0,
                                             g_stAtNdisDhcpPara.ucIpv6Cid))
                {
                    AT_NdisSetState(TAF_PDP_IPV6, AT_PDP_STATE_DEACTING);
                }
            }
        }
    }

    return;
}

/***************************************************************************
               APP
*****************************************************************************/

/*****************************************************************************
     : AT_CalcIpv6LanAddrFromIpv6Prefix
   : IPV6IPV6
   : pucPrefix
             ulPrefixByteLen
             pucIpv6LanAddr
             ulIpv6LanAddrLen
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 20111217
           : C00173809
       : /PS

  2.       : 2012630
           : A00165503
       : DTS2012062900707: IPv6, IPv6
*****************************************************************************/
VOS_UINT32 AT_CalcIpv6LanAddrFromIpv6Prefix(
    VOS_UINT8                          *pucPrefix,
    VOS_UINT32                          ulPrefixByteLen,
    VOS_UINT8                          *pucIpv6LanAddr,
    VOS_UINT32                          ulIpv6LanAddrLen
)
{
    VOS_UINT16                         *pausAddr;
    VOS_UINT8                           aucLanAddr[AT_MAC_LEN] = { 0x58, 0x2C, 0x80, 0x13, 0x92, 0x08 };

    if ( (ulIpv6LanAddrLen < TAF_IPV6_ADDR_LEN )
      || (ulPrefixByteLen > AT_IPV6_ADDR_PREFIX_BYTE_LEN) )
    {
        return VOS_ERR;
    }

    pausAddr = (VOS_UINT16 *)pucIpv6LanAddr;

    /* IPv6 */
    TAF_MEM_CPY_S(pucIpv6LanAddr, TAF_IPV6_ADDR_LEN, pucPrefix, ulPrefixByteLen);

    /*--------------------------------------------------------------
       MACID160xFFFEMAC
       MAC24 + 0xFFFE + MAC24
       U/L(/,MAC)
    --------------------------------------------------------------*/
    pausAddr[4] = ((VOS_UINT16 *)aucLanAddr)[0] ^ VOS_HTONS(0x0200);
    pausAddr[5] = VOS_HTONS(0x00ff) | ((VOS_UINT16 *)aucLanAddr)[1];
    pausAddr[6] = VOS_HTONS(0xfe00) | (((VOS_UINT16 *)aucLanAddr)[1] & VOS_HTONS(0x00ff));
    pausAddr[7] = ((VOS_UINT16 *)aucLanAddr)[2];

    return VOS_OK;
}

/*****************************************************************************
     : AT_AppRcvIpv6LanAddr
   : NASHOSTHOSTIPv6NAS-
             IPv6
   : aucLanAddr       - Ipv6
             ulLanAddrByteLen - , BYTE
             ulPrefixBitLen   - , BIT
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 2011725
           : f62575
       : 

  2.       : 2012630
           : A00165503
       : DTS2012062900707: IPv6, IPv6

  3.       : 2013114
           : A00165503
       : DTS2012042104301: PCUINDIS/APP
*****************************************************************************/
VOS_VOID AT_AppRcvIpv6LanAddr(
    VOS_UINT8                           aucLanAddr[],
    VOS_UINT32                          ulLanAddrByteLen,
    VOS_UINT32                          ulPrefixBitLen
)
{
    VOS_UINT16                          usLength;
    VOS_UINT8                           aucIpv6AddrStr[TAF_MAX_IPV6_ADDR_COLON_STR_LEN];

    /*  */
    AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                      aucLanAddr,
                                      TAF_IPV6_STR_RFC2373_TOKENS);

    /* LAN */
    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR*)pgucAtSndCodeAddr,
                                      (VOS_CHAR*)pgucAtSndCodeAddr,
                                      "%s^APLANADDR: \"%s\",%d%s",
                                      gaucAtCrLf,
                                      aucIpv6AddrStr,
                                      ulPrefixBitLen,
                                      gaucAtCrLf);
    At_SendResultData(AT_APP_GET_USR_PORT_INDEX(), pgucAtSndCodeAddr, usLength);

    return;
}

/*****************************************************************************
     : AT_AppRcvIpV6Prefix
   : NASHOSTHOSTGGSNRA
             IPV6NASIPv6
   : VOS_UINT8  aucPrefix   Ipv6
             VOS_UINT32 ulPrefixLen BIT
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 2011725
           : f62575
       : 

  2.       : 2012630
           : A00165503
       : DTS2012062900707: IPv6, IPv6

  3.       : 2013114
           : A00165503
       : DTS2012042104301: PCUINDIS/APP
*****************************************************************************/
VOS_VOID AT_AppRcvIpv6Prefix(
    VOS_UINT8                           aucPrefix[],
    VOS_UINT32                          ulPrefixBitLen
)
{
    VOS_UINT8                           aucPrefixStr[TAF_MAX_IPV6_ADDR_COLON_STR_LEN];
    VOS_UINT16                          usLength;
    VOS_UINT8                           ucTokensNum;

    /*  */
    ucTokensNum = TAF_IPV6_STR_RFC2373_TOKENS;
    AT_ConvertIpv6AddrToCompressedStr(aucPrefixStr, aucPrefix, ucTokensNum);

    /* ^APPREFIX: <PrefixAddr> */
    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR*)pgucAtSndCodeAddr,
                                      (VOS_CHAR*)pgucAtSndCodeAddr,
                                      "%s^APPREFIX: \"%s/%d\"%s",
                                      gaucAtCrLf,
                                      aucPrefixStr,
                                      ulPrefixBitLen,
                                      gaucAtCrLf);
    At_SendResultData(AT_APP_GET_USR_PORT_INDEX(), pgucAtSndCodeAddr, usLength);
    return;
}

/*****************************************************************************
     : AT_AppRcvPrefixIpV6PreferredLifetime
   : :
   : ulPrefixPreferredLifetime - 
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 2011726
           : f62575
       : 

  2.       : 2012511
           : l60609
       : DTS2012051002464lifetime%u

  3.       : 2012630
           : A00165503
       : DTS2012062900707: IPv6, IPv6
  4.       : 2013114
           : A00165503
       : DTS2012042104301: PCUINDIS/APP
*****************************************************************************/
VOS_VOID AT_AppRcvPrefixIpv6PreferredLifetime(
    VOS_UINT32                          ulPrefixPreferredLifetime
)
{
    VOS_UINT16                          usLength;

    /* ^APPREFERREDLIFETIME: <PreferredLifetime> */
    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR*)pgucAtSndCodeAddr,
                                      (VOS_CHAR*)pgucAtSndCodeAddr,
                                      "%s^APPREFERREDLIFETIME: %u%s",
                                      gaucAtCrLf,
                                      ulPrefixPreferredLifetime,
                                      gaucAtCrLf);
    At_SendResultData(AT_APP_GET_USR_PORT_INDEX(), pgucAtSndCodeAddr, usLength);

    return;
}

/*****************************************************************************
     : AT_RcvPrefixIpV6ValidLifetime
   : :
   : ulValidLifetime - 
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 2011726
           : f62575
       : 

  2.       : 2012511
           : l60609
       : DTS2012051002464lifetime%u

  3.       : 2012630
           : A00165503
       : DTS2012062900707: IPv6, IPv6

  4.       : 2013114
           : A00165503
       : DTS2012042104301: PCUINDIS/APP
*****************************************************************************/
VOS_VOID AT_AppRcvPrefixIpv6ValidLifetime(
    VOS_UINT32                          ulValidLifetime
)
{
    VOS_UINT16                          usLength;

    /* ^APVALIDLIFETIME: <ValidLifetime> */
    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR*)pgucAtSndCodeAddr,
                                      (VOS_CHAR*)pgucAtSndCodeAddr,
                                      "%s^APVALIDLIFETIME: %u%s",
                                      gaucAtCrLf,
                                      ulValidLifetime,
                                      gaucAtCrLf);
    At_SendResultData(AT_APP_GET_USR_PORT_INDEX(), pgucAtSndCodeAddr, usLength);

    return;
}

/*****************************************************************************
     : AT_RcvIpV6LinkMtu
   : HOSTMTU: MTU
             APPRAHOST
             NASMTU
   : ulMTU - MTU Size
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 2011725
           : f62575
       : 

  2.       : 2012630
           : A00165503
       : DTS2012062900707: IPv6, IPv6

  3.       : 2013114
           : A00165503
       : DTS2012042104301: PCUINDIS/APP
*****************************************************************************/
VOS_VOID AT_AppRcvIpv6LinkMtu(
    VOS_UINT32                          ulMtu
)
{
    VOS_UINT16                          usLength;

    /* ^IPV6MTU: <MTU> */
    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR*)pgucAtSndCodeAddr,
                                      (VOS_CHAR*)pgucAtSndCodeAddr,
                                      "%s^APIPV6MTU: %d%s",
                                      gaucAtCrLf,
                                      ulMtu,
                                      gaucAtCrLf);
    At_SendResultData(AT_APP_GET_USR_PORT_INDEX(), pgucAtSndCodeAddr, usLength);
    return;
}

/*****************************************************************************
     : AT_RcvEnableIpV6Prefix
   : IPV6
   : VOS_VOID
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 2011726
           : f62575
       : 

  2.       : 2013114
           : A00165503
       : DTS2012042104301: PCUINDIS/APP

*****************************************************************************/
VOS_VOID AT_AppRcvEnableIpv6Prefix(VOS_VOID)
{
    VOS_UINT16                          usLength;
    VOS_UINT8                           ucStatus;

    ucStatus                            = 1;

    /* ^APIPV6ENABLE: <status> */
    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR*)pgucAtSndCodeAddr,
                                      (VOS_CHAR*)pgucAtSndCodeAddr,
                                      "%s^APIPV6ENABLE: %d%s",
                                      gaucAtCrLf,
                                      ucStatus,
                                      gaucAtCrLf);
    At_SendResultData(AT_APP_GET_USR_PORT_INDEX(), pgucAtSndCodeAddr, usLength);

    return;
}

/*****************************************************************************
     : AT_AppProcIpv6RaInfo
   : Router Advertisement IP, 
   : pstRaInfoNotifyInd         - RA
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 2012630
           : A00165503
       : 

*****************************************************************************/
VOS_VOID AT_AppProcIpv6RaInfo(TAF_PS_IPV6_INFO_IND_STRU *pstRaInfoNotifyInd)
{
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity;
    AT_IPV6_RA_INFO_STRU               *pstAppRaInfoAddr;
    VOS_UINT8                           aucIpv6LanAddr[TAF_IPV6_ADDR_LEN] = {0};

    pstAppRaInfoAddr = AT_APP_GetRaInfoAddr();
    pstAppPdpEntity  = AT_APP_GetPdpEntInfoAddr();

    if (0 == pstRaInfoNotifyInd->stIpv6RaInfo.ulPrefixNum)
    {
        AT_NORM_LOG("AT_AppProcIpv6RaInfo: No IPv6 prefix address in RA.");
        return;
    }

    /* IPv6, ^DCONN */
    if (VOS_FALSE == pstAppRaInfoAddr->bitOpPrefixAddr)
    {
        /* APPIPv6 */
        AT_AppSndCallConnectedResult(pstRaInfoNotifyInd->ucCid, TAF_PDP_IPV6);
    }

    /* IPv6 */
    pstAppRaInfoAddr->bitOpPrefixAddr        = VOS_TRUE;
    pstAppRaInfoAddr->ulPrefixBitLen         = pstRaInfoNotifyInd->stIpv6RaInfo.astPrefixList[0].ulBitPrefixLen;
    TAF_MEM_CPY_S(pstAppRaInfoAddr->aucPrefixAddr,
               sizeof(pstAppRaInfoAddr->aucPrefixAddr),
               pstRaInfoNotifyInd->stIpv6RaInfo.astPrefixList[0].aucPrefix,
               TAF_IPV6_ADDR_LEN);

    /* Preferred Lifetime */
    pstAppRaInfoAddr->bitOpPreferredLifetime = VOS_TRUE;
    pstAppRaInfoAddr->ulPreferredLifetime    = pstRaInfoNotifyInd->stIpv6RaInfo.astPrefixList[0].ulPreferredLifeTime;

    /* Valid Lifetime */
    pstAppRaInfoAddr->bitOpValidLifetime     = VOS_TRUE;
    pstAppRaInfoAddr->ulValidLifetime        = pstRaInfoNotifyInd->stIpv6RaInfo.astPrefixList[0].ulValidLifeTime;

    /* IPv6 MTU */
    if (VOS_TRUE == pstRaInfoNotifyInd->stIpv6RaInfo.bitOpMtu)
    {
        pstAppRaInfoAddr->bitOpMtuSize       = VOS_TRUE;
        pstAppRaInfoAddr->ulMtuSize          = pstRaInfoNotifyInd->stIpv6RaInfo.ulMtu;
    }

    /* IPv6 */
    AT_CalcIpv6LanAddrFromIpv6Prefix(pstRaInfoNotifyInd->stIpv6RaInfo.astPrefixList[0].aucPrefix,
                                     pstRaInfoNotifyInd->stIpv6RaInfo.astPrefixList[0].ulBitPrefixLen/8,
                                     aucIpv6LanAddr,
                                     TAF_IPV6_ADDR_LEN);

    /* IPv6 */
    pstAppRaInfoAddr->bitOpLanAddr           = VOS_TRUE;
    TAF_MEM_CPY_S(pstAppRaInfoAddr->aucLanAddr, sizeof(pstAppRaInfoAddr->aucLanAddr), aucIpv6LanAddr, TAF_IPV6_ADDR_LEN);

    /* DHCPV6IPv6 */
    TAF_MEM_CPY_S(pstAppPdpEntity->stIpv6Dhcp.aucIpv6Addr, sizeof(pstAppPdpEntity->stIpv6Dhcp.aucIpv6Addr), aucIpv6LanAddr, TAF_IPV6_ADDR_LEN);

    /* IPV6 */
    AT_AppRcvIpv6Prefix(pstAppRaInfoAddr->aucPrefixAddr, pstAppRaInfoAddr->ulPrefixBitLen);

    /*  */
    AT_AppRcvPrefixIpv6PreferredLifetime(pstAppRaInfoAddr->ulPreferredLifetime);

    /*  */
    AT_AppRcvPrefixIpv6ValidLifetime(pstAppRaInfoAddr->ulValidLifetime);

    /* IPV6 */
    AT_AppRcvIpv6LanAddr(pstAppRaInfoAddr->aucLanAddr, TAF_IPV6_ADDR_LEN, pstAppRaInfoAddr->ulPrefixBitLen);

    /* APPIPV6 */
    AT_AppRcvEnableIpv6Prefix();

    return;
}

/*****************************************************************************
     : AT_AppCtrlConnIpv6IndProc
   : IPv6
   : pstAppPdpEntity - PDP
             pstEvent        - 
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 2011720
           : A00165503
       : 

*****************************************************************************/
VOS_VOID AT_AppCtrlConnIpv6IndProc(
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
    pstAppPdpEntity->stIpv6Dhcp.ucRabId  = pstEvent->ucRabId;

    /* IPv6IP */
    if (TAF_PDP_IPV6 == (pstEvent->stPdpAddr.enPdpType & TAF_PDP_IPV6))
    {
        TAF_MEM_CPY_S(pstAppPdpEntity->stIpv6Dhcp.aucIpv6Addr,
                   sizeof(pstAppPdpEntity->stIpv6Dhcp.aucIpv6Addr),
                   pstEvent->stPdpAddr.aucIpv6Addr,
                   TAF_IPV6_ADDR_LEN);
    }

    /* IPV6DNS */
    AT_SaveIPv6Dns(pstEvent, pstAppPdpEntity);

    /* IPV6PCSCF */
    AT_SaveIPv6Pcscf(pstEvent, pstAppPdpEntity);

    return;
}

/*****************************************************************************
     : AT_AppDhcpv6Reset
   : IPv6
   : VOS_VOID
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 2011720
           : A00165503
       : 

*****************************************************************************/
VOS_VOID AT_AppDhcpv6Reset(VOS_VOID)
{
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity;
    AT_IPV6_RA_INFO_STRU               *pucAppRaInfoAddr;

    pstAppPdpEntity                     = AT_APP_GetPdpEntInfoAddr();
    pucAppRaInfoAddr                    = AT_APP_GetRaInfoAddr();

    TAF_MEM_SET_S(&pstAppPdpEntity->stIpv6Dhcp,
               sizeof(pstAppPdpEntity->stIpv6Dhcp),
               0x00,
               sizeof(AT_IPV6_DHCP_PARAM_STRU));

    TAF_MEM_SET_S(pucAppRaInfoAddr,
               sizeof(AT_IPV6_RA_INFO_STRU),
               0x00,
               sizeof(AT_IPV6_RA_INFO_STRU));

    return;
}

/*****************************************************************************
     : AT_AppDhcpReset
   : APPDHCP
   : VOS_VOID
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 2011720
           : A00165503
       : 

*****************************************************************************/
VOS_VOID AT_AppDhcpReset(VOS_VOID)
{
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity;

    pstAppPdpEntity                     = AT_APP_GetPdpEntInfoAddr();

    TAF_MEM_SET_S(&pstAppPdpEntity->stIpv4Dhcp,
               sizeof(pstAppPdpEntity->stIpv4Dhcp),
               0x00,
               sizeof(AT_IPV4_DHCP_PARAM_STRU));

    return;
}

/*****************************************************************************
     : AT_AppPdpAddrProc
   : IPv4
   : pstAppPdpEntity - PDP
             pstDhcpConfig   - DCHP
             pstEvent        - 
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 2011722
           : A00165503
       : 
  2.       : 20110818
           : A00165503
       : : DTS2011081400480, ^DNSP^DNSSHiLink
  3.       : 20120102
           : C00173809
       : PSIPV4PCSCF
  4.       : 20120807
           : f00179208
       : :DTS2015031000157, p-cscf
*****************************************************************************/
VOS_VOID AT_AppPdpAddrProc(
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity,
    AT_DHCP_CONFIG_STRU                *pstDhcpConfig,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
    AT_DIAL_PARAM_STRU                 *pstAppDialPara;
    VOS_UINT32                          ulIpAddr;
    VOS_UINT8                           ucIndex;

    pstAppDialPara                      = AT_APP_GetDailParaAddr();
    ulIpAddr                            = 0;

    pstAppPdpEntity->stIpv4Dhcp.ucRabId                 = pstEvent->ucRabId;
    pstAppPdpEntity->stIpv4Dhcp.ulIpv4Addr              = pstDhcpConfig->ulIPAddr;
    pstAppPdpEntity->stIpv4Dhcp.ulIpv4GateWay           = pstDhcpConfig->ulGateWay;
    pstAppPdpEntity->stIpv4Dhcp.ulIpv4NetMask           = pstDhcpConfig->ulSubNetMask;

    /* DNSDNSDNS */
    if (VOS_TRUE == pstAppDialPara->ulPrimIPv4DNSValidFlag)
    {
        if (VOS_ERR == AT_LenStr2IpAddr(pstAppDialPara->aucPrimIPv4DNSAddr,
                                        (VOS_UINT8*)&ulIpAddr))
        {
            ulIpAddr = 0;
        }

        pstAppPdpEntity->stIpv4Dhcp.bitOpIpv4PriDns     = VOS_TRUE;
        pstAppPdpEntity->stIpv4Dhcp.ulIpv4PrimDNS       = VOS_NTOHL(ulIpAddr);
    }
    else
    {
        if (0 != pstDhcpConfig->ulPrimDNS)
        {
            pstAppPdpEntity->stIpv4Dhcp.bitOpIpv4PriDns = VOS_TRUE;
            pstAppPdpEntity->stIpv4Dhcp.ulIpv4PrimDNS   = pstDhcpConfig->ulPrimDNS;
        }
        else
        {
            pstAppPdpEntity->stIpv4Dhcp.bitOpIpv4PriDns = VOS_FALSE;
        }
    }

    /* DNSDNSDNS */
    if (VOS_TRUE == pstAppDialPara->ulSndIPv4DNSValidFlag)
    {
        if (VOS_ERR == AT_LenStr2IpAddr(pstAppDialPara->aucSndIPv4DNSAddr,
                                        (VOS_UINT8*)&ulIpAddr))
        {
            ulIpAddr = 0;
        }

        pstAppPdpEntity->stIpv4Dhcp.bitOpIpv4SecDns     = VOS_TRUE;
        pstAppPdpEntity->stIpv4Dhcp.ulIpv4SecDNS        = VOS_NTOHL(ulIpAddr);
    }
    else
    {
        if (0 != pstDhcpConfig->ulSndDNS)
        {
            pstAppPdpEntity->stIpv4Dhcp.bitOpIpv4SecDns = VOS_TRUE;
            pstAppPdpEntity->stIpv4Dhcp.ulIpv4SecDNS    = pstDhcpConfig->ulSndDNS;
        }
        else
        {
            pstAppPdpEntity->stIpv4Dhcp.bitOpIpv4SecDns = VOS_FALSE;
        }
    }

    pstAppPdpEntity->stIpv4Dhcp.bitOpIpv4PriWINNS       = VOS_FALSE;
    pstAppPdpEntity->stIpv4Dhcp.bitOpIpv4SecWINNS       = VOS_FALSE;

    /* PCSCF */
    pstAppPdpEntity->stIpv4Dhcp.stIpv4PcscfList.ucIpv4PcscfAddrNum = AT_MIN(TAF_PCSCF_ADDR_MAX_NUM,
                                                                            pstEvent->stIpv4PcscfList.ucIpv4PcscfAddrNum);

    for (ucIndex = 0; ucIndex < pstAppPdpEntity->stIpv4Dhcp.stIpv4PcscfList.ucIpv4PcscfAddrNum; ucIndex++)
    {
        pstAppPdpEntity->stIpv4Dhcp.stIpv4PcscfList.aulIpv4PcscfAddrList[ucIndex] = AT_GetLanAddr32(pstEvent->stIpv4PcscfList.astIpv4PcscfAddrList[ucIndex].aucPcscfAddr);
    }


    return;
}


/*****************************************************************************
     : AT_AppCheckPdpIdleState
   : IDLEDEACTIVATINGPDP
   : VOS_VOID
   : 
     : VOS_TRUE  - PDP
             VOS_FALSE - PDP
   :
   :

       :
  1.       : 2011723
           : A00165503
       : 

*****************************************************************************/
VOS_UINT32 AT_AppCheckPdpIdleState(VOS_VOID)
{
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity;

    pstAppPdpEntity                     = AT_APP_GetPdpEntInfoAddr();

    /* PDPIDLE, DEACTIVATINGTRUE */
    if ( (AT_PDP_STATE_DEACTING == pstAppPdpEntity->enIpv4State)
      || (AT_PDP_STATE_DEACTING == pstAppPdpEntity->enIpv6State)
      || (AT_PDP_STATE_DEACTING == pstAppPdpEntity->enIpv4v6State)
      || ( (AT_PDP_STATE_IDLE == pstAppPdpEntity->enIpv4State)
        && (AT_PDP_STATE_IDLE == pstAppPdpEntity->enIpv6State)
        && (AT_PDP_STATE_IDLE == pstAppPdpEntity->enIpv4v6State) ) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}
/*****************************************************************************
     : AT_AppCheckIpv4PdpState
   : IPv4PDP
   : enPdpState - PDP
   : 
     : VOS_TRUE   - PDP
             VOS_FALSE  - PDP
   :
   :

       :
  1.       : 2011721
           : A00165503
       : 

*****************************************************************************/
VOS_UINT32 AT_AppCheckIpv4PdpState(
    AT_PDP_STATE_ENUM_U8                enPdpState
)
{
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity;

    pstAppPdpEntity                     = AT_APP_GetPdpEntInfoAddr();

    if ( (enPdpState == pstAppPdpEntity->enIpv4State)
      || (enPdpState == pstAppPdpEntity->enIpv4v6State) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
     : AT_AppCheckIpv6PdpState
   : IPv6PDP
   : enPdpState - PDP
   : 
     : VOS_TRUE   - PDP
             VOS_FALSE  - PDP
   :
   :

       :
  1.       : 2011721
           : A00165503
       : 

*****************************************************************************/
VOS_UINT32 AT_AppCheckIpv6PdpState(
    AT_PDP_STATE_ENUM_U8                enPdpState
)
{
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity;

    pstAppPdpEntity                     = AT_APP_GetPdpEntInfoAddr();

    if ( (enPdpState == pstAppPdpEntity->enIpv6State)
      || (enPdpState == pstAppPdpEntity->enIpv4v6State) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
     : AT_AppGetPdpStateByCid
   : CIDPDP
   : ucCid
   : 
     : AT_PDP_STATE_ENUM_U8
   :
   :

       :
  1.       : 2011725
           : A00165503
       : 

*****************************************************************************/
AT_PDP_STATE_ENUM_U8 AT_AppGetPdpStateByCid(
    VOS_UINT8                           ucCid
)
{
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity;

    pstAppPdpEntity                     = AT_APP_GetPdpEntInfoAddr();

    if (ucCid == pstAppPdpEntity->ucIpv4Cid)
    {
        return pstAppPdpEntity->enIpv4State;
    }
    else if (ucCid == pstAppPdpEntity->ucIpv6Cid)
    {
        return pstAppPdpEntity->enIpv6State;
    }
    else if (ucCid == pstAppPdpEntity->ucIpv4v6Cid)
    {
        return pstAppPdpEntity->enIpv4v6State;
    }
    else
    {
        return AT_PDP_STATE_IDLE;
    }
}

/*****************************************************************************
     : AT_AppGetPdpState
   : APPPDP/
   : ucPdpType - PDP
   : 
     : AT_PDP_STATE_ENUM_U8
   :
   :

       :
  1.       : 2011720
           : A00165503
       : 

*****************************************************************************/
AT_PDP_STATE_ENUM_U8 AT_AppGetPdpState(
    VOS_UINT8                           ucPdpType
)
{
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity;
    AT_PDP_STATE_ENUM_U8                enPdpState;

    pstAppPdpEntity                     = AT_APP_GetPdpEntInfoAddr();

    switch (ucPdpType)
    {
        case TAF_PDP_IPV4:
            enPdpState = pstAppPdpEntity->enIpv4State;
            break;

        case TAF_PDP_IPV6:
            enPdpState = pstAppPdpEntity->enIpv6State;
            break;

        case TAF_PDP_IPV4V6:
            enPdpState = pstAppPdpEntity->enIpv4v6State;
            break;

        default:
            AT_ERR_LOG("AT_AppGetPdpState:ERROR: PDP type is invalid!");
            enPdpState = AT_PDP_STATE_IDLE;
            break;
    }

    return enPdpState;
}

/*****************************************************************************
     : AT_AppSetPdpState
   : APPPDP
   : ucPdpType  - PDP
             enPdpState - PDP
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 2011720
           : A00165503
       : 

*****************************************************************************/
VOS_VOID AT_AppSetPdpState(
    VOS_UINT8                           ucPdpType,
    AT_PDP_STATE_ENUM_U8                enPdpState
)
{
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity;

    pstAppPdpEntity                     = AT_APP_GetPdpEntInfoAddr();

    switch (ucPdpType)
    {
        case TAF_PDP_IPV4:
            pstAppPdpEntity->enIpv4State    = enPdpState;
            break;

        case TAF_PDP_IPV6:
            pstAppPdpEntity->enIpv6State    = enPdpState;
            break;

        case TAF_PDP_IPV4V6:
            pstAppPdpEntity->enIpv4v6State  = enPdpState;
            break;

        default:
            AT_ERR_LOG("AT_AppSetPdpState:ERROR: PDP type is invalid!");
            break;
    }

    return;
}

/*****************************************************************************
     : AT_AppSndCallConnectedResult
   : ^DCONN, APP
   : ucCid                      - CID
             enPdpType                  - (IPv4/IPv6)
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 2012630
           : A00165503
       : 

  2.       : 2013114
           : A00165503
       : DTS2012042104301: PCUINDIS/APP
*****************************************************************************/
VOS_VOID AT_AppSndCallConnectedResult(
    VOS_UINT8                           ucCid,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
)
{
    VOS_UINT16                          usLength = 0;

    switch (enPdpType)
    {
        case TAF_PDP_IPV4:
            usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                              (VOS_CHAR *)pgucAtSndCodeAddr,
                                              (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                              "%s^DCONN:%d,\"IPV4\"%s",
                                              gaucAtCrLf,
                                              ucCid,
                                              gaucAtCrLf);
            break;

        case TAF_PDP_IPV6:
            usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                              (VOS_CHAR *)pgucAtSndCodeAddr,
                                              (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                              "%s^DCONN:%d,\"IPV6\"%s",
                                              gaucAtCrLf,
                                              ucCid,
                                              gaucAtCrLf);
            break;

        default:
            AT_ERR_LOG("AT_AppSndConnectResult: PDP type is invalid in ^DCONN.");
            return;
    }

    At_SendResultData(AT_APP_GET_USR_PORT_INDEX(), pgucAtSndCodeAddr, usLength);

    return;
}

/*****************************************************************************
     : AT_AppSndCallEndedResult
   : ^DCONN, APP
   : ucCid     - CID
             enCause   - 
             enPdpType - (IPv4/IPv6)
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 2012630
           : A00165503
       : 

  2.       : 2012822
           : A00165503
       : PS

  3.       : 2013114
           : A00165503
       : DTS2012042104301: PCUINDIS/APP
*****************************************************************************/
VOS_VOID AT_AppSndCallEndedResult(
    VOS_UINT8                           ucCid,
    TAF_PS_CAUSE_ENUM_UINT32            enCause,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
)
{
    VOS_UINT16                          usLength = 0;

    switch (enPdpType)
    {
        case TAF_PDP_IPV4:

            usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                              (VOS_CHAR *)pgucAtSndCodeAddr,
                                              (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                              "%s^DEND:%d,%d,\"IPV4\"%s",
                                              gaucAtCrLf,
                                              ucCid,
                                              enCause,
                                              gaucAtCrLf);

            break;

        case TAF_PDP_IPV6:

            usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                              (VOS_CHAR *)pgucAtSndCodeAddr,
                                              (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                              "%s^DEND:%d,%d,\"IPV6\"%s",
                                              gaucAtCrLf,
                                              ucCid,
                                              enCause,
                                              gaucAtCrLf);

            break;

        default:
            AT_ERR_LOG("AT_AppSndCallEndedResult: PDP type is invalid in ^DEND.");
            return;
    }

    At_SendResultData(AT_APP_GET_USR_PORT_INDEX(), pgucAtSndCodeAddr, usLength);

    return;
}

/*****************************************************************************
     : AT_SendRnicIpv4ActInd
   : APPIPV4
   : VOS_UINT8 ucRmNetId
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 20111018
           : S62952
       : 
  2.       : 20111018
           : f00179208
       : PS 
  3.       : 20121218
           : l60609
       : DSDA Phase II

*****************************************************************************/
VOS_UINT32 AT_SendRnicIpv4ActInd(VOS_UINT8 ucRmNetId)
{
    AT_RNIC_IPV4_PDP_ACT_IND_STRU      *pstMsg;

    /* AT_RNIC_IPV4_PDP_ACT_IND_STRU */
    pstMsg = (AT_RNIC_IPV4_PDP_ACT_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                            WUEPS_PID_AT,
                            sizeof(AT_RNIC_IPV4_PDP_ACT_IND_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        AT_WARN_LOG("AT_NotifyRnicIpv4ActInd: alloc msg fail!");
        return VOS_ERR;
    }

    /*  */
    TAF_MEM_SET_S((VOS_CHAR*)pstMsg + VOS_MSG_HEAD_LENGTH,
               (VOS_SIZE_T)(sizeof(AT_RNIC_IPV4_PDP_ACT_IND_STRU) - VOS_MSG_HEAD_LENGTH),
               0x00,
               (VOS_SIZE_T)(sizeof(AT_RNIC_IPV4_PDP_ACT_IND_STRU) - VOS_MSG_HEAD_LENGTH));

    /*  */
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = ACPU_PID_RNIC;
    pstMsg->enMsgId         = ID_AT_RNIC_IPV4_PDP_ACT_IND;

    /*  */
    pstMsg->ucRabId         = g_stAtAppPdpEntity.stIpv4Dhcp.ucRabId;
    /* Added by l60609 for DSDA Phase II, 2012-12-18, Begin */
    pstMsg->ucRmNetId       = ucRmNetId;
    /* Added by l60609 for DSDA Phase II, 2012-12-18, End */
    pstMsg->ulIpv4Addr      = g_stAtAppPdpEntity.stIpv4Dhcp.ulIpv4Addr;
    pstMsg->ulNetMask       = g_stAtAppPdpEntity.stIpv4Dhcp.ulIpv4NetMask;
    pstMsg->ulGateWay       = g_stAtAppPdpEntity.stIpv4Dhcp.ulIpv4GateWay;
    pstMsg->OP_PriDns       = g_stAtAppPdpEntity.stIpv4Dhcp.bitOpIpv4PriDns;
    pstMsg->OP_SecDns       = g_stAtAppPdpEntity.stIpv4Dhcp.bitOpIpv4SecDns;
    pstMsg->OP_PriWINNS     = g_stAtAppPdpEntity.stIpv4Dhcp.bitOpIpv4PriWINNS;
    pstMsg->OP_SecWINNS     = g_stAtAppPdpEntity.stIpv4Dhcp.bitOpIpv4SecWINNS;
    pstMsg->ulPrimDNS       = g_stAtAppPdpEntity.stIpv4Dhcp.ulIpv4PrimDNS;
    pstMsg->ulSecDNS        = g_stAtAppPdpEntity.stIpv4Dhcp.ulIpv4SecDNS;
    pstMsg->ulPrimWINNS     = g_stAtAppPdpEntity.stIpv4Dhcp.ulIpv4PrimWINNS;
    pstMsg->ulSecWINNS      = g_stAtAppPdpEntity.stIpv4Dhcp.ulIpv4SecWINNS;

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_AT, pstMsg))
    {
        AT_WARN_LOG("AT_NotifyRnicIpv4ActInd: Send msg fail!");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
    : AT_SendRnicIpv6ActInd
  : APPIPV6
  : VOS_UINT8 ucRmNetId
  : 
    : 
            
  :
  :

      :
 1.       : 20111018
          : S62952
      : 
 2.       : 20111018
          : f00179208
      : PS 
 3.       : 20121227
          : l00227485
      : DSDA PhaseII
*****************************************************************************/
VOS_UINT32 AT_SendRnicIpv6ActInd(VOS_UINT8 ucRmNetId)
{
    AT_RNIC_IPV6_PDP_ACT_IND_STRU      *pstMsg;

    /* AT_NDIS_IPV6_PDP_ACT_IND_STRU */
    pstMsg = (AT_RNIC_IPV6_PDP_ACT_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                            WUEPS_PID_AT,
                            sizeof(AT_RNIC_IPV6_PDP_ACT_IND_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        AT_WARN_LOG("AT_NotifyRnicIpv6ActInd: alloc msg fail!");
        return VOS_ERR;
    }

    /*  */
    TAF_MEM_SET_S((VOS_CHAR*)pstMsg + VOS_MSG_HEAD_LENGTH,
               (VOS_SIZE_T)(sizeof(AT_RNIC_IPV6_PDP_ACT_IND_STRU) - VOS_MSG_HEAD_LENGTH),
               0x00,
               (VOS_SIZE_T)(sizeof(AT_RNIC_IPV6_PDP_ACT_IND_STRU) - VOS_MSG_HEAD_LENGTH));


    /*  */
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = ACPU_PID_RNIC;
    pstMsg->enMsgId         = ID_AT_RNIC_IPV6_PDP_ACT_IND;

    /*  */
    pstMsg->ucRabId         = g_stAtAppPdpEntity.stIpv6Dhcp.ucRabId;
    pstMsg->ucRmNetId       = ucRmNetId;
    pstMsg->OP_PriDns       = g_stAtAppPdpEntity.stIpv6Dhcp.bitOpIpv6PriDns;
    pstMsg->OP_SecDns       = g_stAtAppPdpEntity.stIpv6Dhcp.bitOpIpv6SecDns;

    TAF_MEM_CPY_S(pstMsg->aucIpv6Addr,
               sizeof(pstMsg->aucIpv6Addr),
               g_stAtAppPdpEntity.stIpv6Dhcp.aucIpv6Addr,
               TAF_IPV6_ADDR_LEN);

    TAF_MEM_CPY_S(pstMsg->aucPrimDNS,
               sizeof(pstMsg->aucPrimDNS),
               g_stAtAppPdpEntity.stIpv6Dhcp.aucIpv6PrimDNS,
               AT_MAX_IPV6_DNS_LEN);

    TAF_MEM_CPY_S(pstMsg->aucSecDNS,
               sizeof(pstMsg->aucSecDNS),
               g_stAtAppPdpEntity.stIpv6Dhcp.aucIpv6SecDNS,
               AT_MAX_IPV6_DNS_LEN);

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_AT, pstMsg))
    {
        AT_WARN_LOG("AT_NotifyRnicIpv6ActInd: Send msg fail!");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
    : AT_SendRnicIpv4v6ActInd
  : APPIPV4V6
  : VOS_UINT8 ucRmNetId
  : 
    : VOS_UINT32
  :
  :

      :
 1.       : 20111018
          : S62952
      : 
 2.       : 20111225
          : c00173809
      : PS IPV6
 3.       : 20121227
          : l00227485
      : DSDA PhaseII
*****************************************************************************/
VOS_UINT32 AT_SendRnicIpv4v6ActInd(VOS_UINT8 ucRmNetId)
{
    AT_RNIC_IPV4V6_PDP_ACT_IND_STRU      *pstMsg;

    /* AT_NDIS_IPV6_PDP_ACT_IND_STRU */
    pstMsg = (AT_RNIC_IPV4V6_PDP_ACT_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                            WUEPS_PID_AT,
                            sizeof(AT_RNIC_IPV4V6_PDP_ACT_IND_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        AT_WARN_LOG("AT_NotifyRnicIpv6ActInd: alloc msg fail!");
        return VOS_ERR;
    }

    /*  */
    TAF_MEM_SET_S((VOS_CHAR*)pstMsg + VOS_MSG_HEAD_LENGTH,
               (VOS_SIZE_T)(sizeof(AT_RNIC_IPV4V6_PDP_ACT_IND_STRU) - VOS_MSG_HEAD_LENGTH),
               0x00,
               (VOS_SIZE_T)(sizeof(AT_RNIC_IPV4V6_PDP_ACT_IND_STRU) - VOS_MSG_HEAD_LENGTH));


    /*  */
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = ACPU_PID_RNIC;
    pstMsg->enMsgId         = ID_AT_RNIC_IPV4V6_PDP_ACT_IND;

    /*  */
    pstMsg->ucRabId             = g_stAtAppPdpEntity.stIpv4Dhcp.ucRabId;
    pstMsg->ucRmNetId           = ucRmNetId;
    pstMsg->ulIpv4Addr          = g_stAtAppPdpEntity.stIpv4Dhcp.ulIpv4Addr;
    pstMsg->ulIPv4NetMask       = g_stAtAppPdpEntity.stIpv4Dhcp.ulIpv4NetMask;
    pstMsg->ulIPv4GateWay       = g_stAtAppPdpEntity.stIpv4Dhcp.ulIpv4GateWay;
    pstMsg->OP_IPv4PriDns       = g_stAtAppPdpEntity.stIpv4Dhcp.bitOpIpv4PriDns;
    pstMsg->OP_IPv4SecDns       = g_stAtAppPdpEntity.stIpv4Dhcp.bitOpIpv4SecDns;
    pstMsg->OP_IPv4PriWINNS     = g_stAtAppPdpEntity.stIpv4Dhcp.bitOpIpv4PriWINNS;
    pstMsg->OP_IPv4SecWINNS     = g_stAtAppPdpEntity.stIpv4Dhcp.bitOpIpv4SecWINNS;
    pstMsg->ulIPv4PrimDNS       = g_stAtAppPdpEntity.stIpv4Dhcp.ulIpv4PrimDNS;
    pstMsg->ulIPv4SecDNS        = g_stAtAppPdpEntity.stIpv4Dhcp.ulIpv4SecDNS;
    pstMsg->ulIPv4PrimWINNS     = g_stAtAppPdpEntity.stIpv4Dhcp.ulIpv4PrimWINNS;
    pstMsg->ulIPv4SecWINNS      = g_stAtAppPdpEntity.stIpv4Dhcp.ulIpv4SecWINNS;

    pstMsg->OP_IPv6PriDns       = g_stAtAppPdpEntity.stIpv6Dhcp.bitOpIpv6PriDns;
    pstMsg->OP_IPv6SecDns       = g_stAtAppPdpEntity.stIpv6Dhcp.bitOpIpv6SecDns;

    TAF_MEM_CPY_S(pstMsg->aucIpv6Addr,
               sizeof(pstMsg->aucIpv6Addr),
               g_stAtAppPdpEntity.stIpv6Dhcp.aucIpv6Addr,
               TAF_IPV6_ADDR_LEN);

    TAF_MEM_CPY_S(pstMsg->aucIpv6PrimDNS,
               sizeof(pstMsg->aucIpv6PrimDNS),
               g_stAtAppPdpEntity.stIpv6Dhcp.aucIpv6PrimDNS,
               AT_MAX_IPV6_DNS_LEN);

    TAF_MEM_CPY_S(pstMsg->aucIpv6SecDNS,
               sizeof(pstMsg->aucIpv6SecDNS),
               g_stAtAppPdpEntity.stIpv6Dhcp.aucIpv6SecDNS,
               AT_MAX_IPV6_DNS_LEN);

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_AT, pstMsg))
    {
        AT_WARN_LOG("AT_NotifyRnicIpv6ActInd: Send msg fail!");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
     : AT_AppSndRnicPdpActInd
   : APPPDPRNIC
   : enPdpType      PDP
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 2013727
           : Y00213812
       : 

*****************************************************************************/
VOS_VOID AT_AppSndRnicPdpActInd(
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
)
{
    VOS_UINT32                          ulResult;

    /* RNIC PDP */
    if ( TAF_PDP_IPV4== enPdpType )
    {
        AT_SendRnicIpv4ActInd(RNIC_RMNET_ID_0);
    }
    if ( TAF_PDP_IPV6== enPdpType )
    {
        AT_SendRnicIpv6ActInd(RNIC_RMNET_ID_0);
    }

    if ( TAF_PDP_IPV4V6== enPdpType )
    {
        ulResult = AT_SendRnicIpv4v6ActInd(RNIC_RMNET_ID_0);
        if (VOS_OK != ulResult)
        {
            AT_ERR_LOG("AT_AppSndRnicPdpActInd: ERROR: Send Rnic Ipv4 Act Ind To Rnic Failed.");
        }
    }
    return;
}

/*****************************************************************************
    : AT_SendRnicPdpDeactInd
  : APP
  : VOS_UINT8                           ucRabId
            VOS_UINT8                           ucRmNetId
  : 
    : 
            
  :
  :

      :
 1.       : 20111018
          : S62952
      : 

*****************************************************************************/
VOS_UINT32 AT_SendRnicPdpDeactInd(
    VOS_UINT8                           ucRabId,
    VOS_UINT8                           ucRmNetId
)
{
    AT_RNIC_PDP_DEACT_IND_STRU         *pstMsg;

    /* AT_NDIS_PDP_DEACT_IND_STRU */
    pstMsg = (AT_RNIC_PDP_DEACT_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                            WUEPS_PID_AT,
                            sizeof(AT_RNIC_PDP_DEACT_IND_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        AT_WARN_LOG("AT_NotifyRnicPdpDeactInd: alloc msg fail!");
        return VOS_ERR;
    }

    /*  */
    TAF_MEM_SET_S((VOS_CHAR*)pstMsg + VOS_MSG_HEAD_LENGTH,
               (VOS_SIZE_T)(sizeof(AT_RNIC_PDP_DEACT_IND_STRU) - VOS_MSG_HEAD_LENGTH),
               0x00,
               (VOS_SIZE_T)(sizeof(AT_RNIC_PDP_DEACT_IND_STRU) - VOS_MSG_HEAD_LENGTH));

    /*  */
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = ACPU_PID_RNIC;
    pstMsg->enMsgId         = ID_AT_RNIC_PDP_DEACT_IND;

    /*  */
    pstMsg->ucRabId         = ucRabId;
    pstMsg->ucRmNetId       = ucRmNetId;

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_AT, pstMsg))
    {
        AT_WARN_LOG("AT_NotifyRnicPdpDeactInd: Send msg fail!");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
     : AT_AppPdpActOrig
   : PDP
   : usClientId - ID
             ucCid      - CID
             ucPdpType  - PDP
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 2011613
           : A00165503
       : 
  2.       : 20111020
           : A00165503
       : AT Project: PS
  3.       : 20111231
           : C00173809
       : ps

*****************************************************************************/
VOS_VOID AT_AppPdpActOrig(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCid,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
)
{
    TAF_PS_DIAL_PARA_STRU               stDialParaInfo;
    TAF_PDP_PRIM_CONTEXT_EXT_STRU       stPdpPrimContextExt;

    AT_GetPdpContextFromAtDialParam(&stPdpPrimContextExt,AT_APP_GetDailParaAddr());
    stPdpPrimContextExt.enPdpType   = enPdpType;
    stPdpPrimContextExt.ucCid       = ucCid;

    /* QOS */
    if (VOS_OK != AT_PS_SetQosPara(usClientId, AT_APP_GET_USR_CID(), ucCid))
    {
        return;
    }

    AT_GetPsDialParamFromAtDialParam(&stDialParaInfo,AT_APP_GetDailParaAddr());
    stDialParaInfo.enPdpType    = enPdpType;
    stDialParaInfo.ucCid        = ucCid;

    /* PDP */
    if ( VOS_OK == TAF_PS_CallOrig(WUEPS_PID_AT,
                                   AT_PS_BuildExClientId(usClientId),
                                   0, &stDialParaInfo) )
    {
        if (TAF_PDP_IPV4 == enPdpType)
        {
            g_stAtAppPdpEntity.ucIpv4Cid = ucCid;
        }
        else
        {
            g_stAtAppPdpEntity.ucIpv6Cid = ucCid;
        }

        AT_APP_SetActPdpType(enPdpType);

        AT_AppSetPdpState(enPdpType, AT_PDP_STATE_ACTING);
    }

    return;
}

/*****************************************************************************
     : AT_ProcAppRegFCPoint
   : APPPDP
   : TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent,
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20130708
           : Y00213812
       : VoLTE_PhaseI 

*****************************************************************************/
VOS_VOID  AT_ProcAppRegFCPoint(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
    VOS_UINT32                          ulResult;
    AT_FCID_MAP_STRU                    stFCPriOrg;
    FC_ID_ENUM_UINT8                    enDefaultFcId;

    /* APPNDIS1 */
    enDefaultFcId = FC_ID_NIC_1;

    ulResult = AT_GetFcPriFromMap(enDefaultFcId ,&stFCPriOrg);
    if (VOS_OK == ulResult)
    {
        /* FC ID.*/
        if (VOS_TRUE != stFCPriOrg.ulUsed)
        {
            /* APP(1) */
            AT_AppRegFCPoint(enDefaultFcId, pstEvent, RNIC_RMNET_ID_0);
        }
        else
        {
            /* APPQOSFC_PRI_FOR_PDN_LOWEST */
            AT_NORM_LOG("AT_ProcAppRegFCPoint: No need to change the default QOS priority.");
        }
    }

    return;
}

/*****************************************************************************
     : AT_SaveIPv6Pcscf
   : IPV6PcscfPDP
   : TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent,
             AT_PDP_ENTITY_STRU                 *pstPdpEntity
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20111225
           : c00173809
       : /PS
  2.       : 20130708
           : Y00213812
       : VoLTE_PhaseI EVENT
  3.       : 20120807
           : f00179208
       : :DTS2015031000157, p-cscf
*****************************************************************************/
VOS_VOID  AT_SaveIPv6Pcscf(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent,
    AT_PDP_ENTITY_STRU                 *pstPdpEntity
)
{
    VOS_UINT8                           ucIndex;

    pstPdpEntity->stIpv6Dhcp.stIpv6PcscfList.ucIpv6PcscfAddrNum = AT_MIN(TAF_PCSCF_ADDR_MAX_NUM,
                                                                         pstEvent->stIpv6PcscfList.ucIpv6PcscfAddrNum);

    for (ucIndex = 0; ucIndex < pstPdpEntity->stIpv6Dhcp.stIpv6PcscfList.ucIpv6PcscfAddrNum; ucIndex++)
    {
        TAF_MEM_CPY_S(pstPdpEntity->stIpv6Dhcp.stIpv6PcscfList.astIpv6PcscfAddrList[ucIndex].aucPcscfAddr,
                      TAF_IPV6_ADDR_LEN,
                      pstEvent->stIpv6PcscfList.astIpv6PcscfAddrList[ucIndex].aucPcscfAddr,
                      TAF_IPV6_ADDR_LEN);
    }
}
/*****************************************************************************
     : AT_SaveIPv6Dns
   : IPV6DNSPDP
   : TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU        *pstEvent,
             AT_PDP_ENTITY_STRU                 *pstPdpEntity
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20111225
           : c00173809
       : /PS
  2.       : 20130708
           : Y00213812
       : VoLTE_PhaseI EVENT
*****************************************************************************/
VOS_VOID  AT_SaveIPv6Dns(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent,
    AT_PDP_ENTITY_STRU                 *pstPdpEntity
)
{
    pstPdpEntity->stIpv6Dhcp.bitOpIpv6PriDns    = VOS_FALSE;
    pstPdpEntity->stIpv6Dhcp.bitOpIpv6SecDns    = VOS_FALSE;

    /* Modified by Y00213812 for VoLTE_PhaseI , 2013-07-08, begin */
    /* DNSRADRV */
    if (VOS_TRUE == pstEvent->stIpv6Dns.bitOpPrimDnsAddr)
    {
        TAF_MEM_CPY_S((VOS_VOID*)pstPdpEntity->stIpv6Dhcp.aucIpv6PrimDNS,
                sizeof(pstPdpEntity->stIpv6Dhcp.aucIpv6PrimDNS),
                pstEvent->stIpv6Dns.aucPrimDnsAddr,
                TAF_IPV6_ADDR_LEN);
        pstPdpEntity->stIpv6Dhcp.bitOpIpv6PriDns = VOS_TRUE;
    }

    if (VOS_TRUE == pstEvent->stIpv6Dns.bitOpSecDnsAddr)
    {
        TAF_MEM_CPY_S((VOS_VOID*)pstPdpEntity->stIpv6Dhcp.aucIpv6SecDNS,
                   sizeof(pstPdpEntity->stIpv6Dhcp.aucIpv6SecDNS),
                   pstEvent->stIpv6Dns.aucSecDnsAddr,
                   TAF_IPV6_ADDR_LEN);
        pstPdpEntity->stIpv6Dhcp.bitOpIpv6SecDns = VOS_TRUE;
    }
    /* Modified by Y00213812 for VoLTE_PhaseI , 2013-07-08, end */

}

/*****************************************************************************
     : AT_AppActCnfBackProc
   : PDP
   : pstEvent   - 
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 2011721
           : A00165503
       : 

  2.       : 2012421
           : A00165503
       : DTS2012041806921: IPv4v6, IPv4
                 ONLYIPv6 ONLY, APP

  3.       : 2012630
           : A00165503
       : DTS2012062900707: IPv6, IPv6

  4.       : 2012822
           : A00165503
       : PS

  5.       : 20121221
           : l00227485
       : DSDA PhaseII
  6.       : 20130708
           : Y00213812
       : VoLTE_PhaseI EVENT

  7.       : 2015717
           : Y00213812
       : CDMA
*****************************************************************************/
VOS_VOID AT_AppActCnfBackProc(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
    AT_COMM_PS_CTX_STRU                *pstCommPsCtx = VOS_NULL_PTR;
    VOS_UINT8                           ucCid;
    VOS_UINT32                          ulRet;

    pstCommPsCtx = AT_GetCommPsCtxAddr();

    /* 52PDP */
    if ( (VOS_FALSE == pstEvent->bitOpCause)
      || ( (VOS_TRUE == pstEvent->bitOpCause)
        && (TAF_PS_CAUSE_SM_NW_SINGLE_ADDR_BEARERS_ONLY_ALLOWED == pstEvent->enCause) ) )
    {
        if (TAF_PDP_IPV4 == pstEvent->stPdpAddr.enPdpType)
        {
            if ((VOS_FALSE == pstEvent->bitOpCause)
             && (VOS_FALSE == pstCommPsCtx->ucRedialForNoCauseFlag))
            {
                AT_AppSndCallEndedResult(pstEvent->ucCid,
                                         TAF_PS_CAUSE_SM_NW_PDP_TYPE_IPV4_ONLY_ALLOWED,
                                         TAF_PDP_IPV6);
            }
            else
            {
                if (AT_PDP_STATE_IDLE == AT_AppGetPdpState(TAF_PDP_IPV6))
                {
                    /* CID */
                    ulRet = TAF_AGENT_FindCidForDial(pstEvent->stCtrl.usClientId, &ucCid);
                    if (VOS_OK == ulRet)
                    {
                        AT_AppPdpActOrig(pstEvent->stCtrl.usClientId, ucCid, TAF_PDP_IPV6);
                    }
                }
            }
        }
        else if (TAF_PDP_IPV6 == pstEvent->stPdpAddr.enPdpType)
        {
            if ((VOS_FALSE == pstEvent->bitOpCause)
             && (VOS_FALSE == pstCommPsCtx->ucRedialForNoCauseFlag))
            {
                AT_AppSndCallEndedResult(pstEvent->ucCid,
                                         TAF_PS_CAUSE_SM_NW_PDP_TYPE_IPV6_ONLY_ALLOWED,
                                         TAF_PDP_IPV4);
            }
            else
            {
                if (AT_PDP_STATE_IDLE == AT_AppGetPdpState(TAF_PDP_IPV4))
                {
                    /* CID */
                    ulRet = TAF_AGENT_FindCidForDial(pstEvent->stCtrl.usClientId, &ucCid);
                    if (VOS_OK == ulRet)
                    {
                        AT_AppPdpActOrig(pstEvent->stCtrl.usClientId, ucCid, TAF_PDP_IPV4);
                    }
                }
            }
        }
        else
        {
            ;
        }
    }
    else
    {
        /* , APP */
        switch (pstEvent->enCause)
        {
            /* #50 (IPv4 ONLY), APPIPv6 */
            case TAF_PS_CAUSE_SM_NW_PDP_TYPE_IPV4_ONLY_ALLOWED:
            case TAF_PS_CAUSE_PDP_TYPE_IPV4_ONLY_ALLOWED:
                AT_AppSndCallEndedResult(pstEvent->ucCid,
                                         pstEvent->enCause,
                                         TAF_PDP_IPV6);

                break;

            /* #51 (IPv6 ONLY), APPIPv4 */
            case TAF_PS_CAUSE_SM_NW_PDP_TYPE_IPV6_ONLY_ALLOWED:
            case TAF_PS_CAUSE_PDP_TYPE_IPV6_ONLY_ALLOWED:
                AT_AppSndCallEndedResult(pstEvent->ucCid,
                                         pstEvent->enCause,
                                         TAF_PDP_IPV4);

                break;

            /* ,  */
            default:
                AT_NORM_LOG1("AT_AppActCnfBackProc: Other <Cause>", pstEvent->enCause);
                break;
        }
    }

    return;
}

/*****************************************************************************
     : AT_AppIpv4ActCnfProc
   : IPV4PDP
   : pstAppPdpEntity - PDP
             pstEvent        - 
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 2011721
           : A00165503
       : 

  2.       : 20111217
           : C00173809
       : PSAPPADSRNIC

  3.       : 2012630
           : A00165503
       : DTS2012062900707: IPv6, IPv6

  4.       : 20121221
           : l00227485
       : DSDA PhaseII
*****************************************************************************/
VOS_VOID AT_AppIpv4PdpActCnfProc(
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
    VOS_UINT8                           ucCid;
    VOS_UINT32                          ulRet;

    /* DHCP */
    AT_AppDhcpReset();

    /* IPv4PDPCID */
    pstAppPdpEntity->ucIpv4Cid          = pstEvent->ucCid;

    /* IPv4PDP */
    AT_AppSetPdpState(TAF_PDP_IPV4, AT_PDP_STATE_ACTED);

    /* IPv4DHCP */
    AT_CtrlConnIndProc(pstEvent, AT_APP_USER);

    /* APPIPv4 */
    AT_AppSndCallConnectedResult(pstEvent->ucCid, TAF_PDP_IPV4);

    /*  */
    AT_ProcAppRegFCPoint(pstEvent);

    /* RNIC */
    AT_AppSndRnicPdpActInd(TAF_PDP_IPV4);

    /* IPV4V6PDP */
    if (TAF_PDP_IPV4V6 == AT_APP_GetFirstActPdpType())
    {
        switch (AT_APP_GetActPdpType())
        {
            /* PDPPDPIPV4
               IPV6PDPTAF_PDP_IPV6IPV6PDP
               IPV4IPV6PDP */
            case TAF_PDP_IPV4:
                if (AT_PDP_STATE_IDLE == AT_AppGetPdpState(TAF_PDP_IPV6))
                {
                    /* CID */
                    ulRet = TAF_AGENT_FindCidForDial(pstEvent->stCtrl.usClientId, &ucCid);
                    if (VOS_OK == ulRet )
                    {
                        AT_AppPdpActOrig(pstEvent->stCtrl.usClientId, ucCid, TAF_PDP_IPV6);
                    }
                }
                break;

            /* PDP */
            case TAF_PDP_IPV4V6:
                /* PDPIDLE */
                AT_AppSetPdpState(TAF_PDP_IPV4V6, AT_PDP_STATE_IDLE);

                AT_AppActCnfBackProc(pstEvent);
                break;

            default:
                AT_WARN_LOG("AT_AppIpv4ActCnfProc:WARNING: PDP type is invalid!");
                break;
        }
    }

    return;
}

/*****************************************************************************
     : AT_AppIpv6ActCnfProc
   : IPV6PDP
   : pstAppPdpEntity - PDP
             pstEvent        - 
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 2011721
           : A00165503
       : 

  2.       : 20111217
           : C00173809
       : PSAPPADSRNIC

  3.       : 2012630
           : A00165503
       : DTS2012062900707: IPv6, IPv6
*****************************************************************************/
VOS_VOID AT_AppIpv6PdpActCnfProc(
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
    /* DHCPv6 */
    AT_AppDhcpv6Reset();

    /* PDPCID */
    pstAppPdpEntity->ucIpv6Cid  = pstEvent->ucCid;

    /* IPv6 */
    AT_AppSetPdpState(TAF_PDP_IPV6, AT_PDP_STATE_ACTED);

    /* IPV6 */
    AT_AppCtrlConnIpv6IndProc(pstAppPdpEntity, pstEvent);

    /* IPv6RA */

    /*  */
    AT_ProcAppRegFCPoint(pstEvent);

    /* RNIC */
    AT_AppSndRnicPdpActInd(TAF_PDP_IPV6);

    /* IPV4V6PDP */
    if (TAF_PDP_IPV4V6 == AT_APP_GetFirstActPdpType())
    {
        switch (AT_APP_GetActPdpType())
        {
            case TAF_PDP_IPV6:
                /* PDPPDPIPV4
                   IPV6PDP, IPV6IPV4PDP */
                break;

            /* PDP */
            case TAF_PDP_IPV4V6:
                /* PDPIDLE */
               AT_AppSetPdpState(AT_APP_GetActPdpType(), AT_PDP_STATE_IDLE);

               AT_AppActCnfBackProc(pstEvent);
               break;

            default:
               AT_WARN_LOG("AT_AppIpv6ActCnfProc: PDP type is invalid!");
               break;
        }
    }

    return;
}

/*****************************************************************************
     : AT_AppIpv4v6ActCnfProc
   : IPv4v6PDP
   : pstAppPdpEntity - PDP
             pstEvent        - 
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 2011721
           : A00165503
       : 

  2.       : 20111217
           : C00173809
       : PSAPPADSRNIC

  3.       : 2012630
           : A00165503
       : DTS2012062900707: IPv6, IPv6
*****************************************************************************/
VOS_VOID AT_AppIpv4v6PdpActCnfProc(
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
    /* DHCP */
    AT_AppDhcpReset();

    /* DHCPv6 */
    AT_AppDhcpv6Reset();

    /* PDPCID */
    pstAppPdpEntity->ucIpv4v6Cid   = pstEvent->ucCid;

    /* IPv6 */
    AT_AppSetPdpState(TAF_PDP_IPV4V6, AT_PDP_STATE_ACTED);

    /* IPV4 */
    AT_CtrlConnIndProc(pstEvent, AT_APP_USER);

    /* IPV6*/
    AT_AppCtrlConnIpv6IndProc(pstAppPdpEntity, pstEvent);

    /* APPIPv4, IPv6RA */
    AT_AppSndCallConnectedResult(pstEvent->ucCid, TAF_PDP_IPV4);

    /*  */
    AT_ProcAppRegFCPoint(pstEvent);

    /* RNIC */
    AT_AppSndRnicPdpActInd(TAF_PDP_IPV4V6);

    return;
}

/*****************************************************************************
     : AT_AppIpv4DeactCnfProc
   : IPv4PDP
   : pstAppPdpEntity - PDP
             pstEvent        - 
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 2011723
           : A00165503
       : 

  2.       : 20111217
           : c00173809
       : PSADSRNIC

  3.       : 201262
           : A00165503
       : DTS2012060105018: IPv4v6, PDP(-
                 #39), UE

  4.       : 2012630
           : A00165503
       : DTS2012062900707: IPv6, IPv6

  5.       : 2012822
           : A00165503
       : PS
  6.       : 20130708
           : Y00213812
       : VoLTE_PhaseI EVENT
*****************************************************************************/
VOS_VOID AT_AppIpv4PdpDeactivatedProc(
    AT_PDP_ENTITY_STRU                  *pstAppPdpEntity,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
)
{
    AT_PDP_STATE_ENUM_U8                enPdpState;

    /* IPv4PDPIDLE */
    AT_AppSetPdpState(TAF_PDP_IPV4, AT_PDP_STATE_IDLE);

    /* DHCP */
    AT_AppDhcpReset();

    /* APPIPv4 */
    AT_AppSndCallEndedResult(pstEvent->ucCid,
                             pstEvent->enCause,
                             TAF_PDP_IPV4);

    /* Added by Y00213812 for VoLTE_PhaseI , 2013-07-08, begin */
    /* RNIC PDP */
    AT_SendRnicPdpDeactInd(pstEvent->ucRabId, RNIC_RMNET_ID_0);

    /* APP(1) */
    AT_AppDeRegFCPoint(FC_ID_NIC_1, pstEvent);
    /* Added by Y00213812 for VoLTE_PhaseI , 2013-07-08, end */

   /* IPv4PDP,  */
    enPdpState  = AT_AppGetPdpState(TAF_PDP_IPV6);
    if ( (AT_PDP_STATE_IDLE     != enPdpState)
      && (AT_PDP_STATE_DEACTING != enPdpState) )
    {
        if ( VOS_OK == TAF_PS_CallEnd(WUEPS_PID_AT,
                                      AT_PS_BuildExClientId(pstEvent->stCtrl.usClientId),
                                      0,
                                      pstAppPdpEntity->ucIpv6Cid) )
        {
            AT_AppSetPdpState(TAF_PDP_IPV6, AT_PDP_STATE_DEACTING);
        }
        else
        {
            AT_ERR_LOG("AT_AppIpv4DeactCnfProc:ERROR: Deactivate PDP failed!");
        }
    }
}

/*****************************************************************************
     : AT_AppIpv6DeactCnfProc
   : IPv4PDP
   : pstAppPdpEntity - PDP
             pstEvent        - 
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 2011723
           : A00165503
       : 

  2.       : 20111217
           : C00173809
       : PSPDPADSRNIC

  3.       : 201262
           : A00165503
       : DTS2012060105018: IPv4v6, PDP(-
                 #39), UE

  4.       : 2012630
           : A00165503
       : DTS2012062900707: IPv6, IPv6

  5.       : 2012822
           : A00165503
       : PS
  6.       : 20130708
           : Y00213812
       : VoLTE_PhaseI EVENT
*****************************************************************************/
VOS_VOID AT_AppIpv6PdpDeactivatedProc(
    AT_PDP_ENTITY_STRU                  *pstAppPdpEntity,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
)
{
    AT_PDP_STATE_ENUM_U8                enPdpState;

    /* IPv6PDPIDLE */
    AT_AppSetPdpState(TAF_PDP_IPV6, AT_PDP_STATE_IDLE);

    /* DHCPv6 */
    AT_AppDhcpv6Reset();

    /* APPIPv6 */
    AT_AppSndCallEndedResult(pstEvent->ucCid,
                             pstEvent->enCause,
                             TAF_PDP_IPV6);

    /* Added by Y00213812 for VoLTE_PhaseI , 2013-07-08, begin */
    /* RNIC PDP */
    AT_SendRnicPdpDeactInd(pstEvent->ucRabId, RNIC_RMNET_ID_0);

    /* APP(1) */
    AT_AppDeRegFCPoint(FC_ID_NIC_1, pstEvent);
    /* Added by Y00213812 for VoLTE_PhaseI , 2013-07-08, end */

    /* IPv4PDP,  */
    enPdpState  = AT_AppGetPdpState(TAF_PDP_IPV4);
    if ( (AT_PDP_STATE_IDLE     != enPdpState)
      && (AT_PDP_STATE_DEACTING != enPdpState) )
    {
        if ( VOS_OK == TAF_PS_CallEnd(WUEPS_PID_AT,
                                      AT_PS_BuildExClientId(pstEvent->stCtrl.usClientId),
                                      0,
                                      pstAppPdpEntity->ucIpv4Cid) )
        {
            AT_AppSetPdpState(TAF_PDP_IPV4, AT_PDP_STATE_DEACTING);
        }
        else
        {
            AT_ERR_LOG("AT_AppIpv6DeactCnfProc:ERROR: Deactivate PDP failed!");
        }
    }
}

/*****************************************************************************
     : AT_AppIpv4v6DeactCnfProc
   : IPv4v6PDP
   : pstAppPdpEntity - PDP
             pstEvent        - 
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 2011723
           : A00165503
       : 

  2.       : 20111217
           : C00173809
       : psPDPADSRNIC

  3.       : 201262
           : A00165503
       : DTS2012060105018: IPv4v6, PDP(-
                 #39), UE

  4.       : 2012630
           : A00165503
       : DTS2012062900707: IPv6, IPv6

  5.       : 2012822
           : A00165503
       : PS
  6.       : 20130708
           : Y00213812
       : VoLTE_PhaseI EVENT
*****************************************************************************/
VOS_VOID AT_AppIpv4v6PdpDeactivatedProc(
    AT_PDP_ENTITY_STRU                  *pstAppPdpEntity,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
)
{
    /* IPv6PDPIDLE */
    AT_AppSetPdpState(TAF_PDP_IPV4V6, AT_PDP_STATE_IDLE);

    /* DHCP */
    AT_AppDhcpReset();

    /* DHCPv6 */
    AT_AppDhcpv6Reset();

    /* APPIPv4 */
    AT_AppSndCallEndedResult(pstEvent->ucCid,
                             pstEvent->enCause,
                             TAF_PDP_IPV4);

    /* APPIPv6 */
    AT_AppSndCallEndedResult(pstEvent->ucCid,
                             pstEvent->enCause,
                             TAF_PDP_IPV6);

    /* Added by Y00213812 for VoLTE_PhaseI , 2013-07-08, begin */
    /* RNIC PDP */
    AT_SendRnicPdpDeactInd(pstEvent->ucRabId, RNIC_RMNET_ID_0);

    /* APP(1) */
    AT_AppDeRegFCPoint(FC_ID_NIC_1, pstEvent);
    /* Added by Y00213812 for VoLTE_PhaseI , 2013-07-08, end */

    return;
}

/*****************************************************************************
     : AT_AppIpv4v6PdpActRejProc
   : IPv4PDP
   : pstAppPdpEntity - PDP
             pstEvent        - 
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 2011723
           : A00165503
       : 

  2.       : 20111217
           : C00173809
       : PS

  3.       : 2012616
           : A00165503
       : DTS2012061408511: IPv4v6,
                 IPv4PDP

  4.       : 2012630
           : A00165503
       : DTS2012062900707: IPv6, IPv6

  5.       : 2012822
           : A00165503
       : PS
  6.       : 2013508
           : Y00213812
       : V9R1 IPv6&TAF/SM Project
*****************************************************************************/
VOS_VOID AT_AppIpv4PdpActRejProc(
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity,
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU  *pstEvent
)
{
    AT_PDP_STATE_ENUM_U8                enPreIpv4State;

    enPreIpv4State = pstAppPdpEntity->enIpv4State;

    /* IPv4v6PDP, , 28, 
       IPv4/IPv6PDP, IPv4, IPv6,
       IPv4PDP, IPV6
       PDPPDP, IPv6PDP, 
       IPv4PDP */

    /* IPv4PDPIDLE */
    AT_AppSetPdpState(TAF_PDP_IPV4, AT_PDP_STATE_IDLE);

    /* IPv4 */
    AT_AppSndCallEndedResult(pstEvent->ucCid,
                             pstEvent->enCause,
                             TAF_PDP_IPV4);
    if ((TAF_PDP_IPV4V6 == AT_APP_GetFirstActPdpType())
     && (AT_PDP_STATE_ACTING == enPreIpv4State) )
    {
        /* IPv6, , IPv6PDP */
        if (AT_PDP_STATE_IDLE == AT_AppGetPdpState(TAF_PDP_IPV6))
        {
            /* IPv6PDP */
            AT_AppPdpActOrig(pstEvent->stCtrl.usClientId, pstEvent->ucCid, TAF_PDP_IPV6);

            /* PDP,  */
            return;
        }

        /* PDP,  */
        return;
    }

    /*  */
    TAF_MEM_SET_S(AT_APP_GetDailParaAddr(), sizeof(AT_DIAL_PARAM_STRU), 0x00, sizeof(AT_DIAL_PARAM_STRU));

    return;
}

/*****************************************************************************
     : AT_AppIpv6PdpActRejProc
   : IPv6PDP
   : pstAppPdpEntity - PDP
             pstEvent        - 
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 2011723
           : A00165503
       : 

  2.       : 20111217
           : C00173809
       : PS

  3.       : 2012630
           : A00165503
       : DTS2012062900707: IPv6, IPv6

  4.       : 2012822
           : A00165503
       : PS
*****************************************************************************/
VOS_VOID AT_AppIpv6PdpActRejProc(
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity,
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU  *pstEvent
)
{
    /* IPv6, IPv4, IPv4PDP
       , IPv4PDP, PDP */

    /* IPv6PDPIDLE */
    AT_AppSetPdpState(TAF_PDP_IPV6, AT_PDP_STATE_IDLE);

    /* IPv6 */
    AT_AppSndCallEndedResult(pstEvent->ucCid,
                             pstEvent->enCause,
                             TAF_PDP_IPV6);

    /*  */
    TAF_MEM_SET_S(AT_APP_GetDailParaAddr(), sizeof(AT_DIAL_PARAM_STRU), 0x00, sizeof(AT_DIAL_PARAM_STRU));

    return;
}

/*****************************************************************************
     : AT_AppIpv4v6PdpActRejProc
   : IPv4PDP
   : pstAppPdpEntity - PDP
             pstEvent        - 
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 2011723
           : A00165503
       : 

  2.       : 20111217
           : C00173809
       : PS

  3.       : 2012630
           : A00165503
       : DTS2012062900707: IPv6, IPv6

  4.       : 2012822
           : A00165503
       : PS
*****************************************************************************/
VOS_VOID AT_AppIpv4v6PdpActRejProc(
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity,
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU  *pstEvent
)
{
    /* IPv4v6PDPIDLE */
    AT_AppSetPdpState(TAF_PDP_IPV4V6, AT_PDP_STATE_IDLE);

    /* IPv4IPv6PDP */
    if (TAF_PS_CAUSE_SM_NW_UNKNOWN_PDP_ADDR_OR_TYPE == pstEvent->enCause)
    {
        /* IPv4PDP */
        AT_AppPdpActOrig(pstEvent->stCtrl.usClientId, pstEvent->ucCid, TAF_PDP_IPV4);
    }
    else
    {
        /* IPv4 */
        AT_AppSndCallEndedResult(pstEvent->ucCid,
                                 pstEvent->enCause,
                                 TAF_PDP_IPV4);

        /* IPv6 */
        AT_AppSndCallEndedResult(pstEvent->ucCid,
                                 pstEvent->enCause,
                                 TAF_PDP_IPV6);

        /*  */
        TAF_MEM_SET_S(AT_APP_GetDailParaAddr(), sizeof(AT_DIAL_PARAM_STRU), 0x00, sizeof(AT_DIAL_PARAM_STRU));
    }

    return;
}

/*****************************************************************************
     : AT_AppPsRspPdpActEvtCnfProc
   : PDPAPP
   : ucIndex  - 
             pstEvent - 
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 2011720
           : A00165503
       : 

*****************************************************************************/
VOS_VOID AT_AppPsRspEvtPdpActCnfProc(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity;

    pstAppPdpEntity                     = AT_APP_GetPdpEntInfoAddr();

    /* PDP*/
    switch ( pstEvent->stPdpAddr.enPdpType )
    {
        case TAF_PDP_IPV4:
            /* IPv4PDP */
            AT_AppIpv4PdpActCnfProc(pstAppPdpEntity, pstEvent);
            break;

        case TAF_PDP_IPV6:
            /* IPv6PDP */
            AT_AppIpv6PdpActCnfProc(pstAppPdpEntity, pstEvent);
            break;

        case TAF_PDP_IPV4V6:
            /* IPv4v6PDP */
            AT_AppIpv4v6PdpActCnfProc(pstAppPdpEntity, pstEvent);
            break;

        default:
            AT_WARN_LOG("AT_AppPsRspPdpActEvtCnfProc:WARNING: PDP type is invaild!");
            break;
    }

    return;
}

/*****************************************************************************
     : AT_AppPsRspPdpActEvtRejProc
   : PDPAPP
   : ucIndex  - 
             pstEvent - 
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 2011721
           : A00165503
       : 

*****************************************************************************/
VOS_VOID AT_AppPsRspEvtPdpActRejProc(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU  *pstEvent
)
{
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity;

    pstAppPdpEntity                     = AT_APP_GetPdpEntInfoAddr();

    switch (AT_APP_GetActPdpType())
    {
        case TAF_PDP_IPV4:
            AT_AppIpv4PdpActRejProc(pstAppPdpEntity, pstEvent);
            break;

        case TAF_PDP_IPV6:
            AT_AppIpv6PdpActRejProc(pstAppPdpEntity, pstEvent);
            break;

        case TAF_PDP_IPV4V6:
            AT_AppIpv4v6PdpActRejProc(pstAppPdpEntity, pstEvent);
            break;

        default:
            AT_WARN_LOG("AT_AppPsRspEvtPdpActRejProc:WARNING: PDP type is invaild!");
            break;
    }

    return;
}

/*****************************************************************************
     : AT_AppPsRspPdpDeactEvtCnfProc
   : PDPAPP
   : ucIndex  - 
             pstEvent - 
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 2011721
           : A00165503
       : 

*****************************************************************************/
VOS_VOID AT_AppPsRspEvtPdpDeactCnfProc(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
)
{
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity;
    AT_DIAL_PARAM_STRU                 *pstAppDialPara;

    pstAppPdpEntity                     = AT_APP_GetPdpEntInfoAddr();
    pstAppDialPara                      = AT_APP_GetDailParaAddr();

    switch (pstEvent->enPdpType)
    {
        case TAF_PDP_IPV4:
            AT_AppIpv4PdpDeactivatedProc(pstAppPdpEntity, pstEvent);
            break;

        case TAF_PDP_IPV6:
            AT_AppIpv6PdpDeactivatedProc(pstAppPdpEntity, pstEvent);
            break;

        case TAF_PDP_IPV4V6:
            AT_AppIpv4v6PdpDeactivatedProc(pstAppPdpEntity, pstEvent);
            break;

        default:
            AT_WARN_LOG("AT_AppPsRspPdpDeactEvtCnfProc:WARNING: Invalid PDP type.");
            break;
    }

    /*  */
    if ( (AT_PDP_STATE_IDLE == pstAppPdpEntity->enIpv4State)
      && (AT_PDP_STATE_IDLE == pstAppPdpEntity->enIpv6State)
      && (AT_PDP_STATE_IDLE == pstAppPdpEntity->enIpv4v6State) )
    {
        TAF_MEM_SET_S(pstAppDialPara, sizeof(AT_DIAL_PARAM_STRU), 0x00, sizeof(AT_DIAL_PARAM_STRU));
    }

    return;
}

/*****************************************************************************
     : AT_AppPsRspPdpDeactivatedEvtProc
   : PDP, APP
   : ucIndex  - 
             pstEvent - 
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 2011721
           : A00165503
       : 

*****************************************************************************/
VOS_VOID AT_AppPsRspEvtPdpDeactivatedProc(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_DEACTIVATE_IND_STRU *pstEvent
)
{
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity;
    AT_DIAL_PARAM_STRU                 *pstAppDialPara;

    pstAppPdpEntity                     = AT_APP_GetPdpEntInfoAddr();
    pstAppDialPara                      = AT_APP_GetDailParaAddr();

    switch (pstEvent->enPdpType)
    {
        case TAF_PDP_IPV4:
            AT_AppIpv4PdpDeactivatedProc(pstAppPdpEntity, pstEvent);
            break;

        case TAF_PDP_IPV6:
            AT_AppIpv6PdpDeactivatedProc(pstAppPdpEntity, pstEvent);
            break;

        case TAF_PDP_IPV4V6:
            AT_AppIpv4v6PdpDeactivatedProc(pstAppPdpEntity, pstEvent);
            break;

        default:
            AT_WARN_LOG("AT_AppPsRspPdpDeactEvtCnfProc:WARNING: Invalid PDP type.");
            break;
    }

    /* APP */
    if ( (AT_PDP_STATE_IDLE == pstAppPdpEntity->enIpv4State)
      && (AT_PDP_STATE_IDLE == pstAppPdpEntity->enIpv6State)
      && (AT_PDP_STATE_IDLE == pstAppPdpEntity->enIpv4v6State) )
    {
        TAF_MEM_SET_S(pstAppDialPara, sizeof(AT_DIAL_PARAM_STRU), 0x00, sizeof(AT_DIAL_PARAM_STRU));
    }

    return;
}

/*****************************************************************************
     : AT_AppSetFlowCtrl
   : 
   : ulParam1   - 
             ulParam2   - 
   : 
     : VOS_OK     - 
             VOS_ERR    - 
   :
   :

       :
  1.       : 2012531
           : A00165503
       : 

*****************************************************************************/
VOS_UINT32 AT_AppSetFlowCtrl(
    VOS_UINT32                          ulParam1,
    VOS_UINT32                          ulParam2
)
{
    VOS_UINT32                          ulRslt;

    ulRslt = RNIC_StartFlowCtrl((VOS_UINT8)ulParam1);

    if (VOS_OK != ulRslt)
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
     : AT_AppClearFlowCtrl
   : 
   : ulParam1   - 
             ulParam2   - 
   : 
     : VOS_OK     - 
             VOS_ERR    - 
   :
   :

       :
  1.       : 2012531
           : A00165503
       : 

*****************************************************************************/
VOS_UINT32 AT_AppClearFlowCtrl(
    VOS_UINT32                          ulParam1,
    VOS_UINT32                          ulParam2
)
{
    VOS_UINT32                          ulRslt;

    ulRslt = RNIC_StopFlowCtrl((VOS_UINT8)ulParam1);

    if (VOS_OK != ulRslt)
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
     : AT_AppRegFCPoint
   : 
   : FC_ID_ENUM_UINT8                    enFcId
             TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU   *pstEvent
             VOS_UINT8                           ucRmNetId
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 2012531
           : A00165503
       : 
  2.       : 20121222
           : l00227485
       : DSDA PhaseII
  3.       : 20130417
           : f00179208
       : C
*****************************************************************************/
VOS_UINT32 AT_AppRegFCPoint(
    FC_ID_ENUM_UINT8                    enFcId,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent,
    VOS_UINT8                           ucRmNetId
)
{
    FC_REG_POINT_STRU                   stRegFcPoint;
    FC_PRI_ENUM_UINT8                   enDefaultFcPri;
    VOS_UINT32                          ulRslt;
    MODEM_ID_ENUM_UINT16                enModemId;

    enModemId = MODEM_ID_0;

    TAF_MEM_SET_S(&stRegFcPoint, sizeof(stRegFcPoint), 0x00, sizeof(FC_REG_POINT_STRU));

    ulRslt = AT_GetModemIdFromClient((AT_CLIENT_TAB_INDEX_UINT8)pstEvent->stCtrl.usClientId, &enModemId);

    if (VOS_OK != ulRslt)
    {
        AT_ERR_LOG("AT_AppRegFCPoint: Get modem id fail.");
        return VOS_ERR;
    }

    /* RABID */
    FC_ChannelMapCreate(enFcId, pstEvent->ucRabId, enModemId);

    /* RAB QoS, */
    /*  FC_PRI_3        
        FC_PRI_4        NONGBR
        FC_PRI_5        GBR */
    enDefaultFcPri          = FC_PRI_FOR_PDN_LOWEST;
    stRegFcPoint.enFcId     = enFcId;
    stRegFcPoint.enFcPri    = enDefaultFcPri;

    stRegFcPoint.enModemId  = enModemId;
    stRegFcPoint.pClrFunc   = AT_AppClearFlowCtrl;
    stRegFcPoint.pSetFunc   = AT_AppSetFlowCtrl;

    /* Paramter1RmNetId, Paramter2FCID */
    stRegFcPoint.ulParam1   = ucRmNetId;
    stRegFcPoint.ulParam2   = enFcId;
    stRegFcPoint.pRstFunc   = AT_ResetFlowCtl;

    /* , MEMCDS */
    stRegFcPoint.enPolicyId = FC_POLICY_ID_MEM;
    ulRslt = FC_RegPoint(&stRegFcPoint);
    if (VOS_OK != ulRslt)
    {
        AT_ERR_LOG("AT_AppRegFCPoint: ERROR: reg mem point Failed.");
        return VOS_ERR;
    }


    stRegFcPoint.enPolicyId = FC_POLICY_ID_CDS;
    ulRslt = FC_RegPoint(&stRegFcPoint);
    if (VOS_OK != ulRslt)
    {
        AT_ERR_LOG("AT_AppRegFCPoint: ERROR: reg CDS point Failed.");
        return VOS_ERR;
    }

    /* FCIDFC Pri */
    g_stFcIdMaptoFcPri[enFcId].ulUsed       = VOS_TRUE;
    g_stFcIdMaptoFcPri[enFcId].enFcPri      = enDefaultFcPri;
    /* RABIDRABID */
    g_stFcIdMaptoFcPri[enFcId].ulRabIdMask  |= ((VOS_UINT32)1 << (pstEvent->ucRabId));
    g_stFcIdMaptoFcPri[enFcId].enModemId    = enModemId;

    /*  */
    AT_MNTN_TraceRegFcPoint((VOS_UINT8)pstEvent->stCtrl.usClientId, AT_FC_POINT_TYPE_RMNET);

    return VOS_OK;
}

/*****************************************************************************
     : AT_AppDeRegFCPoint
   : 
   : FC_ID_ENUM_UINT8                            enFcId,
             TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU        *pstEvent
   : 
     : VOS_OK     - 
             VOS_ERR    - 
   :
   :

       :
  1.       : 2012531
           : A00165503
       : 
  2.       : 20121222
           : l00227485
       : DSDA PhaseII
  3.       : 20130417
           : f00179208
       : C
*****************************************************************************/
VOS_UINT32 AT_AppDeRegFCPoint(
    FC_ID_ENUM_UINT8                     enFcId,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
)
{
    VOS_UINT32                          ulRslt;
    MODEM_ID_ENUM_UINT16                enModemId;

    enModemId = MODEM_ID_0;

    ulRslt = AT_GetModemIdFromClient((AT_CLIENT_TAB_INDEX_UINT8)pstEvent->stCtrl.usClientId, &enModemId);

    if (VOS_OK != ulRslt)
    {
        AT_ERR_LOG("AT_AppDeRegFCPoint: Get modem id fail.");
        return VOS_ERR;
    }

    /* FC_DeRegPoint,FC_ChannelMapDelete */
    FC_ChannelMapDelete(pstEvent->ucRabId, enModemId);

    ulRslt = FC_DeRegPoint(enFcId, enModemId);
    if (VOS_OK != ulRslt)
    {
        AT_ERR_LOG("AT_AppDeRegFCPoint: ERROR: de reg point Failed.");
        return VOS_ERR;
    }

    /* FCIDFC Pri */
    g_stFcIdMaptoFcPri[enFcId].ulUsed       = VOS_FALSE;
    g_stFcIdMaptoFcPri[enFcId].enFcPri      = FC_PRI_BUTT;
    /* RABIDRABID */
    g_stFcIdMaptoFcPri[enFcId].ulRabIdMask &= ~((VOS_UINT32)1 << pstEvent->ucRabId);
    g_stFcIdMaptoFcPri[enFcId].enModemId    = MODEM_ID_BUTT;

    /*  */
    AT_MNTN_TraceDeregFcPoint((VOS_UINT8)pstEvent->stCtrl.usClientId, AT_FC_POINT_TYPE_RMNET);

    return VOS_OK;
}

/*****************************************************************************
     : AT_APP_ParseUsrInfo
   : APP
   : ucIndex     - (ClientId)
   : pstUserInfo - 
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20130114
           : A00165503
       : 
*****************************************************************************/
VOS_VOID AT_APP_ParseUsrInfo(
    VOS_UINT8                           ucIndex,
    AT_PS_USER_INFO_STRU               *pstUsrInfo
)
{
    AT_CLIENT_TAB_INDEX_UINT8           enUserIndex;

    if (VOS_TRUE == AT_CheckAppUser(ucIndex))
    {
        enUserIndex = ucIndex;
    }
    else
    {
        enUserIndex = AT_CLIENT_TAB_APP_INDEX;
    }

    pstUsrInfo->enPortIndex = ucIndex;
    pstUsrInfo->enUserIndex = enUserIndex;
    pstUsrInfo->ucUsrType   = (AT_USER_TYPE)gastAtClientTab[enUserIndex].UserType;
    pstUsrInfo->ucUsrCid    = (VOS_UINT8)gastAtParaList[0].ulParaValue;

    return;
}

/*****************************************************************************
     : AT_GetFCPriFromQos
   : QosFC
   : TAF_UMTS_QOS_STRU                  *pstUmtsQos
   : 
     : FC_PRI_ENUM_UINT8
   :
   :

       :
  1.       : 20111217
           : c00173809
       : 
  2.       : 20130708
           : Y00213812
       : VoLTE_PhaseI EVENTQOS
*****************************************************************************/
FC_PRI_ENUM_UINT8 AT_GetFCPriFromQos(
    TAF_UMTS_QOS_STRU                  *pstUmtsQos
)
{

    FC_PRI_ENUM_UINT8                   enFCPri;
    VOS_UINT8                           ucTrafficClass;

    /*  */
    enFCPri         = FC_PRI_FOR_PDN_NONGBR;

    ucTrafficClass              = pstUmtsQos->ucTrafficClass;

    /* QOS trafficClassQCI */
    if (AT_QOS_TRAFFIC_CLASS_CONVERSATIONAL == ucTrafficClass)
    {
        enFCPri = FC_PRI_FOR_PDN_GBR;
    }
    else if (AT_QOS_TRAFFIC_CLASS_STREAMING == ucTrafficClass)
    {
        enFCPri = FC_PRI_FOR_PDN_GBR;
    }
    else if (AT_QOS_TRAFFIC_CLASS_INTERACTIVE == ucTrafficClass)
    {
        enFCPri = FC_PRI_FOR_PDN_NONGBR;
    }
    else
    {
        enFCPri = FC_PRI_FOR_PDN_LOWEST;
    }

    return enFCPri;
}

/*****************************************************************************
     : AT_ModemPsRspPdpDeactivatedEvtProc
   : pdpModem
   : ucIndex --- 
             pEvent  --- 
   : 
     : 
   :
   :

       :
  1.       : 201155
           : S62952
       : 
  2.       : 20111217
           : C00173809
       : PSIPMODEMADS
  3.       : 20130527
           : f00179208
       : V3R3 PPP PROJECT
  4.       : 20130708
           : Y00213812
       : VoLTE_PhaseI EVENT
  5.       : 2013923
           : A00165503
       : UART-MODEM: UARTPPP
*****************************************************************************/
VOS_VOID  AT_ModemPsRspPdpDeactivatedEvtProc(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
)
{
    AT_UART_LINE_CTRL_STRU             *pstLineCtrl = VOS_NULL_PTR;
    VOS_UINT32                          ulATHCmdFlg;
    VOS_UINT32                          ulResult;
    VOS_UINT16                          usLength;

    pstLineCtrl = AT_GetUartLineCtrlInfo();
    usLength    = 0;
    ulResult    = AT_FAILURE;
    ulATHCmdFlg = (AT_CMD_H_PS_SET == AT_PS_GET_CURR_CMD_OPT(ucIndex)) ?
                  VOS_TRUE : VOS_FALSE;

    /* Added by Y00213812 for VoLTE_PhaseI , 2013-07-08, begin */
    /* Modem */
    AT_DeRegModemPsDataFCPoint(ucIndex, pstEvent->ucRabId);
    /* Added by Y00213812 for VoLTE_PhaseI , 2013-07-08, end */

    if (AT_PPP_DATA_MODE == gastAtClientTab[ucIndex].DataMode)
    {
        /* PPP & HDLC */
        PPP_RcvAtCtrlOperEvent(gastAtClientTab[ucIndex].usPppId, PPP_AT_CTRL_REL_PPP_REQ);
        PPP_RcvAtCtrlOperEvent(gastAtClientTab[ucIndex].usPppId, PPP_AT_CTRL_HDLC_DISABLE);

        if (AT_DATA_MODE == gastAtClientTab[ucIndex].Mode)
        {
            /* AT2D13296PPP
               PPP_AT_CTRL_REL_PPP_REQ
               PPPAT_PPP_PROTOCOL_REL_IND_MSG */
            /* PPPAT_PPP_PROTOCOL_REL_IND_MSG */
            AT_STOP_TIMER_CMD_READY(ucIndex);

            if (AT_SUCCESS != At_StartTimer(AT_PPP_PROTOCOL_REL_TIME, ucIndex))
            {
                AT_ERR_LOG("At_UsbModemStatusPreProc:ERROR:Start Timer fail");
            }

            /*  */
            gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_WAIT_PPP_PROTOCOL_REL_SET;

            return;
        }
    }
    else if (AT_IP_DATA_MODE == gastAtClientTab[ucIndex].DataMode)
    {
        /* PPP & HDLC */
        PPP_RcvAtCtrlOperEvent(gastAtClientTab[ucIndex].usPppId, PPP_AT_CTRL_REL_PPP_RAW_REQ);
        PPP_RcvAtCtrlOperEvent(gastAtClientTab[ucIndex].usPppId, PPP_AT_CTRL_HDLC_DISABLE);
    }
    else
    {
        /*  */
        AT_WARN_LOG("TAF_PS_EVT_PDP_DEACTIVATED OTHER MODE");
    }

    /*  */
    At_SetMode(ucIndex, AT_CMD_MODE,AT_NORMAL_MODE);

    if (VOS_TRUE == ulATHCmdFlg)
    {
        ulResult = AT_OK;
    }
    else
    {
        ulResult = AT_NO_CARRIER;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);
    gstAtSendData.usBufLen = usLength;
    At_FormatResultData(ucIndex,ulResult);

    /* ATHPPP, DCDCONNECT ON, DCD */
    if ( (AT_OK == ulResult)
      && (AT_UART_DCD_MODE_CONNECT_ON == pstLineCtrl->enDcdMode) )
    {
        AT_CtrlDCD(ucIndex, AT_IO_LEVEL_LOW);
    }

    return;
}

/*****************************************************************************
     : AT_ModemPsRspPdpActEvtRejProc
   : pdpAP MODEM
   : ucIndex --- 
             pEvent  --- 
   : 
     : 
   :
   :

       :
  1.       : 201155
           : S62952
       : 
  2.       : 20111022
           : f62575
       : AT PROJECT OM_GreenChannel -> OM_AppGreenChannel
  3.       : 20150722
           : wx270776
       : OM
*****************************************************************************/
VOS_VOID  AT_ModemPsRspPdpActEvtRejProc(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU  *pstEvent
)
{
    VOS_UINT32                          ulResult;
    VOS_UINT16                          usLength;

    ulResult                            = AT_FAILURE;
    usLength                            = 0;

    if ( (AT_CMD_D_PPP_CALL_SET == gastAtClientTab[ucIndex].CmdCurrentOpt)
      || (AT_CMD_PPP_ORG_SET == gastAtClientTab[ucIndex].CmdCurrentOpt) )
    {
        ulResult = AT_NO_CARRIER;
        PPP_RcvAtCtrlOperEvent(gastAtClientTab[ucIndex].usPppId, PPP_AT_CTRL_REL_PPP_REQ);

        /* PPPHDLC */
        PPP_RcvAtCtrlOperEvent(gastAtClientTab[ucIndex].usPppId, PPP_AT_CTRL_HDLC_DISABLE);

        /*  */
        At_SetMode(ucIndex,AT_CMD_MODE,AT_NORMAL_MODE);

        /* Deleted by wx270776 for OM, 2015-6-29, begin */
        /* Deleted by wx270776 for OM, 2015-6-29, end */
    }
    else if (AT_CMD_D_IP_CALL_SET == gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        ulResult = AT_ERROR;
        PPP_RcvAtCtrlOperEvent(gastAtClientTab[ucIndex].usPppId, PPP_AT_CTRL_REL_PPP_RAW_REQ);

        /* PPPHDLC */
        PPP_RcvAtCtrlOperEvent(gastAtClientTab[ucIndex].usPppId, PPP_AT_CTRL_HDLC_DISABLE);


        /* Deleted by wx270776 for OM, 2015-6-29, begin */
        /* Deleted by wx270776 for OM, 2015-6-29, end */
    }
    else
    {
        ulResult = AT_ERROR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);
    gstAtSendData.usBufLen = usLength;
    At_FormatResultData(ucIndex,ulResult);

    return;
}

/*****************************************************************************
     : AT_FillPppIndConfigInfoPara
   : PPP
   : AT_PPP_IND_CONFIG_INFO_STRU        *pstPppIndConfigInfo
             TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 2011329
           : A00165503
       : 
  2.       : 20121211
           : l00167671
       : DTS2012121802573, TQE
  3.       : 20130708
           : Y00213812
       : VoLTE_PhaseI EVENT

*****************************************************************************/
VOS_VOID AT_FillPppIndConfigInfoPara(
    AT_PPP_IND_CONFIG_INFO_STRU        *pstPppIndConfigInfo,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
    /* Modified by Y00213812 for VoLTE_PhaseI , 2013-07-08, begin */
    /* IP */
    TAF_MEM_CPY_S(pstPppIndConfigInfo->aucIpAddr,
               sizeof(pstPppIndConfigInfo->aucIpAddr),
               pstEvent->stPdpAddr.aucIpv4Addr,
               TAF_IPV4_ADDR_LEN);

    /* DNS */
    if (VOS_TRUE == pstEvent->stDns.bitOpPrimDnsAddr)
    {
        pstPppIndConfigInfo->stPcoIpv4Item.bitOpPriDns = VOS_TRUE;

        TAF_MEM_CPY_S(pstPppIndConfigInfo->stPcoIpv4Item.aucPriDns,
               sizeof(pstPppIndConfigInfo->stPcoIpv4Item.aucPriDns),
               pstEvent->stDns.aucPrimDnsAddr,
               TAF_IPV4_ADDR_LEN);
    }

    if (VOS_TRUE == pstEvent->stDns.bitOpSecDnsAddr)
    {
        pstPppIndConfigInfo->stPcoIpv4Item.bitOpSecDns = VOS_TRUE;

        TAF_MEM_CPY_S(pstPppIndConfigInfo->stPcoIpv4Item.aucSecDns,
                       sizeof(pstPppIndConfigInfo->stPcoIpv4Item.aucSecDns),
                       pstEvent->stDns.aucSecDnsAddr,
                       TAF_IPV4_ADDR_LEN);

    }

    /* NBNS */
    if (VOS_TRUE == pstEvent->stNbns.bitOpPrimNbnsAddr)
    {
        pstPppIndConfigInfo->stPcoIpv4Item.bitOpPriNbns = VOS_TRUE;

        TAF_MEM_CPY_S(pstPppIndConfigInfo->stPcoIpv4Item.aucPriNbns,
                   sizeof(pstPppIndConfigInfo->stPcoIpv4Item.aucPriNbns),
                   pstEvent->stNbns.aucPrimNbnsAddr,
                   TAF_IPV4_ADDR_LEN);
    }

    if (VOS_TRUE == pstEvent->stNbns.bitOpSecNbnsAddr)
    {
        pstPppIndConfigInfo->stPcoIpv4Item.bitOpSecNbns = VOS_TRUE;

        TAF_MEM_CPY_S(pstPppIndConfigInfo->stPcoIpv4Item.aucSecNbns,
                   sizeof(pstPppIndConfigInfo->stPcoIpv4Item.aucSecNbns),
                   pstEvent->stNbns.aucSecNbnsAddr,
                   TAF_IPV4_ADDR_LEN);
    }

    /* GATE WAY */
    if (VOS_TRUE == pstEvent->stGateWay.bitOpGateWayAddr)
    {
        pstPppIndConfigInfo->stPcoIpv4Item.bitOpGateWay = VOS_TRUE;

        TAF_MEM_CPY_S(pstPppIndConfigInfo->stPcoIpv4Item.aucGateWay,
                   sizeof(pstPppIndConfigInfo->stPcoIpv4Item.aucGateWay),
                   pstEvent->stGateWay.aucGateWayAddr,
                   TAF_IPV4_ADDR_LEN);
    }

    /* Modified by Y00213812 for VoLTE_PhaseI , 2013-07-08, end */

}

/*****************************************************************************
     : AT_ModemPsRspPdpActEvtCnfProc
   : Modempdp
   : ucIndex --- 
             pEvent  --- 
   : 
     : 
   :
   :

       :
  1.       : 201155
           : S62952
       : 
  2.       : 20111217
           : C00173809
       : PSIPMODEMADS
  3.       : 201364
           : z00214637
       : V3R3 Share-PDP
  4.       : 20130708
           : Y00213812
       : VoLTE_PhaseI EVENT
*****************************************************************************/
VOS_VOID  AT_ModemPsRspPdpActEvtCnfProc(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
    AT_PPP_IND_CONFIG_INFO_STRU         stPppIndConfigInfo;

    /* Added by Y00213812 for VoLTE_PhaseI , 2013-07-08, begin */
    /* Modem */
    AT_RegModemPsDataFCPoint(ucIndex, pstEvent, FC_ID_MODEM);
    /* Added by Y00213812 for VoLTE_PhaseI , 2013-07-08, end */


    /*  */
    TAF_MEM_SET_S(&stPppIndConfigInfo, sizeof(stPppIndConfigInfo), 0x00, sizeof(AT_PPP_IND_CONFIG_INFO_STRU));

    /*  */
    AT_STOP_TIMER_CMD_READY(ucIndex);


    if (TAF_PDP_PPP == pstEvent->stPdpAddr.enPdpType)
    {
        At_SetMode(ucIndex, AT_DATA_MODE, AT_IP_DATA_MODE);

        /*  */
        Ppp_RegDlDataCallback(gastAtClientTab[ucIndex].usPppId);

        At_FormatResultData(ucIndex, AT_CONNECT);
    }
    else if (TAF_PDP_IPV4 == pstEvent->stPdpAddr.enPdpType)
    {
        /* IP, DNS, NBNS */
        AT_FillPppIndConfigInfoPara(&stPppIndConfigInfo, pstEvent);

        /* AUTHIPCPPPP: */
        Ppp_RcvConfigInfoInd(gastAtClientTab[ucIndex].usPppId, &stPppIndConfigInfo);

        AT_PS_ProcActSharePdpState(pstEvent, TAF_PDP_IPV4);
    }
    else
    {
        /*  */
    }

    return;
}

/*****************************************************************************
     : AT_ModemPsRspPdpDeactEvtCnfProc
   : pdpModem
   : ucIndex --- 
             pEvent  --- 
   : 
     : 
   :
   :

       :
  1.       : 201155
           : S62952
       : 
  2.       : 20111022
           : f62575
       : AT PROJECT NAS_EventReport -> AT_EventReport
  3.       : 20111217
           : C00173809
       : PSPDPADS
  4.       : 201364
           : z00214637
       : V3R3 Share-PDP

  5.       : 2013923
           : A00165503
       : UART-MODEM: UARTPPP
*****************************************************************************/
VOS_VOID  AT_ModemPsRspPdpDeactEvtCnfProc(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
)
{
    AT_UART_LINE_CTRL_STRU             *pstLineCtrl = VOS_NULL_PTR;
    VOS_UINT32                          ulModemUsrFlg;
    VOS_UINT32                          ulATHCmdFlg;
    VOS_UINT32                          ulResult;
    VOS_UINT16                          usLength;

    pstLineCtrl     = AT_GetUartLineCtrlInfo();
    ulModemUsrFlg   = AT_CheckModemUser(ucIndex);
    usLength        = 0;
    ulResult        = AT_FAILURE;
    ulATHCmdFlg     = (AT_CMD_H_PS_SET == gastAtClientTab[ucIndex].CmdCurrentOpt) ?
                      VOS_TRUE : VOS_FALSE;

    if ( (AT_MODEM_USER != gastAtClientTab[ucIndex].UserType)
      && (AT_HSUART_USER != gastAtClientTab[ucIndex].UserType) )
    {
        return;
    }

    if (AT_PPP_DATA_MODE == gastAtClientTab[ucIndex].DataMode)
    {
        /* PPP & HDLC */
        PPP_RcvAtCtrlOperEvent(gastAtClientTab[ucIndex].usPppId, PPP_AT_CTRL_REL_PPP_REQ);
        PPP_RcvAtCtrlOperEvent(gastAtClientTab[ucIndex].usPppId, PPP_AT_CTRL_HDLC_DISABLE);

        AT_PS_ProcDeactSharePdpState(pstEvent, TAF_PDP_IPV4);
    }
    else if (AT_IP_DATA_MODE == gastAtClientTab[ucIndex].DataMode)
    {
        /* PPP & HDLC */
        PPP_RcvAtCtrlOperEvent(gastAtClientTab[ucIndex].usPppId, PPP_AT_CTRL_REL_PPP_RAW_REQ);

        /* PPPHDLC */
        PPP_RcvAtCtrlOperEvent(gastAtClientTab[ucIndex].usPppId, PPP_AT_CTRL_HDLC_DISABLE);
    }
    else
    {
        /*  */
        AT_WARN_LOG("TAF_PS_EVT_PDP_DEACTIVE_CNF OTHER MODE");
    }

    /* Added by Y00213812 for VoLTE_PhaseI , 2013-07-08, begin */
    /* Modem */
    AT_DeRegModemPsDataFCPoint(ucIndex, pstEvent->ucRabId);
    /* Added by Y00213812 for VoLTE_PhaseI , 2013-07-08, end */

    /*  */
    At_SetMode(ucIndex, AT_CMD_MODE, AT_NORMAL_MODE);

    /* Linux:
       PDPTAF_PS_EVT_PDP_DEACTIVE_CNF
       Linux"NO CARRIER" */
    if ((VOS_OK == DRV_GET_LINUXSYSTYPE()) && (VOS_TRUE == ulModemUsrFlg))
    {
        /* At_FormatResultData"NO CARRIER"
           DCD"NO CARRIER"DCD
           
        */
        AT_STOP_TIMER_CMD_READY(ucIndex);
        AT_CtrlDCD(ucIndex, AT_IO_LEVEL_LOW);
        return;
    }

    if (VOS_TRUE == ulATHCmdFlg)
    {
        ulResult = AT_OK;
    }
    else
    {
        ulResult = AT_NO_CARRIER;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);
    gstAtSendData.usBufLen = usLength;
    At_FormatResultData(ucIndex,ulResult);

    /* ATHPPP, DCDCONNECT ON, DCD */
    if ( (AT_OK == ulResult)
      && (AT_UART_DCD_MODE_CONNECT_ON == pstLineCtrl->enDcdMode) )
    {
        AT_CtrlDCD(ucIndex, AT_IO_LEVEL_LOW);
    }

    return;
}

/*****************************************************************************
     : AT_MODEM_ProcCallEndedEvent
   : PS_CALL_END_CNF
   : ucIndex  - 
             pstEvent - ID_EVT_TAF_PS_CALL_END_CNF
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 2013923
           : A00165503
       : 
*****************************************************************************/
VOS_VOID AT_MODEM_ProcCallEndCnfEvent(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_END_CNF_STRU           *pstEvent
)
{
    AT_UART_LINE_CTRL_STRU             *pstLineCtrl = VOS_NULL_PTR;
    AT_DCE_MSC_STRU                     stDecMsc;
    VOS_UINT32                          ulModemUsrFlg;
    VOS_UINT32                          ulATHCmdFlg;
    VOS_UINT32                          ulResult;
    VOS_UINT16                          usLength;

    pstLineCtrl     = AT_GetUartLineCtrlInfo();
    ulModemUsrFlg   = AT_CheckModemUser(ucIndex);
    ulResult        = AT_FAILURE;
    usLength        = 0;
    ulATHCmdFlg     = (AT_CMD_H_PS_SET == AT_PS_GET_CURR_CMD_OPT(ucIndex)) ?
                      VOS_TRUE : VOS_FALSE;

    TAF_MEM_SET_S(&stDecMsc, sizeof(stDecMsc), 0x00, sizeof(AT_DCE_MSC_STRU));

    /*  */
    if ( (AT_CMD_PS_DATA_CALL_END_SET != AT_PS_GET_CURR_CMD_OPT(ucIndex))
      && (AT_CMD_H_PS_SET != AT_PS_GET_CURR_CMD_OPT(ucIndex)) )
    {
        return;
    }

    /* PS,  */
    if (TAF_ERR_NO_ERROR == pstEvent->enCause)
    {
        return;
    }

    /* PPP & HDLC */
    if (AT_PPP_DATA_MODE == AT_PS_GET_CURR_DATA_MODE(ucIndex))
    {
        PPP_RcvAtCtrlOperEvent(AT_PS_GET_PPPID(ucIndex), PPP_AT_CTRL_REL_PPP_REQ);
        PPP_RcvAtCtrlOperEvent(AT_PS_GET_PPPID(ucIndex), PPP_AT_CTRL_HDLC_DISABLE);
    }
    else if (AT_IP_DATA_MODE == AT_PS_GET_CURR_DATA_MODE(ucIndex))
    {
        PPP_RcvAtCtrlOperEvent(AT_PS_GET_PPPID(ucIndex), PPP_AT_CTRL_REL_PPP_RAW_REQ);
        PPP_RcvAtCtrlOperEvent(AT_PS_GET_PPPID(ucIndex), PPP_AT_CTRL_HDLC_DISABLE);
    }
    else
    {
        ;
    }

    /*  */
    At_SetMode(ucIndex, AT_CMD_MODE, AT_NORMAL_MODE);

    /* Linux:
       PDPTAF_PS_EVT_PDP_DEACTIVE_CNF
       Linux"NO CARRIER" */
    if ((VOS_OK == DRV_GET_LINUXSYSTYPE()) && (VOS_TRUE == ulModemUsrFlg))
    {
        /* At_FormatResultData"NO CARRIER"
           DCD"NO CARRIER"DCD
           
        */
        AT_STOP_TIMER_CMD_READY(ucIndex);
        AT_CtrlDCD(ucIndex, AT_IO_LEVEL_LOW);
        return;
    }

    if (VOS_TRUE == ulATHCmdFlg)
    {
        ulResult = AT_OK;
    }
    else
    {
        ulResult = AT_NO_CARRIER;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);
    gstAtSendData.usBufLen = usLength;
    At_FormatResultData(ucIndex, ulResult);

    /* ATHPPP, DCDCONNECT ON, DCD */
    if ( (AT_OK == ulResult)
      && (AT_UART_DCD_MODE_CONNECT_ON == pstLineCtrl->enDcdMode) )
    {
        AT_CtrlDCD(ucIndex, AT_IO_LEVEL_LOW);
    }

    return;
}

/*****************************************************************************
     : AT_AnswerPdpActInd
   : pdp
   : ucIndex --- 
             pstEvent  --- 
   : 
     : 
   :
   :

       :
  1.       : 20130605
           : f00179208
       : 
  2.       : 20130708
           : Y00213812
       : VoLTE_PhaseI EVENT
  3.       : 20150723
           : wx270776
       : OM
*****************************************************************************/
VOS_VOID  AT_AnswerPdpActInd(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
    VOS_UINT16                          usPppId;
    VOS_UINT32                          ulRslt;

    usPppId     = 0;

    if (TAF_PDP_PPP == pstEvent->stPdpAddr.enPdpType)
    {
        if (VOS_OK != Ppp_CreateRawDataPppReq(&usPppId))
        {
            /* Deleted by wx270776 for OM, 2015-7-23, begin */
            /* Deleted by wx270776 for OM, 2015-6-29, end */
            ulRslt = AT_ERROR;
        }
        else
        {
            /* PPP idIndex */
            gastAtPppIndexTab[usPppId]          = ucIndex;

            /* PPP id */
            gastAtClientTab[ucIndex].usPppId    = usPppId;


            /* Added by Y00213812 for VoLTE_PhaseI , 2013-07-08, begin */
            /* Modem */
            AT_RegModemPsDataFCPoint(ucIndex, pstEvent, FC_ID_MODEM);
            /* Added by Y00213812 for VoLTE_PhaseI , 2013-07-08, end */

            /*  */
            At_SetMode(ucIndex, AT_DATA_MODE, AT_IP_DATA_MODE);

            /*  */
            Ppp_RegDlDataCallback(usPppId);

            ulRslt = AT_CONNECT;
        }

        AT_STOP_TIMER_CMD_READY(ucIndex);
        At_FormatResultData(ucIndex, ulRslt);
    }
    else
    {
        /* ....*/
        AT_STOP_TIMER_CMD_READY(ucIndex);
        At_FormatResultData(ucIndex, AT_CONNECT);
    }

    return;
}

/*****************************************************************************
 Prototype      : At_RcvTeConfigInfoReq
 Description    : ATTE
 Input          : usPppId --- PPP ID
                  pPppReqConfigInfo  --- TE
 Output         :
 Return Value   : AT_XXX  --- ATC
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function

  2.       : 20111212
           : l00171473
       : DTS2011112306269,PDPATTIMER

*****************************************************************************/
TAF_UINT32 At_RcvTeConfigInfoReq(
    TAF_UINT16                          usPppId,
    AT_PPP_REQ_CONFIG_INFO_STRU        *pstPppReqConfigInfo
)
{
    if (AT_MAX_CLIENT_NUM <= usPppId)
    {
        AT_WARN_LOG("At_RcvTeConfigInfoReq usPppId Wrong");
        return AT_FAILURE;
    }

    if (TAF_NULL_PTR == pstPppReqConfigInfo)
    {
        AT_WARN_LOG("At_RcvTeConfigInfoReq pPppReqConfigInfo NULL");
        return AT_FAILURE;
    }

    if (AT_CMD_D_PPP_CALL_SET != gastAtClientTab[gastAtPppIndexTab[usPppId]].CmdCurrentOpt)
    {
        AT_WARN_LOG("At_RcvTeConfigInfoReq NOT AT_CMD_D_PPP_CALL_SET");
        return AT_FAILURE;
    }

    if ( VOS_OK == TAF_PS_PppDialOrig(WUEPS_PID_AT,
                                      AT_PS_BuildExClientId(gastAtClientTab[gastAtPppIndexTab[usPppId]].usClientId),
                                      0,
                                      gastAtClientTab[gastAtPppIndexTab[usPppId]].ucCid,
                                      (TAF_PPP_REQ_CONFIG_INFO_STRU *)pstPppReqConfigInfo) )
    {
        /*  */
        /* Modified by L00171473 for DTS2011112306269,PDPAT, 2011-12-09, Begin */
        if (AT_SUCCESS != At_StartTimer(AT_ACT_PDP_TIME, gastAtPppIndexTab[usPppId]))
        {
            AT_ERR_LOG("At_RcvTeConfigInfoReq:ERROR:Start Timer");
            return AT_FAILURE;
        }

        /*  */
        gastAtClientTab[gastAtPppIndexTab[usPppId]].CmdCurrentOpt = AT_CMD_PPP_ORG_SET;

        return AT_SUCCESS;
    }
    else
    {
        return AT_FAILURE;
    }
}

/*****************************************************************************
     : At_RcvPppReleaseInd
   : ATPPP
   : TAF_UINT16                          usPppId  PPP ID
   : 
     : TAF_UINT32
             0 --- 
             1 --- 
   :
   :

       :
  1.       : 20111022
           : f62575
       : 
*****************************************************************************/
TAF_UINT32 At_RcvPppReleaseInd(
    TAF_UINT16                          usPppId
)
{
    TAF_UINT8                           aucEventInfo[4];
    AT_PPP_RELEASE_IND_MSG_STRU        *pMsg;
    VOS_UINT32                          ulLength;

    if (AT_MAX_CLIENT_NUM <= usPppId)
    {
        AT_WARN_LOG("At_RcvPppReleaseInd usPppId Wrong");
        return AT_FAILURE;
    }

    /* EVENT- At_RcvPppReleaseInd:usPppId / gastAtPppIndexTab[usPppId] */
    aucEventInfo[0] = (TAF_UINT8)(usPppId >> 8);
    aucEventInfo[1] = (TAF_UINT8)usPppId;
    aucEventInfo[2] = gastAtPppIndexTab[usPppId];
    AT_EventReport(WUEPS_PID_AT, NAS_OM_EVENT_DTE_RELEASE_PPP,
                   aucEventInfo, (VOS_UINT32)sizeof(aucEventInfo));

    /* ATAT_PPP_RELEASE_IND_MSG */
    ulLength       = sizeof(AT_PPP_RELEASE_IND_MSG_STRU) - VOS_MSG_HEAD_LENGTH;
    pMsg = (AT_PPP_RELEASE_IND_MSG_STRU *)PS_ALLOC_MSG(PS_PID_APP_PPP, ulLength);
    if (VOS_NULL_PTR == pMsg)
    {
        /* --- */
        AT_ERR_LOG( "At_RcvPppReleaseInd:ERROR:Allocates a message packet for AT_PPP_RELEASE_IND_MSG_STRU msg FAIL!" );
        return AT_FAILURE;
    }
    /*  */
    pMsg->MsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pMsg->MsgHeader.ulSenderPid     = PS_PID_APP_PPP;
    pMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pMsg->MsgHeader.ulReceiverPid   = WUEPS_PID_AT;
    pMsg->MsgHeader.ulLength        = ulLength;

    pMsg->MsgHeader.ulMsgName       = AT_PPP_RELEASE_IND_MSG;
    /*  */
    pMsg->ucIndex                   = gastAtPppIndexTab[usPppId];

    /*  */
    if (VOS_OK != PS_SEND_MSG(PS_PID_APP_PPP, pMsg))
    {
        /* --- */
        AT_WARN_LOG( "At_RcvPppReleaseInd:WARNING:SEND AT_PPP_RELEASE_IND_MSG msg FAIL!" );
        return AT_FAILURE;
    }
    else
    {
        /* --- */
        AT_WARN_LOG( "At_RcvPppReleaseInd:NORMAL:SEND AT_PPP_RELEASE_IND_MSG Msg" );
        return AT_SUCCESS;
    }
}

/*****************************************************************************
 Prototype      : At_PppReleaseIndProc
 Description    : ATPPP
 Input          : ucIndex
 Output         : ---
 Return Value   : VOS_VOID
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2009-04-19
    Author      : L47619
    Modification: Created function

  2.       : 20111212
           : l00171473
       : DTS2011112306269,PDPAT

  3.       : 2014114
           : A00165503
       : DTS2013120310013: PPP
*****************************************************************************/
TAF_VOID At_PppReleaseIndProc(
    TAF_UINT8                           ucIndex
)
{
    if (AT_MAX_CLIENT_NUM <= ucIndex)
    {
        AT_WARN_LOG("At_PppReleaseIndProc:ERROR:ucIndex is abnormal!");
        return;
    }

    if (AT_CMD_WAIT_PPP_PROTOCOL_REL_SET == gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        /* AT */
        At_SetMode(ucIndex, AT_CMD_MODE, AT_NORMAL_MODE);

        /**/
        AT_STOP_TIMER_CMD_READY(ucIndex);

        /*NO CARRIER*/
        gstAtSendData.usBufLen = 0;
        At_FormatResultData(ucIndex, AT_NO_CARRIER);

        return;
    }

    if (AT_CMD_PS_DATA_CALL_END_SET == gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return;
    }

    if ( VOS_OK == TAF_PS_CallEnd(WUEPS_PID_AT,
                                  AT_PS_BuildExClientId(gastAtClientTab[ucIndex].usClientId),
                                  0,
                                  gastAtClientTab[ucIndex].ucCid) )
    {
        /*  */
        /* Modified by L00171473 for DTS2011112306269,PDPAT, 2011-12-09, Begin */
        if (AT_SUCCESS != At_StartTimer(AT_DETACT_PDP_TIME, ucIndex))
        {
            AT_ERR_LOG("At_PppReleaseIndProc:ERROR:Start Timer");
            return;
        }

        /*  */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_PS_DATA_CALL_END_SET;
    }

    return;
}

/*****************************************************************************
 Prototype      : At_PsRab2PppId
 Description    : Rab IDPPP ID
 Input          : RabId     --- RAB ID
 Output         : pusPppId  --- PPP ID
 Return Value   : AT_SUCCESS --- 
                  AT_FAILURE --- 
 Calls          : ---
 Called By      : ---

 History        :
  1.Date        : 2008-03-05
    Author      : g45205
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_PsRab2PppId(
    TAF_UINT8                           ucExRabId,
    TAF_UINT16                         *pusPppId
)
{
    TAF_UINT16                          usPppId;
    TAF_UINT8                           ucIndex;

    if (VOS_NULL_PTR == pusPppId)
    {
        AT_WARN_LOG("At_PsRab2PppId, pusPppId NULL");
        return TAF_FAILURE;
    }

    /* PPP ID */
    for (usPppId = 1; usPppId <= PPP_MAX_ID_NUM; usPppId++)
    {
        ucIndex = gastAtPppIndexTab[usPppId];

        if (AT_MAX_CLIENT_NUM <= ucIndex)
        {
            continue;
        }

        if ( AT_CLIENT_USED != gastAtClientTab[ucIndex].ucUsed )
        {
            continue;
        }

        if (AT_DATA_MODE != gastAtClientTab[ucIndex].Mode)
        {
            continue;
        }

        if ( (AT_PPP_DATA_MODE != gastAtClientTab[ucIndex].DataMode)
          && (AT_IP_DATA_MODE != gastAtClientTab[ucIndex].DataMode) )
        {
            continue;
        }

        if (gastAtClientTab[ucIndex].ucExPsRabId == ucExRabId)
        {
            *pusPppId = usPppId;    /*  */
            return TAF_SUCCESS;
        }

    }

    AT_LOG1("AT, At_PsRab2PppId, WARNING, Get PppId from Rab <1> Fail", ucExRabId);

    return TAF_FAILURE;
} /* At_PsRab2PppId */


/*****************************************************************************
 Prototype      : At_PppId2PsRab
 Description    : PPP IDRab ID
 Input          : usPppId   ---  PPP ID
 Output         : pucRabId  ---  RAB ID
 Return Value   : AT_SUCCESS --- 
                  AT_FAILURE --- 
 Calls          : ---
 Called By      : ---

 History        :
  1.Date        : 2008-03-05
    Author      : g45205
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_PppId2PsRab(
    TAF_UINT16                          usPppId,
    TAF_UINT8                          *pucExRabId
)
{
    TAF_UINT8                           ucIndex;


    if ((usPppId < 1) || (usPppId > PPP_MAX_ID_NUM))
    {
        TAF_LOG1(WUEPS_PID_AT, 0, PS_LOG_LEVEL_WARNING,
            "AT, At_PppId2PsRab, WARNING, PppId <1> Wrong", usPppId);
        return TAF_FAILURE;
    }

    if (TAF_NULL_PTR == pucExRabId)
    {
        AT_WARN_LOG("AT, At_PppId2PsRab, WARNING, pucRabId NULL");
        return TAF_FAILURE;
    }

    ucIndex = gastAtPppIndexTab[usPppId];

    if (AT_MAX_CLIENT_NUM <= ucIndex)
    {
        AT_LOG1("AT, At_PppId2PsRab, WARNING, index <1> Wrong", ucIndex);
        return TAF_FAILURE;
    }

    if (AT_DATA_MODE != gastAtClientTab[ucIndex].Mode)
    {
        AT_LOG1("AT, At_PppId2PsRab, WARNING, Mode <1> Wrong", gastAtClientTab[ucIndex].Mode);
        return TAF_FAILURE;
    }

    if ( (AT_PPP_DATA_MODE != gastAtClientTab[ucIndex].DataMode)
      && (AT_IP_DATA_MODE  != gastAtClientTab[ucIndex].DataMode) )
    {
        AT_LOG1("AT, At_PppId2PsRab, WARNING, DataMode <1> Wrong", gastAtClientTab[ucIndex].DataMode);
        return TAF_FAILURE;
    }

    *pucExRabId = gastAtClientTab[ucIndex].ucExPsRabId;

    return TAF_SUCCESS;
} /* At_PppId2PsRab */


/*****************************************************************************
     : AT_RegModemPsDataFCPoint
   : ModemPsData
   : TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 20111217
           : c00173809
       : 
  2.       : 2012224
           : L47619
       : V7R1C50 IPC:MODEM
  3.       : 2012522
           : f00179208
       : DTS2012052205142, VIDEO PHONE
  4.       : 20121227
           : l60609
       : DSDA Phase II
  5.       : 20130417
           : f00179208
       : C
  6.       : 20130708
           : Y00213812
       : VoLTE_PhaseI EVENT
  7.       : 2013923
           : A00165503
       : UART-MODEM: 

*****************************************************************************/
VOS_UINT32 AT_RegModemPsDataFCPoint(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent,
    FC_ID_ENUM_UINT8                    enFcId
)
{
    FC_REG_POINT_STRU                   stRegFcPoint;
    VOS_UINT32                          ulRet;
    FC_PRI_ENUM_UINT8                   enFcPri;
    /* Modified by l60609 for DSDA Phase II, 2012-12-21, Begin */
    MODEM_ID_ENUM_UINT16                enModemId;
    AT_UART_CTX_STRU                   *pstUartCtx = VOS_NULL_PTR;

    pstUartCtx = AT_GetUartCtxAddr();

    /* UART */
    if ( (VOS_TRUE == AT_CheckHsUartUser(ucIndex))
      && (AT_UART_FC_DTE_BY_DCE_NONE == pstUartCtx->stFlowCtrl.enDteByDce) )
    {
        return VOS_ERR;
    }

    enModemId = MODEM_ID_0;

    TAF_MEM_SET_S(&stRegFcPoint, sizeof(stRegFcPoint), 0x00, sizeof(FC_REG_POINT_STRU));

    ulRet = AT_GetModemIdFromClient((AT_CLIENT_TAB_INDEX_UINT8)pstEvent->stCtrl.usClientId, &enModemId);

    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_RegModemPsDataFCPoint: Get modem id fail.");
        return VOS_ERR;
    }

    /* RABID */
    FC_ChannelMapCreate(enFcId, pstEvent->ucRabId, enModemId);

    stRegFcPoint.enFcId             = enFcId;

    /* RAB QoS, */
    /*  FC_PRI_3        
        FC_PRI_4        NONGBR
        FC_PRI_5        GBR */
    if (TAF_USED == pstEvent->bitOpUmtsQos)
    {
        enFcPri = AT_GetFCPriFromQos(&pstEvent->stUmtsQos);
    }
    else
    {
        enFcPri = FC_PRI_FOR_PDN_NONGBR;
    }
    stRegFcPoint.enFcPri            = enFcPri;
    stRegFcPoint.enPolicyId         = FC_POLICY_ID_MEM;
    stRegFcPoint.pClrFunc           = AT_MODEM_StopFlowCtrl;
    stRegFcPoint.pSetFunc            = AT_MODEM_StartFlowCtrl;

    stRegFcPoint.ulParam1           = (VOS_UINT32)g_alAtUdiHandle[ucIndex];
    stRegFcPoint.enModemId          = enModemId;
    /* Modified by l60609 for DSDA Phase II, 2012-12-21, End */
    stRegFcPoint.ulParam2           = enFcId;
    stRegFcPoint.pRstFunc           = AT_ResetFlowCtl;

    /* ,MEM,CPU,CDSGPRS */
    ulRet = FC_RegPoint(&stRegFcPoint);
    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_RegModemFCPoint: ERROR: FC RegPoint MEM Failed.");
        return VOS_ERR;
    }

    stRegFcPoint.enPolicyId         = FC_POLICY_ID_CPU_A;
    ulRet = FC_RegPoint(&stRegFcPoint);
    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_RegModemFCPoint: ERROR: FC RegPoint A CPU Failed.");
        return VOS_ERR;
    }

    stRegFcPoint.enPolicyId         = FC_POLICY_ID_CDS;
    ulRet = FC_RegPoint(&stRegFcPoint);
    if (VOS_OK != ulRet)
    {
        return VOS_ERR;
    }

    stRegFcPoint.enPolicyId         = FC_POLICY_ID_GPRS;
    ulRet = FC_RegPoint(&stRegFcPoint);
    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_RegModemFCPoint: ERROR: FC RegPoint GPRS Failed.");
        return VOS_ERR;
    }

    stRegFcPoint.enPolicyId         = FC_POLICY_ID_CDMA;
    ulRet = FC_RegPoint(&stRegFcPoint);
    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_RegModemFCPoint: ERROR: reg CDMA point Failed.");
        return VOS_ERR;
    }

    /* FCIDFC Pri */
    g_stFcIdMaptoFcPri[FC_ID_MODEM].ulUsed      = VOS_TRUE;
    g_stFcIdMaptoFcPri[FC_ID_MODEM].enFcPri     = enFcPri;
    /* RABIDRABID */
    g_stFcIdMaptoFcPri[FC_ID_MODEM].ulRabIdMask |= ((VOS_UINT32)1 << (pstEvent->ucRabId));
    g_stFcIdMaptoFcPri[FC_ID_MODEM].enModemId   = enModemId;

    /*  */
    AT_MNTN_TraceRegFcPoint(ucIndex, AT_FC_POINT_TYPE_MODEM_PS);

    return VOS_OK;
}

/*****************************************************************************
     : AT_DeRegModemPsDataFCPoint
   : ModemPsData
   : VOS_UINT8                           ucRabId
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 20111217
           : c00173809
       : 
  2.       : 2012224
           : L47619
       : V7R1C50 IPC:NDIS
  3.       : 2012522
           : f00179208
       : DTS2012052205142, VIDEO PHONE
  4.       : 20121227
           : l60609
       : DSDA Phase II
  5.       : 20130417
           : f00179208
       : C
  6.       : 20130522
           : f00179208
       : V3R3 PPP PROJECT
  7.       : 2013923
           : A00165503
       : UART-MODEM: 

*****************************************************************************/
VOS_UINT32 AT_DeRegModemPsDataFCPoint(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                           ucRabId
)
{
    VOS_UINT32                          ulRet;
    /* Modified by l60609 for DSDA Phase II, 2012-12-28, Begin */
    MODEM_ID_ENUM_UINT16                enModemId;
    AT_UART_CTX_STRU                   *pstUartCtx = VOS_NULL_PTR;

    pstUartCtx = AT_GetUartCtxAddr();

    /* UART */
    if ( (VOS_TRUE == AT_CheckHsUartUser(ucIndex))
        && (AT_UART_FC_DTE_BY_DCE_NONE == pstUartCtx->stFlowCtrl.enDteByDce) )
    {
        return VOS_ERR;
    }

    enModemId = MODEM_ID_0;

    ulRet = AT_GetModemIdFromClient(ucIndex, &enModemId);
    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_DeRegModemPsDataFCPoint: Get modem id fail.");
        return VOS_ERR;
    }
    /* Modified by l60609 for DSDA Phase II, 2012-12-21, Begin */
    /*  */
    FC_ChannelMapDelete(ucRabId, enModemId);

    ulRet = FC_DeRegPoint(FC_ID_MODEM, enModemId);
    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_DeRegModemPsDataFCPoint: ERROR: FC DeRegPoint Failed.");
        return VOS_ERR;
    }
    /* Modified by l60609 for DSDA Phase II, 2012-12-21, End */

    /* FCIDFC Pri */
    g_stFcIdMaptoFcPri[FC_ID_MODEM].ulUsed      = VOS_FALSE;
    g_stFcIdMaptoFcPri[FC_ID_MODEM].enFcPri     = FC_PRI_BUTT;
    /* RABIDRABID */
    g_stFcIdMaptoFcPri[FC_ID_MODEM].ulRabIdMask &= ~((VOS_UINT32)1 << ucRabId);
    g_stFcIdMaptoFcPri[FC_ID_MODEM].enModemId   = MODEM_ID_BUTT;

    /*  */
    AT_MNTN_TraceDeregFcPoint(ucIndex, AT_FC_POINT_TYPE_MODEM_PS);

    return VOS_OK;
}
/* Modified by s62952 for BalongV300R002 Build 2012-02-28, end */

/*****************************************************************************
     : AT_ChangeFCPoint
   : 
   : TAF_CTRL_STRU                       *pstCtrl,
             FC_PRI_ENUM_UINT8                    enFCPri,
             FC_ID_ENUM_UINT8                     enFcId
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 20111217
           : c00173809
       : 
  2.       : 20121222
           : l00227485
       : DSDA PhaseII
*****************************************************************************/
VOS_UINT32 AT_ChangeFCPoint(
    TAF_CTRL_STRU                       *pstCtrl,
    FC_PRI_ENUM_UINT8                    enFCPri,
    FC_ID_ENUM_UINT8                     enFcId
)
{
    VOS_UINT32                          ulRet;
    MODEM_ID_ENUM_UINT16                enModemId;

    enModemId = MODEM_ID_0;

    ulRet = AT_GetModemIdFromClient((AT_CLIENT_TAB_INDEX_UINT8)pstCtrl->usClientId, &enModemId);

    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_ChangeFCPoint: Get modem id fail.");
        return VOS_ERR;
    }

    if (FC_ID_BUTT != enFcId)
    {
        ulRet = FC_ChangePoint(enFcId, FC_POLICY_ID_MEM, enFCPri, enModemId);
        if (VOS_OK != ulRet)
        {
            AT_ERR_LOG("AT_ChangeFCPoint: ERROR: Change FC Point Failed.");
        }

        ulRet = FC_ChangePoint(enFcId, FC_POLICY_ID_CPU_A , enFCPri, enModemId);
        if (VOS_OK != ulRet)
        {
            AT_ERR_LOG("AT_ChangeFCPoint: ERROR: Change FC Point Failed.");
        }

        ulRet = FC_ChangePoint(enFcId, FC_POLICY_ID_CDS, enFCPri, enModemId);
        if (VOS_OK != ulRet)
        {
            AT_ERR_LOG("AT_ChangeFCPoint: ERROR: Change FC Point Failed.");
        }

        ulRet = FC_ChangePoint(enFcId, FC_POLICY_ID_GPRS, enFCPri, enModemId);
        if (VOS_OK != ulRet)
        {
            AT_ERR_LOG("AT_ChangeFCPoint: ERROR: Change FC Point Failed.");
        }
    }

    return VOS_OK;
}

/*****************************************************************************
     : AT_EnableHsicFlowCtl
   : Hsic
   : VOS_UINT32                          ulUdiHdl,
             VOS_UINT32                          ulParam2
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 2012217
           : L47619
       : 
*****************************************************************************/
VOS_UINT32 AT_EnableHsicFlowCtl(
    VOS_UINT32                          ulUdiHdl,
    VOS_UINT32                          ulParam2
)
{
    VOS_UINT32  ulEnbflg = ACM_IOCTL_FLOW_CONTROL_ENABLE;

    if (0 != mdrv_udi_ioctl ((VOS_INT)ulUdiHdl, ACM_IOCTL_FLOW_CONTROL, (VOS_VOID*)(&ulEnbflg)))
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
     : AT_DisableHsicFlowCtl
   : HSIC
   : VOS_UINT32                          ulUdiHdl,
             VOS_UINT32                          ulParam2
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 2012217
           : L47619
       : 
*****************************************************************************/
VOS_UINT32 AT_DisableHsicFlowCtl(
    VOS_UINT32                          ulUdiHdl,
    VOS_UINT32                          ulParam2
)
{
    VOS_UINT32  ulEnbflg = ACM_IOCTL_FLOW_CONTROL_DISABLE;

    if (0 != mdrv_udi_ioctl ((VOS_INT)ulUdiHdl, ACM_IOCTL_FLOW_CONTROL, (VOS_VOID*)(&ulEnbflg)))
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
     : AT_RegHsicFCPoint
   : HSIC
   : TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU   *pstEvent,
             FC_ID_ENUM_UINT8                     enFcId
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 2012217
           : L47619
       : 
  2.       : 20121227
           : L60609
       : DSDA Phase II
  3.       : 20130415
           : f00179208
       : C
  4.       : 20130708
           : Y00213812
       : VoLTE_PhaseI EVENT
*****************************************************************************/
VOS_UINT32 AT_RegHsicFCPoint(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
    FC_REG_POINT_STRU                   stRegFcPoint;
    VOS_UINT32                          ulRet;
    FC_PRI_ENUM_UINT8                   enFCPri;
    UDI_DEVICE_ID_E                     enDataChannelId;
    FC_ID_ENUM_UINT8                    enFcId;
    /* Modified by l60609 for DSDA Phase II, 2012-12-21, Begin */
    MODEM_ID_ENUM_UINT16                enModemId;
    AT_MODEM_PS_CTX_STRU               *pstPsModemCtx = VOS_NULL_PTR;

    enModemId = MODEM_ID_0;

    TAF_MEM_SET_S(&stRegFcPoint, sizeof(stRegFcPoint), 0x00, sizeof(FC_REG_POINT_STRU));

    ulRet = AT_GetModemIdFromClient((AT_CLIENT_TAB_INDEX_UINT8)pstEvent->stCtrl.usClientId, &enModemId);
    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_RegHsicFCPoint: Get modem id fail.");
        return VOS_ERR;
    }

    pstPsModemCtx = AT_GetModemPsCtxAddrFromModemId(enModemId);

    /* ID */
    if ((VOS_TRUE == pstPsModemCtx->astChannelCfg[pstEvent->ucCid].ulUsed)
      &&(AT_PS_INVALID_RMNET_ID != pstPsModemCtx->astChannelCfg[pstEvent->ucCid].ulRmNetId))
    {
        enDataChannelId = (UDI_DEVICE_ID_E)pstPsModemCtx->astChannelCfg[pstEvent->ucCid].ulRmNetId;
    }
    else
    {
        AT_ERR_LOG("AT_RegHsicFCPoint: ERROR: data channel id is abnormal.");
        return VOS_ERR;
    }

    /* Modified by L47619 for C52 HSIC ACM->NCM Project, 2012/09/06, begin */
    switch ( enDataChannelId )
    {
        case UDI_ACM_HSIC_ACM1_ID:
        case UDI_NCM_HSIC_NCM0_ID:
            enFcId = FC_ID_DIPC_1;
            break;
        case UDI_ACM_HSIC_ACM3_ID:
        case UDI_NCM_HSIC_NCM1_ID:
            enFcId = FC_ID_DIPC_2;
            break;
        case UDI_ACM_HSIC_ACM5_ID:
        case UDI_NCM_HSIC_NCM2_ID:
            enFcId = FC_ID_DIPC_3;
            break;
        default:
            AT_WARN_LOG("AT_RegHsicFCPoint: WARNING: data channel id is abnormal.");
            return VOS_ERR;
    }
    /* Modified by L47619 for C52 HSIC ACM->NCM Project, 2012/09/06, end */

    /* RABID */
    FC_ChannelMapCreate(enFcId, pstEvent->ucRabId, enModemId);

    stRegFcPoint.enFcId             = enFcId;
    /* RAB QoS, */
    /*  FC_PRI_3        
        FC_PRI_4        NONGBR
        FC_PRI_5        GBR */
    if (TAF_USED == pstEvent->bitOpUmtsQos)
    {
        enFCPri = AT_GetFCPriFromQos(&pstEvent->stUmtsQos);
    }
    else
    {
        enFCPri = FC_PRI_FOR_PDN_NONGBR;
    }
    stRegFcPoint.enFcPri            = enFCPri;
    stRegFcPoint.enPolicyId         = FC_POLICY_ID_MEM;
    stRegFcPoint.pClrFunc           = AT_DisableHsicFlowCtl;
    stRegFcPoint.pSetFunc           = AT_EnableHsicFlowCtl;
    stRegFcPoint.ulParam1           = (VOS_UINT32)DIPC_GetDevHandleByRabId(pstEvent->ucRabId);
    stRegFcPoint.enModemId          = enModemId;
    /* Modified by l60609 for DSDA Phase II, 2012-12-21, End */
    stRegFcPoint.ulParam2           = enFcId;
    stRegFcPoint.pRstFunc           = AT_ResetFlowCtl;

    /* ,MEM,CPU,CDSGPRS */
    ulRet = FC_RegPoint(&stRegFcPoint);
    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_RegHsicFCPoint: ERROR: reg mem point Failed.");
        return VOS_ERR;
    }

    stRegFcPoint.enPolicyId         = FC_POLICY_ID_CPU_A;
    ulRet = FC_RegPoint(&stRegFcPoint);
    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_RegHsicFCPoint: ERROR: reg a cpu point Failed.");
        return VOS_ERR;
    }

    stRegFcPoint.enPolicyId         = FC_POLICY_ID_CDS;
    ulRet = FC_RegPoint(&stRegFcPoint);
    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_RegHsicFCPoint: ERROR: reg cds point Failed.");
        return VOS_ERR;
    }

    stRegFcPoint.enPolicyId         = FC_POLICY_ID_GPRS;
    ulRet = FC_RegPoint(&stRegFcPoint);
    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_RegHsicFCPoint: ERROR: reg gprs point Failed.");
        return VOS_ERR;
    }

    /* FCIDFC Pri */
    g_stFcIdMaptoFcPri[enFcId].ulUsed       = VOS_TRUE;
    g_stFcIdMaptoFcPri[enFcId].enFcPri      = enFCPri;
    /* RABIDRABID */
    g_stFcIdMaptoFcPri[enFcId].ulRabIdMask  |= ((VOS_UINT32)1 << (pstEvent->ucRabId));
    g_stFcIdMaptoFcPri[enFcId].enModemId    = enModemId;

    /*  */
    AT_MNTN_TraceRegFcPoint((VOS_UINT8)pstEvent->stCtrl.usClientId, AT_FC_POINT_TYPE_HSIC);

    return VOS_OK;
}

/*****************************************************************************
     : AT_DeRegHsicFCPoint
   : HSIC
   : MN_CLIENT_ID_T                      usClientID,
             VOS_UINT8                           ucRabId
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 2012217
           : L47619
       : 
  2.       : 20121227
           : L60609
       : DSDA Phase II
  3.       : 20130415
           : f00179208
       : C
*****************************************************************************/
VOS_UINT32 AT_DeRegHsicFCPoint(
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
)
{
    FC_ID_ENUM_UINT8                    enFcId;
    VOS_UINT32                          ulRet;
    UDI_DEVICE_ID_E                     enDataChannelId;
    /* Modified by l60609 for DSDA Phase II, 2012-12-21, Begin */
    MODEM_ID_ENUM_UINT16                enModemId;
    AT_MODEM_PS_CTX_STRU               *pstPsModemCtx = VOS_NULL_PTR;

    enModemId = MODEM_ID_0;

    ulRet = AT_GetModemIdFromClient((AT_CLIENT_TAB_INDEX_UINT8)pstEvent->stCtrl.usClientId, &enModemId);
    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_DeRegHsicFCPoint: Get modem id fail.");
        return VOS_ERR;
    }

    pstPsModemCtx = AT_GetModemPsCtxAddrFromModemId(enModemId);

    /* ID */
    if ((VOS_TRUE == pstPsModemCtx->astChannelCfg[pstEvent->ucCid].ulUsed)
      &&(AT_PS_INVALID_RMNET_ID != pstPsModemCtx->astChannelCfg[pstEvent->ucCid].ulRmNetId))
    {
        enDataChannelId = (UDI_DEVICE_ID_E)pstPsModemCtx->astChannelCfg[pstEvent->ucCid].ulRmNetId;
    }
    else
    {
        AT_ERR_LOG("AT_DeRegHsicFCPoint: ERROR: data channel id is abnormal.");
        return VOS_ERR;
    }

    /* Modified by L47619 for C52 HSIC ACM->NCM Project, 2012/09/06, begin */
    switch ( enDataChannelId )
    {
        case UDI_ACM_HSIC_ACM1_ID:
        case UDI_NCM_HSIC_NCM0_ID:
            enFcId = FC_ID_DIPC_1;
            break;
        case UDI_ACM_HSIC_ACM3_ID:
        case UDI_NCM_HSIC_NCM1_ID:
            enFcId = FC_ID_DIPC_2;
            break;
        case UDI_ACM_HSIC_ACM5_ID:
        case UDI_NCM_HSIC_NCM2_ID:
            enFcId = FC_ID_DIPC_3;
            break;
        default:
            AT_WARN_LOG("AT_DeRegHsicFCPoint: WARNING: data channel id is abnormal.");
            return VOS_ERR;
    }
    /* Modified by L47619 for C52 HSIC ACM->NCM Project, 2012/09/06, end */

    /*  */
    FC_ChannelMapDelete(pstEvent->ucRabId, enModemId);

    ulRet = FC_DeRegPoint(enFcId, enModemId);
    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_DeRegHsicFCPoint: ERROR: de reg point Failed.");
        return VOS_ERR;
    }
    /* Modified by l60609 for DSDA Phase II, 2012-12-21, End */

    /* FCIDFC Pri */
    g_stFcIdMaptoFcPri[enFcId].ulUsed       = VOS_FALSE;
    g_stFcIdMaptoFcPri[enFcId].enFcPri      = FC_PRI_BUTT;
    /* RABIDRABID */
    g_stFcIdMaptoFcPri[enFcId].ulRabIdMask &= ~((VOS_UINT32)1 << pstEvent->ucRabId);
    g_stFcIdMaptoFcPri[enFcId].enModemId    = MODEM_ID_BUTT;

    /*  */
    AT_MNTN_TraceDeregFcPoint((VOS_UINT8)pstEvent->stCtrl.usClientId, AT_FC_POINT_TYPE_HSIC);


    return VOS_OK;
}


/*****************************************************************************
     : AT_HsicPsRspEvtPdpActCnfProc
   : pdpHSIC AT
   : pEvent  --- 
   : 
     : 
   :
   :

       :
  1.       : 2012217
           : L47619
       : 
  2.       : 20130708
           : Y00213812
       : VoLTE_PhaseI EVENT,
*****************************************************************************/
VOS_VOID  AT_HsicPsRspEvtPdpActCnfProc(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
    /* Added by Y00213812 for VoLTE_PhaseI , 2013-07-08, begin */
    /* DIPCPDP */
    AT_SndDipcPdpActInd(pstEvent->stCtrl.usClientId, pstEvent->ucCid, pstEvent->ucRabId);

    /* FC */
    AT_RegHsicFCPoint(pstEvent);

    /* CIDPDP */
    AT_SetAtChdataCidActStatus(pstEvent->stCtrl.usClientId, pstEvent->ucCid, VOS_TRUE);
    /* Added by Y00213812 for VoLTE_PhaseI , 2013-07-08, end */
    return;
}


/*****************************************************************************
     : AT_HsicPsRspEvtPdpDeactCnfProc
   : pdpHSIC AT
   : pEvent  --- 
   : 
     : 
   :
   :

       :
  1.       : 2012217
           : L47619
       : 
  2.       : 20130708
           : Y00213812
       : VoLTE_PhaseI EVENT,
*****************************************************************************/
VOS_VOID  AT_HsicPsRspEvtPdpDeactCnfProc(
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
)
{
    /* Added by Y00213812 for VoLTE_PhaseI , 2013-07-08, begin */
    /* DIPCPDP */
    AT_SndDipcPdpDeactInd(pstEvent->ucRabId);

    /* FC */
    AT_DeRegHsicFCPoint(pstEvent);

    /* CID */
    AT_CleanAtChdataCfg(pstEvent->stCtrl.usClientId, pstEvent->ucCid);
    /* Added by Y00213812 for VoLTE_PhaseI , 2013-07-08, end */

    return;
}


/*****************************************************************************
     : AT_HsicPsRspEvtPdpDeactivatedProc
   : pdpHSIC AT
   : ucIndex --- 
             pEvent  --- 
   : 
     : 
   :
   :

       :
  1.       : 2012217
           : L47619
       : 

  2.       : 2012822
           : A00165503
       : PS

  3.       : 2012822
           : y00213812
       : DTS2012113005521:AT
                 HSICAT_STOP_TIMER_CMD_READY

  4.       : 20130708
           : Y00213812
       : VoLTE_PhaseI EVENT,

*****************************************************************************/
VOS_VOID  AT_HsicPsRspEvtPdpDeactivatedProc(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_DEACTIVATE_IND_STRU *pstEvent
)
{
    VOS_UINT16  usLength;

    usLength    = 0;

    /* Added by Y00213812 for VoLTE_PhaseI , 2013-07-08, begin */
    /* DIPCPDP */
    AT_SndDipcPdpDeactInd(pstEvent->ucRabId);

    /* FC */
    AT_DeRegHsicFCPoint(pstEvent);

    /* CID */
    AT_CleanAtChdataCfg(pstEvent->stCtrl.usClientId, pstEvent->ucCid);
    /* Added by Y00213812 for VoLTE_PhaseI , 2013-07-08, end */

    switch (pstEvent->enPdpType)
    {
        case TAF_PDP_IPV4:

            usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                        "%s^DEND:%d,%d,\"%s\"%s",
                                        gaucAtCrLf,
                                        pstEvent->ucCid,
                                        pstEvent->enCause,
                                        "IPV4",
                                        gaucAtCrLf);

            break;

        case TAF_PDP_IPV6:

            usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                        "%s^DEND:%d,%d,\"%s\"%s",
                                        gaucAtCrLf,
                                        pstEvent->ucCid,
                                        pstEvent->enCause,
                                        "IPV6",
                                        gaucAtCrLf);

            break;

        case TAF_PDP_IPV4V6:

            usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                        "%s^DEND:%d,%d,\"%s\"%s",
                                        gaucAtCrLf,
                                        pstEvent->ucCid,
                                        pstEvent->enCause,
                                        "IPV4",
                                        gaucAtCrLf);
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                        "%s^DEND:%d,%d,\"%s\"%s",
                                        gaucAtCrLf,
                                        pstEvent->ucCid,
                                        pstEvent->enCause,
                                        "IPV6",
                                        gaucAtCrLf);

            break;

        default:
            AT_ERR_LOG("AT_HsicPsRspEvtPdpDeactivatedProc:ERROR: PDP type is invalid!");
            return;
    }

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, usLength);

    return;
}

/* Modified by l60609 for AP 2012-09-10 Begin */
/*****************************************************************************
     : AT_SendRnicCgactIpv4ActInd
   : AT+CGACTRNICPDP
   : VOS_UINT8                           ucRabId,
             VOS_UINT8                           ucRmNetId
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 20121219
           : l60609
       : 

*****************************************************************************/
VOS_UINT32 AT_SendRnicCgactIpv4ActInd(
    VOS_UINT8                           ucRabId,
    VOS_UINT8                           ucRmNetId
)
{
    AT_RNIC_IPV4_PDP_ACT_IND_STRU      *pstMsg;

    /* AT_RNIC_IPV4_PDP_ACT_IND_STRU */
    pstMsg = (AT_RNIC_IPV4_PDP_ACT_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                            WUEPS_PID_AT,
                            sizeof(AT_RNIC_IPV4_PDP_ACT_IND_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        AT_WARN_LOG("AT_SendRnicCgactIpv4ActInd: alloc msg fail!");
        return VOS_ERR;
    }

    /*  */
    TAF_MEM_SET_S((VOS_CHAR*)pstMsg + VOS_MSG_HEAD_LENGTH,
               (VOS_SIZE_T)(sizeof(AT_RNIC_IPV4_PDP_ACT_IND_STRU) - VOS_MSG_HEAD_LENGTH),
               0x00,
               (VOS_SIZE_T)(sizeof(AT_RNIC_IPV4_PDP_ACT_IND_STRU) - VOS_MSG_HEAD_LENGTH));

    /*  */
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = ACPU_PID_RNIC;
    pstMsg->enMsgId         = ID_AT_RNIC_IPV4_PDP_ACT_IND;

    /*  */
    pstMsg->ucRabId         = ucRabId;
    pstMsg->ucRmNetId       = ucRmNetId;

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_AT, pstMsg))
    {
        AT_WARN_LOG("AT_SendRnicCgactIpv4ActInd: Send msg fail!");
        return VOS_ERR;
    }

    return VOS_OK;
}
/*****************************************************************************
     : AT_ProcAppPsRspEvtPdpActCnf
   : RILAT+CGACTPDP
   : VOS_UINT8                           ucIndex
             TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU   *pEvent
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 2012112
           : l60609
       : 
  2.       : 20121218
           : l60609
       : DSDA Phase II
*****************************************************************************/
VOS_VOID  AT_ProcAppPsRspEvtPdpActCnf(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
    VOS_UINT32                          ulRslt;
    AT_FCID_MAP_STRU                    stFCPriOrg;
    FC_ID_ENUM_UINT8                    enDefaultFcId;
    VOS_UINT8                           ucRmNetId;

    ucRmNetId = 0;

    /* Id */
    ulRslt = AT_PS_GetRmNetIdByCid(ucIndex, pstEvent->ucCid, &ucRmNetId);

    /* IdCID */
    if (VOS_OK != ulRslt)
    {
        return;
    }

    /* FcId */
    enDefaultFcId = g_astPsRmNetIdTab[ucRmNetId].enFcId;

    TAF_MEM_SET_S(&stFCPriOrg, sizeof(stFCPriOrg), 0x00, sizeof(stFCPriOrg));

    ulRslt = AT_GetFcPriFromMap(enDefaultFcId ,&stFCPriOrg);
    if (VOS_OK == ulRslt)
    {
        /* FC ID*/
        if (VOS_TRUE != stFCPriOrg.ulUsed)
        {
            /* APP */
            AT_AppRegFCPoint(enDefaultFcId, pstEvent, ucRmNetId);
        }
        else
        {
            /* APPQOSFC_PRI_FOR_PDN_LOWEST */
            AT_NORM_LOG("AT_ProcAppPsRspEvtPdpActCnf: No need to change the default QOS priority.");
        }
    }

    /* APPAT+CGACTIPV4 */
    AT_SendRnicCgactIpv4ActInd(pstEvent->ucRabId, ucRmNetId);

    return;
}

/*****************************************************************************
     : AT_ProcAppPsRspEvtPdpDeActCnf
   : RILAT+CGACTPDP
   : TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU        *pstEvent
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 2012112
           : l60609
       : 
  2.       : 20121218
           : l60609
       : DSDA Phase II
*****************************************************************************/
VOS_VOID  AT_ProcAppPsRspEvtPdpDeActCnf(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
)
{
    FC_ID_ENUM_UINT8                    enDefaultFcId;
    VOS_UINT8                           ucRmNetId;
    VOS_UINT32                          ulRslt;

    ucRmNetId = 0;

    /* Id */
    ulRslt = AT_PS_GetRmNetIdByCid(ucIndex, pstEvent->ucCid, &ucRmNetId);

    /* IdCID */
    if (VOS_OK != ulRslt)
    {
        return;
    }

    /* FcId */
    enDefaultFcId = g_astPsRmNetIdTab[ucRmNetId].enFcId;

    /* RNIC PDP */
    AT_SendRnicPdpDeactInd(pstEvent->ucRabId, ucRmNetId);

    /* APP(1) */
    AT_AppDeRegFCPoint(enDefaultFcId, pstEvent);

    return;
}
/* Modified by l60609 for AP 2012-09-10 End */
/*****************************************************************************
     : AT_ProcAppPsRspEvtPdpDeactivated
   : APPAT+CGACTPDPPDP
   : VOS_UINT8                           ucIndex
             TAF_PS_CALL_PDP_DEACTIVATE_IND_STRU *pstEvent
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20121218
           : l60609
       : 

*****************************************************************************/
VOS_VOID AT_ProcAppPsRspEvtPdpDeactivated(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_DEACTIVATE_IND_STRU *pstEvent
)
{
    VOS_UINT16                          usLength;
    FC_ID_ENUM_UINT8                    enDefaultFcId;
    VOS_UINT8                           ucRmNetId;
    VOS_UINT32                          ulRslt;

    usLength    = 0;
    ucRmNetId   = 0;

    /* APPNDIS1 */
    enDefaultFcId = FC_ID_NIC_1;

    /* Id */
    ulRslt = AT_PS_GetRmNetIdByCid(ucIndex, pstEvent->ucCid, &ucRmNetId);

    /* IdCID */
    if (VOS_OK == ulRslt)
    {
        /* RNIC PDP */
        AT_SendRnicPdpDeactInd(pstEvent->ucRabId, ucRmNetId);

        /* APP(1) */
        AT_AppDeRegFCPoint(enDefaultFcId, pstEvent);
    }

    switch (pstEvent->enPdpType)
    {
        case TAF_PDP_IPV4:
            usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                        "%s^DEND:%d,%d,\"%s\"%s",
                                        gaucAtCrLf,
                                        pstEvent->ucCid,
                                        pstEvent->enCause,
                                        "IPV4",
                                        gaucAtCrLf);
            break;

        case TAF_PDP_IPV6:
            usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                        "%s^DEND:%d,%d,\"%s\"%s",
                                        gaucAtCrLf,
                                        pstEvent->ucCid,
                                        pstEvent->enCause,
                                        "IPV6",
                                        gaucAtCrLf);
            break;

        case TAF_PDP_IPV4V6:
            usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                        "%s^DEND:%d,%d,\"%s\"%s",
                                        gaucAtCrLf,
                                        pstEvent->ucCid,
                                        pstEvent->enCause,
                                        "IPV4",
                                        gaucAtCrLf);
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                        "%s^DEND:%d,%d,\"%s\"%s",
                                        gaucAtCrLf,
                                        pstEvent->ucCid,
                                        pstEvent->enCause,
                                        "IPV6",
                                        gaucAtCrLf);
            break;

        default:
            AT_ERR_LOG("AT_ProcAppPsRspEvtPdpDeactivated:ERROR: PDP type is invalid!");
            return;
    }

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, usLength);

    return;
}

/*****************************************************************************
     : AT_NotifyFcWhenAppPdpModify
   : PDP MODIFY(UE)FC
   : VOS_UINT8                           ucIndex,
             TAF_PS_CALL_PDP_MODIFY_CNF_STRU    *pstEvent
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 2013117
           : l60609
       : 

*****************************************************************************/
VOS_VOID AT_NotifyFcWhenAppPdpModify(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_MODIFY_CNF_STRU    *pstEvent
)
{
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           ucRmNetId;
    FC_ID_ENUM_UINT8                    enDefaultFcId;

    ucRmNetId = 0;

    /* Id */
    ulRslt = AT_PS_GetRmNetIdByCid(ucIndex, pstEvent->ucCid, &ucRmNetId);

    /* IdCID */
    if (VOS_OK != ulRslt)
    {
        return;
    }

    /* FcId */
    enDefaultFcId = g_astPsRmNetIdTab[ucRmNetId].enFcId;

    AT_NotifyFcWhenPdpModify(pstEvent, enDefaultFcId);

    return;
}

/*****************************************************************************
     : AT_PS_AddIpAddrRabIdMap
   : IPRABID
   : usClientId - ID
             pstEvent   - PS
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20131111
           : A00165503
       : 

  2.       : 201459
           : A00165503
       : DTS2014050900349: IP
*****************************************************************************/
VOS_VOID AT_PS_AddIpAddrRabIdMap(
    VOS_UINT16                          usClientId,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
    AT_MODEM_PS_CTX_STRU               *pstPsModemCtx = VOS_NULL_PTR;
    VOS_UINT32                          ulIpAddr;

    pstPsModemCtx = AT_GetModemPsCtxAddrFromClientId(usClientId);
    ulIpAddr      = 0;

    if (!AT_PS_IS_RABID_VALID(pstEvent->ucRabId))
    {
        return;
    }

    if (pstEvent->bitOpPdpAddr)
    {
        ulIpAddr = AT_GetLanAddr32(pstEvent->stPdpAddr.aucIpv4Addr);
        pstPsModemCtx->aulIpAddrRabIdMap[pstEvent->ucRabId - AT_PS_RABID_OFFSET] = ulIpAddr;
    }

    return;
}

/*****************************************************************************
     : AT_PS_DeleteIpAddrRabIdMap
   : IPRABID
   : usClientId - ID
             pstEvent   - PS
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20131111
           : A00165503
       : 
*****************************************************************************/
VOS_VOID AT_PS_DeleteIpAddrRabIdMap(
    VOS_UINT16                          usClientId,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
)
{
    AT_MODEM_PS_CTX_STRU               *pstPsModemCtx = VOS_NULL_PTR;

    pstPsModemCtx = AT_GetModemPsCtxAddrFromClientId(usClientId);

    if (!AT_PS_IS_RABID_VALID(pstEvent->ucRabId))
    {
        return;
    }

    pstPsModemCtx->aulIpAddrRabIdMap[pstEvent->ucRabId - AT_PS_RABID_OFFSET] = 0;

    return;
}

/*****************************************************************************
     : AT_PS_GetIpAddrByRabId
   : RABIDIP
   : usClientId - ID
             ucRabId    - RABID [5,15]
   : 
     : ulIpAddr   - IP()
   :
   :

       :
  1.       : 20131111
           : A00165503
       : 
*****************************************************************************/
VOS_UINT32 AT_PS_GetIpAddrByRabId(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucRabId
)
{
    AT_MODEM_PS_CTX_STRU               *pstPsModemCtx = VOS_NULL_PTR;
    VOS_UINT32                          ulIpAddr;

    pstPsModemCtx = AT_GetModemPsCtxAddrFromClientId(usClientId);
    ulIpAddr      = 0;

    if (AT_PS_IS_RABID_VALID(ucRabId))
    {
        ulIpAddr = pstPsModemCtx->aulIpAddrRabIdMap[ucRabId - AT_PS_RABID_OFFSET];
    }

    return ulIpAddr;
}

/* Added by l60609 for DSDA Phase II, 2012-12-18, Begin */
/*****************************************************************************
     : AT_PS_GetRmNetIdFromCid
   : Client IdCidId
   : VOS_UINT16                          usClientId,
             VOS_UINT8                           ucCid,
             VOS_UINT8                          *pucRmNetId
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 20121218
           : l60609
       : 

*****************************************************************************/
VOS_UINT32 AT_PS_GetRmNetIdByCid(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCid,
    VOS_UINT8                          *pucRmNetId
)
{
    VOS_UINT8                           i;
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT32                          ulRslt;

    enModemId = MODEM_ID_0;

    if (VOS_NULL_PTR == pucRmNetId)
    {
        return VOS_ERR;
    }

    ulRslt = AT_GetModemIdFromClient((VOS_UINT8)usClientId, &enModemId);

    /* modem id */
    if (VOS_OK != ulRslt)
    {
        return VOS_ERR;
    }

    for (i = 0; i < (sizeof(g_astPsRmNetIdTab)/sizeof(AT_PS_RMNET_ID_TAB)); i++)
    {
        if ((enModemId == g_astPsRmNetIdTab[i].enModemId)
         && (ucCid == g_astPsRmNetIdTab[i].ucUsrCid))
        {
            *pucRmNetId = i;
            break;
        }
    }

    /*  */
    if (i >= sizeof(g_astPsRmNetIdTab)/sizeof(AT_PS_RMNET_ID_TAB))
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/* Added by l60609 for DSDA Phase II, 2012-12-18, End */

/*****************************************************************************
     : AT_ResetFlowCtl
   : 
   : ulParam1      
             ulParam2      FCID
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 20130415
           : f00179208
       : 
*****************************************************************************/
VOS_UINT32 AT_ResetFlowCtl(
    VOS_UINT32                          ulParam1,
    VOS_UINT32                          ulParam2
)
{
    VOS_UINT8                           ucRabIdIndex;
    VOS_UINT32                          ulRabIdMask;
    VOS_UINT32                          ulRet;
    FC_ID_ENUM_UINT8                    enFcId;
    MODEM_ID_ENUM_UINT16                enModemId;

    enFcId      = (FC_ID_ENUM_UINT8)ulParam2;
    enModemId   = g_stFcIdMaptoFcPri[enFcId].enModemId;
    ulRabIdMask = g_stFcIdMaptoFcPri[enFcId].ulRabIdMask;

    if (VOS_TRUE == g_stFcIdMaptoFcPri[enFcId].ulUsed)
    {
        for (ucRabIdIndex = AT_PS_MIN_RABID; ucRabIdIndex <= AT_PS_MAX_RABID; ucRabIdIndex++)
        {
            if (1 == ((ulRabIdMask >> ucRabIdIndex) & 0x1))
            {
                FC_ChannelMapDelete(ucRabIdIndex, enModemId);
            }
        }

        ulRet = FC_DeRegPoint(enFcId, enModemId);
        if (VOS_OK != ulRet)
        {
            AT_ERR_LOG("AT_ResetFlowCtl: ERROR: DeReg point failed.");
            return VOS_ERR;
        }

        g_stFcIdMaptoFcPri[enFcId].ulUsed       = VOS_FALSE;
        g_stFcIdMaptoFcPri[enFcId].enFcPri      = FC_PRI_BUTT;
        g_stFcIdMaptoFcPri[enFcId].ulRabIdMask  = 0;
        g_stFcIdMaptoFcPri[enFcId].enModemId    = MODEM_ID_BUTT;

    }

    return VOS_OK;
}

/* Added by l60609 for V9R1 IPv6&TAF/SM Project, 2013-4-24, begin */

/*****************************************************************************
     : AT_PS_GetRnicRmNetIdFromChDataValue
   : CHDATARNICID
   : VOS_UINT8                           ucIndex
             AT_CH_DATA_CHANNEL_ENUM_UINT32      enDataChannelId
             RNIC_RMNET_ID_ENUM_UINT8           *penRnicRmNetId
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 2013426
           : L60609
       : 

  2.       : 2015528
           : l00198894
       : TSTS
*****************************************************************************/
VOS_UINT32 AT_PS_GetRnicRmNetIdFromChDataValue(
    VOS_UINT8                           ucIndex,
    AT_CH_DATA_CHANNEL_ENUM_UINT32      enDataChannelId,
    RNIC_RMNET_ID_ENUM_UINT8           *penRnicRmNetId
)
{
    VOS_UINT32                          i;
    MODEM_ID_ENUM_UINT16                enModemId;
    AT_CHDATA_RNIC_RMNET_ID_STRU       *pstChdataRnicRmNetIdTab;
    VOS_UINT32                          ulRslt;

    pstChdataRnicRmNetIdTab = AT_PS_GET_CHDATA_RNIC_RMNET_ID_TBL_PTR();

    *penRnicRmNetId = RNIC_RMNET_ID_0;

    ulRslt = AT_GetModemIdFromClient(ucIndex, &enModemId);

    if (VOS_OK != ulRslt)
    {
        return VOS_ERR;
    }

    /*
        MODEM0 RNIC ID  0~2 CHDATA 1~3
        MODEM1 RNIC ID  3~4 CHDATA 4~5
        MODEM2 RNIC ID  6~7 CHDATA 6~7
    */

    if (MODEM_ID_0 == enModemId)
    {
        if ((enDataChannelId < AT_CH_DATA_CHANNEL_ID_1)
         || (enDataChannelId > AT_CH_DATA_CHANNEL_ID_3))
        {
            return VOS_ERR;
        }
    }

    else if (MODEM_ID_1 == enModemId)
    {
        if ((enDataChannelId < AT_CH_DATA_CHANNEL_ID_4)
         || (enDataChannelId > AT_CH_DATA_CHANNEL_ID_5))
        {
            return VOS_ERR;
        }
    }
    else
    {
        return VOS_ERR;
    }

    /*  enDataChannelIdRM NET ID */
    for (i = 0; i < AT_PS_GET_CHDATA_RNIC_RMNET_ID_TBL_SIZE() ; i++)
    {
        if (enDataChannelId == pstChdataRnicRmNetIdTab[i].enChdataValue)
        {
            *penRnicRmNetId = pstChdataRnicRmNetIdTab[i].enRnicRmNetId;
            break;
        }
    }

    return VOS_OK;
}

/*****************************************************************************
     : AT_PS_GetChDataValueFromRnicRmNetId
   : RNICIDCHDATA
   : RNIC_RMNET_ID_ENUM_UINT8            enRnicRmNetId
             AT_CH_DATA_CHANNEL_ENUM_UINT32     *penDataChannelId
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 2013426
           : l60609
       : 

*****************************************************************************/
VOS_UINT32 AT_PS_GetChDataValueFromRnicRmNetId(
    RNIC_RMNET_ID_ENUM_UINT8            enRnicRmNetId,
    AT_CH_DATA_CHANNEL_ENUM_UINT32     *penDataChannelId
)
{
    VOS_UINT32                          i;
    AT_CHDATA_RNIC_RMNET_ID_STRU       *pstChdataRnicRmNetIdTab;

    pstChdataRnicRmNetIdTab = AT_PS_GET_CHDATA_RNIC_RMNET_ID_TBL_PTR();

    for (i = 0; i < AT_PS_GET_CHDATA_RNIC_RMNET_ID_TBL_SIZE() ; i++)
    {
        if (enRnicRmNetId == pstChdataRnicRmNetIdTab[i].enRnicRmNetId)
        {
            *penDataChannelId = pstChdataRnicRmNetIdTab[i].enChdataValue;
            break;
        }
    }

    if (i >= AT_PS_GET_CHDATA_RNIC_RMNET_ID_TBL_SIZE())
    {
        return VOS_ERR;
    }


    return VOS_OK;
}

/*****************************************************************************
     : AT_PS_GetFcIdByUdiDeviceId
   : DIPCIDFCID
   : UDI_DEVICE_ID                       enDataChannelId
   : 
     : FC_ID_ENUM_UINT8
   :
   :

       :
  1.       : 201352
           : l60609
       : 

*****************************************************************************/
FC_ID_ENUM_UINT8 AT_PS_GetFcIdByUdiDeviceId(
    UDI_DEVICE_ID_E                     enDataChannelId
)
{
    switch ( enDataChannelId )
    {
        case UDI_ACM_HSIC_ACM1_ID:
        case UDI_NCM_HSIC_NCM0_ID:
            return FC_ID_DIPC_1;

        case UDI_ACM_HSIC_ACM3_ID:
        case UDI_NCM_HSIC_NCM1_ID:
            return FC_ID_DIPC_2;

        case UDI_ACM_HSIC_ACM5_ID:
        case UDI_NCM_HSIC_NCM2_ID:
            return FC_ID_DIPC_3;

        default:
            AT_WARN_LOG("AT_PS_GetFcIdByUdiDeviceId: WARNING: data channel id is abnormal.");
            return FC_ID_BUTT;
    }
}

/*****************************************************************************
     : AT_PS_GetFcIdFromRnicByRmNetId
   : RNICFCID
   : VOS_UINT32                          ulRmNetId
   : 
     : FC_ID_ENUM_UINT8
   :
   :

       :
  1.       : 201352
           : l60609
       : 

  2.       : 2015527
           : l00198894
       : TSTS
*****************************************************************************/
FC_ID_ENUM_UINT8 AT_PS_GetFcIdFromRnicByRmNetId(
    VOS_UINT32                          ulRmNetId
)
{
    switch (ulRmNetId)
    {
        case RNIC_RMNET_ID_0:
            return FC_ID_NIC_1;

        case RNIC_RMNET_ID_1:
            return FC_ID_NIC_2;

        case RNIC_RMNET_ID_2:
            return FC_ID_NIC_3;

        case RNIC_RMNET_ID_3:
            return FC_ID_NIC_4;

        case RNIC_RMNET_ID_4:
            return FC_ID_NIC_5;

        default:
            AT_WARN_LOG("AT_PS_GetFcIdFromRnidRmNetId: WARNING: data channel id is abnormal.");
            return FC_ID_BUTT;
    }
}

/*****************************************************************************
     : AT_PS_GetCallEntity
   : PS
   : VOS_UINT16                          usClientId
             VOS_UINT8                           ucCallId
   : 
     : AT_PS_CALL_ENTITY_STRU *
   :
   :

       :
  1.       : 2013425
           : l60609
       : 

*****************************************************************************/
AT_PS_CALL_ENTITY_STRU* AT_PS_GetCallEntity(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId
)
{
    AT_MODEM_PS_CTX_STRU                  *pstPsModemCtx = VOS_NULL_PTR;

    pstPsModemCtx = AT_GetModemPsCtxAddrFromClientId(usClientId);

    return &(pstPsModemCtx->astCallEntity[ucCallId]);
}

/*****************************************************************************
     : AT_PS_GetUserInfo
   : PS
   : VOS_UINT16                          usClientId
             VOS_UINT8                           ucCallId
   : 
     : AT_PS_USER_INFO_STRU*
   :
   :

       :
  1.       : 2013425
           : l60609
       : 

*****************************************************************************/
AT_PS_USER_INFO_STRU* AT_PS_GetUserInfo(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId
)
{
    AT_MODEM_PS_CTX_STRU                  *pstPsModemCtx = VOS_NULL_PTR;

    pstPsModemCtx = AT_GetModemPsCtxAddrFromClientId(usClientId);

    return &(pstPsModemCtx->astCallEntity[ucCallId].stUserInfo);
}

/*****************************************************************************
     : AT_PS_GetDataChanlCfg
   : 
   : VOS_UINT16                          usClientId
             VOS_UINT8                           ucCid
   : 
     : AT_PS_DATA_CHANL_CFG_STRU*
   :
   :

       :
  1.       : 201357
           : l60609
       : 

*****************************************************************************/
AT_PS_DATA_CHANL_CFG_STRU* AT_PS_GetDataChanlCfg(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCid
)
{
    AT_MODEM_PS_CTX_STRU                  *pstPsModemCtx = VOS_NULL_PTR;

    pstPsModemCtx = AT_GetModemPsCtxAddrFromClientId(usClientId);

    return &(pstPsModemCtx->astChannelCfg[ucCid]);
}
/*****************************************************************************
     : AT_PS_TransCidToCallId
   : CIDPS
   : VOS_UINT16                          usClientId
             VOS_UINT8                           ucCid
   : 
     : VOS_UINT8
   :
   :

       :
  1.       : 2013425
           : l60609
       : 

*****************************************************************************/
VOS_UINT8 AT_PS_TransCidToCallId(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCid
)
{
    AT_MODEM_PS_CTX_STRU               *pstPsModemCtx = VOS_NULL_PTR;

    /* cid  */
    if (ucCid > TAF_MAX_CID)
    {
        return AT_PS_CALL_INVALID_CALLID;
    }

    pstPsModemCtx = AT_GetModemPsCtxAddrFromClientId(usClientId);

    return pstPsModemCtx->aucCidToIndexTbl[ucCid];
}

/*****************************************************************************
     : AT_PS_TransCallEndCause
   : CIDPS
   : VOS_UINT8                           ucConnectType
   : 
     : TAF_PS_CALL_END_CAUSE_ENUM_UINT8
   :
   :

       :
  1.       : 20170206
           : w00316404
       : 
*****************************************************************************/
TAF_PS_CALL_END_CAUSE_ENUM_UINT8 AT_PS_TransCallEndCause(
    VOS_UINT8                           ucConnectType
)
{
    TAF_PS_CALL_END_CAUSE_ENUM_UINT8    enCause;

    enCause = TAF_PS_CALL_END_CAUSE_NORMAL;

    if (TAF_PS_CALL_TYPE_DOWN_FORCE == ucConnectType)
    {
        enCause = TAF_PS_CALL_END_CAUSE_FORCE;
    }

    return enCause;
}

/*****************************************************************************
     : AT_PS_IsCallIdValid
   : PS
   : VOS_UINT16                          usClientId
             VOS_UINT8                           ucCallId
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 2013425
           : l60609
       : 

*****************************************************************************/
VOS_UINT32 AT_PS_IsCallIdValid(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId
)
{
    AT_MODEM_PS_CTX_STRU               *pstPsModemCtx = VOS_NULL_PTR;

    if (ucCallId >= AT_PS_MAX_CALL_NUM)
    {
        return VOS_FALSE;
    }

    pstPsModemCtx = AT_GetModemPsCtxAddrFromClientId(usClientId);

    if ((AT_PS_CALL_INVALID_CID == pstPsModemCtx->astCallEntity[ucCallId].ucIpv4Cid)
     && (AT_PS_CALL_INVALID_CID == pstPsModemCtx->astCallEntity[ucCallId].ucIpv6Cid))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
     : AT_PS_AssignCallIdToCid
   : cidcallid
   : VOS_UINT16                          usClientId
             VOS_UINT8                           ucCid
             VOS_UINT8                           ucCallId
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 2013425
           : l60609
       : 

*****************************************************************************/
VOS_VOID AT_PS_AssignCallIdToCid(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCid,
    VOS_UINT8                           ucCallId
)
{
    AT_MODEM_PS_CTX_STRU               *pstPsModemCtx = VOS_NULL_PTR;

    pstPsModemCtx = AT_GetModemPsCtxAddrFromClientId(usClientId);

    pstPsModemCtx->aucCidToIndexTbl[ucCid] = ucCallId;

    return;
}

/*****************************************************************************
     : AT_PS_FreeCallIdToCid
   : cidcallid
   : VOS_UINT16                          usClientId
             VOS_UINT8                           ucCid
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 2013425
           : l60609
       : 

*****************************************************************************/
VOS_VOID AT_PS_FreeCallIdToCid(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCid
)
{
    AT_MODEM_PS_CTX_STRU               *pstPsModemCtx = VOS_NULL_PTR;

    pstPsModemCtx = AT_GetModemPsCtxAddrFromClientId(usClientId);

    pstPsModemCtx->aucCidToIndexTbl[ucCid] = AT_PS_CALL_INVALID_CALLID;

    return;
}

/*****************************************************************************
     : AT_PS_SetCid2CurrCall
   : CID
   : usClientId - ID
             ucCallId  - 
             enPdpType - PDP
             ucCid     - CID
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20121220
           : A00165503
       : 
*****************************************************************************/
VOS_VOID AT_PS_SetCid2CurrCall(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType,
    VOS_UINT8                           ucCid
)
{
    /* (CallId) */

    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;

    pstCallEntity = AT_PS_GetCallEntity(usClientId, ucCallId);

    switch (enPdpType)
    {
        case TAF_PDP_IPV4:
            pstCallEntity->ucIpv4Cid = ucCid;
            break;

        case TAF_PDP_IPV6:
            pstCallEntity->ucIpv6Cid = ucCid;
            break;

        case TAF_PDP_IPV4V6:
            pstCallEntity->ucIpv4Cid = ucCid;
            pstCallEntity->ucIpv6Cid = ucCid;
            break;

        default:
            AT_ERR_LOG("AT_PS_SetCid2CurrCall: PDP type is invalid!");
            break;
    }

    return;
}

/*****************************************************************************
     : AT_PS_GetCidByCallType
   : CID
   : usClientId - ID
             ucCallId  - 
             enPdpType - PDP
   : 
     : VOS_UINT8 - CID
   :
   :

       :
  1.       : 20121220
           : A00165503
       : 
*****************************************************************************/
VOS_UINT8 AT_PS_GetCidByCallType(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
)
{
    /* (CallId) */

    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;
    VOS_UINT8                           ucCid;

    pstCallEntity = AT_PS_GetCallEntity(usClientId, ucCallId);

    switch (enPdpType)
    {
        case TAF_PDP_IPV4:
            ucCid = pstCallEntity->ucIpv4Cid;
            break;

        case TAF_PDP_IPV6:
            ucCid = pstCallEntity->ucIpv6Cid;
            break;

        default:
            ucCid = AT_PS_CALL_INVALID_CID;
            AT_ERR_LOG("AT_PS_SetCid2CurrCall: PDP type is invalid!");
            break;
    }

    return ucCid;
}

/*****************************************************************************
     : AT_PS_SetCallStateByType
   : PDP
   : usClientId - ID
             ucCallId   - 
             enPdpType  - PDP(IPv4, IPv6 or IPv4v6)
             enPdpState - PDP
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20121210
           : Y00213812
       : C50 IPv6 
*****************************************************************************/
VOS_VOID AT_PS_SetCallStateByType(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType,
    AT_PDP_STATE_ENUM_U8                enPdpState
)
{
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;

    pstCallEntity = AT_PS_GetCallEntity(usClientId, ucCallId);

    switch (enPdpType)
    {
        case TAF_PDP_IPV4:
            pstCallEntity->enIpv4State = enPdpState;
            break;

        case TAF_PDP_IPV6:
            pstCallEntity->enIpv6State = enPdpState;
            break;

        case TAF_PDP_IPV4V6:
            pstCallEntity->enIpv4State = enPdpState;
            pstCallEntity->enIpv6State = enPdpState;
            break;

        default:
            AT_ERR_LOG("AT_PS_SetCallStateByType: PDP type is invalid!");
            break;
    }

    return;
}

/*****************************************************************************
     : AT_PS_GetCallStateByType
   : PDP, PDPIPv4IPv6
   : usClientId - ID
             ucCallId   - 
             enPdpType  - PDP(IPv4 or IPv6)
   : 
     : AT_PDP_STATE_ENUM_U8
   :
   :

       :
  1.       : 20121218
           : A00165503
       : 
*****************************************************************************/
AT_PDP_STATE_ENUM_U8 AT_PS_GetCallStateByType(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
)
{
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;
    AT_PDP_STATE_ENUM_U8                enPdpState;

    pstCallEntity = AT_PS_GetCallEntity(usClientId, ucCallId);

    switch (enPdpType)
    {
        case TAF_PDP_IPV4:
            enPdpState = pstCallEntity->enIpv4State;
            break;

        case TAF_PDP_IPV6:
            enPdpState = pstCallEntity->enIpv6State;
            break;

        default:
            enPdpState = AT_PDP_STATE_IDLE;
            AT_ERR_LOG("AT_PS_GetCallStateByType: PDP type is invalid!");
            break;
    }

    return enPdpState;
}

/*****************************************************************************
     : AT_PS_GetCallStateByCid
   : CID
   : usClientId - ID
             ucCallId   - 
             ucCid      - CID
   : 
     : AT_PDP_STATE_ENUM_U8
   :
   :

       :
  1.       : 20121218
           : A00165503
       : 
*****************************************************************************/
AT_PDP_STATE_ENUM_U8 AT_PS_GetCallStateByCid(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId,
    VOS_UINT8                           ucCid
)
{
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;

    pstCallEntity = AT_PS_GetCallEntity(usClientId, ucCallId);

    if (pstCallEntity->ucIpv4Cid == ucCid)
    {
        return pstCallEntity->enIpv4State;
    }

    if (pstCallEntity->ucIpv6Cid == ucCid)
    {
        return pstCallEntity->enIpv6State;
    }

    return AT_PDP_STATE_IDLE;
}

/*****************************************************************************
     : AT_PS_IsUsrDialTypeDualStack
   : 
   : VOS_UINT16                          usClientId
             VOS_UINT8                           ucCallId
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 2013425
           : l60609
       : 

*****************************************************************************/
VOS_UINT32  AT_PS_IsUsrDialTypeDualStack(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId
)
{
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;

    pstCallEntity = AT_PS_GetCallEntity(usClientId, ucCallId);

    if (TAF_PDP_IPV4V6 == pstCallEntity->stUsrDialParam.enPdpType)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
     : AT_PS_ReportDCONN
   : ^DCONN
   : ucCid          - CID
             ucPortIndex    - 
             enPdpType      - PDP
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20121217
           : Y00213812
       : 
*****************************************************************************/
VOS_VOID AT_PS_ReportDCONN(
    VOS_UINT8                           ucCid,
    VOS_UINT8                           ucPortIndex,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
)
{
    VOS_UINT16                          usLength;

    usLength = 0;

    switch (enPdpType)
    {
        case TAF_PDP_IPV4:
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%s^DCONN:%d,\"IPV4\"%s",
                                               gaucAtCrLf,
                                               ucCid,
                                               gaucAtCrLf);
            break;

        case TAF_PDP_IPV6:
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%s^DCONN:%d,\"IPV6\"%s",
                                               gaucAtCrLf,
                                               ucCid,
                                               gaucAtCrLf);
            break;

        case TAF_PDP_IPV4V6:
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%s^DCONN:%d,\"IPV4\"%s",
                                               gaucAtCrLf,
                                               ucCid,
                                               gaucAtCrLf);
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%s^DCONN:%d,\"IPV6\"%s",
                                               gaucAtCrLf,
                                               ucCid,
                                               gaucAtCrLf);
            break;

        default:
            AT_ERR_LOG("AT_PS_ReportDCONN: PDP type is invalid in ^DCONN.");
            return;
    }

    At_SendResultData(ucPortIndex, pgucAtSndCodeAddr, usLength);

    return;
}

/*****************************************************************************
     : AT_PS_ReportDend
   : ^DEND
   : ucCid       - CID
             ucPortIndex - (Client ID)
             enPdpType   - PDP
             enCause     - 
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20121217
           : Y00213812
       : 
*****************************************************************************/
VOS_VOID AT_PS_ReportDEND(
    VOS_UINT8                           ucCid,
    VOS_UINT8                           ucPortIndex,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType,
    TAF_PS_CAUSE_ENUM_UINT32            enCause
)
{
    VOS_UINT16                          usLength;

    usLength = 0;

    switch (enPdpType)
    {
        case TAF_PDP_IPV4:
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%s^DEND:%d,%d,\"IPV4\"%s",
                                               gaucAtCrLf,
                                               ucCid,
                                               enCause,
                                               gaucAtCrLf);

            break;
        case TAF_PDP_IPV6:
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%s^DEND:%d,%d,\"IPV6\"%s",
                                               gaucAtCrLf,
                                               ucCid,
                                               enCause,
                                               gaucAtCrLf);
            break;

        case TAF_PDP_IPV4V6:
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%s^DEND:%d,%d,\"IPV4\"%s",
                                               gaucAtCrLf,
                                               ucCid,
                                               enCause,
                                               gaucAtCrLf);
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%s^DEND:%d,%d,\"IPV6\"%s",
                                               gaucAtCrLf,
                                               ucCid,
                                               enCause,
                                               gaucAtCrLf);
            break;

        default:
            AT_ERR_LOG("AT_PS_ReportDEND: PDP type is invalid in ^DEND.");
            return;
    }

    At_SendResultData(ucPortIndex, pgucAtSndCodeAddr, usLength);

    return;
}

/*****************************************************************************
     : AT_PS_GetRptConnResultFunc
   : 
   : ucUsrType - 
   : 
     : AT_PS_RPT_CONN_RSLT_FUNC
   :
   :

       :
  1.       : 20121218
           : A00165503
       : 
*****************************************************************************/
AT_PS_RPT_CONN_RSLT_FUNC AT_PS_GetRptConnResultFunc(AT_USER_TYPE ucUsrType)
{
    AT_PS_REPORT_CONN_RESULT_STRU      *pstRptConnRsltFuncTblPtr = VOS_NULL_PTR;
    AT_PS_RPT_CONN_RSLT_FUNC            pRptConnRsltFunc         = VOS_NULL_PTR;
    VOS_UINT32                          ulCnt;

    pstRptConnRsltFuncTblPtr = AT_PS_GET_RPT_CONN_RSLT_FUNC_TBL_PTR();

    /*  */
    for (ulCnt = 0; ulCnt < AT_PS_GET_RPT_CONN_RSLT_FUNC_TBL_SIZE(); ulCnt++)
    {
        if (ucUsrType == pstRptConnRsltFuncTblPtr[ulCnt].ucUsrType)
        {
            pRptConnRsltFunc = pstRptConnRsltFuncTblPtr[ulCnt].pRptConnRsltFunc;
            break;
        }
    }

    return pRptConnRsltFunc;
}

/*****************************************************************************
     : AT_PS_GetRptEndResultFunc
   : 
   : ucUsrType - 
   : 
     : AT_PS_RPT_END_RSLT_FUNC
   :
   :

       :
  1.       : 20121218
           : A00165503
       : 
*****************************************************************************/
AT_PS_RPT_END_RSLT_FUNC AT_PS_GetRptEndResultFunc(AT_USER_TYPE ucUsrType)
{
    AT_PS_REPORT_END_RESULT_STRU       *pstRptEndRsltFuncTblPtr = VOS_NULL_PTR;
    AT_PS_RPT_END_RSLT_FUNC             pRptEndRsltFunc         = VOS_NULL_PTR;
    VOS_UINT32                          ulCnt;

    pstRptEndRsltFuncTblPtr = AT_PS_GET_RPT_END_RSLT_FUNC_TBL_PTR();

    /*  */
    for (ulCnt = 0; ulCnt < AT_PS_GET_RPT_END_RSLT_FUNC_TBL_SIZE(); ulCnt++)
    {
        if (ucUsrType == pstRptEndRsltFuncTblPtr[ulCnt].ucUsrType)
        {
            pRptEndRsltFunc = pstRptEndRsltFuncTblPtr[ulCnt].pRptEndRsltFunc;
            break;
        }
    }

    return pRptEndRsltFunc;
}

/*****************************************************************************
     : AT_PS_PdpAddrProc
   : IPv4
   : ucCallId      - 
             pstDhcpConfig - DCHP
             pstEvent      - 
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20121210
           : Y00213812
       : C50 IPv6 
  2.       : 20120807
           : f00179208
       : :DTS2015031000157, p-cscf
*****************************************************************************/
VOS_VOID AT_PS_PdpAddrProc(
    VOS_UINT8                           ucCallId,
    AT_DHCP_CONFIG_STRU                *pstDhcpConfig,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;
    AT_DIAL_PARAM_STRU                 *pstDialPara = VOS_NULL_PTR;
    VOS_UINT32                          ulIpAddr;
    VOS_UINT8                           ucIndex;

    pstCallEntity = AT_PS_GetCallEntity(pstEvent->stCtrl.usClientId, ucCallId);
    pstDialPara   = &pstCallEntity->stUsrDialParam;
    ulIpAddr      = 0;

    pstCallEntity->stIpv4DhcpInfo.ucRabId                 = pstEvent->ucRabId;
    pstCallEntity->stIpv4DhcpInfo.ulIpv4Addr              = pstDhcpConfig->ulIPAddr;
    pstCallEntity->stIpv4DhcpInfo.ulIpv4GateWay           = pstDhcpConfig->ulGateWay;
    pstCallEntity->stIpv4DhcpInfo.ulIpv4NetMask           = pstDhcpConfig->ulSubNetMask;

    /* DNSDNSDNS */
    if (VOS_TRUE == pstDialPara->ulPrimIPv4DNSValidFlag)
    {
        if (AT_FAILURE == AT_LenStr2IpAddr(pstDialPara->aucPrimIPv4DNSAddr,
                                           (VOS_UINT8*)&ulIpAddr))
        {
            ulIpAddr = 0;
        }

        pstCallEntity->stIpv4DhcpInfo.bitOpIpv4PriDns     = VOS_TRUE;
        pstCallEntity->stIpv4DhcpInfo.ulIpv4PrimDNS       = VOS_NTOHL(ulIpAddr);
    }
    else
    {
        if (0 != pstDhcpConfig->ulPrimDNS)
        {
            pstCallEntity->stIpv4DhcpInfo.bitOpIpv4PriDns = VOS_TRUE;
            pstCallEntity->stIpv4DhcpInfo.ulIpv4PrimDNS   = pstDhcpConfig->ulPrimDNS;
        }
        else
        {
            pstCallEntity->stIpv4DhcpInfo.bitOpIpv4PriDns = VOS_FALSE;
        }
    }

    /* DNSDNSDNS */
    if (VOS_TRUE == pstDialPara->ulSndIPv4DNSValidFlag)
    {
        if (AT_FAILURE == AT_LenStr2IpAddr(pstDialPara->aucSndIPv4DNSAddr,
                                           (VOS_UINT8*)&ulIpAddr))
        {
            ulIpAddr = 0;
        }

        pstCallEntity->stIpv4DhcpInfo.bitOpIpv4SecDns     = VOS_TRUE;
        pstCallEntity->stIpv4DhcpInfo.ulIpv4SecDNS        = VOS_NTOHL(ulIpAddr);
    }
    else
    {
        if (0 != pstDhcpConfig->ulSndDNS)
        {
            pstCallEntity->stIpv4DhcpInfo.bitOpIpv4SecDns = VOS_TRUE;
            pstCallEntity->stIpv4DhcpInfo.ulIpv4SecDNS    = pstDhcpConfig->ulSndDNS;
        }
        else
        {
            pstCallEntity->stIpv4DhcpInfo.bitOpIpv4SecDns = VOS_FALSE;
        }
    }

    pstCallEntity->stIpv4DhcpInfo.bitOpIpv4PriWINNS       = VOS_FALSE;
    pstCallEntity->stIpv4DhcpInfo.bitOpIpv4SecWINNS       = VOS_FALSE;

    /* PCSCF */
    pstCallEntity->stIpv4DhcpInfo.stIpv4PcscfList.ucIpv4PcscfAddrNum = AT_MIN(TAF_PCSCF_ADDR_MAX_NUM,
                                                                              pstEvent->stIpv4PcscfList.ucIpv4PcscfAddrNum);
    for (ucIndex = 0; ucIndex < pstEvent->stIpv4PcscfList.ucIpv4PcscfAddrNum; ucIndex++)
    {
        pstCallEntity->stIpv4DhcpInfo.stIpv4PcscfList.aulIpv4PcscfAddrList[ucIndex] = AT_GetLanAddr32(pstEvent->stIpv4PcscfList.astIpv4PcscfAddrList[ucIndex].aucPcscfAddr);
    }

    return;
}

/******************************************************************************
     : AT_PS_ProcConnInd
   : DHCP
   : ucCallId - 
             pstEvent - 
   : 
     : 
   :
   :

       :
  1.       : 20121210
           : Y00213812
       : C50 IPv6 
  2.       : 20130708
           : Y00213812
       : VoLTE_PhaseI EVENT

******************************************************************************/
VOS_VOID AT_PS_ProcConnInd(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
    AT_DHCP_SETUP_PARAM_ST              stParam;
    AT_DHCP_CONFIG_STRU                 stConfig;

    TAF_MEM_SET_S(&stParam, sizeof(stParam), 0x00, sizeof(AT_DHCP_SETUP_PARAM_ST));
    TAF_MEM_SET_S(&stConfig, sizeof(stConfig), 0x00, sizeof(AT_DHCP_CONFIG_STRU));

    /* PSDNSDNS*/
    if (pstEvent->stDns.bitOpPrimDnsAddr)
    {
        stParam.ulPrimDNS = AT_GetLanAddr32(pstEvent->stDns.aucPrimDnsAddr);
    }

    if (pstEvent->stDns.bitOpSecDnsAddr)
    {
        stParam.ulSndDNS = AT_GetLanAddr32(pstEvent->stDns.aucSecDnsAddr);
    }

    /* IP*/
    stParam.ulIPAddr = AT_GetLanAddr32(pstEvent->stPdpAddr.aucIpv4Addr);

    if (VOS_ERR == AT_DHCPServerSetUp(&stParam, &stConfig))
    {
        AT_ERR_LOG("AT_PS_ProcConnInd : ERROR AT_DHCPServerSetUp Error!" );
    }
    else
    {
        /* IPv4 */
        AT_PS_PdpAddrProc(ucCallId, &stConfig, pstEvent);
    }

    return;
}

/*****************************************************************************
     : AT_PS_SndCallConnectedResult
   : 
   : ucCallId  - 
             enPdpType - PDP
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20121217
           : Y00213812
       : 
*****************************************************************************/
VOS_VOID AT_PS_SndCallConnectedResult(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
)
{
    AT_PS_USER_INFO_STRU               *pstUsrInfo          = VOS_NULL_PTR;
    AT_PS_RPT_CONN_RSLT_FUNC            pRptConnRsltFunc    = VOS_NULL_PTR;

    /*  */
    pstUsrInfo       = AT_PS_GetUserInfo(usClientId, ucCallId);

    /*  */
    pRptConnRsltFunc = AT_PS_GetRptConnResultFunc(pstUsrInfo->ucUsrType);

    /*  */
    if (VOS_NULL_PTR != pRptConnRsltFunc)
    {
        pRptConnRsltFunc(pstUsrInfo->ucUsrCid,
                         pstUsrInfo->enPortIndex,
                         enPdpType);
    }
    else
    {
        AT_ERR_LOG("AT_PS_SndCallConnectedResult:ERROR: User type is invalid!");
    }

    return;
}

/*****************************************************************************
     : AT_PS_SndCallEndedResult
   : ^DEND
   : ucCallId  - 
             enPdpType - PDP
             enCause   - 
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20121217
           : Y00213812
       : 
*****************************************************************************/
VOS_VOID AT_PS_SndCallEndedResult(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType,
    TAF_PS_CAUSE_ENUM_UINT32            enCause
)
{
    AT_PS_USER_INFO_STRU               *pstUsrInfo      = VOS_NULL_PTR;
    AT_PS_RPT_END_RSLT_FUNC             pRptEndRsltFunc = VOS_NULL_PTR;

    /*  */
    pstUsrInfo      = AT_PS_GetUserInfo(usClientId, ucCallId);

    /*  */
    pRptEndRsltFunc = AT_PS_GetRptEndResultFunc(pstUsrInfo->ucUsrType);

    /*  */
    if (VOS_NULL_PTR != pRptEndRsltFunc)
    {
        pRptEndRsltFunc(pstUsrInfo->ucUsrCid,
                        pstUsrInfo->enPortIndex,
                        enPdpType,
                        enCause);
    }
    else
    {
        AT_ERR_LOG("AT_PS_SndCallEndedResult:ERROR: User type is invalid!");
    }

    return;
}

/*****************************************************************************
     : AT_PS_GenCallDialParam
   : PS
   : pstUsrDialParam  - 
             ucCid            - CID
             enPdpType        - PDP
   : pstCallDialParam - 
     : VOS_VOID
   :
   :

       :
  1.       : 20121220
           : A00165503
       : 
*****************************************************************************/
VOS_VOID AT_PS_GenCallDialParam(
    AT_DIAL_PARAM_STRU                 *pstCallDialParam,
    AT_DIAL_PARAM_STRU                 *pstUsrDialParam,
    VOS_UINT8                           ucCid,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
)
{
    /*  */
    *pstCallDialParam           = *pstUsrDialParam;

    /* CIDPDP */
    pstCallDialParam->ucCid     = ucCid;
    pstCallDialParam->enPdpType = enPdpType;

    return;
}

/*****************************************************************************
     : AT_PS_RegFCPoint
   : 
   : ucCallId   - ID
             pstEvent   - 
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20121210
           : Y00213812
       : C50 IPv6 
*****************************************************************************/
VOS_VOID AT_PS_RegFCPoint(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
    AT_PS_USER_INFO_STRU               *pstUserInfo = VOS_NULL_PTR;
    AT_PS_REG_FC_POINT_STRU            *pstRegFcPointFuncTblPtr = VOS_NULL_PTR;
    AT_PS_REG_FC_POINT_FUNC             pRegFcPointFunc = VOS_NULL_PTR;
    VOS_UINT32                          ulCnt;

    pstUserInfo             = AT_PS_GetUserInfo(pstEvent->stCtrl.usClientId, ucCallId);
    pstRegFcPointFuncTblPtr = AT_PS_GET_REG_FC_POINT_FUNC_TBL_PTR();

    /*  */
    for (ulCnt = 0; ulCnt < AT_PS_GET_REG_FC_POINT_FUNC_TBL_SIZE(); ulCnt++)
    {
        if (pstUserInfo->ucUsrType == pstRegFcPointFuncTblPtr[ulCnt].ucUsrType)
        {
            /*  */
            pRegFcPointFunc = pstRegFcPointFuncTblPtr[ulCnt].pRegFcPoint;
            break;
        }
    }

    /*  */
    if (VOS_NULL_PTR != pRegFcPointFunc)
    {
        pRegFcPointFunc(pstUserInfo->ucUsrCid, pstEvent);
    }
    else
    {
        AT_ERR_LOG("AT_PS_RegFCPoint:ERROR: User type is invalid!");
    }

    return;
}

/*****************************************************************************
     : AT_PS_DeRegFCPoint
   : 
   : ucCallId   - ID
             pstEvent   - 
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 2013426
           : l60609
       : C50 IPv6 
*****************************************************************************/
VOS_VOID AT_PS_DeRegFCPoint(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
)
{
    AT_PS_USER_INFO_STRU               *pstUserInfo = VOS_NULL_PTR;
    AT_PS_DEREG_FC_POINT_STRU          *pstDeRegFcPointFuncTblPtr = VOS_NULL_PTR;
    AT_PS_DEREG_FC_POINT_FUNC           pDeRegFcPointFunc = VOS_NULL_PTR;
    VOS_UINT32                          ulCnt;

    pstUserInfo               = AT_PS_GetUserInfo(pstEvent->stCtrl.usClientId, ucCallId);
    pstDeRegFcPointFuncTblPtr = AT_PS_GET_DEREG_FC_POINT_FUNC_TBL_PTR();

    /*  */
    for (ulCnt = 0; ulCnt < AT_PS_GET_DEREG_FC_POINT_FUNC_TBL_SIZE(); ulCnt++)
    {
        if (pstUserInfo->ucUsrType == pstDeRegFcPointFuncTblPtr[ulCnt].ucUsrType)
        {
            /*  */
            pDeRegFcPointFunc = pstDeRegFcPointFuncTblPtr[ulCnt].pDeRegFcPoint;
            break;
        }
    }

    /*  */
    if (VOS_NULL_PTR != pDeRegFcPointFunc)
    {
        pDeRegFcPointFunc(pstUserInfo->ucUsrCid, pstEvent);
    }
    else
    {
        AT_ERR_LOG("AT_PS_DeRegFCPoint:ERROR: User type is invalid!");
    }

    return;
}

/*****************************************************************************
     : AT_PS_SndDipcPdpActBearerTypeInd
   : ATDIPCPDP
   : ucCid          ----  CID
             pstEvent       ----  PsCallEventInfo
             enBearerType   ----  BearerType
   : 
     : 
   :
   :

       :
  1.       : 2012217
           : L47619
       : 

  2.       : 20121218
           : A00165503
       : C50 IPv6 
*****************************************************************************/
VOS_VOID  AT_PS_SndDipcPdpActBearerTypeInd(
    VOS_UINT8                           ucCid,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent,
    DIPC_BEARER_TYPE_ENUM_UINT8         enBearerType
)
{
    AT_DIPC_PDP_ACT_STRU               *pstAtDipcPdpAct = VOS_NULL_PTR;
    VOS_UINT32                          ulLength;
    AT_MODEM_PS_CTX_STRU               *pstPsModemCtx = VOS_NULL_PTR;

    ulLength        = sizeof( AT_DIPC_PDP_ACT_STRU ) - VOS_MSG_HEAD_LENGTH;
    pstAtDipcPdpAct = ( AT_DIPC_PDP_ACT_STRU *)PS_ALLOC_MSG( WUEPS_PID_AT, ulLength );

    if (VOS_NULL_PTR == pstAtDipcPdpAct)
    {
        /*---:*/
        AT_WARN_LOG( "AT_PS_SndDipcPdpActInd:ERROR:Allocates a message packet for AT_DIPC_PDP_ACT_STRU FAIL!" );
        return;
    }

    pstPsModemCtx = AT_GetModemPsCtxAddrFromClientId(pstEvent->stCtrl.usClientId);

    /*:*/
    pstAtDipcPdpAct->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstAtDipcPdpAct->ulSenderPid     = WUEPS_PID_AT;
    pstAtDipcPdpAct->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstAtDipcPdpAct->ulReceiverPid   = PS_PID_APP_DIPC;
    pstAtDipcPdpAct->ulLength        = ulLength;
    /*:*/
    pstAtDipcPdpAct->enMsgType       = ID_AT_DIPC_PDP_ACT_IND;
    pstAtDipcPdpAct->ucRabId         = pstEvent->ucRabId;
    pstAtDipcPdpAct->enBearerType    = enBearerType;
    pstAtDipcPdpAct->enUdiDevId      = (UDI_DEVICE_ID_E)pstPsModemCtx->astChannelCfg[ucCid].ulRmNetId;

    /*:*/
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_AT, pstAtDipcPdpAct))
    {
        /*---:*/
        AT_WARN_LOG( "AT_PS_SndDipcPdpActInd:WARNING:SEND AT_DIPC_PDP_ACT_STRU msg FAIL!" );
    }

    return;
}

/*****************************************************************************
     : AT_PS_SndDipcPdpActInd
   : ATDIPCPDP
   : usClientId     ----  CLIENT ID
             ucCid          ----  CID
             ucRabId        ----  RABID
             enBearerType   ----  BearerType
   : 
     : 
   :
   :

       :
  1.       : 2012217
           : L47619
       : 

  2.       : 20121218
           : A00165503
       : C50 IPv6 
*****************************************************************************/
VOS_VOID  AT_PS_SndDipcPdpActInd(
    VOS_UINT8                           ucCid,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
)
{
    /* DIPCPDP IPv4 */
    if (TAF_PDP_IPV4 == (enPdpType & TAF_PDP_IPV4))
    {
        AT_PS_SndDipcPdpActBearerTypeInd(ucCid,
                                         pstEvent,
                                         DIPC_BEARER_TYPE_IPV4);
    }

    /* DIPCPDP IPv6 */
    if (TAF_PDP_IPV6 == (enPdpType & TAF_PDP_IPV6))
    {
        AT_PS_SndDipcPdpActBearerTypeInd(ucCid,
                                         pstEvent,
                                         DIPC_BEARER_TYPE_IPV6);
    }

    return;
}

/*****************************************************************************
     : AT_PS_SndDipcPdpDeactBearerTypeInd
   : ATDIPCPDP
   : TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent,
             DIPC_BEARER_TYPE_ENUM_UINT8         enBearerType
   : 
     : 
   :
   :

       :
  1.       : 2012217
           : L47619
       : 

  2.       : 20121218
           : A00165503
       : C50 IPv6 
*****************************************************************************/
VOS_VOID  AT_PS_SndDipcPdpDeactBearerTypeInd(
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent,
    DIPC_BEARER_TYPE_ENUM_UINT8         enBearerType
)
{
    AT_DIPC_PDP_DEACT_STRU             *pstAtDipcPdpDeact = VOS_NULL_PTR;
    VOS_UINT32                          ulLength;

    ulLength          = sizeof( AT_DIPC_PDP_DEACT_STRU ) - VOS_MSG_HEAD_LENGTH;
    pstAtDipcPdpDeact = (AT_DIPC_PDP_DEACT_STRU *)PS_ALLOC_MSG(WUEPS_PID_AT, ulLength);

    if (VOS_NULL_PTR == pstAtDipcPdpDeact)
    {
        /*---:*/
        AT_WARN_LOG( "AT_PS_SndDipcPdpDeactInd:ERROR:Allocates a message packet for AT_DIPC_PDP_DEACT_STRU FAIL!" );
        return;
    }

    /*:*/
    pstAtDipcPdpDeact->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstAtDipcPdpDeact->ulSenderPid     = WUEPS_PID_AT;
    pstAtDipcPdpDeact->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstAtDipcPdpDeact->ulReceiverPid   = PS_PID_APP_DIPC;
    pstAtDipcPdpDeact->ulLength        = ulLength;
    /*:*/
    pstAtDipcPdpDeact->enMsgType       = ID_AT_DIPC_PDP_REL_IND;
    pstAtDipcPdpDeact->ucRabId         = pstEvent->ucRabId;
    pstAtDipcPdpDeact->enBearerType    = enBearerType;

    /*:*/
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_AT, pstAtDipcPdpDeact))
    {
        /*---:*/
        AT_WARN_LOG( "AT_PS_SndDipcPdpDeactInd:WARNING:SEND AT_DIPC_PDP_DEACT_STRU msg FAIL!" );
    }

    return;
}

/*****************************************************************************
     : AT_PS_SndDipcPdpDeactInd
   : ATDIPCPDP
   : VOS_UINT8                           ucCid,
             TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent,
             TAF_PDP_TYPE_ENUM_UINT8             enPdpType
   : 
     : 
   :
   :

       :
  1.       : 2012217
           : L47619
       : 

  2.       : 20121218
           : A00165503
       : C50 IPv6 
*****************************************************************************/
VOS_VOID  AT_PS_SndDipcPdpDeactInd(
    VOS_UINT8                           ucCid,
    TAF_PS_CALL_PDP_DEACTIVATE_IND_STRU *pstEvent,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
)
{
    /* DIPCPDP IPv4 */
    if (TAF_PDP_IPV4 == (enPdpType & TAF_PDP_IPV4))
    {
        AT_PS_SndDipcPdpDeactBearerTypeInd(pstEvent,
                                           DIPC_BEARER_TYPE_IPV4);
    }

    /* DIPCPDP IPv6 */
    if (TAF_PDP_IPV6 == (enPdpType & TAF_PDP_IPV6))
    {
        AT_PS_SndDipcPdpDeactBearerTypeInd(pstEvent,
                                           DIPC_BEARER_TYPE_IPV6);
    }

    return;
}

/*****************************************************************************
     : AT_PS_SndRnicIpv4PdpActInd
   : RNICPDP, IPv4
   : VOS_UINT8                           ucCid
             TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 2013426
           : l60609
       : 

*****************************************************************************/
VOS_VOID AT_PS_SndRnicIpv4PdpActInd(
    VOS_UINT8                           ucCid,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU *pstEvent
)
{
    AT_RNIC_IPV4_PDP_ACT_IND_STRU      *pstMsg;

    AT_MODEM_PS_CTX_STRU               *pstPsModemCtx = VOS_NULL_PTR;

    pstPsModemCtx = AT_GetModemPsCtxAddrFromClientId(pstEvent->stCtrl.usClientId);

    /*  */
    if (pstPsModemCtx->astChannelCfg[ucCid].ulRmNetId >= RNIC_RMNET_ID_BUTT)
    {
        return;
    }

    /* AT_RNIC_IPV4_PDP_ACT_IND_STRU */
    pstMsg = (AT_RNIC_IPV4_PDP_ACT_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                            WUEPS_PID_AT,
                            sizeof(AT_RNIC_IPV4_PDP_ACT_IND_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        AT_WARN_LOG("AT_PS_SndRnicIpv4PdpActInd: alloc msg fail!");
        return;
    }

    /*  */
    TAF_MEM_SET_S((VOS_CHAR*)pstMsg + VOS_MSG_HEAD_LENGTH,
               (VOS_SIZE_T)(sizeof(AT_RNIC_IPV4_PDP_ACT_IND_STRU) - VOS_MSG_HEAD_LENGTH),
               0x00,
               (VOS_SIZE_T)(sizeof(AT_RNIC_IPV4_PDP_ACT_IND_STRU) - VOS_MSG_HEAD_LENGTH));

    /*  */
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = ACPU_PID_RNIC;
    pstMsg->enMsgId         = ID_AT_RNIC_IPV4_PDP_ACT_IND;

    /* rab id */
    pstMsg->ucRabId         = pstEvent->ucRabId;

    /* rmnet idchdata */
    pstMsg->ucRmNetId       = (VOS_UINT8)pstPsModemCtx->astChannelCfg[ucCid].ulRmNetId;



    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_AT, pstMsg))
    {
        AT_WARN_LOG("AT_PS_SndRnicIpv4PdpActInd: Send msg fail!");
    }

    return;
}

/*****************************************************************************
     : AT_PS_SndRnicIpv6PdpActInd
   : RNICPDP, IPv6
   : VOS_UINT8                           ucCid
             TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 2013426
           : l60609
       : 

*****************************************************************************/
VOS_VOID AT_PS_SndRnicIpv6PdpActInd(
    VOS_UINT8                           ucCid,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
    AT_RNIC_IPV6_PDP_ACT_IND_STRU      *pstMsg;

    AT_MODEM_PS_CTX_STRU               *pstPsModemCtx = VOS_NULL_PTR;

    pstPsModemCtx = AT_GetModemPsCtxAddrFromClientId(pstEvent->stCtrl.usClientId);

    /*  */
    if (pstPsModemCtx->astChannelCfg[ucCid].ulRmNetId >= RNIC_RMNET_ID_BUTT)
    {
        return;
    }

    /* AT_RNIC_IPV6_PDP_ACT_IND_STRU */
    pstMsg = (AT_RNIC_IPV6_PDP_ACT_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                            WUEPS_PID_AT,
                            sizeof(AT_RNIC_IPV6_PDP_ACT_IND_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        AT_WARN_LOG("AT_PS_SndRnicIpv6PdpActInd: alloc msg fail!");
        return;
    }

    /*  */
    TAF_MEM_SET_S((VOS_CHAR*)pstMsg + VOS_MSG_HEAD_LENGTH,
               (VOS_SIZE_T)(sizeof(AT_RNIC_IPV6_PDP_ACT_IND_STRU) - VOS_MSG_HEAD_LENGTH),
               0x00,
               (VOS_SIZE_T)(sizeof(AT_RNIC_IPV6_PDP_ACT_IND_STRU) - VOS_MSG_HEAD_LENGTH));

    /*  */
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = ACPU_PID_RNIC;
    pstMsg->enMsgId         = ID_AT_RNIC_IPV6_PDP_ACT_IND;

    /* rab id */
    pstMsg->ucRabId         = pstEvent->ucRabId;

    /* rmnet idchdata */
    pstMsg->ucRmNetId       = (VOS_UINT8)pstPsModemCtx->astChannelCfg[ucCid].ulRmNetId;



    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_AT, pstMsg))
    {
        AT_WARN_LOG("AT_PS_SndRnicIpv6PdpActInd: Send msg fail!");
    }

    return;
}

/*****************************************************************************
     : AT_PS_SndRnicPdpActInd
   : PDPRNIC
   : VOS_UINT8                           ucCid
             TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
             TAF_PDP_TYPE_ENUM_UINT8             enPdpType
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 201357
           : l60609
       : 

*****************************************************************************/
VOS_VOID AT_PS_SndRnicPdpActInd(
    VOS_UINT8                           ucCid,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
)
{
    /* DIPCPDP IPv4 */
    if (TAF_PDP_IPV4 == (enPdpType & TAF_PDP_IPV4))
    {
        AT_PS_SndRnicIpv4PdpActInd(ucCid, pstEvent);
    }

    /* DIPCPDP IPv6 */
    if (TAF_PDP_IPV6 == (enPdpType & TAF_PDP_IPV6))
    {
        AT_PS_SndRnicIpv6PdpActInd(ucCid, pstEvent);
    }

    return;

}

/*****************************************************************************
     : AT_PS_SndRnicPdpDeactInd
   : APP
   : VOS_UINT8                           ucRabId
             VOS_UINT8                           ucRmNetId
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 2013426
           : l60609
       : 

*****************************************************************************/
VOS_VOID AT_PS_SndRnicPdpDeactInd(
    VOS_UINT8                           ucCid,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
)
{
    AT_RNIC_PDP_DEACT_IND_STRU         *pstMsg;
    AT_MODEM_PS_CTX_STRU               *pstPsModemCtx = VOS_NULL_PTR;

    pstPsModemCtx = AT_GetModemPsCtxAddrFromClientId(pstEvent->stCtrl.usClientId);

    /*  */
    if (pstPsModemCtx->astChannelCfg[ucCid].ulRmNetId >= RNIC_RMNET_ID_BUTT)
    {
        return;
    }

    /* AT_NDIS_PDP_DEACT_IND_STRU */
    pstMsg = (AT_RNIC_PDP_DEACT_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                            WUEPS_PID_AT,
                            sizeof(AT_RNIC_PDP_DEACT_IND_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        AT_WARN_LOG("AT_NotifyRnicPdpDeactInd: alloc msg fail!");
        return;
    }

    /*  */
    TAF_MEM_SET_S((VOS_CHAR*)pstMsg + VOS_MSG_HEAD_LENGTH,
               (VOS_SIZE_T)(sizeof(AT_RNIC_PDP_DEACT_IND_STRU) - VOS_MSG_HEAD_LENGTH),
               0x00,
               (VOS_SIZE_T)(sizeof(AT_RNIC_PDP_DEACT_IND_STRU) - VOS_MSG_HEAD_LENGTH));

    /*  */
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = ACPU_PID_RNIC;
    pstMsg->enMsgId         = ID_AT_RNIC_PDP_DEACT_IND;

    /*  rab id */
    pstMsg->ucRabId         = pstEvent->ucRabId;

    /*  rmnet idchdata */
    pstMsg->ucRmNetId       = (VOS_UINT8)pstPsModemCtx->astChannelCfg[ucCid].ulRmNetId;

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_AT, pstMsg))
    {
        AT_WARN_LOG("AT_NotifyRnicPdpDeactInd: Send msg fail!");
        return;
    }

    return;
}

/*****************************************************************************
     : AT_PS_ActivateRmNet
   : PDP
   : VOS_UINT8                           ucCallId
             TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
             TAF_PDP_TYPE_ENUM_UINT8             enPdpType
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 2013426
           : l60609
       : 

*****************************************************************************/
VOS_VOID AT_PS_ActivateRmNet(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
)
{
    AT_PS_USER_INFO_STRU               *pstUserInfo = VOS_NULL_PTR;
    AT_PS_SND_PDP_ACT_IND_STRU         *pstSndPdpActIndFuncTblPtr = VOS_NULL_PTR;
    AT_PS_SND_PDP_ACT_IND_FUNC          pSndPdpActIndFunc = VOS_NULL_PTR;
    VOS_UINT32                          ulCnt;

    pstUserInfo               = AT_PS_GetUserInfo(pstEvent->stCtrl.usClientId, ucCallId);
    pstSndPdpActIndFuncTblPtr = AT_PS_GET_SND_PDP_ACT_IND_FUNC_TBL_PTR();

    /*  */
    for (ulCnt = 0; ulCnt < AT_PS_GET_SND_PDP_ACT_IND_FUNC_TBL_SIZE(); ulCnt++)
    {
        if (pstUserInfo->ucUsrType == pstSndPdpActIndFuncTblPtr[ulCnt].ucUsrType)
        {
            /*  */
            pSndPdpActIndFunc = pstSndPdpActIndFuncTblPtr[ulCnt].pSndPdpActInd;
            break;
        }
    }

    /*  */
    if (VOS_NULL_PTR != pSndPdpActIndFunc)
    {
        pSndPdpActIndFunc(pstUserInfo->ucUsrCid, pstEvent, enPdpType);
    }
    else
    {
        AT_ERR_LOG("AT_PS_ActivateRmNet:ERROR: User type is invalid!");
    }

    return;
}

/*****************************************************************************
     : AT_PS_DeactivateRmNet
   : PDP
   : VOS_UINT8                           ucCallId
             TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
             TAF_PDP_TYPE_ENUM_UINT8             enPdpType
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 2013426
           : l60609
       : 

*****************************************************************************/
VOS_VOID AT_PS_DeactivateRmNet(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
)
{
    AT_PS_USER_INFO_STRU               *pstUserInfo = VOS_NULL_PTR;
    AT_PS_SND_PDP_DEACT_IND_STRU       *pstSndPdpDeActIndFuncTblPtr = VOS_NULL_PTR;
    AT_PS_SND_PDP_DEACT_IND_FUNC        pSndPdpDeActIndFunc = VOS_NULL_PTR;
    VOS_UINT32                          ulCnt;

    pstUserInfo                 = AT_PS_GetUserInfo(pstEvent->stCtrl.usClientId, ucCallId);
    pstSndPdpDeActIndFuncTblPtr = AT_PS_GET_SND_PDP_DEACT_IND_FUNC_TBL_PTR();

    /*  */
    for (ulCnt = 0; ulCnt < AT_PS_GET_SND_PDP_DEACT_IND_FUNC_TBL_SIZE(); ulCnt++)
    {
        if (pstUserInfo->ucUsrType == pstSndPdpDeActIndFuncTblPtr[ulCnt].ucUsrType)
        {
            /*  */
            pSndPdpDeActIndFunc = pstSndPdpDeActIndFuncTblPtr[ulCnt].pSndPdpDeActInd;
            break;
        }
    }

    /*  */
    if (VOS_NULL_PTR != pSndPdpDeActIndFunc)
    {
        pSndPdpDeActIndFunc(pstUserInfo->ucUsrCid, pstEvent, enPdpType);
    }
    else
    {
        AT_ERR_LOG("AT_PS_DeactivateRmNet:ERROR: User type is invalid!");
    }

    return;
}

/*****************************************************************************
     : AT_PS_IsIpv6CapabilityValid
   : ipv6
   : VOS_UINT8 ucCapability
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 201357
           : l60609
       : 

*****************************************************************************/
VOS_UINT32 AT_PS_IsIpv6CapabilityValid(VOS_UINT8 ucCapability)
{
    if ((AT_IPV6_CAPABILITY_IPV4_ONLY == ucCapability)
     || (AT_IPV6_CAPABILITY_IPV6_ONLY == ucCapability)
     || (AT_IPV6_CAPABILITY_IPV4V6_OVER_ONE_PDP == ucCapability))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
     : AT_PS_IsIpv6Support
   : IPV6
   : VOS_VOID
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 201352
           : L60609
       : 

*****************************************************************************/
VOS_UINT32 AT_PS_IsIpv6Support(VOS_VOID)
{
    VOS_UINT8                           ucIpv6Capability;

    ucIpv6Capability = AT_GetCommPsCtxAddr()->ucIpv6Capability;

    if ((AT_IPV6_CAPABILITY_IPV6_ONLY == ucIpv6Capability)
     || (AT_IPV6_CAPABILITY_IPV4V6_OVER_ONE_PDP == ucIpv6Capability))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}
/*****************************************************************************
     : AT_PS_GenIpv6LanAddrWithRadomIID
   : IPv6
   : pucPrefix          - 
             ulPrefixByteLen    - 
             pucIpv6LanAddr     - IPv6
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 20121218
           : A00165503
       : C50 IPv6 
*****************************************************************************/
VOS_UINT32 AT_PS_GenIpv6LanAddrWithRadomIID(
    VOS_UINT8                          *pucPrefix,
    VOS_UINT32                          ulPrefixByteLen,
    VOS_UINT8                          *pucIpv6LanAddr
)
{
    VOS_UINT32                         *paulAddr = VOS_NULL_PTR;
    VOS_UINT32                          ulTick;

    paulAddr = (VOS_UINT32 *)pucIpv6LanAddr;

    if (ulPrefixByteLen > AT_IPV6_ADDR_PREFIX_BYTE_LEN)
    {
        return VOS_ERR;
    }

    /* IPv6 */
    TAF_MEM_CPY_S(pucIpv6LanAddr, TAF_IPV6_ADDR_LEN, pucPrefix, ulPrefixByteLen);

    ulTick = VOS_GetTick();

    /* PC */
    VOS_SetSeed(ulTick);
    paulAddr[2] = VOS_Rand(0xFFFFFFFFU);

    VOS_SetSeed(ulTick + 10);
    paulAddr[3] = VOS_Rand(0xFFFFFFFFU);


    *(VOS_UINT8 *)(&paulAddr[2]) &= ~0x02;

    return VOS_OK;
}

/*****************************************************************************
     : AT_PS_SaveIPv6Dns
   : IPV6DNSPDP
   : ucCallId   - ID
             pstEvent   - 
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20121210
           : Y00213812
       : C50 IPv6 
  2.       : 20130708
           : Y00213812
       : VoLTE_PhaseI EVENT

*****************************************************************************/
VOS_VOID  AT_PS_SaveIPv6Dns(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;

    pstCallEntity = AT_PS_GetCallEntity(pstEvent->stCtrl.usClientId, ucCallId);

    pstCallEntity->stIpv6DhcpInfo.bitOpIpv6PriDns    = VOS_FALSE;
    pstCallEntity->stIpv6DhcpInfo.bitOpIpv6SecDns    = VOS_FALSE;

    /* Modified by Y00213812 for VoLTE_PhaseI , 2013-07-08, begin */
    /* DNSRADRV */
    if (VOS_TRUE == pstEvent->stIpv6Dns.bitOpPrimDnsAddr)
    {
        TAF_MEM_CPY_S((VOS_VOID*)pstCallEntity->stIpv6DhcpInfo.aucIpv6PrimDNS,
                sizeof(pstCallEntity->stIpv6DhcpInfo.aucIpv6PrimDNS),
                pstEvent->stIpv6Dns.aucPrimDnsAddr,
                AT_MAX_IPV6_DNS_LEN);
        pstCallEntity->stIpv6DhcpInfo.bitOpIpv6PriDns = VOS_TRUE;
    }

    if (VOS_TRUE == pstEvent->stIpv6Dns.bitOpSecDnsAddr)
    {
        TAF_MEM_CPY_S((VOS_VOID*)pstCallEntity->stIpv6DhcpInfo.aucIpv6SecDNS,
                   sizeof(pstCallEntity->stIpv6DhcpInfo.aucIpv6SecDNS),
                   pstEvent->stIpv6Dns.aucSecDnsAddr,
                   AT_MAX_IPV6_DNS_LEN);
        pstCallEntity->stIpv6DhcpInfo.bitOpIpv6SecDns = VOS_TRUE;
    }
    /* Modified by Y00213812 for VoLTE_PhaseI , 2013-07-08, end */

}

/*****************************************************************************
     : AT_PS_SaveIPv6Pcscf
   : IPV6PcscfPDP
   : ucCallId   - ID
             pstEvent   - 
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20121210
           : Y00213812
       : C50 IPv6 
  2.       : 20120807
           : f00179208
       : :DTS2015031000157, p-cscf
*****************************************************************************/
VOS_VOID  AT_PS_SaveIPv6Pcscf(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;

    pstCallEntity = AT_PS_GetCallEntity(pstEvent->stCtrl.usClientId, ucCallId);

    pstCallEntity->stIpv6DhcpInfo.stIpv6PcscfList.ucIpv6PcscfAddrNum = AT_MIN(TAF_PCSCF_ADDR_MAX_NUM,
                                                                              pstEvent->stIpv6PcscfList.ucIpv6PcscfAddrNum);

    for (ucIndex = 0; ucIndex < pstCallEntity->stIpv6DhcpInfo.stIpv6PcscfList.ucIpv6PcscfAddrNum; ucIndex++)
    {
        TAF_MEM_CPY_S(pstCallEntity->stIpv6DhcpInfo.stIpv6PcscfList.astIpv6PcscfAddrList[ucIndex].aucPcscfAddr,
                      TAF_IPV6_ADDR_LEN,
                      pstEvent->stIpv6PcscfList.astIpv6PcscfAddrList[ucIndex].aucPcscfAddr,
                      TAF_IPV6_ADDR_LEN);
    }
}

/*****************************************************************************
     : AT_PS_ProcConnectedIpv6Addr
   : IPv6
   : ucCallId   - ID
             pstEvent   - 
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20121210
           : Y00213812
       : C50 IPv6 

*****************************************************************************/
VOS_VOID AT_PS_ProcConnectedIpv6Addr(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;

    pstCallEntity = AT_PS_GetCallEntity(pstEvent->stCtrl.usClientId, ucCallId);

    pstCallEntity->stIpv6DhcpInfo.ucRabId  = pstEvent->ucRabId;

    /* IPv6IP */
    TAF_MEM_CPY_S(pstCallEntity->stIpv6DhcpInfo.aucIpv6Addr,
               sizeof(pstCallEntity->stIpv6DhcpInfo.aucIpv6Addr),
               pstEvent->stPdpAddr.aucIpv6Addr,
               TAF_IPV6_ADDR_LEN);

    /* IPV6DNS */
    AT_PS_SaveIPv6Dns(ucCallId, pstEvent);

    /* IPV6PCSCF */
    AT_PS_SaveIPv6Pcscf(ucCallId, pstEvent);

    return;
}

/*****************************************************************************
     : AT_PS_ProcIpv6RaInfo
   : Router Advertisement IP, 
   : pstRaInfoNotifyInd - RA
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20121210
           : Y00213812
       : C50 IPv6 

  2.       : 20130121
           : A00165503
       : DTS2013011803709: IPv6
*****************************************************************************/
VOS_VOID AT_PS_ProcIpv6RaInfo(TAF_PS_IPV6_INFO_IND_STRU *pstRaInfoNotifyInd)
{
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;
    AT_IPV6_RA_INFO_STRU               *pstIpv6RaInfo = VOS_NULL_PTR;
    VOS_UINT32                          ulIpv6AddrTestModeCfg;
    AT_COMM_PS_CTX_STRU                *pstCommPsCtx = VOS_NULL_PTR;
    VOS_UINT8                           aucIpv6LanAddr[TAF_IPV6_ADDR_LEN] = {0};
    VOS_UINT8                           ucCallId;

    pstCommPsCtx          = AT_GetCommPsCtxAddr();
    ulIpv6AddrTestModeCfg = pstCommPsCtx->ulIpv6AddrTestModeCfg;

    ucCallId = AT_PS_TransCidToCallId(pstRaInfoNotifyInd->stCtrl.usClientId, pstRaInfoNotifyInd->ucCid);

    if (VOS_FALSE == AT_PS_IsCallIdValid(pstRaInfoNotifyInd->stCtrl.usClientId, ucCallId))
    {
        AT_ERR_LOG("AT_PS_ProcIpv6RaInfo: CallId is invalid!");
        return;
    }

    pstCallEntity = AT_PS_GetCallEntity(pstRaInfoNotifyInd->stCtrl.usClientId, ucCallId);
    pstIpv6RaInfo = &pstCallEntity->stIpv6RaInfo;

    if (0 == pstRaInfoNotifyInd->stIpv6RaInfo.ulPrefixNum)
    {
        AT_NORM_LOG("AT_PS_ProcIpv6RaInfo: No IPv6 prefix address in RA.");
        return;
    }

    /* IPv6, ^DCONN */
    if (VOS_FALSE == pstIpv6RaInfo->bitOpPrefixAddr)
    {
        /* IPv6 */
        AT_PS_SndCallConnectedResult(pstRaInfoNotifyInd->stCtrl.usClientId, ucCallId, TAF_PDP_IPV6);

        /* IPv6 */
        pstIpv6RaInfo->bitOpPrefixAddr    = VOS_TRUE;
        pstIpv6RaInfo->ulPrefixBitLen     = pstRaInfoNotifyInd->stIpv6RaInfo.astPrefixList[0].ulBitPrefixLen;
        TAF_MEM_CPY_S(pstIpv6RaInfo->aucPrefixAddr,
                   sizeof(pstIpv6RaInfo->aucPrefixAddr),
                   pstRaInfoNotifyInd->stIpv6RaInfo.astPrefixList[0].aucPrefix,
                   TAF_IPV6_ADDR_LEN);

        /* IPv6 */
        if (VOS_TRUE == AT_IsApPort((VOS_UINT8)pstRaInfoNotifyInd->stCtrl.usClientId))
        {
            AT_PS_GenIpv6LanAddrWithRadomIID(pstRaInfoNotifyInd->stIpv6RaInfo.astPrefixList[0].aucPrefix,
                                             pstRaInfoNotifyInd->stIpv6RaInfo.astPrefixList[0].ulBitPrefixLen/8,
                                             aucIpv6LanAddr);
        }
        else
        {
            AT_CalcIpv6LanAddrFromIpv6Prefix(pstRaInfoNotifyInd->stIpv6RaInfo.astPrefixList[0].aucPrefix,
                                             pstRaInfoNotifyInd->stIpv6RaInfo.astPrefixList[0].ulBitPrefixLen/8,
                                             aucIpv6LanAddr,
                                             TAF_IPV6_ADDR_LEN);
        }

        /* IPv6 */
        pstIpv6RaInfo->bitOpLanAddr       = VOS_TRUE;
        TAF_MEM_CPY_S(pstIpv6RaInfo->aucLanAddr, sizeof(pstIpv6RaInfo->aucLanAddr), aucIpv6LanAddr, TAF_IPV6_ADDR_LEN);

        /* DHCPV6IPv6 */
        if ((IPV6_ADDRESS_TEST_MODE_ENABLE == ulIpv6AddrTestModeCfg)
         && (AT_PS_IS_IPV6_ADDR_IID_VALID(pstCallEntity->stIpv6DhcpInfo.aucIpv6Addr)))
        {
            TAF_MEM_CPY_S(pstCallEntity->stIpv6DhcpInfo.aucIpv6Addr,
                       sizeof(pstCallEntity->stIpv6DhcpInfo.aucIpv6Addr),
                       pstRaInfoNotifyInd->stIpv6RaInfo.astPrefixList[0].aucPrefix,
                       pstRaInfoNotifyInd->stIpv6RaInfo.astPrefixList[0].ulBitPrefixLen/8);
        }
        else
        {
            TAF_MEM_CPY_S(pstCallEntity->stIpv6DhcpInfo.aucIpv6Addr, sizeof(pstCallEntity->stIpv6DhcpInfo.aucIpv6Addr), aucIpv6LanAddr, TAF_IPV6_ADDR_LEN);
        }
    }

    /* Preferred Lifetime */
    pstIpv6RaInfo->bitOpPreferredLifetime = VOS_TRUE;
    pstIpv6RaInfo->ulPreferredLifetime    = pstRaInfoNotifyInd->stIpv6RaInfo.astPrefixList[0].ulPreferredLifeTime;

    /* Valid Lifetime */
    pstIpv6RaInfo->bitOpValidLifetime     = VOS_TRUE;
    pstIpv6RaInfo->ulValidLifetime        = pstRaInfoNotifyInd->stIpv6RaInfo.astPrefixList[0].ulValidLifeTime;

    /* IPv6 MTU */
    if (VOS_TRUE == pstRaInfoNotifyInd->stIpv6RaInfo.bitOpMtu)
    {
        pstIpv6RaInfo->bitOpMtuSize       = VOS_TRUE;
        pstIpv6RaInfo->ulMtuSize          = pstRaInfoNotifyInd->stIpv6RaInfo.ulMtu;
    }

    return;
}

/*****************************************************************************
     : AT_PS_MatchIpv4v6ConnFailFallbackCause
   : IPv4v6
   : enCause   - 
   : 
     : VOS_TRUE  - 
             VOS_FALSE - 
   :
   :

       :
  1.       : 20121218
           : A00165503
       : 
*****************************************************************************/
VOS_UINT32 AT_PS_MatchIpv4v6ConnFailFallbackCause(
    TAF_PS_CAUSE_ENUM_UINT32            enCause
)
{
    AT_PS_IPV6_BACKPROC_EXT_CAUSE_STRU *pstBackProcExtCause = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;
    VOS_UINT32                          ulCnt;

    ulRslt = VOS_FALSE;

    /* #28 */
    if (TAF_PS_CAUSE_SM_NW_UNKNOWN_PDP_ADDR_OR_TYPE == enCause)
    {
        ulRslt = VOS_TRUE;
    }

    /*  */
    pstBackProcExtCause = &(AT_GetCommPsCtxAddr()->stIpv6BackProcExtCauseTbl);

    for (ulCnt = 0; ulCnt < pstBackProcExtCause->ulCauseNum; ulCnt++)
    {
        if (pstBackProcExtCause->aenPsCause[ulCnt] == enCause)
        {
            ulRslt = VOS_TRUE;
            break;
        }
    }

    return ulRslt;
}

/*****************************************************************************
     : AT_PS_SetupSingleStackConn
   : 
   : ucCallId  - 
             enPdpType - PDP(IPv4 or IPv6)
   : 
     : VOS_OK    - 
             VOS_ERR   - 
   :
   :

       :
  1.       : 20121218
           : A00165503
       : 
*****************************************************************************/
VOS_UINT32 AT_PS_SetupSingleStackConn(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
)
{
    AT_DIAL_PARAM_STRU                 *pstUsrDialParam = VOS_NULL_PTR;
    AT_DIAL_PARAM_STRU                  stCallDialParam;
    AT_PDP_STATE_ENUM_U8                enCallState;
    VOS_UINT8                           ucCid;
    VOS_UINT32                          ulRslt;

    TAF_MEM_SET_S(&stCallDialParam, sizeof(stCallDialParam), 0x00, sizeof(AT_DIAL_PARAM_STRU));

    ulRslt          = VOS_ERR;
    ucCid           = 0;
    pstUsrDialParam = &(AT_PS_GetCallEntity(usClientId, ucCallId)->stUsrDialParam);
    enCallState     = AT_PS_GetCallStateByType(usClientId, ucCallId, enPdpType);

    if (AT_PDP_STATE_IDLE == enCallState)
    {
        /* CID */
        if (VOS_OK == TAF_AGENT_FindCidForDial(usClientId, &ucCid))
        {
            /*  */
            AT_PS_GenCallDialParam(&stCallDialParam,
                                   pstUsrDialParam,
                                   ucCid,
                                   enPdpType);

            /*  */
            if (VOS_OK == AT_PS_SetupCall(usClientId, ucCallId, &stCallDialParam))
            {
                ulRslt = VOS_OK;
            }
        }
    }
    else
    {
        ulRslt = VOS_OK;
    }

    return ulRslt;
}

/*****************************************************************************
     : AT_PS_HangupSingleStackConn
   : 
   : ucCallId  - 
             enPdpType - PDP(IPv4 or IPv6)
   : 
     : VOS_OK    - 
             VOS_ERR   - 
   :
   :

       :
  1.       : 20121218
           : A00165503
       : 
*****************************************************************************/
VOS_UINT32 AT_PS_HangupSingleStackConn(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
)
{
    VOS_UINT32                          ulRslt;
    AT_PDP_STATE_ENUM_U8                enCallState;
    VOS_UINT8                           ucCid;

    ulRslt      = VOS_ERR;
    ucCid       = AT_PS_GetCidByCallType(usClientId, ucCallId, enPdpType);
    enCallState = AT_PS_GetCallStateByType(usClientId, ucCallId, enPdpType);

    switch (enCallState)
    {
        case AT_PDP_STATE_ACTED:
        case AT_PDP_STATE_ACTING:
            if (VOS_OK == TAF_PS_CallEnd(WUEPS_PID_AT,
                                         AT_PS_BuildExClientId(usClientId),
                                         0,
                                         ucCid))
            {
                ulRslt = VOS_OK;

                AT_PS_SetCallStateByType(usClientId, ucCallId, enPdpType, AT_PDP_STATE_DEACTING);
            }
            else
            {
                AT_ERR_LOG("AT_PS_HangupSingleStackConn: Hangup call failed!");
            }
            break;

        case AT_PDP_STATE_DEACTING:
            ulRslt = VOS_OK;
            break;

        case AT_PDP_STATE_IDLE:
        default:
            break;
    }

    return ulRslt;
}

/*****************************************************************************
     : AT_PS_ProcDualStackCallConn
   : PDP
   : ucCallId   - ID
             pstEvent   - 
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20121210
           : Y00213812
       : C50 IPv6 
  2.       : 20130708
           : Y00213812
       : VoLTE_PhaseI EVENT

  3.       : 2015717
           : Y00213812
       : CDMA
*****************************************************************************/
VOS_VOID AT_PS_ProcDualStackCallConn(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
    AT_COMM_PS_CTX_STRU                *pstCommPsCtx = VOS_NULL_PTR;

    pstCommPsCtx = AT_GetCommPsCtxAddr();

    /* #52PDP */
    if ( (VOS_FALSE == pstEvent->bitOpCause)
      || ( (VOS_TRUE == pstEvent->bitOpCause)
        && (TAF_PS_CAUSE_SM_NW_SINGLE_ADDR_BEARERS_ONLY_ALLOWED == pstEvent->enCause) ) )
    {
        switch (pstEvent->stPdpAddr.enPdpType)
        {
            case TAF_PDP_IPV4:
                if ((VOS_FALSE == pstEvent->bitOpCause)
                 && (VOS_FALSE == pstCommPsCtx->ucRedialForNoCauseFlag))
                {
                    AT_PS_SndCallEndedResult(pstEvent->stCtrl.usClientId,
                                             ucCallId,
                                             TAF_PDP_IPV6,
                                             TAF_PS_CAUSE_SM_NW_PDP_TYPE_IPV4_ONLY_ALLOWED);
                    break;
                }

                if (VOS_OK != AT_PS_SetupSingleStackConn(pstEvent->stCtrl.usClientId, ucCallId, TAF_PDP_IPV6))
                {
                    /*  */
                    AT_PS_SetPsCallErrCause(pstEvent->stCtrl.usClientId, TAF_PS_CAUSE_UNKNOWN);

                    /* IPv6 */
                    AT_PS_SndCallEndedResult(pstEvent->stCtrl.usClientId,
                                             ucCallId,
                                             TAF_PDP_IPV6,
                                             AT_PS_GetPsCallErrCause(pstEvent->stCtrl.usClientId));
                }
                break;

            case TAF_PDP_IPV6:
                if ((VOS_FALSE == pstEvent->bitOpCause)
                 && (VOS_FALSE == pstCommPsCtx->ucRedialForNoCauseFlag))
                {
                    AT_PS_SndCallEndedResult(pstEvent->stCtrl.usClientId,
                                             ucCallId,
                                             TAF_PDP_IPV4,
                                             TAF_PS_CAUSE_SM_NW_PDP_TYPE_IPV6_ONLY_ALLOWED);
                    break;
                }

                if (VOS_OK != AT_PS_SetupSingleStackConn(pstEvent->stCtrl.usClientId, ucCallId, TAF_PDP_IPV4))
                {
                    /*  */
                    AT_PS_SetPsCallErrCause(pstEvent->stCtrl.usClientId, TAF_PS_CAUSE_UNKNOWN);

                    /* IPv4 */
                    AT_PS_SndCallEndedResult(pstEvent->stCtrl.usClientId,
                                             ucCallId,
                                             TAF_PDP_IPV4,
                                             AT_PS_GetPsCallErrCause(pstEvent->stCtrl.usClientId));
                }
                break;

            default:
                AT_WARN_LOG("AT_PS_ProcDualStackCallConn: PDP type is invalid!");
                break;
        }
    }
    else
    {
        /* , APP */
        switch (pstEvent->enCause)
        {
            /* #50 (IPv4 ONLY), APPIPv6 */
            case TAF_PS_CAUSE_SM_NW_PDP_TYPE_IPV4_ONLY_ALLOWED:
            case TAF_PS_CAUSE_PDP_TYPE_IPV4_ONLY_ALLOWED:
                AT_PS_SndCallEndedResult(pstEvent->stCtrl.usClientId,
                                         ucCallId,
                                         TAF_PDP_IPV6,
                                         pstEvent->enCause);

                break;

            /* #51 (IPv6 ONLY), APPIPv4 */
            case TAF_PS_CAUSE_SM_NW_PDP_TYPE_IPV6_ONLY_ALLOWED:
            case TAF_PS_CAUSE_PDP_TYPE_IPV6_ONLY_ALLOWED:
                AT_PS_SndCallEndedResult(pstEvent->stCtrl.usClientId,
                                         ucCallId,
                                         TAF_PDP_IPV4,
                                         pstEvent->enCause);

                break;

            /* ,  */
            default:
                AT_PS_SndCallEndedResult(pstEvent->stCtrl.usClientId,
                                         ucCallId,
                                         (TAF_PDP_IPV4 == pstEvent->stPdpAddr.enPdpType) ? TAF_PDP_IPV6 : TAF_PDP_IPV4,
                                         pstEvent->enCause);
                break;
        }
    }

    return;
}

/*****************************************************************************
     : AT_PS_ProcIpv4ConnSuccFallback
   : IPv4
   : ucCallId - 
             pstEvent - 
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20121218
           : A00165503
       : 
  2.       : 20130708
           : Y00213812
       : VoLTE_PhaseI EVENT

*****************************************************************************/
VOS_VOID AT_PS_ProcIpv4ConnSuccFallback(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
    switch (AT_PS_GetCurrCallType(pstEvent->stCtrl.usClientId, ucCallId))
    {
        /* PDPPDPIPV4
           IPV6PDPTAF_PDP_IPV6IPV6PDP
           IPV4IPV6PDP */
        case TAF_PDP_IPV4:
            if (VOS_OK != AT_PS_SetupSingleStackConn(pstEvent->stCtrl.usClientId, ucCallId, TAF_PDP_IPV6))
            {
                /*  */
                AT_PS_SetPsCallErrCause(pstEvent->stCtrl.usClientId, TAF_PS_CAUSE_UNKNOWN);

                /* IPv6 */
                AT_PS_SndCallEndedResult(pstEvent->stCtrl.usClientId,
                                         ucCallId,
                                         TAF_PDP_IPV6,
                                         AT_PS_GetPsCallErrCause(pstEvent->stCtrl.usClientId));
            }
            break;

        /* PDP */
        case TAF_PDP_IPV4V6:

            /* IPv6CID */
            AT_PS_SetCid2CurrCall(pstEvent->stCtrl.usClientId, ucCallId, TAF_PDP_IPV6, AT_PS_CALL_INVALID_CID);

            /* PDPIDLE */
            AT_PS_SetCallStateByType(pstEvent->stCtrl.usClientId, ucCallId, TAF_PDP_IPV6, AT_PDP_STATE_IDLE);

            AT_PS_ProcDualStackCallConn(ucCallId, pstEvent);

            break;

        default:
            AT_ERR_LOG("AT_PS_ProcIpv4ConnSuccFallback: PDP type is invalid!");
            break;
    }

    return;
}

/*****************************************************************************
     : AT_PS_ProcIpv6ConnSuccFallback
   : IPv6
   : ucCallId - 
             pstEvent - 
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20121218
           : A00165503
       : 
  2.       : 20130708
           : Y00213812
       : VoLTE_PhaseI EVENT

*****************************************************************************/
VOS_VOID AT_PS_ProcIpv6ConnSuccFallback(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
    switch (AT_PS_GetCurrCallType(pstEvent->stCtrl.usClientId, ucCallId))
    {
        case TAF_PDP_IPV6:
            /* PDPPDPIPV4
               IPV6PDP, IPV6IPV4PDP */
            break;

        /* PDP */
        case TAF_PDP_IPV4V6:

            /* IPv4CID */
            AT_PS_SetCid2CurrCall(pstEvent->stCtrl.usClientId, ucCallId, TAF_PDP_IPV4, AT_PS_CALL_INVALID_CID);

            /* PDPIDLE */
            AT_PS_SetCallStateByType(pstEvent->stCtrl.usClientId, ucCallId, TAF_PDP_IPV4, AT_PDP_STATE_IDLE);

            AT_PS_ProcDualStackCallConn(ucCallId, pstEvent);

            break;

        default:
            AT_ERR_LOG("AT_PS_ProcIpv6ConnSuccFallback: PDP type is invalid!");
            break;
    }

    return;
}

/*****************************************************************************
     : AT_PS_ProcIpv4ConnFailFallback
   : IPv4
   : ucCallId - 
             pstEvent - 
   : 
     : VOS_OK   - 
             VOS_ERR  - 
   :
   :

       :
  1.       : 20121218
           : A00165503
       : 
*****************************************************************************/
VOS_UINT32 AT_PS_ProcIpv4ConnFailFallback(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU  *pstEvent
)
{
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity       = VOS_NULL_PTR;
    AT_DIAL_PARAM_STRU                  stCallDialParam;
    VOS_UINT32                          ulRslt;

    TAF_MEM_SET_S(&stCallDialParam, sizeof(stCallDialParam), 0x00, sizeof(AT_DIAL_PARAM_STRU));

    pstCallEntity = AT_PS_GetCallEntity(pstEvent->stCtrl.usClientId, ucCallId);
    ulRslt        = VOS_OK;

    if (AT_PDP_STATE_IDLE == pstCallEntity->enIpv6State)
    {
        /*  */
        AT_PS_GenCallDialParam(&stCallDialParam,
                               &pstCallEntity->stUsrDialParam,
                               pstCallEntity->stUserInfo.ucUsrCid,
                               TAF_PDP_IPV6);

        /* IPv4PDP */
        if (VOS_OK != AT_PS_SetupCall(pstEvent->stCtrl.usClientId, ucCallId, &stCallDialParam))
        {
            ulRslt = VOS_ERR;
        }
    }

    return ulRslt;
}

/*****************************************************************************
     : AT_PS_ProcIpv4v6ConnFailFallback
   : IPv4v6
   : ucCallId - 
             pstEvent - 
   : 
     : VOS_OK   - 
             VOS_ERR  - 
   :
   :

       :
  1.       : 20121218
           : A00165503
       : 
*****************************************************************************/
VOS_UINT32 AT_PS_ProcIpv4v6ConnFailFallback(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU  *pstEvent
)
{
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity       = VOS_NULL_PTR;
    AT_DIAL_PARAM_STRU                  stCallDialParam;
    VOS_UINT32                          ulRslt;

    TAF_MEM_SET_S(&stCallDialParam, sizeof(stCallDialParam), 0x00, sizeof(AT_DIAL_PARAM_STRU));

    pstCallEntity = AT_PS_GetCallEntity(pstEvent->stCtrl.usClientId, ucCallId);
    ulRslt        = VOS_ERR;

    /*  */
    AT_PS_GenCallDialParam(&stCallDialParam,
                           &pstCallEntity->stUsrDialParam,
                           pstCallEntity->stUserInfo.ucUsrCid,
                           TAF_PDP_IPV4);

    /* IPv4PDP */
    if (VOS_OK == AT_PS_SetupCall(pstEvent->stCtrl.usClientId, ucCallId, &stCallDialParam))
    {
        ulRslt = VOS_OK;
    }

    return ulRslt;
}

/*****************************************************************************
     : AT_PS_ProcIpv4CallConnected
   : IPv4
   : ucCallId - 
             pstEvent - 
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20121217
           : Y00213812
       : C50 IPv6 
  2.       : 20130708
           : Y00213812
       : VoLTE_PhaseI EVENT

*****************************************************************************/
VOS_VOID AT_PS_ProcIpv4CallConnected(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity;

    pstCallEntity = AT_PS_GetCallEntity(pstEvent->stCtrl.usClientId, ucCallId);

    /* IPv4PDP */
    AT_PS_SetCallStateByType(pstEvent->stCtrl.usClientId, ucCallId, TAF_PDP_IPV4, AT_PDP_STATE_ACTED);

    /* IPv4DHCP */
    AT_PS_ProcConnInd(ucCallId, pstEvent);

    /* IPv4 */
    AT_PS_SndCallConnectedResult(pstEvent->stCtrl.usClientId, ucCallId, TAF_PDP_IPV4);

    /* PDP */
    AT_PS_ActivateRmNet(ucCallId, pstEvent, TAF_PDP_IPV4);

    /* FC */
    AT_PS_RegFCPoint(ucCallId, pstEvent);

    /* CIDPDP */
    AT_SetAtChdataCidActStatus(pstEvent->stCtrl.usClientId, pstCallEntity->stUserInfo.ucUsrCid, VOS_TRUE);

    /* IPV4V6PDP */
    if (VOS_TRUE == AT_PS_IsUsrDialTypeDualStack(pstEvent->stCtrl.usClientId, ucCallId))
    {
        AT_PS_ProcIpv4ConnSuccFallback(ucCallId, pstEvent);
    }

    return;
}

/*****************************************************************************
     : AT_PS_ProcIpv4CallReject
   : IPv4PDP
   : ucCallId   - ID
             pstEvent   - 
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20121210
           : Y00213812
       : C50 IPv6 
*****************************************************************************/
VOS_VOID AT_PS_ProcIpv4CallReject(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU  *pstEvent
)
{
    /* IPv4v6PDP, , 28, 
       IPv4/IPv6PDP, IPv4, IPv6,
       IPv4PDP, IPV6
       PDPPDP, IPv6PDP, 
       IPv4PDP */

    AT_PDP_STATE_ENUM_U8                enPreCallState;

    enPreCallState = AT_PS_GetCallStateByType(pstEvent->stCtrl.usClientId, ucCallId, TAF_PDP_IPV4);

    /* IPv4CID */
    AT_PS_SetCid2CurrCall(pstEvent->stCtrl.usClientId, ucCallId, TAF_PDP_IPV4, AT_PS_CALL_INVALID_CID);

    /* IPv4PDPIDLE */
    AT_PS_SetCallStateByType(pstEvent->stCtrl.usClientId, ucCallId, TAF_PDP_IPV4, AT_PDP_STATE_IDLE);

    /* IPv4 */
    AT_PS_SndCallEndedResult(pstEvent->stCtrl.usClientId,
                             ucCallId,
                             TAF_PDP_IPV4,
                             pstEvent->enCause);

    /* CALLIDCID */
    AT_PS_FreeCallIdToCid(pstEvent->stCtrl.usClientId, pstEvent->ucCid);

    if ( (AT_PS_IsUsrDialTypeDualStack(pstEvent->stCtrl.usClientId, ucCallId))
      && (AT_PDP_STATE_ACTING == enPreCallState) )
    {
        if (VOS_OK == AT_PS_ProcIpv4ConnFailFallback(ucCallId, pstEvent))
        {
            AT_ERR_LOG("AT_PS_ProcIpv4CallReject: 14004AT_PS_ProcIpv4ConnFailFallback.");
            return;
        }
        else
        {
            /*  */
            AT_PS_SetPsCallErrCause(pstEvent->stCtrl.usClientId, TAF_PS_CAUSE_UNKNOWN);

            /* IPv6 */
            AT_PS_SndCallEndedResult(pstEvent->stCtrl.usClientId,
                                     ucCallId,
                                     TAF_PDP_IPV6,
                                     AT_PS_GetPsCallErrCause(pstEvent->stCtrl.usClientId));
        }
    }

    AT_ERR_LOG("AT_PS_ProcIpv4CallReject: AT_PS_FreeCallEntity.");

    /*  */
    AT_PS_FreeCallEntity(pstEvent->stCtrl.usClientId, ucCallId);

    return;
}

/*****************************************************************************
     : AT_PS_ProcIpv4CallEnded
   : IPv4PDP
   : ucCallId - PDPID
             pstEvent - 
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20121210
           : Y00213812
       : C50 IPv6 
*****************************************************************************/
VOS_VOID AT_PS_ProcIpv4CallEnded(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
)
{
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity;

    pstCallEntity = AT_PS_GetCallEntity(pstEvent->stCtrl.usClientId, ucCallId);

    /* IPv4CID */
    AT_PS_SetCid2CurrCall(pstEvent->stCtrl.usClientId, ucCallId, TAF_PDP_IPV4, AT_PS_CALL_INVALID_CID);

    /* IPv4PDPIDLE */
    AT_PS_SetCallStateByType(pstEvent->stCtrl.usClientId, ucCallId, TAF_PDP_IPV4, AT_PDP_STATE_IDLE);

    /* IPv4 */
    AT_PS_SndCallEndedResult(pstEvent->stCtrl.usClientId,
                             ucCallId,
                             TAF_PDP_IPV4,
                             pstEvent->enCause);

    /* PDP */
    AT_PS_DeactivateRmNet(ucCallId, pstEvent, TAF_PDP_IPV4);

    /* FC */
    AT_PS_DeRegFCPoint(ucCallId, pstEvent);

    /* CID */
    AT_CleanAtChdataCfg(pstEvent->stCtrl.usClientId, pstCallEntity->stUserInfo.ucUsrCid);

    /* CALLIDCID */
    AT_PS_FreeCallIdToCid(pstEvent->stCtrl.usClientId, pstEvent->ucCid);

    /* IPv6PDP,  */
    if (AT_PS_IsUsrDialTypeDualStack(pstEvent->stCtrl.usClientId, ucCallId))
    {
        if (VOS_OK == AT_PS_HangupSingleStackConn(pstEvent->stCtrl.usClientId, ucCallId, TAF_PDP_IPV6))
        {
             AT_ERR_LOG("AT_PS_ProcIpv4CallEnded: 14087AT_PS_HangupSingleStackConn.");
            return;
        }

        if (TAF_PDP_IPV4 == AT_PS_GetCurrCallType(pstEvent->stCtrl.usClientId, ucCallId))
        {
            /* IPv6 */
            AT_PS_SndCallEndedResult(pstEvent->stCtrl.usClientId,
                                     ucCallId,
                                     TAF_PDP_IPV6,
                                     TAF_PS_CAUSE_SUCCESS);
        }
    }

    AT_ERR_LOG("AT_PS_ProcIpv4CallEnded: AT_PS_FreeCallEntity.");

    /* PDP */
    AT_PS_FreeCallEntity(pstEvent->stCtrl.usClientId, ucCallId);

    return;
}

/*****************************************************************************
     : AT_PS_ProcIpv6CallConnected
   : IPV6PDP
   : ucCallId - PDPID
             pstEvent - 
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20121210
           : Y00213812
       : C50 IPv6 
*****************************************************************************/
VOS_VOID AT_PS_ProcIpv6CallConnected(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity;

    pstCallEntity = AT_PS_GetCallEntity(pstEvent->stCtrl.usClientId, ucCallId);

    /* IPv6 */
    AT_PS_SetCallStateByType(pstEvent->stCtrl.usClientId, ucCallId, TAF_PDP_IPV6, AT_PDP_STATE_ACTED);

    /* IPV6 */
    AT_PS_ProcConnectedIpv6Addr(ucCallId, pstEvent);

    /* PDP */
    AT_PS_ActivateRmNet(ucCallId, pstEvent, TAF_PDP_IPV6);

    /* FC */
    AT_PS_RegFCPoint(ucCallId, pstEvent);

    /* CIDPDP */
    AT_SetAtChdataCidActStatus(pstEvent->stCtrl.usClientId, pstCallEntity->stUserInfo.ucUsrCid, VOS_TRUE);

    /* IPV4V6PDP */
    if (AT_PS_IsUsrDialTypeDualStack(pstEvent->stCtrl.usClientId, ucCallId))
    {
        AT_PS_ProcIpv6ConnSuccFallback(ucCallId, pstEvent);
    }

    return;
}

/*****************************************************************************
     : AT_AppIpv4v6ActCnfProc
   : IPv4v6PDP
   : ucCallId - PDPID
             pstEvent - 
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20121210
           : Y00213812
       : C50 IPv6 
*****************************************************************************/
VOS_VOID AT_PS_ProcIpv4v6CallConnected(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity;

    pstCallEntity = AT_PS_GetCallEntity(pstEvent->stCtrl.usClientId, ucCallId);

    /* IPv4v6 */
    AT_PS_SetCallStateByType(pstEvent->stCtrl.usClientId, ucCallId, TAF_PDP_IPV4V6, AT_PDP_STATE_ACTED);

    /* IPV4 */
    AT_PS_ProcConnInd(ucCallId, pstEvent);

    /* IPV6 */
    AT_PS_ProcConnectedIpv6Addr(ucCallId, pstEvent);

    /* IPv4, IPv6RA */
    AT_PS_SndCallConnectedResult(pstEvent->stCtrl.usClientId, ucCallId, TAF_PDP_IPV4);

    /* PDP */
    AT_PS_ActivateRmNet(ucCallId, pstEvent, TAF_PDP_IPV4V6);

    /* FC */
    AT_PS_RegFCPoint(ucCallId, pstEvent);

    /* CIDPDP */
    AT_SetAtChdataCidActStatus(pstEvent->stCtrl.usClientId, pstCallEntity->stUserInfo.ucUsrCid, VOS_TRUE);

    return;
}

/*****************************************************************************
     : AT_PS_ProcIpv6CallReject
   : IPv6PDP
   : ucCallId - PDPID
             pstEvent - 
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20121210
           : Y00213812
       : C50 IPv6 
*****************************************************************************/
VOS_VOID AT_PS_ProcIpv6CallReject(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU  *pstEvent
)
{
    /* IPv6, IPv4, IPv4PDP
       , IPv4PDP, PDP */

    /* IPv6CID */
    AT_PS_SetCid2CurrCall(pstEvent->stCtrl.usClientId, ucCallId, TAF_PDP_IPV6, AT_PS_CALL_INVALID_CID);

    /* IPv6PDPIDLE */
    AT_PS_SetCallStateByType(pstEvent->stCtrl.usClientId, ucCallId, TAF_PDP_IPV6, AT_PDP_STATE_IDLE);

    /* IPv6 */
    AT_PS_SndCallEndedResult(pstEvent->stCtrl.usClientId,
                             ucCallId,
                             TAF_PDP_IPV6,
                             pstEvent->enCause);

    /* CALLIDCID */
    AT_PS_FreeCallIdToCid(pstEvent->stCtrl.usClientId, pstEvent->ucCid);

    /* IPV4IDLE */
    if (AT_PDP_STATE_IDLE == AT_PS_GetCallStateByType(pstEvent->stCtrl.usClientId, ucCallId, TAF_PDP_IPV4))
    {
        AT_ERR_LOG("AT_PS_ProcIpv6CallReject: AT_PS_FreeCallEntity.");

        /*  */
        AT_PS_FreeCallEntity(pstEvent->stCtrl.usClientId, ucCallId);
    }

    return;
}

/*****************************************************************************
     : AT_PS_ProcIpv4v6CallReject
   : IPv4v6PDP
   : pstAppPdpEntity - PDP
             pstEvent        - 
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20121210
           : Y00213812
       : C50 IPv6 
*****************************************************************************/
VOS_VOID AT_PS_ProcIpv4v6CallReject(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU  *pstEvent
)
{
    /* IPv4v6CID */
    AT_PS_SetCid2CurrCall(pstEvent->stCtrl.usClientId, ucCallId, TAF_PDP_IPV4V6, AT_PS_CALL_INVALID_CID);

    /* IPv4v6PDPIDLE */
    AT_PS_SetCallStateByType(pstEvent->stCtrl.usClientId, ucCallId, TAF_PDP_IPV4V6, AT_PDP_STATE_IDLE);

    /* CALLIDCID */
    AT_PS_FreeCallIdToCid(pstEvent->stCtrl.usClientId, pstEvent->ucCid);

    /* IPv4v6 */
    if (VOS_TRUE == AT_PS_MatchIpv4v6ConnFailFallbackCause(pstEvent->enCause))
    {
        if (VOS_OK == AT_PS_ProcIpv4v6ConnFailFallback(ucCallId, pstEvent))
        {
            return;
        }
        else
        {
            /*  */
            AT_PS_SetPsCallErrCause(pstEvent->stCtrl.usClientId, TAF_PS_CAUSE_UNKNOWN);
        }
    }

    /* IPv4 */
    AT_PS_SndCallEndedResult(pstEvent->stCtrl.usClientId,
                             ucCallId,
                             TAF_PDP_IPV4,
                             AT_PS_GetPsCallErrCause(pstEvent->stCtrl.usClientId));
    /* IPv6 */
    AT_PS_SndCallEndedResult(pstEvent->stCtrl.usClientId,
                             ucCallId,
                             TAF_PDP_IPV6,
                             AT_PS_GetPsCallErrCause(pstEvent->stCtrl.usClientId));

    AT_ERR_LOG("AT_PS_ProcIpv4v6CallReject: AT_PS_FreeCallEntity.");

    /*  */
    AT_PS_FreeCallEntity(pstEvent->stCtrl.usClientId, ucCallId);

    return;
}

/*****************************************************************************
     : AT_PS_ProcIpv6CallEnded
   : IPv6PDP
   : ucCallId - PDPID
             pstEvent - 
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20121210
           : Y00213812
       : C50 IPv6 
*****************************************************************************/
VOS_VOID AT_PS_ProcIpv6CallEnded(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
)
{
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity;

    pstCallEntity = AT_PS_GetCallEntity(pstEvent->stCtrl.usClientId, ucCallId);

    /* IPv6CID */
    AT_PS_SetCid2CurrCall(pstEvent->stCtrl.usClientId, ucCallId, TAF_PDP_IPV6, AT_PS_CALL_INVALID_CID);

    /* IPv6PDPIDLE */
    AT_PS_SetCallStateByType(pstEvent->stCtrl.usClientId, ucCallId, TAF_PDP_IPV6, AT_PDP_STATE_IDLE);

    /* IPv6 */
    AT_PS_SndCallEndedResult(pstEvent->stCtrl.usClientId,
                             ucCallId,
                             TAF_PDP_IPV6,
                             pstEvent->enCause);

    /* PDP */
    AT_PS_DeactivateRmNet(ucCallId, pstEvent, TAF_PDP_IPV6);

    /* FC */
    AT_PS_DeRegFCPoint(ucCallId, pstEvent);

    /* CID */
    AT_CleanAtChdataCfg(pstEvent->stCtrl.usClientId, pstCallEntity->stUserInfo.ucUsrCid);

    /* CALLIDCID */
    AT_PS_FreeCallIdToCid(pstEvent->stCtrl.usClientId, pstEvent->ucCid);

    /* IPv4PDP,  */
    if (VOS_OK == AT_PS_HangupSingleStackConn(pstEvent->stCtrl.usClientId, ucCallId, TAF_PDP_IPV4))
    {
        AT_ERR_LOG("AT_PS_ProcIpv6CallEnded: 14378AT_PS_HangupSingleStackConn.");
        return;
    }

    /*  */
    AT_PS_FreeCallEntity(pstEvent->stCtrl.usClientId, ucCallId);

    AT_ERR_LOG("AT_PS_ProcIpv6CallEnded: AT_PS_FreeCallEntity.");

    return;
}

/*****************************************************************************
     : AT_PS_ProcIpv4v6CallEnded
   : IPv4v6PDP
   : ucCallId - PDPID
             pstEvent - 
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20121210
           : Y00213812
       : C50 IPv6 
*****************************************************************************/
VOS_VOID AT_PS_ProcIpv4v6CallEnded(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
)
{
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity;

    pstCallEntity = AT_PS_GetCallEntity(pstEvent->stCtrl.usClientId, ucCallId);

    /* IPv4v6CID */
    AT_PS_SetCid2CurrCall(pstEvent->stCtrl.usClientId, ucCallId, TAF_PDP_IPV4V6, AT_PS_CALL_INVALID_CID);

    /* IPv4v6PDPIDLE */
    AT_PS_SetCallStateByType(pstEvent->stCtrl.usClientId, ucCallId, TAF_PDP_IPV4V6, AT_PDP_STATE_IDLE);

    /* IPv4IPv6 */
    AT_PS_SndCallEndedResult(pstEvent->stCtrl.usClientId,
                             ucCallId,
                             TAF_PDP_IPV4V6,
                             pstEvent->enCause);

    /* PDP */
    AT_PS_DeactivateRmNet(ucCallId, pstEvent, TAF_PDP_IPV4V6);

    /* FC */
    AT_PS_DeRegFCPoint(ucCallId, pstEvent);

    /* CID */
    AT_CleanAtChdataCfg(pstEvent->stCtrl.usClientId, pstCallEntity->stUserInfo.ucUsrCid);

    /* CALLIDCID */
    AT_PS_FreeCallIdToCid(pstEvent->stCtrl.usClientId, pstEvent->ucCid);

    AT_ERR_LOG("AT_PS_ProcIpv4v6CallEnded: AT_PS_FreeCallEntity.");

    /* PDP */
    AT_PS_FreeCallEntity(pstEvent->stCtrl.usClientId, ucCallId);

    return;
}

/*****************************************************************************
     : AT_PS_ProcCallConnectedEvent
   : PS
   : pstEvent - CALL_PDP_ACTIVATE_CNF
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20121217
           : A00165503
       : 
*****************************************************************************/
VOS_VOID AT_PS_ProcCallConnectedEvent(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
    VOS_UINT8                           ucCallId;

    ucCallId = AT_PS_TransCidToCallId(pstEvent->stCtrl.usClientId, pstEvent->ucCid);

    if (VOS_FALSE == AT_PS_IsCallIdValid(pstEvent->stCtrl.usClientId, ucCallId))
    {
        AT_ERR_LOG("AT_PS_ProcCallConnectedEvent:ERROR: CallId is invalid!");
        return;
    }

    /* PDP*/
    switch (pstEvent->stPdpAddr.enPdpType)
    {
        case TAF_PDP_IPV4:
            /* IPv4PDP */
            AT_PS_ProcIpv4CallConnected(ucCallId, pstEvent);
            break;

        case TAF_PDP_IPV6:
            /* IPv6PDP */
            AT_PS_ProcIpv6CallConnected(ucCallId, pstEvent);
            break;

        case TAF_PDP_IPV4V6:
            /* IPv4v6PDP */
            AT_PS_ProcIpv4v6CallConnected(ucCallId, pstEvent);
            break;

        default:
            AT_WARN_LOG("AT_PS_ProcCallConnectedEvent:WARNING: PDP type is invaild!");
            break;
    }

    return;
}

/*****************************************************************************
     : AT_PS_ProcCallRejectEvent
   : PS
   : pstEvent - CALL_PDP_ACTIVATE_REJ
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20121217
           : A00165503
       : 
*****************************************************************************/
VOS_VOID AT_PS_ProcCallRejectEvent(
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU   *pstEvent
)
{
    VOS_UINT8                           ucCallId;

    ucCallId = AT_PS_TransCidToCallId(pstEvent->stCtrl.usClientId, pstEvent->ucCid);

    if (VOS_FALSE == AT_PS_IsCallIdValid(pstEvent->stCtrl.usClientId, ucCallId))
    {
        AT_ERR_LOG("AT_PS_ProcCallRejectEvent:ERROR: CallId is invalid!");
        return;
    }

    /* PDP*/
    switch (AT_PS_GetCurrCallType(pstEvent->stCtrl.usClientId, ucCallId))
    {
        case TAF_PDP_IPV4:
            /* IPv4PDP */
            AT_PS_ProcIpv4CallReject(ucCallId, pstEvent);
            break;

        case TAF_PDP_IPV6:
            /* IPv6PDP */
            AT_PS_ProcIpv6CallReject(ucCallId, pstEvent);
            break;

        case TAF_PDP_IPV4V6:
            /* IPv4v6PDP */
            AT_PS_ProcIpv4v6CallReject(ucCallId, pstEvent);
            break;

        default:
            AT_WARN_LOG("AT_PS_ProcCallRejectEvent:WARNING: PDP type is invaild!");
            break;
    }

    return;
}

/*****************************************************************************
     : AT_PS_ProcCallEndedEvent
   : PS
   : pstEvent - PDP_DEACTIVATE_IND/PDP_DEACTIVATE_CNF
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20121217
           : A00165503
       : 
*****************************************************************************/
VOS_VOID AT_PS_ProcCallEndedEvent(
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
)
{
    VOS_UINT8                           ucCallId;

    ucCallId = AT_PS_TransCidToCallId(pstEvent->stCtrl.usClientId, pstEvent->ucCid);

    if (VOS_FALSE == AT_PS_IsCallIdValid(pstEvent->stCtrl.usClientId, ucCallId))
    {
        AT_ERR_LOG("AT_PS_ProcCallEndedEvent:ERROR: CallId is invalid!");
        return;
    }

    /* PDP*/
    switch ( pstEvent->enPdpType )
    {
        case TAF_PDP_IPV4:
            /* IPv4PDP */
            AT_PS_ProcIpv4CallEnded(ucCallId, pstEvent);
            break;

        case TAF_PDP_IPV6:
            /* IPv6PDP */
            AT_PS_ProcIpv6CallEnded(ucCallId, pstEvent);
            break;

        case TAF_PDP_IPV4V6:
            /* IPv4v6PDP */
            AT_PS_ProcIpv4v6CallEnded(ucCallId, pstEvent);
            break;

        default:
            AT_WARN_LOG("AT_PS_ProcCallRejectEvent:WARNING: PDP type is invaild!");
            break;
    }

    return;
}

/*****************************************************************************
     : AT_PS_ProcCallOrigCnfEvent
   : PS_CALL_ORIG_CNF
   : pstCallOrigCnf - PS_CALL_ORIG_CNF
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20121217
           : A00165503
       : 
*****************************************************************************/
VOS_VOID AT_PS_ProcCallOrigCnfEvent(TAF_PS_CALL_ORIG_CNF_STRU *pstCallOrigCnf)
{
    /* (1) CID
     * (2) 
     * (3) &
     *     
     *     ->
     *     
     *     ->^DEND
     *     ->CALLIDCID
     *     ->
     */
    AT_PDP_STATE_ENUM_U8                enCallState;
    VOS_UINT8                           ucCallId;

    /* CID(CallId) */
    ucCallId = AT_PS_TransCidToCallId(pstCallOrigCnf->stCtrl.usClientId, pstCallOrigCnf->ucCid);

    if (VOS_FALSE == AT_PS_IsCallIdValid(pstCallOrigCnf->stCtrl.usClientId, ucCallId))
    {
        AT_ERR_LOG("AT_PS_ProcCallOrigCnfEvent: CallId is invalid!");
        return;
    }

    enCallState = AT_PS_GetCallStateByCid(pstCallOrigCnf->stCtrl.usClientId, ucCallId, pstCallOrigCnf->ucCid);

    if (TAF_PS_CAUSE_SUCCESS != pstCallOrigCnf->enCause)
    {
        switch (enCallState)
        {
            case AT_PDP_STATE_ACTING:
            case AT_PDP_STATE_DEACTING:

                /* CID */
                AT_PS_SetCid2CurrCall(pstCallOrigCnf->stCtrl.usClientId,
                                      ucCallId,
                                      AT_PS_GetCurrCallType(pstCallOrigCnf->stCtrl.usClientId, ucCallId),
                                      AT_PS_CALL_INVALID_CID);

                /* PDPIDLE */
                AT_PS_SetCallStateByType(pstCallOrigCnf->stCtrl.usClientId,
                                         ucCallId,
                                         AT_PS_GetCurrCallType(pstCallOrigCnf->stCtrl.usClientId, ucCallId),
                                         AT_PDP_STATE_IDLE);

                /*  */
                AT_PS_SndCallEndedResult(pstCallOrigCnf->stCtrl.usClientId,
                                         ucCallId,
                                         AT_PS_GetCurrCallType(pstCallOrigCnf->stCtrl.usClientId, ucCallId),
                                         pstCallOrigCnf->enCause);

                /* CALLIDCID */
                AT_PS_FreeCallIdToCid(pstCallOrigCnf->stCtrl.usClientId, pstCallOrigCnf->ucCid);

                break;

            default:
                AT_WARN_LOG1("AT_PS_ProcCallOrigCnfEvent: State is invalid! <state>", enCallState);
                break;
        }

        if (VOS_TRUE == AT_PS_IsLinkDown(pstCallOrigCnf->stCtrl.usClientId, ucCallId))
        {
            AT_ERR_LOG("AT_PS_ProcCallOrigCnfEvent: AT_PS_FreeCallEntity.");

            /*  */
            AT_PS_FreeCallEntity(pstCallOrigCnf->stCtrl.usClientId, ucCallId);
        }
    }
    return;
}

/*****************************************************************************
     : AT_PS_ProcCallEndCnfEvent
   : PS_CALL_END_CNF
   : pstCallOrigCnf - PS_CALL_ORIG_CNF
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20121217
           : A00165503
       : 
*****************************************************************************/
VOS_VOID AT_PS_ProcCallEndCnfEvent(TAF_PS_CALL_END_CNF_STRU *pstCallEndCnf)
{
    /* (1) CID
     * (2) 
     * (3) 
     *     
     *     ->
     *     
     *     ->()
     */

    /* CID(CallId)
     * (A) CallId
     *     -> 
     * (B) CallId
     *     -> 
     */
    VOS_UINT8                           ucCallId;

    ucCallId = AT_PS_TransCidToCallId(pstCallEndCnf->stCtrl.usClientId, pstCallEndCnf->ucCid);

    if (VOS_FALSE == AT_PS_IsCallIdValid(pstCallEndCnf->stCtrl.usClientId, ucCallId))
    {
        AT_ERR_LOG("AT_PS_ProcCallOrigCnfEvent: CallId is invalid!");
        return;
    }

    if (TAF_ERR_NO_ERROR != pstCallEndCnf->enCause)
    {
        AT_ERR_LOG1("AT_PS_ProcCallOrigCnfEvent: End call failed! <cause>", pstCallEndCnf->enCause);
    }

    return;
}

/*****************************************************************************
     : AT_PS_ProcCallModifyEvent
   : APPmodify
   : VOS_UINT8                           ucIndex
             TAF_PS_CALL_PDP_MODIFY_CNF_STRU    *pstEvent
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 201357
           : l60609
       : 

*****************************************************************************/
VOS_UINT32 AT_PS_ProcCallModifyEvent(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_MODIFY_CNF_STRU    *pstEvent
)
{
    VOS_UINT8                           ucCallId;
    VOS_UINT8                           ucUserCid;
    AT_MODEM_PS_CTX_STRU               *pstModemPsCtx = VOS_NULL_PTR;
    VOS_UINT32                          ulRmNetId;
    FC_ID_ENUM_UINT8                    enDefaultFcId;

    ulRmNetId = 0;

    ucCallId = AT_PS_TransCidToCallId(ucIndex, pstEvent->ucCid);

    if (!AT_PS_IsCallIdValid(ucIndex, ucCallId))
    {
        /* AT+CGACTCGCMODEMODIFY IND */
        AT_NotifyFcWhenAppPdpModify(ucIndex, pstEvent);
    }
    else
    {
        /* AT^NDISDUPCGCMODEMODIFY IND */
        pstModemPsCtx = AT_GetModemPsCtxAddrFromClientId(pstEvent->stCtrl.usClientId);

        /* CID */
        ucUserCid = pstModemPsCtx->astCallEntity[ucCallId].stUserInfo.ucUsrCid;

        /* CIDID */
        ulRmNetId = pstModemPsCtx->astChannelCfg[ucUserCid].ulRmNetId;

        /* IDFC ID */
        enDefaultFcId = AT_PS_GetFcIdFromRnicByRmNetId(ulRmNetId);

        if (enDefaultFcId >= FC_ID_BUTT)
        {
            return VOS_ERR;
        }

        AT_NotifyFcWhenPdpModify(pstEvent, enDefaultFcId);
    }

    return VOS_OK;
}

/*****************************************************************************
     : AT_PS_RegHsicFCPoint
   : HISC
   : ucCid      - CID
             pstEvent   - 
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20121112
           : A00165503
       : 
  2.       : 20130708
           : Y00213812
       : VoLTE_PhaseI EVENT,
  3.       : 20131008
           : j00174725
       : TQE

*****************************************************************************/
VOS_VOID AT_PS_RegHsicFCPoint(
    VOS_UINT8                           ucCid,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
    AT_FCID_MAP_STRU                    stFCPriOrg;
    FC_REG_POINT_STRU                   stRegFcPoint;
    FC_PRI_ENUM_UINT8                   enFCPri;
    UDI_DEVICE_ID_E                     enDataChannelId;
    FC_ID_ENUM_UINT8                    enFcId;
    VOS_UINT32                          ulRet;
    MODEM_ID_ENUM_UINT16                enModemId;
    AT_MODEM_PS_CTX_STRU               *pstPsModemCtx = VOS_NULL_PTR;

    TAF_MEM_SET_S(&stRegFcPoint, sizeof(stRegFcPoint), 0x00, sizeof(FC_REG_POINT_STRU));

    enModemId = MODEM_ID_0;

    ulRet = AT_GetModemIdFromClient((VOS_UINT8)pstEvent->stCtrl.usClientId, &enModemId);

    if (VOS_OK != ulRet)
    {
         return;
    }

    pstPsModemCtx = AT_GetModemPsCtxAddrFromModemId(enModemId);

    /* ID */
    if ((VOS_TRUE         == pstPsModemCtx->astChannelCfg[ucCid].ulUsed)
     && (AT_PS_INVALID_RMNET_ID != pstPsModemCtx->astChannelCfg[ucCid].ulRmNetId))
    {
        enDataChannelId = (UDI_DEVICE_ID_E)pstPsModemCtx->astChannelCfg[ucCid].ulRmNetId;
    }
    else
    {
        AT_ERR_LOG("AT_PS_RegHsicFCPoint: data channel id is abnormal.\n");
        return;
    }

    enFcId = AT_PS_GetFcIdByUdiDeviceId(enDataChannelId);

    if (enFcId >= FC_ID_BUTT)
    {
        return;
    }

    /* QOS */
    if (TAF_USED == pstEvent->bitOpUmtsQos)
    {
        enFCPri = AT_GetFCPriFromQos(&pstEvent->stUmtsQos);
    }
    else
    {
        enFCPri = FC_PRI_FOR_PDN_NONGBR;
    }
    /*  */
    ulRet = AT_GetFcPriFromMap(enFcId ,&stFCPriOrg);
    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_PS_RegHsicFCPoint: AT_GetFcPriFromMap Err.\n");
    }

    if (VOS_TRUE == stFCPriOrg.ulUsed)
    {
        /* FCFC,  */
        if (enFCPri > stFCPriOrg.enFcPri)
        {
            AT_ChangeFCPoint(&pstEvent->stCtrl, enFCPri, enFcId);
        }

        /* RABID */
        FC_ChannelMapCreate(enFcId, pstEvent->ucRabId, enModemId);

        AT_INFO_LOG("AT_PS_RegHsicFCPoint: FC is already registered.");

        return;
    }

    /* RABID */
    FC_ChannelMapCreate(enFcId, pstEvent->ucRabId, enModemId);

    stRegFcPoint.enFcId             = enFcId;
    stRegFcPoint.enModemId          = enModemId;
    /* RAB QoS, */
    /*  FC_PRI_3        
        FC_PRI_4        NONGBR
        FC_PRI_5        GBR */
    stRegFcPoint.enFcPri            = enFCPri;
    stRegFcPoint.enPolicyId         = FC_POLICY_ID_MEM;
    stRegFcPoint.pClrFunc           = AT_DisableHsicFlowCtl;
    stRegFcPoint.pSetFunc           = AT_EnableHsicFlowCtl;
    stRegFcPoint.ulParam1           = (VOS_UINT32)DIPC_GetDevHandleByRabId(pstEvent->ucRabId);

    /* ,MEM,CPU,CDSGPRS */
    ulRet = FC_RegPoint(&stRegFcPoint);
    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_PS_RegHsicFCPoint: ERROR: reg mem point Failed.");
        return;
    }

    stRegFcPoint.enPolicyId         = FC_POLICY_ID_CPU_A;
    ulRet = FC_RegPoint(&stRegFcPoint);
    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_PS_RegHsicFCPoint: ERROR: reg a cpu point Failed.");
        return;
    }

    stRegFcPoint.enPolicyId         = FC_POLICY_ID_CDS;
    ulRet = FC_RegPoint(&stRegFcPoint);
    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_PS_RegHsicFCPoint: ERROR: reg cds point Failed.");
        return;
    }

    stRegFcPoint.enPolicyId         = FC_POLICY_ID_GPRS;
    ulRet = FC_RegPoint(&stRegFcPoint);
    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_PS_RegHsicFCPoint: ERROR: reg gprs point Failed.");
        return;
    }

    /* FCIDFC Pri */
    g_stFcIdMaptoFcPri[enFcId].ulUsed  = VOS_TRUE;
    g_stFcIdMaptoFcPri[enFcId].enFcPri = enFCPri;

    /*  */
    AT_MNTN_TraceRegFcPoint((VOS_UINT8)pstEvent->stCtrl.usClientId, AT_FC_POINT_TYPE_HSIC);

    return;
}

/*****************************************************************************
     : AT_PS_DeRegHsicFCPoint
   : hsic
   : VOS_UINT8                           ucCid
             TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 2013426
           : l60609
       : 

*****************************************************************************/
VOS_VOID AT_PS_DeRegHsicFCPoint(
    VOS_UINT8                           ucCid,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
)
{
    FC_ID_ENUM_UINT8                    enFcId;
    VOS_UINT32                          ulRet;
    UDI_DEVICE_ID_E                     enDataChannelId;
    MODEM_ID_ENUM_UINT16                enModemId;
    AT_MODEM_PS_CTX_STRU               *pstPsModemCtx = VOS_NULL_PTR;

    enModemId = MODEM_ID_0;

    ulRet = AT_GetModemIdFromClient((AT_CLIENT_TAB_INDEX_UINT8)pstEvent->stCtrl.usClientId, &enModemId);
    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_DeRegHsicFCPoint: Get modem id fail.");
        return;
    }

    pstPsModemCtx = AT_GetModemPsCtxAddrFromModemId(enModemId);

    /* ID */
    if ((VOS_TRUE == pstPsModemCtx->astChannelCfg[ucCid].ulUsed)
      &&(AT_PS_INVALID_RMNET_ID != pstPsModemCtx->astChannelCfg[ucCid].ulRmNetId))
    {
        enDataChannelId = (UDI_DEVICE_ID_E)pstPsModemCtx->astChannelCfg[ucCid].ulRmNetId;
    }
    else
    {
        AT_ERR_LOG("AT_PS_DeRegHsicFCPoint: ERROR: data channel id is abnormal.");
        return;
    }

    enFcId = AT_PS_GetFcIdByUdiDeviceId(enDataChannelId);

    if (enFcId >= FC_ID_BUTT)
    {
         return;
    }

    /*  */
    FC_ChannelMapDelete(pstEvent->ucRabId, enModemId);

    ulRet = FC_DeRegPoint(enFcId, enModemId);
    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_PS_DeRegHsicFCPoint: ERROR: de reg point Failed.");
        return;
    }

    /* FCIDFC Pri */
    g_stFcIdMaptoFcPri[enFcId].ulUsed  = VOS_FALSE;
    g_stFcIdMaptoFcPri[enFcId].enFcPri = FC_PRI_BUTT;

    /*  */
    AT_MNTN_TraceDeregFcPoint((VOS_UINT8)pstEvent->stCtrl.usClientId, AT_FC_POINT_TYPE_HSIC);

    return;
}

/*****************************************************************************
     : AT_PS_RegAppFCPoint
   : APP
   : VOS_UINT8                           ucCid
             TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 2013424
           : l60609
       : 

*****************************************************************************/
VOS_VOID AT_PS_RegAppFCPoint(
    VOS_UINT8                           ucCid,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
    VOS_UINT32                          ulRslt;
    AT_FCID_MAP_STRU                    stFCPriOrg;
    FC_ID_ENUM_UINT8                    enDefaultFcId;
    VOS_UINT32                          ulRmNetId;
    AT_MODEM_PS_CTX_STRU               *pstPsModemCtx = VOS_NULL_PTR;

    pstPsModemCtx = AT_GetModemPsCtxAddrFromClientId(pstEvent->stCtrl.usClientId);

    /* ID */
    if ((VOS_TRUE == pstPsModemCtx->astChannelCfg[ucCid].ulUsed)
     && (pstPsModemCtx->astChannelCfg[ucCid].ulRmNetId < RNIC_RMNET_ID_BUTT))
    {
        ulRmNetId = pstPsModemCtx->astChannelCfg[ucCid].ulRmNetId;
    }
    else
    {
        AT_ERR_LOG("AT_PS_RegAppFCPoint: data channel id is abnormal.\n");
        return;
    }

    /*  */
    enDefaultFcId = AT_PS_GetFcIdFromRnicByRmNetId(ulRmNetId);

    ulRslt = AT_GetFcPriFromMap(enDefaultFcId ,&stFCPriOrg);
    if (VOS_OK == ulRslt)
    {
        /* FC ID*/
        if (VOS_TRUE != stFCPriOrg.ulUsed)
        {
            /* APP */
            AT_AppRegFCPoint(enDefaultFcId, pstEvent, (VOS_UINT8)ulRmNetId);
        }
        else
        {
            /* APPQOSFC_PRI_FOR_PDN_LOWEST */
            AT_NORM_LOG("AT_PS_RegAppFCPoint: No need to change the default QOS priority.");
        }
    }
    return;
}

/*****************************************************************************
     : AT_PS_DeRegAppFCPoint
   : APP
   : VOS_UINT8                           ucCid
             TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 2013424
           : l60609
       : 

*****************************************************************************/
VOS_VOID AT_PS_DeRegAppFCPoint(
    VOS_UINT8                           ucCid,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
)
{
    FC_ID_ENUM_UINT8                    enDefaultFcId;
    VOS_UINT32                          ulRmNetId;
    AT_MODEM_PS_CTX_STRU               *pstPsModemCtx = VOS_NULL_PTR;

    pstPsModemCtx = AT_GetModemPsCtxAddrFromClientId(pstEvent->stCtrl.usClientId);

    /* ID */
    if ((VOS_TRUE == pstPsModemCtx->astChannelCfg[ucCid].ulUsed)
     && (pstPsModemCtx->astChannelCfg[ucCid].ulRmNetId < RNIC_RMNET_ID_BUTT))
    {
        ulRmNetId = (VOS_UINT8)pstPsModemCtx->astChannelCfg[ucCid].ulRmNetId;
    }
    else
    {
        AT_ERR_LOG("AT_PS_DeRegAppFCPoint: data channel id is abnormal.\n");
        return;
    }

    /*  */
    enDefaultFcId = AT_PS_GetFcIdFromRnicByRmNetId(ulRmNetId);

    /* APP */
    AT_AppDeRegFCPoint(enDefaultFcId, pstEvent);

    return;
}

/*****************************************************************************
     : AT_PS_AllocCallEntity
   : PS
   : usClientId - ID
   : pucCallId - 
     : VOS_OK    - 
             VOS_ERR   - 
   :
   :

       :
  1.       : 20121217
           : A00165503
       : 
*****************************************************************************/
VOS_UINT32 AT_PS_AllocCallEntity(
    VOS_UINT16                          usClientId,
    VOS_UINT8                          *pucCallId
)
{
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;
    VOS_UINT8                           ucCallId;

    for (ucCallId = 0; ucCallId < AT_PS_MAX_CALL_NUM; ucCallId++)
    {
        pstCallEntity = AT_PS_GetCallEntity(usClientId, ucCallId);

        AT_LOG1("AT_PS_AllocCallEntity_normal: usClientId.", (VOS_INT32)usClientId);
        AT_LOG1("AT_PS_AllocCallEntity_normal: ucCallId.", (VOS_INT32)ucCallId);

        if (VOS_FALSE == pstCallEntity->ulUsedFlg)
        {
            break;
        }
    }

    if (ucCallId >= AT_PS_MAX_CALL_NUM)
    {
        for (ucCallId = 0; ucCallId < AT_PS_MAX_CALL_NUM; ucCallId++)
        {
            pstCallEntity = AT_PS_GetCallEntity(usClientId, ucCallId);

            AT_LOG1("AT_PS_AllocCallEntity: ulUsedFlg.", (VOS_INT32)(pstCallEntity->ulUsedFlg));
            AT_LOG1("AT_PS_AllocCallEntity: enPortIndex.", (VOS_INT32)(pstCallEntity->stUserInfo.enPortIndex));
            AT_LOG1("AT_PS_AllocCallEntity: enUserIndex.", (VOS_INT32)(pstCallEntity->stUserInfo.enUserIndex));
            AT_LOG1("AT_PS_AllocCallEntity: ucUsrType.", (VOS_INT32)(pstCallEntity->stUserInfo.ucUsrType));
            AT_LOG1("AT_PS_AllocCallEntity: ucUsrCid.", (VOS_INT32)(pstCallEntity->stUserInfo.ucUsrCid));
            AT_LOG1("AT_PS_AllocCallEntity: ucCid.", (VOS_INT32)(pstCallEntity->stUsrDialParam.ucCid));
            AT_LOG1("AT_PS_AllocCallEntity: enPdpType.", (VOS_INT32)(pstCallEntity->stUsrDialParam.enPdpType));
            AT_LOG1("AT_PS_AllocCallEntity: ucPdpTypeValidFlag.", (VOS_INT32)(pstCallEntity->stUsrDialParam.ucPdpTypeValidFlag));
            AT_LOG1("AT_PS_AllocCallEntity: ucAPNLen.", (VOS_INT32)(pstCallEntity->stUsrDialParam.ucAPNLen));
            AT_LOG1("AT_PS_AllocCallEntity: usUsernameLen.", (VOS_INT32)(pstCallEntity->stUsrDialParam.usUsernameLen));
            AT_LOG1("AT_PS_AllocCallEntity: usPasswordLen.", (VOS_INT32)(pstCallEntity->stUsrDialParam.usPasswordLen));
            AT_LOG1("AT_PS_AllocCallEntity: usAuthType.", (VOS_INT32)(pstCallEntity->stUsrDialParam.usAuthType));
            AT_LOG1("AT_PS_AllocCallEntity: ulIPv4ValidFlag.", (VOS_INT32)(pstCallEntity->stUsrDialParam.ulIPv4ValidFlag));
            AT_LOG1("AT_PS_AllocCallEntity: ucIpv4Cid.", (VOS_INT32)(pstCallEntity->ucIpv4Cid));
            AT_LOG1("AT_PS_AllocCallEntity: enIpv4State.", (VOS_INT32)(pstCallEntity->enIpv4State));
            AT_LOG1("AT_PS_AllocCallEntity: ucIpv6Cid.", (VOS_INT32)(pstCallEntity->ucIpv6Cid));
            AT_LOG1("AT_PS_AllocCallEntity: enIpv6State.", (VOS_INT32)(pstCallEntity->enIpv6State));

        }


        return VOS_ERR;
    }

    pstCallEntity->ulUsedFlg = VOS_TRUE;

    *pucCallId = ucCallId;

    return VOS_OK;
}

/*****************************************************************************
     : AT_PS_FreeCallEntity
   : PS
   : usClientId - 
             ucCallId - 
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20121217
           : A00165503
       : 
*****************************************************************************/
VOS_VOID AT_PS_FreeCallEntity(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId
)
{
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;

    pstCallEntity = AT_PS_GetCallEntity(usClientId, ucCallId);

    AT_LOG1("AT_PS_FreeCallEntity_normal: usClientId.", (VOS_INT32)usClientId);
    AT_LOG1("AT_PS_FreeCallEntity_normal: ucCallId.", (VOS_INT32)ucCallId);


    /* CID */
    AT_CleanAtChdataCfg(usClientId, pstCallEntity->stUserInfo.ucUsrCid);

    TAF_MEM_SET_S(&pstCallEntity->stUserInfo,
               sizeof(pstCallEntity->stUserInfo), 0x00, sizeof(AT_PS_USER_INFO_STRU));

    pstCallEntity->ulUsedFlg   = VOS_FALSE;
    pstCallEntity->ucIpv4Cid   = AT_PS_CALL_INVALID_CID;
    pstCallEntity->enIpv4State = AT_PDP_STATE_IDLE;

    TAF_MEM_SET_S(&pstCallEntity->stIpv4DhcpInfo,
               sizeof(pstCallEntity->stIpv4DhcpInfo), 0x00, sizeof(AT_IPV4_DHCP_PARAM_STRU));

    pstCallEntity->ucIpv6Cid   = AT_PS_CALL_INVALID_CID;
    pstCallEntity->enIpv6State = AT_PDP_STATE_IDLE;

    TAF_MEM_SET_S(&pstCallEntity->stIpv6RaInfo,
               sizeof(pstCallEntity->stIpv6RaInfo), 0x00, sizeof(AT_IPV6_RA_INFO_STRU));
    TAF_MEM_SET_S(&pstCallEntity->stIpv6DhcpInfo,
               sizeof(pstCallEntity->stIpv6DhcpInfo), 0x00, sizeof(AT_IPV6_DHCP_PARAM_STRU));

    return;
}

/*****************************************************************************
     : AT_PS_IsLinkGoingUp
   : /
   : usClientId - ID
             ucCallId  - 
   : 
     : VOS_TRUE  - /
             VOS_FALSE - 
   :
   :

       :
  1.       : 20121217
           : A00165503
       : 
*****************************************************************************/
VOS_UINT32 AT_PS_IsLinkGoingUp(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId
)
{
    /* (CallId) */

    /* (1) /: TRUE
     * (2) : FALSE
     */

    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;
    VOS_UINT32                          ulLinkUpFlg;

    pstCallEntity = AT_PS_GetCallEntity(usClientId, ucCallId);
    ulLinkUpFlg   = VOS_FALSE;

    if ((AT_PDP_STATE_ACTED == pstCallEntity->enIpv4State)
     || (AT_PDP_STATE_ACTING == pstCallEntity->enIpv4State))
    {
        ulLinkUpFlg = VOS_TRUE;
    }

    if ((AT_PDP_STATE_ACTED == pstCallEntity->enIpv6State)
     || (AT_PDP_STATE_ACTING == pstCallEntity->enIpv6State))
    {
        ulLinkUpFlg = VOS_TRUE;
    }

    return ulLinkUpFlg;
}

/*****************************************************************************
     : AT_PS_IsLinkGoingDown
   : 
   : usClientId - ID
             ucCallId   - 
   : 
     : VOS_TRUE
             VOS_FALSE
   :
   :

       :
  1.       : 20121217
           : A00165503
       : 
*****************************************************************************/
VOS_UINT32 AT_PS_IsLinkGoingDown(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId
)
{
    /* (CallId) */

    /* (1) DEACTING, TRUE
     * (2) , FALSE
     */

    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;
    VOS_UINT32                          ulLinkDownFlg;

    pstCallEntity = AT_PS_GetCallEntity(usClientId, ucCallId);
    ulLinkDownFlg = VOS_FALSE;

    if (AT_PDP_STATE_DEACTING == pstCallEntity->enIpv4State)
    {
        ulLinkDownFlg = VOS_TRUE;
    }

    if (AT_PDP_STATE_DEACTING == pstCallEntity->enIpv6State)
    {
        ulLinkDownFlg = VOS_TRUE;
    }

    return ulLinkDownFlg;
}

/*****************************************************************************
     : AT_PS_IsLinkDown
   : 
   : usClientId - ID
             ucCallId   - 
   : 
     : VOS_TRUE  - 
             VOS_FALSE - 
   :
   :

       :
  1.       : 20121217
           : A00165503
       : 
*****************************************************************************/
VOS_UINT32 AT_PS_IsLinkDown(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId
)
{
    /* (CallId) */

    /* (1) IPv4IPv6IDLE, TRUE
     * (2) , FALSE
     */

    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;
    VOS_UINT32                          ulLinkDownFlg;

    pstCallEntity = AT_PS_GetCallEntity(usClientId, ucCallId);
    ulLinkDownFlg = VOS_TRUE;

    if (AT_PDP_STATE_IDLE != pstCallEntity->enIpv4State)
    {
        ulLinkDownFlg = VOS_FALSE;
    }

    if (AT_PDP_STATE_IDLE != pstCallEntity->enIpv6State)
    {
        ulLinkDownFlg = VOS_FALSE;
    }

    return ulLinkDownFlg;
}

/*****************************************************************************
     : AT_PS_ReportCurrCallConnState
   : 
   : usClientId - ID
             ucCallId   - 
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20121217
           : A00165503
       : 
*****************************************************************************/
VOS_VOID AT_PS_ReportCurrCallConnState(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId
)
{
    /* (CallId) */

    /* (1) , 
     * (2) , 
     */

    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;
    AT_PS_RPT_CONN_RSLT_FUNC            pRptConnRsltFunc = VOS_NULL_PTR;

    pstCallEntity    = AT_PS_GetCallEntity(usClientId, ucCallId);

    pRptConnRsltFunc = AT_PS_GetRptConnResultFunc(pstCallEntity->stUserInfo.ucUsrType);

    if (VOS_NULL_PTR != pRptConnRsltFunc)
    {
        if (AT_PDP_STATE_ACTED == pstCallEntity->enIpv4State)
        {
            pRptConnRsltFunc(pstCallEntity->stUserInfo.ucUsrCid,
                             pstCallEntity->stUserInfo.enPortIndex,
                             TAF_PDP_IPV4);
        }

        if ( (AT_PDP_STATE_ACTED == pstCallEntity->enIpv6State)
          && (VOS_TRUE == pstCallEntity->stIpv6RaInfo.bitOpPrefixAddr) )
        {
            pRptConnRsltFunc(pstCallEntity->stUserInfo.ucUsrCid,
                             pstCallEntity->stUserInfo.enPortIndex,
                             TAF_PDP_IPV6);
        }
    }
    else
    {
        AT_WARN_LOG("AT_PS_ReportCurrCallConnState: pRptConnRsltFunc is NULL.");
    }

    return;
}

/*****************************************************************************
     : AT_PS_ReportCurrCallEndState
   : 
   : usClientId - ID
             ucCallId   - 
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20121217
           : A00165503
       : 
*****************************************************************************/
VOS_VOID AT_PS_ReportCurrCallEndState(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId
)
{
    /* (CallId) */

    /* (1) , 
     * (2) , 
     */

    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;
    AT_PS_RPT_END_RSLT_FUNC             pRptEndRsltFunc = VOS_NULL_PTR;

    pstCallEntity   = AT_PS_GetCallEntity(usClientId, ucCallId);
    pRptEndRsltFunc = AT_PS_GetRptEndResultFunc(pstCallEntity->stUserInfo.ucUsrType);

    if (VOS_NULL_PTR != pRptEndRsltFunc)
    {
        if (AT_PDP_STATE_IDLE == pstCallEntity->enIpv4State)
        {
            pRptEndRsltFunc(pstCallEntity->stUserInfo.ucUsrCid,
                            pstCallEntity->stUserInfo.enPortIndex,
                            TAF_PDP_IPV4,
                            TAF_PS_CAUSE_SUCCESS);
        }

        if (VOS_TRUE == AT_PS_IsIpv6Support())
        {
            if (AT_PDP_STATE_IDLE == pstCallEntity->enIpv6State)
            {
                pRptEndRsltFunc(pstCallEntity->stUserInfo.ucUsrCid,
                                pstCallEntity->stUserInfo.enPortIndex,
                                TAF_PDP_IPV6,
                                TAF_PS_CAUSE_SUCCESS);
            }
        }
    }
    else
    {
        AT_WARN_LOG("AT_PS_ReportCurrCallEndState: pRptConnRsltFunc is NULL.");
    }

    return;
}

/*****************************************************************************
     : AT_PS_ReportAllCallEndState
   : 
   : ucIndex - (ClientId)
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20121217
           : A00165503
       : 
*****************************************************************************/
VOS_VOID AT_PS_ReportAllCallEndState(VOS_UINT8 ucIndex)
{
    /* (1) , 
     * (2) 
     */

    AT_PS_RPT_END_RSLT_FUNC             pRptEndRsltFunc = VOS_NULL_PTR;
    AT_PS_USER_INFO_STRU                stUsrInfo;

    TAF_MEM_SET_S(&stUsrInfo, sizeof(stUsrInfo), 0x00, sizeof(AT_PS_USER_INFO_STRU));

    AT_PS_ParseUsrInfo(ucIndex, &stUsrInfo);

    pRptEndRsltFunc = AT_PS_GetRptEndResultFunc(stUsrInfo.ucUsrType);

    if (VOS_NULL_PTR != pRptEndRsltFunc)
    {
        pRptEndRsltFunc(stUsrInfo.ucUsrCid,
                        stUsrInfo.enPortIndex,
                        TAF_PDP_IPV4,
                        TAF_PS_CAUSE_SUCCESS);

        if (VOS_TRUE == AT_PS_IsIpv6Support())
        {
            pRptEndRsltFunc(stUsrInfo.ucUsrCid,
                            stUsrInfo.enPortIndex,
                            TAF_PDP_IPV6,
                            TAF_PS_CAUSE_SUCCESS);
        }
    }
    else
    {
        AT_WARN_LOG("AT_PS_ReportAllCallEndState: pRptConnRsltFunc is NULL.");
    }

    return;
}

/*****************************************************************************
     : AT_PS_ValidateDialParam
   : 
   : ucIndex    - (ClientId)
   : 
     : AT_SUCCESS - 
             OTHER CODE - 
   :
   :

       :
  1.       : 20121217
           : A00165503
       : 

  2.       : 201631
           : Y00213812
       : DTS2016022504530
*****************************************************************************/
VOS_UINT32 AT_PS_ValidateDialParam(VOS_UINT8 ucIndex)
{
    AT_PS_DATA_CHANL_CFG_STRU          *pstChanCfg = VOS_NULL_PTR;

    /*  */
    if (AT_CMD_OPT_SET_CMD_NO_PARA == g_stATParseCmd.ucCmdOptType)
    {
        AT_NORM_LOG("AT_PS_ValidateDialParam: No parameter input.");
        return AT_CME_INCORRECT_PARAMETERS;
    }


    /*  */
    if (gucAtParaIndex > 8)
    {
        AT_NORM_LOG1("AT_PS_ValidateDialParam: Parameter number is .\n", gucAtParaIndex);
        return AT_TOO_MANY_PARA;
    }


    /*  CID */
    if (0 == gastAtParaList[0].usParaLen)
    {
        AT_NORM_LOG("AT_PS_ValidateDialParam: Missing CID.");
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /*  CONN: , 1, 0 */
    if (0 == gastAtParaList[1].usParaLen)
    {
        AT_NORM_LOG("AT_PS_ValidateDialParam: Missing connect state.");
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /*  APN */
    if (0 != gastAtParaList[2].usParaLen)
    {
        /* APN */
        if (gastAtParaList[2].usParaLen > TAF_MAX_APN_LEN)
        {
            AT_NORM_LOG("AT_PS_ValidateDialParam: APN is too long.");
            return AT_CME_INCORRECT_PARAMETERS;
        }

        /* APN */
        if (VOS_OK != AT_CheckApnFormat(gastAtParaList[2].aucPara,
                                        gastAtParaList[2].usParaLen))
        {
            AT_NORM_LOG("AT_PS_ValidateDialParam: Format of APN is wrong.");
            return AT_CME_INCORRECT_PARAMETERS;
        }
    }

    /*  Username */
    if (gastAtParaList[3].usParaLen > TAF_MAX_GW_AUTH_USERNAME_LEN)
    {
        AT_NORM_LOG1("AT_PS_ValidateDialParam: Username length is.\n", gastAtParaList[3].usParaLen);
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /*  Password */
    if (gastAtParaList[4].usParaLen > TAF_MAX_GW_AUTH_PASSWORD_LEN)
    {
        AT_NORM_LOG1("AT_PS_ValidateDialParam: Password length is.\n", gastAtParaList[4].usParaLen);
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if (gastAtParaList[7].usParaLen > 0)
    {
        if (VOS_TRUE != AT_PS_CheckDialRatType(ucIndex, (VOS_UINT8)gastAtParaList[7].ulParaValue))
        {
            AT_NORM_LOG1("AT_PS_ValidateDialParam: DialRatType is.\n", gastAtParaList[7].ulParaValue);
            return AT_CME_INCORRECT_PARAMETERS;
        }
    }

    /*  */
    pstChanCfg = AT_PS_GetDataChanlCfg(ucIndex, (VOS_UINT8)gastAtParaList[0].ulParaValue);

    if ( (VOS_FALSE == pstChanCfg->ulUsed)
      || (AT_PS_INVALID_RMNET_ID == pstChanCfg->ulRmNetId) )
    {
        AT_NORM_LOG1("AT_PS_ValidateDialParam: Used is .\n", pstChanCfg->ulUsed);
        AT_NORM_LOG1("AT_PS_ValidateDialParam: RmNetId is .\n", pstChanCfg->ulRmNetId);
        return AT_CME_INCORRECT_PARAMETERS;
    }

    return AT_SUCCESS;
}

/*****************************************************************************
     : AT_PS_ParseUsrInfo
   : 
   : ucIndex     - (ClientId)
   : pstUserInfo - 
     : VOS_VOID
   :
   :

       :
  1.       : 20121217
           : A00165503
       : 

  2.       : 2015527
           : l00198894
       : TSTS
*****************************************************************************/
VOS_VOID AT_PS_ParseUsrInfo(
    VOS_UINT8                           ucIndex,
    AT_PS_USER_INFO_STRU               *pstUserInfo
)
{
    AT_CLIENT_TAB_INDEX_UINT8           enUserIndex;

    enUserIndex = ucIndex;

    /* PCUIPCUINDISDUP */
    if (AT_USBCOM_USER == gastAtClientTab[ucIndex].UserType)
    {
        if (VOS_TRUE == AT_GetPcuiPsCallFlag())
        {
            enUserIndex = AT_GetPcuiUsertId();
        }
    }

    /* CTRLCTRLNDISDUP */
    if (AT_CTR_USER == gastAtClientTab[ucIndex].UserType)
    {
        if (VOS_TRUE == AT_GetCtrlPsCallFlag())
        {
            enUserIndex = AT_GetCtrlUserId();
        }
    }

    /* PCUI2CTRLNDISDUP */
    if (AT_PCUI2_USER == gastAtClientTab[ucIndex].UserType)
    {
        if (VOS_TRUE == AT_GetPcui2PsCallFlag())
        {
            enUserIndex = AT_GetPcui2UserId();
        }
    }

    pstUserInfo->enPortIndex = ucIndex;
    pstUserInfo->enUserIndex = enUserIndex;
    pstUserInfo->ucUsrType   = (AT_USER_TYPE)gastAtClientTab[enUserIndex].UserType;
    pstUserInfo->ucUsrCid    = (VOS_UINT8)gastAtParaList[0].ulParaValue;

    return;
}

/*****************************************************************************
     : AT_PS_ParseUsrDialParam
   : 
   : ucIndex         - (ClientId)
   : pstUsrDialParam - 
     : VOS_OK          - 
             VOS_ERR         - 
   :
   :

       :
  1.       : 20121217
           : A00165503
       : 

  2.       : 2016216
           : Y00213812
       : 
*****************************************************************************/
VOS_UINT32 AT_PS_ParseUsrDialParam(
    VOS_UINT8                           ucIndex,
    AT_DIAL_PARAM_STRU                 *pstUsrDialParam
)
{
    /*  */

    TAF_PDP_PRIM_CONTEXT_STRU                    stPdpCtxInfo;
    VOS_UINT32                          ulRslt;

    TAF_MEM_SET_S(&stPdpCtxInfo, sizeof(stPdpCtxInfo), 0x00, sizeof(TAF_PDP_PRIM_CONTEXT_STRU));

    /* CID */
    pstUsrDialParam->ucCid         = (VOS_UINT8)gastAtParaList[0].ulParaValue;

    /* APN */
    pstUsrDialParam->ucAPNLen      = (VOS_UINT8)gastAtParaList[2].usParaLen;
    TAF_MEM_CPY_S(pstUsrDialParam->aucAPN,
               sizeof(pstUsrDialParam->aucAPN),
               gastAtParaList[2].aucPara,
               gastAtParaList[2].usParaLen);

    /* Username */
    pstUsrDialParam->usUsernameLen = (VOS_UINT16)gastAtParaList[3].usParaLen;
    TAF_MEM_CPY_S(pstUsrDialParam->aucUsername,
               sizeof(pstUsrDialParam->aucUsername),
               gastAtParaList[3].aucPara,
               gastAtParaList[3].usParaLen);

    /* Password */
    pstUsrDialParam->usPasswordLen = (VOS_UINT16)gastAtParaList[4].usParaLen;
    TAF_MEM_CPY_S(pstUsrDialParam->aucPassword,
               sizeof(pstUsrDialParam->aucPassword),
               gastAtParaList[4].aucPara,
               gastAtParaList[4].usParaLen);

    /* AUTH TYPE */

    if (VOS_TRUE == At_CheckCurrRatModeIsCL(ucIndex))
    {
        pstUsrDialParam->usAuthType = AT_ClGetPdpAuthType(gastAtParaList[5].ulParaValue,
                                                               gastAtParaList[5].usParaLen);
    }
    else
    {
        if (gastAtParaList[5].usParaLen > 0)
        {
            pstUsrDialParam->usAuthType = AT_CtrlGetPDPAuthType(gastAtParaList[5].ulParaValue,
                                                                    gastAtParaList[5].usParaLen);
        }
        else
        {
            /* 0, , CHAP */
            if ( (0 != gastAtParaList[3].usParaLen)
              && (0 != gastAtParaList[4].usParaLen) )
            {
                pstUsrDialParam->usAuthType = TAF_PDP_AUTH_TYPE_CHAP;
            }
            else
            {
                pstUsrDialParam->usAuthType = TAF_PDP_AUTH_TYPE_NONE;
            }
        }
    }





    /* ADDR:  */

    /* PDN TYPE */
    ulRslt = TAF_AGENT_GetPdpCidPara(&stPdpCtxInfo, ucIndex, pstUsrDialParam->ucCid);

    if ( (VOS_OK == ulRslt)
      && (AT_PS_IS_PDP_TYPE_SUPPORT(stPdpCtxInfo.stPdpAddr.enPdpType)) )
    {
        pstUsrDialParam->enPdpType = stPdpCtxInfo.stPdpAddr.enPdpType;
    }
    else
    {
        pstUsrDialParam->enPdpType = TAF_PDP_IPV4;
    }


    if (gastAtParaList[7].usParaLen > 0)
    {
        pstUsrDialParam->ucBitRatType  = (VOS_UINT8)gastAtParaList[7].ulParaValue;
    }


    if (VOS_OK != AT_CheckIpv6Capability(pstUsrDialParam->enPdpType))
    {
        AT_INFO_LOG("AT_PS_ParseUsrDialParam: PDP type is not supported.");

        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
     : AT_PS_SetCurrCallType
   : 
   : VOS_UINT16                          usClientId
             VOS_UINT8                           ucCallId
             TAF_PDP_TYPE_ENUM_UINT8             enPdpType
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 2013425
           : l60609
       : 

*****************************************************************************/
VOS_VOID AT_PS_SetCurrCallType(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
)
{
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;

    pstCallEntity = AT_PS_GetCallEntity(usClientId, ucCallId);

    pstCallEntity->enCurrPdpType = enPdpType;

    return;
}

/*****************************************************************************
     : AT_PS_GetCurrCallType
   : 
   : VOS_UINT16                          usClientId
             VOS_UINT8                           ucCallId
   : 
     : TAF_PDP_TYPE_ENUM_UINT8
   :
   :

       :
  1.       : 2013425
           : l60609
       : 

*****************************************************************************/
TAF_PDP_TYPE_ENUM_UINT8 AT_PS_GetCurrCallType(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId
)
{
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;

    pstCallEntity = AT_PS_GetCallEntity(usClientId, ucCallId);

    return pstCallEntity->enCurrPdpType;
}

/*****************************************************************************
     : AT_PS_TransferQosPara
   : QOSTAF_PS_PDP_QOS_QUERY_PARA_STRU-->TAF_PS_PDP_QOS_SET_PARA_STRU
   : VOS_UINT8                           ucCid,
             TAF_PS_PDP_QOS_QUERY_PARA_STRU     *pstQosQueryPara,
   : TAF_PS_PDP_QOS_SET_PARA_STRU       *pstQosSetPara
     : VOS_VOID
   :
   :

       :
  1.       : 201371
           : l60609
       : 

*****************************************************************************/
VOS_VOID AT_PS_TransferQosPara(
    VOS_UINT8                           ucCid,
    TAF_PS_PDP_QOS_QUERY_PARA_STRU     *pstQosQueryPara,
    TAF_PS_PDP_QOS_SET_PARA_STRU       *pstQosSetPara
)
{
    if (VOS_TRUE == pstQosQueryPara->ucQosFlag)
    {
        pstQosSetPara->stQos.ucDefined = VOS_TRUE;
        pstQosSetPara->stQos.ucCid = ucCid;

        pstQosSetPara->stQos.bitOpTrafficClass = VOS_TRUE;
        pstQosSetPara->stQos.ucTrafficClass    = pstQosQueryPara->stQos.ucTrafficClass;

        pstQosSetPara->stQos.bitOpDeliverOrder = VOS_TRUE;
        pstQosSetPara->stQos.ucDeliverOrder    = pstQosQueryPara->stQos.ucDeliverOrder;

        pstQosSetPara->stQos.bitOpDeliverErrSdu = VOS_TRUE;
        pstQosSetPara->stQos.ucDeliverErrSdu    = pstQosQueryPara->stQos.ucDeliverErrSdu;

        pstQosSetPara->stQos.bitOpMaxSduSize = VOS_TRUE;
        pstQosSetPara->stQos.usMaxSduSize    = pstQosQueryPara->stQos.usMaxSduSize;

        pstQosSetPara->stQos.bitOpMaxBitUl = VOS_TRUE;
        pstQosSetPara->stQos.ulMaxBitUl    = pstQosQueryPara->stQos.ulMaxBitUl;

        pstQosSetPara->stQos.bitOpMaxBitDl = VOS_TRUE;
        pstQosSetPara->stQos.ulMaxBitDl    = pstQosQueryPara->stQos.ulMaxBitDl;

        pstQosSetPara->stQos.bitOpResidualBer = VOS_TRUE;
        pstQosSetPara->stQos.ucResidualBer    = pstQosQueryPara->stQos.ucResidualBer;

        pstQosSetPara->stQos.bitOpSduErrRatio = VOS_TRUE;
        pstQosSetPara->stQos.ucSduErrRatio    = pstQosQueryPara->stQos.ucSduErrRatio;

        pstQosSetPara->stQos.bitOpTransDelay = VOS_TRUE;
        pstQosSetPara->stQos.usTransDelay    = pstQosQueryPara->stQos.usTransDelay;

        pstQosSetPara->stQos.bitOpTraffHandlePrior = VOS_TRUE;
        pstQosSetPara->stQos.ucTraffHandlePrior    = pstQosQueryPara->stQos.ucTraffHandlePrior;

        pstQosSetPara->stQos.bitOpGtdBitUl = VOS_TRUE;
        pstQosSetPara->stQos.ulGtdBitUl    = pstQosQueryPara->stQos.ulGuarantBitUl;

        pstQosSetPara->stQos.bitOpGtdBitDl  = VOS_TRUE;
        pstQosSetPara->stQos.ulGtdBitDl     = pstQosQueryPara->stQos.ulGuarantBitDl;
    }
    else
    {
        pstQosSetPara->stQos.ucDefined = VOS_FALSE;
        pstQosSetPara->stQos.ucCid = ucCid;
    }

    if (VOS_TRUE == pstQosQueryPara->ucMinQosFlag)
    {
        pstQosSetPara->stMinQos.ucDefined = VOS_TRUE;
        pstQosSetPara->stMinQos.ucCid = ucCid;

        pstQosSetPara->stMinQos.bitOpTrafficClass = VOS_TRUE;
        pstQosSetPara->stMinQos.ucTrafficClass    = pstQosQueryPara->stMinQos.ucTrafficClass;

        pstQosSetPara->stMinQos.bitOpDeliverOrder = VOS_TRUE;
        pstQosSetPara->stMinQos.ucDeliverOrder    = pstQosQueryPara->stMinQos.ucDeliverOrder;

        pstQosSetPara->stMinQos.bitOpDeliverErrSdu = VOS_TRUE;
        pstQosSetPara->stMinQos.ucDeliverErrSdu    = pstQosQueryPara->stMinQos.ucDeliverErrSdu;

        pstQosSetPara->stMinQos.bitOpMaxSduSize = VOS_TRUE;
        pstQosSetPara->stMinQos.usMaxSduSize    = pstQosQueryPara->stMinQos.usMaxSduSize;

        pstQosSetPara->stMinQos.bitOpMaxBitUl = VOS_TRUE;
        pstQosSetPara->stMinQos.ulMaxBitUl    = pstQosQueryPara->stMinQos.ulMaxBitUl;

        pstQosSetPara->stMinQos.bitOpMaxBitDl = VOS_TRUE;
        pstQosSetPara->stMinQos.ulMaxBitDl    = pstQosQueryPara->stMinQos.ulMaxBitDl;

        pstQosSetPara->stMinQos.bitOpResidualBer = VOS_TRUE;
        pstQosSetPara->stMinQos.ucResidualBer    = pstQosQueryPara->stMinQos.ucResidualBer;

        pstQosSetPara->stMinQos.bitOpSduErrRatio = VOS_TRUE;
        pstQosSetPara->stMinQos.ucSduErrRatio    = pstQosQueryPara->stMinQos.ucSduErrRatio;

        pstQosSetPara->stMinQos.bitOpTransDelay = VOS_TRUE;
        pstQosSetPara->stMinQos.usTransDelay    = pstQosQueryPara->stMinQos.usTransDelay;

        pstQosSetPara->stMinQos.bitOpTraffHandlePrior = VOS_TRUE;
        pstQosSetPara->stMinQos.ucTraffHandlePrior    = pstQosQueryPara->stMinQos.ucTraffHandlePrior;

        pstQosSetPara->stMinQos.bitOpGtdBitUl = VOS_TRUE;
        pstQosSetPara->stMinQos.ulGtdBitUl    = pstQosQueryPara->stMinQos.ulGuarantBitUl;

        pstQosSetPara->stMinQos.bitOpGtdBitDl  = VOS_TRUE;
        pstQosSetPara->stMinQos.ulGtdBitDl     = pstQosQueryPara->stMinQos.ulGuarantBitDl;

    }
    else
    {
        pstQosSetPara->stMinQos.ucDefined = VOS_FALSE;
        pstQosSetPara->stMinQos.ucCid = ucCid;
    }

    return;
}

/*****************************************************************************
     : AT_PS_SetQosPara
   : QOS
   : VOS_UINT16                          usClientId,
             VOS_UINT8                           ucUserCid,
             VOS_UINT8                           ucActCid
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 2013629
           : l60609
       : 

*****************************************************************************/
VOS_UINT32 AT_PS_SetQosPara(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucUserCid,
    VOS_UINT8                           ucActCid
)
{
    TAF_PS_PDP_QOS_QUERY_PARA_STRU      stQosQueryPara;
    TAF_PS_PDP_QOS_SET_PARA_STRU        stQosSetPara;

    TAF_MEM_SET_S(&stQosQueryPara, sizeof(stQosQueryPara), 0x00, sizeof(TAF_PS_PDP_QOS_QUERY_PARA_STRU));
    TAF_MEM_SET_S(&stQosSetPara, sizeof(stQosSetPara), 0x00, sizeof(TAF_PS_PDP_QOS_SET_PARA_STRU));

    /* CIDCID */
    if (ucActCid == ucUserCid)
    {
        return VOS_OK;
    }

    /* QOS */
    if (VOS_OK != TAF_AGENT_GetPdpCidQosPara(usClientId,
                                             ucUserCid,
                                             &stQosQueryPara))
    {
        AT_ERR_LOG("AT_PS_SetQosPara: ERROR: Get QOS Fail.");
        return VOS_ERR;
    }

    /* QOS */
    AT_PS_TransferQosPara(ucActCid, &stQosQueryPara, &stQosSetPara);

    /* QOS */
    if (VOS_OK != TAF_AGENT_SetPdpCidQosPara(usClientId,
                                             &stQosSetPara))
    {
        AT_ERR_LOG("AT_PS_SetQosPara: ERROR: Set QOS Fail.");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
     : AT_PS_SetupCall
   : PS
   : usClientId       - ID
             ucCallId         - 
             pstCallDialParam - 
   : 
     : VOS_OK           - 
             VOS_ERR          - 
   :
   :

       :
  1.       : 20121217
           : A00165503
       : 
*****************************************************************************/
VOS_UINT32 AT_PS_SetupCall(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId,
    AT_DIAL_PARAM_STRU                 *pstCallDialParam
)
{
    /* (CallId) */

    /* (1) CID
     *     -> : ERROR
     *     -> : 
     * (2) PS
     *     -> : ERROR
     *     -> : 
     * (3) CallId
     * (4) PDP
     * (5) CID
     * (6) 
     */
    TAF_PS_DIAL_PARA_STRU               stPsDialParamInfo;
    VOS_UINT32                          ulRslt;

    TAF_MEM_SET_S(&stPsDialParamInfo, sizeof(stPsDialParamInfo), 0x00, sizeof(TAF_PS_DIAL_PARA_STRU));

    /* QOS */
    if (VOS_OK != AT_PS_SetQosPara(usClientId, AT_PS_GetUserInfo(usClientId, ucCallId)->ucUsrCid, pstCallDialParam->ucCid))
    {
        return VOS_ERR;
    }

    /* PS */
    AT_GetPsDialParamFromAtDialParam(&stPsDialParamInfo, pstCallDialParam);

    /* PS */
    ulRslt = TAF_PS_CallOrig(WUEPS_PID_AT,
                             AT_PS_BuildExClientId(usClientId),
                             0, &stPsDialParamInfo);

    if (VOS_OK != ulRslt)
    {
        AT_ERR_LOG("AT_PS_SetupCall: Setup call failed.");
        return VOS_ERR;
    }

    /* CALLID */
    AT_PS_AssignCallIdToCid(usClientId, stPsDialParamInfo.ucCid, ucCallId);

    /* PDP */
    AT_PS_SetCurrCallType(usClientId, ucCallId, stPsDialParamInfo.enPdpType);

    /* CID */
    AT_PS_SetCid2CurrCall(usClientId, ucCallId, stPsDialParamInfo.enPdpType, stPsDialParamInfo.ucCid);

    /*  */
    AT_PS_SetCallStateByType(usClientId, ucCallId, stPsDialParamInfo.enPdpType, AT_PDP_STATE_ACTING);

    return VOS_OK;
}

/*****************************************************************************
     : AT_PS_HangupCall
   : PS
   : usClientId       - ID
             ucCallId - 
   : 
     : VOS_OK   - 
             VOS_ERR  - 
   :
   :

       :
  1.       : 20121217
           : A00165503
       : 
  2.       : 20170206
           : w00316404
       : do recovery requirement
*****************************************************************************/
VOS_UINT32 AT_PS_HangupCall(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_END_CAUSE_ENUM_UINT8    enCause
)
{
    /* (CallId) */

    /* (1) IPv4/
     *     -> : , 
     *     -> : 
     * (2) IPv6/
     *     -> : , 
     *     -> : 
     * (3) 
     */
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;

    pstCallEntity   = AT_PS_GetCallEntity(usClientId, ucCallId);

    if ( (AT_PDP_STATE_ACTED == pstCallEntity->enIpv4State)
      || (AT_PDP_STATE_ACTING == pstCallEntity->enIpv4State) )
    {
        if (VOS_OK == TAF_PS_CallEndEx(WUEPS_PID_AT,
                                       AT_PS_BuildExClientId(usClientId),
                                       0,
                                       pstCallEntity->ucIpv4Cid,
                                       enCause))
        {
            AT_PS_SetCallStateByType(usClientId, ucCallId, TAF_PDP_IPV4, AT_PDP_STATE_DEACTING);
        }
        else
        {
            AT_ERR_LOG("AT_PS_HangupCall: STEP1->End call failed.");
            return VOS_ERR;
        }
    }

    if ( (pstCallEntity->ucIpv4Cid != pstCallEntity->ucIpv6Cid)
      && ( (AT_PDP_STATE_ACTED == pstCallEntity->enIpv6State)
        || (AT_PDP_STATE_ACTING == pstCallEntity->enIpv6State) ) )
    {
        if (VOS_OK == TAF_PS_CallEndEx(WUEPS_PID_AT,
                                       AT_PS_BuildExClientId(usClientId),
                                       0,
                                       pstCallEntity->ucIpv6Cid,
                                       enCause))
        {
            AT_PS_SetCallStateByType(usClientId, ucCallId, TAF_PDP_IPV6, AT_PDP_STATE_DEACTING);
        }
        else
        {
            AT_ERR_LOG("AT_PS_HangupCall: STEP2->End call step2 failed.");
            return VOS_ERR;
        }
    }

    return VOS_OK;
}

/*****************************************************************************
     : AT_PS_ProcConflictDialUpWithCurrCall
   : 
   : ucIndex  - (ClientId)
             ucCallId - 
   : 
     : VOS_OK   - 
             VOS_ERR  - 
   :
   :

       :
  1.       : 20121217
           : A00165503
       : 
*****************************************************************************/
VOS_UINT32 AT_PS_ProcConflictDialUpWithCurrCall(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                           ucCallId
)
{
    /* (CallId) */

    /* , OK,  */
    if (VOS_TRUE == AT_PS_IsLinkGoingUp(ucIndex, ucCallId))
    {
        AT_INFO_LOG("AT_PS_ProcConflictDialUpWithCurrCall: Call is going up.");

        At_FormatResultData(ucIndex, AT_OK);

        AT_PS_ReportCurrCallConnState(ucIndex, ucCallId);

        return VOS_OK;
    }

    /* , ERROR */
    if (VOS_TRUE == AT_PS_IsLinkGoingDown(ucIndex, ucCallId))
    {
        AT_INFO_LOG("AT_PS_ProcConflictDialUpWithCurrCall: Call is going down.");

        AT_PS_SetPsCallErrCause(ucIndex, TAF_PS_CAUSE_UNKNOWN);

        At_FormatResultData(ucIndex, AT_ERROR);

        return VOS_OK;
    }

    return VOS_ERR;
}

/*****************************************************************************
     : AT_PS_ProcDialUp
   : 
   : ucIndex    - (ClientId)
   : 
     : AT_OK      - OK
             AT_ERROR   - ERROR
             AT_SUCCESS - 
   :
   :

       :
  1.       : 20121217
           : A00165503
       : 
*****************************************************************************/
VOS_UINT32 AT_PS_ProcDialUp(VOS_UINT8 ucIndex)
{
    /* (1) CID(CallId)
     * (2) 
     * (3) 
     *     -> : 
     *     -> : 
     * (4) 
     * (5) 
     */
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;
    AT_PS_USER_INFO_STRU                stUserInfo;
    AT_DIAL_PARAM_STRU                  stUsrDialParam;
    VOS_UINT8                           ucCallId;
    VOS_UINT32                          ulRslt;

    TAF_MEM_SET_S(&stUserInfo, sizeof(stUserInfo), 0x00, sizeof(AT_PS_USER_INFO_STRU));
    TAF_MEM_SET_S(&stUsrDialParam, sizeof(stUsrDialParam), 0x00, sizeof(AT_DIAL_PARAM_STRU));

    /*  */
    AT_PS_ParseUsrInfo(ucIndex, &stUserInfo);

    /*  */
    ulRslt = AT_PS_ParseUsrDialParam(ucIndex, &stUsrDialParam);

    if (VOS_OK != ulRslt)
    {
        AT_ERR_LOG("AT_PS_ProcDialUp: Get dial parameter failed.");

        AT_PS_SetPsCallErrCause(ucIndex, TAF_PS_CAUSE_UNKNOWN);

        return AT_ERROR;
    }

    /* CID */
    ucCallId = AT_PS_TransCidToCallId(ucIndex, stUsrDialParam.ucCid);

    if (AT_PS_IsCallIdValid(ucIndex, ucCallId))
    {
        ulRslt = AT_PS_ProcConflictDialUpWithCurrCall(ucIndex, ucCallId);

        if (VOS_OK != ulRslt)
        {
            AT_PS_SetPsCallErrCause(ucIndex, TAF_PS_CAUSE_UNKNOWN);

             AT_ERR_LOG("AT_PS_ProcDialUp: AT_PS_FreeCallEntity 16376.");
            AT_PS_FreeCallEntity(ucIndex, ucCallId);

            AT_ERR_LOG("AT_PS_ProcCallDialUp: Call entity status error.");
            return AT_ERROR;
        }

        return AT_SUCCESS;
    }

    /*  */
    ulRslt = AT_PS_AllocCallEntity(ucIndex, &ucCallId);

    if (VOS_OK != ulRslt)
    {
        AT_NORM_LOG("AT_PS_ProcDialUp: Alloc call entity failed.");

        AT_PS_SetPsCallErrCause(ucIndex, TAF_PS_CAUSE_UNKNOWN);

        return AT_ERROR;
    }

    pstCallEntity = AT_PS_GetCallEntity(ucIndex, ucCallId);

    /*  */
    pstCallEntity->stUserInfo = stUserInfo;

    /*  */
    pstCallEntity->stUsrDialParam = stUsrDialParam;

    /*  */
    ulRslt = AT_PS_SetupCall(stUserInfo.enUserIndex, ucCallId, &stUsrDialParam);

    if (VOS_OK != ulRslt)
    {
        /*  */
        AT_PS_SetPsCallErrCause(ucIndex, TAF_PS_CAUSE_UNKNOWN);

         AT_ERR_LOG("AT_PS_ProcDialUp: AT_PS_SetupCall AT_PS_FreeCallEntity.");

        /*  */
        AT_PS_FreeCallEntity(ucIndex, ucCallId);

        AT_ERR_LOG("AT_PS_ProcDialUp: Setup call failed.");
        return AT_ERROR;
    }

    return AT_OK;
}

/*****************************************************************************
     : AT_PS_ProcDialUp
   : 
   : ucIndex    - (ClientId)
   : 
     : AT_OK      - OK
             AT_ERROR   - ERROR
             AT_SUCCESS - 
   :
   :

       :
  1.       : 20121217
           : A00165503
       : 
*****************************************************************************/
VOS_UINT32 AT_PS_ProcDialDown(VOS_UINT8 ucIndex)
{
    /* (1) CID(CallId)
     * (2) 
     *     -> : 
     *     -> : 
     * (3) 
     * (4) 
     */

    /* CID(CallId)
     * (A) CallId
     *     -> OK
     *     -> ^DEND(or NDISSTAT)
     *     -> 
     * (B) CallId
     *     -> 
     */
    AT_PS_USER_INFO_STRU               *pstUserInfo = VOS_NULL_PTR;
    VOS_UINT8                           ucCallId;
    TAF_PS_CALL_END_CAUSE_ENUM_UINT8    enCause;

    ucCallId = AT_PS_TransCidToCallId(ucIndex, (VOS_UINT8)gastAtParaList[0].ulParaValue);

    pstUserInfo = AT_PS_GetUserInfo(ucIndex, ucCallId);

    enCause = AT_PS_TransCallEndCause((VOS_UINT8)gastAtParaList[1].ulParaValue);

    if (VOS_FALSE ==  AT_PS_IsCallIdValid(ucIndex, ucCallId))
    {
        At_FormatResultData(ucIndex, AT_OK);

        AT_PS_ReportAllCallEndState(ucIndex);

        return AT_SUCCESS;
    }

    /* 
     * (A) 
     * -> OK
     *     -> ^DEND(or NDISSTAT)
     *     -> SUCCESS
     * (B) 
     *     -> 
     */
    if (VOS_TRUE == AT_PS_IsLinkGoingDown(ucIndex, ucCallId))
    {
        At_FormatResultData(ucIndex, AT_OK);

        AT_PS_ReportCurrCallEndState(ucIndex, ucCallId);

        return AT_SUCCESS;
    }

    /*  */
    if (VOS_OK != AT_PS_HangupCall(pstUserInfo->enUserIndex, ucCallId, enCause))
    {
        AT_ERR_LOG("AT_PS_ProcDialDown: Hangup call failed.");
        return AT_ERROR;
    }
    return AT_OK;
}

/*****************************************************************************
     : AT_PS_ProcDialCmd
   : 
   : ucIndex  - (ClientId)
   : 
     : AT - 
   :
   :

       :
  1.       : 20121217
           : A00165503
       : 
*****************************************************************************/
VOS_UINT32 AT_PS_ProcDialCmd(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRslt;

    /*  */
    ulRslt = AT_PS_ValidateDialParam(ucIndex);

    if (AT_SUCCESS != ulRslt)
    {
        /* PS */
        AT_PS_SetPsCallErrCause(ucIndex, TAF_PS_CAUSE_INVALID_PARAMETER);

        return ulRslt;
    }

    if (TAF_PS_CALL_TYPE_UP == gastAtParaList[1].ulParaValue)
    {
        ulRslt = AT_PS_ProcDialUp(ucIndex);
    }
    else
    {
        ulRslt = AT_PS_ProcDialDown(ucIndex);
    }

    return ulRslt;
}
/* Added by l60609 for V9R1 IPv6&TAF/SM Project, 2013-4-24, end */

/*****************************************************************************
     : AT_PS_ProcSharePdpStateChange
   : PDPShare PDP
   : TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent,
             TAF_PDP_TYPE_ENUM_UINT8             enPdpType
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 201367
           : z00214637
       : V3R3 Share-PDP

  2.       : 20130708
           : Y00213812
       : VoLTE_PhaseI 
*****************************************************************************/
VOS_VOID  AT_PS_ProcDeactSharePdpState(
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
)
{
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity  = VOS_NULL_PTR;
    AT_PS_RPT_END_RSLT_FUNC             pRptEndRsltFunc  = VOS_NULL_PTR;

    /* SHARE-PDP */
    if (VOS_TRUE != AT_PS_GET_SHARE_PDP_FLG())
    {
        return;
    }

    /* APP PDP */
    pstAppPdpEntity                         = AT_APP_GetPdpEntInfoAddr();
    pstAppPdpEntity->stUsrInfo.enPortIndex  = AT_CLIENT_TAB_APP_INDEX;
    pstAppPdpEntity->stUsrInfo.ucUsrType    = AT_APP_USER;

    /*  */
    pRptEndRsltFunc = AT_PS_GetRptEndResultFunc(pstAppPdpEntity->stUsrInfo.ucUsrType);

    AT_PS_SendRnicPdnInfoRelInd(pstEvent->ucRabId);

    /* APPPDP */
    if (VOS_NULL_PTR != pRptEndRsltFunc)
    {
        pRptEndRsltFunc(pstEvent->ucCid,
                        pstAppPdpEntity->stUsrInfo.enPortIndex,
                        enPdpType,
                        pstEvent->enCause);
    }
    else
    {
        AT_ERR_LOG("AT_PS_ProcDeactSharePdpState:ERROR: Get End Report Func Failed!");
    }

    /* APP PDP */
    AT_PS_ResetRnicPdpDhcpPara(enPdpType);

    return;
}

/*****************************************************************************
     : AT_PS_ProcActSharePdpState
   : PDPShare PDP
   : TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent,
             TAF_PDP_TYPE_ENUM_UINT8             enPdpType
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 201367
           : z00214637
       : V3R3 Share-PDP

  2.       : 20130708
           : Y00213812
       : VoLTE_PhaseI 
*****************************************************************************/
VOS_VOID  AT_PS_ProcActSharePdpState(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
)
{
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity  = VOS_NULL_PTR;
    AT_PS_RPT_CONN_RSLT_FUNC            pRptConnRsltFunc = VOS_NULL_PTR;

    /* SHARE-PDP */
    if (VOS_TRUE != AT_PS_GET_SHARE_PDP_FLG())
    {
        return;
    }

    /* APP PDP */
    pstAppPdpEntity                         = AT_APP_GetPdpEntInfoAddr();
    pstAppPdpEntity->stUsrInfo.enPortIndex  = AT_CLIENT_TAB_APP_INDEX;
    pstAppPdpEntity->stUsrInfo.ucUsrType    = AT_APP_USER;

    /*  */
    pRptConnRsltFunc = AT_PS_GetRptConnResultFunc(pstAppPdpEntity->stUsrInfo.ucUsrType);

    if (TAF_PDP_IPV4 == enPdpType)
    {
        AT_PS_SaveRnicPdpDhcpPara(TAF_PDP_IPV4, pstEvent);
        AT_PS_SendRnicPdnInfoCfgInd(TAF_PDP_IPV4, pstEvent->ucRabId, AT_APP_GetPdpEntInfoAddr());

        /* APPIPv4 */
        if (VOS_NULL_PTR != pRptConnRsltFunc)
        {
            pRptConnRsltFunc(pstEvent->ucCid,
                             pstAppPdpEntity->stUsrInfo.enPortIndex,
                             TAF_PDP_IPV4);
        }
        else
        {
            AT_ERR_LOG("AT_PS_ProcActSharePdpState:ERROR: Get Connet Report Func Failed!");
        }
    }

    if (TAF_PDP_IPV6 == enPdpType)
    {
        AT_PS_SaveRnicPdpDhcpPara(TAF_PDP_IPV6, pstEvent);
    }

    if (TAF_PDP_IPV4V6 == enPdpType)
    {
        AT_PS_SaveRnicPdpDhcpPara(TAF_PDP_IPV4V6, pstEvent);
        AT_PS_SendRnicPdnInfoCfgInd(TAF_PDP_IPV4, pstEvent->ucRabId, AT_APP_GetPdpEntInfoAddr());

        /* APPIPv4 */
        if (VOS_NULL_PTR != pRptConnRsltFunc)
        {
            pRptConnRsltFunc(pstEvent->ucCid,
                             pstAppPdpEntity->stUsrInfo.enPortIndex,
                             TAF_PDP_IPV4);
        }
        else
        {
            AT_ERR_LOG("AT_PS_ProcActSharePdpState:ERROR: Get Connet Report Func Failed!");
        }
    }

    return;
}

/*****************************************************************************
     : AT_PS_ProcSharePdpIpv6RaInfo
   : Share-PDPRouter Advertisement IP, PDN
   : pstRaInfoNotifyInd         - RA
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 201366
           : L47619
       : V3R3 Share-PDP

*****************************************************************************/
VOS_VOID AT_PS_ProcSharePdpIpv6RaInfo(
    TAF_PS_IPV6_INFO_IND_STRU *pstRaInfoNotifyInd
)
{
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity                      = VOS_NULL_PTR;
    AT_IPV6_RA_INFO_STRU               *pstAppRaInfoAddr                     = VOS_NULL_PTR;
    AT_PS_RPT_CONN_RSLT_FUNC            pRptConnRsltFunc                     = VOS_NULL_PTR;
    VOS_UINT8                           aucIpv6LanAddr[TAF_IPV6_ADDR_LEN] = {0};

    /* SHARE-PDP */
    if (VOS_TRUE != AT_PS_GET_SHARE_PDP_FLG())
    {
        return;
    }

    /* RaInfo */
    if (0 == pstRaInfoNotifyInd->stIpv6RaInfo.ulPrefixNum)
    {
        AT_NORM_LOG("AT_PS_ProcSharePdpIpv6RaInfo: No IPv6 prefix address in RA.");
        return;
    }

    /* APP PDPRaInfo */
    pstAppRaInfoAddr = AT_APP_GetRaInfoAddr();
    pstAppPdpEntity  = AT_APP_GetPdpEntInfoAddr();

    /*  */
    pRptConnRsltFunc = AT_PS_GetRptConnResultFunc(pstAppPdpEntity->stUsrInfo.ucUsrType);

    /* IPv6, ^DCONN */
    if (VOS_FALSE == pstAppRaInfoAddr->bitOpPrefixAddr)
    {
        /* APPIPv6 */
        if (VOS_NULL_PTR != pRptConnRsltFunc)
        {
            pRptConnRsltFunc(pstRaInfoNotifyInd->ucCid,
                             pstAppPdpEntity->stUsrInfo.enPortIndex,
                             TAF_PDP_IPV6);
        }
        else
        {
            AT_ERR_LOG("AT_PS_ProcSharePdpIpv6RaInfo:ERROR: Get Connet Report Func Failed!");
        }

        /* IPv6 */
        pstAppRaInfoAddr->bitOpPrefixAddr        = VOS_TRUE;
        pstAppRaInfoAddr->ulPrefixBitLen         = pstRaInfoNotifyInd->stIpv6RaInfo.astPrefixList[0].ulBitPrefixLen;
        TAF_MEM_CPY_S(pstAppRaInfoAddr->aucPrefixAddr,
                   sizeof(pstAppRaInfoAddr->aucPrefixAddr),
                   pstRaInfoNotifyInd->stIpv6RaInfo.astPrefixList[0].aucPrefix,
                   TAF_IPV6_ADDR_LEN);

        /* IPv6 */
        AT_PS_GenIpv6LanAddrWithRadomIID(pstRaInfoNotifyInd->stIpv6RaInfo.astPrefixList[0].aucPrefix,
                                         pstRaInfoNotifyInd->stIpv6RaInfo.astPrefixList[0].ulBitPrefixLen/8,
                                         aucIpv6LanAddr);

        /* IPv6 */
        pstAppRaInfoAddr->bitOpLanAddr           = VOS_TRUE;
        TAF_MEM_CPY_S(pstAppRaInfoAddr->aucLanAddr, sizeof(pstAppRaInfoAddr->aucLanAddr), aucIpv6LanAddr, TAF_IPV6_ADDR_LEN);

        /* DHCPV6IPv6 */
        TAF_MEM_CPY_S(pstAppPdpEntity->stIpv6Dhcp.aucIpv6Addr, sizeof(pstAppPdpEntity->stIpv6Dhcp.aucIpv6Addr), aucIpv6LanAddr, TAF_IPV6_ADDR_LEN);
    }

    /* Preferred Lifetime */
    pstAppRaInfoAddr->bitOpPreferredLifetime = VOS_TRUE;
    pstAppRaInfoAddr->ulPreferredLifetime    = pstRaInfoNotifyInd->stIpv6RaInfo.astPrefixList[0].ulPreferredLifeTime;

    /* Valid Lifetime */
    pstAppRaInfoAddr->bitOpValidLifetime     = VOS_TRUE;
    pstAppRaInfoAddr->ulValidLifetime        = pstRaInfoNotifyInd->stIpv6RaInfo.astPrefixList[0].ulValidLifeTime;

    /* IPv6 MTU */
    if (VOS_TRUE == pstRaInfoNotifyInd->stIpv6RaInfo.bitOpMtu)
    {
        pstAppRaInfoAddr->bitOpMtuSize       = VOS_TRUE;
        pstAppRaInfoAddr->ulMtuSize          = pstRaInfoNotifyInd->stIpv6RaInfo.ulMtu;
    }

    /* RNIC PDN */
    AT_PS_SendRnicPdnInfoCfgInd(TAF_PDP_IPV6, pstRaInfoNotifyInd->ucRabId, AT_APP_GetPdpEntInfoAddr());

    return;
}

/******************************************************************************
     : AT_PS_SaveRnicPdpDhcpPara
   : NDIS PDPDHCPAPP PDP
   : TAF_PDP_TYPE_ENUM_UINT8             ucPdpType,
             TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
   : 
     : 
   :
   :

       :
  1.       : 201365
           : z00214637
       : 
******************************************************************************/
VOS_VOID AT_PS_SaveRnicPdpDhcpPara(
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity;

    pstAppPdpEntity                     = AT_APP_GetPdpEntInfoAddr();

    switch(enPdpType)
    {
        case TAF_PDP_IPV4:

            /* DHCP */
            AT_AppDhcpReset();

            /* IPv4PDPCID */
            pstAppPdpEntity->ucIpv4Cid  = pstEvent->ucCid;

            /* PDP */
            AT_AppSetPdpState(TAF_PDP_IPV4, AT_PDP_STATE_ACTED);

            /* IPv4DHCP */
            AT_CtrlConnIndProc(pstEvent, AT_APP_USER);
            break;

        case TAF_PDP_IPV6:
            /* DHCPv6 */
            AT_AppDhcpv6Reset();

            /* PDPCID */
            pstAppPdpEntity->ucIpv6Cid  = pstEvent->ucCid;

            /* IPv6 */
            AT_AppSetPdpState(TAF_PDP_IPV6, AT_PDP_STATE_ACTED);

            /* IPV6 */
            AT_AppCtrlConnIpv6IndProc(pstAppPdpEntity, pstEvent);
            break;

        case TAF_PDP_IPV4V6:
            /* DHCP */
            AT_AppDhcpReset();

            /* DHCPv6 */
            AT_AppDhcpv6Reset();

            /* PDPCID */
            pstAppPdpEntity->ucIpv4v6Cid   = pstEvent->ucCid;

            /* IPv6 */
            AT_AppSetPdpState(TAF_PDP_IPV4V6, AT_PDP_STATE_ACTED);

            /* IPV4 */
            AT_CtrlConnIndProc(pstEvent, AT_APP_USER);

            /* IPV6*/
            AT_AppCtrlConnIpv6IndProc(pstAppPdpEntity, pstEvent);
            break;

        default:
            AT_WARN_LOG("AT_PS_SaveRnicPdpDhcpPara:PDP type is invaild!");
            break;
    }
}

/******************************************************************************
     : AT_PS_ResetRnicPdpDhcpPara
   : NDIS PDPAppPdpEntity
   : ucPdpType - PDP
   : 
     : 
   :
   :

       :
  1.       : 201365
           : z00214637
       : 
******************************************************************************/
VOS_VOID AT_PS_ResetRnicPdpDhcpPara(
    TAF_PDP_TYPE_ENUM_UINT8             ucPdpType
)
{
    switch(ucPdpType)
    {
        case TAF_PDP_IPV4:
            /* IPv4PDPIDLE */
            AT_AppSetPdpState(TAF_PDP_IPV4, AT_PDP_STATE_IDLE);

            /* DHCP */
            AT_AppDhcpReset();
            break;

        case TAF_PDP_IPV6:
            /* IPv6PDPIDLE */
            AT_AppSetPdpState(TAF_PDP_IPV6, AT_PDP_STATE_IDLE);

            /* DHCPv6 */
            AT_AppDhcpv6Reset();
            break;

        case TAF_PDP_IPV4V6:
            /* IPv4\IPv6PDPIDLE */
            AT_AppSetPdpState(TAF_PDP_IPV4V6, AT_PDP_STATE_IDLE);

            /* DHCP\DHCPv6 */
            AT_AppDhcpReset();
            AT_AppDhcpv6Reset();
            break;

        default:
            AT_WARN_LOG("AT_PS_ResetRnicPdpDhcpPara:PDP type is invaild!");
            break;
    }
}

/*****************************************************************************
     : AT_PS_SendRnicPdnInfoCfgInd
   : RNICPDN
   : TAF_PDP_TYPE_ENUM_UINT8             ucPdpType,
             VOS_UINT8                           ucRabId,
             AT_PDP_ENTITY_STRU                 *pstAppPdpEntity
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 201364
           : z00214637
       : V3R3 Share-PDP
  2.       : 20120807
           : f00179208
       : :DTS2015031000157, p-cscf
*****************************************************************************/
VOS_UINT32 AT_PS_SendRnicPdnInfoCfgInd(
    TAF_PDP_TYPE_ENUM_UINT8             ucPdpType,
    VOS_UINT8                           ucRabId,
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity
)
{

    AT_RNIC_PDN_INFO_CFG_IND_STRU      *pstRnicPdnCfgInd;

    /* AT_RNIC_PDN_INFO_CFG_IND_STRU */
    pstRnicPdnCfgInd = (AT_RNIC_PDN_INFO_CFG_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                        WUEPS_PID_AT,
                        sizeof(AT_RNIC_PDN_INFO_CFG_IND_STRU));

    if (VOS_NULL_PTR == pstRnicPdnCfgInd)
    {
        AT_WARN_LOG("AT_PS_SendRnicPdnInfoCfgInd: Alloc Msg Fail!");
        return VOS_ERR;
    }

    /*  */
    TAF_MEM_SET_S((VOS_CHAR*)pstRnicPdnCfgInd + VOS_MSG_HEAD_LENGTH,
               (VOS_SIZE_T)(sizeof(AT_RNIC_PDN_INFO_CFG_IND_STRU) - VOS_MSG_HEAD_LENGTH),
               0x00,
               (VOS_SIZE_T)(sizeof(AT_RNIC_PDN_INFO_CFG_IND_STRU) - VOS_MSG_HEAD_LENGTH));

    /*  */
    pstRnicPdnCfgInd->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstRnicPdnCfgInd->ulReceiverPid   = ACPU_PID_RNIC;

    /*  */
    pstRnicPdnCfgInd->enMsgId   = ID_AT_RNIC_PDN_INFO_CFG_IND;
    pstRnicPdnCfgInd->ucRabId   = ucRabId;
    pstRnicPdnCfgInd->ucRmNetId = RNIC_RMNET_ID_0;

    if (TAF_PDP_IPV4 == ucPdpType)
    {
        pstRnicPdnCfgInd->bitOpIpv4PdnInfo  = VOS_TRUE;

        /* IPv4 PDN */
        pstRnicPdnCfgInd->stIpv4PdnInfo.ulPdnAddr       = pstAppPdpEntity->stIpv4Dhcp.ulIpv4Addr;
        pstRnicPdnCfgInd->stIpv4PdnInfo.ulSubnetMask    = pstAppPdpEntity->stIpv4Dhcp.ulIpv4NetMask;
        pstRnicPdnCfgInd->stIpv4PdnInfo.ulGateWayAddr   = pstAppPdpEntity->stIpv4Dhcp.ulIpv4GateWay;
        pstRnicPdnCfgInd->stIpv4PdnInfo.ulDnsPrimAddr   = pstAppPdpEntity->stIpv4Dhcp.ulIpv4PrimDNS;
        pstRnicPdnCfgInd->stIpv4PdnInfo.ulDnsSecAddr    = pstAppPdpEntity->stIpv4Dhcp.ulIpv4SecDNS;
        pstRnicPdnCfgInd->stIpv4PdnInfo.ulWinnsPrimAddr = pstAppPdpEntity->stIpv4Dhcp.ulIpv4PrimWINNS;
        pstRnicPdnCfgInd->stIpv4PdnInfo.ulWinnsSecAddr  = pstAppPdpEntity->stIpv4Dhcp.bitOpIpv4SecWINNS;
        pstRnicPdnCfgInd->stIpv4PdnInfo.ulPcscfPrimAddr = pstAppPdpEntity->stIpv4Dhcp.stIpv4PcscfList.aulIpv4PcscfAddrList[0];
        pstRnicPdnCfgInd->stIpv4PdnInfo.ulPcscfSecAddr  = pstAppPdpEntity->stIpv4Dhcp.stIpv4PcscfList.aulIpv4PcscfAddrList[1];

        pstRnicPdnCfgInd->stIpv4PdnInfo.ulPcscfThiAddr  = pstAppPdpEntity->stIpv4Dhcp.stIpv4PcscfList.aulIpv4PcscfAddrList[2];

    }
    else if(TAF_PDP_IPV6 == ucPdpType)
    {
        pstRnicPdnCfgInd->bitOpIpv6PdnInfo              = VOS_TRUE;

        /* IPv6 PDN */
        TAF_MEM_CPY_S(pstRnicPdnCfgInd->stIpv6PdnInfo.aucPdnAddr,
                   sizeof(pstRnicPdnCfgInd->stIpv6PdnInfo.aucPdnAddr),
                   pstAppPdpEntity->stIpv6Dhcp.aucIpv6Addr,
                   TAF_IPV6_ADDR_LEN);

        TAF_MEM_CPY_S(pstRnicPdnCfgInd->stIpv6PdnInfo.aucDnsPrimAddr,
                   sizeof(pstRnicPdnCfgInd->stIpv6PdnInfo.aucDnsPrimAddr),
                   pstAppPdpEntity->stIpv6Dhcp.aucIpv6PrimDNS,
                   TAF_IPV6_ADDR_LEN);

        TAF_MEM_CPY_S(pstRnicPdnCfgInd->stIpv6PdnInfo.aucDnsSecAddr,
                   sizeof(pstRnicPdnCfgInd->stIpv6PdnInfo.aucDnsSecAddr),
                   pstAppPdpEntity->stIpv6Dhcp.aucIpv6SecDNS,
                   TAF_IPV6_ADDR_LEN);

        TAF_MEM_CPY_S(pstRnicPdnCfgInd->stIpv6PdnInfo.aucPcscfPrimAddr,
                      sizeof(pstRnicPdnCfgInd->stIpv6PdnInfo.aucPcscfPrimAddr),
                      pstAppPdpEntity->stIpv6Dhcp.stIpv6PcscfList.astIpv6PcscfAddrList[0].aucPcscfAddr,
                      TAF_IPV6_ADDR_LEN);

        TAF_MEM_CPY_S(pstRnicPdnCfgInd->stIpv6PdnInfo.aucPcscfSecAddr,
                      sizeof(pstRnicPdnCfgInd->stIpv6PdnInfo.aucPcscfSecAddr),
                      pstAppPdpEntity->stIpv6Dhcp.stIpv6PcscfList.astIpv6PcscfAddrList[1].aucPcscfAddr,
                      TAF_IPV6_ADDR_LEN);

        TAF_MEM_CPY_S(pstRnicPdnCfgInd->stIpv6PdnInfo.aucPcscfThiAddr,
                      sizeof(pstRnicPdnCfgInd->stIpv6PdnInfo.aucPcscfThiAddr),
                      pstAppPdpEntity->stIpv6Dhcp.stIpv6PcscfList.astIpv6PcscfAddrList[2].aucPcscfAddr,
                      TAF_IPV6_ADDR_LEN);

    }
    else
    {
        AT_WARN_LOG("AT_PS_SendRnicPdnInfoCfgInd:PDP type is invaild!");

        PS_FREE_MSG(WUEPS_PID_AT, pstRnicPdnCfgInd);
        return VOS_OK;
    }

    /*  */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_AT, pstRnicPdnCfgInd))
    {
        AT_WARN_LOG("AT_PS_SendRnicPdnInfoCfgInd: Send Msg Fail!");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
     : AT_PS_SendRnicPdnInfoRelInd
   : RNICPDN
   : AT_PDP_ENTITY_STRU                 *pstAppPdpEntity
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 201364
           : z00214637
       : V3R3 Share-PDP
*****************************************************************************/
VOS_UINT32 AT_PS_SendRnicPdnInfoRelInd(
    VOS_UINT8                           ucRabId
)
{
    AT_RNIC_PDN_INFO_REL_IND_STRU      *pstRnicPdnRelInd;

    /* AT_RNIC_PDN_INFO_REL_IND_STRU */
    pstRnicPdnRelInd = (AT_RNIC_PDN_INFO_REL_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                        WUEPS_PID_AT,
                        sizeof(AT_RNIC_PDN_INFO_REL_IND_STRU));

    if (VOS_NULL_PTR == pstRnicPdnRelInd)
    {
        AT_WARN_LOG("AT_PS_SendRnicPdnInfoRelInd: Alloc Msg Fail!");
        return VOS_ERR;
    }

    /*  */
    TAF_MEM_SET_S((VOS_CHAR *)pstRnicPdnRelInd + VOS_MSG_HEAD_LENGTH,
               (VOS_SIZE_T)(sizeof(AT_RNIC_PDN_INFO_REL_IND_STRU) - VOS_MSG_HEAD_LENGTH),
               0x00,
               (VOS_SIZE_T)(sizeof(AT_RNIC_PDN_INFO_REL_IND_STRU) - VOS_MSG_HEAD_LENGTH));

    /*  */
    pstRnicPdnRelInd->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstRnicPdnRelInd->ulReceiverPid   = ACPU_PID_RNIC;

    /*  */
    pstRnicPdnRelInd->enMsgId         = ID_AT_RNIC_PDN_INFO_REL_IND;
    pstRnicPdnRelInd->ucRabId         = ucRabId;
    pstRnicPdnRelInd->ucRmNetId       = RNIC_RMNET_ID_0;

    /*  */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_AT, pstRnicPdnRelInd))
    {
        AT_WARN_LOG("AT_PS_SendRnicPdnInfoRelInd: Send Msg Fail!");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
     : AT_PS_BuildExClientId
   : ClientId(ModemId + ClientId)
   : usClientId                 - ClientId
   : 
     : VOS_UINT16                 - ClientId
   :
   :

       :
  1.       : 20160219
           : w00316404
       : 
*****************************************************************************/
VOS_UINT16 AT_PS_BuildExClientId(VOS_UINT16 usClientId)
{
    MODEM_ID_ENUM_UINT16                enModemId;

    enModemId = MODEM_ID_0;

    if (VOS_OK != AT_GetModemIdFromClient(usClientId, &enModemId))
    {
        enModemId =  MODEM_ID_BUTT;
    }

    return TAF_PS_BUILD_EXCLIENTID(enModemId, usClientId);
}

/*****************************************************************************
     : AT_PS_BuildNdisExClientId
   : ClientId(ModemId + ClientId)
   : usPortIndex                - 
             usClientId                 - ClientId
   : 
     : VOS_UINT16                 - ClientId
   :
   :

       :
  1.       : 20160219
           : w00316404
       : 
*****************************************************************************/
VOS_UINT16 AT_PS_BuildNdisExClientId(
    VOS_UINT16                          usPortIndex,
    VOS_UINT16                          usClientId
)
{
    MODEM_ID_ENUM_UINT16                enModemId;

    enModemId = MODEM_ID_0;

    if (VOS_OK != AT_GetModemIdFromClient(usPortIndex, &enModemId))
    {
        enModemId =  MODEM_ID_BUTT;
    }

    return TAF_PS_BUILD_EXCLIENTID(enModemId, usClientId);
}




/*****************************************************************************
     : AT_PS_CheckDialRatType
   : 
   : VOS_UINT8                           ucIndex
             VOS_UINT8                           ucBitRatType
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 2016223
           : Y00213812
       : 

*****************************************************************************/
VOS_UINT32 AT_PS_CheckDialRatType(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                           ucBitRatType
)
{
    if (VOS_TRUE == At_CheckCurrRatModeIsCL(ucIndex))
    {
        switch (ucBitRatType)
        {
            case AT_PS_DIAL_RAT_TYPE_NO_ASTRICT:
            case AT_PS_DIAL_RAT_TYPE_1X_OR_HRPD:
            case AT_PS_DIAL_RAT_TYPE_LTE_OR_EHRPD:
                return VOS_TRUE;

            default:
                AT_NORM_LOG1("AT_PS_CheckDialRatType: Rat Type Error.\n", ucBitRatType);
                return VOS_FALSE;
        }
    }
    else
    {
        AT_NORM_LOG("AT_PS_CheckDialRatType: Not CL mode.\n");
        return VOS_FALSE;
    }

}

/*****************************************************************************
     : AT_PS_ProcRabidChangedEvent
   : RabId
   : TAF_PS_CALL_PDP_RABID_CHANGE_IND_STRU  *pstEvent
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 201663
           : Y00213812
       : 

*****************************************************************************/
VOS_VOID AT_PS_ProcRabidChangedEvent(
    TAF_PS_CALL_PDP_RABID_CHANGE_IND_STRU  *pstEvent
)
{
    VOS_UINT8                               ucCallId;
    AT_PS_CALL_ENTITY_STRU                 *pstCallEntity   = VOS_NULL_PTR;
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU      *pstActEvent     = VOS_NULL_PTR;
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU     stDeactEvent;

    ucCallId = AT_PS_TransCidToCallId(pstEvent->stCtrl.usClientId, pstEvent->ucCid);

    if (VOS_FALSE == AT_PS_IsCallIdValid(pstEvent->stCtrl.usClientId, ucCallId))
    {
        AT_ERR_LOG("AT_PS_ProcRabidChangedEvent:ERROR: CallId is invalid!");
        return;
    }

    /*--------------------------1.----------------------------*/

    TAF_MEM_SET_S(&stDeactEvent,
                  sizeof(stDeactEvent),
                  0,
                  sizeof(TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU));

    TAF_MEM_CPY_S(&stDeactEvent.stCtrl,
                  sizeof(TAF_CTRL_STRU),
                  &pstEvent->stCtrl,
                  sizeof(TAF_CTRL_STRU));

    stDeactEvent.ucRabId                = pstEvent->ucOldRabId;
    stDeactEvent.enPdpType              = pstEvent->enPdpType;

    /* PDP */
    AT_PS_DeactivateRmNet(ucCallId, &stDeactEvent, pstEvent->enPdpType);

    /* FC */
    AT_PS_DeRegFCPoint(ucCallId, &stDeactEvent);


    /*--------------------------2.----------------------------*/

    pstActEvent = (TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF,
                      sizeof(TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU));

    /*  */
    if (VOS_NULL_PTR == pstActEvent)
    {
        /* ,  */
        AT_ERR_LOG("AT_PS_ProcRabidChangedEvent: PS_MEM_ALLOC Error!");
        return;
    }

    TAF_MEM_SET_S(pstActEvent,
                  sizeof(TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU),
                  0,
                  sizeof(TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU));

    TAF_MEM_CPY_S(&pstActEvent->stCtrl,
                  sizeof(TAF_CTRL_STRU),
                  &pstEvent->stCtrl,
                  sizeof(TAF_CTRL_STRU));

    pstActEvent->ucRabId                = pstEvent->ucNewRabId;

    /* PDP */
    AT_PS_ActivateRmNet(ucCallId, pstActEvent, pstEvent->enPdpType);

    /* FC */
    AT_PS_RegFCPoint(ucCallId, pstActEvent);

    PS_MEM_FREE(WUEPS_PID_TAF, pstActEvent);


    /*--------------------------3.AT----------------------------*/

    pstCallEntity = AT_PS_GetCallEntity(pstEvent->stCtrl.usClientId, ucCallId);

    if (TAF_PDP_IPV4 == (pstEvent->enPdpType & TAF_PDP_IPV4))
    {
        pstCallEntity->stIpv4DhcpInfo.ucRabId   = pstEvent->ucNewRabId;
    }

    if (TAF_PDP_IPV6 == (pstEvent->enPdpType & TAF_PDP_IPV6))
    {
        pstCallEntity->stIpv6DhcpInfo.ucRabId   = pstEvent->ucNewRabId;
    }

    return;
}


