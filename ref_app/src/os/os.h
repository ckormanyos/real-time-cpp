///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2021.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef OS_2011_10_20_H_
  #define OS_2011_10_20_H_

  #include <cstdint>
  #include <limits>
  #include <os/os_cfg.h>
  #include <util/utility/util_time.h>

  namespace os
  {
    void start_os   ();
    bool set_event  (const task_id_type task_id, const event_type& event_to_set);
    void get_event  (event_type& event_to_get);
    void clear_event(const event_type& event_to_clear);
  }

#endif // OS_2011_10_20_H_
