///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _MCAL_PORT_2012_06_27_H_
  #define _MCAL_PORT_2012_06_27_H_

  #include <mcal_reg_access.h>

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
          // Set the port direction to output.
          mcal::reg::access<addr_type, reg_type, the_tris_reg, bpos>::bit_clr();
        }

        static void set_direction_input()
        {
          // Set the port direction to input.
          mcal::reg::access<addr_type, reg_type, the_tris_reg, bpos>::bit_set();
        }

        static void set_pin_high()
        {
          // Set the port output value to high.
          mcal::reg::access<addr_type, reg_type, the_lat_reg, bpos>::bit_set();
        }

        static void set_pin_low()
        {
          // Set the port output value to low.
          mcal::reg::access<addr_type, reg_type, the_lat_reg, bpos>::bit_clr();
        }

        static bool read_input_value()
        {
          // Read the port input value.
          return mcal::reg::access<addr_type, reg_type, the_port_reg, bpos>::bit_get();
        }

        static void toggle_pin()
        {
          // Toggle the port output value.
          return mcal::reg::access<addr_type, reg_type, the_lat_reg, bpos>::bit_not();
        }

      private:
        static constexpr addr_type the_tris_reg = port;
        static constexpr addr_type the_port_reg = addr_type(port + 0x10U);
        static constexpr addr_type the_lat_reg  = addr_type(port + 0x20U);
        static constexpr addr_type the_odc_reg  = addr_type(port + 0x30U);
      };
    }
  }

#endif // _MCAL_PORT_2012_06_27_H_
