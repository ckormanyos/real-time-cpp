///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter03_18-001_alignment.cpp

#include <iostream>

auto as  = alignof(short);      // Could be 2, 4,...
auto ai  = alignof(int);        // Could be 2, 4,...
auto aL  = alignof(long);       // Could be 4, 8,...
auto aLL = alignof(long long);  // Could be 8,...

auto main() -> int
{
  std::cout << as  << std::endl; // system-dependent result.
  std::cout << ai  << std::endl; // system-dependent result.
  std::cout << aL  << std::endl; // system-dependent result.
  std::cout << aLL << std::endl; // system-dependent result.
}
