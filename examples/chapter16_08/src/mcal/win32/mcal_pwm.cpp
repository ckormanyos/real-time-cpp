///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2022.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_pwm.h>
#include <mcal_pwm_software.h>

mcal::pwm::pwm_base& mcal::pwm::pwm0() noexcept
{
  static mcal::pwm::pwm_software pwm;

  static const volatile bool init_is_ok = pwm.init();

  static_cast<void>(init_is_ok);

  return pwm;
}
