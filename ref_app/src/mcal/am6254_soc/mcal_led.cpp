///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_led.h>
#include <mcal_led_am6254_soc.h>

auto mcal::led::led0() -> mcal::led::led_base&
{
  using led0_led_type = led_am6254_soc<LED_1>;

  static led0_led_type l0;

  return l0;
}
