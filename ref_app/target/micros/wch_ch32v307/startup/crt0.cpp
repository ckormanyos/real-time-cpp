///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2022 - 2024.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

asm (".extern __initial_stack_pointer");
asm (".extern InterruptVectorTable");

#include <mcal/mcal.h>

namespace crt
{
  void init_ram();
  void init_ctors();
}

extern "C"
{
  void __my_startup() __attribute__ ((section(".startup")));
}

void __my_startup()
{
  // Setup the stack pointer.
  asm volatile("la sp, __initial_stack_pointer");

  // Setup the interrupt vector table.
  asm volatile("la x1, InterruptVectorTable");
  asm volatile("ori x1, x1, 3");
  asm volatile("csrw mtvec, x1");

  // Chip init: Watchdog, port, and oscillator.
  mcal::cpu::init();

  // Initialize statics from ROM to RAM.
  // Zero-clear default-initialized static RAM.
  crt::init_ram();
  mcal::wdg::secure::trigger();

  // Call all ctor initializations.
  crt::init_ctors();
  mcal::wdg::secure::trigger();

  // Jump to main (and never return).
  asm volatile("jal main");

  // Catch an unexpected return from main.
  for(;;)
  {
    // Replace with a loud error if desired.
    mcal::wdg::secure::trigger();
  }
}
