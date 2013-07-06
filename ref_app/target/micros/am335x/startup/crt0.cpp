
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
  void init_ram();
  void init_ctors();
  void init_system_interrupt_vectors();
}

asm volatile(".extern __initial_stack_pointer");
asm volatile(".extern main");

asm volatile(".set undefined_stack_size, 0x0010");
asm volatile(".set abort_stack_size,     0x0010");
asm volatile(".set fiq_stack_size,       0x0010");
asm volatile(".set irq_stack_size,       0x0400");
asm volatile(".set svc_stack_size,       0x0010");

asm volatile(".set usr_mode,         0x10");
asm volatile(".set fiq_mode,         0x11");
asm volatile(".set irq_mode,         0x12");
asm volatile(".set svc_mode,         0x13");
asm volatile(".set abort_mode,       0x17");
asm volatile(".set undefined_mode,   0x1B");
asm volatile(".set user_system_mode, 0x1F");

asm volatile(".equ if_mask, 0xC0");

extern "C" void __my_startup() __attribute__((section(".startup"), naked, used, noinline));

void __my_startup()
{
  // Setup the Stack for undefined mode.
  asm volatile("ldr r0, =__initial_stack_pointer");
  asm volatile("msr cpsr_c, #undefined_mode | if_mask");
  asm volatile("mov sp,r0");
  asm volatile("sub r0, r0, #undefined_stack_size");

  // Setup the stack for abort mode.
  asm volatile("msr cpsr_c, #abort_mode | if_mask");
  asm volatile("mov sp, r0");
  asm volatile("sub r0,r0, #abort_stack_size");

  // Setup the stack for fiq mode.
  asm volatile("msr cpsr_c, #fiq_mode | if_mask");
  asm volatile("mov sp, r0");
  asm volatile("sub r0, r0, #fiq_stack_size");

  // Setup the stack for irq mode.
  asm volatile("msr cpsr_c, #irq_mode | if_mask");
  asm volatile("mov sp, r0");
  asm volatile("sub r0, r0, #irq_stack_size");

  // Setup the stack for svc mode.
  asm volatile("msr cpsr_c, #svc_mode | if_mask");
  asm volatile("mov sp, r0");
  asm volatile("sub r0, r0, #svc_stack_size");

  // Setup the stack for user/system mode.
  asm volatile("msr cpsr_c, #user_system_mode | if_mask");
  asm volatile("mov sp, r0");

  // Copy the system interrupt vector table from ROM to RAM.
  crt::init_system_interrupt_vectors();

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
