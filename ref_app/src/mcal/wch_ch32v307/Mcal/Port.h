/******************************************************************************************
  Filename    : SysTick.h
  
  Core        : QingKe V4F (RISC-V)
  
  MCU         : CH32V307VCT6 (WCH)
    
  Author      : Chalandi Amine
 
  Owner       : Chalandi Amine
  
  Date        : 23.01.2023
  
  Description : system tick timer driver header file
  
******************************************************************************************/

#ifndef __PORT_H__
#define __PORT_H__

//=========================================================================================
// Includes
//=========================================================================================
#include <CH32V30xxx.h>
#include <Platform_Types.h>

#if defined(__cplusplus)
extern "C"
{
#endif

void Port_Init(void);

#if defined(__cplusplus)
}
#endif

#endif /* __PORT_H__ */
