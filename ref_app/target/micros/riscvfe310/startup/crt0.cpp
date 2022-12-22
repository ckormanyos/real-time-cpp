///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2022.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal/mcal.h>

asm(".extern __initial_stack_pointer");
asm(".extern DirectModeInterruptHandler");
asm(".extern Startup_Init");

namespace crt
{
  void init_ram();
  void init_ctors();
}

extern "C" void __my_startup(void) __attribute__ ((section(".startup"), naked, no_reorder, optimize(0), used, noinline));

void __my_startup()
{
  // Disable all interrupts flag.
  // Disable all specific interrupt sources.
  // Setup the stack pointer.
  // setup the direct interrupt handler.
  asm volatile
  (
    "csrrs x0, mstatus, x0\n\t"
    "csrrs x0, mie, x0\n\t"
    "la sp, __initial_stack_pointer\n\t"
    "la t0, DirectModeInterruptHandler\n\t"
    "csrrs x0, mtvec, t0"
  );

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
