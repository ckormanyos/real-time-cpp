///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <util/utility/util_time.h>

#include <cstdint>

extern "C" auto toggle_led() -> void;

extern "C" auto task_led() -> void;

extern "C" auto task_led() -> void
{
  using local_timer_type = util::timer<std::uint64_t>;
  using local_tick_type = typename local_timer_type::tick_type;

  static local_timer_type local_timer(local_timer_type::seconds(local_tick_type{ UINT8_C(1) }));

  if(local_timer.timeout())
  {
    local_timer.start_interval(local_timer_type::seconds(local_tick_type { UINT8_C(1) }));

    toggle_led();
  }
}
