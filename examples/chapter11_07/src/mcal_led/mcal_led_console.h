///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2013 - 2024.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_LED_CONSOLE_2020_04_23_H
  #define MCAL_LED_CONSOLE_2020_04_23_H

  #include <mcal_led/mcal_led_boolean_state_base.h>

  #include <cstdint>
  #include <iostream>

  namespace mcal { namespace led {

  class led_console final : public mcal::led::led_boolean_state_base // NOLINT(cppcoreguidelines-special-member-functions,hicpp-special-member-functions)
  {
  public:
    explicit constexpr led_console(const std::uint_fast8_t idx = std::uint_fast8_t { UINT8_C(0) })
      : my_index(idx) { }

    ~led_console() override = default;

    auto toggle() -> void override
    {
      using base_class_type = mcal::led::led_boolean_state_base;

      base_class_type::toggle();

      // Print the LED state to the console.
      std::cout << "LED"
                << static_cast<unsigned>(my_index)
                << " is "
                << (base_class_type::state_is_on() ? "on" : "off")
                << std::endl;
    }

  private:
    const std::uint_fast8_t my_index { };
  };

  } // namespace led
  } // namespace mcal

#endif // MCAL_LED_CONSOLE_2020_04_23_H
