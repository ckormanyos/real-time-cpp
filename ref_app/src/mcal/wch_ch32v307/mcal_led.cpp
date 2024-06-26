///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2022 - 2024.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_led.h>

#include <CH32V30xxx.h>

mcal::led::led_wch_temporary::led_wch_temporary()
{
  // Inverted: High switches off the LED.
  GPIOC->OUTDR.bit.ODR0 = 1u;
}

auto mcal::led::led_wch_temporary::toggle() -> void
{
  GPIOC->OUTDR.bit.ODR0 ^= 1u;

  base_class_type::toggle();
}

mcal::led::led_base& mcal::led::led0()
{
  using led0_led_type = mcal::led::led_wch_temporary;

  static led0_led_type local_led0;

  return local_led0;
}
