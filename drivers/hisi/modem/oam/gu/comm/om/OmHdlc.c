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

/******************************************************************************

                   (C), 2001-2011, 

 ******************************************************************************
       : OM_Hdlc.c
       : 
         : zengfei 57034
     : 200864
     :
     :
     :
     :
  1.       : 200864
           : zengfei 57034
       : 

******************************************************************************/



/******************************************************************************
   1 
******************************************************************************/
#include "OmHdlcInterface.h"

/******************************************************************************
   2 
******************************************************************************/


/******************************************************************************
   3 
******************************************************************************/


/******************************************************************************
   4 
******************************************************************************/
/* FCS16FCS
    rfc1662: the lookup table used to calculate the FCS-16. */
VOS_UINT16 const g_ausOmHdlcFcsTab[256] = {
   /* 00 */ 0x0000, 0x1189, 0x2312, 0x329b, 0x4624, 0x57ad, 0x6536, 0x74bf,
   /* 08 */ 0x8c48, 0x9dc1, 0xaf5a, 0xbed3, 0xca6c, 0xdbe5, 0xe97e, 0xf8f7,
   /* 10 */ 0x1081, 0x0108, 0x3393, 0x221a, 0x56a5, 0x472c, 0x75b7, 0x643e,
   /* 18 */ 0x9cc9, 0x8d40, 0xbfdb, 0xae52, 0xdaed, 0xcb64, 0xf9ff, 0xe876,
   /* 20 */ 0x2102, 0x308b, 0x0210, 0x1399, 0x6726, 0x76af, 0x4434, 0x55bd,
   /* 28 */ 0xad4a, 0xbcc3, 0x8e58, 0x9fd1, 0xeb6e, 0xfae7, 0xc87c, 0xd9f5,
   /* 30 */ 0x3183, 0x200a, 0x1291, 0x0318, 0x77a7, 0x662e, 0x54b5, 0x453c,
   /* 38 */ 0xbdcb, 0xac42, 0x9ed9, 0x8f50, 0xfbef, 0xea66, 0xd8fd, 0xc974,
   /* 40 */ 0x4204, 0x538d, 0x6116, 0x709f, 0x0420, 0x15a9, 0x2732, 0x36bb,
   /* 48 */ 0xce4c, 0xdfc5, 0xed5e, 0xfcd7, 0x8868, 0x99e1, 0xab7a, 0xbaf3,
   /* 50 */ 0x5285, 0x430c, 0x7197, 0x601e, 0x14a1, 0x0528, 0x37b3, 0x263a,
   /* 58 */ 0xdecd, 0xcf44, 0xfddf, 0xec56, 0x98e9, 0x8960, 0xbbfb, 0xaa72,
   /* 60 */ 0x6306, 0x728f, 0x4014, 0x519d, 0x2522, 0x34ab, 0x0630, 0x17b9,
   /* 68 */ 0xef4e, 0xfec7, 0xcc5c, 0xddd5, 0xa96a, 0xb8e3, 0x8a78, 0x9bf1,
   /* 70 */ 0x7387, 0x620e, 0x5095, 0x411c, 0x35a3, 0x242a, 0x16b1, 0x0738,
   /* 78 */ 0xffcf, 0xee46, 0xdcdd, 0xcd54, 0xb9eb, 0xa862, 0x9af9, 0x8b70,
   /* 80 */ 0x8408, 0x9581, 0xa71a, 0xb693, 0xc22c, 0xd3a5, 0xe13e, 0xf0b7,
   /* 88 */ 0x0840, 0x19c9, 0x2b52, 0x3adb, 0x4e64, 0x5fed, 0x6d76, 0x7cff,
   /* 90 */ 0x9489, 0x8500, 0xb79b, 0xa612, 0xd2ad, 0xc324, 0xf1bf, 0xe036,
   /* 98 */ 0x18c1, 0x0948, 0x3bd3, 0x2a5a, 0x5ee5, 0x4f6c, 0x7df7, 0x6c7e,
   /* a0 */ 0xa50a, 0xb483, 0x8618, 0x9791, 0xe32e, 0xf2a7, 0xc03c, 0xd1b5,
   /* a8 */ 0x2942, 0x38cb, 0x0a50, 0x1bd9, 0x6f66, 0x7eef, 0x4c74, 0x5dfd,
   /* b0 */ 0xb58b, 0xa402, 0x9699, 0x8710, 0xf3af, 0xe226, 0xd0bd, 0xc134,
   /* b8 */ 0x39c3, 0x284a, 0x1ad1, 0x0b58, 0x7fe7, 0x6e6e, 0x5cf5, 0x4d7c,
   /* c0 */ 0xc60c, 0xd785, 0xe51e, 0xf497, 0x8028, 0x91a1, 0xa33a, 0xb2b3,
   /* c8 */ 0x4a44, 0x5bcd, 0x6956, 0x78df, 0x0c60, 0x1de9, 0x2f72, 0x3efb,
   /* d0 */ 0xd68d, 0xc704, 0xf59f, 0xe416, 0x90a9, 0x8120, 0xb3bb, 0xa232,
   /* d8 */ 0x5ac5, 0x4b4c, 0x79d7, 0x685e, 0x1ce1, 0x0d68, 0x3ff3, 0x2e7a,
   /* e0 */ 0xe70e, 0xf687, 0xc41c, 0xd595, 0xa12a, 0xb0a3, 0x8238, 0x93b1,
   /* e8 */ 0x6b46, 0x7acf, 0x4854, 0x59dd, 0x2d62, 0x3ceb, 0x0e70, 0x1ff9,
   /* f0 */ 0xf78f, 0xe606, 0xd49d, 0xc514, 0xb1ab, 0xa022, 0x92b9, 0x8330,
   /* f8 */ 0x7bc7, 0x6a4e, 0x58d5, 0x495c, 0x3de3, 0x2c6a, 0x1ef1, 0x0f78
};



