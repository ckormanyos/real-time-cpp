///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_led.h>
#include <mcal_led/mcal_led_port.h>

auto mcal::led::led0() -> mcal::led::led_base&
{
  using led0_port_type = mcal::port::port_pin<unsigned { UINT8_C(3) }>;

  using led0_led_type = mcal::led::led_port<led0_port_type>;

  static led0_led_type l0;

  return l0;
}
