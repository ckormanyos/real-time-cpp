///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2014 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_BENCHMARK_2014_04_16_H
  #define MCAL_BENCHMARK_2014_04_16_H

  #include <mcal_port.h>
  #include <mcal_reg.h>

  #include <cstdint>

  namespace mcal
  {
    namespace benchmark
    {
      typedef mcal::port::port_pin<std::uint8_t,
                                   std::uint8_t,
                                   mcal::reg::portd,
                                   UINT8_C(3)> benchmark_port_type;
    }
  }

#endif // MCAL_BENCHMARK_2014_04_16_H
