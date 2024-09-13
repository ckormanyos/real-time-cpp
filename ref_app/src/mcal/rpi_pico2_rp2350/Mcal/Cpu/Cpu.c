/******************************************************************************************
  Filename    : Cpu.c
  
  Core        : ARM Cortex-M33 / RISC-V Hazard3
  
  MCU         : RP2350
    
  Author      : Chalandi Amine
 
  Owner       : Chalandi Amine
  
  Date        : 04.09.2024
  
  Description : Cpu initialization for RP2350
  
******************************************************************************************/

//=============================================================================
// Includes
//=============================================================================
#include "Cpu.h"
#include "core_arch.h"

#include <stdbool.h>

//=============================================================================
// Globals
//=============================================================================
static uint32 u32MulticoreLock  = 0;
static volatile uint32 u32MulticoreSync = 0;


//-----------------------------------------------------------------------------------------
/// \brief  RP2350_MulticoreSync function
///
/// \param  CpuId : The cpu core identifier
///
/// \return void
//-----------------------------------------------------------------------------------------
void RP2350_MulticoreSync(uint32 CpuId)
{
  /* aquire the multicore lock */
  arch_spin_lock(&u32MulticoreLock);

  u32MulticoreSync |= (1UL << CpuId);

  /* release the multicore lock */
  arch_spin_unlock(&u32MulticoreLock);

  while(u32MulticoreSync != MULTICORE_SYNC_MASK);
}

//-----------------------------------------------------------------------------------------
/// \brief  RP2350_StartCore1 function
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------------------
void RP2350_InitCore(void)
{
  /* we came here from the RP2350 BootRom and SBL */
  /* Reset core1 to start from a known state */

  HW_PER_PSM->FRCE_OFF.bit.PROC1 = 1U;

  while((HW_PER_PSM->DONE.bit.PROC1 == 1U));

  HW_PER_PSM->FRCE_OFF.bit.PROC1 = 0U;

  while((HW_PER_PSM->DONE.bit.PROC1 != 1U));

  /* Reset peripheral to start from a known state */
  HW_PER_RESETS->RESET.bit.IO_BANK0   = 1U;
  HW_PER_RESETS->RESET.bit.PADS_BANK0 = 1U;

  while((HW_PER_RESETS->RESET_DONE.bit.IO_BANK0 == 1U) || (HW_PER_RESETS->RESET_DONE.bit.PADS_BANK0 == 1U));

  HW_PER_RESETS->RESET.bit.IO_BANK0   = 0U;
  HW_PER_RESETS->RESET.bit.PADS_BANK0 = 0U;

  while((HW_PER_RESETS->RESET_DONE.bit.IO_BANK0 == 0U) || (HW_PER_RESETS->RESET_DONE.bit.PADS_BANK0 == 0U));

#ifdef CORE_FAMILY_ARM
  /*Setting EXTEXCLALL allows external exclusive operations to be used in a configuration with no MPU.
  This is because the default memory map does not include any shareable Normal memory.*/
  SCnSCB->ACTLR |= (1ul<<29);
#endif
}

extern bool core_1_run_flag_get(void);

//-----------------------------------------------------------------------------------------
/// \brief  RP2350_StartCore1 function
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------------------
boolean RP2350_StartCore1(void)
{
  extern uint32 __INTVECT_Core1[2];

  /* Flush the mailbox */
  while(HW_PER_SIO->FIFO_ST.bit.VLD == 1UL)
  {
    (void)HW_PER_SIO->FIFO_RD.reg;
  }

  /* Send 0 to wakeup the core 1 */
  HW_PER_SIO->FIFO_WR.reg = 0;
  CORE_ARCH_SEND_EVENT_INST();

  while(HW_PER_SIO->FIFO_ST.bit.VLD != 1UL);

  if(HW_PER_SIO->FIFO_RD.reg != 0U)
  {
    return(FALSE);
  }

  /* Send 1 to synchronize with Core 1*/
  HW_PER_SIO->FIFO_WR.reg = 1;
  CORE_ARCH_SEND_EVENT_INST();

  while(HW_PER_SIO->FIFO_ST.bit.VLD != 1UL);

  if(HW_PER_SIO->FIFO_RD.reg != 1U)
  {
    return(FALSE);
  }

  /* Send the VTOR address */
  HW_PER_SIO->FIFO_WR.reg = (uint32)(&__INTVECT_Core1[0]);
  CORE_ARCH_SEND_EVENT_INST();

  while(HW_PER_SIO->FIFO_ST.bit.VLD != 1UL);

  if(HW_PER_SIO->FIFO_RD.reg != (uint32)(&__INTVECT_Core1[0]))
  {
    return(FALSE);
  }

  /* Send the stack pointer value */
  HW_PER_SIO->FIFO_WR.reg = (uint32)__INTVECT_Core1[0];
  CORE_ARCH_SEND_EVENT_INST();

  while(HW_PER_SIO->FIFO_ST.bit.VLD != 1UL);

  if(HW_PER_SIO->FIFO_RD.reg != (uint32)__INTVECT_Core1[0])
  {
    return(FALSE);
  }

  /* Send the reset handler */
  HW_PER_SIO->FIFO_WR.reg = (uint32)__INTVECT_Core1[1];
  CORE_ARCH_SEND_EVENT_INST();

  while(HW_PER_SIO->FIFO_ST.bit.VLD != 1UL);


  if(HW_PER_SIO->FIFO_RD.reg != (uint32)__INTVECT_Core1[1])
  {
    return(FALSE);
  }

  /* Clear the stiky bits of the FIFO_ST on core 0 */
  HW_PER_SIO->FIFO_ST.reg = 0xFFu;

  while(!core_1_run_flag_get()) { ; }

  return(TRUE);
}
