
///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// AM335x ARM(R) A8 startup code
// Written in C++ for BeagleBone by Chris.

#include <mcal/mcal.h>

namespace crt
{
  void init_ram           ();
  void init_ctors         ();
  void init_interrupts_nmi();
}

extern "C" int  main                   ();
extern "C" void __initial_stack_pointer();
extern "C" void __my_startup           () __attribute__((section(".startup"), naked, used, noinline));

void __my_startup()
{
  // Setup the Stack for undefined mode.
  asm volatile("ldr r0, =__initial_stack_pointer");
  asm volatile("msr cpsr_c, #0x1B | 0xC0");
  asm volatile("mov sp,r0");
  asm volatile("sub r0, r0, #0x0010");

  // Setup the stack for abort mode.
  asm volatile("msr cpsr_c, #0x17 | 0xC0");
  asm volatile("mov sp, r0");
  asm volatile("sub r0,r0, #0x0010");

  // Setup the stack for fiq mode.
  asm volatile("msr cpsr_c, #0x11 | 0xC0");
  asm volatile("mov sp, r0");
  asm volatile("sub r0, r0, #0x0010");

  // Setup the stack for irq mode.
  asm volatile("msr cpsr_c, #0x12 | 0xC0");
  asm volatile("mov sp, r0");
  asm volatile("sub r0, r0, #0x0400");

  // Setup the stack for svc mode.
  asm volatile("msr cpsr_c, #0x13 | 0xC0");
  asm volatile("mov sp, r0");
  asm volatile("sub r0, r0, #0x0010");

  // Setup the stack for user/system mode.
  asm volatile("msr cpsr_c, #0x1F | 0xC0");
  asm volatile("mov sp, r0");

  // Copy the system interrupt vector table from ROM to RAM.
  crt::init_interrupts_nmi();

  // Chip init: Port, oscillator and watchdog.
  mcal::cpu::init();

  // Initialize statics from ROM to RAM.
  // Zero-clear non-initialized static RAM.
  crt::init_ram();
  mcal::wdg::trigger();

  // Call all ctor initializations.
  crt::init_ctors();
  mcal::wdg::trigger();

  // Call main (and never return).
  asm volatile("ldr r3, =main");
  asm volatile("blx r3");

  // Catch an unexpected return from main.
  for(;;)
  {
    // Replace with a loud error if desired.
    mcal::wdg::trigger();
  }
}
