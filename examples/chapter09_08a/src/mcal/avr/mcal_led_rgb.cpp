///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2023.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_led_rgb.h>
#include <mcal_led_rgb_ws2812.h>
#include <mcal_reg.h>

mcal::led::led_rgb_base& mcal::led::led_rgb0()
{
  using led_rgb0_type =
    mcal::led::led_rgb_ws2812<mcal::reg::portd,
                              static_cast<std::uint8_t>(UINT8_C(3)),
                              static_cast<unsigned>(UINT8_C(8))>;

  static led_rgb0_type the_rgb_led;

  return the_rgb_led;
}
