///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2023.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_REG_2022_08_03_H
  #define MCAL_REG_2022_08_03_H

  #include <cstdint>

  namespace mcal
  {
    namespace reg
    {
      // Global base addresses.
      constexpr std::uint32_t scs_base             = UINT32_C(0xE000E000);

      // Individual unit base addresses.
      constexpr std::uint32_t scb_base             = scs_base            + UINT32_C(0x00000D00);

      // Chip-specific registers.
      constexpr auto ccm_analog_pll_arm     = static_cast<std::uint32_t>(UINT32_C(0x400D8000)); // BootROM forced to 0x80002042
      constexpr auto ccm_analog_pll_arm_set = static_cast<std::uint32_t>(UINT32_C(0x400D8004));
      constexpr auto ccm_analog_pll_arm_clr = static_cast<std::uint32_t>(UINT32_C(0x400D8008));
      constexpr auto ccm_analog_pll_arm_tog = static_cast<std::uint32_t>(UINT32_C(0x400D800C));

      constexpr auto ccm_cbcdr              = static_cast<std::uint32_t>(UINT32_C(0x400FC014)); // BootROM forced to 0x000A8200
      constexpr auto ccm_cacrr              = static_cast<std::uint32_t>(UINT32_C(0x400FC010)); // BootROM forced to 0x00000001
      constexpr auto ccm_cbcmr              = static_cast<std::uint32_t>(UINT32_C(0x400FC018)); // BootROM forced to 0x75AE8104

      constexpr auto dcdc_reg0              = static_cast<std::uint32_t>(UINT32_C(0x40080000));
      constexpr auto dcdc_reg3              = static_cast<std::uint32_t>(UINT32_C(0x4008000C));

      constexpr auto gpio_01_base_address   = static_cast<std::uint32_t>(UINT32_C(0x401B8000));
      constexpr auto gpio_02_base_address   = static_cast<std::uint32_t>(UINT32_C(0x401BC000));
      constexpr auto gpio_03_base_address   = static_cast<std::uint32_t>(UINT32_C(0x401C0000));
      constexpr auto gpio_04_base_address   = static_cast<std::uint32_t>(UINT32_C(0x401C4000));
      constexpr auto gpio_05_base_address   = static_cast<std::uint32_t>(UINT32_C(0x400C0000));
      constexpr auto gpio_06_base_address   = static_cast<std::uint32_t>(UINT32_C(0x42000000));
      constexpr auto gpio_07_base_address   = static_cast<std::uint32_t>(UINT32_C(0x42004000));
      constexpr auto gpio_08_base_address   = static_cast<std::uint32_t>(UINT32_C(0x42008000));
      constexpr auto gpio_09_base_address   = static_cast<std::uint32_t>(UINT32_C(0x4200C000));
      constexpr auto gpio_10_base_address   = static_cast<std::uint32_t>(UINT32_C(0x401C8000));

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
    }
  }

  #include <mcal/mcal_reg_access_dynamic.h>
  #include <mcal/mcal_reg_access_static.h>

#endif // MCAL_REG_2022_08_03_H
