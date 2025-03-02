///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_irq.h>

#include <cstdint>
#include <limits>

extern "C"
{
  extern void enable_irq(uint32_t);
}

void mcal::irq::init(const config_type*)
{
  // Enable all interrupts on running core.
  ::enable_irq((std::numeric_limits<std::uint32_t>::max)());
}
