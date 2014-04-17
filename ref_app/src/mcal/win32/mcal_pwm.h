///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _MCAL_PWM_2010_09_14_H_
  #define _MCAL_PWM_2010_09_14_H_

  #include <cstdint>
  #include <util/utility/util_noncopyable.h>

  namespace mcal
  {
    namespace pwm
    {
      typedef void config_type;

      inline void init(const config_type*) { }

      class pwm_type : private util::noncopyable
      {
      public:
        typedef std::uint8_t duty_type;

        explicit pwm_type(const duty_type = 0U) { }

        void set_duty(const duty_type) { }

        duty_type get_duty() const { return 0U; }

        void service() { }
      };

      typedef pwm_type pwm0_type;
      typedef pwm_type pwm1_type;

      extern pwm0_type pwm0;
      extern pwm1_type pwm1;

      inline void set_duty_cycle(const std::uint8_t, const std::uint8_t) { }
    }
  }

#endif // _MCAL_PWM_2010_09_14_H_
