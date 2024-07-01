///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2011 - 2018.
//  Copyright Joel Winarske 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdint>

#include <mcal_osc.h>
#include <mcal_reg.h>
#include <mcal_cpu.h>
#include <mcal_config.h>


void mcal::osc::init(const config_type*)
{
  constexpr std::uint32_t syscon_pllclksrc_mainosc_sel = UINT32_C(1);
  constexpr std::uint32_t syscon_mainclksrc_pllout_sel = UINT32_C(3);
  constexpr std::uint32_t flashtim_50mhz_cpu_sel       = UINT32_C(3);

  constexpr std::uint32_t syspll_m_msk                 = UINT32_C(0x1F);
  constexpr std::uint32_t syspll_p_msk                 = UINT32_C(0x3);

  // Power on the system OSC.
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::syscon_pdruncfg,
                               mcal::reg::syscon_pdruncfg_sysosc_pd_bpos>::bit_clr();

  // Wait for the system OSC to stabilize.
  for(volatile std::uint_fast16_t i = UINT16_C(0); i < UINT16_C(0x100); ++i) {

    // TBD: Can a bit or other hardware register
    // be used here as a condition to break the loop?
    mcal::cpu::nop();
  }

  // Select the PLL clock source as the main OSC.
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::syscon_syspllclksel,
                               syscon_pllclksrc_mainosc_sel>::reg_set();
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::syscon_syspllclkuen,
                               UINT32_C(0)>::reg_set();
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::syscon_syspllclkuen,
                               UINT32_C(1)>::reg_set();

  // Power off the PLL.
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::syscon_pdruncfg,
                               mcal::reg::syscon_pdruncfg_syspll_pd_bpos>::bit_set();

  // Setup the PLL.
  constexpr std::uint32_t syscon_syspllctrl_value =
    std::uint32_t(   ((mcal::config::syspll_m - 1U) & syspll_m_msk)
                  | (((mcal::config::syspll_p - 1U) & syspll_p_msk) << 5U));

  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::syscon_syspllctrl,
                               syscon_syspllctrl_value>::reg_set();

  // Power on the PLL.
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::syscon_pdruncfg,
                               mcal::reg::syscon_pdruncfg_syspll_pd_bpos>::bit_clr();

  // Wait for the PLL to lock.
  while(mcal::reg::reg_access_static<std::uint32_t,
                                     std::uint32_t,
                                     mcal::reg::syscon_syspllstat,
                                     UINT32_C(0)>::bit_get() == false) { mcal::cpu::nop(); }

  // Set the AHB clock divider.
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::syscon_sysahbclkdiv,
                               mcal::config::sysahbclkdiv>::reg_set();

  // Set the flash wait states per system clock.
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::flash_flashcfg,
                               flashtim_50mhz_cpu_sel>::template reg_msk<UINT32_C(0x03)>();

  // Set the main clock as PLL out.
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::syscon_mainclksel,
                               syscon_mainclksrc_pllout_sel>::reg_set();
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::syscon_mainclkuen,
                               UINT32_C(0)>::reg_set();
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::syscon_mainclkuen,
                               UINT32_C(1)>::reg_set();

  // Enable the IOCON clock.
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::syscon_sysahbclkctrl,
                               mcal::reg::syscon_clock_iocon>::reg_or();
}

std::uint32_t mcal::osc::get_sys_clk_rate()
{
  const std::uint32_t syscon_mainclksel_value =
    mcal::reg::reg_access_static<std::uint32_t,
                                 std::uint32_t,
                                 mcal::reg::syscon_mainclksel>::reg_get();

  std::uint32_t clk_rate;

  switch(syscon_mainclksel_value & 0x3U) {

    case syscon_mainclksel_irc:
    case syscon_mainclksel_pllin:
      clk_rate = mcal::config::fclkin;
      break;

    case syscon_mainclksel_wdtosc:
      clk_rate = mcal::osc::get_wdt_osc_rate();
      break;

    case syscon_mainclksel_pllout:
      clk_rate = mcal::osc::get_sys_pllout_clk_rate();
      break;

    default:
      clk_rate = UINT32_C(0);
  }

  return std::uint32_t(clk_rate /
    mcal::reg::reg_access_static<std::uint32_t,
                                 std::uint32_t,
                                 mcal::reg::syscon_sysahbclkdiv>::reg_get());
}

std::uint32_t mcal::osc::get_sys_pllout_clk_rate()
{
  const std::uint32_t pll =
    mcal::reg::reg_access_static<std::uint32_t,
                                 std::uint32_t,
                                 mcal::reg::syscon_syspllctrl>::reg_get();

  return mcal::config::fclkin * std::uint32_t(std::uint32_t(pll & 0x1FU) + 1U);
}

void mcal::osc::set_wdt_osc(std::uint32_t freqsel, std::uint32_t divsel)
{
  const std::uint32_t wdt_osc_value =
    std::uint32_t(freqsel << 5U) | std::uint32_t(std::uint32_t(divsel >> 1U) - 1U);

  mcal::reg::reg_access_dynamic<std::uint32_t,
                                std::uint32_t>::reg_set(mcal::reg::syscon_wdtoscctrl,
                                                        wdt_osc_value);
}

void mcal::osc::set_wdt_clk_src(const std::uint32_t src, const std::uint32_t div)
{
  mcal::reg::reg_access_dynamic<std::uint32_t,
                                std::uint32_t>::reg_set(mcal::reg::syscon_wdtclksel, src);

  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::syscon_wdtclkuen,
                               UINT32_C(0)>::reg_set();

  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::syscon_wdtclkuen,
                               UINT32_C(1)>::reg_set();

  mcal::reg::reg_access_dynamic<std::uint32_t,
                                std::uint32_t>::reg_set(mcal::reg::syscon_wdtclkdiv, div);
}

std::uint32_t mcal::osc::get_wdt_osc_rate()
{
  const std::uint32_t div =
    mcal::reg::reg_access_static<std::uint32_t,
                                 std::uint32_t,
                                 mcal::reg::syscon_wdtoscctrl>::reg_get() & 0x1FU;

  const std::uint32_t clk = std::uint32_t(std::uint32_t(div >> 5U) & 0xFU);

  return wdt_osc_rate.begin()[clk] / std::uint32_t(std::uint32_t(div + 1U) << 1U);
}
