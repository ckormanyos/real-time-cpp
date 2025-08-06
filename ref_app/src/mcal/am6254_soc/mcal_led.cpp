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
  using local_led_port_type = mcal::port::port_pin<mcal::reg::gpio0, mcal::led::LED_ID_1>;

  using local_led_type = led_port<local_led_port_type>;

  static local_led_type led_instance;

  return led_instance;
}

auto mcal::led::led1() -> mcal::led::led_base&
{
  using local_led_port_type = mcal::port::port_pin<mcal::reg::gpio0, mcal::led::LED_ID_2>;

  using local_led_type = led_port<local_led_port_type>;

  static local_led_type led_instance;

  return led_instance;
}

auto mcal::led::led2() -> mcal::led::led_base&
{
  using local_led_port_type = mcal::port::port_pin<mcal::reg::gpio0, mcal::led::LED_ID_3>;

  using local_led_type = led_port<local_led_port_type>;

  static local_led_type led_instance;

  return led_instance;
}

auto mcal::led::led3() -> mcal::led::led_base&
{
  using local_led_port_type = mcal::port::port_pin<mcal::reg::gpio0, mcal::led::LED_ID_4>;

  using local_led_type = led_port<local_led_port_type>;

  static local_led_type led_instance;

  return led_instance;
}
