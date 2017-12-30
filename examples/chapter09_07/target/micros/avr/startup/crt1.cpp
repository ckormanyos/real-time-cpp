///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2018.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdint>

#include <mcal_cpu.h>

extern "C"
{
  struct ctor_type
  {
    typedef void(*function_type)();
  };

  extern ctor_type::function_type _ctors_end[];
  extern ctor_type::function_type _ctors_begin[];
}

namespace crt
{
  void init_ctors() __attribute__((section(".startup"), used, noinline));
}

void crt::init_ctors()
{
  typedef std::uint16_t function_aligned_type;

  for(std::uint8_t* rom_source  = static_cast<std::uint8_t*>(static_cast<void*>(_ctors_end));
                    rom_source != static_cast<std::uint8_t*>(static_cast<void*>(_ctors_begin));
                    rom_source -= sizeof(function_aligned_type))
  {
    // Note that particular care needs to be taken to read program
    // memory with the function mcal_cpu_read_program_memory_word().

    // Acquire the next 16-bit ctor function address.
    const ctor_type::function_type ctor_function_address =
      reinterpret_cast<const ctor_type::function_type>(mcal_cpu_read_program_memory_word(rom_source - 2U));

    // Call the ctor function.
    ctor_function_address();
  }
}
