///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2023.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <array>
#include <cstddef>
#include <mcal_cpu.h>

extern "C" void __initial_stack_pointer();

extern "C" void __my_startup         () noexcept __attribute__((used, noinline));
extern "C" void __vector_unused_irq  () noexcept __attribute__((used, noinline));
extern "C" void __nmi_handler        () noexcept __attribute__((used, noinline));
extern "C" void __hard_fault_handler () noexcept __attribute__((used, noinline));
extern "C" void __mem_manage_handler () noexcept __attribute__((used, noinline));
extern "C" void __bus_fault_handler  () noexcept __attribute__((used, noinline));
extern "C" void __usage_fault_handler() noexcept __attribute__((used, noinline));
extern "C" void __svc_handler        () noexcept __attribute__((used, noinline));
extern "C" void __debug_mon_handler  () noexcept __attribute__((used, noinline));
extern "C" void __pend_sv_handler    () noexcept __attribute__((used, noinline));
extern "C" void __sys_tick_handler   () noexcept __attribute__((used, noinline));

extern "C" void __vector_unused_irq  () noexcept { for(;;) { mcal::cpu::nop(); } }
extern "C" void __nmi_handler        () noexcept { for(;;) { mcal::cpu::nop(); } }
extern "C" void __hard_fault_handler () noexcept { for(;;) { mcal::cpu::nop(); } }
extern "C" void __mem_manage_handler () noexcept { for(;;) { mcal::cpu::nop(); } }
extern "C" void __bus_fault_handler  () noexcept { for(;;) { mcal::cpu::nop(); } }
extern "C" void __usage_fault_handler() noexcept { for(;;) { mcal::cpu::nop(); } }
extern "C" void __svc_handler        () noexcept { for(;;) { mcal::cpu::nop(); } }
extern "C" void __debug_mon_handler  () noexcept { for(;;) { mcal::cpu::nop(); } }
extern "C" void __pend_sv_handler    () noexcept { for(;;) { mcal::cpu::nop(); } }

namespace
{
  typedef void(*isr_type)(void);

  constexpr auto number_of_interrupts = static_cast<std::size_t>(UINT8_C(64));
}

extern "C"
const volatile std::array<isr_type, number_of_interrupts> __isr_vector __attribute__((section(".isr_vector")));

extern "C"
const volatile std::array<isr_type, number_of_interrupts> __isr_vector =
{{
  __initial_stack_pointer,   // 0x0000, initial stack pointer
  __my_startup,              // 0x0004, reset
  __nmi_handler,             // 0x0008, nmi exception
  __hard_fault_handler,      // 0x000C, hard fault exception
  __mem_manage_handler,      // 0x0010, memory management exception
  __bus_fault_handler,       // 0x0014, bus fault exception
  __usage_fault_handler,     // 0x0018, usage fault exception
  __vector_unused_irq,       // 0x001C, reserved
  __vector_unused_irq,       // 0x0020, reserved
  __vector_unused_irq,       // 0x0024, reserved
  __vector_unused_irq,       // 0x0028, reserved
  __svc_handler,             // 0x002C, svc handler
  __debug_mon_handler,       // 0x0030, debug monitor
  __vector_unused_irq,       // 0x0034, reserved
  __pend_sv_handler,         // 0x0038, pending svc,
  __sys_tick_handler,        // 0x003C, system tick handler,
  __vector_unused_irq,       // 0x0040, wwdg irq handler,
  __vector_unused_irq,       // 0x0044, pvd irq handler,
  __vector_unused_irq,       // 0x0048, tamper irq handler,
  __vector_unused_irq,       // 0x004C, rtc irq handler,
  __vector_unused_irq,       // 0x0050, flash irq handler,
  __vector_unused_irq,       // 0x0054, rcc irq handler,
  __vector_unused_irq,       // 0x0058, exti0 irq handler,
  __vector_unused_irq,       // 0x005C, exti1 irq handler,
  __vector_unused_irq,       // 0x0060, exti2 irq handler,
  __vector_unused_irq,       // 0x0064, exti3 irq handler,
  __vector_unused_irq,       // 0x0068, exti4 irq handler,
  __vector_unused_irq,       // 0x006C, dma_channel1 irq handler,
  __vector_unused_irq,       // 0x0070, dma_channel2 irq handler,
  __vector_unused_irq,       // 0x0074, dma_channel3 irq handler,
  __vector_unused_irq,       // 0x0078, dma_channel4 irq handler,
  __vector_unused_irq,       // 0x007C, dma_channel5 irq handler,
  __vector_unused_irq,       // 0x0080, dma_channel6 irq handler,
  __vector_unused_irq,       // 0x0084, dma_channel7 irq handler,
  __vector_unused_irq,       // 0x0088, adc1 irq handler,
  __vector_unused_irq,       // 0x008C, usb_hp irq handler,
  __vector_unused_irq,       // 0x0090, usb_lp irq handler,
  __vector_unused_irq,       // 0x0094, dac irq handler,
  __vector_unused_irq,       // 0x0098, comp irq handler,
  __vector_unused_irq,       // 0x009C, exti9_5 irq handler,
  __vector_unused_irq,       // 0x00A0, lcd irq handler,
  __vector_unused_irq,       // 0x00A4, tim9 irq handler,
  __vector_unused_irq,       // 0x00A8, tim10 irq handler,
  __vector_unused_irq,       // 0x00AC, tim11 irq handler,
  __vector_unused_irq,       // 0x00B0, tim2 irq handler,
  __vector_unused_irq,       // 0x00B4, tim3 irq handler,
  __vector_unused_irq,       // 0x00B8, tim4 irq handler,
  __vector_unused_irq,       // 0x00BC, i2c1_ev irq handler,
  __vector_unused_irq,       // 0x00C0, i2c1_er irq handler,
  __vector_unused_irq,       // 0x00C4, i2c2_ev irq handler,
  __vector_unused_irq,       // 0x00C8, i2c2_er irq handler,
  __vector_unused_irq,       // 0x00CC, spi1 irq handler,
  __vector_unused_irq,       // 0x00D0, spi2 irq handler,
  __vector_unused_irq,       // 0x00D4, usart1 irq handler,
  __vector_unused_irq,       // 0x00D8, usart2 irq handler,
  __vector_unused_irq,       // 0x00DC, usart3 irq handler,
  __vector_unused_irq,       // 0x00E0, exti15_10 irq handler,
  __vector_unused_irq,       // 0x00E4, rtcalarm irq handler,
  __vector_unused_irq,       // 0x00E8, usb_fs_wakeup irq handler,
  __vector_unused_irq,       // 0x00EC, tim6 irq handler
  __vector_unused_irq,       // 0x00F0, tim7 irq handler
  nullptr,                   // 0x00F4, dummy
  nullptr,                   // 0x00F8, dummy
  nullptr,                   // 0x00FC, dummy
}};
