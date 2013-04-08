///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdint>
#include <mcal_cpu.h>

extern "C" void startup();
extern "C" void __vector_unused_irq() __attribute__((signal, used, externally_visible));
extern "C" void __vector_14        () __attribute__((signal, used, externally_visible));
extern "C" void __vector_17        () __attribute__((signal, used, externally_visible));

extern "C" void __vector_unused_irq() { for(;;) { mcal::cpu::nop(); } }

typedef struct struct_isr_type
{
  typedef void(*function_type)();

  std::uint8_t  jmp[2]; // JMP instruction (0x940C): 0x0C = low byte, 0x94 = high byte.
  function_type func;   // The interrupt service routine.
}
isr_type;

extern "C"
const volatile isr_type isr_vector[26U] __attribute__ ((section(".isr_vector")));

extern "C"
const volatile isr_type isr_vector[26U] =
{
                                            // Vector No.  Program Address  Source Interrupt Definition
  {{0x0C, 0x94}, startup },                 //  1 reset
  {{0x0C, 0x94}, __vector_unused_irq},      //  2 ext0
  {{0x0C, 0x94}, __vector_unused_irq},      //  3 ext1
  {{0x0C, 0x94}, __vector_unused_irq},      //  4 pin0
  {{0x0C, 0x94}, __vector_unused_irq},      //  5 pin1
  {{0x0C, 0x94}, __vector_unused_irq},      //  6 pin2
  {{0x0C, 0x94}, __vector_unused_irq},      //  7 watchdog
  {{0x0C, 0x94}, __vector_unused_irq},      //  8 timer2 cmp a
  {{0x0C, 0x94}, __vector_unused_irq},      //  9 timer2 cmp b
  {{0x0C, 0x94}, __vector_unused_irq},      // 10 timer2 ovf
  {{0x0C, 0x94}, __vector_unused_irq},      // 11 timer1 cap
  {{0x0C, 0x94}, __vector_unused_irq},      // 12 timer1 cmp a
  {{0x0C, 0x94}, __vector_unused_irq},      // 13 timer1 cmp b
  {{0x0C, 0x94}, __vector_unused_irq},      // 14 timer1 ovf
  {{0x0C, 0x94}, __vector_14},              // 15 timer0 cmp a
  {{0x0C, 0x94}, __vector_unused_irq},      // 16 timer0 cmp b
  {{0x0C, 0x94}, __vector_unused_irq},      // 17 timer0 ovf
  {{0x0C, 0x94}, __vector_17},              // 18 spi(TM)
  {{0x0C, 0x94}, __vector_unused_irq},      // 19 usart rx
  {{0x0C, 0x94}, __vector_unused_irq},      // 20 usart err
  {{0x0C, 0x94}, __vector_unused_irq},      // 21 usart rx
  {{0x0C, 0x94}, __vector_unused_irq},      // 22 adc
  {{0x0C, 0x94}, __vector_unused_irq},      // 23 eep Ready
  {{0x0C, 0x94}, __vector_unused_irq},      // 24 comparator
  {{0x0C, 0x94}, __vector_unused_irq},      // 25 two-wire
  {{0x0C, 0x94}, __vector_unused_irq}       // 26 spm
};
