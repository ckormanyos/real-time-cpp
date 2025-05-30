﻿///////////////////////////////////////////////////////////////////////////////
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
  typedef void(*isr_type)();

  constexpr auto number_of_interrupts = static_cast<std::size_t>(UINT8_C(128));
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
  __pend_sv_handler,         // 0x0038, pending svc
  __sys_tick_handler,        // 0x003C, system tick handler
  __vector_unused_irq,       // 0x0040, window watchdog
  __vector_unused_irq,       // 0x0044, pvd through exti line detection
  __vector_unused_irq,       // 0x0048, tamp_stamp on exti line
  __vector_unused_irq,       // 0x004C, rtc_wkup wakeup through the exti line
  __vector_unused_irq,       // 0x0050, flash
  __vector_unused_irq,       // 0x0054, rcc
  __vector_unused_irq,       // 0x0058, exti0 irq handler
  __vector_unused_irq,       // 0x005C, exti1 irq handler
  __vector_unused_irq,       // 0x0060, exti2 irq handler
  __vector_unused_irq,       // 0x0064, exti3 irq handler
  __vector_unused_irq,       // 0x0068, exti4 irq handler
  __vector_unused_irq,       // 0x006C, dma_channel1 irq handler
  __vector_unused_irq,       // 0x0070, dma_channel2 irq handler
  __vector_unused_irq,       // 0x0074, dma_channel3 irq handler
  __vector_unused_irq,       // 0x0078, dma_channel4 irq handler
  __vector_unused_irq,       // 0x007C, dma_channel5 irq handler
  __vector_unused_irq,       // 0x0080, dma_channel6 irq handler
  __vector_unused_irq,       // 0x0084, dma_channel7 irq handler
  __vector_unused_irq,       // 0x0088, adc irq handler
  __vector_unused_irq,       // 0x008C, can1_tx
  __vector_unused_irq,       // 0x0090, can1_rx0
  __vector_unused_irq,       // 0x0094, can1_rx1
  __vector_unused_irq,       // 0x0098, can1_sce
  __vector_unused_irq,       // 0x009C, exti9_5 exti line[9:5]
  __vector_unused_irq,       // 0x00A0, tim1 break and tim9
  __vector_unused_irq,       // 0x00A4, tim1 update and tim10
  __vector_unused_irq,       // 0x00A8, tim1 trigger and commutation, and tim11
  __vector_unused_irq,       // 0x00AC, tim1 capture compare
  __vector_unused_irq,       // 0x00B0, tim2
  __vector_unused_irq,       // 0x00B4, tim3
  __vector_unused_irq,       // 0x00B8, tim4
  __vector_unused_irq,       // 0x00BC, i2c1 event
  __vector_unused_irq,       // 0x00C0, i2c1 error
  __vector_unused_irq,       // 0x00C4, i2c2 event
  __vector_unused_irq,       // 0x00C8, i2c2 error
  __vector_unused_irq,       // 0x00CC, spi1
  __vector_unused_irq,       // 0x00D0, spi2
  __vector_unused_irq,       // 0x00D4, usart1
  __vector_unused_irq,       // 0x00D8, usart2
  __vector_unused_irq,       // 0x00DC, usart3
  __vector_unused_irq,       // 0x00E0, exti line[15:10]
  __vector_unused_irq,       // 0x00E4, rtc alarms (a and b) through exti line
  __vector_unused_irq,       // 0x00E8, usb on-the-go fs wakeup through exti line
  __vector_unused_irq,       // 0x00EC, tim8 break and tim12
  __vector_unused_irq,       // 0x00F0, tim8 update and tim13
  __vector_unused_irq,       // 0x00F4, tim8 trigger and commutation, and tim14
  __vector_unused_irq,       // 0x00F8, tim8 capture compare
  __vector_unused_irq,       // 0x00FC, dma1_stream7
  __vector_unused_irq,       // 0x0100, fmc
  __vector_unused_irq,       // 0x0104, sdio
  __vector_unused_irq,       // 0x0108, tim5
  __vector_unused_irq,       // 0x010C, spi3
  __vector_unused_irq,       // 0x0110, uart4
  __vector_unused_irq,       // 0x0114, uart5
  __vector_unused_irq,       // 0x0118, tim6_dac, dac1 and dac2 underrun error
  __vector_unused_irq,       // 0x011C, tim7
  __vector_unused_irq,       // 0x0120, dma2 stream0
  __vector_unused_irq,       // 0x0124, dma2 stream1
  __vector_unused_irq,       // 0x0128, dma2 stream2
  __vector_unused_irq,       // 0x012C, dma2 stream3
  __vector_unused_irq,       // 0x0130, dma2 stream4
  __vector_unused_irq,       // 0x0134, ethernet
  __vector_unused_irq,       // 0x0138, ethernet wakeup through exti line
  __vector_unused_irq,       // 0x013C, can2 tx
  __vector_unused_irq,       // 0x0140, can2 rx0
  __vector_unused_irq,       // 0x0144, can2 rx1
  __vector_unused_irq,       // 0x0148, can2 sce
  __vector_unused_irq,       // 0x014C, usb otg fs
  __vector_unused_irq,       // 0x0150, dma2 stream5
  __vector_unused_irq,       // 0x0154, dma2 stream6
  __vector_unused_irq,       // 0x0158, dma2 stream7
  __vector_unused_irq,       // 0x015C, usart6
  __vector_unused_irq,       // 0x0160, i2c3 event
  __vector_unused_irq,       // 0x0164, i2c3 error
  __vector_unused_irq,       // 0x0168, usb on the go hs end point 1 out
  __vector_unused_irq,       // 0x016C, usb on the go hs end point 1 in
  __vector_unused_irq,       // 0x0170, usb on the go hs wakeup through exti
  __vector_unused_irq,       // 0x0174, usb on the go hs
  __vector_unused_irq,       // 0x0178, dcmi
  __vector_unused_irq,       // 0x017C, cryp crypto
  __vector_unused_irq,       // 0x0180, hash and rng
  __vector_unused_irq,       // 0x0184, fpu
  __vector_unused_irq,       // 0x0188, uart7
  __vector_unused_irq,       // 0x018C, uart8
  __vector_unused_irq,       // 0x0190, spi4
  __vector_unused_irq,       // 0x0194, spi5
  __vector_unused_irq,       // 0x0198, spi6
  __vector_unused_irq,       // 0x019C, sai1
  __vector_unused_irq,       // 0x01A0, reserved
  __vector_unused_irq,       // 0x01A4, reserved
  __vector_unused_irq,       // 0x01A8, dma2d
  nullptr,                   // 0x01AC, dummy
  nullptr,                   // 0x01B0, dummy
  nullptr,                   // 0x01B4, dummy
  nullptr,                   // 0x01B8, dummy
  nullptr,                   // 0x01BC, dummy
  nullptr,                   // 0x01C0, dummy
  nullptr,                   // 0x01C4, dummy
  nullptr,                   // 0x01C8, dummy
  nullptr,                   // 0x01CC, dummy
  nullptr,                   // 0x01D0, dummy
  nullptr,                   // 0x01D4, dummy
  nullptr,                   // 0x01D8, dummy
  nullptr,                   // 0x01DC, dummy
  nullptr,                   // 0x01E0, dummy
  nullptr,                   // 0x01E4, dummy
  nullptr,                   // 0x01E8, dummy
  nullptr,                   // 0x01EC, dummy
  nullptr,                   // 0x01F0, dummy
  nullptr,                   // 0x01F4, dummy
  nullptr,                   // 0x01F8, dummy
  nullptr                    // 0x01FC, dummy
}};
