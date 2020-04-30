///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_PWM_DUMMY_2020_04_29_H_
  #define MCAL_PWM_DUMMY_2020_04_29_H_

  #include <mcal_pwm/mcal_pwm_base.h>

  namespace mcal { namespace pwm {

  class pwm_dummy : public mcal::pwm::pwm_base
  {
  private:
    using base_class_type = mcal::pwm::pwm_base;

  public:
    pwm_dummy() = default;

    virtual bool init() noexcept { return true; }

    virtual void set_duty(const std::uint16_t duty_cycle) noexcept
    {
      base_class_type::my_duty_cycle = duty_cycle;
    }

    virtual ~pwm_dummy() = default;
  };

  } }

#endif // MCAL_PWM_DUMMY_2020_04_29_H_
