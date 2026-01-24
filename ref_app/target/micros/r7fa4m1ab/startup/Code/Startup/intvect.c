/******************************************************************************************************
  Filename    : intvect.c
  
  Core        : ARM Cortex-M4
  
  MCU         : Renesas R7FA4M1AB
    
  Author      : Chalandi Amine
 
  Owner       : Chalandi Amine
  
  Date        : 22.01.2026
  
  Description : Interrupt vector table implementation
  
******************************************************************************************************/

//=====================================================================================================
// Includes
//=====================================================================================================
#include <stdint.h>

//=====================================================================================================
// Functions prototype
//=====================================================================================================
static void UndefinedHandler(void);
static void UndefinedHandler(void){ for(;;); }

extern void __STACK_TOP(void);
extern void Startup_Init(void);

void NMI                   (void) __attribute__((weak, alias("UndefinedHandler")));
void HardFault             (void) __attribute__((weak, alias("UndefinedHandler")));
void MemoryManagementFault (void) __attribute__((weak, alias("UndefinedHandler")));
void BusFault              (void) __attribute__((weak, alias("UndefinedHandler")));
void UsageFault            (void) __attribute__((weak, alias("UndefinedHandler")));
void SVCall                (void) __attribute__((weak, alias("UndefinedHandler")));
void DebugMonitor          (void) __attribute__((weak, alias("UndefinedHandler")));
void PendSV                (void) __attribute__((weak, alias("UndefinedHandler")));
void SysTickTimer          (void) __attribute__((weak, alias("UndefinedHandler")));
void IEL0_IRQn             (void) __attribute__((weak, alias("UndefinedHandler")));
void IEL1_IRQn             (void) __attribute__((weak, alias("UndefinedHandler")));
void IEL2_IRQn             (void) __attribute__((weak, alias("UndefinedHandler")));
void IEL3_IRQn             (void) __attribute__((weak, alias("UndefinedHandler")));
void IEL4_IRQn             (void) __attribute__((weak, alias("UndefinedHandler")));
void IEL5_IRQn             (void) __attribute__((weak, alias("UndefinedHandler")));
void IEL6_IRQn             (void) __attribute__((weak, alias("UndefinedHandler")));
void IEL7_IRQn             (void) __attribute__((weak, alias("UndefinedHandler")));
void IEL8_IRQn             (void) __attribute__((weak, alias("UndefinedHandler")));
void IEL9_IRQn             (void) __attribute__((weak, alias("UndefinedHandler")));
void IEL10_IRQn            (void) __attribute__((weak, alias("UndefinedHandler")));
void IEL11_IRQn            (void) __attribute__((weak, alias("UndefinedHandler")));
void IEL12_IRQn            (void) __attribute__((weak, alias("UndefinedHandler")));
void IEL13_IRQn            (void) __attribute__((weak, alias("UndefinedHandler")));
void IEL14_IRQn            (void) __attribute__((weak, alias("UndefinedHandler")));
void IEL15_IRQn            (void) __attribute__((weak, alias("UndefinedHandler")));
void IEL16_IRQn            (void) __attribute__((weak, alias("UndefinedHandler")));
void IEL17_IRQn            (void) __attribute__((weak, alias("UndefinedHandler")));
void IEL18_IRQn            (void) __attribute__((weak, alias("UndefinedHandler")));
void IEL19_IRQn            (void) __attribute__((weak, alias("UndefinedHandler")));
void IEL20_IRQn            (void) __attribute__((weak, alias("UndefinedHandler")));
void IEL21_IRQn            (void) __attribute__((weak, alias("UndefinedHandler")));
void IEL22_IRQn            (void) __attribute__((weak, alias("UndefinedHandler")));
void IEL23_IRQn            (void) __attribute__((weak, alias("UndefinedHandler")));
void IEL24_IRQn            (void) __attribute__((weak, alias("UndefinedHandler")));
void IEL25_IRQn            (void) __attribute__((weak, alias("UndefinedHandler")));
void IEL26_IRQn            (void) __attribute__((weak, alias("UndefinedHandler")));
void IEL27_IRQn            (void) __attribute__((weak, alias("UndefinedHandler")));
void IEL28_IRQn            (void) __attribute__((weak, alias("UndefinedHandler")));
void IEL29_IRQn            (void) __attribute__((weak, alias("UndefinedHandler")));
void IEL30_IRQn            (void) __attribute__((weak, alias("UndefinedHandler")));
void IEL31_IRQn            (void) __attribute__((weak, alias("UndefinedHandler")));

typedef void (*InterruptHandler)(void);

//=====================================================================================================
// Interrupt vector table
//=====================================================================================================
const InterruptHandler __attribute__((section(".intvect"), aligned(512))) InterruptVectorTable[] =
{
    (InterruptHandler)&__STACK_TOP,       /* IRQ 00  Reserved  */
    (InterruptHandler)&Startup_Init,      /* IRQ 01  Reserved  */
    (InterruptHandler)&NMI,
    (InterruptHandler)&HardFault,
    (InterruptHandler)&MemoryManagementFault,
    (InterruptHandler)&BusFault,
    (InterruptHandler)&UsageFault,
    (InterruptHandler)0,
    (InterruptHandler)0,
    (InterruptHandler)0,
    (InterruptHandler)0,
    (InterruptHandler)&SVCall,
    (InterruptHandler)&DebugMonitor,
    (InterruptHandler)0,
    (InterruptHandler)&PendSV,
    (InterruptHandler)&SysTickTimer,
    (InterruptHandler)&IEL0_IRQn,
    (InterruptHandler)&IEL1_IRQn,
    (InterruptHandler)&IEL2_IRQn,
    (InterruptHandler)&IEL3_IRQn,
    (InterruptHandler)&IEL4_IRQn,
    (InterruptHandler)&IEL5_IRQn,
    (InterruptHandler)&IEL6_IRQn,
    (InterruptHandler)&IEL7_IRQn,
    (InterruptHandler)&IEL8_IRQn,
    (InterruptHandler)&IEL9_IRQn,
    (InterruptHandler)&IEL10_IRQn,
    (InterruptHandler)&IEL11_IRQn,
    (InterruptHandler)&IEL12_IRQn,
    (InterruptHandler)&IEL13_IRQn,
    (InterruptHandler)&IEL14_IRQn,
    (InterruptHandler)&IEL15_IRQn,
    (InterruptHandler)&IEL16_IRQn,
    (InterruptHandler)&IEL17_IRQn,
    (InterruptHandler)&IEL18_IRQn,
    (InterruptHandler)&IEL19_IRQn,
    (InterruptHandler)&IEL20_IRQn,
    (InterruptHandler)&IEL21_IRQn,
    (InterruptHandler)&IEL22_IRQn,
    (InterruptHandler)&IEL23_IRQn,
    (InterruptHandler)&IEL24_IRQn,
    (InterruptHandler)&IEL25_IRQn,
    (InterruptHandler)&IEL26_IRQn,
    (InterruptHandler)&IEL27_IRQn,
    (InterruptHandler)&IEL28_IRQn,
    (InterruptHandler)&IEL29_IRQn,
    (InterruptHandler)&IEL30_IRQn,
    (InterruptHandler)&IEL31_IRQn,
};
