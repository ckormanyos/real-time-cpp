///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <iostream>
#include <string>

// chapter05_06-001_template_specialization.cpp

// Generic add template function.
template<typename T>
auto add(T a, T b) -> T
{
  return a + b;
}

// Specialize add() for the type int.
template<>
auto add<int>(int a, int b) -> int
{
  return a + b;
}

auto main() -> int
{
  // Add with generic template to get result "abcxyz".
  std::cout << add(std::string("abc"), std::string("xyz")) << std::endl;

  // Add with specialized template to get result 3.
  std::cout << add(1, 2) << std::endl;
}
