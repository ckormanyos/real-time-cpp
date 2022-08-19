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
  #define PWR_REGULATOR_VOLTAGE_SCALE0           (PWR_SRDCR_VOS_1 | PWR_SRDCR_VOS_0)
  #define PWR_REGULATOR_VOLTAGE_SCALE1           (PWR_SRDCR_VOS_1)
  #define PWR_REGULATOR_VOLTAGE_SCALE2           (PWR_SRDCR_VOS_0)
  #define PWR_REGULATOR_VOLTAGE_SCALE3           (0U)

  #define PWR_SUPPLY_CONFIG_MASK                 (PWR_CR3_SMPSLEVEL | PWR_CR3_SMPSEXTHP | PWR_CR3_SMPSEN | PWR_CR3_LDOEN | PWR_CR3_BYPASS)

  // PWREx_Supply_configuration PWREx Supply configuration
  #define PWR_LDO_SUPPLY                         PWR_CR3_LDOEN
  #define PWR_DIRECT_SMPS_SUPPLY                 PWR_CR3_SMPSEN
  #define PWR_SMPS_1V8_SUPPLIES_LDO              (PWR_CR3_SMPSLEVEL_0 | PWR_CR3_SMPSEN    | PWR_CR3_LDOEN)
  #define PWR_SMPS_2V5_SUPPLIES_LDO              (PWR_CR3_SMPSLEVEL_1 | PWR_CR3_SMPSEN    | PWR_CR3_LDOEN)
  #define PWR_SMPS_1V8_SUPPLIES_EXT_AND_LDO      (PWR_CR3_SMPSLEVEL_0 | PWR_CR3_SMPSEXTHP | PWR_CR3_SMPSEN | PWR_CR3_LDOEN)
  #define PWR_SMPS_2V5_SUPPLIES_EXT_AND_LDO      (PWR_CR3_SMPSLEVEL_1 | PWR_CR3_SMPSEXTHP | PWR_CR3_SMPSEN | PWR_CR3_LDOEN)
  #define PWR_SMPS_1V8_SUPPLIES_EXT              (PWR_CR3_SMPSLEVEL_0 | PWR_CR3_SMPSEXTHP | PWR_CR3_SMPSEN | PWR_CR3_BYPASS)
  #define PWR_SMPS_2V5_SUPPLIES_EXT              (PWR_CR3_SMPSLEVEL_1 | PWR_CR3_SMPSEXTHP | PWR_CR3_SMPSEN | PWR_CR3_BYPASS)
  #define PWR_EXTERNAL_SOURCE_SUPPLY             PWR_CR3_BYPASS

#endif // STM32H7XX_HAL_PWR_2022_08_05_H_
