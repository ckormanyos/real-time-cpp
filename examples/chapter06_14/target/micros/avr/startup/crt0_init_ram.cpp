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
  typedef std::uint16_t memory_aligned_type;

  // Copy the data segment initializers from rom-to-ram.
  // Note that all data segments are aligned by 2.
  const std::size_t size_data =
    std::size_t(  static_cast<const memory_aligned_type*>(static_cast<const void*>(&_data_end))
                - static_cast<const memory_aligned_type*>(static_cast<const void*>(&_data_begin)));

  mcal_progmem_uintptr_t rom_source = reinterpret_cast<mcal_progmem_uintptr_t>(static_cast<void*>(&_rom_data_begin));

  std::for_each(static_cast<memory_aligned_type*>(static_cast<void*>(&_data_begin)),
                static_cast<memory_aligned_type*>(static_cast<void*>(&_data_begin)) + size_data,
                [&rom_source](memory_aligned_type& ram_destination)
                {
                  // Note that particular care needs to be taken to read program
                  // memory with the function mcal::memory::progmem::read().

                  // Copy the data from the rom-source to the ram-destination.
                  ram_destination =
                    mcal::memory::progmem::read<std::uint16_t>(rom_source);

                  // Acquire the next 16-bit address of the rom-source.
                  rom_source += 2U;
                });

  // Clear the bss segment.
  // Note that the bss segment is aligned by 2.
  std::fill(static_cast<memory_aligned_type*>(static_cast<void*>(&_bss_begin)),
            static_cast<memory_aligned_type*>(static_cast<void*>(&_bss_end)),
            static_cast<memory_aligned_type>(0U));
}
