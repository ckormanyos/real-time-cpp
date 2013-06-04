///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_port.h>
#include <util/monitor/util_single_pin_debug_monitor.h>

namespace
{
  typedef util::single_pin_debug_monitor<mcal::port::port_rdm_type> rdm_debug_monitor_type;

  rdm_debug_monitor_type rdm_debug_monitor;
}

namespace sys
{
  namespace rdm
  {
    void task_init();
    void task_func();
  }
}

void sys::rdm::task_init()
{
}

void sys::rdm::task_func()
{
  rdm_debug_monitor.driver_task();
  rdm_debug_monitor.protocol_task<std::uint16_t, 0U>();
}
