///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <array>
#include <mcal_cpu.h>

extern "C" void __initial_stack_pointer();

extern "C" void __my_startup();
extern "C" void __vector_unused_irq();
extern "C" void __nmi_handler        ();
extern "C" void __hard_fault_handler ();
extern "C" void __mem_manage_handler ();
extern "C" void __bus_fault_handler  ();
extern "C" void __usage_fault_handler();
extern "C" void __svc_handler        ();
extern "C" void __debug_mon_handler  ();
extern "C" void __pend_sv_handler    ();
extern "C" void __sys_tick_handler   ();
extern "C" void __timer4_irq_handler ();

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
}

extern "C"
const volatile std::array<isr_type, 116U> __isr_vector __attribute__((section(".isr_vector")));

extern "C"
const volatile std::array<isr_type, 116U> __isr_vector =
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
  __timer4_irq_handler,      // 0x00B8, TIM4 IRQ handler,
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
  __vector_unused_irq,       // 0x00EC, Reserved
  __vector_unused_irq,       // 0x00F0, Reserved
  __vector_unused_irq,       // 0x00F4, Reserved
  __vector_unused_irq,       // 0x00F8, Reserved
  __vector_unused_irq,       // 0x00FC, Reserved
  __vector_unused_irq,       // 0x0100, Reserved
  __vector_unused_irq,       // 0x0104, Reserved
  __vector_unused_irq,       // 0x0108, This is for boot in RAM mode for medium density devices.
  __vector_unused_irq,       // 0x010C, Unused
  __vector_unused_irq,       // 0x0110, Unused
  __vector_unused_irq,       // 0x0114, Unused
  __vector_unused_irq,       // 0x0118, Unused
  __vector_unused_irq,       // 0x011C, Unused
  __vector_unused_irq,       // 0x0120, Unused
  __vector_unused_irq,       // 0x0124, Unused
  __vector_unused_irq,       // 0x0128, Unused
  __vector_unused_irq,       // 0x012C, Unused
  __vector_unused_irq,       // 0x0130, Unused
  __vector_unused_irq,       // 0x0134, Unused
  __vector_unused_irq,       // 0x0138, Unused
  __vector_unused_irq,       // 0x013C, Unused
  __vector_unused_irq,       // 0x0140, Unused
  __vector_unused_irq,       // 0x0144, Unused
  __vector_unused_irq,       // 0x0148, Unused
  __vector_unused_irq,       // 0x014C, Unused
  __vector_unused_irq,       // 0x0150, Unused
  __vector_unused_irq,       // 0x0154, Unused
  __vector_unused_irq,       // 0x0158, Unused
  __vector_unused_irq,       // 0x015C, Unused
  __vector_unused_irq,       // 0x0160, Unused
  __vector_unused_irq,       // 0x0164, Unused
  __vector_unused_irq,       // 0x0168, Unused
  __vector_unused_irq,       // 0x016C, Unused
  __vector_unused_irq,       // 0x0170, Unused
  __vector_unused_irq,       // 0x0174, Unused
  __vector_unused_irq,       // 0x0178, Unused
  __vector_unused_irq,       // 0x017C, Unused
  __vector_unused_irq,       // 0x0180, Unused
  __vector_unused_irq,       // 0x0184, Unused
  __vector_unused_irq,       // 0x0188, Unused
  __vector_unused_irq,       // 0x018C, Unused
  __vector_unused_irq,       // 0x0190, Unused
  __vector_unused_irq,       // 0x0194, Unused
  __vector_unused_irq,       // 0x0198, Unused
  __vector_unused_irq,       // 0x019C, Unused
  __vector_unused_irq,       // 0x01A0, Unused
  __vector_unused_irq,       // 0x01A4, Unused
  __vector_unused_irq,       // 0x01A8, Unused
  __vector_unused_irq,       // 0x01AC, Unused
  __vector_unused_irq,       // 0x01B0, Unused
  __vector_unused_irq,       // 0x01B4, Unused
  __vector_unused_irq,       // 0x01B8, Unused
  __vector_unused_irq,       // 0x01BC, Unused
  __vector_unused_irq,       // 0x01C0, Unused
  __vector_unused_irq,       // 0x01C4, Unused
  __vector_unused_irq,       // 0x01C8, Unused
  __vector_unused_irq        // 0x01CC, Unused
}};
