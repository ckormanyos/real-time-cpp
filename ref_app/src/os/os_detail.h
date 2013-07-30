///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _OS_DETAIL_2013_07_30_H_
  #define _OS_DETAIL_2013_07_30_H_

  #include <cstdint>
  #include <array>
  #include <os/os.h>

  namespace os
  {
    namespace detail
    {
      class task_control_block
      {
      public:
        typedef std::uint_fast8_t task_index_type;

        task_control_block(const function_type i,
                           const function_type f,
                           const tick_type c,
                           const tick_type o = static_cast<tick_type>(0U));

        task_control_block(const task_control_block&);

        void initialize() const { init(); }

        bool execute()
        {
          const bool has_event = (event != event_type(0U));

          if(has_event)
          {
            ready_task_index = my_index;

            // Call the task because of an event.
            func();
          }

          const bool has_timeout = timer.timeout();

          if(has_timeout)
          {
            ready_task_index = my_index;

            // Increment the task's interval timer with the task cycle.
            timer.start_interval(cycle);

            // Call the task because of a timer timeout.
            func();
          }

          return (has_timeout | has_event);
        }

      private:
        const function_type    init;
        const function_type    func;
        const tick_type        cycle;
              timer_type       timer;
              event_type       event;
        const task_index_type  my_index;

        static task_index_type ready_task_index;

        task_control_block();
        const task_control_block& operator=(const task_control_block&);

        friend void os::schedule();
        friend void os::set_event(const task_id_type task_id, const event_type& event_to_set);
        friend void os::get_event(event_type& event_to_get);
        friend void os::clr_event(const event_type& event_mask_to_clear);
      };

      static_assert(OS_TASK_COUNT > 0U, "the task count must exceed zero");

      typedef std::array<os::detail::task_control_block, OS_TASK_COUNT> task_list_type;

      extern task_list_type task_list;
    }
  }

#endif // _OS_DETAIL_2013_07_30_H_
