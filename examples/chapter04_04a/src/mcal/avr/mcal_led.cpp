///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2024.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_led.h>
#include <mcal_led/mcal_led_port.h>
#include <mcal_led/mcal_led_pwm.h>
#include <mcal_port.h>
#include <mcal_pwm.h>
#include <mcal_spi.h>

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
  using led1_led_type = mcal::led::led_pwm;

  static led1_led_type l1(mcal::pwm::pwm0());

  return l1;
}

mcal::led::led_base& mcal::led::led2()
{
  using led2_port_type = mcal::port::port_pin_expander<0U>;
  using led2_led_type  = mcal::led::led_port<led2_port_type>;

  static led2_led_type l2;

  return l2;
}

mcal::led::led_base& mcal::led::led3()
{
  using led3_port_type = mcal::port::port_pin_expander<1U>;
  using led3_led_type  = mcal::led::led_port<led3_port_type>;

  static led3_led_type l3;

  return l3;
}

mcal::led::led_base& mcal::led::led4()
{
  using led4_port_type = mcal::port::port_pin_expander<2U>;
  using led4_led_type  = mcal::led::led_port<led4_port_type>;

  static led4_led_type l4;

  return l4;
}
