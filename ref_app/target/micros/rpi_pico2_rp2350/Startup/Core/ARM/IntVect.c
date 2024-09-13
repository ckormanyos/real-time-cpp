/******************************************************************************************
  Filename    : IntVect.c
  
  Core        : ARM Cortex-M33
  
  MCU         : RP2350
    
  Author      : Chalandi Amine
 
  Owner       : Chalandi Amine
  
  Date        : 29.08.2024
  
  Description : Interrupt vector tables for RP2350
  
******************************************************************************************/

//=============================================================================
// Types definition
//=============================================================================
typedef void (*InterruptHandler)(void);

void UndefinedHandler(void);
void UndefinedHandler(void) { for(;;); }

//=============================================================================
// Functions prototype
//=============================================================================
void Startup_Init(void) __attribute__((used));
void main_Core1 (void) __attribute__((weak, alias("UndefinedHandler")));
void __CORE0_STACK_TOP(void);
void __CORE1_STACK_TOP(void);

/* Default interrupts handler */
void NMI(void)                   __attribute__((weak, alias("UndefinedHandler")));
void HardFault(void)             __attribute__((weak, alias("UndefinedHandler")));
void SVCall(void)                __attribute__((weak, alias("UndefinedHandler")));
void PendSV(void)                __attribute__((weak, alias("UndefinedHandler")));
void SysTickTimer(void)          __attribute__((weak, alias("UndefinedHandler")));
void TIMER0_IRQ_0_IRQn(void)     __attribute__((weak, alias("UndefinedHandler")));
void TIMER0_IRQ_1_IRQn(void)     __attribute__((weak, alias("UndefinedHandler")));
void TIMER0_IRQ_2_IRQn(void)     __attribute__((weak, alias("UndefinedHandler")));
void TIMER0_IRQ_3_IRQn(void)     __attribute__((weak, alias("UndefinedHandler")));
void TIMER1_IRQ_0_IRQn(void)     __attribute__((weak, alias("UndefinedHandler")));
void TIMER1_IRQ_1_IRQn(void)     __attribute__((weak, alias("UndefinedHandler")));
void TIMER1_IRQ_2_IRQn(void)     __attribute__((weak, alias("UndefinedHandler")));
void TIMER1_IRQ_3_IRQn(void)     __attribute__((weak, alias("UndefinedHandler")));
void PWM_IRQ_WRAP_0_IRQn(void)   __attribute__((weak, alias("UndefinedHandler")));
void PWM_IRQ_WRAP_1_IRQn(void)   __attribute__((weak, alias("UndefinedHandler")));
void DMA_IRQ_0_IRQn(void)        __attribute__((weak, alias("UndefinedHandler")));
void DMA_IRQ_1_IRQn(void)        __attribute__((weak, alias("UndefinedHandler")));
void DMA_IRQ_2_IRQn(void)        __attribute__((weak, alias("UndefinedHandler")));
void DMA_IRQ_3_IRQn(void)        __attribute__((weak, alias("UndefinedHandler")));
void USBCTRL_IRQ_IRQn(void)      __attribute__((weak, alias("UndefinedHandler")));
void PIO0_IRQ_0_IRQn(void)       __attribute__((weak, alias("UndefinedHandler")));
void PIO0_IRQ_1_IRQn(void)       __attribute__((weak, alias("UndefinedHandler")));
void PIO1_IRQ_0_IRQn(void)       __attribute__((weak, alias("UndefinedHandler")));
void PIO1_IRQ_1_IRQn(void)       __attribute__((weak, alias("UndefinedHandler")));
void PIO2_IRQ_0_IRQn(void)       __attribute__((weak, alias("UndefinedHandler")));
void PIO2_IRQ_1_IRQn(void)       __attribute__((weak, alias("UndefinedHandler")));
void IO_IRQ_BANK0_IRQn(void)     __attribute__((weak, alias("UndefinedHandler")));
void IO_IRQ_BANK0_NS_IRQn(void)  __attribute__((weak, alias("UndefinedHandler")));
void IO_IRQ_QSPI_IRQn(void)      __attribute__((weak, alias("UndefinedHandler")));
void IO_IRQ_QSPI_NS_IRQn(void)   __attribute__((weak, alias("UndefinedHandler")));
void SIO_IRQ_FIFO_IRQn(void)     __attribute__((weak, alias("UndefinedHandler")));
void SIO_IRQ_BELL_IRQn(void)     __attribute__((weak, alias("UndefinedHandler")));
void SIO_IRQ_FIFO_NS_IRQn(void)  __attribute__((weak, alias("UndefinedHandler")));
void SIO_IRQ_BELL_NS_IRQn(void)  __attribute__((weak, alias("UndefinedHandler")));
void SIO_IRQ_MTIMECMP_IRQn(void) __attribute__((weak, alias("UndefinedHandler")));
void CLOCKS_IRQ_IRQn(void)       __attribute__((weak, alias("UndefinedHandler")));
void SPI0_IRQ_IRQn(void)         __attribute__((weak, alias("UndefinedHandler")));
void SPI1_IRQ_IRQn(void)         __attribute__((weak, alias("UndefinedHandler")));
void UART0_IRQ_IRQn(void)        __attribute__((weak, alias("UndefinedHandler")));
void UART1_IRQ_IRQn(void)        __attribute__((weak, alias("UndefinedHandler")));
void ADC_IRQ_FIFO_IRQn(void)     __attribute__((weak, alias("UndefinedHandler")));
void I2C0_IRQ_IRQn(void)         __attribute__((weak, alias("UndefinedHandler")));
void I2C1_IRQ_IRQn(void)         __attribute__((weak, alias("UndefinedHandler")));
void OTP_IRQ_IRQn(void)          __attribute__((weak, alias("UndefinedHandler")));
void TRNG_IRQ_IRQn(void)         __attribute__((weak, alias("UndefinedHandler")));
void PLL_SYS_IRQ_IRQn(void)      __attribute__((weak, alias("UndefinedHandler")));
void PLL_USB_IRQ_IRQn(void)      __attribute__((weak, alias("UndefinedHandler")));
void POWMAN_IRQ_POW_IRQn(void)   __attribute__((weak, alias("UndefinedHandler")));
void POWMAN_IRQ_TIMER_IRQn(void) __attribute__((weak, alias("UndefinedHandler")));

