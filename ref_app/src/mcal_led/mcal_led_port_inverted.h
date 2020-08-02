///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_LED_PORT_INVERTED_2020_08_02_H_
  #define MCAL_LED_PORT_INVERTED_2020_08_02_H_

  #include <mcal_led/mcal_led_base.h>
  #include <mcal_port.h>

  namespace mcal { namespace led {

  template<typename port_type>
  class led_port_inverted : public mcal::led::led_base
  {
  public:
    led_port_inverted() : is_on(false)
    {
      port_type::set_pin_high();
      port_type::set_direction_output();
    }

    virtual ~led_port_inverted() = default;

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

#endif // MCAL_LED_PORT_INVERTED_2020_08_02_H_
