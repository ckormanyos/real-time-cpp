///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2018 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter06_06-001_name_mangling.cpp

#include <iostream>

namespace this_space
{
  int my_integer { };
}

namespace another_space
{
  int my_integer { };
}

auto do_something() -> void;

auto do_something() -> void
{
  this_space::my_integer    = 123;
  another_space::my_integer =  42;

  std::cout << this_space::my_integer    << std::endl;
  std::cout << another_space::my_integer << std::endl;
}

auto main() -> int;

auto main() -> int
{
  do_something();
}
