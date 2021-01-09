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
extern "C" void __vector_3         () __attribute__((signal, used, externally_visible));

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
const volatile std::array<isr_type, 40U> __isr_vector __attribute__((section(".isr_vector")));

extern "C"
const volatile std::array<isr_type, 40U> __isr_vector =
{{
                                              // addr.  nr. interrupt source
  { { 0x0C, 0x94 }, __my_startup },           // 0x00 RESET
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x02 NMI    Non-Maskable Interrupt from CRC 2
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x04 VLM    Voltage Level Monitor 3
  { { 0x0C, 0x94 }, __vector_3 },             // 0x06 RTC    Overflow or compare match 4
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x08 PIT    Periodic interrupt 5
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x0A CCL    Configurable Custom Logic 6
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x0C PORTA  External interrupt 7
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x0E TCA0   Overflow 8
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x10 TCA0   Underflow (Split mode) 9
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x12 TCA0   Compare channel 0 
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x14 TCA0   Compare channel 1 11
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x16 TCA0   Compare channel 2 12
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x18 TCB0   Capture 13
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x1A TCB1   Capture 14
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x1C TWI0   Slave 15
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x1E TWI0   Master 16
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x20 SPI0   Serial Peripheral Interface 0 17
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x22 USART0 Receive Complete 18
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x24 USART0 Data Register Empty 19
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x26 USART0 Transmit Complete 20
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x28 PORTD  External interrupt 21
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x2A AC0    Compare 22
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x2C ADC0   Result Ready 23
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x2E ADC0   Window Compare 24
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x30 PORTC  External interrupt 25
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x32 TCB2   Capture 26
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x34 USART1 Receive Complete 27
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x36 USART1 Data Register Empty 28
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x38 USART1 Transmit Complete 29
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x3A PORTF  External interrupt 30
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x3C NVM    Ready 31
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x3E USART2 Receive Complete 32
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x40 USART2 Data Register Empty 33
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x42 USART2 Transmit Complete 34
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x44 PORTB  External interruptX35
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x46 PORTE  External interrupt 36
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x48 TCB3   Capture 37
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x4A USART3 Receive Complete 38
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x4C USART3 Data Register Empty 39
  { { 0x0C, 0x94 }, __vector_unused_irq }     // 0x4E USART3 Transmit Complete
}};
