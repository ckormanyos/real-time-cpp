///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2022.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <Port.h>

#include <mcal_led.h>
#include <mcal_led/mcal_led_port.h>

auto mcal::led::led_wch_temporary::toggle() -> void
{
  GPIOC->OUTDR.bit.ODR0 ^= 1u;

  base_class_type::toggle();
}

mcal::led::led_base& mcal::led::led0()
{
  using led0_led_type = led_wch_temporary;

  static led0_led_type local_led0;

  return local_led0;
}
