///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2014.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <algorithm>
#include <cstdint>
#include <iterator>
#include <mcal_irq.h>

extern "C" void __int_vect_undef_instr_handler   () __attribute__((section(".text.isr1"),  interrupt("UNDEF"), used, noinline));
extern "C" void __int_vect_sw_interrupt_handler  () __attribute__((section(".text.isr2"),  interrupt("SWI"),   used, noinline));
extern "C" void __int_vect_prefetch_abort_handler() __attribute__((section(".text.isr3"),  interrupt("ABORT"), used, noinline));
extern "C" void __int_vect_data_abort_handler    () __attribute__((section(".text.isr4"),  interrupt("ABORT"), used, noinline));
extern "C" void __int_vect_unused_05_handler     () __attribute__((section(".text.isr5"),  interrupt("IRQ"),   used, noinline));
extern "C" void __int_vect_irq_handler           () __attribute__((section(".text.isr6"),  interrupt("IRQ"),   used, noinline));
extern "C" void __int_vect_fiq_handler           () __attribute__((section(".text.isr7"),  interrupt("FIQ"),   used, noinline));
extern "C" void __int_vect_future_08_handler     () __attribute__((section(".text.isr8"),  interrupt("IRQ"),   used, noinline));
extern "C" void __int_vect_future_09_handler     () __attribute__((section(".text.isr9"),  interrupt("IRQ"),   used, noinline));
extern "C" void __int_vect_future_10_handler     () __attribute__((section(".text.isr10"), interrupt("IRQ"),   used, noinline));
extern "C" void __int_vect_future_11_handler     () __attribute__((section(".text.isr11"), interrupt("IRQ"),   used, noinline));
extern "C" void __int_vect_future_12_handler     () __attribute__((section(".text.isr12"), interrupt("IRQ"),   used, noinline));
extern "C" void __int_vect_future_13_handler     () __attribute__((section(".text.isr13"), interrupt("IRQ"),   used, noinline));
extern "C" void __int_vect_future_14_handler     () __attribute__((section(".text.isr14"), interrupt("IRQ"),   used, noinline));
extern "C" void __int_vect_future_15_handler     () __attribute__((section(".text.isr15"), interrupt("IRQ"),   used, noinline));

void __int_vect_undef_instr_handler   () { mcal::irq::secure::int_vect_undef_instr_handler_callback   (); }
void __int_vect_sw_interrupt_handler  () { mcal::irq::secure::int_vect_sw_interrupt_handler_callback  (); }
void __int_vect_prefetch_abort_handler() { mcal::irq::secure::int_vect_prefetch_abort_handler_callback(); }
void __int_vect_data_abort_handler    () { mcal::irq::secure::int_vect_data_abort_handler_callback    (); }
void __int_vect_unused_05_handler     () { mcal::irq::secure::int_vect_unused_05_handler_callback     (); }
void __int_vect_irq_handler           () { mcal::irq::secure::int_vect_irq_handler_callback           (); }
void __int_vect_fiq_handler           () { mcal::irq::secure::int_vect_fiq_handler_callback           (); }
void __int_vect_future_08_handler     () { mcal::irq::secure::int_vect_future_08_handler_callback     (); }
void __int_vect_future_09_handler     () { mcal::irq::secure::int_vect_future_09_handler_callback     (); }
void __int_vect_future_10_handler     () { mcal::irq::secure::int_vect_future_10_handler_callback     (); }
void __int_vect_future_11_handler     () { mcal::irq::secure::int_vect_future_11_handler_callback     (); }
void __int_vect_future_12_handler     () { mcal::irq::secure::int_vect_future_12_handler_callback     (); }
void __int_vect_future_13_handler     () { mcal::irq::secure::int_vect_future_13_handler_callback     (); }
void __int_vect_future_14_handler     () { mcal::irq::secure::int_vect_future_14_handler_callback     (); }
void __int_vect_future_15_handler     () { mcal::irq::secure::int_vect_future_15_handler_callback     (); }

namespace int_vect
{
  void load_lower_interrupt_vector_data(const std::uint32_t load_address = UINT32_C(0x00000000));

  void load_lower_interrupt_vector_data(const std::uint32_t load_address)
  {
    // These data have been extracted from the lower interrupt
    // vector table code that is implemented in "int_vect_table.s".
    // The code has been assembled and linked to address 0x00000000.
    // The corresponding byte code has subsequently been extracted
    // from the hex mask and has been transcribed to the table
    // of hex-values below.

    // In this sense the input parameter load_address is unused.
    // But we supply this parameter in order to avoid hard-coding
    // a pointer to zero, which would otherwise result in undesired
    // compiler warnings.

    static const std::uint8_t the_data[64U] =
    {
      0x18U, 0xF0U, 0x9FU, 0xE5U, 0x18U, 0xF0U, 0x9FU, 0xE5U, 0x18U, 0xF0U, 0x9FU, 0xE5U, 0x18U, 0xF0U, 0x9FU, 0xE5U,
      0x18U, 0xF0U, 0x9FU, 0xE5U, 0x18U, 0xF0U, 0x9FU, 0xE5U, 0x18U, 0xF0U, 0x9FU, 0xE5U, 0x18U, 0xF0U, 0x9FU, 0xE5U,
      0x00U, 0x84U, 0x00U, 0x00U, 0x40U, 0x80U, 0x00U, 0x00U, 0x80U, 0x80U, 0x00U, 0x00U, 0xC0U, 0x80U, 0x00U, 0x00U,
      0x00U, 0x81U, 0x00U, 0x00U, 0x40U, 0x81U, 0x00U, 0x00U, 0x80U, 0x81U, 0x00U, 0x00U, 0xC0U, 0x81U, 0x00U, 0x00U,
    };

    std::copy(std::begin(the_data),
              std::end  (the_data),
              reinterpret_cast<volatile std::uint8_t*>(load_address));
  }
}
