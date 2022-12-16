/******************************************************************************************
  Filename    : Clock.c
  
  Core        : RV32IMAC
  
  MCU         : FE310-G002 (SiFive)
    
  Author      : Chalandi Amine
 
  Owner       : Chalandi Amine
  
  Date        : 11.12.2022
  
  Description : Clock driver implementation
  
******************************************************************************************/

//=====================================================================================================
// Includes
//=====================================================================================================
#include "FE310.h"
#include "Clock.h"
#include "riscv-csr.h"

//=====================================================================================================
// Functions prototype
//=====================================================================================================

//=====================================================================================================
// Macros
//=====================================================================================================

//=====================================================================================================
// Globals
//=====================================================================================================


//-----------------------------------------------------------------------------------------
/// \brief  
///
/// \param  
///
/// \return 
//-----------------------------------------------------------------------------------------
void FE310_ClockInitialization(void)
{
  /* wait for HFXOSC to be become ready */
  while(!PRCI->hfxosccfg.bit.ready);

  /* select pllref clock (HFXOSC) */
  PRCI->pllcfg.bit.refsel = 1;

  /* divide pllref (HFXOSC) by 2 ==> refr = 8 MHz */
  PRCI->pllcfg.bit.pllr = 1;

  /* multiply refr by 96 ==> vco = 768 MHz */
  PRCI->pllcfg.bit.pllf = 47;

  /* divide vco by 4 ==> pllout = 192 MHz */
  PRCI->pllcfg.bit.pllq = 2;

  /* bypass final pllout divider */
  PRCI->plloutdiv.bit.divby1 = 1;

  /* drive the final hfclk with the PLL output */
  PRCI->pllcfg.bit.sel = 1;

  /* disable pll bypass */
  PRCI->pllcfg.bit.bypass = 0;

  /* wait for pll to lock */
  while(!PRCI->pllcfg.bit.lock);
}
