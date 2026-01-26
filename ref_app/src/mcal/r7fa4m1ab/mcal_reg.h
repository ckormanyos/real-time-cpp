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
      // Global base addresses.
      constexpr std::uint32_t scs_base            { UINT32_C(0xE000E000) };

      // Individual unit base addresses.
      constexpr std::uint32_t scb_base            { scs_base + UINT32_C(0x00000D00) };
      constexpr std::uint32_t system_base         { UINT32_C(0x4001E000) };
      constexpr std::uint32_t unknown_hococr2     { UINT32_C(0x4001E037) };
      constexpr std::uint32_t pfs_base            { UINT32_C(0x40040800) };
      constexpr std::uint32_t pmisc_base          { UINT32_C(0x40040D00) };

      // Core system registers.
      constexpr std::uint32_t scb_cpacr           { scb_base + UINT32_C(0x00000088) };

     static_assert(scb_cpacr == UINT32_C(0xE000ED88), "Error: wrong scb_cpacr register address)");

      // System (system struct) registers.
      constexpr std::uint32_t system_sckdivcr     { system_base + UINT32_C(0x00000020) };
      constexpr std::uint32_t system_sckscr       { system_base + UINT32_C(0x00000026) };
      constexpr std::uint32_t system_memwait      { system_base + UINT32_C(0x00000031) };
      constexpr std::uint32_t system_hococr       { system_base + UINT32_C(0x00000036) };
      constexpr std::uint32_t system_oscsf        { system_base + UINT32_C(0x0000003C) };
      constexpr std::uint32_t system_opccr        { system_base + UINT32_C(0x000000A0) };
      constexpr std::uint32_t system_prcr         { system_base + UINT32_C(0x000003FE) };

      // Miscellaneous port control registers.
      constexpr std::uint32_t pmisc_pwpr          { pmisc_base + UINT32_C(0x00000003) };

      // Port registers.
      constexpr std::uint32_t pfs_p001pfs_base    { pfs_base + UINT32_C(0x00000004) };
      constexpr std::uint32_t pfs_p010pfs_base    { pfs_base + UINT32_C(0x00000028) };
      constexpr std::uint32_t pfs_p011pfs_base    { pfs_base + UINT32_C(0x0000002C) };
      constexpr std::uint32_t pfs_p111pfs_base    { pfs_base + UINT32_C(0x0000006C) };
      constexpr std::uint32_t pfs_p200pfs_base    { pfs_base + UINT32_C(0x00000080) };
      constexpr std::uint32_t pfs_p300pfs_base    { pfs_base + UINT32_C(0x000000C0) };
      constexpr std::uint32_t pfs_p400pfs_base    { pfs_base + UINT32_C(0x00000100) };

    } // namespace reg
  } // namespace mcal

  #include <mcal/mcal_reg_access_dynamic.h>
  #include <mcal/mcal_reg_access_static.h>

#endif // MCAL_REG_2010_04_10_H
