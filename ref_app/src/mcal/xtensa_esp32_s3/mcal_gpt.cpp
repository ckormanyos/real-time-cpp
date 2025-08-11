///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_gpt.h>
#include <mcal_led.h>
#include <mcal_reg.h>

#include <cstddef>

extern "C"
{
  extern auto get_core_id() -> uint32_t;
  extern auto get_cpu_private_timer1() -> uint32_t;
  extern auto set_cpu_private_timer1(uint32_t) -> void;
  extern auto __system_tick_handler() -> void;
}

namespace
{
  volatile mcal::gpt::value_type system_tick[std::size_t { UINT8_C(2) }];

  template<const std::size_t CoreIndex>
  auto get_consistent_tick() -> mcal::gpt::value_type;

  template<const std::size_t CoreIndex>
  auto get_consistent_tick() -> mcal::gpt::value_type
  {
    using value_type = mcal::gpt::value_type;

    constexpr std::size_t core_index = CoreIndex;

    // Do the first read of the timer1 counter and the system tick.
    const volatile std::uint32_t t1_cnt_1   = get_cpu_private_timer1();
    const volatile std::uint64_t sys_tick_1 = system_tick[core_index];

    // Do the second read of the timer1 counter.
    const volatile std::uint32_t t1_cnt_2 = get_cpu_private_timer1();

    // Perform the consistency check.
    return
      static_cast<value_type>
      (
        (t1_cnt_2 >= t1_cnt_1) ? static_cast<value_type>(sys_tick_1  + t1_cnt_1)
                               : static_cast<value_type>(system_tick[core_index] + t1_cnt_2)
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
  // Reload the private timer1 for the running core,
  // which could be either core0 or core1.
  set_cpu_private_timer1(mcal::gpt::detail::timer1_reload());

  const std::size_t core_id { static_cast<std::size_t>(get_core_id()) };

  // Increment the 64-bit system tick (on the appropriate core).
  // Here, we service the system tick for either core0 or core1,
  // depending on the running core.

  system_tick[core_id] += mcal::gpt::detail::timer1_max();
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
  // At the moment, mhz_value is equal to 80.
  constexpr std::uint32_t mhz_value { (mcal::gpt::detail::timer1_max() / UINT32_C(1000000)) };

  return
    (gpt_is_initialized()
      ? static_cast<mcal::gpt::value_type>
        (
          static_cast<std::uint64_t>(get_consistent_tick<std::size_t { UINT8_C(0) }>() + mhz_value) / mhz_value
        )
      : mcal::gpt::value_type { });
}

auto mcal::gpt::secure::get_time_elapsed_core1() -> mcal::gpt::value_type_core1
{
  // At the moment, mhz_value is equal to 80.
  constexpr std::uint32_t mhz_value { (mcal::gpt::detail::timer1_max() / UINT32_C(1000000)) };

  return
    (gpt_is_initialized()
      ? static_cast<mcal::gpt::value_type>
        (
          static_cast<std::uint64_t>(get_consistent_tick<std::size_t { UINT8_C(1) }>() + mhz_value) / mhz_value
        )
      : mcal::gpt::value_type { });
}
