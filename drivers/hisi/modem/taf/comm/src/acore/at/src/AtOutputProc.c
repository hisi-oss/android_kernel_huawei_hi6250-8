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
#include "ATCmdProc.h"
#include "AtCheckFunc.h"
#include "AtParseCmd.h"
#include "AtInputProc.h"
#include "AtDataProc.h"
#include "cpm.h"
#include "AtTafAgentInterface.h"
#include "AtEventReport.h"




 /*****************************************************************************
   2 
 *****************************************************************************/

/*****************************************************************************
   2 
*****************************************************************************/

/*****************************************************************************
    .C
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_AT_OUTPUTPROC_C

const AT_RETURN_TAB_TYPE_STRU gastAtReturnCodeTab[]=
{
    {AT_SUCCESS,                                           {TAF_NULL_PTR,          TAF_NULL_PTR             }  },
    {AT_FAILURE,                                           {TAF_NULL_PTR,          TAF_NULL_PTR             }  },
    {AT_WAIT_SMS_INPUT,                                    {(TAF_UINT8*)"\r\n> ", (TAF_UINT8*)"\r\n> "      }  },
    {AT_WAIT_XML_INPUT,                                    {(TAF_UINT8*)"\r\n> ", (TAF_UINT8*)"\r\n> "      }  },
    {AT_WAIT_ASYNC_RETURN,                                 {TAF_NULL_PTR,          TAF_NULL_PTR             }  },

    {AT_BASIC_CODE_ENUM_BEGAIN,                            {TAF_NULL_PTR,          TAF_NULL_PTR             }  },

    {AT_OK,                                                {(TAF_UINT8*)"0", (TAF_UINT8*)"OK"           }},
    {AT_CONNECT,                                           {(TAF_UINT8*)"1", (TAF_UINT8*)"CONNECT"      }},
    {AT_RING,                                              {(TAF_UINT8*)"2", (TAF_UINT8*)"RING"         }},
    {AT_NO_CARRIER,                                        {(TAF_UINT8*)"3", (TAF_UINT8*)"NO CARRIER"   }},
    {AT_ERROR,                                             {(TAF_UINT8*)"4", (TAF_UINT8*)"ERROR"        }},
    {AT_NO_DIALTONE,                                       {(TAF_UINT8*)"6", (TAF_UINT8*)"NO DIALTONE"  }},
    {AT_BUSY,                                              {(TAF_UINT8*)"7", (TAF_UINT8*)"BUSY"         }},
    {AT_NO_ANSWER,                                         {(TAF_UINT8*)"8", (TAF_UINT8*)"NO ANSWER"    }},
    {AT_BASIC_CODE_ENUM_END,                               {TAF_NULL_PTR,     TAF_NULL_PTR              }  },
    {AT_CME_ERROR_ENUM_BEGAIN,                             {TAF_NULL_PTR,     TAF_NULL_PTR              }  },
    {AT_CME_PHONE_FAILURE,                                 {(TAF_UINT8*)"0" , (TAF_UINT8*)"phone failure"                                  }  },
    {AT_CME_NO_CONNECTION_TO_PHONE,                        {(TAF_UINT8*)"1" , (TAF_UINT8*)"NO CONNECTION TO PHONE"                         }  },
    {AT_CME_PHONE_ADAPTOR_LINK_RESERVED,                   {(TAF_UINT8*)"2" , (TAF_UINT8*)"PHONE ADAPTOR LINK RESERVED"                    }  },
    {AT_CME_OPERATION_NOT_ALLOWED,                         {(TAF_UINT8*)"3" , (TAF_UINT8*)"operation not allowed"                          }  },
    {AT_CME_OPERATION_NOT_SUPPORTED,                       {(TAF_UINT8*)"4" , (TAF_UINT8*)"operation not supported"                        }  },
    {AT_CME_PH_SIM_PIN_REQUIRED,                           {(TAF_UINT8*)"5" , (TAF_UINT8*)"PH SIM PIN REQUIRED"                            }  },
    {AT_CME_PH_FSIM_PIN_REQUIRED,                          {(TAF_UINT8*)"6" , (TAF_UINT8*)"PH-FSIM PIN REQUIRED"                           }  },
    {AT_CME_PH_FSIM_PUK_REQUIRED,                          {(TAF_UINT8*)"7" , (TAF_UINT8*)"PH-FSIM PUK REQUIRED"                           }  },
    {AT_CME_SIM_NOT_INSERTED,                              {(TAF_UINT8*)"10", (TAF_UINT8*)"SIM not inserted"                               }  },
    {AT_CME_SIM_PIN_REQUIRED,                              {(TAF_UINT8*)"11", (TAF_UINT8*)"SIM PIN required"                               }  },
    {AT_CME_SIM_PUK_REQUIRED,                              {(TAF_UINT8*)"12", (TAF_UINT8*)"SIM PUK required"                               }  },
    {AT_CME_SIM_FAILURE,                                   {(TAF_UINT8*)"13", (TAF_UINT8*)"SIM failure"                                    }  },
    {AT_CME_SIM_BUSY,                                      {(TAF_UINT8*)"14", (TAF_UINT8*)"SIM busy"                                       }  },
    {AT_CME_SIM_WRONG,                                     {(TAF_UINT8*)"15", (TAF_UINT8*)"SIM wrong"                                      }  },
    {AT_CME_INCORRECT_PASSWORD,                            {(TAF_UINT8*)"16", (TAF_UINT8*)"incorrect password"                             }  },
    {AT_CME_SIM_PIN2_REQUIRED,                             {(TAF_UINT8*)"17", (TAF_UINT8*)"SIM PIN2 required"                              }  },
    {AT_CME_SIM_PUK2_REQUIRED,                             {(TAF_UINT8*)"18", (TAF_UINT8*)"SIM PUK2 required"                              }  },
    {AT_CME_MEMORY_FULL,                                   {(TAF_UINT8*)"20", (TAF_UINT8*)"memory full"                                    }  },
    {AT_CME_INVALID_INDEX,                                 {(TAF_UINT8*)"21", (TAF_UINT8*)"invalid index"                                  }  },
    {AT_CME_NOT_FOUND,                                     {(TAF_UINT8*)"22", (TAF_UINT8*)"not found"                                      }  },
    {AT_CME_MEMORY_FAILURE,                                {(TAF_UINT8*)"23", (TAF_UINT8*)"memory failure"                                 }  },
    {AT_CME_TEXT_STRING_TOO_LONG,                          {(TAF_UINT8*)"24", (TAF_UINT8*)"text string too long"                           }  },
    {AT_CME_INVALID_CHARACTERS_IN_TEXT_STRING,             {(TAF_UINT8*)"25", (TAF_UINT8*)"INVALID CHARACTERS IN TEXT STRING"              }  },
    {AT_CME_DIAL_STRING_TOO_LONG,                          {(TAF_UINT8*)"26", (TAF_UINT8*)"dial string too long"                           }  },
    {AT_CME_INVALID_CHARACTERS_IN_DIAL_STRING,             {(TAF_UINT8*)"27", (TAF_UINT8*)"invalid characters in dial string"              }  },

    {AT_CME_SPN_FILE_CONTENT_ERROR,                        {(TAF_UINT8*)"65284", (TAF_UINT8*)"SPN FILE CONTENT ERROR"                      }  },
    {AT_CME_SPN_FILE_QUERY_REJECT,                         {(TAF_UINT8*)"65285", (TAF_UINT8*)"READ SPN FILE REJECTED"                      }  },
    {AT_CME_SPN_FILE_NOT_EXISTS,                           {(TAF_UINT8*)"65286", (TAF_UINT8*)"SPN FILE NOT EXIST"                          }  },

    {AT_CME_NO_NETWORK_SERVICE,                            {(TAF_UINT8*)"30",  (TAF_UINT8*)"NO NETWORK SERVICE"                             }  },
    {AT_CME_NETWORK_TIMEOUT,                               {(TAF_UINT8*)"31",  (TAF_UINT8*)"NETWORK TIMEOUT"                                }  },
    {AT_CME_NETWORK_NOT_ALLOWED_EMERGENCY_CALLS_ONLY,      {(TAF_UINT8*)"32",  (TAF_UINT8*)"NETWORK NOT ALLOWED - EMERGENCY CALLS ONLY"     }  },
    {AT_CME_NETWORK_PERSONALIZATION_PIN_REQUIRED,          {(TAF_UINT8*)"40",  (TAF_UINT8*)"NETWORK PERSONALIZATION PIN REQUIRED"           }  },
    {AT_CME_NETWORK_PERSONALIZATION_PUK_REQUIRED,          {(TAF_UINT8*)"41",  (TAF_UINT8*)"NETWORK PERSONALIZATION PUK REQUIRED"           }  },
    {AT_CME_NETWORK_SUBSET_PERSONALIZATION_PIN_REQUIRED,   {(TAF_UINT8*)"42",  (TAF_UINT8*)"NETWORK SUBSET PERSONALIZATION PIN REQUIRED"    }  },
    {AT_CME_NETWORK_SUBSET_PERSONALIZATION_PUK_REQUIRED,   {(TAF_UINT8*)"43",  (TAF_UINT8*)"NETWORK SUBSET PERSONALIZATION PUK REQUIRED"    }  },
    {AT_CME_SERVICE_PROVIDER_PERSONALIZATION_PIN_REQUIRED, {(TAF_UINT8*)"44",  (TAF_UINT8*)"SERVICE PROVIDER PERSONALIZATION PIN REQUIRED"  }  },
    {AT_CME_SERVICE_PROVIDER_PERSONALIZATION_PUK_REQUIRED, {(TAF_UINT8*)"45",  (TAF_UINT8*)"SERVICE PROVIDER PERSONALIZATION PUK REQUIRED"  }  },
    {AT_CME_CORPORATE_PERSONALIZATION_PIN_REQUIRED,        {(TAF_UINT8*)"46",  (TAF_UINT8*)"CORPORATE PERSONALIZATION PIN REQUIRED"         }  },
    {AT_CME_CORPORATE_PERSONALIZATION_PUK_REQUIRED,        {(TAF_UINT8*)"47",  (TAF_UINT8*)"CORPORATE PERSONALIZATION PUK REQUIRED"         }  },
    {AT_CME_HIDDEN_KEY_REQUIRED,                           {(TAF_UINT8*)"48",  (TAF_UINT8*)"hidden key required"                            }  },
    {AT_CME_EAP_METHOD_NOT_SUPPORTED,                      {(TAF_UINT8*)"49",  (TAF_UINT8*)"EAP method not supported"                       }  },
    {AT_CME_INCORRECT_PARAMETERS,                          {(TAF_UINT8*)"50",  (TAF_UINT8*)"Incorrect parameters"                           }  },
    {AT_CME_RX_DIV_NOT_SUPPORTED,                          {(TAF_UINT8*)"0" ,  (TAF_UINT8*)"NOT SUPPORTED"                                  }  },
    {AT_CME_RX_DIV_OTHER_ERR,                              {(TAF_UINT8*)"1" ,  (TAF_UINT8*)"OTHER ERROR"                                    }  },
    {AT_CME_UNKNOWN,                                       {(TAF_UINT8*)"100", (TAF_UINT8*)"UNKNOWN"                                        }  },

    {AT_CME_ILLEGAL_MS,                                    {(TAF_UINT8*)"103", (TAF_UINT8*)"Illegal MS"                                     }  },
    {AT_CME_ILLEGAL_ME,                                    {(TAF_UINT8*)"106", (TAF_UINT8*)"Illegal ME"                                     }  },
    {AT_CME_GPRS_SERVICES_NOT_ALLOWED,                     {(TAF_UINT8*)"107", (TAF_UINT8*)"GPRS services not allowed"                      }  },
    {AT_CME_PLMN_NOT_ALLOWED,                              {(TAF_UINT8*)"111", (TAF_UINT8*)"PLMN not allowed"                               }  },
    {AT_CME_LOCATION_AREA_NOT_ALLOWED,                     {(TAF_UINT8*)"112", (TAF_UINT8*)"Location area not allowed"                      }  },
    {AT_CME_ROAMING_NOT_ALLOWED_IN_THIS_LOCATION_AREA,     {(TAF_UINT8*)"113", (TAF_UINT8*)"Roaming not allowed in this location area"      }  },

    {AT_CME_SERVICE_OPTION_NOT_SUPPORTED,                  {(TAF_UINT8*)"132", (TAF_UINT8*)"service option not supported"                   }  },
    {AT_CME_REQUESTED_SERVICE_OPTION_NOT_SUBSCRIBED,       {(TAF_UINT8*)"133", (TAF_UINT8*)"requested service option not subscribed"        }  },
    {AT_CME_SERVICE_OPTION_TEMPORARILY_OUT_OF_ORDER,       {(TAF_UINT8*)"134", (TAF_UINT8*)"service option temporarily out of order"        }  },
    {AT_CME_PDP_AUTHENTICATION_FAILURE,                    {(TAF_UINT8*)"149", (TAF_UINT8*)"PDP authentication failure"                     }  },

    {AT_CME_INVALID_MOBILE_CLASS,                          {(TAF_UINT8*)"150" ,(TAF_UINT8*)"invalid mobile class"                           }  },
    {AT_CME_UNSPECIFIED_GPRS_ERROR,                        {(TAF_UINT8*)"148" ,(TAF_UINT8*)"unspecified GPRS error"                         }  },

    {AT_CME_VBS_VGCS_NOT_SUPPORTED_BY_THE_NETWORK,         {(TAF_UINT8*)"151", (TAF_UINT8*)"VBS/VGCS not supported by the network"          }  },
    {AT_CME_NO_SERVICE_SUBSCRIPTION_ON_SIM,                {(TAF_UINT8*)"152", (TAF_UINT8*)"No service subscription on SIM"                 }  },
    {AT_CME_NO_SUBSCRIPTION_FOR_GROUP_ID,                  {(TAF_UINT8*)"153", (TAF_UINT8*)"No subscription for group ID"                   }  },
    {AT_CME_GROUP_ID_NOT_ACTIVATED_ON_SIM,                 {(TAF_UINT8*)"154", (TAF_UINT8*)"Group Id not activated on SIM"                  }  },
    {AT_CME_NO_MATCHING_NOTIFICATION,                      {(TAF_UINT8*)"155", (TAF_UINT8*)"No matching notification"                       }  },
    {AT_CME_VBS_VGCS_CALL_ALREADY_PRESENT,                 {(TAF_UINT8*)"156", (TAF_UINT8*)"VBS/VGCS call already present"                  }  },
    {AT_CME_CONGESTION,                                    {(TAF_UINT8*)"157", (TAF_UINT8*)"Congestion"                                     }  },
    {AT_CME_NETWORK_FAILURE,                               {(TAF_UINT8*)"158", (TAF_UINT8*)"Network failure"                                }  },
    {AT_CME_UPLINK_BUSY,                                   {(TAF_UINT8*)"159", (TAF_UINT8*)"Uplink busy"                                    }  },
    {AT_CME_NO_ACCESS_RIGHTS_FOR_SIM_FILE,                 {(TAF_UINT8*)"160", (TAF_UINT8*)"No access rights for SIM file"                  }  },
    {AT_CME_NO_SUBSCRIPTION_FOR_PRIORITY,                  {(TAF_UINT8*)"161", (TAF_UINT8*)"No subscription for priority"                   }  },
    {AT_CME_OPERATION_NOT_APPLICABLE_OR_NOT_POSSIBLE,      {(TAF_UINT8*)"162", (TAF_UINT8*)"operation not applicable or not possible"       }  },
    {AT_CME_FILE_NOT_EXISTS,                               {(TAF_UINT8*)"163", (TAF_UINT8*)"FILE NOT EXIST"                            }  },

    {AT_CME_1X_RAT_NOT_SUPPORTED,                          {(VOS_UINT8*)"170", (VOS_UINT8*)"1X RAT NOT SUPPORTED"                }  },

    {AT_CME_SERVICE_NOT_PROVISIONED,                       {(VOS_UINT8*)"171", (VOS_UINT8*)"Service not provisioned"       }  },

    /* 3GPP 27007 9.2.3 Also all other values below 256 are reserved */
    /* Added by L60609 for V7R1C50 AT&T&DCM, 2012-6-16, begin */
    {AT_CME_PDP_ACT_LIMIT,                                 {(TAF_UINT8*)"300", (TAF_UINT8*)"PDP ACT LIMIT"                            }  },
    {AT_CME_NET_SEL_MENU_DISABLE,                          {(TAF_UINT8*)"301", (TAF_UINT8*)"NETWORK SELECTION MENU DISABLE"           }  },
    /* Added by L60609 for V7R1C50 AT&T&DCM, 2012-6-16, end */

    {AT_CME_CS_IMS_SERV_EXIST,                             {(TAF_UINT8*)"302", (TAF_UINT8*)"CS SERVICE EXIST"                         }  },

    {AT_CME_FDN_FAILED,                                    {(TAF_UINT8*)"303", (TAF_UINT8*)"FDN Failed"                              }  },
    {AT_CME_CALL_CONTROL_FAILED,                           {(TAF_UINT8*)"304", (TAF_UINT8*)"Call Control Failed"                           }  },
    {AT_CME_CALL_CONTROL_BEYOND_CAPABILITY,                {(TAF_UINT8*)"305", (TAF_UINT8*)"Call Control beyond Capability"                }  },

    {AT_CME_IMS_NOT_SUPPORT,                               {(VOS_UINT8*)"306", (VOS_UINT8*)"IMS Not Support"                 }  },
    {AT_CME_IMS_SERVICE_EXIST,                             {(VOS_UINT8*)"307", (VOS_UINT8*)"IMS Service Exist"               }  },
    {AT_CME_IMS_VOICE_DOMAIN_PS_ONLY,                      {(VOS_UINT8*)"308", (VOS_UINT8*)"IMS Voice Domain PS Only"              }  },
    {AT_CME_IMS_STACK_TIMEOUT,                             {(VOS_UINT8*)"309", (VOS_UINT8*)"IMS Stack Time Out"              }  },

    {AT_CME_NO_RF,                                         {(TAF_UINT8*)"310"  ,(TAF_UINT8*)"NO RF"                          }  },

    /* Added by c64416 for AT Project 2011-10-23  Begin */
    {AT_CME_APN_LEN_ILLEGAL,                               {(VOS_UINT8*)"700", (VOS_UINT8*)"APN length illegal"              }  },
    {AT_CME_APN_SYNTACTICAL_ERROR,                         {(VOS_UINT8*)"701", (VOS_UINT8*)"APN syntactical error"           }  },
    {AT_CME_SET_APN_BEFORE_SET_AUTH,                       {(VOS_UINT8*)"702", (VOS_UINT8*)"set APN before set auth"         }  },
    {AT_CME_AUTH_TYPE_ILLEGAL,                             {(VOS_UINT8*)"703", (VOS_UINT8*)"auth type illegal"               }  },
    {AT_CME_USER_NAME_TOO_LONG,                            {(VOS_UINT8*)"704", (VOS_UINT8*)"user name too long"              }  },
    {AT_CME_USER_PASSWORD_TOO_LONG,                        {(VOS_UINT8*)"705", (VOS_UINT8*)"user password too long"          }  },
    {AT_CME_ACCESS_NUM_TOO_LONG,                           {(VOS_UINT8*)"706", (VOS_UINT8*)"access number too long"          }  },
    {AT_CME_CALL_CID_IN_OPERATION,                         {(VOS_UINT8*)"707", (VOS_UINT8*)"call cid in operation"           }  },
    {AT_CME_BEARER_TYPE_NOT_DEFAULT,                       {(VOS_UINT8*)"708", (VOS_UINT8*)"bearer type not default"         }  },
    {AT_CME_CALL_CID_INVALID,                              {(VOS_UINT8*)"709", (VOS_UINT8*)"call cid invalid"                }  },
    {AT_CME_CALL_CID_ACTIVE,                               {(VOS_UINT8*)"710", (VOS_UINT8*)"call cid active"                 }  },
    {AT_CME_BEARER_TYPE_ILLEGAL,                           {(VOS_UINT8*)"711", (VOS_UINT8*)"bearer type illegal"             }  },
    {AT_CME_MUST_EXIST_DEFAULT_TYPE_CID,                   {(VOS_UINT8*)"712", (VOS_UINT8*)"must exist default type cid"     }  },
    {AT_CME_PDN_TYPE_ILLEGAL,                              {(VOS_UINT8*)"713", (VOS_UINT8*)"PDN type illegal"                }  },
    {AT_CME_IPV4_ADDR_ALLOC_TYPE_ILLEGAL,                  {(VOS_UINT8*)"714", (VOS_UINT8*)"IPV4 address alloc type illegal" }  },
    {AT_CME_LINK_CID_INVALID,                              {(VOS_UINT8*)"715", (VOS_UINT8*)"link cid invalid"                }  },
    /* Added by c64416 for AT Project 2011-10-23  End*/
    {AT_CME_NO_SUCH_ELEMENT,                               {(VOS_UINT8*)"716", (VOS_UINT8*)"no such element"                 }  },
    {AT_CME_MISSING_RESOURCE,                              {(VOS_UINT8*)"717", (VOS_UINT8*)"missing resource"                }  },
    {AT_CME_OPERATION_NOT_ALLOWED_IN_CL_MODE,              {(VOS_UINT8*)"718", (VOS_UINT8*)"operation not allowed in CL mode"                }  },
    {AT_CME_ERROR_ENUM_END,                                {TAF_NULL_PTR,       TAF_NULL_PTR                 }  },

    /*AT*/
    {AT_DEVICE_ERROR_BEGIN,                                {VOS_NULL_PTR   ,VOS_NULL_PTR                                     }  },
    {AT_DEVICE_MODE_ERROR,                                 {(VOS_UINT8*)"0", (VOS_UINT8*)"Mode Error"                        }  },
    {AT_FCHAN_BAND_NOT_MATCH,                              {(VOS_UINT8*)"1", (VOS_UINT8*)"Band not match"                    }  },
    {AT_FCHAN_SET_CHANNEL_FAIL,                            {(VOS_UINT8*)"2", (VOS_UINT8*)"Channel number set fail"           }  },
    {AT_FCHAN_BAND_CHANNEL_NOT_MATCH,                      {(VOS_UINT8*)"3", (VOS_UINT8*)"Band and Channel not match"        }  },
    {AT_FCHAN_OTHER_ERR,                                   {(VOS_UINT8*)"4", (VOS_UINT8*)"Other error"                       }  },
    {AT_FDAC_CHANNEL_NOT_SET,                              {(VOS_UINT8*)"0", (VOS_UINT8*)"channel not set"                   }  },
    {AT_FDAC_SET_FAIL,                                     {(VOS_UINT8*)"2", (VOS_UINT8*)"Set DAC fail"                      }  },
    {AT_CHANNEL_NOT_SET,                                   {(VOS_UINT8*)"1", (VOS_UINT8*)"channel not set"                   }  },
    {AT_FTXON_SET_FAIL,                                    {(VOS_UINT8*)"2", (VOS_UINT8*)"Set FTXON fail"                    }  },
    {AT_FTXON_OTHER_ERR,                                   {(VOS_UINT8*)"3", (VOS_UINT8*)"other FTXON Error"                 }  },
    {AT_DATA_UNLOCK_ERROR,                                 {(VOS_UINT8*)"0", (VOS_UINT8*)"Data UNLock Error:0"               }  },
    {AT_DPAUPA_ERROR,                                      {(VOS_UINT8*)"1", (VOS_UINT8*)"DPA UPA Error:1"                   }  },
    {AT_SN_LENGTH_ERROR,                                   {(VOS_UINT8*)"0", (VOS_UINT8*)"SN LENGTH Error:1"                 }  },
    {AT_FRXON_OTHER_ERR,                                   {(VOS_UINT8*)"3", (VOS_UINT8*)"other FRXON Error"                 }  },
    {AT_FRXON_SET_FAIL,                                    {(VOS_UINT8*)"2", (VOS_UINT8*)"Set FRXON fail"                    }  },
    {AT_FPA_OTHER_ERR,                                     {(VOS_UINT8*)"3", (VOS_UINT8*)"Other FPA error"                   }  },
    {AT_FLNA_OTHER_ERR,                                    {(VOS_UINT8*)"3", (VOS_UINT8*)"Other LNA error"                   }  },
    {AT_FRSSI_OTHER_ERR,                                   {(VOS_UINT8*)"4", (VOS_UINT8*)"Other FRSSI error"                 }  },
    {AT_FRSSI_RX_NOT_OPEN,                                 {(VOS_UINT8*)"2", (VOS_UINT8*)"RX Not Open"                       }  },
    {AT_SD_CARD_NOT_EXIST,                                 {(VOS_UINT8*)"0", (VOS_UINT8*)"SD Card Not Exist"                 }  },
    {AT_SD_CARD_INIT_FAILED,                               {(VOS_UINT8*)"1", (VOS_UINT8*)"SD Card init fail"                 }  },
    {AT_SD_CARD_OPRT_NOT_ALLOWED,                          {(VOS_UINT8*)"2", (VOS_UINT8*)"Sd Oprt not allowed"               }  },
    {AT_SD_CARD_ADDR_ERR,                                  {(VOS_UINT8*)"3", (VOS_UINT8*)"Sd Card Address Error"             }  },
    {AT_SD_CARD_OTHER_ERR,                                 {(VOS_UINT8*)"4", (VOS_UINT8*)"Sd Card Other Error"               }  },
    {AT_DEVICE_OTHER_ERROR,                                {(VOS_UINT8*)"1", (VOS_UINT8*)"1"                                 }  },
    {AT_PHYNUM_LENGTH_ERR,                                 {(VOS_UINT8*)"0", (VOS_UINT8*)"Physical Number length error"      }  },
    {AT_PHYNUM_NUMBER_ERR,                                 {(VOS_UINT8*)"1", (VOS_UINT8*)"Physical Number number error"      }  },
    {AT_PHYNUM_TYPE_ERR,                                   {(VOS_UINT8*)"2", (VOS_UINT8*)"Physical Number type error"        }  },
    {AT_SIMLOCK_PLMN_NUM_ERR,                              {(VOS_UINT8*)"2", (VOS_UINT8*)"Simlock Plmn num invalid"          }  },
    {AT_SIMLOCK_PLMN_MNC_LEN_ERR,                          {(VOS_UINT8*)"3", (VOS_UINT8*)"Simlock Plmn MNC len Err"          }  },

    /* Added by c64416 for AT Project 2011-10-23  Begin */
    {AT_DEVICE_NOT_SUPPORT,                                {(VOS_UINT8*)"500", (VOS_UINT8*)"Undone",                            }},
    {AT_DEVICE_ERR_UNKNOWN,                                {(VOS_UINT8*)"501", (VOS_UINT8*)"Unknown error",                     }},
    {AT_DEVICE_INVALID_PARAMETERS,                         {(VOS_UINT8*)"502", (VOS_UINT8*)"Invalid parameters",                }},
    {AT_DEVICE_NV_NOT_SUPPORT_ID,                          {(VOS_UINT8*)"520", (VOS_UINT8*)"NVIM Not Exist",                    }},
    {AT_DEVICE_NV_READ_FAILURE,                            {(VOS_UINT8*)"521", (VOS_UINT8*)"Read NVIM Failure",                 }},
    {AT_DEVICE_NV_WRITE_FAIL_OVERLEN,                      {(VOS_UINT8*)"522", (VOS_UINT8*)"Write Error for Length Overflow",   }},
    {AT_DEVICE_NV_WRITE_FAIL_BADFLASH,                     {(VOS_UINT8*)"523", (VOS_UINT8*)"Write Error for Flash Bad Block",   }},
    {AT_DEVICE_NV_WRITE_FAIL_UNKNOWN,                      {(VOS_UINT8*)"524", (VOS_UINT8*)"Write Error for Unknown Reason",    }},
    {AT_DEVICE_VCTCXO_OVER_HIGH,                           {(VOS_UINT8*)"525", (VOS_UINT8*)"Higher Voltage",                    }},
    {AT_DEVICE_UE_MODE_ERR,                                {(VOS_UINT8*)"526", (VOS_UINT8*)"UE Mode Error",                     }},
    {AT_DEVICE_NOT_SET_CHAN,                               {(VOS_UINT8*)"527", (VOS_UINT8*)"Not Set Appointed Channel",         }},
    {AT_DEVICE_OPEN_UL_CHAN_ERROR,                         {(VOS_UINT8*)"528", (VOS_UINT8*)"Open TX Transmitter Failure",       }},
    {AT_DEVICE_OPEN_DL_CHAN_ERROR,                         {(VOS_UINT8*)"529", (VOS_UINT8*)"Open RX Transmitter Failure",       }},
    {AT_DEVICE_OPEN_CHAN_ERROR,                            {(VOS_UINT8*)"530", (VOS_UINT8*)"Open Channel Failure",              }},
    {AT_DEVICE_CLOSE_CHAN_ERROR,                           {(VOS_UINT8*)"531", (VOS_UINT8*)"Close Channel Failure",             }},
    {AT_DEVICE_OPERATION_NOT_SUPPORT,                      {(VOS_UINT8*)"532", (VOS_UINT8*)"Not Support",                       }},
    {AT_DEVICE_INVALID_OP,                                 {(VOS_UINT8*)"533", (VOS_UINT8*)"Invalid Operation",                 }},
    {AT_DEVICE_CHAN_BAND_INVALID,                          {(VOS_UINT8*)"534", (VOS_UINT8*)"Band No Match",                     }},
    {AT_DEVICE_SET_CHAN_INFO_FAILURE,                      {(VOS_UINT8*)"535", (VOS_UINT8*)"Set Channel Information Failure",   }},
    {AT_DEVICE_CHAN_BAND_CHAN_NOT_MAP,                     {(VOS_UINT8*)"536", (VOS_UINT8*)"Band And Channel Not Combined",     }},
    {AT_DEVICE_SET_TX_POWER_FAILURE,                       {(VOS_UINT8*)"537", (VOS_UINT8*)"Set TX Transmitter Power Error",    }},
    {AT_DEVICE_SET_PA_LEVEL_FAILURE,                       {(VOS_UINT8*)"538", (VOS_UINT8*)"Set PA Level Failure",              }},
    {AT_DEVICE_NOT_SET_CURRENT_CHAN,                       {(VOS_UINT8*)"539", (VOS_UINT8*)"Not Set Current Channel",           }},
    {AT_DEVICE_CUR_APC_UNAVAILABLE,                        {(VOS_UINT8*)"540", (VOS_UINT8*)"APC Value Can't Be Read",           }},
    {AT_DEVICE_SET_APC_ERR,                                {(VOS_UINT8*)"541", (VOS_UINT8*)"Write APC Failure",                 }},
    {AT_DEVICE_RD_APC_ERR,                                 {(VOS_UINT8*)"542", (VOS_UINT8*)"Read APC Failure",                  }},
    {AT_DEVICE_SET_LNA_ERR,                                {(VOS_UINT8*)"543", (VOS_UINT8*)"Set AAGC Failure",                  }},
    {AT_DEVICE_NOT_OPEN_DL_CHAN,                           {(VOS_UINT8*)"544", (VOS_UINT8*)"RX Transmitter Not Open",           }},
    {AT_DEVICE_NOT_OPEN_UL_CHAN,                           {(VOS_UINT8*)"545", (VOS_UINT8*)"TX Transmitter Not Open",           }},
    {AT_DEVICE_NO_SIGNAL,                                  {(VOS_UINT8*)"546", (VOS_UINT8*)"No Signal",                         }},
    {AT_DEVICE_PHYNUM_LEN_ERR,                             {(VOS_UINT8*)"547", (VOS_UINT8*)"PHY Number Length Error",           }},
    {AT_DEVICE_PHYNUM_INVALID,                             {(VOS_UINT8*)"548", (VOS_UINT8*)"Invalid PHY Number",                }},
    {AT_DEVICE_PHYNUM_TYPE_ERR,                            {(VOS_UINT8*)"549", (VOS_UINT8*)"Invalid PHY Type",                  }},
    {AT_DEVICE_PLATFORM_INFO_UNAVAILABLE,                  {(VOS_UINT8*)"550", (VOS_UINT8*)"Platform Infomation Can't Be Read", }},
    {AT_DEVICE_DATA_LOCK,                                  {(VOS_UINT8*)"551", (VOS_UINT8*)"Not unlock, write error",           }},
    {AT_DEVICE_PLMN_OVER_20,                               {(VOS_UINT8*)"552", (VOS_UINT8*)"Card Number More than 20",          }},
    {AT_DEVICE_MNC_NUM_INVALID,                            {(VOS_UINT8*)"553", (VOS_UINT8*)"<mnc-digital-num> Enter Error",     }},
    {AT_DEVICE_GET_VER_ERR,                                {(VOS_UINT8*)"554", (VOS_UINT8*)"Read Version Failure",              }},
    {AT_DEVICE_PORTLOCK_ERR,                               {(VOS_UINT8*)"555", (VOS_UINT8*)"Operation Failure",                 }},
    {AT_DEVICE_PWD_ERR,                                    {(VOS_UINT8*)"556", (VOS_UINT8*)"Password Error",                    }},
    {AT_DEVICE_TIMEOUT_ERR,                                {(VOS_UINT8*)"557", (VOS_UINT8*)"Timeout",                           }},
    {AT_DEVICE_NOT_ENOUGH_MEMORY,                          {(VOS_UINT8*)"558", (VOS_UINT8*)"No Memory",                         }},
    {AT_DEVICE_SIMM_LOCK,                                  {(VOS_UINT8*)"559", (VOS_UINT8*)"SIM Lock Active",                   }},
    {AT_DEVICE_CLOSE_UL_CHAN_FAILURE,                      {(VOS_UINT8*)"560", (VOS_UINT8*)"Close TX Transmitter Failure",      }},
    {AT_DEVICE_CLOSE_DL_CHAN_FAILURE,                      {(VOS_UINT8*)"561", (VOS_UINT8*)"Close RX Transmitter Failure",      }},
    {AT_DEVICE_NV_DATA_INVALID,                            {(VOS_UINT8*)"562", (VOS_UINT8*)"NV DATA INVALID",                   }},
    /* Added by c64416 for AT Project 2011-10-23  End*/

    {AT_PERSONALIZATION_ERR_BEGIN,                          {VOS_NULL_PTR     , VOS_NULL_PTR                                     } },
    {AT_PERSONALIZATION_IDENTIFY_FAIL,                      {(VOS_UINT8*)"301", (VOS_UINT8*)"Identify failure",                  } },
    {AT_PERSONALIZATION_SIGNATURE_FAIL,                     {(VOS_UINT8*)"302", (VOS_UINT8*)"Signature verification failed",     } },
    {AT_PERSONALIZATION_DK_INCORRECT,                       {(VOS_UINT8*)"303", (VOS_UINT8*)"Debug port password incorrect",     } },
    {AT_PERSONALIZATION_PH_PHYNUM_LEN_ERROR,                {(VOS_UINT8*)"304", (VOS_UINT8*)"Phone physical number length error",} },
    {AT_PERSONALIZATION_PH_PHYNUM_VALUE_ERROR,              {(VOS_UINT8*)"305", (VOS_UINT8*)"Phone physical number value error", } },
    {AT_PERSONALIZATION_PH_PHYNUM_TYPE_ERROR,               {(VOS_UINT8*)"306", (VOS_UINT8*)"Phone physical number type error",  } },
    {AT_PERSONALIZATION_RSA_ENCRYPT_FAIL,                   {(VOS_UINT8*)"307", (VOS_UINT8*)"RSA encryption failed",             } },
    {AT_PERSONALIZATION_RSA_DECRYPT_FAIL,                   {(VOS_UINT8*)"308", (VOS_UINT8*)"RSA decryption failed",             } },
    {AT_PERSONALIZATION_GET_RAND_NUMBER_FAIL,               {(VOS_UINT8*)"309", (VOS_UINT8*)"Generate random number failed",     } },
    {AT_PERSONALIZATION_WRITE_HUK_FAIL,                     {(VOS_UINT8*)"310", (VOS_UINT8*)"Write HUK failed",                  } },
    {AT_PERSONALIZATION_FLASH_ERROR,                        {(VOS_UINT8*)"311", (VOS_UINT8*)"Flash error",                       } },
    {AT_PERSONALIZATION_OTHER_ERROR,                        {(VOS_UINT8*)"312", (VOS_UINT8*)"Other error",                       } },
    {AT_PERSONALIZATION_ERR_END,                            {VOS_NULL_PTR     , VOS_NULL_PTR                                     } },

    {AT_DEVICE_ERROR_END,                                  {VOS_NULL_PTR,       VOS_NULL_PTR                                     } },

    {AT_CMS_ERROR_ENUM_BEGAIN,                             {TAF_NULL_PTR,       TAF_NULL_PTR                                     } },
    {AT_CMS_UNASSIGNED_UNALLOCATED_NUMBER,                            { (TAF_UINT8*)"1  ", (TAF_UINT8*)"Unassigned (unallocated) number"                             } },
    {AT_CMS_OPERATOR_DETERMINED_BARRING,                              { (TAF_UINT8*)"8  ", (TAF_UINT8*)"Operator determined barring"                                 } },
    {AT_CMS_CALL_BARRED,                                              { (TAF_UINT8*)"10 ", (TAF_UINT8*)"Call barred"                                                 } },
    {AT_CMS_SHORT_MESSAGE_TRANSFER_REJECTED,                          { (TAF_UINT8*)"21 ", (TAF_UINT8*)"Short message transfer rejected"                             } },
    {AT_CMS_DESTINATION_OUT_OF_SERVICE,                               { (TAF_UINT8*)"27 ", (TAF_UINT8*)"Destination out of service"                                  } },
    {AT_CMS_UNIDENTIFIED_SUBSCRIBER,                                  { (TAF_UINT8*)"28 ", (TAF_UINT8*)"Unidentified subscriber"                                     } },
    {AT_CMS_FACILITY_REJECTED,                                        { (TAF_UINT8*)"29 ", (TAF_UINT8*)"Facility rejected"                                           } },
    {AT_CMS_UNKNOWN_SUBSCRIBER,                                       { (TAF_UINT8*)"30 ", (TAF_UINT8*)"Unknown subscriber"                                          } },
    {AT_CMS_NETWORK_OUT_OF_ORDER,                                     { (TAF_UINT8*)"38 ", (TAF_UINT8*)"Network out of order"                                        } },
    {AT_CMS_TEMPORARY_FAILURE,                                        { (TAF_UINT8*)"41 ", (TAF_UINT8*)"Temporary failure"                                           } },
    {AT_CMS_CONGESTION,                                               { (TAF_UINT8*)"42 ", (TAF_UINT8*)"Congestion"                                                  } },
    {AT_CMS_RESOURCES_UNAVAILABLE_UNSPECIFIED,                        { (TAF_UINT8*)"47 ", (TAF_UINT8*)"Resources unavailable, unspecified"                          } },
    {AT_CMS_REQUESTED_FACILITY_NOT_SUBSCRIBED,                        { (TAF_UINT8*)"50 ", (TAF_UINT8*)"Requested facility not subscribed"                           } },
    {AT_CMS_REQUESTED_FACILITY_NOT_IMPLEMENTED,                       { (TAF_UINT8*)"69 ", (TAF_UINT8*)"Requested facility not implemented"                          } },
    {AT_CMS_INVALID_SHORT_MESSAGE_TRANSFER_REFERENCE_VALUE,           { (TAF_UINT8*)"81 ", (TAF_UINT8*)"Invalid short message transfer reference value"              } },
    {AT_CMS_INVALID_MESSAGE_UNSPECIFIED,                              { (TAF_UINT8*)"95 ", (TAF_UINT8*)"Invalid message, unspecified"                                } },
    {AT_CMS_INVALID_MANDATORY_INFORMATION,                            { (TAF_UINT8*)"96 ", (TAF_UINT8*)"Invalid mandatory information"                               } },
    {AT_CMS_MESSAGE_TYPE_NON_EXISTENT_OR_NOT_IMPLEMENTED,             { (TAF_UINT8*)"97 ", (TAF_UINT8*)"Message type non existent or not implemented"                } },
    {AT_CMS_MESSAGE_NOT_COMPATIBLE_WITH_SHORT_MESSAGE_PROTOCOL_STATE, { (TAF_UINT8*)"98 ", (TAF_UINT8*)"Message not compatible with short message protocol state"    } },
    {AT_CMS_INFORMATION_ELEMENT_NON_EXISTENT_OR_NOT_IMPLEMENTED,      { (TAF_UINT8*)"99 ", (TAF_UINT8*)"Information element non existent or not implemented"         } },
    {AT_CMS_PROTOCOL_ERROR_UNSPECIFIED,                               { (TAF_UINT8*)"111", (TAF_UINT8*)"Protocol error, unspecified"                                 } },
    {AT_CMS_INTERWORKING_UNSPECIFIED,                                 { (TAF_UINT8*)"127", (TAF_UINT8*)"Interworking, unspecified"                                   } },

    {AT_CMS_TELEMATIC_INTERWORKING_NOT_SUPPORTED,                     { (TAF_UINT8*)"128", (TAF_UINT8*)"Telematic interworking not supported"                        } },
    {AT_CMS_SHORT_MESSAGE_TYPE_0_NOT_SUPPORTED,                       { (TAF_UINT8*)"129", (TAF_UINT8*)"Short message Type 0 not supported"                          } },
    {AT_CMS_CANNOT_REPLACE_SHORT_MESSAGE,                             { (TAF_UINT8*)"130", (TAF_UINT8*)"Cannot replace short message"                                } },
    {AT_CMS_UNSPECIFIED_TPPID_ERROR,                                  { (TAF_UINT8*)"143", (TAF_UINT8*)"Unspecified TPPID error"                                     } },
    {AT_CMS_DATA_CODING_SCHEME_ALPHABET_NOT_SUPPORTED,                { (TAF_UINT8*)"144", (TAF_UINT8*)"Data coding scheme (alphabet) not supported"                 } },
    {AT_CMS_MESSAGE_CLASS_NOT_SUPPORTED,                              { (TAF_UINT8*)"145", (TAF_UINT8*)"Message class not supported"                                 } },
    {AT_CMS_UNSPECIFIED_TPDCS_ERROR,                                  { (TAF_UINT8*)"159", (TAF_UINT8*)"Unspecified TPDCS error"                                     } },
    {AT_CMS_COMMAND_CANNOT_BE_ACTIONED,                               { (TAF_UINT8*)"160", (TAF_UINT8*)"Command cannot be actioned"                                  } },
    {AT_CMS_COMMAND_UNSUPPORTED,                                      { (TAF_UINT8*)"161", (TAF_UINT8*)"Command unsupported"                                         } },
    {AT_CMS_UNSPECIFIED_TPCOMMAND_ERROR,                              { (TAF_UINT8*)"175", (TAF_UINT8*)"Unspecified TPCommand erro"                                  } },
    {AT_CMS_TPDU_NOT_SUPPORTED,                                       { (TAF_UINT8*)"176", (TAF_UINT8*)"TPDU not supported"                                          } },
    {AT_CMS_SC_BUSY,                                                  { (TAF_UINT8*)"192", (TAF_UINT8*)"SC busy"                                                     } },
    {AT_CMS_NO_SC_SUBSCRIPTION,                                       { (TAF_UINT8*)"193", (TAF_UINT8*)"No SC subscription"                                          } },
    {AT_CMS_SC_SYSTEM_FAILURE,                                        { (TAF_UINT8*)"194", (TAF_UINT8*)"SC system failure"                                           } },
    {AT_CMS_INVALID_SME_ADDRESS,                                      { (TAF_UINT8*)"195", (TAF_UINT8*)"Invalid SME address"                                         } },
    {AT_CMS_DESTINATION_SME_BARRED,                                   { (TAF_UINT8*)"196", (TAF_UINT8*)"Destination SME barred"                                      } },
    {AT_CMS_SM_REJECTEDDUPLICATE_SM,                                  { (TAF_UINT8*)"197", (TAF_UINT8*)"SM RejectedDuplicate SM"                                     } },
    {AT_CMS_TPVPF_NOT_SUPPORTED,                                      { (TAF_UINT8*)"198", (TAF_UINT8*)"TPVPF not supported"                                         } },
    {AT_CMS_TPVP_NOT_SUPPORTED,                                       { (TAF_UINT8*)"199", (TAF_UINT8*)"TPVP not supported"                                          } },
    {AT_CMS_SIM_SMS_STORAGE_FULL,                                     { (TAF_UINT8*)"208", (TAF_UINT8*)"(U)SIM SMS storage full"                                     } },
    {AT_CMS_NO_SMS_STORAGE_CAPABILITY_IN_SIM,                         { (TAF_UINT8*)"209", (TAF_UINT8*)"No SMS storage capability in (U)SIM"                         } },
    {AT_CMS_ERROR_IN_MS,                                              { (TAF_UINT8*)"210", (TAF_UINT8*)"Error in MS"                                                 } },
    {AT_CMS_MEMORY_CAPACITY_EXCEEDED,                                 { (TAF_UINT8*)"211", (TAF_UINT8*)"Memory Capacity Exceeded"                                    } },
    {AT_CMS_SIM_APPLICATION_TOOLKIT_BUSY,                             { (TAF_UINT8*)"212", (TAF_UINT8*)"(U)SIM Application Toolkit Busy"                             } },
    {AT_CMS_SIM_DATA_DOWNLOAD_ERROR,                                  { (TAF_UINT8*)"213", (TAF_UINT8*)"(U)SIM data download error"                                  } },
    {AT_CMS_UNSPECIFIED_ERROR_CAUSE,                                  { (TAF_UINT8*)"255", (TAF_UINT8*)"Unspecified error cause"                                     } },

    {AT_CMS_ME_FAILURE,                                               { (TAF_UINT8*)"300", (TAF_UINT8*)"ME failure"                                                  } },
    {AT_CMS_SMS_SERVICE_OF_ME_RESERVED,                               { (TAF_UINT8*)"301", (TAF_UINT8*)"SMS service of ME reserved"                                  } },
    {AT_CMS_OPERATION_NOT_ALLOWED,                                    { (TAF_UINT8*)"302", (TAF_UINT8*)"operation not allowed"                                       } },
    {AT_CMS_OPERATION_NOT_SUPPORTED,                                  { (TAF_UINT8*)"303", (TAF_UINT8*)"operation not supported"                                     } },
    {AT_CMS_INVALID_PDU_MODE_PARAMETER,                               { (TAF_UINT8*)"304", (TAF_UINT8*)"304"                                                         } },/*"invalid PDU mode parameter"*/
    {AT_CMS_INVALID_TEXT_MODE_PARAMETER,                              { (TAF_UINT8*)"305", (TAF_UINT8*)"305"                                                         } },/*"invalid text mode parameter"*/
    {AT_CMS_U_SIM_NOT_INSERTED,                                       { (TAF_UINT8*)"310", (TAF_UINT8*)"(U)SIM not inserted"                                         } },
    {AT_CMS_U_SIM_PIN_REQUIRED,                                       { (TAF_UINT8*)"311", (TAF_UINT8*)"(U)SIM PIN required"                                         } },
    {AT_CMS_PH_U_SIM_PIN_REQUIRED,                                    { (TAF_UINT8*)"312", (TAF_UINT8*)"PH-(U)SIM PIN required"                                      } },
    {AT_CMS_U_SIM_FAILURE,                                            { (TAF_UINT8*)"313", (TAF_UINT8*)"313"                                                         } },
    {AT_CMS_U_SIM_BUSY,                                               { (TAF_UINT8*)"314", (TAF_UINT8*)"(U)SIM busy"                                                 } },
    {AT_CMS_U_SIM_WRONG,                                              { (TAF_UINT8*)"315", (TAF_UINT8*)"(U)SIM wrong"                                                } },
    {AT_CMS_U_SIM_PUK_REQUIRED,                                       { (TAF_UINT8*)"316", (TAF_UINT8*)"(U)SIM PUK required"                                         } },
    {AT_CMS_U_SIM_PIN2_REQUIRED,                                      { (TAF_UINT8*)"317", (TAF_UINT8*)"(U)SIM PIN2 required"                                        } },
    {AT_CMS_U_SIM_PUK2_REQUIRED,                                      { (TAF_UINT8*)"318", (TAF_UINT8*)"(U)SIM PUK2 required"                                        } },
    {AT_CMS_MEMORY_FAILURE,                                           { (TAF_UINT8*)"320", (TAF_UINT8*)"memory failure"                                              } },
    {AT_CMS_INVALID_MEMORY_INDEX,                                     { (TAF_UINT8*)"321", (TAF_UINT8*)"invalid memory index"                                        } },
    {AT_CMS_MEMORY_FULL,                                              { (TAF_UINT8*)"322", (TAF_UINT8*)"memory full"                                                 } },
    {AT_CMS_SMSC_ADDRESS_UNKNOWN,                                     { (TAF_UINT8*)"330", (TAF_UINT8*)"330"                                                         } },/*"SMSC address unknown"*/
    {AT_CMS_NO_NETWORK_SERVICE,                                       { (TAF_UINT8*)"331", (TAF_UINT8*)"no network service"                                          } },
    {AT_CMS_NETWORK_TIMEOUT,                                          { (TAF_UINT8*)"332", (TAF_UINT8*)"network timeout"                                             } },
    {AT_CMS_NO_CNMA_ACKNOWLEDGEMENT_EXPECTED,                         { (TAF_UINT8*)"340", (TAF_UINT8*)"no +CNMA acknowledgement expected"                           } },
    {AT_CMS_FDN_DEST_ADDR_FAILED,                                     { (TAF_UINT8*)"341", (TAF_UINT8*)"FDN Failed"                                                  } },
    {AT_CMS_FDN_SERVICE_CENTER_ADDR_FAILED,                           { (TAF_UINT8*)"342", (TAF_UINT8*)"Service Centre Address FDN failed"                           } },
    {AT_CMS_MO_SMS_CONTROL_FAILED,                                    { (TAF_UINT8*)"343", (TAF_UINT8*)"MO SMS Control Failed"                                       } },
    {AT_CMS_UNKNOWN_ERROR,                                            { (TAF_UINT8*)"500", (TAF_UINT8*)"500"                                               } },/*"unknown error"*/

    {AT_CMS_ERROR_ENUM_END,                                           { TAF_NULL_PTR,       TAF_NULL_PTR                          }  },

    {AT_CMOLRE_ERR_ENUM_BEGIN,                                        { VOS_NULL_PTR,       VOS_NULL_PTR                                                            } },
    {AT_CMOLRE_METHOD_NOT_SUPPORTED,                                  { (VOS_UINT8*)"0",    (VOS_UINT8*)"Method not supported"                                      } },
    {AT_CMOLRE_ADDITIONAL_ASSIS_DATA_REQIRED,                         { (VOS_UINT8*)"1",    (VOS_UINT8*)"Additional assistance data required"                       } },
    {AT_CMOLRE_NOT_ENOUGH_SATELLITES,                                 { (VOS_UINT8*)"2",    (VOS_UINT8*)"Not enough satellites"                                     } },
    {AT_CMOLRE_UE_BUSY,                                               { (VOS_UINT8*)"3",    (VOS_UINT8*)"UE busy"                                                   } },
    {AT_CMOLRE_NETWORK_ERROR,                                         { (VOS_UINT8*)"4",    (VOS_UINT8*)"Network error"                                             } },
    {AT_CMOLRE_TOO_MANY_CONNECTIONS,                                  { (VOS_UINT8*)"5",    (VOS_UINT8*)"Failed to open internet connection, too many connections"  } },
    {AT_CMOLRE_TOO_MANY_USERS,                                        { (VOS_UINT8*)"6",    (VOS_UINT8*)"Failed to open internet connection, too many users"        } },
    {AT_CMOLRE_FAILURE_DUE_TO_HANDOVER,                               { (VOS_UINT8*)"7",    (VOS_UINT8*)"Failure due to handover"                                   } },
    {AT_CMOLRE_INTERNET_CONN_FAILURE,                                 { (VOS_UINT8*)"8",    (VOS_UINT8*)"Internet connection failure"                               } },
    {AT_CMOLRE_MEMORY_ERROR,                                          { (VOS_UINT8*)"9",    (VOS_UINT8*)"Memory error"                                              } },
    {AT_CMOLRE_UNKNOWN_ERROR,                                         { (VOS_UINT8*)"255",  (VOS_UINT8*)"Unknown error"                                             } },
    {AT_CMOLRE_ERR_ENUM_END,                                          { VOS_NULL_PTR,       VOS_NULL_PTR                                                            } },

};

