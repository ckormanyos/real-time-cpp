/*
  ******************************************************************************
  * @file    stm32h7xx_hal_rcc.c
  * @author  MCD Application Team
  * @brief   RCC HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the Reset and Clock Control (RCC) peripheral:
  *           + Initialization and de-initialization functions
  *           + Peripheral Control functions
  *
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

#include "stm32h7xx_hal.h"

#define MCO1_CLK_ENABLE()     __HAL_RCC_GPIOA_CLK_ENABLE()
#define MCO1_GPIO_PORT        GPIOA
#define MCO1_PIN              GPIO_PIN_8

#define MCO2_CLK_ENABLE()      __HAL_RCC_GPIOC_CLK_ENABLE()
#define MCO2_GPIO_PORT         GPIOC
#define MCO2_PIN               GPIO_PIN_9

HAL_StatusTypeDef HAL_RCC_OscConfig(const RCC_OscInitTypeDef* RCC_OscInitStruct)
{
  // Initializes the RCC Oscillators according to the specified parameters in the
  // RCC_OscInitTypeDef.
  // RCC_OscInitStruct: pointer to an RCC_OscInitTypeDef structure that
  // contains the configuration information for the RCC Oscillators.
  // The PLL is not disabled when used as system clock.
  // Transitions LSE Bypass to LSE On and LSE On to LSE Bypass are not
  // supported by this function. User should request a transition to LSE Off
  // first and then LSE On or LSE Bypass.
  // Transition HSE Bypass to HSE On and HSE On to HSE Bypass are not
  // supported by this function. User should request a transition to HSE Off
  // first and then HSE On or HSE Bypass.

  if(RCC_OscInitStruct == nullptr) { return HAL_ERROR; }

  std::uint32_t temp1_pllckcfg;
  std::uint32_t temp2_pllckcfg;

  // HSE Configuration
  if(((RCC_OscInitStruct->OscillatorType) & RCC_OSCILLATORTYPE_HSE) == RCC_OSCILLATORTYPE_HSE)
  {
    const std::uint32_t temp_sysclksrc = hal_rcc_get_sysclk_source();
    const std::uint32_t temp_pllckselr = RCC->PLLCKSELR;

    // When the HSE is used as system clock or clock source
    // for PLL in these cases HSE will not disabled.

    const auto
      hse_is_system_clock =
      (
           (temp_sysclksrc == RCC_CFGR_SWS_HSE)
        || (
                 (temp_sysclksrc == RCC_CFGR_SWS_PLL1)
             && ((temp_pllckselr & RCC_PLLCKSELR_PLLSRC) == RCC_PLLCKSELR_PLLSRC_HSE)
           )
      );

    if(hse_is_system_clock)
    {
      if((hal_rcc_get_flag(RCC_FLAG_HSERDY) != 0U) && (RCC_OscInitStruct->HSEState == RCC_HSE_OFF))
      {
        return HAL_ERROR;
      }
    }
    else
    {
      // Set the new HSE configuration.
      hal_rcc_hse_config(RCC_OscInitStruct->HSEState);

      // Check the HSE State.
      if(RCC_OscInitStruct->HSEState != RCC_HSE_OFF)
      {
        // Wait until the HSE is ready.
        while(hal_rcc_get_flag(RCC_FLAG_HSERDY) == 0U) { ; }
      }
      else
      {
        // Wait until the HSE is disabled
        while(hal_rcc_get_flag(RCC_FLAG_HSERDY) != 0U) { ; }
      }
    }
  }

  // HSI Configuration
  if(((RCC_OscInitStruct->OscillatorType) & RCC_OSCILLATORTYPE_HSI) == RCC_OSCILLATORTYPE_HSI)
  {
    // When the HSI is used as system clock it will not be disabled.
    const auto temp_sysclksrc = hal_rcc_get_sysclk_source();
    const auto temp_pllckselr = RCC->PLLCKSELR;

    if((temp_sysclksrc == RCC_CFGR_SWS_HSI) || ((temp_sysclksrc == RCC_CFGR_SWS_PLL1) && ((temp_pllckselr & RCC_PLLCKSELR_PLLSRC) == RCC_PLLCKSELR_PLLSRC_HSI)))
    {
      // When the HSI is used as system clock it will not be disabled.
      if((hal_rcc_get_flag(RCC_FLAG_HSIRDY) != 0U) && (RCC_OscInitStruct->HSIState == RCC_HSI_OFF))
      {
        return HAL_ERROR;
      }
      else
      {
          // Otherwise, only HSI division and calibration are allowed.
          // Enable the Internal High Speed oscillator (HSI, HSIDIV2, HSIDIV4, or HSIDIV8).
          hal_rcc_hsi_config(RCC_OscInitStruct->HSIState);

          // Wait until the HSI is ready.
          while(hal_rcc_get_flag(RCC_FLAG_HSIRDY) == 0U) { ; }

         // Adjust the Internal High Speed oscillator (HSI) calibration value.
         hal_rcc_hsi_calibration_value_adjust(RCC_OscInitStruct->HSICalibrationValue);
      }
    }
    else
    {
      /* Check the HSI State */
      if((RCC_OscInitStruct->HSIState)!= RCC_HSI_OFF)
      {
        // Enable the Internal High Speed oscillator (HSI, HSIDIV2,HSIDIV4, or HSIDIV8)
        hal_rcc_hsi_config(RCC_OscInitStruct->HSIState);

        // Wait until the HSI is ready.
        while(hal_rcc_get_flag(RCC_FLAG_HSIRDY) == 0U) { ; }

        // Adjust the Internal High Speed oscillator (HSI) calibration value.
        hal_rcc_hsi_calibration_value_adjust(RCC_OscInitStruct->HSICalibrationValue);
      }
      else
      {
        /* Disable the Internal High Speed oscillator (HSI). */
        hal_rcc_hsi_disable();

        /* Get Start Tick*/
        //tickstart = HAL_GetTick();

        /* Wait till HSI is disabled */
        while(hal_rcc_get_flag(RCC_FLAG_HSIRDY) != 0U)
        {
          //if((HAL_GetTick() - tickstart ) > HSI_TIMEOUT_VALUE)
          //{
          //  return HAL_TIMEOUT;
          //}
        }
      }
    }
  }
  /*----------------------------- CSI Configuration --------------------------*/
  if(((RCC_OscInitStruct->OscillatorType) & RCC_OSCILLATORTYPE_CSI) == RCC_OSCILLATORTYPE_CSI)
  {
    /* When the CSI is used as system clock it will not disabled */
    const uint32_t temp_sysclksrc = hal_rcc_get_sysclk_source();
    const uint32_t temp_pllckselr = RCC->PLLCKSELR;
    if((temp_sysclksrc == RCC_CFGR_SWS_CSI) || ((temp_sysclksrc == RCC_CFGR_SWS_PLL1) && ((temp_pllckselr & RCC_PLLCKSELR_PLLSRC) == RCC_PLLCKSELR_PLLSRC_CSI)))
    {
      /* When CSI is used as system clock it will not disabled */
      if((hal_rcc_get_flag(RCC_FLAG_CSIRDY) != 0U) && (RCC_OscInitStruct->CSIState != RCC_CSI_ON))
      {
        return HAL_ERROR;
      }
      /* Otherwise, just the calibration is allowed */
      else
      {
        /* Adjusts the Internal High Speed oscillator (CSI) calibration value.*/
        hal_rcc_csi_calibration_value_adjust(RCC_OscInitStruct->CSICalibrationValue);
      }
    }
    else
    {
      /* Check the CSI State */
      if((RCC_OscInitStruct->CSIState)!= RCC_CSI_OFF)
      {
        // Enable the Internal High Speed oscillator (CSI).
        hal_rcc_csi_enable();

        /* Get Start Tick*/
        //tickstart = HAL_GetTick();

        /* Wait till CSI is ready */
        while(hal_rcc_get_flag(RCC_FLAG_CSIRDY) == 0U)
        {
          //if((HAL_GetTick() - tickstart ) > CSI_TIMEOUT_VALUE)
          //{
          //  return HAL_TIMEOUT;
          //}
        }

        /* Adjusts the Internal High Speed oscillator (CSI) calibration value.*/
        hal_rcc_csi_calibration_value_adjust(RCC_OscInitStruct->CSICalibrationValue);
      }
      else
      {
        // Disable the Internal High Speed oscillator (CSI).
        hal_rcc_csi_disable();

        /* Get Start Tick*/
        //tickstart = HAL_GetTick();

        /* Wait till CSI is disabled */
        while(hal_rcc_get_flag(RCC_FLAG_CSIRDY) != 0U)
        {
          //if((HAL_GetTick() - tickstart ) > CSI_TIMEOUT_VALUE)
          //{
          //  return HAL_TIMEOUT;
          //}
        }
      }
    }
  }
  /*------------------------------ LSI Configuration -------------------------*/
  if(((RCC_OscInitStruct->OscillatorType) & RCC_OSCILLATORTYPE_LSI) == RCC_OSCILLATORTYPE_LSI)
  {
    /* Check the LSI State */
    if((RCC_OscInitStruct->LSIState)!= RCC_LSI_OFF)
    {
      /* Enable the Internal Low Speed oscillator (LSI). */
      hal_rcc_lsi_enable();

      /* Get Start Tick*/
      //tickstart = HAL_GetTick();

      /* Wait till LSI is ready */
      while(hal_rcc_get_flag(RCC_FLAG_LSIRDY) == 0U)
      {
        //if((HAL_GetTick() - tickstart ) > LSI_TIMEOUT_VALUE)
        //{
        //  return HAL_TIMEOUT;
        //}
      }
    }
    else
    {
      /* Disable the Internal Low Speed oscillator (LSI). */
      hal_rcc_lsi_disable();

      /* Get Start Tick*/
      //tickstart = HAL_GetTick();

      /* Wait till LSI is ready */
      while(hal_rcc_get_flag(RCC_FLAG_LSIRDY) != 0U)
      {
        //if((HAL_GetTick() - tickstart ) > LSI_TIMEOUT_VALUE)
        //{
        //  return HAL_TIMEOUT;
        //}
      }
    }
  }

  /*------------------------------ HSI48 Configuration -------------------------*/
  if(((RCC_OscInitStruct->OscillatorType) & RCC_OSCILLATORTYPE_HSI48) == RCC_OSCILLATORTYPE_HSI48)
  {
    /* Check the HSI48 State */
    if((RCC_OscInitStruct->HSI48State)!= RCC_HSI48_OFF)
    {
      // Enable the Internal Low Speed oscillator (HSI48).
      hal_rcc_hsi48_enable();

      /* Get time-out */
      //tickstart = HAL_GetTick();

      /* Wait till HSI48 is ready */
      while(hal_rcc_get_flag(RCC_FLAG_HSI48RDY) == 0U)
      {
        //if((HAL_GetTick() - tickstart ) > HSI48_TIMEOUT_VALUE)
        //{
        //  return HAL_TIMEOUT;
        //}
      }
    }
    else
    {
      // Disable the Internal Low Speed oscillator (HSI48).
      hal_rcc_hsi48_disable();

      // Wait until the HSI48 is ready.
      while(hal_rcc_get_flag(RCC_FLAG_HSI48RDY) != 0U) { ; }
    }
  }

  // LSE Configuration
  if(((RCC_OscInitStruct->OscillatorType) & RCC_OSCILLATORTYPE_LSE) == RCC_OSCILLATORTYPE_LSE)
  {
    // Enable write access to Backup domain.
    PWR->CR1 |= PWR_CR1_DBP;

    while((PWR->CR1 & PWR_CR1_DBP) == 0U) { ; }

    // Set the new LSE configuration.
    hal_rcc_lse_config(RCC_OscInitStruct->LSEState);

    // Check the LSE State.
    if((RCC_OscInitStruct->LSEState) != RCC_LSE_OFF)
    {
      // Wait until the LSE is ready.
      while(hal_rcc_get_flag(RCC_FLAG_LSERDY) == 0U) { ; }
    }
    else
    {
      // Wait until the LSE is disabled.
      while(hal_rcc_get_flag(RCC_FLAG_LSERDY) != 0U) { ; }
    }
  }

  // PLL Configuration
  if ((RCC_OscInitStruct->PLL.PLLState) != RCC_PLL_NONE)
  {
    // Check if the PLL is used as system clock or not.
    if(hal_rcc_get_sysclk_source() != RCC_CFGR_SWS_PLL1)
    {
      if((RCC_OscInitStruct->PLL.PLLState) == RCC_PLL_ON)
      {
        // Disable the main PLL.
        hal_rcc_pll_disable();

        // Wait until the PLL is disabled
        while(hal_rcc_get_flag(RCC_FLAG_PLLRDY) != 0U) { ; }

        // Configure the main PLL clock source, multiplication and division factors.
        hal_rcc_pll_config(RCC_OscInitStruct->PLL.PLLSource,
                           RCC_OscInitStruct->PLL.PLLM,
                           RCC_OscInitStruct->PLL.PLLN,
                           RCC_OscInitStruct->PLL.PLLP,
                           RCC_OscInitStruct->PLL.PLLQ,
                           RCC_OscInitStruct->PLL.PLLR);

        // Disable PLLFRACN.
        hal_rcc_pllfracn_disable();

        // Configure PLL PLL1FRACN.
        hal_rcc_pllfracn_config(RCC_OscInitStruct->PLL.PLLFRACN);

        // Select PLL1 input reference frequency range: VCI.
        hal_rcc_pll_vcirange(RCC_OscInitStruct->PLL.PLLRGE) ;

        // Select PLL1 output frequency range : VCO.
        hal_rcc_pll_vcorange(RCC_OscInitStruct->PLL.PLLVCOSEL) ;

        // Enable PLL System Clock output.
        hal_rcc_pllclkout_enable(RCC_PLL1_DIVP);

        // Enable PLL1Q Clock output.
        hal_rcc_pllclkout_enable(RCC_PLL1_DIVQ);

        // Enable PLL1R  Clock output.
        hal_rcc_pllclkout_enable(RCC_PLL1_DIVR);

        // Enable PLL1FRACN.
        hal_rcc_pllfracn_enable();

        // Enable the main PLL.
        hal_rcc_pll_enable();

        // Wait until the PLL is ready.
        while(hal_rcc_get_flag(RCC_FLAG_PLLRDY) == 0U) { ; }
      }
      else
      {
        // Disable the main PLL.
        hal_rcc_pll_disable();

        // Wait until the PLL is disabled.
        while(hal_rcc_get_flag(RCC_FLAG_PLLRDY) != 0U) { ; }
      }
    }
    else
    {
      /* Do not return HAL_ERROR if request repeats the current configuration */
      temp1_pllckcfg = RCC->PLLCKSELR;
      temp2_pllckcfg = RCC->PLL1DIVR;

      const auto
        read_back_is_not_ok =
        (
             ((RCC_OscInitStruct->PLL.PLLState) == RCC_PLL_OFF)
          ||  (read_bit(temp1_pllckcfg, RCC_PLLCKSELR_PLLSRC) != RCC_OscInitStruct->PLL.PLLSource)
          || ((read_bit(temp1_pllckcfg, RCC_PLLCKSELR_DIVM1) >> RCC_PLLCKSELR_DIVM1_Pos) != RCC_OscInitStruct->PLL.PLLM)
          ||  (read_bit(temp2_pllckcfg, RCC_PLL1DIVR_N1) != (RCC_OscInitStruct->PLL.PLLN - 1U))
          || ((read_bit(temp2_pllckcfg, RCC_PLL1DIVR_P1) >> RCC_PLL1DIVR_P1_Pos) != (RCC_OscInitStruct->PLL.PLLP - 1U))
          || ((read_bit(temp2_pllckcfg, RCC_PLL1DIVR_Q1) >> RCC_PLL1DIVR_Q1_Pos) != (RCC_OscInitStruct->PLL.PLLQ - 1U))
          || ((read_bit(temp2_pllckcfg, RCC_PLL1DIVR_R1) >> RCC_PLL1DIVR_R1_Pos) != (RCC_OscInitStruct->PLL.PLLR - 1U))
        );

      if(read_back_is_not_ok)
      {
        return HAL_ERROR;
      }
    }
  }

  return HAL_OK;
}

