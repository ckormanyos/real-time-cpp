///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_port.h>

#include <CH32V30xxx.h>

void mcal::port::init(const config_type*)
{
  /* enable the GPIO peripheral clock */
  RCC->APB2PCENR.bit.IOPCEN = 1u;

  /* configure PC0 (LED1) as output (active-low) */
  GPIOC->BSHR.bit.BS0    = 1u; /* output a logic high (turn off the LED1) */
  GPIOC->CFGLR.bit.MODE0 = 3u; /* Output mode, maximum speed: 50MHz */
  GPIOC->CFGLR.bit.CNF0  = 1u; /* General push-pull output mode */
}
