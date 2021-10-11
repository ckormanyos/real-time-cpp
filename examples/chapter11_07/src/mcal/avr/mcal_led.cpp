///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2021.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_led.h>
#include <mcal_led/mcal_led_port.h>

mcal::led::led_base& mcal::led::led0()
{
  using led0_port_type = mcal::port::port_pin<std::uint8_t,
                                              std::uint8_t,
                                              mcal::reg::portb,
                                              UINT8_C(5)>;

  using led0_led_type = mcal::led::led_port<led0_port_type>;

  static led0_led_type l0;

  return l0;
}

mcal::led::led_base& mcal::led::led1()
{
  using led1_port_type = mcal::port::port_pin<std::uint8_t,
                                              std::uint8_t,
                                              mcal::reg::portd,
                                              UINT8_C(3)>;

  using led1_led_type = mcal::led::led_port<led1_port_type>;

  static led1_led_type l1;

  return l1;
}
