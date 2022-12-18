///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2022.
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
      constexpr auto plic_base         = static_cast<std::uint32_t>(UINT32_C(0x0C000000));
      constexpr auto plic_enable_0     = static_cast<std::uint32_t>(plic_base + static_cast<std::uint32_t>(UINT32_C(0x00002000)));
      constexpr auto plic_enable_1     = static_cast<std::uint32_t>(plic_base + static_cast<std::uint32_t>(UINT32_C(0x00002004)));

      constexpr auto clint_base        = static_cast<std::uint32_t>(UINT32_C(0x02000000));
      constexpr auto clint_mtime       = static_cast<std::uint32_t>(clint_base + static_cast<std::uint32_t>(UINT32_C(0x0000BFF8)));
      constexpr auto clint_mtimeh      = static_cast<std::uint32_t>(clint_base + static_cast<std::uint32_t>(UINT32_C(0x0000BFFC)));
      constexpr auto clint_mtimecmp    = static_cast<std::uint32_t>(clint_base + static_cast<std::uint32_t>(UINT32_C(0x00004000)));
      constexpr auto clint_mtimecmph   = static_cast<std::uint32_t>(clint_base + static_cast<std::uint32_t>(UINT32_C(0x00004004)));

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
