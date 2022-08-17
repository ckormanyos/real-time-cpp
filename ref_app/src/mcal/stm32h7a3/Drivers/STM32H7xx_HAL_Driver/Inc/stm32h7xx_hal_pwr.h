///////////////////////////////////////////////////////////////////////////////
//  Modified by Christopher Kormanyos 2022.
//  Distributed under (see below).
//

/*
  ******************************************************************************
  * @file    stm32h7xx_hal_pwr.h
  * @author  MCD Application Team
  * @brief   Header file of PWR HAL module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
*/

#ifndef STM32H7XX_HAL_PWR_2022_08_05_H_
#define STM32H7XX_HAL_PWR_2022_08_05_H_

#include "stm32h7xx_hal_def.h"

// PWR_Regulator_Voltage_Scale PWR Regulator Voltage Scale
#define PWR_REGULATOR_VOLTAGE_SCALE0  (PWR_SRDCR_VOS_1 | PWR_SRDCR_VOS_0)
#define PWR_REGULATOR_VOLTAGE_SCALE1  (PWR_SRDCR_VOS_1)
#define PWR_REGULATOR_VOLTAGE_SCALE2  (PWR_SRDCR_VOS_0)
#define PWR_REGULATOR_VOLTAGE_SCALE3  (0U)

/** @brief  Configure the main internal regulator output voltage.
  * @param  __REGULATOR__ : Specifies the regulator output voltage to achieve a
  *                         trade-off between performance and power consumption
  *                         when the device does not operate at the maximum
  *                         frequency (refer to the datasheet for more details).
  *          This parameter can be one of the following values:
  *            @arg PWR_REGULATOR_VOLTAGE_SCALE0 : Regulator voltage output
  *                                                Scale 0 mode.
  *            @arg PWR_REGULATOR_VOLTAGE_SCALE1 : Regulator voltage output
  *                                                Scale 1 mode.
  *            @arg PWR_REGULATOR_VOLTAGE_SCALE2 : Regulator voltage output
  *                                                Scale 2 mode.
  *            @arg PWR_REGULATOR_VOLTAGE_SCALE3 : Regulator voltage output
  *                                                Scale 3 mode.
  * @note   For STM32H74x and STM32H75x lines, configuring Voltage Scale 0 is
  *         only possible when Vcore is supplied from LDO (Low DropOut). The
  *         SYSCFG Clock must be enabled through __HAL_RCC_SYSCFG_CLK_ENABLE()
  *         macro before configuring Voltage Scale 0 using
  *         __HAL_PWR_VOLTAGESCALING_CONFIG().
  *         Transition to Voltage Scale 0 is only possible when the system is
  *         already in Voltage Scale 1.
  *         Transition from Voltage Scale 0 is only possible to Voltage Scale 1
  *         then once in Voltage Scale 1 it is possible to switch to another
  *         voltage scale.
  *         After each regulator voltage setting, wait on VOSRDY flag to be set
  *         using macro __HAL_PWR_GET_FLAG().
  *         To enter low power mode , and if current regulator voltage is
  *         Voltage Scale 0 then first switch to Voltage Scale 1 before entering
  *         low power mode.
  * @retval None.
  */
