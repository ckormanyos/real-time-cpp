///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2014 - 2023.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_BENCHMARK_2023_07_04_H
  #define MCAL_BENCHMARK_2023_07_04_H

  #include <cstdint>

  #include <mcal_port.h>
  #include <mcal_reg.h>

  namespace mcal
  {
    namespace benchmark
    {
      // Use port_b2.2, which is Teensy-Pin A11, name B0_02, GPIO 2.02.

      typedef mcal::port::port_pin<std::uint32_t,
                                   std::uint32_t,
                                   mcal::reg::gpio_02_base_address,
                                   static_cast<std::uint32_t>(UINT8_C(2))> benchmark_port_type;
    }
  }

#endif // MCAL_BENCHMARK_2023_07_04_H
