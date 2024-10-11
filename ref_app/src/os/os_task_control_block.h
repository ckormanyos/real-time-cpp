///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2024.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef OS_TASK_CONTROL_BLOCK_2013_07_30_H
  #define OS_TASK_CONTROL_BLOCK_2013_07_30_H

  #include <os/os.h>

  #include <cstddef>
  #include <cstdint>
  #include <limits>

  namespace os
  {
    class task_control_block final
    {
    public:
      task_control_block(const function_type init, // NOLINT(bugprone-easily-swappable-parameters)
                         const function_type func, // NOLINT(bugprone-easily-swappable-parameters)
                         const tick_type cycle,    // NOLINT(bugprone-easily-swappable-parameters)
                         const tick_type offset)   // NOLINT(bugprone-easily-swappable-parameters)
        : my_init  { init },
          my_func  { func },
          my_cycle { cycle },
          my_timer { offset } { }

      task_control_block(const task_control_block& other_tcb) = default;

      task_control_block(task_control_block&& other_tcb) noexcept = default;

      task_control_block() = delete;

      ~task_control_block() = default;

      auto operator=(const task_control_block&) -> task_control_block& = delete;
      auto operator=(task_control_block&&) noexcept -> task_control_block& = delete;

    private:
      const function_type my_init;  // NOLINT(cppcoreguidelines-avoid-const-or-ref-data-members)
      const function_type my_func;  // NOLINT(cppcoreguidelines-avoid-const-or-ref-data-members)
      const tick_type     my_cycle; // NOLINT(cppcoreguidelines-avoid-const-or-ref-data-members)
            timer_type    my_timer;
            event_type    my_event { };

      auto initialize() const -> void { my_init(); }

      auto execute(const tick_type& timepoint_of_ckeck_ready) -> bool
      {
        // Check for a task event.
        const auto task_does_have_event = (my_event != static_cast<event_type>(UINT8_C(0)));

        if(task_does_have_event)
        {
          // Call the task function because of an event.
          my_func();
        }

        // Check for a task timeout.
        const bool task_does_have_timeout = (   (my_cycle != static_cast<os::tick_type>(UINT8_C(0)))
                                             &&  my_timer.timeout_of_specific_timepoint(timepoint_of_ckeck_ready));

        if(task_does_have_timeout)
        {
          // Increment the task's interval timer with the task cycle.
          my_timer.start_interval(my_cycle);

          // Call the task function because of a timer timeout.
          my_func();
        }

        return (task_does_have_event || task_does_have_timeout);
      }

      friend auto start_os   () -> void;
      friend auto set_event  (const task_id_type, const event_type&) -> bool;
      friend auto get_event  (event_type&) -> void;
      friend auto clear_event(const event_type&) -> void;
    };
  } // namespace os

#endif // OS_TASK_CONTROL_BLOCK_2013_07_30_H
