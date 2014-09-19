///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

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
      typedef std::uint32_t type_of_rom_memory_address;

      enum enum_number_of_rom_memory_blocks
      {
        number_of_rom_memory_blocks = 1
      };

      typedef util::safety::memory_block<mcal::safety::type_of_rom_memory_address> rom_memory_block_type;

      typedef util::safety::rom_memory_checksum<mcal::safety::type_of_rom_memory_address,
                                                mcal::safety::number_of_rom_memory_blocks> rom_memory_checksum_type;

      typedef rom_memory_checksum_type::memory_list_type rom_memory_checksum_block_list_type;

      extern const rom_memory_checksum_block_list_type rom_memory_block_list;
      extern const type_of_rom_memory_address          rom_memory_result_address;
    }
  }

#endif // _MCAL_SAFETY_DRAM_2013_11_25_H_
