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



#ifndef __MSP_ERRNO_H__
#define __MSP_ERRNO_H__

#define  ERR_MSP_SUCCESS                (0)
#define  ERR_MSP_WAIT_ASYNC             (1)
#define  ERR_MSP_INVALID_ID             (2)
#define  ERR_MSP_NO_INITILIZATION       (3)
#define  ERR_MSP_NOT_FOUND              (4)
#define  ERR_MSP_FULL                   (7)
#define  ERR_MSP_INSUFFICIENT_BUFFER    (8)
#define  ERR_MSP_CONSUMED               (9)
#define  ERR_MSP_CONTINUE               (10)
#define  ERR_MSP_TOO_SMALL_BUFFER       (11)
#define  ERR_MSP_NOT_FREEE_SPACE        (12)
#define  ERR_MSP_NO_MORE_DATA           (13)
#define  ERR_MSP_MALLOC_FAILUE          (15)
#define  ERR_MSP_NOT_ENOUGH_MEMORY      (16)
#define  ERR_MSP_INVALID_HEAP_ADDR      (17)
#define  ERR_MSP_SHUTDOWN               (18) /* */
#define  ERR_MSP_NOT_CONNECT            (19) /* UE*/
#define  ERR_MSP_BUSY                   (20) /* */


#define  ERR_MSP_UNAVAILABLE            (50)
#define  ERR_MSP_TIMEOUT                (51)
#define  ERR_MSP_INIT_FAILURE           (52)
#define  ERR_MSP_IO_REGISTER_FAILURE    (53)
#define  ERR_MSP_NO_REGISTER            (54)

#define  ERR_MSP_FLASH_ERASE_ERROR      (100)
#define  ERR_MSP_FLASH_WRITE_ERROR      (101)
#define  ERR_MSP_FLASH_ALIGN_ERROR      (102)             /* sector aligned addresses*/
#define  ERR_MSP_FLASH_PROTECT_ERROR    (103)
#define  ERR_MSP_FLASH_BIN_LOAD_NEED_FIRST_BLOCK    (104) /* while bin file load,req need first block*/
#define  ERR_MSP_DIAG_CMD_SIZE_INVALID              (106)


#define  ERR_MSP_CFG_RAM_SUCCESS         (201)
#define  ERR_MSP_CFG_PART_SUCCESS        (202)
#define  ERR_MSP_CFG_LOG_NOT_ALLOW       (203)
#define  ERR_MSP_DIAG_CYC_CMD_NOT_START  (204)
#define  ERR_MSP_DIAG_MSG_CFG_NOT_SET    (205)
#define  ERR_MSP_QUEUE_FULL              (300)
#define  ERR_MSP_QUEUE_NOT_EXIST         (301)
#define  ERR_MSP_INVALID_TASK_ID         (302)
#define  ERR_MSP_INVALID_TASK_QUEUE      (303)

#define  ERR_MSP_VCOM_WRITE_ERROR        (401)

