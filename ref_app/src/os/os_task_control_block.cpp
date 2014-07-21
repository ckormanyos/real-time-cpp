#include <os/os_task_control_block.h>

namespace
{
  os::task_control_block::index_type& os_task_global_index()
  {
    static os::task_control_block::index_type the_index;

    return the_index;
  }
}

os::task_control_block::task_control_block(const function_type i,
                                           const function_type f,
                                           const tick_type c,
                                           const tick_type o) : init (i),
                                                                func (f),
                                                                cycle(c),
                                                                timer(o),
                                                                event(os::event_type(0U)),
                                                                index(os_task_global_index())
{
  ++os_task_global_index();
}

bool os::task_control_block::execute() const
{
  // Check for a task event.
  const bool task_does_have_event = (event != event_type(0U));

  if(task_does_have_event)
  {
    // Set the global task index equal to the index of the running task.
    os_task_global_index() = index;

    // Call the task function because of an event.
    func();
  }

  // Check for a task timeout.
  const bool task_does_have_timeout = timer.timeout();

  if(task_does_have_timeout)
  {
    // Increment the task's interval timer with the task cycle.
    timer.start_interval(cycle);

    // Set the global task index equal to the index of the running task.
    os_task_global_index() = index;

    // Call the task function because of a timer timeout.
    func();
  }

  const bool task_is_ready = (task_does_have_event || task_does_have_timeout);

  return task_is_ready;
}

os::task_list_type::iterator os_get_running_task_iterator();

os::task_list_type::iterator os_get_running_task_iterator()
{
  // Return the iterator of the running task. If no task is running
  // (for example when the idle task is running), then the iterator
  // of the end of the task list is returned.

  const os::task_list_type::size_type this_task_index = static_cast<os::task_list_type::size_type>(os_task_global_index());

  return ((this_task_index < os::task_list().size()) ? (os::task_list().begin() + this_task_index)
                                                     :  os::task_list().end());
}
