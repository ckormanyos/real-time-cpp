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

extern "C" int main(void) __attribute__((used));

extern "C" void __my_startup(void) __attribute__((section(".startup"), used, noinline));
extern "C" void __main      (void) __attribute__((section(".startup"), used, noinline));
extern "C" void __main_core0(void) __attribute__((section(".startup"), used, noinline));
extern "C" void __main_core1(void) __attribute__((section(".startup"), used, noinline));

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

  // Jump to __main, which calls __main_core0, the main
  // function of core 0. The main function of core 0
  // itself then subsequently starts up core 1 which
  // is launched in __main_core1. Bot of these core 0/1
  // subroutines will never return.

  __main();

  // Catch an unexpected return from __main().
  for(;;)
  {
    // Replace with a loud error if desired.
    mcal::wdg::secure::trigger();
  }
}

extern "C"
{
  void __main(void)
  {
    // Run the main function of core 0.
    // This will subsequently start core 1.
    ::__main_core0();

    // Synchronize with core 1.
    ::RP2040_MulticoreSync(SIO->CPUID);

    // Execute an endless loop on core 0.
    for(;;) { mcal::cpu::nop(); }

    // This point is never reached.
  }

  void __main_core0(void)
  {
    // Disable interrupts on core 0.
    mcal::irq::disable_all();

    // Set GPIO pin 25 to output.
    //LED_GREEN_CFG();

    // Start the core 1 and turn on the led to be sure that
    // we passed successfully the core 1 initiaization.
    if(TRUE == ::RP2040_StartCore1())
    {
      //LED_GREEN_ON();
    }
    else
    {
      // Loop forever in case of error.
      for(;;)
      {
        // Replace with a loud error if desired.
        mcal::wdg::secure::trigger();
      }
    }
  }

  void __main_core1(void)
  {
    // Core 1 is started via interrupt enabled by the BootRom.

    // Clear the sticky bits of the FIFO_ST on core 1.
    SIO->FIFO_ST.reg = 0xFFu;
    asm volatile("dsb");

    // Clear all pending interrupts on core 1.
    NVIC->ICPR[0U] = static_cast<std::uint32_t>(UINT32_C(0xFFFFFFFF));

    // Synchronize with core 0.
    ::RP2040_MulticoreSync(SIO->CPUID);

    // Jump to main (and never return).

    asm volatile("ldr r3, =main");
    asm volatile("blx r3");
  }
}
