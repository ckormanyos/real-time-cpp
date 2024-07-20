/******************************************************************************************
  Filename    : Cpu.c
  
  Core        : ARM Cortex-M0+
  
  MCU         : RP2040
    
  Author      : Chalandi Amine
 
  Owner       : Chalandi Amine
  
  Date        : 07.02.2023
  
  Description : Cpu initialization for RP2040
  
******************************************************************************************/

//=============================================================================
// Includes
//=============================================================================
#include "Cpu.h"

//=============================================================================
// Globals
//=============================================================================
static volatile uint32 u32MulticoreSync = 0;


//-----------------------------------------------------------------------------------------
/// \brief  RP2040_MulticoreSync function
///
/// \param  CpuId : The cpu core identifier
///
/// \return void
//-----------------------------------------------------------------------------------------
extern "C"
void RP2040_MulticoreSync(uint32 CpuId)
{
  u32MulticoreSync |= (1UL << CpuId);

  while(u32MulticoreSync != MULTICORE_SYNC_MASK);
}

//-----------------------------------------------------------------------------------------
/// \brief  RP2040_StartCore1 function
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------------------
extern "C"
void RP2040_InitCore(void)
{
  /* we came here from the RP2040 BootRom and SBL */
  /* Reset core1 to start from a known state */

  PSM->FRCE_OFF.bit.proc1 = 1U;

  while((PSM->DONE.bit.proc1 == 1U));

  PSM->FRCE_OFF.bit.proc1 = 0U;

  while((PSM->DONE.bit.proc1 != 1U));

  /* Reset peripheral to start from a known state */
  RESETS->RESET.bit.io_bank0   = 1U;
  RESETS->RESET.bit.pads_bank0 = 1U;

  while((RESETS->RESET_DONE.bit.io_bank0 == 1U) || (RESETS->RESET_DONE.bit.pads_bank0 == 1U));

  RESETS->RESET.bit.io_bank0   = 0U;
  RESETS->RESET.bit.pads_bank0 = 0U;

  while((RESETS->RESET_DONE.bit.io_bank0 == 0U) || (RESETS->RESET_DONE.bit.pads_bank0 == 0U));

}

//-----------------------------------------------------------------------------------------
/// \brief  RP2040_StartCore1 function
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------------------
extern "C"
boolean RP2040_StartCore1(void)
{
  extern uint32 __INTVECT_Core1[2];

  /* Flush the mailbox */
  while(SIO->FIFO_ST.bit.VLD == 1UL)
  {
    (void)SIO->FIFO_RD;
  }

  /* Send 0 to wakeup the core 1 */
  SIO->FIFO_WR = 0;
  __asm("SEV");

  while(SIO->FIFO_ST.bit.VLD != 1UL);

  if(SIO->FIFO_RD != 0U)
  {
    return(FALSE);
  }

  /* Send 1 to synchronize with Core 1*/
  SIO->FIFO_WR = 1;
  __asm("SEV");

  while(SIO->FIFO_ST.bit.VLD != 1UL);

  if(SIO->FIFO_RD != 1U)
  {
    return(FALSE);
  }

  /* Send the VTOR address */
  SIO->FIFO_WR = (uint32)(&__INTVECT_Core1[0]);
  __asm("SEV");

  while(SIO->FIFO_ST.bit.VLD != 1UL);

  if(SIO->FIFO_RD != (uint32)(&__INTVECT_Core1[0]))
  {
    return(FALSE);
  }

  /* Send the stack pointer value */
  SIO->FIFO_WR = (uint32)__INTVECT_Core1[0];
  __asm("SEV");

  while(SIO->FIFO_ST.bit.VLD != 1UL);

  if(SIO->FIFO_RD != (uint32)__INTVECT_Core1[0])
  {
    return(FALSE);
  }

  /* Send the reset handler */
  SIO->FIFO_WR = (uint32)__INTVECT_Core1[1];
  __asm("SEV");

  while(SIO->FIFO_ST.bit.VLD != 1UL);

  if(SIO->FIFO_RD != (uint32)__INTVECT_Core1[1])
  {
    return(FALSE);
  }

  /* Clear the stiky bits of the FIFO_ST on core 0 */
  SIO->FIFO_ST.reg = 0xFFu;

  return(TRUE);
}
