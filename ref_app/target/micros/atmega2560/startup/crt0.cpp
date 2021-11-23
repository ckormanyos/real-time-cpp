///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2021.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// ATMEL(R) AVR(R) startup code.
// Expressed with C++ for atmega2560 by Chris.

#include <mcal/mcal.h>

asm(".extern __initial_stack_pointer");

namespace crt
{
  void init_ram  () __attribute__((section(".startup"), used, noinline));
  void init_ctors() __attribute__((section(".startup"), used, noinline));
}

extern "C" void __my_startup() __attribute__((section(".startup"), used, noinline));

void __my_startup()
{
  // Load the sreg register.
  asm volatile("eor r1, r1");
  asm volatile("out 0x3f, r1");

  // Set the stack pointer.
  asm volatile("ldi r28, lo8(__initial_stack_pointer)");
  asm volatile("ldi r29, hi8(__initial_stack_pointer)");

  // Load the sph register (stack pointer high).
  asm volatile("out 0x3e, r29");

  // Load the spl register (stack pointer low).
  asm volatile("out 0x3d, r28");

  // CPU Initialization, including watchdog,
  // port, oscillators and other clocks.
  mcal::cpu::init();

  // Initialize statics from ROM to RAM.
  // Zero-clear default-initialized static RAM.
  crt::init_ram();
  mcal::wdg::secure::trigger();

  // Call all ctor initializations.
  crt::init_ctors();
  mcal::wdg::secure::trigger();

  // Jump to main (and never return).
  asm volatile("jmp main");

  // Catch an unexpected return from main.
  for(;;)
  {
    // Replace with a loud error if desired.
    mcal::wdg::secure::trigger();
  }
}
