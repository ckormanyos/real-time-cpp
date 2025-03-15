///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_REG_2025_03_15_H
  #define MCAL_REG_2025_03_15_H

  #include <cstdint>

  namespace mcal
  {
    namespace reg
    {
      namespace gpio
      {
        constexpr std::uint32_t rtc_gpio_base                                  { UINT32_C(0x0000A400) };
        constexpr std::uint32_t rtc_gpio_out_reg                               { rtc_gpio_base + UINT32_C(0x00000000) };
        constexpr std::uint32_t rtc_gpio_enable_reg                            { rtc_gpio_base + UINT32_C(0x0000000C) };
      }
    }
  }

  #include <mcal/mcal_reg_access_dynamic.h>
  #include <mcal/mcal_reg_access_static.h>

#endif // MCAL_REG_2025_03_15_H
