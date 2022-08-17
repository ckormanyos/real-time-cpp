///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2022.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_PORT_2022_08_03_H_
  #define MCAL_PORT_2022_08_03_H_

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
          // Set the port pin control bits.

          {
            // Select the lowest output speed.
            constexpr auto msk = static_cast<reg_type>(gpio_ospeedr_ospeed0 << (bpos * 2U));
            constexpr auto val = static_cast<reg_type>(gpio_speed_freq_low  << (bpos * 2U));

            mcal::reg::reg_access_static<addr_type,
                                         reg_type,
                                         output_speed_register,
                                         val>::template reg_msk<msk>();
          }

          {
            // Configure the I/O Output Type.
            constexpr auto msk = static_cast<reg_type>(gpio_otyper_ot0 << bpos);
            constexpr auto val = static_cast<reg_type>(static_cast<reg_type>(static_cast<reg_type>(gpio_mode_output_pp & output_type) >> output_type_pos) << bpos);

            mcal::reg::reg_access_static<addr_type,
                                         reg_type,
                                         output_type_register,
                                         val>::template reg_msk<msk>();
          }

          {
            // Activate the Pull-up or Pull down resistor for the I/O pin.
            constexpr auto msk = static_cast<reg_type>(gpio_pupdr_pupd0 << (bpos * 2u));
            constexpr auto val = static_cast<reg_type>(gpio_nopull      << (bpos * 2u));

            mcal::reg::reg_access_static<addr_type,
                                         reg_type,
                                         pull_up_pull_down_register,
                                         val>::template reg_msk<msk>();
          }

          {
            // Configure the I/O Direction mode (Input, Output, Alternate or Analog)
            constexpr auto msk = static_cast<reg_type>(gpio_moder_mode0 << (bpos * 2u));
            constexpr auto val = static_cast<reg_type>(static_cast<reg_type>(gpio_mode_output_pp & gpio_mode) << (bpos * 2U));

            mcal::reg::reg_access_static<addr_type,
                                         reg_type,
                                         port_mode_register,
                                         val>::template reg_msk<msk>();
          }
        }

        static void set_direction_input()
        {
          // Set the port pin direction to digital input.
          mcal::reg::reg_access_static<addr_type,
                                       reg_type,
                                       port_mode_register,
                                       ~static_cast<std::uint32_t>(UINT32_C(0x03) << (bpos * 1U))>::reg_and();
        }

        static void set_pin_high()
        {
          // Set the port output value to high.
          mcal::reg::reg_access_static<addr_type,
                                       reg_type,
                                       output_data_register,
                                       bpos>::bit_set();
        }

        static void set_pin_low()
        {
          // Set the port output value to low.
          mcal::reg::reg_access_static<addr_type,
                                       reg_type,
                                       output_data_register,
                                       bpos>::bit_clr();
        }

        static bool read_input_value()
        {
          // Read the port input value.
          return mcal::reg::reg_access_static<addr_type,
                                              reg_type,
                                              input_data_register,
                                              bpos>::bit_get();
        }

        static void toggle_pin()
        {
          // Toggle the port output value.
          mcal::reg::reg_access_static<addr_type,
                                       reg_type,
                                       output_data_register,
                                       bpos>::bit_not();
        }

      private:
        static constexpr auto gpio_mode_pos              = static_cast<reg_type>(0x0ULL);
        static constexpr auto gpio_mode                  = static_cast<reg_type>(0x3ULL << gpio_mode_pos);
        static constexpr auto mode_input                 = static_cast<reg_type>(0x0ULL << gpio_mode_pos);
        static constexpr auto mode_output                = static_cast<reg_type>(0x1ULL << gpio_mode_pos);
        static constexpr auto mode_af                    = static_cast<reg_type>(0x2ULL << gpio_mode_pos);
        static constexpr auto mode_analog                = static_cast<reg_type>(0x3ULL << gpio_mode_pos);
        static constexpr auto output_type_pos            = static_cast<reg_type>(0x4ULL);
        static constexpr auto output_type                = static_cast<reg_type>(0x1ULL << output_type_pos);
        static constexpr auto output_pp                  = static_cast<reg_type>(0x0ULL << output_type_pos);
        static constexpr auto output_od                  = static_cast<reg_type>(0x1ULL << output_type_pos);

        static constexpr auto gpio_speed_freq_low        = static_cast<reg_type>(0x00000000ULL);
        static constexpr auto gpio_mode_input            = static_cast<reg_type>(mode_input);
        static constexpr auto gpio_mode_output_pp        = static_cast<reg_type>(mode_output | output_pp);
        static constexpr auto gpio_nopull                = static_cast<reg_type>(0x00000000ULL);

        static constexpr auto gpio_ospeedr_ospeed0_pos   = static_cast<reg_type>(0x0ULL);
        static constexpr auto gpio_ospeedr_ospeed0_msk   = static_cast<reg_type>(0x3ULL << gpio_ospeedr_ospeed0_pos);
        static constexpr auto gpio_ospeedr_ospeed0       = static_cast<reg_type>(gpio_ospeedr_ospeed0_msk);

        static constexpr auto gpio_otyper_ot0_pos        = static_cast<reg_type>(0x0ULL);
        static constexpr auto gpio_otyper_ot0_msk        = static_cast<reg_type>(0x1ULL << gpio_otyper_ot0_pos);
        static constexpr auto gpio_otyper_ot0            = static_cast<reg_type>(gpio_otyper_ot0_msk);

        static constexpr auto gpio_pupdr_pupd0_pos       = static_cast<reg_type>(0x0ULL);
        static constexpr auto gpio_pupdr_pupd0_msk       = static_cast<reg_type>(0x3ULL << gpio_pupdr_pupd0_pos);
        static constexpr auto gpio_pupdr_pupd0           = static_cast<reg_type>(gpio_pupdr_pupd0_msk);

        static constexpr auto gpio_moder_mode0_pos       = static_cast<reg_type>(0x0ULL);
        static constexpr auto gpio_moder_mode0_msk       = static_cast<reg_type>(0x3ULL << gpio_moder_mode0_pos);
        static constexpr auto gpio_moder_mode0           = static_cast<reg_type>(gpio_moder_mode0_msk);

        static constexpr auto port_mode_register         = static_cast<addr_type>(port + 0x00ULL);
        static constexpr auto output_type_register       = static_cast<addr_type>(port + 0x04ULL);
        static constexpr auto output_speed_register      = static_cast<addr_type>(port + 0x08ULL);
        static constexpr auto pull_up_pull_down_register = static_cast<addr_type>(port + 0x0CULL);
        static constexpr auto input_data_register        = static_cast<addr_type>(port + 0x10ULL);
        static constexpr auto output_data_register       = static_cast<addr_type>(port + 0x14ULL);
      };
    }
  }

#endif // MCAL_PORT_2022_08_03_H_
