/******************************************************************************************
  Filename    : Clock.h
  
  Core        : ARM Cortex-M0+
  
  MCU         : RP2040
    
  Author      : Chalandi Amine
 
  Owner       : Chalandi Amine
  
  Date        : 07.02.2023
  
  Description : Clock initialization header file for RP2040
  
******************************************************************************************/
#ifndef __RP2040_CLOCK_H__
#define __RP2040_CLOCK_H__

//=============================================================================
// Includes
//=============================================================================
#include "RP2040.h"
#include "Platform_Types.h"

#ifdef __cplusplus
extern "C" {
#endif

//=============================================================================
// Functions prototype
//=============================================================================
void RP2040_ClockInit(void);

#ifdef __cplusplus
}
#endif


#endif /*__RP2040_CLOCK_H__*/
