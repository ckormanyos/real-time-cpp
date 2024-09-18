///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2024.
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
      constexpr std::uint32_t scs_base                         { UINT32_C(0xE000E000) };
      constexpr std::uint32_t nvic_base                        { scs_base + UINT32_C(0x00000100) };

      // NVIC registers.
      constexpr std::uint32_t nvic_icpr                        { nvic_base + UINT32_C(0x00000180) };

      // SCnSCB registers.
      constexpr std::uint32_t scnscb_reserved0                 { scs_base + UINT32_C(0x00000000) };
      constexpr std::uint32_t scnscb_ictr                      { scs_base + UINT32_C(0x00000004) };
      constexpr std::uint32_t scnscb_actlr                     { scs_base + UINT32_C(0x00000008) };
      constexpr std::uint32_t scnscb_cppwr                     { scs_base + UINT32_C(0x0000000C) };

      // Reset registers.
      constexpr std::uint32_t hw_per_resets_resets_base        { UINT32_C(0x40020000) };
      constexpr std::uint32_t hw_per_resets_reset              { hw_per_resets_resets_base + UINT32_C(0x00000000) };
      constexpr std::uint32_t hw_per_resets_wdsel              { hw_per_resets_resets_base + UINT32_C(0x00000004) };
      constexpr std::uint32_t hw_per_resets_reset_done         { hw_per_resets_resets_base + UINT32_C(0x00000008) };

      // PLL registers.
      constexpr std::uint32_t hw_per_pll_sys_base              { UINT32_C(0x40050000) };
      constexpr std::uint32_t hw_per_pll_sys_cs                { hw_per_pll_sys_base + UINT32_C(0x00000000) };
      constexpr std::uint32_t hw_per_pll_sys_pwr               { hw_per_pll_sys_base + UINT32_C(0x00000004) };
      constexpr std::uint32_t hw_per_pll_sys_fbdiv_int         { hw_per_pll_sys_base + UINT32_C(0x00000008) };
      constexpr std::uint32_t hw_per_pll_sys_prim              { hw_per_pll_sys_base + UINT32_C(0x0000000C) };
      constexpr std::uint32_t hw_per_pll_sys_intr              { hw_per_pll_sys_base + UINT32_C(0x00000010) };
      constexpr std::uint32_t hw_per_pll_sys_inte              { hw_per_pll_sys_base + UINT32_C(0x00000014) };
      constexpr std::uint32_t hw_per_pll_sys_intf              { hw_per_pll_sys_base + UINT32_C(0x00000018) };
      constexpr std::uint32_t hw_per_pll_sys_ints              { hw_per_pll_sys_base + UINT32_C(0x0000001C) };

      // Clock registers.
      constexpr std::uint32_t hw_per_clocks_base               { UINT32_C(0x40010000) };
      constexpr std::uint32_t hw_per_clocks_clk_ref_ctrl       { hw_per_clocks_base + UINT32_C(0x00000030) };
      constexpr std::uint32_t hw_per_clocks_clk_ref_div        { hw_per_clocks_base + UINT32_C(0x00000034) };
      constexpr std::uint32_t hw_per_clocks_clk_ref_selected   { hw_per_clocks_base + UINT32_C(0x00000038) };
      constexpr std::uint32_t hw_per_clocks_clk_sys_ctrl       { hw_per_clocks_base + UINT32_C(0x0000003C) };
      constexpr std::uint32_t hw_per_clocks_clk_sys_div        { hw_per_clocks_base + UINT32_C(0x00000040) };
      constexpr std::uint32_t hw_per_clocks_clk_sys_selected   { hw_per_clocks_base + UINT32_C(0x00000044) };
      constexpr std::uint32_t hw_per_clocks_clk_peri_ctrl      { hw_per_clocks_base + UINT32_C(0x00000048) };

      // PSM registers.
      constexpr std::uint32_t hw_per_psm_base                  { UINT32_C(0x40018000) };
      constexpr std::uint32_t psm_base                         { UINT32_C(0x40018000) };
      constexpr std::uint32_t psm_frce_on                      { psm_base + UINT32_C(0x00000000) };
      constexpr std::uint32_t psm_frce_off                     { psm_base + UINT32_C(0x00000004) };
      constexpr std::uint32_t psm_wdsel                        { psm_base + UINT32_C(0x00000008) };
      constexpr std::uint32_t psm_done                         { psm_base + UINT32_C(0x0000000C) };

      // PPB registers.
      constexpr std::uint32_t hw_per_ppb_base                  { UINT32_C(0xE0000000) };
      constexpr std::uint32_t hw_per_ppb_cpacr                 { hw_per_ppb_base + UINT32_C(0x0000ED88) };
      constexpr std::uint32_t hw_per_ppb_nsacr                 { hw_per_ppb_base + UINT32_C(0x0000ED8C) };

      // I/O-Bank registers.
      constexpr std::uint32_t pads_bank0_base                  { UINT32_C(0x40038000) };
      constexpr std::uint32_t pads_bank0_gpio                  { UINT32_C(0x40038004) };

      constexpr std::uint32_t io_bank0_base                    { UINT32_C(0x40028000) };
      constexpr std::uint32_t io_bank0_status_base             { io_bank0_base + UINT32_C(0x00000000) };

      constexpr std::uint32_t hw_per_io_bank0                  { io_bank0_base };

      constexpr std::uint32_t hw_per_xosc_base                 { UINT32_C(0x40048000) };
      constexpr std::uint32_t hw_per_xosc_control              { UINT32_C(0x40048000) };
      constexpr std::uint32_t hw_per_xosc_status               { UINT32_C(0x40048004) };
      constexpr std::uint32_t hw_per_xosc_dormant              { UINT32_C(0x40048008) };
      constexpr std::uint32_t hw_per_xosc_startup              { UINT32_C(0x4004800C) };
      constexpr std::uint32_t hw_per_xosc_count                { UINT32_C(0x40048010) };

      // Single-instruction registers.
      constexpr std::uint32_t sio_base                         { UINT32_C(0xD0000000) };
      constexpr std::uint32_t sio_cpuid                        { sio_base + UINT32_C(0x00000000) };
      constexpr std::uint32_t sio_gpio_out_set                 { sio_base + UINT32_C(0x00000018) };
      constexpr std::uint32_t sio_gpio_out_clr                 { sio_base + UINT32_C(0x00000020) };
      constexpr std::uint32_t sio_gpio_out_xor                 { sio_base + UINT32_C(0x00000028) };
      constexpr std::uint32_t sio_gpio_oe_set                  { sio_base + UINT32_C(0x00000038) };
      constexpr std::uint32_t sio_gpio_oe_clr                  { sio_base + UINT32_C(0x00000040) };
      constexpr std::uint32_t sio_fifo_st                      { sio_base + UINT32_C(0x00000050) };
      constexpr std::uint32_t sio_fifo_wr                      { sio_base + UINT32_C(0x00000054) };
      constexpr std::uint32_t sio_fifo_rd                      { sio_base + UINT32_C(0x00000058) };

      constexpr std::uint32_t hw_per_sio_base                  { sio_base };
    }
  }

  #include <mcal/mcal_reg_access_dynamic.h>
  #include <mcal/mcal_reg_access_static.h>

#endif // MCAL_REG_2010_04_10_H
