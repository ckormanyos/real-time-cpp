///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _OS_CFG_2011_10_20_H_
  #define _OS_CFG_2011_10_20_H_

  // Declare and define the task initialization and the task function of the idle process.
  namespace sys { namespace idle { void task_init(); void task_func(); } }

  // Define symbols for the task initialization and the task function of the idle process.
  #define OS_IDLE_TASK_INIT() sys::idle::task_init()
  #define OS_IDLE_TASK_FUNC() sys::idle::task_func()

  // Declare all of the task initializations and the task functions.
  namespace app { namespace led { void task_init(); void task_func(); } }
  namespace sys { namespace mon { void task_init(); void task_func(); } }

  // Enumerate the task IDs. Note that the order in this list must
  // be identical with the order of the tasks in the task list below.
  namespace os
  {
    typedef enum enum_task_id
    {
      task_id_app_led,
      task_id_sys_mon,
      task_id_end
    }
    task_id_type;
  }

  // Configure the operating system tasks.

  #define OS_TASK_COUNT 2U

  #define OS_TASK_LIST                                                                           \
  {                                                                                              \
    {                                                                                            \
      os::task_control_block(app::led::task_init,                                                \
                             app::led::task_func,                                                \
                             os::timer_type::microseconds(UINT32_C(  2000)),                     \
                             os::timer_type::microseconds(UINT32_C(   417))),                    \
      os::task_control_block(sys::mon::task_init,                                                \
                             sys::mon::task_func,                                                \
                             os::timer_type::microseconds(UINT32_C(  4000)),                     \
                             os::timer_type::microseconds(UINT32_C(   513))),                    \
    }                                                                                            \
  }

#endif // _OS_CFG_2011_10_20_H_
