///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2023.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal/mcal_led_rgb.h>
#include <mcal_reg.h>
#include <mcal_led_rgb_board_ws2812.h>

util::device::led_rgb& mcal::led::led_rgb0()
{
  using led_rgb0_type = mcal::led::led_rgb_board<mcal::reg::portd, UINT8_C(3)>;

  static led_rgb0_type the_rgb_led;

  return the_rgb_led;
}
