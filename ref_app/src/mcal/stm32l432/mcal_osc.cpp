///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2011 - 2014.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_cpu.h>
#include <mcal_gpt.h>
#include <mcal_osc.h>
#include <mcal_reg.h>

namespace
{
  auto set_system_clock() -> bool;

  auto set_system_clock() -> bool
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
                                 static_cast<std::uint32_t>(UINT32_C(0x00010000))>::reg_or();

    // Wait until the hse is ready.
    while(!mcal::reg::reg_access_static<std::uint32_t,
                                        std::uint32_t,
                                        mcal::reg::rcc_cr,
                                        static_cast<std::uint32_t>(UINT8_C(17))>::bit_get())
    {
      mcal::cpu::nop();
    }

    // Set the pll parameters.

    // pll_vco              =  (hse_value / pll_m) * pll_n
    // sysclk               = ((hse_value / pll_m) * pll_n) / pll_p
    // usb, sdio, rng clock = ((hse_value / pll_m) * pll_n) / pll_q

    using local_arm_sys_tick_type       = mcal::gpt::arm_sys_tick_type;
    using local_arm_sys_tick_value_type = typename local_arm_sys_tick_type::value_type;

    const auto param_n =
      static_cast<std::uint32_t>
      (
        (local_arm_sys_tick_type::sys_tick_mhz() == static_cast<local_arm_sys_tick_value_type>(UINT16_C(180)))
          ? static_cast<std::uint32_t>(UINT16_C(360))
          : static_cast<std::uint32_t>(UINT16_C(336))
      );

    // Configure the main pll.
    constexpr auto rcc_pllcfgr_value =
      static_cast<std::uint32_t>
      (
          static_cast<std::uint32_t>(static_cast<std::uint32_t>(UINT8_C(8)) << static_cast<unsigned>(UINT8_C( 0))) // pll_m
        | static_cast<std::uint32_t>(param_n                                << static_cast<unsigned>(UINT8_C( 6))) // pll_n
        | static_cast<std::uint32_t>(static_cast<std::uint32_t>(UINT8_C(0)) << static_cast<unsigned>(UINT8_C(16))) // pll_p
        | static_cast<std::uint32_t>(static_cast<std::uint32_t>(UINT8_C(1)) << static_cast<unsigned>(UINT8_C(22))) // pll_source (hse)
        | static_cast<std::uint32_t>(static_cast<std::uint32_t>(UINT8_C(7)) << static_cast<unsigned>(UINT8_C(24))) // pll_q
      );

    // Verify the exact PLL settings at compile-time.
    static_assert
    (
         ((param_n == static_cast<std::uint32_t>(UINT16_C(336))) && (rcc_pllcfgr_value == static_cast<std::uint32_t>(UINT32_C(0x07405408))))
      || ((param_n == static_cast<std::uint32_t>(UINT16_C(360))) && (rcc_pllcfgr_value == static_cast<std::uint32_t>(UINT32_C(0x07405A08)))),
      "Error: Wrong PLL configuration. Please check PLL parameters."
    );

    mcal::reg::reg_access_static<std::uint32_t,
                                  std::uint32_t,
                                  mcal::reg::rcc_pllcfgr,
                                  rcc_pllcfgr_value>::reg_set();

    // Set hclk  = sysclk / 1.
    // Set pclk2 =   hclk / 2.
    // Set pclk1 =   hclk / 4.
    mcal::reg::reg_access_static<std::uint32_t,
                                  std::uint32_t,
                                  mcal::reg::rcc_cfgr,
                                  static_cast<std::uint32_t>(UINT32_C(0x00009400))>::reg_or();

    // Enable the pll via setting the pllon bit of the rcc_cr register.
    mcal::reg::reg_access_static<std::uint32_t,
                                  std::uint32_t,
                                  mcal::reg::rcc_cr,
                                  static_cast<std::uint32_t>(UINT32_C(0x01000000))>::reg_or();

    // Wait until the pll is locked.
    while(!mcal::reg::reg_access_static<std::uint32_t,
                                        std::uint32_t,
                                        mcal::reg::rcc_cr,
                                        static_cast<std::uint32_t>(UINT8_C(25))>::bit_get())
    {
      mcal::cpu::nop();
    }

    // Select the pll as the system clock source.
    mcal::reg::reg_access_static<std::uint32_t,
                                  std::uint32_t,
                                  mcal::reg::rcc_cfgr,
                                  static_cast<std::uint32_t>(UINT8_C(2))>::template reg_msk<static_cast<std::uint32_t>(UINT8_C(3))>();

    volatile auto mcal_osc_rcc_cfgr = static_cast<std::uint32_t>(UINT8_C(0));

    // Wait until the pll is latched as the system clock source.
    while(mcal_osc_rcc_cfgr != static_cast<std::uint32_t>(UINT32_C(0x00000008)))
    {
      mcal_osc_rcc_cfgr =
        static_cast<std::uint32_t>
        (
            mcal::reg::reg_access_static<std::uint32_t,
                                          std::uint32_t,
                                          mcal::reg::rcc_cfgr>::reg_get()
          & static_cast<std::uint32_t>(UINT32_C(0x0000000C))
        );
    }

    // Now we have:
    //   * The hse is ready.
    //   * The pll is locked.
    //   * The pll is the clock source.
    return true;
  }
}

void mcal::osc::init(const config_type*)
{
  // Configure the system clock for 168MHz using the hse-pll.
  const auto result_system_clock_is_ok = set_system_clock();

  static_cast<void>(result_system_clock_is_ok);
}
