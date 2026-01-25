///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2026.
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
      // System registers.
      constexpr std::uint32_t system_base       { UINT32_C(0x4001E000) };
      constexpr std::uint32_t unknown_hococr2   { UINT32_C(0x4001E037) };

      constexpr std::uint32_t system_sckdivcr   { system_base + UINT32_C(0x00000020) };
      constexpr std::uint32_t system_sckscr     { system_base + UINT32_C(0x00000026) };
      constexpr std::uint32_t system_memwait    { system_base + UINT32_C(0x00000031) };
      constexpr std::uint32_t system_hococr     { system_base + UINT32_C(0x00000036) };
      constexpr std::uint32_t system_oscsf      { system_base + UINT32_C(0x0000003C) };
      constexpr std::uint32_t system_opccr      { system_base + UINT32_C(0x000000A0) };
      constexpr std::uint32_t system_prcr       { system_base + UINT32_C(0x000003FE) };
    } // namespace reg
  } // namespace mcal

  #include <mcal/mcal_reg_access_dynamic.h>
  #include <mcal/mcal_reg_access_static.h>

#endif // MCAL_REG_2010_04_10_H
