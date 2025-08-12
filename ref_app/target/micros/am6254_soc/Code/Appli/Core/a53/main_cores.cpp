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
  template<typename UnsignedTickType, const unsigned CoreId>
  struct timer_core_x_backend
  {
    static_assert(CoreId == 0U, "Error: This template is intended for CoreId 0 only");

    using tick_type = UnsignedTickType;

    static constexpr auto get_now() -> tick_type { return util::default_timer_backend<tick_type>::get_now(); }
  };

  template<typename UnsignedTickType>
  struct timer_core_x_backend<UnsignedTickType, 1U>
  {
    using tick_type = UnsignedTickType;

    static constexpr auto get_now() -> tick_type { return static_cast<tick_type>(mcal::gpt::secure::get_time_elapsed_core1()); }
  };

  template<typename UnsignedTickType>
  struct timer_core_x_backend<UnsignedTickType, 2U>
  {
    using tick_type = UnsignedTickType;

    static constexpr auto get_now() -> tick_type { return static_cast<tick_type>(mcal::gpt::secure::get_time_elapsed_core2()); }
  };

  template<typename UnsignedTickType>
  struct timer_core_x_backend<UnsignedTickType, 3U>
  {
    using tick_type = UnsignedTickType;

    static constexpr auto get_now() -> tick_type { return static_cast<tick_type>(mcal::gpt::secure::get_time_elapsed_core3()); }
  };

  template<const unsigned CoreId>
  auto main_worker_core_x(mcal::led::led_base& my_led) -> void;

  template<const unsigned CoreId>
  auto main_worker_core_x(mcal::led::led_base& my_led) -> void
  {
    my_led.toggle();

    using local_timer_backend_type = timer_core_x_backend<std::uint64_t, CoreId>;
    using local_tick_type = typename local_timer_backend_type::tick_type;
    using local_timer_type = util::timer<local_tick_type, local_timer_backend_type>;

    constexpr local_tick_type led_time_1sec { local_timer_type::seconds(local_tick_type { UINT8_C(1) }) };

    local_timer_type led_timer { led_time_1sec };

    for(;;)
    {
      while(!led_timer.timeout())
      {
        mcal::cpu::nop();
      }

      my_led.toggle();

      led_timer.start_interval(led_time_1sec);
    }
  }
}

extern "C" auto main_core1(void) -> void;
extern "C" auto main_core2(void) -> void;
extern "C" auto main_core3(void) -> void;
extern "C" auto main_core0_init(void) -> void;

extern "C" auto main_core1(void) -> void { local::main_worker_core_x<1U>(mcal::led::led1()); }
extern "C" auto main_core2(void) -> void { local::main_worker_core_x<2U>(mcal::led::led2()); }
extern "C" auto main_core3(void) -> void { local::main_worker_core_x<3U>(mcal::led::led3()); }

extern "C" auto main_core0_init(void) -> void
{
  mcal::wdg::init (nullptr);
  mcal::port::init(nullptr);
  mcal::osc::init (nullptr);
}
