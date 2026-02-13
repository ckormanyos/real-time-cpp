///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2026.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_PORT_2025_02_22_H
  #define MCAL_PORT_2025_02_22_H

  #include <gpio.h>
  #include <mcal_reg.h>

  #include <cstdint>

  namespace mcal
  {
    namespace port
    {
      typedef void config_type;

      void init(const config_type*);

      template<const unsigned PortIndex>
      class port_pin
      {
      public:
        static auto set_direction_output() -> void
        {
          ::gpio_cfg_output(static_cast<std::uint8_t>(PortIndex));
        }

        static auto set_direction_input() -> void
        {
        }

        static auto set_pin_high() -> void
        {
          ::gpio_set_output_level(static_cast<std::uint8_t>(PortIndex), std::uint8_t { UINT8_C(1) });
        }

        static auto set_pin_low() -> void
        {
          ::gpio_set_output_level(static_cast<std::uint8_t>(PortIndex), std::uint8_t { UINT8_C(0) });
        }

        static auto read_input_value() -> bool
        {
          return false;
        }

        static auto toggle_pin() -> void
        {
          ::gpio_toggle_output_level(static_cast<std::uint8_t>(PortIndex));
        }
      };
    }
  }

#endif // MCAL_PORT_2025_02_22_H
