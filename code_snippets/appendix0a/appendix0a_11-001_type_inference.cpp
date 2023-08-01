///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019 - 2023.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// appendix0a_10-002_initializer_list.cpp

#include <cstdint>
#include <initializer_list>
#include <iostream>
#include <numeric>

// appendix0a_11-001_type_inference.cpp

// The type of n is int.
auto n = static_cast<int>(INT8_C(3));

// The type of u is std::uint8_t.
auto u = static_cast<std::uint8_t>(UINT8_C(3));

// The type of lst is std::initializer_list<int>.
auto lst =
{
  static_cast<int>(INT8_C(1)),
  static_cast<int>(INT8_C(2)),
  static_cast<int>(INT8_C(3))
};

auto main() -> int;

auto main() -> int
{
  const auto sum = std::accumulate(lst.begin(), lst.end(), static_cast<int>(INT8_C(0)));

  std::cout << "sum: " << sum << std::endl;
}
