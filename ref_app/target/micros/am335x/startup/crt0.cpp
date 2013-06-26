
///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// AM335x ARM(R) A8 startup code
// Switched to C++ and re-written for BeagleBone by Chris.

#include <mcal/mcal.h>

namespace crt
{
  void init_ram()                      __attribute__((section(".startup")));
  void init_ctors()                    __attribute__((section(".startup")));
  void init_system_interrupt_vectors() __attribute__((section(".startup")));
}

asm volatile(".extern __initial_stack_pointer");
asm volatile(".extern main");

asm volatile(".set UND_STACK_SIZE, 0x8");
asm volatile(".set ABT_STACK_SIZE, 0x8");
asm volatile(".set FIQ_STACK_SIZE, 0x8");
asm volatile(".set IRQ_STACK_SIZE, 0x800");
asm volatile(".set SVC_STACK_SIZE, 0x8");

asm volatile(".set MODE_USR, 0x10");
asm volatile(".set MODE_FIQ, 0x11");
asm volatile(".set MODE_IRQ, 0x12");
asm volatile(".set MODE_SVC, 0x13");
asm volatile(".set MODE_ABT, 0x17");
asm volatile(".set MODE_UND, 0x1B");
asm volatile(".set MODE_SYS, 0x1F");

asm volatile(".equ I_F_BIT, 0xC0");

extern "C" void __my_startup() __attribute__((section(".entry_code"), naked));

void __my_startup()
{
  // Setup the Stack for Undefined mode
  asm volatile("ldr r0, =__initial_stack_pointer");    // Read the stack address.
  asm volatile("msr cpsr_c, #MODE_UND | I_F_BIT");     // Switch to undefined mode.
  asm volatile("mov sp,r0");                           // Set the stack pointer.
  asm volatile("sub r0, r0, #UND_STACK_SIZE");         // Provide stack space.

  // Setup the Stack for abort mode
  asm volatile("msr cpsr_c, #MODE_ABT | I_F_BIT");     // Switch to abort mode.
  asm volatile("mov sp, r0");                          // Set the stack pointer.
  asm volatile("sub r0,r0, #ABT_STACK_SIZE");          // Provide stack space.

  // Setup the Stack for FIQ mode
  asm volatile("msr cpsr_c, #MODE_FIQ | I_F_BIT");      // Switch to FIQ mode.
  asm volatile("mov sp, r0");                           // Set the stack pointer.
  asm volatile("sub r0, r0, #FIQ_STACK_SIZE");          // Provide stack space.

  // Setup the Stack for IRQ mode
  asm volatile("msr cpsr_c, #MODE_IRQ | I_F_BIT");      // Switch to IRQ mode.
  asm volatile("mov sp, r0");                           // Set the stack pointer.
  asm volatile("sub r0, r0, #IRQ_STACK_SIZE");          // Provide stack space.

  // Setup the Stack for SVC mode
  asm volatile("msr cpsr_c, #MODE_SVC | I_F_BIT");      // Switch to SVC mode.
  asm volatile("mov sp, r0");                           // Set the stack pointer.
  asm volatile("sub r0, r0, #SVC_STACK_SIZE");          // Provide stack space.

  // Setup the Stack for User/System mode
  asm volatile("msr cpsr_c, #MODE_SYS | I_F_BIT");      // Switch to system mode.
  asm volatile("mov sp, r0");                           // Set the stack pointer.

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
  asm volatile("ldr r10, =main");
  asm volatile("mov lr, pc");
  asm volatile("bx r10");

  // TBD: Consider this alternative call to main().
//  asm volatile("ldr r3, =main");
//  asm volatile("blx r3");

  // Catch an unexpected return from main.
  for(;;)
  {
    // Replace with a loud error if desired.
    mcal::wdg::trigger();
  }
}
