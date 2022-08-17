///////////////////////////////////////////////////////////////////////////////
//  Modified by Christopher Kormanyos 2022.
//  Distributed under (see below).
//

/*
  ******************************************************************************
  * @file    stm32h7xx_hal_rcc.h
  * @author  MCD Application Team
  * @brief   Header file of RCC HAL module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file in
  * the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  ******************************************************************************
*/

#ifndef STM32H7XX_HAL_RCC_2022_08_05_H_
#define STM32H7XX_HAL_RCC_2022_08_05_H_

#include <cstdint>

#include "stm32h7xx_hal_def.h"

typedef struct
{
  std::uint32_t PLLState;   // The new state of the PLL.
  std::uint32_t PLLSource;  // RCC_PLLSource: PLL entry clock source.
  std::uint32_t PLLM;       // PLLM: Division factor for PLL VCO input clock.
  std::uint32_t PLLN;       // PLLN: Multiplication factor for PLL VCO output clock.
  std::uint32_t PLLP;       // PLLP: Division factor for system clock.
  std::uint32_t PLLQ;       // PLLQ: Division factor for peripheral clocks.
  std::uint32_t PLLR;       // PLLR: Division factor for peripheral clocks.
  std::uint32_t PLLRGE;     // PLLRGE: PLL1 clock Input range
  std::uint32_t PLLVCOSEL;  // PLLVCOSEL: PLL1 clock Output range
  std::uint32_t PLLFRACN;   // PLLFRACN: Specifies Fractional Part Of The Multiplication Factor for
}
RCC_PLLInitTypeDef;

typedef struct
{
  uint32_t           OscillatorType;       // The oscillators to be configured.
  uint32_t           HSEState;             // The new state of the HSE.
  uint32_t           LSEState;             // The new state of the LSE.
  uint32_t           HSIState;             // The new state of the HSI.
  uint32_t           HSICalibrationValue;  // The calibration trimming value.
  uint32_t           LSIState;             // The new state of the LSI.
  uint32_t           HSI48State;           // The new state of the HSI48.
  uint32_t           CSIState;             // The new state of the CSI.
  uint32_t           CSICalibrationValue;  // The calibration trimming value.
  RCC_PLLInitTypeDef PLL;                  // PLL structure parameters
}
RCC_OscInitTypeDef;

typedef struct
{
  uint32_t ClockType;      // The clock to be configured.
  uint32_t SYSCLKSource;   // The clock source (SYSCLKS) used as system clock.
  uint32_t SYSCLKDivider;  // The system clock  divider. This parameter can be
  uint32_t AHBCLKDivider;  // The AHB clock (HCLK) divider. This clock is derived from the system clock (SYSCLK).
  uint32_t APB3CLKDivider; // The APB3 clock (D1PCLK1) divider. This clock is derived from the AHB clock (HCLK).
  uint32_t APB1CLKDivider; // The APB1 clock (PCLK1) divider. This clock is derived from the AHB clock (HCLK).
  uint32_t APB2CLKDivider; // The APB2 clock (PCLK2) divider. This clock is derived from the AHB clock (HCLK).
  uint32_t APB4CLKDivider; // The APB4 clock (D3PCLK1) divider. This clock is derived from the AHB clock (HCLK).
}
RCC_ClkInitTypeDef;

#define RCC_OSCILLATORTYPE_NONE        (0x00000000U)
#define RCC_OSCILLATORTYPE_HSE         (0x00000001U)
#define RCC_OSCILLATORTYPE_HSI         (0x00000002U)
#define RCC_OSCILLATORTYPE_LSE         (0x00000004U)
#define RCC_OSCILLATORTYPE_LSI         (0x00000008U)
#define RCC_OSCILLATORTYPE_CSI         (0x00000010U)
#define RCC_OSCILLATORTYPE_HSI48       (0x00000020U)
#define RCC_HSE_OFF                    (0x00000000U)
#define RCC_HSE_ON                     RCC_CR_HSEON
#define RCC_HSE_BYPASS                 ((uint32_t)(RCC_CR_HSEBYP | RCC_CR_HSEON))
#define RCC_HSE_BYPASS_DIGITAL         ((uint32_t)(RCC_CR_HSEEXT | RCC_CR_HSEBYP | RCC_CR_HSEON))
#define RCC_LSE_OFF                    (0x00000000U)
#define RCC_LSE_ON                     RCC_BDCR_LSEON
#define RCC_LSE_BYPASS                 ((uint32_t)(RCC_BDCR_LSEBYP | RCC_BDCR_LSEON))
#define RCC_LSE_BYPASS_DIGITAL         ((uint32_t)(RCC_BDCR_LSEEXT | RCC_BDCR_LSEBYP | RCC_BDCR_LSEON))
#define RCC_HSI_OFF                    (0x00000000U)                    // HSI clock deactivation
#define RCC_HSI_ON                     RCC_CR_HSION                     // HSI clock activation
#define RCC_HSI_DIV1                   (RCC_CR_HSIDIV_1 | RCC_CR_HSION) // HSI_DIV1 clock activation
#define RCC_HSI_DIV2                   (RCC_CR_HSIDIV_2 | RCC_CR_HSION) // HSI_DIV2 clock activation
#define RCC_HSI_DIV4                   (RCC_CR_HSIDIV_4 | RCC_CR_HSION) // HSI_DIV4 clock activation
#define RCC_HSI_DIV8                   (RCC_CR_HSIDIV | RCC_CR_HSION)   // HSI_DIV8 clock activation
#define RCC_HSICALIBRATION_DEFAULT     (0x40U)                          // Default HSI calibration trimming value for STM32H7 rev.V and above. (0x20 value for rev.Y handled within __HAL_RCC_HSI_CALIBRATIONVALUE_ADJUST macro)
#define RCC_HSI48_OFF                  (static_cast<std::uint8_t>(UINT8_C(0x00)))
#define RCC_HSI48_ON                   (static_cast<std::uint8_t>(UINT8_C(0x01)))

#define RCC_LSI_OFF                    (0x00000000U)
#define RCC_LSI_ON                     RCC_CSR_LSION
#define RCC_CSI_OFF                    (0x00000000U)
#define RCC_CSI_ON                     RCC_CR_CSION
#define RCC_CSICALIBRATION_DEFAULT     (0x20U)                          // Default CSI calibration trimming value for STM32H7 rev.V and above. (0x10 value for rev.Y handled within __HAL_RCC_CSI_CALIBRATIONVALUE_ADJUST macro)

#define RCC_PLL_NONE                   (0x00000000U)
#define RCC_PLL_OFF                    (0x00000001U)
#define RCC_PLL_ON                     (0x00000002U)

/**
  * @}
  */


/** @defgroup RCC_PLL_Clock_Source  RCC PLL Clock Source
  * @{
  */
#define RCC_PLLSOURCE_HSI              (0x00000000U)
#define RCC_PLLSOURCE_CSI              (0x00000001U)
#define RCC_PLLSOURCE_HSE              (0x00000002U)
#define RCC_PLLSOURCE_NONE             (0x00000003U)
/**
  * @}
  */

/** @defgroup RCC_PLL_Clock_Output  RCC PLL Clock Output
  * @{
  */
#define RCC_PLL1_DIVP                RCC_PLLCFGR_DIVP1EN
#define RCC_PLL1_DIVQ                RCC_PLLCFGR_DIVQ1EN
#define RCC_PLL1_DIVR                RCC_PLLCFGR_DIVR1EN

/**
  * @}
  */



/** @defgroup RCC_PLL1_VCI_Range  RCC PLL1 VCI Range
  * @{
  */
#define RCC_PLL1VCIRANGE_0                RCC_PLLCFGR_PLL1RGE_0       /*!< Clock range frequency between 1 and 2 MHz  */
#define RCC_PLL1VCIRANGE_1                RCC_PLLCFGR_PLL1RGE_1       /*!< Clock range frequency between 2 and 4 MHz  */
#define RCC_PLL1VCIRANGE_2                RCC_PLLCFGR_PLL1RGE_2       /*!< Clock range frequency between 4 and 8 MHz  */
#define RCC_PLL1VCIRANGE_3                RCC_PLLCFGR_PLL1RGE_3       /*!< Clock range frequency between 8 and 16 MHz */


/**
  * @}
  */


/** @defgroup RCC_PLL1_VCO_Range  RCC PLL1 VCO Range
  * @{
  */
#define RCC_PLL1VCOWIDE                 (0x00000000U)
#define RCC_PLL1VCOMEDIUM               RCC_PLLCFGR_PLL1VCOSEL

/**
  * @}
  */


/** @defgroup RCC_System_Clock_Type  RCC System Clock Type
  * @{
  */
#define RCC_CLOCKTYPE_SYSCLK           (0x00000001U)
#define RCC_CLOCKTYPE_HCLK             (0x00000002U)
#define RCC_CLOCKTYPE_D1PCLK1          (0x00000004U)
#define RCC_CLOCKTYPE_PCLK1            (0x00000008U)
#define RCC_CLOCKTYPE_PCLK2            (0x00000010U)
#define RCC_CLOCKTYPE_D3PCLK1          (0x00000020U)

/**
  * @}
  */

/** @defgroup RCC_System_Clock_Source  RCC System Clock Source
  * @{
  */
#define RCC_SYSCLKSOURCE_CSI           RCC_CFGR_SW_CSI
#define RCC_SYSCLKSOURCE_HSI           RCC_CFGR_SW_HSI
#define RCC_SYSCLKSOURCE_HSE           RCC_CFGR_SW_HSE
#define RCC_SYSCLKSOURCE_PLLCLK        RCC_CFGR_SW_PLL1

/**
  * @}
  */

/** @defgroup RCC_System_Clock_Source_Status System Clock Source Status
  * @{
  */
#define RCC_SYSCLKSOURCE_STATUS_CSI    RCC_CFGR_SWS_CSI   /*!< CSI used as system clock */
#define RCC_SYSCLKSOURCE_STATUS_HSI    RCC_CFGR_SWS_HSI   /*!< HSI used as system clock */
#define RCC_SYSCLKSOURCE_STATUS_HSE    RCC_CFGR_SWS_HSE   /*!< HSE used as system clock */
#define RCC_SYSCLKSOURCE_STATUS_PLLCLK RCC_CFGR_SWS_PLL1  /*!< PLL1 used as system clock */
/**
  * @}
  */

/** @defgroup RCC_SYS_Clock_Source  RCC SYS Clock Source
  * @{
  */
#if defined(RCC_D1CFGR_D1CPRE_DIV1)
#define RCC_SYSCLK_DIV1                RCC_D1CFGR_D1CPRE_DIV1
#define RCC_SYSCLK_DIV2                RCC_D1CFGR_D1CPRE_DIV2
#define RCC_SYSCLK_DIV4                RCC_D1CFGR_D1CPRE_DIV4
#define RCC_SYSCLK_DIV8                RCC_D1CFGR_D1CPRE_DIV8
#define RCC_SYSCLK_DIV16               RCC_D1CFGR_D1CPRE_DIV16
#define RCC_SYSCLK_DIV64               RCC_D1CFGR_D1CPRE_DIV64
#define RCC_SYSCLK_DIV128              RCC_D1CFGR_D1CPRE_DIV128
#define RCC_SYSCLK_DIV256              RCC_D1CFGR_D1CPRE_DIV256
#define RCC_SYSCLK_DIV512              RCC_D1CFGR_D1CPRE_DIV512
#else
#define RCC_SYSCLK_DIV1                RCC_CDCFGR1_CDCPRE_DIV1
#define RCC_SYSCLK_DIV2                RCC_CDCFGR1_CDCPRE_DIV2
#define RCC_SYSCLK_DIV4                RCC_CDCFGR1_CDCPRE_DIV4
#define RCC_SYSCLK_DIV8                RCC_CDCFGR1_CDCPRE_DIV8
#define RCC_SYSCLK_DIV16               RCC_CDCFGR1_CDCPRE_DIV16
#define RCC_SYSCLK_DIV64               RCC_CDCFGR1_CDCPRE_DIV64
#define RCC_SYSCLK_DIV128              RCC_CDCFGR1_CDCPRE_DIV128
#define RCC_SYSCLK_DIV256              RCC_CDCFGR1_CDCPRE_DIV256
#define RCC_SYSCLK_DIV512              RCC_CDCFGR1_CDCPRE_DIV512
#endif
/**
  * @}
  */


