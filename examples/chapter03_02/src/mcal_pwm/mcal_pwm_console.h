///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_PWM_CONSOLE_2020_04_12_H_
  #define MCAL_PWM_CONSOLE_2020_04_12_H_

  #include <iomanip>
  #include <iostream>
  #include <sstream>

  #include <mcal_pwm/mcal_pwm_base.h>

  namespace mcal { namespace pwm {

  class pwm_console : public mcal::pwm::pwm_base
  {
  private:
    using base_class_type = mcal::pwm::pwm_base;

  public:
    pwm_console() = default;

    virtual bool init() noexcept { return true; }

    virtual void set_duty(const std::uint16_t duty_cycle) noexcept
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

    virtual ~pwm_console() = default;
  };

  } }

#endif // MCAL_PWM_CONSOLE_2020_04_12_H_
