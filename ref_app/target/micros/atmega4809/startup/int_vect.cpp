///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2023.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <array>
#include <cstddef>
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

namespace local
{
  typedef struct struct_isr_type
  {
    typedef void(*function_type)();

    const std::uint8_t  jmp[static_cast<std::size_t>(UINT8_C(2))]; // JMP instruction (0x940C): 0x0C = low byte, 0x94 = high byte.
    const function_type func;                                      // The interrupt service routine.
  }
  isr_type;

  constexpr auto count_of_isr_vector = static_cast<std::size_t>(UINT8_C(40));

  using isr_vector_array_type = std::array<isr_type, count_of_isr_vector>;
}

const volatile local::isr_vector_array_type my_isr_vector __attribute__((section(".isr_vector"))) =
{{
                                                                                                                      // address   index   interrupt source
  { { static_cast<std::uint8_t>(UINT8_C(0x0C)), static_cast<std::uint8_t>(UINT8_C(0x94)) }, __my_startup },           // 0x00      0       RESET
  { { static_cast<std::uint8_t>(UINT8_C(0x0C)), static_cast<std::uint8_t>(UINT8_C(0x94)) }, __vector_unused_irq },    // 0x02      1       NMI    Non-Maskable Interrupt from CRC
  { { static_cast<std::uint8_t>(UINT8_C(0x0C)), static_cast<std::uint8_t>(UINT8_C(0x94)) }, __vector_unused_irq },    // 0x04      2       VLM    Voltage Level Monitor
  { { static_cast<std::uint8_t>(UINT8_C(0x0C)), static_cast<std::uint8_t>(UINT8_C(0x94)) }, __vector_3 },             // 0x06      3       RTC    Overflow or compare match
  { { static_cast<std::uint8_t>(UINT8_C(0x0C)), static_cast<std::uint8_t>(UINT8_C(0x94)) }, __vector_unused_irq },    // 0x08      4       PIT    Periodic interrupt
  { { static_cast<std::uint8_t>(UINT8_C(0x0C)), static_cast<std::uint8_t>(UINT8_C(0x94)) }, __vector_unused_irq },    // 0x0A      5       CCL    Configurable Custom Logic
  { { static_cast<std::uint8_t>(UINT8_C(0x0C)), static_cast<std::uint8_t>(UINT8_C(0x94)) }, __vector_unused_irq },    // 0x0C      6       PORTA  External interrupt
  { { static_cast<std::uint8_t>(UINT8_C(0x0C)), static_cast<std::uint8_t>(UINT8_C(0x94)) }, __vector_unused_irq },    // 0x0E      7       TCA0   Overflow
  { { static_cast<std::uint8_t>(UINT8_C(0x0C)), static_cast<std::uint8_t>(UINT8_C(0x94)) }, __vector_unused_irq },    // 0x10      8       TCA0   Underflow (Split mode)
  { { static_cast<std::uint8_t>(UINT8_C(0x0C)), static_cast<std::uint8_t>(UINT8_C(0x94)) }, __vector_unused_irq },    // 0x12      9       TCA0   Compare channel
  { { static_cast<std::uint8_t>(UINT8_C(0x0C)), static_cast<std::uint8_t>(UINT8_C(0x94)) }, __vector_unused_irq },    // 0x14      10      TCA0   Compare channel 1
  { { static_cast<std::uint8_t>(UINT8_C(0x0C)), static_cast<std::uint8_t>(UINT8_C(0x94)) }, __vector_unused_irq },    // 0x16      11      TCA0   Compare channel 2
  { { static_cast<std::uint8_t>(UINT8_C(0x0C)), static_cast<std::uint8_t>(UINT8_C(0x94)) }, __vector_unused_irq },    // 0x18      12      TCB0   Capture
  { { static_cast<std::uint8_t>(UINT8_C(0x0C)), static_cast<std::uint8_t>(UINT8_C(0x94)) }, __vector_unused_irq },    // 0x1A      13      TCB1   Capture
  { { static_cast<std::uint8_t>(UINT8_C(0x0C)), static_cast<std::uint8_t>(UINT8_C(0x94)) }, __vector_unused_irq },    // 0x1C      14      TWI0   Slave
  { { static_cast<std::uint8_t>(UINT8_C(0x0C)), static_cast<std::uint8_t>(UINT8_C(0x94)) }, __vector_unused_irq },    // 0x1E      15      TWI0   Master
  { { static_cast<std::uint8_t>(UINT8_C(0x0C)), static_cast<std::uint8_t>(UINT8_C(0x94)) }, __vector_unused_irq },    // 0x20      16      SPI0   Serial Peripheral Interface 0
  { { static_cast<std::uint8_t>(UINT8_C(0x0C)), static_cast<std::uint8_t>(UINT8_C(0x94)) }, __vector_unused_irq },    // 0x22      17      USART0 Receive Complete
  { { static_cast<std::uint8_t>(UINT8_C(0x0C)), static_cast<std::uint8_t>(UINT8_C(0x94)) }, __vector_unused_irq },    // 0x24      18      USART0 Data Register Empty
  { { static_cast<std::uint8_t>(UINT8_C(0x0C)), static_cast<std::uint8_t>(UINT8_C(0x94)) }, __vector_unused_irq },    // 0x26      19      USART0 Transmit Complete
  { { static_cast<std::uint8_t>(UINT8_C(0x0C)), static_cast<std::uint8_t>(UINT8_C(0x94)) }, __vector_unused_irq },    // 0x28      20      PORTD  External interrupt
  { { static_cast<std::uint8_t>(UINT8_C(0x0C)), static_cast<std::uint8_t>(UINT8_C(0x94)) }, __vector_unused_irq },    // 0x2A      21      AC0    Compare
  { { static_cast<std::uint8_t>(UINT8_C(0x0C)), static_cast<std::uint8_t>(UINT8_C(0x94)) }, __vector_unused_irq },    // 0x2C      22      ADC0   Result Ready
  { { static_cast<std::uint8_t>(UINT8_C(0x0C)), static_cast<std::uint8_t>(UINT8_C(0x94)) }, __vector_unused_irq },    // 0x2E      23      ADC0   Window Compare
  { { static_cast<std::uint8_t>(UINT8_C(0x0C)), static_cast<std::uint8_t>(UINT8_C(0x94)) }, __vector_unused_irq },    // 0x30      24      PORTC  External interrupt
  { { static_cast<std::uint8_t>(UINT8_C(0x0C)), static_cast<std::uint8_t>(UINT8_C(0x94)) }, __vector_unused_irq },    // 0x32      25      TCB2   Capture
  { { static_cast<std::uint8_t>(UINT8_C(0x0C)), static_cast<std::uint8_t>(UINT8_C(0x94)) }, __vector_unused_irq },    // 0x34      26      USART1 Receive Complete
  { { static_cast<std::uint8_t>(UINT8_C(0x0C)), static_cast<std::uint8_t>(UINT8_C(0x94)) }, __vector_unused_irq },    // 0x36      27      USART1 Data Register Empty
  { { static_cast<std::uint8_t>(UINT8_C(0x0C)), static_cast<std::uint8_t>(UINT8_C(0x94)) }, __vector_unused_irq },    // 0x38      28      USART1 Transmit Complete
  { { static_cast<std::uint8_t>(UINT8_C(0x0C)), static_cast<std::uint8_t>(UINT8_C(0x94)) }, __vector_unused_irq },    // 0x3A      29      PORTF  External interrupt
  { { static_cast<std::uint8_t>(UINT8_C(0x0C)), static_cast<std::uint8_t>(UINT8_C(0x94)) }, __vector_unused_irq },    // 0x3C      30      NVM    Ready
  { { static_cast<std::uint8_t>(UINT8_C(0x0C)), static_cast<std::uint8_t>(UINT8_C(0x94)) }, __vector_unused_irq },    // 0x3E      31      USART2 Receive Complete
  { { static_cast<std::uint8_t>(UINT8_C(0x0C)), static_cast<std::uint8_t>(UINT8_C(0x94)) }, __vector_unused_irq },    // 0x40      32      USART2 Data Register Empty
  { { static_cast<std::uint8_t>(UINT8_C(0x0C)), static_cast<std::uint8_t>(UINT8_C(0x94)) }, __vector_unused_irq },    // 0x42      33      USART2 Transmit Complete
  { { static_cast<std::uint8_t>(UINT8_C(0x0C)), static_cast<std::uint8_t>(UINT8_C(0x94)) }, __vector_unused_irq },    // 0x44      34      PORTB  External interruptX
  { { static_cast<std::uint8_t>(UINT8_C(0x0C)), static_cast<std::uint8_t>(UINT8_C(0x94)) }, __vector_unused_irq },    // 0x46      35      PORTE  External interrupt
  { { static_cast<std::uint8_t>(UINT8_C(0x0C)), static_cast<std::uint8_t>(UINT8_C(0x94)) }, __vector_unused_irq },    // 0x48      36      TCB3   Capture
  { { static_cast<std::uint8_t>(UINT8_C(0x0C)), static_cast<std::uint8_t>(UINT8_C(0x94)) }, __vector_unused_irq },    // 0x4A      37      USART3 Receive Complete
  { { static_cast<std::uint8_t>(UINT8_C(0x0C)), static_cast<std::uint8_t>(UINT8_C(0x94)) }, __vector_unused_irq },    // 0x4C      38      USART3 Data Register Empty
  { { static_cast<std::uint8_t>(UINT8_C(0x0C)), static_cast<std::uint8_t>(UINT8_C(0x94)) }, __vector_unused_irq }     // 0x4E      39      USART3 Transmit Complete
}};
