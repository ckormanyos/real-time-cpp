///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2023.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_led_rgb.h>
#include <mcal_led_rgb_ws2812.h>
#include <mcal_reg.h>

auto mcal::led::led_rgb0() -> led_rgb_base&
{
  using led_rgb0_port_pin_type = mcal::port::port_pin<std::uint32_t,
                                                       std::uint32_t,
                                                       mcal::reg::gpiob_odr,
                                                       static_cast<std::uint32_t>(UINT32_C(9))>;

  using led_rgb0_type = led_rgb_ws2812<led_rgb0_port_pin_type>;

  static led_rgb0_type the_rgb_led;

  return the_rgb_led;
}
