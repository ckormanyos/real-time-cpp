///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2014.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _MCAL_BENCHMARK_2014_04_16_H_
  #define _MCAL_BENCHMARK_2014_04_16_H_

  #include <mcal_port.h>

  namespace mcal
  {
    namespace benchmark
    {
      typedef mcal::port::port_pin<std::uint32_t,
                                   std::uint32_t,
                                   mcal::reg::trisg,
                                   UINT32_C(14)> benchmark_port_type;
    }
  }

#endif // _MCAL_BENCHMARK_2014_04_16_H_
