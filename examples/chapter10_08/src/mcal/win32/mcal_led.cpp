///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_led.h>
#include <iostream>

const mcal::led::led_type& mcal::led::led0()
{
  static mcal::led::led l0;

  return l0;
}

void mcal::led::led::toggle() const
{
  // Toggle the LED state.
  is_on = (!is_on);

  std::cout << std::string(32U, ' ') + "\r";

  // Print the LED state.
  if(is_on)
  {
    std::cout << "LED is on" << std::endl;
  }
  else
  {
    std::cout << "LED is off" << std::endl;
  }
}
