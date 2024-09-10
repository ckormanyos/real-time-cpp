/******************************************************************************************
  Filename    : Clock.c
  
  Core        : ARM Cortex-M33 / RISC-V Hazard3
  
  MCU         : RP2350
    
  Author      : Chalandi Amine
 
  Owner       : Chalandi Amine
  
  Date        : 04.09.2024
  
  Description : Clock initialization for RP2350
  
******************************************************************************************/

//=============================================================================
// Includes
//=============================================================================
#include "Clock.h"


//-----------------------------------------------------------------------------------------
/// \brief  RP2350_ClockInit function
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------------------
void RP2350_ClockInit(void)
{
   /* Init the clock XOSC */
   HW_PER_XOSC->STARTUP.bit.X4      = 0U;
   HW_PER_XOSC->STARTUP.bit.DELAY   = 47U;
   HW_PER_XOSC->CTRL.bit.FREQ_RANGE = HW_PER_XOSC->STATUS.bit.FREQ_RANGE;
   HW_PER_XOSC->CTRL.bit.ENABLE     = XOSC_CTRL_ENABLE_ENABLE;
   while(HW_PER_XOSC->STATUS.bit.STABLE != 1U);

   /* Switch the ref clock to use the xosc clock as source */
   HW_PER_CLOCKS->CLK_REF_CTRL.bit.SRC = CLOCKS_CLK_REF_CTRL_SRC_xosc_clksrc;
   while(HW_PER_CLOCKS->CLK_REF_SELECTED.reg != (1ul << CLOCKS_CLK_REF_CTRL_SRC_xosc_clksrc));

   while(HW_PER_CLOCKS->CLK_REF_DIV.bit.INT != 1);

  /* Release the reset of PLL_SYS */
   HW_PER_RESETS->RESET.bit.PLL_SYS = 0U;
   while(HW_PER_RESETS->RESET_DONE.bit.PLL_SYS != 1);

   /* Configure the PLL_SYS */
   HW_PER_PLL_SYS->CS.bit.REFDIV           = 1U;
   HW_PER_PLL_SYS->FBDIV_INT.bit.FBDIV_INT = 125U;
   HW_PER_PLL_SYS->PRIM.bit.POSTDIV1       = 5U;
   HW_PER_PLL_SYS->PRIM.bit.POSTDIV2       = 2U;

   HW_PER_PLL_SYS->PWR.bit.PD        = 0U;
   HW_PER_PLL_SYS->PWR.bit.VCOPD     = 0U;
   HW_PER_PLL_SYS->PWR.bit.POSTDIVPD = 0U;

   while(HW_PER_PLL_SYS->CS.bit.LOCK != 1U);

   /* Switch the system clock to use the PLL */
 
   if(HW_PER_CLOCKS->CLK_SYS_DIV.reg != 0x10000ul)
       HW_PER_CLOCKS->CLK_SYS_DIV.reg = 0x10000ul;
 
   HW_PER_CLOCKS->CLK_SYS_CTRL.bit.AUXSRC = CLOCKS_CLK_SYS_CTRL_AUXSRC_clksrc_pll_sys;
   HW_PER_CLOCKS->CLK_SYS_CTRL.bit.SRC    = CLOCKS_CLK_SYS_CTRL_SRC_clksrc_clk_sys_aux;
 
   while(HW_PER_CLOCKS->CLK_SYS_SELECTED.bit.CLK_SYS_SELECTED != (1ul << CLOCKS_CLK_SYS_CTRL_SRC_clksrc_clk_sys_aux));

   /* Enable clock for peripheral */
   HW_PER_CLOCKS->CLK_PERI_CTRL.bit.ENABLE = 1U;

   /* Release reset on IO_BANK0 */
    HW_PER_RESETS->RESET.bit.IO_BANK0 = 0U;

    /* Wait for reset to be done */
    /* Release reset is done on IO_BANK0 */
    while(HW_PER_RESETS->RESET_DONE.bit.IO_BANK0 != 1);
}
