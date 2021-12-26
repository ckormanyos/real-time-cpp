///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// Renesas v850es/fx2 startup code.
// Expressed with C++ for upd703231 by Chris.

#include <mcal/mcal.h>

namespace crt
{
  void init_ram();
  void init_ctors();
}

extern "C" void __my_startup() __attribute__((used, noinline));

void __my_startup()
{
  // Load the stack pointer.
  asm volatile("movea 255, r0, r20");
  asm volatile("mov   65535, r21");
  asm volatile("mov   hilo(__initial_stack_pointer), sp");

  // Initialize other chip registers and pointers.
  asm volatile("mov   hilo(__ep), ep");
  asm volatile("mov   hilo(__gp), gp");
  asm volatile("mov   hilo(__ctbp), r6");
  asm volatile("ldsr  r6, ctbp");

  // Chip init: Watchdog, port, and oscillator.
  mcal::cpu::init();

  // Initialize statics from ROM to RAM.
  // Zero-clear default-initialized static RAM.
  crt::init_ram();
  asm volatile("nop");

  // Call all ctor initializations.
  crt::init_ctors();
  asm volatile("nop");

  // Jump to main (and never return).
  asm volatile("jarl _main, lp");

  // Catch an unexpected return from main.
  for(;;)
  {
    // Replace with a loud error if desired.
    asm volatile("nop");
  }
}
