///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2023.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_led_rgb.h>
#include <mcal_led_rgb_pc.h>

mcal::led::led_rgb_base& mcal::led::led_rgb0()
{
  static mcal::led::led_rgb_pc the_led;

  return the_led;
}
