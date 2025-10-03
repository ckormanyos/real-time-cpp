///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter03_02-001_fixed_size_integer.cpp

#include <cstdint>
#include <iomanip>
#include <iostream>

// This has *exactly* 16-bits signed.
constexpr std::int16_t value16 { INT16_C(0x7FFF) };

// This has *at least* 32-bits unsigned.
constexpr std::uint_least32_t value32
  { UINT32_C(4'294'967'295) };

auto main() -> int
{
  std::cout << std::hex << std::showbase << value16 << std::endl;

  std::cout << std::dec << value32 << std::endl;
}
