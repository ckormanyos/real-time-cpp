///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_cpu.h>
#include <mcal_led.h>
#include <mcal_osc.h>
#include <mcal_port.h>
#include <mcal_wdg.h>

#include <util/utility/util_time.h>

#include <cstdint>

namespace local
{
  static auto main_core_worker(mcal::led::led_base& my_led) -> void;
}

extern "C" auto main_core1(void) -> void;
extern "C" auto main_core2(void) -> void;
extern "C" auto main_core3(void) -> void;
extern "C" auto main_core0_init(void) -> void;

extern "C" auto main_core1(void) -> void { local::main_core_worker(mcal::led::led1()); }
extern "C" auto main_core2(void) -> void { local::main_core_worker(mcal::led::led2()); }
extern "C" auto main_core3(void) -> void { local::main_core_worker(mcal::led::led3()); }

extern "C" auto main_core0_init(void) -> void
{
  mcal::wdg::init (nullptr);
  mcal::port::init(nullptr);
  mcal::osc::init (nullptr);
}

static auto local::main_core_worker(mcal::led::led_base& my_led) -> void
{
  using local_timer_type = util::timer<std::uint64_t>;
  using local_tick_type = typename local_timer_type::tick_type;

  my_led.toggle();

  for(;;)
  {
    local_timer_type::blocking_delay(local_timer_type::seconds(local_tick_type { UINT8_C(1) }));

    my_led.toggle();
  }
}
