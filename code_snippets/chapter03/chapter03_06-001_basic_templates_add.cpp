///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter03_06-001_basic_templates_add.cpp

#include <cstdint>
#include <iostream>
#include <string>

template<typename T>
constexpr auto add(const T& a, const T& b) -> T
{
  return a + b;
}

constexpr int n { add(1, 2) };
// n is 3.

constexpr float f { add(1.2F, 3.4F) };
// f is 4.6.

const std::string str
  { add(std::string("abc"), std::string("xyz")) };
// str is "abcxyz".

auto main() -> int
{
  std::cout << "int    addition result is " << n   << std::endl;
  std::cout << "float  addition result is " << f   << std::endl;
  std::cout << "string addition result is " << str << std::endl;
}
