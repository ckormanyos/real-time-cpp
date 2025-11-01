///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2024.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_LED_2010_09_14_H
  #define MCAL_LED_2010_09_14_H

  #include <mcal_led/mcal_led_base.h>

  #include <cstdint>

  namespace mcal
  {
    namespace led
    {
      constexpr unsigned LED_ID_1 { UINT8_C(6) };
      constexpr unsigned LED_ID_2 { UINT8_C(5) };
      constexpr unsigned LED_ID_3 { UINT8_C(4) };
      constexpr unsigned LED_ID_4 { UINT8_C(3) };

      auto led0() -> led_base&;
      auto led1() -> led_base&;
      auto led2() -> led_base&;
      auto led3() -> led_base&;
    }
  }

#endif // MCAL_LED_2010_09_14_H
