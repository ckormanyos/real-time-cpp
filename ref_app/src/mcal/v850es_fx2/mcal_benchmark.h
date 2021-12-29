///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2021.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_BENCHMARK_2021_12_25_H_
  #define MCAL_BENCHMARK_2021_12_25_H_

  #include <mcal_port.h>
  #include <mcal_reg.h>

  namespace mcal
  {
    namespace benchmark
    {
      using benchmark_port_type = mcal::port::port_pin<std::uint32_t,
                                                       std::uint8_t,
                                                       mcal::reg::pdll,
                                                       1U>;
    }
  }

#endif // MCAL_BENCHMARK_2021_12_25_H_
