
///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// SitaraWare AM335x ARM(R) A8 startup code
// Switched to C++ and re-written for BeagleBone by Chris.

#include <mcal/mcal.h>

namespace crt
{
  void init_ram        () __attribute__((section(".startup")));
  void init_ctors      () __attribute__((section(".startup")));
  void init_isr_vectors() __attribute__((section(".startup")));
}

asm volatile(".global __initial_stack_pointer");
asm volatile(".global _bss_begin");
asm volatile(".global _bss_end");

asm volatile(".set  UND_STACK_SIZE, 0x8");
asm volatile(".set  ABT_STACK_SIZE, 0x8");
asm volatile(".set  FIQ_STACK_SIZE, 0x8");
asm volatile(".set  IRQ_STACK_SIZE, 0x800");
asm volatile(".set  SVC_STACK_SIZE, 0x8");

// to set the mode bits in CPSR for different modes

asm volatile(".set  MODE_USR, 0x10");
asm volatile(".set  MODE_FIQ, 0x11");
asm volatile(".set  MODE_IRQ, 0x12");
asm volatile(".set  MODE_SVC, 0x13");
asm volatile(".set  MODE_ABT, 0x17");
asm volatile(".set  MODE_UND, 0x1B");
asm volatile(".set  MODE_SYS, 0x1F");

asm volatile(".equ  I_F_BIT, 0xC0");

extern "C" void Entry() __attribute__((section(".entry_code"), naked));

void Entry()
{
  // Set up the Stack for Undefined mode
  asm volatile("LDR   r0, =__initial_stack_pointer");  // @ Read the stack address
  asm volatile("MSR   cpsr_c, #MODE_UND|I_F_BIT");     // @ switch to undef  mode
  asm volatile("MOV   sp,r0");                         // @ write the stack pointer
  asm volatile("SUB   r0, r0, #UND_STACK_SIZE");       // @ give stack space

  // Set up the Stack for abort mode
  asm volatile("MSR   cpsr_c, #MODE_ABT|I_F_BIT");     // @ Change to abort mode
  asm volatile("MOV   sp, r0");                        // @ write the stack pointer
  asm volatile("SUB   r0,r0, #ABT_STACK_SIZE");        // @ give stack space

  // Set up the Stack for FIQ mode
  asm volatile("MSR   cpsr_c, #MODE_FIQ|I_F_BIT");     // @ change to FIQ mode
  asm volatile("MOV   sp,r0");                         // @ write the stack pointer
  asm volatile("SUB   r0,r0, #FIQ_STACK_SIZE");        // @ give stack space

  // Set up the Stack for IRQ mode
  asm volatile("MSR   cpsr_c, #MODE_IRQ|I_F_BIT");     // @ change to IRQ mode
  asm volatile("MOV   sp,r0");                         // @ write the stack pointer
  asm volatile("SUB   r0,r0, #IRQ_STACK_SIZE");        // @ give stack space

  // Set up the Stack for SVC mode
  asm volatile("MSR   cpsr_c, #MODE_SVC|I_F_BIT");     // @ change to SVC mode
  asm volatile("MOV   sp,r0");                         // @ write the stack pointer
  asm volatile("SUB   r0,r0, #SVC_STACK_SIZE");        // @ give stack space

  // Set up the Stack for User/System mode
  asm volatile("MSR   cpsr_c, #MODE_SYS|I_F_BIT");     // @ change to system mode
  asm volatile("MOV   sp,r0");                         // @ write the stack pointer

  // Copy the interrupt vector table from ROM to RAM.
  crt::init_isr_vectors();

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
  asm volatile("bl main");

  // Catch an unexpected return from main.
  for(;;)
  {
    // Replace with a loud error if desired.
    mcal::wdg::trigger();
  }
}
