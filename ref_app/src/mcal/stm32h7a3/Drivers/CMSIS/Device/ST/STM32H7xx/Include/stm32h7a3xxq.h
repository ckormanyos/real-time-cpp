///////////////////////////////////////////////////////////////////////////////
//  Modified by Christopher Kormanyos 2022.
//  Distributed under (see below).
//

/*
  ******************************************************************************
  * @file    stm32h7a3xxq.h
  * @author  MCD Application Team
  * @brief   CMSIS STM32H7A3xxQ Device Peripheral Access Layer Header File.
  *
  *          This file contains:
  *           - Data structures and the address mapping for all peripherals
  *           - Peripheral's registers declarations and bits definition
  *           - Macros to access peripheral's registers hardware
  *
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
*/

#ifndef STM32H7A3XXQ_2022_08_05_H_
  #define STM32H7A3XXQ_2022_08_05_H_

  #include <stdint.h>

  // IO definitions (access restrictions to peripheral registers).
  #if defined(__cplusplus)
  #define   __I    volatile
  #else
  #define   __I    volatile const
  #endif
  #define   __O    volatile
  #define   __IO   volatile

  // following defines should be used for structure members
  #define   __IM   volatile const
  #define   __OM   volatile
  #define   __IOM  volatile

  // SCB D-Cache Invalidate by Set-way Register Definitions.
  #define SCB_DCISW_WAY_Pos                  30U
  #define SCB_DCISW_WAY_Msk                  (3UL << SCB_DCISW_WAY_Pos)

  #define SCB_DCISW_SET_Pos                  5U
  #define SCB_DCISW_SET_Msk                  (0x1FFUL << SCB_DCISW_SET_Pos)

  #define SCB_CCSIDR_NUMSETS_Pos             13U
  #define SCB_CCSIDR_NUMSETS_Msk             (0x7FFFUL << SCB_CCSIDR_NUMSETS_Pos)

  #define SCB_CCSIDR_ASSOCIATIVITY_Pos       3U
  #define SCB_CCSIDR_ASSOCIATIVITY_Msk       (0x3FFUL << SCB_CCSIDR_ASSOCIATIVITY_Pos)

  // Cache Size ID Register Macros
  #define CCSIDR_WAYS(x)         (((x) & SCB_CCSIDR_ASSOCIATIVITY_Msk) >> SCB_CCSIDR_ASSOCIATIVITY_Pos)
  #define CCSIDR_SETS(x)         (((x) & SCB_CCSIDR_NUMSETS_Msk      ) >> SCB_CCSIDR_NUMSETS_Pos      )

  // Flexible Memory Controller
  typedef struct
  {
    __IO uint32_t BTCR[8U];
  }
  FMC_Bank1_TypeDef;

  // Bit definitions for PWR registers.
  #define PWR_CR1_DBP_Pos                        (8U)
  #define PWR_CR1_DBP_Msk                        (0x1UL << PWR_CR1_DBP_Pos)              /*!< 0x00000100 */
  #define PWR_CR1_DBP                            PWR_CR1_DBP_Msk                         /*!< Disable Back-up domain Protection */

  #define PWR_CR3_SMPSLEVEL_Pos                  (4U)
  #define PWR_CR3_SMPSLEVEL_Msk                  (0x3UL << PWR_CR3_SMPSLEVEL_Pos)        /*!< 0x00000030 */
  #define PWR_CR3_SMPSLEVEL                      PWR_CR3_SMPSLEVEL_Msk                   /*!< SMPS output Voltage */
  #define PWR_CR3_SMPSLEVEL_0                    (0x1UL << PWR_CR3_SMPSLEVEL_Pos)        /*!< 0x00000010 */
  #define PWR_CR3_SMPSLEVEL_1                    (0x2UL << PWR_CR3_SMPSLEVEL_Pos)        /*!< 0x00000020 */
  #define PWR_CR3_SMPSEXTHP_Pos                  (3U)
  #define PWR_CR3_SMPSEXTHP_Msk                  (0x1UL << PWR_CR3_SMPSEXTHP_Pos)        /*!< 0x00000008 */
  #define PWR_CR3_SMPSEXTHP                      PWR_CR3_SMPSEXTHP_Msk                   /*!< SMPS forced ON and in High Power MR mode */
  #define PWR_CR3_SMPSEN_Pos                     (2U)
  #define PWR_CR3_SMPSEN_Msk                     (0x1UL << PWR_CR3_SMPSEN_Pos)           /*!< 0x00000004 */
  #define PWR_CR3_SMPSEN                         PWR_CR3_SMPSEN_Msk                      /*!< SMPS Enable */
  #define PWR_CR3_LDOEN_Pos                      (1U)
  #define PWR_CR3_LDOEN_Msk                      (0x1UL << PWR_CR3_LDOEN_Pos)            /*!< 0x00000002 */
  #define PWR_CR3_LDOEN                          PWR_CR3_LDOEN_Msk                       /*!< Low Drop Output regulator enable */
  #define PWR_CR3_BYPASS_Pos                     (0U)
  #define PWR_CR3_BYPASS_Msk                     (0x1UL << PWR_CR3_BYPASS_Pos)           /*!< 0x00000001 */
  #define PWR_CR3_BYPASS                         PWR_CR3_BYPASS_Msk                      /*!< Power Management Unit bypass */

  // Bit definitions for PWR_SRDCR register
  #define PWR_SRDCR_VOS_Pos                      (14U)
  #define PWR_SRDCR_VOS_Msk                      (0x3UL << PWR_SRDCR_VOS_Pos)             /*!< 0x0000C000 */
  #define PWR_SRDCR_VOS                          PWR_SRDCR_VOS_Msk                        /*!< Voltage Scaling selection according performance */
  #define PWR_SRDCR_VOS_0                        (0x1UL << PWR_SRDCR_VOS_Pos)             /*!< 0x00004000 */
  #define PWR_SRDCR_VOS_1                        (0x2UL << PWR_SRDCR_VOS_Pos)             /*!< 0x00008000 */
  #define PWR_SRDCR_VOSRDY_Pos                   (13U)
  #define PWR_SRDCR_VOSRDY_Msk                   (0x1UL << PWR_SRDCR_VOSRDY_Pos)          /*!< 0x00002000 */
  #define PWR_SRDCR_VOSRDY                       PWR_SRDCR_VOSRDY_Msk                     /*!< VOS Ready bit for VDD11 Voltage Scaling output selection */

  // Bit definitions for FLASH_ACR register
  #define FLASH_ACR_LATENCY_Pos                  (0U)
  #define FLASH_ACR_LATENCY_Msk                  (0xFUL << FLASH_ACR_LATENCY_Pos)  /*!< 0x0000000F: bit4 is kept only for legacy purpose */
  #define FLASH_ACR_LATENCY                      FLASH_ACR_LATENCY_Msk             /*!< Read Latency */
  #define FLASH_ACR_LATENCY_0WS                  (0x00000000UL)
  #define FLASH_ACR_LATENCY_1WS                  (0x00000001UL)
  #define FLASH_ACR_LATENCY_2WS                  (0x00000002UL)
  #define FLASH_ACR_LATENCY_3WS                  (0x00000003UL)
  #define FLASH_ACR_LATENCY_4WS                  (0x00000004UL)
  #define FLASH_ACR_LATENCY_5WS                  (0x00000005UL)
  #define FLASH_ACR_LATENCY_6WS                  (0x00000006UL)
  #define FLASH_ACR_LATENCY_7WS                  (0x00000007UL)

  #define FLASH_LATENCY_DEFAULT                  FLASH_ACR_LATENCY_3WS /* FLASH Three Latency cycles */

  // Reset and Clock Control
  #define RCC_VER_2_0

  // Bit definitions for RCC_CR register
  #define RCC_CR_HSION_Pos                       (0U)
  #define RCC_CR_HSION_Msk                       (0x1UL << RCC_CR_HSION_Pos)     /*!< 0x00000001 */
  #define RCC_CR_HSION                           RCC_CR_HSION_Msk                /*!< Internal High Speed clock enable */
  #define RCC_CR_HSIKERON_Pos                    (1U)
  #define RCC_CR_HSIKERON_Msk                    (0x1UL << RCC_CR_HSIKERON_Pos)  /*!< 0x00000002 */
  #define RCC_CR_HSIKERON                        RCC_CR_HSIKERON_Msk             /*!< Internal High Speed clock enable for some IPs Kernel */
  #define RCC_CR_HSIRDY_Pos                      (2U)
  #define RCC_CR_HSIRDY_Msk                      (0x1UL << RCC_CR_HSIRDY_Pos)    /*!< 0x00000004 */
  #define RCC_CR_HSIRDY                          RCC_CR_HSIRDY_Msk               /*!< Internal High Speed clock ready flag */
  #define RCC_CR_HSIDIV_Pos                      (3U)
  #define RCC_CR_HSIDIV_Msk                      (0x3UL << RCC_CR_HSIDIV_Pos)    /*!< 0x00000018 */
  #define RCC_CR_HSIDIV                          RCC_CR_HSIDIV_Msk               /*!< Internal High Speed clock divider selection */
  #define RCC_CR_HSIDIV_1                        (0x0UL << RCC_CR_HSIDIV_Pos)     /*!< 0x00000000 */
  #define RCC_CR_HSIDIV_2                        (0x1UL << RCC_CR_HSIDIV_Pos)     /*!< 0x00000008 */
  #define RCC_CR_HSIDIV_4                        (0x2UL << RCC_CR_HSIDIV_Pos)     /*!< 0x00000010 */
  #define RCC_CR_HSIDIV_8                        (0x3UL << RCC_CR_HSIDIV_Pos)     /*!< 0x00000018 */

#endif // STM32H7A3XXQ_2022_08_05_H_
