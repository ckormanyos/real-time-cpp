///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2014.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _OS_TASK_CONTROL_BLOCK_2013_07_30_H_
  #define _OS_TASK_CONTROL_BLOCK_2013_07_30_H_

  #include <array>
  #include <cstdint>
  #include <limits>
  #include <os/os.h>
  #include <util/utility/util_bit_mask.h>

  namespace os
  {
    class task_control_block final
    {
    public:
      typedef std::uint_fast8_t index_type;

      task_control_block(const function_type init,
                         const function_type func,
                         const tick_type     cycle,
                         const tick_type     offset);

      task_control_block(const task_control_block& other_tcb);

      ~task_control_block();

    private:
      const    function_type my_init;
      const    function_type my_func;
      const    tick_type     my_cycle;
      mutable  timer_type    my_timer;
      mutable  event_type    my_event;
      const    index_type    my_index;

      void initialize() const;

      bool execute() const;

      task_control_block();
      task_control_block& operator=(const task_control_block&);

      friend void start_os   ();
      friend void set_event  (const task_id_type, const event_type&);
      friend void get_event  (event_type&);
      friend void clear_event(const event_type&);
    };

    static_assert(OS_TASK_COUNT > 0U,
                  "the task count must exceed zero");

    static_assert(OS_TASK_COUNT == unsigned(task_id_end),
                  "the task count must be identically equal to the highest task id");

    typedef const std::array<task_control_block, OS_TASK_COUNT> task_list_type;

    extern const task_list_type& task_list();

    struct secure
    {
    private:
      static task_list_type::const_iterator os_get_running_task_iterator();

      friend void os::get_event  (os::event_type&);
      friend void os::clear_event(const os::event_type&);
    };
  }

#endif // _OS_TASK_CONTROL_BLOCK_2013_07_30_H_
