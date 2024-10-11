///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2013 - 2024.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_LED_PORT_2020_04_23_H
  #define MCAL_LED_PORT_2020_04_23_H

  #include <mcal_led/mcal_led_boolean_state_base.h>
  #include <mcal_port.h>

  namespace mcal { namespace led {

  template<typename port_type>
  class led_port : public mcal::led::led_boolean_state_base
  {
  public:
    led_port()
    {
      port_type::set_pin_low();
      port_type::set_direction_output();
    }

    ~led_port() override = default;

    auto toggle() -> void override
    {
      using base_class_type = led_boolean_state_base;

      port_type::toggle_pin();

      base_class_type::toggle();
    }
  };

  } // namespace led
  } // namespace mcal

#endif // MCAL_LED_PORT_2020_04_23_H
