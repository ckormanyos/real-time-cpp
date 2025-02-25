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

#include <mcal_led.h>

#include <cstdint>

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
  constexpr std::uint32_t tim1_reload { static_cast<std::uint32_t>(80000000ULL - 1ULL) };
} // namespace local

extern "C"
int main(void)
{
  // GPIO->OUT.reg |= CORE0_LED;
  mcal::led::led0().toggle();

  // Use core 0 to start core 1.
  Mcu_StartCore1();

  // Set the private cpu timer1 for core 0.
  set_cpu_private_timer1(local::tim1_reload);

  // Enable all interrupts on core 0.
  enable_irq(static_cast<std::uint32_t>(-1L));

  for(;;);
}

extern "C"
void main_c1()
{
  // GPIO->OUT.reg |= CORE1_LED;
  mcal::led::led1().toggle();

  // Set the private cpu timer1 for core 1.
  set_cpu_private_timer1(local::tim1_reload);

  // Enable all interrupts on core 1.
  enable_irq(static_cast<std::uint32_t>(-1L));

  for(;;);
}

extern "C"
void blink_led()
{
  // Reload the private timer1 for the running core.
  set_cpu_private_timer1(local::tim1_reload);

  // Toggle the leds.
  if(get_core_id() != std::uint32_t { UINT8_C(0) })
  {
    // GPIO->OUT.reg ^= CORE1_LED;
    mcal::led::led1().toggle();
  }
  else
  {
    // GPIO->OUT.reg ^= CORE0_LED;
    mcal::led::led0().toggle();
  }
}
