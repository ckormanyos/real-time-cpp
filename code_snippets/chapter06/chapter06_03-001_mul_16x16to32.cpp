///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2018 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter06_03-001_mul_16x16to32.cpp

#include <cstdint>
#include <iostream>

namespace
{
  std::uint16_t a { UINT16_C(55555) };
  std::uint16_t b { UINT16_C(61234) };
}

auto do_something() -> void;

auto do_something() -> void
{
  // Unsigned 16 x 16 --> 32-bit.
  // 55555 * 61234 = 3401854870

  // Cast and multiply.
  std::uint32_t result
    { a * static_cast<std::uint32_t>(b) };

  std::cout << result << std::endl;
}

auto main() -> int;

auto main() -> int
{
  do_something();
}
