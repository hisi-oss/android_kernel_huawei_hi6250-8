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


#ifndef __TTF_COMM_H_
#define __TTF_COMM_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/******************************************************************************
  1 
******************************************************************************/
#include "vos.h"
#include "PsLogdef.h"
#include "PsCommonDef.h"
#include "PsLib.h"
#include "PsTypeDef.h"
#include "LPSCommon.h"
#include "product_config.h"
#include "msp_diag_comm.h"

/******************************************************************************
  2 
******************************************************************************/

#define PS_UE_CAP_2507_SUPPT                  (PS_CAP_SUPPORT)
#define PS_UE_CAP_1144_SUPPT                  (PS_CAP_SUPPORT)
#define PS_UE_CAP_V42_SUPPT                   (PS_CAP_SUPPORT)



/**/
#define TTF_BIT_MOVE_24  (24)
#define TTF_BIT_MOVE_16  (16)
#define TTF_BIT_MOVE_8   (8)

/**/
#define TTF_BIT_OPR_8    (0xFF)
#define TTF_BIT_OPR_16   (0xFFFF)
#define TTF_BIT_OPR_24   (0xFFFFFF)
#define TTF_BIT_OPR_32   (0xFFFFFFFF)

/**/
#define TTF_UNSIGN_LONG_MOD         (0x7FFFFFFFUL)

/*4UINT8UINT32, UINT8*/
#define TTF_CONN_UINT32_FROM_UINT8(ulNum, ucNum1, ucNum2, ucNum3, ucNum4)   \
{       \
    (ulNum) = 0;        \
    (ulNum) |= (VOS_UINT32)(((VOS_UINT32)(ucNum1)) << TTF_BIT_MOVE_24);     \
    (ulNum) |= (VOS_UINT32)(((VOS_UINT32)(ucNum2)) << TTF_BIT_MOVE_16);     \
    (ulNum) |= (VOS_UINT32)(((VOS_UINT32)(ucNum3)) << TTF_BIT_MOVE_8);     \
    (ulNum) |= (VOS_UINT32)(ucNum4);     \
}

#define TTF_MOD_GET(x, y)                       ((x) % (y))
#define TTF_MOD_ADD_GU(x, y, z)                 (((x) + (y)) % (z))
#define TTF_MOD_SUB_GU(x, y, z)                 ((((x) + (z)) - (y)) % (z))
#ifdef _lint
#define TTF_MOD_ADD(x, y, z)                    (((x) + (y)) % (z))
#define TTF_MOD_SUB(x, y, z)                    ((((x) + (z)) - (y)) % (z))
#else
#define TTF_MOD_ADD(x, y, z)                    ((((x) + (y)) < (z))? ((x) + (y)):(((x) + (y)) - (z)))
#define TTF_MOD_SUB(x, y, z)                    (((x) < (y))?(((x) + (z)) - (y)):((x) - (y)))
#endif


/* XY */
#define TTF_CEIL(x, y) \
            /*lint -e{961} */ \
            ((0==(x)%(y))?((x)/(y)):((x)/(y)+1))

#define TTF_MIN(x, y)                           (((x)<(y))?(x):(y))
#define TTF_MAX(x, y)                           (((x)>(y))?(x):(y))

/* SN[lower, upper]lower upper */
#define TTF_SN_OUTSIDE_WINDOW(sn, lowerEdge, upperEdge, module) \
            /*lint -e{961,731} */ \
            ((TTF_MOD_SUB(sn, lowerEdge, module) >= TTF_MOD_SUB(sn, upperEdge, module)) && ((sn) != (upperEdge)))

/* SN[lower, upper]lower upper */
#define TTF_SN_WITHIN_WINDOW(sn, lowerEdge, upperEdge, module)  \
            /*lint -e{961,731,685} */ \
            ((TTF_MOD_SUB(sn, lowerEdge, module) < TTF_MOD_SUB(sn, upperEdge, module)) || ((sn) == (upperEdge)))

#define TTF_SN1_BELOW_SN2_WITHIN_WINDOW(sn1, sn2, upperEdge, module)\
            (TTF_MOD_SUB(upperEdge, sn1, module) > TTF_MOD_SUB(upperEdge, sn2, module))

