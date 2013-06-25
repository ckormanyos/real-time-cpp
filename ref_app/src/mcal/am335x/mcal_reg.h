///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _MCAL_REG_2010_04_10_H_
  #define _MCAL_REG_2010_04_10_H_

  #include <cstdint>

  namespace mcal
  {
    namespace reg
    {
      // Base addresses.
      constexpr std::uint32_t l4_wkup_base            = std::uint32_t(0x44C00000UL);                // Peripheral base address in the alias region.

      constexpr std::uint32_t cm_per_base             = std::uint32_t(l4_wkup_base + 0x200000UL);   // Clock module peripheral base.
      constexpr std::uint32_t cm_wkup_base            = std::uint32_t(l4_wkup_base + 0x200400UL);   // Clock module wakup base.
      constexpr std::uint32_t cm_dpll_base            = std::uint32_t(l4_wkup_base + 0x200500UL);   // Clock module DPLL base.

      // Clock module registers.
      namespace cm_per
      {
        constexpr std::uint32_t l4ls_clkstctrl      = std::uint32_t(cm_per_base + 0x000UL);  // 0x000
        constexpr std::uint32_t l3s_clkstctrl       = std::uint32_t(cm_per_base + 0x004UL);  // 0x004
        constexpr std::uint32_t reserved0           = std::uint32_t(cm_per_base + 0x008UL);  // 0x008
        constexpr std::uint32_t l3_clkstctrl        = std::uint32_t(cm_per_base + 0x00CUL);  // 0x00C
        constexpr std::uint32_t reserved1           = std::uint32_t(cm_per_base + 0x010UL);  // 0x010
        constexpr std::uint32_t cpgmac0_clkctrl     = std::uint32_t(cm_per_base + 0x014UL);  // 0x014
        constexpr std::uint32_t lcdc_clkctrl        = std::uint32_t(cm_per_base + 0x018UL);  // 0x018
        constexpr std::uint32_t usb0_clkctrl        = std::uint32_t(cm_per_base + 0x01CUL);  // 0x01C
        constexpr std::uint32_t reserved2           = std::uint32_t(cm_per_base + 0x020UL);  // 0x020
        constexpr std::uint32_t tptc0_clkctrl       = std::uint32_t(cm_per_base + 0x024UL);  // 0x024
        constexpr std::uint32_t emif_clkctrl        = std::uint32_t(cm_per_base + 0x028UL);  // 0x028
        constexpr std::uint32_t ocmcram_clkctrl     = std::uint32_t(cm_per_base + 0x02CUL);  // 0x02C
        constexpr std::uint32_t gpmc_clkctrl        = std::uint32_t(cm_per_base + 0x030UL);  // 0x030
        constexpr std::uint32_t mcasp0_clkctrl      = std::uint32_t(cm_per_base + 0x034UL);  // 0x034
        constexpr std::uint32_t uart5_clkctrl       = std::uint32_t(cm_per_base + 0x038UL);  // 0x038
        constexpr std::uint32_t mmc0_clkctrl        = std::uint32_t(cm_per_base + 0x03CUL);  // 0x03C
        constexpr std::uint32_t elm_clkctrl         = std::uint32_t(cm_per_base + 0x040UL);  // 0x040
        constexpr std::uint32_t i2c2_clkctrl        = std::uint32_t(cm_per_base + 0x044UL);  // 0x044
        constexpr std::uint32_t i2c1_clkctrl        = std::uint32_t(cm_per_base + 0x048UL);  // 0x048
        constexpr std::uint32_t spi0_clkctrl        = std::uint32_t(cm_per_base + 0x04CUL);  // 0x04C
        constexpr std::uint32_t spi1_clkctrl        = std::uint32_t(cm_per_base + 0x050UL);  // 0x050
        constexpr std::uint32_t reserved3_0         = std::uint32_t(cm_per_base + 0x054UL);  // 0x054
        constexpr std::uint32_t reserved3_1         = std::uint32_t(cm_per_base + 0x058UL);  // 0x058
        constexpr std::uint32_t reserved3_2         = std::uint32_t(cm_per_base + 0x05CUL);  // 0x05C
        constexpr std::uint32_t l4ls_clkctrl        = std::uint32_t(cm_per_base + 0x060UL);  // 0x060
        constexpr std::uint32_t l4fw_clkctrl        = std::uint32_t(cm_per_base + 0x064UL);  // 0x064
        constexpr std::uint32_t mcasp1_clkctrl      = std::uint32_t(cm_per_base + 0x068UL);  // 0x068
        constexpr std::uint32_t uart1_clkctrl       = std::uint32_t(cm_per_base + 0x06CUL);  // 0x06C
        constexpr std::uint32_t uart2_clkctrl       = std::uint32_t(cm_per_base + 0x070UL);  // 0x070
        constexpr std::uint32_t uart3_clkctrl       = std::uint32_t(cm_per_base + 0x074UL);  // 0x074
        constexpr std::uint32_t uart4_clkctrl       = std::uint32_t(cm_per_base + 0x078UL);  // 0x078
        constexpr std::uint32_t timer7_clkctrl      = std::uint32_t(cm_per_base + 0x07CUL);  // 0x07C
        constexpr std::uint32_t timer2_clkctrl      = std::uint32_t(cm_per_base + 0x080UL);  // 0x080
        constexpr std::uint32_t timer3_clkctrl      = std::uint32_t(cm_per_base + 0x084UL);  // 0x084
        constexpr std::uint32_t timer4_clkctrl      = std::uint32_t(cm_per_base + 0x088UL);  // 0x088
        constexpr std::uint32_t reserved4_0         = std::uint32_t(cm_per_base + 0x08CUL);  // 0x08C
        constexpr std::uint32_t reserved4_1         = std::uint32_t(cm_per_base + 0x090UL);  // 0x090
        constexpr std::uint32_t reserved4_2         = std::uint32_t(cm_per_base + 0x094UL);  // 0x094
        constexpr std::uint32_t reserved4_3         = std::uint32_t(cm_per_base + 0x098UL);  // 0x098
        constexpr std::uint32_t reserved4_4         = std::uint32_t(cm_per_base + 0x09CUL);  // 0x09C
        constexpr std::uint32_t reserved4_5         = std::uint32_t(cm_per_base + 0x0A0UL);  // 0x0A0
        constexpr std::uint32_t reserved4_6         = std::uint32_t(cm_per_base + 0x0A4UL);  // 0x0A4
        constexpr std::uint32_t reserved4_7         = std::uint32_t(cm_per_base + 0x0A8UL);  // 0x0A8
        constexpr std::uint32_t gpio1_clkctrl       = std::uint32_t(cm_per_base + 0x0ACUL);  // 0x0AC
        constexpr std::uint32_t gpio2_clkctrl       = std::uint32_t(cm_per_base + 0x0B0UL);  // 0x0B0
        constexpr std::uint32_t gpio3_clkctrl       = std::uint32_t(cm_per_base + 0x0B4UL);  // 0x0B4
        constexpr std::uint32_t reserved5           = std::uint32_t(cm_per_base + 0x0B8UL);  // 0x0B8
        constexpr std::uint32_t tpcc_clkctrl        = std::uint32_t(cm_per_base + 0x0BCUL);  // 0x0BC
        constexpr std::uint32_t dcan0_clkctrl       = std::uint32_t(cm_per_base + 0x0C0UL);  // 0x0C0
        constexpr std::uint32_t dcan1_clkctrl       = std::uint32_t(cm_per_base + 0x0C4UL);  // 0x0C4
        constexpr std::uint32_t reserved6           = std::uint32_t(cm_per_base + 0x0C8UL);  // 0x0C8
        constexpr std::uint32_t epwmss1_clkctrl     = std::uint32_t(cm_per_base + 0x0CCUL);  // 0x0CC
        constexpr std::uint32_t reserved7           = std::uint32_t(cm_per_base + 0x0D0UL);  // 0x0D0
        constexpr std::uint32_t epwmss0_clkctrl     = std::uint32_t(cm_per_base + 0x0D4UL);  // 0x0D4
        constexpr std::uint32_t epwmss2_clkctrl     = std::uint32_t(cm_per_base + 0x0D8UL);  // 0x0D8
        constexpr std::uint32_t l3_instr_clkctrl    = std::uint32_t(cm_per_base + 0x0DCUL);  // 0x0DC
        constexpr std::uint32_t l3_clkctrl          = std::uint32_t(cm_per_base + 0x0E0UL);  // 0x0E0
        constexpr std::uint32_t ieee5000_clkctrl    = std::uint32_t(cm_per_base + 0x0E4UL);  // 0x0E4
        constexpr std::uint32_t pruss_clkctrl       = std::uint32_t(cm_per_base + 0x0E8UL);  // 0x0E8
        constexpr std::uint32_t timer5_clkctrl      = std::uint32_t(cm_per_base + 0x0ECUL);  // 0x0EC
        constexpr std::uint32_t timer6_clkctrl      = std::uint32_t(cm_per_base + 0x0F0UL);  // 0x0F0
        constexpr std::uint32_t mmc1_clkctrl        = std::uint32_t(cm_per_base + 0x0F4UL);  // 0x0F4
        constexpr std::uint32_t mmc2_clkctrl        = std::uint32_t(cm_per_base + 0x0F8UL);  // 0x0F8
        constexpr std::uint32_t tptc1_clkctrl       = std::uint32_t(cm_per_base + 0x0FCUL);  // 0x0FC
        constexpr std::uint32_t tptc2_clkctrl       = std::uint32_t(cm_per_base + 0x100UL);  // 0x100
        constexpr std::uint32_t reserved8_0         = std::uint32_t(cm_per_base + 0x104UL);  // 0x104
        constexpr std::uint32_t reserved8_1         = std::uint32_t(cm_per_base + 0x108UL);  // 0x108
        constexpr std::uint32_t spinlock_clkctrl    = std::uint32_t(cm_per_base + 0x10CUL);  // 0x10C
        constexpr std::uint32_t mailbox0_clkctrl    = std::uint32_t(cm_per_base + 0x110UL);  // 0x110
        constexpr std::uint32_t reserved9_0         = std::uint32_t(cm_per_base + 0x114UL);  // 0x114
        constexpr std::uint32_t reserved9_1         = std::uint32_t(cm_per_base + 0x118UL);  // 0x118
        constexpr std::uint32_t l4hs_clkstctrl      = std::uint32_t(cm_per_base + 0x11CUL);  // 0x11C
        constexpr std::uint32_t l4hs_clkctrl        = std::uint32_t(cm_per_base + 0x120UL);  // 0x120
        constexpr std::uint32_t reserved10_0        = std::uint32_t(cm_per_base + 0x124UL);  // 0x124
        constexpr std::uint32_t reserved10_1        = std::uint32_t(cm_per_base + 0x128UL);  // 0x128
        constexpr std::uint32_t ocpwp_l3_clkstctrl  = std::uint32_t(cm_per_base + 0x12CUL);  // 0x12C
        constexpr std::uint32_t ocpwp_clkctrl       = std::uint32_t(cm_per_base + 0x130UL);  // 0x130
        constexpr std::uint32_t reserved11_0        = std::uint32_t(cm_per_base + 0x134UL);  // 0x134
        constexpr std::uint32_t reserved11_1        = std::uint32_t(cm_per_base + 0x138UL);  // 0x138
        constexpr std::uint32_t reserved11_2        = std::uint32_t(cm_per_base + 0x13CUL);  // 0x13C
        constexpr std::uint32_t pruss_clkstctrl     = std::uint32_t(cm_per_base + 0x140UL);  // 0x140
        constexpr std::uint32_t cpsw_clkstctrl      = std::uint32_t(cm_per_base + 0x144UL);  // 0x144
        constexpr std::uint32_t lcdc_clkstctrl      = std::uint32_t(cm_per_base + 0x148UL);  // 0x148
        constexpr std::uint32_t clkdiv32k_clkctrl   = std::uint32_t(cm_per_base + 0x14CUL);  // 0x14C
        constexpr std::uint32_t clk_24mhz_clkstctrl = std::uint32_t(cm_per_base + 0x150UL);  // 0x150
      }

      namespace cm_wkup
      {
        constexpr std::uint32_t clkstctrl                = std::uint32_t(cm_wkup_base + 0x000UL);  // 0x000
        constexpr std::uint32_t control_clkctrl          = std::uint32_t(cm_wkup_base + 0x004UL);  // 0x004
        constexpr std::uint32_t gpio0_clkctrl            = std::uint32_t(cm_wkup_base + 0x008UL);  // 0x008
        constexpr std::uint32_t l4wkup_clkctrl           = std::uint32_t(cm_wkup_base + 0x00CUL);  // 0x00C
        constexpr std::uint32_t timer0_clkctrl           = std::uint32_t(cm_wkup_base + 0x010UL);  // 0x010
        constexpr std::uint32_t debugss_clkctrl          = std::uint32_t(cm_wkup_base + 0x014UL);  // 0x014
        constexpr std::uint32_t l3_aon_clkstctrl         = std::uint32_t(cm_wkup_base + 0x018UL);  // 0x018
        constexpr std::uint32_t autoidle_dpll_mpu        = std::uint32_t(cm_wkup_base + 0x01CUL);  // 0x01C
        constexpr std::uint32_t idlest_dpll_mpu          = std::uint32_t(cm_wkup_base + 0x020UL);  // 0x020
        constexpr std::uint32_t ssc_deltamstep_dpll_mpu  = std::uint32_t(cm_wkup_base + 0x024UL);  // 0x024
        constexpr std::uint32_t ssc_modfreqdiv_dpll_mpu  = std::uint32_t(cm_wkup_base + 0x028UL);  // 0x028
        constexpr std::uint32_t clksel_dpll_mpu          = std::uint32_t(cm_wkup_base + 0x02CUL);  // 0x02C
        constexpr std::uint32_t autoidle_dpll_ddr        = std::uint32_t(cm_wkup_base + 0x030UL);  // 0x030
        constexpr std::uint32_t idlest_dpll_ddr          = std::uint32_t(cm_wkup_base + 0x034UL);  // 0x034
        constexpr std::uint32_t ssc_deltamstep_dpll_ddr  = std::uint32_t(cm_wkup_base + 0x038UL);  // 0x038
        constexpr std::uint32_t ssc_modfreqdiv_dpll_ddr  = std::uint32_t(cm_wkup_base + 0x03CUL);  // 0x03C
        constexpr std::uint32_t clksel_dpll_ddr          = std::uint32_t(cm_wkup_base + 0x040UL);  // 0x040
        constexpr std::uint32_t autoidle_dpll_disp       = std::uint32_t(cm_wkup_base + 0x044UL);  // 0x044
        constexpr std::uint32_t idlest_dpll_disp         = std::uint32_t(cm_wkup_base + 0x048UL);  // 0x048
        constexpr std::uint32_t ssc_deltamstep_dpll_disp = std::uint32_t(cm_wkup_base + 0x04CUL);  // 0x04C
        constexpr std::uint32_t ssc_modfreqdiv_dpll_disp = std::uint32_t(cm_wkup_base + 0x050UL);  // 0x050
        constexpr std::uint32_t clksel_dpll_disp         = std::uint32_t(cm_wkup_base + 0x054UL);  // 0x054
        constexpr std::uint32_t autoidle_dpll_core       = std::uint32_t(cm_wkup_base + 0x058UL);  // 0x058
        constexpr std::uint32_t idlest_dpll_core         = std::uint32_t(cm_wkup_base + 0x05CUL);  // 0x05C
        constexpr std::uint32_t ssc_deltamstep_dpll_core = std::uint32_t(cm_wkup_base + 0x060UL);  // 0x060
        constexpr std::uint32_t ssc_modfreqdiv_dpll_core = std::uint32_t(cm_wkup_base + 0x064UL);  // 0x064
        constexpr std::uint32_t clksel_dpll_core         = std::uint32_t(cm_wkup_base + 0x068UL);  // 0x068
        constexpr std::uint32_t autoidle_dpll_per        = std::uint32_t(cm_wkup_base + 0x06CUL);  // 0x06C
        constexpr std::uint32_t idlest_dpll_per          = std::uint32_t(cm_wkup_base + 0x070UL);  // 0x070
        constexpr std::uint32_t ssc_deltamstep_dpll_per  = std::uint32_t(cm_wkup_base + 0x074UL);  // 0x074
        constexpr std::uint32_t ssc_modfreqdiv_dpll_per  = std::uint32_t(cm_wkup_base + 0x078UL);  // 0x078
        constexpr std::uint32_t clkdcoldo_dpll_per       = std::uint32_t(cm_wkup_base + 0x07CUL);  // 0x07C
        constexpr std::uint32_t div_m4_dpll_core         = std::uint32_t(cm_wkup_base + 0x080UL);  // 0x080
        constexpr std::uint32_t div_m5_dpll_core         = std::uint32_t(cm_wkup_base + 0x084UL);  // 0x084
        constexpr std::uint32_t clkmode_dpll_mpu         = std::uint32_t(cm_wkup_base + 0x088UL);  // 0x088
        constexpr std::uint32_t clkmode_dpll_per         = std::uint32_t(cm_wkup_base + 0x08CUL);  // 0x08C
        constexpr std::uint32_t clkmode_dpll_core        = std::uint32_t(cm_wkup_base + 0x090UL);  // 0x090
        constexpr std::uint32_t clkmode_dpll_ddr         = std::uint32_t(cm_wkup_base + 0x094UL);  // 0x094
        constexpr std::uint32_t clkmode_dpll_disp        = std::uint32_t(cm_wkup_base + 0x098UL);  // 0x098
        constexpr std::uint32_t clksel_dpll_periph       = std::uint32_t(cm_wkup_base + 0x09CUL);  // 0x09C
        constexpr std::uint32_t div_m2_dpll_ddr          = std::uint32_t(cm_wkup_base + 0x0A0UL);  // 0x0A0
        constexpr std::uint32_t div_m2_dpll_disp         = std::uint32_t(cm_wkup_base + 0x0A4UL);  // 0x0A4
        constexpr std::uint32_t div_m2_dpll_mpu          = std::uint32_t(cm_wkup_base + 0x0A8UL);  // 0x0A8
        constexpr std::uint32_t div_m2_dpll_per          = std::uint32_t(cm_wkup_base + 0x0ACUL);  // 0x0AC
        constexpr std::uint32_t wkup_m3_clkctrl          = std::uint32_t(cm_wkup_base + 0x0B0UL);  // 0x0B0
        constexpr std::uint32_t uart0_clkctrl            = std::uint32_t(cm_wkup_base + 0x0B4UL);  // 0x0B4
        constexpr std::uint32_t i2c0_clkctrl             = std::uint32_t(cm_wkup_base + 0x0B8UL);  // 0x0B8
        constexpr std::uint32_t adc_tsc_clkctrl          = std::uint32_t(cm_wkup_base + 0x0BCUL);  // 0x0BC
        constexpr std::uint32_t smartreflex0_clkctrl     = std::uint32_t(cm_wkup_base + 0x0C0UL);  // 0x0C0
        constexpr std::uint32_t timer1_clkctrl           = std::uint32_t(cm_wkup_base + 0x0C4UL);  // 0x0C4
        constexpr std::uint32_t smartreflex1_clkctrl     = std::uint32_t(cm_wkup_base + 0x0C8UL);  // 0x0C8
        constexpr std::uint32_t l4_wkup_aon_clkstctrl    = std::uint32_t(cm_wkup_base + 0x0CCUL);  // 0x0CC
        constexpr std::uint32_t reserved0                = std::uint32_t(cm_wkup_base + 0x0D0UL);  // 0x0D0
        constexpr std::uint32_t wdt1_clkctrl             = std::uint32_t(cm_wkup_base + 0x0D4UL);  // 0x0D4
        constexpr std::uint32_t div_m6_dpll_core         = std::uint32_t(cm_wkup_base + 0x0D8UL);  // 0x0D8
      }

      namespace cm_dpll
      {
        constexpr std::uint32_t reserved0             = std::uint32_t(cm_dpll_base + 0x000UL);  // 0x000
        constexpr std::uint32_t clksel_timer7_clk     = std::uint32_t(cm_dpll_base + 0x004UL);  // 0x004
        constexpr std::uint32_t clksel_timer2_clk     = std::uint32_t(cm_dpll_base + 0x008UL);  // 0x008
        constexpr std::uint32_t clksel_timer3_clk     = std::uint32_t(cm_dpll_base + 0x00CUL);  // 0x00C
        constexpr std::uint32_t clksel_timer4_clk     = std::uint32_t(cm_dpll_base + 0x010UL);  // 0x010
        constexpr std::uint32_t cm_mac_clksel         = std::uint32_t(cm_dpll_base + 0x014UL);  // 0x014
        constexpr std::uint32_t clksel_timer5_clk     = std::uint32_t(cm_dpll_base + 0x018UL);  // 0x018
        constexpr std::uint32_t clksel_timer6_clk     = std::uint32_t(cm_dpll_base + 0x01CUL);  // 0x01C
        constexpr std::uint32_t cm_cpts_rft_clksel    = std::uint32_t(cm_dpll_base + 0x020UL);  // 0x020
        constexpr std::uint32_t reserved1             = std::uint32_t(cm_dpll_base + 0x024UL);  // 0x024
        constexpr std::uint32_t clksel_timer1ms_clk   = std::uint32_t(cm_dpll_base + 0x028UL);  // 0x028
        constexpr std::uint32_t clksel_gfx_fclk       = std::uint32_t(cm_dpll_base + 0x02CUL);  // 0x02C
        constexpr std::uint32_t clksel_pruss_ocp_clk  = std::uint32_t(cm_dpll_base + 0x030UL);  // 0x030
        constexpr std::uint32_t clksel_lcdc_pixel_clk = std::uint32_t(cm_dpll_base + 0x034UL);  // 0x034
        constexpr std::uint32_t clksel_wdt1_clk       = std::uint32_t(cm_dpll_base + 0x038UL);  // 0x038
        constexpr std::uint32_t clksel_gpio0_dbclk    = std::uint32_t(cm_dpll_base + 0x03CUL);  // 0x03C
      }

      // Interrupt registers.

      // Port registers.

      // Timer registers.

      // Power management registers.
    }
  }
#endif // _MCAL_REG_2010_04_10_H_
