///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2020.
//  Copyright Joel Winarske 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_WDG_2010_04_10_H_
  #define MCAL_WDG_2010_04_10_H_

  #include <cstdint>

  extern "C" void __my_startup() __attribute__((section(".startup"), used, noinline));

  namespace sys { namespace idle { void task_func(); } }

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

      class secure final
      {
        static void trigger();

        friend void __wdt_handler() __attribute__((interrupt));
        friend void ::sys::idle::task_func();
        friend void ::__my_startup();
      };
    }
  }

#endif // MCAL_WDG_2010_04_10_H_
