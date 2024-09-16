///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2024.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_REG_2010_04_10_H
  #define MCAL_REG_2010_04_10_H

  #include <cstdint>

  namespace mcal
  {
    namespace reg
    {
      // Global base addresses.
      constexpr std::uint32_t scs_base                  { UINT32_C(0xE000E000) };

      // SCnSCB registers.
      constexpr std::uint32_t scnscb_reserved0        { scs_base + UINT32_C(0x00000000) };
      constexpr std::uint32_t scnscb_ictr             { scs_base + UINT32_C(0x00000004) };
      constexpr std::uint32_t scnscb_actlr            { scs_base + UINT32_C(0x00000008) };
      constexpr std::uint32_t scnscb_cppwr            { scs_base + UINT32_C(0x0000000C) };

      // PSM registers.
      constexpr std::uint32_t psm_base                  { UINT32_C(0x40018000) };
      constexpr std::uint32_t psm_frce_on               { psm_base + UINT32_C(0x00000000) };
      constexpr std::uint32_t psm_frce_off              { psm_base + UINT32_C(0x00000004) };
      constexpr std::uint32_t psm_wdsel                 { psm_base + UINT32_C(0x00000008) };
      constexpr std::uint32_t psm_done                  { psm_base + UINT32_C(0x0000000C) };

      // Single-instruction registers.
      constexpr std::uint32_t sio_base                  { UINT32_C(0xD0000000) };
      constexpr std::uint32_t sio_cpuid                 { sio_base + UINT32_C(0x00000000) };
      constexpr std::uint32_t sio_gpio_out_set          { sio_base + UINT32_C(0x00000018) };
      constexpr std::uint32_t sio_gpio_out_clr          { sio_base + UINT32_C(0x00000020) };
      constexpr std::uint32_t sio_gpio_out_xor          { sio_base + UINT32_C(0x00000028) };
      constexpr std::uint32_t sio_gpio_oe_set           { sio_base + UINT32_C(0x00000038) };
      constexpr std::uint32_t sio_gpio_oe_clr           { sio_base + UINT32_C(0x00000040) };
      constexpr std::uint32_t sio_fifo_st               { sio_base + UINT32_C(0x00000050) };
      constexpr std::uint32_t sio_fifo_wr               { sio_base + UINT32_C(0x00000054) };
      constexpr std::uint32_t sio_fifo_rd               { sio_base + UINT32_C(0x00000058) };

      constexpr std::uint32_t hw_per_sio_base           { sio_base };

      // I/O-Bank registers.
      constexpr std::uint32_t io_bank0_base             { UINT32_C(0x40028000) };
      constexpr std::uint32_t io_bank0_status_base      { io_bank0_base + UINT32_C(0x00000000) };

      constexpr std::uint32_t pads_bank0_base           { UINT32_C(0x40038000) };
      constexpr std::uint32_t pads_bank0_gpio           { UINT32_C(0x40038004) };

      constexpr std::uint32_t hw_per_io_bank0           { io_bank0_base };

      constexpr std::uint32_t hw_per_psm_base           { UINT32_C(0x40018000) };

      constexpr std::uint32_t hw_per_resets_resets_base { UINT32_C(0x40020000) };
      constexpr std::uint32_t hw_per_resets_reset       { hw_per_resets_resets_base + UINT32_C(0x00000000) };
      constexpr std::uint32_t hw_per_resets_wdsel       { hw_per_resets_resets_base + UINT32_C(0x00000004) };
      constexpr std::uint32_t hw_per_resets_reset_done  { hw_per_resets_resets_base + UINT32_C(0x00000008) };
    }
  }

  #include <mcal/mcal_reg_access_dynamic.h>
  #include <mcal/mcal_reg_access_static.h>

#endif // MCAL_REG_2010_04_10_H
