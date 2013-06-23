///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <array>
#include <algorithm>
#include <mcal_cpu.h>
#include <mcal_irq.h>
#include <am335x_hw_regs.h>

extern "C"
{
  void __vector_unused_irq() { for(;;) { mcal::cpu::nop(); } }

  // Declare the RAM ISR vectors.
  std::array<mcal::irq::isr_handler_type,
             mcal::irq::interrupt_descriptor::number_of_interrupts> isr_ram_vectors;
}

void mcal::irq::register_interrupt(const mcal::irq::interrupt_descriptor& isr_descriptor)
{
  if(isr_descriptor.number < isr_ram_vectors.size())
  {
    // Assign the ISR.
    isr_ram_vectors[isr_descriptor.number] = isr_descriptor.handler;

    const bool isr_routing_is_irq = (isr_descriptor.routing == interrupt_descriptor::route_to_irq);

    INTC->ILR[isr_descriptor.number] = ((isr_descriptor.priority << 2U) & 0x01FCUL) | (isr_routing_is_irq ? 0UL : 1UL);

    // Enable the system interrupt in the corresponding MIR_CLEAR register.
    INTC->REG[(isr_descriptor.number >> 5U) & 3UL].MIR_CLEAR = (1UL << (isr_descriptor.number & 0x01FUL));
  }
}

void mcal::irq::init(const config_type*)
{
  // Initialize all the RAM interrupt vectors.
  std::fill(isr_ram_vectors.begin(),
            isr_ram_vectors.end(),
            __vector_unused_irq);

  // Reset the ARM interrupt controller.
  INTC->SYSCONFIG = 2UL;

  // Wait for the reset to complete
  while(std::uint32_t(INTC->SYSSTATUS & 1U) != std::uint32_t(1UL)) { ; }

  // Enable any interrupt generation by setting priority threshold.
  INTC->THRESHOLD = 0xFFU;

  // Enable all global interrupts.
  mcal::irq::enable_all();
}
