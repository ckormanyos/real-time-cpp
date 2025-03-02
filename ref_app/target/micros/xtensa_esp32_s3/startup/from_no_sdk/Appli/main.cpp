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
#include <os/os.h>

#include <cstdint>
#include <limits>

extern "C"
{
  int  main();
  void main_c1();

  extern void     Mcu_StartCore1();
  extern uint32_t get_core_id();
  extern void     enable_irq(uint32_t mask);
  extern void     set_cpu_private_timer1(uint32_t ticks);
}

extern "C"
int main()
{
  // Set the private cpu timer1 for core 0.
  set_cpu_private_timer1(mcal::gpt::timer1_reload());

  // Enable all interrupts on core 0.
  enable_irq((std::numeric_limits<std::uint32_t>::max)());

  // Use core 0 to start core 1.
  Mcu_StartCore1();

  mcal::gpt::init(nullptr);

  os::start_os();
}

extern "C"
void main_c1()
{
  // Set the private cpu timer1 for core 1.
  set_cpu_private_timer1(mcal::gpt::timer1_reload());

  // Enable all interrupts on core 1.
  enable_irq((std::numeric_limits<std::uint32_t>::max)());

  // GPIO->OUT.reg |= CORE1_LED;
  mcal::led::led1().toggle();

  for(;;) { asm volatile("nop"); }
}

