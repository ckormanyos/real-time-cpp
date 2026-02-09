/******************************************************************************************************
  Filename    : intvect.c
  
  Core        : RISC-V
  
  MCU         : ESP32-P4
    
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

void Isr_SW_Interrupt      (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_TIMER_Interrupt   (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_ExtInt00          (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_ExtInt01          (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_ExtInt02          (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_ExtInt03          (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_ExtInt04          (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_ExtInt05          (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_ExtInt06          (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_ExtInt07          (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_ExtInt08          (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_ExtInt09          (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_ExtInt10          (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_ExtInt11          (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_ExtInt12          (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_ExtInt13          (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_ExtInt14          (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_ExtInt15          (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_ExtInt16          (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_ExtInt17          (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_ExtInt18          (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_ExtInt19          (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_ExtInt20          (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_ExtInt21          (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_ExtInt22          (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_ExtInt23          (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_ExtInt24          (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_ExtInt25          (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_ExtInt26          (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_ExtInt27          (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_ExtInt28          (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_ExtInt29          (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_ExtInt30          (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_ExtInt31          (void) __attribute__((weak, alias("UndefinedHandler")));

typedef void (*InterruptHandler)(void);

//=====================================================================================================
// Interrupt vector table
//=====================================================================================================
const InterruptHandler __attribute__((aligned(64))) InterruptVectorTable[] =
{
    (InterruptHandler)&UndefinedHandler,      /* IRQ 00  Reserved  */
    (InterruptHandler)&UndefinedHandler,      /* IRQ 01  Reserved  */
    (InterruptHandler)&UndefinedHandler,      /* IRQ 02  Reserved  */
    (InterruptHandler)&Isr_SW_Interrupt,      /* IRQ 03  M mode software interrupt */
    (InterruptHandler)&UndefinedHandler,      /* IRQ 04  Reserved  */
    (InterruptHandler)&UndefinedHandler,      /* IRQ 05  Reserved  */
    (InterruptHandler)&UndefinedHandler,      /* IRQ 06  Reserved  */
    (InterruptHandler)&Isr_TIMER_Interrupt,   /* IRQ 07  M mode timer interrupt */
    (InterruptHandler)&UndefinedHandler,      /* IRQ 08  Reserved  */
    (InterruptHandler)&UndefinedHandler,      /* IRQ 09  Reserved  */
    (InterruptHandler)&UndefinedHandler,      /* IRQ 10  Reserved  */
    (InterruptHandler)&UndefinedHandler,      /* IRQ 11  Reserved  */
    (InterruptHandler)&UndefinedHandler,      /* IRQ 12  Reserved  */
    (InterruptHandler)&UndefinedHandler,      /* IRQ 13  Reserved  */
    (InterruptHandler)&UndefinedHandler,      /* IRQ 14  Reserved  */
    (InterruptHandler)&UndefinedHandler,      /* IRQ 15  Reserved  */
    (InterruptHandler)&Isr_ExtInt00,          /* IRQ 16  External Interrupt (00) */
    (InterruptHandler)&Isr_ExtInt01,          /* IRQ 17  External Interrupt (01) */
    (InterruptHandler)&Isr_ExtInt02,          /* IRQ 18  External Interrupt (02) */
    (InterruptHandler)&Isr_ExtInt03,          /* IRQ 19  External Interrupt (03) */
    (InterruptHandler)&Isr_ExtInt04,          /* IRQ 20  External Interrupt (04) */
    (InterruptHandler)&Isr_ExtInt05,          /* IRQ 21  External Interrupt (05) */
    (InterruptHandler)&Isr_ExtInt06,          /* IRQ 22  External Interrupt (06) */
    (InterruptHandler)&Isr_ExtInt07,          /* IRQ 23  External Interrupt (07) */
    (InterruptHandler)&Isr_ExtInt08,          /* IRQ 24  External Interrupt (08) */
    (InterruptHandler)&Isr_ExtInt09,          /* IRQ 25  External Interrupt (09) */
    (InterruptHandler)&Isr_ExtInt10,          /* IRQ 26  External Interrupt (10) */
    (InterruptHandler)&Isr_ExtInt11,          /* IRQ 27  External Interrupt (11) */
    (InterruptHandler)&Isr_ExtInt12,          /* IRQ 28  External Interrupt (12) */
    (InterruptHandler)&Isr_ExtInt13,          /* IRQ 29  External Interrupt (13) */
    (InterruptHandler)&Isr_ExtInt14,          /* IRQ 30  External Interrupt (14) */
    (InterruptHandler)&Isr_ExtInt15,          /* IRQ 31  External Interrupt (15) */
    (InterruptHandler)&Isr_ExtInt16,          /* IRQ 32  External Interrupt (16) */
    (InterruptHandler)&Isr_ExtInt17,          /* IRQ 33  External Interrupt (17) */
    (InterruptHandler)&Isr_ExtInt18,          /* IRQ 34  External Interrupt (18) */
    (InterruptHandler)&Isr_ExtInt19,          /* IRQ 35  External Interrupt (19) */
    (InterruptHandler)&Isr_ExtInt20,          /* IRQ 36  External Interrupt (20) */
    (InterruptHandler)&Isr_ExtInt21,          /* IRQ 37  External Interrupt (21) */
    (InterruptHandler)&Isr_ExtInt22,          /* IRQ 38  External Interrupt (22) */
    (InterruptHandler)&Isr_ExtInt23,          /* IRQ 39  External Interrupt (23) */
    (InterruptHandler)&Isr_ExtInt24,          /* IRQ 40  External Interrupt (24) */
    (InterruptHandler)&Isr_ExtInt25,          /* IRQ 41  External Interrupt (25) */
    (InterruptHandler)&Isr_ExtInt26,          /* IRQ 42  External Interrupt (26) */
    (InterruptHandler)&Isr_ExtInt27,          /* IRQ 43  External Interrupt (27) */
    (InterruptHandler)&Isr_ExtInt28,          /* IRQ 44  External Interrupt (28) */
    (InterruptHandler)&Isr_ExtInt29,          /* IRQ 45  External Interrupt (29) */
    (InterruptHandler)&Isr_ExtInt30,          /* IRQ 46  External Interrupt (30) */
    (InterruptHandler)&Isr_ExtInt31,          /* IRQ 47  External Interrupt (31) */
};
