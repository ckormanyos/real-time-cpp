///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2021 - 2024.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_cpu.h>

#include <array>
#include <cstddef>
#include <cstdint>

namespace
{
  using isr_type = void(*)(void);

  constexpr auto number_of_interrupts = static_cast<std::size_t>(UINT8_C(104));
  constexpr auto number_of_exceptions = static_cast<std::size_t>(UINT8_C( 12));
}

extern "C"
{
  void UndefinedHandler(void);
  void Isr_HardFault   (void);
}

extern "C"
const volatile std::array<isr_type, number_of_interrupts> InterruptVectorTable __attribute__((section(".isr_vector"), aligned(4)));

extern "C"
const volatile std::array<isr_type, number_of_interrupts> InterruptVectorTable =
{{
  &UndefinedHandler, //   0  Reserved
  &UndefinedHandler, //   1  Reserved
  &UndefinedHandler, //   2  Non maskable Interrupt  cannot be stopped or preempted
  &Isr_HardFault,    //   3  Exception interrupt
  &UndefinedHandler, //   4  Reserved
  &UndefinedHandler, //   5  Callback interrupt in machine mode
  &UndefinedHandler, //   6  Reserved
  &UndefinedHandler, //   7  Reserved
  &UndefinedHandler, //   8  Callback interrupt in user mode
  &UndefinedHandler, //   9  Breakpoint callback interrupt
  &UndefinedHandler, //  10  Reserved
  &UndefinedHandler, //  11  Reserved
  &UndefinedHandler, //  12  System Tick Timer
  &UndefinedHandler, //  13  Reserved
  &UndefinedHandler, //  14  Software interrupt
  &UndefinedHandler, //  15  Reserved
  &UndefinedHandler, //  16  Window Watchdog interrupt
  &UndefinedHandler, //  17  PVD through EXTI line detection interrupt
  &UndefinedHandler, //  18  Tamper interrupt
  &UndefinedHandler, //  19  RTC global interrupt
  &UndefinedHandler, //  20  Flash global interrupt
  &UndefinedHandler, //  21  RCC global interrupt
  &UndefinedHandler, //  22  EXTI Line0 interrupt
  &UndefinedHandler, //  23  EXTI Line1 interrupt
  &UndefinedHandler, //  24  EXTI Line2 interrupt
  &UndefinedHandler, //  25  EXTI Line3 interrupt
  &UndefinedHandler, //  26  EXTI Line4 interrupt
  &UndefinedHandler, //  27  DMA1 Channel1 global interrupt
  &UndefinedHandler, //  28  DMA1 Channel2 global interrupt
  &UndefinedHandler, //  29  DMA1 Channel3 global interrupt
  &UndefinedHandler, //  30  DMA1 Channel4 global interrupt
  &UndefinedHandler, //  31  DMA1 Channel5 global interrupt
  &UndefinedHandler, //  32  DMA1 Channel6 global interrupt
  &UndefinedHandler, //  33  DMA1 Channel7 global interrupt
  &UndefinedHandler, //  34  ADC global interrupt
  &UndefinedHandler, //  35  CAN1 TX interrupts
  &UndefinedHandler, //  36  CAN1 RX0 interrupts
  &UndefinedHandler, //  37  CAN1 RX1 interrupt
  &UndefinedHandler, //  38  CAN1 SCE interrupt
  &UndefinedHandler, //  39  EXTI Line[9:5] interrupts
  &UndefinedHandler, //  40  TIM1 Break interrupt
  &UndefinedHandler, //  41  TIM1 Update interrupt
  &UndefinedHandler, //  42  TIM1 Trigger and Commutation interrupts
  &UndefinedHandler, //  43  TIM1 Capture Compare interrupt
  &UndefinedHandler, //  44  TIM2 global interrupt
  &UndefinedHandler, //  45  TIM3 global interrupt
  &UndefinedHandler, //  46  TIM4 global interrupt
  &UndefinedHandler, //  47  I2C1 event interrupt
  &UndefinedHandler, //  48  I2C1 error interrupt
  &UndefinedHandler, //  49  I2C2 event interrupt
  &UndefinedHandler, //  50  I2C2 error interrupt
  &UndefinedHandler, //  51  SPI1 global interrupt
  &UndefinedHandler, //  52  SPI2 global interrupt
  &UndefinedHandler, //  53  USART1 global interrupt
  &UndefinedHandler, //  54  USART2 global interrupt
  &UndefinedHandler, //  55  USART3 global interrupt
  &UndefinedHandler, //  56  EXTI Line[15:10] interrupts
  &UndefinedHandler, //  57  RTC Alarms through EXTI line interrupt
  &UndefinedHandler, //  58  USB Device WakeUp from suspend through EXTI Line Interrupt
  &UndefinedHandler, //  59  TIM8 Break interrupt
  &UndefinedHandler, //  60  TIM8 Update interrupt
  &UndefinedHandler, //  61  TIM8 Trigger and Commutation interrupts
  &UndefinedHandler, //  62  TIM8 Capture Compare interrupt
  &UndefinedHandler, //  63  RNG interrupt
  &UndefinedHandler, //  64  FSMC global interrupt
  &UndefinedHandler, //  65  SDIO global interrupt
  &UndefinedHandler, //  66  TIM5 global interrupt
  &UndefinedHandler, //  67  SPI3 global interrupt
  &UndefinedHandler, //  68  UART4 global interrupt
  &UndefinedHandler, //  69  UART5 global interrupt
  &UndefinedHandler, //  70  TIM6 Basic interrupt
  &UndefinedHandler, //  71  TIM8 Basic interrupt
  &UndefinedHandler, //  72  DMA2 Channel1 global interrupt
  &UndefinedHandler, //  73  DMA2 Channel2 global interrupt
  &UndefinedHandler, //  74  DMA2 Channel3 global interrupt
  &UndefinedHandler, //  75  DMA2 Channel4 global interrupt
  &UndefinedHandler, //  76  DMA2 Channel5 global interrupt
  &UndefinedHandler, //  77  Ethernet global interrupt
  &UndefinedHandler, //  78  Ethernet Wakeup through EXTI line interrupt
  &UndefinedHandler, //  79  CAN2 TX interrupts
  &UndefinedHandler, //  80  CAN2 RX0 interrupts
  &UndefinedHandler, //  81  CAN2 RX1 interrupt
  &UndefinedHandler, //  82  CAN2 SCE interrupt
  &UndefinedHandler, //  83  OTG_FS
  &UndefinedHandler, //  84  USBHSWakeup
  &UndefinedHandler, //  85  USBHS
  &UndefinedHandler, //  86  DVP global Interrupt interrupt
  &UndefinedHandler, //  87  UART6 global interrupt
  &UndefinedHandler, //  88  UART7 global interrupt
  &UndefinedHandler, //  89  UART8 global interrupt
  &UndefinedHandler, //  90  TIM9 Break interrupt
  &UndefinedHandler, //  91  TIM9 Update interrupt
  &UndefinedHandler, //  92  TIM9 Trigger and Commutation interrupts
  &UndefinedHandler, //  93  TIM9 Capture Compare interrupt
  &UndefinedHandler, //  94  TIM10 Break interrupt
  &UndefinedHandler, //  95  TIM10 Update interrupt
  &UndefinedHandler, //  96  TIM10 Trigger and Commutation interrupts
  &UndefinedHandler, //  97  TIM10 Capture Compare interrupt
  &UndefinedHandler, //  98  DMA2 Channel6 global interrupt
  &UndefinedHandler, //  99  DMA2 Channel7 global interrupt
  &UndefinedHandler, // 100  DMA2 Channel8 global interrupt
  &UndefinedHandler, // 101  DMA2 Channel9 global interrupt
  &UndefinedHandler, // 102  DMA2 Channel10 global interrupt
  &UndefinedHandler, // 103  DMA2 Channel11 global interrupt
}};

