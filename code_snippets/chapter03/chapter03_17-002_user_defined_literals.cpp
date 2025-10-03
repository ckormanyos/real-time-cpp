///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter03_17-002_user_defined_literals.cpp

#include <iostream>
#include <string>

using namespace std::string_literals;

std::string str = "creativity"s;

auto main() -> int
{
  std::cout << "str is " << str << std::endl;
}
