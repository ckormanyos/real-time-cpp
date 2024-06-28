///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2022 - 2024.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_PORT_2022_12_16_H
  #define MCAL_PORT_2022_12_16_H

  #include <mcal_reg.h>

  #include <cstdint>

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
          // Output mode, maximum speed: 50MHz.
          // GPIOA->CFGLR.bit.MODE0 = 3u;
          mcal::reg::reg_access_static<std::uint32_t,
                                       std::uint32_t,
                                       port_cfg_lo_register,
                                       UINT32_C(3)>::template reg_msk<UINT32_C(0x3) << 0U>();

          // General push-pull output mode.
          // GPIOC->CFGLR.bit.CNF0  = 1u;
          mcal::reg::reg_access_static<std::uint32_t,
                                       std::uint32_t,
                                       port_cfg_lo_register,
                                       UINT32_C(1)>::template reg_msk<UINT32_C(0x3) << 2U>();
        }

        static void set_direction_input()
        {
        }

        static void set_pin_high()
        {
          // Output a logic high.
          // GPIOA->OUTDR.bit.ODR0 = 1u;
          mcal::reg::reg_access_static<std::uint32_t,
                                       std::uint32_t,
                                       output_data_register,
                                       bpos>::bit_set();
        }

        static void set_pin_low()
        {
          // Output a logic low.
          // GPIOA->OUTDR.bit.ODR0 = 0u;
          mcal::reg::reg_access_static<std::uint32_t,
                                       std::uint32_t,
                                       output_data_register,
                                       bpos>::bit_clr();
        }

        static bool read_input_value()
        {
          return false;
        }

        static void toggle_pin()
        {
          // Toggle the output.
          // GPIOA->OUTDR.bit.ODR0 ^= 0u;
          mcal::reg::reg_access_static<std::uint32_t,
                                       std::uint32_t,
                                       output_data_register,
                                       bpos>::bit_not();
        }

      private:
        static constexpr addr_type port_cfg_lo_register       { static_cast<addr_type>(port + 0x00UL) }; // GPIOn_CFGLR
        static constexpr addr_type port_cfg_hi_register       { static_cast<addr_type>(port + 0x04UL) }; // GPIOn_CFGHR
        static constexpr addr_type input_data_register        { static_cast<addr_type>(port + 0x08UL) }; // GPIOn_INDR
        static constexpr addr_type output_data_register       { static_cast<addr_type>(port + 0x0CUL) }; // GPIOn_OUTDR
        static constexpr addr_type bit_set_reset_register     { static_cast<addr_type>(port + 0x10UL) }; // GPIOn_BSHR
        static constexpr addr_type bit_reset_register         { static_cast<addr_type>(port + 0x14UL) }; // GPIOn_BCR
        static constexpr addr_type cfg_lock_register          { static_cast<addr_type>(port + 0x18UL) }; // GPIOn_LCKR
      };
    }
  }

#endif // MCAL_PORT_2022_12_16_H
