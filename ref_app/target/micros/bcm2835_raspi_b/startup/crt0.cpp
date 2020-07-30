///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2014 - 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// Raspberry Pi bare-metal startup code.
// Expressed with C++ for Raspberry Pi bare-metal by Chris.

#include <cstdint>

#include <mcal_cpu.h>
#include <mcal_irq.h>
#include <mcal_wdg.h>

namespace crt
{
  void init_ram  ();
  void init_ctors();
}

extern "C" void __my_startup()
{
  /* The ARM1176JZF-S is started in supervisor mode with interrupt disabled */
  /* Setup the stack pointer for the supervisor mode */

  asm volatile("ldr r3, =__SVC_STACK_TOP");
  asm volatile("mov sp, r3");

  /* relocate the interrupt vector table */
  asm volatile("ldr r3, =__INTVECT_BASE_ADDRESS");
  asm volatile("mcr p15, 0, r3, c12, c0, 0");

  /* switch to Abort mode and setup the relevant stack pointer */
  asm volatile("cps #0x17");
  asm volatile("ldr r3, =__ABT_STACK_TOP");
  asm volatile("mov sp, r3");

  /* switch to Undefined mode and setup the relevant stack pointer */
  asm volatile("cps #0x1b");
  asm volatile("ldr r3, =__UND_STACK_TOP");
  asm volatile("mov sp, r3");

  /* switch to IRQ mode and setup the relevant stack pointer */
  asm volatile("cps #0x12");
  asm volatile("ldr r3, =__IRQ_STACK_TOP");
  asm volatile("mov sp, r3");

  /* switch to FIQ mode and setup the relevant stack pointer */
  asm volatile("cps #0x11");
  asm volatile("ldr r3, =__FIQ_STACK_TOP");
  asm volatile("mov sp, r3");

  /* switch to System mode and setup the relevant stack pointer */
  asm volatile("cps #0x1f");
  asm volatile("ldr r3, =__SYS_STACK_TOP");
  asm volatile("mov sp, r3");

  /* Enable the Program flow prediction, I-Cache and D-Cache */
  asm volatile("mrc p15, 0, r1, c1, c0, 0");
  asm volatile("ldr r0, =#0x1804");
  asm volatile("orr r1, r0");
  asm volatile("mcr p15, 0, r1, c1, c0, 0");

  /* Enable the floating point unit vfp11 (ARMv6 coprocessor cp10 and cp11) */
  asm volatile("mrc p15, 0, r1, c1, c1, 2");
  asm volatile("ldr r0, =0x00000C00");
  asm volatile("orr r1, r0");
  asm volatile("mcr p15, 0, r1, c1, c1, 2");

  asm volatile("mrc p15, 0, r1, c1, c0, 2");
  asm volatile("ldr r0, =0x00F00000");
  asm volatile("orr r1, r0");
  asm volatile("mcr p15, 0, r1, c1, c0, 2");

  asm volatile("mov r0, #0");
  asm volatile("mcr p15, 0, r0, c7, c10, 5");

  asm volatile("ldr r0, =#0x40000000");
  asm volatile("vmsr fpexc,r0");

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
  asm volatile("b main");

  // Catch an unexpected return from main.
  for(;;)
  {
    // Replace with a loud error if desired.
    mcal::wdg::secure::trigger();
  }
}
