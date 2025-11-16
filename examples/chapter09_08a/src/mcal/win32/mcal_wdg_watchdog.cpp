///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2013 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <iostream>

#include <mcal_wdg_watchdog.h>

auto mcal::wdg::print_timeout_message() -> void
{
  std::cout << "error: at least one watchdog timeout has occurred" << std::endl;
}
