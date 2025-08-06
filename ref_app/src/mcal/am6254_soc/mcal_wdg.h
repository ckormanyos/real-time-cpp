///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_WDG_2010_04_10_H_
  #define MCAL_WDG_2010_04_10_H_

  namespace util { template<typename unsigned_tick_type> class timer; }

  namespace sys { namespace idle { auto task_func() -> void; } }

  namespace mcal
  {
    namespace wdg
    {
      using config_type = void;

      auto init(const config_type*) -> void;

      class secure final
      {
        static auto trigger() -> void;

        template<typename unsigned_tick_type>
        friend class util::timer;

        friend auto ::sys::idle::task_func() -> void;
      };
    }
  }

#endif // MCAL_WDG_2010_04_10_H_
