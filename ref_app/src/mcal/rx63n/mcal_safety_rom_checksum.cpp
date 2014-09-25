///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdint>
#include <mcal_safety_rom_checksum.h>
#include <util/safety/memory/util_safety_rom_memory_checksum.h>

extern "C"
{
  extern std::uintptr_t rom_begin;      // Start address for the program ROM section (the lowest ROM address).
  extern std::uintptr_t rom_end;        // End   address for the program ROM section (one past the highest ROM address).
}

namespace mcal
{
  namespace safety
  {
    const rom_memory_checksum_block_list_type rom_memory_block_list =
    {{
      rom_memory_block_type(reinterpret_cast<type_of_rom_memory_address>(&rom_begin),
                            reinterpret_cast<type_of_rom_memory_address>(&rom_end) - reinterpret_cast<type_of_rom_memory_address>(&rom_begin))
    }};

    const type_of_rom_memory_address rom_memory_result_address = reinterpret_cast<type_of_rom_memory_address>(&rom_end);
  }
}
