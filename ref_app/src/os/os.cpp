///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2015.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <algorithm>
#include <iterator>
#include <mcal_irq.h>
#include <os/os.h>
#include <os/os_task_control_block.h>

// The one (and only one) operating system task list.
os::task_list_type& os::task_list()
{
  static task_list_type the_task_list(OS_TASK_LIST);

  return the_task_list;
}

void os::start_os()
{
  // Initialize each task once (and only once) before the task scheduling begins.
  std::for_each(task_list().cbegin(),
                task_list().cend(),
                [](const task_control_block& the_tcb)
                {
                  the_tcb.initialize();
                });

  // Initialize the idle task.
  OS_IDLE_TASK_INIT();

  // Enter the endless loop of the multitasking scheduler...
  // ...and never return.
  for(;;)
  {
    // Find the next ready task using a priority-based search algorithm.
    // Use a constant time-point based on the timer mark of now.
    // In this way, each task in the loop will be checked for being
    // ready using the same time-point.

    const os::tick_type timepoint_of_ckeck_ready = os::timer_type::get_mark();

    const task_list_type::iterator it_ready_task =
      std::find_if(task_list().begin(),
                   task_list().end(),
                   [&timepoint_of_ckeck_ready](task_control_block& the_tcb) -> bool
                   {
                     return the_tcb.execute(timepoint_of_ckeck_ready);
                   });

    // If no ready-task was found, then service the idle task.
    if(it_ready_task == task_list().end())
    {
      OS_IDLE_TASK_FUNC();
    }
  }
}

bool os::set_event(const task_id_type task_id, const event_type& event_to_set)
{
  if(task_id < task_id_end)
  {
    // Get the iterator of the control block corresponding to
    // the task id that has been supplied to this subroutine.
    task_list_type::iterator iterator_of_the_task_id = task_list().begin() + task_list_type::size_type(task_id);

    // Set the event of the corresponding task.
    mcal::irq::disable_all();
    iterator_of_the_task_id->my_event |= event_to_set;
    mcal::irq::enable_all();

    return true;
  }
  else
  {
    return false;
  }
}

void os::get_event(event_type& event_to_get)
{
  // Get the iterator of the control block of the running task.
  const task_list_type::iterator running_task_iterator = secure::get_running_task_iterator();

  if(running_task_iterator != task_list().cend())
  {
    // Get the event of the running task.
    mcal::irq::disable_all();
    const volatile event_type the_event = running_task_iterator->my_event;
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
  const task_list_type::iterator running_task_iterator = secure::get_running_task_iterator();

  if(running_task_iterator != task_list().cend())
  {
    const volatile event_type event_clear_mask(~event_to_clear);

    // Clear the event of the running task.
    mcal::irq::disable_all();
    running_task_iterator->my_event &= event_clear_mask;
    mcal::irq::enable_all();
  }
}
