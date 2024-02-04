///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2023.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_PORT_2023_07_04_H
  #define MCAL_PORT_2023_07_04_H

  #include <mcal_reg.h>

  // NOTE: The following table reproduces the layout information of Teensy 4.0.
  // See also: https://github.com/KurtE/TeensyDocuments
  // 
  // Teensy-Pin  "ARDUINO"-Pin    Name       GPIO
  //  1                          AD_B0_02    1.02
  //  0                          AD_B0_03    1.03
  // 24           A10            AD_B0_12    1.12
  // 25           A11            AD_B0_13    1.13
  // 19           A5             AD_B1_00    1.16
  // 18           A4             AD_B1_01    1.17
  // 14           A0             AD_B1_02    1.18
  // 15           A1             AD_B1_03    1.19
  // 17           A3             AD_B1_06    1.22
  // 16           A2             AD_B1_07    1.23
  // 22           A8             AD_B1_08    1.24
  // 23           A9             AD_B1_09    1.25
  // 20           A6             AD_B1_10    1.26
  // 21           A7             AD_B1_11    1.27
  // 26           A12            AD_B1_14    1.30
  // 27           A13            AD_B1_15    1.31
  // 10                          B0_00       2.00
  // 12                          B0_01       2.01
  // 11                          B0_02       2.02
  // 13                          B0_03       2.03
  //  6                          B0_10       2.10
  //  9                          B0_11       2.11
  // 32                          B0_12       2.12
  //  8                          B1_00       2.16
  //  7                          B1_01       2.17
  // 37                          SD_B0_00    3.12
  // 36                          SD_B0_01    3.13
  // 35                          SD_B0_02    3.14
  // 34                          SD_B0_03    3.15
  // 39                          SD_B0_04    3.16
  // 38                          SD_B0_05    3.17
  // 28                          EMC_32      3.18
  // 31                          EMC_36      3.22
  // 30                          EMC_37      3.23
  //  2                          EMC_04      4.04
  //  3                          EMC_05      4.05
  //  4                          EMC_06      4.06
  // 33                          EMC_07      4.07
  //  5                          EMC_08      4.08
  // 29                          EMC_31      4.31

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
          mcal::reg::reg_access_static<addr_type, reg_type, gdir, bpos>::bit_set();
        }

        static auto set_direction_input() -> void
        {
          mcal::reg::reg_access_static<addr_type, reg_type, gdir, bpos>::bit_clr();
        }

        static void set_pin_high()
        {
          mcal::reg::reg_access_static<addr_type, reg_type, dr_set, bpos>::bit_set();
        }

        static auto set_pin_low() -> void
        {
          mcal::reg::reg_access_static<addr_type, reg_type, dr_clear, bpos>::bit_set();
        }

        static auto read_input_value() -> bool
        {
          // TBD: Implement digital port-pin input-read.
          return false;
        }

        static auto toggle_pin() -> void
        {
          mcal::reg::reg_access_static<addr_type, reg_type, dr_toggle, bpos>::bit_set();
        }

      private:
        static constexpr auto dr        = static_cast<reg_type>(port + static_cast<reg_type>(0x00));
        static constexpr auto gdir      = static_cast<reg_type>(port + static_cast<reg_type>(0x04));
        static constexpr auto psr       = static_cast<reg_type>(port + static_cast<reg_type>(0x08));
        static constexpr auto icr1      = static_cast<reg_type>(port + static_cast<reg_type>(0x0C));
        static constexpr auto icr2      = static_cast<reg_type>(port + static_cast<reg_type>(0x10));
        static constexpr auto imr       = static_cast<reg_type>(port + static_cast<reg_type>(0x14));
        static constexpr auto isr       = static_cast<reg_type>(port + static_cast<reg_type>(0x18));
        static constexpr auto edge_sel  = static_cast<reg_type>(port + static_cast<reg_type>(0x1C));
        static constexpr auto unused_25 = static_cast<reg_type>(port + static_cast<reg_type>(0x20));
        static constexpr auto dr_set    = static_cast<reg_type>(port + static_cast<reg_type>(0x84));
        static constexpr auto dr_clear  = static_cast<reg_type>(port + static_cast<reg_type>(0x88));
        static constexpr auto dr_toggle = static_cast<reg_type>(port + static_cast<reg_type>(0x8C));
      };
    }
  }

#endif // MCAL_PORT_2022_08_03_H_
