///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2022.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_wdg_watchdog.h>

auto mcal::wdg::init(const config_type*) -> void // NOLINT(readability-named-parameter,hicpp-named-parameter)
{
  // Subroutine is empty on purpose.
}

auto mcal::wdg::secure::trigger() -> void
{
  using local_watchdog_timer_type = watchdog_base::base_timer_type;

  constexpr auto time_two_seconds = static_cast<typename local_watchdog_timer_type::tick_type>(UINT8_C(2));

  using local_watchdog_type = watchdog<local_watchdog_timer_type::seconds(time_two_seconds)>;

  local_watchdog_type::my_watchdog.reset_watchdog_timer();
}
