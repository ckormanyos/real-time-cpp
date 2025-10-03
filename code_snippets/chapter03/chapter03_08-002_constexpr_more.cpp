///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter03_08-002_constexpr_more.cpp

#include <algorithm>
#include <array>
#include <iostream>
#include <iterator>

// A compile-time constant function of low complexity.
inline constexpr int three() { return 3; }

// A constant array of integers.
constexpr std::array<int, 3U> my_array
{
  { 1, 2, 3 }
};

struct version_information
{
  // A compile-time constant member variable.
  static constexpr unsigned version { 7U };
};

auto main() -> int
{
  std::cout << "three() is " << three() << std::endl;

  std::cout << "my_array is ";
  std::copy(my_array.cbegin(), my_array.cend(), std::ostream_iterator<int>(std::cout, ","));
  std::cout << std::endl;

  std::cout << "version_information::version is " << version_information::version << std::endl;
}