#define TTF_SN_IN_WINDOW(sn, lowerEdge, winSize, module) \
            ( TTF_MOD_SUB((sn), (lowerEdge), (module)) < (winSize) )

/*usSn:
usSns:
usWndSize:
usHeader:usHeaderSn
usHeaderSn:
usSn:*/
#define TTF_GET_WND_POS(usSns, usWndSize, usHeader, usHeaderSn, usSn)   \
    TTF_MOD_GET(((usHeader) + TTF_MOD_SUB((usSn), (usHeaderSn), (usSns))), (usWndSize))

/* change bit to byte */
#define TTF_BIT2BYTE(BitLen)        (((BitLen) + 7) >> 3)
/* change byte to bit */
#define TTF_BYTE2BIT(ByteLen)       (VOS_UINT32)(((VOS_UINT32)(ByteLen)) << 3)

/*=============*/   /*offset*/
#define TTF_OFFSET_OF(s, m) /*lint -e(413)*/((VOS_SIZE_T)(VOS_UINT_PTR)(&(((s *)0)->m)))

#define TTF_GET_OFFSET(offset, s, m) \
{ \
    /*lint --e{545,413,831} */ \
    offset  = TTF_OFFSET_OF(s, m); \
}

/* ucSrcucDestbitstart(07)bitlen(18)IE,
   , ucDest*/
#define TTF_SET_UC_BIT(ucSrc, ucDest, bitstart, bitlen) \
((ucDest) |= (VOS_UINT8)( (VOS_UINT8)((VOS_UINT32)(ucSrc) << (8 - bitlen)) >> ((8 - bitstart) - bitlen) ))

/* ucSrcucDestbitlen(18)IE,
   , ucDest*/
#define TTF_SET_UC_HIGH_BIT(ucSrc, ucDest, bitlen) \
((ucDest) |= (VOS_UINT8)( (VOS_UINT8)((VOS_UINT32)(ucSrc) << (8 - bitlen)) ))

/* usSrcusDestbitstart(015)bitlen(116)IE,
   , usDest*/
#define TTF_SET_US_BIT(usSrc, usDest, bitstart, bitlen) \
((usDest) |= (VOS_UINT16)( (VOS_UINT16)((VOS_UINT32)(usSrc) << (16 - bitlen)) >> ((16 - bitstart) - bitlen) ))

/* usSrcusDestbitlen(116)IE,
   , ucDest*/
#define TTF_SET_US_HIGH_BIT(usSrc, usDest, bitlen) \
((usDest) |= (VOS_UINT16)( (VOS_UINT16)((VOS_UINT32)(usSrc) << (16 - bitlen)) ))

/* USbitstart(015)bitlen(116),
   ,
   : bitstart
   +  -  +  -  +  -  + - + - + - + - + -
   15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
   +  -  +  -  +  -  + - + - + - + - + -
*/
#define TTF_GET_US_BIT(us, bitstart, bitlen) \
((VOS_UINT16)((VOS_UINT32)(us) << ((16 - (bitstart)) - (bitlen))) >> (16 - (bitlen)))

#define TTF_GET_US_HIGH_BIT(us, bitlen) \
((VOS_UINT16)((us)  >> (16 - (bitlen))))

/* UCbitstart(07)bitlen(18),
   , */
#define TTF_GET_UC_BIT(uc, bitstart, bitlen) \
((VOS_UINT8)((VOS_UINT32)(uc) << ((8 - (bitstart)) - (bitlen))) >> (8 - (bitlen)))

/* ucbitlen(18)IE,
   , */
#define TTF_GET_UC_HIGH_BIT(uc, bitlen) \
((VOS_UINT8)(uc) >> (8 - (bitlen)))

#define TTF_GET_HIGH_16BIT_FROM_32BIT(ul32BitValue) ((VOS_UINT16)((ul32BitValue) >> 16))
#define TTF_GET_HIGH_8BIT_FROM_32BIT(ul32BitValue)  ((VOS_UINT8)((ul32BitValue) >> 24))
#define TTF_GET_LOW_16BIT_FROM_32BIT(ul32BitValue)  ((VOS_UINT16)((ul32BitValue) & 0xFFFF))
#define TTF_GET_HIGH_8BIT_FROM_16BIT(us16BitValue)  ((VOS_UINT8)((us16BitValue) >> 8))
#define TTF_GET_LOW_8BIT_FROM_16BIT(us16BitValue)   ((VOS_UINT8)((us16BitValue) & 0xFF))

