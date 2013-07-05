///////////////////////////////////////////////////////////////////////////////
//  Copyright Michael Schnerr 2011 - 2013.
//  Copyright Christopher Kormanyos 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <array>
#include <mcal_cpu.h>
#include <mcal_irq.h>

void mcal::irq::init(const config_type*)
{
  // Reset the ARM interrupt controller.
  mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::intc::sysconfig, 2UL>::reg_set();

  // Wait for the interrupt reset to finish.
  while(std::uint32_t(mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::intc::sysstatus>::reg_get() & std::uint32_t(1UL)) != std::uint32_t(1UL))
  {
    mcal::cpu::nop();
  }

  // Enable the generation of all interrupts by setting the
  // priority threshold appropriately.
  mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::intc::threshold, 0xFFUL>::reg_set();

  // Enable all global interrupts.
  mcal::irq::enable_all();
}