/* AT*/
/* MSP*/
#define  ERR_MSP_NOT_EXIST               (500) /* ""   Undone*/
#define  ERR_MSP_UNKNOWN                 (501) /* "" unknown error*/
#define  ERR_MSP_INVALID_PARAMETER       (502) /* "" "invalid parameters"*/
#define  ERR_MSP_NV_NOT_SUPPORT_ID       (520) /* "NV""NVIM Not Exist"*/
#define  ERR_MSP_NV_ERROR_READ           (521) /* "NV" "Read NVIM Failure"*/
#define  ERR_MSP_NV_NOT_SUPPORT_LENTH    (522) /* "NV""Write Error for Length Overflow"*/
#define  ERR_MSP_NV_BAD_BLOCK            (523) /* "NVFlash" "Write Error for Flash Bad Block"*/
#define  ERR_MSP_NV_ERROR_WRITE          (524) /* "NV" "Write Error for Unknown Reason"*/
#define  ERR_MSP_VCTCXO_OVER_HIGH        (525) /* "VCTCXO" "Higher Voltage"	*/
#define  ERR_MSP_UE_MODE_ERR             (526) /* "()"	"UE Mode Error"	*/
#define  ERR_MSP_NOT_SET_CHAN            (527) /* """Not Set Appointed Channel"	*/
#define  ERR_MSP_OPEN_RFTX_ERROR         (528) /* """Open TX Transmitter Failure"	*/
#define  ERR_MSP_OPEN_RFRX_ERROR         (529) /* """Open RX Transmitter Failure"	*/
#define  ERR_MSP_OPEN_CHAN_ERROR         (530) /* """Open Channel Failure"	*/
#define  ERR_MSP_CLOSE_CHAN_ERROR        (531) /* """Close Channel Failure"	*/
#define  ERR_MSP_NOT_SUPPORT             (532) /* "2DD8001T2R"	"Not Support"*/
#define  ERR_MSP_INVALID_OP              (533) /* "NV""Invalid Operation"	*/
#define  ERR_MSP_ENTER_BAND_ERROR        (534) /* "" "Band No Match"	*/
#define  ERR_MSP_SET_CHAN_INFOR_ERROR    (535) /* "" "Set Channel Information Failure"	*/
#define  ERR_MSP_FRE_CHANI_NOTMATCH      (536) /* """Band And Channel Not Combinated"	*/
#define  ERR_MSP_SET_TX_POWER_FAILUE     (537) /* "TX""Set TX Transmitter Power Error"	*/
#define  ERR_MSP_SET_PA_LEVEL_FAILUE     (538) /* "PA""Set PA Level Failure"	*/
#define  ERR_MSP_NOT_SET_CURRENT_CHAN    (539) /* ""	"Not Set Current Channel"*/
#define  ERR_MSP_NOT_ABLETO_RD_APC       (540) /* "APC"	"APC Value Can't Be Read"*/
#define  ERR_MSP_SET_APC_ERROR           (541) /* "APC"	"Write APC Failure"*/
#define  ERR_MSP_RD_APC_ERROR            (542) /* "APC"	"Read APC Failure"*/
#define  ERR_MSP_SET_LINA_ERROR          (543) /* "LNA"	"Set AAGC Failure"*/
#define  ERR_MSP_NOT_OPEN_RXRX           (544) /* ""	"RX Transmitter Not Open"*/
#define  ERR_MSP_NOT_OPEN_RXTX           (545) /* ""	"TX Transmitter Not Open"*/
#define  ERR_MSP_NO_SIGNAL               (546) /* "" "No Signal"	*/
#define  ERR_MSP_PHYNUM_LENGTH_ERROR     (547) /* ""	"PHY Number Length Error"*/
#define  ERR_MSP_PHYNUM_INVALID          (548) /* "" "Invalid PHY Number"	*/
#define  ERR_MSP_PHYNUM_TYPE_ERROR       (549) /* """Invalid PHY Type"*/
#define  ERR_MSP_PLATINFOR_NOTABLE_TORD  (550) /* """Platform Information Can't Be Read"	*/
#define  ERR_MSP_WRT_NOT_UNLOCK          (551) /* ", "	"Not unlock, write error"*/
#define  ERR_MSP_CALLNUM_OVER20          (552) /* "20"	"Card Number Morethan 20"*/
#define  ERR_MSP_MNC_ENTER_OVERFLOW      (553) /* "<mnc-digital-num>" "<mnc-digital-num> Enter Error"	*/
#define  ERR_MSP_RD_VER_FAILUE           (554) /* """Read VERSION Failure"	*//* [false alarm]:alarm */
#define  ERR_MSP_OPERTION_ERROR          (555) /* """Operation Failure"*//* [false alarm]:alarm */
#define  ERR_MSP_PWD_ERR                 (556) /* : """Password Error"*//* [false alarm]:alarm */
#define  ERR_MSP_TIME_OUT                (557) /* : "" "Overtime"*//* [false alarm]:alarm */
#define  ERR_MSP_NO_MORE_MEMORY	         (558) /*  "No Memory"*/
#define  ERR_MSP_SIMM_LOCK               (559) /* SIMLOCK"Sim Lock Active"*/
#define  ERR_MSP_CLOSE_RFTX_ERROR        (560) /* """Close TX Transmitter Failure"	*/
#define  ERR_MSP_CLOSE_RFRX_ERROR        (561) /* """Close RX Transmitter Failure"*/
#define  ERR_MSP_NV_DATA_INVALID         (562) /* "NV""NV DATA INVALID"*/
#define  ERR_MSP_AT_CHANNEL_CLOSE        (563) /* DIAG/MUXAT*/
#define  ERR_MSP_AT_CHANNEL_BUSY         (564) /* DIAG/MUXATBUSY*/
#define  ERR_MSP_OS_MSG_BODY_NULL        (565) /* NULL(NULL)*/
#define  ERR_MSP_AT_ACK_URC_INVALID      (566) /* AT ACK or URC invalid, such as size is zero*/
#define  ERR_MSP_PS_START_FAILURE        (567) /* START PS FAILURE*/
#define  ERR_MSP_PS_STOP_FAILURE         (568) /* STOP PS FAILURE*/
#define  ERR_MSP_PS_SET_APN_FAILURE      (569) /* SET APN FAILURE*/
#define  ERR_MSP_PS_SET_AUTH_FAILURE     (570) /* SET AUTH FAILURE*/
#define  ERR_MSP_PS_SET_BEARER_TYPE_FAILURE      (571) /* SET BEARER TYPE*/


