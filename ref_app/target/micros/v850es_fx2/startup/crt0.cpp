///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2021.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// Renesas v850es/fx2 startup code.
// Expressed with C++ for upd703231 by Chris.

#include <mcal_cpu.h>
#include <mcal_wdg.h>

namespace crt
{
  void init_ram();
  void init_ctors();
}

extern "C" void __my_startup(void) __attribute__((used, noinline));
extern "C" void mcal_cpu_init(void);
extern "C" void crt_init_ctors(void);

void __my_startup()
{
  asm volatile("movea 255, r0, r20");
  asm volatile("mov   65535, r21");
  asm volatile("mov   hilo(_stack), sp");
  asm volatile("mov   hilo(__ep), ep");
  asm volatile("mov   hilo(__gp), gp");
  asm volatile("movhi hi(__tp), zero, tp");
  asm volatile("movea lo(__tp), tp, tp");
  asm volatile("mov   hilo(__ctbp), r6");
  asm volatile("ldsr  r6, ctbp");

  // Chip init: Watchdog, port, and oscillator.
  mcal_cpu_init();
  mcal::wdg::secure::trigger();

  // Initialize statics from ROM to RAM.
  // Zero-clear default-initialized static RAM.
  crt::init_ram();
  mcal::wdg::secure::trigger();

  // Call all ctor initializations.
  crt_init_ctors();
  mcal::wdg::secure::trigger();

  // Jump to main (and never return).
  asm volatile("jr _main");

  // Catch an unexpected return from main.
  for(;;)
  {
    // Replace with a loud error if desired.
    mcal::wdg::secure::trigger();
  }
}
