///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// Originally from:

/******************************************************************************************
  Filename    : main.c

  Core        : Xtensa LX7

  MCU         : ESP32-S3

  Author      : Chalandi Amine

  Owner       : Chalandi Amine

  Date        : 22.02.2025

  Description : Application main function

******************************************************************************************/

#include <mcal_gpt.h>
#include <mcal_led.h>

#include <util/utility/util_time.h>

#include <cstdint>
#include <limits>

extern "C"
{
  int  main();
  void main_c1();
  void blink_led();

  extern void     Mcu_StartCore1();
  extern uint32_t get_core_id();
  extern void     enable_irq(uint32_t mask);
  extern void     set_cpu_private_timer1(uint32_t ticks);
}

namespace local
{
  static constexpr std::uint32_t timer1_max    { UINT32_C(80000000) };
  static constexpr std::uint32_t timer1_reload { timer1_max - UINT32_C(1) };
} // namespace local

volatile std::uint64_t system_tick;

extern "C"
int main()
{
  // GPIO->OUT.reg |= CORE0_LED;
  mcal::led::led0().toggle();

  // Set the private cpu timer1 for core 0.
  set_cpu_private_timer1(local::timer1_reload);

  // Enable all interrupts on core 0.
  enable_irq((std::numeric_limits<std::uint32_t>::max)());

  mcal::gpt::init(nullptr);

  using timer_type = util::timer<std::uint32_t>;

  timer_type led_timer(timer_type::seconds(1U));

  // Use core 0 to start core 1.
  Mcu_StartCore1();

  for(;;)
  {
    if(led_timer.timeout())
    {
      mcal::led::led0().toggle();

      led_timer.start_interval(timer_type::seconds(1U));
    }
  }
}

extern "C"
void main_c1()
{
  // GPIO->OUT.reg |= CORE1_LED;
  mcal::led::led1().toggle();

  // Set the private cpu timer1 for core 1.
  set_cpu_private_timer1(local::timer1_reload);

  // Enable all interrupts on core 1.
  enable_irq((std::numeric_limits<std::uint32_t>::max)());

  for(;;) { asm volatile("nop"); }
}

extern "C" void blink_led()
{
  // Reload the private timer1 for the running core.
  set_cpu_private_timer1(local::timer1_reload);

  const bool is_not_core0 { (get_core_id() != std::uint32_t { UINT8_C(0) }) };

  // Toggle the LED (on core1) or increment the 64-bit system tick (on core0).

  if(is_not_core0) { mcal::led::led1().toggle(); }
  else             { system_tick += local::timer1_max; }
}