/** @defgroup RCC_HCLK_Clock_Source  RCC HCLK Clock Source
  * @{
  */
#if defined(RCC_D1CFGR_HPRE_DIV1)
#define RCC_HCLK_DIV1                RCC_D1CFGR_HPRE_DIV1
#define RCC_HCLK_DIV2                RCC_D1CFGR_HPRE_DIV2
#define RCC_HCLK_DIV4                RCC_D1CFGR_HPRE_DIV4
#define RCC_HCLK_DIV8                RCC_D1CFGR_HPRE_DIV8
#define RCC_HCLK_DIV16               RCC_D1CFGR_HPRE_DIV16
#define RCC_HCLK_DIV64               RCC_D1CFGR_HPRE_DIV64
#define RCC_HCLK_DIV128              RCC_D1CFGR_HPRE_DIV128
#define RCC_HCLK_DIV256              RCC_D1CFGR_HPRE_DIV256
#define RCC_HCLK_DIV512              RCC_D1CFGR_HPRE_DIV512
#else
#define RCC_HCLK_DIV1                RCC_CDCFGR1_HPRE_DIV1
#define RCC_HCLK_DIV2                RCC_CDCFGR1_HPRE_DIV2
#define RCC_HCLK_DIV4                RCC_CDCFGR1_HPRE_DIV4
#define RCC_HCLK_DIV8                RCC_CDCFGR1_HPRE_DIV8
#define RCC_HCLK_DIV16               RCC_CDCFGR1_HPRE_DIV16
#define RCC_HCLK_DIV64               RCC_CDCFGR1_HPRE_DIV64
#define RCC_HCLK_DIV128              RCC_CDCFGR1_HPRE_DIV128
#define RCC_HCLK_DIV256              RCC_CDCFGR1_HPRE_DIV256
#define RCC_HCLK_DIV512              RCC_CDCFGR1_HPRE_DIV512
#endif
/**
  * @}
  */

/** @defgroup RCC_APB3_Clock_Source  RCC APB3 Clock Source
  * @{
  */
#if defined (RCC_D1CFGR_D1PPRE_DIV1)
#define RCC_APB3_DIV1                  RCC_D1CFGR_D1PPRE_DIV1
#define RCC_APB3_DIV2                  RCC_D1CFGR_D1PPRE_DIV2
#define RCC_APB3_DIV4                  RCC_D1CFGR_D1PPRE_DIV4
#define RCC_APB3_DIV8                  RCC_D1CFGR_D1PPRE_DIV8
#define RCC_APB3_DIV16                 RCC_D1CFGR_D1PPRE_DIV16
#else
#define RCC_APB3_DIV1                  RCC_CDCFGR1_CDPPRE_DIV1
#define RCC_APB3_DIV2                  RCC_CDCFGR1_CDPPRE_DIV2
#define RCC_APB3_DIV4                  RCC_CDCFGR1_CDPPRE_DIV4
#define RCC_APB3_DIV8                  RCC_CDCFGR1_CDPPRE_DIV8
#define RCC_APB3_DIV16                 RCC_CDCFGR1_CDPPRE_DIV16
#endif
/**
  * @}
  */

/** @defgroup RCC_APB1_Clock_Source  RCC APB1 Clock Source
  * @{
  */
#if defined (RCC_D2CFGR_D2PPRE1_DIV1)
#define RCC_APB1_DIV1                  RCC_D2CFGR_D2PPRE1_DIV1
#define RCC_APB1_DIV2                  RCC_D2CFGR_D2PPRE1_DIV2
#define RCC_APB1_DIV4                  RCC_D2CFGR_D2PPRE1_DIV4
#define RCC_APB1_DIV8                  RCC_D2CFGR_D2PPRE1_DIV8
#define RCC_APB1_DIV16                 RCC_D2CFGR_D2PPRE1_DIV16
#else
#define RCC_APB1_DIV1                  RCC_CDCFGR2_CDPPRE1_DIV1
#define RCC_APB1_DIV2                  RCC_CDCFGR2_CDPPRE1_DIV2
#define RCC_APB1_DIV4                  RCC_CDCFGR2_CDPPRE1_DIV4
#define RCC_APB1_DIV8                  RCC_CDCFGR2_CDPPRE1_DIV8
#define RCC_APB1_DIV16                 RCC_CDCFGR2_CDPPRE1_DIV16
#endif

/**
  * @}
  */

/** @defgroup RCC_APB2_Clock_Source  RCC APB2 Clock Source
  * @{
  */
#if defined (RCC_D2CFGR_D2PPRE2_DIV1)
#define RCC_APB2_DIV1                  RCC_D2CFGR_D2PPRE2_DIV1
#define RCC_APB2_DIV2                  RCC_D2CFGR_D2PPRE2_DIV2
#define RCC_APB2_DIV4                  RCC_D2CFGR_D2PPRE2_DIV4
#define RCC_APB2_DIV8                  RCC_D2CFGR_D2PPRE2_DIV8
#define RCC_APB2_DIV16                 RCC_D2CFGR_D2PPRE2_DIV16
#else
#define RCC_APB2_DIV1                  RCC_CDCFGR2_CDPPRE2_DIV1
#define RCC_APB2_DIV2                  RCC_CDCFGR2_CDPPRE2_DIV2
#define RCC_APB2_DIV4                  RCC_CDCFGR2_CDPPRE2_DIV4
#define RCC_APB2_DIV8                  RCC_CDCFGR2_CDPPRE2_DIV8
#define RCC_APB2_DIV16                 RCC_CDCFGR2_CDPPRE2_DIV16
#endif
/**
  * @}
  */

/** @defgroup RCC_APB4_Clock_Source  RCC APB4 Clock Source
  * @{
  */
#if defined(RCC_D3CFGR_D3PPRE_DIV1)
#define RCC_APB4_DIV1                  RCC_D3CFGR_D3PPRE_DIV1
#define RCC_APB4_DIV2                  RCC_D3CFGR_D3PPRE_DIV2
#define RCC_APB4_DIV4                  RCC_D3CFGR_D3PPRE_DIV4
#define RCC_APB4_DIV8                  RCC_D3CFGR_D3PPRE_DIV8
#define RCC_APB4_DIV16                 RCC_D3CFGR_D3PPRE_DIV16
#else
#define RCC_APB4_DIV1                  RCC_SRDCFGR_SRDPPRE_DIV1
#define RCC_APB4_DIV2                  RCC_SRDCFGR_SRDPPRE_DIV2
#define RCC_APB4_DIV4                  RCC_SRDCFGR_SRDPPRE_DIV4
#define RCC_APB4_DIV8                  RCC_SRDCFGR_SRDPPRE_DIV8
#define RCC_APB4_DIV16                 RCC_SRDCFGR_SRDPPRE_DIV16
#endif
/**
  * @}
  */

/** @defgroup RCC_RTC_Clock_Source  RCC RTC Clock Source
  * @{
  */
#define RCC_RTCCLKSOURCE_NO_CLK          (0x00000000U)
#define RCC_RTCCLKSOURCE_LSE             (0x00000100U)
#define RCC_RTCCLKSOURCE_LSI             (0x00000200U)
#define RCC_RTCCLKSOURCE_HSE_DIV2        (0x00002300U)
#define RCC_RTCCLKSOURCE_HSE_DIV3        (0x00003300U)
#define RCC_RTCCLKSOURCE_HSE_DIV4        (0x00004300U)
#define RCC_RTCCLKSOURCE_HSE_DIV5        (0x00005300U)
#define RCC_RTCCLKSOURCE_HSE_DIV6        (0x00006300U)
#define RCC_RTCCLKSOURCE_HSE_DIV7        (0x00007300U)
#define RCC_RTCCLKSOURCE_HSE_DIV8        (0x00008300U)
#define RCC_RTCCLKSOURCE_HSE_DIV9        (0x00009300U)
#define RCC_RTCCLKSOURCE_HSE_DIV10       (0x0000A300U)
#define RCC_RTCCLKSOURCE_HSE_DIV11       (0x0000B300U)
#define RCC_RTCCLKSOURCE_HSE_DIV12       (0x0000C300U)
#define RCC_RTCCLKSOURCE_HSE_DIV13       (0x0000D300U)
#define RCC_RTCCLKSOURCE_HSE_DIV14       (0x0000E300U)
#define RCC_RTCCLKSOURCE_HSE_DIV15       (0x0000F300U)
#define RCC_RTCCLKSOURCE_HSE_DIV16       (0x00010300U)
#define RCC_RTCCLKSOURCE_HSE_DIV17       (0x00011300U)
#define RCC_RTCCLKSOURCE_HSE_DIV18       (0x00012300U)
#define RCC_RTCCLKSOURCE_HSE_DIV19       (0x00013300U)
#define RCC_RTCCLKSOURCE_HSE_DIV20       (0x00014300U)
#define RCC_RTCCLKSOURCE_HSE_DIV21       (0x00015300U)
#define RCC_RTCCLKSOURCE_HSE_DIV22       (0x00016300U)
#define RCC_RTCCLKSOURCE_HSE_DIV23       (0x00017300U)
#define RCC_RTCCLKSOURCE_HSE_DIV24       (0x00018300U)
#define RCC_RTCCLKSOURCE_HSE_DIV25       (0x00019300U)
#define RCC_RTCCLKSOURCE_HSE_DIV26       (0x0001A300U)
#define RCC_RTCCLKSOURCE_HSE_DIV27       (0x0001B300U)
#define RCC_RTCCLKSOURCE_HSE_DIV28       (0x0001C300U)
#define RCC_RTCCLKSOURCE_HSE_DIV29       (0x0001D300U)
#define RCC_RTCCLKSOURCE_HSE_DIV30       (0x0001E300U)
#define RCC_RTCCLKSOURCE_HSE_DIV31       (0x0001F300U)
#define RCC_RTCCLKSOURCE_HSE_DIV32       (0x00020300U)
#define RCC_RTCCLKSOURCE_HSE_DIV33       (0x00021300U)
#define RCC_RTCCLKSOURCE_HSE_DIV34       (0x00022300U)
#define RCC_RTCCLKSOURCE_HSE_DIV35       (0x00023300U)
#define RCC_RTCCLKSOURCE_HSE_DIV36       (0x00024300U)
#define RCC_RTCCLKSOURCE_HSE_DIV37       (0x00025300U)
#define RCC_RTCCLKSOURCE_HSE_DIV38       (0x00026300U)
#define RCC_RTCCLKSOURCE_HSE_DIV39       (0x00027300U)
#define RCC_RTCCLKSOURCE_HSE_DIV40       (0x00028300U)
#define RCC_RTCCLKSOURCE_HSE_DIV41       (0x00029300U)
#define RCC_RTCCLKSOURCE_HSE_DIV42       (0x0002A300U)
#define RCC_RTCCLKSOURCE_HSE_DIV43       (0x0002B300U)
#define RCC_RTCCLKSOURCE_HSE_DIV44       (0x0002C300U)
#define RCC_RTCCLKSOURCE_HSE_DIV45       (0x0002D300U)
#define RCC_RTCCLKSOURCE_HSE_DIV46       (0x0002E300U)
#define RCC_RTCCLKSOURCE_HSE_DIV47       (0x0002F300U)
#define RCC_RTCCLKSOURCE_HSE_DIV48       (0x00030300U)
#define RCC_RTCCLKSOURCE_HSE_DIV49       (0x00031300U)
#define RCC_RTCCLKSOURCE_HSE_DIV50       (0x00032300U)
#define RCC_RTCCLKSOURCE_HSE_DIV51       (0x00033300U)
#define RCC_RTCCLKSOURCE_HSE_DIV52       (0x00034300U)
#define RCC_RTCCLKSOURCE_HSE_DIV53       (0x00035300U)
#define RCC_RTCCLKSOURCE_HSE_DIV54       (0x00036300U)
#define RCC_RTCCLKSOURCE_HSE_DIV55       (0x00037300U)
#define RCC_RTCCLKSOURCE_HSE_DIV56       (0x00038300U)
#define RCC_RTCCLKSOURCE_HSE_DIV57       (0x00039300U)
#define RCC_RTCCLKSOURCE_HSE_DIV58       (0x0003A300U)
#define RCC_RTCCLKSOURCE_HSE_DIV59       (0x0003B300U)
#define RCC_RTCCLKSOURCE_HSE_DIV60       (0x0003C300U)
#define RCC_RTCCLKSOURCE_HSE_DIV61       (0x0003D300U)
#define RCC_RTCCLKSOURCE_HSE_DIV62       (0x0003E300U)
#define RCC_RTCCLKSOURCE_HSE_DIV63       (0x0003F300U)

