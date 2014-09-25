///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2014.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_port.h>
#include <mcal_reg_access.h>

void mcal::port::init(const config_type*)
{
  // Enable the peripheral clocks for portf and portg.
  // 0x01 = porta
  // 0x02 = portb
  // 0x04 = portc
  // 0x08 = portd
  // 0x10 = porte
  // 0x20 = portf
  // 0x40 = portg
  // ------------
  // So we have:
  // (portf + portg) = (0x20 + 0x40) = 0x60.

  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::rcc_ahb1enr,
                    UINT32_C(0x60) >::reg_or();
}
