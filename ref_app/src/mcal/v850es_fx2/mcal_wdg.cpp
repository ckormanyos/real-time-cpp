///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2021.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_reg.h>
#include <mcal_wdg.h>

void mcal::wdg::init(const config_type*)
{
  // The watchdog is middle-fast.
  // TBD: Verify what setting this is.
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint8_t,
                               mcal::reg::wdtm2,
                               UINT8_C(0x6F)>::reg_set();
}

void mcal::wdg::secure::trigger()
{
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint8_t,
                               mcal::reg::wdte,
                               UINT8_C(0xAC)>::reg_set();
}
