///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_irq.h>

namespace
{
  void __attribute__((nomips16)) enable_interrupts();
  void __attribute__((nomips16)) disable_interrupts();

  void __attribute__((nomips16)) enable_interrupts()
  {
    unsigned int result = 0U;

    asm volatile("ei %0" : "=r"(result));

    static_cast<void>(result);
  }

  void __attribute__((nomips16)) disable_interrupts()
  {
    unsigned int result = 0U;

    asm volatile("di %0" : "=r"(result));

    static_cast<void>(result);
  }
}

void mcal::irq::init(const config_type*)
{
  // Enable all global interrupts.
  mcal::irq::enable_all();
}

void mcal::irq::enable_all()
{
  enable_interrupts();
}

void mcal::irq::disable_all()
{
  disable_interrupts();
}