#if defined (PWR_SRDCR_VOS) /* STM32H7Axxx and STM32H7Bxxx lines */
#define __HAL_PWR_VOLTAGESCALING_CONFIG(__REGULATOR__)                         \
do {                                                                           \
      __IO uint32_t tmpreg = 0x00;                                             \
      /* Configure the Voltage Scaling */                                      \
      modify_reg(PWR->SRDCR, PWR_SRDCR_VOS, (__REGULATOR__));                  \
      /* Delay after setting the voltage scaling */                            \
      tmpreg = read_bit(PWR->SRDCR, PWR_SRDCR_VOS);                            \
      UNUSED(tmpreg);                                                          \
} while(0)
#else /* 3 power domains devices */
#if defined(SYSCFG_PWRCR_ODEN) /* STM32H74xxx and STM32H75xxx lines */
#define __HAL_PWR_VOLTAGESCALING_CONFIG(__REGULATOR__)                         \
do {                                                                           \
      __IO uint32_t tmpreg = 0x00;                                             \
      /* Check the voltage scaling to be configured */                         \
      if((__REGULATOR__) == PWR_REGULATOR_VOLTAGE_SCALE0)                      \
      {                                                                        \
        /* Configure the Voltage Scaling 1 */                                  \
        modify_reg(PWR->D3CR, PWR_D3CR_VOS, PWR_REGULATOR_VOLTAGE_SCALE1);     \
        /* Delay after setting the voltage scaling */                          \
        tmpreg = read_bit(PWR->D3CR, PWR_D3CR_VOS);                            \
        /* Enable the PWR overdrive */                                         \
        set_bit(SYSCFG->PWRCR, SYSCFG_PWRCR_ODEN);                             \
        /* Delay after setting the syscfg boost setting */                     \
        tmpreg = read_bit(SYSCFG->PWRCR, SYSCFG_PWRCR_ODEN);                   \
      }                                                                        \
      else                                                                     \
      {                                                                        \
        /* Disable the PWR overdrive */                                        \
        clear_bit(SYSCFG->PWRCR, SYSCFG_PWRCR_ODEN);                           \
        /* Delay after setting the syscfg boost setting */                     \
        tmpreg = read_bit(SYSCFG->PWRCR, SYSCFG_PWRCR_ODEN);                   \
        /* Configure the Voltage Scaling x */                                  \
        modify_reg(PWR->D3CR, PWR_D3CR_VOS, (__REGULATOR__));                  \
        /* Delay after setting the voltage scaling */                          \
        tmpreg = read_bit(PWR->D3CR, PWR_D3CR_VOS);                            \
      }                                                                        \
      UNUSED(tmpreg);                                                          \
} while(0)
#else /* STM32H72xxx and STM32H73xxx lines */
#define __HAL_PWR_VOLTAGESCALING_CONFIG(__REGULATOR__)                         \
do {                                                                           \
      __IO uint32_t tmpreg = 0x00;                                             \
      /* Configure the Voltage Scaling */                                      \
      modify_reg (PWR->D3CR, PWR_D3CR_VOS, (__REGULATOR__));                   \
      /* Delay after setting the voltage scaling */                            \
      tmpreg = read_bit(PWR->D3CR, PWR_D3CR_VOS);                              \
      UNUSED(tmpreg);                                                          \
} while(0)
#endif /* defined(SYSCFG_PWRCR_ODEN) */
#endif /* defined (PWR_SRDCR_VOS) */

/** @brief  Check PWR wake up flags are set or not.
  * @param  __FLAG__: specifies the wake up flag to check.
  *           This parameter can be one of the following values:
  *            @arg PWR_FLAG_WKUP1 : This parameter clear Wake up line 1 flag.
  *            @arg PWR_FLAG_WKUP2 : This parameter clear Wake up line 2 flag.
  *            @arg PWR_FLAG_WKUP3 : This parameter clear Wake up line 3 flag.
  *            @arg PWR_FLAG_WKUP4 : This parameter clear Wake up line 4 flag.
  *            @arg PWR_FLAG_WKUP5 : This parameter clear Wake up line 5 flag.
  *            @arg PWR_FLAG_WKUP6 : This parameter clear Wake up line 6 flag.
  * @note   The PWR_FLAG_WKUP3 and PWR_FLAG_WKUP5 are available only for devices
  *         that support GPIOI port.
  * @retval The (__FLAG__) state (TRUE or FALSE).
  */
#define __HAL_PWR_GET_WAKEUPFLAG(__FLAG__) ((PWR->WKUPFR & (__FLAG__)) ? 0 : 1)

