///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _MCAL_LED_2010_09_14_H_
  #define _MCAL_LED_2010_09_14_H_

  #include <util/utility/util_type.h>
  #include <util/utility/util_noncopyable.h>
  #include <mcal_reg_access.h>

  namespace mcal
  {
    namespace led
    {
      template<typename addr_type,
               typename reg_type,
               const addr_type port,
               const reg_type bpos>
      class led : private util::noncopyable
      {
      public:
        led()
        {
          // The ports have already been initialized.
          // TBD: Implement the proper LED encapsulation.
        }

        void toggle() const
        {
          // Toggle the LED.
          mcal::reg::access<addr_type, reg_type, port, bpos>::bit_not();
        }
      };

      typedef led<std::uint32_t, std::uint32_t, mcal::reg::gpioc_odr, 8U> led_type;

      extern const led_type led0;
    }
  }

#endif // _MCAL_LED_2010_09_14_H_
