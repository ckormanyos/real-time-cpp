/** ============================================================================
 *   \file  soc_TI814x.h
 *
 *   \brief This file contains the peripheral information for AM1808 SOC
 *
 *  ============================================================================
 */

/* Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#ifndef _SOC_TI814x_H_
#define _SOC_TI814x_H_

#ifdef __cplusplus
extern "C" {
#endif

/** @brief Base address of AINTC memory mapped registers                      */
#define SOC_AINTC_REGS                      (0x48200000)

#define SOC_CONTROL_MODULE                  (0x48140000)

/** @brief Base address of Channel controller  memory mapped registers        */
#define SOC_EDMA30CC_0_REGS                 (0x49000000)
#define SOC_GPMC_REGS                       (0x50000000)
#define SOC_ELM_REGS                        (0x48080000)

#define TPCC_MUX(n)                          0xF90 + ((n) * 4)


#define  SOC_I2C_0_REGS                     (0x48028000) 
/******************************************************************************\
*  Parameterizable Configuration:- These are fed directly from the RTL
*  parameters for the given SOC
\******************************************************************************/

#define SOC_EDMA3_NUM_DMACH                 64
#define SOC_EDMA3_NUM_QDMACH                8
#define SOC_EDMA3_NUM_PARAMSETS             512
#define SOC_EDMA3_NUM_EVQUE                 4
#define SOC_EDMA3_CHMAPEXIST                0
#define SOC_EDMA3_NUM_REGIONS               8
#define SOC_EDMA3_MEMPROTECT                0

#define SOC_HSMMCSD_1_REGS				    0x481D8000

#ifdef __cplusplus
}
#endif

#endif  /* _SOC_TI814x_H_ */
