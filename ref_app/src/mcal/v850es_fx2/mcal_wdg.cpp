///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2021.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_reg.h>
#include <mcal_wdg.h>

extern "C" void HalWdtService(void);

extern "C" void HalWdtService(void) { mcal::wdg::secure::trigger(); }

void mcal::wdg::init(const config_type*)
{
  // The watchdog invokes a system reset (0x60 = bit pattern 11 00000).
  // The watchdog is middle-fast (i.e., having a watchdog period
  // of approximately 0.27 sec at 32MHz).

  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint8_t,
                               mcal::reg::wdtm2,
                               UINT8_C(0x64)>::reg_set();
}

void mcal::wdg::secure::trigger()
{
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint8_t,
                               mcal::reg::wdte,
                               UINT8_C(0xAC)>::reg_set();
}