/******************************************************************************
   5 
******************************************************************************/

/*****************************************************************************
     : Om_HdlcEncap
   : HDLC
   : VOS_UINT8 *pucSrc
             VOS_UINT16 usSrcLen
             VOS_UINT8 *pucDest
             VOS_UINT16 usDestBuffLen
   : VOS_UINT16* pusDestLen
     : VOS_UINT32
             PS_SUCC: 
             PS_FAIL: 

   :
   :

       :
  1.       : 200863
           : zengfei 57034
       : 

*****************************************************************************/
VOS_UINT32 Om_HdlcEncap(
                const VOS_UINT8  *pucSrc,
                VOS_UINT16  usSrcLen,
                VOS_UINT8  *pucDest,
                VOS_UINT16  usDestBuffLen,
                VOS_UINT16 *pusDestLen )
{
    VOS_UINT16  usFcs       = OM_HDLC_INIT_FCS;
    VOS_UINT8  *pucDestPos  = pucDest;
    VOS_UINT8   ucFcsChar;

    if ((VOS_NULL_PTR == pucSrc) || (VOS_NULL_PTR == pucDest) ||(VOS_NULL_PTR == pusDestLen))
    {
        (VOS_VOID)vos_printf("\n\rERROR, Om_HdlcEncap, Pointer Para is NULL !\n\r");
        return VOS_ERR;
    }

    if (0 == usSrcLen)
    {
        *pusDestLen = 0;
        (VOS_VOID)vos_printf("\n\rWARNING, Om_HdlcEncap, Src Data Len is 0 !\n\r");
        return VOS_ERR;
    }

    if (usDestBuffLen <= 4)             /* 0HDLC5 */
    {
        *pusDestLen = 0;
        (VOS_VOID)vos_printf("\n\rWARNING, Om_HdlcEncap, Dst Buf is not Enough #1:BufLen:%d !\n\r", usDestBuffLen);
        return VOS_ERR;
    }

    /*  */
    *pucDestPos++   = OM_HDLC_FRAME_FLAG;

    /* FCS */
    while (usSrcLen-- && ((pucDestPos - pucDest) <= (usDestBuffLen - 3)))
    {
        usFcs = (usFcs >> 8) ^ g_ausOmHdlcFcsTab[(usFcs ^ *pucSrc) & 0xff];

        if ((OM_HDLC_FRAME_FLAG == *pucSrc) || (OM_HDLC_ESC == *pucSrc))
        {
            *pucDestPos++ = OM_HDLC_ESC;
            *pucDestPos++ = (*pucSrc++) ^ OM_HDLC_ESC_MASK;
        }
        else
        {
            *pucDestPos++ = *pucSrc++;
        }
    }

    /* BUFFERFCS */
    if ((pucDestPos - pucDest) > (usDestBuffLen - 3))
    {
        *pusDestLen = 0;
        (VOS_VOID)vos_printf("\n\rWARNING, Om_HdlcEncap, Dst Buf is not Enough #2:BufLen:%d !\n\r", usDestBuffLen);
        return VOS_ERR;
    }

    usFcs       = ~usFcs;

    /* FCS */
    ucFcsChar   = usFcs & 0xFF;
    if ((OM_HDLC_FRAME_FLAG == ucFcsChar) || (OM_HDLC_ESC == ucFcsChar))
    {
        *pucDestPos++ = OM_HDLC_ESC;
        *pucDestPos++ = ucFcsChar ^ OM_HDLC_ESC_MASK;
    }
    else
    {
        *pucDestPos++ = ucFcsChar;
    }

    /* BUFFERFCS */
    if ((pucDestPos - pucDest) > (usDestBuffLen - 2))
    {
        *pusDestLen = 0;
        (VOS_VOID)vos_printf("\n\rWARNING, Om_HdlcEncap, Dst Buf is not Enough #3:BufLen:%d !\n\r", usDestBuffLen);
        return VOS_ERR;
    }

    /* FCS */
    ucFcsChar       = (usFcs >> 8) & 0xFF;
    if ((OM_HDLC_FRAME_FLAG == ucFcsChar) || (OM_HDLC_ESC == ucFcsChar))
    {
        *pucDestPos++ = OM_HDLC_ESC;
        *pucDestPos++ = ucFcsChar ^ OM_HDLC_ESC_MASK;
    }
    else
    {
        *pucDestPos++ = ucFcsChar;
    }

    /* BUFFER */
    if ((pucDestPos - pucDest) > (usDestBuffLen - 1))
    {
        *pusDestLen = 0;
        (VOS_VOID)vos_printf("\n\rWARNING, Om_HdlcEncap, Dst Buf is not Enough #4:BufLen:%d !\n\r", usDestBuffLen);
        return VOS_ERR;
    }

    *pucDestPos++   = OM_HDLC_FRAME_FLAG;

    *pusDestLen     = (VOS_UINT16)(pucDestPos - pucDest);
    return VOS_OK;
}

