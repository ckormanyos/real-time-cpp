///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_led.h>
#include <mcal_led/mcal_led_port.h>

#include <util/utility/util_time.h>

#include <cstdint>

static auto main_core_worker(mcal::led::led_base& my_led) -> void;

extern "C" auto main_core1(void) -> void;
extern "C" auto main_core2(void) -> void;
extern "C" auto main_core3(void) -> void;

extern "C" auto main_core1(void) -> void { main_core_worker(mcal::led::led1()); }
extern "C" auto main_core2(void) -> void { main_core_worker(mcal::led::led2()); }
extern "C" auto main_core3(void) -> void { main_core_worker(mcal::led::led3()); }

static auto main_core_worker(mcal::led::led_base& my_led) -> void
{
  using local_timer_type = util::timer<std::uint64_t>;
  using local_tick_type = typename local_timer_type::tick_type;

  local_timer_type led_timer(local_timer_type::seconds(local_tick_type { UINT8_C(1) }));

  my_led.toggle();

  for(;;)
  {
    while(!led_timer.timeout()) { asm volatile("nop"); }

    my_led.toggle();

    led_timer.start_interval(local_timer_type::seconds(local_tick_type { UINT8_C(1) }));
  }
}
