///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2014.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_irq.h>

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
