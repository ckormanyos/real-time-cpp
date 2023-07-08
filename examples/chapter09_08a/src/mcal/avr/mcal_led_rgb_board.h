///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2018.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_LED_RGB_BOARD_2017_11_12_H_
  #define MCAL_LED_RGB_BOARD_2017_11_12_H_

  #include <cstdint>

  #include <mcal_pwm.h>
  #include <util/device/util_device_led_rgb.h>

  namespace mcal { namespace led {

  // The RGB LED on the board is controlled with 3 digital PWM signals.

  class led_rgb_board final : public util::device::led_rgb
  {
  public:
    led_rgb_board() { }

    virtual ~led_rgb_board() { }

  private:
    virtual void apply_color();
  };

  } } // namespace mcal::led

#endif // MCAL_LED_RGB_BOARD_2017_11_12_H_
