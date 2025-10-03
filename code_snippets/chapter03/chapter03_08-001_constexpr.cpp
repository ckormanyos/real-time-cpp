///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter03_08-001_constexpr.cpp

#include <iostream>

// A compile-time constant version number.
constexpr unsigned int version { 3U };

// A compile-time floating-point value.
constexpr float pi { 3.1415926535'8979323846F };

auto main() -> int
{
  std::cout << "version is " << version << std::endl;

  std::cout << "pi is " << pi << std::endl;
}
