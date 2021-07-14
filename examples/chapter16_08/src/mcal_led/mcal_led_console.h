///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2013 - 2021.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_LED_CONSOLE_2020_04_23_H_
  #define MCAL_LED_CONSOLE_2020_04_23_H_

  #include <cstdint>
  #include <iostream>

  #include <mcal_led/mcal_led_boolean_state_base.h>

  namespace mcal { namespace led {

  class led_console final : public mcal::led::led_boolean_state_base
  {
  public:
    explicit led_console(const std::uint_fast8_t i)
      : my_index(i) { }

    virtual ~led_console() = default;

  private:
    const std::uint_fast8_t my_index;

    virtual void toggle()
    {
      led_boolean_state_base::toggle();

      // Print the LED state.
      std::cout << "LED"
                << unsigned(my_index)
                << " is "
                << (led_boolean_state_base::state_is_on() ? "on" : "off")
                << std::endl;
    }
  };

  } } // namespace mcal::led

#endif // MCAL_LED_CONSOLE_2020_04_23_H_
