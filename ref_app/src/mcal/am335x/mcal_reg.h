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
      constexpr std::uint32_t l4_wkup_base          = std::uint32_t(0x44C00000UL);                // Wakeup register area base address.
      constexpr std::uint32_t l4_per_base           = std::uint32_t(0x48000000UL);                // Peripheral register area base address.

      constexpr std::uint32_t cm_per_base           = std::uint32_t(l4_wkup_base + 0x200000UL);   // Clock module peripheral base address.
      constexpr std::uint32_t cm_wkup_base          = std::uint32_t(l4_wkup_base + 0x200400UL);   // Clock module wakup base address.
      constexpr std::uint32_t cm_dpll_base          = std::uint32_t(l4_wkup_base + 0x200500UL);   // Clock module DPLL base address.

      constexpr std::uint32_t control_base          = std::uint32_t(l4_wkup_base + 0x210000UL);   // System control base address.

      constexpr std::uint32_t dmtimer7_base         = std::uint32_t(l4_per_base  + 0x04A000UL);   // DM Timer7 base address.

      constexpr std::uint32_t gpio0_base            = std::uint32_t(l4_wkup_base + 0x207000UL);   // GPIO0 base address.
      constexpr std::uint32_t gpio1_base            = std::uint32_t(l4_per_base  + 0x04C000UL);   // GPIO1 base address.
      constexpr std::uint32_t gpio2_base            = std::uint32_t(l4_per_base  + 0x1AC000UL);   // GPIO2 base address.
      constexpr std::uint32_t gpio3_base            = std::uint32_t(l4_per_base  + 0x1AE000UL);   // GPIO3 base address.

      constexpr std::uint32_t wdt1_base             = std::uint32_t(l4_wkup_base + 0x235000UL);   // Watchdog 1 base address.

      constexpr std::uint32_t intc_base             = std::uint32_t(l4_per_base  + 0x200000UL);   // Interrupt controller base address.

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

      // System control registers.
      namespace control
      {
        constexpr std::uint32_t control_revision       = std::uint32_t(control_base + 0x0000UL);  // 0x0000
        constexpr std::uint32_t control_hwinfo         = std::uint32_t(control_base + 0x0004UL);  // 0x0004
        constexpr std::uint32_t reserved0_0            = std::uint32_t(control_base + 0x0008UL);  // 0x0008
        constexpr std::uint32_t reserved0_1            = std::uint32_t(control_base + 0x000CUL);  // 0x000C
        constexpr std::uint32_t control_sysconfig      = std::uint32_t(control_base + 0x0010UL);  // 0x0010
        constexpr std::uint32_t reserved1_0x0b         = std::uint32_t(control_base + 0x0014UL);  // 0x0014
        constexpr std::uint32_t control_status         = std::uint32_t(control_base + 0x0040UL);  // 0x0040
        constexpr std::uint32_t reserved2_0xf6         = std::uint32_t(control_base + 0x0044UL);  // 0x0044
        constexpr std::uint32_t cortex_vbbldo_ctrl     = std::uint32_t(control_base + 0x041CUL);  // 0x041C
        constexpr std::uint32_t reserved3_0x02         = std::uint32_t(control_base + 0x0420UL);  // 0x0420
        constexpr std::uint32_t core_sldo_ctrl         = std::uint32_t(control_base + 0x0428UL);  // 0x0428
        constexpr std::uint32_t mpu_sldo_ctrl          = std::uint32_t(control_base + 0x042CUL);  // 0x042C
        constexpr std::uint32_t reserved4_0x05         = std::uint32_t(control_base + 0x0430UL);  // 0x0430
        constexpr std::uint32_t clk32kdivratio_ctrl    = std::uint32_t(control_base + 0x0444UL);  // 0x0444
        constexpr std::uint32_t bandgap_ctrl           = std::uint32_t(control_base + 0x0448UL);  // 0x0448
        constexpr std::uint32_t bandgap_trim           = std::uint32_t(control_base + 0x044CUL);  // 0x044C
        constexpr std::uint32_t reserved5_0x02         = std::uint32_t(control_base + 0x0450UL);  // 0x0450
        constexpr std::uint32_t pll_clkinpulow_ctrl    = std::uint32_t(control_base + 0x0458UL);  // 0x0458
        constexpr std::uint32_t reserved6_0x03         = std::uint32_t(control_base + 0x045CUL);  // 0x045C
        constexpr std::uint32_t mosc_ctrl              = std::uint32_t(control_base + 0x0468UL);  // 0x0468
        constexpr std::uint32_t rcosc_ctrl             = std::uint32_t(control_base + 0x046CUL);  // 0x046C
        constexpr std::uint32_t deepsleep_ctrl         = std::uint32_t(control_base + 0x0470UL);  // 0x0470
        constexpr std::uint32_t reserved7_0x63         = std::uint32_t(control_base + 0x0474UL);  // 0x0474
        constexpr std::uint32_t device_id              = std::uint32_t(control_base + 0x0600UL);  // 0x0600
        constexpr std::uint32_t dev_feature            = std::uint32_t(control_base + 0x0604UL);  // 0x0604
        constexpr std::uint32_t init_priority_0        = std::uint32_t(control_base + 0x0608UL);  // 0x0608
        constexpr std::uint32_t init_priority_1        = std::uint32_t(control_base + 0x060CUL);  // 0x060C
        constexpr std::uint32_t mmu_cfg                = std::uint32_t(control_base + 0x0610UL);  // 0x0610
        constexpr std::uint32_t tptc_cfg               = std::uint32_t(control_base + 0x0614UL);  // 0x0614
        constexpr std::uint32_t reserved8_0x02         = std::uint32_t(control_base + 0x0618UL);  // 0x0618
        constexpr std::uint32_t usb_ctrl0              = std::uint32_t(control_base + 0x0620UL);  // 0x0620
        constexpr std::uint32_t usb_sts0               = std::uint32_t(control_base + 0x0624UL);  // 0x0624
        constexpr std::uint32_t usb_ctrl1              = std::uint32_t(control_base + 0x0628UL);  // 0x0628
        constexpr std::uint32_t usb_sts1               = std::uint32_t(control_base + 0x062CUL);  // 0x062C
        constexpr std::uint32_t mac_id0_lo             = std::uint32_t(control_base + 0x0630UL);  // 0x0630
        constexpr std::uint32_t mac_id0_hi             = std::uint32_t(control_base + 0x0634UL);  // 0x0634
        constexpr std::uint32_t mac_id1_lo             = std::uint32_t(control_base + 0x0638UL);  // 0x0638
        constexpr std::uint32_t mac_id1_hi             = std::uint32_t(control_base + 0x063CUL);  // 0x063C
        constexpr std::uint32_t reserved9              = std::uint32_t(control_base + 0x0640UL);  // 0x0640
        constexpr std::uint32_t dcan_raminit           = std::uint32_t(control_base + 0x0644UL);  // 0x0644
        constexpr std::uint32_t usb_wkup_ctrl          = std::uint32_t(control_base + 0x0648UL);  // 0x0648
        constexpr std::uint32_t reserved10             = std::uint32_t(control_base + 0x064CUL);  // 0x064C
        constexpr std::uint32_t gmii_sel               = std::uint32_t(control_base + 0x0650UL);  // 0x0650
        constexpr std::uint32_t reserved11_0x04        = std::uint32_t(control_base + 0x0654UL);  // 0x0654
        constexpr std::uint32_t pwmss_ctrl             = std::uint32_t(control_base + 0x0664UL);  // 0x0664
        constexpr std::uint32_t reserved12_0x02        = std::uint32_t(control_base + 0x0668UL);  // 0x0668
        constexpr std::uint32_t mreqprio_0             = std::uint32_t(control_base + 0x0670UL);  // 0x0670
        constexpr std::uint32_t mreqprio_1             = std::uint32_t(control_base + 0x0674UL);  // 0x0674
        constexpr std::uint32_t reserved13_0x06        = std::uint32_t(control_base + 0x0678UL);  // 0x0678
        constexpr std::uint32_t hw_event_sel_grp1      = std::uint32_t(control_base + 0x0690UL);  // 0x0690
        constexpr std::uint32_t hw_event_sel_grp2      = std::uint32_t(control_base + 0x0694UL);  // 0x0694
        constexpr std::uint32_t hw_event_sel_grp3      = std::uint32_t(control_base + 0x0698UL);  // 0x0698
        constexpr std::uint32_t hw_event_sel_grp4      = std::uint32_t(control_base + 0x069CUL);  // 0x069C
        constexpr std::uint32_t smrt_ctrl              = std::uint32_t(control_base + 0x06A0UL);  // 0x06A0
        constexpr std::uint32_t mpuss_hw_debug_sel     = std::uint32_t(control_base + 0x06A4UL);  // 0x06A4
        constexpr std::uint32_t mpuss_hw_dbg_info      = std::uint32_t(control_base + 0x06A8UL);  // 0x06A8
        constexpr std::uint32_t reserved14_0x31        = std::uint32_t(control_base + 0x06ACUL);  // 0x06AC
        constexpr std::uint32_t vdd_mpu_opp_050        = std::uint32_t(control_base + 0x0770UL);  // 0x0770
        constexpr std::uint32_t vdd_mpu_opp_100        = std::uint32_t(control_base + 0x0774UL);  // 0x0774
        constexpr std::uint32_t vdd_mpu_opp_120        = std::uint32_t(control_base + 0x0778UL);  // 0x0778
        constexpr std::uint32_t vdd_mpu_opp_turbo      = std::uint32_t(control_base + 0x077CUL);  // 0x077C
        constexpr std::uint32_t reserved15_0x0e        = std::uint32_t(control_base + 0x0780UL);  // 0x0780
        constexpr std::uint32_t vdd_core_opp_050       = std::uint32_t(control_base + 0x07B8UL);  // 0x07B8
        constexpr std::uint32_t vdd_core_opp_100       = std::uint32_t(control_base + 0x07BCUL);  // 0x07BC
        constexpr std::uint32_t reserved16_0x04        = std::uint32_t(control_base + 0x07C0UL);  // 0x07C0
        constexpr std::uint32_t bb_scale               = std::uint32_t(control_base + 0x07D0UL);  // 0x07D0
        constexpr std::uint32_t reserved17_0x08        = std::uint32_t(control_base + 0x07D4UL);  // 0x07D4
        constexpr std::uint32_t usb_vid_pid            = std::uint32_t(control_base + 0x07F4UL);  // 0x07F4
        constexpr std::uint32_t reserved18_0x02        = std::uint32_t(control_base + 0x07F8UL);  // 0x07F8
        constexpr std::uint32_t conf_gpmc_ad0          = std::uint32_t(control_base + 0x0800UL);  // 0x0800
        constexpr std::uint32_t conf_gpmc_ad1          = std::uint32_t(control_base + 0x0804UL);  // 0x0804
        constexpr std::uint32_t conf_gpmc_ad2          = std::uint32_t(control_base + 0x0808UL);  // 0x0808
        constexpr std::uint32_t conf_gpmc_ad3          = std::uint32_t(control_base + 0x080CUL);  // 0x080C
        constexpr std::uint32_t conf_gpmc_ad4          = std::uint32_t(control_base + 0x0810UL);  // 0x0810
        constexpr std::uint32_t conf_gpmc_ad5          = std::uint32_t(control_base + 0x0814UL);  // 0x0814
        constexpr std::uint32_t conf_gpmc_ad6          = std::uint32_t(control_base + 0x0818UL);  // 0x0818
        constexpr std::uint32_t conf_gpmc_ad7          = std::uint32_t(control_base + 0x081CUL);  // 0x081C
        constexpr std::uint32_t conf_gpmc_ad8          = std::uint32_t(control_base + 0x0820UL);  // 0x0820
        constexpr std::uint32_t conf_gpmc_ad9          = std::uint32_t(control_base + 0x0824UL);  // 0x0824
        constexpr std::uint32_t conf_gpmc_ad10         = std::uint32_t(control_base + 0x0828UL);  // 0x0828
        constexpr std::uint32_t conf_gpmc_ad11         = std::uint32_t(control_base + 0x082CUL);  // 0x082C
        constexpr std::uint32_t conf_gpmc_ad12         = std::uint32_t(control_base + 0x0830UL);  // 0x0830
        constexpr std::uint32_t conf_gpmc_ad13         = std::uint32_t(control_base + 0x0834UL);  // 0x0834
        constexpr std::uint32_t conf_gpmc_ad14         = std::uint32_t(control_base + 0x0838UL);  // 0x0838
        constexpr std::uint32_t conf_gpmc_ad15         = std::uint32_t(control_base + 0x083CUL);  // 0x083C
        constexpr std::uint32_t conf_gpmc_a0           = std::uint32_t(control_base + 0x0840UL);  // 0x0840
        constexpr std::uint32_t conf_gpmc_a1           = std::uint32_t(control_base + 0x0844UL);  // 0x0844
        constexpr std::uint32_t conf_gpmc_a2           = std::uint32_t(control_base + 0x0848UL);  // 0x0848
        constexpr std::uint32_t conf_gpmc_a3           = std::uint32_t(control_base + 0x084CUL);  // 0x084C
        constexpr std::uint32_t conf_gpmc_a4           = std::uint32_t(control_base + 0x0850UL);  // 0x0850
        constexpr std::uint32_t conf_gpmc_a5           = std::uint32_t(control_base + 0x0854UL);  // 0x0854
        constexpr std::uint32_t conf_gpmc_a6           = std::uint32_t(control_base + 0x0858UL);  // 0x0858
        constexpr std::uint32_t conf_gpmc_a7           = std::uint32_t(control_base + 0x085CUL);  // 0x085C
        constexpr std::uint32_t conf_gpmc_a8           = std::uint32_t(control_base + 0x0860UL);  // 0x0860
        constexpr std::uint32_t conf_gpmc_a9           = std::uint32_t(control_base + 0x0864UL);  // 0x0864
        constexpr std::uint32_t conf_gpmc_a10          = std::uint32_t(control_base + 0x0868UL);  // 0x0868
        constexpr std::uint32_t conf_gpmc_a11          = std::uint32_t(control_base + 0x086CUL);  // 0x086C
        constexpr std::uint32_t conf_gpmc_wait0        = std::uint32_t(control_base + 0x0870UL);  // 0x0870
        constexpr std::uint32_t conf_gpmc_wpn          = std::uint32_t(control_base + 0x0874UL);  // 0x0874
        constexpr std::uint32_t conf_gpmc_be1n         = std::uint32_t(control_base + 0x0878UL);  // 0x0878
        constexpr std::uint32_t conf_gpmc_csn0         = std::uint32_t(control_base + 0x087CUL);  // 0x087C
        constexpr std::uint32_t conf_gpmc_csn1         = std::uint32_t(control_base + 0x0880UL);  // 0x0880
        constexpr std::uint32_t conf_gpmc_csn2         = std::uint32_t(control_base + 0x0884UL);  // 0x0884
        constexpr std::uint32_t conf_gpmc_csn3         = std::uint32_t(control_base + 0x0888UL);  // 0x0888
        constexpr std::uint32_t conf_gpmc_clk          = std::uint32_t(control_base + 0x088CUL);  // 0x088C
        constexpr std::uint32_t conf_gpmc_advn_ale     = std::uint32_t(control_base + 0x0890UL);  // 0x0890
        constexpr std::uint32_t conf_gpmc_oen_ren      = std::uint32_t(control_base + 0x0894UL);  // 0x0894
        constexpr std::uint32_t conf_gpmc_wen          = std::uint32_t(control_base + 0x0898UL);  // 0x0898
        constexpr std::uint32_t conf_gpmc_be0n_cle     = std::uint32_t(control_base + 0x089CUL);  // 0x089C
        constexpr std::uint32_t conf_lcd_data0         = std::uint32_t(control_base + 0x08A0UL);  // 0x08A0
        constexpr std::uint32_t conf_lcd_data1         = std::uint32_t(control_base + 0x08A4UL);  // 0x08A4
        constexpr std::uint32_t conf_lcd_data2         = std::uint32_t(control_base + 0x08A8UL);  // 0x08A8
        constexpr std::uint32_t conf_lcd_data3         = std::uint32_t(control_base + 0x08ACUL);  // 0x08AC
        constexpr std::uint32_t conf_lcd_data4         = std::uint32_t(control_base + 0x08B0UL);  // 0x08B0
        constexpr std::uint32_t conf_lcd_data5         = std::uint32_t(control_base + 0x08B4UL);  // 0x08B4
        constexpr std::uint32_t conf_lcd_data6         = std::uint32_t(control_base + 0x08B8UL);  // 0x08B8
        constexpr std::uint32_t conf_lcd_data7         = std::uint32_t(control_base + 0x08BCUL);  // 0x08BC
        constexpr std::uint32_t conf_lcd_data8         = std::uint32_t(control_base + 0x08C0UL);  // 0x08C0
        constexpr std::uint32_t conf_lcd_data9         = std::uint32_t(control_base + 0x08C4UL);  // 0x08C4
        constexpr std::uint32_t conf_lcd_data10        = std::uint32_t(control_base + 0x08C8UL);  // 0x08C8
        constexpr std::uint32_t conf_lcd_data11        = std::uint32_t(control_base + 0x08CCUL);  // 0x08CC
        constexpr std::uint32_t conf_lcd_data12        = std::uint32_t(control_base + 0x08D0UL);  // 0x08D0
        constexpr std::uint32_t conf_lcd_data13        = std::uint32_t(control_base + 0x08D4UL);  // 0x08D4
        constexpr std::uint32_t conf_lcd_data14        = std::uint32_t(control_base + 0x08D8UL);  // 0x08D8
        constexpr std::uint32_t conf_lcd_data15        = std::uint32_t(control_base + 0x08DCUL);  // 0x08DC
        constexpr std::uint32_t conf_lcd_vsync         = std::uint32_t(control_base + 0x08E0UL);  // 0x08E0
        constexpr std::uint32_t conf_lcd_hsync         = std::uint32_t(control_base + 0x08E4UL);  // 0x08E4
        constexpr std::uint32_t conf_lcd_pclk          = std::uint32_t(control_base + 0x08E8UL);  // 0x08E8
        constexpr std::uint32_t conf_lcd_ac_bias_en    = std::uint32_t(control_base + 0x08ECUL);  // 0x08EC
        constexpr std::uint32_t conf_mmc0_dat3         = std::uint32_t(control_base + 0x08F0UL);  // 0x08F0
        constexpr std::uint32_t conf_mmc0_dat2         = std::uint32_t(control_base + 0x08F4UL);  // 0x08F4
        constexpr std::uint32_t conf_mmc0_dat1         = std::uint32_t(control_base + 0x08F8UL);  // 0x08F8
        constexpr std::uint32_t conf_mmc0_dat0         = std::uint32_t(control_base + 0x08FCUL);  // 0x08FC
        constexpr std::uint32_t conf_mmc0_clk          = std::uint32_t(control_base + 0x0900UL);  // 0x0900
        constexpr std::uint32_t conf_mmc0_cmd          = std::uint32_t(control_base + 0x0904UL);  // 0x0904
        constexpr std::uint32_t conf_mii1_col          = std::uint32_t(control_base + 0x0908UL);  // 0x0908
        constexpr std::uint32_t conf_mii1_crs          = std::uint32_t(control_base + 0x090CUL);  // 0x090C
        constexpr std::uint32_t conf_mii1_rxerr        = std::uint32_t(control_base + 0x0910UL);  // 0x0910
        constexpr std::uint32_t conf_mii1_txen         = std::uint32_t(control_base + 0x0914UL);  // 0x0914
        constexpr std::uint32_t conf_mii1_rxdv         = std::uint32_t(control_base + 0x0918UL);  // 0x0918
        constexpr std::uint32_t conf_mii1_txd3         = std::uint32_t(control_base + 0x091CUL);  // 0x091C
        constexpr std::uint32_t conf_mii1_txd2         = std::uint32_t(control_base + 0x0920UL);  // 0x0920
        constexpr std::uint32_t conf_mii1_txd1         = std::uint32_t(control_base + 0x0924UL);  // 0x0924
        constexpr std::uint32_t conf_mii1_txd0         = std::uint32_t(control_base + 0x0928UL);  // 0x0928
        constexpr std::uint32_t conf_mii1_txclk        = std::uint32_t(control_base + 0x092CUL);  // 0x092C
        constexpr std::uint32_t conf_mii1_rxclk        = std::uint32_t(control_base + 0x0930UL);  // 0x0930
        constexpr std::uint32_t conf_mii1_rxd3         = std::uint32_t(control_base + 0x0934UL);  // 0x0934
        constexpr std::uint32_t conf_mii1_rxd2         = std::uint32_t(control_base + 0x0938UL);  // 0x0938
        constexpr std::uint32_t conf_mii1_rxd1         = std::uint32_t(control_base + 0x093CUL);  // 0x093C
        constexpr std::uint32_t conf_mii1_rxd0         = std::uint32_t(control_base + 0x0940UL);  // 0x0940
        constexpr std::uint32_t conf_rmii1_refclk      = std::uint32_t(control_base + 0x0944UL);  // 0x0944
        constexpr std::uint32_t conf_mdio_data         = std::uint32_t(control_base + 0x0948UL);  // 0x0948
        constexpr std::uint32_t conf_mdio_clk          = std::uint32_t(control_base + 0x094CUL);  // 0x094C
        constexpr std::uint32_t conf_spi0_sclk         = std::uint32_t(control_base + 0x0950UL);  // 0x0950
        constexpr std::uint32_t conf_spi0_d0           = std::uint32_t(control_base + 0x0954UL);  // 0x0954
        constexpr std::uint32_t conf_spi0_d1           = std::uint32_t(control_base + 0x0958UL);  // 0x0958
        constexpr std::uint32_t conf_spi0_cs0          = std::uint32_t(control_base + 0x095CUL);  // 0x095C
        constexpr std::uint32_t conf_spi0_cs1          = std::uint32_t(control_base + 0x0960UL);  // 0x0960
        constexpr std::uint32_t conf_ecap0_in_pwm0_out = std::uint32_t(control_base + 0x0964UL);  // 0x0964
        constexpr std::uint32_t conf_uart0_ctsn        = std::uint32_t(control_base + 0x0968UL);  // 0x0968
        constexpr std::uint32_t conf_uart0_rtsn        = std::uint32_t(control_base + 0x096CUL);  // 0x096C
        constexpr std::uint32_t conf_uart0_rxd         = std::uint32_t(control_base + 0x0970UL);  // 0x0970
        constexpr std::uint32_t conf_uart0_txd         = std::uint32_t(control_base + 0x0974UL);  // 0x0974
        constexpr std::uint32_t conf_uart1_ctsn        = std::uint32_t(control_base + 0x0978UL);  // 0x0978
        constexpr std::uint32_t conf_uart1_rtsn        = std::uint32_t(control_base + 0x097CUL);  // 0x097C
        constexpr std::uint32_t conf_uart1_rxd         = std::uint32_t(control_base + 0x0980UL);  // 0x0980
        constexpr std::uint32_t conf_uart1_txd         = std::uint32_t(control_base + 0x0984UL);  // 0x0984
        constexpr std::uint32_t conf_i2c0_sda          = std::uint32_t(control_base + 0x0988UL);  // 0x0988
        constexpr std::uint32_t conf_i2c0_scl          = std::uint32_t(control_base + 0x098CUL);  // 0x098C
        constexpr std::uint32_t conf_mcasp0_aclkx      = std::uint32_t(control_base + 0x0990UL);  // 0x0990
        constexpr std::uint32_t conf_mcasp0_fsx        = std::uint32_t(control_base + 0x0994UL);  // 0x0994
        constexpr std::uint32_t conf_mcasp0_axr0       = std::uint32_t(control_base + 0x0998UL);  // 0x0998
        constexpr std::uint32_t conf_mcasp0_ahclkr     = std::uint32_t(control_base + 0x099CUL);  // 0x099C
        constexpr std::uint32_t conf_mcasp0_aclkr      = std::uint32_t(control_base + 0x09A0UL);  // 0x09A0
        constexpr std::uint32_t conf_mcasp0_fsr        = std::uint32_t(control_base + 0x09A4UL);  // 0x09A4
        constexpr std::uint32_t conf_mcasp0_axr1       = std::uint32_t(control_base + 0x09A8UL);  // 0x09A8
        constexpr std::uint32_t conf_mcasp0_ahclkx     = std::uint32_t(control_base + 0x09ACUL);  // 0x09AC
        constexpr std::uint32_t conf_xdma_event_intr0  = std::uint32_t(control_base + 0x09B0UL);  // 0x09B0
        constexpr std::uint32_t conf_xdma_event_intr1  = std::uint32_t(control_base + 0x09B4UL);  // 0x09B4
        constexpr std::uint32_t conf_nresetin_out      = std::uint32_t(control_base + 0x09B8UL);  // 0x09B8
        constexpr std::uint32_t conf_porz              = std::uint32_t(control_base + 0x09BCUL);  // 0x09BC
        constexpr std::uint32_t conf_nnmi              = std::uint32_t(control_base + 0x09C0UL);  // 0x09C0
        constexpr std::uint32_t conf_osc0_in           = std::uint32_t(control_base + 0x09C4UL);  // 0x09C4
        constexpr std::uint32_t conf_osc0_out          = std::uint32_t(control_base + 0x09C8UL);  // 0x09C8
        constexpr std::uint32_t conf_osc0_vss          = std::uint32_t(control_base + 0x09CCUL);  // 0x09CC
        constexpr std::uint32_t conf_tms               = std::uint32_t(control_base + 0x09D0UL);  // 0x09D0
        constexpr std::uint32_t conf_tdi               = std::uint32_t(control_base + 0x09D4UL);  // 0x09D4
        constexpr std::uint32_t conf_tdo               = std::uint32_t(control_base + 0x09D8UL);  // 0x09D8
        constexpr std::uint32_t conf_tck               = std::uint32_t(control_base + 0x09DCUL);  // 0x09DC
        constexpr std::uint32_t conf_ntrst             = std::uint32_t(control_base + 0x09E0UL);  // 0x09E0
        constexpr std::uint32_t conf_emu0              = std::uint32_t(control_base + 0x09E4UL);  // 0x09E4
        constexpr std::uint32_t conf_emu1              = std::uint32_t(control_base + 0x09E8UL);  // 0x09E8
        constexpr std::uint32_t conf_osc1_in           = std::uint32_t(control_base + 0x09ECUL);  // 0x09EC
        constexpr std::uint32_t conf_osc1_out          = std::uint32_t(control_base + 0x09F0UL);  // 0x09F0
        constexpr std::uint32_t conf_osc1_vss          = std::uint32_t(control_base + 0x09F4UL);  // 0x09F4
        constexpr std::uint32_t conf_rtc_porz          = std::uint32_t(control_base + 0x09F8UL);  // 0x09F8
        constexpr std::uint32_t conf_pmic_power_en     = std::uint32_t(control_base + 0x09FCUL);  // 0x09FC
        constexpr std::uint32_t conf_ext_wakeup        = std::uint32_t(control_base + 0x0A00UL);  // 0x0A00
        constexpr std::uint32_t conf_enz_kaldo_1p8v    = std::uint32_t(control_base + 0x0A04UL);  // 0x0A04
        constexpr std::uint32_t conf_usb0_dm           = std::uint32_t(control_base + 0x0A08UL);  // 0x0A08
        constexpr std::uint32_t conf_usb0_dp           = std::uint32_t(control_base + 0x0A0CUL);  // 0x0A0C
        constexpr std::uint32_t conf_usb0_ce           = std::uint32_t(control_base + 0x0A10UL);  // 0x0A10
        constexpr std::uint32_t conf_usb0_id           = std::uint32_t(control_base + 0x0A14UL);  // 0x0A14
        constexpr std::uint32_t conf_usb0_vbus         = std::uint32_t(control_base + 0x0A18UL);  // 0x0A18
        constexpr std::uint32_t conf_usb0_drvvbus      = std::uint32_t(control_base + 0x0A1CUL);  // 0x0A1C
        constexpr std::uint32_t conf_usb1_dm           = std::uint32_t(control_base + 0x0A20UL);  // 0x0A20
        constexpr std::uint32_t conf_usb1_dp           = std::uint32_t(control_base + 0x0A24UL);  // 0x0A24
        constexpr std::uint32_t conf_usb1_ce           = std::uint32_t(control_base + 0x0A28UL);  // 0x0A28
        constexpr std::uint32_t conf_usb1_id           = std::uint32_t(control_base + 0x0A2CUL);  // 0x0A2C
        constexpr std::uint32_t conf_usb1_vbus         = std::uint32_t(control_base + 0x0A30UL);  // 0x0A30
        constexpr std::uint32_t conf_usb1_drvvbus      = std::uint32_t(control_base + 0x0A34UL);  // 0x0A34
        constexpr std::uint32_t conf_ddr_resetn        = std::uint32_t(control_base + 0x0A38UL);  // 0x0A38
        constexpr std::uint32_t conf_ddr_csn0          = std::uint32_t(control_base + 0x0A3CUL);  // 0x0A3C
        constexpr std::uint32_t conf_ddr_cke           = std::uint32_t(control_base + 0x0A40UL);  // 0x0A40
        constexpr std::uint32_t reserved19             = std::uint32_t(control_base + 0x0A44UL);  // 0x0A44
        constexpr std::uint32_t conf_ddr_nck           = std::uint32_t(control_base + 0x0A48UL);  // 0x0A48
        constexpr std::uint32_t conf_ddr_casn          = std::uint32_t(control_base + 0x0A4CUL);  // 0x0A4C
        constexpr std::uint32_t conf_ddr_rasn          = std::uint32_t(control_base + 0x0A50UL);  // 0x0A50
        constexpr std::uint32_t conf_ddr_wen           = std::uint32_t(control_base + 0x0A54UL);  // 0x0A54
        constexpr std::uint32_t conf_ddr_ba0           = std::uint32_t(control_base + 0x0A58UL);  // 0x0A58
        constexpr std::uint32_t conf_ddr_ba1           = std::uint32_t(control_base + 0x0A5CUL);  // 0x0A5C
        constexpr std::uint32_t conf_ddr_ba2           = std::uint32_t(control_base + 0x0A60UL);  // 0x0A60
        constexpr std::uint32_t conf_ddr_a0            = std::uint32_t(control_base + 0x0A64UL);  // 0x0A64
        constexpr std::uint32_t conf_ddr_a1            = std::uint32_t(control_base + 0x0A68UL);  // 0x0A68
        constexpr std::uint32_t conf_ddr_a2            = std::uint32_t(control_base + 0x0A6CUL);  // 0x0A6C
        constexpr std::uint32_t conf_ddr_a3            = std::uint32_t(control_base + 0x0A70UL);  // 0x0A70
        constexpr std::uint32_t conf_ddr_a4            = std::uint32_t(control_base + 0x0A74UL);  // 0x0A74
        constexpr std::uint32_t conf_ddr_a5            = std::uint32_t(control_base + 0x0A78UL);  // 0x0A78
        constexpr std::uint32_t conf_ddr_a6            = std::uint32_t(control_base + 0x0A7CUL);  // 0x0A7C
        constexpr std::uint32_t conf_ddr_a7            = std::uint32_t(control_base + 0x0A80UL);  // 0x0A80
        constexpr std::uint32_t conf_ddr_a8            = std::uint32_t(control_base + 0x0A84UL);  // 0x0A84
        constexpr std::uint32_t conf_ddr_a9            = std::uint32_t(control_base + 0x0A88UL);  // 0x0A88
        constexpr std::uint32_t conf_ddr_a10           = std::uint32_t(control_base + 0x0A8CUL);  // 0x0A8C
        constexpr std::uint32_t conf_ddr_a11           = std::uint32_t(control_base + 0x0A90UL);  // 0x0A90
        constexpr std::uint32_t conf_ddr_a12           = std::uint32_t(control_base + 0x0A94UL);  // 0x0A94
        constexpr std::uint32_t conf_ddr_a13           = std::uint32_t(control_base + 0x0A98UL);  // 0x0A98
        constexpr std::uint32_t conf_ddr_a14           = std::uint32_t(control_base + 0x0A9CUL);  // 0x0A9C
        constexpr std::uint32_t conf_ddr_a15           = std::uint32_t(control_base + 0x0AA0UL);  // 0x0AA0
        constexpr std::uint32_t conf_ddr_odt           = std::uint32_t(control_base + 0x0AA4UL);  // 0x0AA4
        constexpr std::uint32_t conf_ddr_d0            = std::uint32_t(control_base + 0x0AA8UL);  // 0x0AA8
        constexpr std::uint32_t conf_ddr_d1            = std::uint32_t(control_base + 0x0AACUL);  // 0x0AAC
        constexpr std::uint32_t conf_ddr_d2            = std::uint32_t(control_base + 0x0AB0UL);  // 0x0AB0
        constexpr std::uint32_t conf_ddr_d3            = std::uint32_t(control_base + 0x0AB4UL);  // 0x0AB4
        constexpr std::uint32_t conf_ddr_d4            = std::uint32_t(control_base + 0x0AB8UL);  // 0x0AB8
        constexpr std::uint32_t conf_ddr_d5            = std::uint32_t(control_base + 0x0ABCUL);  // 0x0ABC
        constexpr std::uint32_t conf_ddr_d6            = std::uint32_t(control_base + 0x0AC0UL);  // 0x0AC0
        constexpr std::uint32_t conf_ddr_d7            = std::uint32_t(control_base + 0x0AC4UL);  // 0x0AC4
        constexpr std::uint32_t conf_ddr_d8            = std::uint32_t(control_base + 0x0AC8UL);  // 0x0AC8
        constexpr std::uint32_t conf_ddr_d9            = std::uint32_t(control_base + 0x0ACCUL);  // 0x0ACC
        constexpr std::uint32_t conf_ddr_d10           = std::uint32_t(control_base + 0x0AD0UL);  // 0x0AD0
        constexpr std::uint32_t conf_ddr_d11           = std::uint32_t(control_base + 0x0AD4UL);  // 0x0AD4
        constexpr std::uint32_t conf_ddr_d12           = std::uint32_t(control_base + 0x0AD8UL);  // 0x0AD8
        constexpr std::uint32_t conf_ddr_d13           = std::uint32_t(control_base + 0x0ADCUL);  // 0x0ADC
        constexpr std::uint32_t conf_ddr_d14           = std::uint32_t(control_base + 0x0AE0UL);  // 0x0AE0
        constexpr std::uint32_t conf_ddr_d15           = std::uint32_t(control_base + 0x0AE4UL);  // 0x0AE4
        constexpr std::uint32_t conf_ddr_dqm0          = std::uint32_t(control_base + 0x0AE8UL);  // 0x0AE8
        constexpr std::uint32_t conf_ddr_dqm1          = std::uint32_t(control_base + 0x0AECUL);  // 0x0AEC
        constexpr std::uint32_t conf_ddr_dqs0          = std::uint32_t(control_base + 0x0AF0UL);  // 0x0AF0
        constexpr std::uint32_t conf_ddr_dqsn0         = std::uint32_t(control_base + 0x0AF4UL);  // 0x0AF4
        constexpr std::uint32_t conf_ddr_dqs1          = std::uint32_t(control_base + 0x0AF8UL);  // 0x0AF8
        constexpr std::uint32_t conf_ddr_dqsn1         = std::uint32_t(control_base + 0x0AFCUL);  // 0x0AFC
        constexpr std::uint32_t conf_ddr_vref          = std::uint32_t(control_base + 0x0B00UL);  // 0x0B00
        constexpr std::uint32_t conf_ddr_vtp           = std::uint32_t(control_base + 0x0B04UL);  // 0x0B04
        constexpr std::uint32_t conf_ddr_strben0       = std::uint32_t(control_base + 0x0B08UL);  // 0x0B08
        constexpr std::uint32_t conf_ddr_strben1       = std::uint32_t(control_base + 0x0B0CUL);  // 0x0B0C
        constexpr std::uint32_t conf_ain7              = std::uint32_t(control_base + 0x0B10UL);  // 0x0B10
        constexpr std::uint32_t conf_ain6              = std::uint32_t(control_base + 0x0B14UL);  // 0x0B14
        constexpr std::uint32_t conf_ain5              = std::uint32_t(control_base + 0x0B18UL);  // 0x0B18
        constexpr std::uint32_t conf_ain4              = std::uint32_t(control_base + 0x0B1CUL);  // 0x0B1C
        constexpr std::uint32_t conf_ain3              = std::uint32_t(control_base + 0x0B20UL);  // 0x0B20
        constexpr std::uint32_t conf_ain2              = std::uint32_t(control_base + 0x0B24UL);  // 0x0B24
        constexpr std::uint32_t conf_ain1              = std::uint32_t(control_base + 0x0B28UL);  // 0x0B28
        constexpr std::uint32_t conf_ain0              = std::uint32_t(control_base + 0x0B2CUL);  // 0x0B2C
        constexpr std::uint32_t conf_vrefp             = std::uint32_t(control_base + 0x0B30UL);  // 0x0B30
        constexpr std::uint32_t conf_vrefn             = std::uint32_t(control_base + 0x0B34UL);  // 0x0B34
        constexpr std::uint32_t conf_avdd              = std::uint32_t(control_base + 0x0B38UL);  // 0x0B38
        constexpr std::uint32_t conf_avss              = std::uint32_t(control_base + 0x0B3CUL);  // 0x0B3C
        constexpr std::uint32_t conf_iforce            = std::uint32_t(control_base + 0x0B40UL);  // 0x0B40
        constexpr std::uint32_t conf_vsense            = std::uint32_t(control_base + 0x0B44UL);  // 0x0B44
        constexpr std::uint32_t conf_testout           = std::uint32_t(control_base + 0x0B48UL);  // 0x0B48
        constexpr std::uint32_t reserved20_0xad        = std::uint32_t(control_base + 0x0B4CUL);  // 0x0B4C
        constexpr std::uint32_t cqdetect_status        = std::uint32_t(control_base + 0x0E00UL);  // 0x0E00
        constexpr std::uint32_t ddr_io_ctrl            = std::uint32_t(control_base + 0x0E04UL);  // 0x0E04
        constexpr std::uint32_t reserved21             = std::uint32_t(control_base + 0x0E08UL);  // 0x0E08
        constexpr std::uint32_t vtp_ctrl               = std::uint32_t(control_base + 0x0E0CUL);  // 0x0E0C
        constexpr std::uint32_t reserved22             = std::uint32_t(control_base + 0x0E10UL);  // 0x0E10
        constexpr std::uint32_t vref_ctrl              = std::uint32_t(control_base + 0x0E14UL);  // 0x0E14
        constexpr std::uint32_t reserved23_0x5e        = std::uint32_t(control_base + 0x0E18UL);  // 0x0E18
        constexpr std::uint32_t tpcc_evt_mux_0_3       = std::uint32_t(control_base + 0x0F90UL);  // 0x0F90
        constexpr std::uint32_t tpcc_evt_mux_4_7       = std::uint32_t(control_base + 0x0F94UL);  // 0x0F94
        constexpr std::uint32_t tpcc_evt_mux_8_11      = std::uint32_t(control_base + 0x0F98UL);  // 0x0F98
        constexpr std::uint32_t tpcc_evt_mux_12_15     = std::uint32_t(control_base + 0x0F9CUL);  // 0x0F9C
        constexpr std::uint32_t tpcc_evt_mux_16_19     = std::uint32_t(control_base + 0x0FA0UL);  // 0x0FA0
        constexpr std::uint32_t tpcc_evt_mux_20_23     = std::uint32_t(control_base + 0x0FA4UL);  // 0x0FA4
        constexpr std::uint32_t tpcc_evt_mux_24_27     = std::uint32_t(control_base + 0x0FA8UL);  // 0x0FA8
        constexpr std::uint32_t tpcc_evt_mux_28_31     = std::uint32_t(control_base + 0x0FACUL);  // 0x0FAC
        constexpr std::uint32_t tpcc_evt_mux_32_35     = std::uint32_t(control_base + 0x0FB0UL);  // 0x0FB0
        constexpr std::uint32_t tpcc_evt_mux_36_39     = std::uint32_t(control_base + 0x0FB4UL);  // 0x0FB4
        constexpr std::uint32_t tpcc_evt_mux_40_43     = std::uint32_t(control_base + 0x0FB8UL);  // 0x0FB8
        constexpr std::uint32_t tpcc_evt_mux_44_47     = std::uint32_t(control_base + 0x0FBCUL);  // 0x0FBC
        constexpr std::uint32_t tpcc_evt_mux_48_51     = std::uint32_t(control_base + 0x0FC0UL);  // 0x0FC0
        constexpr std::uint32_t tpcc_evt_mux_52_55     = std::uint32_t(control_base + 0x0FC4UL);  // 0x0FC4
        constexpr std::uint32_t tpcc_evt_mux_56_59     = std::uint32_t(control_base + 0x0FC8UL);  // 0x0FC8
        constexpr std::uint32_t tpcc_evt_mux_60_63     = std::uint32_t(control_base + 0x0FCCUL);  // 0x0FCC
        constexpr std::uint32_t timer_evt_capt         = std::uint32_t(control_base + 0x0FD0UL);  // 0x0FD0
        constexpr std::uint32_t ecap_evt_capt          = std::uint32_t(control_base + 0x0FD4UL);  // 0x0FD4
        constexpr std::uint32_t adc_evt_capt           = std::uint32_t(control_base + 0x0FD8UL);  // 0x0FD8
        constexpr std::uint32_t reserved24_0x09        = std::uint32_t(control_base + 0x0FDCUL);  // 0x0FDC
        constexpr std::uint32_t reset_iso              = std::uint32_t(control_base + 0x1000UL);  // 0x1000
        constexpr std::uint32_t reserved25_0xc6        = std::uint32_t(control_base + 0x1004UL);  // 0x1004
        constexpr std::uint32_t ddr_cke_ctrl           = std::uint32_t(control_base + 0x131CUL);  // 0x131C
        constexpr std::uint32_t sma2                   = std::uint32_t(control_base + 0x1320UL);  // 0x1320
        constexpr std::uint32_t m3_txev_eoi            = std::uint32_t(control_base + 0x1324UL);  // 0x1324
        constexpr std::uint32_t ipc_msg_reg0           = std::uint32_t(control_base + 0x1328UL);  // 0x1328
        constexpr std::uint32_t ipc_msg_reg1           = std::uint32_t(control_base + 0x132CUL);  // 0x132C
        constexpr std::uint32_t ipc_msg_reg2           = std::uint32_t(control_base + 0x1330UL);  // 0x1330
        constexpr std::uint32_t ipc_msg_reg3           = std::uint32_t(control_base + 0x1334UL);  // 0x1334
        constexpr std::uint32_t ipc_msg_reg4           = std::uint32_t(control_base + 0x1338UL);  // 0x1338
        constexpr std::uint32_t ipc_msg_reg5           = std::uint32_t(control_base + 0x133CUL);  // 0x133C
        constexpr std::uint32_t ipc_msg_reg6           = std::uint32_t(control_base + 0x1340UL);  // 0x1340
        constexpr std::uint32_t ipc_msg_reg7           = std::uint32_t(control_base + 0x1344UL);  // 0x1344
        constexpr std::uint32_t reserved26_0x2f        = std::uint32_t(control_base + 0x1348UL);  // 0x1348
        constexpr std::uint32_t ddr_cmd0_ioctrl        = std::uint32_t(control_base + 0x1404UL);  // 0x1404
        constexpr std::uint32_t ddr_cmd1_ioctrl        = std::uint32_t(control_base + 0x1408UL);  // 0x1408
        constexpr std::uint32_t ddr_cmd2_ioctrl        = std::uint32_t(control_base + 0x140CUL);  // 0x140C
        constexpr std::uint32_t reserved27_0x0c        = std::uint32_t(control_base + 0x1410UL);  // 0x1410
        constexpr std::uint32_t ddr_data0_ioctrl       = std::uint32_t(control_base + 0x1440UL);  // 0x1440
        constexpr std::uint32_t ddr_data1_ioctrl       = std::uint32_t(control_base + 0x1444UL);  // 0x1444
      }

      // Interrupt control registers.
      namespace intc
      {
        namespace sys
        {
          constexpr std::uint32_t itr         = std::uint32_t(0x000UL);  // 0x000
          constexpr std::uint32_t mir         = std::uint32_t(0x004UL);  // 0x004
          constexpr std::uint32_t mir_clear   = std::uint32_t(0x008UL);  // 0x008
          constexpr std::uint32_t mir_set     = std::uint32_t(0x00CUL);  // 0x00C
          constexpr std::uint32_t isr_set     = std::uint32_t(0x010UL);  // 0x010
          constexpr std::uint32_t isr_clear   = std::uint32_t(0x014UL);  // 0x014
          constexpr std::uint32_t pending_irq = std::uint32_t(0x018UL);  // 0x018
          constexpr std::uint32_t pending_fiq = std::uint32_t(0x01CUL);  // 0x01C
        }

        constexpr std::uint32_t revision        = std::uint32_t(intc_base + 0x000UL);  // 0x000
        constexpr std::uint32_t reserved0_0x03  = std::uint32_t(intc_base + 0x004UL);  // 0x004
        constexpr std::uint32_t sysconfig       = std::uint32_t(intc_base + 0x010UL);  // 0x010
        constexpr std::uint32_t sysstatus       = std::uint32_t(intc_base + 0x014UL);  // 0x014
        constexpr std::uint32_t reserved1_0x0a  = std::uint32_t(intc_base + 0x018UL);  // 0x018
        constexpr std::uint32_t sir_irq         = std::uint32_t(intc_base + 0x040UL);  // 0x040
        constexpr std::uint32_t sir_fiq         = std::uint32_t(intc_base + 0x044UL);  // 0x044
        constexpr std::uint32_t control         = std::uint32_t(intc_base + 0x048UL);  // 0x048
        constexpr std::uint32_t protection      = std::uint32_t(intc_base + 0x04CUL);  // 0x04C
        constexpr std::uint32_t idle            = std::uint32_t(intc_base + 0x050UL);  // 0x050
        constexpr std::uint32_t reserved2_0x03  = std::uint32_t(intc_base + 0x054UL);  // 0x054
        constexpr std::uint32_t irq_priority    = std::uint32_t(intc_base + 0x060UL);  // 0x060
        constexpr std::uint32_t fiq_priority    = std::uint32_t(intc_base + 0x064UL);  // 0x064
        constexpr std::uint32_t threshold       = std::uint32_t(intc_base + 0x068UL);  // 0x068
        constexpr std::uint32_t reserved3_0x05  = std::uint32_t(intc_base + 0x06CUL);  // 0x06C
        constexpr std::uint32_t sys_base_0x04   = std::uint32_t(intc_base + 0x080UL);  // 0x080
        constexpr std::uint32_t ilr_base_0x80   = std::uint32_t(intc_base + 0x100UL);  // 0x100
      }

      // Port registers.
      namespace gpiox
      {
        constexpr std::uint32_t revision            = std::uint32_t(0x000UL);  // 0x000
        constexpr std::uint32_t reserved0_0x03      = std::uint32_t(0x004UL);  // 0x004
        constexpr std::uint32_t sysconfig           = std::uint32_t(0x010UL);  // 0x010
        constexpr std::uint32_t reserved1_0x03      = std::uint32_t(0x014UL);  // 0x014
        constexpr std::uint32_t eoi                 = std::uint32_t(0x020UL);  // 0x020
        constexpr std::uint32_t irqstatus_RAW_0     = std::uint32_t(0x024UL);  // 0x024
        constexpr std::uint32_t irqstatus_RAW_1     = std::uint32_t(0x028UL);  // 0x028
        constexpr std::uint32_t irqstatus_0         = std::uint32_t(0x02CUL);  // 0x02C
        constexpr std::uint32_t irqstatus_1         = std::uint32_t(0x030UL);  // 0x030
        constexpr std::uint32_t irqstatus_SET_0     = std::uint32_t(0x034UL);  // 0x034
        constexpr std::uint32_t irqstatus_SET_1     = std::uint32_t(0x038UL);  // 0x038
        constexpr std::uint32_t irqstatus_CLR_0     = std::uint32_t(0x03CUL);  // 0x03C
        constexpr std::uint32_t irqstatus_CLR_1     = std::uint32_t(0x040UL);  // 0x040
        constexpr std::uint32_t reserved2_0x34      = std::uint32_t(0x044UL);  // 0x044
        constexpr std::uint32_t sysstatus           = std::uint32_t(0x114UL);  // 0x114
        constexpr std::uint32_t reserved3_0x06      = std::uint32_t(0x118UL);  // 0x118
        constexpr std::uint32_t ctrl                = std::uint32_t(0x130UL);  // 0x130
        constexpr std::uint32_t oe                  = std::uint32_t(0x134UL);  // 0x134
        constexpr std::uint32_t datain              = std::uint32_t(0x138UL);  // 0x138
        constexpr std::uint32_t dataout             = std::uint32_t(0x13CUL);  // 0x13C
        constexpr std::uint32_t leveldetect0        = std::uint32_t(0x140UL);  // 0x140
        constexpr std::uint32_t leveldetect1        = std::uint32_t(0x144UL);  // 0x144
        constexpr std::uint32_t risingdetect        = std::uint32_t(0x148UL);  // 0x148
        constexpr std::uint32_t fallingdetect       = std::uint32_t(0x14CUL);  // 0x14C
        constexpr std::uint32_t debouncenable       = std::uint32_t(0x150UL);  // 0x150
        constexpr std::uint32_t debouncingtime      = std::uint32_t(0x154UL);  // 0x154
        constexpr std::uint32_t reserved4_0x0e      = std::uint32_t(0x158UL);  // 0x158
        constexpr std::uint32_t cleardataout        = std::uint32_t(0x190UL);  // 0x190
        constexpr std::uint32_t setdataout          = std::uint32_t(0x194UL);  // 0x194
      }

      // Timer registers.
      namespace dmtimer7
      {
        constexpr std::uint32_t tidr          = std::uint32_t(dmtimer7_base + 0x000UL);  // 0x000
        constexpr std::uint32_t reserved0_0   = std::uint32_t(dmtimer7_base + 0x004UL);  // 0x004
        constexpr std::uint32_t reserved0_1   = std::uint32_t(dmtimer7_base + 0x008UL);  // 0x008
        constexpr std::uint32_t reserved0_2   = std::uint32_t(dmtimer7_base + 0x00CUL);  // 0x00C
        constexpr std::uint32_t tiocp_cfg     = std::uint32_t(dmtimer7_base + 0x010UL);  // 0x010
        constexpr std::uint32_t reserved1_0   = std::uint32_t(dmtimer7_base + 0x014UL);  // 0x014
        constexpr std::uint32_t reserved1_1   = std::uint32_t(dmtimer7_base + 0x018UL);  // 0x018
        constexpr std::uint32_t reserved1_2   = std::uint32_t(dmtimer7_base + 0x01CUL);  // 0x01C
        constexpr std::uint32_t irq_eoi       = std::uint32_t(dmtimer7_base + 0x020UL);  // 0x020
        constexpr std::uint32_t irqstatus_raw = std::uint32_t(dmtimer7_base + 0x024UL);  // 0x024
        constexpr std::uint32_t irqstatus     = std::uint32_t(dmtimer7_base + 0x028UL);  // 0x028
        constexpr std::uint32_t irqenable_set = std::uint32_t(dmtimer7_base + 0x02CUL);  // 0x02C
        constexpr std::uint32_t irqenable_clr = std::uint32_t(dmtimer7_base + 0x030UL);  // 0x030
        constexpr std::uint32_t irqwakeen     = std::uint32_t(dmtimer7_base + 0x034UL);  // 0x034
        constexpr std::uint32_t tclr          = std::uint32_t(dmtimer7_base + 0x038UL);  // 0x038
        constexpr std::uint32_t tcrr          = std::uint32_t(dmtimer7_base + 0x03CUL);  // 0x03C
        constexpr std::uint32_t tldr          = std::uint32_t(dmtimer7_base + 0x040UL);  // 0x040
        constexpr std::uint32_t ttgr          = std::uint32_t(dmtimer7_base + 0x044UL);  // 0x044
        constexpr std::uint32_t twps          = std::uint32_t(dmtimer7_base + 0x048UL);  // 0x048
        constexpr std::uint32_t tmar          = std::uint32_t(dmtimer7_base + 0x04CUL);  // 0x04C
        constexpr std::uint32_t tcar1         = std::uint32_t(dmtimer7_base + 0x050UL);  // 0x050
        constexpr std::uint32_t tsicr         = std::uint32_t(dmtimer7_base + 0x054UL);  // 0x054
        constexpr std::uint32_t tcar2         = std::uint32_t(dmtimer7_base + 0x058UL);  // 0x058
      }

      // Watchdog registers.
      namespace wdt1
      {
        static constexpr std::uint32_t widr           = std::uint32_t(wdt1_base + 0x000UL);  // 0x000
        static constexpr std::uint32_t reserved0_0x03 = std::uint32_t(wdt1_base + 0x004UL);  // 0x004
        static constexpr std::uint32_t wdsc           = std::uint32_t(wdt1_base + 0x010UL);  // 0x010
        static constexpr std::uint32_t wdst           = std::uint32_t(wdt1_base + 0x014UL);  // 0x014
        static constexpr std::uint32_t wisr           = std::uint32_t(wdt1_base + 0x018UL);  // 0x018
        static constexpr std::uint32_t wier           = std::uint32_t(wdt1_base + 0x01CUL);  // 0x01C
        static constexpr std::uint32_t reserved1      = std::uint32_t(wdt1_base + 0x020UL);  // 0x020
        static constexpr std::uint32_t wclr           = std::uint32_t(wdt1_base + 0x024UL);  // 0x024
        static constexpr std::uint32_t wcrr           = std::uint32_t(wdt1_base + 0x028UL);  // 0x028
        static constexpr std::uint32_t wldr           = std::uint32_t(wdt1_base + 0x02CUL);  // 0x02C
        static constexpr std::uint32_t wtgr           = std::uint32_t(wdt1_base + 0x030UL);  // 0x030
        static constexpr std::uint32_t wwps           = std::uint32_t(wdt1_base + 0x034UL);  // 0x034
        static constexpr std::uint32_t reserved2_0x03 = std::uint32_t(wdt1_base + 0x038UL);  // 0x038
        static constexpr std::uint32_t wdly           = std::uint32_t(wdt1_base + 0x044UL);  // 0x044
        static constexpr std::uint32_t wspr           = std::uint32_t(wdt1_base + 0x048UL);  // 0x048
        static constexpr std::uint32_t reserved3_0x02 = std::uint32_t(wdt1_base + 0x04CUL);  // 0x04C
        static constexpr std::uint32_t wirqstatraw    = std::uint32_t(wdt1_base + 0x054UL);  // 0x054
        static constexpr std::uint32_t wirqstat       = std::uint32_t(wdt1_base + 0x058UL);  // 0x058
        static constexpr std::uint32_t wirqenset      = std::uint32_t(wdt1_base + 0x05CUL);  // 0x05C
        static constexpr std::uint32_t wirqenclr      = std::uint32_t(wdt1_base + 0x060UL);  // 0x060
      }
    }
  }

#endif // _MCAL_REG_2010_04_10_H_
