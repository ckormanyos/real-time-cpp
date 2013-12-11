///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _MCAL_SAFETY_DRAM_2013_11_25_H_
  #define _MCAL_SAFETY_DRAM_2013_11_25_H_

  #include <array>
  #include <cstddef>
  #include <cstdint>
  #include <util/safety/memory/util_safety_dram_memory_refresh.h>

  namespace mcal
  {
    namespace safety
    {
      typedef std::uint32_t type_of_dram_memory_address;

      enum enum_number_of_dram_memory_blocks
      {
        number_of_dram_memory_blocks = 1
      };

      typedef util::safety::memory_block<mcal::safety::type_of_dram_memory_address> dram_memory_block_type;

      typedef util::safety::dram_memory_refresh<mcal::safety::type_of_dram_memory_address,
                                                mcal::safety::number_of_dram_memory_blocks> dram_memory_refresh_type;

      typedef dram_memory_refresh_type::memory_list_type dram_memory_block_list_type;

      extern const dram_memory_block_list_type dram_memory_block_list;
    }
  }

#endif // _MCAL_SAFETY_DRAM_2013_11_25_H_
