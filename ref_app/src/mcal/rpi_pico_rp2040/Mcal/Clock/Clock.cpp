/******************************************************************************************
  Filename    : Clock.c
  
  Core        : ARM Cortex-M0+
  
  MCU         : RP2040
    
  Author      : Chalandi Amine
 
  Owner       : Chalandi Amine
  
  Date        : 07.02.2023
  
  Description : Clock initialization for RP2040
  
******************************************************************************************/

//=============================================================================
// Includes
//=============================================================================
#include "Clock.h"


//-----------------------------------------------------------------------------------------
/// \brief  RP2040_ClockInit function
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------------------
extern "C"
void RP2040_ClockInit(void)
{
   /* Init the clock XOSC */
   XOSC->STARTUP.bit.X4      = 1U;
   XOSC->STARTUP.bit.DELAY   = 47U;
   XOSC->CTRL.bit.FREQ_RANGE = XOSC_CTRL_FREQ_RANGE_1_15MHZ;
   XOSC->CTRL.bit.ENABLE     = XOSC_CTRL_ENABLE_ENABLE;
   while(XOSC->STATUS.bit.STABLE != 1U);


  /* Release the reset of PLL_SYS */
   RESETS->RESET.bit.pll_sys = 0U;
   while(RESETS->RESET_DONE.bit.pll_sys != 1);

   /* Configure the PLL_SYS */
   PLL_SYS->CS.bit.REFDIV           = 1U;
   PLL_SYS->FBDIV_INT.bit.FBDIV_INT = 133U;
   PLL_SYS->PRIM.bit.POSTDIV1       = 6U;
   PLL_SYS->PRIM.bit.POSTDIV2       = 2U;

   PLL_SYS->PWR.bit.PD        = 0U;
   PLL_SYS->PWR.bit.VCOPD     = 0U;

   while(PLL_SYS->CS.bit.LOCK != 1U);

   PLL_SYS->PWR.bit.POSTDIVPD = 0U;

   /* Switch the system clock to use the PLL */
   CLOCKS->CLK_SYS_CTRL.bit.AUXSRC = CLOCKS_CLK_SYS_CTRL_AUXSRC_clksrc_pll_sys;
   CLOCKS->CLK_SYS_CTRL.bit.SRC    = CLOCKS_CLK_SYS_CTRL_SRC_clksrc_clk_sys_aux;
   CLOCKS->CLK_SYS_DIV.bit.INT     = 1U;
   CLOCKS->CLK_SYS_DIV.bit.FRAC    = 0U;
 
   while(CLOCKS->CLK_SYS_SELECTED == 0UL);

   /* Enable clock for peripheral */
   CLOCKS->CLK_PERI_CTRL.bit.ENABLE = 1U;

   /* Release reset on IO_BANK0 */
    RESETS->RESET.bit.io_bank0 = 0U;

    /* Wait for reset to be done */
    /* Release reset is done on IO_BANK0 */
    while(RESETS->RESET_DONE.bit.io_bank0 != 1);
}
