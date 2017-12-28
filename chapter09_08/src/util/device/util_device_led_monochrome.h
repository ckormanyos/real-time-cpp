///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2018.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef UTIL_DEVICE_LED_MONOCHROME_2017_11_18_H_
  #define UTIL_DEVICE_LED_MONOCHROME_2017_11_18_H_

  #include <cstdint>

  #include <util/device/util_device_led_base.h>


  namespace util
  {
    namespace device
    {
      class led_monochrome : public led_base
      {
      public:
        virtual ~led_monochrome() { }

      protected:
        led_monochrome() { }
      };
    }
  }

#endif // UTIL_DEVICE_LED_MONOCHROME_2017_11_18_H_
