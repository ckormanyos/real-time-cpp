///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2014.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <algorithm>
#include <mcal_irq.h>
#include <os/os.h>
#include <os/os_task_control_block.h>

// The one (and only one) operating system task list.
const os::task_list_type& os::task_list()
{
  static const os::task_list_type the_task_list(OS_TASK_LIST);

  return the_task_list;
}

void os::start_os()
{
  // Initialize each task once.
  std::for_each(task_list().cbegin(),
                task_list().cend(),
                [](const task_control_block& the_tcb)
                {
                  the_tcb.initialize();
                });

  // Initialize the idle task.
  OS_IDLE_TASK_INIT();

  // Enter the endless loop of the multitasking scheduler.
  for(;;)
  {
    // Find the next ready task using a priority-based search algorithm.
    const task_list_type::const_iterator it_ready_task = std::find_if(task_list().cbegin(),
                                                                      task_list().cend(),
                                                                      [](const task_control_block& the_tcb) -> bool
                                                                      {
                                                                        return the_tcb.execute();
                                                                      });

    // If no ready-task was found, then service the idle task.
    if(it_ready_task == task_list().cend())
    {
      OS_IDLE_TASK_FUNC();
    }
  }
}

void os::set_event(const task_id_type task_id, const event_type& event_to_set)
{
  if(task_id < task_id_end)
  {
    // Get a pointer to the control block corresponding to
    // the task ID that has been supplied to this subroutine.
    task_list_type::const_iterator control_block_of_the_task_id = task_list().cbegin() + task_list_type::size_type(task_id);

    mcal::irq::disable_all();
    control_block_of_the_task_id->my_event |= event_to_set;
    mcal::irq::enable_all();
  }
}

void os::get_event(event_type& event_to_get)
{
  // Get the iterator of the control block of the running task.
  const os::task_list_type::const_iterator control_block_of_the_running_task = os::secure::os_get_running_task_iterator();

  if(control_block_of_the_running_task != os::task_list().cend())
  {
    mcal::irq::disable_all();
    const volatile event_type the_event = control_block_of_the_running_task->my_event;
    mcal::irq::enable_all();

    event_to_get = the_event;
  }
  else
  {
    event_to_get = event_type();
  }
}

void os::clear_event(const event_type& event_to_clear)
{
  // Get the iterator of the control block of the running task.
  const os::task_list_type::const_iterator control_block_of_the_running_task = os::secure::os_get_running_task_iterator();

  if(control_block_of_the_running_task != os::task_list().cend())
  {
    const volatile event_type event_clear_mask = static_cast<event_type>(~event_to_clear);

    mcal::irq::disable_all();
    control_block_of_the_running_task->my_event &= event_clear_mask;
    mcal::irq::enable_all();
  }
}
