///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_PWM_LCD_2020_05_04_H_
  #define MCAL_PWM_LCD_2020_05_04_H_

  #include <algorithm>
  #include <cstdint>

  #include <mcal_pwm/mcal_pwm_base.h>

  namespace mcal { namespace pwm {

  class pwm_lcd : public mcal::pwm::pwm_base
  {
  private:
    using base_class_type = mcal::pwm::pwm_base;

  public:
    pwm_lcd()
    {
      base_class_type::set_duty(static_cast<std::uint16_t>(UINT16_C(1000));
    }

    virtual ~pwm_lcd() = default;

    virtual bool init() noexcept
    {
      return true;
    }

    virtual void set_duty(const std::uint16_t duty_cycle) noexcept;
  };

  } }

#endif // MCAL_PWM_LCD_2020_05_04_H_
