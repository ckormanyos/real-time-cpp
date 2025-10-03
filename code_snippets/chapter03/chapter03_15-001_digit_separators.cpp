///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter03_15-001_digit_separators.cpp

#include <cstdint>
#include <iostream>

constexpr std::uint64_t one_trillion
  { UINT64_C(1'000'000'000'000) };

auto main() -> int
{
  std::cout << "one_trillion is " << one_trillion << std::endl;
}
