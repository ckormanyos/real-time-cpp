///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_led.h>
#include <mcal_led/mcal_led_dummy.h>

mcal::led::led_base& mcal::led::led0()
{
  // The user LED on the stm32f446 Nucleo-64 board:
  // - porta.5: green

  using led0_led_type = mcal::led::led_dummy;

  static led0_led_type l0;

  return l0;
}
