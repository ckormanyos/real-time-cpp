/******************************************************************************************
  Filename    : Cpu.h
  
  Core        : ARM Cortex-M0+
  
  MCU         : RP2040
    
  Author      : Chalandi Amine
 
  Owner       : Chalandi Amine
  
  Date        : 07.02.2023
  
  Description : Cpu initialization header file for RP2040
  
******************************************************************************************/
#ifndef __RP2040_CPU_H__
#define __RP2040_CPU_H__

//=============================================================================
// Includes
//=============================================================================
#include "RP2040.h"
#include "Platform_Types.h"

#ifdef __cplusplus
extern "C" {
#endif

//=============================================================================
// Defines
//=============================================================================
#define CPU_CORE0_ID   0UL
#define CPU_CORE1_ID   1UL

#define MULTICORE_SYNC_MASK  (uint32)((1UL << CPU_CORE0_ID) | (1UL << CPU_CORE1_ID))

//=============================================================================
// Functions prototype
//=============================================================================
void RP2040_MulticoreSync(uint32 CpuId);
boolean RP2040_StartCore1(void);
void RP2040_InitCore(void);

#ifdef __cplusplus
}
#endif

#endif /*__RP2040_CPU_H__*/
