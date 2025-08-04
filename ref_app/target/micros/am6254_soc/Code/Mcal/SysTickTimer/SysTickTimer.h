#ifndef __SYSTICK_TIMER_H__
#define __SYSTICK_TIMER_H__

#include <stdint.h>

//=========================================================================================
// Types definition
//=========================================================================================
typedef union
{
  struct
  {
    uint32_t u1ENABLE:1;
    uint32_t u1TICKINT:1;
    uint32_t u1CLOCKSRC:1;
    uint32_t :13;
    uint32_t u1COUNTFLAG:1;
    uint32_t :15;
  }bits;

  uint32_t u32Register;

}stStkCtrl;

typedef union
{
  struct
  {
    uint32_t u24RELOAD:24;
    uint32_t :8;
  }bits;

  uint32_t u32Register;

}stStkLoad;

typedef union
{
  struct
  {
    uint32_t u24CURRENT:24;
    uint32_t :8;
  }bits;

  uint32_t u32Register;

}stStkVal;

typedef union
{
  struct
  {
    uint32_t u24TENMS:24;
    uint32_t :6;
    uint32_t u1SKEW:1;
    uint32_t u1NOREF:1;
  }bits;

  uint32_t u32Register;

}stStkCalib;

//=========================================================================================
// Definitions
//=========================================================================================
#define SYS_TICK_BASE_REG (0xE000E010UL)

#define pSTK_CTRL   ((volatile stStkCtrl* const) (SYS_TICK_BASE_REG + 0x00))
#define pSTK_LOAD   ((volatile stStkLoad* const) (SYS_TICK_BASE_REG + 0x04))
#define pSTK_VAL    ((volatile stStkVal* const)  (SYS_TICK_BASE_REG + 0x08))
#define pSTK_CALIB  ((volatile stStkCalib* const)(SYS_TICK_BASE_REG + 0x0C))

#define CPU_FREQ_MHZ      400U
#define SYS_TICK_MS(x)    ((uint32_t)(CPU_FREQ_MHZ * x * 1000UL) - 1UL)
#define SYS_TICK_US(x)    ((uint32_t)(CPU_FREQ_MHZ * x) - 1UL)

#define SYS_TICK_CLKSRC_PROCESSOR_CLOCK           1U
#define SYS_TICK_CLKSRC_EXTERNAL_REFERENCE_CLOCK  0U
#define SYS_TICK_ENABLE_INT                       1U
#define SYS_TICK_ENABLE_TIMER                     1U

//=========================================================================================
// Prototypes
//=========================================================================================
void SysTickTimer_Init(void);
void SysTickTimer_Start(uint32_t timeout);
void SysTickTimer_Stop(void);
void SysTickTimer_Reload(uint32_t timeout);

#endif /*__SYSTICK_TIMER_H__*/