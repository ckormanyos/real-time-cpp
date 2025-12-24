///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2020 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef OS_TASK_2020_10_08_H
  #define OS_TASK_2020_10_08_H

  #include <FreeRTOS.h>

  #if defined(__AVR__)

  #include <task.h>

  #else

  #include <array>
  #include <chrono>
  #include <cstddef>
  #include <thread>

  #endif

  #if defined(__AVR__)

  #define OS_TASK_CREATE(name, param, prio, size) \
    static StackType_t os_task_##name##_stack_buffer[(size_t) (size)]; \
    static StaticTask_t os_task_##name##_cb_buffer; \
    ::xTaskCreateStatic(name,                                                          \
                        #name,                                                         \
                        sizeof(os_task_##name##_stack_buffer) / sizeof(StackType_t),   \
                        (void*) (param),                                               \
                        (UBaseType_t) prio,                                            \
                        &os_task_##name##_stack_buffer[(size_t) (UINT8_C(0))],         \
                        &os_task_##name##_cb_buffer)

  static inline void OS_TASK_START_SCHEDULER() { vTaskStartScheduler(); }
  static inline void OS_TASK_WAIT_YIELD(const TickType_t x) { vTaskDelay(pdMS_TO_TICKS(x)); }

  #else

  namespace os_task
  {
    namespace detail
    {
      template<const std::size_t TaskCount>
      struct task_list
      {
        static constexpr std::size_t task_count { TaskCount };

        using task_pointers_array_type = std::array<std::thread*, task_count>;

        static task_pointers_array_type task_pointers;
      };

      template<const std::size_t TaskCount>
      typename task_list<TaskCount>::task_pointers_array_type task_list<TaskCount>::task_pointers { };
    } // namespace detail

    inline void start_scheduler()
    {
      for(auto* p_task : detail::task_list<std::size_t { UINT8_C(8) }>::task_pointers)
      {
        if(p_task != nullptr)
        {
          p_task-> join();
        }
      }
    }

    inline void yield(const TickType_t x)
    {
      std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<unsigned>(x)));
    }
  } // namespace os_task

  #define OS_TASK_CREATE(name, param, prio, size) \
    std::thread t##prio { name, (void*) param }; \
    ::os_task::detail::task_list<std::size_t { UINT8_C(8) }>::task_pointers[static_cast<std::size_t>(prio)] = &t##prio

  static inline void OS_TASK_START_SCHEDULER() { ::os_task::start_scheduler(); }

  static inline void OS_TASK_WAIT_YIELD(const TickType_t x) { ::os_task::yield(x); }

  #endif

#endif // OS_TASK_2020_10_08_H
