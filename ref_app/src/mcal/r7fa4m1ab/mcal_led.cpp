///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2026.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "R7FA4M1AB.h"

#include <mcal_led.h>
#include <mcal_led/mcal_led_port.h>

class led_minima_blinky : public mcal::led::led_boolean_state_base
{
public:
  led_minima_blinky()
  {
    /* configure pin P111 as output */
    /* disable register write protection for PFS*/
    PMISC->PWPR.bit.B0WI  = 0;
    PMISC->PWPR.bit.PFSWE = 1;

    /* output low */
    PFS->P111PFS.bit.PODR = 0;

    /* configure the pin as output */
    PFS->P111PFS.bit.PDR  = 1;
  }

  ~led_minima_blinky() override = default;

  auto toggle() noexcept -> void override
  {
    using base_class_type = led_boolean_state_base;

    // Toggle the LED.
    PFS->P111PFS.bit.PODR ^= 1;

    base_class_type::toggle();
  }
};

mcal::led::led_base& mcal::led::led0()
{
  using led0_led_type = led_minima_blinky;

  static led0_led_type l0;

  return l0;
}
