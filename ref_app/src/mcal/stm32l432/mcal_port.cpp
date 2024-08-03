///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2024.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_port.h>
#include <mcal_reg.h>

#include <Mcal/Reg.h>

extern "C"
void PortInit(void);

extern "C"
void PortInit(void)
{
  /* Initialize the ports.      */
  /* Enable the clock for GPIOB */
  RCC_AHB2ENR |= (1U << 1U);
}

void mcal::port::init(const config_type*)
{
  ::PortInit();
}
