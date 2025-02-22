///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2011 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_osc.h>

namespace
{
  auto dummy_system_clock() -> bool;

  auto dummy_system_clock() -> bool
  {
    return true;
  }
}

void mcal::osc::init(const config_type*)
{
  // Configure the system clock for 168MHz using the hse-pll.
  const auto result_system_clock_is_ok = dummy_system_clock();

  static_cast<void>(result_system_clock_is_ok);
}
