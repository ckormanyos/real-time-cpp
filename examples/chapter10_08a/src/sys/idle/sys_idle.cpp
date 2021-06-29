///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_wdg.h>
#include <mcal_led.h>
#include <sys/idle/sys_idle_pi_spigot.h>

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
  if(pi_spigot_get_result() == false)
  {
    for(;;)
    {
      mcal::led::led0().toggle();

      mcal::wdg::secure::trigger();
    }
  }
  else
  {
    sys::idle::pi_spigot_run();
    mcal::wdg::secure::trigger();
    sys::idle::pi_spigot_run();
    mcal::wdg::secure::trigger();
  }
}
