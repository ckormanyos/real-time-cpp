///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _MCAL_WDG_2010_04_10_H_
  #define _MCAL_WDG_2010_04_10_H_

  namespace sys { namespace idle { void task_func(const bool); } }

  namespace mcal
  {
    namespace wdg
    {
      typedef void config_type;

      inline void init(const config_type*) { }

      class secure
      {
      private:
        static void trigger();

        friend void ::sys::idle::task_func(const bool);
      };
    }
  }

#endif // _MCAL_WDG_2010_04_10_H_
