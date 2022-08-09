///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2022.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_led.h>
#include <mcal_led/mcal_led_port.h>

mcal::led::led_base& mcal::led::led0()
{
  // The 1st user-LED on the STM32H7A3xxQ board is:
  // - portb.0: green

  using led0_port_type = mcal::port::port_pin<std::uint32_t,
                                              std::uint32_t,
                                              mcal::reg::gpiob_base,
                                              UINT32_C(0)>;

  using led0_led_type = mcal::led::led_port<led0_port_type>;

  static led0_led_type l0;

  return l0;
}
