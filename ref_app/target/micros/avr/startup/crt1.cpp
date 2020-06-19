///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdint>

#include <mcal_memory/mcal_memory_progmem_access.h>
#include <util/utility/util_utype_helper.h>

extern "C"
{
  struct constructor_function_type
  {
    using pointer = void(*)(void);

    using size_type =
      util::utype_helper<sizeof(pointer) * 8U>::exact_type;

    static constexpr size_type static_size = static_cast<size_type>(sizeof(size_type));
  };

  extern constructor_function_type::pointer _ctors_end[];
  extern constructor_function_type::pointer _ctors_begin[];
}

namespace crt
{
  void init_ctors() __attribute__((section(".startup"), used, noinline));
}

void crt::init_ctors()
{
  for(constructor_function_type::size_type rom_source
                  = reinterpret_cast<constructor_function_type::size_type>(static_cast<void*>(_ctors_end));
      rom_source  > reinterpret_cast<constructor_function_type::size_type>(static_cast<void*>(_ctors_begin));
      rom_source -= constructor_function_type::static_size)
  {
    // Note that particular care needs to be taken to read program
    // memory with the function mcal::memory::progmem::read.

    // Acquire the next constructor function address.
    const constructor_function_type::size_type pf =
      mcal::memory::progmem::read<constructor_function_type::size_type>(rom_source - constructor_function_type::static_size);

    // Call the constructor function.
    (reinterpret_cast<const constructor_function_type::pointer>(pf))();
  }
}
