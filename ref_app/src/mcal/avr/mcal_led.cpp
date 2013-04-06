///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal/mcal.h>

namespace mcal
{
  namespace led
  {
    const led_type<std::uint8_t,
                   std::uint8_t,
                   mcal::reg::portb,
                   5U> led0;
  }
}
