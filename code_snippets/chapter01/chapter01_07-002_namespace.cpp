///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter01_07-002_namespace.cpp

#include <cstdint>
#include <iostream>

using namespace std;

uint8_t my_u8; // No need for std:: with uint8_t

auto main() -> int
{
  my_u8 = UINT8_C(42);

  // 42
  std::cout << unsigned { my_u8 } << std::endl;
}
