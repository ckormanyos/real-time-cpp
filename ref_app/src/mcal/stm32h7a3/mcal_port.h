///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2022 - 2024.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_PORT_2022_08_03_H
  #define MCAL_PORT_2022_08_03_H

  #include <mcal_reg.h>

  namespace mcal
  {
    namespace port
    {
      using config_type = void;

      auto init(const config_type*) -> void;

      template<typename addr_type,
               typename reg_type,
               const addr_type port,
               const reg_type bpos>
      class port_pin
      {
      public:
        static auto set_direction_output() -> void
        {
          // Set the port pin control bits.

          {
            // Select the output speed.
            constexpr reg_type msk { gpio_ospeedr_ospeed0 << static_cast<unsigned>(bpos * 2U) };
            constexpr reg_type val { gpio_speed_freq_med  << static_cast<unsigned>(bpos * 2U) };

            mcal::reg::reg_access_static<addr_type, reg_type, output_speed_register, val>::template reg_msk<msk>();
          }

          {
            // Configure the I/O Output Type.
            constexpr reg_type msk { gpio_otyper_ot0 << static_cast<unsigned>(bpos) };

            constexpr reg_type
              val
              {
                static_cast<reg_type>
                (
                  static_cast<reg_type>
                  (
                    static_cast<reg_type>(gpio_mode_output_pp & output_type) >> static_cast<unsigned>(output_type_pos)
                  ) << static_cast<unsigned>(bpos)
                )
              };

            mcal::reg::reg_access_static<addr_type, reg_type, output_type_register, val>::template reg_msk<msk>();
          }

          {
            // Activate the Pull-up or Pull down resistor for the I/O pin.
            constexpr reg_type msk { gpio_pupdr_pupd0 << static_cast<unsigned>(bpos * 2U) };
            constexpr reg_type val { gpio_nopull      << static_cast<unsigned>(bpos * 2U) };

            mcal::reg::reg_access_static<addr_type, reg_type, pull_up_pull_down_register, val>::template reg_msk<msk>();
          }

          {
            // Configure the I/O Direction mode (Input, Output, Alternate or Analog)
            constexpr reg_type msk { gpio_moder_mode0 << static_cast<unsigned>(bpos * 2U) };
            constexpr reg_type val { static_cast<reg_type>(gpio_mode_output_pp & gpio_mode) << static_cast<unsigned>(bpos * 2U) };

            mcal::reg::reg_access_static<addr_type, reg_type, port_mode_register, val>::template reg_msk<msk>();
          }
        }

        static auto set_direction_input() -> void
        {
          // Set the port pin direction to digital input.
          constexpr reg_type mode_inp_not_val { static_cast<std::uint32_t>(UINT32_C(0x03) << static_cast<unsigned>(bpos * 1U)) };

          mcal::reg::reg_access_static<addr_type, reg_type, port_mode_register, mode_inp_not_val>::reg_not();
        }

        static void set_pin_high()
        {
          // Set the port output value to high.
          mcal::reg::reg_access_static<addr_type, reg_type, output_data_register, bpos>::bit_set();
        }

        static auto set_pin_low() -> void
        {
          // Set the port output value to low.
          mcal::reg::reg_access_static<addr_type, reg_type, output_data_register, bpos>::bit_clr();
        }

        static auto read_input_value() -> bool
        {
          // Read the port input value.
          return mcal::reg::reg_access_static<addr_type, reg_type, input_data_register, bpos>::bit_get();
        }

        static auto toggle_pin() -> void
        {
          // Toggle the port output value.
          mcal::reg::reg_access_static<addr_type, reg_type, output_data_register, bpos>::bit_not();
        }

      private:
        static constexpr reg_type gpio_mode_pos              { static_cast<reg_type>(0x0ULL) };
        static constexpr reg_type gpio_mode                  { static_cast<reg_type>(0x3ULL << gpio_mode_pos) };
        static constexpr reg_type mode_input                 { static_cast<reg_type>(0x0ULL << gpio_mode_pos) };
        static constexpr reg_type mode_output                { static_cast<reg_type>(0x1ULL << gpio_mode_pos) };
        static constexpr reg_type mode_af                    { static_cast<reg_type>(0x2ULL << gpio_mode_pos) };
        static constexpr reg_type mode_analog                { static_cast<reg_type>(0x3ULL << gpio_mode_pos) };
        static constexpr reg_type output_type_pos            { static_cast<reg_type>(0x4ULL) };
        static constexpr reg_type output_type                { static_cast<reg_type>(0x1ULL << output_type_pos) };
        static constexpr reg_type output_pp                  { static_cast<reg_type>(0x0ULL << output_type_pos) };
        static constexpr reg_type output_od                  { static_cast<reg_type>(0x1ULL << output_type_pos) };

        static constexpr reg_type gpio_speed_freq_low        { static_cast<reg_type>(0x00000000ULL) };
        static constexpr reg_type gpio_speed_freq_med        { static_cast<reg_type>(0x00000001ULL) };
        static constexpr reg_type gpio_speed_freq_high       { static_cast<reg_type>(0x00000002ULL) };
        static constexpr reg_type gpio_speed_freq_very_high  { static_cast<reg_type>(0x00000003ULL) };
        static constexpr reg_type gpio_mode_input            { static_cast<reg_type>(mode_input) };
        static constexpr reg_type gpio_mode_output_pp        { static_cast<reg_type>(mode_output | output_pp) };
        static constexpr reg_type gpio_nopull                { static_cast<reg_type>(0x00000000ULL) };

        static constexpr reg_type gpio_ospeedr_ospeed0_pos   { static_cast<reg_type>(0x0ULL) };
        static constexpr reg_type gpio_ospeedr_ospeed0_msk   { static_cast<reg_type>(0x3ULL << gpio_ospeedr_ospeed0_pos) };
        static constexpr reg_type gpio_ospeedr_ospeed0       { static_cast<reg_type>(gpio_ospeedr_ospeed0_msk) };

        static constexpr reg_type gpio_otyper_ot0_pos        { static_cast<reg_type>(0x0ULL) };
        static constexpr reg_type gpio_otyper_ot0_msk        { static_cast<reg_type>(0x1ULL << gpio_otyper_ot0_pos) };
        static constexpr reg_type gpio_otyper_ot0            { static_cast<reg_type>(gpio_otyper_ot0_msk) };

        static constexpr reg_type gpio_pupdr_pupd0_pos       { static_cast<reg_type>(0x0ULL) };
        static constexpr reg_type gpio_pupdr_pupd0_msk       { static_cast<reg_type>(0x3ULL << gpio_pupdr_pupd0_pos) };
        static constexpr reg_type gpio_pupdr_pupd0           { static_cast<reg_type>(gpio_pupdr_pupd0_msk) };

        static constexpr reg_type gpio_moder_mode0_pos       { static_cast<reg_type>(0x0ULL) };
        static constexpr reg_type gpio_moder_mode0_msk       { static_cast<reg_type>(0x3ULL << gpio_moder_mode0_pos) };
        static constexpr reg_type gpio_moder_mode0           { static_cast<reg_type>(gpio_moder_mode0_msk) };

        static constexpr reg_type port_mode_register         { static_cast<addr_type>(port + UINT32_C(0x0000)) };
        static constexpr reg_type output_type_register       { static_cast<addr_type>(port + UINT32_C(0x0004)) };
        static constexpr reg_type output_speed_register      { static_cast<addr_type>(port + UINT32_C(0x0008)) };
        static constexpr reg_type pull_up_pull_down_register { static_cast<addr_type>(port + UINT32_C(0x000C)) };
        static constexpr reg_type input_data_register        { static_cast<addr_type>(port + UINT32_C(0x0010)) };
        static constexpr reg_type output_data_register       { static_cast<addr_type>(port + UINT32_C(0x0014)) };
      };
    }
  }

#endif // MCAL_PORT_2022_08_03_H
