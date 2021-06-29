///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_cpu.h>
#include <sys/idle/sys_idle_pi_spigot.h>

namespace app
{
  namespace benchmark
  {
    void task_init();
    void task_func();
  }
}

void app::benchmark::task_init()
{
}

void app::benchmark::task_func()
{
  const bool result_is_ok = sys::idle::pi_spigot_get_result();

  if(result_is_ok == false)
  {
    for(;;)
    {
      mcal::cpu::nop();
    }
  }
}
