///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdint>

#include <mcal_memory/mcal_memory_progmem_access.h>

#include <util/utility/util_attribute.h>
#include <util/utility/util_utype_helper.h>

extern "C"
{
  struct ctor_type
  {
    using function_type = void(*)();

    using function_pointer_as_uint_type =
      util::utype_helper<sizeof(function_type) * 8U>::exact_type;

    static constexpr auto function_size = static_cast<function_pointer_as_uint_type>(sizeof(function_pointer_as_uint_type));
  };

  extern ctor_type::function_type _ctors_end;
  extern ctor_type::function_type _ctors_begin;
}

namespace crt
{
  void init_ctors() ATTRIBUTE(section(".startup"), used, noinline);
}

void crt::init_ctors()
{
  for(auto rom_source  = reinterpret_cast<ctor_type::function_pointer_as_uint_type>(static_cast<void*>(&_ctors_end));
           rom_source  > reinterpret_cast<ctor_type::function_pointer_as_uint_type>(static_cast<void*>(&_ctors_begin));
           rom_source -= ctor_type::function_size)
  {
    // Note that particular care needs to be taken to read program
    // memory with the function mcal::memory::progmem::read.

    // Acquire the next constructor function address.
    const auto pf =
      mcal::memory::progmem::read<ctor_type::function_pointer_as_uint_type>(rom_source - ctor_type::function_size);

    // Call the constructor function.
    (reinterpret_cast<ctor_type::function_type>(pf))();
  }
}
