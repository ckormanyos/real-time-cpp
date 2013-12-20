///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdint>
#include <mcal_cpu.h>
#include <mcal_osc.h>
#include <mcal_reg_access.h>

namespace
{
  constexpr std::uint32_t pll_m = UINT32_C(8);
  constexpr std::uint32_t pll_n = UINT32_C(336);
  constexpr std::uint32_t pll_p = UINT32_C(2);
  constexpr std::uint32_t pll_q = UINT32_C(7);

  constexpr std::uint32_t hse_startup_timeout    = UINT32_C(0x05000);

  constexpr std::uint32_t rcc_cr_hseon           = UINT32_C(0x00010000);
  constexpr std::uint32_t rcc_cr_hserdy_bit      = UINT32_C(17);
  constexpr std::uint32_t rcc_pllcfgr_pllsrc_hse = UINT32_C(0x00400000);
  constexpr std::uint32_t rcc_apb1enr_pwren      = UINT32_C(0x10000000);
  constexpr std::uint32_t pwr_cr_vos_bit         = UINT32_C(14);
  constexpr std::uint32_t rcc_cr_pllrdy_bit      = UINT32_C(25);
  constexpr std::uint32_t rcc_cfgr_sw            = UINT32_C(0x00000003);
  constexpr std::uint32_t rcc_cfgr_sw_pll        = UINT32_C(0x00000002);
  constexpr std::uint32_t rcc_cfgr_sws           = UINT32_C(0x0000000C);
  constexpr std::uint32_t rcc_cfgr_sws_pll       = UINT32_C(0x00000008);

  void set_the_system_clock()
  {
    // Configure the system clock for 128MHz.
    // The hse pll is used as the system clock source.

    // Enable the hse.
    mcal::reg::access<std::uint32_t,
                      std::uint32_t,
                      mcal::reg::rcc_cr,
                      rcc_cr_hseon>::reg_or();

    volatile bool hse_is_ready;

    // Wait until the hse is ready.
    for(volatile std::uint32_t start_up_counter = UINT32_C(0); start_up_counter < hse_startup_timeout; ++start_up_counter)
    {
      mcal::cpu::nop();

      hse_is_ready = mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::rcc_cr, rcc_cr_hserdy_bit>::bit_get();

      if(hse_is_ready) { break; }
    }

    // Verify that the hse is ready.
    if(hse_is_ready)
    {
      // Set the pll Parameters.

      // pll_vco = (hse_value / pll_m) * pll_n
      // sysclk = pll_vco / pll_p
      // usb otg fs, sdio and rng clock =  pll_vco / pll_q

      // Configure the main PLL.
      mcal::reg::access<std::uint32_t,
                        std::uint32_t,
                        mcal::reg::rcc_pllcfgr,
                        static_cast<std::uint32_t>(     pll_m
                                                   |   (pll_n << 6)
                                                   | (((pll_p >> 1) - 1) << 16)
                                                   | rcc_pllcfgr_pllsrc_hse
                                                   |   (pll_q << 24))>::reg_set();
    }
    else
    {
      // If the hse fails to start-up, then the application will have
      // the wrong clock configuration. Here, appropriate error code
      // can be added if desired.
      for(;;) { mcal::cpu::nop(); }
    }

    // Enable the power interface clock.
    mcal::reg::access<std::uint32_t,
                      std::uint32_t,
                      mcal::reg::rcc_apb1enr,
                      rcc_apb1enr_pwren>::reg_or();

    // Select the regulator voltage scaling output to scale 1 mode.
    mcal::reg::access<std::uint32_t,
                      std::uint32_t,
                      mcal::reg::pwr_cr,
                      pwr_cr_vos_bit>::bit_set();

    // Set hclk  = sysclk / 1.
    // Set pclk2 =   hclk / 2.
    // Set pclk1 =   hclk / 4.
    mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::rcc_cfgr, UINT32_C(0x00009400)>::reg_or();

    // Enable the main PLL.
    mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::rcc_cr, UINT32_C(0x01000000)>::reg_or();

    // Wait until the main PLL is ready.
    while(false == mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::rcc_cr, rcc_cr_pllrdy_bit>::bit_get())
    {
      mcal::cpu::nop();
    }

    // Select the main pll as the system clock source.
    mcal::reg::access<std::uint32_t,
                      std::uint32_t,
                      mcal::reg::rcc_cfgr,
                      rcc_cfgr_sw_pll>::reg_msk<rcc_cfgr_sw>();

    volatile bool pll_is_the_clock_source = false;

    // Ensure that the pll is the clock source.
    while(false == pll_is_the_clock_source)
    {
      mcal::cpu::nop();

      const std::uint32_t rcc_cfgr_sws_value =
        mcal::reg::access<std::uint32_t,
                          std::uint32_t,
                          mcal::reg::rcc_cfgr>::reg_get() & rcc_cfgr_sws;

      pll_is_the_clock_source = (rcc_cfgr_sws_value == rcc_cfgr_sws_pll);
    }
  }
}


void mcal::osc::init(const config_type*)
{
  set_the_system_clock();
}
