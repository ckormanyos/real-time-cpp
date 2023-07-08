///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2018.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_LED_RGB_PC_2017_11_20_H_
  #define MCAL_LED_RGB_PC_2017_11_20_H_

  #include <cstdint>

  #include <util/device/util_device_led_rgb.h>

  namespace mcal
  {
    namespace led
    {
      class led_rgb_pc final : public util::device::led_rgb
      {
      public:
        led_rgb_pc() { }

        virtual ~led_rgb_pc() { }

      private:
        virtual void apply_color();
      };
    }
  }


#endif // MCAL_LED_RGB_PC_2017_11_20_H_
