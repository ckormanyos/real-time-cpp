///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_WDT_2010_04_10_H
  #define MCAL_WDT_2010_04_10_H

  extern "C" void __my_startup() __attribute__((section(".startup"), used, noinline));

  namespace sys { namespace idle { auto task_func() -> void; } }

  namespace mcal
  {
    namespace wdg
    {
      using config_type = void;

      auto init(const config_type*) -> void;

      struct secure final
      {
      private:
        static auto trigger() -> void;

        friend auto ::sys::idle::task_func() -> void;
        friend auto ::__my_startup() -> void;
      };
    }
  }

#endif // MCAL_WDT_2010_04_10_H
