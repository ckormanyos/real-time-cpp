///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// STM32 EABI Cortex-M3 startup code
// Switched to C++ and modified for STM32F103x by Chris.

#include <mcal/mcal.h>

namespace crt
{
  void init_ram();
  void init_ctors();
}

extern "C" void __my_startup() __attribute__((naked, used, noinline));

void __my_startup()
{
  // Load the stack pointer.
  asm volatile("movs r1, #0");

  // Chip init: Port, oscillator and watchdog.
  mcal::cpu::init();

  // Initialize statics from ROM to RAM.
  // Zero-clear non-initialized static RAM.
  crt::init_ram();
  mcal::wdg::trigger();

  // Call all ctor initializations.
  crt::init_ctors();
  mcal::wdg::trigger();

  // Call main (and never return).
  asm volatile("ldr r3, =main");
  asm volatile("blx r3");

  // Catch an unexpected return from main.
  for(;;)
  {
    // Replace with a loud error if desired.
    mcal::wdg::trigger();
  }
}
