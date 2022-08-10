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
        static constexpr auto gpio_mode_pos            = static_cast<std::uint32_t>(0ULL);
        static constexpr auto gpio_mode                = static_cast<std::uint32_t>(0x3ULL << gpio_mode_pos);
        static constexpr auto mode_input               = static_cast<std::uint32_t>(0x0ULL << gpio_mode_pos);
        static constexpr auto mode_output              = static_cast<std::uint32_t>(0x1ULL << gpio_mode_pos);
        static constexpr auto mode_af                  = static_cast<std::uint32_t>(0x2ULL << gpio_mode_pos);
        static constexpr auto mode_analog              = static_cast<std::uint32_t>(0x3ULL << gpio_mode_pos);
        static constexpr auto output_type_pos          = static_cast<std::uint32_t>(4ULL);
        static constexpr auto output_type              = static_cast<std::uint32_t>(0x1ULL << output_type_pos);
        static constexpr auto output_pp                = static_cast<std::uint32_t>(0x0ULL << output_type_pos);
        static constexpr auto output_od                = static_cast<std::uint32_t>(0x1ULL << output_type_pos);

        static constexpr auto gpio_speed_freq_low      = static_cast<std::uint32_t>(0x00000000U);             // Low speed
        static constexpr auto gpio_mode_input          = static_cast<std::uint32_t>(mode_input);              // Input Floating Mode
        static constexpr auto gpio_mode_output_pp      = static_cast<std::uint32_t>(mode_output | output_pp); // Output Push Pull Mode
        static constexpr auto gpio_nopull              = static_cast<std::uint32_t>(0x00000000U);             // No Pull-up or Pull-down activation

        static constexpr auto gpio_ospeedr_ospeed0_pos = static_cast<std::uint32_t>(0ull);
        static constexpr auto gpio_ospeedr_ospeed0_msk = static_cast<std::uint32_t>(0x3ul << gpio_ospeedr_ospeed0_pos);     // 0x00000003
        static constexpr auto gpio_ospeedr_ospeed0     = static_cast<std::uint32_t>(gpio_ospeedr_ospeed0_msk);

        static constexpr auto gpio_otyper_ot0_pos      = static_cast<std::uint32_t>(0ull);
        static constexpr auto gpio_otyper_ot0_msk      = static_cast<std::uint32_t>(0x1ul << gpio_otyper_ot0_pos);          // 0x00000001
        static constexpr auto gpio_otyper_ot0          = static_cast<std::uint32_t>(gpio_otyper_ot0_msk);

        static constexpr auto gpio_pupdr_pupd0_pos     = static_cast<std::uint32_t>(0ull);
        static constexpr auto gpio_pupdr_pupd0_msk     = static_cast<std::uint32_t>(0x3ull << gpio_pupdr_pupd0_pos);        // 0x00000003
        static constexpr auto gpio_pupdr_pupd0         = static_cast<std::uint32_t>(gpio_pupdr_pupd0_msk);

        static constexpr auto gpio_moder_mode0_pos     = static_cast<std::uint32_t>(0ull);
        static constexpr auto gpio_moder_mode0_msk     = static_cast<std::uint32_t>(0x3ull << gpio_moder_mode0_pos);        // 0x00000003
        static constexpr auto gpio_moder_mode0         = static_cast<std::uint32_t>(gpio_moder_mode0_msk);

      public:
        static void set_direction_output()
        {
          // Set the port pin control bits.
          std::uint32_t temp { };
          
          // Select the lowest output speed.
          temp = mcal::reg::reg_access_static<addr_type,
                                              reg_type,
                                              output_speed_register>::reg_get();
          temp &= ~(gpio_ospeedr_ospeed0 << (bpos * 2U));
          temp |= (gpio_speed_freq_low << (bpos * 2U));
          mcal::reg::reg_access_dynamic<addr_type,
                                        reg_type>::reg_set(output_speed_register, temp);

          // Configure the IO Output Type
          temp =  mcal::reg::reg_access_static<addr_type,
                                       reg_type,
                                       output_type_register>::reg_get();
          temp &= ~(gpio_otyper_ot0 << bpos) ;
          temp |= (((gpio_mode_output_pp & output_type) >> output_type_pos) << bpos);
          mcal::reg::reg_access_dynamic<addr_type,
                                        reg_type>::reg_set(output_type_register, temp);

          // Activate the Pull-up or Pull down resistor for the current IO
          temp =  mcal::reg::reg_access_static<addr_type,
                                       reg_type,
                                       pull_up_pull_down_register>::reg_get();
          temp &= ~(gpio_pupdr_pupd0 << (bpos * 2u));
          temp |= (gpio_nopull << (bpos * 2u));
          mcal::reg::reg_access_dynamic<addr_type,
                                        reg_type>::reg_set(pull_up_pull_down_register, temp);


          // Configure IO Direction mode (Input, Output, Alternate or Analog)
          temp =  mcal::reg::reg_access_static<addr_type,
                                       reg_type,
                                       port_mode_register>::reg_get();
          temp &= ~(gpio_moder_mode0 << (bpos * 2u));
          temp |= ((gpio_mode_output_pp & gpio_mode) << (bpos * 2U));
          mcal::reg::reg_access_dynamic<addr_type,
                                        reg_type>::reg_set(port_mode_register, temp);
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
        static constexpr addr_type port_mode_register         = addr_type(port + 0x00UL);
        static constexpr addr_type output_type_register       = addr_type(port + 0x04UL);
        static constexpr addr_type output_speed_register      = addr_type(port + 0x08UL);
        static constexpr addr_type pull_up_pull_down_register = addr_type(port + 0x0CUL);
        static constexpr addr_type input_data_register        = addr_type(port + 0x10UL);
        static constexpr addr_type output_data_register       = addr_type(port + 0x14UL);
      };
    }
  }

#endif // MCAL_PORT_2022_08_03_H_
