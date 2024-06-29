///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2022.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_cpu.h>
#include <mcal_osc.h>
#include <mcal_reg.h>

void mcal::osc::init(const config_type*)
{
  // Configure PLL1.
  {
    // RCC->PLLCKSELR.bit.DIVM1    = 32u;
    mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::rcc_pllckselr, static_cast<std::uint32_t>(32ULL << 4U)>::template reg_msk<static_cast<std::uint32_t>(63ULL << 4U)>();

    // RCC->PLLCFGR.bit.PLL1RGE    = 0u;
    mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::rcc_pllcfgr, static_cast<std::uint32_t>(UINT8_C(0))>::template reg_msk<static_cast<std::uint32_t>(3ULL << 2U)>();

    // RCC->PLLCFGR.bit.PLL1VCOSEL = 0u;
    mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::rcc_pllcfgr, static_cast<std::uint32_t>(UINT8_C(1))>::bit_clr();

    // RCC->PLLCFGR.bit.PLL1FRACEN = 0u;
    mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::rcc_pllcfgr, static_cast<std::uint32_t>(UINT8_C(0))>::bit_clr();
  }

  {
    // RCC->PLLCFGR.bit.DIVP1EN = 1u;
    mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::rcc_pllcfgr, static_cast<std::uint32_t>(UINT8_C(16))>::bit_set();

    // RCC->PLLCFGR.bit.DIVQ1EN = 1u;
    mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::rcc_pllcfgr, static_cast<std::uint32_t>(UINT8_C(17))>::bit_set();

    // RCC->PLLCFGR.bit.DIVR1EN = 1u;
    mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::rcc_pllcfgr, static_cast<std::uint32_t>(UINT8_C(18))>::bit_set();
  }

  {
    // VCO = 560 MHz
    // RCC->PLL1DIVR.bit.DIVN1 = 279u;
    mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::rcc_pll1divr, static_cast<std::uint32_t>(UINT32_C(279))>::template reg_msk<static_cast<std::uint32_t>(511ULL << 0U)>();

    // pll1_p_ck = 280 MHz
    // RCC->PLL1DIVR.bit.DIVP1 = 1u;
    mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::rcc_pll1divr, static_cast<std::uint32_t>(1ULL << 9U)>::template reg_msk<static_cast<std::uint32_t>(127ULL << 9U)>();

    // pll1_q_ck = 280 MHz
    // RCC->PLL1DIVR.bit.DIVQ1 = 1u;
    mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::rcc_pll1divr, static_cast<std::uint32_t>(1ULL << 16U)>::template reg_msk<static_cast<std::uint32_t>(127ULL << 16U)>();

    // pll1_r_ck = 280 MHz
    // RCC->PLL1DIVR.bit.DIVR1 = 1u;
    mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::rcc_pll1divr, static_cast<std::uint32_t>(1ULL << 24U)>::template reg_msk<static_cast<std::uint32_t>(127ULL << 24U)>();
  }

  // Enable PLL1.
  //RCC->CR.bit.PLL1ON = 1u;
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::rcc_cr, static_cast<std::uint32_t>(UINT8_C(24))>::bit_set();

  // Wait for PLL1 to become ready.
  //while(!RCC->CR.bit.PLL1RDY) { ; }
  while(!mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::rcc_cr, static_cast<std::uint32_t>(UINT8_C(25))>::bit_get())
  {
    mcal::cpu::nop();
  }

  // Set pll1_p_ck as the system clock.
  //RCC->CFGR.bit.SW = 3u;
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::rcc_cfgr, static_cast<std::uint32_t>(UINT8_C(3))>::template reg_msk<static_cast<std::uint32_t>(7ULL << 0U)>();

  // Wait for pll1_p_ck to become the system clock.
  //while(RCC->CFGR.bit.SWS != 3u) { ; }
  for(;;)
  {
    const auto sws_value =
      static_cast<std::uint32_t>
      (
          static_cast<std::uint32_t>
          (
               mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::rcc_cfgr>::reg_get()
            >> static_cast<unsigned>(UINT8_C(3))
          )
        &
          static_cast<std::uint32_t>(UINT8_C(7))
      );

    if(sws_value == static_cast<std::uint32_t>(UINT8_C(3)))
    {
      break;
    }
  }
}
