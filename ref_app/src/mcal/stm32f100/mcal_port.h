///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_PORT_2012_06_27_H_
  #define MCAL_PORT_2012_06_27_H_

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
          // Read the value of the port direction register.
          // Clear all the port pin control bits in the new register value.
          // Set the port pin control bits for output, push-pull, 50MHz in the new register value.
          // Set the port for digital output.
          mcal::reg::reg_access_static<
            addr_type,
            reg_type,
            pdir,
            reg_type(0x3UL << pdir_shift)>::template reg_msk<reg_type(0xFUL << pdir_shift)>();
        }

        static void set_direction_input()
        {
          // Read the value of the port direction register.
          // Clear all the port pin control bits in the new register value.
          // Set the port pin control bits for input in the new register value.
          // Set the port for digital input.
          mcal::reg::reg_access_static<
            addr_type,
            reg_type,
            pdir,
            reg_type(0x4UL << pdir_shift)>::template reg_msk<reg_type(0xFUL << pdir_shift)>();
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
        static constexpr addr_type pdir = addr_type(port - addr_type((bpos >= 8U) ? 8U : 12U));
        static constexpr addr_type pinp = addr_type(port - 4U);

        static constexpr reg_type pdir_shift = reg_type((bpos - reg_type((bpos >= 8U) ? 8U : 0U)) * 4U);
      };
    }
  }

#endif // MCAL_PORT_2012_06_27_H_
