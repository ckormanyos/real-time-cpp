///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_cpu.h>

#include <util/utility/util_attribute.h>

#include <array>
#include <cstddef>
#include <cstdint>

extern "C" void __my_startup       () ATTRIBUTE(section(".startup"), used, noinline);
extern "C" void __vector_unused_irq() ATTRIBUTE(signal, used, externally_visible);
extern "C" void __vector_16        () ATTRIBUTE(signal, used, externally_visible);

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

  constexpr auto count_of_isr_vector = static_cast<std::size_t>(UINT8_C(26));

  using isr_vector_array_type = std::array<isr_type, count_of_isr_vector>;
}

const volatile local::isr_vector_array_type my_isr_vector ATTRIBUTE(section(".isr_vector")) =
{{
                                                                                                                    // address   index   interrupt source
  { { static_cast<std::uint8_t>(UINT8_C(0x0C)), static_cast<std::uint8_t>(UINT8_C(0x94)) }, __my_startup },         // 0x00      0       reset
  { { static_cast<std::uint8_t>(UINT8_C(0x0C)), static_cast<std::uint8_t>(UINT8_C(0x94)) }, __vector_unused_irq },  // 0x02      1       ext0
  { { static_cast<std::uint8_t>(UINT8_C(0x0C)), static_cast<std::uint8_t>(UINT8_C(0x94)) }, __vector_unused_irq },  // 0x04      2       ext1
  { { static_cast<std::uint8_t>(UINT8_C(0x0C)), static_cast<std::uint8_t>(UINT8_C(0x94)) }, __vector_unused_irq },  // 0x06      3       pin0
  { { static_cast<std::uint8_t>(UINT8_C(0x0C)), static_cast<std::uint8_t>(UINT8_C(0x94)) }, __vector_unused_irq },  // 0x08      4       pin1
  { { static_cast<std::uint8_t>(UINT8_C(0x0C)), static_cast<std::uint8_t>(UINT8_C(0x94)) }, __vector_unused_irq },  // 0x0A      5       pin2
  { { static_cast<std::uint8_t>(UINT8_C(0x0C)), static_cast<std::uint8_t>(UINT8_C(0x94)) }, __vector_unused_irq },  // 0x0C      6       watchdog
  { { static_cast<std::uint8_t>(UINT8_C(0x0C)), static_cast<std::uint8_t>(UINT8_C(0x94)) }, __vector_unused_irq },  // 0x0E      7       timer2 cmp a
  { { static_cast<std::uint8_t>(UINT8_C(0x0C)), static_cast<std::uint8_t>(UINT8_C(0x94)) }, __vector_unused_irq },  // 0x10      8       timer2 cmp b
  { { static_cast<std::uint8_t>(UINT8_C(0x0C)), static_cast<std::uint8_t>(UINT8_C(0x94)) }, __vector_unused_irq },  // 0x12      9       timer2 ovf
  { { static_cast<std::uint8_t>(UINT8_C(0x0C)), static_cast<std::uint8_t>(UINT8_C(0x94)) }, __vector_unused_irq },  // 0x14      10      timer1 cap
  { { static_cast<std::uint8_t>(UINT8_C(0x0C)), static_cast<std::uint8_t>(UINT8_C(0x94)) }, __vector_unused_irq },  // 0x16      11      timer1 cmp a
  { { static_cast<std::uint8_t>(UINT8_C(0x0C)), static_cast<std::uint8_t>(UINT8_C(0x94)) }, __vector_unused_irq },  // 0x18      12      timer1 cmp b
  { { static_cast<std::uint8_t>(UINT8_C(0x0C)), static_cast<std::uint8_t>(UINT8_C(0x94)) }, __vector_unused_irq },  // 0x1A      13      timer1 ovf
  { { static_cast<std::uint8_t>(UINT8_C(0x0C)), static_cast<std::uint8_t>(UINT8_C(0x94)) }, __vector_unused_irq },  // 0x1C      14      timer0 cmp a
  { { static_cast<std::uint8_t>(UINT8_C(0x0C)), static_cast<std::uint8_t>(UINT8_C(0x94)) }, __vector_unused_irq },  // 0x1E      15      timer0 cmp b
  { { static_cast<std::uint8_t>(UINT8_C(0x0C)), static_cast<std::uint8_t>(UINT8_C(0x94)) }, __vector_16 },          // 0x2E      16      timer0 ovf
  { { static_cast<std::uint8_t>(UINT8_C(0x0C)), static_cast<std::uint8_t>(UINT8_C(0x94)) }, __vector_unused_irq },  // 0x20      17      spi(TM)
  { { static_cast<std::uint8_t>(UINT8_C(0x0C)), static_cast<std::uint8_t>(UINT8_C(0x94)) }, __vector_unused_irq },  // 0x22      18      usart rx
  { { static_cast<std::uint8_t>(UINT8_C(0x0C)), static_cast<std::uint8_t>(UINT8_C(0x94)) }, __vector_unused_irq },  // 0x24      19      usart err
  { { static_cast<std::uint8_t>(UINT8_C(0x0C)), static_cast<std::uint8_t>(UINT8_C(0x94)) }, __vector_unused_irq },  // 0x26      20      usart tx
  { { static_cast<std::uint8_t>(UINT8_C(0x0C)), static_cast<std::uint8_t>(UINT8_C(0x94)) }, __vector_unused_irq },  // 0x28      21      adc
  { { static_cast<std::uint8_t>(UINT8_C(0x0C)), static_cast<std::uint8_t>(UINT8_C(0x94)) }, __vector_unused_irq },  // 0x2A      22      eep ready
  { { static_cast<std::uint8_t>(UINT8_C(0x0C)), static_cast<std::uint8_t>(UINT8_C(0x94)) }, __vector_unused_irq },  // 0x2C      23      comparator
  { { static_cast<std::uint8_t>(UINT8_C(0x0C)), static_cast<std::uint8_t>(UINT8_C(0x94)) }, __vector_unused_irq },  // 0x2E      24      two-wire
  { { static_cast<std::uint8_t>(UINT8_C(0x0C)), static_cast<std::uint8_t>(UINT8_C(0x94)) }, __vector_unused_irq }   // 0x30      25      spm
}};