/*****************************************************************************
     : Om_HdlcInit
   : HDLC, 
             Om_HdlcDecap
   : OM_HDLC_STRU *pstHdlc
   : OM_HDLC_STRU *pstHdlc
     : VOS_VOID
   :
   :

       :
  1.       : 200864
           : zengfei 57034
       : 

*****************************************************************************/
VOS_VOID Om_HdlcInit( OM_HDLC_STRU *pstHdlc )
{
    if (VOS_NULL_PTR == pstHdlc)
    {
        (VOS_VOID)vos_printf("\n\rERROR, Om_HdlcInit, OM_HDLC_STRU Pointer is NULL !\n\r");
        return;
    }

    pstHdlc->ulInfoLen  = 0;
    pstHdlc->ulLength   = 0;
    pstHdlc->ulMode     = OM_HDLC_MODE_HUNT;
}

/*****************************************************************************
     : OM_HdlcFcs
   : FCS. RFC 1662 Appendix C and CCITT X.25 section 2.27.
   : VOS_UINT8 *pucData
             VOS_UINT32 ulDataLen
   : 
     : VOS_UINT16
   :
   :

       :
  1.       : 200863
           : zengfei 57034
       : 

*****************************************************************************/
VOS_UINT16 OM_HdlcFcs( VOS_UINT8 *pucData, VOS_UINT32 ulDataLen )
{
    VOS_UINT16 usFcs = OM_HDLC_INIT_FCS;

    while (ulDataLen--)
    {
        usFcs = (usFcs >> 8) ^ g_ausOmHdlcFcsTab[(usFcs ^ *pucData++) & 0xff];
    }

    return usFcs;
}

