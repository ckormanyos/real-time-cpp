///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <array>
#include <cstddef>
#include <mcal_cpu.h>

extern "C" void __initial_stack_pointer();

extern "C" void __my_startup         () __attribute__((used, noinline));
extern "C" void __vector_unused_irq  () __attribute__((used, noinline));
extern "C" void __nmi_handler        () __attribute__((used, noinline));
extern "C" void __hard_fault_handler () __attribute__((used, noinline));
extern "C" void __svc_handler        () __attribute__((used, noinline));
extern "C" void __pend_sv_handler    () __attribute__((used, noinline));
extern "C" void __sys_tick_handler   ();
extern "C" void __wdt_handler        ();

extern "C" void __vector_unused_irq  () { for(;;) { mcal::cpu::nop(); } }
extern "C" void __nmi_handler        () { for(;;) { mcal::cpu::nop(); } }
extern "C" void __hard_fault_handler () { for(;;) { mcal::cpu::nop(); } }
extern "C" void __svc_handler        () { for(;;) { mcal::cpu::nop(); } }
extern "C" void __pend_sv_handler    () { for(;;) { mcal::cpu::nop(); } }

namespace
{
  typedef void(*isr_type)();

  constexpr std::size_t number_of_interrupts = 48U;
}

extern "C"
const volatile std::array<isr_type, number_of_interrupts> __isr_vector __attribute__((section(".isr_vector")));

extern "C"
const volatile std::array<isr_type, number_of_interrupts> __isr_vector =
{{
  __initial_stack_pointer,   // 0x0000, initial stack pointer,
  __my_startup,              // 0x0004, reset,
  __nmi_handler,             // 0x0008, nmi exception,
  __hard_fault_handler,      // 0x000C, hard fault exception,
  __vector_unused_irq,       // 0x0010, memory management exception,
  __vector_unused_irq,       // 0x0014, bus fault exception,
  __vector_unused_irq,       // 0x0018, usage fault exception,
  __vector_unused_irq,       // 0x001C, reserved,
  __vector_unused_irq,       // 0x0020, reserved,
  __vector_unused_irq,       // 0x0024, reserved,
  __vector_unused_irq,       // 0x0028, reserved,
  __svc_handler,             // 0x002C, svc handler,
  __vector_unused_irq,       // 0x0030, reserved,
  __vector_unused_irq,       // 0x0034, reserved,
  __pend_sv_handler,         // 0x0038, pending svc,
  __sys_tick_handler,        // 0x003C, system tick handler,
  __vector_unused_irq,       // 0x0040, GPIO port 0, pin 0 irq handler,
  __vector_unused_irq,       // 0x0044, GPIO port 0, pin 1 irq handler,
  __vector_unused_irq,       // 0x0048, GPIO port 0, pin 2 irq handler,
  __vector_unused_irq,       // 0x004C, GPIO port 0, pin 3 irq handler,
  __vector_unused_irq,       // 0x0050, GPIO port 0, pin 4 irq handler,
  __vector_unused_irq,       // 0x0054, GPIO port 0, pin 5 irq handler,
  __vector_unused_irq,       // 0x0058, GPIO port 0, pin 6 irq handler,
  __vector_unused_irq,       // 0x005C, GPIO port 0, pin 7 irq handler,
  __vector_unused_irq,       // 0x0060, GPIO port 0, pin 8 irq handler,
  __vector_unused_irq,       // 0x0064, GPIO port 0, pin 9 irq handler,
  __vector_unused_irq,       // 0x0068, GPIO port 0, pin 10 irq handler,
  __vector_unused_irq,       // 0x006C, GPIO port 0, pin 11 irq handler,
  __vector_unused_irq,       // 0x0070, GPIO port 1, pin 0 irq handler,
  __vector_unused_irq,       // 0x0074, C_CAN irq handler,
  __vector_unused_irq,       // 0x0078, SSP1 irq handler,
  __vector_unused_irq,       // 0x007C, I2C irq handler,
  __vector_unused_irq,       // 0x0080, 16-bit Timer0 irq handler,
  __vector_unused_irq,       // 0x0084, 16-bit Timer1 irq handler,
  __vector_unused_irq,       // 0x0088, 32-bit Timer0 irq handler,
  __vector_unused_irq,       // 0x008C, 32-bit Timer1 irq handler,
  __vector_unused_irq,       // 0x0090, SSP0 irq handler,
  __vector_unused_irq,       // 0x0094, UART irq handler,
  __vector_unused_irq,       // 0x0098, reserved,
  __vector_unused_irq,       // 0x009C, reserved,
  __vector_unused_irq,       // 0x00A0, A/D Converter irq handler,
  __wdt_handler,             // 0x00A4, Watchdog timer irq handler,
  __vector_unused_irq,       // 0x00A8, Brown Out Detect(BOD) irq handler,
  __vector_unused_irq,       // 0x00AC, reserved,
  __vector_unused_irq,       // 0x00B0, External Interrupt 3 irq handler,
  __vector_unused_irq,       // 0x00B4, External Interrupt 2 irq handler,
  __vector_unused_irq,       // 0x00B8, External Interrupt 1 irq handler,
  __vector_unused_irq        // 0x00BC, External Interrupt 0 irq handler,
}};
