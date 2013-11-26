
#include <cstdint>
#include <mcal_safety_dram.h>
#include <util/safety/memory/util_safety_dram_memory_refresh.h>

extern "C"
{
  extern std::uintptr_t _data_begin;     // Start address for the .data section (the lowest DRAM address).
  extern std::uintptr_t _stack_begin;    // Start address for the lower end of the stack (one past the highest DRAM address).
}

namespace mcal
{
  namespace safety
  {
    const dram_memory_block_list_type dram_memory_block_list =
    {{
      dram_memory_block_type(reinterpret_cast<type_of_dram_memory_address>(&_data_begin),
                             reinterpret_cast<type_of_dram_memory_address>(&_stack_begin) - reinterpret_cast<type_of_dram_memory_address>(&_data_begin))
    }};
  }
}
