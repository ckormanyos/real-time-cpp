
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
  void init_ram  ();
  void init_ctors();
}

extern "C" int  main                   ();
extern "C" void __initial_stack_pointer();
extern "C" void __my_startup           () __attribute__((section(".startup"), used, noinline));

void __my_startup()
{
  // Setup the stack pointers and the stacks.
  // For additional information on stack setup,
  // see parts of Sitara Ware's "init.s".

  asm volatile("mov r3, #0");

  // Setup the undefined mode Stack.
  asm volatile("ldr r3, =__initial_stack_pointer");
  asm volatile("msr cpsr_c, #0x1B | 0xC0");
  asm volatile("mov sp, r3");
  asm volatile("sub r3, r3, #0x0010");

  // Setup the abort mode stack.
  asm volatile("msr cpsr_c, #0x17 | 0xC0");
  asm volatile("mov sp, r3");
  asm volatile("sub r3, r3, #0x0010");

  // Setup the fiq stack.
  asm volatile("msr cpsr_c, #0x11 | 0xC0");
  asm volatile("mov sp, r3");
  asm volatile("sub r3, r3, #0x0010");

  // Setup the irq stack (with 1kB stack size).
  asm volatile("msr cpsr_c, #0x12 | 0xC0");
  asm volatile("mov sp, r3");
  asm volatile("sub r3, r3, #0x0400");

  // Setup the svc stack.
  asm volatile("msr cpsr_c, #0x13 | 0xC0");
  asm volatile("mov sp, r3");
  asm volatile("sub r3, r3, #0x0010");

  // Setup the user/system stack.
  asm volatile("msr cpsr_c, #0x1F | 0xC0");
  asm volatile("mov sp, r3");

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
  asm volatile("ldr r3, =main");
  asm volatile("blx r3");

  // Catch an unexpected return from main.
  for(;;)
  {
    // Replace with a loud error if desired.
    mcal::wdg::secure::trigger();
  }
}
