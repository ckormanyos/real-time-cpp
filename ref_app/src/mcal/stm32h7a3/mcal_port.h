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
        static constexpr auto GPIO_MODE_Pos            = static_cast<std::uint32_t>(0ULL);
        static constexpr auto GPIO_MODE                = static_cast<std::uint32_t>(0x3ULL << GPIO_MODE_Pos);
        static constexpr auto MODE_INPUT               = static_cast<std::uint32_t>(0x0ULL << GPIO_MODE_Pos);
        static constexpr auto MODE_OUTPUT              = static_cast<std::uint32_t>(0x1ULL << GPIO_MODE_Pos);
        static constexpr auto MODE_AF                  = static_cast<std::uint32_t>(0x2ULL << GPIO_MODE_Pos);
        static constexpr auto MODE_ANALOG              = static_cast<std::uint32_t>(0x3ULL << GPIO_MODE_Pos);
        static constexpr auto OUTPUT_TYPE_Pos          = static_cast<std::uint32_t>(4ULL);
        static constexpr auto OUTPUT_TYPE              = static_cast<std::uint32_t>(0x1ULL << OUTPUT_TYPE_Pos);
        static constexpr auto OUTPUT_PP                = static_cast<std::uint32_t>(0x0ULL << OUTPUT_TYPE_Pos);
        static constexpr auto OUTPUT_OD                = static_cast<std::uint32_t>(0x1ULL << OUTPUT_TYPE_Pos);

        static constexpr auto GPIO_SPEED_FREQ_LOW      = static_cast<std::uint32_t>(0x00000000U);             // Low speed
        static constexpr auto GPIO_MODE_INPUT          = static_cast<std::uint32_t>(MODE_INPUT);              // Input Floating Mode
        static constexpr auto GPIO_MODE_OUTPUT_PP      = static_cast<std::uint32_t>(MODE_OUTPUT | OUTPUT_PP); // Output Push Pull Mode
        static constexpr auto GPIO_NOPULL              = static_cast<std::uint32_t>(0x00000000U);             // No Pull-up or Pull-down activation

        static constexpr auto GPIO_OSPEEDR_OSPEED0_Pos = static_cast<std::uint32_t>(0ULL);
        static constexpr auto GPIO_OSPEEDR_OSPEED0_Msk = static_cast<std::uint32_t>(0x3UL << GPIO_OSPEEDR_OSPEED0_Pos);     // 0x00000003
        static constexpr auto GPIO_OSPEEDR_OSPEED0     = static_cast<std::uint32_t>(GPIO_OSPEEDR_OSPEED0_Msk);

        static constexpr auto GPIO_OTYPER_OT0_Pos      = static_cast<std::uint32_t>(0ULL);
        static constexpr auto GPIO_OTYPER_OT0_Msk      = static_cast<std::uint32_t>(0x1UL << GPIO_OTYPER_OT0_Pos);          // 0x00000001
        static constexpr auto GPIO_OTYPER_OT0          = static_cast<std::uint32_t>(GPIO_OTYPER_OT0_Msk);

        static constexpr auto GPIO_PUPDR_PUPD0_Pos     = static_cast<std::uint32_t>(0ULL);
        static constexpr auto GPIO_PUPDR_PUPD0_Msk     = static_cast<std::uint32_t>(0x3ULL << GPIO_PUPDR_PUPD0_Pos);        // 0x00000003
        static constexpr auto GPIO_PUPDR_PUPD0         = static_cast<std::uint32_t>(GPIO_PUPDR_PUPD0_Msk);

        static constexpr auto GPIO_MODER_MODE0_Pos     = static_cast<std::uint32_t>(0ULL);
        static constexpr auto GPIO_MODER_MODE0_Msk     = static_cast<std::uint32_t>(0x3ULL << GPIO_MODER_MODE0_Pos);        // 0x00000003
        static constexpr auto GPIO_MODER_MODE0         = static_cast<std::uint32_t>(GPIO_MODER_MODE0_Msk);

      public:
        static void set_direction_output()
        {
          // Set the port pin control bits.
          std::uint32_t temp { };
          
          // Select the lowest output speed.
          temp = mcal::reg::reg_access_static<addr_type,
                                              reg_type,
                                              output_speed_register>::reg_get();
          temp &= ~(GPIO_OSPEEDR_OSPEED0 << (bpos * 2U));
          temp |= (GPIO_SPEED_FREQ_LOW << (bpos * 2U));
          mcal::reg::reg_access_dynamic<addr_type,
                                        reg_type>::reg_set(output_speed_register, temp);

          // Configure the IO Output Type
          temp =  mcal::reg::reg_access_static<addr_type,
                                       reg_type,
                                       output_type_register>::reg_get();
          temp &= ~(GPIO_OTYPER_OT0 << bpos) ;
          temp |= (((GPIO_MODE_OUTPUT_PP & OUTPUT_TYPE) >> OUTPUT_TYPE_Pos) << bpos);
          mcal::reg::reg_access_dynamic<addr_type,
                                        reg_type>::reg_set(output_type_register, temp);

          // Activate the Pull-up or Pull down resistor for the current IO
          temp =  mcal::reg::reg_access_static<addr_type,
                                       reg_type,
                                       pull_up_pull_down_register>::reg_get();
          temp &= ~(GPIO_PUPDR_PUPD0 << (bpos * 2U));
          temp |= (GPIO_NOPULL << (bpos * 2U));
          mcal::reg::reg_access_dynamic<addr_type,
                                        reg_type>::reg_set(pull_up_pull_down_register, temp);


          // Configure IO Direction mode (Input, Output, Alternate or Analog)
          temp =  mcal::reg::reg_access_static<addr_type,
                                       reg_type,
                                       port_mode_register>::reg_get();
          temp &= ~(GPIO_MODER_MODE0 << (bpos * 2U));
          temp |= ((GPIO_MODE_OUTPUT_PP & GPIO_MODE) << (bpos * 2U));
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
