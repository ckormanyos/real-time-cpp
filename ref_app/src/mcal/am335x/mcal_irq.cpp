///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <array>
#include <mcal_cpu.h>
#include <mcal_irq.h>
#include <am335x_hw_regs.h>

extern "C"
{
  extern std::array<isr_vector_type, mcal::irq::interrupt_descriptor::number_of_interrupts> __isr_vector;
}

void mcal::irq::interrupt_descriptor::register_interrupt(const mcal::irq::interrupt_descriptor& isr_descriptor)
{
  if(isr_descriptor.number < __isr_vector.size())
  {
    __isr_vector[isr_descriptor.number] = isr_descriptor.isr_function;

    const bool isr_routing_is_irq = (isr_descriptor.routing == interrupt_descriptor::route_to_irq);

    INTC->ILR[isr_descriptor.number] = std::uint32_t(  std::uint32_t(std::uint32_t(isr_descriptor.priority << std::uint32_t(2UL)) & std::uint32_t(0x01FCUL))
                                                     | std::uint32_t(isr_routing_is_irq ? 0UL : 1UL));

    // Enable the system interrupt in the corresponding MIR_CLEAR register.
    INTC->REG[std::size_t(std::size_t(isr_descriptor.number >> 5U) & std::size_t(3UL))].MIR_CLEAR = std::uint32_t(1UL << (isr_descriptor.number & std::size_t(0x01FUL)));
  }
}

void mcal::irq::init(const config_type*)
{
  // Reset the ARM interrupt controller.
  INTC->SYSCONFIG = std::uint32_t(2UL);

  // Wait for the interrupt reset to finish.
  while(std::uint32_t(INTC->SYSSTATUS & std::uint32_t(1UL)) != std::uint32_t(1UL))
  {
    mcal::cpu::nop();
  }

  // Enable all interrupt generation by setting the priority threshold appropriately.
  INTC->THRESHOLD = std::uint32_t(0xFFUL);

  // Enable all global interrupts.
  mcal::irq::enable_all();
}
