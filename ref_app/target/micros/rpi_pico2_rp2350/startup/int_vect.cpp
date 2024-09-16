///////////////////////////////////////////////////////////////////////////////
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
extern "C" auto NMI                  () -> void __attribute__((weak, alias("UndefinedHandler")));
extern "C" auto HardFault            () -> void __attribute__((weak, alias("UndefinedHandler")));
extern "C" auto SVCall               () -> void __attribute__((weak, alias("UndefinedHandler")));
extern "C" auto PendSV               () -> void __attribute__((weak, alias("UndefinedHandler")));
extern "C" auto SysTickTimer         () -> void __attribute__((weak, alias("UndefinedHandler")));
extern "C" auto TIMER0_IRQ_0_IRQn    () -> void __attribute__((weak, alias("UndefinedHandler")));
extern "C" auto TIMER0_IRQ_1_IRQn    () -> void __attribute__((weak, alias("UndefinedHandler")));
extern "C" auto TIMER0_IRQ_2_IRQn    () -> void __attribute__((weak, alias("UndefinedHandler")));
extern "C" auto TIMER0_IRQ_3_IRQn    () -> void __attribute__((weak, alias("UndefinedHandler")));
extern "C" auto TIMER1_IRQ_0_IRQn    () -> void __attribute__((weak, alias("UndefinedHandler")));
extern "C" auto TIMER1_IRQ_1_IRQn    () -> void __attribute__((weak, alias("UndefinedHandler")));
extern "C" auto TIMER1_IRQ_2_IRQn    () -> void __attribute__((weak, alias("UndefinedHandler")));
extern "C" auto TIMER1_IRQ_3_IRQn    () -> void __attribute__((weak, alias("UndefinedHandler")));
extern "C" auto PWM_IRQ_WRAP_0_IRQn  () -> void __attribute__((weak, alias("UndefinedHandler")));
extern "C" auto PWM_IRQ_WRAP_1_IRQn  () -> void __attribute__((weak, alias("UndefinedHandler")));
extern "C" auto DMA_IRQ_0_IRQn       () -> void __attribute__((weak, alias("UndefinedHandler")));
extern "C" auto DMA_IRQ_1_IRQn       () -> void __attribute__((weak, alias("UndefinedHandler")));
extern "C" auto DMA_IRQ_2_IRQn       () -> void __attribute__((weak, alias("UndefinedHandler")));
extern "C" auto DMA_IRQ_3_IRQn       () -> void __attribute__((weak, alias("UndefinedHandler")));
extern "C" auto USBCTRL_IRQ_IRQn     () -> void __attribute__((weak, alias("UndefinedHandler")));
extern "C" auto PIO0_IRQ_0_IRQn      () -> void __attribute__((weak, alias("UndefinedHandler")));
extern "C" auto PIO0_IRQ_1_IRQn      () -> void __attribute__((weak, alias("UndefinedHandler")));
extern "C" auto PIO1_IRQ_0_IRQn      () -> void __attribute__((weak, alias("UndefinedHandler")));
extern "C" auto PIO1_IRQ_1_IRQn      () -> void __attribute__((weak, alias("UndefinedHandler")));
extern "C" auto PIO2_IRQ_0_IRQn      () -> void __attribute__((weak, alias("UndefinedHandler")));
extern "C" auto PIO2_IRQ_1_IRQn      () -> void __attribute__((weak, alias("UndefinedHandler")));
extern "C" auto IO_IRQ_BANK0_IRQn    () -> void __attribute__((weak, alias("UndefinedHandler")));
extern "C" auto IO_IRQ_BANK0_NS_IRQn () -> void __attribute__((weak, alias("UndefinedHandler")));
extern "C" auto IO_IRQ_QSPI_IRQn     () -> void __attribute__((weak, alias("UndefinedHandler")));
extern "C" auto IO_IRQ_QSPI_NS_IRQn  () -> void __attribute__((weak, alias("UndefinedHandler")));
extern "C" auto SIO_IRQ_FIFO_IRQn    () -> void __attribute__((weak, alias("UndefinedHandler")));
extern "C" auto SIO_IRQ_BELL_IRQn    () -> void __attribute__((weak, alias("UndefinedHandler")));
extern "C" auto SIO_IRQ_FIFO_NS_IRQn () -> void __attribute__((weak, alias("UndefinedHandler")));
extern "C" auto SIO_IRQ_BELL_NS_IRQn () -> void __attribute__((weak, alias("UndefinedHandler")));
extern "C" auto SIO_IRQ_MTIMECMP_IRQn() -> void __attribute__((weak, alias("UndefinedHandler")));
extern "C" auto CLOCKS_IRQ_IRQn      () -> void __attribute__((weak, alias("UndefinedHandler")));
extern "C" auto SPI0_IRQ_IRQn        () -> void __attribute__((weak, alias("UndefinedHandler")));
extern "C" auto SPI1_IRQ_IRQn        () -> void __attribute__((weak, alias("UndefinedHandler")));
extern "C" auto UART0_IRQ_IRQn       () -> void __attribute__((weak, alias("UndefinedHandler")));
extern "C" auto UART1_IRQ_IRQn       () -> void __attribute__((weak, alias("UndefinedHandler")));
extern "C" auto ADC_IRQ_FIFO_IRQn    () -> void __attribute__((weak, alias("UndefinedHandler")));
extern "C" auto I2C0_IRQ_IRQn        () -> void __attribute__((weak, alias("UndefinedHandler")));
extern "C" auto I2C1_IRQ_IRQn        () -> void __attribute__((weak, alias("UndefinedHandler")));
extern "C" auto OTP_IRQ_IRQn         () -> void __attribute__((weak, alias("UndefinedHandler")));
extern "C" auto TRNG_IRQ_IRQn        () -> void __attribute__((weak, alias("UndefinedHandler")));
extern "C" auto PLL_SYS_IRQ_IRQn     () -> void __attribute__((weak, alias("UndefinedHandler")));
extern "C" auto PLL_USB_IRQ_IRQn     () -> void __attribute__((weak, alias("UndefinedHandler")));
extern "C" auto POWMAN_IRQ_POW_IRQn  () -> void __attribute__((weak, alias("UndefinedHandler")));
extern "C" auto POWMAN_IRQ_TIMER_IRQn() -> void __attribute__((weak, alias("UndefinedHandler")));

