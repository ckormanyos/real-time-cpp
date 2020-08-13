///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2013 - 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_LED_PWM_2020_04_23_H_
  #define MCAL_LED_PWM_2020_04_23_H_

  #include <mcal_led/mcal_led_base.h>
  #include <mcal_pwm/mcal_pwm_base.h>

  namespace mcal { namespace led {

  class led_pwm : public mcal::led::led_base
  {
  public:
    led_pwm(mcal::pwm::pwm_base& pwm) : my_pwm(pwm)
    {
      my_pwm.set_duty(0U);
    }

    virtual ~led_pwm() = default;

    virtual bool state_is_on() const { return (my_pwm.get_duty() > 0U); }

  private:
    mcal::pwm::pwm_base& my_pwm;

    virtual void toggle()
    {
      // Toggle the duty cycle.
      const std::uint16_t new_duty = ((my_pwm.get_duty() > 0U) ? 0U : 1000U);

      my_pwm.set_duty(new_duty);
    }
  };

  } } // namespace mcal::led

#endif // MCAL_LED_PWM_2020_04_23_H_
