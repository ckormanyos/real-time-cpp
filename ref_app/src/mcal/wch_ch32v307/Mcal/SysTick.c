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

//=========================================================================================
// Defines
//=========================================================================================
#define SYSTICK_USED_WITHOUT_OS   TRUE

//=========================================================================================
// ISR function prototype
//=========================================================================================
#if (SYSTICK_USED_WITHOUT_OS == TRUE)
  void Isr_SysTick(void) __attribute__ ((interrupt ("machine")));
#endif

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

  /* no countinous counting */
  R32_STK_CTLR->bit.u1STRE = 1u;

  /* select upcounting mode */
  R32_STK_CTLR->bit.u1MODE = 0u;

  /* init the count value */
  R32_STK_CTLR->bit.u1INIT = 1u;

#if (SYSTICK_USED_WITHOUT_OS == TRUE)
  /* enable the PFIC interrupt for systick */
  PFIC->IENR1.reg |= (1ul  << 12);
#endif
}

//-----------------------------------------------------------------------------------------
/// \brief  
///
/// \param  
///
/// \return 
//-----------------------------------------------------------------------------------------
void SysTick_Start(uint64 timeout)
{
  *(volatile uint64*) (&R32_STK_CMPLR->u32Reg) = (uint64) timeout;

  R32_STK_CTLR->bit.u1STE = 1u;
}

//-----------------------------------------------------------------------------------------
/// \brief  
///
/// \param  
///
/// \return 
//-----------------------------------------------------------------------------------------
void SysTick_Stop(void)
{
  R32_STK_CTLR->bit.u1STE = 0u;
}

#if (SYSTICK_USED_WITHOUT_OS == TRUE)
//-----------------------------------------------------------------------------------------
/// \brief  
///
/// \param  
///
/// \return 
//-----------------------------------------------------------------------------------------
void Isr_SysTick(void)
{
  GPIOC->OUTDR.bit.ODR0 ^= 1u;

  R32_STK_SR->bit.u1CNTIF = 0u;
}
#endif

