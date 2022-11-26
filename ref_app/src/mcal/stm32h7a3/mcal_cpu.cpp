///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2022.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "stm32h7xx.h"

#include <mcal_cpu.h>
#include <mcal_osc.h>
#include <mcal_port.h>
#include <mcal_reg.h>
#include <mcal_wdg.h>


namespace local
{
  auto system_init       () -> void;
  auto system_pll_default() -> void;

  auto system_init() -> void
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

    // Reset the HSEON, HSECSSON, CSION, HSI48ON, CSIKERON, PLL1ON, PLL2ON and PLL3ON bits.
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
    mcal::reg::reg_access_static<std::uint32_t,
                                 std::uint32_t,
                                 mcal::reg::rcc_cdcfgr1,
                                 static_cast<std::uint32_t>(UINT32_C(0x00000000))>::reg_set();

    // Reset CDCFGR2 register.
    mcal::reg::reg_access_static<std::uint32_t,
                                 std::uint32_t,
                                 mcal::reg::rcc_cdcfgr2,
                                 static_cast<std::uint32_t>(UINT32_C(0x00000000))>::reg_set();

    // Reset SRDCFGR register.
    mcal::reg::reg_access_static<std::uint32_t,
                                 std::uint32_t,
                                 mcal::reg::rcc_srdcfgr,
                                 static_cast<std::uint32_t>(UINT32_C(0x00000000))>::reg_set();

    // Set (reset) default PLL settings.
    system_pll_default();

    // Reset HSEBYP bit.
    mcal::reg::reg_access_static<std::uint32_t,
                                 std::uint32_t,
                                 mcal::reg::rcc_cr,
                                 static_cast<std::uint32_t>(UINT32_C(0xFFFBFFFF))>::reg_and();

    // Disable all interrupts.
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

  auto system_pll_default() -> void
  {
    // Set (reset) default PLL settings.
    // Reset PLLCKSELR register.
    mcal::reg::reg_access_static<std::uint32_t,
                                 std::uint32_t,
                                 mcal::reg::rcc_pllckselr,
                                 static_cast<std::uint32_t>(UINT32_C(0x02020200))>::reg_set();

    // Reset PLLCFGR register.
    mcal::reg::reg_access_static<std::uint32_t,
                                 std::uint32_t,
                                 mcal::reg::rcc_pllcfgr,
                                 static_cast<std::uint32_t>(UINT32_C(0x01FF0000))>::reg_set();

    // Reset PLL1DIVR register.
    mcal::reg::reg_access_static<std::uint32_t,
                                 std::uint32_t,
                                 mcal::reg::rcc_pll1divr,
                                 static_cast<std::uint32_t>(UINT32_C(0x01010280))>::reg_set();

    // Reset PLL1FRACR register.
    mcal::reg::reg_access_static<std::uint32_t,
                                 std::uint32_t,
                                 mcal::reg::rcc_pll1fracr,
                                 static_cast<std::uint32_t>(UINT32_C(0x00000000))>::reg_set();

    // Reset PLL2DIVR register.
    mcal::reg::reg_access_static<std::uint32_t,
                                 std::uint32_t,
                                 mcal::reg::rcc_pll2divr,
                                 static_cast<std::uint32_t>(UINT32_C(0x01010280))>::reg_set();

    // Reset PLL2FRACR register.
    mcal::reg::reg_access_static<std::uint32_t,
                                 std::uint32_t,
                                 mcal::reg::rcc_pll2fracr,
                                 static_cast<std::uint32_t>(UINT32_C(0x00000000))>::reg_set();

    // Reset PLL3DIVR register.
    mcal::reg::reg_access_static<std::uint32_t,
                                 std::uint32_t,
                                 mcal::reg::rcc_pll3divr,
                                 static_cast<std::uint32_t>(UINT32_C(0x01010280))>::reg_set();

    // Reset PLL3FRACR register.
    mcal::reg::reg_access_static<std::uint32_t,
                                 std::uint32_t,
                                 mcal::reg::rcc_pll3fracr,
                                 static_cast<std::uint32_t>(UINT32_C(0x00000000))>::reg_set();
  }
} // namespace local

void mcal::cpu::init()
{
  local::system_init();

  mcal::wdg::init(nullptr);
  mcal::port::init(nullptr);
  mcal::osc::init(nullptr);
}
