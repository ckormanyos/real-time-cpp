///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_port.h>
#include <mcal_reg_access.h>

void mcal::port::init(const config_type*)
{
/*
  // Enable the peripheral clocks for portb and porte.
  // 0x01 = porta
  // 0x02 = portb
  // 0x04 = portc
  // 0x08 = portd
  // 0x10 = porte
  // 0x20 = portf
  // 0x40 = portg
  // ------------
  // So we have:
  // (portb + porte) = (0x02 + 0x10) = 0x12.

  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::rcc_ahb1enr,
                    UINT32_C(0x12)>::reg_or();
*/

  // Enable the peripheral clocks for portb, portc, and portd.
  // 0x01 = porta
  // 0x02 = portb
  // 0x04 = portc
  // 0x08 = portd
  // 0x10 = porte
  // 0x20 = portf
  // 0x40 = portg
  // ------------
  // So we have:
  // (portb + portc + portd) = (0x02 + 0x04 + 0x08) = 0x0E.

  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::rcc_ahb1enr,
                    UINT32_C(0x0E)>::reg_or();
}
