///////////////////////////////////////////////////////////////////////////////
//  Copyright Joel Winarske 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_CONFIG_2019_06_25_H_
  #define MCAL_CONFIG_2019_06_25_H_

  #include <cstdint>
  #include <mcal_osc.h>

  namespace mcal
  {
    namespace config
    {
      // PLL configuration.
      constexpr std::uint32_t fclkin       = UINT32_C(12000000); // Crystal Oscillator
      constexpr std::uint32_t syspll_m     = UINT32_C(4);
      constexpr std::uint32_t syspll_p     = UINT32_C(2);
      constexpr std::uint32_t fclkout      = fclkin * syspll_m;
      constexpr std::uint32_t fcco         = fclkout * 2 * syspll_p;

      static_assert(fclkout <  UINT32_C(100000000), "System PLL FCLKOUT cannot exceed 100MHz");
      static_assert(   fcco >= UINT32_C(156000000), "System PLL FCCO < 156MHz");
      static_assert(   fcco <= UINT32_C(320000000), "System PLL FCCO > 320MHz");

      // System AHB clock divider.
      constexpr std::uint32_t sysahbclkdiv = UINT32_C(1);

      // System Tick configuration.
      constexpr std::uint32_t systick_hz   = UINT32_C(10000);
      constexpr std::uint32_t systick_inc  = UINT32_C(100); // in microseconds

      // Watchdog Timer configuration.
      constexpr std::uint32_t wdt_osc_freq = mcal::osc::wdtlfo_osc_1_05;
      constexpr std::uint32_t wdt_osc_div  = UINT32_C(20);
      constexpr std::uint32_t wdt_clk_div  = UINT32_C(1);
      constexpr std::uint32_t wdt_hz       = UINT32_C(2);   // ~2 Seconds
    }
  }

#endif // MCAL_CONFIG_2019_06_25_H_
