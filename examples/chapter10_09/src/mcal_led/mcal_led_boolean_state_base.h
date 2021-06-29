///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_LED_BOOLEAN_STATE_BASE_2020_08_07_H_
  #define MCAL_LED_BOOLEAN_STATE_BASE_2020_08_07_H_

  #include <mcal_led/mcal_led_base.h>

  namespace mcal { namespace led {

  class led_boolean_state_base : public mcal::led::led_base
  {
  public:
    virtual ~led_boolean_state_base() = default;

  protected:
    led_boolean_state_base() : is_on(false) { }

    virtual void toggle()
    {
      // Toggle the LED state.
      is_on = (!is_on);
    }

    virtual bool state_is_on() const { return is_on; }

  private:
    bool is_on;
  };

  } } // namespace mcal::led

#endif // MCAL_LED_BOOLEAN_STATE_BASE_2020_08_07_H_
