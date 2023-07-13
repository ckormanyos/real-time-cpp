///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2013 - 2022.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_LED_PWM_2020_04_23_H
  #define MCAL_LED_PWM_2020_04_23_H

  #include <mcal_led/mcal_led_base.h>
  #include <mcal_pwm/mcal_pwm_base.h>

  namespace mcal { namespace led {

  class led_pwm : public mcal::led::led_base
  {
  public:
    explicit led_pwm(mcal::pwm::pwm_base& pwm) : my_pwm(pwm)
    {
      my_pwm.set_duty(0U);
    }

    ~led_pwm() override = default;

    auto state_is_on() const -> bool override { return (my_pwm.get_duty() > 0U); }

  private:
    mcal::pwm::pwm_base& my_pwm;

    auto toggle() -> void override
    {
      // Toggle the duty cycle.
      const std::uint16_t new_duty = ((my_pwm.get_duty() > 0U) ? 0U : 1000U);

      my_pwm.set_duty(new_duty);
    }
  };

  } } // namespace mcal::led

#endif // MCAL_LED_PWM_2020_04_23_H
