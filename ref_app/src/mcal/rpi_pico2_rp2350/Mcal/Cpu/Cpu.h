/******************************************************************************************
  Filename    : Cpu.h
  
  Core        : ARM Cortex-M33 / RISC-V Hazard3
  
  MCU         : RP2350
    
  Author      : Chalandi Amine
 
  Owner       : Chalandi Amine
  
  Date        : 04.09.2024
  
  Description : Cpu initialization header file for RP2350
  
******************************************************************************************/
#ifndef __RP2350_CPU_H__
#define __RP2350_CPU_H__

//=============================================================================
// Includes
//=============================================================================
#include "RP2350.h"
#include "Platform_Types.h"

//=============================================================================
// Defines
//=============================================================================
#define CPU_CORE0_ID   0UL
#define CPU_CORE1_ID   1UL

#define MULTICORE_SYNC_MASK  (uint32)((1UL << CPU_CORE0_ID) | (1UL << CPU_CORE1_ID))

//=============================================================================
// Functions prototype
//=============================================================================
void RP2350_MulticoreSync(uint32 CpuId);
boolean RP2350_StartCore1(void);
void RP2350_InitCore(void);

#endif /*__RP2350_CPU_H__*/
