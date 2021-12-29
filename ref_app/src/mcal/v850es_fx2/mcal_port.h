///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2021.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_PORT_2021_12_25_H_
  #define MCAL_PORT_2021_12_25_H_

  #include <mcal_reg.h>

  namespace mcal
  {
    namespace port
    {
      typedef void config_type;

      void init(const config_type*);

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
          mcal::reg::reg_access_static<addr_type, reg_type, pdir, bpos>::bit_clr();
        }

        static void set_direction_input()
        {
          // Set the port pin's direction to input.
          mcal::reg::reg_access_static<addr_type, reg_type, pdir, bpos>::bit_set();
        }

        static void set_pin_high()
        {
          // Set the port output value to high.
          mcal::reg::reg_access_static<addr_type, reg_type, port, bpos>::bit_set();
        }

        static void set_pin_low()
        {
          // Set the port output value to low.
          mcal::reg::reg_access_static<addr_type, reg_type, port, bpos>::bit_clr();
        }

        static bool read_input_value()
        {
          // Read the port input value.
          return mcal::reg::reg_access_static<addr_type, reg_type, pinp, bpos>::bit_get();
        }

        static void toggle_pin()
        {
          // Toggle the port output value.
          mcal::reg::reg_access_static<addr_type, reg_type, port, bpos>::bit_not();
        }

      private:
        static constexpr addr_type pdir = port + 0x20U;
        static constexpr addr_type pinp = port;
      };
    }
  }

#endif // MCAL_PORT_2021_12_25_H_
