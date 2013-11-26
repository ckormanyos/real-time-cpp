///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_safety_dram.h>
#include <mcal_wdg.h>

namespace sys
{
  namespace idle
  {
    void task_init();
    void task_func(const bool do_trigger);
  }
}

namespace
{
  mcal::safety::dram_memory_refresh_type sys_idle_dram_refresh(mcal::safety::dram_memory_block_list);
}

void sys::idle::task_init()
{
}

void sys::idle::task_func(const bool do_trigger)
{
  sys_idle_dram_refresh.service();

  if(do_trigger)
  {
    mcal::wdg::trigger();
  }
}
