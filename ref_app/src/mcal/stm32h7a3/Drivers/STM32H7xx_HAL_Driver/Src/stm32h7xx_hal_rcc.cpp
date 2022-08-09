/**
  ******************************************************************************
  * @file    stm32h7xx_hal_rcc.c
  * @author  MCD Application Team
  * @brief   RCC HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the Reset and Clock Control (RCC) peripheral:
  *           + Initialization and de-initialization functions
  *           + Peripheral Control functions
  *
  @verbatim
  ==============================================================================
                      ##### RCC specific features #####
  ==============================================================================
    [..]
      After reset the device is running from Internal High Speed oscillator
      (HSI 64MHz) with Flash 0 wait state,and all peripherals are off except
      internal SRAM, Flash, JTAG and PWR
      (+) There is no pre-scaler on High speed (AHB) and Low speed (APB) buses;
          all peripherals mapped on these buses are running at HSI speed.
      (+) The clock for all peripherals is switched off, except the SRAM and FLASH.
      (+) All GPIOs are in analogue mode , except the JTAG pins which
          are assigned to be used for debug purpose.

    [..]
      Once the device started from reset, the user application has to:
      (+) Configure the clock source to be used to drive the System clock
          (if the application needs higher frequency/performance)
      (+) Configure the System clock frequency and Flash settings
      (+) Configure the AHB and APB buses pre-scalers
      (+) Enable the clock for the peripheral(s) to be used
      (+) Configure the clock kernel source(s) for peripherals which clocks are not
          derived from the System clock through :RCC_D1CCIPR,RCC_D2CCIP1R,RCC_D2CCIP2R
          and RCC_D3CCIPR registers

                      ##### RCC Limitations #####
  ==============================================================================
    [..]
      A delay between an RCC peripheral clock enable and the effective peripheral
      enabling should be taken into account in order to manage the peripheral read/write
      from/to registers.
      (+) This delay depends on the peripheral mapping.
      (+) If peripheral is mapped on AHB: the delay is 2 AHB clock cycle
          after the clock enable bit is set on the hardware register
      (+) If peripheral is mapped on APB: the delay is 2 APB clock cycle
          after the clock enable bit is set on the hardware register

    [..]
      Implemented Workaround:
      (+) For AHB & APB peripherals, a dummy read to the peripheral register has been
          inserted in each __HAL_RCC_PPP_CLK_ENABLE() macro.

  @endverbatim
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

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"

/** @addtogroup STM32H7xx_HAL_Driver
  * @{
  */

/** @defgroup RCC  RCC
  * @brief RCC HAL module driver
  * @{
  */

