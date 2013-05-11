///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdint>
#include <algorithm>

asm volatile (".extern _rom_data_begin"); // Start address for the initialization values of the rom-to-ram section.
asm volatile (".extern _data_begin");     // Start address for the .data section.
asm volatile (".extern _data_end");       // End address for the .data section.

extern "C"
{
  extern std::uintptr_t _bss_begin;       // Start address for the .bss section.
  extern std::uintptr_t _bss_end;         // End address for the .bss section.
}

namespace
{
  void do_copy_data() __attribute__ ((section(".init4")));
  void do_clear_bss() __attribute__ ((section(".init4")));

  void do_copy_data()
  {
    // Copy the data segment initializers from ROM to RAM.
    asm volatile ("ldi  r17, hi8(_data_end)");
    asm volatile ("ldi  r26, lo8(_data_begin)");
    asm volatile ("ldi  r27, hi8(_data_begin)");
    asm volatile ("ldi  r30, lo8(_rom_data_begin)");
    asm volatile ("ldi  r31, hi8(_rom_data_begin)");

    asm volatile ("rjmp  .L__do_copy_data_start");

    asm volatile (".L__do_copy_data_loop:");

    asm volatile ("lpm  r0, Z+");
    asm volatile ("st  X+, r0");

    asm volatile (".L__do_copy_data_start:");

    asm volatile ("cpi  r26, lo8(_data_end)");
    asm volatile ("cpc  r27, r17");
    asm volatile ("brne  .L__do_copy_data_loop");
  }

  void do_clear_bss()
  {
    // Clear the bss segment.
    std::fill(static_cast<std::uint8_t*>(static_cast<void*>(&_bss_begin)),
              static_cast<std::uint8_t*>(static_cast<void*>(&_bss_end)),
              static_cast<std::uint8_t>(0U));
  }
}

namespace crt
{
  void init_ram()
  {
    do_copy_data();
    do_clear_bss();
  }
}
