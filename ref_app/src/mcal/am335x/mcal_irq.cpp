///////////////////////////////////////////////////////////////////////////////
//  Copyright Michael Schnerr 2011 - 2013.
//  Copyright Christopher Kormanyos 2013 - 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdint>
#include <mcal_cpu.h>
#include <mcal_irq.h>

void mcal::irq::init(const config_type*)
{
  // Reset the ARM(R) interrupt controller.
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::intc::sysconfig, UINT32_C(2)>::reg_set();

  // Wait for the interrupt reset to finish.
  while(std::uint32_t(mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::intc::sysstatus>::reg_get() & UINT32_C(1)) != UINT32_C(1))
  {
    mcal::cpu::nop();
  }

  // Enable the generation of all interrupts by setting the
  // priority threshold appropriately.
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::intc::threshold, UINT32_C(0xFF)>::reg_set();

  // Enable all global interrupts.
  mcal::irq::enable_all();
}