#ifdef HAL_RCC_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/** @defgroup RCC_Private_Macros RCC Private Macros
  * @{
  */
#define MCO1_CLK_ENABLE()     __HAL_RCC_GPIOA_CLK_ENABLE()
#define MCO1_GPIO_PORT        GPIOA
#define MCO1_PIN              GPIO_PIN_8

#define MCO2_CLK_ENABLE()      __HAL_RCC_GPIOC_CLK_ENABLE()
#define MCO2_GPIO_PORT         GPIOC
#define MCO2_PIN               GPIO_PIN_9

/**
  * @}
  */
/* Private variables ---------------------------------------------------------*/
/** @defgroup RCC_Private_Variables RCC Private Variables
  * @{
  */

/**
  * @}
  */
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/** @defgroup RCC_Exported_Functions RCC Exported Functions
  * @{
  */

/** @defgroup RCC_Exported_Functions_Group1 Initialization and de-initialization functions
 *  @brief    Initialization and Configuration functions
 *
@verbatim
 ===============================================================================
           ##### Initialization functions #####
 ===============================================================================
    [..]
      This section provides functions allowing to configure the internal/external oscillators
      (HSE, HSI, LSE,CSI, LSI,HSI48, PLL, CSS and MCO) and the System buses clocks (SYSCLK, AHB3, AHB1
       AHB2,AHB4,APB3, APB1L, APB1H, APB2, and APB4).

    [..] Internal/external clock and PLL configuration
         (#) HSI (high-speed internal), 64 MHz factory-trimmed RC used directly or through
             the PLL as System clock source.
         (#) CSI is a low-power RC oscillator which can be used directly as system clock, peripheral
             clock, or PLL input.But even with frequency calibration, is less accurate than an
             external crystal oscillator or ceramic resonator.
         (#) LSI (low-speed internal), 32 KHz low consumption RC used as IWDG and/or RTC
             clock source.

         (#) HSE (high-speed external), 4 to 48 MHz crystal oscillator used directly or
             through the PLL as System clock source. Can be used also as RTC clock source.

         (#) LSE (low-speed external), 32 KHz oscillator used as RTC clock source.

         (#) PLL , The RCC features three independent PLLs (clocked by HSI , HSE or CSI),
             featuring three different output clocks and able  to work either in integer or Fractional mode.
           (++) A main PLL, PLL1, which is generally used to provide clocks to the CPU
                and to some peripherals.
           (++) Two dedicated PLLs, PLL2 and PLL3, which are used to generate the kernel clock for peripherals.


         (#) CSS (Clock security system), once enabled and if a HSE clock failure occurs
            (HSE used directly or through PLL as System clock source), the System clock
             is automatically switched to HSI and an interrupt is generated if enabled.
             The interrupt is linked to the Cortex-M NMI (Non-Mask-able Interrupt)
             exception vector.

         (#) MCO1 (micro controller clock output), used to output HSI, LSE, HSE, PLL1(PLL1_Q)
             or HSI48 clock (through a configurable pre-scaler) on PA8 pin.

         (#) MCO2 (micro controller clock output), used to output HSE, PLL2(PLL2_P), SYSCLK,
             LSI, CSI, or PLL1(PLL1_P) clock (through a configurable pre-scaler) on PC9 pin.

    [..] System, AHB and APB buses clocks configuration
         (#) Several clock sources can be used to drive the System clock (SYSCLK): CSI,HSI,
             HSE and PLL.
             The AHB clock (HCLK) is derived from System core clock through configurable
             pre-scaler and used to clock the CPU, memory and peripherals mapped
             on AHB and APB bus of the 3 Domains (D1, D2, D3)* through configurable pre-scalers
             and used to clock the peripherals mapped on these buses. You can use
             "HAL_RCC_GetSysClockFreq()" function to retrieve system clock frequency.

         -@- All the peripheral clocks are derived from the System clock (SYSCLK) except those
             with dual clock domain where kernel source clock could be selected through
             RCC_D1CCIPR,RCC_D2CCIP1R,RCC_D2CCIP2R and RCC_D3CCIPR registers.

     (*) : 2 Domains (CD and SRD) for stm32h7a3xx and stm32h7b3xx family lines.
@endverbatim
  * @{
  */

/**
  * @brief  Initializes the RCC Oscillators according to the specified parameters in the
  *         RCC_OscInitTypeDef.
  * @param  RCC_OscInitStruct: pointer to an RCC_OscInitTypeDef structure that
  *         contains the configuration information for the RCC Oscillators.
  * @note   The PLL is not disabled when used as system clock.
  * @note   Transitions LSE Bypass to LSE On and LSE On to LSE Bypass are not
  *         supported by this function. User should request a transition to LSE Off
  *         first and then LSE On or LSE Bypass.
  * @note   Transition HSE Bypass to HSE On and HSE On to HSE Bypass are not
  *         supported by this function. User should request a transition to HSE Off
  *         first and then HSE On or HSE Bypass.
  * @retval HAL status
  */
__weak HAL_StatusTypeDef HAL_RCC_OscConfig(RCC_OscInitTypeDef  *RCC_OscInitStruct)
{
  //uint32_t tickstart;
  uint32_t temp1_pllckcfg, temp2_pllckcfg;

    /* Check Null pointer */
  if(RCC_OscInitStruct == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_RCC_OSCILLATORTYPE(RCC_OscInitStruct->OscillatorType));
  /*------------------------------- HSE Configuration ------------------------*/
  if(((RCC_OscInitStruct->OscillatorType) & RCC_OSCILLATORTYPE_HSE) == RCC_OSCILLATORTYPE_HSE)
  {
    /* Check the parameters */
    assert_param(IS_RCC_HSE(RCC_OscInitStruct->HSEState));

    const uint32_t temp_sysclksrc = __HAL_RCC_GET_SYSCLK_SOURCE();
    const uint32_t temp_pllckselr = RCC->PLLCKSELR;
    /* When the HSE is used as system clock or clock source for PLL in these cases HSE will not disabled */
    if((temp_sysclksrc == RCC_CFGR_SWS_HSE) || ((temp_sysclksrc == RCC_CFGR_SWS_PLL1) && ((temp_pllckselr & RCC_PLLCKSELR_PLLSRC) == RCC_PLLCKSELR_PLLSRC_HSE)))
    {
      if((__HAL_RCC_GET_FLAG(RCC_FLAG_HSERDY) != 0U) && (RCC_OscInitStruct->HSEState == RCC_HSE_OFF))
      {
        return HAL_ERROR;
      }
    }
    else
    {
      /* Set the new HSE configuration ---------------------------------------*/
      __HAL_RCC_HSE_CONFIG(RCC_OscInitStruct->HSEState);

      /* Check the HSE State */
      if(RCC_OscInitStruct->HSEState != RCC_HSE_OFF)
      {
        /* Get Start Tick*/
        //tickstart = HAL_GetTick();

        /* Wait till HSE is ready */
        while(__HAL_RCC_GET_FLAG(RCC_FLAG_HSERDY) == 0U)
        {
          //if((uint32_t) (HAL_GetTick() - tickstart ) > HSE_TIMEOUT_VALUE)
          //{
          //  return HAL_TIMEOUT;
          //}
        }
      }
      else
      {
        /* Get Start Tick*/
        //tickstart = HAL_GetTick();

        /* Wait till HSE is disabled */
        while(__HAL_RCC_GET_FLAG(RCC_FLAG_HSERDY) != 0U)
        {
          //if((uint32_t) (HAL_GetTick() - tickstart ) > HSE_TIMEOUT_VALUE)
          //{
          //  return HAL_TIMEOUT;
          //}
        }
      }
    }
  }
  /*----------------------------- HSI Configuration --------------------------*/
  if(((RCC_OscInitStruct->OscillatorType) & RCC_OSCILLATORTYPE_HSI) == RCC_OSCILLATORTYPE_HSI)
  {
    /* Check the parameters */
    assert_param(IS_RCC_HSI(RCC_OscInitStruct->HSIState));
    assert_param(IS_RCC_HSICALIBRATION_VALUE(RCC_OscInitStruct->HSICalibrationValue));

    /* When the HSI is used as system clock it will not be disabled */
    const uint32_t temp_sysclksrc = __HAL_RCC_GET_SYSCLK_SOURCE();
    const uint32_t temp_pllckselr = RCC->PLLCKSELR;
    if((temp_sysclksrc == RCC_CFGR_SWS_HSI) || ((temp_sysclksrc == RCC_CFGR_SWS_PLL1) && ((temp_pllckselr & RCC_PLLCKSELR_PLLSRC) == RCC_PLLCKSELR_PLLSRC_HSI)))
    {
      /* When HSI is used as system clock it will not be disabled */
      if((__HAL_RCC_GET_FLAG(RCC_FLAG_HSIRDY) != 0U) && (RCC_OscInitStruct->HSIState == RCC_HSI_OFF))
      {
        return HAL_ERROR;
      }
      /* Otherwise, only HSI division and calibration are allowed */
      else
      {
          /* Enable the Internal High Speed oscillator (HSI, HSIDIV2, HSIDIV4, or HSIDIV8) */
          __HAL_RCC_HSI_CONFIG(RCC_OscInitStruct->HSIState);

          /* Get Start Tick*/
          //tickstart = HAL_GetTick();

          /* Wait till HSI is ready */
          while(__HAL_RCC_GET_FLAG(RCC_FLAG_HSIRDY) == 0U)
          {
            //if((uint32_t) (HAL_GetTick() - tickstart ) > HSI_TIMEOUT_VALUE)
            //{
            //  return HAL_TIMEOUT;
            //}
          }
        /* Adjusts the Internal High Speed oscillator (HSI) calibration value.*/
        __HAL_RCC_HSI_CALIBRATIONVALUE_ADJUST(RCC_OscInitStruct->HSICalibrationValue);
      }
    }

    else
    {
      /* Check the HSI State */
      if((RCC_OscInitStruct->HSIState)!= RCC_HSI_OFF)
      {
     /* Enable the Internal High Speed oscillator (HSI, HSIDIV2,HSIDIV4, or HSIDIV8) */
        __HAL_RCC_HSI_CONFIG(RCC_OscInitStruct->HSIState);

        /* Get Start Tick*/
        //tickstart = HAL_GetTick();

        /* Wait till HSI is ready */
        while(__HAL_RCC_GET_FLAG(RCC_FLAG_HSIRDY) == 0U)
        {
          //if((HAL_GetTick() - tickstart ) > HSI_TIMEOUT_VALUE)
          //{
          //  return HAL_TIMEOUT;
          //}
        }

        /* Adjusts the Internal High Speed oscillator (HSI) calibration value.*/
        __HAL_RCC_HSI_CALIBRATIONVALUE_ADJUST(RCC_OscInitStruct->HSICalibrationValue);
      }
      else
      {
        /* Disable the Internal High Speed oscillator (HSI). */
        __HAL_RCC_HSI_DISABLE();

        /* Get Start Tick*/
        //tickstart = HAL_GetTick();

        /* Wait till HSI is disabled */
        while(__HAL_RCC_GET_FLAG(RCC_FLAG_HSIRDY) != 0U)
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
    /* Check the parameters */
    assert_param(IS_RCC_CSI(RCC_OscInitStruct->CSIState));
    assert_param(IS_RCC_CSICALIBRATION_VALUE(RCC_OscInitStruct->CSICalibrationValue));

    /* When the CSI is used as system clock it will not disabled */
    const uint32_t temp_sysclksrc = __HAL_RCC_GET_SYSCLK_SOURCE();
    const uint32_t temp_pllckselr = RCC->PLLCKSELR;
    if((temp_sysclksrc == RCC_CFGR_SWS_CSI) || ((temp_sysclksrc == RCC_CFGR_SWS_PLL1) && ((temp_pllckselr & RCC_PLLCKSELR_PLLSRC) == RCC_PLLCKSELR_PLLSRC_CSI)))
    {
      /* When CSI is used as system clock it will not disabled */
      if((__HAL_RCC_GET_FLAG(RCC_FLAG_CSIRDY) != 0U) && (RCC_OscInitStruct->CSIState != RCC_CSI_ON))
      {
        return HAL_ERROR;
      }
      /* Otherwise, just the calibration is allowed */
      else
      {
        /* Adjusts the Internal High Speed oscillator (CSI) calibration value.*/
        __HAL_RCC_CSI_CALIBRATIONVALUE_ADJUST(RCC_OscInitStruct->CSICalibrationValue);
      }
    }
    else
    {
      /* Check the CSI State */
      if((RCC_OscInitStruct->CSIState)!= RCC_CSI_OFF)
      {
        /* Enable the Internal High Speed oscillator (CSI). */
        __HAL_RCC_CSI_ENABLE();

        /* Get Start Tick*/
        //tickstart = HAL_GetTick();

        /* Wait till CSI is ready */
        while(__HAL_RCC_GET_FLAG(RCC_FLAG_CSIRDY) == 0U)
        {
          //if((HAL_GetTick() - tickstart ) > CSI_TIMEOUT_VALUE)
          //{
          //  return HAL_TIMEOUT;
          //}
        }

        /* Adjusts the Internal High Speed oscillator (CSI) calibration value.*/
        __HAL_RCC_CSI_CALIBRATIONVALUE_ADJUST(RCC_OscInitStruct->CSICalibrationValue);
      }
      else
      {
        /* Disable the Internal High Speed oscillator (CSI). */
        __HAL_RCC_CSI_DISABLE();

        /* Get Start Tick*/
        //tickstart = HAL_GetTick();

        /* Wait till CSI is disabled */
        while(__HAL_RCC_GET_FLAG(RCC_FLAG_CSIRDY) != 0U)
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
    /* Check the parameters */
    assert_param(IS_RCC_LSI(RCC_OscInitStruct->LSIState));

    /* Check the LSI State */
    if((RCC_OscInitStruct->LSIState)!= RCC_LSI_OFF)
    {
      /* Enable the Internal Low Speed oscillator (LSI). */
      __HAL_RCC_LSI_ENABLE();

      /* Get Start Tick*/
      //tickstart = HAL_GetTick();

      /* Wait till LSI is ready */
      while(__HAL_RCC_GET_FLAG(RCC_FLAG_LSIRDY) == 0U)
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
      __HAL_RCC_LSI_DISABLE();

      /* Get Start Tick*/
      //tickstart = HAL_GetTick();

      /* Wait till LSI is ready */
      while(__HAL_RCC_GET_FLAG(RCC_FLAG_LSIRDY) != 0U)
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
    /* Check the parameters */
    assert_param(IS_RCC_HSI48(RCC_OscInitStruct->HSI48State));

    /* Check the HSI48 State */
    if((RCC_OscInitStruct->HSI48State)!= RCC_HSI48_OFF)
    {
      /* Enable the Internal Low Speed oscillator (HSI48). */
      __HAL_RCC_HSI48_ENABLE();

      /* Get time-out */
      //tickstart = HAL_GetTick();

      /* Wait till HSI48 is ready */
      while(__HAL_RCC_GET_FLAG(RCC_FLAG_HSI48RDY) == 0U)
      {
        //if((HAL_GetTick() - tickstart ) > HSI48_TIMEOUT_VALUE)
        //{
        //  return HAL_TIMEOUT;
        //}
      }
    }
    else
    {
      /* Disable the Internal Low Speed oscillator (HSI48). */
      __HAL_RCC_HSI48_DISABLE();

      /* Get time-out */
      //tickstart = HAL_GetTick();

      /* Wait till HSI48 is ready */
      while(__HAL_RCC_GET_FLAG(RCC_FLAG_HSI48RDY) != 0U)
      {
        //if((HAL_GetTick() - tickstart ) > HSI48_TIMEOUT_VALUE)
        //{
        //  return HAL_TIMEOUT;
        //}
      }
    }
  }
  /*------------------------------ LSE Configuration -------------------------*/
  if(((RCC_OscInitStruct->OscillatorType) & RCC_OSCILLATORTYPE_LSE) == RCC_OSCILLATORTYPE_LSE)
  {
    /* Check the parameters */
    assert_param(IS_RCC_LSE(RCC_OscInitStruct->LSEState));

    /* Enable write access to Backup domain */
    PWR->CR1 |= PWR_CR1_DBP;

    /* Wait for Backup domain Write protection disable */
    //tickstart = HAL_GetTick();

    while((PWR->CR1 & PWR_CR1_DBP) == 0U)
    {
      //if((HAL_GetTick() - tickstart ) > RCC_DBP_TIMEOUT_VALUE)
      //{
      //  return HAL_TIMEOUT;
      //}
    }

    /* Set the new LSE configuration -----------------------------------------*/
    __HAL_RCC_LSE_CONFIG(RCC_OscInitStruct->LSEState);
    /* Check the LSE State */
    if((RCC_OscInitStruct->LSEState) != RCC_LSE_OFF)
    {
      /* Get Start Tick*/
      //tickstart = HAL_GetTick();

      /* Wait till LSE is ready */
      while(__HAL_RCC_GET_FLAG(RCC_FLAG_LSERDY) == 0U)
      {
        //if((HAL_GetTick() - tickstart ) > RCC_LSE_TIMEOUT_VALUE)
        //{
        //  return HAL_TIMEOUT;
        //}
      }
    }
    else
    {
      /* Get Start Tick*/
      //tickstart = HAL_GetTick();

      /* Wait till LSE is disabled */
      while(__HAL_RCC_GET_FLAG(RCC_FLAG_LSERDY) != 0U)
      {
        //if((HAL_GetTick() - tickstart ) > RCC_LSE_TIMEOUT_VALUE)
        //{
        //  return HAL_TIMEOUT;
        //}
      }
    }
  }
  /*-------------------------------- PLL Configuration -----------------------*/
  /* Check the parameters */
  assert_param(IS_RCC_PLL(RCC_OscInitStruct->PLL.PLLState));
  if ((RCC_OscInitStruct->PLL.PLLState) != RCC_PLL_NONE)
  {
    /* Check if the PLL is used as system clock or not */
    if(__HAL_RCC_GET_SYSCLK_SOURCE() != RCC_CFGR_SWS_PLL1)
    {
      if((RCC_OscInitStruct->PLL.PLLState) == RCC_PLL_ON)
      {
        /* Check the parameters */
        assert_param(IS_RCC_PLLSOURCE(RCC_OscInitStruct->PLL.PLLSource));
        assert_param(IS_RCC_PLLRGE_VALUE(RCC_OscInitStruct->PLL.PLLRGE));
        assert_param(IS_RCC_PLLVCO_VALUE(RCC_OscInitStruct->PLL.PLLVCOSEL));
        assert_param(IS_RCC_PLLM_VALUE(RCC_OscInitStruct->PLL.PLLM));
        assert_param(IS_RCC_PLLN_VALUE(RCC_OscInitStruct->PLL.PLLN));
        assert_param(IS_RCC_PLLP_VALUE(RCC_OscInitStruct->PLL.PLLP));
        assert_param(IS_RCC_PLLQ_VALUE(RCC_OscInitStruct->PLL.PLLQ));
        assert_param(IS_RCC_PLLR_VALUE(RCC_OscInitStruct->PLL.PLLR));
        assert_param(IS_RCC_PLLFRACN_VALUE(RCC_OscInitStruct->PLL.PLLFRACN));

        /* Disable the main PLL. */
        __HAL_RCC_PLL_DISABLE();

        /* Get Start Tick*/
        //tickstart = HAL_GetTick();

        /* Wait till PLL is disabled */
        while(__HAL_RCC_GET_FLAG(RCC_FLAG_PLLRDY) != 0U)
        {
          //if((HAL_GetTick() - tickstart ) > PLL_TIMEOUT_VALUE)
          //{
          //  return HAL_TIMEOUT;
          //}
        }

        /* Configure the main PLL clock source, multiplication and division factors. */
        __HAL_RCC_PLL_CONFIG(RCC_OscInitStruct->PLL.PLLSource,
                             RCC_OscInitStruct->PLL.PLLM,
                             RCC_OscInitStruct->PLL.PLLN,
                             RCC_OscInitStruct->PLL.PLLP,
                             RCC_OscInitStruct->PLL.PLLQ,
                             RCC_OscInitStruct->PLL.PLLR);

         /* Disable PLLFRACN . */
         __HAL_RCC_PLLFRACN_DISABLE();

         /* Configure PLL PLL1FRACN */
         __HAL_RCC_PLLFRACN_CONFIG(RCC_OscInitStruct->PLL.PLLFRACN);

        /* Select PLL1 input reference frequency range: VCI */
        __HAL_RCC_PLL_VCIRANGE(RCC_OscInitStruct->PLL.PLLRGE) ;

        /* Select PLL1 output frequency range : VCO */
        __HAL_RCC_PLL_VCORANGE(RCC_OscInitStruct->PLL.PLLVCOSEL) ;

        /* Enable PLL System Clock output. */
         __HAL_RCC_PLLCLKOUT_ENABLE(RCC_PLL1_DIVP);

        /* Enable PLL1Q Clock output. */
         __HAL_RCC_PLLCLKOUT_ENABLE(RCC_PLL1_DIVQ);

        /* Enable PLL1R  Clock output. */
         __HAL_RCC_PLLCLKOUT_ENABLE(RCC_PLL1_DIVR);

        /* Enable PLL1FRACN . */
         __HAL_RCC_PLLFRACN_ENABLE();

        /* Enable the main PLL. */
        __HAL_RCC_PLL_ENABLE();

        /* Get Start Tick*/
        //tickstart = HAL_GetTick();

        /* Wait till PLL is ready */
        while(__HAL_RCC_GET_FLAG(RCC_FLAG_PLLRDY) == 0U)
        {
          //if((HAL_GetTick() - tickstart ) > PLL_TIMEOUT_VALUE)
          //{
          //  return HAL_TIMEOUT;
          //}
        }
      }
      else
      {
        /* Disable the main PLL. */
        __HAL_RCC_PLL_DISABLE();

        /* Get Start Tick*/
        //tickstart = HAL_GetTick();

        /* Wait till PLL is disabled */
        while(__HAL_RCC_GET_FLAG(RCC_FLAG_PLLRDY) != 0U)
        {
          //if((HAL_GetTick() - tickstart ) > PLL_TIMEOUT_VALUE)
          //{
          //  return HAL_TIMEOUT;
          //}
        }
      }
    }
    else
    {
      /* Do not return HAL_ERROR if request repeats the current configuration */
      temp1_pllckcfg = RCC->PLLCKSELR;
      temp2_pllckcfg = RCC->PLL1DIVR;
      if(((RCC_OscInitStruct->PLL.PLLState) == RCC_PLL_OFF) ||
	 (READ_BIT(temp1_pllckcfg, RCC_PLLCKSELR_PLLSRC) != RCC_OscInitStruct->PLL.PLLSource) ||
         ((READ_BIT(temp1_pllckcfg, RCC_PLLCKSELR_DIVM1) >> RCC_PLLCKSELR_DIVM1_Pos) != RCC_OscInitStruct->PLL.PLLM) ||
         (READ_BIT(temp2_pllckcfg, RCC_PLL1DIVR_N1) != (RCC_OscInitStruct->PLL.PLLN - 1U)) ||
         ((READ_BIT(temp2_pllckcfg, RCC_PLL1DIVR_P1) >> RCC_PLL1DIVR_P1_Pos) != (RCC_OscInitStruct->PLL.PLLP - 1U)) ||
         ((READ_BIT(temp2_pllckcfg, RCC_PLL1DIVR_Q1) >> RCC_PLL1DIVR_Q1_Pos) != (RCC_OscInitStruct->PLL.PLLQ - 1U)) ||
         ((READ_BIT(temp2_pllckcfg, RCC_PLL1DIVR_R1) >> RCC_PLL1DIVR_R1_Pos) != (RCC_OscInitStruct->PLL.PLLR - 1U)))
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
HAL_StatusTypeDef HAL_RCC_ClockConfig(RCC_ClkInitTypeDef  *RCC_ClkInitStruct, uint32_t FLatency)
{
  HAL_StatusTypeDef halstatus;
  //uint32_t tickstart;
  //uint32_t common_system_clock;

   /* Check Null pointer */
  if(RCC_ClkInitStruct == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_RCC_CLOCKTYPE(RCC_ClkInitStruct->ClockType));
  assert_param(IS_FLASH_LATENCY(FLatency));

  /* To correctly read data from FLASH memory, the number of wait states (LATENCY)
    must be correctly programmed according to the frequency of the CPU clock
    (HCLK) and the supply voltage of the device. */

  /* Increasing the CPU frequency */
  if(FLatency > __HAL_FLASH_GET_LATENCY())
  {
    /* Program the new number of wait states to the LATENCY bits in the FLASH_ACR register */
    __HAL_FLASH_SET_LATENCY(FLatency);

    /* Check that the new number of wait states is taken into account to access the Flash
    memory by reading the FLASH_ACR register */
    if(__HAL_FLASH_GET_LATENCY() != FLatency)
    {
      return HAL_ERROR;
    }

  }

  /* Increasing the BUS frequency divider */
  /*-------------------------- D1PCLK1/CDPCLK1 Configuration ---------------------------*/
  if(((RCC_ClkInitStruct->ClockType) & RCC_CLOCKTYPE_D1PCLK1) == RCC_CLOCKTYPE_D1PCLK1)
  {
#if defined (RCC_D1CFGR_D1PPRE)
    if((RCC_ClkInitStruct->APB3CLKDivider) > (RCC->D1CFGR & RCC_D1CFGR_D1PPRE))
    {
      assert_param(IS_RCC_D1PCLK1(RCC_ClkInitStruct->APB3CLKDivider));
      MODIFY_REG(RCC->D1CFGR, RCC_D1CFGR_D1PPRE, RCC_ClkInitStruct->APB3CLKDivider);
    }
#else
    if((RCC_ClkInitStruct->APB3CLKDivider) > (RCC->CDCFGR1 & RCC_CDCFGR1_CDPPRE))
    {
      assert_param(IS_RCC_CDPCLK1(RCC_ClkInitStruct->APB3CLKDivider));
      MODIFY_REG(RCC->CDCFGR1, RCC_CDCFGR1_CDPPRE, RCC_ClkInitStruct->APB3CLKDivider);
    }
#endif
  }

  /*-------------------------- PCLK1 Configuration ---------------------------*/
  if(((RCC_ClkInitStruct->ClockType) & RCC_CLOCKTYPE_PCLK1) == RCC_CLOCKTYPE_PCLK1)
  {
#if defined (RCC_D2CFGR_D2PPRE1)
    if((RCC_ClkInitStruct->APB1CLKDivider) > (RCC->D2CFGR & RCC_D2CFGR_D2PPRE1))
    {
      assert_param(IS_RCC_PCLK1(RCC_ClkInitStruct->APB1CLKDivider));
      MODIFY_REG(RCC->D2CFGR, RCC_D2CFGR_D2PPRE1, (RCC_ClkInitStruct->APB1CLKDivider));
    }
#else
    if((RCC_ClkInitStruct->APB1CLKDivider) > (RCC->CDCFGR2 & RCC_CDCFGR2_CDPPRE1))
    {
      assert_param(IS_RCC_PCLK1(RCC_ClkInitStruct->APB1CLKDivider));
      MODIFY_REG(RCC->CDCFGR2, RCC_CDCFGR2_CDPPRE1, (RCC_ClkInitStruct->APB1CLKDivider));
  }
#endif
    }
  /*-------------------------- PCLK2 Configuration ---------------------------*/
  if(((RCC_ClkInitStruct->ClockType) & RCC_CLOCKTYPE_PCLK2) == RCC_CLOCKTYPE_PCLK2)
  {
#if defined(RCC_D2CFGR_D2PPRE2)
    if((RCC_ClkInitStruct->APB2CLKDivider) > (RCC->D2CFGR & RCC_D2CFGR_D2PPRE2))
    {
      assert_param(IS_RCC_PCLK2(RCC_ClkInitStruct->APB2CLKDivider));
      MODIFY_REG(RCC->D2CFGR, RCC_D2CFGR_D2PPRE2, (RCC_ClkInitStruct->APB2CLKDivider));
    }
#else
     if((RCC_ClkInitStruct->APB2CLKDivider) > (RCC->CDCFGR2 & RCC_CDCFGR2_CDPPRE2))
    {
      assert_param(IS_RCC_PCLK2(RCC_ClkInitStruct->APB2CLKDivider));
      MODIFY_REG(RCC->CDCFGR2, RCC_CDCFGR2_CDPPRE2, (RCC_ClkInitStruct->APB2CLKDivider));
    }
#endif
  }

  /*-------------------------- D3PCLK1 Configuration ---------------------------*/
  if(((RCC_ClkInitStruct->ClockType) & RCC_CLOCKTYPE_D3PCLK1) == RCC_CLOCKTYPE_D3PCLK1)
  {
#if defined(RCC_D3CFGR_D3PPRE)
    if((RCC_ClkInitStruct->APB4CLKDivider) > (RCC->D3CFGR & RCC_D3CFGR_D3PPRE))
    {
      assert_param(IS_RCC_D3PCLK1(RCC_ClkInitStruct->APB4CLKDivider));
      MODIFY_REG(RCC->D3CFGR, RCC_D3CFGR_D3PPRE, (RCC_ClkInitStruct->APB4CLKDivider) );
    }
#else
    if((RCC_ClkInitStruct->APB4CLKDivider) > (RCC->SRDCFGR & RCC_SRDCFGR_SRDPPRE))
    {
      assert_param(IS_RCC_D3PCLK1(RCC_ClkInitStruct->APB4CLKDivider));
      MODIFY_REG(RCC->SRDCFGR, RCC_SRDCFGR_SRDPPRE, (RCC_ClkInitStruct->APB4CLKDivider) );
    }
#endif
  }

   /*-------------------------- HCLK Configuration --------------------------*/
  if(((RCC_ClkInitStruct->ClockType) & RCC_CLOCKTYPE_HCLK) == RCC_CLOCKTYPE_HCLK)
  {
#if defined (RCC_D1CFGR_HPRE)
    if((RCC_ClkInitStruct->AHBCLKDivider) > (RCC->D1CFGR & RCC_D1CFGR_HPRE))
    {
      /* Set the new HCLK clock divider */
      assert_param(IS_RCC_HCLK(RCC_ClkInitStruct->AHBCLKDivider));
      MODIFY_REG(RCC->D1CFGR, RCC_D1CFGR_HPRE, RCC_ClkInitStruct->AHBCLKDivider);
    }
#else
        if((RCC_ClkInitStruct->AHBCLKDivider) > (RCC->CDCFGR1 & RCC_CDCFGR1_HPRE))
    {
      /* Set the new HCLK clock divider */
      assert_param(IS_RCC_HCLK(RCC_ClkInitStruct->AHBCLKDivider));
      MODIFY_REG(RCC->CDCFGR1, RCC_CDCFGR1_HPRE, RCC_ClkInitStruct->AHBCLKDivider);
    }
#endif
  }

    /*------------------------- SYSCLK Configuration -------------------------*/
    if(((RCC_ClkInitStruct->ClockType) & RCC_CLOCKTYPE_SYSCLK) == RCC_CLOCKTYPE_SYSCLK)
    {
      assert_param(IS_RCC_SYSCLK(RCC_ClkInitStruct->SYSCLKDivider));
      assert_param(IS_RCC_SYSCLKSOURCE(RCC_ClkInitStruct->SYSCLKSource));
#if defined(RCC_D1CFGR_D1CPRE)
      MODIFY_REG(RCC->D1CFGR, RCC_D1CFGR_D1CPRE, RCC_ClkInitStruct->SYSCLKDivider);
#else
      MODIFY_REG(RCC->CDCFGR1, RCC_CDCFGR1_CDCPRE, RCC_ClkInitStruct->SYSCLKDivider);
#endif
      /* HSE is selected as System Clock Source */
      if(RCC_ClkInitStruct->SYSCLKSource == RCC_SYSCLKSOURCE_HSE)
      {
        /* Check the HSE ready flag */
        if(__HAL_RCC_GET_FLAG(RCC_FLAG_HSERDY) == 0U)
        {
          return HAL_ERROR;
        }
      }
      /* PLL is selected as System Clock Source */
      else if(RCC_ClkInitStruct->SYSCLKSource == RCC_SYSCLKSOURCE_PLLCLK)
      {
        /* Check the PLL ready flag */
        if(__HAL_RCC_GET_FLAG(RCC_FLAG_PLLRDY) == 0U)
        {
          return HAL_ERROR;
        }
      }
      /* CSI is selected as System Clock Source */
      else if(RCC_ClkInitStruct->SYSCLKSource == RCC_SYSCLKSOURCE_CSI)
      {
        /* Check the PLL ready flag */
        if(__HAL_RCC_GET_FLAG(RCC_FLAG_CSIRDY) == 0U)
        {
          return HAL_ERROR;
        }
      }
      /* HSI is selected as System Clock Source */
      else
      {
        /* Check the HSI ready flag */
        if(__HAL_RCC_GET_FLAG(RCC_FLAG_HSIRDY) == 0U)
        {
          return HAL_ERROR;
        }
      }
      MODIFY_REG(RCC->CFGR, RCC_CFGR_SW, RCC_ClkInitStruct->SYSCLKSource);

      /* Get Start Tick*/
      //tickstart = HAL_GetTick();

        while (__HAL_RCC_GET_SYSCLK_SOURCE() !=  (RCC_ClkInitStruct->SYSCLKSource << RCC_CFGR_SWS_Pos))
        {
          //if((HAL_GetTick() - tickstart ) > CLOCKSWITCH_TIMEOUT_VALUE)
          //{
          //  return HAL_TIMEOUT;
          //}
        }

    }

    /* Decreasing the BUS frequency divider */
   /*-------------------------- HCLK Configuration --------------------------*/
  if(((RCC_ClkInitStruct->ClockType) & RCC_CLOCKTYPE_HCLK) == RCC_CLOCKTYPE_HCLK)
  {
#if defined(RCC_D1CFGR_HPRE)
    if((RCC_ClkInitStruct->AHBCLKDivider) < (RCC->D1CFGR & RCC_D1CFGR_HPRE))
    {
      /* Set the new HCLK clock divider */
      assert_param(IS_RCC_HCLK(RCC_ClkInitStruct->AHBCLKDivider));
      MODIFY_REG(RCC->D1CFGR, RCC_D1CFGR_HPRE, RCC_ClkInitStruct->AHBCLKDivider);
    }
#else
    if((RCC_ClkInitStruct->AHBCLKDivider) < (RCC->CDCFGR1 & RCC_CDCFGR1_HPRE))
    {
      /* Set the new HCLK clock divider */
      assert_param(IS_RCC_HCLK(RCC_ClkInitStruct->AHBCLKDivider));
      MODIFY_REG(RCC->CDCFGR1, RCC_CDCFGR1_HPRE, RCC_ClkInitStruct->AHBCLKDivider);
    }
#endif
  }

  /* Decreasing the number of wait states because of lower CPU frequency */
  if(FLatency < __HAL_FLASH_GET_LATENCY())
  {
    /* Program the new number of wait states to the LATENCY bits in the FLASH_ACR register */
    __HAL_FLASH_SET_LATENCY(FLatency);

    /* Check that the new number of wait states is taken into account to access the Flash
    memory by reading the FLASH_ACR register */
    if(__HAL_FLASH_GET_LATENCY() != FLatency)
    {
      return HAL_ERROR;
    }
 }

  /*-------------------------- D1PCLK1/CDPCLK Configuration ---------------------------*/
 if(((RCC_ClkInitStruct->ClockType) & RCC_CLOCKTYPE_D1PCLK1) == RCC_CLOCKTYPE_D1PCLK1)
 {
#if defined(RCC_D1CFGR_D1PPRE)
   if((RCC_ClkInitStruct->APB3CLKDivider) < (RCC->D1CFGR & RCC_D1CFGR_D1PPRE))
   {
     assert_param(IS_RCC_D1PCLK1(RCC_ClkInitStruct->APB3CLKDivider));
     MODIFY_REG(RCC->D1CFGR, RCC_D1CFGR_D1PPRE, RCC_ClkInitStruct->APB3CLKDivider);
   }
#else
   if((RCC_ClkInitStruct->APB3CLKDivider) < (RCC->CDCFGR1 & RCC_CDCFGR1_CDPPRE))
   {
     assert_param(IS_RCC_CDPCLK1(RCC_ClkInitStruct->APB3CLKDivider));
     MODIFY_REG(RCC->CDCFGR1, RCC_CDCFGR1_CDPPRE, RCC_ClkInitStruct->APB3CLKDivider);
   }
#endif
 }

  /*-------------------------- PCLK1 Configuration ---------------------------*/
 if(((RCC_ClkInitStruct->ClockType) & RCC_CLOCKTYPE_PCLK1) == RCC_CLOCKTYPE_PCLK1)
 {
#if defined(RCC_D2CFGR_D2PPRE1)
   if((RCC_ClkInitStruct->APB1CLKDivider) < (RCC->D2CFGR & RCC_D2CFGR_D2PPRE1))
   {
     assert_param(IS_RCC_PCLK1(RCC_ClkInitStruct->APB1CLKDivider));
     MODIFY_REG(RCC->D2CFGR, RCC_D2CFGR_D2PPRE1, (RCC_ClkInitStruct->APB1CLKDivider));
   }
#else
   if((RCC_ClkInitStruct->APB1CLKDivider) < (RCC->CDCFGR2 & RCC_CDCFGR2_CDPPRE1))
   {
     assert_param(IS_RCC_PCLK1(RCC_ClkInitStruct->APB1CLKDivider));
     MODIFY_REG(RCC->CDCFGR2, RCC_CDCFGR2_CDPPRE1, (RCC_ClkInitStruct->APB1CLKDivider));
   }
#endif
 }

  /*-------------------------- PCLK2 Configuration ---------------------------*/
 if(((RCC_ClkInitStruct->ClockType) & RCC_CLOCKTYPE_PCLK2) == RCC_CLOCKTYPE_PCLK2)
 {
#if defined (RCC_D2CFGR_D2PPRE2)
   if((RCC_ClkInitStruct->APB2CLKDivider) < (RCC->D2CFGR & RCC_D2CFGR_D2PPRE2))
   {
     assert_param(IS_RCC_PCLK2(RCC_ClkInitStruct->APB2CLKDivider));
     MODIFY_REG(RCC->D2CFGR, RCC_D2CFGR_D2PPRE2, (RCC_ClkInitStruct->APB2CLKDivider));
   }
#else
   if((RCC_ClkInitStruct->APB2CLKDivider) < (RCC->CDCFGR2 & RCC_CDCFGR2_CDPPRE2))
   {
     assert_param(IS_RCC_PCLK2(RCC_ClkInitStruct->APB2CLKDivider));
     MODIFY_REG(RCC->CDCFGR2, RCC_CDCFGR2_CDPPRE2, (RCC_ClkInitStruct->APB2CLKDivider));
   }
#endif
 }

  /*-------------------------- D3PCLK1/SRDPCLK1 Configuration ---------------------------*/
 if(((RCC_ClkInitStruct->ClockType) & RCC_CLOCKTYPE_D3PCLK1) == RCC_CLOCKTYPE_D3PCLK1)
 {
#if defined(RCC_D3CFGR_D3PPRE)
   if((RCC_ClkInitStruct->APB4CLKDivider) < (RCC->D3CFGR & RCC_D3CFGR_D3PPRE))
   {
     assert_param(IS_RCC_D3PCLK1(RCC_ClkInitStruct->APB4CLKDivider));
     MODIFY_REG(RCC->D3CFGR, RCC_D3CFGR_D3PPRE, (RCC_ClkInitStruct->APB4CLKDivider) );
   }
#else
   if((RCC_ClkInitStruct->APB4CLKDivider) < (RCC->SRDCFGR & RCC_SRDCFGR_SRDPPRE))
   {
     assert_param(IS_RCC_SRDPCLK1(RCC_ClkInitStruct->APB4CLKDivider));
     MODIFY_REG(RCC->SRDCFGR, RCC_SRDCFGR_SRDPPRE, (RCC_ClkInitStruct->APB4CLKDivider) );
   }
#endif
 }

  /* Update the SystemCoreClock global variable */
#if defined(RCC_D1CFGR_D1CPRE)
  //common_system_clock = HAL_RCC_GetSysClockFreq() >> ((D1CorePrescTable[(RCC->D1CFGR & RCC_D1CFGR_D1CPRE)>> RCC_D1CFGR_D1CPRE_Pos]) & 0x1FU);
#else
  //common_system_clock = HAL_RCC_GetSysClockFreq() >> ((D1CorePrescTable[(RCC->CDCFGR1 & RCC_CDCFGR1_CDCPRE)>> RCC_CDCFGR1_CDCPRE_Pos]) & 0x1FU);
#endif

#if defined(RCC_D1CFGR_HPRE)
  //SystemD2Clock = (common_system_clock >> ((D1CorePrescTable[(RCC->D1CFGR & RCC_D1CFGR_HPRE)>> RCC_D1CFGR_HPRE_Pos]) & 0x1FU));
#else
  //SystemD2Clock = (common_system_clock >> ((D1CorePrescTable[(RCC->CDCFGR1 & RCC_CDCFGR1_HPRE)>> RCC_CDCFGR1_HPRE_Pos]) & 0x1FU));
#endif

#if defined(DUAL_CORE) && defined(CORE_CM4)
  //SystemCoreClock = SystemD2Clock;
#else
  //SystemCoreClock = common_system_clock;
#endif /* DUAL_CORE && CORE_CM4 */

  /* Configure the source of time base considering new system clocks settings*/
  halstatus = HAL_OK;//HAL_InitTick (uwTickPrio);

  return halstatus;
}

#endif /* HAL_RCC_MODULE_ENABLED */
/**
  * @}
  */

/**
  * @}
  */

