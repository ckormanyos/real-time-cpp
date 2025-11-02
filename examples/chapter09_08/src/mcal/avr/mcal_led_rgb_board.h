///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_LED_RGB_BOARD_2017_11_12_H
  #define MCAL_LED_RGB_BOARD_2017_11_12_H

  #include <mcal_pwm.h>
  #include <util/device/util_device_led_rgb.h>

  #include <cstdint>

  namespace mcal { namespace led {

  // The RGB LED on the board is controlled with 3 digital PWM signals.

  class led_rgb_board final : public util::device::led_rgb
  {
  public:
    led_rgb_board() = default;

    ~led_rgb_board() override = default;

  private:
    auto apply_color() -> void override;
  };

  } } // namespace mcal::led

#endif // MCAL_LED_RGB_BOARD_2017_11_12_H