/*,CONNECT <Rate>*/
const TAF_CHAR   *g_PppDialRateDisplay[] =
{
    " 9600",
    " 85600",
    " 107000",
    " 236800",
    " 296000",
    " 384000",
    " 3600000",
    " 7200000",
    " 10200000",
    " 14400000",
    " 1800000",
    " 21600000",
    " 28800000",
    " 43200000",
    " 57600000",
    " 86400000"
};

/*,NV*/
const VOS_CHAR   *g_ucDialRateDisplayNv[] =
{
    " 53600",
    " 236800",
    " 384000",
    " 1800000",
    " 3600000",
    " 7200000",
};

/*,NV*/
const AT_DISPLAY_RATE_PAIR_STRU         g_ucLTERateDisplay[AT_UE_LTE_CATEGORY_NUM_MAX] =
{
    {" 1000000",    " 1000000"  },                                              /* category0 */
    {" 10000000",   " 5000000"  },                                              /* category1 */
    {" 50000000",   " 25000000" },                                              /* category2 */
    {" 100000000",  " 50000000" },                                              /* category3 */
    {" 150000000",  " 50000000" },                                              /* category4 */
    {" 300000000",  " 75000000" },                                              /* category5 */
    {" 300000000",  " 50000000" },                                              /* category6 */
    {" 300000000",  " 100000000"},                                              /* category7 */
    {" 3000000000", " 1500000000"},                                             /* category8 */
    {" 450000000",  " 50000000"},                                               /* category9 */
    {" 450000000",  " 100000000"},                                              /* category10 */
    {" 600000000",  " 50000000"},                                               /* category11 */
    {" 600000000",  " 100000000"},                                              /* category12 */
    {" 390000000",  " 150000000"},                                              /* category13 */
    {" 3900000000", " 9500000000"},                                             /* category14 */
    {" 750000000",  " 0"},                                                      /* category15 */
    {" 980000000",  " 0"},                                                      /* category16 */
    {" 25000000000"," 0"},                                                      /* category17 */
};



