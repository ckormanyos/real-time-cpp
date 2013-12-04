
#include <array>
#include <cstdint>
#include <mcal_safety_rom_checksum.h>
#include <util/safety/memory/util_safety_rom_memory_checksum.h>

namespace
{
  std::array<std::uint8_t,  64U> dummy_rom =
  {{
     0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
     1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U,
     2U, 2U, 2U, 2U, 2U, 2U, 2U, 2U,
     3U, 3U, 3U, 3U, 3U, 3U, 3U, 3U,
     4U, 4U, 4U, 4U, 4U, 4U, 4U, 4U,
     5U, 5U, 5U, 5U, 5U, 5U, 5U, 5U,
     6U, 6U, 6U, 6U, 6U, 6U, 6U, 6U,
     7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U
  }};
}

namespace mcal
{
  namespace safety
  {
    const rom_memory_checksum_block_list_type rom_memory_block_list =
    {{
      rom_memory_block_type(reinterpret_cast<type_of_rom_memory_address>(dummy_rom.data()), dummy_rom.size())
    }};
  }
}
