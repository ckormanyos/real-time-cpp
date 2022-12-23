///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2022.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstddef>
#include <cstdint>

extern "C"
{
  extern std::uintptr_t _rom_data_begin; // Start address for the initialization values of the rom-to-ram section.
  extern std::uintptr_t _data_begin;     // Start address for the .data section.
  extern std::uintptr_t _data_end;       // End address for the .data section.
  extern std::uintptr_t _bss_begin;      // Start address for the .bss section.
  extern std::uintptr_t _bss_end;        // End address for the .bss section.
}

namespace crt
{
  void init_ram();
}

void crt::init_ram()
{
  // Copy the data segment initializers from ROM to RAM.
  const auto count_data =
    static_cast<std::size_t>
    (
      (std::uintptr_t) &_data_end - (std::uintptr_t) &_data_begin
    );

  for(auto i = static_cast<std::size_t>(UINT8_C(0)); i < count_data; ++i)
  {
    ((std::uint8_t*) &_data_begin)[i] = ((std::uint8_t*) &_rom_data_begin)[i];
  }

  // Clear the bss segment.
  const auto count_bss =
    static_cast<std::size_t>
    (
      (std::uintptr_t) &_bss_end - (std::uintptr_t) &_bss_begin
    );

  for(auto i = static_cast<std::size_t>(UINT8_C(0)); i < count_bss; ++i)
  {
    ((std::uint8_t*) &_bss_begin)[i] = static_cast<std::uint8_t>(UINT8_C(0));
  }
}