/*****************************************************************************
   3 
*****************************************************************************/
/* Modified by L60609 for AT Project2011-10-20,  Begin*/
/* Modified by L60609 for AT Project2011-10-20,  Begin*/


/*****************************************************************************
   4 
*****************************************************************************/

/*****************************************************************************
 Prototype      : At_SendData
 Description    :
 Input          : ---
 Output         : ---
 Return Value   : AT_SUCCESS --- 
                  AT_FAILURE --- 
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
  2.     : 2007-03-27
         : h59254
     : :A32D09820(PC-Lint)
  3.       : 2011103
           : /l60609
       : AT Project: DRV/DMS
  4.       : 20111019
           : S62952
       : AT Project: modem
  5.       : 20120214
           : l00171473
       : DTS2012021405602,AT_APP_SOCK_PORT_NOAT
  6.       : 2012224
           : L47619
       : V7R1C50 IPC:HSIC AT
  7.       : 201286
           : l60609
       : MUXmux
  8.       : 20121129
           : l00227485
       : DSDA PHASE1, VCOM
  9.       : 20130313
           : z00214637
       : BodySAR
 10.       : 20130527
           : f00179208
       : V3R3 PPP PROJECT
 11.       : 2015527
           : l00198894
       : TSTS
*****************************************************************************/
TAF_UINT32 At_SendData(TAF_UINT8 ucIndex,TAF_UINT8 ucType,TAF_UINT8* pData,TAF_UINT16 usLen)
{

    /* Added by L60609 for MUX2012-08-06,  Begin */
    VOS_UINT32                          ulHsicUserFlg;
    VOS_UINT32                          ulMuxUserFlg;
    /* Added by L60609 for MUX2012-08-06,  End */

    /* Added by L60609 for MUX2012-08-06,  Begin */
    ulHsicUserFlg = AT_CheckHsicUser(ucIndex);
    ulMuxUserFlg  = AT_CheckMuxUser(ucIndex);
    /* Added by L60609 for MUX2012-08-06,  End */

    /*   */
    /*  */
    if (AT_MAX_CLIENT_NUM <= ucIndex)
    {
        return AT_FAILURE;
    }
    if ( (AT_CLIENT_USED != gastAtClientTab[ucIndex].ucUsed)
      || (AT_DATA_BUTT_MODE == gastAtClientTab[ucIndex].DataMode))
    {
        return AT_FAILURE;
    }
    if (ucType != gastAtClientTab[ucIndex].DataMode)
    {
        return AT_FAILURE;
    }

/* Added by S62952 for IPV6, 2011-07-19, begin */

    if (AT_DATA_STOP_STATE == gastAtClientTab[ucIndex].DataState)
    {
        return AT_FAILURE;
    }

    if (AT_DATA_MODE != gastAtClientTab[ucIndex].Mode)
    {
        return AT_FAILURE;
    }
    else
    {
        if (AT_USBCOM_USER == gastAtClientTab[ucIndex].UserType)
        {
            /*USB COM*/
            /* Modified by L60609 for AT Project2011-10-15,  Begin*/
            DMS_COM_SEND(AT_USB_COM_PORT_NO, pData, usLen);
            AT_MNTN_TraceCmdResult(ucIndex, pData, usLen);
            /* Modified by L60609 for AT Project2011-10-15,  End*/
            return AT_SUCCESS;
        }
        /* VCOM */
        else if (AT_APP_USER == gastAtClientTab[ucIndex].UserType)
        {
            /* Modified by L60609 for AT Project2011-10-18,  Begin*/
            /* Modified by l00227485 for DSDA Phase I2012-11-28, Begin */
            APP_VCOM_Send(gastAtClientTab[ucIndex].ucPortNo, pData, usLen);
            /* Modified by l00227485 for DSDA Phase I2012-11-28, End */
            return AT_SUCCESS;
            /* Modified by L60609 for AT Project2011-10-18,  End*/
        }
        else if (AT_SOCK_USER == gastAtClientTab[ucIndex].UserType)
        {
            /* Modified by L60609 for AT Project2011-10-18,  Begin*/
            if (BSP_MODULE_SUPPORT == mdrv_misc_support_check(BSP_MODULE_TYPE_WIFI))
            {
                CPM_ComSend(CPM_AT_COMM, pData, VOS_NULL_PTR, usLen);
                return AT_SUCCESS;
            }
            /* Modified by L60609 for AT Project2011-10-18,  End*/
         }
        else if (AT_CTR_USER == gastAtClientTab[ucIndex].UserType)
        {

            DMS_COM_SEND(AT_CTR_PORT_NO, pData, usLen );
            AT_MNTN_TraceCmdResult(ucIndex, pData, usLen);
            return AT_SUCCESS;
        }
        else if (AT_PCUI2_USER == gastAtClientTab[ucIndex].UserType)
        {
            DMS_COM_SEND(AT_PCUI2_PORT_NO, pData, usLen );
            AT_MNTN_TraceCmdResult(ucIndex, pData, usLen);
            return AT_SUCCESS;
        }
        /* Modified by s62952 for BalongV300R002 Build 2012-02-28, begin */
        else if (AT_MODEM_USER == gastAtClientTab[ucIndex].UserType)
        {
            /* Modified by S62952 for AT Project2011-10-18,  Begin*/
            return AT_SendDataToModem(ucIndex, pData, usLen);
            /* Modified by S62952 for AT Project2011-10-18,  END*/
        }
        /* Modified by s62952 for BalongV300R002 Build 2012-02-28, end */
        else if (AT_NDIS_USER == gastAtClientTab[ucIndex].UserType)
        {
            /* NDIS AT,,3AT_FAILURE */
            return AT_FAILURE;
        }
        /* Modified by L60609 for MUX2012-08-13,  Begin */
        else if (VOS_TRUE == ulHsicUserFlg)
        /* Modified by L60609 for MUX2012-08-13,  End */
        {
/* Added by j00174725 for V3R3 Cut Out Memory2013-11-07,  Begin */
/* Added by j00174725 for V3R3 Cut Out Memory2013-11-07,  End */
        }
        /* Added by L60609 for MUX2012-08-06,  Begin */
        else if (VOS_TRUE == ulMuxUserFlg)
        {
            return AT_SendMuxResultData(ucIndex, pData, usLen);
        }
        /* Added by L60609 for MUX2012-08-06,  End */
        else
        {
            return AT_FAILURE;
        }
        return AT_FAILURE;
    }
 /* Added by S62952 for IPV6, 2011-07-19, end */
}



