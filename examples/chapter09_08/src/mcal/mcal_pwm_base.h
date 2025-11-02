///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_PWM_BASE_2017_10_13_H
  #define MCAL_PWM_BASE_2017_10_13_H

  #include <mcal_irq.h>
  #include <util/utility/util_noncopyable.h>

  #include <algorithm>
  #include <cstdint>

  namespace mcal
  {
    namespace pwm
    {
      class pwm_base : private util::noncopyable
      {
      public:
        using duty_type = std::uint_fast16_t;

        explicit pwm_base(const duty_type resol,
                          const duty_type duty = duty_type { UINT8_C(0) })
          : resolution { resol },
            duty_cycle { duty },
            shadow     { duty } { }

        auto get_resolution() const -> duty_type { return resolution; }

        auto set_duty(const duty_type duty) -> void
        {
          // Set a new duty cycle in the shadow register.
          mcal::irq::disable_all();

          shadow = static_cast<std::uint_fast8_t>((std::min)(duty, get_resolution()));

          mcal::irq::enable_all();
        }

        auto get_duty() const -> duty_type
        {
          // Retrieve the duty cycle.
          mcal::irq::disable_all();

          const volatile duty_type the_duty { duty_cycle };

          mcal::irq::enable_all();

          return the_duty;
        }

        virtual auto service() -> void = 0;

      protected:
        const duty_type resolution;
              duty_type duty_cycle;
              duty_type shadow;
              duty_type counter { };
      };
    }
  }

#endif // MCAL_PWM_BASE_2017_10_13_H
