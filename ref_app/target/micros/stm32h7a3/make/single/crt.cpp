///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2018 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <iterator>

// STM32 EABI ARM(R) Cortex-M4(TM) startup code.
// Expressed with C++ for STM32F446 by Chris.

// C:\Users\User\Documents\Ks\uC_Software\Boards\real-time-cpp\ref_app\tools\Util\MinGW\msys\1.0\local\gcc-9.3.1-arm-none-eabi\bin\arm-none-eabi-g++ -std=c++14 -Wall -Wextra -Wpedantic -O2 -g -gdwarf-2 -fno-exceptions -ffunction-sections -fdata-sections -x c++ -fno-rtti -fno-use-cxa-atexit -fno-exceptions -fno-nonansi-builtins -fno-threadsafe-statics -fno-enforce-eh-specs -ftemplate-depth=32 -mcpu=cortex-m4 -mtune=cortex-m4 -mthumb -mfloat-abi=soft -mno-unaligned-access -mno-long-calls -I./src/mcal/stm32f446 -I./src -DAPP_BENCHMARK_TYPE=APP_BENCHMARK_TYPE_CRC -DAPP_BENCHMARK_STANDALONE_MAIN ./src/app/benchmark/app_benchmark_crc.cpp ./target/micros/stm32f446/make/single/crt.cpp -nostartfiles -Wl,--gc-sections -Wl,-Map,./bin/app_benchmark_crc.map -T ./target/micros/stm32f446/make/stm32f446.ld -o ./bin/app_benchmark_crc.elf

namespace crt
{
  void init_ram();
}

namespace crt
{
  void init_ctors();
}

extern "C" void __my_startup() __attribute__((used, noinline));

void __my_startup()
{
  // Load the stack pointer.
  // The stack pointer is automatically loaded from
  // the base position of the interrupt vector table.
  // So we do nothing here.

  // TBD: Chip init: Watchdog, port, and oscillator, if any needed.

  // Initialize statics from ROM to RAM.
  // Zero-clear default-initialized static RAM.
  crt::init_ram();

  // Call all ctor initializations.
  crt::init_ctors();

  // Jump to main (and never return).
  asm volatile("ldr r3, =main");
  asm volatile("blx r3");

  exit(EXIT_SUCCESS);

  // TBD: Nothing on return from main.
}

extern "C" void _exit (int);

extern "C" void _exit (int) { }

extern "C"
{
  extern std::uintptr_t _rom_data_begin; // Start address for the initialization values of the rom-to-ram section.
  extern std::uintptr_t _data_begin;     // Start address for the .data section.
  extern std::uintptr_t _data_end;       // End address for the .data section.
  extern std::uintptr_t _bss_begin;      // Start address for the .bss section.
  extern std::uintptr_t _bss_end;        // End address for the .bss section.
}

void crt::init_ram()
{
  typedef std::uint32_t memory_aligned_type;

  // Copy the data segment initializers from ROM to RAM.
  // Note that all data segments are aligned by 4.
  const std::size_t size_data =
    std::size_t(  static_cast<const memory_aligned_type*>(static_cast<const void*>(&_data_end))
                - static_cast<const memory_aligned_type*>(static_cast<const void*>(&_data_begin)));

  std::copy(static_cast<const memory_aligned_type*>(static_cast<const void*>(&_rom_data_begin)),
            static_cast<const memory_aligned_type*>(static_cast<const void*>(&_rom_data_begin)) + size_data,
            static_cast<      memory_aligned_type*>(static_cast<      void*>(&_data_begin)));

  // Clear the bss segment.
  // Note that the bss segment is aligned by 4.
  std::fill(static_cast<memory_aligned_type*>(static_cast<void*>(&_bss_begin)),
            static_cast<memory_aligned_type*>(static_cast<void*>(&_bss_end)),
            static_cast<memory_aligned_type>(0U));
}

extern "C"
{
  struct ctor_type
  {
    typedef void(*function_type)();
    typedef std::reverse_iterator<const function_type*> const_reverse_iterator;
  };

  extern ctor_type::function_type _ctors_end[];
  extern ctor_type::function_type _ctors_begin[];
}

void crt::init_ctors()
{
  std::for_each(ctor_type::const_reverse_iterator(_ctors_end),
                ctor_type::const_reverse_iterator(_ctors_begin),
                [](const ctor_type::function_type pf)
                {
                  pf();
                });
}

