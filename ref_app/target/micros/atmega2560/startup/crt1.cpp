///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2026.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_memory/mcal_memory_progmem_access.h>
#include <util/utility/util_utype_helper.h>

#include <avr/io.h>
#include <avr/pgmspace.h>

#include <cstdint>

extern "C"
{
  struct constructor_function_type
  {
    // Function pointers remain 16-bit on avr-gcc (pointing either directly
    // to <128KB flash or to a linker-generated entry in .trampolines).
    using pointer      = void(*)();
    using pointer_type = util::utype_helper<sizeof(pointer) * 8U>::exact_type;

    // Flash byte addresses on ATmega2560 require 24 bits (stored in 32-bit).
    using address_type = std::uint32_t;

    static constexpr address_type static_size = static_cast<address_type>(sizeof(pointer_type));
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
  // Retrieve true 24-bit far byte addresses of the linker symbols
  // using avr-libc's pgm_get_far_address (handles hh8/hi8/lo8).
  const constructor_function_type::address_type begin_addr = pgm_get_far_address(_ctors_begin);
  const constructor_function_type::address_type end_addr   = pgm_get_far_address(_ctors_end);

  for(constructor_function_type::address_type rom_source = end_addr;
      rom_source > begin_addr;
      rom_source -= constructor_function_type::static_size)
  {
    // Ensure EIND is 0 before each indirect call (EICALL) so that 16-bit
    // function pointers / trampolines resolve in the lower 128 KB word space.
    EIND = 0U;

    // Read the 16-bit function pointer entry from anywhere in the 256 KB flash
    // using ELPM (via pgm_read_word_far, or your own ELPM-based progmem::read).
    const constructor_function_type::pointer_type pf =
      pgm_read_word_far(rom_source - constructor_function_type::static_size);

    // Call the constructor function.
    (reinterpret_cast<constructor_function_type::pointer>(pf))();
  }

  // Leave RAMPZ cleared so standard 16-bit LPM operations in user code work as expected.
  RAMPZ = 0U;
}
