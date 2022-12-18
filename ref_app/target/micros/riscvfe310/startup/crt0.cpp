///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2022.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal/mcal.h>

asm(".extern __STACK_TOP");
asm(".extern DirectModeInterruptHandler");
asm(".extern Startup_Init");

extern "C"
{
  void __my_startup(void) __attribute__ ((section(".boot"), used, noinline));

  void Startup_InitRam(void);

  void Startup_InitCtors(void);
}

void __my_startup()
{
  // Disable all interrupts flag.
  asm volatile("csrrs x0, mstatus, x0");

  // Disable all specific interrupt sources.
  asm volatile("csrrs x0, mie, x0");

  // Setup the stack pointer.
  asm volatile("la sp, __STACK_TOP");

  // setup the direct interrupt handler.
  asm volatile("la t0, DirectModeInterruptHandler");
  asm volatile("csrrs x0, mtvec, t0");

  // Chip init: Watchdog, port, and oscillator.
  mcal::cpu::init();

  // Initialize statics from ROM to RAM.
  // Zero-clear default-initialized static RAM.
  ::Startup_InitRam();
  mcal::wdg::secure::trigger();

  // Call all ctor initializations.
  ::Startup_InitCtors();
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
