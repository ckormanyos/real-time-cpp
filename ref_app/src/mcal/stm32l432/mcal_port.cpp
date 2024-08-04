///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2024.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_port.h>
#include <mcal_reg.h>

auto mcal::port::init(const config_type*) -> void
{
  // Enable the peripheral clocks for porta, portc.
  // 0x02 = portb
  // ------------
  // So we have:
  // (portb) = (0x02).

  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::rcc_ahb2enr,
                               UINT32_C(0x02) >::reg_or();
}
