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
  #include <mcal_port.h>

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
          // Set the port pin value to low.
          port_pin_type::set_pin_low();

          // Set the port pin direction to output.
          port_pin_type::set_direction_output();
        }

        static void toggle()
        {
          // Toggle the LED.
          port_pin_type::toggle();
        }

      private:
        typedef mcal::port::port_pin<addr_type,
                                     reg_type,
                                     port,
                                     bpos> port_pin_type;
      };

      typedef led<std::uint8_t,
                  std::uint8_t,
                  mcal::reg::portb,
                  5U> led_type;

      extern const led_type led0;
    }
  }

#endif // _MCAL_LED_2010_09_14_H_
