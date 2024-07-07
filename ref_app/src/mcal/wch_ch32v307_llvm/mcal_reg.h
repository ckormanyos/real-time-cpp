///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2024.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_REG_2022_12_16_H
  #define MCAL_REG_2022_12_16_H

  #include <cstdint>

  namespace mcal
  {
    namespace reg
    {
      constexpr std::uint32_t rcc_base          = static_cast<std::uint32_t>(UINT32_C(0x40021000));
      constexpr std::uint32_t stk_base_address  = static_cast<std::uint32_t>(UINT32_C(0xE000F000));

      constexpr std::uint32_t r32_stk_ctlr      = static_cast<std::uint32_t>(stk_base_address + static_cast<std::uint32_t>(UINT32_C(0x00)));
      constexpr std::uint32_t r32_stk_sr        = static_cast<std::uint32_t>(stk_base_address + static_cast<std::uint32_t>(UINT32_C(0x04)));
      constexpr std::uint32_t r32_stk_cntl      = static_cast<std::uint32_t>(stk_base_address + static_cast<std::uint32_t>(UINT32_C(0x08)));
      constexpr std::uint32_t r32_stk_cnth      = static_cast<std::uint32_t>(stk_base_address + static_cast<std::uint32_t>(UINT32_C(0x0C)));
      constexpr std::uint32_t r32_stk_cmplr     = static_cast<std::uint32_t>(stk_base_address + static_cast<std::uint32_t>(UINT32_C(0x10)));
      constexpr std::uint32_t r32_stk_cmphr     = static_cast<std::uint32_t>(stk_base_address + static_cast<std::uint32_t>(UINT32_C(0x14)));

      constexpr std::uint32_t rcc_ctlr          = static_cast<std::uint32_t>(rcc_base + static_cast<std::uint32_t>(UINT32_C(0x00)));
      constexpr std::uint32_t rcc_cfgr0         = static_cast<std::uint32_t>(rcc_base + static_cast<std::uint32_t>(UINT32_C(0x04)));
      constexpr std::uint32_t rcc_apb2pcenr     = static_cast<std::uint32_t>(rcc_base + static_cast<std::uint32_t>(UINT32_C(0x18)));
      constexpr std::uint32_t rcc_cfgr2         = static_cast<std::uint32_t>(rcc_base + static_cast<std::uint32_t>(UINT32_C(0x2C)));

      constexpr std::uint32_t gpioa_base        = static_cast<std::uint32_t>(UINT32_C(0x40010800));
      constexpr std::uint32_t gpiob_base        = static_cast<std::uint32_t>(UINT32_C(0x40010C00));
      constexpr std::uint32_t gpioc_base        = static_cast<std::uint32_t>(UINT32_C(0x40011000));
      constexpr std::uint32_t gpiod_base        = static_cast<std::uint32_t>(UINT32_C(0x40011400));
      constexpr std::uint32_t gpioe_base        = static_cast<std::uint32_t>(UINT32_C(0x40011800));
    }
  }

  #include <mcal/mcal_reg_access_dynamic.h>
  #include <mcal/mcal_reg_access_static.h>

#endif // MCAL_REG_2022_12_16_H
