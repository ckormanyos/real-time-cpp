///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2020 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_PWM_DUMMY_2020_04_29_H
  #define MCAL_PWM_DUMMY_2020_04_29_H

  #include <mcal_pwm/mcal_pwm_base.h>

  namespace mcal { namespace pwm {

  class pwm_dummy : public mcal::pwm::pwm_base
  {
  private:
    using base_class_type = mcal::pwm::pwm_base;

  public:
    pwm_dummy() = default;

    auto init() noexcept -> bool override { return true; }

    auto set_duty(const std::uint16_t duty_cycle) noexcept -> void override
    {
      base_class_type::set_duty(duty_cycle);
    }

    ~pwm_dummy() override = default;
  };

  } // namespace pwm
  } // namespace mcal

#endif // MCAL_PWM_DUMMY_2020_04_29_H
