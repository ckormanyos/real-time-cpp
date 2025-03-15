///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_PORT_2025_03_15_H
  #define MCAL_PORT_2025_03_15_H

  #include <mcal_reg.h>

  namespace mcal
  {
    namespace port
    {
      using config_type = void;

      auto init(const config_type*) -> void;

      template<const std::uint32_t bpos>
      class port_pin
      {
      private:
        static constexpr std::uint32_t gpio_base         { mcal::reg::gpio::rtc_gpio_base };
        static constexpr std::uint32_t gpio_pinxx_reg    { gpio_base + std::uint32_t { (UINT32_C(10) + bpos) * UINT32_C(4) } };
        static constexpr std::uint32_t io_rtc_padxx_reg  { gpio_base + std::uint32_t { UINT32_C(0x5C) + (UINT32_C(10) + bpos) * UINT32_C(4) } };

      public:
        static auto set_direction_output() -> void
        {
          mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, io_rtc_padxx_reg, UINT32_C(19)>::bit_set();
          mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, gpio_pinxx_reg, UINT32_C(0)>::reg_set();

          // Set the pin to output low.
          mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::gpio::rtc_gpio_out_reg,    std::uint32_t { UINT32_C(10) + bpos }>::bit_clr();
          mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::gpio::rtc_gpio_enable_reg, std::uint32_t { UINT32_C(10) + bpos }>::bit_set();
        }

        static auto set_direction_input() -> void
        {
        }

        static auto set_pin_high() -> void
        {
          mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::gpio::rtc_gpio_out_reg, std::uint32_t { UINT32_C(10) + bpos }>::bit_set();
        }

        static auto set_pin_low() -> void
        {
          mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::gpio::rtc_gpio_out_reg, std::uint32_t { UINT32_C(10) + bpos }>::bit_clr();
        }

        static auto read_input_value() -> bool
        {
          return false;
        }

        static auto toggle_pin() -> void
        {
          mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::gpio::rtc_gpio_out_reg, std::uint32_t { UINT32_C(10) + bpos }>::bit_not();
        }
      };
    }
  }

#endif // MCAL_PORT_2025_03_15_H
