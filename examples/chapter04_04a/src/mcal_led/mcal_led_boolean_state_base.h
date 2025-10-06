///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2020 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_LED_BOOLEAN_STATE_BASE_2020_08_07_H
  #define MCAL_LED_BOOLEAN_STATE_BASE_2020_08_07_H

  #include <mcal_led/mcal_led_base.h>

  namespace mcal { namespace led {

  class led_boolean_state_base : public mcal::led::led_base // NOLINT(cppcoreguidelines-special-member-functions,hicpp-special-member-functions)
  {
  public:
    ~led_boolean_state_base() override = default;

    auto state_is_on() const noexcept -> bool override { return is_on; }

  protected:
    constexpr led_boolean_state_base() = default;

    auto toggle() -> void override
    {
      // Toggle the LED state.
      set_is_on(!is_on);
    }

    auto set_is_on(const bool val) noexcept -> void { is_on = val; }

  private:
    bool is_on { };
  };

  } // namespace led
  } // namespace mcal

#endif // MCAL_LED_BOOLEAN_STATE_BASE_2020_08_07_H