#define TTF_MAKE_32BIT(usHighVal, usLowVal)         ( (((VOS_UINT32)(usHighVal))<<16) | ((VOS_UINT32)((usLowVal) & 0xFFFF)) )
#define TTF_MAKE_16BIT(ucHighVal, ucLowVal)         ( (VOS_UINT16)(((VOS_UINT8)(ucLowVal)) | (((VOS_UINT16)((VOS_UINT8)(ucHighVal)))<<8)) )

#define TTF_SET_HIGH_16BIT_TO_32BIT(ul32BitVal, usHigh16BitVal) \
    ( (((VOS_UINT32)ul32BitVal) & 0xFFFF) | (((VOS_UINT32)usHigh16BitVal) << 16) )

/* 4  */
#define TTF_GET_4BYTE_ALIGN_VALUE(ulValue)       ( ((ulValue) + 0x03UL) & (~0x03UL) )

/* 8  */
#define TTF_GET_8BYTE_ALIGN_VALUE(ulValue)       ( ((ulValue) + 0x07UL) & (~0x07UL) )

/* 32  */
#define TTF_GET_32BYTE_ALIGN_VALUE(ulValue)      ( ((ulValue) + 0x1FUL) & (~0x1FUL) )

/* 1bitpos:[0..31] */
#define TTF_SET_A_BIT(value, bitpos)    ((value) |= (1UL << (bitpos)))

/* 0bitpos:[0..31] */
#define TTF_CLEAR_A_BIT(value, bitpos)  ((value) &= (~(1UL << (bitpos))))

/* 10bitpos:[0..31] */
#define TTF_GET_A_BIT(value, bitpos)    (((value) & (1UL << (bitpos))) >> (bitpos))

/*  */
#define TTF_GET_ARRAYSIZE(array)        (sizeof(array)/sizeof(array[0]))


/*  */
#define TTF_GET_MSGTYPE(pMsg) \
    (*(VOS_UINT16*)((VOS_UINT8*)(pMsg) + VOS_MSG_HEAD_LENGTH))

#if (OSA_CPU_CCPU == VOS_OSA_CPU)
#ifndef __PS_WIN32_RECUR__
#define TTF_TRACE_MSG(pMsg)     DIAG_TraceReport(pMsg)
#else
#define TTF_TRACE_MSG(pMsg)     TTF_TraceMsgHook(pMsg)
#endif
#else
#define TTF_TRACE_MSG(pMsg)
#endif
/* STTrace,UT */
#define RECUR_ST_TRACE      (1)
#define RECUR_OTHER_TRACE   (0)

/*,
  NASGRMLLC
 */
#define GRM_MNTN_TIMER_PC_RECUR_LEN     60533
#define LLC_MNTN_TIMER_PC_RECUR_LEN     60503

/* 16bit 32 bit  */
#define TTF_WRITE_32REG(pAddr, value)       ( *((volatile VOS_UINT32 *)(pAddr)) = (value) )
#define TTF_WRITE_16REG(pAddr, value)       ( *((volatile VOS_UINT16 *)(pAddr)) = (value) )
#define TTF_READ_32REG(pAddr)               ( *((volatile VOS_UINT32 *)(pAddr)) )
#define TTF_READ_16REG(pAddr)               ( *((volatile VOS_UINT16 *)(pAddr)) )

/* 32 bit  */
#define TTF_WRITE_32REG_MASK(pAddr,ulMask)  ( *(volatile VOS_UINT32 *)(pAddr) |= (ulMask) )

/* 32 bit  */
#define TTF_CLEAR_32REG_MASK(pAddr,ulMask)  ( *(volatile VOS_UINT32 *)(pAddr) &= ~(ulMask) )

