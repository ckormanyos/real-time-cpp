///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2015.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <os/os_task_control_block.h>

namespace
{
  os::task_control_block::index_type& os_task_global_index()
  {
    static os::task_control_block::index_type the_index;

    return the_index;
  }
}

os::task_control_block::task_control_block(const function_type init,
                                           const function_type func,
                                           const tick_type cycle,
                                           const tick_type offset) : my_init (init),
                                                                     my_func (func),
                                                                     my_cycle(cycle),
                                                                     my_timer(offset),
                                                                     my_event(os::event_type(0U)),
                                                                     my_index(os_task_global_index())
{
  ++os_task_global_index();
}

os::task_control_block::task_control_block(const task_control_block& other_tcb) : my_init (other_tcb.my_init),
                                                                                  my_func (other_tcb.my_func),
                                                                                  my_cycle(other_tcb.my_cycle),
                                                                                  my_timer(other_tcb.my_timer),
                                                                                  my_event(other_tcb.my_event),
                                                                                  my_index(other_tcb.my_index)
{
}

os::task_control_block::~task_control_block()
{
}

void os::task_control_block::initialize() const
{
  my_init();
}

bool os::task_control_block::execute(const os::tick_type& timepoint_of_ckeck_ready)
{
  // Check for a task event.
  const bool task_does_have_event = (my_event != event_type(0U));

  if(task_does_have_event)
  {
    // Set the global task index equal to the index of the running task.
    os_task_global_index() = my_index;

    // Call the task function because of an event.
    my_func();
  }

  // Check for a task timeout.
  const bool task_does_have_timeout = (   (my_cycle != os::tick_type(0U))
                                       &&  my_timer.timeout_of_specific_timepoint(timepoint_of_ckeck_ready));

  if(task_does_have_timeout)
  {
    // Increment the task's interval timer with the task cycle.
    my_timer.start_interval(my_cycle);

    // Set the global task index equal to the index of the running task.
    os_task_global_index() = my_index;

    // Call the task function because of a timer timeout.
    my_func();
  }

  return (task_does_have_event || task_does_have_timeout);
}

os::task_list_type::iterator os::secure::get_running_task_iterator()
{
  // Return the iterator of the running task. If no task is running
  // (for example when the idle task is running), then the iterator
  // of the end of the task list is returned.

  const auto this_task_index = static_cast<os::task_list_type::size_type>(os_task_global_index());

  return ((this_task_index < os::task_list().size()) ? (os::task_list().begin() + this_task_index)
                                                     :  os::task_list().end());
}
