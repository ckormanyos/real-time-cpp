///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2014.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdint>
#include <mcal/mcal.h>

namespace crt
{
  void init_ram  ();
  void init_ctors();
}

namespace int_vect
{
  void load_lower_interrupt_vector_data(const std::uint32_t load_address);
}

extern "C" int  main                   ();
extern "C" void __initial_stack_pointer();
extern "C" void __my_startup           () __attribute__((section(".text.startup"), used, noinline));

void __my_startup()
{
  // Setup the interrupt stack (with 1kB stack size),
  // and switch to irq mode.
  asm volatile("ldr r3, =__initial_stack_pointer");
  asm volatile("msr cpsr_c, #(0x12 | 0xC0)");
  asm volatile("mov sp, r3");
  asm volatile("sub r3, r3, #0x0400");

  // Setup the user/system stack (with 3kB stack size),
  // and switch back to system mode.
  asm volatile("msr cpsr_c, #(0x13 | 0xC0)");
  asm volatile("mov sp, r3");

  // Load the lower interrupt vector table to address 0x00000000.
  int_vect::load_lower_interrupt_vector_data(UINT32_C(0x00000000));

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
  asm volatile("b main");

  // Catch an unexpected return from main.
  for(;;)
  {
    // Replace with a loud error if desired.
    mcal::wdg::secure::trigger();
  }
}