/*****************************************************************************
     : AT_DisplayResultData
   : TafAT
   : TAF_UINT16  usLen 
             TAF_UINT8   ucIndex 
   : 
     : 
   :
   :

       :
  1.       : 2010310
           : s62952
       : 

  2.       : 20110224
           : A00165503
       : : DTS2011022404828MODEMAT

  3.       : 2011103
           : /l60609
       : AT Project: DRV_COM_SEND
  4.       : 20111019
           : S62952
       : AT Project: modem
  5.       : 2011127
           :  l00171473
       : DTS2011120801675UART
  6.       : 20120214
           : l00171473
       : DTS2012021405602,AT_APP_SOCK_PORT_NOAT
  7.       : 20120224
           : w00181244
       : DTS2012021305344,PCUI/control/FEATURE_NDIS
  8.       : 2012224
           : L47619
       : V7R1C50 IPC:HSIC ATAT
  9.       : 201286
           : l60609
       : MUXmux
 10.       : 20121129
           : l00227485
       : DSDA PHASE1, VCOM
 11.       : 20121211
           : l00167671
       : DTS2012121802573, TQE
 12.       : 20130313
           : z00214637
       : BodySAR
 13.       : 20130527
           : f00179208
       : V3R3 PPP PROJECT
 14.       : 2013925
           : j00174725
       : UART-MODEM: HSUART
*****************************************************************************/
VOS_VOID  AT_DisplayResultData (
    VOS_UINT8                           ucIndex,
    VOS_UINT16                          usLen
)
{

    /* Added by L60609 for MUX2012-08-06,  Begin */
    VOS_UINT32                          ulHsicUserFlg;
    VOS_UINT32                          ulMuxUserFlg;
    /* Added by L60609 for MUX2012-08-06,  End */

    /* Added by L60609 for MUX2012-08-06,  Begin */
    ulHsicUserFlg = AT_CheckHsicUser(ucIndex);
    ulMuxUserFlg  = AT_CheckMuxUser(ucIndex);
    /* Added by L60609 for MUX2012-08-06,  End */

    /**/
    if (AT_DATA_START_STATE == gastAtClientTab[ucIndex].DataState)
    {
        AT_LOG1("At_SendResultData DataState:",gastAtClientTab[ucIndex].DataState);
        return;
    }

    if ((AT_DATA_STOP_STATE == gastAtClientTab[ucIndex].DataState)
        && (AT_DATA_MODE == gastAtClientTab[ucIndex].Mode))
    {
        gastAtClientTab[ucIndex].DataState = AT_DATA_START_STATE;
    }

    /*PCUI*/
    if (AT_USBCOM_USER == gastAtClientTab[ucIndex].UserType)
    {
        /*USB COM*/
        DMS_COM_SEND(AT_USB_COM_PORT_NO, gstAtSendDataBuffer, usLen);
    }

    /*control*/
    else if (AT_CTR_USER == gastAtClientTab[ucIndex].UserType)
    {

        DMS_COM_SEND(AT_CTR_PORT_NO, gstAtSendDataBuffer, usLen);
    }
    else if (AT_PCUI2_USER == gastAtClientTab[ucIndex].UserType)
    {
        DMS_COM_SEND(AT_PCUI2_PORT_NO, gstAtSendDataBuffer, usLen);
    }
    /* Modified by s62952 for BalongV300R002 Build 2012-02-28, begin */
    /*MODEM*/
    else if (AT_MODEM_USER == gastAtClientTab[ucIndex].UserType)
    {
        AT_SendDataToModem(ucIndex, gstAtSendDataBuffer, usLen);
    }
    /* Modified by s62952 for BalongV300R002 Build 2012-02-28, end */
    else if (AT_APP_USER == gastAtClientTab[ucIndex].UserType)
    {
        /* Modified by l00227485 for DSDA Phase I2012-11-28, Begin */
        APP_VCOM_Send(gastAtClientTab[ucIndex].ucPortNo, gstAtSendDataBuffer, usLen);
        /* Modified by l00227485 for DSDA Phase I2012-11-28, End */
    }
    else if (AT_SOCK_USER == gastAtClientTab[ucIndex].UserType)
    {
        if (BSP_MODULE_SUPPORT == mdrv_misc_support_check(BSP_MODULE_TYPE_WIFI))
        {
            CPM_ComSend(CPM_AT_COMM, gstAtSendDataBuffer, VOS_NULL_PTR, usLen);
        }
    }
    else if (AT_NDIS_USER == gastAtClientTab[ucIndex].UserType)
    {
        DMS_COM_SEND(AT_NDIS_PORT_NO, gstAtSendDataBuffer, usLen);
    }
    else if(AT_UART_USER == gastAtClientTab[ucIndex].UserType)
    {
        AT_UART_SendDlData(ucIndex, gstAtSendDataBuffer, usLen);
    }
    /* Modified by L60609 for MUX2012-08-13,  Begin */
    else if(VOS_TRUE == ulHsicUserFlg)
    /* Modified by L60609 for MUX2012-08-13,  End */
    {
        /* Added by j00174725 for V3R3 Cut Out Memory2013-11-07,  Begin */
        /* Added by j00174725 for V3R3 Cut Out Memory2013-11-07,  End */
    }
    /* Added by L60609 for MUX2012-08-06,  Begin */
    else if (VOS_TRUE == ulMuxUserFlg)
    {
        AT_SendMuxResultData(ucIndex, gstAtSendDataBuffer, usLen);
    }
    /* Added by L60609 for MUX2012-08-06,  End */
    else
    {
        ;
    }

    return;
}

