/******************************************************************************************
  Filename    : Mcu.c
  
  Core        : QingKe V4F (RISC-V)
  
  MCU         : CH32V307VCT6 (WCH)
    
  Author      : Chalandi Amine
 
  Owner       : Chalandi Amine
  
  Date        : 23.01.2023
  
  Description : Hw Initialization implementation
  
******************************************************************************************/

//=========================================================================================
// Includes
//=========================================================================================
#include <CH32V30xxx.h>
#include <Mcu.h>


//-----------------------------------------------------------------------------------------
/// \brief  
///
/// \param  
///
/// \return 
//-----------------------------------------------------------------------------------------
void Mcu_HwInitialization(void)
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

  /* enable the GPIO peripheral clock */
  RCC->APB2PCENR.bit.IOPAEN = 1u;
  RCC->APB2PCENR.bit.IOPBEN = 1u;
  RCC->APB2PCENR.bit.IOPCEN = 1u;
  RCC->APB2PCENR.bit.IOPDEN = 1u;
  RCC->APB2PCENR.bit.IOPEEN = 1u;

  /* configure PC0 (LED1) as output (active-low) */
  GPIOC->BSHR.bit.BS0    = 1u; /* output a logic high (turn off the LED1) */
  GPIOC->CFGLR.bit.MODE0 = 3u; /* Output mode, maximum speed: 50MHz */
  GPIOC->CFGLR.bit.CNF0  = 1u; /* General push-pull output mode */
}