// Flags in the CR register
#define RCC_FLAG_HSIRDY                ((uint8_t)0x22)
#define RCC_FLAG_HSIDIV                ((uint8_t)0x25)
#define RCC_FLAG_CSIRDY                ((uint8_t)0x28)
#define RCC_FLAG_HSI48RDY              ((uint8_t)0x2D)
#if defined(RCC_CR_D1CKRDY)
#define RCC_FLAG_D1CKRDY               ((uint8_t)0x2E)
#else
#define RCC_FLAG_CPUCKRDY              ((uint8_t)0x2E)
#define RCC_FLAG_D1CKRDY               RCC_FLAG_CPUCKRDY   /* alias */
#endif /* RCC_CR_D1CKRDY */
#if defined(RCC_CR_D2CKRDY)
#define RCC_FLAG_D2CKRDY               ((uint8_t)0x2F)
#else
#define RCC_FLAG_CDCKRDY               ((uint8_t)0x2F)
#define RCC_FLAG_D2CKRDY               RCC_FLAG_CDCKRDY    /* alias */
#endif /* RCC_CR_D2CKRDY */
#define RCC_FLAG_HSERDY                ((uint8_t)0x31)
#define RCC_FLAG_PLLRDY                ((uint8_t)0x39)
#define RCC_FLAG_PLL2RDY               ((uint8_t)0x3B)
#define RCC_FLAG_PLL3RDY               ((uint8_t)0x3D)
/* Flags in the BDCR register */
#define RCC_FLAG_LSERDY                ((uint8_t)0x41)

/* Flags in the CSR register */
#define RCC_FLAG_LSIRDY                ((uint8_t)0x61)

/* Flags in the RSR register */
#if defined(RCC_RSR_CPURSTF)
#define RCC_FLAG_CPURST                ((uint8_t)0x91)
#endif /* RCC_RSR_CPURSTF */

#if defined(RCC_RSR_D1RSTF)
#define RCC_FLAG_D1RST                 ((uint8_t)0x93)
#else
#define RCC_FLAG_CDRST                 ((uint8_t)0x93)
#endif /* RCC_RSR_D1RSTF */
#if defined(RCC_RSR_D2RSTF)
#define RCC_FLAG_D2RST                 ((uint8_t)0x94)
#endif /* RCC_RSR_D2RSTF */
#define RCC_FLAG_BORRST                ((uint8_t)0x95)
#define RCC_FLAG_PINRST                ((uint8_t)0x96)
#define RCC_FLAG_PORRST                ((uint8_t)0x97)
#define RCC_FLAG_SFTRST                ((uint8_t)0x98)
#define RCC_FLAG_IWDG1RST              ((uint8_t)0x9A)
#define RCC_FLAG_WWDG1RST              ((uint8_t)0x9C)
#define RCC_FLAG_LPWR1RST              ((uint8_t)0x9E)
#define RCC_FLAG_LPWR2RST              ((uint8_t)0x9F)

#if defined(DUAL_CORE)
#define RCC_FLAG_C1RST                 (RCC_FLAG_CPURST)
#define RCC_FLAG_C2RST                 ((uint8_t)0x92)
#define RCC_FLAG_SFTR1ST               (RCC_FLAG_SFTRST)
#define RCC_FLAG_SFTR2ST               ((uint8_t)0x99)
#define RCC_FLAG_WWDG2RST              ((uint8_t)0x9D)
#define RCC_FLAG_IWDG2RST              ((uint8_t)0x9B)
#endif /*DUAL_CORE*/


/**
  * @}
  */

/** @defgroup RCC_LSEDrive_Config LSE Drive Config
  * @{
  */
#define RCC_LSEDRIVE_LOW                 (0x00000000U) /*!< LSE low drive capability */
#define RCC_LSEDRIVE_MEDIUMLOW           RCC_BDCR_LSEDRV_0      /*!< LSE medium low drive capability */
#define RCC_LSEDRIVE_MEDIUMHIGH          RCC_BDCR_LSEDRV_1      /*!< LSE medium high drive capability */
#define RCC_LSEDRIVE_HIGH                RCC_BDCR_LSEDRV        /*!< LSE high drive capability */
/**
  * @}
  */

/** @defgroup RCC_Stop_WakeUpClock  RCC Stop WakeUpClock
  * @{
  */
#define RCC_STOP_WAKEUPCLOCK_HSI       (0x00000000U)
#define RCC_STOP_WAKEUPCLOCK_CSI       RCC_CFGR_STOPWUCK

/**
  * @}
  */

/** @defgroup RCC_Stop_KernelWakeUpClock  RCC Stop KernelWakeUpClock
  * @{
  */
#define RCC_STOP_KERWAKEUPCLOCK_HSI       (0x00000000U)
#define RCC_STOP_KERWAKEUPCLOCK_CSI        RCC_CFGR_STOPKERWUCK

// Macro to enable or disable the Internal High Speed oscillator (HSI).
static inline auto hal_rcc_hsi_config(const std::uint32_t state) -> void
{
  modify_reg(
             RCC->CR,
             static_cast<std::uint32_t>(RCC_CR_HSION | RCC_CR_HSIDIV),
             state
            );
}


/** @brief  Macro to get the HSI divider.
  * @retval The HSI divider. The returned value can be one
  *         of the following:
  *            - RCC_CR_HSIDIV_1  HSI oscillator divided by 1 (default after reset)
  *            - RCC_CR_HSIDIV_2  HSI oscillator divided by 2
  *            - RCC_CR_HSIDIV_4  HSI oscillator divided by 4
  *            - RCC_CR_HSIDIV_8  HSI oscillator divided by 8
  */
#define __HAL_RCC_GET_HSI_DIVIDER() ((uint32_t)(read_bit(RCC->CR, RCC_CR_HSIDIV)))

/** @brief  Macros to enable or disable the Internal High Speed oscillator (HSI).
  * @note   The HSI is stopped by hardware when entering STOP and STANDBY modes.
  *         It is used (enabled by hardware) as system clock source after start-up
  *         from Reset, wakeup from STOP and STANDBY mode, or in case of failure
  *         of the HSE used directly or indirectly as system clock (if the Clock
  *         Security System CSS is enabled).
  * @note   HSI can not be stopped if it is used as system clock source. In this case,
  *         you have to select another source of the system clock then stop the HSI.
  * @note   After enabling the HSI, the application software should wait on HSIRDY
  *         flag to be set indicating that HSI clock is stable and can be used as
  *         system clock source.
  *         This parameter can be: ENABLE or DISABLE.
  * @note   When the HSI is stopped, HSIRDY flag goes low after 6 HSI oscillator
  *         clock cycles.
  */
#define __HAL_RCC_HSI_ENABLE()  set_bit(RCC->CR, RCC_CR_HSION)
#define __HAL_RCC_HSI_DISABLE() clear_bit(RCC->CR, RCC_CR_HSION)


static inline auto hal_rcc_hsi_calibration_value_adjust(const std::uint32_t HSICalibrationValue) -> void
{
  // Adjust the Internal High Speed oscillator (HSI) calibration value.
  // The calibration is used to compensate for the variations in voltage
  // and temperature that influence the frequency of the internal HSI RC.
  // __HSICalibrationValue__: specifies the calibration trimming value.
  // This parameter must be a number between 0 and 0x7F (3F for Rev Y device).

  modify_reg
  (
    RCC->HSICFGR,
    static_cast<std::uint32_t>(RCC_HSICFGR_HSITRIM),
    static_cast<std::uint32_t>(HSICalibrationValue << RCC_HSICFGR_HSITRIM_Pos)
  );
}

/**
  * @brief    Macros to enable or disable the force of the Internal High Speed oscillator (HSI)
  *           in STOP mode to be quickly available as kernel clock for some peripherals.
  * @note     Keeping the HSI ON in STOP mode allows to avoid slowing down the communication
  *           speed because of the HSI start-up time.
  * @note     The enable of this function has not effect on the HSION bit.
  *           This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
#define __HAL_RCC_HSISTOP_ENABLE()     set_bit(RCC->CR, RCC_CR_HSIKERON)
#define __HAL_RCC_HSISTOP_DISABLE()    clear_bit(RCC->CR, RCC_CR_HSIKERON)


/**
  * @brief  Macro to enable or disable the Internal High Speed oscillator for USB (HSI48).
  * @note   After enabling the HSI48, the application software should wait on
  *         HSI48RDY flag to be set indicating that HSI48 clock is stable and can
  *         be used to clock the USB.
  * @note   The HSI48 is stopped by hardware when entering STOP and STANDBY modes.
  */
#define __HAL_RCC_HSI48_ENABLE()    set_bit(RCC->CR, RCC_CR_HSI48ON);

#define __HAL_RCC_HSI48_DISABLE()   clear_bit(RCC->CR, RCC_CR_HSI48ON);

/**
  * @brief  Macros to enable or disable the Internal  oscillator (CSI).
  * @note     The CSI is stopped by hardware when entering STOP and STANDBY modes.
  *           It is used (enabled by hardware) as system clock source after
  *           start-up from Reset, wakeup from STOP and STANDBY mode, or in case
  *           of failure of the HSE used directly or indirectly as system clock
  *           (if the Clock Security System CSS is enabled).
  * @note     CSI can not be stopped if it is used as system clock source.
  *           In this case, you have to select another source of the system
  *           clock then stop the CSI.
  * @note     After enabling the CSI, the application software should wait on
  *           CSIRDY flag to be set indicating that CSI clock is stable and can
  *           be used as system clock source.
  * @note     When the CSI is stopped, CSIRDY flag goes low after 6 CSI oscillator
  *           clock cycles.
  */
#define __HAL_RCC_CSI_ENABLE()  set_bit(RCC->CR, RCC_CR_CSION)
#define __HAL_RCC_CSI_DISABLE() clear_bit(RCC->CR, RCC_CR_CSION)

/** @brief  Macro Adjusts the Internal  oscillator (CSI) calibration value.
  * @note   The calibration is used to compensate for the variations in voltage
  *         and temperature that influence the frequency of the internal CSI RC.
  * @param  __CSICalibrationValue__: specifies the calibration trimming value.
  *         This parameter must be a number between 0 and 0x1F.
  */
