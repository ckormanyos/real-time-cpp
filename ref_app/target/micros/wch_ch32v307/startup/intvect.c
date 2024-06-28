/******************************************************************************************************
  Filename    : intvect.c
  
  Core        : QingKe V4 (RISC-V)
  
  MCU         : CH32V307VCT6 (WCH)
    
  Author      : Chalandi Amine
 
  Owner       : Chalandi Amine
  
  Date        : 20.01.2023
  
  Description : Interrupt vector table implementation
  
******************************************************************************************************/

static void UndefinedHandler(void);

void Isr_InstructionAddressMisaligned (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_InstructionAccessFault       (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_IllegalInstruction           (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_Breakpoint                   (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_LoadAddressMisaligned        (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_LoadAccessFault              (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_StoreAddressMisaligned       (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_StoreAccessFault             (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_EnvironmentCallFromUmode     (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_EnvironmentCallFromMmode     (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_HardFault                    (void);
void Isr_Ecall_M                      (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_Ecall_U                      (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_BreakPoint                   (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_NMI                          (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_SysTick                      (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_SoftwareInt                  (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_WWDG                         (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_PVD                          (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_TAMPER                       (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_RTC                          (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_FLASH                        (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_RCC                          (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_EXTI0                        (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_EXTI1                        (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_EXTI2                        (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_EXTI3                        (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_EXTI4                        (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_DMA1_Channel1                (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_DMA1_Channel2                (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_DMA1_Channel3                (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_DMA1_Channel4                (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_DMA1_Channel5                (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_DMA1_Channel6                (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_DMA1_Channel7                (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_ADC                          (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_USB_HP_CAN1_TX               (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_USB_LP_CAN1_RX0              (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_CAN1_RX1                     (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_CAN1_SCE                     (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_EXTI9_5                      (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_TIM1_BRK                     (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_TIM1_UP_                     (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_TIM1_TRG_COM                 (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_TIM1_CC                      (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_TIM2                         (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_TIM3                         (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_TIM4                         (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_I2C1_EV                      (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_I2C1_ER                      (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_I2C2_EV                      (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_I2C2_ER                      (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_SPI1                         (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_SPI2                         (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_USART1                       (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_USART2                       (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_USART3                       (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_EXTI15_10                    (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_RTCAlarm                     (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_USBWakeUp                    (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_TIM8_BRK                     (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_TIM8_UP_                     (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_TIM8_TRG_COM                 (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_TIM8_CC                      (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_RNG                          (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_FSMC                         (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_SDIO                         (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_TIM5                         (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_SPI3                         (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_UART4                        (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_UART5                        (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_TIM6                         (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_TIM7                         (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_DMA2_Channel1                (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_DMA2_Channel2                (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_DMA2_Channel3                (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_DMA2_Channel4                (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_DMA2_Channel5                (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_ETH                          (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_ETH_WKUP                     (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_CAN2_TX                      (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_CAN2_RX0                     (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_CAN2_RX1                     (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_CAN2_SCE                     (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_OTG_FS                       (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_USBHSWakeup                  (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_USBHS                        (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_DVP                          (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_UART6                        (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_UART7                        (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_UART8                        (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_TIM9_BRK                     (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_TIM9_UP_                     (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_TIM9_TRG_COM                 (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_TIM9_CC                      (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_TIM10_BRK                    (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_TIM10_UP                     (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_TIM10_TRG_COM                (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_TIM10_CC                     (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_DMA2_Channel6                (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_DMA2_Channel7                (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_DMA2_Channel8                (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_DMA2_Channel9                (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_DMA2_Channel10               (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_DMA2_Channel11               (void) __attribute__((weak, alias("UndefinedHandler")));

//=====================================================================================================
// Interrupt vector table
//=====================================================================================================
typedef void (*InterruptHandler)(void);

const InterruptHandler __attribute__((section(".intvect"), aligned(4))) InterruptVectorTable[] =
{
    (InterruptHandler)&UndefinedHandler,    /*   0  Reserved                                                   */
    (InterruptHandler)&UndefinedHandler,    /*   1  Reserved                                                   */
    (InterruptHandler)&Isr_NMI,             /*   2  Non maskable Interrupt  cannot be stopped or preempted     */
    (InterruptHandler)&Isr_HardFault,       /*   3  Exception interrupt                                        */
    (InterruptHandler)&UndefinedHandler,    /*   4  Reserved                                                   */
    (InterruptHandler)&Isr_Ecall_M,         /*   5  Callback interrupt in machine mode                         */
    (InterruptHandler)&UndefinedHandler,    /*   6  Reserved                                                   */
    (InterruptHandler)&UndefinedHandler,    /*   7  Reserved                                                   */
    (InterruptHandler)&Isr_Ecall_U,         /*   8  Callback interrupt in user mode                            */
    (InterruptHandler)&Isr_BreakPoint,      /*   9  Breakpoint callback interrupt                              */
    (InterruptHandler)&UndefinedHandler,    /*  10  Reserved                                                   */
    (InterruptHandler)&UndefinedHandler,    /*  11  Reserved                                                   */
    (InterruptHandler)&Isr_SysTick,         /*  12  System Tick Timer                                          */
    (InterruptHandler)&UndefinedHandler,    /*  13  Reserved                                                   */
    (InterruptHandler)&Isr_SoftwareInt,     /*  14  Software interrupt                                         */
    (InterruptHandler)&UndefinedHandler,    /*  15  Reserved                                                   */
    (InterruptHandler)&Isr_WWDG,            /*  16  Window Watchdog interrupt                                  */
    (InterruptHandler)&Isr_PVD,             /*  17  PVD through EXTI line detection interrupt                  */
    (InterruptHandler)&Isr_TAMPER,          /*  18  Tamper interrupt                                           */
    (InterruptHandler)&Isr_RTC,             /*  19  RTC global interrupt                                       */
    (InterruptHandler)&Isr_FLASH,           /*  20  Flash global interrupt                                     */
    (InterruptHandler)&Isr_RCC,             /*  21  RCC global interrupt                                       */
    (InterruptHandler)&Isr_EXTI0,           /*  22  EXTI Line0 interrupt                                       */
    (InterruptHandler)&Isr_EXTI1,           /*  23  EXTI Line1 interrupt                                       */
    (InterruptHandler)&Isr_EXTI2,           /*  24  EXTI Line2 interrupt                                       */
    (InterruptHandler)&Isr_EXTI3,           /*  25  EXTI Line3 interrupt                                       */
    (InterruptHandler)&Isr_EXTI4,           /*  26  EXTI Line4 interrupt                                       */
    (InterruptHandler)&Isr_DMA1_Channel1,   /*  27  DMA1 Channel1 global interrupt                             */
    (InterruptHandler)&Isr_DMA1_Channel2,   /*  28  DMA1 Channel2 global interrupt                             */
    (InterruptHandler)&Isr_DMA1_Channel3,   /*  29  DMA1 Channel3 global interrupt                             */
    (InterruptHandler)&Isr_DMA1_Channel4,   /*  30  DMA1 Channel4 global interrupt                             */
    (InterruptHandler)&Isr_DMA1_Channel5,   /*  31  DMA1 Channel5 global interrupt                             */
    (InterruptHandler)&Isr_DMA1_Channel6,   /*  32  DMA1 Channel6 global interrupt                             */
    (InterruptHandler)&Isr_DMA1_Channel7,   /*  33  DMA1 Channel7 global interrupt                             */
    (InterruptHandler)&Isr_ADC,             /*  34  ADC global interrupt                                       */
    (InterruptHandler)&Isr_USB_HP_CAN1_TX,  /*  35  CAN1 TX interrupts                                         */
    (InterruptHandler)&Isr_USB_LP_CAN1_RX0, /*  36  CAN1 RX0 interrupts                                        */
    (InterruptHandler)&Isr_CAN1_RX1,        /*  37  CAN1 RX1 interrupt                                         */
    (InterruptHandler)&Isr_CAN1_SCE,        /*  38  CAN1 SCE interrupt                                         */
    (InterruptHandler)&Isr_EXTI9_5,         /*  39  EXTI Line[9:5] interrupts                                  */
    (InterruptHandler)&Isr_TIM1_BRK,        /*  40  TIM1 Break interrupt                                       */
    (InterruptHandler)&Isr_TIM1_UP_,        /*  41  TIM1 Update interrupt                                      */
    (InterruptHandler)&Isr_TIM1_TRG_COM,    /*  42  TIM1 Trigger and Commutation interrupts                    */
    (InterruptHandler)&Isr_TIM1_CC,         /*  43  TIM1 Capture Compare interrupt                             */
    (InterruptHandler)&Isr_TIM2,            /*  44  TIM2 global interrupt                                      */
    (InterruptHandler)&Isr_TIM3,            /*  45  TIM3 global interrupt                                      */
    (InterruptHandler)&Isr_TIM4,            /*  46  TIM4 global interrupt                                      */
    (InterruptHandler)&Isr_I2C1_EV,         /*  47  I2C1 event interrupt                                       */
    (InterruptHandler)&Isr_I2C1_ER,         /*  48  I2C1 error interrupt                                       */
    (InterruptHandler)&Isr_I2C2_EV,         /*  49  I2C2 event interrupt                                       */
    (InterruptHandler)&Isr_I2C2_ER,         /*  50  I2C2 error interrupt                                       */
    (InterruptHandler)&Isr_SPI1,            /*  51  SPI1 global interrupt                                      */
    (InterruptHandler)&Isr_SPI2,            /*  52  SPI2 global interrupt                                      */
    (InterruptHandler)&Isr_USART1,          /*  53  USART1 global interrupt                                    */
    (InterruptHandler)&Isr_USART2,          /*  54  USART2 global interrupt                                    */
    (InterruptHandler)&Isr_USART3,          /*  55  USART3 global interrupt                                    */
    (InterruptHandler)&Isr_EXTI15_10,       /*  56  EXTI Line[15:10] interrupts                                */
    (InterruptHandler)&Isr_RTCAlarm,        /*  57  RTC Alarms through EXTI line interrupt                     */
    (InterruptHandler)&Isr_USBWakeUp,       /*  58  USB Device WakeUp from suspend through EXTI Line Interrupt */
    (InterruptHandler)&Isr_TIM8_BRK,        /*  59  TIM8 Break interrupt                                       */
    (InterruptHandler)&Isr_TIM8_UP_,        /*  60  TIM8 Update interrupt                                      */
    (InterruptHandler)&Isr_TIM8_TRG_COM,    /*  61  TIM8 Trigger and Commutation interrupts                    */
    (InterruptHandler)&Isr_TIM8_CC,         /*  62  TIM8 Capture Compare interrupt                             */
    (InterruptHandler)&Isr_RNG,             /*  63  RNG interrupt                                              */
    (InterruptHandler)&Isr_FSMC,            /*  64  FSMC global interrupt                                      */
    (InterruptHandler)&Isr_SDIO,            /*  65  SDIO global interrupt                                      */
    (InterruptHandler)&Isr_TIM5,            /*  66  TIM5 global interrupt                                      */
    (InterruptHandler)&Isr_SPI3,            /*  67  SPI3 global interrupt                                      */
    (InterruptHandler)&Isr_UART4,           /*  68  UART4 global interrupt                                     */
    (InterruptHandler)&Isr_UART5,           /*  69  UART5 global interrupt                                     */
    (InterruptHandler)&Isr_TIM6,            /*  70  TIM6 Basic interrupt                                       */
    (InterruptHandler)&Isr_TIM7,            /*  71  TIM8 Basic interrupt                                       */
    (InterruptHandler)&Isr_DMA2_Channel1,   /*  72  DMA2 Channel1 global interrupt                             */
    (InterruptHandler)&Isr_DMA2_Channel2,   /*  73  DMA2 Channel2 global interrupt                             */
    (InterruptHandler)&Isr_DMA2_Channel3,   /*  74  DMA2 Channel3 global interrupt                             */
    (InterruptHandler)&Isr_DMA2_Channel4,   /*  75  DMA2 Channel4 global interrupt                             */
    (InterruptHandler)&Isr_DMA2_Channel5,   /*  76  DMA2 Channel5 global interrupt                             */
    (InterruptHandler)&Isr_ETH,             /*  77  Ethernet global interrupt                                  */
    (InterruptHandler)&Isr_ETH_WKUP,        /*  78  Ethernet Wakeup through EXTI line interrupt                */
    (InterruptHandler)&Isr_CAN2_TX,         /*  79  CAN2 TX interrupts                                         */
    (InterruptHandler)&Isr_CAN2_RX0,        /*  80  CAN2 RX0 interrupts                                        */
    (InterruptHandler)&Isr_CAN2_RX1,        /*  81  CAN2 RX1 interrupt                                         */
    (InterruptHandler)&Isr_CAN2_SCE,        /*  82  CAN2 SCE interrupt                                         */
    (InterruptHandler)&Isr_OTG_FS,          /*  83  OTG_FS                                                     */
    (InterruptHandler)&Isr_USBHSWakeup,     /*  84  USBHSWakeup                                                */
    (InterruptHandler)&Isr_USBHS,           /*  85  USBHS                                                      */
    (InterruptHandler)&Isr_DVP,             /*  86  DVP global Interrupt interrupt                             */
    (InterruptHandler)&Isr_UART6,           /*  87  UART6 global interrupt                                     */
    (InterruptHandler)&Isr_UART7,           /*  88  UART7 global interrupt                                     */
    (InterruptHandler)&Isr_UART8,           /*  89  UART8 global interrupt                                     */
    (InterruptHandler)&Isr_TIM9_BRK,        /*  90  TIM9 Break interrupt                                       */
    (InterruptHandler)&Isr_TIM9_UP_,        /*  91  TIM9 Update interrupt                                      */
    (InterruptHandler)&Isr_TIM9_TRG_COM,    /*  92  TIM9 Trigger and Commutation interrupts                    */
    (InterruptHandler)&Isr_TIM9_CC,         /*  93  TIM9 Capture Compare interrupt                             */
    (InterruptHandler)&Isr_TIM10_BRK,       /*  94  TIM10 Break interrupt                                      */
    (InterruptHandler)&Isr_TIM10_UP,        /*  95  TIM10 Update interrupt                                     */
    (InterruptHandler)&Isr_TIM10_TRG_COM,   /*  96  TIM10 Trigger and Commutation interrupts                   */
    (InterruptHandler)&Isr_TIM10_CC,        /*  97  TIM10 Capture Compare interrupt                            */
    (InterruptHandler)&Isr_DMA2_Channel6,   /*  98  DMA2 Channel6 global interrupt                             */
    (InterruptHandler)&Isr_DMA2_Channel7,   /*  99  DMA2 Channel7 global interrupt                             */
    (InterruptHandler)&Isr_DMA2_Channel8,   /* 100  DMA2 Channel8 global interrupt                             */
    (InterruptHandler)&Isr_DMA2_Channel9,   /* 101  DMA2 Channel9 global interrupt                             */
    (InterruptHandler)&Isr_DMA2_Channel10,  /* 102  DMA2 Channel10 global interrupt                            */
    (InterruptHandler)&Isr_DMA2_Channel11,  /* 103  DMA2 Channel11 global interrupt                            */
};

//=====================================================================================================
// Exception vector table
//=====================================================================================================
const InterruptHandler __attribute__((section(".intvect"), aligned(4))) ExceptionVectorTable[] =
{
    (InterruptHandler)&Isr_InstructionAddressMisaligned,  /* 0  - Instruction address misaligned */
    (InterruptHandler)&Isr_InstructionAccessFault,        /* 1  - Instruction access fault       */
    (InterruptHandler)&Isr_IllegalInstruction,            /* 2  - Illegal instruction            */
    (InterruptHandler)&Isr_Breakpoint,                    /* 3  - Breakpoint                     */
    (InterruptHandler)&Isr_LoadAddressMisaligned,         /* 4  - Load address misaligned        */
    (InterruptHandler)&Isr_LoadAccessFault,               /* 5  - Load access fault              */
    (InterruptHandler)&Isr_StoreAddressMisaligned,        /* 6  - Store/AMO address misaligned   */
    (InterruptHandler)&Isr_StoreAccessFault,              /* 7  - Store/AMO access fault         */
    (InterruptHandler)&Isr_EnvironmentCallFromUmode,      /* 8  - Environment call from U-mode   */
    (InterruptHandler)&UndefinedHandler,                  /* 9  - Reserved                       */
    (InterruptHandler)&UndefinedHandler,                  /* 10 - Reserved                       */
    (InterruptHandler)&Isr_EnvironmentCallFromMmode,      /* 11 - Environment call from M-mode   */
};

//=====================================================================================================
// Implementation
//=====================================================================================================

//-----------------------------------------------------------------------------------------
/// \brief  
///
/// \param  
///
/// \return 
//-----------------------------------------------------------------------------------------
static void UndefinedHandler(void)
{
  for(;;) { ; }
}

void Isr_HardFault(void)
{
  for(;;) { ; }
}
