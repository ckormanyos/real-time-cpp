///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2020.
//  Copyright Joel Winarske 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdint>
#include <mcal_wdg.h>
#include <mcal_reg.h>
#include <mcal_irq.h>
#include <mcal_osc.h>
#include <mcal_config.h>

extern "C" void __wdt_handler() __attribute__((interrupt));

extern "C" void __wdt_handler()
{
  if(mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, 
                                  mcal::reg::wdt_mod,
                                  mcal::wdg::wdmod_wdtof_bpos>::bit_get()) {
    do {
      mcal::reg::reg_access_static<std::uint32_t, std::uint32_t,
                                   mcal::reg::wdt_mod,
                                   mcal::wdg::wdmod_wdtof_bpos>::bit_clr();

    } while (mcal::reg::reg_access_static<std::uint32_t, std::uint32_t,
                                          mcal::reg::wdt_mod,
                                          mcal::wdg::wdmod_wdtof_bpos>::bit_get());

    // Restart the watchdog.
    mcal::reg::reg_access_static<std::uint32_t, std::uint32_t,
                                 mcal::reg::wdt_mod,
                                 mcal::wdg::wdmod_wden_bpos>::bit_set();

    // Feed it.
    mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, 
                                 mcal::reg::wdt_feed,
                                 mcal::wdg::wdt_feed_seq_1>::reg_set();

    mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, 
                                 mcal::reg::wdt_feed,
                                 mcal::wdg::wdt_feed_seq_2>::reg_set();
  }
}

void mcal::wdg::init(const config_type*)
{

  // power on the oscillator.
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, 
                               mcal::reg::syscon_sysahbclkctrl,
                               mcal::reg::syscon_clock_wdg>::reg_or();

  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, 
                               mcal::reg::wdt_mod,
                               UINT32_C(0)>::reg_set();

  // Setup WDT clocking.

  // power off wdtosc.
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t,
                               mcal::reg::syscon_pdruncfg,
                               mcal::reg::syscon_pdruncfg_wdtosc_pd_bpos>::bit_set();

  // setup osc
  mcal::osc::set_wdt_osc(mcal::config::wdt_osc_freq, mcal::config::wdt_osc_div);

  // power on wdtosc.
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t,
                               mcal::reg::syscon_pdruncfg,
                               mcal::reg::syscon_pdruncfg_wdtosc_pd_bpos>::bit_clr();

  // set watchdog OSC for WDT clock source.
  mcal::osc::set_wdt_clk_src(mcal::osc::wdtclksrc_wdtosc, mcal::config::wdt_clk_div);


  // Set watchdog feed time constant.
  uint32_t wdt_freq = mcal::osc::get_wdt_osc_rate() / mcal::config::wdt_hz;

  // Set Timer Constant.
  mcal::reg::reg_access_dynamic<std::uint32_t, std::uint32_t>::reg_set(mcal::reg::wdt_tc, wdt_freq);


	// Clear watchdog peripheral interrupt.
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t,
                               mcal::reg::wdt_mod,
                               wdmod_wdtof_bpos>::bit_clr();

	// Clear pending watchdog interrupt.
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t,
                               mcal::reg::nvic_icpr,
                               (1 << mcal::irq::wdt_irqn)>::reg_set();

  // Set enable watchdog interrupt.
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t,
                               mcal::reg::nvic_iser,
                               (1 << mcal::irq::wdt_irqn)>::reg_set();

	// Start watchdog.
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t,
                               mcal::reg::wdt_mod,
                               wdmod_wden_bpos>::bit_set();

  // Feed.
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, 
                               mcal::reg::wdt_feed,
                               mcal::wdg::wdt_feed_seq_1>::reg_set();

  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, 
                               mcal::reg::wdt_feed,
                               mcal::wdg::wdt_feed_seq_2>::reg_set();
}

void mcal::wdg::secure::trigger()
{
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, 
                               mcal::reg::wdt_feed,
                               mcal::wdg::wdt_feed_seq_1>::reg_set();

  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, 
                               mcal::reg::wdt_feed,
                               mcal::wdg::wdt_feed_seq_2>::reg_set();
}
