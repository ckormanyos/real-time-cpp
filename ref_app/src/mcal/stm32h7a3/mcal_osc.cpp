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
#include <mcal_reg.h>

namespace
{
  bool set_the_system_clock()
  {
    // Set the HCLK frequency to 168MHz generated from an input HSE OSC of 8MHz.
    // The clock configuration class in the detail namespace has been used to
    // generate the clock settings.
    // The resulting frequency of tim2/3/4/5/6/7/12/13/14 is 84MHz.
    // The resulting frequency of tim1/8/9/10/11 is 168MHz.
    // The wait states are set in mcal_cpu.cpp.

    // Enable the hse.
    mcal::reg::reg_access_static<std::uint32_t,
                                 std::uint32_t,
                                 mcal::reg::rcc_cr,
                                 UINT32_C(0x00010000)>::reg_or();

    // Wait until the hse is ready.
    while(mcal::reg::reg_access_static<std::uint32_t,
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

    const mcal::osc::detail::stm32f4xx_clock_settings my_clock_settings(UINT16_C(168), UINT8_C(8));

    if(my_clock_settings.get_clock_settings_are_valid())
    {
      const std::uint32_t rcc_pllcfgr_value =
        static_cast<std::uint32_t>(  my_clock_settings.get_param_m()
                                   | static_cast<std::uint32_t>(my_clock_settings.get_param_n() << 6)
                                   | static_cast<std::uint32_t>(static_cast<std::uint32_t>((my_clock_settings.get_param_p() >> 1) - 1) << 16)
                                   | UINT32_C(0x00400000)
                                   | static_cast<std::uint32_t>(my_clock_settings.get_param_q() << 24));

      // TBD: What should we do if the usb frequency is not exactly 48?
      const bool my_f_usb_is_exactly_48 = my_clock_settings.get_f_usb_is_exactly_48();
      static_cast<void>(my_f_usb_is_exactly_48);

      // Configure the main pll.
      mcal::reg::reg_access_dynamic<std::uint32_t,
                                    std::uint32_t>::reg_set(mcal::reg::rcc_pllcfgr,
                                                            rcc_pllcfgr_value);

      // Set hclk  = sysclk / 1.
      // Set pclk2 =   hclk / 2.
      // Set pclk1 =   hclk / 4.
      mcal::reg::reg_access_static<std::uint32_t,
                                   std::uint32_t,
                                   mcal::reg::rcc_cfgr,
                                   UINT32_C(0x00009400)>::reg_or();

      // Enable the pll via setting the pllon bit of the rcc_cr register.
      mcal::reg::reg_access_static<std::uint32_t,
                                   std::uint32_t,
                                   mcal::reg::rcc_cr,
                                   UINT32_C(0x01000000)>::reg_or();

      // Wait until the pll is locked.
      while(mcal::reg::reg_access_static<std::uint32_t,
                                         std::uint32_t,
                                         mcal::reg::rcc_cr,
                                         UINT32_C(25)>::bit_get() == false)
      {
        mcal::cpu::nop();
      }

      // Select the pll as the system clock source.
      mcal::reg::reg_access_static<std::uint32_t,
                                   std::uint32_t,
                                   mcal::reg::rcc_cfgr,
                                   UINT32_C(2)>::reg_msk<UINT32_C(3)>();

      volatile std::uint32_t mcal_osc_rcc_cfgr = UINT32_C(0);

      // Wait until the pll is latched as the system clock source.
      while(mcal_osc_rcc_cfgr != UINT32_C(0x00000008))
      {
        mcal_osc_rcc_cfgr =
          mcal::reg::reg_access_static<std::uint32_t,
                                       std::uint32_t,
                                       mcal::reg::rcc_cfgr>::reg_get() & UINT32_C(0x0000000C);
      }

      // Now we have:
      //   * The hse is ready.
      //   * The pll is locked.
      //   * The pll is the clock source.
      return true;
    }
    else
    {
      return false;
    }
  }
}

void mcal::osc::init(const config_type*)
{
  // Configure the system clock for 168MHz using the hse-pll.
  const bool system_clock_is_ok = set_the_system_clock();

  static_cast<void>(system_clock_is_ok);
}
