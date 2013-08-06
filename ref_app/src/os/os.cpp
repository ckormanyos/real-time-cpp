///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <algorithm>
#include <mcal_irq.h>
#include <os/os_task_control_block.h>

void os::start_os()
{
  // Initialize the idle task.
  OS_IDLE_TASK_INIT();

  // Initialize each task once.
  std::for_each(os::task_list.begin(),
                os::task_list.end(),
                [](const os::task_control_block& tcb)
                {
                  tcb.initialize();
                });

  for(;;)
  {
    // Find the next ready task using a priority-based search algorithm.
    const os::task_list_type::iterator it_ready_task
      = std::find_if(os::task_list.begin(),
                     os::task_list.end(),
                     [](os::task_control_block& tcb) -> bool
                     {
                       return tcb.execute();
                     });

    // If no ready-task was found, then service the idle task.
    if(it_ready_task == os::task_list.end())
    {
      // Verify that all of the tasks have checked in by setting
      // their appropriate bits in the task trace.
      os::task_control_block::task_index = os::task_control_block::task_index_type(os::task_list.size());

      const os::task_control_block::task_trace_type idle_trace( os::task_control_block::task_trace | os::task_control_block::task_trace_type(os::task_control_block::task_trace_type(1U) << std::uint_fast8_t(os::task_list.size())));
      const os::task_control_block::task_trace_type idle_mask (~os::task_control_block::task_trace_type((std::numeric_limits<os::task_control_block::task_trace_type>::max)() << std::uint_fast8_t(os::task_list.size() + 1U)));

      const bool my_trigger_condition = (idle_trace == idle_mask);

      // Service the idle task (also include the task trace information).
      OS_IDLE_TASK_FUNC(my_trigger_condition);

      if(my_trigger_condition)
      {
        // Reset the task trace value to zero.
        os::task_control_block::task_trace = os::task_control_block::task_trace_type(0U);
      }
    }
  }
}

void os::set_event(const os::task_id_type task_id, const os::event_type& event_to_set)
{
  if(task_id < os::task_id_end)
  {
    os::task_control_block* task_pointer = os::task_control_block::get_task_pointer();

    mcal::irq::disable_all();
    task_pointer->event |= event_to_set;
    mcal::irq::enable_all();
  }
}

void os::get_event(os::event_type& event_to_get)
{
  os::task_control_block* task_pointer = os::task_control_block::get_task_pointer();

  mcal::irq::disable_all();
  const os::event_type evt = task_pointer->event;
  mcal::irq::enable_all();

  event_to_get = evt;
}

void os::clear_event(const os::event_type& event_mask_to_clear)
{
  os::task_control_block* task_pointer = os::task_control_block::get_task_pointer();

  const os::event_type event_clear_value = os::event_type(~event_mask_to_clear);

  mcal::irq::disable_all();
  task_pointer->event &= event_clear_value;
  mcal::irq::enable_all();
}
