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
#include <Cpu.h>

extern "C"
{
  void arch_spin_lock  (uint32* lock);
  void arch_spin_unlock(uint32* lock);
}

namespace
{
           uint32 u32MulticoreLock;
  volatile uint32 u32MulticoreSync;
}

#define CORE_ARCH_SEND_EVENT_INST()    __asm("SEV")
#define CORE_ARCH_DISABLE_INTERRUPTS() __asm("CPSID i")
#define CORE_ARCH_ENABLE_INTERRUPTS()  __asm("CPSIE i")

//-----------------------------------------------------------------------------------------
/// \brief  RP2350_MulticoreSync function
///
/// \param  CpuId : The cpu core identifier
///
/// \return void
//-----------------------------------------------------------------------------------------
extern "C"
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
extern "C"
boolean RP2350_StartCore1()
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

  return(TRUE);
}