/*  */
#define TTF_GET_MSG_NAME(pRcvMsg)           (*((VOS_UINT32 *)(VOS_VOID *)((VOS_UINT8 *)(pRcvMsg) + VOS_MSG_HEAD_LENGTH)))
#define TTF_GET_MSG_SENDER_PID(pRcvMsg)     (*((VOS_UINT32 *)(VOS_VOID *)(pRcvMsg) + 1))
#define TTF_GET_MSG_RECV_PID(pRcvMsg)       (*((VOS_UINT32 *)(VOS_VOID *)(pRcvMsg) + 3))
#define TTF_GET_MSG_MSG_LEN(pRcvMsg)        (*((VOS_UINT32 *)(VOS_VOID *)(pRcvMsg) + 4))
#define TTF_GET_MSG_OPID(pRcvMsg)      (*(VOS_UINT16 *)(VOS_VOID*)((VOS_UINT8 *)pRcvMsg + 24))


/**/
#define TTF_SET_MSG_SENDER_PID(pRcvMsg, ulPid)          \
                                            (*((VOS_UINT32 *)(VOS_VOID *)(pRcvMsg) + 1) = (ulPid))
#define TTF_SET_MSG_RECV_PID(pRcvMsg, ulPid)          \
                                            (*((VOS_UINT32 *)(VOS_VOID *)(pRcvMsg) + 3) = (ulPid))
#define TTF_SET_MSG_LEN(pRcvMsg, ulLen)            \
                                            (*((VOS_UINT32 *)(VOS_VOID *)(pRcvMsg) + 4) = (ulLen))


#define  ETH_MAC_HEADER_LEN             (14)      /**/
/*Ethenet*/
#define ETH_MAC_ADDR_LEN                6         /*MAC*/
#define ETH_MIN_FRAME_SIZE              60        /**/
#define ETH_CRC_LEN                     4
#define ETH_MAX_FRAME_SIZE              (1514)    /**/

/*ARP*/
#define ETH_ARP_REQ_TYPE                0x0100      /*ARP Request*/
#define ETH_ARP_RSP_TYPE                0x0200      /*ARP Reply*/
#define ETH_ARP_FIXED_MSG_LEN           8           /*ARP*/

/*IP*/
/*#define IPPACKET_MIN_LEN                (1500)
 */
#define IPV4_FIX_HDR_LEN                (20)       /* IPV4*/
#define IPV4_HDR_TTL                    (128)      /* IPV4 TTL*/

#define IP_IPV4_VERSION                 (4)        /* IP V4      */
#define IP_PROTOCOL_UDP                 (0x11)     /* IPUDP  */
#define IP_PROTOCOL_TCP                 (0x06)     /* IPTCP  */
#define IP_PROTOCOL_ICMP                (0x01)     /* IPICMP */

/*DHCP67,*/
#define UDP_DHCP_SERVICE_PORT           (0x4300)   /* DHCP */
#define UDP_DHCP_CLIENT_PORT            (0x4400)   /* DHCP Client*/

#define TTF_L1_CACHE_SHIFT              (5)
#define TTF_L1_CACHE_BYTES              (1UL << TTF_L1_CACHE_SHIFT)


#define TTF_SMP_CACHE_BYTES             (TTF_L1_CACHE_BYTES)        /* Linuxcheck */

#define TTF_DATA_ALIGN(X)               (((X) + (TTF_SMP_CACHE_BYTES - 1)) & \
                                        ~(TTF_SMP_CACHE_BYTES - 1))

/* TCP/IP */
#define IP_VER_MASK                         (0xF0)    /* IP */
#define IP_HEADER_LEN_MASK                  (0x0F)    /* IP */
#define IPV4_VER_VAL                        (0x40)    /* IP v4 */
#define IPV6_VER_VAL                        (0x60)    /* IP v6 */

#define PROTOCOL_POS                        (9)       /* IPProtocal  */
#define NEXT_HEADER_POS                     (6)       /* IPNext header  */

#define IPV4_HEAD_NORMAL_LEN                (20)      /* IPV4 */
#define IPV6_HEAD_NORMAL_LEN                (40)      /* IPV6 */

