///////////////////////////////////////////////////////////////////////////////
//  Modified by Christopher Kormanyos 2022.
//  Distributed under (see below).
//

/*
  ******************************************************************************
  * @file    stm32h7xx_hal_flash.h
  * @author  MCD Application Team
  * @brief   Header file of FLASH HAL module.
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

#ifndef STM32H7XX_HAL_FLASH_2022_08_05_H_
  #define STM32H7XX_HAL_FLASH_2022_08_05_H_

  #include <cstdint>

  #include "stm32h7xx_hal_def.h"

  static inline auto hal_flash_set_latency(const std::uint32_t latency) -> void
  {
    modify_reg
    (
      FLASH->ACR,
      static_cast<std::uint32_t>(FLASH_ACR_LATENCY),
      latency
    );
  }

  static inline auto hal_flash_get_latency() -> std::uint32_t
  {
    return read_bit(FLASH->ACR, static_cast<std::uint32_t>(FLASH_ACR_LATENCY));
  }

#endif // STM32H7XX_HAL_FLASH_2022_08_05_H_