namespace local
{
  constexpr std::size_t number_of_interrupts { static_cast<std::size_t>(UINT8_C(66)) };
} // namespace local

extern "C"
{
  using isr_type = void(*)(void);

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
  &TIMER0_IRQ_0_IRQn,
  &TIMER0_IRQ_1_IRQn,
  &TIMER0_IRQ_2_IRQn,
  &TIMER0_IRQ_3_IRQn,
  &TIMER1_IRQ_0_IRQn,
  &TIMER1_IRQ_1_IRQn,
  &TIMER1_IRQ_2_IRQn,
  &TIMER1_IRQ_3_IRQn,
  &PWM_IRQ_WRAP_0_IRQn,
  &PWM_IRQ_WRAP_1_IRQn,
  &DMA_IRQ_0_IRQn,
  &DMA_IRQ_1_IRQn,
  &DMA_IRQ_2_IRQn,
  &DMA_IRQ_3_IRQn,
  &USBCTRL_IRQ_IRQn,
  &PIO0_IRQ_0_IRQn,
  &PIO0_IRQ_1_IRQn,
  &PIO1_IRQ_0_IRQn,
  &PIO1_IRQ_1_IRQn,
  &PIO2_IRQ_0_IRQn,
  &PIO2_IRQ_1_IRQn,
  &IO_IRQ_BANK0_IRQn,
  &IO_IRQ_BANK0_NS_IRQn,
  &IO_IRQ_QSPI_IRQn,
  &IO_IRQ_QSPI_NS_IRQn,
  &SIO_IRQ_FIFO_IRQn,
  &SIO_IRQ_BELL_IRQn,
  &SIO_IRQ_FIFO_NS_IRQn,
  &SIO_IRQ_BELL_NS_IRQn,
  &SIO_IRQ_MTIMECMP_IRQn,
  &CLOCKS_IRQ_IRQn,
  &SPI0_IRQ_IRQn,
  &SPI1_IRQ_IRQn,
  &UART0_IRQ_IRQn,
  &UART1_IRQ_IRQn,
  &ADC_IRQ_FIFO_IRQn,
  &I2C0_IRQ_IRQn,
  &I2C1_IRQ_IRQn,
  &OTP_IRQ_IRQn,
  &TRNG_IRQ_IRQn,
  &PLL_SYS_IRQ_IRQn,
  &PLL_USB_IRQ_IRQn,
  &POWMAN_IRQ_POW_IRQn,
  &POWMAN_IRQ_TIMER_IRQn,
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
  &TIMER0_IRQ_0_IRQn,
  &TIMER0_IRQ_1_IRQn,
  &TIMER0_IRQ_2_IRQn,
  &TIMER0_IRQ_3_IRQn,
  &TIMER1_IRQ_0_IRQn,
  &TIMER1_IRQ_1_IRQn,
  &TIMER1_IRQ_2_IRQn,
  &TIMER1_IRQ_3_IRQn,
  &PWM_IRQ_WRAP_0_IRQn,
  &PWM_IRQ_WRAP_1_IRQn,
  &DMA_IRQ_0_IRQn,
  &DMA_IRQ_1_IRQn,
  &DMA_IRQ_2_IRQn,
  &DMA_IRQ_3_IRQn,
  &USBCTRL_IRQ_IRQn,
  &PIO0_IRQ_0_IRQn,
  &PIO0_IRQ_1_IRQn,
  &PIO1_IRQ_0_IRQn,
  &PIO1_IRQ_1_IRQn,
  &PIO2_IRQ_0_IRQn,
  &PIO2_IRQ_1_IRQn,
  &IO_IRQ_BANK0_IRQn,
  &IO_IRQ_BANK0_NS_IRQn,
  &IO_IRQ_QSPI_IRQn,
  &IO_IRQ_QSPI_NS_IRQn,
  &SIO_IRQ_FIFO_IRQn,
  &SIO_IRQ_BELL_IRQn,
  &SIO_IRQ_FIFO_NS_IRQn,
  &SIO_IRQ_BELL_NS_IRQn,
  &SIO_IRQ_MTIMECMP_IRQn,
  &CLOCKS_IRQ_IRQn,
  &SPI0_IRQ_IRQn,
  &SPI1_IRQ_IRQn,
  &UART0_IRQ_IRQn,
  &UART1_IRQ_IRQn,
  &ADC_IRQ_FIFO_IRQn,
  &I2C0_IRQ_IRQn,
  &I2C1_IRQ_IRQn,
  &OTP_IRQ_IRQn,
  &TRNG_IRQ_IRQn,
  &PLL_SYS_IRQ_IRQn,
  &PLL_USB_IRQ_IRQn,
  &POWMAN_IRQ_POW_IRQn,
  &POWMAN_IRQ_TIMER_IRQn,
  nullptr,
  nullptr,
  nullptr,
  nullptr,
  nullptr,
  nullptr
};
