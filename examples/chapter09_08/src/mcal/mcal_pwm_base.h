///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2018.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_PWM_BASE_2017_10_13_H_
  #define MCAL_PWM_BASE_2017_10_13_H_

  #include <algorithm>
  #include <cstdint>

  #include <mcal_irq.h>
  #include <util/utility/util_noncopyable.h>

  namespace mcal
  {
    namespace pwm
    {
      class pwm_base : private util::noncopyable
      {
      public:
        typedef std::uint_fast16_t duty_type;

        pwm_base(const duty_type resol,
                 const duty_type duty = 0U) : resolution(resol),
                                              counter   (0U),
                                              duty_cycle(duty),
                                              shadow    (duty) { }

        duty_type get_resolution() const { return resolution; }

        void set_duty(const duty_type duty)
        {
          // Set a new duty cycle in the shadow register.
          mcal::irq::disable_all();

          shadow = static_cast<std::uint_fast8_t>((std::min)(duty, get_resolution()));

          mcal::irq::enable_all();
        }

        duty_type get_duty() const
        {
          // Retrieve the duty cycle.
          mcal::irq::disable_all();

          const volatile std::uint_fast8_t the_duty = duty_cycle;

          mcal::irq::enable_all();

          return the_duty;
        }

        virtual void service() = 0;

      protected:
        const duty_type resolution;
              duty_type counter;
              duty_type duty_cycle;
              duty_type shadow;
      };
    }
  }

#endif // MCAL_PWM_BASE_2017_10_13_H_
