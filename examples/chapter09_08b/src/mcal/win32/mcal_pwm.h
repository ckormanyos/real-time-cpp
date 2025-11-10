///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_PWM_2010_09_14_H
  #define MCAL_PWM_2010_09_14_H

  #include <mcal_pwm/mcal_pwm_base.h>

  namespace mcal
  {
    namespace pwm
    {
      using config_type = void;

      inline auto init(const config_type*) -> void { }

      auto pwm0() noexcept -> mcal::pwm::pwm_base&;
    } // namespace pwm
  } // namespace mcal

#endif // MCAL_PWM_2010_09_14_H
