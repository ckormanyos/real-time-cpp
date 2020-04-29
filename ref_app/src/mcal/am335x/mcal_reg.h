///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2013 - 2020.
//  Copyright Michael Schnerr 2011 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_REG_2010_04_10_H_
  #define MCAL_REG_2010_04_10_H_

  #include <cstdint>

  namespace mcal
  {
    namespace reg
    {
      // Base addresses.
      constexpr std::uint32_t l4_wkup_base          = UINT32_C(0x44C00000);                // Wakeup register area base address.
      constexpr std::uint32_t l4_per_base           = UINT32_C(0x48000000);                // Peripheral register area base address.

      constexpr std::uint32_t cm_per_base           = UINT32_C(l4_wkup_base + 0x200000);   // Clock module peripheral base address.
      constexpr std::uint32_t cm_wkup_base          = UINT32_C(l4_wkup_base + 0x200400);   // Clock module wakup base address.
      constexpr std::uint32_t cm_dpll_base          = UINT32_C(l4_wkup_base + 0x200500);   // Clock module DPLL base address.

      constexpr std::uint32_t control_base          = UINT32_C(l4_wkup_base + 0x210000);   // System control base address.

      constexpr std::uint32_t dmtimer7_base         = UINT32_C(l4_per_base  + 0x04A000);   // DM Timer7 base address.

      constexpr std::uint32_t gpio0_base            = UINT32_C(l4_wkup_base + 0x207000);   // GPIO0 base address.
      constexpr std::uint32_t gpio1_base            = UINT32_C(l4_per_base  + 0x04C000);   // GPIO1 base address.
      constexpr std::uint32_t gpio2_base            = UINT32_C(l4_per_base  + 0x1AC000);   // GPIO2 base address.
      constexpr std::uint32_t gpio3_base            = UINT32_C(l4_per_base  + 0x1AE000);   // GPIO3 base address.

      constexpr std::uint32_t wdt1_base             = UINT32_C(l4_wkup_base + 0x235000);   // Watchdog 1 base address.

      constexpr std::uint32_t intc_base             = UINT32_C(l4_per_base  + 0x200000);   // Interrupt controller base address.

      // Clock module registers.
      namespace cm_per
      {
        constexpr std::uint32_t l4ls_clkstctrl      = UINT32_C(cm_per_base + 0x000);  // 0x000
        constexpr std::uint32_t l3s_clkstctrl       = UINT32_C(cm_per_base + 0x004);  // 0x004
        constexpr std::uint32_t reserved0           = UINT32_C(cm_per_base + 0x008);  // 0x008
        constexpr std::uint32_t l3_clkstctrl        = UINT32_C(cm_per_base + 0x00C);  // 0x00C
        constexpr std::uint32_t reserved1           = UINT32_C(cm_per_base + 0x010);  // 0x010
        constexpr std::uint32_t cpgmac0_clkctrl     = UINT32_C(cm_per_base + 0x014);  // 0x014
        constexpr std::uint32_t lcdc_clkctrl        = UINT32_C(cm_per_base + 0x018);  // 0x018
        constexpr std::uint32_t usb0_clkctrl        = UINT32_C(cm_per_base + 0x01C);  // 0x01C
        constexpr std::uint32_t reserved2           = UINT32_C(cm_per_base + 0x020);  // 0x020
        constexpr std::uint32_t tptc0_clkctrl       = UINT32_C(cm_per_base + 0x024);  // 0x024
        constexpr std::uint32_t emif_clkctrl        = UINT32_C(cm_per_base + 0x028);  // 0x028
        constexpr std::uint32_t ocmcram_clkctrl     = UINT32_C(cm_per_base + 0x02C);  // 0x02C
        constexpr std::uint32_t gpmc_clkctrl        = UINT32_C(cm_per_base + 0x030);  // 0x030
        constexpr std::uint32_t mcasp0_clkctrl      = UINT32_C(cm_per_base + 0x034);  // 0x034
        constexpr std::uint32_t uart5_clkctrl       = UINT32_C(cm_per_base + 0x038);  // 0x038
        constexpr std::uint32_t mmc0_clkctrl        = UINT32_C(cm_per_base + 0x03C);  // 0x03C
        constexpr std::uint32_t elm_clkctrl         = UINT32_C(cm_per_base + 0x040);  // 0x040
        constexpr std::uint32_t i2c2_clkctrl        = UINT32_C(cm_per_base + 0x044);  // 0x044
        constexpr std::uint32_t i2c1_clkctrl        = UINT32_C(cm_per_base + 0x048);  // 0x048
        constexpr std::uint32_t spi0_clkctrl        = UINT32_C(cm_per_base + 0x04C);  // 0x04C
        constexpr std::uint32_t spi1_clkctrl        = UINT32_C(cm_per_base + 0x050);  // 0x050
        constexpr std::uint32_t reserved3_0         = UINT32_C(cm_per_base + 0x054);  // 0x054
        constexpr std::uint32_t reserved3_1         = UINT32_C(cm_per_base + 0x058);  // 0x058
        constexpr std::uint32_t reserved3_2         = UINT32_C(cm_per_base + 0x05C);  // 0x05C
        constexpr std::uint32_t l4ls_clkctrl        = UINT32_C(cm_per_base + 0x060);  // 0x060
        constexpr std::uint32_t l4fw_clkctrl        = UINT32_C(cm_per_base + 0x064);  // 0x064
        constexpr std::uint32_t mcasp1_clkctrl      = UINT32_C(cm_per_base + 0x068);  // 0x068
        constexpr std::uint32_t uart1_clkctrl       = UINT32_C(cm_per_base + 0x06C);  // 0x06C
        constexpr std::uint32_t uart2_clkctrl       = UINT32_C(cm_per_base + 0x070);  // 0x070
        constexpr std::uint32_t uart3_clkctrl       = UINT32_C(cm_per_base + 0x074);  // 0x074
        constexpr std::uint32_t uart4_clkctrl       = UINT32_C(cm_per_base + 0x078);  // 0x078
        constexpr std::uint32_t timer7_clkctrl      = UINT32_C(cm_per_base + 0x07C);  // 0x07C
        constexpr std::uint32_t timer2_clkctrl      = UINT32_C(cm_per_base + 0x080);  // 0x080
        constexpr std::uint32_t timer3_clkctrl      = UINT32_C(cm_per_base + 0x084);  // 0x084
        constexpr std::uint32_t timer4_clkctrl      = UINT32_C(cm_per_base + 0x088);  // 0x088
        constexpr std::uint32_t reserved4_0         = UINT32_C(cm_per_base + 0x08C);  // 0x08C
        constexpr std::uint32_t reserved4_1         = UINT32_C(cm_per_base + 0x090);  // 0x090
        constexpr std::uint32_t reserved4_2         = UINT32_C(cm_per_base + 0x094);  // 0x094
        constexpr std::uint32_t reserved4_3         = UINT32_C(cm_per_base + 0x098);  // 0x098
        constexpr std::uint32_t reserved4_4         = UINT32_C(cm_per_base + 0x09C);  // 0x09C
        constexpr std::uint32_t reserved4_5         = UINT32_C(cm_per_base + 0x0A0);  // 0x0A0
        constexpr std::uint32_t reserved4_6         = UINT32_C(cm_per_base + 0x0A4);  // 0x0A4
        constexpr std::uint32_t reserved4_7         = UINT32_C(cm_per_base + 0x0A8);  // 0x0A8
        constexpr std::uint32_t gpio1_clkctrl       = UINT32_C(cm_per_base + 0x0AC);  // 0x0AC
        constexpr std::uint32_t gpio2_clkctrl       = UINT32_C(cm_per_base + 0x0B0);  // 0x0B0
        constexpr std::uint32_t gpio3_clkctrl       = UINT32_C(cm_per_base + 0x0B4);  // 0x0B4
        constexpr std::uint32_t reserved5           = UINT32_C(cm_per_base + 0x0B8);  // 0x0B8
        constexpr std::uint32_t tpcc_clkctrl        = UINT32_C(cm_per_base + 0x0BC);  // 0x0BC
        constexpr std::uint32_t dcan0_clkctrl       = UINT32_C(cm_per_base + 0x0C0);  // 0x0C0
        constexpr std::uint32_t dcan1_clkctrl       = UINT32_C(cm_per_base + 0x0C4);  // 0x0C4
        constexpr std::uint32_t reserved6           = UINT32_C(cm_per_base + 0x0C8);  // 0x0C8
        constexpr std::uint32_t epwmss1_clkctrl     = UINT32_C(cm_per_base + 0x0CC);  // 0x0CC
        constexpr std::uint32_t reserved7           = UINT32_C(cm_per_base + 0x0D0);  // 0x0D0
        constexpr std::uint32_t epwmss0_clkctrl     = UINT32_C(cm_per_base + 0x0D4);  // 0x0D4
        constexpr std::uint32_t epwmss2_clkctrl     = UINT32_C(cm_per_base + 0x0D8);  // 0x0D8
        constexpr std::uint32_t l3_instr_clkctrl    = UINT32_C(cm_per_base + 0x0DC);  // 0x0DC
        constexpr std::uint32_t l3_clkctrl          = UINT32_C(cm_per_base + 0x0E0);  // 0x0E0
        constexpr std::uint32_t ieee5000_clkctrl    = UINT32_C(cm_per_base + 0x0E4);  // 0x0E4
        constexpr std::uint32_t pruss_clkctrl       = UINT32_C(cm_per_base + 0x0E8);  // 0x0E8
        constexpr std::uint32_t timer5_clkctrl      = UINT32_C(cm_per_base + 0x0EC);  // 0x0EC
        constexpr std::uint32_t timer6_clkctrl      = UINT32_C(cm_per_base + 0x0F0);  // 0x0F0
        constexpr std::uint32_t mmc1_clkctrl        = UINT32_C(cm_per_base + 0x0F4);  // 0x0F4
        constexpr std::uint32_t mmc2_clkctrl        = UINT32_C(cm_per_base + 0x0F8);  // 0x0F8
        constexpr std::uint32_t tptc1_clkctrl       = UINT32_C(cm_per_base + 0x0FC);  // 0x0FC
        constexpr std::uint32_t tptc2_clkctrl       = UINT32_C(cm_per_base + 0x100);  // 0x100
        constexpr std::uint32_t reserved8_0         = UINT32_C(cm_per_base + 0x104);  // 0x104
        constexpr std::uint32_t reserved8_1         = UINT32_C(cm_per_base + 0x108);  // 0x108
        constexpr std::uint32_t spinlock_clkctrl    = UINT32_C(cm_per_base + 0x10C);  // 0x10C
        constexpr std::uint32_t mailbox0_clkctrl    = UINT32_C(cm_per_base + 0x110);  // 0x110
        constexpr std::uint32_t reserved9_0         = UINT32_C(cm_per_base + 0x114);  // 0x114
        constexpr std::uint32_t reserved9_1         = UINT32_C(cm_per_base + 0x118);  // 0x118
        constexpr std::uint32_t l4hs_clkstctrl      = UINT32_C(cm_per_base + 0x11C);  // 0x11C
        constexpr std::uint32_t l4hs_clkctrl        = UINT32_C(cm_per_base + 0x120);  // 0x120
        constexpr std::uint32_t reserved10_0        = UINT32_C(cm_per_base + 0x124);  // 0x124
        constexpr std::uint32_t reserved10_1        = UINT32_C(cm_per_base + 0x128);  // 0x128
        constexpr std::uint32_t ocpwp_l3_clkstctrl  = UINT32_C(cm_per_base + 0x12C);  // 0x12C
        constexpr std::uint32_t ocpwp_clkctrl       = UINT32_C(cm_per_base + 0x130);  // 0x130
        constexpr std::uint32_t reserved11_0        = UINT32_C(cm_per_base + 0x134);  // 0x134
        constexpr std::uint32_t reserved11_1        = UINT32_C(cm_per_base + 0x138);  // 0x138
        constexpr std::uint32_t reserved11_2        = UINT32_C(cm_per_base + 0x13C);  // 0x13C
        constexpr std::uint32_t pruss_clkstctrl     = UINT32_C(cm_per_base + 0x140);  // 0x140
        constexpr std::uint32_t cpsw_clkstctrl      = UINT32_C(cm_per_base + 0x144);  // 0x144
        constexpr std::uint32_t lcdc_clkstctrl      = UINT32_C(cm_per_base + 0x148);  // 0x148
        constexpr std::uint32_t clkdiv32k_clkctrl   = UINT32_C(cm_per_base + 0x14C);  // 0x14C
        constexpr std::uint32_t clk_24mhz_clkstctrl = UINT32_C(cm_per_base + 0x150);  // 0x150
      }

      namespace cm_wkup
      {
        constexpr std::uint32_t clkstctrl                = UINT32_C(cm_wkup_base + 0x000);  // 0x000
        constexpr std::uint32_t control_clkctrl          = UINT32_C(cm_wkup_base + 0x004);  // 0x004
        constexpr std::uint32_t gpio0_clkctrl            = UINT32_C(cm_wkup_base + 0x008);  // 0x008
        constexpr std::uint32_t l4wkup_clkctrl           = UINT32_C(cm_wkup_base + 0x00C);  // 0x00C
        constexpr std::uint32_t timer0_clkctrl           = UINT32_C(cm_wkup_base + 0x010);  // 0x010
        constexpr std::uint32_t debugss_clkctrl          = UINT32_C(cm_wkup_base + 0x014);  // 0x014
        constexpr std::uint32_t l3_aon_clkstctrl         = UINT32_C(cm_wkup_base + 0x018);  // 0x018
        constexpr std::uint32_t autoidle_dpll_mpu        = UINT32_C(cm_wkup_base + 0x01C);  // 0x01C
        constexpr std::uint32_t idlest_dpll_mpu          = UINT32_C(cm_wkup_base + 0x020);  // 0x020
        constexpr std::uint32_t ssc_deltamstep_dpll_mpu  = UINT32_C(cm_wkup_base + 0x024);  // 0x024
        constexpr std::uint32_t ssc_modfreqdiv_dpll_mpu  = UINT32_C(cm_wkup_base + 0x028);  // 0x028
        constexpr std::uint32_t clksel_dpll_mpu          = UINT32_C(cm_wkup_base + 0x02C);  // 0x02C
        constexpr std::uint32_t autoidle_dpll_ddr        = UINT32_C(cm_wkup_base + 0x030);  // 0x030
        constexpr std::uint32_t idlest_dpll_ddr          = UINT32_C(cm_wkup_base + 0x034);  // 0x034
        constexpr std::uint32_t ssc_deltamstep_dpll_ddr  = UINT32_C(cm_wkup_base + 0x038);  // 0x038
        constexpr std::uint32_t ssc_modfreqdiv_dpll_ddr  = UINT32_C(cm_wkup_base + 0x03C);  // 0x03C
        constexpr std::uint32_t clksel_dpll_ddr          = UINT32_C(cm_wkup_base + 0x040);  // 0x040
        constexpr std::uint32_t autoidle_dpll_disp       = UINT32_C(cm_wkup_base + 0x044);  // 0x044
        constexpr std::uint32_t idlest_dpll_disp         = UINT32_C(cm_wkup_base + 0x048);  // 0x048
        constexpr std::uint32_t ssc_deltamstep_dpll_disp = UINT32_C(cm_wkup_base + 0x04C);  // 0x04C
        constexpr std::uint32_t ssc_modfreqdiv_dpll_disp = UINT32_C(cm_wkup_base + 0x050);  // 0x050
        constexpr std::uint32_t clksel_dpll_disp         = UINT32_C(cm_wkup_base + 0x054);  // 0x054
        constexpr std::uint32_t autoidle_dpll_core       = UINT32_C(cm_wkup_base + 0x058);  // 0x058
        constexpr std::uint32_t idlest_dpll_core         = UINT32_C(cm_wkup_base + 0x05C);  // 0x05C
        constexpr std::uint32_t ssc_deltamstep_dpll_core = UINT32_C(cm_wkup_base + 0x060);  // 0x060
        constexpr std::uint32_t ssc_modfreqdiv_dpll_core = UINT32_C(cm_wkup_base + 0x064);  // 0x064
        constexpr std::uint32_t clksel_dpll_core         = UINT32_C(cm_wkup_base + 0x068);  // 0x068
        constexpr std::uint32_t autoidle_dpll_per        = UINT32_C(cm_wkup_base + 0x06C);  // 0x06C
        constexpr std::uint32_t idlest_dpll_per          = UINT32_C(cm_wkup_base + 0x070);  // 0x070
        constexpr std::uint32_t ssc_deltamstep_dpll_per  = UINT32_C(cm_wkup_base + 0x074);  // 0x074
        constexpr std::uint32_t ssc_modfreqdiv_dpll_per  = UINT32_C(cm_wkup_base + 0x078);  // 0x078
        constexpr std::uint32_t clkdcoldo_dpll_per       = UINT32_C(cm_wkup_base + 0x07C);  // 0x07C
        constexpr std::uint32_t div_m4_dpll_core         = UINT32_C(cm_wkup_base + 0x080);  // 0x080
        constexpr std::uint32_t div_m5_dpll_core         = UINT32_C(cm_wkup_base + 0x084);  // 0x084
        constexpr std::uint32_t clkmode_dpll_mpu         = UINT32_C(cm_wkup_base + 0x088);  // 0x088
        constexpr std::uint32_t clkmode_dpll_per         = UINT32_C(cm_wkup_base + 0x08C);  // 0x08C
        constexpr std::uint32_t clkmode_dpll_core        = UINT32_C(cm_wkup_base + 0x090);  // 0x090
        constexpr std::uint32_t clkmode_dpll_ddr         = UINT32_C(cm_wkup_base + 0x094);  // 0x094
        constexpr std::uint32_t clkmode_dpll_disp        = UINT32_C(cm_wkup_base + 0x098);  // 0x098
        constexpr std::uint32_t clksel_dpll_periph       = UINT32_C(cm_wkup_base + 0x09C);  // 0x09C
        constexpr std::uint32_t div_m2_dpll_ddr          = UINT32_C(cm_wkup_base + 0x0A0);  // 0x0A0
        constexpr std::uint32_t div_m2_dpll_disp         = UINT32_C(cm_wkup_base + 0x0A4);  // 0x0A4
        constexpr std::uint32_t div_m2_dpll_mpu          = UINT32_C(cm_wkup_base + 0x0A8);  // 0x0A8
        constexpr std::uint32_t div_m2_dpll_per          = UINT32_C(cm_wkup_base + 0x0AC);  // 0x0AC
        constexpr std::uint32_t wkup_m3_clkctrl          = UINT32_C(cm_wkup_base + 0x0B0);  // 0x0B0
        constexpr std::uint32_t uart0_clkctrl            = UINT32_C(cm_wkup_base + 0x0B4);  // 0x0B4
        constexpr std::uint32_t i2c0_clkctrl             = UINT32_C(cm_wkup_base + 0x0B8);  // 0x0B8
        constexpr std::uint32_t adc_tsc_clkctrl          = UINT32_C(cm_wkup_base + 0x0BC);  // 0x0BC
        constexpr std::uint32_t smartreflex0_clkctrl     = UINT32_C(cm_wkup_base + 0x0C0);  // 0x0C0
        constexpr std::uint32_t timer1_clkctrl           = UINT32_C(cm_wkup_base + 0x0C4);  // 0x0C4
        constexpr std::uint32_t smartreflex1_clkctrl     = UINT32_C(cm_wkup_base + 0x0C8);  // 0x0C8
        constexpr std::uint32_t l4_wkup_aon_clkstctrl    = UINT32_C(cm_wkup_base + 0x0CC);  // 0x0CC
        constexpr std::uint32_t reserved0                = UINT32_C(cm_wkup_base + 0x0D0);  // 0x0D0
        constexpr std::uint32_t wdt1_clkctrl             = UINT32_C(cm_wkup_base + 0x0D4);  // 0x0D4
        constexpr std::uint32_t div_m6_dpll_core         = UINT32_C(cm_wkup_base + 0x0D8);  // 0x0D8
      }

      namespace cm_dpll
      {
        constexpr std::uint32_t reserved0             = UINT32_C(cm_dpll_base + 0x000);  // 0x000
        constexpr std::uint32_t clksel_timer7_clk     = UINT32_C(cm_dpll_base + 0x004);  // 0x004
        constexpr std::uint32_t clksel_timer2_clk     = UINT32_C(cm_dpll_base + 0x008);  // 0x008
        constexpr std::uint32_t clksel_timer3_clk     = UINT32_C(cm_dpll_base + 0x00C);  // 0x00C
        constexpr std::uint32_t clksel_timer4_clk     = UINT32_C(cm_dpll_base + 0x010);  // 0x010
        constexpr std::uint32_t cm_mac_clksel         = UINT32_C(cm_dpll_base + 0x014);  // 0x014
        constexpr std::uint32_t clksel_timer5_clk     = UINT32_C(cm_dpll_base + 0x018);  // 0x018
        constexpr std::uint32_t clksel_timer6_clk     = UINT32_C(cm_dpll_base + 0x01C);  // 0x01C
        constexpr std::uint32_t cm_cpts_rft_clksel    = UINT32_C(cm_dpll_base + 0x020);  // 0x020
        constexpr std::uint32_t reserved1             = UINT32_C(cm_dpll_base + 0x024);  // 0x024
        constexpr std::uint32_t clksel_timer1ms_clk   = UINT32_C(cm_dpll_base + 0x028);  // 0x028
        constexpr std::uint32_t clksel_gfx_fclk       = UINT32_C(cm_dpll_base + 0x02C);  // 0x02C
        constexpr std::uint32_t clksel_pruss_ocp_clk  = UINT32_C(cm_dpll_base + 0x030);  // 0x030
        constexpr std::uint32_t clksel_lcdc_pixel_clk = UINT32_C(cm_dpll_base + 0x034);  // 0x034
        constexpr std::uint32_t clksel_wdt1_clk       = UINT32_C(cm_dpll_base + 0x038);  // 0x038
        constexpr std::uint32_t clksel_gpio0_dbclk    = UINT32_C(cm_dpll_base + 0x03C);  // 0x03C
      }

      // System control registers.
      namespace control
      {
        constexpr std::uint32_t control_revision       = UINT32_C(control_base + 0x0000);  // 0x0000
        constexpr std::uint32_t control_hwinfo         = UINT32_C(control_base + 0x0004);  // 0x0004
        constexpr std::uint32_t reserved0_0            = UINT32_C(control_base + 0x0008);  // 0x0008
        constexpr std::uint32_t reserved0_1            = UINT32_C(control_base + 0x000C);  // 0x000C
        constexpr std::uint32_t control_sysconfig      = UINT32_C(control_base + 0x0010);  // 0x0010
        constexpr std::uint32_t reserved1_0x0b         = UINT32_C(control_base + 0x0014);  // 0x0014
        constexpr std::uint32_t control_status         = UINT32_C(control_base + 0x0040);  // 0x0040
        constexpr std::uint32_t reserved2_0xf6         = UINT32_C(control_base + 0x0044);  // 0x0044
        constexpr std::uint32_t cortex_vbbldo_ctrl     = UINT32_C(control_base + 0x041C);  // 0x041C
        constexpr std::uint32_t reserved3_0x02         = UINT32_C(control_base + 0x0420);  // 0x0420
        constexpr std::uint32_t core_sldo_ctrl         = UINT32_C(control_base + 0x0428);  // 0x0428
        constexpr std::uint32_t mpu_sldo_ctrl          = UINT32_C(control_base + 0x042C);  // 0x042C
        constexpr std::uint32_t reserved4_0x05         = UINT32_C(control_base + 0x0430);  // 0x0430
        constexpr std::uint32_t clk32kdivratio_ctrl    = UINT32_C(control_base + 0x0444);  // 0x0444
        constexpr std::uint32_t bandgap_ctrl           = UINT32_C(control_base + 0x0448);  // 0x0448
        constexpr std::uint32_t bandgap_trim           = UINT32_C(control_base + 0x044C);  // 0x044C
        constexpr std::uint32_t reserved5_0x02         = UINT32_C(control_base + 0x0450);  // 0x0450
        constexpr std::uint32_t pll_clkinpulow_ctrl    = UINT32_C(control_base + 0x0458);  // 0x0458
        constexpr std::uint32_t reserved6_0x03         = UINT32_C(control_base + 0x045C);  // 0x045C
        constexpr std::uint32_t mosc_ctrl              = UINT32_C(control_base + 0x0468);  // 0x0468
        constexpr std::uint32_t rcosc_ctrl             = UINT32_C(control_base + 0x046C);  // 0x046C
        constexpr std::uint32_t deepsleep_ctrl         = UINT32_C(control_base + 0x0470);  // 0x0470
        constexpr std::uint32_t reserved7_0x63         = UINT32_C(control_base + 0x0474);  // 0x0474
        constexpr std::uint32_t device_id              = UINT32_C(control_base + 0x0600);  // 0x0600
        constexpr std::uint32_t dev_feature            = UINT32_C(control_base + 0x0604);  // 0x0604
        constexpr std::uint32_t init_priority_0        = UINT32_C(control_base + 0x0608);  // 0x0608
        constexpr std::uint32_t init_priority_1        = UINT32_C(control_base + 0x060C);  // 0x060C
        constexpr std::uint32_t mmu_cfg                = UINT32_C(control_base + 0x0610);  // 0x0610
        constexpr std::uint32_t tptc_cfg               = UINT32_C(control_base + 0x0614);  // 0x0614
        constexpr std::uint32_t reserved8_0x02         = UINT32_C(control_base + 0x0618);  // 0x0618
        constexpr std::uint32_t usb_ctrl0              = UINT32_C(control_base + 0x0620);  // 0x0620
        constexpr std::uint32_t usb_sts0               = UINT32_C(control_base + 0x0624);  // 0x0624
        constexpr std::uint32_t usb_ctrl1              = UINT32_C(control_base + 0x0628);  // 0x0628
        constexpr std::uint32_t usb_sts1               = UINT32_C(control_base + 0x062C);  // 0x062C
        constexpr std::uint32_t mac_id0_lo             = UINT32_C(control_base + 0x0630);  // 0x0630
        constexpr std::uint32_t mac_id0_hi             = UINT32_C(control_base + 0x0634);  // 0x0634
        constexpr std::uint32_t mac_id1_lo             = UINT32_C(control_base + 0x0638);  // 0x0638
        constexpr std::uint32_t mac_id1_hi             = UINT32_C(control_base + 0x063C);  // 0x063C
        constexpr std::uint32_t reserved9              = UINT32_C(control_base + 0x0640);  // 0x0640
        constexpr std::uint32_t dcan_raminit           = UINT32_C(control_base + 0x0644);  // 0x0644
        constexpr std::uint32_t usb_wkup_ctrl          = UINT32_C(control_base + 0x0648);  // 0x0648
        constexpr std::uint32_t reserved10             = UINT32_C(control_base + 0x064C);  // 0x064C
        constexpr std::uint32_t gmii_sel               = UINT32_C(control_base + 0x0650);  // 0x0650
        constexpr std::uint32_t reserved11_0x04        = UINT32_C(control_base + 0x0654);  // 0x0654
        constexpr std::uint32_t pwmss_ctrl             = UINT32_C(control_base + 0x0664);  // 0x0664
        constexpr std::uint32_t reserved12_0x02        = UINT32_C(control_base + 0x0668);  // 0x0668
        constexpr std::uint32_t mreqprio_0             = UINT32_C(control_base + 0x0670);  // 0x0670
        constexpr std::uint32_t mreqprio_1             = UINT32_C(control_base + 0x0674);  // 0x0674
        constexpr std::uint32_t reserved13_0x06        = UINT32_C(control_base + 0x0678);  // 0x0678
        constexpr std::uint32_t hw_event_sel_grp1      = UINT32_C(control_base + 0x0690);  // 0x0690
        constexpr std::uint32_t hw_event_sel_grp2      = UINT32_C(control_base + 0x0694);  // 0x0694
        constexpr std::uint32_t hw_event_sel_grp3      = UINT32_C(control_base + 0x0698);  // 0x0698
        constexpr std::uint32_t hw_event_sel_grp4      = UINT32_C(control_base + 0x069C);  // 0x069C
        constexpr std::uint32_t smrt_ctrl              = UINT32_C(control_base + 0x06A0);  // 0x06A0
        constexpr std::uint32_t mpuss_hw_debug_sel     = UINT32_C(control_base + 0x06A4);  // 0x06A4
        constexpr std::uint32_t mpuss_hw_dbg_info      = UINT32_C(control_base + 0x06A8);  // 0x06A8
        constexpr std::uint32_t reserved14_0x31        = UINT32_C(control_base + 0x06AC);  // 0x06AC
        constexpr std::uint32_t vdd_mpu_opp_050        = UINT32_C(control_base + 0x0770);  // 0x0770
        constexpr std::uint32_t vdd_mpu_opp_100        = UINT32_C(control_base + 0x0774);  // 0x0774
        constexpr std::uint32_t vdd_mpu_opp_120        = UINT32_C(control_base + 0x0778);  // 0x0778
        constexpr std::uint32_t vdd_mpu_opp_turbo      = UINT32_C(control_base + 0x077C);  // 0x077C
        constexpr std::uint32_t reserved15_0x0e        = UINT32_C(control_base + 0x0780);  // 0x0780
        constexpr std::uint32_t vdd_core_opp_050       = UINT32_C(control_base + 0x07B8);  // 0x07B8
        constexpr std::uint32_t vdd_core_opp_100       = UINT32_C(control_base + 0x07BC);  // 0x07BC
        constexpr std::uint32_t reserved16_0x04        = UINT32_C(control_base + 0x07C0);  // 0x07C0
        constexpr std::uint32_t bb_scale               = UINT32_C(control_base + 0x07D0);  // 0x07D0
        constexpr std::uint32_t reserved17_0x08        = UINT32_C(control_base + 0x07D4);  // 0x07D4
        constexpr std::uint32_t usb_vid_pid            = UINT32_C(control_base + 0x07F4);  // 0x07F4
        constexpr std::uint32_t reserved18_0x02        = UINT32_C(control_base + 0x07F8);  // 0x07F8
        constexpr std::uint32_t conf_gpmc_ad0          = UINT32_C(control_base + 0x0800);  // 0x0800
        constexpr std::uint32_t conf_gpmc_ad1          = UINT32_C(control_base + 0x0804);  // 0x0804
        constexpr std::uint32_t conf_gpmc_ad2          = UINT32_C(control_base + 0x0808);  // 0x0808
        constexpr std::uint32_t conf_gpmc_ad3          = UINT32_C(control_base + 0x080C);  // 0x080C
        constexpr std::uint32_t conf_gpmc_ad4          = UINT32_C(control_base + 0x0810);  // 0x0810
        constexpr std::uint32_t conf_gpmc_ad5          = UINT32_C(control_base + 0x0814);  // 0x0814
        constexpr std::uint32_t conf_gpmc_ad6          = UINT32_C(control_base + 0x0818);  // 0x0818
        constexpr std::uint32_t conf_gpmc_ad7          = UINT32_C(control_base + 0x081C);  // 0x081C
        constexpr std::uint32_t conf_gpmc_ad8          = UINT32_C(control_base + 0x0820);  // 0x0820
        constexpr std::uint32_t conf_gpmc_ad9          = UINT32_C(control_base + 0x0824);  // 0x0824
        constexpr std::uint32_t conf_gpmc_ad10         = UINT32_C(control_base + 0x0828);  // 0x0828
        constexpr std::uint32_t conf_gpmc_ad11         = UINT32_C(control_base + 0x082C);  // 0x082C
        constexpr std::uint32_t conf_gpmc_ad12         = UINT32_C(control_base + 0x0830);  // 0x0830
        constexpr std::uint32_t conf_gpmc_ad13         = UINT32_C(control_base + 0x0834);  // 0x0834
        constexpr std::uint32_t conf_gpmc_ad14         = UINT32_C(control_base + 0x0838);  // 0x0838
        constexpr std::uint32_t conf_gpmc_ad15         = UINT32_C(control_base + 0x083C);  // 0x083C
        constexpr std::uint32_t conf_gpmc_a0           = UINT32_C(control_base + 0x0840);  // 0x0840
        constexpr std::uint32_t conf_gpmc_a1           = UINT32_C(control_base + 0x0844);  // 0x0844
        constexpr std::uint32_t conf_gpmc_a2           = UINT32_C(control_base + 0x0848);  // 0x0848
        constexpr std::uint32_t conf_gpmc_a3           = UINT32_C(control_base + 0x084C);  // 0x084C
        constexpr std::uint32_t conf_gpmc_a4           = UINT32_C(control_base + 0x0850);  // 0x0850
        constexpr std::uint32_t conf_gpmc_a5           = UINT32_C(control_base + 0x0854);  // 0x0854
        constexpr std::uint32_t conf_gpmc_a6           = UINT32_C(control_base + 0x0858);  // 0x0858
        constexpr std::uint32_t conf_gpmc_a7           = UINT32_C(control_base + 0x085C);  // 0x085C
        constexpr std::uint32_t conf_gpmc_a8           = UINT32_C(control_base + 0x0860);  // 0x0860
        constexpr std::uint32_t conf_gpmc_a9           = UINT32_C(control_base + 0x0864);  // 0x0864
        constexpr std::uint32_t conf_gpmc_a10          = UINT32_C(control_base + 0x0868);  // 0x0868
        constexpr std::uint32_t conf_gpmc_a11          = UINT32_C(control_base + 0x086C);  // 0x086C
        constexpr std::uint32_t conf_gpmc_wait0        = UINT32_C(control_base + 0x0870);  // 0x0870
        constexpr std::uint32_t conf_gpmc_wpn          = UINT32_C(control_base + 0x0874);  // 0x0874
        constexpr std::uint32_t conf_gpmc_be1n         = UINT32_C(control_base + 0x0878);  // 0x0878
        constexpr std::uint32_t conf_gpmc_csn0         = UINT32_C(control_base + 0x087C);  // 0x087C
        constexpr std::uint32_t conf_gpmc_csn1         = UINT32_C(control_base + 0x0880);  // 0x0880
        constexpr std::uint32_t conf_gpmc_csn2         = UINT32_C(control_base + 0x0884);  // 0x0884
        constexpr std::uint32_t conf_gpmc_csn3         = UINT32_C(control_base + 0x0888);  // 0x0888
        constexpr std::uint32_t conf_gpmc_clk          = UINT32_C(control_base + 0x088C);  // 0x088C
        constexpr std::uint32_t conf_gpmc_advn_ale     = UINT32_C(control_base + 0x0890);  // 0x0890
        constexpr std::uint32_t conf_gpmc_oen_ren      = UINT32_C(control_base + 0x0894);  // 0x0894
        constexpr std::uint32_t conf_gpmc_wen          = UINT32_C(control_base + 0x0898);  // 0x0898
        constexpr std::uint32_t conf_gpmc_be0n_cle     = UINT32_C(control_base + 0x089C);  // 0x089C
        constexpr std::uint32_t conf_lcd_data0         = UINT32_C(control_base + 0x08A0);  // 0x08A0
        constexpr std::uint32_t conf_lcd_data1         = UINT32_C(control_base + 0x08A4);  // 0x08A4
        constexpr std::uint32_t conf_lcd_data2         = UINT32_C(control_base + 0x08A8);  // 0x08A8
        constexpr std::uint32_t conf_lcd_data3         = UINT32_C(control_base + 0x08AC);  // 0x08AC
        constexpr std::uint32_t conf_lcd_data4         = UINT32_C(control_base + 0x08B0);  // 0x08B0
        constexpr std::uint32_t conf_lcd_data5         = UINT32_C(control_base + 0x08B4);  // 0x08B4
        constexpr std::uint32_t conf_lcd_data6         = UINT32_C(control_base + 0x08B8);  // 0x08B8
        constexpr std::uint32_t conf_lcd_data7         = UINT32_C(control_base + 0x08BC);  // 0x08BC
        constexpr std::uint32_t conf_lcd_data8         = UINT32_C(control_base + 0x08C0);  // 0x08C0
        constexpr std::uint32_t conf_lcd_data9         = UINT32_C(control_base + 0x08C4);  // 0x08C4
        constexpr std::uint32_t conf_lcd_data10        = UINT32_C(control_base + 0x08C8);  // 0x08C8
        constexpr std::uint32_t conf_lcd_data11        = UINT32_C(control_base + 0x08CC);  // 0x08CC
        constexpr std::uint32_t conf_lcd_data12        = UINT32_C(control_base + 0x08D0);  // 0x08D0
        constexpr std::uint32_t conf_lcd_data13        = UINT32_C(control_base + 0x08D4);  // 0x08D4
        constexpr std::uint32_t conf_lcd_data14        = UINT32_C(control_base + 0x08D8);  // 0x08D8
        constexpr std::uint32_t conf_lcd_data15        = UINT32_C(control_base + 0x08DC);  // 0x08DC
        constexpr std::uint32_t conf_lcd_vsync         = UINT32_C(control_base + 0x08E0);  // 0x08E0
        constexpr std::uint32_t conf_lcd_hsync         = UINT32_C(control_base + 0x08E4);  // 0x08E4
        constexpr std::uint32_t conf_lcd_pclk          = UINT32_C(control_base + 0x08E8);  // 0x08E8
        constexpr std::uint32_t conf_lcd_ac_bias_en    = UINT32_C(control_base + 0x08EC);  // 0x08EC
        constexpr std::uint32_t conf_mmc0_dat3         = UINT32_C(control_base + 0x08F0);  // 0x08F0
        constexpr std::uint32_t conf_mmc0_dat2         = UINT32_C(control_base + 0x08F4);  // 0x08F4
        constexpr std::uint32_t conf_mmc0_dat1         = UINT32_C(control_base + 0x08F8);  // 0x08F8
        constexpr std::uint32_t conf_mmc0_dat0         = UINT32_C(control_base + 0x08FC);  // 0x08FC
        constexpr std::uint32_t conf_mmc0_clk          = UINT32_C(control_base + 0x0900);  // 0x0900
        constexpr std::uint32_t conf_mmc0_cmd          = UINT32_C(control_base + 0x0904);  // 0x0904
        constexpr std::uint32_t conf_mii1_col          = UINT32_C(control_base + 0x0908);  // 0x0908
        constexpr std::uint32_t conf_mii1_crs          = UINT32_C(control_base + 0x090C);  // 0x090C
        constexpr std::uint32_t conf_mii1_rxerr        = UINT32_C(control_base + 0x0910);  // 0x0910
        constexpr std::uint32_t conf_mii1_txen         = UINT32_C(control_base + 0x0914);  // 0x0914
        constexpr std::uint32_t conf_mii1_rxdv         = UINT32_C(control_base + 0x0918);  // 0x0918
        constexpr std::uint32_t conf_mii1_txd3         = UINT32_C(control_base + 0x091C);  // 0x091C
        constexpr std::uint32_t conf_mii1_txd2         = UINT32_C(control_base + 0x0920);  // 0x0920
        constexpr std::uint32_t conf_mii1_txd1         = UINT32_C(control_base + 0x0924);  // 0x0924
        constexpr std::uint32_t conf_mii1_txd0         = UINT32_C(control_base + 0x0928);  // 0x0928
        constexpr std::uint32_t conf_mii1_txclk        = UINT32_C(control_base + 0x092C);  // 0x092C
        constexpr std::uint32_t conf_mii1_rxclk        = UINT32_C(control_base + 0x0930);  // 0x0930
        constexpr std::uint32_t conf_mii1_rxd3         = UINT32_C(control_base + 0x0934);  // 0x0934
        constexpr std::uint32_t conf_mii1_rxd2         = UINT32_C(control_base + 0x0938);  // 0x0938
        constexpr std::uint32_t conf_mii1_rxd1         = UINT32_C(control_base + 0x093C);  // 0x093C
        constexpr std::uint32_t conf_mii1_rxd0         = UINT32_C(control_base + 0x0940);  // 0x0940
        constexpr std::uint32_t conf_rmii1_refclk      = UINT32_C(control_base + 0x0944);  // 0x0944
        constexpr std::uint32_t conf_mdio_data         = UINT32_C(control_base + 0x0948);  // 0x0948
        constexpr std::uint32_t conf_mdio_clk          = UINT32_C(control_base + 0x094C);  // 0x094C
        constexpr std::uint32_t conf_spi0_sclk         = UINT32_C(control_base + 0x0950);  // 0x0950
        constexpr std::uint32_t conf_spi0_d0           = UINT32_C(control_base + 0x0954);  // 0x0954
        constexpr std::uint32_t conf_spi0_d1           = UINT32_C(control_base + 0x0958);  // 0x0958
        constexpr std::uint32_t conf_spi0_cs0          = UINT32_C(control_base + 0x095C);  // 0x095C
        constexpr std::uint32_t conf_spi0_cs1          = UINT32_C(control_base + 0x0960);  // 0x0960
        constexpr std::uint32_t conf_ecap0_in_pwm0_out = UINT32_C(control_base + 0x0964);  // 0x0964
        constexpr std::uint32_t conf_uart0_ctsn        = UINT32_C(control_base + 0x0968);  // 0x0968
        constexpr std::uint32_t conf_uart0_rtsn        = UINT32_C(control_base + 0x096C);  // 0x096C
        constexpr std::uint32_t conf_uart0_rxd         = UINT32_C(control_base + 0x0970);  // 0x0970
        constexpr std::uint32_t conf_uart0_txd         = UINT32_C(control_base + 0x0974);  // 0x0974
        constexpr std::uint32_t conf_uart1_ctsn        = UINT32_C(control_base + 0x0978);  // 0x0978
        constexpr std::uint32_t conf_uart1_rtsn        = UINT32_C(control_base + 0x097C);  // 0x097C
        constexpr std::uint32_t conf_uart1_rxd         = UINT32_C(control_base + 0x0980);  // 0x0980
        constexpr std::uint32_t conf_uart1_txd         = UINT32_C(control_base + 0x0984);  // 0x0984
        constexpr std::uint32_t conf_i2c0_sda          = UINT32_C(control_base + 0x0988);  // 0x0988
        constexpr std::uint32_t conf_i2c0_scl          = UINT32_C(control_base + 0x098C);  // 0x098C
        constexpr std::uint32_t conf_mcasp0_aclkx      = UINT32_C(control_base + 0x0990);  // 0x0990
        constexpr std::uint32_t conf_mcasp0_fsx        = UINT32_C(control_base + 0x0994);  // 0x0994
        constexpr std::uint32_t conf_mcasp0_axr0       = UINT32_C(control_base + 0x0998);  // 0x0998
        constexpr std::uint32_t conf_mcasp0_ahclkr     = UINT32_C(control_base + 0x099C);  // 0x099C
        constexpr std::uint32_t conf_mcasp0_aclkr      = UINT32_C(control_base + 0x09A0);  // 0x09A0
        constexpr std::uint32_t conf_mcasp0_fsr        = UINT32_C(control_base + 0x09A4);  // 0x09A4
        constexpr std::uint32_t conf_mcasp0_axr1       = UINT32_C(control_base + 0x09A8);  // 0x09A8
        constexpr std::uint32_t conf_mcasp0_ahclkx     = UINT32_C(control_base + 0x09AC);  // 0x09AC
        constexpr std::uint32_t conf_xdma_event_intr0  = UINT32_C(control_base + 0x09B0);  // 0x09B0
        constexpr std::uint32_t conf_xdma_event_intr1  = UINT32_C(control_base + 0x09B4);  // 0x09B4
        constexpr std::uint32_t conf_nresetin_out      = UINT32_C(control_base + 0x09B8);  // 0x09B8
        constexpr std::uint32_t conf_porz              = UINT32_C(control_base + 0x09BC);  // 0x09BC
        constexpr std::uint32_t conf_nnmi              = UINT32_C(control_base + 0x09C0);  // 0x09C0
        constexpr std::uint32_t conf_osc0_in           = UINT32_C(control_base + 0x09C4);  // 0x09C4
        constexpr std::uint32_t conf_osc0_out          = UINT32_C(control_base + 0x09C8);  // 0x09C8
        constexpr std::uint32_t conf_osc0_vss          = UINT32_C(control_base + 0x09CC);  // 0x09CC
        constexpr std::uint32_t conf_tms               = UINT32_C(control_base + 0x09D0);  // 0x09D0
        constexpr std::uint32_t conf_tdi               = UINT32_C(control_base + 0x09D4);  // 0x09D4
        constexpr std::uint32_t conf_tdo               = UINT32_C(control_base + 0x09D8);  // 0x09D8
        constexpr std::uint32_t conf_tck               = UINT32_C(control_base + 0x09DC);  // 0x09DC
        constexpr std::uint32_t conf_ntrst             = UINT32_C(control_base + 0x09E0);  // 0x09E0
        constexpr std::uint32_t conf_emu0              = UINT32_C(control_base + 0x09E4);  // 0x09E4
        constexpr std::uint32_t conf_emu1              = UINT32_C(control_base + 0x09E8);  // 0x09E8
        constexpr std::uint32_t conf_osc1_in           = UINT32_C(control_base + 0x09EC);  // 0x09EC
        constexpr std::uint32_t conf_osc1_out          = UINT32_C(control_base + 0x09F0);  // 0x09F0
        constexpr std::uint32_t conf_osc1_vss          = UINT32_C(control_base + 0x09F4);  // 0x09F4
        constexpr std::uint32_t conf_rtc_porz          = UINT32_C(control_base + 0x09F8);  // 0x09F8
        constexpr std::uint32_t conf_pmic_power_en     = UINT32_C(control_base + 0x09FC);  // 0x09FC
        constexpr std::uint32_t conf_ext_wakeup        = UINT32_C(control_base + 0x0A00);  // 0x0A00
        constexpr std::uint32_t conf_enz_kaldo_1p8v    = UINT32_C(control_base + 0x0A04);  // 0x0A04
        constexpr std::uint32_t conf_usb0_dm           = UINT32_C(control_base + 0x0A08);  // 0x0A08
        constexpr std::uint32_t conf_usb0_dp           = UINT32_C(control_base + 0x0A0C);  // 0x0A0C
        constexpr std::uint32_t conf_usb0_ce           = UINT32_C(control_base + 0x0A10);  // 0x0A10
        constexpr std::uint32_t conf_usb0_id           = UINT32_C(control_base + 0x0A14);  // 0x0A14
        constexpr std::uint32_t conf_usb0_vbus         = UINT32_C(control_base + 0x0A18);  // 0x0A18
        constexpr std::uint32_t conf_usb0_drvvbus      = UINT32_C(control_base + 0x0A1C);  // 0x0A1C
        constexpr std::uint32_t conf_usb1_dm           = UINT32_C(control_base + 0x0A20);  // 0x0A20
        constexpr std::uint32_t conf_usb1_dp           = UINT32_C(control_base + 0x0A24);  // 0x0A24
        constexpr std::uint32_t conf_usb1_ce           = UINT32_C(control_base + 0x0A28);  // 0x0A28
        constexpr std::uint32_t conf_usb1_id           = UINT32_C(control_base + 0x0A2C);  // 0x0A2C
        constexpr std::uint32_t conf_usb1_vbus         = UINT32_C(control_base + 0x0A30);  // 0x0A30
        constexpr std::uint32_t conf_usb1_drvvbus      = UINT32_C(control_base + 0x0A34);  // 0x0A34
        constexpr std::uint32_t conf_ddr_resetn        = UINT32_C(control_base + 0x0A38);  // 0x0A38
        constexpr std::uint32_t conf_ddr_csn0          = UINT32_C(control_base + 0x0A3C);  // 0x0A3C
        constexpr std::uint32_t conf_ddr_cke           = UINT32_C(control_base + 0x0A40);  // 0x0A40
        constexpr std::uint32_t reserved19             = UINT32_C(control_base + 0x0A44);  // 0x0A44
        constexpr std::uint32_t conf_ddr_nck           = UINT32_C(control_base + 0x0A48);  // 0x0A48
        constexpr std::uint32_t conf_ddr_casn          = UINT32_C(control_base + 0x0A4C);  // 0x0A4C
        constexpr std::uint32_t conf_ddr_rasn          = UINT32_C(control_base + 0x0A50);  // 0x0A50
        constexpr std::uint32_t conf_ddr_wen           = UINT32_C(control_base + 0x0A54);  // 0x0A54
        constexpr std::uint32_t conf_ddr_ba0           = UINT32_C(control_base + 0x0A58);  // 0x0A58
        constexpr std::uint32_t conf_ddr_ba1           = UINT32_C(control_base + 0x0A5C);  // 0x0A5C
        constexpr std::uint32_t conf_ddr_ba2           = UINT32_C(control_base + 0x0A60);  // 0x0A60
        constexpr std::uint32_t conf_ddr_a0            = UINT32_C(control_base + 0x0A64);  // 0x0A64
        constexpr std::uint32_t conf_ddr_a1            = UINT32_C(control_base + 0x0A68);  // 0x0A68
        constexpr std::uint32_t conf_ddr_a2            = UINT32_C(control_base + 0x0A6C);  // 0x0A6C
        constexpr std::uint32_t conf_ddr_a3            = UINT32_C(control_base + 0x0A70);  // 0x0A70
        constexpr std::uint32_t conf_ddr_a4            = UINT32_C(control_base + 0x0A74);  // 0x0A74
        constexpr std::uint32_t conf_ddr_a5            = UINT32_C(control_base + 0x0A78);  // 0x0A78
        constexpr std::uint32_t conf_ddr_a6            = UINT32_C(control_base + 0x0A7C);  // 0x0A7C
        constexpr std::uint32_t conf_ddr_a7            = UINT32_C(control_base + 0x0A80);  // 0x0A80
        constexpr std::uint32_t conf_ddr_a8            = UINT32_C(control_base + 0x0A84);  // 0x0A84
        constexpr std::uint32_t conf_ddr_a9            = UINT32_C(control_base + 0x0A88);  // 0x0A88
        constexpr std::uint32_t conf_ddr_a10           = UINT32_C(control_base + 0x0A8C);  // 0x0A8C
        constexpr std::uint32_t conf_ddr_a11           = UINT32_C(control_base + 0x0A90);  // 0x0A90
        constexpr std::uint32_t conf_ddr_a12           = UINT32_C(control_base + 0x0A94);  // 0x0A94
        constexpr std::uint32_t conf_ddr_a13           = UINT32_C(control_base + 0x0A98);  // 0x0A98
        constexpr std::uint32_t conf_ddr_a14           = UINT32_C(control_base + 0x0A9C);  // 0x0A9C
        constexpr std::uint32_t conf_ddr_a15           = UINT32_C(control_base + 0x0AA0);  // 0x0AA0
        constexpr std::uint32_t conf_ddr_odt           = UINT32_C(control_base + 0x0AA4);  // 0x0AA4
        constexpr std::uint32_t conf_ddr_d0            = UINT32_C(control_base + 0x0AA8);  // 0x0AA8
        constexpr std::uint32_t conf_ddr_d1            = UINT32_C(control_base + 0x0AAC);  // 0x0AAC
        constexpr std::uint32_t conf_ddr_d2            = UINT32_C(control_base + 0x0AB0);  // 0x0AB0
        constexpr std::uint32_t conf_ddr_d3            = UINT32_C(control_base + 0x0AB4);  // 0x0AB4
        constexpr std::uint32_t conf_ddr_d4            = UINT32_C(control_base + 0x0AB8);  // 0x0AB8
        constexpr std::uint32_t conf_ddr_d5            = UINT32_C(control_base + 0x0ABC);  // 0x0ABC
        constexpr std::uint32_t conf_ddr_d6            = UINT32_C(control_base + 0x0AC0);  // 0x0AC0
        constexpr std::uint32_t conf_ddr_d7            = UINT32_C(control_base + 0x0AC4);  // 0x0AC4
        constexpr std::uint32_t conf_ddr_d8            = UINT32_C(control_base + 0x0AC8);  // 0x0AC8
        constexpr std::uint32_t conf_ddr_d9            = UINT32_C(control_base + 0x0ACC);  // 0x0ACC
        constexpr std::uint32_t conf_ddr_d10           = UINT32_C(control_base + 0x0AD0);  // 0x0AD0
        constexpr std::uint32_t conf_ddr_d11           = UINT32_C(control_base + 0x0AD4);  // 0x0AD4
        constexpr std::uint32_t conf_ddr_d12           = UINT32_C(control_base + 0x0AD8);  // 0x0AD8
        constexpr std::uint32_t conf_ddr_d13           = UINT32_C(control_base + 0x0ADC);  // 0x0ADC
        constexpr std::uint32_t conf_ddr_d14           = UINT32_C(control_base + 0x0AE0);  // 0x0AE0
        constexpr std::uint32_t conf_ddr_d15           = UINT32_C(control_base + 0x0AE4);  // 0x0AE4
        constexpr std::uint32_t conf_ddr_dqm0          = UINT32_C(control_base + 0x0AE8);  // 0x0AE8
        constexpr std::uint32_t conf_ddr_dqm1          = UINT32_C(control_base + 0x0AEC);  // 0x0AEC
        constexpr std::uint32_t conf_ddr_dqs0          = UINT32_C(control_base + 0x0AF0);  // 0x0AF0
        constexpr std::uint32_t conf_ddr_dqsn0         = UINT32_C(control_base + 0x0AF4);  // 0x0AF4
        constexpr std::uint32_t conf_ddr_dqs1          = UINT32_C(control_base + 0x0AF8);  // 0x0AF8
        constexpr std::uint32_t conf_ddr_dqsn1         = UINT32_C(control_base + 0x0AFC);  // 0x0AFC
        constexpr std::uint32_t conf_ddr_vref          = UINT32_C(control_base + 0x0B00);  // 0x0B00
        constexpr std::uint32_t conf_ddr_vtp           = UINT32_C(control_base + 0x0B04);  // 0x0B04
        constexpr std::uint32_t conf_ddr_strben0       = UINT32_C(control_base + 0x0B08);  // 0x0B08
        constexpr std::uint32_t conf_ddr_strben1       = UINT32_C(control_base + 0x0B0C);  // 0x0B0C
        constexpr std::uint32_t conf_ain7              = UINT32_C(control_base + 0x0B10);  // 0x0B10
        constexpr std::uint32_t conf_ain6              = UINT32_C(control_base + 0x0B14);  // 0x0B14
        constexpr std::uint32_t conf_ain5              = UINT32_C(control_base + 0x0B18);  // 0x0B18
        constexpr std::uint32_t conf_ain4              = UINT32_C(control_base + 0x0B1C);  // 0x0B1C
        constexpr std::uint32_t conf_ain3              = UINT32_C(control_base + 0x0B20);  // 0x0B20
        constexpr std::uint32_t conf_ain2              = UINT32_C(control_base + 0x0B24);  // 0x0B24
        constexpr std::uint32_t conf_ain1              = UINT32_C(control_base + 0x0B28);  // 0x0B28
        constexpr std::uint32_t conf_ain0              = UINT32_C(control_base + 0x0B2C);  // 0x0B2C
        constexpr std::uint32_t conf_vrefp             = UINT32_C(control_base + 0x0B30);  // 0x0B30
        constexpr std::uint32_t conf_vrefn             = UINT32_C(control_base + 0x0B34);  // 0x0B34
        constexpr std::uint32_t conf_avdd              = UINT32_C(control_base + 0x0B38);  // 0x0B38
        constexpr std::uint32_t conf_avss              = UINT32_C(control_base + 0x0B3C);  // 0x0B3C
        constexpr std::uint32_t conf_iforce            = UINT32_C(control_base + 0x0B40);  // 0x0B40
        constexpr std::uint32_t conf_vsense            = UINT32_C(control_base + 0x0B44);  // 0x0B44
        constexpr std::uint32_t conf_testout           = UINT32_C(control_base + 0x0B48);  // 0x0B48
        constexpr std::uint32_t reserved20_0xad        = UINT32_C(control_base + 0x0B4C);  // 0x0B4C
        constexpr std::uint32_t cqdetect_status        = UINT32_C(control_base + 0x0E00);  // 0x0E00
        constexpr std::uint32_t ddr_io_ctrl            = UINT32_C(control_base + 0x0E04);  // 0x0E04
        constexpr std::uint32_t reserved21             = UINT32_C(control_base + 0x0E08);  // 0x0E08
        constexpr std::uint32_t vtp_ctrl               = UINT32_C(control_base + 0x0E0C);  // 0x0E0C
        constexpr std::uint32_t reserved22             = UINT32_C(control_base + 0x0E10);  // 0x0E10
        constexpr std::uint32_t vref_ctrl              = UINT32_C(control_base + 0x0E14);  // 0x0E14
        constexpr std::uint32_t reserved23_0x5e        = UINT32_C(control_base + 0x0E18);  // 0x0E18
        constexpr std::uint32_t tpcc_evt_mux_0_3       = UINT32_C(control_base + 0x0F90);  // 0x0F90
        constexpr std::uint32_t tpcc_evt_mux_4_7       = UINT32_C(control_base + 0x0F94);  // 0x0F94
        constexpr std::uint32_t tpcc_evt_mux_8_11      = UINT32_C(control_base + 0x0F98);  // 0x0F98
        constexpr std::uint32_t tpcc_evt_mux_12_15     = UINT32_C(control_base + 0x0F9C);  // 0x0F9C
        constexpr std::uint32_t tpcc_evt_mux_16_19     = UINT32_C(control_base + 0x0FA0);  // 0x0FA0
        constexpr std::uint32_t tpcc_evt_mux_20_23     = UINT32_C(control_base + 0x0FA4);  // 0x0FA4
        constexpr std::uint32_t tpcc_evt_mux_24_27     = UINT32_C(control_base + 0x0FA8);  // 0x0FA8
        constexpr std::uint32_t tpcc_evt_mux_28_31     = UINT32_C(control_base + 0x0FAC);  // 0x0FAC
        constexpr std::uint32_t tpcc_evt_mux_32_35     = UINT32_C(control_base + 0x0FB0);  // 0x0FB0
        constexpr std::uint32_t tpcc_evt_mux_36_39     = UINT32_C(control_base + 0x0FB4);  // 0x0FB4
        constexpr std::uint32_t tpcc_evt_mux_40_43     = UINT32_C(control_base + 0x0FB8);  // 0x0FB8
        constexpr std::uint32_t tpcc_evt_mux_44_47     = UINT32_C(control_base + 0x0FBC);  // 0x0FBC
        constexpr std::uint32_t tpcc_evt_mux_48_51     = UINT32_C(control_base + 0x0FC0);  // 0x0FC0
        constexpr std::uint32_t tpcc_evt_mux_52_55     = UINT32_C(control_base + 0x0FC4);  // 0x0FC4
        constexpr std::uint32_t tpcc_evt_mux_56_59     = UINT32_C(control_base + 0x0FC8);  // 0x0FC8
        constexpr std::uint32_t tpcc_evt_mux_60_63     = UINT32_C(control_base + 0x0FCC);  // 0x0FCC
        constexpr std::uint32_t timer_evt_capt         = UINT32_C(control_base + 0x0FD0);  // 0x0FD0
        constexpr std::uint32_t ecap_evt_capt          = UINT32_C(control_base + 0x0FD4);  // 0x0FD4
        constexpr std::uint32_t adc_evt_capt           = UINT32_C(control_base + 0x0FD8);  // 0x0FD8
        constexpr std::uint32_t reserved24_0x09        = UINT32_C(control_base + 0x0FDC);  // 0x0FDC
        constexpr std::uint32_t reset_iso              = UINT32_C(control_base + 0x1000);  // 0x1000
        constexpr std::uint32_t reserved25_0xc6        = UINT32_C(control_base + 0x1004);  // 0x1004
        constexpr std::uint32_t ddr_cke_ctrl           = UINT32_C(control_base + 0x131C);  // 0x131C
        constexpr std::uint32_t sma2                   = UINT32_C(control_base + 0x1320);  // 0x1320
        constexpr std::uint32_t m3_txev_eoi            = UINT32_C(control_base + 0x1324);  // 0x1324
        constexpr std::uint32_t ipc_msg_reg0           = UINT32_C(control_base + 0x1328);  // 0x1328
        constexpr std::uint32_t ipc_msg_reg1           = UINT32_C(control_base + 0x132C);  // 0x132C
        constexpr std::uint32_t ipc_msg_reg2           = UINT32_C(control_base + 0x1330);  // 0x1330
        constexpr std::uint32_t ipc_msg_reg3           = UINT32_C(control_base + 0x1334);  // 0x1334
        constexpr std::uint32_t ipc_msg_reg4           = UINT32_C(control_base + 0x1338);  // 0x1338
        constexpr std::uint32_t ipc_msg_reg5           = UINT32_C(control_base + 0x133C);  // 0x133C
        constexpr std::uint32_t ipc_msg_reg6           = UINT32_C(control_base + 0x1340);  // 0x1340
        constexpr std::uint32_t ipc_msg_reg7           = UINT32_C(control_base + 0x1344);  // 0x1344
        constexpr std::uint32_t reserved26_0x2f        = UINT32_C(control_base + 0x1348);  // 0x1348
        constexpr std::uint32_t ddr_cmd0_ioctrl        = UINT32_C(control_base + 0x1404);  // 0x1404
        constexpr std::uint32_t ddr_cmd1_ioctrl        = UINT32_C(control_base + 0x1408);  // 0x1408
        constexpr std::uint32_t ddr_cmd2_ioctrl        = UINT32_C(control_base + 0x140C);  // 0x140C
        constexpr std::uint32_t reserved27_0x0c        = UINT32_C(control_base + 0x1410);  // 0x1410
        constexpr std::uint32_t ddr_data0_ioctrl       = UINT32_C(control_base + 0x1440);  // 0x1440
        constexpr std::uint32_t ddr_data1_ioctrl       = UINT32_C(control_base + 0x1444);  // 0x1444
      }

      // Interrupt control registers.
      namespace intc
      {
        namespace sys
        {
          constexpr std::uint32_t itr         = UINT32_C(0x000);  // 0x000
          constexpr std::uint32_t mir         = UINT32_C(0x004);  // 0x004
          constexpr std::uint32_t mir_clear   = UINT32_C(0x008);  // 0x008
          constexpr std::uint32_t mir_set     = UINT32_C(0x00C);  // 0x00C
          constexpr std::uint32_t isr_set     = UINT32_C(0x010);  // 0x010
          constexpr std::uint32_t isr_clear   = UINT32_C(0x014);  // 0x014
          constexpr std::uint32_t pending_irq = UINT32_C(0x018);  // 0x018
          constexpr std::uint32_t pending_fiq = UINT32_C(0x01C);  // 0x01C
        }

        constexpr std::uint32_t revision        = UINT32_C(intc_base + 0x000);  // 0x000
        constexpr std::uint32_t reserved0_0x03  = UINT32_C(intc_base + 0x004);  // 0x004
        constexpr std::uint32_t sysconfig       = UINT32_C(intc_base + 0x010);  // 0x010
        constexpr std::uint32_t sysstatus       = UINT32_C(intc_base + 0x014);  // 0x014
        constexpr std::uint32_t reserved1_0x0a  = UINT32_C(intc_base + 0x018);  // 0x018
        constexpr std::uint32_t sir_irq         = UINT32_C(intc_base + 0x040);  // 0x040
        constexpr std::uint32_t sir_fiq         = UINT32_C(intc_base + 0x044);  // 0x044
        constexpr std::uint32_t control         = UINT32_C(intc_base + 0x048);  // 0x048
        constexpr std::uint32_t protection      = UINT32_C(intc_base + 0x04C);  // 0x04C
        constexpr std::uint32_t idle            = UINT32_C(intc_base + 0x050);  // 0x050
        constexpr std::uint32_t reserved2_0x03  = UINT32_C(intc_base + 0x054);  // 0x054
        constexpr std::uint32_t irq_priority    = UINT32_C(intc_base + 0x060);  // 0x060
        constexpr std::uint32_t fiq_priority    = UINT32_C(intc_base + 0x064);  // 0x064
        constexpr std::uint32_t threshold       = UINT32_C(intc_base + 0x068);  // 0x068
        constexpr std::uint32_t reserved3_0x05  = UINT32_C(intc_base + 0x06C);  // 0x06C
        constexpr std::uint32_t sys_base_0x04   = UINT32_C(intc_base + 0x080);  // 0x080
        constexpr std::uint32_t ilr_base_0x80   = UINT32_C(intc_base + 0x100);  // 0x100
      }

      // Port registers.
      namespace gpiox
      {
        constexpr std::uint32_t revision            = UINT32_C(0x000);  // 0x000
        constexpr std::uint32_t reserved0_0x03      = UINT32_C(0x004);  // 0x004
        constexpr std::uint32_t sysconfig           = UINT32_C(0x010);  // 0x010
        constexpr std::uint32_t reserved1_0x03      = UINT32_C(0x014);  // 0x014
        constexpr std::uint32_t eoi                 = UINT32_C(0x020);  // 0x020
        constexpr std::uint32_t irqstatus_raw_0     = UINT32_C(0x024);  // 0x024
        constexpr std::uint32_t irqstatus_raw_1     = UINT32_C(0x028);  // 0x028
        constexpr std::uint32_t irqstatus_0         = UINT32_C(0x02C);  // 0x02C
        constexpr std::uint32_t irqstatus_1         = UINT32_C(0x030);  // 0x030
        constexpr std::uint32_t irqstatus_set_0     = UINT32_C(0x034);  // 0x034
        constexpr std::uint32_t irqstatus_set_1     = UINT32_C(0x038);  // 0x038
        constexpr std::uint32_t irqstatus_clr_0     = UINT32_C(0x03C);  // 0x03C
        constexpr std::uint32_t irqstatus_clr_1     = UINT32_C(0x040);  // 0x040
        constexpr std::uint32_t reserved2_0x34      = UINT32_C(0x044);  // 0x044
        constexpr std::uint32_t sysstatus           = UINT32_C(0x114);  // 0x114
        constexpr std::uint32_t reserved3_0x06      = UINT32_C(0x118);  // 0x118
        constexpr std::uint32_t ctrl                = UINT32_C(0x130);  // 0x130
        constexpr std::uint32_t oe                  = UINT32_C(0x134);  // 0x134
        constexpr std::uint32_t datain              = UINT32_C(0x138);  // 0x138
        constexpr std::uint32_t dataout             = UINT32_C(0x13C);  // 0x13C
        constexpr std::uint32_t leveldetect0        = UINT32_C(0x140);  // 0x140
        constexpr std::uint32_t leveldetect1        = UINT32_C(0x144);  // 0x144
        constexpr std::uint32_t risingdetect        = UINT32_C(0x148);  // 0x148
        constexpr std::uint32_t fallingdetect       = UINT32_C(0x14C);  // 0x14C
        constexpr std::uint32_t debouncenable       = UINT32_C(0x150);  // 0x150
        constexpr std::uint32_t debouncingtime      = UINT32_C(0x154);  // 0x154
        constexpr std::uint32_t reserved4_0x0e      = UINT32_C(0x158);  // 0x158
        constexpr std::uint32_t cleardataout        = UINT32_C(0x190);  // 0x190
        constexpr std::uint32_t setdataout          = UINT32_C(0x194);  // 0x194
      }

      // Timer registers.
      namespace dmtimer7
      {
        constexpr std::uint32_t tidr          = UINT32_C(dmtimer7_base + 0x000);  // 0x000
        constexpr std::uint32_t reserved0_0   = UINT32_C(dmtimer7_base + 0x004);  // 0x004
        constexpr std::uint32_t reserved0_1   = UINT32_C(dmtimer7_base + 0x008);  // 0x008
        constexpr std::uint32_t reserved0_2   = UINT32_C(dmtimer7_base + 0x00C);  // 0x00C
        constexpr std::uint32_t tiocp_cfg     = UINT32_C(dmtimer7_base + 0x010);  // 0x010
        constexpr std::uint32_t reserved1_0   = UINT32_C(dmtimer7_base + 0x014);  // 0x014
        constexpr std::uint32_t reserved1_1   = UINT32_C(dmtimer7_base + 0x018);  // 0x018
        constexpr std::uint32_t reserved1_2   = UINT32_C(dmtimer7_base + 0x01C);  // 0x01C
        constexpr std::uint32_t irq_eoi       = UINT32_C(dmtimer7_base + 0x020);  // 0x020
        constexpr std::uint32_t irqstatus_raw = UINT32_C(dmtimer7_base + 0x024);  // 0x024
        constexpr std::uint32_t irqstatus     = UINT32_C(dmtimer7_base + 0x028);  // 0x028
        constexpr std::uint32_t irqenable_set = UINT32_C(dmtimer7_base + 0x02C);  // 0x02C
        constexpr std::uint32_t irqenable_clr = UINT32_C(dmtimer7_base + 0x030);  // 0x030
        constexpr std::uint32_t irqwakeen     = UINT32_C(dmtimer7_base + 0x034);  // 0x034
        constexpr std::uint32_t tclr          = UINT32_C(dmtimer7_base + 0x038);  // 0x038
        constexpr std::uint32_t tcrr          = UINT32_C(dmtimer7_base + 0x03C);  // 0x03C
        constexpr std::uint32_t tldr          = UINT32_C(dmtimer7_base + 0x040);  // 0x040
        constexpr std::uint32_t ttgr          = UINT32_C(dmtimer7_base + 0x044);  // 0x044
        constexpr std::uint32_t twps          = UINT32_C(dmtimer7_base + 0x048);  // 0x048
        constexpr std::uint32_t tmar          = UINT32_C(dmtimer7_base + 0x04C);  // 0x04C
        constexpr std::uint32_t tcar1         = UINT32_C(dmtimer7_base + 0x050);  // 0x050
        constexpr std::uint32_t tsicr         = UINT32_C(dmtimer7_base + 0x054);  // 0x054
        constexpr std::uint32_t tcar2         = UINT32_C(dmtimer7_base + 0x058);  // 0x058
      }

      // Watchdog registers.
      namespace wdt1
      {
        static constexpr std::uint32_t widr           = UINT32_C(wdt1_base + 0x000);  // 0x000
        static constexpr std::uint32_t reserved0_0x03 = UINT32_C(wdt1_base + 0x004);  // 0x004
        static constexpr std::uint32_t wdsc           = UINT32_C(wdt1_base + 0x010);  // 0x010
        static constexpr std::uint32_t wdst           = UINT32_C(wdt1_base + 0x014);  // 0x014
        static constexpr std::uint32_t wisr           = UINT32_C(wdt1_base + 0x018);  // 0x018
        static constexpr std::uint32_t wier           = UINT32_C(wdt1_base + 0x01C);  // 0x01C
        static constexpr std::uint32_t reserved1      = UINT32_C(wdt1_base + 0x020);  // 0x020
        static constexpr std::uint32_t wclr           = UINT32_C(wdt1_base + 0x024);  // 0x024
        static constexpr std::uint32_t wcrr           = UINT32_C(wdt1_base + 0x028);  // 0x028
        static constexpr std::uint32_t wldr           = UINT32_C(wdt1_base + 0x02C);  // 0x02C
        static constexpr std::uint32_t wtgr           = UINT32_C(wdt1_base + 0x030);  // 0x030
        static constexpr std::uint32_t wwps           = UINT32_C(wdt1_base + 0x034);  // 0x034
        static constexpr std::uint32_t reserved2_0x03 = UINT32_C(wdt1_base + 0x038);  // 0x038
        static constexpr std::uint32_t wdly           = UINT32_C(wdt1_base + 0x044);  // 0x044
        static constexpr std::uint32_t wspr           = UINT32_C(wdt1_base + 0x048);  // 0x048
        static constexpr std::uint32_t reserved3_0x02 = UINT32_C(wdt1_base + 0x04C);  // 0x04C
        static constexpr std::uint32_t wirqstatraw    = UINT32_C(wdt1_base + 0x054);  // 0x054
        static constexpr std::uint32_t wirqstat       = UINT32_C(wdt1_base + 0x058);  // 0x058
        static constexpr std::uint32_t wirqenset      = UINT32_C(wdt1_base + 0x05C);  // 0x05C
        static constexpr std::uint32_t wirqenclr      = UINT32_C(wdt1_base + 0x060);  // 0x060
      }
    }
  }

  #include <mcal/mcal_reg_access_dynamic.h>
  #include <mcal/mcal_reg_access_static.h>

#endif // MCAL_REG_2010_04_10_H_
