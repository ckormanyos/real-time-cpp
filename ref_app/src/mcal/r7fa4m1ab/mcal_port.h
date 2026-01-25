///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2026.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_PORT_2025_02_22_H
  #define MCAL_PORT_2025_02_22_H

  #include <mcal_reg.h>

  #include <cstdint>

  namespace mcal
  {
    namespace port
    {
      typedef void config_type;

      void init(const config_type*);

      template<const std::uint32_t PfsBase>
      class port_pin
      {
      private:
        static constexpr auto my_pfs_base() -> std::uint32_t { return PfsBase; }

      public:
        static auto set_direction_output() -> void
        {
          // Configure the pin as output.
          // Disable register write protection for PFS.
          // PMISC->PWPR.bit.B0WI  = 0;
          // PMISC->PWPR.bit.PFSWE = 1;
          // PFS->PxxxPFS.bit.PDR  = 1;

          mcal::reg::reg_access_static<std::uint32_t, std::uint8_t, mcal::reg::pmisc_pwpr, UINT8_C(7)>::bit_clr();
          mcal::reg::reg_access_static<std::uint32_t, std::uint8_t, mcal::reg::pmisc_pwpr, UINT8_C(6)>::bit_set();
          mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, my_pfs_base(), UINT32_C(2)>::bit_set();
        }

        static auto set_direction_input() -> void
        {
        }

        static auto set_pin_high() -> void
        {
        }

        static auto set_pin_low() -> void
        {
        }

        static auto read_input_value() -> bool
        {
          return false;
        }

        static auto toggle_pin() -> void
        {
          // PFS->P111PFS.bit.PODR ^= 1;
          mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, my_pfs_base(), UINT32_C(0)>::bit_not();
        }
      };
    }
  }

#endif // MCAL_PORT_2025_02_22_H
