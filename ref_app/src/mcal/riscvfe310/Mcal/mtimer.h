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

#if defined(__cplusplus)
extern "C"
{
#endif

uint64 mtimer_GetTick(void);

#if defined(__cplusplus)
}
#endif

#endif /* __MTIME_H__ */
