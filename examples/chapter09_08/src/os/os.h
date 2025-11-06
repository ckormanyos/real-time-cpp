///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef OS_2011_10_20_H
  #define OS_2011_10_20_H

  #include <os/os_cfg.h>
  #include <util/utility/util_time.h>

  namespace os
  {
    auto start_os() -> void;
    auto set_event(const task_id_type task_id, const event_type& event_to_set) -> bool;
    auto get_event(event_type& event_to_get) -> void;
    auto clear_event(const event_type& event_to_clear) -> void;
  }

#endif // OS_2011_10_20_H
