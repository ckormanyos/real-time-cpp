///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2024.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <Gpio/Gpio.h>

#include <mcal_led.h>
#include <mcal_led/mcal_led_boolean_state_base.h>

namespace mcal
{
  namespace led
  {
    class led_rp2040_green : public mcal::led::led_boolean_state_base
    {
      public:
        led_rp2040_green()
        {
          LED_GREEN_OFF();
          LED_GREEN_CFG();
        }

      ~led_rp2040_green() override = default;

        auto toggle() -> void override
        {
          using base_class_type = led_boolean_state_base;

          LED_GREEN_TOGGLE();

          base_class_type::toggle();
        }
    };
  }
}

mcal::led::led_base& mcal::led::led0()
{
  using led0_led_type = mcal::led::led_rp2040_green;

  static led0_led_type l0;

  return l0;
}
