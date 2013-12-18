///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _MCAL_PORT_2012_06_27_H_
  #define _MCAL_PORT_2012_06_27_H_

  #include <cstdint>
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
          // Set the port pin control bits.

          // Set for no pull up, no pull down.
          mcal::reg::dynamic_access<addr_type, reg_type>::reg_msk(pull_up_pull_down, reg_type(0U), my_mask);

          // Select the fastest output speed.
          mcal::reg::dynamic_access<addr_type, reg_type>::reg_msk(output_speed, reg_type(3U) << (bpos * 2), my_mask);

          // Set to push-pull.
          mcal::reg::access<addr_type, reg_type, output_type, bpos>::bit_clr();

          // Set to output.
          mcal::reg::dynamic_access<addr_type, reg_type>::reg_msk(port_mode, reg_type(1U) << (bpos * 2), my_mask);
        }

        static void set_direction_input()
        {
          // Set the port for digital input.
          mcal::reg::dynamic_access<addr_type, reg_type>::reg_msk(port_mode, reg_type(0U), my_mask);
        }

        static void set_pin_high()
        {
          // Set the port output value to high.
          mcal::reg::access<addr_type, reg_type, output_data, bpos>::bit_set();
        }

        static void set_pin_low()
        {
          // Set the port output value to low.
          mcal::reg::access<addr_type, reg_type, output_data, bpos>::bit_clr();
        }

        static bool read_input_value()
        {
          // Read the port input value.
          return mcal::reg::access<addr_type, reg_type, input_data, bpos>::bit_get();
        }

        static void toggle_pin()
        {
          // Toggle the port output value.
          mcal::reg::access<addr_type, reg_type, output_data, bpos>::bit_not();
        }

      private:
        static constexpr addr_type port_mode         = port;
        static constexpr addr_type output_type       = port + 0x04U;
        static constexpr addr_type output_speed      = port + 0x08U;
        static constexpr addr_type pull_up_pull_down = port + 0x0CU;
        static constexpr addr_type input_data        = port + 0x10U;
        static constexpr addr_type output_data       = port + 0x14U;

        static constexpr reg_type my_mask = reg_type(3U << (bpos * 2));
      };
    }
  }

#endif // _MCAL_PORT_2012_06_27_H_