#define IP_VER_VAL                          (0x40)    /* IP v4 */
#define TCP_IP_OFFSET_LEN_POS               (32)      /* TCPIP */

#define IPV4_INDENTIFY_OFFSET_POS           (4)        /* IPV4 Identification offsetIPV4 */

#define IPV4_SRC_IP_ADDR_OFFSET_POS         (12)       /* IPV4 Src Ip Adrr offsetIPV4 */
#define IPV4_DST_IP_ADDR_OFFSET_POS         (16)       /* IPV4 Dst Ip Adrr offsetIPV4 */

#define IP_VER_VAL_V6                       (0x60)    /* IP v6 */

#define IPV4_HEAD_FRAGMENT_OFFSET_POS       (6)       /* IPV4 Fragment offsetIPV4 */
#define IPV6_HEAD_FRAGMENT_OFFSET_POS       (20)      /* IPV6 Fragment offsetIPV4 */
#define IPV4_HEAD_FRAGMENT_OFFSET_MASK      (0x3FFF)  /* IPV4 Fragment offset */
#define ICMP_TYPE_CODE_OFFSET_POS           (1)       /* ICMP CODE */
#define ICMP_HEADER_LEN                     (8)       /* ICMP  */
#define ICMP_TYPE_REPLY                     (0)       /* ICMP */
#define ICMP_TYPE_REQUEST                   (8)       /* ICMP */

#define TCP_DST_PORT_POS                    (2)       /* TCPTCP */
#define TCP_SEQ_NUM_POS                     (4)       /* TCPSeq numberTCP */
#define TCP_ACK_NUM_POS                     (8)       /* TCPAck numberTCP */
#define TCP_LEN_POS                         (12)      /* TCPTCP */
#define TCP_FLAG_POS                        (13)      /* TCPTCP */
#define TCP_SYN_MASK                        (0x02)    /* TCP */
#define TCP_ACK_MASK                        (0x10)    /* TCP */
#define TCP_LEN_MASK                        (0xF0)    /* TCP */
#define FTP_DEF_SERVER_SIGNALLING_PORT      (21)      /* FTP */

#define PROTOCOL_POS_V6                     (6)       /* IP */

#define TCP_LEN_POS_V6                      (52)      /* TCPIP */

#define ICMPV6_TYPE_REQUEST                 (128)     /* ICMP */
#define ICMPV6_TYPE_REPLY                   (129)     /* ICMP */

#define UDP_HEAD_LEN                        (8)       /* UDP */
#define UDP_DST_PORT_POS                    (2)       /* UDPUDP */
#define DNS_QR_POS                          (2)       /* DNS QRQR */
#define DNS_QR_MASK                         (0x80)    /* DNS QR */
#define DNS_DEF_SERVER_PORT                 (53)      /* DNS */

#define TCP_ACK_MIN_LEN                     (40)       /* TCP ACK, , typically IP header 20 bytes and TCP header 20 bytes */
#define TCP_ACK_MIN_LEN_V6                  (60)       /* TCP ACK, , typically IP header 40 bytes and TCP header 20 bytes */
#define TCP_ACK_MAX_LEN                     (80)       /* TCP ACK, , typically IP header 20 bytes, and TCP header max size 60 bytes */
#define TCP_ACK_MAX_LEN_V6                  (100)      /* TCP ACK, , typically IP header 40 bytes, and TCP header max size 60 bytes */
#define ICMP_PROTOCOL_VAL                   (0x01)     /* ICMP */
#define ICMP_PROTOCOL_VAL_V6                (0x3A)     /* ICMP */

