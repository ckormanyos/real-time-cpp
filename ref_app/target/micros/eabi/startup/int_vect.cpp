///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_cpu.h>

extern "C" void _estack();
extern "C" void my_startup();

extern "C" void unused_irq_handler ();
extern "C" void nmi_handler        ();
extern "C" void hard_fault_handler ();
extern "C" void mem_manage_handler ();
extern "C" void bus_fault_handler  ();
extern "C" void usage_fault_handler();
extern "C" void svc_handler        ();
extern "C" void debug_mon_handler  ();
extern "C" void pend_sv_handler    ();
extern "C" void sys_tick_handler   ();
extern "C" void timer4_irq_handler ();

extern "C" void unused_irq_handler () { for(;;) { mcal::cpu::nop(); } }
extern "C" void nmi_handler        () { for(;;) { mcal::cpu::nop(); } }
extern "C" void hard_fault_handler () { for(;;) { mcal::cpu::nop(); } }
extern "C" void mem_manage_handler () { for(;;) { mcal::cpu::nop(); } }
extern "C" void bus_fault_handler  () { for(;;) { mcal::cpu::nop(); } }
extern "C" void usage_fault_handler() { for(;;) { mcal::cpu::nop(); } }
extern "C" void svc_handler        () { for(;;) { mcal::cpu::nop(); } }
extern "C" void debug_mon_handler  () { for(;;) { mcal::cpu::nop(); } }
extern "C" void pend_sv_handler    () { for(;;) { mcal::cpu::nop(); } }
extern "C" void sys_tick_handler   () { for(;;) { mcal::cpu::nop(); } }

struct isr
{
  typedef void(*function_type)();
};

