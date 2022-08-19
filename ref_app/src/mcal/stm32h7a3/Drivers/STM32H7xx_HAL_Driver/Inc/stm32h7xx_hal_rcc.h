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
    std::uint32_t      OscillatorType;       // The oscillators to be configured.
    std::uint32_t      HSEState;             // The new state of the HSE.
    std::uint32_t      LSEState;             // The new state of the LSE.
    std::uint32_t      HSIState;             // The new state of the HSI.
    std::uint32_t      HSICalibrationValue;  // The calibration trimming value.
    std::uint32_t      LSIState;             // The new state of the LSI.
    std::uint32_t      HSI48State;           // The new state of the HSI48.
    std::uint32_t      CSIState;             // The new state of the CSI.
    std::uint32_t      CSICalibrationValue;  // The calibration trimming value.
    RCC_PLLInitTypeDef PLL;                  // PLL structure parameters
  }
  RCC_OscInitTypeDef;

  typedef struct
  {
    std::uint32_t ClockType;      // The clock to be configured.
    std::uint32_t SYSCLKSource;   // The clock source (SYSCLKS) used as system clock.
    std::uint32_t SYSCLKDivider;  // The system clock  divider. This parameter can be
    std::uint32_t AHBCLKDivider;  // The AHB clock (HCLK) divider. This clock is derived from the system clock (SYSCLK).
    std::uint32_t APB3CLKDivider; // The APB3 clock (D1PCLK1) divider. This clock is derived from the AHB clock (HCLK).
    std::uint32_t APB1CLKDivider; // The APB1 clock (PCLK1) divider. This clock is derived from the AHB clock (HCLK).
    std::uint32_t APB2CLKDivider; // The APB2 clock (PCLK2) divider. This clock is derived from the AHB clock (HCLK).
    std::uint32_t APB4CLKDivider; // The APB4 clock (D3PCLK1) divider. This clock is derived from the AHB clock (HCLK).
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
  #define RCC_HSI_OFF                    (0x00000000U)
  #define RCC_HSI_ON                     RCC_CR_HSION
  #define RCC_HSI_DIV1                   (RCC_CR_HSIDIV_1 | RCC_CR_HSION)
  #define RCC_HSI_DIV2                   (RCC_CR_HSIDIV_2 | RCC_CR_HSION)
  #define RCC_HSI_DIV4                   (RCC_CR_HSIDIV_4 | RCC_CR_HSION)
  #define RCC_HSI_DIV8                   (RCC_CR_HSIDIV | RCC_CR_HSION)
  #define RCC_HSICALIBRATION_DEFAULT     (0x40U)
  #define RCC_HSI48_OFF                  (static_cast<std::uint8_t>(UINT8_C(0x00)))
  #define RCC_HSI48_ON                   (static_cast<std::uint8_t>(UINT8_C(0x01)))

  #define RCC_LSI_OFF                    (0x00000000U)
  #define RCC_LSI_ON                     RCC_CSR_LSION
  #define RCC_CSI_OFF                    (0x00000000U)
  #define RCC_CSI_ON                     RCC_CR_CSION
  #define RCC_CSICALIBRATION_DEFAULT     (0x20U)

  #define RCC_PLL_NONE                   (0x00000000U)
  #define RCC_PLL_OFF                    (0x00000001U)
  #define RCC_PLL_ON                     (0x00000002U)

  // RCC_PLL_Clock_Source  RCC PLL Clock Source
  #define RCC_PLLSOURCE_HSI              (0x00000000U)
  #define RCC_PLLSOURCE_CSI              (0x00000001U)
  #define RCC_PLLSOURCE_HSE              (0x00000002U)
  #define RCC_PLLSOURCE_NONE             (0x00000003U)

  // RCC_PLL_Clock_Output  RCC PLL Clock Output
  #define RCC_PLL1_DIVP                  RCC_PLLCFGR_DIVP1EN
  #define RCC_PLL1_DIVQ                  RCC_PLLCFGR_DIVQ1EN
  #define RCC_PLL1_DIVR                  RCC_PLLCFGR_DIVR1EN

  // RCC_PLL1_VCI_Range  RCC PLL1 VCI Range
  #define RCC_PLL1VCIRANGE_0             RCC_PLLCFGR_PLL1RGE_0
  #define RCC_PLL1VCIRANGE_1             RCC_PLLCFGR_PLL1RGE_1
  #define RCC_PLL1VCIRANGE_2             RCC_PLLCFGR_PLL1RGE_2
  #define RCC_PLL1VCIRANGE_3             RCC_PLLCFGR_PLL1RGE_3

  // RCC_PLL1_VCO_Range  RCC PLL1 VCO Range
  #define RCC_PLL1VCOWIDE                (0x00000000U)
  #define RCC_PLL1VCOMEDIUM              RCC_PLLCFGR_PLL1VCOSEL

  // RCC_System_Clock_Type  RCC System Clock Type
  #define RCC_CLOCKTYPE_SYSCLK           (0x00000001U)
  #define RCC_CLOCKTYPE_HCLK             (0x00000002U)
  #define RCC_CLOCKTYPE_D1PCLK1          (0x00000004U)
  #define RCC_CLOCKTYPE_PCLK1            (0x00000008U)
  #define RCC_CLOCKTYPE_PCLK2            (0x00000010U)
  #define RCC_CLOCKTYPE_D3PCLK1          (0x00000020U)

  // RCC_System_Clock_Source  RCC System Clock Source
  #define RCC_SYSCLKSOURCE_CSI           RCC_CFGR_SW_CSI
  #define RCC_SYSCLKSOURCE_HSI           RCC_CFGR_SW_HSI
  #define RCC_SYSCLKSOURCE_HSE           RCC_CFGR_SW_HSE
  #define RCC_SYSCLKSOURCE_PLLCLK        RCC_CFGR_SW_PLL1

  // RCC_System_Clock_Source_Status System Clock Source Status
  #define RCC_SYSCLKSOURCE_STATUS_CSI    RCC_CFGR_SWS_CSI
  #define RCC_SYSCLKSOURCE_STATUS_HSI    RCC_CFGR_SWS_HSI
  #define RCC_SYSCLKSOURCE_STATUS_HSE    RCC_CFGR_SWS_HSE
  #define RCC_SYSCLKSOURCE_STATUS_PLLCLK RCC_CFGR_SWS_PLL1

  // RCC_SYS_Clock_Source  RCC SYS Clock Source
  #define RCC_SYSCLK_DIV1                RCC_CDCFGR1_CDCPRE_DIV1
  #define RCC_SYSCLK_DIV2                RCC_CDCFGR1_CDCPRE_DIV2
  #define RCC_SYSCLK_DIV4                RCC_CDCFGR1_CDCPRE_DIV4
  #define RCC_SYSCLK_DIV8                RCC_CDCFGR1_CDCPRE_DIV8
  #define RCC_SYSCLK_DIV16               RCC_CDCFGR1_CDCPRE_DIV16
  #define RCC_SYSCLK_DIV64               RCC_CDCFGR1_CDCPRE_DIV64
  #define RCC_SYSCLK_DIV128              RCC_CDCFGR1_CDCPRE_DIV128
  #define RCC_SYSCLK_DIV256              RCC_CDCFGR1_CDCPRE_DIV256
  #define RCC_SYSCLK_DIV512              RCC_CDCFGR1_CDCPRE_DIV512

  // RCC_HCLK_Clock_Source  RCC HCLK Clock Source
  #define RCC_HCLK_DIV1                  RCC_CDCFGR1_HPRE_DIV1
  #define RCC_HCLK_DIV2                  RCC_CDCFGR1_HPRE_DIV2
  #define RCC_HCLK_DIV4                  RCC_CDCFGR1_HPRE_DIV4
  #define RCC_HCLK_DIV8                  RCC_CDCFGR1_HPRE_DIV8
  #define RCC_HCLK_DIV16                 RCC_CDCFGR1_HPRE_DIV16
  #define RCC_HCLK_DIV64                 RCC_CDCFGR1_HPRE_DIV64
  #define RCC_HCLK_DIV128                RCC_CDCFGR1_HPRE_DIV128
  #define RCC_HCLK_DIV256                RCC_CDCFGR1_HPRE_DIV256
  #define RCC_HCLK_DIV512                RCC_CDCFGR1_HPRE_DIV512

  // RCC_APB3_Clock_Source  RCC APB3 Clock Source
  #define RCC_APB3_DIV1                  RCC_CDCFGR1_CDPPRE_DIV1
  #define RCC_APB3_DIV2                  RCC_CDCFGR1_CDPPRE_DIV2
  #define RCC_APB3_DIV4                  RCC_CDCFGR1_CDPPRE_DIV4
  #define RCC_APB3_DIV8                  RCC_CDCFGR1_CDPPRE_DIV8
  #define RCC_APB3_DIV16                 RCC_CDCFGR1_CDPPRE_DIV16

  // RCC_APB1_Clock_Source  RCC APB1 Clock Source
  #define RCC_APB1_DIV1                  RCC_CDCFGR2_CDPPRE1_DIV1
  #define RCC_APB1_DIV2                  RCC_CDCFGR2_CDPPRE1_DIV2
  #define RCC_APB1_DIV4                  RCC_CDCFGR2_CDPPRE1_DIV4
  #define RCC_APB1_DIV8                  RCC_CDCFGR2_CDPPRE1_DIV8
  #define RCC_APB1_DIV16                 RCC_CDCFGR2_CDPPRE1_DIV16

  // RCC_APB2_Clock_Source  RCC APB2 Clock Source
  #define RCC_APB2_DIV1                  RCC_CDCFGR2_CDPPRE2_DIV1
  #define RCC_APB2_DIV2                  RCC_CDCFGR2_CDPPRE2_DIV2
  #define RCC_APB2_DIV4                  RCC_CDCFGR2_CDPPRE2_DIV4
  #define RCC_APB2_DIV8                  RCC_CDCFGR2_CDPPRE2_DIV8
  #define RCC_APB2_DIV16                 RCC_CDCFGR2_CDPPRE2_DIV16

  // RCC_APB4_Clock_Source  RCC APB4 Clock Source
  #define RCC_APB4_DIV1                  RCC_SRDCFGR_SRDPPRE_DIV1
  #define RCC_APB4_DIV2                  RCC_SRDCFGR_SRDPPRE_DIV2
  #define RCC_APB4_DIV4                  RCC_SRDCFGR_SRDPPRE_DIV4
  #define RCC_APB4_DIV8                  RCC_SRDCFGR_SRDPPRE_DIV8
  #define RCC_APB4_DIV16                 RCC_SRDCFGR_SRDPPRE_DIV16

  // Flags in the CR register
  #define RCC_FLAG_HSIRDY                (0x22)
  #define RCC_FLAG_HSIDIV                (0x25)
  #define RCC_FLAG_CSIRDY                (0x28)
  #define RCC_FLAG_HSI48RDY              (0x2D)
  #define RCC_FLAG_CPUCKRDY              (0x2E)
  #define RCC_FLAG_D1CKRDY               RCC_FLAG_CPUCKRDY
  #define RCC_FLAG_CDCKRDY               (0x2F)
  #define RCC_FLAG_D2CKRDY               RCC_FLAG_CDCKRDY
  #define RCC_FLAG_HSERDY                (0x31)
  #define RCC_FLAG_PLLRDY                (0x39)
  #define RCC_FLAG_PLL2RDY               (0x3B)
  #define RCC_FLAG_PLL3RDY               (0x3D)

  // Flags in the BDCR register
  #define RCC_FLAG_LSERDY                (0x41)

  // Flags in the CSR register
  #define RCC_FLAG_LSIRDY                (0x61)

  // Macro to enable or disable the Internal High Speed oscillator (HSI).
  static inline auto hal_rcc_hsi_config(const std::uint32_t state) -> void
  {
    modify_reg
    (
      RCC->CR,
      static_cast<std::uint32_t>(RCC_CR_HSION | RCC_CR_HSIDIV),
      state
    );
  }

  // Enable or disable the Internal High Speed oscillator (HSI).
  static inline auto hal_rcc_hsi_enable () -> void { set_bit  (RCC->CR, static_cast<std::uint32_t>(RCC_CR_HSION)); }
  static inline auto hal_rcc_hsi_disable() -> void { clear_bit(RCC->CR, static_cast<std::uint32_t>(RCC_CR_HSION)); }

  static inline auto hal_rcc_hsi_calibration_value_adjust(const std::uint32_t HSICalibrationValue) -> void
  {
    // Adjust the Internal High Speed oscillator (HSI) calibration value.
    // The calibration is used to compensate for the variations in voltage
    // and temperature that influence the frequency of the internal HSI RC.
    // HSICalibrationValue: specifies the calibration trimming value.
    // This parameter must be a number between 0 and 0x7F (3F for Rev Y device).

    modify_reg
    (
      RCC->HSICFGR,
      static_cast<std::uint32_t>(RCC_HSICFGR_HSITRIM),
      static_cast<std::uint32_t>(HSICalibrationValue << RCC_HSICFGR_HSITRIM_Pos)
    );
  }

  // Enable or disable the force of the Internal High Speed oscillator (HSI)
  static inline auto hal_rcc_hsistop_enable () -> void { set_bit  (RCC->CR, static_cast<std::uint32_t>(RCC_CR_HSIKERON)); }
  static inline auto hal_rcc_hsistop_disable() -> void { clear_bit(RCC->CR, static_cast<std::uint32_t>(RCC_CR_HSIKERON)); }

  // Enable or disable the Internal High Speed oscillator for USB (HSI48).
  static inline auto hal_rcc_hsi48_enable () -> void { set_bit  (RCC->CR, static_cast<std::uint32_t>(RCC_CR_HSI48ON)); }
  static inline auto hal_rcc_hsi48_disable() -> void { clear_bit(RCC->CR, static_cast<std::uint32_t>(RCC_CR_HSI48ON)); }

  // Enable or disable the Internal  oscillator (CSI).
  static inline auto hal_rcc_csi_enable () -> void { set_bit  (RCC->CR, static_cast<std::uint32_t>(RCC_CR_CSION)); }
  static inline auto hal_rcc_csi_disable() -> void { clear_bit(RCC->CR, static_cast<std::uint32_t>(RCC_CR_CSION)); }

  // Adjusts the Internal  oscillator (CSI) calibration value.
  static inline auto hal_rcc_csi_calibration_value_adjust(const std::uint32_t CSICalibrationValue) -> void
  {
    modify_reg
    (
      RCC->CSICFGR,
      static_cast<std::uint32_t>(RCC_CSICFGR_CSITRIM),
      static_cast<std::uint32_t>(CSICalibrationValue << RCC_CSICFGR_CSITRIM_Pos)
    );
  }

  // Enable or disable the force of the Low-power Internal oscillator (CSI)
  static inline auto hal_rcc_csistop_enable () -> void { set_bit  (RCC->CR, static_cast<std::uint32_t>(RCC_CR_CSIKERON)); }
  static inline auto hal_rcc_csistop_disable() -> void { clear_bit(RCC->CR, static_cast<std::uint32_t>(RCC_CR_CSIKERON)); }

  // Enable or disable the Internal Low Speed oscillator (LSI).
  static inline auto hal_rcc_lsi_enable () -> void { set_bit  (RCC->CSR, static_cast<std::uint32_t>(RCC_CSR_LSION)); }
  static inline auto hal_rcc_lsi_disable() -> void { clear_bit(RCC->CSR, static_cast<std::uint32_t>(RCC_CSR_LSION)); }

  static inline auto hal_rcc_hse_config(const std::uint32_t state) -> void
  {
    // Configure the External High Speed oscillator (HSE).
    if(state == RCC_HSE_ON)
    {
      set_bit(RCC->CR, RCC_CR_HSEON);
    }
    else if(state == RCC_HSE_OFF)
    {
      clear_bit(RCC->CR, RCC_CR_HSEON);
      clear_bit(RCC->CR, RCC_CR_HSEEXT);
      clear_bit(RCC->CR, RCC_CR_HSEBYP);
    }
    else if(state == RCC_HSE_BYPASS)
    {
      set_bit  (RCC->CR, RCC_CR_HSEBYP);
      clear_bit(RCC->CR, RCC_CR_HSEEXT);
      set_bit  (RCC->CR, RCC_CR_HSEON);
    }
    else if(state == RCC_HSE_BYPASS_DIGITAL)
    {
      set_bit(RCC->CR, RCC_CR_HSEBYP);
      set_bit(RCC->CR, RCC_CR_HSEEXT);
      set_bit(RCC->CR, RCC_CR_HSEON);
    }
    else
    {
      clear_bit(RCC->CR, RCC_CR_HSEON); 
      clear_bit(RCC->CR, RCC_CR_HSEBYP);
      clear_bit(RCC->CR, RCC_CR_HSEEXT);
    }
  }

  static inline auto hal_rcc_lse_config(const std::uint32_t state) -> void
  {
    // Configure the External Low Speed oscillator (LSE).
    if(state == RCC_LSE_ON)
    {
      set_bit(RCC->BDCR, RCC_BDCR_LSEON);
    }
    else if(state== RCC_LSE_OFF)
    {
      clear_bit(RCC->BDCR, RCC_BDCR_LSEON);
      clear_bit(RCC->BDCR, RCC_BDCR_LSEBYP);
    }
    else if(state == RCC_LSE_BYPASS)
    {
      set_bit(RCC->BDCR, RCC_BDCR_LSEBYP);
      set_bit(RCC->BDCR, RCC_BDCR_LSEON);
    }
    else
    {
      clear_bit(RCC->BDCR, RCC_BDCR_LSEON);
      clear_bit(RCC->BDCR, RCC_BDCR_LSEBYP);
    }
  }

  // Enable or disable the main PLL.
  static inline auto hal_rcc_pll_enable () -> void { set_bit  (RCC->CR, static_cast<std::uint32_t>(RCC_CR_PLL1ON)); }
  static inline auto hal_rcc_pll_disable() -> void { clear_bit(RCC->CR, static_cast<std::uint32_t>(RCC_CR_PLL1ON)); }

  // Enables or disables each clock output (PLL_P_CLK, PLL_Q_CLK, PLL_R_CLK)
  static inline auto hal_rcc_pllclkout_enable (const std::uint32_t RCC_PLL1ClockOut) -> void { set_bit  (RCC->PLLCFGR, RCC_PLL1ClockOut); }
  static inline auto hal_rcc_pllclkout_disablE(const std::uint32_t RCC_PLL1ClockOut) -> void { clear_bit(RCC->PLLCFGR, RCC_PLL1ClockOut); }

  // Enables or disables fractional part of the Multiplication Factor of PLL1 VCO
  static inline auto hal_rcc_pllfracn_enable () -> void { set_bit  (RCC->PLLCFGR, static_cast<std::uint32_t>(RCC_PLLCFGR_PLL1FRACEN)); }
  static inline auto hal_rcc_pllfracn_disable() -> void { clear_bit(RCC->PLLCFGR, static_cast<std::uint32_t>(RCC_PLLCFGR_PLL1FRACEN)); }

  static inline auto hal_rcc_pll_config(const std::uint32_t RCC_PLLSOURCE,
                                        const std::uint32_t PLLM1,
                                        const std::uint32_t PLLN1,
                                        const std::uint32_t PLLP1,
                                        const std::uint32_t PLLQ1,
                                        const std::uint32_t PLLR1) -> void
  {
    // Configures the main PLL clock source, multiplication and division factors.
    // This function must be used only when the main PLL is disabled.
    //
    // RCC_PLLSOURCE: specifies the PLL entry clock source.
    //  This parameter can be one of the following values:
    //    RCC_PLLSOURCE_CSI: CSI oscillator clock selected as PLL clock entry
    //    RCC_PLLSOURCE_HSI: HSI oscillator clock selected as PLL clock entry
    //    RCC_PLLSOURCE_HSE: HSE oscillator clock selected as PLL clock entry
    // This clock source (RCC_PLLSource) is common for the main PLL1 (main PLL) and PLL2 & PLL3 .
    //
    // PLLM1: specifies the division factor for PLL VCO input clock
    //  This parameter must be a number between 1 and 63.
    // You have to set the PLLM parameter correctly to ensure that the VCO input
    // frequency ranges from 1 to 16 MHz.
    //
    // PLLN1: specifies the multiplication factor for PLL VCO output clock
    //  This parameter must be a number between 4 and 512 or between 8 and 420(*).
    // You have to set the PLLN parameter correctly to ensure that the VCO
    // output frequency is between 150 and 420 MHz (when in medium VCO range) or
    // between 192 and 836 MHZ or between 128 and 560 MHZ(*) (when in wide VCO range)
    //
    // PLLP1: specifies the division factor for system  clock.
    //  This parameter must be a number between 2 or 1(**) and 128 (where odd numbers are not allowed) 
    //
    // PLLQ1: specifies the division factor for peripheral kernel clocks
    //  This parameter must be a number between 1 and 128
    //
    // PLLR1: specifies the division factor for peripheral kernel clocks
    //  This parameter must be a number between 1 and 128
    //
    // To insure an optimal behavior of the PLL when one of the post-divider (DIVP, DIVQ or DIVR)
    // is not used, application shall clear the enable bit (DIVyEN) and assign lowest possible 
    // value to  PLL1P, PLL1Q or PLL1R parameters.
    // None
    //
    // (*) : For stm32h7a3xx and stm32h7b3xx family lines.
    // (**): For stm32h72xxx and stm32h73xxx family lines.

    modify_reg(RCC->PLLCKSELR, (RCC_PLLCKSELR_PLLSRC | RCC_PLLCKSELR_DIVM1), (RCC_PLLSOURCE | (PLLM1 <<4U)));

    const auto val =
      static_cast<std::uint32_t>
      (
          (((PLLN1 - 1U) & RCC_PLL1DIVR_N1) | (((PLLP1 -1U ) << 9U) & RCC_PLL1DIVR_P1)
        | (((PLLQ1 - 1U) << 16U) & RCC_PLL1DIVR_Q1) | (((PLLR1 - 1U) << 24U) & RCC_PLL1DIVR_R1))
      );

    write_reg(RCC->PLL1DIVR , val);
  }

  // configures the main PLL clock Fractional Part Of The Multiplication Factor
  static inline auto hal_rcc_pllfracn_config(const std::uint32_t RCC_PLL1FRACN) -> void
  {
    modify_reg
    (
      RCC->PLL1FRACR,
      static_cast<std::uint32_t>(RCC_PLL1FRACR_FRACN1),
      static_cast<std::uint32_t>(RCC_PLL1FRACN << RCC_PLL1FRACR_FRACN1_Pos)
    );
  }

  // Select  the PLL1  reference frequency range.
  static inline auto hal_rcc_pll_vcirange(const std::uint32_t RCC_PLL1VCIRange) -> void
  {
    modify_reg
    (
      RCC->PLLCFGR,
      static_cast<std::uint32_t>(RCC_PLLCFGR_PLL1RGE),
      RCC_PLL1VCIRange
    );
  }

  // Select  the PLL1  reference frequency range.
  static inline auto hal_rcc_pll_vcorange(const std::uint32_t RCC_PLL1VCORange) -> void
  {
    modify_reg
    (
      RCC->PLLCFGR,
      static_cast<std::uint32_t>(RCC_PLLCFGR_PLL1VCOSEL),
      RCC_PLL1VCORange
    );
  }

  // Get the clock source used as system clock.
  static inline auto hal_rcc_get_sysclk_source() -> std::uint32_t
  {
    return static_cast<uint32_t>(RCC->CFGR & RCC_CFGR_SWS);
  }

  static inline auto hal_rcc_get_flag(const std::uint32_t flag_in) -> std::uint32_t
  {
    // Check RCC flag is set or not.
    constexpr auto RCC_FLAG_MASK = static_cast<std::uint32_t>(UINT8_C(0x1F));

    const auto flag = static_cast<std::uint32_t>((flag_in) >> 5U);

    return (((((flag == 1U) ? RCC->CR  : ((flag == 2U) ? RCC->BDCR :
              ((flag == 3U) ? RCC->CSR : ((flag == 4U) ? RCC->RSR  : RCC->CIFR)))) & (1UL << (flag_in & RCC_FLAG_MASK))) != 0U) ? 1U : 0U);
  }

  // Initialization functions.
  HAL_StatusTypeDef HAL_RCC_OscConfig  (const RCC_OscInitTypeDef* RCC_OscInitStruct);
  HAL_StatusTypeDef HAL_RCC_ClockConfig(const RCC_ClkInitTypeDef* RCC_ClkInitStruct, const uint32_t FLatency);

#endif // STM32H7XX_HAL_RCC_2022_08_05_H_
