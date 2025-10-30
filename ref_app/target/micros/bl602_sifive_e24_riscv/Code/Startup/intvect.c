/******************************************************************************************************
  Filename    : intvect.c
  
  Core        : RV32IMAFCB (SiFive E24 RISC-V)
  
  MCU         : BL602
    
  Author      : Chalandi Amine
 
  Owner       : Chalandi Amine
  
  Date        : 22.10.2025
  
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
void Isr_Ext_Interrupt     (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_CLIC_SW_Interrupt (void) __attribute__((weak, alias("UndefinedHandler")));
void L1C_BMX_ERR           (void) __attribute__((weak, alias("UndefinedHandler")));
void L1C_BMX_TO            (void) __attribute__((weak, alias("UndefinedHandler")));
void DMA_BMX_ERR           (void) __attribute__((weak, alias("UndefinedHandler")));
void IRTX                  (void) __attribute__((weak, alias("UndefinedHandler")));
void IRRX                  (void) __attribute__((weak, alias("UndefinedHandler")));
void GPADC_DMA             (void) __attribute__((weak, alias("UndefinedHandler")));
void SPI                   (void) __attribute__((weak, alias("UndefinedHandler")));
void UART0                 (void) __attribute__((weak, alias("UndefinedHandler")));
void UART1                 (void) __attribute__((weak, alias("UndefinedHandler")));
void I2C                   (void) __attribute__((weak, alias("UndefinedHandler")));
void PWM                   (void) __attribute__((weak, alias("UndefinedHandler")));
void TIMER_CH0             (void) __attribute__((weak, alias("UndefinedHandler")));
void TIMER_CH1             (void) __attribute__((weak, alias("UndefinedHandler")));
void TIMER_WDT             (void) __attribute__((weak, alias("UndefinedHandler")));
void GPIO_INT0             (void) __attribute__((weak, alias("UndefinedHandler")));
void PDS_WAKEUP            (void) __attribute__((weak, alias("UndefinedHandler")));
void HBN_OUT0              (void) __attribute__((weak, alias("UndefinedHandler")));
void HBN_OUT1              (void) __attribute__((weak, alias("UndefinedHandler")));

typedef void (*InterruptHandler)(void);

//=====================================================================================================
// Interrupt vector table
//=====================================================================================================
const InterruptHandler __attribute__((aligned(64))) InterruptVectorTable[] =
{
    (InterruptHandler)&UndefinedHandler,      /* IRQ 00  Reserved  */
    (InterruptHandler)&UndefinedHandler,      /* IRQ 01  Reserved  */
    (InterruptHandler)&UndefinedHandler,      /* IRQ 02  Reserved  */
    (InterruptHandler)&Isr_SW_Interrupt,      /* IRQ 03  SW Interrupt     */
    (InterruptHandler)&UndefinedHandler,      /* IRQ 04  Reserved  */
    (InterruptHandler)&UndefinedHandler,      /* IRQ 05  Reserved  */
    (InterruptHandler)&UndefinedHandler,      /* IRQ 06  Reserved  */
    (InterruptHandler)&Isr_TIMER_Interrupt,   /* IRQ 07  Timer Interrupt     */
    (InterruptHandler)&UndefinedHandler,      /* IRQ 08  Reserved  */
    (InterruptHandler)&UndefinedHandler,      /* IRQ 09  Reserved  */
    (InterruptHandler)&UndefinedHandler,      /* IRQ 10  Reserved  */
    (InterruptHandler)&Isr_Ext_Interrupt,     /* IRQ 11  External Interrupt  */
    (InterruptHandler)&Isr_CLIC_SW_Interrupt, /* IRQ 12  CLIC SW Interrupt  */
    (InterruptHandler)&UndefinedHandler,      /* IRQ 13  Reserved  */
    (InterruptHandler)&UndefinedHandler,      /* IRQ 14  Reserved  */
    (InterruptHandler)&UndefinedHandler,      /* IRQ 15  Reserved  */
    (InterruptHandler)&UndefinedHandler,      /* IRQ 16  Local Interrupt (IRQ_NUM_BASE + 00) */
    (InterruptHandler)&UndefinedHandler,      /* IRQ 17  Local Interrupt (IRQ_NUM_BASE + 01) */
    (InterruptHandler)&L1C_BMX_ERR,           /* IRQ 18  Local Interrupt (IRQ_NUM_BASE + 02) */
    (InterruptHandler)&L1C_BMX_TO,            /* IRQ 19  Local Interrupt (IRQ_NUM_BASE + 03) */
    (InterruptHandler)&UndefinedHandler,      /* IRQ 20  Local Interrupt (IRQ_NUM_BASE + 04) */
    (InterruptHandler)&UndefinedHandler,      /* IRQ 21  Local Interrupt (IRQ_NUM_BASE + 05) */
    (InterruptHandler)&UndefinedHandler,      /* IRQ 22  Local Interrupt (IRQ_NUM_BASE + 06) */
    (InterruptHandler)&UndefinedHandler,      /* IRQ 23  Local Interrupt (IRQ_NUM_BASE + 07) */
    (InterruptHandler)&DMA_BMX_ERR,           /* IRQ 24  Local Interrupt (IRQ_NUM_BASE + 08) */
    (InterruptHandler)&UndefinedHandler,      /* IRQ 25  Local Interrupt (IRQ_NUM_BASE + 09) */
    (InterruptHandler)&UndefinedHandler,      /* IRQ 26  Local Interrupt (IRQ_NUM_BASE + 10) */
    (InterruptHandler)&UndefinedHandler,      /* IRQ 27  Local Interrupt (IRQ_NUM_BASE + 11) */
    (InterruptHandler)&UndefinedHandler,      /* IRQ 28  Local Interrupt (IRQ_NUM_BASE + 12) */
    (InterruptHandler)&UndefinedHandler,      /* IRQ 29  Local Interrupt (IRQ_NUM_BASE + 13) */
    (InterruptHandler)&UndefinedHandler,      /* IRQ 30  Local Interrupt (IRQ_NUM_BASE + 14) */
    (InterruptHandler)&UndefinedHandler,      /* IRQ 31  Local Interrupt (IRQ_NUM_BASE + 15) */
    (InterruptHandler)&UndefinedHandler,      /* IRQ 32  Local Interrupt (IRQ_NUM_BASE + 16) */
    (InterruptHandler)&UndefinedHandler,      /* IRQ 33  Local Interrupt (IRQ_NUM_BASE + 17) */
    (InterruptHandler)&UndefinedHandler,      /* IRQ 34  Local Interrupt (IRQ_NUM_BASE + 18) */
    (InterruptHandler)&IRTX,                  /* IRQ 35  Local Interrupt (IRQ_NUM_BASE + 19) */
    (InterruptHandler)&IRRX,                  /* IRQ 36  Local Interrupt (IRQ_NUM_BASE + 20) */
    (InterruptHandler)&UndefinedHandler,      /* IRQ 37  Local Interrupt (IRQ_NUM_BASE + 21) */
    (InterruptHandler)&UndefinedHandler,      /* IRQ 38  Local Interrupt (IRQ_NUM_BASE + 22) */
    (InterruptHandler)&UndefinedHandler,      /* IRQ 39  Local Interrupt (IRQ_NUM_BASE + 23) */
    (InterruptHandler)&UndefinedHandler,      /* IRQ 40  Local Interrupt (IRQ_NUM_BASE + 24) */
    (InterruptHandler)&GPADC_DMA,             /* IRQ 41  Local Interrupt (IRQ_NUM_BASE + 25) */
    (InterruptHandler)&UndefinedHandler,      /* IRQ 42  Local Interrupt (IRQ_NUM_BASE + 26) */
    (InterruptHandler)&SPI,                   /* IRQ 43  Local Interrupt (IRQ_NUM_BASE + 27) */
    (InterruptHandler)&UndefinedHandler,      /* IRQ 44  Local Interrupt (IRQ_NUM_BASE + 28) */
    (InterruptHandler)&UART0,                 /* IRQ 45  Local Interrupt (IRQ_NUM_BASE + 29) */
    (InterruptHandler)&UART1,                 /* IRQ 46  Local Interrupt (IRQ_NUM_BASE + 30) */
    (InterruptHandler)&UndefinedHandler,      /* IRQ 47  Local Interrupt (IRQ_NUM_BASE + 31) */
    (InterruptHandler)&I2C,                   /* IRQ 48  Local Interrupt (IRQ_NUM_BASE + 32) */
    (InterruptHandler)&UndefinedHandler,      /* IRQ 49  Local Interrupt (IRQ_NUM_BASE + 33) */
    (InterruptHandler)&PWM,                   /* IRQ 50  Local Interrupt (IRQ_NUM_BASE + 34) */
    (InterruptHandler)&UndefinedHandler,      /* IRQ 51  Local Interrupt (IRQ_NUM_BASE + 35) */
    (InterruptHandler)&TIMER_CH0,             /* IRQ 52  Local Interrupt (IRQ_NUM_BASE + 36) */
    (InterruptHandler)&TIMER_CH1,             /* IRQ 53  Local Interrupt (IRQ_NUM_BASE + 37) */
    (InterruptHandler)&TIMER_WDT,             /* IRQ 54  Local Interrupt (IRQ_NUM_BASE + 38) */
    (InterruptHandler)&UndefinedHandler,      /* IRQ 55  Local Interrupt (IRQ_NUM_BASE + 39) */
    (InterruptHandler)&UndefinedHandler,      /* IRQ 56  Local Interrupt (IRQ_NUM_BASE + 40) */
    (InterruptHandler)&UndefinedHandler,      /* IRQ 57  Local Interrupt (IRQ_NUM_BASE + 41) */
    (InterruptHandler)&UndefinedHandler,      /* IRQ 58  Local Interrupt (IRQ_NUM_BASE + 42) */
    (InterruptHandler)&UndefinedHandler,      /* IRQ 59  Local Interrupt (IRQ_NUM_BASE + 43) */
    (InterruptHandler)&GPIO_INT0,             /* IRQ 60  Local Interrupt (IRQ_NUM_BASE + 44) */
    (InterruptHandler)&UndefinedHandler,      /* IRQ 61  Local Interrupt (IRQ_NUM_BASE + 45) */
    (InterruptHandler)&UndefinedHandler,      /* IRQ 62  Local Interrupt (IRQ_NUM_BASE + 46) */
    (InterruptHandler)&UndefinedHandler,      /* IRQ 63  Local Interrupt (IRQ_NUM_BASE + 47) */
    (InterruptHandler)&UndefinedHandler,      /* IRQ 64  Local Interrupt (IRQ_NUM_BASE + 48) */
    (InterruptHandler)&UndefinedHandler,      /* IRQ 65  Local Interrupt (IRQ_NUM_BASE + 49) */
    (InterruptHandler)&PDS_WAKEUP,            /* IRQ 66  Local Interrupt (IRQ_NUM_BASE + 50) */
    (InterruptHandler)&HBN_OUT0,              /* IRQ 67  Local Interrupt (IRQ_NUM_BASE + 51) */
    (InterruptHandler)&HBN_OUT1               /* IRQ 68  Local Interrupt (IRQ_NUM_BASE + 52) */
};
