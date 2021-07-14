///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019 - 2021.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef SYS_IDLE_MILLER_RABIN_2020_06_01_H_
  #define SYS_IDLE_MILLER_RABIN_2020_06_01_H_

  #include <cstdint>

  namespace sys
  {
    namespace idle
    {
      void miller_rabin_init();
      void miller_rabin_run ();

      extern bool miller_rabin_result_is_ok;

      inline bool miller_rabin_get_result_is_ok() { return miller_rabin_result_is_ok; }
    }
  }

#endif // SYS_IDLE_PI_SPIGOT_H_2020_04_17_H_