#if defined(RCC_VER_X)
#define __HAL_RCC_CSI_CALIBRATIONVALUE_ADJUST(__CSICalibrationValue__)                                                                   \
           do {                                                                                                                          \
             if(HAL_GetREVID() <= REV_ID_Y)                                                                                              \
             {                                                                                                                           \
                if((__CSICalibrationValue__) == RCC_CSICALIBRATION_DEFAULT)                                                              \
                {                                                                                                                        \
                  modify_reg(RCC->HSICFGR, HAL_RCC_REV_Y_CSITRIM_Msk, ((uint32_t)0x10) << HAL_RCC_REV_Y_CSITRIM_Pos);                    \
                }                                                                                                                        \
                else                                                                                                                     \
                {                                                                                                                        \
                  modify_reg(RCC->HSICFGR, HAL_RCC_REV_Y_CSITRIM_Msk, (uint32_t)(__CSICalibrationValue__) << HAL_RCC_REV_Y_CSITRIM_Pos); \
                }                                                                                                                        \
             }                                                                                                                           \
             else                                                                                                                        \
             {                                                                                                                           \
               modify_reg(RCC->CSICFGR, RCC_CSICFGR_CSITRIM, (uint32_t)(__CSICalibrationValue__) << RCC_CSICFGR_CSITRIM_Pos);            \
             }                                                                                                                           \
           } while(0)

#else
#define __HAL_RCC_CSI_CALIBRATIONVALUE_ADJUST(__CSICalibrationValue__)                                                                   \
           do {                                                                                                                          \
               modify_reg(RCC->CSICFGR, RCC_CSICFGR_CSITRIM, (uint32_t)(__CSICalibrationValue__) << RCC_CSICFGR_CSITRIM_Pos);            \
               } while(0)

#endif /*RCC_VER_X*/

/**
  * @brief    Macros to enable or disable the force of the Low-power Internal oscillator (CSI)
  *           in STOP mode to be quickly available as kernel clock for USARTs and I2Cs.
  * @note     Keeping the CSI ON in STOP mode allows to avoid slowing down the communication
  *           speed because of the CSI start-up time.
  * @note     The enable of this function has not effect on the CSION bit.
  *           This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
#define __HAL_RCC_CSISTOP_ENABLE()     set_bit(RCC->CR, RCC_CR_CSIKERON)
#define __HAL_RCC_CSISTOP_DISABLE()    clear_bit(RCC->CR, RCC_CR_CSIKERON)

/** @brief  Macros to enable or disable the Internal Low Speed oscillator (LSI).
  * @note   After enabling the LSI, the application software should wait on
  *         LSIRDY flag to be set indicating that LSI clock is stable and can
  *         be used to clock the IWDG and/or the RTC.
  * @note   LSI can not be disabled if the IWDG is running.
  * @note   When the LSI is stopped, LSIRDY flag goes low after 6 LSI oscillator
  *         clock cycles.
  */
#define __HAL_RCC_LSI_ENABLE()         set_bit(RCC->CSR, RCC_CSR_LSION)
#define __HAL_RCC_LSI_DISABLE()        clear_bit(RCC->CSR, RCC_CSR_LSION)

/**
  * @brief  Macro to configure the External High Speed oscillator (__HSE__).
  * @note   After enabling the HSE (RCC_HSE_ON, RCC_HSE_BYPASS or RCC_HSE_BYPASS_DIGITAL),
  *         the application software should wait on HSERDY flag to be set indicating
  *         that HSE clock is stable and can be used to clock the PLL and/or system clock.
  * @note   HSE state can not be changed if it is used directly or through the
  *         PLL as system clock. In this case, you have to select another source
  *         of the system clock then change the HSE state (ex. disable it).
  * @note   The HSE is stopped by hardware when entering STOP and STANDBY modes.
  * @note   This function reset the CSSON bit, so if the clock security system(CSS)
  *         was previously enabled you have to enable it again after calling this
  *         function.
  * @param  __STATE__: specifies the new state of the HSE.
  *         This parameter can be one of the following values:
  *            @arg RCC_HSE_OFF: turn OFF the HSE oscillator, HSERDY flag goes low after
  *                              6 HSE oscillator clock cycles.
  *            @arg RCC_HSE_ON: turn ON the HSE oscillator.
  *            @arg RCC_HSE_BYPASS: HSE oscillator bypassed with external clock.
  *            @arg RCC_HSE_BYPASS_DIGITAL: HSE oscillator bypassed with digital external clock. (*)
  *
  * (*): Only available on stm32h7a3xx, stm32h7b3xx and stm32h7b0xx family lines.
  */
#if defined(RCC_CR_HSEEXT)
#define __HAL_RCC_HSE_CONFIG(__STATE__)                                \
                    do {                                               \
                      if ((__STATE__) == RCC_HSE_ON)                   \
                      {                                                \
                        set_bit(RCC->CR, RCC_CR_HSEON);                \
                      }                                                \
                      else if ((__STATE__) == RCC_HSE_OFF)             \
                      {                                                \
                        clear_bit(RCC->CR, RCC_CR_HSEON);              \
                        clear_bit(RCC->CR, RCC_CR_HSEEXT);             \
                        clear_bit(RCC->CR, RCC_CR_HSEBYP);             \
                      }                                                \
                      else if ((__STATE__) == RCC_HSE_BYPASS)          \
                      {                                                \
                        set_bit(RCC->CR, RCC_CR_HSEBYP);               \
                        clear_bit(RCC->CR, RCC_CR_HSEEXT);             \
                        set_bit(RCC->CR, RCC_CR_HSEON);                \
                      }                                                \
                      else if((__STATE__) == RCC_HSE_BYPASS_DIGITAL)   \
                      {                                                \
                        set_bit(RCC->CR, RCC_CR_HSEBYP);               \
                        set_bit(RCC->CR, RCC_CR_HSEEXT);               \
                        set_bit(RCC->CR, RCC_CR_HSEON);                \
                      }                                                \
                      else                                             \
                      {                                                \
                        clear_bit(RCC->CR, RCC_CR_HSEON);              \
                        clear_bit(RCC->CR, RCC_CR_HSEBYP);             \
                        clear_bit(RCC->CR, RCC_CR_HSEEXT);             \
                      }                                                \
                    } while(0)
#else
#define __HAL_RCC_HSE_CONFIG(__STATE__)                         \
                    do {                                        \
                      if ((__STATE__) == RCC_HSE_ON)            \
                      {                                         \
                        set_bit(RCC->CR, RCC_CR_HSEON);         \
                      }                                         \
                      else if ((__STATE__) == RCC_HSE_OFF)      \
                      {                                         \
                        clear_bit(RCC->CR, RCC_CR_HSEON);       \
                        clear_bit(RCC->CR, RCC_CR_HSEBYP);      \
                      }                                         \
                      else if ((__STATE__) == RCC_HSE_BYPASS)   \
                      {                                         \
                        set_bit(RCC->CR, RCC_CR_HSEBYP);        \
                        set_bit(RCC->CR, RCC_CR_HSEON);         \
                      }                                         \
                      else                                      \
                      {                                         \
                        clear_bit(RCC->CR, RCC_CR_HSEON);       \
                        clear_bit(RCC->CR, RCC_CR_HSEBYP);      \
                      }                                         \
                    } while(0)
#endif /* RCC_CR_HSEEXT */

/** @defgroup RCC_LSE_Configuration LSE Configuration
  * @{
  */

/**
  * @brief  Macro to configure the External Low Speed oscillator (LSE).
  * @note   Transition LSE Bypass to LSE On and LSE On to LSE Bypass are not supported by this macro.
  *         User should request a transition to LSE Off first and then LSE On or LSE Bypass.
  * @note   The external input clock can have a frequency up to 1 MHz and be low swing (analog) or digital(*).
            A duty cycle close to 50% is recommended.
  * @note   As the LSE is in the Backup domain and write access is denied to
  *         this domain after reset, you have to enable write access using
  *         HAL_PWR_EnableBkUpAccess() function before to configure the LSE
  *         (to be done once after reset).
  * @note   After enabling the LSE (RCC_LSE_ON, RCC_LSE_BYPASS or RCC_LSE_BYPASS_DIGITAL*), the application
  *         software should wait on LSERDY flag to be set indicating that LSE clock
  *         is stable and can be used to clock the RTC.
  * @note   If the RTC is used, the LSE bypass must not be configured in digital mode but in low swing analog mode (*)
  * @param  __STATE__: specifies the new state of the LSE.
  *         This parameter can be one of the following values:
  *            @arg RCC_LSE_OFF: turn OFF the LSE oscillator, LSERDY flag goes low after
  *                              6 LSE oscillator clock cycles.
  *            @arg RCC_LSE_ON: turn ON the LSE oscillator.
  *            @arg RCC_LSE_BYPASS: LSE oscillator bypassed with external clock.
  *            @arg RCC_LSE_BYPASS_DIGITAL: LSE oscillator bypassed with external digital clock. (*)
  *
  *         (*) Available on some STM32H7 lines only.
  */
#if defined(RCC_BDCR_LSEEXT)
#define __HAL_RCC_LSE_CONFIG(__STATE__) \
                    do {                                               \
                      if((__STATE__) == RCC_LSE_ON)                    \
                      {                                                \
                        set_bit(RCC->BDCR, RCC_BDCR_LSEON);            \
                      }                                                \
                      else if((__STATE__) == RCC_LSE_OFF)              \
                      {                                                \
                        clear_bit(RCC->BDCR, RCC_BDCR_LSEON);          \
                        clear_bit(RCC->BDCR, RCC_BDCR_LSEEXT);         \
                        clear_bit(RCC->BDCR, RCC_BDCR_LSEBYP);         \
                      }                                                \
                      else if((__STATE__) == RCC_LSE_BYPASS)           \
                      {                                                \
                        set_bit(RCC->BDCR, RCC_BDCR_LSEBYP);           \
                        clear_bit(RCC->BDCR, RCC_BDCR_LSEEXT);         \
                        set_bit(RCC->BDCR, RCC_BDCR_LSEON);            \
                      }                                                \
                      else if((__STATE__) == RCC_LSE_BYPASS_DIGITAL)   \
                      {                                                \
                        set_bit(RCC->BDCR, RCC_BDCR_LSEBYP);           \
                        set_bit(RCC->BDCR, RCC_BDCR_LSEEXT);           \
                        set_bit(RCC->BDCR, RCC_BDCR_LSEON);            \
                      }                                                \
                      else                                             \
                      {                                                \
                        clear_bit(RCC->BDCR, RCC_BDCR_LSEON);          \
                        clear_bit(RCC->BDCR, RCC_BDCR_LSEBYP);         \
                        clear_bit(RCC->BDCR, RCC_BDCR_LSEEXT);         \
                      }                                                \
                    } while(0)
#else

#define __HAL_RCC_LSE_CONFIG(__STATE__) \
                    do {                                       \
                      if((__STATE__) == RCC_LSE_ON)            \
                      {                                        \
                        set_bit(RCC->BDCR, RCC_BDCR_LSEON);    \
                      }                                        \
                      else if((__STATE__) == RCC_LSE_OFF)      \
                      {                                        \
                        clear_bit(RCC->BDCR, RCC_BDCR_LSEON);  \
                        clear_bit(RCC->BDCR, RCC_BDCR_LSEBYP); \
                      }                                        \
                      else if((__STATE__) == RCC_LSE_BYPASS)   \
                      {                                        \
                        set_bit(RCC->BDCR, RCC_BDCR_LSEBYP);   \
                        set_bit(RCC->BDCR, RCC_BDCR_LSEON);    \
                      }                                        \
                      else                                     \
                      {                                        \
                        clear_bit(RCC->BDCR, RCC_BDCR_LSEON);  \
                        clear_bit(RCC->BDCR, RCC_BDCR_LSEBYP); \
                      }                                        \
                    } while(0)

#endif /* RCC_BDCR_LSEEXT */
/**
  * @}
  */

/** @brief  Macros to enable or disable the the RTC clock.
  * @note   These macros must be used only after the RTC clock source was selected.
  */
