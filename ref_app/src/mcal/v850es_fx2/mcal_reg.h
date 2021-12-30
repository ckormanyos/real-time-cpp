///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2021.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_REG_2021_12_25_H_
  #define MCAL_REG_2021_12_25_H_

  #include <cstdint>

  namespace mcal
  {
    namespace reg
    {
      // System registers.
      constexpr std::uint32_t bpc     = UINT32_C(0xFFFFF064);
      constexpr std::uint32_t bsc     = UINT32_C(0xFFFFF066);
      constexpr std::uint32_t vswc    = UINT32_C(0xFFFFF06E);
      constexpr std::uint32_t sys     = UINT32_C(0xFFFFF802);
      constexpr std::uint32_t prcmd   = UINT32_C(0xFFFFF1FC);

      // Port registers.
      constexpr std::uint32_t p0      = UINT32_C(0xFFFFF400);
      constexpr std::uint32_t p1      = UINT32_C(0xFFFFF402);
      constexpr std::uint32_t pdll    = UINT32_C(0xFFFFF004);
      constexpr std::uint32_t pdlh    = UINT32_C(0xFFFFF005);
      constexpr std::uint32_t p3l     = UINT32_C(0xFFFFF406);
      constexpr std::uint32_t p3h     = UINT32_C(0xFFFFF407);
      constexpr std::uint32_t p4      = UINT32_C(0xFFFFF408);
      constexpr std::uint32_t p5      = UINT32_C(0xFFFFF40A);
      constexpr std::uint32_t p7l     = UINT32_C(0xFFFFF40E);
      constexpr std::uint32_t p7h     = UINT32_C(0xFFFFF40F);
      constexpr std::uint32_t p9l     = UINT32_C(0xFFFFF412);
      constexpr std::uint32_t p9h     = UINT32_C(0xFFFFF413);

      constexpr std::uint32_t pm0     = static_cast<std::uint32_t>(p0   + 0x20U);
      constexpr std::uint32_t pm1     = static_cast<std::uint32_t>(p1   + 0x20U);
      constexpr std::uint32_t pmdll   = static_cast<std::uint32_t>(pdll + 0x20U);
      constexpr std::uint32_t pmdlh   = static_cast<std::uint32_t>(pdlh + 0x20U);
      constexpr std::uint32_t pm3l    = static_cast<std::uint32_t>(p3l  + 0x20U);
      constexpr std::uint32_t pm3h    = static_cast<std::uint32_t>(p3h  + 0x20U);
      constexpr std::uint32_t pm4     = static_cast<std::uint32_t>(p4   + 0x20U);
      constexpr std::uint32_t pm5     = static_cast<std::uint32_t>(p5   + 0x20U);
      constexpr std::uint32_t pm7l    = static_cast<std::uint32_t>(p7l  + 0x20U);
      constexpr std::uint32_t pm7h    = static_cast<std::uint32_t>(p7h  + 0x20U);
      constexpr std::uint32_t pm9l    = static_cast<std::uint32_t>(p9l  + 0x20U);
      constexpr std::uint32_t pm9h    = static_cast<std::uint32_t>(p9h  + 0x20U);

      constexpr std::uint32_t pmc0    = static_cast<std::uint32_t>(p0  + 0x40U);
      constexpr std::uint32_t pmc1    = static_cast<std::uint32_t>(p1  + 0x40U);
      constexpr std::uint32_t pmc3l   = static_cast<std::uint32_t>(p3l + 0x40U);
      constexpr std::uint32_t pmc3h   = static_cast<std::uint32_t>(p3h + 0x40U);
      constexpr std::uint32_t pmc4    = static_cast<std::uint32_t>(p4  + 0x40U);
      constexpr std::uint32_t pmc5    = static_cast<std::uint32_t>(p5  + 0x40U);
      constexpr std::uint32_t pmc7l   = static_cast<std::uint32_t>(p7l + 0x40U);
      constexpr std::uint32_t pmc7h   = static_cast<std::uint32_t>(p7h + 0x40U);
      constexpr std::uint32_t pmc9l   = static_cast<std::uint32_t>(p9l + 0x40U);
      constexpr std::uint32_t pmc9h   = static_cast<std::uint32_t>(p9h + 0x40U);

      constexpr std::uint32_t pfc0    = static_cast<std::uint32_t>(p0  + 0x60U);
      constexpr std::uint32_t pfc1    = static_cast<std::uint32_t>(p1  + 0x60U);
      constexpr std::uint32_t pfcdl   = static_cast<std::uint32_t>(p3l + 0x60U);
      constexpr std::uint32_t pfcdh   = static_cast<std::uint32_t>(p3h + 0x60U);
      constexpr std::uint32_t pfc3l   = static_cast<std::uint32_t>(p3l + 0x60U);
      constexpr std::uint32_t pfc3h   = static_cast<std::uint32_t>(p3h + 0x60U);
      constexpr std::uint32_t pfc4    = static_cast<std::uint32_t>(p4  + 0x60U);
      constexpr std::uint32_t pfc5    = static_cast<std::uint32_t>(p5  + 0x60U);
      constexpr std::uint32_t pfc7l   = static_cast<std::uint32_t>(p7l + 0x60U);
      constexpr std::uint32_t pfc7h   = static_cast<std::uint32_t>(p7h + 0x60U);
      constexpr std::uint32_t pfc9l   = static_cast<std::uint32_t>(p9l + 0x60U);
      constexpr std::uint32_t pfc9h   = static_cast<std::uint32_t>(p9h + 0x60U);

      // Timer registers.
      constexpr std::uint32_t tq0ctl0  = UINT32_C(0xFFFFF540);
      constexpr std::uint32_t tq0ctl1  = UINT32_C(0xFFFFF541);
      constexpr std::uint32_t tq0cnt   = UINT32_C(0xFFFFF54E);

      // Clock.
      constexpr std::uint32_t osts    =  UINT32_C(0xFFFFF6C0);
      constexpr std::uint32_t plls    =  UINT32_C(0xFFFFF6C1);
      constexpr std::uint32_t ostc    =  UINT32_C(0xFFFFF6C2);
      constexpr std::uint32_t lockr   =  UINT32_C(0xFFFFF824);
      constexpr std::uint32_t pcc     =  UINT32_C(0xFFFFF828);
      constexpr std::uint32_t pllctl  =  UINT32_C(0xFFFFF82C);
      constexpr std::uint32_t mcm     =  UINT32_C(0xFFFFF860);

      // Watchdog registers.
      constexpr std::uint32_t wdtm2   =  UINT32_C(0xFFFFF6D0);
      constexpr std::uint32_t wdte    =  UINT32_C(0xFFFFF6D1);

      // Interrupt registers.
      constexpr std::uint32_t tq0ovic  = UINT32_C(0xFFFFF122);
    }
  }

  #include <mcal/mcal_reg_access_dynamic.h>
  #include <mcal/mcal_reg_access_static.h>

#endif // MCAL_REG_2021_12_25_H_
