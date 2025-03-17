///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// Generic code.

#include <mcal_cpu.h>
#include <mcal_wdg.h>

namespace crt
{
  void init_ram();
  void init_ctors();
}

extern "C"
{
  asm(".extern main");

  void __my_startup() __attribute__((used, noinline));
}

void __my_startup()
{
  // Load the stack pointer.
  // The stack pointer has already been loaded
  // in the subroutine _start in the file boot.S.
  // So we do nothing here.

  // Chip init: Watchdog, port, and oscillator.
  mcal::cpu::init();

  // Initialize statics from ROM to RAM.
  // Zero-clear default-initialized static RAM.
  crt::init_ram();

  // Call all ctor initializations.
  crt::init_ctors();

  // Jump to main (and never return).
  asm volatile("j main");

  // Catch an unexpected return from main.
  for(;;)
  {
    // Replace with a loud error if desired.
    mcal::wdg::secure::trigger();
  }
}
