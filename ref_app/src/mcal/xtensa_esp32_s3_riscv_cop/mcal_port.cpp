///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_port.h>

auto mcal::port::init(const config_type*) -> void
{
  // Set all GPIO out registers to low.
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::gpio::rtc_gpio_out_reg, UINT32_C(0)>::reg_set();
}
