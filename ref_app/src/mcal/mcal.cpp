///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <limits>
#include <mcal/mcal.h>

static_assert(   (std::numeric_limits<mcal::gpt::value_type>::digits >= 32)
              && (std::numeric_limits<mcal::gpt::value_type>::is_signed == false),
              "the gpt value type must be unsigned and have at least 32 bits");

void mcal::init()
{
  // Initialize the microcontroller abstraction layer.

  // Note: mcal::cpu::init() has already been called from the startup code.
  // Therefore, the following subroutines have already been called:
  //   mcal::wdg::init(nullptr);
  //   mcal::port::init(nullptr);
  //   mcal::osc::init(nullptr);

  mcal::irq::init (nullptr);
  mcal::gpt::init (nullptr);
  mcal::ser::init (nullptr);
  mcal::spi::init (nullptr);
  mcal::pwm::init (nullptr);
}
