///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2024.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <array>
#include <cstddef>
#include <mcal_cpu.h>

extern "C" void UndefinedHandler(void);
extern "C" void UndefinedHandler(void) { for(;;); }

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

namespace
{
  using isr_type = void(*)(void);

  constexpr auto number_of_interrupts = static_cast<std::size_t>(UINT8_C(48));
}

extern "C"
const volatile isr_type __attribute__((section(".intvect_c0"), aligned(128))) __INTVECT_Core0[number_of_interrupts];

extern "C"
const volatile isr_type __attribute__((section(".intvect_c1"), aligned(128))) __INTVECT_Core1[number_of_interrupts];

extern "C"
const volatile isr_type __INTVECT_Core0[number_of_interrupts] =
{
  &__CORE0_STACK_TOP,
  &__my_startup,
  &NMI,
  &HardFault,
  nullptr,
  nullptr,
  nullptr,
  nullptr,
  nullptr,
  nullptr,
  nullptr,
  &SVCall,
  nullptr,
  nullptr,
  &PendSV,
  &SysTickTimer,
  &TIMER_IRQ_0,
  &TIMER_IRQ_1,
  &TIMER_IRQ_2,
  &TIMER_IRQ_3,
  &PWM_IRQ_WRAP,
  &USBCTRL_IRQ,
  &XIP_IRQ,
  &PIO0_IRQ_0,
  &PIO0_IRQ_1,
  &PIO1_IRQ_0,
  &PIO1_IRQ_1,
  &DMA_IRQ_0,
  &DMA_IRQ_1,
  &IO_IRQ_BANK0,
  &IO_IRQ_QSPI,
  &SIO_IRQ_PROC0,
  &SIO_IRQ_PROC1,
  &CLOCKS_IRQ,
  &SPI0_IRQ,
  &SPI1_IRQ,
  &UART0_IRQ,
  &UART1_IRQ,
  &ADC_IRQ_FIFO,
  &I2C0_IRQ,
  &I2C1_IRQ,
  &RTC_IRQ,
  nullptr,
  nullptr,
  nullptr,
  nullptr,
  nullptr,
  nullptr
};

//=============================================================================
// Interrupt vector table Core1
//=============================================================================
extern "C"
const volatile isr_type __INTVECT_Core1[number_of_interrupts] =
{
  &__CORE1_STACK_TOP,
  &__main_core1,
  &NMI,
  &HardFault,
  nullptr,
  nullptr,
  nullptr,
  nullptr,
  nullptr,
  nullptr,
  nullptr,
  &SVCall,
  nullptr,
  nullptr,
  &PendSV,
  &__sys_tick_handler,
  &TIMER_IRQ_0,
  &TIMER_IRQ_1,
  &TIMER_IRQ_2,
  &TIMER_IRQ_3,
  &PWM_IRQ_WRAP,
  &USBCTRL_IRQ,
  &XIP_IRQ,
  &PIO0_IRQ_0,
  &PIO0_IRQ_1,
  &PIO1_IRQ_0,
  &PIO1_IRQ_1,
  &DMA_IRQ_0,
  &DMA_IRQ_1,
  &IO_IRQ_BANK0,
  &IO_IRQ_QSPI,
  &SIO_IRQ_PROC0,
  &SIO_IRQ_PROC1,
  &CLOCKS_IRQ,
  &SPI0_IRQ,
  &SPI1_IRQ,
  &UART0_IRQ,
  &UART1_IRQ,
  &ADC_IRQ_FIFO,
  &I2C0_IRQ,
  &I2C1_IRQ,
  &RTC_IRQ,
  nullptr,
  nullptr,
  nullptr,
  nullptr,
  nullptr,
  nullptr
};
