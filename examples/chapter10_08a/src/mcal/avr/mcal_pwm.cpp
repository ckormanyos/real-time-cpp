///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <limits>

#include <mcal_lcd.h>
#include <mcal_pwm.h>
#include <mcal_pwm_lcd.h>

void mcal::pwm::init(const mcal::pwm::config_type*)
{
  mcal::pwm::pwm0().set_duty(0U);
}

mcal::pwm::pwm_base& mcal::pwm::pwm0() noexcept
{
  static mcal::pwm::pwm_lcd p0(mcal::lcd::lcd0());

  return p0;
}
