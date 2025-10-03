///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter01_07-001_namespace.cpp

#include <iostream>

namespace this_space
{
  constexpr int version = 1;
}

namespace another_space
{
  constexpr int version = 3;
}

auto main() -> int
{
  // 1
  std::cout << this_space::version << std::endl;

  // 3
  std::cout << another_space::version << std::endl;
}
