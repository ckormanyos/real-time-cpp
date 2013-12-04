#ifndef _MCAL_SAFETY_ROM_CHECKSUM_2013_11_27_H_
  #define _MCAL_SAFETY_ROM_CHECKSUM_2013_11_27_H_

  #include <array>
  #include <cstddef>
  #include <cstdint>
  #include <util/safety/memory/util_safety_rom_memory_checksum.h>

  namespace mcal
  {
    namespace safety
    {
      typedef std::uint16_t type_of_rom_memory_address;

      constexpr std::size_t number_of_rom_memory_blocks = static_cast<std::size_t>(1U);

      typedef util::safety::memory_block<mcal::safety::type_of_rom_memory_address> rom_memory_block_type;

      typedef util::safety::rom_memory_checksum<mcal::safety::type_of_rom_memory_address,
                                                mcal::safety::number_of_rom_memory_blocks> rom_memory_checksum_type;

      typedef rom_memory_checksum_type::memory_list_type rom_memory_checksum_block_list_type;

      extern const rom_memory_checksum_block_list_type rom_memory_block_list;
      extern const type_of_rom_memory_address          rom_memory_result_address;
    }
  }

#endif // _MCAL_SAFETY_ROM_CHECKSUM_2013_11_27_H_
