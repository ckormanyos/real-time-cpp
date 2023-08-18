///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2023.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_gpt.h>
#include <mcal_reg.h>

namespace
{
  // The one (and only one) system tick.
  volatile auto mcal_gpt_system_tick = mcal::gpt::value_type { };

  auto gpt_is_initialized() -> bool& __attribute__((used, noinline));

  auto gpt_is_initialized() -> bool&
  {
    static auto is_init = bool { };

    return is_init;
  }
}

extern "C"
auto __vector_16(void) -> void __attribute__((signal, used, externally_visible));

auto __vector_16(void) -> void
{
  // Increment the 32-bit system tick with 0x100, representing 256 [(1/2) microseconds].
  const auto new_tick =
    static_cast<mcal::gpt::value_type>
    (
      mcal_gpt_system_tick + static_cast<std::uint16_t>(UINT16_C(0x100))
    );

  mcal_gpt_system_tick = new_tick;
}

auto mcal::gpt::init(const config_type*) -> void
{
  if(!gpt_is_initialized())
  {
    // Clear the timer0 overflow flag.
    mcal::reg::reg_access_static<std::uint8_t, std::uint8_t, mcal::reg::tifr0, 0x01U>::reg_set();

    // Enable the timer0 overflow interrupt.
    mcal::reg::reg_access_static<std::uint8_t, std::uint8_t, mcal::reg::timsk0, 0x01U>::reg_set();

    // Set the timer0 clock source to f_osc/8 = 2MHz and begin counting.
    mcal::reg::reg_access_static<std::uint8_t, std::uint8_t, mcal::reg::tccr0b, 0x02U>::reg_set();

    // Set the is-initialized indication flag.
    gpt_is_initialized() = true;
  }
}

auto mcal::gpt::secure::get_time_elapsed() -> mcal::gpt::value_type
{
  if(gpt_is_initialized())
  {
    // Return the system tick using a multiple read to ensure data consistency.

    using timer_address_type  = std::uint8_t;
    using timer_register_type = std::uint8_t;

    // Do the first read of the timer0 counter and the system tick.
    const auto t0_cnt_1   = mcal::reg::reg_access_static<timer_address_type, timer_register_type, mcal::reg::tcnt0>::reg_get();
    const auto sys_tick_1 = mcal_gpt_system_tick;

    // Do the second read of the timer0 counter.
    const auto t0_cnt_2 = mcal::reg::reg_access_static<timer_address_type, timer_register_type, mcal::reg::tcnt0>::reg_get();

    const auto t0_tick_is_consistent = (t0_cnt_2 >= t0_cnt_1);

    // Perform the consistency check.
    const auto consistent_half_microsecond_tick =
      static_cast<value_type>
      (
        t0_tick_is_consistent ? static_cast<value_type>(sys_tick_1           | static_cast<std::uint8_t>(t0_cnt_1))
                              : static_cast<value_type>(mcal_gpt_system_tick | static_cast<std::uint8_t>(t0_cnt_2))
      );

    const auto consistent_microsecond_tick =
      static_cast<value_type>
      (
        static_cast<value_type>
        (
          consistent_half_microsecond_tick + static_cast<std::uint8_t>(UINT8_C(1))
        )
        / static_cast<std::uint8_t>(UINT8_C(2))
      );

    return consistent_microsecond_tick;
  }
  else
  {
    return static_cast<value_type>(UINT8_C(0));
  }
}
