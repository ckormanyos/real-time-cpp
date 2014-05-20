///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2014.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_cpu.h>
#include <mcal_gpt.h>
#include <mcal_irq.h>
#include <mcal_reg_access.h>

namespace
{
  // The one (and only one) system tick.
  volatile mcal::gpt::value_type system_tick;

  bool& gpt_is_initialized()
  {
    static bool is_init;

    return is_init;
  }

  constexpr std::uint16_t timer7_frequency_khz = UINT16_C(24);
  constexpr std::uint32_t timer7_reload_value  = static_cast<std::uint32_t>(UINT32_C(0x10000) * static_cast<std::uint32_t>(timer7_frequency_khz));
}

extern "C" void __vector_timer7();

void __vector_timer7()
{
  // Disable the dmtimer interrupts.
  mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::dmtimer7::irqenable_clr, UINT32_C(7)>::reg_set();

  // Clear the status of the interrupt flags.
  mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::dmtimer7::irqstatus, UINT32_C(7)>::reg_set();

  // Increment the 64-bit system tick with 1000, representing 1000 microseconds.
  system_tick += (timer7_reload_value / timer7_frequency_khz);

  // Signal the end of the interrupt.
  mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::dmtimer7::irq_eoi, UINT32_C(1)>::reg_not();

  // Enable the dmtimer interrupts.
  mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::dmtimer7::irqenable_set, UINT32_C(2)>::reg_set();
}

void mcal::gpt::init(const config_type*)
{
  if(gpt_is_initialized() == false)
  {
    mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::dmtimer7::tsicr, UINT32_C(6)>::reg_set();

    while(std::uint32_t(mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::dmtimer7::tiocp_cfg>::reg_get() & UINT32_C(1)) != UINT32_C(0))
    {
      mcal::cpu::nop();
    }

    // Register the dmtimer7 interrupt, including priority, routing, etc.
    mcal::irq::interrupt_descriptor::register_interrupt<mcal::irq::interrupt_descriptor::isr_id_tint7,
                                                        mcal::irq::interrupt_descriptor::priority_type(0U),
                                                        mcal::irq::interrupt_descriptor::route_to_irq>();

    // Enable the dmtimer7 overflow interrupt.
    mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::dmtimer7::irqenable_set, UINT32_C(2)>::reg_msk<UINT32_C(7)>();

    // Set the dmtimer7 counter register.
    while(mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::dmtimer7::twps>::reg_get() != UINT32_C(0))
    {
      mcal::cpu::nop();
    }

    mcal::reg::access<std::uint32_t,
                      std::uint32_t,
                      mcal::reg::dmtimer7::tcrr,
                      static_cast<std::uint32_t>(UINT32_C(0xFFFFFFFE) - timer7_reload_value)>::reg_set();

    // Set the dmtimer7 reload register.
    while(mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::dmtimer7::twps>::reg_get() != UINT32_C(0))
    {
      mcal::cpu::nop();
    }

    mcal::reg::access<std::uint32_t,
                      std::uint32_t,
                      mcal::reg::dmtimer7::tldr,
                      static_cast<std::uint32_t>(UINT32_C(0xFFFFFFFE) - timer7_reload_value)>::reg_set();

    // Setup auto reload mode and start dmtimer7, with no prescaler.
    mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::dmtimer7::tclr, UINT32_C(3)>::reg_set();

    gpt_is_initialized() = true;
  }
}

mcal::gpt::value_type mcal::gpt::secure::get_time_elapsed()
{
  // Return the system tick using a multiple read to ensure
  // data consistency of the high-byte of the system tick.

  typedef std::uint32_t timer_address_type;
  typedef std::uint32_t timer_register_type;

  // Do the first read of the dmtimer7 counter and the system tick.
  const timer_register_type   tim7_cnt_1 = timer_register_type(mcal::reg::access<timer_address_type, timer_register_type, mcal::reg::dmtimer7::tcrr>::reg_get() + timer_register_type(timer7_reload_value + 2U));
  const mcal::gpt::value_type sys_tick_1 = system_tick;

  // Do the second read of the dmtimer7 counter and the system tick.
  const timer_register_type   tim7_cnt_2 = timer_register_type(mcal::reg::access<timer_address_type, timer_register_type, mcal::reg::dmtimer7::tcrr>::reg_get() + timer_register_type(timer7_reload_value + 2U));
  const mcal::gpt::value_type sys_tick_2 = system_tick;

  // Perform the consistency check and obtain the consistent microsecond tick.
  const mcal::gpt::value_type consistent_microsecond_tick
    = ((tim7_cnt_2 >= tim7_cnt_1) ? mcal::gpt::value_type(sys_tick_1 + std::uint32_t(timer_register_type(tim7_cnt_1 + timer_register_type(timer7_frequency_khz / 2)) / timer7_frequency_khz))
                                  : mcal::gpt::value_type(sys_tick_2 + std::uint32_t(timer_register_type(tim7_cnt_2 + timer_register_type(timer7_frequency_khz / 2)) / timer7_frequency_khz)));

  return (gpt_is_initialized() ? consistent_microsecond_tick : mcal::gpt::value_type(0U));
}
