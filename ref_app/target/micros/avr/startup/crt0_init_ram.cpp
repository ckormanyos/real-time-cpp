///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2014.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <mcal_cpu.h>
#include <util/utility/util_two_part_data_manipulation.h>

extern "C"
{
  extern std::uintptr_t _rom_data_begin;  // Start address for the initialization values of the rom-to-ram section.
  extern std::uintptr_t _data_begin;      // Start address for the .data section.
  extern std::uintptr_t _data_end;        // End address for the .data section.
  extern std::uintptr_t _bss_begin;       // Start address for the .bss section.
  extern std::uintptr_t _bss_end;         // End address for the .bss section.
}

namespace crt
{
  void init_ram() __attribute__((section(".startup")));
}

void crt::init_ram()
{
  typedef std::uint16_t memory_aligned_type;

  // Copy the data segment initializers from rom-to-ram.
  // Note that all data segments are aligned by 2.
  const std::size_t size = std::size_t(  static_cast<const memory_aligned_type*>(static_cast<const void*>(&_data_end))
                                       - static_cast<const memory_aligned_type*>(static_cast<const void*>(&_data_begin)));


  volatile std::uint8_t* rom_source = static_cast<volatile std::uint8_t*>(static_cast<volatile void*>(&_rom_data_begin));

  std::for_each(static_cast<memory_aligned_type*>(static_cast<void*>(&_data_begin)),
                static_cast<memory_aligned_type*>(static_cast<void*>(&_data_begin)) + size,
                [&rom_source](memory_aligned_type& data_ram_value)
                {
                  // Note that particular care needs to be taken to read program
                  // memory with the function mcal::cpu::read_program_memory().

                  // Acquire the next 16-bit rom-value located at the address
                  // of the rom-source.
                  const std::uint16_t const_rom_value =
                    util::make_long(mcal::cpu::read_program_memory(rom_source + 0U),
                                    mcal::cpu::read_program_memory(rom_source + 1U));

                  // Copy the value from constant-rom to data-ram.
                  data_ram_value = const_rom_value;

                  rom_source += 2U;
                });

  // Clear the bss segment.
  // Note that the bss segment is aligned by 2.
  std::fill(static_cast<memory_aligned_type*>(static_cast<void*>(&_bss_begin)),
            static_cast<memory_aligned_type*>(static_cast<void*>(&_bss_end)),
            static_cast<memory_aligned_type>(0U));
}
