///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2026.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_gpt.h>
#include <util/utility/util_attribute.h>

#include <cstdint>

#define TM0CTL0  (*(volatile uint8_t*)0xFFFFF690ul)
#define TM0CMP0  (*(volatile uint16_t*)0xFFFFF694ul)
#define TM0EQIC0 (*(volatile uint8_t*)0xFFFFF150ul)

namespace
{
  // The one (and only one) system tick.
  volatile auto mcal_gpt_system_tick = mcal::gpt::value_type { };

  auto gpt_is_initialized() -> bool& ATTRIBUTE(used, noinline);

  auto gpt_is_initialized() -> bool&
  {
    static auto is_init = bool { };

    return is_init;
  }
}

auto mcal::gpt::init(const config_type*) -> void
{
  /* configure the TMM0 timer */
  TM0CTL0 = 0;
  TM0CMP0 = 5120 - 1; // (256/1000)ms interrupt
  TM0EQIC0 = 7;
  TM0CTL0 = 0x80;

  // Set the is-initialized indication flag.
  gpt_is_initialized() = true;
}

auto mcal::gpt::secure::get_time_elapsed() -> value_type
{
  if(gpt_is_initialized())
  {
    // Return the system tick using a multiple read to ensure data consistency.

    // Make an initial reading of the system tick.
    const auto sys_tick = mcal_gpt_system_tick;

    // Do the first read of the low 16-bits of the mcal_gpt_system_tick variable.
    const auto sys_tick_lo16_1 = static_cast<std::uint16_t>(mcal_gpt_system_tick);

    // Do the second read of the low 16-bits of the mcal_gpt_system_tick variable.
    const auto sys_tick_lo16_2 = static_cast<std::uint16_t>(mcal_gpt_system_tick);

    // Perform the consistency check.
    const auto t0_tick_is_consistent = (sys_tick_lo16_2 >= sys_tick_lo16_1);

    return (t0_tick_is_consistent ? sys_tick : mcal_gpt_system_tick);
  }
  else
  {
    return value_type { };
  }
}

extern "C"
__attribute__((interrupt)) void timer_isr(void);

extern "C"
__attribute__((interrupt)) void timer_isr(void)
{
  mcal_gpt_system_tick = static_cast<mcal::gpt::value_type>(mcal_gpt_system_tick + 0x100U);
}
