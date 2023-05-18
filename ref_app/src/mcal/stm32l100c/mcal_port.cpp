///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_port.h>
#include <mcal_reg.h>

void mcal::port::init(const config_type*)
{
  // Enable the peripheral clocks for portb, portc.
  // 0x01 = porta
  // 0x02 = portb
  // 0x04 = portc
  // ------------
  // So we have:
  // (portb + portc) = (0x02 + 0x04) = 0x06.

  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::rcc_ahbenr,
                               static_cast<std::uint32_t>(UINT32_C(0x00000006))>::reg_or();
}