#define __HAL_RCC_RTC_ENABLE()         set_bit(RCC->BDCR, RCC_BDCR_RTCEN)
#define __HAL_RCC_RTC_DISABLE()        clear_bit(RCC->BDCR, RCC_BDCR_RTCEN)

/** @brief  Macros to configure the RTC clock (RTCCLK).
  * @note   As the RTC clock configuration bits are in the Backup domain and write
  *         access is denied to this domain after reset, you have to enable write
  *         access using the Power Backup Access macro before to configure
  *         the RTC clock source (to be done once after reset).
  * @note   Once the RTC clock is configured it can't be changed unless the
  *         Backup domain is reset using __HAL_RCC_BackupReset_RELEASE() macro, or by
  *         a Power On Reset (POR).
  * @param  __RTCCLKSource__: specifies the RTC clock source.
  *         This parameter can be one of the following values:
  *            @arg RCC_RTCCLKSOURCE_LSE: LSE selected as RTC clock.
  *            @arg RCC_RTCCLKSOURCE_LSI: LSI selected as RTC clock.
  *            @arg RCC_RTCCLKSOURCE_HSE_DIVx: HSE clock divided by x selected
  *                                            as RTC clock, where x:[2,31]
  * @note   If the LSE or LSI is used as RTC clock source, the RTC continues to
  *         work in STOP and STANDBY modes, and can be used as wakeup source.
  *         However, when the HSE clock is used as RTC clock source, the RTC
  *         cannot be used in STOP and STANDBY modes.
  * @note   The maximum input clock frequency for RTC is 1MHz (when using HSE as
  *         RTC clock source).
  */
#define __HAL_RCC_RTC_CLKPRESCALER(__RTCCLKSource__) (((__RTCCLKSource__) & RCC_BDCR_RTCSEL) == RCC_BDCR_RTCSEL) ?    \
                                                 modify_reg(RCC->CFGR, RCC_CFGR_RTCPRE, (((__RTCCLKSource__) & 0xFFFFCFFU) >> 4)) : clear_bit(RCC->CFGR, RCC_CFGR_RTCPRE)

#define __HAL_RCC_RTC_CONFIG(__RTCCLKSource__) do { __HAL_RCC_RTC_CLKPRESCALER(__RTCCLKSource__);    \
                                                    RCC->BDCR |= ((__RTCCLKSource__) & 0x00000FFFU);  \
                                                   } while (0)

#define  __HAL_RCC_GET_RTC_SOURCE() ((uint32_t)(read_bit(RCC->BDCR, RCC_BDCR_RTCSEL)))


/** @brief  Macros to force or release the Backup domain reset.
  * @note   This function resets the RTC peripheral (including the backup registers)
  *         and the RTC clock source selection in RCC_BDCR register.
  * @note   The BKPSRAM is not affected by this reset.
  */
#define __HAL_RCC_BACKUPRESET_FORCE()   set_bit(RCC->BDCR, RCC_BDCR_BDRST)
#define __HAL_RCC_BACKUPRESET_RELEASE() clear_bit(RCC->BDCR, RCC_BDCR_BDRST)

/** @brief  Macros to enable or disable the main PLL.
  * @note   After enabling the main PLL, the application software should wait on
  *         PLLRDY flag to be set indicating that PLL clock is stable and can
  *         be used as system clock source.
  * @note   The main PLL can not be disabled if it is used as system clock source
  * @note   The main PLL is disabled by hardware when entering STOP and STANDBY modes.
  */
#define __HAL_RCC_PLL_ENABLE()         set_bit(RCC->CR, RCC_CR_PLL1ON)
#define __HAL_RCC_PLL_DISABLE()        clear_bit(RCC->CR, RCC_CR_PLL1ON)

/**
  * @brief  Enables or disables each clock output (PLL_P_CLK, PLL_Q_CLK, PLL_R_CLK)
  * @note   Enabling/disabling  those Clocks can be done only when the PLL is disabled.
  *         This is mainly used to save Power.
  *        (The ck_pll_p of the System PLL cannot be stopped if used as System Clock).
  * @param  __RCC_PLL1ClockOut__: specifies the PLL clock to be outputted
  *          This parameter can be one of the following values:
  *            @arg RCC_PLL1_DIVP: This clock is used to generate system clock up to 550MHZ(*), 480MHZ(**) or 280MHZ(***)
  *            @arg RCC_PLL1_DIVQ: This clock is used to generate peripherals clock up to 550MHZ(*), 480MHZ(**) or 280MHZ(***)
  *            @arg RCC_PLL1_DIVR: This clock is used to generate peripherals clock up to 550MHZ(*), 480MHZ(**) or 280MHZ(***)
  *
  * (*) : For stm32h72xxx and stm32h73xxx family lines and requires to enable the CPU_FREQ_BOOST flash option byte, 520MHZ otherwise.
  * (**) : For stm32h74xx and stm32h75xx family lines and requires the board to be connected on LDO regulator not SMPS, 400MHZ otherwise.
  * (***): For stm32h7a3xx, stm32h7b3xx and stm32h7b0xx family lines.
  *
  * @retval None
  */
#define __HAL_RCC_PLLCLKOUT_ENABLE(__RCC_PLL1ClockOut__)   set_bit(RCC->PLLCFGR, (__RCC_PLL1ClockOut__))

#define __HAL_RCC_PLLCLKOUT_DISABLE(__RCC_PLL1ClockOut__)  clear_bit(RCC->PLLCFGR, (__RCC_PLL1ClockOut__))


/**
  * @brief  Enables or disables Fractional Part Of The Multiplication Factor of PLL1 VCO
  * @note   Enabling/disabling  Fractional Part can be any time  without the need to stop the PLL1
  * @retval None
  */
#define __HAL_RCC_PLLFRACN_ENABLE()   set_bit(RCC->PLLCFGR, RCC_PLLCFGR_PLL1FRACEN)

#define __HAL_RCC_PLLFRACN_DISABLE()  clear_bit(RCC->PLLCFGR, RCC_PLLCFGR_PLL1FRACEN)


/**
  * @brief  Macro to configures the main PLL clock source, multiplication and division factors.
  * @note   This function must be used only when the main PLL is disabled.
  *
  * @param  __RCC_PLLSOURCE__: specifies the PLL entry clock source.
  *          This parameter can be one of the following values:
  *            @arg RCC_PLLSOURCE_CSI: CSI oscillator clock selected as PLL clock entry
  *            @arg RCC_PLLSOURCE_HSI: HSI oscillator clock selected as PLL clock entry
  *            @arg RCC_PLLSOURCE_HSE: HSE oscillator clock selected as PLL clock entry
  * @note   This clock source (__RCC_PLLSource__) is common for the main PLL1 (main PLL) and PLL2 & PLL3 .
  *
  * @param  __PLLM1__: specifies the division factor for PLL VCO input clock
  *          This parameter must be a number between 1 and 63.
  * @note   You have to set the PLLM parameter correctly to ensure that the VCO input
  *         frequency ranges from 1 to 16 MHz.
  *
  * @param  __PLLN1__: specifies the multiplication factor for PLL VCO output clock
  *          This parameter must be a number between 4 and 512 or between 8 and 420(*).
  * @note   You have to set the PLLN parameter correctly to ensure that the VCO
  *         output frequency is between 150 and 420 MHz (when in medium VCO range) or
  *         between 192 and 836 MHZ or between 128 and 560 MHZ(*) (when in wide VCO range)
  *
  * @param  __PLLP1__: specifies the division factor for system  clock.
  *          This parameter must be a number between 2 or 1(**) and 128 (where odd numbers are not allowed) 
  *
  * @param  __PLLQ1__: specifies the division factor for peripheral kernel clocks
  *          This parameter must be a number between 1 and 128
  *
  * @param  __PLLR1__: specifies the division factor for peripheral kernel clocks
  *          This parameter must be a number between 1 and 128
  *
  * @note   To insure an optimal behavior of the PLL when one of the post-divider (DIVP, DIVQ or DIVR)
  *         is not used, application shall clear the enable bit (DIVyEN) and assign lowest possible 
  *         value to  __PLL1P__, __PLL1Q__ or __PLL1R__ parameters.
  * @retval None
  *
  *  (*) : For stm32h7a3xx and stm32h7b3xx family lines.
  *  (**): For stm32h72xxx and stm32h73xxx family lines.
  */


static inline auto hal_rcc_pll_config(const std::uint32_t RCC_PLLSOURCE,
                                      const std::uint32_t PLLM1,
                                      const std::uint32_t PLLN1,
                                      const std::uint32_t PLLP1,
                                      const std::uint32_t PLLQ1,
                                      const std::uint32_t PLLR1) -> void
{
  modify_reg(RCC->PLLCKSELR, (RCC_PLLCKSELR_PLLSRC | RCC_PLLCKSELR_DIVM1), (RCC_PLLSOURCE | (PLLM1 <<4U)));

  const auto val =
    static_cast<std::uint32_t>
    (
        (((PLLN1 - 1U) & RCC_PLL1DIVR_N1) | (((PLLP1 -1U ) << 9U) & RCC_PLL1DIVR_P1)
      | (((PLLQ1 - 1U) << 16U) & RCC_PLL1DIVR_Q1) | (((PLLR1 - 1U) << 24U) & RCC_PLL1DIVR_R1))
    );

  write_reg(RCC->PLL1DIVR , val);
}

/** @brief  Macro to configure the PLLs clock source.
  * @note   This function must be used only when all PLLs are disabled.
  * @param  __PLLSOURCE__: specifies the PLLs entry clock source.
  *         This parameter can be one of the following values:
  *            @arg RCC_PLLSOURCE_CSI: CSI oscillator clock selected as PLL clock entry
  *            @arg RCC_PLLSOURCE_HSI: HSI oscillator clock selected as PLL clock entry
  *            @arg RCC_PLLSOURCE_HSE: HSE oscillator clock selected as PLL clock entry
  *
  */
#define __HAL_RCC_PLL_PLLSOURCE_CONFIG(__PLLSOURCE__) modify_reg(RCC->PLLCKSELR, RCC_PLLCKSELR_PLLSRC, (__PLLSOURCE__))


/**
  * @brief  Macro to configures the main PLL clock Fractional Part Of The Multiplication Factor
  *
  * @note   These bits can be written at any time, allowing dynamic fine-tuning of the PLL1 VCO
  *
  * @param  __RCC_PLL1FRACN__: specifies Fractional Part Of The Multiplication Factor for PLL1 VCO
  *                            It should be a value between 0 and 8191
  * @note   Warning: The software has to set correctly these bits to insure that the VCO
  *                  output frequency is between its valid frequency range, which is:
  *                   192 to 836 MHz or 128 to 560 MHz(*) if PLL1VCOSEL = 0
  *                   150 to 420 MHz if PLL1VCOSEL = 1.
  *
  * (*) : For stm32h7a3xx and stm32h7b3xx family lines.
  *
  * @retval None
  */
 #define  __HAL_RCC_PLLFRACN_CONFIG(__RCC_PLL1FRACN__) modify_reg(RCC->PLL1FRACR, RCC_PLL1FRACR_FRACN1, (uint32_t)(__RCC_PLL1FRACN__) << RCC_PLL1FRACR_FRACN1_Pos)


/** @brief  Macro to select  the PLL1  reference frequency range.
  * @param  __RCC_PLL1VCIRange__: specifies the PLL1 input frequency range
  *         This parameter can be one of the following values:
  *            @arg RCC_PLL1VCIRANGE_0: Range frequency is between 1 and 2 MHz
  *            @arg RCC_PLL1VCIRANGE_1: Range frequency is between 2 and 4 MHz
  *            @arg RCC_PLL1VCIRANGE_2: Range frequency is between 4 and 8 MHz
  *            @arg RCC_PLL1VCIRANGE_3: Range frequency is between 8 and 16 MHz
  * @retval None
  */
