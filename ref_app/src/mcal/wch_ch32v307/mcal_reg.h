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
      constexpr auto stk_base_address  = static_cast<std::uint32_t>(UINT32_C(0xE000F000));

      constexpr auto r32_stk_ctlr      = static_cast<std::uint32_t>(stk_base_address + static_cast<std::uint32_t>(UINT32_C(0x00)));
      constexpr auto r32_stk_sr        = static_cast<std::uint32_t>(stk_base_address + static_cast<std::uint32_t>(UINT32_C(0x04)));
      constexpr auto r32_stk_cntl      = static_cast<std::uint32_t>(stk_base_address + static_cast<std::uint32_t>(UINT32_C(0x08)));
      constexpr auto r32_stk_cnth      = static_cast<std::uint32_t>(stk_base_address + static_cast<std::uint32_t>(UINT32_C(0x0C)));
      constexpr auto r32_stk_cmplr     = static_cast<std::uint32_t>(stk_base_address + static_cast<std::uint32_t>(UINT32_C(0x10)));
      constexpr auto r32_stk_cmphr     = static_cast<std::uint32_t>(stk_base_address + static_cast<std::uint32_t>(UINT32_C(0x14)));
    }
  }

  #include <mcal/mcal_reg_access_dynamic.h>
  #include <mcal/mcal_reg_access_static.h>

#endif // MCAL_REG_2022_12_16_H
