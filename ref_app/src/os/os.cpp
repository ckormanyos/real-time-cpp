///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <algorithm>
#include <mcal_irq.h>
#include <os/os_task_control_block.h>


// The one (and only one) operating system task list.
os::task_list_type os::task_list = OS_TASK_LIST;


void os::start_os()
{
  // Initialize the idle task.
  OS_IDLE_TASK_INIT();

  // Call the idle task and trigger the watchdog at OS begin.
  OS_IDLE_TASK_FUNC();

  // Initialize each task once.
  std::for_each(task_list.cbegin(),
                task_list.cend(),
                [](const task_control_block& tcb)
                {
                  tcb.initialize();
                });

  // Enter the endless loop of the multitasking scheduler.
  for(;;)
  {
    // Find the next ready task using a priority-based search algorithm.
    const task_list_type::const_iterator it_ready_task = std::find_if(task_list.cbegin(),
                                                                      task_list.cend(),
                                                                      [](const task_control_block& tcb) -> bool
                                                                      {
                                                                        return tcb.execute();
                                                                      });

    // If no ready-task was found, then service the idle task.
    if(it_ready_task == task_list.end())
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
    task_control_block* control_block_of_the_task_id = task_list.data() + task_list_type::size_type(task_id);

    mcal::irq::disable_all();
    control_block_of_the_task_id->event |= event_to_set;
    mcal::irq::enable_all();
  }
}

void os::get_event(event_type& event_to_get)
{
  // Get a pointer to the control block of the task that is running.
  const task_control_block* control_block_of_the_running_task = task_control_block::get_running_task_pointer();

  if(control_block_of_the_running_task != nullptr)
  {
    mcal::irq::disable_all();
    const event_type my_event = control_block_of_the_running_task->event;
    mcal::irq::enable_all();

    event_to_get = my_event;
  }
  else
  {
    event_to_get = event_type(0U);
  }
}

void os::clear_event(const event_type& event_mask_to_clear)
{
  // Get a pointer to the control block of the task that is running.
  task_control_block* control_block_of_the_running_task = task_control_block::get_running_task_pointer();

  if(control_block_of_the_running_task != nullptr)
  {
    mcal::irq::disable_all();
    control_block_of_the_running_task->event &= event_type(~event_mask_to_clear);
    mcal::irq::enable_all();
  }
}
