///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// Raspberry Pi bare-metal startup code.
// Expressed with C++ for Raspberry Pi bare-metal by Chris.

#include <mcal_cpu.h>
#include <mcal_irq.h>
#include <mcal_wdg.h>

namespace crt
{
  void init_ram  () __attribute__((section(".startup"), used, noinline));
  void init_ctors() __attribute__((section(".startup"), used, noinline));
}

extern "C" void __my_startup()
{
  // The ARM1176JZF-S is started in supervisor mode
  // with all interrupts disabled.

  // Setup the stack pointer for the supervisor mode.

  asm volatile("ldr r3, =_svc_stack_top");
  asm volatile("mov sp, r3");

  // Relocate the interrupt vector table.
  asm volatile("ldr r3, =_intvect_base_address");
  asm volatile("mcr p15, 0, r3, c12, c0, 0");

  // Switch to Abort mode and setup the relevant stack pointer.
  asm volatile("cps #0x17");
  asm volatile("ldr r3, =_abt_stack_top");
  asm volatile("mov sp, r3");

  // Switch to Undefined mode and setup the relevant stack pointer.
  asm volatile("cps #0x1b");
  asm volatile("ldr r3, =_und_stack_top");
  asm volatile("mov sp, r3");

  // Switch to IRQ mode and setup the relevant stack pointer.
  asm volatile("cps #0x12");
  asm volatile("ldr r3, =_irq_stack_top");
  asm volatile("mov sp, r3");

  // Switch to FIQ mode and setup the relevant stack pointer.
  asm volatile("cps #0x11");
  asm volatile("ldr r3, =_fiq_stack_top");
  asm volatile("mov sp, r3");

  // Switch to System mode and setup the relevant stack pointer.
  asm volatile("cps #0x1f");
  asm volatile("ldr r3, =_sys_stack_top");
  asm volatile("mov sp, r3");

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
