///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2019.
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

namespace
{
  typedef struct struct_isr_type
  {
    typedef void(*function_type)();

    const std::uint8_t  jmp[2]; // JMP instruction (0x940C): 0x0C = low byte, 0x94 = high byte.
    const function_type func;   // The interrupt service routine.
  }
  isr_type;
}

extern "C"
const volatile std::array<isr_type, 57U> __isr_vector __attribute__((section(".isr_vector")));

extern "C"
const volatile std::array<isr_type, 57U> __isr_vector =
{{
                                              // addr.  nr. interrupt source
  { { 0x0C, 0x94 }, __my_startup },           // 0x00,  0   reset
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x02,  1   external interrupt0
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x04,  2   external interrupt1
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x06,  3   external interrupt2
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x08,  4   external interrupt3
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x0A,  5   external interrupt4
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x0C,  6   external interrupt5
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x0E,  7   external interrupt6
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x10,  8   external interrupt7
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x12,  9   pin change int request0
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x14, 10   pin change int request1
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x16, 11   pin change int request2
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x18, 12   Watchdog Timer Interrupt
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x1A, 13   timer/counter2 compare A
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x1C, 14   timer/counter2 compare B
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x1E, 15   timer/counter2 overflow
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x20, 16   timer/counter1 capture
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x22, 17   timer/counter1 compare A
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x24, 18   timer/counter1 compare B
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x26, 19   timer/counter1 compare C
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x28, 20   timer/counter1 overflow
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x2A, 21   timer/counter0 compare A
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x2C, 22   timer/counter0 compare B
  { { 0x0C, 0x94 }, __vector_23 },            // 0x2E, 23   timer/counter0 overflow
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x30, 24   spi serial transfer cComplete
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x32, 25   uart0 rx complete
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x34, 26   uart0 data register empty
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x36, 27   uart0 tx complete
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x38, 28   analog comparator
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x3A, 29   adc conversion complete
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x3C, 30   eeprom ready
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x3E, 31   timer/counter3 capture event
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x40, 32   timer/counter3 compare match a
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x42, 33   timer/counter3 compare match b
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x44, 34   timer/counter3 compare match c
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x46, 35   timer/counter3 overflow
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x48, 36   uart1 rx complete
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x4A, 37   uart1 data register empty
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x4C, 38   uart1 tx complete
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x4E, 39   2 wire serial interface
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x50, 40   store program memory ready
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x52, 41   timer/counter4 captureevent
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x54, 42   timer/counter4 compare a
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x56, 43   timer/counter4 compare b
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x58, 44   timer/counter4 compare c
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x5A, 45   timer/counter4 overflow
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x5C, 46   timer/counter5 capture event
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x5E, 47   timer/counter5 compare a
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x60, 48   timer/counter5 compare b
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x62, 49   timer/counter5 compare c
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x64, 50   timer/counter5 overflow
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x66, 51   uart2 rx complete
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x68, 52   uart2 data register empty
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x6A, 53   uart2 tx complete
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x6C, 54   uart3 rx complete
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x6E, 55   uart3 data register empty
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x70, 56   uart3 tx complete
}};