#define  ERR_MSP_BNADSW_ERROR            (572) /* : "BAND"*/
#define	 ERR_MSP_TXWAVE_ERROR	         (573) /* : ""*/
#define  ERR_MSP_AT_FW_TABLEID_EXIST     (574) /* client id */
#define  ERR_MSP_START_TIMER_FAIL           (575)

/* add simm error number (/67193/2009-08-14)*/
/* 600 ~ 699 should be used by simm*/
#define  ERR_MSP_SIMM_NOT_INIT             (601)          /*SIMM*/
#define  ERR_MSP_SIMM_WRONG_PARA           (602)          /**/
#define  ERR_MSP_SIMM_NOAPP                (603)          /**/
#define  ERR_MSP_SIMM_NO_MEM               (604)          /**/
#define  ERR_MSP_SIMM_ALLOCMEM_FAILED      (605)          /**/
#define  ERR_MSP_SIMM_SENDMSG_FAILED       (606)          /**/
#define  ERR_MSP_SIMM_TIMEOUT              (607)          /*,*/
#define  ERR_MSP_SIMM_NO_CARD              (608)          /**/
#define  ERR_MSP_SIMM_SEM                  (609)          /**/

#define  ERR_MSP_SIMM_QUEUE_FULL           (621)          /**/
#define  ERR_MSP_SIMM_QUEUE_EMPTY          (622)          /**/
#define  ERR_MSP_SIMM_CMD_EXCEPTION        (623)          /**/
#define  ERR_MSP_SIMM_CMD_TIMEOUT          (624)          /**/

#define  ERR_MSP_SIMM_DF_FCP_FAILED        (630)          /*DF*/
#define  ERR_MSP_SIMM_PIDO_FAILED          (631)          /*PIDO*/
#define  ERR_MSP_SIMM_FCP_FAILED           (632)          /*EF*/
#define  ERR_MSP_SIMM_EFDIR_FAILED         (632)          /*EF*/

#define  ERR_MSP_SIMM_NEED_PIN             (640)          /*PIN*/
#define  ERR_MSP_SIMM_NEED_PIN2            (641)          /*PIN2*/
#define  ERR_MSP_SIMM_NEED_PUK             (642)          /*PUK*/
#define  ERR_MSP_SIMM_NEED_PUK2            (643)          /*PUK2*/

#define  ERR_MSP_SIMM_AUTH_MAC_FAILURE     (645)          /*MAC*/
#define  ERR_MSP_SIMM_AUTH_SYNC_FAILURE    (646)          /*SYNC*/
#define  ERR_MSP_SIMM_AUTH_OTHER_FAILURE   (647)          /**/
#define  ERR_MSP_SIMM_OTHER_FAILURE        (648)          /**/


#define  ERR_MSP_QUEUE_NOT_OPEN          (1000)
#define  ERR_MSP_QUEUE_UNAVAILABLE       (1001)
#define  ERR_MSP_QUEUE_SHUTDOWN          (1002)

#define  ERR_MSP_NV_ITEM_IS_EMPTY        (1100)
#define  ERR_MSP_NV_FLASH_FULL           (1103)

/* BSP*/
#define  ERR_MSP_NV_GOOD_BLOCK           (1105)
#define  ERR_MSP_NV_ERROR_INIT           (1106)
#define  ERR_MSP_NV_ERROR_ARGS           (1107)
#define  ERR_MSP_NV_ERROR_MALLOC         (1108)
#define  ERR_MSP_NV_ERROR_ERASE          (1111)

