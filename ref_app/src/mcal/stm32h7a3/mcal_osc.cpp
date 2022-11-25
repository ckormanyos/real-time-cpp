///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2022.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "STM32H7x3.h"

#include <mcal_osc.h>

void mcal::osc::init(const config_type*)
{
  /* Configure flash wait state (280 MHz --> 6 WS)*/
  Flash->ACR.bit.LATENCY = 6u;

  /* Configure PLL1 */
  RCC->PLLCKSELR.bit.DIVM1    = 32u;
  RCC->PLLCFGR.bit.PLL1RGE    = 0u;
  RCC->PLLCFGR.bit.PLL1VCOSEL = 0u;
  RCC->PLLCFGR.bit.PLL1FRACEN = 0u;

  RCC->PLLCFGR.bit.DIVP1EN = 1u;
  RCC->PLLCFGR.bit.DIVQ1EN = 1u;
  RCC->PLLCFGR.bit.DIVR1EN = 1u;

  RCC->PLL1DIVR.bit.DIVN1 = 279u; /* VCO = 560 MHz       */
  RCC->PLL1DIVR.bit.DIVP1 = 1u;   /* pll1_p_ck = 280 MHz */
  RCC->PLL1DIVR.bit.DIVQ1 = 1u;   /* pll1_q_ck = 280 MHz */
  RCC->PLL1DIVR.bit.DIVR1 = 1u;   /* pll1_r_ck = 280 MHz */

  /* Enable PLL1 */
  RCC->CR.bit.PLL1ON = 1u;

  /* Wait for PLL1 to become ready */
  while(!RCC->CR.bit.PLL1RDY);

  /* Set pll1_p_ck as system clock */
  RCC->CFGR.bit.SW = 3u;

  /* Wait for pll1_p_ck to become system clock*/
  while(RCC->CFGR.bit.SWS != 3u);

  /* Enable GPIOs clock */
  RCC->AHB4ENR.bit.GPIOBEN = 1u;
  RCC->AHB4ENR.bit.GPIOEEN = 1u;
}
