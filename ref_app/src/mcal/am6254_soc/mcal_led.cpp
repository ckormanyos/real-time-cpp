///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_led.h>
#include <mcal_led/mcal_led_port.h>
#include <mcal_port.h>
#include <mcal_reg.h>

auto mcal::led::led0() -> mcal::led::led_base&
{
  using led0_port_type = mcal::port::port_pin<mcal::reg::gpio0, mcal::led::LED_1>;

  using led0_led_type = led_port<led0_port_type>;

  static led0_led_type l0;

  return l0;
}

auto mcal::led::led1() -> mcal::led::led_base&
{
  using led1_port_type = mcal::port::port_pin<mcal::reg::gpio0, mcal::led::LED_2>;

  using led1_led_type = led_port<led1_port_type>;

  static led1_led_type l1;

  return l1;
}

auto mcal::led::led2() -> mcal::led::led_base&
{
  using led2_port_type = mcal::port::port_pin<mcal::reg::gpio0, mcal::led::LED_3>;

  using led2_led_type = led_port<led2_port_type>;

  static led2_led_type l2;

  return l2;
}

auto mcal::led::led3() -> mcal::led::led_base&
{
  using led3_port_type = mcal::port::port_pin<mcal::reg::gpio0, mcal::led::LED_4>;

  using led3_led_type = led_port<led3_port_type>;

  static led3_led_type l3;

  return l3;
}
