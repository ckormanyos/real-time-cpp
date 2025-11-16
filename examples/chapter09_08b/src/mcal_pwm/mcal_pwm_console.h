///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2020 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_PWM_CONSOLE_2020_04_12_H
  #define MCAL_PWM_CONSOLE_2020_04_12_H

  #include <mcal_pwm/mcal_pwm_base.h>

  #include <iomanip>
  #include <iostream>
  #include <sstream>

  namespace mcal { namespace pwm {

  class pwm_console : public mcal::pwm::pwm_base // NOLINT(cppcoreguidelines-special-member-functions,hicpp-special-member-functions)
  {
  private:
    using base_class_type = mcal::pwm::pwm_base;

  public:
    pwm_console() = default;

    auto init() -> bool override { return true; }

    auto set_duty(const std::uint16_t duty_cycle) -> void override
    {
      base_class_type::set_duty(duty_cycle);

      const auto duty_cycle_as_percent = 
        static_cast<float>
        (
          static_cast<float>(base_class_type::get_duty()) / 10.0F
        );

      std::stringstream strm;

      strm << "duty cycle: "
           << std::fixed
           << std::setprecision(1)
           << duty_cycle_as_percent
           << "%";

      std::cout << strm.str() + (std::string(2U, ' ') + "\r");
    }

    ~pwm_console() override = default;
  };

  } // namespace pwm
  } // namespace mcal

#endif // MCAL_PWM_CONSOLE_2020_04_12_H
