///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2022.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_REG_2022_08_03_H_
  #define MCAL_REG_2022_08_03_H_

  #include <cstdint>

  namespace mcal
  {
    namespace reg
    {
      // Global base addresses.
      constexpr std::uint32_t periph_base          = UINT32_C(0x40000000);
      constexpr std::uint32_t scs_base             = UINT32_C(0xE000E000);

      // Individual unit base addresses.
      constexpr std::uint32_t scb_base             = scs_base            + UINT32_C(0x00000D00);
      constexpr std::uint32_t nvic_base            = scs_base            + UINT32_C(0x00000100);
      constexpr std::uint32_t sys_tick_base        = scs_base            + UINT32_C(0x00000010);
      constexpr std::uint32_t apb1periph_base      = periph_base         + UINT32_C(0x00000000);

      constexpr std::uint32_t ahb1periph_base      = periph_base         + UINT32_C(0x00020000);
      constexpr std::uint32_t cd_ahb3periph_base   = periph_base         + UINT32_C(0x12000000);
      constexpr std::uint32_t srd_ahb4periph_base  = periph_base         + UINT32_C(0x18020000);
      constexpr std::uint32_t rcc_base             = srd_ahb4periph_base + UINT32_C(0x00004400);
      constexpr std::uint32_t pwr_base             = srd_ahb4periph_base + UINT32_C(0x00004800);
      constexpr std::uint32_t fmc_r_base           = cd_ahb3periph_base  + UINT32_C(0x00004000);

      constexpr std::uint32_t flash_r_base         = cd_ahb3periph_base  + UINT32_C(0x2000);
      constexpr std::uint32_t fmc_bank1_r_base     = fmc_r_base          + UINT32_C(0x0000);

      constexpr std::uint32_t sys_tick_ctrl        = sys_tick_base   + UINT32_C(0x0000);
      constexpr std::uint32_t sys_tick_load        = sys_tick_base   + UINT32_C(0x0004);
      constexpr std::uint32_t sys_tick_val         = sys_tick_base   + UINT32_C(0x0008);
      constexpr std::uint32_t sys_tick_cal         = sys_tick_base   + UINT32_C(0x000C);

      constexpr std::uint32_t gpioa_base           = srd_ahb4periph_base + UINT32_C(0x0000);
      constexpr std::uint32_t gpiob_base           = srd_ahb4periph_base + UINT32_C(0x0400);
      constexpr std::uint32_t gpioc_base           = srd_ahb4periph_base + UINT32_C(0x0800);
      constexpr std::uint32_t gpiod_base           = srd_ahb4periph_base + UINT32_C(0x0C00);
      constexpr std::uint32_t gpioe_base           = srd_ahb4periph_base + UINT32_C(0x1000);
      constexpr std::uint32_t gpiof_base           = srd_ahb4periph_base + UINT32_C(0x1400);
      constexpr std::uint32_t gpiog_base           = srd_ahb4periph_base + UINT32_C(0x1800);
      constexpr std::uint32_t gpioh_base           = srd_ahb4periph_base + UINT32_C(0x1C00);
      constexpr std::uint32_t gpioi_base           = srd_ahb4periph_base + UINT32_C(0x2000);
      constexpr std::uint32_t gpioj_base           = srd_ahb4periph_base + UINT32_C(0x2400);
      constexpr std::uint32_t gpiok_base           = srd_ahb4periph_base + UINT32_C(0x2800);

      constexpr std::uint32_t tim4_base            = periph_base     + UINT32_C(0x0800);

      constexpr std::uint32_t iwdg_base            = periph_base     + UINT32_C(0x3000);

      // SCB registers.
      constexpr std::uint32_t scb_cpuid            = scb_base        + UINT32_C(0x0000); // (R/ )  CPUID Base Register */
      constexpr std::uint32_t scb_icsr             = scb_base        + UINT32_C(0x0004); // (R/W)  Interrupt Control and State Register */
      constexpr std::uint32_t scb_vtor             = scb_base        + UINT32_C(0x0008); // (R/W)  Vector Table Offset Register */
      constexpr std::uint32_t scb_aircr            = scb_base        + UINT32_C(0x000C); // (R/W)  Application Interrupt and Reset Control Register */
      constexpr std::uint32_t scb_scr              = scb_base        + UINT32_C(0x0010); // (R/W)  System Control Register */
      constexpr std::uint32_t scb_ccr              = scb_base        + UINT32_C(0x0014); // (R/W)  Configuration Control Register */
      constexpr std::uint32_t scb_shpr0            = scb_base        + UINT32_C(0x0018); // (R/W)  System Handlers Priority Registers (8-bit) */
      constexpr std::uint32_t scb_shpr1            = scb_base        + UINT32_C(0x0019); // (R/W)  System Handlers Priority Registers (8-bit) */
      constexpr std::uint32_t scb_shpr2            = scb_base        + UINT32_C(0x001A); // (R/W)  System Handlers Priority Registers (8-bit) */
      constexpr std::uint32_t scb_shpr3            = scb_base        + UINT32_C(0x001B); // (R/W)  System Handlers Priority Registers (8-bit) */
      constexpr std::uint32_t scb_shpr4            = scb_base        + UINT32_C(0x001C); // (R/W)  System Handlers Priority Registers (8-bit) */
      constexpr std::uint32_t scb_shpr5            = scb_base        + UINT32_C(0x001D); // (R/W)  System Handlers Priority Registers (8-bit) */
      constexpr std::uint32_t scb_shpr6            = scb_base        + UINT32_C(0x001E); // (R/W)  System Handlers Priority Registers (8-bit) */
      constexpr std::uint32_t scb_shpr7            = scb_base        + UINT32_C(0x001F); // (R/W)  System Handlers Priority Registers (8-bit) */
      constexpr std::uint32_t scb_shpr8            = scb_base        + UINT32_C(0x0020); // (R/W)  System Handlers Priority Registers (8-bit) */
      constexpr std::uint32_t scb_shpr9            = scb_base        + UINT32_C(0x0021); // (R/W)  System Handlers Priority Registers (8-bit) */
      constexpr std::uint32_t scb_shpr10           = scb_base        + UINT32_C(0x0021); // (R/W)  System Handlers Priority Registers (8-bit) */
      constexpr std::uint32_t scb_shpr11           = scb_base        + UINT32_C(0x0023); // (R/W)  System Handlers Priority Registers (8-bit) */
      constexpr std::uint32_t scb_shcsr            = scb_base        + UINT32_C(0x0024); // (R/W)  System Handler Control and State Register */
      constexpr std::uint32_t scb_cfsr             = scb_base        + UINT32_C(0x0028); // (R/W)  Configurable Fault Status Register */
      constexpr std::uint32_t scb_hfsr             = scb_base        + UINT32_C(0x002C); // (R/W)  HardFault Status Register */
      constexpr std::uint32_t scb_dfsr             = scb_base        + UINT32_C(0x0030); // (R/W)  Debug Fault Status Register */
      constexpr std::uint32_t scb_mmfar            = scb_base        + UINT32_C(0x0034); // (R/W)  MemManage Fault Address Register */
      constexpr std::uint32_t scb_bfar             = scb_base        + UINT32_C(0x0038); // (R/W)  BusFault Address Register */
      constexpr std::uint32_t scb_afsr             = scb_base        + UINT32_C(0x003C); // (R/W)  Auxiliary Fault Status Register */
      constexpr std::uint32_t scb_id_pfr0          = scb_base        + UINT32_C(0x0040); // (R/ )  Processor Feature Register */
      constexpr std::uint32_t scb_id_pfr1          = scb_base        + UINT32_C(0x0044); // (R/ )  Processor Feature Register */
      constexpr std::uint32_t scb_id_dfr           = scb_base        + UINT32_C(0x0048); // (R/ )  Debug Feature Register */
      constexpr std::uint32_t scb_id_afr           = scb_base        + UINT32_C(0x004C); // (R/ )  Auxiliary Feature Register */
      constexpr std::uint32_t scb_id_mfr0          = scb_base        + UINT32_C(0x0050); // (R/ )  Memory Model Feature Register */
      constexpr std::uint32_t scb_id_mfr1          = scb_base        + UINT32_C(0x0054); // (R/ )  Memory Model Feature Register */
      constexpr std::uint32_t scb_id_mfr2          = scb_base        + UINT32_C(0x0058); // (R/ )  Memory Model Feature Register */
      constexpr std::uint32_t scb_id_mfr3          = scb_base        + UINT32_C(0x005C); // (R/ )  Memory Model Feature Register */
      constexpr std::uint32_t scb_id_isar0         = scb_base        + UINT32_C(0x0060); // (R/ )  Instruction Set Attributes Register */
      constexpr std::uint32_t scb_id_isar1         = scb_base        + UINT32_C(0x0064); // (R/ )  Instruction Set Attributes Register */
      constexpr std::uint32_t scb_id_isar2         = scb_base        + UINT32_C(0x0068); // (R/ )  Instruction Set Attributes Register */
      constexpr std::uint32_t scb_id_isar3         = scb_base        + UINT32_C(0x006C); // (R/ )  Instruction Set Attributes Register */
      constexpr std::uint32_t scb_id_isar4         = scb_base        + UINT32_C(0x0070); // (R/ )  Instruction Set Attributes Register */
      constexpr std::uint32_t scb_clidr            = scb_base        + UINT32_C(0x0078); // (R/ )  Cache Level ID register */
      constexpr std::uint32_t scb_ctr              = scb_base        + UINT32_C(0x007C); // (R/ )  Cache Type register */
      constexpr std::uint32_t scb_ccsidr           = scb_base        + UINT32_C(0x0080); // (R/ )  Cache Size ID Register */
      constexpr std::uint32_t scb_csselr           = scb_base        + UINT32_C(0x0084); // (R/W)  Cache Size Selection Register */
      static_assert(scb_csselr == UINT32_C(0xE000ED84), "Error: Verification of scb_csselr failed");
      constexpr std::uint32_t scb_cpacr            = scb_base        + UINT32_C(0x0088); // (R/W)  Coprocessor Access Control Register */
      static_assert(scb_cpacr == UINT32_C(0xE000ED88), "Error: Verification of scb_cpacr failed");
      constexpr std::uint32_t scb_stir             = scb_base        + UINT32_C(0x0200); // ( /W)  Software Triggered Interrupt Register */
      constexpr std::uint32_t scb_mvfr0            = scb_base        + UINT32_C(0x0240); // (R/ )  Media and VFP Feature Register 0 */
      constexpr std::uint32_t scb_mvfr1            = scb_base        + UINT32_C(0x0244); // (R/ )  Media and VFP Feature Register 1 */
      constexpr std::uint32_t scb_mvfr2            = scb_base        + UINT32_C(0x0248); // (R/ )  Media and VFP Feature Register 2 */
      constexpr std::uint32_t scb_iciallu          = scb_base        + UINT32_C(0x0250); // ( /W)  I-Cache Invalidate All to PoU */
      constexpr std::uint32_t scb_icimvau          = scb_base        + UINT32_C(0x0258); // ( /W)  I-Cache Invalidate by MVA to PoU */
      constexpr std::uint32_t scb_dcimvac          = scb_base        + UINT32_C(0x025C); // ( /W)  D-Cache Invalidate by MVA to PoC */
      constexpr std::uint32_t scb_dcisw            = scb_base        + UINT32_C(0x0260); // ( /W)  D-Cache Invalidate by Set-way */
      constexpr std::uint32_t scb_dccmvau          = scb_base        + UINT32_C(0x0264); // ( /W)  D-Cache Clean by MVA to PoU */
      constexpr std::uint32_t scb_dccmvac          = scb_base        + UINT32_C(0x0268); // ( /W)  D-Cache Clean by MVA to PoC */
      constexpr std::uint32_t scb_dccsw            = scb_base        + UINT32_C(0x026C); // ( /W)  D-Cache Clean by Set-way */
      constexpr std::uint32_t scb_dccimvac         = scb_base        + UINT32_C(0x0270); // ( /W)  D-Cache Clean and Invalidate by MVA to PoC */
      constexpr std::uint32_t scb_dccisw           = scb_base        + UINT32_C(0x0274); // ( /W)  D-Cache Clean and Invalidate by Set-way */
      constexpr std::uint32_t scb_itcmcr           = scb_base        + UINT32_C(0x0290); // (R/W)  Instruction Tightly-Coupled Memory Control Register */
      static_assert(scb_itcmcr == UINT32_C(0xE000EF90), "Error: Verification of scb_itcmcr failed");
      constexpr std::uint32_t scb_dtcmcr           = scb_base        + UINT32_C(0x0294); // (R/W)  Data Tightly-Coupled Memory Control Registers */
      constexpr std::uint32_t scb_ahbpcr           = scb_base        + UINT32_C(0x0298); // (R/W)  AHBP Control Register */
      constexpr std::uint32_t scb_cacr             = scb_base        + UINT32_C(0x029C); // (R/W)  L1 Cache Control Register */
      constexpr std::uint32_t scb_ahbscr           = scb_base        + UINT32_C(0x02A0); // (R/W)  AHB Slave Control Register */
      constexpr std::uint32_t scb_abfsr            = scb_base        + UINT32_C(0x02A8); // (R/W)  Auxiliary Bus Fault Status Register */

      // RCC registers.
      constexpr std::uint32_t rcc_cr               = rcc_base        + UINT32_C(0x0000); // RCC clock control register
      static_assert(rcc_cr == UINT32_C(0x58024400), "Error: Verification of rcc_cr failed");
      constexpr std::uint32_t rcc_hsicfgr          = rcc_base        + UINT32_C(0x0004); // HSI Clock Calibration Register
      constexpr std::uint32_t rcc_crrcr            = rcc_base        + UINT32_C(0x0008); // Clock Recovery RC  Register
      constexpr std::uint32_t rcc_csicfgr          = rcc_base        + UINT32_C(0x000C); // CSI Clock Calibration Register
      constexpr std::uint32_t rcc_cfgr             = rcc_base        + UINT32_C(0x0010); // RCC clock configuration register
      static_assert(rcc_cfgr == UINT32_C(0x58024410), "Error: Verification of rcc_cfgr failed");
      constexpr std::uint32_t rcc_cdcfgr1          = rcc_base        + UINT32_C(0x0018); // RCC Domain 1 configuration register
      constexpr std::uint32_t rcc_cdcfgr2          = rcc_base        + UINT32_C(0x001C); // RCC Domain 2 configuration register
      constexpr std::uint32_t rcc_srdcfgr          = rcc_base        + UINT32_C(0x0020); // RCC Domain 3 configuration register
      constexpr std::uint32_t rcc_pllckselr        = rcc_base        + UINT32_C(0x0028); // RCC PLLs Clock Source Selection Register
      static_assert(rcc_pllckselr == UINT32_C(0x58024428), "Error: Verification of rcc_pllckselr failed");
      constexpr std::uint32_t rcc_pllcfgr          = rcc_base        + UINT32_C(0x002C); // RCC PLLs  Configuration Register
      constexpr std::uint32_t rcc_pll1divr         = rcc_base        + UINT32_C(0x0030); // RCC PLL1 Dividers Configuration Register
      static_assert(rcc_pll1divr == UINT32_C(0x58024430), "Error: Verification of rcc_pll1divr failed");
      constexpr std::uint32_t rcc_pll1fracr        = rcc_base        + UINT32_C(0x0034); // RCC PLL1 Fractional Divider Configuration Register
      constexpr std::uint32_t rcc_pll2divr         = rcc_base        + UINT32_C(0x0038); // RCC PLL2 Dividers Configuration Register
      constexpr std::uint32_t rcc_pll2fracr        = rcc_base        + UINT32_C(0x003C); // RCC PLL2 Fractional Divider Configuration Register
      constexpr std::uint32_t rcc_pll3divr         = rcc_base        + UINT32_C(0x0040); // RCC PLL3 Dividers Configuration Register
      constexpr std::uint32_t rcc_pll3fracr        = rcc_base        + UINT32_C(0x0044); // RCC PLL3 Fractional Divider Configuration Register
      constexpr std::uint32_t rcc_cdccipr          = rcc_base        + UINT32_C(0x004C); // RCC Domain 1 Kernel Clock Configuration Register
      constexpr std::uint32_t rcc_cdccip1r         = rcc_base        + UINT32_C(0x0050); // RCC Domain 2 Kernel Clock Configuration Register
      constexpr std::uint32_t rcc_cdccip2r         = rcc_base        + UINT32_C(0x0054); // RCC Domain 2 Kernel Clock Configuration Register
      constexpr std::uint32_t rcc_srdccipr         = rcc_base        + UINT32_C(0x0058); // RCC Domain 3 Kernel Clock Configuration Register
      constexpr std::uint32_t rcc_cier             = rcc_base        + UINT32_C(0x0060); // RCC Clock Source Interrupt Enable Register
      constexpr std::uint32_t rcc_cifr             = rcc_base        + UINT32_C(0x0064); // RCC Clock Source Interrupt Flag Register
      constexpr std::uint32_t rcc_cicr             = rcc_base        + UINT32_C(0x0068); // RCC Clock Source Interrupt Clear Register
      constexpr std::uint32_t rcc_bdcr             = rcc_base        + UINT32_C(0x0070); // RCC Vswitch Backup Domain Control Register
      constexpr std::uint32_t rcc_csr              = rcc_base        + UINT32_C(0x0074); // RCC clock control & status register
      constexpr std::uint32_t rcc_ahb3rstr         = rcc_base        + UINT32_C(0x007C); // RCC AHB3 peripheral reset register
      constexpr std::uint32_t rcc_ahb1rstr         = rcc_base        + UINT32_C(0x0080); // RCC AHB1 peripheral reset register
      constexpr std::uint32_t rcc_ahb2rstr         = rcc_base        + UINT32_C(0x0084); // RCC AHB2 peripheral reset register
      constexpr std::uint32_t rcc_ahb4rstr         = rcc_base        + UINT32_C(0x0088); // RCC AHB4 peripheral reset register
      constexpr std::uint32_t rcc_apb3rstr         = rcc_base        + UINT32_C(0x008C); // RCC APB3 peripheral reset register
      constexpr std::uint32_t rcc_apb1lrstr        = rcc_base        + UINT32_C(0x0090); // RCC APB1 peripheral reset Low Word register
      constexpr std::uint32_t rcc_apb1hrstr        = rcc_base        + UINT32_C(0x0094); // RCC APB1 peripheral reset High Word register
      constexpr std::uint32_t rcc_apb2rstr         = rcc_base        + UINT32_C(0x0098); // RCC APB2 peripheral reset register
      constexpr std::uint32_t rcc_apb4rstr         = rcc_base        + UINT32_C(0x009C); // RCC APB4 peripheral reset register
      constexpr std::uint32_t rcc_srdamr           = rcc_base        + UINT32_C(0x00A8); // RCC Domain 3 Autonomous Mode Register 
      constexpr std::uint32_t rcc_ckgaenr          = rcc_base        + UINT32_C(0x00B0); // AXI Clocks Gating Enable Register 
      constexpr std::uint32_t rcc_rsr              = rcc_base        + UINT32_C(0x00D0); // RCC Reset status register 
      constexpr std::uint32_t rcc_ahb3enr          = rcc_base        + UINT32_C(0x00D4); // RCC AHB3 peripheral clock register
      constexpr std::uint32_t rcc_ahb1enr          = rcc_base        + UINT32_C(0x00D8); // RCC AHB1 peripheral clock register
      constexpr std::uint32_t rcc_ahb2enr          = rcc_base        + UINT32_C(0x00DC); // RCC AHB2 peripheral clock register
      constexpr std::uint32_t rcc_ahb4enr          = rcc_base        + UINT32_C(0x00E0); // RCC AHB4 peripheral clock register
      constexpr std::uint32_t rcc_apb3enr          = rcc_base        + UINT32_C(0x00E4); // RCC APB3 peripheral clock register
      constexpr std::uint32_t rcc_apb1lenr         = rcc_base        + UINT32_C(0x00E8); // RCC APB1 peripheral clock Low Word register
      constexpr std::uint32_t rcc_apb1henr         = rcc_base        + UINT32_C(0x00EC); // RCC APB1 peripheral clock High Word register
      constexpr std::uint32_t rcc_apb2enr          = rcc_base        + UINT32_C(0x00F0); // RCC APB2 peripheral clock register
      constexpr std::uint32_t rcc_apb4enr          = rcc_base        + UINT32_C(0x00F4); // RCC APB4 peripheral clock register
      constexpr std::uint32_t rcc_ahb3lpenr        = rcc_base        + UINT32_C(0x00FC); // RCC AHB3 peripheral sleep clock register
      constexpr std::uint32_t rcc_ahb1lpenr        = rcc_base        + UINT32_C(0x0100); // RCC AHB1 peripheral sleep clock register
      constexpr std::uint32_t rcc_ahb2lpenr        = rcc_base        + UINT32_C(0x0104); // RCC AHB2 peripheral sleep clock register
      constexpr std::uint32_t rcc_ahb4lpenr        = rcc_base        + UINT32_C(0x0108); // RCC AHB4 peripheral sleep clock register
      constexpr std::uint32_t rcc_apb3lpenr        = rcc_base        + UINT32_C(0x010C); // RCC APB3 peripheral sleep clock register
      constexpr std::uint32_t rcc_apb1llpenr       = rcc_base        + UINT32_C(0x0110); // RCC APB1 peripheral sleep clock Low Word register
      constexpr std::uint32_t rcc_apb1hlpenr       = rcc_base        + UINT32_C(0x0114); // RCC APB1 peripheral sleep clock High Word register
      constexpr std::uint32_t rcc_apb2lpenr        = rcc_base        + UINT32_C(0x0118); // RCC APB2 peripheral sleep clock register
      constexpr std::uint32_t rcc_apb4lpenr        = rcc_base        + UINT32_C(0x011C); // RCC APB4 peripheral sleep clock register

      // Flash memory registers.
      constexpr std::uint32_t flash_acr            = flash_r_base    + UINT32_C(0x0000);  // 32-bit register.
      static_assert(flash_acr == UINT32_C(0x52002000), "Error: Verification of flash_acr failed");
      constexpr std::uint32_t flash_keyr           = flash_r_base    + UINT32_C(0x0004);  // 32-bit register.
      constexpr std::uint32_t flash_optkeyr        = flash_r_base    + UINT32_C(0x0008);  // 32-bit register.
      constexpr std::uint32_t flash_sr             = flash_r_base    + UINT32_C(0x000C);  // 32-bit register.
      constexpr std::uint32_t flash_cr             = flash_r_base    + UINT32_C(0x0010);  // 32-bit register.
      constexpr std::uint32_t flash_optcr          = flash_r_base    + UINT32_C(0x0014);  // 32-bit register.
      constexpr std::uint32_t flash_optcr1         = flash_r_base    + UINT32_C(0x0018);  // 32-bit register.

      // Power control registers.
      constexpr std::uint32_t pwr_cr1              = pwr_base       + UINT32_C(0x0000);  // PWR power control register 1
      constexpr std::uint32_t pwr_csr1             = pwr_base       + UINT32_C(0x0004);  // PWR power control status register 1
      constexpr std::uint32_t pwr_cr2              = pwr_base       + UINT32_C(0x0008);  // PWR power control register 2
      constexpr std::uint32_t pwr_cr3              = pwr_base       + UINT32_C(0x000C);  // PWR power control register 3
      constexpr std::uint32_t pwr_cpucr            = pwr_base       + UINT32_C(0x0010);  // PWR CPU control register
      constexpr std::uint32_t pwr_srdcr            = pwr_base       + UINT32_C(0x0018);  // PWR SRD domain control register
      constexpr std::uint32_t pwr_wkupcr           = pwr_base       + UINT32_C(0x0020);  // PWR wakeup clear register
      constexpr std::uint32_t pwr_wkupfr           = pwr_base       + UINT32_C(0x0024);  // PWR wakeup flag register
      constexpr std::uint32_t pwr_wkupepr          = pwr_base       + UINT32_C(0x0028);  // PWR wakeup enable and polarity register

      // Port registers.
      constexpr std::uint32_t gpioa_moder          = gpioa_base      + UINT32_C(0x0000);  // 32-bit register.
      constexpr std::uint32_t gpioa_otyper         = gpioa_base      + UINT32_C(0x0004);  // 32-bit register.
      constexpr std::uint32_t gpioa_ospeedr        = gpioa_base      + UINT32_C(0x0008);  // 32-bit register.
      constexpr std::uint32_t gpioa_pupdr          = gpioa_base      + UINT32_C(0x000C);  // 32-bit register.
      constexpr std::uint32_t gpioa_idr            = gpioa_base      + UINT32_C(0x0010);  // 32-bit register.
      constexpr std::uint32_t gpioa_odr            = gpioa_base      + UINT32_C(0x0014);  // 32-bit register.
      constexpr std::uint32_t gpioa_bsrr           = gpioa_base      + UINT32_C(0x0018);  // 32-bit register.
      constexpr std::uint32_t gpioa_lckr           = gpioa_base      + UINT32_C(0x001C);  // 32-bit register.
      constexpr std::uint32_t gpioa_afrl           = gpioa_base      + UINT32_C(0x0020);  // 32-bit register.
      constexpr std::uint32_t gpioa_afrh           = gpioa_base      + UINT32_C(0x0024);  // 32-bit register.

      constexpr std::uint32_t gpiob_moder          = gpiob_base      + UINT32_C(0x0000);  // 32-bit register.
      constexpr std::uint32_t gpiob_otyper         = gpiob_base      + UINT32_C(0x0004);  // 32-bit register.
      constexpr std::uint32_t gpiob_ospeedr        = gpiob_base      + UINT32_C(0x0008);  // 32-bit register.
      constexpr std::uint32_t gpiob_pupdr          = gpiob_base      + UINT32_C(0x000C);  // 32-bit register.
      constexpr std::uint32_t gpiob_idr            = gpiob_base      + UINT32_C(0x0010);  // 32-bit register.
      constexpr std::uint32_t gpiob_odr            = gpiob_base      + UINT32_C(0x0014);  // 32-bit register.
      constexpr std::uint32_t gpiob_bsrr           = gpiob_base      + UINT32_C(0x0018);  // 32-bit register.
      constexpr std::uint32_t gpiob_lckr           = gpiob_base      + UINT32_C(0x001C);  // 32-bit register.
      constexpr std::uint32_t gpiob_afrl           = gpiob_base      + UINT32_C(0x0020);  // 32-bit register.
      constexpr std::uint32_t gpiob_afrh           = gpiob_base      + UINT32_C(0x0024);  // 32-bit register.

      constexpr std::uint32_t gpioc_moder          = gpioc_base      + UINT32_C(0x0000);  // 32-bit register.
      constexpr std::uint32_t gpioc_otyper         = gpioc_base      + UINT32_C(0x0004);  // 32-bit register.
      constexpr std::uint32_t gpioc_ospeedr        = gpioc_base      + UINT32_C(0x0008);  // 32-bit register.
      constexpr std::uint32_t gpioc_pupdr          = gpioc_base      + UINT32_C(0x000C);  // 32-bit register.
      constexpr std::uint32_t gpioc_idr            = gpioc_base      + UINT32_C(0x0010);  // 32-bit register.
      constexpr std::uint32_t gpioc_odr            = gpioc_base      + UINT32_C(0x0014);  // 32-bit register.
      constexpr std::uint32_t gpioc_bsrr           = gpioc_base      + UINT32_C(0x0018);  // 32-bit register.
      constexpr std::uint32_t gpioc_lckr           = gpioc_base      + UINT32_C(0x001C);  // 32-bit register.
      constexpr std::uint32_t gpioc_afrl           = gpioc_base      + UINT32_C(0x0020);  // 32-bit register.
      constexpr std::uint32_t gpioc_afrh           = gpioc_base      + UINT32_C(0x0024);  // 32-bit register.

      constexpr std::uint32_t gpiod_moder          = gpiod_base      + UINT32_C(0x0000);  // 32-bit register.
      constexpr std::uint32_t gpiod_otyper         = gpiod_base      + UINT32_C(0x0004);  // 32-bit register.
      constexpr std::uint32_t gpiod_ospeedr        = gpiod_base      + UINT32_C(0x0008);  // 32-bit register.
      constexpr std::uint32_t gpiod_pupdr          = gpiod_base      + UINT32_C(0x000C);  // 32-bit register.
      constexpr std::uint32_t gpiod_idr            = gpiod_base      + UINT32_C(0x0010);  // 32-bit register.
      constexpr std::uint32_t gpiod_odr            = gpiod_base      + UINT32_C(0x0014);  // 32-bit register.
      constexpr std::uint32_t gpiod_bsrr           = gpiod_base      + UINT32_C(0x0018);  // 32-bit register.
      constexpr std::uint32_t gpiod_lckr           = gpiod_base      + UINT32_C(0x001C);  // 32-bit register.
      constexpr std::uint32_t gpiod_afrl           = gpiod_base      + UINT32_C(0x0020);  // 32-bit register.
      constexpr std::uint32_t gpiod_afrh           = gpiod_base      + UINT32_C(0x0024);  // 32-bit register.

      constexpr std::uint32_t gpioe_moder          = gpioe_base      + UINT32_C(0x0000);  // 32-bit register.
      constexpr std::uint32_t gpioe_otyper         = gpioe_base      + UINT32_C(0x0004);  // 32-bit register.
      constexpr std::uint32_t gpioe_ospeedr        = gpioe_base      + UINT32_C(0x0008);  // 32-bit register.
      constexpr std::uint32_t gpioe_pupdr          = gpioe_base      + UINT32_C(0x000C);  // 32-bit register.
      constexpr std::uint32_t gpioe_idr            = gpioe_base      + UINT32_C(0x0010);  // 32-bit register.
      constexpr std::uint32_t gpioe_odr            = gpioe_base      + UINT32_C(0x0014);  // 32-bit register.
      constexpr std::uint32_t gpioe_bsrr           = gpioe_base      + UINT32_C(0x0018);  // 32-bit register.
      constexpr std::uint32_t gpioe_lckr           = gpioe_base      + UINT32_C(0x001C);  // 32-bit register.
      constexpr std::uint32_t gpioe_afrl           = gpioe_base      + UINT32_C(0x0020);  // 32-bit register.
      constexpr std::uint32_t gpioe_afrh           = gpioe_base      + UINT32_C(0x0024);  // 32-bit register.

      constexpr std::uint32_t gpiof_moder          = gpiof_base      + UINT32_C(0x0000);  // 32-bit register.
      constexpr std::uint32_t gpiof_otyper         = gpiof_base      + UINT32_C(0x0004);  // 32-bit register.
      constexpr std::uint32_t gpiof_ospeedr        = gpiof_base      + UINT32_C(0x0008);  // 32-bit register.
      constexpr std::uint32_t gpiof_pupdr          = gpiof_base      + UINT32_C(0x000C);  // 32-bit register.
      constexpr std::uint32_t gpiof_idr            = gpiof_base      + UINT32_C(0x0010);  // 32-bit register.
      constexpr std::uint32_t gpiof_odr            = gpiof_base      + UINT32_C(0x0014);  // 32-bit register.
      constexpr std::uint32_t gpiof_bsrr           = gpiof_base      + UINT32_C(0x0018);  // 32-bit register.
      constexpr std::uint32_t gpiof_lckr           = gpiof_base      + UINT32_C(0x001C);  // 32-bit register.
      constexpr std::uint32_t gpiof_afrl           = gpiof_base      + UINT32_C(0x0020);  // 32-bit register.
      constexpr std::uint32_t gpiof_afrh           = gpiof_base      + UINT32_C(0x0024);  // 32-bit register.

      constexpr std::uint32_t gpiog_moder          = gpiog_base      + UINT32_C(0x0000);  // 32-bit register.
      constexpr std::uint32_t gpiog_otyper         = gpiog_base      + UINT32_C(0x0004);  // 32-bit register.
      constexpr std::uint32_t gpiog_ospeedr        = gpiog_base      + UINT32_C(0x0008);  // 32-bit register.
      constexpr std::uint32_t gpiog_pupdr          = gpiog_base      + UINT32_C(0x000C);  // 32-bit register.
      constexpr std::uint32_t gpiog_idr            = gpiog_base      + UINT32_C(0x0010);  // 32-bit register.
      constexpr std::uint32_t gpiog_odr            = gpiog_base      + UINT32_C(0x0014);  // 32-bit register.
      constexpr std::uint32_t gpiog_bsrr           = gpiog_base      + UINT32_C(0x0018);  // 32-bit register.
      constexpr std::uint32_t gpiog_lckr           = gpiog_base      + UINT32_C(0x001C);  // 32-bit register.
      constexpr std::uint32_t gpiog_afrl           = gpiog_base      + UINT32_C(0x0020);  // 32-bit register.
      constexpr std::uint32_t gpiog_afrh           = gpiog_base      + UINT32_C(0x0024);  // 32-bit register.
    }
  }

  #include <mcal/mcal_reg_access_dynamic.h>
  #include <mcal/mcal_reg_access_static.h>

#endif // MCAL_REG_2022_08_03_H_
