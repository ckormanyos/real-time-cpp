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

extern "C" void main_core0(void);
extern "C" void main_core1(void);
extern "C" void main_core2(void);
extern "C" void main_core3(void);

template<const int LED_ID>
void main_core_worker(void)
{
  using timer_type = util::timer<std::uint64_t>;

  using led_type = my_led<LED_ID>;

  led_type led;

  timer_type led_timer(timer_type::seconds(1U));

  led.toggle();

  for(;;)
  {
    while(!led_timer.timeout()) { asm volatile("nop"); }

    led.toggle();

    led_timer.start_interval(timer_type::seconds(1U));
  }
}

extern "C" void main_core0(void) { main_core_worker<LED_1>(); }
extern "C" void main_core1(void) { main_core_worker<LED_2>(); }
extern "C" void main_core2(void) { main_core_worker<LED_3>(); }
extern "C" void main_core3(void) { main_core_worker<LED_4>(); }