//=====================================================================================================
// Exception vector table
//=====================================================================================================
extern "C"
const volatile std::array<isr_type, number_of_exceptions> ExceptionVectorTable __attribute__((section(".isr_vector"), aligned(4)));

extern "C"
const volatile std::array<isr_type, number_of_exceptions> ExceptionVectorTable =
{{
  &UndefinedHandler,  // 0  Instruction address misaligned
  &UndefinedHandler,  // 1  Instruction access fault
  &UndefinedHandler,  // 2  Illegal instruction
  &UndefinedHandler,  // 3  Breakpoint
  &UndefinedHandler,  // 4  Load address misaligned
  &UndefinedHandler,  // 5  Load access fault
  &UndefinedHandler,  // 6  Store/AMO address misaligned
  &UndefinedHandler,  // 7  Store/AMO access fault
  &UndefinedHandler,  // 8  Environment call from U-mode
  &UndefinedHandler,  // 9  Reserved
  &UndefinedHandler,  // 10 Reserved
  &UndefinedHandler,  // 11 Environment call from M-mode
}};

extern "C"
{
  void UndefinedHandler(void)
  {
    for(;;) { mcal::cpu::nop(); }
  }

  void Isr_HardFault(void)
  {
    for(;;) { mcal::cpu::nop(); }
  }
}
