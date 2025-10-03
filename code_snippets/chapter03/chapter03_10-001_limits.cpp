///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter03_10-001_limits.cpp

#include <iostream>
#include <limits>

// This is 31 on a system with 4 byte int.
// The sign bit is not included in digits.
constexpr int n_dig = std::numeric_limits<int>::digits;

// This is 2,147,483,647 if int is 4 bytes.
constexpr int n_max { (std::numeric_limits<int>::max)() };

// Compile-time check if float conforms to IEEE-754.
static_assert(std::numeric_limits<float>::is_iec559,
              "float is not IEEE754 conforming!");

constexpr bool is_ieee754_conform
  { std::numeric_limits<float>::is_iec559 };

auto main() -> int
{
  std::cout << "n_dig is " << n_dig << std::endl;

  std::cout << "n_max is " << n_max << std::endl;

  std::cout << "is_ieee754_conform is " << std::boolalpha << is_ieee754_conform << std::endl;
}
