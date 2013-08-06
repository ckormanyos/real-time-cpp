#include <os/os_task_control_block.h>

namespace os
{
  task_list_type task_list = OS_TASK_LIST;
}

os::task_control_block::task_index_type os::task_control_block::task_index;
os::task_control_block::task_trace_type os::task_control_block::task_trace;

os::task_control_block::task_control_block(const function_type i,
                                           const function_type f,
                                           const tick_type c,
                                           const tick_type o) : init    (i),
                                                                func    (f),
                                                                cycle   (c),
                                                                timer   (o),
                                                                event   (os::event_type(0U)),
                                                                my_index(task_index)
{
  ++task_index;
}

bool os::task_control_block::execute()
{
  const bool has_event   = (event != event_type(0U));
  const bool has_timeout = timer.timeout();

  const bool task_is_ready = (has_event || has_timeout);

  if(task_is_ready)
  {
    task_index  = my_index;
    task_trace |= task_trace_type(task_trace_type(1U) << my_index);

    if(has_event)
    {
      // Call the task because of an event.
      func();
    }

    if(has_timeout)
    {
      // Increment the task's interval timer with the task cycle.
      timer.start_interval(cycle);

      // Call the task because of a timer timeout.
      func();
    }
  }

  return task_is_ready;
}

os::task_control_block* os::task_control_block::get_task_pointer()
{
  return &task_list[os::task_list_type::size_type(task_index)];
}

