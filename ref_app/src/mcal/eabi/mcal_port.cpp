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
  // Set portc.8 for digital output.
  mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::gpioc_crh, 0x44444433UL>::reg_set();

  // Set porta.2 for digital output.
//  mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::gpioa_crl, 0x44443344UL>::reg_set();
}