#if defined (DUAL_CORE)
/** @brief  Clear CPU PWR flags.
  * @param  __FLAG__ : Specifies the flag to clear.
  * @note   This parameter is not used for the STM32H7 family and is kept as
  *         parameter just to maintain compatibility with other families.
  * @note   This macro clear all CPU flags STOPF, SBF, SBF_D1, and SBF_D2.
  *           This parameter can be one of the following values :
  *            @arg PWR_CPU_FLAGS : Clear HOLD2F, STOPF, SBF, SBF_D1, and SBF_D2
  *                                 CPU flags.
  * @retval None.
  */
#define __HAL_PWR_CLEAR_FLAG(__FLAG__)      \
do {                                        \
     set_bit(PWR->CPUCR, PWR_CPUCR_CSSF);   \
     set_bit(PWR->CPU2CR, PWR_CPU2CR_CSSF); \
} while(0)
#else
/** @brief  Clear CPU PWR flags.
  * @param  __FLAG__ : Specifies the flag to clear.
  * @note   This parameter is not used for the STM32H7 family and is kept as
  *         parameter just to maintain compatibility with other families.
  * @note   This macro clear all CPU flags.
  *         For single core devices except STM32H7Axxx and STM32H7Bxxx, CPU
  *         flags are STOPF, SBF, SBF_D1 and SBF_D2.
  *         For STM32H7Axxx and STM32H7Bxxx lines, CPU flags are STOPF and SBF.
  * @retval None.
  */
#define __HAL_PWR_CLEAR_FLAG(__FLAG__) set_bit(PWR->CPUCR, PWR_CPUCR_CSSF)
#endif /* defined (DUAL_CORE) */

/** @brief  Clear PWR wake up flags.
  * @param  __FLAG__ : Specifies the wake up flag to be cleared.
  *           This parameter can be one of the following values :
  *            @arg PWR_FLAG_WKUP1 : This parameter clear Wake up line 1 flag.
  *            @arg PWR_FLAG_WKUP2 : This parameter clear Wake up line 2 flag.
  *            @arg PWR_FLAG_WKUP3 : This parameter clear Wake up line 3 flag.
  *            @arg PWR_FLAG_WKUP4 : This parameter clear Wake up line 4 flag.
  *            @arg PWR_FLAG_WKUP5 : This parameter clear Wake up line 5 flag.
  *            @arg PWR_FLAG_WKUP6 : This parameter clear Wake up line 6 flag.
  * @note   The PWR_FLAG_WKUP3 and PWR_FLAG_WKUP5 are available only for devices
  *         that support GPIOI port.
  * @retval None.
  */
#define __HAL_PWR_CLEAR_WAKEUPFLAG(__FLAG__) set_bit(PWR->WKUPCR, (__FLAG__))

/**
  * @brief Enable the PVD EXTI Line 16.
  * @retval None.
  */
#define __HAL_PWR_PVD_EXTI_ENABLE_IT() set_bit(EXTI->IMR1, PWR_EXTI_LINE_PVD)

#if defined (DUAL_CORE)
/**
  * @brief Enable the PVD EXTI D2 Line 16.
  * @retval None.
  */
#define __HAL_PWR_PVD_EXTID2_ENABLE_IT() set_bit(EXTI_D2->IMR1, PWR_EXTI_LINE_PVD)
#endif /* defined (DUAL_CORE) */

/**
  * @brief Disable the PVD EXTI Line 16.
  * @retval None.
  */
#define __HAL_PWR_PVD_EXTI_DISABLE_IT() clear_bit(EXTI->IMR1, PWR_EXTI_LINE_PVD)

#if defined (DUAL_CORE)
/**
  * @brief Disable the PVD EXTI D2 Line 16.
  * @retval None.
  */
#define __HAL_PWR_PVD_EXTID2_DISABLE_IT() clear_bit(EXTI_D2->IMR1, PWR_EXTI_LINE_PVD)
#endif /* defined (DUAL_CORE) */

