///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <concepts>
#include <iostream>
#include <string>
#include <type_traits>

// chapter05_06-003_template_concepts.cpp

// Generic add template function.
template<typename T>
auto add(T a, T b) -> T
{
  return a + b;
}

template<typename T>
requires std::integral<T>
auto add(T a, T b) -> T
{
  return a + b;
}

auto do_something() -> void
{
  // 3U
  const unsigned c { add(1U, 2U) };

  std::cout << c << std::endl;

  // abcxyz
  const std::string str
    { add(std::string("abc"), std::string("xyz")) };

  std::cout << str << std::endl;
}

auto main() -> int
{
  do_something();
}
