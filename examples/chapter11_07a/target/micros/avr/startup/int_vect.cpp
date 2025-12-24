///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <FreeRTOS.h>
#include <mcal_cpu.h>

#include <util/utility/util_attribute.h>

#include <array>
#include <cstddef>
#include <cstdint>

extern "C" void __my_startup       () ATTRIBUTE(section(".startup"), used, noinline);
extern "C" void __vector_unused_irq() ATTRIBUTE(signal, used, externally_visible);
#if (configUSE_PREEMPTION == 1)
extern "C" void __vector_11        () ATTRIBUTE(signal, used, externally_visible, naked);
#else
extern "C" void __vector_11        () ATTRIBUTE(signal, used, externally_visible);
#endif
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
    using function_type = void(*)();

    const std::uint8_t  jmp[static_cast<std::size_t>(UINT8_C(2))]; // JMP instruction (0x940C): 0x0C = low byte, 0x94 = high byte.
    const function_type func;                                      // The interrupt service routine.
  }
  isr_type;

  constexpr auto count_of_isr_vector = static_cast<std::size_t>(UINT8_C(26));

  using isr_vector_array_type = std::array<isr_type, count_of_isr_vector>;
} // namespace local

const volatile local::isr_vector_array_type my_isr_vector ATTRIBUTE(section(".isr_vector")) =
{{
                                              // addr.  nr. interrupt source
  { { 0x0C, 0x94 }, __my_startup },           // 0x00,  0,  reset
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x02,  1,  ext0
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x04,  2,  ext1
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x06,  3,  pin0
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x08,  4,  pin1
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x0A,  5,  pin2
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x0C,  6,  watchdog
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x0E,  7,  timer2 cmp a
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x10,  8,  timer2 cmp b
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x12,  9,  timer2 ovf
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x14, 10,  timer1 cap
  { { 0x0C, 0x94 }, __vector_11 },            // 0x16, 11,  timer1 cmp a
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x18, 12,  timer1 cmp b
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x1A, 13,  timer1 ovf
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x1C, 14,  timer0 cmp a
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x1E, 15,  timer0 cmp b
  { { 0x0C, 0x94 }, __vector_16 },            // 0x2E, 16,  timer0 ovf
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x20, 17,  spi(TM)
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x22, 18,  usart rx
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x24, 19,  usart err
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x26, 20,  usart tx
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x28, 21,  adc
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x2A, 22,  eep ready
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x2C, 23,  comparator
  { { 0x0C, 0x94 }, __vector_unused_irq },    // 0x2E, 24,  two-wire
  { { 0x0C, 0x94 }, __vector_unused_irq }     // 0x30, 25,  spm
}};
