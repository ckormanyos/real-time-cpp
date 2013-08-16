///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _OS_2011_10_20_H_
  #define _OS_2011_10_20_H_

  #include <cstdint>
  #include <os/os_cfg.h>
  #include <util/utility/util_time.h>

  namespace os
  {
    typedef void(*function_type)();

    typedef util::timer<std::uint32_t> timer_type;
    typedef timer_type::tick_type      tick_type;

    typedef std::uint_fast8_t event_type;

    void start_os   ();
    void set_event  (const task_id_type task_id, const event_type& event_to_set);
    void get_event  (event_type& event_to_get);
    void clear_event(const event_type& event_clear_mask);
  }

#endif // _OS_2011_10_20_H_
