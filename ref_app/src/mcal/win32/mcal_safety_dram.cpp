///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <array>
#include <cstdint>
#include <mcal_safety_dram.h>
#include <util/safety/memory/util_safety_dram_memory_refresh.h>

namespace
{
  std::array<std::uint8_t, 32U> dummy_dram;
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