/*****************************************************************************
     : AT_DisplaySelResultData
   : TafAT
   : TAF_UINT16  usLen 
             TAF_UINT8   ucIndex 
   : 
     : 
   :
   :

       :
  1.       : 2010310
           : s62952
       : 

  2.       : 20110224
           : A00165503
       : : DTS2011022404828MODEMAT

  3.       : 2011103
           : /l60609
       : AT Project: DRV_COM_SENDAT_USB_COM_PORT_NO
  4.       : 20111019
           : S62952
       : AT Project: modem
  5.       : 20120214
           : l00171473
       : DTS2012021405602,AT_APP_SOCK_PORT_NOAT
  6.       : 20120224
           : w00181244
       : DTS2012021305344,PCUI/control/FEATURE_NDIS,ctrl
  7.       : 2012224
           : L47619
       : V7R1C50 IPC:HSIC ATAT
  8.       : 201286
           : l60609
       : MUXmux
  9.       : 20121129
           : l00227485
       : DSDA PHASE1, VCOM
 10.      : 20130313
          : z00214637
      : BodySAR
 11.       : 20130527
           : f00179208
       : V3R3 PPP PROJECT
 12.       : 2013925
           : j00174725
       : UART-MODEM: HSUART
 13.       : 2015527
           : l00198894
       : TSTS
*****************************************************************************/
VOS_VOID AT_DisplaySelResultData(
    VOS_UINT16                          usLen,
    VOS_UINT8                           ucIndex
)
{
    VOS_UINT8                           ucLoop;
    /* Added by L60609 for MUX2012-08-06,  Begin */
    VOS_UINT32                          ulHsicUserFlg;
    VOS_UINT32                          ulMuxUserFlg;
    /* Added by L60609 for MUX2012-08-06,  End */

    /* Added by L60609 for MUX2012-08-06,  Begin */
    ulHsicUserFlg = AT_CheckHsicUser(ucIndex);
    ulMuxUserFlg  = AT_CheckMuxUser(ucIndex);
    /* Added by L60609 for MUX2012-08-06,  End */

    /* Added by S62952 for IPV6, 2011-07-19, begin */

    if ( (AT_CMD_MODE == gastAtClientTab[ucIndex].Mode)
      || (AT_ONLINE_CMD_MODE == gastAtClientTab[ucIndex].Mode) )
    {
        if (AT_USBCOM_USER == gastAtClientTab[ucIndex].UserType)
        {
            /* PCUI */
            if (0 == gucAtPortSel)
            {
                DMS_COM_SEND(AT_USB_COM_PORT_NO, gstAtSendDataBuffer, usLen);
            }
        }
        else if (AT_CTR_USER == gastAtClientTab[ucIndex].UserType)
        {

             /* control */
            if (0 == gucAtPortSel)
            {
                DMS_COM_SEND(AT_CTR_PORT_NO, gstAtSendDataBuffer, usLen);
            }
        }
        else if (AT_PCUI2_USER == gastAtClientTab[ucIndex].UserType)
        {
             /* PCUI2 */
            if (0 == gucAtPortSel)
            {
                DMS_COM_SEND(AT_PCUI2_PORT_NO, gstAtSendDataBuffer, usLen);
            }
        }
        else if (AT_MODEM_USER == gastAtClientTab[ucIndex].UserType)
        {
            /* modem */
            if (1 == gucAtPortSel)
            {
                /* Modified by S62952 for AT Project2011-10-18,  Begin*/
                AT_SendDataToModem(ucIndex, gstAtSendDataBuffer, usLen);
                /* Modified by S62952 for AT Project2011-10-18,  END*/
            }
        }
        else if (AT_APP_USER == gastAtClientTab[ucIndex].UserType)
        {
            /* Modified by L60609 for AT Project2011-10-18,  Begin*/
            /* Modified by l00227485 for DSDA Phase I2012-11-28, Begin */
            APP_VCOM_Send(gastAtClientTab[ucIndex].ucPortNo, gstAtSendDataBuffer, usLen);
            /* Modified by l00227485 for DSDA Phase I2012-11-28, End */
            /* Modified by L60609 for AT Project2011-10-18,  end*/
        }
        else if (AT_SOCK_USER == gastAtClientTab[ucIndex].UserType)
        {
            if (BSP_MODULE_SUPPORT == mdrv_misc_support_check(BSP_MODULE_TYPE_WIFI))
            {
            /* Modified by L60609 for AT Project2011-10-18,  Begin*/
                CPM_ComSend(CPM_AT_COMM, gstAtSendDataBuffer, VOS_NULL_PTR, usLen);
            /* Modified by L60609 for AT Project2011-10-18,  End*/
            }
        }
        else if (AT_NDIS_USER == gastAtClientTab[ucIndex].UserType)
        {
            DMS_COM_SEND(AT_NDIS_PORT_NO,gstAtSendDataBuffer, (VOS_UINT32)usLen);
        }
        /* Modified by L60609 for MUX2012-08-13,  Begin */
        else if (VOS_TRUE == ulHsicUserFlg)
        /* Modified by L60609 for MUX2012-08-13,  End */
        {
            /* HSIC ATAT */
            for (ucLoop = 0; ucLoop < AT_HSIC_AT_CHANNEL_MAX; ucLoop++)
            {
/* Added by j00174725 for V3R3 Cut Out Memory2013-11-07,  Begin */
/* Added by j00174725 for V3R3 Cut Out Memory2013-11-07,  End */
            }
        }
        /* Added by L60609 for MUX2012-08-06,  Begin */
        else if (VOS_TRUE == ulMuxUserFlg)
        {
            AT_SendMuxSelResultData(ucIndex, gstAtSendDataBuffer, usLen);
        }
        /* Added by L60609 for MUX2012-08-06,  End */
        else
        {
            ;
        }
    }
    /* Added by S62952 for IPV6, 2011-07-19, end */
    return;
}

/*****************************************************************************
     : At_BufferorSendResultData
   : AT
   : VOS_UINT8  ucIndex     
             VOS_UINT8  *pucData    
             VOS_UINT16 usLength    
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20101220
           : /f62575
       : 
  2.       : 20130506
           : f62575
       : SS FDN&Call Control+COPN
  3.       : 20140115
           : f62575
       : DTS2014011301359+CPOL37UPLMN
*****************************************************************************/
VOS_VOID At_BufferorSendResultData(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                          *pucData,
    VOS_UINT16                          usLength
)
{
    VOS_UINT32                          ulBufferLength;
    VOS_UINT8                          *pBuffer;

    if (0 == usLength)
    {
        return;
    }

    ulBufferLength = gstAtCombineSendData[ucIndex].usBufLen + usLength;

    /*  */
    /* Modified by f62575 for SS FDN&Call Control, 2013-05-06, begin */
    if (ulBufferLength > AT_CMD_OUTPUT_MAX_LEN)
    /* Modified by f62575 for SS FDN&Call Control, 2013-05-06, end */
    {
        At_SendResultData(ucIndex,
                          gstAtCombineSendData[ucIndex].aucBuffer,
                          gstAtCombineSendData[ucIndex].usBufLen);
        gstAtCombineSendData[ucIndex].usBufLen = 0;
    }

    /*  */
    pBuffer = gstAtCombineSendData[ucIndex].aucBuffer + gstAtCombineSendData[ucIndex].usBufLen;
    TAF_MEM_CPY_S(pBuffer, AT_CMD_MAX_LEN + 20 - gstAtCombineSendData[ucIndex].usBufLen, pucData, usLength);
    gstAtCombineSendData[ucIndex].usBufLen += usLength;

    return;
}

/*****************************************************************************
     : AT_SendBroadCastResultData
   : 
   : VOS_UINT8                           ucIndex
             VOS_UINT8                          *pData
             VOS_UINT16                          usLen
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20121217
           : l60609
       : 

  2.       : 2015527
           : l00198894
       : TSTS
*****************************************************************************/
VOS_VOID AT_SendBroadCastResultData(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                          *pData,
    VOS_UINT16                          usLen
)
{
    VOS_UINT8                           ucCount;
    MODEM_ID_ENUM_UINT16                enBroadCastModemId;
    MODEM_ID_ENUM_UINT16                enCurModemId;
    VOS_UINT32                          ulRslt;
    AT_CLIENT_CTX_STRU                 *pstAtClientCtx = VOS_NULL_PTR;

    enCurModemId = MODEM_ID_0;

    switch (ucIndex)
    {
        case AT_BROADCAST_CLIENT_INDEX_MODEM_0:
            enBroadCastModemId = MODEM_ID_0;
            break;
        case AT_BROADCAST_CLIENT_INDEX_MODEM_1:
            enBroadCastModemId = MODEM_ID_1;
            break;
        case AT_BROADCAST_CLIENT_INDEX_MODEM_2:
            enBroadCastModemId = MODEM_ID_2;
            break;
        default:
            enBroadCastModemId = MODEM_ID_0;
            break;
    }

    for (ucCount = 0; ucCount < AT_MAX_CLIENT_NUM; ucCount++ )
    {
        /* Modified by l60609 for DSDA Phase III, 2013-2-21, Begin */
        pstAtClientCtx = AT_GetClientCtxAddr(ucCount);
        /* Modified by l60609 for DSDA Phase III, 2013-2-21, End */

        /*  */
        if (AT_CLIENT_NULL == gastAtClientTab[ucCount].ucUsed)
        {
            continue;
        }

        /*  */
        if (VOS_FALSE == pstAtClientCtx->stClientConfiguration.ucReportFlg)
        {
            continue;
        }

        ulRslt = AT_GetModemIdFromClient(ucCount, &enCurModemId);

        if (VOS_OK != ulRslt)
        {
            continue;
        }

        /* Modem */
        if (enBroadCastModemId != enCurModemId)
        {
            continue;
        }

        if (AT_IND_MODE == gastAtClientTab[ucCount].IndMode)
        {
            /*4*/
            TAF_MEM_CPY_S(gstAtSendDataBuffer, AT_CMD_MAX_LEN, pData, usLen);
            AT_DisplaySelResultData(usLen, ucCount);
        }
    }

}

/*****************************************************************************
 Prototype      : At_SendResultData
 Description    : TafATAPP
 Input          : ucIndex --- 
                  pData   --- 
                  usLen   --- 
 Output         : ---
 Return Value   : ---
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
  2.       : 2007-03-27
           : h59254
       : :A32D09820(PC-Lint)
  3.       : 2010330
           : s62952
       : AT2D18046
  4.       : 2012823
           : z60575
       : ATDTS2012081501160
  5.       : 20121208
           : f62575
       : DTS2012110804140ATATOK
  6.       : 20121227
           : l60609
       : DSDA Phase II

  7.       : 20131228
           : j00174725
       : HSUART PHASE III

*****************************************************************************/
VOS_VOID At_SendResultData(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                          *pData,
    VOS_UINT16                          usLen
)
{
    gstAtSendData.usBufLen = 0;

    /*  */
    if ((0 == usLen) || (AT_CMD_MAX_LEN <= usLen))
    {
        AT_LOG1("At_SendResultData usLen:",usLen);
        return;
    }

    pData[usLen] = 0;
    AT_INFO_LOG((TAF_CHAR *)pData);
    AT_LOG1("At_SendResultData:",usLen);


        /* ucIndex */
    AT_MNTN_TraceCmdResult(ucIndex, pData, usLen);

    /* Modified by l60609 for DSDA Phase II, 2012-12-17, Begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_SendBroadCastResultData(ucIndex, pData, usLen);
        AT_MNTN_TraceRPTPORT();
    }
    /* Modified by l60609 for DSDA Phase II, 2012-12-17, End */
    else
    {
        if (AT_MAX_CLIENT_NUM <= ucIndex)
        {
            AT_LOG1("At_SendResultData ucIndex:",ucIndex);
            return;
        }

        /* :  */
        if (AT_CLIENT_NULL == gastAtClientTab[ucIndex].ucUsed)
        {
            AT_LOG1("At_SendResultData ucUsed:",gastAtClientTab[ucIndex].ucUsed);
            AT_ParseCmdOver(ucIndex);
            return;
        }

        /*4*/
        TAF_MEM_CPY_S(gstAtSendDataBuffer, AT_CMD_MAX_LEN, pData, usLen);

        AT_DisplayResultData(ucIndex, usLen);

        /* Flash ,flash */
        if (VOS_FALSE == AT_IsClientBlock())
        {
            AT_FlushSmsIndication();
        }
    }

    return;
}

