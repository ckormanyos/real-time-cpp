/******************************************************************************************
  Filename    : SysTickTimer.h
  
  Core        : ARM Cortex-M33 / RISC-V Hazard3
  
  MCU         : RP2350
    
  Author      : Chalandi Amine
 
  Owner       : Chalandi Amine
  
  Date        : 04.09.2024
  
  Description : System timer driver header file
  
******************************************************************************************/

#ifndef __SYSTICK_TIMER_H__
#define __SYSTICK_TIMER_H__

#include "Platform_Types.h"

//=========================================================================================
// Types definition
//=========================================================================================
typedef union
{
  struct
  {
    uint32 u1ENABLE:1;
    uint32 u1TICKINT:1;
    uint32 u1CLOCKSRC:1;
    uint32 :13;
    uint32 u1COUNTFLAG:1;
    uint32 :15;
  }bits;

  uint32 u32Register;

}stStkCtrl;

typedef union
{
  struct
  {
    uint32 u24RELOAD:24;
    uint32 :8;
  }bits;

  uint32 u32Register;

}stStkLoad;

typedef union
{
  struct
  {
    uint32 u24CURRENT:24;
    uint32 :8;
  }bits;

  uint32 u32Register;

}stStkVal;

typedef union
{
  struct
  {
    uint32 u24TENMS:24;
    uint32 :6;
    uint32 u1SKEW:1;
    uint32 u1NOREF:1;
  }bits;

  uint32 u32Register;

}stStkCalib;

//=========================================================================================
// Definitions
//=========================================================================================
#define SYS_TICK_BASE_REG (0xE000E010UL)

#define pSTK_CTRL   ((volatile stStkCtrl* const) (SYS_TICK_BASE_REG + 0x00))
#define pSTK_LOAD   ((volatile stStkLoad* const) (SYS_TICK_BASE_REG + 0x04))
#define pSTK_VAL    ((volatile stStkVal* const)  (SYS_TICK_BASE_REG + 0x08))
#define pSTK_CALIB  ((volatile stStkCalib* const)(SYS_TICK_BASE_REG + 0x0C))

#define CPU_FREQ_MHZ      150U
#define SYS_TICK_MS(x)    ((uint32)(CPU_FREQ_MHZ * x * 1000UL) - 1UL)
#define SYS_TICK_US(x)    ((uint32)(CPU_FREQ_MHZ * x) - 1UL)

#define SYS_TICK_CLKSRC_PROCESSOR_CLOCK           1U
#define SYS_TICK_CLKSRC_EXTERNAL_REFERENCE_CLOCK  0U
#define SYS_TICK_ENABLE_INT                       1U
#define SYS_TICK_ENABLE_TIMER                     1U

//=========================================================================================
// Prototypes
//=========================================================================================
void SysTickTimer_Init(void);
void SysTickTimer_Start(uint32 timeout);
void SysTickTimer_Stop(void);
void SysTickTimer_Reload(uint32 timeout);

#endif /*__SYSTICK_TIMER_H__*/
