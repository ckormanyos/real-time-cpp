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
          // First (re-)set the pin as input.
          set_direction_input();

          // Set the port pin control bits.

          // Select the fastest output speed (MODx = 11b).
          mcal::reg::reg_access_static<std::uint32_t,
                                       std::uint32_t,
                                       port_cfg_my_register,
                                       UINT32_C(3) << static_cast<unsigned>(bpos_shift + 0UL)>::template reg_msk<UINT32_C(0x3) << static_cast<unsigned>(bpos_shift + 0UL)>();

          // Set general push-pull output mode (CNFx = 00b).
          mcal::reg::reg_access_static<std::uint32_t,
                                       std::uint32_t,
                                       port_cfg_my_register,
                                       UINT32_C(0) << static_cast<unsigned>(bpos_shift + 2UL)>::template reg_msk<UINT32_C(0x3) << static_cast<unsigned>(bpos_shift + 2UL)>();
        }

        static void set_direction_input()
        {
          // Select input mode (MODx = 00b).
          mcal::reg::reg_access_static<std::uint32_t,
                                       std::uint32_t,
                                       port_cfg_my_register,
                                       UINT32_C(0) << static_cast<unsigned>(bpos_shift + 0UL)>::template reg_msk<UINT32_C(0x3) << static_cast<unsigned>(bpos_shift + 0UL)>();

          // Set for Floating input mode (CNFx = 01b, with MODx = 00b).
          mcal::reg::reg_access_static<std::uint32_t,
                                       std::uint32_t,
                                       port_cfg_my_register,
                                       UINT32_C(1) << static_cast<unsigned>(bpos_shift + 2UL)>::template reg_msk<UINT32_C(0x3) << static_cast<unsigned>(bpos_shift + 2UL)>();
        }

        static void set_pin_high()
        {
          // Output a logic high.
          mcal::reg::reg_access_static<std::uint32_t,
                                       std::uint32_t,
                                       bit_set_reset_register,
                                       bpos>::bit_set();
        }

        static void set_pin_low()
        {
          // Output a logic low.
          mcal::reg::reg_access_static<std::uint32_t,
                                       std::uint32_t,
                                       bit_reset_register,
                                       bpos>::bit_set();
        }

        static bool read_input_value()
        {
          return mcal::reg::reg_access_static<std::uint32_t,
                                              std::uint32_t,
                                              input_data_register,
                                              bpos>::bit_get();
        }

        static void toggle_pin()
        {
          // Toggle the output.
          mcal::reg::reg_access_static<std::uint32_t,
                                       std::uint32_t,
                                       output_data_register,
                                       bpos>::bit_not();
        }

      private:
        static constexpr reg_type  bpos_shift { static_cast<reg_type>(bpos * 4UL) % 32UL };

        static constexpr addr_type port_cfg_lo_register       { static_cast<addr_type>(port + 0x00UL) }; // GPIOn_CFGLR
        static constexpr addr_type port_cfg_hi_register       { static_cast<addr_type>(port + 0x04UL) }; // GPIOn_CFGHR
        static constexpr addr_type input_data_register        { static_cast<addr_type>(port + 0x08UL) }; // GPIOn_INDR
        static constexpr addr_type output_data_register       { static_cast<addr_type>(port + 0x0CUL) }; // GPIOn_OUTDR
        static constexpr addr_type bit_set_reset_register     { static_cast<addr_type>(port + 0x10UL) }; // GPIOn_BSHR
        static constexpr addr_type bit_reset_register         { static_cast<addr_type>(port + 0x14UL) }; // GPIOn_BCR
        static constexpr addr_type cfg_lock_register          { static_cast<addr_type>(port + 0x18UL) }; // GPIOn_LCKR

        static constexpr addr_type port_cfg_my_register       { (bpos < 8U) ? port_cfg_lo_register : port_cfg_hi_register};
      };
    }
  }

#endif // MCAL_PORT_2022_12_16_H
