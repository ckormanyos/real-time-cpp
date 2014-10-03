///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2014.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _OS_DEBUG_MONITOR_2014_03_12_H_
  #define _OS_DEBUG_MONITOR_2014_03_12_H_

  #include <cstdint>

  namespace os
  {
    struct debug_monitor
    {
      // The debug monitor task poll time in microseconds.
      static std::uint_fast16_t task_poll_time() { return UINT16_C(250); }
    };
  }

#endif // _OS_DEBUG_MONITOR_2014_03_12_H_
