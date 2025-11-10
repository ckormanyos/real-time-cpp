///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <algorithm>
#include <cstddef>
#include <cstdint>

#include <mcal_memory/mcal_memory_progmem_access.h>

extern "C"
{
  extern mcal_progmem_uintptr_t _rom_data_begin;  // Start address for the initialization values of the rom-to-ram section.
  extern std::uintptr_t         _data_begin;      // Start address for the .data section.
  extern std::uintptr_t         _data_end;        // End address for the .data section.
  extern std::uintptr_t         _bss_begin;       // Start address for the .bss section.
  extern std::uintptr_t         _bss_end;         // End address for the .bss section.
}

namespace crt
{
  void init_ram() __attribute__((section(".startup"), used, noinline));
}

void crt::init_ram()
{
  // Copy the data segment initializers from rom-to-ram.
  mcal_progmem_uintptr_t rom_source = (mcal_progmem_uintptr_t) &_rom_data_begin;

  volatile std::uint8_t* first = (volatile std::uint8_t*) &_data_begin;
  volatile std::uint8_t* last  = (volatile std::uint8_t*) &_data_end;

  for(volatile std::uint8_t* it = first; it !=  last; ++it)
  {
    // Note that particular care needs to be taken to read program
    // memory with the function mcal::memory::progmem::read().

    // Copy the data from the rom-source to the ram-destination.
    *it = mcal::memory::progmem::read<std::uint8_t>(rom_source);

    // Acquire the next address of the rom-source.
    ++rom_source;
  };

  // Clear the bss segment.
  // Note that the bss segment is aligned by 2.
  std::fill((std::uint8_t*) &_bss_begin, (std::uint8_t*) &_bss_end, 0U);
}
