
///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal/mcal.h>

namespace crt
{
  void init_ram  ();
  void init_ctors();
}

extern "C" int  main                   ();
//extern "C" void __initial_stack_pointer();
extern "C" void __my_startup           () __attribute__((used, noinline));




void __my_startup()
{
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
  asm volatile("b main");

  // Catch an unexpected return from main.
  for(;;)
  {
    // Replace with a loud error if desired.
    mcal::wdg::secure::trigger();
  }
}