#define __HAL_RCC_PLL_VCIRANGE(__RCC_PLL1VCIRange__) \
                  modify_reg(RCC->PLLCFGR, RCC_PLLCFGR_PLL1RGE, (__RCC_PLL1VCIRange__))


/** @brief  Macro to select  the PLL1  reference frequency range.
  * @param  __RCC_PLL1VCORange__: specifies the PLL1 input frequency range
  *         This parameter can be one of the following values:
  *            @arg RCC_PLL1VCOWIDE: Range frequency is between 192 and 836 MHz or between 128 to 560 MHz(*)
  *            @arg RCC_PLL1VCOMEDIUM: Range frequency is between 150 and 420 MHz
  *
  * (*) : For stm32h7a3xx and stm32h7b3xx family lines.
  *
  * @retval None
  */
#define __HAL_RCC_PLL_VCORANGE(__RCC_PLL1VCORange__) \
                  modify_reg(RCC->PLLCFGR, RCC_PLLCFGR_PLL1VCOSEL, (__RCC_PLL1VCORange__))



/** @brief  Macro to get the clock source used as system clock.
  * @retval The clock source used as system clock. The returned value can be one
  *         of the following:
  *              - RCC_CFGR_SWS_CSI: CSI used as system clock.
  *              - RCC_CFGR_SWS_HSI: HSI used as system clock.
  *              - RCC_CFGR_SWS_HSE: HSE used as system clock.
  *              - RCC_CFGR_SWS_PLL: PLL used as system clock.
  */
static inline auto hal_rcc_get_sysclk_source() -> std::uint32_t
{
  return static_cast<uint32_t>(RCC->CFGR & RCC_CFGR_SWS);
}

/**
  * @brief Macro to configure the system clock source.
  * @param __RCC_SYSCLKSOURCE__: specifies the system clock source.
  * This parameter can be one of the following values:
  *              - RCC_SYSCLKSOURCE_HSI: HSI oscillator is used as system clock source.
  *              - RCC_SYSCLKSOURCE_CSI: CSI oscillator is used as system clock source.
  *              - RCC_SYSCLKSOURCE_HSE: HSE oscillator is used as system clock source.
  *              - RCC_SYSCLKSOURCE_PLLCLK: PLL output is used as system clock source.
  */
#define __HAL_RCC_SYSCLK_CONFIG(__RCC_SYSCLKSOURCE__) modify_reg(RCC->CFGR, RCC_CFGR_SW, (__RCC_SYSCLKSOURCE__))

/** @brief  Macro to get the oscillator used as PLL clock source.
  * @retval The oscillator used as PLL clock source. The returned value can be one
  *         of the following:
  *              - RCC_PLLSOURCE_NONE: No oscillator is used as PLL clock source.
  *              - RCC_PLLSOURCE_CSI: CSI oscillator is used as PLL clock source.
  *              - RCC_PLLSOURCE_HSI: HSI oscillator is used as PLL clock source.
  *              - RCC_PLLSOURCE_HSE: HSE oscillator is used as PLL clock source.
  */
#define __HAL_RCC_GET_PLL_OSCSOURCE() ((uint32_t)(RCC->PLLCKSELR & RCC_PLLCKSELR_PLLSRC))

/** @defgroup RCCEx_MCOx_Clock_Config RCC Extended MCOx Clock Config
  * @{
  */

/** @brief  Macro to configure the MCO1 clock.
  * @param  __MCOCLKSOURCE__ specifies the MCO clock source.
  *          This parameter can be one of the following values:
  *            @arg RCC_MCO1SOURCE_HSI: HSI clock selected as MCO1 source
  *            @arg RCC_MCO1SOURCE_LSE: LSE clock selected as MCO1 source
  *            @arg RCC_MCO1SOURCE_HSE: HSE clock selected as MCO1 source
  *            @arg RCC_MCO1SOURCE_PLL1QCLK:  PLL1Q clock selected as MCO1 source
  *            @arg RCC_MCO1SOURCE_HSI48: HSI48 (48MHZ) selected as MCO1 source
  * @param  __MCODIV__ specifies the MCO clock prescaler.
  *          This parameter can be one of the following values:
  *            @arg RCC_MCODIV_1 up to RCC_MCODIV_15  : divider applied to MCO1 clock
  */
#define __HAL_RCC_MCO1_CONFIG(__MCOCLKSOURCE__, __MCODIV__) \
                 modify_reg(RCC->CFGR, (RCC_CFGR_MCO1 | RCC_CFGR_MCO1PRE), ((__MCOCLKSOURCE__) | (__MCODIV__)))

/** @brief  Macro to configure the MCO2 clock.
  * @param  __MCOCLKSOURCE__ specifies the MCO clock source.
  *          This parameter can be one of the following values:
  *            @arg RCC_MCO2SOURCE_SYSCLK: System clock (SYSCLK) selected as MCO2 source
  *            @arg RCC_MCO2SOURCE_PLL2PCLK: PLL2P clock selected as MCO2 source
  *            @arg RCC_MCO2SOURCE_HSE: HSE clock selected as MCO2 source
  *            @arg RCC_MCO2SOURCE_PLLCLK:  PLL1P clock selected as MCO2 source
  *            @arg RCC_MCO2SOURCE_CSICLK:  CSI clock selected as MCO2 source
  *            @arg RCC_MCO2SOURCE_LSICLK:  LSI clock selected as MCO2 source
  * @param  __MCODIV__ specifies the MCO clock prescaler.
  *          This parameter can be one of the following values:
  *            @arg RCC_MCODIV_1 up to RCC_MCODIV_15  : divider applied to MCO2 clock
  */
#define __HAL_RCC_MCO2_CONFIG(__MCOCLKSOURCE__, __MCODIV__) \
    modify_reg(RCC->CFGR, (RCC_CFGR_MCO2 | RCC_CFGR_MCO2PRE), ((__MCOCLKSOURCE__) | ((__MCODIV__) << 7)));

/**
  * @}
  */

/**
  * @brief  Macro to configure the External Low Speed oscillator (LSE) drive capability.
  * @note   As the LSE is in the Backup domain and write access is denied to
  *         this domain after reset, you have to enable write access using
  *         HAL_PWR_EnableBkUpAccess() function before to configure the LSE
  *         (to be done once after reset).
  * @note   On STM32H7 Rev.B and above devices this can't be updated while LSE is ON.
  * @param  __LSEDRIVE__: specifies the new state of the LSE drive capability.
  *          This parameter can be one of the following values:
  *            @arg RCC_LSEDRIVE_LOW: LSE oscillator low drive capability.
  *            @arg RCC_LSEDRIVE_MEDIUMLOW: LSE oscillator medium low drive capability.
  *            @arg RCC_LSEDRIVE_MEDIUMHIGH: LSE oscillator medium high drive capability.
  *            @arg RCC_LSEDRIVE_HIGH: LSE oscillator high drive capability.
  * @retval None
  */
#if defined(RCC_VER_X)
#define __HAL_RCC_LSEDRIVE_CONFIG(__LSEDRIVE__) \
           do{                                                                                                                                \
             if((HAL_GetREVID() <= REV_ID_Y) && (((__LSEDRIVE__) == RCC_LSEDRIVE_MEDIUMLOW) || ((__LSEDRIVE__) == RCC_LSEDRIVE_MEDIUMHIGH)))  \
             {                                                                                                                                \
              modify_reg(RCC->BDCR, RCC_BDCR_LSEDRV, (~(uint32_t)(__LSEDRIVE__)) & RCC_BDCR_LSEDRV_Msk);                                      \
             }                                                                                                                                \
             else                                                                                                                             \
             {                                                                                                                                \
               modify_reg(RCC->BDCR, RCC_BDCR_LSEDRV, (uint32_t)(__LSEDRIVE__));                                                              \
             }                                                                                                                                \
           } while(0)
#else
#define __HAL_RCC_LSEDRIVE_CONFIG(__LSEDRIVE__) \
               modify_reg(RCC->BDCR, RCC_BDCR_LSEDRV, (uint32_t)(__LSEDRIVE__));
#endif /*RCC_VER_X*/
/**
  * @brief  Macro to configure the wake up from stop clock.
  * @param  __RCC_STOPWUCLK__: specifies the clock source used after wake up from stop
  *         This parameter can be one of the following values:
  *            @arg RCC_STOP_WAKEUPCLOCK_CSI: CSI selected as system clock source
  *            @arg RCC_STOP_WAKEUPCLOCK_HSI: HSI selected as system clock source
  * @retval None
  */
#define __HAL_RCC_WAKEUPSTOP_CLK_CONFIG(__RCC_STOPWUCLK__) \
                  modify_reg(RCC->CFGR, RCC_CFGR_STOPWUCK, (__RCC_STOPWUCLK__))

/**
  * @brief  Macro to configure the Kernel wake up from stop clock.
  * @param  __RCC_STOPKERWUCLK__: specifies the Kernel clock source used after wake up from stop
  *         This parameter can be one of the following values:
  *            @arg RCC_STOP_KERWAKEUPCLOCK_CSI: CSI selected as Kernel clock source
  *            @arg RCC_STOP_KERWAKEUPCLOCK_HSI: HSI selected as Kernel clock source
  * @retval None
  */
#define __HAL_RCC_KERWAKEUPSTOP_CLK_CONFIG(__RCC_STOPKERWUCLK__) \
                  modify_reg(RCC->CFGR, RCC_CFGR_STOPKERWUCK, (__RCC_STOPKERWUCLK__))

/** @defgroup RCC_Flags_Interrupts_Management Flags Interrupts Management
  * @brief macros to manage the specified RCC Flags and interrupts.
  * @{
  */
/** @brief  Enable RCC interrupt.
  * @param  __INTERRUPT__: specifies the RCC interrupt sources to be enabled.
  *         This parameter can be any combination of the following values:
  *            @arg RCC_IT_LSIRDY: LSI ready interrupt
  *            @arg RCC_IT_LSERDY: LSE ready interrupt
  *            @arg RCC_IT_CSIRDY: HSI ready interrupt
  *            @arg RCC_IT_HSIRDY: HSI ready interrupt
  *            @arg RCC_IT_HSERDY: HSE ready interrupt
  *            @arg RCC_IT_HSI48RDY: HSI48 ready interrupt
  *            @arg RCC_IT_PLLRDY: main PLL ready interrupt
  *            @arg RCC_IT_PLL2RDY: PLL2 ready interrupt
  *            @arg RCC_IT_PLL3RDY: PLL3 ready interrupt
  *            @arg RCC_IT_LSECSS: Clock security system interrupt
  */
#define __HAL_RCC_ENABLE_IT(__INTERRUPT__) set_bit(RCC->CIER, (__INTERRUPT__))

/** @brief Disable RCC interrupt
  * @param  __INTERRUPT__: specifies the RCC interrupt sources to be disabled.
  *         This parameter can be any combination of the following values:
  *            @arg RCC_IT_LSIRDY: LSI ready interrupt
  *            @arg RCC_IT_LSERDY: LSE ready interrupt
  *            @arg RCC_IT_CSIRDY: HSI ready interrupt
  *            @arg RCC_IT_HSIRDY: HSI ready interrupt
  *            @arg RCC_IT_HSERDY: HSE ready interrupt
  *            @arg RCC_IT_HSI48RDY: HSI48 ready interrupt
  *            @arg RCC_IT_PLLRDY: main PLL ready interrupt
  *            @arg RCC_IT_PLL2RDY: PLL2 ready interrupt
  *            @arg RCC_IT_PLL3RDY: PLL3 ready interrupt
  *            @arg RCC_IT_LSECSS: Clock security system interrupt
  */
#define __HAL_RCC_DISABLE_IT(__INTERRUPT__) clear_bit(RCC->CIER, (__INTERRUPT__))

