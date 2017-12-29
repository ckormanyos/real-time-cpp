///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_wdg.h>

namespace sys
{
  namespace idle
  {
    void task_init();
    void task_func();
  }
}

void sys::idle::task_init() { }

void sys::idle::task_func()
{
  // Service the watchdog.
  mcal::wdg::secure::trigger();
}
