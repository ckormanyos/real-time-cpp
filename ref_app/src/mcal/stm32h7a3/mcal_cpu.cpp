///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2022.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "stm32h7xx_hal.h"

#include <mcal_cpu.h>
#include <mcal_osc.h>
#include <mcal_port.h>
#include <mcal_reg.h>
#include <mcal_wdg.h>


namespace local
{
  void system_init();
  void enable_i_cache();
  void enable_d_cache();

  void system_init()
  {
    // FPU settings.
    // set CP10 and CP11 Full Access.
    mcal::reg::reg_access_static<std::uint32_t,
                                 std::uint32_t,
                                 mcal::reg::scb_cpacr,
                                 static_cast<std::uint32_t>((3ULL << (10U * 2U)) | (3ULL << (11U * 2U)))>::reg_or();

    // Reset the RCC clock configuration to the default reset state.

    {
      const volatile std::uint32_t flash_latency_from_flash_acr = 
        mcal::reg::reg_access_static<std::uint32_t,
                                     std::uint32_t,
                                     mcal::reg::flash_acr>::reg_get() & static_cast<std::uint32_t>(FLASH_ACR_LATENCY);

      // Increase the CPU frequency.
      if(FLASH_LATENCY_DEFAULT > flash_latency_from_flash_acr)
      {
        // Program the new number of wait states to the LATENCY bits in the FLASH_ACR register.
        mcal::reg::reg_access_static<std::uint32_t,
                                     std::uint32_t,
                                     mcal::reg::flash_acr,
                                     static_cast<std::uint32_t>(FLASH_LATENCY_DEFAULT)>::reg_msk<static_cast<std::uint32_t>(FLASH_ACR_LATENCY)>();
      }
    }

    // Set HSION bit.
    mcal::reg::reg_access_static<std::uint32_t,
                                 std::uint32_t,
                                 mcal::reg::rcc_cr,
                                 static_cast<std::uint32_t>(RCC_CR_HSION)>::reg_or();

    // Reset CFGR register.
    mcal::reg::reg_access_static<std::uint32_t,
                                 std::uint32_t,
                                 mcal::reg::rcc_cfgr,
                                 static_cast<std::uint32_t>(UINT32_C(0x00000000))>::reg_set();

    /* Reset HSEON, HSECSSON, CSION, HSI48ON, CSIKERON, PLL1ON, PLL2ON and PLL3ON bits */
    mcal::reg::reg_access_static<std::uint32_t,
                                 std::uint32_t,
                                 mcal::reg::rcc_cr,
                                 static_cast<std::uint32_t>(UINT32_C(0xEAF6ED7F))>::reg_and();

    {
      const volatile std::uint32_t flash_latency_from_flash_acr = 
        mcal::reg::reg_access_static<std::uint32_t,
                                     std::uint32_t,
                                     mcal::reg::flash_acr>::reg_get() & static_cast<std::uint32_t>(FLASH_ACR_LATENCY);

      // Decrease the number of wait states because of lower CPU frequency.
      if(FLASH_LATENCY_DEFAULT < flash_latency_from_flash_acr)
      {
        // Program the new number of wait states to the LATENCY bits in the FLASH_ACR register.
        mcal::reg::reg_access_static<std::uint32_t,
                                     std::uint32_t,
                                     mcal::reg::flash_acr,
                                     static_cast<std::uint32_t>(FLASH_LATENCY_DEFAULT)>::reg_msk<static_cast<std::uint32_t>(FLASH_ACR_LATENCY)>();
      }
    }

    // Reset CDCFGR1 register.
    // RCC->CDCFGR1 = 0x00000000;
    mcal::reg::reg_access_static<std::uint32_t,
                                 std::uint32_t,
                                 mcal::reg::rcc_cdcfgr1,
                                 static_cast<std::uint32_t>(UINT32_C(0x00000000))>::reg_set();

    // Reset CDCFGR2 register.
    // RCC->CDCFGR2 = 0x00000000;
    mcal::reg::reg_access_static<std::uint32_t,
                                 std::uint32_t,
                                 mcal::reg::rcc_cdcfgr2,
                                 static_cast<std::uint32_t>(UINT32_C(0x00000000))>::reg_set();

    // Reset SRDCFGR register.
    // RCC->SRDCFGR = 0x00000000;
    mcal::reg::reg_access_static<std::uint32_t,
                                 std::uint32_t,
                                 mcal::reg::rcc_srdcfgr,
                                 static_cast<std::uint32_t>(UINT32_C(0x00000000))>::reg_set();

    // Reset PLLCKSELR register.
    // RCC->PLLCKSELR = 0x02020200;
    mcal::reg::reg_access_static<std::uint32_t,
                                 std::uint32_t,
                                 mcal::reg::rcc_pllckselr,
                                 static_cast<std::uint32_t>(UINT32_C(0x02020200))>::reg_set();

    // Reset PLLCFGR register.
    // RCC->PLLCFGR = 0x01FF0000;
    mcal::reg::reg_access_static<std::uint32_t,
                                 std::uint32_t,
                                 mcal::reg::rcc_pllcfgr,
                                 static_cast<std::uint32_t>(UINT32_C(0x01FF0000))>::reg_set();

    // Reset PLL1DIVR register.
    // RCC->PLL1DIVR = 0x01010280;
    mcal::reg::reg_access_static<std::uint32_t,
                                 std::uint32_t,
                                 mcal::reg::rcc_pll1divr,
                                 static_cast<std::uint32_t>(UINT32_C(0x01010280))>::reg_set();

    // Reset PLL1FRACR register.
    // RCC->PLL1FRACR = 0x00000000;
    mcal::reg::reg_access_static<std::uint32_t,
                                 std::uint32_t,
                                 mcal::reg::rcc_pll1fracr,
                                 static_cast<std::uint32_t>(UINT32_C(0x00000000))>::reg_set();

    // Reset PLL2DIVR register.
    // RCC->PLL2DIVR = 0x01010280;
    mcal::reg::reg_access_static<std::uint32_t,
                                 std::uint32_t,
                                 mcal::reg::rcc_pll2divr,
                                 static_cast<std::uint32_t>(UINT32_C(0x01010280))>::reg_set();

    // Reset PLL2FRACR register.
    // RCC->PLL2FRACR = 0x00000000;
    mcal::reg::reg_access_static<std::uint32_t,
                                 std::uint32_t,
                                 mcal::reg::rcc_pll2fracr,
                                 static_cast<std::uint32_t>(UINT32_C(0x00000000))>::reg_set();

    // Reset PLL3DIVR register.
    // RCC->PLL3DIVR = 0x01010280;
    mcal::reg::reg_access_static<std::uint32_t,
                                 std::uint32_t,
                                 mcal::reg::rcc_pll3divr,
                                 static_cast<std::uint32_t>(UINT32_C(0x01010280))>::reg_set();

    // Reset PLL3FRACR register.
    // RCC->PLL3FRACR = 0x00000000;
    mcal::reg::reg_access_static<std::uint32_t,
                                 std::uint32_t,
                                 mcal::reg::rcc_pll3fracr,
                                 static_cast<std::uint32_t>(UINT32_C(0x00000000))>::reg_set();

    // Reset HSEBYP bit.
    // RCC->CR &= 0xFFFBFFFFU;
    mcal::reg::reg_access_static<std::uint32_t,
                                 std::uint32_t,
                                 mcal::reg::rcc_cr,
                                 static_cast<std::uint32_t>(UINT32_C(0xFFFBFFFF))>::reg_and();

    // Disable all interrupts.
    // RCC->CIER = 0x00000000;
    mcal::reg::reg_access_static<std::uint32_t,
                                 std::uint32_t,
                                 mcal::reg::rcc_cier,
                                 static_cast<std::uint32_t>(UINT32_C(0x00000000))>::reg_set();

    // Disable the FMC bank1 (enabled after reset).
    // This prevents CPU speculation access on this bank which blocks
    // the use of the FMC for 24us. During this time the other FMC masters
    // (such as LTDC) cannot use it.
    ((FMC_Bank1_TypeDef*) mcal::reg::fmc_bank1_r_base)->BTCR[0U] = UINT32_C(0x000030D2);

    // Relocate the vector table to internal flash.
    mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::scb_vtor, 0x08000000UL>::reg_set();
  }

