///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <array>
#include <algorithm>

#include <mcal_gpt.h>
#include <os/os.h>
#include <os/os_cfg.h>
#include <util/utility/util_time.h>

namespace os
{
  class task_control_block
  {
  public:
    typedef void (*function_type)();

    typedef util::timer<mcal::gpt::value_type> timer_type;
    typedef timer_type::tick_type              tick_type;

    task_control_block(const function_type i,
                       const function_type f,
                       const tick_type c,
                       const tick_type o = static_cast<tick_type>(0U)) : init (i),
                                                                         func (f),
                                                                         cycle(c),
                                                                         timer(o) { }

    task_control_block(const task_control_block& tcb);

    ~task_control_block() { }

    void initialize() const { init(); }

    bool execute()
    {
      if(timer.timeout())
      {
        // Increment the task's interval timer with the task cycle.
        timer.start_interval(cycle);

        // Call the task.
        func();

        return true;
      }
      else
      {
        return false;
      }

    }

  private:
    const function_type init;
    const function_type func;
    const tick_type     cycle;
          timer_type    timer;

    task_control_block();
    const task_control_block& operator=(const task_control_block&);
  };

  typedef std::array<task_control_block, OS_TASK_COUNT> task_list_type;

  task_list_type task_list = OS_TASK_LIST;
}

void os::schedule()
{
  // Initialize the idle task.
  os::idle_task_init();

  // Initialize each task.
  std::for_each(os::task_list.begin(),
                os::task_list.end(),
                [](const os::task_control_block& tcb)
                {
                  tcb.initialize();
                });

  for(;;)
  {
    // Find the next ready task using a priority-based find algorithm.
    const task_list_type::const_iterator it_task = std::find_if(os::task_list.begin(),
                                                                os::task_list.end(),
                                                                [](os::task_control_block& tcb) -> bool
                                                                {
                                                                  return tcb.execute();
                                                                });

    if(os::task_list.end() == it_task)
    {
      // If no ready-task was found, then service the idle task.
      os::idle_task_func();
    }
  }
}

