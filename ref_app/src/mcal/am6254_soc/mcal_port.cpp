///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_port.h>

void mcal::port::init(const config_type*)
{
  // Initialize the benchmark toggle pin explicitly, even though
  // this is also done in the application benchmark when one
  // of the benchmarks is active.

  mcal::port::port_pin<mcal::reg::gpio0, 36U>::set_pin_low();
  mcal::port::port_pin<mcal::reg::gpio0, 36U>::set_direction_output();

  // Empirical observation seemingly reveals that the pad configuration
  // of gpio0.36 is mistakenly on pad37. So we must initialize pad37
  // as well since we will use gpio0.36 as the benchmark toggle-pin.

  mcal::port::port_pin<mcal::reg::gpio0, 37U>::set_pin_low();
  mcal::port::port_pin<mcal::reg::gpio0, 37U>::set_direction_output();
}
