///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2018.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_LED_RGB_PC_2017_11_20_H_
  #define MCAL_LED_RGB_PC_2017_11_20_H_

  #include <cstdint>

  #include <mcal_led/mcal_led_rgb_base.h>

  namespace mcal
  {
    namespace led
    {
      class led_rgb_pc final : public mcal::led::led_rgb_base
      {
      public:
        constexpr led_rgb_pc() = default;

      private:
        auto apply_color() -> void override;
      };
    }
  }


#endif // MCAL_LED_RGB_PC_2017_11_20_H_
