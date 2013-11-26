
#include <array>
#include <cstdint>
#include <mcal_safety_dram.h>
#include <util/safety/memory/util_safety_dram_memory_refresh.h>

namespace
{
  std::array<std::uint8_t, 256U> dummy_dram;
}

namespace mcal
{
  namespace safety
  {
    const dram_memory_block_list_type dram_memory_block_list =
    {{
      dram_memory_block_type(reinterpret_cast<type_of_dram_memory_address>(dummy_dram.data()), dummy_dram.size())
    }};
  }
}
