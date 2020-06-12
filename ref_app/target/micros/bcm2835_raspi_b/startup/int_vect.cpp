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

extern "C" void __my_startup                     () __attribute__((section(".text.startup"), used, noinline));
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

//   __my_startup                     () : This is implemented in crt0.cpp.                                     Position 00.
void __int_vect_undef_instr_handler   () { mcal::irq::secure::int_vect_undef_instr_handler_callback   (); }  // Position 01.
void __int_vect_sw_interrupt_handler  () { mcal::irq::secure::int_vect_sw_interrupt_handler_callback  (); }  // Position 02.
void __int_vect_prefetch_abort_handler() { mcal::irq::secure::int_vect_prefetch_abort_handler_callback(); }  // Position 03.
void __int_vect_data_abort_handler    () { mcal::irq::secure::int_vect_data_abort_handler_callback    (); }  // Position 04.
void __int_vect_unused_05_handler     () { mcal::irq::secure::int_vect_unused_05_handler_callback     (); }  // Position 05.
void __int_vect_irq_handler           () { mcal::irq::secure::int_vect_irq_handler_callback           (); }  // Position 06.
void __int_vect_fiq_handler           () { mcal::irq::secure::int_vect_fiq_handler_callback           (); }  // Position 07.
void __int_vect_future_08_handler     () { mcal::irq::secure::int_vect_future_08_handler_callback     (); }  // Position 08.
void __int_vect_future_09_handler     () { mcal::irq::secure::int_vect_future_09_handler_callback     (); }  // Position 09.
void __int_vect_future_10_handler     () { mcal::irq::secure::int_vect_future_10_handler_callback     (); }  // Position 10.
void __int_vect_future_11_handler     () { mcal::irq::secure::int_vect_future_11_handler_callback     (); }  // Position 11.
void __int_vect_future_12_handler     () { mcal::irq::secure::int_vect_future_12_handler_callback     (); }  // Position 12.
void __int_vect_future_13_handler     () { mcal::irq::secure::int_vect_future_13_handler_callback     (); }  // Position 13.
void __int_vect_future_14_handler     () { mcal::irq::secure::int_vect_future_14_handler_callback     (); }  // Position 14.
void __int_vect_future_15_handler     () { mcal::irq::secure::int_vect_future_15_handler_callback     (); }  // Position 15.

namespace int_vect
{
  void load_lower_interrupt_vector_data(const std::uint32_t load_address);

  void load_lower_interrupt_vector_data(const std::uint32_t load_address)
  {
    // Copy the lower interrupt vector table to the destination
    // address 0x00000000.

    // Here the input parameter "load_address" is hard-wired to be
    // identically equal to zero. In this sense the input parameter
    // "load_address" is unused. We supply this parameter in order
    // to avoid hard-coding a pointer to zero, which would otherwise
    // result in undesired compiler warnings related to zero used
    // instead of nullptr.

    static_cast<void>(load_address);

    volatile std::uint8_t* my_load_address_zero = nullptr;

    // The data below have been extracted from the lower interrupt
    // vector table code that is implemented in "int_vect_table.s".
    // The code has been assembled and linked to address 0x00000000.
    // The corresponding byte code has subsequently been extracted
    // from the hex mask and has been transcribed to the table
    // of hex-values below.

    static const std::uint8_t the_lower_interrupt_vector_table_data[64U] =
    {
      UINT8_C(0x18), UINT8_C(0xF0), UINT8_C(0x9F), UINT8_C(0xE5), UINT8_C(0x18), UINT8_C(0xF0), UINT8_C(0x9F), UINT8_C(0xE5),
      UINT8_C(0x18), UINT8_C(0xF0), UINT8_C(0x9F), UINT8_C(0xE5), UINT8_C(0x18), UINT8_C(0xF0), UINT8_C(0x9F), UINT8_C(0xE5),
      UINT8_C(0x18), UINT8_C(0xF0), UINT8_C(0x9F), UINT8_C(0xE5), UINT8_C(0x18), UINT8_C(0xF0), UINT8_C(0x9F), UINT8_C(0xE5),
      UINT8_C(0x18), UINT8_C(0xF0), UINT8_C(0x9F), UINT8_C(0xE5), UINT8_C(0x18), UINT8_C(0xF0), UINT8_C(0x9F), UINT8_C(0xE5),
      UINT8_C(0x00), UINT8_C(0x84), UINT8_C(0x00), UINT8_C(0x00), UINT8_C(0x40), UINT8_C(0x80), UINT8_C(0x00), UINT8_C(0x00),
      UINT8_C(0x80), UINT8_C(0x80), UINT8_C(0x00), UINT8_C(0x00), UINT8_C(0xC0), UINT8_C(0x80), UINT8_C(0x00), UINT8_C(0x00),
      UINT8_C(0x00), UINT8_C(0x81), UINT8_C(0x00), UINT8_C(0x00), UINT8_C(0x40), UINT8_C(0x81), UINT8_C(0x00), UINT8_C(0x00),
      UINT8_C(0x80), UINT8_C(0x81), UINT8_C(0x00), UINT8_C(0x00), UINT8_C(0xC0), UINT8_C(0x81), UINT8_C(0x00), UINT8_C(0x00),
    };

    // Perform the copy of the lower interrupt vector table data.
    std::copy(std::begin(the_lower_interrupt_vector_table_data),
              std::end  (the_lower_interrupt_vector_table_data),
              my_load_address_zero);
  }
}