/*****************************************************************************
     : Om_HdlcDecap
   : HDLC
   : OM_HDLC_STRU *pstHdlc
             VOS_UINT8 ucChar
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 200863
           : zengfei 57034
       : 

*****************************************************************************/
OM_HDLC_RESULT_ENUM_UINT32 Om_HdlcDecap( OM_HDLC_STRU *pstHdlc, VOS_UINT8 ucChar )
{
    VOS_UINT16  usFcs;

    if (VOS_NULL_PTR == pstHdlc)
    {
        (VOS_VOID)vos_printf("\n\rERROR, Om_HdlcDecap, Pointer Para is NULL !\n\r");
        return HDLC_PARA_ERROR;
    }

    if (VOS_NULL_PTR == pstHdlc->pucDecapBuff)
    {
        (VOS_VOID)vos_printf("\n\rERROR, Om_HdlcDecap, Dst Buff is NULL !\n\r");
        return HDLC_PARA_ERROR;
    }

    /* OM_HDLC_FRAME_FLAG */
    if ((pstHdlc->ulMode & OM_HDLC_MODE_HUNT) && (OM_HDLC_FRAME_FLAG != ucChar))
    {
        pstHdlc->ulLength   = 0;        /* Om_HdlcDecapOm_HdlcInitpstHdlc->ulLength0 */
        return HDLC_NOT_HDLC_FRAME;
    }

    switch (ucChar)
    {
        case OM_HDLC_FRAME_FLAG:
            pstHdlc->ulMode &= ~OM_HDLC_MODE_HUNT;          /*  */

            if (pstHdlc->ulLength > OM_HDLC_FCS_LEN)
            {                           /* (+FCS)2 BYTE */
                usFcs = OM_HdlcFcs(pstHdlc->pucDecapBuff, pstHdlc->ulLength);
                if (OM_HDLC_GOOD_FCS != usFcs)
                {
                    pstHdlc->ulLength       = 0;
                    return HDLC_FCS_ERROR;
                }

                pstHdlc->ulInfoLen      = pstHdlc->ulLength - OM_HDLC_FCS_LEN;
                pstHdlc->ulLength       = 0;
                return HDLC_SUCC;
            }
            else
            {                           /* pstHdlc->ulLength0OM_HDLC_FRAME_FLAG */
                                        /* pstHdlc->ulLength0HDLC(+FCS)3 */
                pstHdlc->ulLength   = 0;
                break;
            }
        case OM_HDLC_ESC:
            if (!(pstHdlc->ulMode & OM_HDLC_MODE_ESC))
            {
                pstHdlc->ulMode |= OM_HDLC_MODE_ESC;        /*  */
            }
            else
            {                           /* : OM_HDLC_ESC */
                pstHdlc->ulMode &= ~OM_HDLC_MODE_ESC;       /*  */
                pstHdlc->ulMode |= OM_HDLC_MODE_HUNT;       /*  */
                pstHdlc->ulLength = 0;
                (VOS_VOID)vos_printf("\n\rERROR, Om_HdlcDecap, Esc Char Error:0x%x !\n\r", ucChar);
                return HDLC_FRAME_DISCARD;
            }
            break;
        default:
            /* BUFFER */
            if (pstHdlc->ulLength >= pstHdlc->ulDecapBuffSize)
            {                           /* : BUFFER */
                pstHdlc->ulMode |= OM_HDLC_MODE_HUNT;        /*  */
                pstHdlc->ulLength = 0;
                (VOS_VOID)vos_printf("\n\rWARNING, Om_HdlcDecap, Dst Buf is full #1:BufLen:%d !\n\r", (VOS_INT32)pstHdlc->ulDecapBuffSize);
                return HDLC_BUFF_FULL;
            }

            if (pstHdlc->ulMode & OM_HDLC_MODE_ESC)
            {
                pstHdlc->ulMode &= ~OM_HDLC_MODE_ESC;          /*  */
                if (((OM_HDLC_FRAME_FLAG^OM_HDLC_ESC_MASK) == ucChar)
                    || ((OM_HDLC_ESC^OM_HDLC_ESC_MASK) == ucChar))
                {
                    ucChar ^= OM_HDLC_ESC_MASK;
                }
                else
                {                           /* : OM_HDLC_ESC */
                    pstHdlc->ulMode |= OM_HDLC_MODE_HUNT;        /*  */
                    pstHdlc->ulLength = 0;
                    (VOS_VOID)vos_printf("\n\rERROR, Om_HdlcDecap, Esc Char Error:0x%x !\n\r", ucChar);
                    return HDLC_FRAME_DISCARD;
                }
            }

            pstHdlc->pucDecapBuff[pstHdlc->ulLength] = ucChar;
            pstHdlc->ulLength++;
            break;
    }


    return HDLC_NOT_HDLC_FRAME;
}



