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
  // Enable all global interrupts.
  mcal::irq::enable_all();
}

void mcal::irq::enable_all()
{
  // Enable all maskable interrupts.
  asm volatile("mrs r1, cpsr");
  asm volatile("bic r1, r1, #0x80");
  asm volatile("msr cpsr_c, r1");
}

void mcal::irq::disable_all()
{
  // Disable all maskable interrupts.
  asm volatile("mrs r1, cpsr");
  asm volatile("orr r1, r1, #0x80");
  asm volatile("msr cpsr_c, r1");
}

void mcal::irq::secure::int_vect_undef_instr_handler_callback   () { for(;;) { mcal::cpu::nop(); } }
void mcal::irq::secure::int_vect_sw_interrupt_handler_callback  () { for(;;) { mcal::cpu::nop(); } }
void mcal::irq::secure::int_vect_prefetch_abort_handler_callback() { for(;;) { mcal::cpu::nop(); } }
void mcal::irq::secure::int_vect_data_abort_handler_callback    () { for(;;) { mcal::cpu::nop(); } }
void mcal::irq::secure::int_vect_unused_05_handler_callback     () { for(;;) { mcal::cpu::nop(); } }

void mcal::irq::secure::int_vect_irq_handler_callback()
{
  // Query and clear the active interrupt bit(s).

  // Query the interrupt source.
  const std::uint32_t pending_irq_value =
    mcal::reg::reg_access_static<std::uint32_t,
                                 std::uint32_t,
                                 mcal::reg::rpi_interrupt_irq_basic_pending>::reg_get();

  const bool pending_bit_00_is_set = (static_cast<std::uint32_t>(pending_irq_value & static_cast<std::uint32_t>(UINT32_C(1) << 0)) != UINT32_C(0));
  const bool pending_bit_01_is_set = (static_cast<std::uint32_t>(pending_irq_value & static_cast<std::uint32_t>(UINT32_C(1) << 1)) != UINT32_C(0));
  const bool pending_bit_02_is_set = (static_cast<std::uint32_t>(pending_irq_value & static_cast<std::uint32_t>(UINT32_C(1) << 2)) != UINT32_C(0));
  const bool pending_bit_03_is_set = (static_cast<std::uint32_t>(pending_irq_value & static_cast<std::uint32_t>(UINT32_C(1) << 3)) != UINT32_C(0));
  const bool pending_bit_06_is_set = (static_cast<std::uint32_t>(pending_irq_value & static_cast<std::uint32_t>(UINT32_C(1) << 6)) != UINT32_C(0));
  const bool pending_bit_07_is_set = (static_cast<std::uint32_t>(pending_irq_value & static_cast<std::uint32_t>(UINT32_C(1) << 7)) != UINT32_C(0));
  const bool pending_bit_08_is_set = (static_cast<std::uint32_t>(pending_irq_value & static_cast<std::uint32_t>(UINT32_C(1) << 8)) != UINT32_C(0));
  const bool pending_bit_09_is_set = (static_cast<std::uint32_t>(pending_irq_value & static_cast<std::uint32_t>(UINT32_C(1) << 9)) != UINT32_C(0));

  // ARM Timer IRQ pending: Call the rpi_arm timer callback function in mcal::gpt.
  if(pending_bit_00_is_set) { mcal::gpt::detail::rpi_armtimer_interrupt_callback(); }

  // ARM Mailbox IRQ pending: Not yet needed.
  if(pending_bit_01_is_set) { }

  // ARM Doorbell 0 IRQ pending: Not yet needed.
  if(pending_bit_02_is_set) { }

  // ARM Doorbell 1 IRQ pending: Not yet needed.
  if(pending_bit_03_is_set) { }

  // Illegal access type 1 IRQ pending: Not yet needed.
  if(pending_bit_06_is_set) { }

  // Illegal access type 0 IRQ pending: Not yet needed.
  if(pending_bit_07_is_set) { }

  // One or more bits set in pending register 1: Not yet needed.
  if(pending_bit_08_is_set) { }

  // One or more bits set in pending register 2: Not yet needed.
  if(pending_bit_09_is_set) { }

  // TBD: Implement potential support for GPU and additional interrupts.
}

void mcal::irq::secure::int_vect_fiq_handler_callback           () { }
void mcal::irq::secure::int_vect_future_08_handler_callback     () { for(;;) { mcal::cpu::nop(); } }
void mcal::irq::secure::int_vect_future_09_handler_callback     () { for(;;) { mcal::cpu::nop(); } }
void mcal::irq::secure::int_vect_future_10_handler_callback     () { for(;;) { mcal::cpu::nop(); } }
void mcal::irq::secure::int_vect_future_11_handler_callback     () { for(;;) { mcal::cpu::nop(); } }
void mcal::irq::secure::int_vect_future_12_handler_callback     () { for(;;) { mcal::cpu::nop(); } }
void mcal::irq::secure::int_vect_future_13_handler_callback     () { for(;;) { mcal::cpu::nop(); } }
void mcal::irq::secure::int_vect_future_14_handler_callback     () { for(;;) { mcal::cpu::nop(); } }
void mcal::irq::secure::int_vect_future_15_handler_callback     () { for(;;) { mcal::cpu::nop(); } }
