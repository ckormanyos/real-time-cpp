///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2018 - 2023.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_reg.h>
#include <mcal_wdg.h>

auto mcal::wdg::init(const config_type*) -> void
{
  // Set the watchdog timer cycle period to approximately 2s.

  // CCP = static_cast<std::uint8_t>(UINT8_C(0xD8));
  mcal::reg::reg_access_static<std::uint8_t,
                               std::uint8_t,
                               mcal::reg::sys_ccp,
                               static_cast<std::uint8_t>(UINT8_C(0xD8))>::reg_set();

  // WDT_CTRLA = static_cast<std::uint8_t>(UINT8_C(9));
  mcal::reg::reg_access_static<std::uint16_t,
                               std::uint8_t,
                               mcal::reg::wdt_ctrla,
                               static_cast<std::uint8_t>(UINT8_C(9))>::reg_set();
}

auto mcal::wdg::secure::trigger() -> void
{
  asm volatile("wdr");
}
