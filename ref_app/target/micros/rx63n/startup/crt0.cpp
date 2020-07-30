///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// Renesas RX63n startup code.
// Expressed with C++ for RX6300 by Chris.

#include <mcal/mcal.h>

namespace crt
{
  void init_ram();
  void init_ctors();
}

extern "C" void __my_startup() __attribute__((used, noinline));

void __my_startup()
{
  asm volatile("mvtc #0, psw");

  // Enable the DN bit
  asm volatile("mvtc #0x100, fpsw");

  // Load the stack pointer.
  asm volatile("mov #__initial_stack_pointer, r0");

  // Load the address of the interrupt vector table.
  asm volatile("mvtc #__vectors_begin, intb");

  // Initialize the small data area pointer.
  // We will not use the small area data pointer.
  // asm volatile("mov #__gp, r13");

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
  asm volatile("bsr.a _main");

  // Catch an unexpected return from main.
  for(;;)
  {
    // Replace with a loud error if desired.
    mcal::wdg::secure::trigger();
  }
}
