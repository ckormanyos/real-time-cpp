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
      // Global base addresses.
      constexpr std::uint32_t scs_base        = UINT32_C(0xE000E000);
      constexpr std::uint32_t nvic_base       = scs_base + UINT32_C(0x00000100);

      // Interrupt control registers.
      constexpr std::uint32_t nvic_iser { nvic_base + UINT32_C(0x00000000) };  // Offset: 0x000 Interrupt set enable registers.
      constexpr std::uint32_t nvic_icer { nvic_base + UINT32_C(0x00000080) };  // Offset: 0x080 Interrupt clear enable registers.
      constexpr std::uint32_t nvic_ispr { nvic_base + UINT32_C(0x00000100) };  // Offset: 0x100 Interrupt set pending registers.
      constexpr std::uint32_t nvic_icpr { nvic_base + UINT32_C(0x00000180) };  // Offset: 0x180 Interrupt clear pending registers.
      constexpr std::uint32_t nvic_ip   { nvic_base + UINT32_C(0x00000300) };  // Offset: 0x300 Interrupt priority registers (each one 8 bits wide).
    }
  }

  #include <mcal/mcal_reg_access_dynamic.h>
  #include <mcal/mcal_reg_access_static.h>

#endif // MCAL_REG_2010_04_10_H
