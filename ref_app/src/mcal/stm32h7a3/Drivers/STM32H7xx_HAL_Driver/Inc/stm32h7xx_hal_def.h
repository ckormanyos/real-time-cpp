///////////////////////////////////////////////////////////////////////////////
//  Modified by Christopher Kormanyos 2022.
//  Distributed under (see below).
//

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

#ifndef STM32H7XX_HAL_DEF_2022_08_05_H_
  #define STM32H7XX_HAL_DEF_2022_08_05_H_

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

#endif // STM32H7XX_HAL_DEF_2022_08_05_H_