/*****************************************************************************
 Prototype      : At_JudgeCombineCmdSubSequentProcess
 Description    : 
                  1.
                  2.
                    
                  3.
 Input          : ucIndex    --- 
                  ReturnCode --- 
 Output         : TAF_UINT32
 Return Value   : ---
 Calls          : ---
 Called By      : At_FormatResultData

 History        : ---
  1.Date        : 2009-05-30
    Author      : L47619
    Modification: Created function
*****************************************************************************/
TAF_UINT32  At_JudgeCombineCmdSubSequentProcess(TAF_UINT8 ucIndex, TAF_UINT32 ReturnCode)
{
    /*  */
    if (g_stParseContext[ucIndex].stCombineCmdInfo.usTotalNum == 0)
    {
        /* :
            1.
            2.AT(AT)
         */
        return AT_COM_CMD_SUB_PROC_FINISH;
    }

    /* AT */
    if ((g_stParseContext[ucIndex].stCombineCmdInfo.usProcNum + 1) == g_stParseContext[ucIndex].stCombineCmdInfo.usTotalNum)
    {
        return AT_COM_CMD_SUB_PROC_FINISH;
    }

    if (AT_SUCCESS == ReturnCode)
    {
        return AT_COM_CMD_SUB_PROC_CONTINUE;
    }
    else if (AT_FAILURE == ReturnCode)
    {
        return AT_COM_CMD_SUB_PROC_ABORT;
    }
    else if ((AT_CME_ERROR_ENUM_BEGAIN < ReturnCode) && (ReturnCode < AT_CME_ERROR_ENUM_END))
    {
        return AT_COM_CMD_SUB_PROC_ABORT;
    }
    else if ((AT_CMS_ERROR_ENUM_BEGAIN < ReturnCode) && (ReturnCode < AT_CMS_ERROR_ENUM_END))
    {
        return AT_COM_CMD_SUB_PROC_ABORT;
    }
    else if (AT_CMD_NOT_SUPPORT == ReturnCode)
    {
        return AT_COM_CMD_SUB_PROC_ABORT;
    }
    else if (AT_TOO_MANY_PARA == ReturnCode)
    {
        return AT_COM_CMD_SUB_PROC_ABORT;
    }
    else if (AT_TOO_MANY_PARA <= ReturnCode)
    {
        return AT_COM_CMD_SUB_PROC_ABORT;
    }
    else if (AT_OK == ReturnCode)
    {
        return AT_COM_CMD_SUB_PROC_CONTINUE;
    }
    else if (AT_CONNECT == ReturnCode)
    {
        return AT_COM_CMD_SUB_PROC_ABORT;
    }
    else if (AT_RING == ReturnCode)
    {
        return AT_COM_CMD_SUB_PROC_ABORT;
    }
    else if (AT_NO_CARRIER == ReturnCode)
    {
        return AT_COM_CMD_SUB_PROC_ABORT;
    }
    else if (AT_ERROR == ReturnCode)
    {
        return AT_COM_CMD_SUB_PROC_ABORT;
    }
    else if (AT_NO_DIALTONE == ReturnCode)
    {
        return AT_COM_CMD_SUB_PROC_ABORT;
    }
    else if (AT_BUSY == ReturnCode)
    {
        return AT_COM_CMD_SUB_PROC_ABORT;
    }
    else if (AT_NO_ANSWER == ReturnCode)
    {
        return AT_COM_CMD_SUB_PROC_ABORT;
    }
    else
    {
        return AT_COM_CMD_SUB_PROC_CONTINUE;
    }

}


/*****************************************************************************
     : AT_GetReturnCodeId
   : gastAtReturnCodeTabindex
   : VOS_UINT32                          ulReturnCode
             VOS_UINT32                         *pulIndex
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 20111024
           : /l60609
       : 

*****************************************************************************/
VOS_UINT32 AT_GetReturnCodeId(
    VOS_UINT32                          ulReturnCode,
    VOS_UINT32                         *pulIndex
)
{
    VOS_UINT32                          i;

    for (i = 0; i < sizeof(gastAtReturnCodeTab)/sizeof(gastAtReturnCodeTab[0]); i++)
    {
        if (ulReturnCode == gastAtReturnCodeTab[i].ucIndex)
        {
            *pulIndex = i;
            return VOS_OK;
        }
    }

    AT_ERR_LOG("AT_GetResultDataId, ReturnCode is out of gastAtReturnCodeTab!");
    return VOS_ERR;
}

/*****************************************************************************
     : AT_FormatAtCmdNotSupportResult
   : AT_CMD_NOT_SUPPORT 
   : enReturnCode
   : 
     : 
   :
   :

       :
  1.       : 20120924
           : l00171473
       :  for V7R1C50_At_Abort, 

*****************************************************************************/
VOS_VOID AT_FormatAtCmdNotSupportResult(
    VOS_UINT8                           ucIndex,
    AT_RRETURN_CODE_ENUM_UINT32         enReturnCode
)
{
    VOS_UINT16                          usLength;
    VOS_UINT8                          *pucDataAt;
    VOS_UINT32                          ulTmp;

    usLength  = 0;
    ulTmp     = 0;

    pucDataAt = pgucAtSndCodeAddr;

    TAF_MEM_CPY_S((pucDataAt + usLength),
        2,
        (VOS_CHAR *)gaucAtCrLf,
        2);
    usLength += 2;

    ulTmp = VOS_StrLen((VOS_CHAR *)gaucAtCmdNotSupportStr);
    TAF_MEM_CPY_S((pucDataAt + usLength),
        ulTmp,
        (VOS_CHAR *)gaucAtCmdNotSupportStr,
        ulTmp );
    usLength += (VOS_UINT16)ulTmp;

    TAF_MEM_CPY_S((pucDataAt + usLength),
        2,
        (VOS_CHAR *)gaucAtCrLf,
        2);
    usLength += 2;

    if ( (AT_CMD_MAX_LEN + 20) >= (gstAtCombineSendData[ucIndex].usBufLen + usLength) )
    {
        TAF_MEM_CPY_S((gstAtCombineSendData[ucIndex].aucBuffer + gstAtCombineSendData[ucIndex].usBufLen),
                    usLength,
                    pucDataAt,
                    usLength);
        gstAtCombineSendData[ucIndex].usBufLen += usLength;
    }

    At_SendResultData(ucIndex, gstAtCombineSendData[ucIndex].aucBuffer, gstAtCombineSendData[ucIndex].usBufLen);

}

/*****************************************************************************
     : AT_FormatAtTooManyParaResult
   : AT_TOO_MANY_PARA 
   : enReturnCode
   : 
     : 
   :
   :

       :
  1.       : 20120924
           : l00171473
       :  for V7R1C50_At_Abort, 

*****************************************************************************/
VOS_VOID AT_FormatAtTooManyParaResult(
    VOS_UINT8                           ucIndex,
    AT_RRETURN_CODE_ENUM_UINT32         enReturnCode
)
{
    VOS_UINT16                          usLength;
    VOS_UINT8                          *pucDataAt;
    VOS_UINT32                          ulTmp;

    usLength  = 0;
    ulTmp     = 0;

    pucDataAt = pgucAtSndCodeAddr;

    TAF_MEM_CPY_S((pucDataAt + usLength),
        2,
        (VOS_CHAR *)gaucAtCrLf,
        2);
    usLength += 2;

    ulTmp = VOS_StrLen((VOS_CHAR *)gaucAtTooManyParaStr);
    TAF_MEM_CPY_S( (pucDataAt + usLength),
        ulTmp,
        (VOS_CHAR *)gaucAtTooManyParaStr,
        ulTmp );
    usLength += (VOS_UINT16)ulTmp;

    TAF_MEM_CPY_S((pucDataAt + usLength),
        2,
        (VOS_CHAR *)gaucAtCrLf,
        2);
    usLength += 2;

    if ((AT_CMD_MAX_LEN + 20) >= (gstAtCombineSendData[ucIndex].usBufLen + usLength))
    {
        TAF_MEM_CPY_S((gstAtCombineSendData[ucIndex].aucBuffer + gstAtCombineSendData[ucIndex].usBufLen),
                    usLength,
                    pucDataAt,
                    usLength);
        gstAtCombineSendData[ucIndex].usBufLen += usLength;
    }

    At_SendResultData(ucIndex, gstAtCombineSendData[ucIndex].aucBuffer, gstAtCombineSendData[ucIndex].usBufLen);

    return;
}

/*****************************************************************************
     : AT_FormatAtAbortResult
   : AT_ABORT 
   : ucIndex:
              enReturnCode:
   : 
     : 
   :
   :

       :
  1.       : 20120924
           : l00171473
       :  for V7R1C50_At_Abort, 

*****************************************************************************/
VOS_VOID AT_FormatAtAbortResult(
    VOS_UINT8                           ucIndex,
    AT_RRETURN_CODE_ENUM_UINT32         enReturnCode
)
{
    VOS_UINT16                          usLength;
    VOS_UINT8                          *pucDataAt;
    VOS_UINT32                          ulTmp;

    usLength  = 0;
    ulTmp     = 0;

    pucDataAt = pgucAtSndCodeAddr;

    TAF_MEM_CPY_S((pucDataAt + usLength),
        2,
        (VOS_CHAR *)gaucAtCrLf,
        2);
    usLength += 2;

    /*  */
    ulTmp = VOS_StrLen((VOS_CHAR *)AT_GetAbortRspStr());
    TAF_MEM_CPY_S( (pucDataAt + usLength),
        ulTmp,
        (VOS_CHAR *)AT_GetAbortRspStr(),
        ulTmp );
    usLength += (VOS_UINT16)ulTmp;

    /*  */
    TAF_MEM_CPY_S((pucDataAt + usLength),
        2,
        (VOS_CHAR *)gaucAtCrLf,
        2);
    usLength += 2;

    /*  */
    if ((AT_CMD_MAX_LEN + 20) >= (gstAtCombineSendData[ucIndex].usBufLen + usLength))
    {
        TAF_MEM_CPY_S((gstAtCombineSendData[ucIndex].aucBuffer + gstAtCombineSendData[ucIndex].usBufLen),
                    usLength,
                    pucDataAt,
                    usLength);
        gstAtCombineSendData[ucIndex].usBufLen += usLength;
    }

    /* ATAPP */
    At_SendResultData(ucIndex, gstAtCombineSendData[ucIndex].aucBuffer, gstAtCombineSendData[ucIndex].usBufLen);

    return;
}


