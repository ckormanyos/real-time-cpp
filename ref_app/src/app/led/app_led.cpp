///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2022.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal/mcal.h>
#include <util/utility/util_time.h>

namespace app { namespace led {

void task_init();
void task_func();

} // namespace led
} // namespace app

namespace local
{
  using app_led_timer_type = util::timer<std::uint32_t>;

  auto app_led_timer() noexcept -> app_led_timer_type&;
} // namespace local

auto local::app_led_timer() noexcept -> app_led_timer_type&
{
  using local_app_led_tick_type = typename app_led_timer_type::tick_type;

  static app_led_timer_type local_app_led_timer(app_led_timer_type::seconds(static_cast<local_app_led_tick_type>(UINT8_C(1))));

  return local_app_led_timer;
}

auto app::led::task_init() -> void
{
  mcal::led::led0().toggle();
}

auto app::led::task_func() -> void
{
  if(local::app_led_timer().timeout())
  {
    local::app_led_timer().start_interval(local::app_led_timer_type::seconds(1U));

    mcal::led::led0().toggle();
  }
}
