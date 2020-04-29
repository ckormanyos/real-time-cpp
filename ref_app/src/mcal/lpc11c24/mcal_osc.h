///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2020.
//  Copyright Joel Winarske 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_OSC_2011_10_20_H_
  #define MCAL_OSC_2011_10_20_H_

  #include <cstdint>
  #include <initializer_list>

  namespace mcal
  {
    namespace osc
    {
      typedef void config_type;
      void init(const config_type*);

      std::uint32_t get_sys_clk_rate(void);
      std::uint32_t get_sys_pllout_clk_rate(void);

      void set_wdt_osc(std::uint32_t freqsel, std::uint32_t divsel);
      void set_wdt_clk_src(std::uint32_t src, std::uint32_t div);
      std::uint32_t get_wdt_osc_rate(void);

      // Main Clock Source Select.
      constexpr std::uint32_t syscon_mainclksel_irc    = UINT32_C(0);
      constexpr std::uint32_t syscon_mainclksel_pllin  = UINT32_C(1);
      constexpr std::uint32_t syscon_mainclksel_wdtosc = UINT32_C(2);
      constexpr std::uint32_t syscon_mainclksel_pllout = UINT32_C(3);

      // PLL Clock Sources.
      constexpr std::uint32_t syscon_pllclksrc_irc     = UINT32_C(0);
      constexpr std::uint32_t syscon_pllclksrc_mainosc = UINT32_C(1);

      // Watchdog.
      constexpr std::uint32_t wdtlfo_osc_0_60      = UINT32_C(1);  // 0.6 MHz watchdog/LFO rate
      constexpr std::uint32_t wdtlfo_osc_1_05      = UINT32_C(2);	// 1.05 MHz watchdog/LFO rate
      constexpr std::uint32_t wdtlfo_osc_1_40      = UINT32_C(3);	// 1.4 MHz watchdog/LFO rate
      constexpr std::uint32_t wdtlfo_osc_1_75      = UINT32_C(4);	// 1.75 MHz watchdog/LFO rate
      constexpr std::uint32_t wdtlfo_osc_2_10      = UINT32_C(5);	// 2.1 MHz watchdog/LFO rate
      constexpr std::uint32_t wdtlfo_osc_2_40      = UINT32_C(6);	// 2.4 MHz watchdog/LFO rate
      constexpr std::uint32_t wdtlfo_osc_2_70      = UINT32_C(7);	// 2.7 MHz watchdog/LFO rate
      constexpr std::uint32_t wdtlfo_osc_3_00      = UINT32_C(8);	// 3.0 MHz watchdog/LFO rate
      constexpr std::uint32_t wdtlfo_osc_3_25      = UINT32_C(9);	// 3.25 MHz watchdog/LFO rate
      constexpr std::uint32_t wdtlfo_osc_3_50      = UINT32_C(10);	// 3.5 MHz watchdog/LFO rate
      constexpr std::uint32_t wdtlfo_osc_3_75      = UINT32_C(11);	// 3.75 MHz watchdog/LFO rate
      constexpr std::uint32_t wdtlfo_osc_4_00      = UINT32_C(12);	// 4.0 MHz watchdog/LFO rate
      constexpr std::uint32_t wdtlfo_osc_4_20      = UINT32_C(13);	// 4.2 MHz watchdog/LFO rate
      constexpr std::uint32_t wdtlfo_osc_4_40      = UINT32_C(14);	// 4.4 MHz watchdog/LFO rate
      constexpr std::uint32_t wdtlfo_osc_4_60      = UINT32_C(15);	// 4.6 MHz watchdog/LFO rate

      constexpr std::uint32_t wdtclksrc_irc        = UINT32_C(0); // Internal oscillator
      constexpr std::uint32_t wdtclksrc_mainsysclk = UINT32_C(1); // Main system clock
      constexpr std::uint32_t wdtclksrc_wdtosc     = UINT32_C(2); // Watchdog oscillator

      constexpr std::initializer_list<std::uint32_t> wdt_osc_rate = {
        0,
        600000,  // wdtlfo_osc_0_60
        1050000, // wdtlfo_osc_1_05
        1400000, // wdtlfo_osc_1_40
        1750000, // wdtlfo_osc_1_75
        2100000, // wdtlfo_osc_2_10
        2400000, // wdtlfo_osc_2_40
        2700000, // wdtlfo_osc_2_70
        3000000, // wdtlfo_osc_3_00
        3250000, // wdtlfo_osc_3_25
        3500000, // wdtlfo_osc_3_50
        3750000, // wdtlfo_osc_3_75
        4000000, // wdtlfo_osc_4_00
        4200000, // wdtlfo_osc_4_20
        4400000, // wdtlfo_osc_4_40
        4600000  // wdtlfo_osc_4_60
      };

    }
  }

#endif // MCAL_OSC_2011_10_20_H_