/*****************************************************************************
     : At_FormatResultData
   : V,+CMEE,
   : VOS_UINT8                           ucIndex
             VOS_UINT32                          ulReturnCode
   : 
     : VOS_VOID
   :
   :

       :
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
  2.     : 2007-03-27
         : h59254
     : :A32D09820(PC-Lint)
  3.       : 20081030
           : l00130025
       : AT2D07005,AT
  4.       : 20100925
           : z00161729
      : DTS2010091901225,ATVPAT
  5.       : 2011720
           : /f62575
       : DTS2011063000712 
  6.       : 20111022
           : f62575
       : AT PROJECT NAS_EventReport -> AT_EventReport
  7.       : 20111027
           : f62575
       : AT PROJECT gstAtSendData.usBufLen
  8.       : 20120627
           : y00213812
       : V7R1C50 A-GPSXML
  9.       : 2012919
           : l00171473
       : for V7R1C50_At_Abort,  AT_ABORT
 10.       : 2012919
           : s00217060
       : ATC
 11.       : 20130921
           : j00174725
       : UART-MODEM: UARTPPP
 12.       : 2015410
           : h00313353
       : SysCfg
 13.       : 20151226
           : f00179208
       : Coverity
 14.       : 20151117
           : zwx247453
       : dallas gps
 15.       : 2016830
           : A00165503
       : DTS2016060307279: PPP
 16.       : 2016123
           : A00165503
       : DTS2016070404601:, PPP
*****************************************************************************/
VOS_VOID At_FormatResultData(
    VOS_UINT8                           ucIndex,
    VOS_UINT32                          ulReturnCode
)
{
    VOS_UINT32                          ulTmp;
    VOS_UINT16                          usLength;
    VOS_UINT8                          *pDataAt1;
    VOS_UINT8                          *pDataAt3;
    VOS_UINT32                          ulMdmMscFlg;

    VOS_UINT32                          ulComCmdSubProc;
    /* TAF_UINT32                          ulResult; */
    VOS_UINT32                          ulNvDialRateIndex;
    VOS_UINT8                           ucSubSysMode;
    VOS_UINT8                           aucDialRateTmp[AT_AP_RATE_STRLEN];
    /* Added by L60609 for AT Project2011-10-24,  Begin*/
    VOS_UINT32                          ulReturnCodeIndex;
    VOS_UINT32                          ulRslt;
    /*AT_ERRORindex*/
    VOS_UINT32                          ulAtErrIndex;
    VOS_UINT32                          ulAtErrRslt;

    /* Added by s00217060 for ATC, 2013-4-2, begin */
    TAF_AGENT_SYS_MODE_STRU             stSysMode;
    VOS_UINT32                          ulRet;
    /* Added by s00217060 for ATC, 2013-4-2, end */

    VOS_UINT8                           ucDlCategoryIndex = 0;

    /**/
    usLength               = gstAtSendData.usBufLen;
    gstAtSendData.usBufLen = 0;

    ulTmp                  = 0;
    pDataAt1               = pgucAtSndCrLfAddr;
    pDataAt3               = pgucAtSndCodeAddr;
    ulMdmMscFlg            = VOS_FALSE;
    ulRslt                 = VOS_ERR;

    ulAtErrIndex           = 0;
    ulReturnCodeIndex      = 0;
    /* Added by L60609 for AT Project2011-10-24,  End*/

    TAF_MEM_SET_S(aucDialRateTmp, sizeof(aucDialRateTmp), 0x00, sizeof(aucDialRateTmp));

    ulComCmdSubProc = At_JudgeCombineCmdSubSequentProcess(ucIndex, ulReturnCode);

    if(ulReturnCode > AT_RRETURN_CODE_BUTT)
    {
        At_ResetCombinParseInfo(ucIndex);
        AT_CheckProcBlockCmd();
        return;
    }

    if ( AT_CMD_NOT_SUPPORT == ulReturnCode )
    {
        /*  */

        AT_FormatAtCmdNotSupportResult(ucIndex, (AT_RRETURN_CODE_ENUM_UINT32)ulReturnCode);

        At_ResetCombinParseInfo(ucIndex);
        AT_CheckProcBlockCmd();
        return;
    }

    if ( AT_TOO_MANY_PARA == ulReturnCode )
    {
        /*  */

        AT_FormatAtTooManyParaResult(ucIndex, (AT_RRETURN_CODE_ENUM_UINT32)ulReturnCode);

        At_ResetCombinParseInfo(ucIndex);
        AT_CheckProcBlockCmd();
        return;
    }

    if (AT_ABORT == ulReturnCode)
    {
        AT_FormatAtAbortResult(ucIndex, (AT_RRETURN_CODE_ENUM_UINT32)ulReturnCode);

        At_ResetCombinParseInfo(ucIndex);

        AT_CheckProcBlockCmd();
        /* AT */
        return;
    }

    /* Added by L60609 for AT Project2011-10-24,  Begin*/
    ulRslt = AT_GetReturnCodeId(ulReturnCode, &ulReturnCodeIndex);

    if (VOS_OK != ulRslt)
    {
        AT_ERR_LOG("At_FormatResultData: result code index is err!");
        return;
    }
    /* Added by L60609 for AT Project2011-10-24,  End*/
    if ((AT_WAIT_SMS_INPUT == ulReturnCode)/* SMS */
        || (AT_WAIT_XML_INPUT == ulReturnCode))/* XML */
    {

        ulTmp = VOS_StrLen((TAF_CHAR *)gastAtReturnCodeTab[ulReturnCodeIndex].Result[gucAtVType]);
        TAF_MEM_CPY_S( pDataAt3 + usLength,
            ulTmp,
            (TAF_CHAR *)gastAtReturnCodeTab[ulReturnCodeIndex].Result[0],
            ulTmp );
        usLength += (TAF_UINT16)ulTmp;

        if ((AT_CMD_MAX_LEN + 20) >= (gstAtCombineSendData[ucIndex].usBufLen + usLength))
        {
            TAF_MEM_CPY_S((gstAtCombineSendData[ucIndex].aucBuffer + gstAtCombineSendData[ucIndex].usBufLen),
                        usLength,
                        pDataAt3,
                        usLength);
            gstAtCombineSendData[ucIndex].usBufLen += usLength;
        }

        At_SendResultData(ucIndex,pDataAt3,usLength);

        /* gstAtCombineSendData */
        TAF_MEM_SET_S(&gstAtCombineSendData[ucIndex], sizeof(AT_SEND_DATA_BUFFER_STRU), 0x00, sizeof(AT_SEND_DATA_BUFFER_STRU));

        return;
    }
    else if((AT_CME_ERROR_ENUM_BEGAIN < ulReturnCode) && (ulReturnCode < AT_CME_ERROR_ENUM_END) )
    {
        switch (gucAtCmeeType)
        {
        case AT_CMEE_ONLY_ERROR:
            /* Added by L60609 for AT Project2011-10-24,  Begin*/
            ulAtErrRslt = AT_GetReturnCodeId(AT_ERROR, &ulAtErrIndex);

            if(VOS_OK != ulAtErrRslt)
            {
                AT_ERR_LOG("At_FormatResultData: AT ERROR index is err!");
                return;
            }
            /* Added by L60609 for AT Project2011-10-24,  End*/
            ulTmp = VOS_StrLen( (TAF_CHAR *)gastAtReturnCodeTab[ulAtErrIndex].Result[gucAtVType] );
            TAF_MEM_CPY_S( pDataAt3 + usLength,
                ulTmp,
                (TAF_CHAR *)gastAtReturnCodeTab[ulAtErrIndex].Result[gucAtVType],
                ulTmp );
            usLength += (TAF_UINT16)ulTmp;
            break;

        case AT_CMEE_ERROR_CODE:
            TAF_MEM_CPY_S( pDataAt3 + usLength,
                12,
                (TAF_CHAR *)gaucAtCmeErrorStr,
                12 );
            usLength += 12;

            ulTmp = VOS_StrLen((TAF_CHAR *)gastAtReturnCodeTab[ulReturnCodeIndex].Result[0]);
            TAF_MEM_CPY_S( pDataAt3 + usLength,
                ulTmp,
                (TAF_CHAR *)gastAtReturnCodeTab[ulReturnCodeIndex].Result[0],
                ulTmp );
            usLength += (TAF_UINT16)ulTmp;
            break;

        default:
            TAF_MEM_CPY_S( pDataAt3 + usLength,
                12,
                (TAF_CHAR *)gaucAtCmeErrorStr,
                12 );
            usLength += 12;

            ulTmp = VOS_StrLen((TAF_CHAR *)gastAtReturnCodeTab[ulReturnCodeIndex].Result[1]);
            TAF_MEM_CPY_S( pDataAt3 + usLength,
                ulTmp,
                (TAF_CHAR *)gastAtReturnCodeTab[ulReturnCodeIndex].Result[1],
                ulTmp );
            usLength += (TAF_UINT16)ulTmp;
            break;
        }
    }
    else if((AT_DEVICE_ERROR_BEGIN < ulReturnCode) && (ulReturnCode < AT_DEVICE_ERROR_END) )
    {
        TAF_MEM_CPY_S( pDataAt3 + usLength ,
            12,
            (TAF_CHAR *)gaucAtCmeErrorStr,
            12 );
        usLength += 12;

        ulTmp = VOS_StrLen((TAF_CHAR *)gastAtReturnCodeTab[ulReturnCodeIndex].Result[0]);
        TAF_MEM_CPY_S( pDataAt3 + usLength,
            ulTmp,
            (TAF_CHAR *)gastAtReturnCodeTab[ulReturnCodeIndex].Result[0],
            ulTmp );
        usLength += (TAF_UINT16)ulTmp;
    }
    else if((AT_CMS_ERROR_ENUM_BEGAIN < ulReturnCode) && (ulReturnCode < AT_CMS_ERROR_ENUM_END) )
    {
        switch(gucAtCmeeType)
        {
            case AT_CMEE_ONLY_ERROR:
                /* Added by L60609 for AT Project2011-10-24,  Begin*/
                ulAtErrRslt = AT_GetReturnCodeId(AT_ERROR, &ulAtErrIndex);

                if(VOS_OK != ulAtErrRslt)
                {
                    AT_ERR_LOG("At_FormatResultData: AT ERROR index is err!");
                    return;
                }
                /* Added by L60609 for AT Project2011-10-24,  End*/

                ulTmp = VOS_StrLen( (TAF_CHAR *)gastAtReturnCodeTab[ulAtErrIndex].Result[gucAtVType] );
                TAF_MEM_CPY_S( pDataAt3 + usLength ,
                    ulTmp,
                    (TAF_CHAR *)gastAtReturnCodeTab[ulAtErrIndex].Result[gucAtVType] ,
                    ulTmp);
                usLength += (TAF_UINT16)ulTmp;
                break;

            case AT_CMEE_ERROR_CODE:

                TAF_MEM_CPY_S( pDataAt3 + usLength ,
                    12,
                    (TAF_CHAR *)gaucAtCmsErrorStr,
                    12);
                usLength += 12;

                ulTmp = VOS_StrLen((TAF_CHAR *)gastAtReturnCodeTab[ulReturnCodeIndex].Result[0]);
                TAF_MEM_CPY_S( pDataAt3 + usLength,
                    ulTmp,
                    (TAF_CHAR *)gastAtReturnCodeTab[ulReturnCodeIndex].Result[0],
                    ulTmp);
                usLength += (TAF_UINT16)ulTmp;
                break;

            default:
                TAF_MEM_CPY_S( pDataAt3 + usLength ,
                    12,
                    (TAF_CHAR *)gaucAtCmsErrorStr,
                    12);
                usLength += 12;

                ulTmp = VOS_StrLen((TAF_CHAR *)gastAtReturnCodeTab[ulReturnCodeIndex].Result[1]);
                TAF_MEM_CPY_S( pDataAt3 + usLength,
                    ulTmp,
                    (TAF_CHAR *)gastAtReturnCodeTab[ulReturnCodeIndex].Result[1],
                    ulTmp);
                usLength += (TAF_UINT16)ulTmp;
                break;
        }
    }
    else
    {

    }

    if (AT_V_ENTIRE_TYPE == gucAtVType)
    {
        if (0 != usLength)
        {
            TAF_MEM_CPY_S(pDataAt1,
                2,
                (TAF_CHAR *)gaucAtCrLf,
                2);/*Text\r\n*/

            TAF_MEM_CPY_S(pDataAt3 + usLength,
                2,
                (TAF_CHAR *)gaucAtCrLf,
                2);/*Text\r\n*/
            usLength += 2;
            usLength += 2;
        }

        if ((AT_COM_CMD_SUB_PROC_FINISH == ulComCmdSubProc)
            || (AT_COM_CMD_SUB_PROC_ABORT == ulComCmdSubProc))
        {
            if((AT_BASIC_CODE_ENUM_BEGAIN < ulReturnCode) && (ulReturnCode < AT_BASIC_CODE_ENUM_END))
            {
                TAF_MEM_CPY_S((TAF_CHAR *)(pDataAt1 + usLength),
                    2,
                    (TAF_CHAR *)gaucAtCrLf,
                    2);/*Code\r\n*/
                usLength += 2;

                ulTmp = VOS_StrLen((TAF_CHAR *)gastAtReturnCodeTab[ulReturnCodeIndex].Result[gucAtVType]);
                TAF_MEM_CPY_S(pDataAt1 + usLength,
                    ulTmp,
                    (TAF_CHAR *)gastAtReturnCodeTab[ulReturnCodeIndex].Result[gucAtVType],
                    ulTmp);/*Code*/
                usLength += (TAF_UINT16)ulTmp;

                /*PPPgucAtXType0CONNECT:CONNECT <Rate>*/
                if (AT_CONNECT == ulReturnCode)
                {
                    if ((AT_DATA_MODE == gastAtClientTab[ucIndex].Mode)
                        && ( (AT_PPP_DATA_MODE == gastAtClientTab[ucIndex].DataMode)
                              || (AT_IP_DATA_MODE == gastAtClientTab[ucIndex].DataMode) ) )
                    {
                        /*  */
                        ulMdmMscFlg = VOS_TRUE;

                        /* gucAtXType0CONNECT */
                        if (gucAtXType > 0)
                        {

                            PPP_RATE_DISPLAY_ENUM_UINT32 enRateDisplay;

                            /* Modified by s00217060 for ATC, 2013-4-2, end */
                            TAF_MEM_SET_S(&stSysMode, sizeof(stSysMode), 0x00, sizeof(stSysMode));

                            /* CucRatTypeucSysSubMode */
                            ulRet = TAF_AGENT_GetSysMode(ucIndex, &stSysMode);
                            if (VOS_OK != ulRet)
                            {
                                ucSubSysMode = TAF_SYS_SUBMODE_BUTT;
                            }
                            else
                            {
                                ucSubSysMode = stSysMode.enSysSubMode;
                            }

                            switch (ucSubSysMode)
                            {
                                case TAF_SYS_SUBMODE_GSM:
                                    ulNvDialRateIndex =    g_stDialConnectDisplayRate.ucGsmConnectRate;
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
                                    ulTmp = VOS_StrLen((TAF_CHAR *)g_PppDialRateDisplay[enRateDisplay]);
                                    TAF_MEM_CPY_S(aucDialRateTmp, sizeof(aucDialRateTmp), g_PppDialRateDisplay[enRateDisplay], ulTmp);
                                }
                                else if (TAF_PH_INFO_LTE_RAT == stSysMode.enRatType)
                                {
                                    ucDlCategoryIndex = AT_GetLteUeDlCategoryIndex();

                                    ulTmp = VOS_StrLen((TAF_CHAR *)(g_ucLTERateDisplay[ucDlCategoryIndex].acStrDlSpeed));
                                    TAF_MEM_CPY_S(aucDialRateTmp, sizeof(aucDialRateTmp), g_ucLTERateDisplay[ucDlCategoryIndex].acStrDlSpeed, ulTmp);
                                }
                                else
                                {
                                    enRateDisplay = AT_GetRateDisplayIndexForGsm(&stSysMode);
                                    ulTmp = VOS_StrLen((TAF_CHAR *)g_PppDialRateDisplay[enRateDisplay]);
                                    TAF_MEM_CPY_S(aucDialRateTmp, sizeof(aucDialRateTmp), g_PppDialRateDisplay[enRateDisplay], ulTmp);
                                }
                            }
    /* Modified by s00217060 for ATC, 2013-4-2, end */
                            else
                            {
                                ulTmp = VOS_StrLen((TAF_CHAR *)g_ucDialRateDisplayNv[ulNvDialRateIndex - 1]);
                                TAF_MEM_CPY_S(aucDialRateTmp, sizeof(aucDialRateTmp), g_ucDialRateDisplayNv[ulNvDialRateIndex - 1], ulTmp);
                            }

                            /*CONNECT*/
                            TAF_MEM_CPY_S(pDataAt1 + usLength,
                                ulTmp,
                                aucDialRateTmp,
                                ulTmp);
                            usLength += (TAF_UINT16)ulTmp;
                        }
                    }
                    else if ((AT_CSD_DATA_MODE == gastAtClientTab[ucIndex].DataMode)
                          && (AT_MODEM_USER == gastAtClientTab[ucIndex].UserType))
                    {
                        /*  */
                        ulMdmMscFlg = VOS_TRUE;
                    }
                    else
                    {

                    }
                }
                if ( AT_NO_CARRIER == ulReturnCode )
                {
                    if ( (AT_MODEM_USER == gastAtClientTab[ucIndex].UserType)
                      || (AT_HSUART_USER == gastAtClientTab[ucIndex].UserType) )
                    {
                        ulMdmMscFlg = VOS_TRUE;
                    }
                }

                TAF_MEM_CPY_S(pDataAt1 + usLength,
                    2,
                    (TAF_CHAR *)gaucAtCrLf,
                    2);/*Code\r\n*/
                usLength += 2;

            }

            /* <text> */
            if ((0 != usLength)
                && ((AT_CMD_MAX_LEN + 20) >= (gstAtCombineSendData[ucIndex].usBufLen + usLength)))
            {
                TAF_MEM_CPY_S((gstAtCombineSendData[ucIndex].aucBuffer + gstAtCombineSendData[ucIndex].usBufLen),
                            usLength,
                            pDataAt1,
                            usLength);
                gstAtCombineSendData[ucIndex].usBufLen += usLength;
            }

            if ((VOS_TRUE == ulMdmMscFlg) && (AT_NO_CARRIER == ulReturnCode))
            {
                AT_ProcFormatResultMsc(ucIndex, ulReturnCode);
            }

            At_SendResultData(ucIndex, gstAtCombineSendData[ucIndex].aucBuffer, gstAtCombineSendData[ucIndex].usBufLen);

            if ((VOS_TRUE == ulMdmMscFlg) && (AT_CONNECT == ulReturnCode))
            {
                AT_ProcFormatResultMsc(ucIndex, ulReturnCode);
            }

            At_ResetCombinParseInfo(ucIndex);
            AT_CheckProcBlockCmd();
        }
        else
        {
            if ((0 != usLength)
                && ((AT_CMD_MAX_LEN + 20) >= (gstAtCombineSendData[ucIndex].usBufLen + usLength)))
            {
                TAF_MEM_CPY_S((gstAtCombineSendData[ucIndex].aucBuffer + gstAtCombineSendData[ucIndex].usBufLen),
                            usLength,
                            pDataAt1,
                            usLength);
                gstAtCombineSendData[ucIndex].usBufLen += usLength;
            }

            /* Added by c64416 for AT Project 2011-10-20  Begin */
            AT_ParseCmdOver(ucIndex);
            /* Added by c64416 for AT Project 2011-10-20  End*/
        }
    }
    else
    {
        if ((AT_COM_CMD_SUB_PROC_FINISH == ulComCmdSubProc)
            || (AT_COM_CMD_SUB_PROC_ABORT == ulComCmdSubProc))
        {
            if((AT_BASIC_CODE_ENUM_BEGAIN < ulReturnCode) && (ulReturnCode < AT_BASIC_CODE_ENUM_END) )
            {
                if (0 != usLength)
                {
                   TAF_MEM_CPY_S(pDataAt3 + usLength,
                      2,
                      (TAF_CHAR *)gaucAtCrLf,
                      2);
                   usLength += 2;
                }
                ulTmp = VOS_StrLen((TAF_CHAR *)gastAtReturnCodeTab[ulReturnCodeIndex].Result[gucAtVType]);
                TAF_MEM_CPY_S(pDataAt3 + usLength,
                    ulTmp,
                    (TAF_CHAR *)gastAtReturnCodeTab[ulReturnCodeIndex].Result[gucAtVType],
                    ulTmp);/*Code*/
                usLength += (TAF_UINT16)ulTmp;

                TAF_MEM_CPY_S(pDataAt3 + usLength,
                    1,
                    &ucAtS3,
                    1);/*Code\r*/
                usLength += 1;
            }
            else
            {
                if ( 0 != usLength )
                {
                    if (AT_CMEE_ONLY_ERROR == gucAtCmeeType)
                    {
                        TAF_MEM_CPY_S(pDataAt3 + usLength,
                            1,
                            &ucAtS3,
                            1);
                        usLength += 1;
                    }
                    else
                    {
                        TAF_MEM_CPY_S(pDataAt3 + usLength,
                            2,
                            (TAF_CHAR *)gaucAtCrLf,
                            2);
                        usLength += 2;
                    }
                }
            }

            if ((0 != usLength)
                && ((AT_CMD_MAX_LEN + 20) >= (gstAtCombineSendData[ucIndex].usBufLen + usLength)))
            {
                TAF_MEM_CPY_S((gstAtCombineSendData[ucIndex].aucBuffer + gstAtCombineSendData[ucIndex].usBufLen),
                            usLength,
                            pDataAt3,
                            usLength);
                gstAtCombineSendData[ucIndex].usBufLen += usLength;
            }

            At_SendResultData(ucIndex, gstAtCombineSendData[ucIndex].aucBuffer, gstAtCombineSendData[ucIndex].usBufLen);

            At_ResetCombinParseInfo(ucIndex);
            AT_CheckProcBlockCmd();
        }
        else
        {
            if (0 != usLength)
            {
                TAF_MEM_CPY_S(pDataAt3 + usLength,
                    2,
                    (TAF_CHAR *)gaucAtCrLf,
                    2);
                usLength += 2;

                if ((AT_CMD_MAX_LEN + 20) >= (gstAtCombineSendData[ucIndex].usBufLen + usLength))
                {
                    TAF_MEM_CPY_S((gstAtCombineSendData[ucIndex].aucBuffer + gstAtCombineSendData[ucIndex].usBufLen),
                                usLength,
                                pDataAt3,
                                usLength);
                    gstAtCombineSendData[ucIndex].usBufLen += usLength;
                }
            }

            /* Added by c64416 for AT Project 2011-10-20  Begin */
            AT_ParseCmdOver(ucIndex);
            /* Added by c64416 for AT Project 2011-10-20  End*/
        }
    }

}

