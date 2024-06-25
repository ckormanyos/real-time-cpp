/******************************************************************************************
  Filename    : SysTick.c
  
  Core        : QingKe V4F (RISC-V)
  
  MCU         : CH32V307VCT6 (WCH)
    
  Author      : Chalandi Amine
 
  Owner       : Chalandi Amine
  
  Date        : 23.01.2023
  
  Description : system tick timer driver implementation
  
******************************************************************************************/

//=========================================================================================
// Includes
//=========================================================================================
#include <SysTick.h>

//-----------------------------------------------------------------------------------------
/// \brief  
///
/// \param  
///
/// \return 
//-----------------------------------------------------------------------------------------
void SysTick_Init(void)
{
  /* enable counter interrupt */
  R32_STK_CTLR->bit.u1STIE = 1u;

  /* select HCLK as time base */
  R32_STK_CTLR->bit.u1STCLK = 1u;

  /* select upcounting mode */
  R32_STK_CTLR->bit.u1MODE = 0u;

  /* init the count value */
  R32_STK_CTLR->bit.u1INIT = 0u;

  /* start the counter */
  R32_STK_CTLR->bit.u1STE = 1u;
}

uint64 SysTick_Get(void)
{
  uint64 consistent_unscaled_tick;

  for(;;)
  {
    const volatile uint32 mt_lo1 __attribute__((no_reorder)) = R32_STK_CNTL->u32Reg;
    const volatile uint32 mt_hi  __attribute__((no_reorder)) = R32_STK_CNTH->u32Reg;
    const volatile uint32 mt_lo2 __attribute__((no_reorder)) = R32_STK_CNTL->u32Reg;

    if(mt_lo2 > mt_lo1)
    {
      consistent_unscaled_tick = (uint64) ((uint64) (((uint64) mt_hi) << 32U) | mt_lo1);

      break;
    }
  }

  return (uint64) ((uint64) (consistent_unscaled_tick + 72U) / 144U);
}
