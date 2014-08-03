///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _MCAL_DEBUG_MONITOR_2013_06_07_H_
  #define _MCAL_DEBUG_MONITOR_2013_06_07_H_

  #include <cstdint>
  #include <mcal_port.h>

  namespace mcal
  {
    namespace debug_monitor
    {
      typedef std::uint16_t address_type;
      constexpr address_type address_offset = UINT16_C(0);

      typedef mcal::port::port_pin<std::uint8_t,
                                   std::uint8_t,
                                   mcal::reg::portd,
                                   UINT8_C(3)> debug_monitor_port_type;
    }
  }

#endif // _MCAL_DEBUG_MONITOR_2013_06_07_H_

