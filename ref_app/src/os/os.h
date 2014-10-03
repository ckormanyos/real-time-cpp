///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2014.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _OS_2011_10_20_H_
  #define _OS_2011_10_20_H_

  #include <cstdint>
  #include <limits>
  #include <os/os_cfg.h>
  #include <util/utility/util_time.h>

  namespace os
  {
    typedef void(*function_type)();

    typedef std::uint_fast32_t              unsigned_tick_type;
    typedef util::timer<unsigned_tick_type> timer_type;
    typedef timer_type::tick_type           tick_type;
    typedef std::uint_fast16_t              event_type;

    static_assert(std::numeric_limits<os::tick_type>::digits >= 32,
                  "The operating system timer_type must be at least 32-bits wide.");

    static_assert(std::numeric_limits<os::event_type>::digits >= 16,
                  "The operating system event_type must be at least 16-bits wide.");

    void start_os   ();
    void set_event  (const task_id_type task_id, const event_type& event_to_set);
    void get_event  (event_type& event_to_get);
    void clear_event(const event_type& event_clear_mask);
  }

  #include <os/os_task_control_block.h>

#endif // _OS_2011_10_20_H_
