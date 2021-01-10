///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_reg.h>
#include <mcal_wdg.h>

void mcal::wdg::init(const config_type*)
{
  // Set main clock prescaler (uses protect protected I/O registers).
  volatile std::uint8_t* p_wdt_ctrla = (volatile std::uint8_t*) mcal::reg::wdt_ctrla;
  volatile std::uint8_t* p_ccp       = (volatile std::uint8_t*) mcal::reg::reg_ccp;

  // Set the watchdog timer to cycle watchdog with a period of about 2s.
  *p_ccp       = 0xD8U;
  *p_wdt_ctrla = 9U;
}

void mcal::wdg::secure::trigger()
{
  asm volatile("wdr");
}
