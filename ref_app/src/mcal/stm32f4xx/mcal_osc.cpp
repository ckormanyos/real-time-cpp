///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_osc.h>
#include <mcal_reg_access.h>

extern "C" void SetSysClock();

void mcal::osc::init(const config_type*)
{
  // Configure the System clock source.
  // Set the PLL Multiply and divide factors, the AHB/APBx prescalers,
  // and the flash settings.
  SetSysClock();
}
