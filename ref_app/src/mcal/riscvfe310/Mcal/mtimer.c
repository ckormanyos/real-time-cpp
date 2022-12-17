/******************************************************************************************
  Filename    : mtimer.c
  
  Core        : RV32IMAC
  
  MCU         : FE310-G002 (SiFive)
    
  Author      : Chalandi Amine
 
  Owner       : Chalandi Amine
  
  Date        : 11.12.2022
  
  Description : mtimer driver implementation
  
******************************************************************************************/

#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-align"
#endif

#include "mtimer.h"
#include "riscv-csr.h"

#define MTIME64 *(volatile uint64*)(&(CLINT->mtime))

uint64 mtimer_GetTick(void)
{
  return MTIME64;
}

#if defined(__GNUC__)
#pragma GCC diagnostic pop
#endif
