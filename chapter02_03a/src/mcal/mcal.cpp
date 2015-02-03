///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal/mcal.h>

void mcal::init()
{
  // Initialize the microcontroller abstraction layer.

  // Note: mcal::cpu::init() has already been called from the startup code.
  // Therefore, the following subroutines have already been called:
  //   mcal::wdg::init(nullptr);
  //   mcal::port::init(nullptr);
  //   mcal::osc::init(nullptr);

  mcal::gpt::init(nullptr);

  mcal::irq::init(nullptr);
}
