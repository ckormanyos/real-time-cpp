// ***************************************************************************************
// Filename    : Startup.c
//
// Author      : Chalandi Amine
//
// Owner       : Chalandi Amine
// 
// Date        : 04.09.2024
// 
// Description : C/C++ Runtime Setup (Crt0)
// 
// ***************************************************************************************

#include <mcal_cpu.h>
#include <mcal_irq.h>
#include <mcal_led.h>

#include <Platform_Types.h>
#include <RP2350.h>

#include <util/utility/util_time.h>

extern "C"
{
  extern void core_1_run_flag_set(bool);

  void __my_startup(void) __attribute__((used));
  void __main(void);

  extern int  main        (void);
  extern void __main_core0(void);
  extern void __main_core1(void) __attribute__((used));

  extern boolean RP2350_StartCore1   (void);
  extern void    RP2350_MulticoreSync(uint32_t CpuId);
}

namespace crt
{
  auto init_ram  () -> void;
  auto init_ctors() -> void;
}

namespace local
{
  inline auto get_cpuid() -> std::uint32_t
  {
    const std::uint32_t cpuid { HW_PER_SIO->CPUID.reg };

    return cpuid;
  }
}

extern "C"
void __my_startup(void)
{
  /* Configure the system clock */
  mcal::cpu::init();

  /* Initialize the RAM memory */
  crt::init_ram();

  /* Initialize the non-local C++ objects */
  crt::init_ctors();

  // Jump to __main, which calls __main_core0, the main
  // function of core 0. The main function of core 0
  // itself then subsequently starts up core 1 which
  // is launched in __main_core1. Both of these core 0/1
  // subroutines will never return.

  ::__main();

  // Catch an unexpected return from __main().
  for(;;)
  {
    // Replace with a loud error if desired.
    mcal::wdg::secure::trigger();
  }
}

extern "C"
void __main(void)
{
  // Run the main function of core 0.
  // This will subsequently start core 1.
  ::__main_core0();

  // Synchronize with core 1.
  RP2350_MulticoreSync(local::get_cpuid());

  // It is here that an actual application could
  // be started and then executed on core 0.

  // Execute an endless loop on core 0 (while the application runs on core 1).
  for(;;) { mcal::cpu::nop(); }

  // This point is never reached.
}

extern "C"
void __main_core0(void)
{
  // Disable interrupts on core 0.
  mcal::irq::disable_all();

  /* Start the Core 1 and turn on the led to be sure that we passed successfully the core 1 initiaization */
  if(TRUE == RP2350_StartCore1())
  {
    mcal::led::led0().toggle();
  }
  else
  {
    /* Loop forever in case of error */
    while(1)
    {
      asm volatile("NOP");
    }
  }
}

extern "C"
void __main_core1(void)
{
  // Disable interrupts on core 1.
  mcal::irq::disable_all();

  core_1_run_flag_set(true);

  /* Note: Core 1 is started with interrupt enabled by the BootRom */

  /* Clear the stiky bits of the FIFO_ST on core 1 */
  HW_PER_SIO->FIFO_ST.reg = 0xFFu;

  /*Setting EXTEXCLALL allows external exclusive operations to be used in a configuration with no MPU.
  This is because the default memory map does not include any shareable Normal memory.*/
  SCnSCB->ACTLR |= (1ul<<29);

  __asm volatile("DSB");

  /* Clear all pending interrupts on core 1 */
  NVIC->ICPR[0] = (uint32_t)-1;

  // Synchronize with core 0.
  RP2350_MulticoreSync(local::get_cpuid());

  // Jump to main on core 1 (and never return).
  asm volatile("ldr r3, =main");
  asm volatile("blx r3");
}
