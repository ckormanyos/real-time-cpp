///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2016.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef OS_CFG_2011_10_20_H_
  #define OS_CFG_2011_10_20_H_

  #include <cstddef>
  #include <cstdint>
  #include <limits>

  #include <util/utility/util_time.h>

  // Declare the task initialization and the task function of the idle process.
  namespace sys { namespace idle { void task_init(); void task_func(); } }

  // Define symbols for the task initialization and the task function of the idle process.
  #define OS_IDLE_TASK_INIT() sys::idle::task_init()
  #define OS_IDLE_TASK_FUNC() sys::idle::task_func()

  // Declare all of the task initializations and the task functions.
  namespace app { namespace led       { void task_init(); void task_func(); } }
  namespace app { namespace benchmark { void task_init(); void task_func(); } }
  namespace sys { namespace mon       { void task_init(); void task_func(); } }

  namespace os
  {
    // Enumerate the task IDs. Note that the order in this list must
    // be identical with the order of the tasks in the task list below.
    typedef enum enum_task_id
    {
      task_id_app_led,
      task_id_app_benchmark,
      task_id_sys_mon,
      task_id_end
    }
    task_id_type;

    // Configure the operating system types.
    typedef void(*function_type)();

    typedef util::timer<std::uint_fast32_t> timer_type;
    typedef timer_type::tick_type           tick_type;
    typedef std::uint_fast16_t              event_type;

    static_assert(std::numeric_limits<os::tick_type>::digits >= 32,
                  "The operating system timer_type must be at least 32-bits wide.");

    static_assert(std::numeric_limits<os::event_type>::digits >= 16,
                  "The operating system event_type must be at least 16-bits wide.");
  }

  // Configure the operating system tasks.

  // Use small prime numbers (representing microseconds) for task offsets.
  // Use Wolfram's Alpha or Mathematica(R): Table[Prime[n], {n, 25, 1000, 25}]
  // to obtain:
  //    97,  229,  379,  541,  691,  863, 1039, 1223, 1427, 1583, 1777,
  //  1987, 2153, 2357, 2557, 2741, 2953, 3181, 3371, 3571, 3769, 3989,
  //  4201, 4409, 4637, 4831, 5039, 5279, 5483, 5693, 5881, 6133, 6337,
  //  6571, 6793, 6997, 7237, 7499, 7687, 7919

  #define OS_TASK_COUNT static_cast<std::size_t>(os::task_id_end)

  #define OS_TASK_LIST                                                                           \
  {                                                                                              \
    {                                                                                            \
      os::task_control_block(app::led::task_init,                                                \
                             app::led::task_func,                                                \
                             os::timer_type::microseconds(UINT32_C(  2000)),                     \
                             os::timer_type::microseconds(UINT32_C(     0))),                    \
      os::task_control_block(app::benchmark::task_init,                                          \
                             app::benchmark::task_func,                                          \
                             os::timer_type::microseconds(UINT32_C(100000)),                     \
                             os::timer_type::microseconds(UINT32_C(   379))),                    \
      os::task_control_block(sys::mon::task_init,                                                \
                             sys::mon::task_func,                                                \
                             os::timer_type::microseconds(UINT32_C(  4000)),                     \
                             os::timer_type::microseconds(UINT32_C(   541))),                    \
    }                                                                                            \
  }

  static_assert(OS_TASK_COUNT > std::size_t(0U), "the task count must exceed zero");

#endif // OS_CFG_2011_10_20_H_