/**
  * @brief   Enable event on PVD EXTI Line 16.
  * @retval None.
  */
#define __HAL_PWR_PVD_EXTI_ENABLE_EVENT() set_bit(EXTI->EMR1, PWR_EXTI_LINE_PVD)

#if defined (DUAL_CORE)
/**
  * @brief Enable event on PVD EXTI D2 Line.
  * @retval None.
  */
#define __HAL_PWR_PVD_EXTID2_ENABLE_EVENT() set_bit(EXTI_D2->EMR1, PWR_EXTI_LINE_PVD)
#endif /* defined (DUAL_CORE) */

/**
  * @brief   Disable event on PVD EXTI Line 16.
  * @retval None.
  */
#define __HAL_PWR_PVD_EXTI_DISABLE_EVENT() clear_bit(EXTI->EMR1, PWR_EXTI_LINE_PVD)

#if defined (DUAL_CORE)
/**
  * @brief Disable event on PVD EXTI D2 Line.
  * @retval None.
  */
#define __HAL_PWR_PVD_EXTID2_DISABLE_EVENT() clear_bit(EXTI_D2->EMR1, PWR_EXTI_LINE_PVD)
#endif /* defined (DUAL_CORE) */

/**
  * @brief Enable the PVD Rising Interrupt Trigger.
  * @retval None.
  */
#define __HAL_PWR_PVD_EXTI_ENABLE_RISING_EDGE() set_bit(EXTI->RTSR1, PWR_EXTI_LINE_PVD)

/**
  * @brief Disable the PVD Rising Interrupt Trigger.
  * @retval None.
  */
#define __HAL_PWR_PVD_EXTI_DISABLE_RISING_EDGE() clear_bit(EXTI->RTSR1, PWR_EXTI_LINE_PVD)

/**
  * @brief Enable the PVD Falling Interrupt Trigger.
  * @retval None.
  */
#define __HAL_PWR_PVD_EXTI_ENABLE_FALLING_EDGE() set_bit(EXTI->FTSR1, PWR_EXTI_LINE_PVD)

/**
  * @brief Disable the PVD Falling Interrupt Trigger.
  * @retval None.
  */
#define __HAL_PWR_PVD_EXTI_DISABLE_FALLING_EDGE() clear_bit(EXTI->FTSR1, PWR_EXTI_LINE_PVD)

/**
  * @brief Enable the PVD Rising & Falling Interrupt Trigger.
  * @retval None.
  */
#define __HAL_PWR_PVD_EXTI_ENABLE_RISING_FALLING_EDGE() \
do {                                                    \
      __HAL_PWR_PVD_EXTI_ENABLE_RISING_EDGE();          \
      __HAL_PWR_PVD_EXTI_ENABLE_FALLING_EDGE();         \
} while(0);

/**
  * @brief Disable the PVD Rising & Falling Interrupt Trigger.
  * @retval None.
  */
#define __HAL_PWR_PVD_EXTI_DISABLE_RISING_FALLING_EDGE() \
do {                                                     \
      __HAL_PWR_PVD_EXTI_DISABLE_RISING_EDGE();          \
      __HAL_PWR_PVD_EXTI_DISABLE_FALLING_EDGE();         \
} while(0);

/**
  * @brief Check whether the specified PVD EXTI interrupt flag is set or not.
  * @retval EXTI PVD Line Status.
  */
#define __HAL_PWR_PVD_EXTI_GET_FLAG() ((read_bit(EXTI->PR1, PWR_EXTI_LINE_PVD) == PWR_EXTI_LINE_PVD) ? 1UL : 0UL)

#if defined (DUAL_CORE)
/**
  * @brief Checks whether the specified PVD EXTI interrupt flag is set or not.
  * @retval EXTI D2 PVD Line Status.
  */
#define __HAL_PWR_PVD_EXTID2_GET_FLAG() ((read_bit(EXTI_D2->PR1, PWR_EXTI_LINE_PVD) == PWR_EXTI_LINE_PVD) ? 1UL : 0UL)
#endif /* defined (DUAL_CORE) */

