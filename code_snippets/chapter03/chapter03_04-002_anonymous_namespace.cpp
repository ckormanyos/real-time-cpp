///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter03_04-002_anonymous_namespace.cpp

#include <iostream>

// A file-local anonymous namespace.
namespace
{
  unsigned local_counter;
}

auto main() -> int
{
  ++local_counter;

  std::cout << "local counter: " << local_counter << std::endl;
}
