
#include <cstdint>
#include <mcal_safety_rom_checksum.h>
#include <util/safety/memory/util_safety_rom_memory_checksum.h>

extern "C"
{
  extern std::uintptr_t _data_begin;     // Start address for the .data section (the lowest DRAM address).
  extern std::uintptr_t _stack_begin;    // Start address for the lower end of the stack (one past the highest DRAM address).
  extern std::uintptr_t _rom_begin;      // Start address for the program ROM section (the lowest ROM address).
  extern std::uintptr_t _rom_end;        // End   address for the program ROM section (one past the highest ROM address).
}

namespace mcal
{
  namespace safety
  {
    const rom_memory_checksum_block_list_type rom_memory_block_list =
    {{
      rom_memory_block_type(reinterpret_cast<type_of_rom_memory_address>(&_rom_begin),
                            reinterpret_cast<type_of_rom_memory_address>(&_rom_end) - reinterpret_cast<type_of_rom_memory_address>(&_rom_begin))
    }};

    const type_of_rom_memory_address rom_memory_result_address = reinterpret_cast<type_of_rom_memory_address>(&_rom_end);
  }
}