/* IP */
#define IP_IPV4_PROTO_VERSION        4      /* IPV4 */
#define IP_IPV4_HEAD_LEN             20     /* IPV4 */
#define IP_IPV4_PROTO_TCP            6      /* IPV4TCP */
#define IP_IPV4_PROTO_UDP            17     /* IPV4UDP */
#define IP_IPV4_PROTO_ICMP           1      /* IPV4ICMP */
#define IP_IPV4_ICMP_ECHO_REQUEST    8      /* IPV4ICMPTYPE ECHO REQ */
#define IP_IPV4_ICMP_ECHO_REPLY      0      /* IPV4ICMPTYPE ECHO REPLY */
#define IP_IPV4_DATA_LEN_POS         2      /* IPV4IP */
#define IP_IPV4_IDENTIFY_POS         4      /* IPV4IPIDENTIFY */
#define IP_IPV4_PROTO_POS            9      /* IPV4IP */
#define IP_IPV4_ICMP_IDENTIFY_POS    4      /* IPICMPIDENTIFY */
#define IP_IPV4_ICMP_SN_POS          6      /* IPICMPSN */
#define IP_IPV4_TCP_SEQ_POS          4      /* IPTCPSEQ */
#define IP_IPV4_TCP_ACK_POS          8      /* IPTCPACK */
#define IP_IPV4_DST_PORT_POS         2      /* IPIPV4 */
#define IP_PROTO_VERSION_POS         4      /* IP */

#define IP_IPV6_PROTO_VERSION        6      /* IPV6 */
#define IP_IPV6_HEAD_LEN             40     /* IPV6 */
#define IP_IPV6_PROTO_TCP            6      /* IPV6TCP */
#define IP_IPV6_PROTO_UDP            17     /* IPV6UDP */
#define IP_IPV6_PROTO_ICMP           58     /* IPV6ICMP */
#define IP_IPV6_ICMP_ECHO_REQUEST    128    /* IPV6ICMPTYPE ECHO REQ */
#define IP_IPV6_ICMP_ECHO_REPLY      129    /* IPV6ICMPTYPE ECHO REPLY */
#define IP_IPV6_DATA_LEN_POS         4      /* IPV6IP */
#define IP_IPV6_PROTO_POS            6      /* IPV6IP */
#define IP_IPV6_ICMP_IDENTIFY_POS    4      /* IPICMPIDENTIFY */
#define IP_IPV6_TCP_SEQ_POS          4      /* IPTCPSEQ */
#define IP_IPV6_TCP_ACK_POS          8      /* IPTCPACK */
#define IP_IPV6_DST_PORT_POS         2      /* IPIPV6 */

#define IP_IPV4_VER_AND_HEAD         0x45   /* IPv4 */
#define IP_IPV6_VER_AND_HEAD         0x60   /* IPv6 */
#define MAC_HEAD_LEN                 14     /* MAC */

/* IP */
#define IP_GET_VAL_NTOH_U8(data,pos)    ((data)[pos])
#define IP_GET_VAL_NTOH_U16(data,pos)   (((data)[pos]<<8)|((data)[pos+1]))
#define IP_GET_VAL_NTOH_U32(data,pos)   (((VOS_UINT32)((data)[pos])<<24)|((VOS_UINT32)((data)[pos+1])<<16)|((VOS_UINT32)((data)[pos+2])<<8)|((data)[pos+3]))

/* v9SRAM */
#define     GTTF_SRAM_400K
#define     WTTF_SRAM_400K

/* core mask */
#define TTF_GET_MAX_CORE_MASK     ((1UL << VOS_GetNumberOfCores()) - 1)

/* TTF Log */
#define TTF_LOG(ModulePID, ModeType, Level, String) \
        ((VOS_VOID)DIAG_LogReport(DIAG_GEN_LOG_MODULE(VOS_GetModemIDFromPid(ModulePID), ModeType, Level), (ModulePID), __FILE__, __LINE__, "%s \r\n", String))

#define TTF_LOG1(ModulePID, ModeType, Level, String, Para1) \
        ((VOS_VOID)DIAG_LogReport(DIAG_GEN_LOG_MODULE(VOS_GetModemIDFromPid(ModulePID), ModeType, Level), (ModulePID), __FILE__, __LINE__, "%s, %d \r\n", String, Para1))

#define TTF_LOG2(ModulePID, ModeType, Level, String, Para1, Para2) \
        ((VOS_VOID)DIAG_LogReport(DIAG_GEN_LOG_MODULE(VOS_GetModemIDFromPid(ModulePID), ModeType, Level), (ModulePID), __FILE__, __LINE__, "%s, %d, %d \r\n", String, Para1, Para2))

