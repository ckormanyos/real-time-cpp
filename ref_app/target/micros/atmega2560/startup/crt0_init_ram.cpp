///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2026.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_memory/mcal_memory_progmem_access.h>
#include <mcal_reg.h>

#include <algorithm>
#include <cstddef>
#include <cstdint>

extern "C"
{
  extern std::uint8_t   _rom_data_begin[]; // Start address for the initialization values of the rom-to-ram section.
  extern std::uintptr_t _data_begin;       // Start address for the .data section.
  extern std::uintptr_t _data_end;         // End address for the .data section.
  extern std::uintptr_t _bss_begin;        // Start address for the .bss section.
  extern std::uintptr_t _bss_end;          // End address for the .bss section.
}

namespace crt
{
  void init_ram() __attribute__((section(".startup"), used, noinline));
}

void crt::init_ram()
{
  using memory_aligned_type = std::uint16_t;
  using far_address_type    = std::uint32_t;

  // Copy the data segment initializers from rom-to-ram.
  // Note that all data segments are aligned by 2.
  const std::size_t size_data =
    std::size_t(  static_cast<const memory_aligned_type*>(static_cast<const void*>(&_data_end))
                - static_cast<const memory_aligned_type*>(static_cast<const void*>(&_data_begin)));

  // Retrieve the true 24-bit unsigned flash byte address without 16-bit pointer
  // truncation or sign-extension at >= 0x8000.
  far_address_type rom_source = pgm_get_far_address(_rom_data_begin);

  std::for_each(static_cast<memory_aligned_type*>(static_cast<void*>(&_data_begin)),
                static_cast<memory_aligned_type*>(static_cast<void*>(&_data_begin)) + size_data,
                [&rom_source](memory_aligned_type& ram_destination)
                {
                  // Read 16-bit initializer from anywhere in the 256 KB flash via ELPM.
                  ram_destination = pgm_read_word_far(rom_source);

                  // Acquire the next 16-bit address of the rom-source.
                  rom_source += 2U;
                });

  // Restore RAMPZ to 0 so subsequent 16-bit LPM reads in user code are unaffected.
  mcal::reg::reg_access_static<std::uint8_t,
                               std::uint8_t,
                               mcal::reg::rampz,
                               UINT8_C(0)>::reg_set();

  // Clear the bss segment.
  // Note that the bss segment is aligned by 2.
  std::fill(static_cast<memory_aligned_type*>(static_cast<void*>(&_bss_begin)),
            static_cast<memory_aligned_type*>(static_cast<void*>(&_bss_end)),
            static_cast<memory_aligned_type>(0U));
}
