///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _MCAL_WDG_2010_04_10_H_
  #define _MCAL_WDG_2010_04_10_H_

  extern "C" void __my_startup();

  namespace sys { namespace idle { void task_func(const bool); } }

  namespace mcal
  {
    namespace wdg
    {
      typedef void config_type;

      void init(const config_type*);

      class secure
      {
      private:
        static void trigger();

        friend void sys::idle::task_func(const bool);
        friend void ::__my_startup();
      };
    }
  }

#endif // _MCAL_WDG_2010_04_10_H_
