///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019 - 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter03_08-003_constexpr_pown.cpp

#include <cstdint>
#include <iostream>

inline constexpr std::uintmax_t pown(std::uintmax_t x, std::uintmax_t n)
{
  return ((n == 0U) ? UINTMAX_C(1) : pown(x, n - 1U) * x);
}

// 1000 is computed at compile time.
constexpr std::uintmax_t t3 { pown(10U, 3U) };

// OK because t3 is compile-time constant.
static_assert(t3 == 1000U,
              "Error: Unexpected constexpr");

auto main() -> int
{
  std::cout << "t3: " << t3 << std::endl;
}
