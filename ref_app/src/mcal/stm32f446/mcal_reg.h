///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2022.
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
      // Global base addresses.
      constexpr std::uint32_t periph_base     = UINT32_C(0x40000000);
      constexpr std::uint32_t scs_base        = UINT32_C(0xE000E000);

      // Individual unit base addresses.
      constexpr std::uint32_t scb_base        = scs_base        + UINT32_C(0x00000D00);
      constexpr std::uint32_t nvic_base       = scs_base        + UINT32_C(0x00000100);
      constexpr std::uint32_t sys_tick_base   = scs_base        + UINT32_C(0x00000010);
      constexpr std::uint32_t apb1periph_base = periph_base     + UINT32_C(0x00000000);
      constexpr std::uint32_t pwr_base        = apb1periph_base + UINT32_C(0x00007000);
      constexpr std::uint32_t ahb1periph_base = periph_base     + UINT32_C(0x00020000);
      constexpr std::uint32_t rcc_base        = ahb1periph_base + UINT32_C(0x00003800);
      constexpr std::uint32_t flash_r_base    = ahb1periph_base + UINT32_C(0x00003C00);

      constexpr std::uint32_t sys_tick_ctrl   = sys_tick_base   + UINT32_C(0x00000000);
      constexpr std::uint32_t sys_tick_load   = sys_tick_base   + UINT32_C(0x00000004);
      constexpr std::uint32_t sys_tick_val    = sys_tick_base   + UINT32_C(0x00000008);
      constexpr std::uint32_t sys_tick_cal    = sys_tick_base   + UINT32_C(0x0000000C);

      constexpr std::uint32_t gpioa_base      = ahb1periph_base + UINT32_C(0x0000);
      constexpr std::uint32_t gpiob_base      = ahb1periph_base + UINT32_C(0x0400);
      constexpr std::uint32_t gpioc_base      = ahb1periph_base + UINT32_C(0x0800);
      constexpr std::uint32_t gpiod_base      = ahb1periph_base + UINT32_C(0x0C00);
      constexpr std::uint32_t gpioe_base      = ahb1periph_base + UINT32_C(0x1000);
      constexpr std::uint32_t gpiof_base      = ahb1periph_base + UINT32_C(0x1400);
      constexpr std::uint32_t gpiog_base      = ahb1periph_base + UINT32_C(0x1800);

      constexpr std::uint32_t tim4_base       = periph_base     + UINT32_C(0x0800);

      constexpr std::uint32_t iwdg_base       = periph_base     + UINT32_C(0x3000);

      // System registers.
      constexpr std::uint32_t scb_cpuid       = scb_base        + UINT32_C(0x0000);  // 32-bit register.
      constexpr std::uint32_t scb_icsr        = scb_base        + UINT32_C(0x0004);  // 32-bit register.
      constexpr std::uint32_t scb_vtor        = scb_base        + UINT32_C(0x0008);  // 32-bit register.
      constexpr std::uint32_t scb_cpacr       = scb_base        + UINT32_C(0x0088);  // 32-bit register.
      constexpr std::uint32_t aircr           = scb_base        + UINT32_C(0x000C);  // 32-bit register. SCB application interrupt / reset control.

      // Interrupt registers.
      constexpr std::uint32_t rcc_cr          = rcc_base        + UINT32_C(0x0000);  // 32-bit register.
      constexpr std::uint32_t rcc_pllcfgr     = rcc_base        + UINT32_C(0x0004);  // 32-bit register.
      constexpr std::uint32_t rcc_cfgr        = rcc_base        + UINT32_C(0x0008);  // 32-bit register.
      constexpr std::uint32_t rcc_cir         = rcc_base        + UINT32_C(0x000C);  // 32-bit register.

      // Flash memory registers.
      constexpr std::uint32_t flash_acr       = flash_r_base    + UINT32_C(0x0000);  // 32-bit register.
      constexpr std::uint32_t flash_keyr      = flash_r_base    + UINT32_C(0x0004);  // 32-bit register.
      constexpr std::uint32_t flash_optkeyr   = flash_r_base    + UINT32_C(0x0008);  // 32-bit register.
      constexpr std::uint32_t flash_sr        = flash_r_base    + UINT32_C(0x000C);  // 32-bit register.
      constexpr std::uint32_t flash_cr        = flash_r_base    + UINT32_C(0x0010);  // 32-bit register.
      constexpr std::uint32_t flash_optcr     = flash_r_base    + UINT32_C(0x0014);  // 32-bit register.
      constexpr std::uint32_t flash_optcr1    = flash_r_base    + UINT32_C(0x0018);  // 32-bit register.

      // Power control registers.
      constexpr std::uint32_t pwr_cr          = pwr_base        + UINT32_C(0x0000);  // 32-bit register.
      constexpr std::uint32_t pwr_csr         = pwr_base        + UINT32_C(0x0004);  // 32-bit register.

      // Port registers.
      constexpr std::uint32_t gpioa_moder     = gpioa_base      + UINT32_C(0x0000);  // 32-bit register.
      constexpr std::uint32_t gpioa_otyper    = gpioa_base      + UINT32_C(0x0004);  // 32-bit register.
      constexpr std::uint32_t gpioa_ospeedr   = gpioa_base      + UINT32_C(0x0008);  // 32-bit register.
      constexpr std::uint32_t gpioa_pupdr     = gpioa_base      + UINT32_C(0x000C);  // 32-bit register.
      constexpr std::uint32_t gpioa_idr       = gpioa_base      + UINT32_C(0x0010);  // 32-bit register.
      constexpr std::uint32_t gpioa_odr       = gpioa_base      + UINT32_C(0x0014);  // 32-bit register.
      constexpr std::uint32_t gpioa_bsrr      = gpioa_base      + UINT32_C(0x0018);  // 32-bit register.
      constexpr std::uint32_t gpioa_lckr      = gpioa_base      + UINT32_C(0x001C);  // 32-bit register.
      constexpr std::uint32_t gpioa_afrl      = gpioa_base      + UINT32_C(0x0020);  // 32-bit register.
      constexpr std::uint32_t gpioa_afrh      = gpioa_base      + UINT32_C(0x0024);  // 32-bit register.

      constexpr std::uint32_t gpiob_moder     = gpiob_base      + UINT32_C(0x0000);  // 32-bit register.
      constexpr std::uint32_t gpiob_otyper    = gpiob_base      + UINT32_C(0x0004);  // 32-bit register.
      constexpr std::uint32_t gpiob_ospeedr   = gpiob_base      + UINT32_C(0x0008);  // 32-bit register.
      constexpr std::uint32_t gpiob_pupdr     = gpiob_base      + UINT32_C(0x000C);  // 32-bit register.
      constexpr std::uint32_t gpiob_idr       = gpiob_base      + UINT32_C(0x0010);  // 32-bit register.
      constexpr std::uint32_t gpiob_odr       = gpiob_base      + UINT32_C(0x0014);  // 32-bit register.
      constexpr std::uint32_t gpiob_bsrr      = gpiob_base      + UINT32_C(0x0018);  // 32-bit register.
      constexpr std::uint32_t gpiob_lckr      = gpiob_base      + UINT32_C(0x001C);  // 32-bit register.
      constexpr std::uint32_t gpiob_afrl      = gpiob_base      + UINT32_C(0x0020);  // 32-bit register.
      constexpr std::uint32_t gpiob_afrh      = gpiob_base      + UINT32_C(0x0024);  // 32-bit register.

      constexpr std::uint32_t gpioc_moder     = gpioc_base      + UINT32_C(0x0000);  // 32-bit register.
      constexpr std::uint32_t gpioc_otyper    = gpioc_base      + UINT32_C(0x0004);  // 32-bit register.
      constexpr std::uint32_t gpioc_ospeedr   = gpioc_base      + UINT32_C(0x0008);  // 32-bit register.
      constexpr std::uint32_t gpioc_pupdr     = gpioc_base      + UINT32_C(0x000C);  // 32-bit register.
      constexpr std::uint32_t gpioc_idr       = gpioc_base      + UINT32_C(0x0010);  // 32-bit register.
      constexpr std::uint32_t gpioc_odr       = gpioc_base      + UINT32_C(0x0014);  // 32-bit register.
      constexpr std::uint32_t gpioc_bsrr      = gpioc_base      + UINT32_C(0x0018);  // 32-bit register.
      constexpr std::uint32_t gpioc_lckr      = gpioc_base      + UINT32_C(0x001C);  // 32-bit register.
      constexpr std::uint32_t gpioc_afrl      = gpioc_base      + UINT32_C(0x0020);  // 32-bit register.
      constexpr std::uint32_t gpioc_afrh      = gpioc_base      + UINT32_C(0x0024);  // 32-bit register.

      constexpr std::uint32_t gpiod_moder     = gpiod_base      + UINT32_C(0x0000);  // 32-bit register.
      constexpr std::uint32_t gpiod_otyper    = gpiod_base      + UINT32_C(0x0004);  // 32-bit register.
      constexpr std::uint32_t gpiod_ospeedr   = gpiod_base      + UINT32_C(0x0008);  // 32-bit register.
      constexpr std::uint32_t gpiod_pupdr     = gpiod_base      + UINT32_C(0x000C);  // 32-bit register.
      constexpr std::uint32_t gpiod_idr       = gpiod_base      + UINT32_C(0x0010);  // 32-bit register.
      constexpr std::uint32_t gpiod_odr       = gpiod_base      + UINT32_C(0x0014);  // 32-bit register.
      constexpr std::uint32_t gpiod_bsrr      = gpiod_base      + UINT32_C(0x0018);  // 32-bit register.
      constexpr std::uint32_t gpiod_lckr      = gpiod_base      + UINT32_C(0x001C);  // 32-bit register.
      constexpr std::uint32_t gpiod_afrl      = gpiod_base      + UINT32_C(0x0020);  // 32-bit register.
      constexpr std::uint32_t gpiod_afrh      = gpiod_base      + UINT32_C(0x0024);  // 32-bit register.

      constexpr std::uint32_t gpioe_moder     = gpioe_base      + UINT32_C(0x0000);  // 32-bit register.
      constexpr std::uint32_t gpioe_otyper    = gpioe_base      + UINT32_C(0x0004);  // 32-bit register.
      constexpr std::uint32_t gpioe_ospeedr   = gpioe_base      + UINT32_C(0x0008);  // 32-bit register.
      constexpr std::uint32_t gpioe_pupdr     = gpioe_base      + UINT32_C(0x000C);  // 32-bit register.
      constexpr std::uint32_t gpioe_idr       = gpioe_base      + UINT32_C(0x0010);  // 32-bit register.
      constexpr std::uint32_t gpioe_odr       = gpioe_base      + UINT32_C(0x0014);  // 32-bit register.
      constexpr std::uint32_t gpioe_bsrr      = gpioe_base      + UINT32_C(0x0018);  // 32-bit register.
      constexpr std::uint32_t gpioe_lckr      = gpioe_base      + UINT32_C(0x001C);  // 32-bit register.
      constexpr std::uint32_t gpioe_afrl      = gpioe_base      + UINT32_C(0x0020);  // 32-bit register.
      constexpr std::uint32_t gpioe_afrh      = gpioe_base      + UINT32_C(0x0024);  // 32-bit register.

      constexpr std::uint32_t gpiof_moder     = gpiof_base      + UINT32_C(0x0000);  // 32-bit register.
      constexpr std::uint32_t gpiof_otyper    = gpiof_base      + UINT32_C(0x0004);  // 32-bit register.
      constexpr std::uint32_t gpiof_ospeedr   = gpiof_base      + UINT32_C(0x0008);  // 32-bit register.
      constexpr std::uint32_t gpiof_pupdr     = gpiof_base      + UINT32_C(0x000C);  // 32-bit register.
      constexpr std::uint32_t gpiof_idr       = gpiof_base      + UINT32_C(0x0010);  // 32-bit register.
      constexpr std::uint32_t gpiof_odr       = gpiof_base      + UINT32_C(0x0014);  // 32-bit register.
      constexpr std::uint32_t gpiof_bsrr      = gpiof_base      + UINT32_C(0x0018);  // 32-bit register.
      constexpr std::uint32_t gpiof_lckr      = gpiof_base      + UINT32_C(0x001C);  // 32-bit register.
      constexpr std::uint32_t gpiof_afrl      = gpiof_base      + UINT32_C(0x0020);  // 32-bit register.
      constexpr std::uint32_t gpiof_afrh      = gpiof_base      + UINT32_C(0x0024);  // 32-bit register.

      constexpr std::uint32_t gpiog_moder     = gpiog_base      + UINT32_C(0x0000);  // 32-bit register.
      constexpr std::uint32_t gpiog_otyper    = gpiog_base      + UINT32_C(0x0004);  // 32-bit register.
      constexpr std::uint32_t gpiog_ospeedr   = gpiog_base      + UINT32_C(0x0008);  // 32-bit register.
      constexpr std::uint32_t gpiog_pupdr     = gpiog_base      + UINT32_C(0x000C);  // 32-bit register.
      constexpr std::uint32_t gpiog_idr       = gpiog_base      + UINT32_C(0x0010);  // 32-bit register.
      constexpr std::uint32_t gpiog_odr       = gpiog_base      + UINT32_C(0x0014);  // 32-bit register.
      constexpr std::uint32_t gpiog_bsrr      = gpiog_base      + UINT32_C(0x0018);  // 32-bit register.
      constexpr std::uint32_t gpiog_lckr      = gpiog_base      + UINT32_C(0x001C);  // 32-bit register.
      constexpr std::uint32_t gpiog_afrl      = gpiog_base      + UINT32_C(0x0020);  // 32-bit register.
      constexpr std::uint32_t gpiog_afrh      = gpiog_base      + UINT32_C(0x0024);  // 32-bit register.

      // Timer registers.
      constexpr std::uint32_t tim4_cr1        = tim4_base       + UINT32_C(0x0000);  // 16-bit register.
      constexpr std::uint32_t tim4_cr2        = tim4_base       + UINT32_C(0x0004);  // 16-bit register.
      constexpr std::uint32_t tim4_smcr       = tim4_base       + UINT32_C(0x0008);  // 16-bit register.
      constexpr std::uint32_t tim4_dier       = tim4_base       + UINT32_C(0x000C);  // 16-bit register.
      constexpr std::uint32_t tim4_sr         = tim4_base       + UINT32_C(0x0010);  // 16-bit register.
      constexpr std::uint32_t tim4_egr        = tim4_base       + UINT32_C(0x0014);  // 16-bit register.
      constexpr std::uint32_t tim4_ccmr1      = tim4_base       + UINT32_C(0x0018);  // 16-bit register.
      constexpr std::uint32_t tim4_ccmr2      = tim4_base       + UINT32_C(0x001C);  // 16-bit register.
      constexpr std::uint32_t tim4_ccer       = tim4_base       + UINT32_C(0x0020);  // 16-bit register.
      constexpr std::uint32_t tim4_cnt        = tim4_base       + UINT32_C(0x0024);  // 16-bit register.
      constexpr std::uint32_t tim4_psc        = tim4_base       + UINT32_C(0x0028);  // 16-bit register.
      constexpr std::uint32_t tim4_arr        = tim4_base       + UINT32_C(0x002C);  // 16-bit register.
      constexpr std::uint32_t tim4_rcr        = tim4_base       + UINT32_C(0x0030);  // 16-bit register.

      // Power management registers.
      constexpr std::uint32_t rcc_ahb1enr     = rcc_base        + UINT32_C(0x0030);  // 32-bit register.
      constexpr std::uint32_t rcc_ahb2enr     = rcc_base        + UINT32_C(0x0034);  // 32-bit register.
      constexpr std::uint32_t rcc_apb1enr     = rcc_base        + UINT32_C(0x0040);  // 32-bit register.
      constexpr std::uint32_t rcc_apb2enr     = rcc_base        + UINT32_C(0x0044);  // 32-bit register.

      // Watchdog registers.
      constexpr std::uint32_t iwdg_kr         = iwdg_base       + UINT32_C(0x0000);  // 32-bit register.
      constexpr std::uint32_t iwdg_pr         = iwdg_base       + UINT32_C(0x0004);  // 32-bit register.
      constexpr std::uint32_t iwdg_rlr        = iwdg_base       + UINT32_C(0x0008);  // 32-bit register.
      constexpr std::uint32_t iwdg_sr         = iwdg_base       + UINT32_C(0x000C);  // 32-bit register.

      // Interrupt control registers.
      constexpr std::uint32_t nvic_iser       = nvic_base       + UINT32_C(0x0000);  // 32-bit registers : Interrupt set enable registers.
      constexpr std::uint32_t nvic_icer       = nvic_base       + UINT32_C(0x0080);  // 32-bit registers : Interrupt clear enable registers.
      constexpr std::uint32_t nvic_ispr       = nvic_base       + UINT32_C(0x0100);  // 32-bit registers : Interrupt set pending registers.
      constexpr std::uint32_t nvic_icpr       = nvic_base       + UINT32_C(0x0180);  // 32-bit registers : Interrupt clear pending registers.
      constexpr std::uint32_t nvic_iabr       = nvic_base       + UINT32_C(0x0200);  // 32-bit registers : Interrupt active bit registers.
      constexpr std::uint32_t nvic_ip         = nvic_base       + UINT32_C(0x0300);  //  8-bit registers : Interrupt priority registers (each one 8 bits wide).
    }
  }

  #include <mcal/mcal_reg_access_dynamic.h>
  #include <mcal/mcal_reg_access_static.h>

#endif // MCAL_REG_2010_04_10_H_
