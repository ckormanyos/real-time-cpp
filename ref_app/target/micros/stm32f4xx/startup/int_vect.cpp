///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <array>
#include <mcal_cpu.h>

extern "C" void __initial_stack_pointer();

extern "C" void __my_startup         () __attribute__((used, noinline));
extern "C" void __vector_unused_irq  () __attribute__((used, noinline));
extern "C" void __nmi_handler        () __attribute__((used, noinline));
extern "C" void __hard_fault_handler () __attribute__((used, noinline));
extern "C" void __mem_manage_handler () __attribute__((used, noinline));
extern "C" void __bus_fault_handler  () __attribute__((used, noinline));
extern "C" void __usage_fault_handler() __attribute__((used, noinline));
extern "C" void __svc_handler        () __attribute__((used, noinline));
extern "C" void __debug_mon_handler  () __attribute__((used, noinline));
extern "C" void __pend_sv_handler    () __attribute__((used, noinline));
extern "C" void __sys_tick_handler   () __attribute__((used, noinline));
extern "C" void __vector_timer4      ();

extern "C" void __vector_unused_irq  () { for(;;) { mcal::cpu::nop(); } }
extern "C" void __nmi_handler        () { for(;;) { mcal::cpu::nop(); } }
extern "C" void __hard_fault_handler () { for(;;) { mcal::cpu::nop(); } }
extern "C" void __mem_manage_handler () { for(;;) { mcal::cpu::nop(); } }
extern "C" void __bus_fault_handler  () { for(;;) { mcal::cpu::nop(); } }
extern "C" void __usage_fault_handler() { for(;;) { mcal::cpu::nop(); } }
extern "C" void __svc_handler        () { for(;;) { mcal::cpu::nop(); } }
extern "C" void __debug_mon_handler  () { for(;;) { mcal::cpu::nop(); } }
extern "C" void __pend_sv_handler    () { for(;;) { mcal::cpu::nop(); } }
extern "C" void __sys_tick_handler   () { for(;;) { mcal::cpu::nop(); } }

namespace
{
  typedef void(*isr_type)();

  constexpr std::size_t number_of_interrupts = 128U;
}

extern "C"
const volatile std::array<isr_type, number_of_interrupts> __isr_vector __attribute__((section(".isr_vector")));

