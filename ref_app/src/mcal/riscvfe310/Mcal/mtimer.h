/******************************************************************************************
  Filename    : mtimer.h
  
  Core        : RV32IMAC
  
  MCU         : FE310-G002 (SiFive)
    
  Author      : Chalandi Amine
 
  Owner       : Chalandi Amine
  
  Date        : 11.12.2022
  
  Description : mtimer driver header file
  
******************************************************************************************/

#ifndef __MTIME_H__
#define __MTIME_H__

//=========================================================================================
// Includes
//=========================================================================================
#include "FE310.h"

//=========================================================================================
// Macros
//=========================================================================================

/* 64-bit access to the mtime registers */
#define MTIMECMP64  *(volatile uint64*)(&(CLINT->mtimecmp))
#define MTIME64     *(volatile uint64*)(&(CLINT->mtime))

/* macros for mtime timeout */
#define MTIME_FREQ_KHZ         (uint64)32768ull
#define MTIME_TIMEOUT_S(t)     (uint64)(MTIME_FREQ_KHZ * t)
#define MTIME_TIMEOUT_MS(t)    (uint64)((uint64)(MTIME_FREQ_KHZ * t) / 1000U)
#define MTIME_TIMEOUT_US(t)    (uint64)((uint64)(MTIME_FREQ_KHZ * t) / 1000000UL)

//=========================================================================================
// Function prototypes
//========================================================================================= 
void mtimer_StopTimer(void);
void mtimer_ReloadTimer(uint64 timeout);
void mtimer_StartTimer(uint64 timeout);


#endif /* __MTIME_H__ */
