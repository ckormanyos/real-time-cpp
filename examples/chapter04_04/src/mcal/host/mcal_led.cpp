///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_led.h>
#include <mcal_led/mcal_led_console.h>

mcal::led::led_base* mcal::led::led0()
{
  static mcal::led::led_console l0(0U);

  return &l0;
}

mcal::led::led_base* mcal::led::led1()
{
  static mcal::led::led_console l1(1U);

  return &l1;
}

mcal::led::led_base* mcal::led::led2()
{
  static mcal::led::led_console l2(2U);

  return &l2;
}

mcal::led::led_base* mcal::led::led3()
{
  static mcal::led::led_console l3(3U);

  return &l3;
}

mcal::led::led_base* mcal::led::led4()
{
  static mcal::led::led_console l4(4U);

  return &l4;
}
