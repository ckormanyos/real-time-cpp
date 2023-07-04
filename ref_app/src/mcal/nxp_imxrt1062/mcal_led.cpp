///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2023.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_led/mcal_led_port.h>
#include <mcal_led.h>
#include <mcal_port.h>
#include <mcal_reg.h>

mcal::led::led_base& mcal::led::led0()
{
  // The user LED on the stm32f446 Nucleo-64 board:
  // - portb.3: orange

  using led0_port_type = mcal::port::port_pin<std::uint32_t,
                                              std::uint32_t,
                                              mcal::reg::gpio_02_base_address,
                                              static_cast<std::uint32_t>(UINT8_C(3))>;

  using led0_led_type = mcal::led::led_port<led0_port_type>;

  static led0_led_type l0;

  return l0;
}
