///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2024.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// RaspberryPi RP2040 dual-core ARM(R) Cortex(R)-M0+ startup code.

#include <Cpu/Cpu.h>
#include <Gpio/Gpio.h>

#include <mcal/mcal.h>

namespace crt
{
  void init_ram();
  void init_ctors();
}

extern "C" void __my_startup(void) __attribute__((used, noinline));
extern "C" void __main_core0(void) __attribute__((used, noinline));
extern "C" void __main_core1(void) __attribute__((used, noinline));

void __my_startup(void)
{
  // Load the stack pointer.
  // The stack pointer is automatically loaded from
  // the base position of the interrupt vector table.
  // So we do nothing here.

  // Chip init: Watchdog, port, and oscillator.
  mcal::cpu::init();

  // Initialize statics from ROM to RAM.
  // Zero-clear default-initialized static RAM.
  crt::init_ram();
  mcal::wdg::secure::trigger();

  // Call all ctor initializations.
  crt::init_ctors();
  mcal::wdg::secure::trigger();

  // Jump to __main_core0, which subsequently starts up core1
  // (and never return).

  asm volatile("ldr r3, =__main_core0");
  asm volatile("blx r3");

  // Catch an unexpected return from main.
  for(;;)
  {
    // Replace with a loud error if desired.
    mcal::wdg::secure::trigger();
  }
}

extern "C"
{
  void __main_core0(void)
  {
    /* Disable interrupts on core 0 */
    asm volatile("CPSID i");

    /* Output disable on pin 25 */
    LED_GREEN_CFG();

    /* Start the Core 1 and turn on the led to be sure that we passed successfully the core 1 initiaization */
    if(TRUE == ::RP2040_StartCore1())
    {
      LED_GREEN_ON();
    }
    else
    {
      /* Loop forever in case of error */
      while(1)
      {
        __asm volatile("NOP");
      }
    }

    // Run the main function of the core 0, it will start the core 1.

    // Synchronize with core 1.
    ::RP2040_MulticoreSync(SIO->CPUID);

    /* endless loop on the core 0 */
    for(;;) { ; }
  }

  void __main_core1(void)
  {
    /* Note: Core 1 is started with interrupt enabled by the BootRom */

    /* Clear the stiky bits of the FIFO_ST on core 1 */
    SIO->FIFO_ST.reg = 0xFFu;
    __asm volatile("DSB");

    /* Clear all pending interrupts on core 1 */
    NVIC->ICPR[0] = (uint32)-1;

    /* Synchronize with core 0 */
    ::RP2040_MulticoreSync(SIO->CPUID);

    // Jump to main (and never return).

    asm volatile("ldr r3, =main");
    asm volatile("blx r3");
  }
}
