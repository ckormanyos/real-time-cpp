///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2023.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_PORT_2023_07_04_H
  #define MCAL_PORT_2023_07_04_H

  #include <mcal_reg.h>

  namespace mcal
  {
    namespace port
    {
      using config_type = void;

      auto init(const config_type*) -> void;

      template<typename addr_type,
               typename reg_type,
               const addr_type port = static_cast<addr_type>(0U),
               const reg_type bpos = static_cast<reg_type>(0U)>
      class port_pin
      {
      public:
        static auto set_direction_output() -> void
        {
        }

        static auto set_direction_input() -> void
        {
        }

        static void set_pin_high()
        {
        }

        static auto set_pin_low() -> void
        {
        }

        static auto read_input_value() -> bool
        {
          return false;
        }

        static auto toggle_pin() -> void
        {
        }
      };
    }
  }

#endif // MCAL_PORT_2022_08_03_H_
