///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// Renesas RX63n startup code
// Switched to C++ and modified for RX6300 by Chris.

#include <mcal/mcal.h>

namespace crt
{
  void init_ram();
  void init_ctors();
}


extern "C" void __my_startup() __attribute__((used, noinline));

extern "C" void _reset() __attribute__((used, noinline));

void _reset()
{
  __my_startup();
}

void __my_startup()
{
  asm volatile("la $sp, __initial_stack_pointer");

//  asm volatile("la $gp, __global_pointer");

  // Chip init: Watchdog, port, and oscillator.
  mcal::cpu::init();

  // Initialize statics from ROM to RAM.
  // Zero-clear non-initialized static RAM.
  crt::init_ram();
  mcal::wdg::secure::trigger();

  // Call all ctor initializations.
  crt::init_ctors();
  mcal::wdg::secure::trigger();

  // Call main (and never return).
  asm volatile("la $t0, main");
  asm volatile("jalr $t0");

  // Catch an unexpected return from main.
  for(;;)
  {
    // Replace with a loud error if desired.
    mcal::wdg::secure::trigger();
  }
}