  void enable_i_cache()
  {
    // Enable instruction cache.
    asm volatile("dsb");
    asm volatile("isb");
    mcal::reg::reg_access_static<std::uint32_t,
                                 std::uint32_t,
                                 mcal::reg::scb_iciallu,
                                 static_cast<std::uint32_t>(UINT8_C(0))>::reg_set();
    asm volatile("dsb");
    asm volatile("isb");

    mcal::reg::reg_access_static<std::uint32_t,
                                 std::uint32_t,
                                 mcal::reg::scb_ccr,
                                 static_cast<std::uint32_t>(UINT8_C(17))>::bit_set();

    asm volatile("dsb");
    asm volatile("isb");
  }

  void enable_d_cache()
  {
    const auto d_cache_is_already_enabled =
      mcal::reg::reg_access_static<std::uint32_t,
                                   std::uint32_t,
                                   mcal::reg::scb_ccr,
                                   static_cast<std::uint32_t>(UINT8_C(16))>::bit_get();

    if(d_cache_is_already_enabled)
    {
      return;
    }

    // Select Level-1 data cache.
    mcal::reg::reg_access_static<std::uint32_t,
                                 std::uint32_t,
                                 mcal::reg::scb_csselr,
                                 static_cast<std::uint32_t>(UINT8_C(0))>::reg_set();

    asm volatile("dsb");

    const std::uint32_t ccsidr = mcal::reg::reg_access_static<std::uint32_t,
                                                              std::uint32_t,
                                                              mcal::reg::scb_ccsidr>::reg_get();

    // Invalidate the data cache.
    std::uint32_t sets = static_cast<std::uint32_t>(CCSIDR_SETS(ccsidr));
    std::uint32_t ways { };

    do
    {
      ways = static_cast<std::uint32_t>(CCSIDR_WAYS(ccsidr));

      do
      {
        const auto dcisw_value_new =
          static_cast<std::uint32_t>
          (
              static_cast<std::uint32_t>(static_cast<std::uint32_t>(sets << SCB_DCISW_SET_Pos) & SCB_DCISW_SET_Msk)
            | static_cast<std::uint32_t>(static_cast<std::uint32_t>(ways << SCB_DCISW_WAY_Pos) & SCB_DCISW_WAY_Msk)
          );

        mcal::reg::reg_access_dynamic<std::uint32_t,
                                      std::uint32_t>::reg_set(mcal::reg::scb_dcisw,
                                                              dcisw_value_new);
      }
      while (ways-- != 0U);
    }
    while(sets-- != 0U);

    asm volatile("dsb");

    // Enable D-Cache.
    mcal::reg::reg_access_static<std::uint32_t,
                                 std::uint32_t,
                                 mcal::reg::scb_ccr,
                                 static_cast<std::uint32_t>(UINT8_C(16))>::bit_set();

    asm volatile("dsb");
    asm volatile("isb");
  }
} // namespace local

void mcal::cpu::init()
{
  local::system_init();

  // Enable instruction cache.
  local::enable_i_cache();

  // Enable data cache.
  local::enable_d_cache();

  // Enable RCC peripheral clock(s).
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::rcc_apb4enr,
                               static_cast<std::uint32_t>(UINT8_C(1))>::bit_set();

  // Delay after an RCC peripheral clock enabling.
  volatile bool rcc_apb4enr_is_set = 
    mcal::reg::reg_access_static<std::uint32_t,
                                 std::uint32_t,
                                 mcal::reg::rcc_apb4enr,
                                 static_cast<std::uint32_t>(UINT8_C(1))>::bit_get();

  static_cast<void>(rcc_apb4enr_is_set);

  mcal::wdg::init(nullptr);
  mcal::port::init(nullptr);
  mcal::osc::init(nullptr);
}
