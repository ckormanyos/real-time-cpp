/******************************************************************************************
  Filename    : core_arch.h
  
  Core        : ARM Cortex-M33
  
  MCU         : RP2350
    
  Author      : Chalandi Amine
 
  Owner       : Chalandi Amine
  
  Date        : 29.08.2024
  
  Description : ARM macros for Raspberry Pi Pico 2
  
******************************************************************************************/

#ifndef __CORE_ARCH_H__
#define __CORE_ARCH_H__

#define CORE_ARCH_SEND_EVENT_INST()  __asm("SEV")
#define CORE_ARCH_DISABLE_INTERRUPTS() __asm("CPSID i")
#define CORE_ARCH_ENABLE_INTERRUPTS()  __asm("CPSIE i")

void arch_spin_lock  (uint32* lock);
void arch_spin_unlock(uint32* lock);

#endif //__CORE_ARCH_H__