/** @brief  Clear the RCC's interrupt pending bits
  * @param  __INTERRUPT__: specifies the interrupt pending bit to clear.
  *         This parameter can be any combination of the following values:
  *            @arg RCC_IT_LSIRDY: LSI ready interrupt
  *            @arg RCC_IT_LSERDY: LSE ready interrupt
  *            @arg RCC_IT_CSIRDY: CSI ready interrupt
  *            @arg RCC_IT_HSIRDY: HSI ready interrupt
  *            @arg RCC_IT_HSERDY: HSE ready interrupt
  *            @arg RCC_IT_HSI48RDY: HSI48 ready interrupt
  *            @arg RCC_IT_PLLRDY: main PLL ready interrupt
  *            @arg RCC_IT_PLL2RDY: PLL2 ready interrupt
  *            @arg RCC_IT_PLL3RDY: PLL3 ready interrupt
  *            @arg RCC_IT_HSECSS: HSE Clock Security interrupt
  *            @arg RCC_IT_LSECSS: Clock security system interrupt
  */
#define __HAL_RCC_CLEAR_IT(__INTERRUPT__) (RCC->CICR = (__INTERRUPT__))

/** @brief  Check the RCC's interrupt has occurred or not.
  * @param  __INTERRUPT__: specifies the RCC interrupt source to check.
  *         This parameter can be any combination of the following values:
  *            @arg RCC_IT_LSIRDY: LSI ready interrupt
  *            @arg RCC_IT_LSERDY: LSE ready interrupt
  *            @arg RCC_IT_CSIRDY: CSI ready interrupt
  *            @arg RCC_IT_HSIRDY: HSI ready interrupt
  *            @arg RCC_IT_HSERDY: HSE ready interrupt
  *            @arg RCC_IT_HSI48RDY: HSI48 ready interrupt
  *            @arg RCC_IT_PLLRDY: main PLL ready interrupt
  *            @arg RCC_IT_PLL2RDY: PLL2 ready interrupt
  *            @arg RCC_IT_PLL3RDY: PLL3 ready interrupt
  *            @arg RCC_IT_HSECSS: HSE Clock Security interrupt
  *            @arg RCC_IT_LSECSS: Clock security system interrupt
  * @retval The new state of __INTERRUPT__ (TRUE or FALSE).
  */
#define __HAL_RCC_GET_IT(__INTERRUPT__) ((RCC->CIFR & (__INTERRUPT__)) == (__INTERRUPT__))

/** @brief Set RMVF bit to clear the reset flags.
  */
#define __HAL_RCC_CLEAR_RESET_FLAGS() (RCC->RSR |= RCC_RSR_RMVF)

#if defined(DUAL_CORE)
#define __HAL_RCC_C1_CLEAR_RESET_FLAGS() (RCC_C1->RSR |= RCC_RSR_RMVF)

#define __HAL_RCC_C2_CLEAR_RESET_FLAGS() (RCC_C2->RSR |= RCC_RSR_RMVF)
#endif /*DUAL_CORE*/

static inline auto hal_rcc_get_flag(const std::uint32_t flag_in) -> std::uint32_t
{
  // Check RCC flag is set or not.
  constexpr auto RCC_FLAG_MASK = static_cast<std::uint32_t>(UINT8_C(0x1F));

  const auto flag = static_cast<std::uint32_t>((flag_in) >> 5U);

  return (((((flag == 1U) ? RCC->CR  : ((flag == 2U) ? RCC->BDCR :
            ((flag == 3U) ? RCC->CSR : ((flag == 4U) ? RCC->RSR  : RCC->CIFR)))) & (1UL << (flag_in & RCC_FLAG_MASK))) != 0U) ? 1U : 0U);
}

/**
  * @}
  */

#define RCC_GET_PLL_OSCSOURCE() ((RCC->PLLCKSELR & RCC_PLLCKSELR_PLLSRC) >> RCC_PLLCKSELR_PLLSRC_Pos)

/* Initialization and de-initialization functions  ******************************/
HAL_StatusTypeDef HAL_RCC_OscConfig  (const RCC_OscInitTypeDef* RCC_OscInitStruct);
HAL_StatusTypeDef HAL_RCC_ClockConfig(RCC_ClkInitTypeDef *RCC_ClkInitStruct, uint32_t FLatency);

/**
  * @}
  */

/** @addtogroup RCC_Exported_Functions_Group2
  * @{
  */
/* Peripheral Control functions  ************************************************/
void     HAL_RCC_MCOConfig(uint32_t RCC_MCOx, uint32_t RCC_MCOSource, uint32_t RCC_MCODiv);
void     HAL_RCC_EnableCSS(void);
void     HAL_RCC_DisableCSS(void);
uint32_t HAL_RCC_GetSysClockFreq(void);
uint32_t HAL_RCC_GetHCLKFreq(void);
uint32_t HAL_RCC_GetPCLK1Freq(void);
uint32_t HAL_RCC_GetPCLK2Freq(void);
void     HAL_RCC_GetOscConfig(RCC_OscInitTypeDef *RCC_OscInitStruct);
void     HAL_RCC_GetClockConfig(RCC_ClkInitTypeDef *RCC_ClkInitStruct, uint32_t *pFLatency);
/* CSS NMI IRQ handler */
void     HAL_RCC_NMI_IRQHandler(void);
/* User Callbacks in non blocking mode (IT mode) */
void     HAL_RCC_CCSCallback(void);

/**
  * @}
  */

/**
  * @}
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/** @defgroup RCC_Private_Constants RCC Private Constants
  * @{
  */

#define HSE_TIMEOUT_VALUE          HSE_STARTUP_TIMEOUT
#define HSI_TIMEOUT_VALUE          (2U)    /* 2 ms */
#define HSI48_TIMEOUT_VALUE        (2U)    /* 2 ms */
#define CSI_TIMEOUT_VALUE          (2U)    /* 2 ms */
#define LSI_TIMEOUT_VALUE          (2U)    /* 2 ms */
#define PLL_TIMEOUT_VALUE          (2U)    /* 2 ms */
#define CLOCKSWITCH_TIMEOUT_VALUE  (5000U) /* 5 s  */
#define RCC_DBP_TIMEOUT_VALUE      (100U)
#define RCC_LSE_TIMEOUT_VALUE      LSE_STARTUP_TIMEOUT

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @addtogroup RCC_Private_Macros RCC Private Macros
  * @{
  */

/** @defgroup RCC_IS_RCC_Definitions RCC Private macros to check input parameters
  * @{
  */

#define IS_RCC_OSCILLATORTYPE(OSCILLATOR) (((OSCILLATOR) == RCC_OSCILLATORTYPE_NONE)                           || \
                                           (((OSCILLATOR) & RCC_OSCILLATORTYPE_HSE) == RCC_OSCILLATORTYPE_HSE) || \
                                           (((OSCILLATOR) & RCC_OSCILLATORTYPE_HSI) == RCC_OSCILLATORTYPE_HSI) || \
                                           (((OSCILLATOR) & RCC_OSCILLATORTYPE_CSI) == RCC_OSCILLATORTYPE_CSI) || \
                                           (((OSCILLATOR) & RCC_OSCILLATORTYPE_LSI) == RCC_OSCILLATORTYPE_LSI) || \
                                           (((OSCILLATOR) & RCC_OSCILLATORTYPE_LSE) == RCC_OSCILLATORTYPE_LSE) || \
                                           (((OSCILLATOR) & RCC_OSCILLATORTYPE_HSI48) == RCC_OSCILLATORTYPE_HSI48))

#if defined(RCC_CR_HSEEXT)
#define IS_RCC_HSE(HSE) (((HSE) == RCC_HSE_OFF) || ((HSE) == RCC_HSE_ON) || \
                         ((HSE) == RCC_HSE_BYPASS) || ((HSE) == RCC_HSE_BYPASS_DIGITAL))
#else
#define IS_RCC_HSE(HSE) (((HSE) == RCC_HSE_OFF) || ((HSE) == RCC_HSE_ON) || \
                         ((HSE) == RCC_HSE_BYPASS))
#endif /* RCC_CR_HSEEXT */

#if defined(RCC_BDCR_LSEEXT)
#define IS_RCC_LSE(LSE) (((LSE) == RCC_LSE_OFF) || ((LSE) == RCC_LSE_ON) || \
                         ((LSE) == RCC_LSE_BYPASS) || ((LSE) == RCC_LSE_BYPASS_DIGITAL))
#else
#define IS_RCC_LSE(LSE) (((LSE) == RCC_LSE_OFF) || ((LSE) == RCC_LSE_ON) || \
                         ((LSE) == RCC_LSE_BYPASS))
#endif /* RCC_BDCR_LSEEXT */

#define IS_RCC_HSI(HSI) (((HSI) == RCC_HSI_OFF) || ((HSI) == RCC_HSI_ON)    || \
                         ((HSI) == RCC_HSI_DIV1) || ((HSI) == RCC_HSI_DIV2) || \
                         ((HSI) == RCC_HSI_DIV4) || ((HSI) == RCC_HSI_DIV8))

#define IS_RCC_HSI48(HSI48) (((HSI48) == RCC_HSI48_OFF) || ((HSI48) == RCC_HSI48_ON))

#define IS_RCC_LSI(LSI) (((LSI) == RCC_LSI_OFF) || ((LSI) == RCC_LSI_ON))

#define IS_RCC_CSI(CSI) (((CSI) == RCC_CSI_OFF) || ((CSI) == RCC_CSI_ON))

#define IS_RCC_PLL(PLL) (((PLL) == RCC_PLL_NONE) ||((PLL) == RCC_PLL_OFF) || \
                         ((PLL) == RCC_PLL_ON))

#define IS_RCC_PLLSOURCE(SOURCE) (((SOURCE) == RCC_PLLSOURCE_CSI)  || \
                                  ((SOURCE) == RCC_PLLSOURCE_HSI)  || \
                                  ((SOURCE) == RCC_PLLSOURCE_NONE) || \
                                  ((SOURCE) == RCC_PLLSOURCE_HSE))

#define IS_RCC_PLLRGE_VALUE(VALUE) (((VALUE) == RCC_PLL1VCIRANGE_0) || \
                                    ((VALUE) == RCC_PLL1VCIRANGE_1) || \
                                    ((VALUE) == RCC_PLL1VCIRANGE_2) || \
                                    ((VALUE) == RCC_PLL1VCIRANGE_3))

#define IS_RCC_PLLVCO_VALUE(VALUE) (((VALUE) == RCC_PLL1VCOWIDE) || ((VALUE) == RCC_PLL1VCOMEDIUM))

#define IS_RCC_PLLFRACN_VALUE(VALUE) ((VALUE) <= 8191U)

#define IS_RCC_PLLM_VALUE(VALUE) ((1U <= (VALUE)) && ((VALUE) <= 63U))
#if !defined(RCC_VER_2_0)
#define IS_RCC_PLLN_VALUE(VALUE) ((4U <= (VALUE)) && ((VALUE) <= 512U))
#else
#define IS_RCC_PLLN_VALUE(VALUE) ((8U <= (VALUE)) && ((VALUE) <= 420U))
#endif /* !RCC_VER_2_0 */
#define IS_RCC_PLLP_VALUE(VALUE) ((1U <= (VALUE)) && ((VALUE) <= 128U))
#define IS_RCC_PLLQ_VALUE(VALUE) ((1U <= (VALUE)) && ((VALUE) <= 128U))
#define IS_RCC_PLLR_VALUE(VALUE) ((1U <= (VALUE)) && ((VALUE) <= 128U))

#define IS_RCC_PLLCLOCKOUT_VALUE(VALUE) (((VALUE) == RCC_PLL1_DIVP) || \
                                         ((VALUE) == RCC_PLL1_DIVQ) || \
                                         ((VALUE) == RCC_PLL1_DIVR))

#define IS_RCC_CLOCKTYPE(CLK) ((1U <= (CLK)) && ((CLK) <= 0x3FU))

