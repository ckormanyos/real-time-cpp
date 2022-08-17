///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2013 - 2020.
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

#ifndef STM32H7xx_H
  #define STM32H7xx_H

  #include <cstdint>

  #include "stm32h7a3xxq.h"

  #include <mcal_reg.h>

  #if !defined  (STM32H7)
  #define STM32H7
  #endif

  constexpr auto __STM32H7xx_CMSIS_DEVICE_VERSION_MAIN = static_cast<unsigned int>(0x01);
  constexpr auto __STM32H7xx_CMSIS_DEVICE_VERSION_SUB1 = static_cast<unsigned int>(0x0A);
  constexpr auto __STM32H7xx_CMSIS_DEVICE_VERSION_SUB2 = static_cast<unsigned int>(0x02);
  constexpr auto __STM32H7xx_CMSIS_DEVICE_VERSION_RC   = static_cast<unsigned int>(0x00);
  constexpr auto __STM32H7xx_CMSIS_DEVICE_VERSION      = static_cast<unsigned int>
                                                         (
                                                             (__STM32H7xx_CMSIS_DEVICE_VERSION_MAIN << 24U)
                                                           | (__STM32H7xx_CMSIS_DEVICE_VERSION_SUB1 << 16U)
                                                           | (__STM32H7xx_CMSIS_DEVICE_VERSION_SUB2 <<  8U)
                                                           | (__STM32H7xx_CMSIS_DEVICE_VERSION_RC   <<  0U)
                                                         );

  template<typename UnknownAddressType,
           typename UnknownValueType>
  static inline auto read_bit(const UnknownAddressType& reg, const UnknownValueType bit) -> UnknownValueType
  {
    using local_value_type = UnknownValueType;

    auto addr = (volatile local_value_type*) &reg;

    const local_value_type result = *addr;

    return static_cast<local_value_type>(result & bit);
  }

  template<typename UnknownAddressType,
           typename UnknownValueType>
  static inline auto write_reg(UnknownAddressType& reg, const UnknownValueType val) -> void
  {
    using local_value_type = UnknownValueType;

    auto addr = (volatile local_value_type*) &reg;

    *addr = val;
  }

  template<typename UnknownAddressType>
  static inline auto read_reg(const UnknownAddressType& reg) -> std::uint32_t
  {
    using local_value_type = std::uint32_t;

    const auto addr = (const volatile local_value_type*) &reg;

    return *addr;
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

#endif // STM32H7xx_H
