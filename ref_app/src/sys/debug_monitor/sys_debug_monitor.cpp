///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_port.h>
#include <mcal_debug_monitor.h>
#include <util/debug_monitor/util_single_pin_debug_monitor.h>

namespace sys
{
  namespace debug_monitor
  {
    void task_init();
    void task_func();
  }
}

/*
namespace
{
  typedef util::single_pin_debug_monitor<mcal::debug_monitor::debug_monitor_port_type> debug_monitor_type;

  debug_monitor_type the_debug_monitor;

  std::uint_least8_t protocol_prescaler;
}
*/

void sys::debug_monitor::task_init()
{
}

void sys::debug_monitor::task_func()
{
/*
  the_debug_monitor.driver_task();

  const bool run_the_protocol_task = (static_cast<std::uint_fast8_t>(protocol_prescaler % 16U) == static_cast<std::uint_fast8_t>(0U));

  if(run_the_protocol_task)
  {
    the_debug_monitor.protocol_task<mcal::debug_monitor::address_type,
                                    mcal::debug_monitor::address_offset>();
  }

  ++protocol_prescaler;
*/
}
