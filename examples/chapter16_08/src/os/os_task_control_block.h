///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2022.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef OS_TASK_CONTROL_BLOCK_2013_07_30_H_
  #define OS_TASK_CONTROL_BLOCK_2013_07_30_H_

  #include <cstddef>
  #include <cstdint>
  #include <limits>
  #include <os/os.h>

  namespace os
  {
    class task_control_block final
    {
    public:
      task_control_block(const function_type init,
                         const function_type func,
                         const tick_type cycle,
                         const tick_type offset) : my_init (init),
                                                   my_func (func),
                                                   my_cycle(cycle),
                                                   my_timer(offset),
                                                   my_event() { }

      task_control_block(const task_control_block& other_tcb) : my_init (other_tcb.my_init),
                                                                my_func (other_tcb.my_func),
                                                                my_cycle(other_tcb.my_cycle),
                                                                my_timer(other_tcb.my_timer),
                                                                my_event(other_tcb.my_event) { }

      ~task_control_block() { }

    private:
      const function_type my_init;
      const function_type my_func;
      const tick_type     my_cycle;
            timer_type    my_timer;
            event_type    my_event;

      void initialize() const { my_init(); }

      bool execute(const tick_type& timepoint_of_ckeck_ready);

      task_control_block();
      task_control_block& operator=(const task_control_block&);

      friend void start_os   ();
      friend bool set_event  (const task_id_type, const event_type&);
      friend void get_event  (event_type&);
      friend void clear_event(const event_type&);
    };
  }

#endif // OS_TASK_CONTROL_BLOCK_2013_07_30_H_
