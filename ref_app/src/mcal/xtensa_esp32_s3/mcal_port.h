///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_PORT_2025_02_22_H
  #define MCAL_PORT_2025_02_22_H

  #include <mcal_reg.h>

  namespace mcal
  {
    namespace port
    {
      typedef void config_type;

      void init(const config_type*);

      template<const std::uint32_t bpos>
      class port_pin
      {
      private:
        static constexpr std::uint32_t bit_pos { bpos };

      public:
        static auto set_direction_output() -> void
        {
          mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::gpio::out,          bit_pos>::bit_clr();
          mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::gpio::out1,         bit_pos>::bit_clr();
          mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::gpio::enable_w1ts,  bit_pos>::bit_set();
          mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::gpio::enable1_w1ts, bit_pos>::bit_set();
        }

        static auto set_direction_input() -> void
        {
          mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::gpio::enable_w1ts,  bit_pos>::bit_clr();
          mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::gpio::enable1_w1ts, bit_pos>::bit_clr();
          mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::gpio::out,          bit_pos>::bit_clr();
          mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::gpio::out1,         bit_pos>::bit_clr();
        }

        static auto set_pin_high() -> void
        {
          mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::gpio::out, bit_pos>::bit_set();
        }

        static auto set_pin_low() -> void
        {
          mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::gpio::out, bit_pos>::bit_clr();
        }

        static auto read_input_value() -> bool
        {
          return false;
        }

        static auto toggle_pin() -> void
        {
          mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::gpio::out, bit_pos>::bit_not();
        }
      };
    }
  }

#endif // MCAL_PORT_2025_02_22_H
