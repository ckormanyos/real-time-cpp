///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdint>

#include <mcal/memory/mcal_memory_progmem_access.h>
#include <util/utility/util_utype_helper.h>

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
  using function_aligned_integral_type =
    util::utype_helper<sizeof(void(*)(void)) * 8U>::exact_type;

  for(std::uint8_t* rom_source  = static_cast<std::uint8_t*>(static_cast<void*>(_ctors_end));
                    rom_source != static_cast<std::uint8_t*>(static_cast<void*>(_ctors_begin));
                    rom_source -= sizeof(function_aligned_integral_type))
  {
    // Note that particular care needs to be taken to read program
    // memory with the function mcal::cpu::read_program_memory.

    // Acquire the next constructor function address.
    const function_aligned_integral_type ctor_function_address =
      mcal::memory::progmem::read(reinterpret_cast<function_aligned_integral_type*>(rom_source - sizeof(function_aligned_integral_type)));

    // Call the constructor function.
    (reinterpret_cast<const ctor_type::function_type>(ctor_function_address))();
  }
}