/**
  * @brief Clear the PVD EXTI flag.
  * @retval None.
  */
#define __HAL_PWR_PVD_EXTI_CLEAR_FLAG() set_bit(EXTI->PR1, PWR_EXTI_LINE_PVD)

#if defined (DUAL_CORE)
/**
  * @brief Clear the PVD EXTI D2 flag.
  * @retval None.
  */
#define __HAL_PWR_PVD_EXTID2_CLEAR_FLAG() set_bit(EXTI_D2->PR1, PWR_EXTI_LINE_PVD)
#endif /* defined (DUAL_CORE) */

/**
  * @brief  Generates a Software interrupt on PVD EXTI line.
  * @retval None.
  */
#define __HAL_PWR_PVD_EXTI_GENERATE_SWIT() set_bit(EXTI->SWIER1, PWR_EXTI_LINE_PVD)
/**
  * @}
  */

#define PWR_SUPPLY_CONFIG_MASK (PWR_CR3_SMPSLEVEL | PWR_CR3_SMPSEXTHP | PWR_CR3_SMPSEN | PWR_CR3_LDOEN | PWR_CR3_BYPASS)

// PWREx_Supply_configuration PWREx Supply configuration
#define PWR_LDO_SUPPLY                      PWR_CR3_LDOEN                                                               /*!< Core domains are supplied from the LDO                                                                     */
#define PWR_DIRECT_SMPS_SUPPLY              PWR_CR3_SMPSEN                                                              /*!< Core domains are supplied from the SMPS only                                                               */
#define PWR_SMPS_1V8_SUPPLIES_LDO           (PWR_CR3_SMPSLEVEL_0 | PWR_CR3_SMPSEN    | PWR_CR3_LDOEN)                   /*!< The SMPS 1.8V output supplies the LDO which supplies the Core domains                                       */
#define PWR_SMPS_2V5_SUPPLIES_LDO           (PWR_CR3_SMPSLEVEL_1 | PWR_CR3_SMPSEN    | PWR_CR3_LDOEN)                   /*!< The SMPS 2.5V output supplies the LDO which supplies the Core domains                                       */
#define PWR_SMPS_1V8_SUPPLIES_EXT_AND_LDO   (PWR_CR3_SMPSLEVEL_0 | PWR_CR3_SMPSEXTHP | PWR_CR3_SMPSEN | PWR_CR3_LDOEN)  /*!< The SMPS 1.8V output supplies an external circuits and the LDO. The Core domains are supplied from the LDO */
#define PWR_SMPS_2V5_SUPPLIES_EXT_AND_LDO   (PWR_CR3_SMPSLEVEL_1 | PWR_CR3_SMPSEXTHP | PWR_CR3_SMPSEN | PWR_CR3_LDOEN)  /*!< The SMPS 2.5V output supplies an external circuits and the LDO. The Core domains are supplied from the LDO */
#define PWR_SMPS_1V8_SUPPLIES_EXT           (PWR_CR3_SMPSLEVEL_0 | PWR_CR3_SMPSEXTHP | PWR_CR3_SMPSEN | PWR_CR3_BYPASS) /*!< The SMPS 1.8V output supplies an external source which supplies the Core domains                            */
#define PWR_SMPS_2V5_SUPPLIES_EXT           (PWR_CR3_SMPSLEVEL_1 | PWR_CR3_SMPSEXTHP | PWR_CR3_SMPSEN | PWR_CR3_BYPASS) /*!< The SMPS 2.5V output supplies an external source which supplies the Core domains                            */
#define PWR_EXTERNAL_SOURCE_SUPPLY          PWR_CR3_BYPASS                                                              /*!< The SMPS disabled and the LDO Bypass. The Core domains are supplied from an external source                 */

#endif // STM32H7XX_HAL_PWR_2022_08_05_H_
