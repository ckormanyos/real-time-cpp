///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter03_04-003_nested_namespace.cpp

#include <iostream>

// A nested namespace definition.
namespace X::Y::Z
{
  int value { };
}

auto do_something() -> void
{
  X::Y::Z::value = 1;
}

auto main() -> int
{
  do_something();

  std::cout << "X::Y::Z::value is " << X::Y::Z::value << std::endl;
}
