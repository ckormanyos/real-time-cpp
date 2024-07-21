/******************************************************************************************
  Filename    : IntVect.c
  
  Core        : ARM Cortex-M0+
  
  MCU         : RP2040
    
  Author      : Chalandi Amine
 
  Owner       : Chalandi Amine
  
  Date        : 07.02.2023
  
  Description : Interrupt vector tables for Raspberry Pi Pico
  
******************************************************************************************/

//=============================================================================
// Types definition
//=============================================================================

extern "C"
{
  typedef void (*InterruptHandler)(void);
}

extern "C" void UndefinedHandler(void);
extern "C" void UndefinedHandler(void) { for(;;); }

//=============================================================================
// Functions prototype
//=============================================================================
extern "C" void __my_startup(void) __attribute__((used, noinline));
extern "C" void __main_core1(void) __attribute__((weak, alias("UndefinedHandler")));

extern "C" void __sys_tick_handler(void) noexcept __attribute__((used, noinline));

extern "C" void __CORE0_STACK_TOP(void);
extern "C" void __CORE1_STACK_TOP(void);

/* Default interrupts handler */
extern "C" void NMI(void)             __attribute__((weak, alias("UndefinedHandler")));
extern "C" void HardFault(void)       __attribute__((weak, alias("UndefinedHandler")));
extern "C" void SVCall(void)          __attribute__((weak, alias("UndefinedHandler")));
extern "C" void PendSV(void)          __attribute__((weak, alias("UndefinedHandler")));
extern "C" void SysTickTimer(void)    __attribute__((weak, alias("UndefinedHandler")));
extern "C" void TIMER_IRQ_0(void)     __attribute__((weak, alias("UndefinedHandler")));
extern "C" void TIMER_IRQ_1(void)     __attribute__((weak, alias("UndefinedHandler")));
extern "C" void TIMER_IRQ_2(void)     __attribute__((weak, alias("UndefinedHandler")));
extern "C" void TIMER_IRQ_3(void)     __attribute__((weak, alias("UndefinedHandler")));
extern "C" void PWM_IRQ_WRAP(void)    __attribute__((weak, alias("UndefinedHandler")));
extern "C" void USBCTRL_IRQ(void)     __attribute__((weak, alias("UndefinedHandler")));
extern "C" void XIP_IRQ(void)         __attribute__((weak, alias("UndefinedHandler")));
extern "C" void PIO0_IRQ_0(void)      __attribute__((weak, alias("UndefinedHandler")));
extern "C" void PIO0_IRQ_1(void)      __attribute__((weak, alias("UndefinedHandler")));
extern "C" void PIO1_IRQ_0(void)      __attribute__((weak, alias("UndefinedHandler")));
extern "C" void PIO1_IRQ_1(void)      __attribute__((weak, alias("UndefinedHandler")));
extern "C" void DMA_IRQ_0(void)       __attribute__((weak, alias("UndefinedHandler")));
extern "C" void DMA_IRQ_1(void)       __attribute__((weak, alias("UndefinedHandler")));
extern "C" void IO_IRQ_BANK0(void)    __attribute__((weak, alias("UndefinedHandler")));
extern "C" void IO_IRQ_QSPI(void)     __attribute__((weak, alias("UndefinedHandler")));
extern "C" void SIO_IRQ_PROC0(void)   __attribute__((weak, alias("UndefinedHandler")));
extern "C" void SIO_IRQ_PROC1(void)   __attribute__((weak, alias("UndefinedHandler")));
extern "C" void CLOCKS_IRQ(void)      __attribute__((weak, alias("UndefinedHandler")));
extern "C" void SPI0_IRQ(void)        __attribute__((weak, alias("UndefinedHandler")));
extern "C" void SPI1_IRQ(void)        __attribute__((weak, alias("UndefinedHandler")));
extern "C" void UART0_IRQ(void)       __attribute__((weak, alias("UndefinedHandler")));
extern "C" void UART1_IRQ(void)       __attribute__((weak, alias("UndefinedHandler")));
extern "C" void ADC_IRQ_FIFO(void)    __attribute__((weak, alias("UndefinedHandler")));
extern "C" void I2C0_IRQ(void)        __attribute__((weak, alias("UndefinedHandler")));
extern "C" void I2C1_IRQ(void)        __attribute__((weak, alias("UndefinedHandler")));
extern "C" void RTC_IRQ(void)         __attribute__((weak, alias("UndefinedHandler")));

