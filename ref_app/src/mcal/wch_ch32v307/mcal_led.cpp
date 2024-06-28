///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2022 - 2024.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_led.h>
#include <mcal_port.h>
#include <mcal_led/mcal_led_port_inverted.h>

mcal::led::led_base& mcal::led::led0()
{
  // Use portc.0 on the WCH board (with manual wire-connection to LED1 (blue).

  using led0_port_type = mcal::port::port_pin<std::uint32_t,
                                              std::uint32_t,
                                              mcal::reg::gpioc_base,
                                              UINT32_C(0)>;

  using led0_led_type = mcal::led::led_port_inverted<led0_port_type>;

  static led0_led_type l0;

  return l0;
}
