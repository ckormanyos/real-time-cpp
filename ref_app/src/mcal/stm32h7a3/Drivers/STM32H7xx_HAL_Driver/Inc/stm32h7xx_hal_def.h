/*
  ******************************************************************************
  * @file    stm32h7xx_hal_def.h
  * @author  MCD Application Team
  * @brief   This file contains HAL common defines, enumeration, macros and
  *          structures definitions.
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

#ifndef STM32H7xx_HAL_DEF
  #define STM32H7xx_HAL_DEF

  #include <cmath>
  #include <cstddef>

  #include "stm32h7xx.h"

  typedef enum
  {
    HAL_OK       = 0x00,
    HAL_ERROR    = 0x01,
    HAL_BUSY     = 0x02,
    HAL_TIMEOUT  = 0x03
  }
  HAL_StatusTypeDef;

  #define UNUSED(x) ((void)(x))

#endif // STM32H7xx_HAL_DEF
