///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_LED_PORT_2020_04_23_H_
  #define MCAL_LED_PORT_2020_04_23_H_

  #include <mcal_led/mcal_led_base.h>
  #include <mcal_port.h>

  namespace mcal { namespace led {

  template<typename port_type>
  class led_port : public mcal::led::led_base
  {
  public:
    led_port() : is_on(false)
    {
      port_type::set_pin_low();
      port_type::set_direction_output();
    }

    virtual ~led_port() = default;

    virtual void toggle()
    {
      // Toggle the LED state.
      is_on = (!is_on);

      port_type::toggle_pin();
    }

    virtual bool state_is_on() const { return is_on; }

  private:
    bool is_on;
  };

  } } // namespace mcal::led

#endif // MCAL_LED_PORT_2020_04_23_H_
