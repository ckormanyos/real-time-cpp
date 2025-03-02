///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_gpt.h>
#include <mcal_led.h>
#include <mcal_reg.h>

extern "C"
{
  extern auto get_core_id() -> uint32_t;
  extern auto get_cpu_private_timer1() -> uint32_t;
  extern auto set_cpu_private_timer1(uint32_t) -> void;
  extern auto __system_tick_handler() -> void;
}

namespace
{
  volatile mcal::gpt::value_type system_tick;

  auto get_consistent_tick() -> mcal::gpt::value_type
  {
    using value_type = mcal::gpt::value_type;

    // Do the first read of the timer1 counter and the system tick.
    const volatile std::uint32_t t1_cnt_1   = get_cpu_private_timer1();
    const volatile std::uint64_t sys_tick_1 = system_tick;

    // Do the second read of the timer1 counter.
    const volatile std::uint32_t t1_cnt_2 = get_cpu_private_timer1();

    // Perform the consistency check.
    return
      static_cast<value_type>
      (
        (t1_cnt_2 >= t1_cnt_1) ? static_cast<value_type>(sys_tick_1  + t1_cnt_1)
                               : static_cast<value_type>(system_tick + t1_cnt_2)
      );
  }

  auto gpt_is_initialized() -> bool& __attribute__((used, noinline));

  auto gpt_is_initialized() -> bool&
  {
    static auto is_init = bool { };

    return is_init;
  }
}

extern "C" void __system_tick_handler()
{
  // Reload the private timer1 for the running core.
  set_cpu_private_timer1(mcal::gpt::timer1_reload());

  const bool is_not_core0 { (get_core_id() != std::uint32_t { UINT8_C(0) }) };

  // Toggle the LED (on core1) or increment the 64-bit system tick (on core0).

  if(is_not_core0) { mcal::led::led1().toggle(); }
  else             { system_tick += mcal::gpt::timer1_max(); }
}

auto mcal::gpt::init(const config_type*) -> void
{
  if(!gpt_is_initialized())
  {
    // Set the is-initialized indication flag.
    gpt_is_initialized() = true;
  }
}

auto mcal::gpt::secure::get_time_elapsed() -> mcal::gpt::value_type
{
  mcal::gpt::value_type result { };

  if(gpt_is_initialized())
  {
    constexpr std::uint32_t mhz_value { (mcal::gpt::timer1_max() / UINT32_C(1000000)) };

    result = get_consistent_tick() / mhz_value;
  }

  return result;
}
