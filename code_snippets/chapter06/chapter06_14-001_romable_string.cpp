///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter06_14-001_romable_string.cpp

#include <initializer_list>
#include <iostream>

namespace
{
  // A version that is compile-time constant.
  const std::initializer_list<char> version_string
  {
    '1', '.', '2', '3', '\0'
  };
}

auto main() -> int;

auto main() -> int
{
  std::cout << "version_string: " << version_string.begin() << std::endl;
}
