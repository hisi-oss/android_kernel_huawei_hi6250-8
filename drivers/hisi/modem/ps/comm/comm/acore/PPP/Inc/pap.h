/*-
 * Copyright (c) 1996 - 2001 Brian Somers <brian@Awfulhak.org>
 *          based on work by Toshiharu OHNO <tony-o@iij.ad.jp>
 *                           Internet Initiative Japan, Inc (IIJ)
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * $FreeBSD: releng/11.1/usr.sbin/ppp/pap.h 78189 2001-06-13 21:52:19Z brian $
 */
#ifndef __PPP_PAP_H__
#define __PPP_PAP_H__

#include "PPP/Inc/auth.h"


#pragma pack(4)
#define    PAP_REQUEST    1
#define    PAP_ACK        2
#define    PAP_NAK        3


struct authinfo;

struct pap {
  struct authinfo auth;    /* common structure of authentication */
  struct {
      VOS_CHAR password[PASSWORDLEN+1];    /* just use it to store password for print */
      VOS_UINT8 aucReserved[1];            /* add for pclint */

      /*GGSNconfig req
      pap reqAT*/
      VOS_UINT16 LenOfRequest;
      VOS_UINT8  BufRequest[PASSWORDLEN + AUTHLEN];
  } RecordData;    /* encapsulated to structure RecordData by liukai */
};

extern void pap_Init(struct pap * /*, struct physical **/);
extern PPP_ZC_STRU *pap_Input(/*struct bundle *, */struct link *, PPP_ZC_STRU *);

#pragma pack()

#endif /* end of pap.h */

