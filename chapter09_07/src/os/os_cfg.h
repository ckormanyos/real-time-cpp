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
  namespace app { namespace display { void task_init(); void task_func(); } }
  namespace sys { namespace mon     { void task_init(); void task_func(); } }

  // Enumerate the task IDs. Note that the order in this list must
  // be identical with the order of the tasks in the task list below.
  namespace os
  {
    typedef enum enum_task_id
    {
      task_id_app_display,
      task_id_sys_mon,
      task_id_end
    }
    task_id_type;
  }

  // Configure the operating system tasks.

  // Use prime numbers for offsets.
  // Use Wolfram's alpha or Mathematica(R): Table[Prime[n], {n, 50, 2000, 50}]
  // to obtain:
  //   229,   541,   863,  1223,  1583,  1987,  2357,  2741,  3181,  3571,
  //  3989,  4409,  4831,  5279,  5693,  6133,  6571,  6997,  7499,  7919,
  //  8387,  8831,  9283,  9733, 10177, 10657, 11149, 11657, 12109, 12553,
  // 13007, 13499, 13967, 14519, 14947, 15401, 15881, 16381, 16903, 17389

  #define OS_TASK_COUNT static_cast<std::size_t>(os::task_id_end)

  #define OS_TASK_LIST                                                                           \
  {                                                                                              \
    {                                                                                            \
      os::task_control_block(app::display::task_init,                                            \
                             app::display::task_func,                                            \
                             os::timer_type::microseconds(UINT32_C(  2000)),                     \
                             os::timer_type::microseconds(UINT32_C(   229))),                    \
      os::task_control_block(sys::mon::task_init,                                                \
                             sys::mon::task_func,                                                \
                             os::timer_type::microseconds(UINT32_C( 20000)),                     \
                             os::timer_type::microseconds(UINT32_C(   541))),                    \
    }                                                                                            \
  }

#endif // _OS_CFG_2011_10_20_H_
