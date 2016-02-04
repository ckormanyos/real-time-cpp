///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2016.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdint>
#include <mcal_cpu.h>
#include <util/utility/util_two_part_data_manipulation.h>

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
  void init_ctors() __attribute__((section(".startup")));
}

void crt::init_ctors()
{
  for(ctor_type::function_type* pf = _ctors_end - 1U; pf >= _ctors_begin; --pf)
  {
    // Note that particular care needs to be taken to read program
    // memory with the function mcal::cpu::read_program_memory().

    volatile std::uint8_t* rom_source = static_cast<volatile std::uint8_t*>(static_cast<volatile void*>(pf));

    // Acquire the individual bytes of the next 16-bit ctor function address.
    const std::uint8_t addr_lo = mcal::cpu::read_program_memory(rom_source + 0U);
    const std::uint8_t addr_hi = mcal::cpu::read_program_memory(rom_source + 1U);

    // Create the address of the ctor function.
    const ctor_type::function_type ctor_function_address
      = reinterpret_cast<const ctor_type::function_type>(util::make_long(addr_lo, addr_hi));

    // Call the ctor function.
    ctor_function_address();
  }
}
