///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2014.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_PORT_2014_01_10_H_
  #define MCAL_PORT_2014_01_10_H_

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
          mcal::reg::access<addr_type,
                            reg_type,
                            pull_up_pull_down_register,
                            ~static_cast<std::uint32_t>(UINT32_C(0x03) << (bpos * 2U))>::reg_and();

          // Select the fastest output speed.
          mcal::reg::access<addr_type,
                            reg_type,
                            output_speed_register,
                            static_cast<std::uint32_t>(UINT32_C(0x03) << (bpos * 2U))>::reg_or();

          // Set the port pin to push-pull output type.
          mcal::reg::access<addr_type,
                            reg_type,
                            output_type_register,
                            bpos>::bit_clr();

          // Set the port pin direction to digital output.
          mcal::reg::access<addr_type,
                            reg_type,
                            port_mode_register,
                            static_cast<std::uint32_t>(UINT32_C(0x01) << (bpos * 2U))>::reg_or();
        }

        static void set_direction_input()
        {
          // Set the port pin direction to digital input.
          mcal::reg::access<addr_type,
                            reg_type,
                            port_mode_register,
                            ~static_cast<std::uint32_t>(UINT32_C(0x03) << (bpos * 2U))>::reg_and();
        }

        static void set_pin_high()
        {
          // Set the port output value to high.
          mcal::reg::access<addr_type,
                            reg_type,
                            output_data_register,
                            bpos>::bit_set();
        }

        static void set_pin_low()
        {
          // Set the port output value to low.
          mcal::reg::access<addr_type,
                            reg_type,
                            output_data_register,
                            bpos>::bit_clr();
        }

        static bool read_input_value()
        {
          // Read the port input value.

          // According to the microcontroller handbook:
          // "These bits are read-only and can be accessed in *word* mode only, ..."
          // We, therefore, access this register with a 16-bit address-type
          // template parameter.

          return mcal::reg::access<addr_type,
                                   std::uint16_t,
                                   input_data_register,
                                   bpos>::bit_get();
        }

        static void toggle_pin()
        {
          // Toggle the port output value.
          mcal::reg::access<addr_type,
                            reg_type,
                            output_data_register,
                            bpos>::bit_not();
        }

      private:
        static constexpr addr_type port_mode_register         = addr_type(port + 0x00UL);
        static constexpr addr_type output_type_register       = addr_type(port + 0x04UL);
        static constexpr addr_type output_speed_register      = addr_type(port + 0x08UL);
        static constexpr addr_type pull_up_pull_down_register = addr_type(port + 0x0CUL);
        static constexpr addr_type input_data_register        = addr_type(port + 0x10UL);
        static constexpr addr_type output_data_register       = addr_type(port + 0x14UL);
      };
    }
  }

#endif // MCAL_PORT_2014_01_10_H_