#define TTF_LOG3(ModulePID, ModeType, Level, String,Para1, Para2, Para3) \
        ((VOS_VOID)DIAG_LogReport(DIAG_GEN_LOG_MODULE(VOS_GetModemIDFromPid(ModulePID), ModeType, Level), (ModulePID), __FILE__, __LINE__, "%s, %d, %d, %d \r\n", String, Para1, Para2, Para3))

#define TTF_LOG4(ModulePID, ModeType, Level, String, Para1, Para2, Para3, Para4) \
        ((VOS_VOID)DIAG_LogReport(DIAG_GEN_LOG_MODULE(VOS_GetModemIDFromPid(ModulePID), ModeType, Level), (ModulePID), __FILE__, __LINE__, "%s, %d, %d, %d, %d \r\n", String, Para1, Para2, Para3, Para4))

/******************************************************************************
  3 
******************************************************************************/
/*****************************************************************************
     :
   :
 ASN.1 :
   :
*****************************************************************************/
enum APPITF_RTN_CODE_ENUM
{
    APPITF_SUCC                             = 0,
    APPITF_FAIL                             = 1,

    APPITF_PTR_NULL                         = 2,    /**/
    APPITF_PARA_ERR                         = 3,    /**/
    APPITF_STATE_ERR                        = 4,    /**/
    APPITF_MODE_ERR                         = 5,    /**/
    APPITF_SCOPE_ERR                        = 6,    /**/
    APPITF_MEM_ALLOC_FAIL                   = 7,    /**/
    APPITF_MSG_ALLOC_FAIL                   = 8,    /**/
    APPITF_MSG_SEND_FAIL                    = 9,    /**/
    APPITF_TIMER_ERR                        = 10,   /**/
    APPITF_TIMER_OUT                        = 11,   /**/
    APPITF_QUE_FULL                         = 12,   /**/
    APPITF_QUE_EMPTY                        = 13,   /**/

    APPITF_SNDTOETH_FAIL                    = 14,
    APPITF_CPYMEM_ERR                       = 15,
    APPITF_TOOBIGIPPACKET                   = 16,

    APP_RTN_CODE_BUTT
};
typedef VOS_UINT32   APP_RTN_CODE_ENUM_UINT32;

/*****************************************************************************
     : TTF_SOFT_RESET_CAUSE_VALUE_ENUM
   :
 ASN.1 :
   : TTF  
*****************************************************************************/
enum TTF_SOFT_RESET_CAUSE_VALUE_ENUM
{
    TTF_SOFT_RESET_CAUSE_NORMAL                      = 0x30000000,  /* 0x3******* */
    TTF_SOFT_RESET_CAUSE_BUTT
};
typedef VOS_INT32 TTF_SOFT_RESET_CAUSE_VALUE_ENUM_INT32;


/******************************************************************************
  4 
******************************************************************************/


/******************************************************************************
  5 
******************************************************************************/


/******************************************************************************
  6 
******************************************************************************/


/******************************************************************************
  7 STRUCT
******************************************************************************/
#pragma pack(4)

typedef struct
{
    VOS_MSG_HEADER                      /*  */

    VOS_UINT16 usMsgType;               /*  */
    VOS_UINT16 usTransId;               /* , */
#define TTF_MSG_HEAD    4               /* (usMsgTypeusTransId) */

    VOS_UINT8  astMsg[4];               /*  */
}TTF_COMM_MSG;

typedef struct
{
    VOS_MSG_HEADER                      /*  */

    VOS_UINT16 usMsgType;               /*  */
    VOS_UINT8  astMsg[2];               /*  */
}WTF_COMM_MSG;


/* 
   pMsg:
   pSelfDefinePara: */
typedef VOS_UINT32 (*PTTFMSGPROC)(MsgBlock *pMsg, void *pSelfDefinePara);

typedef struct
{
    VOS_UINT16 usMsgType;               /* ID */
    VOS_UINT8  ucState;                 /*  */
    VOS_UINT8  ucRsv;                   /*  */
    PTTFMSGPROC pProcFun;               /*  */
}TTF_COMM_STATUS;

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif
/******************************************************************************
  8 UNION
******************************************************************************/


/******************************************************************************
  9 OTHERS
******************************************************************************/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* TTFComm.h */


