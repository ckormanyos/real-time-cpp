///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2014.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_cpu.h>
#include <mcal_gpt.h>
#include <mcal_irq.h>
#include <mcal_reg.h>

void mcal::irq::init(const config_type*)
{
  // Enable all global (maskable) interrupts.
  mcal::irq::enable_all();
}

extern "C" void __int_vect_undef_instr_handler   () { for(;;) { mcal::cpu::nop(); } }
extern "C" void __int_vect_sw_interrupt_handler  () { for(;;) { mcal::cpu::nop(); } }
extern "C" void __int_vect_prefetch_abort_handler() { for(;;) { mcal::cpu::nop(); } }
extern "C" void __int_vect_data_abort_handler    () { for(;;) { mcal::cpu::nop(); } }
extern "C" void __int_vect_unused_05_handler     () { for(;;) { mcal::cpu::nop(); } }

extern "C" void __int_vect_irq_handler()
{
  // Query and clear the active interrupt bit(s).

  // Query the interrupt source.
  const std::uint32_t pending_irq_value =
    mcal::reg::reg_access_static<std::uint32_t,
                                 std::uint32_t,
                                 mcal::reg::rpi_interrupt_irq_basic_pending>::reg_get();

  const bool pending_bit_00_is_set = (std::uint32_t(pending_irq_value & std::uint32_t(1ULL << 0U)) != UINT32_C(0));
  const bool pending_bit_01_is_set = (std::uint32_t(pending_irq_value & std::uint32_t(1ULL << 1U)) != UINT32_C(0));
  const bool pending_bit_02_is_set = (std::uint32_t(pending_irq_value & std::uint32_t(1ULL << 2U)) != UINT32_C(0));
  const bool pending_bit_03_is_set = (std::uint32_t(pending_irq_value & std::uint32_t(1ULL << 3U)) != UINT32_C(0));
  const bool pending_bit_06_is_set = (std::uint32_t(pending_irq_value & std::uint32_t(1ULL << 6U)) != UINT32_C(0));
  const bool pending_bit_07_is_set = (std::uint32_t(pending_irq_value & std::uint32_t(1ULL << 7U)) != UINT32_C(0));
  const bool pending_bit_08_is_set = (std::uint32_t(pending_irq_value & std::uint32_t(1ULL << 8U)) != UINT32_C(0));
  const bool pending_bit_09_is_set = (std::uint32_t(pending_irq_value & std::uint32_t(1ULL << 9U)) != UINT32_C(0));

  // ARM Timer IRQ pending: Call the rpi_arm timer callback function in mcal::gpt.
  if(pending_bit_00_is_set) { mcal::gpt::detail::rpi_armtimer_interrupt_callback(); }

  // ARM Mailbox IRQ pending: Not yet needed.
  if(pending_bit_01_is_set) { mcal::cpu::nop(); }

  // ARM Doorbell 0 IRQ pending: Not yet needed.
  if(pending_bit_02_is_set) { mcal::cpu::nop(); }

  // ARM Doorbell 1 IRQ pending: Not yet needed.
  if(pending_bit_03_is_set) { mcal::cpu::nop(); }

  // Illegal access type 1 IRQ pending: Not yet needed.
  if(pending_bit_06_is_set) { mcal::cpu::nop(); }

  // Illegal access type 0 IRQ pending: Not yet needed.
  if(pending_bit_07_is_set) { mcal::cpu::nop(); }

  // One or more bits set in pending register 1: Not yet needed.
  if(pending_bit_08_is_set) { mcal::cpu::nop(); }

  // One or more bits set in pending register 2: Not yet needed.
  if(pending_bit_09_is_set) { mcal::cpu::nop(); }

  // TBD: Implement potential support for GPU and additional interrupts.
}

extern "C" void __int_vect_fiq_handler() { mcal::cpu::nop(); }
