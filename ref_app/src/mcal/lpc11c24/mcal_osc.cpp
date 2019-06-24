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
  static constexpr std::uint32_t syscon_pllclksrc_mainosc_sel    = UINT32_C(1);
  static constexpr std::uint32_t syscon_mainclksrc_pllout_sel    = UINT32_C(3);
  static constexpr std::uint32_t flashtim_50mhz_cpu_sel          = UINT32_C(3);

  static constexpr std::uint32_t syspll_m_msk                    = UINT32_C(0x1F);
  static constexpr std::uint32_t syspll_p_msk                    = UINT32_C(0x3);


  // Power on System Osc.
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, 
                               mcal::reg::syscon_pdruncfg, 
                               mcal::reg::syscon_pdruncfg_sysosc_pd_bpos>::bit_clr();

  // Wait for System Osc to stabilize.
  for (volatile int i = 0; i < 0x100; i++) {}

  // Select PLL Clock Source as Main OSC.
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, 
                               mcal::reg::syscon_syspllclksel, 
                               syscon_pllclksrc_mainosc_sel>::reg_set();
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, 
                               mcal::reg::syscon_syspllclkuen, 
                               UINT32_C(0)>::reg_set();
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, 
                               mcal::reg::syscon_syspllclkuen, 
                               UINT32_C(1)>::reg_set();

  // Power Off PLL.
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, 
                               mcal::reg::syscon_pdruncfg, 
                               mcal::reg::syscon_pdruncfg_syspll_pd_bpos>::bit_set();

  // Setup PLL.
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, 
                               mcal::reg::syscon_syspllctrl,
                               (((mcal::config::syspll_m - 1) & syspll_m_msk) | 
                               (((mcal::config::syspll_p - 1) & syspll_p_msk) << 5))>::reg_set();

  // Power On PLL.
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, 
                               mcal::reg::syscon_pdruncfg, 
                               mcal::reg::syscon_pdruncfg_syspll_pd_bpos>::bit_clr();

  // Wait for PLL to lock.
  while(
    (mcal::reg::reg_access_static<std::uint32_t, std::uint32_t,
                                  mcal::reg::syscon_syspllstat>::reg_get() & 1) == 0) { mcal::cpu::nop(); }

  // Set AHB clock divider.
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, 
                               mcal::reg::syscon_sysahbclkdiv, 
                               mcal::config::sysahbclkdiv>::reg_set();

  // Set Flash wait states per system clock.
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, 
                               mcal::reg::flash_flashcfg, 
                               flashtim_50mhz_cpu_sel>::reg_msk<UINT32_C(0x03)>();

  // Set Main Clock as PLL out.
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, 
                               mcal::reg::syscon_mainclksel, 
                               syscon_mainclksrc_pllout_sel>::reg_set();
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, 
                               mcal::reg::syscon_mainclkuen, 
                               UINT32_C(0)>::reg_set();
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, 
                               mcal::reg::syscon_mainclkuen, 
                               UINT32_C(1)>::reg_set();

  // Enable IOCON Clock.
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, 
                               mcal::reg::syscon_sysahbclkctrl, 
                               mcal::reg::syscon_clock_iocon>::reg_or();
}

std::uint32_t mcal::osc::get_sys_clk_rate()
{
	uint32_t clk_rate = 0;

  switch(mcal::reg::reg_access_static<std::uint32_t, std::uint32_t,
                              mcal::reg::syscon_mainclksel>::reg_get() & 0x3) {

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
      clk_rate = 0;
    }

    return clk_rate /
      mcal::reg::reg_access_static<std::uint32_t, std::uint32_t,
                                   mcal::reg::syscon_sysahbclkdiv>::reg_get();
}

std::uint32_t mcal::osc::get_sys_pllout_clk_rate()
{
  uint32_t pll = mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, 
                                              mcal::reg::syscon_syspllctrl>::reg_get();
	return mcal::config::fclkin * ((pll & 0x1F) + 1);
}

void mcal::osc::set_wdt_osc(std::uint32_t freqsel, std::uint32_t divsel)
{
  mcal::reg::reg_access_dynamic<std::uint32_t, std::uint32_t>::reg_set(
                                mcal::reg::syscon_wdtoscctrl,
                                (freqsel << 5) | ((divsel >> 1) - 1));
}

void mcal::osc::set_wdt_clk_src(const std::uint32_t src, const std::uint32_t div)
{
  mcal::reg::reg_access_dynamic<std::uint32_t, std::uint32_t>::reg_set(mcal::reg::syscon_wdtclksel, src);
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, 
                               mcal::reg::syscon_wdtclkuen,
                               UINT32_C(0)>::reg_set();
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, 
                               mcal::reg::syscon_wdtclkuen,
                               UINT32_C(1)>::reg_set();

  mcal::reg::reg_access_dynamic<std::uint32_t, std::uint32_t>::reg_set(mcal::reg::syscon_wdtclkdiv, div);
}

std::uint32_t mcal::osc::get_wdt_osc_rate()
{
  std::uint32_t div = mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, 
                                                   mcal::reg::syscon_wdtoscctrl>::reg_get() & 0x1F;
  std::uint32_t clk = ((div >> 5) & 0xF);

  return wdt_osc_rate.begin()[clk] / ((div + 1) << 1);
}
