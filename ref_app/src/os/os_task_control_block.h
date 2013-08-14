///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _OS_TASK_CONTROL_BLOCK_2013_07_30_H_
  #define _OS_TASK_CONTROL_BLOCK_2013_07_30_H_

  #include <cstdint>
  #include <array>
  #include <limits>
  #include <os/os.h>

  namespace os
  {
    class task_control_block
    {
    public:
      typedef std::uint_fast8_t  index_type;
      typedef std::uint_fast16_t trace_type;

      task_control_block(const function_type i,
                         const function_type f,
                         const tick_type c,
                         const tick_type o);

      task_control_block(const task_control_block& tcb);

      void initialize() const { init(); }

      bool execute() const;

    private:
      const   function_type init;
      const   function_type func;
      const   tick_type     cycle;
      mutable timer_type    timer;
      mutable event_type    event;
      const   index_type    index;

      static index_type task_global_index;
      static trace_type task_global_trace;

      static task_control_block* get_task_pointer();

      task_control_block();
      const task_control_block& operator=(const task_control_block&);

      friend void os::start_os   ();
      friend void os::set_event  (const task_id_type task_id, const event_type& event_to_set);
      friend void os::get_event  (event_type& event_to_get);
      friend void os::clear_event(const event_type& event_mask_to_clear);
    };

    static_assert(OS_TASK_COUNT > 0U,
                  "the task count must exceed zero");

    static_assert(OS_TASK_COUNT < unsigned(std::numeric_limits<os::task_control_block::trace_type>::digits),
                  "the task count exceeds the available bits in the task trace mechanism");

    typedef std::array<os::task_control_block, OS_TASK_COUNT> task_list_type;

    extern task_list_type task_list;
  }

#endif // _OS_TASK_CONTROL_BLOCK_2013_07_30_H_
