// ***************************************************************************************
// Filename    : Startup.c
//
// Author      : Chalandi Amine
//
// Owner       : Chalandi Amine
// 
// Date        : 11.03.2020
// 
// Description : C/C++ Runtime Setup (Crt0)
// 
// ***************************************************************************************

#include <mcal_cpu.h>
#include <mcal_wdg.h>

namespace crt
{
  void init_ram();
  void init_ctors();
}

//=========================================================================================
// Extern function prototype
//=========================================================================================
extern "C"
{
  int main(void);
}

asm (".extern __initial_stack_pointer");
asm (".extern InterruptVectorTable");

extern "C"
{
  void __my_startup(void) __attribute__ ((section(".startup")));
}

extern "C" void __my_startup(void)
{
  /* setup the stack pointer */
  asm volatile("la sp, __initial_stack_pointer");

  /* setup the interrupt vector table */
  asm volatile("la x1, InterruptVectorTable");
  asm volatile("ori x1, x1, 3");
  asm volatile("csrw mtvec, x1");

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
  asm volatile("jal main");

  // Catch an unexpected return from main.
  for(;;)
  {
    // Replace with a loud error if desired.
    mcal::wdg::secure::trigger();
  }
}