extern "C" void __initial_stack_pointer();

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

extern "C" void __vector_unused_irq  () { for(;;) { ; } }
extern "C" void __nmi_handler        () { for(;;) { ; } }
extern "C" void __hard_fault_handler () { for(;;) { ; } }
extern "C" void __mem_manage_handler () { for(;;) { ; } }
extern "C" void __bus_fault_handler  () { for(;;) { ; } }
extern "C" void __usage_fault_handler() { for(;;) { ; } }
extern "C" void __svc_handler        () { for(;;) { ; } }
extern "C" void __debug_mon_handler  () { for(;;) { ; } }
extern "C" void __pend_sv_handler    () { for(;;) { ; } }
extern "C" void __sys_tick_handler   () { ; }

namespace
{
  typedef void(*isr_type)();

  constexpr std::size_t number_of_interrupts = 128U;
}

extern "C"
const volatile std::array<isr_type, number_of_interrupts> __isr_vector __attribute__((section(".isr_vector")));

// See pages 238-242 in the microcontroller manual.
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
  __vector_unused_irq,       // 0x0058, exti0 line0
  __vector_unused_irq,       // 0x005C, exti1 line1
  __vector_unused_irq,       // 0x0060, exti2 line2
  __vector_unused_irq,       // 0x0064, exti3 line3
  __vector_unused_irq,       // 0x0068, exti4 line4
  __vector_unused_irq,       // 0x006C, dma1 stream0
  __vector_unused_irq,       // 0x0070, dma1 stream1
  __vector_unused_irq,       // 0x0074, dma1 stream2
  __vector_unused_irq,       // 0x0078, dma1 stream3
  __vector_unused_irq,       // 0x007C, dma1 stream4
  __vector_unused_irq,       // 0x0080, dma1 stream5
  __vector_unused_irq,       // 0x0084, dma1 stream6
  __vector_unused_irq,       // 0x0088, adc1, adc2 and adc3 global
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
  __vector_unused_irq,       // 0x0134, reserved
  __vector_unused_irq,       // 0x0138, reserved
  __vector_unused_irq,       // 0x013C, can2_tx
  __vector_unused_irq,       // 0x0140, can2_rx0
  __vector_unused_irq,       // 0x0144, can2_rx1
  __vector_unused_irq,       // 0x0148, can2_sce
  __vector_unused_irq,       // 0x014C, usb on the go fs
  __vector_unused_irq,       // 0x0150, dma2 stream5
  __vector_unused_irq,       // 0x0154, dma2 stream6
  __vector_unused_irq,       // 0x0158, dma2 stream7
  __vector_unused_irq,       // 0x015C, usart6 usart6
  __vector_unused_irq,       // 0x0160, i2c3 event
  __vector_unused_irq,       // 0x0164, i2c3 error
  __vector_unused_irq,       // 0x0168, usb on the go hs end point 1 out
  __vector_unused_irq,       // 0x016C, usb on the go hs end point 1 in
  __vector_unused_irq,       // 0x0170, usb on the go hs wakeup through exti
  __vector_unused_irq,       // 0x0174, usb on the go hs
  __vector_unused_irq,       // 0x0178, dcmi
  __vector_unused_irq,       // 0x017C, reserved
  __vector_unused_irq,       // 0x0180, reserved
  __vector_unused_irq,       // 0x0184, fpu
  __vector_unused_irq,       // 0x0188, reserved
  __vector_unused_irq,       // 0x018C, reserved
  __vector_unused_irq,       // 0x0190, spi4
  __vector_unused_irq,       // 0x0194, reserved
  __vector_unused_irq,       // 0x0198, reserved
  __vector_unused_irq,       // 0x019C, sai1
  __vector_unused_irq,       // 0x01A0, reserved
  __vector_unused_irq,       // 0x01A4, reserved
  __vector_unused_irq,       // 0x01A8, reserved
  __vector_unused_irq,       // 0x01AC, sai2
  __vector_unused_irq,       // 0x01B0, quadspi
  __vector_unused_irq,       // 0x01B4, hdmi-cec
  __vector_unused_irq,       // 0x01B8, spdif-rx
  __vector_unused_irq,       // 0x01BC, fmpi2c1 event
  __vector_unused_irq,       // 0x01C0, fmpi2c1 error
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
