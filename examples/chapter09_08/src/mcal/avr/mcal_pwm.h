///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_PWM_2018_01_08_H
  #define MCAL_PWM_2018_01_08_H

  #include <mcal/mcal_pwm_base.h>

  namespace mcal
  {
    namespace pwm
    {
      auto mcal_pwm0() -> pwm_base&;
      auto mcal_pwm1() -> pwm_base&;
      auto mcal_pwm2() -> pwm_base&;
    }
  }

#endif // MCAL_PWM_2018_01_08_H
