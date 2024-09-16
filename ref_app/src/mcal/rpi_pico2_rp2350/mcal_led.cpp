///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2024.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <Gpio.h>

#include <mcal_led.h>
#include <mcal_led/mcal_led_boolean_state_base.h>

namespace mcal { namespace led {

class led_port_green_25 : public mcal::led::led_boolean_state_base
{
private:
  using base_class_type = mcal::led::led_boolean_state_base;

public:
  led_port_green_25()
  {
    LED_GREEN_CFG();
  }

  auto toggle() -> void override
  {
    LED_GREEN_TOGGLE();

    base_class_type::toggle();
  }
};

} // namespace led
} // namespace mcal

mcal::led::led_base& mcal::led::led0()
{
  using led0_led_type = mcal::led::led_port_green_25;

  static led0_led_type l0;

  return l0;
}
