///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2013 - 2025.
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
      my_pwm.set_duty(mcal::pwm::pwm_base::duty_type { UINT8_C(0) });
    }

    ~led_pwm() override = default;

    auto state_is_on() const noexcept -> bool override { return (my_pwm.get_duty() > static_cast<std::uint16_t>(UINT8_C(0))); }

    auto toggle() -> void override
    {
      // Toggle the duty cycle.
      const auto new_duty =
        static_cast<mcal::pwm::pwm_base::duty_type>
        (
          state_is_on() ? UINT16_C(0) : UINT16_C(1000)
        );

      my_pwm.set_duty(new_duty);
    }

  private:
    mcal::pwm::pwm_base& my_pwm;
  };

  } // namespace led
  } // namespace mcal

#endif // MCAL_LED_PWM_2020_04_23_H
