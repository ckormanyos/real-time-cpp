///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2024.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <algorithm>
#include <cstddef>
#include <cstdint>

extern "C"
{
  extern std::uintptr_t _rom_data_begin; // Start address for the initialization values of the rom-to-ram section.
  extern std::uintptr_t _data_begin;     // Start address for the .data section.
  extern std::uintptr_t _data_end;       // End address for the .data section.
  extern std::uintptr_t _bss_begin;      // Start address for the .bss section.
  extern std::uintptr_t _bss_end;        // End address for the .bss section.

  extern std::uintptr_t _srom_data_begin; // Start address for the initialization values of the rom-to-sram section.
  extern std::uintptr_t _sdata_begin;     // Start address for the .sdata section.
  extern std::uintptr_t _sdata_end;       // End address for the .sdata section.
  extern std::uintptr_t _sbss_begin;      // Start address for the .sbss section.
  extern std::uintptr_t _sbss_end;        // End address for the .sbss section.
}

namespace crt
{
  void init_ram();
}

void crt::init_ram()
{
  using memory_aligned_type = std::uint8_t;

  // Copy the sdata segment initializers from ROM to RAM.
  // Note that all data segments are aligned by 1.
  const std::size_t size_sdata =
    std::size_t(  static_cast<const memory_aligned_type*>(static_cast<const void*>(&_sdata_end))
                - static_cast<const memory_aligned_type*>(static_cast<const void*>(&_sdata_begin)));

  std::copy(static_cast<const memory_aligned_type*>(static_cast<const void*>(&_srom_data_begin)),
            static_cast<const memory_aligned_type*>(static_cast<const void*>(&_srom_data_begin)) + size_sdata,
            static_cast<      memory_aligned_type*>(static_cast<      void*>(&_sdata_begin)));

  // Clear the sbss segment.
  // Note that the bss segment is aligned by 1.
  std::fill(static_cast<memory_aligned_type*>(static_cast<void*>(&_sbss_begin)),
            static_cast<memory_aligned_type*>(static_cast<void*>(&_sbss_end)),
            static_cast<memory_aligned_type>(0U));

  // Copy the data segment initializers from ROM to RAM.
  // Note that all data segments are aligned by 1.
  const std::size_t size_data =
    std::size_t(  static_cast<const memory_aligned_type*>(static_cast<const void*>(&_data_end))
                - static_cast<const memory_aligned_type*>(static_cast<const void*>(&_data_begin)));

  std::copy(static_cast<const memory_aligned_type*>(static_cast<const void*>(&_rom_data_begin)),
            static_cast<const memory_aligned_type*>(static_cast<const void*>(&_rom_data_begin)) + size_data,
            static_cast<      memory_aligned_type*>(static_cast<      void*>(&_data_begin)));

  // Clear the bss segment.
  // Note that the bss segment is aligned by 1.
  std::fill(static_cast<memory_aligned_type*>(static_cast<void*>(&_bss_begin)),
            static_cast<memory_aligned_type*>(static_cast<void*>(&_bss_end)),
            static_cast<memory_aligned_type>(0U));
}
