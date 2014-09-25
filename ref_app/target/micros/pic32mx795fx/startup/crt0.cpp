
///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2014.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// Microchip(R) pic32mx795fx startup code
// Switched to C++ and modified for pic32mx795fx by Chris.

#include <mcal/mcal.h>

namespace crt
{
  void init_ram();
  void init_ctors();
}

extern "C" void __my_startup_entry() __attribute__((section(".startup"), used, noinline));
extern "C" void __my_startup      () __attribute__((section(".startup"), used, noinline));

asm volatile(".section .startup,\"ax\",@progbits");
asm(".set noreorder");
asm(".ent __my_startup_entry");
asm volatile("__my_startup_entry:");

  // Check what kind of reset this is.
  asm volatile("mfc0 $k0, $12, 0");               // Read the status register.
  asm volatile("ext $k0, $k0, 19, 1");            // Check the nmi bit.
  asm volatile("beqz $k0, jump_to_normal_reset"); // It is a normal reset.
  asm volatile("nop");

  // An nmi interrupt has been detected.
  // This happens when there is a watchdog reset in sleep mode.
  // Do nothing. Simply return and let the cpu wakeup.
  asm volatile("eret");
  asm volatile("nop");

  asm volatile("jump_to_normal_reset:");

  // Initialize the stack pointer and the global (small data) pointer.
  asm volatile("la $sp, __initial_stack_pointer");
  asm volatile("la $gp, _gp");

  asm volatile("mfc0 $t1, $12, 2");
  asm volatile("add  $t3, $t1, $0");
  asm volatile("ext  $t2, $t1, 26, 4");
  asm volatile("ins  $t1, $t2, 6, 4");
  asm volatile("mtc0 $t1, $12, 2");
  asm volatile("ehb");
  asm volatile("wrpgpr $gp, $gp");
  asm volatile("mtc0 $t3, $12, 2");

  // Setup the coprocessor cp0.

  // Clear the count register.
  asm volatile("mtc0 $0, $9, 0");

  // Set the compare register.
  asm volatile("li $t2, -1");
  asm volatile("mtc0 $t2, $11, 0");

  // Set the ebase register to points to the interrupt vector table,
  asm volatile("la $t1, _ebase_address");
  asm volatile("mtc0 $t1, $15, 1");

  // Set the intctl register to specify the interrupt vector spacing.
  asm volatile("la $t1, _vector_spacing");
  asm volatile("li $t2, 0");
  asm volatile("ins $t2, $t1, 5, 5");
  asm volatile("mtc0 $t2, $12, 1");

  // Set the cause register.
  // Reset everything, set the iv-bit to enable vectored interrupts.
  asm volatile("li $t1, 0x00800000");
  asm volatile("mtc0 $t1, $13, 0");

  // Set the status register.
  // Reset everything set bev = 0 (enable vectored interrupts),
  // Set ipl = 0 (lowest priority run mode).
  asm volatile("li $t1, 0");
  asm volatile("mtc0 $t1, $12, 0");

  // Call __my_startup which will do the following:
  // * finish the initialization
  // * subsequently call main()
  // * and never return from main().
  asm volatile("la $t0, __my_startup");
  asm volatile("jalr $t0");
asm(".end __my_startup_entry");
asm(".globl __my_startup_entry");

void __my_startup()
{
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
  asm volatile("la $t0, main");
  asm volatile("jalr $t0");

  // Catch an unexpected return from main.
  for(;;)
  {
    // Replace with a loud error if desired.
    mcal::wdg::secure::trigger();
  }
}