/* */
#define  ERR_MSP_SUM_ONLY_NVCOPY_OK      (1200)
#define  ERR_MSP_SUM_BACK_OK             (1201) /*  */
#define  ERR_MSP_SUM_BACK_FAIL           (1202) /*  */
#define  ERR_MSP_SUM_BACK_NO_VERSION     (1203) /*  */
#define  ERR_MSP_SUM_UPDATE_RESET_FAILUE (1204)

#define  ERR_MSP_NVIM_BACKUP_FILE_FAIL    (2001)
#define  ERR_MSP_NVIM_BACKUP_DATA_FAIL    (2002)
#define  ERR_MSP_NVIM_WRITE_FILE_FAIL     (2003)
#define  ERR_MSP_NVIM_UPDATA_DATA_FAIL    (2004)
#define  ERR_MSP_NVIM_UPDATA_FILE_FAIL    (2005)
#define  ERR_MSP_NVIM_SECTION_NOT_SUPPORT_UPDATA    2006
#define  ERR_MSP_NVIM_NOT_SUPPORT_WRITE    2007
#define  ERR_MSP_NVIM_NEED_BACK_ERR             2008

#define LNVM_OPEN_FILE_ERROR      (2010)
#define	LNVM_READ_FILE_ERROR      (2011)
#define	LNVM_FTELL_FILE_ERROR     (2012)
#define	LNVM_WRITE_FILE_ERROR     (2013)
#define	LNVM_SEEK_FILE_ERROR      (2014)
#define	LNVM_REMOVE_FILE_ERROR    (2015)
#define	LNVM_CLOSE_FILE_ERROR     (2016)

#define MSP_SD_OPEN_FILE_ERROR      (2200)
#define	MSP_SD_WRITE_FILE_ERROR     (2201)
#define	MSP_SD_SEEK_FILE_ERROR      (2202)
#define	MSP_SD_GET_STATE_ERROR      (2203)
#define MSP_SD_CREAT_DIR_ERROR      (2204)


/*CDM ERR NO. START*/

#define ERR_MSP_CDM_BEGIN               (0x3000)

#define ERR_MSP_CDM_ACPU_CODER_SRC_FAIL (ERR_MSP_CDM_BEGIN + 1)

#define ERR_MSP_CDM_END                 (0x3100)
/*CDM ERR NO. END*/

/* DIAG 0x4000-0x4fff */

#define  ERR_MSP_DIAG_ERROR_BEGIN               (0x4000)
#define  ERR_MSP_DIAG_ACORE_ERROR               (ERR_MSP_DIAG_ERROR_BEGIN + 1)  /* A */
#define  ERR_MSP_DIAG_CCORE_ERROR               (ERR_MSP_DIAG_ERROR_BEGIN + 2)  /* C */
#define  ERR_MSP_DIAG_INVALID_CMD               (ERR_MSP_DIAG_ERROR_BEGIN + 3)  /*  */
#define  ERR_MSP_DIAG_ERRPID_CMD                (ERR_MSP_DIAG_ERROR_BEGIN + 4)  /* PID */
#define  ERR_MSP_DIAG_UNKNOWNPID_CMD            (ERR_MSP_DIAG_ERROR_BEGIN + 5)  /* PID */
#define  ERR_MSP_DIAG_SAMPLE_START_FAIL         (ERR_MSP_DIAG_ERROR_BEGIN + 6)  /*  */    
#define  ERR_MSP_DIAG_TL_SEND_MSG_FAIL          (ERR_MSP_DIAG_ERROR_BEGIN + 7)  /* TL */
#define  ERR_MSP_DIAG_GUC_SEND_MSG_FAIL         (ERR_MSP_DIAG_ERROR_BEGIN + 8)  /* GUC */

#define  ERR_MSP_FAILURE                (0XFFFFFFFFU)
#define  ERR_MSP_SYSTEM                 (0XFFFFFFFFU)

/* The definition of error number which result in reboot */
enum
{
    MSP_REBOOT_FTM_ERR  = 0xb0000000,
	MSP_REBOOT_USB_SEND_ERROR = 0xb0000001,
    MSP_REBOOT_ID_BUTT  = 0xbfffffff
};



#endif /* __MSP_ERRNO_H__ */
