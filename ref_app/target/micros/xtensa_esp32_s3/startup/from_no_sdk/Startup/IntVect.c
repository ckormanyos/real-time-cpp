/******************************************************************************************
  Filename    : IntVect.c
  
  Core        : Xtensa LX7
  
  MCU         : ESP32-S3
    
  Author      : Chalandi Amine
 
  Owner       : Chalandi Amine
  
  Date        : 22.02.2025
  
  Description : Interrupt vector tables for ESP32-S3
  
******************************************************************************************/


#if 0

//=============================================================================
// Types definition
//=============================================================================
typedef void (*InterruptHandler)(void);

void UndefinedHandler(void);
void UndefinedHandler(void) { for(;;); }

//=============================================================================
// Functions prototype
//=============================================================================


/* Default interrupts handler */
void irq_Peripherals(void)       __attribute__((weak, alias("UndefinedHandler")));
void irq_Timer0(void)            __attribute__((weak, alias("UndefinedHandler")));
void irq_Timer1(void)            __attribute__((weak, alias("UndefinedHandler")));
void irq_Timer2(void)            __attribute__((weak, alias("UndefinedHandler")));
void irq_Trap0(void)             __attribute__((weak, alias("UndefinedHandler")));
void irq_Trap1(void)             __attribute__((weak, alias("UndefinedHandler")));

//=============================================================================
// Interrupt vector table Core0
//=============================================================================
const InterruptHandler __attribute__((section(".intvect_core0"), aligned(4))) __INTVECT_Core0[] =
{
    /* 0 */  (InterruptHandler)&irq_Peripherals,
    /* 1 */  (InterruptHandler)&irq_Peripherals,
    /* 2 */  (InterruptHandler)&irq_Peripherals,
    /* 3 */  (InterruptHandler)&irq_Peripherals,
    /* 4 */  (InterruptHandler)&irq_Peripherals,
    /* 5 */  (InterruptHandler)&irq_Peripherals,
    /* 6 */  (InterruptHandler)&irq_Timer0,
    /* 7 */  (InterruptHandler)&irq_Trap0,
    /* 8 */  (InterruptHandler)&irq_Peripherals,
    /* 9 */  (InterruptHandler)&irq_Peripherals,
    /* 10 */ (InterruptHandler)&irq_Peripherals,
    /* 11 */ (InterruptHandler)&irq_Peripherals,
    /* 12 */ (InterruptHandler)&irq_Peripherals,
    /* 13 */ (InterruptHandler)&irq_Peripherals,
    /* 14 */ (InterruptHandler)&irq_Peripherals,
    /* 15 */ (InterruptHandler)&irq_Timer1,
    /* 16 */ (InterruptHandler)&irq_Timer2,
    /* 17 */ (InterruptHandler)&irq_Peripherals,
    /* 18 */ (InterruptHandler)&irq_Peripherals,
    /* 19 */ (InterruptHandler)&irq_Peripherals,
    /* 20 */ (InterruptHandler)&irq_Peripherals,
    /* 21 */ (InterruptHandler)&irq_Peripherals,
    /* 22 */ (InterruptHandler)&irq_Peripherals,
    /* 23 */ (InterruptHandler)&irq_Peripherals,
    /* 24 */ (InterruptHandler)&irq_Peripherals,
    /* 25 */ (InterruptHandler)&irq_Peripherals,
    /* 26 */ (InterruptHandler)&irq_Peripherals,
    /* 27 */ (InterruptHandler)&irq_Peripherals,
    /* 28 */ (InterruptHandler)&irq_Peripherals,
    /* 29 */ (InterruptHandler)&irq_Trap0,
    /* 30 */ (InterruptHandler)&irq_Peripherals,
    /* 31 */ (InterruptHandler)&irq_Peripherals
 };

//=============================================================================
// Interrupt vector table Core1
//=============================================================================
const InterruptHandler __attribute__((section(".intvect_core1"), aligned(4))) __INTVECT_Core1[] =
{
    /* 0 */  (InterruptHandler)&irq_Peripherals,
    /* 1 */  (InterruptHandler)&irq_Peripherals,
    /* 2 */  (InterruptHandler)&irq_Peripherals,
    /* 3 */  (InterruptHandler)&irq_Peripherals,
    /* 4 */  (InterruptHandler)&irq_Peripherals,
    /* 5 */  (InterruptHandler)&irq_Peripherals,
    /* 6 */  (InterruptHandler)&irq_Timer0,
    /* 7 */  (InterruptHandler)&irq_Trap0,
    /* 8 */  (InterruptHandler)&irq_Peripherals,
    /* 9 */  (InterruptHandler)&irq_Peripherals,
    /* 10 */ (InterruptHandler)&irq_Peripherals,
    /* 11 */ (InterruptHandler)&irq_Peripherals,
    /* 12 */ (InterruptHandler)&irq_Peripherals,
    /* 13 */ (InterruptHandler)&irq_Peripherals,
    /* 14 */ (InterruptHandler)&irq_Peripherals,
    /* 15 */ (InterruptHandler)&irq_Timer1,
    /* 16 */ (InterruptHandler)&irq_Timer2,
    /* 17 */ (InterruptHandler)&irq_Peripherals,
    /* 18 */ (InterruptHandler)&irq_Peripherals,
    /* 19 */ (InterruptHandler)&irq_Peripherals,
    /* 20 */ (InterruptHandler)&irq_Peripherals,
    /* 21 */ (InterruptHandler)&irq_Peripherals,
    /* 22 */ (InterruptHandler)&irq_Peripherals,
    /* 23 */ (InterruptHandler)&irq_Peripherals,
    /* 24 */ (InterruptHandler)&irq_Peripherals,
    /* 25 */ (InterruptHandler)&irq_Peripherals,
    /* 26 */ (InterruptHandler)&irq_Peripherals,
    /* 27 */ (InterruptHandler)&irq_Peripherals,
    /* 28 */ (InterruptHandler)&irq_Peripherals,
    /* 29 */ (InterruptHandler)&irq_Trap0,
    /* 30 */ (InterruptHandler)&irq_Peripherals,
    /* 31 */ (InterruptHandler)&irq_Peripherals
 };

#endif
