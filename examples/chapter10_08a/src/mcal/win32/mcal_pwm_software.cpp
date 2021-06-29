///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <iomanip>
#include <iostream>
#include <sstream>

#include <mcal_pwm_software.h>

void mcal::pwm::pwm_software::set_duty(const std::uint16_t duty_cycle) noexcept
{
  base_class_type::my_duty_cycle = duty_cycle;

  const float duty_cycle_as_percent = float(duty_cycle) / 10.0F;

  std::stringstream strm;

  strm << "duty cycle: "
       << std::fixed
       << std::setprecision(1)
       << duty_cycle_as_percent
       << "%";

  std::cout << strm.str() + (std::string(2U, ' ') + "\r");
}
