#include <os/os_detail.h>

namespace os
{
  namespace detail
  {
    task_list_type task_list = OS_TASK_LIST;
  }
}

os::detail::task_control_block::task_index_type os::detail::task_control_block::ready_task_index;

os::detail::task_control_block::task_control_block(const function_type i,
                                                   const function_type f,
                                                   const tick_type c,
                                                   const tick_type o) : init    (i),
                                                                        func    (f),
                                                                        cycle   (c),
                                                                        timer   (o),
                                                                        event   (os::event_type(0U)),
                                                                        my_index(ready_task_index)
{
  ++ready_task_index;
}
