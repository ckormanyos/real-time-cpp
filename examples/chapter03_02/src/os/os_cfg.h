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
  namespace app { namespace led   { void task_init(); void task_func(); } }
  namespace app { namespace prime { void task_init(); void task_func(); } }
  namespace sys { namespace mon   { void task_init(); void task_func(); } }

  namespace os
  {
    // Enumerate the task IDs. Note that the order in this list must
    // be identical with the order of the tasks in the task list below.
    typedef enum enum_task_id
    {
      task_id_app_led,
      task_id_app_prime,
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
  // Use Wolfram's Alpha or Mathematica(R): Table[Prime[n], {n, 50, 4000, 50}]
  // to obtain:
  //   229,   541,   863,  1223,  1583,  1987,  2357,  2741,  3181,  3571,
  //  3989,  4409,  4831,  5279,  5693,  6133,  6571,  6997,  7499,  7919,
  //  8387,  8831,  9283,  9733, 10177, 10657, 11149, 11657, 12109, 12553,
  // 13007, 13499, 13967, 14519, 14947, 15401, 15881, 16381, 16903, 17389,
  // 17891, 18313, 18899, 19423, 19891, 20357, 20897, 21383, 21841, 22307,
  // 22817, 23321, 23827, 24281, 24877, 25391, 25913, 26399, 26891, 27449,
  // 27947, 28499, 28933, 29443, 30059, 30559, 31091, 31601, 32159, 32609,
  // 33113, 33613, 34157, 34649, 35159, 35759, 36277, 36781, 37309, 37813

  #define OS_TASK_COUNT static_cast<std::size_t>(os::task_id_end)

  #define OS_TASK_LIST                                                                           \
  {                                                                                              \
    {                                                                                            \
      os::task_control_block(app::led::task_init,                                                \
                             app::led::task_func,                                                \
                             os::timer_type::microseconds(UINT32_C( 8000)),                      \
                             os::timer_type::microseconds(UINT32_C(    0))),                     \
      os::task_control_block(app::prime::task_init,                                              \
                             app::prime::task_func,                                              \
                             os::timer_type::microseconds(UINT32_C(10000)),                      \
                             os::timer_type::microseconds(UINT32_C(  229))),                     \
      os::task_control_block(sys::mon::task_init,                                                \
                             sys::mon::task_func,                                                \
                             os::timer_type::microseconds(UINT32_C(40000)),                      \
                             os::timer_type::microseconds(UINT32_C(  541))),                     \
    }                                                                                            \
  }

  static_assert(OS_TASK_COUNT > std::size_t(0U), "the task count must exceed zero");

#endif // OS_CFG_2011_10_20_H_
