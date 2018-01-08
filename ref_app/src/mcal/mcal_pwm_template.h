///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2018.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_PWM_TEMPLATE_2017_10_13_H_
  #define MCAL_PWM_TEMPLATE_2017_10_13_H_

  #include <algorithm>
  #include <cstdint>

  #include <mcal_irq.h>
  #include <mcal_port.h>
  #include <util/utility/util_noncopyable.h>

  namespace mcal
  {
    namespace pwm
    {
      // A software PWM template for a pin at address addr and
      // bit-position bpos. The default resolution is 100 ticks.
      // These values can be changed as needed.

      template<typename port_pin_type,
               const std::uint_fast8_t resol = 100U>
      class pwm_template : private util::noncopyable
      {
      private:
        static const std::uint_fast8_t my_resolution = resol;

      public:
        typedef std::uint8_t duty_type;

        pwm_template(const duty_type duty = 0U) : counter(0U),
                                                  duty_cycle(duty),
                                                  shadow(duty)
        {
          // Set the port pin to output with logic level low.
          port_pin_type::set_pin_low();
          port_pin_type::set_direction_output();
        }

        virtual std::uint_fast8_t get_resolution() const { return my_resolution; }

        virtual void set_duty(const duty_type duty)
        {
          // Set a new duty cycle in the shadow register.
          mcal::irq::disable_all();

          shadow = static_cast<std::uint_fast8_t>((std::min)(duty, my_resolution));

          mcal::irq::enable_all();
        }

        virtual duty_type get_duty() const
        {
          // Retrieve the duty cycle.
          mcal::irq::disable_all();

          const volatile std::uint_fast8_t the_duty = duty_cycle;

          mcal::irq::enable_all();

          return the_duty;
        }

        void service()
        {
          // Increment the counter.
          ++counter;

          if(counter <= duty_cycle)
          {
            // Output high if counter less than duty cycle.
            port_pin_type::set_pin_high();
          }
          else
          {
            // Output low if counter exceeds duty cycle.
            port_pin_type::set_pin_low();
          }

          if(counter >= my_resolution)
          {
            // Latch duty cycle from the shadow register.
            duty_cycle = shadow;

            // Reset the counter for a new PWM period.
            counter = 0U;
          }
        }

      private:
        duty_type counter;
        duty_type duty_cycle;
        duty_type shadow;
      };
    }
  }

#endif // MCAL_PWM_TEMPLATE_2017_10_13_H_
