///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <iostream>

// chapter05_06-002_template_enable_if.cpp

// The original add template function.
template<typename T>
auto add(T a, T b) noexcept
  -> std::enable_if_t<!std::is_floating_point_v<T>, T>
{
  return a + b;
}

// Easy-to-detect errors for float, double
// and long double.

template<typename T>
auto add(T, T) noexcept
  -> std::enable_if_t<std::is_floating_point_v<T>, T>
{
  // Explicitly create an erroneous result!
  return T { 0.0F };
}

auto main() -> int;

auto main() -> int
{
  // 3
  std::cout << add(1, 2) << std::endl;

  // 0
  std::cout << add(1.0F, 2.0F) << std::endl;
}