/*****************************************************************************
     : AT_GetDlRateDisplayIndex
   : WCDMA
   : ucWasCategory - UE
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 2011914
           : w00181244
       : 

*****************************************************************************/
VOS_UINT32 AT_GetDlRateDisplayIndex(
    VOS_UINT8                           ucWasCategory
)
{
    PPP_RATE_DISPLAY_ENUM_UINT32   enDlRateDisplayIndex;

    switch (ucWasCategory)
    {
        case AT_RATE_WCDMA_CATEGORY_6 :
            enDlRateDisplayIndex = PPP_RATE_DISPLAY_DPA_CATEGORY_6;
            break;

        case AT_RATE_WCDMA_CATEGORY_8:
            enDlRateDisplayIndex = PPP_RATE_DISPLAY_DPA_CATEGORY_8;
            break;

        case AT_RATE_WCDMA_CATEGORY_9:
            enDlRateDisplayIndex = PPP_RATE_DISPLAY_DPA_CATEGORY_9;
            break;

        case AT_RATE_WCDMA_CATEGORY_10:
            enDlRateDisplayIndex = PPP_RATE_DISPLAY_DPA_CATEGORY_10;
            break;

        case AT_RATE_WCDMA_CATEGORY_12 :
            enDlRateDisplayIndex = PPP_RATE_DISPLAY_DPA_CATEGORY_12;
            break;

        default:
            enDlRateDisplayIndex = PPP_RATE_DISPLAY_DPA_CATEGORY_10;
            break;

        }

     return enDlRateDisplayIndex;
}

/*****************************************************************************
     : AT_GetR7DlRateDisplayIndex
   : WCDMAR7
   : ucWasCategory - UE
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 2011914
           : w00181244
       : 

*****************************************************************************/
VOS_UINT32 AT_GetR7DlRateDisplayIndex(
    VOS_UINT8                           ucWasCategory
)
{
    PPP_RATE_DISPLAY_ENUM_UINT32   enDlRateDisplayIndex;

    switch (ucWasCategory)
    {
        case AT_RATE_WCDMA_CATEGORY_6 :
            enDlRateDisplayIndex = PPP_RATE_DISPLAY_DPA_CATEGORY_6;
            break;

        case AT_RATE_WCDMA_CATEGORY_8:
            enDlRateDisplayIndex = PPP_RATE_DISPLAY_DPA_CATEGORY_8;
            break;

        case AT_RATE_WCDMA_CATEGORY_9:
            enDlRateDisplayIndex = PPP_RATE_DISPLAY_DPA_CATEGORY_9;
            break;

        case AT_RATE_WCDMA_CATEGORY_10:
            enDlRateDisplayIndex = PPP_RATE_DISPLAY_DPA_CATEGORY_10;
            break;

        case AT_RATE_WCDMA_CATEGORY_12 :
            enDlRateDisplayIndex = PPP_RATE_DISPLAY_DPA_CATEGORY_12;
            break;

        case AT_RATE_WCDMA_CATEGORY_14:
            enDlRateDisplayIndex = PPP_RATE_DISPLAY_DPA_CATEGORY_14;
            break;

        case AT_RATE_WCDMA_CATEGORY_18:
            enDlRateDisplayIndex = PPP_RATE_DISPLAY_DPA_CATEGORY_18;
            break;

        default:
            enDlRateDisplayIndex = PPP_RATE_DISPLAY_DPA_CATEGORY_18;
            break;

    }

    return enDlRateDisplayIndex;
}

/*****************************************************************************
     : AT_GetR8DlRateDisplayIndex
   : WCDMAR8
   : ucWasCategory - UE
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 2011914
           : w00181244
       : 

*****************************************************************************/
VOS_UINT32 AT_GetR8DlRateDisplayIndex(
    VOS_UINT8                           ucWasCategory
)
{
    PPP_RATE_DISPLAY_ENUM_UINT32   enDlRateDisplayIndex;

    switch (ucWasCategory)
    {
        case AT_RATE_WCDMA_CATEGORY_6 :
            enDlRateDisplayIndex = PPP_RATE_DISPLAY_DPA_CATEGORY_6;
            break;

        case AT_RATE_WCDMA_CATEGORY_8:
            enDlRateDisplayIndex = PPP_RATE_DISPLAY_DPA_CATEGORY_8;
            break;

        case AT_RATE_WCDMA_CATEGORY_9:
            enDlRateDisplayIndex = PPP_RATE_DISPLAY_DPA_CATEGORY_9;
            break;

        case AT_RATE_WCDMA_CATEGORY_10:
            enDlRateDisplayIndex = PPP_RATE_DISPLAY_DPA_CATEGORY_10;
            break;

        case AT_RATE_WCDMA_CATEGORY_12 :
            enDlRateDisplayIndex = PPP_RATE_DISPLAY_DPA_CATEGORY_12;
            break;

        case AT_RATE_WCDMA_CATEGORY_14:
            enDlRateDisplayIndex = PPP_RATE_DISPLAY_DPA_CATEGORY_14;
            break;

        case AT_RATE_WCDMA_CATEGORY_18:
            enDlRateDisplayIndex = PPP_RATE_DISPLAY_DPA_CATEGORY_18;
            break;

        case AT_RATE_WCDMA_CATEGORY_24:
            enDlRateDisplayIndex = PPP_RATE_DISPLAY_DPA_CATEGORY_24;
            break;

        default:
            enDlRateDisplayIndex = PPP_RATE_DISPLAY_DPA_CATEGORY_24;
            break;

        }

     return enDlRateDisplayIndex;
}

/*****************************************************************************
     : AT_GetR9DlRateDisplayIndex
   : WCDMAR9
   : ucWasCategory - UE
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 2011914
           : w00181244
       : 

*****************************************************************************/
VOS_UINT32 AT_GetR9DlRateDisplayIndex(
    VOS_UINT8                           ucWasCategory
)
{
    PPP_RATE_DISPLAY_ENUM_UINT32   enDlRateDisplayIndex;

    switch (ucWasCategory)
    {
        case AT_RATE_WCDMA_CATEGORY_6 :
            enDlRateDisplayIndex = PPP_RATE_DISPLAY_DPA_CATEGORY_6;
            break;

        case AT_RATE_WCDMA_CATEGORY_8:
            enDlRateDisplayIndex = PPP_RATE_DISPLAY_DPA_CATEGORY_8;
            break;

        case AT_RATE_WCDMA_CATEGORY_9:
            enDlRateDisplayIndex = PPP_RATE_DISPLAY_DPA_CATEGORY_9;
            break;

        case AT_RATE_WCDMA_CATEGORY_10:
            enDlRateDisplayIndex = PPP_RATE_DISPLAY_DPA_CATEGORY_10;
            break;

        case AT_RATE_WCDMA_CATEGORY_12 :
            enDlRateDisplayIndex = PPP_RATE_DISPLAY_DPA_CATEGORY_12;
            break;

        case AT_RATE_WCDMA_CATEGORY_14:
            enDlRateDisplayIndex = PPP_RATE_DISPLAY_DPA_CATEGORY_14;
            break;

        case AT_RATE_WCDMA_CATEGORY_18:
            enDlRateDisplayIndex = PPP_RATE_DISPLAY_DPA_CATEGORY_18;
            break;

        case AT_RATE_WCDMA_CATEGORY_24:
            enDlRateDisplayIndex = PPP_RATE_DISPLAY_DPA_CATEGORY_24;
            break;

        case AT_RATE_WCDMA_CATEGORY_26:
            enDlRateDisplayIndex = PPP_RATE_DISPLAY_DPA_CATEGORY_26;
            break;

        case AT_RATE_WCDMA_CATEGORY_28:
            enDlRateDisplayIndex = PPP_RATE_DISPLAY_DPA_CATEGORY_28;
            break;

        default:
            enDlRateDisplayIndex = PPP_RATE_DISPLAY_DPA_CATEGORY_28;
            break;

        }

     return enDlRateDisplayIndex;
}

/*****************************************************************************
     : AT_GetRateDisplayIndexForGsm
   : GSM
   : 
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 20111020
           : A00165503
       : 
  2.       : 2012725
           : z60575
       : DTS2012072409126GPRSClass33
  3.       : 201342
           : s00217060
       : ATC
*****************************************************************************/
VOS_UINT32 AT_GetRateDisplayIndexForGsm(
    TAF_AGENT_SYS_MODE_STRU            *pstSysMode
)
{
    PPP_RATE_DISPLAY_ENUM_UINT32   enRateIndex;

    /* Modified by s00217060 for ATC, 2013-4-2, begin */
    if ( TAF_SYS_SUBMODE_EDGE == pstSysMode->enSysSubMode )
    /* Modified by s00217060 for ATC, 2013-4-2, end */
    {
        if ( VOS_TRUE == g_stAtDlRateCategory.ucGasMultislotClass33Flg )
        {
            enRateIndex = PPP_RATE_DISPLAY_EDGE_CALSS33;
        }
        else
        {
            enRateIndex = PPP_RATE_DISPLAY_EDGE;
        }
    }
    else
    {
    	if ( VOS_TRUE == g_stAtDlRateCategory.ucGasMultislotClass33Flg )
        {
            enRateIndex = PPP_RATE_DISPLAY_GPRS_CALSS33;
        }
        else
        {
            enRateIndex = PPP_RATE_DISPLAY_GPRS;
        }
    }

    return enRateIndex;
}

/*****************************************************************************
     : AT_GetRateDisplayIndexForWcdma
   : WCDMA
   : pstDlRateCategory - UE
   : 
     : VOS_UINT32
   :
   :

       :
  1.       : 2011914
           : w00181244
       : 
  2.       : 20111213
           : l00171473
       : DTS2011092204540MODEM

*****************************************************************************/
VOS_UINT32 AT_GetRateDisplayIndexForWcdma(
    AT_DOWNLINK_RATE_CATEGORY_STRU     *pstDlRateCategory
)
{
    PPP_RATE_DISPLAY_ENUM_UINT32   enRateIndex;

    switch (pstDlRateCategory->cWasRelIndicator)
    {
        case PS_PTL_VER_R99:
        case PS_PTL_VER_R3:
        case PS_PTL_VER_R4:
            enRateIndex = PPP_RATE_DISPLAY_R99;
            break;

        case PS_PTL_VER_R5:
        case PS_PTL_VER_R6:
            enRateIndex = AT_GetDlRateDisplayIndex(pstDlRateCategory->ucWasCategory);
            break;

        case PS_PTL_VER_R7:
            enRateIndex = AT_GetR7DlRateDisplayIndex(pstDlRateCategory->ucWasCategory);
            break;

        case PS_PTL_VER_R8:
            enRateIndex = AT_GetR8DlRateDisplayIndex(pstDlRateCategory->ucWasCategory);
            break;

        case PS_PTL_VER_R9:
            enRateIndex = AT_GetR9DlRateDisplayIndex(pstDlRateCategory->ucWasCategory);
            break;

        default:
            enRateIndex = AT_GetDlRateDisplayIndex(pstDlRateCategory->ucWasCategory);
            break;
    }

    return enRateIndex;
}


/*****************************************************************************
     : AT_ProcFormatResultMsc
   :
   : ulReturnCode 
             ucIndex
   : 
     : VOS_VOID
   :
   :

       :
  1.       : 20130921
           : j00174725
       : 

  2.       : 2016830
           : A00165503
       : DTS2016060307279: PPP

  3.       : 2016123
           : A00165503
       : DTS2016070404601:, PPP
*****************************************************************************/
VOS_VOID AT_ProcFormatResultMsc(
    VOS_UINT8                           ucIndex,
    VOS_UINT32                          ulReturnCode
)
{
    AT_UART_CTX_STRU                   *pstUartCtx = VOS_NULL_PTR;
    AT_DCE_MSC_STRU                     stMscStru;

    TAF_MEM_SET_S(&stMscStru, sizeof(stMscStru), 0x00, sizeof(AT_DCE_MSC_STRU));

    pstUartCtx      = AT_GetUartCtxAddr();

    if (AT_CONNECT == ulReturnCode)
    {
        if (VOS_TRUE == AT_CheckHsUartUser(ucIndex))
        {
            /* &SDSR  */
            if (AT_UART_DSR_MODE_CONNECT_ON == pstUartCtx->stLineCtrl.enDsrMode)
            {
                AT_CtrlDSR(ucIndex, AT_IO_LEVEL_HIGH);
            }

            /* &CDCD  */
            if (AT_UART_DCD_MODE_CONNECT_ON == pstUartCtx->stLineCtrl.enDcdMode)
            {
                AT_CtrlDCD(ucIndex, AT_IO_LEVEL_HIGH);
            }
        }
        else
        {
            /* DCD */
            AT_CtrlDCD(ucIndex, AT_IO_LEVEL_HIGH);
        }
    }
    else
    {
        if (VOS_TRUE == AT_CheckHsUartUser(ucIndex))
        {
           /* &SDSR  */
            if (AT_UART_DSR_MODE_CONNECT_ON == pstUartCtx->stLineCtrl.enDsrMode)
            {
                AT_CtrlDSR(ucIndex, AT_IO_LEVEL_LOW);
            }

            /* &CDCD  */
            if (AT_UART_DCD_MODE_CONNECT_ON == pstUartCtx->stLineCtrl.enDcdMode)
            {
                AT_CtrlDCD(ucIndex, AT_IO_LEVEL_LOW);
            }
        }
        else
        {
            /* DCD */
            AT_CtrlDCD(ucIndex, AT_IO_LEVEL_LOW);
            mdelay(30);
        }
    }

}



