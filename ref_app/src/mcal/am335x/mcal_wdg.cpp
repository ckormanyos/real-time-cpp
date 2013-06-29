///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_cpu.h>
#include <mcal_wdg.h>
#include <am335x_hw_regs.h>

namespace
{
  void wdg_stop()
  {
    WDT1->WSPR = 0xAAAAu;
    while(std::uint32_t(WDT1->WWPS & 0x3FU) != std::uint32_t(0UL)) { mcal::cpu::nop(); }

    WDT1->WSPR = 0x5555u;
    while(std::uint32_t(WDT1->WWPS & 0x3FU) != std::uint32_t(0UL)) { mcal::cpu::nop(); }
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
