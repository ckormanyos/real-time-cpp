///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _MCAL_PORT_2012_06_27_H_
  #define _MCAL_PORT_2012_06_27_H_

  #include <util/utility/util_type.h>
  #include <util/utility/util_noncopyable.h>
  #include <mcal_reg_access.h>

  namespace mcal
  {
    namespace port
    {
      typedef void config_type;
      inline void init(const config_type*) { }

      template<typename addr_type,
               typename reg_type,
               const addr_type port,
               const reg_type bpos>
      class port_pin
      {
      public:
        static void set_direction_output()
        {
          // Set the port pin's direction to output.
          mcal::reg::access<addr_type,
                            reg_type,
                            pdir,
                            bpos>::bit_set();
        }

        static void set_direction_input()
        {
          // Set the port pin's direction to input.
          mcal::reg::access<addr_type,
                            reg_type,
                            pdir,
                            bpos>::bit_clr();
        }

        static void set_pin_high()
        {
          // Set the port output value to high.
          mcal::reg::access<addr_type,
                            reg_type,
                            port,
                            bpos>::bit_set();
        }

        static void set_pin_low()
        {
          // Set the port output value to low.
          mcal::reg::access<addr_type,
                            reg_type,
                            port,
                            bpos>::bit_clr();
        }

        static bool read_input_value()
        {
          // Read the port input value.
          return mcal::reg::access<addr_type,
                                   reg_type,
                                   pinp,
                                   bpos>::bit_get();
        }

        static void toggle()
        {
          // Toggle the port output value.
          mcal::reg::access<addr_type,
                            reg_type,
                            port,
                            bpos>::bit_not();
        }

      private:
        static constexpr addr_type pdir = port - 1U;
        static constexpr addr_type pinp = port - 2U;
      };

      // Microcontroller input TFT output left-hand side.
      typedef port_pin<std::uint8_t,
                       std::uint8_t,
                       mcal::reg::portd,
                       0U> port0;

      // Microcontroller input TFT output right-hand side.
      typedef port_pin<std::uint8_t,
                       std::uint8_t,
                       mcal::reg::portd,
                       1U> port1;

      // Microcontroller output SPI slave-select left-hand side TFT.
      typedef port_pin<std::uint8_t,
                       std::uint8_t,
                       mcal::reg::portd,
                       2U> port2;

      // Microcontroller output SPI slave-select right-hand side TFT.
      typedef port_pin<std::uint8_t,
                       std::uint8_t,
                       mcal::reg::portd,
                       3U> port3;
    }
  }

#endif // _MCAL_PORT_2012_06_27_H_