/**
  * @brief  Initializes the CPU, AHB and APB buses clocks according to the specified
  *         parameters in the RCC_ClkInitStruct.
  * @param  RCC_ClkInitStruct: pointer to an RCC_OscInitTypeDef structure that
  *         contains the configuration information for the RCC peripheral.
  * @param  FLatency: FLASH Latency, this parameter depend on device selected
  *
  * @note   The SystemCoreClock CMSIS variable is used to store System Core Clock Frequency
  *         and updated by HAL_InitTick() function called within this function
  *
  * @note   The HSI is used (enabled by hardware) as system clock source after
  *         start-up from Reset, wake-up from STOP and STANDBY mode, or in case
  *         of failure of the HSE used directly or indirectly as system clock
  *         (if the Clock Security System CSS is enabled).
  *
  * @note   A switch from one clock source to another occurs only if the target
  *         clock source is ready (clock stable after start-up delay or PLL locked).
  *         If a clock source which is not yet ready is selected, the switch will
  *         occur when the clock source will be ready.
  *         You can use HAL_RCC_GetClockConfig() function to know which clock is
  *         currently used as system clock source.
  * @note   Depending on the device voltage range, the software has to set correctly
  *         D1CPRE[3:0] bits to ensure that  Domain1 core clock not exceed the maximum allowed frequency
  *         (for more details refer to section above "Initialization/de-initialization functions")
  * @retval None
  */
