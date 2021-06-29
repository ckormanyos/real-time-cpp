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
  #include <functional>

  #include <mcal_lcd/mcal_lcd_base.h>
  #include <mcal_pwm/mcal_pwm_base.h>

  namespace mcal { namespace pwm {

  class pwm_lcd : public mcal::pwm::pwm_base
  {
  private:
    using base_class_type = mcal::pwm::pwm_base;

  public:
    pwm_lcd(mcal::lcd::lcd_base& lcd_ref) : my_lcd_ref(lcd_ref)
    {
      static_cast<void>(my_lcd_ref.get().init());

      base_class_type::my_duty_cycle = UINT16_C(1000);
    }

    virtual ~pwm_lcd() = default;

    virtual bool init() noexcept
    {
      return true;
    }

    virtual void set_duty(const std::uint16_t duty_cycle) noexcept
    {
      base_class_type::my_duty_cycle = (std::min)(duty_cycle, std::uint16_t(UINT16_C(1000)));

      // Write the duty cycle as percent.
      char pstr_lcd_line0[6U];

      std::uint16_t u = base_class_type::my_duty_cycle;

      std::uint16_t hundreds = u / 1000U; u -= (hundreds * 1000U);
      std::uint16_t tens     = u /  100U; u -= (tens     *  100U);
      std::uint16_t ones     = u /   10U; u -= (ones     *   10U);
      std::uint16_t tenths   = u;

      pstr_lcd_line0[0U] = char(std::uint8_t((hundreds != 0U) ? hundreds + 0x30U : std::uint8_t('0')));
      pstr_lcd_line0[1U] = char(std::uint8_t((tens     != 0U) ? tens     + 0x30U : std::uint8_t('0')));
      pstr_lcd_line0[2U] = char(std::uint8_t(                   ones     + 0x30U));
      pstr_lcd_line0[3U] = char(std::uint8_t('.'));
      pstr_lcd_line0[4U] = char(std::uint8_t(                   tenths   + 0x30U));
      pstr_lcd_line0[5U] = char(std::uint8_t('%'));

      my_lcd_ref.get().write_n(pstr_lcd_line0, 6U, 0U, false);
    }

  private:
    std::reference_wrapper<mcal::lcd::lcd_base> my_lcd_ref;
  };

  } }

#endif // MCAL_PWM_LCD_2020_05_04_H_
