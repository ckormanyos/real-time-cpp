///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2014 - 2022.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_BENCHMARK_2022_12_16_H_
  #define MCAL_BENCHMARK_2022_12_16_H_

  #include <cstdint>
  #include <mcal_port.h>
  #include <mcal_reg.h>

  namespace mcal
  {
    namespace benchmark
    {
      typedef mcal::port::port_pin<std::uint32_t,
                                   std::uint32_t,
                                   mcal::reg::gpio0_base,
                                   static_cast<std::uint32_t>(UINT8_C(4))> benchmark_port_type;
    }
  }

#endif // MCAL_BENCHMARK_2022_12_16_H_
