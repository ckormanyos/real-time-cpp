///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2026.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

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


extern "C" void __isr_vector() __attribute__((naked, used, noinline, section(".isr_vector")));

extern "C" void __isr_vector()
{
  // Use explicit .org offsets and jmp instructions. The offsets
  // provide exact address positions in the interrupt vector table
  // and the jumps reach 22-bit addresses. This interrupt vector
  // table works even when compiling and linking with (or without)
  // the option -mrelax. For a quick sanity check, look in the
  // map file and verify that the size of __isr_vector is 0xF4.

  asm volatile
  (
    ".org 0x00 \n\t jmp __my_startup          \n\t" //  0 reset
    ".org 0x04 \n\t jmp __vector_unused_irq   \n\t" //  1 external interrupt0
    ".org 0x08 \n\t jmp __vector_unused_irq   \n\t" //  2 external interrupt1
    ".org 0x0C \n\t jmp __vector_unused_irq   \n\t" //  3 external interrupt2
    ".org 0x10 \n\t jmp __vector_unused_irq   \n\t" //  4 external interrupt3
    ".org 0x14 \n\t jmp __vector_unused_irq   \n\t" //  5 external interrupt4
    ".org 0x18 \n\t jmp __vector_unused_irq   \n\t" //  6 external interrupt5
    ".org 0x1C \n\t jmp __vector_unused_irq   \n\t" //  7 external interrupt6
    ".org 0x20 \n\t jmp __vector_unused_irq   \n\t" //  8 external interrupt7
    ".org 0x24 \n\t jmp __vector_unused_irq   \n\t" //  9 pin change int request0
    ".org 0x28 \n\t jmp __vector_unused_irq   \n\t" // 10 pin change int request1
    ".org 0x2C \n\t jmp __vector_unused_irq   \n\t" // 11 pin change int request2
    ".org 0x30 \n\t jmp __vector_unused_irq   \n\t" // 12 Watchdog Timer Interrupt
    ".org 0x34 \n\t jmp __vector_unused_irq   \n\t" // 13 timer/counter2 compare A
    ".org 0x38 \n\t jmp __vector_unused_irq   \n\t" // 14 timer/counter2 compare B
    ".org 0x3C \n\t jmp __vector_unused_irq   \n\t" // 15 timer/counter2 overflow
    ".org 0x40 \n\t jmp __vector_unused_irq   \n\t" // 16 timer/counter1 capture
    ".org 0x44 \n\t jmp __vector_unused_irq   \n\t" // 17 timer/counter1 compare A
    ".org 0x48 \n\t jmp __vector_unused_irq   \n\t" // 18 timer/counter1 compare B
    ".org 0x4C \n\t jmp __vector_unused_irq   \n\t" // 19 timer/counter1 compare C
    ".org 0x50 \n\t jmp __vector_unused_irq   \n\t" // 20 timer/counter1 overflow
    ".org 0x54 \n\t jmp __vector_unused_irq   \n\t" // 21 timer/counter0 compare A
    ".org 0x58 \n\t jmp __vector_unused_irq   \n\t" // 22 timer/counter0 compare B
    ".org 0x5C \n\t jmp __vector_23           \n\t" // 23 timer/counter0 overflow
    ".org 0x60 \n\t jmp __vector_unused_irq   \n\t" // 24 spi serial transfer Complete
    ".org 0x64 \n\t jmp __vector_unused_irq   \n\t" // 25 uart0 rx complete
    ".org 0x68 \n\t jmp __vector_unused_irq   \n\t" // 26 uart0 data register empty
    ".org 0x6C \n\t jmp __vector_unused_irq   \n\t" // 27 uart0 tx complete
    ".org 0x70 \n\t jmp __vector_unused_irq   \n\t" // 28 analog comparator
    ".org 0x74 \n\t jmp __vector_unused_irq   \n\t" // 29 adc conversion complete
    ".org 0x78 \n\t jmp __vector_unused_irq   \n\t" // 30 eeprom ready
    ".org 0x7C \n\t jmp __vector_unused_irq   \n\t" // 31 timer/counter3 capture event
    ".org 0x80 \n\t jmp __vector_unused_irq   \n\t" // 32 timer/counter3 compare match a
    ".org 0x84 \n\t jmp __vector_unused_irq   \n\t" // 33 timer/counter3 compare match b
    ".org 0x88 \n\t jmp __vector_unused_irq   \n\t" // 34 timer/counter3 compare match c
    ".org 0x8C \n\t jmp __vector_unused_irq   \n\t" // 35 timer/counter3 overflow
    ".org 0x90 \n\t jmp __vector_unused_irq   \n\t" // 36 uart1 rx complete
    ".org 0x94 \n\t jmp __vector_unused_irq   \n\t" // 37 uart1 data register empty
    ".org 0x98 \n\t jmp __vector_unused_irq   \n\t" // 38 uart1 tx complete
    ".org 0x9C \n\t jmp __vector_unused_irq   \n\t" // 39 2 wire serial interface
    ".org 0xA0 \n\t jmp __vector_unused_irq   \n\t" // 40 store program memory ready
    ".org 0xA4 \n\t jmp __vector_unused_irq   \n\t" // 41 timer/counter4 capture event
    ".org 0xA8 \n\t jmp __vector_unused_irq   \n\t" // 42 timer/counter4 compare a
    ".org 0xAC \n\t jmp __vector_unused_irq   \n\t" // 43 timer/counter4 compare b
    ".org 0xB0 \n\t jmp __vector_unused_irq   \n\t" // 44 timer/counter4 compare c
    ".org 0xB4 \n\t jmp __vector_unused_irq   \n\t" // 45 timer/counter4 overflow
    ".org 0xB8 \n\t jmp __vector_unused_irq   \n\t" // 46 timer/counter5 capture event
    ".org 0xBC \n\t jmp __vector_unused_irq   \n\t" // 47 timer/counter5 compare a
    ".org 0xC0 \n\t jmp __vector_unused_irq   \n\t" // 48 timer/counter5 compare b
    ".org 0xC4 \n\t jmp __vector_unused_irq   \n\t" // 49 timer/counter5 compare c
    ".org 0xC8 \n\t jmp __vector_unused_irq   \n\t" // 50 timer/counter5 overflow
    ".org 0xCC \n\t jmp __vector_unused_irq   \n\t" // 51 uart2 rx complete
    ".org 0xD0 \n\t jmp __vector_unused_irq   \n\t" // 52 uart2 data register empty
    ".org 0xD4 \n\t jmp __vector_unused_irq   \n\t" // 53 uart2 tx complete
    ".org 0xD8 \n\t jmp __vector_unused_irq   \n\t" // 54 uart3 rx complete
    ".org 0xDC \n\t jmp __vector_unused_irq   \n\t" // 55 uart3 data register empty
    ".org 0xE0 \n\t jmp __vector_unused_irq   \n\t" // 56 uart3 tx complete
  );
}
