///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2018.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_wdg_watchdog.h>

void mcal::wdg::init(const config_type*)
{
}

void mcal::wdg::secure::trigger()
{
  mcal::wdg::watchdog::the_watchdog.reset_watchdog_timer();
}
