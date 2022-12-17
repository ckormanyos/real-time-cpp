﻿///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2022.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_REG_2022_12_16_H_
  #define MCAL_REG_2022_12_16_H_

  #include <cstdint>

  namespace mcal
  {
    namespace reg
    {
      // Global base addresses.
      constexpr auto gpio0_base        = static_cast<std::uint32_t>(UINT32_C(0x10012000));
      constexpr auto gpio0_input_val   = static_cast<std::uint32_t>(gpio0_base + static_cast<std::uint32_t>(UINT32_C(0x00000000)));
      constexpr auto gpio0_input_en    = static_cast<std::uint32_t>(gpio0_base + static_cast<std::uint32_t>(UINT32_C(0x00000004)));
      constexpr auto gpio0_output_en   = static_cast<std::uint32_t>(gpio0_base + static_cast<std::uint32_t>(UINT32_C(0x00000008)));
      constexpr auto gpio0_output_val  = static_cast<std::uint32_t>(gpio0_base + static_cast<std::uint32_t>(UINT32_C(0x0000000C)));
    }
  }

  #include <mcal/mcal_reg_access_dynamic.h>
  #include <mcal/mcal_reg_access_static.h>

#endif // MCAL_REG_2022_12_16_H_