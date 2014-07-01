///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdint>
#include <mcal_safety_dram.h>
#include <util/safety/memory/util_safety_dram_memory_refresh.h>

extern "C"
{
  extern std::uintptr_t data_begin;     // Start address for the .data section (the lowest DRAM address).
  extern std::uintptr_t stack_begin;    // Start address for the lower end of the stack (one past the highest DRAM address).
}

namespace mcal
{
  namespace safety
  {
    const dram_memory_block_list_type dram_memory_block_list =
    {{
      dram_memory_block_type(reinterpret_cast<type_of_dram_memory_address>(&data_begin),
                             reinterpret_cast<type_of_dram_memory_address>(&stack_begin) - reinterpret_cast<type_of_dram_memory_address>(&data_begin))
    }};
  }
}

