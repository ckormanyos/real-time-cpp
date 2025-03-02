///////////////////////////////////////////////////////////////////////////////
//  Copyright Amine Chalandi 2024.
//  Copyright Christopher Kormanyos 2024.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_cpu.h>

#include <array>
#include <cstddef>

extern "C" auto UndefinedHandler() -> void;
extern "C" auto UndefinedHandler() -> void { for(;;) { mcal::cpu::nop(); } }

extern "C" auto __my_startup() -> void __attribute__((section(".startup"), used, noinline));
extern "C" auto __main_core1() -> void __attribute__((section(".startup"), used, noinline));

extern "C" auto __sys_tick_handler() -> void __attribute__((used, noinline));

extern "C" auto __CORE0_STACK_TOP() -> void;
extern "C" auto __CORE1_STACK_TOP() -> void;

/* Default interrupts handler */
extern "C" auto NMI          () -> void __attribute__((weak, alias("UndefinedHandler")));
extern "C" auto HardFault    () -> void __attribute__((weak, alias("UndefinedHandler")));
extern "C" auto SVCall       () -> void __attribute__((weak, alias("UndefinedHandler")));
extern "C" auto PendSV       () -> void __attribute__((weak, alias("UndefinedHandler")));
extern "C" auto SysTickTimer () -> void __attribute__((weak, alias("UndefinedHandler")));
extern "C" auto TIMER_IRQ_0  () -> void __attribute__((weak, alias("UndefinedHandler")));
extern "C" auto TIMER_IRQ_1  () -> void __attribute__((weak, alias("UndefinedHandler")));
extern "C" auto TIMER_IRQ_2  () -> void __attribute__((weak, alias("UndefinedHandler")));
extern "C" auto TIMER_IRQ_3  () -> void __attribute__((weak, alias("UndefinedHandler")));
extern "C" auto PWM_IRQ_WRAP () -> void __attribute__((weak, alias("UndefinedHandler")));
extern "C" auto USBCTRL_IRQ  () -> void __attribute__((weak, alias("UndefinedHandler")));
extern "C" auto XIP_IRQ      () -> void __attribute__((weak, alias("UndefinedHandler")));
extern "C" auto PIO0_IRQ_0   () -> void __attribute__((weak, alias("UndefinedHandler")));
extern "C" auto PIO0_IRQ_1   () -> void __attribute__((weak, alias("UndefinedHandler")));
extern "C" auto PIO1_IRQ_0   () -> void __attribute__((weak, alias("UndefinedHandler")));
extern "C" auto PIO1_IRQ_1   () -> void __attribute__((weak, alias("UndefinedHandler")));
extern "C" auto DMA_IRQ_0    () -> void __attribute__((weak, alias("UndefinedHandler")));
extern "C" auto DMA_IRQ_1    () -> void __attribute__((weak, alias("UndefinedHandler")));
extern "C" auto IO_IRQ_BANK0 () -> void __attribute__((weak, alias("UndefinedHandler")));
extern "C" auto IO_IRQ_QSPI  () -> void __attribute__((weak, alias("UndefinedHandler")));
extern "C" auto SIO_IRQ_PROC0() -> void __attribute__((weak, alias("UndefinedHandler")));
extern "C" auto SIO_IRQ_PROC1() -> void __attribute__((weak, alias("UndefinedHandler")));
extern "C" auto CLOCKS_IRQ   () -> void __attribute__((weak, alias("UndefinedHandler")));
extern "C" auto SPI0_IRQ     () -> void __attribute__((weak, alias("UndefinedHandler")));
extern "C" auto SPI1_IRQ     () -> void __attribute__((weak, alias("UndefinedHandler")));
extern "C" auto UART0_IRQ    () -> void __attribute__((weak, alias("UndefinedHandler")));
extern "C" auto UART1_IRQ    () -> void __attribute__((weak, alias("UndefinedHandler")));
extern "C" auto ADC_IRQ_FIFO () -> void __attribute__((weak, alias("UndefinedHandler")));
extern "C" auto I2C0_IRQ     () -> void __attribute__((weak, alias("UndefinedHandler")));
extern "C" auto I2C1_IRQ     () -> void __attribute__((weak, alias("UndefinedHandler")));
extern "C" auto RTC_IRQ      () -> void __attribute__((weak, alias("UndefinedHandler")));

namespace local
{
  constexpr std::size_t number_of_interrupts { static_cast<std::size_t>(UINT8_C(48)) };
} // namespace local

extern "C"
{
  using isr_type = void(*)();

  extern "C"
  const volatile isr_type __attribute__((section(".intvect_c0"), aligned(128))) __INTVECT_Core0[local::number_of_interrupts];

  extern "C"
  const volatile isr_type __attribute__((section(".intvect_c1"), aligned(128))) __INTVECT_Core1[local::number_of_interrupts];
}

extern "C"
const volatile isr_type __INTVECT_Core0[local::number_of_interrupts] =
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
const volatile isr_type __INTVECT_Core1[local::number_of_interrupts] =
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
