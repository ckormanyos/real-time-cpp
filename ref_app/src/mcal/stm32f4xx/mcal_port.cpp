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
  // Enable the peripheral clocks for portc and portd.
  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::rcc_ahb1enr,
                    UINT32_C(0x04) | UINT32_C(0x08) >::reg_or();
}
