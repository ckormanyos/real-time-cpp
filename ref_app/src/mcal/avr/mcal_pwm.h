///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _MCAL_PWM_2010_09_14_H_
  #define _MCAL_PWM_2010_09_14_H_

  #include <algorithm>
  #include <atomic>
  #include <cstdint>
  #include <mcal_port.h>
  #include <mcal_reg_access.h>
  #include <util/utility/util_noncopyable.h>


  namespace mcal
  {
    namespace pwm
    {
      typedef void config_type;

      void init(const config_type*);

      // A software PWM template for a pin at address addr and
      // bit-position bpos. The default resolution is 100 ticks.
      // These values can be changed as needed.

      template<typename addr_type,
               typename reg_type,
               const addr_type addr,
               const reg_type bpos,
               const std::uint8_t period = 100U>
      class pwm_type : private util::noncopyable
      {
      public:
        typedef std::uint8_t duty_type;

        pwm_type(const duty_type duty = 0U) : counter   (0U),
                                              duty_cycle(duty),
                                              shadow    (duty)
        {
          // Set the port pin to output with logic level low.
          port_pin_type::set_pin_low();
          port_pin_type::set_direction_output();
        }

        void set_duty(const duty_type duty)
        {
          // Set a new duty cycle in the shadow register.
          std::atomic_store(&shadow, (std::min)(duty, period));
        }

        duty_type get_duty() const
        {
          // Retrieve the duty cycle.
          return std::atomic_load(&duty_cycle);
        }

        void service()
        {
          if(duty_cycle == 0U)
          {
            // Output low if  duty cycle == 0U.
            port_pin_type::set_pin_low();
          }
          else if(duty_cycle == period)
          {
            // Output high if duty_cycle == period.
            port_pin_type::set_pin_high();
          }
          else
          {
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
          }

          // Increment the counter.
          ++counter;

          if(counter >= period)
          {
            // Latch duty cycle from the shadow register.
            duty_cycle = shadow;

            // Reset the counter for a new PWM period.
            counter = 0U;
          }
        }


        duty_type get_period() const { return period; }

      private:
        duty_type counter;
        volatile duty_type duty_cycle;
        duty_type shadow;

        // Define the type for the PWM port pin.
        typedef mcal::port::port_pin<addr_type,
                                     reg_type,
                                     addr,
                                     bpos> port_pin_type;
      };

      void set_duty_cycle(const std::uint8_t channel, const std::uint8_t duty_cycle);
    }
  }

#endif // _MCAL_PWM_2010_09_14_H_
