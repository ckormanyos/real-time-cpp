///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_led_rgb_board.h>
#include <mcal_pwm.h>

auto mcal::led::led_rgb_board::apply_color() -> void
{
  const uint_fast8_t my_r = uint_fast8_t(uint_fast16_t(uint_fast16_t(255U - get_hue_r()) * 100U) / 255U);
  const uint_fast8_t my_g = uint_fast8_t(uint_fast16_t(uint_fast16_t(255U - get_hue_g()) * 100U) / 255U);
  const uint_fast8_t my_b = uint_fast8_t(uint_fast16_t(uint_fast16_t(255U - get_hue_b()) * 100U) / 255U);

  mcal::pwm::mcal_pwm0().set_duty(my_r);
  mcal::pwm::mcal_pwm1().set_duty(my_g);
  mcal::pwm::mcal_pwm2().set_duty(my_b);
}