#define IS_RCC_SYSCLKSOURCE(SOURCE) (((SOURCE) == RCC_SYSCLKSOURCE_CSI) || \
                                     ((SOURCE) == RCC_SYSCLKSOURCE_HSI) || \
                                     ((SOURCE) == RCC_SYSCLKSOURCE_HSE) || \
                                     ((SOURCE) == RCC_SYSCLKSOURCE_PLLCLK))

#define IS_RCC_SYSCLK(SYSCLK) (((SYSCLK) == RCC_SYSCLK_DIV1)   || ((SYSCLK) == RCC_SYSCLK_DIV2)   || \
                               ((SYSCLK) == RCC_SYSCLK_DIV4)   || ((SYSCLK) == RCC_SYSCLK_DIV8)   || \
                               ((SYSCLK) == RCC_SYSCLK_DIV16)  || ((SYSCLK) == RCC_SYSCLK_DIV64)  || \
                               ((SYSCLK) == RCC_SYSCLK_DIV128) || ((SYSCLK) == RCC_SYSCLK_DIV256) || \
                               ((SYSCLK) == RCC_SYSCLK_DIV512))


#define IS_RCC_HCLK(HCLK) (((HCLK) == RCC_HCLK_DIV1)   || ((HCLK) == RCC_HCLK_DIV2)   || \
                           ((HCLK) == RCC_HCLK_DIV4)   || ((HCLK) == RCC_HCLK_DIV8)   || \
                           ((HCLK) == RCC_HCLK_DIV16)  || ((HCLK) == RCC_HCLK_DIV64)  || \
                           ((HCLK) == RCC_HCLK_DIV128) || ((HCLK) == RCC_HCLK_DIV256) || \
                           ((HCLK) == RCC_HCLK_DIV512))

#define IS_RCC_CDPCLK1(CDPCLK1) (((CDPCLK1) == RCC_APB3_DIV1) || ((CDPCLK1) == RCC_APB3_DIV2) || \
                                 ((CDPCLK1) == RCC_APB3_DIV4) || ((CDPCLK1) == RCC_APB3_DIV8) || \
                                 ((CDPCLK1) == RCC_APB3_DIV16))

#define IS_RCC_D1PCLK1 IS_RCC_CDPCLK1  /* for legacy compatibility between H7 lines */

#define IS_RCC_PCLK1(PCLK1) (((PCLK1) == RCC_APB1_DIV1) || ((PCLK1) == RCC_APB1_DIV2) || \
                             ((PCLK1) == RCC_APB1_DIV4) || ((PCLK1) == RCC_APB1_DIV8) || \
                            ((PCLK1) == RCC_APB1_DIV16))

#define IS_RCC_PCLK2(PCLK2) (((PCLK2) == RCC_APB2_DIV1) || ((PCLK2) == RCC_APB2_DIV2) || \
                             ((PCLK2) == RCC_APB2_DIV4) || ((PCLK2) == RCC_APB2_DIV8) || \
                             ((PCLK2) == RCC_APB2_DIV16))

#define IS_RCC_SRDPCLK1(SRDPCLK1) (((SRDPCLK1) == RCC_APB4_DIV1) || ((SRDPCLK1) == RCC_APB4_DIV2) || \
                                  ((SRDPCLK1) == RCC_APB4_DIV4)  || ((SRDPCLK1) == RCC_APB4_DIV8) || \
                                  ((SRDPCLK1) == RCC_APB4_DIV16))

#define IS_RCC_D3PCLK1 IS_RCC_SRDPCLK1 /* for legacy compatibility between H7 lines*/

#define IS_RCC_RTCCLKSOURCE(SOURCE) (((SOURCE) == RCC_RTCCLKSOURCE_LSE)       || ((SOURCE) == RCC_RTCCLKSOURCE_LSI)       || \
                                     ((SOURCE) == RCC_RTCCLKSOURCE_HSE_DIV2)  || ((SOURCE) == RCC_RTCCLKSOURCE_HSE_DIV3)  || \
                                     ((SOURCE) == RCC_RTCCLKSOURCE_HSE_DIV4)  || ((SOURCE) == RCC_RTCCLKSOURCE_HSE_DIV5)  || \
                                     ((SOURCE) == RCC_RTCCLKSOURCE_HSE_DIV6)  || ((SOURCE) == RCC_RTCCLKSOURCE_HSE_DIV7)  || \
                                     ((SOURCE) == RCC_RTCCLKSOURCE_HSE_DIV8)  || ((SOURCE) == RCC_RTCCLKSOURCE_HSE_DIV9)  || \
                                     ((SOURCE) == RCC_RTCCLKSOURCE_HSE_DIV10) || ((SOURCE) == RCC_RTCCLKSOURCE_HSE_DIV11) || \
                                     ((SOURCE) == RCC_RTCCLKSOURCE_HSE_DIV12) || ((SOURCE) == RCC_RTCCLKSOURCE_HSE_DIV13) || \
                                     ((SOURCE) == RCC_RTCCLKSOURCE_HSE_DIV14) || ((SOURCE) == RCC_RTCCLKSOURCE_HSE_DIV15) || \
                                     ((SOURCE) == RCC_RTCCLKSOURCE_HSE_DIV16) || ((SOURCE) == RCC_RTCCLKSOURCE_HSE_DIV17) || \
                                     ((SOURCE) == RCC_RTCCLKSOURCE_HSE_DIV18) || ((SOURCE) == RCC_RTCCLKSOURCE_HSE_DIV19) || \
                                     ((SOURCE) == RCC_RTCCLKSOURCE_HSE_DIV20) || ((SOURCE) == RCC_RTCCLKSOURCE_HSE_DIV21) || \
                                     ((SOURCE) == RCC_RTCCLKSOURCE_HSE_DIV22) || ((SOURCE) == RCC_RTCCLKSOURCE_HSE_DIV23) || \
                                     ((SOURCE) == RCC_RTCCLKSOURCE_HSE_DIV24) || ((SOURCE) == RCC_RTCCLKSOURCE_HSE_DIV25) || \
                                     ((SOURCE) == RCC_RTCCLKSOURCE_HSE_DIV26) || ((SOURCE) == RCC_RTCCLKSOURCE_HSE_DIV27) || \
                                     ((SOURCE) == RCC_RTCCLKSOURCE_HSE_DIV28) || ((SOURCE) == RCC_RTCCLKSOURCE_HSE_DIV29) || \
                                     ((SOURCE) == RCC_RTCCLKSOURCE_HSE_DIV30) || ((SOURCE) == RCC_RTCCLKSOURCE_HSE_DIV31) || \
                                     ((SOURCE) == RCC_RTCCLKSOURCE_HSE_DIV32) || ((SOURCE) == RCC_RTCCLKSOURCE_HSE_DIV33) || \
                                     ((SOURCE) == RCC_RTCCLKSOURCE_HSE_DIV34) || ((SOURCE) == RCC_RTCCLKSOURCE_HSE_DIV35) || \
                                     ((SOURCE) == RCC_RTCCLKSOURCE_HSE_DIV36) || ((SOURCE) == RCC_RTCCLKSOURCE_HSE_DIV37) || \
                                     ((SOURCE) == RCC_RTCCLKSOURCE_HSE_DIV38) || ((SOURCE) == RCC_RTCCLKSOURCE_HSE_DIV39) || \
                                     ((SOURCE) == RCC_RTCCLKSOURCE_HSE_DIV40) || ((SOURCE) == RCC_RTCCLKSOURCE_HSE_DIV41) || \
                                     ((SOURCE) == RCC_RTCCLKSOURCE_HSE_DIV42) || ((SOURCE) == RCC_RTCCLKSOURCE_HSE_DIV43) || \
                                     ((SOURCE) == RCC_RTCCLKSOURCE_HSE_DIV44) || ((SOURCE) == RCC_RTCCLKSOURCE_HSE_DIV45) || \
                                     ((SOURCE) == RCC_RTCCLKSOURCE_HSE_DIV46) || ((SOURCE) == RCC_RTCCLKSOURCE_HSE_DIV47) || \
                                     ((SOURCE) == RCC_RTCCLKSOURCE_HSE_DIV48) || ((SOURCE) == RCC_RTCCLKSOURCE_HSE_DIV49) || \
                                     ((SOURCE) == RCC_RTCCLKSOURCE_HSE_DIV50) || ((SOURCE) == RCC_RTCCLKSOURCE_HSE_DIV51) || \
                                     ((SOURCE) == RCC_RTCCLKSOURCE_HSE_DIV52) || ((SOURCE) == RCC_RTCCLKSOURCE_HSE_DIV53) || \
                                     ((SOURCE) == RCC_RTCCLKSOURCE_HSE_DIV54) || ((SOURCE) == RCC_RTCCLKSOURCE_HSE_DIV55) || \
                                     ((SOURCE) == RCC_RTCCLKSOURCE_HSE_DIV56) || ((SOURCE) == RCC_RTCCLKSOURCE_HSE_DIV57) || \
                                     ((SOURCE) == RCC_RTCCLKSOURCE_HSE_DIV58) || ((SOURCE) == RCC_RTCCLKSOURCE_HSE_DIV59) || \
                                     ((SOURCE) == RCC_RTCCLKSOURCE_HSE_DIV60) || ((SOURCE) == RCC_RTCCLKSOURCE_HSE_DIV61) || \
                                     ((SOURCE) == RCC_RTCCLKSOURCE_HSE_DIV62) || ((SOURCE) == RCC_RTCCLKSOURCE_HSE_DIV63))

#define IS_RCC_MCO(MCOx) (((MCOx) == RCC_MCO1) || ((MCOx) == RCC_MCO2))

#define IS_RCC_MCO1SOURCE(SOURCE) (((SOURCE) == RCC_MCO1SOURCE_HSI) || ((SOURCE) == RCC_MCO1SOURCE_LSE)       || \
                                   ((SOURCE) == RCC_MCO1SOURCE_HSE) || ((SOURCE) == RCC_MCO1SOURCE_PLL1QCLK)  || \
                                   ((SOURCE) == RCC_MCO1SOURCE_HSI48))

#define IS_RCC_MCO2SOURCE(SOURCE) (((SOURCE) == RCC_MCO2SOURCE_SYSCLK)    || ((SOURCE) == RCC_MCO2SOURCE_PLL2PCLK) || \
                                   ((SOURCE) == RCC_MCO2SOURCE_HSE)       || ((SOURCE) == RCC_MCO2SOURCE_PLLCLK)   || \
                                   ((SOURCE) == RCC_MCO2SOURCE_CSICLK)    || ((SOURCE) == RCC_MCO2SOURCE_LSICLK))

#define IS_RCC_MCODIV(DIV) (((DIV) == RCC_MCODIV_1)  || ((DIV) == RCC_MCODIV_2)   || \
                            ((DIV) == RCC_MCODIV_3)  || ((DIV) == RCC_MCODIV_4)   || \
                            ((DIV) == RCC_MCODIV_5)  || ((DIV) == RCC_MCODIV_6)   || \
                            ((DIV) == RCC_MCODIV_7)  || ((DIV) == RCC_MCODIV_8)   || \
                            ((DIV) == RCC_MCODIV_9)  || ((DIV) == RCC_MCODIV_10)  || \
                            ((DIV) == RCC_MCODIV_11) || ((DIV) == RCC_MCODIV_12)  || \
                            ((DIV) == RCC_MCODIV_13) || ((DIV) == RCC_MCODIV_14)  || \
                            ((DIV) == RCC_MCODIV_15))

#define IS_RCC_HSICALIBRATION_VALUE(VALUE) ((VALUE) <= 0x7FU)
#define IS_RCC_CSICALIBRATION_VALUE(VALUE) ((VALUE) <= 0x3FU)

#endif // STM32H7XX_HAL_RCC_2022_08_05_H_
