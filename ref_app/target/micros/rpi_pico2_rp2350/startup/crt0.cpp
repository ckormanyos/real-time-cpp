///////////////////////////////////////////////////////////////////////////////
//  Copyright Amine Chalandi 2024.
//  Copyright Christopher Kormanyos 2024.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// RaspberryPi RP2350 dual-core ARM(R) Cortex(R)-M33 startup code.

#include <mcal_cpu.h>
#include <mcal_cpu_rp2350.h>
#include <mcal_irq.h>
#include <mcal_reg.h>
#include <mcal_wdg.h>

namespace crt
{
  auto init_ram  () -> void;
  auto init_ctors() -> void;
}

extern "C" auto __my_startup() -> void __attribute__((section(".startup"), used, noinline));
extern "C" auto __main      () -> void __attribute__((section(".startup"), used, noinline));
extern "C" auto __main_core0() -> void __attribute__((section(".startup"), used, noinline));
extern "C" auto __main_core1() -> void __attribute__((section(".startup"), used, noinline));

extern "C"
{
  auto core_1_run_flag_set(bool) noexcept -> void;
  auto core_1_run_flag_get() noexcept -> bool;
}

namespace local
{
  inline auto get_cpuid() -> std::uint32_t
  {
    const std::uint32_t
      cpuid
      {
        mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::sio_cpuid>::reg_get()
      };

    return cpuid;
  }
}

extern "C"
auto __my_startup() -> void
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
  // function of core0. The main function of core0
  // itself then subsequently starts up core1 which
  // is launched in __main_core1. Both of these core0/1
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
auto __main() -> void
{
  // Run the main function of core0.
  // This will subsequently start core1.
  ::__main_core0();

  // Synchronize with core1.
  mcal::cpu::rp2350::multicore_sync(local::get_cpuid());

  // It is here that an actual application could
  // be started and then executed on core0.

  // Execute an endless loop on core0 (while the application runs on core1).
  for(;;) { mcal::cpu::nop(); }

  // This point is never reached.
}

extern "C"
auto __main_core0() -> void
{
  // Disable interrupts on core0.
  mcal::irq::disable_all();

  // Start core1 and verify successful initiaization of core1.
  if(!mcal::cpu::rp2350::start_core1())
  {
    // In case of error, loop forever (on core0).
    for(;;)
    {
      // Replace with a loud error if desired.
      mcal::wdg::secure::trigger();
    }
  }

  // This flag will be set by core1 (which is now running).
  while(!core_1_run_flag_get())
  {
    mcal::cpu::nop();
  }

  // This subroutine (running on core0) *does* return
  // at this point here.
}

extern "C"
auto __main_core1() -> void
{
  // Disable interrupts on core1.
  mcal::irq::disable_all();

  core_1_run_flag_set(true);

  // Core1 is started via interrupt enabled by the BootRom.
  // But core1 remains in an interrupt handler until core0
  // actually manually starts core1 in the subroutine
  // mcal::cpu::rp2040::start_core1(). Execution on core1
  // begins here.

  // Clear the sticky bits of the FIFO_ST on core1.
  // HW_PER_SIO->FIFO_ST.reg = 0xFFu;
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::sio_fifo_st,
                               std::uint32_t { UINT32_C(0xFF) }>::reg_set();

  // Setting EXTEXCLALL allows external exclusive operations to be used
  // in a configuration with no MPU. This is because the default memory map
  // does not include any shareable normal memory.

  // SCnSCB->ACTLR |= (1ul<<29);
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::scnscb_actlr,
                               UINT32_C(29)>::bit_set();

  asm volatile("dsb");

  // Clear all pending interrupts on core1.

  // NVIC->ICPR[0U] = static_cast<std::uint32_t>(UINT32_C(0xFFFFFFFF));
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::nvic_icpr,
                               std::uint32_t { UINT32_C(0xFFFFFFFF) }>::reg_set();

  // Synchronize with core0.
  mcal::cpu::rp2350::multicore_sync(local::get_cpuid());

  // Enable the hardware FPU on core1.

  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::ppb_nsacr,
                               std::uint32_t { (1UL << 10U) | (1UL << 11U) }>::reg_or();

  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::ppb_cpacr,
                               std::uint32_t { (3UL << 20U) | (3UL << 22U) }>::reg_or();

  // Jump to main on core1 (and never return).
  asm volatile("ldr r3, =main");
  asm volatile("blx r3");
}
