///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2022.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_cpu.h>
#include <mcal_osc.h>
#include <mcal_reg.h>

namespace local
{
  auto enable_i_cache() -> void;
  auto enable_d_cache() -> void;

  auto enable_i_cache() -> void
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

  auto enable_d_cache() -> void
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
    std::uint32_t sets = static_cast<std::uint32_t>(mcal::cpu::ccsidr_sets(ccsidr));
    std::uint32_t ways { };

    do
    {
      ways = static_cast<std::uint32_t>(mcal::cpu::ccsidr_ways(ccsidr));

      do
      {
        const auto dcisw_value_new =
          static_cast<std::uint32_t>
          (
              static_cast<std::uint32_t>(static_cast<std::uint32_t>(sets << mcal::cpu::scb_dcisw_set_pos) & mcal::cpu::scb_dcisw_set_msk)
            | static_cast<std::uint32_t>(static_cast<std::uint32_t>(ways << mcal::cpu::scb_dcisw_way_pos) & mcal::cpu::scb_dcisw_way_msk)
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

void STM32H7A3ZI_InitClock(void);

void mcal::osc::init(const config_type*)
{
  // AXI clock gating.
  // RCC->CKGAENR = 0xFFFFFFFF;
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::rcc_ckgaenr,
                               static_cast<std::uint32_t>(UINT32_C(0xFFFFFFFF))>::reg_set();

  {
    // Supply configuration update enable.

    constexpr auto pwr_supply_config_mask = static_cast<std::uint32_t>(UINT8_C(0x3F));
    constexpr auto pwr_direct_smps_supply = static_cast<std::uint32_t>(UINT8_C(4));

    // Set the power supply configuration.
    mcal::reg::reg_access_static<std::uint32_t,
                                 std::uint32_t,
                                 mcal::reg::pwr_cr3,
                                 pwr_direct_smps_supply>::reg_msk<pwr_supply_config_mask>();

    constexpr auto delay_max = static_cast<std::uint32_t>(UINT32_C(1000000));

    // Wait until the voltage level flag is set.
    volatile auto delay = std::uint32_t { };

    for(  delay = static_cast<std::uint32_t>(UINT32_C(0));
          delay < delay_max;
        ++delay)
    {
      const auto pwr_flag_actvosrdy_is_set =
        mcal::reg::reg_access_static<std::uint32_t,
                                     std::uint32_t,
                                     mcal::reg::pwr_csr1,
                                     static_cast<std::uint32_t>(UINT8_C(13))>::bit_get();

      if(pwr_flag_actvosrdy_is_set)
      {
        break;
      }
    }
  }

  // Configure the main internal regulator output voltage
  // Configure the Voltage Scaling.
  // __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE0);
  {
    constexpr auto pwr_regulator_voltage_scale0 = static_cast<std::uint32_t>(UINT32_C(0x0000C000));
    constexpr auto pwr_srdcr_vos_msk            = static_cast<std::uint32_t>(UINT32_C(0x0000C000));

    mcal::reg::reg_access_static<std::uint32_t,
                                 std::uint32_t,
                                 mcal::reg::pwr_srdcr,
                                 pwr_regulator_voltage_scale0>::reg_msk<pwr_srdcr_vos_msk>();
  }

  // Delay after setting the voltage scaling
  const volatile auto tmpreg =
    mcal::reg::reg_access_static<std::uint32_t,
                                 std::uint32_t,
                                 mcal::reg::pwr_srdcr>::reg_get();

  static_cast<void>(tmpreg);

  while(!mcal::reg::reg_access_static<std::uint32_t,
                                      std::uint32_t,
                                      mcal::reg::pwr_srdcr,
                                      static_cast<std::uint32_t>(UINT8_C(13))>::bit_get()) { ; }

 // Configure the flash wait states (280 MHz --> 6 WS).
  //Flash->ACR.bit.LATENCY = 6u;
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::flash_acr,
                               mcal::cpu::flash_acr_latency_6ws>::reg_msk<mcal::cpu::flash_acr_latency>();

  STM32H7A3ZI_InitClock();

  // Enable instruction cache.
  local::enable_i_cache();

  // Enable data cache.
  local::enable_d_cache();
}

void STM32H7A3ZI_InitClock(void)
{
 // Configure PLL1.
  {
    // RCC->PLLCKSELR.bit.DIVM1    = 32u;
    mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::rcc_pllckselr, static_cast<std::uint32_t>(32ULL << 4U)>::reg_msk<static_cast<std::uint32_t>(63ULL << 4U)>();

    // RCC->PLLCFGR.bit.PLL1RGE    = 0u;
    mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::rcc_pllcfgr, UINT32_C(0)>::reg_msk<static_cast<std::uint32_t>(3ULL << 2U)>();

    // RCC->PLLCFGR.bit.PLL1VCOSEL = 0u;
    mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::rcc_pllcfgr, UINT32_C(1)>::bit_clr();

    // RCC->PLLCFGR.bit.PLL1FRACEN = 0u;
    mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::rcc_pllcfgr, UINT32_C(0)>::bit_clr();
  }

  {
    // RCC->PLLCFGR.bit.DIVP1EN = 1u;
    mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::rcc_pllcfgr, UINT32_C(16)>::bit_set();

    // RCC->PLLCFGR.bit.DIVQ1EN = 1u;
    mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::rcc_pllcfgr, UINT32_C(17)>::bit_set();

    // RCC->PLLCFGR.bit.DIVR1EN = 1u;
    mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::rcc_pllcfgr, UINT32_C(18)>::bit_set();
  }

  {
    // VCO = 560 MHz
    // RCC->PLL1DIVR.bit.DIVN1 = 279u;
    mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::rcc_pll1divr, UINT32_C(279)>::reg_msk<static_cast<std::uint32_t>(511ULL << 0U)>();

    // pll1_p_ck = 280 MHz
    // RCC->PLL1DIVR.bit.DIVP1 = 1u;
    mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::rcc_pll1divr, static_cast<std::uint32_t>(1ULL << 9U)>::reg_msk<static_cast<std::uint32_t>(127ULL << 9U)>();

    // pll1_q_ck = 280 MHz
    // RCC->PLL1DIVR.bit.DIVQ1 = 1u;
    mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::rcc_pll1divr, static_cast<std::uint32_t>(1ULL << 16U)>::reg_msk<static_cast<std::uint32_t>(127ULL << 16U)>();

    // pll1_r_ck = 280 MHz
    // RCC->PLL1DIVR.bit.DIVR1 = 1u;
    mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::rcc_pll1divr, static_cast<std::uint32_t>(1ULL << 24U)>::reg_msk<static_cast<std::uint32_t>(127ULL << 24U)>();
  }

  // Enable PLL1.
  //RCC->CR.bit.PLL1ON = 1u;
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::rcc_cr, UINT32_C(24)>::bit_set();

  // Wait for PLL1 to become ready.
  //while(!RCC->CR.bit.PLL1RDY) { ; }
  while(!mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::rcc_cr, UINT32_C(25)>::bit_get())
  {
    mcal::cpu::nop();
  }

  // Set pll1_p_ck as the system clock.
  //RCC->CFGR.bit.SW = 3u;
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::rcc_cfgr, UINT32_C(3)>::reg_msk<static_cast<std::uint32_t>(7ULL << 0U)>();

  // Wait for pll1_p_ck to become the system clock.
  //while(RCC->CFGR.bit.SWS != 3u) { ; }
  for(;;)
  {
    const auto sws_value =
      static_cast<std::uint32_t>
      (
          static_cast<std::uint32_t>
          (
            mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::rcc_cfgr>::reg_get() >> 3U
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
