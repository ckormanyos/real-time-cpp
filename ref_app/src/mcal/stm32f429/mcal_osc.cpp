///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2011 - 2014.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdint>
#include <mcal_cpu.h>
#include <mcal_osc.h>
#include <mcal_osc_detail.h>
#include <mcal_reg_access.h>

namespace
{
  void set_the_system_clock()
  {
    // Set the HCLK frequency to 168MHz generated from an input HSE OSC of 8MHz.
    // The clock configuration class in the detail namespace has been used to
    // generate the clock settings.
    // The resulting frequency of tim2/3/4/5/6/7/12/13/14 is 84MHz.
    // The resulting frequency of tim1/8/9/10/11 is 168MHz.
    // The wait states are set in mcal_cpu.cpp.

    // Enable the hse.
    mcal::reg::access<std::uint32_t,
                      std::uint32_t,
                      mcal::reg::rcc_cr,
                      UINT32_C(0x00010000)>::reg_or();

    // Wait until the hse is ready.
    while(mcal::reg::access<std::uint32_t,
                            std::uint32_t,
                            mcal::reg::rcc_cr,
                            UINT32_C(17)>::bit_get() == false)
    {
      mcal::cpu::nop();
    }

    // Set the pll parameters.

    // pll_vco              =  (hse_value / pll_m) * pll_n
    // sysclk               = ((hse_value / pll_m) * pll_n) / pll_p
    // usb, sdio, rng clock = ((hse_value / pll_m) * pll_n) / pll_q

    const mcal::osc::detail::stm32f4xx_clock_settings my_stm32f4xx_clock_settings(UINT16_C(168), UINT8_C(8));

    const std::uint32_t pll_m = my_stm32f4xx_clock_settings.get_param_m();
    const std::uint32_t pll_n = my_stm32f4xx_clock_settings.get_param_n();
    const std::uint32_t pll_p = my_stm32f4xx_clock_settings.get_param_p();
    const std::uint32_t pll_q = my_stm32f4xx_clock_settings.get_param_q();

    const std::uint32_t rcc_pllcfgr_value =
      static_cast<std::uint32_t>(  pll_m
                                 | static_cast<std::uint32_t>(pll_n << 6)
                                 | static_cast<std::uint32_t>(static_cast<std::uint32_t>((pll_p >> 1) - 1) << 16)
                                 | UINT32_C(0x00400000)
                                 | static_cast<std::uint32_t>(pll_q << 24));

    // TBD: What should we do if the usb frequency is not exactly 48?
    const bool my_f_usb_is_exactly_48 = my_stm32f4xx_clock_settings.get_f_usb_is_exactly_48();
    static_cast<void>(my_f_usb_is_exactly_48);

    // Configure the main pll.
    mcal::reg::dynamic_access<std::uint32_t,
                              std::uint32_t>::reg_set(mcal::reg::rcc_pllcfgr,
                                                      rcc_pllcfgr_value);

    // Set hclk  = sysclk / 1.
    // Set pclk2 =   hclk / 2.
    // Set pclk1 =   hclk / 4.
    mcal::reg::access<std::uint32_t,
                      std::uint32_t,
                      mcal::reg::rcc_cfgr,
                      UINT32_C(0x00009400)>::reg_or();

    // Enable the pll via setting the pllon bit of the rcc_cr register.
    mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::rcc_cr, UINT32_C(0x01000000)>::reg_or();

    // Wait until the pll is locked.
    while(mcal::reg::access<std::uint32_t,
                            std::uint32_t,
                            mcal::reg::rcc_cr,
                            UINT32_C(25)>::bit_get() == false)
    {
      mcal::cpu::nop();
    }

    // Select the pll as the system clock source.
    mcal::reg::access<std::uint32_t,
                      std::uint32_t,
                      mcal::reg::rcc_cfgr,
                      UINT32_C(0x00000002)>::reg_msk<UINT32_C(0x00000003)>();

    std::uint32_t rcc_cfgr_sws_value = UINT32_C(0);

    // Wait until the pll is latched as the system clock source.
    while(rcc_cfgr_sws_value != UINT32_C(0x00000008))
    {
      rcc_cfgr_sws_value = mcal::reg::access<std::uint32_t,
                                             std::uint32_t,
                                             mcal::reg::rcc_cfgr>::reg_get() & UINT32_C(0x0000000C);
    }

    // Now we have:
    //   * The hse is ready.
    //   * The pll is locked.
    //   * The pll is the clock source.
  }
}

void mcal::osc::init(const config_type*)
{
  // Configure the system clock for 168MHz using the hse-pll.
  set_the_system_clock();
}
