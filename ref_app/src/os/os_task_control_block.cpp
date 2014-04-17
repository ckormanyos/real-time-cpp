#include <os/os_task_control_block.h>

os::task_control_block::index_type os::task_control_block::task_global_index;

os::task_control_block::task_control_block(const function_type i,
                                           const function_type f,
                                           const tick_type c,
                                           const tick_type o) : init (i),
                                                                func (f),
                                                                cycle(c),
                                                                timer(o),
                                                                event(os::event_type(0U)),
                                                                index(task_global_index)
{
  ++task_global_index;
}

os::task_control_block::task_control_block(const task_control_block& tcb) : init (tcb.init),
                                                                            func (tcb.func),
                                                                            cycle(tcb.cycle),
                                                                            timer(tcb.timer),
                                                                            event(tcb.event),
                                                                            index(tcb.index)
{
}

bool os::task_control_block::execute() const
{
  // Check for a task event.
  const bool task_does_have_event = (event != event_type(0U));

  if(task_does_have_event)
  {
    // Set the global task index to the index of the running task.
    task_global_index = index;

    // Call the task function because of an event.
    func();
  }

  // Check for a task timeout.
  const bool task_does_have_timeout = timer.timeout();

  if(task_does_have_timeout)
  {
    // Increment the task's interval timer with the task cycle.
    timer.start_interval(cycle);

    // Set the global task index to the index of the running task.
    task_global_index = index;

    // Call the task function because of a timer timeout.
    func();
  }

  const bool task_is_ready = (task_does_have_event || task_does_have_timeout);

  return task_is_ready;
}

os::task_control_block* os::task_control_block::get_running_task_pointer()
{
  // Return a pointer to the index of the task that is running.
  // If no task is running, for example when the idle task is
  // running, then the null pointer is returned.

  const task_list_type::size_type this_task_index = static_cast<task_list_type::size_type>(task_global_index);

  return ((this_task_index < task_list.size()) ? (task_list.data() + this_task_index)
                                               : nullptr);
}