//=============================================================================
// Interrupt vector table Core0
//=============================================================================
const InterruptHandler __attribute__((section(".intvect_c0"), used, aligned(128))) __INTVECT_Core0[] =
{
    (InterruptHandler)&__CORE0_STACK_TOP,
    (InterruptHandler)&Startup_Init,
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
    (InterruptHandler)&TIMER0_IRQ_0_IRQn,
    (InterruptHandler)&TIMER0_IRQ_1_IRQn,
    (InterruptHandler)&TIMER0_IRQ_2_IRQn,
    (InterruptHandler)&TIMER0_IRQ_3_IRQn,
    (InterruptHandler)&TIMER1_IRQ_0_IRQn,
    (InterruptHandler)&TIMER1_IRQ_1_IRQn,
    (InterruptHandler)&TIMER1_IRQ_2_IRQn,
    (InterruptHandler)&TIMER1_IRQ_3_IRQn,
    (InterruptHandler)&PWM_IRQ_WRAP_0_IRQn,
    (InterruptHandler)&PWM_IRQ_WRAP_1_IRQn,
    (InterruptHandler)&DMA_IRQ_0_IRQn,
    (InterruptHandler)&DMA_IRQ_1_IRQn,
    (InterruptHandler)&DMA_IRQ_2_IRQn,
    (InterruptHandler)&DMA_IRQ_3_IRQn,
    (InterruptHandler)&USBCTRL_IRQ_IRQn,
    (InterruptHandler)&PIO0_IRQ_0_IRQn,
    (InterruptHandler)&PIO0_IRQ_1_IRQn,
    (InterruptHandler)&PIO1_IRQ_0_IRQn,
    (InterruptHandler)&PIO1_IRQ_1_IRQn,
    (InterruptHandler)&PIO2_IRQ_0_IRQn,
    (InterruptHandler)&PIO2_IRQ_1_IRQn,
    (InterruptHandler)&IO_IRQ_BANK0_IRQn,
    (InterruptHandler)&IO_IRQ_BANK0_NS_IRQn,
    (InterruptHandler)&IO_IRQ_QSPI_IRQn,
    (InterruptHandler)&IO_IRQ_QSPI_NS_IRQn,
    (InterruptHandler)&SIO_IRQ_FIFO_IRQn,
    (InterruptHandler)&SIO_IRQ_BELL_IRQn,
    (InterruptHandler)&SIO_IRQ_FIFO_NS_IRQn,
    (InterruptHandler)&SIO_IRQ_BELL_NS_IRQn,
    (InterruptHandler)&SIO_IRQ_MTIMECMP_IRQn,
    (InterruptHandler)&CLOCKS_IRQ_IRQn,
    (InterruptHandler)&SPI0_IRQ_IRQn,
    (InterruptHandler)&SPI1_IRQ_IRQn,
    (InterruptHandler)&UART0_IRQ_IRQn,
    (InterruptHandler)&UART1_IRQ_IRQn,
    (InterruptHandler)&ADC_IRQ_FIFO_IRQn,
    (InterruptHandler)&I2C0_IRQ_IRQn,
    (InterruptHandler)&I2C1_IRQ_IRQn,
    (InterruptHandler)&OTP_IRQ_IRQn,
    (InterruptHandler)&TRNG_IRQ_IRQn,
    (InterruptHandler)&PLL_SYS_IRQ_IRQn,
    (InterruptHandler)&PLL_USB_IRQ_IRQn,
    (InterruptHandler)&POWMAN_IRQ_POW_IRQn,
    (InterruptHandler)&POWMAN_IRQ_TIMER_IRQn,
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
const InterruptHandler __attribute__((section(".intvect_c1"), used, aligned(128))) __INTVECT_Core1[] =
{
    (InterruptHandler)&__CORE1_STACK_TOP,
    (InterruptHandler)&main_Core1,
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
    (InterruptHandler)&TIMER0_IRQ_0_IRQn,
    (InterruptHandler)&TIMER0_IRQ_1_IRQn,
    (InterruptHandler)&TIMER0_IRQ_2_IRQn,
    (InterruptHandler)&TIMER0_IRQ_3_IRQn,
    (InterruptHandler)&TIMER1_IRQ_0_IRQn,
    (InterruptHandler)&TIMER1_IRQ_1_IRQn,
    (InterruptHandler)&TIMER1_IRQ_2_IRQn,
    (InterruptHandler)&TIMER1_IRQ_3_IRQn,
    (InterruptHandler)&PWM_IRQ_WRAP_0_IRQn,
    (InterruptHandler)&PWM_IRQ_WRAP_1_IRQn,
    (InterruptHandler)&DMA_IRQ_0_IRQn,
    (InterruptHandler)&DMA_IRQ_1_IRQn,
    (InterruptHandler)&DMA_IRQ_2_IRQn,
    (InterruptHandler)&DMA_IRQ_3_IRQn,
    (InterruptHandler)&USBCTRL_IRQ_IRQn,
    (InterruptHandler)&PIO0_IRQ_0_IRQn,
    (InterruptHandler)&PIO0_IRQ_1_IRQn,
    (InterruptHandler)&PIO1_IRQ_0_IRQn,
    (InterruptHandler)&PIO1_IRQ_1_IRQn,
    (InterruptHandler)&PIO2_IRQ_0_IRQn,
    (InterruptHandler)&PIO2_IRQ_1_IRQn,
    (InterruptHandler)&IO_IRQ_BANK0_IRQn,
    (InterruptHandler)&IO_IRQ_BANK0_NS_IRQn,
    (InterruptHandler)&IO_IRQ_QSPI_IRQn,
    (InterruptHandler)&IO_IRQ_QSPI_NS_IRQn,
    (InterruptHandler)&SIO_IRQ_FIFO_IRQn,
    (InterruptHandler)&SIO_IRQ_BELL_IRQn,
    (InterruptHandler)&SIO_IRQ_FIFO_NS_IRQn,
    (InterruptHandler)&SIO_IRQ_BELL_NS_IRQn,
    (InterruptHandler)&SIO_IRQ_MTIMECMP_IRQn,
    (InterruptHandler)&CLOCKS_IRQ_IRQn,
    (InterruptHandler)&SPI0_IRQ_IRQn,
    (InterruptHandler)&SPI1_IRQ_IRQn,
    (InterruptHandler)&UART0_IRQ_IRQn,
    (InterruptHandler)&UART1_IRQ_IRQn,
    (InterruptHandler)&ADC_IRQ_FIFO_IRQn,
    (InterruptHandler)&I2C0_IRQ_IRQn,
    (InterruptHandler)&I2C1_IRQ_IRQn,
    (InterruptHandler)&OTP_IRQ_IRQn,
    (InterruptHandler)&TRNG_IRQ_IRQn,
    (InterruptHandler)&PLL_SYS_IRQ_IRQn,
    (InterruptHandler)&PLL_USB_IRQ_IRQn,
    (InterruptHandler)&POWMAN_IRQ_POW_IRQn,
    (InterruptHandler)&POWMAN_IRQ_TIMER_IRQn,
    (InterruptHandler)0,
    (InterruptHandler)0,
    (InterruptHandler)0,
    (InterruptHandler)0,
    (InterruptHandler)0,
    (InterruptHandler)0
};
