///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2026.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <array>
#include <cstdint>
#include <mcal_cpu.h>

extern "C" void __my_startup       () __attribute__((section(".startup"), used, noinline));
extern "C" void __vector_unused_irq() __attribute__((signal, used, externally_visible));
extern "C" void __vector_23        () __attribute__((signal, used, externally_visible));

extern "C"
void __vector_unused_irq()
{
  for(;;)
  {
    mcal::cpu::nop();
  }
}

extern "C" void __isr_vector() __attribute__((naked,used,noinline,section(".isr_vector")));

extern "C" void __isr_vector()
{
  // Use explicit .org and jmp instructions, where the .org addresses
  // retain direct 22-bit jumps, even with -mrelax. For a quick check
  // in map-like files, verify that the size of __isr_vector is 0xF4.

  asm volatile
  (
    ".org 0x00 \n\t jmp  __my_startup        ; 0x00,  0   reset                           \n\t"
    ".org 0x04 \n\t jmp  __vector_unused_irq ; 0x02,  1   external interrupt0             \n\t"
    ".org 0x08 \n\t jmp  __vector_unused_irq ; 0x04,  2   external interrupt1             \n\t"
    ".org 0x0C \n\t jmp  __vector_unused_irq ; 0x06,  3   external interrupt2             \n\t"
    ".org 0x10 \n\t jmp  __vector_unused_irq ; 0x08,  4   external interrupt3             \n\t"
    ".org 0x14 \n\t jmp  __vector_unused_irq ; 0x0A,  5   external interrupt4             \n\t"
    ".org 0x18 \n\t jmp  __vector_unused_irq ; 0x0C,  6   external interrupt5             \n\t"
    ".org 0x1C \n\t jmp  __vector_unused_irq ; 0x0E,  7   external interrupt6             \n\t"
    ".org 0x20 \n\t jmp  __vector_unused_irq ; 0x10,  8   external interrupt7             \n\t"
    ".org 0x24 \n\t jmp  __vector_unused_irq ; 0x12,  9   pin change int request0         \n\t"
    ".org 0x28 \n\t jmp  __vector_unused_irq ; 0x14, 10   pin change int request1         \n\t"
    ".org 0x2C \n\t jmp  __vector_unused_irq ; 0x16, 11   pin change int request2         \n\t"
    ".org 0x30 \n\t jmp  __vector_unused_irq ; 0x18, 12   Watchdog Timer Interrupt        \n\t"
    ".org 0x34 \n\t jmp  __vector_unused_irq ; 0x1A, 13   timer/counter2 compare A        \n\t"
    ".org 0x38 \n\t jmp  __vector_unused_irq ; 0x1C, 14   timer/counter2 compare B        \n\t"
    ".org 0x3C \n\t jmp  __vector_unused_irq ; 0x1E, 15   timer/counter2 overflow         \n\t"
    ".org 0x40 \n\t jmp  __vector_unused_irq ; 0x20, 16   timer/counter1 capture          \n\t"
    ".org 0x44 \n\t jmp  __vector_unused_irq ; 0x22, 17   timer/counter1 compare A        \n\t"
    ".org 0x48 \n\t jmp  __vector_unused_irq ; 0x24, 18   timer/counter1 compare B        \n\t"
    ".org 0x4C \n\t jmp  __vector_unused_irq ; 0x26, 19   timer/counter1 compare C        \n\t"
    ".org 0x50 \n\t jmp  __vector_unused_irq ; 0x28, 20   timer/counter1 overflow         \n\t"
    ".org 0x54 \n\t jmp  __vector_unused_irq ; 0x2A, 21   timer/counter0 compare A        \n\t"
    ".org 0x58 \n\t jmp  __vector_unused_irq ; 0x2C, 22   timer/counter0 compare B        \n\t"
    ".org 0x5C \n\t jmp  __vector_23         ; 0x2E, 23   timer/counter0 overflow         \n\t"
    ".org 0x60 \n\t jmp  __vector_unused_irq ; 0x30, 24   spi serial transfer cComplete   \n\t"
    ".org 0x64 \n\t jmp  __vector_unused_irq ; 0x32, 25   uart0 rx complete               \n\t"
    ".org 0x68 \n\t jmp  __vector_unused_irq ; 0x34, 26   uart0 data register empty       \n\t"
    ".org 0x6C \n\t jmp  __vector_unused_irq ; 0x36, 27   uart0 tx complete               \n\t"
    ".org 0x70 \n\t jmp  __vector_unused_irq ; 0x38, 28   analog comparator               \n\t"
    ".org 0x74 \n\t jmp  __vector_unused_irq ; 0x3A, 29   adc conversion complete         \n\t"
    ".org 0x78 \n\t jmp  __vector_unused_irq ; 0x3C, 30   eeprom ready                    \n\t"
    ".org 0x7C \n\t jmp  __vector_unused_irq ; 0x3E, 31   timer/counter3 capture event    \n\t"
    ".org 0x80 \n\t jmp  __vector_unused_irq ; 0x40, 32   timer/counter3 compare match a  \n\t"
    ".org 0x84 \n\t jmp  __vector_unused_irq ; 0x42, 33   timer/counter3 compare match b  \n\t"
    ".org 0x88 \n\t jmp  __vector_unused_irq ; 0x44, 34   timer/counter3 compare match c  \n\t"
    ".org 0x8C \n\t jmp  __vector_unused_irq ; 0x46, 35   timer/counter3 overflow         \n\t"
    ".org 0x90 \n\t jmp  __vector_unused_irq ; 0x48, 36   uart1 rx complete               \n\t"
    ".org 0x94 \n\t jmp  __vector_unused_irq ; 0x4A, 37   uart1 data register empty       \n\t"
    ".org 0x98 \n\t jmp  __vector_unused_irq ; 0x4C, 38   uart1 tx complete               \n\t"
    ".org 0x9C \n\t jmp  __vector_unused_irq ; 0x4E, 39   2 wire serial interface         \n\t"
    ".org 0xA0 \n\t jmp  __vector_unused_irq ; 0x50, 40   store program memory ready      \n\t"
    ".org 0xA4 \n\t jmp  __vector_unused_irq ; 0x52, 41   timer/counter4 captureevent     \n\t"
    ".org 0xA8 \n\t jmp  __vector_unused_irq ; 0x54, 42   timer/counter4 compare a        \n\t"
    ".org 0xAC \n\t jmp  __vector_unused_irq ; 0x56, 43   timer/counter4 compare b        \n\t"
    ".org 0xB0 \n\t jmp  __vector_unused_irq ; 0x58, 44   timer/counter4 compare c        \n\t"
    ".org 0xB4 \n\t jmp  __vector_unused_irq ; 0x5A, 45   timer/counter4 overflow         \n\t"
    ".org 0xB8 \n\t jmp  __vector_unused_irq ; 0x5C, 46   timer/counter5 capture event    \n\t"
    ".org 0xBC \n\t jmp  __vector_unused_irq ; 0x5E, 47   timer/counter5 compare a        \n\t"
    ".org 0xC0 \n\t jmp  __vector_unused_irq ; 0x60, 48   timer/counter5 compare b        \n\t"
    ".org 0xC4 \n\t jmp  __vector_unused_irq ; 0x62, 49   timer/counter5 compare c        \n\t"
    ".org 0xC8 \n\t jmp  __vector_unused_irq ; 0x64, 50   timer/counter5 overflow         \n\t"
    ".org 0xCC \n\t jmp  __vector_unused_irq ; 0x66, 51   uart2 rx complete               \n\t"
    ".org 0xD0 \n\t jmp  __vector_unused_irq ; 0x68, 52   uart2 data register empty       \n\t"
    ".org 0xD4 \n\t jmp  __vector_unused_irq ; 0x6A, 53   uart2 tx complete               \n\t"
    ".org 0xD8 \n\t jmp  __vector_unused_irq ; 0x6C, 54   uart3 rx complete               \n\t"
    ".org 0xDC \n\t jmp  __vector_unused_irq ; 0x6E, 55   uart3 data register empty       \n\t"
    ".org 0xF0 \n\t jmp  __vector_unused_irq ; 0x70, 56   uart3 tx complete               \n\t"
  );
}
