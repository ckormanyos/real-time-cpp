///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2018.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_LED_MONOCHROME_PC_2017_11_12_H_
  #define MCAL_LED_MONOCHROME_PC_2017_11_12_H_

  #include <cstdint>

  #include <mcal_led/mcal_led_boolean_state_base.h>

  extern auto post_message_led_monochrome(const bool is_on) -> void;

  namespace mcal
  {
    namespace led
    {
      class led_monochrome_pc final : public mcal::led::led_boolean_state_base
      {
      private:
        using base_class_type = mcal::led::led_boolean_state_base;

      public:
        led_monochrome_pc() = default;

        ~led_monochrome_pc() override = default;

        auto toggle() -> void override
        {
          // Toggle the LED state.
          (base_class_type::state_is_on() ? my_off() : my_on());

          base_class_type::toggle();
        }

      private:
        void my_on () { post_message_led_monochrome(true); }
        void my_off() { post_message_led_monochrome(false); }
      };
    }
  }

#endif // MCAL_LED_MONOCHROME_PC_2017_11_12_H_
