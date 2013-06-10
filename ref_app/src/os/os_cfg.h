///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _OS_CFG_2011_10_20_H_
  #define _OS_CFG_2011_10_20_H_

  // Declare and define the idle task.
  namespace sys { namespace idle { void task_init(); void task_func(); } }
  namespace os
  {
    inline void idle_task_init() { sys::idle::task_init(); }
    inline void idle_task_func() { sys::idle::task_func(); }
  }

  // Declare all of the tasks and their initialization functions.
  namespace sys { namespace rdm { void task_init(); void task_func(); } }
  namespace app { namespace led { void task_init(); void task_func(); } }
  namespace sys { namespace mon { void task_init(); void task_func(); } }

  // Configure the operating system tasks.
  #define OS_TASK_COUNT 3U

  #define OS_TASK_LIST                                                           \
  {                                                                              \
    {                                                                            \
    task_control_block ( sys::rdm::task_init,                                    \
                         sys::rdm::task_func,                                    \
                         task_control_block::timer_type::microseconds( 1000U),   \
                         task_control_block::timer_type::microseconds(    0U)),  \
    task_control_block ( app::led::task_init,                                    \
                         app::led::task_func,                                    \
                         task_control_block::timer_type::microseconds( 2000U),   \
                         task_control_block::timer_type::microseconds(  211U)),  \
    task_control_block ( sys::mon::task_init,                                    \
                         sys::mon::task_func,                                    \
                         task_control_block::timer_type::microseconds(20000U),   \
                         task_control_block::timer_type::microseconds(  419U)),  \
    }                                                                            \
  }

#endif // _OS_CFG_2011_10_20_H_
