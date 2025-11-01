///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2024.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_REG_2010_04_10_H
  #define MCAL_REG_2010_04_10_H

  #include <cstdint>

  namespace mcal
  {
    namespace reg
    {
      // CLIC (timer) registers.
      constexpr std::uintptr_t clic_ctrl_addr { UINT32_C(0x02000000) };
      constexpr std::uintptr_t clic_msip      { clic_ctrl_addr + UINT32_C(0x00000000) };
      constexpr std::uintptr_t clic_mtimecmp  { clic_ctrl_addr + UINT32_C(0x00004000) };
      constexpr std::uintptr_t clic_mtime     { clic_ctrl_addr + UINT32_C(0x0000BFF8) };
      constexpr std::uintptr_t clic_clk_gate  { clic_ctrl_addr + UINT32_C(0x007FF000) };
    }
  }

  #include <mcal/mcal_reg_access_dynamic.h>
  #include <mcal/mcal_reg_access_static.h>

#endif // MCAL_REG_2010_04_10_H
