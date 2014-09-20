///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2014.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_gpt.h>
#include <mcal_irq.h>
#include <mcal_reg_access.h>

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

void mcal::irq::secure::interrupt_vector()
{
  // Query and clear the active interrupt bit(s).

  // TBD: For now, the rpi_arm timer is the only interrupt enabled.
  // TBD: So we do not have to query the interrupt source.

  // TBD: Query the interrupt source.

  // Clear the rpi_arm timer interrupt.
  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::rpi_armtimer_irq_clear,
                    UINT32_C(1)>::reg_set();

  // Call the rpi_arm timer callback function in mcal::gpt.
  mcal::gpt::detail::rpi_armtimer_interrupt_callback();
}

void mcal::irq::secure::fast_interrupt_vector()
{
}
