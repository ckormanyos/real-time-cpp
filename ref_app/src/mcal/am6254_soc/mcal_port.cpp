///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_port.h>

void mcal::port::init(const config_type*)
{
  // The pad configuration of gpio0.37 is on pad37 (empirical observation).
  // So we must initialize pad37 since we will use gpio0.36 as the
  // benchmark toggle-pin.
  mcal::port::port_pin<mcal::reg::gpio0, 36U>::set_pin_low();
  mcal::port::port_pin<mcal::reg::gpio0, 36U>::set_direction_output();

  mcal::port::port_pin<mcal::reg::gpio0, 37U>::set_pin_low();
  mcal::port::port_pin<mcal::reg::gpio0, 37U>::set_direction_output();
}
