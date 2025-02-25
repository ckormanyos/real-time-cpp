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

#include <mcal_reg.h>

#include <cstdint>

namespace local
{
  constexpr std::uint32_t core0_led    { UINT32_C(7) };
  constexpr std::uint32_t core1_led    { UINT32_C(6) };
  constexpr std::uint32_t apb_freq_mhz { UINT32_C(80000000) };
} // namespace local

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

extern "C"
int main(void)
{
  // GPIO->OUT.reg |= CORE0_LED;
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::gpio::out, local::core0_led>::bit_set();

  /* enable all interrupts on core 0 */
  enable_irq((uint32_t)-1);

  Mcu_StartCore1();

  /* set the private cpu timer1 for core 0 */
  set_cpu_private_timer1(local::apb_freq_mhz);

  for(;;);
}

extern "C"
void main_c1(void)
{
  // GPIO->OUT.reg |= CORE1_LED;
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::gpio::out, local::core1_led>::bit_set();

  // Enable all interrupts on core 1.
  enable_irq((uint32_t)-1);

  // Set the private cpu timer1 for core 1.
  set_cpu_private_timer1(local::apb_freq_mhz);

  for(;;);
}

extern "C"
void blink_led(void)
{
  // Reload the private timer1 for the running core.
  set_cpu_private_timer1(local::apb_freq_mhz);

  // Toggle the leds.
  if(get_core_id() != std::uint32_t { UINT8_C(0) })
  {
    // GPIO->OUT.reg ^= CORE1_LED;
    mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::gpio::out, local::core1_led>::bit_not();
  }
  else
  {
    // GPIO->OUT.reg ^= CORE0_LED;
    mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::gpio::out, local::core0_led>::bit_not();
  }
}
