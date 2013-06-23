///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_wdg.h>
#include <am335x_hw_regs.h>

void Wdg_Stop(void)
{
  WDT1->WSPR = 0xAAAAu;
  while((WDT1->WWPS & 0x3Fu) != 0x00) { ; }

  WDT1->WSPR = 0x5555u;
  while((WDT1->WWPS & 0x3Fu) != 0x00) { ; }
}

void mcal::wdg::init(const config_type*)
{
  // TBD: Properly activate the watchdog.
  Wdg_Stop();
}

void mcal::wdg::trigger()
{
  // TBD: Properly trigger the watchdog.
}
