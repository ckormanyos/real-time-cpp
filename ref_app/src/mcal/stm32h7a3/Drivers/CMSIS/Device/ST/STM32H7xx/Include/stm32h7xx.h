///////////////////////////////////////////////////////////////////////////////
//  Modified by Christopher Kormanyos 2022.
//  Distributed under (see below).
//

/*
  ******************************************************************************
  * @file    stm32h7xx.h
  * @author  MCD Application Team
  * @brief   CMSIS STM32H7xx Device Peripheral Access Layer Header File.
  *
  *          The file is the unique include file that the application programmer
  *          is using in the C source code, usually in main.c. This file contains:
  *           - Configuration section that allows to select:
  *              - The STM32H7xx device used in the target application
  *              - To use or not the peripheral's drivers in application code(i.e.
  *                code will be based on direct access to peripheral's registers
  *                rather than drivers API), this option is controlled by
  *                "#define USE_HAL_DRIVER"
  *
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

#ifndef STM32H7XX_2022_08_05_H_
  #define STM32H7XX_2022_08_05_H_

  #include <cstdint>

  #include "stm32h7a3xxq.h"

  #include <mcal_reg.h>

  #if !defined(STM32H7)
  #define STM32H7
  #endif

  // Extracted from version:
  //   __STM32H7xx_CMSIS_DEVICE_VERSION_MAIN 0x01
  //   __STM32H7xx_CMSIS_DEVICE_VERSION_SUB1 0x0A
  //   __STM32H7xx_CMSIS_DEVICE_VERSION_SUB2 0x02
  //   __STM32H7xx_CMSIS_DEVICE_VERSION_RC   0x00

  template<typename UnknownAddressType,
           typename UnknownValueType>
  static inline auto write_reg(UnknownAddressType& reg, const UnknownValueType val) -> void
  {
    using local_address_type = UnknownAddressType;
    using local_value_type   = UnknownValueType;

    mcal::reg::reg_access_dynamic<local_address_type,
                                  local_value_type>::reg_set((local_address_type) &reg, val);
  }

  template<typename UnknownAddressType>
  static inline auto read_reg(const UnknownAddressType& reg) -> std::uint32_t
  {
    using local_address_type = UnknownAddressType;
    using local_value_type   = std::uint32_t;

    return mcal::reg::reg_access_dynamic<local_address_type,
                                         local_value_type>::reg_get((local_address_type) &reg);
  }

  template<typename UnknownAddressType,
           typename UnknownValueType>
  static inline auto read_bit(const UnknownAddressType& reg, const UnknownValueType bit) -> UnknownValueType
  {
    using local_value_type = UnknownValueType;

    return static_cast<local_value_type>(read_reg(reg) & bit);
  }

  template<typename UnknownAddressType,
           typename UnknownValueType>
  static inline auto set_bit(      UnknownAddressType& reg,
                             const UnknownValueType    bit) -> void
  {
    using local_value_type = UnknownValueType;

    const auto val =
      static_cast<local_value_type>
      (
          static_cast<local_value_type>(read_reg(reg))
        | static_cast<local_value_type>(bit)
      );

    write_reg(reg, val);
  }

  template<typename UnknownAddressType,
           typename UnknownValueType>
  static inline auto clear_bit(      UnknownAddressType& reg,
                               const UnknownValueType    bit) -> void
  {
    using local_value_type = UnknownValueType;

    const auto val =
      static_cast<local_value_type>
      (
          static_cast<local_value_type>(read_reg(reg))
        & static_cast<local_value_type>(~bit)
      );

    write_reg(reg, val);
  }

  template<typename UnknownAddressType,
           typename UnknownValueType>
  static inline auto modify_reg(      UnknownAddressType& reg,
                                const UnknownValueType    clearmask,
                                const UnknownValueType    setmask) -> void
  {
    using local_value_type = std::uint32_t;

    const auto reg_val =
      static_cast<local_value_type>
      (
          (read_reg(reg) & static_cast<local_value_type>(~clearmask))
        | static_cast<local_value_type>(setmask)
      );

    write_reg(reg, reg_val);
  }

#endif // STM32H7XX_2022_08_05_H_
