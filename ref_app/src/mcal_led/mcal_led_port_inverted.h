///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2020 - 2024.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_LED_PORT_INVERTED_2020_08_02_H
  #define MCAL_LED_PORT_INVERTED_2020_08_02_H

  #include <mcal_led/mcal_led_boolean_state_base.h>
  #include <mcal_port.h>

  namespace mcal { namespace led {

  template<typename port_type>
  class led_port_inverted : public mcal::led::led_boolean_state_base
  {
  public:
    led_port_inverted()
    {
      port_type::set_pin_high();
      port_type::set_direction_output();
    }

    ~led_port_inverted() override = default;

    auto toggle() -> void override
    {
      using base_class_type = led_boolean_state_base;

      port_type::toggle_pin();

      base_class_type::toggle();
    }
  };

  } // namespace led
  } // namespace mcal

#endif // MCAL_LED_PORT_INVERTED_2020_08_02_H
