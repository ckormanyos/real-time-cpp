///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _MCAL_PWM_2010_09_14_H_
  #define _MCAL_PWM_2010_09_14_H_

  #include <util/utility/util_type.h>

  namespace mcal
  {
    namespace pwm
    {
      typedef void config_type;

      inline void init(const config_type*) { }

      class pwm_type
      {
      public:
        explicit pwm_type(const std::uint8_t = 0U) { }

        void set_duty(const uint8_t) { }

        std::uint8_t get_duty() const { return 0U; }

        void service() { }
      };

      extern pwm_type pwm0;
      extern pwm_type pwm1;
    }
  }

#endif // _MCAL_PWM_2010_09_14_H_
