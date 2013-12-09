
#include <array>
#include <cstdint>
#include <mcal_safety_rom_checksum.h>
#include <util/safety/memory/util_safety_rom_memory_checksum.h>

namespace
{
  std::array<std::uint8_t,  9U + 4U> dummy_rom =
  {{
    0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39,
    0x89, 0xA1, 0x89, 0x7F
  }};
}

namespace mcal
{
  namespace safety
  {
    const rom_memory_checksum_block_list_type rom_memory_block_list =
    {{
      rom_memory_block_type(reinterpret_cast<type_of_rom_memory_address>(dummy_rom.data()), dummy_rom.size() - 4U)
    }};

    const type_of_rom_memory_address rom_memory_result_address = reinterpret_cast<type_of_rom_memory_address>(&dummy_rom[dummy_rom.size() - 4U]);
  }
}
