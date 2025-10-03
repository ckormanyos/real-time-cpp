///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter03_09-001_static_assert.cpp

#include <iostream>

constexpr unsigned int version { 3U };

// Print an error if version is less than 2.
static_assert(version >= 2U, "Version is too low!");

auto main() -> int
{
  std::cout << "version is " << version << std::endl;
}
