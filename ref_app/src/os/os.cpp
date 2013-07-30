///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <algorithm>
#include <mcal_irq.h>
#include <os/os_detail.h>

void os::schedule()
{
  // Initialize the idle task.
  OS_IDLE_TASK_INIT();

  // Initialize each task.
  std::for_each(os::detail::task_list.begin(),
                os::detail::task_list.end(),
                [](const os::detail::task_control_block& tcb)
                {
                  tcb.initialize();
                });

  for(;;)
  {
    // Find the next ready task using a priority-based find algorithm.
    const os::detail::task_list_type::iterator it_ready_task
      = std::find_if(os::detail::task_list.begin(),
                     os::detail::task_list.end(),
                     [](os::detail::task_control_block& tcb) -> bool
                     {
                       return tcb.execute();
                     });

    if(it_ready_task == os::detail::task_list.end())
    {
      os::detail::task_control_block::ready_task_index
        = os::detail::task_control_block::task_index_type(os::detail::task_list.size());

      // If no ready-task was found, then service the idle task.
      OS_IDLE_TASK_FUNC();
    }
  }
}

void os::set_event(const os::task_id_type task_id, const os::event_type& event_to_set)
{
  if(task_id < os::task_id_end)
  {
    os::detail::task_list_type::iterator task_iterator
      = (os::detail::task_list.begin() + os::detail::task_list_type::size_type(task_id));

    mcal::irq::disable_all();
    task_iterator->event |= event_to_set;
    mcal::irq::enable_all();
  }
}

void os::get_event(os::event_type& event_to_get)
{
  os::detail::task_list_type::iterator task_iterator
    = (os::detail::task_list.begin() + os::detail::task_list_type::size_type(os::detail::task_control_block::ready_task_index));

  mcal::irq::disable_all();
  const os::event_type evt = task_iterator->event;
  mcal::irq::enable_all();

  event_to_get = evt;
}

void os::clr_event(const os::event_type& event_mask_to_clear)
{
  os::detail::task_list_type::iterator task_iterator
    = (os::detail::task_list.begin() + os::detail::task_list_type::size_type(os::detail::task_control_block::ready_task_index));

  const os::event_type event_clear_value = os::event_type(~event_mask_to_clear);

  mcal::irq::disable_all();
  task_iterator->event &= event_clear_value;
  mcal::irq::enable_all();
}
