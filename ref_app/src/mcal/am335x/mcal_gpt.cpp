///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2013.
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
}

mcal::gpt::value_type consistent_microsecond_tick()
{
  // Return the system tick using a multiple read to ensure
  // data consistency of the high-byte of the system tick.

  typedef std::uint32_t timer_address_type;
  typedef std::uint32_t timer_register_type;

  // Do the first read of the timer7 counter and the system tick.
  const timer_register_type   tim7_cnt_1 = timer_register_type(mcal::reg::access<timer_address_type, timer_register_type, mcal::reg::dmtimer7::tcrr>::reg_get() + 24002UL);
  const mcal::gpt::value_type sys_tick_1 = system_tick;

  // Do the second read of the timer7 counter and the system tick.
  const timer_register_type   tim7_cnt_2 = timer_register_type(mcal::reg::access<timer_address_type, timer_register_type, mcal::reg::dmtimer7::tcrr>::reg_get() + 24002UL);
  const mcal::gpt::value_type sys_tick_2 = system_tick;

  // Perform the consistency check and return the consistent microsecond tick.
  return ((tim7_cnt_2 >= tim7_cnt_1) ? mcal::gpt::value_type(sys_tick_1 + std::uint32_t(timer_register_type(tim7_cnt_1 + 12UL) / 24U))
                                     : mcal::gpt::value_type(sys_tick_2 + std::uint32_t(timer_register_type(tim7_cnt_2 + 12UL) / 24U)));
}

extern "C" void __vector_timer7();

void __vector_timer7()
{
  // Disable the DMTimer interrupts.
  mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::dmtimer7::irqenable_clr, 7UL>::reg_set();

  // Clear the status of the interrupt flags.
  mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::dmtimer7::irqstatus, 7UL>::reg_set();

  // Increment the 64-bit system tick by 1000, representing 1000us.
  system_tick += 1000U;

  // Notify end of interrupt.
  mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::dmtimer7::irq_eoi, 1UL>::reg_not();

  // Re-enable the DMTimer interrupts.
  mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::dmtimer7::irqenable_set, 2UL>::reg_set();
}

void mcal::gpt::init(const config_type*)
{
  if(gpt_is_initialized() == false)
  {
    mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::dmtimer7::tsicr, 6UL>::reg_set();
    while(std::uint32_t(mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::dmtimer7::tiocp_cfg>::reg_get() & std::uint32_t(1UL)) != std::uint32_t(0UL))
    {
      mcal::cpu::nop();
    }

    // Register the timer7 interrupt, including priority, routing, etc.
    mcal::irq::interrupt_descriptor::register_interrupt<mcal::irq::interrupt_descriptor::isr_id_tint7,
                                                        mcal::irq::interrupt_descriptor::priority_type(0U),
                                                        mcal::irq::interrupt_descriptor::route_to_irq>();

    // Enable the timer7 overflow interrupt.
    mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::dmtimer7::irqenable_set, 2UL>::reg_msk<7UL>();

    // Set the timer7 counter register.
    while(mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::dmtimer7::twps>::reg_get() != std::uint32_t(0UL))
    {
      mcal::cpu::nop();
    }
    mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::dmtimer7::tcrr, 0xFFFFFFFEUL - 24000UL>::reg_set();

    // Set the timer7 reload register.
    while(mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::dmtimer7::twps>::reg_get() != std::uint32_t(0UL))
    {
      mcal::cpu::nop();
    }
    mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::dmtimer7::tldr, 0xFFFFFFFEUL - 24000UL>::reg_set();

    // Set auto reload mode and start timer (no prescaler).
    mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::dmtimer7::tclr, 3UL>::reg_set();

    gpt_is_initialized() = true;
  }
}

mcal::gpt::value_type mcal::gpt::get_time_elapsed()
{
  return (gpt_is_initialized() ? consistent_microsecond_tick()
                               : mcal::gpt::value_type(0U));
}