//=============================================================================
// Interrupt vector table Core0
//=============================================================================
extern "C"
const InterruptHandler __attribute__((section(".intvect_c0"), aligned(128))) __INTVECT_Core0[48] =
{
   (InterruptHandler)&__CORE0_STACK_TOP,
   (InterruptHandler)&__my_startup,
   (InterruptHandler)&NMI,
   (InterruptHandler)&HardFault,
   (InterruptHandler)0,
   (InterruptHandler)0,
   (InterruptHandler)0,
   (InterruptHandler)0,
   (InterruptHandler)0,
   (InterruptHandler)0,
   (InterruptHandler)0,
   (InterruptHandler)&SVCall,
   (InterruptHandler)0,
   (InterruptHandler)0,
   (InterruptHandler)&PendSV,
   (InterruptHandler)&SysTickTimer,
   (InterruptHandler)&TIMER_IRQ_0,
   (InterruptHandler)&TIMER_IRQ_1,
   (InterruptHandler)&TIMER_IRQ_2,
   (InterruptHandler)&TIMER_IRQ_3,
   (InterruptHandler)&PWM_IRQ_WRAP,
   (InterruptHandler)&USBCTRL_IRQ,
   (InterruptHandler)&XIP_IRQ,
   (InterruptHandler)&PIO0_IRQ_0,
   (InterruptHandler)&PIO0_IRQ_1,
   (InterruptHandler)&PIO1_IRQ_0,
   (InterruptHandler)&PIO1_IRQ_1,
   (InterruptHandler)&DMA_IRQ_0,
   (InterruptHandler)&DMA_IRQ_1,
   (InterruptHandler)&IO_IRQ_BANK0,
   (InterruptHandler)&IO_IRQ_QSPI,
   (InterruptHandler)&SIO_IRQ_PROC0,
   (InterruptHandler)&SIO_IRQ_PROC1,
   (InterruptHandler)&CLOCKS_IRQ,
   (InterruptHandler)&SPI0_IRQ,
   (InterruptHandler)&SPI1_IRQ,
   (InterruptHandler)&UART0_IRQ,
   (InterruptHandler)&UART1_IRQ,
   (InterruptHandler)&ADC_IRQ_FIFO,
   (InterruptHandler)&I2C0_IRQ,
   (InterruptHandler)&I2C1_IRQ,
   (InterruptHandler)&RTC_IRQ,
   (InterruptHandler)0,
   (InterruptHandler)0,
   (InterruptHandler)0,
   (InterruptHandler)0,
   (InterruptHandler)0,
   (InterruptHandler)0
 };

//=============================================================================
// Interrupt vector table Core1
//=============================================================================
extern "C"
const InterruptHandler __attribute__((section(".intvect_c1"), aligned(128))) __INTVECT_Core1[48] =
{
   (InterruptHandler)&__CORE1_STACK_TOP,
   (InterruptHandler)&__main_core1,
   (InterruptHandler)&NMI,
   (InterruptHandler)&HardFault,
   (InterruptHandler)0,
   (InterruptHandler)0,
   (InterruptHandler)0,
   (InterruptHandler)0,
   (InterruptHandler)0,
   (InterruptHandler)0,
   (InterruptHandler)0,
   (InterruptHandler)&SVCall,
   (InterruptHandler)0,
   (InterruptHandler)0,
   (InterruptHandler)&PendSV,
   (InterruptHandler)&__sys_tick_handler,
   (InterruptHandler)&TIMER_IRQ_0,
   (InterruptHandler)&TIMER_IRQ_1,
   (InterruptHandler)&TIMER_IRQ_2,
   (InterruptHandler)&TIMER_IRQ_3,
   (InterruptHandler)&PWM_IRQ_WRAP,
   (InterruptHandler)&USBCTRL_IRQ,
   (InterruptHandler)&XIP_IRQ,
   (InterruptHandler)&PIO0_IRQ_0,
   (InterruptHandler)&PIO0_IRQ_1,
   (InterruptHandler)&PIO1_IRQ_0,
   (InterruptHandler)&PIO1_IRQ_1,
   (InterruptHandler)&DMA_IRQ_0,
   (InterruptHandler)&DMA_IRQ_1,
   (InterruptHandler)&IO_IRQ_BANK0,
   (InterruptHandler)&IO_IRQ_QSPI,
   (InterruptHandler)&SIO_IRQ_PROC0,
   (InterruptHandler)&SIO_IRQ_PROC1,
   (InterruptHandler)&CLOCKS_IRQ,
   (InterruptHandler)&SPI0_IRQ,
   (InterruptHandler)&SPI1_IRQ,
   (InterruptHandler)&UART0_IRQ,
   (InterruptHandler)&UART1_IRQ,
   (InterruptHandler)&ADC_IRQ_FIFO,
   (InterruptHandler)&I2C0_IRQ,
   (InterruptHandler)&I2C1_IRQ,
   (InterruptHandler)&RTC_IRQ,
   (InterruptHandler)0,
   (InterruptHandler)0,
   (InterruptHandler)0,
   (InterruptHandler)0,
   (InterruptHandler)0,
   (InterruptHandler)0
};
