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
#include <RP2040.h>

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

//=============================================================================
// Functions prototype
//=============================================================================
void RP2040_MulticoreSync(uint32_t CpuId);
bool RP2040_StartCore1   (void);

#ifdef __cplusplus
}
#endif

#endif /*__RP2040_CPU_H__*/
