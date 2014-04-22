/////////////////////////////////////////////////////// 
//  Copyright 2013 Stephan Hage.
//  Copyright 2013 Christopher Kormanyos.
//  Distributed under the Boost 
//  Software License, Version 1.0. 
//  (See accompanying file LICENSE_1_0.txt 
//  or copy at http://www.boost.org/LICENSE_1_0.txt ) 
//

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
  // Copy the data segment initializers from ROM to RAM.
  const std::size_t size = std::size_t(  static_cast<const std::uint8_t*>(static_cast<const void*>(&data_end))
                                       - static_cast<const std::uint8_t*>(static_cast<const void*>(&data_begin)));

  std::copy(static_cast<const std::uint8_t*>(static_cast<const void*>(&rom_data_begin)),
            static_cast<const std::uint8_t*>(static_cast<const void*>(&rom_data_begin)) + size,
            static_cast<      std::uint8_t*>(static_cast<      void*>(&data_begin)));

  // Clear the bss segment.
  std::fill(static_cast<std::uint8_t*>(static_cast<void*>(&bss_begin)),
            static_cast<std::uint8_t*>(static_cast<void*>(&bss_end)),
            static_cast<std::uint8_t>(0U));
}
