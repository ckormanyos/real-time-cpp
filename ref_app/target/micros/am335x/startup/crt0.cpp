
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

asm volatile(".set und_stack_size, 0x0008");
asm volatile(".set abt_stack_size, 0x0008");
asm volatile(".set fiq_stack_size, 0x0008");
asm volatile(".set irq_stack_size, 0x0800");
asm volatile(".set svc_stack_size, 0x0008");

asm volatile(".set mode_usr, 0x10");
asm volatile(".set mode_fiq, 0x11");
asm volatile(".set mode_irq, 0x12");
asm volatile(".set mode_svc, 0x13");
asm volatile(".set mode_abt, 0x17");
asm volatile(".set mode_und, 0x1B");
asm volatile(".set mode_sys, 0x1F");

asm volatile(".equ i_f_bit, 0xC0");

extern "C" void __my_startup() __attribute__((section(".startup"), naked));

void __my_startup()
{
  // Setup the Stack for Undefined mode
  asm volatile("ldr r0, =__initial_stack_pointer");    // Read the stack address.
  asm volatile("msr cpsr_c, #mode_und | i_f_bit");     // Switch to undefined mode.
  asm volatile("mov sp,r0");                           // Set the stack pointer.
  asm volatile("sub r0, r0, #und_stack_size");         // Provide stack space.

  // setup the stack for abort mode
  asm volatile("msr cpsr_c, #mode_abt | i_f_bit");     // Switch to abort mode.
  asm volatile("mov sp, r0");                          // Set the stack pointer.
  asm volatile("sub r0,r0, #abt_stack_size");          // Provide stack space.

  // setup the stack for fiq mode
  asm volatile("msr cpsr_c, #mode_fiq | i_f_bit");     // Switch to fiq mode.
  asm volatile("mov sp, r0");                          // Set the stack pointer.
  asm volatile("sub r0, r0, #fiq_stack_size");         // Provide stack space.

  // setup the stack for irq mode
  asm volatile("msr cpsr_c, #mode_irq | i_f_bit");     // Switch to irq mode.
  asm volatile("mov sp, r0");                          // Set the stack pointer.
  asm volatile("sub r0, r0, #irq_stack_size");         // Provide stack space.

  // setup the stack for svc mode
  asm volatile("msr cpsr_c, #mode_svc | i_f_bit");     // Switch to svc mode.
  asm volatile("mov sp, r0");                          // Set the stack pointer.
  asm volatile("sub r0, r0, #svc_stack_size");         // Provide stack space.

  // setup the stack for user/system mode
  asm volatile("msr cpsr_c, #mode_sys | i_f_bit");     // Switch to system mode.
  asm volatile("mov sp, r0");                          // Set the stack pointer.

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
