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

      template<const unsigned PortIndex>
      class port_pin
      {
      private:
        static constexpr std::uint32_t GPIO_FUN_SDIO   { UINT32_C( 1) };
        static constexpr std::uint32_t GPIO_FUN_FLASH  { UINT32_C( 2) };
        static constexpr std::uint32_t GPIO_FUN_SPI    { UINT32_C( 4) };
        static constexpr std::uint32_t GPIO_FUN_I2C    { UINT32_C( 6) };
        static constexpr std::uint32_t GPIO_FUN_UART   { UINT32_C( 7) };
        static constexpr std::uint32_t GPIO_FUN_PWM    { UINT32_C( 8) };
        static constexpr std::uint32_t GPIO_FUN_EXT_PA { UINT32_C( 9) };
        static constexpr std::uint32_t GPIO_FUN_ANALOG { UINT32_C(10) };
        static constexpr std::uint32_t GPIO_FUN_SWGPIO { UINT32_C(11) };
        static constexpr std::uint32_t GPIO_FUN_JTAG   { UINT32_C(14) };

        static constexpr std::uint32_t port_index { static_cast<std::uint32_t>(PortIndex) };

        static constexpr bool odd_index { ((PortIndex % unsigned { UINT8_C(2) }) != unsigned { UINT8_C(0) }) };

        static constexpr std::uintptr_t
          cfgctl
          {
            static_cast<std::uintptr_t>
            (
              mcal::reg::gpio_cfgctl0 + (port_index / 2U) * 4U
            )
          };

        static constexpr unsigned cfgctl_bpos_reg_gpio_3_func_sel { odd_index ? UINT8_C(24) : UINT8_C(24) - UINT8_C(16) };
        static constexpr unsigned cfgctl_bpos_reg_gpio_3_ie       { odd_index ? UINT8_C(16) : UINT8_C(16) - UINT8_C(16) };
        static constexpr unsigned cfgctl_bpos_reg_gpio_3_smt      { odd_index ? UINT8_C(17) : UINT8_C(17) - UINT8_C(16) };
        static constexpr unsigned cfgctl_bpos_reg_gpio_3_drv      { odd_index ? UINT8_C(18) : UINT8_C(18) - UINT8_C(16) };

      public:
        static auto set_direction_output() noexcept -> void
        {
          mcal::reg::reg_access_static<std::uintptr_t, std::uint32_t, cfgctl, static_cast<std::uint32_t>(GPIO_FUN_SWGPIO << cfgctl_bpos_reg_gpio_3_func_sel)>::template reg_msk<static_cast<std::uint32_t>(UINT32_C(0xF) << cfgctl_bpos_reg_gpio_3_func_sel)>();
          mcal::reg::reg_access_static<std::uintptr_t, std::uint32_t, cfgctl, cfgctl_bpos_reg_gpio_3_ie>::bit_clr();
          mcal::reg::reg_access_static<std::uintptr_t, std::uint32_t, cfgctl, cfgctl_bpos_reg_gpio_3_smt>::bit_clr();
          mcal::reg::reg_access_static<std::uintptr_t, std::uint32_t, cfgctl, UINT32_C(0) << cfgctl_bpos_reg_gpio_3_drv>::template reg_msk<UINT32_C(3) << cfgctl_bpos_reg_gpio_3_drv>();

          mcal::reg::reg_access_static<std::uintptr_t, std::uint32_t, mcal::reg::gpio_cfgctl34, port_index>::bit_set();
        }

        static auto set_direction_input() noexcept -> void
        {
          // Not yet implemented.
        }

        static auto set_pin_high() noexcept -> void
        {
          mcal::reg::reg_access_static<std::uintptr_t, std::uint32_t, mcal::reg::gpio_cfgctl32, port_index>::bit_set();
        }

        static auto set_pin_low() noexcept -> void
        {
          mcal::reg::reg_access_static<std::uintptr_t, std::uint32_t, mcal::reg::gpio_cfgctl32, port_index>::bit_clr();
        }

        static auto read_input_value() noexcept -> bool
        {
          // Not yet implemented.
          return false;
        }

        static auto toggle_pin() noexcept -> void
        {
          mcal::reg::reg_access_static<std::uintptr_t, std::uint32_t, mcal::reg::gpio_cfgctl32, port_index>::bit_not();
        }
      };
    }
  }

#endif // MCAL_PORT_2014_01_10_H
