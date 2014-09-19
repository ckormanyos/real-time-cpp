#ifndef _MCAL_DEBUG_MONITOR_2013_06_07_H_
  #define _MCAL_DEBUG_MONITOR_2013_06_07_H_

  #include <cstdint>
  #include <mcal_port.h>

  namespace mcal
  {
    namespace debug_monitor
    {
      typedef std::uint32_t address_type;
      const address_type address_offset = address_type(0UL);

      typedef mcal::port::port_pin debug_monitor_port_type;
    }
  }

#endif // _MCAL_DEBUG_MONITOR_2013_06_07_H_
