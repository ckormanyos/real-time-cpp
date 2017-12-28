///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_LED_2010_09_14_H_
  #define MCAL_LED_2010_09_14_H_

  #include <cstdint>
  #include <mcal_port.h>
  #include <util/utility/util_noncopyable.h>

  namespace mcal
  {
    namespace led
    {
      template<typename addr_type,
               typename reg_type,
               const addr_type port,
               const reg_type bpos>
      class led final : private util::noncopyable
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
          port_pin_type::toggle_pin();
        }

      private:
        typedef mcal::port::port_pin<addr_type,
                                     reg_type,
                                     port,
                                     bpos> port_pin_type;
      };

      // The LED's on the stm32f4discovery board are as follows:
      // - portd.12: green
      // - portd.13: organge
      // - portd.14: red
      // - portd.15: blue
      typedef led<std::uint32_t,
                  std::uint32_t,
                  mcal::reg::gpiog_base,
                  UINT32_C(13)> led_type;

      extern const led_type led0;
    }
  }

#endif // MCAL_LED_2010_09_14_H_
