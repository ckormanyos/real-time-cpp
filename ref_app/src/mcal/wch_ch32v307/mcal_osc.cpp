///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2022.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdint>

#include <mcal_osc.h>

#include <CH32V30xxx.h>

#include <cstdint>

void mcal::osc::init(const config_type*)
{
  /* enable the HSE clock */
  RCC->CTLR.bit.HSEON = 1u;
  while(!(RCC->CTLR.bit.HSERDY));

  /* configure the PLL */
  RCC->CFGR2.bit.PREDIV1SRC = 0u; /* PREDIV1 clock source is HSE         */
  RCC->CFGR2.bit.PREDIV1    = 0u; /* PREDIV1 output is 8 MHz / 1         */
  RCC->CFGR0.bit.PLLSRC     = 1u; /* PLL entry clock source is HSE       */
  RCC->CFGR0.bit.PLLMUL     = 0u; /* PLLCLK  = 8MHz * 18 = 144 MHz       */
  RCC->CFGR0.bit.PLLXTPRE   = 0u; /* HSE clock not divided for PLL entry */

  /* configure internal buses clocks */
  RCC->CFGR0.bit.HPRE  = 0u; /* AHB  = PLLCLK = 144 MHz */
  RCC->CFGR0.bit.PPRE1 = 4u; /* APB1 = AHB / 2 = 72 MHz */
  RCC->CFGR0.bit.PPRE2 = 0u; /* APB2 = AHB = 144 MHz    */

  /* enable the PLL (144 MHz) */
  RCC->CTLR.bit.PLLON = 1u;
  while(!(RCC->CTLR.bit.PLLRDY));

  /* set PLL as system clock */
  RCC->CFGR0.bit.SW = 2u;
  while(RCC->CFGR0.bit.SWS != 2u);
}
