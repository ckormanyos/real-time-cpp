///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2024.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#if (defined(__GNUC__) && (__GNUC__ >= 12))
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Warray-bounds"
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wstringop-overflow"
#endif

#include <algorithm>
#include <cstddef>
#include <cstdint>

extern "C"
{
  extern std::uintptr_t rom_data_begin; // Start address for the initialization values of the rom-to-ram section.
  extern std::uintptr_t data_begin;     // Start address for the .data section.
  extern std::uintptr_t data_end;       // End address for the .data section.
  extern std::uintptr_t bss_begin;      // Start address for the .bss section.
  extern std::uintptr_t bss_end;        // End address for the .bss section.
}

namespace crt
{
  void init_ram();
}

void crt::init_ram()
{
  typedef std::uint32_t memory_aligned_type;

  // Copy the data segment initializers from ROM to RAM.
  // Note that all data segments are aligned by 4.
  const std::size_t size_data =
    std::size_t(  static_cast<const memory_aligned_type*>(static_cast<const void*>(&data_end))
                - static_cast<const memory_aligned_type*>(static_cast<const void*>(&data_begin)));

  std::copy(static_cast<const memory_aligned_type*>(static_cast<const void*>(&rom_data_begin)),
            static_cast<const memory_aligned_type*>(static_cast<const void*>(&rom_data_begin)) + size_data,
            static_cast<      memory_aligned_type*>(static_cast<      void*>(&data_begin)));

  // Clear the bss segment.
  std::fill(static_cast<memory_aligned_type*>(static_cast<void*>(&bss_begin)),
            static_cast<memory_aligned_type*>(static_cast<void*>(&bss_end)),
            static_cast<memory_aligned_type>(0U));
}

#if (defined(__GNUC__) && (__GNUC__ >= 12))
#pragma GCC diagnostic pop
#pragma GCC diagnostic pop
#endif
