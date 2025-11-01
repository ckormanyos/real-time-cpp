///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_PORT_2014_01_10_H
  #define MCAL_PORT_2014_01_10_H

  #include <mcal_cpu.h>
  #include <mcal_reg.h>

  #include <cstddef>
  #include <cstdint>

  namespace mcal
  {
    namespace port
    {
      using config_type = void;

      void init(const config_type*);

      class port_pin
      {
      public:
        static auto set_direction_output() noexcept -> void
        {
          // Not yet implemented.
        }

        static auto set_direction_input() noexcept -> void
        {
          // Not yet implemented.
        }

        static auto set_pin_high() noexcept -> void
        {
          // Not yet implemented.
        }

        static auto set_pin_low() noexcept -> void
        {
          // Not yet implemented.
        }

        static auto read_input_value() noexcept -> bool
        {
          // Not yet implemented.
          return false;
        }

        static auto toggle_pin() noexcept -> void
        {
          // Not yet implemented.
        }
      };
    }
  }

#endif // MCAL_PORT_2014_01_10_H