extern "C"
const volatile std::array<isr_type, number_of_interrupts> __isr_vector =
{{
  __initial_stack_pointer,   // 0x0000, initial stack pointer
  __my_startup,              // 0x0004, reset
  __nmi_handler,             // 0x0008, NMI exception
  __hard_fault_handler,      // 0x000C, hard fault exception
  __mem_manage_handler,      // 0x0010, memory management exception
  __bus_fault_handler,       // 0x0014, bus fault exception
  __usage_fault_handler,     // 0x0018, usage fault exception
  __vector_unused_irq,       // 0x001C, reserved
  __vector_unused_irq,       // 0x0020, reserved
  __vector_unused_irq,       // 0x0024, reserved
  __vector_unused_irq,       // 0x0028, reserved
  __svc_handler,             // 0x002C, SVC handler
  __debug_mon_handler,       // 0x0030, debug monitor
  __vector_unused_irq,       // 0x0034, reserved
  __pend_sv_handler,         // 0x0038, pending SVC,
  __sys_tick_handler,        // 0x003C, system tick handler,
  __vector_unused_irq,       // 0x0040, WWDG IRQ handler,
  __vector_unused_irq,       // 0x0044, PVD IRQ handler,
  __vector_unused_irq,       // 0x0048, TAMPER IRQ handler,
  __vector_unused_irq,       // 0x004C, RTC IRQ handler,
  __vector_unused_irq,       // 0x0050, FLASH IRQ handler,
  __vector_unused_irq,       // 0x0054, RCC IRQ handler,
  __vector_unused_irq,       // 0x0058, EXTI0 IRQ handler,
  __vector_unused_irq,       // 0x005C, EXTI1 IRQ handler,
  __vector_unused_irq,       // 0x0060, EXTI2 IRQ handler,
  __vector_unused_irq,       // 0x0064, EXTI3 IRQ handler,
  __vector_unused_irq,       // 0x0068, EXTI4 IRQ handler,
  __vector_unused_irq,       // 0x006C, DMAChannel1 IRQ handler,
  __vector_unused_irq,       // 0x0070, DMAChannel2 IRQ handler,
  __vector_unused_irq,       // 0x0074, DMAChannel3 IRQ handler,
  __vector_unused_irq,       // 0x0078, DMAChannel4 IRQ handler,
  __vector_unused_irq,       // 0x007C, DMAChannel5 IRQ handler,
  __vector_unused_irq,       // 0x0080, DMAChannel6 IRQ handler,
  __vector_unused_irq,       // 0x0084, DMAChannel7 IRQ handler,
  __vector_unused_irq,       // 0x0088, ADC IRQ handler,
  __vector_unused_irq,       // 0x008C, USB_HP_CAN_TX IRQ handler,
  __vector_unused_irq,       // 0x0090, USB_LP_CAN_RX0 IRQ handler,
  __vector_unused_irq,       // 0x0094, CAN_RX1 IRQ handler,
  __vector_unused_irq,       // 0x0098, CAN_SCE IRQ handler,
  __vector_unused_irq,       // 0x009C, EXTI9_5 IRQ handler,
  __vector_unused_irq,       // 0x00A0, TIM1_BRK IRQ handler,
  __vector_unused_irq,       // 0x00A4, TIM1_UP IRQ handler,
  __vector_unused_irq,       // 0x00A8, TIM1_TRG_COM IRQ handler,
  __vector_unused_irq,       // 0x00AC, TIM1_CC IRQ handler,
  __vector_unused_irq,       // 0x00B0, TIM2 IRQ handler,
  __vector_unused_irq,       // 0x00B4, TIM3 IRQ handler,
  __vector_timer4,           // 0x00B8, TIM4 IRQ handler,
  __vector_unused_irq,       // 0x00BC, I2C1_EV IRQ handler,
  __vector_unused_irq,       // 0x00C0, I2C1_ER IRQ handler,
  __vector_unused_irq,       // 0x00C4, I2C2_EV IRQ handler,
  __vector_unused_irq,       // 0x00C8, I2C2_ER IRQ handler,
  __vector_unused_irq,       // 0x00CC, SPI1 IRQ handler,
  __vector_unused_irq,       // 0x00D0, SPI2 IRQ handler,
  __vector_unused_irq,       // 0x00D4, USART1 IRQ handler,
  __vector_unused_irq,       // 0x00D8, USART2 IRQ handler,
  __vector_unused_irq,       // 0x00DC, USART3 IRQ handler,
  __vector_unused_irq,       // 0x00E0, EXTI15_10 IRQ handler,
  __vector_unused_irq,       // 0x00E4, RTCAlarm IRQ handler,
  __vector_unused_irq,       // 0x00E8, USBWakeUp IRQ handler,
  __vector_unused_irq,       // 0x00EC, TIM8 Break and TIM12
  __vector_unused_irq,       // 0x00F0, TIM8 Update and TIM13
  __vector_unused_irq,       // 0x00F4, TIM8 Trigger and Commutation and TIM14
  __vector_unused_irq,       // 0x00F8, TIM8 Capture Compare
  __vector_unused_irq,       // 0x00FC, DMA1 Stream7
  __vector_unused_irq,       // 0x0100, FMC
  __vector_unused_irq,       // 0x0104, SDIO
  __vector_unused_irq,       // 0x0108, TIM5
  __vector_unused_irq,       // 0x010C, SPI3
  __vector_unused_irq,       // 0x0110, UART4
  __vector_unused_irq,       // 0x0114, UART5
  __vector_unused_irq,       // 0x0118, TIM6 and DAC1&2 underrun errors
  __vector_unused_irq,       // 0x011C, TIM7
  __vector_unused_irq,       // 0x0120, DMA2 Stream 0
  __vector_unused_irq,       // 0x0124, DMA2 Stream 1
  __vector_unused_irq,       // 0x0128, DMA2 Stream 2
  __vector_unused_irq,       // 0x012C, DMA2 Stream 3
  __vector_unused_irq,       // 0x0130, DMA2 Stream 4
  __vector_unused_irq,       // 0x0134, Ethernet
  __vector_unused_irq,       // 0x0138, Ethernet Wakeup through EXTI line
  __vector_unused_irq,       // 0x013C, CAN2 TX
  __vector_unused_irq,       // 0x0140, CAN2 RX0
  __vector_unused_irq,       // 0x0144, CAN2 RX1
  __vector_unused_irq,       // 0x0148, CAN2 SCE
  __vector_unused_irq,       // 0x014C, USB OTG FS
  __vector_unused_irq,       // 0x0150, DMA2 Stream 5
  __vector_unused_irq,       // 0x0154, DMA2 Stream 6
  __vector_unused_irq,       // 0x0158, DMA2 Stream 7
  __vector_unused_irq,       // 0x015C, USART6
  __vector_unused_irq,       // 0x0160, I2C3 event
  __vector_unused_irq,       // 0x0164, I2C3 error
  __vector_unused_irq,       // 0x0168, USB OTG HS End Point 1 Out
  __vector_unused_irq,       // 0x016C, USB OTG HS End Point 1 In
  __vector_unused_irq,       // 0x0170, USB OTG HS Wakeup through EXTI
  __vector_unused_irq,       // 0x0174, USB OTG HS
  __vector_unused_irq,       // 0x0178, DCMI
  __vector_unused_irq,       // 0x017C, CRYP crypto
  __vector_unused_irq,       // 0x0180, Hash and Rng
  __vector_unused_irq,       // 0x0184, FPU
  __vector_unused_irq,       // 0x0188, UART7
  __vector_unused_irq,       // 0x018C, UART8
  __vector_unused_irq,       // 0x0190, SPI4
  __vector_unused_irq,       // 0x0194, SPI5
  __vector_unused_irq,       // 0x0198, SPI6
  __vector_unused_irq,       // 0x019C, SAI1
  __vector_unused_irq,       // 0x01A0, Reserved
  __vector_unused_irq,       // 0x01A4, Reserved
  __vector_unused_irq,       // 0x01A8, DMA2D
  nullptr,                   // 0x01AC, Dummy
  nullptr,                   // 0x01B0, Dummy
  nullptr,                   // 0x01B4, Dummy
  nullptr,                   // 0x01B8, Dummy
  nullptr,                   // 0x01BC, Dummy
  nullptr,                   // 0x01C0, Dummy
  nullptr,                   // 0x01C4, Dummy
  nullptr,                   // 0x01C8, Dummy
  nullptr,                   // 0x01CC, Dummy
  nullptr,                   // 0x01D0, Dummy
  nullptr,                   // 0x01D4, Dummy
  nullptr,                   // 0x01D8, Dummy
  nullptr,                   // 0x01DC, Dummy
  nullptr,                   // 0x01E0, Dummy
  nullptr,                   // 0x01E4, Dummy
  nullptr,                   // 0x01E8, Dummy
  nullptr,                   // 0x01EC, Dummy
  nullptr,                   // 0x01F0, Dummy
  nullptr,                   // 0x01F4, Dummy
  nullptr,                   // 0x01F8, Dummy
  nullptr                    // 0x01FC, Dummy
}};
