///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2013 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_LED_CONSOLE_2020_04_23_H
  #define MCAL_LED_CONSOLE_2020_04_23_H

  #include <mcal_led/mcal_led_boolean_state_base.h>

  #include <atomic>
  #include <cstdint>
  #include <iostream>
  #include <sstream>

  namespace mcal { namespace led {

  class led_console final : public mcal::led::led_boolean_state_base // NOLINT(cppcoreguidelines-special-member-functions,hicpp-special-member-functions)
  {
  public:
    explicit constexpr led_console(const std::uint_fast8_t idx = std::uint_fast8_t { UINT8_C(0) }) noexcept
      : my_index(idx) { }

    ~led_console() override = default;

    auto toggle() -> void override
    {
      using base_class_type = mcal::led::led_boolean_state_base;

      base_class_type::toggle();

      // Print the LED state to the console.
      std::stringstream strm { };

      strm << "LED"
           << static_cast<unsigned>(my_index)
           << " is "
           << (base_class_type::state_is_on() ? "on" : "off");

      console_sync().test_and_set();
      std::cout << strm.str() << std::endl;
      console_sync().clear();
    }

  private:
    const std::uint_fast8_t my_index { };

    static auto console_sync() -> std::atomic_flag&
    {
      static std::atomic_flag console_lock { };

      return console_lock;
    }
  };

  } // namespace led
  } // namespace mcal

#endif // MCAL_LED_CONSOLE_2020_04_23_H