HAL_StatusTypeDef HAL_RCC_ClockConfig(const RCC_ClkInitTypeDef* RCC_ClkInitStruct, const uint32_t FLatency)
{
  if(RCC_ClkInitStruct == nullptr) { return HAL_ERROR; }

  HAL_StatusTypeDef halstatus;

  // To correctly read data from FLASH memory, the number of wait states (LATENCY)
  // must be correctly programmed according to the frequency of the CPU clock
  // (HCLK) and the supply voltage of the device.

  // Increase the CPU frequency.
  if(FLatency > hal_flash_get_latency())
  {
    // Program the new number of wait states to the LATENCY bits in the FLASH_ACR register.
    hal_flash_set_latency(FLatency);

    /* Check that the new number of wait states is taken into account to access the Flash
    memory by reading the FLASH_ACR register */
    if(hal_flash_get_latency() != FLatency)
    {
      return HAL_ERROR;
    }
  }

  // Increase the BUS frequency divider.
  // D1PCLK1/CDPCLK1 Configuration
  if(((RCC_ClkInitStruct->ClockType) & RCC_CLOCKTYPE_D1PCLK1) == RCC_CLOCKTYPE_D1PCLK1)
  {
    if((RCC_ClkInitStruct->APB3CLKDivider) > (RCC->CDCFGR1 & RCC_CDCFGR1_CDPPRE))
    {
      modify_reg(RCC->CDCFGR1, RCC_CDCFGR1_CDPPRE, RCC_ClkInitStruct->APB3CLKDivider);
    }
  }

  // PCLK1 Configuration
  if(((RCC_ClkInitStruct->ClockType) & RCC_CLOCKTYPE_PCLK1) == RCC_CLOCKTYPE_PCLK1)
  {
    if((RCC_ClkInitStruct->APB1CLKDivider) > (RCC->CDCFGR2 & RCC_CDCFGR2_CDPPRE1))
    {
      modify_reg(RCC->CDCFGR2, RCC_CDCFGR2_CDPPRE1, (RCC_ClkInitStruct->APB1CLKDivider));
    }
  }

  // PCLK2 Configuration
  if(((RCC_ClkInitStruct->ClockType) & RCC_CLOCKTYPE_PCLK2) == RCC_CLOCKTYPE_PCLK2)
  {
     if((RCC_ClkInitStruct->APB2CLKDivider) > (RCC->CDCFGR2 & RCC_CDCFGR2_CDPPRE2))
    {
      modify_reg(RCC->CDCFGR2, RCC_CDCFGR2_CDPPRE2, (RCC_ClkInitStruct->APB2CLKDivider));
    }
  }

  // D3PCLK1 Configuration
  if(((RCC_ClkInitStruct->ClockType) & RCC_CLOCKTYPE_D3PCLK1) == RCC_CLOCKTYPE_D3PCLK1)
  {
    if((RCC_ClkInitStruct->APB4CLKDivider) > (RCC->SRDCFGR & RCC_SRDCFGR_SRDPPRE))
    {
      modify_reg(RCC->SRDCFGR, RCC_SRDCFGR_SRDPPRE, (RCC_ClkInitStruct->APB4CLKDivider) );
    }
  }

  // HCLK Configuration
  if(((RCC_ClkInitStruct->ClockType) & RCC_CLOCKTYPE_HCLK) == RCC_CLOCKTYPE_HCLK)
  {
    if((RCC_ClkInitStruct->AHBCLKDivider) > (RCC->CDCFGR1 & RCC_CDCFGR1_HPRE))
    {
      /* Set the new HCLK clock divider */
      modify_reg(RCC->CDCFGR1, RCC_CDCFGR1_HPRE, RCC_ClkInitStruct->AHBCLKDivider);
    }
  }

  // SYSCLK Configuration
  if(((RCC_ClkInitStruct->ClockType) & RCC_CLOCKTYPE_SYSCLK) == RCC_CLOCKTYPE_SYSCLK)
  {
    modify_reg(RCC->CDCFGR1, RCC_CDCFGR1_CDCPRE, RCC_ClkInitStruct->SYSCLKDivider);

    if(RCC_ClkInitStruct->SYSCLKSource == RCC_SYSCLKSOURCE_HSE)
    {
      // HSE is selected as System Clock Source.
      // Check the HSE ready flag.
      if(hal_rcc_get_flag(RCC_FLAG_HSERDY) == 0U)
      {
        return HAL_ERROR;
      }
    }
    else if(RCC_ClkInitStruct->SYSCLKSource == RCC_SYSCLKSOURCE_PLLCLK)
    {
      // PLL is selected as System Clock Source.
      // Check the PLL ready flag.
      if(hal_rcc_get_flag(RCC_FLAG_PLLRDY) == 0U)
      {
        return HAL_ERROR;
      }
    }
    else if(RCC_ClkInitStruct->SYSCLKSource == RCC_SYSCLKSOURCE_CSI)
    {
      // CSI is selected as System Clock Source.
      // Check the PLL ready flag.
      if(hal_rcc_get_flag(RCC_FLAG_CSIRDY) == 0U)
      {
        return HAL_ERROR;
      }
    }
    else
    {
      // HSI is selected as System Clock Source.
      // Check the HSI ready flag.
      if(hal_rcc_get_flag(RCC_FLAG_HSIRDY) == 0U)
      {
        return HAL_ERROR;
      }
    }

    modify_reg(RCC->CFGR, RCC_CFGR_SW, RCC_ClkInitStruct->SYSCLKSource);

    while(hal_rcc_get_sysclk_source() !=  (RCC_ClkInitStruct->SYSCLKSource << RCC_CFGR_SWS_Pos)) { ; }
  }

  // Decrease the BUS frequency divider.
  // HCLK Configuration
  if(((RCC_ClkInitStruct->ClockType) & RCC_CLOCKTYPE_HCLK) == RCC_CLOCKTYPE_HCLK)
  {
    if((RCC_ClkInitStruct->AHBCLKDivider) < (RCC->CDCFGR1 & RCC_CDCFGR1_HPRE))
    {
      // Set the new HCLK clock divider.
      modify_reg(RCC->CDCFGR1, RCC_CDCFGR1_HPRE, RCC_ClkInitStruct->AHBCLKDivider);
    }
  }

  // Decrease the number of wait states because of lower CPU frequency.
  if(FLatency < hal_flash_get_latency())
  {
    // Program the new number of wait states to the LATENCY bits in the FLASH_ACR register.
    hal_flash_set_latency(FLatency);

    // Check that the new number of wait states is taken into account to access the Flash
    // memory by reading the FLASH_ACR register.
    if(hal_flash_get_latency() != FLatency)
    {
      return HAL_ERROR;
    }
  }

  // D1PCLK1/CDPCLK Configuration.
  if(((RCC_ClkInitStruct->ClockType) & RCC_CLOCKTYPE_D1PCLK1) == RCC_CLOCKTYPE_D1PCLK1)
  {
    if((RCC_ClkInitStruct->APB3CLKDivider) < (RCC->CDCFGR1 & RCC_CDCFGR1_CDPPRE))
    {
      modify_reg(RCC->CDCFGR1, RCC_CDCFGR1_CDPPRE, RCC_ClkInitStruct->APB3CLKDivider);
    }
  }

  // PCLK1 Configuration
  if(((RCC_ClkInitStruct->ClockType) & RCC_CLOCKTYPE_PCLK1) == RCC_CLOCKTYPE_PCLK1)
  {
    if((RCC_ClkInitStruct->APB1CLKDivider) < (RCC->CDCFGR2 & RCC_CDCFGR2_CDPPRE1))
    {
      modify_reg(RCC->CDCFGR2, RCC_CDCFGR2_CDPPRE1, (RCC_ClkInitStruct->APB1CLKDivider));
    }
  }

  // PCLK2 Configuration
  if(((RCC_ClkInitStruct->ClockType) & RCC_CLOCKTYPE_PCLK2) == RCC_CLOCKTYPE_PCLK2)
  {
    if((RCC_ClkInitStruct->APB2CLKDivider) < (RCC->CDCFGR2 & RCC_CDCFGR2_CDPPRE2))
    {
      modify_reg(RCC->CDCFGR2, RCC_CDCFGR2_CDPPRE2, (RCC_ClkInitStruct->APB2CLKDivider));
    }
  }

  // D3PCLK1/SRDPCLK1 Configuration
  if(((RCC_ClkInitStruct->ClockType) & RCC_CLOCKTYPE_D3PCLK1) == RCC_CLOCKTYPE_D3PCLK1)
  {
    if((RCC_ClkInitStruct->APB4CLKDivider) < (RCC->SRDCFGR & RCC_SRDCFGR_SRDPPRE))
    {
      modify_reg(RCC->SRDCFGR, RCC_SRDCFGR_SRDPPRE, (RCC_ClkInitStruct->APB4CLKDivider) );
    }
  }

  halstatus = HAL_OK;

  return halstatus;
}
