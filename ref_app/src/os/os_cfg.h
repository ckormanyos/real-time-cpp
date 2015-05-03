///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2014.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _OS_CFG_2011_10_20_H_
  #define _OS_CFG_2011_10_20_H_

  #include <os/os_debug_monitor_cfg.h>

  // Declare the task initialization and the task function of the idle process.
  namespace sys { namespace idle { void task_init(); void task_func(); } }

  // Define symbols for the task initialization and the task function of the idle process.
  #define OS_IDLE_TASK_INIT() sys::idle::task_init()
  #define OS_IDLE_TASK_FUNC() sys::idle::task_func()

  // Declare all of the task initializations and the task functions.
  namespace sys { namespace debug_monitor    { void task_init(); void task_func(); } }
  namespace app { namespace led              { void task_init(); void task_func(); } }
  namespace app { namespace benchmark        { void task_init(); void task_func(); } }
  namespace sys { namespace mon              { void task_init(); void task_func(); } }

  // Enumerate the task IDs. Note that the order in this list must
  // be identical with the order of the tasks in the task list below.
  namespace os
  {
    typedef enum enum_task_id
    {
      task_id_sys_debug_monitor,
      task_id_app_led,
      task_id_app_benchmark,
      task_id_sys_mon,
      task_id_end
    }
    task_id_type;
  }

  // Configure the operating system tasks.

  // Use prime numbers for offsets.
  // Use Wolfram's Alpha or Mathematica(R): Table[Prime[n], {n, 50, 4000, 100}]
  // to obtain:
  //   229,   863,  1583,  2357,  3181,  3989,  4831,  5693,  6571,  7499,
  //  8387,  9283, 10177, 11149, 12109, 13007, 13967, 14947, 15881, 16903,
  // 17891, 18899, 19891, 20897, 21841, 22817, 23827, 24877, 25913, 26891,
  // 27947, 28933, 30059, 31091, 32159, 33113, 34157, 35159, 36277, 37309

  #define OS_TASK_COUNT static_cast<std::size_t>(os::task_id_end)

  #define OS_TASK_LIST                                                                           \
  {                                                                                              \
    {                                                                                            \
      os::task_control_block(sys::debug_monitor::task_init,                                      \
                             sys::debug_monitor::task_func,                                      \
                             os::timer_type::microseconds(os::debug_monitor::task_poll_time()),  \
                             os::timer_type::microseconds(UINT32_C(     0))),                    \
      os::task_control_block(app::led::task_init,                                                \
                             app::led::task_func,                                                \
                             os::timer_type::microseconds(UINT32_C(  2000)),                     \
                             os::timer_type::microseconds(UINT32_C(   229))),                    \
      os::task_control_block(app::benchmark::task_init,                                          \
                             app::benchmark::task_func,                                          \
                             os::timer_type::microseconds(UINT32_C(100000)),                     \
                             os::timer_type::microseconds(UINT32_C(   863))),                    \
      os::task_control_block(sys::mon::task_init,                                                \
                             sys::mon::task_func,                                                \
                             os::timer_type::microseconds(UINT32_C(  4000)),                     \
                             os::timer_type::microseconds(UINT32_C(  1583))),                    \
    }                                                                                            \
  }

#endif // _OS_CFG_2011_10_20_H_
