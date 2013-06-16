/**
 *  \file   elm.h
 *
 *  \brief  Definitions used for ELM
 *
 *   This file contains the driver API prototypes and macro definitions.
 */

/* Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */


#ifndef _ELM_H_
#define _ELM_H__

#include "hw_elm.h"
#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
*                           MACRO DEFINITIONS
*******************************************************************************/
/*****************************************************************************/

/*
** Macros which can be used as 'configVal' parameter to ELMCAutoGatingConfig API
** 
*/
#define ELM_AUTOGATING_OCP_FREE                       (0)
#define ELM_AUTOGATING_OCP_GATING                     (1)

/*
** Macros which can be used as 'configVal' parameter to ELMCIdleModeSelect API.
** 
*/
#define ELM_IDLEMODE_FORCEIDLE                        (0)
#define ELM_IDLEMODE_NOIDLE                           (1)
#define ELM_IDLEMODE_SMARTIDLE                        (2)

/*
** Macros which can be used as 'configVal' parameter to ELMOCPClkActivityConfig 
** API.
** 
*/
#define ELM_CLOCKACTIVITYOCP_OCP_ON                   (1)
#define ELM_CLOCKACTIVITYOCP_OCP_OFF                  (0)

/*
** Macros which can be used as 'flag' parameter to ELMIntStatusGet API.
** 
*/
#define ELM_LOC_VALID_0_STATUS                        (0)
#define ELM_LOC_VALID_1_STATUS                        (1)
#define ELM_LOC_VALID_2_STATUS                        (2)
#define ELM_LOC_VALID_3_STATUS                        (3)
#define ELM_LOC_VALID_4_STATUS                        (4)
#define ELM_LOC_VALID_5_STATUS                        (5)
#define ELM_LOC_VALID_6_STATUS                        (6)
#define ELM_LOC_VALID_7_STATUS                        (7)
#define ELM_PAGE_VALID_STATUS                         (8)

/*
** Macros which can be used as 'flag' parameter to ELMIntConfig API.
** 
*/
#define ELM_INT_ENALBLE                               (1)
#define ELM_INT_DISALBLE                              (0)

/*
** Macros which can be used as 'bchECCLevel' parameter to
** ELMErrCorrectionLevelSet API.
** 
*/
#define ELM_ECC_BCH_LEVEL_4BITS                       (0)
#define ELM_ECC_BCH_LEVEL_8BITS                       (1)
#define ELM_ECC_BCH_LEVEL_16BITS                      (2)

/*
** Macros which can be used as 'mode' parameter to ELMModeSet API.
** 
*/
#define ELM_MODE_CONTINUOUS                           (0)
#define ELM_MODE_PAGE                                 (1)

/*
** Macros which can be used as 'sectorNum' parameter to ELMModeSet API.
** 
*/
#define ELM_PAGEMODE_SECTOR_0                         (0)
#define ELM_PAGEMODE_SECTOR_1                         (1)
#define ELM_PAGEMODE_SECTOR_2                         (2)
#define ELM_PAGEMODE_SECTOR_3                         (3)
#define ELM_PAGEMODE_SECTOR_4                         (4)
#define ELM_PAGEMODE_SECTOR_5                         (5)
#define ELM_PAGEMODE_SECTOR_6                         (6)
#define ELM_PAGEMODE_SECTOR_7                         (7)

/*
** Macros which can be used as 'synFrgmtId' parameter to ELMSyndromeFrgmtSet API
** 
*/
#define ELM_SYNDROME_FRGMT_0                          (0)
#define ELM_SYNDROME_FRGMT_1                          (1)
#define ELM_SYNDROME_FRGMT_2                          (2)
#define ELM_SYNDROME_FRGMT_3                          (3)
#define ELM_SYNDROME_FRGMT_4                          (4)
#define ELM_SYNDROME_FRGMT_5                          (5)
#define ELM_SYNDROME_FRGMT_6                          (6)

/*
** Macros which can be used as 'errNum' parameter to ELMErrLocBitAddrGet API.
** 
*/
#define ELM_ERROR_NUM_0                               (0)
#define ELM_ERROR_NUM_1                               (1)
#define ELM_ERROR_NUM_2                               (2)
#define ELM_ERROR_NUM_3                               (3)
#define ELM_ERROR_NUM_4                               (4)
#define ELM_ERROR_NUM_5                               (5)
#define ELM_ERROR_NUM_6                               (6)
#define ELM_ERROR_NUM_7                               (7)
#define ELM_ERROR_NUM_8                               (8)
#define ELM_ERROR_NUM_9                               (9)
#define ELM_ERROR_NUM_10                              (10)
#define ELM_ERROR_NUM_11                              (11)
#define ELM_ERROR_NUM_12                              (12)
#define ELM_ERROR_NUM_13                              (13)
#define ELM_ERROR_NUM_14                              (14)
#define ELM_ERROR_NUM_15                              (15)

/*****************************************************************************
**                    FUNCTION PROTOTYPES
*****************************************************************************/

extern void  ELMModuleReset(unsigned int baseAddr);
extern unsigned int  ELMRevisionGet(unsigned int baseAddr);
extern unsigned int ELMNumOfErrsGet(unsigned int baseAddr);
extern void  ELMErrLocProcessingStart(unsigned int baseAddr);
extern unsigned int  ELMModuleResetStatusGet(unsigned int baseAddr);
extern unsigned int ELMErrLocProcessingStatusGet(unsigned int baseAddr);
extern void  ELMECCSizeSet(unsigned int baseAddr, unsigned int eccSize);
extern void  ELMIntStatusClear(unsigned int baseAddr, unsigned int flag);
extern void  GPMCIntStatusClear(unsigned int baseAddr, unsigned int flag);
extern void  ELMCIdleModeSelect(unsigned int baseAddr, unsigned int mode);
extern unsigned int  ELMIntStatusGet(unsigned int baseAddr, unsigned int flag);
extern void  ELMCAutoGatingConfig(unsigned int baseAddr,
                                  unsigned int configVal);
extern unsigned int ELMErrLocBitAddrGet(unsigned int baseAddr,
                                        unsigned int errNum);
extern void  ELMOCPClkActivityConfig(unsigned int baseAddr,
                                     unsigned int configVal);
extern void  ELMErrCorrectionLevelSet(unsigned int baseAddr,
                                      unsigned int bchECCLevel);
extern void  ELMModeSet(unsigned int baseAddr, unsigned int mode,
                        unsigned int sectorNum);
extern void  ELMIntConfig(unsigned int baseAddr, unsigned int intFlag,
                          unsigned int configVal);
extern void  ELMSyndromeFrgmtSet(unsigned int baseAddr, unsigned int synFrgmtId,
                                 unsigned int synFrgmtVal);

#ifdef __cplusplus
}
#endif
#endif
