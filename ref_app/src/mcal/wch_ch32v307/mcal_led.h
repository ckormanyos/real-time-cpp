///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2024.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_LED_2022_12_16_H_
  #define MCAL_LED_2022_12_16_H_

  #include <mcal_led/mcal_led_boolean_state_base.h>

  namespace mcal
  {
    namespace led
    {
      class led_wch_temporary : public led_boolean_state_base
      {
      private:
        using base_class_type = led_boolean_state_base;

      public:
        led_wch_temporary();

        ~led_wch_temporary() override = default;

        auto toggle() -> void override;
      };

      led_base& led0();
    }
  }

#endif // MCAL_LED_2022_12_16_H_
