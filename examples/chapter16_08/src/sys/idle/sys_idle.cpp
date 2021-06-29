///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2021.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_wdg.h>
#include <mcal_led.h>
#include <sys/idle/sys_idle_miller_rabin.h>

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
  mcal::wdg::secure::trigger();

  ((miller_rabin_get_result_is_ok() == false) ? mcal::led::led0().toggle()
                                              : sys::idle::miller_rabin_run());
}
