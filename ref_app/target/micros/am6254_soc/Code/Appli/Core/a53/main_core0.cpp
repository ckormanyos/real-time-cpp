///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <core_macros.h>
#include <my_led.h>

#include <util/utility/util_time.h>

#include <cstdint>

extern "C"
void main_core0(void);

namespace local
{
  my_led<LED_1> led_1;
  my_led<LED_2> led_2;
  my_led<LED_3> led_3;
  my_led<LED_4> led_4;

  inline auto leds_toggle() -> void { led_1.toggle(); led_2.toggle(); led_3.toggle(); led_4.toggle(); }
}

extern "C"
void main_core0(void)
{
  using timer_type = util::timer<std::uint64_t>;

  timer_type led0_timer(timer_type::seconds(1U));

  local::leds_toggle();

  for(;;)
  {
    while(!led0_timer.timeout())
    {
      __asm volatile("nop");
    }

    local::leds_toggle();

    led0_timer.start_interval(timer_type::seconds(1U));
  }
}
