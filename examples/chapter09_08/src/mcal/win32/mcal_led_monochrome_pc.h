///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2018.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_LED_MONOCHROME_PC_2017_11_12_H_
  #define MCAL_LED_MONOCHROME_PC_2017_11_12_H_

  #include <cstdint>

  #include <util/device/util_device_led_monochrome.h>

  namespace mcal
  {
    namespace led
    {
      class led_monochrome_pc final : public util::device::led_monochrome
      {
      public:
        led_monochrome_pc() { }

        virtual ~led_monochrome_pc() { }

        virtual void my_on ();
        virtual void my_off();
      };
    }
  }

#endif // MCAL_LED_MONOCHROME_PC_2017_11_12_H_
