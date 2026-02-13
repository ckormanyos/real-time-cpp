///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2026.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_REG_2026_02_11_H
  #define MCAL_REG_2026_02_11_H

  #include <cstdint>

  namespace mcal
  {
    namespace reg
    {
      constexpr std::uint32_t clint_base        { UINT32_C(0x20000000) };
      constexpr std::uint32_t clint_mtime       { clint_base + static_cast<std::uint32_t>(UINT32_C(0x0000BFF8)) };
      constexpr std::uint32_t clint_mtimeh      { clint_base + static_cast<std::uint32_t>(UINT32_C(0x0000BFFC)) };
      constexpr std::uint32_t clint_mtimecmp    { clint_base + static_cast<std::uint32_t>(UINT32_C(0x00004000)) };
      constexpr std::uint32_t clint_mtimecmph   { clint_base + static_cast<std::uint32_t>(UINT32_C(0x00004004)) };

      constexpr std::uint32_t clic_base         { UINT32_C(0x20800000) };

      constexpr std::uint32_t gpio_base         { UINT32_C(0x500E0000) };
      constexpr std::uint32_t lp_io_mux_base    { UINT32_C(0x5012B000) };
      constexpr std::uint32_t io_mux_base       { UINT32_C(0x500E1000) };
    }
  }

  #include <mcal/mcal_reg_access_dynamic.h>
  #include <mcal/mcal_reg_access_static.h>

#endif // MCAL_REG_2026_02_11_H