extern "C"
const volatile isr::function_type __vectors[116U] __attribute__((section(".isr_vector"))) =
{
  _estack,                             // 0x0000, Initial stack pointer
  my_startup,                          // 0x0004, Reset handler
  nmi_handler,                         // 0x0008, NMIException
  hard_fault_handler,                  // 0x000C, HardFaultException
  mem_manage_handler,                  // 0x0010, MemManageException
  bus_fault_handler,                   // 0x0014, BusFaultException
  usage_fault_handler,                 // 0x0018, UsageFaultException
  nullptr,                             // 0x001C, Reserved
  nullptr,                             // 0x0020, Reserved
  nullptr,                             // 0x0024, Reserved
  nullptr,                             // 0x0028, Reserved
  svc_handler,                         // 0x002C, SVCHandler
  debug_mon_handler,                   // 0x0030, DebugMonitor
  nullptr,                             // 0x0034, Reserved
  pend_sv_handler,                     // 0x0038, PendSVC,
  sys_tick_handler,                    // 0x003C, SysTickHandler,
  unused_irq_handler,                  // 0x0040, WWDG_IRQHandler,
  unused_irq_handler,                  // 0x0044, PVD_IRQHandler,
  unused_irq_handler,                  // 0x0048, TAMPER_IRQHandler,
  unused_irq_handler,                  // 0x004C, RTC_IRQHandler,
  unused_irq_handler,                  // 0x0050, FLASH_IRQHandler,
  unused_irq_handler,                  // 0x0054, RCC_IRQHandler,
  unused_irq_handler,                  // 0x0058, EXTI0_IRQHandler,
  unused_irq_handler,                  // 0x005C, EXTI1_IRQHandler,
  unused_irq_handler,                  // 0x0060, EXTI2_IRQHandler,
  unused_irq_handler,                  // 0x0064, EXTI3_IRQHandler,
  unused_irq_handler,                  // 0x0068, EXTI4_IRQHandler,
  unused_irq_handler,                  // 0x006C, DMAChannel1_IRQHandler,
  unused_irq_handler,                  // 0x0070, DMAChannel2_IRQHandler,
  unused_irq_handler,                  // 0x0074, DMAChannel3_IRQHandler,
  unused_irq_handler,                  // 0x0078, DMAChannel4_IRQHandler,
  unused_irq_handler,                  // 0x007C, DMAChannel5_IRQHandler,
  unused_irq_handler,                  // 0x0080, DMAChannel6_IRQHandler,
  unused_irq_handler,                  // 0x0084, DMAChannel7_IRQHandler,
  unused_irq_handler,                  // 0x0088, ADC_IRQHandler,
  unused_irq_handler,                  // 0x008C, USB_HP_CAN_TX_IRQHandler,
  unused_irq_handler,                  // 0x0090, USB_LP_CAN_RX0_IRQHandler,
  unused_irq_handler,                  // 0x0094, CAN_RX1_IRQHandler,
  unused_irq_handler,                  // 0x0098, CAN_SCE_IRQHandler,
  unused_irq_handler,                  // 0x009C, EXTI9_5_IRQHandler,
  unused_irq_handler,                  // 0x00A0, TIM1_BRK_IRQHandler,
  unused_irq_handler,                  // 0x00A4, TIM1_UP_IRQHandler,
  unused_irq_handler,                  // 0x00A8, TIM1_TRG_COM_IRQHandler,
  unused_irq_handler,                  // 0x00AC, TIM1_CC_IRQHandler,
  unused_irq_handler,                  // 0x00B0, TIM2_IRQHandler,
  unused_irq_handler,                  // 0x00B4, TIM3_IRQHandler,
  timer4_irq_handler,                  // 0x00B8, TIM4_IRQHandler,
  unused_irq_handler,                  // 0x00BC, I2C1_EV_IRQHandler,
  unused_irq_handler,                  // 0x00C0, I2C1_ER_IRQHandler,
  unused_irq_handler,                  // 0x00C4, I2C2_EV_IRQHandler,
  unused_irq_handler,                  // 0x00C8, I2C2_ER_IRQHandler,
  unused_irq_handler,                  // 0x00CC, SPI1_IRQHandler,
  unused_irq_handler,                  // 0x00D0, SPI2_IRQHandler,
  unused_irq_handler,                  // 0x00D4, USART1_IRQHandler,
  unused_irq_handler,                  // 0x00D8, USART2_IRQHandler,
  unused_irq_handler,                  // 0x00DC, USART3_IRQHandler,
  unused_irq_handler,                  // 0x00E0, EXTI15_10_IRQHandler,
  unused_irq_handler,                  // 0x00E4, RTCAlarm_IRQHandler,
  unused_irq_handler,                  // 0x00E8, USBWakeUp_IRQHandler,
  nullptr,                             // 0x00EC, Reserved
  nullptr,                             // 0x00F0, Reserved
  nullptr,                             // 0x00F4, Reserved
  nullptr,                             // 0x00F8, Reserved
  nullptr,                             // 0x00FC, Reserved
  nullptr,                             // 0x0100, Reserved
  nullptr,                             // 0x0104, Reserved
  nullptr,                             // 0x0108 This is for boot in RAM mode for medium density devices.
  nullptr,                             // 0x010C, Unused
  nullptr, nullptr, nullptr, nullptr,  // 0x0110, Unused
  nullptr, nullptr, nullptr, nullptr,  // 0x0120, Unused
  nullptr, nullptr, nullptr, nullptr,  // 0x0130, Unused
  nullptr, nullptr, nullptr, nullptr,  // 0x0140, Unused
  nullptr, nullptr, nullptr, nullptr,  // 0x0150, Unused
  nullptr, nullptr, nullptr, nullptr,  // 0x0160, Unused
  nullptr, nullptr, nullptr, nullptr,  // 0x0170, Unused
  nullptr, nullptr, nullptr, nullptr,  // 0x0180, Unused
  nullptr, nullptr, nullptr, nullptr,  // 0x0190, Unused
  nullptr, nullptr, nullptr, nullptr,  // 0x01A0, Unused
  nullptr, nullptr, nullptr, nullptr,  // 0x01B0, Unused
  nullptr, nullptr, nullptr, nullptr   // 0x01C0, Unused
};
