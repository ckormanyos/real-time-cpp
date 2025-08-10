///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2025.
//  Copyright Joel Winarske 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_WDG_2010_04_10_H
  #define MCAL_WDG_2010_04_10_H

  #include <cstdint>

  namespace mcal
  {
    namespace wdg
    {
      typedef void config_type;

      void init(const config_type*);

      constexpr std::uint32_t wdmod_wden_bpos      = UINT32_C(0);
      constexpr std::uint32_t wdmod_wdreset_bpos   = UINT32_C(1);
      constexpr std::uint32_t wdmod_wdtof_bpos     = UINT32_C(2);
      constexpr std::uint32_t wdmod_wdint_bpos     = UINT32_C(3);
      constexpr std::uint32_t wdmod_wdprotect_bpos = UINT32_C(3);

      constexpr std::uint32_t wdt_feed_seq_1       = UINT32_C(0xAA);
      constexpr std::uint32_t wdt_feed_seq_2       = UINT32_C(0x55);

      struct secure final
      {
        static void trigger();
      };
    }
  }

#endif // MCAL_WDG_2010_04_10_H
