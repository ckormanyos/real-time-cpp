///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2020 - 2022.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_PWM_TIMER1_2020_04_12_H
  #define MCAL_PWM_TIMER1_2020_04_12_H

  #include <algorithm>
  #include <cstdint>

  #include <mcal_pwm/mcal_pwm_base.h>
  #include <mcal_reg.h>

  namespace mcal { namespace pwm {

  class pwm_timer1 : public pwm_base
  {
  private:
    using base_class_type = pwm_base;

  public:
    pwm_timer1() = default;

    ~pwm_timer1() override = default;

    auto init() noexcept -> bool override
    {
      // Set portb.1 to output.
      mcal::reg::reg_access_static<std::uint8_t,
                                   std::uint8_t,
                                   mcal::reg::ddrb,
                                   UINT8_C(1)>::bit_set();

      // Set the pwm top to 1000.
      mcal::reg::reg_access_static<std::uint8_t,
                                   std::uint16_t,
                                   mcal::reg::icr1,
                                   UINT16_C(1000)>::reg_set();

      // Set the pwm duty cycle for channel a.
      mcal::reg::reg_access_static<std::uint8_t,
                                   std::uint16_t,
                                   mcal::reg::ocr1a,
                                   UINT16_C(0x0000)>::reg_set();

      // Set the pwm duty cycle for channel b.
      //mcal::reg::reg_access_static<std::uint8_t,
      //                             std::uint16_t,
      //                             mcal::reg::ocr1b,
      //                             UINT16_C(0x0000)>::reg_set();

      {
        constexpr std::uint8_t wgm11  = UINT8_C(1);
        constexpr std::uint8_t wgm12  = UINT8_C(3);
        constexpr std::uint8_t wgm13  = UINT8_C(4);
        //constexpr std::uint8_t com1b1 = UINT8_C(5);
        constexpr std::uint8_t com1a1 = UINT8_C(7);
        constexpr std::uint8_t cs11   = UINT8_C(1);

        // Set non-inverting mode for channel a.
        mcal::reg::reg_access_static<std::uint8_t,
                                     std::uint8_t,
                                     mcal::reg::tccr1a,
                                     std::uint8_t(1U << com1a1)>::reg_or();

        // Set non-inverting mode for channel b.
        //mcal::reg::reg_access_static<std::uint8_t,
        //                             std::uint8_t,
        //                             mcal::reg::tccr1a,
        //                             std::uint8_t(1U << com1b1)>::reg_or();

        // Set fast pwm mode using icr1 as top.
        mcal::reg::reg_access_static<std::uint8_t,
                                     std::uint8_t,
                                     mcal::reg::tccr1a,
                                     std::uint8_t(1U << wgm11)>::reg_or();

        mcal::reg::reg_access_static<std::uint8_t,
                                     std::uint8_t,
                                     mcal::reg::tccr1b,
                                     std::uint8_t((1U << wgm12) | (1U << wgm13))>::reg_or();

        // Start the timer with prescaler (clock / 8).
        mcal::reg::reg_access_static<std::uint8_t,
                                     std::uint8_t,
                                     mcal::reg::tccr1b,
                                     std::uint8_t(1U << cs11)>::reg_or();
      }

      return true;
    }

    auto set_duty(const std::uint16_t duty_cycle) noexcept -> void override
    {
      // Set the duty cycle 0...1000.

      base_class_type::set_duty((std::min)(duty_cycle, static_cast<std::uint16_t>(UINT16_C(1000))));

      mcal::reg::reg_access_dynamic<std::uint8_t,
                                    std::uint16_t>::reg_set(mcal::reg::ocr1a,
                                                            base_class_type::get_duty());
    }
  };

  } // namespace pwm
  } // namespace mcal

#endif // MCAL_PWM_TIMER1_2020_04_12_H
