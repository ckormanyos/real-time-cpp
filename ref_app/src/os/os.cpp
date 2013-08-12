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
  using os::task_control_block;

  // Initialize each task once.
  std::for_each(task_list.begin(),
                task_list.end(),
                [](const task_control_block& tcb)
                {
                  tcb.initialize();
                });

  // Initialize the idle task.
  OS_IDLE_TASK_INIT();

  // Enter the endless loop of the multitasking scheduler.
  for(;;)
  {
    // Find the next ready task using a priority-based search algorithm.
    const task_list_type::iterator it_ready_task = std::find_if(task_list.begin(),
                                                                task_list.end(),
                                                                [](task_control_block& tcb) -> bool
                                                                {
                                                                  return tcb.execute();
                                                                });

    // If no ready-task was found, then service the idle task.
    if(it_ready_task == task_list.end())
    {
      // Set the task index to one higher than the index of the
      // highest task in order to signify the idle task.
      task_control_block::task_global_index = task_control_block::task_index_type(task_list.size());

      // Set the bit in the task trace belonging to the idle task.
      task_control_block::task_global_trace |= task_control_block::task_trace_type(task_control_block::task_trace_type(1U) << std::uint_fast8_t(task_control_block::task_global_index));

      // Check if all of the tasks have, indeed, checked in by setting
      // their appropriate bit in the task trace. This should be the case,
      // and it means that the task trace will have a set bit corresponding
      // to each task and also the idle task.
      const task_control_block::task_trace_type idle_mask (~task_control_block::task_trace_type((std::numeric_limits<task_control_block::task_trace_type>::max)() << std::uint_fast8_t(task_list.size() + 1U)));

      // Service the idle task, and also include the task trace information.
      if(task_control_block::task_global_trace == idle_mask)
      {
        OS_IDLE_TASK_FUNC(true);

        // Reset the task trace value to zero.
        task_control_block::task_global_trace = task_control_block::task_trace_type(0U);
      }
      else
      {
        OS_IDLE_TASK_FUNC(false);
      }
    }
  }
}

void os::set_event(const os::task_id_type task_id, const os::event_type& event_to_set)
{
  if(task_id < os::task_id_end)
  {
    using os::task_control_block;

    task_control_block* my_task_pointer = task_control_block::get_task_pointer();

    mcal::irq::disable_all();
    my_task_pointer->event |= event_to_set;
    mcal::irq::enable_all();
  }
}

void os::get_event(os::event_type& event_to_get)
{
  using os::task_control_block;

  task_control_block* my_task_pointer = task_control_block::get_task_pointer();

  mcal::irq::disable_all();
  const event_type my_event = my_task_pointer->event;
  mcal::irq::enable_all();

  event_to_get = my_event;
}

void os::clear_event(const os::event_type& event_mask_to_clear)
{
  using os::task_control_block;

  task_control_block* my_task_pointer = task_control_block::get_task_pointer();

  const event_type my_event_clear_value = event_type(~event_mask_to_clear);

  mcal::irq::disable_all();
  my_task_pointer->event &= my_event_clear_value;
  mcal::irq::enable_all();
}
