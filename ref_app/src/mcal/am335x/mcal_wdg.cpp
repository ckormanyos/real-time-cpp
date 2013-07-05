///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_cpu.h>
#include <mcal_wdg.h>
#include <mcal_reg_access.h>

namespace
{
  void wdg_stop()
  {
    mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::wdt1::wspr, 0xAAAAUL>::reg_set();
    while(std::uint32_t(mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::wdt1::wwps>::reg_get() & std::uint32_t(0x3FUL)) != std::uint32_t(0UL)) { mcal::cpu::nop(); }

    mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::wdt1::wspr, 0x5555UL>::reg_set();
    while(std::uint32_t(mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::wdt1::wwps>::reg_get() & std::uint32_t(0x3FUL)) != std::uint32_t(0UL)) { mcal::cpu::nop(); }
  }
}

void mcal::wdg::init(const config_type*)
{
  // TBD: Properly activate the watchdog.
  wdg_stop();
}

void mcal::wdg::trigger()
{
  // TBD: Properly trigger the watchdog.
}
