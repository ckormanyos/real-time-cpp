///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2026.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_gpt.h>
#include <mcal_led.h>
#include <mcal_osc.h>
#include <mcal_port.h>
#include <mcal_wdg.h>

#include <util/utility/util_time.h>

extern "C"
{
  extern auto osGetActiveCore(void) -> std::uint32_t;

  auto main_core0() -> void;
  auto main_core1() -> void;
  auto main_caller() -> void;
}

auto main(void) -> int __attribute__((used,noinline));

namespace local
{
  struct timer_core1_backend
  {
    using tick_type = std::uint64_t;

    static auto get_now() -> tick_type { return static_cast<tick_type>(mcal::gpt::secure::get_time_elapsed_core1()); }
  };

  using timer_type = util::timer<std::uint64_t>;

  constexpr typename timer_type::tick_type
    led_timeout
    {
      static_cast<typename timer_type::tick_type>(timer_type::seconds(UINT8_C(1)))
    };

  using timer_core1_type = util::timer<std::uint64_t, timer_core1_backend>;
} // namespace local

extern "C"
auto main_core0() -> void
{
  mcal::wdg::init(nullptr);
  mcal::osc::init(nullptr);

  mcal::port::init(nullptr);

  ::main_caller();
}

extern "C"
auto main_core1() -> void
{
  mcal::wdg::init(nullptr);
  mcal::osc::init(nullptr);

  mcal::gpt::init(nullptr);

  local::timer_core1_type local_led_timer(local::led_timeout);

  auto& my_led1_ref { mcal::led::led1() };

  my_led1_ref.toggle();

  // Endless LED1 togglee-loop: Never return or break.
  for(;;)
  {
    if(local_led_timer.timeout())
    {
      my_led1_ref.toggle();

      local_led_timer.start_interval(local::led_timeout);
    }
  }
}
